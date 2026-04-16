# Microsoft Developer Studio Project File - Name="asrPublic" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=asrPublic - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "asrPublic.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "asrPublic.mak" CFG="asrPublic - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "asrPublic - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "asrPublic - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "asrPublic - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Release\lib"
# PROP Intermediate_Dir "..\..\o\asrPublic\Release"
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

!ELSEIF  "$(CFG)" == "asrPublic - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\debug\lib"
# PROP Intermediate_Dir "..\..\o\asrPublic\debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\asrInclude" /I "..\qyInclude2" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
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

# Name "asrPublic - Win32 Release"
# Name "asrPublic - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\commonfunc.cpp
# End Source File
# Begin Source File

SOURCE=.\commonFunc1.cpp
# End Source File
# Begin Source File

SOURCE=.\commonFunc2.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\asrInclude\asrCommon.h
# End Source File
# Begin Source File

SOURCE=..\asrInclude\asrObjs.h
# End Source File
# Begin Source File

SOURCE=..\asrInclude\asrPrecomp.h
# End Source File
# Begin Source File

SOURCE=..\asrInclude\asrTemp.h
# End Source File
# Begin Source File

SOURCE=..\asrInclude\asrWObjs.h
# End Source File
# Begin Source File

SOURCE=..\asrInclude\commondefs.h
# End Source File
# Begin Source File

SOURCE=..\asrInclude\commonDefs1.h
# End Source File
# Begin Source File

SOURCE=..\asrInclude\commonfunc.h
# End Source File
# Begin Source File

SOURCE=..\asrInclude\commonFunc1.h
# End Source File
# Begin Source File

SOURCE=..\asrInclude\commonFunc3.h
# End Source File
# Begin Source File

SOURCE=..\asrInclude\commonFunc4.h
# End Source File
# Begin Source File

SOURCE=..\asrInclude\commonSock.h
# End Source File
# Begin Source File

SOURCE=..\asrInclude\commonSql.h
# End Source File
# Begin Source File

SOURCE=..\asrInclude\genericqueue.h
# End Source File
# Begin Source File

SOURCE=..\asrInclude\getopt_long.h
# End Source File
# Begin Source File

SOURCE=..\asrInclude\mtSockFunc.h
# End Source File
# End Group
# Begin Group "qyInclude2"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\qyInclude2\qyPrecomp.h
# End Source File
# End Group
# End Target
# End Project
