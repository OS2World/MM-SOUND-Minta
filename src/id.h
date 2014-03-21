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

#define ID_MAIN                   1

#define ID_DLG_ABOUT              2
#define ID_DLG_LISTER             3
#define ID_DLG_SETTINGS           4
#define ID_DLG_STATUS             5
#define ID_DLG_NOTIFY             6
#define ID_DLG_RENAMER            7

#define ID_DLG_FILE               10000

#define ID_DLG_SETTINGSPAGE1      41
#define ID_DLG_SETTINGSPAGE2      42
#define ID_DLG_SETTINGSPAGE3      43
#define ID_DLG_SETTINGSPAGE4      44

#define WID_NIL                             1    
                                                 
#define WID_PB_FILES                        2    
#define WID_PB_SAVE                         3    
#define WID_PB_REMOVE                       4    
#define WID_PB_ABOUT                        5    
#define WID_E_FREQUENCY                     6    
#define WID_E_BITRATE                       7    
#define WID_E_TIME                          8    
#define WID_E_MODE                          9    
#define WID_E_EMPHASIS                      10   
#define WID_E_TITLE                         11   
#define WID_E_ARTIST                        12   
#define WID_E_ALBUM                         13   
#define WID_E_COMMENT                       14   
#define WID_E_YEAR                          15   
#define WID_DDL_GENRE                       16   
#define WID_CB_PRIVATE                      17   
#define WID_CB_CRCS                         18   
#define WID_CB_COPYRIGHT                    19   
#define WID_CB_PADDING                      20   
#define WID_CB_ORIGINAL                     21   
#define WID_E_VERSION                       22   
#define WID_E_LAYER                         23   
#define WID_DDL_FILES                       24   
#define WID_G_FILES                         25   
#define WID_PB_SAVEALL                      26   
#define WID_PB_REMOVEALL                    27   
#define WID_PB_SETTINGS                     28   
#define WID_PB_HELP                         29   
#define WID_PB_SAVENEXT                     30   
#define WID_PB_SAVEPREV                     31   
#define WID_G_TAG                           32   
#define WID_PB_LIST                         33   
#define WID_E_LISTFILENAME                  34   
#define WID_PB_FIND                         35   
#define WID_CB_TITLE                        36   
#define WID_CB_YEAR                         37   
#define WID_CB_ALBUM                        38   
#define WID_CB_TIME                         39   
#define WID_CB_GENRE                        40   
#define WID_CB_COMMENT                      41   
#define WID_CB_ARTIST                       42   
#define WID_PB_OK                           43   
#define WID_PB_CANCEL                       44   
#define WID_CB_OUTPUTTIME                   45   
#define WID_CB_OUTPUTHEADER                 46   
#define WID_CB_OVERWRITE                    47   
#define WID_LB_INCLUDE                      48   
#define WID_PB_DELETEFROMLIST               49   
#define WID_CB_AUTOSIZE                     50   
#define WID_PB_AUTOOPEN                     51   
#define WID_PB_DELETEALLFROMLIST            52   
#define WID_CB_ONLYTAGGED                   53   
#define WID_SB_TRACK                        54   
#define WID_PB_SAVEKEEPNEXT                 55   
#define WID_PB_SAVEKEEPPREV                 56   
#define WID_PB_RENAMEALL                    57   
#define WID_CB_NOTIFYLOAD                   58   
#define WID_CB_NOTIFYSAVE                   59   
#define WID_CB_NOTIFYRENAME                 60   
#define WID_CB_NOTIFYREMOVE                 61   
#define WID_CB_NOTIFYLIST                   62   
#define WID_VS_LANGUAGE                     63   
#define WID_E_PLAYERCOMMAND                 64   
#define WID_PB_PLAY                         65   
#define WID_PB_SHOWBUTTONS                  66   
#define WID_PB_EXIT                         67   
#define WID_PB_SHOWFILEINFO                 68   
#define WID_G_FILEINFO                      69   
#define WID_ST_VERSION                      70   
#define WID_ST_LAYER                        71   
#define WID_ST_FREQUENCY                    72   
#define WID_ST_BITRATE                      73   
#define WID_ST_MODE                         74   
#define WID_ST_EMPHASIS                     75   
#define WID_ST_TIME                         76   
#define WID_ST_TITLE                        77   
#define WID_ST_ARTIST                       78   
#define WID_ST_ALBUM                        79   
#define WID_ST_YEAR                         80   
#define WID_ST_COMMENT                      81   
#define WID_ST_GENRE                        82   
#define WID_ST_TRACK                        83   
#define WID_E_GENRESFILE                    84   
#define WID_CB_FILENAMETOTITLE              85   
#define WID_E_FILE                          86   
#define WID_S_PROGRESS                      87   
#define WID_ST_COUNT                        88   
#define WID_NB_SETTINGS                     89   
#define WID_CB_KEEPTITLE                    90   
#define WID_CB_KEEPARTIST                   91   
#define WID_CB_KEEPALBUM                    92   
#define WID_CB_KEEPYEAR                     93   
#define WID_CB_KEEPGENRE                    94   
#define WID_CB_KEEPCOMMENT                  95   
#define WID_CB_KEEPTRACK                    96   
#define WID_CB_ADJUSTTRACK                  97   
#define WID_CB_ONLYIFMISSING                98   
#define WID_CB_KEEP                         99   
#define WID_RB_CLICKAWAY                    100  
#define WID_RB_TIMER                        101  
#define WID_RB_BEEP                         102  
#define WID_ST_NOTIFY                       103  
#define WID_LB_LANGUAGES                    104  
#define WID_CB_LIMITRENAME                  105  
#define WID_ST_LANGNOTE                     106  
#define WID_CB_NOINVALIDMP3WARNING          107
#define WID_PB_UNDO                         108
#define WID_CB_ONLYREADONLY                 109
#define WID_LB_MACROS                       110
#define WID_E_TEMPLATE                      111
#define WID_CB_LIMITLENGTH                  112
#define WID_SB_LENGTH                       113
#define WID_CB_REPLACESPACES                114
#define WID_PB_RENAME                       115
#define WID_PB_CUTTAG                       116
#define WID_PB_COPYTAG                      117
#define WID_PB_PASTETAG                     118
#define WID_CB_CUSTOMFILEDIALOG             119
#define WID_PB_SHOWTOOLBAR                  120
#define WID_PB_PREV                         121
#define WID_PB_NEXT                         122
#define WID_MAIN_HELP                       123

#ifdef _SPLITNLS_
#define WID_LB_LANGUAGESHELP                120
#endif

#define WID_PB_TEST               13273

#define UM_REFRESHDISPLAY         WM_USER+1000
#define UM_XYZ                    WM_USER+1001
#define UM_OPENFILES              WM_USER+1002
#define UM_SETTINGS2DIALOG        WM_USER+1003

#define WID_MENU_FILES            1
#define WID_MENU_TAG              2

#define ID_BITMAP_GERMAN          1
#define ID_BITMAP_ENGLISH         2

#define MAIN_HELP_TABLE                     1000

#define SUBTABLE_MAIN                       2000
#define PANEL_MAIN                          2100
#define PANEL_FILELIST                      2210
#define PANEL_FILEINFO                      2220
#define PANEL_TAGINFO                       2230
#define PANEL_BUTTONS                       2240

#define SUBTABLE_LISTER                     3000
#define PANEL_LISTER                        3100

#define SUBTABLE_SETTINGS                   4000
#define PANEL_SETTINGS                      4100

#define SUBTABLE_RENAMER                    5000

#define PANEL_KEYSHELP                      3

#define ID_DLG_FINDDIR       1000

#define WID_LB_DRIVES        1001
#define WID_LB_DIRECTORIES   1002
#define WID_ST_PATH          1003

#define ID_ACCELTABLE_FINDDIR     1000
#define ID_ACCELTABLE_SETTINGS    1001

#define IDS_ERROR_GENREFILEHEADING               1
#define IDS_ERROR_COULDNOTOPENGENREFILE          2
#define IDS_ERROR_HELPERHEADING                  3
#define IDS_ERROR_COULDNOTINITHELP               4
#define IDS_ERROR_BORINGLISTHEADING              5
#define IDS_ERROR_BORINGLIST                     6
#define IDS_ERROR_LISTFILEHEADING                7
#define IDS_ERROR_MUSTGIVEVALIDLISTFILENAME      8
#define IDS_ERROR_GENERALHEADING                 9
#define IDS_ERROR_WRONGGENREFOUND                10
#define IDS_SCANNINGFORMAT                       11
#define IDS_WRITINGFORMAT                        12
#define IDS_IGNORINGFORMAT                       13
#define IDS_SEARCHINGFORMAT                      14
#define IDS_SAVINGFORMAT                         15
#define IDS_RENAMINGFORMAT                       16
#define IDS_REMOVINGFORMAT                       17
#define IDS_FILESWRITTENTOLISTHEADING            18
#define IDS_FILESWRITTENTOLIST                   19
#define IDS_ERROR_COULDNOTOPENLISTFILE           20
#define IDS_SELECTLISTFILE                       21
#define IDS_LISTFILENAME                         22
#define IDS_LISTTITLE                            23
#define IDS_LISTTIME                             24
#define IDS_LISTARTIST                           25
#define IDS_LISTALBUM                            26
#define IDS_LISTYEAR                             27
#define IDS_LISTGENRE                            28
#define IDS_LISTCOMMENT                          29
#define IDS_LISTVERSION                          30
#define IDS_LISTLAYER                            31
#define IDS_LISTFREQUENCY                        32
#define IDS_LISTBITRATE                          33
#define IDS_LISTMODE                             34
#define IDS_ERROR_MP3FILEHEADING                 35
#define IDS_ERROR_COULDNOTOPENMP3FILE            36
#define IDS_ERROR_NOVALIDMP3FILE                 37
#define IDS_ERROR_COULDNOTGETFILESIZE            38
#define IDS_ERROR_COULDNOTREMOVETAG              39
#define IDS_GENRENONE                            40
#define IDS_OPENMP3FILES                         41
#define IDS_NOFILENOTAG                          42
#define IDS_ID3TAGREADONLY                       43
#define IDS_ID3TAG                               44
#define IDS_FILEHASNOTAGREADONLY                 45
#define IDS_FILEHASNOTAG                         46
#define IDS_NOFILESSELECTED                      47
#define IDS_ONEFILESELECTED                      48
#define IDS_FILESSELECTED                        49
#define IDS_FILESINSERTEDHEADING                 50
#define IDS_FILESWEREINSERTED                    51
#define IDS_ONEFILEWASINSERTED                   52
#define IDS_NOFILESFOUNDHEADING                  53
#define IDS_NONEWFILESWEREFOUND                  54
#define IDS_ERROR_INIFILEHEADING                 55
#define IDS_ERROR_NOOROLDINIFILE                 56
#define IDS_ERROR_COULDNOTOPENINIFILE            57
#define IDS_XOFX                                 58
#define IDS_OK                                   59
#define IDS_REALLYSAVETAGSHEADING                60
#define IDS_REALLYSAVETAGS                       61
#define IDS_SAVEALL                              62
#define IDS_TAGSSAVEDHEADING                     63
#define IDS_SOMETAGSSAVED                        64
#define IDS_ALLTAGSSAVED                         65
#define IDS_REALLYRENAMEALLHEADING               66
#define IDS_REALLYRENAMEALL                      67
#define IDS_ERROR_RENAMINGFAILED                 68
#define IDS_FILESRENAMEDHEADING                  69
#define IDS_SOMEFILESRENAMED                     70
#define IDS_ALLFILESRENAMED                      71
#define IDS_REALLYREMOVETAGSHEADING              72
#define IDS_REALLYREMOVETAGS                     73
#define IDS_TAGSREMOVEDHEADING                   74
#define IDS_SOMETAGSREMOVED                      75
#define IDS_ALLTAGSREMOVED                       76
#define IDS_TOTALTIME                            77
#define IDS_UNKNOWN                              78
#define IDS_NONE                                 79
#define IDS_STEREO                               80
#define IDS_JOINTSTEREO                          81
#define IDS_DUALCHANNEL                          82
#define IDS_SINGLECHANNEL                        83
#define IDS_TITLE                                84
#define IDS_TIME                                 85
#define IDS_ARTIST                               86
#define IDS_ALBUM                                87
#define IDS_YEAR                                 88
#define IDS_GENRE                                89
#define IDS_COMMENT                              90
#define IDS_FILENAMEPATH                         91
#define IDS_VERSION                              92
#define IDS_LAYER                                93
#define IDS_FREQUENCY                            94
#define IDS_BITRATE                              95
#define IDS_MODE                                 96
#define IDS_PAGENOTIFICATION                     97
#define IDS_PAGEKEEPINFO                         98
#define IDS_PAGEMISC                             99
#define IDS_PAGELANGUAGE                         100
#define IDS_ERROR_LAUNCHFAILED                   101
#define IDS_ERROR_GENREIDALREADYASSIGNED         102
#define IDS_UNKNOWNGENRENAME                     103
#define IDS_ERROR_NOFILENODIR                    104
#define IDS_NOFILENOINFO                         105
#define IDS_FILEINFOGROUPNAME                    106
#define IDS_FILEINFOGROUPNAMEINVALID             107
#define IDS_ERROR_COULDNOTINITHELPFILE           108
#define IDS_RENAMETITLE                          109
#define IDS_RENAMETIME                           110
#define IDS_RENAMEARTIST                         111
#define IDS_RENAMEALBUM                          112
#define IDS_RENAMEYEAR                           113
#define IDS_RENAMEGENRE                          114
#define IDS_RENAMECOMMENT                        115
#define IDS_RENAMEVERSION                        116
#define IDS_RENAMELAYER                          117
#define IDS_RENAMEFREQUENCY                      118
#define IDS_RENAMEBITRATE                        119
#define IDS_RENAMEMODE                           120
#define IDS_FILEHASUNSUPPORTEDTAG                121

#define SEI_DIRECTORIESWORK                      1
#define SEI_FILENAMETOTITLE                      2
#define SEI_GENRESFILE                           3
#define SEI_LANGUAGE                             4
//#define SEI_LIMITRENAME                          5
#define SEI_NOINVALIDMP3WARNING                  6
#define SEI_ONLYREADONLY                         7
#define SEI_PLAYERCOMMAND                        8
#define SEI_SHOWBUTTONS                          9
#define SEI_SHOWFILEINFO                         10
#define SEI_KEEP                                 11
#define SEI_KEEPADJUSTTRACK                      12
#define SEI_KEEPONLYIFMISSING                    13
#define SEI_KEEPTAGINFO                          14
#define SEI_AUTOSIZE                             15
#define SEI_INCLUDE                              16
#define SEI_LISTFILE                             17
#define SEI_ONLYTAGGED                           18
#define SEI_NOTIFYLIST                           19
#define SEI_NOTIFYLOAD                           20
#define SEI_NOTIFYREMOVE                         21
#define SEI_NOTIFYRENAME                         22
#define SEI_NOTIFYSAVE                           23
#define SEI_NOTIFYSTYLE                          24
#define SEI_BACKGROUNDCOLOR                      25
#define SEI_FONTNAMESIZE                         26
#define SEI_SWP                                  27
#define SEI_US                                   28
#define SEI_RENAMETEMPLATE                       29
#define SEI_RENAMELIMITLENGTH                    30
#define SEI_RENAMELENGTH                         31
#define SEI_RENAMEREPLACESPACES                  32
#define SEI_CUSTOMFILEDIALOG                     33
#define SEI_LANGUAGEHELP                         34
#define SEI_SHOWTOOLBAR                          35
