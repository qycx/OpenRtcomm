

#include	"stdafx.h"

#include	"qyPrecomp.h"

#include	<windows.h>
#include	<assert.h>
#include	<tchar.h>
#ifndef  __WINCE__
	#include	<vfw.h>
#else
	#ifdef  __TEST__
		#include	<vfw.h>
	#endif
	#include	<mmreg.h>
	#include	<MSAcm.h>
#endif
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyCommCommon.h"
#include	"qyWmComm.h"
#include	"qyCommProc.h"
#include	"qmOpenCommon.h"

#include	"qySyncCommProc.h"
#include	"genericQueue.h"
#include	"qyq2.h"				//  2009/05/13

#include	"qnmCommProc.h"
//#include	"qnmCommProc_mis.h"
//#include	"qyWmComm_is.h"



//  2015/06/07
extern  "C"  __declspec(  dllexport  ) int  WINAPI  assert_MessageBox(  HWND hWnd ,  LPCWSTR lpText,  LPCWSTR lpCaption,  UINT uType  )
 {
#ifdef  __DEBUG__
	 //
	 return  ::MessageBox(  hWnd,  lpText,  lpCaption,  uType  );
#else
	 return  0;
#endif
 }
