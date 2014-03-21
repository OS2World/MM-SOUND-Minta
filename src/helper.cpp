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

#include "helper.h"

// ** Helper ************************************************************** /*FOLD00*/

HELPER :: Helper (HWND hwnd)
{
    HELPINIT   helpInit;

    // if we return because of an error, Help will be disabled
    fHelpEnabled = TRUE;

    // inititalize help init structure
    helpInit.cb                  = sizeof (HELPINIT);
    helpInit.ulReturnCode        = 0L;
    helpInit.pszTutorialName     = PSZ (NULL);
    helpInit.phtHelpTable        = PHELPTABLE (MAKELONG (MAIN_HELP_TABLE,
                                                         0xFFFF));
    helpInit.hmodHelpTableModule = GETMODULE;
    helpInit.hmodAccelActionBarModule = GETMODULE;
    helpInit.idAccelTable        = 0;
    helpInit.idActionBar         = 0;
    helpInit.pszHelpWindowTitle  = PSZ (PSZ_NAMEVERSION);
    helpInit.fShowPanelId        = CMIC_HIDE_PANEL_ID;

    CHAR   ach[_MAX_FNAME+_MAX_EXT];
#ifdef _SPLITNLS_
    sprintf (ach, "%s.hlp", GETSETTINGS->QueryString (SEI_LANGUAGEHELP));
#else
    sprintf (ach, "%s.hlp", GETSETTINGS->QueryLanguage ());
#endif

#ifdef _FROM_FOREIGN_DIR_
    CHAR pszFile[_MAX_PATH];
    sprintf( pszFile, "%s%s", g_pszMintaDir, ach );
    helpInit.pszHelpLibraryName  = PSZ (pszFile);
#else
    helpInit.pszHelpLibraryName  = PSZ (ach);
#endif

    // create the help instance
    hwndHelpInstance = WinCreateHelpInstance (hab, &helpInit);
    if (!hwndHelpInstance || helpInit.ulReturnCode)
    {
#ifdef _MULTILANGUAGES_
        DisplayError (RSTR (IDS_ERROR_HELPERHEADING),
                      RSTR (IDS_ERROR_COULDNOTINITHELPFILE), ach);
#else
        DisplayError ("ERROR",
                      "Could not initialize online help. Please check if "
                      "helpfile '%s' exists in Minta's directory.", ach);
#endif
        fHelpEnabled = FALSE;
    }

    // associate help instance with main frame
    if (! WinAssociateHelpInstance (hwndHelpInstance, hwnd))
    {
#ifdef _MULTILANGUAGES_
        DisplayError (RSTR (IDS_ERROR_HELPERHEADING),
                      RSTR (IDS_ERROR_COULDNOTINITHELP));
#else
        DisplayError ("ERROR", "Could not initialize online help.");
#endif
        fHelpEnabled = FALSE;
    }
}

// ** ~Helper ************************************************************* /*FOLD00*/

HELPER :: ~Helper (VOID)
{
    if (hwndHelpInstance)
        WinDestroyHelpInstance (hwndHelpInstance);
}

// ** DisplayPanel ******************************************************** /*FOLD00*/

VOID HELPER :: DisplayPanel (SHORT idPanel)
{
    if (fHelpEnabled)
    {
        WinSendMsg (hwndHelpInstance, HM_DISPLAY_HELP,
                    MPFROM2SHORT (idPanel, NULL), MPFROMSHORT (HM_RESOURCEID));
    }
}

// ************************************************************************
