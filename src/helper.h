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

#ifndef _HELPER_H_
#define _HELPER_H_

#include "minta.h"
#include "mp3disp.h"

class Helper
{
public:
    Helper (HWND hwnd);
    ~Helper (VOID);
    
    VOID   DisplayPanel (SHORT idPanel);
    BOOL   IsAvailable (VOID);

    VOID   DisplayContents (VOID);
    VOID   DisplayIndex (VOID);
    VOID   DisplayKeysHelp (VOID);

private:
    HWND   hwndHelpInstance;
    BOOL   fHelpEnabled;
};

inline BOOL HELPER :: IsAvailable (VOID)
{
    return (fHelpEnabled);
}

inline VOID HELPER :: DisplayContents (VOID)
{
    WinSendMsg (hwndHelpInstance, HM_HELP_CONTENTS, 0,0);
}

inline VOID HELPER :: DisplayIndex (VOID)
{
    WinSendMsg (hwndHelpInstance, HM_HELP_INDEX, 0,0);
}

inline VOID HELPER :: DisplayKeysHelp (VOID)
{
    WinSendMsg (hwndHelpInstance, HM_KEYS_HELP, 0,0);
}

#endif
