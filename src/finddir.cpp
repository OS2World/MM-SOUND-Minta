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

#include "finddir.h"

// ** defines ************************************************************* /*fold00*/

CHAR   FINDDIR :: pszDummy[_MAX_PATH];

// ** Dialog ************************************************************** /*FOLD00*/

BOOL FINDDIR :: Dialog (HWND hwnd, PSZ pszDir, PSZ pszBuffer, ULONG ulSize)
{
    if (pszDir && pszDir[0])
    {
        strcpy (pszBuffer, pszDir);

        struct stat   st;

        stat (pszBuffer, &st);

        if (S_ISREG (st.st_mode))
        {
            PSZ   psz = _getname (pszBuffer);
            if (psz)
                *(psz-1) = '\0';
        }
    }
    else
    {
        ULONG   pdisknum, plogical;
        DosQueryCurrentDisk (&pdisknum, &plogical);

        CHAR    psz[_MAX_PATH];
        ULONG   ul = _MAX_PATH;
        DosQueryCurrentDir (pdisknum, psz, &ul);
        sprintf (pszBuffer, "%c:\\%s", CHAR (pdisknum-1+'A'), psz);
    }

    SetBuffer (pszBuffer, ulSize);

    WinLoadDlg (HWND_DESKTOP, hwnd, DialogProcedure, GETMODULE,
                ID_DLG_FINDDIR, this);
    WinSetAccelTable (hab, WinLoadAccelTable (hab, GETMODULE,
                                              ID_ACCELTABLE_FINDDIR),
                      QueryHWND ());
    ULONG   ul = WinProcessDlg (QueryHWND ());
    WinDestroyWindow (QueryHWND ());

    SetBuffer (NULL, 0L);

    return (BOOL (ul));
}

// ** DialogProcedure ***************************************************** /*fold00*/

MRESULT EXPENTRY
FINDDIR :: DialogProcedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    static BOOL       f = FALSE;
    static PFINDDIR   pfd = NULL;

    switch (msg)
    {
    case WM_INITDLG:
        {
            pfd = PFINDDIR (mp2);
            pfd->hwnd = hwnd;

            // The calls made in ResetDrives () will overwrite (via LN_SELECT)
            // the dir we set through ChangeDirectory () if we don't set this
            // flag
            pfd->fSkipSelect = TRUE;

            pfd->ResetDrives ();
            pfd->ChangeDirectory (pfd->pszBuffer);
        }
        return MRESULT (FALSE);

    case WM_COMMAND:
        switch (COMMANDMSG (&msg)->cmd)
        {
        case DID_CANCEL:
            f = FALSE;
            WinSendMsg (hwnd, WM_CLOSE, NULL, NULL);
            break;

        case DID_OK:
            f = TRUE;
            WinSendMsg (hwnd, WM_CLOSE, NULL, NULL);
            break;

        default:
            DosBeep (1000, 10);
            break;
        }
        return MRESULT (FALSE);

    case WM_CONTROL:
        switch (SHORT1FROMMP (mp1))
        {
        case WID_LB_DIRECTORIES:
            switch (SHORT2FROMMP (mp1))
            {
            case LN_ENTER:
                if (strcmp (pfd->QuerySelected (), "..") == 0)
                    WinSendMsg (hwnd, UM_DIROUT, NULL, NULL);
                else
                    WinSendMsg (hwnd, UM_DIRIN, NULL, NULL);
                break;
            }
            break;

        case WID_LB_DRIVES:
            switch (SHORT2FROMMP (mp1))
            {
            case LN_SELECT:
                if (! pfd->fSkipSelect)
                {
                    pfd->fSkipSelect = TRUE;
                    if (! pfd->ChangeDrive (pfd->QuerySelectedDrive ()))
                        if (! pfd->ChangeDrive (pfd->usOldDrive))
                            pfd->ResetDrives ();
                }
                pfd->fSkipSelect = FALSE;
                break;
            }
            break;
        }
        return MRESULT (FALSE);

    case UM_DIRIN:      pfd->DirIn ();           return (MRESULT)0;
    case UM_DIROUT:     pfd->DirOut ();          return (MRESULT)0;

    case WM_CLOSE:
        WinDismissDlg (hwnd, f);
        return MRESULT (FALSE);
    }

    return WinDefDlgProc (hwnd, msg, mp1, mp2);
}

// ** ChangeDrive ********************************************************* /*fold00*/

BOOL FINDDIR :: ChangeDrive (USHORT us)
{
    CHAR   ach[_MAX_PATH];

    ULONG   ul = sizeof (ach);
    switch (USHORT usError = DosQueryCurrentDir (us+1, ach, &ul))
    {
    case NO_ERROR:
        break;

    case ERROR_INVALID_DRIVE:
        DisplayError ("ERROR", "Invalid drive.");
        return FALSE;

    case ERROR_NOT_DOS_DISK:
        DisplayError ("ERROR", "Not a DOS disk.");
        return FALSE;

    case ERROR_DRIVE_LOCKED:
        DisplayError ("ERROR", "Drive locked.");
        return FALSE;

    case ERROR_BUFFER_OVERFLOW:
        DisplayError ("ERROR", "Buffer overflow.");
        return FALSE;

    case ERROR_NOT_READY:
        DisplayError ("ERROR", "Drive not ready.");
        return FALSE;

    default:
        DisplayError ("ERROR", "Error %d (Sorry for being not more specific!)",
                      usError);
        return FALSE;
    }

    USHORT  usDrive, i;

    for (i = DRIVE_FIRST; i < DRIVE_LAST; i++)
        if ((usDrive = USHORT
             (WinSendDlgItemMsg (hwnd, WID_LB_DRIVES, LM_QUERYITEMHANDLE,
                                 MPFROMSHORT (i), 0))) == us)
            break;

    // drive us not found in list
    if (usDrive != us)
        return FALSE;

    WinSendDlgItemMsg (hwnd, WID_LB_DRIVES, LM_SELECTITEM,
                       MPFROMLONG (i), MPFROMLONG (TRUE));
    WinSendDlgItemMsg (hwnd, WID_LB_DRIVES, CBM_SHOWLIST, FALSE, 0);
    usOldDrive = us;

/*    if (strlen (ach) == 0)
        sprintf (pszBuffer, "%c:", CHAR (us+'A'));
    else */
    sprintf (pszBuffer, "%c:\\%s", CHAR (us+'A'), ach);

    return ChangeDirectory (pszBuffer);
}

// ** DirIn *************************************************************** /*fold00*/

BOOL FINDDIR :: DirIn (VOID)
{
    if (pszBuffer[strlen (pszBuffer)-1] == '\\')
        sprintf (pszBuffer, "%s%s", pszBuffer, QuerySelected ());
    else
        sprintf (pszBuffer, "%s\\%s", pszBuffer, QuerySelected ());

    DisableListRefresh ();
    ChangeDirectory (pszBuffer);
    SelectFirstItem ();
    EnableListRefresh ();

    return (TRUE);
}

// ** DirOut ************************************************************** /*fold00*/

BOOL FINDDIR :: DirOut (VOID)
{
    PSZ   psz = strrchr (pszBuffer, '\\');

    if (psz)
    {
        // only a drive ('c:') or only the "root-backslash" ('\') ?
        if (psz == pszBuffer)
            psz[1] = '\0';
        else if (psz[-1] == ':')
            psz[1] = '\0';
        else
            psz[0] = '\0';
    }

    DisableListRefresh ();
    ChangeDirectory (pszBuffer);
    SelectFirstItem ();
    EnableListRefresh ();

    return (TRUE);
}

// ** ChangeDirectory ***************************************************** /*fold00*/

BOOL FINDDIR :: ChangeDirectory (PSZ psz)
{
    ClearItemList ();

    CHAR          pszPath[_MAX_PATH];
    HDIR          hdir;
    ULONG         c, fl, cFound = 0L;
    FILEFINDBUF3  findbuf;
    APIRET        rc;

    if (psz[strlen (psz)-1] == '\\')
        sprintf (pszPath, "%s*", psz);
    else
        sprintf (pszPath, "%s\\*", psz);

    /* find all subdirectories */
    fl = MUST_HAVE_DIRECTORY;
    hdir = HDIR_CREATE;
    c = 1L;
    rc = DosFindFirst (pszPath, &hdir, fl, &findbuf, sizeof (findbuf), &c,
                       FIL_STANDARD);
    while (!rc)
    {
        if ((strcmp (findbuf.achName, "..") == 0) && (strlen (psz) <= 3))
            ;
        else if (strcmp (findbuf.achName, ".") == 0)
            ;
        else
            AddItem (findbuf.achName);

        cFound ++;
        c = 1L;
        rc = DosFindNext (hdir, &findbuf, sizeof (findbuf), &c);
    }
    DosFindClose (hdir);

    // The calls made when selecting here will overwrite (via LN_SELECT)
    // the dir we set through ChangeDirectory () if we don't set this flag
    // FIXME this whole section is not that good ...
    fSkipSelect = TRUE;
    WinSendDlgItemMsg (hwnd, WID_LB_DRIVES, LM_SELECTITEM,
                       MPFROMLONG (toupper (psz[0])-'A'), MPFROMLONG (TRUE));
    WinSendDlgItemMsg (hwnd, WID_LB_DRIVES, CBM_SHOWLIST, FALSE,
                       0);

    HWND    hwndText = WinWindowFromID (QueryHWND (), WID_ST_PATH);
    WinSetWindowText (hwndText, pszBuffer);

    return TRUE;
}

// ** QuerySelected ******************************************************* /*fold00*/

PSZ FINDDIR :: QuerySelected (VOID)
{
    HWND    hwndLB = WinWindowFromID (QueryHWND (), WID_LB_DIRECTORIES);
    ULONG   ul = (ULONG) WinSendMsg (hwndLB, LM_QUERYSELECTION,
                                     NULL, NULL);
    WinQueryLboxItemText (hwndLB, ul, pszDummy, _MAX_PATH);
    return (pszDummy);
}

// ** QuerySelectedDrive ************************************************** /*fold00*/

USHORT FINDDIR :: QuerySelectedDrive (VOID)
{
    HWND     hwndLB = WinWindowFromID (QueryHWND (), WID_LB_DRIVES);
    USHORT   us = USHORT (WinQueryLboxSelectedItem (hwndLB));
    USHORT   us2 = USHORT (WinSendMsg (hwndLB, LM_QUERYITEMHANDLE,
                                       MPFROMSHORT (us), NULL));
    return (us2);
}

// ** AddItem ************************************************************* /*fold00*/

LONG FINDDIR :: AddItem (PSZ psz)
{
    HWND   hwnd = WinWindowFromID (QueryHWND (), WID_LB_DIRECTORIES);
    LONG   l = (LONG) WinSendMsg (hwnd, LM_INSERTITEM,
                                  MPFROM2SHORT (LIT_SORTASCENDING,0),
                                  MPFROMP (psz));
    return (l);
}

// ** SelectFirstItem ***************************************************** /*fold00*/

VOID FINDDIR :: SelectFirstItem (VOID)
{
    HWND    hwnd = WinWindowFromID (QueryHWND (), WID_LB_DIRECTORIES);
    WinSetFocus (HWND_DESKTOP, hwnd);
    WinSendMsg (hwnd, LM_SELECTITEM, MPFROMLONG (0), MPFROM2SHORT (TRUE, 0));
}

// ** ResetDrives ********************************************************* /*fold00*/

USHORT FINDDIR :: ResetDrives (VOID)
{
    USHORT   i;
    ULONG    pdisknum, plogical, ul;
    CHAR     pszDrive[_MAX_DRIVE];

    // clear combo-box
    WinSendDlgItemMsg (hwnd, WID_LB_DRIVES, LM_DELETEALL, 0,0);

    // fill combo-box with all available drives
    DosQueryCurrentDisk (&pdisknum, &plogical);
    usOldDrive = pdisknum-1;

    for (i = DRIVE_FIRST; i <= DRIVE_LAST; i++)
        if (plogical & (1<<i))
        {
            sprintf (pszDrive, "%c:", i+'A');
            ul = ULONG (WinSendDlgItemMsg (hwnd, WID_LB_DRIVES, LM_INSERTITEM,
                                           MPFROMSHORT (LIT_SORTASCENDING),
                                           pszDrive));
            WinSendDlgItemMsg (hwnd, WID_LB_DRIVES, LM_SETITEMHANDLE,
                               MPFROMSHORT (ul), MPFROMSHORT (i));
            // make current drive the selected
            // NOTE: this will set other stuff via LN_SELECT in the WP
            if (i == usOldDrive)
            {
                WinSendDlgItemMsg (hwnd, WID_LB_DRIVES, LM_SELECTITEM,
                                   MPFROMLONG (ul), MPFROMLONG (TRUE));
                WinSendDlgItemMsg (hwnd, WID_LB_DRIVES, CBM_SHOWLIST, FALSE,
                                   0);
            }
        }

    return usOldDrive;
}

// ************************************************************************
