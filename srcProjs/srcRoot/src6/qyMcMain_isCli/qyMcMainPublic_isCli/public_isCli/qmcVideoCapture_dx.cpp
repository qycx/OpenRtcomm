

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
#include	"myTChar.h"


//
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
#include	<dsound.h>

#include	"qmcDmoPublic.h"

#include	"qmcVideoCapture_dx.h"

#include	"myfourcc.h"
#include	"mywmcodecconst.h"

#include	"qmcCmdProc.h"

#include	"cPropertyBag.h"

#include	"qyCusResTemp.h"
#include	"qmcDirectX.h"

//  #include	"myresource.h"
#ifdef  __SUPPORT_CUS_sampleGrabber__
		#include	"qySampleGrabberPublic.h"
#endif

#include	"myresource.h"
#include	"qmcShareMediaDevice.h"




extern  HWND  ghwndApp;



int  printDmoMediaType(  int  index,  DMO_MEDIA_TYPE  *  pMt  );



HRESULT  CMySampleGrabberCB::SampleCB(  double  SampleTime,  IMediaSample  *  pSample  )
{
	return  S_OK;
}



#if  0
 HRESULT  BufferCB_qmCmd(  CMySampleGrabberCB  *  pObj,  int  iSampleTimeInMs,  BYTE  *  pBuffer,  long  BufferLen  )
{
	MC_VAR_qmCmd	*	pProcInfo	=	(  MC_VAR_qmCmd  *  )pObj->m_var.pProcInfo;
	QM_SHM_DATA		*	pShmData	=	(  QM_SHM_DATA  *  )pProcInfo->dataShm.pBuf;

	traceLogA(  (char*)  "BufferCB_qmCmd called"  );
	
	switch  (  pObj->m_var.uiCapType  )  {
		case  CONST_capType_av:  {
			  // qyShowInfo1(  CONST_qyShowType_debug,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "BufferCB_qmCmd: not finished uiCapType %d"  ),  pObj->m_var.uiCapType  );

			  #ifdef  __DEBUG__
					  //  traceLogA(  (char*)  "Grab: video data, len %d, SampleTime %d",  BufferLen, iSampleTimeInMs  );
					  if  (  1  )  {
						  TCHAR  buf[128];
						  DWORD	dwTickCnt  =  GetTickCount(  );
						  float  fRate;

						  if  (  pObj->m_var.iSampleTimeInMs  >  iSampleTimeInMs  )  {
							  pObj->m_var.iFrames  =  0;
							  pObj->m_var.firstTickCnt  =  0;
						  }
						  pObj->m_var.iSampleTimeInMs  =  iSampleTimeInMs;

						  pObj->m_var.iFrames  ++  ;
						  if  (  !pObj->m_var.firstTickCnt  )  {
							  pObj->m_var.firstTickCnt =  dwTickCnt;									  
						  }
						  if  (  dwTickCnt  !=  pObj->m_var.firstTickCnt  )  {
							  fRate  =  pObj->m_var.iFrames  *  1000.  /  (  dwTickCnt  -  pObj->m_var.firstTickCnt  );
							  if  (  !(  pObj->m_var.iFrames  %  60  )  )  {
								  _sntprintf(  buf,  sizeof(  buf  )  /  sizeof(  buf[0]  ),  _T(  "BufferCB called, fRate: %f fps\n"  ),  fRate  );
								  if (pProcInfo->cfg.debugStatusInfo.ucbDbgDetail) {
									  OutputDebugString(buf);
								  }
							  }
						  }
					  }
			  #endif
			

			  if  (  1  )  {
				  CAP_procInfo_video		*	pVc							=	&pProcInfo->vc;
				  BYTE						*	pInput						=	pBuffer;
				  BITMAPINFO				*	pBmpInfo_input				=	(  BITMAPINFO  *  )&pVc->vh_org.bih;
			
				  //
			      #ifdef  __DEBUG__
						  //  iFourcc2Str(  pProcInfo->av.bmpInfo_org.bmiHeader.biCompression,  0,  0  );
						  //  iFourcc2Str(  pProcInfo->av.bmpInfo_compress.bmiHeader.biCompression,  0,  0  );
				  #endif	
				  //
				  if  (  pVc->bOrg2RgbBufInited  )  {
					  if  (  org2Rgb(  (  MC_VAR_common  *  )pProcInfo,  (  CAP_procInfo_bmpCommon  *  )pVc,  pInput,  pVc->pOrg2RgbBuf  )  )  {			
						  traceLogA(  (char*)  "Video capture: org2Rgb failed."  );
						  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Video capture: Decompress failed"  )  );
						  goto  errLabel;
					  }
					  pInput  =  (  BYTE  *  )pVc->pOrg2RgbBuf;
					  pBmpInfo_input  =  (  BITMAPINFO  *  )&pVc->vh_rgb.bih;			
					  //  traceLogA(  (char*)  "doVideoCapture: bmp.sizeImage %d",  pVc->bmpInfo_rgb.bmiHeader.biSizeImage  );
				  }
				#if  0
				  if  (  pVc->iPicBufSize  )  {
					  if  (  pVc->policy.degreesToRotate  )  {
						  if  (  rotateRgb2Pic(  (  MC_VAR_common  *  )pProcInfo,  pVc,  pInput,  pVc->pPicBuf  )  )  {
							  traceLogA(  (char*)  "Video capture: rgb2Pic failed"  );
							  goto  errLabel;
						  }
					  }
					  pInput  =  (  BYTE  *  )pVc->pPicBuf;
					  pBmpInfo_input  =  (  BITMAPINFO  *  )&pVc->vh_pic;

					  //  2011/08/31
					  if  (  !pInput  )  {
						  #ifdef  __DEBUG__
								  traceLog((TCHAR*)  _T(  "BufferCB_qmCmd failed: pInput is null"  )  );
						  #endif
						  goto  errLabel;
					  }
				  }
				#endif
				  //
				  iSampleTimeInMs  =  timeGetTime(  );
				  pBuffer  =  pInput;
				  BufferLen  =  pBmpInfo_input->bmiHeader.biSizeImage;
				  //
				  if  (  pBmpInfo_input->bmiHeader.biCompression  !=  BI_RGB  )  {
					  traceLogA(  (char*)  "CMySampleGrabberCB::BufferCB failed: pBmpInfo_input is not rgb"  );
					  goto  errLabel;
				  }
				  //				  
				  if  (  BufferLen  !=  pShmData->v.nBytes_pktData  )  {					  	
					  qyShowInfo1(  CONST_qyShowType_debug,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "BufferCB_qmCmd: av, BufferLen != biSizeImage"  )  );
					  goto  errLabel;				  
				  }

					int	nCnt;
					int	iIndex_post;
					{	
						CQySyncObj	syncObj;
						if  (  syncObj.sync(  pProcInfo->v.mutexName_syncShmData  )  )  goto  errLabel;
						nCnt  =  pShmData->v.nCnt;
						iIndex_post  =  pShmData->v.iIndex_post;		  
					}
					if  (  nCnt  >=  pShmData->v.usMaxCnt  )  {
						SetEvent(  pProcInfo->v.hEvent_toSendData  );			//  2010/09/11
						qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "BufferCB_qmCmd failed: av, v.nCnt %d >=  usMaxCnt %d"  ),  nCnt,  pShmData->v.usMaxCnt  );
						goto  errLabel;
					}
					iIndex_post  =  (  iIndex_post  +  1  )  %  pShmData->v.usMaxCnt;

					char	*	pPkt  =  pShmData->buf  +  (  pShmData->a.nBytes_pktHead  +  pShmData->a.nBytes_pktData  )  *  pShmData->a.usMaxCnt  +  (  pShmData->v.nBytes_pktHead  +  pShmData->v.nBytes_pktData  )  *  iIndex_post;
					QM_SHM_pktHead  *  pPktHead  =  (  QM_SHM_pktHead  *  )pPkt;
					pPktHead->iSampleTimeInMs  =  iSampleTimeInMs;
				    #ifdef  __DEBUG__
							//  _sntprintf(  pPktHead->tHint,  mycountof(  pPktHead->tHint  ),  _T(  "Hello, iSampleTimeInMs %d"  ),  iSampleTimeInMs  );
					#endif
					memcpy(  pPkt  +  pShmData->v.nBytes_pktHead,  pBuffer,  BufferLen  );

					{
						CQySyncObj	syncObj;
						if  (  !syncObj.sync(  pProcInfo->v.mutexName_syncShmData  )  )  {
							pShmData->v.nCnt  ++  ;
							pShmData->v.iIndex_post  =  iIndex_post;
						}
					}		  

					SetEvent(  pProcInfo->v.hEvent_toSendData  );
			  }

			  }
			  break;
		case  CONST_capType_mediaFile:
			  if  (  pObj->m_var.bAudio  )  {
				  //  qyShowInfo1(  CONST_qyShowType_debug,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "BufferCB_qmCmd: audio"  )  );

				  QM_SHM_CMD	*	pShmCmd  =  getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  pProcInfo->iIndex_shmCmd  );
				  if  (  !pShmCmd  )  goto  errLabel;

				  if  (  pShmCmd->bGlobalMute  )  break;

				  int	nCnt;
				  int	iIndex_post;
				  {	
					  CQySyncObj	syncObj;
					  if  (  syncObj.sync(  pProcInfo->a.mutexName_syncShmData  )  )  goto  errLabel;
					  nCnt  =  pShmData->a.nCnt;
					  iIndex_post  =  pShmData->a.iIndex_post;		  
				  }		 
				  if  (  nCnt  >=  pShmData->a.usMaxCnt  )  {	
					  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "BufferCB_qmCmd failed: a.nCnt %d >=  usMaxCnt %d"  ),  nCnt,  pShmData->a.usMaxCnt  );
					  goto  errLabel;
				  }
				  if  (  !pObj->m_var.cache.nBytes_pkt  )  goto  errLabel;
				  int  nCnt_new  =  BufferLen  /  pObj->m_var.cache.nBytes_pkt;
				  if  (  nCnt_new  +  nCnt  >  pShmData->a.usMaxCnt  )  {
					  SetEvent(  pProcInfo->a.hEvent_toSendData  );		//  2010/09/11
					  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "BufferCB_qmCmd failed: nCnt_new %d + a.nCnt %d >  usMaxCnt %d"  ),  nCnt_new,  nCnt,  pShmData->a.usMaxCnt  );
					  goto  errLabel;
				  }
				  int  i;
				  for  (  i  =  0;  i  <  nCnt_new;  i  ++  )  {
					   iIndex_post  =  (  iIndex_post  +  1  )  %  pShmData->a.usMaxCnt;
	
					   char	*	pPkt  =  pShmData->buf  +  (  pShmData->a.nBytes_pktHead  +  pShmData->a.nBytes_pktData  )  *  iIndex_post;
					   QM_SHM_pktHead  *  pPktHead  =  (  QM_SHM_pktHead  *  )pPkt;
					   pPktHead->iSampleTimeInMs  =  iSampleTimeInMs  +  i  *  pShmData->a.nBytes_pktData  *  1000  /  pObj->m_var.cache.nAvgBytesPerSec;
					   #ifdef  __DEBUG__
							   //  _sntprintf(  pPktHead->tHint,  mycountof(  pPktHead->tHint  ),  _T(  "Hello, iSampleTimeInMs %d"  ),  iSampleTimeInMs  );
					   #endif
					   memcpy(  pPkt  +  pShmData->a.nBytes_pktHead,  pBuffer  +  i  *  pObj->m_var.cache.nBytes_pkt,  pObj->m_var.cache.nBytes_pkt  );
				  }
				  {
					  CQySyncObj	syncObj;
					  if  (  !syncObj.sync(  pProcInfo->a.mutexName_syncShmData  )  )  {
						  pShmData->a.nCnt  +=  nCnt_new  ;
						  pShmData->a.iIndex_post  =  iIndex_post;
					  }
				  }		  

				  SetEvent(  pProcInfo->a.hEvent_toSendData  );
				  }	
			  else  {
				    //  qyShowInfo1(  CONST_qyShowType_debug,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "BufferCB_qmCmd: video"  )  );
				    #ifdef  __DEBUG__
						    //  traceLogA(  (char*)  "Grab: video data, len %d, SampleTime %d",  BufferLen, iSampleTimeInMs  );

							if  (  1  )  {		
								TCHAR  buf[128];
								DWORD	dwTickCnt  =  GetTickCount(  );
								float  fRate;

								if  (  pObj->m_var.iSampleTimeInMs  >  iSampleTimeInMs  )  {
									pObj->m_var.iFrames  =  0;
									pObj->m_var.firstTickCnt  =  0;
								}
								pObj->m_var.iSampleTimeInMs  =  iSampleTimeInMs;

								pObj->m_var.iFrames  ++  ;
								if  (  !pObj->m_var.firstTickCnt  )  {
									pObj->m_var.firstTickCnt =  dwTickCnt;									  						  
								}
								if  (  dwTickCnt  !=  pObj->m_var.firstTickCnt  )  {
									fRate  =  pObj->m_var.iFrames  *  1000.  /  (  dwTickCnt  -  pObj->m_var.firstTickCnt  );
									if  (  !(  pObj->m_var.iFrames  %  60  )  )  {
										_sntprintf(  buf,  sizeof(  buf  )  /  sizeof(  buf[0]  ),  _T(  "BufferCB called, fRate: %f fps\n"  ),  fRate  );
										if (pProcInfo->cfg.debugStatusInfo.ucbDbgDetail) {
											OutputDebugString(buf);
										}
									}
								}
							}
				    #endif
			  
					if  (  BufferLen  !=  pShmData->v.nBytes_pktData  )  {					  	
						qyShowInfo1(  CONST_qyShowType_debug,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "BufferCB_qmCmd: BufferLen != biSizeImage"  )  );
						goto  errLabel;				  
					}

					int	nCnt;
					int	iIndex_post;
					{	
						CQySyncObj	syncObj;
						if  (  syncObj.sync(  pProcInfo->v.mutexName_syncShmData  )  )  goto  errLabel;
						nCnt  =  pShmData->v.nCnt;
						iIndex_post  =  pShmData->v.iIndex_post;		  
					}
					if  (  nCnt  >=  pShmData->v.usMaxCnt  )  {
						SetEvent(  pProcInfo->v.hEvent_toSendData  );		//  2010/09/11
						qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "BufferCB_qmCmd failed: v.nCnt %d >=  usMaxCnt %d"  ),  nCnt,  pShmData->v.usMaxCnt  );
						goto  errLabel;
					}
					iIndex_post  =  (  iIndex_post  +  1  )  %  pShmData->v.usMaxCnt;

					char	*	pPkt  =  pShmData->buf  +  (  pShmData->a.nBytes_pktHead  +  pShmData->a.nBytes_pktData  )  *  pShmData->a.usMaxCnt  +  (  pShmData->v.nBytes_pktHead  +  pShmData->v.nBytes_pktData  )  *  iIndex_post;
					QM_SHM_pktHead  *  pPktHead  =  (  QM_SHM_pktHead  *  )pPkt;
					pPktHead->iSampleTimeInMs  =  iSampleTimeInMs;
				    #ifdef  __DEBUG__
							//  _sntprintf(  pPktHead->tHint,  mycountof(  pPktHead->tHint  ),  _T(  "Hello, iSampleTimeInMs %d"  ),  iSampleTimeInMs  );
					#endif
					memcpy(  pPkt  +  pShmData->v.nBytes_pktHead,  pBuffer,  BufferLen  );

					{
						CQySyncObj	syncObj;
						if  (  !syncObj.sync(  pProcInfo->v.mutexName_syncShmData  )  )  {
							pShmData->v.nCnt  ++  ;
							pShmData->v.iIndex_post  =  iIndex_post;
						}
					}		  

					SetEvent(  pProcInfo->v.hEvent_toSendData  );
			  }
			  break;			  
		default:							  
			    qyShowInfo1(  CONST_qyShowType_debug,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "BufferCB_qmCmd: unknown uiCapType %d"  ),  pObj->m_var.uiCapType  );
				break;				
		}


errLabel:
	return  S_OK;
}
#endif


/////////





 //  2011/12/04
 HRESULT  BufferCB_av(  void  *  pProcInfoParam,  int  iIndex_capProcInfo,  void  *  pSampleGrabberCbVar,  int  iSampleTimeInMs,  BYTE  *  pBuffer,  long  BufferLen  )
{
	HRESULT						hr					=	-1;
	MC_VAR_isCli			*	pProcInfo			=	(  MC_VAR_isCli  *  )pProcInfoParam;
	QY_SHARED_OBJ			*	pSharedObj			=	NULL;

	if  (  !pSampleGrabberCbVar  )  return  -1;
	SAMPLE_grabberCb_var  &  m_var					=	*(  SAMPLE_grabberCb_var  *  )pSampleGrabberCbVar;

	CQyMalloc					mallocObj;
	//  CAP_procInfo_video	*	pVc;
	CAP_procInfo_bmpCommon	*	pVc;

	pVc				=	(  CAP_procInfo_bmpCommon  *  )getCapBmpBySth(  pProcInfo,  iIndex_capProcInfo,  0  );
	if  (  !pVc  )  goto  errLabel;
	pSharedObj			=	getSharedObjByIndex(  pProcInfo,  pVc->iIndex_sharedObj  );		//  ÕâÀïÒªÓÃindexÀ´»ñÈ¡
	if  (  !pSharedObj  )  goto  errLabel;


	//
	#ifdef  __DEBUG__
			//  traceLogA(  (char*)  "Grab: video data, len %d, SampleTime %d",  BufferLen, iSampleTimeInMs  );
			//
			char fourcc_org[5];
			iFourcc2Str(pVc->vh_org.bih.biCompression, fourcc_org, mycountof(fourcc_org));

			if  (  1  )  {

				TCHAR  buf[128];
				DWORD	dwTickCnt  =  GetTickCount(  );
				float  fRate;

				if  (  m_var.iSampleTimeInMs  >  iSampleTimeInMs  )  {
					m_var.iFrames  =  0;
					m_var.firstTickCnt  =  0;
				}
				m_var.iSampleTimeInMs  =  iSampleTimeInMs;

				m_var.iFrames  ++  ;
				if  (  !m_var.firstTickCnt  )  {
					m_var.firstTickCnt =  dwTickCnt;									  
				}
				if  (  dwTickCnt  !=  m_var.firstTickCnt  )  {
					fRate  =  m_var.iFrames  *  1000.  /  (  dwTickCnt  -  m_var.firstTickCnt  );
					if  (  !(  m_var.iFrames  %  600  )  )  {
						_sntprintf(  buf,  sizeof(  buf  )  /  sizeof(  buf[0]  ),  _T(  "BufferCB called, fRate: %f fps\n"  ),  fRate  );
						if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
							OutputDebugString(buf);
						}
					}
				}
			}
	#endif

		//  
		#if  0  //  def  __WINCE__
				if  (  pProcInfo->hWnd_testWebcam  !=  pSharedObj->hWnd_starter  )  {
					//  for winCe, localVideo don't need to be displayed
					goto  errLabel;
				}
		#endif

		//
				CAP_procInfo_bmpCommon* pCapProcInfo; pCapProcInfo = pVc;
		myDRAW_VIDEO_DATA	*	p;
		int						len;

		//  len  =  offsetof(  myDRAW_VIDEO_DATA,  buf  )  +  pCapProcInfo->vh_org.bih.biSizeImage;
		len  =  sizeof(  myDRAW_VIDEO_DATA  );
#if  0
		if  (  len  >  m_var.uiBufSize_pBuf  ||  !m_var.pBuf  )  {
			showNotification(  NULL,  0,  0,  0,  0,  0,  _T(  "pBuf is null or buf too small, need allocated in bGetCapturePara(  ) first"  )  );
			traceLog((TCHAR*)  _T(  "pBuf is null or buf too small, need allocated in bGetCapturePara(  ) first"  )  );
			goto  errLabel;
		}
#endif
		myDRAW_VIDEO_DATA	tmp_myDRAW_VIDEO_DATA;
		p  =  &tmp_myDRAW_VIDEO_DATA;	//  (  myDRAW_VIDEO_DATA  *  )m_var.pBuf;
		if  (  !p  )  goto  errLabel;
		memset(  p,  0,  sizeof(  myDRAW_VIDEO_DATA  )  );	//  memset(  p,  0,  m_var.uiBufSize_pBuf  );
#if  0	//  def  __DEBUG__
		if  (  m_var.uiBufSize_pBuf  !=  sizeof(  myDRAW_VIDEO_DATA  )  )  {
			traceLog((TCHAR*)  _T(  "BufferCB_av, uiBufSize_pBuf is not correct"  )  );
			goto  errLabel;
		}
#endif

		//
#ifdef  __DEBUG__
		safeTcsnCpy(  _T(  "BuffCB_av: "  ),  pVc->compressVideo.input_BufferCB.videoInputInfo.tBuf,  mycountof(  pVc->compressVideo.input_BufferCB.videoInputInfo.tBuf  )  );
#endif
		TCHAR  tBuf[128];
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "sharedObj[%d].BufferCB_av"  ),  pVc->iIndex_sharedObj  );
		//
		if  (  setPktInputInfo(  pProcInfo,  &pVc->compressVideo.input_BufferCB,  pVc->compressVideo.usFrames_perSecond_expected,  FALSE,  p,  mynull,tBuf  )  )  {
			#ifdef  __DEBUG__
					//  traceLog((TCHAR*)  _T(  "BufferCB_av: setPktInputInfo failed, skipped"  )  );
			#endif
			goto  errLabel;
		}
		//
		BYTE* pInput; pInput = pBuffer;
		BITMAPINFO* pBmpInfo_input; pBmpInfo_input = (BITMAPINFO*)&pVc->vh_org.bih;
		//
		unsigned  int  uiSize_dec; uiSize_dec = max(pVc->vh_org.bih.biSizeImage, BufferLen);
		if  (  pVc->bOrg2RgbBufInited  )  uiSize_dec  =  max(  uiSize_dec,  pVc->vh_rgb.bih.biSizeImage  );
		//

		//  if  (  pVc->iPicBufSize  )  uiSize_dec  =  max(  uiSize_dec,  pVc->vh_pic.bih.biSizeImage  );
		//  2013/10/06
		//  uiSize_dec  =  max(  uiSize_dec,  M_sizeImage(  32,  pVc->vh_org.bih.biWidth,  pVc->vh_org.bih.biHeight  )  );

		//  2011/12/06
		unsigned  int  uiSize_enc; uiSize_enc = sizeof(TRANSFER_VIDEO_DATA);

		//
		p->head.uiLen  =  uiSize_dec  +  uiSize_enc;		//  pBmpInfo_input->bmiHeader.biSizeImage;	
		p->head.uiSampleTimeInMs  =  iSampleTimeInMs;
		//
		p->uiSize_dec  =  uiSize_dec;
		//
		if  (  !mallocObj.mallocf(  CONST_iAllocType_video,  uiSize_dec  +  uiSize_enc  )  )  goto  errLabel;
		if  (  mallocObj.get(  &p->memory  )  )  goto  errLabel;

	    //  2011/12/04
		memcpy(  &p->bih,  &pVc->vh_org.bih,  sizeof(  p->bih  )  );
		//
		if  (  p->bih.biCompression  ==  CONST_fourcc_MJPG  )  {
			p->bih.biSizeImage  =  BufferLen;
		}
		//
		memcpy(  p->memory.m_pBuf,  pBuffer,  BufferLen  );  

#if  0	//  在doEncVideo里有清0 
		TRANSFER_VIDEO_DATA  *  pReq  =  (  TRANSFER_VIDEO_DATA  *  )(  p->memory.m_pBuf  +  p->uiSize_dec  );
		memset(  pReq,  0,  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  );
#endif

	    #if  1
			 p->debugInfo.dwTickCnt_start  =  GetTickCount(  );
			 M_pkt_setNo(  m_var.tn_pktNo,  m_var.lLastPktNo,  *p  );
		#endif
		//
		//M_set_pktId_alloc(  p  );
		p->lPktId_alloc = getuiNextTranNo(0, 0, &pSharedObj->last_lPktId_alloc);


#ifdef  __DEBUG__
				 if  (  !p->input.tStartTran  )  {
					 traceLog((TCHAR*)  _T(  "kk"  )  );
				 }
				 //
				 if (pProcInfo->cfg.debugStatusInfo.ucbPrint_lPktId_alloc) {
					 _sntprintf(tBuf, mycountof(tBuf), _T("BufferCB_av: p.lAlloc %d"), p->lPktId_alloc);
					 showInfo_open(0, 0, 0, tBuf);
				 }

#endif


		//
		if  (  q2PostMsgAndTrigger(  p,  len,  &pCapProcInfo->vppThread.q2,  _T(  "BufferCB_av"  )))  goto  errLabel;
		mallocObj.detach(    );

	

	hr  =  S_OK;

errLabel:
		
	return  hr;
}


//



///////////

 HRESULT  CMySampleGrabberCB::BufferCB(  double  SampleTime1,  BYTE  *  pBuffer,  long  BufferLen  )
{
	int						iErr				=	-1;
	int						iSampleTimeInMs		=  (  int  )(  SampleTime1  *  1000  );
	QY_SHARED_OBJ		*	pSharedObj			=	NULL;
	//QM_SHM_CMD			*	pShmCmd				=	NULL;
	BOOL					bCached				=	FALSE;

	//
	if  (  !m_var.pProcInfo  )  {
		#ifdef  __DEBUG__
				traceLogA(  (char*)  "CMySampleGrabberCB::BufferCB error, pProcInfo is null,  BufferLen %d",  BufferLen  );  
		#endif
		//
		showInfo_open0(  0,  0,  _T(  "BufferCB failed, m_var.pProcInfo is null"  )  );
		//
		return  -1;
	}
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	(  MC_VAR_isCli  *  )m_var.pProcInfo;


	//  20170821
#ifdef  __DEBUG__
		#if  0
			 //  for test
			 static  int  ii  =  0;  ii  ++  ;
			 unsigned  int  kk  =  0xefffffff;
			 iSampleTimeInMs  =  kk  -  33  *  ii;  
		#endif
#endif
			 
	//
	if  (  !m_var.bAudio  )  {
		  //
		  if  (  pProcInfo->cfg.debugStatusInfo.ucbShowVideoCapStatus  )  {			
			  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "VideoCap: org %d."  ),  iSampleTimeInMs  );
		  }
	}


	//
#if  0  //  2017/08/21
	if  (  iSampleTimeInMs  <  0  )  {
		traceLog((TCHAR*)  _T(  "BufferCB failed, iSampleTimeInMs %d < 0"  ),  iSampleTimeInMs  );
		return  -1;
	}
#endif

	//
	if  (  m_var.cache.nBytes_pkt  )  {
		if  (  !m_var.cache.pBuf  )  {
			m_var.cache.pBuf  =  (  BYTE  *  )mymalloc(  m_var.cache.uiBufSize  );
			if  (  !m_var.cache.pBuf  )  goto  errLabel;
		}
		int	iSampleTimeInMs_left;
		iSampleTimeInMs_left  =  iSampleTimeInMs  -  m_var.cache.nLeft  *  1000  /  m_var.cache.nAvgBytesPerSec;
		if  (  abs(  iSampleTimeInMs_left  -  m_var.cache.iSampleTimeInMs_left  )  >  40  )  {
			#ifdef  __DEBUG__
					traceLogA(  (char*)  "GrabberCB: iSampleTime_left not matched, skip data left"  );
			#endif
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "GrabberCB: iSampleTime_left not matched, skip data left"  )  );
			m_var.cache.nLeft  =  0;
			iSampleTimeInMs_left  =  iSampleTimeInMs;			
		}
		if  (  m_var.cache.nLeft  +  BufferLen  <  m_var.cache.uiBufSize  )  {
			memcpy(  m_var.cache.pBuf  +  m_var.cache.nLeft,  pBuffer,  BufferLen  );
			m_var.cache.nLeft  +=  BufferLen;
			m_var.cache.iSampleTimeInMs_left  =  iSampleTimeInMs_left;
			}
		else  {
			  if  (  !m_var.cache.nLeft  )  {
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "GrabberCB failed: BufferLen too large"  )  );	
				  goto  errLabel;
			  }
			  #ifdef  __DEBUG__
					  traceLogA(  (char*)  (  "GrabberCB error: BufferLen too large to chche, skipped"  )  );			
			  #endif
			  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "GrabberCB error: BufferLen too large to chche, skipped"  )  );	
		}
		//
		//  traceLogA(  (char*)  "BufferCB: iSampleTimeInMs %d, BufferLen %d, cache.iSampleTimeInMs %d, nLeft %d",  iSampleTimeInMs,  BufferLen,  m_var.cache.iSampleTimeInMs_left,  m_var.cache.nLeft  );  
		//
		iSampleTimeInMs  =  m_var.cache.iSampleTimeInMs_left;
		pBuffer  =  m_var.cache.pBuf;
		BufferLen  =  m_var.cache.nLeft  /  m_var.cache.nBytes_pkt  *  m_var.cache.nBytes_pkt;	
		//  traceLogA(  (char*)  "BufferLen is %d",  BufferLen  );
		if  (  !BufferLen  )  {			
			iErr  =  0;  goto  errLabel;
		}	
		bCached  =  TRUE;
	}



	#ifdef  __DEBUG__
			#if  0
				if  (  m_var.bAudio  )  {
					if  (  pProcInfo->cfg.debugStatusInfo.ucbPrintDataFlow_a  )  {
						traceLog((TCHAR*)  _T(  "BufferCB: a, SampleTime %d,  len %d"  ),  iSampleTimeInMs,  BufferLen  );
					}
					}
				else  {
					  if  (  pProcInfo->cfg.debugStatusInfo.ucbPrintDataFlow_v  )  {
						  traceLog((TCHAR*)  _T(  "BufferCB: v, SampleTime %d,  len %d"  ),  iSampleTimeInMs,  BufferLen  );
					  }
				}
			#endif
	#endif


	//  2012/11/11. 把时间戳调整到自己的方式
				int	 iSampleTimeInMs_org; iSampleTimeInMs_org = iSampleTimeInMs;
				int	 iVal_timeGetTime; iVal_timeGetTime = myGetTickCount(mynull);// timeGetTime();
				int  nDataInMs; nDataInMs = 0;
	int	 iSampleTimeInMs_tmp; iSampleTimeInMs_tmp = 0;
	int  iMinDelayInMs; iMinDelayInMs = 100;	//  300;


	if  (  m_var.bAudio  )  {  
		//  先看音频
		CAP_procInfo_audioCommon  *  pCapAudio  =  (  CAP_procInfo_audioCommon  *  )getCapAudioBySth(  pProcInfo,  m_var.iIndex_capProcInfo,  0  );
		if  (  !pCapAudio  )  {
			#ifdef  __DEBUG__
					traceLogA(  (char*)  "CMySampleGrabberCB::BufferCB failed: pCapAudio is null"  );
			#endif
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "BufferCB failed: pCapAudio is null"  )  );
			goto  errLabel;
		}
		if  (  !pCapAudio->wf_org.nAvgBytesPerSec  )  {
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "BufferCB failed: wf_org.nAvgBytesPerSec is 0"  )  );
			goto  errLabel;
		}
		nDataInMs  =  (  BufferLen  *  1000  )  /  pCapAudio->wf_org.nAvgBytesPerSec;

		int  kk  =  0;
		//  
		if  (  !iSampleTimeInMs  )  iSampleTimeInMs  =  iVal_timeGetTime  -  nDataInMs;
		else  {
			  kk   =  m_var.iSampleTimeInMs_org_expected  -  iSampleTimeInMs_org;
			  if  (  abs(  kk  )  <  4  )  {	//  表明是正常的数据流
				  iSampleTimeInMs  =  iSampleTimeInMs_org  -  m_var.iSampleTimeInMs_org_start  +  m_var.iSampleTimeInMs_start;
				  }
			  else  {
				    m_var.iSampleTimeInMs_org_start  =  iSampleTimeInMs_org;
					m_var.iSampleTimeInMs_start  =  iVal_timeGetTime  -  nDataInMs;
					//
					iSampleTimeInMs  =  m_var.iSampleTimeInMs_start;	
					//
					#ifdef  __DEBUG__  //  2014/05/04
							traceLog((TCHAR*)  _T(  "BufferCB::audio, st_start adjusted. kk too big"  )  );
					#endif
			  }	   
		}
		//
		iSampleTimeInMs_tmp  =  iSampleTimeInMs;
		//
		if  (  abs(  iSampleTimeInMs  -  iVal_timeGetTime  )  >  iMinDelayInMs  
			||  iSampleTimeInMs  <  m_var.iSampleTimeInMs_last  ) 
		{		
			//   如果数据严重不符,就需要重置时间戳. 这里的abs表明要求声音的播放时间跟当前时间比较接近	
			//
			#ifdef  __DEBUG__  //  2014/05/04
					traceLog((TCHAR*)  _T(  "BufferCB::audio, st_start adjusted. >minDelay or s<last"  )  );
			#endif

			//
			m_var.iSampleTimeInMs_org_start  =  iSampleTimeInMs_org;
			m_var.iSampleTimeInMs_start  =  iVal_timeGetTime;
			//
			iSampleTimeInMs  =  m_var.iSampleTimeInMs_start;						
			//
		}
		//
		m_var.iSampleTimeInMs_org_expected  =  iSampleTimeInMs_org  +  nDataInMs;
		//
		pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pCapAudio->iIndex_sharedObj  );			
		if  (  !pSharedObj  )  goto  errLabel;
		//
		pSharedObj->syncAv.iSampleTimeInMs_org_start  =  m_var.iSampleTimeInMs_org_start;
		pSharedObj->syncAv.iSampleTimeInMs_start  =  m_var.iSampleTimeInMs_start;

		//  2012/11/11			
		if  (  pProcInfo->cfg.debugStatusInfo.ucbShowAudioCapStatus  )  {					
			  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "AudioCap: org %d, iD_org %d, tmp %d, ST %d, iD %d, cur %d. kk %d"  ),  iSampleTimeInMs_org,  iSampleTimeInMs_org  -  m_var.iSampleTimeInMs_org_last,  iSampleTimeInMs_tmp,  iSampleTimeInMs,  iSampleTimeInMs  -  m_var.iSampleTimeInMs_last,  iVal_timeGetTime,  kk  );
		}  

		}
	else  {  //  视频的事件戳调整
		  CAP_procInfo_bmpU  *  pCapProcInfo  =  getCapBmpBySth(  pProcInfo,  m_var.iIndex_capProcInfo,  0  );		
		  if  (  !pCapProcInfo  )  {
			  #ifdef  __DEBUG__
					  traceLogA(  (char*)  "CMySampleGrabberCB::BufferCB failed: pCapProcInfo is null"  );
			  #endif
			  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "BufferCB failed: pCapBmp is null"  )  );
			  goto  errLabel;
		  }
		  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pCapProcInfo->common.iIndex_sharedObj  );			
		  if  (  !pSharedObj  )  goto  errLabel;

		  //  2017/09/13
		  pCapProcInfo->common.dwTickCnt_lastVideoGot  =  GetTickCount(  );
		  
		  //
		  if  (  pSharedObj->syncAv.iSampleTimeInMs_start  )  {	//  靠音频来同步
			  if  (  m_var.iSampleTimeInMs_org_start  !=  pSharedObj->syncAv.iSampleTimeInMs_org_start
				  ||  m_var.iSampleTimeInMs_start  !=  pSharedObj->syncAv.iSampleTimeInMs_start  )
			  {
				  //
				  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "BufferCB: video, st_start adjusted. !=syncAv"  )  );
				  #endif
				  //
				  m_var.iSampleTimeInMs_org_start  =  pSharedObj->syncAv.iSampleTimeInMs_org_start;
				  m_var.iSampleTimeInMs_start  =  pSharedObj->syncAv.iSampleTimeInMs_start;
			  }
			  //
			  iSampleTimeInMs  =  iSampleTimeInMs_org  -  m_var.iSampleTimeInMs_org_start  +  m_var.iSampleTimeInMs_start;
			  //
			  iMinDelayInMs  =  200;	//  400;
			  }
		  else  {
			    if  (  !iSampleTimeInMs  )  iSampleTimeInMs  =  iVal_timeGetTime;
				else  {
					  iSampleTimeInMs  =  iSampleTimeInMs_org  -  m_var.iSampleTimeInMs_org_start  +  m_var.iSampleTimeInMs_start;
				}
				//
				iMinDelayInMs  =  100;
		  }
		  //
		  iSampleTimeInMs_tmp  =  iSampleTimeInMs;
		  //		  	
		  int  kk;
		  //
		  if  (  iSampleTimeInMs  <  m_var.iSampleTimeInMs_last  )  {
			  kk  =  iSampleTimeInMs_org  -  m_var.iSampleTimeInMs_org_last;
			  if  (  kk  >  40  )  kk  =  40;
			  iSampleTimeInMs  =  m_var.iSampleTimeInMs_last  +  kk;	//  1;
		  }
		  kk  =  iSampleTimeInMs  -  iVal_timeGetTime;
		  if  (  abs(  kk  )  >  iMinDelayInMs  )
		  {		
			  //   如果数据严重不符,就需要重置时间戳. 这里表明只有在当前时间之后很久播放的视频需要重新调整. (之前播放的不需要调整)						
			  #ifdef  __DEBUG__
					  traceLog((TCHAR*)  _T(  "BufferCB: video, st_start adjusted, kk %d >minDelay"  ),  kk  );
			  #endif
			  //
			  m_var.iSampleTimeInMs_org_start  =  iSampleTimeInMs_org;
			  m_var.iSampleTimeInMs_start  =  iVal_timeGetTime;
			  //
			  iSampleTimeInMs  =  m_var.iSampleTimeInMs_start;						
		  }
		  
		  //
		  if  (  pProcInfo->cfg.debugStatusInfo.ucbShowVideoCapStatus  )  {			
			  TCHAR  tBuf[128];
			  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "CMySampleGrab.BufferCB, org %d, iDiff_org %d, tmp %d, ST %d, iDiff %d. cur %d. len %d"  ),  iSampleTimeInMs_org,  iSampleTimeInMs_org  -  m_var.iSampleTimeInMs_org_last,  iSampleTimeInMs_tmp,  iSampleTimeInMs,  iSampleTimeInMs  -  m_var.iSampleTimeInMs_last,  iVal_timeGetTime,  BufferLen  );
			  showInfo_open0(  0,  0,  tBuf  );
		  }

	}
	m_var.iSampleTimeInMs_org_last  =  iSampleTimeInMs_org;		
	m_var.iSampleTimeInMs_last  =  iSampleTimeInMs;



	//
	switch  (  m_var.uiCapType  )  {
			#if  10
			case  CONST_capType_av:  {
			
				  if  (  m_var.bAudio  )  {
					  //  processInput_post(  pProcInfo,  0,  (  BYTE  *  )pBuffer,  BufferLen,  (  MIS_MSGU  *  )m_var.pMsgBuf  );				    
					  traceLog((TCHAR*)  _T(  "Not supported"  )  );
					  goto  errLabel;
					  }
				  else  {
					    BufferCB_av(  pProcInfo,  m_var.iIndex_capProcInfo,  &m_var,  iSampleTimeInMs,  pBuffer,  BufferLen  );
				  }

				  }
				  break;
			#endif
			//  case  CONST_capType_av:
			case  CONST_capType_mediaDevice:  {

				  #ifdef  __DEBUG__
						  if  (  m_var.uiCapType  ==  CONST_capType_av  )  {
							  if  (  m_var.bAudio  )  {
								  traceLog((TCHAR*)  _T(  "kk"  )  );
							  }
						  }

				  #endif

				  if  (  !m_var.bAudio  )  {
					  BufferCB_av(  pProcInfo,  m_var.iIndex_capProcInfo,  &m_var,  iSampleTimeInMs,  pBuffer,  BufferLen  );
					  }
				  else  {
					    CQyMalloc				mallocObj;
					    //  CAP_procInfo_mediaDeviceAudio  *  pCapAudio  =  (  CAP_procInfo_mediaDeviceAudio  *  )getCapAudioBySth(  pProcInfo,  m_var.iIndex_capProcInfo,  0  );
						CAP_procInfo_audioCommon  *  pCapAudio  =  (  CAP_procInfo_audioCommon  *  )getCapAudioBySth(  pProcInfo,  m_var.iIndex_capProcInfo,  0  );
						if  (  !pCapAudio  )  {
							traceLogA(  (char*)  "CMySampleGrabberCB::BufferCB failed: pCapAudio is null"  );
							goto  errLabel;
						}
						pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pCapAudio->iIndex_sharedObj  );
						if  (  !pSharedObj  )  goto  errLabel;
						
#if  0
						pShmCmd  =  getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  pSharedObj->iIndex_shmCmd  );
						if  (  !pShmCmd  )  goto  errLabel;
#endif


						//
						//  if  (  pSharedObj->psCurrent  !=  State_Running  )  break;

						//if  (  !pShmCmd->bGlobalMute  )  
						{

							//
							myPLAY_AUDIO_DATA		*	p;
							int							len;
							//  len  =  offsetof(  myPLAY_AUDIO_DATA,  buf  )  +  BufferLen;
							len  =  sizeof(  myPLAY_AUDIO_DATA  );
						#if  0
							if  (  len  >  m_var.uiBufSize_pBuf  )  {
								MACRO_safeFree(  m_var.pBuf  );
								m_var.uiBufSize_pBuf  =  0;
								//
								m_var.pBuf  =  (  BYTE  *  )mymalloc(  len  );
								if  (  !m_var.pBuf  )  goto  errLabel;
								m_var.uiBufSize_pBuf  =  len;
							}
						#endif
							myPLAY_AUDIO_DATA	tmp_myPLAY_AUDIO_DATA;
							p  =  &tmp_myPLAY_AUDIO_DATA;	//  (  myPLAY_AUDIO_DATA  *  )m_var.pBuf;
							if  (  !p  )  goto  errLabel;
							memset(  p,  0,  sizeof(  myPLAY_AUDIO_DATA  )  );
							//
							//  2016/12/10			
							unsigned  int  uiSize_dec  =  BufferLen;					
							//  2011/12/06					
							unsigned  int  uiSize_enc  =  sizeof(  TRANSFER_AUDIO_DATA  );

							//p->head.uiLen  =  BufferLen;
							p->head.uiLen  =  uiSize_dec  +  uiSize_enc;	//  2016/12/10			
							p->uiSize_dec  =  uiSize_dec;					//  2016/12/10

							//
							p->head.uiSampleTimeInMs  =  iSampleTimeInMs;						
							//  
						#if  0
							p->pBuf  =  mallocObj.malloc(  p->head.uiLen  );
							if  (  !p->pBuf  )  goto  errLabel;
						#else
							if  (  !mallocObj.mallocf(  p->head.uiLen  )  )  goto  errLabel;
							if  (  mallocObj.get(  &p->memory  )  )  goto  errLabel;
						#endif
							memcpy(  p->memory.m_pBuf,  pBuffer,  p->uiSize_dec  );  //  p->head.uiLen  );

							if  (  q2PostMsgAndTrigger(  p,  len,  &pCapAudio->thread.q2,  _T(  "grab.BufferCB"  )))  goto  errLabel;
							mallocObj.detach(    );

							//
					#if  0
							if  (  m_var.cache.nBytes_pkt  )  {
								m_var.cache.iSampleTimeInMs_left  +=  BufferLen  *  1000  /  m_var.cache.nAvgBytesPerSec;
								m_var.cache.nLeft  -=  BufferLen;
								if  (  m_var.cache.nLeft  )  memcpy(  m_var.cache.pBuf,  m_var.cache.pBuf  +  BufferLen,  m_var.cache.nLeft  );
							}
					#endif
						}

				  }
				  }
				  break;
			case  CONST_capType_mediaFile:  {
				  if  (  !m_var.bAudio  )  {
					  CQyMalloc				mallocObj;
					  CAP_procInfo_bmpU  *  pCapProcInfo  =  getCapBmpBySth(  pProcInfo,  m_var.iIndex_capProcInfo,  0  );
					  if  (  !pCapProcInfo  )  {
						  traceLogA(  (char*)  "CMySampleGrabberCB::BufferCB failed: pCapProcInfo is null"  );
						  goto  errLabel;
					  }
					  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pCapProcInfo->common.iIndex_sharedObj  );
					  if  (  !pSharedObj  )  goto  errLabel;
#if  0
					  pShmCmd  =  getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  pSharedObj->iIndex_shmCmd  );
					  if  (  !pShmCmd  )  goto  errLabel;
#endif

					  #ifdef  __DEBUG__
							  //  traceLogA(  (char*)  "Grab: video data, len %d, SampleTime %d",  BufferLen, iSampleTimeInMs  );
							  if  (  1  )  {
								  TCHAR  buf[128];
								  DWORD	dwTickCnt  =  GetTickCount(  );
								  float  fRate;

								  m_var.iFrames  ++  ;
								  if  (  !m_var.firstTickCnt  )  {
									  m_var.firstTickCnt =  dwTickCnt;									  
								  }
								  if  (  dwTickCnt  !=  m_var.firstTickCnt  )  {
									    fRate  =  m_var.iFrames  *  1000.  /  (  dwTickCnt  -  m_var.firstTickCnt  );
										if  (  !(  m_var.iFrames  %  60  )  )  {
											_sntprintf(  buf,  sizeof(  buf  )  /  sizeof(  buf[0]  ),  _T(  "BufferCB called, fRate: %f fps\n"  ),  fRate  );
											if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
												OutputDebugString(buf);
											}
										}
								  }
							  }

					  #endif


					    
					
					  if  (  pCapProcInfo->mediaFile.vh_org.bih.biSizeImage  !=  BufferLen  )  {
						  #ifdef  __DEBUG__
								  traceLogA(  (char*)  "CMySampleGrabberCB::BufferCB failed: pCapProcInfo->vh_org.bih.biSizeImage %d != BufferLen %d",  pCapProcInfo->mediaFile.vh_org.bih.biSizeImage,  BufferLen  );
						  #endif
						  goto  errLabel;
					  }					  
					  if  (  BufferLen  >  pProcInfo->cfg.uiBufSize_myDrawVideoData  )  {
						  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "BufferCB failed: biSizeImage %d is too big"  ),  BufferLen  );
						  goto  errLabel;
					  }

					  /*
					  pCapProcInfo->bLocalVideoShowed  =  FALSE;
					  toShareBmp(  pProcInfo,  m_var.uiCapType,  m_var.iIndex_capProcInfo,  (  BITMAPINFO  *  )&pCapProcInfo->vh_org.bih,  iSampleTimeInMs,  pBuffer,  &pCapProcInfo->compressVideo,  getSharedObjByIndex(  pProcInfo,  pCapProcInfo->iIndex_sharedObj  )  );				  
					  if  (  !pCapProcInfo->bLocalVideoShowed  )  {
						  //  drawLocalVideoData(  pProcInfo,  pCapProcInfo->compressVideo.uiTranNo_openAvDev,  (  BITMAPINFO  *  )&pCapProcInfo->vh_org.bih,  iSampleTimeInMs,  pBuffer,  m_var.uiCapType,  m_var.iIndex_capProcInfo,  pCapProcInfo->compressVideo.iTaskId  );							
						  drawLocalVideoData(  pProcInfo,  pCapProcInfo->compressVideo.uiTranNo_openAvDev,  (  BITMAPINFO  *  )&pCapProcInfo->vh_org.bih,  iSampleTimeInMs,  pBuffer,  m_var.uiCapType,  m_var.iIndex_capProcInfo,  pSharedObj->iTaskId  );							
					  }
					  */
					  myDRAW_VIDEO_DATA		*	p;
					  int						len;

					  //  len  =  offsetof(  myDRAW_VIDEO_DATA,  buf  )  +  pCapProcInfo->vh_org.bih.biSizeImage;
					  len  =  sizeof(  myDRAW_VIDEO_DATA  );
#if  0
					  if  (  len  >  m_var.uiBufSize_pBuf  )  {
						  MACRO_safeFree(  m_var.pBuf  );
						  m_var.uiBufSize_pBuf  =  0;
						  //
						  m_var.pBuf  =  (  BYTE  *  )mymalloc(  len  );
						  if  (  !m_var.pBuf  )  goto  errLabel;
						  m_var.uiBufSize_pBuf  =  len;
					  }
#endif
					  myDRAW_VIDEO_DATA		tmp_myDRAW_VIDEO_DATA;
					  p  =  &tmp_myDRAW_VIDEO_DATA;	//  (  myDRAW_VIDEO_DATA  *  )m_var.pBuf;
					  if  (  !p  )  goto  errLabel;
					  memset(  p,  0,  sizeof(  myDRAW_VIDEO_DATA  )  );	//  m_var.uiBufSize_pBuf  );
					  #if  0  //  def  __DEBUG__
							  if  (  m_var.uiBufSize_pBuf  !=  sizeof(  myDRAW_VIDEO_DATA  )  )  {									
								  traceLog((TCHAR*)  _T(  "CMySampleGrabberCB::BufferCB: uiBufferSize_pBuf err"  )  );
								  goto  errLabel;					  
							  }
					  #endif
					  //
					  if  (  setPktInputInfo(  pProcInfo,  &pCapProcInfo->common.compressVideo.input_BufferCB,  pCapProcInfo->common.compressVideo.usFrames_perSecond_expected,  FALSE,  p,  mynull,  NULL  )  )  {
						  goto  errLabel;
					  }
					  //  2011/12/10
					  unsigned  int  uiSize_dec  =  max(  pCapProcInfo->mediaFile.vh_org.bih.biSizeImage,  BufferLen  );
					  //  2014/01/29
					  uiSize_dec  =  max(  uiSize_dec,  pCapProcInfo->mediaFile.compressVideo.vh_decompress.bih.biSizeImage  );
					  //
					  unsigned  int  uiSize_enc  =  sizeof(  TRANSFER_VIDEO_DATA  );
					  //
					  p->head.uiLen  =  uiSize_dec  +  uiSize_enc;	//  BufferLen;	//  pCapProcInfo->vh_org.bih.biSizeImage;
					  p->head.uiSampleTimeInMs  =  iSampleTimeInMs;
					  //
					  p->uiSize_dec  =  uiSize_dec;
					  //
					  if  (  !mallocObj.mallocf(  uiSize_dec  +  uiSize_enc  )  )  goto  errLabel;
					  if  (  mallocObj.get(  &p->memory  )  )  goto  errLabel;
					  memcpy(  p->memory.m_pBuf,  pBuffer,  BufferLen  );

					  //  2011/12/05
					  memcpy(  &p->bih,  &pCapProcInfo->mediaFile.vh_org.bih,  sizeof(  p->bih  )  );

					  //  2012/11/09
					  M_pkt_setNo(  m_var.tn_pktNo,  m_var.lLastPktNo,  *p  );
					  //
					  M_set_pktId_alloc(  p  );


					  //
					  #if  0	//  2011/12/15
							if  (  q2PostMsgAndTrigger(  p,  len,  &pCapProcInfo->common.thread.q2  )  )  goto  errLabel;
					  #else
							if  (  q2PostMsgAndTrigger(  p,  len,  &pCapProcInfo->common.vppThread.q2,  _T(  "grab.BufferCB 1"  )))  goto  errLabel;
					  #endif
					  mallocObj.detach(    );

					  //  这里似乎分配内存对音乐有很多影响。应想法将myDRAW_VIDEO_DATA等事先分配好，不要临时分配
					  //  第2是，audio的处理还没有变成线程的方式。
					  }
				  else  {
					    CQyMalloc				mallocObj;
					    CAP_procInfo_mediaFileAudio  *  pCapAudio  =  (  CAP_procInfo_mediaFileAudio  *  )getCapAudioBySth(  pProcInfo,  m_var.iIndex_capProcInfo,  0  );
						if  (  !pCapAudio  )  {
							traceLogA(  (char*)  "CMySampleGrabberCB::BufferCB failed: pCapAudio is null"  );
							goto  errLabel;
						}
						pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pCapAudio->iIndex_sharedObj  );
						if  (  !pSharedObj  )  goto  errLabel;
#if  0
						pShmCmd  =  getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  pSharedObj->iIndex_shmCmd  );
						if  (  !pShmCmd  )  goto  errLabel;
#endif

						//
						//  if  (  pSharedObj->psCurrent  !=  State_Running  )  break;

						//if  (  !pShmCmd->bGlobalMute  )  
						{

							//
							myPLAY_AUDIO_DATA		*	p;
							int							len;
							//  len  =  offsetof(  myPLAY_AUDIO_DATA,  buf  )  +  BufferLen;
							len  =  sizeof(  myPLAY_AUDIO_DATA  );
						#if  0
							if  (  len  >  m_var.uiBufSize_pBuf  )  {
								MACRO_safeFree(  m_var.pBuf  );
								m_var.uiBufSize_pBuf  =  0;
								//
								m_var.pBuf  =  (  BYTE  *  )mymalloc(  len  );
								if  (  !m_var.pBuf  )  goto  errLabel;
								m_var.uiBufSize_pBuf  =  len;
							}
						#endif
							myPLAY_AUDIO_DATA	tmp_myPLAY_AUDIO_DATA;
							p  =  &tmp_myPLAY_AUDIO_DATA;	//  (  myPLAY_AUDIO_DATA  *  )m_var.pBuf;
							if  (  !p  )  goto  errLabel;
							memset(  p,  0,  sizeof(  myPLAY_AUDIO_DATA  )  );
							//  2016/12/14
							unsigned int uiSize_dec  =  BufferLen;
							//
							unsigned int uiSize_enc  =  0;	//  sizeof(  TRANSFER_AUDIO_DATA  );
							//	p->head.uiLen  =  BufferLen;
							p->head.uiLen  =  uiSize_dec  +  uiSize_enc;
							p->uiSize_dec  =  uiSize_dec;

							//
							p->head.uiSampleTimeInMs  =  iSampleTimeInMs;
							//  
						#if  0
							p->pBuf  =  mallocObj.malloc(  p->head.uiLen  );
							if  (  !p->pBuf  )  goto  errLabel;
						#else
							if  (  !mallocObj.mallocf(  p->head.uiLen  )  )  goto  errLabel;
							if  (  mallocObj.get(  &p->memory  )  )  goto  errLabel;
						#endif
							memcpy(  p->memory.m_pBuf,  pBuffer,  p->uiSize_dec  );		//  p->head.uiLen  );

							if  (  q2PostMsgAndTrigger(  p,  len,  &pCapAudio->thread.q2,  _T(  "grab.buffercb 3"  )))  goto  errLabel;
							mallocObj.detach(    );

							//
					#if  0
							if  (  m_var.cache.nBytes_pkt  )  {
								m_var.cache.iSampleTimeInMs_left  +=  BufferLen  *  1000  /  m_var.cache.nAvgBytesPerSec;
								m_var.cache.nLeft  -=  BufferLen;
								if  (  m_var.cache.nLeft  )  memcpy(  m_var.cache.pBuf,  m_var.cache.pBuf  +  BufferLen,  m_var.cache.nLeft  );
							}
					#endif
						}

				  }

				  }
				  break;
			default:

				#if  0			//  2011/12/05，不知道下面的代码是干什么用的. 
				   if  (  m_var.pDmoInfo  )  {
					   MY_DMO_INFO	*	pDmoInfo  =  (  MY_DMO_INFO  *  )m_var.pDmoInfo;
					   int  iSampleTimeInMs_stream  =  iSampleTimeInMs;

					   iSampleTimeInMs  +=  pDmoInfo->iDiffInMs_tStartStream;

					   //
					   #ifdef  __DEBUG__
							   #if  10
					   				if  (  m_var.bAudio  )  {
										if  (  pProcInfo->cfg.debugStatusInfo.ucbPrint_a_in  )  {
											traceLog((TCHAR*)  _T(  "BufferCB: a, t_stream %d, SampleTime %d,  len %d"  ),  iSampleTimeInMs_stream,  iSampleTimeInMs,  BufferLen  );
										}
									}
									else  {
										  if  (  pProcInfo->cfg.debugStatusInfo.ucbPrint_v_in  )  
										{
											traceLog((TCHAR*)  _T(  "BufferCB: v, t_stream %d, SampleTime %d,  len %d"  ),  iSampleTimeInMs_stream,  iSampleTimeInMs,  BufferLen  );
										}
									}
							   #endif
					   #endif
					   //
					   //
					   if  (  m_var.bAudio  )  {
						   playAudioData(  pProcInfo,  iSampleTimeInMs,  pBuffer,  BufferLen,  pDmoInfo->iIndex_player  );
						   }
					   else  {
						     //  drawVideoData(  pProcInfo,  iSampleTimeInMs,  pBuffer,  BufferLen,  pDmoInfo->iIndex_player  );							 
						     BufferCB_decVideo(  pProcInfo,  &m_var,  iSampleTimeInMs,  pBuffer,  BufferLen,  pDmoInfo->iIndex_player  );

					   }
					   break;
				   }
				#endif

				   traceLogA(  (char*)  "BufferCb called, capType error, %d",  m_var.uiCapType  );
				   break;
	}

	iErr  =  0;
errLabel:
	
	if  (  bCached  )  {
		if  (  m_var.cache.nBytes_pkt  )  {
			m_var.cache.iSampleTimeInMs_left  +=  BufferLen  *  1000  /  m_var.cache.nAvgBytesPerSec;
			m_var.cache.nLeft  -=  BufferLen;
			if  (  m_var.cache.nLeft  )  memcpy(  m_var.cache.pBuf,  m_var.cache.pBuf  +  BufferLen,  m_var.cache.nLeft  );
		}
	}

	return  S_OK;
}



#if !defined(  __WINCE__  )  ||  defined(  __TEST__  )


 void  *  CAP_STUFF_new(  )  
{
	return  objNew(  sizeof(  CAP_STUFF  )  );
}


 void  CAP_STUFF_free(  void  *  p  )
{
	if  (  !p  )  return;
	CAP_STUFF  &  gcap  =  *(  CAP_STUFF  *  )p;

	CAP_STUFF_exit(  p  );

	MACRO_safeFree(  p  );
	return;
}

 void  CAP_STUFF_exit(  void  *  p  )
 {
	if  (  !p  )  return;
	CAP_STUFF  &  gcap  =  *(  CAP_STUFF  *  )p;

	// Destroy the filter graph and cleanup
    StopPreview(gcap);
    StopCapture(gcap);
    TearDownGraph(gcap);
    FreeCapFilters(gcap);

	//
	IMonRelease(gcap.pmVideo);
	IMonRelease(gcap.pmAudio);

	for(int i = 0; i < NUMELMS(gcap.rgpmVideoMenu); i++)  {
		IMonRelease(gcap.rgpmVideoMenu[i]);
	}
	for(int i = 0; i < NUMELMS(gcap.rgpmAudioMenu); i++)  {
		IMonRelease(gcap.rgpmAudioMenu[i]);
	}
	return;
 }

 BOOL  CAP_STUFF_bAudio(  void  *  p  )
{
	if  (  !p  )  return  FALSE;
	CAP_STUFF  *  p1  =  (  CAP_STUFF  *  )p;
	return  p1->pmAudio  ?  TRUE  :  FALSE;
}

 BOOL  CAP_STUFF_bVideo(  void  *  p  )
{
	if  (  !p  )  return  FALSE;
	CAP_STUFF  *  p1  =  (  CAP_STUFF  *  )p;
	return  p1->pmVideo  ?  TRUE  :  FALSE;
}

#endif


 //  2013/06/12
  void  myChooseDevices(  void  *  p_gcap,void  *  pIMoniker_v, void  *  pIMoniker_a  )
  {
	  if  (  !p_gcap  )  return;
	  CAP_STUFF  &gcap  =  *(  CAP_STUFF  *  )p_gcap;
	  ChooseDevices(  gcap,  (  IMoniker  *  )pIMoniker_v,  (  IMoniker  *  )pIMoniker_a  );
	  return;
  }

 


 //  2012/02/24
  BOOL  bRecorderUsing(  void  *  pMC_VAR_isCli,  void  *  pMoniker_a,  int  *  piIndex_capAudio,  int  *  piIndex_sharedObj  )
 {
	BOOL			bRet				=	FALSE;
	int				iIndex_capAudio		=	-1;
	int				iIndex_sharedObj	=	-1;
	int				i					=	0;

	MC_VAR_isCli  *  pProcInfo  =  (  MC_VAR_isCli  *  )pMC_VAR_isCli;

	if  (  pMoniker_a  )  {
		IMoniker  *		pM					=	(  IMoniker  *  )pMoniker_a;


		for  (  int  index  =  0;  index  <  pProcInfo->cfg.usMaxCnt_pSharedObjs;  index  ++  )  {
			 QY_SHARED_OBJ	*	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  index  );
			 if  (  !pSharedObj->bUsed  )  continue;
			 switch  (  pSharedObj->uiType1  )  {
					 case  CONST_sharedObjType_av:
					 case  CONST_sharedObjType_mediaDevice:  {
						   SHARE_MEDIA_DEVICE  *  p  =  (  SHARE_MEDIA_DEVICE  *  )pSharedObj->pShareMediaObj;
						   if  (  p  &&  p->p_gcap  )  {
							   AV_capStuff  &  gcap  =  *(  AV_capStuff  *  )p->p_gcap;
							   if  (  gcap.pmVideo  )  {
								   if  (  S_OK   ==  pM->IsEqual(  gcap.pmAudio  )  )  {
									   iIndex_sharedObj  =  i;
									   bRet  =  TRUE;  
									   goto  errLabel;
								   }
							   }
						   }
						   }					   
						   break;
					 default:
							break;
			 }
		}
	}

errLabel:

	if  (  bRet  )  {
		if  (  piIndex_capAudio  )  *piIndex_capAudio  =  iIndex_capAudio;
		if  (  piIndex_sharedObj  )  *piIndex_sharedObj  =  iIndex_sharedObj;
	}

	 return  bRet;
  }

 //BOOL  bWebcamUsing(  MC_VAR_isCli  *  pProcInfo,  void  *  pMoniker_v,  int  *  piIndex_capBmp,  int  *  piIndex_sharedObj  )
 BOOL  bWebcamUsing(  void  *  pMC_VAR_isCli,  unsigned  int  uiCamCapType,  void  *  pMoniker_v,  LPCTSTR  camName,  int  *  piIndex_capBmp,  int  *  piIndex_sharedObj  )
{
	BOOL			bRet				=	FALSE;
	int				iIndex_capBmp		=	-1;
	int				iIndex_sharedObj	=	-1;
	int				i					=	0;

	MC_VAR_isCli  *  pProcInfo  =  (  MC_VAR_isCli  *  )pMC_VAR_isCli;

	if  (  !pProcInfo  )  return  FALSE;


	if  (  pMoniker_v  )  {
		IMoniker  *		pM					=	(  IMoniker  *  )pMoniker_v;

#if  0	//  2014/03/28
		if  (  pProcInfo->cfg.policy.video.uiCamCapType  !=  CONST_camCapType_directX  )  return  FALSE;
#endif

		for  (  i  =  0;  i  <  pProcInfo->cfg.usMaxCnt_capProcInfoBmps;  i  ++  )  {
			 CAP_procInfo_bmpU  *  pCapBmp  =  getCapBmpBySth(  pProcInfo,  i,  0  );
			 if  (  !pCapBmp  )  continue;
			 switch  (  pCapBmp->common.uiType  )  {
					  case  CONST_capType_av:  {  
						    CAP_procInfo_video  *  pVc;
							pVc  =  (  CAP_procInfo_video  *  )getCapBmpBySth(  pProcInfo,  i,  0  );
							if  (  !pVc  )  continue;

							if  (  pVc->bCapDevConnected  )  {
								if  (  pVc->uiCamCapType  ==  CONST_camCapType_directX  )  {
									VIDEO_capDev_dx	*	p;

									p  =	(  VIDEO_capDev_dx  *  )pVc->capDev.pVideoCapDev;
									//
									if  (  p  &&  p->p_gcap  )  {
										AV_capStuff  &  gcap  =  *(  AV_capStuff  *  )p->p_gcap;
										if  (  gcap.pmVideo  )  {
											if  (  S_OK   ==  pM->IsEqual(  gcap.pmVideo  )  )  {
												//
												TCHAR  friendlyName[256];
												getMonikerFriendlyName(pM, friendlyName, mycountof(friendlyName));
												//
												iIndex_capBmp  =  i;
												bRet  =  TRUE;  
												goto  errLabel;
											}
										}
									}
								}
							}
							}
							break;
					  default:
							  break;
			 }
		}


		for  (  int  index  =  0;  index  <  pProcInfo->cfg.usMaxCnt_pSharedObjs;  index  ++  )  {
			 QY_SHARED_OBJ	*	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  index  );
			 if  (  !pSharedObj->bUsed  )  continue;
			 switch  (  pSharedObj->uiType1  )  {
					 case  CONST_sharedObjType_av:
					 case  CONST_sharedObjType_mediaDevice:  {
						   SHARE_MEDIA_DEVICE  *  p  =  (  SHARE_MEDIA_DEVICE  *  )pSharedObj->pShareMediaObj;
						   if  (  p  &&  p->p_gcap  )  {
							   AV_capStuff  &  gcap  =  *(  AV_capStuff  *  )p->p_gcap;
							   if  (  gcap.pmVideo  )  {
								   if  (  S_OK   ==  pM->IsEqual(  gcap.pmVideo  )  )  {
									   //
									   //
									   iIndex_sharedObj  =  i;
									   bRet  =  TRUE;  
									   goto  errLabel;
								   }
							   }
						   }
						   }					   
						   break;
					 default:
							break;
			 }
		}

		//
		TCHAR	displayName[MAX_monikerDisplayNameLen  +  1];
		if  (  getMonikerDisplayName(  pM,  displayName,  mycountof(  displayName  )  )  )  displayName[0]  =  0;

		if  (  displayName[0]  )  {
			for  (  i  =  0;  i  <  pProcInfo->cfg.usMaxCnt_pSharedObjs;  i  ++  )  {
				 QY_SHARED_OBJ	*	pSharedObj	=	getSharedObjByIndex(  pProcInfo,  i  );
				 if  (  !pSharedObj  )  continue;
				 if  (  pSharedObj->bUsed  )  {
#if  0
					 QM_SHM_CMD  *  pShmCmd  =  getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  pSharedObj->iIndex_shmCmd  );
					 if  (  pShmCmd  )  {
						 if  (  !lstrcmpi(  displayName,  pShmCmd->path  )  )  {
							 iIndex_sharedObj  =  i;
							 bRet  =  TRUE;
							 goto  errLabel;
						 }
					 }
#endif
				 }
			}
		}

	}




errLabel:
	
	if  (  bRet  )  {
		if  (  piIndex_capBmp  )  *piIndex_capBmp  =  iIndex_capBmp;
		if  (  piIndex_sharedObj  )  *piIndex_sharedObj  =  iIndex_sharedObj;
	}

	return  bRet;
}


#ifndef  __WINCE__
  void  chooseAvDevice(  void  *  pCapParam,  BOOL  bIncludeACap,  HWND  hWnd,  HWND  hWndStatus,  int  iMenuId  )
 {
	 if  (  !pCapParam  )  return;
	 CAP_STUFF  *  pCap  =  (  CAP_STUFF  *  )pCapParam;
	 CAP_STUFF	&	gcap	=	*(  CAP_STUFF  *  )pCapParam;
	

	if  (  iMenuId  >=  ID_MENU_VDEVICE0  &&  iMenuId  <=  ID_MENU_VDEVICE9  )  {
		ChooseDevices(  *pCap,  gcap.rgpmVideoMenu[iMenuId - ID_MENU_VDEVICE0], gcap.pmAudio  );
		}
	else  if  (  iMenuId  >=  ID_MENU_ADEVICE0  &&  iMenuId  <=  ID_MENU_ADEVICE9  )  {
			  if  (  bIncludeACap  )  {
				  ChooseDevices(  *pCap,  gcap.pmVideo, gcap.rgpmAudioMenu[iMenuId - ID_MENU_ADEVICE0]);
				  }
			  else  {
				    MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

				    if  (  pProcInfo->cfg.policy.audio.ucbNot_selectDefaultRecorder  )  {	//  2014/07/31. 
						unsigned  int  uCheck;
						int i;

						gcap.old_audioDevices.iMenuId_selectedAudio  =  iMenuId;

						for  (  i  =  0;  i  <  NUMELMS(  gcap.old_audioDevices.mems  );  i  ++  )  {
							if  (  gcap.old_audioDevices.mems[i].iMenuIds_audio  ==  0  )  break;

							if  (  !gcap.old_audioDevices.iMenuId_selectedAudio  )  uCheck  =  MF_UNCHECKED;
							else  uCheck  =  (  gcap.old_audioDevices.mems[i].iMenuIds_audio  ==  gcap.old_audioDevices.iMenuId_selectedAudio  )  ?  MF_CHECKED  :  MF_UNCHECKED;

							 CheckMenuItem(::GetMenu(  hWnd  ), ID_MENU_ADEVICE0 + i,  uCheck  );
						}
					}

			  }
	}
	return;
 }

  //  2012/05/03
  void  chooseAvDevice_shadow(  void  *  pCapParam_mgr,  BOOL  bIncludeACap,  HWND  hShadow,  HWND  hWndStatus,  int  iMenuId  )
 {
	 if  (  !pCapParam_mgr  )  return;
	 //  CAP_STUFF  *  pCap  =  (  CAP_STUFF  *  )pCapParam;
	 CAP_STUFF	&	gcap	=	*(  CAP_STUFF  *  )pCapParam_mgr;
	 HWND  hWnd  =  hShadow;

	 unsigned  int  uCheck;
	 int i;

	if  (  iMenuId  >=  ID_MENU_VDEVICE0  &&  iMenuId  <=  ID_MENU_VDEVICE9  )  {
		//  ChooseDevices(  *pCap,  gcap.rgpmVideoMenu[iMenuId - ID_MENU_VDEVICE0], gcap.pmAudio  );
		for  (  i  =  0;  i  <  NUMELMS(  gcap.rgpmVideoMenu  );  i  ++  )  {
			 if  (  !gcap.rgpmVideoMenu[i]  )  break;
			 uCheck  =  (  iMenuId  ==  ID_MENU_VDEVICE0  +  i  )  ?  MF_CHECKED  :  MF_UNCHECKED;

			 //
			 CheckMenuItem(::GetMenu(  hWnd  ), ID_MENU_VDEVICE0 + i,  uCheck  );

		}
		}
	else  if  (  iMenuId  >=  ID_MENU_ADEVICE0  &&  iMenuId  <=  ID_MENU_ADEVICE9  )  {

			  if  (  bIncludeACap  )  {
				  for  (  i  =  0;  i  <  NUMELMS(  gcap.rgpmAudioMenu  );  i  ++  )  {
					   if  (  !gcap.rgpmAudioMenu[i]  )  break;
					   uCheck  =  (  iMenuId  ==  ID_MENU_ADEVICE0  +  i  )  ?  MF_CHECKED  :  MF_UNCHECKED;

					   //
					   CheckMenuItem(::GetMenu(  hWnd  ), ID_MENU_ADEVICE0 + i,  uCheck  );

				  }
				  }
			  else  {
				    MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
					if  (  pProcInfo->cfg.policy.audio.ucbNot_selectDefaultRecorder  )  {
						//  2014/07/31
						gcap.old_audioDevices.iMenuId_selectedAudio  =  iMenuId;

						for  (  i  =  0;  i  <  NUMELMS(  gcap.old_audioDevices.mems  );  i  ++  )  {
							if  (  gcap.old_audioDevices.mems[i].iMenuIds_audio  ==  0  )  break;

							if  (  !gcap.old_audioDevices.iMenuId_selectedAudio  )  uCheck  =  MF_UNCHECKED;
							else  uCheck  =  (  gcap.old_audioDevices.mems[i].iMenuIds_audio  ==  gcap.old_audioDevices.iMenuId_selectedAudio  )  ?  MF_CHECKED  :  MF_UNCHECKED;

							 CheckMenuItem(::GetMenu(  hWnd  ), ID_MENU_ADEVICE0 + i,  uCheck  );
						}
					}
			  }

	}
	return;
 }

  //
 int  saveChosenDevice(  void  *  pCapParam,  BOOL  bIncludeACap,  int  iMenuId  )
{
	QY_MC		*	pQyMc	=	QY_GET_GBUF(  );
	CAP_STUFF	*	pCapStuff  =  (  CAP_STUFF  *  )pCapParam;

	QY_REG			reg;
	memset(  &reg,  0,  sizeof(  reg  )  );
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	lstrcpyn(  reg.rootKey,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );
	TCHAR		tBuf[MAX_monikerDisplayNameLen  +  1];

	if  (  iMenuId  >=  ID_MENU_ADEVICE0  &&  iMenuId  <=  ID_MENU_ADEVICE9  )  {
		if  (  bIncludeACap  )  {
			getMonikerDisplayName(  pCapStuff->rgpmAudioMenu[iMenuId  -  ID_MENU_ADEVICE0],  tBuf,  mycountof(  tBuf  )  );
			qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  _T(  CONST_regValName_recorder_selected  ),  tBuf  );
			}
		else  {
			  safeTcsnCpy(  pCapStuff->old_audioDevices.mems[iMenuId  -  ID_MENU_ADEVICE0].names_audio,  tBuf,  mycountof(  tBuf  )  );
			  qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  _T(  CONST_regValName_recorder_selected  ),  tBuf  );		
		}
	}
	if  (  iMenuId  >=  ID_MENU_VDEVICE0  &&  iMenuId  <=  ID_MENU_VDEVICE9  )  {		
		//  2011/10/24
		getMonikerDisplayName(  pCapStuff->rgpmVideoMenu[iMenuId  -  ID_MENU_VDEVICE0],  tBuf,  mycountof(  tBuf  )  );
		qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  _T(  CONST_regValName_webcam_selected  ),  tBuf  );
	}

	return  0;
}

 int  getChosenDevice(  TCHAR  *  recorder_selected,  unsigned  int  uiCnt_recorder_selected,  TCHAR  *  webcam_selected,  unsigned  int  uiCnt_webcam_selected,
						void  *  pCapParam,  BOOL  bIncludeACap,  int  *  piMenuId_selectedAudio,  int  *  piMenuId_selectedVideo  )
{
	QY_MC		*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	QY_REG			reg;
	memset(  &reg,  0,  sizeof(  reg  )  );
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	lstrcpyn(  reg.rootKey,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );

	int		i;
	int		iMenuId_selectedAudio  =  0;
	int		iMenuId_selectedVideo  =  0;
	TCHAR	tBuf[256];

	if  (  recorder_selected  )  {
		if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  _T(  CONST_regValName_recorder_selected  ),  (  char  *  )recorder_selected,  sizeof(  TCHAR  )  *  uiCnt_recorder_selected,  NULL  )  )  {
			if  (  pCapParam  )  {
				CAP_STUFF	*	pCapStuff  =  (  CAP_STUFF  *  )pCapParam;

				if  (  bIncludeACap  )  {
					for  (  i  =  0;  i  <  mycountof(  pCapStuff->rgpmAudioMenu  );  i  ++  )  {
						 if  (  !pCapStuff->rgpmAudioMenu[i]  )  break;
						 getMonikerDisplayName(  pCapStuff->rgpmAudioMenu[i],  tBuf,  mycountof(  tBuf  )  );
						 if  (  !lstrcmpi(  tBuf,  recorder_selected  )  )  {
							 iMenuId_selectedAudio  =  ID_MENU_ADEVICE0  +  i;
							 break;
						 }			
					}
					}
				else  {
					for  (  i  =  0;  i  <  mycountof(  pCapStuff->old_audioDevices.mems  );  i  ++  )  {
						  if  (  !pCapStuff->old_audioDevices.mems[i].names_audio[0]  )  break;
						  //
						  if  (  pProcInfo->cfg.policy.audio.ucbNot_selectDefaultRecorder  )  {
							  if  (  !lstrcmpi(  pCapStuff->old_audioDevices.mems[i].names_audio,  recorder_selected  )  )  {
								  iMenuId_selectedAudio  =  pCapStuff->old_audioDevices.mems[i].iMenuIds_audio;
								  break;
							  }
						 }			
					}	
				}				
			}
		}
	}
	if  (  webcam_selected  )  {
		if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  _T(  CONST_regValName_webcam_selected  ),  (  char  *  )webcam_selected,  sizeof(  TCHAR  )  *  uiCnt_webcam_selected,  NULL  )  )  {
			if  (  pCapParam  )  {
				CAP_STUFF	*	pCapStuff  =  (  CAP_STUFF  *  )pCapParam;

				for  (  i  =  0;  i  <  mycountof(  pCapStuff->rgpmVideoMenu  );  i  ++  )  {
					 if  (  !pCapStuff->rgpmVideoMenu[i]  )  break;
					 getMonikerDisplayName(  pCapStuff->rgpmVideoMenu[i],  tBuf,  mycountof(  tBuf  )  );
					 if  (  !lstrcmpi(  tBuf,  webcam_selected  )  )  {
						 iMenuId_selectedVideo  =  ID_MENU_VDEVICE0  +  i;
						 break;
					 }			
				}
			}
		}
	}

	if  (  piMenuId_selectedAudio  )  *piMenuId_selectedAudio  =  iMenuId_selectedAudio;
	if  (  piMenuId_selectedVideo  )  *piMenuId_selectedVideo  =  iMenuId_selectedVideo;

	return  0;
}

#endif


#if !defined(  __WINCE__  )  ||  defined(  __TEST__  )

 //
 int  get_iNumADevices(void* pCapParam)
 {
	 int  n = 0;

	 if (!pCapParam)  return  0;
	 CAP_STUFF* pCap = (CAP_STUFF*)pCapParam;


	 return  pCap->old_audioDevices.iNumADevices;
 }

//
 

 //
 int get_iNumVCapDevices(void* pCapParam)
 {
	 int  n = 0;
	 if (!pCapParam)  return  0;
	 CAP_STUFF* pCap = (CAP_STUFF*)pCapParam;

	 return  pCap->iNumVCapDevices;
 }


 //
 bool  bHaveSubStr(TCHAR* subStr, TCHAR* str)
 {
	 if (!subStr || !str)  return false;

	 int  n_subStr = lstrlen(subStr);
	 int n_str = lstrlen(str);

	 int i;
	 for (i = 0; i < n_str; i++) {
		 TCHAR* pT = &str[i];
		 if (!_tcsnicmp(subStr, pT, n_subStr)) {
			 return true;
		 }
	 }

	 return false;
 }


 //
 int  get_iNumADevices(void* pCapParam, QY_DMITEM* pSkippedTable,bool bPrint)
 {
	 int  n = 0;

	 if (!pCapParam)  return  0;
	 CAP_STUFF* pCap = (CAP_STUFF*)pCapParam;

	 //
	 if (pSkippedTable) {
		 QY_DMITEM* pItem;
		 int cnt = 0;
		 int i;
		 for (i = 0; i < pCap->old_audioDevices.iNumADevices; i++) {
			 bool bSkipped = false;
			 for (pItem = pSkippedTable; pItem->type != -1; pItem++) {
				 if (bHaveSubStr(const_cast<TCHAR*>(pItem->des), pCap->old_audioDevices.mems[i].names_audio)) {
					 bSkipped = true;
					 break;
				 }
			 }
			 //
			 if (!bSkipped) {
				 cnt++;
				 //
				 if (bPrint) {
					 showInfo_open0(0, _T("get_iNumADev"), pCap->old_audioDevices.mems[i].names_audio);
				 }
			 }
			 //
			 continue;
		 }
		 return  cnt;
	 }

	 //
	 return  pCap->old_audioDevices.iNumADevices;
 }

 //
 int get_iNumVCapDevices(void* pCapParam, QY_DMITEM* pSkippedTable, bool bPrint)
 {
	 int  n = 0;
	 if (!pCapParam)  return  0;
	 CAP_STUFF* pCap = (CAP_STUFF*)pCapParam;


	 //
	 if (pSkippedTable) {
		 QY_DMITEM* pItem;
		 int cnt = 0;
		 int i;
		 for (i = 0; i < pCap->iNumVCapDevices; i++) {
			 ///
			 TCHAR  devName[128];
			 getMonikerFriendlyName(pCap->rgpmVideoMenu[i], devName, mycountof(devName));
			 //
			 bool bSkipped = false;
			 for (pItem = pSkippedTable; pItem->type != -1; pItem++) {
				 if (bHaveSubStr(const_cast<TCHAR*>(pItem->des), devName)) {
					 bSkipped = true;
					 break;
				 }
			 }
			 //
			 if (!bSkipped) {
				 cnt++;
				 //
				 if (bPrint) {
					 showInfo_open0(0, _T("get_iNumVDev"), devName);
				 }
			 }
			 //
			 continue;
		 }
		 return  cnt;
	 }



	 //
	 return  pCap->iNumVCapDevices;
 }


 //  2011/10/24
 //  void  *  getADeviceGuid(  void  *  pCapParam,  int  iMenuId  )
 void  *  getADeviceGuid(  void  *  pCapParam,  int  iMenuId,  TCHAR  *  devDesc,  int  devDescCnt  )		//  2011/10/24
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );


	 if  (  !pCapParam  )  return  NULL;
	 CAP_STUFF  *  pCap  =  (  CAP_STUFF  *  )pCapParam;
	 
	 OLD_audioDevice  *  pMem=NULL;
	 BOOL				bMatched_defADev  =  FALSE;

	 //  2014/07/31
	if  (  !pProcInfo->cfg.policy.audio.ucbNot_selectDefaultRecorder
		||  !iMenuId  )  
	{		
		int  i;
		for  (  i  =  0;  i  <  pCap->old_audioDevices.iNumADevices;  i  ++  )  {
			 pMem  =  &pCap->old_audioDevices.mems[i];
			 if  (  pMem->guid_audio  ==  pCap->old_audioDevices.default_guid_audio  )  {
				 bMatched_defADev  =  TRUE;
				 break;
			 }			
		}
	}

	//
	if  (  !bMatched_defADev  )  {
		//
		if  (  !iMenuId  )  {
			//  iMenuId  =  ID_MENU_ADEVICE0;
			return  NULL;						//  当音频设备不选时，希望采用系统缺省麦克风
		}
		if  (  iMenuId  <  ID_MENU_ADEVICE0  ||  iMenuId  >  ID_MENU_ADEVICE9  )  return  NULL;
		
		pMem  =  &pCap->old_audioDevices.mems[iMenuId  -  ID_MENU_ADEVICE0];
	}

	//
	TCHAR  tBuf[128]  =  _T(  ""  );
	if  (  pProcInfo->cfg.policy.audio.ucbNot_selectDefaultRecorder  )  {
		if  (  !iMenuId  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "The specified aDev not exists."  )  );		
	}
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s defaultADev. %s"  ),  tBuf,  bMatched_defADev  ?  _T(  "Use"  )  :  _T(  "Not use"  ),  pMem->names_audio  );	
	//
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  "getADeviceGuid:"  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );
	
	//
	 safeTcsnCpy(  pMem->names_audio,  devDesc,  devDescCnt  );
	 return  &pMem->guid_audio;
 }

 //  2013/03/19
  void  *  getMoniker_a(  void  *  pCapParam,  int  iMenuId  )
 {
	 if  (  !pCapParam  )  return  NULL;
	 CAP_STUFF  *  pCap  =  (  CAP_STUFF  *  )pCapParam;

	 if  (  !iMenuId  )  iMenuId  =  ID_MENU_ADEVICE0;
	 if  (  iMenuId  <  ID_MENU_ADEVICE0  ||  iMenuId  >  ID_MENU_ADEVICE9  )  return  NULL;

	 return   pCap->rgpmAudioMenu[iMenuId  -  ID_MENU_ADEVICE0];
 }

  //
  void  *  getMoniker_v(  void  *  pCapParam,  int  iMenuId  )
 {
	 if  (  !pCapParam  )  return  NULL;
	 CAP_STUFF  *  pCap  =  (  CAP_STUFF  *  )pCapParam;

	 if  (  !iMenuId  )  iMenuId  =  ID_MENU_VDEVICE0;
	 if  (  iMenuId  <  ID_MENU_VDEVICE0  ||  iMenuId  >  ID_MENU_VDEVICE9  )  return  NULL;

	 return   pCap->rgpmVideoMenu[iMenuId  -  ID_MENU_VDEVICE0];
 }

#endif


 //  2011/12/28
  int  getMonikerProp(  void  *  pMonikerParam,  LPCTSTR  propName,  TCHAR  *  propVal,  int  propValCnt  )
 {
	 int				iErr	=	-1;	 
	 IMoniker		*	pM		=	(  IMoniker  *  )pMonikerParam;
	 HRESULT			hr;
	 IPropertyBag	*	pBag	=	0;
	 BOOL				bGot	=	FALSE;

	 if  (  !pM  ||  !propVal  ||  !propValCnt  )  return  -1;

	 hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
	 if  (  SUCCEEDED(  hr  )  )  {
		 VARIANT var;
		 var.vt = VT_BSTR;			 
		 hr = pBag->Read(propName, &var, NULL);
		 if  (  hr  ==  NOERROR  )  {										
			 lstrcpyn(  propVal,  var.bstrVal,  propValCnt  );		//  2009/08/17
			 SysFreeString(var.bstrVal);
			 bGot  =  TRUE;
		 }
		 pBag->Release();
	 }

	 if  (  !bGot  )  goto  errLabel;

	 iErr  =  0;
errLabel:
	 return  iErr;
 }

  int  getMonikerDisplayName(  void  *  pMonikerParam,  TCHAR  *  displayName,  int  displayNameCnt  )
{
	 int				iErr	=	-1;	 
	 IMoniker		*	pM		=	(  IMoniker  *  )pMonikerParam;
    
	 TCHAR szBuf[512];
	 WCHAR *wszDisplayName = NULL;

	 wszDisplayName = 0;
	 szBuf[0] = NULL;

	 if(pM)
    {
        if(SUCCEEDED(pM->GetDisplayName(0, 0, &wszDisplayName)))
        {
            if(wszDisplayName)
            {
                StringCchCopyN(szBuf, NUMELMS(szBuf), wszDisplayName, NUMELMS(szBuf)-1);
                CoTaskMemFree(wszDisplayName);
            }
        }
    }

	 lstrcpyn(  displayName,  szBuf,  displayNameCnt  );
	 return  0;
 }


  int  getMonikerByDisplayName(  LPCTSTR  displayName,  void  **  ppMoniker  )
 {
	IBindCtx *lpBC=0;
    IMoniker *pm = 0;
	HRESULT hr = CreateBindCtx(0, &lpBC);
    if(SUCCEEDED(hr))
    {
        DWORD dwEaten;
        hr = MkParseDisplayName(lpBC, displayName, &dwEaten, &pm);

        lpBC->Release();
    }

	if  (  pm  )  {
		*ppMoniker  =  pm;
	}
	return  pm  ?  0  :  -1;
 }

 //  2013/04/04
int  getADevFriendlyName(  void  *  pCapParam,  BOOL  bIncludeAudio,  int  iMenuId,  TCHAR  *  name,  int  cnt  )
{
	 if  (  !pCapParam  )  return  NULL;
	 CAP_STUFF  *  pCap  =  (  CAP_STUFF  *  )pCapParam;

	 //if  (  !iMenuId  )  iMenuId  =  ID_MENU_ADEVICE0;
	 if  (  iMenuId  <  ID_MENU_ADEVICE0  ||  iMenuId  >  ID_MENU_ADEVICE9  )  return  NULL;

	 safeTcsnCpy(  pCap->old_audioDevices.mems[iMenuId  -  ID_MENU_ADEVICE0].names_audio,  name,  cnt  );
	 return  0;
}

  //
#if !defined(  __WINCE__  )  ||  defined(  __TEST__  )

 BOOL CALLBACK myDSEnumCallback(
  LPGUID lpGuid,
  LPCTSTR lpcstrDescription,
  LPCTSTR lpcstrModule,
  LPVOID lpContext
)
 {
#ifdef  __DEBUG__	 
		traceLog((TCHAR*)  _T(  "%s, %s"  ),  lpcstrDescription,  lpcstrModule  );
#endif
		COMMON_PARAM	*	pCommonParam	=	(  COMMON_PARAM  *  )lpContext;
		//
		CAP_STUFF	&	gcap		=	*(  CAP_STUFF  *  )pCommonParam->p0;
		HMENU			hMenuSub	=	(  HMENU  )pCommonParam->p1;
		UINT		&	uIndex		=	*(  UINT  *  )pCommonParam->p2;

		//  注意：lpGuid为NULL时表示主要音频设备。这里是将这个缺省设备放弃了
		if  (  !lpGuid  ||  !lpcstrDescription  )  return  TRUE;

		if  (  uIndex  <  mycountof(  gcap.old_audioDevices.mems  )  )  {

			gcap.old_audioDevices.mems[uIndex].iMenuIds_audio  =  ID_MENU_ADEVICE0  +  uIndex;	
			lstrcpyn(  gcap.old_audioDevices.mems[uIndex].names_audio,  lpcstrDescription,  mycountof(  gcap.old_audioDevices.mems[uIndex].names_audio  )  );		//  2009/08/17
			gcap.old_audioDevices.mems[uIndex].guid_audio  =  *lpGuid;
				
			//  if  (  gcap.iMenuId_selectedAudio  ==  gcap.iMenuIds_audio[uIndex]  )  bCheck = TRUE;

			#if  0
			if  (  hMenuSub  )  {

				AppendMenu(hMenuSub, MF_STRING, ID_MENU_ADEVICE0 + uIndex,  lpcstrDescription);
				  
				#if  0
					CheckMenuItem(hMenuSub,  ID_MENU_ADEVICE0 + uIndex,  (bCheck ? MF_CHECKED : MF_UNCHECKED));
					EnableMenuItem(hMenuSub, ID_MENU_ADEVICE0 + uIndex,  (gcap.fCapturing ? MF_DISABLED : MF_ENABLED));
					bCheck = FALSE;
				#endif
			}
			#endif
					
			uIndex++;
		}
			 
		return  TRUE;
 }


 void  addDevicesToMenu(  void  *  pCapParam,  BOOL  bIncludeACap,  HWND  hWnd  )
{
	if  (  !pCapParam  )  return;
	CAP_STUFF	&	gcap	=	*(  CAP_STUFF  *  )pCapParam;
	QY_MC		*	pQyMc	=	QY_GET_GBUF(  );

	gcap.ghwndApp  =  hWnd;

	//
	gcap.iNumVCapDevices	=	0;
	gcap.iNumACapDevices	=	0;
	gcap.old_audioDevices.iNumADevices  =  0;

	//
    UINT    uIndex			=	0;
    HMENU   hMenuSub		=	0;
    HRESULT hr				=	0;
    BOOL	bCheck			=	FALSE;

	if  (  hWnd  )  {
		hMenuSub = GetSubMenu(  ::GetMenu(  hWnd  ),  0  );        // Devices menu
		if  (  hMenuSub  )  {		//  2012/04/08. 墙上使用时,会没菜单

			// Clean the sub menu
			int iMenuItems = GetMenuItemCount(hMenuSub);
			if  (  iMenuItems == -1)  return;
    
			if  (  iMenuItems > 0)  {
				BOOL  bRet;
				for  (  int  i  =  0;  i  <  NUMELMS(  gcap.rgpmVideoMenu  );  i  ++  )  {
					 bRet  =  RemoveMenu(  hMenuSub,  ID_MENU_VDEVICE0  +  i,  MF_BYCOMMAND  );
				}
				for  (  int  i  =  0;  i  <  NUMELMS(  gcap.rgpmAudioMenu  );  i  ++  )  {
					 bRet  =  RemoveMenu(  hMenuSub,  ID_MENU_ADEVICE0  +  i,  MF_BYCOMMAND  );
				}				
				//  2014/07/31
				bRet  =  RemoveMenu(  hMenuSub,  ID_MENU_selectDefaultRecorder,  MF_BYCOMMAND  );
				//
				bRet  =  RemoveMenu(  hMenuSub,  ID_MENU_cfgCaptureFilter_v,  MF_BYCOMMAND  );
				bRet  =  RemoveMenu(  hMenuSub,  ID_MENU_cfgCapturePin_v,  MF_BYCOMMAND  );
				#ifdef  __SUPPORT_cfgPreviewPin__
						bRet  =  RemoveMenu(  hMenuSub,  ID_MENU_cfgPreviewPin_v,  MF_BYCOMMAND  );
				#endif
				bRet  =  RemoveMenu(  hMenuSub,  ID_MENU_cfgCrossBar_v,  MF_BYCOMMAND  );			
			}

			//		
			iMenuItems = GetMenuItemCount(hMenuSub);
			if  (  iMenuItems  >  3  )  {
				UINT iState;
				int  nPos;
				int		i;
				for  (  i  =  0;  i  <  3;  i  ++  )  {
					 nPos  =  iMenuItems  -  1  -  i;
					 iState  =  GetMenuState(  hMenuSub,  nPos,  MF_BYPOSITION  );
					 if  (  !(  iState  &  MF_SEPARATOR  )  )  break;				 
					 RemoveMenu(  hMenuSub,  nPos,  MF_BYPOSITION  );				 
				}
			}

		}
	}

	for(int i = 0; i < NUMELMS(gcap.rgpmVideoMenu); i++)
    {
        IMonRelease(gcap.rgpmVideoMenu[i]);
    }
    for(int i = 0; i < NUMELMS(gcap.rgpmAudioMenu); i++)
    {
        IMonRelease(gcap.rgpmAudioMenu[i]);
    }


	//
	AppendMenu(hMenuSub, MF_SEPARATOR, 0, NULL);


    // enumerate all video capture devices
    ICreateDevEnum *pCreateDevEnum=0;
    hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
                          IID_ICreateDevEnum, (void**)&pCreateDevEnum);
    if  (  SUCCEEDED(  hr  )  )  {

		IEnumMoniker	*	pEm		=	0;
		ULONG				cFetched;
		IMoniker		*	pM;

		hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEm, 0);
		if  (  hr  ==  S_OK  )  {
			pEm->Reset();

			while(hr = pEm->Next(1, &pM, &cFetched), hr==S_OK)  {
				IPropertyBag *pBag=0;

				hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
				if  (  SUCCEEDED(  hr  )  )  {
					VARIANT var;
					var.vt = VT_BSTR;
					hr = pBag->Read(L"FriendlyName", &var, NULL);
					if  (  hr  ==  NOERROR  )  {


						//  if  (  gcap.iMenuId_selectedVideo  ==  gcap.iMenuIds_video[uIndex]  )  bCheck = TRUE;

						if  (  hWnd  )  {
							AppendMenu(hMenuSub, MF_STRING, ID_MENU_VDEVICE0 + uIndex,  var.bstrVal);

							CheckMenuItem(hMenuSub,  ID_MENU_VDEVICE0 + uIndex,  (bCheck ? MF_CHECKED : MF_UNCHECKED));
							EnableMenuItem(hMenuSub, ID_MENU_VDEVICE0 + uIndex,  (gcap.fCapturing ? MF_DISABLED : MF_ENABLED));
						}

						bCheck = FALSE;

						SysFreeString(var.bstrVal);

						//  2012/05/04.这里缺少一个判断,就是可能视频设备超过了rgpmVideoMenu[].一般没有这么多.
						//  暂时不解决
						//  ASSERT(gcap.rgpmVideoMenu[uIndex] == 0);
						MACRO_qyAssert(  gcap.rgpmVideoMenu[uIndex]  ==  0,  _T(  ""  )  );
						gcap.rgpmVideoMenu[uIndex] = pM;
						pM->AddRef();
					}
					pBag->Release();
				}

				pM->Release();
				uIndex++;
			}
			pEm->Release();		
		}

		gcap.iNumVCapDevices = uIndex;


		// separate the video and audio devices
		AppendMenu(hMenuSub, MF_SEPARATOR, 0, NULL);

#if  10
		if  (  bIncludeACap  )  {

		// enumerate all audio capture devices
		uIndex = 0;
		bCheck = FALSE;

		ASSERT(pCreateDevEnum != NULL);

		hr = pCreateDevEnum->CreateClassEnumerator(CLSID_AudioInputDeviceCategory, &pEm, 0);
		if  (  hr  ==  S_OK  )  {
			pEm->Reset();

			while  (  hr = pEm->Next(1, &pM, &cFetched), hr==S_OK)  {
				   IPropertyBag *pBag;
				   hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
				   if(SUCCEEDED(hr))  {
					   VARIANT var;
					   var.vt = VT_BSTR;
					   hr = pBag->Read(L"FriendlyName", &var, NULL);
					   if  (  hr  ==  NOERROR  )  {
						   AppendMenu(hMenuSub, MF_STRING, ID_MENU_ADEVICE0 + uIndex,  var.bstrVal);



						   CheckMenuItem(hMenuSub,  ID_MENU_ADEVICE0 + uIndex,  (bCheck ? MF_CHECKED : MF_UNCHECKED));
						   EnableMenuItem(hMenuSub, ID_MENU_ADEVICE0 + uIndex,  (gcap.fCapturing ? MF_DISABLED : MF_ENABLED));
						   bCheck = FALSE;

						   SysFreeString(var.bstrVal);

						   ASSERT(gcap.rgpmAudioMenu[uIndex] == 0);
						   gcap.rgpmAudioMenu[uIndex] = pM;
						   pM->AddRef();
					   }
					   pBag->Release();
				   }
				   pM->Release();
				   uIndex++;
			}
			pEm->Release();
		}

		//  2013/03/19
		gcap.iNumACapDevices = uIndex;

		
		}

#endif

		pCreateDevEnum->Release(  );
	}

	//  2011/10/23
#if  10
	if  (  !bIncludeACap  )
	{
		//  2013/03/22
		list_devices_a(  TRUE,  &gcap.old_audioDevices  );
		
		if  (  !gcap.old_audioDevices.iNumADevices  )  {
			
			DYN_LIB_DX					*	pDynLibDx						=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;
		
			if  (  pDynLibDx->pDirectSoundCaptureEnumerateW  )  {
				COMMON_PARAM	commonParam;
				uIndex  =  0;
				MACRO_makeCommonParam3(  pCapParam,  hMenuSub,  &uIndex,  commonParam  );  
				pDynLibDx->pDirectSoundCaptureEnumerateW(  myDSEnumCallback,  (  LPVOID  )&commonParam  );

				gcap.old_audioDevices.iNumADevices  =  uIndex;
			}

		}

		//
		if  (  gcap.old_audioDevices.iNumADevices  )  {
			//  2014/07/31
			AppendMenu(  hMenuSub,  MF_STRING,  ID_MENU_selectDefaultRecorder,  getResStr(  0,  &pQyMc->cusRes,  ID_MENU_selectDefaultRecorder  )  );
			AppendMenu(hMenuSub, MF_SEPARATOR, 0, NULL);
			//
			for  (  uIndex  =  0;  uIndex  <  gcap.old_audioDevices.iNumADevices;  uIndex  ++  )  {
				OLD_audioDevice  *  pMem  =  &gcap.old_audioDevices.mems[uIndex];
				pMem->iMenuIds_audio  =  ID_MENU_ADEVICE0  +  uIndex;	
				 
				 if  (  hMenuSub  )  {
					 if  (  pMem->guid_audio  ==  gcap.old_audioDevices.default_guid_audio  )  {
						 TCHAR  tBuf[128];
						 //  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s (default)"  ),  pMem->names_audio  );
						 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s (%s)"  ),  pMem->names_audio,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_useDefault  )  );
						 AppendMenu(hMenuSub, MF_STRING, ID_MENU_ADEVICE0 + uIndex,  tBuf  );
						 }
					 else  {
						   AppendMenu(hMenuSub, MF_STRING, ID_MENU_ADEVICE0 + uIndex,  pMem->names_audio  );
					 }
				 }  
			}
		}

	}
#endif



	if  (  hWnd  )  {
		if  (  gcap.iNumVCapDevices  )  {
			AppendMenu(hMenuSub, MF_SEPARATOR, 0, NULL);
			AppendMenu(hMenuSub, MF_STRING, ID_MENU_cfgCaptureFilter_v,  getResStr(  0,  &pQyMc->cusRes,  ID_MENU_cfgCaptureFilter_v  )  );
			AppendMenu(hMenuSub, MF_STRING, ID_MENU_cfgCapturePin_v,  getResStr(  0,  &pQyMc->cusRes,  ID_MENU_cfgCapturePin_v  )  );
			#ifdef  __SUPPORT_cfgPreviewPin__
					AppendMenu(hMenuSub, MF_STRING, ID_MENU_cfgPreviewPin_v,  getResStr(  0,  &pQyMc->cusRes,  ID_MENU_cfgPreviewPin_v  )  );
			#endif
			AppendMenu(hMenuSub, MF_STRING, ID_MENU_cfgCrossBar_v,  getResStr(  0,  &pQyMc->cusRes,  ID_MENU_cfgCrossBar_v  )  );

		}
	}

	return;
}


//  2012/05/03
 void  addDevicesToMenu_shadow(  void  *  pCapParam,  BOOL  bIncludeACap,  HWND  hWnd  )
{
	if  (  !pCapParam  )  return;
	CAP_STUFF	&	gcap	=	*(  CAP_STUFF  *  )pCapParam;
	QY_MC		*	pQyMc	=	QY_GET_GBUF(  );


    UINT    uIndex			=	0;
    HMENU   hMenuSub		=	0;
    HRESULT hr				=	0;
    BOOL	bCheck			=	FALSE;

	if  (  hWnd  )  {
		hMenuSub = GetSubMenu(  ::GetMenu(  hWnd  ),  0  );        // Devices menu
		if  (  hMenuSub  )  {		//  2012/04/08. 墙上使用时,会没菜单

			// Clean the sub menu
			int iMenuItems = GetMenuItemCount(hMenuSub);
			if  (  iMenuItems == -1)  return;
    
			if  (  iMenuItems > 0)  {
				BOOL  bRet;
				for  (  int  i  =  0;  i  <  NUMELMS(  gcap.rgpmVideoMenu  );  i  ++  )  {
					 bRet  =  RemoveMenu(  hMenuSub,  ID_MENU_VDEVICE0  +  i,  MF_BYCOMMAND  );
				}
				for  (  int  i  =  0;  i  <  NUMELMS(  gcap.rgpmAudioMenu  );  i  ++  )  {
					 bRet  =  RemoveMenu(  hMenuSub,  ID_MENU_ADEVICE0  +  i,  MF_BYCOMMAND  );
				}
				//  2014/07/31
				bRet  =  RemoveMenu(  hMenuSub,  ID_MENU_selectDefaultRecorder,  MF_BYCOMMAND  );
				//
				bRet  =  RemoveMenu(  hMenuSub,  ID_MENU_cfgCaptureFilter_v,  MF_BYCOMMAND  );
				bRet  =  RemoveMenu(  hMenuSub,  ID_MENU_cfgCapturePin_v,  MF_BYCOMMAND  );
				#ifdef  __SUPPORT_cfgPreviewPin__
						bRet  =  RemoveMenu(  hMenuSub,  ID_MENU_cfgPreviewPin_v,  MF_BYCOMMAND  );
				#endif
				bRet  =  RemoveMenu(  hMenuSub,  ID_MENU_cfgCrossBar_v,  MF_BYCOMMAND  );			
			}

			//		
			iMenuItems = GetMenuItemCount(hMenuSub);
			if  (  iMenuItems  >  3  )  {
				UINT iState;
				int  nPos;
				int		i;
				for  (  i  =  0;  i  <  3;  i  ++  )  {
					 nPos  =  iMenuItems  -  1  -  i;
					 iState  =  GetMenuState(  hMenuSub,  nPos,  MF_BYPOSITION  );
					 if  (  !(  iState  &  MF_SEPARATOR  )  )  break;				 
					 RemoveMenu(  hMenuSub,  nPos,  MF_BYPOSITION  );				 
				}
			}

		}
	}


	//
	AppendMenu(hMenuSub, MF_SEPARATOR, 0, NULL);


	TCHAR			tName[MAX_monikerDisplayNameLen  +  1];

	//
	for  (  uIndex  =  0;  uIndex  <  gcap.iNumVCapDevices;  uIndex  ++  )  {

		 if  (  !gcap.rgpmVideoMenu[uIndex]  )  continue;
		 tName[0]  =  0;
		 getMonikerFriendlyName(  gcap.rgpmVideoMenu[uIndex],  tName,  mycountof(  tName  )  );

		 if  (  hWnd  )  {
			 AppendMenu(hMenuSub, MF_STRING, ID_MENU_VDEVICE0 + uIndex,  tName);

			 CheckMenuItem(hMenuSub,  ID_MENU_VDEVICE0 + uIndex,  (bCheck ? MF_CHECKED : MF_UNCHECKED));
			 EnableMenuItem(hMenuSub, ID_MENU_VDEVICE0 + uIndex,  (gcap.fCapturing ? MF_DISABLED : MF_ENABLED));
		 }

		 bCheck = FALSE;
	}
			
	// separate the video and audio devices	
	AppendMenu(hMenuSub, MF_SEPARATOR, 0, NULL);

	//  2013/03/19
	if  (  bIncludeACap  )  {

		//
		for  (  uIndex  =  0;  uIndex  <  gcap.iNumACapDevices;  uIndex  ++  )  {
			
			if  (  !gcap.rgpmAudioMenu[uIndex]  )  continue;	
			tName[0]  =  0;
			getMonikerFriendlyName(  gcap.rgpmAudioMenu[uIndex],  tName,  mycountof(  tName  )  );
			
			if  (  hWnd  )  {			
				AppendMenu(hMenuSub, MF_STRING, ID_MENU_ADEVICE0 + uIndex,  tName);
				
				CheckMenuItem(hMenuSub,  ID_MENU_ADEVICE0 + uIndex,  (bCheck ? MF_CHECKED : MF_UNCHECKED));
				EnableMenuItem(hMenuSub, ID_MENU_ADEVICE0 + uIndex,  (gcap.fCapturing ? MF_DISABLED : MF_ENABLED));
			}

			bCheck = FALSE;	
		}

	}


	//  2011/10/23
#if  10
	if  (  !bIncludeACap  )
	{
		unsigned  int  uCheck;

		//  2014/07/31
		AppendMenu(  hMenuSub,  MF_STRING,  ID_MENU_selectDefaultRecorder,  getResStr(  0,  &pQyMc->cusRes,  ID_MENU_selectDefaultRecorder  )  );
		AppendMenu(hMenuSub, MF_SEPARATOR, 0, NULL);
		
		//
		for  (  uIndex  =  0;  uIndex  <  gcap.old_audioDevices.iNumADevices;  uIndex  ++  )  {
			 OLD_audioDevice  *  pMem  =  &gcap.old_audioDevices.mems[uIndex];

			if  (  hMenuSub  )  {
				if  (  pMem->guid_audio  ==  gcap.old_audioDevices.default_guid_audio  )  {
					TCHAR  tBuf[128];
					//  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s (default)"  ),  pMem->names_audio  );
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s (%s)"  ),  pMem->names_audio,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_useDefault  )  );
					AppendMenu(hMenuSub, MF_STRING, ID_MENU_ADEVICE0 + uIndex,  tBuf  );
					}
				else  {
					  AppendMenu(hMenuSub, MF_STRING, ID_MENU_ADEVICE0 + uIndex,  pMem->names_audio);
				}

				//
				uCheck  =  MF_UNCHECKED;
#if  0
				if  (  !gcap.old_audioDevices.iMenuId_selectedAudio  )  uCheck  =  MF_UNCHECKED;
				else  uCheck  =  (  gcap.old_audioDevices.mems[uIndex].iMenuIds_audio  ==  gcap.old_audioDevices.iMenuId_selectedAudio  )  ?  MF_CHECKED  :  MF_UNCHECKED;
#endif

				CheckMenuItem(::GetMenu(  hWnd  ), ID_MENU_ADEVICE0 + uIndex,  uCheck  );
			  
			}
		}

	}
#endif



	if  (  hWnd  )  {
		if  (  gcap.iNumVCapDevices  )  {
			AppendMenu(hMenuSub, MF_SEPARATOR, 0, NULL);
			AppendMenu(hMenuSub, MF_STRING, ID_MENU_cfgCaptureFilter_v,  getResStr(  0,  &pQyMc->cusRes,  ID_MENU_cfgCaptureFilter_v  )  );
			AppendMenu(hMenuSub, MF_STRING, ID_MENU_cfgCapturePin_v,  getResStr(  0,  &pQyMc->cusRes,  ID_MENU_cfgCapturePin_v  )  );
			#ifdef  __SUPPORT_cfgPreviewPin__
					AppendMenu(hMenuSub, MF_STRING, ID_MENU_cfgPreviewPin_v,  getResStr(  0,  &pQyMc->cusRes,  ID_MENU_cfgPreviewPin_v  )  );
			#endif
			AppendMenu(hMenuSub, MF_STRING, ID_MENU_cfgCrossBar_v,  getResStr(  0,  &pQyMc->cusRes,  ID_MENU_cfgCrossBar_v  )  );


			#if  0
				 AppendMenu(hMenuSub, MF_SEPARATOR, 0, NULL);
				 AppendMenu(hMenuSub, MF_STRING, ID_MENU_notUseVfwWebcam,  getResStr(  0,  &pQyMc->cusRes,  ID_MENU_notUseVfwWebcam  )  );
				 AppendMenu(hMenuSub, MF_STRING, ID_MENU_useVfwWebcam,  getResStr(  0,  &pQyMc->cusRes,  ID_MENU_useVfwWebcam  )  );
		    #endif
		}
	}

	return;
}


//
 int  list_devices_v( OLD_videoDevices* pVideoDevices)
 {
	 HRESULT hr;
	 int uIndex = 0;

	 //
	 memset(pVideoDevices, 0, sizeof(pVideoDevices[0]));

	 // enumerate all video capture devices
	 ICreateDevEnum* pCreateDevEnum = 0;
	 hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
		 IID_ICreateDevEnum, (void**)&pCreateDevEnum);
	 if (SUCCEEDED(hr)) {

		 IEnumMoniker* pEm = 0;
		 ULONG				cFetched;
		 IMoniker* pM;

		 hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEm, 0);
		 if (hr == S_OK) {
			 pEm->Reset();

			 while (hr = pEm->Next(1, &pM, &cFetched), hr == S_OK) {
				 IPropertyBag* pBag = 0;

				 hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void**)&pBag);
				 if (SUCCEEDED(hr)) {
					 VARIANT var;
					 var.vt = VT_BSTR;
					 hr = pBag->Read(L"FriendlyName", &var, NULL);
					 if (hr == NOERROR) {


						 //  if  (  gcap.iMenuId_selectedVideo  ==  gcap.iMenuIds_video[uIndex]  )  bCheck = TRUE;
						 safeTcsnCpy(var.bstrVal, pVideoDevices->mems[uIndex].names_video, mycountof(pVideoDevices->mems[uIndex].names_video));
						 getMonikerDisplayName(pM, pVideoDevices->mems[uIndex].monikerDisplayName, mycountof(pVideoDevices->mems[uIndex].monikerDisplayName));

#if  0
						 if (hWnd) {
							 AppendMenu(hMenuSub, MF_STRING, ID_MENU_VDEVICE0 + uIndex, var.bstrVal);

							 CheckMenuItem(hMenuSub, ID_MENU_VDEVICE0 + uIndex, (bCheck ? MF_CHECKED : MF_UNCHECKED));
							 EnableMenuItem(hMenuSub, ID_MENU_VDEVICE0 + uIndex, (gcap.fCapturing ? MF_DISABLED : MF_ENABLED));
						 }
#endif

						 //bCheck = FALSE;

						 SysFreeString(var.bstrVal);

						 //  2012/05/04.这里缺少一个判断,就是可能视频设备超过了rgpmVideoMenu[].一般没有这么多.
						 //  暂时不解决
						 //  ASSERT(gcap.rgpmVideoMenu[uIndex] == 0);
#if  0
						 MACRO_qyAssert(gcap.rgpmVideoMenu[uIndex] == 0, _T(""));
						 gcap.rgpmVideoMenu[uIndex] = pM;
						 pM->AddRef();
#endif
					 }
					 pBag->Release();
				 }

				 pM->Release();
				 uIndex++;
			 }
			 pEm->Release();
		 }
	 }

		 pVideoDevices->iNumVDevices = uIndex;

		 return  0;
 }


#endif

	
 int  initCaptureGraphBuilder(  QMC_captureGraphBuilder  *  p,  void  *  pDebugStepParam  )
{
	int			iErr	=	-1;
	HRESULT		hr;
	MY_DEBUG_STEP	*	pDebugStep	=	(  MY_DEBUG_STEP  *  )pDebugStepParam;

	if  (  !p  )  return  -1;
	if  (  p->bInited  )  return  0;
	
	//  2012/03/21
	M_setMyStep(  pDebugStep,  300  );

	// ´´½¨ICaptureGraphBuilder2½Ó¿Ú
#if !defined(  __WINCE__  )  ||  defined(  __TEST__  )
	hr = CoCreateInstance(CLSID_CaptureGraphBuilder2 , NULL,
						CLSCTX_INPROC,
						IID_ICaptureGraphBuilder2, (void **)&p->m_pCapture);
	if  (  FAILED(  hr  )  )  goto  errLabel;
#else
	hr = CoCreateInstance(CLSID_CaptureGraphBuilder , NULL,
						CLSCTX_INPROC,
						IID_ICaptureGraphBuilder2, (void **)&p->m_pCapture);
	if  (  FAILED(  hr  )  )  goto  errLabel;
#endif

	// ´´½¨IGraphBuilder½Ó¿Ú
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, 
						CLSCTX_INPROC_SERVER,
						IID_IGraphBuilder, (void **)&p->m_pGB);
	if (  FAILED(  hr  )  )  goto  errLabel;


	// ³õÊ¼»¯ÂË²¨Æ÷Á´±í¹ÜÀíÆ÷IGraphBuilder
	hr  =  p->m_pCapture->SetFiltergraph(  p->m_pGB);
	if  (  FAILED(  hr  )  )  goto  errLabel;
	
	// ²éÑ¯Ã½Ìå¿ØÖÆ½Ó¿Ú
#if  10	// amcap中没有这个成员,是不是不应该保存, 而应该临时取得并立即释放. 2013/03/19
	hr  =  p->m_pGB->QueryInterface(IID_IMediaControl, (void **)&p->m_pMC);
	if  (  FAILED(  hr  )  )  goto  errLabel;
#endif
	
	//
	hr  =  p->m_pGB->QueryInterface(IID_IVideoWindow, (LPVOID *) &p->m_pVW);
	if  (  FAILED(  hr  )  )  goto  errLabel;
	
	p->bInited  =  TRUE;


	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		exitCaptureGraphBuilder(  p,  pDebugStep  );
	}

	return  iErr;
}

 int  exitCaptureGraphBuilder(  QMC_captureGraphBuilder  *  p,  void  *  pDebugStepParam  )
{
	MY_DEBUG_STEP	*	pDebugStep  =  (  MY_DEBUG_STEP  *  )pDebugStepParam;

	if  (  !p  )  return  -1;

	//
	M_setMyStep(  pDebugStep,  500  );

	//
	if  (  p->m_pMC  )  {
		HRESULT			hr;
		OAFilterState	fs;
		//
		M_setMyStep(  pDebugStep,  501  );
		//
		hr  =  p->m_pMC->GetState(  1000,  &fs  );
		//
		M_setMyStep(  pDebugStep,  502  );
		if  (  pDebugStep  )  {
			pDebugStep->fg.hr_GetState_beforeStop  =  hr;
			pDebugStep->fg.fs_beforeStop  =  fs;
			//
			#ifdef  __DEBUG__
					int  kk  =  State_Running;
			#endif

		}
		//
		if  (  p->bCalled_Run  )  {
			int  i;
			for  (  i  =  0;  !p->bFailed_FillBuffer  &&  i  <  50;  i  ++  )  {
				 Sleep(  100  );
			}
		}
		if  (  pDebugStep  )  {
			pDebugStep->fg.FillBuffer.bFailed  =  p->bFailed_FillBuffer;
		}
		//
		if  (  p->bCalled_Run  )  {
			p->m_pMC->Stop();
		}
	}

	//
	M_setMyStep(  pDebugStep,  501  );

	//
	if  (  p->m_pVW  )  {
		p->m_pVW->put_Visible(OAFALSE);
		p->m_pVW->put_Owner(NULL);
	}
	MACRO_safeRelease(  p->m_pME  );			//  2013/03/19
	MACRO_safeRelease(  p->m_pVW  );
	MACRO_safeRelease(  p->m_pMC  );
	MACRO_safeRelease(  p->m_pCapture);
	MACRO_safeRelease(  p->m_pGB  );
	MACRO_safeRelease(  p->m_pDecFilter  );		//  2009/04/10
	MACRO_safeRelease(  p->m_pMoniker  );		//  2009/08/16
	MACRO_safeRelease(  p->m_pBF  );
	MACRO_safeRelease(  p->m_pVSC);
	MACRO_safeRelease(  p->m_pASC  );			//  2013/03/19

	//
	M_setMyStep(  pDebugStep,  502  );

	//
	p->bInited  =  FALSE;

	return  0;
}



#if !defined(  __WINCE__  )  ||  defined(  __TEST__  )

#if  0	//  2013/03/19
 BOOL  bBindFilter(  IMoniker  *  pM_selected,  IMoniker  **  ppMoniker,  IBaseFilter  **  ppFilter  )
{

	BOOL	bRet	=	FALSE;

	//  if  (  deviceIndex  <  0  )  return  FALSE;

	// enumerate all video capture devices
	ICreateDevEnum	*	pCreateDevEnum;

	HRESULT  hr  =  CoCreateInstance(CLSID_SystemDeviceEnum, NULL, 
					CLSCTX_INPROC_SERVER,
					IID_ICreateDevEnum,
					(void**)&pCreateDevEnum);
	if  (  SUCCEEDED(  hr  )  )  {
		IEnumMoniker *pEm;

		hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,&pEm, 0);
		if  (  hr  ==  S_OK  )  {
			pEm->Reset();
			ULONG cFetched;
			IMoniker *pM;
			int index = 0;
			while  (  hr  =  pEm->Next(  1,  &pM,  &cFetched  ),  hr  ==  S_OK  )  {
				   IPropertyBag *pBag;
				   hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
				   if  (  SUCCEEDED(  hr  )  ) {
					   VARIANT var;
					   var.vt = VT_BSTR;
					   hr = pBag->Read(L"FriendlyName", &var, NULL);
					   if  (  hr  ==  NOERROR  )  {
						   if  (  !bRet  )  {
							   //  if  (  index  ==  deviceIndex  )  
							   if  (  !pM_selected  ||  S_OK  ==  pM_selected->IsEqual(  pM  )  )  
							   {
								   hr  =  pM->BindToObject(0, 0, IID_IBaseFilter, (void**)ppFilter);
								   if  (  !FAILED(  hr  )  )  {
									   *ppMoniker  =  pM;
									   pM->AddRef();
									   bRet  =  TRUE;
								   }
							   }
						   }
						   SysFreeString(var.bstrVal);
					   }			
					   pBag->Release();
				   }
				   pM->Release();
				   index++;
			}
			pEm->Release(  );
		}
		pCreateDevEnum->Release(  );
	}

	return  bRet;
}
#endif



#endif


 HRESULT myCopyMediaType(__out AM_MEDIA_TYPE *pmtTarget, const AM_MEDIA_TYPE *pmtSource)
{
    //  We'll leak if we copy onto one that already exists - there's one
    //  case we can check like that - copying to itself.
    ASSERT(pmtSource != pmtTarget);
    *pmtTarget = *pmtSource;
    if (pmtSource->cbFormat != 0) {
        ASSERT(pmtSource->pbFormat != NULL);
        pmtTarget->pbFormat = (PBYTE)CoTaskMemAlloc(pmtSource->cbFormat);
        if (pmtTarget->pbFormat == NULL) {
            pmtTarget->cbFormat = 0;
            return E_OUTOFMEMORY;
        } else {
            CopyMemory((PVOID)pmtTarget->pbFormat, (PVOID)pmtSource->pbFormat,
                       pmtTarget->cbFormat);
        }
    }
    if (pmtTarget->pUnk != NULL) {
        pmtTarget->pUnk->AddRef();
    }

    return S_OK;
}


 void myFreeMediaType(  AM_MEDIA_TYPE& mt)
{
    if (mt.cbFormat != 0)
    {
        CoTaskMemFree((PVOID)mt.pbFormat);
        mt.cbFormat = 0;
        mt.pbFormat = NULL;
    }
    if (mt.pUnk != NULL)
    {
        // Unecessary because pUnk should not be used, but safest.
        mt.pUnk->Release();
        mt.pUnk = NULL;
    }
}


 void WINAPI myDeleteMediaType(__inout_opt AM_MEDIA_TYPE *pmt)
{
    // allow NULL pointers for coding simplicity

    if (pmt == NULL) {
        return;
    }

    myFreeMediaType(*pmt);
    CoTaskMemFree((PVOID)pmt);
}

#ifdef  __WINCE__
#ifndef  __TEST__

 HRESULT  GetFirstCameraDriver( WCHAR *pwzName )
{
	HRESULT hr = S_OK;
	HANDLE	handle = NULL;
	DEVMGR_DEVICE_INFORMATION di;
	GUID guidCamera = { 0xCB998A05, 0x122C, 0x4166, 0x84, 0x6A, 0x93, 0x3E, 0x4D, 0x7E, 0x3C, 0x86 };
	// Note about the above: The driver material doesn't ship as part of the SDK. This GUID is hardcoded
	// here to be able to enumerate the camera drivers and pass the name of the driver to the video capture filter

	if( pwzName == NULL )
	{
		return E_POINTER;
	}

	di.dwSize = sizeof(di);

	handle = FindFirstDevice( DeviceSearchByGuid, &guidCamera, &di );
	if(( handle == NULL ) || ( di.hDevice == NULL ))
	{
		hr  =  HRESULT_FROM_WIN32( GetLastError() );
		goto  errLabel;
	}

	StringCchCopy( pwzName, MAX_PATH, di.szLegacyName );

errLabel:
	FindClose( handle );
	return hr;
}

#endif
#endif

////////////////////////////////////////////////////////////





 int  myChkFmt_v(  IAMStreamConfig  *  m_pVSC,  BITMAPINFOHEADER  *  pBih_suggested,  BOOL  &  bMatched,  AM_MEDIA_TYPE  &  mt_matched  )
{
	int					iErr		=	-1;
	BOOL				bNeedSet	=	TRUE;
	HRESULT				hr;

	if  (  !pBih_suggested  )  return  -1;

	//  2014/04/26
	if  (  !pBih_suggested->biWidth  ||  !pBih_suggested->biHeight  )  return  0;

	//
	if  (  m_pVSC  )  {
		AM_MEDIA_TYPE	*	pmt;

		hr  =  m_pVSC->GetFormat(  &pmt  );
		if  (  SUCCEEDED(  hr  )  )  {

			traceLog((TCHAR*)  _T(  "subtype %s"  ),  getMediaSubtypeName(  pmt->subtype  )  );

			if  (  pmt->majortype  ==  MEDIATYPE_Video
				&&  pmt->formattype  ==  FORMAT_VideoInfo
					&&  pmt->cbFormat  >=  sizeof(  VIDEOINFOHEADER  )  
						&&  pmt->pbFormat  )
			{
				VIDEOINFOHEADER  *  pVih  =  (  VIDEOINFOHEADER  *  )pmt->pbFormat;
				if  (
					#if  0
						pmt->subtype  ==  MEDIASUBTYPE_YUY2  
					||  pmt->subtype  ==  MEDIASUBTYPE_MJPG  
					||  pmt->subtype  ==  MEDIASUBTYPE_YV12
					||  pmt->subtype  ==  WMCMEDIASUBTYPE_I420
					||  pmt->subtype  ==  MEDIASUBTYPE_RGB565
					||  pVih->bmiHeader.biCompression  ==  BI_RGB  
					#endif
					bSubtypeGrabbable(  pmt->subtype  )
					)  
				{
					if  (  pBih_suggested  &&  pBih_suggested->biWidth  &&  pBih_suggested->biHeight  )  {
						BOOL  bMatched_biCompression  =  FALSE;
						if  (  !pBih_suggested->biCompression  )  bMatched_biCompression  =  TRUE;
						else  {
							  FOURCCMap  map(  pBih_suggested->biCompression  );									
							  if  (  map  ==  pmt->subtype  )  bMatched_biCompression  =  TRUE;
						}
						if  (  bMatched_biCompression  )  {
							#if  0	//  2014/12/24
								 if  (  pVih->bmiHeader.biWidth  ==  pBih_suggested->biWidth  )  bNeedSet  =  FALSE;				
							#endif
							if  (  pVih->bmiHeader.biHeight  ==  pBih_suggested->biHeight  )  bNeedSet  =  FALSE;
						}
						}
					else  
						bNeedSet  =  FALSE;
				}
			}
			myDeleteMediaType(  pmt  );
		}		
	}
	
	if  (  bNeedSet  &&  m_pVSC  )  {
		int		iCount  =  0,  iSize  =  0;
		int		i;

		traceLogA(  (char*)  "initVideoCapDev_dx: need to set capture bmp"  );

		hr  =  m_pVSC->GetNumberOfCapabilities(  &iCount,  &iSize  );
		if  (  SUCCEEDED(  hr  )  )  {
			VIDEO_STREAM_CONFIG_CAPS		scc;
			AM_MEDIA_TYPE				*	pmtConfig;
			for  (  i  =  0;  i  <  iCount  &&  bNeedSet;  i  ++  )  {
				hr  =  m_pVSC->GetStreamCaps(  i,  &pmtConfig,  (  BYTE  *  )&scc  );
				if  (  SUCCEEDED(  hr  )  )  {
					//  pmtcon
					printDmoMediaType(  i,  pmtConfig  );

					if  (  pmtConfig->majortype  ==  MEDIATYPE_Video  
						&&  pmtConfig->formattype  ==  FORMAT_VideoInfo  
							&&	pmtConfig->cbFormat  >=  sizeof(  VIDEOINFOHEADER  )
								&&  pmtConfig->pbFormat  )				
					{
						VIDEOINFOHEADER	*	pvih	=	(  VIDEOINFOHEADER  *  )pmtConfig->pbFormat;
						BOOL				bOk		=	FALSE;

						if  (  
							#if  0
								pmtConfig->subtype  ==  MEDIASUBTYPE_YUY2  
							||  pmtConfig->subtype  ==  MEDIASUBTYPE_MJPG 
							||  pmtConfig->subtype  ==  MEDIASUBTYPE_YV12
							||  pmtConfig->subtype  ==  WMCMEDIASUBTYPE_I420
							||  pmtConfig->subtype  ==  MEDIASUBTYPE_RGB565
							||  pvih->bmiHeader.biCompression  ==  BI_RGB  
							#endif
							bSubtypeGrabbable(  pmtConfig->subtype  )
							)  
						{
							if  (  pBih_suggested  &&  pBih_suggested->biWidth  &&  pBih_suggested->biHeight  )  {
								BOOL  bMatched_biCompression  =  FALSE;
								if  (  !pBih_suggested->biCompression  )  bMatched_biCompression  =  TRUE;
								else  {
									  FOURCCMap	map(  pBih_suggested->biCompression  );
									  if  (  map  ==  pmtConfig->subtype  )  bMatched_biCompression  =  TRUE;
								}
								if  (  bMatched_biCompression  )  {
									if  (  //  pvih->bmiHeader.biWidth  ==  pBih_suggested->biWidth  &&  
										pvih->bmiHeader.biHeight  ==  pBih_suggested->biHeight  
										)  
									{
										bOk  =  TRUE;
									}
								}
								}
							else							
								bOk  =  TRUE;
						}

						if  (  bOk  )  {
							#if  1  //  ndef  __DEBUG__
									 hr  =  m_pVSC->SetFormat(  pmtConfig  );	
							#endif

							//  2011/09/02. 将选中的类型从此函数中带出，方便sampleGrabber设置
							bMatched  =  TRUE;								//  
							myCopyMediaType(  &mt_matched,  pmtConfig  );

							//
							#ifdef  __DEBUG__
									char  fourccStr[16]	=	"";
									iFourcc2Str(  pvih->bmiHeader.biCompression,  fourccStr,  mycountof(  fourccStr  )  );
									if  (  FAILED(  hr  )  )  {  
										traceLogA(  (char*)  "initVideoCapDev_dx: SetFormat failed, hr %x. %s, w %d,  h %d",  hr,  fourccStr,  pvih->bmiHeader.biWidth,  pvih->bmiHeader.biHeight  );
										}
									else  
										traceLogA(  (char*)  "initVideoCapDev_dx: cap bmp is set. %s, w %d,  h %d",  fourccStr,  pvih->bmiHeader.biWidth,  pvih->bmiHeader.biHeight  );
							#endif
							//
							bNeedSet  =  FALSE;
						}
					}					
					myDeleteMediaType(  pmtConfig  );
				}
			}
		}
	}

	iErr  =  0;

	return  iErr;
}



 //  2011/09/01
 int  initVideoCapDev_dx(  void  *  p_reserved,  LPCTSTR  displayName_selected,  void  **  ppCapStuff,  BITMAPINFOHEADER  *  pBih_suggested,  BOOL  bForConfig,  HWND hWnd_notify,  LONG_PTR lInstanceData,  void  **  ppVideoCapDevParam  )
{
	int								iErr	=	-1;
	HRESULT							hr;
	VIDEO_capDev_dx				*	p		=	NULL;

	IMoniker					*	pMoniker	=	NULL;

	BOOL							bMatched  =  FALSE;
	AM_MEDIA_TYPE					mt_matched;
	memset(  &mt_matched,  0,  sizeof(  mt_matched  )  );

	
	if  (  !ppVideoCapDevParam  )  return  -1;
	if  (  *ppVideoCapDevParam  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initVideoCapDev_dx failed, *ppVideoCapDevParam is not null"  )  );
		return  -1;
	}
	
	p  =  (  VIDEO_capDev_dx  *  )mymalloc(  sizeof(  VIDEO_capDev_dx  )  );
	if  (  !p  )  goto  errLabel;
	memset(  p,  0,  sizeof(  VIDEO_capDev_dx  )  );

	if  (  !ppCapStuff  )  {
		p->p_gcap  =  CAP_STUFF_new(  );
		if  (  !p->p_gcap  )  goto  errLabel;

	}
	else  {
		  p->p_gcap  =  *ppCapStuff;	*ppCapStuff  =  NULL;		//  这里pCapStuff被转交
	}
	if  (  !p->p_gcap  )  goto  errLabel;


	{

		AV_capStuff& gcap = *(AV_capStuff*)p->p_gcap;


		// get the frame rate from win.ini before making the graph
		gcap.fUseFrameRate = 1;		//  GetProfileInt(TEXT("annie"), TEXT("UseFrameRate"), 1);
		int units_per_frame; units_per_frame = 666667;	//  GetProfileInt(TEXT("annie"), TEXT("FrameRate"), 666667);  // 15fps
		gcap.FrameRate = 10000000. / units_per_frame;
		gcap.FrameRate = (int)(gcap.FrameRate * 100) / 100.;

		// reasonable default
		if (gcap.FrameRate <= 0.)
			gcap.FrameRate = 15.0;

#ifdef  __DEBUG__
		//  gcap.FrameRate  =  8;
#endif

#if !defined(  __WINCE__  )  ||  defined(  __TEST__  )

		if (!ppCapStuff) {
			if (getMonikerByDisplayName(displayName_selected, (void**)&pMoniker)
				|| !pMoniker)
			{
#ifdef  __DEBUG__
				traceLogA((char*)"openLocalVideo failed:  pMoniker null");
#endif
				goto  errLabel;
			}
		}
		else {
			if (displayName_selected && displayName_selected[0]) {
				if (getMonikerByDisplayName(displayName_selected, (void**)&pMoniker)
					|| !pMoniker)
				{
#ifdef  __DEBUG__
					traceLogA((char*)"openLocalVideo failed:  pMoniker null");
#endif
					goto  errLabel;
				}
			}
			else {
				pMoniker = gcap.pmVideo;
				if (!pMoniker) {
#ifdef  __DEBUG__
					traceLog((TCHAR*)_T("initVideoCap_dx failed, pMoniker is null"));
#endif
					goto  errLabel;
				}
				pMoniker->AddRef();
			}
		}

		//  if  (  !bBindFilter(  (  IMoniker  *  )pMoniker, &p->m_captureGraphBuilder.m_pMoniker,  &p->m_captureGraphBuilder.m_pBF  )  )  goto  errLabel;

		IMoniker* pmVideo; pmVideo = NULL;
		IMoniker* pmAudio; pmAudio = NULL;
		pmVideo = pMoniker;

		// they chose a new device. rebuild the graphs
		if (gcap.pmVideo != pmVideo || gcap.pmAudio != pmAudio)
		{
			if (pmVideo)
			{
				pmVideo->AddRef();
			}
			if (pmAudio)
			{
				pmAudio->AddRef();
			}

			IMonRelease(gcap.pmVideo);
			IMonRelease(gcap.pmAudio);
			gcap.pmVideo = pmVideo;
			gcap.pmAudio = pmAudio;

			if (gcap.fPreviewing)
				StopPreview(gcap);
			if (gcap.fCaptureGraphBuilt || gcap.fPreviewGraphBuilt)
				TearDownGraph(gcap);

			FreeCapFilters(gcap);
			InitCapFilters(gcap);

		}



#else
		{
			CComPtr<IBaseFilter>			m_pVideoCaptureFilter;
			CComPtr<IPersistPropertyBag>    pPropertyBag;

			CComVariant   varCamName;
			CPropertyBag  PropBag;
			//  OAEVENT       oaEvent;
			WCHAR	      wzDeviceName[MAX_PATH + 1];

			hr = m_pVideoCaptureFilter.CoCreateInstance(CLSID_VideoCapture);
			if (FAILED(hr))  goto  errLabel;
			hr = m_pVideoCaptureFilter.QueryInterface(&pPropertyBag);
			if (FAILED(hr))  goto  errLabel;


			hr = (GetFirstCameraDriver(wzDeviceName));
			if (FAILED(hr))  goto  errLabel;
			varCamName = wzDeviceName;
			if (varCamName.vt != VT_BSTR) {
				hr = E_OUTOFMEMORY;
				goto  errLabel;
			}

			hr = PropBag.Write(L"VCapName", &varCamName);
			if (FAILED(hr))  goto  errLabel;

			hr = pPropertyBag->Load(&PropBag, NULL);
			if (FAILED(hr))  goto  errLabel;

			p->m_pBF = m_pVideoCaptureFilter;
			p->m_pBF->AddRef();

		}
#endif




#if  10  //  ndef  __DEBUG__


		//  2012/02/17
		if (!gcap.pBuilder) {
			qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("initVideoCapDev_dx failed, pBuilder is null"));
			goto  errLabel;
		}

		{

			//
			IAMStreamConfig* m_pVSC = gcap.pVSC;				//  for video cap
			IGraphBuilder* m_pGB = gcap.pFg;
			IBaseFilter* m_pBF = gcap.pVCap;
			ICaptureGraphBuilder2* m_pCapture = (ICaptureGraphBuilder2*)get_ICaptureGraphBuilder(gcap.pBuilder);
			IBaseFilter* m_pDecFilter = NULL;		//  for mjpg. 2009/04/10

			//  2012/02/17
			if (!m_pCapture) {
				qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("initVideoCapDev_dx failed, m_pCapture is null"));
				goto  errLabel;
			}


			//
			BOOL	bConnectDirectly; bConnectDirectly = FALSE;
			//
			if (!bForConfig) {

				myChkFmt_v(m_pVSC, pBih_suggested, bMatched, mt_matched);

				//  2009/04/10
				if (m_pVSC) {
					AM_MEDIA_TYPE* pmt;
					hr = m_pVSC->GetFormat(&pmt);
					if (SUCCEEDED(hr)) {

#ifdef  __DEBUG__
						traceLog((TCHAR*)_T("initVideoCapDev_dx: output %s"), getMediaSubtypeName(pmt->subtype));
#endif
						qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("Video capture: output %s"), getMediaSubtypeName(pmt->subtype));

						if (bSubtypeGrabbable(pmt->subtype))  bConnectDirectly = TRUE;

#if  0
						if (pmt->subtype == MEDIASUBTYPE_MJPG) {
							//  CLSID_MjpegDec
							hr = CoCreateInstance(CLSID_MjpegDec, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&p->m_captureGraphBuilder.m_pDecFilter);
							if (FAILED(hr))  goto  errLabel;
							hr = p->m_captureGraphBuilder.m_pGB->AddFilter(p->m_captureGraphBuilder.m_pDecFilter, _T("mjpeg decoder"));
							if (FAILED(hr))  goto  errLabel;
						}
#endif
						myDeleteMediaType(pmt);
					}
				}

				//
#ifndef  __SUPPORT_CUS_sampleGrabber__
				hr = CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&p->video.m_pGrabberFilter);
				if (FAILED(hr)) {
					qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("initVideoCapDev_dx failed, sampleGrabber failed"));
					goto  errLabel;
				}
#else
				if (myGetNewFilter(g_pEnv, CLSID_SampleGrabber_is, 0, (void**)&p->video.m_pGrabberFilter)) {
#ifdef  __DEBUG__
					traceLog((TCHAR*)_T("initVideoCapDev_dx failed, myGetNewFilter, sampleGrabber_is failed"));
#endif
					qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("initVideoCapDev_dx failed, myGetNewFilter, sampleGrabber_is failed"));
					//
					goto  errLabel;
				}
#endif

				hr = m_pGB->AddFilter(p->video.m_pGrabberFilter, _T("Sample Grabber"));
				if (FAILED(hr)) {
					qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("initVideoCapDev_dx failed, addFilter, sampleGrabber failed"));
					goto  errLabel;
				}

#ifndef  __SUPPORT_CUS_sampleGrabber__
				hr = p->video.m_pGrabberFilter->QueryInterface(IID_ISampleGrabber, (void**)&p->video.m_pGrabber);
				if (FAILED(hr))  goto  errLabel;
#else
				hr = p->video.m_pGrabberFilter->QueryInterface(IID_ISampleGrabber_is, (void**)&p->video.m_pGrabber);
				if (FAILED(hr)) {
					qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("initVideoCapDev_dx failed, sampleGrabber queryInterface failed"));
					goto  errLabel;
				}
#endif

				if (bMatched) {
					hr = p->video.m_pGrabber->SetMediaType(&mt_matched);
				}
				else {
					DMO_MEDIA_TYPE	mt;
					memset(&mt, 0, sizeof(mt));
					mt.majortype = MEDIATYPE_Video;
#ifdef  __DEBUG__
					//  mt.subtype  =  MEDIASUBTYPE_MJPG;
#endif

					hr = p->video.m_pGrabber->SetMediaType(&mt);
				}
				if (FAILED(hr)) {
					qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("initVideoCapDev_dx failed, sampleGrabber setMediaType failed"));
					goto  errLabel;
				}

#include	"unDeclareDebugNew.h"
				p->video.m_pCallBack = new  CMySampleGrabberCB;
#include	"declareDebugNew.h"
				if (!p->video.m_pCallBack)  goto  errLabel;

				//  set modes
				hr = p->video.m_pGrabber->SetBufferSamples(FALSE);
				if (FAILED(hr))  goto  errLabel;
				hr = p->video.m_pGrabber->SetCallback(p->video.m_pCallBack, 1);
				if (FAILED(hr))  goto  errLabel;

#ifndef  __SUPPORT_CUS_nullRenderer__
				hr = CoCreateInstance(CLSID_NullRenderer, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&p->video.m_pNullRenderer);
				if (FAILED(hr))  goto  errLabel;
#else
				if (myGetNewFilter(g_pEnv, CLSID_NullRenderer_is, 0, (void**)&p->video.m_pNullRenderer)) {
					qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("initVideoCapDev_dx failed, myGetNewFilter, nullRenderer failed"));
					goto  errLabel;
				}
#endif

				hr = m_pGB->AddFilter(p->video.m_pNullRenderer, L"Null  Renderer");
				if (FAILED(hr)) {
					qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("initVideoCapDev_dx failed, addFilter, nullRenderer failed"));
					goto  errLabel;
				}

				if (0  /*bConnectDirectly*/) {		//  2011/09/02, 直接连容易在1080p时，引起系统报警，性能紧张。所以不能使用

					hr = ConnectFilters(m_pGB, m_pBF, p->video.m_pGrabberFilter);
					if (FAILED(hr))  goto  errLabel;

					hr = ConnectFilters(m_pGB, p->video.m_pGrabberFilter, p->video.m_pNullRenderer);
					if (FAILED(hr))  goto  errLabel;

				}
				else {

					const GUID* pCategory = &PIN_CATEGORY_CAPTURE;
					hr = m_pCapture->RenderStream(pCategory, &MEDIATYPE_Interleaved, m_pBF, m_pDecFilter, p->video.m_pGrabberFilter);
					if (hr != S_OK) {
						hr = m_pCapture->RenderStream(pCategory, &MEDIATYPE_Video, m_pBF, m_pDecFilter, p->video.m_pGrabberFilter);
						if (hr != S_OK) {
#ifdef  __DEBUG__
							traceLogA((char*)"Can't build the graph");
							//  E_INVALIDARG 
#endif
							TCHAR  tBuf[128];  //  2017/09/19
							_sntprintf(tBuf, mycountof(tBuf), _T("initVideoCapDev_dx failed, renderStream bf->gb failed. hr 0x%x"), hr);
							//
							qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), tBuf);
							//
							showNotification(0, 0, 0, 0, 0, 0, tBuf);
							//
							goto  errLabel;
						}
					}
					hr = m_pCapture->RenderStream(NULL, NULL, p->video.m_pGrabberFilter, NULL, p->video.m_pNullRenderer);
					if (FAILED(hr)) {
						traceLogA((char*)"Can¡¯t build the graph");
						qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("initVideoCapDev_dx failed, renderStream gb->null failed"));
						goto  errLabel;
					}
				}

				//							
				qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("initVideoCapDev_dx: renderStream ok"));


#if  0
				AM_MEDIA_TYPE* pmt = 0;

				if (!gcap.fMPEG2)
				{
					hr = gcap.fUseFrameRate ? E_FAIL : NOERROR;
					if (gcap.pVSC && gcap.fUseFrameRate)
					{
						hr = gcap.pVSC->GetFormat(&pmt);

						// DV capture does not use a VIDEOINFOHEADER
						if (hr == NOERROR)
						{
							if (pmt->formattype == FORMAT_VideoInfo)
							{
								VIDEOINFOHEADER* pvi = (VIDEOINFOHEADER*)pmt->pbFormat;
								pvi->AvgTimePerFrame = (LONGLONG)(10000000 / gcap.FrameRate);
								hr = gcap.pVSC->SetFormat(pmt);
							}
							myDeleteMediaType(pmt);
						}
					}
					if (hr != NOERROR)
						ErrMsg_amCap(TEXT("Cannot set frame rate for capture"));
				}
#endif


				//
				if (IsWindow(hWnd_notify)) {
					if (!gcap.pME) {
						hr = gcap.pFg->QueryInterface(IID_IMediaEventEx, (void**)&gcap.pME);
						if (hr != NOERROR)  goto  errLabel;
					}

					// Have the graph signal event via window callbacks		
					hr = gcap.pME->SetNotifyWindow((OAHWND)hWnd_notify, CONST_qyWm_graphNotify_mediaDevice, lInstanceData);
				}


				// All done.
				gcap.fCaptureGraphBuilt = TRUE;


#ifdef  __DEBUG__
				//  myDumpGraph(  p->m_pGB,  6  );
#endif
				qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("Video capture: graph is ok"));

			}

		}

#endif

	}



	iErr  =  0;

errLabel:

	myFreeMediaType(  mt_matched  );

	MACRO_safeRelease(  pMoniker  );
	
	if  (  iErr  )  {
		exitVideoCapDev_dx(  (  void  **  )&p  );
	}
	if  (  !iErr  )  {
		*ppVideoCapDevParam  =  p;
	}

	return  iErr;
}


//
 int  exitVideoCapDev_dx(  void  **  ppVideoCapDevParam  )
{
	VIDEO_capDev_dx  *  p;

	if  (  !ppVideoCapDevParam  )  return  0;
	if  (  !*ppVideoCapDevParam  )  return  0;

	p  =  (  VIDEO_capDev_dx  *  )*ppVideoCapDevParam;
	
	//
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "exitVideoCapDev_dx enters"  )  );
	
	//
	p->bQuit  =  TRUE;
	if  (  p->pQ2  &&  p->bQInited  )  {
		q2PostMsgAndTrigger(  NULL,  0,  p->pQ2,  _T(  "exitVideoCapDev_dx"  ));
	}

#ifndef  __DEBUG__
	//  exitCaptureGraphBuilder(  &p->m_captureGraphBuilder  );
#endif

	// Destroy the filter graph and cleanup
#if  0
	StopPreview(p->gcap);
	StopCapture(p->gcap);
    TearDownGraph(p->gcap);
	FreeCapFilters(p->gcap);

	//  2011/09/02
	IMonRelease(p->gcap.pmVideo);
	IMonRelease(p->gcap.pmAudio);
#else
	CAP_STUFF_free(  p->p_gcap  );
#endif

	//
	MACRO_safeRelease(  p->video.m_pGrabber  );
	MACRO_safeRelease(  p->video.m_pGrabberFilter  );
	if  (  p->video.m_pCallBack  )  {
		MACRO_safeFree(  p->video.m_pCallBack->m_var.pMsgBuf  );
		delete  p->video.m_pCallBack;
	}

	MACRO_safeRelease(  p->video.m_pNullRenderer  );

	MACRO_safeFree(  p->pPkt  );
	if  (  p->pQ2  )  {
		if  (  p->bQInited  )  exitQyQ2(  p->pQ2  );
		free(  p->pQ2  );
	}

	free(  p  );
	*ppVideoCapDevParam  =  NULL;

	//
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "exitVideoCapDev_dx leaves"  )  );

	
	return  0;
}


int  handleGraphEvent_videoCapDev_dx(  void  *  pVideoCapDevParam  )
{
	VIDEO_capDev_dx  *  p  =  (  VIDEO_capDev_dx  *  )pVideoCapDevParam;

	if  (  !p  )  return  -1;
	if  (  !p->p_gcap  )  return  -1;
	AV_capStuff	&	gcap  =  *(  AV_capStuff  *  )p->p_gcap;

	if  (  gcap.pME  )
	{
                LONG event;
				LONG_PTR l1, l2;
                HRESULT hrAbort = S_OK;
                BOOL bAbort = FALSE;
                while(gcap.pME->GetEvent(&event, &l1, &l2, 0) == S_OK)
                {
                    gcap.pME->FreeEventParams(event, l1, l2);
					
					//  2014/08/01
					qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  "graphEvent_vCap"  ),  _T(  ""  ),  _T(  "event %d, l1 %d, l2 %d"  ),  event,  (  long  )l1,  (  long  )l2  );


					//
                    if(event == EC_ERRORABORT)
                    {
                        StopCapture(  gcap );
                        bAbort = TRUE;
                        hrAbort = static_cast<HRESULT>(l1);
                        continue;
                    }
                    else if(event == EC_DEVICE_LOST)
                    {
                            // Check if we have lost a capture filter being used.
                            // lParam2 of EC_DEVICE_LOST event == 1 indicates device added
                            //                                 == 0 indicates device removed
                            if(l2 == 0)
                            {
                                IBaseFilter *pf;
                                IUnknown *punk = (IUnknown *) l1;
                                if(S_OK == punk->QueryInterface(IID_IBaseFilter, (void **) &pf))
                                {
								#if  0
                                    if(AreComObjectsEqual(gcap.pVCap, pf))
                                    {
                                        pf->Release();
                                        bAbort = FALSE;
                                        StopCapture();
                                        TCHAR szError[100];
                                        HRESULT hr = StringCchCopy(szError, 100,
                                            TEXT("Stopping Capture (Device Lost). Select New Capture Device\0"));
                                        ErrMsg(szError);
                                        break;
                                    }
								#endif
                                    pf->Release();
									StopCapture(  gcap  );	//  2014/08/01
                                }
                            }
                    }


                } // end while
                if(bAbort)
                {
					#if  0
                        if(gcap.fWantPreview)
                        {
                            BuildPreviewGraph();
                            StartPreview();
                        }
                        TCHAR szError[100];
                        HRESULT hr = StringCchPrintf(szError, 100, TEXT("ERROR during capture, error code=%08x\0"), hrAbort);
                        ErrMsg(szError);
					#endif
                }
            }



	return  0;
}


//  #define	exitFilterGraph(  ppFilterGraph  )	exitVideoCapDev_dx(  ppFilterGraph  )
  int  exitFilterGraph(  void  **  ppVideoCapDevParam,  void  *  pDebugStepParam  )
{
	QMC_FILTER_GRAPH  *  p;

	//
	if  (  !ppVideoCapDevParam  )  return  0;
	if  (  !*ppVideoCapDevParam  )  return  0;

	p  =  (  QMC_FILTER_GRAPH  *  )*ppVideoCapDevParam;
	MY_DEBUG_STEP	*	pDebugStep  =  (  MY_DEBUG_STEP  *  )pDebugStepParam;

	//
	MACRO_qyAssert(  pDebugStepParam,  _T(  "Invalid, pDebugStep is null"  )  );

	//  2012/03/20
	MACRO_setMyStep(  *pDebugStep,  300  );
	if  (  pDebugStep  )  pDebugStep->fg.dwTickCnt_startToQuit  =  GetTickCount(  );

	//
	p->bQuit  =  TRUE;
	if  (  p->pQ2  &&  p->bQInited  )  {
		q2PostMsgAndTrigger(  NULL,  0,  p->pQ2,  _T(  "exitFilterGraph"  ));
	}

	//  2012/03/20
	MACRO_setMyStep(  *pDebugStep,  301  );  

	//
	exitCaptureGraphBuilder(  &p->m_captureGraphBuilder,  pDebugStep  );


	//  2012/03/20
	MACRO_setMyStep(  *pDebugStep,  302  );  

	//
	MACRO_safeRelease(  p->m_pGrabber  );
	MACRO_safeRelease(  p->m_pGrabberFilter  );
	if  (  p->m_pCallBack  )  {
#if  0
		MACRO_safeFree(  p->m_pCallBack->m_var.pBuf  );
#endif
		MACRO_safeFree(  p->m_pCallBack->m_var.pMsgBuf  );
		delete  p->m_pCallBack;
	}

	MACRO_safeRelease(  p->m_pNullRenderer  );

	MACRO_safeFree(  p->pPkt  );
	if  (  p->pQ2  )  {
		if  (  p->bQInited  )  exitQyQ2(  p->pQ2  );
		free(  p->pQ2  );
	}

	free(  p  );
	*ppVideoCapDevParam  =  NULL;

	return  0;
}


 int  printDmoMediaType(  int  index,  DMO_MEDIA_TYPE  *  pMt  )
{
	int		iErr			=	-1;
	TCHAR	szID[128]		=	_T(  ""  );
	TCHAR	tDesc[128]		=	_T(  ""  );

#ifndef  __DEBUG__
		return  0;
#endif
	
	if  (  pMt->majortype  ==  MEDIATYPE_Video  )  {
		if  (  pMt->subtype  ==  MEDIASUBTYPE_YUY2  )  {
			lstrcpyn(  szID,  _T(  "yuy2"  ),  mycountof(  szID  )  );
			}
		else  if  (  pMt->subtype  ==  MEDIASUBTYPE_MJPG  )  {
				  lstrcpyn(  szID,  _T(  "mjpg"  ),  mycountof(  szID  )  );
				  }
		else  {
			  StringFromGUID2(  pMt->subtype,  szID,  mycountof(  szID  )  );
		}

		if  (  pMt->formattype  ==  FORMAT_VideoInfo  )  {
			if  (  NULL  ==  pMt->pbFormat  ||  pMt->cbFormat  <  sizeof(  VIDEOINFOHEADER  )  )  goto  errLabel;
			VIDEOINFO  *	pVih			=	(  VIDEOINFO  *  )pMt->pbFormat;
			char			fourccStr[16]	=	"";

			iFourcc2Str(  pVih->bmiHeader.biCompression,  fourccStr,  mycountof(  fourccStr  )  );
			_sntprintf(  tDesc,  mycountof(  tDesc  ),  _T(  "%S, w %d, h %d"  ),  fourccStr,  pVih->bmiHeader.biWidth,  pVih->bmiHeader.biHeight  );
		}
	}
	if  (  pMt->majortype  ==  MEDIATYPE_Audio  )  {
		if  (  pMt->subtype  ==  MEDIASUBTYPE_PCM  )  {
			lstrcpyn(  szID,  _T(  "pcm"  ),  mycountof(  szID  )  );
			}
		else  {
			  StringFromGUID2(  pMt->subtype,  szID,  mycountof(  szID  )  );
		}

		//
		if  (  pMt->formattype  ==  FORMAT_WaveFormatEx  )  {
			if  (  !pMt->pbFormat  ||  pMt->cbFormat  <  sizeof(  WAVEFORMATEX  )  )  goto  errLabel;
			WAVEFORMATEX  *  pWf  =  (  WAVEFORMATEX  *  )pMt->pbFormat;

			_sntprintf(  tDesc,  mycountof(  tDesc  ),  _T(  "nChan %d,nSamples %d,nAvg %d,wBits %d,nBlock %d"  ),  pWf->nChannels,  pWf->nSamplesPerSec,  pWf->nAvgBytesPerSec,  pWf->wBitsPerSample,  pWf->nBlockAlign  );


		
		}

	}

	traceLogA(  (char*)  "dmoMediaTypes[%d]: subType %S, %S",  index,  szID,  tDesc  );

	iErr  =  0;

errLabel:

	return  0;
}



 
	//  2011/09/01
  BOOL  bGetCapturePara_dx(  void  *  pProcInfo,  int  iIndex_capBmp,  PF_BufferCB_av  pf,  unsigned  int  uiBufSize_pMsgBuf,  void  *  pVideoCapDevParam,  QY_VIDEO_HEADER  *  pVh_org  )
{
	BOOL					bRet	=	FALSE;
	HRESULT					hr;
	//  if  (  !pVc  )  return  FALSE;
	VIDEO_capDev_dx		*	p		=	(  VIDEO_capDev_dx  *  )pVideoCapDevParam;
	DMO_MEDIA_TYPE			mt;
	BOOL					bMtGot	=	FALSE;

	if  (  !p  )  return  FALSE;
	if  (  !pVh_org  )  return  FALSE;
	//
	if  (  !p->video.m_pGrabber  )  return  FALSE;

	//
	hr  =  p->video.m_pGrabber->GetConnectedMediaType(  &mt  );
	if  (  FAILED(  hr  )  )  goto  errLabel;
	bMtGot  =  TRUE;

	if  (  mt.majortype  !=  MEDIATYPE_Video  )  goto  errLabel;
#ifdef  __DEBUG__
	traceLogA(  (char*)  "bSetCapturePara_dx: mediaSubtype: %S",  getMediaSubtypeName(  mt.subtype  )  );
#endif

	//
	if  (  mt.formattype  !=  FORMAT_VideoInfo  ) goto  errLabel;
    if  (  NULL  ==  mt.pbFormat  ||  mt.cbFormat  <  sizeof(  VIDEOINFOHEADER  )  )  goto  errLabel;

	VIDEOINFO* pVih; pVih = (VIDEOINFO*)mt.pbFormat;
 
	//  2017/09/13  
	memset(  pVh_org,  0,  sizeof(  pVh_org[0]  )  );
	//
	memcpy(  &pVh_org->bih,  &pVih->bmiHeader,  sizeof(  pVh_org->bih  )  );
	
#ifdef  __DEBUG__
		if  (  pVh_org->bih.biHeight  <  0  )  {
			traceLog((TCHAR*)  _T(  "Note: bGetCapturePara_dx, biHeight < 0"  )  );
		}
#endif

	//  2010/06/03
	if  (  mt.subtype  ==  MEDIASUBTYPE_RGB32
		&&  pVh_org->bih.biCompression  )  
	{
		makeBmpInfoHeader_rgb(  32,  pVih->bmiHeader.biWidth,  pVih->bmiHeader.biHeight,  &pVh_org->bih  );
	}
	if  (  mt.subtype  ==  MEDIASUBTYPE_YUY2  )  {	//  2010/06/07
		if  (  pVh_org->bih.biCompression  !=  CONST_fourcc_YUY2  )  pVh_org->bih.biCompression  =  CONST_fourcc_YUY2;
		if  (  pVh_org->bih.biHeight  <  0  )  pVh_org->bih.biHeight  =  -1  *  pVh_org->bih.biHeight;
	}
	if  (  mt.subtype  ==  MEDIASUBTYPE_YV12  )  {
		if  (  pVh_org->bih.biCompression  !=  CONST_fourcc_YV12  )  pVh_org->bih.biCompression  =  CONST_fourcc_YV12;
		if  (  pVh_org->bih.biHeight  <  0  )  pVh_org->bih.biHeight  =  -1  *  pVh_org->bih.biHeight;
	}
	if  (  mt.subtype  ==  WMCMEDIASUBTYPE_I420  )  {
		if  (  pVh_org->bih.biCompression  !=  CONST_fourcc_I420  )  pVh_org->bih.biCompression  =  CONST_fourcc_I420;
		if  (  pVh_org->bih.biHeight  <  0  )  pVh_org->bih.biHeight  =  -1  *  pVh_org->bih.biHeight;
	}
	if  (  mt.subtype  ==  MEDIASUBTYPE_RGB565  )  {
		if  (  sizeof(  pVih->bmiHeader  )  +  sizeof(  pVih->dwBitMasks  )  >  sizeof(  pVh_org[0]  )  )  goto  errLabel;
		memcpy(  pVh_org,  &pVih->bmiHeader,  sizeof(  pVih->bmiHeader  )  +  sizeof(  pVih->dwBitMasks  )  );
		//
#ifdef  BI_SRCPREROTATE
		pVh_org->bih.biCompression  &=  ~BI_SRCPREROTATE;
#else
		pVh_org->bih.biCompression  =  BI_BITFIELDS;
#endif
	}
	//  2014/06/17
	if  (  mt.subtype  ==  MEDIASUBTYPE_MJPG  )  {
#if  0
		showNotification(  0,  0,  0,  0,  0,  0,  _T(  "mjpg not supported"  )  );
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bGetCapPara_dx failed, mpjg not supported"  )  );

		//
		goto  errLabel;
#endif
		//

	}

	//
	p->video.m_pCallBack->m_var.pProcInfo  =  (  MC_VAR_common  *  )pProcInfo;
	p->video.m_pCallBack->m_var.uiCapType  =  CONST_capType_av;
	p->video.m_pCallBack->m_var.iIndex_capProcInfo  =  iIndex_capBmp;
	p->video.m_pCallBack->m_var.pf_BufferCB  =  pf;
	p->video.m_pCallBack->m_var.uiBufSize_pMsgBuf  =  uiBufSize_pMsgBuf;
	if  (  p->video.m_pCallBack->m_var.uiBufSize_pMsgBuf  )  {
		p->video.m_pCallBack->m_var.pMsgBuf  =  mymalloc(  p->video.m_pCallBack->m_var.uiBufSize_pMsgBuf  );
		if  (  !p->video.m_pCallBack->m_var.pMsgBuf  )  goto  errLabel;
	}
#if  0
	p->m_pCallBack->m_var.uiBufSize_pBuf  =  uiBufSize_pBuf;
	if  (  p->m_pCallBack->m_var.uiBufSize_pBuf  )  {
		p->m_pCallBack->m_var.pBuf  =  (  BYTE  *  )mymalloc(  p->m_pCallBack->m_var.uiBufSize_pBuf  );
		if  (  !p->m_pCallBack->m_var.pBuf  )  goto  errLabel;
	}
#endif


#ifdef  __DEBUG__
		iFourcc2Str(  pVh_org->bih.biCompression,  0,  0  );
#endif


	bRet  =  TRUE;

errLabel:

	if  (  bMtGot  )  myFreeMediaType(  mt  );

	return  bRet;
}




 int  startCapture_dx(  void  *  pVideoCapDevParam  )
{
	int						iErr	=	-1;
	HRESULT					hr;
	VIDEO_capDev_dx		*	p		=	(  VIDEO_capDev_dx  *  )pVideoCapDevParam;
	if  (  !p  )  return  -1;

	AV_capStuff  &  gcap  =  *(  AV_capStuff  *  )p->p_gcap;

#if  0  //ndef  __DEBUG__
	if  (  !p->m_captureGraphBuilder.bInited  )  return  -1;

	hr  =  p->m_captureGraphBuilder.m_pMC->Run(  );
	if  (  FAILED(  hr  )  )  goto  errLabel;
#endif

	// run the graph
    IMediaControl *pMC = NULL;
	hr = gcap.pFg->QueryInterface(IID_IMediaControl, (void **)&pMC);
    if(SUCCEEDED(hr))
    {
        hr = pMC->Run();
        if(FAILED(hr))
        {
			TCHAR	tBuf[128]	=	_T(  ""  );
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "startCapture_dx,IMediaControl.run failed,hr 0x%x"  ),  hr  );
			#ifdef  __DEBUG__
					traceLog((TCHAR*)  _T(  "%s"  ),  tBuf  );
			#endif
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Cap, run failed, 0x%x"  ),  hr  );
			showNotification(  NULL,  NULL,  NULL,  0,  0,  0,  tBuf  );

            // stop parts that ran
            pMC->Stop();
        }
        pMC->Release();
    }
    if(FAILED(hr))
    {
		goto  errLabel;
    }

	iErr  =  0;
errLabel:
	return  iErr;
}



  int  stopCapture_dx(  void  *  pVideoCapDevParam  )
{
	int						iErr	=	-1;
	HRESULT					hr;
	VIDEO_capDev_dx		*	p		=	(  VIDEO_capDev_dx  *  )pVideoCapDevParam;
	if  (  !p  )  return  -1;

	AV_capStuff  &  gcap  =  *(  AV_capStuff  *  )p->p_gcap;

#if  0  //  ndef  __DEBUG__
	if  (  !p->m_captureGraphBuilder.bInited  )  return  -1;

	if  (  p->m_captureGraphBuilder.m_pMC  )  {
		hr  =  p->m_captureGraphBuilder.m_pMC->Stop();
		if  (  FAILED(  hr  )  )  goto  errLabel;
	}
#endif

	// stop the graph
    IMediaControl *pMC = NULL;
	hr = gcap.pFg->QueryInterface(IID_IMediaControl, (void **)&pMC);
    if(SUCCEEDED(hr))
    {
        hr = pMC->Stop();
        pMC->Release();
    }
    if(FAILED(hr))
    {
		goto  errLabel;
    }

	iErr  =  0;

errLabel:

	return  iErr;
}










 /////////////////////////////

  HRESULT  myGetPin(  IBaseFilter  *  pFilter,  PIN_DIRECTION  PinDir,  IPin  **  ppPin  )
{
	IEnumPins  *  pEnum;
	IPin  *  pPin;
	pFilter->EnumPins(  &pEnum  );
	while(  pEnum->Next(  1,  &pPin,  0  )  ==  S_OK  )
	{
		PIN_DIRECTION  PinDirThis;
		pPin->QueryDirection(  &PinDirThis  );
		if  (  PinDir  ==  PinDirThis  )
		{
			pEnum->Release(  );
			*ppPin  =  pPin;
			return  S_OK;
		}
		pPin->Release(  );
	}
	pEnum->Release(  );
	return  E_FAIL;
}

  HRESULT GetPinMediaType(
    IPin *pPin,             // pointer to the pin
    REFGUID majorType,      // desired major type, or GUID_NULL = don't care
    REFGUID subType,        // desired subtype, or GUID_NULL = don't care
    REFGUID formatType,     // desired format type, of GUID_NULL = don't care
    AM_MEDIA_TYPE **ppmt    // Receives a pointer to the media type. (Can be NULL)
    )
{
	if  (  ppmt  )  {
	    *ppmt = NULL;
	}

    IEnumMediaTypes *pEnum = NULL;
    AM_MEDIA_TYPE *pmt = NULL;
    BOOL bFound = FALSE;
    
    HRESULT hr = pPin->EnumMediaTypes(&pEnum);
    if (FAILED(hr))
    {
        return hr;
    }

    while (hr = pEnum->Next(1, &pmt, NULL), hr == S_OK)
    {
        if ((majorType == GUID_NULL) || (majorType == pmt->majortype))
        {
            if ((subType == GUID_NULL) || (subType == pmt->subtype))
            {
                if ((formatType == GUID_NULL) || 
                    (formatType == pmt->formattype))
                {
                    // Found a match. 
                    if (ppmt)
                    {
                        *ppmt = pmt;  // Return it to the caller
                    }
                    else
                    {
                        myDeleteMediaType(pmt);
                    }
                    bFound = TRUE;
                    break;
                }
            }
        }
        myDeleteMediaType(pmt);
    }

    MACRO_safeRelease(pEnum);
    if (SUCCEEDED(hr))
    {
        if (!bFound)
        {
            hr = VFW_E_NOT_FOUND;
        }
    }
    return hr;
}

 HRESULT  newConnectFilters(  IGraphBuilder  *  pGraph,  IBaseFilter  *  pFirst,  IBaseFilter  *  pSecond,  REFGUID  majorType  )
{
	IPin  *  pOut  =  NULL,  *pIn  =  NULL;
	
	HRESULT  hr  =  myGetPin(  pSecond,  PINDIR_INPUT,  &pIn  );
	if  (  FAILED(  hr  )  )  return  hr;

	hr  =  -1;

	IEnumPins  *  pEnum;
	pFirst->EnumPins(  &pEnum  );
	while(  pEnum->Next(  1,  &pOut,  0  )  ==  S_OK  )
	{
		if  (  SUCCEEDED(  GetPinMediaType(  pOut,  majorType,  GUID_NULL,  GUID_NULL,  NULL  )  )  )  {
			PIN_DIRECTION  PinDirThis;
			pOut->QueryDirection(  &PinDirThis  );
			if  (  PINDIR_OUTPUT  ==  PinDirThis  )
			{
				hr  =  pGraph->Connect(  pOut,  pIn  );
				if  (  !FAILED(  hr  )  )  {
					pOut->Release(  );
					break;
				}
			}
		}
		pOut->Release(  );
	}
	pEnum->Release(  );
	pIn->Release(  );

	return  hr;
}


 HRESULT  ConnectFilters(  IGraphBuilder  *  pGraph,  IBaseFilter  *  pFirst,  IBaseFilter  *  pSecond  )
{
	IPin  *  pOut  =  NULL,  *pIn  =  NULL;
	
	HRESULT  hr  =  myGetPin(  pSecond,  PINDIR_INPUT,  &pIn  );
	if  (  FAILED(  hr  )  )  return  hr;

	hr  =  -1;

	IEnumPins  *  pEnum;
	pFirst->EnumPins(  &pEnum  );
	while(  pEnum->Next(  1,  &pOut,  0  )  ==  S_OK  )
	{
		PIN_DIRECTION  PinDirThis;
		pOut->QueryDirection(  &PinDirThis  );
		if  (  PINDIR_OUTPUT  ==  PinDirThis  )
		{
			hr  =  pGraph->Connect(  pOut,  pIn  );
			if  (  !FAILED(  hr  )  )  {
				pOut->Release(  );				
				break;
			}
		}
		pOut->Release(  );
	}
	pEnum->Release(  );
	pIn->Release(  );

	return  hr;
}



 //////////////////////////////////////////

#ifdef  __DEBUG__  //  {

#if  0  

 void ErrMsg(LPTSTR szFormat,...){}


 void AddDevicesToMenu(  HWND  ghwndApp  )
{
	/*
    if(gcap.fDeviceMenuPopulated)
    {
        return;
    }
    gcap.fDeviceMenuPopulated = true;
	*/

    gcap.iNumVCapDevices = 0;

    UINT    uIndex = 0;
    HMENU   hMenuSub;
    HRESULT hr;
    BOOL bCheck = FALSE;

    hMenuSub = GetSubMenu(GetMenu(ghwndApp), 1);        // Devices menu

    // Clean the sub menu
    int iMenuItems = GetMenuItemCount(hMenuSub);
    if(iMenuItems == -1)
    {
        ErrMsg(TEXT("Error Cleaning Devices Menu"));
        return;
    }
    else if(iMenuItems > 0)
    {
        for(int i = 0; i < iMenuItems; i++)
        {
            RemoveMenu(hMenuSub, 0, MF_BYPOSITION);
        }
    }

    for(int i = 0; i < NUMELMS(gcap.rgpmVideoMenu); i++)
    {
        IMonRelease(gcap.rgpmVideoMenu[i]);
    }
    for(int i = 0; i < NUMELMS(gcap.rgpmAudioMenu); i++)
    {
        IMonRelease(gcap.rgpmAudioMenu[i]);
    }

    // enumerate all video capture devices
    ICreateDevEnum *pCreateDevEnum=0;
    hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
                          IID_ICreateDevEnum, (void**)&pCreateDevEnum);
    if(hr != NOERROR)
    {
        ErrMsg(TEXT("Error Creating Device Enumerator"));
        return;
    }

    IEnumMoniker *pEm=0;
    hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEm, 0);
    if(hr != NOERROR)
    {
        ErrMsg(TEXT("Sorry, you have no video capture hardware.\r\n\r\n")
               TEXT("Video capture will not function properly."));
        goto EnumAudio;
    }

    pEm->Reset();
    ULONG cFetched;
    IMoniker *pM;

    while(hr = pEm->Next(1, &pM, &cFetched), hr==S_OK)
    {
        IPropertyBag *pBag=0;

        hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
        if(SUCCEEDED(hr))
        {
            VARIANT var;
            var.vt = VT_BSTR;
            hr = pBag->Read(L"FriendlyName", &var, NULL);
            if(hr == NOERROR)
            {
                AppendMenu(hMenuSub, MF_STRING, ID_MENU_VDEVICE0 + uIndex,
                    var.bstrVal);

                if(gcap.pmVideo != 0 && (S_OK == gcap.pmVideo->IsEqual(pM)))
                    bCheck = TRUE;

                CheckMenuItem(hMenuSub,  ID_MENU_VDEVICE0 + uIndex,
                    (bCheck ? MF_CHECKED : MF_UNCHECKED));
                EnableMenuItem(hMenuSub, ID_MENU_VDEVICE0 + uIndex,
                    (gcap.fCapturing ? MF_DISABLED : MF_ENABLED));
                bCheck = FALSE;

                SysFreeString(var.bstrVal);

                ASSERT(gcap.rgpmVideoMenu[uIndex] == 0);
                gcap.rgpmVideoMenu[uIndex] = pM;
                pM->AddRef();
            }
            pBag->Release();
        }

        pM->Release();
        uIndex++;
    }
    pEm->Release();

    gcap.iNumVCapDevices = uIndex;

    // separate the video and audio devices
    AppendMenu(hMenuSub, MF_SEPARATOR, 0, NULL);

EnumAudio:

    // enumerate all audio capture devices
    uIndex = 0;
    bCheck = FALSE;

    ASSERT(pCreateDevEnum != NULL);

    hr = pCreateDevEnum->CreateClassEnumerator(CLSID_AudioInputDeviceCategory, &pEm, 0);
    pCreateDevEnum->Release();
    if(hr != NOERROR)
        return;
    pEm->Reset();

    while(hr = pEm->Next(1, &pM, &cFetched), hr==S_OK)
    {
        IPropertyBag *pBag;
        hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
        if(SUCCEEDED(hr))
        {
            VARIANT var;
            var.vt = VT_BSTR;
            hr = pBag->Read(L"FriendlyName", &var, NULL);
            if(hr == NOERROR)
            {
                AppendMenu(hMenuSub, MF_STRING, ID_MENU_ADEVICE0 + uIndex,
                    var.bstrVal);

                if(gcap.pmAudio != 0 && (S_OK == gcap.pmAudio->IsEqual(pM)))
                    bCheck = TRUE;

                CheckMenuItem(hMenuSub,  ID_MENU_ADEVICE0 + uIndex,
                    (bCheck ? MF_CHECKED : MF_UNCHECKED));
                EnableMenuItem(hMenuSub, ID_MENU_ADEVICE0 + uIndex,
                    (gcap.fCapturing ? MF_DISABLED : MF_ENABLED));
                bCheck = FALSE;

                SysFreeString(var.bstrVal);

                ASSERT(gcap.rgpmAudioMenu[uIndex] == 0);
                gcap.rgpmAudioMenu[uIndex] = pM;
                pM->AddRef();
            }
            pBag->Release();
        }
        pM->Release();
        uIndex++;
    }

    pEm->Release();
}

BOOL MakeBuilder()
{
    // we have one already
    if(gcap.pBuilder)
        return TRUE;

    //gcap.pBuilder = new ISampleCaptureGraphBuilder( );
	HRESULT hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER, 
			IID_ICaptureGraphBuilder2, (void**)&gcap.pBuilder ); 

    if( NULL == gcap.pBuilder )
    {
        return FALSE;
    }

    return TRUE;
}

BOOL MakeGraph()
{
    // we have one already
    if(gcap.pFg)
        return TRUE;

    HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC,
                                  IID_IGraphBuilder, (LPVOID *)&gcap.pFg);

    return (hr == NOERROR) ? TRUE : FALSE;
}

int gnRecurse = 0;

void ResizeWindow(HWND  ghwndApp,  int w, int h)
{
    RECT rcW, rcC;
    int xExtra, yExtra;
    int cyBorder = GetSystemMetrics(SM_CYBORDER);

      gnRecurse++;

    GetWindowRect(ghwndApp, &rcW);
    GetClientRect(ghwndApp, &rcC);
    xExtra = rcW.right - rcW.left - rcC.right;
    yExtra = rcW.bottom - rcW.top - rcC.bottom + cyBorder + 0;	//  statusGetHeight();

    rcC.right = w;
    rcC.bottom = h;
    SetWindowPos(ghwndApp, NULL, 0, 0, rcC.right + xExtra,
        rcC.bottom + yExtra, SWP_NOZORDER | SWP_NOMOVE);

    // we may need to recurse once.  But more than that means the window cannot
    // be made the size we want, trying will just stack fault.
    //
    if(gnRecurse == 1 && ((rcC.right + xExtra != rcW.right - rcW.left && w > GetSystemMetrics(SM_CXMIN)) ||
        (rcC.bottom + yExtra != rcW.bottom - rcW.top)))
        ResizeWindow( ghwndApp,  w,h);

    gnRecurse--;
}

void FreeCapFilters()
{
    SAFE_RELEASE(gcap.pFg);

	SAFE_RELEASE(  gcap.pBuilder  );
    	
    SAFE_RELEASE(gcap.pVCap);
    SAFE_RELEASE(gcap.pACap);
    SAFE_RELEASE(gcap.pASC);
    SAFE_RELEASE(gcap.pVSC);
    SAFE_RELEASE(gcap.pVC);
    SAFE_RELEASE(gcap.pDlg);

	/*
    if(gcap.pCrossbar)
    {
        delete gcap.pCrossbar;
        gcap.pCrossbar = NULL;
    }
	*/
}


BOOL InitCapFilters()
{
    HRESULT hr=S_OK;
    BOOL f;

    gcap.fCCAvail = FALSE;  // assume no closed captioning support

    f = MakeBuilder();
    if(!f)
    {
        ErrMsg(TEXT("Cannot instantiate graph builder"));
        return FALSE;
    }

    //
    // First, we need a Video Capture filter, and some interfaces
    //
    gcap.pVCap = NULL;

    if(gcap.pmVideo != 0)
    {
        IPropertyBag *pBag;
        gcap.wachFriendlyName[0] = 0;

        hr = gcap.pmVideo->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
        if(SUCCEEDED(hr))
        {
            VARIANT var;
            var.vt = VT_BSTR;

            hr = pBag->Read(L"FriendlyName", &var, NULL);
            if(hr == NOERROR)
            {
                hr = StringCchCopyW(gcap.wachFriendlyName, sizeof(gcap.wachFriendlyName) / sizeof(gcap.wachFriendlyName[0]), var.bstrVal);
                SysFreeString(var.bstrVal);
            }

            pBag->Release();
        }

        hr = gcap.pmVideo->BindToObject(0, 0, IID_IBaseFilter, (void**)&gcap.pVCap);
    }

    if(gcap.pVCap == NULL)
    {
        ErrMsg(TEXT("Error %x: Cannot create video capture filter"), hr);
        goto InitCapFiltersFail;
    }

    //
    // make a filtergraph, give it to the graph builder and put the video
    // capture filter in the graph
    //

    f = MakeGraph();
    if(!f)
    {
        ErrMsg(TEXT("Cannot instantiate filtergraph"));
        goto InitCapFiltersFail;
    }

    hr = gcap.pBuilder->SetFiltergraph(gcap.pFg);
    if(hr != NOERROR)
    {
        ErrMsg(TEXT("Cannot give graph to builder"));
        goto InitCapFiltersFail;
    }

    // Add the video capture filter to the graph with its friendly name
    hr = gcap.pFg->AddFilter(gcap.pVCap, gcap.wachFriendlyName);
    if(hr != NOERROR)
    {
        ErrMsg(TEXT("Error %x: Cannot add vidcap to filtergraph"), hr);
        goto InitCapFiltersFail;
    }

    // Calling FindInterface below will result in building the upstream
    // section of the capture graph (any WDM TVTuners or Crossbars we might
    // need).

    // we use this interface to get the name of the driver
    // Don't worry if it doesn't work:  This interface may not be available
    // until the pin is connected, or it may not be available at all.
    // (eg: interface may not be available for some DV capture)
	/*
    hr = gcap.pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                                      &MEDIATYPE_Interleaved, gcap.pVCap,
                                      IID_IAMVideoCompression, (void **)&gcap.pVC);
    if(hr != S_OK)
    {
        hr = gcap.pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                                          &MEDIATYPE_Video, gcap.pVCap,
                                          IID_IAMVideoCompression, (void **)&gcap.pVC);
    }*/


    // !!! What if this interface isn't supported?
    // we use this interface to set the frame rate and get the capture size
    hr = gcap.pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                                      &MEDIATYPE_Interleaved,
                                      gcap.pVCap, IID_IAMStreamConfig, (void **)&gcap.pVSC);

    if(hr != NOERROR)
    {
        hr = gcap.pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                                          &MEDIATYPE_Video, gcap.pVCap,
                                          IID_IAMStreamConfig, (void **)&gcap.pVSC);
        if(hr != NOERROR)
        {
            // this means we can't set frame rate (non-DV only)
            ErrMsg(TEXT("Error %x: Cannot find VCapture:IAMStreamConfig"), hr);
        }
    }

    gcap.fCapAudioIsRelevant = TRUE;

    AM_MEDIA_TYPE *pmt;

    // default capture format
    if(gcap.pVSC && gcap.pVSC->GetFormat(&pmt) == S_OK)
    {
        // DV capture does not use a VIDEOINFOHEADER
        if(pmt->formattype == FORMAT_VideoInfo)
        {
            // resize our window to the default capture size
            //  ResizeWindow(HEADER(pmt->pbFormat)->biWidth,                         abs(HEADER(pmt->pbFormat)->biHeight));
			traceLogA(  (char*)  "InitCapFilters: ResizeWindow is skipped"  );
        }
        if(pmt->majortype != MEDIATYPE_Video)
        {
            // This capture filter captures something other that pure video.
            // Maybe it's DV or something?  Anyway, chances are we shouldn't
            // allow capturing audio separately, since our video capture
            // filter may have audio combined in it already!
            gcap.fCapAudioIsRelevant = FALSE;
            gcap.fCapAudio = FALSE;
        }
        DeleteMediaType(pmt);
    }

    // we use this interface to bring up the 3 dialogs
    // NOTE:  Only the VfW capture filter supports this.  This app only brings
    // up dialogs for legacy VfW capture drivers, since only those have dialogs
    hr = gcap.pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                                      &MEDIATYPE_Video, gcap.pVCap,
                                      IID_IAMVfwCaptureDialogs, (void **)&gcap.pDlg);

    // Use the crossbar class to help us sort out all the possible video inputs
    // The class needs to be given the capture filters ANALOGVIDEO input pin
	/*
    {
        IPin        *pP = 0;
        IEnumPins   *pins=0;
        ULONG        n;
        PIN_INFO     pinInfo;
        BOOL         Found = FALSE;
        IKsPropertySet *pKs=0;
        GUID guid;
        DWORD dw;
        BOOL fMatch = FALSE;

        //  gcap.pCrossbar = NULL;

        if(SUCCEEDED(gcap.pVCap->EnumPins(&pins)))
        {
            while(!Found && (S_OK == pins->Next(1, &pP, &n)))
            {
                if(S_OK == pP->QueryPinInfo(&pinInfo))
                {
                    if(pinInfo.dir == PINDIR_INPUT)
                    {
                        // is this pin an ANALOGVIDEOIN input pin?
                        if(pP->QueryInterface(IID_IKsPropertySet,
                            (void **)&pKs) == S_OK)
                        {
                            if(pKs->Get(AMPROPSETID_Pin,
                                AMPROPERTY_PIN_CATEGORY, NULL, 0,
                                &guid, sizeof(GUID), &dw) == S_OK)
                            {
                                if(guid == PIN_CATEGORY_ANALOGVIDEOIN)
                                    fMatch = TRUE;
                            }
                            pKs->Release();
                        }

                        if(fMatch)
                        {
                            HRESULT hrCreate=S_OK;
						#if  0
                            gcap.pCrossbar = new CCrossbar(pP, &hrCreate);
                            if (!gcap.pCrossbar || FAILED(hrCreate))
                                break;

                            hr = gcap.pCrossbar->GetInputCount(&gcap.NumberOfVideoInputs);
						#endif
							myMessageBox(  _T(  "error"  )  );

                            Found = TRUE;
                        }
                    }
                    pinInfo.pFilter->Release();
                }
                pP->Release();
            }
            pins->Release();
        }
    }
	*/

    // there's no point making an audio capture filter
    if(gcap.fCapAudioIsRelevant == FALSE)
        goto SkipAudio;

    // create the audio capture filter, even if we are not capturing audio right
    // now, so we have all the filters around all the time.

    //
    // We want an audio capture filter and some interfaces
    //

    if(gcap.pmAudio == 0)
    {
        // there are no audio capture devices. We'll only allow video capture
        gcap.fCapAudio = FALSE;
        goto SkipAudio;
    }
    gcap.pACap = NULL;


    hr = gcap.pmAudio->BindToObject(0, 0, IID_IBaseFilter, (void**)&gcap.pACap);

    if(gcap.pACap == NULL)
    {
        // there are no audio capture devices. We'll only allow video capture
        gcap.fCapAudio = FALSE;
        ErrMsg(TEXT("Cannot create audio capture filter"));
        goto SkipAudio;
    }

    //
    // put the audio capture filter in the graph
    //
    {
        WCHAR wachAudioFriendlyName[256];
        IPropertyBag *pBag;

        wachAudioFriendlyName[0] = 0;

        // Read the friendly name of the filter to assist with remote graph
        // viewing through GraphEdit
        hr = gcap.pmAudio->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
        if(SUCCEEDED(hr))
        {
            VARIANT var;
            var.vt = VT_BSTR;

            hr = pBag->Read(L"FriendlyName", &var, NULL);
            if(hr == NOERROR)
            {
                hr = StringCchCopyW(wachAudioFriendlyName, 256, var.bstrVal);
                SysFreeString(var.bstrVal);
            }

            pBag->Release();
        }

        // We'll need this in the graph to get audio property pages
        hr = gcap.pFg->AddFilter(gcap.pACap, wachAudioFriendlyName);
        if(hr != NOERROR)
        {
            ErrMsg(TEXT("Error %x: Cannot add audio capture filter to filtergraph"), hr);
            goto InitCapFiltersFail;
        }
    }

    // Calling FindInterface below will result in building the upstream
    // section of the capture graph (any WDM TVAudio's or Crossbars we might
    // need).

    // !!! What if this interface isn't supported?
    // we use this interface to set the captured wave format
    hr = gcap.pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Audio, gcap.pACap,
                                      IID_IAMStreamConfig, (void **)&gcap.pASC);

    if(hr != NOERROR)
    {
        ErrMsg(TEXT("Cannot find ACapture:IAMStreamConfig"));
    }

SkipAudio:

    // Can this filter do closed captioning?
    IPin *pPin;
    hr = gcap.pBuilder->FindPin(gcap.pVCap, PINDIR_OUTPUT, &PIN_CATEGORY_VBI,
                                NULL, FALSE, 0, &pPin);
    if(hr != S_OK)
        hr = gcap.pBuilder->FindPin(gcap.pVCap, PINDIR_OUTPUT, &PIN_CATEGORY_CC,
                                    NULL, FALSE, 0, &pPin);
    if(hr == S_OK)
    {
        pPin->Release();
        gcap.fCCAvail = TRUE;
    }
    else
    {
        gcap.fCapCC = FALSE;    // can't capture it, then
    }

    // potential debug output - what the graph looks like
    // DumpGraph(gcap.pFg, 1);

    return TRUE;

InitCapFiltersFail:
    FreeCapFilters();
    return FALSE;
}


 void ChooseDevices(  HWND  ghwndApp,  HWND  ghwndStatus,  IMoniker *pmVideo, IMoniker *pmAudio)
{
#define VERSIZE 40
#define DESCSIZE 80

    int versize = VERSIZE;
    int descsize = DESCSIZE;
    WCHAR wachVer[VERSIZE]={0}, wachDesc[DESCSIZE]={0};
    TCHAR tachStatus[VERSIZE + DESCSIZE + 5]={0};


    // they chose a new device. rebuild the graphs
    if(gcap.pmVideo != pmVideo || gcap.pmAudio != pmAudio)
    {
        if(pmVideo)
        {
            pmVideo->AddRef();
        }
        if(pmAudio)
        {
            pmAudio->AddRef();
        }

        IMonRelease(gcap.pmVideo);
        IMonRelease(gcap.pmAudio);
        gcap.pmVideo = pmVideo;
        gcap.pmAudio = pmAudio;

        //  if(gcap.fPreviewing)  StopPreview();
        //  if(gcap.fCaptureGraphBuilt || gcap.fPreviewGraphBuilt)  TearDownGraph();

        //  FreeCapFilters();
        InitCapFilters();

        /*
		if(gcap.fWantPreview)   // were we previewing?
        {
            BuildPreviewGraph();
            StartPreview();
        }
		*/

        MakeMenuOptions(  ghwndApp  );      // the UI choices change per device
    }

    // Set the check marks for the devices menu.
    int i;
    for(i = 0; i < NUMELMS(gcap.rgpmVideoMenu); i++)
    {
        if(gcap.rgpmVideoMenu[i] == NULL)
            break;

        CheckMenuItem(GetMenu(ghwndApp),
            ID_MENU_VDEVICE0 + i,
            (S_OK == gcap.rgpmVideoMenu[i]->IsEqual(gcap.pmVideo)) ? MF_CHECKED : MF_UNCHECKED);
    }

    for(i = 0; i < NUMELMS(gcap.rgpmAudioMenu); i++)
    {
        if(gcap.rgpmAudioMenu[i] == NULL)
            break;

        CheckMenuItem(GetMenu(ghwndApp), ID_MENU_ADEVICE0 + i,
            (S_OK == gcap.rgpmAudioMenu[i]->IsEqual(gcap.pmAudio)) ? MF_CHECKED : MF_UNCHECKED);
    }

    // Put the video driver name in the status bar - if the filter supports
    // IAMVideoCompression::GetInfo, that's the best way to get the name and
    // the version.  Otherwise use the name we got from device enumeration
    // as a fallback.
	/*
    if(gcap.pVC)
    {
        HRESULT hr = gcap.pVC->GetInfo(wachVer, &versize, wachDesc, &descsize,
                                       NULL, NULL, NULL, NULL);
        if(hr == S_OK)
        {
            // It's possible that the call succeeded without actually filling
            // in information for description and version.  If these strings
            // are empty, just display the device's friendly name.
            if(wcslen(wachDesc) && wcslen(wachVer))
            {
                hr = StringCchPrintf(tachStatus, VERSIZE + DESCSIZE + 5, TEXT("%s - %s\0"), wachDesc, wachVer);
                statusUpdateStatus(ghwndStatus, tachStatus);
                return;
            }
        }
    }
	*/

    // Since the GetInfo method failed (or the interface did not exist),
    // display the device's friendly name.
    statusUpdateStatus(ghwndStatus, gcap.wachFriendlyName);
}

 void  StopPreview(  )
 {
 }

int  myAppCommand(  HWND  hwnd,  unsigned  msg,  WPARAM  wParam,  LPARAM  lParam  )
{


	HRESULT hr;
    int id = GET_WM_COMMAND_ID(wParam, lParam);

				///llllllllllll


                // You can change this pin's output format in these dialogs.
                // If the capture pin is already connected to somebody who's
                // fussy about the connection type, that may prevent using
                // this dialog(!) because the filter it's connected to might not
                // allow reconnecting to a new format. (EG: you switch from RGB
                // to some compressed type, and need to pull in a decoder)
                // I need to tear down the graph downstream of the
                // capture filter before bringing up these dialogs.
                // In any case, the graph must be STOPPED when calling them.
                if(gcap.fWantPreview)
                    StopPreview();  // make sure graph is stopped

                // The capture pin that we are trying to set the format on is connected if
                // one of these variable is set to TRUE. The pin should be disconnected for
                // the dialog to work properly.
                /*
				if(gcap.fCaptureGraphBuilt || gcap.fPreviewGraphBuilt)
                {
                    TearDownGraph();    // graph could prevent dialog working
                }
				*/

                IAMStreamConfig *pSC;
                hr = gcap.pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                    &MEDIATYPE_Interleaved, gcap.pVCap,
                    IID_IAMStreamConfig, (void **)&pSC);

                if(hr != NOERROR)
                    hr = gcap.pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                        &MEDIATYPE_Video, gcap.pVCap,
                        IID_IAMStreamConfig, (void **)&pSC);

                ISpecifyPropertyPages *pSpec;
                CAUUID cauuid;

                hr = pSC->QueryInterface(IID_ISpecifyPropertyPages,
                    (void **)&pSpec);

                if(hr == S_OK)
                {
                    hr = pSpec->GetPages(&cauuid);
                    hr = OleCreatePropertyFrame(hwnd, 30, 30, NULL, 1,
                        (IUnknown **)&pSC, cauuid.cElems,
                        (GUID *)cauuid.pElems, 0, 0, NULL);

                    // !!! What if changing output formats couldn't reconnect
                    // and the graph is broken?  Shouldn't be possible...

                    if(gcap.pVSC)
                    {
                        AM_MEDIA_TYPE *pmt;
                        // get format being used NOW
                        hr = gcap.pVSC->GetFormat(&pmt);

                        // DV capture does not use a VIDEOINFOHEADER
                        if(hr == NOERROR)
                        {
                            if(pmt->formattype == FORMAT_VideoInfo)
                            {
                                // resize our window to the new capture size
                                //  ResizeWindow(  hwnd,  HEADER(pmt->pbFormat)->biWidth,  abs(HEADER(pmt->pbFormat)->biHeight));
								traceLogA(  (char*)  "myAppCommand: ResizeWindow is skipped"  );
                            }
                            DeleteMediaType(pmt);
                        }
                    }

                    CoTaskMemFree(cauuid.pElems);
                    pSpec->Release();
                }

                pSC->Release();
                if(gcap.fWantPreview)
                {
                    //  BuildPreviewGraph();
                    //  StartPreview();
					myMessageBox(  _T(  "err"  )  );
                }

				return  0;
}

BOOL AppInit(HWND  hWnd)
{
	AddDevicesToMenu(  hWnd  );
	ChooseDevices(  hWnd,  0,  gcap.rgpmVideoMenu[0], NULL  );
	
	//
	myAppCommand(  hWnd,  273, 43,  0  );

	FreeCapFilters(  );

	return  TRUE;
}

#endif








#endif  //  }





