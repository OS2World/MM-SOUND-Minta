/***
 settings.cpp
 ***/

#include "thth_settings.h"

#ifndef NO_ERROR
#define NO_ERROR 0
#endif

// ** Settings ************************************************************ /*FOLD00*/

THTH_SETTINGS :: ththSettings (PTHTH_SE *ppse, PSZ pszInifile, ULONG ulVersion)
{
    // what's this?!? well, just forget about doing inits ...
    if (! ppse)
        return;
    this->ppse = ppse;

    // reset - everything should already be on defaults, but just in case ...
    Reset ();

    // shall we use the pro-file?
    if (! pszInifile)
        return;
    psz = pszInifile;  // FIXME maybe do a strdup instead ...

    ulError = 0;

    // check if a pro-file does exist; if not we need not complain
    // about wrong version
    if (access(pszInifile, 0) != NO_ERROR) {
        ulVersion = 0;
        ulError = 3; // "select language" needed
    }

    // open the pro-file
    CHAR   ach[_MAX_PATH];
    strcpy (ach, psz);
    if (! (hini = PrfOpenProfile (GETHAB, ach)))
    {
        ulError = 1;
        return;
    }

    // shall we check the version number?
    if (ulVersion) {
        if ((this->ulVersion =
             PrfQueryProfileInt (hini, "Profile", "Version", 0L))) {
            if (this->ulVersion != ulVersion) {
                ulError = 2;
                return;
            }
        } else
            ulError = 4; // INI file corrupted or wrong ini file
    }

    // awright baby, load the stuff! ;-)
    Load ();
}

// ** Save ****************************************************************

BOOL THTH_SETTINGS :: Save (VOID)
{
    if (!hini || !ppse)
        return FALSE;

    if (ulVersion)
    {
        CHAR   ach[11];
        sprintf (ach, "%lu", ulVersion);
        PrfWriteProfileString (hini, "Profile", "Version", ach);
    }

    // awright baby, save the stuff! ;-)
    for (LONG i = 0; ppse[i]; i++)
        ppse[i]->Save (hini);

    return TRUE;
}

// ** ~Settings *********************************************************** /*FOLD00*/

THTH_SETTINGS :: ~ththSettings (VOID)
{
    // the only thing we might need to do is save the stuff to the pro-file
    Save ();

    // goodbye pro-file!
    if (hini) { PrfCloseProfile (hini); }
    hini = NULL;

    // FIXME if we copied the filename, delete it now
}

// ************************************************************************
