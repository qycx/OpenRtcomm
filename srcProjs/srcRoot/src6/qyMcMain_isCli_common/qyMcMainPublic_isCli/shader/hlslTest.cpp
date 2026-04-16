

#include	"stdafx.h"
#include	<tchar.h>
#include	<math.h>
#include	"colorSpaceFunc.h"
#include	"qyMcMainCommon.h"
#include	"imgProcessPublic.h"

#define		__C__









	

#include	"qisChromaKey.fx"


 int  hslToRgb_f( float hsl_X,  float  hsl_Y,  float  hsl_Z,  float  hsl_W,  BYTE  *  ucpR,  BYTE  *  ucpG,  BYTE  *  ucpB,  BYTE  *  ucpA  )
{
	float r, g, b, a;

	MY_float4	color_res  =  hlsl_hslToRgb_f(  hsl_X,  hsl_Y,  hsl_Z,  hsl_W  );
	r  =  color_res.x;
	g  =  color_res.y;
	b  =  color_res.z;
	a  =  color_res.w;

	//
	WORD  wR,  wG,  wB,  wA;
	r  =  255  *  r;
	wR  =  myRound(  r  );
	g  =  255  *  g;
	wG  =  myRound(  g  );
	b  =  255  *  b;
	wB  =  myRound(  b  );
	a  =  255  *  a;
	wA  =  myRound(  a  );
	//
	clip255(  wR  );
	clip255(  wG  );
	clip255(  wB  );
	clip255(  wA  );

	//  return new Color((int)(r * 255), (int)(g * 255), (int)(b * 255), (int)(hsl.W * 255) );
	  
	if  (  ucpR  )  *ucpR  =  wR;
	if  (  ucpG  )  *ucpG  =  wG;
	if  (  ucpB  )  *ucpB  =  wB;
	if  (  ucpA  )  *ucpA  =  wA;

	return  0;
}

  int  rgbToHsl_f( BYTE  rgba_R,  BYTE  rgba_G,  BYTE  rgba_B,  BYTE  rgba_A,  float  *  pfH,  float  *  pfS,  float  *  pfL,  float  *  pfA )
{
	float r = rgba_R / 255.0f;
	float g = rgba_G / 255.0f;
	float b = rgba_B / 255.0f;
	float a = rgba_A / 255.0f;

	MY_float4  res;
	res  =  hlsl_rgbToHsl_f(  r,  g,  b,  a  );

	float  h,  s,  l;
	h  =  res.x;
	s  =  res.y;
	l  =  res.z;

	//  return new Vector4(h, s, l, rgba.A / 2555.0f);
	if  (  pfH  )  *pfH  =  h;
	if  (  pfS  )  *pfS  =  s;
	if  (  pfL  )  *pfL  =  l;
	if  (  pfA  )  *pfA  =  a;

	return  0;
}




   