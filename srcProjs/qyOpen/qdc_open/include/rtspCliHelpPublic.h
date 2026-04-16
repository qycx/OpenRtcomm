

#ifndef  __RTSPCLIHELPPUBLIC_H__
#define  __RTSPCLIHELPPUBLIC_H__	//  {


#define		CONST_bufSize_rtspCliPipe					3  *  1024  *  1024
#define		CONST_rtspCliPipePrefix						_T(  "\\\\.\\pipe\\rtspCliPipe"  )

//
#define		CONST_ipcProcPipePrefix						_T(  "\\\\.\\pipe\\ipcProcPipe"  )
#define		CONST_ipcProcPipe_tn						0
#define		CONST_ipcProcPipe_tn_dhListIp				10
#define		CONST_ipcProcPipe_tn_dhPtz					11
#define		CONST_ipcProcPipe_tn_dhDeviceControl		12

#define		CONST_ipcProcPipe_tn_hikListIp				20
#define		CONST_ipcProcPipe_tn_hikPtz					21
#define		CONST_ipcProcPipe_tn_hikDeviceControl		22
//
#define		CONST_ipcProcPipe_tn_hk3ddw					23

//
#define		CONST_ipcProcPipe_tn_d4kListIp				30
#define		CONST_ipcProcPipe_tn_d4kPtz					31
#define		CONST_ipcProcPipe_tn_d4kDeviceControl		32





//
#define		M_get_pipeName(  sym,  appObjPrefix,  tn,  pipeName  )	_sntprintf(  pipeName,  mycountof(  pipeName  ),  _T(  "%s%s-%d"  ),  CONST_rtspCliPipePrefix,  appObjPrefix,  tn  );
//  2015/02/02
#define		M_get_evtName_syncQuit(  sym,  appObjPrefix,  tn,  evtName  )		_sntprintf(  evtName,  mycountof(  evtName  ),  _T(  "%s%s-%d"  ),  sym,  appObjPrefix,  tn  );


//
typedef  struct  __qyPipe_t				{	
				 HANDLE					hPipe;
				 HANDLE					hEvent;
				 HANDLE					hThread;
				 DWORD					dwThreadId;
				 //  201406/06
				 BOOL					bThreadQuit;
}		 QY_pipe;

//
typedef  struct  __CbRtspRes_t			{
				 bool					bQuit;
				 //
				 unsigned  int			dwTickCnt_doPretrans;				//  2015/02/24
}		 CB_rtsp_res;

//
#define		CONST_bufSize_rtspMsg		CONST_bufSize_rtspCliPipe  -  100	//  100是为了给iType等包头留位置
//
#if  0  //  2015/10/15
typedef  struct  __rtspMsg_t			{
				 int					iType;
				 //
				 int					iMediumType;
				 int					iCodecType;
				 int					iSampleTimeInMs;
				 unsigned  int			uiPts;								//  2015/02/09
				 bool					bSpsPps;
				 int					index_spsPps;
				 bool					bFinished_spsPps;
				 //
				 bool					bNeedResp;							//  2015/01/30. 设置此标志位时，需要返回一个响应
				 //
				 unsigned  int			dwTickCnt_doPretrans;				//  2014/02/24
				 //
				 unsigned  int			uiLen;
				 char					buf[CONST_bufSize_rtspMsg];
}		 RTSP_msg;
#endif

//
typedef  struct  __rtspMsg_t			{
				 int					iType;
				 //
				 int					iMediumType;
				 int					iCodecType;
				 int					iSampleTimeInMs;
				 unsigned  int			uiPts;								//  2015/02/09
				 //
				 int					iDataType;							//  2015/10/15
				 //
				 bool					bSpsPps;
				 int					index_spsPps;
				 bool					bFinished_spsPps;
				 //
				 bool					bNeedResp;							//  2015/01/30. 设置此标志位时，需要返回一个响应
				 //
				 unsigned  int			dwTickCnt_doPretrans;				//  2014/02/24
				 //
				 unsigned  int			uiLen;
				 char					buf[CONST_bufSize_rtspMsg];
}		 RTSP_msg;



//
typedef int  (  *PF_BufferCB_rtsp  )(  void  *  pGBUF_rtspCliHelp,  int  iIndex_capProcInfo,  int  iMediumType,  int  iCodecType,  int  iSampleTimeInMs,  unsigned  int  uiPts,  int  iDataType,  unsigned  char  *  pBuffer,  long  BufferLen,  bool  bSpsPps,  int  index_spsPps,  bool  bFinished_spsPps,  bool  bNeedResp,  CB_rtsp_res  *  pRes  );
typedef int  (  *PF_rtspCliHelp_exit  )(  void  *  pGBUF_rtspCliHelp  );

__declspec(  dllexport  )  int  set_PF_BufferCB_rtsp(  PF_BufferCB_rtsp  pf_BufferCB_rtsp,  PF_rtspCliHelp_exit  pf_exit,  int  iIndex_capProcInfo,  LPCTSTR  appObjPrefix,  int  tn  );
__declspec(  dllexport  )  int rtspCliHelp_main(int argc, char** argv);



//  2015/01/27
typedef  struct  __rtspCli_common_t					{
				 PF_BufferCB_rtsp					pf_BufferCB_rtsp;			
				 PF_rtspCliHelp_exit				pf_rtspCliHelp_exit;
				 int								iIndex_capProcInfo;			
				 //
				 TCHAR								appObjPrefix[32];		//  2015/02/02
				 int								tn_rtspCliPipe;			
				 				 
				 //
				 QY_pipe							pipe;
				 //
				 void							*	pRTSP_msg;
			
				 //
#define		CONST_evtNamePrefix_rtspCliSyncQuit		_T(  "rtspCliSQ"  )				
				 //
				 TCHAR								evtName_syncQuit[32];				
				 HANDLE								hEvent_syncQuit;

				 //
				 struct								{				 	
					 DWORD							dwLastTickCnt_BufferCB_rtspCli;	
					 //
					 BOOL							bException_pRTSP_msg;		//  2015/02/08
					 BOOL							bRet_CancelIo;
				 }									status;
				 
}		 RTSP_cli_common;

#if  10	//  2015/01/27
//
typedef  struct								{
			RTSP_cli_common					common;

			//
			void						*	pCtx_showInfo;

			
			//
			void						*	pMediaDataForSpl_toPost;

			//
			unsigned  int					uiMaxQNodes_streamDataQ;
			void						*	pStreamDataQ;			//  2014/03/10
			BOOL							bInited_streamDataQ;
			

			//
			BOOL							bQuit;
			
			
			//  2014/06/06
			struct							{
				struct						{
		
				}							status;
			}								dataCap;
			
			//
			HANDLE							hThread_spl;
			DWORD							dwThreadId_spl;

			//
			struct							{
				BOOL						bRunning;
				//
				BOOL						bStopped;
				
				//
				QDC_spl_info				g_splInfo;				 
				BOOL						bInited_splInfo;

			}								spl;

			
			//  2014/06/06
			HANDLE							hThread_cmdProc;
			DWORD							dwThreadId_cmdProc;

			//  2014/06/06
			struct							{
				BOOL						bRunning;
				//
				BOOL						bStopped;
				//
				BOOL						bSeriousErr;


				//
				struct						{
					int						nCnt_noDataArrive;
				}							status;

			}								cmdProc;


			//
}		GBUF_rtspCliHelp;
#endif


//
typedef  struct  __ctxSpl_t					{
	

				 //				
				 QDC_stream_buf				streamBuf;

				//
				BOOL						fHaveWrittenFirstFrame;
				 
}		 CTX_spl;

//  2014/06/06
typedef  struct  __ctxRtspCliHelpCmdProc_t	{
				 //
				 char						reserved;
}		 CTX_rtspCliHelp_cmdProc;


//
#define			CONST_mediumType_null			0
#define			CONST_mediumType_audio			1
#define			CONST_mediumType_video			2
#define			CONST_mediumType_usrData		3		//  2015/01/30


//
#define			CONST_codecType_null			0
#define			CONST_codecType_h264			1
//  #define		CONST_codecType_MP2T			2
#define			CONST_codecType_HEVC			3		//  2017/10/08


//
//
#define		bUseSplitter(  ucCompressors,  dwFourcc  )		(  (  ucCompressors  )  ==  CONST_videoCompressors_stream  &&  (  dwFourcc  )  !=  CONST_fourcc_h264  )  

//  2015/01/27
int  rtspCliCommon_init(  PF_BufferCB_rtsp  pf_BufferCB_rtsp,  PF_rtspCliHelp_exit  pf_exit,  int  iIndex_capProcInfo,  LPCTSTR  appObjPrefix,  int  tn,  void  *  pRTSP_cli_common  );
int  rtspCliCommon_exit(  void  *  pRTSP_cli_common  );
//
int  rtspCliCommon_chkPipe(  void  *  pRTSP_cli_common  );
// 2015/10/16
int  BufferCB_rtspCliCommon(  void  *  pRTSP_cli_common,  int  iIndex_capProcInfo,  int  iMediumType,  int  iCodecType,  int  iSampleTimeInMs,  unsigned  int  uiPts,  int  iDataType,  unsigned  char  *  pBuffer,  long  BufferLen,  bool  bSpsPps,  int  index_spsPps,  bool  bFinished_spsPps,  bool  bNeedResp,  CB_rtsp_res  *  pRes  );





#endif  //  }


