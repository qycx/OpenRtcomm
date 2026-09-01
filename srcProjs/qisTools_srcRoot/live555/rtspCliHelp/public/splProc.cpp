
#include	"stdafx.h"
#include	<stdlib.h>
#include	<tchar.h>
#include	<stddef.h>
#include	<mmsystem.h>

#include	"rtspCliHelpCommon.h"

#include	"OutputFile.hh"




extern "C" DWORD WINAPI mcThreadProc_spl( LPVOID lpParameter )
{


	 #define		DEFAULT_dwToInMs		5000
	 DWORD								dwToInMs					=	DEFAULT_dwToInMs;

	 DWORD								dwTickCnt_lastAudioData		=	GetTickCount(  );;						// 

	 GBUF_rtspCliHelp			*		pGBuf						=	&gBuf_rtspCliHelp;
	 CTX_spl							ctx;
	 memset(  &ctx,  0,  sizeof(  ctx  )  );

	 OutputDebugString(  _T(  "thread_spl enters\n"  )  );
	 dyn_isCliHelp_showInfo(  gBuf_rtspCliHelp.pCtx_showInfo,  _T(  "rtspCli::spl starts"  )  );


	 //
	 if  (  !ctx.streamBuf.pBuf  )  {
		 ctx.streamBuf.uiBufSize  =  MAX_uiBufSize_streamBuf;	
		 ctx.streamBuf.uiLen  =  0;
		 ctx.streamBuf.pBuf  =  (  char  *  )malloc(  ctx.streamBuf.uiBufSize  );
		 if  (  !ctx.streamBuf.pBuf  )  goto  errLabel;
	}

	 //
	 gBuf_rtspCliHelp.spl.bRunning  =  TRUE;
	 //  memset(  &pDispatchAudio->m_var,  0,  sizeof(  pDispatchAudio->m_var  )  );



	 //

	int  dwToInMs_rtsp  =  3000;

	 //
	 for  (  ;  !gBuf_rtspCliHelp.bQuit;  )  {
		 
		  if  (  !gBuf_rtspCliHelp.spl.bInited_splInfo  )  {
			  //  放慢一点点	
			  Sleep(  200  );
		  }

#ifdef  __DEBUG__
		  traceLog(  _T(  "start rtsp session"  )  );
#endif

		  //
		  int  iBUFSIZE  =  CONST_bufSize_rtspCliPipe;


		  #if  10
			 //			 			
		  if  (  !pGBuf->spl.bInited_splInfo  )  {							
			  qdcExitSplInfo(  &pGBuf->spl.g_splInfo  );											 			
		  }
		  if  (  !pGBuf->spl.bInited_splInfo
				&&  isCliHelp_streamDataQ_qNodes(  gBuf_rtspCliHelp.pStreamDataQ,  0,  0  )  >  CONST_qNodes_toInitSpl  )  			
		  {	
				//

				//
				QDC_spl_cfg	cfg;
				memset(  &cfg,  0,  sizeof(  cfg  )  );		
				//
				cfg.pf_streamDataQ_qNodes  =  isCliHelp_streamDataQ_qNodes;
				cfg.pf_readData  =  isCliHelp_tmpHandler_readData_forSpl;
				//  cfg.pf_writeData
				//
				cfg.pStreamBuf  =  &ctx.streamBuf;
				cfg.pStreamDataQ  =  gBuf_rtspCliHelp.pStreamDataQ;
				//
#ifdef  _DEBUG
				isCliHelp_streamDataQ_debug(  gBuf_rtspCliHelp.pStreamDataQ  );
#endif
				//
				void  *  p0  =  0;
				void  *  p1  =  0;									
				if  (  qdcInitSplInfo(  &cfg,  p0,  p1,  &pGBuf->spl.g_splInfo  )  )  continue;
				pGBuf->spl.bInited_splInfo  =  TRUE;													 
			
		  }
#endif

		  if  (  pGBuf->spl.bInited_splInfo  )  {
			  if  (  doSpl(  &ctx  )  )  {
				  //
				  dyn_isCliHelp_showInfo(  gBuf_rtspCliHelp.pCtx_showInfo,  _T(  "rtspCli::doSpl failed"  )  );
				  //
				  goto  errLabel;
			  }
		  }

		  continue;
	 }

errLabel:
	 
	 //
	 dyn_isCliHelp_showInfo(  gBuf_rtspCliHelp.pCtx_showInfo,  _T(  "rtspCli::thread_spl will stop"  )  );


	 //
	 qdcExitSplInfo(  &pGBuf->spl.g_splInfo  );											 
			

	 //
	 gBuf_rtspCliHelp.spl.bRunning  =  FALSE;

	 //
	 if  (  ctx.streamBuf.pBuf  )  {
		 free(  ctx.streamBuf.pBuf  );  ctx.streamBuf.pBuf  =  NULL;
	 }

	 //
	 gBuf_rtspCliHelp.spl.bStopped  =  TRUE;


	 dyn_isCliHelp_showInfo(  gBuf_rtspCliHelp.pCtx_showInfo,  _T(  "rtspCli::spl quit"  )  );
	 OutputDebugString(  _T(  "mcThreadProc_spl quit\n"  )  );

	return  0;
}



int  doSpl(  CTX_spl  *  pCtx  )
{
	int  iErr  =  -1;
	GBUF_rtspCliHelp  *  pGBuf  =  &gBuf_rtspCliHelp;

	if  (  pGBuf->spl.bInited_splInfo  )
	{
		if  (  !qdcSplGetNextData(  &pGBuf->spl.g_splInfo,  pGBuf->spl.g_splInfo.pMediaDataForSpl_pkt  )  )  {
					
			int  i;			
			i  =  0;					
			TCHAR	tBuf[128];					
			QDC_MEDIA_data  *  pMediaData  =  pGBuf->spl.g_splInfo.pMediaDataForSpl_pkt;
			#ifdef  _DEBUG
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "qdcSplGetNextData: get pkt %d bytes\n"  ),  pMediaData->head.uiLen  );
					OutputDebugString(  tBuf  );
			#endif

					
				
			//			
			
			//  
			if  (  pGBuf->spl.bInited_splInfo  
				&&  gBuf_rtspCliHelp.common.pf_BufferCB_rtsp  
				&&  pMediaData->head.iMediumType
				&&  pMediaData->head.iCodecType	  
				)    
			{
				//
				int		iMediumType  =  pMediaData->head.iMediumType;	//  CONST_mediumType_video;
				int		iCodecType  =  pMediaData->head.iCodecType;		//  CONST_codecType_MP2T;
				unsigned  __int64  ui64ValInMs  =  pMediaData->head.iSampleTimeInMs;	//  presentationTime.tv_sec  *  1000  +  presentationTime.tv_usec  /  1000;
				unsigned  int  uiPts  =  0;	//  2015/02/09
				int  iSize_startCode  =  0;
				bool  bNeedResp  = false;	//  2015/01/30
	  	  
				//	  
				if (!pCtx->fHaveWrittenFirstFrame) {
					char  buf[2048]  =  "";
					int	index		=	0;
					CB_rtsp_res  res;
							
					#if  0
					// If we have NAL units encoded in "sprop parameter strings", prepend these to the file:
					for (unsigned j = 0; j < 3; ++j) {			  
						unsigned numSPropRecords;
						SPropRecord* sPropRecords = parseSPropParameterSets(fSPropParameterSetsStr[j], numSPropRecords);
		
						for (unsigned i = 0; i < numSPropRecords; ++i) {
							//addData(start_code, 4, presentationTime);
							// addData(sPropRecords[i].sPropBytes, sPropRecords[i].sPropLength, presentationTime);				  
							memcpy(  buf,  start_code,  4  );		
							memcpy(  buf  +  4,  sPropRecords[i].sPropBytes, sPropRecords[i].sPropLength  );				  
							//
							memset(  &res,  0,  sizeof(  res  )  );
							if  (  gBuf_rtspCliHelp.pf_BufferCB_rtsp(  &gBuf_rtspCliHelp,  gBuf_rtspCliHelp.iIndex_capProcInfo,  iMediumType,  iCodecType,  ui64ValInMs,  (  unsigned  char  *  )buf,  4  +  sPropRecords[i].sPropLength,  TRUE,  index,  FALSE,  &res  )  )  {
								goto  errLabel;
							}
							index  ++  ;      			  
						}
						delete[] sPropRecords;    		  
					}
					#endif

					//
					unsigned  char  sps[512];
					unsigned  char  pps[512];
					unsigned  char  kk[512];
					unsigned  int  spsLen  =  sizeof(  sps  );
					unsigned  int  ppsLen  =  sizeof(  pps  );
					unsigned  int  kkLen  =  sizeof(  kk  );
					if  (  qdcSplGetSpsPps(  &pGBuf->spl.g_splInfo,  (  char  *  )sps,  &spsLen,  (  char  *  )pps,  &ppsLen,  (  char  *  )kk,  &kkLen  )  )  {
						dyn_isCliHelp_showInfo(  pGBuf->pCtx_showInfo,  _T(  "doSpl failed: getSpsPps failed"  )  );
						goto  errLabel;
					}
					if  (  spsLen  )  {
						memset(  &res,  0,  sizeof(  res  )  );
						if  (  gBuf_rtspCliHelp.common.pf_BufferCB_rtsp(  &gBuf_rtspCliHelp,  gBuf_rtspCliHelp.common.iIndex_capProcInfo,  iMediumType,  iCodecType,  (  int  )ui64ValInMs,  uiPts,  0,  sps,  spsLen,  TRUE,  index,  FALSE,  bNeedResp,  &res  )  <  0  )  {
							goto  errLabel;
						}
						index  ++  ;		  
					}
					if  (  ppsLen  )  {
						memset(  &res,  0,  sizeof(  res  )  );
						if  (  gBuf_rtspCliHelp.common.pf_BufferCB_rtsp(  &gBuf_rtspCliHelp,  gBuf_rtspCliHelp.common.iIndex_capProcInfo,  iMediumType,  iCodecType,  (  int  )ui64ValInMs,  uiPts,  0,  pps,  ppsLen,  TRUE,  index,  FALSE,  bNeedResp,  &res  )  <  0  )  {
							goto  errLabel;			  
						}
						index  ++  ;		  
					}
					
					//		  
					memset(  &res,  0,  sizeof(  res  )  );
					if  (  gBuf_rtspCliHelp.common.pf_BufferCB_rtsp(  &gBuf_rtspCliHelp,  gBuf_rtspCliHelp.common.iIndex_capProcInfo,  iMediumType,  iCodecType,  (  int  )ui64ValInMs,  uiPts,  0,  NULL,  0,  TRUE,  index,  TRUE,  bNeedResp,  &res  )  <  0  )  {
						goto  errLabel;		  
					}
					//  这里，不应该每次都加sps,应该第一次发送的时候就发过去。就不用经常在包里加了。   
					pCtx->fHaveWrittenFirstFrame = True; // for next time  	  
				}
				
				//
				CB_rtsp_res  res;		
				memset(  &res,  0,  sizeof(  res  )  );
				if  (  gBuf_rtspCliHelp.common.pf_BufferCB_rtsp(  &gBuf_rtspCliHelp,  gBuf_rtspCliHelp.common.iIndex_capProcInfo,  iMediumType,  iCodecType,  ui64ValInMs,  uiPts,  0,  (  unsigned  char  *  )pMediaData->buf,  pMediaData->head.uiLen,  FALSE,  0,  FALSE,  bNeedResp,  &res  )  )  {
					goto  errLabel;
				}    
			}
			
		}			
	}

	//
	iErr  =  0;
errLabel:
	return  iErr;
}
