
#include	"stdafx.h"

#include	"qyPrecomp.h"
#include	<winsock2.h>
#include	<windows.h>
#include	<stddef.h>
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
#include	<Wincrypt.h>

#include	"qyCommon.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qmOpenCommon.h"
#include	"qyMsgFunc.h"

#include	"qySyncCommProc.h"
#include	"genericQueue.h"
#include	"qyq2.h"				//  2009/05/13

#include	"qnmCommProc_mis.h"
#include	"qnmPcComm.h"
#include	"qnmAssetsCommProc.h"
#include	"qnmSpCommProc.h"
#include	"qwmNetworkStatusCommProc.h"
#include	"qyTCharCommProc.h"
#include	"qnmCustom.h"
#include	"qySyncCommProc.h"
#include	"qmCrypt.h"
#include	"qnmFwCommProc.h"
//  #include	"qyGuiCommProc.h"


int  printImMsgContent_n(  void  *  pSessionParam,  MSG_ROUTE  *  pRoute,  IM_CONTENTU  *  pContent_n,  int  iContentLen,  TCHAR  *  tBuf,  unsigned  int  maxuiBufCnt  )
{
	traceLogA(  (char*)  "test"  );
	return  0;
}



 #ifdef  __DEBUG__
int  printMsgRoute(  unsigned  char  ucFlg,  MSG_ROUTE  *  pRoute  )
{
	if  (  !pRoute  )  return  -1;

	if  (  !pRoute->idInfo_to.ui64Id  )  traceLogA(  (char*)  "msgRoute is null"  );
	else  {
		  TCHAR	tBuf[256];
		  int  i;
		  if  (  isUcFlgRouteTalkData(  ucFlg  )  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "msgRoute: RouteTalkData"  )  );
		  //else  if  (  isUcFlgTalkData(  ucFlg  )  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "msgRoute: TalkData"  )  );
		  //
		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. %I64u->%I64u"  ),  tBuf,  pRoute->idInfo_from.ui64Id,  pRoute->idInfo_to.ui64Id  );
		  for  (  i  =  0;  i  <  mycountof(  pRoute->mems_to  );  i  ++  )  {
			   if  (  !pRoute->mems_to[i].idInfo.ui64Id  )  break;
			   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %I64u"  ),  tBuf,  pRoute->mems_to[i].idInfo.ui64Id  );
		  }
		  traceLogA(  (char*)  "%S",  tBuf  );
	}
	return  0;
}


 int  snprintContent(  MIS_MSG_routeTalkData  *  pTalkData,  IM_CONTENTU  *  pContent,  TCHAR  *  tBuf,  unsigned  int  cnt  )
{
	
	char	timeBuf[CONST_qyTimeLen  +  1]	=	"";

	if  (  pTalkData  )  {
		_sntprintf(  tBuf,  cnt,  _T(  "%s, msgrId_src is %I64u, msgrId_dst is %I64u"  ),  tBuf,  pTalkData->route.idInfo_from.ui64Id,  pTalkData->route.idInfo_to.ui64Id  );
		pContent  =  (  IM_CONTENTU  *  )pTalkData->buf;
	}
	if  (  !pContent  )  return  -1;

	_sntprintf(  tBuf,  cnt,  _T(  "%s, %s"  ),  tBuf,  qyGetDesByType1(  CONST_qyCommTypeTable_en,  pContent->uiType  )  );
	switch  (  pContent->uiType  )  {
			case  CONST_imCommType_simpleResp:
				  _sntprintf(  tBuf,  cnt,  _T(  "%s, %s, %s"  ),  tBuf,  qyGetDesByType1(  CONST_qyCmdTable,  pContent->simpleResp.usCmd_org  ),  qyGetDesByType1(  CONST_qyCommTypeTable_en,  pContent->simpleResp.uiContentType_org  )  );
				  break;
			case  CONST_imCommType_htmlContent:
				  //  _sntprintf(  tBuf,  cnt,  _T(  "%s, %s"  ),  tBuf,  pContent->html.wBuf  );
				  break;
#if  0
			case  CONST_imCommType_streamContent:
				  //  stream
				  break;
#endif
			case  CONST_imCommType_transferFileReq:
				  _sntprintf(  tBuf,  cnt,  _T(  "%s, %s, %I64u bytes, usErrors is %d"  ),  tBuf,  pContent->transferFileReq.fileName,  pContent->transferFileReq.ui64FileLen,  pContent->transferFileReq.usErrors  );
				  break;
			case  CONST_imCommType_transferFileReplyReq:
				  getTimeStr(  (  time_t  )pContent->transferFileReplyReq.tStartTime_org,  timeBuf,  mycountof(  timeBuf  )  );
				  //_sntprintf(  tBuf,  cnt,  _T(  "%s, tStartTime_org is %S, uiTranNo_org is %d, ui64FileLen is %I64u, usErrors is %d"  ),  tBuf,  timeBuf,  pContent->transferFileReplyReq.uiTranNo_org,  pContent->transferFileReplyReq.ui64FileLen,  pContent->transferFileReplyReq.usErrors  );
				  break;
			case  CONST_imCommType_transferFileDataReq:
				  getTimeStr(  (  time_t  )pContent->transferFileDataReq.tStartTime_org,  timeBuf,  mycountof(  timeBuf  )  );
				  _sntprintf(  tBuf,  cnt,  _T(  "%s, tStartTime_org is %S,  uiTranNo_org is %d, dataBlockIndex is %d"  ),  tBuf,  timeBuf,  pContent->transferFileDataReq.uiTranNo_org,  pContent->transferFileDataReq.uiDataBlockIndex  );
				  break;
			case  CONST_imCommType_transferFileDataResp:
				  _sntprintf(  tBuf,  cnt,  _T(  "%s, dataBlockIndex is %d, uiLen is %d"  ),  tBuf,  pContent->transferFileDataResp.uiDataBlockIndex,  pContent->transferFileDataResp.uiLen  );
				  break;
			case  CONST_imCommType_taskProcReq:
				  getTimeStr(  (  time_t  )pContent->taskProcReq.tStartTime_org,  timeBuf,  mycountof(  timeBuf  )  );
				  _sntprintf(  tBuf,  cnt,  _T(  "%s, tStartTime_ort is %S, uiTranNo_org is %d"  ),  tBuf,  timeBuf,  pContent->taskProcReq.uiTranNo_org  );
				  break;
			default:
				    _sntprintf(  tBuf,  cnt,  _T(  "%s, contentType {%d}"  ),  tBuf,  pContent->uiType  );
					break;

	}
	return  0;
}

#endif
 
 int  printMisMsg(  void  *  bNetworkDataParam,  void  *  p1,  MIS_MSGU  *  pMsg  )
{	
	BOOL					bNetworkData	=	(  BOOL  )bNetworkDataParam;
	TCHAR					tBuf[2048]	=	_T(  ""  );
	IM_CONTENTU			*	pContent	=	NULL;
	char					timeBuf[CONST_qyTimeLen  +  1]	=	"";

#ifdef  __DEBUG__

	  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "\t%s"  ),  qyGetDesByType1(  CONST_misMsgTypeTable,  pMsg->uiType  )  );
	  OutputDebugString(  tBuf  );
	  switch  (  pMsg->uiType  )  {
			  case  CONST_misMsgType_input:
				    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s | %s"  ),  tBuf,  isUcFlgResp(  pMsg->input.ucFlg  )  ?  _T(  "Resp"  )  :  _T(  "Req"  )  );
					getTimeStr(  pMsg->input.tStartTime,  timeBuf,  mycountof(  timeBuf  )  );
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s,  tStartTime  is %S, tranNo is %d"  ),  tBuf,  timeBuf,  pMsg->input.uiTranNo  );
					pContent  =  M_getMsgContent(  pMsg->input.ucFlg,  &pMsg->input.data  );
					if  (  !pContent  )  break;
					if  (  bNetworkData  )  {
						#ifndef  __WINCE__
								 printImMsgContent_n(  NULL,  NULL,  pContent,  pMsg->input.lenInBytes, tBuf,  mycountof(  tBuf  )  );
						#endif
						}
					else  
						snprintContent(  0,  pContent,  tBuf,  mycountof(  tBuf  )  );
				    break;
			  case  CONST_misMsgType_req:
				    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s | %s"  ),  tBuf,  qyGetDesByType1(  CONST_qyCmdTable,  pMsg->req.usCode  )  );
					break;
			  case  CONST_misMsgType_recentFriend_qmc:
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, messengerId is %I64u, tickCnt is %u"  ),  tBuf,  pMsg->recentFriend_qmc.idInfo.ui64Id,  pMsg->recentFriend_qmc.dwTickCnt_op  );
					break;
			  case  CONST_misMsgType_talk:
				    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, uiTranNo_processed is %d,  uiSessionId is %d"  ), tBuf,  pMsg->talk.uiTranNo_processed,  pMsg->talk.uiSessionId  );
					if  (  !isUcFlgResp(  pMsg->talk.ucFlg  )  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, cmd is  %s"  ),   tBuf,  qyGetDesByType1(  CONST_qyCmdTable,  pMsg->talk.usCode  )  );
					else  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, cmd_org is  %s"  ),   tBuf,  qyGetDesByType1(  CONST_qyCmdTable,  pMsg->talk.usCode_org  )  );
				    snprintContent(  &pMsg->talk.data,  0,  tBuf,  mycountof(  tBuf  )  );
					break;
			  case  CONST_misMsgType_task:
			  case  CONST_misMsgType_outputTask:
				    getTimeStr(  pMsg->task.tStartTime,  timeBuf,  mycountof(  timeBuf  )  );
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, taskId %d, %s,  st %S, tn %d, sender %I64u, receiver %I64u"  ),  tBuf,  pMsg->task.iTaskId,  qyGetDesByType1(  CONST_qyStatusTable_en,  pMsg->task.iStatus  ),  timeBuf,  pMsg->task.uiTranNo,  pMsg->task.idInfo_taskSender.ui64Id,  pMsg->task.idInfo_taskReceiver.ui64Id  );
				    snprintContent(  &pMsg->task.data,  0,  tBuf,  mycountof(  tBuf  )  );
					break;
			  case  CONST_misMsgType_grp:
				    int  i;
					MIS_MSG_grpMemData	*	pMem;
					
					//  if  (  pMsg->grp.usCnt >=  2  )  {
					//		traceLogA(  (char*)  "hehe"  );
					// }					

					for  (  i  =  0;  i  <  pMsg->grp.usCnt;  i  ++  )  {
						 pMem  =  (  MIS_MSG_grpMemData  *  )(  pMsg->grp.buf  +  pMsg->grp.memDataHeads[i].uiPos  );
						 getTimelStr(  pMem->tStartTime,  timeBuf,  mycountof(  timeBuf  )  );
						 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "第%d个, tStartTime is %S, tranNo is %d. "  ),  i,  timeBuf,  pMem->uiTranNo  );
						 OutputDebugString(  tBuf  );
						 if  (  bNetworkData  )  {
							 #ifndef  __WINCE__
									  printImMsgContent_n(  NULL,  NULL,  (  IM_CONTENTU  *  )pMem->buf,  pMem->lenInBytes,  tBuf,  mycountof(  tBuf  )  );
							 #endif
							 }
						 else  
							 snprintContent(  NULL,  (  IM_CONTENTU  *  )pMem->buf,  tBuf,  mycountof(  tBuf  )  );
						 //
						 OutputDebugString(  _T(  "  "  )  );  OutputDebugString(  tBuf  );  OutputDebugString(  _T(  "\n"  )  );
						 tBuf[0]  =  0;
					}
				    break;
			  default:
					 break;

	  }
	  OutputDebugString(  tBuf  );  OutputDebugString(  _T(  "\n"  )  );

#endif

	  return  0;
}


 int  printQ_mis(  void  *  pQParam,  BOOL  bNetworkData  )		//  是否网络数据
{
	GENERIC_Q  *  pQ  =  (  GENERIC_Q  *  )pQParam;
	if  (  !pQ  )  return  -1;

#ifdef  __DEBUG__
		
		return  0;

	 traceLogA(  (char*)  "printQ_mc %S starts, %d qNodes",  pQ->cfg.name,  pQ->uiQNodes  );
	 qTraverse(  pQ,  (  PF_commonHandler  )printMisMsg,  (  void  *  )bNetworkData,  0  );
	 traceLogA(  (char*)  "printQ_mc ends"  );
#endif

	 return  0;
}

//  #define		__PRINT_imObj__
 //  2014/02/06
 int  printRetrieveImGrpListResp(  RETRIEVE_IMGRPLIST_RESP  *  pResp  )
 {
#ifdef  __DEBUG__

	 #ifdef  __PRINT_imObj__
	 int  i;
	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "isClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "printRetrieveImGrpListResp: enters, usCnt is %d"  ),  pResp->usCnt  );

	 for  (  i  =  0;  i  <  pResp->usCnt;  i ++  )  {
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "isClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "grp (%I64u)"  ),  pResp->mems[i].idInfo.ui64Id  );
	 }
	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (""),  _T( "isClient"  ),  0,  _T(  ""),  _T(  "" ),  _T(  "printRetrieveImGrpListResp:leaves"  )  );
	 #endif

#endif

	 return  0;
 }


  int  printRetrieveImGrpMemListResp(  RETRIEVE_IMGRPMEMLIST_RESP  *  pResp  )
 {

#ifdef  __DEBUG__
	 #ifdef  __PRINT_imObj__
	 int	i;

	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "isClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "printRetrieveImGrpMemListResp: enters, usCnt is %d"  ),  pResp->usCnt  );

	 for  (  i  =  0;  i  <  pResp->usCnt;  i  ++  )  {
		  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "isClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "grp ( %I64u ), mem ( %I64u )"  ),  pResp->mems[i].idInfo_grp.ui64Id,  pResp->mems[i].idInfo_mem.ui64Id  );
	 }

	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (""),  _T( "isClient"  ),  0,  _T(  ""),  _T(  "" ),  _T(  "printRetrieveImGrpMemListResp: leaves"  )  );
	 #endif
#endif


	 return  0;
 }

 int  printRetrieveContactListResp(  RETRIEVE_CONTACTLIST_RESP  *  p  )
{
#ifdef  __DEBUG__
#ifdef  __PRINT_imObj__
	 int	i;
	 TCHAR	tBuf[1024]	=	_T(  ""  );
	 char	idStr[128]  =  "";
	 char	lastModifiedTime_regInfo[128]  =  "";

	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "isClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "printRetrieveContactListResp: enters, usCnt is %d"  ),  p->usCnt  );
	 for  (  i  =  0;  i  <  p->usCnt;  i  ++  )  {
		  tBuf[0]  =  0;
		  idInfo2Str(  &p->mems[i].addr.idInfo,  idStr,  mycountof(  idStr  )  );
		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "第%d条, %S: %S"  ),  i,  idStr,  lastModifiedTime_regInfo  );
		  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "isClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );
	 }
	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (""),  _T( "isClient"  ),  0,  _T(  ""),  _T(  "" ),  _T(  "printRetrieveContactListResp: leaves"  )  );
#endif

#endif
	 return  0;
}


 int  printRefreshRecentFriendsReq(  REFRESH_RECENTFRIENDS_REQ_h  *  p  )
{
	return  0;

#ifdef  __DEBUG__

	char	timeBuf[128]	=	"";
	int		i;
	
	traceLogA(  (char*)  "start to print RefreshRecentFriendsReq"  );

	traceLogA(  (char*)  "\tuiType is %d, tLast is %I64u, usCnt is %d",  p->uiType,  p->tLastRefreshedTime_misServ,  p->usCnt  );
	for  (  i  =  0;  i  <  p->usCnt;  i  ++  )  {
		 getTimeStr(  (  time_t  )p->mems[i].tLastRefreshedTime_misServ,  timeBuf,  mycountof(  timeBuf  )  );
		 traceLogA(  (char*)  "\tidInfo is %I64u, tLastRefreshedTime_misServ is %d",  p->mems[i].idInfo.ui64Id,  timeBuf  );
	}

	traceLogA(  (char*)  "end printing RefreshRecentFriendsReq"  );

#endif
	return  0;
}

 //
 int  printRefreshRecentFriendsResp(  REFRESH_RECENTFRIENDS_RESP_h  *  p,  LPCTSTR  hint  )
{
	//return  0;

#ifdef  __DEBUG__

	 if (0) {
		 if (!hint)hint = _T("");
		 TCHAR  tBuf[128];

		 char	timeBuf[128] = "";
		 int		i;

		 _sntprintf(tBuf, mycountof(tBuf), _T("start to print RefreshRecentFriendsResp, %s"), hint);
		 traceLog(tBuf);

		 traceLogA((char*)"t is %s, usCnt is %d", timeBuf, p->usCnt);
		 for (i = 0; i < p->usCnt; i++) {
			 //
			 traceLogA((char*)"idInfo is %I64u, usStatus is %S", p->mems[i].idInfo.ui64Id, qyGetDesByType1(CONST_usRunningStatusTable_en, p->mems[i].usRunningStatus));
		 }

		 traceLogA((char*)"end printing RefreshRecentFriendsResp");
	 }
#endif
	return  0;
}



//////////////////////

