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

#ifndef _TOOLBAR_H_
#define _TOOLBAR_H_

// ** defines ************************************************************* /*FOLD00*/

#define INCL_PM
#define OS2EMX_PLAIN_CHAR

#include <os2.h>
#include <memory.h>
#include <stdio.h>

typedef class Toolbar TOOLBAR;
typedef TOOLBAR *PTOOLBAR;

#ifndef GETHAB
#define GETHAB hab
extern HAB hab;
#endif

#define TOOLBARBUTTONSMAX    64

#define TBID_SEPERATOR       0

#define TBPOS_FIRST          -1
#define TBPOS_LAST           -2

#define CY_TOOLBAR           28

#define X_TBBUTTONS           3
#define Y_TBBUTTONS           4
#define CX_TBBUTTONS         22
#define CY_TBBUTTONS         22

#define CX_TBSEPERATOR        4

#define PSZ_WCTOOLBAR        "thth.wc.toolbar"

#define FID_TOOLBAR          0x8100

struct ToolbarTemplateEntry
{
    USHORT   id;
    USHORT   idBitmap;
    BOOL     fIsHelp;
};

// ** classdef ************************************************************ /*FOLD00*/

class Toolbar
{
public:
    Toolbar (HWND hwndFrame);
    ~Toolbar (VOID);

    VOID   Show (BOOL f = TRUE);
    VOID   Hide (VOID);
    BOOL   IsShown (VOID);

    SHORT  AddButton (USHORT id, USHORT usBitmapID, PSZ psz = NULL,
                      BOOL fHelp = FALSE);
    SHORT  AddButton (USHORT id, USHORT usBitmapID, SHORT sPos, PSZ psz = NULL,
                      BOOL fHelp = FALSE);

    SHORT  AddSeperator (VOID);
    SHORT  AddSeperator (SHORT sPos);

    VOID   Rebuild (ToolbarTemplateEntry atte[]);

    BOOL   RemoveButton (USHORT id);
    BOOL   RemoveButton (SHORT sPos);
    BOOL   RemoveAllButtons (VOID);

    VOID   EnableButton (USHORT id, BOOL f = TRUE);
    VOID   DisableButton (USHORT id);

    VOID   EnableUpdate (BOOL f = TRUE);
    VOID   DisableUpdate (VOID);

    static PTOOLBAR   QueryToolbar (HWND hwnd);

protected:
    static FNWP   fnwpNewFrame;
    static FNWP   fnwp;

private:
    BOOL    fHidden, fOwnerIsDialog;
    PFNWP   pfnwpOldFrame;
    HWND    hwndFrame, hwndAnchor, hwnd;
    USHORT  aid[TOOLBARBUTTONSMAX], c;
    PSZ     apsz[TOOLBARBUTTONSMAX];

    static PTOOLBAR   ptb;   // FIXME puke!
    static BOOL   fClassRegistered;
};

// ** inline funcs ********************************************************

inline SHORT TOOLBAR :: AddButton (USHORT id, USHORT usBitmapID, PSZ psz,
                                   BOOL fHelp) {
    return AddButton (id, usBitmapID, TBPOS_LAST, psz, fHelp); }

inline SHORT TOOLBAR :: AddSeperator (VOID) {
    return AddButton (TBID_SEPERATOR, 0); }

inline SHORT TOOLBAR :: AddSeperator (SHORT sPos) {
    return AddButton (TBID_SEPERATOR, 0, sPos); }

inline VOID TOOLBAR :: Hide (VOID)      { Show (FALSE); }

inline BOOL TOOLBAR :: IsShown (VOID)   { return !fHidden; }

inline VOID TOOLBAR :: EnableButton (USHORT id, BOOL f = TRUE) {
    WinEnableWindow (WinWindowFromID (hwnd, id), f); }

inline VOID TOOLBAR :: DisableButton (USHORT id) {
    EnableButton (id, FALSE); }

inline VOID TOOLBAR :: EnableUpdate (BOOL f = TRUE) {
    WinEnableWindowUpdate (hwnd, f); }

inline VOID TOOLBAR :: DisableUpdate (VOID) {
    EnableUpdate (FALSE); }

inline BOOL TOOLBAR :: RemoveButton (USHORT)    { return FALSE; }
inline BOOL TOOLBAR :: RemoveButton (SHORT)     { return FALSE; }
inline BOOL TOOLBAR :: RemoveAllButtons (VOID)  { return FALSE; }

inline PTOOLBAR TOOLBAR :: QueryToolbar (HWND) {
    return ptb; } // FIXME puke!

// ************************************************************************
#endif
