
#include	"stdafx.h"

#include	"qyPrecomp.h"
#include	<winsock2.h>
#include	<windows.h>
#include	<assert.h>
#include	<tchar.h>
#include	<iphlpapi.h>
//  #include	<IPTypes.h>
#include	<stdlib.h>

#include	"qyCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qySyncCommProc.h"
//
#include	"qyMcMainCommon.h"
//int  showInfo_open0(  void  *  p0,  LPCTSTR  tWhere,  LPCTSTR  hint  );



 void  qyExitProcessEx(  LPCTSTR  hint,  BOOL  bNoGui  )
{
	if  (  !hint  )  hint  =  _T(  "qyExitProcess called"  );

	if  (  bNoGui  )  {
		showInfo_open0(  0,  0,  hint  );
		}
	else  {
#ifdef  __DEBUG__
		  MessageBox(  NULL,  hint,  _T(  "Serious error."  ),  MB_OK  |  MB_TASKMODAL  );
#endif
	}
	//
	ExitProcess(  0  );
}


