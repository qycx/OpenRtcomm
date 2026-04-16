//--------------------------------------------------------------------------------------
// File: Tutorial08.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------

//



#ifndef  __C__

#define		__DEBUG_hlsl__

//
Texture2D txDiffuse;
Texture2D txMask;

SamplerState samLinear
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

#if  10
BlendState AdditiveBlending
{
    AlphaToCoverageEnable = FALSE;
    BlendEnable[0] = TRUE;
    SrcBlend = SRC_ALPHA;
    DestBlend = INV_SRC_ALPHA;	//  ONE;
    BlendOp = ADD;
    SrcBlendAlpha = ZERO;
    DestBlendAlpha = ZERO;
    BlendOpAlpha = ADD;
    RenderTargetWriteMask[0] = 0x0F;
};
#endif


cbuffer cbNeverChanges
{
    matrix View;
};

cbuffer cbChangeOnResize
{
    matrix Projection;
};

cbuffer cbChangesEveryFrame
{
    matrix World;
    float4 vMeshColor;
};

struct VS_INPUT
{
    float4 Pos : POSITION;
    float2 Tex : TEXCOORD;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
};

#define		MY_float3					float3
#define		MY_float4					float4
#define		MY_RGB						float3
#define		MY_RGBA						float4
//
#define		MY_uniform					uniform
#define		MY_out						out
#define		MY_static					static

//
#define		CONST_alphaArrayCnt					256
#define		CONST_imgKeysCnt					10

//
typedef  struct  colorDistance_keys_res			{
				 int							iErr;
				 int							ucIndex_key;
				 float							distanceVal;
}		MY_colorDistance_keys_res;

//
#define		to_MY_float3(x,y,z)					float3(x,y,z)
#define		to_MY_float4(x,y,z,w)				float4(x,y,z,w)
#define		to_MY_RGB(x,y,z)					float3(x,y,z)

#define		myRound(x)							round(x)


//
#define  myabs(x)  abs(x)


#endif


//////////////////





//
MY_uniform	int									g_cfg_usCnt  =  0;
//
MY_uniform	MY_float3							g_cfg_keys_rgb_key[CONST_imgKeysCnt];

//
MY_uniform  MY_float3							g_cfg_keys_hsl_key[CONST_imgKeysCnt];
//
MY_uniform  float								g_cfg_keys_alphaArray[CONST_imgKeysCnt  *  CONST_alphaArrayCnt];

//
MY_uniform	int									g_iImgW  =  640;
MY_uniform	int									g_iImgH  =  480;

//
MY_uniform  int									g_lBlurSize;

//
MY_uniform  float								g_ws_preBlur[21];
MY_uniform  float								g_ws_postBlur[21];


//
MY_uniform  int									g_tn_modified  =  0;	//  FALSE;

//
MY_static  int									s_tn_modified  =  0;



//
MY_float4  hlsl_rgbToHsl_f( float  r,  float g,  float b,  float  a );


//
#ifdef  __DEBUG_hlsl__
MY_float4 debugSth(  )
{
	MY_float4	f4;
	f4.x  =  0;
	f4.y  =  0;
	f4.z  =  0;
	f4.w  =  0;
	//
#if  0
	f4.x  =  g_cfg_0_rgb_key.x;
	f4.y  =  g_cfg_0_rgb_key.y;
	f4.z  =  g_cfg_0_rgb_key.z;
	f4.w  =  1;
#endif

	return  f4;

}


#endif

//
#if  0
 MY_float3  rgb2yuv( MY_float3 rgb  )
{
#if  0
	const float4x4 yuvMat  =  { 0.257,  -0.148,   0.439,  0.0,
				0.504,	-0.291,  -0.368,  0.0,
				0.098,   0.439,  -0.071,  0.0,
				0.0625,  0.50,    0.50,   1.0  };
#endif

//	float4 yuvx = (  float4  )0;
// 	yuvx  =  mul( float4(rgb.rgb, 1.0), yuvMat );

	float  y  =  0.257  *  rgb.r  +  0.504  *  rgb.g  +  0.098  *  rgb.b  +  0.0625;
	float  cb  =  -0.148  *  rgb.r  -  0.291  *  rgb.g  +  0.439  *  rgb.b  +  0.50;
	float  cr  =  0.439  *  rgb.r  -  0.368  *  rgb.g  -  0.071  *  rgb.b  +  0.50;
	

	return  float3(  y,  cb,  cr  );
}
#endif


float  hlsl_colorDistance(  MY_float3 color_hsl_p,  MY_float3  color_hsl_key  )
{
	float  h_p  =  color_hsl_p.x;
	float  h_key  =  color_hsl_key.x;
#if  10
	float  res0  =  myabs((float)(  h_p  +  1  -  h_key  ));		//  abs(  h1  +  1  -  h2  );
	float  res1  =  myabs(  h_p  -  h_key  );			//  abs(  h1  -  h2  );
	float  res2  =  myabs(  h_p  -  1  -  h_key  );		//  abs(  h1  -  1  -  h2  );
	
	float  res  =  min(  res0,  res1  );
	res  =  min(  res,  res2  );
	return  res;
#endif

	return  0;
}





 colorDistance_keys_res  hlsl_getColorDistance_keys(  MY_float3 p_xyz  )
{
	colorDistance_keys_res	res;	//  =  (  colorDistance_keys_res  )0;
	res.iErr  =  0;
	res.ucIndex_key  =  0;
	res.distanceVal  =  0;

	//
	float	tmp		=	0;
	int  i  =  0;
	float  tmp1	=	0;
	int	ucIndex  =  0;
	
	res.iErr  =  -1;

	if  (  !g_cfg_usCnt  )  {
		return  res;
	}


	for  (  i  =  0;  i  <  g_cfg_usCnt;  i  ++  )  {

		tmp1  =  hlsl_colorDistance(  p_xyz,  g_cfg_keys_hsl_key[i]  );

#if  0
		 //
		 if  (  tmp1  <  cfg.keyCfgs[i].tola  )  {
			 tmp  =  tmp1;			 
			 ucIndex  =  i;
			break;
		 }
#endif


		 //
		 if  (  !i  )  {
			 tmp  =  tmp1;
			 ucIndex  =  0;
			 }
		 else  if  (  tmp  >  tmp1  )  {
				   tmp  =  tmp1;			 
				   ucIndex  =  i;
		 }

	}
	
	res.iErr  =  0;


//  errLabel:


	if  (  !res.iErr  )  {
		res.distanceVal  =  tmp;
		res.ucIndex_key  =  ucIndex;
	}

	return  res;
}


int  hlsl_init(  )
{	
	if  (  g_tn_modified  ==  s_tn_modified  )  return  0;
	
	int  i  =  0;
	if  (  g_cfg_usCnt  >  CONST_imgKeysCnt  )  return  -1;

	//
	s_tn_modified  =  g_tn_modified;

	return  0;
}


////////////////////////////////////

 float HueToRgb(float p, float q, float t)
{
	if (t < 0.0f ) t += 1.0f;
	if (t > 1.0f ) t -= 1.0f;
	if (t < 1.0f/6.0f) return p + ( q - p) * 6.0f * t;
	if (t < 1.0f/2.0f) return q;
	if (t < 2.0f/3.0f) return p + ( q - p) * (2.0f / 3.0f - t) * 6.0f;

	return p;
}


 MY_float4  hlsl_hslToRgb_f( float hsl_X,  float  hsl_Y,  float  hsl_Z,  float  hsl_W  )
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

	
	MY_float4 color_res;
	color_res.x  =  r;
	color_res.y  =  g;
	color_res.z  =  b;
	color_res.w  =  a;

	return  color_res;
}

 MY_float4  hlsl_rgbToHsl_f( float  r,  float g,  float b,  float  a )
{
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
		//  s = (l > 0.5f) ? d / (2.0f - max - min) : d / (max + min);
		float  tmp_m;
		tmp_m = (l > 0.5f) ? (2.0f - max - min) : (max + min);
		if  (  myabs(  tmp_m  )  <  0.00001  )  tmp_m  =  0.00001;
		s  =  d  /  tmp_m;
		
		float  tmp_d;
		tmp_d  =  d;
		if  (  myabs(  tmp_d  )  <  0.00001  )  tmp_d  =  0.00001;

		if (r > g && r > b)
			h = (g - b) / tmp_d + (g < b ? 6.0f : 0.0f);

		else if (g > b)
			h = (b - r) / tmp_d + 2.0f;

		else
			h = (r - g) / tmp_d + 4.0f;

		h /= 6.0f;

	}

	MY_float4 hsl_res;

	//  return new Vector4(h, s, l, rgba.A / 2555.0f);
	hsl_res.x  =  h;
	hsl_res.y  =  s;
	hsl_res.z  =  l;
	hsl_res.w  =  a;

	return  hsl_res;
}




////////////////////////
 MY_float4  hlsl_procChromaKey(  MY_RGBA  p_rgba  )
{
	
	//
	//  MY_float4  hlsl_rgbToHsl_f( float  r,  float g,  float b,  float  a );
	
	MY_float4  p_hsla;
	p_hsla  =  hlsl_rgbToHsl_f(  p_rgba.r,  p_rgba.g,  p_rgba.b,  p_rgba.a  );
	

	// colorDistance_keys_res  hlsl_getColorDistance_keys(  HLSL_imgProcessCfg  cfg,  MY_float3 p_xyz  );


	colorDistance_keys_res  res;	//  =  (  colorDistance_keys_res  )0;
	
	res  =  hlsl_getColorDistance_keys(  to_MY_float3(  p_hsla.x,  p_hsla.y,  p_hsla.z  )  );

	//
	int  index_key_minA  =  res.ucIndex_key;
    int  minA  =  res.distanceVal  *  240;
	
			  
	if  (  index_key_minA  >=  CONST_imgKeysCnt  )  index_key_minA  =  0;
	if  (  minA  >=  CONST_alphaArrayCnt  )  minA  =  CONST_alphaArrayCnt  -  1;
	
	float  a  =  g_cfg_keys_alphaArray[index_key_minA  *  CONST_alphaArrayCnt  +  minA];
	
	return  to_MY_float4(  p_rgba.r,  p_rgba.g,  p_rgba.b,  a  );

}



#ifndef  __C__

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( VS_INPUT input )
{
    PS_INPUT output = (PS_INPUT)0;
    output.Pos = mul( input.Pos, World );
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );
    output.Tex = input.Tex;
    
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------

float4 PS( PS_INPUT input) : SV_Target
{
	float4  p_rgb  =  txDiffuse.Sample( samLinear, input.Tex );

#if  0	//  for test
	float4 p_hsl;
	rgbToHsl_f(  p_rgb.r,  p_rgb.g,  p_rgb.b,  p_rgb.a, p_hsl  );
	hslToRgb_f(  p_hsl.x,  p_hsl.y,  p_hsl.z,  p_hsl.w,  p_rgb  );
	//  p_rgb.r  =  1.;
#endif

	return  p_rgb;
}




float4 PS_preBlur_x( PS_INPUT input) : SV_Target
{
	//
	hlsl_init(  );
	
	float  fW  =  g_iImgW;
	if  (  fW  <  256.0f  )  fW  =  256.0f;

	//
	float blurStep_x  =  1.0  /  fW;
	//
#if  0
	float  w0  =  0.15915494f;
	float  w1  =  0.096532352f;
	float  w2  =  0.021539278f;
	float  w3  =  0.0017680516f;
	float  w4  =  0.000053390533f;
	float  normal  =  w0  +  2  *  (  w1  +  w2  +  w3  +  w4  );
	w0  =  w0  /  normal;
	w1  =  w1  /  normal;
	w2  =  w2  /  normal;
	w3  =  w3  /  normal;
	w4  =  w4  /  normal;
#else
	float  w0  =  g_ws_preBlur[4];
	float  w1  =  g_ws_preBlur[3];
	float  w2  =  g_ws_preBlur[2];
	float  w3  =  g_ws_preBlur[1];
	float  w4  =  g_ws_preBlur[0];
#endif


	float4  p_rgb  =  float4(  0,0,0,0  );	//  txDiffuse.Sample( samLinear, input.Tex );
	p_rgb  +=  txDiffuse.Sample( samLinear, float2(input.Tex.x  -  4.0  *  blurStep_x,  input.Tex.y  )  )  *  w4;
	p_rgb  +=  txDiffuse.Sample( samLinear, float2(input.Tex.x  -  3.0  *  blurStep_x,  input.Tex.y  )  )  *  w3;
	p_rgb  +=  txDiffuse.Sample( samLinear, float2(input.Tex.x  -  2.0  *  blurStep_x,  input.Tex.y  )  )  *  w2;
	p_rgb  +=  txDiffuse.Sample( samLinear, float2(input.Tex.x  -  1.0  *  blurStep_x,  input.Tex.y  )  )  *  w1;
	p_rgb  +=  txDiffuse.Sample( samLinear, float2(input.Tex.x,  input.Tex.y  )  )  		       *  w0;
	p_rgb  +=  txDiffuse.Sample( samLinear, float2(input.Tex.x  +  1.0  *  blurStep_x,  input.Tex.y  )  )  *  w1;
	p_rgb  +=  txDiffuse.Sample( samLinear, float2(input.Tex.x  +  2.0  *  blurStep_x,  input.Tex.y  )  )  *  w2;
	p_rgb  +=  txDiffuse.Sample( samLinear, float2(input.Tex.x  +  3.0  *  blurStep_x,  input.Tex.y  )  )  *  w3;
	p_rgb  +=  txDiffuse.Sample( samLinear, float2(input.Tex.x  +  4.0  *  blurStep_x,  input.Tex.y  )  )  *  w4;

	return  p_rgb;
}


float4 PS_preBlur_y( PS_INPUT input) : SV_Target
{
	float  fH  =  g_iImgH;
	if  (  fH  <  256.0f  )  fH  =  256.0f;
	//
	float blurStep_y  =  1.0  /  fH;
	//
	//
#if  0
	float  w0  =  1.0f;
	float  w1  =  0.9f;
	float  w2  =  0.55f;
	float  w3  =  0.18f;
	float  w4  =  0.1f;
	float  normal  =  w0  +  2  *  (  w1  +  w2  +  w3  +  w4  );
	w0  =  w0  /  normal;
	w1  =  w1  /  normal;
	w2  =  w2  /  normal;
	w3  =  w3  /  normal;
	w4  =  w4  /  normal;
#else
	float  w0  =  g_ws_preBlur[4];
	float  w1  =  g_ws_preBlur[3];
	float  w2  =  g_ws_preBlur[2];
	float  w3  =  g_ws_preBlur[1];
	float  w4  =  g_ws_preBlur[0];
#endif


	float4  p_rgb  =  float4(  0,0,0,0  );	//  txDiffuse.Sample( samLinear, input.Tex );
	p_rgb  +=  txDiffuse.Sample( samLinear, float2(input.Tex.x,  input.Tex.y  -  4.0  *  blurStep_y  )  )  *  w4;
	p_rgb  +=  txDiffuse.Sample( samLinear, float2(input.Tex.x,  input.Tex.y  -  3.0  *  blurStep_y  )  )  *  w3;
	p_rgb  +=  txDiffuse.Sample( samLinear, float2(input.Tex.x,  input.Tex.y  -  2.0  *  blurStep_y  )  )  *  w2;
	p_rgb  +=  txDiffuse.Sample( samLinear, float2(input.Tex.x,  input.Tex.y  -  1.0  *  blurStep_y  )  )  *  w1;
	p_rgb  +=  txDiffuse.Sample( samLinear, float2(input.Tex.x,  input.Tex.y  )  )  		       *  w0;
	p_rgb  +=  txDiffuse.Sample( samLinear, float2(input.Tex.x,  input.Tex.y  +  1.0  *  blurStep_y  )  )  *  w1;
	p_rgb  +=  txDiffuse.Sample( samLinear, float2(input.Tex.x,  input.Tex.y  +  2.0  *  blurStep_y  )  )  *  w2;
	p_rgb  +=  txDiffuse.Sample( samLinear, float2(input.Tex.x,  input.Tex.y  +  3.0  *  blurStep_y  )  )  *  w3;
	p_rgb  +=  txDiffuse.Sample( samLinear, float2(input.Tex.x,  input.Tex.y  +  4.0  *  blurStep_y  )  )  *  w4;

	return  p_rgb;
}


float4 PS_chromaKey( PS_INPUT input) : SV_Target
{

	//  float4  p_rgb  =  txDiffuse.Sample( samLinear, input.Tex );
	float4  p_rgba  =  txMask.Sample(  samLinear,  input.Tex  );

	// 
	float4  f4; 
	  f4  =  hlsl_procChromaKey(  p_rgba  );

	  p_rgba.a  =  f4.w;
	return  p_rgba;
	
	//
	return  float4(  1.,0,0,1.);
    //  return txDiffuse.Sample( samLinear, input.Tex ) * vMeshColor;
	return txDiffuse.Sample( samLinear, input.Tex );
}



float4 PS_postBlur_x( PS_INPUT input) : SV_Target
{
	float  fW  =  g_iImgW;
	if  (  fW  <  256.0f  )  fW  =  256.0f;
	//
	float blurStep_x  =  1.0  /  fW;
	//
#if  0
	float  w0  =  0.039788734f;
	float  w1  =  0.035113435f;
	float  w2  =  0.024133088f;
	float  w3  =  0.012917511f;
	float  w4  =  0.0053848196f;
	float  normal  =  w0  +  2  *  (  w1  +  w2  +  w3  +  w4  );
	w0  =  w0  /  normal;
	w1  =  w1  /  normal;
	w2  =  w2  /  normal;
	w3  =  w3  /  normal;
	w4  =  w4  /  normal;
#else
	float  w0  =  g_ws_postBlur[4];
	float  w1  =  g_ws_postBlur[3];
	float  w2  =  g_ws_postBlur[2];
	float  w3  =  g_ws_postBlur[1];
	float  w4  =  g_ws_postBlur[0];
#endif

	float4  p_rgb  =  txMask.Sample( samLinear, input.Tex );

	float  p_a  =  0.;	//  txDiffuse.Sample( samLinear, input.Tex );
	p_a  +=  txMask.Sample( samLinear, float2(input.Tex.x  -  4.0  *  blurStep_x,  input.Tex.y  )  ).a  *  w4;
	p_a  +=  txMask.Sample( samLinear, float2(input.Tex.x  -  3.0  *  blurStep_x,  input.Tex.y  )  ).a  *  w3;
	p_a  +=  txMask.Sample( samLinear, float2(input.Tex.x  -  2.0  *  blurStep_x,  input.Tex.y  )  ).a  *  w2;
	p_a  +=  txMask.Sample( samLinear, float2(input.Tex.x  -  1.0  *  blurStep_x,  input.Tex.y  )  ).a  *  w1;
	p_a  +=  p_rgb.a								 		    *  w0;
	p_a  +=  txMask.Sample( samLinear, float2(input.Tex.x  +  1.0  *  blurStep_x,  input.Tex.y  )  ).a  *  w1;
	p_a  +=  txMask.Sample( samLinear, float2(input.Tex.x  +  2.0  *  blurStep_x,  input.Tex.y  )  ).a  *  w2;
	p_a  +=  txMask.Sample( samLinear, float2(input.Tex.x  +  3.0  *  blurStep_x,  input.Tex.y  )  ).a  *  w3;
	p_a  +=  txMask.Sample( samLinear, float2(input.Tex.x  +  4.0  *  blurStep_x,  input.Tex.y  )  ).a  *  w4;
	p_rgb.a  =  p_a;

	//  p_rgb.a  =  abs(  p_rgb.a  -  p_a  );

	return  p_rgb;
}

float4 PS_postBlur_y( PS_INPUT input) : SV_Target
{
	float  fH  =  g_iImgH;
	if  (  fH  <  256.0f  )  fH  =  256.0f;
	//
	float blurStep_y  =  1.0  /  fH;
	//
#if  0
	float  w0  =  1.0f;
	float  w1  =  0.9f;
	float  w2  =  0.55f;
	float  w3  =  0.18f;
	float  w4  =  0.1f;
	float  normal  =  w0  +  2  *  (  w1  +  w2  +  w3  +  w4  );
	w0  =  w0  /  normal;
	w1  =  w1  /  normal;
	w2  =  w2  /  normal;
	w3  =  w3  /  normal;
	w4  =  w4  /  normal;
#else
	float  w0  =  g_ws_postBlur[4];
	float  w1  =  g_ws_postBlur[3];
	float  w2  =  g_ws_postBlur[2];
	float  w3  =  g_ws_postBlur[1];
	float  w4  =  g_ws_postBlur[0];
#endif

	float4  p_rgb  =  txMask.Sample( samLinear, input.Tex );

	float  p_a  =  0.;	//  txDiffuse.Sample( samLinear, input.Tex );
	p_a  +=  txMask.Sample( samLinear, float2(input.Tex.x,  input.Tex.y  -  4.0  *  blurStep_y  )  ).a  *  w4;
	p_a  +=  txMask.Sample( samLinear, float2(input.Tex.x,  input.Tex.y  -  3.0  *  blurStep_y  )  ).a  *  w3;
	p_a  +=  txMask.Sample( samLinear, float2(input.Tex.x,  input.Tex.y  -  2.0  *  blurStep_y  )  ).a  *  w2;
	p_a  +=  txMask.Sample( samLinear, float2(input.Tex.x,  input.Tex.y  -  1.0  *  blurStep_y  )  ).a  *  w1;
	p_a  +=  p_rgb.a								 		    *  w0;
	p_a  +=  txMask.Sample( samLinear, float2(input.Tex.x,  input.Tex.y  +  1.0  *  blurStep_y  )  ).a  *  w1;
	p_a  +=  txMask.Sample( samLinear, float2(input.Tex.x,  input.Tex.y  +  2.0  *  blurStep_y  )  ).a  *  w2;
	p_a  +=  txMask.Sample( samLinear, float2(input.Tex.x,  input.Tex.y  +  3.0  *  blurStep_y  )  ).a  *  w3;
	p_a  +=  txMask.Sample( samLinear, float2(input.Tex.x,  input.Tex.y  +  4.0  *  blurStep_y  )  ).a  *  w4;
	p_rgb.a  =  p_a;


	//
	return  p_rgb;
}


float4 PS_blend( PS_INPUT input) : SV_Target
{
	float4  p_rgb  =  txDiffuse.Sample( samLinear, input.Tex );
	float4  p_rgb_mask  =  txMask.Sample( samLinear, input.Tex );

	//
#ifdef  __DEBUG_hlsl__	//  for test
	float4  f4  =  debugSth(  );
	#if  10
	if  (  (  int  )f4.x  ||  (  int  )f4.y  ||  (  int  )f4.z  ||  (  int  )f4.w  )  {
		return  f4;
	}
	#endif
#endif

	//
	return  float4(  p_rgb.rgb, p_rgb_mask.a  );
}



float4 PS_mask( PS_INPUT input) : SV_Target
{
	float4  p_rgb  =  txMask.Sample( samLinear, input.Tex );

	return  p_rgb;
}


//--------------------------------------------------------------------------------------
technique10 Render
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}


technique10 Render_preBlur_x
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS_preBlur_x() ) );
    }	
}

technique10 Render_preBlur_y
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS_preBlur_y() ) );
    }
}



technique10 Render_chromaKey
{
    pass P0
    {
//	SetBlendState(  AdditiveBlending,  float4(0.0f,0.0f,0.0f,0.0f), 0xffffffff  );
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS_chromaKey() ) );
    }
}


technique10 Render_postBlur_x
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS_postBlur_x() ) );
    }
}

technique10 Render_postBlur_y
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS_postBlur_y() ) );
    }
}



technique10 Render_blend
{
    pass P0
    {
		SetBlendState(  AdditiveBlending,  float4(0.0f,0.0f,0.0f,0.0f), 0xffffffff  );
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS_blend() ) );
    }
}

technique10 Render_mask
{
    pass P0
    {
		SetBlendState(  AdditiveBlending,  float4(0.0f,0.0f,0.0f,0.0f), 0xffffffff  );
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS_mask() ) );
    }
}

#endif


