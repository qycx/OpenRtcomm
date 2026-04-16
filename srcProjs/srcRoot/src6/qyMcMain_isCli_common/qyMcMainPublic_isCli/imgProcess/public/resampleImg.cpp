

#include "stdafx.h"
#include	<tchar.h>
#include	<time.h>
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

//  #include	"myresource.h"
#include	"tmpCeLib.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qmcDmoPublic.h"
#include	"qyCusResTemp.h"

#ifndef  __WINCE__
#include	"qmcVWall.h"
#endif
#include	"qmcCmdProc.h"

#include	"qyAvRecordPublic.h"
#include	"imgProcessPublic.h"
#include	"imgProcessCommon.h"
#include	"isCliHelpPublic.h"

#include	<Shlwapi.h>
#include	<math.h>

 int resizeRgb24_nearest(  unsigned  char  *  src,  int  srcWidth,  int  srcHeight,  unsigned  char  *  dst,  int  dstWidth,  int  dstHeight  );
int resizeRgb24_bilinear(  unsigned  char  *  src,  int  srcWidth,  int  srcHeight,  unsigned  char  *  dst,  int  dstWidth,  int  dstHeight  );

//
 int bmpEx_ScaleBilinear2_24(  unsigned  char  *  src,  int  srcWidth,  int  srcHeight,  unsigned  char  *  dst,  int  dstWidth,  int  dstHeight  );



__declspec(  dllexport  ) int resizeRgb24(  unsigned  char  *  src,  int  srcWidth,  int  srcHeight,  unsigned  char  *  dst,  int  dstWidth,  int  dstHeight  )
{


		#if  10
			 return   bmpEx_ScaleBilinear2_24(  src,  srcWidth,  srcHeight,  dst,  dstWidth,  dstHeight  );
		#endif


	//
#if  0
	return  resizeRgb24_nearest(  src,  srcWidth,  srcHeight,  dst,  dstWidth,  dstHeight  );
#else
	return  resizeRgb24_bilinear(  src,  srcWidth,  srcHeight,  dst,  dstWidth,  dstHeight  );
#endif


}



//  2014/04/24. nearest
int resizeRgb24_nearest(  unsigned  char  *  src,  int  srcWidth,  int  srcHeight,  unsigned  char  *  dst,  int  dstWidth,  int  dstHeight  )
{
	int  width  =  0,  height  =  0;
	int  x =  0,  y  = 0;
	
	//
	width  =  dstWidth;
	height  =  dstHeight;
	
	//
	int  bits  =  24;
	int	rgbIncrement  =  bits  /  8;
	int  widthBytes_src  =  M_lineBytes_rgb(  bits,  srcWidth  );
	int  widthBytes_dst  =  M_lineBytes_rgb(  bits,  dstWidth  );
	
	if  (  !src  ||  srcWidth  <=  0  ||  srcHeight  <=  0  ||  !dst  ||  dstWidth  <=  0  ||  dstHeight  <=  0  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "resizeRgb24 failed: input param err"  )  );
		#endif
		return  -1;
	}
	if  (  srcWidth  <  dstWidth
		||  srcHeight  <  dstHeight  )
	{
		#ifdef  __DEBUG__
				traceLog(  _T(  "resizeRgb24 failed: only scaling down is supported"  )  );
		#endif
		return  -1;
	}

	float  tx  =  (  float  )(  srcWidth  -  1  )  /  dstWidth;
	float  ty  =  (  float  )(  srcHeight  -  1  )  /  dstHeight;

	//
	for  (  y  = 0; y < height; y ++  )
	{
		
		for (  x = 0; x < width; x ++  )
		{
			int  xSrc  =  ceil(  tx  *  x  );
			int  ySrc  =  ceil(  ty  *  y  );


			//				
			int  index_rgb_src  =  widthBytes_src  *  ySrc  +  xSrc  *  rgbIncrement;
							
			BYTE  b_src  =  src[index_rgb_src  +  0];							
			BYTE  g_src  =  src[index_rgb_src  +  1];
			BYTE  r_src  =  src[index_rgb_src  +  2];


			//			
			int  index_rgb_dst  =  widthBytes_dst  *  y  +  x  *  rgbIncrement;
				
			dst[index_rgb_dst  +  0]  =  b_src;
			dst[index_rgb_dst  +  1]  =  g_src;
			dst[index_rgb_dst  +  2]  =  r_src;
			
			//  SetDIBPixel(  x,y, color32 );
		}
	}


	return 0;
}





int resizeRgb24_bilinear(  unsigned  char  *  src,  int  srcWidth,  int  srcHeight,  unsigned  char  *  dst,  int  dstWidth,  int  dstHeight  )
{
	int  width  =  0,  height  =  0;
	//  int  x =  0,  y  = 0;
	
	//
	width  =  dstWidth;
	height  =  dstHeight;
	
	//
	int  bits  =  24;
	int	rgbIncrement  =  bits  /  8;
	int  widthBytes_src  =  M_lineBytes_rgb(  bits,  srcWidth  );
	int  widthBytes_dst  =  M_lineBytes_rgb(  bits,  dstWidth  );
	
	if  (  !src  ||  srcWidth  <=  0  ||  srcHeight  <=  0  ||  !dst  ||  dstWidth  <=  0  ||  dstHeight  <=  0  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "resizeRgb24 failed: input param err"  )  );
		#endif
		return  -1;
	}
	if  (  srcWidth  <  dstWidth
		||  srcHeight  <  dstHeight  )
	{
		#ifdef  __DEBUG__
				traceLog(  _T(  "resizeRgb24 failed: only scaling down is supported"  )  );
		#endif
		return  -1;
	}

	float  tx  =  (  float  )(  srcWidth  -  1  )  /  dstWidth;
	float  ty  =  (  float  )(  srcHeight  -  1  )  /  dstHeight;
	float  dx,  dy;
	int  i,  j;
	int  index_rgb_src;
	int  a,  b,  c;
	//
	for  (  j  = 0; j < height; j ++  )
	{		
		for (  i = 0; i < width; i ++  )
		{
			dx  =  tx  *  i;
			dy  =  ty  *  j;

			int  xSrc  =  (  int  )(  dx  );
			int  ySrc  =  (  int  )(  dy  );

			dx  =  dx  -  xSrc;
			dy  =  dy  -  ySrc;

			//				
			int  index_rgb_src  =  widthBytes_src  *  ySrc  +  xSrc  *  rgbIncrement;
			a  =  ySrc  *  widthBytes_src  +  (  xSrc  +  1  )  *  rgbIncrement;
			b  =  (  ySrc  +  1  )  *  widthBytes_src  +  xSrc  *  rgbIncrement;
			c  =  (  ySrc  +  1  )  *  widthBytes_src  +  (  xSrc  +  1  )  *  rgbIncrement;
			
			
			//			
			int  index_rgb_dst  =  widthBytes_dst  *  j  +  i  *  rgbIncrement;

			//
			int  k;
			for  (  k  =  0;  k  <  3;  k  ++  )  {
				 dst[index_rgb_dst  +  k]  =  src[index_rgb_src  +  k]  *  (  1  -  dx  )  *  (  1  -  dy  )
					 +  src[a  +  k]  *  dx  *  (  1  -  dy  )  +  src[b  +  k]  *  (  1  -  dx  )  *  dy
					 +  src[c  +  k]  *  dx  *  dy;
			}			
			//  SetDIBPixel(  x,y, color32 );
		}
	}


	return 0;
}
