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

#ifndef _GENLIST_H_
#define _GENLIST_H_

#include "minta.h"

#define MAX_GENRES           256

class GenreList
{
public:
    GenreList (PSZ psz);
    ~GenreList (VOID);

    USHORT   QueryCount (VOID);
    PSZ      QueryName (USHORT us);

private:
    USHORT   AddGenre (PSZ psz, USHORT id);
    USHORT   AddGenre (PSZ psz);

    USHORT   c, cLines, cNextFree;
    PSZ      apsz[MAX_GENRES];
};

inline USHORT GENLIST :: QueryCount (VOID)  { return c; }

#endif
