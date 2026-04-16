

#ifdef  __WINCE__

	#ifdef  WIN32_PLATFORM_PSPC
			#include	"resource_main_win32.h"
			#include	"resourceppc.h"
	#endif 

	#ifdef  WIN32_PLATFORM_WFSP
			#include	"resource_main_win32.h"
			#include	"resourcesp.h"
	#endif

	#ifdef  WIN32_PLATFORM_QMSP
			#include	"resource_main_win32.h"
			#include	"resource_main_winCe.h"
	#endif


#else
	#include	"resource_main_isCli_noMfc.h"
#endif



