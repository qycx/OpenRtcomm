

#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
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
#include	"qmcCopyData.h"
#include	"rtspUsrData.h"
#include	"qmcCfg.h"

#include	"qvcfDefs.h"


int  qvcf_doRecvRtsp(  void  *  pQVCF_rtsp  )
{
	int  iErr	=	-1;
	  
	QVCF_rtsp  *  pRtsp  =  (    QVCF_rtsp  *  )pQVCF_rtsp;
	
	unsigned  int  bufSize_toRead  =  1024  *  1024;
	char  *  pBuf_toRead  =  NULL;
	CQyMalloc  mallocObj_pBuf_toRead;
	pBuf_toRead  =  mallocObj_pBuf_toRead.mallocf(  bufSize_toRead  );
	if  (  !pBuf_toRead  )  return  -1;

	unsigned  int  bufSize_pMsgTaskBuf  =  sizeof(  MIS_MSG_TASK  );
	CQyMalloc  mallocObj_pMsgTaskBuf;
	MIS_MSG_TASK  *  pMsgTaskBuf  =  (  MIS_MSG_TASK  *  )mallocObj_pMsgTaskBuf.mallocf(  bufSize_pMsgTaskBuf  );
	if  (  !pMsgTaskBuf  )  return  -1;


	MC_VAR_common						*	pProcInfo					=	(  MC_VAR_common  *  )pRtsp->pProcInfoCommon;	//  
	if (  !pProcInfo  )  return  -1;	 
	
	TCHAR  tBuf[128]  =  _T(  ""  );
	DWORD  dwTickCnt_startToPlay  =  0;
	DWORD  uiSampleTimeInMs_startToPlay  =  0;
	

	FILE  *  fp  =  NULL;
	TCHAR  *  fileName  =  (TCHAR*)_T(  "C:\\tttbbb\\1\\20150510\\1.qvcf"  );
	fileName  =  pRtsp->url;	//  pRtsp->fileName;


	if  (  pRtsp->nTimes_played  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "qvcf_doRecvRtsp, %s has been played"  ),  fileName  );
		showInfo_open0(  0,  0,  tBuf  );
		return  -1;
	}
	pRtsp->nTimes_played  ++  ;

#ifdef  __DEBUG__
	traceLog((TCHAR*)  _T(  "qvcf_doRecvRtsp: called"  )  );
#endif
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "qvcf_doRecvRtsp, %s open"  ),  fileName  );
	showInfo_open0(  0,  0,  tBuf  );
	
	//
	fp  =  _tfopen(  fileName,  _T(  "rb"  )  );
	if  (  !fp  )  goto  errLabel;


	QY_SHARED_OBJ  *  pSharedObj;
	 pSharedObj			=	getSharedObjByIndex(  pProcInfo,  pRtsp->iIndex_sharedObj  );		//  ÕâÀïÒªÓÃindexÀ´»ñÈ¡
	 if  (  !pSharedObj  )  goto  errLabel;

	

	//
	BOOL  bFrameDataStarted  =  FALSE;
	VCF_file_header  fh;
	memset(  &fh,  0,  sizeof(  fp  )  );

	//
	if  (  qvcf_read_fileHeader(  fp,  &fh  )  )  goto  errLabel;


	//
	for  (  ;  ;  )  {
		 if  (  pRtsp->bQuit  )  goto  errLabel;
		 //
		 //
		 VCF_line_common  lineCommon;
		 memset(  &lineCommon,  0,  sizeof(  lineCommon  )  );
		 if  (  qvcf_readLineCommon(  fp,  &lineCommon  )  )  goto  errLabel;
		 //
		 switch  (  lineCommon.usLineType  )  {
				 case  CONST_vcfLineType_streamInfo:  {
					   if  (  bFrameDataStarted  )  goto  errLabel;
					   //
					   unsigned  int  size  =  bufSize_toRead;
					   VCF_streamInfo_u  u;
					   memset(  &u,  0,  sizeof(  u  )  );
					   if  (  qvcf_read_streamInfo(  fp,  &lineCommon,  pBuf_toRead,  size,  &u.common  )  )  {
						   goto  errLabel;
					   }
					   //
					   switch  (  u.common.usDataType  )  {
							   case  CONST_vcfDataType_ucCompressors:
								     if  (  u.common.ucMediaType  ==  CONST_mediumType_audio  )  {
									     //
									     CB_rtsp_res  res;
										 memset(  &res,  0,  sizeof(  res  )  );
										 //
										 int  iIndex_capAudio  =  pSharedObj->iIndex_capAudio;
										 int		iMediumType  =  u.common.ucMediaType;
										 int		iCodecType  =  0;//CONST_codecType_h264;
										 int  iSampleTimeInMs  =  0;
										 unsigned  int  uiPts  =  0;	//  2015/02/09
										 bool  bNeedResp  =  false;	//  2015/01/30
										 int  index  =  0;
										 
										 //									 
										 int  iDataType  =  u.common.usDataType;
										 
										 //							
										 BufferCB_a_rtsp(  pProcInfo,  NULL,  iIndex_capAudio,  iMediumType,  iDataType,  iCodecType,  iSampleTimeInMs,  uiPts,  (  unsigned  char  *  )&u.ucCompressors.ucCompressors,  sizeof(  u.ucCompressors.ucCompressors  ),  pMsgTaskBuf,  &res  );    
									 									 
										 //
									 }
									 else  if  (  u.common.ucMediaType  ==  CONST_mediumType_video  )  {
									     //
									     CB_rtsp_res  res;
										 memset(  &res,  0,  sizeof(  res  )  );
										 //
										 int  iIndex_capBmp  =  pSharedObj->iIndex_capBmp;
										 int		iMediumType  =  u.common.ucMediaType;
										 int		iCodecType  =  0;//CONST_codecType_h264;
										 int  iSampleTimeInMs  =  0;
										 unsigned  int  uiPts  =  0;	//  2015/02/09
										 bool  bNeedResp  =  false;	//  2015/01/30
										 int  index  =  0;
										 
										 //
										 BOOL  bSpsPps  =  FALSE;										
										 int  index_spsPps  =  index;
										 BOOL  bFinished_spsPps  =  FALSE;

									 
										 //
										 int  iDataType  =  u.common.usDataType;
										 
										 //							

										 BufferCB_v_rtsp(  pProcInfo,  NULL,  iIndex_capBmp,  iMediumType,  iDataType,  iCodecType,  iSampleTimeInMs,  uiPts,  (  unsigned  char  *  )&u.ucCompressors.ucCompressors,  sizeof(  u.ucCompressors.ucCompressors  ),  bSpsPps,  index_spsPps,  bFinished_spsPps,  &res  );    
					 

											   }
									 else  {
										   #ifdef  __DEBUG__
												   traceLog((TCHAR*)  _T(  "Err: unprocessed mediumType %d"  ),  u.common.ucMediaType  );
										   #endif
									 }

								     break;
							   case  CONST_vcfDataType_ah:  {
								     //
								     CB_rtsp_res  res;
									 memset(  &res,  0,  sizeof(  res  )  );
									 //
									 int  iIndex_capAudio  =  pSharedObj->iIndex_capAudio;
									 int		iMediumType  =  CONST_mediumType_audio;
#if  1  //def  __DEBUG__
									 int		iCodecType  =  0;//CONST_codecType_h264;
#endif
									 int  iSampleTimeInMs  =  0;
									 unsigned  int  uiPts  =  0;	//  2015/02/09
									 bool  bNeedResp  =  false;	//  2015/01/30
									 int  index  =  0;
									 //
									 
#if  1  //def  __DEBUG__
									 int  iDataType  =  u.common.usDataType;
#endif

									 //
									 BufferCB_a_rtsp(  pProcInfo,  NULL,  iIndex_capAudio,  iMediumType,  iDataType,  iCodecType,  iSampleTimeInMs,  uiPts,  (  unsigned  char  *  )&u.ah.ah,  sizeof(  u.ah.ah  ),  pMsgTaskBuf,  &res  );    
									 
									 //
									 }
									 break;
									 									 							  
							   case  CONST_vcfDataType_vh:  {
								     //
								     CB_rtsp_res  res;
									 memset(  &res,  0,  sizeof(  res  )  );
									 //
									 int  iIndex_capBmp  =  pSharedObj->iIndex_capBmp;
									 int		iMediumType  =  CONST_mediumType_video;
									 int		iCodecType  =  0;//CONST_codecType_h264;
									 int  iSampleTimeInMs  =  0;
									 unsigned  int  uiPts  =  0;	//  2015/02/09
									 bool  bNeedResp  =  false;	//  2015/01/30
									 int  index  =  0;
									 //
									 BOOL  bSpsPps  =  FALSE;										
									 int  index_spsPps  =  index;
									 BOOL  bFinished_spsPps  =  FALSE;
									 
									 //
									 int  iDataType  =  u.common.usDataType;

									 //
									 BufferCB_v_rtsp(  pProcInfo,  NULL,  iIndex_capBmp,  iMediumType,  iDataType,  iCodecType,  iSampleTimeInMs,  uiPts,  (  unsigned  char  *  )&u.vh.vh,  sizeof(  u.vh.vh  ),  bSpsPps,  index_spsPps,  bFinished_spsPps,  &res  );    
									 
									 //
									 }
								     break;

							   case  CONST_vcfDataType_spsPps:  {
								     //
								     BOOL  bSpsExists  =  FALSE;
									 {
										 int  i;
										 for  (  i  =  0;  i  <  u.spsPps.vh_stream.usCnt;  i  ++  )  {
											 if  (  u.spsPps.vh_stream.mems[i].usLen  )  {
												 bSpsExists  =  TRUE;
												 break;
											 }
										 }
									 }
									 if  (  !bSpsExists  )  break;

								     //
								     CB_rtsp_res  res;
									 memset(  &res,  0,  sizeof(  res  )  );
									 //
									 int  iIndex_capBmp  =  pSharedObj->iIndex_capBmp;
									 int		iMediumType  =  CONST_mediumType_video;
									 int		iCodecType  =  CONST_codecType_h264;
									 int  iSampleTimeInMs  =  0;
									 unsigned  int  uiPts  =  0;	//  2015/02/09
									 bool  bNeedResp  =  false;	//  2015/01/30
									 int  index  =  0;
									 //
									 BOOL  bSpsPps  =  TRUE;										
									 int  index_spsPps  =  index;
									 BOOL  bFinished_spsPps  =  FALSE;
									 
									 //
									 int  iDataType  =  0;

									 //
									 for  (  index  =  0;  index  <  u.spsPps.vh_stream.usCnt;  index  ++  )  {
										  char  *  tmppBuf  =  u.spsPps.vh_stream.mems[index].spsPps;
										  unsigned  int  uiLen  =  u.spsPps.vh_stream.mems[index].usLen;
										  //
										  index_spsPps  =  index;
										  //								
										  BufferCB_v_rtsp(  pProcInfo,  NULL,  iIndex_capBmp,  iMediumType,  iDataType,  iCodecType,  iSampleTimeInMs,  uiPts,  (  unsigned  char  *  )tmppBuf,  uiLen,  bSpsPps,  index_spsPps,  bFinished_spsPps,  &res  );    
									 }
									 //
									 index_spsPps  =  index;										 
									 bFinished_spsPps  =  TRUE;
									 BufferCB_v_rtsp(  pProcInfo,  NULL,  iIndex_capBmp,  iMediumType,  iDataType,  iCodecType,  iSampleTimeInMs,  uiPts,  (  unsigned  char  *  )NULL,  0,  bSpsPps,  index_spsPps,  bFinished_spsPps,  &res  );    
									 
									 //
									 }
								     break;
							   default:
									  #ifdef  __DEBUG__
											  traceLog((TCHAR*)  _T(  "qvcf_doRecvRtsp: streamInfo, unprocessed usDataType"  )  );
									  #endif
									  break;
					   }

					   }
					   break;
				 case  CONST_vcfLineType_frame:  {
					   bFrameDataStarted  =  TRUE;
					   //
					   unsigned  int  size  =  bufSize_toRead;
					   VCF_frame_header  frameHeader;
					   memset(  &frameHeader,  0,  sizeof(  frameHeader  )  );
					   if  (  qvcf_read_frame(  fp,  &lineCommon,  &frameHeader,  pBuf_toRead,  &size  )  )  {
						   goto  errLabel;
					   }
					   //
					   if  (  frameHeader.ucMediaType  ==  CONST_vcfMediaType_v  )  {
						   if  (  !dwTickCnt_startToPlay  )  {
							   dwTickCnt_startToPlay  =  GetTickCount(  );
							   uiSampleTimeInMs_startToPlay  =  frameHeader.uiSampleTimeInMs;
							   }
						   else  {
							     int  iSleepInMs  =  25;
								 //
								 int  elapseInMs_tickCnt  =  GetTickCount(  )  -  dwTickCnt_startToPlay;
								 int  elapseInMs_ts  =  frameHeader.uiSampleTimeInMs  -  uiSampleTimeInMs_startToPlay;
								 //
								 iSleepInMs  =  elapseInMs_ts  -  elapseInMs_tickCnt;
								 //
								 #ifdef  __DEBUG__
										 #if  0
										 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "qvcf_doRecvRtsp: iSleepInMs %d"  ),  iSleepInMs  );
										 showInfo_open0(  0,  0,  tBuf  );
										 #endif
								 #endif
								 //
								 BOOL  bNeedAdjust  =  FALSE;
								 if  (  iSleepInMs  <  0  )  {								
									 if  (  iSleepInMs  <  -200  )  bNeedAdjust  =  TRUE;
									 iSleepInMs  =  0;									
									 }
								 else  if  (  iSleepInMs  >  200  )  {
										   iSleepInMs  =  200;
										   bNeedAdjust  =  TRUE;									 
								 }
								 if  (  bNeedAdjust  )  {
									 dwTickCnt_startToPlay  =  GetTickCount(  )  +  iSleepInMs;
									 uiSampleTimeInMs_startToPlay  =  frameHeader.uiSampleTimeInMs;
								 }
								 //
								 if  (  iSleepInMs  )  {
									 #ifdef  __DEBUG__
											 traceLog((TCHAR*)  _T(  "qvcf_doRecvRtsp: Sleep( %d ). bAdjust %d"  ),  iSleepInMs,  bNeedAdjust  );			 
									 #endif
									 //
									 Sleep(  iSleepInMs  );		 						   
								 }
						   }
					   }

					   //
					   switch  (  frameHeader.ucMediaType  )  {
							   case  CONST_vcfMediaType_a:  {								   					   								    
								     CB_rtsp_res  res;
									 memset(  &res,  0,  sizeof(  res  )  );
									 //
									 int  iIndex_capAudio  =  pSharedObj->iIndex_capAudio;
									 int		iMediumType  =  CONST_mediumType_audio;
#if  1  //  def  __DEBUG__
									 int		iCodecType  =  0;//CONST_codecType_h264;
#endif
									 int  iSampleTimeInMs  =  frameHeader.uiSampleTimeInMs;
									 unsigned  int  uiPts  =  0;	//  2015/02/09
									 bool  bNeedResp  =  false;	//  2015/01/30
									 int  index  =  0;
									 
									 //
									 int  iDataType  =  0;

									 //
									 BufferCB_a_rtsp(  pProcInfo,  NULL,  iIndex_capAudio,  iMediumType,  iDataType,  iCodecType,  iSampleTimeInMs,  uiPts,  (  unsigned  char  *  )pBuf_toRead,  size,  pMsgTaskBuf,  &res  );    
									 }
								     break;
							   case  CONST_vcfMediaType_v:  {					   								    
								     CB_rtsp_res  res;
									 memset(  &res,  0,  sizeof(  res  )  );
									 //
									 int  iIndex_capBmp  =  pSharedObj->iIndex_capBmp;
									 int		iMediumType  =  CONST_mediumType_video;
#if  1  //  def  __DEBUG__
									 int		iCodecType  =  0;//CONST_codecType_h264;
#endif
									 int  iSampleTimeInMs  =  frameHeader.uiSampleTimeInMs;
									 unsigned  int  uiPts  =  0;	//  2015/02/09
									 bool  bNeedResp  =  false;	//  2015/01/30
									 int  index  =  0;
									 //
									 BOOL  bSpsPps  =  FALSE;										
									 int  index_spsPps  =  index;
									 BOOL  bFinished_spsPps  =  FALSE;
									 
									 //
									 int  iDataType  =  0;

									 //
									 index_spsPps  =  0;										 
									 bFinished_spsPps  =  FALSE;
									 BufferCB_v_rtsp(  pProcInfo,  NULL,  iIndex_capBmp,  iMediumType,  iDataType,  iCodecType,  iSampleTimeInMs,  uiPts,  (  unsigned  char  *  )pBuf_toRead,  size,  bSpsPps,  index_spsPps,  bFinished_spsPps,  &res  );    
									 }
									 break;
							   default:
										#ifdef  __DEBUG__
												traceLog((TCHAR*)  _T(  "qvcf_doRecvRtsp failed, unprocessed frame mediaType"  )  );
										#endif
										goto  errLabel;
									
					   }

					   //
					   }
					   break;
				 default:
						#ifdef  __DEBUG__
								traceLog((TCHAR*)  _T(  "unprocessed lineType"  )  );
						#endif
						goto  errLabel;
		 }

		 //  qvcf_read_
	}

	


	//
	iErr  =  0;
errLabel:

	if  (  fp  )  fclose(  fp  );

	//
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "qvcf_doRecvRtsp %s closed. iErr %d"  ),  fileName,  iErr  );
	showInfo_open0(  0,  0,  tBuf  );

	//
	return  iErr;
}