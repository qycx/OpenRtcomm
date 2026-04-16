


#include	"stdafx.h"

#include	<windows.h>
#include	<tchar.h>
#include	<WinSock2.h>
#include	<stdlib.h>

#include	"qyCommon.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCustom.h"
#include	"qyTCharCommProc.h"

#include	"testOnly.h"

#ifdef  __TEST_ONLY__

static  BOOL  __sbTestOn(  )
{
#if  0  ||  defined(  __DEBUG__  )
		//return  TRUE;
#endif

		return  FALSE;
}

BOOL  b__TEST_ON__(  )
{
	return  __sbTestOn(  );
}

BOOL  b__TEST_joinInBgWall__(  )
{
	if  (  !__sbTestOn(  )  )  {
		return  FALSE;
	}

	return  TRUE;
}

//
//  2014/11/22
BOOL  b__TEST_avProxy__(  )
{
	if  (  !__sbTestOn(  )  )  {
		return  FALSE;
	}
#if  0
	traceLog(  _T(  "Note: b__TEST_avProxy__ is on"  )  );
	return  TRUE;
#endif
	return  FALSE;
}




#endif




