/***
 finddir.h
 ***/

#ifndef _FINDDIR_H_
#define _FINDDIR_H_

#include "minta.h"
#include <sys/types.h>
#include <sys/stat.h>

// ** defines ************************************************************* /*FOLD00*/

#define MAX_DEPTH_DIRS  32

#define DRIVE_FIRST     0
#define DRIVE_LAST      25

#define UM_DIROUT            WM_USER+100
#define UM_DIRIN             WM_USER+101

typedef class FindDir FINDDIR;
typedef FINDDIR *PFINDDIR;

// ** classdef ************************************************************ /*FOLD00*/

class FindDir
{
public:
    BOOL    Dialog (HWND hwnd, PSZ pszDir, PSZ pszBuffer, ULONG ulSize);

protected:
    BOOL    DirIn (VOID);
    BOOL    DirOut (VOID);
    BOOL    ChangeDirectory (PSZ psz);
    BOOL    ChangeDrive (USHORT us);
    USHORT  ResetDrives (VOID);

    PSZ     QuerySelected (VOID);
    USHORT  QuerySelectedDrive (VOID);

    LONG    AddItem (PSZ psz);
    VOID    ClearItemList (VOID);
    VOID    SelectFirstItem (VOID);
    VOID    DisableListRefresh (VOID);
    VOID    EnableListRefresh (VOID);

    VOID    SetBuffer (PSZ psz, ULONG ul);

    HWND    QueryHWND (VOID);

    static MRESULT EXPENTRY
        DialogProcedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

private:
    HWND     hwnd;
    ULONG    ulPositions[MAX_DEPTH_DIRS][2], cPositions;
    CHAR     pszDir[_MAX_PATH];

    ULONG    ulSize;
    PSZ      pszBuffer;
    USHORT   usOldDrive;
    BOOL     fSkipSelect;

    static CHAR   pszDummy[_MAX_PATH];
};

// ** inline funcs ******************************************************** /*FOLD00*/

inline HWND FINDDIR :: QueryHWND (VOID)  { return (hwnd); }

inline VOID FINDDIR :: ClearItemList (VOID)
{
    WinSendMsg (WinWindowFromID (QueryHWND (), WID_LB_DIRECTORIES),
                LM_DELETEALL, NULL, NULL);
}

inline VOID FINDDIR :: DisableListRefresh (VOID)
{
    WinEnableWindowUpdate (WinWindowFromID (QueryHWND (), WID_LB_DIRECTORIES),
                           FALSE);
}

inline VOID FINDDIR :: EnableListRefresh (VOID)
{
    WinShowWindow (WinWindowFromID (QueryHWND (), WID_LB_DIRECTORIES),
                   TRUE);
}

inline VOID FINDDIR :: SetBuffer (PSZ psz, ULONG ul)
{
    pszBuffer = psz;
    ulSize = ul;
}

// ************************************************************************
#endif
