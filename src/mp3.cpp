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

#include "mp3.h"

// ** class data ********************************************************** /*fold00*/

#ifndef _MULTILANGUAGES_

PSZ MP3::apszVersions[4] =
{
    "Unknown", "MPEG 1", "MPEG 2", "MPEG 2.5",
};

PSZ MP3::apszLayers[4] =
{
    "Unknown", "Layer 1", "Layer 2", "Layer 3",
};

PSZ MP3::apszModes[4] =
{
    "Stereo", "Joint-Stereo", "Dual-Channel", "Mono"
};

PSZ MP3::apszEmphasis[4] =
{
    "None", "50/15ms", "???", "CITT j. 17",
};

#else

PSZ MP3::apszVersions[4] =
{
    NULL, "MPEG 1", "MPEG 2", "MPEG 2.5",
};

PSZ MP3::apszLayers[4] =
{
    NULL, "Layer 1", "Layer 2", "Layer 3",
};

PSZ MP3::apszModes[4];

PSZ MP3::apszEmphasis[4] =
{
    NULL, "50/15ms", "???", "CITT j. 17",
};

PSZ MP3::pszUnknownGenre = "(unknown)";

#endif

#ifndef _LOADGENRES_
PSZ MP3::apszGenres[MAX_GENRES] =
{
    "Blues",
    "Classic Rock",
    "Country",
    "Dance",
    "Disco",
    "Funk",
    "Grunge",
    "Hip-Hop",
    "Jazz",
    "Metal",
    "New Age",
    "Oldies",
    "Other",
    "Pop",
    "R&B",
    "Rap",
    "Reggae",
    "Rock",
    "Techno",
    "Industrial",
    "Alternative",
    "Ska",
    "Death Metal",
    "Pranks",
    "Soundtrack",
    "Euro-Techno",
    "Ambient",
    "Trip-Hop",
    "Vocal",
    "Jazz+Funk",
    "Fusion",
    "Trance",
    "Classical",
    "Instrumental",
    "Acid",
    "House",
    "Game",
    "Sound Clip",
    "Gospel",
    "Noise",
    "AlternRock",
    "Bass",
    "Soul",
    "Punk",
    "Space",
    "Meditative",
    "Instrumental Pop",
    "Instrumental Rock",
    "Ethnic",
    "Gothic",
    "Darkwave",
    "Techno-Industrial",
    "Electronic",
    "Pop-Folk",
    "Eurodance",
    "Dream",
    "Southern Rock",
    "Comedy",
    "Cult",
    "Gangsta",
    "Top 40",
    "Christian Rap",
    "Pop/Funk",
    "Jungle",
    "Native American",
    "Cabaret",
    "New Wave",
    "Psychadelic",
    "Rave",
    "Showtunes",
    "Trailer",
    "Lo-Fi",
    "Tribal",
    "Acid Punk",
    "Acid Jazz",
    "Polka",
    "Retro",
    "Musical",
    "Rock & Roll",
    "Hard Rock",
    "Folk",
    "Folk/Rock",
    "National Folk",
    "Swing",
    "Bebob",
    "Latin",
    "Revival",
    "Celtic",
    "Bluegrass",
    "Avantgarde",
    "Gothic Rock",
    "Progressive R",
    "Psychedelic R",
    "Symphonic Roc",
    "Slow Rock",
    "Big Band",
    "Chorus",
    "Easy Listenin",
    "Acoustic",
    "Humour",
    "Speech",
    "Chanson",
    "Opera",
    "Chamber Music",
    "Sonata",
    "Symphony",
    "Booty Bass",
    "Primus",
    "Porn Groove",
    "Satire",
    "Slow Jam",
    "Club",
    "Tango",
    "Samba",
    "Folklore",
};
#endif

// ** MP3 ***************************************************************** /*fold00*/

MP3 :: MP3File (STRING strFilename)
{
    pis = NULL;
    this->strFilename = strFilename;
    Reload ();
}

// ** QueryBitrate ******************************************************** /*fold00*/

ULONG MP3 :: QueryBitrate (VOID)
{
    static ULONG aulBitrates[16][VER_MAX][LAYER_MAX] =
    {
        { {   0,   0,   0 }, {   0,   0,   0 } },
        { {  32,  32,  32 }, {  32,   8,   8 } },
        { {  64,  48,  40 }, {  48,  16,  16 } },
        { {  96,  56,  48 }, {  56,  24,  24 } },
        { { 128,  64,  56 }, {  64,  32,  32 } },
        { { 160,  80,  64 }, {  80,  40,  40 } },
        { { 192,  96,  80 }, {  96,  48,  48 } },
        { { 224, 112,  96 }, { 112,  56,  56 } },
        { { 256, 128, 112 }, { 128,  64,  64 } },
        { { 288, 160, 128 }, { 144,  80,  80 } },
        { { 320, 192, 160 }, { 160,  96,  96 } },
        { { 352, 224, 192 }, { 176, 112, 112 } },
        { { 384, 256, 224 }, { 192, 128, 128 } },
        { { 416, 320, 256 }, { 224, 144, 144 } },
        { { 448, 384, 320 }, { 256, 160, 160 } },
        { {   0,   0,   0 }, {   0,   0,   0 } },
    };

    return aulBitrates[Header.usBitrate][QueryVersion ()-1][QueryLayer ()-1];
}

// ** QueryFrequency ****************************************************** /*fold00*/

ULONG MP3 :: QueryFrequency (VOID)
{
    static ULONG aulFrequency[7] = {
        44100, 48000, 32000, 22050, 24000, 16000, 11025 };

    return aulFrequency[Header.usFreq];
}

// ** QueryMode *********************************************************** /*fold00*/

MODE MP3 :: QueryMode (ULONG *pulBands)
{
    ULONG apulBands[LAYER_MAX][4] =
    {
        { 4, 8, 12, 16 },
        { 4, 8, 12, 16 },
        { 0, 4,  8, 16 },
    };

    if (pulBands)
        *pulBands = 0L;

    switch (Header.usMode)
    {
    case 0:        return MODE_STEREO;
    case 2:        return MODE_DUALCHANNEL;
    case 3:        return MODE_MONO;
    }

    if (pulBands)
        *pulBands = apulBands[QueryLayer ()-1L][Header.usModeExt];
    return MODE_JOINTSTEREO;
}

// ** SaveTag ************************************************************* /*fold00*/

BOOL MP3 :: SaveTag (VOID)
{
    unsigned char chTmp;

#ifdef _DEBUGLOG_
    time_t      tt = time (NULL);
    struct tm   *ptm = localtime (&tt);
    fprintf (pfileLog, "\n%sAbout to SaveTag of '%s' ...\n", asctime (ptm),
             QueryFilename ().c_str ());
#endif
    if (IsReadOnly ())
    {
#ifdef _DEBUGLOG_
        fprintf (pfileLog, "File is read only, aborting\n");
#endif
        return FALSE;
    }

    if (IsTagged ())
    {
#ifdef _DEBUGLOG_
        fprintf (pfileLog, "File is tagged ...\n");
        fprintf (pfileLog, "Pos = p%ld/g%ld\n", pis->tellp (), pis->tellg ());
#endif
        pis->seekp (S_TAGOFFSET, ios::end);
    }
    else
    {
#ifdef _DEBUGLOG_
        fprintf (pfileLog, "File is NOT tagged ...\n");
        fprintf (pfileLog, "Pos = p%ld/g%ld\n", pis->tellp (), pis->tellg ());
#endif
        pis->seekp (0L, ios::end);
    }
#ifdef _DEBUGLOG_
    fprintf (pfileLog, "Pos after seek = p%ld/g%ld\n",
             pis->tellp (), pis->tellg ());
    if (pis->fail ())
        fprintf (pfileLog, "fail () after seek\n");
#endif

    pis->write (PSZ_TAGSIGNATURE, strlen (PSZ_TAGSIGNATURE));
#ifdef _DEBUGLOG_
    if (pis->fail ())
        fprintf (pfileLog, "fail () after PSZ_TAGSIG...\n");
#endif

    PaddWithZeros (QueryTitle (), MAXLEN_TITLE);
    pis->write (QueryTitle (), MAXLEN_TITLE);
#ifdef _DEBUGLOG_
    if (pis->fail ())
        fprintf (pfileLog, "fail () after Title\n");
#endif
    PaddWithZeros (QueryArtist (), MAXLEN_ARTIST);
    pis->write (QueryArtist (), MAXLEN_ARTIST);
#ifdef _DEBUGLOG_
    if (pis->fail ())
        fprintf (pfileLog, "fail () after Artist\n");
#endif
    PaddWithZeros (QueryAlbum (), MAXLEN_ALBUM);
    pis->write (QueryAlbum (), MAXLEN_ALBUM);
#ifdef _DEBUGLOG_
    if (pis->fail ())
        fprintf (pfileLog, "fail () after Album\n");
#endif
    PaddWithZeros (QueryYear (), MAXLEN_YEAR);
    pis->write (QueryYear (), MAXLEN_YEAR);
#ifdef _DEBUGLOG_
    if (pis->fail ())
        fprintf (pfileLog, "fail () after Year\n");
#endif

    // expand macros and stuff
    FinalizeComment ();

    PaddWithZeros (QueryComment (), MAXLEN_COMMENT);
    pis->write (QueryComment (), MAXLEN_COMMENT);
#ifdef _DEBUGLOG_
    if (pis->fail ())
        fprintf (pfileLog, "fail () after Comment\n");
#endif

    if (QueryTrack ())
    {
        pis->seekp (-2, ios::cur);
        pis->put (0);
        chTmp = QueryTrack ();
//    DisplayInfo( "Track us 1", "'%d' '%02x'", chTmp, chTmp );
        pis->write( &chTmp, 1 );
    }

    // FIXME move this lines somewhere else?
    if (sGenre == GENREID_NIL)
        SetGenre (GENREID_DEFAULT);

    chTmp = sGenre;
    pis->write( &chTmp, 1 );
#ifdef _DEBUGLOG_
    if (pis->fail ())
        fprintf (pfileLog, "fail () after Genre\n");
#endif

    pis->flush ();
#ifdef _DEBUGLOG_
    if (pis->fail ())
        fprintf (pfileLog, "fail () after flush ()\n");
#endif
    IsTagged (TRUE);

#ifdef _DEBUGLOG_
    fprintf (pfileLog, "File should now be tagged, exiting\n");
    fflush (pfileLog);
#endif

    return TRUE;
}

// ** RemoveTag *********************************************************** /*fold00*/

BOOL MP3 :: RemoveTag (VOID)
{
#ifdef _DEBUGLOG_
    time_t      tt = time (NULL);
    struct tm   *ptm = localtime (&tt);
    fprintf (pfileLog, "\n%sAbout to RemoveTag of '%s' ...\n", asctime (ptm),
             QueryFilename ().c_str ());
#endif
    if (! IsTagged ())
    {
#ifdef _DEBUGLOG_
        fprintf (pfileLog, "File is not tagged, aborting\n");
#endif
        return TRUE;
    }

    if (IsReadOnly ())
    {
#ifdef _DEBUGLOG_
        fprintf (pfileLog, "File is read only, aborting\n");
#endif
        return FALSE;
    }

    HFILE  hf;
    ULONG  ulAction;

    FILESTATUS3   fs3;

    if (DosOpen (QueryFilename ().c_str (), &hf, &ulAction, 0L, FILE_NORMAL,
                 OPEN_ACTION_FAIL_IF_NEW | OPEN_ACTION_OPEN_IF_EXISTS,
                 OPEN_FLAGS_NOINHERIT | OPEN_SHARE_DENYNONE |
                 OPEN_ACCESS_READWRITE, 0L) != NO_ERROR)
    {
#ifdef _MULTILANGUAGES_
        DisplayError (RSTR (IDS_ERROR_MP3FILEHEADING),
                      RSTR (IDS_ERROR_COULDNOTOPENMP3FILE));
#else
        DisplayError ("ERROR", "Could not open file.");
#endif
#ifdef _DEBUGLOG_
        fprintf (pfileLog, "Could not open file\n");
#endif
        return FALSE;
    }

    if (DosQueryFileInfo (hf, FIL_STANDARD, &fs3, sizeof (fs3)) != NO_ERROR)
    {
#ifdef _MULTILANGUAGES_
        DisplayError (RSTR (IDS_ERROR_MP3FILEHEADING),
                      RSTR (IDS_ERROR_COULDNOTGETFILESIZE));
#else
        DisplayError ("ERROR", "Could not get current filesize.");
#endif
#ifdef _DEBUGLOG_
        fprintf (pfileLog, "Could not get current filesize\n");
#endif
        return FALSE;
    }
    if (DosSetFileSize (hf, fs3.cbFile+S_TAGOFFSET) != NO_ERROR)
    {
#ifdef _MULTILANGUAGES_
        DisplayError (RSTR (IDS_ERROR_MP3FILEHEADING),
                      RSTR (IDS_ERROR_COULDNOTREMOVETAG));
#else
        DisplayError ("ERROR", "Could not remove tag.");
#endif
#ifdef _DEBUGLOG_
        fprintf (pfileLog, "Could not remove tag (i.e. reset filesize)\n");
#endif
        return FALSE;
    }

    DosClose (hf);
    SetGenre (GENREID_NIL);
    IsTagged (FALSE);

#ifdef _DEBUGLOG_
    fprintf (pfileLog, "File should now have NO tag, exiting\n");
    fflush (pfileLog);
#endif

    return TRUE;
}

// ** ReadHeader ********************************************************** /*fold00*/

BOOL MP3 :: ReadHeader (VOID)
{
    ULONG   ul;

    if (! FindHeader (pis, ul))
        return FALSE;

    // check if MPEG-2.5 and get other version bit
    if (ul & (1<<20))
    {
        Header.usVersion = (ul & (1<<19)) ? 0x0 : 0x1;
        fIsV25 = FALSE;
    }
    else
    {
        Header.usVersion = 1;
        fIsV25 = TRUE;
    }

    // get layer
    Header.usLayer = 4 - ((ul>>17) & 3);
    if (Header.usLayer == 4)
        Header.usLayer = LAYER_UNKNOWN;

    // get bitrate index
    Header.usBitrate = ((ul>>12) & 0xf);
    if (((ul>>10) & 0x3) == 0x3)
    {
        // FIXME do something
    }

    // allow bitrate change for 2.5 - whatever that means :-)
    if (fIsV25)
        Header.usBitrate = ((ul>>12) & 0xf);

    // get frequency
    if (fIsV25)
        Header.usFreq = 6 + ((ul>>10) & 0x3);
    else
        Header.usFreq = ((ul>>10) & 0x3) + (Header.usVersion*3);

    // get error protection flag
    Header.usProtect = ((ul>>16) & 0x1)^0x1;

    // assign some stuff
    Header.usPadd      = ((ul>>9) & 0x1);
    Header.usPrivate   = ((ul>>8) & 0x1);
    Header.usMode      = ((ul>>6) & 0x3);
    Header.usModeExt   = ((ul>>4) & 0x3);
    Header.usCopyright = ((ul>>3) & 0x1);
    Header.usOriginal  = ((ul>>2) & 0x1);
    Header.usEmphasis  = ul & 0x3;

    return TRUE;
}

// ** FindHeader ********************************************************** /*fold00*/

BOOL MP3 :: FindHeader (istream *pis, ULONG &ul)
{
    CHAR   ach[4];

    // check if we get an ID3 v2.x tag at the beginning
    pis->read (ach, 3);
    if (strncmp (ach, "ID3", 3) == 0)
    {
        fHasUnsupportedTag = TRUE;
        usTagVersion[0] = 2;
        usTagVersion[1] = pis->get ();
        usTagVersion[2] = pis->get ();
        pis->ignore (1);
        pis->read (ach, 4);
        ULONG  ul = 0L |
            ULONG (ach[0])<<21 |
            ULONG (ach[1])<<14 |
            ULONG (ach[2])<< 7 |
            ULONG (ach[3]);
        //        DisplayError ("DEBUG", "0x%08lx-(%lu,%d,%d,%d,%d)", WinGetLastError (GETHAB), ul, ach[0], ach[1], ach[2], ach[3]);
        pis->ignore (ul);
    }
    else
        fHasUnsupportedTag = FALSE;

    // YOU STUPID! STUPID!! STUPID!!! How could you forget this?!?! ;-)
    pis->seekg (0);

read_again:
    ReadHeaderBytes (pis, ul);

    if (! ValidHeader (ul))
    {
        USHORT   i;

        // check for RIFF header
        if (ul == ('R'<<24)+('I'<<16)+('F'<<8)+'F')
        {
            pis->seekg (68L, ios::cur);
            goto read_again;
        }

        // search in 32 bit steps through the first 2K
        for (i = 0; i < 512; i++)
        {
            if (! ReadHeaderBytes (pis, ul))
                return FALSE;
            if (ValidHeader (ul))
                break;
        }

        // nothing found; keep on searching
        if (i == 512)
        {
            // step in byte steps through next 2K
/*            for (i = 0; i < 2048; i++)
            {
                memmove (&hbuf[0], &hbuf[1], 3);
                if(fread(hbuf+3,1,1,filept) != 1)
                    return 0;
                ul <<= 8;
                ul |= hbuf[3];
                ul &= 0xffffffff;

                if (ValidHeader (ul))
                    break;
            }

            if (i == 2048) */
                return FALSE;
        }
    }

    return TRUE;
}

// ** ValidHeader ********************************************************* /*fold00*/

BOOL MP3 :: ValidHeader (ULONG ul)
{
    // check header
    if ((ul & 0xffe00000) != 0xffe00000)
        return FALSE;
    if (!((ul>>17) & 3))
        return FALSE;
    if (((ul>>12) & 0xf) == 0xf)
        return FALSE;
    if (((ul>>10) & 0x3) == 0x3)
        return FALSE;

    return TRUE;
}

// ** ReadHeaderBytes ***************************************************** /*fold00*/

BOOL MP3 :: ReadHeaderBytes (istream *pis, ULONG &ul)
{
    unsigned char   ach[4];

    // get four bytes from file
    pis->read (&ach, 4);
    if (! pis->good ())
        return FALSE;

    // rearrange bytes
    ul = (ULONG (ach[0]) << 24) | (ULONG (ach[1]) << 16) |
        (ULONG (ach[2]) << 8)  | (ULONG (ach[3]));
    return TRUE;
}

// ** FinalizeComment ***************************************************** /*fold00*/

VOID MP3 :: FinalizeComment (VOID)
{
    CHAR   ach[MAXLEN_COMMENT+_MAX_PATH];

    ExpandMacros (pszComment, ach, MAXLEN_COMMENT+_MAX_PATH);
    SetComment (ach);
}

// ** ExpandMacros ******************************************************** /*FOLD00*/

BOOL MP3 :: ExpandMacros (PSZ pszTemplate, PSZ psz, USHORT cb)
{
    CHAR   ach[_MAX_PATH];
    USHORT i, j = 0;

    psz[j] = '\0';
    for (i = 0; pszTemplate[i]; i++)
    {
        if (pszTemplate[i] == CHAR_COMMENTMACRO)
        {
            switch (pszTemplate[i+1])
            {
            case 't':
                sprintf (ach, "%02ld:%02ld", QueryTime ()/60L,
                         QueryTime ()%60L);
                break;

            case 'T':   sprintf (ach, "%s", QueryTitle ());            break;
            case 'A':   sprintf (ach, "%s", QueryArtist ());           break;
            case 'a':   sprintf (ach, "%s", QueryAlbum ());            break;
            case 'Y':   sprintf (ach, "%s", QueryYear ());             break;
            case 'G':   sprintf (ach, "%s", QueryGenreName ());        break;

            case 'C':   sprintf (ach, "%s", QueryComment ());          break;

            case 'v':   sprintf (ach, "%s", QueryVersionName ());      break;
            case 'l':   sprintf (ach, "%s", QueryLayerName ());        break;
            case 'f':   sprintf (ach, "%ld", QueryFrequency ());       break;
            case 'b':   sprintf (ach, "%ld", QueryBitrate ());         break;
            case 'm':   sprintf (ach, "%s", QueryModeName ());         break;

            case 'r':
#ifdef _TWO_DIGIT_TRACKNUMBERS_
                if( g_fTwoDigitTracknumbers ) {
                    sprintf (ach, "%02d", QueryTrack ());
                } else
#endif
#ifdef _CUSTOMIZABLE_TRACKNUMBERS_WIDTH_
                if( isdigit( pszTemplate[i+2] ) ) {
                    int length = 0;
                    if( ( length = pszTemplate[i+2]-'0' ) > 0 )
                        sprintf (ach, "%0*d", length, QueryTrack ());
                    i ++;
                } else
#endif
                    sprintf (ach, "%d", QueryTrack ());
                break;

            default:
                sprintf (ach, "%c%c", CHAR_COMMENTMACRO, pszComment[i+1]);
                break;
            }
            if (USHORT (j+strlen (ach)) < cb-1)
            {
                strcat (psz, ach);
                j += strlen (ach);
                i ++;
            }
            else
                // not enough space in dest. string. stop expanding.
                return FALSE;
        }
        else
        {
            if (j < cb-1)
            {
                psz[j] = pszTemplate[i];
                psz[j+1] = '\0';
                j ++;
            }
            else
                // not enough space in dest. string. stop expanding.
                return FALSE;
        }
    }

    return TRUE;
}

// ** Rename ************************************************************** /*fold00*/

BOOL MP3 :: Rename (PSZ psz)
{
    // try to actually rename the file
    if (rename (QueryFilename ().c_str (), psz) != 0)
    {
/*        DisplayError ("DEBUG", "<%s> -> <%s> failed.",
 QueryFilename ().c_str (), achNew); */
        Reload ();
        return FALSE;
    }

    PSZ pszLongname = _getname(psz), pszExt = _getext(pszLongname);
    if (pszExt) { pszExt[0] = '\0'; }

    // START setting .LONGNAME EA
    PSZ     pszName = ".LONGNAME";
    PSZ     pszValue = pszLongname;
    USHORT  cbName = strlen (pszName)+1;
    USHORT  cbValue = strlen (pszValue)+1;
    USHORT  usMemNeeded = sizeof (FEA2LIST) + cbName + cbValue;
    PBYTE  pb = PBYTE (malloc (usMemNeeded));

    EAOP2   eaop2;

    eaop2.fpFEA2List = (FEA2LIST FAR *) pb;
    eaop2.fpFEA2List->cbList = usMemNeeded;

    eaop2.fpFEA2List->list[0].fEA     = 0;  // EA is no "must have"
    eaop2.fpFEA2List->list[0].cbName  = cbName-1;
    eaop2.fpFEA2List->list[0].cbValue = cbValue;

    strcpy (eaop2.fpFEA2List->list[0].szName, pszName);
    memcpy (eaop2.fpFEA2List->list[0].szName+cbName, pszValue, cbValue);

    if (pszExt) { pszExt[0] = '.'; }
    if (DosSetPathInfo (psz, FIL_QUERYEASIZE, PVOID (&eaop2),
                        sizeof (EAOP2), DSPI_WRTTHRU))
    {
#ifdef _ALLOW_DISABLE_EA_ERROR_
        if( !g_fDisableEAError )
#endif
            DisplayError ("ERROR", "Could not write .LONGNAME EA.");
    }
    free (pb);
    // END setting .LONGNAME EA

    strFilename = psz;
    Reload ();

    return TRUE;
}

// ** Reload ************************************************************** /*fold00*/

VOID MP3 :: Reload (VOID)
{
#ifdef _DEBUGLOG_
    fprintf (pfileLog, "\nAbout to load '%s' ...\n", strFilename.c_str ());
#endif

    if (pis)
        delete pis;

    // set "defaults"
    memset (pszTitle, 0x00, MAXLEN_TITLE);
    memset (pszArtist, 0x00, MAXLEN_ARTIST);
    memset (pszAlbum, 0x00, MAXLEN_ALBUM);
    memset (pszComment, 0x00, MAXLEN_COMMENT);
    memset (pszYear, 0x00, MAXLEN_YEAR);
    sGenre = GENREID_NIL;
    sTrack = 0;
    memset (&Header, 0x00, sizeof (Header));
    ulTime = 0L;
    IsReadOnly (FALSE);
    IsTagged (FALSE);
    IsValid (FALSE);
    HasValidHeader (FALSE);

    if (access (strFilename.c_str (), 0) != 0)
    {
        err = MP3ERR_FILENOTOPEN;
        return;
    }
    else
        err = MP3ERR_NONE;

    // open file
    pis = new fstream (strFilename.c_str (), ios::in | ios::out | ios::binary);
    if (pis->fail ())
    {
        IsReadOnly (TRUE);
        pis = new fstream (strFilename.c_str (), ios::in | ios::binary);
        if (pis->fail ())
        {
            pis = NULL;
#ifdef _MULTILANGUAGES_
            DisplayError (RSTR (IDS_ERROR_MP3FILEHEADING),
                          RSTR (IDS_ERROR_COULDNOTOPENMP3FILE),
                          strFilename.c_str (), errno);
#else
            DisplayError ("MP3 FILE NOT OPEN",
                          "Could not open MP3 file \"%s\". Error %d.",
                          strFilename.c_str (), errno);
#endif
            return;
        }
    }

    CHAR   ach[81];

    if (! ReadHeader ())
    {
        if (! GETSETTINGS->NoInvalidMP3Warning ())
        {
#ifdef _MULTILANGUAGES_
            DisplayError (RSTR (IDS_ERROR_MP3FILEHEADING),
                          RSTR (IDS_ERROR_NOVALIDMP3FILE),
                          strFilename.c_str ());
#else

            DisplayError ("NOT AN MP3 FILE?",
                          "File \"%s\" seems not to be a valid MP3 file. If "
                          "you modify it, you will act on your own risk ...",
                          strFilename.c_str ());
#endif
        }
    }
    else
        HasValidHeader (TRUE);

/*    DisplayError ("DEBUG", "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
                  Header.usSync1, Header.usVersion, Header.usLayer, Header.usProtect,
                  Header.usBitrate, Header.usFreq, Header.usPadd, Header.usPrivate,
                  Header.usMode, Header.usModeExt, Header.usCopyright, Header.usOriginal,
                  Header.usEmphasis); */

    if (! HasUnsupportedTag ())
    {
        // check for "TAG" - signature
        pis->seekg (S_TAGOFFSET, ios::end);
        pis->read (&ach, strlen (PSZ_TAGSIGNATURE));
#ifdef _DEBUGLOG_
        for (USHORT i = 0; i < strlen (PSZ_TAGSIGNATURE); i++)
            fprintf (pfileLog, "0x%02x ", ach[i]);
        fputs ("have been read ...\n", pfileLog);
#endif
        if (strncmp (ach, PSZ_TAGSIGNATURE, strlen (PSZ_TAGSIGNATURE)) == 0)
        {
            pis->read (pszTitle, MAXLEN_TITLE);
            pszTitle[MAXLEN_TITLE] = '\0';
            strkspc (pszTitle);

            pis->read (pszArtist, MAXLEN_ARTIST);
            pszArtist[MAXLEN_ARTIST] = '\0';
            strkspc (pszArtist);

            pis->read (pszAlbum, MAXLEN_ALBUM);
            pszAlbum[MAXLEN_ALBUM] = '\0';
            strkspc (pszAlbum);

            pis->read (pszYear, MAXLEN_YEAR);
            pszYear[MAXLEN_YEAR] = '\0';
            strkspc (pszYear);

            pis->read (pszComment, MAXLEN_COMMENT);
            pszComment[MAXLEN_COMMENT] = '\0';
            strkspc (pszComment);

            unsigned char chTmp;

            if (pszComment[MAXLEN_COMMENT-2] == 0) {
                chTmp = pszComment[MAXLEN_COMMENT-1];
                sTrack = chTmp;
//    DisplayInfo( "Track us 2", "'%d' '%02x' '%02x' '%02x'", sTrack, sTrack, pszComment[MAXLEN_COMMENT-1], chTmp );
            }

            chTmp = pis->get ();
            if ((sGenre = chTmp) >= MAX_GENRES)
                sGenre = GENREID_DEFAULT;

            IsTagged (TRUE);
        }
    }

#ifdef _DEBUGLOG_
    fprintf (pfileLog, "This means file '%s' has %s tag\n", strFilename.c_str (),
             IsTagged () ? "a" : "no");
    fflush (pfileLog);
#endif

    /*        for (i = 0; i < 32; i++)
     if (Bits2Value (achHeader, i, 1))
                ach[i] = '1';
            else
                ach[i] = '-';
        ach[i] = '\0';

        DisplayError ("DEBUG", ach); */

    ULONG   ul;

    pis->seekg (0L, ios::end);
    ul = pis->tellg ();
    if (QueryBitrate () > 0)
    {
        if (IsTagged ())
            ulTime = (ul+S_TAGOFFSET)/(QueryBitrate ()*125L);
        else
            ulTime = ul/(QueryBitrate ()*125L);
    }
    else
        ul = 0L;

    IsValid (TRUE);
}

// ** Close *************************************************************** /*fold00*/

VOID MP3 :: Close (VOID)
{
    if (pis)
    {
        delete pis;
        pis = NULL;
    }
}

// ************************************************************************
