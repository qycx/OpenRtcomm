

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

#include	<dbt.h>
#include	<mmreg.h>
#include	<msacm.h>
#ifndef   __WINCE__
	#include	<fcntl.h>
	#include	<io.h>
#endif
#include	<stdio.h>
#include	<commdlg.h>
#include	<strsafe.h>

#include	<dshow.h>

#ifndef  __WINCE__
#pragma include_alias( "dxtrans.h", "myqedit.h" )
#define __IDxtCompositor_INTERFACE_DEFINED__
#define __IDxtAlphaSetter_INTERFACE_DEFINED__
#define __IDxtJpeg_INTERFACE_DEFINED__
#define __IDxtKey_INTERFACE_DEFINED__

	//  #include	<Qedit.h>
	#include	<myQedit.h>
#endif
#include	<Mediaobj.h>
#include	<Dmo.h>


#include	<dvdmedia.h>


//  #include	"qmcDmo.h"
#include	"qmcVideoCapture_isCli.h"
#ifndef  __WINCE__
	#include	"qmcVideoCapture_dx.h"
#endif

#include	"qyDynLib.h"

#include	"mywmcodecconst.h"
#include	"mywmcodeciface.h"
#include	"myfourcc.h"

#include	"qyAvRecord.h"
#include	"qyAvRecord_dx.h"



