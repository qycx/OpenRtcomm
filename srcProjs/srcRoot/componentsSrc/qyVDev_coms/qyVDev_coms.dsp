# Microsoft Developer Studio Project File - Name="qyVDev_coms" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=qyVDev_coms - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "qyVDev_coms.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "qyVDev_coms.mak" CFG="qyVDev_coms - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "qyVDev_coms - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "qyVDev_coms - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "qyVDev_coms - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\Release\cusModule"
# PROP Intermediate_Dir "..\..\..\o\qyVDev_coms\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\src6\asrInclude" /I "..\..\src6\qyInclude" /I "..\..\src6\qyPublic\include" /I "..\..\src6\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\src6\qyCustom\include" /I "..\..\src6\tmpInclude" /I "..\..\qyCusResSrc\qyCusRes\include" /I "..\..\src6\qyCommProc\include" /I "..\..\src6\qyCommProc_mis\include" /I "..\..\qyOpen\qyCommProc_open\include" /I "sms" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /D "UNICODE" /D WINVER=0x0500 /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 netapi32.lib qyPublic.lib qyEncLib.lib libDes.lib ws2_32.lib /nologo /subsystem:windows /dll /machine:I386 /libpath:"..\..\..\Release\lib"

!ELSEIF  "$(CFG)" == "qyVDev_coms - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\Debug\cusModule"
# PROP Intermediate_Dir "..\..\..\o\qyVDev_coms\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\src6\asrInclude" /I "..\..\src6\qyInclude" /I "..\..\src6\qyPublic\include" /I "..\..\src6\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\src6\qyCustom\include" /I "..\..\src6\tmpInclude" /I "..\..\qyCusResSrc\qyCusRes\include" /I "..\..\src6\qyCommProc\include" /I "..\..\src6\qyCommProc_mis\include" /I "..\..\qyOpen\qyCommProc_open\include" /I "sms" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /D "UNICODE" /D WINVER=0x0500 /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 netapi32.lib qyPublic.lib qyEncLib.lib libDes.lib ws2_32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept /libpath:"..\..\..\Debug\lib"

!ENDIF 

# Begin Target

# Name "qyVDev_coms - Win32 Release"
# Name "qyVDev_coms - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\dlgQyTestProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qyComPort.cpp
# End Source File
# Begin Source File

SOURCE=.\qyVDev_coms.cpp
# End Source File
# Begin Source File

SOURCE=.\qyVDev_coms.def
# End Source File
# Begin Source File

SOURCE=.\qyVDev_coms.rc
# End Source File
# Begin Source File

SOURCE=.\qyVDevProc.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\qyComPort.h
# End Source File
# Begin Source File

SOURCE=.\qyVDev_coms.h
# End Source File
# Begin Source File

SOURCE=.\qyVDevProc.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\qyVDev_coms.rc2
# End Source File
# End Group
# Begin Group "include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\qyVDev.h
# End Source File
# End Group
# Begin Group "qyCommProc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src6\qyCommProc\genericqueue.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\src6\qyCommProc\qnmCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\src6\qyCommProc\qyCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\src6\qyCommProc\qyDmItemCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\src6\qyCommProc\qyLangCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\src6\qyCommProc\qyShowInfoCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\src6\qyCommProc\qySyncCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\src6\qyCommProc\qyTCharCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\src6\qyCommProc\traceLogA.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "qyCustom"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src6\qyCustom\qyCusResHelp.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\src6\qyCustom\qyCustom.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "qyCommProc_open"

# PROP Default_Filter ""
# Begin Group "qyCommProc_open_include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\qyOpen\qyCommProc_open\include\qyCommProc_open.h
# End Source File
# Begin Source File

SOURCE=..\..\qyOpen\qyCommProc_open\include\qyCusGui.h
# End Source File
# End Group
# End Group
# Begin Group "qyCommProc_mis"

# PROP Default_Filter ""
# Begin Group "qyCommProc_is_include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src6\qyCommProc_mis\include\qyWmComm_is.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\src6\qyCommProc_mis\qyWmComm_is.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "sms"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sms\Comm.cpp
# End Source File
# Begin Source File

SOURCE=.\sms\Comm.h
# End Source File
# Begin Source File

SOURCE=.\sms\Sms.cpp
# End Source File
# Begin Source File

SOURCE=.\sms\Sms.h
# End Source File
# Begin Source File

SOURCE=.\sms\SmsTraffic.cpp
# End Source File
# Begin Source File

SOURCE=.\sms\SmsTraffic.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
