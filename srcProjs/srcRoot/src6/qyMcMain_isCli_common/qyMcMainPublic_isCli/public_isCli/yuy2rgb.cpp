
#include	"stdafx.h"
#include	<tchar.h>
//#include	"qyMcMainCommon.h"

#include	"colorSpaceFunc.h"


//  2011/11/30
//  #define	clip255(  v  )  if  (  (  v  )  <  0  )  (  v  )  =  0;  if  (  (  v  )  >  255  )  (  v  )  =  255;



#if  0
//
 int  convert_yuv_to_rgb_pixel(  int  y,  int  u,  int  v  )
{
	unsigned int pixel32  =  0;
	unsigned char * pixel  =  (  unsigned  char  *  )&pixel32;
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

	pixel[0]  =  b;
	pixel[1]  =  g;
	pixel[2]  =  r;

	return  pixel32;
}
  

  int  yuy2ToRgb24(  unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height  )
{
	if  (  width  <=  0  ||  height  <=  0  )  {
		OutputDebugString(  _T(  "yuy2reg24 failed, width or height <=  0"  )  );
		return  -1;
	}
	unsigned  int	in,  out  =  0;
	unsigned  int	pixel_16;
	unsigned  char  pixel_24[3];
	unsigned  int	pixel32;
	int  y0,  u,  y1,  v;
	int				i,  j;
	int				nBytesPerLine_rgb24	=	(  width  *  24  +  31  )  /  32  *  4;
	
	for  (  j  =  0;  j  <  (  int  )height;  j  ++  )  {
		 for  (  i  =  0;  i  <  (  int  )width;  i  +=  2  )  {
			  in  =  j  *  width  *  2  +  i  *  2;
			  out  =  (  height  -  j  -  1  )  *  nBytesPerLine_rgb24  +  i  *  3;  
	
			  pixel_16  =
				  yuv[in  +  3]  <<  24  |
				  yuv[in  +  2]  <<  16  |
				  yuv[in  +  1]  <<  8   |
				  yuv[in  +  0];

			  y0  =  (  pixel_16  &  0x000000ff  );
			  u   =  (  pixel_16  &  0x0000ff00  )  >>  8;
			  y1  =  (  pixel_16  &  0x00ff0000  )  >>  16;
			  v   =  (  pixel_16  &  0xff000000  )  >>  24;

			  pixel32  =  convert_yuv_to_rgb_pixel(  y0,  u,  v  );

			  pixel_24[0]  =  (  pixel32  &  0x000000ff  );
			  pixel_24[1]  =  (  pixel32  &  0x0000ff00  )  >>  8;
			  pixel_24[2]  =  (  pixel32  &  0x00ff0000  )  >>  16;

			  rgb[out]  =  pixel_24[0];
			  rgb[out+1]  =  pixel_24[1];
			  rgb[out+2]  =  pixel_24[2];

			  pixel32  =  convert_yuv_to_rgb_pixel(y1,  u,  v  );

			  pixel_24[0]  =  (  pixel32  &  0x000000ff  );
			  pixel_24[1]  =  (  pixel32  &  0x0000ff00  )  >>  8;
			  pixel_24[2]  =  (  pixel32  &  0x00ff0000  )  >>  16;

			  rgb[out+3]  =  pixel_24[0];
			  rgb[out+4]  =  pixel_24[1];
			  rgb[out+5]  =  pixel_24[2];
	 
		 }
	}

	return  0;
}

#else

//  注, c, d, e是辅助变量
#define		M_yuvtorgb(  y,  u,  v,  b,  g,  r,  c,  d,  e  )							\
			  c  =  y  -  16;															\
			  d  =  u  -  128;															\
			  e  =  v  -  128;															\
			  r  =  (  298  *  c  +  409  *  e  +  128  )  >>  8;						\
			  g  =  (  298  *  c  -  100  *  d  -  208  *  e  +  128  )  >>  8;			\
			  b  =  (  298  *  c  +  516  *  d  +  128  )  >>  8;						\
  			  clip255(  r  );															\
			  clip255(  g  );															\
			  clip255(  b  );


 int  yuy2ToRgb24(  void  *  pCusModulesParam,  unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height,  BOOL  bFlipImg  )
{
#ifdef  __SUPPORT_qyMc_ipp__
		//QY_MC	*	pQyMc	=	
	    CUS_MODULES  *  pCusModules  =  (  CUS_MODULES  *  )pCusModulesParam;
		
		if  (  pCusModules
			&&  pCusModules->pIpp  
			&&  pCusModules->pIpp->compress.mgr.pf_yuy2ToRgb24  
			//&&  bFlipImg  
			)  
		{	
			//  2011/12/03
			return  pCusModules->pIpp->compress.mgr.pf_yuy2ToRgb24(  yuv,  (  unsigned  char  *  )rgb,  width,  height,  bFlipImg  );
		}

#endif


	//
	if  (  width  <=  0  ||  height  <=  0  )  {
		OutputDebugString(  _T(  "yuy2reg24 failed, width or height <=  0"  )  );
		return  -1;
	}
	unsigned  int	in,  out  =  0;
	//  unsigned  int	pixel_16;
	//  unsigned  char  pixel_24[3];
	//  unsigned  int	pixel32;
	int  y0,  u,  y1,  v;
	int				i,  j;
	int				nBytesPerLine_rgb24	=	(  width  *  24  +  31  )  /  32  *  4;


	int  y,  c,  d,  e;
	int  r,  g,  b;


	for  (  j  =  0;  j  <  (  int  )height;  j  ++  )  {
		 for  (  i  =  0;  i  <  (  int  )width;  i  +=  2  )  {
			  in  =  j  *  width  *  2  +  i  *  2;
			  out  =  (  height  -  j  -  1  )  *  nBytesPerLine_rgb24  +  i  *  3;  
	
#if  0
			  pixel_16  =
				  yuv[in  +  3]  <<  24  |
				  yuv[in  +  2]  <<  16  |
				  yuv[in  +  1]  <<  8   |
				  yuv[in  +  0];

			  y0  =  (  pixel_16  &  0x000000ff  );
			  u   =  (  pixel_16  &  0x0000ff00  )  >>  8;
			  y1  =  (  pixel_16  &  0x00ff0000  )  >>  16;
			  v   =  (  pixel_16  &  0xff000000  )  >>  24;
#endif
			  y0  =  yuv[in];
			  u  =  yuv[in  +  1];
			  y1  =  yuv[in  +  2];
			  v  =  yuv[in  +  3];

#if  0
			  pixel32  =  convert_yuv_to_rgb_pixel(  y0,  u,  v  );

			  pixel_24[0]  =  (  pixel32  &  0x000000ff  );
			  pixel_24[1]  =  (  pixel32  &  0x0000ff00  )  >>  8;
			  pixel_24[2]  =  (  pixel32  &  0x00ff0000  )  >>  16;

			  rgb[out]  =  pixel_24[0];
			  rgb[out+1]  =  pixel_24[1];
			  rgb[out+2]  =  pixel_24[2];
#endif

			  M_yuvtorgb(  y0,  u,  v,  b,  g,  r,  c,  d,  e  );

			  rgb[out]  =  b;
			  rgb[out  +  1]  =  g;
			  rgb[out  +  2]  =  r;
#if  0
			  pixel32  =  convert_yuv_to_rgb_pixel(y1,  u,  v  );

			  pixel_24[0]  =  (  pixel32  &  0x000000ff  );
			  pixel_24[1]  =  (  pixel32  &  0x0000ff00  )  >>  8;
			  pixel_24[2]  =  (  pixel32  &  0x00ff0000  )  >>  16;

			  rgb[out+3]  =  pixel_24[0];
			  rgb[out+4]  =  pixel_24[1];
			  rgb[out+5]  =  pixel_24[2];
#endif

			  M_yuvtorgb(  y1,  u,  v,  b,  g,  r,  c,  d,  e  );

			  rgb[out  +  3]  =  b;
			  rgb[out  +  4]  =  g;
			  rgb[out  +  5]  =  r;

	 
		 }
	}

	return  0;
}

 //  2012/02/23
  int  uyvyToRgb24(  void  *  pCusModulesParam,  unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height,  BOOL  bFlipImg  )
{

#ifdef  __SUPPORT_qyMc_ipp__
		//QY_MC	*	pQyMc	=	
	    CUS_MODULES  *  pCusModules  =  (  CUS_MODULES  *  )pCusModulesParam;
		
		//  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "uyvyToRgb24 before ipp"  )  );

		if  (  pCusModules
			&&  pCusModules->pIpp  
			&&  pCusModules->pIpp->compress.mgr.pf_uyvyToRgb24  
			//  &&  bFlipImg  
			)  
		{	

			//  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "uyvyToRgb24 here"  )  );

			//  2011/12/03
			return  pCusModules->pIpp->compress.mgr.pf_uyvyToRgb24(  yuv,  (  unsigned  char  *  )rgb,  width,  height,  bFlipImg  );
		}

#endif


	//
	if  (  width  <=  0  ||  height  <=  0  )  {
		OutputDebugString(  _T(  "yuy2reg24 failed, width or height <=  0"  )  );
		return  -1;
	}
	unsigned  int	in,  out  =  0;
	//  unsigned  int	pixel_16;
	//  unsigned  char  pixel_24[3];
	//  unsigned  int	pixel32;
	int  y0,  u,  y1,  v;
	int				i,  j;
	int				nBytesPerLine_rgb24	=	(  width  *  24  +  31  )  /  32  *  4;


	int  y,  c,  d,  e;
	int  r,  g,  b;


	for  (  j  =  0;  j  <  (  int  )height;  j  ++  )  {
		 for  (  i  =  0;  i  <  (  int  )width;  i  +=  2  )  {
			  in  =  j  *  width  *  2  +  i  *  2;
			  out  =  (  height  -  j  -  1  )  *  nBytesPerLine_rgb24  +  i  *  3;  
	
			  u  =  yuv[in];
			  y0  =  yuv[in  +  1];
			  v  =  yuv[in  +  2];
			  y1  =  yuv[in  +  3];


			  M_yuvtorgb(  y0,  u,  v,  b,  g,  r,  c,  d,  e  );

			  rgb[out]  =  b;
			  rgb[out  +  1]  =  g;
			  rgb[out  +  2]  =  r;

			  M_yuvtorgb(  y1,  u,  v,  b,  g,  r,  c,  d,  e  );

			  rgb[out  +  3]  =  b;
			  rgb[out  +  4]  =  g;
			  rgb[out  +  5]  =  r;

	 
		 }
	}

	return  0;
}



 //  2012/01/03
  int  hdycToRgb24(  void  *  pCusModulesParam,  unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height,  BOOL  bFlipImg  )
{
#ifdef  __SUPPORT_qyMc_ipp__
		//  QY_MC	*	pQyMc	=	

	#if  0
		if  (  pQyMc->cusModules.pIpp  
			&&  pQyMc->cusModules.pIpp->compress.mgr.pf_yuy2ToRgb24  
			&&  bFlipImg  )  
		{	
			//  2011/12/03
			return  pQyMc->cusModules.pIpp->compress.mgr.pf_yuy2ToRgb24(  yuv,  (  unsigned  char  *  )rgb,  width,  height,  bFlipImg  );
		}
	#endif

#endif


	//
	if  (  width  <=  0  ||  height  <=  0  )  {
		OutputDebugString(  _T(  "yuy2reg24 failed, width or height <=  0"  )  );
		return  -1;
	}
	unsigned  int	in,  out  =  0;
	//  unsigned  int	pixel_16;
	//  unsigned  char  pixel_24[3];
	//  unsigned  int	pixel32;
	int  y0,  u,  y1,  v;
	int				i,  j;
	int				nBytesPerLine_rgb24	=	(  width  *  24  +  31  )  /  32  *  4;


	int  y,  c,  d,  e;
	int  r,  g,  b;


	for  (  j  =  0;  j  <  (  int  )height;  j  ++  )  {
		 for  (  i  =  0;  i  <  (  int  )width;  i  +=  2  )  {
			  in  =  j  *  width  *  2  +  i  *  2;
			  out  =  (  height  -  j  -  1  )  *  nBytesPerLine_rgb24  +  i  *  3;  
	
			  u  =  yuv[in];
			  y0  =  yuv[in  +  1];
			  v  =  yuv[in  +  2];
			  y1  =  yuv[in  +  3];

			  M_yuvtorgb(  y0,  u,  v,  b,  g,  r,  c,  d,  e  );

			  rgb[out]  =  b;
			  rgb[out  +  1]  =  g;
			  rgb[out  +  2]  =  r;

			  M_yuvtorgb(  y1,  u,  v,  b,  g,  r,  c,  d,  e  );

			  rgb[out  +  3]  =  b;
			  rgb[out  +  4]  =  g;
			  rgb[out  +  5]  =  r;

	 
		 }
	}

	return  0;
}


#endif

  //
#if  0  //  2013/09/20
  int  convert_rgb_to_yuv_pixel(  int  r,  int  g,  int  b  )
{
	unsigned  int  pixel32  =  0;
	unsigned  char  *  pixel  =  (  unsigned  char  *  )&pixel32;
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
	pixel[0]  =  y;
	pixel[1]  =  u;
	pixel[2]  =  v;

	return  pixel32;
}
#endif


  int  rgb24ToYuy2(  unsigned  char  *  rgb,  unsigned  char  *  yuy2,  int  width,  int  height  )
{
	if  (  width  <=  0  ||  height  <=  0  )  {
		return  -1;
	}

	unsigned  int  in,  out  =  0;
	//  unsigned  int  pixel32;
	BYTE  y0,  u0,  v0,  y1,  u1,  v1;
	int				i,  j;
	int				nBytesPerLine_rgb24	=	(  width  *  24  +  31  )  /  32  *  4;

	for  (  j  =  0;  j  <  height;  j  ++  )  {
		 for  (  i  =  0;  i  <  width;  i  +=  2  )  {
			  in  =  (  height  -  j  -  1  )  *  nBytesPerLine_rgb24  +  i  *  3;  
			  out  =  j  *  width  *  2  +  i  *  2;
			  //
#if  0
			  pixel32  =  convert_rgb_to_yuv_pixel(  rgb[in  +  2],  rgb[in  +  1],  rgb[in]  );
			  y0  =  (  pixel32  &  0x000000ff  );
			  u0  =  (  pixel32  &  0x0000ff00  )  >>  8;
			  v0  =  (  pixel32  &  0x00ff0000  )  >>  16;
#endif
			  convert_rgb_to_yuv_pixel(  rgb[in  +  2],  rgb[in  +  1],  rgb[in],  &y0,  &u0,  &v0  );

#if  0
			  pixel32  =  convert_rgb_to_yuv_pixel(  rgb[in  +  5],  rgb[in  +  4],  rgb[in  +  3]  );
			  y1  =  (  pixel32  &  0x000000ff  );
			  u1  =  (  pixel32  &  0x0000ff00  )  >>  8;
			  v1  =  (  pixel32  &  0x00ff0000  )  >>  16;
#endif
			  convert_rgb_to_yuv_pixel(  rgb[in  +  5],  rgb[in  +  4],  rgb[in  +  3],  &y1,  &u1,  &v1  );
			  //
			  yuy2[out  ++  ]  =  y0;
			  yuy2[out  ++  ]  =  (  u0  +  u1  )  /  2;
			  yuy2[out  ++  ]  =  y1;
			  yuy2[out  ++  ]  =  (  v0  +  v1  )  /  2;
		 }
	}

	return  0;
}

