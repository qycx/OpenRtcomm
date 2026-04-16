

#ifndef  __qmcSharedObj_h__
#define  __qmcSharedObj_h__	//  {


//
#include	"syncMtCnt.h"

//
#include	"qoi.h"
#include	"aecPublic.h"
#include	"videoInputInfo1.h"
#include	"saveAvProc_open.h"
#include <dumpVideo.h>


//
typedef  struct  __route_sendLocalAv							{
				 
				 int											iIndex_misCnt;									//  
				 MSG_ROUTE										route;
				 QY_MESSENGER_ID								videoConference_idInfo_to;						//  2007/11/30, 

				 //  2017/09/17
				 struct											{															//  2009/09/11
					 time_t										tModifiedTime;
					 time_t										tRecvTime_lastResp;
					 struct										{
						 time_t									tModifiedTime;
						 time_t									tRecvTime_lastResp;
					 }											mems[CONST_maxMsgrs_sendTo];
				 }												routeInfo;

				 //
				 MSG_ROUTE										route_confAv;									//  2025/01/21

}		 ROUTE_sendLocalAv;										// 


//
//  2015/10/11
typedef  struct  __evtCli_t										{
					 
				 unsigned  int									tn_cliPipe;		

				 //
				 void									*		pVideoCapDev;
			 
				 //  2015/02/01
				 VT_process										vtProcess;
				 
				 //  2015/01/30				
				 QY_shm											dataShm;
				 					 
				 //				
				 struct											{
						 //				
						 TCHAR									evtName_syncR[32];				
						 HANDLE									hEvent_syncR;

						 //  2015/02/19
						 TCHAR									evtName_syncW[32];				
						 HANDLE									hEvent_syncW;

				 }												writeShm;
				
				 struct											{
					 //
					 DWORD										dwLastTickCnt_encDataGot;
					 //
					 struct										{
						 int									nTimes_noEncData;
						 DWORD									dwStartTickCnt_noEncData;		//  2016/04/18
					 }											noEncData;

				 }												status;

				 //

				 //
				 BOOL											bQuit;

}		 EVT_cli;



//  2008/10/04
typedef  struct  __compressVideo_t								{

				 BOOL											bVideoCompressInited1;										//  

				 //  
				 unsigned  int									uiTranNo_openAvDev_org;										//  2010/09/04

				 //
				 int											left,  top;													//  
				 int											width,  height;
				 
				 //
				 VIDEO_COMPRESSOR_CFG							compressor;													//  2009/03/27


				 //  2012/09/15
				 unsigned  int									uiModuleType_toEnc;
				 
				 //  2015/10/13
				 unsigned  char									ucbUseEvt;

				 //
				 union											{
					 struct										{
						 HIC									hicLocal;

						 BOOL									bVIDCF_QUALITY;												//  
						 int									iQuality;													//  
					 }											vcm;
					 MY_DMO_INFO								dmo;

					 //QDC_OBJ_INFO								qdcObjInfo;													//  2015/10/11	//  custom;
					 QOI_encV									qoi;														//  2016/04/19
				 }												u;

				 QY_VIDEO_HEADER								vh_decompress;												//  2009/03/29

				 //
				 QY_VIDEO_HEADER								vh_compress;				 
				 VH_stream										vh_stream;													//  2014/02/25
				 
				 //  2014/05/03
				 unsigned  char									ucbResizeByEncoder;

				 //
				 int											iCompressBufSize;
				 char										*	pCompressBuf;

				 //
				 TRANSFER_VIDEO_DATA						*	pReqBuf_myVideoCapture;										//  myVideoCapure

				 //  2014/04/02
				 myDRAW_VIDEO_DATA						*		pCurPkt;
				 //
				 GENERIC_Q									*	pInDataCacheQ;
				 GENERIC_Q									*	pTmpDataQ;

				 
				 // 
				 unsigned  char									ucbFixedRate;												//  

				 //
				 unsigned  char									ucSeconds_perFrame_expected;								//  
				 unsigned  short								usFrames_perSecond_expected;								//  
				 time_t											tSelectTime;												//  
				 DWORD											dwTickCnt_selectTime;										//  
				 unsigned  int									uiCnt_pkts_fromSelect;										//  SelectTime							
				 float											fFps_sending;												//  uiCnt_pkts_fromSelect / (  GetTickCount(  )  -  dwTickCnt_selectTime  )
				 //
				 //BOOL											tmp_bMediaChannelReady;										//  
				 //unsigned  char									tmp_ucbNotSendData;											//  2011/07/29, 仅用于记录
					 
				 unsigned  char									ucTimeoutInS_showFrameInfoResp;								//  showFrameInfo
				 //
				 VIDEO_input_info1								input_BufferCB;
				 
				 //
				 VIDEO_input_info1								input_doPostEnc_forTest;
				 
				 //
				 time_t											tLastTime_sendVideo;										//  
				 unsigned  short								usFramesThisSecond_toSend;									//  
				 unsigned  short								usFps_toSend;
				 //
				 time_t											tLastTime_post;												//  2011/12/07
				 
				 //
				 time_t											tLastTime_showFrameInfo;									//  
				 
				 //  
				 time_t											tFirstTime_showFrameInfo_withoutResp;						//  
				 time_t											tRecvTime_resp_fromCli;

				 //
				 unsigned  short								usFps_ok;													//  
				 BOOL											bTopFrames;													//  
				 //
				 unsigned  short								usTimes_ok;
				 unsigned  short								usTimes_failure;											//  
				 //
																															//  
																															//	
																															//	Frames_perSecond_expected usFrames_perSecond_ok
																															//  usFrames_perSecond_ok.ÐèÒªÓÐusTimes_noErr
																															//  usTimes_err
																															//  



				 //
				 //
#define		MAX_cnt_preEnc_array		30
				 //
				 struct											{					
					 //  2014/04/22
					 int										iSampleTimeInMs_preEnc_array[MAX_cnt_preEnc_array];
					 int										iNextIndex_preEnc_unused;
					 unsigned  int								cnt_preEnc;
					 //
					 int										iNextIndex_postEnc_unused;
					 int										iSampleTimeInMs_postEnc;
					 unsigned  int								cnt_postEnc;

					 //  2014/08/15
					 DWORD										dwTickCnt_startToForceKeyFrame;

					 //  2025/10/22
					 int										iSampleTimeInMs_startToCalcElapseInMs_fromLastPkt;			//  选择一个起点，完整的传输sampleTimeInMs. 以后的每帧，只传elapseInMs_fromLastPkt
																															//  每5秒选一个
					 int										iSampleTimeInMs_lastPkt;

					 //
					 int										totalPkts;						//  2026/03/04

					 //
				 }												encInfo;

				 //  2010/12/28
				 TCHAR											tag_dbg[64];		//  2016/04/02
				 struct											{
					 time_t										tStart;
					 int										nStep;
				 }												debugInfo;
				 int											iVal_dbg;			//  2017/09/05

				 //
				 AnDumpVideoObj									dumpVideoObj;


				 //
				 void										*	pData;


}		 COMPRESS_VIDEO;


//
typedef  struct  __compressAudio_t								{

				 BOOL											bCompressInited;
				 
				 //  unsigned  int									uiTranNo_openAvDev;										//  tranNo
				 unsigned  int									uiTranNo_openAvDev_org;										//  tranNo. 2010/09/04
				 AUDIO_COMPRESSOR_CFG							compressor;

				 unsigned int									uiModuleType_toEnc;											//  2015/02/14

				 //
				 union											{
					 struct										{
						 HACMDRIVERID							hadid;

						 HACMSTREAM								hstr1;														//  2009/07/14
						 HACMSTREAM								hstr2;
					 }											acm;
					 MY_DMO_INFO								dmo;
					 
					 //QDC_OBJ_INFO								custom;
					 QOI_encA									qoi;				//  2016/04/19
				 }												u;

				 //
				 QY_AUDIO_HEADER								ah_decompress;												//  2009/05/16
				 QY_AUDIO_HEADER								ah_pcm;														//  2009/05/16
				 QY_AUDIO_HEADER								ah_compress;												//  2009/05/16
				 //  2016/12/17
				 AH_stream										ah_stream;													//  2016/12/16

				 //
				 char										*	pPcmBuf;
				 DWORD											dwPcmBufSize;
				 char										*	pDstBuf;
				 DWORD											dwDstBufSize;

				 TRANSFER_AUDIO_DATA						*	pReqCache;													//  2008/05/25


				 //  2015/02/13
				 myPLAY_AUDIO_DATA							*	pCurPkt;
				 //
				 GENERIC_Q									*	pInDataCacheQ;


				 //
				 unsigned  char									ucTimeoutInS_showFrameInfoResp;								//  ´Ó·¢³öshowFrameInfoµ½µÃµ½respµÄ³¬Ê±

				 

				 // 
				 time_t											tSelectTime;												//  ÐÞ¸ÄÖ¡ËÙÊ±¼ä					

				 unsigned  short								usCnt_pkts;													//  ´ÓÉÏÒ»¸ö

				 //
				 time_t											tLastTime_sendAudio;										//  ·¢°üµÄÊ±¼ä					 
				 time_t											tLastTime_showFrameInfo;									//  ÉÏÒ»´ÎµÄ·¢ËÍÖ¡ËÙÐÅÏ¢

				 //
				 time_t											tFirstTime_showFrameInfo_withoutResp;
				 time_t											tRecvTime_resp_fromCli;

				 //
				 //  2015/09/10
				 struct											{					
					 //  2014/04/22
					 //unsigned  int							cnt_preEnc;
					 //
					 unsigned  int								cnt_postEnc;

					 //
					 int										iSampleTimeInMs_startToCalcElapseInMs_fromLastPkt;
					 int										iSampleTimeInMs_lastPkt;


					 //
					 //  2016/12/15
					 struct										{

						 //
					 }											st;

				 }												encInfo;



}		 COMPRESS_AUDIO;



//
#define		CONST_capType_null									0
#define		CONST_capType_av									1
#define		CONST_capType_screen								2
#define		CONST_capType_mediaFile								3
#define		CONST_capType_mediaDevice							4			//  2011/12/28
//
#define		CONST_capType_mosaic								20			//  2013/12/10. d3dWall的欢迎字幕，或者note等
//
#define		CONST_capType_slave									25			//  2016/04/06

//
#define		CONST_capType_qvcf									30			//  2015/05/25, 本地播放qvcf文件，不需要压缩，不需要resize


//
#define		CONST_subCapType_null								0
#define		CONST_subCapType_webcam								1
#define		CONST_subCapType_mosaic_video						2			//  2014/12/01
#define		CONST_subCapType_mosaic_resource					3			//  2014/12/01
//
#define		CONST_subCapType_unresizable						10			//  2015/03/11
//
#define		CONST_subCapType_slave_video						20			//  2016/04/06	




//  2014/11/13
#define		CONST_capUsage_null									0
#define		CONST_capUsage_conf									1
#define		CONST_capUsage_3dConf								2			//  2014/12/15
#define		CONST_usage_mosaic_sys								3			//  2014/12/21



//
typedef  struct  __capBmp_saveAv_t {
				 SAVE_av_pktU		tmpBuf_saveAvPkt;
				 bool				bPost_spspps;
}		 CapBmp_saveAv;



//
//  2015/05/06. 把vpp分成3段，vpp负责把原始格式转成rgp. vpp_proc负责处理，比如字幕。vpp_beforeEnc负责把格式转成yv12之类							
//
#define		MACRO_capProcInfo_bmpMems							unsigned  int				uiType;						\
																unsigned  int				uiSubtype;					\
																int							iIndex_sharedObj;			\
																unsigned  int				uiTranNo_sharedObj;			\
																HWND						curhWnd;					\
																QY_VIDEO_HEADER				vh_org;						\
																DWORD						dwTickCnt_lastVideoGot;		\
																HIC							hicOrg2Rgb;					\
																QY_VIDEO_HEADER				vh_rgb;						\
																int							iOrg2RgbBufSize;			\
																char				*		pOrg2RgbBuf;				\
																BOOL						bOrg2RgbBufInited;			\
																QY_qThreadProcInfo_common	vppThread;					\
																QY_qThreadProcInfo_common	thread;						\
																QY_qThreadProcInfo_common	postThread;					\
																COMPRESS_VIDEO				compressVideo;				\
																CapBmp_saveAv				capBmpSaveAv;


//
#define		MACRO_capProcInfo_audioMems							unsigned  int				uiType;						\
																int							iIndex_sharedObj;			\
																unsigned  int				uiTranNo_sharedObj;			\
																WAVEFORMATEX				wf_org;						\
																DWORD						dwTickCnt_lastAudioGot;		\
																QY_qThreadProcInfo_common	appThread;					\
																QY_qThreadProcInfo_common	thread;						\
																COMPRESS_AUDIO				compressAudio;	            \
                                                                void*                       ctxResample;


                                                                //RESAMPLE_AUDIO				resampleAudio;	
                                                                    


//  Note: capProcInfo_bmpMems中的curhWnd是产生视频的窗口，sharedObj里的窗口是显示用的。不能混为一谈。
//  在qmCmd进程里，也没有sharedObj. 所以curhWnd不能删除。 2010/08/31

typedef  struct  __capProcInfo_bmpCommon_t						{
					MACRO_capProcInfo_bmpMems
}		 CAP_procInfo_bmpCommon;		

typedef  struct  __capProcInfo_audioCommon_t					{
				 MACRO_capProcInfo_audioMems
}		 CAP_procInfo_audioCommon;


//  2010/07/26
#define		CONST_camCapType_null								0
#define		CONST_camCapType_vfw								1
#define		CONST_camCapType_directX							2
#define		CONST_camCapType_rtsp								3		//  2014/02/23
//
#define		CONST_camCapType_qvcf								4		//  2015/05/11
//
#define		CONST_camCapType_ic									5		//  industrial camera

//
#define		CONST_camCapType_slave								50		//  2014/09/29. 虚拟的流捕获，实际是另一个流的resize

//
#define		CONST_camCapType_mosaic								55		//  2014/10/30

//
#define		CONST_camCapType_custom								100		//  2013/03/18. 2014/09/29





//  2009/03/18
typedef  struct  __capProcInfo_video_t							{
				 MACRO_capProcInfo_bmpMems

				 //
				 unsigned  int									uiCamCapType;

				 //  2017/09/13
				 TCHAR											displayName[256  +  1];	
				 
				 //
				 struct											{
					 void								*		pVideoCapDev;
					 
					 //  2014/02/23. vfw暂时保留
					 struct										{
						 HWND									hCapWnd;
						 BOOL									bCapWndInited;
						 unsigned  short						usCapDriverIndex;
					 }											vfw;

				 }												capDev;

				 //
				 struct											{
					 BITMAPINFOHEADER							bih;
					 //
				 }												policy;		 

				 //
				 BOOL											bCapDevConnected;
				 BOOL											bCaptureStarted;
				 DWORD											dwTickCnt_captureStarted;		//  2017/09/19

				 //  2017/09/14
				 BOOL											bCaptureStarted_openLocalVideo;


}		 CAP_procInfo_video;


typedef  struct  __capProcInfo_screen_t							{
				 MACRO_capProcInfo_bmpMems

}		 CAP_procInfo_screen;


typedef  struct  __capProcInfo_mediaFileBmp_t					{
				 MACRO_capProcInfo_bmpMems

				 //
}		 CAP_procInfo_mediaFileBmp;

//  2011/12/28
typedef  CAP_procInfo_video										CAP_procInfo_mediaDeviceBmp;

//
typedef  union  __capProcInfoBmpU_t								{
				CAP_procInfo_bmpCommon							common;
				CAP_procInfo_video								video;
				CAP_procInfo_screen								screen;
				CAP_procInfo_mediaFileBmp						mediaFile;
				CAP_procInfo_mediaDeviceBmp						mediaDevice;
}		 CAP_procInfo_bmpU;




//  2010/08/03
#define		CONST_recordType_null								0
#define		CONST_recordType_waveform							1
#define		CONST_recordType_dSound								2		//  2013/03/18
#define		CONST_recordType_directX							3		//  2013/03/18
#define		CONST_recordType_msAec								4		//  2013/05/22
//
#define		CONST_recordType_coreAudio							5		//  2017/01/28
//
#define		CONST_recordType_webRtc								7		//  2017/06/15
//
#define		CONST_recordType_custom								10		//  2013/03/18


//  2009/02/10
//

typedef  struct  __capProcInfoRecordSound_t						{
				 MACRO_capProcInfo_audioMems

				 unsigned  int									uiRecordType;												//  2010/08/03

				 //  2013/03/18
				 union											{
					 struct										{
						 void  *								pAudioCapDev;
					 }											dx;
					 struct										{
						 void  *								pObj;
					 }											webRtc;
				 }												u;

				 //  2011/10/24
				 GUID											guid_aDevice;												//  被选中的audio device
				 TCHAR											capDevDesc[64];												//  2013/05/25
				 TCHAR											aec_rendDevDesc[64];

				 //  2013/08/02. 录制的线程是这里, 将audioMems.thread留给压缩
				 QY_qThreadProcInfo_common						recThread;				

				 //
				 QY_qThreadProcInfo_common						aecThread;

				 //
				 BOOL											bLocalAudioPlaying;											//  

				 //  
				 DWORD											dwTickCnt_sendLocalAv;										//  2010/05/04

				 //
				 unsigned  short								usErrors_processInput;										//  2009/05/09
				 //
				 BOOL											bInputErr_aec;												//  2013/05/26. 如果aec没有本地player在运行,就会出错
				 DWORD											dwStartTickCnt_inputErr;									//  2015/02/06. 如果inputErr持久超过5秒，就要退出线程。用户可以在申请发言时，重新初始化aec
				 //
				 DWORD											dwLastTickCnt_toStartLocalAudioPlayer;						//  2013/05/26

				 //
				 unsigned  short								usTimes_ok;													//  
				 unsigned  short								usTimes_failure;											//  

				 //  2013/03/18
				 BOOL											bCapDevConnected;
				 BOOL											bCaptureStarted;

				 //
				 struct											{

					 int										bufSize_pAudioDataBuf;	//  =  pProcInfo->cfg.uiBufSize_myPlayAudioData;
					 char						*				pAudioDataBuf;			//   if  (  !(  pAudioDataBuf  =  (  char  *  )mallocObj_pAudioDataBuf.mallocf(  bufSize_pAudioDataBuf  )  )  )  goto  errLabel;

					 //
					 int										nBytes_toRecord;	//  =  pRecordSoundProcInfo->compressAudio.compressor.uiBytesRecorded_perBlockAlign  *  pRecordSoundProcInfo->compressAudio.ah_decompress.wfx.nBlockAlign;
					 int										nAvgBytesPerSec;	//  =  pRecordSoundProcInfo->compressAudio.ah_decompress.wfx.nAvgBytesPerSec;

					 //
					 int										dataLen_pAudioDataBuf;

					 //
					 void						*				 pMsgBuf;

				 }												cache;

}		 CAP_procInfo_recordSound;


typedef  struct  __capProcInfoMediaFileAudio_t					{
				 MACRO_capProcInfo_audioMems

				 //  
}		 CAP_procInfo_mediaFileAudio;

//  2011/12/28
typedef  CAP_procInfo_mediaFileAudio							CAP_procInfo_mediaDeviceAudio;

//
typedef  union  __capProcInfoAudioU_t							{
				 CAP_procInfo_audioCommon						common;
				 CAP_procInfo_recordSound						recordSound;
				 CAP_procInfo_mediaFileAudio					mediaFileAudio;
				 CAP_procInfo_mediaDeviceAudio					mediaDeviceAudio;
}		 CAP_procInfo_audioU;


//////////////





//
typedef  struct  __sharedObjUsr_t								{
				 HWND											hWnd_starter;												//  2009/08/21
				 unsigned  int									uiTaskType;													//  2009/12/23
				 int											iTaskId;													//  2009/08/23
				 //
				 //QY_MESSENGER_ID								idInfo_to;
				 unsigned  char									ucbVideoConferenceStarter;
				 unsigned  char									ucbVideoConference;											//  2018/11/10

				 //
				 unsigned  int									uiTranNo_openAvDev_a;										//  2010/09/04
				 unsigned  int									uiTranNo_openAvDev_v;										//  2010/09/04

				 //
				 //unsigned  char									ucbNotSendData;												//  2009/02/22

				 //
				 //int											iIndex_activeMems_from_videoConferenceStarter;				//  2009/05/30

				 //  2015/05/23
				 BOOL											bIn3DConf;													//  2015/05/23. 在doCmd_startAvCall的sharedObjUsr(非mosaic)里设置。在检测到这个标志位后，doEncode要忽略，因为不需要。压缩工作都转移到了mosaic里去了 

				 //
				 unsigned  char									ucbInConfMosaic;											//  2014/11/16

				 //  
				 DWORD											dwLastTickCnt_applyForPlayer;								//  2014/12/10
				 
				 //  2017/09/06
				 //TASK_respInfo									taskRespInfo;

				 //
				 TCHAR											tDbgHint[64];												//  2016/03/28

}		 SHARED_OBJ_USR;







//  2013/03/19
#define		CONST_sharedObjType_null							0
#define		CONST_sharedObjType_av								101
#define		CONST_sharedObjType_mediaFile						102
#define		CONST_sharedObjType_mediaDevice						103
#define		CONST_sharedObjType_webcam_vOnly					104
#define		CONST_sharedObjType_mosaic							105					//  2014/12/01	
#define		CONST_sharedObjType_qvcf							106					//  2015/05/11
#define		CONST_sharedObjType_webcam_av						107					//  2015/05/18
#define		CONST_sharedObjType_rtsp							108					//  2015/10/11
#define		CONST_sharedObjType_screen							109
#define		CONST_sharedObjType_ic								110

//
#define		CONST_sharedObjSubtype_null							0
#define		CONST_sharedObjSubtype_slave						10
#define		CONST_sharedObjSubtype_mosaic						11


//
typedef  struct  __sharedObjKey_t								{
				 int											iIndex_sharedObj;
				 unsigned  int									uiTranNo;
}		 SHARED_obj_key;


//  2017/09/06
//#define		MAX_sharedObjUsrs								MAX_activeTalkers		//  16															//  2011/03/16
//#define		MAX_sharedObjUsrs								8
#define			MAX_sharedObjUsrs								1


//
#define		isSharedObjUsrIndexValid(  index  )					(  (  index  )  >=  0  &&  (  index  )  <  MAX_sharedObjUsrs  )
typedef  struct  __qySharedObj_t								{
				 unsigned  int									uiType1;														//  2013/03/19

				 //
				 BOOL											bUsed;															//  
				 int											index_sharedObj;
				 unsigned  int									uiTranNo;
 				 
				 //
				 void									*		pProcInfo;													//  2015/10/15
				 				 
				 //
				 DWORD											dwTickCnt_start;											//  2011/08/01

				 //
				 unsigned  short								usSubtype;													//  2014/10/30
				 BOOL											bSlave;
				 struct											{
					 //unsigned  int								uiObjType_slave;
					 void								*		pShareDynBmp_slave;
					 //
					 SHARED_obj_key								slaveKey;
				 }												master;
				 struct											{
					 SHARED_obj_key								masterKey;
				 }												slave;

				 //  2010/09/01
				 SHARED_OBJ_USR									usrs[MAX_sharedObjUsrs];
				 int											iIndex_curUsr;

				 //
				 BOOL											bCapDev;													//  
				 BOOL											bDirectX;
				 BOOL											bRemoteAssist;												//  2008/11/10, 
				 BOOL											bSoundRecorder;

				 //
				 void									*		pShareMediaObj;												//  2009/05/07

				 //
				 void									*		pTransInfo_stream;											//  2014/03/15. 对rtsp这样的流，需要转换成无压缩视频。pTransInfo_stream是用来解码的结构

				 //
				 void									*		pIcObj;														//  industrial camera


				 //
				 void									*		pEvt;														//  2015/10/15. evt有shm等提供数据源

				 //
				 int											iIndex_capBmp;
				 int											iIndex_capAudio;											//  2009/04/23
				 
				 //
				 int											iDiffInMs_tStartAudio;										//  2009/05/26. used to sync video and audio

				 //
				 int											iIndex_localPlayer;											//  2009/05/02

				 HANDLE											hThread;													//  
				 BOOL											bThreadEnd;

				 //
#if  0
				 //		
				 int											iIndex_shmCmd;												//  2009/12/22

				 //
				 HANDLE											hProcess;													//  2009/12/22
				 struct											{
					 unsigned  int								uiBufSize_qmShm;

					 HANDLE										hMap;
					 char	*									pBuf;
				 }												dataShm;
#endif

				 //
				 BOOL											bQuit;

				 //  2008/10/16
				 //ROUTE_sendLocalAv								curRoute_sendLocalAv;										//  2014/10/29

				 //
#if  0
				 struct											{															//  2009/09/11
					 time_t										tModifiedTime;
					 time_t										tRecvTime_lastResp;
					 struct										{
						 time_t									tModifiedTime;
						 time_t									tRecvTime_lastResp;
					 }											mems[CONST_maxMsgrs_sendTo];
				 }												routeInfo;
#endif

				 //  2012/11/11
				 struct											{
					 int										iSampleTimeInMs_org_start;
					 int										iSampleTimeInMs_start;
				 }												syncAv;
				 
				 //  2012/01/06
				 struct											{
					 unsigned  char								ucbFpsUnmatched;											//  2012/01/06,fps unmatched
				 }												status;

				 //
				 TASK_av_props									taskAvProps;

				 //
				 long											last_lPktId_alloc;
				 
}		 QY_SHARED_OBJ;


//  2014/09/30
typedef  struct  __qySharedObjInfo_t							{
				 QY_SHARED_OBJ									sharedObj;
				 //
				 SYNC_mt_cnt									syncMtCnt;
}		 QY_sharedObj_sync;

//




#endif  //  }


