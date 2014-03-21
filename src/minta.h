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

#ifndef _MINTA_H_
#define _MINTA_H_

#include "config.h"

#include <io.h>

// this should be provided I thought, but isn't
#define R_OK  4
#define W_OK  2

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include <string>
#include <algo.h>
#include <list.h>
#include <map.h>
#include <vector.h>
#include <iostream.h>
#include <iomanip.h>
#include <fstream.h>

#define OS2EMX_PLAIN_CHAR
#define INCL_PM
#define INCL_DOS
#define INCL_DOSERRORS

#include <os2.h>

#include "version.h"
#include "id.h"

// ** typedefs ************************************************************ /*FOLD00*/

typedef class MP3Display MP3DISPLAY;
typedef MP3DISPLAY *PMP3DISPLAY;

typedef class MP3File MP3;
typedef MP3 *PMP3;

typedef class Helper HELPER;
typedef HELPER *PHELPER;

typedef class Lister LISTER;
typedef LISTER *PLISTER;

typedef class Renamer RENAMER;
typedef RENAMER *PRENAMER;

typedef class GenreList GENLIST;
typedef GENLIST *PGENLIST;

typedef string STRING;

// ** whatever ************************************************************

#define RSTR(id)   PSZ (ResourceString (id))

#define GETHAB     hab
#define GETHWND    hwndMain
#define GETGENLIST (*pgenlist)
#define GETPMP3D   (g_pmp3d)
#define GETMODULE  hmod

#define GETSETTINGS     (GETPMP3D->QuerySettings ())

#ifdef _WARPAMPFIX_
extern BOOL g_fUseSpaces;
#endif

extern HAB         hab;
extern PGENLIST    pgenlist;
extern PMP3DISPLAY g_pmp3d;
extern HMODULE     hmod;
#ifdef _NEWLISTER_
extern PSZ apszInc[];
extern PSZ apszMacroDescs[];
#endif
#ifdef _DEBUGLOG_
extern FILE        *pfileLog;
#endif

#ifdef _TWO_DIGIT_TRACKNUMBERS_
extern BOOL g_fTwoDigitTracknumbers;
#endif

#ifdef _ALLOW_DISABLE_EA_ERROR_
extern CHAR g_fDisableEAError;
#endif

#ifdef _SET_INI_FILE_PATH_
PSZ _QueryProfileName( VOID );
extern CHAR g_pszIniFilePath[_MAX_PATH];
#endif

extern CHAR g_pszMintaDir[_MAX_PATH];

#define MAX_TRACK  255
#define C_MACROS   12

#define PSZ_MP3TYPE   "MP3"

#include "rstring.h"

// ** function protos *****************************************************

VOID     AboutBox (HWND hwnd);
VOID     DisplayError (PSZ pszTitle, PSZ psz, ...);
VOID     DisplayInfo (PSZ pszTitle, PSZ psz, ...);
PSZ      strkspc (PSZ psz);
VOID     Notify (PSZ pszTitle, PSZ psz, ...);

MRESULT EXPENTRY FileDLGProcedure (HWND hwnd, ULONG msg, MPARAM mp1,
                                   MPARAM mp2);
MRESULT EXPENTRY NotifyWP (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

#ifdef _ANIMTEST_
VOID     AnimateMousepointer (VOID);
#endif

#define WinLboxIsSelectedItem(hwndLbox,i) \
    ((LONG)WinSendMsg (hwndLbox, LM_QUERYSELECTION, MPFROMLONG ((i)-1), \
		       (MPARAM)NULL)==(i))

#endif
