
#include	"stdafx.h"

#include	<windows.h>
#include	<tchar.h>
#include	<time.h>
#include	<stdlib.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyDefs_open.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCustom.h"
#include	"qyTCharCommProc.h"

#include	"tmpCeLib.h"



//
 QY_DMITEM  CONST_qyServiceIdTable[]  =
{
	{	CONST_qyServiceId_netMc,						(TCHAR*)_T(  "NetMc"  ),	},
	{	CONST_qyServiceId_is,							(TCHAR*)_T(  "Is"  ),		},
	{	CONST_qyServiceId_showInfo,						(TCHAR*)_T(  "showInfo"  ),	},
	{	-1,					},
};


 QY_DMITEM	CONST_qyAppTypeTable[]  =
{
	{	CONST_qyAppType_null,							(TCHAR*)_T(  ""  ),					},
	{	CONST_qyAppType_mc,								(TCHAR*)_T(  "mc"  ),				},		//  ???í????
	{	CONST_qyAppType_interMonOfBhb,					(TCHAR*)_T(  "interMon"  ),			},		//  bhb???????à????
	{	-1,												NULL,				},
};






 
 QY_DMITEM  CONST_qyCmdTable[]  =
{
	//  ????±?????
	{	CONST_qyCmd_tellService,						(TCHAR*)_T(  "tellService"  ),				},
	{	CONST_qyCmd_end,								(TCHAR*)_T(  "cmdEnd"  ),						},
	//  ???§?¨??:
	{	CONST_qyCmd_base,								(TCHAR*)_T(  "cmd_base"  ),						},
	{	CONST_qyCmd_getGlCntIp,							(TCHAR*)_T(  "getGlCntIp"  ),					},
	{	CONST_qyCmd_getCfgs,							(TCHAR*)_T(  "getCfgs"  ),						},
	{	CONST_qyCmd_sndLog,								(TCHAR*)_T(  "sndLog"  ),						},
	{	CONST_qyCmd_reg,								(TCHAR*)_T(  "reg"  ),							},
	//  {	CONST_qyCmd_commWithGlCnt,					(TCHAR*)_T(  "commWithGlCnt"  ),				},
	{	CONST_qyCmd_showQwmInfo,						(TCHAR*)_T(  "showQwmInfo"  ),					},
	{	CONST_qyCmd_queryReg,							(TCHAR*)_T(  "queryReg"  ),						},
	{	CONST_qyCmd_getProxyCfgs,						(TCHAR*)_T(  "getProxyCfgs"  ),					},
	{	CONST_qyCmd_putProxyChkedPcsInfo,				(TCHAR*)_T(  "putProxyChkedPcsInfo"  ),			},
	{	CONST_qyCmd_getProxyChkedPcsInfo,				(TCHAR*)_T(  "getProxyChkedPcsInfo"  ),			},
	{	CONST_qyCmd_getMacByIp,							(TCHAR*)_T(  "getMacByIp"  ),					},
	{	CONST_qyCmd_refreshProxyPolicy,					(TCHAR*)_T(  "refreshProxyPolicy"  ),			},
	{	CONST_qyCmd_getProxyStatusParams,				(TCHAR*)_T(  "getProxyStatusParams"  ),			},
	{	CONST_qyCmd_policyChanged,						(TCHAR*)_T(  "policyChanged"  ),				},
	{	CONST_qyCmd_quit,								(TCHAR*)_T(  "quit"  ),							},
	{	CONST_qyCmd_sndSecChkLog,						(TCHAR*)_T(  "sndSecChkLog"  ),					},
	{	CONST_qyCmd_secChkGetCfgs,						(TCHAR*)_T(  "secChkGetCfgs"  ),				},
	{	CONST_qyCmd_showQwmInfoEx,						(TCHAR*)_T(  "showQwmInfoEx"  ),				},
	{	CONST_qyCmd_showQwmAssetsInfo,					(TCHAR*)_T(  "showQwmAssetsInfo"  ),			},
	{	CONST_qyCmd_endShowQwmAssetsInfo,				(TCHAR*)_T(  "endShowQwmAssetsInfo"  ),			},
	{	CONST_qyCmd_queryPcSp,							(TCHAR*)_T(  "queryPcSp"  ),					},
	{	CONST_qyCmd_showQwmSvrStatus,					(TCHAR*)_T(  "showQwmSvrStatus"  ),				},
	{	CONST_qyCmd_showPcNetworkProp,					(TCHAR*)_T(  "showPcNetworkProp"  ),			},
	{	CONST_qyCmd_tryToConnectToServer,				(TCHAR*)_T(  "tryToConnectToServer"  ),			},
	{	CONST_qyCmd_showPcProcess,						(TCHAR*)_T(  "showPcProcess"  ),				},
	{	CONST_qyCmd_sndEventLog,						(TCHAR*)_T(  "sndEventLog"  ),					},
	{	CONST_qyCmd_sndUsrInfo,							(TCHAR*)_T(  "sndUsrInfo"  ),					},
	{	CONST_qyCmd_sndNetStat,							(TCHAR*)_T(  "sndNetStat"  ),					},
	{	CONST_qyCmd_sndPrinters,						(TCHAR*)_T(  "sndPrinters"  ),					},
	{	CONST_qyCmd_queryAutoLogon,						(TCHAR*)_T(  "queryAutoLogon"  ),				},
	{	CONST_qyCmd_sndAutoLogon,						(TCHAR*)_T(  "sndAutoLogon"  ),					},
	{	CONST_qyCmd_getOpCmd,							(TCHAR*)_T(  "getOpCmd"  ),						},
	{	CONST_qyCmd_sndCapScreen,						(TCHAR*)_T(  "sndCapScreen"  ),					},
	{	CONST_qyCmd_queryCfgs,							(TCHAR*)_T(  "queryCfgs"  ),					},
	{	CONST_qyCmd_showPcProcessModule,				(TCHAR*)_T(  "showPcProcessModule"  ),			},
	{	CONST_qyCmd_retrieveWarningMsg,					(TCHAR*)_T(  "retrieveWarningMsg"  ),			},
	{	CONST_qyCmd_sndRegistryVals,					(TCHAR*)_T(  "sndRegistryVals"  ),				},
	{	CONST_qyCmd_showPcNetFlow,						(TCHAR*)_T(  "showPcNetFlow"  ),				},
	{	CONST_qyCmd_showPcNetShare,						(TCHAR*)_T(  "showPcNetShare"  ),				},
	//
	{	CONST_qyCmd_talkTo,								(TCHAR*)_T(  "talkTo"  ),						},	//  2007/04/09
	{	CONST_qyCmd_refreshImObjListReq,				(TCHAR*)_T(  "refreshImObjListReq"  ),			},	//  2007/05/06
	{	CONST_qyCmd_refreshRecentFriendsReq,			(TCHAR*)_T(  "refreshRecentFriendsReq"  ),		},
	//
	{	CONST_qyCmd_mcComm,								(TCHAR*)_T(  "mcComm"  ),				},	//  2011/01/09
	//
	{	CONST_qyCmd_sendTask,							(TCHAR*)_T(  "sndTask"  ),						},
	{	CONST_qyCmd_sendTaskReply,						(TCHAR*)_T(  "sndTaskReply"  ),				},
	{	CONST_qyCmd_sendRobotTask,						(TCHAR*)_T(  "sndRobotTask"  ),				},
	{	CONST_qyCmd_sendRobotTaskReply,					(TCHAR*)_T(  "sndRobotTaskReply"  ),			},
	{	CONST_qyCmd_sendRobotTaskData,					(TCHAR*)_T(  "sndRobotTaskData"  ),			},
	//
	{	CONST_qyCmd_sendMedia,							(TCHAR*)_T(  "sndMedia"  ),					},	//  2008/03/15
	//
	{	CONST_qyCmd_lastMsgInSession,					(TCHAR*)_T(  "lastMsgInSession"  ),				},	//  2007/12/11
	//
	{	CONST_qyCmd_sendVDevReq,						(TCHAR*)_T(  "sndVDevReq"  ),					},	//  2008/01/24
	//
	//  ????±?????
	{	CONST_qyCmd_upReserved,							(TCHAR*)_T(  "upReserved"  ),					},
	{	CONST_qyCmd_update,								(TCHAR*)_T(  "update"  ),						},
	{	CONST_qyCmd_getFile,							(TCHAR*)_T(  "getFile"  ),						},
	{	CONST_qyCmd_getDigest,							(TCHAR*)_T(  "getDigest"  ),					},
	{	-1,												NULL,						},
};




 QY_DMITEM  CONST_qyRcTable[]  =  
{
	 //  ????±???
	{	CONST_qyRc_ok,					(TCHAR*)_T(  "OK"  ),						},
	{	CONST_qyRc_err,					(TCHAR*)_T(  "Err"  ),						},
	 //			 ???§?¨??
	{	CONST_qyRc_user,				(TCHAR*)_T(  "User"  ),					},
	{	CONST_qyRc_redirect,			(TCHAR*)_T(  "Redirect"  ),					},
	{	CONST_qyRc_needAutoReg,			(TCHAR*)_T(  "Need auto req"  ),				},
	//  #define		CONST_qyRc_notFound
	{	CONST_qyRc_needVerified,		(TCHAR*)_T(  "Need verified"  ),				},
	//
	{	CONST_qyRc_peerOffline,			(TCHAR*)_T(  "Peer offline"  ),				},
	{	CONST_qyRc_servBusy,			(TCHAR*)_T(  "Serv busy"  ),				},
	//
	//			 ????±???
	{	CONST_qyRc_upReserved,			(TCHAR*)_T(  "Up reserved"  ),					},
	{	CONST_qyRc_quit,				(TCHAR*)_T(  "Quit"  ),						},
	{	CONST_qyRc_update,				(TCHAR*)_T(  "Update"  ),						},
	{	-1,								NULL,						},
};


 //  鉴于CONST_qyRet_err定义为-1, 故将显示""
 QY_DMITEM	CONST_qyRetTable[]  =
{
	{	CONST_qyRet_ok,					(TCHAR*)_T(  "OK"  ),						},
	{	CONST_qyRet_redirect,			(TCHAR*)_T(  "Redirect"  ),					},
	{	CONST_qyRet_update,				(TCHAR*)_T(  "Update"  ),						},
	{	CONST_qyRet_quit,				(TCHAR*)_T(  "Quit"  ),						},
	{	-1,								NULL,						},
};







  extern  "C"  time_t  gettTimeBylStr(  char  *  timeBuf  )
{
	int			iErr	=	-1;
	char		buf[5];
	struct tm	tm;
	time_t		t1 = 0;

	memset( &tm, 0, sizeof( struct tm ) );
	memcpy( buf, timeBuf, 4 );
	buf[4] = 0;
	tm.tm_year += atol( buf ) - 1900;
	memcpy( buf, timeBuf + 4, 2 );
	buf[2] = 0;
	tm.tm_mon += atol( buf ) - 1;
	memcpy( buf, timeBuf + 6, 2 );
	tm.tm_mday += atol( buf );
	memcpy( buf, timeBuf + 8, 2 );
	tm.tm_hour += atol( buf );
	memcpy( buf, timeBuf + 10, 2 );
	tm.tm_min += atol( buf );
	memcpy( buf, timeBuf + 12, 2 );
	tm.tm_sec += atol( buf );

	t1  =  mymktime( &tm );
	if  (  t1  ==  -1  )  goto  errLabel;

	iErr  =  0;
    
errLabel:
	  
	return  iErr  ?  iErr  :  t1;

}






 extern  "C"  int  getTimeStr(  time_t  t,  char  *  timeBuf,  unsigned  int  size  )
{
	 struct  tm		*	p		=	NULL;
	 struct  tm			when;
     
	 if  (  !timeBuf  )  return  -1;
	 if  (  !(  p  =  mygmtime(  &t  )  )  )  return  -1;

     when  =  *p;		 
	 _snprintf(  timeBuf,  size,  "%04d%02d%02d%02d%02d%02d",  when.tm_year  +  1900,
				when.tm_mon  +  1,  when.tm_mday,  when.tm_hour,  when.tm_min,
		 		when.tm_sec  );        
   
	 return  0;

}


 //
#if 0
 extern  "C"  int  iiwaitForObject(  HANDLE  *  ph, DWORD  dwMilliseconds   )  
{  
	DWORD	dwRet  =  0;														

	if  (  !ph  )  return  -1;

	if  (  *ph  )  {											

		dwRet  =  WaitForSingleObject(  *ph,  dwMilliseconds   );				
		if  (  dwRet  !=  WAIT_TIMEOUT  &&  dwRet  !=  WAIT_FAILED  )  {	

			CloseHandle(  *ph  );  *ph  =  NULL;								

		}																											
	}																		

	return  0;

}
#endif





 //
  extern  "C"  BOOL  bObjTypeGrp(unsigned  int  uiObjType)
 {
	 bool  bRet = false;

	 switch (uiObjType) {
	 case  CONST_objType_imGrp:
	 case  CONST_objType_tmpGrp:
		 bRet = true;
		 break;
	 default:
		 break;
	 }

	 return  bRet;
 }


 //
 extern  "C"  BOOL  bTaskAlive(  int  iStatus  )
{
	switch  (  iStatus  )  {
			case  0:
			case  CONST_imTaskStatus_req:
			case  CONST_imTaskStatus_resp:  
			case  CONST_imTaskStatus_applyToSend:
			case  CONST_imTaskStatus_waitToSend:
			case  CONST_imTaskStatus_applyToRecv:
			case  CONST_imTaskStatus_waitToRecv:
			case  CONST_imTaskStatus_acceptedByReceiver:
			case  CONST_imTaskStatus_dualByReceiver:
				  return  TRUE;
				  break;
			default:
					break;
	}
	return  FALSE;

 }

 //
 extern "C" bool bTaskNeedAcception(int iStatus)
 {
	 switch (iStatus)
	 {
	 case 0:
	 case CONST_imTaskStatus_resp:
	 case CONST_imTaskStatus_applyToRecv:
		 return true;
	 default:
		 break;
	 }
	 return false;
 }


 
