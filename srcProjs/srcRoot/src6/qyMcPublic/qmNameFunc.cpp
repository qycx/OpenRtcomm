

#include	"stdafx.h"
#include	<tchar.h>

#ifndef	 __WINCE__
	#include	<vfw.h>
	#include	<winsvc.h>
#else
	#ifdef  __TEST__
		#include	<vfw.h>
	#endif
	#include	<mmreg.h>
	#include	<MSAcm.h>
	#include	<time.h>
#endif
#include	<WinSock2.h>

#include	"qmCommon.h"

#include	"qisNameDefs.h"



