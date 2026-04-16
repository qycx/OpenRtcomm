


#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
//#include	"qmcVideoCapture_isCli.h"
//#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"
#include	"qmcDmoPublic.h"
#include	"qmcCmdProc.h"
#include	"tmpCeLib.h"
//  #include	"myfourcc.h"
#include	"module_qisCamCap.h"
#include	"isCmdConst.h"
#include	"qyOpenShellCommon.h"
#include	"qyCusResTemp.h"
#include	"policyAvParams.h"

#include	"qmcVideoCapture_rtsp.h"
#include	"qmcVideoCapture_isCli.h"

//#include	"isCliHelpPublic.h"





//
 int  smplBitstreamReader_ReadNextFrame_func_a(  void  *  pQdcObjInfoParam,  long  *  pold_lPktId,  unsigned  int  uiToInMs,  char  *  pBsBuf,  unsigned  int  *  puiBsBufSize,  unsigned  int  *  puiSampleTimeInMs  )
 {
	 unsigned  int  uiPts  =  0;
	 SMPL_bsRead_param  param;
	 memset(  &param,  0,  sizeof(  param  )  );

	 return  smplBitstreamReader_ReadNextFrame_func_a_new(  pQdcObjInfoParam,  pold_lPktId,  uiToInMs,  pBsBuf,  puiBsBufSize,  puiSampleTimeInMs,  &uiPts,  &param  );
 }


// 
 int  smplBitstreamReader_ReadNextFrame_func_a_new(  void  *  pQdcObjInfoParam,  long  *  pold_lPktId,  unsigned  int  uiToInMs,  char  *  pBsBuf,  unsigned  int  *  puiBsBufSize,  unsigned  int  *  puiSampleTimeInMs,  unsigned  int  *  puiPts,  SMPL_bsRead_param  *  pParam  )
{
	int  iErr  =  -1;

    //CHECK_POINTER(pBS, MFX_ERR_NULL_PTR);
    //  CHECK_ERROR(m_bInited, false, MFX_ERR_NOT_INITIALIZED);

#ifdef  _DEBUG
		//OutputDebugString(  _T(  "smplBitstreamReader::ReadNextFrame_func called\n"  )  );
#endif

	//
	unsigned  int  nBytesRead = 0;

#if  0
	if  (  pBS->DataOffset  )  {
	    memcpy(pBS->Data, pBS->Data + pBS->DataOffset, pBS->DataLength);
	    pBS->DataOffset = 0;
	}
#endif


#if  0
    nBytesRead = (mfxU32)fread(pBS->Data + pBS->DataLength, 1, pBS->MaxLength - pBS->DataLength, m_fSource);
#else
	BYTE  *  pInput  =  NULL;	//  m_var.inputInfo.pInput;
	unsigned  int  uiInputSize  =  0;	//  m_var.inputInfo.uiInputSize;
	unsigned  int  uiSampleTimeInMs  =  0;	//  2015/01/28
	unsigned  int  uiPts  =  0;				//  2015/02/09
	TCHAR  tBuf[256];
	
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )pQdcObjInfoParam;
	if  (  !pQdcObjInfo  )  {
		showInfo_open0(  0,  0,  _T(  "CMySmpl::ReadNextFrame failed, pQdcObjInfo is null"  )  );
		return    -1;
	}
	//  QDC_OBJ_hdDec	*	pObj	=	(  QDC_OBJ_hdDec  *  )pQdcObjInfo->pObj;
	//CMyDecPipeline  *  pPipeline  =  (  CMyDecPipeline  *  )pObj->pPipeline;
	//
	if  (  !pQdcObjInfo->var.ucbTransformFuncsOk  )  {
		showInfo_open0(  0,  0,  _T(  "CMySmpl::ReadNextFrame failed, ucbTransformFuncsOk false"  )  );
		return  -1;
	}
	
	//  2016/12/13
	QY_TRANSFORM  *  pTransform  =  (  QY_TRANSFORM  *  )pQdcObjInfo->cfg.a.pParent_transform;

	//  2014/07/26
	DWORD  dwTickCnt_start  =  timeGetTime(  );
	//
	for  (  ;  ;  )  {
		 if  (  pQdcObjInfo->cfg.a.pf_bTransformAudioQuit(  pQdcObjInfo->cfg.a.pParent_transform,  0,  0  )  )  return  -1;

		 //
#if  0
		 if  (  !pQdcObjInfo->cfg.a.pf_getNextAPkt(  pQdcObjInfo->cfg.a.pCurPkt,  pQdcObjInfo->cfg.a.pInDataCacheQ,  pQdcObjInfo->cfg.a.pAudioQ2  )  )  {
			 break;	
		 }
#endif
		 //  2016/12/13
		 if  (  !getNextAPktInfo_toDec(  &pTransform->audio.curPktInfo_toDec,  &pTransform->audio.q2  )  )  break;


		 //  2014/07/26
		 if  (  uiToInMs  )  {
			 DWORD  dwTickCnt  =  timeGetTime(  );
			 if  (  dwTickCnt  -  dwTickCnt_start  >  uiToInMs  )  {
				 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "SmplBsReader::LoadNextFrame failed, timeout. toInMs %d"  ),  uiToInMs  );
				 showInfo_open0(  0,  0,  tBuf  );
				 goto  errLabel;
			 }
		 }

		 //
 		 #if  0
			  Sleep(  40  );
		 #else
			  //
			  int  nWaitInMs  =  40;
			  //
			  nWaitInMs  =  100;	//  2015/02/06. 是不是放大点能让cpu更悠闲点。但是，不能影响获取包的实时性
			  //
			  DWORD  dwRet;
			  QY_Q2  *  pAudioQ2  =  (  QY_Q2  *  )pQdcObjInfo->cfg.a.pAudioQ2;
			  dwRet  =  WaitForSingleObject(  pAudioQ2->hEvents[0],  nWaitInMs  );
			  if  (  dwRet  ==  WAIT_FAILED  )  {
				  showInfo_open0(  0,  0,  _T(  "SmplBsReader::LoadNextFrame failed, WaitForSingleObject failed"  )  );
				  goto  errLabel;
			  }
			  #ifdef  __DEBUG__
					  #if  0  
					  {
						  CQyString	tmpStr;
					  switch  (  dwRet  )  {
							  case  WAIT_OBJECT_0:
								    tmpStr  =  _T(  "SmplBsReader::LoadNextFrame: waited"  );
									break;
							  case  WAIT_TIMEOUT:
								    tmpStr  =  _T(  "SmplBsReader::LoadNextFrame: timeout"  );
									break;
							  default:
								      tmpStr  =  _T(  "SmplBsReader::LoadNextFrame: unknown wait ret"  );
									  break;
					  }
					  showInfo_open0(  0,  0,  tmpStr  );
					  }
					  #endif
			  #endif
		 #endif

	}
#if  0
	//  检查一下。每个包都只能处理一次，否则，容易死循环	
	if  (  !pTransform->video.pCurPkt->lPktId_alloc  )  {
		MACRO_qyAssert(  0,  _T(  "pktId 0"  )  );
			  }
			  if  (  pTransform->video.pCurPkt->lPktId_alloc  ==  old_pktId  )  {
				  showInfo_open0(  0,  0,  _T(  "failed: tn_getNextPkt==old_"  )  );
				  goto  errLabel;
			  }
			  old_pktId  =  pTransform->video.pCurPkt->lPktId_alloc;
#endif
	//
	if  (  dec_parseEncAPkt_i_useAudioQ2(  pQdcObjInfo->cfg.a.uiTransformType_pParent,  pQdcObjInfo->cfg.a.pParent_transform,  &pTransform->audio.curPktInfo_toDec,  pold_lPktId,  &pInput,  &uiInputSize,  &uiSampleTimeInMs,  &uiPts  )  )
	{
		showInfo_open0(  0,  0,  _T(  "doTrans_default failed, parsePkt failed"  )  );
		return  -1;	  
	}
	if  (  !uiInputSize  )  {
		showInfo_open0(  0,  0,  _T(  "CMySmpl::ReadNextFrame failed, uiInputSize 0"  )  );
		return  -1;
	}
	if  (  uiInputSize  >  *puiBsBufSize  )  {
		_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "CMySmpl~::ReadNextFrame failed, inputSize %d, dataSize %d:"  ),  uiInputSize,  *puiBsBufSize  );
		showInfo_open0(  0,  0,  tBuf  );
		return  -1;
	}
	//
#ifdef  _DEBUG
		#if  0
		_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "CMySmpl~::ReadNextFrame failed, inputSize %d, dataSize %d:"  ),  uiInputSize,  *puiBsBufSize  );
		showInfo_open0(  0,  0,  tBuf  );
		#endif
		#if  0
			int  nalType  =  M_nalType_h264(  pInput  );
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "BitstreamReader::ReadNextFrame: nalTye %d, len %d"  ),  nalType,  uiInputSize  );
			tmp_showInfo(  tBuf  );
		#endif
#endif
	//  2014/08/05
	//postAPktToSave(  pQdcObjInfo->cfg.a.uiTransformType_pParent,  pQdcObjInfo->cfg.a.pParent_transform,  uiSampleTimeInMs,  uiPts,  (  char  *  )pInput,  uiInputSize  );  
	//
	//  memcpy(  pBS->Data + pBS->DataLength, pInput,  uiInputSize  );  			
	memcpy(  pBsBuf, pInput,  uiInputSize  );  
	nBytesRead  =  uiInputSize;
	//
	//m_var.inputInfo.bFinished  =  TRUE;
#endif
    
    if (0 == nBytesRead)
    {
        return -1;
    }     

    //  pBS->DataLength += nBytesRead;    
	*puiBsBufSize  =  nBytesRead;
	//  2015/01/28
	if  (  puiSampleTimeInMs  )  *puiSampleTimeInMs  =  uiSampleTimeInMs;
	if  (  puiPts  )  *puiPts  =  uiPts;	//  2015/02/09

	//
#if  0
#if  1
	GENERIC_Q  *  pTmpDataQ  =  (  GENERIC_Q  *  )pQdcObjInfo->cfg.a.pTmpDataQ;
	if  (  pTmpDataQ->uiQNodes  <  60	// 30	//  15	//  2015/02/18	//  15	//  5	//  30  //  2014/04/12
		&&  !qPostMsg(  pQdcObjInfo->cfg.a.pCurPkt,  pQdcObjInfo->cfg.a.size_pCurPkt,  (  GENERIC_Q  *  )pQdcObjInfo->cfg.a.pTmpDataQ  )  )  
	{
		pQdcObjInfo->cfg.a.pf_detachPkt(  pQdcObjInfo->cfg.a.pCurPkt,  0  );
		}
	else  {
		  pQdcObjInfo->cfg.a.pf_clean_myPLAY_AUDIO_DATA(  pQdcObjInfo->cfg.a.pCurPkt,  _T(  ""  )  );
	}
#else
	 pQdcObjInfo->cfg.pf_clean_myDRAW_VIDEO_DATA(  pQdcObjInfo->cfg.pCurPkt,  _T(  ""  )  );
#endif
#endif
	 //  2016/12/13
	 clean_PKT_info_toDec(  &pTransform->audio.curPktInfo_toDec,  _T(  ""  )  );




	 //
	 iErr  =  0;

errLabel:
	//
    return  iErr;
}



////////////
//
int smplPCMWriter_WriteNextFrame_pre(  void  *  pQdcObjInfoParam,  void  *  pQDC_OBJ_transCommon,  void  *  pYUVWriter_var  )
{
	int  sts  =  -1;
	BOOL  bMsgGot  =  FALSE;

	QDC_OBJ_transCommon  *  pTrans  =  (  QDC_OBJ_transCommon  *  )pQDC_OBJ_transCommon;
	YUVWriter_var  & m_var  =  *(  YUVWriter_var  *  )pYUVWriter_var;

	if  (  !pTrans->bInited2  )  return  0;

	//
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.pQdcObjInfoParam;
	//
	DEBUG_step_dec	*	pDebugStepDec  =  (  DEBUG_step_dec  *  )getDebugStep_sth(  0,  CONST_debugStepType_dec,  (  MY_DEBUG_STEP  *  )pQdcObjInfo->var.pDebugStep  );
	if  (  !pDebugStepDec  )  return  -1;
	//
	if  (  pQdcObjInfo->cfg.v.uiTransformType_pParent  !=  CONST_uiTransformType_dec  )  goto  errLabel;
	QY_TRANSFORM* pTransform; pTransform = (QY_TRANSFORM*)pQdcObjInfo->cfg.a.pParent_transform;
	//
	MC_VAR_common* pProcInfoCommon; pProcInfoCommon = (MC_VAR_common*)pTransform->pProcInfo;


#if  0
	//
	int  nTimeInMs  =  pDebugStepDec->nTimeInMs_smplYUVWriter_WriteNextFrame0;
	int  tmp_fps  =  0;
	if  (  nTimeInMs  )  {
		tmp_fps   =  1000  /  nTimeInMs;
		pQdcObjInfo->cfg.v.tmp_max_dec_fps  =  tmp_fps;
		}
	else  {
		  tmp_fps  =  pQdcObjInfo->cfg.v.tmp_max_dec_fps;
	}		
	if  (  tmp_fps  >  1  )  {		
		if  (  setPktInputInfo(  pProcInfoCommon,  &pQdcObjInfo->cfg.v.inputInfo,  tmp_fps,  FALSE,  NULL  )  )  {
				#ifdef  __DEBUG__
						traceLog(  _T(  "smplYUVWriter_WriteNextFrame_pre: pkt skipped"  )  );
				#endif
				goto  errLabel;				
		}		
	}
#endif


	sts  =  0;

errLabel:

	return  sts;
}


//
int smplPCMWriter_WriteNextFrame0(  void  *  pQdcObjInfoParam,  void  *  pQDC_OBJ_transCommon,  int  iFourcc,  void  *  pYUVWriter_var,  void *pImg,  PF_data_to_pcm  pf_data_to_pcm,  double  dFrameRate,  LPCTSTR  hint  )
{ 
	int  sts  =  -1;
	BOOL  bMsgGot  =  FALSE;

	QDC_OBJ_transCommon  *  pTrans  =  (  QDC_OBJ_transCommon  *  )pQDC_OBJ_transCommon;
	YUVWriter_var  & m_var  =  *(  YUVWriter_var  *  )pYUVWriter_var;

	//  2015/10/04
	if  (  !hint  )  hint  =  _T(  ""  );

	//
	unsigned  int  i, j, h, w;   

	//  2011/12/04. 因为只能存放一祯，所以需要清0
	if  (  !m_var.pQdcObjInfoParam
		||  !m_var.pPkt  )		
	{
		showInfo_open0(  0,  0,  _T(  "yuvWrite::write failed, pPkt is null. skipped"  )  );
		return  0;
	}
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.pQdcObjInfoParam;
	
#if  0
	DEBUG_step_dec	*	pDebugStepDec  =  (  DEBUG_step_dec  *  )getDebugStep_sth(  0,  CONST_debugStepType_dec,  (  MY_DEBUG_STEP  *  )pQdcObjInfo->var.pDebugStep  );
	if  (  !pDebugStepDec  )  return  -1;
#endif

	//
	DWORD  dwTickCnt_start  =  GetTickCount(  );


	//
#if  10
	if  (  !pTrans->bInited2  )  {


#if  0
		int  imgWidth  =  cropW;	//  pInfo->CropW;
		int  imgHeight  =  cropH;	//  pInfo->CropH;
		if  (  !imgWidth  ||  !imgHeight  )  {
			showInfo_open0(  0,  0,  _T(  "smplYUVWriter_WriteNextFrame failed, imgW or imgH is 0"  )  );
			goto  errLabel;
		}

		//  2014/04/22	 
		//
		BITMAPINFOHEADER  bih;
		//  makeBmpInfoHeader_yv12(  12,  imgWidth,  imgHeight,  &bih  );
		makeBmpInfoHeader_yuv(  iFourcc,  12,  imgWidth,  imgHeight,  &bih  );
		if  (  pQdcObjInfo->cfg.v.dec.pf_updateDecVideoParam(  &bih,  dFrameRate,  pQdcObjInfo->cfg.v.pParent_transform,  pQdcObjInfo->cfg.v.uiTransformType_pParent  )  )  {
			showInfo_open0(  0,  0,  _T(  "decPipeline: updateDecVideoParam  failed"  )  );
			goto  errLabel;
		}

		//  qdcObjInfo.
		pQdcObjInfo->var.cbOutputBuffer  =  M_sizeImage_open(  24,  imgWidth,  imgHeight  );
		pQdcObjInfo->var.cbInputBuffer  =  pQdcObjInfo->var.cbOutputBuffer;
#endif
	
		//
		//
		memset(  &m_var.outputInfo,  0,  sizeof(  m_var.outputInfo  )  );

		//
		pTrans->bInited2  =  TRUE;


	}


#endif


	
	//  2015/01/17
#if  0
	pQdcObjInfo->cfg.a.pf_clean_myPLAY_AUDIO_DATA(  m_var.pPkt,  _T(  "smplYUVWriter"  )  );
	
	//
	unsigned  int  size  =  m_var.size_pPkt;
	if  (  qGetMsg(  (  GENERIC_Q  *  )pQdcObjInfo->cfg.a.pTmpDataQ,  m_var.pPkt,  &size  )  )  {
		TCHAR  tBuf[128]  =  _T(  ""  );
		if  (  !hint  )  hint  =  _T(  ""  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "yuvWrite::write failed, qGetMsg failed. %s"  ),  hint  );
		showInfo_open0(  0,  0,  tBuf  );
		return  -1;
	}
	bMsgGot  =  TRUE;
#endif
	//
	myPLAY_AUDIO_DATA  *  pPkt  =  (  myPLAY_AUDIO_DATA  *  )m_var.pPkt;
	if  (  !pPkt->memory.m_pBuf  )  {
		pPkt->uiSize_dec  =  pQdcObjInfo->var.cbOutputBuffer;
		pPkt->head.uiLen  =  pPkt->uiSize_dec;
		//
		pPkt->memory.m_pBuf  =  (  char  *  )malloc(  pPkt->head.uiLen  );
		if  (  !pPkt->memory.m_pBuf  )  goto  errLabel;
	}

	//
	//QY_AUDIO_HEADER  *  pAh  =  NULL;
	WAVEFORMATEX* pWfx; pWfx = NULL;
	if  (  pQdcObjInfo->cfg.a.pf_parseDecAPkt_o(  m_var.pPkt,  (  void  **  )&pWfx,  &m_var.outputInfo.pBuf,  &m_var.outputInfo.uiOutputSize  )  )  {
		showInfo_open0(  0,  0,  _T(  "parseDecVPkt_o failed"  )  );
		goto  errLabel;
	}
	//
	m_var.outputInfo.bBufTooSmall  =  FALSE;
	m_var.outputInfo.DataOffset  =  0;
	m_var.outputInfo.len  =  0;	

	//
	//QY_AUDIO_HEADER		ah_trans;
	WAVEFORMATEX			wfx_trans;
	if  (  pQdcObjInfo->cfg.a.pf_transformGetWfx(  pQdcObjInfo->cfg.a.pParent_transform,  &wfx_trans,  0  )  )  {
		goto  errLabel;
	}
	if  (  !wfx_trans.wFormatTag  )  {
		showInfo_open0(  0,  0,  _T(  "smplPCMWriter_WriteNextFrame0 failed: ah_trans.wFormatTag is 0"  )  );
		goto  errLabel;
	}
	//  makeBmpInfoHeader_yuv(  iFourcc,  12,  bih_trans.biWidth,  bih_trans.biHeight,  &bih_trans  );


	//
	if  (  pQdcObjInfo->var.usPktResType_dec  !=  CONST_pktResType_sharedTex  )  {


		//
		if  (  pf_data_to_pcm  )  {
			pf_data_to_pcm(  pQdcObjInfo,  pImg,  &m_var  );
		}
		if  (  pPkt->uiSize_dec  <  m_var.outputInfo.len  )  m_var.outputInfo.bBufTooSmall  =  TRUE;
		else  {
			  pPkt->uiSize_dec  =  m_var.outputInfo.len;
		}

		//
		if  (  m_var.outputInfo.bBufTooSmall  )  {
			TCHAR  tBuf[128];
			int  cropW  =  0;
			int  cropH  =  0;
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "yuvWrite::write err, bufTooSmall. bufSize %d, w %d, h %d"  ),  m_var.outputInfo.uiOutputSize,  cropW,  cropH  );
			showInfo_open0(  0,  0,  tBuf  );
			OutputDebugString(  _T(  "qdcSetOutput failed: uiOutputSize too big\n"  )  );							
		}
		
	}

		//
	memcpy(  pWfx,  &wfx_trans,  sizeof(  pWfx[0]  )  );


#ifdef  __TEST_save__
		CHECK_NOT_EQUAL(
			fwrite(  m_var.outputInfo.pBuf,  m_var.outputInfo.len,  1,  m_fDest  ),
			1,  MFX_ERR_UNDEFINED_BEHAVIOR  );
#endif
		

	//
	sts  =  0;

errLabel:

	//
	//pDebugStepDec->nTimeInMs_smplYUVWriter_WriteNextFrame0  =  GetTickCount(  )  -  dwTickCnt_start;

    return sts;	//  MFX_ERR_NONE;
}


//
//  2016/04/09
int smplPCMWriter_WriteNextFrame1(  void  *  pQdcObjInfoParam,  void  *  pQDC_OBJ_transCommon,  void  *  pYUVWriter_var  )
{ 
	int  sts  =  -1;
	//BOOL  bMsgGot  =  FALSE;

	QDC_OBJ_transCommon  *  pTrans  =  (  QDC_OBJ_transCommon  *  )pQDC_OBJ_transCommon;
	YUVWriter_var  & m_var  =  *(  YUVWriter_var  *  )pYUVWriter_var;

	//
	unsigned  int  i, j, h, w;   

	//  2011/12/04. 因为只能存放一祯，所以需要清0
	if  (  !m_var.pQdcObjInfoParam
		||  !m_var.pPkt  )		
	{
		showInfo_open0(  0,  0,  _T(  "yuvWrite::write failed, pPkt is null. skipped"  )  );
		return  0;
	}
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.pQdcObjInfoParam;
	
#if  0
	DEBUG_step_dec	*	pDebugStepDec  =  (  DEBUG_step_dec  *  )getDebugStep_sth(  0,  CONST_debugStepType_dec,  (  MY_DEBUG_STEP  *  )pQdcObjInfo->var.pDebugStep  );
	if  (  !pDebugStepDec  )  return  -1;
#endif

	//
	DWORD  dwTickCnt_start  =  GetTickCount(  );
	
	//  2015/01/17
	myPLAY_AUDIO_DATA  *  pPkt  =  (  myPLAY_AUDIO_DATA  *  )m_var.pPkt;
	if  (  !pPkt->memory.m_pBuf  )  {
		showInfo_open0(  0,  0,  _T(  "smplPCMWriter_WriteNextFrame1 failed, pkt.m_pBuf is null"  )  );
		return  -1;
	}

	//
	if  (  pQdcObjInfo->cfg.a.uiTransformType_pParent  !=  CONST_uiTransformType_dec  )  {
		showInfo_open0(  0,  0,  _T(  "smplPCMWriter_WriteNextFrame1 failed, transformType != dec"  )  );
		return  -1;
	}
	QY_TRANSFORM  *  pTransform  =  (  QY_TRANSFORM  *  )pQdcObjInfo->cfg.a.pParent_transform;

	//  2015/09/30
	//
	unsigned  short  usIndex  =  pTransform->index_activeMems_from;  

	//
	QY_MESSENGER_ID  *  pIdInfo_sender  =  &pTransform->audio.idInfo;
	unsigned  int  uiTranNo_openAvDev  =  pTransform->audio.ta.uiTranNo_openAvDev;  

	//
	//QY_MESSENGER_ID  *  pIdInfo_peer  =  &pAddr->idInfo;

	//
	pPkt->head.idInfo.ui64Id  =  pIdInfo_sender->ui64Id;
	pPkt->head.uiTranNo_openAvDev  =  uiTranNo_openAvDev;

	//
	#if  10
	
	WAVEFORMATEX  *  pWf  =  &pTransform->audio.ta.ah_decompress.wfx;

	//  2016/12/15
	//if  (  !pPkt->head.uiSampleTimeInMs  )  
	{
		int  nAvgBytesPerSec  =  pWf->nAvgBytesPerSec;
		if  (  nAvgBytesPerSec  )  {
			//
			if  (  !pTransform->audio.decInfo.st.lastEnd_iSampleTimeInMs_postDec  )  pTransform->audio.decInfo.st.lastEnd_iSampleTimeInMs_postDec  =  pTransform->audio.decInfo.st.last_iSampleTimeInMs_preDec;

			//
			int  iSampleTimeInMs_calc  =  0;
			//
			int  iDiffInMs  =  pTransform->audio.decInfo.st.last_iSampleTimeInMs_preDec  -  pTransform->audio.decInfo.st.lastEnd_iSampleTimeInMs_postDec;
			if  (  abs(  iDiffInMs  )  >  300  )  {
				iSampleTimeInMs_calc  =  (  pTransform->audio.decInfo.st.lastEnd_iSampleTimeInMs_postDec  +  pTransform->audio.decInfo.st.last_iSampleTimeInMs_preDec  )  /  2;
			}
			else  iSampleTimeInMs_calc  =  pTransform->audio.decInfo.st.lastEnd_iSampleTimeInMs_postDec;				
			//
			long  long  llValInMs  =  1000  *  pPkt->uiSize_dec;
			int  timeLenInMs  =  llValInMs  /  nAvgBytesPerSec;
			unsigned int  uiSampleTimeInMs_end_calc  =  iSampleTimeInMs_calc  +  timeLenInMs;
			pTransform->audio.decInfo.st.lastEnd_iSampleTimeInMs_postDec  =  uiSampleTimeInMs_end_calc;

			//
			pPkt->head.uiSampleTimeInMs  =  iSampleTimeInMs_calc;

			//

		}
	}
    #ifdef  __DEBUG__
		    #if  10
						 TCHAR  tBuf[128];
						 static int  last_st  =  0;
						 int  iDiffInMs;
						 iDiffInMs  =  pPkt->head.uiSampleTimeInMs  -  last_st;  last_st  =  pPkt->head.uiSampleTimeInMs;
						_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "chkFromPlayerIndex_a: st %dms, diff %dms"  ),  pPkt->head.uiSampleTimeInMs,  iDiffInMs  );
						showInfo_open0(  0,  0,  tBuf  );
			#endif
	#endif


	//			
	if  (  !chkFromPlayerIndex_a(  pQdcObjInfo->cfg.a.uiTransformType_pParent,  pQdcObjInfo->cfg.a.pParent_transform,  (  myPLAY_AUDIO_DATA  *  )m_var.pPkt,  0  )  )  {
		
		//  
			//BOOL  bPktRedirected;
			//bPktRedirected  =  FALSE;
			pQdcObjInfo->cfg.a.dec.pf_postAPktToRender(  pQdcObjInfo->cfg.a.pParent_transform,  m_var.pPkt,  NULL  );
			//  don't need to redirect
#if  0
			if  (  bPktRedirected  )  {
				pQdcObjInfo->cfg.a.pf_detachPkt(  m_var.pPkt,  0  );
				}
			else  {
				   pQdcObjInfo->cfg.a.pf_clean_myPLAY_AUDIO_DATA(  m_var.pPkt,  _T(  ""  )  );			  
			}
			bMsgGot  =  FALSE;
#endif
		}
#endif

		sts  =  0;
errLabel:
		
		//pDebugStepDec->nTimeInMs_smplYUVWriter_WriteNextFrame1  =  GetTickCount(  )  -  dwTickCnt_start;
#ifdef  __DEBUG__
#if  0
		TCHAR  tBuf[128];
		GENERIC_Q  *  pTmpQ  =  (  GENERIC_Q  *  )pQdcObjInfo->cfg.pTmpDataQ;		
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "nTime0_write %dms, nTime1_write %dms"  ),  pDebugStepDec->nTimeInMs_smplYUVWriter_WriteNextFrame0,  pDebugStepDec->nTimeInMs_smplYUVWriter_WriteNextFrame1  );
		if  (  pTmpQ  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. cnt_tmpQ %d"  ),  tBuf,  pTmpQ->uiQNodes  );
		}
		showInfo_open0(  0,  0,  tBuf  );
#endif
#endif

		return  sts;
}


//
///
int smplPCMWriter_WriteNextFrame_all(  void  *  pQdcObjInfoParam,  void  *  pQDC_OBJ_transCommon,  int  iFourcc,  void  *  pYUVWriter_var,  void *pImg,  PF_data_to_pcm  pf_data_to_pcm,  double  dFrameRate,  LPCTSTR  hint  )
{
	if  (  !hint  )  hint  =  _T(  ""  );
	//
	if  (  smplPCMWriter_WriteNextFrame0(  pQdcObjInfoParam,  pQDC_OBJ_transCommon,  iFourcc,  pYUVWriter_var,  pImg,  pf_data_to_pcm,  dFrameRate,  hint  )  )  return  -1;
	if  (  smplPCMWriter_WriteNextFrame1(  pQdcObjInfoParam,  pQDC_OBJ_transCommon,  pYUVWriter_var  )  )  return  -1;
	return  0;
}
