# Microsoft Developer Studio Project File - Name="qyEncLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=qyEncLib - Win32 Debug Static No Mfc
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "qyEncLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "qyEncLib.mak" CFG="qyEncLib - Win32 Debug Static No Mfc"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "qyEncLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "qyEncLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "qyEncLib - Win32 Debug Static" (based on "Win32 (x86) Static Library")
!MESSAGE "qyEncLib - Win32 Release Static" (based on "Win32 (x86) Static Library")
!MESSAGE "qyEncLib - Win32 Debug Static No Mfc" (based on "Win32 (x86) Static Library")
!MESSAGE "qyEncLib - Win32 Release Static No Mfc" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "qyEncLib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\Release\lib"
# PROP Intermediate_Dir "..\..\..\o\qyEncLib\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "include" /I "libDes" /I "..\qyInclude" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "qyEncLib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\Debug\lib"
# PROP Intermediate_Dir "..\..\..\o\qyEncLib\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "include" /I "libDes" /I "..\qyInclude" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_AFXDLL" /YX /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "qyEncLib - Win32 Debug Static"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "qyEncLib___Win32_Debug_Static"
# PROP BASE Intermediate_Dir "qyEncLib___Win32_Debug_Static"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\Debug\lib"
# PROP Intermediate_Dir "..\..\..\o\qyEncLib\DebugStatic"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "include" /I "libDes" /I "..\qyInclude" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_AFXDLL" /FR /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "include" /I "libDes" /I "..\qyInclude" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\Debug\lib\qyEncLibStatic.lib"

!ELSEIF  "$(CFG)" == "qyEncLib - Win32 Release Static"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "qyEncLib___Win32_Release_Static"
# PROP BASE Intermediate_Dir "qyEncLib___Win32_Release_Static"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\Release\lib"
# PROP Intermediate_Dir "..\..\..\o\qyEncLib\ReleaseStatic"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "include" /I "libDes" /I "..\qyInclude" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "include" /I "libDes" /I "..\qyInclude" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\Release\lib\qyEncLibStatic.lib"

!ELSEIF  "$(CFG)" == "qyEncLib - Win32 Debug Static No Mfc"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "qyEncLib___Win32_Debug_Static_No_Mfc"
# PROP BASE Intermediate_Dir "qyEncLib___Win32_Debug_Static_No_Mfc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\Debug\lib"
# PROP Intermediate_Dir "..\..\..\o\qyEncLib\DebugStaticNoMfc"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "include" /I "libDes" /I "..\qyInclude" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "include" /I "libDes" /I "..\qyInclude" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\Debug\lib\qyEncLibStatic.lib"
# ADD LIB32 /nologo /out:"..\..\..\Debug\lib\qyEncLibStaticNoMfc.lib"

!ELSEIF  "$(CFG)" == "qyEncLib - Win32 Release Static No Mfc"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "qyEncLib___Win32_Release_Static_No_Mfc"
# PROP BASE Intermediate_Dir "qyEncLib___Win32_Release_Static_No_Mfc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\Release\lib"
# PROP Intermediate_Dir "..\..\..\o\qyEncLib\ReleaseStaticNoMfc"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "include" /I "libDes" /I "..\qyInclude" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "include" /I "libDes" /I "..\qyInclude" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\Release\lib\qyEncLibStatic.lib"
# ADD LIB32 /nologo /out:"..\..\..\Release\lib\qyEncLibStaticNoMfc.lib"

!ENDIF 

# Begin Target

# Name "qyEncLib - Win32 Release"
# Name "qyEncLib - Win32 Debug"
# Name "qyEncLib - Win32 Debug Static"
# Name "qyEncLib - Win32 Release Static"
# Name "qyEncLib - Win32 Debug Static No Mfc"
# Name "qyEncLib - Win32 Release Static No Mfc"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\D3Des.c
# End Source File
# Begin Source File

SOURCE=.\licenseEncFunc.cpp
# End Source File
# Begin Source File

SOURCE=.\qnmEncFunc.cpp
# End Source File
# Begin Source File

SOURCE=.\qyEncFunc.cpp
# End Source File
# Begin Source File

SOURCE=.\qyRand.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\include\d3des.h
# End Source File
# End Group
# Begin Group "qyInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\qyInclude\qyEncCommon.h
# End Source File
# End Group
# End Target
# End Project
