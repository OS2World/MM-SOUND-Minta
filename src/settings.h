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

#ifndef _SETTINGS_H_
#define _SETTINGS_H_

// ** defines & stuff ***************************************************** /*FOLD00*/

#include "minta.h"
#include "../../z-stuff/settings/thth_settings.h"

#ifdef _TOOLBAR_
#include "toolbar.h"
#endif

#ifdef _SET_INI_FILE_PATH_
#define PSZ_PROFILENAME           _QueryProfileName()
#else
#define PSZ_PROFILENAME           "minta.ini"
#endif

// this should be increased every time the format of the proFile changes
#define PROFILEVERSION            6

#define LEN_FONTNAMESIZE          80

#ifdef _PLAYERCOMMAND_
#define MAXLEN_PLAYERCOMMAND      64
#define PSZ_PCFILEMACRO           "$f"
#endif

enum { NOST_CLICKAWAY, NOST_TIMER, NOST_BEEP };

enum
{
    LINC_TITLE, LINC_TIME, LINC_ARTIST, LINC_ALBUM, LINC_YEAR, LINC_GENRE,
    LINC_COMMENT, LINC_FILEPATH, LINC_VERSION, LINC_LAYER, LINC_FREQUENCY,
    LINC_BITRATE, LINC_MODE,
    LINC_HEADER, LINC_TOTALTIME, LINC_MAX,
};

enum
{
    KEEP_TITLE, KEEP_ARTIST, KEEP_ALBUM, KEEP_YEAR, KEEP_GENRE, KEEP_COMMENT,
    KEEP_MAX
};

#define COUNT_PAGES               4
#define PSZ_DEFAULTLANGUAGE       "english"

#ifdef _SPLITNLS_
#define PSZ_DEFAULTLANGUAGEHELP   "english"
#endif

#define LINC_ADDITIONAL (LINC_MAX-LINC_HEADER)

enum { INC_NO, INC_YES };

typedef class Settings SETTINGS;
typedef SETTINGS *PSETTINGS;

// ** classdef ************************************************************ /*FOLD00*/

class Settings : public ththSettings
{
    friend class MP3Display;
    friend class Renamer;

protected:
    USHORT VersionError (VOID);
    USHORT FileNotOpenError (VOID);
    VOID   SelectLanguage (VOID);
    BOOL   ReloadResources (PSZ psz);

    VOID   AdjustSettings (VOID);

    VOID   AdjustButton (HWND hwnd, USHORT id, BOOL f) {
        WinSendDlgItemMsg (hwnd, id, BM_SETCHECK,
                           MPFROMLONG (f), MPFROMLONG (0));
    }

    BOOL   ButtonChecked (HWND hwnd, USHORT id) {
        return BOOL (WinSendDlgItemMsg (hwnd, id, BM_QUERYCHECK, 0, 0));
    }

public:
    Settings (VOID);
    ~Settings (VOID);

    BOOL   Dialog (HWND hwnd = HWND_DESKTOP, BOOL fOnlyLanguage = FALSE);

    // --------------------------------------------------------------------

    PSZ    QueryWorkDir (VOID) { return QueryString (SEI_DIRECTORIESWORK); }

    VOID   SetWorkDir (PSZ psz) {
        CHAR  achDir[_MAX_PATH];
        strcpy (achDir, psz);
        if (achDir[strlen (achDir)-1] == '\\')
            if (achDir[strlen (achDir)-2] != ':')
                achDir[strlen (achDir)-1] = '\0';
        SetString (SEI_DIRECTORIESWORK, achDir);
    }

    VOID   QueryWindowData (SWP *pswp, USHORT us[7]);

    VOID   SetWindowData (SWP *pswp, USHORT us[7]) {
        SetBinary (SEI_SWP, pswp, sizeof (*pswp));
        SetBinary (SEI_US, us, sizeof (us[0])*7);
    }

    PSZ    QueryListfile (VOID) { return QueryString (SEI_LISTFILE); }
    VOID   SetListfile (PSZ psz) { SetString (SEI_LISTFILE, psz); }

    PSZ    QueryGenresfile (VOID) { return QueryString (SEI_GENRESFILE); }
    VOID   SetGenresfile (PSZ psz) { SetString (SEI_GENRESFILE, psz); }

    VOID   ListInclude (USHORT us, BYTE b) { ((BYTE *) QueryBinary (SEI_INCLUDE))[us] = b; }
    BYTE   ListInclude (USHORT us) { return ((BYTE *) QueryBinary (SEI_INCLUDE))[us]; }

    BOOL   NotifyLoad (VOID) { return QueryFlag (SEI_NOTIFYLOAD); }
    BOOL   NotifySave (VOID) { return QueryFlag (SEI_NOTIFYSAVE); }
    BOOL   NotifyRename (VOID) { return QueryFlag (SEI_NOTIFYRENAME); }
    BOOL   NotifyRemove (VOID) { return QueryFlag (SEI_NOTIFYREMOVE); }
    BOOL   NotifyList (VOID) { return QueryFlag (SEI_NOTIFYLIST); }

    VOID   NotifyLoad (BOOL f) { SetFlag (SEI_NOTIFYLOAD, f); }
    VOID   NotifySave (BOOL f) { SetFlag (SEI_NOTIFYSAVE, f); }
    VOID   NotifyRename (BOOL f) { SetFlag (SEI_NOTIFYRENAME, f); }
    VOID   NotifyRemove (BOOL f) { SetFlag (SEI_NOTIFYREMOVE, f); }
    VOID   NotifyList (BOOL f) { SetFlag (SEI_NOTIFYLIST, f); }

    BYTE   QueryNotifyStyle (VOID) { return QueryLong (SEI_NOTIFYSTYLE); }
    VOID   SetNotifyStyle (BYTE b) { SetLong (SEI_NOTIFYSTYLE, LONG (b)); }

    BOOL   AutoSize (VOID) { return QueryFlag (SEI_AUTOSIZE); }
    VOID   AutoSize (BOOL f) { SetFlag (SEI_AUTOSIZE, f); }

    BOOL   OnlyTagged (VOID) { return QueryFlag (SEI_ONLYTAGGED); }
    VOID   OnlyTagged (BOOL f) { SetFlag (SEI_ONLYTAGGED, f); }

    BOOL   FilenameToTitle (VOID) { return QueryFlag (SEI_FILENAMETOTITLE); }
    VOID   FilenameToTitle (BOOL f) { SetFlag (SEI_FILENAMETOTITLE, f); }

    VOID   SetPlayerCommand (PSZ psz) { SetString (SEI_PLAYERCOMMAND, psz); }
    PSZ    QueryPlayerCommand (VOID) { return QueryString (SEI_PLAYERCOMMAND); }

    BOOL   ShowButtons (VOID) { return QueryFlag (SEI_SHOWBUTTONS); }
    VOID   ShowButtons (BOOL f) { SetFlag (SEI_SHOWBUTTONS, f); }

    BOOL   ShowFileinfo (VOID) { return QueryFlag (SEI_SHOWFILEINFO); }
    VOID   ShowFileinfo (BOOL f) { SetFlag (SEI_SHOWFILEINFO, f); }

    COLOR  QueryBackgroundColor (VOID) { return *((COLOR *)QueryBinary (SEI_BACKGROUNDCOLOR)); }
    VOID   SetBackgroundColor (COLOR color) { SetBinary (SEI_BACKGROUNDCOLOR, &color, sizeof (color)); }

    PSZ    QueryFontNameSize (VOID) { return QueryString (SEI_FONTNAMESIZE); }
    VOID   SetFontNameSize (PSZ psz) { SetString (SEI_FONTNAMESIZE, psz); }

    BOOL   KeepTagInfo (VOID) { return QueryFlag (SEI_KEEPTAGINFO); }
    VOID   KeepTagInfo (BOOL f) { SetFlag (SEI_KEEPTAGINFO, f); }

    BOOL   AdjustTrack (VOID) { return QueryFlag (SEI_KEEPADJUSTTRACK); }
    VOID   AdjustTrack (BOOL f) { SetFlag (SEI_KEEPADJUSTTRACK, f); }

    BOOL   OnlyIfMissing (VOID) { return QueryFlag (SEI_KEEPONLYIFMISSING); }
    VOID   OnlyIfMissing (BOOL f) { SetFlag (SEI_KEEPONLYIFMISSING, f); }

    BOOL   Keep (USHORT id) {
        if (id >= KEEP_MAX)
            return FALSE;
        return ((BOOL *) QueryBinary (SEI_KEEP))[id];
    }

    VOID   Keep (USHORT id, BOOL f) {
        if (id >= KEEP_MAX)
            return;
        ((BOOL *) QueryBinary (SEI_KEEP))[id] = f;
    }

    VOID   SetLanguage (PSZ psz) { SetString (SEI_LANGUAGE, psz); }
    PSZ    QueryLanguage (VOID) { return QueryString (SEI_LANGUAGE); }

    BOOL   OnlyReadOnly (VOID) { return QueryFlag (SEI_ONLYREADONLY); }
    VOID   OnlyReadOnly (BOOL f) { SetFlag (SEI_ONLYREADONLY, f); }

    BOOL   NoInvalidMP3Warning (VOID) { return QueryFlag (SEI_NOINVALIDMP3WARNING); }
    VOID   NoInvalidMP3Warning (BOOL f) { SetFlag (SEI_NOINVALIDMP3WARNING, f); }

#ifdef _TOOLBAR_
private:
    BOOL    fToolbar;
    static  ToolbarTemplateEntry atte[];

public:
    ToolbarTemplateEntry *QueryToolbarTemplate (VOID) { return atte; }

    BOOL   ShowToolbar (VOID) { return fToolbar; }
    VOID   ShowToolbar (BOOL f) { fToolbar = f; }
#endif

private:
    static MRESULT EXPENTRY
        DialogProcedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

    static MRESULT EXPENTRY
        Page1Procedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
    static MRESULT EXPENTRY
        Page2Procedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
    static MRESULT EXPENTRY
        Page3Procedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
    static MRESULT EXPENTRY
        Page4Procedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

    BOOL   fAutoLanguage;

    HWND         hwndDlg;
    HWND         hwndPage[COUNT_PAGES];

    static PSZ   pszPageTab[COUNT_PAGES];
};

// ************************************************************************
#endif
