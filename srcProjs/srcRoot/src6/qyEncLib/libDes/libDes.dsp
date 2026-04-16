# Microsoft Developer Studio Project File - Name="libDes" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libDes - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libDes.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libDes.mak" CFG="libDes - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libDes - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libDes - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libDes - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\Release\lib"
# PROP Intermediate_Dir "..\..\..\..\o\libDes\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "libDes - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\Debug\lib"
# PROP Intermediate_Dir "..\..\..\..\o\libDes\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "MSDOS" /YX /FD /GZ /c
# SUBTRACT CPP /Fr
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

# Name "libDes - Win32 Release"
# Name "libDes - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\cbc3_enc.c
# End Source File
# Begin Source File

SOURCE=.\cbc_cksm.c
# End Source File
# Begin Source File

SOURCE=.\cbc_enc.c
# End Source File
# Begin Source File

SOURCE=.\cfb64ede.c
# End Source File
# Begin Source File

SOURCE=.\cfb64enc.c
# End Source File
# Begin Source File

SOURCE=.\cfb_enc.c
# End Source File
# Begin Source File

SOURCE=.\des_enc.c
# End Source File
# Begin Source File

SOURCE=.\ecb3_enc.c
# End Source File
# Begin Source File

SOURCE=.\ecb_enc.c
# End Source File
# Begin Source File

SOURCE=.\ede_enc.c
# End Source File
# Begin Source File

SOURCE=.\enc_read.c
# End Source File
# Begin Source File

SOURCE=.\enc_writ.c
# End Source File
# Begin Source File

SOURCE=.\fcrypt.c
# End Source File
# Begin Source File

SOURCE=.\ncbc_enc.c
# End Source File
# Begin Source File

SOURCE=.\ofb64ede.c
# End Source File
# Begin Source File

SOURCE=.\ofb64enc.c
# End Source File
# Begin Source File

SOURCE=.\ofb_enc.c
# End Source File
# Begin Source File

SOURCE=.\pcbc_enc.c
# End Source File
# Begin Source File

SOURCE=.\qud_cksm.c
# End Source File
# Begin Source File

SOURCE=.\rand_key.c
# End Source File
# Begin Source File

SOURCE=.\read_pwd.c
# End Source File
# Begin Source File

SOURCE=.\rpc_enc.c
# End Source File
# Begin Source File

SOURCE=.\set_key.c
# End Source File
# Begin Source File

SOURCE=.\str2key.c
# End Source File
# Begin Source File

SOURCE=.\supp.c
# End Source File
# Begin Source File

SOURCE=.\xcbc_enc.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\des.h
# End Source File
# Begin Source File

SOURCE=.\des_locl.h
# End Source File
# Begin Source File

SOURCE=.\des_ver.h
# End Source File
# Begin Source File

SOURCE=.\podd.h
# End Source File
# Begin Source File

SOURCE=.\rpc_des.h
# End Source File
# Begin Source File

SOURCE=.\sk.h
# End Source File
# Begin Source File

SOURCE=.\spr.h
# End Source File
# End Group
# End Target
# End Project
