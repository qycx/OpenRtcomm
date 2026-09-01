

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
//
static  int  siCtrl_chromaKey	=  0;
static  int	 simaxSi			=  20;

#ifdef  __DEBUG__

#endif

//
int ck_main( int argc, char **argv,  BITMAPINFOHEADER  *  pBih,  BYTE  *  pData  );


//
int  g_gaussian_templates[25]  =	{ 1,4,7,4,1,
									  4,16,26,16,4,
									  7,26,41,26,7,
									  4,16,26,16,4,
									  1,4,7,4,1  };



//
CCtxImgProcess::CCtxImgProcess(  )
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );

	COLORREF	colorKey  =  RGB(  0,  255,  0  );
	colorKey  =  0;//  RGB(  136,  226,  216  );
	int  tola  =  CONST_key_tola;
	int  tolb  =  CONST_key_tolb;



	//  0
	colorKey  =  RGB(  0,255,0  );
	addColorKey(  GetRValue(  colorKey  ),  GetGValue(  colorKey  ),  GetBValue(  colorKey  ),  tola  *  100,  tolb  *  100,  FALSE,  &m_var.new_Cfg  );
	
	m_var.new_Cfg.usMin_saturation  =  0.15f  *  240;		//  36
	m_var.new_Cfg.usMin_lightness  =  0.12f  *  240;		//  28.8
	m_var.new_Cfg.usMax_lightness  =  0.8f  *  240;		//  192
	//
#if  0
	{
		BYTE  ucR,  ucG,  ucB;
		convert_key_to_rgb_pixel(  m_var.new_Cfg.keys[0].cfg.ucY_key,  m_var.new_Cfg.keys[0].cfg.ucCb_key,  m_var.new_Cfg.keys[0].cfg.ucCr_key,  &ucR,  &ucG,  &ucB  );
	}
#endif

#if  0
	//  1
	colorKey  =  RGB(  180,191,176  );
	addColorKey(  GetRValue(  colorKey  ),  GetGValue(  colorKey  ),  GetBValue(  colorKey  ),  1.8,  2.4,  FALSE,  &m_var.new_Cfg  );
#endif

	//
	m_var.dwTickCnt_modified_new  =  GetTickCount(  );

}

CCtxImgProcess::~CCtxImgProcess(  )
{
	//  MACRO_safeFree(  m_var.pMems  );
}


//
CCtxImgProcess	gCtx_imgProcess;


#ifdef  __USE_hsl_chromaKey__

 float  colorDistance(  int  h_p,  int  s_p,  int  h_key,  int  s_key  )
{
#if  0

	int  res0  =  abs(  h_p  +  240  -  h_key  );	//  abs(  h1  +  1  -  h2  );
	int  res1  =  abs(  h_p  -  h_key  );			//  abs(  h1  -  h2  );
	int  res2  =  abs(  h_p  -  240  -  h_key  );	//  abs(  h1  -  1  -  h2  );
	
	int  res  =  min(  res0,  res1  );
	res  =  min(  res,  res2  );
	return  res;
#endif
	MY_float3  p_hsl;
	MY_float3  k_hsl;

	p_hsl.x  =  toFloat_hsl(  h_p  );
	p_hsl.y  =  toFloat_hsl(  s_p  );
	p_hsl.z  =  0;
	k_hsl.x  =  toFloat_hsl(  h_key  );
	k_hsl.y  =  toFloat_hsl(  s_key  );
	k_hsl.z  =  0;

	float  f  =  hlsl_colorDistance(  p_hsl,  k_hsl  );
	f  =  f  *  240;
	return  f;
}

#else


 float  colorDistance(  int  Cb_p,  int  Cr_p,  int  Cb_key,  int  Cr_key  )
{
	double tmp = sqrt(( double)( ( Cb_key - Cb_p)*(Cb_key-Cb_p) +  ( Cr_key - Cr_p)*(Cr_key-Cr_p) ));
	return  tmp  *  100;
}
#endif



__declspec(  dllexport  ) int  getColorDistance_keys(  int  h_p,  int  s_p,  void  *  pIMG_process_cfg,  unsigned  char  *  pucIndex_key,  float  *  pDistance  )
{ 
	int					iErr	=	-1;
	IMG_process_cfg  *  pCfg  =  (  IMG_process_cfg  *  )pIMG_process_cfg;
	unsigned  int	tmp		=	0;
	int  i  =  0;
	unsigned  char	ucIndex  =  0;

	colorDistance_keys_res	res;
	memset(&res, 0, sizeof(res));
	//res  =  hlsl_getColorDistance_keys(  to_MY_float3(  toFloat_hsl(  h_p  ),  toFloat_hsl(  s_p  ),  0  )  );
	if  (  res.iErr  )  goto  errLabel;
	tmp  =  res.distanceVal  *  MAX_h_ms;
	ucIndex  =  res.ucIndex_key;
		

	iErr  =  0;
errLabel:

	if  (  !iErr  )  {
		if  (  pDistance  )  *pDistance  =  tmp;
		if  (  pucIndex_key  )  *pucIndex_key  =  ucIndex;
	}
	return  iErr;
}


 __declspec(  dllexport  ) int  addColorKey(  BYTE  r,  BYTE  g,  BYTE  b,  unsigned  int  tola,  unsigned  int  tolb,  BOOL  bForce,  void  *  pIMG_process_cfg  )
{
	IMG_process_cfg  *  pMem  =  (  IMG_process_cfg  *  )pIMG_process_cfg;
	int	iErr	=	-1;
	//  BYTE  y,  cb,  cr;
	BYTE	x,y,z;
#if 10
	MACRO_qyAssert(  tola  <  tolb,  _T(  "tola  <  tolb"  )  );
	MACRO_qyAssert(  tola  >  0.,  _T(  "tola  >  0."  )  );

	if  (  tola  >=  tolb  )  return  -1;
	if  (  tola  <=  0.  )  return  -1;
#endif
	//		
	convert_rgb_to_key_pixel(  r,  g,  b,  &x,  &y,  &z  );

	//
	if  (  !bForce  )  {
		int  i;
		for  (  i  =  0;  i  <  pMem->usCnt;  i  ++  )  {
			 if  (  toByte_hsl(  pMem->keys[i].hsl_key.x  )  ==  x  )  		
			 {
				 break;		
			 }	
		}
		if  (  i  <  pMem->usCnt  )  {	//  已经在keys中了
			iErr  =  0;  goto  errLabel;	
		}
	}

	//		
	if  (  pMem->usCnt  ==  mycountof(  pMem->keys  )  )  {	//  keys满了
		goto  errLabel;
	}

	pMem->keys[pMem->usCnt].rgb_key.r  =  toFloat_rgb(  r  );	
	pMem->keys[pMem->usCnt].rgb_key.g  =  toFloat_rgb(  g  );								  
	pMem->keys[pMem->usCnt].rgb_key.b  =  toFloat_rgb(  b  );
								
	//
	pMem->keys[pMem->usCnt].hsl_key.x  =  toFloat_hsl(  x  );
	pMem->keys[pMem->usCnt].hsl_key.y  =  toFloat_hsl(  y  );		
	pMem->keys[pMem->usCnt].hsl_key.z  =  toFloat_hsl(  z  );

	//
	pMem->keys[pMem->usCnt].tola  =  tola;
	pMem->keys[pMem->usCnt].tolb  =  tolb;
	//
	pMem->usCnt  ++  ;

	iErr  =  0;
	
errLabel:
	return  iErr;
}


 __declspec(  dllexport  ) int  delColorKey(  int  index,  void  *  pIMG_process_cfg  )
{
	IMG_process_cfg  *  pMem  =  (  IMG_process_cfg  *  )pIMG_process_cfg;

	if  (  index  <  0  ||  index  >=  mycountof(  pMem->keys  )  )  return  -1;
	if  (  index  >=  pMem->usCnt  )  return  -1;

	int  i;
	for  (  i  =  index;  i  <  pMem->usCnt  -  1;  i  ++  )  {
		pMem->keys[i]  =  pMem->keys[i  +  1];
	}
	pMem->usCnt  --  ;

	return  0;
}

  __declspec(  dllexport  )  int  getCurImgProcessCfg(  void  *  pIMG_process_cfg,  DWORD  *  pdwTickCnt_modifiedTime  ) 
{
	IMG_process_cfg  *  pCfg  =  (  IMG_process_cfg  *  )pIMG_process_cfg;
	CCtxImgProcess  *  pCtx  =  &gCtx_imgProcess;

	//  memcpy(  pCfg,  &pCtx->m_var.cfg,  sizeof(  pCfg[0]  )  );
	memcpy(  pCfg,  &pCtx->m_var.new_Cfg,  sizeof(  pCfg[0]  )  );
	if  (  pdwTickCnt_modifiedTime  )  {
		*pdwTickCnt_modifiedTime  =  pCtx->m_var.dwTickCnt_modified_new;
	}

	return  0;
}

 __declspec(  dllexport  ) int  refreshCurImgProcessCfg(  void  *  pIMG_process_cfg  )
{
	IMG_process_cfg  *  pCfg  =  (  IMG_process_cfg  *  )pIMG_process_cfg;
	CCtxImgProcess  *  pCtx  =  &gCtx_imgProcess;

	if  (  pCfg->usCnt  >  mycountof(  pCfg->keys  )  )  {
#ifdef  __DEBUG__
		traceLog(  _T(  "refreshCurImProcessCfg failed, usCnt too big"  )  );
#endif
		return  -1;
	}

	if  (  memcmp(  pCfg,  &pCtx->m_var.new_Cfg,  sizeof(  pCfg[0]  )  )  )  {
		CQySyncObj	syncObj;
		if  (  syncObj.sync(  CONST_mutexName_syncImgProcessCfg  )  )  return  -1;

		memcpy(  &pCtx->m_var.new_Cfg,  pCfg,  sizeof(  pCtx->m_var.new_Cfg  )  );
		pCtx->m_var.dwTickCnt_modified_new  =  GetTickCount(  );
	}

	return  0;
}

__declspec(  dllexport  )  int  resetChromaKey(  )
{
#ifdef  __DEBUG__
	siCtrl_chromaKey  =  0;
	traceLog(  _T(  "resetChromaKey: to reinit chromaKey"  )  );
#endif

	//  startToParse(  );

	return  0;
}




 __declspec(  dllexport  )  BOOL  bUseChromaKey(  )
{
	//
	CCtxImgProcess  *  pCtx  =  &gCtx_imgProcess;

	return  pCtx->m_var.new_Cfg.bUseChromaKey;

}

 //  2013/10/31
 __declspec(  dllexport  )  BOOL  bImgProcessCfgNew(  DWORD  dwTickCnt_modified  )
 {
	CCtxImgProcess  *  pCtx  =  &gCtx_imgProcess;

	return  pCtx->m_var.dwTickCnt_modified_new  !=  dwTickCnt_modified;
 }


 __declspec(  dllexport  )  int  procChromaKey(  void  *  pProcInfo,  void  *  pKEYING_ctx,  void  *  pIMG_process_cfg,  BITMAPINFOHEADER  *  pBih,  BYTE  *  pData_src,  BOOL  bFlipImg  )
{
	int  iErr  =  -1;

#ifdef  __DEBUG__
		//  return  0;
#endif

	if  (  pBih->biCompression  !=  0  )  return  -1;
	switch  (  pBih->biBitCount  )  {
			case  32:
					break;
			default:
					#ifdef  __DEBUG__
							traceLog(  _T(  "procChromaKey failed, bih.bits %d"  ),  pBih->biBitCount  );
					#endif
					return  -1;
	}

	
	KEYING_ctx		*	pCtx	=	(  KEYING_ctx  *  )pKEYING_ctx;
	IMG_process_cfg  *  pCfg  =  (  IMG_process_cfg  *  )pIMG_process_cfg;

	if  (  !pCtx  )  return  -1;
	if  (  !pCtx->pPixes  )  {
#ifdef  __DEBUG__
		traceLog(  _T(  "procChromaKey failed: pCtx->pPixes is null"  )  );
#endif
		return  -1;
	}

	//
	int	 i,  j;
	unsigned  char  *  rgb  =  NULL;

	int	 a,  r,  g,  b;
	BYTE	l,  h,  s;
	
	unsigned  char  *  rgbPtr	=	NULL;
	unsigned  int  rgbIncrement  =  pBih->biBitCount  /  8;
	int				lineBytes_src	=	M_lineBytes_rgb(  32,  pBih->biWidth  );

	//
	KEYING_pix_help  *  pPix  =  NULL;
		
	//
	int  width  =  0;
	int  height  =  0;
	
	width  =  pBih->biWidth;
	height  =  pBih->biHeight;
	

	//
	rgb  =  pData_src;


	//  int b_key,  g_key,  r_key,  cb_key,  cr_key;
	unsigned  int tola,  tolb;


	//
	//  double mask;

#ifdef  __DEBUG__
		int  real_i_btnDown  =  0;
		int  real_j_btnDown	=  0;
		int  img_i_btnDown  =  0;
		int  img_j_btnDown  =  0;

		get_real_ij_btnDown(  &real_i_btnDown,  &real_j_btnDown,  &img_i_btnDown,  &img_j_btnDown  );  
#endif
		
	//
	//  if  (  pCtx->m_var.width  !=  width  ||  pCtx->m_var.height  !=  height  )  goto  errLabel;
	if  (  pCfg->usCnt  >  mycountof(  pCfg->keys  )  )  {
		goto  errLabel;
	}
	if  (  !pCfg->usCnt  )  {
		goto  errLabel;
	}
	
	//
	pCtx->tn  =  getuiNextTranNo(  0,  0,  0  );
	

	//
//	BYTE		f_r_r10x	=	0;	//  0.5;
//	BYTE		f_g_r10x	=	0;	//  0.5;
//	BYTE		f_b_r10x	=	0;	//  0.5;

	//
	for  (  j  =  0;  j  <  height;  j  ++  )  {

		 if  (  bFlipImg  )  {
			 rgbPtr  =  rgb  +  lineBytes_src  *  (  height  -  1  -  j  );
			 pPix  =  &pCtx->pPixes[(  height  -  1  -  j  )  *  width];
			 }
		 else  {
			   rgbPtr  =  rgb  +  lineBytes_src  *  j;
			   pPix  =  &pCtx->pPixes[j  *  width];
		 }

		 for  (  i  =  0;  i  <  width;  i  ++  )  {

			  //
			  a  =  rgbPtr[3];
			  r  =  rgbPtr[2];				
			  g  =  rgbPtr[1];
			  b  =  rgbPtr[0];

  			  //
			  #ifdef  __DEBUG__
					  if  (  i  ==  real_i_btnDown  &&  j  ==  real_j_btnDown  )  {
						  #if  0
							   traceLog(  _T(  "btnDown,  r,g,b %d,%d,%d"  ),  (  int  )r,  (  int  )g,  (  int  )b  );
						  #endif
						  int  img_i  =  img_i_btnDown;
						  int  img_j  =  img_j_btnDown;
						  int  kk  =  0;
					  }
			  #endif


			#if  0

			  //	
			  convert_rgb_to_key_pixel(  rgbPtr[2],  rgbPtr[1],  rgbPtr[0],  &h,  &s,  &l  );

			  #ifdef  __DEBUG__
					  //  fot test
					  if  (  10  )  {
						  float  fh, fs, fl;
						  rgbToHsl_f(  r,  g,  b,  0xff,  &fh,  &fs,  &fl,  NULL  );
						  WORD  wh, ws, wl;
						  float  f;
						  f  =  fh  *  MAX_h_ms;
						  wh  =  myRound(  f  );
						  f  =  fs  *  240;
						  ws  =  myRound(  f  );
						  f  =  fl  *  240;
						  wl  =  myRound(  f  );
						  //
						  if  (  abs(  wh  -  h  )  ==  240  &&  abs(  ws  -  s  )  <=  2    &&  abs(  wl  -  l  )  <=  0  )  {
							  //  traceLog(  _T(  "kk"  )  );
							  }
						  else  {
							    if  (  abs(  wh  -  h  )  >  1  ||  abs(  ws  -  s  )  >  2  ||  wl  !=  l  )  {							  								
									traceLog(  _T(  "no ok"  )  );						  
								}
						  }
						  //
						  BYTE  ucR,  ucG,  ucB;
						  hslToRgb_f(  fh,  fs,  fl,  1.,  &ucR,  &ucG,  &ucB,  NULL  );
						  if  (  ucR  !=  r  ||  ucG  !=  g  ||  ucB  !=  b  )  {
							  traceLog(  _T(  "not ok"  )  );
						  }
					  }
			  #endif


			  //
			  BYTE  ucIndex_key  =  0;
			  float			dDistance  =  0;
			  if  (  getColorDistance_keys(  h,  s,  pCfg,  &ucIndex_key,  &dDistance  )  )  goto  errLabel;

			  //
			  tola  =  pCfg->keyCfgs[ucIndex_key].tola;
			  tolb  =  pCfg->keyCfgs[ucIndex_key].tolb;
			  if  (  tolb  <=  tola  )  {
				  #ifdef  __DEBUG__				
						  traceLog(  _T(  "doAlpha failed: tolb <=  tola"  )  );
				  #endif
				  goto  errLabel;			
			  }


			  //
			  MACRO_qyAssert(  tolb  >=  tola,  _T(  "tolb  >=  tola"  )  );
			  //  double  distance  =  colorDistance_pix(  cb,  cr,  pMem,  NULL  );
			  			
			  //
			  pPix->distanceFromKey  =  dDistance;

			  
			  //
			  int  index_minA  =  ucIndex_key;
			  int  minA  =  dDistance;
			  if  (  minA  >=  mycountof(  pCfg->keyCfgs[index_minA].alphaArray  )  )  minA  =  mycountof(  pCfg->keyCfgs[index_minA].alphaArray  )  -  1;
			  //
			  float  *  alphaArray  =  pCfg->keyCfgs[index_minA].alphaArray;
			  //
			  rgbPtr[3]  =  255  *  alphaArray[(  BYTE  )minA];

			#else

			  MY_RGBA  rgba;
			  MY_float4  f4;
			  rgba.r  =  toFloat_rgb(  r  );
			  rgba.g  =  toFloat_rgb(  g  );
			  rgba.b  =  toFloat_rgb(  b  );
			  rgba.a  =  toFloat_rgb(  a  );
			  //f4  =  hlsl_procChromaKey(  rgba  );  
			  memset(&f4, 0, sizeof(f4));
			  rgbPtr[3]  =  toByte_rgb(  f4.w  );
			#endif
			  		
			
			  //			  				
			  rgbPtr  +=  rgbIncrement;			  
			  pPix  ++  ;
		 
			}
	}


	iErr  =  0;
errLabel:


	return  iErr;
}

#if  0
 long  myRound( double value)
{
    long            intpart;

    intpart = value;
    value = value - intpart;
    if (value >= 0.5)
        intpart++;

    return intpart;
}
#endif



#if  0
int kkcalculateAlphaTables(  int  alpha_in,  int  alpha_out,  float  fMaskGamma,  int  alphaArray[256]  )
{
	int  i;

	if  (  alpha_in  <  0  )  alpha_in  =  0;
	if  (  alpha_in  >  254  )  alpha_in  =  254;
	if  (  alpha_out  <=  alpha_in  )  alpha_out  =  alpha_in  +  1;
	if  (  alpha_out  >  255  )  alpha_out  =  255;
	//
	if  (  fMaskGamma  <  0.001  )  fMaskGamma  =  0.001;

	for ( i  = 0; i < alpha_in; i ++ )
	{
		alphaArray[i] = 0;
	}

	float  f = 1./( alpha_out - alpha_in );
	double  n = f;

	for ( i = alpha_in; i < alpha_out; i ++ )
	{			
		//  alphaArray[i] = Math.round( 255 * Math.pow( n, 1.0 / ( maskGamma.value / 100 ) ) ) << 24 | 0xffffff;
		float  f1;

		f1  =  ( 255 * pow( n, 1.0 / fMaskGamma ) );
		int  ta  =  myRound(  f1  );
		
		alphaArray[i] = ta;

		n+= f;
	}

	for ( i = alpha_out; i < 256; i ++ )
	{
		alphaArray[i] = 0xff;
	}

	return  0;
}
#endif


//
 __declspec(  dllexport  )  int calculateAlphaTables(  int  alpha255_in,  int  alpha255_out,  float  fMaskGamma,  float  alphaArray[256]  )
{
	int  i;

	if  (  alpha255_in  <  0  )  alpha255_in  =  0;
	if  (  alpha255_in  >  254  )  alpha255_in  =  254;
	if  (  alpha255_out  <=  alpha255_in  )  alpha255_out  =  alpha255_in  +  1;
	if  (  alpha255_out  >  255  )  alpha255_out  =  255;
	//
	if  (  fMaskGamma  <  0.001  )  fMaskGamma  =  0.001;

	for ( i  = 0; i < alpha255_in; i ++ )
	{
		alphaArray[i] = 0;
	}

	float  f = 1./( alpha255_out - alpha255_in );
	float  n = f;

	for ( i = alpha255_in; i < alpha255_out; i ++ )
	{			
		//  alphaArray[i] = Math.round( 255 * Math.pow( n, 1.0 / ( maskGamma.value / 100 ) ) ) << 24 | 0xffffff;
		float  f1;

		f1  =  (  float  )pow( n, (  float  )(  1.0 / fMaskGamma  ) );
		//  f1  =  f1  *  255
		
		alphaArray[i] = f1;

		n+= f;
	}

	for ( i = alpha255_out; i < 256; i ++ )
	{
		alphaArray[i] = 1.;	
	}

	return  0;
}


 __declspec(  dllexport  )  int  calculateWeights_blur(  float  fSigma,  int  lBlurSize,  float  *  ws,  unsigned  int  cnt_ws  )
{
	//  int  lBlurSize  =  9;	//  7;
	float  sigma  =  fSigma;	//  0.84089642;

#ifdef  __DEBUG__
		float  ws1[21];
		int  cnt  =  mycountof(  ws  );
		cnt  =  mycountof(  ws1  );
#endif

	//
	if  (  lBlurSize  >  cnt_ws  )  return  -1;

	int  halfSize  =  lBlurSize  /  2;
	if  (  lBlurSize  ==  2  *  halfSize  )  return  -1;

	//
	if  (  sigma  <=  0  )  sigma  =  0.001;

	//
	int  i,  j;

	float  total_ws  =  0;
	for  (  i  =  0;  i  <  lBlurSize;  i  ++  )  {
		 int  d  =  abs  (  i  -  halfSize  );
		 float  f  =  exp(  -1  *  d  *  d  /  (  2  *  sigma  *  sigma  )  )  /  (  2  *  PI  *  sigma  *  sigma  );
		 ws[i]  =  f;
		 total_ws  +=  f;
	}
	for  (  i  =  0;  i  <  lBlurSize;  i  ++  )  {
		 ws[i]  =  ws[i]  /  total_ws;
	}

	return  0;
}


 __declspec(  dllexport  )  int  procChromaKey_keyDifference(  void  *  pProcInfo,  void  *  pKEYING_ctx,  void  *  pIMG_process_cfg,  BITMAPINFOHEADER  *  pBih,  BYTE  *  pData_src,  BOOL  bFlipImg  )
{
	int  iErr  =  -1;

#ifdef  __DEBUG__
		//  return  0;
#endif

	if  (  pBih->biCompression  !=  0  )  return  -1;
	switch  (  pBih->biBitCount  )  {
			case  32:
					break;
			default:
					#ifdef  __DEBUG__
							traceLog(  _T(  "procChromaKey failed, bih.bits %d"  ),  pBih->biBitCount  );
					#endif
					return  -1;
	}

	
	KEYING_ctx		*	pCtx	=	(  KEYING_ctx  *  )pKEYING_ctx;
	IMG_process_cfg  *  pCfg  =  (  IMG_process_cfg  *  )pIMG_process_cfg;

	if  (  !pCtx  )  return  -1;
	if  (  !pCtx->pPixes  )  {
#ifdef  __DEBUG__
		traceLog(  _T(  "procChromaKey failed: pCtx->pPixes is null"  )  );
#endif
		return  -1;
	}

	//
	int	 i,  j;
	unsigned  char  *  rgb  =  NULL;

	int	 a,  r,  g,  b;
	
	unsigned  char  *  rgbPtr	=	NULL;
	unsigned  int  rgbIncrement  =  pBih->biBitCount  /  8;
	int				lineBytes_src	=	M_lineBytes_rgb(  32,  pBih->biWidth  );

	//
	KEYING_pix_help  *  pPix  =  NULL;
		
	//
	int  width  =  0;
	int  height  =  0;
	
	width  =  pBih->biWidth;
	height  =  pBih->biHeight;
	



	//
	rgb  =  pData_src;


	//  int b_key,  g_key,  r_key,  cb_key,  cr_key;
	unsigned  int tola100x,  tolb100x;


	//
	//  double mask;

#ifdef  __DEBUG__
		int  real_i_btnDown  =  0;
		int  real_j_btnDown	=  0;
		int  img_i_btnDown  =  0;
		int  img_j_btnDown  =  0;

		get_real_ij_btnDown(  &real_i_btnDown,  &real_j_btnDown,  &img_i_btnDown,  &img_j_btnDown  );  
#endif
		
	//
	//  if  (  pCtx->m_var.width  !=  width  ||  pCtx->m_var.height  !=  height  )  goto  errLabel;
	if  (  pCfg->usCnt  >  mycountof(  pCfg->keys  )  )  {
		goto  errLabel;
	}
	if  (  !pCfg->usCnt  )  {
		goto  errLabel;
	}
	
	//
	pCtx->tn  =  getuiNextTranNo(  0,  0,  0  );
	

	//
	for  (  j  =  0;  j  <  height;  j  ++  )  {

		 if  (  bFlipImg  )  {
			 rgbPtr  =  rgb  +  lineBytes_src  *  (  height  -  1  -  j  );
			 pPix  =  &pCtx->pPixes[(  height  -  1  -  j  )  *  width];
			 }
		 else  {
			   rgbPtr  =  rgb  +  lineBytes_src  *  j;
			   pPix  =  &pCtx->pPixes[j  *  width];
		 }

		 for  (  i  =  0;  i  <  width;  i  ++  )  {

			  //
			  r  =  rgbPtr[2];				
			  g  =  rgbPtr[1];
			  b  =  rgbPtr[0];

			  			  //
			  #ifdef  __DEBUG__
					  if  (  i  ==  real_i_btnDown  &&  j  ==  real_j_btnDown  )  {
						  #if  0
							   traceLog(  _T(  "btnDown,  r,g,b %d,%d,%d"  ),  (  int  )r,  (  int  )g,  (  int  )b  );
						  #endif
						  int  img_i  =  img_i_btnDown;
						  int  img_j  =  img_j_btnDown;
						  int  kk  =  0;
					  }
			  #endif


			  //
			 int  minA  =  0;
			  int  index;
			  int  index_minA  =  0;
			  for  (  index  =  0;  index  <  pCfg->usCnt;  index  ++  )  {
				   int  a  =  abs(  r  -  toByte_rgb(  pCfg->keys[index].rgb_key.r  )  )  +  abs(  g  -  toByte_rgb(  pCfg->keys[index].rgb_key.g  )  )  +  abs(  b  -  toByte_rgb(  pCfg->keys[index].rgb_key.b  )  );
				   a  =  a  /  3;
				   if  (  !index  )  {
					   minA  =  a;
					   index_minA  =  0;
					   }
				   else  {
					     if  (  a  <  minA  )  {
							 minA  =  a;
							 index_minA  =  index;
						 }
				   }
			  }
			  //
			  rgbPtr[3]  =  minA;
			  switch  (  rgbPtr[3]  )  {
					  case  255:
							break;
					  case  0:
						    break;
					  default:
				  		     //  traceLog(  _T(  "procKey: [%d][%d], a %d"  ),  i,  j,  minA  );				
							 break;
			  }

			  //
			  float  fMaskGamma  =  pCfg->fGamma;
			  //  calculateAlphaTables(  pCfg->keys[index_minA].cfg.tola100x  /  100,  pCfg->keys[index_minA].cfg.tolb100x  /  100,  fMaskGamma  );
			  float  *  alphaArray  =  pCfg->keys[index_minA].alphaArray;
			  //
			  rgbPtr[3]  =  255  *  alphaArray[(  BYTE  )minA];

	
				//			  
				rgbPtr  +=  rgbIncrement;			  
				pPix  ++  ;
		 
			}
	}


	iErr  =  0;
errLabel:


	return  iErr;
}

 int  test_setBg(  BITMAPINFOHEADER  *  pBih,  BYTE  *  pData,  BOOL  bFlipImg  )
 {
	 	 int  i,  j;
	 BYTE  *  rgb  =  pData;
	 
	 
	int	 r,  g,  b;
	BYTE	l,  h,  s;
	
	unsigned  char  *  rgbPtr	=	NULL;
	unsigned  int  rgbIncrement  =  pBih->biBitCount  /  8;
	int				lineBytes_src	=	M_lineBytes_rgb(  32,  pBih->biWidth  );


	//
	int  width  =  0;
	int  height  =  0;
	
	width  =  pBih->biWidth;
	height  =  pBih->biHeight;
	
	

	 for  (  j  =  0;  j  <  pBih->biHeight;  j  ++  )  {
		  if  (  bFlipImg  )  {
				   rgbPtr  =  rgb  +  lineBytes_src  *  (  height  -  1  -  j  );			 
				   }
			   else  {			   
				     rgbPtr  =  rgb  +  lineBytes_src  *  j;		 
			   }

		  for  (  i  =  0;  i  <  pBih->biWidth;  i  ++  )  {	

			   BYTE  r  =  255;
			   BYTE  g  =  255;
			   BYTE  b  =  0;
			   BYTE  a  =  255;

			   rgbPtr[0]  =  b;
			   rgbPtr[1]  =  g;
			   rgbPtr[2]  =  r;
			   rgbPtr[3]  =  a;
			   			   			   
			   //			  
			   rgbPtr  +=  rgbIncrement;
		  }
	 }

	 return  0;
}


 #if  1		//  def  __DEBUG__

//

//
#if 0
extern	int									g_cfg_usCnt;
//
extern  MY_float3							g_cfg_keys_rgb_key[CONST_imgKeysCnt];
//
extern  MY_float3							g_cfg_keys_hsl_key[CONST_imgKeysCnt];
extern  float								g_cfg_keys_alphaArray[CONST_imgKeysCnt  *  CONST_alphaArrayCnt];

//
extern  int									g_lBlurSize;
//
extern  float								g_ws_preBlur[21];
extern  float								g_ws_postBlur[21];


extern  int									g_tn_modified;

//
extern  int									s_tn_modified;
#endif




int  test_chromaKey_inputParams_update(  void  *  pIMG_process_cfg  )
{
	int					iErr  =  -1;
	IMG_process_cfg  *  pCfg  =  (  IMG_process_cfg  *  )pIMG_process_cfg;

#if 0
	//
	//g_cfg_usCnt  =  pCfg->usCnt;

	//
	int  i;
	for  (  i  =  0;  i  <  pCfg->usCnt;  i  ++  )  {
		 HLSL_imgKey	*	pKey  =  &pCfg->keys[i];
		g_cfg_keys_rgb_key[i]  =  to_MY_float3(  pKey->rgb_key.r,  pKey->rgb_key.g,  pKey->rgb_key.b  );
		//
		g_cfg_keys_hsl_key[i]  =  to_MY_float3(  pKey->hsl_key.x,  pKey->hsl_key.y,  pKey->hsl_key.z  );
		//
		calculateAlphaTables(  pKey->tola,  pKey->tolb,  pCfg->fGamma,  &g_cfg_keys_alphaArray[i  *  CONST_alphaArrayCnt]  );
	}
	
	//
	pCfg->lBlurSize  =  9;

	//
	if  (  calculateWeights_blur(  pCfg->fSigma_preBlur,  pCfg->lBlurSize,  g_ws_preBlur,  mycountof(  g_ws_preBlur  )  )  )  goto  errLabel;
	if  (  calculateWeights_blur(  pCfg->fSigma_postBlur,  pCfg->lBlurSize,  g_ws_postBlur,  mycountof(  g_ws_postBlur  )  )  )  goto  errLabel;
	
#ifdef  __DEBUG__
		traceLog(  _T(  "test_chromaKey_inputParams_update: pCfg->fSigma_postBlur %f"  ),  pCfg->fSigma_postBlur  );
#endif

	//  
	g_lBlurSize  =  pCfg->lBlurSize;

	//
	g_tn_modified  =  GetTickCount(  );
#endif

	iErr  =  0;
errLabel:
	
	return  iErr;
}


//
int  get_HLSL_imgProcessCfg(  HLSL_imgProcessCfg  &  cfg  )
 {
	 int  i;

#if 0
	 if  (  g_tn_modified  !=  s_tn_modified  )  return  -1;

	 int  usCnt  =  g_cfg_usCnt;
	for  (  i  =  0;  i  <  usCnt;  i  ++  )  {

		 cfg.keys[i].rgb_key  =  to_MY_RGB(  g_cfg_keys_rgb_key[i].x,  g_cfg_keys_rgb_key[i].y,  g_cfg_keys_rgb_key[i].z  );
		 //
		 cfg.keys[i].hsl_key  =  to_MY_float3(  g_cfg_keys_hsl_key[i].x,  g_cfg_keys_hsl_key[i].y,  g_cfg_keys_hsl_key[i].z  );
		 memcpy(  cfg.keys[i].alphaArray,  &g_cfg_keys_alphaArray[i  *  CONST_alphaArrayCnt],  sizeof(  cfg.keys[i].alphaArray  )  );
	}
	//	
	cfg.usCnt  =  usCnt;
	
	//  
	cfg.lBlurSize  =  g_lBlurSize;
	memcpy(  cfg.ws_preBlur,  g_ws_preBlur,  sizeof(  cfg.ws_preBlur  )  );
	memcpy(  cfg.ws_postBlur,  g_ws_postBlur,  sizeof(  cfg.ws_postBlur  )  );

#endif

	return  0;

 }


#endif


  __declspec(  dllexport  )  int  test_procChromaKey(  void  *  pProcInfo,  void  *  pKEYING_ctx,  void  *  pIMG_process_cfg,  BITMAPINFOHEADER  *  pBih,  void  *  pKEYING_img_datas,  BOOL  bFlipImg  )
{
	 int  iErr  =  -1;

	 IMG_process_cfg	*	pCfg	=	(  IMG_process_cfg  *  )pIMG_process_cfg;
	 KEYING_img_datas	*  pDatas  = (  KEYING_img_datas  *  )pKEYING_img_datas;
	 
	 unsigned  int  rgbIncrement  =  pBih->biBitCount  /  8;
	 int				lineBytes_src	=	M_lineBytes_rgb(  32,  pBih->biWidth  );

#ifdef  __DEBUG__
		traceLog(  _T(  "test_procChromaKey called"  )  );
#endif

	 test_chromaKey_inputParams_update(  pCfg  );

	 //hlsl_init(  );
	 
	 //
	 HLSL_imgProcessCfg  cfg;
	 if  (  get_HLSL_imgProcessCfg(  cfg  )  )  goto  errLabel;
	 pCfg  =  &cfg;

	 //
	 memcpy(  pDatas->pData,  pDatas->pData_org,  pBih->biSizeImage  );

	 if  (  gaussianFilter_f(  pCfg->lBlurSize,  pCfg->ws_preBlur,  mycountof(  pCfg->ws_preBlur  ),  pDatas->pData,  pDatas->pData_tmp,  pDatas->pData_mask,  rgbIncrement,  pBih->biWidth,  pBih->biHeight  )  )  goto  errLabel;
	 
#if  0
	 if  (  procChromaKey_keyDifference(  pProcInfo,  pKEYING_ctx,  pCfg,  pBih,  pDatas->pData_mask,  bFlipImg  )  )  goto  errLabel;
#else
	 if  (  procChromaKey(  pProcInfo,  pKEYING_ctx,  pCfg,  pBih,  pDatas->pData_mask,  bFlipImg  )  )  goto  errLabel;
#endif

	 //  注意:最后的alpha值存在pData里
	 if  (  gaussianFilter_a_f(  pCfg->lBlurSize,  pCfg->ws_postBlur,  mycountof(  pCfg->ws_postBlur  ),  pDatas->pData_mask,  pDatas->pData_tmp,  pDatas->pData,  rgbIncrement,  pBih->biWidth,  pBih->biHeight  )  )  goto  errLabel;
	 

	 //  下面设置背景
	 test_setBg(  pBih,  pDatas->pData_bg,  bFlipImg  );


	 //  下面blend
	 int  i,  j;
	

	//
	int  width  =  0;
	int  height  =  0;
	
	width  =  pBih->biWidth;
	height  =  pBih->biHeight;
	
	int  nStart;
	int  nOffset;

	 for  (  j  =  0;  j  <  pBih->biHeight;  j  ++  )  {
		  if  (  bFlipImg  )  {
			  nStart  =  lineBytes_src  *  (  height  -  1  -  j  );			 				   
			  }
		  else  {			   
			    nStart  =  lineBytes_src  *  j;		 			  
		  }

		  for  (  i  =  0;  i  <  pBih->biWidth;  i  ++  )  {	
			   nOffset  =  nStart  +  rgbIncrement *  i;
			   
			   //
			   BYTE  b_data  =  pDatas->pData[nOffset  +  0  ];
			   BYTE  g_data  =  pDatas->pData[nOffset  +  1  ];
			   BYTE	 r_data  =  pDatas->pData[nOffset  +  2  ];
			   BYTE  a_data  =  pDatas->pData[nOffset  +  3  ];
			   			   
			   //
			   BYTE  b_bg  =  pDatas->pData_bg[nOffset  +  0];
			   BYTE  g_bg  =  pDatas->pData_bg[nOffset  +  1];
			   BYTE  r_bg  =  pDatas->pData_bg[nOffset  +  2];
			   
			   //
			   float  f  =  a_data  /  255.;
			   //
			   BYTE  b_blend  =  f  *  b_data  +  (  1  -  f  )  *  b_bg;
			   BYTE  g_blend  =  f  *  g_data  +  (  1  -  f  )  *  g_bg;
			   BYTE  r_blend  =  f  *  r_data  +  (  1  -  f  )  *  r_bg;
			   
			   //
			   pDatas->pData_blend[nOffset  +  0]  =  b_blend;
			   pDatas->pData_blend[nOffset  +  1]  =  g_blend;
			   pDatas->pData_blend[nOffset  +  2]  =  r_blend;
			   pDatas->pData_blend[nOffset  +  3]  =  0xff;
			   			   
		  }
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
}



void  gaussianFilter2_rgb32(  unsigned char  *  corrupted,  unsigned  char  *  smooth,  int  width,  int  height  );

//
void  gaussianFilter2(  unsigned char  *  corrupted,  unsigned  char  *  smooth,  int  width,  int  height  )
{
	int  templates[25]  =	{ 1,4,7,4,1,
							  4,16,26,16,4,
							  7,26,41,26,7,
							  4,16,26,16,4,
							  1,4,7,4,1  };
	//  memcpy(  smooth,  corrupted,  width * height * sizeof(  unsigned char )  );
	for ( int j = 2; j < height -2; j ++  )
	{
		for  ( int i =2; i < width-2; i ++  )
		{
			int sum = 0;
			int index = 0;
			for ( int m = j - 2; m < j + 3; m ++ )  
			{
				for ( int n = i -2; n < i + 3; n ++  )
				{
					sum += corrupted[ m* width + n ] * templates[index ++ ];
				}
			}
			sum /= 273;
			if (sum > 255 ) 
				sum = 255;
			smooth [ j*width + i] = sum;
		}		
	}
}

void  gaussianFilter2_rgb32(  unsigned char  *  corrupted,  unsigned  char  *  smooth,  int  width,  int  height  )
{
	int  templates[25]  =	{ 1,4,7,4,1,
							  4,16,26,16,4,
							  7,26,41,26,7,
							  4,16,26,16,4,
							  1,4,7,4,1  };

	//
	int  rgbIncrement  =  4;
	int  lineBytes  =  width  *  4;

	//  memcpy(  smooth,  corrupted,  width * height * sizeof(  unsigned char )  );
	for ( int j = 2; j < height -2; j ++  )
	{
		for  ( int i =2; i < width-2; i ++  )
		{
			int sum_r = 0;
			int  sum_g  =  0;
			int  sum_b  =  0;
			int  sum_a  =  0;

			int index = 0;
			for ( int m = j - 2; m < j + 3; m ++ )  
			{
				for ( int n = i -2; n < i + 3; n ++  )
				{
					//  sum += corrupted[ m* width + n ] * templates[index ++ ];
					BYTE  *  rgb  =  corrupted  +  m  *  lineBytes  +  n  *  rgbIncrement;
					int  template_val  =  templates[index  ++  ];
					sum_b  +=  rgb[0]  *  template_val;
					sum_g  +=  rgb[1]  *  template_val;
					sum_r  +=  rgb[2]  *  template_val;
					sum_a  +=  rgb[3]  *  template_val;
				}
			}

#if  0
			sum /= 273;
			if (sum > 255 ) 
				sum = 255;
#endif
			sum_r  /=  273;
			if  (  sum_r  >  255  )  sum_r  =  255;
			sum_g  /=  273;
			if  (  sum_g  >  255  )  sum_g  =  255;
			sum_b  /=  273;
			if  (  sum_b  >  255  )  sum_b  =  255;
			sum_a  /=  273;
			if  (  sum_a  >  255  )  sum_a  =  255;

			//
			//smooth [ j*width + i] = sum;
			BYTE  *  rgb  =  smooth  +  j  *  lineBytes  +  i  *  rgbIncrement;
			rgb[0]  =  sum_b;
			rgb[1]  =  sum_g;
			rgb[2]  =  sum_r;
			rgb[3]  =  sum_a;
		}		
	}
}


 //  __declspec(  dllexport  )  int  gaussianFilter_f(  int  lBlurSize,  float  *  ws,  unsigned  int  cnt_ws,  unsigned char  *  corrupted,  unsigned  char  *  smooth,  int  rgbIncrement,  int  width,  int  height  )
__declspec(  dllexport  )  int  gaussianFilter_f(  int  lBlurSize,  float  *  ws,  unsigned  int  cnt_ws,  unsigned char  *  corrupted,  unsigned  char  *  tmpImg,  unsigned  char  *  smooth,  int  rgbIncrement,  int  width,  int  height  )
{
	int		iErr		=	-1;
	
	if  (  lBlurSize  >  cnt_ws  )  return  -1;
	if  (  rgbIncrement  !=  4  )  return  -1;

#if  0
	//  float	ws[21]  =	{ 0,};
	
	//  int  lBlurSize  =  9;	//  7;
	float  sigma  =  fSigma;	//  0.84089642;
	
	if  (  sigma  <=  0  )  sigma  =  0.001;


	int  i,  j;

	float  total_ws  =  0;
	for  (  i  =  0;  i  <  lBlurSize;  i  ++  )  {
		 int  d  =  abs  (  i  -  halfSize  );
		 float  f  =  exp(  -1  *  d  *  d  /  (  2  *  sigma  *  sigma  )  )  /  (  2  *  PI  *  sigma  *  sigma  );
		 ws[i]  =  f;
		 total_ws  +=  f;
	}
	for  (  i  =  0;  i  <  lBlurSize;  i  ++  )  {
		 ws[i]  =  ws[i]  /  total_ws;
	}
#endif
	
	int  halfSize  =  lBlurSize  /  2;
	if  (  halfSize  *  2  ==  lBlurSize  )  goto  errLabel;

		
	if  (  !corrupted  ||  !tmpImg  ||  !smooth  )  goto  errLabel;
	
	//
	//  int  rgbIncrement  =  4;
	int  lineBytes  =  width  *  4;
	BYTE  *  pSrc  =  NULL;
	BYTE  *  pDst  =  NULL;

	//
	pSrc  =  corrupted;
	pDst  =  tmpImg;

	//  x
	for ( int j = 0; j < height; j ++  )
	{
		for  ( int i = halfSize; i < width-halfSize; i ++  )
		{
			float  sum_r = 0;
			float  sum_g  =  0;
			float  sum_b  =  0;
			float  sum_a  =  0;

			int index = 0;
			for ( int m = i - halfSize; m < i + halfSize  +  1; m ++  )
				{
					//  sum += corrupted[ m* width + n ] * templates[index ++ ];
					BYTE  *  rgb  =  pSrc  +  j  *  lineBytes  +  m  *  rgbIncrement;
					float  template_val  =  ws[index];
					sum_b  +=  rgb[0]  *  template_val;
					sum_g  +=  rgb[1]  *  template_val;
					sum_r  +=  rgb[2]  *  template_val;
					sum_a  +=  rgb[3]  *  template_val;
					index  ++  ;
			}

			if  (  sum_r  >  255  )  sum_r  =  255;
			if  (  sum_g  >  255  )  sum_g  =  255;
			if  (  sum_b  >  255  )  sum_b  =  255;
			if  (  sum_a  >  255  )  sum_a  =  255;

			//
			BYTE  *  rgb  =  pDst  +  j  *  lineBytes  +  i  *  rgbIncrement;
			rgb[0]  =  sum_b;
			rgb[1]  =  sum_g;
			rgb[2]  =  sum_r;
			rgb[3]  =  sum_a;
		}
	}

	//
	pSrc  =  tmpImg;
	pDst  =  smooth;

	//  y	
	for ( int i = 0; i < width; i ++  )
	{
		for  ( int j = halfSize; j < height-halfSize; j ++  )
		{
			float  sum_r = 0;
			float  sum_g  =  0;
			float  sum_b  =  0;
			float  sum_a  =  0;

			int index = 0;
			for ( int n = j - halfSize; n < j + halfSize  +  1; n ++  )
				{
					//  sum += corrupted[ m* width + n ] * templates[index ++ ];
					BYTE  *  rgb  =  pSrc  +  n  *  lineBytes  +  i  *  rgbIncrement;
					float  template_val  =  ws[index];
					sum_b  +=  rgb[0]  *  template_val;
					sum_g  +=  rgb[1]  *  template_val;
					sum_r  +=  rgb[2]  *  template_val;
					sum_a  +=  rgb[3]  *  template_val;
					index  ++  ;
			}

			if  (  sum_r  >  255  )  sum_r  =  255;
			if  (  sum_g  >  255  )  sum_g  =  255;
			if  (  sum_b  >  255  )  sum_b  =  255;
			if  (  sum_a  >  255  )  sum_a  =  255;

			//
			BYTE  *  rgb  =  pDst  +  j  *  lineBytes  +  i  *  rgbIncrement;
			rgb[0]  =  sum_b;
			rgb[1]  =  sum_g;
			rgb[2]  =  sum_r;
			rgb[3]  =  sum_a;
		}
	}



	iErr  =  0;
	errLabel:
	return  iErr;
}


 __declspec(  dllexport  )  int  gaussianFilter_a_f(  int  lBlurSize,  float  *  ws,  unsigned  int  cnt_ws,  unsigned char  *  corrupted,  unsigned  char  *  tmpImg,  unsigned  char  *  smooth,  int  rgbIncrement,  int  width,  int  height  )
{
	int		iErr		=	-1;
	
	if  (  lBlurSize  >  cnt_ws  )  return  -1;
	if  (  rgbIncrement  !=  4  )  return  -1;
	
#if  0
	float	ws[21]  =	{ 0,};
	
	int  lBlurSize  =  9;	//  7;
	float  sigma  =  fSigma;	//  0.84089642;

	if  (  lBlurSize  >  mycountof(  ws  )  )  return  -1;
	if  (  rgbIncrement  !=  3   &&  rgbIncrement  !=  4  )  return  -1;
	
	if  (  sigma  <=  0  )  sigma  =  0.001;

	int  i,  j;

	float  total_ws  =  0;
	for  (  i  =  0;  i  <  lBlurSize;  i  ++  )  {
		 int  d  =  abs  (  i  -  halfSize  );
		 float  f  =  exp(  -1  *  d  *  d  /  (  2  *  sigma  *  sigma  )  )  /  (  2  *  PI  *  sigma  *  sigma  );
		 ws[i]  =  f;
		 total_ws  +=  f;
	}
	for  (  i  =  0;  i  <  lBlurSize;  i  ++  )  {
		 ws[i]  =  ws[i]  /  total_ws;
	}
#endif
	
	int  halfSize  =  lBlurSize  /  2;
	if  (  halfSize  *  2  ==  lBlurSize  )  goto  errLabel;

		
	if  (  !corrupted  ||  !tmpImg  ||  !smooth  )  goto  errLabel;
	
	//
	//  int  rgbIncrement  =  4;
	int  lineBytes  =  width  *  4;
	BYTE  *  pSrc  =  NULL;
	BYTE  *  pDst  =  NULL;
	
	//
	pSrc  =  corrupted;
	pDst  =  tmpImg;
	
	//  x
	for ( int j = 0; j < height; j ++  )
	{
		for  ( int i = halfSize; i < width-halfSize; i ++  )
		{
			float  sum_a  =  0;

			int index = 0;
			for ( int m = i - halfSize; m < i + halfSize  +  1; m ++  )
				{
					//  sum += corrupted[ m* width + n ] * templates[index ++ ];
					BYTE  *  rgb  =  pSrc  +  j  *  lineBytes  +  m  *  rgbIncrement;
					float  template_val  =  ws[index];
					sum_a  +=  rgb[3]  *  template_val;
					index  ++  ;
			}

			if  (  sum_a  >  255  )  sum_a  =  255;

			//
			BYTE  *  rgb  =  pDst  +  j  *  lineBytes  +  i  *  rgbIncrement;
			if  (  rgb[3]  !=  (  BYTE  )sum_a  )  {
				rgb[3]  =  sum_a;
			}
		}
	}


	//
	pSrc  =  tmpImg;
	pDst  =  smooth;

	//  y	
	for ( int i = 0; i < width; i ++  )
	{
		for  ( int j = halfSize; j < height-halfSize; j ++  )
		{
			float  sum_a  =  0;

			int index = 0;
			for ( int n = j - halfSize; n < j + halfSize  +  1; n ++  )
				{
					//  sum += corrupted[ m* width + n ] * templates[index ++ ];
					BYTE  *  rgb  =  pSrc  +  n  *  lineBytes  +  i  *  rgbIncrement;
					float  template_val  =  ws[index];
					sum_a  +=  rgb[3]  *  template_val;
					index  ++  ;
			}

			if  (  sum_a  >  255  )  sum_a  =  255;

			//
			BYTE  *  rgb  =  pDst  +  j  *  lineBytes  +  i  *  rgbIncrement;
			if  (  rgb[3]  !=  (  BYTE  )sum_a  )  {
				rgb[3]  =  sum_a;
			}
		}
	}



	iErr  =  0;
	errLabel:
	return  iErr;
}
