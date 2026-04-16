
#ifndef  __qmcSharedObj_public_h__
#define  __qmcSharedObj_public_h__	//  {

//
#include	"qisDefs.h"
#include	"qoi_encA.h"
#include	"qmcStruct_defs.h"
#include	"tmpTypes.h"

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
				 //GENERIC_Q									*	pTmpDataQ;


				 //
				 unsigned  char									ucTimeoutInS_showFrameInfoResp;								//  ´Ó·¢³öshowFrameInfoµ½µÃµ½respµÄ³¬Ê±

				 //  unsigned  int									uiBytesRecorded_perBlockAlign_expected;						//  Ã¿¶ÔÆëµ¥Î»µÄ»º³å, Ö±½Ó¾ö¶¨ÁË²ÉÑùËùºÄÊ±¼ä¡£


				 // ÏÂÃæÎªèåËÙ¿ØÖÆ
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
					 //  2016/12/15
					 struct										{
						 unsigned  int							last_iSampleTimeInMs_preEnc;
						 unsigned  int							uiTimeLen_preEnc;
						 //
						 unsigned  int							lastEnd_iSampleTimeInMs_postEnc;
					 }											st;

				 }												encInfo;



}		 COMPRESS_AUDIO;



#define		MACRO_capProcInfo_audioMems							unsigned  int				uiType;						\
																int							iIndex_sharedObj;			\
																unsigned  int				uiTranNo_sharedObj;			\
																WAVEFORMATEX				wf_org;						\
																QY_qThreadProcInfo_common	appThread;					\
																QY_qThreadProcInfo_common	thread;						\
																COMPRESS_AUDIO				compressAudio;		



//
//
struct  __capProcInfoRecordSound_t						{
				 MACRO_capProcInfo_audioMems

				 unsigned  int									uiRecordType;												//  2010/08/03

				 //  2013/03/18
				 union											{
					 struct										{
						 void  *								pAudioCapDev;
					 }											dx;
				 }												u;

				 //  2011/10/24
				 GUID											guid_aDevice;												//  被选中的audio device
				 TCHAR											capDevDesc[64];												//  2013/05/25
				 TCHAR											aec_rendDevDesc[64];

				 //  2013/08/02. 录制的线程是这里, 将audioMems.thread留给压缩
				 QY_qThreadProcInfo_common						recThread;				

				 //  2009/02/13
				 HANDLE											hEvents[CONST_numCaptureEvents  +  1];

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

				 //  2017/02/25
				 void  *										pProcInfo;

};





#endif  //  }

