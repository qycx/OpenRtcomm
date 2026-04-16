
#ifndef  __imgProcessPublic_h__
#define  __imgProcessPublic_h__		//  {

#include	"colorSpaceFunc.h"


//
/*
 * Format of RGBA colors is
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |    alpha      |      red      |     green     |     blue      |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
#define RGBA_getA(rgb)			((rgb) >> 24)
#define RGBA_getR(rgb)		    (((rgb) >> 16) & 0xff)
#define RGBA_getG(rgb)			(((rgb) >> 8) & 0xff)
#define RGBA_getB(rgb)			((rgb) & 0xff)
#define makeRGBA(r, g, b, a)	((COLORREF) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b)))	//((D3DCOLOR) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b)))

//
#define myD3DX_PI    ((FLOAT)  3.141592654f)





//
typedef  struct  __myFloat3__  {
				 float			x;
				 float			y;
				 float			z;
}		 MY_float3;

typedef  struct  __myFloat4__	{
				 float			x;
				 float			y;
				 float			z;
				 float			w;
}		 MY_float4;

typedef  struct  __myRGB_t		{
				 float			r;
				 float			g;
				 float			b;				
}		 MY_RGB;

typedef  struct  __myRGBA_t		{
				 float			r;
				 float			g;
				 float			b;				
				 float			a;
}		 MY_RGBA;

//
#define		MY_uniform		
#define		MY_out
#define		MY_static

//
typedef  struct  colorDistance_keys_res  {
				 int			iErr;
				 int			ucIndex_key;
				 float			distanceVal;
}		MY_colorDistance_keys_res;

//
#define		CONST_alphaArrayCnt					256
#define		CONST_imgKeysCnt					10


MY_float3  to_MY_float3(  float  x,  float  y,  float  z  );
MY_float4  to_MY_float4(  float  x,  float  y,  float  z,  float  w  );
MY_RGB  to_MY_RGB(  float  x,  float  y,  float  z  );
BYTE  toByte_rgb(  float  f_rgb  );
BYTE  toByte_hsl(  float  f_hsl  );
float  toFloat_rgb(  BYTE  uc_rgb  );
float  toFloat_hsl(  BYTE  uc_hsl  );

#define  myabs(x)  fabs(x)



//
#define		CONST_key_tola						5
#define		CONST_key_tolb						6


typedef  struct  __imgKey_t						{

				 //
				 MY_RGB							rgb_key;
				 MY_float3						hsl_key;
				 
				 //
				 int							tola;
				 int							tolb;

				 //
				 float							alphaArray[CONST_alphaArrayCnt];
				 
}		 IMG_key,  HLSL_imgKey;


typedef  struct  __imgProcessCfg_t				{
				 //
				 BOOL							bUseChromaKey;
				 
				 //
				 BYTE							minVal_r_g_b;
				 unsigned  short				usMin_saturation;		//  =  0.5f
				 unsigned  short				usMin_lightness;		//  =  0.3f
				 unsigned  short				usMax_lightness;		//  =  0.8f

				 
				 //
				 float							fSigma_preBlur;
				 float							fSigma_postBlur;
				 
				 //
				 int							lBlurSize;
				 float							ws_preBlur[21];
				 float							ws_postBlur[21];

				 //
				 float							fGamma;
				 
				 //
				 unsigned  short				usCnt;
				 IMG_key						keys[CONST_imgKeysCnt];

}		 IMG_process_cfg,  HLSL_imgProcessCfg;


typedef  struct  __keyingPixHelp_t				{

				 //
				 BYTE							a_org;
				 BYTE							r_org;
				 BYTE							g_org;
				 BYTE							b_org;
				 unsigned  int					tn_a_org;				//  tn_rgb_org从ctx里获取,如果将rgb_org存这里,就需要将tn_rgb_org赋值.这样和ctx的tn比较下,就知道是否最新了
				 
				 //
				 unsigned  int					distanceFromKey;
				 
				 //
				 unsigned  int					tn_ucbEdgeRelated;

}		 KEYING_pix_help;

typedef  struct  __keyingCtx_t					{
				 unsigned  int					tn;
				 KEYING_pix_help			*	pPixes;
}		 KEYING_ctx;


typedef  struct  __keyingImgDatas_t					{
				 BYTE							*	pData_org;
				 BYTE							*	pData;
				 BYTE							*	pData_tmp;		//  临时数据区, 在高斯滤波时用
				 BYTE							*	pData_mask;
				 BYTE							*	pData_bg;
				 BYTE							*	pData_blend;

}		 KEYING_img_datas;



__declspec(dllexport)  int   set_g_pQyMc_imgProcess(  void  *  pQyMc  );

//
class CCtxQyMc;

__declspec(  dllexport  )  int  init_imgProcess(  CCtxQyMc  *  pQyMc  );
__declspec(  dllexport  )  int  exit_imgProcess(  );


 __declspec(  dllexport  ) int  addColorKey(  BYTE  r,  BYTE  g,  BYTE  b,  unsigned  int  tola,  unsigned  int  tolb,  BOOL  bForce,  void  *  pIMG_process_cfg  );
 __declspec(  dllexport  ) int  delColorKey(  int  index,  void  *  pIMG_process_cfg  );

 __declspec(  dllexport  ) int  getColorDistance_keys(  int  h_p,  int  s_p,  void  *  pIMG_process_cfg,  unsigned  char  *  pucIndex_key,  float  *  pDistance  );
 
  __declspec(  dllexport  )  int calculateAlphaTables(  int  alpha255_in,  int  alpha255_out,  float  fMaskGamma,  float  alphaArray[256]  );
  __declspec(  dllexport  )  int  calculateWeights_blur(  float  fSigma,  int  lBlurSize,  float  *  ws,  unsigned  int  cnt_ws  );


 __declspec(  dllexport  )  int  getCurImgProcessCfg(  void  *  pIMG_process_cfg,  DWORD  *  pdwTickCnt_modifiedTime  );
 __declspec(  dllexport  ) int  refreshCurImgProcessCfg(  void  *  pIMG_process_cfg  );


__declspec(  dllexport  )  int  resetChromaKey(  );



#ifdef  __DEBUG__

 __declspec(  dllexport  )  int  startToParse(  );

 __declspec(  dllexport  )  int  testFunc_imgProcess(  );


#endif


__declspec(  dllexport  )  int  gaussianFilter_f(  int  lBlurSize,  float  *  ws,  unsigned  int  cnt_ws,  unsigned char  *  corrupted,  unsigned  char  *  tmpImg,  unsigned  char  *  smooth,  int  rgbIncrement,  int  width,  int  height  );
__declspec(  dllexport  )  int  gaussianFilter_a_f(  int  lBlurSize,  float  *  ws,  unsigned  int  cnt_ws,  unsigned char  *  corrupted,  unsigned  char  *  tmpImg,  unsigned  char  *  smooth,  int  rgbIncrement,  int  width,  int  height  );


__declspec(  dllexport  )  int  procChromaKey(  void  *  pProcInfo,  void  *  pKEYING_ctx,  void  *  pIMG_process_cfg,  BITMAPINFOHEADER  *  pBih,  BYTE  *  pData_src,  BOOL  bFlipImg  );
//
__declspec(  dllexport  )  int  test_procChromaKey(  void  *  pProcInfo,  void  *  pKEYING_ctx,  void  *  pIMG_process_cfg,  BITMAPINFOHEADER  *  pBih,  void  *  pKEYING_img_datas,  BOOL  bFlipImg  );


 __declspec(  dllexport  )  BOOL  bUseChromaKey(  );
 __declspec(  dllexport  )  BOOL  bImgProcessCfgNew(  DWORD  dwTickCnt_modified  );


__declspec(  dllexport  )  int  doPreChromaKey(  void  *  pProcInfo,  BITMAPINFOHEADER  *  pBih,  BYTE  *  pData,  BOOL  bFlipImg  );

//
__declspec(  dllexport  ) int resizeRgb24(  unsigned  char  *  src,  int  srcWidth,  int  srcHeight,  unsigned  char  *  dst,  int  dstWidth,  int  dstHeight  );




#endif  //  }


