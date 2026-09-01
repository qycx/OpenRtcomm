
#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>


#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"

//#include	"qmcVideoCapture_isCli.h"
//
#include	"qyDynLib.h"
#include	"qmcDmoPublic.h"
#include	"qmcCmdProc.h"
#include	"tmpCeLib.h"
#include	"module_qisCamCap.h"
#include	"isCmdConst.h"
#include	"qyOpenShellCommon.h"
#include	"qyCusResTemp.h"
#include	"policyAvParams.h"

#include	"qmcTaskPublic.h"

#include	"qmcCfg.h"
#include	"imgFunc_open.h"
#include	"qmcFunc.h"

 
#ifndef  __WINCE__
 LRESULT  CALLBACK  myVideoCaptureProc(  HWND  mwnd,  LPVIDEOHDR  lphdr  );
#endif
 int  exitVideoCapWnd(  MC_VAR_common  *  pProcInfo,  CAP_procInfo_video  *  pVc  );
 
 extern  QY_DMITEM  CONST_videoCompressorsTable[];






//  ÏÂÃæÕâ¸öº¯Êý£¬ÔÚÊ¹ÓÃÖÐ£¬±ÈÈç¶ÔÆÁÄ»µÄ»ñÈ¡£¬²¢²»ÄÜÈÎÒâµÄÏñËØ¾ÍµÃµ½ÏàÓ¦µÄbmp,¶øÊÇÒª×öÒ»¶¨µÄÐÞÕýºó²Å·ûºÏÊµ¼Ê¡£
//
 BITMAPINFO  *  newBitmapInfo(  UINT bits,  unsigned  int  bmWidth,  unsigned  int  bmHeight  )
{
	UINT			        wLineLen ;
	DWORD		            dwSize ;
	DWORD			        wColSize ;
	LPBITMAPINFOHEADER		lpbi ;
	LPBYTE					lpBits ;
	

	//
	// DWORD align the width of the DIB
	// Figure out the size of the colour table
	// Calculate the size of the DIB
	//
	wLineLen = (bmWidth*bits+31)/32 * 4;
	wColSize = sizeof(RGBQUAD)*((bits <= 8) ? 1<<bits : 0);
	dwSize = sizeof(BITMAPINFOHEADER) + wColSize +
		(DWORD)(UINT)wLineLen*(DWORD)(UINT)bmHeight;

	//
	// Allocate room for a DIB and set the LPBI fields
	//

	lpbi = (LPBITMAPINFOHEADER)mymalloc(  dwSize  );
	if  (  !lpbi  )  return  NULL;

	lpbi->biSize = sizeof(BITMAPINFOHEADER) ;
	lpbi->biWidth = bmWidth ;
	lpbi->biHeight = bmHeight ;
	lpbi->biPlanes = 1 ;
	lpbi->biBitCount = (WORD) bits ;
	lpbi->biCompression = BI_RGB ;
	lpbi->biSizeImage = dwSize - sizeof(BITMAPINFOHEADER) - wColSize ;
	lpbi->biXPelsPerMeter = 0 ;
	lpbi->biYPelsPerMeter = 0 ;
	lpbi->biClrUsed = (bits <= 8) ? 1<<bits : 0;
	lpbi->biClrImportant = 0 ;

	//
	// Get the bits from the bitmap and stuff them after the LPBI
	//
	lpBits = (LPBYTE)(lpbi+1)+wColSize ;

	return   (  BITMAPINFO  *  )lpbi;
}


 void  exitOrg2RgbBuf(  MC_VAR_common  *  pProcInfo,  CAP_procInfo_bmpCommon  *  pVc  )
{
	//
	if  (  pVc->hicOrg2Rgb  )  {
		ICClose(  pVc->hicOrg2Rgb  );  pVc->hicOrg2Rgb  =  NULL;
	}

#if  0
	if  (  pVc->pOrg2RgbBuf  )  {
		free(  pVc->pOrg2RgbBuf  );  pVc->pOrg2RgbBuf  =  NULL;
	}
#endif
	MACRO_safeFree(  pVc->pOrg2RgbBuf  );
	pVc->iOrg2RgbBufSize  =  0;

	pVc->bOrg2RgbBufInited  =  FALSE;
}



 int  initOrg2RgbBuf(  MC_VAR_common  *  pProcInfo,  CAP_procInfo_bmpCommon  *  pVc  )
{
	int					iErr			=	-1;
	BITMAPINFO		*	pBmpInfo		=	NULL;
	int					iFormatSize		=	0;
	DWORD				biSizeImage		=	0;

	//
	if  (  pVc->bOrg2RgbBufInited  )  return  0;

	memset(  &pVc->vh_rgb,  0,  sizeof(  pVc->vh_rgb  )  );
	//
	pVc->vh_rgb.bih.biSize  =  sizeof(  BITMAPINFOHEADER  );
	pVc->vh_rgb.bih.biCompression  =  BI_RGB;
	pVc->vh_rgb.bih.biBitCount  =  24;
	pVc->vh_rgb.bih.biPlanes  =  1;
	//
	pVc->vh_rgb.bih.biWidth  =  pVc->vh_org.bih.biWidth;
	pVc->vh_rgb.bih.biHeight  =  pVc->vh_org.bih.biHeight;
	//
	biSizeImage  =  (  pVc->vh_rgb.bih.biWidth  *  pVc->vh_rgb.bih.biBitCount  +  31  )  /  32  *  4  *  pVc->vh_rgb.bih.biHeight;
	pVc->vh_rgb.bih.biSizeImage  =  biSizeImage;

	if  (  pVc->vh_org.bih.biCompression  !=  BI_RGB  )  {

		if  (  pVc->vh_org.bih.biCompression  ==  CONST_fourcc_YUY2  )  {
			traceLog((TCHAR*)  _T(  "call yuy2rgb directly"  )  );
			}
		else  if  (  pVc->vh_org.bih.biCompression  ==  CONST_fourcc_YV12  )  {
				  traceLog((TCHAR*)  _T(  "call yv12rgb directly"  )  );
				  }
		else  if  (  pVc->vh_org.bih.biCompression  ==  CONST_fourcc_I420  )  {
			      traceLog((TCHAR*)  _T(  "call yv12rgb directly"  )  );
				  }
		else  if (pVc->vh_org.bih.biCompression == CONST_fourcc_NV12) {
			traceLog((TCHAR*)_T("call yv12rgb directly"));
		}
		else  if  (  pVc->vh_org.bih.biCompression  ==  CONST_fourcc_HDYC  )  {
				  traceLog((TCHAR*)  _T(  "call hdycrgb directly"  )  );		
				  }
		else  if  (  pVc->vh_org.bih.biCompression  ==  CONST_fourcc_v210  )  {		//  2012/02/23
				  traceLog((TCHAR*)  _T(  "call v210rgb directly"  )  );		
				  }
		else  if  (  pVc->vh_org.bih.biCompression  ==  BI_BITFIELDS  &&  pVc->vh_org.bih.biBitCount  ==  16  )  {
			      traceLog((TCHAR*)  _T(  "call rgb565ToRgb directly"  )  );
				  }
		else  if  (  pVc->vh_org.bih.biCompression  ==  CONST_fourcc_MJPG  )  {
				  traceLog((TCHAR*)  _T(  "call MJPG directly"  )  );
				  }
		else  {
			#ifndef  __WINCE__
			  if  (  !(  pVc->hicOrg2Rgb  =  ICLocate(  ICTYPE_VIDEO,  0,  &pVc->vh_org.bih,  &pVc->vh_rgb.bih,  ICMODE_DECOMPRESS  )  )  )  {
				  qyDisplayLastError(  (char*)""  );
				  //  2014/06/17
				  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initOrg2RgbBuf failed, ICLocate failed"  )  );
				  //
				  goto  errLabel;
			  }

			  ICINFO	icInfo;
			  ICGetInfo(  pVc->hicOrg2Rgb,  &icInfo,  sizeof(  icInfo  )  );
			  iFourcc2Str(  icInfo.fccHandler,  0,  0  );

			  iFormatSize  =  ICDecompressGetFormat(  pVc->hicOrg2Rgb,  &pVc->vh_org.bih,  NULL  );
			  if  (  iFormatSize  <=  0  )  goto  errLabel;
			  if  (  !(  pBmpInfo  =  (  BITMAPINFO  *  )mymalloc(  iFormatSize  )  )  )  goto  errLabel;
			  if  (  ICDecompressGetFormat(  pVc->hicOrg2Rgb,  &pVc->vh_org.bih,  pBmpInfo  )  !=  ICERR_OK  )  goto  errLabel;
			  memcpy(  &pVc->vh_rgb.bih,  pBmpInfo,  min(  sizeof(  pVc->vh_rgb.bih  ),  iFormatSize  )  );
			  //
			  if  (  ICDecompressQuery(  pVc->hicOrg2Rgb,  &pVc->vh_org.bih,  &pVc->vh_rgb.bih  )  !=  ICERR_OK  )  {
				  traceLogA(  (char*)  "ÎÞ·¨×ª³Érgb"  );  goto  errLabel;
			  }
			#else
				traceLog((TCHAR*)  _T(  "vcm is not supported in winCe"  )  );
				goto  errLabel;
			#endif
		}
		}
	else  {
		  if  (  pVc->vh_org.bih.biBitCount  !=  32  )  {
			  traceLogA(  (char*)  "initOrg2RgbBuf: not supported, biBitCount %d",  pVc->vh_org.bih.biBitCount  );
			  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initOrg2RgbBuf failed: org.biBitCount is %d"  ),  pVc->vh_org.bih.biBitCount  );
			  goto  errLabel;
		  }
	}

	//
	pVc->iOrg2RgbBufSize  =  max(  pVc->vh_rgb.bih.biSizeImage,  biSizeImage  )  +  iFormatSize  +  4096;	//  ²»ÖªµÀ¾«È·µÄÓ¦¸ÃÊÇ¶àÉÙ£¬ËùÒÔºýÅªÒ»¸öÔÚÕâÀï£®£²£°£°£¸£¯£°£³£¯£±£¹
	if  (  pVc->iOrg2RgbBufSize  <=  0  )  goto  errLabel;

	//  
	if  (  !(  pVc->pOrg2RgbBuf  =  (  char  *  )mymalloc(  pVc->iOrg2RgbBufSize  )  )  )  goto  errLabel;	
	
	pVc->bOrg2RgbBufInited  =  TRUE;

	iErr  =  0;

errLabel:

	if  (  pBmpInfo  )  {  free(  pBmpInfo  );  pBmpInfo  =  NULL;	}
	if  (  iErr  )  {
		exitOrg2RgbBuf(  pProcInfo,  pVc  );
		//
		char	buf[128]  =  "";
		iFourcc2Str(  pVc->vh_org.bih.biCompression,  buf,  mycountof(  buf  )  );
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initOrg2RgbBuf failed, fourcc %s"  ),  CQyString(  buf  )  );
	}

	return  iErr;

}


//
#if  0
 int  ii_org2Rgb(  MC_VAR_common  *  pProcInfo,  CAP_procInfo_bmpCommon  *  pVc,  BYTE  *  pInput,  char  *  pOrg2RgbBuf  )
{
	 int			iErr			=	-1;
	 if  (  !pProcInfo  )  return  -1;
	 QY_MC		*	pQyMc			=	(  QY_MC  *  )pProcInfo->pQyMc;//
	 if  (  !pQyMc  )  return  -1;
	 int			tmpiRet			=	-1;
	 //
	 BOOL			bDecompressOk	=  FALSE;

	 //
	 CUS_MODULES  *  pCusModules  =  (  CUS_MODULES  *  )pProcInfo->getCusModules(  );
	 if  (  !pCusModules  )  {
		 MACRO_qyAssert(  0,  _T(  "org2Rgb. getCusModules returns null"  )  );
		 return  -1;
	 }


	 if  (  !pVc  )  return  -1;
	 if  (  !pVc->bOrg2RgbBufInited  )  return  -1;
	 if  (  !pOrg2RgbBuf  )  {
		 #ifdef  __DEBUG__
				 traceLog((TCHAR*)  _T(  "org2Rgb failed, pOrg2RgbBuf is null"  )  );
		 #endif
		 return  -1;
	 }
	 	
	 //  2011/12/10. 这个函数应该用于不变形的转换，所以，没有倒转的需要
	 unsigned  char  ucbOutputFlippedImg  =  FALSE;

	 //
	 if  (  pVc->vh_org.bih.biCompression  ==  CONST_fourcc_YUY2  )  {
		
		 if  (  yuy2ToRgb24(  pCusModules,  pInput,  (  unsigned  char  *  )pOrg2RgbBuf,  pVc->vh_org.bih.biWidth,  pVc->vh_org.bih.biHeight,  ucbOutputFlippedImg  )  )  goto  errLabel;
		 
		 bDecompressOk  =  TRUE;
		 }
	 else  if  (  pVc->vh_org.bih.biCompression  ==  CONST_fourcc_YV12  )  {
			   if  (  pQyMc->yv12ToRgb24(  pInput,  (  unsigned  char  *  )pOrg2RgbBuf,  pVc->vh_org.bih.biWidth,  pVc->vh_org.bih.biHeight,  ucbOutputFlippedImg  )  )  goto  errLabel;			  
			   bDecompressOk  =  TRUE;
			   }
	 else  if  (  pVc->vh_org.bih.biCompression  ==  CONST_fourcc_I420  )  {
		       if  (  i420ToRgb24(  pInput,  (  unsigned  char  *  )pOrg2RgbBuf,  pVc->vh_org.bih.biWidth,  pVc->vh_org.bih.biHeight,  ucbOutputFlippedImg  )  )  goto  errLabel;			   
			   bDecompressOk  =  TRUE;
			   }
	 else  if (pVc->vh_org.bih.biCompression == CONST_fourcc_NV12) {
		 NV12_TO_RGB24((unsigned  char*)pInput, (unsigned  char*)pOrg2RgbBuf, pVc->vh_org.bih.biWidth, pVc->vh_org.bih.biHeight);
		 bDecompressOk = true;
	 }

	 else  if  (  pVc->vh_org.bih.biCompression  ==  CONST_fourcc_HDYC  )  {
		       if  (  hdycToRgb24(  pCusModules,  pInput,  (  unsigned  char  *  )pOrg2RgbBuf,  pVc->vh_org.bih.biWidth,  pVc->vh_org.bih.biHeight,  ucbOutputFlippedImg  )  )  goto  errLabel;			   
			   bDecompressOk  =  TRUE;
			   }
	 else  if  (  pVc->vh_org.bih.biCompression  ==  CONST_fourcc_v210  )  {	//  2012/02/23
		       if  (  v210ToRgb24(  pCusModules,  pInput,  (  unsigned  char  *  )pOrg2RgbBuf,  pVc->vh_org.bih.biWidth,  pVc->vh_org.bih.biHeight,  ucbOutputFlippedImg  )  )  goto  errLabel;			   
			   bDecompressOk  =  TRUE;
			   }
	 else  if  (  pVc->vh_org.bih.biCompression  ==  BI_BITFIELDS  &&  pVc->vh_org.bih.biBitCount  ==  16  )  {
			   if  (  rgb565ToRgb24(  pInput,  (  unsigned  char  *  )pOrg2RgbBuf,  pVc->vh_org.bih.biWidth,  pVc->vh_org.bih.biHeight  )  )  goto  errLabel;
			   bDecompressOk  =  TRUE;
			   }
	 else  if  (  pVc->hicOrg2Rgb  )  {
			   #ifndef  __WINCE__		
						try  {
							 tmpiRet  =  ICDecompressBegin(  pVc->hicOrg2Rgb,  &pVc->vh_org.bih,  &pVc->vh_rgb.bih  );					 			     
							}
						#ifdef  __useMfc__
						catch  (  CException  *  e  )  {
							   e->Delete(  );
							   tmpiRet  =  -1;	
							   }
						#endif
						catch  (  ...  )  {
							   tmpiRet  =  -1;
						}
						if  (  tmpiRet  !=  ICERR_OK  )  {
							traceLogA(  (char*)  "Video capture: ICDecompressBegin failed."  );
							qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Video capture: ICDecompressBegin failed"  )  );
							}
						else  {
							  try  {
								   tmpiRet  =  ICDecompress(  pVc->hicOrg2Rgb,  0,  &pVc->vh_org.bih,  pInput,  &pVc->vh_rgb.bih,  pOrg2RgbBuf  );						   
								  }
							  #ifdef  __useMfc__
							  catch  (  CException  *  e  )  {
									 e->Delete(  );					
									 tmpiRet  =  -1;
								     }
							  #endif
							  catch  (  ...  )  {
								     tmpiRet  =  -1;
							  }
							  if  (  tmpiRet  ==  ICERR_OK  )  {
								  bDecompressOk  =  TRUE;					  
								  //  pInput  =  (  BYTE  *  )pVc->pOrg2RgbBuf;
								  //  pBmpInfo_input  =  (  BITMAPINFO  *  )&pVc->vh_rgb.bih;
								  }
							  else  {
								    traceLogA(  (char*)  "Video capture: ICDecompress failed."  );
									qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Video capture: ICDecompress failed"  )  );
							  }

							  if  (  (  tmpiRet  =  ICDecompressEnd(  pVc->hicOrg2Rgb  )  )  !=  ICERR_OK  )  traceLogA(  (char*)  "ICDecompressEnd failed"  );					  
						}

			   #else
					traceLog((TCHAR*)  _T(  "vcm is not supported in winCe"  )  );
			   #endif
		 }
	 else  {
		   //
		   int  iWidth  =  pVc->vh_org.bih.biWidth;		
		   int  iHeight  =  pVc->vh_org.bih.biHeight;

		   int  widthBytes1  =  iWidth  *  4;					
		   int  widthBytes2  =  (  iWidth  *  24  +  31  )  /  32  *  4;
		   int	 i,  j;
		   int  offset1,  offset2;

		   for  (  i  =  0;  i  <  iHeight;  i  ++  )  {
			    int  m1  =  i  *  widthBytes1;				
				int  m2  =  i  *  widthBytes2;
				for  (  j  =  0;  j  <  iWidth;  j  ++  )  {
					 offset1  =  m1  +  j  *  4;				
					 offset2  =  m2  +  j  *  3;
					 (  (  BYTE  *  )pOrg2RgbBuf  )[offset2  +  0]  =  *(  (  (  BYTE  *  )pInput  )  +  offset1  +  0  );
					 (  (  BYTE  *  )pOrg2RgbBuf  )[offset2  +  1]  =  *(  (  (  BYTE  *  )pInput  )  +  offset1  +  1  );
					 (  (  BYTE  *  )pOrg2RgbBuf  )[offset2  +  2]  =  *(  (  (  BYTE  *  )pInput  )  +  offset1  +  2  );						 
				}					
		   }
				
		   //  pInput  =  (  BYTE  *  )pVc->pOrg2RgbBuf;
		   //  pBmpInfo_input  =  (  BITMAPINFO  *  )&pVc->vh_rgb.bih;

		   bDecompressOk  =  TRUE;
	 }

	 if  (  !bDecompressOk  )  {
		 traceLogA(  (char*)  "org2Rgb: Decompress failed."  );
		 goto  errLabel;
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;

}
#endif 

 
//
int  org2Rgb(MC_VAR_common* pProcInfo, CAP_procInfo_bmpCommon* pVc, BITMAPINFOHEADER bih_org,  BYTE* pInput, char* pOrg2RgbBuf)
{
	int			iErr = -1;
	if (!pProcInfo)  return  -1;
	QY_MC* pQyMc = (QY_MC*)pProcInfo->pQyMc;//
	if (!pQyMc)  return  -1;
	int			tmpiRet = -1;
	//
	BOOL			bDecompressOk = FALSE;

	//
	CUS_MODULES* pCusModules = (CUS_MODULES*)pProcInfo->getCusModules();
	if (!pCusModules) {
		MACRO_qyAssert(0, _T("org2Rgb. getCusModules returns null"));
		return  -1;
	}


	if (!pVc)  return  -1;
	if (!pVc->bOrg2RgbBufInited)  return  -1;
	if (!pOrg2RgbBuf) {
#ifdef  __DEBUG__
		traceLog((TCHAR*)_T("org2Rgb failed, pOrg2RgbBuf is null"));
#endif
		return  -1;
	}

	//  2011/12/10. 这个函数应该用于不变形的转换，所以，没有倒转的需要
	unsigned  char  ucbOutputFlippedImg = FALSE;

	//
	if (bih_org.biCompression == CONST_fourcc_YUY2) {

		if (yuy2ToRgb24(pCusModules, pInput, (unsigned  char*)pOrg2RgbBuf, bih_org.biWidth, bih_org.biHeight, ucbOutputFlippedImg))  goto  errLabel;

		bDecompressOk = TRUE;
	}
	else  if (bih_org.biCompression == CONST_fourcc_YV12) {
		if (pQyMc->yv12ToRgb24(pInput, (unsigned  char*)pOrg2RgbBuf, bih_org.biWidth, bih_org.biHeight, ucbOutputFlippedImg))  goto  errLabel;
		bDecompressOk = TRUE;
	}
	else  if (bih_org.biCompression == CONST_fourcc_I420) {
		if (i420ToRgb24(pInput, (unsigned  char*)pOrg2RgbBuf, bih_org.biWidth, bih_org.biHeight, ucbOutputFlippedImg))  goto  errLabel;
		bDecompressOk = TRUE;
	}
	else  if (bih_org.biCompression == CONST_fourcc_NV12) {
		nv12ToRgb24((unsigned  char*)pInput, (unsigned  char*)pOrg2RgbBuf, bih_org.biWidth, bih_org.biHeight,ucbOutputFlippedImg);
		bDecompressOk = true;
	}

	else  if (bih_org.biCompression == CONST_fourcc_HDYC) {
		if (hdycToRgb24(pCusModules, pInput, (unsigned  char*)pOrg2RgbBuf, bih_org.biWidth, bih_org.biHeight, ucbOutputFlippedImg))  goto  errLabel;
		bDecompressOk = TRUE;
	}
	else  if (bih_org.biCompression == CONST_fourcc_v210) {	//  2012/02/23
		if (v210ToRgb24(pCusModules, pInput, (unsigned  char*)pOrg2RgbBuf, bih_org.biWidth, bih_org.biHeight, ucbOutputFlippedImg))  goto  errLabel;
		bDecompressOk = TRUE;
	}
	else  if (bih_org.biCompression == BI_BITFIELDS && bih_org.biBitCount == 16) {
		if (rgb565ToRgb24(pInput, (unsigned  char*)pOrg2RgbBuf, bih_org.biWidth, bih_org.biHeight))  goto  errLabel;
		bDecompressOk = TRUE;
	}
	else  if (pVc->hicOrg2Rgb) {
#ifndef  __WINCE__		
		try {
			tmpiRet = ICDecompressBegin(pVc->hicOrg2Rgb, &bih_org, &pVc->vh_rgb.bih);
		}
#ifdef  __useMfc__
		catch (CException* e) {
			e->Delete();
			tmpiRet = -1;
		}
#endif
		catch (...) {
			tmpiRet = -1;
		}
		if (tmpiRet != ICERR_OK) {
			traceLogA((char*)"Video capture: ICDecompressBegin failed.");
			qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("Video capture: ICDecompressBegin failed"));
		}
		else {
			try {
				tmpiRet = ICDecompress(pVc->hicOrg2Rgb, 0, &bih_org, pInput, &pVc->vh_rgb.bih, pOrg2RgbBuf);
			}
#ifdef  __useMfc__
			catch (CException* e) {
				e->Delete();
				tmpiRet = -1;
			}
#endif
			catch (...) {
				tmpiRet = -1;
			}
			if (tmpiRet == ICERR_OK) {
				bDecompressOk = TRUE;
				//  pInput  =  (  BYTE  *  )pVc->pOrg2RgbBuf;
				//  pBmpInfo_input  =  (  BITMAPINFO  *  )&pVc->vh_rgb.bih;
			}
			else {
				traceLogA((char*)"Video capture: ICDecompress failed.");
				qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("Video capture: ICDecompress failed"));
			}

			if ((tmpiRet = ICDecompressEnd(pVc->hicOrg2Rgb)) != ICERR_OK)  traceLogA((char*)"ICDecompressEnd failed");
		}

#else
		traceLog((TCHAR*)_T("vcm is not supported in winCe"));
#endif
	}
	else {
		//
		int  iWidth = bih_org.biWidth;
		int  iHeight = bih_org.biHeight;

		int  widthBytes1 = iWidth * 4;
		int  widthBytes2 = (iWidth * 24 + 31) / 32 * 4;
		int	 i, j;
		int  offset1, offset2;

		for (i = 0; i < iHeight; i++) {
			int  m1 = i * widthBytes1;
			int  m2 = i * widthBytes2;
			for (j = 0; j < iWidth; j++) {
				offset1 = m1 + j * 4;
				offset2 = m2 + j * 3;
				((BYTE*)pOrg2RgbBuf)[offset2 + 0] = *(((BYTE*)pInput) + offset1 + 0);
				((BYTE*)pOrg2RgbBuf)[offset2 + 1] = *(((BYTE*)pInput) + offset1 + 1);
				((BYTE*)pOrg2RgbBuf)[offset2 + 2] = *(((BYTE*)pInput) + offset1 + 2);
			}
		}

		//  pInput  =  (  BYTE  *  )pVc->pOrg2RgbBuf;
		//  pBmpInfo_input  =  (  BITMAPINFO  *  )&pVc->vh_rgb.bih;

		bDecompressOk = TRUE;
	}

	if (!bDecompressOk) {
		traceLogA((char*)"org2Rgb: Decompress failed.");
		goto  errLabel;
	}

	iErr = 0;
errLabel:
	return  iErr;

}





#if  0
 int  rotateRgb2Pic(  MC_VAR_common  *  pProcInfo,  CAP_procInfo_video  *  pVc,  BYTE  *  pInput,  char  *  pPicBuf  )
{
	int					iErr	=	-1;
	int					i,  j;
	QY_VIDEO_HEADER	*	pVh_rgb	=	pVc->bOrg2RgbBufInited  ?  &pVc->vh_rgb  :  &pVc->vh_org;
	int					lineBytes_pic,  lineBytes_rgb;

	if  (  !pPicBuf  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "rotateRgb2Pic failed, pPicBuf is null"  )  );
		#endif
		return  -1;
	}

	lineBytes_pic  =  (  pVc->vh_pic.bih.biWidth  *  24  +  31  )  /  32  *  4;
	lineBytes_rgb  =  (  pVh_rgb->bih.biWidth  *  24  +  31  )  /  32  *  4;

	switch  (  pVc->policy.degreesToRotate  )  {
			case  90:
					 for  (  i  =  0;  i  <  pVh_rgb->bih.biWidth;  i  ++  )  {
						  for  (  j  =  0;  j  <  pVh_rgb->bih.biHeight;  j  ++  )  {							  					
							   memcpy(  &pPicBuf[i  *  lineBytes_pic  + (  pVc->vh_pic.bih.biWidth  -  j  -  1  )  *  3],  &pInput[j  *  lineBytes_rgb  +  i  *  3],  3  );						 						 
						  }				  
					 }
					 break;
			case  270:
					 for  (  i  =  0;  i  <  pVh_rgb->bih.biWidth;  i  ++  )  {
						  for  (  j  =  0;  j  <  pVh_rgb->bih.biHeight;  j  ++  )  {
							   memcpy(  &pPicBuf[(  pVc->vh_pic.bih.biHeight  -  i  -  1  )  *  lineBytes_pic  + j  *  3],  &pInput[j  *  lineBytes_rgb  +  i  *  3],  3  );						 						 							   
						  }
					 }
					 break;
			case  180:
					 for  (  i  =  0;  i  <  pVh_rgb->bih.biWidth;  i  ++  )  {
						  for  (  j  =  0;  j  <  pVh_rgb->bih.biHeight;  j  ++  )  {
							   memcpy(  &pPicBuf[(  pVc->vh_pic.bih.biHeight  -  j  -  1  )  *  lineBytes_pic  + i  *  3],  &pInput[j  *  lineBytes_rgb  +  i  *  3],  3  );						 						 							   
						  }
					 }
				     break;
			case  0:
					memcpy(  pPicBuf,  pInput,  pVc->vh_pic.bih.biSizeImage  );
					break;
			default:
					traceLog((TCHAR*)  _T(  "rgb2Pic failed. degrees error"  )  );
					goto  errLabel;
	}



	//
	iErr   =  0;
errLabel:
	return  iErr;
}
#endif


  BOOL  bGetCapturePara_vfw(  MC_VAR_common  *  pProcInfo,  unsigned  int  uiCapType,  CAP_procInfo_video  *  pVc  )
{
#ifdef  __WINCE__
		return  FALSE;
#else

	BOOL					bRet		=	FALSE;
	CAPTUREPARMS			CapParms	=	{  0  };	
	
	capCaptureGetSetup(  pVc->capDev.vfw.hCapWnd,  &CapParms,  sizeof(  CapParms  )  );

	CapParms.fAbortLeftMouse = FALSE;
	CapParms.fAbortRightMouse = FALSE;
	CapParms.fYield = TRUE;
	CapParms.fCaptureAudio = FALSE;
	CapParms.wPercentDropForError = 50;

	if  (  capCaptureSetSetup(  pVc->capDev.vfw.hCapWnd,  &CapParms,  sizeof(  CapParms  )  )  ==  FALSE  )  {
		traceLogA(  (char*)  "\n Failed to set the capture parameters "  );
		goto  errLabel;
	}


	capGetVideoFormat(  pVc->capDev.vfw.hCapWnd,  &pVc->vh_org.bih,  sizeof(  pVc->vh_org.bih  )  );

	/*
	// Set Video Format 

	pProcInfo->av.bmpInfo_org.bmiHeader.biWidth  =  IMAGE_WIDTH;
	pProcInfo->av.bmpInfo_org.bmiHeader.biHeight  =  IMAGE_HEIGHT;

	BOOL ret;
	ret  =  capSetVideoFormat(  pProcInfo->av.hCapWnd,  &pProcInfo->av.bmpInfo_org,  sizeof(  pProcInfo->av.bmpInfo_org  )  );

	if  (  ret  ==  TRUE  )  traceLogA(  (char*)  "Video parameters set properly"  );

	//  ÔÙÈ¡Ò»±é,ÒÔ·ÀÖ¹ÉÏÃæµÄsetÊ§°Ü
	capGetVideoFormat(  pProcInfo->av.hCapWnd,  &pProcInfo->av.bmpInfo_org,  sizeof(  pProcInfo->av.bmpInfo_org  )  );
	*/

	//

	bRet  =  TRUE;
errLabel:
	return  bRet;

#endif
}



//
 int  startCapture(  MC_VAR_common  *  pProcInfo,  CAP_procInfo_video  *  pVc  )
{
	int				iErr	=	-1;

	if  (  !pProcInfo  )  return  -1;
	QY_MC  *  pQyMc  =  (  QY_MC  *  )pProcInfo->pQyMc;
	if  (  !pQyMc  )  return  -1;

#if  0
	CQySyncObj		syncObj;

	if  (  syncObj.sync(  pProcInfo->cfg.mutexName_syncAv  )  )  {
		traceLogA(  (char*)  "bStartCapture sync faile.d"  );  goto  errLabel;
	}
#endif

	if  (  !pVc->bCapDevConnected  )  goto  errLabel;

	if  (  pVc->bCaptureStarted  )  {		//  ÒÑ¾­Æô¶¯ÁË
		iErr  =  0;  goto  errLabel;
	}

	switch  (  pVc->uiCamCapType  )  {
			case  CONST_camCapType_vfw:
				  //  Start live capturing ...
				  if  (  capCaptureSequenceNoFile(  pVc->capDev.vfw.hCapWnd  )==FALSE)  {
					  #ifdef  __DEBUG__
							  traceLogA(  (char*)  " Failed to capture Sequence .."  );
					  #endif
					  goto  errLabel;
				  }
				  break;
			case  CONST_camCapType_directX:
				  if  (  startCapture_dx(  pVc->capDev.pVideoCapDev  )  )  goto  errLabel;
				  break;
			case  CONST_camCapType_rtsp:  // 2014/02/23 
				  if  (  startCapture_rtsp(  pVc->capDev.pVideoCapDev  )  )  goto  errLabel;
				  break;
			case  CONST_camCapType_custom:  {
				  MODULE_camCap	*	pModule	=	(  MODULE_camCap  *  )getCusModule(  &pQyMc->cusModules,  CONST_moduleType_camCap  );
				  if  (  !pModule  )  goto  errLabel;
				  if  (  pModule->pf_startCapture(  pVc->capDev.pVideoCapDev  )  )  goto  errLabel;
				  }
				  break;
			default:
					goto  errLabel;
	}
	pVc->bCaptureStarted  =  TRUE;
	pVc->dwTickCnt_captureStarted  =  GetTickCount(  );  //  2017/09/19
	
	//  2017/09/17
	switch  (  pVc->uiCamCapType  )  {
			case  CONST_camCapType_directX:
				  pVc->bCaptureStarted_openLocalVideo  =  TRUE;
				  break;
			default:
					break;
	}

	//
	iErr  =  0;
errLabel:
	return  iErr;

}
  

 //
 int  stopCapture(  MC_VAR_common  *  pProcInfo,  CAP_procInfo_video  *  pVc  )
{
	int				iErr		=	-1;

	if  (  !pProcInfo  )  return  -1;
	QY_MC  *  pQyMc  =  (  QY_MC  *  )pProcInfo->pQyMc;
	if  (  !pQyMc  )  return  -1;


#ifdef  __DEBUG__
	traceLogA(  (char*)  "stopCapture enters"  );
#endif
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "stopCapture enters"  )  );


	if  (  pVc->bCaptureStarted  )  {

		switch  (  pVc->uiCamCapType  )  {
				case  CONST_camCapType_vfw:
					  capCaptureStop(  pVc->capDev.vfw.hCapWnd  );
					  capCaptureAbort(  pVc->capDev.vfw.hCapWnd  );
					  Sleep(  800  );	
					  break;
				case  CONST_camCapType_directX:					  
					  stopCapture_dx(  pVc->capDev.pVideoCapDev  );
					  break;

					  //  2014/02/23
				case  CONST_camCapType_rtsp:
					  stopCapture_rtsp(  pVc->capDev.pVideoCapDev  );
					  break;

				case  CONST_camCapType_custom:  {
					  MODULE_camCap	*	pModule	=	(  MODULE_camCap  *  )getCusModule(  &pQyMc->cusModules,  CONST_moduleType_camCap  );
					  if  (  !pModule  )  goto  errLabel;
					  pModule->pf_stopCapture(  pVc->capDev.pVideoCapDev  );
					  }
					  break;
				default:
						goto  errLabel;
		}

		pVc->bCaptureStarted  =  FALSE;

	}

	iErr  =  0;

errLabel:

#ifdef  __DEBUG__
	traceLogA(  (char*)  "stopCapture leaves"  );
#endif
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "stopCapture leaves"  )  );


	return  iErr;
}


 //  2015/05/18
 int  runSharedMediaObj(  MC_VAR_common  *  pProcInfo,  QY_SHARED_OBJ  *  pSharedObj  )
{
	int  iErr  =  -1;

	switch  (  pSharedObj->uiType1  )  {
			case  CONST_sharedObjType_webcam_av:
				  //
#ifdef  __DEBUG__
				  if  (  pSharedObj->bCapDev  )  {
					  int  iIndex_capBmp  =  pSharedObj->iIndex_capBmp;
	
					  CAP_procInfo_video  *  pCapBmp  =  NULL;
					  //
#ifdef  __DEBUG__
					  traceLog((TCHAR*)  _T(  "Note: not finished, CAP_procInfo_video should be changed to CAP_procInfo_bmp"  )  );
#endif

					  //
					  pCapBmp  =  (  CAP_procInfo_video  *  )getCapBmpBySth(  pProcInfo,  iIndex_capBmp,  0  );	
					  if  (  !pCapBmp  )  goto  errLabel;

					  //
					  if  (  pCapBmp->bCapDevConnected  )  {
						  startCapture(  pProcInfo,  pCapBmp  );  	
					  }
					  }
				  else
#endif
				  {
					    if  (  runShareMediaDevice(  pSharedObj->pShareMediaObj  )  )  {					  
							goto  errLabel;				  
						}
				  }
				  break;
			case  CONST_sharedObjType_ic:
				  if (runShareIc(pSharedObj->pIcObj)) {
					  goto  errLabel;
				  }
				  break;
			default:  {
					  int  iIndex_capBmp  =  pSharedObj->iIndex_capBmp;
	
					  CAP_procInfo_video  *  pCapBmp  =  NULL;
					  //
#ifdef  __DEBUG__
					  traceLog((TCHAR*)  _T(  "Note: not finished, CAP_procInfo_video should be changed to CAP_procInfo_bmp"  )  );
#endif

					  //
					  pCapBmp  =  (  CAP_procInfo_video  *  )getCapBmpBySth(  pProcInfo,  iIndex_capBmp,  0  );	
					  if  (  !pCapBmp  )  goto  errLabel;

					  //
					  if  (  pCapBmp->bCapDevConnected  )  {
						  startCapture(  pProcInfo,  pCapBmp  );  	
					  }
					}
					break;
	}

	iErr  =  0;
errLabel:

	return  iErr;
}


 int  exitSharedMediaObj(  MC_VAR_common  *  pProcInfo,  QY_SHARED_OBJ  *  pSharedObj  )
{
	int		iErr	=	-1;
	
	switch  (  pSharedObj->uiType1  )  {
			case  CONST_sharedObjType_webcam_av:
				  if  (  exitShareMediaDevice(  &pSharedObj->pShareMediaObj  )  )  {
					  goto  errLabel;
				  }
				  break;
			default:  {
				    MACRO_qyAssert(  0,  _T(  "exitSharedObj: unprocessed sharedObjType"  )  );
					goto  errLabel;
					}
					break;
	}


	iErr  =  0;
errLabel:
	return  iErr;
}


 //
 
//
#ifndef  __WINCE__
 LRESULT  CALLBACK  myVideoCaptureProc(  HWND  mwnd,  LPVIDEOHDR  lphdr  )
{
	//MC_VAR_isCli			*	pProcInfo			=	(  MC_VAR_isCli  *  )capGetUserData(mwnd);
	int						tmpiRet				=	0;
	TCHAR					tBuf[255  +  1]		=	_T(  ""  );
   
	//  OutputDebugString(  _T(  "myCaptureVideo enters\n"  )  );
#if  0	//  2014/04/19
	if  (  !lphdr  ||  !lphdr->lpData  )  goto  errLabel;

	//  if(vidcap!=NULL )  ((CVideoNetDlg*) (vidcap->dlg))->SendVideo(lphdr->lpData,lphdr->dwBytesUsed);

	#if  0
		 doVideoCapture(  pProcInfo,  CONST_capType_av,  0,  timeGetTime(  ),  lphdr->lpData,  lphdr->dwBytesUsed  );
	#endif

		 {
				  CQyMalloc						mallocObj_pkt;
				  CQyMalloc						mallocObj;
				  CAP_procInfo_video		*	pVc;
				  QY_SHARED_OBJ				*	pSharedObj;
				  COMPRESS_VIDEO			*	pCompressVideo;		
				  int							iIndex_capProcInfo	=	0;

				  pVc				=	(  CAP_procInfo_video  *  )getCapBmpBySth(  pProcInfo,  iIndex_capProcInfo,  0  );
				  if  (  !pVc  )  goto  errLabel;
				  pSharedObj			=	getSharedObjByIndex(  pProcInfo,  pVc->iIndex_sharedObj  );		//  ÕâÀïÒªÓÃindexÀ´»ñÈ¡
				  if  (  !pSharedObj  )  goto  errLabel;

				  SHARED_OBJ_USR	*	pSharedObjUsr	=	getSharedObjUsr(  pSharedObj,  pSharedObj->iIndex_curUsr  );
				  if  (  !pSharedObjUsr  )  goto  errLabel;

				  pCompressVideo  =  &pVc->compressVideo;
				  if  (  !pCompressVideo  )  goto  errLabel;

				  #ifdef  __DEBUG__
						  //  traceLogA(  (char*)  "Grab: video data, len %d, SampleTime %d",  BufferLen, iSampleTimeInMs  );
				  #endif


				  if  (  pCompressVideo->bVideoCompressInited  &&  pCompressVideo->u.vcm.hicLocal  )  {
					  BYTE				*	pInput						=	lphdr->lpData;
					  BITMAPINFO		*	pBmpInfo_input				=	(  BITMAPINFO  *  )&pVc->vh_org.bih;
			
					  //
				      #ifdef  __DEBUG__
							  //  iFourcc2Str(  pProcInfo->av.bmpInfo_org.bmiHeader.biCompression,  0,  0  );
							  //  iFourcc2Str(  pProcInfo->av.bmpInfo_compress.bmiHeader.biCompression,  0,  0  );
					  #endif	
					  //
					  //		
					  if  (  pVc->bOrg2RgbBufInited  )  {
						  if  (  org2Rgb(  (  MC_VAR_common  *  )pProcInfo,  (  CAP_procInfo_bmpCommon  *  )pVc,  pInput,  pVc->pOrg2RgbBuf  )  )  {			
							  traceLogA(  (char*)  "Video capture: org2Rgb failed."  );
							  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Video capture: Decompress failed"  )  );
							  goto  errLabel;
						  }
						  pInput  =  (  BYTE  *  )pVc->pOrg2RgbBuf;
						  pBmpInfo_input  =  (  BITMAPINFO  *  )&pVc->vh_rgb.bih;			
						  //  traceLogA(  (char*)  "doVideoCapture: bmp.sizeImage %d",  pVc->bmpInfo_rgb.bmiHeader.biSizeImage  );
					  }
					#if  0
					  if  (  pVc->pPicBuf  )  {
						  if  (  rgb2Pic(  (  MC_VAR_common  *  )pProcInfo,  pVc,  pInput  )  )  {
							  traceLogA(  (char*)  "Video capture: rgb2Pic failed"  );
							  goto  errLabel;
						  }
						  pInput  =  (  BYTE  *  )pVc->pPicBuf;
						  pBmpInfo_input  =  (  BITMAPINFO  *  )&pVc->vh_pic;
					  }
					#endif

					  //
					  int  iSampleTimeInMs  =  timeGetTime(  );

					  //
					  CAP_procInfo_video	*	pCapProcInfo	=	pVc;
					  myDRAW_VIDEO_DATA		*	p;
					  int						len;

					  if  (  pBmpInfo_input->bmiHeader.biCompression  !=  BI_RGB  )  {
						  traceLogA(  (char*)  "CMySampleGrabberCB::BufferCB failed: pBmpInfo_input is not rgb"  );
						  goto  errLabel;
					  }
					  if  (  pBmpInfo_input->bmiHeader.biSizeImage  !=  pCompressVideo->vh_decompress.bih.biSizeImage  )  {
						  traceLogA(  (char*)  "CMySampleGrabberCB::BufferCB failed: pBmpInfo_input->bih.biSizeImage %d != vh_decompress. %d",  pBmpInfo_input->bmiHeader.biSizeImage,  pCompressVideo->vh_decompress.bih.biSizeImage  );
						  goto  errLabel;
					  }
					
					  if  (  pBmpInfo_input->bmiHeader.biSizeImage  >  pProcInfo->cfg.uiBufSize_myDrawVideoData  )  {
						  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "BufferCB failed: biSizeImage %d is too big"  ),  pBmpInfo_input->bmiHeader.biSizeImage  );
						  goto  errLabel;
					  }
					  //  
					  len  =  sizeof(  myDRAW_VIDEO_DATA  );
					  p  =  (  myDRAW_VIDEO_DATA  *  )mallocObj_pkt.mallocf(  len  );
					  if  (  !p  )  goto  errLabel;
					  memset(  p,  0,  len  );
					  p->head.uiLen  =  pCompressVideo->vh_decompress.bih.biSizeImage;
					  p->head.uiSampleTimeInMs  =  iSampleTimeInMs;
					  //  
					#if  0
					  p->pBuf  =  mallocObj.malloc(  p->head.uiLen  );
					  if  (  !p->pBuf  )  goto  errLabel;
					#else
					  if  (  !mallocObj.mallocf(  p->head.uiLen  )  )  goto  errLabel;
					  if  (  mallocObj.get(  &p->memory  )  )  goto  errLabel;
					#endif
					  memcpy(  p->memory.m_pBuf,  pInput,  p->head.uiLen  );

					  //  2011/12/05
					  memcpy(  &p->bih,  pBmpInfo_input,  sizeof(  p->bih  )  );


					  {
						  CQyMalloc		mallocObj_pMsgBuf;
						  MIS_MSGU	*	pMsgBuf  =  (  MIS_MSGU  *  )mallocObj_pMsgBuf.mallocf(  sizeof(  MIS_MSGU  )  );
						  if  (  pMsgBuf  )  {
							  toShareBmp(  pProcInfo,  pCapProcInfo->uiType,  pSharedObj->iIndex_capBmp,  p,  1,  &pCapProcInfo->compressVideo,  pSharedObj,  pMsgBuf  );				  
						  }
					  }

					  BOOL		bPktRedirected  =  FALSE;
					  //  drawLocalVideoData(  pProcInfo,  pSharedObjUsr->uiTranNo_openAvDev_v,  (  BITMAPINFO  *  )&pCapProcInfo->compressVideo.vh_decompress.bih,  p,  len,  &bPktRedirected,  pCapProcInfo->uiType,  pSharedObj->iIndex_capBmp,  pSharedObjUsr->iTaskId  );							
					  drawLocalVideoData(  pProcInfo,  pSharedObjUsr->uiTranNo_openAvDev_v,  p,  len,  &bPktRedirected,  pCapProcInfo->uiType,  pSharedObj->iIndex_capBmp,  pSharedObjUsr->iTaskId  );							
					  if  (  bPktRedirected  )  {
						  mallocObj.detach(    );
					  }

				  }
				  

	}

	#ifdef  __DEBUG__
			if  (  0  )  {
				OutputDebugString(  _T(  "ÑÏÖØ¾¯¸æ: Test,  ÎªÁË·½±ãµ÷ÊÔ£¬ÏÈ½µµÍÆµÂÊ¡£ÕýÊ½ Debug Ê±ÒªÈ¡Ïû¡£\n"  )  );
			    Sleep(  2000  );
			}
	#endif

#endif

errLabel:	
	return  TRUE;

}
#endif


 //
 int  initVideoCapWnd(  MC_VAR_common  *  pProcInfo,  CAP_procInfo_video  *  pVc  )
{
#ifdef  __WINCE__
		return  -1;
#else
	int			iErr		=		-1;

	traceLogA(  (char*)  "initVideoCapture enters"  );

	if  (  pVc->capDev.vfw.bCapWndInited  )  return  0;

	//  
	pVc->capDev.vfw.hCapWnd  =  capCreateCaptureWindow(  _T(  "Capture"  ),  WS_POPUP,  0,  0,  1,  1,  0,  0  );
	if  (  pVc->capDev.vfw.hCapWnd  ==  NULL  )  {
		traceLogA(  (char*)  "\n Unable to create capture window"  );
		goto  errLabel;
	}

	//  connect callback functions
	capSetUserData(  pVc->capDev.vfw.hCapWnd,  pProcInfo  );


	//  Change destroy functions also........
	if  (  !capSetCallbackOnVideoStream(  pVc->capDev.vfw.hCapWnd,  myVideoCaptureProc  )  )  goto  errLabel;
	
	pVc->capDev.vfw.bCapWndInited  =  TRUE;

	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		exitVideoCapWnd(  pProcInfo,  pVc  );
	}
	traceLogA(  (char*)  "initVideoCapture leaves with %s",  iErr  ?  "failed"  :  "OK"  );
	return  iErr;
#endif
}

 int  exitVideoCapWnd(  MC_VAR_common  *  pProcInfo,  CAP_procInfo_video  *  pVc  )
{
	traceLogA(  (char*)  "exitVideoCapture enters"  );
	
	if  (  pVc->bCapDevConnected  )  {
		traceLogA(  (char*)  "exitVideoCapture failed. still connected."  );
		return  -1;
	}
	
	if  (  IsWindow(  pVc->capDev.vfw.hCapWnd  )  )  {

		// Stop the capturing process    
		capCaptureAbort(  pVc->capDev.vfw.hCapWnd  );
          
		// Disable the callback function..
		capSetCallbackOnVideoStream(  pVc->capDev.vfw.hCapWnd,  NULL  );
     
		traceLogA(  (char*)  "exitVideoCapture, will Sleep(  800  ), ÐèÒªµÈ´ýÊÓÆµÏß³ÌÍêÈ«ÍË³ö¡£"  );
		Sleep(  800  );		// This delay is important...	//  ×ÜÊÇÃ»ÍË³ö¸É¾»£¬ÈÃÊÓÆµÉè±¸ÔÚ³ÌÐòÍË³öºóÈÔÈ»±»Õ¼ÓÃ¡£ËùÒÔ½«Ê±¼äÅª³¤Ò»µã 
	
		//  SendMessage(  pProcInfo->av.hCapWnd,  WM_CLOSE,  0,  0  );
		DestroyWindow(  pVc->capDev.vfw.hCapWnd  );
	}
	pVc->capDev.vfw.hCapWnd  =  NULL;
	
	pVc->capDev.vfw.bCapWndInited  =  FALSE;

	traceLogA(  (char*)  "exitVideoCapture leaves"  );

	return  0;
}






 //  
 int  openLocalVideo(  MC_VAR_common  *  pProcInfoCommon,  unsigned  int  uiCamCapType,  LPCTSTR  displayName,  void  **ppCapStuff,  VIDEO_COMPRESSOR_CFG  *  pVideoCompressorParam,  int  iIndex_sharedObj  )
{
	int								iErr				=		-1;
	QY_MC					*		pQyMc				=		(  QY_MC  *  )pProcInfoCommon->pQyMc;
	PolicyAvParams			*		pAvParams			=		(  PolicyAvParams  *  )pProcInfoCommon->getPolicyAvParams(  );  //  QY_GET_PolicyAvParams(  );
	if  (  !pAvParams  )  return  -1;

	int								usCapDriverIndex	=		0;
	TCHAR							devName[100]		=		_T(  ""  );
	TCHAR							devVersion[100]		=		_T(  ""  );
	//  
	int								iIndex_capBmp		=		-1;
	unsigned  int					uiTranNo_sharedObj	=		0;
	//
	IMoniker				*		pMoniker			=		NULL;
	TCHAR							friendlyName[256]	=		_T(  ""  );

	TCHAR							tBuf[128]			=  _T(  ""  );

	//  2014/09/10
	//
#if !defined(  __WINCE__  )  ||  defined(  __TEST__  )
		  //  enumAvDevices(  NULL,  NULL,  devicePath,  &pMoniker  );	
		 if  (  getMonikerByDisplayName(  displayName,  (  void  **  )&pMoniker  )
			 ||  !pMoniker  )  
		 {
			 #ifdef  __DEBUG__
					 traceLogA(  (char*)  "openLocalVideo failed:  pMoniker null"  );
			 #endif
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "openLocalVideo failed, pMoniker null"  )  );
			 return  -1;
		 }

		 //  2012/02/22
		 getMonikerFriendlyName(  pMoniker,  friendlyName,  mycountof(  friendlyName  )  );
#endif

		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "start to openLocalVideo: %s"  ),  friendlyName  );
		 showInfo_open0(  0,  0,  tBuf  );
#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "openLocalVideo enters [%s]"  ),  displayName  ?  displayName  :  _T(  ""  )  );
#endif

	
		if  (  !pProcInfoCommon  )  return  -1;
		MC_VAR_common	*	pProcInfo	=	(  MC_VAR_common  *  )pProcInfoCommon;
		QY_SHARED_OBJ			*		pSharedObj			=		NULL;
		CAP_procInfo_video  *  pVc  =  NULL;


		pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
		if  (  !pSharedObj  )  goto  errLabel;
		pSharedObj->bCapDev  =  TRUE;

		int	iIndex_sharedObj_used; iIndex_sharedObj_used = -1;
		if  (  pProcInfo->bWebcamUsing(  0,  pMoniker,  NULL,  NULL,  &iIndex_sharedObj_used  )
			&&  iIndex_sharedObj_used  !=  iIndex_sharedObj  )  
		{
			#ifdef  __DEBUG__
					traceLogA(  (char*)  "openLocalVideo failed. webcam is already used."  );
			#endif

			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Failed: webcam is used"  )  );
			showNotification(  NULL,  NULL,  NULL,  0,  0,  0,  tBuf  );

			goto  errLabel;
		}
	
		//
		iIndex_capBmp  =  pSharedObj->iIndex_capBmp;
		uiTranNo_sharedObj  =  pSharedObj->uiTranNo;		//  2011/05/31

		//
		pVc  =  (  CAP_procInfo_video  *  )getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
		if  (  !pVc  )  goto  errLabel;
		

	if  (  pVc->bCapDevConnected  )  {
		#ifdef  __DEBUG__
				traceLogA(  (char*)  "openAv: capDriver already is connected"  );
		#endif
		goto  errLabel;
	}

	//
	pVc->uiType  =  CONST_capType_av;
	pVc->iIndex_sharedObj  =  iIndex_sharedObj;
	pVc->uiCamCapType  =  uiCamCapType;

	//  2017/09/13
	safeTcsnCpy(   displayName,  pVc->displayName,  mycountof(  pVc->displayName  )  );
	pVc->bCaptureStarted_openLocalVideo  =  FALSE;

	//  2014/09/10
	VIDEO_COMPRESSOR_CFG* pVideoCompressor; pVideoCompressor = pVideoCompressorParam;

	//  if  (  !pVc->policy.bih.biWidth  ||  !pVc->policy.bih.biHeight  )  
	{
		refreshWebCamSettings(  pVideoCompressor,  pVc  );
	}

	switch  (  uiCamCapType  )  {
			case  CONST_camCapType_vfw:
				  if  (  initVideoCapWnd(  pProcInfoCommon,  pVc  )  )  goto  errLabel;

				  capGetDriverDescription(  usCapDriverIndex, devName, mycountof(  devName  ),  devVersion,  mycountof(  devVersion  )  );
				  #ifdef  __DEBUG__
						  traceLogA(  (char*)  "Driver name = %S version = %S ",  devName,  devVersion  );
				  #endif
	
				  // Connect to webcam driver
				  if  ( ! capDriverConnect(  pVc->capDev.vfw.hCapWnd,  usCapDriverIndex  )  )  {
					  #ifdef  __DEBUG__
							  traceLogA(  (char*)  "Unable to open Video Capture Device, unable to connect driver to the window");
					  #endif
					  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Unable to connect to capture driver, usCapDriverIndex is %d"  ),  usCapDriverIndex  );
					  goto  errLabel;
				  }
				  pVc->capDev.vfw.usCapDriverIndex  =  usCapDriverIndex;
				  pVc->bCapDevConnected  =  TRUE;

				  //
				  // Ensure everything was initialized
				  CAPDRIVERCAPS  capDc;
				  if  (  !capDriverGetCaps(  pVc->capDev.vfw.hCapWnd,  &capDc,  sizeof(  capDc  )  )  )  goto  errLabel;
				  if  (  !capDc.fCaptureInitialized  ) goto  errLabel;
	
				  // Set the capture parameters
				  if  (  !bGetCapturePara_vfw(  pProcInfoCommon,  pVc->uiType,  pVc  )  )  {
					  #ifdef  __DEBUG__
							  traceLogA(  (char*)  "\n Setting capture parameters failed"  );
					  #endif
					  goto  errLabel;
				  }

				  break;
			case  CONST_camCapType_directX:

				  if  (  initVideoCapDev_dx(  NULL,  displayName,  ppCapStuff,  &pVc->policy.bih,  FALSE,  pQyMc->gui.hMainWnd,  iIndex_sharedObj,  &pVc->capDev.pVideoCapDev  )  )  goto  errLabel;
				  pVc->bCapDevConnected  =  TRUE;
	
				  if  (  !bGetCapturePara_dx(  pProcInfoCommon,  iIndex_capBmp,  BufferCB_av,  sizeof(  MIS_MSGU  ),  pVc->capDev.pVideoCapDev,  &pVc->vh_org  )  )  goto  errLabel;

				  break;
			case  CONST_camCapType_custom:  {
				  MODULE_camCap	*	pModule	=	(  MODULE_camCap  *  )getCusModule(  &pQyMc->cusModules,  CONST_moduleType_camCap  );
				  if  (  !pModule
					  ||  !pModule->pf_initVideoCapDev
					  ||  !pModule->pf_exitVideoCapDev
					  ||  !pModule->pf_bGetCapturePara
					  ||  !pModule->pf_startCapture
					  ||  !pModule->pf_stopCapture  )  
				  {
					  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "openLocalVideo failed, pModule or sth is null"  )  );
					  goto  errLabel;
				  }

				  //  2011/05/30
				  //
				  if  (  pModule->pf_initVideoCapDev(  NULL,  displayName,  &pVc->policy.bih,  FALSE,  0,  &pVc->capDev.pVideoCapDev  )  )  goto  errLabel;
				  pVc->bCapDevConnected  =  TRUE;

				  if  (  !pModule->pf_bGetCapturePara(  pProcInfoCommon,  iIndex_capBmp,  BufferCB_av,  sizeof(  MIS_MSGU  ),  sizeof(  myDRAW_VIDEO_DATA  ),  pVc->capDev.pVideoCapDev,  &pVc->vh_org  )  )  goto  errLabel;

				  }				  
				  break;
			default:
					#ifdef  __DEBUG__
							traceLog((TCHAR*)  _T(  "openLocalVideo failed: unknown uiCamCapType %d"  ),  uiCamCapType  );
					#endif
					goto  errLabel;
	}
	if  (  !pVc->bCapDevConnected  )  goto  errLabel;
	
	//	
	if (pVc->bCapDevConnected) {
		if (startCapture(pProcInfo, pVc)) {
			_sntprintf(tBuf, mycountof(tBuf), _T("Can't use the camera. Maybe it's used by others"));
			showNotification_open(0, 0, 0, tBuf);
		}
	}


	//  2011/08/13
	if  (  pVc->policy.bih.biWidth  &&  pVc->policy.bih.biHeight  )  {
		if  (  //  pVc->vh_org.bih.biWidth  !=  pVc->policy.bih.biWidth  ||  
			pVc->vh_org.bih.biHeight  !=  pVc->policy.bih.biHeight  )
		{
			//_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s: %dx%d"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_cantSupportResolution  ),  pVc->policy.bih.biWidth,  pVc->policy.bih.biHeight  );
			_sntprintf(tBuf, mycountof(tBuf), _T("cant support: %dx%d. real: %dx%d"), pVc->policy.bih.biWidth, pVc->policy.bih.biHeight,  pVc->vh_org.bih.biWidth,  pVc->vh_org.bih.biHeight);
			showNotification(  NULL,  NULL,  NULL,  0,  0,  0,  tBuf  );
		}
	}

	//
	char  fourccStr_org[5 + 1];  fourccStr_org[0] = 0;
	iFourcc2Str(pVc->vh_org.bih.biCompression, fourccStr_org, mycountof(fourccStr_org));

	//
	unsigned int uiModuleType;
	getModuleType_encV(&pVideoCompressor->common, &uiModuleType);
	int  iInputFourcc;
	getInputFourcc_encV(uiModuleType, &iInputFourcc);



	//
	if  (  pVc->vh_org.bih.biCompression  !=  BI_RGB  ||  pVc->vh_org.bih.biBitCount  !=  24  )  {
		if  (  initOrg2RgbBuf(  pProcInfoCommon,  (  CAP_procInfo_bmpCommon  *  )pVc  )  )  {
			#ifdef  __DEBUG__
					traceLogA(  (char*)  "initOrg2RgbBuf failed."  );
			#endif
			goto  errLabel;		
		}
	}



	//
	QY_VIDEO_HEADER	*	pVh_rgb;
	pVh_rgb  =  pVc->bOrg2RgbBufInited  ?  &pVc->vh_rgb  :  &pVc->vh_org;
	QY_VIDEO_HEADER  vh_dec  =  *pVh_rgb;
	
	//
	if  (  pVc->vh_org.bih.biCompression  ==  CONST_fourcc_MJPG  )  {

		//makeBmpInfoHeader_i420(  12,  pVc->vh_org.bih.biWidth,  pVc->vh_org.bih.biHeight,  &vh_dec.bih  );
		//
		if (!pVideoCompressor->common.iWidth_pic || !pVideoCompressor->common.iHeight_pic) {
			showInfo_open0(0, 0, _T("openLocalVideo failed, pVc->policy.w or h is 0"));
			goto  errLabel;
		}
		int sizeImg_policy = M_sizeImage_open(12, pVideoCompressor->common.iWidth_pic, pVideoCompressor->common.iHeight_pic);
		int sizeImg_org = M_sizeImage_open(12, pVc->vh_org.bih.biWidth, pVc->vh_org.bih.biHeight);
		//
		
		//
		if (sizeImg_policy < sizeImg_org) {
			//
			//makeBmpInfoHeader_i420(12, pVideoCompressor->common.iWidth_pic, pVideoCompressor->common.iHeight_pic, &vh_dec.bih);
			makeBmpInfoHeader_yuv(iInputFourcc,  12, pVideoCompressor->common.iWidth_pic, pVideoCompressor->common.iHeight_pic, &vh_dec.bih);
		}
		else {
			//		
			//makeBmpInfoHeader_i420(  12,  pVc->vh_org.bih.biWidth,  pVc->vh_org.bih.biHeight,  &vh_dec.bih  );
			makeBmpInfoHeader_yuv(  iInputFourcc,  12,  pVc->vh_org.bih.biWidth,  pVc->vh_org.bih.biHeight,  &vh_dec.bih  );
		}
	}
	else {
		 //  2026/03/30
		 makeBmpInfoHeader_yuv(iInputFourcc, 12, pVc->vh_org.bih.biWidth, pVc->vh_org.bih.biHeight, &vh_dec.bih);
	}


	

	//
	//  2010/09/13
	//
	//
	//
	{
		//  2014/04/03
		pVideoCompressor->common.pVideoQ2  =  &pVc->thread.q2;
		pVideoCompressor->common.pParent_transform  =  pVc;
		//
		//  2016/04/02
		_sntprintf(  pVc->compressVideo.tag_dbg,  mycountof(  pVc->compressVideo.tag_dbg  ),  _T(  "capBmp%d"  ),  iIndex_capBmp  );
		//
		if  (  pProcInfoCommon->initCompressVideo(  (  BITMAPINFO  *  )&vh_dec.bih,  CONST_capType_av,  pVideoCompressor,  TRUE,  0,  &pVc->compressVideo  )  )  
		{
			TCHAR	tBuf[128]  =  _T(  ""  );
			CUS_MODULE_U  *  pModule  =  NULL;

			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "openLocalVideo: initCompressVideo failed, %s, fourcc %s."  ),  qyGetDesByType1(  pAvParams->pVideoCompressorsTable,  pVideoCompressor->common.ucCompressors  ),  CQyString(  pVideoCompressor->common.fourccStr  )  );  
			if  (  pVideoCompressor->common.ucCompressors  ==  CONST_videoCompressors_hwAccl  )  {
				pModule  =  pQyMc->cusModules.pMediaSdk_enc;
				if  (  pModule
					&&  pModule->common.hModule  
					&&  pModule->compress.mgr.ucbNotSupported_hw  )
				{
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s Hardware accelerator not supported"  ),  tBuf  );
				}
			}
			//  qyShowHint(  _T(  "%s"  ),  tBuf  );  
			//  myMessageBox(  NULL,  tBuf,  _T(  "www.qycx.com"  ),  MB_OK  );
			showNotification(  0,  0,  0,  0,  0,  0,  tBuf  );
			goto  errLabel;
		}

	}

	//
	iFourcc2Str(  pVc->vh_org.bih.biCompression,  fourccStr_org,  mycountof(  fourccStr_org  )  );
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "w [%d], h [%d], org [%s],  sizeImg [%d]"  ),  pVc->vh_org.bih.biWidth,  pVc->vh_org.bih.biHeight, CQyString(  fourccStr_org  ),  pVc->vh_org.bih.biSizeImage  );
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "rgb [%d]"  ),  pVc->vh_rgb.bih.biSizeImage  );
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "fourcc [%s], com [%d], Quality [%d]"  ),  CQyString(  pVc->compressVideo.compressor.common.fourccStr  ),  pVc->compressVideo.iCompressBufSize,  pVc->compressVideo.u.vcm.iQuality  );

	iErr  =  0;

errLabel:

	MACRO_safeRelease(  pMoniker  );

	if  (  iErr  )  {
		closeLocalVideo(  pProcInfoCommon,  iIndex_sharedObj  );
	}
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "openLocalVideo %s"  ),  (  iErr  ?  _T(  "failed"  )  :  _T(  "OK"  )  )  );

	#ifdef  __DEBUG__
			traceLogA(  (char*)  "openLocalVideo leaves with %s",  iErr  ?  "Failed"  :  "OK"  );
	#endif

	return  iErr;

}


//
 int  closeLocalVideo(  MC_VAR_common  *  pProcInfoCommon,  int  iIndex_sharedObj  )
{
	int								iErr				=	-1;
	if  (  !pProcInfoCommon  )  return  -1;
	QY_MC						*	pQyMc				=		(  QY_MC  *  )pProcInfoCommon->pQyMc;//QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  -1;
	int								iIndex_capBmp		=	-1;

	//
	#ifdef  __DEBUG__
			traceLogA(  (char*)  "closeLocalVideo enters, index_sharedObj %d",  iIndex_sharedObj  );
	#endif
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfoCommon->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "closeLocalVideo enters. index_sharedObj %d"  ),  iIndex_sharedObj  );


	if  (  !pProcInfoCommon  )  {
		QY_SERVICEGUI_INFO	*	pSci		=		getServiceGuiInfo(  pQyMc,  pQyMc->iServiceId  );
		if  (  !pSci  )  return  -1;
		pProcInfoCommon						=		(  MC_VAR_common  *  )pSci->pVar;
	}
	if  (  !pProcInfoCommon  )  return  -1;
	
		MC_VAR_common	*	pProcInfo	=	(  MC_VAR_common  *  )pProcInfoCommon;
		QY_SHARED_OBJ				*	pSharedObj			=		NULL;
		CAP_procInfo_video  *  pVc  =  NULL;

		pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
		if  (  !pSharedObj  )  goto  errLabel;

		//
		iIndex_capBmp  =  pSharedObj->iIndex_capBmp;

		//
		pVc  =  (  CAP_procInfo_video  *  )getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
		if  (  !pVc  )  goto  errLabel;
	
		//  2017/09/13
		pVc->bCaptureStarted_openLocalVideo  =  FALSE;

	//
	stopCapture(  pProcInfo,  pVc  );
	if  (  pVc->bCaptureStarted  )  {
		#ifdef  __DEBUG__
				traceLogA(  (char*)  "closeLocalVideo failed: capture is not stopped."  );
		#endif
		goto  errLabel;
	}

	if  (  pVc->bCapDevConnected  )  {
        // Finally disconnect the driver
		switch  (  pVc->uiCamCapType  )  {
				case  CONST_camCapType_vfw:
					  if  (  IsWindow(  pVc->capDev.vfw.hCapWnd  )  )  capDriverDisconnect(  pVc->capDev.vfw.hCapWnd  );  		
					  pVc->bCapDevConnected  =  FALSE;
					  //
					  exitVideoCapWnd(  pProcInfoCommon,  pVc  );  		
					  break;
				case  CONST_camCapType_directX:
					  if  (  exitVideoCapDev_dx(  &pVc->capDev.pVideoCapDev  )  )  {
  						  #ifdef  __DEBUG__
								  traceLog((TCHAR*)  _T(  "closeLocalVideo failed, exitVideoCapDev_dx failed"  )  );
								  MACRO_qyAssert(  0,  _T(  "closeLocalVideo failed, exitVideoCapDev_dx failed"  )  );
						  #endif
						  goto  errLabel;
					  }
					  pVc->bCapDevConnected  =  FALSE;
					  break;
				case  CONST_camCapType_rtsp:		//  2014/02/24
					  if  (  exitVideoCapDev_rtsp(  pProcInfoCommon,  &pVc->capDev.pVideoCapDev  )  )  {
  						  #ifdef  __DEBUG__
								  traceLog((TCHAR*)  _T(  "closeLocalVideo failed, exitVideoCapDev_dx failed"  )  );
								  MACRO_qyAssert(  0,  _T(  "closeLocalVideo failed, exitVideoCapDev_dx failed"  )  );
						  #endif
						  goto  errLabel;
					  }
					  pVc->bCapDevConnected  =  FALSE;
					  break;
				case  CONST_camCapType_custom:  {
					  MODULE_camCap	*	pModule	=	(  MODULE_camCap  *  )getCusModule(  &pQyMc->cusModules,  CONST_moduleType_camCap  );
					  if  (  !pModule  )  goto  errLabel;

					  if  (  pModule->pf_exitVideoCapDev(  &pVc->capDev.pVideoCapDev  )  )  {
						  #ifdef  __DEBUG__
								  traceLog((TCHAR*)  _T(  "closeLocalVideo failed, pf_exitVideoCapDev failed"  )  );
								  MACRO_qyAssert(  0,  _T(  "closeLocalVideo failed, pf_exitVideoCapDev failed"  )  );
						  #endif
						  goto  errLabel;
					  }
					  pVc->bCapDevConnected  =  FALSE;
					  }
					  break;
				default:
						goto  errLabel;
		}
		memset(  &pVc->capDev,  0,  sizeof(  pVc->capDev  )  );
	}
	if  (  pVc->bCapDevConnected  )  {
		#ifdef  __DEBUG__
				traceLogA(  (char*)  "closeLocalVideo failed. bCapDevConnected is true"  );
		#endif
		goto  errLabel;
	}
	

	//
	if  (  pProcInfoCommon->exitCompressVideo(  TRUE,  &pVc->compressVideo  )  )  goto  errLabel;


	//  2009/05/30
	exitOrg2RgbBuf(  pProcInfoCommon,  (  CAP_procInfo_bmpCommon  *  )pVc  );  


	iErr  =  0;
errLabel:

#ifdef  __DEBUG__
	traceLogA(  (char*)  "closeLocalVideo leaves"  );
#endif
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfoCommon->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "closeLocalVideo leaves with %s"  ),  (  iErr  ?  _T(  "failed"  )  :  _T(  "OK"  )  )  );

	return  iErr;
}


//  2017/09/13
 int  resumeLocalVideo(  MC_VAR_common  *  pProcInfoCommon,  int  iIndex_sharedObj  )
 {
	int  iErr  =  -1;
	if  (  !pProcInfoCommon  )  return  -1;
	QY_MC						*	pQyMc				=		(  QY_MC  *  )pProcInfoCommon->pQyMc;//QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  -1;

	//
	TCHAR  tBuf[128];
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "resumeLocalVideo enters, index_sharedObj %d"  ),  iIndex_sharedObj  );
	showInfo_open0(  0,  0,  tBuf  );

	//
	QY_SHARED_OBJ		*	pSharedObj				=		getSharedObjByIndex(  pProcInfoCommon,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  return  -1;

	if  (  pSharedObj->uiType1  )  {
		return  -1;
	}

	//
	int  iIndex_capBmp  =  pSharedObj->iIndex_capBmp;
	CAP_procInfo_bmpU  *  pCapBmp  =  getCapBmpBySth(  pProcInfoCommon,  iIndex_capBmp,  0  );
	if  (  !pCapBmp  )  return  -1;

	if  (  !pCapBmp->common.compressVideo.bVideoCompressInited1  )  return  -1;

	//
	if  (  pCapBmp->common.uiType  !=  CONST_capType_av  )  return  -1;

	CAP_procInfo_video  *  pVc  =  &pCapBmp->video;
	//
	unsigned  int  uiCamCapType  =  pVc->uiCamCapType;

	switch  (  uiCamCapType  )  {
			case  CONST_camCapType_directX:
				  if  (  !bCameraRunning(  pVc  )  )  {
					  //					  	
					  stopCapture(  pProcInfoCommon,  pVc  );
					  if  (  pVc->bCaptureStarted  )  {
						  #ifdef  __DEBUG__
								  traceLogA(  (char*)  "closeLocalVideo failed: capture is not stopped."  );
						  #endif
						  goto  errLabel;	
					  }
					  	
					  if  (  pVc->bCapDevConnected  )  {
						  // Finally disconnect the driver
						  if  (  exitVideoCapDev_dx(  &pVc->capDev.pVideoCapDev  )  )  {
  							  #ifdef  __DEBUG__
									  traceLog((TCHAR*)  _T(  "closeLocalVideo failed, exitVideoCapDev_dx failed"  )  );
									  MACRO_qyAssert(  0,  _T(  "closeLocalVideo failed, exitVideoCapDev_dx failed"  )  );
							  #endif
							  goto  errLabel;						
						  }					  
						  pVc->bCapDevConnected  =  FALSE;
					  }		
					  memset(  &pVc->capDev,  0,  sizeof(  pVc->capDev  )  );

					  //
					  void  **  ppCapStuff  =  NULL;
					  //
					  if  (  initVideoCapDev_dx(  NULL,  pVc->displayName,  ppCapStuff,  &pVc->policy.bih,  FALSE,  pQyMc->gui.hMainWnd,  iIndex_sharedObj,  &pVc->capDev.pVideoCapDev  )  )  goto  errLabel;
					  pVc->bCapDevConnected  =  TRUE;
	
					  //
					  QY_VIDEO_HEADER  vh_org  =  {0};
					  //
					  if  (  !bGetCapturePara_dx(  pProcInfoCommon,  iIndex_capBmp,  BufferCB_av,  sizeof(  MIS_MSGU  ),  pVc->capDev.pVideoCapDev,  &vh_org  )  )  goto  errLabel;

					  //
					  if  (  memcmp(  &vh_org,  &pVc->vh_org,  sizeof(  vh_org  )  )  )  {
						  showInfo_open0(  0,  _T(  "resumeLocalVideo"  ),  _T(  "failed: vh_org not matched"  )  );
						  goto  errLabel;
					  }
					  //
					  startCapture(  pProcInfoCommon,  pVc  );



					  //
					  int  ii  =  0;


				  }				  
				  break;
			default:
					break;
	}





	iErr  =  0;
errLabel:


	//
	showInfo_open0(  0,  0,  _T(  "resumeLocalVideo leaves"  )  );


	 return  iErr;
 }








 //
 //
 //  
 //int  newSharedObjIndex(  MC_VAR_common  *  pProcInfo,  HWND  hWnd,  int  *  piIndex_sharedObjUsr,  BOOL  *  pbFirstUsr  )
 int  newSharedObjIndex(  MC_VAR_common  *  pProcInfo,  HWND  hWnd,  int  iSharedObjType,  int  *  piIndex_sharedObjUsr,  BOOL  *  pbFirstUsr  )
{
	int								iErr				=	-1;
	int								index				=	0;

	//
	if  (  !pProcInfo  )  return  -1;
	QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	if  (  !pQmcCfg  )  return  -1;
	QMC_status  *  pStatus  =  (  QMC_status  *  )pProcInfo->get_qmc_status(  );
	if  (  !pStatus  )  {
		MACRO_qyAssert(  0,  _T(  "newSharedObjIndex: qmcStatus is null"  )  );
		return  -1;
	}

	QY_MC					*		pQyMc				=	(  QY_MC  *  )pProcInfo->pQyMc;	//  QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  -1;

	
	if  (  !IsWindow(  hWnd  )  )  return  -1;

	//QY_sharedObj_sync  *  pSharedObjInfos  =  (  QY_sharedObj_sync  *  )pProcInfo->pSharedObjInfos;
	QY_sharedObj_sync	*	pSharedObjInfo  =  NULL;
	QY_SHARED_OBJ  *  pSharedObj  =  NULL;

	//  
	for  (  index  =  1;  index  <  pQmcCfg->usMaxCnt_pSharedObjs;  index  ++  )  {
		 pSharedObjInfo  =  getSharedObjSyncByIndex(  pProcInfo,  index  );
		 pSharedObj  =  &pSharedObjInfo->sharedObj;	//  getSharedObjByIndex(  pProcInfo,  index  );
		 //
		 if  (  !pSharedObj->bUsed  )  break;
	}
	if  (  index  ==  pQmcCfg->usMaxCnt_pSharedObjs  )  {
		//  2014/12/22
		pStatus->sysErr.bFailed_newSharedObj  =  TRUE;
		//
		goto  errLabel;
	}

	memset(  pSharedObj,  0,  sizeof(  pSharedObj[0]  )  );
	pSharedObj->index_sharedObj  =  index;
	pSharedObj->uiTranNo  =  getuiNextTranNo(  0,  0,  0  );
	pSharedObj->bUsed  =  TRUE;

	//
	pSharedObj->uiType1  =  iSharedObjType;

	//  2015/10/15
	pSharedObj->pProcInfo  =  pProcInfo;		//  2015/10/15

	//
	pSharedObj->iIndex_curUsr  =  -1;			//  2010/09/09

	//
	int					iIndex_usr; iIndex_usr = 0;
	SHARED_OBJ_USR* pSharedObjUsr; pSharedObjUsr = getSharedObjUsr(pSharedObj, iIndex_usr);
	pSharedObjUsr->hWnd_starter  =  hWnd;						//  2010/09/01

	//
	pSharedObj->iIndex_capAudio  =  -1;		//  2009/09/16
	pSharedObj->iIndex_capBmp  =  -1;			//  2009/09/16

	//pSharedObj->iIndex_shmCmd  =  -1;			//  2009/12/22

	pSharedObj->iIndex_localPlayer  =  -1;	//  2009/05/02

	//  2014/09/30
	syncMtCnt_start(  &pSharedObjInfo->syncMtCnt,  getuiNextTranNo  );


	iErr  =  0;
errLabel:

	if  (  !iErr  )  {
		if  (  piIndex_sharedObjUsr  )  *piIndex_sharedObjUsr  =  iIndex_usr;
		if  (  pbFirstUsr  )  *pbFirstUsr  =  TRUE;
	}

	return  iErr  ?  iErr  :  index;
}



 //  2016/03/27
// int  setCurSharedObjUsrFunc(  void  *  pMC_VAR_isCli,  int  index_sharedObj,  BOOL  bLocalAv,  HWND  hWnd  )
 int  setCurSharedObjUsrFunc(void* pMC_VAR_isCli, int  index_sharedObj, BOOL  bLocalAv, int index_sharedObjUsr)
{
	  MC_VAR_common  *  pProcInfo  =  (    MC_VAR_common  *  )pMC_VAR_isCli;

#if  0
	if  (  index  !=  0  )  {
		traceLog((TCHAR*)  _T(  "setSharedObjUsr_localAv failed, index error"  )  );
		return  -1;
	}
#endif
	//  int								index				=	0;
	//MC_VAR_isCli				*		pProcInfo			=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	QY_MC					*		pQyMc				=	(  QY_MC  *  )pProcInfo->pQyMc;//QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  -1;
	//
	QY_SHARED_OBJ			*		pSharedObj			=	NULL;


	//  pSharedObj  =  &pProcInfo->pSharedObjs[index];
	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  index_sharedObj  );
	if  (  !pSharedObj  )  return  -1;
	if  (  pSharedObj->bQuit  )  return  -1;
	if  (  !pSharedObj->bUsed  )  return  -1;

	//if  (  !IsWindow(  hWnd  )  )  return  -1;
	if (index_sharedObjUsr < 0 || index_sharedObjUsr >= mycountof(pSharedObj->usrs))  return  -1;


	int  i;
#if  0
	for  (  i  =  0;  i  <  mycountof(  pSharedObj->usrs  );  i  ++  )  {
		 if  (  pSharedObj->usrs[i].hWnd_starter  ==  hWnd  )  break;		 
	}
	if  (  i  ==  mycountof(  pSharedObj->usrs  )  )  return  -1;
#endif 
	i = index_sharedObjUsr;

	//
	if  (  pSharedObj->iIndex_curUsr  !=  i  )  {
		//
		HWND				hWnd_starter_old	=	NULL;
		SHARED_OBJ_USR	*	pSharedObjUsr	=	getSharedObjUsr(  pSharedObj,  pSharedObj->iIndex_curUsr  );
		if  (  pSharedObjUsr  &&  IsWindow(  pSharedObjUsr->hWnd_starter  )  )  {
			QY_WMBUF_COMM	wmBuf;
			memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );

			wmBuf.uiType  =  CONST_qyWmParam_requestToSpeak;
			wmBuf.u.requestToSpeak.uiCmd  =  ID_stopSpeaking;
			SendMessage(  pSharedObjUsr->hWnd_starter,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
			//
			hWnd_starter_old  =  pSharedObjUsr->hWnd_starter;
		}
		//		
		pSharedObj->iIndex_curUsr  =  i;
		//
		pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  pSharedObj->iIndex_curUsr  );
		MIS_CNT	*	pMisCnt	=	(  MIS_CNT  *  )pProcInfo->getMisCntByName(  _T(  ""  )  );
		//setROUTE_sendLocalAv(  pProcInfo,  pMisCnt,  &pSharedObjUsr->idInfo_to,  pSharedObjUsr->ucbVideoConferenceStarter,  &pSharedObj->curRoute_sendLocalAv  );
		//
		//  2016/02/10
		if  (  bLocalAv  )  {		
			pProcInfo->set_enlarged_gZone(  pSharedObjUsr->hWnd_starter  );
		}
		//
		//  2012/05/12
		PostMessage(  pSharedObjUsr->hWnd_starter,  CONST_qyWm_postComm,  CONST_qyWmParam_curSharedObjUsrChanged_mgr,  0  );
		if  (  IsWindow(  hWnd_starter_old  )  )  PostMessage(  hWnd_starter_old,  CONST_qyWm_postComm,  CONST_qyWmParam_curSharedObjUsrChanged_mgr,  0  );
	}


#if  0
	//  2011/03/13
	PostMessage(  hWnd,  WM_COMMAND,  MAKEWPARAM(  ID_viewLocalAv,  0  ),  0  );
#endif

	return  0;

}

 //
  //int  setCurSharedObjUsr_localAv(  void  *  pMC_VAR_isCli,  int  index_sharedObj,  HWND  hWnd  )
  int  setCurSharedObjUsr_localAv(  void  *  pMC_VAR_isCli,  int  index_sharedObj,  int index_sharedObjUsr  )
 {
	  if  (  !pMC_VAR_isCli  )  return  -1;
	  MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pMC_VAR_isCli;
	  HWND  hWnd = 0;

	  QY_SHARED_OBJ* pSharedObj = getSharedObjByIndex(pProcInfo, index_sharedObj);
	  if (pSharedObj) {
		  SHARED_OBJ_USR* pSharedObjUsr = getSharedObjUsr(pSharedObj, index_sharedObjUsr);
		  if (pSharedObjUsr) {
			  hWnd = pSharedObjUsr->hWnd_starter;
		  }
	  }

	  //
	  BOOL  bLocalAv  =  TRUE;
	  if  (  setCurSharedObjUsrFunc(  pMC_VAR_isCli,  index_sharedObj,  bLocalAv,  index_sharedObjUsr  )  )  {
		  resetCurSharedObjUsr_localAv(  pProcInfo,  index_sharedObj  );
		  //
		  //
		  pProcInfo->set_enlarged_gZone(  hWnd  );
	  }

	  //
	  if  (  bExists_slave(  pProcInfo,  index_sharedObj  )  )  {
		  QY_SHARED_OBJ  *  pSharedObj_master  =  getSharedObjByIndex(  pProcInfo,  index_sharedObj  );
		  if  (  pSharedObj_master  )  {
			  int  iIndex_sharedObj_slave  =  pSharedObj_master->master.slaveKey.iIndex_sharedObj;
			  //
			  int  index_sharedObjUsr = 0;
			  //
			  if  (  setCurSharedObjUsr(  pProcInfo,  iIndex_sharedObj_slave,  index_sharedObjUsr  )  )  {
				  resetCurSharedObjUsr(  pProcInfo,  iIndex_sharedObj_slave  );
			  }
		  }
	  }

	  //
	  return  0;
  }


 //
 //int  setCurSharedObjUsr(  MC_VAR_common  *  pProcInfo,  int  index_sharedObj,  HWND  hWnd  )
 int  setCurSharedObjUsr(MC_VAR_common* pProcInfo, int  index_sharedObj, int  index_sharedObjUsr)
{
	BOOL  bLocalAv  =  FALSE;
	return  setCurSharedObjUsrFunc(  pProcInfo,  index_sharedObj,  bLocalAv,  index_sharedObjUsr  );
}




 




 
 
 ///////////////


///////////////

 

 














 int  qmcChkTasks_gui(  MC_VAR_common  *  pProcInfo  )			//  2009/09/10
{
#if  0
	int								iErr				=	-1;
	//QY_SERVICEGUI_INFO		*		pSci				=	getServiceGuiInfo(  pQyMc,  pQyMc->iServiceId  );
	//if  (  !pSci  )  return  -1;
	//MC_VAR_isCli				*		pProcInfo			=	(  MC_VAR_isCli  *  )pSci->pVar;
	if  (  !pProcInfo  )  return  -1;
	QY_MC					*		pQyMc				=	(  QY_MC  *  )pProcInfo->pQyMc;	//QY_GET_GBUF(  );
	if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_mis  )  return  -1;

	//
	//
	BOOL							bInvalidTaskExists;

	traceLogA(  (char*)  "qisChkTasks_gui(  ) called."  );
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "qisChkTasks_gui called"  )  );

	#ifdef  __DEBUG__
			_ASSERT(  pProcInfo->processQ_media.m_var.dwThreadId_gui  ==  GetCurrentThreadId(  )  );
	#endif
				
	bInvalidTaskExists  =  FALSE;
	pProcInfo->processQ_media.qTraverse(  tmpHandler_findTaskInvalid_gui,  pProcInfo,  &bInvalidTaskExists  );
	if  (  bInvalidTaskExists  )  qisApplyForChkingTasks(  pProcInfo,  CONST_channelType_media  );

	//
	#ifdef  __DEBUG__
			_ASSERT(  pProcInfo->processQ_robot.m_var.dwThreadId_gui  ==  GetCurrentThreadId(  )  );
	#endif

	bInvalidTaskExists  =  FALSE;
	pProcInfo->processQ_robot.qTraverse(  tmpHandler_findTaskInvalid_gui,  pProcInfo,  &bInvalidTaskExists  );
	if  (  bInvalidTaskExists  )  qisApplyForChkingTasks(  pProcInfo,  CONST_channelType_robot  );

	//  2009/12/28
	PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_task_end,  0  );	

	//
	iErr  =  0;

	return  iErr;
#endif
	if  (  !pProcInfo  )  return  -1;
	return  pProcInfo->qisChkTasks_gui(  );
}



 
 int  qmcApplyForRemovingInvalidTasks(  MC_VAR_common  *  pProcInfoParam,  unsigned  int  uiChannelType  )
{
	CCtxQmc  *  pProcInfo  =  (  CCtxQmc  *  )pProcInfoParam;

	pProcInfo->ctrl.bNeedChkTasks  =  true;

	return  0;
}




 


 /*
 int  qmcRemoveInvalidTasks(  MC_VAR_common  *  pProcInfo  )			//  2009/09/10
{
	if  (  !pProcInfo  )  return  -1;
	pProcInfo->removeInvalidTasks(  0  );

	//
	//showInfo_open0(  0,  0,  _T(  "qmcRemoveInvalidTasks called"  )  );

	//
	return  0;
}
*/



 ////////////////

 