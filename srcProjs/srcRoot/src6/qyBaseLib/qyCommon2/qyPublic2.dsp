# Microsoft Developer Studio Project File - Name="qyPublic2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=qyPublic2 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "qyPublic2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "qyPublic2.mak" CFG="qyPublic2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "qyPublic2 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "qyPublic2 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "qyPublic2 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Release\lib"
# PROP Intermediate_Dir "..\..\o\qyPublic2\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "qyPublic2 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\debug\lib"
# PROP Intermediate_Dir "..\..\o\qyPublic2\debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\asrInclude" /I "..\qyInclude2" /I "..\asrComm\include" /I "..\asrLog\Include" /I "..\qyPublic\qyComm\include" /I "..\qyPublic\qyLog\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "qyPublic2 - Win32 Release"
# Name "qyPublic2 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\qyChk.cpp
# End Source File
# Begin Source File

SOURCE=.\qyChkFunc.cpp
# End Source File
# Begin Source File

SOURCE=.\qyChkLog.cpp
# End Source File
# Begin Source File

SOURCE=.\qyCommonFunc5.cpp
# End Source File
# Begin Source File

SOURCE=.\qyCommonFunc6.cpp
# End Source File
# Begin Source File

SOURCE=.\qyErrFunc.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\qyInclude2\qyCfg.h
# End Source File
# Begin Source File

SOURCE=..\qyInclude2\qyChk.h
# End Source File
# Begin Source File

SOURCE=..\qyInclude2\qyChkCommon.h
# End Source File
# Begin Source File

SOURCE=..\qyInclude2\qyCommon.h
# End Source File
# Begin Source File

SOURCE=..\qyInclude2\qyCommonDefs5.h
# End Source File
# Begin Source File

SOURCE=..\qyInclude2\qyCommonFunc5.h
# End Source File
# Begin Source File

SOURCE=..\qyInclude2\qyCommonFunc6.h
# End Source File
# Begin Source File

SOURCE=..\qyInclude2\qyErrFunc.h
# End Source File
# Begin Source File

SOURCE=..\qyInclude2\qyHotKeys.h
# End Source File
# Begin Source File

SOURCE=..\qyInclude2\qyPrecomp.h
# End Source File
# Begin Source File

SOURCE=..\qyInclude2\qyTypes.h
# End Source File
# End Group
# End Target
# End Project
