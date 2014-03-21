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

#include "genlist.h"

// ** GenreList *********************************************************** /*FOLD00*/

GENLIST :: GenreList (PSZ psz)
{
    for (c = 0; c < MAX_GENRES; c++)
        apsz[c] = NULL;

    c = cLines = cNextFree = 0;

    ifstream   ifs (psz);
    CHAR       ach[257];
    BOOL       fMintaLine;

#ifdef _FROM_FOREIGN_DIR_
    // Maybe we're in another directory ...
    if( !ifs ) {
        CHAR pszFile[_MAX_PATH];
        ifs.close();
        sprintf( pszFile, "%s%s", g_pszMintaDir, psz );
        ifs.open( pszFile );
    }
#endif

    if (ifs)
    {
        while (ifs.good () && (c < MAX_GENRES))
        {
            ifs.getline (ach, sizeof (ach));
            cLines ++;
            fMintaLine = TRUE;

            if ((ach[0] != '#') && strlen (ach) >= 1)
            {
                PSZ   psz;

                strkspc (ach);

                // check if the line starts with a number ("WarpAMP format")
                if ((psz = strchr (ach, ' ')))
                {
                    *psz = '\0';
                    if (strspn (ach, "0123456789") == strlen (ach))
                    {
                        // skip spaces at begining of genre name
                        do
                            psz ++;
                        while (isspace (*psz) && *psz);
                        AddGenre (psz, atoi (ach));
                        fMintaLine = FALSE;
                    }
                    else
                        *psz = ' ';
                }

                // it wasn't a "WarpAMP format" line
                if (fMintaLine)
                    AddGenre (ach);
            }
        }
    }
    else
#ifdef _MULTILANGUAGES_
        DisplayError (RSTR (IDS_ERROR_GENREFILEHEADING),
                      RSTR (IDS_ERROR_COULDNOTOPENGENREFILE),
                      psz, errno);
#else
        DisplayError ("GENRE FILE NOT OPEN",
                      "Could not open genre file \"%s\". Error %d.",
                      psz, errno);
#endif
}

// ** ~GenreList ********************************************************** /*fold00*/

GENLIST :: ~GenreList (VOID)
{
    for (USHORT i = 0; i < c; i++)
        if (apsz[i])
            free (apsz);
}

// ** QueryName *********************************************************** /*fold00*/

PSZ GENLIST :: QueryName (USHORT us)
{
    if (us >= MAX_GENRES)
        return NULL;

    return (apsz[us]);
}

// ** AddGenre ************************************************************ /*FOLD00*/

USHORT GENLIST :: AddGenre (PSZ psz, USHORT id)
{
    if (id >= MAX_GENRES)
        return MAX_GENRES;
    
    if (apsz[id] != NULL)
    {
#ifdef _MULTILANGUAGES_
        DisplayError (RSTR (IDS_ERROR_GENREFILEHEADING),
                      RSTR (IDS_ERROR_GENREIDALREADYASSIGNED),
                      id, cLines);
#else
        DisplayError ("GENRE FILE ERROR",
                      "The id (%d) of the genre in line %d "
                      "has already been assigned.",
                      id, cLines);
#endif
        return MAX_GENRES;
    }

    apsz[id] = strdup (psz);
    c ++;

    if (id == cNextFree)
        while ((apsz[cNextFree] != NULL) && (cNextFree < MAX_GENRES))
            cNextFree ++;

    return id;
}

// ------------------------------------------------------------------------ /*fold00*/

USHORT GENLIST :: AddGenre (PSZ psz)
{
    if (cNextFree >= MAX_GENRES)
        return MAX_GENRES;

    USHORT   cDummy = cNextFree;

    apsz[cNextFree] = strdup (psz);
    c ++;

    while ((apsz[cNextFree] != NULL) && (cNextFree < MAX_GENRES))
        cNextFree ++;

    return (cDummy);
}

// ************************************************************************
