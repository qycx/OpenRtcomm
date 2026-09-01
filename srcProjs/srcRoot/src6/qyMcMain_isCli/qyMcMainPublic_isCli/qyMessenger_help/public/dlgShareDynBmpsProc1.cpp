

#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>


#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

#include	<dbt.h>
#include	<mmreg.h>
#include	<msacm.h>
#ifndef  __WINCE__
	#include	<fcntl.h>
	#include	<io.h>
#endif
#include	<stdio.h>
#include	<commdlg.h>
#include	<strsafe.h>

#include	<dshow.h>

#ifndef  __WINCE__
#pragma include_alias( "dxtrans.h", "myqedit.h" )
#define __IDxtCompositor_INTERFACE_DEFINED__
#define __IDxtAlphaSetter_INTERFACE_DEFINED__
#define __IDxtJpeg_INTERFACE_DEFINED__
#define __IDxtKey_INTERFACE_DEFINED__

	//  #include	<Qedit.h>
	#include	"myQedit.h"
#endif
#include	<Mediaobj.h>
#include	<Dmo.h>

#include	"qmcDmoPublic.h"
#ifndef  __WINCE__
	#include	"qmcVideoCapture_dx.h"
#endif
#include	"myfourcc.h"

#include	"qyCusResTemp.h"

//  #include	"qyMc.h"
#include	"qyGuiCommProc.h"

#include	"tmpCeLib.h"

#include	"qyAvRecordPublic.h"

//#include	"myresource.h"

#include	"qyOpenShellCommon.h"
#include	"wallTalkers.h"
#include	"DlgShareDynBmpsProc.h"

#include	"dlgTalkProc.h"
#include	"qmcCmdProc.h"

//  #include	"DlgProgress.h"
#include	"tmpCeLib.h"

#include	"qyComPortEx.h"
#include	"qmcGpsProc.h"

#include	"myDb.h"

#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"qmcCommFunc_isCli.h"


//
BOOL  isSame_onvifRule(Onvif_rule* p1, Onvif_rule* p2)
{
	//
	if (p1->usIndex_obj == p2->usIndex_obj
		&& p1->iOnvifRuleType == p2->iOnvifRuleType
		&& !_strcmpi(p1->url, p2->url)
		&& !_tcsicmp(p1->cusName, p2->cusName)
		&& !_strcmpi(p1->usrName, p2->usrName)
		&& !_strcmpi(p1->passwd, p2->passwd)
		&& !_strcmpi(p1->defToken, p2->defToken)
		)
	{
		return  TRUE;
	}

	//
	return  FALSE;
}

//
BOOL  isSame_ipDev(IP_dev* p1, IP_dev* p2)
{
	//
	if (p1->iType == p2->iType
		&& !_strcmpi(p1->ip, p2->ip)
		&& !_strcmpi(p1->urls[0].token, p2->urls[0].token)
		&& !_strcmpi(p1->urls[0].rtspUrl.url, p2->urls[0].rtspUrl.url)
		&& !_strcmpi(p1->urls[1].token, p2->urls[1].token)
		&& !_strcmpi(p1->urls[1].rtspUrl.url, p2->urls[1].rtspUrl.url)
		&& !_strcmpi(p1->urls[2].token, p2->urls[2].token)
		&& !_strcmpi(p1->urls[2].rtspUrl.url, p2->urls[2].rtspUrl.url)
		&& p1->ucCnt_urls == p2->ucCnt_urls
		&& !_strcmpi(p1->deviceServiceAddr, p2->deviceServiceAddr)
		)
	{
		return  TRUE;
	}

	//
	return  FALSE;
}


__declspec(  dllexport  )  int  storeRecvdReq(  HWND  m_hWnd,  DLG_shareDynBmps_var  *  pVar,  MIS_MSGU  *  pMsg,  unsigned  char  ucbSaveVideo_reply,  int  *piIndex_store  )
 {
	 int						iErr	=	-1;

	 DLG_shareDynBmps_var  &  m_var  =  *pVar;
	 
	 int  j;
	 
	 DWORD  dwTickCnt_cur;  dwTickCnt_cur	=	GetTickCount(  );	
	 IM_CONTENTU			*	pContent	=	NULL;


	 if  (  pMsg->uiType  ==  CONST_misMsgType_input  )  {
		 pContent  =  M_getMsgContent(  pMsg->input.ucFlg,  &pMsg->input.data  );									 
		 }
	 else  if  (  pMsg->uiType  ==  CONST_misMsgType_task  )  {
			   pContent  =  M_getMsgContent(  pMsg->task.ucFlg,  &pMsg->task.data  );									 
			   }
	 else  {
			#ifdef  __DEBUG__
					traceLog((TCHAR*)  _T(  "storeRecvdReq failed: msg.type %d err"  ),  pMsg->uiType  );
			#endif
		   goto  errLabel;
	 }



	 //  先找早的请求
	 for  (  j  =  0;  j  <  mycountof(  m_var.recvdReqs  );  j  ++  )  {
		  //
		  if  (  !m_var.recvdReqs[j].dwTickCnt  )  continue;
		  //
		  if  (  dwTickCnt_cur  -  m_var.recvdReqs[j].dwTickCnt  >  5000  )  {
			  m_var.recvdReqs[j].dwTickCnt  =  0;		//  将dwTickCnt设为0，表明该buf已经回收了
			  //
			  #ifdef  __DEBUG__
					  showInfo_open0(  0,  0,  _T(  "storeRecvdReq: set dwTickCnt to 0"  )  );
			  #endif
			  //
			  continue;
		  }	
		  //
		  if  (  m_var.recvdReqs[j].pMsg->uiType  !=  pMsg->uiType  )  continue;									 			
		  //
		  if  (  m_var.recvdReqs[j].info.uiContentType  !=  pContent->uiType  )  continue;

		  //  2014/09/12
		  switch  (  pContent->uiType  )  {
				  case  CONST_imCommType_transferAvInfo:
					    //  
						#if  0
							 if  (  m_var.recvdReqs[j].info.resObj.uiObjType  !=  pContent->transferAvInfo.viewDynBmp.resObj.uiObjType  )  continue;
							 if  (  m_var.recvdReqs[j].info.resObj.usIndex_obj  !=  pContent->transferAvInfo.viewDynBmp.resObj.usIndex_obj  )  continue;
						#endif
						//  2016/07/24
						if  (  !isSame_resObj(  &m_var.recvdReqs[j].info.resObj,  &pContent->transferAvInfo.ass.resObj  )  )  continue;
						//
					    break;
				  case  CONST_imCommType_retrieveDynBmps:  //  2016/08/16
					    //
					    if  (  m_var.recvdReqs[j].info.resObj.uiObjType  !=  pContent->retrieveDynBmps.u.req.uiObjType  )  continue;
						//
					    break;

				  default:
						 break;
		  }

		  //
		  if  (  pMsg->uiType  ==  CONST_misMsgType_input  )  {
		
			  //
			  if  (  m_var.recvdReqs[j].pMsg->input.data.route.idInfo_from.ui64Id  ==  pMsg->input.data.route.idInfo_from.ui64Id  )  {
				  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "recv req again"  )  );
						  showInfo_open0(  0,  0,  _T(  "storeRecvdReq: recv msgInput req again."  )  );
				  #endif
				  break;				
			  }					
		  }
		  if  (  pMsg->uiType  ==  CONST_misMsgType_task  )  {
			  //
			  if  (  m_var.recvdReqs[j].pMsg->task.data.route.idInfo_from.ui64Id  ==  pMsg->task.data.route.idInfo_from.ui64Id  )  {
				  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "recv req again"  )  );
						  showInfo_open0(  0,  0,  _T(  "storeRecvdReq: recv msgTask req again."  )  );
				  #endif
				  break;				
			  }					
		  }
	 }
	 //  如果没找到，再找新的
	 if  (  j  ==  mycountof(  m_var.recvdReqs  )  )  {
		 for  (  j  =  0;  j  <  mycountof(  m_var.recvdReqs  );  j  ++  )  {
			  if  (  !m_var.recvdReqs[j].dwTickCnt  )  break;
			  //
			  if  (  dwTickCnt_cur  -  m_var.recvdReqs[j].dwTickCnt  >  5000  )  {				
				  m_var.recvdReqs[j].dwTickCnt  =  0;		//  将dwTickCnt设为0，表明该buf已经回收了
				  break;									 
			  }
		 } 
	 }			
	 if  (  j  ==  mycountof(  m_var.recvdReqs  )  )  {
		 #ifdef  __DEBUG__
				 traceLog((TCHAR*)  _T(  "no recvdReqBuf available"  )  );
		 #endif
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp: warning: no recvdReqBuf available"  )  );		
		 goto  errLabel;								
	 }						
	 if  (  !m_var.recvdReqs[j].dwTickCnt  )  {		//  只有dwTickCnt为0的包才表明是要填充的		
		 memcpy(  m_var.recvdReqs[j].pMsg,  pMsg,  sizeof(  pMsg[0]  )  );
		 memset(  &m_var.recvdReqs[j].info,  0,  sizeof(  m_var.recvdReqs[j].info  )  );
		 //  2014/09/11
		 m_var.recvdReqs[j].info.uiTranNo_storeRecvdReq  =  getuiNextTranNo(  0,  0,  0  );
		 //
		 m_var.recvdReqs[j].info.uiContentType  =  pContent->uiType;
		 //
		 switch  (  pContent->uiType  )  {
				 case  CONST_imCommType_transferAvInfo:  {
					   //
					   #if  0
							m_var.recvdReqs[j].info.resObj.uiObjType  =  pContent->transferAvInfo.viewDynBmp.resObj.uiObjType;			
							m_var.recvdReqs[j].info.resObj.usIndex_obj  =  pContent->transferAvInfo.viewDynBmp.resObj.usIndex_obj;
					   #endif
					   //  2016/07/24						
					   m_var.recvdReqs[j].info.resObj  =  pContent->transferAvInfo.ass.resObj;			
					   //
					   //m_var.recvdReqs[j].info.index_pShare_mem  =  index_pShare_mem;				 
					   //  2014/09/07
					   m_var.recvdReqs[j].info.ucbSaveVideo_reply  =  ucbSaveVideo_reply;
					   }
					   break;
				 case  CONST_imCommType_retrieveDynBmps:  //  2014/09/04
					   m_var.recvdReqs[j].info.resObj.uiObjType  =  pContent->retrieveDynBmps.u.req.uiObjType;
					   m_var.recvdReqs[j].info.ucbRetrieveOne  =  pContent->retrieveDynBmps.u.req.ucbRetrieveOne;
					   //  2017/06/11
					   m_var.recvdReqs[j].info.ucbAvConsole  =  pContent->retrieveDynBmps.ucbAvConsole;
					   break;
				 default:
					 break;
		 }
		 //
		 m_var.recvdReqs[j].dwTickCnt  =  dwTickCnt_cur;								
	 }


	 if  (  piIndex_store  )  *piIndex_store  =  j;

	 iErr  =  0;
errLabel:
	 return  iErr;

 }



 //  2014/09/11
 __declspec(  dllexport  )  int  noStoreRecvdReq(  HWND  m_hWnd,  DLG_shareDynBmps_var  *  pVar,  int  iIndex_store  )
 {
	 if  (  iIndex_store  <  0  ||  iIndex_store  >=  mycountof(  pVar->recvdReqs  )  )  return  -1;

	 pVar->recvdReqs[iIndex_store].dwTickCnt  =  0;

	 return  0;
 }


 //
 __declspec(  dllexport  )  BOOL  canPeerSaveVideo(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  QY_MESSENGER_ID  *  pIdInfo_peer  )
{
	BOOL	bRet  =  FALSE;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	if  (  !pDLG_shareDynBmps_var  )  return  FALSE;
	DLG_shareDynBmps_var  &  m_var  =  *(  DLG_shareDynBmps_var  *  )pDLG_shareDynBmps_var;

	if  (  !pIdInfo_peer  ||  !pIdInfo_peer->ui64Id  )  return  FALSE;

	int  i;
	for  (  i  =  0;  i  <  mycountof(  m_var.saveVideo.cfg.idInfos_allowed  );  i  ++  )  {
		if  (  pIdInfo_peer->ui64Id  ==  m_var.saveVideo.cfg.idInfos_allowed[i].ui64Id  )  break;
	}
	if  (  i  ==  mycountof(  m_var.saveVideo.cfg.idInfos_allowed  )  )  goto  errLabel;


	bRet  =  TRUE;
errLabel:

#if  0	//  def  __DEBUG__
		showNotification(  0,  0,  0,  0,  0,  0,  _T(  "For test: canPeerSaveVideo true"  )  );
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "for test: canPeerSaveVideo returns TRUE"  )  );										  
		bRet  =  TRUE;
#endif

	//
	TCHAR  tBuf[128]  =  _T(  ""  );
	if  (  bRet  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Permitted: %I64u saves video"  ),  pIdInfo_peer->ui64Id  );
	else  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Denied: %I64u can't save video"  ),  pIdInfo_peer->ui64Id  );
	//
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  "canPeerSaveVideo: "  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );		
	//
	showNotification(  0,  0,  0,  0,  0,  0,  tBuf  );
	
	return  bRet;
}


 //
#if  0  //  2016/06/27
  int  iidlgShareDynBmps_sndRetrieveDynBmpsRespToMsgr(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  int  index_recvdReqs  )
{
	int		iErr	=	-1;
	DLG_shareDynBmps_var  &  m_var  =  *(  DLG_shareDynBmps_var  *  )pDLG_shareDynBmps_var;
	
	if  (  index_recvdReqs  <  0  ||  index_recvdReqs  >=  mycountof(  m_var.recvdReqs  )  )  return  -1;
	DLG_shareDynBmp_recvdReq  *  pRecvdReq  =  &m_var.recvdReqs[index_recvdReqs];	//  2014/09/04
	QY_MESSENGER_ID  *  pIdInfo_dst  =  &m_var.recvdReqs[index_recvdReqs].pMsg->input.data.route.idInfo_from;

	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return  -1;
	
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli			*	pProcInfo	=	QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	RETRIEVE_DYN_BMPS		resp;
	MACRO_prepareForTran(  );
	int						len;
	int						i,  j;

	QY_DMITEM	*	pTable				=					getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );


	if  (  !bMeOnline(  (  QY_MC  *  )pProcInfo->pQyMc  )  )  return  -1;

	memset(  &resp,  0,  sizeof(  resp  )  );
	resp.uiType  =  CONST_imCommType_retrieveDynBmps;
	resp.ucbResp  =  TRUE;
	//
	if  (  pRecvdReq->info.ucbRetrieveOne  )  {
		if  (  !pRecvdReq->info.uiObjType  )  goto  errLabel;
		unsigned  int  uiObjType  =  pRecvdReq->info.uiObjType;
		SHARE_dynBmps  *  pShare  =  (  SHARE_dynBmps  *  )dlgShareDynBmps_getShareDynBmpsBySth(  m_hWnd,  &m_var,  pRecvdReq->info.uiObjType  );
		if  (  !pShare  )  goto  errLabel;
		//
		if  (  uiObjType  ==  CONST_objType_rtspStream  )  {
			//
			for  (  j  =  0;  j  <  mycountof(  m_var.onvif.urls  );  j  ++  )  {
				if  (  !m_var.onvif.urls[j].index_obj  )  continue;
			   //
			   if  (  resp.usCnt  >=  mycountof(  resp.mems  )  )  break;		 
			   //
			   resp.mems[resp.usCnt].uiObjType  =  CONST_objType_rtspStream;
			   resp.mems[resp.usCnt].usIndex_obj  =  m_var.onvif.urls[j].index_obj;
			   resp.usCnt  ++  ;	
			   //  only one needed
			   break;
			}

			}
		else  {
			  //
			  for  (  i  =  0;  i  <  pShare->usCnt  &&  resp.usCnt  <  mycountof(  resp.mems  );  i  ++  )  {
				   CHelp_shareDynBmp  help_dynBmpMem;
				   SHARE_dyn_bmp  *  pDynBmpMem  =  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  i  );
				   if  (  !pDynBmpMem  )  continue;
				   
				   if  (  !bShared(  pDynBmpMem  )  )  continue;		
				   //		
				   resp.mems[resp.usCnt].uiObjType  =  uiObjType;
				   resp.mems[resp.usCnt].usIndex_obj  =  pDynBmpMem->usIndex_obj;
				   resp.usCnt  ++  ;
				   //  only one needed
				   break;		
			  }
		}
		//
		if  (  !resp.usCnt  )  {
			#ifdef  __DEBUG__
					traceLog((TCHAR*)  _T(  "retrieveOne failed. no sharedObj"  )  );
			#endif
			//
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "retrieveOne failed, no %s shared"  ),  qyGetDesByType1(  pTable,  uiObjType  )  );		
			goto  errLabel;
		}

		#ifdef  __DEBUG__
				int  ii;
				ii  =  1;
		#endif
		//
		}

	else  {
		  for  (  j  =  0;  j  <  mycountof(  m_var.shares  );  j  ++  )  {			
			   SHARE_dynBmps	*	pShare		=	&m_var.shares[j];
			   //
			   //if  (  uiObjType  ==  CONST_objType_rtspStream  )  continue;
			   //
			   for  (  i  =  0;  i  <  pShare->usCnt  &&  resp.usCnt  <  mycountof(  resp.mems  );  i  ++  )  {
				    //CHelp_shareDynBmp  help_dynBmpMem;
					SHARE_dyn_bmp  *  pDynBmpMem  =  &pShare->mems_internal[i];	//  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  pShare->uiObjType,  i  );
					if  (  !pDynBmpMem  )  continue;
					//
					if  (  pDynBmpMem->uiObjType  ==  CONST_objType_rtspStream  )  continue;
					//
				    if  (  !bShared(  pDynBmpMem  )  )  continue;
					resp.mems[resp.usCnt].uiObjType  =  pDynBmpMem->uiObjType;	//  pShare->uiObjType;
					//  resp.mems[resp.usCnt].usIndex_obj  =  i;
					resp.mems[resp.usCnt].usIndex_obj  =  pDynBmpMem->usIndex_obj;		//  2014/05/31
					lstrcpyn(  resp.mems[resp.usCnt].name,  pDynBmpMem->name,  mycountof(  resp.mems[resp.usCnt].name  )  );
					lstrcpyn(  resp.mems[resp.usCnt].cusName,  pDynBmpMem->cusName,  mycountof(  resp.mems[resp.usCnt].cusName  )  );
					resp.usCnt  ++  ;		 		 		 
			   }	
		  }
		  //
		  for  (  j  =  0;  j  <  mycountof(  m_var.onvif.urls  );  j  ++  )  {
			  if  (  !m_var.onvif.urls[j].index_obj  )  continue;
			   //
			   if  (  resp.usCnt  >=  mycountof(  resp.mems  )  )  break;		 
			   //
			   resp.mems[resp.usCnt].uiObjType  =  CONST_objType_rtspStream;
			   resp.mems[resp.usCnt].usIndex_obj  =  m_var.onvif.urls[j].index_obj;
			   safeTcsnCpy(  m_var.onvif.urls[j].cusName,  resp.mems[resp.usCnt].cusName,  mycountof(  resp.mems[resp.usCnt].cusName  )  );
			   resp.usCnt  ++  ;	
		  }
	}
	//
	unsigned  char  ucFlg  =  CONST_commFlg_resp;
	unsigned  short  usCode  =  CONST_qyRc_ok;
	tStartTran  =  m_var.recvdReqs[index_recvdReqs].pMsg->input.tStartTime;
	uiTranNo  =  m_var.recvdReqs[index_recvdReqs].pMsg->input.uiTranNo;
	//
	len  =  offsetof(  RETRIEVE_DYN_BMPS,  mems  )  +  resp.usCnt  *  sizeof(  resp.mems[0]  );
	//
	pFuncs->pf_postMsg2Mgr_mc(  m_var.pMisCnt,  NULL,  CONST_misMsgType_task,  ucFlg,   usCode,  tStartTran,  uiTranNo,  0,  (  char  *  )&resp,  len,  NULL,  pIdInfo_dst,  0,  NULL,  0  ); 

	//  2014/06/04
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp: sendRetrieveDynBmpsResp to %I64u, cnt %d"  ),  pIdInfo_dst->ui64Id,  (  int  )resp.usCnt  );		


	iErr  =  0;
errLabel:
	

	return  iErr;
}
#endif


 //  2016/06/27
  int  dlgShareDynBmps_sndRetrieveDynBmpsRespToMsgr(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  int  index_recvdReqs  )
{
	int		iErr	=	-1;
	DLG_shareDynBmps_var  &  m_var  =  *(  DLG_shareDynBmps_var  *  )pDLG_shareDynBmps_var;
	
	if  (  index_recvdReqs  <  0  ||  index_recvdReqs  >=  mycountof(  m_var.recvdReqs  )  )  return  -1;
	DLG_shareDynBmp_recvdReq  *  pRecvdReq  =  &m_var.recvdReqs[index_recvdReqs];	//  2014/09/04
	QY_MESSENGER_ID  *  pIdInfo_dst  =  &m_var.recvdReqs[index_recvdReqs].pMsg->input.data.route.idInfo_from;

	MC_VAR_isCli			*	pProcInfo	=	QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	RETRIEVE_DYN_BMPS		resp;
	MACRO_prepareForTran(  );
	int						len;
	int						i,  j;

	QY_DMITEM	*	pTable				=					getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );


	if  (  !bMeOnline(  (  QY_MC  *  )pProcInfo->pQyMc  )  )  return  -1;

	memset(  &resp,  0,  sizeof(  resp  )  );
	resp.uiType  =  CONST_imCommType_retrieveDynBmps;
	resp.ucbResp  =  TRUE;
	//
	if  (  pRecvdReq->info.ucbRetrieveOne  )  {
		if  (  !pRecvdReq->info.resObj.uiObjType  )  goto  errLabel;
		unsigned  int  uiObjType  =  pRecvdReq->info.resObj.uiObjType;
		//
#if  10
		if  (  uiObjType  ==  CONST_objType_smallStream  )  {
			resp.mems[resp.usCnt].qisResObj.resObj.uiObjType  =  uiObjType;
			resp.mems[resp.usCnt].qisResObj.resObj.usIndex_obj  =  CONST_usIndex_avStream_slave;
			resp.usCnt  ++  ;	
			}
		else 
#endif
		{
		//
		SHARE_dynBmps  *  pShare  =  (  SHARE_dynBmps  *  )dlgShareDynBmps_getShareDynBmpsBySth(  m_hWnd,  &m_var,  pRecvdReq->info.resObj.uiObjType  );
		if  (  !pShare  )  goto  errLabel;
		//
		if  (  uiObjType  ==  CONST_objType_rtspStream  )  {
			//
			for  (  j  =  0;  j  <  mycountof(  m_var.onvif.ipDevsInfo.mems  );  j  ++  )  {
				if  (  !m_var.onvif.ipDevsInfo.mems[j].rule.usIndex_obj  )  continue;
			   //
			   if  (  resp.usCnt  >=  mycountof(  resp.mems  )  )  break;		 
			   //
			   resp.mems[resp.usCnt].qisResObj.resObj.uiObjType  =  CONST_objType_rtspStream;
			   resp.mems[resp.usCnt].qisResObj.resObj.usIndex_obj  =  m_var.onvif.ipDevsInfo.mems[j].rule.usIndex_obj;
			   resp.usCnt  ++  ;	
			   //  only one needed
			   break;
			}

			}
		else  {
			  //
			  for  (  i  =  0;  i  <  pShare->usCnt  &&  resp.usCnt  <  mycountof(  resp.mems  );  i  ++  )  {
				   CHelp_shareDynBmp  help_dynBmpMem;
				   SHARE_dyn_bmp  *  pDynBmpMem  =  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  i  );
				   if  (  !pDynBmpMem  )  continue;
				   
				   if  (  !bShared(  pDynBmpMem  )  )  continue;		
				   //		
				   resp.mems[resp.usCnt].qisResObj.resObj.uiObjType  =  uiObjType;
				   resp.mems[resp.usCnt].qisResObj.resObj.usIndex_obj  =  pDynBmpMem->resObj.usIndex_obj;
				   resp.usCnt  ++  ;
				   //  only one needed
				   break;		
			  }
		}
		//
		}
		//
		if  (  !resp.usCnt  )  {
			#ifdef  __DEBUG__
					traceLog((TCHAR*)  _T(  "retrieveOne failed. no sharedObj"  )  );
			#endif
			//
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "retrieveOne failed, no %s shared"  ),  qyGetDesByType1(  pTable,  uiObjType  )  );		
			goto  errLabel;
		}

		#ifdef  __DEBUG__
				int  ii;
				ii  =  1;
		#endif
		//
		}

	else  {
		  for  (  j  =  0;  j  <  mycountof(  m_var.shares  );  j  ++  )  {			
			   SHARE_dynBmps	*	pShare		=	&m_var.shares[j];
			   //
			   //if  (  uiObjType  ==  CONST_objType_rtspStream  )  continue;
			   //
			   for  (  i  =  0;  i  <  pShare->usCnt  &&  resp.usCnt  <  mycountof(  resp.mems  );  i  ++  )  {
				    //CHelp_shareDynBmp  help_dynBmpMem;
					SHARE_dyn_bmp  *  pDynBmpMem  =  &pShare->mems_internal[i];	//  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  pShare->uiObjType,  i  );
					if  (  !pDynBmpMem  )  continue;
					//
					if  (  pDynBmpMem->resObj.uiObjType  ==  CONST_objType_rtspStream  )  continue;
					//
				    if  (  !bShared(  pDynBmpMem  )  )  continue;
					resp.mems[resp.usCnt].qisResObj.resObj.uiObjType  =  pDynBmpMem->resObj.uiObjType;	//  pShare->uiObjType;
					//  resp.mems[resp.usCnt].usIndex_obj  =  i;
					resp.mems[resp.usCnt].qisResObj.resObj.usIndex_obj  =  pDynBmpMem->resObj.usIndex_obj;		//  2014/05/31
					lstrcpyn(  resp.mems[resp.usCnt].name,  pDynBmpMem->name,  mycountof(  resp.mems[resp.usCnt].name  )  );
					lstrcpyn(  resp.mems[resp.usCnt].cusName,  pDynBmpMem->cusName,  mycountof(  resp.mems[resp.usCnt].cusName  )  );
					//  2017/06/12
					resp.mems[resp.usCnt].usW  =  pDynBmpMem->usW;
					resp.mems[resp.usCnt].usH  =  pDynBmpMem->usH;
					//
					resp.usCnt  ++  ;		 		 		 
			   }	
		  }
		  //
		  for  (  j  =  0;  j  <  mycountof(  m_var.onvif.ipDevsInfo.mems  );  j  ++  )  {
			   IP_dev  *  pMem  =  &m_var.onvif.ipDevsInfo.mems[j];
			   if  (  !pMem->rule.usIndex_obj  )  continue;
			   //
			   if  (  resp.usCnt  >=  mycountof(  resp.mems  )  )  break;		 
			   //
			   resp.mems[resp.usCnt].qisResObj.resObj.uiObjType  =  CONST_objType_rtspStream;
			   resp.mems[resp.usCnt].qisResObj.resObj.usIndex_obj  =  pMem->rule.usIndex_obj;
			   //  2016/07/23
			   resp.mems[resp.usCnt].qisResObj.resObj.usHelp_subIndex  =  pMem->usHelp_subIndex;
			   //
			   safeTcsnCpy(  pMem->rule.cusName,  resp.mems[resp.usCnt].cusName,  mycountof(  resp.mems[resp.usCnt].cusName  )  );
			   resp.usCnt  ++  ;	
		  }
		  //  2017/06/11
		  resp.ucbAvConsole  =  pRecvdReq->info.ucbAvConsole;
	}
	//
	unsigned  char  ucFlg;ucFlg = CONST_commFlg_resp;
	unsigned  short  usCode;usCode = CONST_qyRc_ok;
	tStartTran  =  m_var.recvdReqs[index_recvdReqs].pMsg->input.tStartTime;
	uiTranNo  =  m_var.recvdReqs[index_recvdReqs].pMsg->input.uiTranNo;
	//
	len  =  offsetof(  RETRIEVE_DYN_BMPS,  mems  )  +  resp.usCnt  *  sizeof(  resp.mems[0]  );
	//
	postMsg2Mgr_mc(  m_var.pMisCnt,  NULL,  CONST_misMsgType_task,  ucFlg,   usCode,  tStartTran,  uiTranNo,  0,  (  char  *  )&resp,  len,  NULL,  pIdInfo_dst,  0,  NULL,  0  ); 

	//  2014/06/04
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp: sendRetrieveDynBmpsResp to %I64u, cnt %d"  ),  pIdInfo_dst->ui64Id,  (  int  )resp.usCnt  );		


	iErr  =  0;
errLabel:
	

	return  iErr;
}




//
 //  2014/05/06
 __declspec(  dllexport  )  int  procRetrieveDynBmpsReq(  HWND  m_hWnd,  DLG_shareDynBmps_var  *  pVar,  MIS_MSG_INPUT  *  pMsgInput  )
 {
	 int						iErr		=	-1;
	 QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	 MC_VAR_isCli			*	pProcInfo	=	QY_GET_procInfo_isCli(  );

	 DLG_shareDynBmps_var  &  m_var  =  *pVar;

	 IM_CONTENTU			*	pContent	=	M_getMsgContent(  pMsgInput->ucFlg,  &pMsgInput->data  );									 

	 if  (  pContent->uiType  !=  CONST_imCommType_retrieveDynBmps  )  return  -1;


	 int  index_store  =  0;
	 
	 //
	 unsigned  char  ucbSaveVideo_reply  =  FALSE;
	 if  (  storeRecvdReq(  m_hWnd,  pVar,  (  MIS_MSGU  *  )pMsgInput,  ucbSaveVideo_reply,  &index_store  )  )  goto  errLabel;

	 //
	 MACRO_prepareForTran(  );		
	 VERIFY_viewDynBmp	req;								
	 int					len;
	 							
	 memset(  &req,  0,  sizeof(  req  )  );	
	 req.uiType  =  CONST_imCommType_verifyViewDynBmp;
	 
	 req.idInfo_viewer.ui64Id  =  pMsgInput->data.route.idInfo_from.ui64Id;
	 
	 len  =  sizeof(  req  );	
	 //							
	 postMsg2Mgr_mc(  m_var.pMisCnt,  NULL,  CONST_misMsgType_req,  0,   CONST_qyCmd_sendVDevReq,  tStartTran,  uiTranNo,  0,  (  char  *  )&req,  len,  NULL,  0,  0,  NULL,  0  ); 
	 	
	 //
	 QY_DMITEM* pTable;pTable = getResTable(0, &pQyMc->cusRes, CONST_resId_objTypeTable);
	 TCHAR  tBuf[128];
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "sharedDynBmp: to verifyViewer %I64u. index_store %d. (%s,%d)"  ),  req.idInfo_viewer.ui64Id,  index_store,  
		 qyGetDesByType1(  pTable,  pContent->retrieveDynBmps.u.req.uiObjType  ),  (  int  )pContent->retrieveDynBmps.u.req.usIndex_obj  );
	 //
	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );
	 
	 iErr  =  0;
errLabel:
	 return  iErr;
 }


 //
 __declspec(  dllexport  )  int  procVerifyViewDynBmpResp_step4(  HWND  m_hWnd,  DLG_shareDynBmps_var  *  pVar,  unsigned  int  uiObjType,  int  index_pShare_mem  )
 {
	 int	iErr	=	-1;
	 		 
	 DLG_shareDynBmps_var  &  m_var  =  *pVar;
	 MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	 QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

	 //													 
	 CHelp_shareDynBmp  help_dynBmpMem;
	 SHARE_dyn_bmp  *  pDynBmpMem  =  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  index_pShare_mem  );
	 if  (  !pDynBmpMem  )  goto  errLabel;
		 
	 //if  (  !pShare->mems[i].var.bShared  )  goto  errLabel;										
	 //  if  (  !pDynBmpMem->var.bShared  )  goto  errLabel;
	 if  (  !pDynBmpMem->var.ucbLocalVideoOpen  )  goto  errLabel;
		
	 //
	 int  j;j = pDynBmpMem->var.recvdReq.index_recvdReq;
	 if  (  j  <  0  ||  j  >=  mycountof(  m_var.recvdReqs  )  )  goto  errLabel;
	 DLG_shareDynBmp_recvdReq* pRecvdReq;pRecvdReq = &m_var.recvdReqs[j];
	 if  (  !pRecvdReq->dwTickCnt  )  goto  errLabel;
	 if  (  pDynBmpMem->var.recvdReq.uiTranNo_storeRecvdReq  !=  pRecvdReq->info.uiTranNo_storeRecvdReq  )  goto  errLabel;
	
	 //
	 MIS_MSG_TASK* pMsg;pMsg = &pRecvdReq->pMsg->task;
		
	 if  (  pMsg->uiTaskType  ==  CONST_imTaskType_viewDynBmp  )  {			
					   //  2014/09/04
					   DYN_BMP_rule	dynBmp;
					   memset(  &dynBmp,  0,  sizeof(  dynBmp  )  );
					   dynBmp.dynBmp.resObj.uiObjType  =  uiObjType;
					   dynBmp.dynBmp.resObj.usIndex_obj  =  pDynBmpMem->resObj.usIndex_obj;	//  pShare->mems[i].usIndex_obj;
					   //
					   dynBmp.ucbSaveVideo  =  m_var.recvdReqs[j].info.ucbSaveVideo_reply;
					   //
					   //  2015/10/23
					   TASK_av_props  *  pTaskAvProps  =  &pDynBmpMem->var.taskAvProps;

					   //
					   if  (  uiObjType  ==  CONST_objType_smallStream  )  {
						   //
						   int  iIndex_sharedObj_localAv  =  getSharedObjIndex_localAv(  );
						   if  (  confMem_procReq_transferAvInfo(  NULL,  iIndex_sharedObj_localAv,  (  MIS_MSGU  *  )pMsg  )  )  goto  errLabel;
						   }
					   else  {
						     //					   
						   if  (  procSendAvReplyInfo(  (  MIS_CNT  *  )pMsg->pMisCnt,  m_hWnd,  pMsg,  TRUE,  pDynBmpMem->var.iIndex_sharedObj,  pDynBmpMem->var.iTaskId,  &dynBmp,  pTaskAvProps,  &pMsg->addr_logicalPeer  )  )  goto  errLabel;									 
					   }
					
		}		
	 else  {
						 #ifdef  __DEBUG__
								 traceLog((TCHAR*)  _T(  "dlgShare: unknown recvd taskType"  )  );
						 #endif					
						 goto  errLabel;								 
		
	 }											 			   
	

	 //
	 QY_DMITEM* pTable;pTable = getResTable(0, &pQyMc->cusRes, CONST_resId_objTypeTable);
	 TCHAR  tBuf[128];
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "sharedDynBmp: avReply to %I64u, index_pShare_mem %d"  ),  pMsg->addr_logicalPeer.idInfo.ui64Id,  index_pShare_mem  );		
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. for req(%s, %d)"  ),  tBuf,  qyGetDesByType1(  pTable,  uiObjType  ),  (  int  )pDynBmpMem->resObj.usIndex_obj  );

	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );		
	 		
	 iErr  =  0;

errLabel:
	
	 return  iErr;

 }


 //
   //  2014/09/12
#if  0
   int  iiprocVerifyViewDynBmpResp_perReq(  HWND  m_hWnd,  DLG_shareDynBmps_var  *  pVar,  MIS_MSG_INPUT  *  pMsgInput,  int  index_store  )
 {
	 int						iErr	=	-1;

	 MC_VAR_isCli			*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	 FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );
	 if  (  !pFuncs  )  return  -1;

	 //
	 DLG_shareDynBmps_var  &  m_var  =  *pVar;

	 IM_CONTENTU			*	pContent	=	M_getMsgContent(  pMsgInput->ucFlg,  &pMsgInput->data  );									 
	 int  i  =  0;

	 if  (  pContent->uiType  !=  CONST_imCommType_verifyViewDynBmp  )  return  -1;

	 //
	 if  (  index_store  <  0  ||  index_store  >=  mycountof(  m_var.recvdReqs  )  )  return  -1;
	 DLG_shareDynBmp_recvdReq  *  pRecvdReq  =  &m_var.recvdReqs[index_store];

	 //	
	 if  (  !pRecvdReq->dwTickCnt  )  {		//  not a stored req
		 return  0;
	 }

	 #ifdef  __DEBUG__
			 traceLog((TCHAR*)  _T(  "verifyViewDynBmp resp per Req %d"  ),  index_store  );
	 #endif

		  //
		  BOOL  bMatched  =  FALSE;
		  //
		  if  (  pRecvdReq->info.uiContentType  ==  CONST_imCommType_retrieveDynBmps  )  {			
			  if  (  pRecvdReq->pMsg->uiType  !=  CONST_misMsgType_input  )  goto  errLabel;
			  if  (  pRecvdReq->pMsg->input.data.route.idInfo_from.ui64Id  ==  pContent->verifyViewDynBmp.idInfo_viewer.ui64Id  )  {
				  bMatched  =  TRUE;
			  }			  
			  }
		  else  {
			    if  (  pRecvdReq->pMsg->uiType  !=  CONST_misMsgType_task  )  goto  errLabel;
				//					  
				if  (  pRecvdReq->pMsg->task.addr_logicalPeer.idInfo.ui64Id  ==  pContent->verifyViewDynBmp.idInfo_viewer.ui64Id  )  {
					bMatched  =  TRUE;
				}
		  }

		  //
		  if  (  !bMatched  )  goto  errLabel;
	 
		  //																	
		  if  (  !isRuleCmdPermit(  pContent->verifyViewDynBmp.uiCmd  )  )  {
		 
			  noStoreRecvdReq(  m_hWnd,  &m_var,  index_store  );
			  //  m_var.recvdReqs[j].dwTickCnt  =  0;		//  这里要记得清除		 		

			  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp: viewer %I64u, access denied"  ),  pContent->verifyViewDynBmp.idInfo_viewer.ui64Id  );		
			  goto  errLabel;
		  }
		 
		  //	
		  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp: viewer %I64u, accepted. "  ),  pContent->verifyViewDynBmp.idInfo_viewer.ui64Id  );		
	 
		  //	 
		  if  (  pRecvdReq->info.uiContentType  ==  CONST_imCommType_retrieveDynBmps  )  {
			  //  2014/05/06
			  
			  dlgShareDynBmps_sndRetrieveDynBmpsRespToMsgr(  m_hWnd,  pVar,  index_store  );
			  
			  //  2014/09/11
			  noStoreRecvdReq(  m_hWnd,  pVar,  index_store  );
			  iErr  =  0;  goto  errLabel;

			  }
		  else  if  (  pRecvdReq->info.uiObjType  )  {	
			   //
			   SHARE_dynBmps	*	pShare;
			   unsigned  int  uiObjType  =  pRecvdReq->info.uiObjType;	//  2014/11/01
			   pShare  =  (  SHARE_dynBmps  *  )dlgShareDynBmps_getShareDynBmpsBySth(  m_hWnd,  &m_var,  pRecvdReq->info.uiObjType  );
			   if  (  !pShare  )  goto  errLabel;							    
		 
			   //		 
			   if  (  pRecvdReq->info.uiObjType  ==  CONST_objType_rtspStream  )  {
				   
				   if  (  !pRecvdReq->info.usIndex_obj  )  {				   
					   //  2014/09/09. 不再支持用0来直接匹配流，所以这里就直接出错了
					   showNotification(  0,  0,  0,  0,  0,  0,  _T(  "Not supported: use 0 to retrieve active stream"  )  );
					   goto  errLabel;			 
			 
				   }			 
				   
				   //
				 int  ii;
				 for  (  ii  =  0;  ii  <  mycountof(  m_var.onvif.urls  );  ii  ++  )  {
					 if  (  m_var.onvif.urls[ii].index_obj  ==  pRecvdReq->info.usIndex_obj  )  break;
				 }
				 if  (  ii  ==  mycountof(  m_var.onvif.urls  )  )  goto  errLabel;
				 //
				 Onvif_rule  url  =  m_var.onvif.urls[ii];
				 
				 //
				 CHelp_shareDynBmp  help_shareDynBmpMem;
				 i  =  help_shareDynBmpMem.getIndexByIndex_obj(  m_hWnd,  &m_var,  uiObjType,  url.index_obj  );
				 SHARE_dyn_bmp  *  pMem  =  help_shareDynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  i  );
				 if  (  !pMem  )  {
					 //  try to find a pos
					 i  =  help_shareDynBmpMem.getNewIndex(  m_hWnd,  &m_var,  uiObjType  );
					 if  (  i  <  0  )  {
						 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp failed: shared rtsp streams are full"  )  );	
						 showNotification(  0,  0,  0,  0,  0,  0,  _T(  "sharedDynBmp failed: shared rtsp streams are full"  )  );
						 goto  errLabel;
					 }
					 pMem  =  help_shareDynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  i  );
					 if  (  !pMem  )  goto  errLabel;
					 //  
					 if  (  help_shareDynBmpMem.clear(  pMem  )  )  {
						 goto  errLabel;
					 }
					 //
					 pMem->uiObjType  =  uiObjType;	//  2014/11/01
					 pMem->usIndex_obj  =  url.index_obj;
					 safeTcsnCpy(  url.tUrl,  pMem->name,  mycountof(  pMem->name  )  );
					 safeTcsnCpy(  url.cusName,  pMem->cusName,  mycountof(  pMem->cusName  )  );
					 //
					 m_var.onvif.bNeedRefreshed  =  TRUE;
				 }

				 //				 
				 if  (  !pMem  )  goto  errLabel;
				 //
				 pMem->var.recvdReq.uiTranNo_storeRecvdReq  =  pRecvdReq->info.uiTranNo_storeRecvdReq;
				 pMem->var.recvdReq.index_recvdReq  =  index_store;
				 //
				 if  (  !pMem->var.ucbLocalVideoOpen  )  {
					 //
					 if  (  pMem->var.internalProcess.bInProcess  )  {
						 showInfo_open0(  0,  0,  _T(  "procVerifyViewDynBmpResp failed: bInProcess true"  )  );
						 goto  errLabel;
					 }
					 //
					 pFuncs->shareDynBmps.pf_dlgShareDynBmps_toShareDynBmp(  m_hWnd,  pVar,  pRecvdReq->info.uiObjType,  i,  NULL,  NULL,  NULL  );
					 //
					 if  (  pMem->var.internalProcess.bInProcess  )  {
						 //
						 m_var.internalProcess.bNeedProcess  =  TRUE;
						 //  2014/09/11
						 iErr  =  0;  goto  errLabel;
					 }
				 }
				 if  (  !pMem->var.ucbLocalVideoOpen  )  {
					 #ifdef  __DEBUG__
							 traceLog((TCHAR*)  _T(  "shareDynBmp failed, ucbLocalVideoOpen 0"  )  );
					 #endif
					 goto  errLabel;
				 }
				 pFuncs->shareDynBmps.pf_dlgShareDynBmps_refreshShareStatus(  m_hWnd,  pVar,  pRecvdReq->info.uiObjType  );
				 
			 
			 }
		 else  {
			   //	
			   //  i  =  pRecvdReq->info.index_pShare_mem;		
			   //

			   CHelp_shareDynBmp  help_shareDynBmpMem;				
			   i  =  help_shareDynBmpMem.getIndexByIndex_obj(  m_hWnd,  &m_var,  uiObjType,  pRecvdReq->info.usIndex_obj  );
			   SHARE_dyn_bmp  *  pMem  =  help_shareDynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  i  );
			   if  (  !pMem  )  goto  errLabel;
			   pMem->var.recvdReq.uiTranNo_storeRecvdReq  =  pRecvdReq->info.uiTranNo_storeRecvdReq;
			   pMem->var.recvdReq.index_recvdReq  =  index_store;
		 }
		 
		 //
		 if  (  procVerifyViewDynBmpResp_step4(  m_hWnd,  &m_var,  uiObjType,  i  )  )  goto  errLabel;
	 	
		 //  2014/09/11
		 noStoreRecvdReq(  m_hWnd,  pVar,  index_store  );

		 iErr  =  0;  goto  errLabel;
		 //			
		 }		
	 else  {
		   if  (  !m_var.share_gps.bShare  )  {			
			   goto  errLabel;									  
		   }								
		   MIS_MSG_TASK  *  pMsg  =  &pRecvdReq->pMsg->task;
		   			
		   if  (  pMsg->uiTaskType  !=  CONST_imTaskType_viewGps  )  goto  errLabel;
		   			
		   if  (  procSendGpsReplyInfo(  (  MIS_CNT  *  )pMsg->pMisCnt,  m_hWnd,  pMsg,  TRUE,  m_var.share_gps.var.iIndex_sharedObj,  &pMsg->addr_logicalPeer  )  )  goto  errLabel;
			
	 
		   //  2014/09/11
		   noStoreRecvdReq(  m_hWnd,  pVar,  index_store  );

		   iErr  =  0;  goto  errLabel;
	 
	 }
	 	
	 //	important:
	 //  m_var.recvdReqs[j].dwTickCnt  =  0;		//  完成了要清除		
	 if  (  pRecvdReq->dwTickCnt  )  {
		 MACRO_qyAssert(  0,  _T(  "Err: recvdReq still stored"  )  );
	 }
	 	
	 


	 //
	 iErr  =  0;

errLabel:
	 
	 return  iErr;
}
#endif


 //
__declspec(  dllexport  )  int  get_realUrl(  IP_dev  *  pIpDev,  char  *  url,  int  urlCnt  )
{
	int  iErr  =  -1;
	char  buf[256]  =  "";
	int  index;


	//
	unsigned  char  ucCnt_urls  =  min(  pIpDev->ucCnt_urls,  mycountof(  pIpDev->urls  )  );
	Onvif_url  *  pMem=NULL;
	for  (  index  =  0;  index  <  ucCnt_urls;  index  ++  )  {
		 pMem  =  &pIpDev->urls[index];
		 if  (  !pMem->rtspUrl.url[0]  )  continue;
		 //
		 if  (  pIpDev->rule.defToken[0]  )  {
			 if  (  wcsstr(  CQyString(  pMem->token  ).GetBuffer(),  CQyString(  pIpDev->rule.defToken  ).GetBuffer()  )  )  {
				 break;
			 }
		 }
	}
	if  (  index  <  ucCnt_urls  )  {
		_snprintf(  buf,  mycountof(  buf  ),  "%s",  pMem->rtspUrl.url  );
	}
	else  {
		  _snprintf(  buf,  mycountof(  buf  ),  "%s",  pIpDev->urls[0].rtspUrl.url  );
	}
	//
	trim(  buf  );
	if  (  !buf[0]  )  return  -1;
	//
	if  (  !strchr(  buf,  '@'  )  )  {  
		//
		if  (  pIpDev->rule.usrName[0]  )  {
			char  *  prefix  =  (char*)"rtsp://";
			if  (  !_strnicmp(  buf,  prefix,  strlen(  prefix  )  )  )  {
				char  buf1[256]  =  "";
				safeStrnCpy(  buf,  buf1,  mycountof(  buf1  )  );
				_snprintf(  buf,  mycountof(  buf  ),  "%s%s:%s@%s",  prefix,  pIpDev->rule.usrName,  pIpDev->rule.passwd,  buf1  +  strlen(  prefix  )  );
			}
		}
	}

	//
	safeStrnCpy(  buf,  url,  urlCnt  );

	//
	iErr  =  0;
errLabel:

	return  iErr;

}


//
   int  procVerifyViewDynBmpResp_perReq( QY_MC  *  pQyMc, HWND  m_hWnd,  DLG_shareDynBmps_var  *  pVar,  MIS_MSG_INPUT  *  pMsgInput,  int  index_store  )
 {
	 int						iErr	=	-1;

	 MC_VAR_isCli			*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  -1;
	 FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  return  -1;

	 //
	 DLG_shareDynBmps_var  &  m_var  =  *pVar;

	 IM_CONTENTU			*	pContent	=	M_getMsgContent(  pMsgInput->ucFlg,  &pMsgInput->data  );									 
	 int  i  =  0;

	 if  (  pContent->uiType  !=  CONST_imCommType_verifyViewDynBmp  )  return  -1;

	 //
	 if  (  index_store  <  0  ||  index_store  >=  mycountof(  m_var.recvdReqs  )  )  return  -1;
	 DLG_shareDynBmp_recvdReq  *  pRecvdReq  =  &m_var.recvdReqs[index_store];

	 //	
	 if  (  !pRecvdReq->dwTickCnt  )  {		//  not a stored req
		 return  0;
	 }

	 #ifdef  __DEBUG__
			 traceLog((TCHAR*)  _T(  "verifyViewDynBmp resp per Req %d"  ),  index_store  );
	 #endif

		  //
		  BOOL  bMatched  =  FALSE;
		  //
		  if  (  pRecvdReq->info.uiContentType  ==  CONST_imCommType_retrieveDynBmps  )  {			
			  if  (  pRecvdReq->pMsg->uiType  !=  CONST_misMsgType_input  )  goto  errLabel;
			  if  (  pRecvdReq->pMsg->input.data.route.idInfo_from.ui64Id  ==  pContent->verifyViewDynBmp.idInfo_viewer.ui64Id  )  {
				  bMatched  =  TRUE;
			  }			  
			  }
		  else  {
			    if  (  pRecvdReq->pMsg->uiType  !=  CONST_misMsgType_task  )  goto  errLabel;
				//					  
				if  (  pRecvdReq->pMsg->task.addr_logicalPeer.idInfo.ui64Id  ==  pContent->verifyViewDynBmp.idInfo_viewer.ui64Id  )  {
					bMatched  =  TRUE;
				}
		  }

		  //
		  if  (  !bMatched  )  goto  errLabel;
	 
		  //																	
		  if  (  !isRuleCmdPermit(  pContent->verifyViewDynBmp.uiCmd  )  )  {
		 
			  noStoreRecvdReq(  m_hWnd,  &m_var,  index_store  );
			  //  m_var.recvdReqs[j].dwTickCnt  =  0;		//  这里要记得清除		 		

			  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp: viewer %I64u, access denied"  ),  pContent->verifyViewDynBmp.idInfo_viewer.ui64Id  );		
			  goto  errLabel;
		  }
		 
		  //	
		  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp: viewer %I64u, accepted. "  ),  pContent->verifyViewDynBmp.idInfo_viewer.ui64Id  );		
	 
		  //	 
		  if  (  pRecvdReq->info.uiContentType  ==  CONST_imCommType_retrieveDynBmps  )  {
			  //  2014/05/06			  
			  //  
			  dlgShareDynBmps_sndRetrieveDynBmpsRespToMsgr(  m_hWnd,  pVar,  index_store  );
			  
			  //  2014/09/11
			  noStoreRecvdReq(  m_hWnd,  pVar,  index_store  );
			  iErr  =  0;  goto  errLabel;

			  }
		  else  if  (  pRecvdReq->info.resObj.uiObjType  )  {	
			   //
			   SHARE_dynBmps	*	pShare;
			   unsigned  int  uiObjType  =  pRecvdReq->info.resObj.uiObjType;	//  2014/11/01
			   pShare  =  (  SHARE_dynBmps  *  )dlgShareDynBmps_getShareDynBmpsBySth(  m_hWnd,  &m_var,  pRecvdReq->info.resObj.uiObjType  );
			   if  (  !pShare  )  goto  errLabel;							    
		 
			   //		 
			   if  (  pRecvdReq->info.resObj.uiObjType  ==  CONST_objType_rtspStream  )  {
				   
				   if  (  !pRecvdReq->info.resObj.usIndex_obj  )  {				   
					   //  2014/09/09. 不再支持用0来直接匹配流，所以这里就直接出错了
					   showNotification(  0,  0,  0,  0,  0,  0,  _T(  "Not supported: use 0 to retrieve active stream"  )  );
					   goto  errLabel;			 
			 
				   }			 
				   
				   //
				 int  ii;
				 for  (  ii  =  0;  ii  <  mycountof(  m_var.onvif.ipDevsInfo.mems  );  ii  ++  )  {
					 if  (  m_var.onvif.ipDevsInfo.mems[ii].rule.usIndex_obj  ==  pRecvdReq->info.resObj.usIndex_obj
						 &&  m_var.onvif.ipDevsInfo.mems[ii].usHelp_subIndex  ==  pRecvdReq->info.resObj.usHelp_subIndex  ) 						 
					 {						
						 break;
					 }
				 }
				 if  (  ii  ==  mycountof(  m_var.onvif.ipDevsInfo.mems  )  )  goto  errLabel;
				 //
				 //Onvif_rule  rule  =  m_var.onvif.ipDevsInfo.mems[ii].rule;
				 IP_dev  *  pIpDev  =  &m_var.onvif.ipDevsInfo.mems[ii];		//  2016/07/11
				 
				 //
				 CHelp_shareDynBmp  help_shareDynBmpMem;
				 i  =  help_shareDynBmpMem.getIndexByIndex_obj(  m_hWnd,  &m_var,  uiObjType,  pIpDev->rule.usIndex_obj,  pIpDev->usHelp_subIndex  );
				 SHARE_dyn_bmp  *  pMem  =  help_shareDynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  i  );
				 if  (  !pMem  )  {
					 //  try to find a pos
					 i  =  help_shareDynBmpMem.getNewIndex(  m_hWnd,  &m_var,  uiObjType  );
					 if  (  i  <  0  )  {
						 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp failed: shared rtsp streams are full"  )  );	
						 showNotification(  0,  0,  0,  0,  0,  0,  _T(  "sharedDynBmp failed: shared rtsp streams are full"  )  );
						 goto  errLabel;
					 }
					 pMem  =  help_shareDynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  i  );
					 if  (  !pMem  )  goto  errLabel;
					 //  
					 if  (  help_shareDynBmpMem.clear(  pMem  )  )  {
						 goto  errLabel;
					 }
					 //
					 pMem->resObj.uiObjType  =  uiObjType;	//  2014/11/01
					 pMem->resObj.usIndex_obj  =  pIpDev->rule.usIndex_obj;
					 pMem->resObj.usHelp_subIndex  =  pIpDev->usHelp_subIndex;		//  2016/07/24
					 //
					 #if  0
						  myUtf82TChar(  pIpDev->urls[0].rtspUrl.url,  pMem->name,  mycountof(  pMem->name  )  );	//  2016/07/06
					 #endif
					 //  2016/07/13
				     char  realUrl[256]  =  "";
					 get_realUrl(  pIpDev,  realUrl,  mycountof(  realUrl  )  );
					 myUtf82TChar(  realUrl,  pMem->name,  mycountof(  pMem->name  )  );

					 //
					 safeTcsnCpy(  pIpDev->rule.cusName,  pMem->cusName,  mycountof(  pMem->cusName  )  );
					 //
					 m_var.onvif.bNeedRefreshed  =  TRUE;
				 }

				 //				 
				 if  (  !pMem  )  goto  errLabel;
				 //
				 pMem->var.recvdReq.uiTranNo_storeRecvdReq  =  pRecvdReq->info.uiTranNo_storeRecvdReq;
				 pMem->var.recvdReq.index_recvdReq  =  index_store;
				 //
				 if  (  !pMem->var.ucbLocalVideoOpen  )  {
					 //
					 if  (  pMem->var.internalProcess.bInProcess  )  {
						 showInfo_open0(  0,  0,  _T(  "procVerifyViewDynBmpResp failed: bInProcess true"  )  );
						 goto  errLabel;
					 }
					 //
					 pFuncs->shareDynBmps.pf_dlgShareDynBmps_toShareDynBmp(  pQyMc,  m_hWnd,  pVar,  pRecvdReq->info.resObj.uiObjType,  i,  NULL,  NULL,  NULL  );
					 //
					 if  (  pMem->var.internalProcess.bInProcess  )  {
						 //
						 m_var.internalProcess.bNeedProcess  =  TRUE;
						 //  2014/09/11
						 iErr  =  0;  goto  errLabel;
					 }
				 }
				 if  (  !pMem->var.ucbLocalVideoOpen  )  {
					 #ifdef  __DEBUG__
							 traceLog((TCHAR*)  _T(  "shareDynBmp failed, ucbLocalVideoOpen 0"  )  );
					 #endif
					 goto  errLabel;
				 }
				 pFuncs->shareDynBmps.pf_dlgShareDynBmps_refreshShareStatus(  pQyMc,  m_hWnd,  pVar,  pRecvdReq->info.resObj.uiObjType  );
				 
			 
			 }
		 else  {
			   //	
			   //  i  =  pRecvdReq->info.index_pShare_mem;		
			   //

			   CHelp_shareDynBmp  help_shareDynBmpMem;				
			   i  =  help_shareDynBmpMem.getIndexByIndex_obj(  m_hWnd,  &m_var,  uiObjType,  pRecvdReq->info.resObj.usIndex_obj,  pRecvdReq->info.resObj.usHelp_subIndex  );
			   SHARE_dyn_bmp  *  pMem  =  help_shareDynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  i  );
			   if  (  !pMem  )  goto  errLabel;
			   pMem->var.recvdReq.uiTranNo_storeRecvdReq  =  pRecvdReq->info.uiTranNo_storeRecvdReq;
			   pMem->var.recvdReq.index_recvdReq  =  index_store;
		 }
		 
		 //
		 if  (  procVerifyViewDynBmpResp_step4(  m_hWnd,  &m_var,  uiObjType,  i  )  )  goto  errLabel;
	 	
		 //  2014/09/11
		 noStoreRecvdReq(  m_hWnd,  pVar,  index_store  );

		 iErr  =  0;  goto  errLabel;
		 //			
		 }		
	 else  {
		   if  (  !m_var.share_gps.bShare  )  {			
			   goto  errLabel;									  
		   }								
		   MIS_MSG_TASK  *  pMsg  =  &pRecvdReq->pMsg->task;
		   			
		   if  (  pMsg->uiTaskType  !=  CONST_imTaskType_viewGps  )  goto  errLabel;
		   			
		   if  (  procSendGpsReplyInfo(  (  MIS_CNT  *  )pMsg->pMisCnt,  m_hWnd,  pMsg,  TRUE,  m_var.share_gps.var.iIndex_sharedObj,  &pMsg->addr_logicalPeer  )  )  goto  errLabel;
			
	 
		   //  2014/09/11
		   noStoreRecvdReq(  m_hWnd,  pVar,  index_store  );

		   iErr  =  0;  goto  errLabel;
	 
	 }
	 	
	 //	important:
	 //  m_var.recvdReqs[j].dwTickCnt  =  0;		//  完成了要清除		
	 if  (  pRecvdReq->dwTickCnt  )  {
		 MACRO_qyAssert(  0,  _T(  "Err: recvdReq still stored"  )  );
	 }
	 	
	 


	 //
	 iErr  =  0;

errLabel:
	 
	 return  iErr;
}



//
 //  CONST_imCommType_verifyViewDynBmp最好改成通用的校验处理verifyRemoteReq，在VERIFY_viewDynBmp里最好包含一个uiType_remoteReq
 //
__declspec(  dllexport  )  int  procVerifyViewDynBmpResp(  HWND  m_hWnd,  DLG_shareDynBmps_var  *  pVar,  MIS_MSG_INPUT  *  pMsgInput  )
 {
	 int						iErr	=	-1;

	 MC_VAR_isCli			*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	 QY_MC* pQyMc = pProcInfo->pQyMc;

	 //
	 DLG_shareDynBmps_var  &  m_var  =  *pVar;

	 IM_CONTENTU			*	pContent	=	M_getMsgContent(  pMsgInput->ucFlg,  &pMsgInput->data  );									 

	 if  (  pContent->uiType  !=  CONST_imCommType_verifyViewDynBmp  )  return  -1;

	 int  index_store  =  0;
	 int  i  =  0;
	
	 #ifdef  __DEBUG__
			 traceLog((TCHAR*)  _T(  "verifyViewDynBmp resp"  )  );
	 #endif
	
	 if  (  !pContent->verifyViewDynBmp.ucbResp  )  {
		 #ifdef  __DEBUG__
				 traceLog((TCHAR*)  _T(  "verifyViewDynBmp resp failed, ucbResp is false"  )  );
		 #endif
		 goto  errLabel;		
	 }						
	 if  (  !pContent->verifyViewDynBmp.idInfo_viewer.ui64Id  )  goto  errLabel;
			
	 //	
	 for  (  index_store  =  0;  index_store  <  mycountof(  m_var.recvdReqs  );  index_store  ++  )  {
		  procVerifyViewDynBmpResp_perReq(  pQyMc,  m_hWnd,  &m_var,  pMsgInput,  index_store  );
	 }

	 //
	 iErr  =  0;

errLabel:
	 
	 return  iErr;
 }




