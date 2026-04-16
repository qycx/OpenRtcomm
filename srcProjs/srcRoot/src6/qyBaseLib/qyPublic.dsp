# Microsoft Developer Studio Project File - Name="qyPublic" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=qyPublic - Win32 Debug Static No Mfc
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "qyPublic.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "qyPublic.mak" CFG="qyPublic - Win32 Debug Static No Mfc"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "qyPublic - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "qyPublic - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "qyPublic - Win32 Debug Static" (based on "Win32 (x86) Static Library")
!MESSAGE "qyPublic - Win32 Release Static" (based on "Win32 (x86) Static Library")
!MESSAGE "qyPublic - Win32 Debug Static No Mfc" (based on "Win32 (x86) Static Library")
!MESSAGE "qyPublic - Win32 Release Static No Mfc" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "qyPublic - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\Release\lib"
# PROP Intermediate_Dir "..\..\..\o\qyPublic\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\asrInclude" /I "..\qyInclude" /I "..\asrComm\include" /I "..\asrLog\Include" /I "include" /I "contentFilter\include" /I "md5\include" /I "..\qyEncLib\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "_AFXDLL" /FR /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "qyPublic - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\debug\lib"
# PROP Intermediate_Dir "..\..\..\o\qyPublic\debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\asrInclude" /I "..\qyInclude" /I "include" /I "contentFilter\include" /I "md5\include" /I "..\qyEncLib\include" /I "..\qyPublic2\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_AFXDLL" /Fr /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "qyPublic - Win32 Debug Static"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "qyPublic___Win32_Debug_Static"
# PROP BASE Intermediate_Dir "qyPublic___Win32_Debug_Static"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\debug\lib"
# PROP Intermediate_Dir "..\..\..\o\qyPublic\debugStatic"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\asrInclude" /I "..\qyInclude" /I "..\asrComm\include" /I "..\asrLog\Include" /I "include" /I "contentFilter\include" /I "md5\include" /I "..\qyEncLib\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_AFXDLL" /FR /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\asrInclude" /I "..\qyInclude" /I "..\asrComm\include" /I "..\asrLog\Include" /I "include" /I "contentFilter\include" /I "md5\include" /I "..\qyEncLib\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\debug\lib\qyPublicStatic.lib"

!ELSEIF  "$(CFG)" == "qyPublic - Win32 Release Static"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "qyPublic___Win32_Release_Static"
# PROP BASE Intermediate_Dir "qyPublic___Win32_Release_Static"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\Release\lib"
# PROP Intermediate_Dir "..\..\..\o\qyPublic\ReleaseStatic"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\asrInclude" /I "..\qyInclude" /I "..\asrComm\include" /I "..\asrLog\Include" /I "include" /I "contentFilter\include" /I "md5\include" /I "..\qyEncLib\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\asrInclude" /I "..\qyInclude" /I "..\asrComm\include" /I "..\asrLog\Include" /I "include" /I "contentFilter\include" /I "md5\include" /I "..\qyEncLib\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\Release\lib\qyPublicStatic.lib"

!ELSEIF  "$(CFG)" == "qyPublic - Win32 Debug Static No Mfc"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "qyPublic___Win32_Debug_Static_No_Mfc"
# PROP BASE Intermediate_Dir "qyPublic___Win32_Debug_Static_No_Mfc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\debug\lib"
# PROP Intermediate_Dir "..\..\..\o\qyPublic\debugStaticNoMfc"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\asrInclude" /I "..\qyInclude" /I "..\asrComm\include" /I "..\asrLog\Include" /I "include" /I "contentFilter\include" /I "md5\include" /I "..\qyEncLib\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\asrInclude" /I "..\qyInclude" /I "..\asrComm\include" /I "..\asrLog\Include" /I "include" /I "contentFilter\include" /I "md5\include" /I "..\qyEncLib\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\debug\lib\qyPublicStatic.lib"
# ADD LIB32 /nologo /out:"..\..\..\debug\lib\qyPublicStaticNoMfc.lib"

!ELSEIF  "$(CFG)" == "qyPublic - Win32 Release Static No Mfc"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "qyPublic___Win32_Release_Static_No_Mfc"
# PROP BASE Intermediate_Dir "qyPublic___Win32_Release_Static_No_Mfc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\Release\lib"
# PROP Intermediate_Dir "..\..\..\o\qyPublic\ReleaseStaticNoMfc"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "..\asrInclude" /I "..\qyInclude" /I "..\asrComm\include" /I "..\asrLog\Include" /I "include" /I "contentFilter\include" /I "md5\include" /I "..\qyEncLib\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\asrInclude" /I "..\qyInclude" /I "..\asrComm\include" /I "..\asrLog\Include" /I "include" /I "contentFilter\include" /I "md5\include" /I "..\qyEncLib\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\Release\lib\qyPublicStatic.lib"
# ADD LIB32 /nologo /out:"..\..\..\Release\lib\qyPublicStaticNoMfc.lib"

!ENDIF 

# Begin Target

# Name "qyPublic - Win32 Release"
# Name "qyPublic - Win32 Debug"
# Name "qyPublic - Win32 Debug Static"
# Name "qyPublic - Win32 Release Static"
# Name "qyPublic - Win32 Debug Static No Mfc"
# Name "qyPublic - Win32 Release Static No Mfc"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "qyLog"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\qyLog\qyLogFunc.cpp
# End Source File
# End Group
# Begin Group "qyDbLib"

# PROP Default_Filter ""
# End Group
# Begin Group "qyCommon"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\qyCommon\qyCommonFunc3.cpp
# End Source File
# Begin Source File

SOURCE=.\qyCommon\qyCommonFunc4.cpp
# End Source File
# Begin Source File

SOURCE=.\qyCommon\qyCommonFunc7.cpp
# End Source File
# Begin Source File

SOURCE=.\qyCommon\qyCommonFunc8.cpp
# End Source File
# Begin Source File

SOURCE=.\qyCommon\qyCommonFunc9.cpp
# End Source File
# Begin Source File

SOURCE=.\qyCommon\qyCommonObj.cpp
# End Source File
# Begin Source File

SOURCE=.\qyCommon\qyDebugFunc.cpp
# End Source File
# Begin Source File

SOURCE=.\qyCommon\qyModifyPeFunc.cpp
# End Source File
# End Group
# Begin Group "qyGuiLib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\qyGuiLib\qyGuiFunc.cpp
# End Source File
# End Group
# Begin Group "qyDaemonLib"

# PROP Default_Filter ""
# Begin Group "qyDaemonLibInclude"

# PROP Default_Filter ""
# End Group
# End Group
# Begin Group "qySock"

# PROP Default_Filter ""
# Begin Group "qySockInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\qySock\include\qyCommonSock.h
# End Source File
# Begin Source File

SOURCE=.\qySock\include\qySockPublic.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\qySock\qyCommonSock.cpp
# End Source File
# Begin Source File

SOURCE=.\qySock\qySockFunc.cpp
# End Source File
# End Group
# Begin Group "qyMfcLib"

# PROP Default_Filter ""
# End Group
# Begin Group "qyComm"

# PROP Default_Filter ""
# Begin Group "qyCommInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\qyComm\include\qyComm.h
# End Source File
# Begin Source File

SOURCE=.\qyComm\include\qyCommFunc.h
# End Source File
# Begin Source File

SOURCE=.\qyComm\include\qyWmComm.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\qyComm\qyCommFunc.cpp
# End Source File
# End Group
# Begin Group "contentFilter"

# PROP Default_Filter ""
# Begin Group "contentFilterInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\contentFilter\include\cfCommon.h
# End Source File
# Begin Source File

SOURCE=.\contentFilter\include\vardefine.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\contentFilter\cfCfgServ.cpp
# End Source File
# Begin Source File

SOURCE=.\contentFilter\cfCommon.cpp
# End Source File
# Begin Source File

SOURCE=.\contentFilter\cfKeyValue.cpp
# End Source File
# Begin Source File

SOURCE=.\contentFilter\contentfilter.cpp
# End Source File
# Begin Source File

SOURCE=.\contentFilter\EmailProcess.cpp
# End Source File
# Begin Source File

SOURCE=.\contentFilter\keyvalue.cpp
# End Source File
# Begin Source File

SOURCE=.\contentFilter\littlefunction.cpp
# End Source File
# Begin Source File

SOURCE=.\contentFilter\setupCfDict.cpp
# End Source File
# Begin Source File

SOURCE=.\contentFilter\zhFunc.cpp
# End Source File
# End Group
# Begin Group "md5"

# PROP Default_Filter ""
# Begin Group "md5Include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\md5\include\global.h
# End Source File
# Begin Source File

SOURCE=.\md5\include\md5.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\md5\asrMd5.c
# End Source File
# Begin Source File

SOURCE=.\md5\md5c.c
# End Source File
# Begin Source File

SOURCE=.\md5\mddriver.c
# End Source File
# Begin Source File

SOURCE=.\md5\qwmMd5.c
# End Source File
# End Group
# Begin Group "qyModuleLib"

# PROP Default_Filter ""
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "qyInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\qyInclude\qyCommon.h
# End Source File
# End Group
# End Group
# Begin Group "qyPublic2"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\qyPublic2\detectNetworkWithSnmp.cpp
# End Source File
# Begin Source File

SOURCE=..\qyPublic2\qnmCommonFunc.cpp
# End Source File
# Begin Source File

SOURCE=..\qyPublic2\qwmCommonFunc.cpp
# End Source File
# Begin Source File

SOURCE=..\qyPublic2\qyCommonFunc5.cpp
# End Source File
# Begin Source File

SOURCE=..\qyPublic2\qyErrFunc.cpp
# End Source File
# End Group
# Begin Group "asrPublic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\asrPublic\commonfunc.cpp
# End Source File
# Begin Source File

SOURCE=..\asrPublic\commonFunc1.cpp
# End Source File
# Begin Source File

SOURCE=..\asrPublic\commonFunc2.cpp
# End Source File
# Begin Source File

SOURCE=..\asrPublic\commonFunc3.cpp
# End Source File
# Begin Source File

SOURCE=..\asrPublic\commonSock.cpp
# End Source File
# Begin Source File

SOURCE=..\asrPublic\commonSql.cpp
# End Source File
# End Group
# End Target
# End Project
