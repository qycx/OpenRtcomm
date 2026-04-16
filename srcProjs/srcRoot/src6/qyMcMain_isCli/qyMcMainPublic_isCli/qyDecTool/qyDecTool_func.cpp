
#include "stdafx.h"
#include "qyDecTool.h"
#include	"qyDecToolCommon.h"

//#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
//#include	"qyMcMainWndProc.h"
//
//#include	"dlgTalkProc.h"
#include	"qyGuiCommon.h"
#include	"qyOpenGuiCommon.h"

#include	"qyGuiCommProc.h"

#include	"qmcShareDynBmp.h"


 BOOL  bApp_ts(  )
 {
	 return  FALSE;
 }


  BOOL  canSave_fourcc(  int  iFourcc  )
  {
	  return  TRUE;
  }


 __declspec(  dllexport  )  int  showNotification(  void  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiContentType,  LPCTSTR  hint  )
 {
	 return  -1;
 }



__declspec(  dllexport  )  int  WINAPI  qyMessageBox(  HWND hWnd ,  LPCWSTR lpText,  LPCWSTR lpCaption,  UINT uType,  UINT  nTimeoutInS,  BOOL  *  pbSyncFlg  )
{
	return  -1;
}



 void  setEncodingDefaults_video(  unsigned  int  uiCapType,  float  fFps,  DWORD  fourcc,  VIDEO_ENC_PARAMS  *  pParams  )
 {
 }


   int  initCompressAudio_dmo(  AUDIO_COMPRESSOR_CFG  *  pCompressor,  QY_AUDIO_HEADER  *  pAh_decompress,  QY_AUDIO_HEADER  *  pAh_compress,  MY_DMO_INFO  *  pDmoInfo  )
   {
	   return  -1;
   }


    int  exitCompressAudio_dmo(  MY_DMO_INFO  *  pDmoInfo  )
	{
		return  -1;
	}


	 int  compressAudio_dmo(  MY_DMO_INFO  *  pDmoInfo,  QY_AUDIO_HEADER  *  pAh_decompress,  BYTE  *  pInput,  unsigned  int  uiInputLen,  int  iSampleTimeInMs  )
	 {
		 return  -1;
	 }

#if  10
BOOL  bQyOpenMcView(  QY_MCVIEW_SEL  *  pParam,  void  *  p1,  void  *  p2  )
{
	return  FALSE;
}
#endif
void  qyMcView_delAllColumns(  void  *  pView,  void  *  p1,  void  *  p2  )
{
	  return;
}
BOOL  qyMcView_bAddColumns(  void  *  pView,  QY_COLUMNINFO * pColumns,  void  *  p2  )
{
	return  FALSE;
}





  


	  int  showNotification_open(  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiContentType,  LPCTSTR  hint  )
	  {
		  return  -1;
	  }






   int  getLvColContent(  HWND  hParent,  HWND  hList,  int  curnItem,  LPCTSTR  colName,  TCHAR  *  buf,  unsigned  int  size  )
{
	  return  -1;
}
int  enumLvSelEventFunc(  QY_EVENTINFO  *  pEventInfo,  PF_procLvEventFunc  pf,  void  *  pObjDb,  int  iLvType,  void  *  pParam  )
{
	  return  -1;
}


 int  postMsg2MgrFunc_mc(  void  *  pMIS_CNT,  MSG_ROUTE  *  pRoute,  unsigned  int  uiMisMsgType,  unsigned  char  ucFlg,  unsigned  short  usCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  short  usSeqNo,  int  iTaskId,  unsigned  int  uiTaskType,  char  *  data,  unsigned  int  dataLen,  
						QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  
						QY_MESSENGER_ID	 *  pIdInfo_taskSender,					
						QY_MESSENGER_ID	 *  pIdInfo_taskReceiver,				
						QY_MESSENGER_ID  *  pIdInfo_dst,  
						unsigned  int  uiChannelType,
						MIS_MSGU  *  pMsgBuf,  BOOL  bLog  )
 {
	 return  -1;
 }




  int  postMsgTask2Mgr_mc(  void  *  pMIS_CNT,  unsigned  int  uiMisMsgType,  unsigned  char  ucFlg,  unsigned  short  usCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  int  iTaskId,  unsigned  int  uiTaskType,  char  *  data,  unsigned  int  dataLen,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_taskSender,  QY_MESSENGER_ID  *  pIdInfo_taskReceiver,  QY_MESSENGER_ID  *  pIdInfo_dst,  unsigned  int  uiChannelType,  MIS_MSGU  *  pMsgBuf,  BOOL  bLog  )
  {
	  return  -1;
  }



 HACMDRIVERID  find_driver(  WORD  wformatTag,  WORD  nChannels,  DWORD  nSamplesPerSec,  WORD  wBitsPerSample  )
 {
	 return  NULL;
 }

  WAVEFORMATEX  *  get_driver_format(  HACMDRIVERID  hadid,  WORD  wFormatTag,  WORD  nChannels,  DWORD  nSamplesPerSec,  WORD  wBitsPerSample  )
  {
	  return  NULL;
  }

   WAVEFORMATEX  *  get_driver_suggestedFormat(  HACMDRIVERID  hadid,  WAVEFORMATEX  *  pWfSrc,  WORD  wFormatTag,  WORD  nChannels,  DWORD  nSamplesPerSec,  WORD  wBitsPerSample  )
   {
	   return  NULL;
   }


    int convertAudio(  HACMSTREAM  hstr1,  HACMSTREAM  hstr2,  WAVEFORMATEX  *  pWfSrc,  BYTE  *  pSrcData,  DWORD  dwSrcBytes,  WAVEFORMATEX  *  pWfPcm,  BYTE  *  pPcmBuf,  DWORD  dwPcmBufSize,  WAVEFORMATEX  *  pWfDrv,  BYTE  *  pDstData,  DWORD  *  pdwDstBytes  )
	{
		return  -1;
	}


	 int  getDmoOutputByIndex(  MY_DMO_INFO  *  pDmoInfo,  int  index,  BYTE *  pbOutData,  unsigned  int  *  puiDataSize,  unsigned  int  *  puiSampleTimeInMs,  unsigned  int  *  pui_rtTimeLen  )
	 {
		 return  -1;
	 }


	   int  stopLocalAudioRecorder(  int  index_sharedObj,  int  nTries  )
	   {
		   return  -1;
	   }


	    BOOL  bSupported_avLevel(  QY_MC  *  pQyMc,  unsigned  int  uiCapType,  BITMAPINFO  *  pBmpInfo_input,  VIDEO_COMPRESSOR_CFG  *  pCompressor  )
		{
			return  FALSE;
		}


		 DWORD WINAPI mcThreadProc_vpp( LPVOID lpParameter )
		 {
			 return  0;
		 }

		  DWORD WINAPI mcThreadProc_encVideo( LPVOID lpParameter )
		  {
			  return 0 ;
		  }

		   DWORD WINAPI mcThreadProc_toShareVideo_post( LPVOID lpParameter )
		   {
			   return  0;
		   }



		  

 int  doPostEnc_mediaSdk(  void  *  pQDC_OBJ_INFO,  char  *  pInput,  unsigned  int  inputSize,  int  iSampleTimeInMs,  void  *  pBuf_pkt  )
 {
	 return  -1;
 }

  int  notifyCapEnd(  void  *  pQY_MC,  unsigned  int  uiCapType,  int  iIndex_capBmp,  int  iTaskId,  HWND  hWnd  )
  {
	  return  -1;
  }

  int  getMonikerProp(  void  *  pMonikerParam,  LPCTSTR  propName,  TCHAR  *  propVal,  int  propValCnt  )
  {
	  return  -1;
  }

   __declspec(  dllexport  )  void  exitAvRecord(  void  *  pCOMPRESS_VIDEO  )
   {
	   return;
   }

  int  getMonikerByDisplayName(  LPCTSTR  displayName,  void  **  ppMoniker  )
  {
	  return  -1;
  }


#if  10
   BOOL  bWebcamUsing(  void  *  pMC_VAR_isCli,  unsigned  int  uiCamCapType,  void  *  pMoniker_v,  LPCTSTR  camName,  int  *  piIndex_capBmp,  int  *  piIndex_sharedObj  )
   {
	   return  FALSE;
   }
#endif

    HRESULT  BufferCB_av(  void  *  pProcInfoParam,  int  iIndex_capProcInfo,  void  *  pSampleGrabberCbVar,  int  iSampleTimeInMs,  BYTE  *  pBuffer,  long  BufferLen  )
	{
		return  -1;
	}

	 int  initVideoCapDev_dx(  void  *  p_reserved,  LPCTSTR  displayName_selected,  void  **  ppCapStuff,  BITMAPINFOHEADER  *  pBih_suggested,  BOOL  bForConfig,  HWND hWnd_notify,  LONG_PTR lInstanceData,  void  **  ppVideoCapDevParam  )
	 {
		 return  -1;
	 }


	  int  exitVideoCapDev_dx(  void  **  ppVideoCapDevParam  )
	  {
		  return  -1;
	  }


	    BOOL  bGetCapturePara_dx(  void  *  pProcInfo,  int  iIndex_capBmp,  PF_BufferCB_av  pf,  unsigned  int  uiBufSize_pMsgBuf,  void  *  pVideoCapDevParam,  QY_VIDEO_HEADER  *  pVh_org  )
		{
			return  FALSE;
		}


		 int  startCapture_dx(  void  *  pVideoCapDevParam  )
		 {
			 return  -1;
		 }

		   int  stopCapture_dx(  void  *  pVideoCapDevParam  )
		   {
			   return  -1;
		   }

		     int  exitShareMediaFile(  void  **  ppShareMediaFileParam  )
			 {
				 return  -1;
			 }

			  int  exitShareMediaDevice(  void  **  ppShareMediaDeviceParam  )
			  {
				  return  -1;
			  }

			    int  initCompressVideo_dmo(  VIDEO_COMPRESSOR_CFG  *  pCompressor,  QY_VIDEO_HEADER  *  pVh_decompress,  QY_VIDEO_HEADER  *  pVh_compress,  MY_DMO_INFO  *  pDmoInfo  )
				{
					return  -1;
				}


				 int  exitCompressVideo_dmo(  MY_DMO_INFO  *  pDmoInfo  )
				 {
					 return  -1;
				 }


				 __declspec(  dllexport  ) int  refreshWebCamSettings(  VIDEO_COMPRESSOR_CFG  *  pVideoCompressorCfg,  CAP_procInfo_video  *  pVc  )
				 {
					 return  -1;
				 }


				 int  shareDynBmp_closeTaskAv(  SHARE_dyn_bmp  *  pDynBmpMem  )

				 {
					 return  -1;
				 }




				   int  getVal_bExists_taskInWnd(  int  iTaskId,  HWND  hWnd_task,  BOOL  *  pbExists  )
				   {
					   return  -1;
				   }

				    LRESULT  CALLBACK  iimyVideoCaptureProc(  HWND  mwnd,  LPVIDEOHDR  lphdr  )
					{
						return  -1;
					}



#if  0
  int  postVPktToSave(  unsigned  int  uiTransformType,  void  *  pQY_TRANSFORM,  int  index_pMems_from,  char  *  video,  int  len  )
  {
	  return  -1;
  }
#endif

int  chkFromPlayerIndex_v(  unsigned  int  uiTransformType,  void  *  pQY_TRANSFORM,  myDRAW_VIDEO_DATA  *  pPkt,  void  *  p2  )
{
	return  0;
}

  int  decompressVideo_dmo(  MY_DMO_INFO  *  pDmoInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput,  int  iSampleTimeInMs,  unsigned  int  ui_rtTimeLen  )
  {
	  return  -1;
  }


   int  decompressVideo_filterGraph(  MY_DMO_INFO  *  pDmoInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput,  int  iSampleTimeInMs,  unsigned  int  ui_rtTimeLen  )
   {
	   return  -1;
   }





 int  enc_parseOrgVPkt_i(  unsigned  int  uiTransformType,  void  *  pParent_transform,  void  *  pPkt_myDRAW_VIDEO_DATA,  long  *  p_old_lPktId_alloc,  unsigned  char  **  ppInput,  unsigned  int  *puiSize,  BOOL  *  pbNeed_forceKeyFrame  )
 {
	 return  -1;
 }

  BOOL  bSupported_sendVhDec(  )
  {
	  return  FALSE;
  }


   int  initDecompressVideo_dmo(  const  VIDEO_COMPRESSOR_CFG  *  pCompressor,  QY_VIDEO_HEADER  *  pVh_compress,  QY_VIDEO_HEADER  *  pVh_decompress,  MY_DEBUG_STEP  *  pDebugStep,  MY_DMO_INFO  *  pDmoInfo  )
   {
	   return  -1;
   }

    int  exitDecompressVideo_dmo(  MY_DMO_INFO  *  pDmoInfo  )
	{
		return  -1;
	}

 int  initDecompressVideo_filterGraph(  const  VIDEO_COMPRESSOR_CFG  *  pCompressor,  QY_VIDEO_HEADER  *  pVh_compress,  QY_VIDEO_HEADER  *  pVh_decompress,  MY_DEBUG_STEP  *  pDebugStep,  MY_DMO_INFO  *  pDmoInfo  )
 {
	 return -1;
 }

  int  exitDecompress_filterGraph(  MY_DMO_INFO  *  pDmoInfo,  MY_DEBUG_STEP  *  pDebugStep  )
  {
	  return  -1;
  }


  

   int  qvcf_doRecvRtsp(  void  *  pVIDEO_capDev_rtsp  )
   {
	   return  -1;
   }

int  exitQvcf_rtsp(  MC_VAR_common  *  pProcInfoCommon,  void  **  ppQvcfParam  )
{
	return  -1;
}

 int  runShareMediaDevice(  void  *  pShareMediaDeviceParam  )
 {
	 return  -1;
 }

 __declspec(dllexport)  int   set_g_dbPool_isCliHelp(  void  *  pPool  )
 {
	 return  -1;
 }

BOOL  tmp_bChkQyMcEnv_mis(  void  *  pQY_MC  )
{
	return  FALSE;
}


 BOOL  bObjDbAvail(  QY_OBJ_DB  *  pObj  )
 {
	 return  FALSE;
 }

//
  int  setModalWnd_func(  QY_MC  *  pQyMc,  HWND  hDlg,  BOOL  bFileDialog  )
  {
	  return  -1;
  }


  //
   int  enc_parseOrgAPkt_i(  unsigned  int  uiTransformType,  void  *  pParent_transform,  void  *  pPkt_myPLAY_AUDIO_DATA,  long  *  p_old_lPktId_getNewPkt,  unsigned  char  **  ppInput,  unsigned  int  *puiSize,  BOOL  *  pbNeed_forceKeyFrame  )
   {
	   return -1;
   }

   int  tmp_playLocalAudioData(  QDC_OBJ_INFO  *  pQdcObjInfo  )
   {
	   return  -1;
   }
   //
    int  doPostEnc_audio(  void  *  pQDC_OBJ_INFO,  char  *  pInput,  unsigned  int  inputSize,  int  iSampleTimeInMs,  unsigned  int  uiPts,  void  *  pBuf_pkt  )
	{
		return  -1;
	}




