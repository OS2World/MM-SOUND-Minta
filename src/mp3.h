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

#ifndef _MP3_H_
#define _MP3_H_

#include "minta.h"

#ifdef _LOADGENRES_
#include "genlist.h"
#endif

// ** defines & enums ***************************************************** /*FOLD00*/

#ifndef _LOADGENRES_
#define MAX_GENRES           115
#endif

#define GENREID_NIL          MAX_GENRES
#define GENREID_DEFAULT      12  // "Other"
#define S_TAGOFFSET         -128
#define CHAR_COMMENTMACRO    '$'
#define MAX_TRACK            255

enum
{
    TAG_TITLE, TAG_ARTIST, TAG_ALBUM, TAG_YEAR, TAG_COMMENT, TAG_GENRE,
    TAG_NIL,
    TAG_FILENAME, TAG_TIME, TAG_VERSION, TAG_LAYER, TAG_FREQ, TAG_BITRATE,
    TAG_MODE,
    TAG_MAX
};

enum { MP3ERR_NONE, MP3ERR_INVALIDFORMAT, MP3ERR_FILENOTOPEN };

enum { VER_UNKNOWN, VER_MPEG1, VER_MPEG2, VER_MPEG25, VER_MAX };

typedef USHORT VERSION;

enum { LAYER_UNKNOWN, LAYER_1, LAYER_2, LAYER_3, LAYER_MAX };

typedef USHORT LAYER;

enum { MODE_STEREO, MODE_JOINTSTEREO, MODE_DUALCHANNEL, MODE_MONO };

typedef USHORT MODE;

#define PSZ_TAGSIGNATURE   "TAG"

#define MAXLEN_TITLE    30
#define MAXLEN_ARTIST   30
#define MAXLEN_ALBUM    30
#define MAXLEN_YEAR     4
#define MAXLEN_COMMENT  30

// ** classdef ************************************************************ /*FOLD00*/

class MP3File
{
    friend class MP3Display;

public:
    MP3File (STRING strFilename);
    ~MP3File (VOID);

    VERSION   QueryVersion (VOID);
    PSZ       QueryVersionName (VOID);
    LAYER     QueryLayer (VOID);
    PSZ       QueryLayerName (VOID);

    ULONG     QueryFrequency (VOID);
    ULONG     QueryBitrate (VOID);
    ULONG     QueryTime (VOID);
    MODE      QueryMode (ULONG *ulBands);
    PSZ       QueryModeName (VOID);

    PSZ       QueryTitle (VOID);
    PSZ       QueryArtist (VOID);
    PSZ       QueryAlbum (VOID);
    PSZ       QueryComment (VOID);
    PSZ       QueryYear (VOID);
    USHORT    QueryGenre (VOID);
    USHORT    QueryTrack (VOID);
    PSZ       QueryGenreName (VOID);
    USHORT    QueryEmphasis (VOID);
    PSZ       QueryEmphasisName (VOID);

    STRING    &QueryFilename (VOID);
    PSZ       QueryTagVersion (VOID);

    BOOL      HasCRCs (VOID);
    BOOL      HasPadding (VOID);
    BOOL      IsPrivate (VOID);
    BOOL      IsCopyright (VOID);
    BOOL      IsOriginal (VOID);

    BOOL      IsTagged (VOID);
    VOID      IsTagged (BOOL f);

    BOOL      IsReadOnly (VOID);
    VOID      IsReadOnly (BOOL f);

    BOOL      IsValid (VOID);
    VOID      IsValid (BOOL f);

    LONG      Error (VOID) { return err; }

    BOOL      HasValidHeader (VOID);
    VOID      HasValidHeader (BOOL f);

    VOID      SetTitle (PSZ psz);
    VOID      SetArtist (PSZ psz);
    VOID      SetAlbum (PSZ psz);
    VOID      SetComment (PSZ psz);
    VOID      SetYear (PSZ psz);
    VOID      SetGenre (USHORT us);
    VOID      SetTrack (USHORT us);

    BOOL      ExpandMacros (PSZ pszTemplate, PSZ psz, USHORT cb);
    BOOL      Rename (PSZ psz);

    VOID      Close (VOID);

    BOOL      HasUnsupportedTag (VOID) { return fHasUnsupportedTag; }

private:
    BOOL    SaveTag (VOID);
    BOOL    RemoveTag (VOID);

    VOID    Reload (VOID);

    VOID    PaddWithZeros (PSZ psz, USHORT usMax);
    VOID    FinalizeComment (VOID);

    BOOL    ReadHeader (VOID);
    BOOL    FindHeader (istream *pis, ULONG &ul);
    BOOL    ValidHeader (ULONG ul);
    BOOL    ReadHeaderBytes (istream *pis, ULONG &ul);

/*    struct Header
    {
        USHORT   usSync : 12;
        USHORT   usVersion : 1;
        USHORT   usLayer : 2;
        USHORT   usProtect : 1;
        USHORT   usBitrate : 4;
        USHORT   usFreq : 2;
        USHORT   usPadd : 1;
        USHORT   usPrivate : 1;
        USHORT   usMode : 2;
        USHORT   usModeExt : 2;
        USHORT   usCopyright : 1;
        USHORT   usOriginal : 1;
        USHORT   usEmphasis : 2;
    } Header; */
#ifndef _123HEADER_
    struct Header
    {
        USHORT   usSync1 : 8;

        USHORT   usVersion : 1;
        USHORT   usLayer : 2;
        USHORT   usProtect : 1;
        USHORT   usSync2 : 4;

        USHORT   usFreq : 2;
        USHORT   usPadd : 1;
        USHORT   usPrivate : 1;
        USHORT   usBitrate : 4;

        USHORT   usEmphasis : 2;
        USHORT   usOriginal : 1;
        USHORT   usCopyright : 1;
        USHORT   usModeExt : 2;
        USHORT   usMode : 2;
    } Header;
#else
    struct Header
    {
        SHORT   usSync1;
        SHORT   usVersion;
        SHORT   usLayer;
        SHORT   usProtect;
        SHORT   usSync2;
        SHORT   usFreq;
        SHORT   usPadd;
        SHORT   usPrivate;
        SHORT   usBitrate;
        SHORT   usEmphasis;
        SHORT   usOriginal;
        SHORT   usCopyright;
        SHORT   usModeExt;
        SHORT   usMode;
    } Header;
#endif

    STRING  strFilename;

    CHAR    pszTitle[MAXLEN_TITLE+1], pszArtist[MAXLEN_ARTIST+1];
    CHAR    pszAlbum[MAXLEN_ALBUM+1], pszComment[MAXLEN_COMMENT+1];
    CHAR    pszYear[MAXLEN_YEAR+1];
    SHORT   sGenre, sTrack;
    ULONG   ulTime;
    BOOL    fReadOnly, fIsTagged, fIsV25, fValid, fHasValidHeader;

    static PSZ   pszUnknownGenre;

    static PSZ   apszVersions[4];
    static PSZ   apszLayers[4];
    static PSZ   apszModes[4];
    static PSZ   apszEmphasis[4];
#ifndef _LOADGENRES_
    static PSZ   apszGenres[MAX_GENRES];
#endif

    fstream  *pis;

    LONG     err;
    BOOL     fHasUnsupportedTag;
    USHORT   usTagVersion[3];
};

// ** inline funcs ******************************************************** /*FOLD00*/

inline MP3 :: ~MP3File (VOID)
{
    Close ();
}

// ------------------------------------------------------------------------

inline VERSION MP3 :: QueryVersion (VOID)
{
    if (fIsV25)
        return VER_MPEG25;

    return Header.usVersion+1;
}

inline PSZ MP3 :: QueryVersionName (VOID) {
    return MP3::apszVersions[QueryVersion ()]; }

// ------------------------------------------------------------------------

inline LAYER MP3 :: QueryLayer (VOID) {
    return Header.usLayer; }

inline PSZ MP3 :: QueryLayerName (VOID) {
    return MP3::apszLayers[QueryLayer ()]; }

// ------------------------------------------------------------------------

inline ULONG MP3 :: QueryTime (VOID)        { return ulTime; }
inline STRING &MP3 :: QueryFilename (VOID)  { return strFilename; }

inline PSZ MP3 :: QueryTagVersion (VOID)
{
    static CHAR ach[5];
    if (HasUnsupportedTag ())
    {
        sprintf (ach, "%d.%d.%d", usTagVersion[0], usTagVersion[1], usTagVersion[2]);
        return ach;
    }

    if (sTrack)
        return "1.1";
    return "1.0";
}

// ------------------------------------------------------------------------

inline USHORT MP3 :: QueryEmphasis (VOID)   { return Header.usEmphasis; }

inline PSZ MP3 :: QueryEmphasisName (VOID) {
    return MP3::apszEmphasis[QueryEmphasis ()]; }

// ------------------------------------------------------------------------

inline BOOL MP3 :: HasCRCs (VOID)      { return BOOL (Header.usProtect); }
inline BOOL MP3 :: HasPadding (VOID)   { return BOOL (Header.usPadd); }
inline BOOL MP3 :: IsPrivate (VOID)    { return BOOL (Header.usPrivate); }
inline BOOL MP3 :: IsCopyright (VOID)  { return BOOL (Header.usCopyright); }
inline BOOL MP3 :: IsOriginal (VOID)   { return BOOL (Header.usOriginal); }

inline BOOL MP3 :: IsTagged (VOID)     { return BOOL (fIsTagged); }
inline VOID MP3 :: IsTagged (BOOL f)   { fIsTagged = f; }

inline BOOL MP3 :: IsReadOnly (VOID) {
    return BOOL (fReadOnly) || HasUnsupportedTag (); }

inline VOID MP3 :: IsReadOnly (BOOL f) { fReadOnly = f; }

inline BOOL MP3 :: IsValid (VOID)   { return BOOL (fValid); }
inline VOID MP3 :: IsValid (BOOL f) { fValid = f; }

inline BOOL MP3 :: HasValidHeader (VOID)   { return BOOL (fHasValidHeader); }
inline VOID MP3 :: HasValidHeader (BOOL f) { fHasValidHeader = f; }

inline PSZ MP3 :: QueryTitle (VOID)   { return pszTitle; }
inline PSZ MP3 :: QueryArtist (VOID)  { return pszArtist; }
inline PSZ MP3 :: QueryAlbum (VOID)   { return pszAlbum; }
inline PSZ MP3 :: QueryComment (VOID) { return pszComment; }
inline PSZ MP3 :: QueryYear (VOID)    { return pszYear; }
inline USHORT MP3 :: QueryGenre (VOID)    { return sGenre; }
inline USHORT MP3 :: QueryTrack (VOID)    { return sTrack; }

inline VOID MP3 :: SetTitle (PSZ psz)
{
    strncpy (pszTitle, psz, MAXLEN_TITLE);
    pszTitle[MAXLEN_TITLE] = '\0';
}

inline VOID MP3 :: SetArtist (PSZ psz)
{
    strncpy (pszArtist, psz, MAXLEN_ARTIST);
    pszArtist[MAXLEN_ARTIST] = '\0';
}

inline VOID MP3 :: SetAlbum (PSZ psz)
{
    strncpy (pszAlbum, psz, MAXLEN_ALBUM);
    pszAlbum[MAXLEN_ALBUM] = '\0';
}

inline VOID MP3 :: SetComment (PSZ psz)
{
    strncpy (pszComment, psz, MAXLEN_COMMENT);
    pszComment[MAXLEN_COMMENT] = '\0';
}

inline VOID MP3 :: SetYear (PSZ psz)
{
    strncpy (pszYear, psz, MAXLEN_YEAR);
    pszYear[MAXLEN_YEAR] = '\0';
}

inline VOID MP3 :: SetGenre (USHORT us) {
    sGenre = us; }
inline VOID MP3 :: SetTrack (USHORT us) {
    sTrack = us; }

inline VOID MP3 :: PaddWithZeros (PSZ psz, USHORT usMax)
{
#ifdef _WARPAMPFIX_
    if (g_fUseSpaces)
        memset (psz+strlen (psz), ' ', usMax-strlen (psz));
    else
#endif
        memset (psz+strlen (psz), 0x00, usMax-strlen (psz));
}

inline PSZ MP3 :: QueryModeName (VOID) {
    return MP3::apszModes[QueryMode (NULL)]; }

inline PSZ MP3 :: QueryGenreName (VOID)
{
#ifndef _LOADGENRES_
    if (QueryGenre () >= MAX_GENRES)
        return "(error)";

    return MP3::apszGenres[QueryGenre ()];
#else
    if (! GETGENLIST.QueryName (QueryGenre ()))
        return pszUnknownGenre;
    return GETGENLIST.QueryName (QueryGenre ());
#endif
}

#include "mp3disp.h"

// ************************************************************************
#endif
