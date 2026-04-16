

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"
#include	"tmpCeLib.h"
#ifndef  __WINCE__
//  #include	"DlgVideos.h"
#endif
//  #include	"qmcVideoCapture_isCli.h"
#include	"qmcVideoCapture.h"
#include	"qmcDmoPublic.h"
#include	"qyCusResTemp.h"

#ifndef  __WINCE__
//#include	"qmcVWall.h"
//  #include	"DlgDynBmps.h"
#endif
#include	"qmcCmdProc.h"

#include	"qySqlFunc.h"
//#include	"qyAvRecordPublic.h"
#include	"saveAvProc_open.h"
#include	<stddef.h>
#include	"qmcCfg.h"
#include <dumpVideo.h>


//
 int  doDecVideoPkt(  QY_TRANSFORM  *  pTransform,  myDRAW_VIDEO_DATA  *  pPkt,  MIS_MSGU  *  pMsgBuf  )
{
	int										iErr						=	-1;
	int	i;
	MC_VAR_common						*	pProcInfo					=	(  MC_VAR_common  *  )pTransform->pProcInfo;	//  QY_GET_procInfo_isCli(  );
	if (  !pProcInfo  )  return  -1;	 
	QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	if  (  !pQmcCfg  )  return  -1;

	MSGR_ADDR			*	pAddr				=	pTransform->pAddr_logicalPeer;
	if  (  !pAddr  )  return  -1;
	int						iTaskId				=	pTransform->iTaskId;
	//
	AV_TRAN_INFO		*	pTranInfo_unused			=	(  AV_TRAN_INFO  *  )pTransform->pTranInfo_unused;
	if  (  !pTranInfo_unused  )  return  -1;
	//
	PROC_TASK_AV		*	pTask				=	(  PROC_TASK_AV  *  )pTransform->pTask;
	if  (  !pTask  )  return  -1;

	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  (  CCtxQmc  *  )pProcInfo,  pTask->iIndex_taskInfo  );
	if  (  !pTaskInfo  )  return  -1;
	if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  return  -1;
	QMC_taskData_conf  *  pTc  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;


	CUS_MODULES  *  pCusModules  =  (  CUS_MODULES  *  )pProcInfo->getCusModules(  );
	if  (  !pCusModules  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "doDecV_pkt failed, pCusModules is null"  )  );
		#endif
		return  -1;
	}	


	int										tmpiRet;
	TCHAR									tHintBuf[128]				=	_T(  ""  );

	//  2014/08/26
	unsigned  int  uiTransformType				=	CONST_uiTransformType_dec;

	//
	for  (  i  =  0;  !pTransform->video.bQuit  &&  i  <  1;  i  ++  )  {
		 //  myDRAW_VIDEO_DATA  *  pPkt  =  &pkts[i];
		 //int  index_pMems_from  =  pPkt->decInfo.index_pMems_from;
		 int  index_activeMems_from  =  pTransform->index_activeMems_from;		//  2014/11/12
		 
		 //		
		 if  (  pPkt->head.uiLen  >  pPkt->memory.uiBufSize  
			 ||  pPkt->uiSize_dec  +  pPkt->uiOffset_enc  +  pPkt->uiLen_enc  >  pPkt->head.uiLen  )  			 
		 {
				#ifdef  __DEBUG__
						 traceLog((TCHAR*)  _T(  "doDecVideo: uiSize_dec or uiLen error"  )  );
				#endif
				return  -1;		 			 
		 }		 
		 char	*	encData	=  pPkt->memory.m_pBuf  +  pPkt->uiSize_dec  +  pPkt->uiOffset_enc;
		 myDRAW_VIDEO_DATA	*	pPkt_dec  =  pPkt;

#if  0
		 TASK_AV_FROM		*	pFrom				=	NULL;

		 pFrom  =  getTaskAvFrom(  pTransform,  index_pMems_from,  index_activeMems_from,  _T(  "doDecVideoPkt"  )  );
		 if  (  !pFrom  )  return  -1;
#endif
		 if  (  index_activeMems_from  <  0  ||  index_activeMems_from  >=  pTc->videoConference.usCntLimit_activeMems_from  )  return  -1;
		 DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from = &pTc->videoConference.activeMems_from[index_activeMems_from];

		 //
		 DWORD					curTickCnt			=	GetTickCount(  );	

#ifdef  __DEBUG__
#endif

		 //
		 if  (  pPkt->debugInfo.dwTickCnt_start  )  {
			 if  (  !pTask->ucbLocalSource_rtspStream  )  {
				 int  iElapse  =  curTickCnt  -  pPkt->debugInfo.dwTickCnt_start;
				 if  (  iElapse  >  pQmcCfg->policy.usTimeoutInMsToSwitch  )  {

					 _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%I64u, %dms, skipped."  ),  pActiveMem_from->avStream.idInfo.ui64Id,  iElapse  );

					 DEBUG_myDRAW_VIDEO_DATA	*	pDebugPkt  =  &pPkt->debugInfo;

					pDebugPkt->usTransInMs  =  curTickCnt  -  pDebugPkt->dwTickCnt_start;
					_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s tE %d, e %d, p %d, d %d, o %d, pt %d, tr %d"  ),  tHintBuf,  (  int  )pDebugPkt->usToEncInMs,  (  int  )pDebugPkt->usEncedInMs,  (  int  )pDebugPkt->usPostInMs,  (  int  )pDebugPkt->usToDispatchInMs,  (  int  )pDebugPkt->usOutputInMs,  (  int  )pDebugPkt->usPreTransInMs,  (  int  )pDebugPkt->usTransInMs  );

					goto  errLabel;
				 }
			 }
		}
		 
		 //
		 if  (  !pTransform->video.ucbInited  )  {
			 traceLogA(  (char*)  "procTaskVideo failed: video is not inited"  );
			 goto  errLabel;
		 }

		 //
		 if  (  pTransform->video.ucbInited  )  {
			 if  (  pTransform->video.index_activeMems_from  !=  index_activeMems_from  
				 ||  pTransform->video.idInfo.ui64Id  !=  pActiveMem_from->avStream.idInfo.ui64Id
				 ||  pTransform->video.tv.uiTranNo_openAvDev  !=  pActiveMem_from->avStream.obj.tranInfo.video.uiTranNo_openAvDev  
				 ||  pTransform->video.status.ucbDecFailed											//  2012/03/19
				 )  
			 {
				 //  2014/04/07
				 pTransform->video.status.ucbNeedReinited  =  TRUE;
				 //
				 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "decVideoPkt failed: trans.active_from %d,id %I64u, tn %d, decFailed %d != %d,%I64u,%d,%d"  ),  
					 pTransform->video.index_activeMems_from,  pTransform->video.idInfo.ui64Id,  pTransform->video.tv.uiTranNo_openAvDev,  (  int  )pTransform->video.status.ucbDecFailed,  
					 index_activeMems_from,  pActiveMem_from->avStream.idInfo.ui64Id,  pActiveMem_from->avStream.obj.tranInfo.video.uiTranNo_openAvDev,  0  );
				 goto  errLabel;
			 }
		 }



		 //  2011/12/14
		 if  (  !pTask->ucbLocalSource_rtspStream  )  {
			 if  (  pPkt->uiSize_dec  <  pTransform->video.tv.vh_decompress.bih.biSizeImage  )  {
				 #ifdef  __DEBUG__
						 traceLogA(  (char*)  (  "mcThreadProc_toShareBmp err: pkt.uiSize_dec %d <  sizeImage %d. skipped"  ),  pPkt->uiSize_dec,  pTransform->video.tv.vh_decompress.bih.biSizeImage  );
				 #endif
				 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "mcThreadProc_toShareBmp err: pkt.uiSize_dec %d !=  sizeImage %d. skipped"  ),  pPkt->uiSize_dec,  pTransform->video.tv.vh_decompress.bih.biSizeImage  );
				 goto  errLabel;
			 }
		 }

		 //  2014/08/07
		 if  (  pTask->saveVideo.ucbSaveVideo_req  )  {
			 if  (  !canSave_fourcc(  pTransform->video.tv.vh_compress.bih.biCompression  )  )  {
				 if  (  GetTickCount(  )  -  pTask->saveVideo.dwLastTickCnt_notification  >  3000  )  {
					 TCHAR  tBuf[128];
					 char	fourccStr[4  +  1];
					 iFourcc2Str(  pTransform->video.tv.vh_compress.bih.biCompression,  fourccStr,  mycountof(  fourccStr  )  );
					 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u's video format [%s] can't be saved"  ),  pActiveMem_from->avStream.idInfo.ui64Id,  CQyString(  fourccStr  )  ); 
					 showNotification(  0,  0,  0,  0,  0,  0,  tBuf  );			 
					 pTask->saveVideo.dwLastTickCnt_notification  =  GetTickCount(  );
				 }
			 }
		 }


		 //
		 BOOL	bDecompressOk  =  FALSE;

		 //
		 pTransform->video.tv.vh_compress.bih.biSizeImage  =  pPkt->uiLen_enc;		//  pPkt->head.uiLen;
		 pTransform->video.tv.vh_decompress.bih.biSizeImage  =  pPkt->uiSize_dec;	//  pProcInfo->cfg.uiBufSize_myDrawVideoData;	//  mycountof(  pPkt_dec->buf  );
		 
		 if  (  pTransform->video.tv.compressor.common.ucCompressors  ==  CONST_videoCompressors_vcm  )  {


				 //
#ifndef  __WINCE__
				 try  {
					  //  tmpiRet  =  ICDecompressBegin(  pFrom->video.u.vcm.hicDecompress,  &pFrom->video.vh_compress.bih,  &pFrom->video.vh_decompress.bih  );
					  tmpiRet  =  ICDecompressBegin(  pTransform->video.u.vcm.hicDecompress,  &pTransform->video.tv.vh_compress.bih,  &pTransform->video.tv.vh_decompress.bih  );
					  }
#ifdef  __useMfc__
				 catch  (  CException  *  e  )  {
						e->Delete(  );
						tmpiRet  =  -1;
				 }
#endif
				 catch  (  ...  )  {
						tmpiRet  =  -1;
				 }
				 if  (  tmpiRet  !=  ICERR_OK  )  {
					 traceLogA(  (char*)  "ICDecompressBegin failed"  );
					 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procTaskVideo: ICDecompressBegin failed"  )  );
					 }
				 else  {
					   try  {
						    //  tmpiRet  =  ICDecompress(  pFrom->video.u.vcm.hicDecompress,  0,  &pFrom->video.vh_compress.bih,  pTransferVideoData->buf  +  iPos,  &pFrom->video.vh_decompress.bih,  pFrom->video.pDecompressBuf  );							
						    tmpiRet  =  ICDecompress(  pTransform->video.u.vcm.hicDecompress,  0,  &pTransform->video.tv.vh_compress.bih,  encData,  &pTransform->video.tv.vh_decompress.bih,  pPkt_dec->memory.m_pBuf  );							
						   }
#ifdef  __useMfc__
					   catch  (  CException  *  e  )  {		//  2009/02/05. 
						      e->Delete(  );
							  tmpiRet  =  -1;
					   }
#endif
					   catch  (  ...  )  {
							  tmpiRet  =  -1;
					   }
					   if  (  tmpiRet  ==  ICERR_OK  )  bDecompressOk  =  TRUE;
					   else  {
						     traceLogA(  (char*)  "ICDecompress failed"  );
						     qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procTaskVideo: ICDecompress failed"  )  );
					   }

					   //
					   //  if  (  (  tmpiRet  =  ICDecompressEnd(  pFrom->video.u.vcm.hicDecompress  )  )  !=  ICERR_OK  )  
					   if  (  (  tmpiRet  =  ICDecompressEnd(  pTransform->video.u.vcm.hicDecompress  )  )  !=  ICERR_OK  )  
					   {
						   traceLogA(  (char*)  "ICDecompressEnd failed"  );					  	
						   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procTaskVideo: ICDecompressEnd failed"  )  );
					   }
				 }
#else
				 traceLog((TCHAR*)  _T(  "vcm is not supported in winCe"  )  );
#endif

				 //  2009/07/27
				 if  (  !bDecompressOk  )  {		//  ½âÑ¹ËõÊ§°Ü²»ÄÜÍË³ö¡£ÒòÎªÓÐÊ±»áÓÐÊý¾Ý°ü´íµÄÇé¿ö¡£
					 _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s %s"  ),  tHintBuf,  _T(  "Decompress failed."  )  );
					 iErr  =  0;  goto  errLabel;
				 }

				 #ifdef  __DEBUG__
						 //  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "transformTaskVideo: decompress %d -> %d"  ),  pTransform->video.vh_compress.bih.biSizeImage,  pTransform->video.vh_decompress.bih.biSizeImage  );
						 #if  0
								traceLogA(  (char*)  "transformV: iSampleTimeInMs %d",  pPkt->head.uiSampleTimeInMs  );
						 #endif
				 #endif
			 
				 // 
				 unsigned  short  usIndex  =  index_activeMems_from;	//  pPkt->head.usIndex;
				 //  
				 if  (  chkFromPlayerIndex_v(  uiTransformType,  pTransform,  pPkt,  0  )  )  continue;

				 //
				 if  (  !pTransform->video.tv.vh_decompress.bih.biSizeImage  )  continue;

				 //
				 memcpy(  &pPkt_dec->bih,  &pTransform->video.tv.vh_decompress,  sizeof(  pPkt_dec->bih  )  );

				 //
				 continue;
	
				 }	
			 else  if  (  pTransform->video.tv.compressor.common.ucCompressors  ==  CONST_videoCompressors_dmo  )  {
					   int  index_dmo  =  0;
#if  0
					   if  (  pFrom->ucbVideoConferenceStarter  )  index_dmo  =  pPkt->head.usIndex;
#endif

					   MACRO_setMyStep(  pTransform->video.debugStep,  61  );

					   //  MY_DMO_INFO	*	pDmoInfo	=  MACRO_getDmo(  pTransform->video.u.dmo.usCnt,  pTransform->video.u.dmo.dmoInfos,  index_dmo  );
					   MY_DMO_INFO	*	pDmoInfo	=  &pTransform->video.u.dmo;
					   if  (  !pDmoInfo  )  goto  errLabel;
					   pDmoInfo->pDebugStep  =  &pTransform->video.debugStep;

					   //  2015/10/01
					   #if  0
							if  (  pDmoInfo->iIndex_player  !=  pTransform->iIndex_player  )  pDmoInfo->iIndex_player  =  pTransform->iIndex_player;
					   #endif
				
					   //  2010/06/20
					   //pDmoInfo->iSampleTimeInMs_audio  =  pFrom->iSampleTimeInMs_audios[index_dmo];

					   //
					   if  (  pQmcCfg->ucb__SUPPORT_dmoToDec__  )  {
						   if  (  decompressVideo_dmo(  pDmoInfo,  (  BITMAPINFO  *  )&pTransform->video.tv.vh_compress.bih,  (  BYTE  *  )encData,  pPkt->head.uiSampleTimeInMs,  0  )  )  {
							   #ifdef  __DEBUG__
									   traceLogA(  (char*)  "procTaskVideo: dmoDecompressVideo failed."  );
							   #endif
							   //  此标志位表明需要重新初始化transform. 2012/03/19
							   pTransform->video.status.ucbDecFailed  =  TRUE;
							   _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s %s"  ),  tHintBuf,  _T(  "decompressVideo_dmo failed."  )  );
							   //
							   goto  errLabel;
						   }
						   }
					   else  {
						     //if  (  decompressVideo_filterGraph(  pDmoInfo,  (  BITMAPINFO  *  )&pTransform->video.tv.vh_compress.bih,  (  BYTE  *  )encData,  pPkt->head.uiSampleTimeInMs,  0  )  )  
							 {
								 #ifdef  __DEBUG__
										 traceLogA(  (char*)  "procTaskVideo: dmoDecompressVideo failed."  );
								 #endif
							     //  此标志位表明需要重新初始化transform. 2012/03/19
								 pTransform->video.status.ucbDecFailed  =  TRUE;
								 _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s %s"  ),  tHintBuf,  _T(  "decompressVideo_fg failed."  )  );
								 //
								 goto  errLabel;
							 }
					   }

					   MACRO_setMyStep(  pTransform->video.debugStep,  171  );

					   unsigned  short  usIndex  =  index_activeMems_from;	//  pPkt->head.usIndex;
					   //  
					   if  (  chkFromPlayerIndex_v(  uiTransformType,  pTransform,  pPkt,  0  )  )  continue;

					   int							j;
					   for  (  j  =  0  ;  ;  j  ++  )  {

						    MACRO_setMyStep(  pTransform->video.debugStep,  172  );

							//
							pTransform->video.tv.vh_decompress.bih.biSizeImage  =  pPkt->uiSize_dec;	//  pProcInfo->cfg.uiBufSize_myDrawVideoData;	//  mycountof(  pPkt_dec->buf  );
							if  (  getDmoOutputByIndex(  pDmoInfo,  j,  (  BYTE  *  )pPkt_dec->memory.m_pBuf,  (  unsigned  int  *  )&pTransform->video.tv.vh_decompress.bih.biSizeImage,  NULL,  NULL  )  )  break;
						
							#ifdef  __DEBUG__
									//  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "transformTaskVideo: decompress %d -> %d"  ),  pTransform->video.vh_compress.bih.biSizeImage,  pTransform->video.vh_decompress.bih.biSizeImage  );
									#if  0
										traceLogA(  (char*)  "transformV: iSampleTimeInMs %d",  pPkt->head.uiSampleTimeInMs  );
									#endif
							#endif
			
							if  (  !pTransform->video.tv.vh_decompress.bih.biSizeImage  )  continue;

							//  2009/05/27
							memcpy(  &pPkt_dec->bih,  &pTransform->video.tv.vh_decompress,  sizeof(  pPkt_dec->bih  )  );

							//
							MACRO_setMyStep(  pTransform->video.debugStep,  175  );
							
							continue;

					   }

					   bDecompressOk  =  TRUE;
					   continue;

					 }
		 			   //  2014/03/17. Note: 对流来说，不能随意丢包是解开包的重要前提。同时，因为流的特殊性，不能提前知道大小，所以不能用同步函数pf_qdcDecompressVideoAndOutput。所以这里可能需要停止使用了
			 else  if  (  10  &&  pTransform->video.uiModuleType_toDec  ==  CONST_moduleType_ipp  )  
					   {
						   CUS_MODULE_U	*	pModule  =  NULL;
						   BITMAPINFOHEADER	bih;

						   //
						   M_getCompressModule(  pCusModules,  pTransform->video.uiModuleType_toDec,  pModule  );

						   //				 
						   if  (  !pModule
							   ||  !pModule->compress.pf_qdcDecompressVideoAndOutput  )  
						   {
							   #ifdef  __DEBUG__
									   traceLog((TCHAR*)  _T(  "pf_qdcDecompressVideoAndOutput not ok"  )  );
							   #endif
							   goto  errLabel;
						   }

						   int  index_dmo  =  0;
#if  0
						   if  (  pFrom->ucbVideoConferenceStarter  )  index_dmo  =  pPkt->head.usIndex;
#endif

						   MACRO_setMyStep(  pTransform->video.debugStep,  61  );

						   //  QDC_OBJ_INFO	*	pDmoInfo	=  MACRO_getDmo(  pTransform->video.u.custom.usCnt,  pTransform->video.u.custom.qdcObjInfos,  index_dmo  );
						   QDC_OBJ_INFO	*	pDmoInfo	=  &pTransform->video.u.qoi.myQoi.common;
						   if  (  !pDmoInfo  )  goto  errLabel;
						   pDmoInfo->var.pDebugStep  =  &pTransform->video.debugStep;

						   //  20134/02/26
						   //  if  (  pTransform->video.ucCompressors  ==  CONST_videoCompressors_stream  )  
						   {
							   if  (  !pTransform->video.status.ucbDecOk  )  {
								   //
								   #ifdef  __DEBUG__
										   #if  1
										   char  fourccStr[4  +  1];
										   iFourcc2Str(  pTransform->video.tv.vh_stream.dwFourcc,  fourccStr,  mycountof(  fourccStr  )  );
										   traceLog((TCHAR*)  _T(  "fourcc %S"  ),  fourccStr  );
										   #endif
								   #endif
								   //
								   if  (  pTransform->video.tv.vh_stream.dwFourcc  ==  CONST_fourcc_h264  )  {
									   //  将sps,pps输入解码
									   int  j;
									   for  (  j  =  0;  j  <  pTransform->video.tv.vh_stream.usCnt;  j  ++  )  {
										    if  (  j  >=  mycountof(  pTransform->video.tv.vh_stream.mems  )  )  break;
											//
										   BITMAPINFOHEADER	bih_enc;
										   memcpy(  &bih_enc,  &pTransform->video.tv.vh_compress.bih,  sizeof(  bih_enc  )  );
										   bih_enc.biSizeImage  =  pTransform->video.tv.vh_stream.mems[j].usLen;
										   //
										   makeBmpInfoHeader_yv12(  12,  pTransform->video.tv.vh_decompress.bih.biWidth,  pTransform->video.tv.vh_decompress.bih.biHeight,  &bih  );
										   if  (  bih.biSizeImage  >  pPkt_dec->uiSize_dec  )  {
   											   #ifdef  __DEBUG__
													   traceLog((TCHAR*)  _T(  "doDecVideo err: bih.biSizeImg %d > uiSize_dec %d"  ),  bih.biSizeImage,  pPkt_dec->uiSize_dec  );
											   #endif
											   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "doDecVideo err: bih.biSizeImg %d > uiSize_dec %d"  ),  bih.biSizeImage,  pPkt_dec->uiSize_dec  );
										   }
										   //
										   bih.biSizeImage  =  min(  bih.biSizeImage,  pPkt_dec->uiSize_dec  );
										   //
										   #ifdef  __DEBUG__
												   if  (  pQmcCfg->debugStatusInfo.ucb__Dump_h265_dec__  )  {
													   static  BOOL  bReset  =  FALSE;
													   char  *  video  =  pTransform->video.tv.vh_stream.mems[j].spsPps;
													   int  len  =  pTransform->video.tv.vh_stream.mems[j].usLen;
													   dumpVideo_init(  mynull,&bReset,  NULL,  _T(  CONST_fn_dump_h265_dec  ),  video,  len,mynull  );
												   }
										   #endif
										   //  2014/08/04
										   if  (  pTask->saveVideo.ucbSaveVideo_req  )  {
											   //
											   char  *  video  =  pTransform->video.tv.vh_stream.mems[j].spsPps;																									
											   int  len  =  pTransform->video.tv.vh_stream.mems[j].usLen;
											   //postVPktToSave(  CONST_uiTransformType_dec,  pTransform,  index_activeMems_from,  0,  0,  video,  len  );  
										   }
										   //
										   tmpiRet  =  pModule->compress.pf_qdcDecompressVideoAndOutput(  pDmoInfo,  (  BITMAPINFO  *  )&bih_enc,  (  BYTE  *  )pTransform->video.tv.vh_stream.mems[j].spsPps,  (  BITMAPINFO  *  )&bih,  (  BYTE  *  )pPkt_dec->memory.m_pBuf  );
										   if  (  tmpiRet  <  0  )  {
											   if  (  tmpiRet  ==  CONST_qdcRet_exception  )  {	//  2014/08/11
												   pTransform->video.status.ucbDecFailed  =  TRUE;
												   showInfo_open0(  0,  0,  _T(  "decV returns exception"  )  );
												   showNotification(  0,  0,  0,  0,  0,  0,  _T(  "decV exception"  )  );
												   goto  errLabel;
											   }
											   if  (  tmpiRet  !=  CONST_qdcRet_bufTooSmall  )  {
												   #ifdef  __DEBUG__
														   traceLogA(  (char*)  "doDecVideo: qdcDecompressVideo spsPps failed."  );
												   #endif
												   goto  errLabel;
											   }
											   showInfo_open0(  0,  0,  _T(  "decV returns bufTooSmall"  )  );
										   }
										   //
										   if  (  bih_enc.biWidth  &&  bih_enc.biHeight  )  {
											   //
											   if  (  pTransform->video.tv.vh_compress.bih.biWidth  &&  pTransform->video.tv.vh_compress.bih.biHeight  )  {
												   if  (  pTransform->video.tv.vh_compress.bih.biWidth  !=  bih_enc.biWidth  )  {
													   goto  errLabel;
												   }
												   if  (  pTransform->video.tv.vh_compress.bih.biHeight  !=  bih_enc.biHeight  )  {
													   goto  errLabel;
												   }
												   }
											   else  {
												     pTransform->video.tv.vh_compress.bih.biWidth  =  bih_enc.biWidth;
													 pTransform->video.tv.vh_compress.bih.biHeight  =  bih_enc.biHeight;
											   }
											   //
											   if  (  pTransform->video.tv.vh_decompress.bih.biWidth  &&  pTransform->video.tv.vh_decompress.bih.biHeight  )  {
												   if  (  pTransform->video.tv.vh_decompress.bih.biWidth  !=  bih_enc.biWidth  )  {
													   goto  errLabel;
												   }
												   if  (  pTransform->video.tv.vh_decompress.bih.biHeight  !=  bih_enc.biHeight  )  {
													   goto  errLabel;
												   }
												   }
											   else  {
												     pTransform->video.tv.vh_decompress.bih.biWidth  =  bih_enc.biWidth;
													 pTransform->video.tv.vh_decompress.bih.biHeight  =  bih_enc.biHeight;
											   }
										   }
									   }
								   }
							   }
						   }

						   makeBmpInfoHeader_yv12(  12,  pTransform->video.tv.vh_decompress.bih.biWidth,  pTransform->video.tv.vh_decompress.bih.biHeight,  &bih  );
						   if  (  bih.biSizeImage  >  pPkt_dec->uiSize_dec  )  {
							   #ifdef  __DEBUG__
									   traceLog((TCHAR*)  _T(  "doDecVideo failed: bih.biSizeImage %d > pkt_dec.uiSize_dec %d"  ),  bih.biSizeImage,  pPkt_dec->uiSize_dec  );
							   #endif
							   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "doDecVideo err: bih.biSizeImg %d > uiSize_dec %d"  ),  bih.biSizeImage,  pPkt_dec->uiSize_dec  );
						   }
						   bih.biSizeImage  = min(  bih.biSizeImage,  pPkt_dec->uiSize_dec  );
						   #ifdef  __DEBUG__
								   if  (  pQmcCfg->debugStatusInfo.ucb__Dump_h265_dec__  )  {
									   char  *  video  =  encData;
									   int  len  =  pTransform->video.tv.vh_compress.bih.biSizeImage;
									   dumpVideo(  NULL,  _T(  CONST_fn_dump_h265_dec  ),  video,  len,mynull  );						   
								   }
						   #endif
						   //  2014/08/04
						   if  (  pTask->saveVideo.ucbSaveVideo_req  )  {
							   //
							   char  *  video  =  encData;							   
							   int  len  =  pTransform->video.tv.vh_compress.bih.biSizeImage;							   
							   //postVPktToSave(  CONST_uiTransformType_dec,  pTransform,  index_activeMems_from,  pPkt->head.uiSampleTimeInMs,  pPkt->head.uiPts,  video,  len  );  
						   }
						   //						
						   tmpiRet  =  pModule->compress.pf_qdcDecompressVideoAndOutput(  pDmoInfo,  (  BITMAPINFO  *  )&pTransform->video.tv.vh_compress.bih,  (  BYTE  *  )encData,  (  BITMAPINFO  *  )&bih,  (  BYTE  *  )pPkt_dec->memory.m_pBuf  );
						   if  (  tmpiRet  <  0  )  {							   											   
							   if  (  tmpiRet  ==  CONST_qdcRet_exception  )  {	//  2014/08/11								   
								   pTransform->video.status.ucbDecFailed  =  TRUE;
								   showInfo_open0(  0,  0,  _T(  "decV returns exception"  )  );
								   showNotification(  0,  0,  0,  0,  0,  0,  _T(  "decV exception"  )  );
								   goto  errLabel;											   
							   }
							   if  (  tmpiRet  !=  CONST_qdcRet_bufTooSmall  )  {
								   #ifdef  __DEBUG__
										   traceLogA(  (char*)  "procTaskVideo: dmoDecompressVideo failed."  );
								   #endif
								   goto  errLabel;
							   }
							   showInfo_open0(  0,  0,  _T(  "decV returns bufTooSmall"  )  );
						   }
						   if  (  tmpiRet  <=  0  )  continue;
						   pTransform->video.status.ucbDecOk  =  TRUE;

						   MACRO_setMyStep(  pTransform->video.debugStep,  171  );

						   //
						   unsigned  short  usIndex  =  index_activeMems_from;	//  pPkt->head.usIndex;
						   //  
						   if  (  chkFromPlayerIndex_v(  uiTransformType,  pTransform,  pPkt,  0  )  )  continue;
				   
						   //
						   #ifdef  __DEBUG__
								   //  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "transformTaskVideo: decompress %d -> %d"  ),  pTransform->video.vh_compress.bih.biSizeImage,  pTransform->video.vh_decompress.bih.biSizeImage  );
								   #if  0
										traceLogA(  (char*)  "transformV: iSampleTimeInMs %d. sizeImg %d",  pPkt->head.uiSampleTimeInMs,  bih.biSizeImage  );
								   #endif
						   #endif
									
						   //
						   if  (  !bih.biSizeImage  )  continue;

						   //  2009/05/27
						   memcpy(  &pPkt_dec->bih,  &bih,  sizeof(  pPkt_dec->bih  )  );

						   //
						   MACRO_setMyStep(  pTransform->video.debugStep,  175  );

						   bDecompressOk  =  TRUE;
						   continue;		 
						   }
			 else  {
				   CUS_MODULE_U	*	pModule  =  NULL;
				   BITMAPINFOHEADER	bih;
				   //
				   M_getCompressModule(  pCusModules,  pTransform->video.uiModuleType_toDec,  pModule  );
				   switch  (  pTransform->video.uiModuleType_toDec  )  {
					   case  CONST_moduleType_ipp:
					   case  CONST_moduleType_mediaSdk_dec:
						     makeBmpInfoHeader_yv12(  12,  pTransform->video.tv.vh_decompress.bih.biWidth,  pTransform->video.tv.vh_decompress.bih.biHeight,  &bih  );
						     break;
					   case  CONST_moduleType_compress:
						     makeBmpInfoHeader_rgb(  24,  pTransform->video.tv.vh_decompress.bih.biWidth,  pTransform->video.tv.vh_decompress.bih.biHeight,  &bih  );
						     break;
					   case CONST_moduleType_ffmpeg:
							makeBmpInfoHeader_i420(12, pTransform->video.tv.vh_decompress.bih.biWidth, pTransform->video.tv.vh_decompress.bih.biHeight, &bih);
							break;

					   default:
							  #ifdef  __DEBUG__
						   			  //  traceLogA(  (char*)  "doDecVideoPkt: ucCompressors error, %d",  pTranInfo->video.compressor.common.ucCompressors  );
									  traceLogA(  (char*)  "doDecVideoPkt: ucCompressors error"  );
							  #endif
							  goto  errLabel;
				   }

				   //				 
				   if  (  !pModule
					   ||  !pModule->compress.pf_qdcDecompressVideo
					   ||  !pModule->compress.pf_qdcGetOutputByIndex  )  goto  errLabel;

				   int  index_dmo  =  0;
#if  0
				   if  (  pFrom->ucbVideoConferenceStarter  )  index_dmo  =  pPkt->head.usIndex;
#endif

				   MACRO_setMyStep(  pTransform->video.debugStep,  61  );

				   //  QDC_OBJ_INFO	*	pDmoInfo	=  MACRO_getDmo(  pTransform->video.u.custom.usCnt,  pTransform->video.u.custom.qdcObjInfos,  index_dmo  );
				   QDC_OBJ_INFO	*	pDmoInfo	=  &pTransform->video.u.qoi.myQoi.common;
				   if  (  !pDmoInfo  )  goto  errLabel;
				   pDmoInfo->var.pDebugStep  =  &pTransform->video.debugStep;

				   					
						   //  20134/02/26
						   if  (  pTransform->video.tv.compressor.common.ucCompressors  ==  CONST_videoCompressors_stream  )  {
							   if  (  !pTransform->video.status.ucbDecOk  )  {
								   if  (  pTransform->video.tv.vh_stream.dwFourcc  ==  CONST_fourcc_h264  )  {
									   //  将sps,pps输入解码
									   int  j;
									   for  (  j  =  0;  j  <  pTransform->video.tv.vh_stream.usCnt;  j  ++  )  {
										    if  (  j  >=  mycountof(  pTransform->video.tv.vh_stream.mems  )  )  break;
											//
											if  (  !pTransform->video.tv.vh_stream.mems[j].usLen  )  continue;
											//
										   BITMAPINFOHEADER	bih_enc;
										   memcpy(  &bih_enc,  &pTransform->video.tv.vh_compress.bih,  sizeof(  bih_enc  )  );
										   bih_enc.biSizeImage  =  pTransform->video.tv.vh_stream.mems[j].usLen;
										   //
										   #if  0
										   makeBmpInfoHeader_yv12(  12,  pTransform->video.vh_decompress.bih.biWidth,  pTransform->video.vh_decompress.bih.biHeight,  &bih  );
										   //  异步解压缩，这里只是输入，所以不需要判断输出缓存大小的问题
										   if  (  bih.biSizeImage  >  pPkt_dec->uiSize_dec  )  {
											   #ifdef  __DEBUG__
													   traceLog((TCHAR*)  _T(  "doDecVideo failed: err: bih.biSizeImg %d > uiSize_dec %d"  ),  bih.biSizeImage,  pPkt_dec->uiSize_dec  );
											   #endif
											   goto  errLabel;
										   }
										   #endif
										   //
										   if  (  pModule->compress.pf_qdcDecompressVideo(  pDmoInfo,  (  BITMAPINFO  *  )&bih_enc,  (  BYTE  *  )pTransform->video.tv.vh_stream.mems[j].spsPps,  pPkt->head.uiSampleTimeInMs  )  <  0  )  {
											   #ifdef  __DEBUG__
													   traceLogA(  (char*)  "doDecVideo: qdcDecompressVideo spsPps failed."  );
											   #endif
											   showInfo_open0(  0,  0,  _T(  "decV spspps failed"  )  );
											   goto  errLabel;
										   }
										   //
										   if  (  bih_enc.biWidth  &&  bih_enc.biHeight  )  {
											   //
											   if  (  pTransform->video.tv.vh_compress.bih.biWidth  &&  pTransform->video.tv.vh_compress.bih.biHeight  )  {
												   if  (  pTransform->video.tv.vh_compress.bih.biWidth  !=  bih_enc.biWidth  )  {
													   goto  errLabel;
												   }
												   if  (  pTransform->video.tv.vh_compress.bih.biHeight  !=  bih_enc.biHeight  )  {
													   goto  errLabel;
												   }
												   }
											   else  {
												     pTransform->video.tv.vh_compress.bih.biWidth  =  bih_enc.biWidth;
													 pTransform->video.tv.vh_compress.bih.biHeight  =  bih_enc.biHeight;
											   }
											   //
											   if  (  pTransform->video.tv.vh_decompress.bih.biWidth  &&  pTransform->video.tv.vh_decompress.bih.biHeight  )  {
												   if  (  pTransform->video.tv.vh_decompress.bih.biWidth  !=  bih_enc.biWidth  )  {
													   goto  errLabel;
												   }
												   if  (  pTransform->video.tv.vh_decompress.bih.biHeight  !=  bih_enc.biHeight  )  {
													   goto  errLabel;
												   }
												   }
											   else  {
												     pTransform->video.tv.vh_decompress.bih.biWidth  =  bih_enc.biWidth;
													 pTransform->video.tv.vh_decompress.bih.biHeight  =  bih_enc.biHeight;
											   }
										   }
									   }
								   }
							   }
						   }

					#ifdef  __DEBUG__
							#if  0
						   unsigned  char  *  pp  =  (  unsigned  char  *  )encData;
						   int  nalType  =  M_nalType_h264(  pp  );
						   TCHAR  tBuf[128];
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "nalType %d|"  ),  nalType  );
						   if  (  pTransform->video.vh_compress.bih.biSizeImage  >  9  )  {
							   for  (  i  =  0;  i  <  9;  i  ++  )  {
								    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s,%d"  ),  tBuf,  (  int  )(  unsigned  char  )encData[i]  );
							   }
						   }
						   showInfo_open0(  0,  0,  tBuf  );

							#endif
					#endif
						   						   
					BITMAPINFOHEADER	bih_enc;					
					memcpy(  &bih_enc,  &pTransform->video.tv.vh_compress.bih,  sizeof(  bih_enc  )  );

				   //
				   if  (  (  tmpiRet  =  pModule->compress.pf_qdcDecompressVideo(  pDmoInfo,  (  BITMAPINFO  *  )&bih_enc,  (  BYTE  *  )encData,  pPkt->head.uiSampleTimeInMs  )  )  <  0  )  {
					   traceLogA(  (char*)  "procTaskVideo: dmoDecompressVideo failed."  );
					   showInfo_open0(  0,  0,  _T(  "decV failed"  )  );
					   goto  errLabel;
				   }
				   //  if  (  !tmpiRet  )  continue;
				   //				   										   
				   if  (  bih_enc.biWidth  &&  bih_enc.biHeight  )  {
											   //
											   if  (  pTransform->video.tv.vh_compress.bih.biWidth  &&  pTransform->video.tv.vh_compress.bih.biHeight  )  {
												   if  (  pTransform->video.tv.vh_compress.bih.biWidth  !=  bih_enc.biWidth  )  {
													   goto  errLabel;
												   }
												   if  (  pTransform->video.tv.vh_compress.bih.biHeight  !=  bih_enc.biHeight  )  {
													   goto  errLabel;
												   }
												   }
											   else  {
												     pTransform->video.tv.vh_compress.bih.biWidth  =  bih_enc.biWidth;
													 pTransform->video.tv.vh_compress.bih.biHeight  =  bih_enc.biHeight;
											   }
											   //
											   if  (  pTransform->video.tv.vh_decompress.bih.biWidth  &&  pTransform->video.tv.vh_decompress.bih.biHeight  )  {
												   if  (  pTransform->video.tv.vh_decompress.bih.biWidth  !=  bih_enc.biWidth  )  {
													   goto  errLabel;
												   }
												   if  (  pTransform->video.tv.vh_decompress.bih.biHeight  !=  bih_enc.biHeight  )  {
													   goto  errLabel;
												   }
												   }
											   else  {
												     pTransform->video.tv.vh_decompress.bih.biWidth  =  bih_enc.biWidth;
													 pTransform->video.tv.vh_decompress.bih.biHeight  =  bih_enc.biHeight;
											   }										   
				   }

				   //
				   MACRO_setMyStep(  pTransform->video.debugStep,  171  );

				   //
				   if  (  !pTask->ucbLocalSource_rtspStream  )  {
					   unsigned  short  usIndex  =  index_activeMems_from;	//  pPkt->head.usIndex
					   //  
					   if  (  chkFromPlayerIndex_v(  uiTransformType,  pTransform,  pPkt,  0  )  )  continue;
				   }
				   //
				   int							j;
				   for  (  j  =  0  ;  ;  j  ++  )  {

					    MACRO_setMyStep(  pTransform->video.debugStep,  172  );


						//
						pTransform->video.tv.vh_decompress.bih.biSizeImage  =  pPkt->uiSize_dec;	//  pProcInfo->cfg.uiBufSize_myDrawVideoData;	//  mycountof(  pPkt_dec->buf  );
						if  (  pModule->compress.pf_qdcGetOutputByIndex(  pDmoInfo,  j,  (  BYTE  *  )pPkt_dec->memory.m_pBuf,  (  unsigned  int  *  )&pTransform->video.tv.vh_decompress.bih.biSizeImage,  NULL,  NULL  )  )  break;
						
						//
						pTransform->video.status.ucbDecOk  =  TRUE;

						//
						#ifdef  __DEBUG__
								//  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "transformTaskVideo: decompress %d -> %d"  ),  pTransform->video.vh_compress.bih.biSizeImage,  pTransform->video.vh_decompress.bih.biSizeImage  );
								#if  0
									traceLogA(  (char*)  "transformV: iSampleTimeInMs %d",  pPkt->head.uiSampleTimeInMs  );
								#endif
						#endif
			
						
						//
						if  (  !pTransform->video.tv.vh_decompress.bih.biSizeImage  )  continue;



						//  2009/05/27
						memcpy(  &pPkt_dec->bih,  &bih,  sizeof(  pPkt_dec->bih  )  );

						//
						MACRO_setMyStep(  pTransform->video.debugStep,  175  );

						
						//	drawVideoData(  pProcInfo,  pTransferVideoData->mems[i].uiSampleTimeInMs,  (  BITMAPINFO  *  )&bih,  (  BYTE  *  )pPkt_dec->buf,  pPkt_dec->head.uiLen,  pTransform->iIndex_player  );
						
						continue;

				   }

				   bDecompressOk  =  TRUE;
				   continue;		 
			 }



	}

	iErr  =  0;
errLabel:

	MACRO_setMyStep(  pTransform->video.debugStep,  181  );


	if  (  iErr  ||  tHintBuf[0]  )  {
		unsigned  int  uiTranNo  =  0;
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "tn %d, %s. %s. l780"  ),  uiTranNo,  (  iErr  ?  _T(  "failed"  )  :  _T(  "OK"  )  ),  tHintBuf  );
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "transformTaskVideo: %s"  ),  tHintBuf  );
		#endif
	}
	
	MACRO_setMyStep(  pTransform->video.debugStep,  199  );

	return  iErr;
}




//


