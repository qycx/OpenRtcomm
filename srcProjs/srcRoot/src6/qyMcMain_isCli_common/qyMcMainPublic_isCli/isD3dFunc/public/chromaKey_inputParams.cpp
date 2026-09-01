
#include "stdafx.h"
#include	<stdlib.h>
#include	<tchar.h>

#include	"DXUT.h"
#include	"DXUTgui.h"
#include	"SDKmisc.h"

//  2014/10/23
#include	"D3dx11effect.h"


#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"qySyncCommProc.h"
#include	"qmcVideoCapture_isCli.h"


//#include	"isCliD3dCommon.h"
//#include	"dlgD3dWall.h"

//
#include	"isCliHelpPublic.h"

//
#include	"isCliD3dPublic.h"

//
//#include	"cuboidTool.h"

#include	"isCmdConst.h"
#include	"qyCusResTemp.h"
#include	"imgProcessPublic.h"
#include	"dlgTalkProc.h"
//#include	"dynFuncs_d3dCall.h"
#include	"funcsForisCliHelp.h"
#include	"subtitlesCfg.h"

//
//#include	"wallMemMgr.h"
//#include	"wmNoWall.h"

#include	"qisChromaKeyEffect.h"




int  ChromaKey_inputParams_init(  QIS_chromaKey_effect  *  pQce,  ChromaKey_inputParams  *  pParams  )
{
	int				iErr	=	-1;
	if  (  !pQce  )  return  -1;

#if  1  //  def  __USE_dx10__

	ChromaKey_inputParams  *  p  =  pParams;
	ID3DX11Effect  *  g_pEffect  =  pQce->g_pEffect;	//  pCtx->test.g_pEffect;

	p->p_g_cfg_usCnt  =  	g_pEffect->GetVariableByName(  "g_cfg_usCnt"  )->AsScalar(  );	//  2013/10/23
		
	//
	p->p_g_cfg_keys_rgb_key  =  g_pEffect->GetVariableByName(  "g_cfg_keys_rgb_key"  )->AsVector(  );

	//
	p->p_g_cfg_keys_hsl_key  =  g_pEffect->GetVariableByName(  "g_cfg_keys_hsl_key"  )->AsVector(  );
	//
	p->p_g_cfg_keys_alphaArray  =  g_pEffect->GetVariableByName(  "g_cfg_keys_alphaArray"  )->AsScalar(  );

	//
	p->p_g_iImgW  =  g_pEffect->GetVariableByName(  "g_iImgW"  )->AsScalar(  );
	p->p_g_iImgH  =  g_pEffect->GetVariableByName(  "g_iImgH"  )->AsScalar(  );


	//
	p->p_g_lBlurSize  =  g_pEffect->GetVariableByName(  "g_lBlurSize"  )->AsScalar(  );
	

	//
	p->p_g_ws_preBlur  =  g_pEffect->GetVariableByName(  "g_ws_preBlur"  )->AsScalar(  );
	p->p_g_ws_postBlur  =  g_pEffect->GetVariableByName(  "g_ws_postBlur"  )->AsScalar(  );

	//
	p->p_g_tn_modified  =  g_pEffect->GetVariableByName(  "g_tn_modified"  )->AsScalar(  );

#endif

	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		ChromaKey_inputParams_exit(  pQce,  pParams  );
	}
	return  iErr;
}

void  ChromaKey_inputParams_exit(  QIS_chromaKey_effect  *  pQce,  ChromaKey_inputParams  *  pParams  )
{
	if  (  !pQce  )  return;


	return;
}



#if  0
int  ChromaKey_inputParams_update(  void  *  pD3D_context,  void  *  pIMG_process_cfg,  ChromaKey_inputParams  *  pParams  )
{
	int				iErr	=	-1;
	D3D_context  *  pCtx  =  (  D3D_context  *  )pD3D_context;
	IMG_process_cfg  *  pCfg  =  (  IMG_process_cfg  *  )pIMG_process_cfg;
	ChromaKey_inputParams  *  p  =  pParams;
	HRESULT						hr;
	int							i;	
	D3DXVECTOR3					f3_rgbs[mycountof(  pCfg->keys  )];
	D3DXVECTOR3					f3_hsls[mycountof(  pCfg->keys  )];
	float						g_cfg_keys_alphaArray[CONST_imgKeysCnt  *  CONST_alphaArrayCnt];
	//
	float						g_ws_preBlur[21];
	float						g_ws_postBlur[21];


	if  (  pCfg->usCnt  >  mycountof(  pCfg->keys  )  )  goto  errLabel;
	
#ifdef  __USE_dx10__

	hr  =  p->p_g_cfg_usCnt->SetInt(  pCfg->usCnt  );
	if  (  FAILED(  hr  )  )  goto  errLabel;

	for  (  i  =  0;  i  <  pCfg->usCnt;  i  ++  )  {
		 IMG_key  *  pKey  =  &pCfg->keys[i];

		 f3_rgbs[i]  =  D3DXVECTOR3(  pKey->rgb_key.r,  pKey->rgb_key.g,  pKey->rgb_key.b  );

		 //
		 f3_hsls[i]  =  D3DXVECTOR3(  pKey->hsl_key.x,  pKey->hsl_key.y,  pKey->hsl_key.z  );
		 
		 //
		 calculateAlphaTables(  pKey->tola,  pKey->tolb,  pCfg->fGamma,  &g_cfg_keys_alphaArray[i  *  CONST_alphaArrayCnt]  );
	}

	//
	pCfg->lBlurSize  =  9;

	//
	if  (  calculateWeights_blur(  pCfg->fSigma_preBlur,  pCfg->lBlurSize,  g_ws_preBlur,  mycountof(  g_ws_preBlur  )  )  )  goto  errLabel;
	if  (  calculateWeights_blur(  pCfg->fSigma_postBlur,  pCfg->lBlurSize,  g_ws_postBlur,  mycountof(  g_ws_postBlur  )  )  )  goto  errLabel;
			
	//
	hr  =  p->p_g_cfg_keys_rgb_key->SetFloatVectorArray(  (  float  *  )&f3_rgbs,  0,  pCfg->usCnt  );	
	if  (  FAILED(  hr  )  )  goto  errLabel;

	//
	hr  =  p->p_g_cfg_keys_hsl_key->SetFloatVectorArray(  (  float  *  )&f3_hsls,  0,  pCfg->usCnt  );	
	if  (  FAILED(  hr  )  )  goto  errLabel;

	//
	hr  =  p->p_g_cfg_keys_alphaArray->SetFloatArray(  g_cfg_keys_alphaArray,  0,  pCfg->usCnt  *  CONST_alphaArrayCnt  );
	if  (  FAILED(  hr  )  )  goto  errLabel;

	//
	hr  =  p->p_g_iImgW->SetInt(  pCtx->wnd_w  );
	if  (  FAILED(  hr  )  )  goto  errLabel;
	hr  =  p->p_g_iImgH->SetInt(  pCtx->wnd_h  );
	if  (  FAILED(  hr  )  )  goto  errLabel;

	//
	hr  =  p->p_g_lBlurSize->SetInt(  pCfg->lBlurSize  );
	if  (  FAILED(  hr  )  )  goto  errLabel;

	//
	hr  =  p->p_g_ws_preBlur->SetFloatArray(  g_ws_preBlur,  0,  pCfg->lBlurSize  );
	if  (  FAILED(  hr  )  )  goto  errLabel;
	hr  =  p->p_g_ws_postBlur->SetFloatArray(  g_ws_postBlur,  0,  pCfg->lBlurSize  );
	if  (  FAILED(  hr  )  )  goto  errLabel;

	//
	DWORD  tn  =  GetTickCount(  );
	hr  =  p->p_g_tn_modified->SetInt(  tn  );	//  0表明需要重新初始化
	if  (  FAILED(  hr  )  )  goto  errLabel;

#endif

	iErr  =  0;
errLabel:
	
	if  (  iErr  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "ChromaKey_inputParams_update failed"  )  );
		#endif
	}

	if  (  !iErr  )  {
		#ifdef  __DEBUG__
		traceLog(  _T(  "ChromaKey_inputParams_update ok, fSigma_preBlur %f, fSigma_postBlur %f"  ),  pCfg->fSigma_preBlur,  pCfg->fSigma_postBlur  );
		#endif
	}

	return  iErr;
}
#endif


