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

#ifndef _MP3DISP_H_
#define _MP3DISP_H_

#include "minta.h"
#include "helper.h"
#include "settings.h"
#include "finddir.h"
#include "status.h"

#ifdef _TOOLBAR_
#include "toolbar.h"
#endif

#include <process.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_AUTONAMELEN   31

// ** classdef ************************************************************ /*FOLD00*/

class MP3Display
{
    friend class Lister;
    friend class Renamer;

public:
    MP3Display (PSZ psz = NULL);

    BOOL   FilesInList (VOID);
    ULONG  CountFilesInList (VOID);

    PSETTINGS   QuerySettings (VOID);

private:
    BOOL   OpenFiles (VOID);
    ULONG  OpenFiles (PSZ psz);

    VOID   SaveAll (VOID);
    VOID   RenameAll (VOID);
    VOID   RemoveAll (VOID);

#ifdef _STATUSDISPLAY_
    static VOID   SaveAllThread (PVOID pta);
#endif

    LONG   AutoOpenFiles (PSZ psz);
    LONG   ProcessDirectory (PSZ psz);

    VOID   AddFile (PSZ psz);
    VOID   RemoveFile (PSZ psz = NULL);
    VOID   RemoveAllFiles (VOID);

    VOID   Refresh (VOID);
    VOID   RefreshFileList (VOID);
    VOID   RefreshTagGroup (VOID);
    VOID   RefreshFileGroup (VOID);
    VOID   RefreshButtons (VOID);

    VOID   EnableSave (BOOL f = TRUE);
    VOID   EnableSaveAll (BOOL f = TRUE);
    VOID   EnableSaveNext (BOOL f = TRUE);
    VOID   EnableSavePrev (BOOL f = TRUE);
    VOID   EnableRemove (BOOL f = TRUE);
    VOID   EnableRemoveAll (BOOL f = TRUE);
    VOID   EnableList (BOOL f = TRUE);
    VOID   EnableDeleteFromList (BOOL f = TRUE);
    VOID   EnableDeleteAllFromList (BOOL f = TRUE);
    VOID   EnableRenameAll (BOOL f = TRUE);
    VOID   EnableAutoopen (BOOL f = TRUE);
    VOID   EnableHelp (BOOL f = TRUE);
    VOID   EnableCut (BOOL f = TRUE);
    VOID   EnableCopy (BOOL f = TRUE);
    VOID   EnablePaste (BOOL f = TRUE);

    VOID   ShowButtons (BOOL f = TRUE);
#ifdef _SHOWFILEINFO_
    VOID   ShowFileinfo (BOOL f = TRUE);
#endif

    VOID   NotificationAutoOpen (ULONG l);

    VOID   SetGenre (USHORT us);

    VOID   AdjustFilelistTitle (VOID);
    VOID   SelectFirstFile (VOID);

    VOID   QueryFile (PCHAR psz, USHORT us);
    VOID   QueryFile (PCHAR psz, USHORT us, ULONG ulPos);

    VOID   AdjustCurrent (BOOL fAlwaysChange);
    VOID   SaveCurrent (BOOL fAlwaysChange = TRUE);

    HWND   QueryHWNDMenu (VOID);

    VOID   SetMP3 (PMP3 pmp3);
    PMP3   QueryMP3 (VOID);

#ifdef _PLAYERCOMMAND_
    VOID   LaunchPlayer (VOID);
#endif

#ifdef _TOOLBAR_
    VOID   ShowToolbar (BOOL f) {
        WinCheckMenuItem (QueryHWNDMenu (), WID_PB_SHOWTOOLBAR, f);
        if (ptb)
            ptb->Show (f);
    }
#endif

    static MRESULT EXPENTRY
        NotifyWP (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

    static MRESULT EXPENTRY
        WindowProcedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

#ifdef _STATUSDISPLAY_
    static MRESULT EXPENTRY
        HeavyDutyWP (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
#endif

/*    static MRESULT EXPENTRY
        LocalDDLProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2); */

    PSETTINGS  pset;
    PHELPER    phelp;
    PLISTER    plist;
    PRENAMER   pren;
    PFINDDIR   pfd;
    PMP3       pmp3;
    HWND       hwnd;
    ULONG      cFiles, cTrack;
    PSZ        pszOpenAtStart;

    PFNWP      pfnwp;

#ifdef _STATUSDISPLAY_
    PSTATD     pstatd;
    PULONG     pc;
    BOOL       fBreak;
#endif

    CHAR   achDir[_MAX_PATH];

    BOOL       fNoKeep;

#ifdef _TOOLBAR_
    class Toolbar  *ptb;
#endif
};

#include "mp3.h"
#include "lister.h"
#include "renamer.h"

// ** inline funcs ******************************************************** /*FOLD00*/

inline VOID MP3DISPLAY :: SetMP3 (PMP3 pmp3) { this->pmp3 = pmp3; }
inline PMP3 MP3DISPLAY :: QueryMP3 (VOID)    { return pmp3; }

inline VOID MP3DISPLAY :: RemoveAllFiles (VOID)
{
    if (! hwnd)
        return;

    if (QueryMP3 ())
        delete QueryMP3 ();

    WinSendDlgItemMsg (hwnd, WID_DDL_FILES, LM_DELETEALL, NULL,NULL);
    cFiles = 0L;
    Refresh ();
}

// ------------------------------------------------------------------------

inline BOOL MP3DISPLAY :: FilesInList (VOID) { return BOOL (cFiles > 0); }
inline ULONG MP3DISPLAY :: CountFilesInList (VOID) { return ULONG (cFiles); }

// ------------------------------------------------------------------------

inline VOID MP3DISPLAY :: SelectFirstFile (VOID)
{
    WinSendDlgItemMsg (hwnd, WID_DDL_FILES, LM_SELECTITEM,
                       MPFROMLONG (0L), MPFROMLONG (TRUE));
    WinSendDlgItemMsg (hwnd, WID_DDL_FILES, CBM_SHOWLIST, FALSE, 0);
    // NOTE: the above will automatically set the MP3 file (this->pmp3)
    //       via the LN_SELECT switch in the Win.Proc. and refresh
    //       the display/buttons
}

// ------------------------------------------------------------------------

inline HWND MP3DISPLAY :: QueryHWNDMenu (VOID)
{
    return WinWindowFromID (hwnd, FID_MENU);
}

// ------------------------------------------------------------------------

inline VOID MP3DISPLAY :: EnableSave (BOOL f)
{
    WinEnableWindow (WinWindowFromID (hwnd, WID_PB_SAVE), f);
    WinEnableMenuItem (QueryHWNDMenu (), WID_PB_SAVE, f);
}

inline VOID MP3DISPLAY :: EnableSaveAll (BOOL f)
{
    WinEnableWindow (WinWindowFromID (hwnd, WID_PB_SAVEALL), f);
    WinEnableMenuItem (QueryHWNDMenu (), WID_PB_SAVEALL, f);
}

inline VOID MP3DISPLAY :: EnableSaveNext (BOOL f)
{
    //    WinEnableWindow (WinWindowFromID (hwnd, WID_PB_), f);
    WinEnableMenuItem (QueryHWNDMenu (), WID_PB_SAVENEXT, f);
}

inline VOID MP3DISPLAY :: EnableSavePrev (BOOL f)
{
    //    WinEnableWindow (WinWindowFromID (hwnd, WID_PB_), f);
    WinEnableMenuItem (QueryHWNDMenu (), WID_PB_SAVEPREV, f);
}

inline VOID MP3DISPLAY :: EnableRemove (BOOL f)
{
    WinEnableWindow (WinWindowFromID (hwnd, WID_PB_REMOVE), f);
    WinEnableMenuItem (QueryHWNDMenu (), WID_PB_REMOVE, f);
}

inline VOID MP3DISPLAY :: EnableRemoveAll (BOOL f)
{
    WinEnableWindow (WinWindowFromID (hwnd, WID_PB_REMOVEALL), f);
    WinEnableMenuItem (QueryHWNDMenu (), WID_PB_REMOVEALL, f);
}

inline VOID MP3DISPLAY :: EnableList (BOOL f)
{
    WinEnableWindow (WinWindowFromID (hwnd, WID_PB_LIST), f);
    WinEnableMenuItem (QueryHWNDMenu (), WID_PB_LIST, f);
}

inline VOID MP3DISPLAY :: EnableDeleteFromList (BOOL f)
{
    //    WinEnableWindow (WinWindowFromID (hwnd, WID_PB_), f);
    WinEnableMenuItem (QueryHWNDMenu (), WID_PB_DELETEFROMLIST, f);
}

inline VOID MP3DISPLAY :: EnableDeleteAllFromList (BOOL f)
{
    //    WinEnableWindow (WinWindowFromID (hwnd, WID_PB_), f);
    WinEnableMenuItem (QueryHWNDMenu (), WID_PB_DELETEALLFROMLIST, f);
}

inline VOID MP3DISPLAY :: EnableRenameAll (BOOL f)
{
    //    WinEnableWindow (WinWindowFromID (hwnd, WID_PB_), f);
    WinEnableMenuItem (QueryHWNDMenu (), WID_PB_RENAMEALL, f);
}

inline VOID MP3DISPLAY :: EnableAutoopen (BOOL f)
{
    //    WinEnableWindow (WinWindowFromID (hwnd, WID_PB_), f);
    WinEnableMenuItem (QueryHWNDMenu (), WID_PB_AUTOOPEN, f);
}

inline VOID MP3DISPLAY :: EnableCut (BOOL f) {
    WinEnableMenuItem (QueryHWNDMenu (), WID_PB_CUTTAG, f); }

inline VOID MP3DISPLAY :: EnableCopy (BOOL f) {
    WinEnableMenuItem (QueryHWNDMenu (), WID_PB_COPYTAG, f); }

inline VOID MP3DISPLAY :: EnablePaste (BOOL f) {
    WinEnableMenuItem (QueryHWNDMenu (), WID_PB_PASTETAG, f); }

inline VOID MP3DISPLAY :: EnableHelp (BOOL f)
{
    WinEnableWindow (WinWindowFromID (hwnd, WID_PB_HELP), f);
    WinEnableMenuItem (QueryHWNDMenu (), HM_HELP_CONTENTS, f);
    WinEnableMenuItem (QueryHWNDMenu (), HM_GENERAL_HELP, f);
}

inline PSETTINGS MP3DISPLAY :: QuerySettings (VOID) { return pset; }

// ************************************************************************
#endif
