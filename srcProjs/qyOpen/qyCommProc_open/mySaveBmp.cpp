

#include	"stdafx.h"
#include	<Windows.h>
#include	<stdio.h>
#include	<math.h>
#include	<stdlib.h>
#include	<tchar.h>
#include	<mmsystem.h>

#include	"qmOpenCommon.h"
#include	"imgFunc_open.h"

//
 

//
void  mySaveBitmap(  BITMAPINFOHEADER  *  pBih,  void  *  rgb,  BOOL  bFlipImg,  LPCTSTR  szFilename  )
{
	//  HDC						hdc		=	NULL;
	FILE				*	fp		=	NULL;
	LPVOID					pBuf	=	NULL;
	BITMAPINFO				bmpInfo;
	BITMAPFILEHEADER		bmpFileHeader;

	if  (  !pBih  ||  !rgb  )  return;
	if  (  !pBih->biWidth  ||  !pBih->biHeight  )  return;
	if  (  pBih->biBitCount  !=  24  )  return;

	do  {
		//  hdc  =  GetDC(  NULL  );
		ZeroMemory(  &bmpInfo,  sizeof(  BITMAPINFO  )  );
		bmpInfo.bmiHeader.biSize  =  sizeof(  BITMAPINFOHEADER  );
		//  GetDIBits(  hdc,  hBitmap,  0,  0,  NULL,  &bmpInfo,  DIB_RGB_COLORS  );
		memcpy(  &bmpInfo,  pBih,  sizeof(  bmpInfo.bmiHeader  )  );

		if  (  bmpInfo.bmiHeader.biSizeImage  <=  0  )  
			bmpInfo.bmiHeader.biSizeImage  =  bmpInfo.bmiHeader.biWidth  *  abs(  bmpInfo.bmiHeader.biHeight  )*  (  bmpInfo.bmiHeader.biBitCount +7  )  /  8;
		
#if  0
		if  (  (  pBuf  =  mymalloc(  bmpInfo.bmiHeader.biSizeImage  )  )  ==  NULL  )  {
			//  myMessageBox(  NULL,  _T(  "Unable  to  Allocate Bitmap Memory  "  ),  _T(  "Error"  ),  MB_OK | MB_ICONERROR  );
			break;
		}
#endif

		bmpInfo.bmiHeader.biCompression  =  BI_RGB;
		//  GetDIBits(  hdc,  hBitmap, 0,  bmpInfo.bmiHeader.biHeight,  pBuf,  &bmpInfo,  DIB_RGB_COLORS  );
		pBuf  =  rgb;

		if  (  (  fp  =  _tfopen(  szFilename,  _T(  "wb"  )  )  )  ==  NULL  )  {
			//  myMessageBox(  NULL,  _T(  "Unable  to  Create Bitmap File"  ),  _T(  "Error"  ),  MB_OK|MB_ICONERROR   );
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

	//  if  (  hdc  )  ReleaseDC(  NULL,  hdc  );
	//  if  (  pBuf  )  free(  pBuf  );
	if  (  fp  )  fclose(  fp  );

	//
#if  0
	parseBmpFile(  szFilename,  _T(  ""  ),  bFlipImg  );
#endif

	return;
}



void  mySaveYv12(  int  w,  int  h,  void  *  yv12,  BOOL  bFlipImg, LPCTSTR  szFilename  )
{
	BITMAPINFOHEADER	bih;
	makeBmpInfoHeader_rgb(  24,  w,  h,  &bih  );
	char  *  rgb  =  NULL;

	rgb  =  (  char  *  )malloc(  bih.biSizeImage  );
	if  (  !rgb  )  goto  errLabel;

	yv12ToRgb24(  (  unsigned  char  *  )yv12,  (  unsigned  char  *  )rgb,  w,  h,  bFlipImg  );

	mySaveBitmap(  &bih,  rgb,  bFlipImg,  szFilename  );


errLabel:

	if  (  rgb  )  free(  rgb  );

	return;
}



//
void  mySaveI420(int  w, int  h, void* yv12, BOOL  bFlipImg, LPCTSTR  szFilename)
{
	BITMAPINFOHEADER	bih;
	makeBmpInfoHeader_rgb(24, w, h, &bih);
	char* rgb = NULL;

	rgb = (char*)malloc(bih.biSizeImage);
	if (!rgb)  goto  errLabel;

	i420ToRgb24((unsigned  char*)yv12, (unsigned  char*)rgb, w, h, bFlipImg);

	mySaveBitmap(&bih, rgb, bFlipImg, szFilename);


errLabel:

	if (rgb)  free(rgb);

	return;
}


//
void  mySaveNv12(int  w, int  h, void* nv12, BOOL  bFlipImg, LPCTSTR  szFilename)
{
	BITMAPINFOHEADER	bih;
	makeBmpInfoHeader_rgb(24, w, h, &bih);
	char* rgb = NULL;

	rgb = (char*)malloc(bih.biSizeImage);
	if (!rgb)  goto  errLabel;

	nv12ToRgb24((unsigned  char*)nv12, (unsigned  char*)rgb, w, h, bFlipImg);

	mySaveBitmap(&bih, rgb, bFlipImg, szFilename);


errLabel:

	if (rgb)  free(rgb);

	return;
}

