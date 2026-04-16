

//
#include	"stdafx.h"

#include	<windowsx.h>
#include	<math.h>
#include	<time.h>
#include	<stddef.h>
#include	<ShellAPI.h>
#include	<tchar.h>

#include	"qymcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"

#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture_isCli.h"


#include	"tmpCeLib.h"
#include	"qyWnd.h"

#include	"qyRtcCommProc.h"
#ifndef  __WINCE__
#include	"dlgVideosProc.h"
#endif
#include	<assert.h>
#include	"qmcDxSurfacePublic.h"
#ifndef  __WINCE__
#include	"qmcConferenceWall.h"
#include	"isCliHelpPublic.h"
#endif
#include	"qmcCmdProc.h"

#include	"policyAvParams.h"

#include	"dlgTalkProc.h"
#include	"qmcSharePublic.h"

#include	"DlgWalls.h"

#include	"gpsCommProc.h"
#include	"qmcGpsProc.h"

#include	"qyCusResTemp.h"

#include	"qmcVWall.h"
#include	"dlgDesktopsMonProc.h"

#include	"sp.h"
#include	"myDb.h"
#include	"isCliHelpPublic.h"

#include	"imgProcessPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"dlgMsgToolProc.h"
#include	"qmcVideoCapture_rtsp.h"
#include	"qmcDynBmp.h"

#include	"qyCusResTemp.h"
#include	"dlgShareDynBmpsProc.h"
#include	"isCliD3dPublic.h"
#include	"policyIsClientFunc.h"

#include	"qmcCommFunc_isCli.h"
#include	"isCliExPublic.h"
#include	"isCliCorePublic.h"
#include	"dyn_isCliD3d_public.h"
#include	"myTChar.h"
#include	"hgCommProc.h"

#ifdef  __TEST_ONLY__
		#include	"testOnly.h"
#endif

//
//
 BOOL  bPermitted_taskAv(  QY_MC  *  pQyMc,  QY_MESSENGER_ID  *  pIdInfo_grp,  TCHAR  *  hint,  unsigned  int  cnt  )
 {	 
	 BOOL  bRet  =  FALSE;
	 //QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	 	
	
		bRet  =  TRUE;
errLabel:
	
		return  bRet;
	
 }


 //
 BOOL  bPermitted_2d_taskAv(  QY_MC  *  pQyMc,  QY_MESSENGER_ID  *  pIdInfo_grp,  TCHAR  *  hint,  unsigned  int  cnt  )
 {	 
	 BOOL  bRet  =  FALSE;
	 //QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	 	
	
	 void  *  pDb  =  NULL;
	 #ifndef  __NOTSUPPORT_DB__
				 CQnmDb				db;
				 if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
				 pDb  =  db.m_pDbMem->pDb;
	 #endif

	 //
#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "for test, bPermitted_2d_taskAv returns true"  )  );
		return  true;
#endif

	 //  2018/10/23
	 if  (  pQyMc->iCustomId  ==  CONST_qyCustomId_hzj
		 ||  pQyMc->iCustomId  ==  CONST_qyCustomId_hbwj  )  
	 {
		 bRet  =  TRUE;  goto  errLabel;
	 }
				 		
	 //	
	 int  n; n = getnGrpMems_isCli(pDb, pQyMc->cfg.db.iDbType, pIdInfo_grp);
	 if  (  n  <=  0  )  {
			goto  errLabel;
	 }


		//
#ifdef  __DEBUG__
		//  traceLogA(  "cnt %d",  pListCtrl->GetItemCount(  )  );		
		traceLogA(  (char*)"cnt %d",  n  );
#endif

		//
		if  (  pQyMc->iCustomId  !=  CONST_qyCustomId_bjyz  )  goto  errLabel;
		//
		if  (  n  >  3  )
		{
				if  (  hint  &&  cnt  )  {
					_sntprintf(  hint,  cnt,  _T(  "%s %d"  ),  _T(  "too many conferenceMems in 2d conf"  ),  3  );
				}
				goto  errLabel;
		}
	
		bRet  =  TRUE;

errLabel:
	
		return  bRet;
	
 }

 //
 



  //
    //
  int  resetGrpConfCtrl(  HWND  hDlgTalk_mgr,  GRP_confCtrl  *  p  )
 {
	 for  (  int  i  =  0;  i  <  p->usCnt;  i  ++  )  {
		  GrpMem_confCtrl  *  pMem  =  &p->pMems[i];
		  memset(  &pMem->m_var,  0,  sizeof(  pMem->m_var  )  );
	 }

	 return  0;
  }
   



//  2014/04/08
  int  confCli_doCmd_startAvCall(HWND  hParent, HWND  hCurTalk, int  level, BOOL  b3D, unsigned  char  ucbAvConsole, PARAM_startAvCall* pParam)
  {
	  int								iErr = -1;

	  HWND							hMgr = NULL;
	  DLG_TALK_var* pMgrVar = NULL;

	  DLG_TALK_var* pCurVar = NULL;

	  CHelp_getDlgTalkVar				help_getDlgTalkVar_cur;
	  CHelp_getDlgTalkVar				help_getDlgTalkVar_mgr;


	  //
	  VIDEO_CONFERENCE_CFG			videoConferenceCfg;
	  BOOL							bVideoConference = FALSE;
	  int								iIndex_sharedObj = -1;
	  int								iIndex_sharedObjUsr = -1;
	  //  
	  QY_SHARED_OBJ* pSharedObj = NULL;

	  //
	  BOOL							bTaskStarted = FALSE;			//  2014/10/31

	  BOOL							bFirstUsr = FALSE;
	  int								iTaskId = 0;				//  2014/10/29

	  CQySyncObj						syncObj;
	  CQySyncObj						syncObj_sync_taskInfo;						//  2016/03/15

	  //
	  TCHAR				tBuf[256] = _T("");

	  //
	  if (0) {
		  showInfo_open0(0, 0, _T("for test: set level to 4k"));
		  level = CONST_policyAvLevel_2160p;
	  }



	  //
	  PARAM_startAvCall  param = { 0 };
	  if (pParam) {
		  param = *pParam;
	  }

	  //
	  pCurVar = (DLG_TALK_var*)help_getDlgTalkVar_cur.getVar(hCurTalk);
	  if (!pCurVar)  return  -1;


	  //  
	  QY_MC* pQyMc = pCurVar->pQyMc;// QY_GET_GBUF();
	  MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	  if (!pProcInfo)  return  -1;
	  FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
	  if (!pFuncs)  return  -1;
	  PolicyAvParams& gAvParams = *pProcInfo->p_gAvParams;	//  QY_GET_PolicyAvParams(  );


	  //
	  if (!isTalkerShadowMgr(pCurVar->addr)) {
		  TALKER_shadow* pTalkerShadow = (TALKER_shadow*)pCurVar->pShadowInfo;
		  if (!pTalkerShadow)  goto  errLabel;
		  if (!IsWindow(pTalkerShadow->hMgr))  goto  errLabel;
		  hMgr = pTalkerShadow->hMgr;		//  2013/02/15
		  pMgrVar = (DLG_TALK_var*)help_getDlgTalkVar_mgr.getVar(pTalkerShadow->hMgr);
		  if (!pMgrVar)  goto  errLabel;
	  }
	  else {
		  //
		  hMgr = hCurTalk;
		  pMgrVar = pCurVar;
	  }
	  TALKER_shadow_mgr* pShadowMgr; pShadowMgr = (TALKER_shadow_mgr*)pMgrVar->pShadowInfo;
	  if (!pShadowMgr)  goto  errLabel;

	  //
#ifdef  __DEBUG__
#endif

//  2009/10/11	
	  TCHAR  tHint[128]; tHint[0] = 0;// = _T("");
	  if (pMgrVar->addr.uiObjType == CONST_objType_imGrp
		  || pMgrVar->addr.uiObjType == CONST_objType_tmpMsgr)
	  {

		  //
		  if (!pQyMc->appParams.canStartConf) {
			  //
			  unsigned  short  usConfType = 0;

			  //
			  BOOL  bNoPrompt = bNoPrompt_selectAvCompressor(CONST_capType_av, 0);
			  if (pQyMc->appParams.bNoPrompt_mfc) {
				  bNoPrompt = TRUE;
			  }
			  if (pParam->bNoPrompt) {
				  bNoPrompt = true;
			  }

			  //
			  b3D = true;

			  //
			  if (!bNoPrompt) {
				  if (pProcInfo->viewDlgSelectAvCompressor(hParent, pMgrVar->addr.idInfo, CONST_capType_av, 0, FALSE, b3D, usConfType) != IDOK)  goto  errLabel;
			  }

			  unsigned  int  uiCapType = CONST_capType_av;
			  unsigned  int  uiSubCapType = 0;
			  int  iCapUsage = CONST_capUsage_3dConf;
			  //
			  int  iResId = gAvParams.iResId_policyAvLevelTable;


			  //
			  if (!level)  level = getPolicyAvLevel(pQyMc, uiCapType, uiSubCapType, iCapUsage);

			  //if  (  !qyGetDesByType(  getResTable(  0,  &pQyMc->cusRes,  iResId  ),  level  )  )    level  =  getDefaultPolicyAvLevel(  pQyMc,  uiCapType,  uiSubCapType,  iCapUsage  );

			  //
			  int conf_fps = get_conf_fps();
			  bool b100k = get_conf_b100k();
			  int  conf_iFourcc = get_conf_iFourcc();
			  ushort  usMaxSpeakers = get_conf_usMaxSpeakers();
			  bool  bLyra = get_conf_bLyra();
			  //
			  int bitrateInKbps_dl = 0;
			  int  bitrateInKbps_ul = 0;
			  get_conf_bitrateInKbps(&bitrateInKbps_dl, &bitrateInKbps_ul);
			  //
			  TALKER_policy tp;
			  memset(&tp, 0, sizeof(tp));
			  getTalkerPolicy(&pMgrVar->addr.idInfo, &tp);
			  tp.conf_iFourcc = conf_iFourcc;
			  //
			  tp.conf_bitrateInKbps_dl = bitrateInKbps_dl;
			  tp.conf_bitrateInKbps_ul = bitrateInKbps_ul;

			  //
			  tp.conf_usFps = conf_fps;
			  tp.conf_ucb100k = b100k;
			  //
			  if (bLyra) {
				  tp.conf_ucAudioCompressors = CONST_audioCompressors_lyra;
			  }
			  

			  //
			  tp.uiTaskType = pParam->talkerPolicy.uiTaskType;
			  tp.shareDevice_grp_index = pParam->talkerPolicy.shareDevice_grp_index;
			  tp.gpu_usIndex = pParam->talkerPolicy.gpu_usIndex;

			  //
			  tp.usConfType = pParam->talkerPolicy.usConfType;

			  //
			  CONF_hg_info  hgInfo;
			  memset(&hgInfo, 0, sizeof(hgInfo));

			  //
#ifdef  __DEBUG__
			  hgInfo.zcrs.mems[0].idInfo.ui64Id = 103;
			  hgInfo.zcrs.mems[1].idInfo.ui64Id = 104;
			  hgInfo.zcrs.mems[2].idInfo.ui64Id = 105;
#endif 


			  //
			  //sendConfReq(  0,  hMgr,  pMgrVar->addr.idInfo,  0,  level,  conf_iFourcc,  usMaxSpeakers  );
			  sendConfReq(0, hMgr, pMgrVar->addr.idInfo, 0, level, usMaxSpeakers, &tp, &hgInfo);

			  //
			  return  0;
		  }

		  //
		  if (!bPermitted_taskAv(pQyMc, &pMgrVar->addr.idInfo, tHint, mycountof(tHint))) {
			  //qyShowHint(  tHint  );
			  showNotification(0, 0, 0, 0, 0, 0, tHint);
			  showInfo_open0(0, 0, tHint);
			  goto  errLabel;
		  }

		  //  2015/08/07
		  if (!b3D) {
			  unsigned  char  ucb2DConfPermitted = FALSE;
			  //
			  if (bPermitted_2d_taskAv(pQyMc, &pMgrVar->addr.idInfo, tHint, mycountof(tHint))) {
				  ucb2DConfPermitted = TRUE;
			  }
			  //
#ifdef  __DEBUG__
#if  0
			  traceLog((TCHAR*)_T("TEST: ucb2DConfPermitted is set to true"));
			  ucb2DConfPermitted = TRUE;
#endif
#endif
			  //
			  if (!ucb2DConfPermitted) {
				  _sntprintf(tHint, mycountof(tHint), getResStr(0, &pQyMc->cusRes, CONST_resId_notUse2DConference));
				  showNotification(0, 0, 0, 0, 0, 0, tHint);
				  //
				  if (!bUseD3DFullScreen()) {
					  myMessageBox(hParent, tHint, _T("www.qycx.com"), MB_OK);
				  }
				  //
				  goto  errLabel;
			  }
		  }

	  }

	  //  2015/07/29
	  if (pMgrVar->addr.uiObjType == CONST_objType_imGrp) {
		  //
		  TALKER_shadow_mgr* pShadowMgr = (TALKER_shadow_mgr*)pMgrVar->pShadowInfo;
		  if (!pShadowMgr)  goto  errLabel;

		  if (pShadowMgr->av.confMgrInfo.usCnt) {
			  if (!pShadowMgr->av.ucbMeConfMgr) {
				  _sntprintf(tHint, mycountof(tHint), getResStr(0, &pQyMc->cusRes, CONST_resId_notConferenceManager));
				  showNotification(0, 0, 0, 0, 0, 0, tHint);
				  //
				  if (!bUseD3DFullScreen()) {
					  myMessageBox(hParent, tHint, _T("www.qycx.com"), MB_OK);
				  }
				  //
				  goto  errLabel;
			  }
		  }
	  }

	  //
	  MIS_CNT* pMisCnt; pMisCnt = pMgrVar->pMisCnt;
	  if (!pMisCnt)  goto  errLabel;
	  //
	  unsigned  char  ucbNotUseAvCall; ucbNotUseAvCall = FALSE;

	  //
	  if (ucbNotUseAvCall) {
		  _sntprintf(tHint, mycountof(tHint), getResStr(0, &pQyMc->cusRes, CONST_resId_notUseP2pCall));
		  showNotification(0, 0, 0, 0, 0, 0, tHint);
		  //
		  if (!bUseD3DFullScreen()) {
			  myMessageBox(hParent, tHint, _T("www.qycx.com"), MB_OK);
		  }
		  //
		  goto  errLabel;
	  }



	  //
	  if (pMgrVar->av.taskInfo.bTaskExists) {
		  showInfo_open0(0, 0, _T("doCmd_startAvCall failed, av.bTaskExists is true"));
		  goto  errLabel;
	  }

	  //  2017/08/25
	  unsigned  short  usConfType; usConfType = 0;

	  //
	  if (param.talkerPolicy.usConfType) {
		  usConfType = param.talkerPolicy.usConfType;
	  }


	  //
	  BOOL  bNoPrompt; bNoPrompt = bNoPrompt_selectAvCompressor(CONST_capType_av, 0);
	  if (pQyMc->appParams.bNoPrompt_mfc) {
		  bNoPrompt = TRUE;
	  }

	  //
	  if (!bNoPrompt) {
		  if (pProcInfo->viewDlgSelectAvCompressor(hParent, pMgrVar->addr.idInfo, CONST_capType_av, 0, FALSE, b3D, usConfType) != IDOK)  goto  errLabel;
	  }

	  //
	  if (syncObj.sync(pProcInfo->cfg.mutexName_syncStartAv))  goto  errLabel;

	  //  2014/12/24
	  if (pMgrVar->av.taskInfo.bTaskExists) {
		  showNotification_open(0, 0, 0, _T("av is started already"));
		  goto  errLabel;
	  }
	  //
	  if (syncMtCnt_wLock_wait(&pMgrVar->av.syncMtCnt_taskInfo, NULL, &syncObj_sync_taskInfo, NULL, _T("doCmd_startAvCall"))) {
		  goto  errLabel;
	  }
	  //  2014/10/31
	  assert(!pMgrVar->av.taskInfo.bTaskExists);
	  //
	  //memset(  &pMgrVar->av.taskInfo,  0,  sizeof(  pMgrVar->av.taskInfo  )  );
	  dlgTalk_taskInfo_memset0(hMgr);
	  //
	  pMgrVar->av.taskInfo.bTaskExists = TRUE;
	  pMgrVar->av.taskInfo.iIndex_taskInfo = -1;
	  //
	  bTaskStarted = TRUE;


	  //  2014/10/29
	  {
		  void* pDb = NULL;
#ifndef  __NOTSUPPORT_DB__
		  CQnmDb		db;
		  if (!db.getAvailableDb(pQyMc->iDsnIndex_mainSys))  goto  errLabel;
		  pDb = db.m_pDbMem->pDb;
#endif

		  iTaskId = newTaskId(pDb, pQyMc->cfg.db.iDbType);
	  }


	  //  2016/03/06
	  exitTalkerThread(pProcInfo, &pMgrVar->talkerThreadInfo);
	  if (initTalkerThread(pProcInfo, hMgr, pMgrVar, &pMgrVar->talkerThreadInfo)) {
		  goto  errLabel;
	  }

	  //
	  if (getNewSharedObjUsr_localAv(pProcInfo, hMgr, &iIndex_sharedObj, &iIndex_sharedObjUsr, &bFirstUsr)) {
		  //  2017/02/12
		  _sntprintf(tHint, mycountof(tHint), getResStr(0, &pQyMc->cusRes, CONST_resId_notStartAv));
		  showNotification(0, 0, 0, 0, 0, 0, tHint);
		  //
		  if (!bUseD3DFullScreen()) {
			  showInfo_open0(0, 0, tHint);
		  }
		  //
		  goto  errLabel;			//  ÕâÀï¹Ì¶¨ÓÃ0
	  }
	  //
	  pSharedObj = getSharedObjByIndex(pProcInfo, iIndex_sharedObj);
	  if (!pSharedObj) {
		  showInfo_open0(0, 0, _T("startAvCall failed: getSharedObj return  NULL"));
		  goto  errLabel;
	  }
	  //
	  SHARED_OBJ_USR* pSharedObjUsr; pSharedObjUsr = getSharedObjUsr(pSharedObj, iIndex_sharedObjUsr);
	  if (!pSharedObjUsr) {
		  goto  errLabel;
	  }
	  //
	  pMgrVar->av.ucbGot_iIndex_sharedObj_localAv = TRUE;
	  pMgrVar->av.iIndex_sharedObj_localAv = iIndex_sharedObj;
	  pMgrVar->av.iIndex_usr_localAv = iIndex_sharedObjUsr;

	  //  2026/02/08
	  setCurSharedObjUsr_localAv(pProcInfo, iIndex_sharedObj, iIndex_sharedObjUsr);

	  //  2011/08/07
	  AV_COMPRESSOR_CFG	avCompressor_req;
	  if (myGetAvCompressorCfg(CONST_capType_av, 0, 0, level, &avCompressor_req))  goto  errLabel;

	  AV_COMPRESSOR_CFG	avCompressor_conf;	//  2014/08/15
	  //  2014/12/15
	  int  iCapUsage; iCapUsage = b3D ? CONST_capUsage_3dConf : CONST_capUsage_conf;
	  //
	  if (myGetAvCompressorCfg(CONST_capType_av, 0, iCapUsage, level, &avCompressor_conf))  goto  errLabel;

	  //
	  if (param.talkerPolicy.conf_ucAudioCompressors) {
		  avCompressor_req.audio.common.ucCompressors = param.talkerPolicy.conf_ucAudioCompressors;
		  avCompressor_conf.audio.common.ucCompressors = param.talkerPolicy.conf_ucAudioCompressors;
	  }
	  //
	  if (param.talkerPolicy.conf_iFourcc) {
		  //
		  set_conf_iFourcc(param.talkerPolicy.conf_iFourcc, param.talkerPolicy.conf_bitrateInKbps_dl, &avCompressor_req);
		  set_conf_iFourcc(param.talkerPolicy.conf_iFourcc, param.talkerPolicy.conf_bitrateInKbps_dl, &avCompressor_conf);

		  //
	  }
	  else {
		  int  conf_iFourcc = get_conf_iFourcc();
		  int  conf_bitrateInKbps_dl = 0;
		  int  conf_bitrateInKbps_ul = 0;
		  get_conf_bitrateInKbps(&conf_bitrateInKbps_dl, &conf_bitrateInKbps_ul);
		  //
		  set_conf_iFourcc(conf_iFourcc, conf_bitrateInKbps_dl, &avCompressor_req);
		  set_conf_iFourcc(conf_iFourcc, conf_bitrateInKbps_dl, &avCompressor_conf);
	  }

	  //
	  if (!pQyMc->appParams.bConfServer) {  //  点对点的情况，如果设置限流，就设置策略
		  //
		  bool b100k = get_conf_b100k();		
		   //
		  if (b100k) {
			  avCompressor_req.audio.common.ucCompressors = CONST_audioCompressors_lyra;

			  //
			  avCompressor_req.video.common.iAvgBitrate = 40 * 1000;

			  //
			  traceLog((TCHAR*)_T("doCmd_startAvCall: for 100k, set ucCompressors to lyra"));

		  }
		  //		  
		  if  (  !avCompressor_req.video.common.iAvgBitrate )  {
			  avCompressor_req.video.common.iAvgBitrate = myGetBitrate(&avCompressor_req.video.common, avCompressor_req.video.common.iWidth_pic, avCompressor_req.video.common.iHeight_pic);

		  }
		  //
		  bool bLyra = get_conf_bLyra();
		  //
		  if (bLyra) {
			  //
			  avCompressor_req.audio.common.ucCompressors = CONST_audioCompressors_lyra;
			  //
			  traceLog((TCHAR*)_T("doCmd_startAvCall: for bLyra, set ucCompressors to lyra"));
		  }

		  //
#ifdef  __DEBUG__
		  //
		  if (0) {
			  //avCompressor_req.video.common.iWidth_pic = 256;
			  //avCompressor_req.video.common.iHeight_pic = 144;
			  //
			  //avCompressor_req.video.common.iAvgBitrate = 50000;
			  //

		  }
#endif 
	  }

	  //
	  if (param.talkerPolicy.conf_usFps) {
		  //
		  switch (param.talkerPolicy.conf_usFps) {
		  case  1:
		  case  2:
			  //
				  case  5:
			      case  10:
				  case  15:
				  case  30:
				  case  60:
						  break;				
				  default:			  
					      param.talkerPolicy.conf_usFps = 30;			  
						  break;
		  }
		  //
		  avCompressor_req.video.common.usMaxFps_toShareBmp = param.talkerPolicy.conf_usFps;
		  avCompressor_conf.video.common.usMaxFps_toShareBmp = param.talkerPolicy.conf_usFps;
	  }
	  //
	  if (pQyMc->appParams.bConfServer) {
		  if (pProcInfo->av.doConf.confReq.hgInfo.bFlow512k) {		//  对设置512的会议，设置融合视频de 输出码流为1m.
			  //avCompressor_conf.video.common.iAvgBitrate = 1000000;
			  avCompressor_conf.video.common.iAvgBitrate = 800000;
		  }
	  }

	  //
	  if (1) {
		  pProcInfo->dlgTalk_confStart_pre(hCurTalk, false, false, _T(""));
		  adjustAudioBitrate(&avCompressor_req.audio.common);
	  }


	  //  2014/10/07
	  TALKER_policy		tp;
	  getTalkerPolicy(&pMgrVar->addr.idInfo, &tp);

	  //
	  if (param.talkerPolicy.conf_iFourcc) {
		  tp.conf_iFourcc = param.talkerPolicy.conf_iFourcc;
	  }
	  if (param.talkerPolicy.conf_bitrateInKbps_dl) {
		  tp.conf_bitrateInKbps_dl = param.talkerPolicy.conf_bitrateInKbps_dl;
	  }
	  if (param.talkerPolicy.conf_bitrateInKbps_ul) {
		  tp.conf_bitrateInKbps_ul = param.talkerPolicy.conf_bitrateInKbps_ul;
	  }

	  //policy.ucb2Streams = param.talkerPolicy.ucb2Streams;
	  tp.uiTaskType = param.talkerPolicy.uiTaskType;
	  tp.shareDevice_grp_index = param.talkerPolicy.shareDevice_grp_index;

	  //
	  //pMgrVar->m_layout.ucbShowBgWall_starter  =  policy.ucbShowBgWall_starter;
	  //pMgrVar->m_layout.usPollingIntervalInS1  =  pShadowMgr->bgWall.bgWallCfg.usPollingIntervalInS;
	  pMgrVar->m_layout.bgWallLayoutCfg.usRows_bg = pShadowMgr->bgWall.bgWallCfg.bgWallLayoutCfg.usRows_bg;
	  pMgrVar->m_layout.bgWallLayoutCfg.usCols_bg = pShadowMgr->bgWall.bgWallCfg.bgWallLayoutCfg.usCols_bg;
	  //  2009/06/04
	  //  memcpy(  &videoCompressor,  &avCompressor_req.video,  sizeof(  videoCompressor  )  );
	  //
	  memset(&videoConferenceCfg, 0, sizeof(videoConferenceCfg));
	  switch (pMgrVar->addr.uiObjType) {
	  case  CONST_objType_imGrp:
		  if (getVideoConferenceCfg(HKEY_CURRENT_USER, ((QY_MC*)pProcInfo->pQyMc)->cfg.pSysCfg->rootKey_qnmScheduler, pMgrVar->addr.misServName, &pMgrVar->addr.idInfo, &videoConferenceCfg))  goto  errLabel;
		  //
		  if (param.conf_usMaxSpeakers) {
			  if (param.conf_usMaxSpeakers > 0 && param.conf_usMaxSpeakers <= MAX_speakers_taskAv) {
				  videoConferenceCfg.usMaxSpeakers = param.conf_usMaxSpeakers;
				  //		
				  _sntprintf(tBuf, mycountof(tBuf), _T("conf_usMaxSpeakers set to %d"), (int)param.conf_usMaxSpeakers);
				  showInfo_open0(0, 0, tBuf);
			  }
		  }
		  //
		  bVideoConference = TRUE;

		  //
		  if (tp.ucbConfCtrl_starter) {
			  pMgrVar->av.taskInfo.ucbConfCtrl = TRUE;
			  //
			  resetGrpConfCtrl(hMgr, &pShadowMgr->confCtrl.grpConfCtrl);
		  }
		  break;
	  default:
		  break;
	  }

	  //
	  uint  uiTaskType; uiTaskType = CONST_imTaskType_transferAvInfo;
	  if (param.talkerPolicy.uiTaskType) {
		  uiTaskType = param.talkerPolicy.uiTaskType;
	  }

	  //
	  if (bFirstUsr) {
		  CAP_procInfo_recordSound* pCapAudio = NULL;			//  2013/03/19
		  CAP_procInfo_video* pCapBmp = NULL;

		  //
		  pCapAudio = (CAP_procInfo_recordSound*)getCapAudioBySth(pProcInfo, pSharedObj->iIndex_capAudio, 0);
		  if (!pCapAudio)  goto  errLabel;
		  pCapBmp = (CAP_procInfo_video*)getCapBmpBySth(pProcInfo, pSharedObj->iIndex_capBmp, 0);
		  if (!pCapBmp)  goto  errLabel;

		  //
		  bool  bRecord_conf = pProcInfo->av.doConf.confReq.hgInfo.bRecord_conf;
		  bool  bRecord_trans = false;
		  //
#ifdef  __DEBUG__
		  if (pQyMc->appParams.bRecord_forDbg) {
			  bRecord_conf = true;
		  }
#endif

		  //
		  if (initSavers(bRecord_conf, bRecord_trans,pProcInfo->av.doConf.confReq.hgInfo.bLive, pProcInfo->av.doConf.confReq.hgInfo.liveUrl, pProcInfo->av.doConf.confReq.hgInfo.ui64MeetingId_hg, pMgrVar->addr.idInfo.ui64Id, iTaskId)) {
			  showInfo_open0(0, 0, _T("doCmd_startAvCall: initSavers failed"));
			  goto  errLabel;
		  }

		  //
		  pCapAudio->iIndex_sharedObj = iIndex_sharedObj;
		  pCapAudio->uiTranNo_sharedObj = pSharedObj->uiTranNo;

		  //
		  pCapBmp->iIndex_sharedObj = iIndex_sharedObj;
		  pCapBmp->uiTranNo_sharedObj = pSharedObj->uiTranNo;


		  //  2013/03/19. 这里要清理一下
		  pCapAudio->uiType = 0;
		  pCapBmp->uiType = 0;

		  //  2013/09/20
		  resetChromaKey();

		  {	  //  老的工作模式. 2013/03/19

				//
#if  1  //  def  __DEBUG__
			  if (pQyMc->appParams.bUse_forTest_noLocalAv) {
				  param.ucbNoLocalAv = true;
				  showInfo_open0(0, 0, _T("For test: noLocalAv"));
			  }
#endif
			  //
			  unsigned  short  usMaxSpeakers = videoConferenceCfg.usMaxSpeakers;
			  unsigned  short  usCntLimit_activeMems_from = 0;
			  calc_conf_param(bVideoConference, uiTaskType, &usMaxSpeakers, &usCntLimit_activeMems_from);

			  //
			  if (!param.ucbNoLocalAv) {

				  TCHAR	displayName[MAX_monikerDisplayNameLen + 1] = _T("");
				  if (pMgrVar->bIncludeACap) {
					  getMonikerDisplayName(getMoniker_a(pMgrVar->pCapStuff, pMgrVar->iMenuId_selectedAudio), displayName, mycountof(displayName));
				  }
				  TCHAR  capDevDesc[128] = _T("");
				  void* pADev = pMgrVar->bIncludeACap ? displayName : getADeviceGuid(pMgrVar->pCapStuff, pMgrVar->iMenuId_selectedAudio, capDevDesc, mycountof(capDevDesc));

				  if (!startLocalAudioRecorder(pQyMc, pProcInfo->cfg.policy.audio.uiRecordType, pADev, capDevDesc, iIndex_sharedObj, usCntLimit_activeMems_from, &avCompressor_req.audio)) {
					  //  pMgrVar->av.ucbLocalAudioRecorderStarted  =  TRUE;
				  }
#ifdef  __DEBUG__
				  //  if  (  !pMgrVar->av.ucbLocalAudioRecorderStarted  )  traceLogA(  "CDlgTalk::Onstartavcall: startLocalAudioRecorder failed."  );
#endif					
			  }
			  else {
				  showInfo_open0(0, 0, (TCHAR*)_T("Warning: NotRecordSound is true"));
			  }

			  //  
			  if (!param.ucbNoLocalAv)
			  {

				  //  2011/07/27						
				  if (newstartQThreadToShareAv(pProcInfo, iIndex_sharedObj, FALSE)) {
					  goto  errLabel;
				  }

				  //
				  if (!pProcInfo->av.localAv.videoCaptureProcInfo.bCapDevConnected) {
#ifndef  __noMfc__
					  CWaitCursor		cur;
#endif

					  if (pProcInfo->cfg.policy.video.uiCamCapType == CONST_camCapType_rtsp) {		//  2014/02/23	//start				  
#if  10
						  //  2014/03/15
						  int  size = sizeof(TRANSINFO_stream);
						  if (!pSharedObj->pTransInfo_stream) {
							  pSharedObj->pTransInfo_stream = mymalloc(size);
							  if (!pSharedObj->pTransInfo_stream)  goto  errLabel;
							  memset(pSharedObj->pTransInfo_stream, 0, size);
							  //
							  TRANSINFO_stream* pTransInfo = (TRANSINFO_stream*)pSharedObj->pTransInfo_stream;

							  //
							  {
								  void* pDb = NULL;
#ifndef  __NOTSUPPORT_DB__
								  CQnmDb		db;
								  if (!db.getAvailableDb(pQyMc->iDsnIndex_mainSys))  goto  errLabel;
								  pDb = db.m_pDbMem->pDb;
#endif
								  int  tmp_iTaskId;

								  tmp_iTaskId = newTaskId(pDb, pQyMc->cfg.db.iDbType);
								  pTransInfo->iTaskId = tmp_iTaskId;

							  }
							  pTransInfo->index_taskInfo = newTaskInfoIndex(pProcInfo, CONST_taskDataType_conf, hCurTalk, pTransInfo->iTaskId, _T(""));
							  if (pTransInfo->index_taskInfo < 0) {
								  showInfo_open0(0, 0, _T("doCmd_startAvCall: for rtsp: newTaskInfoIndex failed"));
								  goto  errLabel;
							  }
							  //
							  pTransInfo->myTask.ucbLocalSource_rtspStream = TRUE;
							  //
							  pTransInfo->myTask.iIndex_taskInfo = pTransInfo->index_taskInfo;

							  //
							  //pTransInfo->myTask.us
							  pTransInfo->myTask.usCntLimit_transforms = 1;
							  if (initTransforms(pProcInfo, &pTransInfo->addr_logicalPeer, 0, 0, &pTransInfo->tranInfo, &pTransInfo->myTask, NULL))  goto  errLabel;
							  //
#ifdef  __DEBUG__
							  safeTcsnCpy(_T("hhh"), pTransInfo->myTask.debugHint, mycountof(pTransInfo->myTask.debugHint));
							  pTransInfo->myTask.pTransforms[0].dwLastTickCnt_doApplyForPlayer_a = 987;
#endif 
							  //
							  QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, pTransInfo->index_taskInfo);
							  if (!pTaskInfo)  goto  errLabel;
							  QMC_taskData_conf* pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;
							  pTc->videoConference.usCntLimit_activeMems_from = 1;


							  //
#if 10
							  pTransInfo->myTask.usCntLimit_mems_from = 1;
							  size = sizeof(TASK_AV_FROM) * pTransInfo->myTask.usCntLimit_mems_from;
							  pTransInfo->myTask.pMems_from = (TASK_AV_FROM*)mymalloc(size);
							  if (!pTransInfo->myTask.pMems_from)  goto  errLabel;
							  memset(pTransInfo->myTask.pMems_from, 0, size);
#endif 
			  }

						  //
						  QY_REG  reg;
						  memset(&reg, 0, sizeof(reg));
						  reg.hKeyRoot0 = HKEY_CURRENT_USER;
						  lstrcpyn(reg.rootKey, pQyMc->cfg.pSysCfg->rootKey_qnmScheduler, sizeof(reg.rootKey));

						  TCHAR  url[256] = _T("");	//  _T(  "rtsp://127.0.0.1:8554/video.264"  );

						  if (qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, _T(CONST_regValName_rtspUrl_selected), (char*)url, sizeof(url), 0)) {
							  qyShowInfo1(CONST_qyShowType_warning, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("doCmd_startAvCall: rtsp url is wrong!"));
							  url[0] = 0;
						  }
						  //  2014/12/12. for test
						  if (pQyMc->appParams.rtspUrl[0]) {
							  safeTcsnCpy(pQyMc->appParams.rtspUrl, url, mycountof(url));
							  showInfo_open0(0, 0, CQyString(_T("TEST: doCmd_startAvCall: use rtsp url: ")) + url);
						  }
						  //
						  if (!openLocalVideo_rtsp((MC_VAR_common*)pProcInfo, url, &avCompressor_req.video, iIndex_sharedObj)) {
							  //  pMgrVar->av.u.av.uc.ucbLocalVideoOpen  =  TRUE;				

						  }
#endif
		  }
					  else {

						  TCHAR	displayName[MAX_monikerDisplayNameLen + 1] = _T("");

						  //
						  //getChosenDevice(0, 0, displayName, mycountof(displayName), 0, 0, 0, 0);
						  if (!pProcInfo->getChosenCamera(displayName, mycountof(displayName))) {
							  if (!displayName[0]) {
								  if (getMonikerDisplayName(getMoniker_v(pMgrVar->pCapStuff, pMgrVar->iMenuId_selectedVideo), displayName, mycountof(displayName)))  displayName[0] = 0;
							  }
						  }

						  if (!openLocalVideo((MC_VAR_common*)pProcInfo, pProcInfo->cfg.policy.video.uiCamCapType, displayName, &pMgrVar->pCapStuff, &avCompressor_req.video, iIndex_sharedObj)) {
							  //  pMgrVar->av.u.av.uc.ucbLocalVideoOpen  =  TRUE;				
						  }
						  if (!pMgrVar->pCapStuff)  dlgTalk_make_capStuff(hMgr, pMgrVar);

#ifdef  __DEBUG__
						  //  if  (  !pMgrVar->av.ucbLocalVideoOpen  )  traceLogA(  "CDlgTalk::Onstartavcall: openLocalVideo failed."  );
#endif									  
					  }
	  }
				  if (pProcInfo->av.localAv.videoCaptureProcInfo.bCapDevConnected) {
					  pProcInfo->av.localAv.videoCaptureProcInfo.curhWnd = hMgr;

					  //
					  //  2014/09/23. 建立多流						
					  int  level = 0;
					  if (makeSlaveStream(pQyMc, hMgr, iIndex_sharedObj, level, param.talkerPolicy.conf_iFourcc))  goto  errLabel;

				  }
  }
			  else {
				  showInfo_open0(0, 0, _T("Warning: notOpenVideo is true"));
			  }

		}
	}


	//


	  //
	  pMgrVar->av.taskInfo.iTaskId = iTaskId;
	  //
	  pMgrVar->av.taskInfo.dwTickCnt_start = myGetTickCount(NULL);

	  //  2014/10/30
	  if (pMgrVar->addr.uiObjType == CONST_objType_imGrp) {
		  if (b3D) {
			  //
			  AV_COMPRESSOR_CFG* pAvCompressor_resource = mynull;
			  AV_COMPRESSOR_CFG  avCompressor_resource;
			  memset(&avCompressor_resource, 0, sizeof(avCompressor_resource));
			  if (param.ucb2Streams) {
				  switch (param.talkerPolicy.conf_iFourcc) {
				  case  CONST_fourcc_h264:
				  case  CONST_fourcc_HEVC:
					  //
					  avCompressor_resource = avCompressor_req;
					  avCompressor_resource.video.common.iWidth_pic = 0;
					  avCompressor_resource.video.common.iHeight_pic = 0;
					  if (param.talkerPolicy.conf_iFourcc) {
						  set_conf_iFourcc(param.talkerPolicy.conf_iFourcc, param.talkerPolicy.conf_bitrateInKbps_dl, &avCompressor_resource);
					  }
					  //
					  avCompressor_resource.video.common.usMaxFps_toShareBmp = min(CONST_fps_mosaicDevice, avCompressor_resource.video.common.usMaxFps_toShareBmp);
					  //
					  pAvCompressor_resource = &avCompressor_resource;
					  break;
				  default:
					  showInfo_open0(0, 0, _T("Note: can't support 30fps for this conf_iFourcc "));
					  break;
							}
			}
			  //
			  if (pProcInfo->makeMosaicStream(hMgr, iTaskId, level, &avCompressor_conf, pAvCompressor_resource, param.talkerPolicy.conf_iFourcc, &pMgrVar->av.taskInfo.mosaicMaker)) {
				  goto  errLabel;
			  }

			  //
#ifdef __DEBUG__
			//int makeMosaicStream2()	;


			//
#endif

			//
			  QMC_mosaic_maker* pMosaic;  pMosaic = &pMgrVar->av.taskInfo.mosaicMaker;
			  //
#if  0  
			  QY_SHARED_OBJ* tmp_pSharedObj;
			  if (pMosaic->video.var.ucbLocalVideoOpen) {
				  tmp_pSharedObj = getSharedObjByIndex(pProcInfo, pMosaic->video.var.iIndex_sharedObj);
				  if (tmp_pSharedObj) {
					  addToMsgrs_sendLocalAv(pProcInfo, pMgrVar->pMisCnt, &pMgrVar->addr.idInfo, TRUE, &tmp_pSharedObj->curRoute_sendLocalAv);
				  }
			  }
			  if (pMosaic->resource.var.ucbLocalVideoOpen) {
				  tmp_pSharedObj = getSharedObjByIndex(pProcInfo, pMosaic->resource.var.iIndex_sharedObj);
				  if (tmp_pSharedObj) {
					  addToMsgrs_sendLocalAv(pProcInfo, pMgrVar->pMisCnt, &pMgrVar->addr.idInfo, TRUE, &tmp_pSharedObj->curRoute_sendLocalAv);
				  }
			  }
#endif
				  }
			  }

	  //  2016/03/14
	  P_sendAvInfo_taskInfo	pst;
	  memset(&pst, 0, sizeof(pst));
	  //  2017/08/02
	  pst.i.ucbVideoConference = (pMgrVar->addr.uiObjType == CONST_objType_imGrp);
	  //  2017/07/17
	  pst.i.ucbAvConsole = ucbAvConsole;
	  //  2017/08/25
	  pst.i.usConfType = usConfType;
	  //
	  pst.i.idInfo_initiator = param.idInfo_initiator;
	  //
#if 0
	  pst.i.ui64MeetingId_hg = pProcInfo->av.doConf.confReq.hgInfo.ui64MeetingId_hg;
	  pst.i.iMeetingType_hg = pProcInfo->av.doConf.confReq.hgInfo.iMeetingType_hg;
#endif
	  //
	  pst.i.hgInfo = pProcInfo->av.doConf.confReq.hgInfo;

	  //
	  if (pst.i.ucbVideoConference
		  && usConfType == CONST_usConfType_consult)
	  {
		  int  i, j;
		  for (i = 0; i < pShadowMgr->confCtrl.grpConfCtrl.usCnt; i++) {
			  GrpMem_confCtrl* pMem = &pShadowMgr->confCtrl.grpConfCtrl.pMems[i];
			  //  traceLog((TCHAR*)  _T(  "mem[%d] %I64u"  ),  i,  pMem->idInfo.ui64Id  );
			  //
			  if (!pMem->idInfo.ui64Id)  continue;
			  if (pMem->idInfo.ui64Id == pMisCnt->idInfo.ui64Id)  continue;
			  //
		  }
	  }
	  //  2017/09/06	
	  //
	  dlgTalk_init_respInfo(hMgr, pMgrVar, pst.i.ucbVideoConference);


	  //
	  switch (pMgrVar->addr.uiObjType) {
	  case  CONST_objType_imGrp:

		  QMC_mosaic_maker* pMosaic;  pMosaic = &pMgrVar->av.taskInfo.mosaicMaker;
		  if (procSendAvInfo_conf(pMgrVar->pMisCnt, hMgr, TRUE, uiTaskType, &videoConferenceCfg, &tp, &param, &avCompressor_conf, pMosaic, &pProcInfo->av.localAv.videoCaptureProcInfo.compressVideo, &pProcInfo->av.localAv.recordSoundProcInfo.compressAudio, iIndex_sharedObj, iIndex_sharedObjUsr, NULL, NULL, &iTaskId, &pMgrVar->addr, &pst))  goto  errLabel;

		  break;
	  case  CONST_objType_tmpGrp:
#ifdef  __DEBUG__
		  traceLog((TCHAR*)_T("Not supported: tmpGrp."));
#endif
		  goto  errLabel;
		  break;
	  default:
		  //
		  memset(&param, 0, sizeof(param));
		  if (!pQyMc->appParams.bConfServer) {
			  bool b100k = get_conf_b100k();
			  param.talkerPolicy.conf_ucb100k = b100k;
		  }
		  //				   
		  if (procSendAvInfo(pMgrVar->pMisCnt, hMgr, TRUE, CONST_imTaskType_transferAvInfo, &param, &pProcInfo->av.localAv.videoCaptureProcInfo.compressVideo, &pProcInfo->av.localAv.recordSoundProcInfo.compressAudio, iIndex_sharedObj, iIndex_sharedObjUsr, NULL, NULL, &iTaskId, &pMgrVar->addr, &pst))  goto  errLabel;

		  break;
	  }

	  {

		  //  2016/03/14
		  DLG_TALK_var& m_var = *pMgrVar;
		  //MIS_CNT  *  pMisCnt  =  pMgrVar->pMisCnt;
		  MSGR_ADDR* pAddr = &pMgrVar->addr;
		  int  lenInBytes = 0;
		  //
		  if (!m_var.av.taskInfo.bTaskExists) {  //  2014/10/31
			  showInfo_open0(0, 0, _T("procSendAvInfo failed, taskInfo.bTaskExists is false"));
			  goto  errLabel;
		  }

		  //
		  m_var.av.taskInfo.iTaskId = pst.o.iTaskId;
		  //  m_var.av.taskInfo.iIndex_sharedObj  =  iIndex_sharedObj;
		  m_var.av.taskInfo.idInfo_starter.ui64Id = pst.o.idInfo_starter.ui64Id;

		  m_var.av.taskInfo.tStartTime_org = pst.o.tStartTime_org;
		  m_var.av.taskInfo.uiTranNo_org = pst.o.uiTranNo_org;
		  m_var.av.taskInfo.uiContentType_org = pst.o.uiContentType_org;

		  m_var.av.taskInfo.ucbStarter = pst.o.ucbStarter;									//  2010/08/31
		  m_var.av.taskInfo.ucbVideoConference = pst.o.ucbVideoConference;					//  2010/08/31
		  //  m_var.av.taskInfo.ucbVideoConferenceStarter  =  pContent->myTask.ucbVideoConferenceStarter;

		  //  2017/08/25
		  m_var.av.taskInfo.usConfType = usConfType;

		  //
		  m_var.av.taskInfo.uiInitW = pst.o.uiInitW;
		  m_var.av.taskInfo.uiInitH = pst.o.uiInitH;

		  //  2014/09/25
		  m_var.av.taskInfo.iIndex_taskInfo = pst.o.iIndex_taskInfo;


		  //  2010/08/31
		  if (!m_var.av.taskInfo.ucbVideoConference) {
			  //  m_var.av.taskInfo.bNeedAutoRequestToSpeak  =  TRUE;
		  }

		  /////////////////
		  int  iMeetingLevel; iMeetingLevel = pProcInfo->av.doConf.confReq.hgInfo.iMeetingLevel_hg;
		  if (!iMeetingLevel) {
#ifdef  __DEBUG__
			  iMeetingLevel = pQyMc->appParams.iMeetingLevel_forDbg;
#endif
		  }
		  pProcInfo->av.confLayout.taskInfo.title[0] = 0;
		  if (iMeetingLevel) {
			  TCHAR* pT = (TCHAR*)_T("");
			  switch (iMeetingLevel) {
			  case  CONST_meetingLevel_gk:
				  pT = (TCHAR*)_T("公开");
				  break;
			  case  CONST_meetingLevel_nb:
				  pT = (TCHAR*)_T("内部");
				  break;
			  case  CONST_meetingLevel_mm:
				  pT = (TCHAR*)_T("秘密");
				  break;
			  case  CONST_meetingLevel_jm:
				  pT = (TCHAR*)_T("机密");
				  break;
			  default:
				  break;
			  }
			  safeTcsnCpy(pT, pProcInfo->av.confLayout.taskInfo.title, mycountof(pProcInfo->av.confLayout.taskInfo.title));
		  }
		  pProcInfo->av.confLayout.taskInfo.ucMbFlg = pProcInfo->getMbFlg(iMeetingLevel);

		  //
		  Mcu_initCfg mi; memset(&mi, 0, sizeof(mi));// = { 0 };
		  bGetMcuInitCfg(pQyMc->cfg.smCfgFile, &mi);
#if 0
		  GBuf_d3d_isCli* pGBuf_d3d = (GBuf_d3d_isCli*)pQyMc->pGBuf_d3d;
		  if (!pGBuf_d3d)  goto  errLabel;
		  pGBuf_d3d->bDraw3dFps = mi.bDraw3dFps;
#endif
		  //
		  pProcInfo->cfg.bSaveAv_conf = mi.bSaveAv_conf;
		  pProcInfo->cfg.bSaveAv_trans = mi.bSaveAv_trans;

		  //
		  QMC_TASK_INFO* pTaskInfo; pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, m_var.av.taskInfo.iIndex_taskInfo);
		  if (!pTaskInfo)  goto errLabel;
		  if (pTaskInfo->var.pTaskData->uiType != CONST_taskDataType_conf)  goto  errLabel;
		  QMC_taskData_conf* pTc; pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;
		  DLG_TALK_videoConference* pVc; pVc = &pTc->videoConference;

		  //
		  if (m_var.av.taskInfo.ucbVideoConference) {
			  pTc->grp.idInfo_initiator.ui64Id = param.idInfo_initiator.ui64Id;

			  //  2023/07/06
			  m_var.av.taskInfo.idInfo_initiator = param.idInfo_initiator;
		  }


		  //
		  if (uiTaskType == CONST_imTaskType_transferAvInfo) {
			  if (!m_var.av.taskInfo.ucbVideoConference) {
				  if (addToMsgrs_sendLocalAv(pProcInfo, pMisCnt, &m_var.addr.idInfo, FALSE, &pTaskInfo->var.curRoute_sendLocalAv, false, _T("doCmd_startAvCall.1258")))  goto  errLabel;
			  }
		  }



#if  10
		  if (true) {
			  HWND  hWnd_task = hMgr;
			  MIS_MSG_TASK* pMsg = &pTaskInfo->var.pTaskData->msgU.task;
			  //
			  CHelp_getDlgTalkVar	help_getDlgTalkVar;
			  DLG_TALK_var* pm_var = (DLG_TALK_var*)help_getDlgTalkVar.getVar(hWnd_task);
			  if (!pm_var)  goto  errLabel;
			  DLG_TALK_var& m_var = *pm_var;

			  if (uiTaskType != CONST_imTaskType_viewDynBmp) {	//  2014/09/26

				  //
				  if (dlgTalk_qPostMsg(hWnd_task, pMsg, offsetof(MIS_MSG_TASK, data) + pMsg->lenInBytes))  goto  errLabel;

				  //  2016/02/27
				  PARAM_PROC_ROW  param;
				  memset(&param, 0, sizeof(param));
				  param.bScrollIntoView = TRUE;
				  if (tmpHandler_showMsg(hWnd_task, &param, pMsg))  goto  errLabel;

				  //
				  //m_var.av.taskInfo.local_avStream.tranInfo.audio.  =  pContent_myTask->mem0_from.audio.ta_recvd;
				  //m_var.av.taskInfo.local_avStream.tranInfo.video  =  pContent_myTask->mem0_from.video.tv_recvd;
				  m_var.av.taskInfo.local_avStream = pst.o.local_avStream;

			  }
		  }





		  //
		  //  				
		  if (!m_var.av.taskInfo.ucbVideoConference
			  //||  pQyMc->iCustomId  ==  CONST_qyCustomId_hzj  
			  )
		  {
			  //  2018/10/28. hzj需要自动发言
			  //  2013/04/09. 在一对一时,自动将自己加入话筒列表,以便显示.				
			  DLG_TALK_videoConferenceActiveMemFrom* pActiveMem_from = NULL;

			  if (pTc->videoConference.activeMems_from[0].avStream.idInfo.ui64Id == pMisCnt->idInfo.ui64Id) {
				  _sntprintf(pTc->videoConference.activeMems_from[0].desc, mycountof(pTc->videoConference.activeMems_from[0].desc), _T("%s(%I64u)"), pMisCnt->displayName, pMisCnt->idInfo.ui64Id);
#ifdef  __DEBUG__
				  traceLog((TCHAR*)_T("Note: 	在一对一时,自动将自己加入话筒列表,以便显示."));
#endif
			  }
		  }


		  //
#if 0
		  if (pMgrVar->iTalkUsage != CONST_talkUsage_doConf) {
			  if (pMgrVar->addr.uiObjType == CONST_objType_imGrp) {
				  if (confStarter_fillGrpMems(hMgr, pMgrVar)) {
					  showInfo_open0(0, 0, _T("doCmd_startAvCall: confStart_fillGrpMems failed"));
					  goto  errLabel;
				  }
			  }
		  }
#endif

		  //
#endif

	  //
		  if (AEC_layout_init(iTaskId, pTc->videoConference.usCntLimit_activeMems_from, &pProcInfo->av.aecInfo.aecLayout))  goto  errLabel;


		  //  2016/03/15
		  if (syncMtCnt_start(&pMgrVar->av.syncMtCnt_taskInfo, pFuncs->isCliHelp.pf_getuiNextTranNo)) {
			  goto  errLabel;
		  }



		  //
		  //setCurSharedObjUsr_localAv(pProcInfo, iIndex_sharedObj, iIndex_sharedObjUsr);
		  //  2015/05/23
		  if (b3D) {
			  SHARED_OBJ_USR* pSharedObjUsr = getSharedObjUsr(pSharedObj, iIndex_sharedObjUsr);
			  if (!pSharedObjUsr)  goto  errLabel;
			  if (pSharedObjUsr->hWnd_starter != hMgr)  goto  errLabel;
			  pSharedObjUsr->bIn3DConf = TRUE;
		  }

		  //
		  pProcInfo->dlgTalk_confStart_post(hMgr, _T("doCmd_startAvCall. l1420"));

		  //
		  resetTalkerList_mgr(hMgr);

		  //
		  bChkMessengerChannelsReady(pQyMc);

		  //
		  pProcInfo->cfg.debugStatusInfo.tn_dumpAv = getuiNextTranNo(NULL, 0, NULL);

		  //
		  pProcInfo->status.confStatus.dwLastTickCnt_doCmd_startAvCall = myGetTickCount(mynull);
		  pProcInfo->status.confStatus.bDone_doCmd_startAvCall = true;

		  //
	  }

	  //
	  iErr = 0;
  errLabel:

	  closeInstantAssistant(hMgr);		//  2011/10/04

	  if (iErr) {
		  if (bTaskStarted) {	//  2014/10/31
			  if (pMgrVar) {
				  dlgTalk_closeTaskAv(hMgr, *pMgrVar);
			  }
		  }
	  }


	  if (pMgrVar) {
		  dlgTalk_displayAvStatus(hMgr, *pMgrVar, 0, 0, 0);
	  }

	  //  sizeAllControls_dlgTalk(  hMgr,  m_var,  NULL  );						//  
	  askToRefreshLayout_mgr(hMgr);

	  //  2013/07/20
	  if (pMgrVar) {
		  if (isTalkerShadowMgr(pMgrVar->addr)) {
			  //  d3dWall_refreshImgs(  hMgr  );
			  dyn_d3dWall_refreshWallMemByTalker(hMgr);
		  }
	  }

	  //  2017/07/07
	  refreshTalkToInfo_mgr(hMgr);

	  //
	  chkAvStatus();


	  //
	  return  iErr;
}


