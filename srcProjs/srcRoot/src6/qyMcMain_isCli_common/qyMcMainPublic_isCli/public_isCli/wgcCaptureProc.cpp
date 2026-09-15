
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"ctxQmc.h"
#include	"dlgtalkproc.h"
#include <qmcVideoCapture.h>
#include <qmcVideoCapture_isCli.h>
#include	"policyAvParams.h"
#include	"wgcCapObj.h"





//
RECT getScreenRect()
{
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = GetSystemMetrics(SM_CXSCREEN);
	rc.bottom = GetSystemMetrics(SM_CYSCREEN);
	return rc;
}

//
int  doCmd_startShareWgcCapture(QY_MC* pQyMc, HWND  hDlgTalk, void  *  pDLG_TALK_var, int level)
{
	int					iErr = -1;

#if  10
	//QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();

	DLG_TALK_var* pm_var = (DLG_TALK_var*)pDLG_TALK_var;
	if (!pm_var)  return  -1;
	DLG_TALK_var& m_var = *pm_var;

	//
	if (!m_var.av.taskInfo.bTaskExists) {
		showInfo_open0(0, 0, _T("shareScreen failed, av.taskinfo.bTaskExists is false"));
		return  -1;
	}

	//	
	QMC_TASK_INFO* pTaskInfo = (QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, m_var.av.taskInfo.iIndex_taskInfo);
	if (!pTaskInfo)  goto  errLabel;
	if (pTaskInfo->var.pTaskData->uiType != CONST_taskDataType_conf)  goto  errLabel;
	QMC_taskData_conf* pTc; pTc = (QMC_taskData_conf*)pTaskInfo->var.pTaskData;

	//
	if (pTc->shareScreen.bTaskExists) {
		showInfo_open0(0, 0, _T("shareScreen failed, shareScreen.bTaskExists already true"));
		goto  errLabel;
	}




	//		
	int						iIndex_sharedObj;
	int						iIndex_sharedObjUsr; iIndex_sharedObjUsr = 0;
	QY_SHARED_OBJ* pSharedObj; pSharedObj = NULL;
	int						iIndex_screenCapProcInfo;
	CAP_procInfo_screen* pScreenCapProcInfo; pScreenCapProcInfo = NULL;
	COMPRESS_VIDEO* pCompressVideo; pCompressVideo = NULL;
	unsigned  int				uiTaskType;

	OutputDebugString(_T("avRecord_start\n"));

	iIndex_sharedObj = newSharedObjIndex(pProcInfo, hDlgTalk, CONST_sharedObjType_screen, &iIndex_sharedObjUsr, NULL);
	if (iIndex_sharedObj < 0) {
		showInfo_open0(0, 0, _T("doCmd_startShareScreen failed, newSharedObj failed"));
		goto  errLabel;
	}
	pSharedObj = getSharedObjByIndex(pProcInfo, iIndex_sharedObj);
	if (!pSharedObj)  goto  errLabel;
	iIndex_screenCapProcInfo = newCapProcInfoBmpIndex(pProcInfo, iIndex_sharedObj);
	pScreenCapProcInfo = (CAP_procInfo_screen*)getCapBmpBySth(pProcInfo, iIndex_screenCapProcInfo, 0);
	if (!pScreenCapProcInfo)  goto  errLabel;
	pScreenCapProcInfo->uiType = CONST_capType_screen;
	pScreenCapProcInfo->iIndex_sharedObj = iIndex_sharedObj;
	pScreenCapProcInfo->uiTranNo_sharedObj = pSharedObj->uiTranNo;
	pCompressVideo = &pScreenCapProcInfo->compressVideo;

	//
	pSharedObj->bDirectX = false;// bDirectX_avRecord();
	pSharedObj->bRemoteAssist = false;// bRemoteAssist_avRecord();		//  2008/11/09, ÊÇ·ñÔ¶³ÌÐ­Öú				
	pSharedObj->iIndex_capBmp = iIndex_screenCapProcInfo;


	//  2014/04/19
	if (newstartQThreadToShareAv(pProcInfo, iIndex_sharedObj, FALSE)) {
		goto  errLabel;
	}

	//
	uiTaskType = pSharedObj->bRemoteAssist ? CONST_imTaskType_remoteAssist : CONST_imTaskType_shareScreen;

	//
	//m_var.av.ucbSendLocalScreen  =  TRUE;	

	//
	sizeAllControls_dlgTalk(hDlgTalk, &m_var, NULL);					//  µ÷ÕûÒ»ÏÂ²¼¾Ö

	//
	if (!level)  level = CONST_policyAvLevel_1080p;

	//  2011/08/08
	//int  level; level = getLevel_avRecord();
	AV_COMPRESSOR_CFG		screenCompressor;
	if (myGetAvCompressorCfg(CONST_capType_screen, 0, 0, level, &screenCompressor))  goto  errLabel;
	screenCompressor.video.common.uiCapType = CONST_capType_screen;

	//
	int  conf_iFourcc; conf_iFourcc = get_conf_iFourcc();
	//
	conf_iFourcc = fourccStr2i(pTc->videoConference.activeMems_from[0].avStream.obj.tranInfo.video.compressor.common.fourccStr);
	//
	int conf_bitrateInKbps; conf_bitrateInKbps = 0;
	//		  
	set_conf_iFourcc(conf_iFourcc, conf_bitrateInKbps, &screenCompressor);

	//
	screenCompressor.video.common.usMaxFps_toShareBmp = min(screenCompressor.video.common.usMaxFps_toShareBmp, CONST_fps_wgcCapture);

	//
	if (pSharedObj->m_pCapDev) {
		showInfo_open(0, 0, 0, _T("doCmd_startShareWgc failed, m_pCapDev is not null"));
		goto  errLabel;
	}
	try {
		//
		//pSharedObj->m_pCapDev = new WgcCapDev();
		//
		pSharedObj->m_pCapDev = new WgcCapObj();
	}
	catch (...) {
		showInfo_open(0, 0, 0, _T("doCmd_startShareWgc failed, new WgcCapDev except"));
		goto  errLabel;
	}

	//
	AV_COMPRESSOR_CFG* pCompressor; pCompressor = &screenCompressor;
	CAP_procInfo_screen* pCapBmp; pCapBmp = pScreenCapProcInfo;
	BITMAPINFOHEADER  policy_bih;// = pCapBmp->policy.bih;
	int  iIndex_capAudio; iIndex_capAudio = 0;
	int  iIndex_capBmp; iIndex_capBmp = iIndex_screenCapProcInfo;

	//
	if (pSharedObj->m_pCapDev->initDev(mynull, &policy_bih, iIndex_sharedObj))  goto  errLabel;
	//  pCapBmp->bCapDevConnected  =  TRUE;	//  2012/02/24

	//  
	if (!pSharedObj->m_pCapDev->bGetCapturePara(pProcInfo, iIndex_capAudio, iIndex_capBmp, pSharedObj->pShareMediaObj, mynull, &pCapBmp->vh_org, NULL))  goto  errLabel;


	//
#if 0
	RECT	selectedRc;		//  ÕâÀïÒª×¢Òâ£ºbmp¿í¶ÈÊÇselectedRcµÄ¿í¶È+1¡£³¤¶ÈÒ²ÊÇÈç´Ë¡£

	//selectedRc = getScreenRect();// getSelectedRect();
	selectedRc.top = 0;
	selectedRc.left = 0;
	selectedRc.right = pCapBmp->vh_org.bih.biWidth;
	selectedRc.bottom = pCapBmp->vh_org.bih.biHeight;

	//  makeBmpInfoHeader_rgb(  24,  selectedRc.right  -  selectedRc.left  +  1,  selectedRc.bottom  -  selectedRc.top  +  1,  &pCompressVideo->vh_decompress.bih  );
	makeBmpInfoHeader_rgb(24, selectedRc.right - selectedRc.left + 1, selectedRc.bottom - selectedRc.top + 1, &pScreenCapProcInfo->vh_org.bih);
#endif 
	//
	// 
	//  2014/04/05
	screenCompressor.video.common.pVideoQ2 = &pScreenCapProcInfo->thread.q2;
	screenCompressor.video.common.pParent_transform = pScreenCapProcInfo;
	//
	if (initCompressVideo(pProcInfo, (BITMAPINFO*)&pScreenCapProcInfo->vh_org.bih, CONST_capType_screen, &screenCompressor.video, FALSE, 0, pCompressVideo)) {
		//  qyShowHint(  _T(  "Initialize video compress failed!"  )  );  
		showNotification(NULL, 0, 0, 0, 0, 0, _T("Initialize video compress failed!"));
		goto  errLabel;
	}

	int  iTaskId; iTaskId = 0;
	iTaskId = m_var.av.taskInfo.iTaskId;

	//
	SHARED_OBJ_USR* pSharedObjUsr;
	pSharedObjUsr = getSharedObjUsr(pSharedObj, iIndex_sharedObjUsr);
	if (!pSharedObjUsr)  goto  errLabel;
	//
	COMPRESS_AUDIO* pCompressAudio; pCompressAudio = NULL;

	/*
	if  (  pCompressAudio  &&  pCompressAudio->uiTranNo_openAvDev_org  )  {	
		pSharedObjUsr->uiTranNo_openAvDev_a  =  pCompressAudio->uiTranNo_openAvDev_org  +  iIndex_sharedObjUsr;	//  pSharedObj->iIndex_curUsr;
	}
	*/
	//
	if (pCompressVideo && pCompressVideo->uiTranNo_openAvDev_org) {	//  
		pSharedObjUsr->uiTranNo_openAvDev_v = pCompressVideo->uiTranNo_openAvDev_org + iIndex_sharedObjUsr;	//  pSharedObj->iIndex_curUsr;
	}
	pSharedObjUsr->iTaskId = iTaskId;



	//  m_var.pProcInfo->av.localAv.curhWnd  =  this->m_hWnd;


	//
	if (pTc->shareScreen.bTaskExists)  goto  errLabel;
	pTc->shareScreen.index_sharedObj = iIndex_sharedObj;
	pTc->shareScreen.bTaskExists = true;


	//  
	//setFps_capScreen(screenCompressor.video.common.usMaxFps_toShareBmp);

	//
	//startAvRecord(pProcInfo, iIndex_screenCapProcInfo, g_pQyMc->gui.hMainWnd);


	//  2010/09/09
	setCurSharedObjUsr(pProcInfo, iIndex_sharedObj, iIndex_sharedObjUsr);
	//  2014/11/17				  	
	pProcInfo->setFlg_inConfMosaic(hDlgTalk, CONST_qyWndContentType_talker, iIndex_sharedObj, iIndex_sharedObjUsr);

	//
	if (m_var.av.taskInfo.ucbStarter) {
		AV_stream  tmpAs = { 0 };
		tmpAs.idInfo.ui64Id = m_var.pMisCnt->idInfo.ui64Id;
		tmpAs.obj.resObj.uiObjType = CONST_objType_screen;
		tmpAs.obj.tranInfo.video.uiTranNo_openAvDev = pSharedObjUsr->uiTranNo_openAvDev_v;
		tmpAs.obj.tranInfo.video.compressor = pCompressVideo->compressor;
		tmpAs.obj.tranInfo.video.vh_compress = pCompressVideo->vh_compress;
		tmpAs.obj.tranInfo.video.vh_stream = pCompressVideo->vh_stream;
		tmpAs.obj.tranInfo.video.vh_decompress = pCompressVideo->vh_decompress;
		//
		if (addTo_activeMems_from(m_var.pMisCnt, &tmpAs.idInfo, &tmpAs.obj, &pTc->videoConference)) {
			goto  errLabel;
		}
	}


	//  2014/11/14
	chkResources(hDlgTalk, FALSE);

	//
	QY_MESSENGER_ID  idInfo_dst;
	if (m_var.av.taskInfo.ucbStarter) {
		if (!m_var.av.taskInfo.ucbVideoConference) {
			idInfo_dst = m_var.addr.idInfo;
			pProcInfo->sendConfKey(hDlgTalk, idInfo_dst, _T("doCmd_startShareScreen"));
		}
	}
	else {  //
		//
		confOthers_requestToSpeak(hDlgTalk, iIndex_sharedObj, mynull, true);
	}




	//  2011/03/12
	dlgTalk_displayAvStatus(hDlgTalk, m_var, 0, 0, 0);


	//
	iErr = 0;

errLabel:
#endif 

	return  iErr;


}






