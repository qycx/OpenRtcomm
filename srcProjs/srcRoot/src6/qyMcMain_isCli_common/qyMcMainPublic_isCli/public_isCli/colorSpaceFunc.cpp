
#include	"stdafx.h"
#include	<Windows.h>
#include	<stdio.h>
#include	<math.h>
#include	<stdlib.h>
#include	<tchar.h>
#include	<Shlwapi.h>

#include	"colorSpaceFunc.h"


 //  2013/09/20
__declspec(  dllexport  )   int  convert_rgb_to_yuv_pixel(  int  r,  int  g,  int  b,  BYTE  *  py,  BYTE  *  pu,  BYTE  *  pv  )
{
#if  0
	unsigned  int  pixel32  =  0;
	unsigned  char  *  pixel  =  (  unsigned  char  *  )&pixel32;
#endif
	int  y,  u,  v;

	y  =  (  (  66  *  r  +  129  *  g  +  25  *  b  +  128  )  >>  8  )  +  16;
	u  =  (  (  -38  *  r  -  74  *  g  +  112  *  b  +  128  )  >>  8  )  +  128;
	v  =  (  (  112  *  r  -  94  *  g  -  18  *  b  +  128  )  >>  8  )  +  128;
	if  (  y  >  255  )  y  =  255;
	if  (  u  >  255  )  u  =  255;
	if  (  v  >  255  )  v  =  255;
	if  (  y  <  0  )  y  =  0;
	if  (  u  <  0  )  u  =  0;
	if  (  v  <  0  )  v  =  0;

#if  0
	pixel[0]  =  y;
	pixel[1]  =  u;
	pixel[2]  =  v;

	return  pixel32;
#endif

	*py  =  y;
	*pu  =  u;
	*pv  =  v;

	return  0;
}


__declspec(  dllexport  )  int  convert_yuv_to_rgb_pixel(  int  y,  int  u,  int  v,  BYTE  *  pr,  BYTE  *  pg,  BYTE  *  pb  )
{
#if  0
	unsigned int pixel32  =  0;
	unsigned char * pixel  =  (  unsigned  char  *  )&pixel32;
#endif

	int c,d,e;
	int r,g,b;

	c  =  y  -  16;
	d  =  u  -  128;
	e  =  v  -  128;

	r  =  (  (  298  *  c                +  409  *  e  +  128  )  >>  8  );
	g  =  (  (  298  *  c  -  100  *  d  -  208  *  e  +  128  )  >>  8  );
	b  =  (  (  298  *  c  +  516  *  d                +  128  )  >>  8  );
		
	if  (  r  >  255  )  r  =  255;
	if  (  g  >  255  )  g  =  255;
	if  (  b  >  255  )  b  =  255;

	if  (  r  <  0  )  r  =  0;
	if  (  g  <  0  )  g  =  0;
	if  (  b  <  0  )  b  =  0;

#if  0
	pixel[0]  =  b;
	pixel[1]  =  g;
	pixel[2]  =  r;

	return  pixel32;
#endif
	*pr  =  r;
	*pg  =  g;
	*pb  =  b;

	return  0;
}



 ////////////////////////

// __declspec(  dllexport  )  int  convert_rgb_to_key_pixel(  int  r,  int  g,  int  b,  BYTE  *  pL,  BYTE  *  pH,  BYTE  *  pS  )
 __declspec(  dllexport  )  int  convert_rgb_to_key_pixel(  int  r,  int  g,  int  b,  BYTE  *  pX,  BYTE  *  pY,  BYTE  *  pZ  )
 {
	 
#ifdef  __USE_hsl_chromaKey__
	 WORD  wH  =  0,  wS  =  0,  wL  =  0;
	 
	 //  VOID ColorRGBToHLS(      COLORREF clrRGB,WORD *  pwHue, WORD *  pwLuminance,  WORD *  pwSaturation  );
	 ColorRGBToHLS(      RGB(  r,  g,  b  ),  &wH,  &wL,  &wS  );
          
#if  0
	 *pL  =  wy;
	 *pH  =  wu;
	 *pS  =  wv;
#endif
	 *pX  =  wH;
	 *pY  =  wS;
	 *pZ  =  wL;
#else

	 	 //  if  (  convert_rgb_to_yuv_pixel(  r,  g,  b,  py,  pu,  pv  )  )  return  -1;
	 if  (  convert_rgb_to_yuv_pixel(  r,  g,  b,  pX,  pY,  pZ  )  )  return  -1;

#endif


	 return  0;
 }

//__declspec(  dllexport  )  int  convert_key_to_rgb_pixel(  int  l,  int  h,  int  s,  BYTE  *  pr,  BYTE  *  pg,  BYTE  *  pb  )
__declspec(  dllexport  )  int  convert_key_to_rgb_pixel(  int  x,  int  y,  int  z,  BYTE  *  pr,  BYTE  *  pg,  BYTE  *  pb  )
  {
#ifdef  __USE_hsl_chromaKey__
	  int  h;
	  int  s;
	  int  l;

	  h  =  x;  s  =  y;  l  =  z;

	  //
	  WORD  wr,  wg,  wb; COLORREF  rgb;
	  //  COLORREF ColorHLSToRGB(  WORD wHue,  WORD wLuminance,  WORD wSaturation  );

	  rgb  =  ColorHLSToRGB(  h, l, s  );

	  *pr  =  GetRValue( rgb  );
	  *pg  =  GetGValue( rgb  );
	  *pb  =  GetRValue( rgb  );
          
#else

	  //  if  (  convert_yuv_to_rgb_pixel(  y,  u,  v,  pr,  pg,  pb  )  )  return  -1;
	  if  (  convert_yuv_to_rgb_pixel(  x,  y,  z,  pr,  pg,  pb  )  )  return  -1;
#endif

	  return  0;

  }
