
#include "stdafx.h"

#include	<stdlib.h>
#include	<math.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"tmpCeLib.h"

//#include	"myresource.h"
#include	"qmcVWall.h"
#include	"WallTalkers.h"

#include	"qmcVideoCapture_isCli.h"
#include	"qyVk.h"

#include	"qmcDxSurfacePublic.h"

#include	"qyCusResTemp.h"

#include	"qyAvRecordPublic.h"

#include	"sp.h"
//#include "isCliHelp.h"
//#include "DlgImg.h"
//#include "afxdialogex.h"

#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"qycusResTemp.h"

#include	"myDb.h"

#include	"qyMcMainCommon.h"
//#include "isCliHelp.h"
//#include "DlgChromaKeyCfg.h"
//#include "afxdialogex.h"

#include	"isCliHelpPublic.h"
#include	"imgProcessPublic.h"

int	 siCnt_parse = 10;
BOOL  bDumped_keyFile = FALSE;


#ifdef  __DEBUG__
__declspec(dllexport)  int  startToParse()
{
	traceLog(_T("startToParse: "));

	siCnt_parse = 0;
	bDumped_keyFile = FALSE;

	return  0;
}


#endif

//
__declspec(dllexport)  int  getImgProcessCfg(QY_MC   *  pQyMc,  void* pIMG_process_cfg)
{
	int  iErr = -1;

	IMG_process_cfg* pCfg = (IMG_process_cfg*)pIMG_process_cfg;

	if (!pCfg)  return  -1;

	//QY_MC* pQyMc = QY_GET_GBUF();
	//if (!pQyMc)  goto  errLabel;

	//
	memset(pCfg, 0, sizeof(pCfg));

	//
	IMG_process_cfg  regCfg;
	memset(&regCfg, 0, sizeof(regCfg));

	COLORREF  init_color = RGB(0, 255, 0);
	regCfg.usCnt = 1;
#if 0
	//  regCfg.reverseColor  =  RGB(  70,41,41  );
	regCfg.ucMax_edge_d = 15;
	regCfg.f_reversoColor10x = 0.5 * 10;
#endif
	regCfg.minVal_r_g_b = 35;
	regCfg.usMin_saturation = 36.;
	regCfg.usMin_lightness = 28.8;
	regCfg.usMax_lightness = 192.;
	regCfg.fSigma_preBlur = 2.0;
	regCfg.fSigma_postBlur = 2.0;
	regCfg.fGamma = 1.5;

#ifdef  __DEBUG__
#if  0
	regCfg.bThinEdge = TRUE;
	traceLog(_T("for test: bThinEdge is true"));
#endif
#endif

	//
	QY_REG			reg;
	TCHAR* pRegVal = NULL;
	TCHAR			tBuf[256] = _T("");
	TCHAR			tRegBuf[256] = _T("");
	int				i, r, g, b;
	unsigned int	tola, tolb;
	float			fm;
	int				errCnt = 0;
	unsigned  short  usCnt;
	COLORREF  color;
	BOOL			bValue = FALSE;

	reg.hKeyRoot0 = HKEY_CURRENT_USER;
	_sntprintf(reg.rootKey, sizeof(reg.rootKey), _T("%s"), pQyMc->cfg.pSysCfg->rootKey_qnmScheduler);

	pRegVal = CONST_regValName_keyCfg_bUseKey;
	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, mycountof(tBuf), 0)) {
		regCfg.bUseChromaKey = _ttol(tBuf);
	}

	pRegVal = CONST_regValName_keyCfg_usCnt;
	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, mycountof(tBuf), 0))
	{
		usCnt = _ttol(tBuf);
		if (usCnt <= 0 && usCnt > mycountof(regCfg.keys))  usCnt = 1;
		//
		if (usCnt != regCfg.usCnt)  regCfg.usCnt = usCnt;
	}

	pRegVal = CONST_regValName_keyCfg_minRgb;
	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, mycountof(tBuf), 0)) {
		color = _ttof(tBuf);
		if (color > 255 || color < 0)  color = 35;
		//
		if (color != regCfg.minVal_r_g_b)  regCfg.minVal_r_g_b = color;
	}

	pRegVal = CONST_regValName_keyCfg_minS;
	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, mycountof(tBuf), 0)) {
		fm = _ttof(tBuf);
		if (fm > 240 || fm <= 0)  fm = 36.;
		//
		if (fm != regCfg.usMin_saturation)  regCfg.usMin_saturation = fm;
	}


	pRegVal = CONST_regValName_keyCfg_minL;
	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, mycountof(tBuf), 0)) {
		fm = _ttof(tBuf);
		if (fm > 240 || fm <= 0)  fm = 28.8;
		//
		if (fm != regCfg.usMin_lightness)  regCfg.usMin_lightness = fm;
	}

	pRegVal = CONST_regValName_keyCfg_maxL;
	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, mycountof(tBuf), 0)) {
		fm = _ttof(tBuf);
		if (fm > 240 || fm <= 0)  fm = 192.;
		//
		if (fm != regCfg.usMax_lightness)  regCfg.usMax_lightness = fm;
	}
#if 0
	pRegVal = CONST_regValName_keyCfg_bStartSmooth;
	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, mycountof(tBuf), 0)) {
		bValue = _ttof(tBuf);
		//
		if (bValue != regCfg.bStartSmooth)  regCfg.bStartSmooth = bValue;
	}


	pRegVal = CONST_regValName_keyCfg_bEdgeColor;
	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, mycountof(tBuf), 0)) {
		bValue = _ttof(tBuf);
		//		
		if (bValue != regCfg.bEdgeColor)  regCfg.bEdgeColor = bValue;
	}

	pRegVal = CONST_regValName_keyCfg_r_rgb;
	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, mycountof(tBuf), 0)) {
		color = _ttof(tBuf);
		if (color > 255 || color < 0)  color = 35;
		//
		if (color != regCfg.reverseColor)  regCfg.reverseColor = color;
	}

	pRegVal = CONST_regValName_keyCfg_r_f;
	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, mycountof(tBuf), 0)) {
		fm = _ttof(tBuf);
		if (fm > 1.0 || fm < 0.)  fm = 0.5;
		//
		if (fm * 10 != regCfg.f_reversoColor10x)  regCfg.f_reversoColor10x = fm * 10;
	}
#endif
	pRegVal = CONST_regValName_keyCfg_preBlur;
	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, mycountof(tBuf), 0)) {
		fm = _ttof(tBuf);
		if (fm > (200.0 / 20.) || fm < 0.)  fm = 2.;
		//
		if (fm != regCfg.fSigma_preBlur) regCfg.fSigma_preBlur = fm;
	}

	pRegVal = CONST_regValName_keyCfg_postBlur;
	if (!qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, mycountof(tBuf), 0)) {
		fm = _ttof(tBuf);
		if (fm > (200.0 / 20.) || fm < 0.)  fm = 2.;
		//
		if (fm != regCfg.fSigma_postBlur) regCfg.fSigma_postBlur = fm;
	}

	_sntprintf(tRegBuf, mycountof(tRegBuf), _T("%s"), reg.rootKey);

	for (i = 0; i < regCfg.usCnt; i++) {
		_sntprintf(reg.rootKey, sizeof(reg.rootKey), _T("%s\\key%d"), tRegBuf, i);

		errCnt = 0;
		r = GetRValue(init_color);
		pRegVal = CONST_regValName_key_r;
		if (qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, mycountof(tBuf), 0)) { errCnt++; }
		else {
			r = _ttol(tBuf);
			if (r > 255 || r < 0)  r = 0;
		}
		if (r != toByte_rgb(regCfg.keys[i].rgb_key.r))  regCfg.keys[i].rgb_key.r = toFloat_rgb(r);

		g = GetGValue(init_color);
		pRegVal = CONST_regValName_key_g;
		if (qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, mycountof(tBuf), 0)) { errCnt++; }
		else {
			g = _ttol(tBuf);
			if (g > 255 || g < 0) g = 255;
		}
		if (g != toByte_rgb(regCfg.keys[i].rgb_key.g))  regCfg.keys[i].rgb_key.g = toFloat_rgb(g);

		b = GetBValue(init_color);
		pRegVal = CONST_regValName_key_b;
		if (qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, mycountof(tBuf), 0)) { errCnt++; }
		else {
			b = _ttol(tBuf);
			if (b > 255 || b < 0) b = 0;
		}
		if (b != toByte_rgb(regCfg.keys[i].rgb_key.b))  regCfg.keys[i].rgb_key.b = toFloat_rgb(b);

		tola = CONST_key_tola;
		pRegVal = CONST_regValName_key_tola;
		if (qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, mycountof(tBuf), 0)) { errCnt++; }
		else {
			//  tola100x  =  _ttof(  tBuf  )  *  100;
			tola = _ttol(tBuf);
			if (tola > 200)  tola = CONST_key_tola;
		}
		if (tola != regCfg.keys[i].tola)  regCfg.keys[i].tola = tola;


		tolb = CONST_key_tolb;
		pRegVal = CONST_regValName_key_tolb;
		if (qyGetRegCfgT(reg.hKeyRoot0, reg.rootKey, pRegVal, (char*)tBuf, mycountof(tBuf), 0)) { errCnt++; }
		else {
			//  tolb100x  =  _ttof(  tBuf  )  *  100;
			tolb = _ttol(tBuf);
			if (tolb > 200)  tolb = CONST_key_tolb;
		}
		if (tolb <= tola)  tolb = tola + 1;
		if (tolb != regCfg.keys[i].tolb)  regCfg.keys[i].tolb = tolb;

		{
			BYTE  h = 0, s = 0, l = 0;
			//  ColorRGBToHLS(  RGB(  regCfg.keys[i].cfg.r_key,  regCfg.keys[i].cfg.g_key,  regCfg.keys[i].cfg.b_key  ),  &h,  &l,  &s  );
			convert_rgb_to_key_pixel(toByte_rgb(regCfg.keys[i].rgb_key.r), toByte_rgb(regCfg.keys[i].rgb_key.g), toByte_rgb(regCfg.keys[i].rgb_key.b), &h, &s, &l);
#ifdef  __USE_hsl_chromaKey__
			regCfg.keys[i].hsl_key.x = toFloat_hsl(h);
			regCfg.keys[i].hsl_key.y = toFloat_hsl(s);
			regCfg.keys[i].hsl_key.z = toFloat_hsl(l);
#else
#if  0
			regCfg.keys[i].cfg.ucY_key = l;
			regCfg.keys[i].cfg.ucCb_key = h;
			regCfg.keys[i].cfg.ucCr_key = s;
#endif

#endif
		}
	}

	iErr = 0;
errLabel:

	memcpy(pCfg, &regCfg, sizeof(regCfg));

	return  iErr;
}


#ifdef  __DEBUG__
static  int  real_i_btnDown = 0;
static  int	 real_j_btnDown = 0;
static  int  img_i_btnDown = 0;
static  int  img_j_btnDown = 0;


__declspec(dllexport)  int  get_real_ij_btnDown(int* p_real_i, int* p_real_j, int* p_img_i, int* p_img_j)
{
	if (p_real_i)  *p_real_i = real_i_btnDown;
	if (p_real_j)  *p_real_j = real_j_btnDown;
	if (p_img_i)  *p_img_i = img_i_btnDown;
	if (p_img_j)  *p_img_j = img_j_btnDown;
	return  0;
}

#endif



