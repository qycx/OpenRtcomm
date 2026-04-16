

#ifndef  __qmcTransform_h__
#define  __qmcTransform_h__	//  {

//
#include	"qoi.h"
#include	"qy_qBuf2.h"
#include	"saveAvProc_open.h"



//  2009/05/12
typedef  struct  __transformAudioProcInfo_t						{
				 MACRO_qyQThreadProcInfo_common

				 //
				 QY_qBuf2 *qBuf2;

				 //
				 //int											index_pMems_from;								//  2009/05/28
				 int											index_activeMems_from;								//  2009/05/28

				 //
				 QY_MESSENGER_ID								idInfo;
				 TRAN_audio										ta;												//  2014/11/26
				 
				 //
				 unsigned  int									uiModuleType_toDec;								//  2016/12/05
				 
				 //
				 union											{
					 struct										{
						 HACMDRIVERID							hadid;

						 HACMSTREAM								hstr1;  
						 HACMSTREAM								hstr2;
					 }											acm;
					 MY_DMO_INFO								dmo;											//  2010/06/21

					 //  QDC_OBJ_INFO							qdcObjInfo;		//  2015/09/30	//  custom;
					 QOI_decA									qoi;			//  2016/04/19

				 }												u;
				 
				 //
				 //  2016/12/10
				 myPLAY_AUDIO_DATA						*		pCurPkt;
				 //  
#if  0
				 GENERIC_Q								*		pInDataCacheQ;
				 GENERIC_Q								*		pTmpDataQ;
#endif

				 //  2015/02/14
				 PKT_info_toDec									curPktInfo_toDec;

				 //
				 WAVEFORMATEX						*			pWf_compress;
				 WAVEFORMATEX						*			pWf_pcm;										//  pcm¸ñÊ½
				 WAVEFORMATEX						*			pWf_decompress;									//  pcm¸ñÊ½

				 DWORD											dwBufSize_pcm;
				 char								*			pBuf_pcm;

				 //
				 //myPLAY_AUDIO_DATA								pkt_dec;

				 //  2015/05/19
				 struct											{

					 //  2015/01/15
					 struct										{
						 DWORD									dwTickCnt_start;			//  2015/01/15
						 unsigned  int							uiPts_first;
						 //
						 //
						 unsigned  int							uiPts_lastRecvd;			//  2015/01/15
					 }											pts;

					 //  2016/12/15
					 struct										{
						 int									last_iSampleTimeInMs_preDec;
						 //
						 int									lastEnd_iSampleTimeInMs_postDec;

					 }											st;	

				 }												decInfo;
				 
				 //  2015/05/19
				 struct											{
					 //
					 unsigned  int								uiSize_pSaveAudioPkt;
					 void								*		pSaveAudioPkt;
				 }												saveAudio;
				 

				 //  2012/03/19
				 struct											{
					 unsigned  char								ucbDecFailed;
				 }												status;

				 //
				 unsigned int									tn_dumpAv;

				 //
				 unsigned  char									ucbInited;

}		 TRANSFORM_AUDIO_procInfo;


//
//
typedef  struct  __transformVideoProcInfo_t						{
				 MACRO_qyQThreadProcInfo_common

				 //
				 //int											index_pMems_from;								//  2009/05/28
				 int											index_activeMems_from;								//  2009/05/28

				 //
				 QY_MESSENGER_ID								idInfo;
				 TRAN_video										tv;												//  2014/11/26


				 //
				 DWORD											dwLastmodifiedTickCnt_keyParams;				//  2014/08/05

				 //
				 #ifdef  __DEBUG__
						 //  unsigned  int						biSizeImage_decompress;							//  2009/06/01
			     #endif

				 //  2012/09/09
				 unsigned  int									uiModuleType_toDec;
				 BOOL											bUseDecTool;									//  2015/01/19
				 unsigned  short								usPktResType;									//  2016/04/28

				 //
				 union											{
					 struct										{
						 HIC									hicDecompress;
					 }											vcm;
					 MY_DMO_INFO								dmo;											//  2010/06/21

					 //  QDC_OBJ_INFO							qdcObjInfo;		//  2015/09/30	
					 QOI_decV									qoi;			//  2016/04/19

				 }												u;

				 //
				 //  2014/03/24
				 myDRAW_VIDEO_DATA						*		pCurPkt;
				 //  
				 GENERIC_Q								*		pInDataCacheQ;
				 GENERIC_Q								*		pTmpDataQ;

				 //  2015/01/19
				 DVT_cli										dvtCli;
				 

				 //  2014/04/22
				 struct											{
					 //
					 double										dFrameRate_dec;				//  2014/04/22
					 
					 //
					 bool										bGot_keyFrame;

					 //  2015/01/15
					 struct										{
						 DWORD									dwTickCnt_start;			//  2015/01/15
						 unsigned  int							uiPts_first;
						 //
						 //
						 unsigned  int							uiPts_lastRecvd;			//  2015/01/15
					 }											pts;

					 //
#define		CONST_mutexName_syncIndex_dec						_T(  "syncInd_dec"  )
#define		MAX_cnt_preDec_array								30
//#define		MAX_iDiff_index_preDec								20
					 //
					 int										iSampleTimeInMs_preDec_array[MAX_cnt_preDec_array];
					 unsigned  int								uiPts_preDec_array[MAX_cnt_preDec_array];		//  2015/02/19
					 //
					 DWORD										dwTickCnt_doPretrans[MAX_cnt_preDec_array];		//  2015/02/24
					 //
					 int										iNextIndex_preDec;
					 //
					 int										cnt_preDec;
					 //
					 int										nTimes_needKeyFrame;				//  如果有多次出现 dwLastTickCnt_postDec  +  2000ms < GetTickCount(  ). 就认为是keyFrame丢了 。需要重新申请. 2014/12/06

					 //  2014/06/24
					 long										lDiff_pre_post;

					 //  
					 int										iSampleTimeInMs_postDec;
					 int										cnt_postDec;
					 //  2014/12/06
					 DWORD										dwLastTickCnt_postDec;

					 //  2014/06/28
					 struct										{
						 long									min_lDiff_pre_post;
						 DWORD									dwTickCnt_start;
					 }											lowLatency;
					 

					 //  2014/08/28
					 struct										{
						 DWORD									dwLastTickCnt_applyForKeyFrame;
					 }											applyForKeyFrame;

					 //
					 int										iSampleTimeInMs_lastPkt;

				 }												decInfo;

				 //  2014/08/04
				 struct											{
					 //
					 unsigned  int								uiSize_pSaveVideoPkt;
					 void								*		pSaveVideoPkt;
				 }												saveVideo;

				 //
				 struct {
					 SAVE_av_pktU								tmpBuf_saveAvPkt;
					 //bool										bPost_spspps;
				 }												transSaveAv;


				 //  2012/03/19
				 struct											{
					 unsigned  char								ucbDecOk;
					 unsigned  char								ucbDecFailed;
					 //
					 unsigned  char								ucbNeedReinited;	//  2014/04/07
				 }												status;

				 //
				 unsigned  char									ucbInited;

}		 TRANSFORM_VIDEO_procInfo;


//
//
typedef  struct  __qyTransform_t								{
				 void									*		pProcInfo;
				 MSGR_ADDR								*		pAddr_logicalPeer;
				 int											iTaskId;
				 unsigned  int									uiTaskType;										//  2012/03/25
				 void									*		pTranInfo_unused;								//  AV_TRAN_INFO  *
				 void									*		pTask;											//  PROC_TASK_AV  *
				 void									*		pMsgTask;										//  2014/08/27

				 //
				 //  void								*		pVIDEO_capDev_rtsp;								//  2014/03/25
				 void									*		pCapDev_rtsp;									//  2014/03/25

				 //
				 //  2014/11/11					
				 BOOL											bMosaicVideo;
				 BOOL											bMosaicResource;
				 //  2009/05/29
				 int											index_activeMems_from;
				 
				 //
				 TRANSFORM_AUDIO_procInfo						audio;

				 //
				 //  QY_qThreadProcInfo_common					v_preTransThread;								//  2011/12/09
				 PRETRANS_procInfo								v_preTransThread;								//  2015/02/25
				 //
				 TRANSFORM_VIDEO_procInfo						video;

				 //  2014/08/04
				 SAVE_av_procInfo						*		pSaver;											//  2014/08/04
				 bool											bInited_saver;

				 //  2011/07/03
				 int											iIndex_player;									//  2009/05/02
			 
				 //  2015/06/18
				 TRANS_pts_info									transPtsInfo;										//  2015/06/18
				 
				 //
				 DWORD											dwLastTickCnt_doApplyForPlayer_a;

				 //
				 int											lastPkt_pts_v;
				 unsigned int									lastPkt_uiSampleTimeInMs_v;

				 //
}		 QY_TRANSFORM;


//
//  2014/11/11
#if  0
typedef  struct  __procConfMosaic_t									{
				 //MOSAIC_TRAN_INFO									mosaicTranInfo;
				 //
				 TASK_AV_FROM										taskAvFrom;
				 //				
				 QY_TRANSFORM										transform;

}		 PROC_conf_mosaic;
#endif

//
//  2015/10/07
 BOOL  isPkt_sharedTex(  QY_TRANSFORM  *  pTransform  );


#endif  //  }


