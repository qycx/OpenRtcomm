# Microsoft Developer Studio Generated NMAKE File, Based on qyNmsModule.dsp
!IF "$(CFG)" == ""
CFG=qyNmsModule - Win32 Debug
!MESSAGE No configuration specified. Defaulting to qyNmsModule - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "qyNmsModule - Win32 Release" && "$(CFG)" != "qyNmsModule - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "qyNmsModule.mak" CFG="qyNmsModule - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "qyNmsModule - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "qyNmsModule - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "qyNmsModule - Win32 Release"

OUTDIR=.\..\..\..\..\..\Release\bin
INTDIR=.\..\..\..\..\..\o\qyNmsModule\Release
# Begin Custom Macros
OutDir=.\..\..\..\..\..\Release\bin
# End Custom Macros

ALL : "$(OUTDIR)\qyNmsModule.dll"


CLEAN :
	-@erase "$(INTDIR)\qnmCommProc.obj"
	-@erase "$(INTDIR)\qnmCommProc1.obj"
	-@erase "$(INTDIR)\qnmScan.obj"
	-@erase "$(INTDIR)\qnmsCommProc.obj"
	-@erase "$(INTDIR)\QnmsModuleDaemon.obj"
	-@erase "$(INTDIR)\qyCommProc.obj"
	-@erase "$(INTDIR)\qyNmsModule.obj"
	-@erase "$(INTDIR)\qyNmsProc.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\qyNmsModule.dll"
	-@erase "$(OUTDIR)\qyNmsModule.exp"
	-@erase "$(OUTDIR)\qyNmsModule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\..\..\asrInclude" /I "..\..\..\..\qyInclude" /I "..\..\..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\..\..\qyCommProc\include" /I "..\..\..\..\qyEncLib\include" /I "..\..\..\..\qyCustom\include" /I "..\..\..\..\qyPublic2\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QYNMSMODULE_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\qyNmsModule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qyNmsModule.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=qyPublic.lib qyEncLib.lib ws2_32.lib user32.lib qyLicense.lib Spromeps.lib libDes.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\qyNmsModule.pdb" /machine:I386 /out:"$(OUTDIR)\qyNmsModule.dll" /implib:"$(OUTDIR)\qyNmsModule.lib" /libpath:"..\..\..\..\..\Release\lib" 
LINK32_OBJS= \
	"$(INTDIR)\QnmsModuleDaemon.obj" \
	"$(INTDIR)\qyNmsModule.obj" \
	"$(INTDIR)\qyNmsProc.obj" \
	"$(INTDIR)\qnmCommProc.obj" \
	"$(INTDIR)\qnmCommProc1.obj" \
	"$(INTDIR)\qnmsCommProc.obj" \
	"$(INTDIR)\qyCommProc.obj" \
	"$(INTDIR)\qnmScan.obj"

"$(OUTDIR)\qyNmsModule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "qyNmsModule - Win32 Debug"

OUTDIR=.\..\..\..\..\..\Debug\bin
INTDIR=.\..\..\..\..\..\o\qyNmsModule\Debug
# Begin Custom Macros
OutDir=.\..\..\..\..\..\Debug\bin
# End Custom Macros

ALL : "$(OUTDIR)\qyNmsModule.dll" "$(OUTDIR)\qyNmsModule.bsc"


CLEAN :
	-@erase "$(INTDIR)\qnmCommProc.obj"
	-@erase "$(INTDIR)\qnmCommProc.sbr"
	-@erase "$(INTDIR)\qnmCommProc1.obj"
	-@erase "$(INTDIR)\qnmCommProc1.sbr"
	-@erase "$(INTDIR)\qnmScan.obj"
	-@erase "$(INTDIR)\qnmScan.sbr"
	-@erase "$(INTDIR)\qnmsCommProc.obj"
	-@erase "$(INTDIR)\qnmsCommProc.sbr"
	-@erase "$(INTDIR)\QnmsModuleDaemon.obj"
	-@erase "$(INTDIR)\QnmsModuleDaemon.sbr"
	-@erase "$(INTDIR)\qyCommProc.obj"
	-@erase "$(INTDIR)\qyCommProc.sbr"
	-@erase "$(INTDIR)\qyNmsModule.obj"
	-@erase "$(INTDIR)\qyNmsModule.sbr"
	-@erase "$(INTDIR)\qyNmsProc.obj"
	-@erase "$(INTDIR)\qyNmsProc.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\qyNmsModule.bsc"
	-@erase "$(OUTDIR)\qyNmsModule.dll"
	-@erase "$(OUTDIR)\qyNmsModule.exp"
	-@erase "$(OUTDIR)\qyNmsModule.ilk"
	-@erase "$(OUTDIR)\qyNmsModule.lib"
	-@erase "$(OUTDIR)\qyNmsModule.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\..\asrInclude" /I "..\..\..\..\qyInclude" /I "..\..\..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\..\..\qyCommProc\include" /I "..\..\..\..\qyEncLib\include" /I "..\..\..\..\qyCustom\include" /I "..\..\..\..\qyPublic2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QYNMSMODULE_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /Fr"$(INTDIR)\\" /Fp"$(INTDIR)\qyNmsModule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qyNmsModule.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\QnmsModuleDaemon.sbr" \
	"$(INTDIR)\qyNmsModule.sbr" \
	"$(INTDIR)\qyNmsProc.sbr" \
	"$(INTDIR)\qnmCommProc.sbr" \
	"$(INTDIR)\qnmCommProc1.sbr" \
	"$(INTDIR)\qnmsCommProc.sbr" \
	"$(INTDIR)\qyCommProc.sbr" \
	"$(INTDIR)\qnmScan.sbr"

"$(OUTDIR)\qyNmsModule.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=qyPublic.lib qyEncLib.lib ws2_32.lib user32.lib qyLicense.lib Spromeps.lib libDes.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\qyNmsModule.pdb" /debug /machine:I386 /out:"$(OUTDIR)\qyNmsModule.dll" /implib:"$(OUTDIR)\qyNmsModule.lib" /pdbtype:sept /libpath:"..\..\..\..\..\Debug\lib" 
LINK32_OBJS= \
	"$(INTDIR)\QnmsModuleDaemon.obj" \
	"$(INTDIR)\qyNmsModule.obj" \
	"$(INTDIR)\qyNmsProc.obj" \
	"$(INTDIR)\qnmCommProc.obj" \
	"$(INTDIR)\qnmCommProc1.obj" \
	"$(INTDIR)\qnmsCommProc.obj" \
	"$(INTDIR)\qyCommProc.obj" \
	"$(INTDIR)\qnmScan.obj"

"$(OUTDIR)\qyNmsModule.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("qyNmsModule.dep")
!INCLUDE "qyNmsModule.dep"
!ELSE 
!MESSAGE Warning: cannot find "qyNmsModule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "qyNmsModule - Win32 Release" || "$(CFG)" == "qyNmsModule - Win32 Debug"
SOURCE=.\QnmsModuleDaemon.cpp

!IF  "$(CFG)" == "qyNmsModule - Win32 Release"


"$(INTDIR)\QnmsModuleDaemon.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "qyNmsModule - Win32 Debug"


"$(INTDIR)\QnmsModuleDaemon.obj"	"$(INTDIR)\QnmsModuleDaemon.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\qyNmsModule.cpp

!IF  "$(CFG)" == "qyNmsModule - Win32 Release"


"$(INTDIR)\qyNmsModule.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "qyNmsModule - Win32 Debug"


"$(INTDIR)\qyNmsModule.obj"	"$(INTDIR)\qyNmsModule.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\qyNmsProc.cpp

!IF  "$(CFG)" == "qyNmsModule - Win32 Release"


"$(INTDIR)\qyNmsProc.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "qyNmsModule - Win32 Debug"


"$(INTDIR)\qyNmsProc.obj"	"$(INTDIR)\qyNmsProc.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=..\..\..\..\qyCommProc\qnmCommProc.cpp

!IF  "$(CFG)" == "qyNmsModule - Win32 Release"


"$(INTDIR)\qnmCommProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qyNmsModule - Win32 Debug"


"$(INTDIR)\qnmCommProc.obj"	"$(INTDIR)\qnmCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\qyCommProc\qnmCommProc1.cpp

!IF  "$(CFG)" == "qyNmsModule - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\..\..\asrInclude" /I "..\..\..\..\qyInclude" /I "..\..\..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\..\..\qyCommProc\include" /I "..\..\..\..\qyEncLib\include" /I "..\..\..\..\qyCustom\include" /I "..\..\..\..\qyPublic2\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QYNMSMODULE_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCommProc1.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyNmsModule - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\..\asrInclude" /I "..\..\..\..\qyInclude" /I "..\..\..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\..\..\qyCommProc\include" /I "..\..\..\..\qyEncLib\include" /I "..\..\..\..\qyCustom\include" /I "..\..\..\..\qyPublic2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QYNMSMODULE_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCommProc1.obj"	"$(INTDIR)\qnmCommProc1.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\..\qyCommProc\qnmsCommProc.cpp

!IF  "$(CFG)" == "qyNmsModule - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\..\..\asrInclude" /I "..\..\..\..\qyInclude" /I "..\..\..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\..\..\qyCommProc\include" /I "..\..\..\..\qyEncLib\include" /I "..\..\..\..\qyCustom\include" /I "..\..\..\..\qyPublic2\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QYNMSMODULE_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\qyNmsModule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmsCommProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyNmsModule - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\..\asrInclude" /I "..\..\..\..\qyInclude" /I "..\..\..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\..\..\qyCommProc\include" /I "..\..\..\..\qyEncLib\include" /I "..\..\..\..\qyCustom\include" /I "..\..\..\..\qyPublic2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QYNMSMODULE_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmsCommProc.obj"	"$(INTDIR)\qnmsCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\..\qyCommProc\qyCommProc.cpp

!IF  "$(CFG)" == "qyNmsModule - Win32 Release"


"$(INTDIR)\qyCommProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qyNmsModule - Win32 Debug"


"$(INTDIR)\qyCommProc.obj"	"$(INTDIR)\qyCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\qyMc\qymcPublic\qnmScan.cpp

!IF  "$(CFG)" == "qyNmsModule - Win32 Release"


"$(INTDIR)\qnmScan.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qyNmsModule - Win32 Debug"


"$(INTDIR)\qnmScan.obj"	"$(INTDIR)\qnmScan.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

