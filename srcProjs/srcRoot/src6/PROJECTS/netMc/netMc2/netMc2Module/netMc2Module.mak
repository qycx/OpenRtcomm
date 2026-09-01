# Microsoft Developer Studio Generated NMAKE File, Based on netMc2Module.dsp
!IF "$(CFG)" == ""
CFG=netMc2Module - Win32 Debug
!MESSAGE No configuration specified. Defaulting to netMc2Module - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "netMc2Module - Win32 Release" && "$(CFG)" != "netMc2Module - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "netMc2Module.mak" CFG="netMc2Module - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "netMc2Module - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "netMc2Module - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "netMc2Module - Win32 Release"

OUTDIR=.\..\..\..\..\..\Release\bin
INTDIR=.\..\..\..\..\..\o\netMc2Module\Release
# Begin Custom Macros
OutDir=.\..\..\..\..\..\Release\bin
# End Custom Macros

ALL : "$(OUTDIR)\netMc2Module.dll"


CLEAN :
	-@erase "$(INTDIR)\netMc2Module.obj"
	-@erase "$(INTDIR)\netMc2Module.pch"
	-@erase "$(INTDIR)\netMc2Module.res"
	-@erase "$(INTDIR)\netMc2ModuleProc.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\netMc2Module.dll"
	-@erase "$(OUTDIR)\netMc2Module.exp"
	-@erase "$(OUTDIR)\netMc2Module.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\..\..\asrInclude" /I "..\..\..\..\qyInclude" /I "..\..\..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\..\..\qyCommProc\include" /I "..\..\..\..\qyEncLib\include" /I "..\..\..\..\qyCustom\include" /I "..\..\..\..\qyPublic2\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\netMc2Module.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\netMc2Module.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\netMc2Module.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=qyPublic.lib qyEncLib.lib ws2_32.lib qyLicense.lib Spromeps.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\netMc2Module.pdb" /machine:I386 /def:".\netMc2Module.def" /out:"$(OUTDIR)\netMc2Module.dll" /implib:"$(OUTDIR)\netMc2Module.lib" /libpath:"..\..\..\..\..\release\lib" 
DEF_FILE= \
	".\netMc2Module.def"
LINK32_OBJS= \
	"$(INTDIR)\netMc2Module.obj" \
	"$(INTDIR)\netMc2ModuleProc.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\netMc2Module.res"

"$(OUTDIR)\netMc2Module.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "netMc2Module - Win32 Debug"

OUTDIR=.\..\..\..\..\..\Debug\bin
INTDIR=.\..\..\..\..\..\o\netMc2Module\Debug
# Begin Custom Macros
OutDir=.\..\..\..\..\..\Debug\bin
# End Custom Macros

ALL : "$(OUTDIR)\netMc2Module.dll" "$(OUTDIR)\netMc2Module.bsc"


CLEAN :
	-@erase "$(INTDIR)\netMc2Module.obj"
	-@erase "$(INTDIR)\netMc2Module.pch"
	-@erase "$(INTDIR)\netMc2Module.res"
	-@erase "$(INTDIR)\netMc2Module.sbr"
	-@erase "$(INTDIR)\netMc2ModuleProc.obj"
	-@erase "$(INTDIR)\netMc2ModuleProc.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\netMc2Module.bsc"
	-@erase "$(OUTDIR)\netMc2Module.dll"
	-@erase "$(OUTDIR)\netMc2Module.exp"
	-@erase "$(OUTDIR)\netMc2Module.ilk"
	-@erase "$(OUTDIR)\netMc2Module.lib"
	-@erase "$(OUTDIR)\netMc2Module.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\..\asrInclude" /I "..\..\..\..\qyInclude" /I "..\..\..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\..\..\qyCommProc\include" /I "..\..\..\..\qyEncLib\include" /I "..\..\..\..\qyCustom\include" /I "..\..\..\..\qyPublic2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fr"$(INTDIR)\\" /Fp"$(INTDIR)\netMc2Module.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\netMc2Module.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\netMc2Module.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\netMc2Module.sbr" \
	"$(INTDIR)\netMc2ModuleProc.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\netMc2Module.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=qyPublic.lib qyEncLib.lib ws2_32.lib qyLicense.lib Spromeps.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\netMc2Module.pdb" /debug /machine:I386 /def:".\netMc2Module.def" /out:"$(OUTDIR)\netMc2Module.dll" /implib:"$(OUTDIR)\netMc2Module.lib" /pdbtype:sept /libpath:"..\..\..\..\..\Debug\lib" 
DEF_FILE= \
	".\netMc2Module.def"
LINK32_OBJS= \
	"$(INTDIR)\netMc2Module.obj" \
	"$(INTDIR)\netMc2ModuleProc.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\netMc2Module.res"

"$(OUTDIR)\netMc2Module.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("netMc2Module.dep")
!INCLUDE "netMc2Module.dep"
!ELSE 
!MESSAGE Warning: cannot find "netMc2Module.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "netMc2Module - Win32 Release" || "$(CFG)" == "netMc2Module - Win32 Debug"
SOURCE=.\netMc2Module.cpp

!IF  "$(CFG)" == "netMc2Module - Win32 Release"


"$(INTDIR)\netMc2Module.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\netMc2Module.pch"


!ELSEIF  "$(CFG)" == "netMc2Module - Win32 Debug"


"$(INTDIR)\netMc2Module.obj"	"$(INTDIR)\netMc2Module.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\netMc2Module.pch"


!ENDIF 

SOURCE=.\netMc2Module.rc

"$(INTDIR)\netMc2Module.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\netMc2ModuleProc.cpp

!IF  "$(CFG)" == "netMc2Module - Win32 Release"


"$(INTDIR)\netMc2ModuleProc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\netMc2Module.pch"


!ELSEIF  "$(CFG)" == "netMc2Module - Win32 Debug"


"$(INTDIR)\netMc2ModuleProc.obj"	"$(INTDIR)\netMc2ModuleProc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\netMc2Module.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "netMc2Module - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\..\..\asrInclude" /I "..\..\..\..\qyInclude" /I "..\..\..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\..\..\qyCommProc\include" /I "..\..\..\..\qyEncLib\include" /I "..\..\..\..\qyCustom\include" /I "..\..\..\..\qyPublic2\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\netMc2Module.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\netMc2Module.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "netMc2Module - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\..\asrInclude" /I "..\..\..\..\qyInclude" /I "..\..\..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\..\..\qyCommProc\include" /I "..\..\..\..\qyEncLib\include" /I "..\..\..\..\qyCustom\include" /I "..\..\..\..\qyPublic2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fr"$(INTDIR)\\" /Fp"$(INTDIR)\netMc2Module.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\netMc2Module.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

