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

#include "minta.h"
#include "toolbar.h"

BOOL TOOLBAR :: fClassRegistered = FALSE;
PTOOLBAR TOOLBAR :: ptb = NULL;   // FIXME puke!

// ** Toolbar ************************************************************* /*fold00*/

TOOLBAR :: Toolbar (HWND hwndFrame)
{
    TOOLBAR::ptb = this; // FIXME puke!

    fHidden = TRUE;
    this->hwndFrame = hwndFrame;

    if (WinWindowFromID (hwndFrame, FID_CLIENT))
        fOwnerIsDialog = FALSE;
    else
        fOwnerIsDialog = TRUE;

    // no buttons by now ...
    c = 0;
    memset (aid, 0x00, sizeof (aid[0]) * TOOLBARBUTTONSMAX);

    if (! (pfnwpOldFrame =
           WinSubclassWindow (hwndFrame, PFNWP (fnwpNewFrame))))
        return;

    // if not already registered, register our window class
    if (! fClassRegistered)
    {
        WinRegisterClass (GETHAB, PSZ_WCTOOLBAR, fnwp, 0L, 4L);
        fClassRegistered = TRUE;
    }

    // either place under menu or under titlebar
    SHORT  y, cx;
    SWP    swp;

    if ((hwndAnchor = WinWindowFromID (hwndFrame, FID_MENU)))
    {
        WinQueryWindowPos (hwndAnchor, &swp);
        cx = swp.cx;
        y  = swp.y-CY_TOOLBAR;
    }
    else if ((hwndAnchor = WinWindowFromID (hwndFrame, FID_TITLEBAR)))
    {
        WinQueryWindowPos (hwndAnchor, &swp);
        cx = swp.cx;
        y  = swp.y-CY_TOOLBAR;
    }
    else
    {
        cx = 1;
        y = 0;
    }

    // create client window and assign object ptr to window word
    hwnd = WinCreateWindow (hwndFrame, PSZ_WCTOOLBAR, "", 0L, 0,y,
                            cx,CY_TOOLBAR, hwndFrame, HWND_TOP, FID_TOOLBAR,
                            NULL, NULL);
    WinSetWindowPtr (hwnd, 0, this);
}

// ** ~Toolbar ************************************************************ /*fold00*/

TOOLBAR :: ~Toolbar (VOID)
{
    // FIXME destroy buttons
    WinDestroyWindow (hwnd);
}

// ** AddButton *********************************************************** /*fold00*/

SHORT TOOLBAR :: AddButton (USHORT id, USHORT usBitmapID, SHORT sPos, PSZ psz,
                            BOOL fHelp)
{
    // room left for another button?
    if (c >= TOOLBARBUTTONSMAX)
        return -1;

    CHAR   ach[11];
    sprintf (ach, "#%u", usBitmapID);

    USHORT   x = X_TBBUTTONS, y = Y_TBBUTTONS;
    USHORT   cx = CX_TBBUTTONS, cy = CY_TBBUTTONS;

    if (id == TBID_SEPERATOR)
        cx = CX_TBSEPERATOR;

    if ((sPos > c) || (sPos == TBPOS_LAST))
        sPos = c;
    else if (sPos == TBPOS_FIRST)
        sPos = 0;

    // shift all buttons (window and ID in id-array) to the "right"
    SWP   swp;
    HWND  hwndButton;

    for (SHORT i = c-1; i >= sPos; i--)
    {
        hwndButton = WinWindowFromID (hwnd, aid[i]);

        WinQueryWindowPos (hwndButton, &swp);
        WinSetWindowPos (hwndButton, 0L, swp.x+cx,swp.y, 0,0, SWP_MOVE);
        aid[i+1] = aid[i];
    }

    // get x-position (in pixels) for button
    for (SHORT i = 0; i < sPos; i++)
    {
        if (aid[i] != TBID_SEPERATOR)
        {
            hwndButton = WinWindowFromID (hwnd, aid[i]);
            WinQueryWindowPos (hwndButton, &swp);
            x += swp.cx;
        }
        else
            x += CX_TBSEPERATOR;
    }

    // insert button id in array
    aid[sPos] = id;
    apsz[sPos] = psz;
    c ++;

    if (id != TBID_SEPERATOR)
    {
        // create button control
        //        HWND   hwndButton =
        if (! fHelp)
            WinCreateWindow (hwnd, WC_BUTTON, ach,
                             WS_VISIBLE | WS_TABSTOP | BS_NOPOINTERFOCUS |
                             BS_PUSHBUTTON | BS_BITMAP,
                             x,y, cx,cy, hwnd, HWND_TOP, id, NULL, NULL);
        else
            WinCreateWindow (hwnd, WC_BUTTON, ach,
                             WS_VISIBLE | WS_TABSTOP | BS_NOPOINTERFOCUS |
                             BS_PUSHBUTTON | BS_BITMAP | BS_HELP,
                             x,y, cx,cy, hwnd, HWND_TOP, id, NULL, NULL);
    }
    return sPos;
}

// ** fnwp **************************************************************** /*fold00*/

MRESULT EXPENTRY
TOOLBAR :: fnwp (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    PTOOLBAR        ptb = PTOOLBAR (WinQueryWindowPtr (hwnd, 0));
//    static USHORT   id = 0;

    switch (msg)
        {
        case WM_PAINT:
            {
                RECTL   rcl;
                HPS     hps = WinBeginPaint (hwnd, NULLHANDLE, NULL);

                WinQueryWindowRect (hwnd, &rcl);
                GpiMove (hps, (PPOINTL) &rcl.xLeft);
                GpiSetColor (hps, SYSCLR_MENU);
                GpiBox (hps, DRO_FILL, (PPOINTL) &rcl.xRight, 0, 0);

                POINTL  ptl;

                GpiSetColor (hps, SYSCLR_BUTTONLIGHT);

                ptl.x = rcl.xLeft;
                ptl.y = rcl.yBottom;
                GpiMove (hps, &ptl);

                ptl.x = rcl.xRight;
                ptl.y = rcl.yBottom;
                GpiLine (hps, &ptl);

                GpiSetColor (hps, SYSCLR_BUTTONDARK);

                ptl.x = rcl.xLeft;
                ptl.y = rcl.yBottom+1;
                GpiMove (hps, &ptl);

                ptl.x = rcl.xRight;
                ptl.y = rcl.yBottom+1;
                GpiLine (hps, &ptl);

                WinEndPaint (hps);
            }
            break;

/*        case WM_CONTROLPOINTER:
            DosBeep (1000, 1);
            return MRESULT (TRUE);

        case WM_MOUSEMOVE:
            DosBeep (1000, 1);
            return MRESULT (TRUE);*/

        case WM_COMMAND:
            if (ptb)
                WinSendMsg (ptb->hwndFrame, msg, mp1, mp2);
            else
                DosBeep (1000, 10);
            return MRESULT (FALSE);
        }

    return WinDefWindowProc (hwnd, msg, mp1, mp2);
}

// ** fnwpNewFrame ******************************************************** /*fold00*/

MRESULT EXPENTRY
TOOLBAR :: fnwpNewFrame (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    PTOOLBAR   ptb = TOOLBAR::QueryToolbar (hwnd);

#ifdef _DEBUGLOG_
    Log ("TOOLBAR::WindowProcedure (0x%08lx, %ld, 0x%08lx, 0x%08lx)\n",
         hwnd, msg, mp1, mp2);
#endif

    if (! ptb)
        return WinDefWindowProc (hwnd, msg, mp1, mp2);

    switch (msg)
    {
    case WM_CLOSE:
        ptb->hwnd = NULLHANDLE;
        break;

    case WM_CALCFRAMERECT:
        {
            MRESULT   mr = ptb->pfnwpOldFrame (hwnd, msg, mp1, mp2);
            if (mr && mp2 && ptb->IsShown ())
            {
                PRECTL prectl = PRECTL (mp1);
                prectl->yTop -= CY_TOOLBAR;
                prectl->yBottom -= CY_TOOLBAR;
            }
            return mr;
        }

    case WM_FORMATFRAME:
        {
            SHORT sCount = SHORT (ptb->pfnwpOldFrame (hwnd, msg, mp1, mp2));

            if (ptb->IsShown ())
            {
                PSWP   pswp = PSWP (mp1);
                PSWP   pswpClient = NULL, pswpNew = pswp+sCount;
                HWND   hwndClient = WinWindowFromID (hwnd, FID_CLIENT);

                for (SHORT i = sCount; i >= 0; i--)
                    if ((pswp+i)->hwnd == hwndClient)
                    {
                        pswpClient = pswp+i;
                        break;
                    }

                *pswpNew = *pswpClient;

                // clients keeps old size
                pswpClient->cy -= CY_TOOLBAR;

                // set swp for the toolbar
                pswpNew->hwnd = WinWindowFromID (hwnd, FID_TOOLBAR);
                pswpNew->cy   = CY_TOOLBAR;
                pswpNew->y    = pswpClient->y + pswpClient->cy;

                sCount ++;
            }
            return MRESULT (sCount);
        }

    case WM_QUERYFRAMECTLCOUNT:
        {
            SHORT sCount = SHORT (ptb->pfnwpOldFrame(hwnd, msg, mp1, mp2));
            if (ptb->IsShown ())
                sCount ++;
            return MRESULT (sCount);
        }
    }

    return ptb->pfnwpOldFrame (hwnd, msg, mp1, mp2);
}

// ** Show **************************************************************** /*fold00*/

VOID TOOLBAR :: Show (BOOL f)
{
    SWP swp;
    WinQueryWindowPos (hwndFrame, &swp);

    if (f)
    {
        fHidden = FALSE;
        WinSetWindowPos (hwndFrame, NULLHANDLE, 0,0,
                         swp.cx, swp.cy+CY_TOOLBAR, SWP_SIZE | SWP_SHOW);
        WinShowWindow (hwnd, TRUE);
    }
    else
    {
        fHidden = TRUE;
        WinSetWindowPos (hwndFrame, NULLHANDLE, 0,0,
                         swp.cx, swp.cy-CY_TOOLBAR, SWP_SIZE | SWP_SHOW);
        WinShowWindow (hwnd, FALSE);
    }
}

// ** Rebuild ************************************************************* /*fold00*/

VOID TOOLBAR :: Rebuild (ToolbarTemplateEntry atte[])
{
    DisableUpdate ();

    RemoveAllButtons ();

    for (USHORT i = 0; atte[i].idBitmap; i ++)
        if (atte[i].id)
            AddButton (atte[i].id, atte[i].idBitmap, PSZ(NULL),
                       atte[i].fIsHelp);
        else
            AddSeperator ();

    EnableUpdate ();
}

// ************************************************************************
