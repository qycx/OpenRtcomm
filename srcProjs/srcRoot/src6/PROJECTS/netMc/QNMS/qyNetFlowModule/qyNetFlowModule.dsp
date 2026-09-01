# Microsoft Developer Studio Project File - Name="qyNetFlowModule" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=qyNetFlowModule - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "qyNetFlowModule.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "qyNetFlowModule.mak" CFG="qyNetFlowModule - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "qyNetFlowModule - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "qyNetFlowModule - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "qyNetFlowModule - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\..\Release\bin"
# PROP Intermediate_Dir "..\..\..\..\..\o\qyNetFlowModule\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QYNETFLOWMODULE_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\..\asrInclude" /I "..\..\..\..\qyInclude" /I "..\..\..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\..\..\qyCommProc\include" /I "..\..\..\..\qyEncLib\include" /I "..\..\..\..\qyCustom\include" /I "..\..\..\..\qyPublic2\include" /I "..\..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QYNETFLOWMODULE_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /D WINVER=0x0400 /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 qyPublic.lib qyEncLib.lib ws2_32.lib user32.lib qyLicense.lib Spromeps.lib /nologo /dll /machine:I386 /libpath:"..\..\..\..\..\Release\lib"

!ELSEIF  "$(CFG)" == "qyNetFlowModule - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\..\Debug\bin"
# PROP Intermediate_Dir "..\..\..\..\..\o\qyNetFlowModule\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QYNETFLOWMODULE_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\..\qyMc\include" /I "..\..\..\..\qyMc\main\include" /I "..\..\..\..\qyMc\main" /I "..\..\..\..\asrInclude" /I "..\..\..\..\qyInclude" /I "..\..\..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\..\..\qyCommProc\include" /I "..\..\..\..\qyEncLib\include" /I "..\..\..\..\qyCustom\include" /I "..\..\..\..\qyPublic2\include" /I "..\..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QYNETFLOWMODULE_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /D WINVER=0x0400 /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 qyPublic.lib qyEncLib.lib ws2_32.lib user32.lib qyLicense.lib Spromeps.lib /nologo /dll /debug /machine:I386 /pdbtype:sept /libpath:"..\..\..\..\..\Debug\lib"

!ENDIF 

# Begin Target

# Name "qyNetFlowModule - Win32 Release"
# Name "qyNetFlowModule - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\qyNetFlowModuleProc.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "qyCommProc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\qyCommProc\qnmCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\qyCommProc\qnmOsAuditCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\qyCommProc\qwmDynFunc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\qyCommProc\qwmNetworkStatusCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\qyCommProc\qyDmItemCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\qyCommProc\qyShowInfoCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\qyCommProc\qyTCharCommProc.cpp
# End Source File
# End Group
# End Target
# End Project
