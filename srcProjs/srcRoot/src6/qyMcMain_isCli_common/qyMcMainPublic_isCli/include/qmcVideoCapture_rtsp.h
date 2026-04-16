

#ifndef  __qmcVideoCapture_rtsp_h__
#define  __qmcVideoCapture_rtsp_h__		//  {

//
//#include	"rtspCliHelpPublic.h"


//  2015/01/29
#define		CONST_rtspType_null									0
#define		CONST_rtspType_decV									1
//  
#define		CONST_rtspType_qvcf									2		//  2015/05/09
//
#define		CONST_rtspType_encV									3		//  2015/10/13




//  2015/01/31
typedef  struct  __dvt_decV_t									{
				 //
				 QY_shm											dataShm;

				 //
				 struct											{
					 	 TCHAR									evtName_syncR[32];				
						 HANDLE									hEvent_syncR;

						 //
					 	 TCHAR									evtName_syncW[32];				
						 HANDLE									hEvent_syncW;


						 //
						 HANDLE									hThread;
						 DWORD									dwThreadId;

				 }												writeShm;
				 
				 //
				 BOOL											bQuit;

}		 DVT_decV;


//  2015/05/11
#define		M_capDev_rtsp_commonMems															\
				 unsigned  int									uiType;							\
																								\
				 DWORD											dwThreadId;						\
				 HANDLE											hThread_recvRtsp;				\
				 BOOL											bQuit;							\
				 DWORD											dwTickCnt_start;				\
				 BOOL											bRunning;						\
				 MY_DEBUG_STEP									debugStep;						\
																								\
				 MC_VAR_common							*		pProcInfoCommon;				\
				 TCHAR											url[256];						\
				 int											iIndex_sharedObj;				\
				 ;


typedef  struct  __capDev_rtsp_common_t								{
				 M_capDev_rtsp_commonMems
}		 CAP_dev_rtspCommon;

//
typedef  struct  __VIDEO_capDev_rtsp_t							{
				 M_capDev_rtsp_commonMems

				 //  2015/06/22
				 HANDLE											hEvent_syncThreadQuit_recvRtsp;

				 //
				 int											tn_rtspCliPipe;

				 //
				 QY_pipe										pipe;

				 //  
				 HANDLE											hProcess_rtspCliHelp;

				 //
				 QY_Q2											cacheQ2_dvt_decV;
				 BOOL											bQInited_dvt_decV;
				 //
				 DVT_decV								*		pDvt_decV;
				 
				 //  2015/10/16
				 void									*		pQdcObjInfo;		//  for encV
				 
}		 VIDEO_capDev_rtsp;


 //  2013/03/19
 typedef  struct  __audioCapDevRtsp_t							{
				  M_capDev_rtsp_commonMems

				  BOOL											bInited;


 }		  AUDIO_capDev_rtsp;



 //  2015/05/11
typedef  struct  __QVCF_rtsp_t									{
				 M_capDev_rtsp_commonMems
					 
				 //
				 //TCHAR											fileName[MAX_PATH];

				 //
				 int											tn_rtspCliPipe;

				 //
				 QY_pipe										pipe;

				 //  
				 HANDLE											hProcess_rtspCliHelp;

				 //
				 QY_Q2											cacheQ2_dvt_decV;
				 BOOL											bQInited_dvt_decV;
				 //
				 DVT_decV								*		pDvt_decV;

				 //  2015/05/20
				 int											nTimes_played;

}		 QVCF_rtsp;

//
extern "C" DWORD WINAPI mcThreadProc_recvRtsp( LPVOID lpParameter );


//  2015/05/20
int  BufferCB_a_rtsp(  MC_VAR_common  *  pProcInfo,  void  *  pGBUF_rtspCliHelp,  int  iIndex_capProcInfo,  int  iMediumType,  int  iDataType,  int  iCodecType,  int  iSampleTimeInMs,  unsigned  int  uiPts,  unsigned  char  *  pBuffer,  long  BufferLen,  void  *  pMsgTaskBufParam,  CB_rtsp_res  *  pRes  );
//
//int  BufferCB_v_rtsp(  MC_VAR_common  *  pProcInfo,  void  *  pGBUF_rtspCliHelp,  int  iIndex_capProcInfo,  int  iMediumType,  int  iCodecType,  int  iSampleTimeInMs,  unsigned  int  uiPts,  unsigned  char  *  pBuffer,  long  BufferLen,  bool  bSpsPps,  int  index_spsPps,  bool  bFinished_spsPps,  CB_rtsp_res  *  pRes  );
int  BufferCB_v_rtsp(  MC_VAR_common  *  pProcInfo,  void  *  pGBUF_rtspCliHelp,  int  iIndex_capProcInfo,  int  iMediumType,  int  iDataType,  int  iCodecType,  int  iSampleTimeInMs,  unsigned  int  uiPts,  unsigned  char  *  pBuffer,  long  BufferLen,  bool  bSpsPps,  int  index_spsPps,  bool  bFinished_spsPps,  CB_rtsp_res  *  pRes  );



#endif


