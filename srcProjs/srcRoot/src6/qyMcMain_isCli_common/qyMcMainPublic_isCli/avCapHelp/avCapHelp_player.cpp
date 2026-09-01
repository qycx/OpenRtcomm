
#include "stdafx.h"


#ifndef  __WINCE__
		 //  #include	<afxtempl.h>
#endif


#ifndef  __WINCE__
	#include	<vfw.h>
#else
	#ifdef  __TEST__
		#include	<vfw.h>
	#endif
	#include	<mmreg.h>
	#include	<MSAcm.h>
#endif

#include	<Wincrypt.h>

#include	<tchar.h>
#include	<WinSock2.h>

#include	"avCapHelp_common.h"



