

#ifndef  __colorSpaceFunc_h__
#define  __colorSpaceFunc_h__




//  2011/12/05
#define		M_sizeImage(  bits,  biWidth,  biHeight  )		(  (  (  biWidth  )  *  (  bits  )  +  31  )  /  32  *  4  *  (  biHeight  )  )
//  #define		M_rgb24SizeImage(  biWidth,  biHeight  )	  (  (  (  biWidth  )  *  24  +  31  )  /  32  *  4  *  (  biHeight  )  )
#define		M_rgb24SizeImage(  biWidth,  biHeight  )		M_sizeImage(  24,  biWidth,  biHeight  )


//
#define		clip255(  v  )		if  (  (  v  )  <  0  )  (  v  )  =  0;  if  (  (  v  )  >  255  )  (  v  )  =  255;

//
#define		myRound( x )		(x)  =  (int)((x) + 0.5 - (double)((x) < 0) );

//
__declspec(  dllexport  ) int  convert_yuv_to_rgb_pixel(  int  y,  int  u,  int  v,  BYTE  *  pr,  BYTE  *  pg,  BYTE  *  pb  );
__declspec(  dllexport  ) int  convert_rgb_to_yuv_pixel(  int  r,  int  g,  int  b,  BYTE  *  py,  BYTE  *  pu,  BYTE  *  pv  );


//  这2个函数采用浮点数计算,不适合用来作转换.主要用在hlsl中
/// Input: Vector4 ( X: [0.0, 1.0], Y: [0.0, 1.0], Z: [0.0, 1.0], W: [0.0, 1.0] )
int  hslToRgb_f( float hsl_X,  float  hsl_Y,  float  hsl_Z,  float  hsl_W,  BYTE  *  ucpR,  BYTE  *  ucpG,  BYTE  *  ucpB,  BYTE  *  ucpA  );
int  rgbToHsl_f( BYTE  rgba_R,  BYTE  rgba_G,  BYTE  rgba_B,  BYTE  rgba_A,  float  *  pfH,  float  *  pfS,  float  *  pfL,  float  *  pfA );

//
#define		MAX_h_ms	240.

//
#if  0
	#define		__USE_hsl_chromaKey__
#endif

//
//  __declspec(  dllexport  )  int  convert_rgb_to_key_pixel(  int  r,  int  g,  int  b,  BYTE  *  pL,  BYTE  *  pH,  BYTE  *  pS  );
//  __declspec(  dllexport  )  int  convert_key_to_rgb_pixel(  int  l,  int  h,  int  s,  BYTE  *  pr,  BYTE  *  pg,  BYTE  *  pb  );
__declspec(  dllexport  )  int  convert_rgb_to_key_pixel(  int  r,  int  g,  int  b,  BYTE  *  pX,  BYTE  *  pY,  BYTE  *  pZ  );
__declspec(  dllexport  )  int  convert_key_to_rgb_pixel(  int  x,  int  y,  int  z,  BYTE  *  pr,  BYTE  *  pg,  BYTE  *  pb  );

#endif


