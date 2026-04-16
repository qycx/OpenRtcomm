

#include	"stdafx.h"

#include	"qyPrecomp.h"
#include	<winsock2.h>
#include	<windows.h>
#include	<assert.h>
#include	<stddef.h>
#include	<tchar.h>
#include	<stdlib.h>
//
//#include	<mmeapi.h>
#include	<MMSystem.h>
//
#include	"qyCommon.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qnmPcComm.h"
#include	"qnmAssetsCommProc.h"
#include	"qnmSpCommProc.h"
#include	"qwmNetworkStatusCommProc.h"
#include	"qyTCharCommProc.h"
#include	"qnmCustom.h"
#include	"qySyncCommProc.h"
#include	"genericQueue.h"
#include	"qyq2.h"
#include	"tmpCeLib.h"
#include	"qyShowInfoCommon.h"
#include	"qy_qBuf2_defs.h"
#include <string>

//
extern  ShowInfo_struct  *  g_pShowInfoStruct;//  =  NULL;

//
#if  0
extern  "C"  __declspec(  dllexport  )  int  set_g_pShowInfoStruct(  void  *  pShowInfoStruct  )
{
	if  (  !pShowInfoStruct  )  return  -1;
	//g_pShowInfoStruct  =  (  ShowInfo_struct  *  )pShowInfoStruct;
	return  0;
}
#endif


//
static int  dbg_sFilter(QY_SHOW_STRUCT  &  ss,  int  iParam)
{
#ifdef  __DEBUG__

	std::wstring tmp_wStr;
	tmp_wStr.assign(ss.what);
	if (tmp_wStr.find(L"failed") != std::wstring::npos) {
		int  ii = 0;
	}

	//if (tcsstr())
#endif 

	return  0;
}



extern  "C"	 __declspec(  dllexport  )  int  qyShowInfo(  void  *  pCtx_showInfo,  int  iShowType,  unsigned  int  *  puiStep,  char  *  clientIp,  LPCWSTR  who_from,  LPCWSTR  who_to,  LPCWSTR  where,  LPCWSTR  doStr,  LPCWSTR  fmt,  ...  )
{
#ifdef  __WINCE__
		return  0;
#endif

	va_list			args;
#ifndef  __WINCE__
	int				errnoBuf;
#endif
	HWND			firstWnd			=		NULL;
	QY_SHOW_STRUCT	showStruct;
	//  char			fileNameBuf[257];
	//  char			timeBuf[CONST_qyTimeLen  +  1];
	FILE		*	fperr				=		NULL;
	int				fileLen				=		0;
	
	
	#ifndef  __DEBUG__
			if  (  iShowType  ==  CONST_qyShowType_debug  )  return  0;
	#endif

#ifndef  __WINCE__
	errnoBuf  =  errno;
#endif

	va_start(  args,  fmt  );

	memset(  &showStruct,  0,  sizeof(  showStruct  )  );
	showStruct.iType  =  iShowType;
	if  (  clientIp  &&  clientIp[0]  )  showStruct.ulClientIp  =  inet_addr(  clientIp  );
	if  (  who_from  )  {
		_snwprintf_s(  showStruct.who_from,  mycountof(  showStruct.who_from  ),  _TRUNCATE,  L"%s",  who_from  );
	}
	if  (  who_to  )  {
		_snwprintf_s(  showStruct.who_to,  mycountof(  showStruct.who_to  ),  _TRUNCATE,  L"%s",  who_to  );
	}
	if  (  where  )  {
		_snwprintf_s(  showStruct.whereBuf,  mycountof(  showStruct.whereBuf  ),  _TRUNCATE,  L"%s",  where  );
	}
	//  when
	GetLocalTime(  &showStruct.when  );	//  2007/06/01
	if  (  puiStep  )  {				//  2008/04/28
		(  *puiStep  )  ++  ;
		showStruct.usStep  =  *puiStep;
	}
	//  201508/20
	showStruct.dwProcessId  =  GetCurrentProcessId(  );  //  2015/08/30
	showStruct.dwThreadId  =  GetCurrentThreadId(  );
	//
	if  (  doStr  )  {
		_snwprintf_s(  showStruct.doStr,  mycountof(  showStruct.doStr  ),  _TRUNCATE,  L"%s",  doStr  );
	}
	_vsnwprintf_s(  showStruct.what,  mycountof(  showStruct.what  )  -  1,  _TRUNCATE,  fmt,  args  );  


	//
#ifdef  __DEBUG__
	{
		dbg_sFilter(showStruct,0);
	}
#endif 


	//
	//  MACRO_qyAssert(  g_pShowInfoStruct,  _T(  "qyShowInfo1: g_pShowInfoStruct is null"  )  );
	//  if  (  !g_pShowInfoStruct  )  return  -1;
	if  (  pCtx_showInfo  )  {
		ShowInfo_struct  &  sShowInfoStruct  =  *(  ShowInfo_struct  *  )pCtx_showInfo;	//  g_pShowInfoStruct;

		//  调用显示信息用的汇调函数
		if  (  sShowInfoStruct.errHintPf  )  sShowInfoStruct.errHintPf(  &showStruct,  0  );

		if  (  sShowInfoStruct.bInited  )  {
			
			switch  (  showStruct.iType  )  {
					case  CONST_qyShowType_qmdState:
						  //if  (  !isQ2Warning(  &sShowInfoStruct.state_q2,  100  )  )  
						  if (!sShowInfoStruct.pstate_q2->is_Q2Warning( 100))
						  {
							  HeadData_showInfo headData;
							  memset(&headData, 0, sizeof(headData));
							  //int tmpLen = sizeof(showStruct);
							  headData.len_showInfo = sizeof(showStruct);

								//q2PostMsg(  &showStruct,  sizeof(  showStruct  ),  &sShowInfoStruct.state_q2,  _T(  "showInfo.state_q2"  )  );										
							    sShowInfoStruct.pstate_q2->q2PostMsg( &headData,  &showStruct,  sizeof(  showStruct  ),  _T(  "showInfo.state_q2"  ));
								//
								sShowInfoStruct.pq2->q2PostMsgAndTrigger(  mynull,  0,  0,  _T(  "showInfo.q2 trig"  ));
						  }
						  break;
					default:
							//  2014/05/11
						    if  (  !sShowInfoStruct.pq2->is_Q2Warning(    100  )  )  {
								HeadData_showInfo headData;
								memset(&headData, 0, sizeof(headData));
								headData.len_showInfo = sizeof(showStruct);

								sShowInfoStruct.pq2->q2PostMsgAndTrigger(  &headData, &showStruct,  sizeof(  showStruct  ),  _T(  "showInfo.q2 "  ));
							}
							break;
			}

			}
		else  {
			  traceLog(  _T(  "qyShowInfo failed: showInfoStruct not inited"  )  );
		}

		}
	else  {
		  //
		  TCHAR  *  errHintWndCls  =  CONST_qnmStatusToolWndClass_client;

		  if  (  errHintWndCls[0]  )  {

			  firstWnd  =  FindWindow(  errHintWndCls,  NULL  );
			  if  (  firstWnd  )  {
				  COPYDATASTRUCT	tmpCopyData;
			
				  tmpCopyData.lpData  =  &showStruct;
				  tmpCopyData.cbData  =  sizeof(  showStruct  );
				  SendMessage( firstWnd,  WM_COPYDATA,  NULL,  (  LPARAM  )&tmpCopyData  );			
			  }

			  //  traceLogA(  "%s %s %s %s %s",  showStruct.when,  showStruct.who,  showStruct.where,  showStruct.doStr,  showStruct.what  );

		  }
	}

	/*
	*/

	va_end(  args  );

#ifndef  __WINCE__
	errno  =  errnoBuf;
#endif

	return  0;
}


extern  "C"	 __declspec(  dllexport  )  int  qyShowInfo1(  int  iShowType,  unsigned  int  *  puiStep,  char  *  clientIp,  LPCWSTR  who_from,  LPCWSTR  who_to,  LPCWSTR  where,  LPCWSTR  doStr,  LPCWSTR  fmt,  ...  )
{
#ifdef  __WINCE__
		return  0;
#endif

	va_list			args;
#ifndef  __WINCE__
	int				errnoBuf;
#endif
	HWND			firstWnd			=		NULL;
	QY_SHOW_STRUCT	showStruct;
	//  char			fileNameBuf[257];
	//  char			timeBuf[CONST_qyTimeLen  +  1];
	FILE		*	fperr				=		NULL;
	int				fileLen				=		0;
	
	
	#ifndef  __DEBUG__
			if  (  iShowType  ==  CONST_qyShowType_debug  )  return  0;
	#endif

#ifndef  __WINCE__
	errnoBuf  =  errno;
#endif

	va_start(  args,  fmt  );

	memset(  &showStruct,  0,  sizeof(  showStruct  )  );
	showStruct.iType  =  iShowType;
	if  (  clientIp  &&  clientIp[0]  )  showStruct.ulClientIp  =  inet_addr(  clientIp  );
	if  (  who_from  )  {
		_snwprintf_s(  showStruct.who_from,  mycountof(  showStruct.who_from  ),  _TRUNCATE,  L"%s",  who_from  );
	}
	if  (  who_to  )  {
		_snwprintf_s(  showStruct.who_to,  mycountof(  showStruct.who_to  ),  _TRUNCATE,  L"%s",  who_to  );
	}
	if  (  where  )  {
		_snwprintf_s(  showStruct.whereBuf,  mycountof(  showStruct.whereBuf  ),  _TRUNCATE,  L"%s",  where  );
	}
	//  when
	GetLocalTime(  &showStruct.when  );	//  2007/06/01
	if  (  puiStep  )  {				//  2008/04/28
		(  *puiStep  )  ++  ;
		showStruct.usStep  =  *puiStep;
	}
	//  201508/20
	showStruct.dwProcessId  =  GetCurrentProcessId(  );  //  2015/08/30
	showStruct.dwThreadId  =  GetCurrentThreadId(  );
	//
	if  (  doStr  )  {
		_snwprintf_s(  showStruct.doStr,  mycountof(  showStruct.doStr  ),  _TRUNCATE,  L"%s",  doStr  );
	}
	_vsnwprintf_s(  showStruct.what,  mycountof(  showStruct.what  )  -  1,  _TRUNCATE,  fmt,  args  );  


	//
#ifdef  __DEBUG__
	{
		dbg_sFilter(showStruct, 1);
	}
#endif 


	//
	//  MACRO_qyAssert(  g_pShowInfoStruct,  _T(  "qyShowInfo1: g_pShowInfoStruct is null"  )  );
	if  (  g_pShowInfoStruct  )  {
		ShowInfo_struct  &  sShowInfoStruct  =  *g_pShowInfoStruct;

		//  调用显示信息用的汇调函数
		if  (  sShowInfoStruct.errHintPf  )  sShowInfoStruct.errHintPf(  &showStruct,  0  );

		if  (  sShowInfoStruct.bInited  )  {
			
			switch  (  showStruct.iType  )  {
					case  CONST_qyShowType_qmdState:
						  if  (  !sShowInfoStruct.pstate_q2->is_Q2Warning(  100  )  )  {
							  HeadData_showInfo headData;
							  memset(&headData, 0, sizeof(headData));
							  headData.len_showInfo = sizeof(showStruct);

							  sShowInfoStruct.pstate_q2->q2PostMsg(  &headData,  &showStruct,  sizeof(  showStruct  ),  _T(  "showInfo.state_q2"  ));
								//
							  sShowInfoStruct.pq2->q2PostMsgAndTrigger(  mynull,0,  0,  _T(  "showInfo.q2 trig"  ));
						  }
						  break;
					default:
							//  2014/05/11
						    if  (  !sShowInfoStruct.pq2->is_Q2Warning(    100  )  )  {
								HeadData_showInfo headData;
								memset(&headData, 0, sizeof(headData));
								headData.len_showInfo = sizeof(showStruct);

								sShowInfoStruct.pq2->q2PostMsgAndTrigger(  &headData,  &showStruct,  sizeof(  showStruct  ),  _T(  "showInfo.q2"  ));
							}
							break;
			}

			}
		else  {
			  traceLog(  _T(  "qyShowInfo1 failed: showInfoStruct not inited"  )  );
		}
		}
	else  {
		  //
		  TCHAR  *  errHintWndCls  =  CONST_qnmStatusToolWndClass_client;

		  if  (  errHintWndCls[0]  )  {

			  firstWnd  =  FindWindow(  errHintWndCls,  NULL  );
			  if  (  firstWnd  )  {
				  COPYDATASTRUCT	tmpCopyData;
			
				  tmpCopyData.lpData  =  &showStruct;
				  tmpCopyData.cbData  =  sizeof(  showStruct  );
				  SendMessage( firstWnd,  WM_COPYDATA,  NULL,  (  LPARAM  )&tmpCopyData  );			
			  }

			  //  traceLogA(  "%s %s %s %s %s",  showStruct.when,  showStruct.who,  showStruct.where,  showStruct.doStr,  showStruct.what  );

		  }
	}

	/*
	*/

	va_end(  args  );

#ifndef  __WINCE__
	errno  =  errnoBuf;
#endif

	return  0;
}


//
extern  "C"	 __declspec(  dllexport  )  int  qyShowInfo2(  PARAM_showInfo  *  pParam,  int  iShowType,  unsigned  int  *  puiStep,  char  *  clientIp,  LPCWSTR  who_from,  LPCWSTR  who_to,  LPCWSTR  where,  LPCWSTR  doStr,  LPCWSTR  fmt,  ...  )
{
#ifdef  __WINCE__
		return  0;
#endif

	va_list			args;
#ifndef  __WINCE__
	int				errnoBuf;
#endif
	HWND			firstWnd			=		NULL;
	QY_SHOW_STRUCT	showStruct;
	//  char			fileNameBuf[257];
	//  char			timeBuf[CONST_qyTimeLen  +  1];
	FILE		*	fperr				=		NULL;
	int				fileLen				=		0;
	
	
	#ifndef  __DEBUG__
			if  (  iShowType  ==  CONST_qyShowType_debug  )  return  0;
	#endif

#ifndef  __WINCE__
	errnoBuf  =  errno;
#endif

	va_start(  args,  fmt  );

	//
	PARAM_showInfo  param =  {0};
	if  (  pParam  )  param  =  *pParam;

	//
	memset(  &showStruct,  0,  sizeof(  showStruct  )  );
	showStruct.iType  =  iShowType;
	//
	showStruct.usStateType = param.usStateType;
	showStruct.usStateSubtype = param.usStateSubtype;
	//
	showStruct.when = param.when;
	//
	showStruct.iPos_toDisplay  =  param.iPos_toDisplay;
	//
	showStruct.iTaskId = param.iTaskId;
	//
	if  (  clientIp  &&  clientIp[0]  )  showStruct.ulClientIp  =  inet_addr(  clientIp  );
	if  (  who_from  )  {
		_snwprintf_s(  showStruct.who_from,  mycountof(  showStruct.who_from  ),  _TRUNCATE,  L"%s",  who_from  );
	}
	if  (  who_to  )  {
		_snwprintf_s(  showStruct.who_to,  mycountof(  showStruct.who_to  ),  _TRUNCATE,  L"%s",  who_to  );
	}
	if  (  where  )  {
		_snwprintf_s(  showStruct.whereBuf,  mycountof(  showStruct.whereBuf  ),  _TRUNCATE,  L"%s",  where  );
	}
	//  when
	if (showStruct.when.wYear == 0 && showStruct.when.wMonth == 0) {
		GetLocalTime(&showStruct.when);	//  2007/06/01
	}
	if  (  puiStep  )  {				//  2008/04/28
		(  *puiStep  )  ++  ;
		showStruct.usStep  =  *puiStep;
	}
	//  201508/20
	showStruct.dwProcessId  =  GetCurrentProcessId(  );  //  2015/08/30
	showStruct.dwThreadId  =  GetCurrentThreadId(  );
	//
	if  (  doStr  )  {
		_snwprintf_s(  showStruct.doStr,  mycountof(  showStruct.doStr  ),  _TRUNCATE,  L"%s",  doStr  );
	}
	_vsnwprintf_s(  showStruct.what,  mycountof(  showStruct.what  )  -  1,  _TRUNCATE,  fmt,  args  );  


	//
#ifdef  __DEBUG__
	{
		dbg_sFilter(showStruct,2);
	}
#endif 


	//
	//  MACRO_qyAssert(  g_pShowInfoStruct,  _T(  "qyShowInfo1: g_pShowInfoStruct is null"  )  );
	if  (  g_pShowInfoStruct  )  {
		ShowInfo_struct  &  sShowInfoStruct  =  *g_pShowInfoStruct;

		//  调用显示信息用的汇调函数
		if  (  sShowInfoStruct.errHintPf  )  sShowInfoStruct.errHintPf(  &showStruct,  0  );

		if  (  sShowInfoStruct.bInited  )  {
			
			switch  (  showStruct.iType  )  {
					case  CONST_qyShowType_qmdState:
						  if  (  !sShowInfoStruct.pstate_q2->is_Q2Warning(  100  )  )  {
							  HeadData_showInfo headData;
							  memset(&headData, 0, sizeof(headData));
							  headData.len_showInfo = sizeof(showStruct);

							  sShowInfoStruct.pstate_q2->q2PostMsg(  &headData,  &showStruct,  sizeof(  showStruct  ),  _T(  "showInfo.state_q2"  ));
								//
							  sShowInfoStruct.pq2->q2PostMsgAndTrigger(  mynull,0,  0,   _T(  "showInfo2.state_q2, trig"  )  );
						  }
						  break;
					default:
							//  2014/05/11
						    if  (  !sShowInfoStruct.pq2->is_Q2Warning(    100  )  )  {
								HeadData_showInfo headData;
								memset(&headData, 0, sizeof(headData));
								headData.len_showInfo = sizeof(showStruct);
								sShowInfoStruct.pq2->q2PostMsgAndTrigger(  &headData,&showStruct,  sizeof(  showStruct  ),    _T(  "showInfo2.q2"  )  );
							}
							break;
			}

			}
		else  {
			  traceLog(  _T(  "qyShowInfo1 failed: showInfoStruct not inited"  )  );
		}
		}
	else  {
		  //
		  TCHAR  *  errHintWndCls  =  CONST_qnmStatusToolWndClass_client;

		  if  (  errHintWndCls[0]  )  {

			  firstWnd  =  FindWindow(  errHintWndCls,  NULL  );
			  if  (  firstWnd  )  {
				  COPYDATASTRUCT	tmpCopyData;
			
				  tmpCopyData.lpData  =  &showStruct;
				  tmpCopyData.cbData  =  sizeof(  showStruct  );
				  SendMessage( firstWnd,  WM_COPYDATA,  NULL,  (  LPARAM  )&tmpCopyData  );			
			  }

			  //  traceLogA(  "%s %s %s %s %s",  showStruct.when,  showStruct.who,  showStruct.where,  showStruct.doStr,  showStruct.what  );

		  }
	}

	/*
	*/

	va_end(  args  );

#ifndef  __WINCE__
	errno  =  errnoBuf;
#endif

	return  0;
}

