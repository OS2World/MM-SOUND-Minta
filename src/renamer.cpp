/***
 This file belongs to the Minta distribution.
 Copyright (C) 1998-2003 Thorsten Thielen <thth@gmx.net>

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 ***/

#include "renamer.h"

// ** Dialog ************************************************************** /*fold00*/

BOOL RENAMER :: Dialog (VOID)
{
    HWND   hwndDlg =
        WinLoadDlg (HWND_DESKTOP, pmp3d->hwnd, dp, GETMODULE, ID_DLG_RENAMER,
                    this);
    WinSetAccelTable (hab, WinLoadAccelTable (hab, GETMODULE, ID_DLG_RENAMER),
                      hwndDlg);
    ULONG   ul = WinProcessDlg (hwndDlg);
    WinDestroyWindow (hwndDlg);

    return (BOOL (ul));
}

// ** dp ****************************************************************** /*FOLD00*/

MRESULT EXPENTRY RENAMER :: dp (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    static BOOL     f = FALSE;
    static PRENAMER  pren = NULL;

    switch (msg)
    {
    case WM_INITDLG:
        pren = PRENAMER (mp2);

        WinSendDlgItemMsg (hwnd, WID_E_TEMPLATE, EM_SETTEXTLIMIT,
                           (MPARAM)_MAX_FNAME, (MPARAM)0);
        WinSetDlgItemText (hwnd, WID_E_TEMPLATE,
                           GETSETTINGS->QueryString (SEI_RENAMETEMPLATE));

        GETSETTINGS->AdjustButton (hwnd, WID_CB_LIMITLENGTH,
                            GETSETTINGS->QueryFlag (SEI_RENAMELIMITLENGTH));
        GETSETTINGS->AdjustButton (hwnd, WID_CB_REPLACESPACES,
                            GETSETTINGS->QueryFlag (SEI_RENAMEREPLACESPACES));

        // init length sb
        WinSendDlgItemMsg (hwnd, WID_SB_LENGTH, SPBM_SETLIMITS,
                           MPFROMLONG (_MAX_PATH), MPFROMLONG (1));
        WinSendDlgItemMsg (hwnd, WID_SB_LENGTH, SPBM_SETCURRENTVALUE,
                           MPFROMLONG (GETSETTINGS->QueryLong (SEI_RENAMELENGTH)), 0);
        return (MRESULT)FALSE;

    case WM_COMMAND:
        switch (COMMANDMSG (&msg)->cmd)
        {
        case WID_PB_RENAME:
            f = TRUE;
            WinSendMsg (hwnd, WM_CLOSE, NULL, NULL);
            break;

        case WID_PB_CANCEL:
            f = FALSE;
            WinSendMsg (hwnd, WM_CLOSE, NULL, NULL);
            break;
        }
        return (MRESULT)FALSE;

    case WM_CLOSE:
        {
            CHAR   ach[_MAX_PATH];

            WinQueryDlgItemText (hwnd, WID_E_TEMPLATE, sizeof (ach), ach);
            GETSETTINGS->SetString (SEI_RENAMETEMPLATE, ach);

            GETSETTINGS->SetFlag (SEI_RENAMELIMITLENGTH,
                                  GETSETTINGS->ButtonChecked (hwnd, WID_CB_LIMITLENGTH));
            GETSETTINGS->SetFlag (SEI_RENAMEREPLACESPACES,
                                  GETSETTINGS->ButtonChecked (hwnd, WID_CB_REPLACESPACES));
            // query length sb
            ULONG   ul;
            if (! BOOL
                (WinSendDlgItemMsg (hwnd, WID_SB_LENGTH, SPBM_QUERYVALUE,
                                    MPFROMP (&ul), MPFROM2SHORT (0, 0))))
                GETSETTINGS->SetLong (SEI_RENAMELENGTH, 31L);
            else
                GETSETTINGS->SetLong (SEI_RENAMELENGTH, ul);

            WinDismissDlg (hwnd, ULONG (f));
        }
        return MRESULT (FALSE);
    }

    return WinDefDlgProc (hwnd, msg, mp1, mp2);
}

// ** Rename ************************************************************** /*FOLD00*/

BOOL RENAMER :: Rename (PMP3 pmp3, PSZ pszTemplate, BOOL fReplaceSpaces,
                        USHORT cb)
{
    // Create our new name using the given template.
    CHAR    achName[_MAX_PATH];
    pmp3->ExpandMacros (pszTemplate, achName, _MAX_PATH);

    USHORT   i;

    // Replace all chars that are not allowed in filenames with '_'.
    for (i = 0; achName[i] != '\0'; i++)
    {
        switch (achName[i])
        {
        case '\\':
        case '?':
        case '*':
        case '/':
        case '<':
        case '>':
        case ':':
        case '"':
        case '|':
            achName[i] = '_';
            break;

        case ' ':
            if (fReplaceSpaces)
                achName[i] = '_';
            break;
        }
    }

    CHAR    achNew[_MAX_PATH], achTmp[_MAX_PATH];
    CHAR    achDrive[_MAX_DRIVE], achDir[_MAX_DIR], achExt[_MAX_EXT];

    // get the various components of our path
    _splitpath (pmp3->QueryFilename ().c_str (),
                achDrive, achDir, achTmp, achExt);

    // Check if the current name is equal to the new name. Obviously no need
    // to do anything then :-)
    if( stricmp( achName, achTmp ) == 0) {
        return TRUE;
    }

    if (cb)
    {
        // Check if the extension is already longer than our names limit;
        // this is not likely to happen, but ...
        if (strlen (achExt) >= cb)
            return FALSE;
/*        // if Title is already too long, shorten it
        if (strlen (achTitle) + strlen (achExt) > MAX_AUTONAMELEN)
            achTitle[MAX_AUTONAMELEN-strlen (achExt)] = '\0';*/
    }

    pmp3->Close ();

    // Check if names are to be limited too a certain length (31 chars
    // currently only) and check if our name is too long and shorten it
    // in this case.
    if (cb && (strlen (achName)+strlen (achExt) > cb))
    {
        CHAR   achName2[_MAX_PATH];
        strcpy (achName2, achName);
        achName2[cb-strlen (achExt)] = '\0';
        sprintf (achNew, "%s%s", achName2, achExt);
        sprintf (achNew, "%s%s%s%s", achDrive, achDir, achName2, achExt);
    }
    else
        sprintf (achNew, "%s%s%s%s", achDrive, achDir, achName, achExt);

    // Check if there is a file that is already named like our new name;
    // if there is, add a running number and try again until we find an
    // unused name.
    for (i = 1; access (achNew, 0) == 0; i ++)
    {
        if (cb)
        {
            while (19)
            {
                sprintf (achNew, "%s_%d%s", achName, i, achExt);
                if (strlen (achNew) > cb)
                {
                    if (strlen (achName) > 1)
                        achName[strlen (achName)-1] = '\0';
                    else
                        return FALSE;
                }
                else
                {
                    sprintf (achNew, "%s%s%s_%d%s", achDrive, achDir,
                             achName, i, achExt);
                    break;
                }
            }
        }
        else
            sprintf (achNew, "%s%s%s_%d%s", achDrive, achDir,
                     achName, i, achExt);
    }

    return pmp3->Rename (achNew);
}

// ************************************************************************
