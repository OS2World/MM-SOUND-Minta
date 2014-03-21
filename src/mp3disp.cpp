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

#include "mp3disp.h"

// FIXME this is yukki ...
SWP   swpSave[2];

// ** MP3Display ********************************************************** /*fold00*/

MP3DISPLAY :: MP3Display (PSZ psz)
{
    GETPMP3D = this;

    // init some variables
    this->pmp3 = NULL;
    cFiles = 0L;
    fNoKeep = TRUE;

#ifdef _TOOLBAR_
    ptb = NULL;
#endif

    pszOpenAtStart = psz;

    // load settings from MINTA.INI or use the defaults
    pset = new Settings;

    // load some resource strings
    // FIXME this should be done better, without MP3Display being a friend
    // of all those classes ...
    SETTINGS::pszPageTab[0] = RSTR (IDS_PAGENOTIFICATION);
    SETTINGS::pszPageTab[1] = RSTR (IDS_PAGEKEEPINFO);
    SETTINGS::pszPageTab[2] = RSTR (IDS_PAGEMISC);
    SETTINGS::pszPageTab[3] = RSTR (IDS_PAGELANGUAGE);

    MP3::pszUnknownGenre = RSTR (IDS_UNKNOWNGENRENAME);

    MP3::apszVersions[0] = MP3::apszLayers[0] = RSTR (IDS_UNKNOWN);
    MP3::apszEmphasis[0] = RSTR (IDS_NONE);

    MP3::apszModes[0] = RSTR (IDS_STEREO);
    MP3::apszModes[1] = RSTR (IDS_JOINTSTEREO);
    MP3::apszModes[2] = RSTR (IDS_DUALCHANNEL);
    MP3::apszModes[3] = RSTR (IDS_SINGLECHANNEL);

    apszInc[ 0] = RSTR (IDS_TITLE);
    apszInc[ 1] = RSTR (IDS_TIME);
    apszInc[ 2] = RSTR (IDS_ARTIST);
    apszInc[ 3] = RSTR (IDS_ALBUM);
    apszInc[ 4] = RSTR (IDS_YEAR);
    apszInc[ 5] = RSTR (IDS_GENRE);
    apszInc[ 6] = RSTR (IDS_COMMENT);
    apszInc[ 7] = RSTR (IDS_FILENAMEPATH);
    apszInc[ 8] = RSTR (IDS_VERSION);
    apszInc[ 9] = RSTR (IDS_LAYER);
    apszInc[10] = RSTR (IDS_FREQUENCY);
    apszInc[11] = RSTR (IDS_BITRATE);
    apszInc[12] = RSTR (IDS_MODE);

#ifdef _LOADGENRES_
    pgenlist = new GENLIST (pset->QueryGenresfile ());
#endif

    plist = new Lister (*this);
    pren = new Renamer (*this);
    pfd = new FindDir;

    hwnd = WinLoadDlg (HWND_DESKTOP, NULLHANDLE, WindowProcedure,
                       GETMODULE, ID_MAIN, this);

    SWP      swp;
    USHORT   us[7];

    ULONG   ul = pset->QueryBackgroundColor ();
    WinSetPresParam (hwnd, PP_BACKGROUNDCOLOR, sizeof (ul), &ul);
    CHAR   ach[LEN_FONTNAMESIZE];
    strcpy (ach, pset->QueryFontNameSize ());
    WinSetPresParam (hwnd, PP_FONTNAMESIZE, sizeof (ach), ach);

    phelp = new HELPER (hwnd);
    if (! phelp->IsAvailable ())
        EnableHelp (FALSE);

    pset->QueryWindowData (&swp, us);
    if (swp.cx > 0)
    {
        /* size, activate & show window */
        WinSetWindowPos (hwnd, HWND_DESKTOP, swp.x,swp.y, 0,0,/*swp.cx,swp.cy,*/
                         SWP_ACTIVATE | SWP_SHOW | /*SWP_SIZE |*/ SWP_MOVE);
        WinSetWindowUShort (hwnd, QWS_XRESTORE, us[0]);
        WinSetWindowUShort (hwnd, QWS_YRESTORE, us[1]);
        WinSetWindowUShort (hwnd, QWS_CXRESTORE, us[2]);
        WinSetWindowUShort (hwnd, QWS_CYRESTORE, us[3]);
        WinSetWindowUShort (hwnd, QWS_XMINIMIZE, us[4]);
        WinSetWindowUShort (hwnd, QWS_YMINIMIZE, us[5]);
    }

#ifdef _TOOLBAR_
    // init the toolbar
    ptb = new TOOLBAR (hwnd);
    ptb->Rebuild (GETSETTINGS->QueryToolbarTemplate ());
    if (GETSETTINGS->ShowToolbar ())
        ShowToolbar (TRUE);
#endif

    WinProcessDlg (hwnd);

    WinQueryWindowPos (hwnd, &swp);
    us[0] = WinQueryWindowUShort (hwnd, QWS_XRESTORE);
    us[1] = WinQueryWindowUShort (hwnd, QWS_YRESTORE);
    us[2] = WinQueryWindowUShort (hwnd, QWS_CXRESTORE);
    us[3] = WinQueryWindowUShort (hwnd, QWS_CYRESTORE);
    us[4] = WinQueryWindowUShort (hwnd, QWS_XMINIMIZE);
    us[5] = WinQueryWindowUShort (hwnd, QWS_YMINIMIZE);

    pset->SetWindowData (&swp, us);

    delete phelp;
    delete pfd;
    delete plist;

#ifdef _LOADGENRES_
// FIXME   delete pgenlist;
#endif

    delete pset;
    WinDestroyWindow (hwnd);
}

// ** WindowProcedure ***************************************************** /*FOLD00*/

MRESULT EXPENTRY
MP3DISPLAY :: WindowProcedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    static PMP3DISPLAY   pmp3d = NULL;

    switch (msg)
    {
    case WM_INITDLG: /*fold01*/
        {
            pmp3d = PMP3DISPLAY (mp2);

            // must be set here already because 'SetMP3' and "Enable*' need it
            pmp3d->hwnd = hwnd;

            WinEnableWindow (WinWindowFromID (hwnd, WID_DDL_FILES), FALSE);
            WinSendDlgItemMsg (hwnd, WID_DDL_FILES, EM_SETTEXTLIMIT,
                               (MPARAM)_MAX_PATH, (MPARAM)0);

            USHORT   usResID = WinQueryWindowUShort (hwnd, QWS_ID);

            // attach the menu
            if (HWND hmenu = WinLoadMenu (hwnd, GETMODULE, usResID))
                WinSendMsg (hwnd, WM_UPDATEFRAME, MPFROMLONG (FID_MENU),
                            NULL);

            // attach the icon
            if (HPOINTER hicon = WinLoadPointer (HWND_DESKTOP, GETMODULE,
                                                 usResID))
                WinSendMsg (hwnd, WM_SETICON, MPFROMLONG (hicon), MPVOID);

            // attach the accelerator table
            if (HACCEL haccel = WinLoadAccelTable (GETHAB, GETMODULE,
                                                   usResID))
                WinSetAccelTable (hab, haccel, hwnd);

            // set text limits of entry fields
            WinSendMsg (WinWindowFromID (hwnd, WID_E_TITLE), EM_SETTEXTLIMIT,
                        MPARAM (MAXLEN_TITLE), (MPARAM)0);
            WinSendMsg (WinWindowFromID (hwnd, WID_E_ARTIST), EM_SETTEXTLIMIT,
                        MPARAM (MAXLEN_ARTIST), (MPARAM)0);
            WinSendMsg (WinWindowFromID (hwnd, WID_E_ALBUM), EM_SETTEXTLIMIT,
                        MPARAM (MAXLEN_ALBUM), (MPARAM)0);
            WinSendMsg (WinWindowFromID (hwnd, WID_E_COMMENT), EM_SETTEXTLIMIT,
                        MPARAM (MAXLEN_COMMENT), (MPARAM)0);
            WinSendMsg (WinWindowFromID (hwnd, WID_E_YEAR), EM_SETTEXTLIMIT,
                        MPARAM (MAXLEN_YEAR), (MPARAM)0);

            // init genres listbox
            ULONG   ul = 0L;
            WinSendDlgItemMsg (hwnd, WID_DDL_GENRE, LM_DELETEALL, NULL,NULL);

#ifdef _LOADGENRES_
            for (USHORT i = 0; i < GETGENLIST.QueryCount (); i++)
#else
            for (USHORT i = 0; i < MAX_GENRES; i++)
#endif
            {
#ifdef _LOADGENRES_
                ul = ULONG (WinSendDlgItemMsg
                            (hwnd, WID_DDL_GENRE, LM_INSERTITEM,
                             MPFROM2SHORT (LIT_SORTASCENDING,0),
                             GETGENLIST.QueryName (i)));
#else
                ul = ULONG (WinSendDlgItemMsg
                            (hwnd, WID_DDL_GENRE, LM_INSERTITEM,
                             MPFROM2SHORT (LIT_SORTASCENDING,0),
                             MP3::apszGenres[i]));
#endif
                WinSendDlgItemMsg (hwnd, WID_DDL_GENRE, LM_SETITEMHANDLE,
                                   MPFROMSHORT (ul), MPFROMSHORT (i));
            }

            // insert the "(none)" item
            WinSendDlgItemMsg (hwnd, WID_DDL_GENRE, LM_INSERTITEM,
                               MPFROMLONG (0L),
#ifdef _MULTILANGUAGES_
                               RSTR (IDS_GENRENONE));
#else
                               "(none)");
#endif
            WinSendDlgItemMsg (hwnd, WID_DDL_GENRE, LM_SETITEMHANDLE,
                               MPFROMSHORT (0L), MPFROMSHORT (GENREID_NIL));

            // init track spinbutton
            WinSendDlgItemMsg (hwnd, WID_SB_TRACK, SPBM_SETLIMITS,
                               MPFROMLONG (MAX_TRACK), MPFROMLONG (0));
            WinSendDlgItemMsg (hwnd, WID_SB_TRACK, SPBM_SETCURRENTVALUE,
                               MPFROMLONG (0), 0);

            // FIXME this belongs to the yukki stuff ...
            WinQueryWindowPos (WinWindowFromID (hwnd, WID_PB_SAVE),
                               &swpSave[0]);
            WinQueryWindowPos (WinWindowFromID (hwnd, WID_PB_REMOVE),
                               &swpSave[1]);

            if (! pmp3d->pset->ShowFileinfo ())
                pmp3d->ShowFileinfo (FALSE);
            if (! pmp3d->pset->ShowButtons ())
                pmp3d->ShowButtons (FALSE);

/*            pmp3d->pfnwp =
                WinSubclassWindow (WinWindowFromID (hwnd, WID_DDL_FILES),
                                   PFNWP (LocalDDLProc)); */

            if (pmp3d->pszOpenAtStart)
                WinSendMsg (hwnd, UM_OPENFILES,
                            MPFROMP (pmp3d->pszOpenAtStart), 0L);
            else
                pmp3d->Refresh ();
        }
        return MRESULT (0);

    case WM_COMMAND: /*FOLD01*/
        switch (SHORT1FROMMP (mp1))
        {
#ifdef _ANIMTEST_
        case WID_PB_TEST:
            AnimateMousepointer ();
            break;
#endif

        case WID_PB_FILES: {
            /*DosBeep( 2000, 200 );
            DisplayError( "DEBUG", QueryProfileName() );*/
            pmp3d->OpenFiles ();
/*            DisplayError( "DEBUG", "Before WinSetFocus %x", WinGetLastError( GETHAB ) );
            if( ! WinIsWindow( GETHAB, hwnd ) )
                DisplayError( "DEBUG", "! WinIsWindow %x %x %x", WinGetLastError( GETHAB ), WinGetLastError( GETHAB ), hwnd );
            HWND hwndFiles = WinWindowFromID( hwnd, WID_DDL_FILES );
            DisplayError( "DEBUG", "After WinWindowFromID %x %x %x", WinGetLastError( GETHAB ), WinGetLastError( GETHAB ), hwndFiles );
            //WinSetFocus( hwndFiles, TRUE );
            WinSetActiveWindow( HWND_DESKTOP, hwndFiles );
            DisplayError( "DEBUG", "After WinSetFocus %x", WinGetLastError( GETHAB ) ); */
        } break;

        case WID_PB_AUTOOPEN:
            pmp3d->EnableAutoopen (FALSE);
            {
                CHAR   ach[_MAX_PATH];

                if (pmp3d->pfd->Dialog (NULL, pmp3d->pset->QueryWorkDir (),
                                        ach, _MAX_PATH))
                    pmp3d->AutoOpenFiles (ach);
            }
            pmp3d->EnableAutoopen (TRUE);
            break;

        case WID_PB_DELETEFROMLIST:
            pmp3d->RemoveFile ();
            break;

        case WID_PB_DELETEALLFROMLIST:
            pmp3d->RemoveAllFiles ();
            break;

        case WID_PB_LIST:
            if (pmp3d->FilesInList ())
                if (pmp3d->plist->Dialog ())
                    pmp3d->plist->OutputList ();
            break;

        case WID_PB_RENAMEALL:
            if (pmp3d->pren->Dialog ())
                pmp3d->RenameAll ();
            break;

        case WID_PB_SETTINGS:
            pmp3d->pset->Dialog (hwnd);
            pmp3d->Refresh ();
            break;

        case WID_PB_EXIT:
            WinSendMsg (hwnd, WM_CLOSE, 0,0);
            break;

        case WID_PB_SAVE:
            pmp3d->SaveCurrent ();
            break;

        case WID_PB_SAVEPREV:
            if (pmp3d->QueryMP3 ())
            {
                pmp3d->fNoKeep = FALSE;
                pmp3d->SaveCurrent ();

                ULONG ul = USHORT
                    (WinSendDlgItemMsg (hwnd, WID_DDL_FILES,
                                        LM_QUERYSELECTION,
                                        MPFROMLONG (LIT_FIRST), 0L));
                // is this the first file in list, so we can't select a
                // previous one?
                if (ul == 0L)
                    DosBeep (1000, 10);
                else
                {
                    if (pmp3d->cTrack > 0)
                        pmp3d->cTrack --;
                    // select previous file in list
                    WinSendDlgItemMsg (hwnd, WID_DDL_FILES, LM_SELECTITEM,
                                       MPFROMLONG (ul-1L), MPFROMLONG (TRUE));
                    WinSendDlgItemMsg (hwnd, WID_DDL_FILES, CBM_SHOWLIST,
                                       FALSE, 0);
                }
                // activate "Title" entryfield
                WinSetFocus (HWND_DESKTOP,
                             WinWindowFromID (hwnd, WID_E_TITLE));
                pmp3d->fNoKeep = TRUE;
            }
            break;

        case WID_PB_SAVENEXT:
            if (pmp3d->QueryMP3 ())
            {
                pmp3d->fNoKeep = FALSE;
                pmp3d->SaveCurrent ();

                ULONG ul = USHORT
                    (WinSendDlgItemMsg (hwnd, WID_DDL_FILES, LM_QUERYSELECTION,
                                        MPFROMLONG (LIT_FIRST), 0L));
                // is this the last file in list, so we can't select a
                // next one?
                if (ul == pmp3d->CountFilesInList ()-1L)
                    DosBeep (1000, 10);
                else
                {
                    if (pmp3d->cTrack < MAX_TRACK)
                        pmp3d->cTrack ++;
                    // select next file in list
                    WinSendDlgItemMsg (hwnd, WID_DDL_FILES, LM_SELECTITEM,
                                       MPFROMLONG (ul+1L), MPFROMLONG (TRUE));
                    WinSendDlgItemMsg (hwnd, WID_DDL_FILES, CBM_SHOWLIST,
                                       FALSE, 0);
                }
                // activate "Title" entryfield
                WinSetFocus (HWND_DESKTOP,
                             WinWindowFromID (hwnd, WID_E_TITLE));
                pmp3d->fNoKeep = TRUE;
            }
            break;

        case WID_PB_SAVEALL:
            pmp3d->SaveAll ();
            break;

        case WID_PB_REMOVE:
            if (pmp3d->QueryMP3 ())
            {
                pmp3d->QueryMP3 ()->RemoveTag ();
                pmp3d->Refresh ();
            }
            break;

        case WID_PB_REMOVEALL:
            pmp3d->RemoveAll ();
            break;

#ifdef _PLAYERCOMMAND_
        case WID_PB_PLAY:
            pmp3d->LaunchPlayer ();
            break;
#endif

        case WID_PB_SHOWBUTTONS:
            if (pmp3d->pset->ShowButtons ())
            {
                pmp3d->ShowButtons (FALSE);
                pmp3d->pset->ShowButtons (FALSE);
            }
            else
            {
                pmp3d->ShowButtons (TRUE);
                pmp3d->pset->ShowButtons (TRUE);
            }
            break;

#ifdef _SHOWFILEINFO_
        case WID_PB_SHOWFILEINFO:
            if (pmp3d->pset->ShowFileinfo ())
            {
                pmp3d->ShowFileinfo (FALSE);
                pmp3d->pset->ShowFileinfo (FALSE);
            }
            else
            {
                pmp3d->ShowFileinfo (TRUE);
                pmp3d->pset->ShowFileinfo (TRUE);
            }
            break;
#endif

#ifdef _TOOLBAR_
        case WID_PB_SHOWTOOLBAR:
            if (GETSETTINGS->ShowToolbar ())
            {
                pmp3d->ShowToolbar (FALSE);
                GETSETTINGS->ShowToolbar (FALSE);
            }
            else
            {
                pmp3d->ShowToolbar (TRUE);
                GETSETTINGS->ShowToolbar (TRUE);
            }
            break;
#endif

        case WID_PB_ABOUT:
            AboutBox (hwnd);
            break;

        case HM_HELP_CONTENTS:
            pmp3d->phelp->DisplayContents ();
            break;

        case HM_HELP_INDEX:
            pmp3d->phelp->DisplayIndex ();
            break;

        case HM_KEYS_HELP:
            pmp3d->phelp->DisplayKeysHelp ();
            break;

        case WID_MAIN_HELP:
            pmp3d->phelp->DisplayPanel( 1000 );
            break;
        }
        return MRESULT (0);

    case WM_CONTROL: /*fold01*/
        switch (SHORT1FROMMP (mp1))
        {
        case WID_DDL_FILES:
            switch (SHORT2FROMMP (mp1))
            {
            case CBN_LBSELECT:         pmp3d->Refresh ();       break;
            }
            break;

        case WID_SB_TRACK:
            break;
        }
        return (MRESULT)0;

    case WM_CLOSE: /*fold01*/
        if (pmp3d->pmp3)
            delete pmp3d->pmp3;
        break;

    case WM_PRESPARAMCHANGED:
        switch (LONGFROMMP (mp1))
        {
        case PP_FONTNAMESIZE:
            {
                ULONG   ppid;
                CHAR    psz[LEN_FONTNAMESIZE];

                if (WinQueryPresParam (hwnd, PP_FONTNAMESIZE, 0, &ppid,
                                       sizeof (psz), &psz, 0))
                    pmp3d->pset->SetFontNameSize (PSZ (psz));
            }
            break;

        case PP_BACKGROUNDCOLOR:
            {
                ULONG   ppid;
                COLOR   color;

                if (WinQueryPresParam (hwnd, PP_BACKGROUNDCOLOR, 0, &ppid,
                                       sizeof (color), &color, 0))
                    pmp3d->pset->SetBackgroundColor (color);
            }
            break;
        }
//        WinInvalidateRect (hwnd, NULL, TRUE);
        break;

    case HM_QUERY_KEYS_HELP:
        return (MRESULT)FALSE;

    case UM_OPENFILES: /*fold01*/
        // FIXME
        pmp3d->AutoOpenFiles (pmp3d->pszOpenAtStart);
        return MRESULT (FALSE);

#ifdef _DRAGNDROP_
    case DM_DRAGOVER: /*fold01*/
        {
            PDRAGINFO   pdinfo = PDRAGINFO (mp1);
            PDRAGITEM   pditem;
            USHORT      usOp = DO_UNKNOWN, usIndicator = DOR_DROP, cItems;

            // get access to the DRAGINFO data structure
            DrgAccessDraginfo (pdinfo);

            // can we accept this drop?
            switch (pdinfo->usOperation)
            {
                /* Return DOR_NODROPOP if current operation
                 is link or unknown or copy or move */
            case DO_UNKNOWN:
            case DO_MOVE:
            case DO_COPY:
                DrgFreeDraginfo (pdinfo);
                return (MRFROM2SHORT (DOR_NODROPOP, 0));
            }

            usIndicator = DOR_DROP;
            cItems      = DrgQueryDragitemCount (pdinfo);

            /* Now, we need to look at each item in turn */
            for (USHORT i = 0; i < cItems; i++)
            {
                pditem = DrgQueryDragitemPtr (pdinfo, i);

                // check the rendering format
                if (DrgVerifyRMF (pditem, "DRM_OS2FILE", NULL))
                    usIndicator = DOR_DROP;
                else
                    usIndicator = DOR_NEVERDROP;
            }

            DrgFreeDraginfo (pdinfo);
            return MRFROM2SHORT (usIndicator, usOp);
        }
        break;

    case DM_DROP:
        {
            PDRAGINFO   pdinfo = PDRAGINFO (mp1);
            PDRAGITEM   pditem = NULL;
            USHORT      usOp = DO_UNKNOWN, usIndicator = DOR_DROP, cItems;

            // get access to the DRAGINFO data structure
            DrgAccessDraginfo (pdinfo);

            usIndicator = DOR_DROP;
            cItems      = DrgQueryDragitemCount (pdinfo);

            CHAR   ach[_MAX_PATH], ach2[_MAX_PATH];
            ULONG  ul = 0L;

            for (USHORT i = 0; i < cItems; i++)
            {
                pditem = DrgQueryDragitemPtr (pdinfo, i);

                if (DrgVerifyRMF (pditem, "DRM_OS2FILE", NULL))
                {
                    usIndicator = DOR_DROP;

                    DrgQueryStrName (pditem->hstrContainerName, sizeof (ach2),
                                     ach2);
                    DrgQueryStrName (pditem->hstrSourceName, sizeof (ach),
                                     ach);
                    strcat (ach2, ach);
                    ul += pmp3d->OpenFiles (ach2);
                }
                else
                    usIndicator = DOR_NEVERDROP;
            }

/*            CHAR  achDummy[3][_MAX_PATH];

            DrgQueryStrName (pditem->hstrType,
                             sizeof (achDummy[0]),
                             achDummy[0]);
            DrgQueryStrName (pditem->hstrRMF,
                             sizeof (achDummy[1]),
                             achDummy[1]);
            DrgQueryStrName (pditem->hstrSourceName,
                             sizeof (achDummy[2]),
                             achDummy[2]);
            DisplayError ("DEBUG", "<%s> <%s> <%s>",
                          achDummy[0], achDummy[1], achDummy[2]); */

            // if no file selected, select first one
            if (LONG (WinSendDlgItemMsg (hwnd, WID_DDL_FILES,
                                         LM_QUERYSELECTION,
                                         MPFROMLONG (LIT_FIRST), 0L))
                == LIT_NONE)
                pmp3d->SelectFirstFile ();
            else
                pmp3d->Refresh ();

            if (pmp3d->pset->NotifyLoad ())
                pmp3d->NotificationAutoOpen (ul);

            WinSetWindowText (hwnd, PSZ_NAMEVERSION);

            DrgFreeDraginfo (pdinfo);
            return MRFROM2SHORT (usIndicator, usOp);
        }
        break;
#endif
    }

    return WinDefDlgProc (hwnd, msg, mp1, mp2);
}

// ** OpenFiles *********************************************************** /*fold00*/

BOOL MP3DISPLAY :: OpenFiles (VOID)
{
#ifdef _DEBUGLOG_
    fputs ("\nOpenFiles ()\n", pfileLog);
#endif

    FILEDLG   fdlg;
    static PSZ  apsz[] = { PSZ_MP3TYPE, "MP3 audio stream", NULL };

    if (! hwnd)
        return FALSE;

    // init the FILEDLG structure
    memset (&fdlg, 0, sizeof (fdlg));

    fdlg.cbSize   = sizeof (fdlg);
    fdlg.fl       = FDS_OPEN_DIALOG | FDS_CENTER | FDS_MULTIPLESEL;
    fdlg.pszTitle = RSTR (IDS_OPENMP3FILES);
    fdlg.pszIType = NULL;
    fdlg.papszITypeList = PAPSZ (&apsz);

    if (GETSETTINGS->QueryFlag (SEI_CUSTOMFILEDIALOG))
    {
        fdlg.fl |= FDS_CUSTOM;
        fdlg.hMod       = GETMODULE;
        fdlg.usDlgId    = ID_DLG_FILE;
        fdlg.pfnDlgProc = FileDLGProcedure;
    }

    strcpy (fdlg.szFullFile, pset->QueryWorkDir ());
    if (fdlg.szFullFile[strlen (fdlg.szFullFile)-1] == '\\')
        strcat (fdlg.szFullFile, "*.mp3");
    else
        strcat (fdlg.szFullFile, "\\*.mp3");

    // invoke the file dialog
    if (! WinFileDlg (HWND_DESKTOP, hwnd, &fdlg))
        return FALSE;

    // "Cancel" or no files were selected
    if ((fdlg.lReturn != DID_OK) ||
        ((fdlg.ulFQFCount == 0L) && (strlen (fdlg.szFullFile) == 0)))
        return FALSE;

    // As there can only be files selected from the listbox or one file
    // entered manually by the user, we can exit with FALSE here
    // FIXME display some error msg?
    if (access (fdlg.szFullFile, R_OK) != 0)
        return FALSE;

#ifndef _MULTIDIRSELECT_
    ClearFiles ();
#endif
    // have multiple files been selected?
    if (fdlg.papszFQFilename)
    {
        for (USHORT i = 0; i < fdlg.ulFQFCount; i++)
            AddFile (*(fdlg.papszFQFilename[i]));
    }
    else
        AddFile (fdlg.szFullFile);

    // if no file selected, select first one
    if (LONG (WinSendDlgItemMsg (hwnd, WID_DDL_FILES, LM_QUERYSELECTION,
                                 MPFROMLONG (LIT_FIRST), 0L)) == LIT_NONE)
        SelectFirstFile ();
    else
        Refresh ();

    // save currently selected dir for use next time dlg is invoked
    strcpy (achDir, fdlg.szFullFile);
    PSZ  psz = _getname (achDir);
    if (psz)
        *(psz-1) = '\0';
    pset->SetWorkDir (achDir);

    return TRUE;
}

// ------------------------------------------------------------------------ /*fold00*/

ULONG MP3DISPLAY :: OpenFiles (PSZ psz)
{
    struct stat   st;

    stat (psz, &st);

    if (S_ISREG (st.st_mode))
    {
        ULONG   ul = CountFilesInList ();
        AddFile (psz);
        if (ul < CountFilesInList ())
            return 1L;
    }
    else if (S_ISDIR (st.st_mode))
    {
        // check dir and all subdirs and insert MP3's found
        return ProcessDirectory (psz);
    }
    else
        DisplayError (RSTR (IDS_ERROR_GENERALHEADING),
                      RSTR (IDS_ERROR_NOFILENODIR), psz, errno);

    return 0L;
}

// ** AutoOpenFiles ******************************************************* /*fold00*/

LONG MP3DISPLAY :: AutoOpenFiles (PSZ psz)
{
#ifdef _DEBUGLOG_
    fputs ("\nAutoOpenFiles ()\n", pfileLog);
#endif

    // set mouse-ptr to "wait" shape
    HPOINTER   hptr = WinQueryPointer (HWND_DESKTOP);
    WinSetPointer (HWND_DESKTOP, WinQuerySysPointer (HWND_DESKTOP, SPTR_WAIT,
                                                     FALSE));
    // check dir and all subdirs and insert MP3's found
    LONG   l = OpenFiles (psz);

    // if no file selected, select first one
    if (LONG (WinSendDlgItemMsg (hwnd, WID_DDL_FILES, LM_QUERYSELECTION,
                                 MPFROMLONG (LIT_FIRST), 0L)) == LIT_NONE)
        SelectFirstFile ();
    else
        Refresh ();

    if (pset->NotifyLoad ())
        NotificationAutoOpen (l);

    // save currently selected dir for use next time dlg is invoked
    pset->SetWorkDir (psz);

    // set mouse-ptr to normal shape
    WinSetPointer (HWND_DESKTOP, hptr);
    WinSetWindowText (hwnd, PSZ_NAMEVERSION);

    return l;
}

// ** ProcessDirectory **************************************************** /*fold00*/

LONG MP3DISPLAY :: ProcessDirectory (PSZ psz)
{
    HDIR          hdir;
    ULONG         c, cFilesOld = CountFilesInList (), fl;
    CHAR          pszNew[_MAX_PATH+31];
    FILEFINDBUF3  findbuf;
    APIRET        rc;
    PSZ           pszDummy = "";

    if (psz[strlen (psz)-1] != '\\')
        pszDummy = "\\";

    // set window title
#ifdef _MULTILANGUAGES_
    sprintf (pszNew, RSTR (IDS_SEARCHINGFORMAT), psz);
#else
    sprintf (pszNew, "Searching - %s", psz);
#endif
    WinSetWindowText (hwnd, pszNew);

    sprintf (pszNew, "%s%s*", psz, pszDummy);

    // find all subdirectories and process them recursivly
    fl = MUST_HAVE_DIRECTORY;
    hdir = HDIR_CREATE;
    c = 1;
    rc = DosFindFirst (pszNew, &hdir, fl, &findbuf, sizeof (findbuf), &c,
                       FIL_STANDARD);
    while (!rc)
    {
        // we don't want to proceed *these*
        if ((strcmp (findbuf.achName, ".") != 0) &&
            (strcmp (findbuf.achName, "..") != 0))
        {
            sprintf (pszNew, "%s%s%s", psz, pszDummy, findbuf.achName);
            ProcessDirectory (pszNew);
        }
        c = 1;
        rc = DosFindNext (hdir, &findbuf, sizeof (findbuf), &c);
    }
    DosFindClose (hdir);

    sprintf (pszNew, "%s%s*.mp3", psz, pszDummy);

    // find all mp3 files and add them to the files list
    fl = FILE_NORMAL;
    hdir = HDIR_CREATE;
    c = 1;
    rc = DosFindFirst (pszNew, &hdir, fl, &findbuf, sizeof (findbuf), &c,
                       FIL_STANDARD);
    while (!rc)
    {
        sprintf (pszNew, "%s%s%s", psz, pszDummy, findbuf.achName);
        AddFile (pszNew);
        c = 1;
        rc = DosFindNext (hdir, &findbuf, sizeof (findbuf), &c);
    }
    DosFindClose (hdir);

    return (CountFilesInList () - cFilesOld);
}

// ** AddFile ************************************************************* /*fold00*/

VOID MP3DISPLAY :: AddFile (PSZ psz)
{
    if (! hwnd)
        return;

    SHORT   s;

    strlwr (psz);

    // only add if not already in list
    // FIXME may there be problems because of CASESENSITIVE?
    s = SHORT (WinSendDlgItemMsg (hwnd, WID_DDL_FILES, LM_SEARCHSTRING,
                                  MPFROM2SHORT (LSS_CASESENSITIVE, LIT_FIRST),
                                  psz));
    if (s == LIT_NONE)
    {
        // if this MP3's filename is longer than current maximum in list
        // adjust maximum (needed for outputing lists)
        plist->usMaxLen[TAG_FILENAME] =
            max (plist->usMaxLen[TAG_FILENAME], USHORT (strlen (psz)));

        // insert filename into listbox
        WinSendDlgItemMsg (hwnd, WID_DDL_FILES, LM_INSERTITEM,
                           MPFROM2SHORT (LIT_SORTASCENDING,0), psz);
        cFiles ++;

#ifdef _DEBUGLOG_
        fprintf (pfileLog, "\nAdded file '%s' ...\n", psz);
#endif
/*
        // if this is the first file in the list, select it; this will auto-
        // refresh the display through LN_SELECT in the W.P.
        if (CountFilesInList () == 1L)
            SelectFirstFile (); */
    }
}

// ** RemoveFile ********************************************************** /*fold00*/

VOID MP3DISPLAY :: RemoveFile (PSZ psz)
{
    if (! hwnd || ! FilesInList ())
        return;

    HWND    hwndDDL = WinWindowFromID (hwnd, WID_DDL_FILES);
    SHORT   s, c = 0;

    // get position of item to be deleted
    if (psz)
        s = SHORT (WinSendMsg (hwndDDL, LM_SEARCHSTRING,
                               MPFROM2SHORT (LSS_CASESENSITIVE, LIT_FIRST),
                               psz));
    else
        s = SHORT (WinSendMsg (hwndDDL, LM_QUERYSELECTION,
                               MPFROMLONG (LIT_FIRST), 0L));

    // name not found (or none selected!?)
    if (s == LIT_NONE)
        return;

    // is it the current one? delete the mp3-object
    if (s == SHORT (WinSendMsg (hwndDDL, LM_QUERYSELECTION,
                                MPFROMLONG (LIT_FIRST), 0L)))
        if (QueryMP3 ())
        {
            delete QueryMP3 ();
            SetMP3 (NULL);  // added - Dec 29, 98
        }

    // delete item from files listbox
    c = USHORT (WinSendMsg (hwndDDL, LM_DELETEITEM, MPFROMSHORT (s), 0L));
    cFiles --;

    // no more files in listbox? disable it
    if (cFiles == 0)
        WinEnableWindow (hwndDDL, FALSE);

    // still files in list?
    if (c > 0)
    {
        // select (next) file in list (usual auto-refresh, etc.)
        if (s >= c)
            s --;
        WinSendMsg (hwndDDL, LM_SELECTITEM, MPFROMLONG (s), MPFROMLONG (TRUE));
        WinSendMsg (hwndDDL, CBM_SHOWLIST, FALSE, 0);
    }
    else
        Refresh ();
}

// ** Refresh ************************************************************* /*fold00*/

VOID MP3DISPLAY :: Refresh (VOID)
{
    if (FilesInList ())
    {
        CHAR   ach[_MAX_PATH];

        // get name of selected file and open it
        QueryFile (ach, sizeof (ach));
        PMP3   pmp3New = new MP3 (ach);
        if (pmp3New->Error () == MP3ERR_FILENOTOPEN)
        {
            DisplayError (RSTR (IDS_ERROR_MP3FILEHEADING),
                          RSTR (IDS_ERROR_COULDNOTOPENMP3FILE),
                          pmp3New->strFilename.c_str (), errno);
            // delete item from files listbox
            SHORT s = SHORT (WinSendDlgItemMsg (hwnd, WID_DDL_FILES, LM_QUERYSELECTION,
                                          MPFROMLONG (LIT_FIRST), 0L));
            WinSendDlgItemMsg (hwnd, WID_DDL_FILES, LM_DELETEITEM, MPFROMSHORT (s), 0L);
/*            WinSendDlgItemMsg (hwnd, WID_DDL_FILES, LM_SELECTITEM,
                               MPFROMLONG (0L), MPFROMLONG (TRUE)); */
            return;
        }

        if (QueryMP3 ())
        {
#ifdef _DEBUGLOG_
            fprintf (pfileLog, "\nRefresh Pre: file '%s' has %s tag\n",
                     QueryMP3 ()->QueryFilename ().c_str (),
                     QueryMP3 ()->IsTagged () ? "a" : "no");
#endif
            delete QueryMP3 ();
        }

        SetMP3 (pmp3New);

#ifdef _DEBUGLOG_
        fprintf (pfileLog, "\nRefresh Post: file '%s' has %s tag\n",
                 QueryMP3 ()->QueryFilename ().c_str (),
                 QueryMP3 ()->IsTagged () ? "a" : "no");
        fflush (pfileLog);
#endif
        // FIXME what if could not be opened?
    }
    else
    {
        SetMP3 (NULL);
        cTrack = 0;
    }

    RefreshFileList ();
    RefreshFileGroup ();
    RefreshTagGroup ();
    RefreshButtons ();
}

// ** RefreshFileList ***************************************************** /*fold00*/

VOID MP3DISPLAY :: RefreshFileList (VOID)
{
    if (! FilesInList ())
    {
        /* FIXME WHY DOES THIS NOT WORK?!?! It does in RenameAll!!
         HWND   hwnd2 = WinWindowFromID (hwnd, WID_DDL_FILES);

        if (hwnd2)
        {
            CHAR   ach[2];
            strcpy (ach, "Test");
            WinSetWindowText (hwnd2, ach);
        } */
        WinEnableWindow (WinWindowFromID (hwnd, WID_DDL_FILES), FALSE);
    }
    else
        WinEnableWindow (WinWindowFromID (hwnd, WID_DDL_FILES), TRUE);

    AdjustFilelistTitle ();
}

// ** RefreshFileGroup **************************************************** /*fold00*/

VOID MP3DISPLAY :: RefreshFileGroup (VOID)
{
    CHAR    ach[301];
    ULONG   ul;

    if (! hwnd)
        return;

    if (! QueryMP3 ())
    {
        // clear file info group
        WinSetWindowText (WinWindowFromID (hwnd, WID_E_VERSION), NULL);
        WinSetWindowText (WinWindowFromID (hwnd, WID_E_LAYER), NULL);
        WinSetWindowText (WinWindowFromID (hwnd, WID_E_FREQUENCY), NULL);
        WinSetWindowText (WinWindowFromID (hwnd, WID_E_BITRATE), NULL);
        WinSetWindowText (WinWindowFromID (hwnd, WID_E_TIME), NULL);
        WinSetWindowText (WinWindowFromID (hwnd, WID_E_MODE), NULL);
        WinSetWindowText (WinWindowFromID (hwnd, WID_E_EMPHASIS), NULL);

        WinSendDlgItemMsg (hwnd, WID_CB_PRIVATE, BM_SETCHECK,
                           MPFROMLONG (FALSE), 0);
        WinSendDlgItemMsg (hwnd, WID_CB_CRCS, BM_SETCHECK,
                           MPFROMLONG (FALSE), 0);
        WinSendDlgItemMsg (hwnd, WID_CB_COPYRIGHT, BM_SETCHECK,
                           MPFROMLONG (FALSE), 0);
        WinSendDlgItemMsg (hwnd, WID_CB_PADDING, BM_SETCHECK,
                           MPFROMLONG (FALSE), 0);
        WinSendDlgItemMsg (hwnd, WID_CB_ORIGINAL, BM_SETCHECK,
                           MPFROMLONG (FALSE), 0);
        // set title of group
        WinSetWindowText (WinWindowFromID (hwnd, WID_G_FILEINFO),
#ifdef _MULTILANGUAGES_
                          RSTR (IDS_NOFILENOINFO));
#else
                          "No file, no info!");
#endif
        return;
    }

    // set info in the file info group
    WinSetWindowText (WinWindowFromID (hwnd, WID_E_VERSION),
                      QueryMP3 ()->QueryVersionName ());
    WinSetWindowText (WinWindowFromID (hwnd, WID_E_LAYER),
                      QueryMP3 ()->QueryLayerName ());

    sprintf (ach, "%ld Hz", QueryMP3 ()->QueryFrequency ());
    WinSetWindowText (WinWindowFromID (hwnd, WID_E_FREQUENCY), ach);

    sprintf (ach, "%ld kbits/s", QueryMP3 ()->QueryBitrate ());
    WinSetWindowText (WinWindowFromID (hwnd, WID_E_BITRATE), ach);

    if (QueryMP3 ()->QueryMode (&ul) == MODE_JOINTSTEREO)
        sprintf (ach, "%s [%lu]", QueryMP3 ()->QueryModeName (), ul);
    else
        sprintf (ach, "%s", QueryMP3 ()->QueryModeName ());
    WinSetWindowText (WinWindowFromID (hwnd, WID_E_MODE), ach);

    WinSetWindowText (WinWindowFromID (hwnd, WID_E_EMPHASIS),
                      QueryMP3 ()->QueryEmphasisName ());

    sprintf (ach, "%0ld:%02ld", QueryMP3 ()->QueryTime ()/60, QueryMP3 ()->QueryTime ()%60);
    WinSetWindowText (WinWindowFromID (hwnd, WID_E_TIME), ach);

    // set checkbuttons in the file info group
    WinSendDlgItemMsg (hwnd, WID_CB_PRIVATE, BM_SETCHECK,
                       MPFROMLONG (QueryMP3 ()->IsPrivate ()), 0);
    WinSendDlgItemMsg (hwnd, WID_CB_CRCS, BM_SETCHECK,
                       MPFROMLONG (QueryMP3 ()->HasCRCs ()), 0);
    WinSendDlgItemMsg (hwnd, WID_CB_COPYRIGHT, BM_SETCHECK,
                       MPFROMLONG (QueryMP3 ()->IsCopyright ()), 0);
    WinSendDlgItemMsg (hwnd, WID_CB_PADDING, BM_SETCHECK,
                       MPFROMLONG (QueryMP3 ()->HasPadding ()), 0);
    WinSendDlgItemMsg (hwnd, WID_CB_ORIGINAL, BM_SETCHECK,
                       MPFROMLONG (QueryMP3 ()->IsOriginal ()), 0);

    // set title of group
    if (QueryMP3 ()->HasValidHeader ())
    {
        WinSetWindowText (WinWindowFromID (hwnd, WID_G_FILEINFO),
#ifdef _MULTILANGUAGES_
                          RSTR (IDS_FILEINFOGROUPNAME)
#else
                          "File info"
#endif
                         );
    }
    else
    {
        WinSetWindowText (WinWindowFromID (hwnd, WID_G_FILEINFO),
#ifdef _MULTILANGUAGES_
                          RSTR (IDS_FILEINFOGROUPNAMEINVALID)
#else
                          "File info (probably incorrect)"
#endif
                         );
    }
}

// ** RefreshTagGroup ***************************************************** /*fold00*/

VOID MP3DISPLAY :: RefreshTagGroup (VOID)
{
    if (! hwnd)
        return;

    if (! QueryMP3 ())
    {
        // clear out tag entry fields
        WinSetWindowText (WinWindowFromID (hwnd, WID_E_TITLE), NULL);
        WinSetWindowText (WinWindowFromID (hwnd, WID_E_ARTIST), NULL);
        WinSetWindowText (WinWindowFromID (hwnd, WID_E_ALBUM), NULL);
        WinSetWindowText (WinWindowFromID (hwnd, WID_E_YEAR), NULL);
        WinSetWindowText (WinWindowFromID (hwnd, WID_E_COMMENT), NULL);

        WinSendDlgItemMsg (hwnd, WID_DDL_GENRE, LM_SELECTITEM,
                           MPFROMLONG (0L), MPFROMLONG (TRUE));
        WinSendDlgItemMsg (hwnd, WID_DDL_GENRE, CBM_SHOWLIST, FALSE, 0);

        WinSendDlgItemMsg (hwnd, WID_SB_TRACK, SPBM_SETCURRENTVALUE,
                           MPFROMLONG (0), 0);

        // disable tag entry fields
        if (pset->OnlyReadOnly ())
        {
            WinSendMsg (WinWindowFromID (hwnd, WID_E_TITLE), EM_SETREADONLY,
                        MPFROMSHORT (TRUE), 0);
            WinSendMsg (WinWindowFromID (hwnd, WID_E_ARTIST), EM_SETREADONLY,
                        MPFROMSHORT (TRUE), 0);
            WinSendMsg (WinWindowFromID (hwnd, WID_E_ALBUM), EM_SETREADONLY,
                        MPFROMSHORT (TRUE), 0);
            WinSendMsg (WinWindowFromID (hwnd, WID_E_YEAR), EM_SETREADONLY,
                        MPFROMSHORT (TRUE), 0);
            WinSendMsg (WinWindowFromID (hwnd, WID_E_COMMENT), EM_SETREADONLY,
                        MPFROMSHORT (TRUE), 0);
        }
        else
        {
            WinEnableWindow (WinWindowFromID (hwnd, WID_E_TITLE), FALSE);
            WinEnableWindow (WinWindowFromID (hwnd, WID_E_ARTIST), FALSE);
            WinEnableWindow (WinWindowFromID (hwnd, WID_E_ALBUM), FALSE);
            WinEnableWindow (WinWindowFromID (hwnd, WID_E_YEAR), FALSE);
            WinEnableWindow (WinWindowFromID (hwnd, WID_E_COMMENT), FALSE);
        }
        WinEnableWindow (WinWindowFromID (hwnd, WID_DDL_GENRE), FALSE);
        WinEnableWindow (WinWindowFromID (hwnd, WID_SB_TRACK), FALSE);

        // set title of group
        WinSetWindowText (WinWindowFromID (hwnd, WID_G_TAG),
#ifdef _MULTILANGUAGES_
                          RSTR (IDS_NOFILENOTAG));
#else
                          "No file, no tag!");
#endif
        return;
    }

    if (QueryMP3 ()->IsTagged () && !QueryMP3 ()->HasUnsupportedTag ())
    {
        // set text of tag entry fields
        if (! pset->KeepTagInfo () || ! pset->Keep (KEEP_TITLE) ||
            (pset->OnlyIfMissing () && (strlen (QueryMP3 ()->QueryTitle ())
                                        > 0))
            || QueryMP3 ()->IsReadOnly () || fNoKeep)
            WinSetWindowText (WinWindowFromID (hwnd, WID_E_TITLE),
                              QueryMP3 ()->QueryTitle ());

        if (! pset->KeepTagInfo () || ! pset->Keep (KEEP_ARTIST) ||
            (pset->OnlyIfMissing () && (strlen (QueryMP3 ()->QueryArtist ())
                                        > 0))
            || QueryMP3 ()->IsReadOnly () || fNoKeep)
            WinSetWindowText (WinWindowFromID (hwnd, WID_E_ARTIST),
                              QueryMP3 ()->QueryArtist ());

        if (! pset->KeepTagInfo () || ! pset->Keep (KEEP_ALBUM) ||
            (pset->OnlyIfMissing () && (strlen (QueryMP3 ()->QueryAlbum ())
                                        > 0))
            || QueryMP3 ()->IsReadOnly () || fNoKeep)
            WinSetWindowText (WinWindowFromID (hwnd, WID_E_ALBUM),
                              QueryMP3 ()->QueryAlbum ());

        if (! pset->KeepTagInfo () || ! pset->Keep (KEEP_COMMENT) ||
            (pset->OnlyIfMissing () && (strlen (QueryMP3 ()->QueryComment ())
                                        > 0))
            || QueryMP3 ()->IsReadOnly () || fNoKeep)
            WinSetWindowText (WinWindowFromID (hwnd, WID_E_COMMENT),
                              QueryMP3 ()->QueryComment ());

        if (! pset->KeepTagInfo () || ! pset->Keep (KEEP_YEAR) ||
            (pset->OnlyIfMissing () && (strlen (QueryMP3 ()->QueryYear ())
                                        > 0))
            || QueryMP3 ()->IsReadOnly () || fNoKeep)
            WinSetWindowText (WinWindowFromID (hwnd, WID_E_YEAR),
                              QueryMP3 ()->QueryYear ());

        if (! pset->KeepTagInfo () || ! pset->Keep (KEEP_GENRE) ||
            (pset->OnlyIfMissing () && (QueryMP3 ()->QueryGenre ()
                                        != GENREID_NIL))
            || QueryMP3 ()->IsReadOnly () || fNoKeep)
            SetGenre (QueryMP3 ()->QueryGenre ());

        if (! pset->KeepTagInfo () || ! pset->AdjustTrack () ||
            (pset->OnlyIfMissing () && (QueryMP3 ()->QueryTrack () != 0))
            || QueryMP3 ()->IsReadOnly () || fNoKeep)
        {
            WinSendDlgItemMsg (hwnd, WID_SB_TRACK, SPBM_SETCURRENTVALUE,
                               MPFROMLONG (ULONG (QueryMP3 ()->QueryTrack ())),
                               0);
            cTrack = QueryMP3 ()->QueryTrack ();
        }
        else
            WinSendDlgItemMsg (hwnd, WID_SB_TRACK, SPBM_SETCURRENTVALUE,
                               MPFROMLONG (ULONG (cTrack)), 0);

        // set title of tag group
        CHAR   ach[81];
        if (QueryMP3 ()->IsReadOnly ())
            sprintf (ach,
#ifdef _MULTILANGUAGES_
                     RSTR (IDS_ID3TAGREADONLY)
#else
                     "ID3-tag v%s (read only)"
#endif
                     , QueryMP3 ()->QueryTagVersion ());
        else
            sprintf (ach,
#ifdef _MULTILANGUAGES_
                     RSTR (IDS_ID3TAG)
#else
                     "ID3-tag v%s"
#endif
                     , QueryMP3 ()->QueryTagVersion ());
        WinSetWindowText (WinWindowFromID (hwnd, WID_G_TAG), ach);
    }
    else
    {
        // clear out tag entry fields
        if (! pset->KeepTagInfo () || ! pset->Keep (KEEP_TITLE)
            || QueryMP3 ()->IsReadOnly () || fNoKeep)
            WinSetWindowText (WinWindowFromID (hwnd, WID_E_TITLE), NULL);
        if (! pset->KeepTagInfo () || ! pset->Keep (KEEP_ARTIST)
            || QueryMP3 ()->IsReadOnly () || fNoKeep)
            WinSetWindowText (WinWindowFromID (hwnd, WID_E_ARTIST), NULL);
        if (! pset->KeepTagInfo () || ! pset->Keep (KEEP_ALBUM)
            || QueryMP3 ()->IsReadOnly () || fNoKeep)
            WinSetWindowText (WinWindowFromID (hwnd, WID_E_ALBUM), NULL);
        if (! pset->KeepTagInfo () || ! pset->Keep (KEEP_YEAR)
            || QueryMP3 ()->IsReadOnly () || fNoKeep)
            WinSetWindowText (WinWindowFromID (hwnd, WID_E_YEAR), NULL);
        if (! pset->KeepTagInfo () || ! pset->Keep (KEEP_COMMENT)
            || QueryMP3 ()->IsReadOnly () || fNoKeep)
            WinSetWindowText (WinWindowFromID (hwnd, WID_E_COMMENT), NULL);

        if (! pset->KeepTagInfo () || ! pset->Keep (KEEP_GENRE)
            || QueryMP3 ()->IsReadOnly () || fNoKeep)
        {
            WinSendDlgItemMsg (hwnd, WID_DDL_GENRE, LM_SELECTITEM,
                               MPFROMLONG (0L), MPFROMLONG (TRUE));
            WinSendDlgItemMsg (hwnd, WID_DDL_GENRE, CBM_SHOWLIST, FALSE, 0);
        }

        if (! pset->KeepTagInfo () || ! pset->AdjustTrack ()
            || QueryMP3 ()->IsReadOnly () || fNoKeep)
            WinSendDlgItemMsg (hwnd, WID_SB_TRACK, SPBM_SETCURRENTVALUE,
                               MPFROMLONG (0), 0);
        else
            WinSendDlgItemMsg (hwnd, WID_SB_TRACK, SPBM_SETCURRENTVALUE,
                               MPFROMLONG (ULONG (cTrack)), 0);

        // set title of tag group
        if (QueryMP3 ()->HasUnsupportedTag ())
        {
            CHAR   ach[81];
            sprintf (ach, RSTR (IDS_FILEHASUNSUPPORTEDTAG),
                     QueryMP3 ()->QueryTagVersion ());
            WinSetWindowText (WinWindowFromID (hwnd, WID_G_TAG), ach);
        }
        else
        {
            if (QueryMP3 ()->IsReadOnly ())
                WinSetWindowText (WinWindowFromID (hwnd, WID_G_TAG),
                                  RSTR (IDS_FILEHASNOTAGREADONLY));
            else
                WinSetWindowText (WinWindowFromID (hwnd, WID_G_TAG),
                                  RSTR (IDS_FILEHASNOTAG));
        }
    }

    if (QueryMP3 ()->IsReadOnly () || QueryMP3 ()->HasUnsupportedTag ())
    {
        // disable tag entry fields
        if (pset->OnlyReadOnly ())
        {
            WinSendMsg (WinWindowFromID (hwnd, WID_E_TITLE), EM_SETREADONLY,
                        MPFROMSHORT (TRUE), 0);
            WinSendMsg (WinWindowFromID (hwnd, WID_E_ARTIST), EM_SETREADONLY,
                        MPFROMSHORT (TRUE), 0);
            WinSendMsg (WinWindowFromID (hwnd, WID_E_ALBUM), EM_SETREADONLY,
                        MPFROMSHORT (TRUE), 0);
            WinSendMsg (WinWindowFromID (hwnd, WID_E_YEAR), EM_SETREADONLY,
                        MPFROMSHORT (TRUE), 0);
            WinSendMsg (WinWindowFromID (hwnd, WID_E_COMMENT), EM_SETREADONLY,
                        MPFROMSHORT (TRUE), 0);
            // FIXME this stuff is all not pretty good, but for now ...
            WinEnableWindow (WinWindowFromID (hwnd, WID_E_TITLE), TRUE);
            WinEnableWindow (WinWindowFromID (hwnd, WID_E_ARTIST), TRUE);
            WinEnableWindow (WinWindowFromID (hwnd, WID_E_ALBUM), TRUE);
            WinEnableWindow (WinWindowFromID (hwnd, WID_E_YEAR), TRUE);
            WinEnableWindow (WinWindowFromID (hwnd, WID_E_COMMENT), TRUE);
        }
        else
        {
            WinSendMsg (WinWindowFromID (hwnd, WID_E_TITLE), EM_SETREADONLY,
                        MPFROMSHORT (FALSE), 0);
            WinSendMsg (WinWindowFromID (hwnd, WID_E_ARTIST), EM_SETREADONLY,
                        MPFROMSHORT (FALSE), 0);
            WinSendMsg (WinWindowFromID (hwnd, WID_E_ALBUM), EM_SETREADONLY,
                        MPFROMSHORT (FALSE), 0);
            WinSendMsg (WinWindowFromID (hwnd, WID_E_YEAR), EM_SETREADONLY,
                        MPFROMSHORT (FALSE), 0);
            WinSendMsg (WinWindowFromID (hwnd, WID_E_COMMENT), EM_SETREADONLY,
                        MPFROMSHORT (FALSE), 0);

            WinEnableWindow (WinWindowFromID (hwnd, WID_E_TITLE), FALSE);
            WinEnableWindow (WinWindowFromID (hwnd, WID_E_ARTIST), FALSE);
            WinEnableWindow (WinWindowFromID (hwnd, WID_E_ALBUM), FALSE);
            WinEnableWindow (WinWindowFromID (hwnd, WID_E_YEAR), FALSE);
            WinEnableWindow (WinWindowFromID (hwnd, WID_E_COMMENT), FALSE);
        }
        WinEnableWindow (WinWindowFromID (hwnd, WID_DDL_GENRE), FALSE);
        WinEnableWindow (WinWindowFromID (hwnd, WID_SB_TRACK), FALSE);
    }
    else
    {
        // enable tag entry fields
        WinSendMsg (WinWindowFromID (hwnd, WID_E_TITLE), EM_SETREADONLY,
                    MPFROMSHORT (FALSE), 0);
        WinSendMsg (WinWindowFromID (hwnd, WID_E_ARTIST), EM_SETREADONLY,
                    MPFROMSHORT (FALSE), 0);
        WinSendMsg (WinWindowFromID (hwnd, WID_E_ALBUM), EM_SETREADONLY,
                    MPFROMSHORT (FALSE), 0);
        WinSendMsg (WinWindowFromID (hwnd, WID_E_YEAR), EM_SETREADONLY,
                    MPFROMSHORT (FALSE), 0);
        WinSendMsg (WinWindowFromID (hwnd, WID_E_COMMENT), EM_SETREADONLY,
                    MPFROMSHORT (FALSE), 0);

        WinEnableWindow (WinWindowFromID (hwnd, WID_E_TITLE), TRUE);
        WinEnableWindow (WinWindowFromID (hwnd, WID_E_ARTIST), TRUE);
        WinEnableWindow (WinWindowFromID (hwnd, WID_E_ALBUM), TRUE);
        WinEnableWindow (WinWindowFromID (hwnd, WID_E_YEAR), TRUE);
        WinEnableWindow (WinWindowFromID (hwnd, WID_E_COMMENT), TRUE);

        WinEnableWindow (WinWindowFromID (hwnd, WID_DDL_GENRE), TRUE);
        WinEnableWindow (WinWindowFromID (hwnd, WID_SB_TRACK), TRUE);
    }

    if (pset->FilenameToTitle () && !QueryMP3 ()->HasUnsupportedTag ())
    {
        CHAR   ach[_MAX_PATH];
        PSZ    psz;

        if (WinQueryWindowText (WinWindowFromID (hwnd, WID_E_TITLE),
                                MAXLEN_TITLE, ach) <= 1)
        {
            strcpy (ach, QueryMP3 ()->QueryFilename ().c_str ());
            if ((psz = _getext (ach)))
                *psz = '\0';
            psz = _getname (ach);
            WinSetWindowText (WinWindowFromID (hwnd, WID_E_TITLE), psz);
        }
    }
}

// ** RefreshButtons ****************************************************** /*fold00*/

VOID MP3DISPLAY :: RefreshButtons (VOID)
{
    if (! hwnd)
        return;

    if (! QueryMP3 ())
    {
        // disable buttons
        EnableSave (FALSE);
        EnableSaveAll (FALSE);
        EnableSaveNext (FALSE);
        EnableSavePrev (FALSE);
        EnableRemove (FALSE);
        EnableRemoveAll (FALSE);
        EnableList (FALSE);
        EnableDeleteFromList (FALSE);
        EnableDeleteAllFromList (FALSE);
        EnableRenameAll (FALSE);
        EnableCut (FALSE);
        EnableCopy (FALSE);
        EnablePaste (FALSE);
        return;
    }

    EnableRenameAll ();
    EnableList ();
    EnableDeleteFromList ();
    EnableDeleteAllFromList ();
    EnableCut ();
    EnableCopy ();
    EnablePaste ();

    if (CountFilesInList () > 1)
    {
        EnableRemoveAll ();
        EnableSaveAll ();
        // FIXME this two maybe only if not read only?
        EnableSaveNext ();
        EnableSavePrev ();
    }
    else
    {
        EnableRemoveAll (FALSE);
        EnableSaveAll (FALSE);
        // FIXME this two maybe only if not read only?
        EnableSaveNext (FALSE);
        EnableSavePrev (FALSE);
    }

    if (QueryMP3 ()->IsReadOnly ())
    {
        EnableSave (FALSE);
        EnableRemove (FALSE);
    }
    else
    {
        EnableSave ();
        if (QueryMP3 ()->IsTagged ())
            EnableRemove ();
        else
            EnableRemove (FALSE);
    }
}

// ** SetGenre ************************************************************ /*fold00*/

VOID MP3DISPLAY :: SetGenre (USHORT us)
{
    ULONG    ul = ULONG (WinSendDlgItemMsg (hwnd, WID_DDL_GENRE,
                                            LM_QUERYITEMCOUNT, 0,0));
    ULONG    i;

    // first one must be ignored, is "(none)"
    for (i = 1L; i < ul; i++)
        if (pmp3->QueryGenre () == USHORT
            (WinSendDlgItemMsg (hwnd, WID_DDL_GENRE, LM_QUERYITEMHANDLE,
                                MPFROMLONG (i), 0L)))
            break;
    /*    DisplayError ("DEBUG", "%ld %u :%u", i,
                  USHORT (WinSendDlgItemMsg (hwnd, WID_DDL_GENRE,
                                             LM_QUERYITEMHANDLE,
                                             MPFROMLONG (i), 0L)),
                  pmp3->QueryGenre ()); */

    if (i == ul)
        i = 0L;

    WinSendDlgItemMsg (hwnd, WID_DDL_GENRE, LM_SELECTITEM,
                       MPFROMLONG (i), MPFROMLONG (TRUE));
    WinSendDlgItemMsg (hwnd, WID_DDL_GENRE, CBM_SHOWLIST,
                       FALSE, 0);
}

// ** AdjustFilelistTitle ************************************************* /*fold00*/

VOID MP3DISPLAY :: AdjustFilelistTitle (VOID)
{
    if (! hwnd)
        return;

    CHAR   ach[41];

    // set title of file-list-border
    if (CountFilesInList () == 0)
#ifdef _MULTILANGUAGES_
        strcpy (ach, RSTR (IDS_NOFILESSELECTED));
#else
        strcpy (ach, "No files selected");
#endif
    else if (CountFilesInList () == 1)
#ifdef _MULTILANGUAGES_
        strcpy (ach, RSTR (IDS_ONEFILESELECTED));
#else
        strcpy (ach, "1 file selected");
#endif
    else
#ifdef _MULTILANGUAGES_
        sprintf (ach, RSTR (IDS_FILESSELECTED), CountFilesInList ());
#else
        sprintf (ach, "%lu files selected", CountFilesInList ());
#endif
    WinSetWindowText (WinWindowFromID (hwnd, WID_G_FILES), ach);
}

// ** QueryFile *********************************************************** /*fold00*/

VOID MP3DISPLAY :: QueryFile (PCHAR psz, USHORT us)
{
    if (! hwnd)
        return;

    ULONG ul = USHORT (WinSendDlgItemMsg (hwnd, WID_DDL_FILES,
                                          LM_QUERYSELECTION,
                                          MPFROMLONG (LIT_FIRST), 0L));
    QueryFile (psz, us, ul);
}

VOID MP3DISPLAY :: QueryFile (PCHAR psz, USHORT us, ULONG ulPos)
{
    if (! hwnd)
        return;

    WinSendDlgItemMsg (hwnd, WID_DDL_FILES, LM_QUERYITEMTEXT,
                       MPFROM2SHORT (ulPos, us), MPFROMP (psz));
}

// ** AdjustCurrent ******************************************************* /*fold00*/

VOID MP3DISPLAY :: AdjustCurrent (BOOL fAlwaysChange)
{
    CHAR   ach[81];  // FIXME length should be maximum of tag-fields lengths'

    WinQueryWindowText (WinWindowFromID (hwnd, WID_E_TITLE),
                        MAXLEN_TITLE+1, ach);
    if ((strlen (ach) > 0) || fAlwaysChange)
        QueryMP3 ()->SetTitle (ach);

    WinQueryWindowText (WinWindowFromID (hwnd, WID_E_ARTIST),
                        MAXLEN_ARTIST+1, ach);
    if ((strlen (ach) > 0) || fAlwaysChange)
        QueryMP3 ()->SetArtist (ach);

    WinQueryWindowText (WinWindowFromID (hwnd, WID_E_ALBUM),
                        MAXLEN_ALBUM+1, ach);
    if ((strlen (ach) > 0) || fAlwaysChange)
        QueryMP3 ()->SetAlbum (ach);

    WinQueryWindowText (WinWindowFromID (hwnd, WID_E_COMMENT),
                        MAXLEN_COMMENT+1, ach);
    if ((strlen (ach) > 0) || fAlwaysChange)
        QueryMP3 ()->SetComment (ach);

    WinQueryWindowText (WinWindowFromID (hwnd, WID_E_YEAR),
                        MAXLEN_YEAR+1, ach);
    if ((strlen (ach) > 0) || fAlwaysChange)
        QueryMP3 ()->SetYear (ach);

    // adjust genre
    ULONG ul = ULONG
        (WinSendDlgItemMsg (hwnd, WID_DDL_GENRE, LM_QUERYSELECTION,
                            MPFROMLONG (LIT_FIRST), 0L));
    USHORT us = USHORT (WinSendDlgItemMsg (hwnd, WID_DDL_GENRE,
                                           LM_QUERYITEMHANDLE,
                                           MPFROMSHORT (ul), 0L));
    // a genre was selected from the list: set this
    if (us != GENREID_NIL)
        QueryMP3 ()->SetGenre (us);
    // genre "(none)" and no genre from tag to "keep", so set default
    else if (! QueryMP3 ()->IsTagged ())
        QueryMP3 ()->SetGenre (GENREID_DEFAULT);

    // set track
    if (! BOOL (WinSendDlgItemMsg (hwnd, WID_SB_TRACK, SPBM_QUERYVALUE,
                                   MPFROMP (&us), MPFROM2SHORT (0, 0))))
        us = 0;
    if ((us > 0) || fAlwaysChange)
    {
        QueryMP3 ()->SetTrack (us);
        cTrack = QueryMP3 ()->QueryTrack ();
    }
}

// ** SaveCurrent ********************************************************* /*fold00*/

VOID MP3DISPLAY :: SaveCurrent (BOOL fAlwaysChange)
{
#ifdef _DEBUGLOG_
    fputs ("\nSaveCurrent ()\n", pfileLog);
#endif

    if (!hwnd || !QueryMP3 ())
        return;

    AdjustCurrent (fAlwaysChange);
    QueryMP3 ()->SaveTag ();
    Refresh ();
}

// ** ShowButtons ********************************************************* /*fold00*/

USHORT idButtons[] =
{
    WID_PB_FILES,
    WID_PB_SAVE,
    WID_PB_SAVEALL,
    WID_PB_REMOVE,
    WID_PB_REMOVEALL,
    WID_PB_LIST,
    WID_PB_ABOUT,
    WID_PB_HELP,
    WID_PB_EXIT,
    0
};

USHORT idButtonsRemain[] =
{
    WID_PB_SAVE,
    WID_PB_REMOVE,
    WID_PB_ABOUT,
    WID_PB_HELP,
    WID_PB_EXIT,
    0
};

VOID MP3DISPLAY :: ShowButtons (BOOL f)
{
    SWP   swp;

    WinQueryWindowPos (WinWindowFromID (hwnd, WID_PB_FILES), &swp);

    SHORT   s, i;

    if (! f)
    {
        WinCheckMenuItem (QueryHWNDMenu (), WID_PB_SHOWBUTTONS, FALSE);
        s = -swp.cx-12;
    }
    else
    {
        WinCheckMenuItem (QueryHWNDMenu (), WID_PB_SHOWBUTTONS, TRUE);
        s = +swp.cx+12;
    }

    if (pset->ShowFileinfo ())
    {
        // hide/show all buttons
        for (i = 0; idButtons[i]; i++)
            WinShowWindow (WinWindowFromID (hwnd, idButtons[i]), f);
    }
    else
    {
        // hide/show only some of them
        for (i = 0; idButtonsRemain[i]; i++)
            WinShowWindow (WinWindowFromID (hwnd, idButtonsRemain[i]), f);
    }

    WinQueryWindowPos (hwnd, &swp);
    WinSetWindowPos (hwnd, HWND_DESKTOP, 0,0, swp.cx+s,swp.cy,
                     SWP_SIZE);
}

// ** ShowFileinfo ******************************************************** /*fold00*/

#ifdef _SHOWFILEINFO_

USHORT idFileinfo[] =
{
    WID_G_FILEINFO,
    WID_ST_VERSION,
    WID_E_VERSION,
    WID_ST_LAYER,
    WID_E_LAYER,
    WID_ST_FREQUENCY,
    WID_E_FREQUENCY,
    WID_ST_BITRATE,
    WID_E_BITRATE,
    WID_ST_MODE,
    WID_E_MODE,
    WID_ST_MODE,
    WID_E_MODE,
    WID_ST_EMPHASIS,
    WID_E_EMPHASIS,
    WID_ST_TIME,
    WID_E_TIME,
    WID_CB_ORIGINAL,
    WID_CB_PRIVATE,
    WID_CB_COPYRIGHT,
    WID_CB_CRCS,
    WID_CB_PADDING,
    0
};

USHORT idFilelist[] =
{
    WID_G_FILES,
    WID_DDL_FILES,
    0
};

USHORT idTaginfo[] =
{
    WID_G_TAG,
    WID_ST_TITLE,
    WID_E_TITLE,
    WID_ST_ARTIST,
    WID_E_ARTIST,
    WID_ST_ALBUM,
    WID_E_ALBUM,
    WID_ST_YEAR,
    WID_E_YEAR,
    WID_ST_GENRE,
    WID_DDL_GENRE,
    WID_ST_COMMENT,
    WID_E_COMMENT,
    WID_ST_TRACK,
    WID_SB_TRACK,
    0
};

USHORT idButtonsHide[] =
{
    WID_PB_FILES,
    WID_PB_SAVEALL,
    WID_PB_REMOVEALL,
    WID_PB_LIST,
    0
};

VOID MP3DISPLAY :: ShowFileinfo (BOOL f)
{
    SWP   swp;

    WinQueryWindowPos (WinWindowFromID (hwnd, WID_G_FILEINFO), &swp);

    SHORT   s, i;

    if (! f)
    {
        WinCheckMenuItem (QueryHWNDMenu (), WID_PB_SHOWFILEINFO, FALSE);
        s = -swp.cy-12;
    }
    else
    {
        WinCheckMenuItem (QueryHWNDMenu (), WID_PB_SHOWFILEINFO, TRUE);
        s = +swp.cy+12;
    }

    // hide all fileinfo windows
    for (i = 0; idFileinfo[i]; i++)
        WinShowWindow (WinWindowFromID (hwnd, idFileinfo[i]), f);

    // if buttons shown hide some
    for (i = 0; idButtonsHide[i]; i++)
        WinShowWindow (WinWindowFromID (hwnd, idButtonsHide[i]), f);

    // shift some buttons (FIXME yet more yukki stuff)
    if (f)
    {
        WinSetWindowPos (WinWindowFromID (hwnd, WID_PB_SAVE), hwnd,
                         swpSave[0].x,swpSave[0].y, 0,0, SWP_MOVE);
        WinSetWindowPos (WinWindowFromID (hwnd, WID_PB_REMOVE), hwnd,
                         swpSave[1].x,swpSave[1].y, 0,0, SWP_MOVE);
    }
    else
    {
        WinQueryWindowPos (WinWindowFromID (hwnd, WID_PB_REMOVEALL), &swp);
        WinSetWindowPos (WinWindowFromID (hwnd, WID_PB_SAVE), hwnd,
                         swp.x,swp.y, 0,0, SWP_MOVE);
        WinQueryWindowPos (WinWindowFromID (hwnd, WID_PB_LIST), &swp);
        WinSetWindowPos (WinWindowFromID (hwnd, WID_PB_REMOVE), hwnd,
                         swp.x,swp.y, 0,0, SWP_MOVE);
    }

/*    for (i = 0; idButtonsShift[i]; i++)
    {
        WinQueryWindowPos (WinWindowFromID (hwnd, idButtonsShift[i]), &swp);
        swp.y += s;
        WinSetWindowPos (WinWindowFromID (hwnd, idButtonsShift[i]), hwnd,
                         swp.x,swp.y, 0,0, SWP_MOVE);
    } */

    // shift all filelist windows
    for (i = 0; idFilelist[i]; i++)
    {
        WinQueryWindowPos (WinWindowFromID (hwnd, idFilelist[i]), &swp);
        swp.y += s;
        WinSetWindowPos (WinWindowFromID (hwnd, idFilelist[i]), hwnd,
                         swp.x,swp.y, 0,0, SWP_MOVE);
    }

    WinQueryWindowPos (hwnd, &swp);
    WinSetWindowPos (hwnd, HWND_DESKTOP, 0,0, swp.cx,swp.cy+s,
                     SWP_SIZE);
}

#endif

// ** NotificationAutoOpen ************************************************ /*fold00*/

VOID MP3DISPLAY :: NotificationAutoOpen (ULONG l)
{
#ifdef _MULTILANGUAGES_
    // some notification msg for the user
    if (l > 1)
        Notify (RSTR (IDS_FILESINSERTEDHEADING),
                RSTR (IDS_FILESWEREINSERTED), l);
    else if (l == 1)
        Notify (RSTR (IDS_FILESINSERTEDHEADING),
                RSTR (IDS_ONEFILEWASINSERTED), l);
    else
        Notify (RSTR (IDS_NOFILESFOUNDHEADING),
                RSTR (IDS_NONEWFILESWEREFOUND));
#else
    // some notification msg for the user
    if (l > 1)
        Notify ("FILES INSERTED",
                "%ld new MP3 files from the directory and its "
                "subdirectories have been inserted into the list.", l);
    else if (l == 1)
        Notify ("FILE INSERTED",
                "One new MP3 file has been found and was inserted into "
                "the list.");
    else
        Notify ("NO FILES FOUND",
                "No new MP3 files could be found in the directory and "
                "its subdirectories.");
#endif
}

#ifdef _PLAYERCOMMAND_

// ** LaunchPlayer ******************************************************** /*fold00*/

VOID MP3DISPLAY :: LaunchPlayer (VOID)
{
    CHAR   ach[MAXLEN_PLAYERCOMMAND+_MAX_FNAME+21];
    PSZ    psz = strstr (pset->QueryPlayerCommand (), PSZ_PCFILEMACRO), psz2;

//    strcpy (ach, "start /I ");
//    strcpy (ach, "start /F ");
    strcpy (ach, "start /I /C ");
    psz2 = ach+strlen (ach);

    if (psz)
    {
        USHORT   us = USHORT (psz - pset->QueryPlayerCommand ());

        // copy part of command before filename to ach
        strncpy (psz2, pset->QueryPlayerCommand (), us);
        psz2[us] = '\0';
        // copy filename to ach
        QueryFile (psz2+us, _MAX_FNAME);
        // copy part of command after filename to ach
        strcat (psz2, psz+2);
    }
    else
        strcpy (psz2, pset->QueryPlayerCommand ());

    /*                if ((psz = strchr (ach, ' ')))
     *psz = '\0'; */

    delete QueryMP3 ();
    SetMP3 (NULL);

    SHORT   rc;

    if ((rc = system (ach)) == -1)
        DisplayError (RSTR (IDS_ERROR_GENERALHEADING),
                      RSTR (IDS_ERROR_LAUNCHFAILED), ach, errno);

    // reload the current file and refresh the display
    SetMP3 (NULL);
    Refresh ();
}

// ************************************************************************
#endif
