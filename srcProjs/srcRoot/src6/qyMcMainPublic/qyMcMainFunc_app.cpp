


#include	"stdafx.h"
#include	"shlobj.h"
#ifndef  __WINCE__
		 //  #include	"myresource.h"
#endif

#include	<tchar.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCustom.h"
#include	"qyTCharCommProc.h"

#include	"qyWmComm.h"
#include	"qyCommCommon.h"


#include	"qnmCommProc.h"


#if  0
 QNM_SYSCFG_INFO  CONST_qnmSysCfgInfoTable[]  =																																														//  Mgr,  System,  Cfg,  pcList,  eventList,  netDevEventList,  searchList,
{																		// defaultDsnName;	rootKey_qnmScheduler;

	{	CONST_qySystemId_bhb,		CONST_qyAppType_null,				FALSE,	_T(  CONST_qyDsn_netMc  ),				_T(  CONST_qyRootKey_mcGui_netMc  ),		_T(  CONST_qyRootKey_qnmScheduler  ),								},
	{	CONST_qySystemId_bhb,		CONST_qyAppType_interMonOfBhb,		FALSE,	_T(  CONST_qyDsn_netMc  ),				_T(  CONST_qyRootKey_mcGui_netMc  ),		_T(  CONST_qyRootKey_qnmScheduler  ),								},
	{	CONST_qySystemId_netMc2,	CONST_qyAppType_null,				FALSE,	_T(  CONST_qyDsn_netMc  ),				_T(  CONST_qyRootKey_mcGui_netMc  ),		_T(  CONST_qyRootKey_qnmScheduler  ),								},
	{	CONST_qySystemId_nms,		CONST_qyAppType_null,				FALSE,	_T(  CONST_qyDsn_netMc  ),				_T(  CONST_qyRootKey_mcGui_netMc  ),		_T(  CONST_qyRootKey_qnmScheduler  ),								},
	{	CONST_qySystemId_secChk,	CONST_qyAppType_null,				FALSE,	_T(  CONST_qyDsn_netMc  ),				_T(  CONST_qyRootKey_mcGui_netMc  ),		_T(  CONST_qyRootKey_qnmScheduler  ),								},
	//  {	CONST_qySystemId_netMc4,	CONST_qyAppType_null,																																		},
	{	CONST_qySystemId_assetMgr,	CONST_qyAppType_null,				FALSE,	_T(  CONST_qyDsn_netMc  ),				_T(  CONST_qyRootKey_mcGui_netMc  ),		_T(  CONST_qyRootKey_qnmScheduler  ),								},
	//
	{	CONST_qySystemId_messenger,	CONST_qyAppType_null,				TRUE,	_T(  CONST_qyDbNamePrefix_mis  ),		_T(  CONST_qyRootKey_mcGui_mis  ),			_T(  CONST_qyRootKey_qnmScheduler_mis  ),							},
	{	CONST_qySystemId_messenger,	CONST_qyAppType_client,				TRUE,	_T(  CONST_qyDbNamePrefix_misClient  ),	_T(  CONST_qyRootKey_mcGui_misClient  ),	_T(  CONST_qyRootKey_qnmScheduler_misClient  ),						},
	{	-1,							NULL,																																},
};

 __declspec(  dllexport  )  QNM_SYSCFG_INFO	*	getQnmSysCfgInfo(  int  iSystemId,  int  iAppType  )
{
	 QNM_SYSCFG_INFO	*	p	=	NULL;

	 for  (  p  =  CONST_qnmSysCfgInfoTable;  p->iSystemId  !=  -1;  p  ++  )  {
		  if  (  p->iSystemId  ==  iSystemId  &&  iAppType  ==  p->iAppType  )  return  p;
	 }
	 //  如果没有全部对应的，则返回仅iSystemId符合的
	 for  (  p  =  CONST_qnmSysCfgInfoTable;  p->iSystemId  !=  -1;  p  ++  )  {
		  if  (  p->iSystemId  ==  iSystemId  )  return  p;
	 }
	 return  NULL;
}

#endif


