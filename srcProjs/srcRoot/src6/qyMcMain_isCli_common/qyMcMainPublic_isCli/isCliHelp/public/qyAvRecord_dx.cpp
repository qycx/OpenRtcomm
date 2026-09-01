
#include	"stdafx.h"

#include	<dmoreg.h>
#ifndef  __WINCE__
	#include	<d3d9.h>
	//#include	<d3dx9.h>
#endif

#include	"qyMcMainCommon.h"
//#include	"qmShell_open.h"
#include	"qmcVideoCapture_isCli.h"

#include	"qyAvRecord.h"
#include	"qyAvRecord_dx.h"
#ifndef  __WINCE__
		 //#include	"qyBoundWnd.h"
#endif
#include	"qyDynLib.h"
#include	"..\\qyHookHelp\\qyHookHelp.h"
//  #include	"myresource.h"
#include	"tmpCeLib.h"
#include	"funcsForIsCliHelp.h"


#define			CONST_bitsPerPixel		24


 








 void  cleanUp_avRecord(  QY_AV_RECORD  *  pAvRecord  )  
{
	/*
	if  (  pAvRecord->directX.hBackBitmap  )  {
		DeleteObject(  pAvRecord->directX.hBackBitmap  );  pAvRecord->directX.hBackBitmap  =  NULL;
	}
	*/
	if  (  pAvRecord->pBits  )  {
		free(  pAvRecord->pBits  );  pAvRecord->pBits  =  NULL;
	}

	if  (  pAvRecord->bUseDirectX  )  {
#if  0	//  2014/10/23
		ii_exitD3D(  pAvRecord  );
#endif
		/*
		if  (  pAvRecord->directX.g_pSurface  )  {
			pAvRecord->directX.g_pSurface->Release(  );
			pAvRecord->directX.g_pSurface  =  NULL;
		}
		if  (  pAvRecord->directX.g_pd3dDevice  )  {
			pAvRecord->directX.g_pd3dDevice->Release(  );
			pAvRecord->directX.g_pd3dDevice  =  NULL;
		}
		if  (  pAvRecord->directX.g_pD3D  )  {
			pAvRecord->directX.g_pD3D->Release(  );
			pAvRecord->directX.g_pD3D  =  NULL;
		}
		*/
	}

}


 int  doCreate_avRecord(  QY_DYN_LIBS  *  pDynLibs,  HWND  hWnd,  COMPRESS_VIDEO  *  pCompressVideo,  BOOL  bUseDirectX,  QY_AV_RECORD  *  pAvRecord  )
{
	int				iErr		=	-1;
	if  (  !pDynLibs  )  return  -1;
	DYN_LIB_DX  *	pDynLib		=	(  DYN_LIB_DX  *  )pDynLibs->pLib_dx;
	if  (  !pDynLib  )  return  -1;
	//  HWND			hDesktop	=	NULL;
	//  HDC				hdc			=	NULL;
	int				iWidth,  iHeight;

	pAvRecord->nBits  =  CONST_bitsPerPixel;

	iWidth  =  pCompressVideo->width;
	iHeight  =  pCompressVideo->height;
	makeBmpInfoHeader_rgb(  pAvRecord->nBits,  iWidth,  iHeight,  &pAvRecord->bmpInfo.bmiHeader  );

	/*
	hDesktop  =  GetDesktopWindow(  );
	hdc  =  GetDC(  hDesktop  );
	pAvRecord->directX.hBackBitmap  =  CreateDIBSection(  hdc,  &pAvRecord->directX.bmpInfo,  DIB_RGB_COLORS,  &pAvRecord->directX.pBits,  NULL,  0  );
	if  (  pAvRecord->directX.hBackBitmap  ==  NULL  )  {
		traceLogA(  "Unable  to  Create  BackBuffer  Bitmap  "  );
		goto  errLabel;
	}
	ReleaseDC(  hDesktop,  hdc  );  hdc  =  NULL;
	*/
	pAvRecord->pBits  =  mymalloc(  pAvRecord->bmpInfo.bmiHeader.biSizeImage  );
	if  (  !pAvRecord->pBits  )  goto  errLabel;

	pAvRecord->bUseDirectX  =  bUseDirectX;		//  2009/09/23

	if  (  pAvRecord->bUseDirectX  )  {

		//  if  (  ii_initD3D(  pDynLib,  hWnd,  pAvRecord  )  )  goto  errLabel;
		#ifdef  __DEBUG__	//  2014/10/23
				traceLog(  _T(  "Failed: unused here"  )  );
		#endif
		goto  errLabel;

		//
		pAvRecord->directX.gCapturedRect.left  =  pCompressVideo->left;
		pAvRecord->directX.gCapturedRect.top  =  pCompressVideo->top;
		pAvRecord->directX.gCapturedRect.right  =  pCompressVideo->left  +  pCompressVideo->width  -  1;
		pAvRecord->directX.gCapturedRect.bottom  =  pCompressVideo->top  +  pCompressVideo->height  -  1;

	}

	iErr  =  0;

errLabel:

	/*
	if  (  hdc  )  {
		ReleaseDC(  hDesktop,  hdc  );
	}
	*/

	if  (  iErr  )  {
		cleanUp_avRecord(  pAvRecord  );
	}

	return  iErr;
}

 void  saveBitmap_debug(  char  *  szFilename,  HBITMAP  hBitmap  )
{
#ifdef  __WINCE__
	return;
#else
	HDC						hdc		=	NULL;
	FILE				*	fp		=	NULL;
	LPVOID					pBuf	=	NULL;
	BITMAPINFO				bmpInfo;
	BITMAPFILEHEADER		bmpFileHeader;

	do  {
		hdc  =  GetDC(  NULL  );
		ZeroMemory(  &bmpInfo,  sizeof(  BITMAPINFO  )  );
		bmpInfo.bmiHeader.biSize  =  sizeof(  BITMAPINFOHEADER  );
		GetDIBits(  hdc,  hBitmap,  0,  0,  NULL,  &bmpInfo,  DIB_RGB_COLORS  );

		if  (  bmpInfo.bmiHeader.biSizeImage  <=  0  )  
			bmpInfo.bmiHeader.biSizeImage  =  bmpInfo.bmiHeader.biWidth  *  abs(  bmpInfo.bmiHeader.biHeight  )*  (  bmpInfo.bmiHeader.biBitCount +7  )  /  8;
		
		if  (  (  pBuf  =  mymalloc(  bmpInfo.bmiHeader.biSizeImage  )  )  ==  NULL  )  {
			myMessageBox(  NULL,  _T(  "Unable  to  Allocate Bitmap Memory  "  ),  _T(  "Error"  ),  MB_OK | MB_ICONERROR  );
			break;
		}

		bmpInfo.bmiHeader.biCompression  =  BI_RGB;
		GetDIBits(  hdc,  hBitmap, 0,  bmpInfo.bmiHeader.biHeight,  pBuf,  &bmpInfo,  DIB_RGB_COLORS  );

		if  (  (  fp  =  fopen(  szFilename,  "wb"  )  )  ==  NULL  )  {
			myMessageBox(  NULL,  _T(  "Unable  to  Create Bitmap File"  ),  _T(  "Error"  ),  MB_OK|MB_ICONERROR   );
			break;
		}

		bmpFileHeader.bfReserved1  =  0;
		bmpFileHeader.bfReserved2  =  0;
		bmpFileHeader.bfSize  =  sizeof(  BITMAPFILEHEADER  )  +  sizeof(  BITMAPINFOHEADER  )  +  bmpInfo.bmiHeader.biSizeImage;
		bmpFileHeader.bfType  =  'MB';
		bmpFileHeader.bfOffBits  =  sizeof(  BITMAPFILEHEADER  )  +  sizeof(  BITMAPINFOHEADER  );

		fwrite(  &bmpFileHeader,  sizeof(  BITMAPFILEHEADER  ),  1,  fp  );
		fwrite(  &bmpInfo.bmiHeader,  sizeof(  BITMAPINFOHEADER  ),  1,  fp  );
		fwrite(  pBuf,  bmpInfo.bmiHeader.biSizeImage,  1,  fp  );

	}  while(  false  );

	if  (  hdc  )  ReleaseDC(  NULL,  hdc  );
	if  (  pBuf  )  free(  pBuf  );
	if  (  fp  )  fclose(  fp  );

	return;
#endif
}









