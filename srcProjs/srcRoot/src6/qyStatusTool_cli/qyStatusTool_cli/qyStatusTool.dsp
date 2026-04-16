# Microsoft Developer Studio Project File - Name="qyStatusTool" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=qyStatusTool - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "qyStatusTool.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "qyStatusTool.mak" CFG="qyStatusTool - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "qyStatusTool - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "qyStatusTool - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "qyStatusTool - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\Release\bin"
# PROP Intermediate_Dir "..\..\..\..\o\qyStatusTool\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\tmpInclude" /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\..\qyCusResSrc\qyCusRes\include" /I "..\..\qyCommProc\include" /I "..\..\qyCommProc_mis\include" /I "..\..\..\qyOpen\qyCommProc_open\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D WINVER=0x0500 /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 qyPublicStatic.lib qyEncLibStatic.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /libpath:"..\..\..\..\Release\lib"

!ELSEIF  "$(CFG)" == "qyStatusTool - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\Debug\bin"
# PROP Intermediate_Dir "..\..\..\..\o\qyStatusTool\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\tmpInclude" /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\..\qyCusResSrc\qyCusRes\include" /I "..\..\qyCommProc\include" /I "..\..\qyCommProc_mis\include" /I "..\..\..\qyOpen\qyCommProc_open\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D WINVER=0x0500 /Fr /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 qyPublicStatic.lib qyEncLibStatic.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\..\..\..\Debug\lib"

!ENDIF 

# Begin Target

# Name "qyStatusTool - Win32 Release"
# Name "qyStatusTool - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "qyMcPublic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\qymcPublic\DlgIp.cpp
# End Source File
# Begin Source File

SOURCE=..\qymcPublic\qmCommonFunc.cpp
# End Source File
# Begin Source File

SOURCE=..\qymcPublic\QyPs.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\DlgFilters.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQyCommStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\PpQnmChkingStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\PpQnmChkingStatus.h
# End Source File
# Begin Source File

SOURCE=.\PpQwmCommStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\PpQwmCommStatus.h
# End Source File
# Begin Source File

SOURCE=.\PpScanningIpStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\qyStatusTool.cpp
# End Source File
# Begin Source File

SOURCE=.\qyStatusTool.rc
# End Source File
# Begin Source File

SOURCE=.\qyStatusToolProc.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "qmInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\DlgIp.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\DlgFilters.h
# End Source File
# Begin Source File

SOURCE=.\DlgQyCommStatus.h
# End Source File
# Begin Source File

SOURCE=.\PpScanningIpStatus.h
# End Source File
# Begin Source File

SOURCE=.\qyStatusTool.h
# End Source File
# Begin Source File

SOURCE=.\qyStatusToolCommon.h
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

SOURCE=.\res\qyStatusTool.ico
# End Source File
# Begin Source File

SOURCE=.\res\qyStatusTool.rc2
# End Source File
# End Group
# Begin Group "qyCommProc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\qyCommProc\genericqueue.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmOsAuditCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qwmDynFunc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qwmNetworkStatusCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyDmItemCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyLangCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyShowInfoCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qySyncCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyTCharCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\traceLogA.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "qyCustom"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\qyCustom\qyCusResHelp.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCustom\qyCustom.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
