/*************************************************************************/
/*  MINTA installation file - Creates a WPS-object for Minta             */
/*  To run this file, just type "install" on the OS/2 command line.      */
/*************************************************************************/

PARSE SOURCE operSystem . sourceFile

IF \(operSystem = "OS/2") THEN DO
    SAY "Please use only with IBM-OS/2 Operating system!"
    EXIT
    END

/*************************************************************************/

'@ECHO OFF'

CALL rxfuncadd 'sysloadfuncs', 'rexxutil', 'sysloadfuncs'
CALL sysloadfuncs

/*************************************************************************/

Ver = "2.52"
MintaDir = FILESPEC("drive", sourceFile)FILESPEC("path", sourceFile)

SAY ""

/*************************************************************************/

CALL SysFileTree MintaDir"MINTA.EXE",'file','F'
IF file.0 = 0 THEN DO
    SAY "MINTA.EXE was not found in the same directory as ",
    FILESPEC("name",sourceFile)

    DO UNTIL \(file.0 = 0)
        SAY ""
        SAY "Please give the full path to the file MINTA.EXE."
        SAY "(Press ENTER/RETURN alone to exit)"
        PULL MintaDir
        IF MintaDir = "" THEN
            EXIT
        IF (FILESPEC("drive",MintaDir) = "") | (FILESPEC("path",MintaDir) = "") THEN
            SAY 'You must give a full path in format "d:\path\"'
        ELSE DO
            IF \(SUBSTR(MintaDir,length(MintaDir),1) = "\" ) THEN
                MintaDir = MintaDir"\"
            CALL SysFileTree MintaDir"MINTA.EXE",'file','F'
            IF file.0 = 0 THEN
                SAY "Can not find "MintaDir"MINTA.EXE. Please try again."
            END
        END
    SAY ""
    END

/*************************************************************************/

SAY ""
SAY ""
CALL CHAROUT , "* Do you want your MP3-files associated with Minta [Y/N] ? "
key = SysGetKey('ECHO')
PARSE upper var key key
SAY ""
IF key = 'Y'  THEN DO
    setup = 'PROGTYPE=PM;EXENAME='MintaDir'MINTA.EXE;STARTUPDIR='MintaDir';'
    setup = setup'ICONFILE='MintaDir'MINTA.ICO;OBJECTID=<THTH_MINTA>;'
    setup = setup'ASSOCFILTER=*.MP3;ASSOCTYPE=MP3;'
    END
ELSE DO
    setup = 'PROGTYPE=PM;EXENAME='MintaDir'MINTA.EXE;STARTUPDIR='MintaDir';'
    setup = setup'ICONFILE='MintaDir'MINTA.ICO;OBJECTID=<THTH_MINTA>;'
    END

SAY ""
SAY "* Creating Minta WPS-object ..."
check = SysCreateObject('WPProgram', 'Minta 'Ver, '<WP_DESKTOP>', setup)

IF check = 0 THEN DO
    SAY "* Could not create WPS-object!"
    SAY "  (Does perhaps an object for Minta already exist?)"
    CALL CHAROUT , "* Do you want to replace the existing object [Y/N] ? "
    key = SysGetKey('ECHO')
    PARSE upper var key key
    SAY ""
    IF key <> 'Y' THEN
        EXIT

    SAY "* Replacing old Minta WPS-object ..."
    check = SysCreateObject('WPProgram','Minta 'Ver,'<WP_DESKTOP>',setup,"r")

    IF check = 0 THEN DO
        SAY ""
        SAY "* Sorry, object-creation failed again. Aborting ..."
        EXIT
        END
    ELSE DO
        SAY ""
        SAY "* Old Minta WPS-object replaced successfully!"
        END
    END
ELSE DO
    SAY ""
    SAY "* Minta WPS-object created successfully!"
    END

/*************************************************************************/

SAY ""
SAY "* See the online help for more information about Minta!"

/*************************************************************************/

EXIT
