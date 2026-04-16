
#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"

#include	"qyDynLib.h"
#include	"qmcDmoPublic.h"
#include	"qmcCmdProc.h"
#include	"tmpCeLib.h"
#include	"module_qisCamCap.h"
#include	"isCmdConst.h"
#include	"qyOpenShellCommon.h"
#include	"qyCusResTemp.h"
#include	"policyAvParams.h"

//#include	"isClid3dpublic.h"
#include	"qmcTaskPublic.h"

#include	"qmcCfg.h"
#include	"dyn_isCliD3d_public.h"

#include    "GuiShare.h"




//  2015/10/11
int  exitObj_rtsp(  MC_VAR_common  *  pProcInfoCommon,  int  iIndex_sharedObj  )
{
	int  iErr  =  -1;

	MC_VAR_common	*	pProcInfo	=	(  MC_VAR_common  *  )pProcInfoCommon;	
	QY_SHARED_OBJ				*	pSharedObj			=		NULL;
	CAP_procInfo_video  *  pVc  =  NULL;
	
	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	
	if  (  !pSharedObj  )  goto  errLabel;
	
	//	
	int  iIndex_capBmp; iIndex_capBmp = pSharedObj->iIndex_capBmp;

		
	//	
	pVc  =  (  CAP_procInfo_video  *  )getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );		
	if  (  !pVc  )  goto  errLabel;
	

	stopCapture(  pProcInfo,  pVc  );
	if  (  pVc->bCaptureStarted  )  {
		traceLogA(  (char*)  "closeLocalVideo failed: capture is not stopped."  );
		goto  errLabel;
	}

	if  (  pVc->bCapDevConnected  )  {
        // Finally disconnect the driver
		switch  (  pVc->uiCamCapType  )  {
				case  CONST_camCapType_rtsp:		//  2014/02/24
					  if  (  exitVideoCapDev_rtsp(  pProcInfoCommon,  &pVc->capDev.pVideoCapDev  )  )  {
  						  #ifdef  __DEBUG__
								  traceLog((TCHAR*)  _T(  "closeLocalVideo failed, exitVideoCapDev_dx failed"  )  );
								  MACRO_qyAssert(  0,  _T(  "closeLocalVideo failed, exitVideoCapDev_dx failed"  )  );
						  #endif
						  goto  errLabel;
					  }
					  pVc->bCapDevConnected  =  FALSE;
					  break;
				default:
						goto  errLabel;
		}
		memset(  &pVc->capDev,  0,  sizeof(  pVc->capDev  )  );
	}
	if  (  pVc->bCapDevConnected  )  {
		traceLogA(  (char*)  "closeLocalVideo failed. bCapDevConnected is true"  );
		goto  errLabel;
	}

	iErr  =  0;

errLabel:

	return  iErr;

}

//
//  2015/01/28
int  freeSharedObjByIndex(  CCtxQmcTmpl  *  pProcInfoParam,  int  index  )
{
	int								iErr				=	-1;

	CCtxQmc  *  pProcInfo  =  (  CCtxQmc  *  )pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	if  (  !pQmcCfg  )  return  -1;

	//
	QY_SHARED_OBJ			*		pSharedObj			=	NULL;
	TCHAR							tHint[128]			=	_T(  ""  );		//  2014/05/27
		
	//
	if  (  index  <  0  ||  index  >=  pQmcCfg->usMaxCnt_pSharedObjs  )  return  -1;
	
	//
	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  index  );	//  &pProcInfo->pSharedObjs[index];
	
	//  2014/05/28
	_sntprintf(  tHint,  mycountof(  tHint  ),  _T(  "freeSharedObjByIndex %d %s enters"  ),  index,  qyGetDesByType1(  CONST_sharedObjTypeTable,  pSharedObj->uiType1  )  );
	//  2012/11/06
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"   ),  tHint  );


	//	
	CQySyncObj						syncObj;	
	//
	if  (  syncObj.sync(  pQmcCfg->mutexName_syncStartAv  )  )  {
		//  2012/11/06
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "freeSharedObjByIndex %d, sync failed"   ),  index  );
		goto  errLabel;
	}


	//
	if  (  !pSharedObj->bQuit  )  {
		pSharedObj->bQuit  =  true;
	}

	//
	int  i;
	for  (  i  =  0;  pSharedObj->hThread;  i  ++ )  {
		_sntprintf(  tHint,  mycountof( tHint  ),  _T(  "freeSharedObjByIndex: %d, waitfor shardObj->hThread. %d times"  ),  index,  i  );
		showInfo_open0(  0,  0,  tHint  );
		waitForObject(  &pSharedObj->hThread,  1000  );
	}

	//
	//  2014/09/28	
	if  (  !pSharedObj->bSlave  )  {
		if  (  bExists_slave(  pProcInfo,  index  )  )  {  										 
			QY_SHARED_OBJ  *  pSharedObj_master  =  pSharedObj; 
			int  iIndex_slave  =  pSharedObj_master->master.slaveKey.iIndex_sharedObj;
			QY_SHARED_OBJ  *  pSharedObj_slave  =  getSharedObjByIndex(  pProcInfo,  iIndex_slave  );
			
			//
			removeSlaveFromMaster(  pProcInfo,  iIndex_slave,  index  );
			if  (  bExists_master(  pProcInfo,  iIndex_slave  )  )  {
				showInfo_open0(  0,  0,  _T(  "Seriouse err: bExists_master also true after removeSlaveFromMaster"  )  );
				#ifdef  __DEBUG__
						assert(  false  );
				#endif
				goto  errLabel;
			}
								 
			//			
			shareDynBmp_closeTaskAv(  (  SHARE_dyn_bmp  *  )pSharedObj_master->master.pShareDynBmp_slave  );				
			//
			if  (  freeSharedObjByIndex(  pProcInfo,  iIndex_slave  )  )  {				
				showInfo_open0(  0,  0,  _T(  "Serious err: freeSharedObjByIndex iIndex_slave failed"  )  );
				#ifdef  __DEBUG__
						assert(  false  );
				#endif
			}				 
		}		
	}

	//  2014/09/29
	if  (  pSharedObj->bSlave  )  {
		removeSlaveFromMaster(  pProcInfo,  index,  pSharedObj->slave.masterKey.iIndex_sharedObj  );
		if  (  bExists_master(  pProcInfo,  index  )  )  {
			showInfo_open0(  0,  0,  _T(  "Seriouse err: bExists_master also true after removeSlaveFromMaster"  )  );
			#ifdef  __DEBUG__
					assert(  false  );
			#endif
			goto  errLabel;
		}
	}
	//  2014/10/31
	switch  (  pSharedObj->usSubtype  )  {
			case  CONST_sharedObjSubtype_mosaic:  {
				  pProcInfo->removeMosaicFromD3dWall(  index  );
				  BOOL  tmp_bExists  =  FALSE;
				  if  (  pProcInfo->getVal_bExists_mosaic(  index,  &tmp_bExists  )  )  {
					  goto  errLabel;
				  }
				  if  (  tmp_bExists  )  {
					  goto  errLabel;
				  }
			      }
				  break;
			default:
					break;
	}



	
	//  2013/08/23
	if  (  pSharedObj->bSoundRecorder  )  {
		#ifdef  __useMfc__
				 CWaitCursor		cur;
		#endif
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "freeSharedObj: try to stopLocalAudioRecorder"  )  );
		pProcInfo->stopLocalAudioRecorder(  index,  100  );
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "stopLocalAudioRecorder ends"  )  );

		//
		CAP_procInfo_audioU  *  pU  =  getCapAudioBySth(  pProcInfo,  pSharedObj->iIndex_capAudio,  0  );
		if  (  pU  )  {
		
			//
			if  (  pU->recordSound.compressAudio.bCompressInited  )  {
				qyExitProcess(  _T(  "freeSharedObjByIndex failed: can't wait for audio recorder."  )  );		
			}
			
			//  2013/03/21
			memset(  &pU->recordSound,  0,  sizeof(  pU->recordSound  )  );

		}
	}


	//
	if  (  !pSharedObj->bCapDev  )  {
		int		i;

		switch  (  pSharedObj->uiType1  )  {
				case  CONST_sharedObjType_mediaFile:  
					  if  (  pSharedObj->pShareMediaObj  )  {
						  #ifdef  __DEBUG__
								  traceLogA(  (char*)  "freeSharedObjByIndex: mediaFile: exitShareMediaFile %d",  index  );							   
						  #endif
						  if  (  exitShareMediaFile(  &pSharedObj->pShareMediaObj  )  )  goto  errLabel;
					  }
					  break;
				case  CONST_sharedObjType_av:
				case  CONST_sharedObjType_mediaDevice:  
					  if  (  pSharedObj->pShareMediaObj  )  {
						  #ifdef  __DEBUG__
								  traceLogA(  (char*)  "freeSharedObjByIndex: mediaDevice: exitShareMediaDevice %d",  index  );							   
						  #endif
						  if  (  exitShareMediaDevice(  &pSharedObj->pShareMediaObj  )  )  goto  errLabel;
					  }
					  break;
				case  CONST_sharedObjType_qvcf:
					  if  (  pSharedObj->pShareMediaObj  )  {
						  exitQvcf_rtsp(  pProcInfo,  &pSharedObj->pShareMediaObj  );

					  }
					  break;
				case  CONST_sharedObjType_webcam_av:  //  2015/05/18
					  if  (  pSharedObj->pShareMediaObj  )  {
						  exitSharedMediaObj(  pProcInfo,  pSharedObj  );					
					  }
					  break;
				case  CONST_sharedObjType_rtsp:  {//  2015/10/11
					  exitObj_rtsp(  pProcInfo,  index  );
					  }
					  break;
				case  CONST_sharedObjType_ic:
					if (pSharedObj->pIcObj) {					
						exitShareIc(&pSharedObj->pIcObj);
					}
					break;
				default:
						break;					
		}

		//
		for  (  i  =  0;  i  <  pQmcCfg->usMaxCnt_capProcInfoBmps;  i  ++  )  {
			 CAP_procInfo_bmpU  *  pU  =  getCapBmpBySth(  pProcInfo,  i,  0  );
			 if  (  pU  &&  pU->common.uiTranNo_sharedObj  ==  pSharedObj->uiTranNo  )  {

				 //  2011/12/04
				 stopQThread(  &pU->common.vppThread,  tHint  );
				 //
				 stopQThread(  &pU->common.thread,  tHint  );
				 stopQThread(  &pU->common.postThread,  tHint  );
				 //
				 if  (  pU->common.vppThread.bQInited  )  {
					 exitQyQ2(  &pU->common.vppThread.q2  );  pU->common.vppThread.bQInited  =  FALSE;
				 }
				 //  2009/12/07
				 if  (  pU->common.thread.bQInited  )  {
					 exitQyQ2(  &pU->common.thread.q2  );	pU->common.thread.bQInited  =  FALSE;
				 }
				 //  2011/12/06
				 if  (  pU->common.postThread.bQInited  )  {
					 exitQyQ2(  &pU->common.postThread.q2  );  pU->common.postThread.bQInited  =  FALSE;
				 }

				 //
				 //  2009/04/28
				 for  (  int  j  =  0;  j  <  mycountof(  pSharedObj->usrs  );  j  ++  )  {
					  if  (  !pSharedObj->usrs[j].iTaskId  )  continue;
					  notifyCapEnd(  pProcInfo->pQyMc,  pU->common.uiType,  i,  pSharedObj->usrs[j].iTaskId,  pSharedObj->usrs[j].hWnd_starter  );
				 }
				 //
				 //  2015/05/15. 这个清理应该是通用的吧
				 exitOrg2RgbBuf(  (  MC_VAR_common  *  )pProcInfo,  &pU->common  );  //  2014/09/23

				 //
				 #ifdef  __DEBUG__
						 traceLogA(  (char*)  "freeSharedObjByIndex: av: exitCompressVideo %d",  i  );
				 #endif
				 pProcInfo->exitCompressVideo(  pSharedObj->bCapDev,  &pU->common.compressVideo  );

				 //  2013/03/21
				 memset(  pU,  0,  sizeof(  pU[0]  )  );
			 }
		}
		for  (  i  =  0;  i  <  pQmcCfg->usMaxCnt_capProcInfoAudios;  i  ++  )  {
			 CAP_procInfo_audioU  *  pU  =  getCapAudioBySth(  pProcInfo,  i,  0  );
			 if  (  pU  &&  pU->common.uiTranNo_sharedObj  ==  pSharedObj->uiTranNo  )  {

				 //  2017/01/29
				 stopQThread(  &pU->common.appThread,  tHint  );
				 //  2009/12/07
				 stopQThread(  &pU->common.thread,  tHint  );
				 //
				 //  2017/01/29
				 if  (  pU->common.appThread.bQInited  )  {
					 exitQyQ2(  &pU->common.appThread.q2  );	pU->common.appThread.bQInited  =  FALSE;
				 }
				 //
				 if  (  pU->common.thread.bQInited  )  {
					 exitQyQ2(  &pU->common.thread.q2  );	pU->common.thread.bQInited  =  FALSE;
				 }
				 //
				 #ifdef  __DEBUG__
						 traceLogA(  (char*)  "freeSharedObjByIndex: mediaFile: exitCompressAudio"  );
				 #endif
				 exitCompressAudio(  pProcInfo,  &pU->common.compressAudio  );

				 if (pU->common.ctxResample) {
					 GuiShare.pf_exitResample(pU->common.ctxResample);
				 }

				 //  2013/03/21
				 memset(  pU,  0,  sizeof(  pU[0]  )  );
			 }
		}

#if  0
		if  (  pSharedObj->hProcess  )  {
			CloseHandle(  pSharedObj->hProcess  );  pSharedObj->hProcess  =  NULL;				
		}
		if  (  pSharedObj->dataShm.pBuf  )  {
			UnmapViewOfFile(  pSharedObj->dataShm.pBuf  );  pSharedObj->dataShm.pBuf  =  NULL;	
		}
		if  (  pSharedObj->dataShm.hMap  )  {		
			CloseHandle(  pSharedObj->dataShm.hMap  );  pSharedObj->dataShm.hMap  =  NULL;	
		}		
		QM_SHM_CMD	*	pShmCmd  =  (  QM_SHM_CMD  *  )pProcInfo->getQmShmCmdByIndex(  pSharedObj->iIndex_shmCmd  );
		if  (  pShmCmd  )  memset(  pShmCmd,  0,  sizeof(  pShmCmd[0]  )  );
#endif
		
		}
	else  {
		CAP_procInfo_bmpU  *  pU  =  getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
		unsigned  int  uiCapType  =  pU->common.uiType;
		
		//
		stopCapture(  pProcInfo,  &pU->video  );	//  2011/07/29
		
		//  2011/12/04
		stopQThread(  &pU->common.vppThread,  tHint  );
		//
		stopQThread(  &pU->common.thread,  tHint  );
		stopQThread(  &pU->common.postThread,  tHint  );

		//
		closeLocalVideo(  (  MC_VAR_common  *  )pProcInfo,  index  ); 

		//
		if  (  pU->common.vppThread.bQInited  )  {
			exitQyQ2(  &pU->common.vppThread.q2  );  pU->common.vppThread.bQInited  =  FALSE;
		}
		//
		if  (  pU->common.thread.bQInited  )  {
			exitQyQ2(  &pU->common.thread.q2  );  pU->common.thread.bQInited  =  FALSE;
		}
		//  2011/12/06
		if  (  pU->common.postThread.bQInited  )  {
			exitQyQ2(  &pU->common.postThread.q2  );  pU->common.postThread.bQInited  =  FALSE;
		}

		//
		for  (  int  j  =  0;  j  <  mycountof(  pSharedObj->usrs  );  j  ++  )  {
			 if  (  !pSharedObj->usrs[j].iTaskId  )  continue;
			 notifyCapEnd(  pProcInfo->pQyMc,  uiCapType,  pSharedObj->iIndex_capBmp,  pSharedObj->usrs[j].iTaskId,  pSharedObj->usrs[j].hWnd_starter  );
			 if  (  pProcInfo->hWnd_testWebcam  ==  pSharedObj->usrs[j].hWnd_starter  )  {
				 pProcInfo->hWnd_testWebcam  =  NULL;
			 }
		}

		//
		AEC_layout_exit(&pProcInfo->av.aecInfo.aecLayout);

		//  2013/03/21
		memset(  pU,  0,  sizeof(  pU[0]  )  );
	}

	//
	if  (  pSharedObj->pTransInfo_stream  )  {
		TRANSINFO_stream  *  pTransInfo  =  (  TRANSINFO_stream  *  )pSharedObj->pTransInfo_stream;
		exitTransforms(  pProcInfo,  &pTransInfo->myTask  );
		//
		freeTaskInfo(pProcInfo, pTransInfo->index_taskInfo, _T("freeSharedObjByIndex.transInfo_stream"));
		//
		MACRO_safeFree(  pTransInfo->myTask.pMems_from  );
	}
	MACRO_safeFree(  pSharedObj->pTransInfo_stream  );

	//
	if  (  !pSharedObj->bSlave  )  {
		if  (  pSharedObj->master.pShareDynBmp_slave  )  {
		}
		MACRO_safeFree(  pSharedObj->master.pShareDynBmp_slave  );
	}

	//
	memset(  pSharedObj,  0,  sizeof(  pSharedObj[0]  )  );
	
	iErr  =  0;

errLabel:


	//  2012/11/06
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "freeSharedObjByIndex %d leaves with %s"   ),  index,  iErr  ?  _T(  "Failed"  )  :  _T(  "OK"  )  );

	return  iErr;
}




