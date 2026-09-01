



#include	"stdafx.h"

#include	<stddef.h>
#include	<mmsystem.h>
#include	<dmo.h>
#include	<dsound.h>
#include	<time.h>

#include	"isCliSaveAvCommon.h"

#if 0
#include	"qyMcMainCommon.h"
#include	"qyDynLib.h"

#include	"qyMcMainRealTimeMediaProc.h"

#include	"tmpCeLib.h"

#include	"qyAvRecord.h"
#include	"qyAvRecord_dx.h"
#include	"qmcSound_dx.h"

#include	"qmcVideoCapture_isCli.h"
#include	"qmOpenCommon.h"
#include	"saveAvProc.h"

#include	"qmcCommFunc_isCli.h"
#include	"ctxMcThread.h"
#endif
#include <saveAvProc_open.h>




#if  10  //  2015/02/17
extern  "C"  __declspec(  dllexport  )  int  qvcf_doSaveAv(  void  *  pTransform,  SAVE_av_pktU  *  pSp,  BOOL  *  pbExists_pSvp,  CTX_mc_saveAv  *  pCtx  )
{
	int									iErr						=	-1;

	int								iFourcc_file = 0;

#if 0
	PROC_TASK_AV					*	pTask						=	(  PROC_TASK_AV  *  )pTransform->pTask;	
	if  (  !pTask  )  return  -1;
	

	MC_VAR_isCli					*	pProcInfo					=	(  MC_VAR_isCli  *  )pTransform->pProcInfo;//  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	QY_MC							*	pQyMc						=	(  QY_MC  *  )pProcInfo->pQyMc;//  
	if  (  !pQyMc  )  return  -1;

	 SAVE_av_procInfo				*	pSave						=	&pTransform->saveThread;
	 unsigned  int  len;
	 TCHAR								dirName[MAX_PATH]			=	_T(  ""  );
	 TCHAR								fileName[MAX_PATH]			=	_T(  ""  );
	 char								timeBuf[CONST_qyTimeLen  +  1];
	 char								buf[256]					=	"";
	 BOOL								bSvpNew						=	FALSE;




	 DWORD  dwTickCnt_start  =  GetTickCount(  );
	 DWORD  dwTickCnt_flush  =  0;

	 for  (  ;!pSave->bQuit  ;  )  {

		 //
		 DWORD  dwTickCnt  =  GetTickCount(  );
		 if  (  dwTickCnt  -  dwTickCnt_start  >  pProcInfo->cfg.policy.uiTimeOfVideoFileInS  *  1000  )  {
			 showInfo_open0(  0,  0,  _T(  "doSaveAv: timeOfVideoFile is big enough."  )  );
			 goto  errLabel;
		 }
		 		 
		 //
		 if  (  pSave->fp  )  {
			 if  (  dwTickCnt  -  dwTickCnt_flush  >  30  *  1000  )  {			  			
				 dwTickCnt_flush  =  dwTickCnt;
			
				 switch  (  iFourcc_file  )  {			
						 case  CONST_fourcc_h264:
						 case  CONST_fourcc_vp80:
						 default:										  
								if  (  doFileFlush(  fileName,  pSave  )  )  goto  errLabel;							
								break;			  						   
				 }		  					   
			 }
		 }

		 //
		 if  (  !*pbExists_pSvp  )  {
			 //

			 //
			 len  =  sizeof(  pSp[0]  );		
			 if  (  q2GetMsg(  &pSave->q2,  pSp,  &len  )  )  {
				 Sleep(  300  );
				 continue;
			 }
			 //
			 bSvpNew  =  TRUE;
			 }
		 else  {
			   *pbExists_pSvp  =  FALSE;
		 }

		 //		 
		 int  index_pMems_from  =  pSp->common.index_pMems_from;
		 
		 TASK_AV_FROM		*	pFrom				=	NULL;
		 pFrom  =  getTaskAvFrom(  pTransform,  index_pMems_from,  pTransform->index_activeMems_from,  _T(  "qvcf_doSaveAv"  )  );
		 if  (  !pFrom  )  goto  errLabel;

		 if  (  !pSave->fp  )  {			 
			 {
				 CQySyncObj	syncObj;	
				 TCHAR		mutexName[128]  =  _T(  ""  );		
				 M_getMutexName_syncActiveMem(  &pProcInfo->cfg,  pTransform->iTaskId,  mutexName, mycountof(  mutexName  )  );
				 
				 if  (  syncObj.sync(  mutexName  )  )  goto  errLabel;
				 
				 //  2015/05/19
				 pSave->audio.idInfo.ui64Id  =  pFrom->idInfo.ui64Id;
				 		
				 //
				 pSave->audio.ta  =  pFrom->audio.ta_recvd;
				 		 
				 //
				 pSave->video.idInfo.ui64Id  =  pFrom->idInfo.ui64Id;
				 pSave->video.usMaxFps_toShareBmp  =  pFrom->video.tv_recvd.compressor.common.usMaxFps_toShareBmp;
				 pSave->video.tv  =  pFrom->video.tv_recvd;
		 		 		 
				 //
				 //pSave->video.dwLastModifiedTickCnt_keyParams  =  pTransform->video.dwLastmodifiedTickCnt_keyParams;	 
			 }
	 	
			 //
			 time_t  t;  time(  &t  );  getTimelStr(  t,  timeBuf,  mycountof(  timeBuf  )  );
			 memcpy(  buf,  timeBuf,  8  );  buf[8]  =  0;
			 	 
			 //
			 TCHAR  *  capScreenDir  =  _T(  "c:\\tttbbb\\test\\"  );
			 capScreenDir  =  pProcInfo->cfg.policy.dirToSaveVideo;
			 if  (  !mybDir(  capScreenDir  )  )  {
				 TCHAR	tBuf[128];
				 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "SaveVideo failed, dir to save [%s] not exists"  ),  capScreenDir  );
				 if  (  GetTickCount(  )  -  pSave->video.dwLastTickCnt_notification  >  3000  )  {
					 showNotification(  0,  0,  0,  0,  0,  0,  tBuf  );
					 pSave->video.dwLastTickCnt_notification  =  GetTickCount(  );		 
				 }		 
				 //		 		 
				 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. try to empty saveQ"  ),  tBuf  );		 
				 showInfo_open0(  0,  0,  tBuf  );
				 emptyQ2(  &pSave->q2  );		 
				 //
				 goto  errLabel;	 
			 }	 	 	 
			 _sntprintf(  dirName,  mycountof(  dirName  ),  _T(  "%s\\%s"  ),  CQyString(  capScreenDir  ),  CQyString(  buf  )  );  
			 if  (  !mybDir(  dirName  )  )  {
				 if  (  !CreateDirectory(  dirName,  NULL  )  )  goto  errLabel;
			 }
			 if  (  tTrailDir(  dirName,  mycountof(  dirName  )  )  )  goto  errLabel;
			 	 
			 //
			 TCHAR	talkerDesc[128];
			 MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pProcInfo->getMisCntByName(  _T(  ""  )  );
			 if  (  !pMisCnt  )  goto  errLabel;
			 getTalkerDesc(  pMisCnt,  &pSave->video.idInfo,  talkerDesc,  mycountof(  talkerDesc  ),  0,  0  );  
	 	 
			 //	 
			 TCHAR								tName[128]					=	_T(  ""  );
			 _sntprintf(  tName,  mycountof(  tName  ),  _T(  "%s_%I64u_%s%d_%s_%S"  ),  talkerDesc,  pSave->video.idInfo.ui64Id,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  ),  pTask->saveVideo.uiObjType  ),  pTask->saveVideo.usIndex_obj,  pQyMc->appParams.appObjPrefix,  timeBuf  +  8  );
			 
	 
			 //
			 iFourcc_file  =  pSave->video.tv.vh_compress.bih.biCompression;	 
			 if  (  iFourcc_file  ==  CONST_fourcc_vp8_bad  )  iFourcc_file  =  CONST_fourcc_vp80;	 
			 //
			 #ifdef  __DEBUG__
			 {
				    char  fourccStr[4  +  1];
					TCHAR  tBuf[128];
					iFourcc2Str(  iFourcc_file,  fourccStr,  mycountof(  fourccStr  )  );		
					int  ii;
					ii  =  0;
			 }
			 #endif
			 //
			 switch  (  iFourcc_file  )  {
					 case  CONST_fourcc_h264:
					 case  CONST_fourcc_vp80:
						   _sntprintf(  fileName,  mycountof(  fileName  ),  _T(  "%s%s.qvcf"  ),  dirName,  tName  );
						   if  (  doFileHead_qvcf(  pTransform,  fileName,  iFourcc_file,  pSave,  pCtx  )  )  goto  errLabel;				   
						   break;
			 default:
				    char  fourccStr[4  +  1];
					TCHAR  tBuf[128];
					iFourcc2Str(  iFourcc_file,  fourccStr,  mycountof(  fourccStr  )  );
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "doSaveAv failed: %s not supported"  ),  CQyString(  fourccStr  )  );
					showInfo_open0(  0,  0,  tBuf  );
				    goto  errLabel;
					break;	 
			 }	 
			 //
			 pSave->audio.frame_cnt  =  0;
			 pSave->video.frame_cnt  =  0;			 
		 }



		 //
		 switch  (  pSp->common.uiMediaType  )  {
				 case  CONST_vcfMediaType_a:  {					 
					   SAVE_audio_pkt  *  pSap  =  &pSp->aPkt;
					   		  
			   		   #ifdef  __DEBUG__
							   traceLog(  _T(  "saveThread: sap->uiLen %d, len %d "  ),  pSap->uiLen,  len  );
					   #endif

					   //
					   if  (  pSap->idInfo.ui64Id  !=  pSave->audio.idInfo.ui64Id
						   ||  pSap->uiTranNo_openAvDev  !=  pSave->audio.ta.uiTranNo_openAvDev
						   ||  pSap->iFourcc  !=  pSave->audio.ta.ah_compress.wfx.wFormatTag  )
					   {
						   if  (  bSvpNew  )  {			//  不许老的包重复循环，所以用bSvpNew来设定
							   *pbExists_pSvp  =  TRUE;			  
						   }
						   goto  errLabel;		  
					   }
					   
					   
					   //
					   VCF_frame_header  vfh;
					   memset(  &vfh,  0,  sizeof(  vfh  )  );		  
					   //
					   vfh.idInfo.ui64Id  =  pSave->audio.idInfo.ui64Id;	
					   vfh.uiTranNo  =  pSave->audio.ta.uiTranNo_openAvDev;	
					   vfh.ucMediaType  =  pSp->common.uiMediaType;	//  CONST_vcfMediaType_a;	
					   //  vfh.timestamp  =  0;
					   vfh.uiSampleTimeInMs  =  pSap->uiSampleTimeInMs;
					   vfh.uiPts  =  pSap->uiPts;
					   		  
					   //
					   unsigned  int  len  =  pCtx->uiBufSize_pBuf;
					   if  (  qvcf_write_frameInfo(  &vfh,  pSap->buf,  pSap->uiLen,  (  char  *  )pCtx->pBuf_forSaving,  &len,  pSave->fp  )  )  goto  errLabel;
					   if  (  fwrite(  pSap->buf,  pSap->uiLen,  1,  pSave->fp  )  !=  1  )  goto  errLabel;
					   		  
					   //
					   pSave->audio.frame_cnt  ++  ;
					   		  
					   }				   
					   break;
				 case  CONST_vcfMediaType_v:  {
					   SAVE_video_pkt  *  pSvp  =  &pSp->vPkt;
					   		  
   			   		   #ifdef  __DEBUG__
							   traceLog(  _T(  "saveThread: svp->uiLen %d, len %d "  ),  pSvp->uiLen,  len  );
							   #if  0
									traceLog(  _T(  "TEST: saveThread skip vPkt"  )  );
									continue;
							   #endif
					   #endif

					   //
					   if  (  pSvp->idInfo.ui64Id  !=  pSave->video.idInfo.ui64Id
						   ||  pSvp->uiTranNo_openAvDev  !=  pSave->video.tv.uiTranNo_openAvDev
						   ||  pSvp->iFourcc  !=  pSave->video.tv.vh_compress.bih.biCompression  )
					   {
						   if  (  bSvpNew  )  {			//  不许老的包重复循环，所以用bSvpNew来设定
							   *pbExists_pSvp  =  TRUE;			  
						   }
						   goto  errLabel;		  
					   }
					   
					   //
#if  0
					   if  (  pSave->video.dwLastModifiedTickCnt_keyParams  !=  pTransform->video.dwLastmodifiedTickCnt_keyParams  )  {
						   CQySyncObj	syncObj;
						   TCHAR		mutexName[128]  =  _T(  ""  );		
						   M_getMutexName_syncActiveMem(  &pProcInfo->cfg,  pTransform->iTaskId,  mutexName, mycountof(  mutexName  )  );
			  
						   if  (  syncObj.sync(  mutexName  )  )  goto  errLabel;
						   			  
						   if  (  pSave->video.bih_enc.biCompression  !=  pTransform->video.tv.vh_compress.bih.biCompression  )  goto  errLabel;
						   //
						   if  (  pSave->video.bih_enc.biWidth  !=  pTransform->video.tv.vh_compress.bih.biWidth  
							   ||  pSave->video.bih_enc.biHeight  !=  pTransform->video.tv.vh_compress.bih.biHeight  )
						   {
							   pSave->video.bih_enc.biWidth  =  pTransform->video.tv.vh_compress.bih.biWidth;			
							   pSave->video.bih_enc.biHeight  =  pTransform->video.tv.vh_compress.bih.biHeight;
							   //
							   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "doSaveAv: wh changed"  )  );			  
						   }
						   
						   pSave->video.dwLastModifiedTickCnt_keyParams  =  pTransform->video.dwLastmodifiedTickCnt_keyParams;
						   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "doSaveAv: keyParams changed"  )  );		  
		  
					   }
#endif
					   
					   //
					   VCF_frame_header  vfh;
					   memset(  &vfh,  0,  sizeof(  vfh  )  );		  
					   //
					   vfh.idInfo.ui64Id  =  pSave->video.idInfo.ui64Id;	
					   vfh.uiTranNo  =  pSave->video.tv.uiTranNo_openAvDev;	
					   vfh.ucMediaType  =  pSp->common.uiMediaType;//CONST_vcfMediaType_v;	
					   //  vfh.timestamp  =  0;
					   vfh.uiSampleTimeInMs  =  pSvp->uiSampleTimeInMs;
					   vfh.uiPts  =  pSvp->uiPts;
					   		  
					   //
					   unsigned  int  len  =  pCtx->uiBufSize_pBuf;
					   if  (  qvcf_write_frameInfo(  &vfh,  pSvp->buf,  pSvp->uiLen,  (  char  *  )pCtx->pBuf_forSaving,  &len,  pSave->fp  )  )  goto  errLabel;
					   if  (  fwrite(  pSvp->buf,  pSvp->uiLen,  1,  pSave->fp  )  !=  1  )  goto  errLabel;
					   		  
					   //
					   pSave->video.frame_cnt  ++  ;
					   		  
					   //
					   }
					   break;
				 default:
						#ifdef  __DEBUG__
								traceLog(  _T(  "qvcf_doSaveAv failed: unprocessed type"  )  );
						#endif
						showInfo_open0(  0,  0,  _T(  "qvcf_doSaveAv failed, unprocessed type"  )  );
						goto  errLabel;
						break;	 
		 }		 
	 }
#endif

	 //
	 iErr  =  0;
errLabel:

	 //
#if 0
	 doFileEnd_qvcf(  iFourcc_file,  pSave  );

	 if  (  pSave->fp  )  {
		 fclose(  pSave->fp  );  pSave->fp  =  NULL;
	 }
#endif


	 return  iErr;
}
#endif



