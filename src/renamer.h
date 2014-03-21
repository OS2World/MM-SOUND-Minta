/***
 renamer.h
 ***/

#ifndef _RENAMER_H_
#define _RENAMER_H_

#include "minta.h"
#include "settings.h"
#include "mp3.h"

// ** classdef ************************************************************ /*FOLD00*/

class Renamer
{
    friend class MP3Display;

public:
    Renamer (MP3DISPLAY &mp3d) { pmp3d = &mp3d; }

    BOOL   Dialog (VOID);

    BOOL   Rename (PMP3 pmp3, PSZ pszTemplate, BOOL fReplaceSpaces,
                   USHORT cb);

private:
    static MRESULT EXPENTRY dp (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

    PMP3DISPLAY   pmp3d;
};

#include "mp3disp.h"

// ************************************************************************
#endif
