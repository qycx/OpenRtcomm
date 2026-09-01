

#include	"stdafx.h"
#include	<tchar.h>
#ifndef  __WINCE__
	#include	<vfw.h>
#else
	#ifdef  __TEST__
		#include	<vfw.h>
	#endif
	#include	<mmreg.h>
	#include	<msacm.h>
#endif

#include	<shlobj.h>

#include	"qyMcMainCommon.h"
//#include	"myresource.h"

#include	"myfourcc.h"


#include	"tmpCeLib.h"
#include	"policyAvParams.h"



//
PolicyAvParams  gAvParams1;

//
PolicyAvParams  *  get_g_pAvParams(  )
{
	return  &gAvParams1;
}


