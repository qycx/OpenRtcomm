

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
#include	"qmcCfg.h"
#include <dynFuncs.h>




//  2016/12/09
 __declspec(  dllexport  )  int  smplPCMReader_LoadNextFrame(  void  *  pQdcObjInfoParam,  long  *  pold_lPktId,  old_PF_myLoadNextFrame  pf_myLoadNextFrame,  void  *  p2_myLoadNextFrame,  BOOL  *  pbNeed_forceKeyFrame  )
{
	int			sts_ret  =  -1;
	int			sts  =  -1;

	BYTE  *  pInput  =  NULL;			///m_var.m_pInput;
	unsigned  int  uiInputSize  =  0;	//  m_var.m_uiInputSize;
	TCHAR  tBuf[256];

	//	
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )pQdcObjInfoParam;
	if  (  !pQdcObjInfo  )  {
		showInfo_open0(  0,  0,  _T(  "CMySmpl::ReadNextFrame failed, pQdcObjInfo is null"  )  );
		goto  errLabel;
	}
	//  QDC_OBJ_hdDec	*	pObj	=	(  QDC_OBJ_hdDec  *  )pQdcObjInfo->pObj;
	//CMyDecPipeline  *  pPipeline  =  (  CMyDecPipeline  *  )pObj->pPipeline;
	//
	if  (  !pQdcObjInfo->var.ucbTransformFuncsOk  )  {
		showInfo_open0(  0,  0,  _T(  "CMySmpl::ReadNextFrame failed, ucbTransformFuncsOk is false"  )  );
		goto  errLabel;
	}
	//
	//
	for  (  ;  ;  )  {
		 if  (  pQdcObjInfo->cfg.a.pf_bTransformAudioQuit(  pQdcObjInfo->cfg.a.pParent_transform,  0,  0  )  )  {
			 showInfo_open0(  0,  0,  _T(  "SmplYUVReader::LoadNextFrame failed, bQuit true"  )  );
			 goto  errLabel;
		 }
		 if  (  !pQdcObjInfo->cfg.a.pf_getNextAPkt(  pQdcObjInfo->cfg.a.pCurPkt,  pQdcObjInfo->cfg.a.pInDataCacheQ,  pQdcObjInfo->cfg.a.pAudioQ2  )  )  {
			 //
			 //  2015/10/31
#if  0
			 myDRAW_VIDEO_DATA  *  pPkt  =  (  myDRAW_VIDEO_DATA  *  )pQdcObjInfo->cfg.pCurPkt;
			 if  (  !pPkt  )  goto  errLabel;
			 if  (  pPkt->usPktResType  ==  CONST_pktResType_sharedTex  )  {
				 if  (  !pPkt->sharedTex.pktSharedTexInfo.bTexShared  )  {		
					 //			
					 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "YUV.loadNextFrame: sharedTex.bTexShared false. skipped"  ),  pPkt->sharedTex.pktSharedTexInfo.uiSeqNo,  pQdcObjInfo->var.sharedTex.uiSeqNo_lastRender  );			
					 showInfo_open0(  0,  0,  tBuf  );
					 //
					 pQdcObjInfo->cfg.pf_clean_myDRAW_VIDEO_DATA(  pQdcObjInfo->cfg.pCurPkt,  _T(  ""  )  );
					 continue;
				 }
			 }
#endif

			 //			
			 break;				 
		 }
		 //
		 #if  0
			  Sleep(  40  );
		 #else
			  DWORD  dwRet;
			  QY_Q2  *  pAudioQ2  =  (  QY_Q2  *  )pQdcObjInfo->cfg.a.pAudioQ2;
			  dwRet  =  WaitForSingleObject(  pAudioQ2->hEvents[0],  40  );
			  if  (  dwRet  ==  WAIT_FAILED  )  {
				  showInfo_open0(  0,  0,  _T(  "SmplYUVReader::LoadNextFrame failed, WaitForSingleObject failed"  )  );
				  goto  errLabel;
			  }
			  #ifdef  __DEBUG__
					  #if  0
					  switch  (  dwRet  )  {
							  case  WAIT_OBJECT_0:
									traceLog(  _T(  "SmplYUVReader::LoadNextFrame: waited"  )  );
									break;
							  case  WAIT_TIMEOUT:
									traceLog(  _T(  "SmplYUVReader::LoadNextFrame: timeout"  )  );
									break;
							  default:
									  traceLog(  _T(  "SmplYUVReader::LoadNextFrame: unknown wait ret"  )  );
									  break;
					  }
					  #endif
			  #endif
		 #endif

		 //  2015/10/31
		 continue;
	}
	//
	myPLAY_AUDIO_DATA* pPkt; pPkt = (myPLAY_AUDIO_DATA*)pQdcObjInfo->cfg.a.pCurPkt;
	if  (  !pPkt  )  {
		showInfo_open0(  0,  0,  _T(  "YUVRead failed, pPkt is null"  )  );
		goto  errLabel;
	}
	//  
	if  (  enc_parseOrgAPkt_i(  pQdcObjInfo->cfg.a.uiTransformType_pParent,  pQdcObjInfo->cfg.a.pParent_transform,  pQdcObjInfo->cfg.a.pCurPkt,  pold_lPktId,  &pInput,  &uiInputSize,  pbNeed_forceKeyFrame  )  )  
	{
		showInfo_open0(  0,  0,  _T(  "YUVRead failed, enc_parsePkt failed"  )  );
		//
		if  (  pold_lPktId  )  {  //  2016/05/03
			if  (  *pold_lPktId  ==  pPkt->lPktId_getNewPkt  )  {
				//
				showInfo_open0(  0,  0,  _T(  "YUVRead failed. old_lPktId == pkt.pktId_alloc, clean pCurPkt"  )  );
				//
				pQdcObjInfo->cfg.v.pf_clean_myDRAW_VIDEO_DATA(  pQdcObjInfo->cfg.v.pCurPkt,  _T(  ""  )  );
			}
		}
		//
		goto  errLabel;
	}
	//
#if  0
	//  2015/10/29
	if  (  pPkt->usPktResType  !=  CONST_pktResType_sharedTex  )  {
		//
		if  (  !uiInputSize  )  {
			showInfo_open0(  0,  0,  _T(  "CMySmpl::ReadNextFrame failed, uiInputSize 0"  )  );
			goto  errLabel;
		}
	}
#endif

	//
	void* p0_pInput; p0_pInput = pInput;
	void* p1_uiInputSize; p1_uiInputSize = (void*)uiInputSize;
	//
#if  0
	if  (  pPkt->usPktResType  ==  CONST_pktResType_sharedTex  )  {		
		p0_pInput  =  &pPkt->sharedTex.pktSharedTexInfo;
		p1_uiInputSize  =  0;
	}
#endif
	//			
	unsigned  short  usPktResType; usPktResType = 0;
	sts  =  pf_myLoadNextFrame(  usPktResType,  p0_pInput,  p1_uiInputSize,  p2_myLoadNextFrame  );					
	if  (  sts  )  {		
		showInfo_open0(  0,  0,  _T(  "smplYUVReader_LoadNextFrame failed, pf_myLoadNextFrame failed"  )  );
		goto  errLabel;					  
	}
	
	

	//
	int  nQNodes_left; nQNodes_left = 0;
	//
#if  0
	GENERIC_Q  *  pTmpDataQ  =  (  GENERIC_Q  *  )pQdcObjInfo->cfg.a.pTmpDataQ;
	BOOL  bDbg  =  FALSE;
	//
#ifdef  __DEBUG__
		//bDbg  =  TRUE;
#endif
	//
	if  (  pTmpDataQ->uiQNodes  >  5  
		||  bDbg  )  
	{
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "enc::LoadNextFrame: tmpDataQ.uiQNodes %d"  ),  pTmpDataQ->uiQNodes  );
		showInfo_open0(  0,  0,  tBuf  );
	}
	//  2015/10/17
	nQNodes_left  =  pTmpDataQ->uiQNodes;
#endif
	//
#if  0
	int  tmp_xql_ok  =  pQdcObjInfo->cfg.v.usMaxFps_toShareBmp;	//  2015/10/24	//  *  2  /  3;
	if  (  tmp_xql_ok  <  10  )  tmp_xql_ok  =  10;
#endif
	//
#ifdef  __DEBUG__
		#if  0
			 tmp_xql_ok  =  1;  // for test
		#endif
#endif
	//
#if  0
	if  (  nQNodes_left  >  tmp_xql_ok  )  {
		int  nThrown  =  nQNodes_left  -  tmp_xql_ok;			
		//
		for  (  ;  nThrown;  nThrown  --  )  {			
			//
			if  (  pTmpDataQ->uiQNodes  <=  tmp_xql_ok  )  break;
			//
			myDRAW_VIDEO_DATA  tmpPkt;				
			unsigned  int  size  =  sizeof(  tmpPkt  );
			if  (  qGetMsg(  pTmpDataQ,  &tmpPkt,  &size  )  )  {
				showInfo_open0(  0,  0,  _T(  "smplYUV_loadFrm: qGetMsg from tmpA failed"  )  );
				break;					
			}					
			pQdcObjInfo->cfg.v.pf_clean_myDRAW_VIDEO_DATA(  &tmpPkt,  _T(  ""  )  );			
		}
		//  2015/10/19
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "smplYUV_loadFrm: qNodes %d > xql_ok %d, remove -> qNodes_left %d"  ),  nQNodes_left,  tmp_xql_ok,  pTmpDataQ->uiQNodes  );
		showInfo_open0(  0,  0,  tBuf  );
		//		
		nQNodes_left  =  pTmpDataQ->uiQNodes;
	}
#endif
	//
	int  nIntervalInMs_toAdjust_mql; nIntervalInMs_toAdjust_mql = 20 * 1000;	//  2015/10/18	//  1000;
	int  tmp_min_qNodes_left_ok; tmp_min_qNodes_left_ok = 3;	//  2015/10/18	//  1;
	//
#ifdef  __DEBUG__
		#if  0  //  for test
			 nIntervalInMs_toAdjust_mql  =  1000;
			 tmp_min_qNodes_left_ok  =  1;
		#endif
#endif
	//
			 DWORD  dwCurTgt; dwCurTgt = timeGetTime();
	if  (  abs(  (  long  )(  dwCurTgt  -  pQdcObjInfo->var.mql.dwTgt_start  )  )  >  nIntervalInMs_toAdjust_mql  )  {
#if  0
		if  (  pQdcObjInfo->var.mql.min_qNodes_left  >  tmp_min_qNodes_left_ok  )  {
			//
			int  nThrown  =  pQdcObjInfo->var.mql.min_qNodes_left  -  tmp_min_qNodes_left_ok;
			//
			for  (  ;  nThrown;  nThrown  --  )  {
				//
				if  (  pTmpDataQ->uiQNodes  <=  tmp_min_qNodes_left_ok  )  break;
				//
				myDRAW_VIDEO_DATA  tmpPkt;
				unsigned  int  size  =  sizeof(  tmpPkt  );
				if  (  qGetMsg(  pTmpDataQ,  &tmpPkt,  &size  )  )  {
					showInfo_open0(  0,  0,  _T(  "smplYUV_loadFrm: qGetMsg from tmpA failed"  )  );
					break;
				}
				pQdcObjInfo->cfg.v.pf_clean_myDRAW_VIDEO_DATA(  &tmpPkt,  _T(  ""  )  );
			}
			//
			//  2015/10/19
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "smplYUV_loadFrm: mql %d > mql_ok %d, qNodes %d, remove -> qNodes_left %d"  ),  pQdcObjInfo->var.mql.min_qNodes_left,  tmp_min_qNodes_left_ok,  nQNodes_left,  pTmpDataQ->uiQNodes  );
			showInfo_open0(  0,  0,  tBuf  );
			//
			nQNodes_left  =  pTmpDataQ->uiQNodes;			
		}
#endif
		//
		pQdcObjInfo->var.mql.min_qNodes_left  =  nQNodes_left;
		pQdcObjInfo->var.mql.dwTgt_start  =  dwCurTgt;		
		}
	else  {
		  if  (  pQdcObjInfo->var.mql.min_qNodes_left  >  nQNodes_left  )  {
			  pQdcObjInfo->var.mql.min_qNodes_left  =  nQNodes_left;
		  }
	}
	

	////////////////////////////
	if  (  pQdcObjInfo->cfg.a.uiTransformType_pParent  ==  CONST_uiTransformType_encAudio  )  {
		tmp_playLocalAudioData(  pQdcObjInfo  );
	}








	/////////////////////////



	//
#if  0
	if  (  !qPostMsg(  pQdcObjInfo->cfg.a.pCurPkt,  pQdcObjInfo->cfg.a.size_pCurPkt,  (  GENERIC_Q  *  )pQdcObjInfo->cfg.a.pTmpDataQ  )  )  {
		pQdcObjInfo->cfg.a.pf_detachPkt(  pQdcObjInfo->cfg.a.pCurPkt,  0  );
		}
	else  {
		  pQdcObjInfo->cfg.a.pf_clean_myPLAY_AUDIO_DATA(  pQdcObjInfo->cfg.a.pCurPkt,  _T(  ""  )  );
	}
#endif
	//  2016/12/15
	pQdcObjInfo->cfg.a.pf_clean_myPLAY_AUDIO_DATA(  pQdcObjInfo->cfg.a.pCurPkt,  _T(  ""  )  );



	//
	 sts_ret  =  0;

errLabel:

	 return  sts_ret;

}

 


//
 //



//
 int  old_smplYUVReader_LoadNextFrame(  void  *  pQdcObjInfoParam,  long  *  pold_lPktId,  old_PF_myLoadNextFrame  pf_myLoadNextFrame,  void  *  p2_myLoadNextFrame,  BOOL  *  pbNeed_forceKeyFrame  )
{
	int			sts_ret  =  -1;
	int			sts  =  -1;

	BYTE  *  pInput  =  NULL;			///m_var.m_pInput;
	unsigned  int  uiInputSize  =  0;	//  m_var.m_uiInputSize;
	TCHAR  tBuf[256];

	//	
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )pQdcObjInfoParam;
	if  (  !pQdcObjInfo  )  {
		showInfo_open0(  0,  0,  _T(  "CMySmpl::ReadNextFrame failed, pQdcObjInfo is null"  )  );
		goto  errLabel;
	}
	//  QDC_OBJ_hdDec	*	pObj	=	(  QDC_OBJ_hdDec  *  )pQdcObjInfo->pObj;
	//CMyDecPipeline  *  pPipeline  =  (  CMyDecPipeline  *  )pObj->pPipeline;
	//
	if  (  !pQdcObjInfo->var.ucbTransformFuncsOk  )  {
		showInfo_open0(  0,  0,  _T(  "CMySmpl::ReadNextFrame failed, ucbTransformFuncsOk is false"  )  );
		goto  errLabel;
	}
	//
	for  (  ;  ;  )  {
		 if  (  pQdcObjInfo->cfg.v.pf_bTransformVideoQuit(  pQdcObjInfo->cfg.v.pParent_transform,  0,  0  )  )  {
			 showInfo_open0(  0,  0,  _T(  "SmplYUVReader::LoadNextFrame failed, bQuit true"  )  );
			 goto  errLabel;
		 }

		//
		for  (  ;  ;  )  {
			 if  (  pQdcObjInfo->cfg.v.pf_bTransformVideoQuit(  pQdcObjInfo->cfg.v.pParent_transform,  0,  0  )  )  {
				 showInfo_open0(  0,  0,  _T(  "SmplYUVReader::LoadNextFrame failed, bQuit true"  )  );
				 goto  errLabel;
			 }
			 //		 	
			 pQdcObjInfo->cfg.v.pf_clean_myDRAW_VIDEO_DATA(  pQdcObjInfo->cfg.v.pCurPkt,  _T(  ""  )  );
			 //
			 if  (  !pQdcObjInfo->cfg.v.pf_getNextVPkt(  pQdcObjInfo->cfg.v.pCurPkt,  pQdcObjInfo->cfg.v.pInDataCacheQ,  pQdcObjInfo->cfg.v.pVideoQ2  )  )  {

				 //			
				 break;				 
			 }
			 //
			 #if  0
				  Sleep(  40  );
			 #else
				  //
			      DWORD  dwToInMs  =  40;
				  dwToInMs  =  30;
				  //
				  DWORD  dwRet;
				  QY_Q2  *  pVideoQ2  =  (  QY_Q2  *  )pQdcObjInfo->cfg.v.pVideoQ2;
				  dwRet  =  WaitForSingleObject(  pVideoQ2->hEvents[0],  dwToInMs  );
				  if  (  dwRet  ==  WAIT_FAILED  )  {
					  showInfo_open0(  0,  0,  _T(  "SmplYUVReader::LoadNextFrame failed, WaitForSingleObject failed"  )  );
					  goto  errLabel;
				  }
				  #ifdef  __DEBUG__
					  #if  0
					  switch  (  dwRet  )  {
							  case  WAIT_OBJECT_0:
									showInfo_open0(  0,  0,  _T(  "SmplYUVReader::LoadNextFrame: waited"  )  );

									break;
							  case  WAIT_TIMEOUT:
									showInfo_open0(  0,  0,  _T(  "SmplYUVReader::LoadNextFrame: timeout"  )  );
									break;
							  default:
									  showInfo_open0(  0,  0,  _T(  "SmplYUVReader::LoadNextFrame: unknown wait ret"  )  );
									  break;
					  }
					  #endif
				  #endif
			 #endif

			 //  2015/10/31
			 continue;
		}
		//
		myDRAW_VIDEO_DATA  *  pPkt  =  (  myDRAW_VIDEO_DATA  *  )pQdcObjInfo->cfg.v.pCurPkt;
		if  (  !pPkt  )  {
			showInfo_open0(  0,  0,  _T(  "YUVRead failed, pPkt is null"  )  );
			goto  errLabel;
		}
		//  
		if  (  enc_parseOrgVPkt_i(  pQdcObjInfo->cfg.v.uiTransformType_pParent,  pQdcObjInfo->cfg.v.pParent_transform,  pQdcObjInfo->cfg.v.pCurPkt,  pold_lPktId,  &pInput,  &uiInputSize,  pbNeed_forceKeyFrame  )  )  
		{
			showInfo_open0(  0,  0,  _T(  "YUVRead err, enc_parsePkt failed"  )  );
			//
			if  (  pold_lPktId  )  {  //  2016/05/03
				if  (  *pold_lPktId  ==  pPkt->lPktId_alloc  )  {
					//
					showInfo_open0(  0,  0,  _T(  "YUVRead err. old_lPktId == pkt.pktId_alloc, clean pCurPkt"  )  );
					//
					pQdcObjInfo->cfg.v.pf_clean_myDRAW_VIDEO_DATA(  pQdcObjInfo->cfg.v.pCurPkt,  _T(  ""  )  );
				}
			}
			//		
			//goto  errLabel;
			continue;
	
		}
			
		//
		break;
	}

	//
	myDRAW_VIDEO_DATA* pPkt; pPkt = (myDRAW_VIDEO_DATA*)pQdcObjInfo->cfg.v.pCurPkt;
	if  (  !pPkt  )  {
		showInfo_open0(  0,  0,  _T(  "YUVRead failed, pPkt is null"  )  );
		goto  errLabel;
	}

	//  2015/10/29
	if  (  pPkt->usPktResType  !=  CONST_pktResType_sharedTex  )  {
		//
		if  (  !uiInputSize  )  {
			showInfo_open0(  0,  0,  _T(  "CMySmpl::ReadNextFrame failed, uiInputSize 0"  )  );
			goto  errLabel;
		}
	}

	//
	char  fourccStr[4 + 1]; fourccStr[0] = 0;// = "";
#ifdef  __DEBUG__
	//
	iFourcc2Str(pPkt->bih.biCompression, fourccStr, mycountof(fourccStr));
	myUtf82TChar(fourccStr, tBuf, mycountof(tBuf));
	//
	int ii; ii = 0;
#endif

	//
	void* p0_pInput; p0_pInput = pInput;
	void* p1_uiInputSize; p1_uiInputSize = (void*)uiInputSize;
	//
	if  (  pPkt->usPktResType  ==  CONST_pktResType_sharedTex  )  {		
		p0_pInput  =  &pPkt->sharedTex.pktSharedTexInfo;
		p1_uiInputSize  =  0;
	}
	//			
	sts  =  pf_myLoadNextFrame(  pPkt->usPktResType,  p0_pInput,  p1_uiInputSize,  p2_myLoadNextFrame  );					
	if  (  sts  )  {		
		showInfo_open0(  0,  0,  _T(  "smplYUVReader_LoadNextFrame failed, pf_myLoadNextFrame failed"  )  );
		goto  errLabel;					  
	}
	
	

	//
	GENERIC_Q* pTmpDataQ; pTmpDataQ = (GENERIC_Q*)pQdcObjInfo->cfg.v.pTmpDataQ;
	BOOL  bDbg; bDbg = FALSE;
	//
#ifdef  __DEBUG__
		//bDbg  =  TRUE;
#endif
	//
	if  (  pTmpDataQ->uiQNodes  >  5  
		||  bDbg  )  
	{
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "enc::LoadNextFrame: tmpDataQ.uiQNodes %d"  ),  pTmpDataQ->uiQNodes  );
		showInfo_open0(  0,  0,  tBuf  );
	}
	//  2015/10/17
	int  nQNodes_left; nQNodes_left = pTmpDataQ->uiQNodes;
	//
	int  tmp_xql_ok; tmp_xql_ok = pQdcObjInfo->cfg.v.usMaxFps_toShareBmp;	//  2015/10/24	//  *  2  /  3;
	if  (  tmp_xql_ok  <  10  )  tmp_xql_ok  =  10;
	//
#ifdef  __DEBUG__
		#if  0
			 tmp_xql_ok  =  1;  // for test
		#endif
#endif
	//
	if  (  nQNodes_left  >  tmp_xql_ok  )  {
		int  nThrown  =  nQNodes_left  -  tmp_xql_ok;			
		//
		for  (  ;  nThrown;  nThrown  --  )  {			
			//
			if  (  pTmpDataQ->uiQNodes  <=  tmp_xql_ok  )  break;
			//
			myDRAW_VIDEO_DATA  tmpPkt;				
			unsigned  int  size  =  sizeof(  tmpPkt  );
			if  (  qGetMsg(  pTmpDataQ,  &tmpPkt,  &size  )  )  {
				showInfo_open0(  0,  0,  _T(  "smplYUV_loadFrm: qGetMsg from tmpA failed"  )  );
				break;					
			}					
			pQdcObjInfo->cfg.v.pf_clean_myDRAW_VIDEO_DATA(  &tmpPkt,  _T(  ""  )  );			
		}
		//  2015/10/19
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "smplYUV_loadFrm: qNodes %d > xql_ok %d, remove -> qNodes_left %d"  ),  nQNodes_left,  tmp_xql_ok,  pTmpDataQ->uiQNodes  );
		showInfo_open0(  0,  0,  tBuf  );
		//		
		nQNodes_left  =  pTmpDataQ->uiQNodes;
	}
	//
	int  nIntervalInMs_toAdjust_mql; nIntervalInMs_toAdjust_mql = 20 * 1000;	//  2015/10/18	//  1000;
	int  tmp_min_qNodes_left_ok; tmp_min_qNodes_left_ok = 3;	//  2015/10/18	//  1;
	//
#ifdef  __DEBUG__
		#if  0  //  for test
			 nIntervalInMs_toAdjust_mql  =  1000;
			 tmp_min_qNodes_left_ok  =  1;
		#endif
#endif
	//
			 DWORD  dwCurTgt; dwCurTgt = timeGetTime();
	if  (  abs(  (  long  )(  dwCurTgt  -  pQdcObjInfo->var.mql.dwTgt_start  )  )  >  nIntervalInMs_toAdjust_mql  )  {
		if  (  pQdcObjInfo->var.mql.min_qNodes_left  >  tmp_min_qNodes_left_ok  )  {
			//
			int  nThrown  =  pQdcObjInfo->var.mql.min_qNodes_left  -  tmp_min_qNodes_left_ok;
			//
			for  (  ;  nThrown;  nThrown  --  )  {
				//
				if  (  pTmpDataQ->uiQNodes  <=  tmp_min_qNodes_left_ok  )  break;
				//
				myDRAW_VIDEO_DATA  tmpPkt;
				unsigned  int  size  =  sizeof(  tmpPkt  );
				if  (  qGetMsg(  pTmpDataQ,  &tmpPkt,  &size  )  )  {
					showInfo_open0(  0,  0,  _T(  "smplYUV_loadFrm: qGetMsg from tmpA failed"  )  );
					break;
				}
				pQdcObjInfo->cfg.v.pf_clean_myDRAW_VIDEO_DATA(  &tmpPkt,  _T(  ""  )  );
			}
			//
			//  2015/10/19
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "smplYUV_loadFrm: mql %d > mql_ok %d, qNodes %d, remove -> qNodes_left %d"  ),  pQdcObjInfo->var.mql.min_qNodes_left,  tmp_min_qNodes_left_ok,  nQNodes_left,  pTmpDataQ->uiQNodes  );
			showInfo_open0(  0,  0,  tBuf  );
			//
			nQNodes_left  =  pTmpDataQ->uiQNodes;			
		}
		//
		pQdcObjInfo->var.mql.min_qNodes_left  =  nQNodes_left;
		pQdcObjInfo->var.mql.dwTgt_start  =  dwCurTgt;		
		}
	else  {
		  if  (  pQdcObjInfo->var.mql.min_qNodes_left  >  nQNodes_left  )  {
			  pQdcObjInfo->var.mql.min_qNodes_left  =  nQNodes_left;
		  }
	}
	
	//
	if  (  !qPostMsg(  pQdcObjInfo->cfg.v.pCurPkt,  pQdcObjInfo->cfg.v.size_pCurPkt,  (  GENERIC_Q  *  )pQdcObjInfo->cfg.v.pTmpDataQ,  _T("smplYuvReader_loadNext"))) {
		pQdcObjInfo->cfg.v.pf_detachPkt(  pQdcObjInfo->cfg.v.pCurPkt,  0  );
		}
	else  {
		  pQdcObjInfo->cfg.v.pf_clean_myDRAW_VIDEO_DATA(  pQdcObjInfo->cfg.v.pCurPkt,  _T(  ""  )  );
	}

	//
	 sts_ret  =  0;

errLabel:

	 return  sts_ret;

}


//
int  smplYUVReader_LoadNextFrame(void* pQdcObjInfoParam, long* pold_lPktId, PF_myLoadNextFrame  pf_myLoadNextFrame, void* p2_myLoadNextFrame, BOOL* pbNeed_forceKeyFrame)
{
	int			sts_ret = -1;
	int			sts = -1;

	BYTE* pInput = NULL;			///m_var.m_pInput;
	unsigned  int  uiInputSize = 0;	//  m_var.m_uiInputSize;
	TCHAR  tBuf[256];

	//	
	QDC_OBJ_INFO* pQdcObjInfo = (QDC_OBJ_INFO*)pQdcObjInfoParam;
	if (!pQdcObjInfo) {
		showInfo_open0(0, 0, _T("CMySmpl::ReadNextFrame failed, pQdcObjInfo is null"));
		goto  errLabel;
	}
	//  QDC_OBJ_hdDec	*	pObj	=	(  QDC_OBJ_hdDec  *  )pQdcObjInfo->pObj;
	//CMyDecPipeline  *  pPipeline  =  (  CMyDecPipeline  *  )pObj->pPipeline;
	//
	if (!pQdcObjInfo->var.ucbTransformFuncsOk) {
		showInfo_open0(0, 0, _T("CMySmpl::ReadNextFrame failed, ucbTransformFuncsOk is false"));
		goto  errLabel;
	}
	//
	for (; ; ) {
		if (pQdcObjInfo->cfg.v.pf_bTransformVideoQuit(pQdcObjInfo->cfg.v.pParent_transform, 0, 0)) {
			showInfo_open0(0, 0, _T("SmplYUVReader::LoadNextFrame failed, bQuit true"));
			goto  errLabel;
		}

		//
		for (; ; ) {
			if (pQdcObjInfo->cfg.v.pf_bTransformVideoQuit(pQdcObjInfo->cfg.v.pParent_transform, 0, 0)) {
				showInfo_open0(0, 0, _T("SmplYUVReader::LoadNextFrame failed, bQuit true"));
				goto  errLabel;
			}
			//		 	
			pQdcObjInfo->cfg.v.pf_clean_myDRAW_VIDEO_DATA(pQdcObjInfo->cfg.v.pCurPkt, _T(""));
			//
			if (!pQdcObjInfo->cfg.v.pf_getNextVPkt(pQdcObjInfo->cfg.v.pCurPkt, pQdcObjInfo->cfg.v.pInDataCacheQ, pQdcObjInfo->cfg.v.pVideoQ2)) {

				//			
				break;
			}
			//
#if  0
			Sleep(40);
#else
	 //
			DWORD  dwToInMs = 40;
			dwToInMs = 30;
			//
			DWORD  dwRet;
			QY_Q2* pVideoQ2 = (QY_Q2*)pQdcObjInfo->cfg.v.pVideoQ2;
			dwRet = WaitForSingleObject(pVideoQ2->hEvents[0], dwToInMs);
			if (dwRet == WAIT_FAILED) {
				showInfo_open0(0, 0, _T("SmplYUVReader::LoadNextFrame failed, WaitForSingleObject failed"));
				goto  errLabel;
			}
#endif

			//  2015/10/31
			continue;
		}

		//
		myDRAW_VIDEO_DATA* pPkt = (myDRAW_VIDEO_DATA*)pQdcObjInfo->cfg.v.pCurPkt;
		if (!pPkt) {
			showInfo_open0(0, 0, _T("YUVRead failed, pPkt is null"));
			goto  errLabel;
		}

		//
		{
			if (pQdcObjInfo->cfg.v.uiTransformType_pParent == CONST_uiTransformType_encVideo) {
				CAP_procInfo_bmpCommon* pCapProcInfo = (CAP_procInfo_bmpCommon*)pQdcObjInfo->cfg.v.pParent_transform;
				CCtxQyMc* pQyMc = g_pQyMc;
				CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

				//
				pCapProcInfo->compressVideo.encInfo.totalPkts++;

				//
				Param_bPktSkipped  param = { 0 };
				int fps_expected = pQdcObjInfo->cfg.v.usMaxFps_toShareBmp;
				int fps_real = fps_expected;
				int  nQNodes = getQ2Nodes((QY_Q2*)pQdcObjInfo->cfg.v.pVideoQ2);
				bool b4k = is4k(pPkt[0].bih.biWidth, pPkt[0].bih.biHeight);
				unsigned  __int64 nFactor = 0;
				//
				if (bPktSkipped(&param, CONST_nWhere_smplYUVReader, fps_expected, fps_real, nQNodes, pCapProcInfo->compressVideo.encInfo.totalPkts, 0, b4k, mynull, mynull)) {
					//
#ifdef  __DEBUG__
					//
					if (pProcInfo->cfg.debugStatusInfo.ucbPrint_lPktId_alloc) {
						int  nQNodes = getQ2Nodes((QY_Q2*)pQdcObjInfo->cfg.v.pVideoQ2);
						_sntprintf(tBuf, mycountof(tBuf), _T("smplYuv.l672: skipped: lAlloc %d. nQNodes %d"), pPkt->lPktId_alloc, nQNodes);
						showInfo_open(0, 0, 0, tBuf);
					}
#endif 
					//
					continue;
				}
			}
		}

		//  
		if (enc_parseOrgVPkt_i(pQdcObjInfo->cfg.v.uiTransformType_pParent, pQdcObjInfo->cfg.v.pParent_transform, pQdcObjInfo->cfg.v.pCurPkt, pold_lPktId, &pInput, &uiInputSize, pbNeed_forceKeyFrame))
		{
			showInfo_open0(0, 0, _T("YUVRead err, enc_parsePkt failed"));
			//
			if (pold_lPktId) {  //  2016/05/03
				if (*pold_lPktId == pPkt->lPktId_alloc) {
					//
					showInfo_open0(0, 0, _T("YUVRead err. old_lPktId == pkt.pktId_alloc, clean pCurPkt"));
					//
					pQdcObjInfo->cfg.v.pf_clean_myDRAW_VIDEO_DATA(pQdcObjInfo->cfg.v.pCurPkt, _T(""));
				}
			}
			//		
			//goto  errLabel;
			continue;

		}

		//
		break;
	}

	//
	myDRAW_VIDEO_DATA* pPkt; pPkt = (myDRAW_VIDEO_DATA*)pQdcObjInfo->cfg.v.pCurPkt;
	if (!pPkt) {
		showInfo_open0(0, 0, _T("YUVRead failed, pPkt is null"));
		goto  errLabel;
	}

	//  2015/10/29
	if (pPkt->usPktResType != CONST_pktResType_sharedTex) {
		//
		if (!uiInputSize) {
			showInfo_open0(0, 0, _T("CMySmpl::ReadNextFrame failed, uiInputSize 0"));
			goto  errLabel;
		}
	}

	//
	char  fourccStr[4 + 1]; fourccStr[0] = 0;// = "";
#ifdef  __DEBUG__
	//
	if (0) {
		int  nQNodes = getQ2Nodes((QY_Q2*)pQdcObjInfo->cfg.v.pVideoQ2);
		_sntprintf(tBuf, mycountof(tBuf), _T("smplYuv.l716: lAlloc %d. nQNodes %d"), pPkt->lPktId_alloc,  nQNodes );
		showInfo_open(0, 0, 0, tBuf);
	}
	//
	int ii; ii = 0;
#endif

	//
	void* p0_pInput; p0_pInput = pInput;
	void* p1_uiInputSize; p1_uiInputSize = (void*)uiInputSize;
	unsigned  int  uiSampleTimeInMs; uiSampleTimeInMs = pPkt->head.uiSampleTimeInMs;
	//
	if (pPkt->usPktResType == CONST_pktResType_sharedTex) {
		p0_pInput = &pPkt->sharedTex.pktSharedTexInfo;
		p1_uiInputSize = 0;
	}
	//
	if (0) {
		_sntprintf(tBuf, mycountof(tBuf), _T("smplYUVRead: pktResType %d"), (int)pPkt->usPktResType);
		showInfo_open0(0, 0, tBuf);
	}
	//			
	sts = pf_myLoadNextFrame(pPkt->usPktResType, pPkt->bih.biCompression,  p0_pInput, p1_uiInputSize, uiSampleTimeInMs,  p2_myLoadNextFrame);
	if (sts) {
		showInfo_open0(0, 0, _T("smplYUVReader_LoadNextFrame failed, pf_myLoadNextFrame failed"));
		goto  errLabel;
	}



	//
	GENERIC_Q* pTmpDataQ; pTmpDataQ = (GENERIC_Q*)pQdcObjInfo->cfg.v.pTmpDataQ;
	BOOL  bDbg; bDbg = FALSE;
	//
#ifdef  __DEBUG__
		//bDbg  =  TRUE;
#endif
	//
	if (pTmpDataQ->uiQNodes > 5
		|| bDbg)
	{
		_sntprintf(tBuf, mycountof(tBuf), _T("enc::LoadNextFrame: tmpDataQ.uiQNodes %d"), pTmpDataQ->uiQNodes);
		showInfo_open0(0, 0, tBuf);
	}
	//  2015/10/17
	int  nQNodes_left; nQNodes_left = pTmpDataQ->uiQNodes;
	//
	int  tmp_xql_ok; tmp_xql_ok = pQdcObjInfo->cfg.v.usMaxFps_toShareBmp;	//  2015/10/24	//  *  2  /  3;
	if (tmp_xql_ok < 10)  tmp_xql_ok = 10;
	//
#ifdef  __DEBUG__
#if  0
	tmp_xql_ok = 1;  // for test
#endif
#endif
	//
	if (nQNodes_left > tmp_xql_ok) {
		int  nThrown = nQNodes_left - tmp_xql_ok;
		//
		for (; nThrown; nThrown--) {
			//
			if (pTmpDataQ->uiQNodes <= tmp_xql_ok)  break;
			//
			myDRAW_VIDEO_DATA  tmpPkt;
			unsigned  int  size = sizeof(tmpPkt);
			if (qGetMsg(pTmpDataQ, &tmpPkt, &size)) {
				showInfo_open0(0, 0, _T("smplYUV_loadFrm: qGetMsg from tmpA failed"));
				break;
			}
			pQdcObjInfo->cfg.v.pf_clean_myDRAW_VIDEO_DATA(&tmpPkt, _T(""));
		}
		//  2015/10/19
		_sntprintf(tBuf, mycountof(tBuf), _T("smplYUV_loadFrm: qNodes %d > xql_ok %d, remove -> qNodes_left %d"), nQNodes_left, tmp_xql_ok, pTmpDataQ->uiQNodes);
		showInfo_open0(0, 0, tBuf);
		//		
		nQNodes_left = pTmpDataQ->uiQNodes;
	}
	//
	int  nIntervalInMs_toAdjust_mql; nIntervalInMs_toAdjust_mql = 20 * 1000;	//  2015/10/18	//  1000;
	int  tmp_min_qNodes_left_ok; tmp_min_qNodes_left_ok = 3;	//  2015/10/18	//  1;
	//
#ifdef  __DEBUG__
#if  0  //  for test
	nIntervalInMs_toAdjust_mql = 1000;
	tmp_min_qNodes_left_ok = 1;
#endif
#endif
	//
	DWORD  dwCurTgt; dwCurTgt = timeGetTime();
	if (abs((long)(dwCurTgt - pQdcObjInfo->var.mql.dwTgt_start)) > nIntervalInMs_toAdjust_mql) {
		if (pQdcObjInfo->var.mql.min_qNodes_left > tmp_min_qNodes_left_ok) {
			//
			int  nThrown = pQdcObjInfo->var.mql.min_qNodes_left - tmp_min_qNodes_left_ok;
			//
			for (; nThrown; nThrown--) {
				//
				if (pTmpDataQ->uiQNodes <= tmp_min_qNodes_left_ok)  break;
				//
				myDRAW_VIDEO_DATA  tmpPkt;
				unsigned  int  size = sizeof(tmpPkt);
				if (qGetMsg(pTmpDataQ, &tmpPkt, &size)) {
					showInfo_open0(0, 0, _T("smplYUV_loadFrm: qGetMsg from tmpA failed"));
					break;
				}
				pQdcObjInfo->cfg.v.pf_clean_myDRAW_VIDEO_DATA(&tmpPkt, _T(""));
			}
			//
			//  2015/10/19
			_sntprintf(tBuf, mycountof(tBuf), _T("smplYUV_loadFrm: mql %d > mql_ok %d, qNodes %d, remove -> qNodes_left %d"), pQdcObjInfo->var.mql.min_qNodes_left, tmp_min_qNodes_left_ok, nQNodes_left, pTmpDataQ->uiQNodes);
			showInfo_open0(0, 0, tBuf);
			//
			nQNodes_left = pTmpDataQ->uiQNodes;
		}
		//
		pQdcObjInfo->var.mql.min_qNodes_left = nQNodes_left;
		pQdcObjInfo->var.mql.dwTgt_start = dwCurTgt;
	}
	else {
		if (pQdcObjInfo->var.mql.min_qNodes_left > nQNodes_left) {
			pQdcObjInfo->var.mql.min_qNodes_left = nQNodes_left;
		}
	}

	//
	if (!qPostMsg(pQdcObjInfo->cfg.v.pCurPkt, pQdcObjInfo->cfg.v.size_pCurPkt, (GENERIC_Q*)pQdcObjInfo->cfg.v.pTmpDataQ, _T("smplYuvReader_loadNext"))) {
		pQdcObjInfo->cfg.v.pf_detachPkt(pQdcObjInfo->cfg.v.pCurPkt, 0);
	}
	else {
		pQdcObjInfo->cfg.v.pf_clean_myDRAW_VIDEO_DATA(pQdcObjInfo->cfg.v.pCurPkt, _T(""));
	}

	//
	sts_ret = 0;

errLabel:

	return  sts_ret;

}



//
 int  smplBitstreamReader_ReadNextFrame_func_v(  void  *  pQdcObjInfoParam,  long  *  pold_lPktId,  unsigned  int  uiToInMs,  char  *  pBsBuf,  unsigned  int  *  puiBsBufSize,  unsigned  int  *  puiSampleTimeInMs  )
 {
	 unsigned  int  uiPts  =  0;
	 SMPL_bsRead_param  param;
	 memset(  &param,  0,  sizeof(  param  )  );

	 return  smplBitstreamReader_ReadNextFrame_func_v_new(  pQdcObjInfoParam,  pold_lPktId,  uiToInMs,  pBsBuf,  puiBsBufSize,  puiSampleTimeInMs,  &uiPts,  &param  );
 }


// 
 int  smplBitstreamReader_ReadNextFrame_func_v_new(void* pQdcObjInfoParam, long* pold_lPktId, unsigned  int  uiToInMs, char* pBsBuf, unsigned  int* puiBsBufSize, unsigned  int* puiSampleTimeInMs, unsigned  int* puiPts, SMPL_bsRead_param* pParam)
 {
	 int  iErr = -1;

	 //CHECK_POINTER(pBS, MFX_ERR_NULL_PTR);
	 //  CHECK_ERROR(m_bInited, false, MFX_ERR_NOT_INITIALIZED);

#ifdef  _DEBUG
		//OutputDebugString(  _T(  "smplBitstreamReader::ReadNextFrame_func called\n"  )  );
#endif

	//
	 unsigned  int  nBytesRead = 0;

#if  0
	 if (pBS->DataOffset) {
		 memcpy(pBS->Data, pBS->Data + pBS->DataOffset, pBS->DataLength);
		 pBS->DataOffset = 0;
	 }
#endif


#if  0
	 nBytesRead = (mfxU32)fread(pBS->Data + pBS->DataLength, 1, pBS->MaxLength - pBS->DataLength, m_fSource);
#else
	 BYTE* pInput = NULL;	//  m_var.inputInfo.pInput;
	 unsigned  int  uiInputSize = 0;	//  m_var.inputInfo.uiInputSize;
	 unsigned  int  uiSampleTimeInMs = 0;	//  2015/01/28
	 unsigned  int  uiPts = 0;				//  2015/02/09
	 TCHAR  tBuf[256];

	 QDC_OBJ_INFO* pQdcObjInfo = (QDC_OBJ_INFO*)pQdcObjInfoParam;
	 if (!pQdcObjInfo) {
		 showInfo_open0(0, 0, _T("CMySmpl::ReadNextFrame failed, pQdcObjInfo is null"));
		 return    -1;
	 }
	 //  QDC_OBJ_hdDec	*	pObj	=	(  QDC_OBJ_hdDec  *  )pQdcObjInfo->pObj;
	 //CMyDecPipeline  *  pPipeline  =  (  CMyDecPipeline  *  )pObj->pPipeline;
	 //
	 if (!pQdcObjInfo->var.ucbTransformFuncsOk) {
		 showInfo_open0(0, 0, _T("CMySmpl::ReadNextFrame failed, ucbTransformFuncsOk false"));
		 return  -1;
	 }

	 //
	 QY_TRANSFORM* pTransform = (QY_TRANSFORM*)pQdcObjInfo->cfg.v.pParent_transform;

	 //
	 for (; ; ) {
		 //  2014/07/26
		 DWORD  dwTickCnt_start = timeGetTime();
		 //
		 for (; ; ) {
			 if (pQdcObjInfo->cfg.v.pf_bTransformVideoQuit(pQdcObjInfo->cfg.v.pParent_transform, 0, 0))  return  -1;
			 if (!pQdcObjInfo->cfg.v.pf_getNextVPkt(pQdcObjInfo->cfg.v.pCurPkt, pQdcObjInfo->cfg.v.pInDataCacheQ, pQdcObjInfo->cfg.v.pVideoQ2)) {
				 break;
			 }

			 //  2014/07/26
			 if (uiToInMs) {
				 DWORD  dwTickCnt = timeGetTime();
				 if (dwTickCnt - dwTickCnt_start > uiToInMs) {
					 _sntprintf(tBuf, mycountof(tBuf), _T("SmplBsReader::LoadNextFrame failed, timeout. toInMs %d"), uiToInMs);
					 showInfo_open0(0, 0, tBuf);
					 goto  errLabel;
				 }
			 }

			 //
#if  0
			 Sleep(40);
#else
	 //
			 int  nWaitInMs = 40;
			 //
			 nWaitInMs = 100;	//  2015/02/06. 是不是放大点能让cpu更悠闲点。但是，不能影响获取包的实时性
			 //
			 DWORD  dwRet;
			 QY_Q2* pVideoQ2 = (QY_Q2*)pQdcObjInfo->cfg.v.pVideoQ2;
			 dwRet = WaitForSingleObject(pVideoQ2->hEvents[0], nWaitInMs);
			 if (dwRet == WAIT_FAILED) {
				 showInfo_open0(0, 0, _T("SmplBsReader::LoadNextFrame failed, WaitForSingleObject failed"));
				 goto  errLabel;
			 }
#ifdef  __DEBUG__
#if  0  
			 {
				 CQyString	tmpStr;
				 switch (dwRet) {
				 case  WAIT_OBJECT_0:
					 tmpStr = _T("SmplBsReader::LoadNextFrame: waited");
					 break;
				 case  WAIT_TIMEOUT:
					 tmpStr = _T("SmplBsReader::LoadNextFrame: timeout");
					 break;
				 default:
					 tmpStr = _T("SmplBsReader::LoadNextFrame: unknown wait ret");
					 break;
				 }
				 showInfo_open0(0, 0, tmpStr);
			 }
#endif
#endif
#endif

		 }
#if  0
		 //  检查一下。每个包都只能处理一次，否则，容易死循环	
		 if (!pTransform->video.pCurPkt->lPktId_alloc) {
			 MACRO_qyAssert(0, _T("pktId 0"));
		 }
		 if (pTransform->video.pCurPkt->lPktId_alloc == old_pktId) {
			 showInfo_open0(0, 0, _T("failed: tn_getNextPkt==old_"));
			 goto  errLabel;
		 }
		 old_pktId = pTransform->video.pCurPkt->lPktId_alloc;
#endif
		 //
		 int  tmpiRet;
		 tmpiRet = dec_parseEncVPkt_i(pQdcObjInfo->cfg.v.uiTransformType_pParent, pQdcObjInfo->cfg.v.pParent_transform, pQdcObjInfo->cfg.v.pCurPkt, pold_lPktId, &pInput, &uiInputSize, &uiSampleTimeInMs, &uiPts, pParam);
		 if (tmpiRet == CONST_qyRet_needKeyFrameFirst)
		 {
			 pQdcObjInfo->cfg.v.pf_clean_myDRAW_VIDEO_DATA(pQdcObjInfo->cfg.v.pCurPkt, _T(""));
			 continue;
		 }
		 if (tmpiRet)
		 {
			 showInfo_open0(0, 0, _T("doTrans_default failed, parsePkt failed"));
			 return  -1;
		 }
		 //
		 break;
	 }

	 //
	 if (!uiInputSize) {
		 showInfo_open0(0, 0, _T("CMySmpl::ReadNextFrame failed, uiInputSize 0"));
		 return  -1;
	 }
	 if (uiInputSize > *puiBsBufSize) {
		 _sntprintf(tBuf, sizeof(tBuf) / sizeof(tBuf[0]), _T("CMySmpl~::ReadNextFrame failed, inputSize %d, dataSize %d:"), uiInputSize, *puiBsBufSize);
		 showInfo_open0(0, 0, tBuf);
		 return  -1;
	 }

	 //
	 pTransform->lastPkt_pts_v = uiPts;
	 pTransform->lastPkt_uiSampleTimeInMs_v = uiSampleTimeInMs;


	 //
#ifdef  _DEBUG

		//
#if  10

//
	 _sntprintf(tBuf, sizeof(tBuf) / sizeof(tBuf[0]), _T("smpl_v: %I64u, pts %d"), pTransform->video.idInfo.ui64Id, uiPts);
	 //showInfo_open0(  0,  0,  tBuf  );
#endif


#if  0
	 int  nalType = M_nalType_h264(pInput);
	 _sntprintf(tBuf, mycountof(tBuf), _T("BitstreamReader::ReadNextFrame: nalTye %d, len %d"), nalType, uiInputSize);
	 tmp_showInfo(tBuf);
#endif
	 //


	 // 
	 //
#if  1
	 int nalType; nalType = M_nalType_h265(pInput);
	 int ii; ii = 0;
	 //
	 switch (nalType) {
	 case  NAL_IDR_W_RADL:
		 ii = 0;
		 break;
	 case  NAL_IDR_N_LP:
		 ii = 0;
		 break;
	 default:
		 break;
	 }
#endif	
#endif
	 //  2014/08/05
	 //postVPktToSave(  pQdcObjInfo->cfg.v.uiTransformType_pParent,  pQdcObjInfo->cfg.v.pParent_transform,  pQdcObjInfo->cfg.v.iDecParam_index_pMems_from,  uiSampleTimeInMs,  uiPts,  (  char  *  )pInput,  uiInputSize  );  
	 if (pTransform->bInited_saver) {
		 Param_saveAv param = { 0 };
		 param.pSaveAvPktU = &pTransform->video.transSaveAv.tmpBuf_saveAvPkt;
		 //
		 param.pSave = pTransform->pSaver;
		 //
		 int  iFourcc = pTransform->video.tv.vh_stream.dwFourcc;
		 //
		 // 		//
		 int  index_activeMems_from = pTransform->index_activeMems_from;
		 __int64  idInfo_from = pTransform->video.idInfo.ui64Id;
		 int tn = pTransform->video.tv.uiTranNo_openAvDev;
		 //
		 postVPktToSave(&param, false, index_activeMems_from, idInfo_from, tn, iFourcc, uiSampleTimeInMs, uiPts, (char*)pInput, uiInputSize);

	 }
	 // 
	 // 
	 // 
	 // 
	 //
	 //  memcpy(  pBS->Data + pBS->DataLength, pInput,  uiInputSize  );  			
	 memcpy(pBsBuf, pInput, uiInputSize);
	 nBytesRead = uiInputSize;
	 //
	 //m_var.inputInfo.bFinished  =  TRUE;
#endif

	 if (0 == nBytesRead)
	 {
		 return -1;
	 }

	 //  pBS->DataLength += nBytesRead;    
	 *puiBsBufSize = nBytesRead;
	 //  2015/01/28
	 if (puiSampleTimeInMs)  *puiSampleTimeInMs = uiSampleTimeInMs;
	 if (puiPts)  *puiPts = uiPts;	//  2015/02/09

	 //
#if  1
	 GENERIC_Q* pTmpDataQ; pTmpDataQ = (GENERIC_Q*)pQdcObjInfo->cfg.v.pTmpDataQ;
	 if (pTmpDataQ->uiQNodes < 60	// 30	//  15	//  2015/02/18	//  15	//  5	//  30  //  2014/04/12
		 && !qPostMsg(pQdcObjInfo->cfg.v.pCurPkt, pQdcObjInfo->cfg.v.size_pCurPkt, (GENERIC_Q*)pQdcObjInfo->cfg.v.pTmpDataQ, _T("smplBitstreamReader_readNext")))
	 {
		 pQdcObjInfo->cfg.v.pf_detachPkt(pQdcObjInfo->cfg.v.pCurPkt, 0);
	 }
	 else {
		 pQdcObjInfo->cfg.v.pf_clean_myDRAW_VIDEO_DATA(pQdcObjInfo->cfg.v.pCurPkt, _T(""));
	 }
#else
	 pQdcObjInfo->cfg.pf_clean_myDRAW_VIDEO_DATA(pQdcObjInfo->cfg.pCurPkt, _T(""));
#endif

	 iErr = 0;

 errLabel:
	 //
	 return  iErr;
 }




//
int smplYUVWriter_WriteNextFrame_pre(  void  *  pQdcObjInfoParam,  void  *  pQDC_OBJ_transCommon,  void  *  pYUVWriter_var  )
{
	int  sts  =  -1;
	BOOL  bMsgGot  =  FALSE;

	QDC_OBJ_transCommon  *  pTrans  =  (  QDC_OBJ_transCommon  *  )pQDC_OBJ_transCommon;
	YUVWriter_var  & m_var  =  *(  YUVWriter_var  *  )pYUVWriter_var;

	if  (  !pTrans->bInited2  )  return  0;

	//
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.pQdcObjInfoParam;
	//
	DEBUG_step_dec	*	pDebugStepDec  =  (  DEBUG_step_dec  *  )getDebugStep_sth(  0,  CONST_debugStepType_dec,  (  MY_DEBUG_STEP  *  )pQdcObjInfo->var.pDebugStep  );
	if  (  !pDebugStepDec  )  return  -1;
	//
	if (pQdcObjInfo->cfg.v.uiTransformType_pParent != CONST_uiTransformType_dec)  return -1;// goto  errLabel;
	QY_TRANSFORM  *  pTransform  =  (  QY_TRANSFORM  *  )pQdcObjInfo->cfg.v.pParent_transform;
	//
	MC_VAR_common  *  pProcInfoCommon  =  (  MC_VAR_common  *  )pTransform->pProcInfo;


	//
	int  nTimeInMs  =  pDebugStepDec->nTimeInMs_smplYUVWriter_WriteNextFrame0;
	int  tmp_fps  =  0;
	if  (  nTimeInMs  )  {
		tmp_fps   =  1000  /  nTimeInMs;
		pQdcObjInfo->cfg.v.tmp_max_dec_fps  =  tmp_fps;
		}
	else  {
		  tmp_fps  =  pQdcObjInfo->cfg.v.tmp_max_dec_fps;
	}		
	if  (  tmp_fps  >  1  )  {
		//
#if  0  //  2021/05/23
		TCHAR  tBuf[128];
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u.smplYUVWriter_WriteNextFrame_pre"  ),  pTransform->video.idInfo.ui64Id  );
		//
		if  (  setPktInputInfo(  pProcInfoCommon,  &pQdcObjInfo->cfg.v.inputInfo,  tmp_fps,  FALSE,  NULL,  tBuf  )  )  {
				#ifdef  __DEBUG__
						traceLog(  _T(  "smplYUVWriter_WriteNextFrame_pre: pkt skipped"  )  );
						showInfo_open0(  0,  0,  _T(  "smplYUVWriter_WriteNextFrame_pre: pkt skipped"  )  );
				#endif
				goto  errLabel;				
		}
#endif
	}


	sts  =  0;

errLabel:

	return  sts;
}


//  2015/01/17
//  2014/07/23
int smplYUVWriter_WriteNextFrame0(  void  *  pQdcObjInfoParam,  void  *  pQDC_OBJ_transCommon,  int  iFourcc,  void  *  pYUVWriter_var,  void *pImg,  unsigned  int  cropW,  unsigned  int  cropH,  unsigned  int  pitch,  PF_img_to_yuv  pf_img_to_yuv,  double  dFrameRate,  LPCTSTR  hint  )
{ 
	int  sts  =  -1;
	BOOL  bMsgGot  =  FALSE;

	QDC_OBJ_transCommon  *  pTrans  =  (  QDC_OBJ_transCommon  *  )pQDC_OBJ_transCommon;
	YUVWriter_var  & m_var  =  *(  YUVWriter_var  *  )pYUVWriter_var;

	//  2015/10/04
	if  (  !hint  )  hint  =  _T(  ""  );

	//
	unsigned  int  i, j, h, w;   

	//  2011/12/04. 因为只能存放一祯，所以需要清0
	if  (  !m_var.pQdcObjInfoParam
		||  !m_var.pPkt  )		
	{
		showInfo_open0(  0,  0,  _T(  "yuvWrite::write failed, pPkt is null. skipped"  )  );
		return  0;
	}
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.pQdcObjInfoParam;
	
	DEBUG_step_dec	*	pDebugStepDec  =  (  DEBUG_step_dec  *  )getDebugStep_sth(  0,  CONST_debugStepType_dec,  (  MY_DEBUG_STEP  *  )pQdcObjInfo->var.pDebugStep  );
	if  (  !pDebugStepDec  )  return  -1;

	//
	DWORD  dwTickCnt_start  =  GetTickCount(  );


	//
#if  10
	if  (  !pTrans->bInited2  )  {

		int  imgWidth  =  cropW;	//  pInfo->CropW;
		int  imgHeight  =  cropH;	//  pInfo->CropH;
		if  (  !imgWidth  ||  !imgHeight  )  {
			showInfo_open0(  0,  0,  _T(  "smplYUVWriter_WriteNextFrame failed, imgW or imgH is 0"  )  );
			goto  errLabel;
		}

		//  2014/04/22	 
		//
		BITMAPINFOHEADER  bih;
		//  makeBmpInfoHeader_yv12(  12,  imgWidth,  imgHeight,  &bih  );
		makeBmpInfoHeader_yuv(  iFourcc,  12,  imgWidth,  imgHeight,  &bih  );
		if  (  pQdcObjInfo->cfg.v.dec.pf_updateDecVideoParam(  &bih,  dFrameRate,  pQdcObjInfo->cfg.v.pParent_transform,  pQdcObjInfo->cfg.v.uiTransformType_pParent  )  )  {
			showInfo_open0(  0,  0,  _T(  "decPipeline: updateDecVideoParam  failed"  )  );
			goto  errLabel;
		}

		//  qdcObjInfo.
		pQdcObjInfo->var.cbOutputBuffer  =  M_sizeImage_open(  24,  imgWidth,  imgHeight  );
		pQdcObjInfo->var.cbInputBuffer  =  pQdcObjInfo->var.cbOutputBuffer;

	
		//
		//
		memset(  &m_var.outputInfo,  0,  sizeof(  m_var.outputInfo  )  );

		//
		pTrans->bInited2  =  TRUE;


	}


#endif


		//
		BITMAPINFOHEADER	bih_trans;
		if  (  pQdcObjInfo->cfg.v.pf_transformGetBih(  pQdcObjInfo->cfg.v.pParent_transform,  &bih_trans,  0  )  )  {
			goto  errLabel;
		}
		if  (  !bih_trans.biWidth  ||  !bih_trans.biHeight  )  {
			showInfo_open0(  0,  0,  _T(  "failed: bih_trans.w,h is 0"  )  );
			goto  errLabel;
		}
		//  makeBmpInfoHeader_yv12(  12,  bih_trans.biWidth,  bih_trans.biHeight,  &bih_trans  );
		makeBmpInfoHeader_yuv(  iFourcc,  12,  bih_trans.biWidth,  bih_trans.biHeight,  &bih_trans  );


	//
	for  (  ;  ;  )  {		 
	
		//  2015/01/17
		pQdcObjInfo->cfg.v.pf_clean_myDRAW_VIDEO_DATA(  m_var.pPkt,  _T(  "smplYUVWriter"  )  );
	
		//
		unsigned  int  size  =  m_var.size_pPkt;
		if  (  qGetMsg(  (  GENERIC_Q  *  )pQdcObjInfo->cfg.v.pTmpDataQ,  m_var.pPkt,  &size  )  )  {
			TCHAR  tBuf[128]  =  _T(  ""  );
			if  (  !hint  )  hint  =  _T(  ""  );
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "yuvWrite::write failed, qGetMsg failed. %s"  ),  hint  );
			showInfo_open0(  0,  0,  tBuf  );
			return  -1;
		}
		bMsgGot  =  TRUE;
		//
		BITMAPINFOHEADER  *  pBih  =  NULL;
		if  (  pQdcObjInfo->cfg.v.pf_parseDecVPkt_o(  m_var.pPkt,  (  void  **  )&pBih,  &m_var.outputInfo.pBuf,  &m_var.outputInfo.uiOutputSize  )  )  {
			showInfo_open0(  0,  0,  _T(  "parseDecVPkt_o failed"  )  );
			goto  errLabel;
		}
		//
		m_var.outputInfo.bBufTooSmall  =  FALSE;
		m_var.outputInfo.DataOffset  =  0;
		m_var.outputInfo.len  =  0;	


		//
		if  (  pQdcObjInfo->var.usPktResType_dec  !=  CONST_pktResType_sharedTex  )  {

			//
			if  (  bih_trans.biSizeImage  >  m_var.outputInfo.uiOutputSize  )  {
				TCHAR  tBuf[128];
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "YUVWriter.writeNextFrame: trans.sizeImg %d > outputSize %d. skipped"  ), bih_trans.biSizeImage,  m_var.outputInfo.uiOutputSize  );
				showInfo_open0(  0,  0,  tBuf  );
						
				//  
				//sts  =  0;  goto  errLabel;		
				continue;

			}
		}
				
		//
		memcpy(  pBih,  &bih_trans,  sizeof(  pBih[0]  )  );
		
		//
		break;
	}

	//
	if  (  pQdcObjInfo->var.usPktResType_dec  !=  CONST_pktResType_sharedTex  )  {

		//
		if  (  bih_trans.biSizeImage  >  m_var.outputInfo.uiOutputSize  )  {
			TCHAR  tBuf[128];
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "YUVWriter.writeNextFrame: trans.sizeImg %d > outputSize %d. skipped"  ), bih_trans.biSizeImage,  m_var.outputInfo.uiOutputSize  );
			showInfo_open0(  0,  0,  tBuf  );
						
			//  
			sts  =  0;  goto  errLabel;		

		}
		
		//
		int  imgW  =  bih_trans.biWidth;
		int  imgH  =  bih_trans.biHeight;

		//
		int  yuvLen  =  imgW  *  imgH  +  imgW  *  (  imgH  >>  1  );
		
		//
		if  (  yuvLen  >  m_var.outputInfo.uiOutputSize  )  {
			m_var.outputInfo.bBufTooSmall  =  TRUE;
			}
		else  {
			  if  (  pf_img_to_yuv  )  {
				  pf_img_to_yuv(  pQdcObjInfo,  pImg,  cropW,  cropH,  pitch,  imgW,  imgH,  &m_var  );
				  m_var.outputInfo.len  =  yuvLen;
			  }
		}

		//
		if  (  m_var.outputInfo.bBufTooSmall  )  {
			TCHAR  tBuf[128];
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "yuvWrite::write err, bufTooSmall. bufSize %d, w %d, h %d"  ),  m_var.outputInfo.uiOutputSize,  cropW,  cropH  );
			showInfo_open0(  0,  0,  tBuf  );
			OutputDebugString(  _T(  "qdcSetOutput failed: uiOutputSize too big\n"  )  );							
		}
		
	}



#ifdef  __TEST_save__
		CHECK_NOT_EQUAL(
			fwrite(  m_var.outputInfo.pBuf,  m_var.outputInfo.len,  1,  m_fDest  ),
			1,  MFX_ERR_UNDEFINED_BEHAVIOR  );
#endif
		

	//
	sts  =  0;

errLabel:

	//
	pDebugStepDec->nTimeInMs_smplYUVWriter_WriteNextFrame0  =  GetTickCount(  )  -  dwTickCnt_start;

    return sts;	//  MFX_ERR_NONE;
}



//  2016/04/09
int smplYUVWriter_WriteNextFrame1(  void  *  pQdcObjInfoParam,  void  *  pQDC_OBJ_transCommon,  void  *  pYUVWriter_var  )
{ 
	int  sts  =  -1;
	BOOL  bMsgGot  =  FALSE;

	QDC_OBJ_transCommon  *  pTrans  =  (  QDC_OBJ_transCommon  *  )pQDC_OBJ_transCommon;
	YUVWriter_var  & m_var  =  *(  YUVWriter_var  *  )pYUVWriter_var;

	//
	unsigned  int  i, j, h, w;   

	//  2011/12/04. 因为只能存放一祯，所以需要清0
	if  (  !m_var.pQdcObjInfoParam
		||  !m_var.pPkt  )		
	{
		showInfo_open0(  0,  0,  _T(  "yuvWrite::write failed, pPkt is null. skipped"  )  );
		return  0;
	}
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.pQdcObjInfoParam;
	
	DEBUG_step_dec	*	pDebugStepDec  =  (  DEBUG_step_dec  *  )getDebugStep_sth(  0,  CONST_debugStepType_dec,  (  MY_DEBUG_STEP  *  )pQdcObjInfo->var.pDebugStep  );
	if  (  !pDebugStepDec  )  return  -1;

	//
	DWORD  dwTickCnt_start  =  GetTickCount(  );
	
	//  2015/01/17
	myDRAW_VIDEO_DATA  *  pPkt  =  (  myDRAW_VIDEO_DATA  *  )m_var.pPkt;
	if  (  !pPkt->memory.m_pBuf  )  return  -1;

	//  2015/09/30
	if  (  m_var.outputInfo.usPktResType  ==  CONST_pktResType_sharedTex  )  {
#if  0
		pPkt->usPktResType  =  CONST_pktResType_sharedTex;
		//
		//pPkt->sharedTex.pktSharedTexInfo  =  m_var.outputInfo.pktSharedTexInfo;
		pPkt->sharedTex.pktSharedTexInfo  =  m_var.outputInfo.pkts_sharedTexInfo.mems[0];
#endif
		myDRAW_VIDEO_DATA  tmpPkt  =  pPkt[0];
		memset(  &tmpPkt.memory,  0,  sizeof(  tmpPkt.memory  )  );
		tmpPkt.usPktResType  =  CONST_pktResType_sharedTex;
		//		
		if  (  !chkFromPlayerIndex_v(  pQdcObjInfo->cfg.v.uiTransformType_pParent,  pQdcObjInfo->cfg.v.pParent_transform,  (  myDRAW_VIDEO_DATA  *  )&tmpPkt,  0  )  )  {

			//
			if  (  !m_var.outputInfo.pkts_sharedTexInfo.ucCnt  )  {
				showInfo_open0(  0,  _T(  "smplYUVWriter_WriteNextFrame1"  ),  _T(  "ERR: pkts_sharedTex.ucCnt is 0"  )  );
			}
			//
			for  (  i  =  0;  i  <  m_var.outputInfo.pkts_sharedTexInfo.ucCnt;  i  ++  )  {
				PKT_sharedTex_info  *  pPktSharedTexInfo  =  &m_var.outputInfo.pkts_sharedTexInfo.mems[i];							
				memcpy(&tmpPkt.sharedTex.pktSharedTexInfo, pPktSharedTexInfo, sizeof(pPktSharedTexInfo[0]));
				//  
				BOOL  bPktRedirected;
				bPktRedirected  =  FALSE;
				pQdcObjInfo->cfg.v.dec.pf_postVPktToRender(  pQdcObjInfo->cfg.v.pParent_transform,  &tmpPkt,  &bPktRedirected  );	
			}
		}
		//
		sts  =  0;  goto  errLabel;
	}

	//
	#if  10
		//
		if  (  !chkFromPlayerIndex_v(  pQdcObjInfo->cfg.v.uiTransformType_pParent,  pQdcObjInfo->cfg.v.pParent_transform,  (  myDRAW_VIDEO_DATA  *  )m_var.pPkt,  0  )  )  
		{

			//  
			BOOL  bPktRedirected;
			bPktRedirected  =  FALSE;
			pQdcObjInfo->cfg.v.dec.pf_postVPktToRender(  pQdcObjInfo->cfg.v.pParent_transform,  m_var.pPkt,  &bPktRedirected  );
			if  (  bPktRedirected  )  {
				pQdcObjInfo->cfg.v.pf_detachPkt(  m_var.pPkt,  0  );
				}
			else  {
				   pQdcObjInfo->cfg.v.pf_clean_myDRAW_VIDEO_DATA(  m_var.pPkt,  _T(  ""  )  );			  
			}
			bMsgGot  =  FALSE;

		}
#endif

		sts  =  0;
errLabel:
		
		pDebugStepDec->nTimeInMs_smplYUVWriter_WriteNextFrame1  =  GetTickCount(  )  -  dwTickCnt_start;
#ifdef  __DEBUG__
#if  0
		TCHAR  tBuf[128];
		GENERIC_Q  *  pTmpQ  =  (  GENERIC_Q  *  )pQdcObjInfo->cfg.pTmpDataQ;		
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "nTime0_write %dms, nTime1_write %dms"  ),  pDebugStepDec->nTimeInMs_smplYUVWriter_WriteNextFrame0,  pDebugStepDec->nTimeInMs_smplYUVWriter_WriteNextFrame1  );
		if  (  pTmpQ  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. cnt_tmpQ %d"  ),  tBuf,  pTmpQ->uiQNodes  );
		}
		showInfo_open0(  0,  0,  tBuf  );
#endif
#endif

		return  sts;
}




///
int smplYUVWriter_WriteNextFrame_all(  void  *  pQdcObjInfoParam,  void  *  pQDC_OBJ_transCommon,  int  iFourcc,  void  *  pYUVWriter_var,  void *pImg,  unsigned  int  cropW,  unsigned  int  cropH,  unsigned  int  pitch,  PF_img_to_yuv  pf_img_to_yuv,  double  dFrameRate,  LPCTSTR  hint  )
{
	if  (  !hint  )  hint  =  _T(  ""  );
	//
	if  (  smplYUVWriter_WriteNextFrame0(  pQdcObjInfoParam,  pQDC_OBJ_transCommon,  iFourcc,  pYUVWriter_var,  pImg,  cropW,  cropH,  pitch,  pf_img_to_yuv,  dFrameRate,  hint  )  )  return  -1;
	if  (  smplYUVWriter_WriteNextFrame1(  pQdcObjInfoParam,  pQDC_OBJ_transCommon,  pYUVWriter_var  )  )  return  -1;
	return  0;
}




