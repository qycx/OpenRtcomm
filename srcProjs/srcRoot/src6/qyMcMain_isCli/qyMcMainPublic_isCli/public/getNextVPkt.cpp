
#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
//#include	"qmcVideoCapture_isCli.h"
//#include	"qyAvRecordPublic.h"
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

//#include	"isCliHelpPublic.h"
#include	"testOnly.h"
#include	"qmcCfg.h"


//
//
  //  2015/02/13
 int  getNextAPkt(  myPLAY_AUDIO_DATA  *  pCurPkt,  GENERIC_Q  *	pInDataCacheQ,  QY_Q2  *	pAudioQ2  )
{
	int								iErr				=	-1;

	//
	//  if  (  pTransformVideo->bQuit  )  return  -1;
	if  (  !pCurPkt  ||  !pInDataCacheQ  )  {  //  2015/10/11
		return  -1;
	}

	//
	if  (  !pCurPkt->memory.m_pBuf  )  {
		if  (  isQEmpty(  pInDataCacheQ  )  )  {
			myPLAY_AUDIO_DATA					pkts[CONST_pkts_decAudio];
			unsigned  int						uiLens[CONST_pkts_decAudio];		//  
			int								nLens							=	mycountof(  uiLens  );		//  一次最多处理的包数。
			
			int								nPkts;
			int								i;

			for  (  ;  ;  )  {
				 //  if  (  pTransformVideo->bQuit  )  goto  errLabel;

				 if  (  isQ2Empty(  pAudioQ2  )  )  {
					 goto  errLabel;
				 }
				 
				 nLens  =  mycountof(  uiLens  );
				 if  (  q2GetMsgPkg(  pAudioQ2,  (  void  *  )pkts,  sizeof(  pkts  ),  (  unsigned  int  *  )uiLens,  (  unsigned  int  *  )&nLens,  _T(  "getNextAPkt"  ))) {
					 showInfo_open0(  0,  0,  _T(  "getValidPkt failed: q2GetMsgPkg failed"  )  );
					 goto  errLabel;
				 }

				 //
				 //
				  nPkts  =  0;
				  for  (  i  =  0;  i  <  nLens;  i  ++  )  {
					   nPkts  +=  uiLens[i]  /  sizeof(  pkts[0]  );
					   if  (  uiLens[i]  %  sizeof(  pkts[0]  )  )  {
						   #ifdef  __DEBUG__
								   traceLog((TCHAR*)  _T(  "vpp: uiLen err"  )  );
								   assert(  0  );
						   #endif						   
					   }					  
				  }
				
				  //
				  for  (  i  =  0;  i  <  nPkts;  i  ++  )  {
					   if  (  qPostMsg(  &pkts[i],  sizeof(  pkts[i]  ),  pInDataCacheQ,  _T(  "getNextApkt"  ))) {
						   clean_myPLAY_AUDIO_DATA(  &pkts[i],  _T(  "decVideo_rtsp, qPostMsg failed"  )  );
					   }
				  }

				 //
				 break;
			}
		}
		//
		unsigned  int  size  =  sizeof(  pCurPkt[0]  );
		if  (  qGetMsg(  pInDataCacheQ,  pCurPkt,  &size  )  )  goto  errLabel;
		//  2015/02/13
		M_set_pktId_getNewPkt(  pCurPkt  );
	}
	//
	if  (  !pCurPkt->memory.m_pBuf  )  goto  errLabel;

	//
	myPLAY_AUDIO_DATA* pPkt; pPkt = pCurPkt;


	//  if  (  pQdcObjInfo->cfg.pCurPkt
	iErr  =  0;
errLabel:

	return  iErr;
}



//
 int  getNextVPkt(  myDRAW_VIDEO_DATA  *  pCurPkt,  GENERIC_Q  *	pInDataCacheQ,  QY_Q2  *	pVideoQ2  )
{
	int								iErr				=	-1;

	//
	//  if  (  pTransformVideo->bQuit  )  return  -1;
	if  (  !pCurPkt  ||  !pInDataCacheQ  )  {	//  2015/10/11
		return  -1;
	}

	//
	if  (  !pCurPkt->memory.m_pBuf  )  {
		if  (  isQEmpty(  pInDataCacheQ  )  )  {
			myDRAW_VIDEO_DATA					pkts[CONST_pkts_decVideo];
			unsigned  int						uiLens[CONST_pkts_encVideo];		//  
			int								nLens							=	mycountof(  uiLens  );		//  一次最多处理的包数。
			
			int								nPkts;
			int								i;

			for  (  ;  ;  )  {
				 //  if  (  pTransformVideo->bQuit  )  goto  errLabel;

				 if  (  isQ2Empty(  pVideoQ2  )  )  {
					 goto  errLabel;
				 }
				 
				 nLens  =  mycountof(  uiLens  );
				 if  (  q2GetMsgPkg(  pVideoQ2,  (  void  *  )pkts,  sizeof(  pkts  ),  (  unsigned  int  *  )uiLens,  (  unsigned  int  *  )&nLens,  _T(  "getNextVPkt"  ))) {
					 showInfo_open0(  0,  0,  _T(  "getNextVPkt failed: q2GetMsgPkg failed"  )  );
					 goto  errLabel;
				 }

				 //
				 //
				  nPkts  =  0;
				  for  (  i  =  0;  i  <  nLens;  i  ++  )  {
					   nPkts  +=  uiLens[i]  /  sizeof(  pkts[0]  );
					   if  (  uiLens[i]  %  sizeof(  pkts[0]  )  )  {
						   #ifdef  __DEBUG__
								   traceLog((TCHAR*)  _T(  "vpp: uiLen err"  )  );
								   assert(  0  );
						   #endif						   
					   }					  
				  }

				  //  2015/10/16
				  #ifdef  __DEBUG__
						  #if  10
								TCHAR  tBuf[128];
								for  (  i  =  0;  i  <  nPkts;  i  ++  )  {
									 char  buf[128];
									 iFourcc2Str(  pkts[i].bih.biCompression,  buf,  mycountof(  buf  )  );
									 int  ii  =  0;
									 #if  0
										_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "getNextVPkt: pkt %d. nPkts %d"  ),  pkts[i].head.uiSampleTimeInMs,  nPkts  );
										showInfo_open0(  0,  0,  tBuf  );
									#endif
								}
						  #endif
				  #endif
												
				  //
				  for  (  i  =  0;  i  <  nPkts;  i  ++  )  {
					   if  (  qPostMsg(  &pkts[i],  sizeof(  pkts[i]  ),  pInDataCacheQ,  _T(  "getNextVPkt"  ))) {
						   clean_myDRAW_VIDEO_DATA(  &pkts[i],  _T(  "decVideo_rtsp, qPostMsg failed"  )  );
					   }
				  }

				 //
				 break;
			}
		}
		//
		unsigned  int  size  =  sizeof(  pCurPkt[0]  );
		if  (  qGetMsg(  pInDataCacheQ,  pCurPkt,  &size  )  )  goto  errLabel;
		//  
	}
	//
	if  (  !pCurPkt->memory.m_pBuf  )  goto  errLabel;

	//
	myDRAW_VIDEO_DATA* pPkt; pPkt = pCurPkt;


	//  if  (  pQdcObjInfo->cfg.pCurPkt
	iErr  =  0;
errLabel:

	return  iErr;
}


 //
  //  2015/02/13
 int  detachAPkt(  void  *  pPkt_myPLAY_AUDIO_DATA,  void  *  p1  )
{
	myPLAY_AUDIO_DATA  *  pPkt  =  (  myPLAY_AUDIO_DATA  *  )pPkt_myPLAY_AUDIO_DATA;

	memset(  &pPkt->memory,  0,  sizeof(  pPkt->memory  )  );

	return  0;
}


 //
 
int  detachVPkt(  void  *  pPkt_myDRAW_VIDEO_DATA,  void  *  p1  )
{
	myDRAW_VIDEO_DATA  *  pPkt  =  (  myDRAW_VIDEO_DATA  *  )pPkt_myDRAW_VIDEO_DATA;

	memset(  &pPkt->memory,  0,  sizeof(  pPkt->memory  )  );

	return  0;
}


//  2016/12/09
 int  parseDecAPkt_o(  void  *  pPktParam,  void  **ppWfx,  unsigned  char  **  ppOutput,  unsigned  int  *puiSize  )
 {
	 int		iErr	=	-1;
	 myPLAY_AUDIO_DATA  *  pPkt  =  (  myPLAY_AUDIO_DATA  *  )pPktParam;

	 *ppWfx  =  &pPkt->wfx;
	 *ppOutput  =  (  unsigned  char  *  )pPkt->memory.m_pBuf;
	 *puiSize  =  pPkt->uiSize_dec;

	 //
	 iErr  =  0;	 
errLabel:
	 return  iErr;
 }





//
 int  parseDecVPkt_o(  void  *  pPktParam,  void  **ppBih,  unsigned  char  **  ppOutput,  unsigned  int  *puiSize  )
 {
	 int		iErr	=	-1;
	 myDRAW_VIDEO_DATA  *  pPkt  =  (  myDRAW_VIDEO_DATA  *  )pPktParam;

	 *ppBih  =  &pPkt->bih;
	 *ppOutput  =  (  unsigned  char  *  )pPkt->memory.m_pBuf;
	 *puiSize  =  pPkt->uiSize_dec;

	 //
	 iErr  =  0;	 
errLabel:
	 return  iErr;
 }



