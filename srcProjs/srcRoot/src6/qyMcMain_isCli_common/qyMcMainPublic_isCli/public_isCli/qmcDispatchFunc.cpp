
#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>
#include	<mmsystem.h>
#include	<dmo.h>
#include	<dsound.h>

#include	"qyMcMainCommon.h"
#include	"qyDynLib.h"

#include	"qyMcMainRealTimeMediaProc.h"

#include	"tmpCeLib.h"

#include	"qyAvRecord.h"
#include	"qyAvRecord_dx.h"
#include	"qmcSound_dx.h"

#include	"qmcVideoCapture_isCli.h"



//
//
__declspec(  dllexport  )  int  dispatch_outputConfVideo(  PROC_TASK_AV  *  pTask,  MIS_MSG_TASK  *  pMsgTask,  TRANSFER_VIDEO_DATA  *  pTransferVideoData,  QY_MESSENGER_ID  *  pIdInfo_from,  int  uiTranNo_openAvDev_conf  )
{
	int  iErr  =  -1;

	MIS_CNT				*	pMisCnt				=	(  MIS_CNT  *  )pMsgTask->pMisCnt;
	if  (  !pMisCnt  )  return  -1;
	int  tmpiRet;
	int  i;

		//
	if  (  !pTransferVideoData->usCnt  )  {
		pTransferVideoData->usCnt  =  1;	//  
		pTransferVideoData->mems[0].uiLen  =  pTransferVideoData->uiLen;
	}
	if  (  pTransferVideoData->usCnt  >  mycountof(  pTransferVideoData->mems  )  )  goto  errLabel;


	//  2009/05/31  
	//  if  (  pTask->ucbVideoConferenceStarter  )  
	

		//
		unsigned  int				uiChannelType				=	CONST_channelType_media;
		time_t						tStartTran;					mytime(  &tStartTran  );  
		unsigned  char				ucbNeedShowFrameInfo		=	FALSE;

		//  unsigned  short  usFrames_perSecond;	usFrames_perSecond  =  pProcInfo->cfg.policy.video.usFrames_perSecond_videoConference;

		unsigned  char				ucFlg						=	0;
		unsigned  int	uiTranNo;  if  (  (  uiTranNo  =  getuiNextTranNo(  0,  0,  0  )  )  ==  -1  )  goto  errLabel;
		int							lenInBytes					=	0;

		if  (  pTask->ucbVideoConferenceStarter  )  {

			//  convert format in order to send to group
			for  (  i  =  0;  i  <  pTransferVideoData->usCnt;  i  ++  )  {
				 pTransferVideoData->mems[i].idInfo.ui64Id  =  pIdInfo_from->ui64Id;  //pFrom->idInfo.ui64Id;
#if  0
				 pTransferVideoData->mems[i].usIndex_ii  =  0;	//  index_activeMems_from;
#endif
				 //  2012/01/09
				 pTransferVideoData->mems[i].uiTranNo_openAvDev  =  pTransferVideoData->uiTranNo_openAvDev;//uiTranNo_openAvDev_from;	//  pFrom->video.tv_recvd.uiTranNo_openAvDev;		 

				 //  2017/09/11
				 #ifdef  __DEBUG__
						 if  (  pTransferVideoData->mems[i].stat.tSelectTime  )  {
							 int  ii  =  0;
						 }
				 #endif
			}
			//
			pTransferVideoData->uiTranNo_openAvDev  =  uiTranNo_openAvDev_conf;

			}
		else  if  (  pTask->doProxy.bExists_avProxy  )  {	//  2014/11/21
				  //  convert format in order to send to group
				  for  (  i  =  0;  i  <  pTransferVideoData->usCnt;  i  ++  )  {
					  pTransferVideoData->mems[i].idInfo.ui64Id  =  0;		//  pIdInfo_from->ui64Id;  //pFrom->idInfo.ui64Id;
#if  0
					  pTransferVideoData->mems[i].usIndex_ii  =  0;			//  index_activeMems_from;
#endif
					  //  2012/01/09
					  pTransferVideoData->mems[i].uiTranNo_openAvDev  =  0;	//  uiTranNo_openAvDev_from;	//  pFrom->video.tv_recvd.uiTranNo_openAvDev;		 			
				  }
			      
				  }
		else  {
			  #ifdef  __DEBUG__
					  traceLog(  _T(  "dispatch_outputConfVideo failed, serious err"  )  );
			  #endif
			  goto  errLabel;
		}


		//  qyShowInfo1(  CONST_qyShowType_debug,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "will send tn [%d]"  ),  uiTranNo  );
			
		if  (  tmpiRet  =  q2PostMsg(  pMsgTask,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsgTask->lenInBytes,  pTask->photomosaic.pOutputQ2,  _T(  "dispatch_outputConfVideo"  ))) {
				 if  (  tmpiRet  !=  CONST_qyRet_qFull  )  goto  errLabel;
				 //  iErr  =  0;  goto  errLabel;				
		}

		MIS_CHANNEL	*	pChannel;		
		if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  uiChannelType  )  )  )  goto  errLabel;

		//
		chkToApplyForChannel(  (  CCtxQmc  *  )pMisCnt->pProcInfoParam,  uiChannelType, false  );

		//
		q2PostMsgAndTrigger(  0,  0,  &pChannel->outputQ2,  _T(  "dispatch_outputConfVideo"  ));		//  触发一下发送
		
	
	iErr  =  0;

errLabel:
	return  iErr;

}



