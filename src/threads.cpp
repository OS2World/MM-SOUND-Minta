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

// ** SaveAll ************************************************************* /*fold00*/

VOID MP3DISPLAY :: SaveAll (VOID)
{
#ifdef _DEBUGLOG_
    fputs ("\nSaveAll ()\n", pfileLog);
#endif

    if (! hwnd || ! FilesInList ())
        return;

    // confirm operation
    if (WinMessageBox (HWND_DESKTOP, hwnd,
#ifdef _MULTILANGUAGES_
                       RSTR (IDS_REALLYSAVETAGS),
                       RSTR (IDS_REALLYSAVETAGSHEADING),
#else
                       "Attach the current tag to all selected files?",
                       "REALLY SAVE?",
#endif
                       0L,
                       MB_OKCANCEL | MB_QUERY | MB_DEFBUTTON2 | MB_MOVEABLE)
        != MBID_OK)
        return;

    if (QueryMP3 ())
    {
        delete QueryMP3 ();
        SetMP3 (NULL);
    }

    // set mouse-ptr to "wait" shape
    HPOINTER   hptr = WinQueryPointer (HWND_DESKTOP);
    WinSetPointer (HWND_DESKTOP, WinQuerySysPointer (HWND_DESKTOP, SPTR_WAIT,
                                                     FALSE));
    // do the thing
    ULONG   c = 0L;

#ifdef _STATUSDISPLAY_
    pstatd = new STATD (
#ifdef _MULTILANGUAGES_
                        RSTR (IDS_SAVEALL),
#else
                        "Save all",
#endif
                        CountFilesInList (), hwnd, FALSE, &fBreak);
    pc     = &c;
    fBreak = FALSE;

    _beginthread (SaveAllThread, NULL, 32L*1024L, this);

    pstatd->Process ();

    delete pstatd;
#else
    CHAR   ach[_MAX_PATH];
    CHAR   ach2[_MAX_PATH+31];

    for (ULONG i = 0; i < CountFilesInList (); i++)
    {
        QueryFile (ach, sizeof (ach), i);

        if ((pmp3 = new MP3 (ach)))
        {
#ifdef _MULTILANGUAGES_
            sprintf (ach2, RSTR (IDS_SAVINGFORMAT), ach);
#else
            sprintf (ach2, "Saving - %s", ach);
#endif
            AdjustCurrent (FALSE);
            if (QueryMP3 ()->SaveTag ())
                c++;
            delete pmp3;
        }
        WinSetWindowText (hwnd, ach2);
    }
#endif

    if (pset->NotifySave ())
    {
#ifdef _MULTILANGUAGES_
        // tell user what has been done
        if (c < CountFilesInList ())
            Notify (RSTR (IDS_TAGSSAVEDHEADING),
                    RSTR (IDS_SOMETAGSSAVED), c);
        else
            Notify (RSTR (IDS_TAGSSAVEDHEADING),
                    RSTR (IDS_ALLTAGSSAVED));
#else
        // tell user what has been done
        if (c < CountFilesInList ())
            Notify ("SOME TAGS SAVED",
                    "Tags have been saved for %ld selected files (The "
                    "others probably were read only)", c);
        else
            Notify ("ALL TAGS SAVED",
                    "Tags have been saved for all selected files.");
#endif
    }

    // reload the current file and refresh the display
    SetMP3 (NULL);
    Refresh ();

    // set mouse-ptr to normal shape
    WinSetPointer (HWND_DESKTOP, hptr);
#ifndef _STATUSDISPLAY_
    WinSetWindowText (hwnd, PSZ_NAMEVERSION);
#endif
}

// ** SaveAllThread ******************************************************* /*fold00*/

#ifdef _STATUSDISPLAY_

VOID MP3DISPLAY :: SaveAllThread (PVOID pv)
{
    PMP3DISPLAY   pmp3d = PMP3DISPLAY (pv);
    CHAR          ach[_MAX_PATH];

    HMQ   hmq = WinCreateMsgQueue (hab, 0);;

    for (ULONG i = 0; i < pmp3d->CountFilesInList (); i++)
    {
        pmp3d->QueryFile (ach, sizeof (ach), i);

        pmp3d->pmp3 = new MP3 (ach);
        if (pmp3d->pmp3->IsValid ())
        {
            pmp3d->AdjustCurrent (FALSE);
            if (pmp3d->QueryMP3 ()->SaveTag ())
            {
                *(pmp3d->pc) += 1;
                if (pmp3d->pstatd)
                    pmp3d->pstatd->Advance (ach);
            }
            delete pmp3d->pmp3;
        }

        if (pmp3d->fBreak)
            break;
    }

    if (pmp3d->pstatd)
        pmp3d->pstatd->Finished ();

    WinDestroyMsgQueue (hmq);
}

#endif

// ** RenameAll *********************************************************** /*FOLD00*/

VOID MP3DISPLAY :: RenameAll (VOID)
{
#ifdef _DEBUGLOG_
    fputs ("\nRenameAll ()\n", pfileLog);
#endif

    if (! hwnd || ! FilesInList ())
        return;

/*    // confirm operation
    if (WinMessageBox (HWND_DESKTOP, hwnd,
#ifdef _MULTILANGUAGES_
                       RSTR (IDS_REALLYRENAMEALL),
                       RSTR (IDS_REALLYRENAMEALLHEADING),
#else
                       "Rename all files (with tag) to their Title?",
                       "REALLY RENAME?",
#endif
                       0L,
                       MB_OKCANCEL | MB_QUERY | MB_DEFBUTTON2 | MB_MOVEABLE)
        != MBID_OK)
        return; */

    if (QueryMP3 ())
    {
        delete QueryMP3 ();
        SetMP3 (NULL);
    }

    // set mouse-ptr to "wait" shape
    HPOINTER   hptr = WinQueryPointer (HWND_DESKTOP);
    WinSetPointer (HWND_DESKTOP, WinQuerySysPointer (HWND_DESKTOP, SPTR_WAIT,
                                                     FALSE));
    // do the thing
    CHAR    ach[_MAX_PATH], ach2[_MAX_PATH+31];
    ULONG   c = 0L;

    // FIXME perhaps ... = strlen ("Filename");
    plist->usMaxLen[TAG_FILENAME] = 0;

    for (ULONG i = 0; i < CountFilesInList (); i++)
    {
        QueryFile (ach, sizeof (ach), i);

        if ((pmp3 = new MP3 (ach)))
        {
//            if (pmp3->IsTagged ())
            {
#ifdef _MULTILANGUAGES_
                sprintf (ach2, RSTR (IDS_RENAMINGFORMAT), ach);
#else
                sprintf (ach2, "Renaming - %s", ach);
#endif
                WinSetWindowText (hwnd, ach2);

                USHORT  cb = GETSETTINGS->QueryLong (SEI_RENAMELENGTH);
                if (! GETSETTINGS->QueryFlag (SEI_RENAMELIMITLENGTH))
                    cb = 0;
                if (pren->Rename (pmp3,
                            GETSETTINGS->QueryString (SEI_RENAMETEMPLATE),
                            GETSETTINGS->QueryFlag (SEI_RENAMEREPLACESPACES),
                            cb))
                {
                    c ++;
                    strcpy (ach2, pmp3->QueryFilename ().c_str ());
                    WinSetLboxItemText (WinWindowFromID (hwnd, WID_DDL_FILES),
                                        i, ach2);
                    WinSendDlgItemMsg (hwnd, WID_DDL_FILES, EM_SETFIRSTCHAR,
                                       0L, 0L);
                    // if this MP3's filename is longer than current maximum
                    // in list adjust maximum (needed for outputing lists)
                    plist->usMaxLen[TAG_FILENAME] =
                        max (plist->usMaxLen[TAG_FILENAME],
                             USHORT (strlen (pmp3->QueryFilename ().c_str ())));
                }
                else
                {
#ifdef _MULTILANGUAGES_
                    DisplayError (RSTR (IDS_ERROR_GENERALHEADING),
                                  RSTR (IDS_ERROR_RENAMINGFAILED),
                                  ach, errno);
#else
                    DisplayError ("ERROR", "Renaming file '%s' failed: "
                                  "Error %d.", ach, errno);
#endif
                    plist->usMaxLen[TAG_FILENAME] =
                        max (plist->usMaxLen[TAG_FILENAME],
                             USHORT (strlen (ach)));
                }
            }
            delete pmp3;
        }
    }

    if (pset->NotifyRename ())
    {
#ifdef _MULTILANGUAGES_
        // tell user what has been done
        if (c < CountFilesInList ())
            Notify (RSTR (IDS_FILESRENAMEDHEADING),
                    RSTR (IDS_SOMEFILESRENAMED), c);
        else
            Notify (RSTR (IDS_FILESRENAMEDHEADING),
                    RSTR (IDS_ALLFILESRENAMED));
#else
        // tell user what has been done
        if (c < CountFilesInList ())
            Notify ("SOME FILES RENAMED",
                    "%ld selected files have been renamed (The "
                    "others probably had no tag)", c);
        else
            Notify ("ALL FILES SAVED",
                    "All selected files have been renamed.");
#endif
    }

    // reload the current file and refresh the display
    SetMP3 (NULL);
    Refresh ();

    QueryFile (ach, sizeof (ach));
    WinSetWindowText (WinWindowFromID (hwnd, WID_DDL_FILES), ach);

    // set mouse-ptr to normal shape
    WinSetPointer (HWND_DESKTOP, hptr);
    WinSetWindowText (hwnd, PSZ_NAMEVERSION);
}

// ** RemoveAll *********************************************************** /*fold00*/

VOID MP3DISPLAY :: RemoveAll (VOID)
{
#ifdef _DEBUGLOG_
    fputs ("\nRemoveAll ()\n", pfileLog);
#endif

    if (! hwnd || ! FilesInList ())
        return;

    // confirm operation
    if (WinMessageBox (HWND_DESKTOP, hwnd,
#ifdef _MULTILANGUAGES_
                       RSTR (IDS_REALLYREMOVETAGS),
                       RSTR (IDS_REALLYREMOVETAGSHEADING),
#else
                       "Really remove the tags of all selected files?",
                       "REALLY REMOVE?",
#endif
                       0L,
                       MB_OKCANCEL | MB_QUERY | MB_DEFBUTTON2 | MB_MOVEABLE)
        != MBID_OK)
        return;

    if (QueryMP3 ())
    {
        delete QueryMP3 ();
        SetMP3 (NULL);
    }

    // set mouse-ptr to "wait" shape
    HPOINTER   hptr = WinQueryPointer (HWND_DESKTOP);
    WinSetPointer (HWND_DESKTOP, WinQuerySysPointer (HWND_DESKTOP, SPTR_WAIT,
                                                     FALSE));

    // do the thing
    CHAR    ach[_MAX_PATH], ach2[_MAX_PATH+31];
    ULONG   c = 0L;

    for (ULONG i = 0; i < CountFilesInList (); i++)
    {
        QueryFile (ach, sizeof (ach), i);

        if ((pmp3 = new MP3 (ach)))
        {
            if (pmp3->IsTagged ())
            {
#ifdef _MULTILANGUAGES_
                sprintf (ach2, RSTR (IDS_REMOVINGFORMAT), ach);
#else
                sprintf (ach2, "Removing - %s", ach);
#endif
                if (pmp3->RemoveTag ())
                    c++;
            }
            else
#ifdef _MULTILANGUAGES_
                sprintf (ach2, RSTR (IDS_IGNORINGFORMAT), ach);
#else
                sprintf (ach2, "Ignoring - %s", ach);
#endif
            delete pmp3;
        }

        WinSetWindowText (hwnd, ach2);
    }

    if (pset->NotifyRemove ())
    {
#ifdef _MULTILANGUAGES_
        // tell user what has been done
        if (c < CountFilesInList ())
            Notify (RSTR (IDS_TAGSREMOVEDHEADING),
                    RSTR (IDS_SOMETAGSREMOVED), c);
        else
            Notify (RSTR (IDS_TAGSREMOVEDHEADING),
                    RSTR (IDS_ALLTAGSREMOVED));
#else
        // tell user what has been done
        if (c < CountFilesInList ())
            Notify ("SOME TAGS REMOVED",
                    "Tags have been removed from %ld selected files (The "
                    "others probably were read only or had no tag)", c);
        else
            Notify ("ALL TAGS REMOVED",
                    "Tags have been removed from all selected files.");
#endif
    }

    // reload the current file and refresh the display
    SetMP3 (NULL);
    Refresh ();

    // set mouse-ptr to normal shape
    WinSetPointer (HWND_DESKTOP, hptr);
    WinSetWindowText (hwnd, PSZ_NAMEVERSION);
}

// ************************************************************************
