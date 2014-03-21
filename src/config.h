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

// do (more) error checking
#define _PARANOID_

// log several events to a logfile
//#define _DEBUGLOG_

// ???
//#define _TEST_

// use the new lister dialog
// WARNING: Disabling this is now unsupported
#define _NEWLISTER_

// do not clear the selected files list before opening files.
// disabling this is not very useful any more and no longer supported
// on various places in the source.
#define _MULTIDIRSELECT_

// use the MP3 header decoding routines from mpg123
#define _123HEADER_

// enable launching MP3 player for current file
#define _PLAYERCOMMAND_

// enable hiding/showing of fileinfo group
#define _SHOWFILEINFO_

// load genres from "genres.txt"
#define _LOADGENRES_

// "Filename -> Title" option
#define _FILENAMETOTITLE_

// enable adding files by drag'n'drop
#define _DRAGNDROP_

// #define this for lots of problems ... :-(
//#define _STATUSDISPLAY_

// use new settings notebook
// WARNING: Disabling this is now unsupported
#define _NEWSETTINGS_

// support multiple languages via resources
// WARNING: Disabling this is now unsupported
#define _MULTILANGUAGES_

// support splitted NLS
#define _SPLITNLS_

// allow tag fields to be padded with spaces
#define _WARPAMPFIX_

// use toolbar
// not working right now!
//#define _TOOLBAR_

// allow customization of the buttons through the settings window
// not working right now!
//#define _CUSTOMBUTTONS_

// Allow command switch for two digit tracknumbers when renaming.
//#define _TWO_DIGIT_TRACKNUMBERS_

// Allow "length" parameters after macro tracknumbers placeholders.
#define _CUSTOMIZABLE_TRACKNUMBERS_WIDTH_

// Allow to set ini file path on command line.
#define _SET_INI_FILE_PATH_

// Allow disabling of EA error while renaming; on some configurations
// while renaming still seems to work, the function returns an error.
#define _ALLOW_DISABLE_EA_ERROR_

// If Minta is called from another dir, try to find the "home directory"
// (where the exe is) and load all files from there.
#define _FROM_FOREIGN_DIR_
