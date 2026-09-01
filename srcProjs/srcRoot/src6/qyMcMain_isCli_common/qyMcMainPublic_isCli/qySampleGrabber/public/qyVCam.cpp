// qyVCam.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"


#include	<streams.h>
#include	<stdio.h>
#include	<olectl.h>
#include	<dvdmedia.h>

#include	<mmreg.h>
#include	<msacm.h>
#include	<tchar.h>

#include	"qySampleGrabberPublic.h"

#include	"qyCommon.h"
#include	"qySyncCommProc.h"
#include	"genericQueue.h"
#include	"qyq2.h"

#include	"qyCommCommon.h"
#include	"qyCommProc.h"
#include	"qmOpenCommon.h"

#ifndef  __WINCE__
	#include	<vfw.h>
#endif

#include	"qyWmComm.h"
#include	"qnmCommProc.h"
#include	"qnmCommProc_mis.h"

#include	"qyVCam.h"


 //  qyVCam is the source filter 
 CUnknown *  WINAPI  QVCam::CreateInstance(  LPUNKNOWN  lpunk,  HRESULT  *  phr  )
{
	ASSERT(  phr  );
	CUnknown  *  punk  =  new  QVCam(  lpunk,  phr  );

	return  punk;
}

 QVCam::QVCam(  LPUNKNOWN  lpunk,  HRESULT  *  phr  ):
	CSource(  NAME(  "Virtual Cam"  ),  lpunk,  CLSID_VCam_is  )
{
	ASSERT(  phr  );
	CAutoLock  cAutoLock(  &m_cStateLock );

	m_paStreams  =  (  CSourceStream  **  )  new  QVCamStream  *  [1];
	m_paStreams[0]  =  new  QVCamStream(  phr,  this ,  L"Virtual  Cam"  );

	//  2010/06/11  
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

QVCam::~QVCam(  )
{
	OutputDebugString(  _T(  "~QVCam\n"  )  );
	if  (  m_var.pPkt  )  {
		free(  m_var.pPkt  );
	}
}

 HRESULT  QVCam::QueryInterface(  REFIID  riid,  void  **  ppv  )
{

	if  (  riid  == _uuidof(  IAMStreamConfig  )  ||  riid  ==  _uuidof(  IKsPropertySet )  )
		return m_paStreams[0]->QueryInterface(  riid,  ppv  );
	else  
		return  CSource::QueryInterface(  riid,  ppv  );

}

 //  QVCamStream  is  the  one and only  output pin of  QVCam  which handles  all the  stuff.
QVCamStream::QVCamStream(  HRESULT  *  phr,  QVCam  *  pParent,  LPCWSTR  pPinName  ) :
	CSourceStream(  NAME(  "Virtual  Cam"  ),  phr,  pParent,  pPinName  ),  m_pParent(  pParent  )  
{
	GetMediaType(  4,  &m_mt  );
}

QVCamStream::~QVCamStream()
{
}

HRESULT  QVCamStream::QueryInterface(   REFIID  riid,  void  **  ppv  )
{
	if  (  riid  ==  _uuidof(  IAMStreamConfig  )  )
		*  ppv  =  (  IAMStreamConfig  *  )this;
	else  if  (  riid  ==  _uuidof(  IKsPropertySet  )  )
		*  ppv  =  (  IKsPropertySet  *  )this;
	else  
		return  CSourceStream::QueryInterface(  riid,  ppv  );

	AddRef(  );
	return  S_OK;
}


//  This is  the  routine  where  we create the data being output by the Virtual Camera  device.
HRESULT  QVCamStream::FillBuffer(  IMediaSample  *  pms  )
{
	HRESULT				hr				=	E_FAIL;
	int					len_pPkt		=	0;
	int					tmpiRet			=	-1;
	MY_DEBUG_STEP	*	pDebugStep		=	(  MY_DEBUG_STEP  *  )m_pParent->m_var.param.pDebugStep;					//  2012/03/21
	BOOL				bPktGot			=	FALSE;					 

	CQyMalloc			mallocObj_pMsg;

	//
	if  (  m_pParent->m_var.param.pnStep_FillBuffer  )  *m_pParent->m_var.param.pnStep_FillBuffer  =  CONST_nStep_enter;
	DWORD	dwTickCnt	=	GetTickCount(  );
	if  (  m_pParent->m_var.param.pdwTickCnt_leave_FillBuffer
		&&  *m_pParent->m_var.param.pdwTickCnt_leave_FillBuffer  )
	{
		int  iDiffInMs_leave_2_enter_FillBuffer  =  dwTickCnt  -  *m_pParent->m_var.param.pdwTickCnt_leave_FillBuffer;

		#ifdef  __DEBUG__
				traceLog(  _T(  "iDiffInMs_leave_2_enter_FillBuffer %d"  ),  iDiffInMs_leave_2_enter_FillBuffer  );
		#endif

		if  (  m_pParent->m_var.param.piDiffInMs_leave_2_enter_FillBuffer  )  {
			*m_pParent->m_var.param.piDiffInMs_leave_2_enter_FillBuffer  =  iDiffInMs_leave_2_enter_FillBuffer;
		}

		if  (  iDiffInMs_leave_2_enter_FillBuffer  >  1000  )  {
			goto  errLabel;
		}
	}	


	//
	if  (  m_pParent->m_var.param.pQ2  )  {
		QY_Q2			*	pQ2			=	(  QY_Q2  *  )m_pParent->m_var.param.pQ2;
		PF_q2GetMsg			pf_q2GetMsg	=	(  PF_q2GetMsg  )m_pParent->m_var.param.pf_q2GetMsg;

		//  2012/03/21
		M_setStep_fg(  pDebugStep,  100  );

		//
		for  (  ;  !(  *m_pParent->m_var.param.pbQuit  );  )  {
			 if  (  isQ2Empty(  pQ2  )  )  {
				 DWORD  dwEvt  =  MsgWaitForMultipleObjects(
							pQ2->cfg.usCnt_hEvents,						//  mycountof(  pPlay->hEvents  ),				// Number of events.
							 pQ2->hEvents,								// Location of handles.
                             FALSE,										// Wait for all?
                             5000,										// How long to wait?
                             0  );										// Any message is an 
																		// event.
				 //  if  (  dwEvt  ==  WAIT_FAILED  )  continue;
				 #ifdef  __DEBUG__
						 #if  0
					 		 if  (  dwEvt  !=  WAIT_TIMEOUT  )  {
								 dwEvt -= WAIT_OBJECT_0;
								 switch  (  dwEvt  )  {
										 case  0:
											   OutputDebugString(  _T(  "FillBuffer: event 0\n"  )  );
											   break;
										 default:
											     OutputDebugString(  _T(  "FillBuffer: event 1\n"  )  );
												 break;
								 }
							 }
						 #endif
				 #endif
			 }

			 bPktGot	=	FALSE;
			 for  (  ;  !(  *m_pParent->m_var.param.pbQuit  )  &&  !isQ2Empty(  pQ2  );  )  {
				  len_pPkt  =  m_pParent->m_var.param.uiBufSize_pPkt;
				  tmpiRet  =  pf_q2GetMsg(  pQ2,  m_pParent->m_var.pPkt,  (  unsigned  int  *  )&len_pPkt  );
				  if  (  !tmpiRet  )  {
					  MY_DMO_INFO	*	pDmoInfo	=	(  MY_DMO_INFO  *  )m_pParent->m_var.param.pDmoInfo;

					  //  可以做一点过滤,对那些过时的数据
					  if  (  this->m_mt.majortype  ==  MEDIATYPE_Video  )  {
						  if  (  m_pParent->m_var.param.bPkt_MIS_MSG_procVideo_qmc  )  {
							  MIS_MSG_procVideo_qmc  *  pMsg  =  (  MIS_MSG_procVideo_qmc  *  )m_pParent->m_var.pPkt;

						#if  10
							  if  (  mallocObj_pMsg.attach(  &pMsg->pkt.memory  )  )  {		//  2012/02/05
								  clean_MIS_MSG_procVideo_qmc(  pMsg,  _T(  ""  )  );
								  continue;
							  }
						#endif

							  }
						  else  {
								TRANSFER_VIDEO_DATA	*	pPkt  =  (  TRANSFER_VIDEO_DATA  *  )m_pParent->m_var.pPkt;
								if  (  !isQ2Empty(  pQ2  )  )  {
									int  iDiff  =  pPkt->mems[0].uiSampleTimeInMs  -  pDmoInfo->iSampleTimeInMs_new;
									if  (  abs(  iDiff  )  >  1800  )  {
										traceLog(  _T(  "FillBuffer: v, iDiff new is %d, skipped. nQNodes %d"  ),  iDiff,  pQ2->qs[0].uiQNodes  +  pQ2->qs[1].uiQNodes  );
										continue;							  
									}
									if  (  pDmoInfo->iSampleTimeInMs_audio  )  {
										iDiff  =  pPkt->mems[0].uiSampleTimeInMs  -  pDmoInfo->iSampleTimeInMs_audio;
										//  if  (  iDiff  >  1200  ||  iDiff  <  -800  )  
										if  (  abs(  iDiff  )  >  1500  )								  
										{
											traceLog(  _T(  "FillBuffer: v, iDiff va is %d, skipped. nQNodes %d"  ),  iDiff,  pQ2->qs[0].uiQNodes  +  pQ2->qs[1].uiQNodes  );
											continue;								  
										}							  
									}						  
								}
						  }
						  }					  
					  else  if  (  m_mt.majortype  ==  MEDIATYPE_Audio  )  {
								TRANSFER_AUDIO_DATA	*	pPkt  =  (  TRANSFER_AUDIO_DATA  *  )m_pParent->m_var.pPkt;
								if  (  !isQ2Empty(  pQ2  )  )  {
									int  iDiff  =  pPkt->mems[0].uiSampleTimeInMs  -  pDmoInfo->iSampleTimeInMs_new;
									if  (  abs(  iDiff  )  >  2200  )  {
										traceLog(  _T(  "FillBuffer: a, iDiff new is %d, skipped. nQNodes %d"  ),  iDiff,  pQ2->qs[0].uiQNodes  +  pQ2->qs[1].uiQNodes  );
										continue;							  
									}						  
								}						
								}
					  else  {
						    OutputDebugString(  _T(  "FillBuffer failed. m_mt.majortype error\n"  )  );
							goto  errLabel;							
					  }
					  bPktGot  =  TRUE;
					  break;
				  }
				  if  (  tmpiRet  ==  CONST_qyRet_bufTooSmall  )  {
					  OutputDebugString(  _T(  "FillBuffer failed, buf too small\n"  )  );
					  goto  errLabel;
				  }
				  continue;
			 }
			 if  (  bPktGot  )  break;
			 continue;
		}

		if  (  *m_pParent->m_var.param.pbQuit  )  goto  errLabel;

	}

	BYTE  *  pData;
	long  lDataSize;
	pms->GetPointer(  &pData );
	lDataSize  =  pms->GetSize(  );

	if  (  !m_pParent->m_var.param.pQ2  )  {
		for  (  int  i  =  0; i <  lDataSize;  ++i  )  {
			 pData[i]  =  rand(  );
		}
		//
		
		REFERENCE_TIME  rtNow			=	m_rtLastTime;
		REFERENCE_TIME  avgFrameTime	=   (  (  VIDEOINFOHEADER  *  )m_mt.pbFormat  )->AvgTimePerFrame;
		m_rtLastTime  =  rtNow  +  avgFrameTime;
		pms->SetTime(  &rtNow, &m_rtLastTime  );
		pms->SetSyncPoint(  TRUE  );
		}
	else  {
		  QY_Q2			*	pQ2					=	(  QY_Q2  *  )m_pParent->m_var.param.pQ2;
		  MY_DMO_INFO	*	pDmoInfo			=	(  MY_DMO_INFO  *  )m_pParent->m_var.param.pDmoInfo;
		  int				iSampleTimeInMs		=	0;
		  unsigned  int		ui_rtTimeLen			=	0;
		  REFERENCE_TIME	rtNow;

		  #ifdef  __DEBUG__
				  unsigned  int		uiLen				=	0;
		  #endif

		  if  (  m_mt.majortype  ==  MEDIATYPE_Video  )  {
			  if  (  m_pParent->m_var.param.bPkt_MIS_MSG_procVideo_qmc  )  {
				  MIS_MSG_procVideo_qmc  *  pMsg  =  (  MIS_MSG_procVideo_qmc  *  )m_pParent->m_var.pPkt;
				  if  (  pMsg->bih.biSizeImage  >  lDataSize  )  {
					  #ifdef  __DEBUG__
								traceLog(  _T(  "FillBuffer failed: v, uiLen > lDataSize"  )  );
					  #endif
					  goto  errLabel;
				  }
				  
				  memcpy(  pData,  pMsg->pkt.memory.m_pBuf,  pMsg->bih.biSizeImage  );
				  pms->SetActualDataLength(  pMsg->bih.biSizeImage  );						

				  hr  =  NOERROR;  goto  errLabel;

				  //
				  }
			  else  {
				    TRANSFER_VIDEO_DATA	*	pPkt  =  (  TRANSFER_VIDEO_DATA  *  )m_pParent->m_var.pPkt;

					if  (  pPkt->mems[0].uiLen  >  lDataSize  )  {
						#ifdef  __DEBUG__
								traceLog(  _T(  "FillBuffer failed: v, uiLen > lDataSize"  )  );
						#endif
						goto  errLabel;				  
					}

					memcpy(  pData,  pPkt->buf,  pPkt->mems[0].uiLen  );
					pms->SetActualDataLength(  pPkt->mems[0].uiLen  );

					//			  
					iSampleTimeInMs	=	pPkt->mems[0].uiSampleTimeInMs;
					ui_rtTimeLen  =  1  *  10000;

				    #ifdef  __DEBUG__
			  				uiLen  =  pPkt->mems[0].uiLen;
					#endif
			  }
			  }
		  else  if  (  m_mt.majortype  ==  MEDIATYPE_Audio  )  {
					TRANSFER_AUDIO_DATA	*	pPkt  =  (  TRANSFER_AUDIO_DATA  *  )m_pParent->m_var.pPkt;

					if  (  pPkt->mems[0].uiLen  >  lDataSize  )  {
						#ifdef  __DEBUG__
							    traceLog(  _T(  "FillBuffer failed: a, uiLen > lDataSize"  )  );
						#endif				  
						goto  errLabel;			  
					}

					memcpy(  pData,  pPkt->buf,  pPkt->mems[0].uiLen  );
					pms->SetActualDataLength(  pPkt->mems[0].uiLen  );

					iSampleTimeInMs  =  pPkt->mems[0].uiSampleTimeInMs;
					ui_rtTimeLen  =  pPkt->mems[0].ui_rtTimeLen;
					#ifdef  __DEBUG__
			  			    uiLen  =  pPkt->mems[0].uiLen;
					#endif
					}
		  else  
			  goto  errLabel;

		  rtNow  =  pDmoInfo->rt_total_rtTimeLen;
		  m_rtLastTime  =  rtNow  +  ui_rtTimeLen;

		  int	iSampleTimeInMs_stream  =  (  int  )(  pDmoInfo->rt_total_rtTimeLen  /  10000  );
		  if  (  pDmoInfo->iDiffInMs_tStartStream  +  iSampleTimeInMs_stream  !=  iSampleTimeInMs  )  {
			  pDmoInfo->iDiffInMs_tStartStream  =  iSampleTimeInMs  -  iSampleTimeInMs_stream;
			  #ifdef  __DEBUG__
					  #if  0
							traceLog(  _T(  "FillBuffer: iDiffInMs_tStartStream modified, %d"  ),  pDmoInfo->iDiffInMs_tStartStream  );
					  #endif
			  #endif
		  }
		  pDmoInfo->rt_total_rtTimeLen  +=  ui_rtTimeLen;  


		  #ifdef  __DEBUG__
				  if  (  m_pParent->m_var.param.ucbPrint_a  )  {
					  traceLog(  _T(  "FillBuffer: a, t_stream %d, st %d, len %d, qNodes %d,%d"  ),  iSampleTimeInMs_stream,  iSampleTimeInMs,  uiLen,  pQ2->qs[0].uiQNodes,  pQ2->qs[1].uiQNodes  );
				  }
				  if  (  m_pParent->m_var.param.ucbPrint_v  )  {
				  	  traceLog(  _T(  "FillBuffer: v, t_stream %d, st %d, len %d, audio %d, iDiff_va %d, qNodes %d,%d"  ),  iSampleTimeInMs_stream,  iSampleTimeInMs,  uiLen,  pDmoInfo->iSampleTimeInMs_audio,  iSampleTimeInMs  -  pDmoInfo->iSampleTimeInMs_audio,  pQ2->qs[0].uiQNodes,  pQ2->qs[1].uiQNodes  );
					  //  traceLog(  _T(  "FillBuffer: iSampleTime %d, audio %d, t_stream %d, frameTime %d. qNodes %d"  ),  iSampleTimeInMs,  pDmoInfo->iSampleTimeInMs_audio,  iSampleTimeInMs_stream,  tmpFrameTimeInMs,  pQ2->qs[0].uiQNodes  +  pQ2->qs[1].uiQNodes  );						
				  }			
		  #endif 
		  
		  hr  =  pms->SetTime(  &rtNow, &m_rtLastTime  );
		  hr  =  pms->SetSyncPoint(  TRUE  );
	}


	hr  =  NOERROR;

errLabel:

	M_setStep_fg(  pDebugStep,  200  );
	if  (  pDebugStep  )  {
		pDebugStep->fg.FillBuffer.hr  =  hr;
		pDebugStep->fg.FillBuffer.bPktGot  =  bPktGot;
		if  (  m_pParent->m_var.param.pbQuit  )  {
			pDebugStep->fg.FillBuffer.bParentQuit  =  *m_pParent->m_var.param.pbQuit;
		}
	}
	if  (  FAILED(  hr  )  )  {
		if  (  m_pParent->m_var.param.pbFailed_FillBuffer  )  {
			*m_pParent->m_var.param.pbFailed_FillBuffer  =  TRUE;
		}
	}
	if  (  m_pParent->m_var.param.pdwTickCnt_leave_FillBuffer  )  *m_pParent->m_var.param.pdwTickCnt_leave_FillBuffer  =  GetTickCount(  );
	if  (  m_pParent->m_var.param.pnStep_FillBuffer  )  *m_pParent->m_var.param.pnStep_FillBuffer  =  CONST_nStep_leave;

	return  hr;
}

STDMETHODIMP  QVCamStream::Notify(  IBaseFilter  *  pSender,  Quality  q  )
{
	return  E_NOTIMPL;
}

// This is called when the output format has been negotiated
HRESULT  QVCamStream::SetMediaType(  const  CMediaType  * pmt  )
{
	//  DECLARE_PTR(  VIDEOINFOHEADER,  pvi,  pmt->Format(  )  );
	HRESULT  hr  =  CSourceStream::SetMediaType(  pmt  );
	return  hr;
}

HRESULT  QVCamStream::GetMediaType(  int  iPosition,  CMediaType  *  pmt  )
{
	if  (  iPosition  <  0  )  return  E_INVALIDARG;
	if  (  iPosition  >  8  )  return  VFW_S_NO_MORE_ITEMS;

	if  (  iPosition  ==  0  )  
	{
		*  pmt  =  m_mt;
		return  S_OK;
	}

#ifdef  __DEBUG__
		#if  0
			 TCHAR	tBuf[64]	=	_T(  ""  );
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "VCam: GetMediaType failed, iPosition %d\n"  ),  iPosition  );
			 OutputDebugString(  tBuf  );
		#endif
#endif

	return  VFW_S_NO_MORE_ITEMS;

#if  0

	DECLARE_PTR(  VIDEOINFOHEADER,  pvi,  pmt->AllocFormatBuffer(  sizeof(  VIDEOINFOHEADER  )  )  );
	ZeroMemory(  pvi,  sizeof(  VIDEOINFOHEADER  )  );

	pvi->bmiHeader.biCompression  =  BI_RGB;
	pvi->bmiHeader.biBitCount  =  24;
	pvi->bmiHeader.biSize  =  sizeof(  BITMAPINFOHEADER  );
	pvi->bmiHeader.biWidth  =  80  *  iPosition;
	pvi->bmiHeader.biHeight  =  60  *  iPosition;
	pvi->bmiHeader.biPlanes  =  1;
	pvi->bmiHeader.biSizeImage  =  GetBitmapSize(  &pvi->bmiHeader  );
	pvi->bmiHeader.biClrImportant   =  0;

	pvi->AvgTimePerFrame  =  DEFAULT_AvgTimePerFrame;	//  1000000;

	SetRectEmpty(  &(  pvi->rcSource  )  );
	SetRectEmpty(  &(  pvi->rcTarget  )  );

	pmt->SetType(  &MEDIATYPE_Video  );
	pmt->SetFormatType(  &FORMAT_VideoInfo  );
	pmt->SetTemporalCompression(  FALSE  );

	//
	const  GUID  SubTypeGUID  =  GetBitmapSubtype(  &pvi->bmiHeader  );
	pmt->SetSubtype(  &SubTypeGUID  );
	pmt->SetSampleSize(  pvi->bmiHeader.biSizeImage  );

	return  NOERROR;

#endif
}

HRESULT  QVCamStream::CheckMediaType(  const  CMediaType  * pMediaType  )
{
	//  VIDEOINFOHEADER  *  pvi =  (  VIDEOINFOHEADER  *  )(  pMediaType->Format(  )  );
	if  (  *  pMediaType  !=  m_mt  )
		return  E_INVALIDARG;
	return S_OK;
}

HRESULT  QVCamStream::DecideBufferSize(  IMemAllocator  *  pAlloc,  ALLOCATOR_PROPERTIES  *  pProperties  )
{
	CAutoLock  cAutoLock(  m_pFilter->pStateLock(  )  );
	HRESULT  hr  =  NOERROR;

	if  (  m_mt.majortype  ==  MEDIATYPE_Video  )  {
		VIDEOINFOHEADER  *  pvi  =  (  VIDEOINFOHEADER  *  )m_mt.Format(  );
		pProperties->cBuffers  = 1;
		pProperties->cbBuffer  =  pvi->bmiHeader.biSizeImage;
		}
	else  if  (  m_mt.majortype  ==  MEDIATYPE_Audio  )  {
			  WAVEFORMATEX	*	pWfx  =  (  WAVEFORMATEX  *  )m_mt.Format(  );
			  pProperties->cBuffers  =  1;
			  pProperties->cbBuffer  =  pWfx->nAvgBytesPerSec;
			  }
	else
		return  E_FAIL;
	
	ALLOCATOR_PROPERTIES  Actual;
	hr  =  pAlloc->SetProperties(  pProperties,  &  Actual  );

	if  (  FAILED(  hr  )  )  return hr;
	if  (  Actual.cbBuffer  <  pProperties->cbBuffer  )  return  E_FAIL;

	return  NOERROR;
}

HRESULT  QVCamStream::OnThreadCreate(  )
{
	m_rtLastTime  =  0;
	return  NOERROR;
}

//  IAMStreamConfig
HRESULT  STDMETHODCALLTYPE  QVCamStream::SetFormat(  AM_MEDIA_TYPE  *  pmt  )
{
	//  DECLARE_PTR(  VIDEOINFOHEADER,  pvi,  m_mt.pbFormat  );
	m_mt  =  *  pmt;
	IPin  *  pin;
	ConnectedTo(  &pin  );
	if  (  pin  )
	{
		IFilterGraph  *  pGraph  =  m_pParent->GetGraph(  );
		pGraph->Reconnect(  this  );
	}


	return  S_OK;
}

HRESULT  STDMETHODCALLTYPE  QVCamStream::GetFormat(  AM_MEDIA_TYPE  **  ppmt  )
{
	*ppmt  =  CreateMediaType(  &m_mt  );
	return  S_OK;
}

HRESULT  STDMETHODCALLTYPE  QVCamStream::GetNumberOfCapabilities(  int  *  piCount,  int  *  piSize  )
{
	if  (  this->m_pParent->m_var.param.pQ2  )  {
		OutputDebugString(  _T(  "VCamStream:GetNumberOfCapabilities failed \n"  )  );
		return  E_FAIL;
	}

	*piCount  =  8;
	*piSize  =  sizeof(  VIDEO_STREAM_CONFIG_CAPS  );
	return  S_OK;
}

HRESULT  STDMETHODCALLTYPE  QVCamStream::GetStreamCaps(  int  iIndex,  AM_MEDIA_TYPE  **  pmt,  BYTE  * pSCC  )
{
	if  (  this->m_pParent->m_var.param.pQ2  )  {
		OutputDebugString(  _T(  "VCamStream:GetStreamCaps failed\n"  )  );
		return  E_FAIL;
	}

	*  pmt  =  CreateMediaType(  &m_mt  );
	DECLARE_PTR(  VIDEOINFOHEADER,  pvi,  (  *  pmt  )->pbFormat  );

	if  (  iIndex  ==  0  )  iIndex  =  4;

	pvi->bmiHeader.biCompression  =  BI_RGB;
	pvi->bmiHeader.biBitCount  =  24;
	pvi->bmiHeader.biSize  =  sizeof(  BITMAPINFOHEADER  );
	pvi->bmiHeader.biWidth  =  80  *  iIndex;
	pvi->bmiHeader.biHeight  =  60  *  iIndex;
	pvi->bmiHeader.biPlanes  =  1;
	pvi->bmiHeader.biSizeImage  =  GetBitmapSize(  &pvi->bmiHeader  );
	pvi->bmiHeader.biClrImportant  =  0;

	SetRectEmpty(  &(  pvi->rcSource  )  );
	SetRectEmpty(  &(  pvi->rcTarget  )  );

	(  *  pmt  )->majortype  =  MEDIATYPE_Video;
	(  *  pmt  )->subtype  =  MEDIASUBTYPE_RGB24;
	(  *  pmt  )->formattype  =  FORMAT_VideoInfo;
	(  *  pmt  )->bTemporalCompression   =  FALSE;
	(  *  pmt  )->bFixedSizeSamples  =  FALSE;
	(  *  pmt  )->lSampleSize  =  pvi->bmiHeader.biSizeImage;
	(  *  pmt  )->cbFormat  =  sizeof(  VIDEOINFOHEADER  );

	DECLARE_PTR(  VIDEO_STREAM_CONFIG_CAPS,  pvscc, pSCC  );

	pvscc->guid  =  FORMAT_VideoInfo;
	pvscc->VideoStandard  =  AnalogVideo_None;
	pvscc->InputSize.cx  =  640;
	pvscc->InputSize.cy  =  480;
	pvscc->MinCroppingSize.cx  =  80;
	pvscc->MinCroppingSize.cy  =  60;
	pvscc->MaxCroppingSize.cx  =  640;
	pvscc->MaxCroppingSize.cy  =  480;
	pvscc->CropGranularityX  =  80;
	pvscc->CropGranularityY  =  60;
	pvscc->CropAlignX  =  0;
	pvscc->CropAlignY  =  0;
	pvscc->MinOutputSize.cx  =  80;
	pvscc->MinOutputSize.cy  =  60;
	pvscc->MaxOutputSize.cx  =  640;
	pvscc->MaxOutputSize.cy  =  480;
	pvscc->OutputGranularityX  =  0;
	pvscc->OutputGranularityY  =  0;
	pvscc->StretchTapsX  =  0;
	pvscc->StretchTapsY  =  0;
	pvscc->ShrinkTapsX  =  0;
	pvscc->ShrinkTapsY  =  0;
	pvscc->MinFrameInterval  =  200000;  //  50fps
	pvscc->MaxFrameInterval  =  50000000;  //  0.2fps
	pvscc->MinBitsPerSecond  =  (  80  *  60  *  3  *  8  )  /  5;
	pvscc->MaxBitsPerSecond  =  640  *  480  *  3  *  8  *  50;

	return  S_OK;
}


//  IKsPropertySet
HRESULT  QVCamStream::Set(  REFGUID  guidPropSet,  DWORD  dwID,  void  *  pInstanceData,
						  DWORD  cbInstanceData,  void  *  pPropData,  DWORD  cbPropData  )
{
	return  E_NOTIMPL;
}

HRESULT  QVCamStream::Get(  
						  REFGUID  guidPropSet,  
						  DWORD  dwPropID,  
						  void  *  pInstanceData,
						  DWORD  cbInstanceData,
						  void  *  pPropData,
						  DWORD  cbPropData, 
						  DWORD  *  pcbReturned
						  )
{
	if  (  guidPropSet  !=  AMPROPSETID_Pin  )  return  E_PROP_SET_UNSUPPORTED;
	if  (  dwPropID  !=  AMPROPERTY_PIN_CATEGORY  )  return  E_PROP_ID_UNSUPPORTED;
	if  (  pPropData  ==  NULL  &&  pcbReturned  ==  NULL  )  return  E_POINTER;

	if  (  pcbReturned  ) *  pcbReturned  =  sizeof(  GUID  );
	if  (  pPropData  ==  NULL  )  return  S_OK;
	if  (  cbPropData  <  sizeof(  GUID  )  )  return  E_UNEXPECTED;

	*(  GUID  *)pPropData  =  PIN_CATEGORY_CAPTURE;
	return  S_OK;
}


HRESULT  QVCamStream::QuerySupported(  REFGUID  guidPropSet,  DWORD  dwPropID,  DWORD  * pTypeSupport  )
{
	if  (  guidPropSet  !=  AMPROPSETID_Pin  )  return  E_PROP_SET_UNSUPPORTED;
	if  (  dwPropID  !=  AMPROPERTY_PIN_CATEGORY  )  return  E_PROP_ID_UNSUPPORTED;
	if  (  pTypeSupport  )  *  pTypeSupport  =  KSPROPERTY_SUPPORT_GET;
	return  S_OK;
}