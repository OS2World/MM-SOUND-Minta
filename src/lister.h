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

#ifndef _LISTER_H_
#define _LISTER_H_

#include "minta.h"
#include "settings.h"
#include "mp3.h"

// ** classdef ************************************************************ /*FOLD00*/

class Lister
{
    friend class MP3Display;

public:
    Lister (MP3DISPLAY &mp3d);

    BOOL   Dialog (VOID);
    VOID   OutputList (VOID);

    BYTE   IncludeTitle (VOID);
    BYTE   IncludeTime (VOID);
    BYTE   IncludeArtist (VOID);
    BYTE   IncludeAlbum (VOID);
    BYTE   IncludeYear (VOID);
    BYTE   IncludeGenre (VOID);
    BYTE   IncludeComment (VOID);

    BYTE   IncludeHeader (VOID);
    BYTE   IncludeTotalTime (VOID);

    BOOL   AutoSize (VOID);
    VOID   AutoSize (BOOL f);

    BOOL   OnlyTagged (VOID);
    VOID   OnlyTagged (BOOL f);

    VOID   IncludeTitle (BYTE b);
    VOID   IncludeTime (BYTE b);
    VOID   IncludeArtist (BYTE b);
    VOID   IncludeAlbum (BYTE b);
    VOID   IncludeYear (BYTE b);
    VOID   IncludeGenre (BYTE b);
    VOID   IncludeComment (BYTE b);

    VOID   IncludeHeader (BYTE b);
    VOID   IncludeTotalTime (BYTE b);

private:
    PSZ    QueryFilename (VOID);
    VOID   SetFilename (PSZ psz);

    BYTE   Include (USHORT us);
    VOID   Include (USHORT us, BYTE b);

    BOOL   SelectFile (VOID);

    BOOL   Output (PMP3 pmp3, fstream &os);
    BOOL   OutputHeader (fstream &os);
    BOOL   OutputTotalTime (fstream &os, ULONG ul);
    VOID   OutputLine (USHORT us, fstream &os);

    static MRESULT EXPENTRY
        DialogProcedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

    USHORT        usMaxLen[TAG_MAX];
    PMP3DISPLAY   pmp3d;

    HWND   hwnd;
};

#include "mp3disp.h"

// ** inline funcs ******************************************************** /*FOLD00*/

inline LISTER :: Lister (MP3DISPLAY &mp3d)
{
    // FIXME perhaps set to strlen ("Headertext")
    memset (usMaxLen, 0, sizeof (usMaxLen));
    pmp3d = &mp3d;
}

inline PSZ LISTER :: QueryFilename (VOID)
{
    return pmp3d->pset->QueryListfile ();
}

inline VOID LISTER :: SetFilename (PSZ psz)
{
    pmp3d->pset->SetListfile (psz);
}

inline BYTE LISTER :: IncludeTitle (VOID) {
    return pmp3d->pset->ListInclude (LINC_TITLE); }
inline BYTE LISTER :: IncludeTime (VOID) {
    return pmp3d->pset->ListInclude (LINC_TIME); }
inline BYTE LISTER :: IncludeArtist (VOID) {
    return pmp3d->pset->ListInclude (LINC_ARTIST); }
inline BYTE LISTER :: IncludeAlbum (VOID) {
    return pmp3d->pset->ListInclude (LINC_ALBUM); }
inline BYTE LISTER :: IncludeYear (VOID) {
    return pmp3d->pset->ListInclude (LINC_YEAR); }
inline BYTE LISTER :: IncludeGenre (VOID) {
    return pmp3d->pset->ListInclude (LINC_GENRE); }
inline BYTE LISTER :: IncludeComment (VOID) {
    return pmp3d->pset->ListInclude (LINC_COMMENT); }

inline BYTE LISTER :: IncludeHeader (VOID) {
    return pmp3d->pset->ListInclude (LINC_HEADER); }
inline BYTE LISTER :: IncludeTotalTime (VOID) {
    return pmp3d->pset->ListInclude (LINC_TOTALTIME); }

inline VOID LISTER :: IncludeTitle (BYTE b) {
    pmp3d->pset->ListInclude (LINC_TITLE, b); }
inline VOID LISTER :: IncludeTime (BYTE b) {
    pmp3d->pset->ListInclude (LINC_TIME, b); }
inline VOID LISTER :: IncludeArtist (BYTE b) {
    pmp3d->pset->ListInclude (LINC_ARTIST, b); }
inline VOID LISTER :: IncludeAlbum (BYTE b) {
    pmp3d->pset->ListInclude (LINC_ALBUM, b); }
inline VOID LISTER :: IncludeYear (BYTE b) {
    pmp3d->pset->ListInclude (LINC_YEAR, b); }
inline VOID LISTER :: IncludeGenre (BYTE b) {
    pmp3d->pset->ListInclude (LINC_GENRE, b); }
inline VOID LISTER :: IncludeComment (BYTE b) {
    pmp3d->pset->ListInclude (LINC_COMMENT, b); }

inline VOID LISTER :: IncludeHeader (BYTE b) {
    pmp3d->pset->ListInclude (LINC_HEADER, b); }
inline VOID LISTER :: IncludeTotalTime (BYTE b) {
    pmp3d->pset->ListInclude (LINC_TOTALTIME, b); }

inline BOOL LISTER :: AutoSize (VOID) {
    return pmp3d->pset->AutoSize (); }
inline VOID LISTER :: AutoSize (BOOL f) {
    pmp3d->pset->AutoSize (f); }

inline BOOL LISTER :: OnlyTagged (VOID) {
    return pmp3d->pset->OnlyTagged (); }
inline VOID LISTER :: OnlyTagged (BOOL f) {
    pmp3d->pset->OnlyTagged (f); }

inline BYTE LISTER :: Include (USHORT us) {
    return pmp3d->pset->ListInclude (us); }
inline VOID LISTER :: Include (USHORT us, BYTE b) {
    pmp3d->pset->ListInclude (us, b); }

inline VOID LISTER :: OutputLine (USHORT us, fstream &os)
{
    for (USHORT i = 0; i < us; i++)
        os << '-';
    os << ' ';
}

#endif
