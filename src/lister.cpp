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

#include "lister.h"

extern PSZ agnr[MAX_GENRES];

#ifdef _NEWLISTER_

#ifndef _MULTILANGUAGES_
PSZ apszInc[] = {
    "Title", "Time", "Artist", "Album", "Year", "Genre", "Comment",
    "Filename & path", "Version", "Layer", "Frequency", "Bitrate", "Mode" };
#else
PSZ apszInc[13];
#endif

#endif

// ** Dialog ************************************************************** /*fold00*/

BOOL LISTER :: Dialog (VOID)
{
    hwnd =
        WinLoadDlg (HWND_DESKTOP, pmp3d->hwnd, DialogProcedure,
                    GETMODULE, ID_DLG_LISTER, this);
    WinSetAccelTable (hab, WinLoadAccelTable (hab, GETMODULE, ID_DLG_LISTER),
                      hwnd);
    ULONG   ul = WinProcessDlg (hwnd);
    WinDestroyWindow (hwnd);
    hwnd = NULLHANDLE;

    return (BOOL (ul));
}

// ** DialogProcedure ***************************************************** /*fold00*/

MRESULT EXPENTRY
LISTER :: DialogProcedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    static CHAR     psz[_MAX_PATH];
    static BOOL     f = FALSE;
    static PLISTER  plist = NULL;

    switch (msg)
    {
    case WM_INITDLG:
        plist = PLISTER (mp2);

#ifdef _NEWLISTER_
        for (USHORT i = 0; i < LINC_MAX-LINC_ADDITIONAL; i++)
        {
            WinSendDlgItemMsg (hwnd, WID_LB_INCLUDE, LM_INSERTITEM,
                               MPFROMLONG (i), apszInc[i]);
            if (plist->Include (i))
                WinSendDlgItemMsg (hwnd, WID_LB_INCLUDE, LM_SELECTITEM,
                                   MPFROMLONG (i), MPFROMLONG (TRUE));
        }
#else
        WinSendDlgItemMsg (hwnd, WID_CB_TITLE, BM_SETCHECK,
                           MPFROMLONG (plist->IncludeTitle ()), MPFROMLONG (0));
        WinSendDlgItemMsg (hwnd, WID_CB_ARTIST, BM_SETCHECK,
                           MPFROMLONG (plist->IncludeArtist ()), MPFROMLONG (0));
        WinSendDlgItemMsg (hwnd, WID_CB_ALBUM, BM_SETCHECK,
                           MPFROMLONG (plist->IncludeAlbum ()), MPFROMLONG (0));
        WinSendDlgItemMsg (hwnd, WID_CB_TIME, BM_SETCHECK,
                           MPFROMLONG (plist->IncludeTime ()), MPFROMLONG (0));
        WinSendDlgItemMsg (hwnd, WID_CB_YEAR, BM_SETCHECK,
                           MPFROMLONG (plist->IncludeYear ()), MPFROMLONG (0));
        WinSendDlgItemMsg (hwnd, WID_CB_COMMENT, BM_SETCHECK,
                           MPFROMLONG (plist->IncludeComment ()), MPFROMLONG (0));
        WinSendDlgItemMsg (hwnd, WID_CB_GENRE, BM_SETCHECK,
                           MPFROMLONG (plist->IncludeGenre ()), MPFROMLONG (0)); */
#endif
        WinSendDlgItemMsg (hwnd, WID_CB_OUTPUTHEADER, BM_SETCHECK,
                           MPFROMLONG (plist->IncludeHeader ()), MPFROMLONG (0));
        WinSendDlgItemMsg (hwnd, WID_CB_OUTPUTTIME, BM_SETCHECK,
                           MPFROMLONG (plist->IncludeTotalTime ()), MPFROMLONG (0));
        WinSendDlgItemMsg (hwnd, WID_CB_AUTOSIZE, BM_SETCHECK,
                           MPFROMLONG (plist->AutoSize ()), MPFROMLONG (0));
        WinSendDlgItemMsg (hwnd, WID_CB_ONLYTAGGED, BM_SETCHECK,
                           MPFROMLONG (plist->OnlyTagged ()), MPFROMLONG (0));

        WinSendDlgItemMsg (hwnd, WID_E_LISTFILENAME, EM_SETTEXTLIMIT,
                           (MPARAM)_MAX_PATH, (MPARAM)0);
        strcpy (psz, plist->QueryFilename ());
        WinSetDlgItemText (hwnd, WID_E_LISTFILENAME, psz);
        WinSendDlgItemMsg (hwnd, WID_E_LISTFILENAME, EM_SETSEL,
                           MPFROM2SHORT (0, _MAX_PATH), (MPARAM)0);
        return (MRESULT)FALSE;

    case WM_COMMAND:
        switch (COMMANDMSG (&msg)->cmd)
        {
        case WID_PB_OK:
            {
                USHORT cSelected = 0L;

                for (USHORT i = 0; i < LINC_MAX-LINC_ADDITIONAL; i++)
                    if (WinLboxIsSelectedItem
                        (WinWindowFromID (hwnd, WID_LB_INCLUDE), i))
                        cSelected ++;

                if (cSelected == 0)
                {
#ifdef _MULTILANGUAGES_
                    DisplayError (RSTR (IDS_ERROR_BORINGLISTHEADING),
                                  RSTR (IDS_ERROR_BORINGLIST));
#else
                    DisplayError ("THIS IS GONNA BE A BORING LIST ...",
                                  "You must select at least one item to be "
                                  "included in the list.");
#endif
                    break;
                }

                WinQueryDlgItemText (hwnd, WID_E_LISTFILENAME, _MAX_PATH, psz);
                if (strlen (psz) == 0)
                {
#ifdef _MULTILANGUAGES_
                    DisplayError (RSTR (IDS_ERROR_LISTFILEHEADING),
                                  RSTR (IDS_ERROR_MUSTGIVEVALIDLISTFILENAME));
#else
                    DisplayError ("NO LISTFILE",
                                  "You must give a valid listfile name");
#endif
                    break;
                }

                f = TRUE;
                WinSendMsg (hwnd, WM_CLOSE, NULL, NULL);
            }
            break;

        case WID_PB_CANCEL:
            f = FALSE;
            WinSendMsg (hwnd, WM_CLOSE, NULL, NULL);
            break;

        case WID_PB_FIND:
            if (plist->SelectFile ())
            {
                strcpy (psz, plist->QueryFilename ());
                WinSetDlgItemText (hwnd, WID_E_LISTFILENAME, psz);
            }
            break;
        }
        return (MRESULT)FALSE;

    case WM_CLOSE:
        /* adjust the settings */
#ifdef _NEWLISTER_
        //  get settings from page 1
        for (USHORT i = 0; i < LINC_MAX-LINC_ADDITIONAL; i++)
            if (WinLboxIsSelectedItem (WinWindowFromID (hwnd,
                                                        WID_LB_INCLUDE), i))
                plist->Include (i, INC_YES);
            else
                plist->Include (i, INC_NO);

/*        if (WinSendDlgItemMsg (hwnd, WID_CB_OVERWRITE, BM_QUERYCHECK,
                               MPFROMLONG (0), MPFROMLONG (0)))
            plist->Overwrite (TRUE);
        else
            plist->Overwrite (FALSE); */

#else
        if (WinSendDlgItemMsg (hwnd, WID_CB_TITLE, BM_QUERYCHECK,
                               MPFROMLONG (0), MPFROMLONG (0)))
            plist->IncludeTitle (INC_YES);
        else
            plist->IncludeTitle (INC_NO);
        
        if (WinSendDlgItemMsg (hwnd, WID_CB_TIME, BM_QUERYCHECK,
                               MPFROMLONG (0), MPFROMLONG (0)))
            plist->IncludeTime (INC_YES);
        else
            plist->IncludeTime (INC_NO);
        
        if (WinSendDlgItemMsg (hwnd, WID_CB_YEAR, BM_QUERYCHECK,
                               MPFROMLONG (0), MPFROMLONG (0)))
            plist->IncludeYear (INC_YES);
        else
            plist->IncludeYear (INC_NO);
        
        if (WinSendDlgItemMsg (hwnd, WID_CB_ALBUM, BM_QUERYCHECK,
                               MPFROMLONG (0), MPFROMLONG (0)))
            plist->IncludeAlbum (INC_YES);
        else
            plist->IncludeAlbum (INC_NO);

        if (WinSendDlgItemMsg (hwnd, WID_CB_COMMENT, BM_QUERYCHECK,
                               MPFROMLONG (0), MPFROMLONG (0)))
            plist->IncludeComment (INC_YES);
        else
            plist->IncludeComment (INC_NO);
            
        if (WinSendDlgItemMsg (hwnd, WID_CB_GENRE, BM_QUERYCHECK,
                               MPFROMLONG (0), MPFROMLONG (0)))
            plist->IncludeGenre (INC_YES);
        else
            plist->IncludeGenre (INC_NO);
            
        if (WinSendDlgItemMsg (hwnd, WID_CB_ARTIST, BM_QUERYCHECK,
                               MPFROMLONG (0), MPFROMLONG (0)))
            plist->IncludeArtist (INC_YES);
        else
            plist->IncludeArtist (INC_NO);
#endif

        if (WinSendDlgItemMsg (hwnd, WID_CB_OUTPUTHEADER, BM_QUERYCHECK,
                               MPFROMLONG (0), MPFROMLONG (0)))
            plist->IncludeHeader (INC_YES);
        else
            plist->IncludeHeader (INC_NO);
            
        if (WinSendDlgItemMsg (hwnd, WID_CB_OUTPUTTIME, BM_QUERYCHECK,
                               MPFROMLONG (0), MPFROMLONG (0)))
            plist->IncludeTotalTime (INC_YES);
        else
            plist->IncludeTotalTime (INC_NO);

        if (WinSendDlgItemMsg (hwnd, WID_CB_AUTOSIZE, BM_QUERYCHECK,
                               MPFROMLONG (0), MPFROMLONG (0)))
            plist->AutoSize (TRUE);
        else
            plist->AutoSize (FALSE);

        if (WinSendDlgItemMsg (hwnd, WID_CB_ONLYTAGGED, BM_QUERYCHECK,
                               MPFROMLONG (0), MPFROMLONG (0)))
            plist->OnlyTagged (TRUE);
        else
            plist->OnlyTagged (FALSE);

        plist->SetFilename (psz);

        WinDismissDlg (hwnd, (ULONG) f);
        return (MRESULT)FALSE;
    }

    return (WinDefDlgProc (hwnd, msg, mp1, mp2));
}


// ** OutputList ********************************************************** /*fold00*/

VOID LISTER :: OutputList (VOID)
{
    PMP3       pmp3;
    fstream    *pos = NULL;
    ULONG      ulTime = 0L;
    HPOINTER   hptr = WinQueryPointer (HWND_DESKTOP);

    // set mouse-ptr to "wait" shape
    WinSetPointer (HWND_DESKTOP, WinQuerySysPointer (HWND_DESKTOP, SPTR_WAIT,
                                                     FALSE));

    // check for max. length of the different infos
    CHAR    ach[_MAX_PATH], ach2[_MAX_PATH+31];
    ULONG   ul = ULONG (WinSendDlgItemMsg (pmp3d->hwnd, WID_DDL_FILES,
                                           LM_QUERYITEMCOUNT, 0,0));

    // set maxlens so that the headers will fit
    usMaxLen[TAG_TITLE]   = strlen (RSTR (IDS_LISTTITLE));
    usMaxLen[TAG_TIME]    = strlen (RSTR (IDS_LISTTIME));
    usMaxLen[TAG_ARTIST]  = strlen (RSTR (IDS_LISTARTIST));
    usMaxLen[TAG_ALBUM]   = strlen (RSTR (IDS_LISTALBUM));
    usMaxLen[TAG_GENRE]   = strlen (RSTR (IDS_LISTGENRE));
    usMaxLen[TAG_YEAR]    = strlen (RSTR (IDS_LISTYEAR));
    usMaxLen[TAG_COMMENT] = strlen (RSTR (IDS_LISTCOMMENT));
    usMaxLen[TAG_VERSION] = strlen (RSTR (IDS_LISTVERSION));
    usMaxLen[TAG_LAYER]   = strlen (RSTR (IDS_LISTLAYER));
    usMaxLen[TAG_FREQ]    = strlen (RSTR (IDS_LISTFREQUENCY));
    usMaxLen[TAG_BITRATE] = strlen (RSTR (IDS_LISTBITRATE));
    usMaxLen[TAG_MODE]    = strlen (RSTR (IDS_LISTMODE));

    if (AutoSize ())
    {
        for (ULONG i = 0; i < ul; i++)
        {
            pmp3d->QueryFile (ach, sizeof (ach), i);

#ifdef _MULTILANGUAGES_
            sprintf (ach2, RSTR (IDS_SCANNINGFORMAT), ach);
#else
            sprintf (ach2, "Scanning - %s", ach);
#endif
            WinSetWindowText (pmp3d->hwnd, ach2);

            if ((pmp3 = new MP3 (ach)))
            {
                if (pmp3->IsTagged ())
                {
                    usMaxLen[TAG_TITLE] =
                        max (usMaxLen[TAG_TITLE],
                             USHORT (strlen (pmp3->QueryTitle ())));
                    usMaxLen[TAG_ARTIST] =
                        max (usMaxLen[TAG_ARTIST],
                             USHORT (strlen (pmp3->QueryArtist ())));
                    usMaxLen[TAG_ALBUM] =
                        max (usMaxLen[TAG_ALBUM],
                             USHORT (strlen (pmp3->QueryAlbum ())));
                    usMaxLen[TAG_COMMENT] =
                        max (usMaxLen[TAG_COMMENT],
                             USHORT (strlen (pmp3->QueryComment ())));
                    usMaxLen[TAG_YEAR] = 4;

                    if (pmp3->QueryGenre () >= MAX_GENRES)
#ifdef _MULTILANGUAGES_
                    DisplayError (RSTR (IDS_ERROR_GENERALHEADING),
                                  RSTR (IDS_ERROR_WRONGGENREFOUND));
#else
                    DisplayError ("ERROR", "Wrong genre found.");
#endif
                    else
                        usMaxLen[TAG_GENRE] =
                            max (usMaxLen[TAG_GENRE],
                                 USHORT (strlen (pmp3->QueryGenreName ())));
/*                    usMaxLen[TAG_FILENAME] =
                        max (usMaxLen[TAG_FILENAME],
                             USHORT (strlen (pmp3->QueryFilename ().c_str ()))); */
                    usMaxLen[TAG_TIME] = 6;
                }
                delete pmp3;
            }
        }
    }
    else
    {
        if (MAXLEN_TITLE > usMaxLen[TAG_TITLE])
            usMaxLen[TAG_TITLE] = MAXLEN_TITLE;
        if (MAXLEN_ARTIST > usMaxLen[TAG_ARTIST])
            usMaxLen[TAG_ARTIST] = MAXLEN_ARTIST;
        if (MAXLEN_ALBUM > usMaxLen[TAG_ALBUM])
            usMaxLen[TAG_ALBUM] = MAXLEN_ALBUM;
        if (MAXLEN_YEAR > usMaxLen[TAG_YEAR])
            usMaxLen[TAG_YEAR] = MAXLEN_YEAR;
        if (MAXLEN_COMMENT > usMaxLen[TAG_COMMENT])
            usMaxLen[TAG_COMMENT] = MAXLEN_COMMENT;
        if (6 > usMaxLen[TAG_TIME])
            usMaxLen[TAG_TIME] = 6;    // FIXME ?
        if (20 > usMaxLen[TAG_GENRE])
            usMaxLen[TAG_GENRE] = 20;  // FIXME ?
    }

    if (7 > usMaxLen[TAG_VERSION])
        usMaxLen[TAG_VERSION] = 7;
    if (8 > usMaxLen[TAG_LAYER])
        usMaxLen[TAG_LAYER] = 8;
    if (9 > usMaxLen[TAG_FREQ])
        usMaxLen[TAG_FREQ] = 9;
    if (11 > usMaxLen[TAG_BITRATE])
        usMaxLen[TAG_BITRATE] = 11;
    if (20 > usMaxLen[TAG_MODE])
        usMaxLen[TAG_MODE] = 20;

//    DisplayError ("DEBUG", "scanning over ...");

    if ((pos = new fstream (QueryFilename (), ios::out)))
    {
//        DisplayError ("DEBUG", "stream open ...");
        if (IncludeHeader ())
            OutputHeader (*pos);
//        DisplayError ("DEBUG", "header out ...");
        BOOL   fOutput;

        ul = ULONG (WinSendDlgItemMsg (pmp3d->hwnd, WID_DDL_FILES,
                                       LM_QUERYITEMCOUNT, 0,0));
        for (ULONG i = 0; i < ul; i++)
        {
            pmp3d->QueryFile (ach, sizeof (ach), i);
            fOutput = TRUE;

            if ((pmp3 = new MP3 (ach)))
            {
                if (pmp3d->pset->OnlyTagged ())
                    if (! pmp3->IsTagged ())
                        fOutput = FALSE;

                if (fOutput)
                {
                    Output (pmp3, *pos);
                    ulTime += pmp3->QueryTime ();
#ifdef _MULTILANGUAGES_
            sprintf (ach2, RSTR (IDS_WRITINGFORMAT), ach);
#else
            sprintf (ach2, "Writing - %s", ach);
#endif
                }
                else
#ifdef _MULTILANGUAGES_
            sprintf (ach2, RSTR (IDS_SCANNINGFORMAT), ach);
#else
            sprintf (ach2, "Ignoring - %s", ach);
#endif

                WinSetWindowText (pmp3d->hwnd, ach2);
                delete pmp3;
            }
        }

        if (IncludeTotalTime ())
            OutputTotalTime (*pos, ulTime);

        if (pmp3d->pset->NotifyList ())
#ifdef _MULTILANGUAGES_
            Notify (RSTR (IDS_FILESWRITTENTOLISTHEADING),
                    RSTR (IDS_FILESWRITTENTOLIST), QueryFilename ());
#else
            Notify ("FILES WRITTEN TO LIST",
                    "All selected files have been written to the "
                    "listfile '%s'.", QueryFilename ());
#endif
        delete pos;
    }
    else
#ifdef _MULTILANGUAGES_
        DisplayError (RSTR (IDS_ERROR_LISTFILEHEADING),
                      RSTR (IDS_ERROR_COULDNOTOPENLISTFILE), QueryFilename ());
#else
        DisplayError ("ERROR", "Could not open the listfile '%s'",
                      QueryFilename ());
#endif

    // set mouse-ptr to normal shape
    WinSetPointer (HWND_DESKTOP, hptr);

    WinSetWindowText (pmp3d->hwnd, PSZ_NAMEVERSION);
}

// ** Output ************************************************************** /*FOLD00*/

BOOL LISTER :: Output (PMP3 pmp3, fstream &os)
{
    os.setf (ios::left);

    if (Include (LINC_FILEPATH))
        os << setw (usMaxLen[TAG_FILENAME])
            << pmp3->QueryFilename ().c_str () << ' ';

    if (IncludeTitle ())
        if (pmp3->IsTagged ())
            os << setw (usMaxLen[TAG_TITLE]) << pmp3->QueryTitle () << ' ';
        else
            os << setw (usMaxLen[TAG_TITLE]) << "" << ' ';

    // FIXME check usMaxLen
    os.setf (ios::right);
    if (IncludeTime ())
        os << setw (3) << pmp3->QueryTime ()/60L << ':'
            << setfill ('0') << setw (2) << pmp3->QueryTime ()%60L
            << setfill (' ') << ' ';
    os.setf (ios::left);

    if (pmp3->IsTagged ())
    {
        if (IncludeArtist ())
            os << setw (usMaxLen[TAG_ARTIST]) << pmp3->QueryArtist () << ' ';
        if (IncludeAlbum ())
            os << setw (usMaxLen[TAG_ALBUM]) << pmp3->QueryAlbum () << ' ';
        if (IncludeYear ())
            os << setw (usMaxLen[TAG_YEAR]) << pmp3->QueryYear () << ' ';
        if (IncludeGenre ())
            os << setw (usMaxLen[TAG_GENRE]) << pmp3->QueryGenreName () << ' ';
        if (IncludeComment ())
            os << setw (usMaxLen[TAG_COMMENT]) << pmp3->QueryComment () << ' ';
    }
    else
    {
        if (IncludeArtist ())
            os << setw (usMaxLen[TAG_ARTIST]) << "" << ' ';
        if (IncludeAlbum ())
            os << setw (usMaxLen[TAG_ALBUM]) << "" << ' ';
        if (IncludeYear ())
            os << setw (usMaxLen[TAG_YEAR]) << "" << ' ';
        if (IncludeGenre ())
            os << setw (usMaxLen[TAG_GENRE]) << "" << ' ';
        if (IncludeComment ())
            os << setw (usMaxLen[TAG_COMMENT]) << "" << ' ';
    }

    if (Include (LINC_VERSION))
        os << setw (usMaxLen[TAG_VERSION]) << pmp3->QueryVersionName () << ' ';
    if (Include (LINC_LAYER))
        os << setw (usMaxLen[TAG_LAYER]) << pmp3->QueryLayerName () << ' ';

    os.setf (ios::right);

    CHAR  ach[21];

    if (Include (LINC_FREQUENCY))
    {
        sprintf (ach, "%lu Hz", pmp3->QueryFrequency ());
        os << setw (usMaxLen[TAG_FREQ]) << ach << ' ';
    }
    if (Include (LINC_BITRATE))
    {
        sprintf (ach, "%lu kbit/s", pmp3->QueryBitrate ());
        os << setw (usMaxLen[TAG_BITRATE]) << ach << ' ';
    }
    
    os.setf (ios::left);

    if (Include (LINC_MODE))
        os << setw (usMaxLen[TAG_MODE]) << pmp3->QueryModeName () << ' ';

    os << endl;

    return TRUE;
}

// ** OutputHeader ******************************************************** /*fold00*/

BOOL LISTER :: OutputHeader (fstream &os)
{
    os.setf (ios::left);

    if (Include (LINC_FILEPATH))
        os << setw (usMaxLen[TAG_FILENAME]) <<
#ifdef _MULTILANGUAGES_
            RSTR (IDS_LISTFILENAME)
#else
            "Filename"
#endif
            << ' ';
    if (IncludeTitle ())
        os << setw (usMaxLen[TAG_TITLE]) <<
#ifdef _MULTILANGUAGES_
            RSTR (IDS_LISTTITLE)
#else
            "Title"
#endif
            << ' ';
    if (IncludeTime ())
        os << setw(usMaxLen[TAG_TIME]) <<
#ifdef _MULTILANGUAGES_
            RSTR (IDS_LISTTIME)
#else
            "Time"
#endif
            << ' ';
    if (IncludeArtist ())
        os << setw (usMaxLen[TAG_ARTIST]) <<
#ifdef _MULTILANGUAGES_
            RSTR (IDS_LISTARTIST)
#else
            "Artist"
#endif
            << ' ';
    if (IncludeAlbum ())
        os << setw (usMaxLen[TAG_ALBUM]) <<
#ifdef _MULTILANGUAGES_
            RSTR (IDS_LISTALBUM)
#else
            "Album"
#endif
            << ' ';
    if (IncludeYear ())
        os << setw (usMaxLen[TAG_YEAR]) <<
#ifdef _MULTILANGUAGES_
            RSTR (IDS_LISTYEAR)
#else
            "Year"
#endif
            << ' ';
    if (IncludeGenre ())
        os << setw (usMaxLen[TAG_GENRE]) <<
#ifdef _MULTILANGUAGES_
            RSTR (IDS_LISTGENRE)
#else
            "Genre"
#endif
            << ' ';
    if (IncludeComment ())
        os << setw (usMaxLen[TAG_COMMENT]) <<
#ifdef _MULTILANGUAGES_
            RSTR (IDS_LISTCOMMENT)
#else
            "Comment"
#endif
            << ' ';

    if (Include (LINC_VERSION))
        os << setw (usMaxLen[TAG_VERSION]) <<
#ifdef _MULTILANGUAGES_
            RSTR (IDS_LISTVERSION)
#else
            "Ver."
#endif
            << ' ';
    if (Include (LINC_LAYER))
        os << setw (usMaxLen[TAG_LAYER]) <<
#ifdef _MULTILANGUAGES_
            RSTR (IDS_LISTLAYER)
#else
            "Layer"
#endif
            << ' ';
    if (Include (LINC_FREQUENCY))
        os << setw (usMaxLen[TAG_FREQ]) <<
#ifdef _MULTILANGUAGES_
            RSTR (IDS_LISTFREQUENCY)
#else
            "Freq."
#endif
            << ' ';
    if (Include (LINC_BITRATE))
        os << setw (usMaxLen[TAG_BITRATE]) <<
#ifdef _MULTILANGUAGES_
            RSTR (IDS_LISTBITRATE)
#else
            "Bitrate"
#endif
            << ' ';
    if (Include (LINC_MODE))
        os << setw (usMaxLen[TAG_MODE]) <<
#ifdef _MULTILANGUAGES_
            RSTR (IDS_LISTMODE)
#else
            "Mode"
#endif
            << ' ';

    os << endl;

    if (Include (LINC_FILEPATH))
        OutputLine (usMaxLen[TAG_FILENAME], os);
    if (IncludeTitle ())
        OutputLine (usMaxLen[TAG_TITLE], os);
    if (IncludeTime ())
        OutputLine (usMaxLen[TAG_TIME], os);
    if (IncludeArtist ())
        OutputLine (usMaxLen[TAG_ARTIST], os);
    if (IncludeAlbum ())
        OutputLine (usMaxLen[TAG_ALBUM], os);
    if (IncludeYear ())
        OutputLine (usMaxLen[TAG_YEAR], os);
    if (IncludeGenre ())
        OutputLine (usMaxLen[TAG_GENRE], os);
    if (IncludeComment ())
        OutputLine (usMaxLen[TAG_COMMENT], os);

    if (Include (LINC_VERSION))
        OutputLine (usMaxLen[TAG_VERSION], os);
    if (Include (LINC_LAYER))
        OutputLine (usMaxLen[TAG_LAYER], os);
    if (Include (LINC_FREQUENCY))
        OutputLine (usMaxLen[TAG_FREQ], os);
    if (Include (LINC_BITRATE))
        OutputLine (usMaxLen[TAG_BITRATE], os);
    if (Include (LINC_MODE))
        OutputLine (usMaxLen[TAG_MODE], os);
    os << endl;

    return TRUE;
}

// ** OutputTotalTime ***************************************************** /*fold00*/

BOOL LISTER :: OutputTotalTime (fstream &os, ULONG ul)
{
    if (Include (LINC_FILEPATH))
        OutputLine (usMaxLen[TAG_FILENAME], os);
    if (IncludeTitle ())
        OutputLine (usMaxLen[TAG_TITLE], os);
    if (IncludeTime ())
        OutputLine (usMaxLen[TAG_TIME], os);
    if (IncludeArtist ())
        OutputLine (usMaxLen[TAG_ARTIST], os);
    if (IncludeAlbum ())
        OutputLine (usMaxLen[TAG_ALBUM], os);
    if (IncludeYear ())
        OutputLine (usMaxLen[TAG_YEAR], os);
    if (IncludeGenre ())
        OutputLine (usMaxLen[TAG_GENRE], os);
    if (IncludeComment ())
        OutputLine (usMaxLen[TAG_COMMENT], os);

    if (Include (LINC_VERSION))
        OutputLine (usMaxLen[TAG_VERSION], os);
    if (Include (LINC_LAYER))
        OutputLine (usMaxLen[TAG_LAYER], os);
    if (Include (LINC_FREQUENCY))
        OutputLine (usMaxLen[TAG_FREQ], os);
    if (Include (LINC_BITRATE))
        OutputLine (usMaxLen[TAG_BITRATE], os);
    if (Include (LINC_MODE))
        OutputLine (usMaxLen[TAG_MODE], os);
    os << endl;

    // FIXME check usMaxLen
    os <<
#ifdef _MULTILANGUAGES_
        RSTR (IDS_TOTALTIME)
#else
        "Total time: "
#endif
        << setw (2) << ul/3600L << ':'
        << setw (2) << setfill ('0') << (ul/60L)%60L << ':'
        << setw (2) << setfill ('0') << ul%60L << setfill (' ') << endl;

    return TRUE;
}

// ** SelectFile ********************************************************** /*fold00*/

BOOL LISTER :: SelectFile (VOID)
{
    FILEDLG    fdlg;

    memset (&fdlg, 0, sizeof (fdlg));

    fdlg.cbSize   = sizeof (fdlg);
    fdlg.fl       = FDS_SAVEAS_DIALOG | FDS_CENTER | FDS_MULTIPLESEL;
    fdlg.pszTitle = RSTR (IDS_SELECTLISTFILE);

    if (GETSETTINGS->QueryFlag (SEI_CUSTOMFILEDIALOG))
    {
        fdlg.fl |= FDS_CUSTOM;
        fdlg.hMod       = GETMODULE;
        fdlg.usDlgId    = ID_DLG_FILE;
        fdlg.pfnDlgProc = FileDLGProcedure;
    }

    strcpy (fdlg.szFullFile, QueryFilename ());

    if (WinFileDlg (HWND_DESKTOP, hwnd, &fdlg))
    {
        if (fdlg.lReturn != DID_OK)
            return FALSE;

        SetFilename (fdlg.szFullFile);
        return TRUE;
    }

    return FALSE;
}

// ************************************************************************
