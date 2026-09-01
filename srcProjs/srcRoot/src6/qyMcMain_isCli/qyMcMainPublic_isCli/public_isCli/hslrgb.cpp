

#include	"stdafx.h"
#include	<tchar.h>
#include	"qyMcMainCommon.h"
#include	"colorSpaceFunc.h"

#if  0

 static float HueToRgb(float p, float q, float t)
{
	if (t < 0.0f ) t += 1.0f;
	if (t > 1.0f ) t -= 1.0f;
	if (t < 1.0f/6.0f) return p + ( q - p) * 6.0f * t;
	if (t < 1.0f/2.0f) return q;
	if (t < 2.0f/3.0f) return p + ( q - p) * (2.0f / 3.0f - t) * 6.0f;

	return p;
}


/// Converts an HSL color value to RGB
/// Input: Vector4 ( X: [0.0, 1.0], Y: [0.0, 1.0], Z: [0.0, 1.0], W: [0.0, 1.0] )
/// Output: Color ( R: [0, 255], G: [0, 255], B: [0, 255], A: [0, 255] )
/// <param name="hsl">Vector4 defining X = h, Y = s, Z = l, W = a. Ranges [0, 1.0] </param>
/// <returns>RGBA Color. Ranges [0, 255] </returns>

 // int  hslToRgb_f( float hsl_X,  float  hsl_Y,  float  hsl_Z,  float  hsl_W,  out  float4 color_res  )
 int  hslToRgb_f( float hsl_X,  float  hsl_Y,  float  hsl_Z,  float  hsl_W,  BYTE  *  ucpR,  BYTE  *  ucpG,  BYTE  *  ucpB,  BYTE  *  ucpA  )
{
	float r, g, b, a;
	
	if (hsl_Y == 0.0f) {
		r = g = b = hsl_Z;
		}
	else 
	{
		float q = hsl_Z < 0.5f ? hsl_Z * (1.0f + hsl_Y) : hsl_Z + hsl_Y - hsl_Z * hsl_Y;
		float p = 2.0f * hsl_Z - q;
		r  =  HueToRgb(p, q, hsl_X + 1.0f / 3.0f );
		g  =  HueToRgb(p, q, hsl_X);
		b  =  HueToRgb(p, q, hsl_X - 1.0f / 3.0f );
	}
	//
	a  =  hsl_W;
	


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



/// Converts an RGBA color value to HSL.
/// Input: Color ( R: [0, 255], G: [0, 255], B: [0, 255], A: [0, 255] )
/// Output: Vector4 ( X: [0.0, 1.0], Y: [0.0, 1.0], Z: [0.0, 1.0], W: [0.0, 1.0] )
/// <param name="hsl">Vector4 defining X = h, Y = s, Z = l, W = a. Ranges [0, 1.0] </param>
/// <returns>RGBA Color. Ranges [0, 255] </returns>
 //   int  rgbToHsl_f( float  r,  float g,  float b,  float  a,  out float4 hsl_res )
 int  rgbToHsl_f( BYTE  rgba_R,  BYTE  rgba_G,  BYTE  rgba_B,  BYTE  rgba_A,  float  *  pfH,  float  *  pfS,  float  *  pfL,  float  *  pfA )
{
	float r = rgba_R / 255.0f;
	float g = rgba_G / 255.0f;
	float b = rgba_B / 255.0f;
	float a = rgba_A / 255.0f;

	float max = ( r > g && r > b ) ? r : ( g > b ) ? g : b;
	float min = ( r < g && r < b ) ? r : ( g < b ) ? g : b;

	float h, s, l;
	h = s = l = ( max + min ) / 2.0f;
	
	if (max == min) {
		h = s = 0.0f;

		//
#ifdef  __DEBUG__	//  这是不定情况下.微软的取值
		h  =  160.  /  MAX_h_ms;
#endif
		}

	else 
	{
		float d = max - min;
		s = (l > 0.5f) ? d / (2.0f - max - min) : d / (max + min);

		if (r > g && r > b)
			h = (g - b) / d + (g < b ? 6.0f : 0.0f);

		else if (g > b)
			h = (b - r) / d + 2.0f;

		else
			h = (r - g) / d + 4.0f;

		h /= 6.0f;

	}

	//  return new Vector4(h, s, l, rgba.A / 2555.0f);
	if  (  pfH  )  *pfH  =  h;
	if  (  pfS  )  *pfS  =  s;
	if  (  pfL  )  *pfL  =  l;
	if  (  pfA  )  *pfA  =  a;

	return  0;
}

#endif



