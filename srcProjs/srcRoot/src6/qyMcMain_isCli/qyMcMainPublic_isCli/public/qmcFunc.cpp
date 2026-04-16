


#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>
#include	"qyMcMainCommon.h"
#include	"qyWnd.h"
#include	"qmcCmdProc.h"
//#include	"qmcVWall.h"
//#include	"dlgTalkPublic.h"
#include	"qyThread.h"
#include	"qisD3dDefs.h"
#include <qmcVideoCapture.h>

//#include	"isCliD3dPublic.h"




//
//
QY_DMITEM  CONST_qyWndContentTypeTable[]  =
{
	{		CONST_qyWndContentType_testLocalAv,					(TCHAR*)_T(  "testLocalAv"  ),	},	//					2048		//  2009/09/07
	{		CONST_qyWndContentType_vWall,						(TCHAR*)_T(  "vWall"  ),		},	//						2049		//  2009/09/21
	{		CONST_qyWndContentType_mcClientLogon,				(TCHAR*)_T(  "mcCliLogon"  ),	},	//				2050		//  2010/07/14
	{		CONST_qyWndContentType_qyMc_winCe,					(TCHAR*)_T(  "qyMc-winCe"  ),	},	//					2051		
	{		CONST_qyWndContentType_qnmCfgOptionsIsClient,		(TCHAR*)_T(  "cfgOptIsCli"  ),	},	//		2052
	{		CONST_qyWndContentType_talker,						(TCHAR*)_T(  "talker"  ),		},	//						2053
	{		CONST_qyWndContentType_objs,						(TCHAR*)_T(  "objs"  ),			},	//							2054
	{		CONST_qyWndContentType_instantAssistant,			(TCHAR*)_T(  "ia"  ),			},	//				2055
	//{		CONST_qyWndContentType_conferenceResources,			(TCHAR*)_T(  "confRes"  ),		},	//			2056		//  2010/12/20
	{		CONST_qyWndContentType_dlgVideos,					(TCHAR*)_T(  "dlgVideos"  ),	},	//					2057		//  2011/02/02
	{		CONST_qyWndContentType_menu_walls,					(TCHAR*)_T(  "menu_walls"  ),	},	//					2059
	{		CONST_qyWndContentType_ts_main,						(TCHAR*)_T(  "ts_main"  ),		},	//						2060		//  2013/07/13
	{		CONST_qyWndContentType_consoleWall,					(TCHAR*)_T(  "d3dWall"  ),		},	//						2061
	{		CONST_qyWndContentType_imObjView_cli,				(TCHAR*)_T(  "imObjView_cli"  ),	},	//				2062		//  2013/07/26
	{		CONST_qyWndContentType_dlgImg,						(TCHAR*)_T(  "dlgImg"  ),			},	//						2063		//  2013/09/26
	{		CONST_qyWndContentType_dlgChromaKeyCfg,				(TCHAR*)_T(  "dlgChromakeyCfg"  ),	},	//				2064		//  2013/09/28
	{		CONST_qyWndContentType_dlgMsgTool,					(TCHAR*)_T(  "dlgMsgTool"  ),		},	//					2065		//  2014/01/25
	{		CONST_qyWndContentType_shareDynBmps,				(TCHAR*)_T(  "shareDynBmps"  ),		},	//  					2066		//  2014/09/22
	{		-1,	},
};


//
//
QY_DMITEM  CONST_wmGrpTypeTable[]  =
{
	{		CONST_wmGrpType_null,			(TCHAR*)_T(  "null"  ),	},
	{		CONST_wmGrpType_gZone,			(TCHAR*)_T(  "gZone"  ),	},
	{		CONST_wmGrpType_noWall,			(TCHAR*)_T(  "noWall"  ),	},
	{		CONST_wmGrpType_confWall,		(TCHAR*)_T(  "confWall"  ),	},

	{		CONST_wmGrpType_enlarge,		(TCHAR*)_T(  "enlarge"  ),	},
	//
	{		CONST_wmGrpType_prop,			(TCHAR*)_T(  "prop"  ),		},
	{		CONST_wmGrpType_menu,			(TCHAR*)_T(  "menu"  ),		},
	//
	{		CONST_wmGrpType_messageBox,		(TCHAR*)_T(  "messageBox"  ),		},
	//
	{		-1,		},
};




//
QY_DMITEM  CONST_wallMemTypeTable[]  =  
{	
	{		0,										(TCHAR*)_T(  "null"  ),				},
	//
	{		CONST_wallMemType_img,					(TCHAR*)_T(  "img"  ),				},

	//
	{		CONST_wallMemType_talker,				(TCHAR*)_T(  "talker"  ),			},
	{		CONST_wallMemType_dynBmp,				(TCHAR*)_T(  "dynBmp"  ),			},
	{		CONST_wallMemType_talkers,				(TCHAR*)_T(  "talkers"  ),			},
	{		CONST_wallMemType_walls,				(TCHAR*)_T(  "walls"  ),			},
	//
	{		CONST_wallMemType_noWall,				(TCHAR*)_T(  "noWall"  ),			},
	//
	{		CONST_wallMemType_enlarge,				(TCHAR*)_T(  "enlarge"  ),			},
	//
	{		CONST_wallMemType_list,					(TCHAR*)_T(  "list"  ),				},
	{		CONST_wallMemType_msgList,				(TCHAR*)_T(  "msgList"  ),			},
	{		CONST_wallMemType_control,				(TCHAR*)_T(  "control"  ),			},
	//
	{		CONST_wallMemType_menu,					(TCHAR*)_T(  "menu"  ),				},
	//
	{		CONST_wallMemType_talker_bgWall,		(TCHAR*)_T(  "talker_bgWall"  ),	},
	//
	{		-1,										(TCHAR*)_T(  ""  ),					},
};


//
 QY_DMITEM  CONST_wmSubtypeTable[]  =
 {
	 {		CONST_wmSubtype_null,					(TCHAR*)_T(  "null"  ),				},
	 {		CONST_wmSubtype_prop,					(TCHAR*)_T(  "prop"  ),				},
	 {		CONST_wmSubtype_menu,					(TCHAR*)_T(  "menu"  ),				},
	 {		CONST_wmSubtype_messageBox,				(TCHAR*)_T(  "messageBox"  ),		},
	 //
	 {		CONST_wmSubtype_bgWallMem,				(TCHAR*)_T(  "bgWallMem"  ),		},
	 //
	 {		CONST_wmSubtype_talkerBgZone,			(TCHAR*)_T(  "talkerBgZone"  ),		},
	 {		CONST_wmSubtype_talkerBgWall,			(TCHAR*)_T(  "talkerBgWall"  ),		},
	 //
	 {		CONST_wmSubtype_edit,					(TCHAR*)_T(  "edit"  ),				},
	 //
	 {		-1,										(TCHAR*)_T(  ""  ),					},
 };



//  2015/06/05. 用的都是窗口的全屏，不是3d的全屏，所以这里返回false
bool  bUseD3DFullScreen(  )
{
	return  FALSE;
}



//
 int  getTransformQName(  TCHAR  *  tName,  unsigned  int  cnt  )
{
	 _sntprintf(  tName,  cnt,  (TCHAR*)_T(  "transQ-%d"  ),  GetCurrentProcessId(  )  );
	 return  0;
}

 //  2011/12/14
 int  myShowInfo(  MC_VAR_common  *  pProcInfo,  void  *  p1,  LPCTSTR  hint  )
{
	//
	if  (  !pProcInfo  )  return  -1;
	
	TCHAR  *  who_from  =  (TCHAR*)_T(  "Gui"  );
	who_from  =  pProcInfo->who_showInfo;

	if  (  !hint  )  return  -1;
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  who_from,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  hint  );
	return  0;
}


 
#ifdef  __DEBUG__

 void  waitForQThread(  QY_qThreadProcInfo_common  * pQThread,  DWORD  dwMilliSeconds  )
{	
	waitForObject(  &pQThread->hThread,  dwMilliSeconds  );		
	return;
}
#endif

  int  startQThread(  LPTHREAD_START_ROUTINE lpStartAddress,  LPVOID lpParameter,  void  *  pThreadClass,  QY_qThreadProcInfo_common  *  pQThread  )
 {
	 int			iErr				=	-1;
	 DWORD			dwThreadDaemonId	=	0;
	 
	 //
	 if  (  lpStartAddress  )  {
		 pQThread->hThread  =  CreateThread(  NULL,  0,  lpStartAddress,  lpParameter,  CREATE_SUSPENDED,  &dwThreadDaemonId  );		
		 if  (  !pQThread->hThread  )  {
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "startQThread failed. CreateThread failed"  )  );
			 goto  errLabel;			
		 }
		 pQThread->dwThreadId  =  dwThreadDaemonId;			
		 if  (  ResumeThread(  pQThread->hThread  )  ==  -1  )  goto  errLabel;
		 }
	 else  {
		   CQyThread  *  pThread  =  (  CQyThread  *  )pThreadClass;
		   if  (  !pThread  )  goto  errLabel;
		   pThread->CreateThread(  );

		   pQThread->hThread  =  pThread->m_hThread;
		   //  qThread.hEvent_winThreadEnd  =  CreateEvent(  NULL,  FALSE,  FALSE,  NULL  );			  
		   pQThread->dwThreadId  =  pThread->m_nThreadID;			  
		   
		   pThread->ResumeThread(  );
	 }

	 iErr  =  0;

errLabel:

	 return  iErr;
}


 int  stopQThread(  QY_qThreadProcInfo_common  *  pThread,  LPCTSTR  hint  )
{
	TCHAR	tBuf[256];

	if  (  !hint  )  hint  =  _T(  ""  );

	if  (  pThread->hThread  )  {
		int  nTries  =  200;
		int  i;
		for  (  i  =  0;  i  <  nTries;  i  ++  )  {
			 if  (  !pThread->hThread  )  break;

			 //
			 pThread->bQuit  =  TRUE;						
			 SetEvent(  pThread->q2.hEvents[0]  );
			 waitForObject(  &pThread->hThread,  100  );
		}
		//
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "stopQ2Thread: %s, %s, wait for thread %d, nStep %d, elapse %dms. "  ),  hint,  pThread->q2.cfg.name,  pThread->dwThreadId,  pThread->debugStep.nStep_debug,  GetTickCount(  )  -  pThread->debugStep.dwTickCnt_step_debug  );
		//  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s  errs: notAccept %d, Input %d, output %d, index %d."  ),  tBuf,  p->video.debugStep.uiCnt_DMO_E_NOTACCEPTING,  p->video.debugStep.nErrs_ProcessInput,  p->video.debugStep.nErrs_ProcessOutput,  p->video.debugStep.nErrs_pOutputBuffers_index  ); 
		
#ifdef  __DEBUG__
		traceLogA(  (char*)  "%S",  tBuf  );
#endif
		//
		if  (  pThread->hThread  )  {
			qyExitProcess(  tBuf  );
		}
	}	

	return  0;
}



  //  2014/05/28
 QY_DMITEM  CONST_sharedObjTypeTable[]  =  
 {
	 {	CONST_sharedObjType_av,				(TCHAR*)_T(  "av"  ),	},
	 {	CONST_sharedObjType_mediaFile,		(TCHAR*)_T(  "mediaFile"  ),	},
	 {	CONST_sharedObjType_mediaDevice,	(TCHAR*)_T(  "mediaDevice"  ),	},
	 {	CONST_sharedObjType_webcam_vOnly,	(TCHAR*)_T(  "webcam_vOnly"  ),		},
	 {	-1,	},
 };


 //  2011/08/30
 //  2014/02/24.对rtsp流，必须设置bNoSkip为true, 不能把压缩包给扔掉
  int  setPktInputInfo(  MC_VAR_common  *  pProcInfoCommon,  VIDEO_input_info1  *  pInput,  unsigned  short  usFrames_perSecond_expected,  BOOL  bNoSkip,  void  *  pmyDRAW_VIDEO_DATA,  Param_setPktInputInfo  *  pParam,  LPCTSTR  hint  )
{
	int						iErr			=	-1;		
	if  (  !hint  )  hint  =  (TCHAR*)_T(  ""  );

	Param_setPktInputInfo  param;
	memset(&param, 0, sizeof(param));
	if (pParam)param = *pParam;


	//
	if  (  !pProcInfoCommon  )  {
		MACRO_qyAssert(  0,  _T(  "setPktInputInfo failed, pProcInfo is null"  )  );	
		return  -1;
	}

	//
	time_t					tStartTran;					mytime(  &tStartTran  );  
	TCHAR					tBuf[128]  =  _T(  ""  );

	//
#ifdef  __DEBUG__
	if (param.bTest_tStartTran) {
		tStartTran = param.tStartTran;
	}
#endif

	//
	//VIDEO_input_info  *  pInput  =  &pVc->compressVideo.input;
	//unsigned  short  usFrames_perSecond_expected  =  pVc->compressVideo.usFrames_perSecond_expected;

	//
	if  (  pInput->videoInputInfo.tStartTran  !=  tStartTran  )  {
		//
		
		if (param.uiCapType == CONST_capType_mosaic) {
			bool  bPrint = false;
			//
			if (bPrint) {
				if (param.bFromMosaic) {
					//_sntprintf(tBuf, mycountof(tBuf), _T("setPktInputInfo: fromMosaic %d, index_mosaic %d, fps %d, fps_ok %d %s"), param.bFromMosaic, param.index_mosaic, pInput->videoInputInfo.usFramesThisSecond, pInput->n_ok_thisSecond, hint);
					_sntprintf(tBuf, mycountof(tBuf), _T("setPktInputInfo: fromMosaic, index_mosaic %d, fps %d, fps_ok %d %s"), param.index_mosaic, pInput->videoInputInfo.usFramesThisSecond, pInput->n_ok_thisSecond, hint);
				}
				else {
					myDRAW_VIDEO_DATA* pPkt = (myDRAW_VIDEO_DATA*)pmyDRAW_VIDEO_DATA;
					if (pPkt) {
						if (!param.uiCapSubtype) {
							_sntprintf(tBuf, mycountof(tBuf), _T("setPktInputInfo: bResource %d, fps %d, fps_ok %d %s"), pPkt->input.bMosaicResource, pInput->videoInputInfo.usFramesThisSecond, pInput->n_ok_thisSecond, hint);
						}
						else {
							switch (param.uiCapSubtype) {
							case  CONST_subCapType_mosaic_resource:
								_sntprintf(tBuf, mycountof(tBuf), _T("setPktInputInfo: mosaicResource, fps %d, fps_ok %d %s"), pInput->videoInputInfo.usFramesThisSecond, pInput->n_ok_thisSecond, hint);
								break;
							case  CONST_subCapType_mosaic_video:
								_sntprintf(tBuf, mycountof(tBuf), _T("setPktInputInfo: mosaicVideo, fps %d, fps_ok %d %s"), pInput->videoInputInfo.usFramesThisSecond, pInput->n_ok_thisSecond, hint);
								break;
							default:
								_sntprintf(tBuf, mycountof(tBuf), _T("setPktInputInfo: capsubtype %d, fps %d, fps_ok %d %s"), param.uiCapSubtype, pInput->videoInputInfo.usFramesThisSecond, pInput->n_ok_thisSecond, hint);
								break;
							}
						}
					}
				}
				traceLog((TCHAR*)tBuf);
				showInfo_open0(0, 0, tBuf);
			}
		}

		//
		DWORD  dwTickCnt = myGetTickCount(mynull);
		int iElapseInMs = abs((int)(dwTickCnt - pInput->toGetFps.dwTickCnt_startToCalc));
		if (iElapseInMs > 60000) {
			pInput->toGetFps.nTotal_toCalc = 0;
			pInput->toGetFps.dwTickCnt_startToCalc = dwTickCnt;
			//
			//pInput->videoInputInfo.usFps = pInput->videoInputInfo.usFramesThisSecond;
		}
		else {
			 //
			if (!iElapseInMs) {
				//pInput->videoInputInfo.usFps = pInput->videoInputInfo.usFramesThisSecond;
			}
			else {
				//
				pInput->toGetFps.nTotal_toCalc += pInput->videoInputInfo.usFramesThisSecond;
				//
				pInput->videoInputInfo.usFps = pInput->toGetFps.nTotal_toCalc * 1000. / iElapseInMs;
			}

		}

		//
		if (pInput->videoInputInfo.usFps > usFrames_perSecond_expected)  pInput->uiNeedSkipped = pInput->videoInputInfo.usFps - usFrames_perSecond_expected;
		else  pInput->uiNeedSkipped = 0;

		//
		pInput->videoInputInfo.usFramesThisSecond  =  1;
		//
		pInput->videoInputInfo.tStartTran  =  tStartTran;
		//
		pInput->n_ok_thisSecond = 0;
		}		
	else  {
		  pInput->videoInputInfo.usFramesThisSecond  ++  ;		
	}

	//
	int  index  =  pInput->videoInputInfo.usFramesThisSecond  -  1;
		
	//  2011/08/31
	if  (  !bNoSkip  )  {
			 //  2009/10/29
			 //  int	index  =  pCompressVideo->usFramesThisSecond_input  -  nPkts  +  ii;
			 //COMPRESS_VIDEO	*	pCompressVideo  =  &pVc->compressVideo;


			 int  tmpusFps_input  =  pInput->videoInputInfo.usFps;	//  _input;
			 int  tmpuiFps_expected	=	usFrames_perSecond_expected;
			 if  (  !tmpuiFps_expected  )  tmpuiFps_expected  =  1;
			 
			 if  (  tmpusFps_input  >  tmpuiFps_expected  )  {

				 BOOL	bSkipped  =  FALSE;
				 int	k  =  0;
				 //
				 if  (  tmpuiFps_expected  >  2  )  k  =  (  tmpusFps_input  +  2  )  /  tmpuiFps_expected;
				 else  k  =  tmpusFps_input  /  tmpuiFps_expected;

#ifdef  __DEBUG__
				 //  traceLog((TCHAR*)  _T(  "k %d, fps_input %d"  ),  k,  tmpusFps_input  );
#endif

				 if  (  k  >  1  )  {	//  如果要发送的帧数是小部分，则选择数要发送的帧
					 if  (  (  index  %  k  )  )  {
						 bSkipped  =  TRUE;
						 }
#if 0
					 else  {	//  2012/03/16
						   int  fps_real  =  0;
						   //
						   if  (  k  >  2  )  fps_real  =  (  tmpusFps_input  +  2  )  /  k;
						   else  fps_real  =  tmpusFps_input  /  k;

						   int  index_real  =  index  /  k;
						   if  (  fps_real  >  tmpuiFps_expected  )  {
							   int  nThrows  =  fps_real  -  tmpuiFps_expected;
							   k  =  fps_real  /  nThrows;
							   if  (  fps_real  >  nThrows  *  k  )  k  ++  ;
							   if  (  !(  index_real  %  k  )  )  {
								   bSkipped  =  TRUE;
							   }
						   }
					 }
#endif
					 }
				 else {	//  如果要发送的帧数是大多数，则选择数丢弃帧
					 int  nThrows = tmpusFps_input - tmpuiFps_expected;
					 k = tmpusFps_input / nThrows;
					 if (tmpusFps_input > nThrows * k)  k++;
					 if (!(index % k)) {
						 bSkipped = TRUE;
					 }
				 }

				 //if (pInput->uiNeedSkipped) 
				 {

					 //
					 if (bSkipped) {
						 //
						 pInput->uiNeedSkipped--;

						 //

#ifdef  __DEBUG__
#if  0
						 traceLogA((char*)"toShareBmp: fps_input %d, fps_expected %d, frames[%d] skipped", (int)pCompressVideo->usFramesPerSecond_input, (int)pCompressVideo->usFrames_perSecond_expected, index);
#endif
#endif

						 goto  errLabel;
					 }
				 }
			 }

			 //
			 if (pInput->n_ok_thisSecond >= tmpuiFps_expected) {
				 goto  errLabel;
			 }
	}

	//
	//
	myDRAW_VIDEO_DATA* pPkt;pPkt = (myDRAW_VIDEO_DATA*)pmyDRAW_VIDEO_DATA;
	if  (  pPkt  )  {
		pPkt->input.tStartTran  =  tStartTran;													//  2011/08/30
		//  pPkt->input.usIndexThisSecond  =  pInput->usFramesThisSecond  -  1;

	}
	//
	pInput->n_ok_thisSecond++;


	iErr  =  0;
errLabel:

	//
	BOOL  bNoShow  =  FALSE;
	bNoShow = true;
#ifdef  __DEBUG__
	#if  0
		if  (  _tcsstr(  pInput->tBuf,  _T(  "BuffCB_av"  )  )  )  {
			bNoShow  =  TRUE;
		}
	#endif
		//
		//bNoShow = false;
#endif

	//
	QMC_debugStatusInfo  *  pCfg_debugStatusInfo  =  pProcInfoCommon->get_qmc_debugStatusInfo(  );

	//
	if  (  iErr  )  {
		#ifdef  __DEBUG__
				//  traceLog((TCHAR*)  _T(  "setPktInputInfo:  pkt[%d] skipped"  ),  index  );
		#endif
		bool  bPrint = false;
		//
#if 0
		if (param.bFromMosaic) {
			bPrint = true;
		}
#endif
		//
		//if  (  pCfg_debugStatusInfo  &&  pCfg_debugStatusInfo->ucbShowVPktInputInfo  &&  !bNoShow  )  
		if  (  bPrint )
		{
			//
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "setPktInputInfo:  pkt[%d] skipped"  ),  index  );			

			//
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %s"  ),  tBuf,  hint  );

			//
			showInfo_open0(  0,  0,  tBuf  );
#ifdef  __DEBUG__
			traceLog(tBuf);
#endif
			int  ii = 0;
		}
	}
	if  (  !iErr  )  {
		//
		bool  bPrint = false;
		//
#if 10
		if (param.bFromMosaic) {
			//bPrint = true;
		}
#endif
		CCtxQyMc* pQyMc = g_pQyMc;
		if (!pQyMc->appParams.bConfServer) {
			//bPrint = true;
		}

		//
		//if  (  pCfg_debugStatusInfo  &&  pCfg_debugStatusInfo->ucbShowVPktInputInfo  &&  !bNoShow  )  
		if  (  bPrint  )
		{
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "setPktInputInfo:  pkt[%d] ok"  ),  index  );
			//
			//_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, usFramesThisSecond %d"  ),  tBuf,  (  int  )pInput->videoInputInfo.usFramesThisSecond  );
			//
			_sntprintf(tBuf, mycountof(tBuf), _T("%s, n_ok_thisSecond %d"), tBuf, pInput->n_ok_thisSecond  );
			//
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %s"  ),  tBuf,  hint  );

			//
			showInfo_open0(  0,  0,  tBuf  );
#ifdef  __DEBUG__
			traceLog(tBuf);
#endif

		}
	}

	//
	return  iErr;
}



   //
   ///
//  2016/05/24
int  tmpPostMessage_cmd(  HWND  hParent_expected,  int  id,  HWND  hTalker  )
{
	//  PostMessage(  m_var.data.hTalkerMgr,  WM_COMMAND,  MAKEWPARAM(  ID_msgBox,  0  ),  0  );
	QY_wmBuf_command	wmBuf  =  {0};
	wmBuf.uiType  =  CONST_qyWmParam_command;
	wmBuf.iCmdId  =  id;
	wmBuf.hParent_expected  =  hParent_expected;
	SendMessageTimeout(  hTalker,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf,  0,  1000,  NULL    );
	return  0;
}


///////////////

 //
  //
  extern  "C"  __declspec(  dllexport  )  BOOL  bRecordRunning(  void  *  pCAP_procInfo_recordSound  )
{
	BOOL  bRet  =  FALSE;

	//
	CAP_procInfo_audioU  *  pCapAudioU  =  (  CAP_procInfo_audioU  *  )pCAP_procInfo_recordSound;
	if  (  pCapAudioU->common.uiType  !=  CONST_capType_av  )  return  FALSE;
	CAP_procInfo_recordSound  *  pRecord  =  (  CAP_procInfo_recordSound  *  )&pCapAudioU->recordSound;
	unsigned  int  uiRecordType  =  pRecord->uiRecordType;

	//
	switch  (  uiRecordType  )  {
			case  CONST_recordType_webRtc:  {
				  int  nDiff  =  0;
				  DWORD  dwTickCnt  =  GetTickCount(  );
				  nDiff  =  dwTickCnt  -  pRecord->dwTickCnt_lastAudioGot;
				  nDiff  =  abs(  nDiff  );
				  //
				  if  (  nDiff  <  1000  )  {
					  bRet  =  TRUE;
					  break;
				  }					  
				  //
				  }
				  break;
			default:
				    if  (  pRecord->recThread.bRunning  )  bRet  =  TRUE;
					break;
	}

	return  bRet;
}

 
    //
  extern  "C"  __declspec(  dllexport  )  BOOL  bCameraRunning(  void  *  pCAP_procInfo_bmp  )
{
	BOOL  bRet  =  FALSE;

	//
#ifdef  __DEBUG__
		#if  0
			  traceLog((TCHAR*)  _T(  "TEST: bCameraRunning returns false"  )  );
			  return  FALSE;
		#endif
#endif

	//
	CAP_procInfo_bmpU  *  pCapBmpU  =  (  CAP_procInfo_bmpU  *  )pCAP_procInfo_bmp;
	if  (  pCapBmpU->common.uiType  !=  CONST_capType_av  )  return  FALSE;
	CAP_procInfo_video  *  pVc  =  &pCapBmpU->video;
	unsigned  int  uiCamCapType  =  pVc->uiCamCapType;

	//
	switch  (  uiCamCapType  )  {
			case  CONST_camCapType_directX:  {
				  int  nDiff  =  0;
				  DWORD  dwTickCnt  =  GetTickCount(  );
				  //
				  nDiff  =  dwTickCnt  -  pVc->dwTickCnt_captureStarted;
				  nDiff  =  abs(  nDiff  );
				  if  (  nDiff  <  5000  )  {
					  bRet  =  TRUE;
					  break;
				  }					  
				  //
				  nDiff  =  dwTickCnt  -  pVc->dwTickCnt_lastVideoGot;
				  nDiff  =  abs(  nDiff  );
				  //
				  if  (  nDiff  <  1000  )  {
					  bRet  =  TRUE;
					  break;
				  }					  
				  //
				  }
				  break;
			default:
					break;
	}

	return  bRet;
}


  int  set_bConnectionTimeout(LPCTSTR  hint  )
  {
	  traceLog((TCHAR*)  _T(  "not finished: set_bConnectionTimeout"  )  );
	  return  0;
  }


