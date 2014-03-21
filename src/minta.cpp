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

#define OS2EMX_PLAIN_CHAR
#define INCL_WIN

#include "minta.h"
#include "mp3disp.h"

HAB       hab;
#ifdef _LOADGENRES_
PGENLIST  pgenlist;
#endif
PMP3DISPLAY   g_pmp3d;
HMODULE       hmod;

#ifdef _WARPAMPFIX_
BOOL g_fUseSpaces = FALSE;
#endif

#ifdef _TWO_DIGIT_TRACKNUMBERS_
BOOL g_fTwoDigitTracknumbers = FALSE;
#endif

#ifdef _SET_INI_FILE_PATH_
CHAR g_pszIniFilePath[_MAX_PATH];
#endif

#ifdef _ALLOW_DISABLE_EA_ERROR_
CHAR g_fDisableEAError = FALSE;
#endif

#ifdef _DEBUGLOG_
FILE   *pfileLog = NULL;
#endif

CHAR g_pszMintaDir[_MAX_PATH];

int main (int argc, char *argv[])
{
    HMQ  hmq;
    PSZ  pszFile = NULL;

    // Get path of Minta's exe-file; used for getting the path to our
    // ressouce dlls.
    CHAR    achDrive[_MAX_DRIVE], achDir[_MAX_DIR];
    CHAR    achName[_MAX_FNAME], achExt[_MAX_EXT];

#ifdef _FROM_FOREIGN_DIR_
    // get the various components of our path
    _splitpath( argv[0], achDrive, achDir, achName, achExt );
    sprintf( g_pszMintaDir, "%s%s", achDrive, achDir );
#endif

    for (argc--; argc >= 1; argc--) {
#ifdef _WARPAMPFIX_
        if (stricmp (argv[argc], "-f") == 0)
            g_fUseSpaces = TRUE;
#endif
#ifdef _TWO_DIGIT_TRACKNUMBERS_
        if (stricmp (argv[argc], "-t") == 0)
            g_fTwoDigitTracknumbers = TRUE;
#endif
#ifdef _SET_INI_FILE_PATH_
        if (strnicmp (argv[argc], "-i", 2) == 0)
            strcpy( g_pszIniFilePath, argv[argc]+2 );
#endif
#ifdef _ALLOW_DISABLE_EA_ERROR_
        if (strnicmp (argv[argc], "-e", 2) == 0)
            g_fDisableEAError = TRUE;
#endif
        // Well, a rather unsecure method of detection if a filename was
        // given ...
        if( argv[argc][0] != '-' ) {
            pszFile = argv[argc];
        }
    }

#ifdef _DEBUGLOG_
    if (! (pfileLog = fopen ("minta.log", "ab")))
        DosBeep (1000, 2000);
    else
    {
        time_t      tt = time (NULL);
        struct tm   *ptm = localtime (&tt);
        fprintf (pfileLog, "\n%s"
                 "-------------\n"
                 "Program started ...\n"
                 "-------------\n", asctime (ptm));
    }
#endif

    hab = WinInitialize (0);
    hmq = WinCreateMsgQueue (hab, 0);

    hmod = NULLHANDLE;

    PMP3DISPLAY   pmp3d;

    if (pszFile)
        pmp3d = new MP3DISPLAY (pszFile);
    else
        pmp3d = new MP3DISPLAY;

    // yes, yes, everything else is handled in the above constructor!
    delete pmp3d;

    WinDestroyMsgQueue (hmq);
    WinTerminate (hab);

#ifdef _DEBUGLOG_
    if (pfileLog)
    {
        time_t      tt = time (NULL);
        struct tm   *ptm = localtime (&tt);
        fprintf (pfileLog, "\n%s"
                 "-------------\n"
                 "Program ended ...\n"
                 "-------------\n", asctime (ptm));
        fclose (pfileLog);
    }
#endif
    return 0;
}

// ** DisplayError ******************************************************** /*FOLD00*/

VOID DisplayError (PSZ pszTitle, PSZ psz, ...)
{
    CHAR      dstring[401];
    va_list   valst;

    va_start (valst, psz);
    vsnprintf (dstring, 401, psz, valst);
    va_end (valst);

    WinMessageBox (HWND_DESKTOP, WinQueryActiveWindow (HWND_DESKTOP), dstring,
                   pszTitle, 0, MB_OK | MB_ERROR | MB_APPLMODAL | MB_MOVEABLE);
}

// ** DisplayInfo *********************************************************

VOID DisplayInfo (PSZ pszTitle, PSZ psz, ...)
{
    CHAR      dstring[401];
    va_list   valst;

    va_start (valst, psz);
    vsnprintf (dstring, 401, psz, valst);
    va_end (valst);

    WinMessageBox (HWND_DESKTOP, WinQueryActiveWindow (HWND_DESKTOP), dstring,
                   pszTitle, 0, MB_OK | MB_INFORMATION | MB_APPLMODAL |
                   MB_MOVEABLE);
}

// ** strkspc ************************************************************* /*fold00*/

PSZ strkspc (PSZ psz)
{
    SHORT   i = strlen (psz)-1;

    while (isspace (psz[i]) && (i >= 0))
    {
        psz[i] = '\0';
        i --;
    }

    return (psz);
}

// ************************************************************************

#ifdef _ANIMTEST_

#define C_POINTERS   16

VOID AnimateMousepointer (VOID)
{
    USHORT     i, j;
    HPOINTER   hptr[C_POINTERS];

    for (i = 0; i < C_POINTERS; i++)
        hptr[i] = WinLoadPointer (HWND_DESKTOP, NULLHANDLE, i+11);

    for (j = 0; j < 100; j++)
    {
        for (i = 0; i < C_POINTERS; i++)
        {
            WinSetPointer (HWND_DESKTOP, hptr[i]);
            _sleep2 (10);
        }
        for (i = C_POINTERS-1; i > 1; i--)
        {
            WinSetPointer (HWND_DESKTOP, hptr[i]);
            _sleep2 (10);
        }
    }

    for (i = 0; i < C_POINTERS; i++)
        WinDestroyPointer (hptr[i]);
}

#endif

// ** Notify ************************************************************** /*fold00*/

VOID Notify (PSZ pszTitle, PSZ psz, ...)
{
    switch (GETSETTINGS->QueryNotifyStyle ())
    {
    case NOST_CLICKAWAY:
        {
            CHAR      ach[401];
            va_list   valst;

            va_start (valst, psz);
            vsnprintf (ach, 401, psz, valst);
            va_end (valst);

            WinMessageBox (HWND_DESKTOP, WinQueryActiveWindow (HWND_DESKTOP),
                           ach, pszTitle, 0,
                           MB_OK | MB_INFORMATION | MB_APPLMODAL |
                           MB_MOVEABLE);
        }
        break;

    case NOST_BEEP:
        DosBeep (1000, 100);
        DosBeep (2000, 150);
        DosBeep (3000, 200);
        break;

    default:
        {
            CHAR      ach[401];
            va_list   valst;

            va_start (valst, psz);
            vsnprintf (ach, 401, psz, valst);
            va_end (valst);

            HWND   hwndDlg =
                WinLoadDlg (HWND_DESKTOP, WinQueryActiveWindow (HWND_DESKTOP),
                            NotifyWP, GETMODULE, ID_DLG_NOTIFY,
                            PVOID (WinQueryActiveWindow (HWND_DESKTOP)));
            WinSetWindowText (hwndDlg, pszTitle);
            WinSetWindowText (WinWindowFromID (hwndDlg, WID_ST_NOTIFY), ach);
            WinStartTimer (GETHAB, hwndDlg, TID_USERMAX-1, 40L*strlen (ach));
            WinProcessDlg (hwndDlg);
            WinDestroyWindow (hwndDlg);
        }
    }

    return;
}

// ** NotifyWP ************************************************************ /*fold00*/

MRESULT EXPENTRY NotifyWP (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    switch (msg)
    {
    case WM_INITDLG:
        {
            RECTL   rclScreen, rclDialog;
            LONG    sWidth, sHeight, sBLCx, sBLCy;

            WinQueryWindowRect (HWND_DESKTOP, &rclScreen);
            WinQueryWindowRect (hwnd, &rclDialog);

            sWidth = (LONG) (rclDialog.xRight - rclDialog.xLeft);
            sHeight = (LONG) (rclDialog.yTop - rclDialog.yBottom);

            sBLCx = ((LONG) rclScreen.xRight - sWidth) / 2;
            sBLCy = ((LONG) rclScreen.yTop - sHeight) / 2;

            WinSetWindowPos(hwnd,
                            HWND_TOP,
                            sBLCx, sBLCy,
                            0, 0,
                            SWP_MOVE);
        }
        return MRESULT (FALSE);

    case WM_BUTTON1DOWN:
    case WM_BUTTON2DOWN:
    case WM_TIMER:
        WinSendMsg (hwnd, WM_CLOSE, 0,0);
        return MRESULT (FALSE);

    case WM_CLOSE:
        WinStopTimer (GETHAB, hwnd, TID_USERMAX-1);
        WinDismissDlg (hwnd, TRUE);
        return MRESULT (TRUE);

/*    case WM_PAINT:
        {
            HPS     hps = WinBeginPaint (hwnd, NULLHANDLE, NULL);
            RECTL   rcl;
            WinQueryWindowRect (hwnd, &rcl);
            WinDrawText (hps, strlen (psz), psz, &rcl, 0,0,
                         DT_CENTER | DT_VCENTER | DT_WORDBREAK | DT_TEXTATTRS);
            WinEndPaint (hps);
        }
        return MRESULT (FALSE); */
    }
    return WinDefDlgProc (hwnd, msg, mp1, mp2);
}

// ** FileDLGProcedure **************************************************** /*fold00*/

MRESULT EXPENTRY FileDLGProcedure (HWND hwnd, ULONG msg, MPARAM mp1,
                                   MPARAM mp2)
{
    return WinDefFileDlgProc (hwnd, msg, mp1, mp2);
}

#ifdef _SET_INI_FILE_PATH_
// ** QueryProfileName ****************************************************

PSZ _QueryProfileName( VOID )
{
    static char ach[_MAX_PATH];
    if( strlen( g_pszIniFilePath ) ) {
        if( g_pszIniFilePath[ strlen( g_pszIniFilePath )-1 ] == '\\' ) {
            sprintf( ach, "%sminta.ini", g_pszIniFilePath );
        } else {
            sprintf( ach, "%s\\minta.ini", g_pszIniFilePath );
        }
    } else {
        if( access( "minta.ini", 0 ) != 0) {
            sprintf( ach, "%sminta.ini", g_pszMintaDir );
        } else {
            sprintf( ach, "minta.ini" );
        }
    }
    return ach;
}

#endif

// ************************************************************************
