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

#include "settings.h"

#include "../../z-stuff/settings/thth_settings.cpp"

// ** class vars ********************************************************** /*fold00*/

PSZ SETTINGS::pszPageTab[COUNT_PAGES];

#ifdef _TOOLBAR_
ToolbarTemplateEntry SETTINGS::atte[] =
{
    { WID_PB_FILES, 1, FALSE },
    { WID_PB_AUTOOPEN, 2, FALSE },
    { 0, 1, FALSE },
    { WID_PB_DELETEFROMLIST, 3, FALSE },
    { WID_PB_DELETEALLFROMLIST, 4, FALSE },
    { 0, 1, FALSE },
    { WID_PB_RENAMEALL,  6, FALSE },
    { WID_PB_LIST, 5, FALSE },
    { WID_PB_SETTINGS, 7, FALSE },
    { 0, 1, FALSE },
    { WID_PB_SAVE, 8, FALSE },
    { WID_PB_SAVEPREV, 10, FALSE },
    { WID_PB_SAVENEXT, 9, FALSE },
    { WID_PB_SAVEALL, 11, FALSE },
    { 0, 1, FALSE },
    { WID_PB_REMOVE, 12, FALSE },
    { WID_PB_REMOVEALL, 13, FALSE },
    { 0, 1, FALSE },
    { WID_PB_PLAY, 14, FALSE },
    { WID_PB_SHOWBUTTONS, 15, FALSE },
    { WID_PB_SHOWFILEINFO, 16, FALSE },
    { 0, 1, FALSE },
    { WID_PB_ABOUT, 17, FALSE },
    { WID_PB_HELP, 18, TRUE },
    { 0, 1, FALSE },
    { WID_PB_PREV, 19, FALSE },
    { WID_PB_NEXT, 20, FALSE },
    { 0, 0, 0},
};
#endif

// ** Settings ************************************************************ /*fold00*/

BYTE abLIncDef[LINC_MAX] =
{
    INC_YES, INC_YES, INC_YES, INC_YES, INC_YES, INC_YES, INC_YES, INC_YES,
};

#ifdef _CUSTOMBUTTONS_
class ButtonTemplate {
    USHORT x[2], y[2], cx[2], cy[2];
    USHORT cmd;
    BOOL   fHelp;
};

class ButtonTemplate *apbt[] =
{
    new ButtonTemplate(310,162, 66,15, 0,0, 0,0, WID_PB_FILES),
    new ButtonTemplate(310,140, 66,15

        PUSHBUTTON      "~Open...", WID_PB_FILES, 310, 162, 66, 15
        PUSHBUTTON      "~Save", WID_PB_SAVE, 310, 140, 66, 15
        PUSHBUTTON      "Save all", WID_PB_SAVEALL, 310, 124, 66, 15
        PUSHBUTTON      "~Remove", WID_PB_REMOVE, 310, 102, 66, 15
        PUSHBUTTON      "Remove all", WID_PB_REMOVEALL, 310, 86, 66, 15
        PUSHBUTTON      "~List...", WID_PB_LIST, 310, 64, 66, 15
        PUSHBUTTON      "~About", WID_PB_ABOUT, 310, 42, 66, 15
        PUSHBUTTON      "E~xit", WID_PB_EXIT, 310, 4, 66, 15
        PUSHBUTTON      "Help", WID_PB_HELP, 310, 26, 66, 15, BS_HELP | 
                        BS_NOPOINTERFOCUS
};



USHORT ausButton2Cmd[C_BUTTONS] = {
    WID_PB_FILES, WID_PB_SAVE, WID_PB_SAVEALL, WID_PB_REMOVE,
    WID_PB_REMOVEALL, WID_PB_LIST, WID_PB_ABOUT, WID_PB_EXIT, WID_PB_HELP
};
#endif

BOOL fKeepDef[KEEP_MAX] =
{
    FALSE, TRUE, TRUE, TRUE, TRUE, FALSE,
};

SWP swpDef;
USHORT ausDef[7];
COLOR colorBGDef = 0x00e0c080;

PTHTH_SE apse[] =
{
    new THTH_SES (SEI_DIRECTORIESWORK, "Directories", "Work", ""),

    new THTH_SEF (SEI_FILENAMETOTITLE, "Extras", "FilenameToTitle", TRUE),
    new THTH_SES (SEI_GENRESFILE,   "Extras", "Genresfile", "genres.txt"),
    new THTH_SES (SEI_LANGUAGE,     "Extras", "Language", PSZ_DEFAULTLANGUAGE),
#ifdef _SPLITNLS_
    new THTH_SES (SEI_LANGUAGEHELP, "Extras", "LanguageHelp", PSZ_DEFAULTLANGUAGEHELP),
#endif
    new THTH_SEF (SEI_CUSTOMFILEDIALOG,  "Extras", "CustomFileDialog", TRUE),
    new THTH_SEF (SEI_NOINVALIDMP3WARNING, "Extras", "NoInvalidMP3Warning", FALSE),
    new THTH_SEF (SEI_ONLYREADONLY, "Extras", "OnlyReadonly", FALSE),
    new THTH_SES (SEI_PLAYERCOMMAND,"Extras", "Playercommand", ""),
    new THTH_SEF (SEI_SHOWBUTTONS,  "Extras", "ShowButtons", TRUE),
    new THTH_SEF (SEI_SHOWFILEINFO, "Extras", "ShowFileinfo", TRUE),
    new THTH_SEF (SEI_SHOWTOOLBAR, "Extras", "ShowToolbar", TRUE),
#ifdef _CUSTOMBUTTONS_
    new THTH_SEB (SEI_BUTTONS2CMD, "Extras", "Buttons2Cmd", &ausButtons2Cmd, sizeof (USHORT)*C_BUTTONS), // FIXME will the sizeof work?
#endif

    new THTH_SEB (SEI_KEEP, "Keep", "Info", &fKeepDef, sizeof (BOOL)*KEEP_MAX), // FIXME will the sizeof work?
    new THTH_SEF (SEI_KEEPADJUSTTRACK,   "Keep", "AdjustTrack", TRUE),
    new THTH_SEF (SEI_KEEPONLYIFMISSING, "Keep", "OnlyIfMissing", TRUE),
    new THTH_SEF (SEI_KEEPTAGINFO,       "Keep", "TagInfo", FALSE),

    new THTH_SEF (SEI_AUTOSIZE,   "List", "AutoSize", TRUE),
    new THTH_SEB (SEI_INCLUDE,    "List", "Include", &abLIncDef, sizeof (BYTE)*LINC_MAX), // FIXME will the sizeof work?
    new THTH_SES (SEI_LISTFILE,   "List", "File", "mp3list.txt"),
    new THTH_SEF (SEI_ONLYTAGGED, "List", "OnlyTagged", FALSE),

    new THTH_SEF (SEI_NOTIFYLIST,   "Notify", "List", TRUE),
    new THTH_SEF (SEI_NOTIFYLOAD,   "Notify", "Load", TRUE),
    new THTH_SEF (SEI_NOTIFYREMOVE, "Notify", "Remove", TRUE),
    new THTH_SEF (SEI_NOTIFYRENAME, "Notify", "Rename", TRUE),
    new THTH_SEF (SEI_NOTIFYSAVE,   "Notify", "Save", TRUE),
    new THTH_SEL (SEI_NOTIFYSTYLE,  "Notify", "Style", NOST_TIMER),

    new THTH_SEB (SEI_BACKGROUNDCOLOR, "Window", "BackgroundColor", &colorBGDef, sizeof (colorBGDef)),
    new THTH_SES (SEI_FONTNAMESIZE, "Window", "FontNameSize", "10.Helv"),
    new THTH_SEB (SEI_SWP, "Window", "SWP", &swpDef, sizeof (swpDef)),
    new THTH_SEB (SEI_US, "Window", "US", &ausDef, sizeof (ausDef)),

    new THTH_SES (SEI_RENAMETEMPLATE, "Rename", "Template", "$T"),
    new THTH_SEF (SEI_RENAMELIMITLENGTH, "Rename", "LimitLength", FALSE),
    new THTH_SEL (SEI_RENAMELENGTH, "Rename", "Length", 31),
    new THTH_SEF (SEI_RENAMEREPLACESPACES, "Rename", "ReplaceSpaces", TRUE),

    NULL,
};

// ------------------------------------------------------------------------

SETTINGS :: Settings (VOID) : ththSettings (apse, PSZ_PROFILENAME,
                                            PROFILEVERSION)
{
    ReloadResources (QueryLanguage ());

    if (Error () == 1)
    {
        FileNotOpenError ();
        ReloadResources (QueryLanguage ());
    }
    else if (Error () == 2)
    {
        VersionError ();
        ReloadResources (QueryLanguage ());
    }
    //DisplayError( "DEBUG", "%s %s %d", PSZ_PROFILENAME, QueryProfileName(), Error() );
}

// ** ~Settings *********************************************************** /*fold00*/

SETTINGS :: ~Settings (VOID)
{
    if (hmod)
        DosFreeModule (hmod);

    this->ththSettings::~ththSettings ();
}

// ** Dialog ************************************************************** /*fold00*/

// FIXME YUKKI! YUKKI!! YUKKI!!! But I'm too lazy to do it better now :-)
HWND g_hwndSettingsDialog = NULL;

BOOL SETTINGS :: Dialog (HWND hwndOwner, BOOL fOnlyLanguage)
{
    fAutoLanguage = fOnlyLanguage;

    hwndDlg = WinLoadDlg (HWND_DESKTOP, hwndOwner, PFNWP (DialogProcedure),
                          GETMODULE, ID_DLG_SETTINGS, this);
    // FIXME YUKKI! YUKKI!! YUKKI!!! But I'm too lazy to do it better now :-)
    g_hwndSettingsDialog = hwndDlg;

    if (fAutoLanguage)
    {
        WinEnableWindow (WinWindowFromID (hwndDlg, WID_PB_HELP), FALSE);
        WinEnableWindow (WinWindowFromID (hwndDlg, WID_PB_UNDO), FALSE);
    }

    HWND   hwndNB = WinWindowFromID (hwndDlg, WID_NB_SETTINGS);

    // set notebook background color
    WinSendMsg (hwndNB, BKM_SETNOTEBOOKCOLORS,
                MPFROMLONG (SYSCLR_DIALOGBACKGROUND),
                MPFROMSHORT (BKA_BACKGROUNDPAGECOLORINDEX));

    // set tab dimensions
    WinSendMsg (hwndNB, BKM_SETDIMENSIONS,
                MPFROM2SHORT (80, 25), MPFROMSHORT (BKA_MAJORTAB));

    ULONG   idPage[COUNT_PAGES];
    USHORT  i, cPages;

    if (fOnlyLanguage)
    {
        cPages = 1;

        idPage[0] = (ULONG)
            WinSendMsg (hwndNB, BKM_INSERTPAGE, 0L,
                        MPFROM2SHORT (BKA_MAJOR | BKA_AUTOPAGESIZE,
                                      BKA_LAST));
        WinSendMsg (hwndNB, BKM_SETTABTEXT, MPFROMLONG (idPage[0]),
                    MPFROMP (pszPageTab[COUNT_PAGES-1]));

        hwndPage[0] = WinLoadDlg (hwndNB, hwndNB, (PFNWP) Page4Procedure,
                                  GETMODULE, ID_DLG_SETTINGSPAGE4, this);
        WinSetAccelTable (hab, WinLoadAccelTable (hab, GETMODULE,
                                                  ID_ACCELTABLE_SETTINGS),
                          hwndPage[0]);
    }
    else
    {
        cPages = COUNT_PAGES;

        // insert empty pages
        for (i = 0; i < cPages; i++)
        {
            idPage[i] = (ULONG)
                WinSendMsg (hwndNB, BKM_INSERTPAGE, 0L,
                            MPFROM2SHORT (BKA_MAJOR | BKA_AUTOPAGESIZE,
                                          BKA_LAST));
            WinSendMsg (hwndNB, BKM_SETTABTEXT,
                        MPFROMLONG (idPage[i]), MPFROMP (pszPageTab[i]));
        }

        // open and assign dialogs to pages
        hwndPage[0] = WinLoadDlg (hwndNB, hwndNB, (PFNWP) Page1Procedure,
                                  GETMODULE, ID_DLG_SETTINGSPAGE1, this);
        WinSetAccelTable (hab, WinLoadAccelTable (hab, GETMODULE,
                                                  ID_ACCELTABLE_SETTINGS),
                          hwndPage[0]);
        hwndPage[1] = WinLoadDlg (hwndNB, hwndNB, (PFNWP) Page2Procedure,
                                  GETMODULE, ID_DLG_SETTINGSPAGE2, this);
        WinSetAccelTable (hab, WinLoadAccelTable (hab, GETMODULE,
                                                  ID_ACCELTABLE_SETTINGS),
                          hwndPage[1]);
        hwndPage[2] = WinLoadDlg (hwndNB, hwndNB, (PFNWP) Page3Procedure,
                                  GETMODULE, ID_DLG_SETTINGSPAGE3, this);
        WinSetAccelTable (hab, WinLoadAccelTable (hab, GETMODULE,
                                                  ID_ACCELTABLE_SETTINGS),
                          hwndPage[2]);
        hwndPage[3] = WinLoadDlg (hwndNB, hwndNB, (PFNWP) Page4Procedure,
                                  GETMODULE, ID_DLG_SETTINGSPAGE4, this);
        WinSetAccelTable (hab, WinLoadAccelTable (hab, GETMODULE,
                                                  ID_ACCELTABLE_SETTINGS),
                          hwndPage[3]);
    }

    // combine dlg-handle and page ids
    for (i = 0; i < cPages; i++)
        WinSendMsg (hwndNB, BKM_SETPAGEWINDOWHWND,
                    MPFROMLONG (idPage[i]), MPFROMHWND (hwndPage[i]));

    WinSetFocus (WinWindowFromID (hwndDlg, WID_PB_OK), TRUE);

    WinSetAccelTable (hab, WinLoadAccelTable (hab, GETMODULE,
                                              ID_ACCELTABLE_SETTINGS),
                      hwndDlg);

    // the "main loop"
    BOOL f = WinProcessDlg (hwndDlg);
    WinDestroyWindow (hwndDlg);

    // clean up
    for (i = 0; i < COUNT_PAGES; i++)
        hwndPage[i] = NULL;

    hwndDlg = NULLHANDLE;
    fAutoLanguage = FALSE;
    return (f);
}

// ** DialogProcedure ***************************************************** /*FOLD00*/

MRESULT EXPENTRY
SETTINGS :: DialogProcedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    static PSETTINGS   pset = NULL;

    switch (msg)
    {
    case WM_INITDLG:
        pset = PSETTINGS (mp2);
        return MRESULT (FALSE);

    case WM_COMMAND:
        switch (SHORT1FROMMP (mp1))
        {
        case WID_PB_OK:
            WinSendMsg (hwnd, WM_CLOSE, 0,0);
            break;

        case WID_PB_UNDO:
            {
                ULONG  id = (ULONG)
                    WinSendDlgItemMsg (hwnd, WID_NB_SETTINGS,
                                       BKM_QUERYPAGEID, 0,
                                       MPFROM2SHORT (BKA_TOP, 0));
                if (id)
                {
                    HWND   hwndPage = (HWND)
                        WinSendDlgItemMsg (hwnd, WID_NB_SETTINGS,
                                           BKM_QUERYPAGEWINDOWHWND,
                                           MPFROMLONG (id), 0);
                    WinSendMsg (hwndPage, UM_SETTINGS2DIALOG, 0,0);
                }
            }
            break;

        case DID_CANCEL:
            {
                // Undo stuff on all notebook pages:
                HWND hwndPage;

                // Get ID of first notebook page.
                ULONG id =
                    ULONG( WinSendDlgItemMsg( hwnd, WID_NB_SETTINGS,
                                              BKM_QUERYPAGEID, 0,
                                              MPFROM2SHORT( BKA_FIRST, 0 ) ) );
                if( id ) {
                    hwndPage =
                        HWND( WinSendDlgItemMsg( hwnd, WID_NB_SETTINGS,
                                                 BKM_QUERYPAGEWINDOWHWND,
                                                 MPFROMLONG( id ), 0 ) );
                    WinSendMsg( hwndPage, UM_SETTINGS2DIALOG, 0,0 );
                }

                while( id ) {
                    // Get ID of next notebook page.
                    if( ( id =
                          ULONG( WinSendDlgItemMsg( hwnd, WID_NB_SETTINGS,
                                                    BKM_QUERYPAGEID,
                                                    MPFROMLONG( id ),
                                                    MPFROM2SHORT( BKA_NEXT, 0 )
                                                  ) ) ) ) {
                        hwndPage =
                            HWND( WinSendDlgItemMsg( hwnd, WID_NB_SETTINGS,
                                                     BKM_QUERYPAGEWINDOWHWND,
                                                     MPFROMLONG( id ), 0 ) );
                        WinSendMsg( hwndPage, UM_SETTINGS2DIALOG, 0,0 );
                    }
                }
                WinSendMsg( hwnd, WM_CLOSE, 0,0 );
            }
            break;
        }
        return MRESULT (FALSE);
    }

    return WinDefDlgProc (hwnd, msg, mp1, mp2);
}

// ** Page1Procedure ****************************************************** /*fold00*/

MRESULT EXPENTRY
SETTINGS :: Page1Procedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    static PSETTINGS   pset = NULL;

    switch (msg)
    {
    case WM_INITDLG:
        pset = PSETTINGS (mp2);
        WinSendMsg (hwnd, UM_SETTINGS2DIALOG, 0,0);
        return MRESULT (FALSE);

    case WM_COMMAND:
        if( SHORT1FROMMP( mp1 ) == DID_CANCEL )
            WinPostMsg( g_hwndSettingsDialog, msg, mp1, mp2 );
        return MRESULT( FALSE );

    case UM_SETTINGS2DIALOG:
        pset->AdjustButton (hwnd, WID_CB_NOTIFYLOAD, pset->NotifyLoad ());
        pset->AdjustButton (hwnd, WID_CB_NOTIFYSAVE, pset->NotifySave ());
        pset->AdjustButton (hwnd, WID_CB_NOTIFYRENAME, pset->NotifyRename ());
        pset->AdjustButton (hwnd, WID_CB_NOTIFYREMOVE, pset->NotifyRemove ());
        pset->AdjustButton (hwnd, WID_CB_NOTIFYLIST, pset->NotifyList ());

        switch (pset->QueryNotifyStyle ())
        {
        case NOST_CLICKAWAY:
            WinSendDlgItemMsg (hwnd, WID_RB_CLICKAWAY, BM_CLICK,
                               MPFROMSHORT(TRUE), 0);
            break;
        case NOST_BEEP:
            WinSendDlgItemMsg (hwnd, WID_RB_BEEP, BM_CLICK,
                               MPFROMSHORT(TRUE), 0);
            break;
        default:
            WinSendDlgItemMsg (hwnd, WID_RB_TIMER, BM_CLICK,
                               MPFROMSHORT(TRUE), 0);
            break;
        }
        return MRESULT (FALSE);

    case WM_DESTROY:
        pset->NotifyLoad (pset->ButtonChecked (hwnd, WID_CB_NOTIFYLOAD));
        pset->NotifySave (pset->ButtonChecked (hwnd, WID_CB_NOTIFYSAVE));
        pset->NotifyRename (pset->ButtonChecked (hwnd, WID_CB_NOTIFYRENAME));
        pset->NotifyRemove (pset->ButtonChecked (hwnd, WID_CB_NOTIFYREMOVE));
        pset->NotifyList (pset->ButtonChecked (hwnd, WID_CB_NOTIFYLIST));

        if (WinSendMsg (WinWindowFromID (hwnd, WID_RB_CLICKAWAY),
                        BM_QUERYCHECK, 0,0))
            pset->SetNotifyStyle (NOST_CLICKAWAY);
        else if (WinSendMsg (WinWindowFromID (hwnd, WID_RB_BEEP),
                             BM_QUERYCHECK, 0,0))
            pset->SetNotifyStyle (NOST_BEEP);
        else
            pset->SetNotifyStyle (NOST_TIMER);
        return MRESULT (FALSE);
    }

    return WinDefDlgProc (hwnd, msg, mp1, mp2);
}

// ** Page2Procedure ****************************************************** /*fold00*/

MRESULT EXPENTRY
SETTINGS :: Page2Procedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    static USHORT  idEnable[] =
    {
        WID_CB_KEEPTITLE, WID_CB_KEEPARTIST, WID_CB_KEEPALBUM,
        WID_CB_KEEPYEAR, WID_CB_KEEPGENRE, WID_CB_KEEPCOMMENT,
        WID_CB_KEEPTRACK, WID_CB_ADJUSTTRACK, WID_CB_ONLYIFMISSING,
        0
    };
    static PSETTINGS   pset = NULL;

    switch (msg)
    {
    case WM_INITDLG:
        pset = PSETTINGS (mp2);
        WinSendMsg (hwnd, UM_SETTINGS2DIALOG, 0,0);
        return MRESULT (FALSE);

    case WM_COMMAND:
        if( SHORT1FROMMP( mp1 ) == DID_CANCEL )
            WinPostMsg( g_hwndSettingsDialog, msg, mp1, mp2 );
        return MRESULT( FALSE );

    case WM_CONTROL:
        switch (SHORT1FROMMP (mp1))
        {
        case WID_CB_KEEP:
            if (WinSendDlgItemMsg (hwnd, WID_CB_KEEP, BM_QUERYCHECK, 0, 0)) {
                for (USHORT i = 0; idEnable[i]; i++)
                    WinEnableWindow (WinWindowFromID (hwnd, idEnable[i]),
                                     TRUE);
            }
            else {
                for (USHORT i = 0; idEnable[i]; i++)
                    WinEnableWindow (WinWindowFromID (hwnd, idEnable[i]),
                                     FALSE);
            }
            break;

        }
        return MRESULT (FALSE);

    case UM_SETTINGS2DIALOG:
        pset->AdjustButton (hwnd, WID_CB_KEEPTITLE, pset->Keep (KEEP_TITLE));
        pset->AdjustButton (hwnd, WID_CB_KEEPARTIST, pset->Keep (KEEP_ARTIST));
        pset->AdjustButton (hwnd, WID_CB_KEEPALBUM, pset->Keep (KEEP_ALBUM));
        pset->AdjustButton (hwnd, WID_CB_KEEPGENRE, pset->Keep (KEEP_GENRE));
        pset->AdjustButton (hwnd, WID_CB_KEEPCOMMENT, pset->Keep (KEEP_COMMENT));
        pset->AdjustButton (hwnd, WID_CB_KEEPYEAR, pset->Keep (KEEP_YEAR));

        pset->AdjustButton (hwnd, WID_CB_ADJUSTTRACK, pset->AdjustTrack ());
        pset->AdjustButton (hwnd, WID_CB_ONLYIFMISSING, pset->OnlyIfMissing ());

        // set the "wrong" button state and "click" the button to revert it
        // so a WM_CONTROL is send and the other buttons are en-/disabled
        pset->AdjustButton (hwnd, WID_CB_KEEP, !pset->KeepTagInfo ());
        WinSendDlgItemMsg (hwnd, WID_CB_KEEP, BM_CLICK, MPFROMSHORT(TRUE), 0);
        return MRESULT (FALSE);

    case WM_DESTROY:
        pset->Keep (KEEP_TITLE, pset->ButtonChecked (hwnd, WID_CB_KEEPTITLE));
        pset->Keep (KEEP_ARTIST, pset->ButtonChecked (hwnd, WID_CB_KEEPARTIST));        
        pset->Keep (KEEP_ALBUM, pset->ButtonChecked (hwnd, WID_CB_KEEPALBUM));
        pset->Keep (KEEP_GENRE, pset->ButtonChecked (hwnd, WID_CB_KEEPGENRE));
        pset->Keep (KEEP_COMMENT, pset->ButtonChecked (hwnd, WID_CB_KEEPCOMMENT));
        pset->Keep (KEEP_YEAR, pset->ButtonChecked (hwnd, WID_CB_KEEPYEAR));

        pset->KeepTagInfo (pset->ButtonChecked (hwnd, WID_CB_KEEP));
        pset->AdjustTrack (pset->ButtonChecked (hwnd, WID_CB_ADJUSTTRACK));
        pset->OnlyIfMissing (pset->ButtonChecked (hwnd, WID_CB_ONLYIFMISSING));
        return MRESULT (FALSE);
    }

    return WinDefDlgProc (hwnd, msg, mp1, mp2);
}

// ** Page3Procedure ****************************************************** /*fold00*/

MRESULT EXPENTRY
SETTINGS :: Page3Procedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    static PSETTINGS   pset = NULL;

    switch (msg)
    {
    case WM_INITDLG:
        pset = PSETTINGS (mp2);
        WinSendMsg (hwnd, UM_SETTINGS2DIALOG, 0,0);
        return MRESULT (FALSE);

    case WM_COMMAND:
        if( SHORT1FROMMP( mp1 ) == DID_CANCEL )
            WinPostMsg( g_hwndSettingsDialog, msg, mp1, mp2 );
        return MRESULT( FALSE );

    case UM_SETTINGS2DIALOG:
        pset->AdjustButton (hwnd, WID_CB_FILENAMETOTITLE,
                            pset->FilenameToTitle ());
        pset->AdjustButton (hwnd, WID_CB_CUSTOMFILEDIALOG,
                            pset->QueryFlag (SEI_CUSTOMFILEDIALOG));
        pset->AdjustButton (hwnd, WID_CB_NOINVALIDMP3WARNING,
                            pset->NoInvalidMP3Warning ());
        pset->AdjustButton (hwnd, WID_CB_ONLYREADONLY,
                            pset->OnlyReadOnly ());
        WinSetWindowText (WinWindowFromID (hwnd, WID_E_GENRESFILE),
                          pset->QueryGenresfile ());
        WinSetWindowText (WinWindowFromID (hwnd, WID_E_PLAYERCOMMAND),
                          pset->QueryPlayerCommand ());
        return MRESULT (FALSE);

    case WM_DESTROY:
        {
            CHAR   ach[_MAX_PATH];

            pset->FilenameToTitle
                (pset->ButtonChecked (hwnd, WID_CB_FILENAMETOTITLE));
            pset->SetFlag (SEI_CUSTOMFILEDIALOG,
                           pset->ButtonChecked (hwnd, WID_CB_CUSTOMFILEDIALOG));
            pset->NoInvalidMP3Warning
                (pset->ButtonChecked (hwnd, WID_CB_NOINVALIDMP3WARNING));
            pset->OnlyReadOnly
                (pset->ButtonChecked (hwnd, WID_CB_ONLYREADONLY));

            WinQueryWindowText (WinWindowFromID (hwnd, WID_E_GENRESFILE),
                                sizeof (ach), ach);
            pset->SetGenresfile (ach);
            WinQueryWindowText (WinWindowFromID (hwnd, WID_E_PLAYERCOMMAND),
                                sizeof (ach), ach);
            pset->SetPlayerCommand (ach);
        }
        return MRESULT (FALSE);
    }
    return WinDefDlgProc (hwnd, msg, mp1, mp2);
}

// ** Page4Procedure ****************************************************** /*fold00*/

MRESULT EXPENTRY
SETTINGS :: Page4Procedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    static PSETTINGS   pset = NULL;

    switch (msg)
    {
    case WM_INITDLG:
        {
            pset = PSETTINGS (mp2);

            // find all dlls and add the names to the language list
            HDIR          hdir;
            ULONG         c, fl;
            FILEFINDBUF3  findbuf;
            APIRET        rc;
            PSZ           psz;

            fl   = FILE_NORMAL;
            hdir = HDIR_CREATE;
            c    = 1;
#ifdef _FROM_FOREIGN_DIR_
            CHAR pszFile[_MAX_PATH];
            sprintf( pszFile, "%s*.dll", g_pszMintaDir );
            rc   = DosFindFirst (pszFile, &hdir, fl, &findbuf,
                                 sizeof (findbuf), &c, FIL_STANDARD);
#else
            rc   = DosFindFirst ("*.dll", &hdir, fl, &findbuf,
                                 sizeof (findbuf), &c, FIL_STANDARD);
#endif

            while (!rc)
            {
                if ((psz = _getext (findbuf.achName)))
                    *psz = '\0';
                findbuf.achName[0] = toupper (findbuf.achName[0]);
                WinInsertLboxItem (WinWindowFromID (hwnd, WID_LB_LANGUAGES),
                                   LIT_END, findbuf.achName);
                c = 1;
                rc = DosFindNext (hdir, &findbuf, sizeof (findbuf), &c);
            }
            DosFindClose (hdir);

#ifdef _SPLITNLS_
            // find all hlps and add the names to the language list
            fl   = FILE_NORMAL;
            hdir = HDIR_CREATE;
            c    = 1;
#ifdef _FROM_FOREIGN_DIR_
            sprintf( pszFile, "%s*.hlp", g_pszMintaDir );
            rc   = DosFindFirst (pszFile, &hdir, fl, &findbuf,
                                 sizeof (findbuf), &c, FIL_STANDARD);
#else
            rc   = DosFindFirst ("*.hlp", &hdir, fl, &findbuf,
                                 sizeof (findbuf), &c, FIL_STANDARD);
#endif
            while (!rc)
            {
                if ((psz = _getext (findbuf.achName)))
                    *psz = '\0';
                findbuf.achName[0] = toupper (findbuf.achName[0]);
                WinInsertLboxItem (WinWindowFromID (hwnd, WID_LB_LANGUAGESHELP),
                                   LIT_END, findbuf.achName);
                c = 1;
                rc = DosFindNext (hdir, &findbuf, sizeof (findbuf), &c);
            }
            DosFindClose (hdir);
#endif

            WinSendMsg (hwnd, UM_SETTINGS2DIALOG, 0,0);

            if (pset->fAutoLanguage)
                WinEnableWindow (WinWindowFromID (hwnd, WID_ST_LANGNOTE),
                                 FALSE);
        }
        return MRESULT (FALSE);

    case WM_COMMAND:
        if( SHORT1FROMMP( mp1 ) == DID_CANCEL )
            WinPostMsg( g_hwndSettingsDialog, msg, mp1, mp2 );
        return MRESULT( FALSE );

/*    case WM_CONTROL:
        switch (SHORT1FROMMP (mp1))
        {
        case WID_LB_LANGUAGES:
            if ((SHORT2FROMMP (mp1) == LN_ENTER) && pset->fAutoLanguage)
                WinSendMsg (pset->hwndDlg, WM_CLOSE, 0, 0);
            break;
        }
        return MRESULT (FALSE);*/

    case UM_SETTINGS2DIALOG:
        {
            // select the appropriate entry in the language-listbox
            CHAR     ach[_MAX_FNAME];
            HWND     hwndLB = WinWindowFromID (hwnd, WID_LB_LANGUAGES);
            ULONG    c, i;

            c = WinQueryLboxCount (hwndLB);

            for (i = 0; i < c; i++)
            {
                WinQueryLboxItemText (hwndLB, i, ach, sizeof (ach));
                if (stricmp (pset->QueryLanguage (), ach) == 0)
                    break;
            }
            if (i < c)
                WinSendDlgItemMsg (hwnd, WID_LB_LANGUAGES, LM_SELECTITEM,
                                   MPFROMSHORT (i), MPFROMSHORT (TRUE));
            else
                WinSendDlgItemMsg (hwnd, WID_LB_LANGUAGES, LM_SELECTITEM,
                                   MPFROMSHORT (0), MPFROMSHORT (TRUE));
#ifdef _SPLITNLS_
            hwndLB = WinWindowFromID (hwnd, WID_LB_LANGUAGESHELP);
            c = WinQueryLboxCount (hwndLB);

            for (i = 0; i < c; i++)
            {
                WinQueryLboxItemText (hwndLB, i, ach, sizeof (ach));
                if (stricmp (pset->QueryString (SEI_LANGUAGEHELP), ach) == 0)
                    break;
            }
            if (i < c)
                WinSendDlgItemMsg (hwnd, WID_LB_LANGUAGESHELP, LM_SELECTITEM,
                                   MPFROMSHORT (i), MPFROMSHORT (TRUE));
            else
                WinSendDlgItemMsg (hwnd, WID_LB_LANGUAGESHELP, LM_SELECTITEM,
                                   MPFROMSHORT (0), MPFROMSHORT (TRUE));
#endif
        }
        return MRESULT (FALSE);

    case WM_DESTROY:
        {
            CHAR   ach[_MAX_FNAME];

            ULONG ul = USHORT (WinSendDlgItemMsg (hwnd, WID_LB_LANGUAGES,
                                                  LM_QUERYSELECTION,
                                                  MPFROMLONG (LIT_FIRST), 0L));
            WinSendDlgItemMsg (hwnd, WID_LB_LANGUAGES, LM_QUERYITEMTEXT,
                               MPFROM2SHORT (ul, sizeof (ach)), MPFROMP (ach));
            pset->SetLanguage (ach);

#ifdef _SPLITNLS_
            ul = USHORT (WinSendDlgItemMsg (hwnd, WID_LB_LANGUAGESHELP,
                                            LM_QUERYSELECTION,
                                            MPFROMLONG (LIT_FIRST), 0L));
            WinSendDlgItemMsg (hwnd, WID_LB_LANGUAGESHELP, LM_QUERYITEMTEXT,
                               MPFROM2SHORT (ul, sizeof (ach)), MPFROMP (ach));
            pset->SetString (SEI_LANGUAGEHELP, ach);
#endif
        }
        return MRESULT (FALSE);
    }

    return WinDefDlgProc (hwnd, msg, mp1, mp2);
}

// ** ReloadResources ***************************************************** /*fold00*/

BOOL SETTINGS :: ReloadResources (PSZ pszName)
{
    if (hmod)
        DosFreeModule (hmod);

    APIRET   rc;

#ifdef _FROM_FOREIGN_DIR_
    CHAR pszFile[_MAX_PATH];
    sprintf( pszFile, "%s%s.dll", g_pszMintaDir, pszName );
#else
    PSZ pszFile = pszName;
#endif

    if ((rc = DosLoadModule (PSZ(NULL), 0, pszFile, &hmod)))
    {
        DisplayError ("ERROR", "Could not (re)load Minta resource module "
                      "'%s' (DosLoadModule() return code %d). Delete "
                      "MINTA.INI and start Minta again. If it does not work "
                      "then, contact the author (thth@gmx.net).", pszFile, rc);
        exit (1);
    }

    return TRUE;
}

// ** SelectLanguage ****************************************************** /*fold00*/

VOID SETTINGS :: SelectLanguage (VOID)
{
    // set this to some default, as we must open the settings dialog for
    // selecting a language
    pszPageTab[0] = RSTR (IDS_PAGENOTIFICATION);
    pszPageTab[1] = RSTR (IDS_PAGEKEEPINFO);
    pszPageTab[2] = RSTR (IDS_PAGEMISC);
    pszPageTab[3] = RSTR (IDS_PAGELANGUAGE);

    // bring up the "select language" settings page
    Dialog (HWND_DESKTOP, TRUE);
}

// ** VersionError ******************************************************** /*fold00*/

USHORT SETTINGS :: VersionError (VOID)
{
    DisplayError (RSTR (IDS_ERROR_INIFILEHEADING),
                  RSTR (IDS_ERROR_NOOROLDINIFILE),
                  QueryProfileName ());
    SelectLanguage ();
    return 0;
}

// ** FileNotOpenError **************************************************** /*fold00*/

USHORT SETTINGS :: FileNotOpenError (VOID)
{
    DisplayError (RSTR (IDS_ERROR_INIFILEHEADING),
                  RSTR (IDS_ERROR_COULDNOTOPENINIFILE),
                  QueryProfileName ());
    SelectLanguage ();
    return 0;
}

// ** QueryWindowData ***************************************************** /*fold00*/

VOID SETTINGS :: QueryWindowData (SWP *pswp, USHORT us[7])
{
    memcpy (pswp, QueryBinary (SEI_SWP), sizeof (*pswp));

    LONG  cx, cy;
    cx = WinQuerySysValue (HWND_DESKTOP, SV_CXSCREEN);
    cy = WinQuerySysValue (HWND_DESKTOP, SV_CYSCREEN);

    // FIXME maybe hidden state and restore coords should be checked too

    // partly outside of screen?
    if (pswp->cx >= cx)
        pswp->x = 0;
    else if (pswp->x+pswp->cx >= cx)
        pswp->x = cx-pswp->cx;

    // partly outside of screen?
    if (pswp->cy >= cy)
        pswp->y = 0;
    else if (pswp->y+pswp->cy >= cy)
        pswp->y = cy-pswp->cy;

    memcpy (us, QueryBinary (SEI_US), sizeof (us[0])*7);
}

// ************************************************************************
