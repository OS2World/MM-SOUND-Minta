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

#include "status.h"

// ** StatusDisplay ******************************************************* /*FOLD00*/

STATD :: StatusDisplay (PSZ pszName, ULONG c, HWND hwndOwner, BOOL f, PBOOL pf)
{
    cMax    = c;
    this->c = 0L;

    fInstantQuit = f;
    fFinished    = FALSE;

    pfBreak = pf;

    hwndDlg = WinLoadDlg (HWND_DESKTOP, hwndOwner, DialogProcedure,
                          GETMODULE, ID_DLG_STATUS, this);
    WinSetWindowText (hwndDlg, pszName);
}

// ** Dialog ************************************************************** /*FOLD00*/

VOID STATD :: Process (VOID)
{
    WinProcessDlg (hwndDlg);
    WinDestroyWindow (hwndDlg);
}

// ** DialogProcedure ***************************************************** /*FOLD00*/

MRESULT EXPENTRY
STATD :: DialogProcedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    static PSTATD   pstatd;

    switch (msg)
    {
    case WM_INITDLG:
        pstatd = PSTATD (mp2);
        return MRESULT (FALSE);

    case WM_COMMAND:
        switch (COMMANDMSG (&msg)->cmd)
        {
        case WID_PB_OK:
            if (! pstatd->fFinished)
            {
                // tell thread to end
                *(pstatd->pfBreak) = TRUE;
            }
            else if (! pstatd->fInstantQuit)
                WinPostMsg (hwnd, WM_CLOSE, 0,0);
            break;
        }
        return MRESULT (FALSE);

    case WM_CLOSE:
        // we can't close if thread isn't finished
        if (! pstatd->fFinished)
        {
            WinPostMsg (hwnd, WM_CLOSE, 0,0);
            return MRESULT (FALSE);
        }
        WinDismissDlg (hwnd, TRUE);
        return MRESULT (FALSE);
    }

    return WinDefDlgProc (hwnd, msg, mp1, mp2);
}

// ** Advance ************************************************************* /*FOLD00*/

VOID STATD :: Advance (PSZ psz)
{
    c ++;

    if (! hwndDlg)
        return;

    CHAR   ach[21];
#ifdef _MULTILANGUAGES_
    sprintf (ach, RSTR (IDS_XOFX), c, cMax);
#else
    sprintf (ach, "%ld of %ld", c, cMax);
#endif
    WinSetWindowText (WinWindowFromID (hwndDlg, WID_ST_COUNT), ach);

    WinSetWindowText (WinWindowFromID (hwndDlg, WID_E_FILE), psz);

    WinSendDlgItemMsg (hwndDlg, WID_S_PROGRESS, SLM_SETSLIDERINFO,
                       MPFROM2SHORT (SMA_SLIDERARMPOSITION,
                                     SMA_INCREMENTVALUE),
                       MPFROMLONG ((c*100L)/cMax));
}

// ** Finished ************************************************************ /*FOLD00*/

VOID STATD :: Finished (VOID)
{
    fFinished = TRUE;

    if (! hwndDlg)
        return;

    WinSetWindowText (WinWindowFromID (hwndDlg, WID_PB_OK),
#ifdef _MULTILANGUAGES_
                      RSTR (IDS_OK));
#else
                      "Ok");
#endif
    if (fInstantQuit)
        WinPostMsg (hwndDlg, WM_CLOSE, 0,0);
}

// ************************************************************************
