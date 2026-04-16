
#include	"stdafx.h"
#include	<stdio.h>
#include	<stddef.h>
#include	<time.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
//  #include	"myresource.h"
#include	"qyVDev.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyMcMainRealTimeMediaProc.h"

#include	"qyDynLib.h"
#include	"qyAvRecordPublic.h"

#include	<windows.h>
#include	<windef.h>
#include	<lmcons.h>
#ifndef  __WINCE__
	#include	<lmshare.h>
#endif
#include	<tlhelp32.h>
#include	<iphlpapi.h>

//  #include	"qwmDynFunc.h"

#include	"qmcCmdProc.h"

#include	"tmpCeLib.h"
#include	"qySqlFunc.h"
#include	"qyThread.h"
#include	"isCmdConst.h"
#include	"qyCusResTemp.h"
//
#include	"policyAvParams.h"


#include	"myDb.h"

#include	"isCliCorePublic.h"
#include	"isCliHelpPublic.h"
#include	"qyMessengerHelpPublic.h"
#include	"imgProcessPublic.h"
#include	"isCliD3dPublic.h"
#include	"qisWallsProc.h"
#include	"qmcObjVarPublic.h"
#include	"qmcTaskPublic.h"
#include	"qmcSharePublic.h"
#include	"dlgShareDynBmpsProc.h"
#include	"funcsForIsCliHelp.h"

#include	"qmcCommFunc_isCli.h"
#include	"isCliExPublic.h"
#include	"ctxMcThread.h"

//
#include	"qmcVideoTool.h"
#include	"qmcStruct_defs.h"

//
#include	"qisWebRtcPublic.h"
#include	"ctxQmc.h"

//
#include	"smCommProc.h"
#include <qmCfg_isCli.h>
#include <qisSyncTex.h>
//
#include	"qmcPlayDev_dSound.h"
#include	"qmcPlayDev_dummy.h"


//
extern "C" DWORD WINAPI mcThreadProc_mis_mgr( LPVOID lpParameter );
extern "C" DWORD WINAPI mcThreadProc_mis_display( LPVOID lpParameter );
extern "C" DWORD WINAPI mcThreadProc_mis_robot( LPVOID lpParameter );
extern "C" DWORD WINAPI mcThreadProc_mis_media( LPVOID lpParameter );
extern "C" DWORD WINAPI mcThreadProc_mis_realTimeMedia( LPVOID lpParameter );
extern "C" DWORD WINAPI mcThreadProc_mis_rtOp( LPVOID lpParameter );
extern "C" DWORD WINAPI mcThreadProc_mis_scheduler( LPVOID lpParameter );

//

int  __cdecl  myCompare_searchPhoneMsgrByDevIdStr(  const  void  *  key,  const  void  *  pElemParam  );
int  __cdecl  myCompare_searchPhoneMsgrByIdInfo(  const  void  *  key,  const  void  *  pElemParam  );

BOOL  bMeInfoNeedReg(  void  *  pDb,  int  iDbType,  MIS_CNT  *  pMisCnt,  QY_MESSENGER_REGINFO  *  pRegInfo  );




//
//extern  struct  PolicyAvParams  gAvParams;


 //
 unsigned  int  getVarSize_is(  void  *  pQyMcParam  )
{
	QY_MC	*	pQyMc	=	(  QY_MC  *  )pQyMcParam;

	//if  (  pQyMc->iAppType  !=  CONST_qyAppType_client  )  return  sizeof(  MC_VAR_isMgr  );

#if  0
	if  (  isQmCmd(  pQyMc  )  )  return  sizeof(  MC_VAR_qmCmd  );
#endif

	return  sizeof(  MC_VAR_isCli  );
}


 //  2007/05/12
 int __cdecl myCompare_misClient( const void * pIdInfoKey, const void * pMemParam) 
{
	 QY_MESSENGER_ID	*	pIdInfo	=	(  QY_MESSENGER_ID  *  )pIdInfoKey;
	 QM_OBJQ_MEM		*	pMem	=	(  QM_OBJQ_MEM  *  )pMemParam;
	 __int64				i64Id	=	(  pIdInfo->ui64Id  -  (  (  QMEM_MESSENGER_CLI  *  )pMem->pQMemObj  )->idInfo.ui64Id  );

	 if  (  i64Id  >  0  )  return  1;
	 else  if  (  i64Id  ==  0  )  return  0;
	 else  return  -1;
}


 //
 void  exitQMem_misClient(  void  *  p0,  void  *  p1,  void  *  pQMemParam  )
{
	return;
}

 //  2007/04/05
 int  fillQmObjMemInfo_misClient(  QY_SERVICEGUI_INFO  *  pSci,  void  *  pQParam,  void  *  pDb,  int  iDbType,  void  *  pClient,  QM_OBJQ_MEM  *  pQMem  )
{
	 int						iErr				=	-1;
	 QY_MESSENGER_INFO		*	pInfo				=	(  QY_MESSENGER_INFO  *  )pClient;

	 if  (  !pSci  ||  !pClient  )  return  -1;
	 QY_MC  *  pQyMc  =  (  QY_MC  *  )pSci->pParent;	//  2016/09/19
	 if  (  !pQyMc  )  return  -1;
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;
	 
	 QMEM_MESSENGER_CLI		*	pObj		=	NULL;

	 memset(  pQMem,  0,  sizeof(  pQMem[0]  )  );
	 //	 
	 pQMem->iType  =  0;

	 pObj  =  (  QMEM_MESSENGER_CLI  *  )mymalloc(  sizeof(  QMEM_MESSENGER_CLI  )  );		//  2007/04/20, ×¢ÒâÕâÀïÔËÓÃÁË¶¯Ì¬·ÖÅä²¢¹ÒÔÚobjQÀïµÄÓÃ·¨
	 if  (  !pObj  )  goto  errLabel;
	 memset(  pObj,  0,  sizeof(  pObj[0]  )  );

	 //
	 pObj->idInfo.ui64Id  =  pInfo->idInfo.ui64Id;
	 pObj->uiType  =  pInfo->uiType;

	 //
#ifndef  __NOTSUPPORT_DB__
		REFRESH_imObjRules_req	req;
		memset(  &req,  0,  sizeof(  req  )  );
		if  (  g_dbFuncs.pf_bGetImObjRulesReq(  pDb,  iDbType,  pInfo->misServName,  0,  &pInfo->idInfo,  NULL,  0,  &req  )  )  {
			imObjRulesReq2Rules(  &req,  &pInfo->idInfo,  &pObj->rules  );
			}
		else  {
			  #ifdef  __DEBUG__
					  traceLog((TCHAR*)  _T(  "fillQmObjMemInfo_misClient, bGetImObjRulesReq failed"  )  );
			  #endif
		}
#endif

	 //
	 pQMem->pQMemObj  =  pObj;

	 //
	 iErr  =  0;
errLabel:
	 if  (  iErr  )  {
		 if  (  pObj  )  free(  pObj  );
	 }
	 if  (  !iErr  )  {
		 pQMem->pQMemObj  =  pObj;
	 }
	 return   iErr;
}

 int  tmp_addToQmObjQ_misClient(  void  *  p0,  QM_OBJQ_MEM  *  tmppMem,  void  *  pQParam  )	//  addÊ§°Ü£¬¿ÉÒÔµ±×÷ÑÏÖØºó¹û£¬¿ÉÒÔÒªÇódaemonÖØÆð
{
	 int					iErr	=	-1;
	 QM_OBJQ			*	pQ		=	(  QM_OBJQ  *  )pQParam;
	 //  CQySyncObj				syncObj;
	 QM_OBJQ_MEM		*	pMem	=	NULL;
	 int					iRet;
	 int					i;


	 if  (  !pQ->pfCompare  )  return  -1;

	 if  (  !tmp_findMisQMemById(  p0,  pQParam,  &(  (  QMEM_MESSENGER_CLI  *  )tmppMem->pQMemObj  )->idInfo,  NULL  )  )  {
		 iErr  =  0;  goto  errLabel;	//  ÔÚÕâÀïµ÷ÓÃÒ»´Î£¬ÒÔ·ÀÖ¹¶àÏß³ÌÍ¬Ê±¼ÓÈëMAC
	 }
	 if  (  bQmObjQFull(  p0,  pQParam  )  )  {
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  CQyString(  (char*)"127.0.0.1"  ),  0,  CQyString(  (char*)""  ),  _T(  ""  ),  _T(  "¹ÜÀí¶ÓÁÐÒÑÂú£¬²»ÄÜ¼ÓÈë¹ÜÀí¶ÓÁÐ"  )  );
		 goto  errLabel;					//  ·ÀÖ¹Ô½½ç
	 }

	 if  (  !pQ->cnt  )  {
		 memcpy(  pQ->pMems,  tmppMem,  sizeof(  pQ->pMems[0]  )  );
		 pQ->cnt  ++  ;
		 pMem  =  pQ->pMems;
		 iErr  =  0;  goto  errLabel;
	 }

	 for  (  i  =  pQ->cnt  -  1;  i  >=0;  i  --  )  {					//  ¶ÓÁÐ°´ÉýÐò´æ·Å
		  iRet  =  pQ->pfCompare(  &(  (  QMEM_MESSENGER_CLI  *  )tmppMem->pQMemObj  )->idInfo,  &pQ->pMems[i]  );  
		  if  (  !iRet  )  {
			  traceLogA(  (char*)  "ÕâÊÇ´íÎóµÄ£¬²»Ó¦¸Ã³öÏÖ"  );  goto  errLabel;
		  }
		  if  (  iRet  <  0  )  {
			  memcpy(  &pQ->pMems[i  +  1],  &pQ->pMems[i],  sizeof(  pQ->pMems[0]  )  );
			  continue;
		  }
		  pMem  =  &pQ->pMems[i  +  1];						//  ·¢ÏÖÁË±È¸ÃMACÐ¡µÄ£¬ÓÚÊÇ·ÅÔÚºóÃæ
		  memcpy(  pMem,  tmppMem,  sizeof(  pQ->pMems[0]  )  );
		  pQ->cnt  ++  ;
		  iErr  =  0;  goto  errLabel;
	 }

	 pMem  =  &pQ->pMems[0];		//  ÕâÀïÊÇ·¢ÏÖÕÒÍê¶ÓÁÐ£¬Ò²Ã»ÓÐ±È¸ÃMACÐ¡µÄ£¬Ö»ºÃ·Å×îÇ°ÃæÁË
	 memcpy(  pMem,  tmppMem,  sizeof(  pQ->pMems[0]  )  );
	 pQ->cnt  ++  ;
	 iErr  =  0;  

errLabel:

	 return  iErr;	 

}


#ifdef  __DEBUG__

 int  kkkkk(  )
 {
	 //void  *  p  =  new  CCtxQyMc;

	 return  0;
 }

#endif




#ifndef  __NOTSUPPORT_d3d__
 //
 int  init_toUseD3d(  MC_VAR_isCli  *  pProcInfo  )
 {
	 int  iErr  =  -1;

	 //
	 if  (  !pProcInfo  )  return  -1;
	

	 //  2013/07/03	
	 if  (  dyn_set_g_pQyMc_isCliD3d(  g_pQyMc  )  )  {					
		 #ifdef  __DEBUG__
				 //  未装载 
				 traceLog((TCHAR*)  _T(  "initVar_isGui: dyn_set_g_pQyMc_isCliD3d（  ）  failed, skipped"  )  );  //
		#endif
		}		
	 else  {
			  //		   
			  if  (  dyn_dllInit_d3d_isCli(  )  )  {		 			   
				  goto  errLabel;		   
			  }		   
			  g_pQyMc->pGBuf_d3d  =  dyn_GBuf_d3d_isCli_new(  );		   
			  if  (  !g_pQyMc->pGBuf_d3d  )  goto  errLabel;		   
			  //		   
			  g_pQyMc->pQisWallsCfg  =  dyn_qisWallsCfgNew(  MAX_qisWallCfgs  );		   
			  if  (  !g_pQyMc->pQisWallsCfg  )  goto  errLabel;
			  		   
			  //  2015/11/16		   
			  if  (  dyn_addQisWallCfg(  g_pQyMc->pQisWallsCfg,  CONST_wallType_conf,  NULL,  NULL  )  )  {			   
				  goto  errLabel;		   
			  }

			  //
			  #ifdef  __DEBUG__
					  #if  0
							TCHAR  *  wallFile  =  _T(  "c:\\tttbbb\\test.qvw"  );
							if  (  addQisWall(  g_pQyMc->pQisWalls,  CONST_wallType_confWall,  wallFile  )  )  {
								goto  errLabel;
							}
					  #endif
			  #endif

			  //  2016/05/18		   
			  if  (  bApp_ts_3d(  g_pQyMc  )  )  {			   			   
				  //			   
				  switch  (  g_pQyMc->env.iPlatformId  )  {					
						  case  CONST_qyPlatform_winxp:					   
						  case  CONST_qyPlatform_win2003:					   
						  case  CONST_qyPlatform_winVista:					   
						  case  CONST_qyPlatform_win2008:					   
						  case  CONST_qyPlatform_win7:					   
						  case  CONST_qyPlatform_win2008R2:							 
							    break;					   
						  default:
							     //							  
							     pProcInfo->cfg.ucb__USE_d2dToRenderTxt__  =  TRUE;												  
								 break;	 			   
				  }		   
			  }
			  if (!pProcInfo->bUse_dx11()) {
				  pProcInfo->cfg.ucb__USE_d2dToRenderTxt__ = false;
			  }
			  //  2016/05/19
			  #ifdef  __DEBUG__
				   #if  10
						pProcInfo->cfg.ucb__USE_d2dToRenderTxt__  =  false;//TRUE;
						traceLog((TCHAR*)  _T(  "TEST: set __USE_d2dToRenderTxt__ to true"  )  );
				   #endif
			  #endif		
		}
		
	 iErr  =  0;
errLabel:
	 return  iErr;
 }


 //
 int  exit_toUseD3d(  MC_VAR_isCli  *  pProcInfo  )
 {

	 //  2013/07/03	
	 if  (  g_pQyMc->pQisWallsCfg  )  dyn_qisWallsCfgFree(  &g_pQyMc->pQisWallsCfg  );
	 
	 if  (  g_pQyMc->pGBuf_d3d  )  dyn_GBuf_d3d_isCli_free(  &g_pQyMc->pGBuf_d3d  );	
	 dyn_dllExit_d3d_isCli(  );
	 
	 return  0;
 }


#endif


 //
#define		DEFAULT_terminalType					CONST_terminalType_conf

 //
 //
 extern  "C"  int  qyGetTerminalType(LPCTSTR  cfgFile  )
 {
	 int  iRet = -1;

	 iRet = DEFAULT_terminalType;

#define		CONST_cfgName_terminalType				_T(  "terminalType")
	 //
	 TCHAR  cfgVal[128];

	 //
	 //USB Video Device
	 getCfgValByNameT(cfgFile, (TCHAR*)CONST_cfgName_terminalType, cfgVal, mycountof(cfgVal));
	 tTrim(cfgVal);
	 int  tmpiRet = _ttol(cfgVal);

	 switch  (tmpiRet) {
			 case  CONST_terminalType_conf:
			 case  CONST_terminalType_mon:
				   iRet = tmpiRet;
				   break;
			 default:
					 break;
	 }

	 //
	 return  iRet;
 }




 //
 //
#define		CONST_uiMaxQNodes_mediaQ_win32						600  *  2		// 120						//  2014/05/12. 2008/03/15
#define		CONST_uiMaxQNodes_mediaQ_x64						600  *  4		//  600  *  2		// 200						//  2012/05/23


 //
 #define		CONST_uiMaxQNodes_aecPlayQ							CONST_uiMaxQNodes_aecQ


 //
 int  initVar_isGui(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int						iErr				=	-1;
	 QY_MC					*	pQyMc				=	(  QY_MC  *  )p0;
	 QY_SERVICEGUI_INFO		*	pSci				=	(  QY_SERVICEGUI_INFO  *  )p1;
	 //  p2
	 int						i;


	 if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_is  )  return  0;

	 //  2010/10/01
	 if  (  pQyMc->iAppType  !=  CONST_qyAppType_client  )  {
		 return  -1;
	 }

	 //
	 QM_dbFuncs* pDbFuncs; pDbFuncs = pQyMc->p_g_dbFuncs;
	 if (!pDbFuncs)  return  -1;// goto  errLabel;
	 QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	 //  2009/12/21
	 //
	 MC_VAR_isCli			*	pProcInfo			=	(  MC_VAR_isCli  *  )pSci->pVar;
	 QY_COMM_AUTHINFO_MIS	*	pAuthInfo			=	&pProcInfo->authInfo;
	 unsigned  long				len;

	 pProcInfo->pQyMc  =  pQyMc;
	 pProcInfo->pSgiParam  =  pSci;


	 //  2013/06/08
	 pProcInfo->p_gAvParams  =  get_g_pAvParams();//&gAvParams;
	 if  (  !pProcInfo->p_gAvParams  )  goto  errLabel;
	 memset(  pProcInfo->p_gAvParams,  0,  sizeof(  PolicyAvParams  )  );
	 //
#if  0  //  2016/09/05
	 pProcInfo->p_g_dbFuncs  =  &g_dbFuncs;
	 memset(  &g_dbFuncs,  0,  sizeof(  g_dbFuncs  )  );
#endif
	 //
	 if  (  pProcInfo->bUse_FUNCS_for_isCliHelp(  )  )  {
		 pProcInfo->pFuncs_for_isCliHelp  =  pProcInfo->FUNCS_for_isCliHelp_new(  );
		 if  (  !pProcInfo->pFuncs_for_isCliHelp  )  {
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "Client"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initVar_isGui failed, pFuncs_for_isCliHelp is null"  ),  _T(  ""  )  ); 
			 goto  errLabel;
		 }

		 //
#ifdef  __DEBUG__
		 FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
		 //
		 int  ii = 0;
		 
#endif

	 }
	 
	 //
	 _sntprintf(  pProcInfo->who_showInfo,  mycountof(  pProcInfo->who_showInfo  ),  _T(  "%s"  ),  pQyMc->who_showInfo  );

	 //
	 pProcInfo->cfg.uiMaxSendMsgs  =  CONST_maxSendMsgs_isClient;
	 pProcInfo->cfg.usMaxMsgrRecentFriends  =  CONST_usMaxMsgrRecentFriends;

	 //  2014/07/13
	 
	 
	 pProcInfo->cfg.uiSizePerSnd_file_noAv  =  min(CONST_bufSize_transferFileDataResp, DEFAULT_uiSizePerSnd_file_noAv );
	 pProcInfo->cfg.uiSizePerSnd_file_avExists  =  min(CONST_bufSize_transferFileDataResp,DEFAULT_uiSizePerSnd_file_avExists);

	 //
	 pProcInfo->cfg.uiSizePerSnd_media  =  DEFAULT_uiSizePerSnd_media_isCli;		//  2008/04/01
	 pProcInfo->cfg.usNeedShowFrameInfoIntervalInS	=	DEFAULT_usNeedShowFrameInfoIntervalInS;

	 //
	 pProcInfo->cfg.uiBufSize_myDrawVideoData  =  CONST_bufSize_myDrawVideoData_5k;	//  2014/06/01
	 if  (  !b4Core(  )  ||  bLikeXp(  )  )  pProcInfo->cfg.uiBufSize_myDrawVideoData  =  CONST_bufSize_myDrawVideoData_2k;	//  2014/06/01
	 //
	 pProcInfo->cfg.uiBufSize_myPlayAudioData  =  CONST_bufSize_myPlayAudioData;	//  2010/04/24

	 //  2010/06/26	 
#ifndef  __WINCE__
	 	
	 //
	 pProcInfo->cfg.envVar.usMaxQNodes_mediaQ  =  bAppX64(  )  ?  CONST_uiMaxQNodes_mediaQ_x64  :  CONST_uiMaxQNodes_mediaQ_win32;
	 pProcInfo->cfg.envVar.usQNodes_warningInterval_mediaQ  =  CONST_uiQNodes_warningInterval_mediaQ;
	 //
	 pProcInfo->cfg.envVar.usMaxQNodes_rtMediaQ  =  bAppX64(  )  ?  CONST_uiMaxQNodes_mediaQ_x64  :  CONST_uiMaxQNodes_mediaQ_win32;
	 pProcInfo->cfg.envVar.usQNodes_warningInterval_rtMediaQ  =  CONST_uiQNodes_warningInterval_mediaQ;
	 //
	 //  2016/12/26
	 pProcInfo->cfg.envVar.usMaxQNodes_rtOpQ  =  pProcInfo->cfg.envVar.usMaxQNodes_rtMediaQ;
	 pProcInfo->cfg.envVar.usQNodes_warningInterval_rtOpQ  =  pProcInfo->cfg.envVar.usQNodes_warningInterval_rtMediaQ;

	 //
	 //pProcInfo->cfg.envVar.usMaxQNodes_vCamQ  =  CONST_uiMaxQNodes_vCamQ;
	 //
	 pProcInfo->cfg.envVar.usMaxQNodes_playSoundQ  =  isMem512(  pQyMc  )  ?  CONST_uiMaxQNodes_playSoundQ_256  :  CONST_uiMaxQNodes_playSoundQ;
	 //  2012/11/09
	 pProcInfo->cfg.envVar.usMaxQNodes_playVideoQ  =  isLowCfg(  pQyMc  )  ?  CONST_uiMaxQNodes_playVideoQ_256  :  CONST_uiMaxQNodes_playVideoQ;
	 pProcInfo->cfg.envVar.usMaxQNodes_displayVideoQ  =  isLowCfg(  pQyMc  )  ?  CONST_uiMaxQNodes_displayVideoQ_256  :  CONST_uiMaxQNodes_displayVideoQ;

	 //
	 pProcInfo->cfg.envVar.usMaxQNodes_dlgTalk_processQ  =  200;		//  

	 pProcInfo->cfg.envVar.usMaxQNodes_imMsgLogQ  =  200;

#else
	 pProcInfo->cfg.envVar.usMaxQNodes_mediaQ  =  10  +  CONST_uiQNodes_warningInterval_mediaQ;
	 pProcInfo->cfg.envVar.usQNodes_warningInterval_mediaQ  =  CONST_uiQNodes_warningInterval_mediaQ;
	 pProcInfo->cfg.envVar.usMaxQNodes_rtMediaQ  =  10  +  CONST_uiQNodes_warningInterval_mediaQ;
	 pProcInfo->cfg.envVar.usQNodes_warningInterval_rtMediaQ  =  CONST_uiQNodes_warningInterval_mediaQ;

	 pProcInfo->cfg.envVar.usMaxQNodes_vCamQ  =  3;
	 pProcInfo->cfg.envVar.usMaxQNodes_playSoundQ  =  8;
	 //  2012/11/09
	 pProcInfo->cfg.envVar.usMaxQNodes_playVideoQ  =  isMem512(  )  ?  CONST_uiMaxQNodes_playVideoQ_256  :  CONST_uiMaxQNodes_playVideoQ;
	 pProcInfo->cfg.envVar.usMaxQNodes_displayVideoQ  =  CONST_uiMaxQNodes_displayVideoQ;
	 //
	 pProcInfo->cfg.envVar.usMaxQNodes_dlgTalk_processQ  =  200;
	 #ifdef  __DEBUG__
			 pProcInfo->cfg.envVar.usMaxnItems_dlgTalk_list  =  5;
	 #else
			 pProcInfo->cfg.envVar.usMaxnItems_dlgTalk_list  =  50;
	 #endif

	 pProcInfo->cfg.envVar.usMaxQNodes_imMsgLogQ  =  200;

#endif

	 //  2017/08/15
	 pProcInfo->cfg.envVar.default_ucbLetConfMgrSetMicOn  =  FALSE;
	 switch  (  pQyMc->iCustomId  )  {
			 case  CONST_qyCustomId_bjyz:
			 case  CONST_qyCustomId_business:
			 case  CONST_qyCustomId_hbwj:
				   pProcInfo->cfg.envVar.default_ucbLetConfMgrSetMicOn  =  TRUE;
				   break;
			 default:
					break;
	 }


	 //  2014/09/22
	 pProcInfo->cfg.ucb__SUPPORT_shareDynBmps__  =  TRUE;
	 if (  !bUse_imObjView_as_guiWnd()  )  {
		 if  (  bApp_ts(  pQyMc  )  )  {
			 pProcInfo->cfg.ucb__SUPPORT_shareDynBmps__  =  FALSE;
			 #ifdef  __DEBUG__
					 traceLog((TCHAR*)  _T(  "shareDynBmps not supported for ts"  )  );
			 #endif
		 }
	 }
	 
	 //
	 //
	 //
#if  0  //  2017/09/03
	 pProcInfo->cfg.ucbNeedShowFrameInfo_forVideoConference  =  1;			//  2008/05/17
	 #ifdef  __DEBUG__
			 traceLogA(  (char*)  "iniitVar_isGui: ucbNeedShowFrameInfo_forVideoConferenceÓ"  );
	 #endif
#endif
	
	 //  2010/08/05
#ifndef  __WINCE__
	 //  if  (  bLikeXp(  )  )  
		pProcInfo->cfg.ucb__SUPPORT_dmoToDec__  =  TRUE;		//  2012/03/22, 因为filterGraph有死锁现象,所以,这里选择使用dmo.

		//  2012/03/23
		TCHAR						tBuf[256];  tBuf[0] = 0;// = _T("");
		QY_REG						reg;
		memset(  &reg,  0,  sizeof(  reg  )  );
		reg.hKeyRoot0  =  HKEY_CURRENT_USER;
		lstrcpyn(  reg.rootKey,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );
		qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  _T(  CONST_regValName_ucbNotUseDmo  ),  (  char  *  )tBuf,  sizeof(  tBuf  ),  NULL  );
		if  (  _ttol(  tBuf  )  )  {
			pProcInfo->cfg.ucb__SUPPORT_dmoToDec__  =  FALSE;
		}

		#ifndef  __SUPPORT_CUS_sampleGrabber__		//  2012/03/20. 如果没定义,则只能使用dmo
				pProcInfo->cfg.ucb__SUPPORT_dmoToDec__  =  TRUE;
		#endif

		//
		//pProcInfo->cfg.ucb__USE_hdEnc_conf__  =  FALSE;	//  2015/10/05	//  TRUE;	//  FALSE;	//  2014/04/03

#endif

		//
		pProcInfo->cfg.b_useQ2_toPlayA = true;


		//
#ifdef  __DEBUG__	//  2011/05/17
			

#endif

		//  2015/12/04
		int  size;
		size  =  sizeof(  ZONE_objs  );
		pProcInfo->pGZone_activeTalkers  =  (  ZONE_objs  *  )mymalloc(  size  );
		if  (  !pProcInfo->pGZone_activeTalkers  )  goto  errLabel;
		memset(  pProcInfo->pGZone_activeTalkers,  0,   size  );
		pProcInfo->pGZone_activeTalkers->iIndex_enlarged1  =  -1;		//  2016/03/25

		//  2016/03
		size  =  sizeof(  ZONE_objs  );
		pProcInfo->pGZone_d3dWalls  =  (  ZONE_objs  *  )mymalloc(  size  );
		if  (  !pProcInfo->pGZone_d3dWalls  )  goto  errLabel;
		memset(  pProcInfo->pGZone_d3dWalls,  0,  size  );
		pProcInfo->pGZone_d3dWalls->iIndex_enlarged1  =  -1;

	 	 //
#ifdef  __isCli__
		//  2015/12/04
		set_g_pQyMc_isCliCore(  pQyMc  );

		//  2013/06/07
		set_g_pQyMc_isCliHelp(  pQyMc  );

		#ifdef  __USE_qyMessengerHelp__
				//  2013/07/26
				set_g_pQyMc_qyMessengerHelp(  pQyMc  );
		#endif

		//  2013/09/20
		set_g_pQyMc_imgProcess(  pQyMc  );


		//
		//  2016/089/08
		#ifndef  __NOTSUPPORT_d3d__
				 if  (  init_toUseD3d(  pProcInfo  )  )  {
					 showInfo_open0(  0,  0,  _T(  "initVar_isGui failed, init_toUseD3d failed"  )  );
					 goto  errLabel;
				 }
		#endif

		//  2017/06/18
		init_webRtc(  );
#endif
	
		//
			//
#if 10
		{
			TCHAR  tDir[256] = _T("");
			//safeTcsnCpy(CONST_cfgFileName_sm, pProcInfo->m_var.smTerminalInitCfgFile, mycountof(pProcInfo->m_var.smTerminalInitCfgFile));
			pProcInfo->getSmCfgInfo(tDir, mycountof(tDir));
		}
#endif

		//
		if (qisSharedTexInfos_init(50,  &pProcInfo->m_pQisSharedTexInfos)) {
			goto  errLabel;
		}


	 //
	 if  (  getPolicyIsClient(  pProcInfo,  &pProcInfo->cfg.policy  )  )  {
		 showInfo_open0(  0,  0,  _T(  "initVar_isGui: getPolicyIsClient failed"  )  );
		 goto  errLabel;
	 }

	 //
	 setSaveMsgFlg(true);

	 //  2016/04/28
	 pProcInfo->m_pf_doDecodeVideo_dvtCli  =  doDecodeVideo_dvtCli;
	 //
	 pProcInfo->m_pf_qdcInitCompressVideo_evtCli  =  qdcInitCompressVideo_evtCli;
	 pProcInfo->m_pf_qdcExitCompressVideo_evtCli  =  qdcExitCompressVideo_evtCli;	  
	 //
	 pProcInfo->m_pf_qdcGetSpsPps_evtCli  =  qdcGetSpsPps_evtCli;	  
	 //
	 pProcInfo->m_pf_doEncodeVideo_evtCli_run  =  doEncodeVideo_evtCli_run;


	 
	 //
	 //
	 //
	 pProcInfo->uiDevType  =  CONST_objType_pc;		//  2007/08/03

	 //
	 pProcInfo->uiTerminalType = qyGetTerminalType(pQyMc->cfg.smCfgFile );
	 //
	 _sntprintf(tBuf, mycountof(tBuf), _T("terminalType %d"), pProcInfo->uiTerminalType);
	 showInfo_open0(0, 0, tBuf);



	 //  authInfo
	 pAuthInfo->iAppType  =  pQyMc->iAppType;
#if  0	//  2013/04/04. 将ts和普通的pc客户端暂时合并, 无登陆的客户端通过authType来区分
	 if  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  {
		 //  &&  bSupported_devAuth(  )  )  
		 #ifdef  __APP_qyMc_touchscreen__
		 //  暂时处理一下.
				 pAuthInfo->iAppType  =  CONST_qyAppType_client_ts;					//  2011/03/27. 因为很多地方用到了对qyAppType_client的判断，所以暂时不能直接在GetAppType(  )里替换。
		 #endif
	 }
#endif
	 //
	 safeStrnCpy(  qnmVerStr(  pSci->cfg.iServiceId  ),  pAuthInfo->ver,  mycountof(  pAuthInfo->ver  )  );
	 pAuthInfo->usLangId  =  pQyMc->env.usLangId;		 
	 pAuthInfo->uiDevType  =  pProcInfo->uiDevType;
	 //
	 pAuthInfo->usAuthType  =  pProcInfo->getAuthType(  );//bSupported_devAuth(  )  ?  CONST_authType_dev  :  CONST_authType_logon;		//  2011/02/23
	 //
	 getQwmMacs(  &pQyMc->env,  &pAuthInfo->macsInfo  );
	 len  =  mycountof(  pAuthInfo->pcName  );
	 myGetComputerName(  pAuthInfo->pcName,  &len  );
	 getProcessUsrAndDomain(  &pQyMc->env,  GetCurrentProcessId(  ),  pAuthInfo->osUsrName,  mycountof(  pAuthInfo->osUsrName  ),  pAuthInfo->domainName,  mycountof(  pAuthInfo->domainName  )  );
	 //  2011/08/15
#if  0
	 pAuthInfo->usAppAvLevel  =  qyGetAppAvLevel_qyMc(  );
#endif

	 //
	 _sntprintf(  pProcInfo->cspContainer_qmc,  mycountof(  pProcInfo->cspContainer_qmc  ),  _T(  "%s%u"  ),  CONST_cspContainer_qmc,  GetCurrentProcessId()  );


	 //  2015/07/01
	 pProcInfo->ucCnt_misCnts  =  CONST_maxMisCnts;
	 size  =  pProcInfo->ucCnt_misCnts  *  sizeof(  MIS_CNT  );
	 pProcInfo->pMisCnts  =  (  MIS_CNT  *  )malloc(  size  );
	 if  (  !pProcInfo->pMisCnts  )  goto  errLabel;
	 memset(  pProcInfo->pMisCnts,  0,  size  );
	 //
	 {
		 i  =  0; 
		 //  pProcInfo->misCnts[index].cfg.dynCfg.cnt.usCntPort  =  DEFAULT_qyPort_mis;
		 //  char  *  pServIp  =  "192.168.1.12";  //  CONST_ip_localhost
		 //  safeStrnCpy(  pServIp,  pProcInfo->misCnts[index].cfg.dynCfg.cnt.cntIp,  mycountof(  pProcInfo->misCnts[index].cfg.dynCfg.cnt.cntIp  )  );
#if  0
		 memcpy(  &pProcInfo->misCnts[i].cfg.dynCfg,  &pQyMc->cfg.dynCfg,  sizeof(  pProcInfo->misCnts[i].cfg.dynCfg  )  );
#endif
		 //  2015/07/01
		 MIS_CNT  *  pMisCnt  =  getMisCntByIndex(  0,  pProcInfo,  i  );
		 if  (  !pMisCnt  )  goto  errLabel;
		 memcpy(  &pMisCnt->cfg.dynCfg,  &pQyMc->cfg.dynCfg,  sizeof(  pMisCnt->cfg.dynCfg  )  );
	 }
  
	 //  2015/09/06
	 _sntprintf(  pProcInfo->cfg.mgrQEx.common.name,  mycountof(  pProcInfo->cfg.mgrQEx.common.name  ),  _T(  "mgrQ"  )  );
	 pProcInfo->cfg.mgrQEx.common.uiMaxQNodes  =  CONST_uiMaxQNodes_mgrQ_isCli;
	 _sntprintf(  pProcInfo->cfg.mgrQEx.common.mutexName_prefix,  mycountof(  pProcInfo->cfg.mgrQEx.common.mutexName_prefix  ),  _T(  "qMgrQ_isCli"  )  );
	 pProcInfo->cfg.mgrQEx.common.bUseEvt  =  TRUE;
	 pProcInfo->cfg.mgrQEx.pfQElemNew  =  malloc;
	 pProcInfo->cfg.mgrQEx.pfQElemFree  =  free;
	 //  
	 _sntprintf(  pProcInfo->cfg.displayQ.name,  mycountof(  pProcInfo->cfg.displayQ.name  ),  _T(  "displayQ"  )  );
	 _sntprintf(  pProcInfo->cfg.displayQ.mutexName_prefix,  mycountof(  pProcInfo->cfg.displayQ.mutexName_prefix  ),  _T(  "qDispQ"  )  );
	 pProcInfo->cfg.displayQ.uiMaxCnt_semaTrigger  =  CONST_uiMaxCnt_semaTrigger_displayQ;
	 pProcInfo->cfg.displayQ.uiMaxQNodes  =  CONST_uiMaxQNodes_displayQ;
	 //			  
	 _sntprintf(  pProcInfo->cfg.workQ.name,  mycountof(  pProcInfo->cfg.workQ.name  ),  _T(  "workQ"  )  );
	 _sntprintf(  pProcInfo->cfg.workQ.mutexName_prefix,  mycountof(  pProcInfo->cfg.workQ.mutexName_prefix  ),  _T(  "qWorkQ"  )  );
	 pProcInfo->cfg.workQ.uiMaxCnt_semaTrigger  =  CONST_uiMaxCnt_semaTrigger_workQ;
	 pProcInfo->cfg.workQ.uiMaxQNodes  =  CONST_uiMaxQNodes_workQ;
	 //
	 _sntprintf(  pProcInfo->cfg.schedulerQ.name,  mycountof(  pProcInfo->cfg.schedulerQ.name  ),  _T(  "schedulerQ"  )  );
	 _sntprintf(  pProcInfo->cfg.schedulerQ.mutexName_prefix,  mycountof(  pProcInfo->cfg.schedulerQ.mutexName_prefix  ),  _T(  "qSchQ"  )  );
	 pProcInfo->cfg.schedulerQ.uiMaxCnt_semaTrigger  =  CONST_uiMaxCnt_semaTrigger_schedulerQ;
	 pProcInfo->cfg.schedulerQ.uiMaxQNodes  =  CONST_uiMaxQNodes_schedulerQ;
	 //  2007/07/04	 			  
	 _sntprintf(  pProcInfo->cfg.robotQ.name,  mycountof(  pProcInfo->cfg.robotQ.name  ),  _T(  "robotQ"  )  );
	 _sntprintf(  pProcInfo->cfg.robotQ.mutexName_prefix,  mycountof(  pProcInfo->cfg.robotQ.mutexName_prefix  ),  _T(  "qRobotQ"  )  );
	 pProcInfo->cfg.robotQ.uiMaxCnt_semaTrigger  =  CONST_uiMaxCnt_semaTrigger_robotQ;
	 pProcInfo->cfg.robotQ.uiMaxQNodes  =  CONST_uiMaxQNodes_robotQ;
	 //
	 _sntprintf(  pProcInfo->cfg.mediaQ.name,  mycountof(  pProcInfo->cfg.mediaQ.name  ),  _T(  "mediaQ"  )  );
	 _sntprintf(  pProcInfo->cfg.mediaQ.mutexName_prefix,  mycountof(  pProcInfo->cfg.mediaQ.mutexName_prefix  ),  _T(  "qMediaQ"  )  );
	 pProcInfo->cfg.mediaQ.uiMaxQNodes  =  pProcInfo->cfg.envVar.usMaxQNodes_mediaQ;
	 //
	 //  2008/04/25
	 _sntprintf(  pProcInfo->cfg.realTimeMediaQ.name,  mycountof(  pProcInfo->cfg.realTimeMediaQ.name  ),  _T(  "rtMediaQ"  )  );
	 _sntprintf(  pProcInfo->cfg.realTimeMediaQ.mutexName_prefix,  mycountof(  pProcInfo->cfg.realTimeMediaQ.mutexName_prefix  ),  _T(  "qRtMediaQ"  )  );
	 pProcInfo->cfg.realTimeMediaQ.uiMaxQNodes  =  pProcInfo->cfg.envVar.usMaxQNodes_rtMediaQ;
	 
	 //  2016/12/26
	 _sntprintf(  pProcInfo->cfg.rtOpQ.name,  mycountof(  pProcInfo->cfg.rtOpQ.name  ),  _T(  "rtOpQ"  )  );
	 _sntprintf(  pProcInfo->cfg.rtOpQ.mutexName_prefix,  mycountof(  pProcInfo->cfg.rtOpQ.mutexName_prefix  ),  _T(  "qRtOpQ"  )  );
	 pProcInfo->cfg.rtOpQ.uiMaxQNodes  =  pProcInfo->cfg.envVar.usMaxQNodes_rtOpQ;

	 //
	 //  2007/07/04
	 //
	 _sntprintf(  pProcInfo->cfg.processQ_robot.name,  mycountof(  pProcInfo->cfg.processQ_robot.name  ),  _T(  "processQ_robot"  )  );
	 pProcInfo->cfg.processQ_robot.uiMaxQNodes  =  CONST_uiMaxQNodes_processQ_robot;
	 //
	 _sntprintf(  pProcInfo->cfg.processQ_media.name,  mycountof(  pProcInfo->cfg.processQ_media.name  ),  _T(  "processQ_media"  )  );
	 pProcInfo->cfg.processQ_media.uiMaxQNodes  =  CONST_uiMaxQNodes_processQ_media;
	 
	 //  2008/05/23
	 _sntprintf(  pProcInfo->cfg.outputQ_toMix_audio.name,  mycountof(  pProcInfo->cfg.outputQ_toMix_audio.name  ),  _T(  "output_mixQ_a"  )  );
	 _sntprintf(  pProcInfo->cfg.outputQ_toMix_audio.mutexName_prefix,  mycountof(  pProcInfo->cfg.outputQ_toMix_audio.mutexName_prefix  ),  _T(  "qoutput_mixQ_a"  )  );
	 if  (  isMem512(  pQyMc  )  )  {
		 pProcInfo->cfg.outputQ_toMix_audio.uiMaxQNodes  =  CONST_uiMaxQNodes_outputQ_toMix_audio_256;
		 }
	 else  if  (  bLikeXp(  )  )  {
		       pProcInfo->cfg.outputQ_toMix_audio.uiMaxQNodes  =  CONST_uiMaxQNodes_outputQ_toMix_audio_xp;
			   }
	 else  {
		   pProcInfo->cfg.outputQ_toMix_audio.uiMaxQNodes  =  CONST_uiMaxQNodes_outputQ_toMix_audio;				
	 }
	 //  2009/07/26
	 _sntprintf(  pProcInfo->cfg.outputQ_toMosaic_video.name,  mycountof(  pProcInfo->cfg.outputQ_toMosaic_video.name  ),  _T(  "output_mosaicQ_v"  )  );
	 _sntprintf(  pProcInfo->cfg.outputQ_toMosaic_video.mutexName_prefix,  mycountof(  pProcInfo->cfg.outputQ_toMosaic_video.mutexName_prefix  ),  _T(  "qOutput_mosaicQ_v"  )  );
	 pProcInfo->cfg.outputQ_toMosaic_video.uiMaxQNodes  =  CONST_uiMaxQNodes_outputQ_toMosaic_video;

	 //	 2008/04/17
	 _sntprintf(  pProcInfo->cfg.playSoundQ.name,  mycountof(  pProcInfo->cfg.playSoundQ.name  ),  _T(  "playSoundQ"  )  );
	 _sntprintf(  pProcInfo->cfg.playSoundQ.mutexName_prefix,  mycountof(  pProcInfo->cfg.playSoundQ.mutexName_prefix  ),  _T(  "playSoundQ"  )  );
	 pProcInfo->cfg.playSoundQ.uiMaxQNodes  =  pProcInfo->cfg.envVar.usMaxQNodes_playSoundQ;	//  isMem512(  )  ?  CONST_uiMaxQNodes_playSoundQ_256  :  CONST_uiMaxQNodes_playSoundQ;
	 //  2009/05/02
	 _sntprintf(  pProcInfo->cfg.playVideoQ.name,  mycountof(  pProcInfo->cfg.playVideoQ.name  ),  _T(  "playVideoQ"  )  );
	 _sntprintf(  pProcInfo->cfg.playVideoQ.mutexName_prefix,  mycountof(  pProcInfo->cfg.playVideoQ.mutexName_prefix  ),  _T(  "playVideoQ"  )  );
	 pProcInfo->cfg.playVideoQ.uiMaxQNodes  =  pProcInfo->cfg.envVar.usMaxQNodes_playVideoQ;	//  isMem512(  )  ?  CONST_uiMaxQNodes_playVideoQ_256  :  CONST_uiMaxQNodes_playVideoQ;
	 //  2009/07/25
	 _sntprintf(  pProcInfo->cfg.displayVideoQ.name,  mycountof(  pProcInfo->cfg.displayVideoQ.name  ),  _T(  "displayVQ"  )  );
	 _sntprintf(  pProcInfo->cfg.displayVideoQ.mutexName_prefix,  mycountof(  pProcInfo->cfg.displayVideoQ.mutexName_prefix  ),  _T(  "displayVQ"  )  );
	 pProcInfo->cfg.displayVideoQ.uiMaxQNodes  =  pProcInfo->cfg.envVar.usMaxQNodes_displayVideoQ;	//  CONST_uiMaxQNodes_displayVideoQ;

	 //  2011/12/09
#if  0
	 _sntprintf(  pProcInfo->cfg.preTransformQ.name,  mycountof(  pProcInfo->cfg.preTransformQ.name  ),  _T(  "preTransQ"  )  );
	 _sntprintf(  pProcInfo->cfg.preTransformQ.mutexName_prefix,  mycountof(  pProcInfo->cfg.preTransformQ.mutexName_prefix  ),  _T(  "preTransQ"  )  );
	 pProcInfo->cfg.preTransformQ.uiMaxQNodes  =  CONST_uiMaxQNodes_preTransformQ;
#endif
	 //  2009/05/12
	 //
	 TCHAR  tName[128];  //  2015/05/23
	 //_sntprintf(  tName,  mycountof(  tName  ),  _T(  "transQ-%d"  ),  GetCurrentProcessId(  )  );
	  getTransformQName(  tName,  mycountof(  tName  )  );
	 _sntprintf(  pProcInfo->cfg.transformQ.name,  mycountof(  pProcInfo->cfg.transformQ.name  ),  _T(  "%s"  ),  tName  );
	 _sntprintf(  pProcInfo->cfg.transformQ.mutexName_prefix,  mycountof(  pProcInfo->cfg.transformQ.mutexName_prefix  ),  _T(  "%s"  ),  tName  );
	 //
	 pProcInfo->cfg.transformQ.uiMaxQNodes  =  isMem512(  pQyMc  )  ?  CONST_uiMaxQNodes_transformQ_256  :  CONST_uiMaxQNodes_transformQ;

	 //
	 _sntprintf(pProcInfo->cfg.mixQ.name, mycountof(pProcInfo->cfg.mixQ.name), _T("mixQ"));
	 _sntprintf(pProcInfo->cfg.mixQ.mutexName_prefix, mycountof(pProcInfo->cfg.mixQ.mutexName_prefix), _T("mixQ"));
	 pProcInfo->cfg.mixQ.uiMaxQNodes = CONST_uiMaxQNodes_mixQ;

	 //  
	 _sntprintf(  pProcInfo->cfg.aecQ.name,  mycountof(  pProcInfo->cfg.aecQ.name  ),  _T(  "aecQ"  )  );
	 _sntprintf(  pProcInfo->cfg.aecQ.mutexName_prefix,  mycountof(  pProcInfo->cfg.aecQ.mutexName_prefix  ),  _T(  "aecQ"  )  );
	 pProcInfo->cfg.aecQ.uiMaxQNodes  =  CONST_uiMaxQNodes_aecQ;
	 //
	 _sntprintf(  pProcInfo->cfg.aecPlayQ.name,  mycountof(  pProcInfo->cfg.aecPlayQ.name  ),  _T(  "aecPlayQ"  )  );
	 _sntprintf(  pProcInfo->cfg.aecPlayQ.mutexName_prefix,  mycountof(  pProcInfo->cfg.aecPlayQ.mutexName_prefix  ),  _T(  "aecPlayQ"  )  );
	 pProcInfo->cfg.aecPlayQ.uiMaxQNodes  =  CONST_uiMaxQNodes_aecPlayQ;



	 //  2017/01/29
	 _sntprintf(  pProcInfo->cfg.appQ.name,  mycountof(  pProcInfo->cfg.appQ.name  ),  _T(  "appQ"  )  );
	 _sntprintf(  pProcInfo->cfg.appQ.mutexName_prefix,  mycountof(  pProcInfo->cfg.appQ.mutexName_prefix  ),  _T(  "appQ"  )  );
	 pProcInfo->cfg.appQ.uiMaxQNodes  =  CONST_uiMaxQNodes_appQ;


	 //  2011/12/04
	 _sntprintf(  pProcInfo->cfg.vppQ.name,  mycountof(  pProcInfo->cfg.vppQ.name  ),  _T(  "vppQ"  )  );
	 _sntprintf(  pProcInfo->cfg.vppQ.mutexName_prefix,  mycountof(  pProcInfo->cfg.vppQ.mutexName_prefix  ),  _T(  "vppQ"  )  );
	 pProcInfo->cfg.vppQ.uiMaxQNodes  =  CONST_uiMaxQNodes_vppQ;

	 _sntprintf(pProcInfo->cfg.toSaveIcQ.name, mycountof(pProcInfo->cfg.toSaveIcQ.name), _T("saveIC"));
	 _sntprintf(pProcInfo->cfg.toSaveIcQ.mutexName_prefix, mycountof(pProcInfo->cfg.toSaveIcQ.mutexName_prefix), _T("saveIC"));
	 pProcInfo->cfg.toSaveIcQ.uiMaxQNodes = isMem512(pQyMc) ? CONST_uiMaxQNodes_toSaveIcQ_256 : CONST_uiMaxQNodes_toSaveIcQ;

	 //  2011/01/21
	 _sntprintf(  pProcInfo->cfg.toShareAudioQ.name,  mycountof(  pProcInfo->cfg.toShareAudioQ.name  ),  _T(  "shareAQ"  )  );
	 _sntprintf(  pProcInfo->cfg.toShareAudioQ.mutexName_prefix,  mycountof(  pProcInfo->cfg.toShareAudioQ.mutexName_prefix  ),  _T(  "shareAQ"  )  );
	 pProcInfo->cfg.toShareAudioQ.uiMaxQNodes  =  isMem512(  pQyMc  )  ?  CONST_uiMaxQNodes_toShareAudioQ_256  :  CONST_uiMaxQNodes_toShareAudioQ;
	 //  2009/05/12
	 _sntprintf(  pProcInfo->cfg.toShareVideoQ.name,  mycountof(  pProcInfo->cfg.toShareVideoQ.name  ),  _T(  "shareVQ"  )  );
	 _sntprintf(  pProcInfo->cfg.toShareVideoQ.mutexName_prefix,  mycountof(  pProcInfo->cfg.toShareVideoQ.mutexName_prefix  ),  _T(  "shareVQ"  )  );
	 pProcInfo->cfg.toShareVideoQ.uiMaxQNodes  =  isMem512(  pQyMc  )  ?  CONST_uiMaxQNodes_toShareVideoQ_256  :  CONST_uiMaxQNodes_toShareVideoQ;

	 //  2011/12/06
	 _sntprintf(  pProcInfo->cfg.toShareVideo_postQ.name,  mycountof(  pProcInfo->cfg.toShareVideo_postQ.name  ),  _T(  "shareVPostQ"  )  );
	 _sntprintf(  pProcInfo->cfg.toShareVideo_postQ.mutexName_prefix,  mycountof(  pProcInfo->cfg.toShareVideo_postQ.mutexName_prefix  ),  _T(  "shareVPostQ"  )  );
	 pProcInfo->cfg.toShareVideo_postQ.uiMaxQNodes  =  CONST_uiMaxQNodes_toShareVideo_postQ;

	 //  2009/06/17
	 _sntprintf(  pProcInfo->cfg.dispatchQ.name,  mycountof(  pProcInfo->cfg.dispatchQ.name  ),  _T(  "dispQ"  )  );
	 _sntprintf(  pProcInfo->cfg.dispatchQ.mutexName_prefix,  mycountof(  pProcInfo->cfg.dispatchQ.mutexName_prefix  ),  _T(  "dispQ"  )  );
	 pProcInfo->cfg.dispatchQ.uiMaxQNodes  =  CONST_uiMaxQNodes_dispatchQ;
 
	 //  2016/03/15
	 _sntprintf(  pProcInfo->cfg.talkerThreadQ.name,  mycountof(  pProcInfo->cfg.talkerThreadQ.name  ),  _T(  "talkerThreadQ"  )  );
	 _sntprintf(  pProcInfo->cfg.talkerThreadQ.mutexName_prefix,  mycountof(  pProcInfo->cfg.talkerThreadQ.mutexName_prefix  ),  _T(  "talkerThreadQ"  )  );
	 pProcInfo->cfg.talkerThreadQ.uiMaxQNodes  =  CONST_uiMaxQNodes_talkerThreadQ;

	 //  2016/06/15
	 _sntprintf(  pProcInfo->cfg.shareDynBmpsQ.name,  mycountof(  pProcInfo->cfg.shareDynBmpsQ.name  ),  _T(  "shareDynBmpsQ"  )  );
	 _sntprintf(  pProcInfo->cfg.shareDynBmpsQ.mutexName_prefix,  mycountof(  pProcInfo->cfg.shareDynBmpsQ.mutexName_prefix  ),  _T(  "shareDynBmpsQ"  )  );
	 pProcInfo->cfg.shareDynBmpsQ.uiMaxQNodes  =  CONST_uiMaxQNodes_shareDynBmpsQ;
	 
	 //
	 _sntprintf(  pProcInfo->cfg.guestQ.name,  mycountof(  pProcInfo->cfg.guestQ.name  ),  _T(  "guestQ"  )  );
	 pProcInfo->cfg.guestQ.uiMaxQNodes  =  isWinCe(  )  ?  CONST_uiMaxQNodes_guestQ_ce  :  CONST_uiMaxQNodes_guestQ;
	 //
#if  0
	 _sntprintf(  pProcInfo->cfg.phoneMsgrQ.name,  mycountof(  pProcInfo->cfg.phoneMsgrQ.name  ),  _T(  "phoneMsgrQ"  )  );
	 _sntprintf(  pProcInfo->cfg.phoneMsgrQ.mutexName_prefix,  mycountof(  pProcInfo->cfg.phoneMsgrQ.mutexName_prefix  ),  _T(  "qyMcPhoneMsgrQ"  )  );
	 pProcInfo->cfg.phoneMsgrQ.uiMaxQNodes  =  isWinCe(  )  ?  CONST_uiMaxQNodes_phoneMsgrQ_ce  :  CONST_uiMaxQNodes_phoneMsgrQ;
#endif
	 //
	 _sntprintf(  pProcInfo->cfg.dynBmpQ.name,  mycountof(  pProcInfo->cfg.dynBmpQ.name  ),  _T(  "dynBmpQ"  )  );
	 _sntprintf(  pProcInfo->cfg.dynBmpQ.mutexName_prefix,  mycountof(  pProcInfo->cfg.dynBmpQ.mutexName_prefix  ),  _T(  "dynBmpQ"  )  );
	 pProcInfo->cfg.dynBmpQ.uiMaxQNodes  =  CONST_uiMaxQNodes_dynBmpQ;

	 //
	 lstrcpyn(  pProcInfo->cfg.mutexName_syncSendAv,  _T(  "qySyncSendAv"  ),  mycountof(  pProcInfo->cfg.mutexName_syncSendAv  )  );
	 lstrcpyn(  pProcInfo->cfg.mutexName_syncActiveMem_prefix1,  _T(  "qySyncAct"  ),  mycountof(  pProcInfo->cfg.mutexName_syncActiveMem_prefix1  )  );	//  2009/05/31
	 lstrcpyn(  pProcInfo->cfg.mutexName_syncStartAv,  _T(  "qyStartAv"  ),  mycountof(  pProcInfo->cfg.mutexName_syncStartAv  )  );					//  2010/09/10

	 //
	 //  if  (  initGenericQ((  &pProcInfo->cfg.mgrQ,  mallocMemory,  NULL,  0,  0,  freeMemory,  NULL,  NULL,  &pProcInfo->mgrQ  )  )  goto  errLabel; 
	 //  2015/09/06
	 pProcInfo->cfg.mgrQEx.pfQElemNewEx  =  mallocMemory;
	 pProcInfo->cfg.mgrQEx.pfQElemFreeEx  =  freeMemory;
	 if  (  initGenericQ(  &pProcInfo->cfg.mgrQEx,  &pProcInfo->mgrQ  )  )  goto  errLabel;
	 //
	 //  2007/07/04	 			  
	 if  (  initGenericQ(  &pProcInfo->cfg.robotQ,  mymalloc,  0,  0,  myfree,  NULL,  &pProcInfo->robotQ  )  )  goto  errLabel;
	 if  (  initGenericQ(  &pProcInfo->cfg.displayQ,  mymalloc,  0,  0,  myfree,  NULL,  &pProcInfo->displayQ  )  )  goto  errLabel;
	 if  (  initGenericQ(  &pProcInfo->cfg.workQ,  mymalloc,  0,  0,  myfree,  NULL,  &pProcInfo->workQ  )  )  goto  errLabel;
	 if  (  initGenericQ(  &pProcInfo->cfg.schedulerQ,  mymalloc,  0,  0,  myfree,  NULL,  &pProcInfo->schedulerQ  )  )  goto  errLabel;
	 
	 if  (  initQyQ2(  &pProcInfo->cfg.mediaQ,  &pQyMc->cfg.rwLockParam,  1,  NULL,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  NULL,  &pProcInfo->mediaQ2  )  )  goto  errLabel;
	 if  (  initQyQ2(  &pProcInfo->cfg.realTimeMediaQ,  &pQyMc->cfg.rwLockParam,  1,  NULL,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  NULL,  &pProcInfo->realTimeMediaQ2  )  )  goto  errLabel;

	 //  2016/12/26
	 if  (  initQyQ2(  &pProcInfo->cfg.rtOpQ,  &pQyMc->cfg.rwLockParam,  1,  NULL,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  NULL,  &pProcInfo->rtOpQ2  )  )  goto  errLabel;
	 
	 //
	 //  ×¢Òâ£º ÏÂÃæµÄ5±íÊ¾×î¶àÓÐ5¸ö²¢·¢Ïß³Ì¿ÉÒÔÓÃ¡£Ò²Ðí²»¹»ÄØ¡£2008/05/18
	 //
#if  0
	 if  (  !pProcInfo->processQ_robot.bSetQInfo(  _T(  "mcSyncRobot"  ),  5,  10000,  10000,  10000,  10000  )  )  goto  errLabel;
	 if  (  pProcInfo->processQ_robot.initQ(  &pProcInfo->cfg.processQ_robot,  mallocMemory,  mymalloc,  initMisMsg,  exitMisMsg,  freeMemory,  myfree  )  )  goto  errLabel;
#endif
	 //
	 pProcInfo->processQ_media.m_var.pQyMc = pQyMc;
	 if  (  !pProcInfo->processQ_media.bSetQInfo(  _T(  "mcSyncMedia"  ),  10,  10000,  10000,  10000,  10000  )  )  goto  errLabel;
	 if  (  pProcInfo->processQ_media.initQ(  &pProcInfo->cfg.processQ_media,  pQyMc->cfg.rwLockParam,  mallocMemory,  mymalloc,  initMisMsg,  exitMisMsg,  freeMemory,  myfree  )  )  goto  errLabel;
	
	 #ifdef  __DEBUG__
			 //pProcInfo->processQ_robot.m_var.dwThreadId_gui  =  pQyMc->gui.dwThreadId;
			 pProcInfo->processQ_media.m_var.dwThreadId_gui  =  pQyMc->gui.ctx_gui_thread.dwThreadId9;
			 pProcInfo->processQ_media.m_var.dwThreadId_console=pQyMc->gui.ctx_gui_thread.dwThreadId9;
	 #endif

	 //  2010/04/22
#ifdef  __NOTSUPPORT_DB__
	 if  (  initGenericQ(  _T(  "memTaskQ"  ),  _T(  "memTaskQ"  ),  0,  2000,  mymalloc,  myfree,  &pProcInfo->memTaskQ  )  )  goto  errLabel;
#endif

	 //
	 if  (  initGenericQ(  _T(  "ImMsgLogQ"  ),  _T(  "ImMsgLogQ"  ),  0,  pProcInfo->cfg.envVar.usMaxQNodes_imMsgLogQ,  mymalloc,  myfree,  &pProcInfo->imMsgLogQ  )  )  goto  errLabel;

	 //
	 //  2008/02/01
#if  0
	 if  (  initGenericQ(  &pProcInfo->cfg.phoneMsgrQ,  mymalloc,  0,  0,  myfree,  NULL,  &pProcInfo->phoneMsgrQ  )  )  goto  errLabel;
	 if  (  pProcInfo->cfg.phoneMsgrQ.uiMaxQNodes  )  {
		 if  (  !(  pProcInfo->ppPhoneMsgrs_sortedByDevIdStr  =  (  void  **  )mymalloc(  sizeof(  void  *  )  *  pProcInfo->cfg.phoneMsgrQ.uiMaxQNodes  )  )  )  goto  errLabel;
		 if  (  !(  pProcInfo->ppPhoneMsgrs_sortedByIdInfo  =  (  void  **  )mymalloc(  sizeof(  void  *  )  *  pProcInfo->cfg.phoneMsgrQ.uiMaxQNodes  )  )  )  goto  errLabel;
	 }
#endif


	 //
	 //for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  
	 for  (  i  =  0;  i  <  pProcInfo->ucCnt_misCnts;  i  ++  )  
	 {
		  MIS_CNT  *  pMisCnt  =  getMisCntByIndex(  0,  pProcInfo,  i  );//&pProcInfo->misCnts[i];
		  if  (  !pMisCnt  )  continue;

		  //
		  pMisCnt->pProcInfoParam  =  pProcInfo;	//  2009/09/07

		  //
		  pMisCnt->channels[0].uiType  =  CONST_channelType_talking;
		  pMisCnt->channels[1].uiType  =  CONST_channelType_robot;
		  pMisCnt->channels[2].uiType  =  CONST_channelType_media;
		  pMisCnt->channels[3].uiType  =  CONST_channelType_realTimeMedia;	//  2008/04/17
		  pMisCnt->channels[4].uiType  =  CONST_channelType_rtOp;	//  2008/04/17
		  
		  //
		  if  (  pMisCnt->cfg.dynCfg.cnt.usCntPort  )  {
			  
			  //  2007/06/03
			  pMisCnt->cfg.iObjQType  =  CONST_objQType_misClient;
			  _sntprintf(  pMisCnt->cfg.mutexName_syncQmObjQ,  mycountof(  pMisCnt->cfg.mutexName_syncQmObjQ  ),  _T(  "%s%u"  ),  DEFAULT_mutexName_syncQmObjQ_client,  pSci->cfg.iServiceId  );	//  2007/01/16
			  _sntprintf(  pMisCnt->cfg.semaphoreName_syncQmObjQ,  mycountof(  pMisCnt->cfg.semaphoreName_syncQmObjQ  ),  _T(  "%s%u"  ),  DEFAULT_semaphoreName_syncQmObjQ_client,  pSci->cfg.iServiceId  );	//  2007/01/16
			  pMisCnt->cfg.uiMaxCnt_semaphore_qmObjQ  =  CONST_maxCnt_sema_syncQmObjQ;

			  //
			  //  pMisCnt->cfg.uiMaxCnt_semaTrigger_input	=	CONST_uiMaxCnt_semaTrigger_input;
			  //
			  //  2008/04/02			 
			  _sntprintf(  pMisCnt->cfg.inCacheQ.name,  mycountof(  pMisCnt->cfg.inCacheQ.name  ),  _T(  "inCacheQ%u"  ),  i  );
			  _sntprintf(  pMisCnt->cfg.inCacheQ.mutexName_prefix,  mycountof(  pMisCnt->cfg.inCacheQ.mutexName_prefix  ),  _T(  "qmcInCacheQ%u"  ),  i  );  
			  pMisCnt->cfg.inCacheQ.uiMaxQNodes  =  CONST_uiMaxQNodes_inCacheQ_isCli;
			  //
#if  0
			  _sntprintf(  pMisCnt->cfg.inputQ.name,  mycountof(  pMisCnt->cfg.inputQ.name  ),  _T(  "inputQ%u"  ),  i  );
			  _sntprintf(  pMisCnt->cfg.inputQ.mutexName_prefix,  mycountof(  pMisCnt->cfg.inputQ.mutexName_prefix  ),  _T(  "qmcInputQ%u"  ),  i  );
			  pMisCnt->cfg.inputQ.uiMaxQNodes  =  CONST_uiMaxQNodes_inputQ_isCli;
#endif
			  
			  //
			  _sntprintf(  pMisCnt->cfg.toSendQ.name,  mycountof(  pMisCnt->cfg.toSendQ.name  ),  _T(  "toSendQ%u"  ),  i  );
			  _sntprintf(  pMisCnt->cfg.toSendQ.mutexName_prefix,  mycountof(  pMisCnt->cfg.toSendQ.mutexName_prefix  ),  _T(  "qmcToSendQ%u"  ),  i  );
			  if  (  isMem512(  pQyMc  )  )  {
				  //  pMisCnt->cfg.toSendQ.uiMaxCnt_semaTrigger  =  CONST_uiMaxCnt_semaTrigger_toSendQ_256;
				  pMisCnt->cfg.toSendQ.uiMaxQNodes  =  CONST_uiMaxQNodes_toSendQ_256;
				  }
			  else  if  (  bLikeXp(  )  )  {
						//  pMisCnt->cfg.toSendQ.uiMaxCnt_semaTrigger  =  CONST_uiMaxCnt_semaTrigger_toSendQ_xp;
						pMisCnt->cfg.toSendQ.uiMaxQNodes  =  CONST_uiMaxQNodes_toSendQ_xp;
					    }
			  else  {
				    //  pMisCnt->cfg.toSendQ.uiMaxCnt_semaTrigger  =  CONST_uiMaxCnt_semaTrigger_toSendQ;				  
					pMisCnt->cfg.toSendQ.uiMaxQNodes  =  CONST_uiMaxQNodes_toSendQ;		
			  }
			  //
			  _sntprintf(  pMisCnt->cfg.outputQ.name,  mycountof(  pMisCnt->cfg.outputQ.name  ),  _T(  "outputQ%u"  ),  i  );
			  _sntprintf(  pMisCnt->cfg.outputQ.mutexName_prefix,  mycountof(  pMisCnt->cfg.outputQ.mutexName_prefix  ),  _T(  "qmcOutputQ%u"  ),  i  );
			  if  (  isMem512(  pQyMc  )  )  {
				  //  pMisCnt->cfg.outputQ.uiMaxCnt_semaTrigger  =  CONST_uiMaxCnt_semaTrigger_outputQ_256;
				  pMisCnt->cfg.outputQ.uiMaxQNodes  =  CONST_uiMaxQNodes_outputQ_256;
				  }
			  else  if  (  bLikeXp(  )  )  {
						//  pMisCnt->cfg.outputQ.uiMaxCnt_semaTrigger  =  CONST_uiMaxCnt_semaTrigger_outputQ_xp;
						pMisCnt->cfg.outputQ.uiMaxQNodes  =  CONST_uiMaxQNodes_outputQ_xp;
		  			    }
			  else  {
				     //  pMisCnt->cfg.outputQ.uiMaxCnt_semaTrigger  =  CONST_uiMaxCnt_semaTrigger_outputQ;
					 pMisCnt->cfg.outputQ.uiMaxQNodes  =  CONST_uiMaxQNodes_outputQ;
			  }
			  //  2007/07/04
			  //
			  _sntprintf(  pMisCnt->cfg.talkingFriendQ.name,  mycountof(  pMisCnt->cfg.talkingFriendQ.name  ),  _T(  "talkingFriendQ"  )  );
			  _sntprintf(  pMisCnt->cfg.talkingFriendQ.mutexName_prefix,  mycountof(  pMisCnt->cfg.talkingFriendQ.mutexName_prefix  ),  _T(  "qyMcTalkQ%u"  ),  i  );
			  pMisCnt->cfg.talkingFriendQ.uiMaxQNodes  =  CONST_uiMaxQNodes_talkingFriendQ;
			  //
			  _sntprintf(  pMisCnt->cfg.recentFriendQ.name,  mycountof(  pMisCnt->cfg.recentFriendQ.name  ),  _T(  "recentFriendQ"  )  );
			  _sntprintf(  pMisCnt->cfg.recentFriendQ.mutexName_prefix,  mycountof(  pMisCnt->cfg.recentFriendQ.mutexName_prefix  ),  _T(  "qyMcRecentQ%u"  ),  i  );
			  pMisCnt->cfg.recentFriendQ.uiMaxQNodes  =  CONST_uiMaxQNodes_recentFriendQ;

			  //  2007/06/06
			  pMisCnt->cfg.usIntervalInS_getIntervalParams  =  CONST_usIntervalInS_getIntervalParams;
			  //
			  pMisCnt->cfg.usMaxMsgrRecentFriends  =  pProcInfo->cfg.usMaxMsgrRecentFriends;
			  pMisCnt->cfg.usIntervalInS_refreshRecentFriends  =  CONST_usIntervalInS_refreshRecentFriends;
			  pMisCnt->cfg.usIntervalInS_refreshContactList  =  CONST_usIntervalInS_refreshContactList;
			  //
			  pMisCnt->cfg.usMaxContactUpdateInfosPerSnd_grp  =  CONST_maxContactUpdateInfos_grp;	//  2014/02/06.	CONST_usMaxContactUpdateInfosPerSnd_isCli;			  	
			  pMisCnt->cfg.usMaxContactUpdateInfosPerSnd_grpMem  =  CONST_maxContactUpdateInfos_grpMem;	//  2014/02/06.	CONST_usMaxContactUpdateInfosPerSnd_isCli;
			  pMisCnt->cfg.usMaxContactUpdateInfosPerSnd_contact  =  CONST_maxContactUpdateInfos_contact;	//  2014/02/06.	CONST_usMaxContactUpdateInfosPerSnd_isCli;

			  //
			  pMisCnt->cfg.usIntervalInS_tryToReg  =  CONST_usIntervalInS_tryToReg;
			  pMisCnt->cfg.usIntervalInS_tryToSndDevInfo  =  CONST_usIntervalInS_tryToSndDevInfo;	//  2007/

			  //  2007/06/27
			  _sntprintf(  pMisCnt->cfg.mutexNamePrefix_syncTask,  mycountof(  pMisCnt->cfg.mutexNamePrefix_syncTask  ),  _T(  "%s%s"  ),  DEFAULT_mutexNamePrefix_syncTask,  pMisCnt->cfg.misServName  );

			  //  2007/07/16
			  //  


			  /////////////////
			  //
			  //


			  //  2007/06/03
			  if  (  !(  pMisCnt->pObjQ  =  mymalloc(  sizeof(  QM_OBJQ  )  )  )  )  {		//  2007/04/01
				  traceLogA(  (char*)  "initVar_misClient(  ):  malloc for objQ failed"  );  
				  goto  errLabel;
			  }
			  memset(  pMisCnt->pObjQ,  0,  sizeof(  QM_OBJQ  )  );
			  if  (  initQmObjQ(  0,  &pQyMc->licenseCtx,  pMisCnt->cfg.iObjQType,  CQyString(  pMisCnt->cfg.misServName  )  +  _T(  "qmObjQ"  ),  pMisCnt->cfg.mutexName_syncQmObjQ,  pMisCnt->cfg.semaphoreName_syncQmObjQ,  pMisCnt->cfg.uiMaxCnt_semaphore_qmObjQ,  myCompare_misClient,  (  PF_commonHandler  )exitQMem_misClient,  (  PF_fillQmObjMemInfo  )fillQmObjMemInfo_misClient,  (  PF_commonHandler  )tmp_addToQmObjQ_misClient,  (  QM_OBJQ  *  )pMisCnt->pObjQ  )  )  {		//  2006/12/07
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  "initQmObjQ failed"  ),  _T(  ""  )  ); 
				  traceLogA(  (char*)  "initQmObjQ(  ) failed."  );  
				  goto  errLabel;
			  }	 
			  (  (  QM_OBJQ  *  )pMisCnt->pObjQ  )->pfPrintQ  =  (  PF_commonHandler  )printQmObjQ_isClient;
			  pMisCnt->ucbQmObjQInited  =  TRUE;
			  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  pMisCnt->cfg.misServName,  _T(  "initQmObjQ OK"  ),  _T(  ""  )  ); 

			  //
			  int				j;
			  GENERIC_Q_CFG		tmpqCfg;

			  for  (  j  =  0;  j  <  mycountof(  pMisCnt->channels  );  j  ++  )  {
				   MIS_CHANNEL	*	pChannel  =  &pMisCnt->channels[j];

				   //  2016/09/09
				   pChannel->pMisCnt  =  pMisCnt;
				   
				   //  
				   memcpy(  &tmpqCfg,  &pMisCnt->cfg.inCacheQ,  sizeof(  tmpqCfg  )  );
				   _sntprintf(  tmpqCfg.name,  mycountof(  tmpqCfg.name  ),  _T(  "%s-%u"  ),  tmpqCfg.name,  j  );
				   _sntprintf(  tmpqCfg.mutexName_prefix,  mycountof(  tmpqCfg.mutexName_prefix  ),  _T(  "%s-%u"  ),  tmpqCfg.mutexName_prefix,  j  );
				   if  (  initGenericQ(  &tmpqCfg,  mymalloc,  0,  0,  myfree,  NULL,  &pChannel->inCacheQ  )  )  goto  errLabel;  		  

				   //  2015/09/09
#if  0
				   memcpy(  &tmpqCfg,  &pMisCnt->cfg.inputQ,  sizeof(  tmpqCfg  )  );
				   _sntprintf(  tmpqCfg.name,  mycountof(  tmpqCfg.name  ),  _T(  "%s-%u"  ),  tmpqCfg.name,  j  );
				   _sntprintf(  tmpqCfg.mutexName_prefix,  mycountof(  tmpqCfg.mutexName_prefix  ),  _T(  "%s-%u"  ),  tmpqCfg.mutexName_prefix,  j  );
				   //  if  (  initGenericQ(  &tmpqCfg,  mymalloc,  0,  0,  myfree,  &pChannel->toSendQ  )  )  goto  errLabel;
				   if  (  initQyQ2(  &tmpqCfg,  &pQyMc->cfg.rwLockParam,  1,  NULL,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  NULL,  &pChannel->inputQ2  )  )  goto  errLabel;
#endif

				   //
				   memcpy(  &tmpqCfg,  &pMisCnt->cfg.toSendQ,  sizeof(  tmpqCfg  )  );
				   _sntprintf(  tmpqCfg.name,  mycountof(  tmpqCfg.name  ),  _T(  "%s-%u"  ),  tmpqCfg.name,  j  );
				   _sntprintf(  tmpqCfg.mutexName_prefix,  mycountof(  tmpqCfg.mutexName_prefix  ),  _T(  "%s-%u"  ),  tmpqCfg.mutexName_prefix,  j  );
				   //  if  (  initGenericQ(  &tmpqCfg,  mymalloc,  0,  0,  myfree,  &pChannel->toSendQ  )  )  goto  errLabel;
				   if  (  initQyQ2(  &tmpqCfg,  &pQyMc->cfg.rwLockParam,  1,  NULL,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  NULL,  &pChannel->toSendQ2  )  )  goto  errLabel;
				   
				   //
				   memcpy(  &tmpqCfg,  &pMisCnt->cfg.outputQ,  sizeof(  tmpqCfg  )  );
				   _sntprintf(  tmpqCfg.name,  mycountof(  tmpqCfg.name  ),  _T(  "%s-%u"  ),  tmpqCfg.name,  j  );
				   _sntprintf(  tmpqCfg.mutexName_prefix,  mycountof(  tmpqCfg.mutexName_prefix  ),  _T(  "%s-%u"  ),  tmpqCfg.mutexName_prefix,  j  );
				   //  if  (  initGenericQ(  &tmpqCfg,  mymalloc,  0,  0,  myfree,  &pChannel->outputQ  )  )  goto  errLabel;  
				   if  (  initQyQ2(  &tmpqCfg,  &pQyMc->cfg.rwLockParam,  1,  NULL,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  NULL,  &pChannel->outputQ2  )  )  goto  errLabel;


			  }
			  //
			  if  (  initGenericQ(  &pMisCnt->cfg.talkingFriendQ,  mymalloc,  0,  0,  myfree,  NULL,  &pMisCnt->talkingFriendQ  )  )  goto  errLabel;
			  if  (  initGenericQ(  &pMisCnt->cfg.recentFriendQ,  mymalloc,  0,  0,  myfree,  NULL,  &pMisCnt->recentFriendQ  )  )  goto  errLabel;


			  //  2007/08/07, ¸³ÎÒµÄÈ±Ê¡Öµ
			  lstrcpyn(  pMisCnt->displayName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_objIdStr_me  ),  mycountof(  pMisCnt->displayName  )  );

		  }

		  //  2012/05/08
		  if  (  pProcInfo->initCapSubWnds1(  DEFAULT_usMaxCnt_capSubWnds,  &pMisCnt->subWnds  )  )  goto  errLabel;

		  //
		  continue;
	 }

	 //  2009/02/11
#ifdef  __DEBUG__
	    //traceLog((TCHAR*)  _T(  "Note: 这里的localAv的player似乎没有必要了，都从下面的players里分配就可以。实际上video已经不再使用localAv里的了，有时间可以把processInput里的也改一下就可以了"  )  );
#endif

		QY_PLAYER* pPlayer;pPlayer = &pProcInfo->av.localAv.player;
	GENERIC_Q_cfgEx	qCfgEx;	//  2012/11/10
	 //
	 //  if  (  initGenericQ(  &pProcInfo->cfg.playSoundQ,  mymalloc,  0,  0,  myfree,  &pProcInfo->av.localAv.player.audio.q  )  )  goto  errLabel;
	 if  (  initQyQ2(  &pProcInfo->cfg.playSoundQ,  &pQyMc->cfg.rwLockParam,  mycountof(  pProcInfo->av.localAv.player.audio.q2.hEvents  ),  NULL,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  ( PF_qElemRemove  )clean_myPLAY_AUDIO_DATA,  &pProcInfo->av.localAv.player.audio.q2  )  )  goto  errLabel;
	 pProcInfo->av.localAv.player.audio.bQInited  =  TRUE;
	 //
	 pProcInfo->av.localAv.player.audio.qBuf2 = new QY_qBuf2();
	 int maxDataBufLen_playA; maxDataBufLen_playA = 48000 * 2 * 3 / 2;  // 1.5 seconds
	 TCHAR* name;name = (TCHAR*)_T("");
	 name = pProcInfo->cfg.playSoundQ.name;
	 if (0 != pProcInfo->av.localAv.player.audio.qBuf2->initQyQ2(CONST_qType_playA, pProcInfo->cfg.playSoundQ.uiMaxQNodes, maxDataBufLen_playA, pQyMc->cfg.rwLockParam, false, name)) goto errLabel;

	 //
	 //  if  (  initQyQ2(  &pProcInfo->cfg.playVideoQ,  &pQyMc->cfg.rwLockParam,  mycountof(  pProcInfo->av.localAv.player.video.q2.hEvents  ),  NULL,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  ( PF_qElemRemove  )clean_myDRAW_VIDEO_DATA,  &pProcInfo->av.localAv.player.video.q2  )  )  goto  errLabel;
	 memset(  &qCfgEx,  0,  sizeof(  qCfgEx  )  );
	 memcpy(  &qCfgEx.common,  &pProcInfo->cfg.playVideoQ,  sizeof(  qCfgEx.common  )  );	
	 qCfgEx.pfQElemNewEx  =  mallocMemory;
	 qCfgEx.pfQElemNew  =  mymalloc;
	 qCfgEx.pfQElemFreeEx  =  freeMemory;
	 qCfgEx.pfQElemFree  =  myfree;
	 qCfgEx.pf_QElemRemoveEx  =  (  PF_qElemRemoveEx  )cleanEx_myDRAW_VIDEO_DATA;
	 qCfgEx.pfQElemRemove  =  ( PF_qElemRemove  )clean_myDRAW_VIDEO_DATA;
	 if  (  initQyQ2(  &qCfgEx,  &pQyMc->cfg.rwLockParam,  mycountof(  pProcInfo->av.localAv.player.video.q2.hEvents  ),  NULL,  &pProcInfo->av.localAv.player.video.q2  )  )  goto  errLabel;
	 pProcInfo->av.localAv.player.video.bQInited  =  TRUE;
	 //
	 //  if  (  initQyQ2(  &pProcInfo->cfg.displayVideoQ,  &pQyMc->cfg.rwLockParam,  0,  NULL,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  (  PF_qElemRemove  )clean_MIS_MSG_procVideo_qmc,  &pProcInfo->av.localAv.player.video.displayQ2  )  )  goto  errLabel;
	 memset(  &qCfgEx,  0,  sizeof(  qCfgEx  )  );
	 memcpy(  &qCfgEx.common,  &pProcInfo->cfg.displayVideoQ,  sizeof(  qCfgEx.common  )  );	
	 qCfgEx.pfQElemNewEx  =  mallocMemory;
	 qCfgEx.pfQElemNew  =  mymalloc;
	 qCfgEx.pfQElemFreeEx  =  freeMemory;
	 qCfgEx.pfQElemFree  =  myfree;
	 qCfgEx.pf_QElemRemoveEx  =  (  PF_qElemRemoveEx  )cleanEx_MIS_MSG_procVideo_qmc;
	 qCfgEx.pfQElemRemove  =  ( PF_qElemRemove  )clean_MIS_MSG_procVideo_qmc;
	 if  (  initQyQ2(  &qCfgEx,  &pQyMc->cfg.rwLockParam,  0,  NULL,  &pProcInfo->av.localAv.player.video.displayQ2  )  )  goto  errLabel;
	 pProcInfo->av.localAv.player.video.ucbDisplayQInited  =  TRUE;
	 
	 //
	 {
		 GENERIC_Q_CFG		tmpCfg;

		 memcpy(&tmpCfg, &pProcInfo->cfg.playVideoQ, sizeof(tmpCfg));
		 //  
		 //  if  (  initQyQ2(  &tmpCfg,  &pQyMc->cfg.rwLockParam,  mycountof(  pProcInfo->av.pPlayers[i].video.q2.hEvents  ),  NULL,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  (  PF_qElemRemove  )clean_myDRAW_VIDEO_DATA,  &pProcInfo->av.pPlayers[i].video.q2  )  )  goto  errLabel;
		 memset(&qCfgEx, 0, sizeof(qCfgEx));
		 memcpy(&qCfgEx.common, &tmpCfg, sizeof(qCfgEx.common));
		 qCfgEx.pfQElemNewEx = mallocMemory;
		 qCfgEx.pfQElemNew = mymalloc;
		 qCfgEx.pfQElemFreeEx = freeMemory;
		 qCfgEx.pfQElemFree = myfree;
		 qCfgEx.pf_QElemRemoveEx = (PF_qElemRemoveEx)cleanEx_myDRAW_VIDEO_DATA;
		 qCfgEx.pfQElemRemove = (PF_qElemRemove)clean_myDRAW_VIDEO_DATA;
		 if (initQyQ2(&qCfgEx, &pQyMc->cfg.rwLockParam, 0, NULL, &pProcInfo->av.localAv.player.video.doPre_toPlayVideo.q2))  goto  errLabel;
		 pProcInfo->av.localAv.player.video.doPre_toPlayVideo.bQInited = TRUE;

	 }


	 //  Æô¶¯ÒôÆµ³Ø
	 pProcInfo->av.usCnt_players  =  pProcInfo->cfg.policy.usMax_nPlayers;		//  isWinCe(  )  ?  DEFAULT_maxusCnt_players_ce  :  DEFAULT_maxusCnt_players;	
	 pProcInfo->av.pPlayers  =  (  QY_PLAYER  *  )mymalloc(  sizeof(  QY_PLAYER  )  *  pProcInfo->av.usCnt_players  );
	 if  (  !pProcInfo->av.pPlayers  )  goto  errLabel;
	 memset(  pProcInfo->av.pPlayers,  0,  sizeof(  QY_PLAYER  )  *  pProcInfo->av.usCnt_players  );
	 for  (  int  i  =  0;  i  <  pProcInfo->av.usCnt_players;  i  ++  )  {
		  QY_PLAYER  *  pPlayer  =  &pProcInfo->av.pPlayers[i];

		  //
		  pPlayer->playerId.index_player = i;

		  //
		  GENERIC_Q_CFG		tmpCfg;
		  //
		  memcpy(  &tmpCfg,  &pProcInfo->cfg.playSoundQ,  sizeof(  tmpCfg  )  );
		  _sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s%d"  ),  tmpCfg.name,  i  );
		  _sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s%d"  ),  tmpCfg.mutexName_prefix,  i  );
		  //  if  (  initGenericQ(  &tmpCfg,  mymalloc,  0,  0,  free,  &pProcInfo->av.pPlayers[i].audio.q  )  )  goto  errLabel;
		  if  (  initQyQ2(  &tmpCfg,  &pQyMc->cfg.rwLockParam,  mycountof(  pProcInfo->av.pPlayers[i].audio.q2.hEvents  ),  NULL,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  (  PF_qElemRemove  )clean_myPLAY_AUDIO_DATA,  &pProcInfo->av.pPlayers[i].audio.q2  )  )  goto  errLabel;
		  pProcInfo->av.pPlayers[i].audio.bQInited  =  TRUE;
		  //
		  pProcInfo->av.pPlayers[i].audio.qBuf2 = new QY_qBuf2();
		  name = (tmpCfg.name);
		  if (pProcInfo->av.pPlayers[i].audio.qBuf2->initQyQ2(CONST_qType_playA, tmpCfg.uiMaxQNodes, maxDataBufLen_playA, pQyMc->cfg.rwLockParam, false, name) != 0) goto errLabel;

		  //
#if  0
		  tmpCfg  =  pProcInfo->cfg.aecQ;
		  if  (  initQyQ2( &tmpCfg,  &pQyMc->cfg.rwLockParam,  0,  NULL,  mallocMemory, mymalloc, 0, 0, freeMemory, myfree, 0, &pPlayer->audio.aecPlayQ2  )  )  goto errLabel;
#endif

		  //
		  memcpy(  &tmpCfg,  &pProcInfo->cfg.playVideoQ,  sizeof(  tmpCfg  )  );
		  _sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s%d"  ),  tmpCfg.name,  i  );
		  _sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s%d"  ),  tmpCfg.mutexName_prefix,  i  );
		  //  
		  //  if  (  initQyQ2(  &tmpCfg,  &pQyMc->cfg.rwLockParam,  mycountof(  pProcInfo->av.pPlayers[i].video.q2.hEvents  ),  NULL,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  (  PF_qElemRemove  )clean_myDRAW_VIDEO_DATA,  &pProcInfo->av.pPlayers[i].video.q2  )  )  goto  errLabel;
		  memset(  &qCfgEx,  0,  sizeof(  qCfgEx  )  );	
		  memcpy(  &qCfgEx.common,  &tmpCfg,  sizeof(  qCfgEx.common  )  );	
		  qCfgEx.pfQElemNewEx  =  mallocMemory;
		  qCfgEx.pfQElemNew  =  mymalloc;
		  qCfgEx.pfQElemFreeEx  =  freeMemory;
		  qCfgEx.pfQElemFree  =  myfree;
		  qCfgEx.pf_QElemRemoveEx  =  (  PF_qElemRemoveEx  )cleanEx_myDRAW_VIDEO_DATA;
		  qCfgEx.pfQElemRemove  =  ( PF_qElemRemove  )clean_myDRAW_VIDEO_DATA;
		  if  (  initQyQ2(  &qCfgEx,  &pQyMc->cfg.rwLockParam,  mycountof(  pProcInfo->av.pPlayers[i].video.q2.hEvents  ),  NULL,  &pProcInfo->av.pPlayers[i].video.q2  )  )  goto  errLabel;
		  pProcInfo->av.pPlayers[i].video.bQInited  =  TRUE;		
		  //
		  memcpy(  &tmpCfg,  &pProcInfo->cfg.displayVideoQ,  sizeof(  tmpCfg  )  );
		  _sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s%d"  ),  tmpCfg.name,  i  );
		  _sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s%d"  ),  tmpCfg.mutexName_prefix,  i  );
		  //  if  (  initQyQ2(  &tmpCfg,  &pQyMc->cfg.rwLockParam,  0,  NULL,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  (  PF_qElemRemove  )clean_MIS_MSG_procVideo_qmc,  &pProcInfo->av.pPlayers[i].video.displayQ2  )  )  goto  errLabel;
		  memset(  &qCfgEx,  0,  sizeof(  qCfgEx  )  );
		  memcpy(  &qCfgEx.common,  &tmpCfg,  sizeof(  qCfgEx.common  )  );	
		  qCfgEx.pfQElemNewEx  =  mallocMemory;
		  qCfgEx.pfQElemNew  =  mymalloc;
		  qCfgEx.pfQElemFreeEx  =  freeMemory;
		  qCfgEx.pfQElemFree  =  myfree;
		  qCfgEx.pf_QElemRemoveEx  =  (  PF_qElemRemoveEx  )cleanEx_MIS_MSG_procVideo_qmc;
		  qCfgEx.pfQElemRemove  =  ( PF_qElemRemove  )clean_MIS_MSG_procVideo_qmc;
		  if  (  initQyQ2(  &qCfgEx,  &pQyMc->cfg.rwLockParam,  0,  NULL,  &pProcInfo->av.pPlayers[i].video.displayQ2  )  )  goto  errLabel;		  
		  pProcInfo->av.pPlayers[i].video.ucbDisplayQInited  =  TRUE;

		  //
		  //
		  memcpy(&tmpCfg, &pProcInfo->cfg.playVideoQ, sizeof(tmpCfg));
		  _sntprintf(tmpCfg.name, mycountof(tmpCfg.name), _T("%s%d_pre"), tmpCfg.name, i);
		  _sntprintf(tmpCfg.mutexName_prefix, mycountof(tmpCfg.mutexName_prefix), _T("%s%d_pre"), tmpCfg.mutexName_prefix, i);
		  //  
		  //  if  (  initQyQ2(  &tmpCfg,  &pQyMc->cfg.rwLockParam,  mycountof(  pProcInfo->av.pPlayers[i].video.q2.hEvents  ),  NULL,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  (  PF_qElemRemove  )clean_myDRAW_VIDEO_DATA,  &pProcInfo->av.pPlayers[i].video.q2  )  )  goto  errLabel;
		  memset(&qCfgEx, 0, sizeof(qCfgEx));
		  memcpy(&qCfgEx.common, &tmpCfg, sizeof(qCfgEx.common));
		  qCfgEx.pfQElemNewEx = mallocMemory;
		  qCfgEx.pfQElemNew = mymalloc;
		  qCfgEx.pfQElemFreeEx = freeMemory;
		  qCfgEx.pfQElemFree = myfree;
		  qCfgEx.pf_QElemRemoveEx = (PF_qElemRemoveEx)cleanEx_myDRAW_VIDEO_DATA;
		  qCfgEx.pfQElemRemove = (PF_qElemRemove)clean_myDRAW_VIDEO_DATA;
		  if (initQyQ2(&qCfgEx, &pQyMc->cfg.rwLockParam, mycountof(pPlayer->video.doPre_toPlayVideo.q2.hEvents), NULL, &pPlayer->video.doPre_toPlayVideo.q2))  goto  errLabel;
		  pPlayer->video.doPre_toPlayVideo.bQInited = TRUE;


	 }

	 //  2012/05/07
	 pProcInfo->gps.usCnt_players  =  pProcInfo->cfg.policy.usMax_nPlayers_gps;
	 int  iSize;
	 iSize  =  sizeof(  QY_PLAYER_gps  )  *  pProcInfo->gps.usCnt_players;
	 pProcInfo->gps.pPlayers  =  (  QY_PLAYER_gps  *  )mymalloc(  iSize  );
	 if  (  !pProcInfo->gps.pPlayers  )  goto  errLabel;
	 memset(  pProcInfo->gps.pPlayers,  0,  iSize  );
	 for  (  i  =  0;  i  <  pProcInfo->gps.usCnt_players;  i  ++  )  {
		  //  2012/04/20
		  GENERIC_Q_CFG	qCfg;
		  memset(  &qCfg,  0,  sizeof(  qCfg  )  );
		  _sntprintf(  qCfg.name,  mycountof(  qCfg.name  ),  _T(  "guiGpsQ%d"  ),  i  );
		  _sntprintf(  qCfg.mutexName_prefix,  mycountof(  qCfg.mutexName_prefix  ),  _T(  "%s%d"  ),  CONST_mutexName_gpsQ,  i  );
		  qCfg.uiMaxQNodes  =  CONST_maxQNodes_gpsQ;
		  if  (  initQyQ2(  &qCfg,  &pQyMc->cfg.rwLockParam,  0,  NULL,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  NULL,  &pProcInfo->gps.pPlayers[i].q2  )  )  goto  errLabel;
		  pProcInfo->gps.pPlayers[i].bQInited  =  TRUE;
	 }



	 //
	 FUNCS_for_isCliHelp* pFuncs;pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	 if (pFuncs->isCliSaveAv.bOk) {
		 pProcInfo->av.sizeof_mySaveAvProcInfo = pFuncs->isCliSaveAv.pf_getSize_SAVE_av_procInfo();
		 pProcInfo->av.usCnt_saveAvProcInfos = MAX_talkerMosaic_streams;
		 size = pProcInfo->av.sizeof_mySaveAvProcInfo * pProcInfo->av.usCnt_saveAvProcInfos;
		 pProcInfo->av.pSaveAvProcInfos = mymalloc(size);
		 if (!pProcInfo->av.pSaveAvProcInfos)  goto  errLabel;
		 memset(pProcInfo->av.pSaveAvProcInfos, 0, size);
	 }



	 //
	 /*
	 QMC_aec_info  *  pAecInfo =  &pProcInfo->av.localAv.aecInfo;
	 for  (  i  = 0; i <  mycountof(  pAecInfo->aecPlayQ2s  );  i  ++  )  {
		 GENERIC_Q_CFG  qCfg;
		 qCfg  =  pProcInfo->cfg.aecQ;
		 if  (  initQyQ2( &qCfg,  &pQyMc->cfg.rwLockParam,  0,  NULL,  mallocMemory, mymalloc, 0, 0, freeMemory, myfree, 0, &pAecInfo->aecPlayQ2s[i]  )  )  goto errLabel;
	 }
	 */
	 //
	 qCfgEx.common = pProcInfo->cfg.aecPlayQ;
	 if (initQyQ2(&qCfgEx.common, &pQyMc->cfg.rwLockParam, 0, NULL, mallocMemory, mymalloc, 0, 0, freeMemory, myfree, 0, &pProcInfo->av.aecInfo.aecPlayQ2))  goto errLabel;




	 #ifdef  __DEBUG__
			 traceLogA(  (char*)  "2008/10/18"  );
	 #endif
			 
	 if  (  pProcInfo->bUse_sharedObj(  )  )  {

	 	 //  2008/10/04. 
		 pProcInfo->cfg.usMaxCnt_pSharedObjs  =  isWinCe(  )  ?  DEFAULT_usMaxCnt_pSharedObjs_ce  :  DEFAULT_usMaxCnt_pSharedObjs;
		 len  =  sizeof(  QY_sharedObj_sync  )  *  pProcInfo->cfg.usMaxCnt_pSharedObjs;
		 if  (  !(  pProcInfo->pSharedObjSyncs  =  mymalloc(  len  )  )  )  goto  errLabel;
		 memset(  pProcInfo->pSharedObjSyncs,  0,  len  );
			 
		 //
		 pProcInfo->cfg.usMaxCnt_capProcInfoBmps  =  pProcInfo->cfg.usMaxCnt_pSharedObjs;		//  DEFAULT_usMaxCnt_pSharedObjs;
		 len  =  sizeof(  CAP_procInfo_bmpU  )  *  pProcInfo->cfg.usMaxCnt_capProcInfoBmps;
		 if  (  !(  pProcInfo->pCapProcInfoBmps  =  (  CAP_procInfo_bmpU  *  )mymalloc(  len  )  )  )  goto  errLabel;
		 memset(  pProcInfo->pCapProcInfoBmps,  0,  len  );

		 pProcInfo->cfg.usMaxCnt_capProcInfoAudios  =  pProcInfo->cfg.usMaxCnt_pSharedObjs;		//  DEFAULT_usMaxCnt_pSharedObjs;
		 len  =  sizeof(  CAP_procInfo_audioU  )  *  pProcInfo->cfg.usMaxCnt_capProcInfoAudios;
		 if  (  !(  pProcInfo->pCapProcInfoAudios  =  (  CAP_procInfo_audioU  *  )mymalloc(  len  )  )  )  goto  errLabel;
		 memset(  pProcInfo->pCapProcInfoAudios,  0,  len  );

	 }

	 //  2015/11/10
	 pProcInfo->cfg.usMaxCnt_qmcObjVarInfos  =  DEFAULT_usMaxCnt_qmcObjVarInfos;
	 len  =  getSize_QMC_objVar_info(  )  *  pProcInfo->cfg.usMaxCnt_qmcObjVarInfos;
	 if  (  !(  pProcInfo->pQmcObjVarInfos  =  mymalloc(  len  )  )  )  goto  errLabel;
	 memset(  pProcInfo->pQmcObjVarInfos,  0,  len  );

	 //  2014/09/24
	 pProcInfo->cfg.usMaxCnt_taskInfos  =  DEFAULT_usMaxCnt_taskInfos;
	 len  =  getSize_QMC_TASK_INFO(  )  *  pProcInfo->cfg.usMaxCnt_taskInfos;
	 if  (  !(  pProcInfo->pQmcTaskInfos  =  mymalloc(  len  )  )  )  goto  errLabel;
	 memset(  pProcInfo->pQmcTaskInfos,  0,  len  );


	 //
	 pProcInfo->cfg.render.fps_suggested  =  60;

	 //  2010/06/25
	 pProcInfo->cfg.usTimeoutInMs_player_a  =  DEFAULT_usTimeoutInMs_player_a;
	 pProcInfo->cfg.usTimeoutInMs_player_v  =  DEFAULT_usTimeoutInMs_player_v;

	 pProcInfo->cfg.loopCtrl_timer_dlgTalk_chkRecvdTasks  =  DEFAULT_loopCtrl_timer_dlgTalk_chkRecvdTasks;
	 pProcInfo->cfg.loopCtrl_chkPlayers  =  DEFAULT_loopCtrl_chkPlayers;

	 pProcInfo->cfg.loopCtrl_chkTasks  =  DEFAULT_loopCtrl_chkTasks;

	 //
	 pProcInfo->cfg.usTimeoutInMs_waitIfNoData  =  30000;

	 //
	 pProcInfo->iDefault_ucHardwareAccl = get_default_ucHardwareAccl();


	 //  主要为解决mcu的无声音设备的问题，所以，只是处理了dSound和dummy
	 if (!pQyMc->appParams.bUse_playDev_dummy) {
		 pProcInfo->pPlayDev = new CQmcPlayDev_dSound();
	 }
	 else {
		 pProcInfo->pPlayDev = new CQmcPlayDev_dummy();
	 }



	 //
	 //if (pQyMc->iCustomId == CONST_qyCustomId_cqyt ) {
	 /*if (pProcInfo->authInfo.usAuthType == ) {
		 pProcInfo->cfg.bSkip_sm_usrLogin = true;
	 }*/

	 //
	 QIS_ptz_wnd* pPtzWnd;pPtzWnd = &pProcInfo->ptzWnd;
	 //
	 if (!pPtzWnd->m_var.cfg.bCfgInited) {
		 getPtzSettings(&pPtzWnd->m_var.cfg);
	 }
	 if (!pPtzWnd->m_var.cfg.bCfgInited) {
		 showInfo_open0(0, 0, _T("initVar_isGui failed, ptz.bCfgInited false"));
		 goto  errLabel;
	 }

	 //  2015/02/17
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Exts: enable_rtsp %d, enable_save %d, enable_fileServer %d"  ),  bSupported_rtsp(  ),  bSupported_remoteStorage_default(  ), bSupported_fileServer(  pQyMc  )  );
	 showInfo_open0(  0,  0,  tBuf  );

	    //
#ifdef  __DEBUG__
		#if  0
				pProcInfo->cfg.usTimeoutInMs_player_a  =  300000;
				pProcInfo->cfg.usTimeoutInMs_player_v  =  300000;
				traceLog((TCHAR*)  _T(  "Test: usTimeoutInMs_player_a is %d, v is %d"  ),  pProcInfo->cfg.usTimeoutInMs_player_a,  pProcInfo->cfg.usTimeoutInMs_player_v  );

				pProcInfo->cfg.loopCtrl_chkPlayers  =  180;
				//pProcInfo->cfg.loopCtrl_timer_dlgTalk_chkRecvdTasks  =  30;	//  00;

		#endif
		#if  1
				//  pProcInfo->cfg.debugStatusInfo.ucbPrint_a_in  =  TRUE;
				  //pProcInfo->cfg.debugStatusInfo.ucbPrint_v_in  =  TRUE;
				//  pProcInfo->cfg.debugStatusInfo.ucbPrint_a_out  =  TRUE;
				//  pProcInfo->cfg.debugStatusInfo.ucbPrint_v_out  =  TRUE;
				//  pProcInfo->cfg.debugStatusInfo.ucbPrint_v_draw  =  TRUE;

				//  pProcInfo->cfg.debugStatusInfo.ucbPrintRtsp  =  TRUE;
		#endif
#endif

#ifdef  __DEBUG__
		#if  10
			#ifdef  __WINCE__
					pProcInfo->cfg.debugStatusInfo.ucbNotUseWebcam  =  TRUE;
					traceLog((TCHAR*)  _T(  "Warning: initVar_isGui: ucbNotUseWebcam is true"  )  );
			#endif
		#endif
		#if	0
					pProcInfo->cfg.debugStatusInfo.ucbUseWmvAsAv  =  1;
		#endif

		//
		assert(  CONST_pkts_playVideo  >=  CONST_pkts_vpp  );
		assert(  CONST_pkts_playVideo  >=  CONST_pkts_encVideo  );
		assert(  CONST_pkts_playVideo  >=  CONST_pkts_toShareVideo_post  );
		//
		assert(  CONST_pkts_toShareVideo_post  >=  CONST_pkts_toShareVideo_post  );
		assert(  CONST_pkts_transformVideo  >=  CONST_maxTransferAvDataMems  );

#endif

#if  1	//  2012/05/25
		#ifdef  __DEBUG__
				#if  0
					 pProcInfo->cfg.debugStatusInfo.ucbShowDlgTalkStatus  =  TRUE;
			    #endif
				//
				#if  10
					pProcInfo->cfg.debugStatusInfo.ucbPrint_ptz  =  TRUE;
				#endif
				//
				#if  0
					 pProcInfo->cfg.debugStatusInfo.ucbDebugSubtitle  =  TRUE;
					 traceLog((TCHAR*)  _T(  "For debug: ucbDebugSubtitle is true"  )  );
					 //
				#endif
					 //
					   pProcInfo->cfg.debugStatusInfo.ucbDebugIa  =  TRUE;

					 //  2014/12/03
					 //pProcInfo->cfg.debugStatusInfo.ucbDebug_newMsgArrives  =  TRUE;										//  2014/12/03
					 //pProcInfo->cfg.debugStatusInfo.ucbDebug_fillData_d3d  =  TRUE;										//  2014/12/03
					 						
					 //
					 pProcInfo->cfg.debugStatusInfo.ucbPrint_d3d  =  TRUE;												//  2014/12/03

					 //

				//
				#if  10
					pProcInfo->cfg.debugStatusInfo.ucb__Dump_h265_enc__  =  TRUE;
					traceLog((TCHAR*)  _T(  "For test: dump_h265_enc set to true"  )  );
				#endif
				//
				#if  0
					pProcInfo->cfg.debugStatusInfo.ucb__Dump_h265_dec__  =  TRUE;
					traceLog((TCHAR*)  _T(  "For test: dump_h265_dec set to true"  )  );
				#endif
				//
				#if 0
					pProcInfo->cfg.debugStatusInfo.ucb__Dump_mic_pcm__=TRUE;
					traceLog((TCHAR*)_T("For test: dump_pcm set to true"));
				#endif

				//
				#if 0
					pProcInfo->cfg.debugStatusInfo.ucb__Dump_mp3_enc__=TRUE;
					traceLog((TCHAR*)_T("For test: dump_mp3_enc set to true"));
				#endif

				#if  0
					pProcInfo->cfg.debugStatusInfo.ucb__Dump_mp3_dec__=TRUE;
					traceLog((TCHAR*)_T("for test: dump_mp3_dec set to true"));
				#endif

					//
				#if 0
					pProcInfo->cfg.debugStatusInfo.ucb__Dump_deced_pcm__=TRUE;
					traceLog((TCHAR*)_T("for test: dump_deced_pcm set to true"));
				#endif

				//
				#if  1
					pProcInfo->cfg.debugStatusInfo.bDbg_use_dsound_toPlay=true;
					traceLog((TCHAR*)_T("for test: bDbg_use_dsound_toPlay set to true"  )  );
				#endif


				#if  0
					pProcInfo->cfg.ucb__USE_hdEnc_conf__  =  TRUE;//FALSE;//TRUE;
					traceLog((TCHAR*)  _T(  "For test: use hdEnc.dll to encode"  )  );
				#endif

				//  2016/06/02
				#if  10
					pProcInfo->cfg.debugStatusInfo.ucb_draw_talkers_frm  =  TRUE;
					pProcInfo->cfg.debugStatusInfo.ucb_draw_walls_frm  =  TRUE;
					traceLog((TCHAR*)  _T(  "For test: draw_talkers_frm and draw_walls_frm true"  )  );
				#endif

				#if 10
					pProcInfo->cfg.debugStatusInfo.ucb_noSlave=true;
					traceLog((TCHAR*)_T("for test: noSlave set to true"));
					//
				#endif

				#if  0
					pProcInfo->cfg.debugStatusInfo.ucbShowPlayAudioStatus=true;
					traceLog((TCHAR*)  _T( "for test: ucbShowPlayAudioStatus set to true"  )  );
				#endif

				//				
				//
#if  0
					pProcInfo->cfg.debugStatusInfo.ucbPrint_rtt = true;
					pProcInfo->cfg.debugStatusInfo.ucbShowVPktInputInfo = true;
					showInfo_open0(0, 0, _T("for dbg: print_rtt set to true"));
#endif


				//
					pProcInfo->cfg.b_useAudioQ2_toDecA = true;
					//pProcInfo->cfg.b_useQ2_toPlayA = true;

					//
					//pProcInfo->cfg.debugStatusInfo.bMon_decV = true;
					//pProcInfo->cfg.debugStatusInfo.bMon_encV = true;

					//
#if 1
					pProcInfo->cfg.debugStatusInfo.ucbPrint_triggerD3d = true;
					showInfo_open0(0, 0, _T("for dbg: print_triggerD3d set to true"));
#endif
					//
					if (0) {
						pProcInfo->cfg.debugStatusInfo.ucbShowToDrawStatus = true;
						showInfo_open0(0, 0, _T("for dbg: ucbShowToDrawStatus set to true"));
					}

	    //
		#endif

#endif


					//
					//pProcInfo->cfg.debugStatusInfo.ucbDbgDetail = ;


#ifdef  __WINCE__
#ifdef  __DEBUG__
		traceLogA(  (char*)  "Daemon need be modified to permit the pocketpc whose nMacs is 0"  );
		pProcInfo->authInfo.macsInfo.nMacs  =  1;
		safeStrnCpy(  "012345678901",  (  char  *  )pProcInfo->authInfo.macsInfo.macs[0],  mycountof(  pProcInfo->authInfo.macsInfo.macs[0]  )  );
#endif
#endif

		//
		pProcInfo->initVar_post(p0, p1, p2);



	 //
	 iErr  =  0;
errLabel:

	 if  (  iErr  )  exitVar_isGui(  p0,  p1,  p2  );

	 return  iErr;
}


 int  init_afterLogon_isGui(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int						iErr				=	-1;
	 QY_MC					*	pQyMc				=	(  QY_MC  *  )p0;
	 QY_SERVICEGUI_INFO		*	pSci				=	(  QY_SERVICEGUI_INFO  *  )p1;
	 //  p2

	 if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_is  )  return  0;
	 if  (  pQyMc->iAppType  !=  CONST_qyAppType_client  )  return  0;  

	 MC_VAR_isCli				*	pProcInfo			=	(  MC_VAR_isCli  *  )pSci->pVar;


#if  10  //  2013/08/23
	 HWND		hMainWnd  =  pQyMc->gui.hMainWnd;
	 
	 QNM_cusRes_moduleMem  *  pResMem  =  getCurCusResModuleMem(  &pQyMc->cusRes  );
	 if  (  !pResMem  )  goto  errLabel;

	 HMENU		hMainMenu;hMainMenu = ::GetMenu(hMainWnd);
	 if  (  hMainMenu  )  {
		 QY_DMITEM	*	pItem;
		 int  iResId  =  CONST_resId_mainMenu;
		 //if  (  qyGetAppAvLevel_qyMc(  )  ==  CONST_qyAppAvLevel_mini  )  iResId  =  CONST_resId_mainMenu_mini;
		 //  if  (  !(  pItem  =  (  QY_DMITEM  *  )qyGetDesByType(  pResMem->pCusMenuTable,  CONST_resId_mainMenu  )  )  )  goto  errLabel;
		 if  (  !(  pItem  =  (  QY_DMITEM  *  )qyGetDesByType(  pResMem->pCusMenuTable,  iResId  )  )  )  goto  errLabel;
		 if  (  makeDynaMenu(  &pQyMc->cusRes,  hMainMenu,  pItem,  getMenuStatus_frame,  pQyMc,  0  )  )  goto  errLabel;
	 }

	 //
#if  0  //  2017/06/21
	 if  (  qyGetSubSystemId_isCli(  )  ==  CONST_subSystemId_basic  )  {

		 //
		 TCHAR  tBuf[128];
		 GetWindowText(  hMainWnd,  tBuf,  mycountof(  tBuf  )  );
		 //
		 HMENU  hMenu  =  GetSubMenu(  hMainMenu,  1  );
		 if  (  hMenu  )  {
			 RemoveMenu(  hMainMenu,  2,  MF_BYPOSITION  );

		 }
		 //
		 //RemoveMenu(  hMainMenu,  8,  MF_BYPOSITION  );

	 }
#endif

#endif



	 //  2009/12/21	 
#ifdef  __DEBUG__
	 if  (  !pQyMc->ucbUseNamedShm  )  {
		traceLogA(  (char*)  "Not finished: unnamed shared memory shall be used"  );
		goto  errLabel;	
	 }
#endif
	 pProcInfo->cmdsShm.usMaxCnt_qmCmds  =  CONST_maxCnt_qmCmds;
	 if  (  pProcInfo->cmdsShm.usMaxCnt_qmCmds  <  pProcInfo->cfg.usMaxCnt_pSharedObjs  )  {
		 traceLogA(  (char*)  (  "initVar_isGui failed: usMaxCnt_qmCmds %d < usMaxCnt_pSharedObjs %d"  ),  pProcInfo->cmdsShm.usMaxCnt_qmCmds,  pProcInfo->cfg.usMaxCnt_pSharedObjs  );
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initVar_isGui failed: usMaxCnt_qmCmds %d < usMaxCnt_pSharedObjs %d"  ),  pProcInfo->cmdsShm.usMaxCnt_qmCmds,  pProcInfo->cfg.usMaxCnt_pSharedObjs  );
		 goto  errLabel;
	 }
	 pProcInfo->cmdsShm.uiBufSize_qmShm  =  sizeof(  QM_SHM_CMDS  );
	 if  (  !pProcInfo->cmdsShm.uiBufSize_qmShm  )  goto  errLabel;
	 pProcInfo->cmdsShm.hMap  =  CreateFileMapping(
                 INVALID_HANDLE_VALUE,						// use paging file
                 NULL,										// default security 
                 PAGE_READWRITE,							// read/write access
                 0,											// max. object size 
				 pProcInfo->cmdsShm.uiBufSize_qmShm,				// buffer size  
                 CQyString(  pQyMc->appParams.appObjPrefix  )  +  CONST_shmName_qm_cmd  );						// name of mapping object 
	 if  (  pProcInfo->cmdsShm.hMap  ==  NULL  ) { 
		 traceLogA(  (char*)"Could not create file mapping object (%d).\n",  GetLastError());
		 goto  errLabel;
	 }
	 pProcInfo->cmdsShm.pBuf  =  (  char  *  ) MapViewOfFile(pProcInfo->cmdsShm.hMap,   // handle to map object
						                        FILE_MAP_ALL_ACCESS,			// read/write permission
						                        0,                   
						                        0,                   
												pProcInfo->cmdsShm.uiBufSize_qmShm  );           
	 if  (  pProcInfo->cmdsShm.pBuf == NULL  )  {
		 traceLogA(  (char*)"Could not map view of file (%d).\n", GetLastError()); 
		 goto  errLabel;
	 }
	 memset(  pProcInfo->cmdsShm.pBuf,  0,  pProcInfo->cmdsShm.uiBufSize_qmShm  );
#ifdef  __DEBUG__
	 QM_SHM_CMDS* pShm;pShm = (QM_SHM_CMDS*)pProcInfo->cmdsShm.pBuf;
		lstrcpyn(  pShm->hint,  _T(  "Hello"  ),  mycountof(  pShm->hint  )  );
#endif


		QM_SHM_CMDS* pShmCmds;pShmCmds = (QM_SHM_CMDS*)pProcInfo->cmdsShm.pBuf;
	 if  (  pShmCmds  )  {
		 pShmCmds->hWnd_main  =  pQyMc->gui.hMainWnd;
	 }

	 //	 2013/12/24
#if  0
	 if  (  pQyMc->usAppAvLevel_daemon  !=  pQyMc->usAppAvLevel_default  /*qyGetAppAvLevel_default(  )*/  )  {
		 //
		 //  2015/06/07. hd以上(含hd)支持hwAccl,和sd不完全兼容
		 //  
		 if  (  (  pQyMc->usAppAvLevel_daemon  <  CONST_qyAppAvLevel_hd  &&  pQyMc->usAppAvLevel_default  >=  CONST_qyAppAvLevel_hd  )  		 
			 ||  (  pQyMc->usAppAvLevel_daemon  >=  CONST_qyAppAvLevel_hd  &&  pQyMc->usAppAvLevel_default  <  CONST_qyAppAvLevel_hd  )  )
		 {
			 //  2017/07/11
			 //  qyMessageBox(  pQyMc->gui.hMainWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_versionErr  ),  _T(  "www.qycx.com"  ),  MB_OK,  10,  NULL  );
			 //showNotification(  0,  0,  0,  0,  0,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_versionErr  )  );
			 showInfo_open0(  0,  _T(  "init_afterLogon"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_versionErr  )  );
		 }
	 }
#endif
	 
	 //  2013/03/10
	 SUBTITLES_cfg  tmp_subtitlesCfg;
	 //
#if  0
	 getSubtitlesCfg(  CONST_capType_av,  0,  0,  &tmp_subtitlesCfg  );
	 //
	 subtitlesCfg_modify(  &tmp_subtitlesCfg,  GetTickCount(  ),  FALSE,  &pProcInfo->subtitles.localVideoInConf,  NULL  );
#endif
	 //
	 getSubtitlesCfg(  CONST_capType_av,  CONST_subCapType_webcam,  0,  &tmp_subtitlesCfg  );
	 subtitlesCfg_modify(  &tmp_subtitlesCfg,  GetTickCount(  ),  FALSE,  &pProcInfo->subtitles.webcam,  NULL  );
	 //  2013/12/10

	 //
	 iErr  =  0;
errLabel:

	 return  iErr;
}



//
 int  exitVar_isGui(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 QY_MC					*	pQyMc				=	(  QY_MC  *  )p0;
	 QY_SERVICEGUI_INFO		*	pSci				=	(  QY_SERVICEGUI_INFO  *  )p1;
	 //  p2
	 int						i;
	 
	 if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_is  )  return  0;

	 traceLogA(  (char*)  "exitVar_isGui enters."  );

	 //
	 MC_VAR_isCli* pProcInfo = (MC_VAR_isCli*)pSci->pVar;



	 //  2010/10/01
	 if  (  pQyMc->iAppType  !=  CONST_qyAppType_client  )  {
		 exitVar_isGui_mgr(  p0,  p1,  p2  );
		 return  0;
	 }

	 //
	 pProcInfo->exitVar_pre(p0, p1, p2);
	 

	 //  2010/08/05
	 pProcInfo->processQ_media.emptyQ(  );
	 //pProcInfo->processQ_robot.emptyQ(  );

	 //  2009/12/21
	 if  (  pProcInfo->cmdsShm.pBuf  )  {
		 UnmapViewOfFile(  pProcInfo->cmdsShm.pBuf  );  
		 pProcInfo->cmdsShm.pBuf  =  NULL;
	 }
	 if  (  pProcInfo->cmdsShm.hMap  )  {
		 CloseHandle(  pProcInfo->cmdsShm.hMap  );  pProcInfo->cmdsShm.hMap  =  NULL;
	 }


	 //  2008/10/04
	 if  (  bNoSharedObjExists(  pProcInfo  )  )  {
		 MACRO_safeFree(  pProcInfo->pCapProcInfoAudios  );
		 MACRO_safeFree(  pProcInfo->pCapProcInfoBmps  );  
		 MACRO_safeFree(  pProcInfo->pSharedObjSyncs  );
		 //
		 }
	 else  {
		   traceLogA(  (char*)  "exitVar_isGui error: shared obj already exists."  );
	 }

	 //  2014/09/24
	 freeTaskInfos(  pProcInfo  );
	 //
	 //  2014/09/24
	 MACRO_safeFree(  pProcInfo->pQmcTaskInfos  );
	 

	 //  2015/11/15
	 tryToFreeQmcObjVarInfos(  pProcInfo  );

	 //  2015/11/10
	 if  (  bNoObjVarInfoExists(  pProcInfo  )  )  {
		 MACRO_safeFree(  pProcInfo->pQmcObjVarInfos  );
	 }

	 //
	 /*
	 QMC_aec_info  *  pAecInfo  =  &pProcInfo->av.localAv.aecInfo;
	 for  (  i  =  0;  i  <  mycountof(  pAecInfo->aecPlayQ2s  );  i  ++  )  {
		 exitQyQ2(  &pAecInfo->aecPlayQ2s[i]  );
	 }
	 */

	 //
	 if (pProcInfo->av.pSaveAvProcInfos) {
		 myfree(pProcInfo->av.pSaveAvProcInfos);  pProcInfo->av.pSaveAvProcInfos = nullptr;
	 }


	 //  2012/05/07
	 if  (  pProcInfo->gps.pPlayers  )  {
		 for  (  i  =  0;  i  <  pProcInfo->gps.usCnt_players;  i  ++  )  {
			  if  (  pProcInfo->gps.pPlayers[i].bQInited  )  exitQyQ2(  &pProcInfo->gps.pPlayers[i].q2  );
		 }
		 free(  pProcInfo->gps.pPlayers  );
	 }

	 //  ÊÍ·ÅÒôÆµ³Ø	 
	 if  (  pProcInfo->av.pPlayers  )  {  //  ÕâÀï»¹Ã»ÅªºÃ£¬ÔõÃ´À´²»Ò»¿ªÊ¼Æô¶¯Ïß³ÌÄØ¡£¶ø´ï¡£¡£¡£¡£¡£
		 		 
		 for  (  i  =  0;  i  <  pProcInfo->av.usCnt_players;  i  ++  )  {
			  QY_PLAYER  *  pPlayer  =  &pProcInfo->av.pPlayers[i];
			  if  (  !bQThreadExists(  pProcInfo->av.pPlayers[i].audio  )  )  {
				  if  (  pProcInfo->av.pPlayers[i].audio.bQInited  )  exitQyQ2(  &pProcInfo->av.pPlayers[i].audio.q2  );
				  //
				  pProcInfo->av.pPlayers[i].audio.qBuf2->exitQyQ2();
				  MACRO_safeDelete(pProcInfo->av.pPlayers[i].audio.qBuf2);
				  //
				  }
			  else  {
					#ifdef  __DEBUG__
							traceLog((TCHAR*)  _T(  "Warning: exitVar_isGui: playes[%d].audio is not quit."  ),  i  );
					#endif
			  }
			  //
			  //exitQyQ2(  &pPlayer->audio.aecPlayQ2  );
			  //
			  if  (  pProcInfo->av.pPlayers[i].video.bQInited  )  exitQyQ2(  &pProcInfo->av.pPlayers[i].video.q2  );
			  if  (  pProcInfo->av.pPlayers[i].video.ucbDisplayQInited  )  exitQyQ2(  &pProcInfo->av.pPlayers[i].video.displayQ2  );
			  if (pPlayer->video.doPre_toPlayVideo.bQInited) exitQyQ2(&pPlayer->video.doPre_toPlayVideo.q2);
		 }

		 free(  pProcInfo->av.pPlayers  );
	 }

	 QY_PLAYER  *  pPlayer  =  &pProcInfo->av.localAv.player;
	 if  (  !bQThreadExists(  pProcInfo->av.localAv.player.audio  )  )  {
		 if  (  pProcInfo->av.localAv.player.audio.bQInited  )  exitQyQ2(  &pProcInfo->av.localAv.player.audio.q2  );	 
		 //
		 pProcInfo->av.localAv.player.audio.qBuf2->exitQyQ2();
		 MACRO_safeDelete(pProcInfo->av.localAv.player.audio.qBuf2);
		 }
	 else  {
		   #ifdef  __DEBUG__
				   traceLog((TCHAR*)  _T(  "Warning: exitVar_isGui: localAv.player.audio is not quit"  )  );
		   #endif
	 }
	 //
	 exitQyQ2(  &pProcInfo->av.aecInfo.aecPlayQ2  );
	 //
	 if  (  pProcInfo->av.localAv.player.video.bQInited  )  exitQyQ2(  &pProcInfo->av.localAv.player.video.q2  );
	 if  (  pProcInfo->av.localAv.player.video.ucbDisplayQInited  )  exitQyQ2(  &pProcInfo->av.localAv.player.video.displayQ2  );	//  
	 if (pProcInfo->av.localAv.player.video.doPre_toPlayVideo.bQInited) exitQyQ2(&pProcInfo->av.localAv.player.video.doPre_toPlayVideo.q2);
	 
	 //for  (  int  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  
	 for  (  int  i  =  0;  i  <  pProcInfo->ucCnt_misCnts;  i  ++  )  
	 {
		  MIS_CNT  *  pMisCnt  =  getMisCntByIndex(  0,  pProcInfo,  i  );//&pProcInfo->misCnts[i];
		  if  (  !pMisCnt  )  continue;
		  //
		  if  (  pMisCnt->cfg.dynCfg.cnt.usCntPort  )  {

			  //  ¹Ø±Õ¹ÜÀí¶ÓÁÐ
			  if  (  pMisCnt->ucbQmObjQInited  )  {		//  2006/12/07
			  	  exitQmObjQ(  0,  (  QM_OBJQ  *  )pMisCnt->pObjQ  );	pMisCnt->ucbQmObjQInited  =  FALSE;
		  	  }
		  	  if  (  pMisCnt->pObjQ  )  {	//  2007/04/01
			  	  free(  pMisCnt->pObjQ  );  pMisCnt->pObjQ  =  NULL;
		  	  }
		  
			  //  ¹Ø±Õ´¥·¢ÐÅºÅµÆ
			  int  j;
			  for  (  j  =  0;  j  <  mycountof(  pMisCnt->channels  );  j  ++  )  {
				   MIS_CHANNEL	*	pChannel  =  &pMisCnt->channels[j];
				   //  
				   //
				   exitQyQ2(  &pChannel->outputQ2  );
				   exitQyQ2(  &pChannel->toSendQ2  );
#if  0
				   exitQyQ2(  &pChannel->inputQ2  );	//  2015/09/09
#endif
				   //
				   exitGenericQ(  &pChannel->inCacheQ  );

			  }
			  			  
			  //
			  exitGenericQ(  &pMisCnt->recentFriendQ  );
			  exitGenericQ(  &pMisCnt->talkingFriendQ  );
			  //
			  //
		  }

		  //  2012/05/08
		  exitCapSubWnds(  &pMisCnt->subWnds  );

		  //
		  continue;
	 }
	 //  2015/07/02
	 MACRO_safeFree(  pProcInfo->pMisCnts  );
	 
	 //
	 qisSharedTexInfos_exit(&pProcInfo->m_pQisSharedTexInfos);


	 //
#if  0  //  2016/06/15
	 if  (  pProcInfo->ppPhoneMsgrs_sortedByIdInfo  )  free(  pProcInfo->ppPhoneMsgrs_sortedByIdInfo  );
	 if  (  pProcInfo->ppPhoneMsgrs_sortedByDevIdStr  )  free(  pProcInfo->ppPhoneMsgrs_sortedByDevIdStr  );
	 exitGenericQ(  &pProcInfo->phoneMsgrQ  );		//  2008/02/01
#endif

	 //
#ifdef  __NOTSUPPORT_DB__
		exitGenericQ(  &pProcInfo->memTaskQ  );			//  2010/04/22
#endif

	 exitGenericQ(  &pProcInfo->imMsgLogQ  );		//  2010/07/17

	 //
	 pProcInfo->processQ_media.exitQ(  );
	 //pProcInfo->processQ_robot.exitQ(  );

	 //
	 exitGenericQ(  &pProcInfo->mgrQ  );
	 exitGenericQ(  &pProcInfo->robotQ  );			//  2007/07/04
	 exitGenericQ(  &pProcInfo->displayQ  );
	 exitGenericQ(  &pProcInfo->workQ  );
	 exitGenericQ(  &pProcInfo->schedulerQ  );
	 //  exitGenericQ(  &pProcInfo->mediaQ  );
	 //  exitGenericQ(  &pProcInfo->realTimeMediaQ  );
	 exitQyQ2(  &pProcInfo->mediaQ2  );
	 exitQyQ2(  &pProcInfo->realTimeMediaQ2  );
	 exitQyQ2(  &pProcInfo->rtOpQ2  );	//  2016/12/26

	 //  2010/04/25
#ifdef  __DEBUG__
	    printShmMemory(  0,  _T(  "exitVar_isGui"  ),  TRUE  );
#endif

#if  0  //  2015/01/18
	 for  (  i  =  0;  i  <  mycountof(  pProcInfo->shmMemory.mems  );  i  ++  )  {
		  if  (  !pProcInfo->shmMemory.mems[i].uiBufSize_packet  )  continue;
		  MACRO_safeFree(  pProcInfo->shmMemory.mems[i].ucbUseds  );
	 }

	 //
	 if  (  pProcInfo->shmMemory.pBuf  )  {
		 UnmapViewOfFile(  pProcInfo->shmMemory.pBuf  );  
		 pProcInfo->shmMemory.pBuf  =  NULL;
	 }
	 if  (  pProcInfo->shmMemory.hMap  )  {
		 CloseHandle(  pProcInfo->shmMemory.hMap  );  pProcInfo->shmMemory.hMap  =  NULL;
	 }
#endif

	 //  2010/09/16
	 //
#ifdef  __isCli__
		#if  0  //  2016/09/08
			 //  2013/07/03
			 if  (  g_pQyMc->pQisWallsCfg  )  dyn_qisWallsCfgFree(  &g_pQyMc->pQisWallsCfg  );
 
			 if  (  g_pQyMc->pGBuf_d3d  )  dyn_GBuf_d3d_isCli_free(  &g_pQyMc->pGBuf_d3d  );
			 dyn_dllExit_d3d_isCli(  ); 
		#endif

		//  2017/06/18
		exit_webRtc(  );


		//  2016/09/08
		#ifndef  __NOTSUPPORT_d3d__
		 		 //
				 exit_toUseD3d(  pProcInfo  );
		#endif

#endif

	//  2016/06/03
	MACRO_safeFree(  pProcInfo->pGZone_d3dWalls  );

	//  2015/12/04
	MACRO_safeFree(  pProcInfo->pGZone_activeTalkers  );

	//		
	MACRO_safeDelete(pProcInfo->pPlayDev);

	 //  2013/06/07
	 pProcInfo->FUNCS_for_isCliHelp_free(  &pProcInfo->pFuncs_for_isCliHelp  );
	 

	 //
	 pProcInfo->exitVar_post(p0, p1, p2);


	 //
	 traceLogA(  (char*)  "exitVar_isGui leaves."  );

	 //
	 return  0;
}



  int  refreshVar_misClient(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int	iErr;



	 iErr  =  0;
//  errLabel:
	 return  iErr;

}









 //  2007/03/28, ´Ëº¯ÊýÔÝÊ±½èÓÃ£¬ÓÃµÄÊÇqwmÐ­Òé£¬Ó¦¸ÃÓÃMISÐ­ÒéÀ´ÖØÐÂ
 extern  "C"  BOOL  bServConnected_mis(  QY_ENV  *  pEnv,  char  *  serverIp,  unsigned  short  serverPort,  void  *  pParam,  int  serviceId,  char  *  ver,  QY_ENC_CTX  *  pCommEncCtx,  __int64  i64StartTime_base,  SOCK_TIMEOUT  *  pTo  )
{
	 BOOL						bRet				=		FALSE;
	 MIS_CNT			*		pMisCnt				=		(  MIS_CNT  *  )pParam;
	 QY_SOCK					sock;
	 QY_COMM_SESSION			session;
	 BOOL						bSessionOpen		=		FALSE;
	 char						buf[8192];
	 int						len;
	 char				*		ptr;
	 AUTH_RESP_MIS				authResp;

	 // traceLogA(  (char*)  "bServConntected_mis enters"  );
#ifdef  __DEBUG__
	    //	 showInfo_open0(0, null, _T("bServConnected_mis enters"));
#endif

	 //  ÏÈ·¢Ò»¸öhelloClient, 
	 clearQySock(  &sock  );
	 memset(  &session,  0,  sizeof(  session  )  );
	 
	 //
	 Param_dbg param;
	 param.m_pHint = (TCHAR*)_T("bServConnected_mis.1943");
	 param.m_bShowInfo = false;

	 //
	 len  =  sizeof(  buf  );
	 if  (  qnmOpenSession_mis(  serverIp,  serverPort,  NULL,  CONST_qnmAuthCmd_clientHello,  CONST_channelType_talking,  NULL,  serviceId,  ver,  NULL,  i64StartTime_base,  &session,  &sock,  pTo,  buf,  (  unsigned  int  *  )&len, &param  )  )  goto  errLabel;
	 bSessionOpen		=		TRUE;
	 if  (  !isRcOk(  session.usLastRespCode_i  )  )  goto  errLabel;
	 qnmCloseSession_msg(  mynull,&session,  &sock,  pTo,_T("bServConnected_mis.l2030"));  bSessionOpen = FALSE;

	 memset(  &authResp,  0,  sizeof(  authResp  )  );
	 ptr  =  buf;
	 if  (  stream2Data(  &ptr,  (  unsigned  int  *  )&len,  filterStream_is,  tmpHandler_stream2AuthResp_mis,  NULL,  &authResp  )  )  goto  errLabel;
	 pMisCnt->commEncCtx.ucbPublicKeyDownloaded  =  TRUE;

#ifdef  __DEBUG__
	 traceLogA(  (char*)  "authResp encType %d, publicKey %d bytes, [%s]",  authResp.uiCommEncCtxType,  authResp.uiBlobLen_publicKey,  authResp.publicKeyBlob  );  
#endif

	 if  (  0  )  {		//  Èç¹û²»×Ô¶¯ÑéÖ¤
		 //  Èç¹ûÔ­À´Ã»ÓÐÃÜÔ¿£¬ÄÇÃ´¾Í·¢ËÍµ½½çÃæÉÏÈ¥µÈ´ýÈ·ÈÏ¡£
		 //  Èç¹ûÔ­À´¾ÍÓÐ¸öÃÜÔ¿£¬ÄÇÃ´ÕâÀïÐ£ÑéÒ»ÏÂÊÇ·ñÒ»ÖÂ¡£Èç¹ûÒ»ÖÂ£¬ÄÇÃ´¾ÍokÁË¡£Èç¹û²»Ò»ÖÂ£¬¾Í·¢µ½½çÃæÉÏÈ¥µÈ´ýÈ·ÈÏ¡£
		}
	 else  {
		   CQySyncObj	syncObj;

		   traceLogA(  (char*)  "publicKey verified"  );  

		   if  (  syncObj.sync(  CONST_mutexName_syncKey_qmc  )  )  goto  errLabel;

		   //  Èç¹ûÔ­À´Ã»ÓÐÃÜÔ¿£¬Ôò´æÈë×¢²á±í¡£²¢µ¼ÈëCSP
		   //  Èç¹ûÓÐ£¬Ð£ÑéÊÇ·ñÒ»ÖÂ¡£
		   pMisCnt->commEncCtx.common.type  =  authResp.uiCommEncCtxType;  
		   if  (  authResp.uiBlobLen_publicKey  >  mycountof(  pMisCnt->commEncCtx.publicKeyBlob  )  )  goto  errLabel;
		   pMisCnt->commEncCtx.uiBlobLen_publicKey  =  authResp.uiBlobLen_publicKey;
		   memcpy(  pMisCnt->commEncCtx.publicKeyBlob,  authResp.publicKeyBlob,  pMisCnt->commEncCtx.uiBlobLen_publicKey  );
		   
		   pMisCnt->commEncCtx.ucbPublicKeyVerified  =   TRUE;
	 }

	 //  Èç¹ûÃ»ÓÐÑéÖ¤£¬¾Í²»Òª°ÑÑéÖ¤ÐÅÏ¢·¢ËÍµ½·þÎñÆ÷ÉÏ£¬ÕâÀïÍË³ö
	 if  (  !pMisCnt->commEncCtx.ucbPublicKeyVerified  )  {
		 traceLogA(  (char*)  ""  );
		 goto  errLabel;
	 }

	 //
#if 0
	 if (bNoEnc_forTest_cli()) {
		 pMisCnt->commEncCtx.common.type = 0;
		 //
		 showInfo_open0(0, 0, _T("bServConnected_mis: bNoEnc"));
	 }
#endif


	 /*
	 clearQySock(  &sock  );
	 memset(  &session,  0,  sizeof(  session  )  );
	 
	 //  ×¼±¸commEncCtx
	 memcpy(  &commEncCtx,  &pMisCnt->commEncCtx,  sizeof(  commEncCtx  )  );

	 if  (  qnmOpenSession_mis(  serverIp,  serverPort,  pMisCnt->pAuthInfo,  0,  CONST_channelType_talking,  NULL,  serviceId,  ver,  &commEncCtx,  &session,  &sock,  pTo,  NULL,  NULL  )  )  goto  errLabel;
	 bSessionOpen		=		TRUE;
	 if  (  !isRcOk(  session.usLastRespCode_i  )  &&  !isRcNeedVerified(  session.usLastRespCode_i  )  )  goto  errLabel;
	 */

	 bRet  =  TRUE;

errLabel:

	 if  (  bSessionOpen  )  qnmCloseSession_msg(  mynull, &session,  &sock,  pTo,  _T("bServConnedted_mis.l2094"));

	 TCHAR  tBuf[128];
	 _sntprintf(tBuf,  mycountof(tBuf),  _T(  "bServConnected_mis: Connecting to %S:%d %s"  ),  (  serverIp  ),  (int)serverPort,  bRet  ?  _T(  "OK"  )  :  _T(  "Failed"  )  );
	 showInfo_open0(0, 0, tBuf);

	 //  traceLogA(  (char*)  "bServConntected_mis leaves"  );

	 return  bRet;

}










//  pMisCnt, 2008/01/06








 //
 int  postMsg2OutputQ_mc(  MIS_CNT  *  pMisCnt,  MIS_MSGU  *  pMsg,  unsigned  int  msgLen,  MIS_CHANNEL  *  pChannel  )
{
	 int						iErr					=	-1;
	 
	 if  (  !pMisCnt  )  {
		 traceLogA(  (char*)  "postMsg2OutputQ_mc failed: pMisCnt is null"  );  
		 return  -1;
	 }
	 
	 MC_VAR_isCli				*	pProcInfo				=	(  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	 if  (  !pProcInfo  )  return  -1;
	 QY_MC					*	pQyMc					=	(  QY_MC  *  )pProcInfo->pQyMc;
	 QY_SERVICEGUI_INFO		*	pSci					=	(  QY_SERVICEGUI_INFO  *  )pProcInfo->pSgiParam;
	 TCHAR						tHintBuf[255  +  1]		=	_T(  ""  );
	 int						tmpiRet					=	-1;
	 //  CQyQ2Help					q2Help;


	 if  (  (  tmpiRet  =  q2PostMsgAndTrigger(  pMsg,  msgLen,  &pChannel->outputQ2,  _T(  "postMsg2OutputQ"  )))) {

		 if  (  tmpiRet  !=  CONST_qyRet_qFull  )  {
			 _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "qPostMsgAndTrigger failed."  )  );			 
			 goto  errLabel;
			 }
		 else  {
			   _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "outputQ of %s is full. "  ),  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  )  );
			   //
#if  0
			   switch  (  pChannel->uiType  )  {		//  2008/05/18, ÎªÁË±ÜÃâÊä³ö¶ÂÈû²»ÄÜÆð×÷ÓÃÁË£¬ÕâÀïÏÈ²ÉÈ¡Çå¿Õ²Ù×÷¡£×¢Òâ£ºÖ»ÄÜ¶ÔÊÓÆµµÈÊý¾Ý²»ÖØÒª£¬µ«ÊÇ×¢ÖØÊµÊ±ÐÔµÄ¶ÓÁÐ¡£
					   case  CONST_channelType_media:
					   case  CONST_channelType_realTimeMedia:
						     _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%semptyQ now."  ),  tHintBuf  );  
						     emptyQ2(  &pChannel->outputQ2  );
						     break;
					   default:
							  break;
			   }
			   //  2015/08/22. 队列满时，不能退出，应接着触发发送. 在q2PostMsgAndTrigger已经触发
#endif
		 }
	 }
	 if  (  pChannel->outputQ2.ucbTriggerErr  )  q2AvoidTriggerTooHigh(  0,  &pChannel->outputQ2  );

	 iErr  =  0;

errLabel:

	 if  (  iErr  ||  tHintBuf[0]  )  {
		 qyShowInfo1(  CONST_qyShowType_debugWarning,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "postMsg2OutputQ_mc: %s"  ),  tHintBuf  );
	 }

	 return  iErr;
}



#ifdef  __WINCE__
 int  tmpHandler_searchImMsgLog(  void  *  p0,  MIS_MSGU  *  pMsg,  MIS_MSGU  *  pMem  )
{
	int	iErr	=	-1;

	if  (  pMsg->uiType  ==  pMem->uiType  )  {
		switch  (  pMem->uiType  )  {
				case  CONST_misMsgType_talk:
					  if  (  pMem->talk.data.route.idInfo_from.ui64Id  ==  pMsg->talk.data.route.idInfo_from.ui64Id
						  &&  pMem->talk.tStartTime  ==  pMsg->talk.tStartTime
						  &&  pMem->talk.uiTranNo  ==  pMsg->talk.uiTranNo  )
					  {
						  iErr  =  1;  goto  errLabel;
					  }
					  break;
				case  CONST_misMsgType_task:
					  if  (  pMem->task.data.route.idInfo_from.ui64Id  ==  pMsg->task.data.route.idInfo_from.ui64Id
						  &&  pMem->task.tStartTime  ==  pMsg->task.tStartTime
						  &&  pMem->task.uiTranNo  ==  pMsg->task.uiTranNo  )
					  {
						  iErr  =  1;  goto  errLabel;
					  }
					  break;

				default:
						break;
		}
	}

	iErr  =  0;
errLabel:
	return  iErr;
}

 BOOL  tmpHandler_bRemoveImMsgLog(  void  *  p0,  void  *  p1,  MIS_MSGU  *  pMem  )
{
	GENERIC_Q	*	pImMsgQ  =  (  GENERIC_Q  *  )p0;

	if  (  pImMsgQ->uiQNodes  >  pImMsgQ->cfg.uiMaxQNodes  /  2  )  return  TRUE;
	return  FALSE;
}
#endif


 


 int  getScreenXy(  int  *  pScreenX,  int  *  pScreenY  )
{
	HDC hScreenDC=::GetDC(NULL);
	if  (  pScreenX  )  *pScreenX  =  GetDeviceCaps(hScreenDC,HORZRES);
	if  (  pScreenY  )  *pScreenY  =  GetDeviceCaps(hScreenDC,VERTRES);
	::ReleaseDC(NULL,hScreenDC);		
	return  0;
}


 
 













 int  waitToQuit_isCli(  MC_VAR_isCli  *  pProcInfo,  int  dwTimeInMs,  LPCTSTR  hint  )
{
	if  (  !pProcInfo  )  return  -1;

	if  (  !hint  )  hint  =  _T(  ""  );

	//
	TCHAR  tBuf[128];
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "waitToQuit_isCli: %s"  ),  hint  );
	showInfo_open0(  0,  0,  tBuf  );
#ifdef  __DEBUG__
	traceLog((TCHAR*)  tBuf  );
#endif

	//
	if  (  pProcInfo->status.waitToQuit.dwTickCnt_start  )  return  0;
	pProcInfo->status.waitToQuit.dwTickCnt_start  =  GetTickCount(  );
	pProcInfo->status.waitToQuit.dwTimeInMs  =  dwTimeInMs;
	return  0;
}

 //
 int  notifyPanicToApp(  QY_MC  *  pQyMc,  int  iErr,  LPCTSTR  hint  )
{
	 //
	 if (!hint)  hint = _T("");
	 TCHAR  tBuf[128];

	 //
#ifdef  __DEBUG__
	 _sntprintf(tBuf, mycountof(tBuf), _T("notifyPanicToApp:  %s"), hint);
	 traceLog(  (TCHAR*)tBuf  );
#endif

	 //
	 if  (  pQyMc  )  {
#ifdef  __DEBUG__
		 traceLogA(  (char*)  "notifyPanicToApp: WM_CLOSE"  );
#endif

		 //  pMainWnd->PostMessage(  WM_CLOSE,  0,  0  );
		 PostMessage(  pQyMc->gui.hMainWnd,  WM_COMMAND,  MAKEWPARAM(  ID_qyQuitMainWnd,  0  ),  0  );  

		 //
		 pQyMc->status_notifyPanicToApp.nTimes_notifyPanicToApp++;

		 //
		 TCHAR  tBuf[128];
		 _sntprintf(tBuf, mycountof(tBuf), _T("notifyPanicToApp called, nTimes %d"), pQyMc->status_notifyPanicToApp.nTimes_notifyPanicToApp);
		 showInfo_open0(0, 0, tBuf);
		 if (pQyMc->appParams.bConfServer) {
			 if (pQyMc->status_notifyPanicToApp.nTimes_notifyPanicToApp > 2) {
				 showInfo_open0(0, 0, _T("nTimes_notifyPanicToApp > 2, call exitProcess"));
				 //
				 qyExitProcessEx(_T(""), true);
			 }
		 }

	 }

	 return  0;
}







 int  procMsgInput_work_resp(  QY_MC  *  pQyMc,  QY_SERVICEGUI_INFO  *  pSci,  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_INPUT  *  pMsgInput,  unsigned  int  lenInBytes_msg,  CTX_MC_THREAD  *  pCtx,  MIS_CHANNEL  *  pChannel  )
{
	 int					iErr		=	-1;
	 	 
	 //  IM_CONTENTU		*	pContent	=	(  IM_CONTENTU  *  )&pMsgInput->data;
	 IM_CONTENTU			*	pContent	=	M_getMsgContent(  pMsgInput->ucFlg,  &pMsgInput->data  );									 

	 int					i;
	 	 						     
	 if  (  !isUcFlgResp(  pMsgInput->ucFlg  )  )  return  -1;	
	 if  (  lenInBytes_msg  <  offsetof(  MIS_MSG_INPUT,  data  )  )  return  -1;

	 switch  (  pContent->uiType  )  {
			 case  CONST_imCommType_refreshWebContactsInfo:  

				   for  (  i  =  0;  i  <  pContent->refreshWebContactsInfo.usCnt;  i  ++  )  {
					    //  ÐèÒªÈ·¶¨logicalPeer
					    pMsgInput->addr_logicalPeer.idInfo.ui64Id  =  pContent->refreshWebContactsInfo.mems[i].idInfo.ui64Id;

						if  (  qPostMsg(  pMsgInput,  lenInBytes_msg,  &pQyMc->gui.processQ,  _T(  "procMsgInput_work_resp"  ))) {
							traceLogA(  (char*)  "mcThreadProc_mis_work(  ): qPostMsg(  ) failed"  );
							break;
						}
						PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );    
				   }

				   break;
			 case  CONST_imCommType_vDevComs:
				   if  (  !pContent->vDevComs.ucbResp  )  goto  errLabel;

				   myVDev_postData2Dev(  pQyMc,  pContent->vDevComs.uiVDevId,  NULL,  0,  0,  0,  pContent,  lenInBytes_msg  -  offsetof(  MIS_MSG_INPUT,  data  ),  0,  NULL,  0  );
				   
				   break;
			 case  CONST_imCommType_retrieveSmPolicy:
				   if  (  !pContent->retrieveSmPolicy.ucbResp  )  goto  errLabel;

				   myVDev_postData2Dev(  pQyMc,  pContent->retrieveSmPolicy.uiVDevId,  NULL,  0,  0,  0,  pContent,  lenInBytes_msg  -  offsetof(  MIS_MSG_INPUT,  data  ),  0,  NULL,  0  );
				   
				   break;
#if  0	//  2011/10/31. 从mgr直接发到gui去了, 所以这里不用处理了
			 case  CONST_imCommType_refreshDynBmps:
				   if  (  !pContent->refreshDynBmps.ucbResp  )  goto  errLabel;

				   if  (  qPostMsg(  pMsgInput,  lenInBytes_msg,  &pQyMc->gui.processQ  )  )  {
					   traceLogA(  (char*)  "mcThreadProc_mis_work: qPostMsg failed."  );
					   break;
				   }
				   PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );

				   break;
#endif
			 case  CONST_imCommType_htmlContent:	//  2014/07/12

				   if  (  qPostMsg(  pMsgInput,  lenInBytes_msg,  &pQyMc->gui.processQ,  _T(  "procmsgInput_work_resp 1"  ))) {
					   traceLogA(  (char*)  "mcThreadProc_mis_work: qPostMsg failed."  );
					   break;
				   }
				   PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );
				   
				   break;
			 default:
					#ifdef  __DEBUG__
							traceLog((TCHAR*)  _T(  "Unprocessed contentType %d, procMsgInput_work_resp"  ),  pContent->uiType  );
					#endif
					break;
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
}





 //
#ifdef  __NOTSUPPORT_DB__
 int  getCeTaskMem(  void  *  pDb,  int  iDbType,  MIS_CNT  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo_send,  time_t  tSendTime,  unsigned  int  uiTranNo,  int  iTaskId,  CE_TASK_MEM  *  pTaskMem  )
{
		MC_VAR_isCli	*	pProcInfo	=	(  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
		int				tmpiRet		=	-1;
		
		if  (  !pTaskMem  )  return  -1;

		memset(  pTaskMem,  0,  sizeof(  pTaskMem[0]  )  );
		if  (  pIdInfo_send  )  pTaskMem->idInfo_send.ui64Id  =  pIdInfo_send->ui64Id;
		pTaskMem->tStartTime  =  tSendTime;
		pTaskMem->uiTranNo  =  uiTranNo;
		pTaskMem->iTaskId  =  iTaskId;

		tmpiRet  =  qTraverse(  &pProcInfo->memTaskQ,  (  PF_commonHandler  )tmpHandler_storeTaskInDb,  0,  pTaskMem  );
		if  (  tmpiRet  <=  0  )  return  -1;
		return  0;
}
#endif

 int  tmpHandler_updateTaskStatus(  int  iStatus,  int  iTaskId,  CE_TASK_MEM  *  pMem  )
{
	int		iErr	=	-1;

	if  (  pMem->iTaskId  ==  iTaskId  )
	{
		pMem->iStatus  =  iStatus;
		iErr  =  1;  goto  errLabel;
	}
	
	iErr  =  0;
errLabel:
	return  iErr;
}



 





 //
 BOOL  isImGrp_isClient(  QY_SERVICEGUI_INFO  *  pSci,  MIS_CNT  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo  )
{
	BOOL					bRet			=	FALSE;

	if  (  !pSci  )  return  FALSE;
	QY_MC				*	pQyMc			=	(  QY_MC  *  )pSci->pParent;
	if  (  !pQyMc  )  return  FALSE;
	QM_OBJQ_MEM				mem;
	QY_MESSENGER_INFO		messengerInfo;
	QMEM_MESSENGER_CLI  *	pQMem			=	NULL;
	//				
	if  (  !pSci  ||  !pMisCnt  ||  !pIdInfo  )  return  FALSE;
	if  (  !pIdInfo->ui64Id  )  return  FALSE;
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if (!pDbFuncs)  return false;// goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	if  (  findQMemByKey(  0,  pMisCnt->pObjQ,  pIdInfo,  &mem  )  )  {	
		#ifdef  __NOTSUPPORT_DB__
				goto  errLabel;
		#else
			CQnmDb	db;
					
			if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
			if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pQyMc->p_g_dbFuncs,  db.m_pDbMem->pDb,  pQyMc->cfg.db.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  pMisCnt->cfg.misServName,  pIdInfo,  0,  &messengerInfo,  NULL,  NULL,  NULL  )  )  goto  errLabel;
			if  (  messengerInfo.uiType  !=  CONST_objType_imGrp  )  goto  errLabel;
			//
			if  (  procQmObjQ(  pSci,  (  QM_OBJQ  *  )pMisCnt->pObjQ,  db.m_pDbMem->pDb,  pQyMc->cfg.db.iDbType,  messengerInfo.uiType,  &messengerInfo,  &mem  )  )  goto  errLabel;
		#endif
	}		
	pQMem  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;
	if  (  !pQMem  )  goto  errLabel;
	if  (  pQMem->uiType  !=  CONST_objType_imGrp  )  goto  errLabel;

	bRet  =  TRUE;
errLabel:
	return  bRet;
}


 int  getIdInfo_logicalPeer(  QY_SERVICEGUI_INFO  *  pSci,  MIS_CNT  *  pMisCnt,  MSG_ROUTE  *  pRoute,  MSGR_ADDR  *  pAddr_logicalPeer  )
{	 		
	int			iErr	=	-1;
	if  (  !pSci  )  return  -1;
	QY_MC	*	pQyMc	=	(  QY_MC  *  )pSci->pParent;
	if  (  !pQyMc  )  return  -1;

	if  (  !pMisCnt  )  return  -1;		//  2007/12/23
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if (!pDbFuncs)  return  -1;// goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	if  (  pRoute->uiDevType_from  ==  CONST_objType_dev  )  {
		if  (  isImGrp_isClient(  pSci,  pMisCnt,  &pRoute->idInfo_to  )  )  {
			pAddr_logicalPeer->idInfo.ui64Id  =  pRoute->idInfo_to.ui64Id;
			iErr  =  0;  goto  errLabel;
		}
		//
		pAddr_logicalPeer->idInfo.ui64Id  =  pRoute->idInfo_from.ui64Id;
		pAddr_logicalPeer->uiDevType  =  pRoute->uiDevType_from;
		//
		//safeWcsnCpy(  pRoute->wDevIdStr_from,  pAddr_logicalPeer->wDevIdStr,  mycountof(  pAddr_logicalPeer->wDevIdStr  )  );
		}
	else  if  (  pRoute->uiDevType_to  ==  CONST_objType_dev  )  {
			  pAddr_logicalPeer->idInfo.ui64Id  =  pRoute->idInfo_to.ui64Id;
		      pAddr_logicalPeer->uiDevType  =  pRoute->uiDevType_to;
			  //
			  //safeWcsnCpy(  pRoute->wDevIdStr_to,  pAddr_logicalPeer->wDevIdStr,  mycountof(  pAddr_logicalPeer->wDevIdStr  )  );
			 }
	else  {

		  if  (  pRoute->idInfo_to.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
			  pAddr_logicalPeer->idInfo.ui64Id  =  pRoute->idInfo_from.ui64Id;
			  iErr  =  0;  goto  errLabel;
			  }
		  else  {
#if  0
			    QM_OBJQ_MEM				mem;
				QY_MESSENGER_INFO		messengerInfo;
				QMEM_MESSENGER_CLI  *	pQMem	=	NULL;
				//								 
				if  (  findQMemByKey(  0,  pMisCnt->pObjQ,  &pRoute->idInfo_to,  &mem  )  )  {
					#ifdef  __NOTSUPPORT_DB__
						    goto  errLabel;
					#else
						CQnmDb	db;

						if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
						if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  db.m_pDbMem->pDb,  pQyMc->cfg.db.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  pMisCnt->cfg.misServName,  &pRoute->idInfo_to,  0,  &messengerInfo,  NULL,  NULL,  NULL  )  )  goto  errLabel;
						if  (  messengerInfo.uiType  !=  CONST_objType_imGrp  )  goto  errLabel;
						//
						if  (  procQmObjQ(  pSci,  (  QM_OBJQ  *  )pMisCnt->pObjQ,  db.m_pDbMem->pDb,  pQyMc->cfg.db.iDbType,  messengerInfo.uiType,  &messengerInfo,  &mem  )  )  goto  errLabel;
					#endif
				}		
				pQMem  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;
				if  (  !pQMem  )  goto  errLabel;
				if  (  pQMem->uiType  !=  CONST_objType_imGrp  )  goto  errLabel;
#endif
				//
				pAddr_logicalPeer->idInfo.ui64Id  =  pRoute->idInfo_to.ui64Id;
		  }
	}

	iErr  =  0;
errLabel:
	return  iErr;
}

   int  myGetPeer(  LPCTSTR  misServName,  MSG_ROUTE  *  pRoute,  MSGR_ADDR  *  pAddr_logicalPeer,  MSGR_ADDR  *  pPeer  )
{
	int			iErr		=	-1;
	
	//
	if  (  !misServName  ||  !pRoute  ||  !pAddr_logicalPeer  ||  !pPeer  )  return  -1;

	lstrcpyn(  pPeer->misServName,  misServName,  mycountof(  pPeer->misServName  )  );
	pPeer->uiObjType  =  pRoute->uiObjType_src;
	//
	pPeer->idInfo.ui64Id  =  pAddr_logicalPeer->idInfo.ui64Id;
	pPeer->uiDevType  =  pAddr_logicalPeer->uiDevType;
	safeWcsnCpy(  pAddr_logicalPeer->wDevIdStr,  pPeer->wDevIdStr,  mycountof(  pPeer->wDevIdStr  )  );
	//
	pPeer->uiLogonId  =  pRoute->uiLogonId;

	
#if  0	//  2014/09/29
	if  (  pRoute->wReversePath[0]  )  {	//  µ±wReversePathÀïÓÐÄÚÈÝÊ±£¬±íÃ÷£¬ÊÇ¾­¹ýÁË×ª·¢¶øÀ´¡£Òò´Ë£¬ÐèÒª½«Ô­Ê¼·¢°ü¶ÔÏóÈ¡³ö¡£²¢½«forwardPath´æÈëwPathÖÐ
		 TCHAR				*	pT  =  NULL;
		 TCHAR				*	pStr;
		 TCHAR					tBuf[255  +  1];
		 char					buf[255  +  1];
		 QY_MESSENGER_ID		idInfo;

		 //
		 if  (  _tcschr(  pRoute->wReversePath,  _T(  '|'  )  )  )  {
			 traceLogA(  (char*)  "Ê§°Ü£ºÔÝÊ±Ö»Ö§³ÖÒ»¸ö×ª·¢."  );  goto  errLabel;
		 }
		 //
		 _sntprintf(  pPeer->wPath,  mycountof(  pPeer->wPath  ),  _T(  "im://%s/%I64u/%s"  ),  pPeer->misServName,  pPeer->idInfo.ui64Id,  pPeer->wDevIdStr  );
		 switch  (  pPeer->uiObjType  )  {
				 case  CONST_objType_phoneGuest:
					   if  (  !_tcsnicmp(  pRoute->wReversePath,  CONST_str_phone,  lstrlen(  CONST_str_phone  )  )  )  {
						   pT  =  pRoute->wReversePath  +  lstrlen(  CONST_str_phone  );
						   if  (  *pT  !=  _T(  ':'  )  )  goto  errLabel;
						   pT  ++  ;
						   safeWcsnCpy(  pT,  pPeer->wDevIdStr,  mycountof(  pPeer->wDevIdStr  )  );
						   if  (  (  pT  =  _tcschr(  pPeer->wDevIdStr,  _T(  '|'  )  )  )  )  *pT  =  0;
						   //
						   pPeer->idInfo.ui64Id  =  0;
						   pPeer->uiDevType  =  CONST_objType_phone;
						   //
						   break;
					   }
					   
					   if  (  !_tcsnicmp(  pRoute->wReversePath,  CONST_str_im,  lstrlen(  CONST_str_im  )  )  )  {
						   pT  =  pRoute->wReversePath  +  lstrlen(  CONST_str_im  );
						   if  (  *pT  !=  _T(  ':'  )  )  goto  errLabel;
						   pT  ++  ;						   				
						   pStr  =  _T(  "//"  );
						   if  (  _tcsnicmp(  pT,  pStr,  lstrlen(  pStr  )  )  )  goto  errLabel;
						   pT  =  pT  +  lstrlen(  pStr  );
						   //
						   if  (  !(  pT  =  _tcschr(  pT,  _T(  '/'  )  )  )  )  goto  errLabel;
						   pT  ++  ;
						   safeWcsnCpy(  pT,  tBuf,  mycountof(  tBuf  )  );
						   if  (  !(  pT  =  _tcschr(  tBuf,  _T(  '/'  )  )  )  )  goto  errLabel;
						   *pT  =  0;  pT  ++  ;
						   myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &idInfo  );
						   //
						   if  (  _tcsnicmp(  pT,  CONST_str_phone,  lstrlen(  CONST_str_phone  )  )  )  {
							   traceLogA(  (char*)  "Ä¿Ç°Ö»Ö§³Öphone"  );  goto  errLabel;
						   }
						   //
						   pPeer->idInfo.ui64Id  =  idInfo.ui64Id;
						   pPeer->uiDevType  =  CONST_objType_phone;
						   pPeer->wDevIdStr[0]  =  0;
						   //
						   break;
					   }
					   

					   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s : [%s]"  ),  _T(  "Path is wrong"  ),  pRoute->wReversePath  );
					   goto  errLabel;

					   break;
				 default:
					     qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "myGetPeer:  uiObjType err: [%d]"  ),  pPeer->uiObjType  );
					     traceLogA(  (char*)  "CDlgTalk::bSetDlgInfo:  Ä¿Ç°ÔÝÊ±Ö»Ö§³Ö¶ÔphoneµÄ·ÖÎö"  );  goto  errLabel;
						 break;
		 }
		 //
	 }
#endif

	iErr  =  0;
errLabel:
	return  iErr;
}


 int  __cdecl  myCompare_searchGuestByDevIdStr(  const  void  *  key,  const  void  *  pElemParam  )
{
	IS_GUEST_ELEM				*	pGuest			=	(  IS_GUEST_ELEM  *  )key;
	IS_GUEST_ELEM				*	pElem			=	*(  IS_GUEST_ELEM  **  )pElemParam;

	if  (  pGuest->uiDevType  !=  pElem->uiDevType  )  return  pGuest->uiDevType  -  pElem->uiDevType;

	switch  (  pGuest->uiDevType  )  {
		    case  CONST_objType_phone:
				  return  _wcsicmp(  pGuest->wDevIdStr,  pElem->wDevIdStr  );
			default:
					break;
	}

	return  -1;
	
}

 int  __cdecl  myCompare_sortGuestByDevIdStr(  const  void  *  key,  const  void  *  pElemParam  )
{
	return  myCompare_searchGuestByDevIdStr(  key,  pElemParam  );
}


 int  printGuests(  void  **  ppElem,  unsigned  int  uiQNodes  )
{
	IS_GUEST_ELEM	*	pGuest;
	int					i;

	#ifndef  __DEBUG__
			 return  0;
	#endif

	traceLog((TCHAR*)  _T(  "printGuests enters"  )  );

	for  (  i  =  0;  i  <  (  int  )uiQNodes;  i  ++  )  {
		 pGuest  =  (  IS_GUEST_ELEM  *  )ppElem[i];
		 traceLog((TCHAR*)  _T(  "\t%d¸guest %s"  ),  i,  pGuest->wDevIdStr  );
	}

	traceLog((TCHAR*)  _T(  "printGuests leaves"  )  );

	return  0;
}


 //
 int  procMsgTalk_work(  QY_MC  *  pQyMc,  QY_SERVICEGUI_INFO  *  pSci,  MC_VAR_isCli  *  pProcInfo,  MIS_MSG_TALK  *  pMsg,  unsigned  int  lenInBytes_msg,  CTX_MC_THREAD  *  pCtxParam,  MIS_CHANNEL  *  pChannel  )
{
	int					iErr								=	-1;
	MIS_CNT			*	pMisCnt								=	(  MIS_CNT  *  )pMsg->pMisCnt;
	CTX_MC_work		*	pCtx								=	(  CTX_MC_work  *  )pCtxParam;
	int					iDbType								=	pQyMc->cfg.db.iDbType;
	char				timeBuf[CONST_qyTimeLen  +  1]		=	"";
	TCHAR			*	pT;
    
	if  (  isUcFlgResp(  pMsg->ucFlg  )  )  return  0;
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if (!pDbFuncs)  return  -1;// goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

#ifndef  __NOTSUPPORT_DB__  //  {

#if  0
	switch  (  pMsg->data.route.uiObjType_src  )  {
			case  CONST_objType_phoneGuest:  	//  2008/01/18
				  IS_GUEST_ELEM		guest;
				  IS_GUEST_ELEM	**	ppElem;


				  break;
			default:
					break;
	}
#endif

	//  ÔÚuiDevType_to·Ç0µÄÇé¿öÏÂ£¬ÊÇÒª·¢ËÍµ½Ä³Éè±¸ÉÏµÄ¡£Îª0Ê±£¬ÔòÊÇ·¢ËÍµ½½çÃæÉÏ
	//
#if  0
	if  (  pMsg->data.route.uiDevType_to  )  {
		char					idStr_from[CONST_qyMessengerIdStrLen  +  1]	=	"";
		IM_CONTENTU		*	pContent									=	NULL;
		BOOL					bPhoneNoOk									=	FALSE;
		WCHAR					wForwardPath[510  +  1]						=	_T(  ""  );
		TCHAR				*	pStr;
		TCHAR					tBuf[255  +  1];
		char					buf[255  +  1];
		QY_MESSENGER_ID			idInfo_to;
		//
		//  
		//
		idInfo2Str(  &pMsg->data.route.idInfo_from,  idStr_from,  mycountof(  idStr_from  )  );
		pContent  =  (  IM_CONTENTU  *  )pMsg->data.buf;
		switch  (  pMsg->data.route.uiDevType_to  )  {
				case  CONST_objType_dev:
					  if  (  pContent->uiType  ==  CONST_imCommType_htmlContent  )  {
						  if  (  myVDev_postStr2Dev(  pQyMc,  idStr_from,  pMsg->tStartTime,  pMsg->uiTranNo,  pMsg->usSeqNo,  pContent->html.wBuf,  pMsg->data.route.uiDevType_to,  pMsg->data.route.wDevIdStr_to,  wForwardPath,  NULL,  0  )  )  goto  errLabel;
						  }
					  else  {
						    traceLogA(  (char*)  "failed: ÔÝÊ±Ö»Ö§³Öhtml"  );  goto  errLabel;							
					  }					  
					  break;
				default:
						traceLogA(  (char*)  "failed:  uiDevType_to [%d] err, ¶ÔuiDevType_to, ÔÝÊ±Ö»Ö§³Ödev",  pMsg->data.route.uiDevType_to  );  goto  errLabel;
						break;
		}
		//
		iErr  =  0;  goto  errLabel;
	}
#endif

#endif  //  }

	//
	MIS_MSG_routeTalkData* pTalkData;pTalkData = &pMsg->data;
	IM_CONTENTU					*	pContent							=	(  IM_CONTENTU  *  )pTalkData->buf;	
	TCHAR							senderDesc[1]						=	_T(  ""  );
	TCHAR							receiverDesc[1]						=	_T(  ""  );

	switch  (  pContent->uiType  )  {
			case  CONST_imCommType_htmlContent:  {
				  //  2015/02/16
				  IM_HTML_CONTENT  *  pReq  =  &pContent->html;
					
				  if  (  pReq->idInfo_logicalPeer.ui64Id  )  {							  
					  if  (  !pMisCnt  )  goto  errLabel;
					  if  (  pReq->idInfo_logicalPeer.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
						  showInfo_open0(  0,  0,  _T(  "procMsgTalk_work failed, req.idInfo_logicalPeer is me"  )  );
						  goto  errLabel;							  
					  }						
					  pMsg->addr_logicalPeer.idInfo.ui64Id  =  pReq->idInfo_logicalPeer.ui64Id;
				  }
				  //
				  if (pMsg->addr_logicalPeer.idInfo.ui64Id) {
					  if (pMsg->addr_logicalPeer.idInfo.ui64Id != pMsg->data.route.idInfo_from.ui64Id) {
						  bool  bGrp = true;
						  //
						  unsigned  int  uiObjType = 0;
						  getTalkerDesc(pMsg->addr_logicalPeer.idInfo, &uiObjType, mynull, 0, mynull, mynull, 0, mynull, 0, mynull, 0);
						  if (!uiObjType) {
							  CQnmDb db;
							  if (!db.getAvailableDb(pQyMc->iDsnIndex_mainSys))  goto  errLabel;
							  void* pDb = db.m_pDbMem->pDb;
							  uiObjType = CONST_objType_tmpGrp;
							  IM_GRP_INFO  grpInfo;
							  memset(&grpInfo, 0, sizeof(grpInfo));
							  grpInfo.idInfo.ui64Id = pMsg->addr_logicalPeer.idInfo.ui64Id;
							  recoverImGrp(&g_dbFuncs, pDb, pQyMc->cfg.db.iDbType, CONST_fieldIdTable_en, uiObjType, &grpInfo, 0, true);
						  }
					  }
				  }
				  //  getTalkerDesc(  pMisCnt,  &pTalkData->route.idInfo_to,  receiverDesc,  mycountof(  receiverDesc  ),  NULL,  0  );
				  //  postImMsg2Log(  pMisCnt->cfg.misServName,  &pTalkData->route.idInfo_from,  senderDesc,  pMsg->tStartTime,  pMsg->uiTranNo,  &pTalkData->route.idInfo_to,  receiverDesc,  pContent->uiType,  pContent->html.wBuf,  NULL,  pMsg->tRecvTime,  &pProcInfo->schedulerQ  );
				  pProcInfo->postImMsg2Log_isClient(  (  MIS_MSGU  *  )pMsg,  lenInBytes_msg  );
				  }
				  break;
			default:
					break;
	}

	//
	if  (  qPostMsg(  pMsg,  lenInBytes_msg,  &pQyMc->gui.processQ,  _T(  "procmsgTalk_work"  ))) {
		traceLogA(  (char*)  "mcThreadProc_mis_work(  ): qPostMsg(  ) failed"  );
		goto  errLabel;
	}
	PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );    


	iErr  =  0;

errLabel:

	return  iErr;
}


//  ÔÝÊ±ÑØÓÃrobot Ãû³Æ£¬Êµ¼ÊÊÇÒ»¸ö´¦ÀíÈÎÎñµÄ¹²Í¬º¯Êý


  extern "C" DWORD WINAPI mcThreadProc_mis_work( LPVOID lpParameter )
{
	 QY_SERVICEGUI_INFO			*		pSci							=	(  QY_SERVICEGUI_INFO  *  )lpParameter;
	 if  (  !pSci  )  return  -1;
	 MC_VAR_isCli				*		pProcInfo						=	(  MC_VAR_isCli  *  )pSci->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 QY_MC						*		pQyMc							=	pProcInfo->pQyMc;
	 if  (  !pQyMc  )  return  -1;

	 int								loopCtrl						=	0;
	 DWORD								dwThreadId						=	GetCurrentThreadId(  );
	 CQyMalloc							mallocObj;
	 MIS_MSGU					*		pMsg							=	NULL;
	 unsigned  int						len;
	 DWORD								dwRet;
	 //
	 CTX_MC_work						ctx;
	 //
	 //  CWnd						*		pMainWnd						=	AfxGetApp(  )->m_pMainWnd;
	 //
	 unsigned  int						uiChannelType					=	CONST_channelType_talking;
	 	 
	 traceLogA(  (char*)  "mcThreadProc_mis_work:  enters"  );

	 memset(  &ctx,  0,  sizeof(  ctx  )  );

	 if  (  !(  pMsg  =  (  MIS_MSGU  *  )mallocObj.mallocf(  CONST_iAllocType_longTimeMsg,  sizeof(  MIS_MSGU  )  )  )  )  goto  errLabel;

	 if  (  initGenericQ(  &pProcInfo->cfg.guestQ,  mymalloc,  0,  0,  myfree,  NULL,  &ctx.guestQ  )  )  goto  errLabel;
	 ctx.bGuestQInited  =  TRUE;
	 //
	 if  (  pProcInfo->cfg.guestQ.uiMaxQNodes  )  {
		 len  =  sizeof(  void  *  )  *  pProcInfo->cfg.guestQ.uiMaxQNodes;
		 ctx.ppGuests_sortedByDevIdStr  =  (  void  **  )mymalloc(  len   );
		 if  (  !ctx.ppGuests_sortedByDevIdStr  )  goto  errLabel;
		 memset(  ctx.ppGuests_sortedByDevIdStr,  0,  len  );
	 }

	 //  2007/06/20
	 #ifndef  __NOTSUPPORT_DB__
			  if  (  !bObjDbAvail(  getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  )  )  )  {
				  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "thread_work failed, bObjDbAvail failed"  )  );
				  #endif
				  goto  errLabel;
			  }
	 #endif

	 for  (  ;  !pQyMc->bQuit;  )  {
		 if (!pQyMc->bLogon) {
			 break;
		 }

		  //  if  (  !pMainWnd  )  pMainWnd					=	AfxGetApp(  )->m_pMainWnd;
		  if  (  !pQyMc->gui.hMainWnd  )  {
			  Sleep(  1000  );  continue;
		  }

		  dwRet  =  WaitForSingleObject(  pProcInfo->workQ.hSemaTrigger,  5000  );
		  if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;
		  
		  for  (  ;  !pQyMc->bQuit;  )  {
			   len  =  sizeof(  pMsg[0]  );
			   if  (  qGetMsg(  &pProcInfo->workQ,  pMsg,  &len  )  )  break;
			   memset(  (  (  char  *  )pMsg  )  +  len,  0,  min(  256,  sizeof(  pMsg[0]  )  -  len  )  );			   
			   switch  (  pMsg->uiType  )  {
					   case  CONST_misMsgType_input:  {
						     MIS_CNT		*  pMisCnt  =  (  MIS_CNT  *  )pMsg->input.pMisCnt;
							 MIS_CHANNEL	*  pChannel	=	NULL;

							 if  (  !pMisCnt  )  {
								 traceLogA(  (char*)  "mcThreadProc_mis_work failed: pMisCnt is null"  );
								 break;
							 }
							 if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  uiChannelType  )  )  )  break;

						     if  (  !isUcFlgResp(  pMsg->input.ucFlg  )  )  {
								 if  (  procMsgInput_other_req(  pQyMc,  pSci,  pProcInfo,  &pMsg->input,  len,  (  CTX_MC_THREAD  *  )&ctx,  pChannel  )  )  break;							 								
								 break;
							 }
							
							 if  (  procMsgInput_work_resp(  pQyMc,  pSci,  pProcInfo,  &pMsg->input,  len,  (  CTX_MC_THREAD  *  )&ctx,  pChannel  )  )  break;																
							 //
							 }
						     break;
					   case  CONST_misMsgType_talk:  {
						     MIS_CNT			*	pMisCnt		=	(  MIS_CNT  *  )pMsg->talk.pMisCnt;
						     IM_CONTENTU		*	pContent	=	(  IM_CONTENTU  *  )pMsg->talk.data.buf;
							 MIS_CHANNEL		*	pChannel	=	NULL;
	
							 if  (  !pMisCnt  )  {
								 traceLogA(  (char*)  "mcThreadProc_mis_work: pMisCnt is null"  );
								 break;
							 }
							 if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  uiChannelType  )  )  )  break;

							 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%I64u [%s]"  ),  pMsg->talk.data.route.idInfo_from.ui64Id,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_pcCommTypeTable  ),  pContent->uiType  )  );
	
							 if  (  getIdInfo_logicalPeer(  pSci,  pMisCnt,  &pMsg->talk.data.route,  &pMsg->talk.addr_logicalPeer  )  )  break;

							 traceLogA(  (char*)  "mcThreadProc_mis_work(  ): talk"  );

							 //  
							 if  (  procMsgTalk_work(  pQyMc,  pSci,  pProcInfo,  &pMsg->talk,  len,  (  CTX_MC_THREAD  *  )&ctx,  pChannel  )  )  break;

							 }
						     break;
					   case  CONST_misMsgType_task:  {
						     MIS_CNT			*	pMisCnt		=	(  MIS_CNT  *  )pMsg->task.pMisCnt;
						     IM_CONTENTU	*	pContent	=	(  IM_CONTENTU  *  )pMsg->task.data.buf;
	
							 if  (  !pMisCnt  )  {
								 traceLogA(  (char*)  "mcThreadProc_mis_work: pMisCnt is null"  );
								 break;
							 }

							 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%I64u [%s]"  ),  pMsg->task.data.route.idInfo_from.ui64Id,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_pcCommTypeTable  ),  pContent->uiType  )  );
	
							 traceLogA(  (char*)  "mcThreadProc_mis_work: task"  );				
													 
							 }							 
						     break;
					   default:
								traceLogA(  (char*)  "mcThreadProc_mis_work failed, unknown  msgType %d",  pMsg->uiType  );
								break;
			   }
		
			   dwRet  =  WaitForSingleObject(  pProcInfo->workQ.hSemaTrigger,  50  );
			   if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;			   
		  }
	 }


errLabel:


	 if  (  ctx.ppGuests_sortedByDevIdStr  )  free(  ctx.ppGuests_sortedByDevIdStr  );
	 if  (  ctx.bGuestQInited  )  exitGenericQ(  &ctx.guestQ  );

	 traceLogA(  (char*)  "mcThreadProc_mis_work:  leaves"  );

	 pProcInfo->status.threadsStatus.ulbWorkQuit  =  TRUE;
	 
	 return  0;
}

















 int  printDisplayedObjQ(  void  **  pp,  unsigned  int  cnt  )
{
	int										i;
	DISPLAYEDELEM_MESSENGER_TREE		*	pElem;
	for  (  i  =  0;  i  <  (  int  )cnt;  i  ++  )  {
		 pElem  =  (  DISPLAYEDELEM_MESSENGER_TREE  *  )pp[i];
		 traceLogA(  (char*)  "\tµÚ%d¸ö, id is %I64u, hTree is %u",  i,  pElem->idInfo.ui64Id,  (  long  )pElem->hItem  );
		 
	}
	return  0;
}










 













 // Ã¿´Î¶¼´ÓrecentFriendQÀïÈ¡³ö²»³¬¹ýuiMaxMessengerRecentFriendsµÄ²»Í¬recentFriend×é°ü£¬·¢ËÍµ½·þÎñÆ÷¶Ë¡£
 int  startToRefreshRecentFriends(  MIS_CNT  *  pMisCnt,  MIS_MSGU  *  pMsgBuf  )
{
	int										iErr								=	-1;
	int										i;
	int										j;
	REFRESH_RECENTFRIENDS_REQ_h				req;
	MIS_MSG_RECENTFRIEND_QMC				msg;
	unsigned  int							len;
	unsigned  int							uiQCnt;
	//unsigned  int							uiTranNo;
	TCHAR									tBuf[128];

	//
	if  (  !pMisCnt  )  return  -1;
	MC_VAR_isCli  *  pProcInfo  =  (  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  {
		#ifdef  __DEBUG__
				MACRO_qyAssert(  0,  _T(  "startToRefreshRecentFriends: pMisCnt->pProcInfo is null"  )  );
		#endif
		return  -1;
	}

#if  0
	if  (  !isQEmpty(  &pMisCnt->recentFriendQ  )  )  {
		traceLogA(  (char*)  "start to print recentFriendQ"  );
		qTraverse(  &pMisCnt->recentFriendQ,  (  PF_commonHandler  )printMisMsg,  0,  0  );
		traceLogA(  (char*)  "end printing recentFriendQ"  );
	}
#endif


#ifdef  __DEBUG__	//  2014/05/06
#if 0
		if  (  dbg_bNoRefreshRecentFriends(  )  )  {
			return  0;
		}
#endif
#endif


	//  printQmObjQ(  (  QM_OBJQ  *  )pMisCnt->pObjQ  );
	//

	memset(  &req,  0,  sizeof(  req  )  );
	//
	req.uiType  =  CONST_imCommType_refreshRecentFriendsReq;
	req.tLastRefreshedTime_misServ  =  pMisCnt->refreshRecentFriends.tLastRefreshedTime_misServ;
	
	uiQCnt  =  pMisCnt->recentFriendQ.uiQNodes;
	//  traceLogA(  (char*)  "startToRefreshRecentFriends: mycountof( mems ) %d",  mycountof(  req.mems  )  );

	for  (  i  =  0;  i  <  mycountof(  req.mems  )  &&  i  <  (  int  )uiQCnt;  i  ++  )  {
		
		 memset(  &msg,  0,  sizeof(  msg  )  );
		 len  =  sizeof(  msg  );
		 if  (  qGetMsg(  &pMisCnt->recentFriendQ,  &msg,  &len  )  )  break;
		 if  (  msg.uiType  !=  CONST_misMsgType_recentFriend_qmc  )  continue;

		 //  °ÑÕâ¸ö³ÉÔ±¼Óµ½ºóÃæµÄ¿Õ¼äÈ¥
		 for  (  j  =  0;  j  <  req.usCnt;  j  ++  )  {
			  if  (  msg.idInfo.ui64Id  ==  req.mems[req.usCnt].idInfo.ui64Id  )  break;
		 }
		 if  (  j  <  req.usCnt  )  continue;
		 
		 //
		 isCli_addTo_qmObjQ(msg.idInfo);
		 
		 //  ÕâÀïÒª¼ÓÈëÁË£¬Ê×ÏÈÔÚ¶ÓÁÐÀïÕÒÒ»ÏÂ£¬°Ñ¸ÃºÃÓÑµÄ×î½üË¢ÐÂÊ±¼äÈ¡³öÀ´£¬¿´ÊÇ·ñºÍ×ÜÊ±¼äÒ»Ñù
		 QM_OBJQ_MEM				mem;
		 QMEM_MESSENGER_CLI		*	pQMemObj;
		 if  (  findQMemByKey(  0,  pMisCnt->pObjQ,  &msg.idInfo,  &mem  )  )  {
			 //
#ifdef  __DEBUG__
			 _sntprintf(tBuf,mycountof(tBuf),_T("startToRefreshRecentFriends: findQMemByKey failed, idInfo %I64u"),  msg.idInfo.ui64Id    );
			 traceLog(tBuf);			 
#endif
			 //
			 continue;
		 }
		 pQMemObj  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;
		 		 
		 req.mems[req.usCnt].idInfo.ui64Id  =  msg.idInfo.ui64Id;
		 req.mems[req.usCnt].tLastRefreshedTime_misServ  =  pQMemObj->tLastRefreshedTickCnt_misServ;
		 req.usCnt  ++  ;
	}
	//
	len  =  offsetof(  REFRESH_RECENTFRIENDS_REQ_h,  mems  )  +  req.usCnt  *  sizeof(  req.mems[0]  );

	//
	MACRO_prepareForTran();

	//if  (  (  uiTranNo  =  getuiNextTranNo(  0,  0,  0  )  )  ==  -1  )  goto  errLabel;
	if  (  pProcInfo->postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_req,  0,  CONST_qyCmd_refreshRecentFriendsReq,  tStartTran,  uiTranNo,  0,  (  char  *  )&req, len,  NULL,  0,  0,  pMsgBuf,  FALSE  )  )  goto  errLabel;
    
	//
	iErr  =  0;

errLabel:
	
	return  iErr;
}



 



 







//
int  getChannelThreasStatus(  MIS_CHANNEL  *  pChannel  )
{
	int  iStatus  =  0;

	if  (  pChannel->hThread_io  )  iStatus  +=  100;
	if  (  pChannel->ctx.hThread_toSend  )  iStatus  +=  10;
	if  (  pChannel->ctx.hThread_snd  )  iStatus  +=  1;
	return  iStatus;
}


 //
 BOOL  bChkMessengerChannelsReady(  QY_MC  *  pQyMc  )
{
	BOOL					bRet			=	FALSE;
	QY_SERVICEGUI_INFO	*	pSci			=  (  QY_SERVICEGUI_INFO  *  )getServiceGuiInfo(  pQyMc,  pQyMc->iServiceId  );
	if (!pSci)  return  false;// goto  errLabel;
	MC_VAR_isCli			*	pVar			=	(  MC_VAR_isCli  *  )pSci->pVar;
	if (!pVar)  return false;// goto  errLabel;
	int						i;
	MIS_CHANNEL			*	pChannel		=	NULL;
	BOOL					bTalkReady		=	FALSE;
	BOOL					bMediaReady		=	FALSE;
	BOOL					bRtMediaReady	=	FALSE;
	BOOL					bRobotReady		=	FALSE;
	BOOL					bRtOpReady		=	FALSE;


	i  =  0;	
	MIS_CNT  *  pMisCnt  =  getMisCntByIndex(  0,  pVar,  i  );		
	if  (  !pMisCnt  )  return  false;

		//
		 if  (  pMisCnt->cfg.dynCfg.cnt.usCntPort  )  {
			 Param_dbg param;
			 param.m_pHint=(TCHAR*)_T("bChkMessengerChannelsReady.3065");
			 param.m_bShowInfo = false;
			 //
			 if  (  bChannelOk(  getChannelByType(  pMisCnt,  CONST_channelType_talking  ), &param  )  )  bTalkReady  =  TRUE;
			 if  (  bChannelOk(  getChannelByType(  pMisCnt,  CONST_channelType_media  ), &param  )  )  bMediaReady  =  TRUE;  
			 if  (  bChannelOk(  getChannelByType(  pMisCnt,  CONST_channelType_realTimeMedia  ), &param  )  )  bRtMediaReady  =  TRUE;
			 if  (  bChannelOk(  getChannelByType(  pMisCnt,  CONST_channelType_robot  ),&param  )  )  bRobotReady  =  TRUE;
			 if  (  bChannelOk(  getChannelByType(  pMisCnt,  CONST_channelType_rtOp  ), &param  )  )  bRtOpReady  =  TRUE;
		 }
	

	bRet  =  TRUE;

errLabel:
	
	if  (  bRet  )  {
		if  (  pVar  )  {
			DWORD  dwTickCnt  =  myGetTickCount(  NULL  );
			//
			if  (  pVar->av.talk.bChannelReady  !=  bTalkReady  )  {
				pVar->av.talk.bChannelReady  =  bTalkReady;
				pVar->av.talk.dwLastModifiedTickCnt  =  dwTickCnt;
			}
			pVar->av.talk.iThreadsStatus  =  getChannelThreasStatus(  getChannelByType(  pMisCnt,  CONST_channelType_talking  )  );
			//
			if  (  pVar->av.audio.bChannelReady  !=  bRtMediaReady  )  {
				pVar->av.audio.bChannelReady  =  bRtMediaReady;
				pVar->av.audio.dwLastModifiedTickCnt  =  dwTickCnt;
			}
			pVar->av.audio.iThreadsStatus  =  getChannelThreasStatus(  getChannelByType(  pMisCnt,  CONST_channelType_realTimeMedia  )  );
			//
			if  (  pVar->av.video.bChannelReady  !=  bMediaReady  )  {
				pVar->av.video.bChannelReady  =  bMediaReady;
				pVar->av.video.dwLastModifiedTickCnt  =  dwTickCnt;
			}
			pVar->av.video.iThreadsStatus  =  getChannelThreasStatus(  getChannelByType(  pMisCnt,  CONST_channelType_media  )  );
			//
			if  (  pVar->av.robot.bChannelReady  !=  bRobotReady  )  {
				pVar->av.robot.bChannelReady  =  bRobotReady;
				pVar->av.robot.dwLastModifiedTickCnt  =  dwTickCnt;
			}
			pVar->av.robot.iThreadsStatus  =  getChannelThreasStatus(  getChannelByType(  pMisCnt,  CONST_channelType_robot  )  );
			//
			if  (  pVar->av.rtOp.bChannelReady  !=  bRtOpReady  )  {
				pVar->av.rtOp.bChannelReady  =  bRtOpReady;
				pVar->av.rtOp.dwLastModifiedTickCnt  =  dwTickCnt;
			}
			pVar->av.rtOp.iThreadsStatus  =  getChannelThreasStatus(  getChannelByType(  pMisCnt,  CONST_channelType_rtOp  )  );
			
			//
		}		
	}

	return  bRet  ;

}






#if  10  //  2015/07/19
 BOOL  tmp_bChkQyMcEnv_mis(  void  *  pQY_MC  )
{
#ifdef  __NOTSUPPORT_DB__
	return  TRUE;
#else

	QY_MC  *  pQyMc  =  (  QY_MC  *  )pQY_MC;

	BOOL		bRet								=	FALSE;
	CQnmDb		db;
	TCHAR		sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if (!pDbFuncs)  return false;// goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	#ifdef  __DEBUG__
			traceLogA(  (char*)  "bCheckQyMcEnv_mis:  enters"  );
	#endif

	if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;

	//  2012/07/14
	if  (  db.m_pDbMem->iDbType  ==  CONST_dbType_myDb  )  {
		bRet  =  TRUE;  goto  errLabel;
	}

	#ifdef  __DEBUG__
			traceLogA(  (char*)  "½«misTaskStatus_waitToRecvºÍwaitToSend¶¼¸ÄÎªapply"  );
	#endif
#if  0
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set iStatus=%d where iStatus=%d or iStatus=%d"  ),  CONST_tabName_qyImTaskTab,  CONST_imTaskStatus_sendBreak,  CONST_imTaskStatus_applyToSend,  CONST_imTaskStatus_waitToSend  );
	if  (  !bQyExecSql(  db.m_pDbMem->pDb,  sqlBuf  )  )  goto  errLabel;
#endif 
	if  (  !g_dbFuncs.pf_bUpdateImTask_bChkQyMcEnv_mis(  db.m_pDbMem->pDb,  CONST_imTaskStatus_sendBreak,  CONST_imTaskStatus_applyToSend,  CONST_imTaskStatus_waitToSend  )  )  goto  errLabel;

#if  0
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set iStatus=%d where iStatus=%d or iStatus=%d"  ),  CONST_tabName_qyImTaskTab,  CONST_imTaskStatus_recvBreak,  CONST_imTaskStatus_applyToRecv,  CONST_imTaskStatus_waitToRecv  );
	if  (  !bQyExecSql(  db.m_pDbMem->pDb,  sqlBuf  )  )  goto  errLabel;
#endif
	if  (  !g_dbFuncs.pf_bUpdateImTask_bChkQyMcEnv_mis(  db.m_pDbMem->pDb,  CONST_imTaskStatus_recvBreak,  CONST_imTaskStatus_applyToRecv,  CONST_imTaskStatus_waitToRecv  )  )  goto  errLabel;

	bRet  =  TRUE;
errLabel:

	#ifdef  __DEBUG__
			traceLogA(  (char*)  "bCheckQyMcEnv_mis:  leaves"  );
	#endif

	return  bRet;
#endif
}
#endif


//
int  tmpHandler_findAValidConversation(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int				iErr	=	-1;
	//  HWND			hWnd_last	=	(  HWND  )p0;
	HWND		*	phWnd_next	=	(  HWND  *  )p1;
	MIS_MSGU	*	pMsg	=	(  MIS_MSGU  *  )p2;

	if  (  pMsg->uiType  ==  CONST_misMsgType_talkingFriend_qmc  )  {
		if  (  IsWindow(  pMsg->talkingFriend_qmc.hWnd  )  )  {
			*phWnd_next  =  pMsg->talkingFriend_qmc.hWnd;
			iErr  =  1;  goto  errLabel;
		}
	}

	iErr  =  0;
errLabel:
	return  iErr;

}


 int  closeAllConversations(  LPVOID  pQyMcParameter,  BOOL  *  pbConversationExists  )
{
	 int							iErr					=	-1;
	 QY_MC					*		pQyMc					=	( QY_MC * )pQyMcParameter;
	 int							iServiceId				=	CONST_qyServiceId_mis;
	 QY_SERVICEGUI_INFO		*		pSci					=	getServiceGuiInfo(  pQyMc,  iServiceId  );
	 if  (  !pSci  )  return  -1;
	 MC_VAR_isCli				*		pProcInfo				=	(  MC_VAR_isCli  *  )pSci->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 //
	 int							i;
	 MIS_CNT				*		pMisCnt					=	0;
	 BOOL							bConversationExists		=	FALSE;


	 traceLogA(  (char*)  "closeAllConversations enters"  );

	 //for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  
	 for  (  i  =  0;  i  <  pProcInfo->ucCnt_misCnts;  i  ++  )  
	 {
		 pMisCnt  =  getMisCntByIndex(  0,  pProcInfo,  i  );//&pProcInfo->misCnts[i];
		 if  (  !pMisCnt  )  continue;
		 if  (  pMisCnt->cfg.dynCfg.cnt.usCntPort  )  {
			 //
			 //  HWND	hWnd_last  =  NULL;  
			 HWND	hWnd_next  =  NULL;
			 for  (  int  j  =  0;  j  <  pMisCnt->talkingFriendQ.cfg.uiMaxQNodes;  j  ++  )  {
				  
				  if  (  !qTraverse(  &pMisCnt->talkingFriendQ,  tmpHandler_findAValidConversation,  NULL,  &hWnd_next  )  )  break;
				  SendMessage(  hWnd_next,  WM_CLOSE,  0,  0  );
				  if  (  IsWindow(  hWnd_next  )  )  {
					  //  not closed.
					  break;
				  }

			 }
			 //
			 if  (  pMisCnt->talkingFriendQ.uiQNodes  )  {
				 if  (  qTraverse(  &pMisCnt->talkingFriendQ,  tmpHandler_findAValidConversation,  NULL,  &hWnd_next  )  >  0  )  {
					 bConversationExists  =  TRUE;
				 }
				 if  (  !bConversationExists  )  {
					 traceLog((TCHAR*)  _T(  "serious error"  )  );
				 }
			 }
			 //
		 }
	 }


	 if  (  pbConversationExists  )  *pbConversationExists  =  bConversationExists;

	 traceLogA(  (char*)  "closeAllConversations leaves"  );

	 return  0;
}


 //
 bool  isValid_qwmDynCfg(QWM_DYN_CFG* pDynCfg)
 {
	 bool  bRet = false;
	 do {
		 if (pDynCfg->cnt.cntIp[0]) {
			 bRet = true; break;
		 }

		 int  i;
		 for (i = 0; i < mycountof(pDynCfg->cnt.cntAddrs); i++) {
			 if (pDynCfg->cnt.cntAddrs[i][0]) {
				 break;
			 }
		 }
		 if (i == mycountof(pDynCfg->cnt.cntAddrs)) {
			 break;
		 }
		 bRet = true;
		 //
	 } while (false);

	
	 //
	 return  bRet;

 }



 //
 extern "C" DWORD WINAPI mcThreadProc_isCli( LPVOID lpParameter )
{
	 int							iErr				=	-1;
	 QY_MC					*		pQyMc				=	( QY_MC * )lpParameter;
	 int							iServiceId			=	CONST_qyServiceId_mis;
	 QY_SERVICEGUI_INFO		*		pSci				=	getServiceGuiInfo(  pQyMc,  iServiceId  );
	 //
	 MC_VAR_isCli				*		pProcInfo			=	(  MC_VAR_isCli  *  )pSci->pVar;
	 int							i;
	 BOOL							bInited				=	FALSE;
	 DWORD							dwThreadDaemonId;
	 int							loopCtrl			=	0;
	 //  QY_LOGICAL_SERVER				tmpCnt;
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if (!pDbFuncs)  return  -1;// goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;
	 

	 traceLogA(  (char*)  "mcThreadProc_mis enters"  );
	 	 

	 for  (  ;  ;  Sleep(  2500  )  )  {			//  ÕâÀïÏÈµÈ´ýÓÃ»§µÇÂ½ÁË£¬ÔÙ¿ªÊ¼×öÏÂÃæµÄÊÂ
		  if  (  pQyMc->bQuit  )  goto  errLabel;
		  if  (  !pQyMc->bLogon  )  continue;		//  2007/05/30

#if  0
		  if  (  !myStr2TChar(  pQyMc->curUsrInfo.name,  pProcInfo->authInfo.messengerName,  mycountof(  pProcInfo->authInfo.messengerName  )  )  )  {
			  traceLogA(  (char*)  "ÓÃ»§ÃûÌ«³¤£¬·Å²»½øauthInfo.messengerNameÀïÈ¥"  );
			  goto  errLabel;
		  }
#endif
		  break;
	 }

	 //
	 if  (  !pQyMc->bChkQyMcEnv_mis(  )  )  {
		 #ifdef  __DEBUG__
				 traceLog((TCHAR*)  _T(  "mcThreadProc_isCli failed, bChkQyMcEnv_mis failed"  )  );
		 #endif
		 goto  errLabel;
	 }
     

	 //for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  
	 for  (  i  =  0;  i  <  pProcInfo->ucCnt_misCnts;  i  ++  )  
	 {
		  MIS_CNT		*	pMisCnt		=	getMisCntByIndex(  0,  pProcInfo,  i  );//&pProcInfo->misCnts[i];
		  if  (  !pMisCnt  )  continue;
		  MIS_CHANNEL	*	pChannel	=	NULL;

		  if  (  pMisCnt->cfg.dynCfg.cnt.usCntPort  )  {
			  //
			  if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  CONST_channelType_talking  )  )  )  goto  errLabel;
			  //
			  //  pMisCnt->pAuthInfo  =  &pProcInfo->authInfo;

			  clearQySock(  &pChannel->sock  );

			  #ifndef  __NOTSUPPORT_DB__
			  {	  //  »ñÈ¡±¾µØµÄqqºÅ
				  CQnmDb				db;
				  QY_MESSENGER_INFO		messengerInfo;

				  if  (  bObjDbAvail(  getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  )  )  
					  &&  db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )
					  &&  db.m_pDbMem->iDbType  !=  CONST_dbType_myDb  )  
				  {
					  if  (  g_dbFuncs.pf_bGetMeInfoBySth(  db.m_pDbMem->pDb,  pSci->cfg.iDbType,  pMisCnt->cfg.misServName,  &messengerInfo  )  )  pMisCnt->idInfo.ui64Id  =  messengerInfo.idInfo.ui64Id;
					  //
					  g_dbFuncs.pf_bClearupDeletedImObjs_isClient(  pMisCnt,  db.m_pDbMem->pDb,  pSci->cfg.iDbType  );
					  //
					  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Start to moveTask2His"  )  );
					  //
					  g_dbFuncs.pf_bMoveTask2His(  pMisCnt,  db.m_pDbMem->pDb,  pSci->cfg.iDbType  );
					  //
					  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "MoveTask2His finished"  )  );
					  //
					  g_dbFuncs.pf_bStatImTasks(  pProcInfo,  pMisCnt,  db.m_pDbMem->pDb,  pSci->cfg.iDbType  ); 
				  }
			  }
			  #endif
		  }
	 }

	 //
	 pProcInfo->status.ulbThreadProcInited  =  TRUE;	//  2007/09/02, ¸æÖªgui¿ÉÒÔÆô¶¯´°¿ÚÁË

	 memset(&pProcInfo->status.threadsStatus, 0, sizeof(pProcInfo->status.threadsStatus));

	 //
#ifdef  __DEBUG__
	 traceLogA((char*)"mcThreadProc_isCli inited");
#endif
	 
	 //  ÏÂÃæÎª´´½¨Ò»Ð©ÆÕÍ¨µÄÏß³Ì¡£
	 pProcInfo->hThread_mgr  =  CreateThread(  NULL,  0,  mcThreadProc_mis_mgr,  pSci,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
	 if  (  !pProcInfo->hThread_mgr  )  goto  errLabel;
	 pProcInfo->dwThreadId_mgr  =  dwThreadDaemonId;
	 if  (  ResumeThread(  pProcInfo->hThread_mgr  )  ==  -1  )  goto  errLabel;
	 //
	 pProcInfo->hThread_robot  =  CreateThread(  NULL,  0,  mcThreadProc_mis_robot,  pSci,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
	 if  (  !pProcInfo->hThread_robot  )  goto  errLabel;
	 pProcInfo->dwThreadId_robot  =  dwThreadDaemonId;
	 if  (  ResumeThread(  pProcInfo->hThread_robot  )  ==  -1  )  goto  errLabel;
	 //
	 pProcInfo->hThread_display  =  CreateThread(  NULL,  0,  mcThreadProc_mis_display,  pSci,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
	 if  (  !pProcInfo->hThread_display  )  goto  errLabel;
	 pProcInfo->dwThreadId_display  =  dwThreadDaemonId;
	 if  (  ResumeThread(  pProcInfo->hThread_display  )  ==  -1  )  goto  errLabel;
	 //
	 pProcInfo->hThread_work  =  CreateThread(  NULL,  0,  mcThreadProc_mis_work,  pSci,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
	 if  (  !pProcInfo->hThread_work  )  goto  errLabel;
	 pProcInfo->dwThreadId_work  =  dwThreadDaemonId;
	 if  (  ResumeThread(  pProcInfo->hThread_work  )  ==  -1  )  goto  errLabel;
	 //
	 pProcInfo->hThread_scheduler  =  CreateThread(  NULL,  0,  mcThreadProc_mis_scheduler,  pSci,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
	 if  (  !pProcInfo->hThread_scheduler  )  goto  errLabel;
	 pProcInfo->dwThreadId_scheduler  =  dwThreadDaemonId;
	 if  (  ResumeThread(  pProcInfo->hThread_scheduler  )  ==  -1  )  goto  errLabel;
	 //  
	 pProcInfo->hThread_media  =  CreateThread(  NULL,  0,  mcThreadProc_mis_media,  pSci,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
	 if  (  !pProcInfo->hThread_media  )  goto  errLabel;
	 pProcInfo->dwThreadId_media  =  dwThreadDaemonId;
	 if  (  ResumeThread(  pProcInfo->hThread_media  )  ==  -1  )  goto  errLabel;
	 //
	 pProcInfo->hThread_realTimeMedia  =  CreateThread(  NULL,  0,  mcThreadProc_mis_realTimeMedia,  pSci,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
	 if  (  !pProcInfo->hThread_realTimeMedia  )  goto  errLabel;
	 pProcInfo->dwThreadId_realTimeMedia  =  dwThreadDaemonId;
	 if  (  ResumeThread(  pProcInfo->hThread_realTimeMedia  )  ==  -1  )  goto  errLabel;
	 //  2016/12/26
	 pProcInfo->hThread_rtOp  =  CreateThread(  NULL,  0,  mcThreadProc_mis_rtOp,  pSci,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
	 if  (  !pProcInfo->hThread_rtOp  )  goto  errLabel;
	 pProcInfo->dwThreadId_rtOp  =  dwThreadDaemonId;
	 if  (  ResumeThread(  pProcInfo->hThread_rtOp  )  ==  -1  )  goto  errLabel;
	 

	 //
#ifdef  __DEBUG__
	 traceLogA(  (char*)  "mcThreadProc_mis: subThreads started"  );
#endif

	 //
	 for  (  ;  !pQyMc->bQuit;  loopCtrl  ++,  Sleep(  1000  )  )  {
		 
		  //  2022/12/06
		  if (!pQyMc->bLogon) {
			 break;
		  }

		  //
		  int  loopCtrl_chkChannel  =  5;
		  loopCtrl_chkChannel  =  3;
		  if  (  !(  loopCtrl  %  loopCtrl_chkChannel  )  )  {	//  ÕâÀïÏÈÓÃÕâ¸öÆµÂÊ£¬Ó¦¸Ã¼ÓÉÏºÍserverÁªÏµ¶ÏµÄÊ±ºò£¬Ò²Òª¼´Ê±ÖØÐÂÁ¬½Ó
			  //for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  
			  for  (  i  =  0;  i  <  pProcInfo->ucCnt_misCnts;  i  ++  )  
			  {
				   MIS_CNT  *  pMisCnt			=  getMisCntByIndex(  0,  pProcInfo,  i  );//&pProcInfo->misCnts[i];
				   if  (  !pMisCnt  )  continue;
				   MIS_CHANNEL	*	pChannel	=  getChannelByType(  pMisCnt,  CONST_channelType_talking  );
				   if  (  !pChannel  )  continue;

			#if  10	//  2010/01/02
				   //if  (  !pChannel->bSessionOpen  )  
				   {
					   DWORD	dwTickCnt  =  myGetTickCount( NULL );
					   //  
					   int tmp_dynCfg_suggested_tn_changed = pMisCnt->dynCfg_suggested.tn_changed;
					   if (
						   //(  dwTickCnt  -  pChannel->status.dwTickCnt_lastStartToRecv  >  20  *  1000
						   //&&  dwTickCnt  -  pQyMc->dwTickCnt_logon  >  20  *  1000  )	//  2013/04/06. 在动态域名时,有可能需要重新获取服务器ip
						   !pChannel->bSessionOpen
						   || tmp_dynCfg_suggested_tn_changed != pMisCnt->servIp_suggested.tn_changed
						   )
					   {
						   //  È¡·þÎñÆ÷µÄIP						
						   //
						   QWM_DYN_CFG	dynCfg;
						   //
						   if (isValid_qwmDynCfg(&pMisCnt->dynCfg_suggested.dynCfg)) {
							   dynCfg = pMisCnt->dynCfg_suggested.dynCfg;
							   //
							   #ifdef  __DEBUG__
									   showInfo_open0(0, 0, _T("use dynCfg_suggest to getCnt"));
							   #endif			
						   }
						   else {
							   dynCfg = pMisCnt->cfg.dynCfg;
							   //
							   #ifdef  __DEBUG__
									   showInfo_open0(0, 0, _T("use cfg_dynCfg to getCnt"));
							   #endif			
						   }
						   //
						   QY_LOGICAL_SERVER	tmpCnt;
						   if (getCorrectCnt(&pQyMc->env, &dynCfg, bServConnected_mis, pMisCnt, pSci->cfg.iServiceId, qnmVerStr(pSci->cfg.iServiceId), &pMisCnt->commEncCtx.common, pQyMc->i64StartTime_base,  &pQyMc->cfg.to, &tmpCnt)) {
							   qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("getCorrectCnt failed"));
							   //
							   pMisCnt->dynCfg_suggested.helpInfo.bFail = true;
						   }
						   else if (inet_addr(tmpCnt.ip) != inet_addr(pMisCnt->server.ip)) {
							   //
							   TCHAR  tBuf[128];
							   _sntprintf(tBuf, mycountof(tBuf), _T("isCli: change server %S to %S"), pMisCnt->server.ip, tmpCnt.ip);
							   showInfo_open0(0, 0, tBuf);
							   //
							   pMisCnt->server = tmpCnt;

						   }
#if 0
						   else if (inet_addr(tmpCnt.ip) != pMisCnt->servIp_suggested.dwServIp) 
						   {
							   pMisCnt->servIp_suggested.dwServIp = inet_addr(tmpCnt.ip);
						   }					   
#endif
						   
							
						   //							
						   pMisCnt->dynCfg_suggested.helpInfo.bDone = true;
						   
						   //
						   pMisCnt->servIp_suggested.tn_changed = tmp_dynCfg_suggested_tn_changed;
					   }
				   }
			#endif

				   //  ÉÏÃæ²âÊÔÍêcorrectCntºó£¬²»ÄÜcontinue. ÒªÁ¢¼´ÅÐ¶ÏÏÂÃæµÄ×´Ì¬Î»¡£
				   //
				   if  (  pMisCnt->cfg.dynCfg.cnt.usCntPort  )  {

					   if  (  pProcInfo->status.threadsStatus.ulbMgrQuit  
						   ||  pProcInfo->status.threadsStatus.ulbWorkQuit
								||  pProcInfo->status.threadsStatus.ulbDisplayQuit
									||  pProcInfo->status.threadsStatus.ulbRobotQuit
										||  pProcInfo->status.threadsStatus.ulbSchedulerQuit
											||  pProcInfo->status.threadsStatus.ulbMediaQuit
											||  pProcInfo->status.threadsStatus.ulbRealTimeMediaQuit
											||  pProcInfo->status.threadsStatus.ulbRtOpQuit
                                            	||  pProcInfo->status.threadsStatus.ulbLogQuit
						   							||  pMisCnt->status.ulbSeriousErr  )  
					   {
						   #ifdef  __DEBUG__
								   traceLogA(  (char*)  "mcThreadProc_mis will quit, because sub thread has quitted."  );
						   #endif
						   goto  errLabel;
					   }

					   //
#if 0
					   if (!pChannel->hThread_io) {
						   if (pMisCnt->servIp_suggested.dwServIp) {
							   if (pMisCnt->servIp_suggested.dwServIp != inet_addr(pMisCnt->server.ip)) {
								   ulIp2Str(pMisCnt->servIp_suggested.dwServIp, pMisCnt->server.ip, mycountof(pMisCnt->server.ip));
								   //
								   showInfo_open0(0, 0, _T("set serv.ip to dwServIp_suggested"));
							   }
						   }
					   }
#endif
					   //
					   if  (  !pChannel->bSessionOpen  )  {
						   bool  canStart = true;
						   //
#if 0
						   if (pMisCnt->servIp_suggested.dwServIp) {
							   if (pMisCnt->servIp_suggested.dwServIp != inet_addr(pMisCnt->server.ip)) {
								   canStart = false;
							   }
						   }
#endif
						   //
						   if (canStart) {
							   //  ´ò¿ªÁ¬½Ó
							   startChannel(pProcInfo, pMisCnt, getChannelByType(pMisCnt, 0), 0);
						   }
					   }

					   if  (  pChannel->hThread_io  )  {	//  ÕâÀïÒª¿´Ò»ÏÂÊÇ·ñÓÐÏß³ÌÍË³öÁË£¬µ±Í¨ÐÅÖÐ¶Ï»òÆäËûÒì³£Ô­ÒòÊ±£¬Ïß³Ì»áÍË³ö
						   waitForObject(  &pChannel->hThread_io,  500  );

						   if  (  !pChannel->hThread_io  )  {
							   
							   //  
							   showInfo_open0(  0,  0,  _T(  "thread_isCli: channel talk waited"  )  );
							   
							   //
							   pMisCnt->dualSystem.bNeedXt_ifSessionOff = true;
							   
							   //
							   QM_OBJQ_MEM			mem;
							   
							   if  (  !findQMemByKey(  0,  (  QM_OBJQ  *  )pMisCnt->pObjQ,  &pMisCnt->idInfo,  &mem  )  )  {
								   //	 
								   (  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj  )->usRunningStatus  =  CONST_usRunningStatus_offline;

								   pMisCnt->status.usRunningStatus  =  CONST_usRunningStatus_offline;
							   
								   lstrcpyn(  pMisCnt->displayName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_objIdStr_me  ),  mycountof(  pMisCnt->displayName  )  );

								   //  Ë¢ÐÂÒ»ÏÂÎÒ½Úµã£¬ 2007/06/20
								   updateMeDisplayInfo(  pProcInfo,  pMisCnt,  NULL,  NULL,  NULL  );	 					   
							   }

						   }
					   }

		  		   }
			  }

		  }

		  //
		  continue;
	 }


	 iErr  =  0;

errLabel:

#ifdef  __DEBUG__
		traceLogA(  (char*)  "mcThreadProc_mis is ready to leave"  );
#endif
	 
	 //
	 for  (  ;  !pQyMc->bQuit;  )  {
		 //
		 if (!pQyMc->bLogon)  break;

		 //
 		  notifyPanicToApp(  pQyMc,  0,  NULL  );		//  2007/05/04
		  //
		  #ifdef  __DEBUG__
				  traceLogA(  (char*)  "notifyPanicToApp"  );  
		  #endif
		  //
		  Sleep(  1000  );
	 }

	 //for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  
	 for  (  i  =  0;  i  <  pProcInfo->ucCnt_misCnts;  i  ++  )  
	 {
		  MIS_CNT		*	pMisCnt		=  getMisCntByIndex(  0,  pProcInfo,  i  );//&pProcInfo->misCnts[i];
		  if  (  !pMisCnt  )  continue;
		  MIS_CHANNEL	*	pChannel	=  getChannelByType(  pMisCnt,  CONST_channelType_talking  );

		  if  (  !pMisCnt->cfg.dynCfg.cnt.usCntPort  )  continue;

		  //
		  #ifdef  __DEBUG__
				  traceLogA(  (char*)  "waitForChannel"  );
		  #endif
		  //
		  waitForChannel(  pProcInfo,  pMisCnt,  0,  TRUE  );
	  
	 }


	 MACRO_qyNullThread(  pProcInfo->hThread_rtOp  );	//  2016/12/26	 
	 MACRO_qyNullThread(  pProcInfo->hThread_realTimeMedia  );	//  2008/04/25
	 MACRO_qyNullThread(  pProcInfo->hThread_media  );			//  2008/03/15
	 MACRO_qyNullThread(  pProcInfo->hThread_scheduler  );
	 MACRO_qyNullThread(  pProcInfo->hThread_work  );
	 MACRO_qyNullThread(  pProcInfo->hThread_display  );
	 MACRO_qyNullThread(  pProcInfo->hThread_robot  );			//  2007/07/04
	 MACRO_qyNullThread(  pProcInfo->hThread_mgr  );

	 //
#ifdef  __DEBUG__
		traceLogA(  (char*)  "mcThreadProc_mis leaves"  );
#endif

	 return  iErr;
}


//
 int  updateMeDisplayInfo(  void  *  pMC_VAR_isCli,  MIS_CNT  *  pMisCnt,  QY_MESSENGER_REGINFO  *  pRegInfo,  LPCTSTR  talkerDesc,  LPCTSTR  displayName  )
{
	int								iErr	=	-1;
	MIS_MSG_REFRESHMESTATUS_QMC		msg;
	int								len;

	MC_VAR_isCli  *  pProcInfo  =  (  MC_VAR_isCli  *  )pMC_VAR_isCli;

	//
	if  (  pRegInfo  &&  pRegInfo->addr.idInfo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
		//
		MY_REG_DESC				desc;
	
		//  2010/04/16
		if  (  regInfo2Desc(  0,  pRegInfo,  &desc,  pMisCnt->talkerDesc,  mycountof(  pMisCnt->talkerDesc  ),  pMisCnt->displayName,  mycountof(  pMisCnt->displayName  )  )  )  goto  errLabel;

		//  2016/04/06
		_sntprintf(  pMisCnt->displayName_withIdInfo,  mycountof(  pMisCnt->displayName_withIdInfo  ),  _T(  "%s %I64u"  ),  pMisCnt->displayName,  pMisCnt->idInfo.ui64Id  );
		}
	else  if  (  talkerDesc  &&  displayName  )  {	
  		      lstrcpyn(  pMisCnt->talkerDesc,  talkerDesc,  mycountof(  pMisCnt->talkerDesc  )  );
			  lstrcpyn(  pMisCnt->displayName,  displayName,  mycountof(  pMisCnt->displayName  )  );
		
			  //  2016/04/06
			  safeTcsnCpy(  pMisCnt->displayName,  pMisCnt->displayName_withIdInfo,  mycountof(  pMisCnt->displayName_withIdInfo  )  );
	}

	//
	memset(  &msg,  0,  sizeof(  msg  )  );
	msg.uiType  =  CONST_misMsgType_refreshMeStatus_qmc;
	msg.pMisCnt  =  pMisCnt;
	//			 
	len  =  sizeof(  msg  );
	//
	if  (  qPostMsgAndTrigger(  &msg,  len,  &pProcInfo->displayQ,  _T(  "updateMe"  ))) {
		#ifdef  __DEBUG__
				traceLogA(  (char*)  "qPostMsgAndTrigger failed"  );  
		#endif
		goto  errLabel;
	}

	iErr  =  0;

errLabel:

	return  iErr;

}



 int  tryToStartChannel(  MIS_CNT  *  pMisCnt,  MIS_CHANNEL  *  pChannel,  TCHAR  *  respHint,  unsigned  int  respHintCnt  )
{
	 int						iErr									=	-1;
	 if  (  !pMisCnt  )  return  -1;
	 MC_VAR_isCli			*	pProcInfo								=	(  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;
	 if  (  !pProcInfo  )  return  -1;
	 QY_MC					*	pQyMc									=	(  QY_MC  *  )pProcInfo->pQyMc;
	 QY_SERVICEGUI_INFO		*	pSci									=	(  QY_SERVICEGUI_INFO  *  )pProcInfo->pSgiParam;

	 //
	 QM_dbFuncs  *  p_g_dbFuncs  =  pQyMc->p_g_dbFuncs;

	 //
	 char						buf[4096];
	 unsigned  int				len;
	 CQyMalloc					mallocObj;
	 QY_BUF						buf_help;
	 buf_help.len  =  sizeof(  buf  );
	 if  (  !(  buf_help.data  =  (  unsigned  char  *  )mallocObj.mallocf(  buf_help.len  )  )  )  return  -1;

	 char					*	ptr;
	 AUTH_RESP_MIS				authResp;
	 QY_MESSENGER_ID			idInfo;
 	 QY_MESSENGER_INFO			obj;
#ifndef  __WINCE__
	 CQnmDb						db;
#endif
	 void					*	pDb										=	NULL;				//  2010/04/08
	 TCHAR						tBuf[128];

	 //
#ifdef  __DEBUG__
	 if (1) {
		 _sntprintf(  tBuf, mycountof(tBuf),  _T("tryToStartChannel enters， %S %d"),  pChannel->curServer.ip, pChannel->curServer.port);
		 showInfo_open0(0, 0, tBuf);
	 }
#endif

	 //
	 if  (  pChannel->bSessionOpen  )  return  0;	//  

	 //
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if (!pDbFuncs)  return  -1;// goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	pChannel->status.ulbNeedVerified  =  FALSE;
	 pChannel->status.ulbAuthed  =  FALSE;
  	
	 //
	 Param_dbg  param;
	 param.m_pHint = (TCHAR*)_T("t1ryToStartChannel.3737");
	 //param.m_bShowInfo = false;


	 //
#ifdef  __DEBUG__
	 _sntprintf(tBuf, mycountof(tBuf), _T("tryToStart.3785. curServer.%S"), pChannel->curServer.ip);
	 showInfo_open0(0, 0, tBuf);
#endif

	 //
	 if (inet_addr(pMisCnt->server.ip) != inet_addr(pChannel->curServer.ip)) {
		 showInfo_open0(0, 0, _T("tryToStartChannel failed, serv!=curServ.ip"));
		 goto  errLabel;
	 }


	 //  ´ò¿ªÁ¬½Ó						   	 
	 len  =  sizeof(  buf  );
	 //if  (  qnmOpenSession_mis(  pMisCnt->server.ip,  pMisCnt->server.port,  pMisCnt->pAuthInfo,  0,  pChannel->uiType,  NULL,  pSci->cfg.iServiceId,  qnmVerStr(  pSci->cfg.iServiceId  ),  &pChannel->commEncCtx,  &pChannel->session,  &pChannel->sock,  &pQyMc->cfg.to,  buf,  &len,  &param  )  )  goto  errLabel;
	 if (qnmOpenSession_mis(pChannel->curServer.ip, pChannel->curServer.port, pMisCnt->pAuthInfo, 0, pChannel->uiType, NULL, pSci->cfg.iServiceId, qnmVerStr(pSci->cfg.iServiceId), &pChannel->commEncCtx, pQyMc->i64StartTime_base,  &pChannel->session, &pChannel->sock, &pQyMc->cfg.to, buf, &len, &param)) {
		 showInfo_open0(0, 0, _T("tryToStart.qnmOpenSession_mis failed"));
		 goto  errLabel;
	 }
	 pChannel->bSessionOpen		=		TRUE;

	 //
#ifdef  __DEBUG__
	 if (1) {
		 showInfo_open0(0, 0, _T("tryToStart.qnmOpenSession_mis ok"));
	 }
#endif


	 //
	 if (decryptData(&pChannel->commEncCtx, &buf_help, buf, &len)) {
		 showInfo_open0(0, 0, _T("tryToStartChannel.decryptData failed"));
		 goto  errLabel;
	 }

	 //
#ifdef  __DEBUG__
	 if (0) {
		 showInfo_open0(0, 0, _T("tryto.mmm"));
	 }
#endif


	 //
	 memset(  &authResp,  0,  sizeof(  authResp  )  );
	 ptr  =  buf;
	 if  (  stream2Data(  &ptr,  &len,  filterStream_is,  tmpHandler_stream2AuthResp_mis,  NULL,  &authResp  )  )  goto  errLabel;
	 if  (  !isRcOk(  pChannel->session.usLastRespCode_i  )  )  {
		 if  (  pChannel->uiType  ==  CONST_channelType_talking  )  {
			 //  2011/08/15
			 if  (  respHint  )  safeWcsnCpy(  authResp.wBuf_hint,  respHint,  respHintCnt  );	
			 //
			 if  (  pChannel->session.usLastRespCode_i  ==  CONST_qyRc_anotherLogonExists  )  {
				 TCHAR  tBuf[128];
				 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "another logon exists. %s"  ),  authResp.wBuf_hint  );
				 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_anotherLogonExists  )  );
				 if  (  pQyMc->bLogon  )  {
					 //
					 if (pProcInfo->m_iCtxSubtype != CONST_ctxSubtype_qmcSm) 
					 {
						 showNotification(pMisCnt, 0, 0, 0, 0, 0, CQyString(getResStr(0, &pQyMc->cusRes, CONST_resId_anotherLogon)) + authResp.wBuf_hint);
						 waitToQuit_isCli(pProcInfo, 5000, tBuf);
					 }
				 }
				 goto  errLabel;
			 }
		 }
		 if  (  !isRcNeedVerified(  pChannel->session.usLastRespCode_i  )  )  {
			 //
			 showInfo_open0(  0,  0,  _T(  "tryToStartChannel failed: access denied"  )  );
			 traceLogA(  (char*)  "tryToStartChannel failed: access denied"  );
			 //
			 goto  errLabel;
		 }
		 traceLogA(  (char*)  "get hint from server: [%S]",  authResp.wBuf_hint  );
		 pChannel->status.ulbNeedVerified  =  TRUE;
	 }
	 if  (  isRcOk(  pChannel->session.usLastRespCode_i  )  )  pChannel->status.ulbAuthed  =  TRUE;		   
	 
	 if  (  !pChannel->status.ulbAuthed  )  {
		 traceLogA(  (char*)  "ulbAuthed is false"  );  goto  errLabel;
	 }
	 if  (  !bMessengerIdValid(  &authResp.idInfo  )  )  goto  errLabel;

	 idInfo.ui64Id  =  authResp.idInfo.ui64Id;

	 _sntprintf(  pProcInfo->who_showInfo,  mycountof(  pProcInfo->who_showInfo  ),  _T(  "%s%I64u"  ),  pQyMc->who_showInfo,  idInfo.ui64Id  );
	 set_who_showInfo(  pProcInfo->who_showInfo  );

	 //
	 TCHAR* pName;
	 pName = qyGetDesByType1(CONST_channelTypeTable, pChannel->uiType);
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s: tryToStartChannel, get idInfo %I64u, pMisCnt->idInfo is %I64u"  ),  pName,  idInfo.ui64Id,  pMisCnt->idInfo.ui64Id  );
	 showInfo_open0(0, 0, tBuf);
#ifdef  __DEBUG__
	 traceLog(tBuf);
#endif

	 //
	 if  (  pChannel->uiType  !=  CONST_channelType_talking  )  {	//  2008/03/17, 
		 iErr  =  0;  goto  errLabel;
	 }

	 //
	 //if  (  memcmp(  &pMisCnt->idInfo,  &idInfo,  sizeof(  pMisCnt->idInfo  )  )  )  memcpy(  &pMisCnt->idInfo,  &idInfo,  sizeof(  pMisCnt->idInfo  )  );		 
	 if (pMisCnt->idInfo.ui64Id != idInfo.ui64Id)  pMisCnt->idInfo = idInfo;


	 //  2011/02/02
	 if  (  authResp.uiLogonId  )  {
		 //
		 int  iii;
		 for (iii = 0; iii < 5; iii++) {
			 //
			 if (!pProcInfo->authInfo.uiLogonId) {
				 //
				 CQyMalloc					mallocObj;
				 IM_L_STREAM* pStream = NULL;

				 if (!(pStream = (IM_L_STREAM*)mallocObj.mallocf(sizeof(IM_L_STREAM)))) {
#ifdef  __DEBUG__
					 traceLogA((char*)"tryToStartChannel . malloc failed.");
#endif
					 goto  errLabel;
				 }

#if  10
				 //
				 showInfo_open0(0, 0, _T("tryToStartChannel: start to chkLogonId"));

				 //
				 ChkLogonIdReq	req;
				 memset(&req, 0, sizeof(req));
				 req.uiType = CONST_imCommType_chkLogonIdReq;
				 req.uiLogonId = authResp.uiLogonId;
				 //
				 MACRO_memset_imLStream(pStream);
				 pStream->uiType = CONST_imCommType_lStream;
				 pStream->uiContentType = req.uiType;
				 len = sizeof(pStream->buf);
				 if (chkLogonIdReq2Stream(pStream->uiContentType, &req, pStream->buf, (unsigned  int*)&len))  goto  errLabel;

				 pStream->ulStreamLen = len;
				 len += offsetof(IM_L_STREAM, buf);

				 len = qyhtonImLStream(0, pStream);
				 if (len > sizeof(buf))  goto  errLabel;
				 memcpy(buf, pStream, len);

				 //
				 if (encryptData(&pChannel->commEncCtx, &buf_help, buf, &len, sizeof(buf))) {
					 goto  errLabel;
				 }
				 MACRO_prepareForTran();
				 unsigned  char  ucFlg = 0;
				 if (qySendMsg(&pChannel->session, &pChannel->sock, &pQyMc->cfg.to, ucFlg, CONST_qyCmd_chkLogonId, tStartTran, uiTranNo, 0, buf, len)) {
					 goto  errLabel;
				 }
				 //
				 QY_MSG_HEAD_h  tmpResp;
				 if (qyRecvMsg(&pChannel->session, &pChannel->sock, &pQyMc->cfg.to, &tmpResp, buf, sizeof(buf))) {
					 goto  errLabel;
				 }
				 //
				 len = tmpResp.uiLen;
				 if (decryptData(&pChannel->commEncCtx, &buf_help, buf, &len)) {
					 goto  errLabel;
				 }
				 //
				 {
					 IM_L_STREAM_nh				stream_ntoh;
					 IM_L_STREAM_nh* pStream = &stream_ntoh;

					 //  pStream  =  (  IM_L_STREAM  *  )ptr;
					 char* ptr = buf;
					 int lenInBytes = 0;

					 //if ((lenInBytes = qyntohImLStream(0, ptr, pStream)) < 0)  goto  errLabel;

					 //
					 ChkLogonIdReq resp;
					 if (qyntohRouteTalkData(0, ptr, len, nullptr, (IM_CONTENTU*)&resp, (TCHAR*)_T(""), 0)) {
						 //goto  errLabel;
						 //  收到了错误的数据包，重新来一次
						 showInfo_open0(0, 0, _T("tryToStartChannel: wrong msg, try to chkLogonId again"));
						 continue;
					 }

					 //
					 if (resp.uiLogonId != authResp.uiLogonId) {
						 showInfo_open0(0, 0, _T("tryToStartChannel failed, resp.uiLogonId != authResp.uiLogonId"));
						 goto  errLabel;
					 }

					 //
					 showInfo_open0(0, 0, _T("tryToStartChannel: chkLogonId ok"));
				 }
#endif

				 int  ii = 0;
			 }
			 //
			 if (pProcInfo->authInfo.uiLogonId != authResp.uiLogonId) {
#ifdef  __DEBUG__
				 traceLog((TCHAR*)_T("tryToStartChannel: get uiLogonId %d"), authResp.uiLogonId);
#endif
				 pProcInfo->authInfo.uiLogonId = authResp.uiLogonId;
			 }
			 //
			 break;
		 }
	 }
	 //
#if  0
	 if  (  authResp.usAppAvLevel_daemon  )  {
		 if  (  pQyMc->usAppAvLevel_daemon  !=  authResp.usAppAvLevel_daemon  )  {
			 pQyMc->usAppAvLevel_daemon  =  authResp.usAppAvLevel_daemon;	//  2011/10/22
			 #ifdef  __DEBUG__
					 traceLog((TCHAR*)  _T(  "tryToStartChannel: usAppAvLevel_daemon is set"  )  );
			 #endif
		 }		 
	 }
#endif
	 //
	 getLocalIpBySocket(pChannel->sock.sockFd, pProcInfo->authInfo.ip);

	 //  2009/10/11
	 if  (  pQyMc->ucbDaemonDemo  !=  authResp.ucbDaemonDemo  )  {
		 pQyMc->ucbDaemonDemo  =  authResp.ucbDaemonDemo;
	 }		
	 //		
	 QM_SHM_CMDS* pShmCmds;pShmCmds = (QM_SHM_CMDS*)pProcInfo->cmdsShm.pBuf;		//  2010/09/14		
	 if  (  pShmCmds  )  {
		 if  (  pShmCmds->ucbDaemonDemo  !=  pQyMc->ucbDaemonDemo  )  {
			 pShmCmds->ucbDaemonDemo  =  pQyMc->ucbDaemonDemo;
		 }
	 }
	 //  2017/06/21
	 if  (  pQyMc->usSubSystemId_daemon  !=  authResp.usSubSystemId_daemon  )  {
		 pQyMc->usSubSystemId_daemon  =  authResp.usSubSystemId_daemon;
	 }

	 //  2016/08/10
	 if  (  pChannel->uiType  ==  CONST_channelType_talking  )  {
		 safeTcsnCpy(  authResp.clientWelcomeMsg,  pProcInfo->cfg.clientWelcomeMsg,  mycountof(  pProcInfo->cfg.clientWelcomeMsg  )  );

		 //
		 switch (pMisCnt->pAuthInfo->usAuthType) {
				case  CONST_authType_bjca:
				case  CONST_authType_jdzy:
					  tTrim(authResp.ca_usrName);
					  if (!authResp.ca_usrName[0]) {
						  showInfo_open0(0, 0, _T("tryToStartChannel failed, ca, authResp.ca_usrName is nothing"));
						  goto  errLabel;
					  }
					  safeTcsnCpy(authResp.ca_usrName, pMisCnt->pAuthInfo->ca_usrName, mycountof(pMisCnt->pAuthInfo->ca_usrName));
					  safeStrnCpy(authResp.ca_tmp_passwd, pMisCnt->pAuthInfo->ca_tmp_passwd, mycountof(pMisCnt->pAuthInfo->ca_tmp_passwd));
					  //
					  break;
				default:
					break;
		 }

		 //
	 }


	 //
	 if  (  !pQyMc->bLogon  )  {		//  2010/03/10
		 iErr  =  0;  goto  errLabel;
	 }

	 //
#ifdef  __DEBUG__
	 if (0) {
		 showInfo_open0(0, 0, _T("tryToStartChannel here"));
		}
#endif

	 //
#ifndef  __NOTSUPPORT_DB__
	 if  (  !bObjDbAvail(  getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  )  )  )  goto  errLabel;
	 if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
	 pDb  =  db.m_pDbMem->pDb;

	 if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pQyMc->p_g_dbFuncs,  pDb,  pSci->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  pMisCnt->cfg.misServName,  &idInfo,  0,  &obj,  NULL,  NULL,  NULL  )  )  {
		 memset(  &obj,  0,  sizeof(  obj  )  );

		 lstrcpyn(  obj.misServName,  pMisCnt->cfg.misServName,  mycountof(  obj.misServName  )  );
		 obj.uiType  =  CONST_objType_me;
		 obj.idInfo.ui64Id  =  idInfo.ui64Id;

		 if  (  pProcInfo->recoverMessenger(  pDbFuncs,  pDb,  pSci->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  &obj,  NULL,  0,  FALSE,  &pProcInfo->schedulerQ  )  )  {
			 //  2013/01/29
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "recoverMessenger failed"  )  );
			 goto  errLabel;
		 }
		
	 }


	 if  (  g_dbFuncs.pf_updateImObj_me(  pDb,  pSci->cfg.iDbType,  &obj  )  )  goto  errLabel;

#else
	 //  update info into storage	//  2010/04/08
#endif

	 if  (  pQyMc->usMaxVideoConferenceMems  !=  authResp.usMaxVideoConferenceMems  )  pQyMc->usMaxVideoConferenceMems  =  authResp.usMaxVideoConferenceMems;
	 //
	 if  (  pQyMc->ucDays_left  !=  authResp.ucDays_left  )  pQyMc->ucDays_left  =  authResp.ucDays_left;	//  2010/03/22
	 //
	 unsigned  int  uiMaxTimeInS_videoConference; uiMaxTimeInS_videoConference = bQmFreeVer(pQyMc) ? pQyMc->uiMaxTimeInS_videoConference_freeVer : pQyMc->uiMaxTimeInS_videoConference_general;
	 if  (  pQyMc->uiMaxTimeInS_videoConference  !=  uiMaxTimeInS_videoConference  )  pQyMc->uiMaxTimeInS_videoConference  =  uiMaxTimeInS_videoConference;
	 //

	 //	 
	 QM_OBJQ_MEM	mem;

	 memset(  &obj,  0,  sizeof(  obj  )  );

	 lstrcpyn(  obj.misServName,  pMisCnt->cfg.misServName,  mycountof(  obj.misServName  )  );
	 obj.uiType  =  CONST_objType_me;
	 obj.idInfo.ui64Id  =  idInfo.ui64Id;

	 //  ÕâÀï·Åµ½¹ÜÀí¶ÓÁÐÖÐÈ¥
	 if  (  procQmObjQ(  pSci,  (  QM_OBJQ  *  )pMisCnt->pObjQ,  pDb,  pQyMc->cfg.db.iDbType,  obj.uiType,  &obj,  &mem  )  )  goto  errLabel;
	 
	 QMEM_MESSENGER_CLI  *  pQMem;
	 pQMem  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;

	 //  (  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj  )->usRunningStatus  =  CONST_usRunningStatus_online;
	 pQMem->usRunningStatus  =  CONST_usRunningStatus_online;

	 pMisCnt->status.usRunningStatus  =  CONST_usRunningStatus_online;	//  2007/08/31

	 int  i;	//  2009/10/11
	 for  (  i  =  0;  i  <  mycountof(  pMisCnt->channels  );  i  ++  )  {
		 memset(  &pMisCnt->channels[i].status.netStat,  0,  sizeof(  pMisCnt->channels[i].status.netStat  )  );
	 }

	 //  ÏÂÃæ£¬ÒªÆô¶¯Ò»Ð©²ßÂÔ£¬´¥·¢ÔÚÁ¬½ÓÉÏ·þÎñÆ÷ºó£¬ÐèÒª×öµÄÒ»Ð©¶¯×÷
	 //
	 QY_MESSENGER_REGINFO	regInfo;
	 //	 
	 if  (  bMeInfoNeedReg(  pDb,  pQyMc->cfg.db.iDbType,  pMisCnt,  &regInfo  )  )  pMisCnt->ucTriesToReg  +=  2;
	 //
	 pMisCnt->ucbNeedSndDevInfo  =  TRUE;		//  2007/08/03
	 //
	 pMisCnt->bIntervalParamsGot  =  FALSE;		//  2007/09/20,  ÕâÀï£¬Í¨¹ý½«¿ØÖÆ±äÁ¿Çå0¿ÉÒÔÈÃÍ¨µÀÁ¬Í¨Ö®ºó£¬ÖØÐÂÏÂÔØÒ»ÏÂÉèÖÃ¡£
	 pMisCnt->bToPathsRetrieved  =  FALSE;		//  2008/02/09


#ifndef  __NOTSUPPORT_DB__
	 if  (  !pQMem->talkerDesc[0]  )  {
		 if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pQyMc->p_g_dbFuncs,  pDb,  pSci->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  pMisCnt->cfg.misServName,  &pMisCnt->idInfo,  0,  NULL,  &regInfo,  NULL,  NULL  )  )  goto  errLabel;
		 if  (  !regInfo.addr.idInfo.ui64Id  )  {
			 regInfo.addr.idInfo.ui64Id  =  idInfo.ui64Id;
		 }

		 MY_REG_DESC				desc;
		 if  (  regInfo2Desc(  0,  &regInfo,  &desc,  pQMem->talkerDesc,  mycountof(  pQMem->talkerDesc  ),  pQMem->displayName,  mycountof(  pQMem->displayName  )  )  )  goto  errLabel;
	 }
#endif
	 safeWcsnCpy(  authResp.talkerDesc,  pQMem->talkerDesc,  mycountof(  pQMem->talkerDesc  )  );

	 if  (  updateMeDisplayInfo(  pProcInfo,  pMisCnt,  NULL,  pQMem->talkerDesc,  pQMem->displayName  )  )  goto  errLabel;	 

#ifdef  __DEBUG__
		traceLogA(  (char*)  "channel start, idInfo %I64u",  pMisCnt->idInfo.ui64Id  );

		test_myDb(  _T(  "tryToStartChannel"  )  );
#endif

	 iErr  =  0;
 errLabel:

	 if  (  iErr  )  {		 
		 if  (  pChannel->bSessionOpen  )  {
			 qnmCloseSession_msg(  mynull, &pChannel->session,  &pChannel->sock,  &pQyMc->cfg.to,  _T("tryToStartChannel.l4253"));
			 pChannel->bSessionOpen  =  FALSE;
		 }

		 //
#ifdef  __DEBUG__
		 showInfo_open0(0, 0, _T("tryToStartChannel failed"));
#endif
	 }

	 //


	 //
	 return  iErr;
}











