

#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"
#include	"tmpCeLib.h"
#include	"qmcVideoCapture.h"
#include	"qmcDmoPublic.h"
#include	"qyCusResTemp.h"

#include	"qmcCmdProc.h"

//  #include	"qySqlFunc.h"
//#include	"qyAvRecordPublic.h"
//#include	"imgProcessPublic.h"
//#include	"isCliHelpPublic.h"

//#include	"qmcCommFunc_isCli.h"

#include	"vppProc.h"
#include	"tmpFfmpegPublic.h"
#include <imgFunc_open.h>





//
 int  old_doVpp(  MC_VAR_common  *  pProcInfo,  CTX_vpp  *  pCtx,  QY_SHARED_OBJ  *  pSharedObj,  CAP_procInfo_bmpCommon  *  pCapBmp,  myDRAW_VIDEO_DATA  *  p,  int  pktLen  )
{
	int				iErr	=	-1;
	QY_MC* pQyMc = g_pQyMc;// QY_GET_GBUF();
	//  MC_VAR_isCli  *  pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pQyMc  )  return  -1;
	if  (  !pProcInfo  )  return  -1;

	BOOL			bNeedVppBuf	=	FALSE;
	int				iFourcc  =  CONST_fourcc_YV12;

	//
	if  (  pCapBmp->compressVideo.compressor.common.ucCompressors  ==  CONST_videoCompressors_ipp		
		||  pCapBmp->compressVideo.compressor.common.ucCompressors  ==  CONST_videoCompressors_hwAccl  
		//||  pCapBmp->compressVideo.compressor.common.ucCompressors  ==  CONST_videoCompressors_cuda  
		)				  
	{
		bNeedVppBuf  =  TRUE;
	}
	//  2014/07/21
	if  (  pCapBmp->compressVideo.vh_decompress.bih.biCompression  ==  CONST_fourcc_I420  )  {
		bNeedVppBuf  =  TRUE;
		iFourcc  =  CONST_fourcc_I420;
	}

	//
	switch  (  pCapBmp->uiType  )  {
			case  CONST_capType_av:  
			case  CONST_capType_mediaDevice:  
			case  CONST_capType_screen:
			case  CONST_capType_mediaFile:
			case  CONST_capType_mosaic:
				{
				  //  
				  CAP_procInfo_bmpCommon	*	pVc	=	(  CAP_procInfo_bmpCommon  *  )pCapBmp;
				  BYTE		*  pInput  =  NULL;
				  BITMAPINFO  *  pBmpInfo_input  =  NULL;
				   
				  //					
				  if  (  !pVc->bOrg2RgbBufInited  )  {

						  pInput  =  (  BYTE  *  )p->memory.m_pBuf;
						  pBmpInfo_input  =  (  BITMAPINFO  *  )&p->bih;

						  
						  //  2013/09/20							
						  //doPreChromaKey(  pProcInfo,  &pBmpInfo_input->bmiHeader,  (  BYTE  *  )pInput,  0  );
						  
						  #if  10
							   //  2010/09/13
							   #ifndef  __WINCE__
										//
										QM_SHM_CMDS	*	pShmCmds  =  (  QM_SHM_CMDS  *  )pProcInfo->get_QM_SHM_CMDS(  );  //  QY_GET_shmCmds(  );		
										if  (  pShmCmds  )  {
											MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pProcInfo->getMisCntByIndex(  0  );  //  &pProcInfo->misCnts[0];
											if  (  !pMisCnt  )  goto  errLabel;
											//
											#if  10  //  2014/12/16. 这里的处理应该在addTxtToPic前调用		
											    COMPRESS_VIDEO  *  pCompressVideo  =  &pCapBmp->compressVideo;
												SUBTITLES_cfg	*	pCurCfg  =  (  SUBTITLES_cfg  *  )pProcInfo->get_cur_SUBTITLES_cfg(  pSharedObj->uiType1,  pCompressVideo->compressor.common.uiCapType,  pCompressVideo->compressor.common.uiSubCapType  );
												if  (  pCurCfg  )  {
													SUBTITLES_cfg  *  pSubtitlesCfg  =  &pCtx->addTxt.subtitlesCfg;
												
													//
													if  (  pCurCfg->dwModifiedTickCnt_any_start  !=  pSubtitlesCfg->dwModifiedTickCnt_any_start  )  {
														SUBTITLES_cfg	tmpCfg;
														memcpy(  &tmpCfg,  pCurCfg,  sizeof(  tmpCfg  )  );
														if  (  tmpCfg.dwModifiedTickCnt_any_start  !=  tmpCfg.dwModifiedTickCnt_any_end  )  goto  errLabel;			
														//
														memcpy(  pSubtitlesCfg,  &tmpCfg,  sizeof(  pSubtitlesCfg[0]  )  );			
														//											
													}
													
													//
													addTxtToPic(pQyMc,  &pCtx->addTxt,  pShmCmds->ucbDaemonDemo,  pMisCnt->talkerDesc,  pSharedObj->dwTickCnt_start,  pSharedObj,  &pCapBmp->compressVideo,  (  BITMAPINFO  *  )pBmpInfo_input,  (  char  *  )pInput  );
												}
											#endif
										}
							   #endif
						  #endif

#if  0  //  ndef  __DEBUG__
						  //
						  if  (  pCapBmp->compressVideo.iVppBufSize				
							  &&  pCapBmp->compressVideo.bih_vpp.biCompression  ==  CONST_fourcc_YV12  )  						  
						  {
							  rgb24ToYv12(  (  BYTE  *  )pInput,  (  BYTE  *  )pCapBmp->compressVideo.pVppBuf,  p->bih.biWidth,  p->bih.biHeight,  pCapBmp->compressVideo.compressor.common.ucbOutputFlippedImg  );									
							  memcpy(  p->memory.m_pBuf,  pCapBmp->compressVideo.pVppBuf,  pCapBmp->compressVideo.bih_vpp.biSizeImage  );
							  memcpy(  &p->bih,  &pCapBmp->compressVideo.bih_vpp,  sizeof(  p->bih  )  );
						  }
#endif
						  //
				  if  (  bNeedVppBuf  )  {
					  if  (  p->bih.biWidth  ==  pCapBmp->compressVideo.vh_decompress.bih.biWidth  &&  p->bih.biHeight  ==  pCapBmp->compressVideo.vh_decompress.bih.biHeight  
						  //||  pCapBmp->compressVideo.compressor.common.ucCompressors  ==  CONST_videoCompressors_hwAccl  
						  )  
					  {
						  //
						  if  (  chkVppBuf(  pCtx,  pCapBmp,  p->bih.biWidth,  p->bih.biHeight,  bNeedVppBuf,  iFourcc  )  )  goto  errLabel;
						  //
						  //  rgb24ToYv12(  (  BYTE  *  )pInput,  (  BYTE  *  )pCtx->vpp.pVppBuf,  p->bih.biWidth,  p->bih.biHeight,  pCapBmp->compressVideo.compressor.common.ucbOutputFlippedImg  );									
						  rgb24ToVppBuf(  (  BYTE  *  )pInput,  (  BYTE  *  )pCtx->vpp.pVppBuf,  p->bih.biWidth,  p->bih.biHeight,  0,  iFourcc  );									
						  //
						  memcpy(  p->memory.m_pBuf,  pCtx->vpp.pVppBuf,  pCtx->vpp.bih_vpp.biSizeImage  );
						  memcpy(  &p->bih,  &pCtx->vpp.bih_vpp,  sizeof(  p->bih  )  );
						  }
					  else  {  //  2014/04/24
							if  (  chkResizeBuf(  pCtx,  pCapBmp  )  )  goto  errLabel;
							if  (  pProcInfo->resizeRgb24(  (  unsigned  char  *  )p->memory.m_pBuf,  p->bih.biWidth,  p->bih.biHeight,  (  unsigned  char  *  )pCtx->resize.pBuf,  pCapBmp->compressVideo.vh_decompress.bih.biWidth,  pCapBmp->compressVideo.vh_decompress.bih.biHeight  )  )  goto  errLabel;
							
							if  (  chkVppBuf(  pCtx,  pCapBmp,  pCtx->resize.bih_rgb.biWidth,  pCtx->resize.bih_rgb.biHeight,  bNeedVppBuf,  iFourcc  )  )  goto  errLabel;
							if  (  pCtx->vpp.iVppBufSize  >  p->memory.uiBufSize  )  goto  errLabel;									
							//
							//  rgb24ToYv12(  (  unsigned  char  *  )pCtx->resize.pBuf,  (  unsigned  char  *  )p->memory.m_pBuf,  pCtx->vpp.bih_vpp.biWidth,  pCtx->vpp.bih_vpp.biHeight,  pCapBmp->compressVideo.compressor.common.ucbOutputFlippedImg  );
							rgb24ToVppBuf(  (  unsigned  char  *  )pCtx->resize.pBuf,  (  unsigned  char  *  )p->memory.m_pBuf,  pCtx->vpp.bih_vpp.biWidth,  pCtx->vpp.bih_vpp.biHeight,  0,  iFourcc  );
							//
							memcpy(  &p->bih,  &pCtx->vpp.bih_vpp,  sizeof(  p->bih  )  );							
					  }			
					  }
				  else  {	//  还有一种情况是，vh_org的长度不对，所以，需要调整到pCapBmp->compressVideo.vh_decompress
					    if  (  p->bih.biWidth  !=  pCapBmp->compressVideo.vh_decompress.bih.biWidth  ||  p->bih.biHeight  !=  pCapBmp->compressVideo.vh_decompress.bih.biHeight  )  {
							if  (  chkResizeBuf(  pCtx,  pCapBmp  )  )  goto  errLabel;
							if  (  pProcInfo->resizeRgb24(  (  unsigned  char  *  )p->memory.m_pBuf,  p->bih.biWidth,  p->bih.biHeight,  (  unsigned  char  *  )pCtx->resize.pBuf,  pCtx->resize.bih_rgb.biWidth,  pCtx->resize.bih_rgb.biHeight  )  )  goto  errLabel;
							if  (  pCtx->resize.bih_rgb.biSizeImage  >  p->memory.uiBufSize  )  goto  errLabel;
							memcpy(  p->memory.m_pBuf,  (  unsigned  char  *  )pCtx->resize.pBuf,  pCtx->resize.bih_rgb.biSizeImage  );
							//
							memcpy(  &p->bih,  &pCtx->resize.bih_rgb,  sizeof(  p->bih  )  );
						}
				  }

						  }
					  else  {							
						     if  (  org2Rgb(  (  MC_VAR_common  *  )pProcInfo,  pVc,  pVc->vh_org.bih, (  BYTE  *  )p->memory.m_pBuf,  pVc->pOrg2RgbBuf  )  )  {			
								 #ifdef  __DEBUG__
										 traceLogA(  (char*)  "Video capture: org2Rgb failed."  );
								 #endif
								 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Video capture: Decompress failed"  )  );
								 goto  errLabel;								 
							 }
							 pInput  =  (  BYTE  *  )pVc->pOrg2RgbBuf;
							 pBmpInfo_input  =  (  BITMAPINFO  *  )&pVc->vh_rgb;


							 //  2013/09/20							
							 //doPreChromaKey(  pProcInfo,  &pBmpInfo_input->bmiHeader,  (  BYTE  *  )pInput,  0  );


							 //  2010/09/13
							 #ifndef  __WINCE__
								      QM_SHM_CMDS	*	pShmCmds  =  (  QM_SHM_CMDS  *  )pProcInfo->get_QM_SHM_CMDS(  );//QY_GET_shmCmds(  );		
									  if  (  pShmCmds  )  {
										   MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pProcInfo->getMisCntByIndex(  0  );  //  &pProcInfo->misCnts[0];
										   if  (  !pMisCnt  )  goto  errLabel;
											   //
   											#if  10  //  2014/12/16. 这里的处理应该在addTxtToPic前调用		
											    COMPRESS_VIDEO  *  pCompressVideo  =  &pCapBmp->compressVideo;
												SUBTITLES_cfg	*	pCurCfg  =  (  SUBTITLES_cfg  *  )pProcInfo->get_cur_SUBTITLES_cfg(  pSharedObj->uiType1,  pCompressVideo->compressor.common.uiCapType,  pCompressVideo->compressor.common.uiSubCapType  );
												if  (  pCurCfg  )  {
													SUBTITLES_cfg  *  pSubtitlesCfg  =  &pCtx->addTxt.subtitlesCfg;
												
													//
													if  (  pCurCfg->dwModifiedTickCnt_any_start  !=  pSubtitlesCfg->dwModifiedTickCnt_any_start  )  {
														SUBTITLES_cfg	tmpCfg;
														memcpy(  &tmpCfg,  pCurCfg,  sizeof(  tmpCfg  )  );
														if  (  tmpCfg.dwModifiedTickCnt_any_start  !=  tmpCfg.dwModifiedTickCnt_any_end  )  goto  errLabel;			
														//
														memcpy(  pSubtitlesCfg,  &tmpCfg,  sizeof(  pSubtitlesCfg[0]  )  );			
														//		
													}
												
													//
												   addTxtToPic(  pQyMc,&pCtx->addTxt,  pShmCmds->ucbDaemonDemo,  pMisCnt->talkerDesc,  pSharedObj->dwTickCnt_start,  pSharedObj,  &pCapBmp->compressVideo,  (  BITMAPINFO  *  )pBmpInfo_input,  (  char  *  )pInput  );									
												}

											 #endif

									  }
							 #endif
							 
							 //
							 
#if  0	//  ndef  __DEBUG__
							 if  (  pCapBmp->compressVideo.iVppBufSize
								 &&  pCapBmp->compressVideo.bih_vpp.biCompression  ==  CONST_fourcc_YV12  )  						  
							 {
								 rgb24ToYv12(  pInput,  (  BYTE  *  )p->memory.m_pBuf,  p->bih.biWidth,  p->bih.biHeight,  pVc->compressVideo.compressor.common.ucbOutputFlippedImg  );
								 memcpy(  &p->bih,  &pCapBmp->compressVideo.bih_vpp,  sizeof(  p->bih  )  );
								 }
							 else  {
								    memcpy(  p->memory.m_pBuf,  pInput,  pBmpInfo_input->bmiHeader.biSizeImage  );									
									memcpy(  &p->bih,  pBmpInfo_input,  sizeof(  p->bih  )  );								  
							 }
#endif
							 //
							 if  (  bNeedVppBuf  )  {
								 if  (  p->bih.biWidth  ==  pCapBmp->compressVideo.vh_decompress.bih.biWidth  &&  p->bih.biHeight  ==  pCapBmp->compressVideo.vh_decompress.bih.biHeight  
									 //  ||  pCapBmp->compressVideo.compressor.common.ucCompressors  ==  CONST_videoCompressors_hwAccl  
									 )  
								 {									
									 //
									 if  (  chkVppBuf(  pCtx,  pCapBmp,  p->bih.biWidth,  p->bih.biHeight,  bNeedVppBuf,  iFourcc  )  )  goto  errLabel;
									 //
									 //  rgb24ToYv12(  (  BYTE  *  )pInput,  (  BYTE  *  )p->memory.m_pBuf,  p->bih.biWidth,  p->bih.biHeight,  pCapBmp->compressVideo.compressor.common.ucbOutputFlippedImg  );									
									 rgb24ToVppBuf(  (  BYTE  *  )pInput,  (  BYTE  *  )p->memory.m_pBuf,  p->bih.biWidth,  p->bih.biHeight,  0,  iFourcc  );									
									 //
									 memcpy(  &p->bih,  &pCtx->vpp.bih_vpp,  sizeof(  p->bih  )  );						  
									 }
								 else  {
									   if  (  chkResizeBuf(  pCtx,  pCapBmp  )  )  goto  errLabel;
									   if  (  pProcInfo->resizeRgb24(  (  unsigned  char  *  )pInput,  p->bih.biWidth,  p->bih.biHeight,  (  unsigned  char  *  )pCtx->resize.pBuf,  pCapBmp->compressVideo.vh_decompress.bih.biWidth,  pCapBmp->compressVideo.vh_decompress.bih.biHeight  )  )  goto  errLabel;
									   //
									   if  (  chkVppBuf(  pCtx,  pCapBmp,  pCtx->resize.bih_rgb.biWidth,  pCtx->resize.bih_rgb.biHeight,  bNeedVppBuf,  iFourcc  )  )  goto  errLabel;
									   //
									   if  (  pCtx->vpp.iVppBufSize  >  p->uiSize_dec  )  {
										   goto  errLabel;
									   }
									   //
									   //  rgb24ToYv12(  (  unsigned  char  *  )pCtx->resize.pBuf,  (  unsigned  char  *  )p->memory.m_pBuf,  pCtx->vpp.bih_vpp.biWidth,  pCtx->vpp.bih_vpp.biHeight,  pCapBmp->compressVideo.compressor.common.ucbOutputFlippedImg  );
									   rgb24ToVppBuf(  (  unsigned  char  *  )pCtx->resize.pBuf,  (  unsigned  char  *  )p->memory.m_pBuf,  pCtx->vpp.bih_vpp.biWidth,  pCtx->vpp.bih_vpp.biHeight,  0,  iFourcc  );
									   //
									   memcpy(  &p->bih,  &pCtx->vpp.bih_vpp,  sizeof(  p->bih  )  );
								 }
								 }
							 else  {
								   //
								   if  (  p->bih.biWidth  !=  pCapBmp->compressVideo.vh_decompress.bih.biWidth  ||  p->bih.biHeight  !=  pCapBmp->compressVideo.vh_decompress.bih.biHeight  )  {
									   if  (  chkResizeBuf(  pCtx,  pCapBmp  )  )  goto  errLabel;
									   if  (  pProcInfo->resizeRgb24(  (  unsigned  char  *  )pInput,  pBmpInfo_input->bmiHeader.biWidth,  pBmpInfo_input->bmiHeader.biHeight,  (  unsigned  char  *  )pCtx->resize.pBuf,  pCtx->resize.bih_rgb.biWidth,  pCtx->resize.bih_rgb.biHeight  )  )  goto  errLabel;
									   if  (  pCtx->resize.bih_rgb.biSizeImage  >  p->uiSize_dec  )  goto  errLabel;
									   memcpy(  p->memory.m_pBuf,  (  unsigned  char  *  )pCtx->resize.pBuf,  pCtx->resize.bih_rgb.biSizeImage  );
									   //
									   memcpy(  &p->bih,  &pCtx->resize.bih_rgb,  sizeof(  p->bih  )  );						
									   }
								   else  {
									     memcpy(  p->memory.m_pBuf,  pInput,  pBmpInfo_input->bmiHeader.biSizeImage  );									
										 memcpy(  &p->bih,  pBmpInfo_input,  sizeof(  p->bih  )  );								  
								   }
							 }


							}
					    

				  }				  
				  break;
			default:
				    TCHAR  tBuf[128];
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "doVpp: unprocessed capType %d"  ),  pCapBmp->uiType  );
					#ifdef  __DEBUG__
							traceLog((TCHAR*)  _T(  "%s"  ),  tBuf  );
					#endif
					showInfo_open0(  0,  0,  tBuf  );
					goto  errLabel;
	}



	iErr  =  0;

errLabel:

	return  iErr;
}


//
#define  isStep0_vpp(  nStep  )  (  nStep  ==  0  )
#define  isStep1_vpp(  nStep  )  (  nStep  ==  1  )
#define  isStep2_vpp(  nStep  )  (  nStep  ==  2  )


//
int  decMJPG(  CTX_vpp  *  pCtx,  myDRAW_VIDEO_DATA  *  p  )
{
	int  iErr  =  -1;

	//
	CCtxQmc  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	DWORD  dwTickCnt1  =  myGetTickCount(  NULL  );

	//
	if  (  !pCtx->qoi_decMJPG.var.pObj  )  {
		VIDEO_COMPRESSOR_CFG  vcc;
		memset(  &vcc,  0,  sizeof(  vcc  )  );
//
		//
		int iFourcc = CONST_fourcc_MJPG;
		iFourcc2Str(iFourcc, vcc.common.fourccStr, mycountof( vcc.common.fourccStr  )  );
		
		//
		//
		QY_VIDEO_HEADER  vh_d, vh_e;
		memset(  &vh_d,  0,  sizeof(  vh_d  )  );
		memset(  &vh_e,  0,  sizeof(  vh_e  )  );
		vh_e.bih  =  p->bih;
		//vh_d.bih  
		if  (  qdcInitDecompressVideo_ffmpeg(  &vcc,  &vh_e,  &vh_d,  &pCtx->qoi_decMJPG  )  )  {
			goto  errLabel;
		}
	}

	//
#if  0
	if  (  qdcDecompressVideo_ffmpeg(  &pCtx->qoi_decMJPG,  (  BITMAPINFO  *  )&p->bih,  (  BYTE  *  )p->memory.m_pBuf,  p->head.uiSampleTimeInMs  )  )  {
		goto  errLabel;
	}

	//
	int  index;
	for  (  index  =  0  ;  ;index  ++  )  {
		unsigned  int  size  =  p->memory.uiBufSize;
		if  (  qdcGetOutputByIndex_ffmpeg(  &pCtx->qoi_decMJPG,  index, (BYTE* )p->memory.m_pBuf,  &size,  &p->head.uiSampleTimeInMs,  NULL  )  )  {
			break;
		}

		//.
			p->bih.biCompression  =  CONST_fourcc_I420;
			p->bih.biSizeImage  =  size;
		//
#ifdef  __DEBUG__
		#if  0
		FILE  *  fp  =  fopen(  (  "c:\\tttbbb\\124\\mjpg.yuv"  ),  "w"  );
		if  (  fp  )  {
			fwrite(  p->memory.m_pBuf,  size,  1,  fp  );
			fclose(  fp  );
		}
		int  ii  =  0;
		#endif
#endif

		//
		continue;
	}

#else

	//
	BITMAPINFOHEADER bih_d;
	memset(&bih_d, 0, sizeof(bih_d));
	makeBmpInfoHeader_yuv(CONST_fourcc_I420, 12, p->bih.biWidth, p->bih.biHeight, &bih_d);
	bih_d.biSizeImage = p->memory.uiBufSize;
	if (qdcDecompressVideoAndOutput_ffmpeg(&pCtx->qoi_decMJPG, (BITMAPINFO*)&p->bih, (BYTE*)p->memory.m_pBuf, (BITMAPINFO*)&bih_d,  (BYTE*)p->memory.m_pBuf)) {
		goto  errLabel;
	}
	//p->bih.biCompression = CONST_fourcc_I420;
	//p->bih.biSizeImage = bih_d.biSizeImage;
	if (bih_d.biSizeImage) 
	{
		p->bih = bih_d;
	}
	else {
		int  ii = 0;
	}

#endif

	//
	iErr  =  0;
errLabel:

	//
	if (iErr) {
		//
		if (pCtx->qoi_decMJPG.var.pObj) {
			//
			showInfo_open0(0, 0, _T("decMJPG: iErr is not 0, call qdcExitDecV_ffmpeg"));
			//
			qdcExitDecompressVideo_ffmpeg(&pCtx->qoi_decMJPG);
		}
	}

	//
	if  (  pProcInfo->cfg.debugStatusInfo.ucbShowVPktInputInfo  )  {
		DWORD  dwTickCnt2  =  myGetTickCount(  NULL  );
		int  iDiffInMs  =  dwTickCnt2  -  dwTickCnt1;
		TCHAR  tBuf[128];
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "decMJPG: diffInMs %dms"  ),  iDiffInMs  );
		showInfo_open0(  0,  0,  tBuf  );
	}

	//
	return  iErr;
}




//  2015/05/07
int  new_doVpp(MC_VAR_common* pProcInfo, CTX_vpp* pCtx, QY_SHARED_OBJ* pSharedObj, CAP_procInfo_bmpCommon* pCapBmp, myDRAW_VIDEO_DATA* p, int  pktLen, int  nStep, int  index_vppHelpInfo)
{
	int				iErr = -1;
	QY_MC* pQyMc = g_pQyMc;// QY_GET_GBUF();
	if (!pQyMc)  return  -1;
	if (!pProcInfo)  return  -1;

	//
	if (index_vppHelpInfo < 0 || index_vppHelpInfo >= pCtx->ucCnt_vppHelpInfos)  return  -1;
	VPP_helpInfo* pVppHelpInfo = &pCtx->pVppHelpInfos[index_vppHelpInfo];

	//
	BOOL			bNeedVppBuf = FALSE;
	int				iFourcc = CONST_fourcc_YV12;

	//
	bool  bFailed_dec_MJPG = false;

	//
	if (pCapBmp->compressVideo.compressor.common.ucCompressors == CONST_videoCompressors_ipp
		|| pCapBmp->compressVideo.compressor.common.ucCompressors == CONST_videoCompressors_hwAccl
		//||  pCapBmp->compressVideo.compressor.common.ucCompressors  ==  CONST_videoCompressors_cuda  
		)
	{
		bNeedVppBuf = TRUE;
	}
	//  2014/07/21
	if (pCapBmp->compressVideo.vh_decompress.bih.biCompression == CONST_fourcc_I420
		|| pCapBmp->compressVideo.vh_decompress.bih.biCompression == CONST_fourcc_NV12
		) 
	{
		bNeedVppBuf = TRUE;
		iFourcc = pCapBmp->compressVideo.vh_decompress.bih.biCompression;
	}
	//
#ifdef  __DEBUG__
#endif 

	//
	switch  (  pCapBmp->uiType  )  {
			case  CONST_capType_av:  
			case  CONST_capType_mediaDevice:  
			case  CONST_capType_screen:
			case  CONST_capType_mediaFile:
			case  CONST_capType_mosaic:
			case  CONST_capType_slave:
				{
				  //  
				  CAP_procInfo_bmpCommon	*	pVc	=	(  CAP_procInfo_bmpCommon  *  )pCapBmp;
				  BYTE		*  pInput  =  NULL;
				  BITMAPINFO  *  pBmpInfo_input  =  NULL;
				   
				  //					
				  if  (  !pVc->bOrg2RgbBufInited  )  {
					  
					  if  (  isStep0_vpp(  nStep  )  )  {
						  iErr  =  0;  goto  errLabel;
					  }

					  pInput  =  (  BYTE  *  )p->memory.m_pBuf;
					  pBmpInfo_input  =  (  BITMAPINFO  *  )&p->bih;

					  //
#ifdef  __DEBUG__
					  if (1) {
						  //
						  //mySaveBitmap(&p->bih, p->memory.m_pBuf, false, _T("d:\\tttbbb\\vpp1.bmp"));
						  //
						  int  ii = 0;

					  }
#endif 



					  //
					  if  (  isStep1_vpp(  nStep  )  )  {

						  //  2013/09/20							
						  //doPreChromaKey(  pProcInfo,  &pBmpInfo_input->bmiHeader,  (  BYTE  *  )pInput,  0  );
						  
						  #if  10
							   //  2010/09/13
							   #ifndef  __WINCE__
										//
										QM_SHM_CMDS	*	pShmCmds  =  (  QM_SHM_CMDS  *  )pProcInfo->get_QM_SHM_CMDS(  );  //  QY_GET_shmCmds(  );		
										if  (  pShmCmds  )  {
											MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pProcInfo->getMisCntByIndex(  0  );  //&pProcInfo->misCnts[0];
											if  (  !pMisCnt  )  goto  errLabel;
											//
											#if  10  //  2014/12/16. 这里的处理应该在addTxtToPic前调用		
											    COMPRESS_VIDEO  *  pCompressVideo  =  &pCapBmp->compressVideo;
												SUBTITLES_cfg	*	pCurCfg  =  (  SUBTITLES_cfg  *  )pProcInfo->get_cur_SUBTITLES_cfg(  pSharedObj->uiType1,  pCompressVideo->compressor.common.uiCapType,  pCompressVideo->compressor.common.uiSubCapType  );
												if  (  pCurCfg  )  {
													SUBTITLES_cfg  *  pSubtitlesCfg  =  &pCtx->addTxt.subtitlesCfg;
												
													//
													if  (  pCurCfg->dwModifiedTickCnt_any_start  !=  pSubtitlesCfg->dwModifiedTickCnt_any_start  )  {
														SUBTITLES_cfg	tmpCfg;
														memcpy(  &tmpCfg,  pCurCfg,  sizeof(  tmpCfg  )  );
														if  (  tmpCfg.dwModifiedTickCnt_any_start  !=  tmpCfg.dwModifiedTickCnt_any_end  )  goto  errLabel;			
														//
														memcpy(  pSubtitlesCfg,  &tmpCfg,  sizeof(  pSubtitlesCfg[0]  )  );			
														//											
													}
													
													//
													addTxtToPic(  pQyMc,&pCtx->addTxt,  pShmCmds->ucbDaemonDemo,  pMisCnt->talkerDesc,  pSharedObj->dwTickCnt_start,  pSharedObj,  &pCapBmp->compressVideo,  (  BITMAPINFO  *  )pBmpInfo_input,  (  char  *  )pInput  );
												}
											#endif
										}
							   #endif
						  #endif
										
						  //								  
						  iErr  =  0;  goto  errLabel;
					  }
					  						
					  //		
					  if  (  bNeedVppBuf  )  {
						  if  (  p->bih.biWidth  ==  pCapBmp->compressVideo.vh_decompress.bih.biWidth  &&  p->bih.biHeight  ==  pCapBmp->compressVideo.vh_decompress.bih.biHeight  
							  //||  pCapBmp->compressVideo.compressor.common.ucCompressors  ==  CONST_videoCompressors_hwAccl  
							  )  
						  {
							  //
#ifdef  __DEBUG__
							  if (1) {
								  //mySaveBitmap(&p->bih, p->memory.m_pBuf, false, _T("d:\\tttbbb\\doVpp2.bmp"));
							  }
#endif 

							  //
							  if  (  chkVppBuf(  pCtx,  pCapBmp,  p->bih.biWidth,  p->bih.biHeight,  bNeedVppBuf,  iFourcc  )  )  goto  errLabel;
							  //
							  //  rgb24ToYv12(  (  BYTE  *  )pInput,  (  BYTE  *  )pCtx->vpp.pVppBuf,  p->bih.biWidth,  p->bih.biHeight,  pCapBmp->compressVideo.compressor.common.ucbOutputFlippedImg  );									
							  rgb24ToVppBuf(  (  BYTE  *  )pInput,  (  BYTE  *  )pCtx->vpp.pVppBuf,  p->bih.biWidth,  p->bih.biHeight,  0,  iFourcc  );									
							  //
							  if (1) {
								  //mySaveYv12(p->bih.biWidth, p->bih.biHeight, pCtx->vpp.pVppBuf, true, _T("d:\\tttbbb\\rtt.yv12.l531.bmp"));
							  }
							  //
							  memcpy(  p->memory.m_pBuf,  pCtx->vpp.pVppBuf,  pCtx->vpp.bih_vpp.biSizeImage  );
							  memcpy(  &p->bih,  &pCtx->vpp.bih_vpp,  sizeof(  p->bih  )  );
							  }
						  else  {  //  2014/04/24
								if  (  chkResizeBuf(  pCtx,  pCapBmp  )  )  goto  errLabel;
								if  (  pProcInfo->resizeRgb24(  (  unsigned  char  *  )p->memory.m_pBuf,  p->bih.biWidth,  p->bih.biHeight,  (  unsigned  char  *  )pCtx->resize.pBuf,  pCapBmp->compressVideo.vh_decompress.bih.biWidth,  pCapBmp->compressVideo.vh_decompress.bih.biHeight  )  )  goto  errLabel;
								
								if  (  chkVppBuf(  pCtx,  pCapBmp,  pCtx->resize.bih_rgb.biWidth,  pCtx->resize.bih_rgb.biHeight,  bNeedVppBuf,  iFourcc  )  )  goto  errLabel;
								if  (  pCtx->vpp.iVppBufSize  >  p->memory.uiBufSize  )  goto  errLabel;									
								//
								//  rgb24ToYv12(  (  unsigned  char  *  )pCtx->resize.pBuf,  (  unsigned  char  *  )p->memory.m_pBuf,  pCtx->vpp.bih_vpp.biWidth,  pCtx->vpp.bih_vpp.biHeight,  pCapBmp->compressVideo.compressor.common.ucbOutputFlippedImg  );
								rgb24ToVppBuf(  (  unsigned  char  *  )pCtx->resize.pBuf,  (  unsigned  char  *  )p->memory.m_pBuf,  pCtx->vpp.bih_vpp.biWidth,  pCtx->vpp.bih_vpp.biHeight,  0,  iFourcc  );
								//
								memcpy(  &p->bih,  &pCtx->vpp.bih_vpp,  sizeof(  p->bih  )  );							
						  }			
					  }
					  else  {	//  还有一种情况是，vh_org的长度不对，所以，需要调整到pCapBmp->compressVideo.vh_decompress
						    if  (  p->bih.biWidth  !=  pCapBmp->compressVideo.vh_decompress.bih.biWidth  ||  p->bih.biHeight  !=  pCapBmp->compressVideo.vh_decompress.bih.biHeight  )  {
								if  (  chkResizeBuf(  pCtx,  pCapBmp  )  )  goto  errLabel;
								if  (  pProcInfo->resizeRgb24(  (  unsigned  char  *  )p->memory.m_pBuf,  p->bih.biWidth,  p->bih.biHeight,  (  unsigned  char  *  )pCtx->resize.pBuf,  pCtx->resize.bih_rgb.biWidth,  pCtx->resize.bih_rgb.biHeight  )  )  goto  errLabel;
								if  (  pCtx->resize.bih_rgb.biSizeImage  >  p->memory.uiBufSize  )  goto  errLabel;
								memcpy(  p->memory.m_pBuf,  (  unsigned  char  *  )pCtx->resize.pBuf,  pCtx->resize.bih_rgb.biSizeImage  );
								//
								memcpy(  &p->bih,  &pCtx->resize.bih_rgb,  sizeof(  p->bih  )  );
							}
					  }

					  }
				
				  else  {	 //  bOrg2RgbBufInited true

							 //
							 if  (  isStep0_vpp(  nStep  )  )  {
								 //
								 if  (  p->bih.biCompression  ==  CONST_fourcc_MJPG  )  {
									 //
									 if  (  decMJPG(  pCtx,  p  )  )  {
										 //
										 showInfo_open0(0, 0, _T("new_doVpp: decMJPG failed"));
										 //
										 goto  errLabel;
									 }
									 //
									 {
										 char  buf[128];
										 iFourcc2Str(p->bih.biCompression, buf, mycountof(buf));
										 //
										 int  ii = 0;

									 }
									 //
									 if (p->bih.biCompression != CONST_fourcc_I420) {
										 //
										 //traceLog((TCHAR*)_T("new_doVpp failed: mjpg,l592,biCompression is not i420"));
										 //
										 bFailed_dec_MJPG = true;
										 //
										 goto  errLabel;
									 }
									 //
									 //iErr  =  0;  goto  errLabel;
								 }
								 //
								 if  (  !pVppHelpInfo->pBuf  ||  pVppHelpInfo->uiBufSize  <  pVc->vh_rgb.bih.biSizeImage  )  {
									 MACRO_safeFree(  pVppHelpInfo->pBuf  );
									 pVppHelpInfo->uiBufSize  =  pVc->vh_rgb.bih.biSizeImage;
									 pVppHelpInfo->pBuf  =  (  char  *  )mymalloc(  pVppHelpInfo->uiBufSize  );
									 if  (  !pVppHelpInfo->pBuf  )  goto  errLabel;

									 //
									 showInfo_open0(0, 0, _T("new_doVpp: malloc"));
								 }
								 //
								 if (bNeedFakePic()) {
									 if (do_fakePic(pCtx, p->bih.biWidth, p->bih.biHeight, 0,  pVppHelpInfo->pBuf, pVppHelpInfo->uiBufSize)) {
										 showInfo_open0(0, 0, _T("new_doVpp.do_fakePic failed"));
										 goto  errLabel;
									 }
									 iErr = 0;  goto  errLabel;
								 }

								 //
								 BITMAPINFOHEADER bih_org = pVc->vh_org.bih;
								 if (pVc->vh_org.bih.biCompression == CONST_fourcc_MJPG) {
									 bih_org = p->bih;
								 }

								 //
								 if  (  org2Rgb(  (  MC_VAR_common  *  )pProcInfo,  pVc,  bih_org, (  BYTE  *  )p->memory.m_pBuf,  pVppHelpInfo->pBuf  )  )  {			
									 #ifdef  __DEBUG__
											 traceLogA(  (char*)  "Video capture: org2Rgb failed."  );
									 #endif
									 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Video capture: Decompress failed"  )  );
									 goto  errLabel;								 
								 }
								 //
#ifdef  __DEBUG__
								 //
#if  0
								 if (1) {
									 int  ii = 0;
									 //
									 BITMAPINFOHEADER  bih_rgb;
									 makeBmpInfoHeader_rgb(24, bih_org.biWidth, bih_org.biHeight, &bih_rgb);
									 //									 
									 mySaveBitmap(&bih_rgb, pVppHelpInfo->pBuf, false, _T("d:\\tttbbb\\mmm.bmp"));
								 }
#endif 
								 //
#endif 
								 //
								 iErr  =  0;  goto  errLabel;
							 }
							 pInput  =  (  BYTE  *  )pVppHelpInfo->pBuf;
							 pBmpInfo_input  =  (  BITMAPINFO  *  )&pVc->vh_rgb;

							 if  (  isStep1_vpp(  nStep  )  )  {

								 //  2013/09/20							
								 //doPreChromaKey(  pProcInfo,  &pBmpInfo_input->bmiHeader,  (  BYTE  *  )pInput,  0  );


								 //  2010/09/13
								 #ifndef  __WINCE__
								      QM_SHM_CMDS	*	pShmCmds  =  (  QM_SHM_CMDS  *  )pProcInfo->get_QM_SHM_CMDS(  );
									  if  (  pShmCmds  )  {
										   MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pProcInfo->getMisCntByIndex(  0  );  //&pProcInfo->misCnts[0];
										   if  (  !pMisCnt  )  goto  errLabel;
											   //
   											#if  10  //  2014/12/16. 这里的处理应该在addTxtToPic前调用		
											    COMPRESS_VIDEO  *  pCompressVideo  =  &pCapBmp->compressVideo;
												SUBTITLES_cfg	*	pCurCfg  =  (  SUBTITLES_cfg  *  )pProcInfo->get_cur_SUBTITLES_cfg(  pSharedObj->uiType1,  pCompressVideo->compressor.common.uiCapType,  pCompressVideo->compressor.common.uiSubCapType  );
												if  (  pCurCfg  )  {
													SUBTITLES_cfg  *  pSubtitlesCfg  =  &pCtx->addTxt.subtitlesCfg;
												
													//
													if  (  pCurCfg->dwModifiedTickCnt_any_start  !=  pSubtitlesCfg->dwModifiedTickCnt_any_start  )  {
														SUBTITLES_cfg	tmpCfg;
														memcpy(  &tmpCfg,  pCurCfg,  sizeof(  tmpCfg  )  );
														if  (  tmpCfg.dwModifiedTickCnt_any_start  !=  tmpCfg.dwModifiedTickCnt_any_end  )  goto  errLabel;			
														//
														memcpy(  pSubtitlesCfg,  &tmpCfg,  sizeof(  pSubtitlesCfg[0]  )  );			
														//		
													}
												
													//
												   addTxtToPic(  pQyMc,&pCtx->addTxt,  pShmCmds->ucbDaemonDemo,  pMisCnt->talkerDesc,  pSharedObj->dwTickCnt_start,  pSharedObj,  &pCapBmp->compressVideo,  (  BITMAPINFO  *  )pBmpInfo_input,  (  char  *  )pInput  );									
												}

											 #endif

									  }
								 #endif
							 
								  //
								  iErr  =  0;  goto  errLabel;
							 }
							 //
							 if  (  bNeedVppBuf  )  {
								 //
#ifdef  __DEBUG__
								 if (0) {
									 traceLog((TCHAR*)_T("test: set NV12"));
									 iFourcc = CONST_fourcc_NV12;
								 }
#endif 
								 //
								 if  (  p->bih.biWidth  ==  pCapBmp->compressVideo.vh_decompress.bih.biWidth  &&  p->bih.biHeight  ==  pCapBmp->compressVideo.vh_decompress.bih.biHeight  
									 //  ||  pCapBmp->compressVideo.compressor.common.ucCompressors  ==  CONST_videoCompressors_hwAccl  
									 )  
								 {	
									 //
									 if (1) {
#if  0
										 BITMAPINFOHEADER bih_rgb;
										 makeBmpInfoHeader_rgb(24, p->bih.biWidth, p->bih.biHeight, &bih_rgb);
										 mySaveBitmap(&bih_rgb, pInput, false, _T("d:\\tttbbb\\doVpp2.bmp"));
#endif 
									 }

									 //
									 if  (  chkVppBuf(  pCtx,  pCapBmp,  p->bih.biWidth,  p->bih.biHeight,  bNeedVppBuf,  iFourcc  )  )  goto  errLabel;

									 //
									 bool bFlip;
									 bFlip = false;
									 if (iFourcc == CONST_fourcc_NV12)  bFlip = true;

									 //
									 //  rgb24ToYv12(  (  BYTE  *  )pInput,  (  BYTE  *  )p->memory.m_pBuf,  p->bih.biWidth,  p->bih.biHeight,  pCapBmp->compressVideo.compressor.common.ucbOutputFlippedImg  );									
									 rgb24ToVppBuf(  (  BYTE  *  )pInput,  (  BYTE  *  )p->memory.m_pBuf,  p->bih.biWidth,  p->bih.biHeight,  bFlip,  iFourcc  );	
									 //
#ifdef  __DEBUG__
									 if (1) {
										 //
#if  0
										 char ttbuf[128];
										 iFourcc2Str(pCtx->vpp.bih_vpp.biCompression,ttbuf,mycountof(ttbuf));
										 BITMAPINFOHEADER  bih_rgb;
										 makeBmpInfoHeader_rgb(24, p->bih.biWidth, p->bih.biHeight, &bih_rgb);
										 unsigned  char* rgb = (unsigned  char*)mymalloc(bih_rgb.biSizeImage);
										 if (rgb) {
											 //
											 nv12ToRgb24((unsigned  char  *  )p->memory.m_pBuf, rgb, p->bih.biWidth, p->bih.biHeight,true);
											 //
											 mySaveBitmap(&bih_rgb, rgb, false, _T("d:\\tttbbb\\doVpp2.l743.bmp"));
											 //
											 myfree(rgb);
										 }
										 //
#endif 
									 }
#endif 
									 //
									 memcpy(  &p->bih,  &pCtx->vpp.bih_vpp,  sizeof(  p->bih  )  );						  
									 }
								 else  {
									 //
#ifdef  __DEBUG__									
									 //
									 if (p->bih.biCompression == CONST_fourcc_I420) {
										 if (1) {
											 traceLog((TCHAR*)_T("l683: for i420, mySaveI420 called"));
											 mySaveI420(p->bih.biWidth, p->bih.biHeight, p->memory.m_pBuf, true, _T("d:\\tttbbb\\l682.bmp"));
										 }
									 }
#endif 

									 //
									   if  (  chkResizeBuf(  pCtx,  pCapBmp  )  )  goto  errLabel;
									   if  (  pProcInfo->resizeRgb24(  (  unsigned  char  *  )pInput,  p->bih.biWidth,  p->bih.biHeight,  (  unsigned  char  *  )pCtx->resize.pBuf,  pCapBmp->compressVideo.vh_decompress.bih.biWidth,  pCapBmp->compressVideo.vh_decompress.bih.biHeight  )  )  goto  errLabel;
									   //
									   // 
#ifdef  __DEBUG__
									   if (1) {
										   traceLog((TCHAR*)_T("l697: for test, save "));
										   //
										   mySaveBitmap(&pCtx->resize.bih_rgb, pCtx->resize.pBuf, true, _T("d:\\tttbbb\\l698.bmp"));

									   }
#endif 
									   // 
									   //
									   if  (  chkVppBuf(  pCtx,  pCapBmp,  pCtx->resize.bih_rgb.biWidth,  pCtx->resize.bih_rgb.biHeight,  bNeedVppBuf,  iFourcc  )  )  goto  errLabel;
									   //
									   if  (  pCtx->vpp.iVppBufSize  >  p->uiSize_dec  )  {
										   //
										   traceLog((TCHAR*)_T("new_doVpp failed, iVppBufSize > uiSize_dec"));
										   //
										   goto  errLabel;
									   }
									   //
									   //  rgb24ToYv12(  (  unsigned  char  *  )pCtx->resize.pBuf,  (  unsigned  char  *  )p->memory.m_pBuf,  pCtx->vpp.bih_vpp.biWidth,  pCtx->vpp.bih_vpp.biHeight,  pCapBmp->compressVideo.compressor.common.ucbOutputFlippedImg  );
									   rgb24ToVppBuf(  (  unsigned  char  *  )pCtx->resize.pBuf,  (  unsigned  char  *  )p->memory.m_pBuf,  pCtx->vpp.bih_vpp.biWidth,  pCtx->vpp.bih_vpp.biHeight,  0,  iFourcc  );
									   //
									   memcpy(  &p->bih,  &pCtx->vpp.bih_vpp,  sizeof(  p->bih  )  );
								 }
								 }
							 else  {
								   //
								   if  (  p->bih.biWidth  !=  pCapBmp->compressVideo.vh_decompress.bih.biWidth  ||  p->bih.biHeight  !=  pCapBmp->compressVideo.vh_decompress.bih.biHeight  )  {
									   if  (  chkResizeBuf(  pCtx,  pCapBmp  )  )  goto  errLabel;
									   if  (  pProcInfo->resizeRgb24(  (  unsigned  char  *  )pInput,  pBmpInfo_input->bmiHeader.biWidth,  pBmpInfo_input->bmiHeader.biHeight,  (  unsigned  char  *  )pCtx->resize.pBuf,  pCtx->resize.bih_rgb.biWidth,  pCtx->resize.bih_rgb.biHeight  )  )  goto  errLabel;
									   if  (  pCtx->resize.bih_rgb.biSizeImage  >  p->uiSize_dec  )  goto  errLabel;
									   memcpy(  p->memory.m_pBuf,  (  unsigned  char  *  )pCtx->resize.pBuf,  pCtx->resize.bih_rgb.biSizeImage  );
									   //
									   memcpy(  &p->bih,  &pCtx->resize.bih_rgb,  sizeof(  p->bih  )  );						
									   }
								   else  {
									     memcpy(  p->memory.m_pBuf,  pInput,  pBmpInfo_input->bmiHeader.biSizeImage  );									
										 memcpy(  &p->bih,  pBmpInfo_input,  sizeof(  p->bih  )  );								  
								   }
							 }


							
						}
					    

				  }				  
				  break;
			default:
				    TCHAR  tBuf[128];
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "doVpp: unprocessed capType %d"  ),  pCapBmp->uiType  );
					#ifdef  __DEBUG__
							traceLog((TCHAR*)  _T(  "%s"  ),  tBuf  );
					#endif
					showInfo_open0(  0,  0,  tBuf  );
					goto  errLabel;
	}



	iErr  =  0;

errLabel:

	//
	if (iErr) {
		//
		if (isStep0_vpp(nStep)) {
			if (!bFailed_dec_MJPG) {
				showInfo_open0(0, 0, _T("doVpp0 failed, new_doVpp failed"));
			}
		}
		else  if (isStep1_vpp(nStep)) {
			showInfo_open0(0, 0, _T("doVpp1 failed, new_doVpp failed"));
		}
		else  if (isStep2_vpp(nStep)) {
			showInfo_open0(0, 0, _T("doVpp2 failed, new_doVpp failed"));
		}
		else {
			showInfo_open0(0, 0, _T("doVpp_err failed, new_doVpp failed"));
		}
		//
	}


	//
	return  iErr;
}


///////////////////
 int  doVpp0(  MC_VAR_common  *  pProcInfo,  CTX_vpp  *  pCtx,  QY_SHARED_OBJ  *  pSharedObj,  CAP_procInfo_bmpCommon  *  pCapBmp,  myDRAW_VIDEO_DATA  *  p,  int  pktLen  )
 {
	 int  iErr  =  -1;
	 QY_MC* pQyMc = g_pQyMc;// QY_GET_GBUF();

	 //  
	 int  index  =  pCtx->uiCnt_vpp0  %  pCtx->ucCnt_vppHelpInfos;
	 VPP_helpInfo  *  pVppHelpInfo  =  &pCtx->pVppHelpInfos[index];
	 TCHAR  tMutexName[128];
	 //_sntprintf(  tMutexName,  mycountof(  tMutexName  ),  _T(  "%s%s%d"  ),  pQyMc->appParams.appObjPrefix,  CONST_mutexNamePrefix_syncVpp,  index  );
	 M_getMutexName_vpp(tMutexName, mycountof(tMutexName), pSharedObj, index);
	 CQySyncObj	syncObj;
	 if  (  syncObj.sync(  tMutexName,  0  )  )  {
		 showInfo_open0(  0,  0,  _T(  "doVpp0 failed, sync failed"  )  );
		 goto  errLabel;
	 }

	 //
	 if (pSharedObj->index_sharedObj) {
		 int  ii = 0;
	 }

	 //
#ifdef  __DEBUG__
	 if (1) {
		 //mySaveBitmap(&p->bih, p->memory.m_pBuf, false, _T("d:\\tttbbb\\doVpp0.bmp"));
		}
#endif 

	 //
	 if  (  pVppHelpInfo->procFlgs.bProcessed_step0  )  {
		 if  (  !pVppHelpInfo->procFlgs.bProcessed_step2  )  {
			 #ifdef  __DEBUG__
					 //showInfo_open0(  0,  0,  _T(  "Note: doVpp0, vppHelpInfo.bProcessed_step2 not true"  )  );
			 #endif
		 }
	 }
	 pVppHelpInfo->uiCnt_vpp0  =  0;
	 memset(  &pVppHelpInfo->procFlgs,  0,  sizeof(  pVppHelpInfo->procFlgs  )  );

	 //
	 if  (  new_doVpp(  pProcInfo,  pCtx,  pSharedObj,  pCapBmp,  p,  pktLen,  0,  index  )  )  {
		 //
		 //showInfo_open0(  0,  0,  _T(  "doVpp0 failed, new_doVpp failed"  )  );
		 //
		 goto  errLabel;
	 }

	 //
	 p->vpp.uiCnt_vpp0  =  pCtx->uiCnt_vpp0;
	 pVppHelpInfo->uiCnt_vpp0  =  pCtx->uiCnt_vpp0;
	 pVppHelpInfo->procFlgs.bProcessed_step0  =  TRUE;

	 //
	 pCtx->uiCnt_vpp0  ++  ;

	 iErr  =  0;
errLabel:

	 return  iErr;
 }

 int  doVpp1(  MC_VAR_common  *  pProcInfo,  CTX_vpp  *  pCtx,  QY_SHARED_OBJ  *  pSharedObj,  CAP_procInfo_bmpCommon  *  pCapBmp,  myDRAW_VIDEO_DATA  *  p,  int  pktLen  )
 {
	 int  iErr  =  -1;
	 QY_MC* pQyMc = g_pQyMc;// QY_GET_GBUF();

	 if  (  p->vpp.uiCnt_vpp0  >=  pCtx->uiCnt_vpp0  )  {
		 showInfo_open0(  0,  0,  _T(  "doVpp1 failed: pkt.uiCnt_vpp0 >= ctx.uiCnt_vpp0"  )  );
		 goto  errLabel;
	 }
	 if  (  p->vpp.uiCnt_vpp0  <  pCtx->uiCnt_vpp1  )  {
		 showInfo_open0(  0,  0,  _T(  "doVpp1 failed: pkt.uiCnt_vpp0 <  ctx.uiCnt_vpp1"  )  );
		 goto  errLabel;
	 }	 
	 //
	 {
	 
		 int  index  =  p->vpp.uiCnt_vpp0  %  pCtx->ucCnt_vppHelpInfos;
		 VPP_helpInfo  *  pVppHelpInfo  =  &pCtx->pVppHelpInfos[index];
		 TCHAR  tMutexName[128];
		 //_sntprintf(  tMutexName,  mycountof(  tMutexName  ),  _T(  "%s%s%d"  ),  pQyMc->appParams.appObjPrefix,  CONST_mutexNamePrefix_syncVpp,  index  );
		 M_getMutexName_vpp(tMutexName, mycountof(tMutexName), pSharedObj, index);
		 CQySyncObj	syncObj;
		 if  (  syncObj.sync(  tMutexName,  0  )  )  {
			 showInfo_open0(  0,  0,  _T(  "doVpp1 failed, sync failed. 2"  )  );
			 goto  errLabel;
		 }
		 //
		 if  (  pVppHelpInfo->uiCnt_vpp0  !=  p->vpp.uiCnt_vpp0  )  {
			 showInfo_open0(  0,  0,  _T(  "doVpp1 failed, helpInfo.cnt_vpp0  !=  pkt.cnt_vpp0"  )  );  
			 goto  errLabel;
		 }
		 //
		 if  (  new_doVpp(  pProcInfo,  pCtx,  pSharedObj,  pCapBmp,  p,  pktLen,  1,  index  )  )  {
			 showInfo_open0(  0,  0,  _T(  "doVpp1 failed, new_doVpp failed"  )  );
			 goto  errLabel;
		 }
		 //
		 pVppHelpInfo->procFlgs.bProcessed_step1  =  TRUE;
		 pCtx->uiCnt_vpp1  ++  ;

	 }


	 iErr  =  0;	 
errLabel:
	 return  iErr;
 }


  int  doVpp2(  MC_VAR_common  *  pProcInfo,  CTX_vpp  *  pCtx,  QY_SHARED_OBJ  *  pSharedObj,  CAP_procInfo_bmpCommon  *  pCapBmp,  myDRAW_VIDEO_DATA  *  p,  int  pktLen  )
 {
	 int  iErr  =  -1;
	 QY_MC* pQyMc = g_pQyMc;// QY_GET_GBUF();

	 if  (  p->vpp.uiCnt_vpp0  >=  pCtx->uiCnt_vpp0  )  {
		 showInfo_open0(  0,  0,  _T(  "doVpp2 failed: pkt.uiCnt_vpp0 >= ctx.uiCnt_vpp0"  )  );
		 goto  errLabel;
	 }
	 if  (  p->vpp.uiCnt_vpp0  <  pCtx->uiCnt_vpp2  )  {
		 showInfo_open0(  0,  0,  _T(  "doVpp2 failed: pkt.uiCnt_vpp0 <  ctx.uiCnt_vpp2"  )  );
		 goto  errLabel;
	 }
	 //
	 {
	 
		 int  index  =  p->vpp.uiCnt_vpp0  %  pCtx->ucCnt_vppHelpInfos;
		 VPP_helpInfo  *  pVppHelpInfo  =  &pCtx->pVppHelpInfos[index];
		 TCHAR  tMutexName[128];
		 //_sntprintf(  tMutexName,  mycountof(  tMutexName  ),  _T(  "%s%s%d"  ),  pQyMc->appParams.appObjPrefix,  CONST_mutexNamePrefix_syncVpp,  index  );
		 M_getMutexName_vpp(tMutexName, mycountof(tMutexName), pSharedObj, index);
		 CQySyncObj	syncObj;
		 if  (  syncObj.sync(  tMutexName,  0  )  )  {
			 showInfo_open0(  0,  0,  _T(  "doVpp2 failed, sync failed"  )  );
			 goto  errLabel;
		 }
		 //
		 if  (  pVppHelpInfo->uiCnt_vpp0  !=  p->vpp.uiCnt_vpp0  )  {
			 showInfo_open0(  0,  0,  _T(  "doVpp2 failed, helpInfo.cnt_vpp0  !=  pkt.cnt_vpp0"  )  );  
			 goto  errLabel;
		 }
		 //
		 if  (  new_doVpp(  pProcInfo,  pCtx,  pSharedObj,  pCapBmp,  p,  pktLen,  2,  index  )  )  {
			 showInfo_open0(  0,  0,  _T(  "doVpp2 failed, new_doVpp failed"  )  );
			 goto  errLabel;
		 }
		 //
		 pVppHelpInfo->procFlgs.bProcessed_step2  =  TRUE;
		 pCtx->uiCnt_vpp2  ++  ;

	 }


	 iErr  =  0;	 
errLabel:
	 return  iErr;
 }



