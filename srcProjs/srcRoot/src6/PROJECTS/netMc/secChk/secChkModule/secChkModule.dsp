# Microsoft Developer Studio Project File - Name="secChkModule" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=secChkModule - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "secChkModule.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "secChkModule.mak" CFG="secChkModule - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "secChkModule - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "secChkModule - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "secChkModule - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\..\..\Release\bin"
# PROP Intermediate_Dir "..\..\..\..\..\..\o\secChkModule\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\..\asrInclude" /I "..\..\..\..\qyInclude" /I "..\..\..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\..\..\qyCommProc\include" /I "..\..\..\..\qyCommProc_mis\include" /I "..\..\..\..\qyEncLib\include" /I "..\..\..\..\qyCustom\include" /I "..\..\..\..\qyPublic2\include" /I "..\..\..\..\tmpInclude" /I "..\..\..\..\..\qyOpen\qyCommProc_open\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D "_USRDLL" /D WINVER=0x0500 /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 libDes.lib qyPublic.lib qyEncLib.lib qyLicense.lib Spromeps.lib SentinelKeys_md.lib /nologo /subsystem:windows /dll /machine:I386 /libpath:"..\..\..\..\..\..\release\lib"

!ELSEIF  "$(CFG)" == "secChkModule - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\..\..\Debug\bin"
# PROP Intermediate_Dir "..\..\..\..\..\..\o\secChkModule\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\..\asrInclude" /I "..\..\..\..\qyInclude" /I "..\..\..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\..\..\qyCommProc\include" /I "..\..\..\..\qyCommProc_mis\include" /I "..\..\..\..\qyEncLib\include" /I "..\..\..\..\qyCustom\include" /I "..\..\..\..\qyPublic2\include" /I "..\..\..\..\tmpInclude" /I "..\..\..\..\..\qyOpen\qyCommProc_open\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D "_USRDLL" /D WINVER=0x0500 /Fr /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 qyPublic.lib qyEncLib.lib qyLicense.lib Spromeps.lib libDes.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept /libpath:"..\..\..\..\..\..\Debug\lib"

!ENDIF 

# Begin Target

# Name "secChkModule - Win32 Release"
# Name "secChkModule - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\secChkModule.cpp
# End Source File
# Begin Source File

SOURCE=.\secChkModule.def
# End Source File
# Begin Source File

SOURCE=.\secChkModule.rc
# End Source File
# Begin Source File

SOURCE=.\secChkModuleProc.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\secChkModule.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\secChkModule.rc2
# End Source File
# End Group
# Begin Group "qyCommProc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\qyCommProc\genericqueue.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\..\qyCommProc\qnmCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\..\qyCommProc\qnmOsAuditCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\..\qyCommProc\qwmDynFunc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\..\qyCommProc\qwmNetworkStatusCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\..\qyCommProc\qyCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\..\qyCommProc\qyDmItemCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\..\qyCommProc\qyGenericDaemon.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\..\qyCommProc\qyModuleFunc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\..\qyCommProc\qyShowInfoCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\..\qyCommProc\qySqlFunc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\..\qyCommProc\qySyncCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\..\qyCommProc\qyTCharCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\..\qyCommProc\traceLogA.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
