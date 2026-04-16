// DlgVideoTagCfg.cpp : implementation file
//

#include	"stdafx.h"

#include	"qyMcMainCommon.h"
#include	"myresource.h"

#include	"DlgVideoTagCfg.h"
#include	"afxdialogex.h"

#include	"qyCusResTemp.h"

//  #include	"DlgSubtitleSelect.h"

#include	"qmcCmdProc.h"

#include	"qyOpenShellCommon.h"
//  #include	"DlgTalk.h"
#include	"dlgTalkProc.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"isCliD3dPublic.h"

#include	"subtitlesCfg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//  #define		DEFAULT_lineIndex			0

 BOOL  bLine_title_subtitles(  int  index  )
{
	if  (  index  ==  0  )  return  TRUE;
	return  FALSE;
}

 int  getLineIndex_bottom_subtitles(  )
{
	//  return  MAX_subtitlesCfg_mems  -  1;
	return  CONST_realMax_subtitles  -  1;			//  2014/12/21
}

int  getLineIndex_default_subtitles(  )
{
	//  return  MAX_subtitlesCfg_mems  -  1;
	return  CONST_realMax_subtitles  -  1;			//  2014/12/21
}
  
//
__declspec(  dllexport  )  int  viewDlgSubtitles(  int  iSharedObjType,  int  iCapType,  int  iCapSubType,  HWND  hParent  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int					iErr	=	-1;

	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	CDlgVideoTagCfg			*		pDlg					=	NULL;
	RECT							rect;

	HWND					*		phWnd_lv				=	NULL;

	if  (  IsWindow(  pProcInfo->subtitles.hWnd_videoTagCfg  )  )  {
		CDlgVideoTagCfg  *  tmp_pDlg  =  (  CDlgVideoTagCfg  *  )CWnd::FromHandle(  pProcInfo->subtitles.hWnd_videoTagCfg  );
		if  (  !tmp_pDlg  )  goto  errLabel;
		if  (  tmp_pDlg->m_var.iCapType  !=  iCapType 
			||  tmp_pDlg->m_var.iCapSubType  !=  iCapSubType  )
		{
			SendMessage(  pProcInfo->subtitles.hWnd_videoTagCfg,  WM_CLOSE,  0,  0  );
			if  (  IsWindow(  pProcInfo->subtitles.hWnd_videoTagCfg  )  )  {
				goto  errLabel;
			}
		}

	}

	//
	phWnd_lv  =  &pProcInfo->subtitles.hWnd_videoTagCfg;

	if  (  phWnd_lv  )  {
		if  (  IsWindow(  *phWnd_lv  )  )  {
			MACRO_SetForegroundWindow(  *phWnd_lv  );
			iErr  =  0;  goto  errLabel;
		}

		*phWnd_lv  =  NULL;
	}

		//
	pDlg  =  new  CDlgVideoTagCfg(  CWnd::GetDesktopWindow(  )  );
	if  (  !pDlg  )  goto  errLabel;

	if  (  !pDlg->bSetInfo(  iSharedObjType,  iCapType,  iCapSubType,  0  )  )  goto  errLabel;
	
	//
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;
	pDlg->ShowWindow(  SW_SHOW  );


	//
	if  (  phWnd_lv  )  *phWnd_lv  =  pDlg->m_hWnd;

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}



	return  iErr;
}



__declspec(  dllexport  )  int  viewDlgSubtitles_talk(  int  iSharedObjType,  int  iCapType,  int  iCapSubType,  int  iUsage,  HWND  hParent,  HWND  hCurTalk,  void  *  pCurVarParam,  void  *  pMgrVarParam  )

{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int					iErr	=	-1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	//  FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );

	CDlgVideoTagCfg			*		pDlg					=	NULL;
	RECT							rect;

	HWND					*		phWnd_lv				=	NULL;


	DLG_TALK_var  *  pCurVar  =  (  DLG_TALK_var  *  )pCurVarParam;
	DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var  *  )pMgrVarParam;

	//
	HWND	hMgr	=	NULL;
	//  DLG_TALK_var  *  pCurVar  =  pFuncs->pf_getDlgTalkVar(  hCurTalk  );
	if  (  !pCurVar  )  goto  errLabel;
	if  (  isTalkerShadowMgr(  pCurVar->addr  )  )  hMgr  =  hCurTalk;
	else  {
		  TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pCurVar->pShadowInfo;
		  if  (  !pShadow  )  goto  errLabel;
		  hMgr  =  pShadow->hMgr;
	}
	//  DLG_TALK_var  *  pMgrVar  =  pFuncs->pf_getDlgTalkVar(  hMgr  );
	if  (  !pMgrVar  )  goto  errLabel;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;


	//
	phWnd_lv  =  &pCurVar->subtitles.hWnd_subtitles;	//  &pProcInfo->subtitles.hWnd_videoTagCfg;

	if  (  phWnd_lv  )  {
		if  (  IsWindow(  *phWnd_lv  )  )  {
			MACRO_SetForegroundWindow(  *phWnd_lv  );
			iErr  =  0;  goto  errLabel;
		}

		*phWnd_lv  =  NULL;
	}

	//
	if  (  pShadowMgr->subtitles.hWnd_subtitles  )  {
		if  (  IsWindow(  pShadowMgr->subtitles.hWnd_subtitles  )  )  {
			SendMessage(  pShadowMgr->subtitles.hWnd_subtitles,  WM_CLOSE,  0,  0  );
		}
		if  (  IsWindow(  pShadowMgr->subtitles.hWnd_subtitles  )  )  goto  errLabel;
	}
	memset(  &pMgrVar->subtitles,  0,  sizeof(  pMgrVar->subtitles  )  );
	
	//
	pDlg  =  new  CDlgVideoTagCfg(  CWnd::FromHandle(  hParent  )  );
	if  (  !pDlg  )  goto  errLabel;

	if  (  !pDlg->bSetInfo(  iSharedObjType,  iCapType,  iCapSubType,  iUsage  )  )  goto  errLabel;
	pDlg->m_var.hDlgTalk_mgr  =  hMgr;	//  hCurTalk;
	
	//
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;
	pDlg->ShowWindow(  SW_SHOW  );


	//
	if  (  phWnd_lv  )  *phWnd_lv  =  pDlg->m_hWnd;
	pShadowMgr->subtitles.hWnd_subtitles  =  pDlg->m_hWnd;


	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}



	return  iErr;
}



//


__declspec(  dllexport  )  int  getSubtitlesCfg(  int  iCapType,  int  iCapSubType,  int  iUsage,  SUBTITLES_cfg  *  pSubtitlesCfg  )
{
	if  (  !pSubtitlesCfg  )  return  -1;

	if  (  iCapType  ==  CONST_capType_mosaic  &&  iUsage  ==  CONST_usage_mosaic_sys    )  return  -1;
	
	memset(  pSubtitlesCfg,  0,  sizeof(  pSubtitlesCfg[0]  )  );
	
	//   2017/07/11
	if  (  iCapType  ==  CONST_capType_av  &&  iCapSubType  ==  0  )  return  0;



	//
	QY_MC			*	pQyMc				=	QY_GET_GBUF(  );
	if  (  !pQyMc  )  {
		traceLog(  _T(  "getSubtitlesCfg failed: pQyMc is null"  )  );
		return  -1;
	}
	QY_REG				reg;
	unsigned  char		ucCmd;
	TCHAR			*	pRegVal				=	NULL;
	char				buf[256];
	TCHAR			name[128]		=	_T(  ""  );
	TCHAR				tBuf[256]	=	_T(  ""  );
	TCHAR				rootKeyBuf[256]		=  _T(  ""  );
	TCHAR		*	pT;
	//  long			lVal;
	
	memset(  &reg,  0,  sizeof(  reg  )  );
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;

#if  0
	 if  (  !(  pT  =  qyGetDesByType(  CONST_capTypeTable,  iCapType  )  )  )  return  -1;		 
	 if  (  !pT[0]  )  return  -1;
	 _sntprintf(  name,  mycountof(  name  ),  _T(  "%s"  ),  pT  );
	 if  (  iCapSubType  )  {
		 if  (  !(  pT  =  qyGetDesByType(  CONST_subCapTypeTable,  iCapSubType  )  )  )  return  -1;
		 if  (  !pT[0]  )  return  -1;
		 _sntprintf(  name,  mycountof(  name  ),  _T(  "%s.%s"  ),  name,  pT  );
	 }

	 _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  name  );
#endif
	 getRegRootKey_qmc(  iCapType,  iCapSubType,  iUsage,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	 safeTcsnCpy(  reg.rootKey, rootKeyBuf,  mycountof(  rootKeyBuf  )  );

	//  2011/08/02
	ucCmd  =  DEFAULT_subtitles_ucbShowVideoHint;
	pRegVal  =  CONST_regValName_ucbShowVideoHint;			//  2013/03/11
	if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  ucCmd  =  atol(  buf  );
	pSubtitlesCfg->flgs.ucbShowVideoHint  =  ucCmd;
	
	ucCmd  =  DEFAULT_subtitles_ucbEffectiveImmediately;
	pRegVal  =  CONST_regValName_ucbEffectiveImmediately;			//  2013/03/11
	if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  ucCmd  =  atol(  buf  );
	pSubtitlesCfg->flgs.ucbEffectiveImmediately  =  ucCmd;

	int  i;
	for  (  i  =  0;  i  <  mycountof(  pSubtitlesCfg->mems  );  i  ++  )  {

		_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\subtitle%d"  ),  rootKeyBuf,  i  );
		 //
		 SUBTITLE_cfg  *  pVideoTagCfg  =  &pSubtitlesCfg->mems[i].subtitle;

		 //		 
		 lstrcpyn(  pVideoTagCfg->font.lf.lfFaceName,  DEFAULT_faceName,  mycountof(  pVideoTagCfg->font.lf.lfFaceName  )  );
		 pRegVal  =  CONST_regValName_faceName;
		 if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {		 
			 lstrcpyn(  pVideoTagCfg->font.lf.lfFaceName,  tBuf,  sizeof(  pVideoTagCfg->font.lf.lfFaceName  )  );
		 }
		 		 
		 pVideoTagCfg->font.iFontSize  =  DEFAULT_fontSize;
#if  0
		 switch  (  i  )  {
				 case  1:
						pVideoTagCfg->font.iFontSize  =  DEFAULT_fontSize_1;
						break;
				 case  2:
						pVideoTagCfg->font.iFontSize  =  DEFAULT_fontSize_2;
						break;
				 case  3:
						pVideoTagCfg->font.iFontSize  =  DEFAULT_fontSize_3;
						break;
				 case  4:
						pVideoTagCfg->font.iFontSize  =  DEFAULT_fontSize_4;
						break;
				 case  5:
						pVideoTagCfg->font.iFontSize  =  DEFAULT_fontSize_5;
						break;
				 case  6:
						pVideoTagCfg->font.iFontSize  =  DEFAULT_fontSize_6;
						break;
				 case  7:
						pVideoTagCfg->font.iFontSize  =  DEFAULT_fontSize_7;
						break;
				 default:
						break;					  
		 }
#endif
		 //
		 if  (  iCapType  ==  CONST_capType_screen  )  pVideoTagCfg->font.iFontSize  =  DEFAULT_fontSize;
		 //
		 pRegVal  =  CONST_regValName_fontSize;
		 if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  pVideoTagCfg->font.iFontSize  =  _ttol(  (  TCHAR  *  )buf  );
		 
		 pVideoTagCfg->font.lf.lfHeight  =  DEFAULT_fontHeight;	
		 switch  (  i  )  {
				 case  0:
					   pVideoTagCfg->font.lf.lfHeight  =  DEFAULT_fontHeight_0;	
					   break;
#if  0
				 case  1:
					   pVideoTagCfg->font.lf.lfHeight  =  DEFAULT_fontHeight_1;	
					   break;
				 case  2:
					   pVideoTagCfg->font.lf.lfHeight  =  DEFAULT_fontHeight_2;	
					   break;
				 case  3:
					   pVideoTagCfg->font.lf.lfHeight  =  DEFAULT_fontHeight_3;	
					   break;
				 case  4:
					   pVideoTagCfg->font.lf.lfHeight  =  DEFAULT_fontHeight_4;	
					   break;
				 case  5:
					   pVideoTagCfg->font.lf.lfHeight  =  DEFAULT_fontHeight_5;	
					   break;
				 case  6:
					   pVideoTagCfg->font.lf.lfHeight  =  DEFAULT_fontHeight_6;	
					   break;
				 case  7:
					   pVideoTagCfg->font.lf.lfHeight  =  DEFAULT_fontHeight_7;	
					   break;
#endif
				 default:
						break;
		 }
		 //
		 if  (  iCapType  ==  CONST_capType_screen  )  pVideoTagCfg->font.lf.lfHeight  =  DEFAULT_fontHeight;	
		 //
		pRegVal  =  CONST_regValName_fontHeight;
		if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  pVideoTagCfg->font.lf.lfHeight  =  _ttol(  (  TCHAR  *  )buf  );

		pVideoTagCfg->font.lf.lfWeight  =  FW_BOLD;		//  FW_NORMAL;
		pRegVal  =  CONST_regValName_fontWeight;
		if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  pVideoTagCfg->font.lf.lfWeight  =  _ttol(  (  TCHAR  *  )buf  );

		pVideoTagCfg->font.lf.lfCharSet  =  DEFAULT_CHARSET;		//  2013/03/24
		pRegVal  =  CONST_regValName_fontCharset;
		if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  pVideoTagCfg->font.lf.lfCharSet  =  _ttol(  (  TCHAR  *  )buf  );

		pVideoTagCfg->font.lf.lfItalic  =  DEFAULT_fontItalic;		//  2013/03/24
		pRegVal  =  CONST_regValName_fontItalic;
		if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  pVideoTagCfg->font.lf.lfItalic  =  _ttol(  (  TCHAR  *  )buf  );

		//  注册表里要存rgb指.读出后用GetRValue(  ), GetGValue(  ),  GetBValue(  )分解出r,g,b
		COLORREF	fontColor  =  DEFAULT_fontColor_addTxt;
#if  0
		switch  (  i  )  {
				case  1:
					   fontColor  =  DEFAULT_fontColor_addTxt_1;
					   break;
				case  2:
					   fontColor  =  DEFAULT_fontColor_addTxt_2;
					   break;
				case  3:
					   fontColor  =  DEFAULT_fontColor_addTxt_3;
					   break;
				case  4:
					   fontColor  =  DEFAULT_fontColor_addTxt_4;
					   break;
				case  5:
					   fontColor  =  DEFAULT_fontColor_addTxt_5;
					   break;
				case  6:
					   fontColor  =  DEFAULT_fontColor_addTxt_6;
					   break;
				case  7:
					   fontColor  =  DEFAULT_fontColor_addTxt_7;
					   break;
				default:
						break;
		}
#endif
		//
		if  (  iCapType  ==  CONST_capType_screen  )  fontColor  =  DEFAULT_fontColor_addTxt_screen;
		//  
		pRegVal  =  CONST_regValName_fontColor;
		if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  fontColor  =  _ttol(  (  TCHAR  *  )buf  );
		pVideoTagCfg->color.fontColor_r  =  GetRValue(  fontColor  );
		pVideoTagCfg->color.fontColor_g  =  GetGValue(  fontColor  );
		pVideoTagCfg->color.fontColor_b  =  GetBValue(  fontColor  );

	
		//
		COLORREF	maskColor  =  DEFAULT_maskColor_addTxt;
		//  pVideoTagCfg->others.maskColor  =  RGB(  222,  222,  222  );				 
		pRegVal  =  CONST_regValName_maskColor;
		if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  maskColor  =  _ttol(  (  TCHAR  *  )buf  );
		pVideoTagCfg->color.maskColor_r  =  GetRValue(  maskColor  );
		pVideoTagCfg->color.maskColor_g  =  GetGValue(  maskColor  );
		pVideoTagCfg->color.maskColor_b  =  GetBValue(  maskColor  );

#if 0
		ucCmd  =  DEFAULT_ucb3DShadow;
		pRegVal  =  CONST_regValName_ucb3DShadow;
		if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  ucCmd  =  atol(  buf  );
		pVideoTagCfg->color.ucb3dShadow  =  ucCmd;

		COLORREF	shadowColor	 =  DEFAULT_shadowColor_addTxt;
		pRegVal  =  CONST_regValName_shadowColor;
		if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ), 0  )  )  shadowColor  =  _ttol(  (  TCHAR  *  )buf  );
		pVideoTagCfg->color.shadowColor_r  =  GetRValue(  shadowColor  );
		pVideoTagCfg->color.shadowColor_g  =  GetGValue(  shadowColor  );
		pVideoTagCfg->color.shadowColor_b  =  GetBValue(  shadowColor  );

		pVideoTagCfg->color.shadow_xOffset  =  DEFAULT_shadow_xOffset;
		pRegVal  =  CONST_regValName_xOffset;
		if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  pVideoTagCfg->color.shadow_xOffset  =  _ttol(  (  TCHAR  *  )buf  );

		pVideoTagCfg->color.shadow_yOffset  =  DEFAULT_shadow_yOffset;
		pRegVal  =  CONST_regValName_yOffset;
		if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  pVideoTagCfg->color.shadow_yOffset  =  _ttol(  (  TCHAR  *  )buf  );
#endif
		ucCmd  =  DEFAULT_ucbUsePath;
		pRegVal  =  CONST_regValName_ucbUsePath;
		if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  ucCmd  =  atol(  buf  );
		pVideoTagCfg->color.usePath.ucbUsePath  =  ucCmd;

		COLORREF	shadowColor	 =  DEFAULT_edgeColor;
		pRegVal  =  CONST_regValName_edgeColor;
		if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ), 0  )  )  shadowColor  =  _ttol(  (  TCHAR  *  )buf  );
		pVideoTagCfg->color.usePath.color_edge_r  =  GetRValue(  shadowColor  );
		pVideoTagCfg->color.usePath.color_edge_g  =  GetGValue(  shadowColor  );
		pVideoTagCfg->color.usePath.color_edge_b  =  GetBValue(  shadowColor  );
		
		pVideoTagCfg->color.usePath.cWidth_pen  =  DEFAULT_edge_width;
		pRegVal  =  CONST_regValName_edgeWidth;
		if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  pVideoTagCfg->color.usePath.cWidth_pen  =  _ttol(  (  TCHAR  *  )buf  );

		pVideoTagCfg->color.usePath.ucbFilled  =  DEFAULT_bFilled;
		pRegVal  =  CONST_regValName_bFilled;
		if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  pVideoTagCfg->color.usePath.ucbFilled  =  _ttol(  (  TCHAR  *  )buf  );

		//  2014/12/22
		ucCmd  =  DEFAULT_ucbHorizontalCenter;
		if  (  bLine_title_subtitles(  i  )  )  ucCmd  =  DEFAULT_ucbHorizontalCenter_titleLine;

		pRegVal  =  CONST_regValName_ucbHorizontalCenter;
		if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  ucCmd  =  atol(  buf  );
		pVideoTagCfg->pos.ucbHorizontalCenter  =  ucCmd;

		//
		pVideoTagCfg->pos.xStart  =  DEFAULT_xStart_addTxt;	//  11;
		pRegVal  =  CONST_regValName_xStart;
		if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  pVideoTagCfg->pos.xStart  =  _ttol(  (  TCHAR  *  )buf  );

		if  (  i  ==  1  )  {
			pVideoTagCfg->pos.yStart  =  DEFAULT_yStart_addTxt  +  50;	//  1;	
			}
		else if  (  i  ==  getLineIndex_bottom_subtitles(  )  )  pVideoTagCfg->pos.yStart  =  DEFAULT_yStart_addTxt;		//  最底的行用bottomUp
		else  {
			pVideoTagCfg->pos.yStart  =  DEFAULT_yStart_addTxt  +  ((  i >  1  )  ?  50  +  ( i - 1 )  *  36  :  1  );	//  1;	
		}
		//  2015/06/23					
		if  (  pQyMc->ucbDaemonDemo  )  {
				//
			    int  ii  =  0;
				//
				if  (  i  ==  0  )  {
					pVideoTagCfg->pos.yStart  =  DEFAULT_yStart_addTxt  +  50  +  ii;
					}
				else if  (  i  ==  getLineIndex_bottom_subtitles(  )  )  pVideoTagCfg->pos.yStart  =  DEFAULT_yStart_addTxt;		//  最底的行用bottomUp
				else  {
					pVideoTagCfg->pos.yStart  =  DEFAULT_yStart_addTxt  +  50  +  ii  +  i *  36;	//  1;	
				}			 		
		}
#ifdef  __DEBUG__
		//if  (  i  ==  0  )  pVideoTagCfg->pos.yStart  =  150;
#endif
		//
		pRegVal  =  CONST_regValName_yStart;
		if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  {
			pVideoTagCfg->pos.yStart  =  _ttol(  (  TCHAR  *  )buf  );
		}
		//
		ucCmd  =  DEFAULT_ucbBottomUp;
		if  (  i  ==  getLineIndex_bottom_subtitles(  )  )  ucCmd  =  DEFAULT_ucbBottomUp_bottomLine;
		//
		pRegVal  =  CONST_regValName_ucbFromBottomUp;			//  2013/03/11
		if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  ucCmd  =  atol(  buf  );
		pVideoTagCfg->pos.ucbBottomUp  =  ucCmd;

		ucCmd  =  FALSE;
		pRegVal  =  CONST_regValName_ucbDisplayTime;			//  2013/03/11
		if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  ucCmd  =  atol(  buf  );
		pVideoTagCfg->tag.ucbDisplayTime  =  ucCmd;

		//  从注册表里读取txt, 如果没有注册表项,则设置tag.ucbDefault		
		unsigned  char	ucbUseDefault  =  TRUE;
		TCHAR	tmpBuf[256]	=	_T(  ""  );
		pRegVal  =  CONST_regValName_subtitles;
		if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  (  char  *  )tmpBuf,  sizeof(  tmpBuf  ),  0  )  )  {
			ucbUseDefault  =  FALSE;
		}
		safeTcsnCpy(  tmpBuf,  pVideoTagCfg->tag.txt,  mycountof(  pVideoTagCfg->tag.txt  )  );
		pVideoTagCfg->tag.ucbUseDefault  =  ucbUseDefault;

	}
	//
	return  0;
}

//  iCapSubType为webcam时,只存一个tag就可以了
int  saveSubtitlesCfg(  int  iCapType,  int  iCapSubType,  int  iUsage,  SUBTITLES_cfg  *  pSubtitlesCfg  )
{
	QY_MC			*	pQyMc				=	QY_GET_GBUF(  );
	QY_REG				reg;
	unsigned  char		ucCmd;
	TCHAR			*	pRegVal				=	NULL;
	char				buf[256];
	TCHAR				tBuf[256]	=  _T(  ""  );
	TCHAR				rootKeyBuf[256]	=	_T(  ""  );
	COLORREF			color,maskColor,edgeColor;

	TCHAR			name[128]		=	_T(  ""  );
	TCHAR		*	pT;
	//  long			lVal;
	
	SUBTITLES_cfg		oldCfg;
	if  (  getSubtitlesCfg(  iCapType,  iCapSubType,  0,  &oldCfg  )  )  memset(  &oldCfg,  0,  sizeof(  oldCfg  )  );
	
	//
	memset(  &reg,  0,  sizeof(  reg  )  );
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
		
	 getRegRootKey_qmc(  iCapType,  iCapSubType,  iUsage,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	 safeTcsnCpy(  reg.rootKey,  rootKeyBuf,  mycountof(  rootKeyBuf  )  );
	 //
	 if  (  pSubtitlesCfg->flgs.ucbShowVideoHint  !=  oldCfg.flgs.ucbShowVideoHint  )  {
		 qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_ucbShowVideoHint,  pSubtitlesCfg->flgs.ucbShowVideoHint  ?  _T(  "1"  )  :  _T(  "0"  )  );
	 }

	 if  (  pSubtitlesCfg->flgs.ucbEffectiveImmediately  !=  oldCfg.flgs.ucbEffectiveImmediately  )  {
		 qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_ucbEffectiveImmediately,  pSubtitlesCfg->flgs.ucbEffectiveImmediately  ?  _T(  "1"  )  :  _T(  "0"  )  );
	 }
	 
	int  i;
	for  (  i  =  0;  i  <  mycountof(  pSubtitlesCfg->mems  );  i  ++  )  {

		_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\subtitle%d"  ),  rootKeyBuf,  i  );
		
		if  (  _tcscmp(  pSubtitlesCfg->mems[i].subtitle.tag.txt,  oldCfg.mems[i].subtitle.tag.txt  )  )  {
			qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_subtitles,  pSubtitlesCfg->mems[i].subtitle.tag.txt  );
		}

		if  (  _tcscmp(  pSubtitlesCfg->mems[i].subtitle.font.lf.lfFaceName,  oldCfg.mems[i].subtitle.font.lf.lfFaceName  )  )  {
			qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_faceName,  pSubtitlesCfg->mems[i].subtitle.font.lf.lfFaceName  );
		}
	 
	 if  (  pSubtitlesCfg->mems[i].subtitle.font.iFontSize  !=  oldCfg.mems[i].subtitle.font.iFontSize  )  {
		 qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_fontSize,  CQyString(  _ltot(  pSubtitlesCfg->mems[i].subtitle.font.iFontSize,  tBuf,  10  )  )  );
	 }
	 
	 if  (  pSubtitlesCfg->mems[i].subtitle.font.lf.lfHeight  !=  oldCfg.mems[i].subtitle.font.lf.lfHeight  )  {
		 qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_fontHeight,  CQyString(  _ltot(  pSubtitlesCfg->mems[i].subtitle.font.lf.lfHeight,  tBuf,  10  )  )  );
	 }
	 
	 if  (  pSubtitlesCfg->mems[i].subtitle.font.lf.lfWeight  !=  oldCfg.mems[i].subtitle.font.lf.lfWeight  )  {
		 qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_fontWeight,  CQyString(  _ltot(  pSubtitlesCfg->mems[i].subtitle.font.lf.lfWeight,  tBuf,  10  )  )  );
	 }

	 if  (  pSubtitlesCfg->mems[i].subtitle.font.lf.lfCharSet  !=  oldCfg.mems[i].subtitle.font.lf.lfCharSet  )  {
		 qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_fontCharset,  CQyString(  _ltot(  pSubtitlesCfg->mems[i].subtitle.font.lf.lfCharSet,  tBuf,  10  )  )  );
	 }

	 if  (  pSubtitlesCfg->mems[i].subtitle.font.lf.lfItalic  !=  oldCfg.mems[i].subtitle.font.lf.lfItalic  )  {
		 qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_fontItalic,  CQyString(  _ltot(  pSubtitlesCfg->mems[i].subtitle.font.lf.lfItalic,  tBuf,  10  )  )  );
	 }


	 COLORREF	oldColor;
	 color  =  RGB(  pSubtitlesCfg->mems[i].subtitle.color.fontColor_r,  pSubtitlesCfg->mems[i].subtitle.color.fontColor_g,  pSubtitlesCfg->mems[i].subtitle.color.fontColor_b  );
	 oldColor  =  RGB(  oldCfg.mems[i].subtitle.color.fontColor_r,  oldCfg.mems[i].subtitle.color.fontColor_g,  oldCfg.mems[i].subtitle.color.fontColor_b  );
	 if  (  color  !=  oldColor  )  {
		 qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_fontColor,  CQyString(  _ltot(  color,  tBuf,  10  )  )  );
	 }
	 
	 maskColor  =  RGB(  pSubtitlesCfg->mems[i].subtitle.color.maskColor_r,  pSubtitlesCfg->mems[i].subtitle.color.maskColor_g,  pSubtitlesCfg->mems[i].subtitle.color.maskColor_b  );
	 oldColor  =  RGB(  oldCfg.mems[i].subtitle.color.maskColor_r,  oldCfg.mems[i].subtitle.color.maskColor_g,  oldCfg.mems[i].subtitle.color.maskColor_b  );
	 if  (  maskColor  !=  oldColor  )  {
		 qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_maskColor,  CQyString(  _ltot(  maskColor,  tBuf,  10  )  )  );
	 }

	 //  2014/12/21
	 if  (  pSubtitlesCfg->mems[i].subtitle.color.usePath.ucbUsePath  !=  oldCfg.mems[i].subtitle.color.usePath.ucbUsePath  )  {
		 qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_ucbUsePath,  pSubtitlesCfg->mems[i].subtitle.color.usePath.ucbUsePath  ?  _T(  "1"  )  :  _T(  ""  )  );
	 }

	 edgeColor  =  RGB(  pSubtitlesCfg->mems[i].subtitle.color.usePath.color_edge_r,  pSubtitlesCfg->mems[i].subtitle.color.usePath.color_edge_g,  pSubtitlesCfg->mems[i].subtitle.color.usePath.color_edge_b  );
	 oldColor  =  RGB(  oldCfg.mems[i].subtitle.color.usePath.color_edge_r,  oldCfg.mems[i].subtitle.color.usePath.color_edge_g,  oldCfg.mems[i].subtitle.color.usePath.color_edge_b  );
	 if  (  edgeColor  !=  oldColor  )  {
		 qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_edgeColor,  CQyString(  _ltot(  edgeColor,  tBuf,  10  )  )  );
	 }

	 if  (  pSubtitlesCfg->mems[i].subtitle.color.usePath.cWidth_pen  !=  oldCfg.mems[i].subtitle.color.usePath.cWidth_pen  )  {
		 qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_edgeWidth,  CQyString(  _ltot(  pSubtitlesCfg->mems[i].subtitle.color.usePath.cWidth_pen,  tBuf,  10  )  )  );
	 }

	 if  (  pSubtitlesCfg->mems[i].subtitle.color.usePath.ucbFilled  !=  oldCfg.mems[i].subtitle.color.usePath.ucbFilled  )  {
		 qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_bFilled,  pSubtitlesCfg->mems[i].subtitle.color.usePath.ucbFilled  ?  _T(  "1"  )  :  _T(  ""  )  );
	 }

	 if  (  pSubtitlesCfg->mems[i].subtitle.pos.xStart  !=  oldCfg.mems[i].subtitle.pos.xStart  )  {
		 qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_xStart,  CQyString(  _ltot(  pSubtitlesCfg->mems[i].subtitle.pos.xStart,  tBuf,  10  )  )  );
	 }
	 
	 if  (  pSubtitlesCfg->mems[i].subtitle.pos.yStart  !=  oldCfg.mems[i].subtitle.pos.yStart  )  {
		 qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_yStart,  CQyString(  _ltot(  pSubtitlesCfg->mems[i].subtitle.pos.yStart,  tBuf,  10  )  )  );
	 }

	 if  (  pSubtitlesCfg->mems[i].subtitle.pos.ucbHorizontalCenter  !=  oldCfg.mems[i].subtitle.pos.ucbHorizontalCenter  )  {
		 qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_ucbHorizontalCenter,  pSubtitlesCfg->mems[i].subtitle.pos.ucbHorizontalCenter  ?  _T(  "1"  )  :  _T(  ""  )  );
	 }
	 if  (  pSubtitlesCfg->mems[i].subtitle.pos.ucbBottomUp  !=  oldCfg.mems[i].subtitle.pos.ucbBottomUp  )  {
		 qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_ucbFromBottomUp,  pSubtitlesCfg->mems[i].subtitle.pos.ucbBottomUp  ?  _T(  "1"  )  :  _T(  ""  )  );
	 }

	 if  (  pSubtitlesCfg->mems[i].subtitle.tag.ucbDisplayTime  !=  oldCfg.mems[i].subtitle.tag.ucbDisplayTime  )  {
		 qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_ucbDisplayTime,  pSubtitlesCfg->mems[i].subtitle.tag.ucbDisplayTime  ?  _T(  "1"  )  :  _T(  ""  )  );
	 }
	}
	 //
	/*
	 if  (  !pSubtitlesCfg->mems[i].subtitle.tag.ucbUseDefault  )
		 qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_subtitles,  pSubtitlesCfg->mems[i].subtitle.tag.txt  );	 
	 else 
		 qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_subtitles  );
		 */
	return  0;
}

//  不要删除ucbShowHint
__declspec(  dllexport  )  int  deleteSubtitlesCfg(  int  iCapType,  int  iCapSubType,  int  iUsage  )
{
	int					iErr				=	-1;
	QY_MC			*	pQyMc				=	QY_GET_GBUF(  );
	QY_REG				reg;
	unsigned  char		ucCmd;
	TCHAR			*	pRegVal				=	NULL;
	char				buf[256];
	TCHAR				rootKeyBuf[256]		=	_T(  ""  );
	TCHAR			name[128]		=	_T(  ""  );
	TCHAR		*	pT;
	//  long			lVal;
	
	memset(  &reg,  0,  sizeof(  reg  )  );
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;

#if  0
	 if  (  !(  pT  =  qyGetDesByType(  CONST_capTypeTable,  iCapType  )  )  )  return  -1;		 
	 if  (  !pT[0]  )  return  -1;
	 _sntprintf(  name,  mycountof(  name  ),  _T(  "%s"  ),  pT  );
	 if  (  iCapSubType  )  {
		 if  (  !(  pT  =  qyGetDesByType(  CONST_subCapTypeTable,  iCapSubType  )  )  )  return  -1;
		 if  (  !pT[0]  )  return  -1;
		 _sntprintf(  name,  mycountof(  name  ),  _T(  "%s.%s"  ),  name,  pT  );
	 }

	 _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  name  );
#endif
	 getRegRootKey_qmc(  iCapType,  iCapSubType,  iUsage,  reg.rootKey,  mycountof(  reg.rootKey  )  );  
	 safeTcsnCpy(  reg.rootKey,  rootKeyBuf,  mycountof(  rootKeyBuf  )  );

	int  i;
	for  (  i  =  0;  i  <  12;  i  ++  )  {

		_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\subtitle%d"  ),  rootKeyBuf,  i  );
	 //
	 qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_ucbShowVideoHint  );
	 qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_ucbEffectiveImmediately  );
	 qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_faceName  );
	 qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_fontSize  );
	 qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_fontHeight  );
	 qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_fontWeight  );
	 qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_fontCharset  );
	 qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_fontItalic  );
	 qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_fontColor  );
	 qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_maskColor  );
	 qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_ucbUsePath  );
	 qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_edgeColor  );
	 qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_edgeWidth  );
	 qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_bFilled  );
	 qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_xStart  );
	 qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_yStart  );

	 pRegVal  =  CONST_regValName_ucbHorizontalCenter;
	 qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal  );

	 pRegVal  =  CONST_regValName_ucbFromBottomUp;
	 qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal  );

	 pRegVal  =  CONST_regValName_ucbDisplayTime;
	 qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal  );
	 
	 qyDelRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_subtitles  );


	 if  (  ERROR_SUCCESS  !=  RegDeleteKey(  reg.hKeyRoot0,  reg.rootKey  )  )  iErr  =  -1;
	 else  iErr  =  0;

	}


	return  0;
}



 
 __declspec(  dllexport  )  int  subtitlesCfg_modify(  SUBTITLES_cfg  *  pCfg,  DWORD  dwTickCnt,  BOOL  bForce,  SUBTITLES_cfg  *  pCur,  BOOL  *  pbModified  )   
{
	if  (  !pCfg  ||  !pCur  )  return  -1;
	BOOL  bModified  =  FALSE;

	int  i;
	for  (  i  =  0;  i  <  mycountof(  pCfg->mems  );  i  ++  )  {
		 if  (  memcmp(  &pCfg->mems[i].subtitle,  &pCur->mems[i].subtitle,  sizeof(  pCfg->mems[i].subtitle  )  )
			 ||  memcmp(  &pCfg->flgs,  &pCur->flgs,  sizeof(  pCfg->flgs  )  )  )  
		 {
			 pCur->dwModifiedTickCnt_any_start  =  dwTickCnt;
			 
			 if  (  memcmp(  &pCfg->flgs,  &pCur->flgs,  sizeof(  pCfg->flgs  )  )  )  {
				 memcpy(  &pCur->flgs,  &pCfg->flgs,  sizeof(  pCur->flgs  )  );
			 }
			 
			 if  (  memcmp(  &pCfg->mems[i].subtitle.font,  &pCur->mems[i].subtitle.font,  sizeof(  pCfg->mems[i].subtitle.font  )  )  )  {
				 memcpy(  &pCur->mems[i].subtitle.font,  &pCfg->mems[i].subtitle.font,  sizeof(  pCur->mems[i].subtitle.font  )  );	
				 pCur->mems[i].tickCnts.dwModifiedTickCnt_font  =  dwTickCnt;
			 }
			 
			 if  (  memcmp(  &pCfg->mems[i].subtitle.color,  &pCur->mems[i].subtitle.color,  sizeof(  pCfg->mems[i].subtitle.color  )  )  )  {
				 memcpy(  &pCur->mems[i].subtitle.color,  &pCfg->mems[i].subtitle.color,  sizeof(  pCur->mems[i].subtitle.color  )  );
				 pCur->mems[i].tickCnts.dwModifiedTickCnt_color  =  dwTickCnt;		
			 }

			 if  (  memcmp(  &pCfg->mems[i].subtitle.pos,  &pCur->mems[i].subtitle.pos,  sizeof(  pCfg->mems[i].subtitle.pos  )  )  )  {
				 memcpy(  &pCur->mems[i].subtitle.pos,  &pCfg->mems[i].subtitle.pos,  sizeof(  pCur->mems[i].subtitle.pos  )  );
				 pCur->mems[i].tickCnts.dwModifiedTickCnt_pos  =  dwTickCnt;		
			 }

			 
			 if  (  _tcscmp(  pCfg->mems[i].subtitle.tag.txt,  pCur->mems[i].subtitle.tag.txt  )
				 ||  pCfg->mems[i].subtitle.tag.ucbUseDefault  !=  pCur->mems[i].subtitle.tag.ucbUseDefault 
				 ||  pCfg->mems[i].subtitle.tag.ucbDisplayTime  !=  pCur->mems[i].subtitle.tag.ucbDisplayTime  
				 )  
			 {
				 safeTcsnCpy(  pCfg->mems[i].subtitle.tag.txt,  pCur->mems[i].subtitle.tag.txt,  mycountof(  pCur->mems[i].subtitle.tag.txt  )  );
				 pCur->mems[i].subtitle.tag.ucbUseDefault  =  pCfg->mems[i].subtitle.tag.ucbUseDefault;
				 pCur->mems[i].subtitle.tag.ucbDisplayTime  =  pCfg->mems[i].subtitle.tag.ucbDisplayTime;
				 pCur->mems[i].tickCnts.dwModifiedTickCnt_tag  =  dwTickCnt;
			 }
			 
			 pCur->dwModifiedTickCnt_any_end  =  dwTickCnt;

			 //
			 bModified  =  TRUE;
		 }
	}

	//  2014/12/16
	if  (  bForce  )  {
		pCur->dwModifiedTickCnt_any_start  =  dwTickCnt;
		pCur->dwModifiedTickCnt_any_end  =  dwTickCnt;

		//
		bModified  =  TRUE;
	}

	//
	if  (  pbModified  )  *pbModified  =  bModified;

	return  0;
}


// CDlgVideoTagCfg dialog

IMPLEMENT_DYNAMIC(CDlgVideoTagCfg, CDialogEx)

CDlgVideoTagCfg::CDlgVideoTagCfg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgVideoTagCfg::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	
	//
	m_var.guiData.iIDC_CHECK_showVideoHint  =  IDC_CHECK_showVideoHint;
	//
	m_var.guiData.iIDC_CHECK_effectiveImmediately  =  IDC_CHECK_effectiveImmediately;
	//
	m_var.guiData.iIDC_BUTTON_useDefault  =  IDC_BUTTON_useDefault;	
	//
	m_var.guiData.iIDC_BUTTON_file  =  IDC_BUTTON_file;
	//
	m_var.guiData.iIDC_BUTTON_subtitlesSettings  =  IDC_BUTTON_subtitlesSettings;
	//
	m_var.guiData.iIDC_LIST_subtitles  =  IDC_LIST_subtitles;


	int  i;
	i  =  0;
	m_var.guiData.mems[i].iIDC_STATIC_subtitle  =  IDC_STATIC_subtitle0;
	m_var.guiData.mems[i].iIDC_EDIT_subtitle  =  IDC_EDIT_subtitle0;

	//
	i  ++  ;
	m_var.guiData.mems[i].iIDC_STATIC_subtitle  =  IDC_STATIC_subtitle1;
	m_var.guiData.mems[i].iIDC_EDIT_subtitle  =  IDC_EDIT_subtitle1;

	//
	i  ++  ;
	m_var.guiData.mems[i].iIDC_STATIC_subtitle  =  IDC_STATIC_subtitle2;
	m_var.guiData.mems[i].iIDC_EDIT_subtitle  =  IDC_EDIT_subtitle2;
	
	//
	i  ++  ;
	m_var.guiData.mems[i].iIDC_STATIC_subtitle  =  IDC_STATIC_subtitle3;
	m_var.guiData.mems[i].iIDC_EDIT_subtitle  =  IDC_EDIT_subtitle3;
	
	//
	i  ++  ;
	m_var.guiData.mems[i].iIDC_STATIC_subtitle  =  IDC_STATIC_subtitle4;
	m_var.guiData.mems[i].iIDC_EDIT_subtitle  =  IDC_EDIT_subtitle4;
	
	//
	i  ++  ;
	m_var.guiData.mems[i].iIDC_STATIC_subtitle  =  IDC_STATIC_subtitle5;
	m_var.guiData.mems[i].iIDC_EDIT_subtitle  =  IDC_EDIT_subtitle5;
	
	//
	i  ++  ;
	m_var.guiData.mems[i].iIDC_STATIC_subtitle  =  IDC_STATIC_subtitle6;
	m_var.guiData.mems[i].iIDC_EDIT_subtitle  =  IDC_EDIT_subtitle6;
	
	//
	i  ++  ;
	m_var.guiData.mems[i].iIDC_STATIC_subtitle  =  IDC_STATIC_subtitle7;
	m_var.guiData.mems[i].iIDC_EDIT_subtitle  =  IDC_EDIT_subtitle7;
	
	//
	i  ++  ;
	m_var.guiData.mems[i].iIDC_STATIC_subtitle  =  IDC_STATIC_subtitle8;
	m_var.guiData.mems[i].iIDC_EDIT_subtitle  =  IDC_EDIT_subtitle8;
	
	//
	i  ++  ;
	m_var.guiData.mems[i].iIDC_STATIC_subtitle  =  IDC_STATIC_subtitle9;
	m_var.guiData.mems[i].iIDC_EDIT_subtitle  =  IDC_EDIT_subtitle9;
	
	//
	i  ++  ;
	m_var.guiData.mems[i].iIDC_STATIC_subtitle  =  IDC_STATIC_subtitle10;
	m_var.guiData.mems[i].iIDC_EDIT_subtitle  =  IDC_EDIT_subtitle10;
	
	//
	i  ++  ;
	m_var.guiData.mems[i].iIDC_STATIC_subtitle  =  IDC_STATIC_subtitle11;
	m_var.guiData.mems[i].iIDC_EDIT_subtitle  =  IDC_EDIT_subtitle11;



	m_var.guiData.iIDOK  =  IDOK;
	m_var.guiData.iIDCANCEL  =  IDCANCEL;
	m_var.guiData.iIDC_BUTTON_emptyTxt  =  IDC_BUTTON_emptyTxt;
	//
	m_var.m_pParent = pParent;
	m_var.m_nID = CDlgVideoTagCfg::IDD;


}

CDlgVideoTagCfg::~CDlgVideoTagCfg()
{
}


BOOL  CDlgVideoTagCfg::bSetInfo(  int  iSharedObjType,  int  iCapType,  int  iCapSubType,  int  iUsage  )
{
	m_var.iSharedObjType  =  iSharedObjType;
	m_var.iCapType  =  iCapType;
	m_var.iCapSubType  =  iCapSubType;
	m_var.iUsage  =  iUsage;
	return  TRUE;
}

BOOL CDlgVideoTagCfg::Create(const RECT& rect)
{

	// TODO: Add your specialized code here and/or call the base class
	BOOL						bRet		=	FALSE;
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli			*	pProc		=	NULL;

	/*
	if  (  !m_var.bInfoSet  )  {
		traceLogA(  "CDlgTalk::Create(  ): ÔÚ´´½¨¶Ô»°¿òÖ®Ç°Ó¦ÏÈÉèÖÃ³õÊ¼Êý¾Ý"  );
		return  FALSE;
	}
	*/

	if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_is  )  return  FALSE;
	

	//
	if  (  !CDialog::Create(  this->m_var.m_nID, m_var.m_pParent  )  )  goto  errLabel;

	//
	m_var.bCreated  =  TRUE;

	bRet  =  TRUE;
errLabel:
	return  bRet;
}


BOOL  CDlgVideoTagCfg::bQuitDlg(  )		
{		
	traceLogA(  "CDlgVideoTagCfg(  )::bQuitDlg enters"  );

	M_syncFlg_bQuitDlg_start(  &m_var.syncFlgs.bInSequence,  m_hWnd,  _T(  "CDlgVideoTagCfg::bQuitDlg failed, bLocked already."  )  );

#if  0
	{
		CQySyncFlg	syncFlg;
		if  (  syncFlg.sync(  &m_var.syncFlgs.bInSequence  )  )  goto  errLabel;
	}
#endif


	//  2009/05/01
	DestroyWindow();				  
		
errLabel:

	M_syncFlg_bQuitDlg_end

	traceLogA(  "CDlgVideoTagCfg(  )::bQuitDlg leaves"  );

	return  TRUE;
}

BOOL  CDlgVideoTagCfg::bShowInfo(  )
{
	QY_MC			*	pQyMc	=	QY_GET_GBUF(  );

	//
	setIdcChked(  m_hWnd,  m_var.guiData.iIDC_CHECK_showVideoHint,  m_var.tagCfgs.flgs.ucbShowVideoHint  );
	setIdcChked(  m_hWnd,  m_var.guiData.iIDC_CHECK_effectiveImmediately,  m_var.tagCfgs.flgs.ucbEffectiveImmediately  );
	
	//	
	//  BYTE  r,  g,  b;
	//
	TCHAR	tBuf[128];
	int  i;
	for  (  i  =  0;  i  <  mycountof(  m_var.tagCfgs.mems  );  i  ++  )  {
		 bShowInfo_mem(  i  );
	}

	if  (  !m_var.bFileGot  )  SetDlgItemText(  m_var.guiData.iIDC_BUTTON_file,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_importFile  )  );
	else  ::SetDlgItemText(  m_hWnd,  m_var.guiData.iIDC_BUTTON_file,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_hideList  )  );
	
	//
	bShowInfo_btn_subtitlesSettings(  );

	//
	return  TRUE;
}

BOOL  CDlgVideoTagCfg::bShowInfo_mem(  int  index  )
{
	if  (  index  <  0  ||  index  >=  mycountof(  m_var.tagCfgs.mems  )  )  return  FALSE;


		 SUBTITLE_cfg	*	pTagCfg	=	&m_var.tagCfgs.mems[index].subtitle;
#if  0
		TCHAR	tBuf[128];
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  pTagCfg->font.lf.lfFaceName  );
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %d"  ),  tBuf,  pTagCfg->font.iFontSize  );
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s RGB(%d,%d,%d)."  ),  tBuf,  (  int  )pTagCfg->color.fontColor_r,  (  int  )pTagCfg->color.fontColor_g,  (  int  )pTagCfg->color.fontColor_b  );
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s x,y(%d,%d)"  ),  tBuf,  pTagCfg->pos.xStart,  pTagCfg->pos.yStart  );
		 if  (  pTagCfg->pos.ucbBottomUp  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s bottom."  ),  tBuf  );
		 if  (  pTagCfg->tag.ucbDisplayTime  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s time."  ),  tBuf  );
		 if  (  pTagCfg->color.ucb3dShadow  )  {
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s shadow"  ),  tBuf  );
		 }
		 SetDlgItemText(  m_var.guiData.mems[index].iIDC_STATIC_select,  tBuf  );
#endif 
		 //
		 //  setIdcChked(  m_hWnd,  m_var.guiData.iIDC_CHECK_displayTime,  pTagCfg->tag.ucbDisplayTime  );
		 SetDlgItemText(  m_var.guiData.mems[index].iIDC_EDIT_subtitle,  pTagCfg->tag.txt  );

		 return  TRUE;
}



BOOL  CDlgVideoTagCfg::bShowInfo_btn_subtitlesSettings(  )
{
	TCHAR	tBuf[256]  =  _T(  ""  );

	if  (  m_var.iCurLineIndex  >=  0  &&  m_var.iCurLineIndex  <  mycountof(  m_var.tagCfgs.mems  )  )  {
		GetDlgItemText(  m_var.guiData.mems[m_var.iCurLineIndex].iIDC_STATIC_subtitle,  tBuf,  mycountof(  tBuf  )  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ..."  ),  tBuf  );
	}
	
	SetDlgItemText(  m_var.guiData.iIDC_BUTTON_subtitlesSettings,  tBuf  );

	return  TRUE;
}


void CDlgVideoTagCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgVideoTagCfg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgVideoTagCfg::OnBnClickedOk)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_emptyTxt, &CDlgVideoTagCfg::OnBnClickedButtonemptytxt)
	ON_BN_CLICKED(IDC_CHECK_effectiveImmediately, &CDlgVideoTagCfg::OnBnClickedCheckeffectiveimmediately)
	ON_BN_CLICKED(IDC_CHECK_showVideoHint, &CDlgVideoTagCfg::OnBnClickedCheckshowvideohint)
	ON_BN_CLICKED(IDC_BUTTON_useDefault, &CDlgVideoTagCfg::OnBnClickedButtonusedefault)
	ON_BN_CLICKED(IDC_BUTTON_file, &CDlgVideoTagCfg::OnBnClickedButtonfile)
	ON_LBN_SELCHANGE(IDC_LIST_subtitles, &CDlgVideoTagCfg::OnLbnSelchangeListsubtitles)
	ON_WM_SIZE()
	//  ON_BN_CLICKED(IDC_BUTTON_more, &CDlgVideoTagCfg::OnBnClickedButtonmore)
#if  0
	ON_BN_CLICKED(IDC_BUTTON_select0, &CDlgVideoTagCfg::OnBnClickedButtonselect0)
	ON_BN_CLICKED(IDC_BUTTON_select1, &CDlgVideoTagCfg::OnBnClickedButtonselect1)
	ON_BN_CLICKED(IDC_BUTTON_select2, &CDlgVideoTagCfg::OnBnClickedButtonselect2)
	ON_BN_CLICKED(IDC_BUTTON_select3, &CDlgVideoTagCfg::OnBnClickedButtonselect3)
	ON_BN_CLICKED(IDC_BUTTON_select4, &CDlgVideoTagCfg::OnBnClickedButtonselect4)
	ON_BN_CLICKED(IDC_BUTTON_select5, &CDlgVideoTagCfg::OnBnClickedButtonselect5)
	ON_BN_CLICKED(IDC_BUTTON_select6, &CDlgVideoTagCfg::OnBnClickedButtonselect6)
	ON_BN_CLICKED(IDC_BUTTON_select7, &CDlgVideoTagCfg::OnBnClickedButtonselect7)
	ON_BN_CLICKED(IDC_BUTTON_select8, &CDlgVideoTagCfg::OnBnClickedButtonselect8)
	ON_BN_CLICKED(IDC_BUTTON_select9, &CDlgVideoTagCfg::OnBnClickedButtonselect9)
	ON_BN_CLICKED(IDC_BUTTON_select10, &CDlgVideoTagCfg::OnBnClickedButtonselect10)
	ON_BN_CLICKED(IDC_BUTTON_select11, &CDlgVideoTagCfg::OnBnClickedButtonselect11)
#endif
	ON_EN_CHANGE(IDC_EDIT_subtitle0, &CDlgVideoTagCfg::OnEnChangeEditsubtitle0)
	ON_EN_CHANGE(IDC_EDIT_subtitle1, &CDlgVideoTagCfg::OnEnChangeEditsubtitle1)
	ON_EN_CHANGE(IDC_EDIT_subtitle2, &CDlgVideoTagCfg::OnEnChangeEditsubtitle2)
	ON_EN_CHANGE(IDC_EDIT_subtitle3, &CDlgVideoTagCfg::OnEnChangeEditsubtitle3)
	ON_EN_CHANGE(IDC_EDIT_subtitle4, &CDlgVideoTagCfg::OnEnChangeEditsubtitle4)
	ON_EN_CHANGE(IDC_EDIT_subtitle5, &CDlgVideoTagCfg::OnEnChangeEditsubtitle5)
	ON_EN_CHANGE(IDC_EDIT_subtitle6, &CDlgVideoTagCfg::OnEnChangeEditsubtitle6)
	ON_EN_CHANGE(IDC_EDIT_subtitle7, &CDlgVideoTagCfg::OnEnChangeEditsubtitle7)
	ON_EN_CHANGE(IDC_EDIT_subtitle8, &CDlgVideoTagCfg::OnEnChangeEditsubtitle8)
	ON_EN_CHANGE(IDC_EDIT_subtitle9, &CDlgVideoTagCfg::OnEnChangeEditsubtitle9)
	ON_EN_CHANGE(IDC_EDIT_subtitle10, &CDlgVideoTagCfg::OnEnChangeEditsubtitle10)
	ON_EN_CHANGE(IDC_EDIT_subtitle11, &CDlgVideoTagCfg::OnEnChangeEditsubtitle11)
	ON_EN_SETFOCUS(IDC_EDIT_subtitle0, &CDlgVideoTagCfg::OnEnSetfocusEditsubtitle0)
	ON_BN_CLICKED(IDC_BUTTON_subtitlesSettings, &CDlgVideoTagCfg::OnBnClickedButtonsubtitlessettings)
	ON_EN_SETFOCUS(IDC_EDIT_subtitle1, &CDlgVideoTagCfg::OnEnSetfocusEditsubtitle1)
	ON_EN_SETFOCUS(IDC_EDIT_subtitle2, &CDlgVideoTagCfg::OnEnSetfocusEditsubtitle2)
	ON_EN_SETFOCUS(IDC_EDIT_subtitle3, &CDlgVideoTagCfg::OnEnSetfocusEditsubtitle3)
	ON_EN_SETFOCUS(IDC_EDIT_subtitle4, &CDlgVideoTagCfg::OnEnSetfocusEditsubtitle4)
	ON_EN_SETFOCUS(IDC_EDIT_subtitle5, &CDlgVideoTagCfg::OnEnSetfocusEditsubtitle5)
	ON_EN_SETFOCUS(IDC_EDIT_subtitle6, &CDlgVideoTagCfg::OnEnSetfocusEditsubtitle6)
	ON_EN_SETFOCUS(IDC_EDIT_subtitle7, &CDlgVideoTagCfg::OnEnSetfocusEditsubtitle7)
	ON_EN_SETFOCUS(IDC_EDIT_subtitle8, &CDlgVideoTagCfg::OnEnSetfocusEditsubtitle8)
	ON_EN_SETFOCUS(IDC_EDIT_subtitle9, &CDlgVideoTagCfg::OnEnSetfocusEditsubtitle9)
	ON_EN_SETFOCUS(IDC_EDIT_subtitle10, &CDlgVideoTagCfg::OnEnSetfocusEditsubtitle10)
	ON_EN_SETFOCUS(IDC_EDIT_subtitle11, &CDlgVideoTagCfg::OnEnSetfocusEditsubtitle11)
END_MESSAGE_MAP()


// CDlgVideoTagCfg message handlers

BOOL CDlgVideoTagCfg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	int					iErr			=	-1;
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	RECT				rc;
	int  idc;


	cusDlgRes(  0,  &pQyMc->cusRes,  m_hWnd,  IDD  );

	DLG_guiData_subtitleCfg  *  p  =  &m_var.guiData;

	::GetClientRect(  m_hWnd,  &rc  );

	p->iw_org  =  rc.right  -  rc.left;  
	p->ih_org  =  rc.bottom  -  rc.top;

	if  (  !p->iw_org  ||  !p->ih_org  )  goto  errLabel;

	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  p->iIDC_CHECK_showVideoHint  ),  &p->rcIDC_CHECK_showVideoHint  );
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDC_CHECK_showVideoHint,  2  );

	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  p->iIDC_CHECK_effectiveImmediately  ),  &p->rcIDC_CHECK_effectiveImmediately  );
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDC_CHECK_effectiveImmediately,  2  );

	//
	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  p->iIDC_BUTTON_useDefault  ),  &p->rcIDC_BUTTON_useDefault  );	
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDC_BUTTON_useDefault,  2  );
	
	int  i;
	for  (  i  =  0;  i  <  mycountof(  m_var.guiData.mems  );  i  ++  )  {
		 //
#if  0
		 idc  =  p->mems[i].iIDC_STATIC_select;
		 ::GetWindowRect(  ::GetDlgItem(  m_hWnd,  idc  ),  &p->mems[i].rcIDC_STATIC_select  );	
		 ::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->mems[i].rcIDC_STATIC_select,  2  );
		 
		 idc  =  p->mems[i].iIDC_BUTTON_select;
		 ::GetWindowRect(  ::GetDlgItem(  m_hWnd,  idc  ),  &p->mems[i].rcIDC_BUTTON_select  );	
		 ::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->mems[i].rcIDC_BUTTON_select,  2  );
#endif 
		 idc  =  p->mems[i].iIDC_EDIT_subtitle;
		 ::GetWindowRect(  ::GetDlgItem(  m_hWnd,  idc  ),  &p->mems[i].rcIDC_EDIT_subtitle  );	
		 ::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->mems[i].rcIDC_EDIT_subtitle,  2  );
		 
		 idc  =  p->mems[i].iIDC_STATIC_subtitle;
		 ::GetWindowRect(  ::GetDlgItem(  m_hWnd,  idc  ),  &p->mems[i].rcIDC_STATIC_subtitle  );	
		 ::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->mems[i].rcIDC_STATIC_subtitle,  2  );
	}

	idc  =  p->iIDC_BUTTON_file;
	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  idc  ),  &p->rcIDC_BUTTON_file  );	
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDC_BUTTON_file,  2  );

	idc  =  p->iIDC_BUTTON_subtitlesSettings;
	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  idc  ),  &p->rcIDC_BUTTON_subtitlesSettings  );
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDC_BUTTON_subtitlesSettings,  2  );

	idc  =  p->iIDOK;
	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  idc  ),  &p->rcIDOK  );	
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDOK,  2  );

	idc  =  p->iIDC_BUTTON_emptyTxt;
	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  idc  ),  &p->rcIDC_BUTTON_emptyTxt  );	
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDC_BUTTON_emptyTxt,  2  );

	idc  =  p->iIDCANCEL;
	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  idc  ),  &p->rcIDCANCEL  );	
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDCANCEL,  2  );

	idc  =  p->iIDC_LIST_subtitles;
	::GetWindowRect(  ::GetDlgItem(  m_hWnd,  idc  ),  &p->rcIDC_LIST_subtitles  );	
	::MapWindowPoints(  NULL,  m_hWnd,  (  LPPOINT  )&p->rcIDC_LIST_subtitles,  2  );

	p->bInited  =  TRUE;

	//
	if  (  IsWindow(  m_var.hDlgTalk_mgr  )  )  {
		 makeWndNoBorder(  m_hWnd,  FALSE,  NULL,  NULL  );
	}

	//
	if  (  !m_var.hDlgTalk_mgr  )  {
		SUBTITLES_cfg  *  pCurCfg  =  (  SUBTITLES_cfg  *  )getCurSubtitlesCfg(  m_var.iSharedObjType,  m_var.iCapType,  m_var.iCapSubType  );
		if  (  !pCurCfg  )  goto  errLabel;
		//
		memcpy(  &m_var.old_tagCfgs,  pCurCfg,  sizeof(  m_var.old_tagCfgs  )  );
		}
	else  {
		  //  CDlg
		  if  (  dlgTalk_getCurSubtitlesCfg(  m_var.hDlgTalk_mgr,  &m_var.old_tagCfgs  )  )  goto  errLabel;
	}
	
	//
	memcpy(  &m_var.tagCfgs,  &m_var.old_tagCfgs,  sizeof(  m_var.tagCfgs  )  );

	//
	TCHAR  tBuf[128];
	if  (  m_var.iCapType  ==  CONST_capType_av  )  {

		if  (  m_var.iCapSubType  ==  CONST_subCapType_webcam  )  SetWindowText(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_webcamSharingSubtitles  )   );  /*_T(  "WebcamSharing subtitles settings"  )*/

		else  	SetWindowText(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_conferencingSubtitles  )   );  //  (  _T(  "Conferencing subtitles settings"  )  );

	}
	else  if  (  m_var.iCapType  ==  CONST_capType_screen  )  {

		SetWindowText(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_screensharingSubtitles  )   );			//  (  _T(  "Screensharing subtitles settings"  )  );
		
	}

	sizeAllControls(  1.,  1.  );
	//
	for  (  i  =  0;  i  <  mycountof(  m_var.guiData.mems  );  i  ++  )  {
		 if  (  bLine_title_subtitles(  i  )  )  {
			 SetDlgItemText(  m_var.guiData.mems[i].iIDC_STATIC_subtitle,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_title  )  );
		 }
	}
	//
	bShowInfo(  );

	iErr  =  0;

errLabel:
	if  (  iErr  )  {
		PostMessage(  WM_CLOSE,  0,  0  );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}




void CDlgVideoTagCfg::OnBnClickedOk()
{
	QY_MC	*  pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;

	unsigned  char  ucbDaemonDemo  =  FALSE;
	//
	QM_SHM_CMDS	*	pShmCmds  =  QY_GET_shmCmds(  pProcInfo  );				
	if  (  pShmCmds  )  {
		if  (  pShmCmds->ucbDaemonDemo  )  {
			ucbDaemonDemo  =  TRUE;
		}
	}
	//
#ifdef  __DEBUG__
		#if  1
			traceLog(  _T(  "TEST: ucbDaemonDemo is set to FALSE"  )  );
			ucbDaemonDemo  =  FALSE;
		#endif
#endif
	//
	if  (  ucbDaemonDemo  &&  !b_tttbbbMac(  pQyMc  )  )  {
		myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_subtitleLimited  ),  _T(  "www.qycx.com"  ),  MB_OK  );
		return;
	}	
	

	// TODO: Add your control notification handler code here
	//  if  (  memcmp(  &m_var.tagCfgs,  &m_var.old_tagCfgs,  sizeof(  m_var.tagCfgs  )  )  )  
	{
		if  (  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToSave  ),  _T(  "Qycx.com"  ),  MB_YESNO  )  !=  IDYES  )  return;
		saveSubtitlesCfg(  m_var.iCapType,  m_var.iCapSubType,  m_var.iUsage,  &m_var.tagCfgs  );
	}


	//
	//  CDialogEx::OnOK();
	bQuitDlg(  );
}

void CDlgVideoTagCfg::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::PostNcDestroy();

	//
	//  2013/04/05
	if  (  m_var.hDlgTalk_mgr  )  {
		//::PostMessage(  m_var.hDlgTalk_mgr,  WM_SIZE,  0,  0  );
		askToRefreshSize_mgr(  m_var.hDlgTalk_mgr  );

		//  2016/04/07
		dyn_d3dWall_askToRefreshMenu(  );
	}


	//
	delete  this;
}

void CDlgVideoTagCfg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	//  CDialogEx::OnClose();
	bQuitDlg(  );
}


void CDlgVideoTagCfg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	//  CDialogEx::OnCancel();
	bQuitDlg(  );
}

void CDlgVideoTagCfg::OnBnClickedButtonemptytxt()
{
	// TODO: Add your control notification handler code here
	int  i;
	for  (  i  =  0;  i  <  mycountof(  m_var.tagCfgs.mems  );   i  ++  )  {
		 if  (  bLine_title_subtitles(  i  )  )  continue;
		 //
		 m_var.tagCfgs.mems[i].subtitle.tag.txt[0]  =  0;
		 m_var.tagCfgs.mems[i].tickCnts.dwModifiedTickCnt_tag  =  GetTickCount(  );
		 SetDlgItemText(  m_var.guiData.mems[i].iIDC_EDIT_subtitle,  m_var.tagCfgs.mems[i].subtitle.tag.txt  );
	}
}





void CDlgVideoTagCfg::OnBnClickedCheckeffectiveimmediately()
{
	// TODO: Add your control notification handler code here
	m_var.tagCfgs.flgs.ucbEffectiveImmediately  =  isIdcChked(  m_hWnd,  m_var.guiData.iIDC_CHECK_effectiveImmediately  );
	if  (  m_var.tagCfgs.flgs.ucbEffectiveImmediately  )  {
		//  subtitlesCfg_modify(  &m_var.tagCfgs,  GetTickCount(  ),  FALSE,  m_var.pCurCfg  );
		mysubtitlesCfg_modify(  &m_var.tagCfgs,  GetTickCount(  ),  FALSE  );
	}
}

void CDlgVideoTagCfg::OnBnClickedCheckshowvideohint()
{
	// TODO: Add your control notification handler code here
	m_var.tagCfgs.flgs.ucbShowVideoHint  =  isIdcChked(  m_hWnd,  m_var.guiData.iIDC_CHECK_showVideoHint  );
	if  (  m_var.tagCfgs.flgs.ucbEffectiveImmediately  )  {
		//  subtitlesCfg_modify(  &m_var.tagCfgs,  GetTickCount(  ),  FALSE,  m_var.pCurCfg  );
		mysubtitlesCfg_modify(  &m_var.tagCfgs,  GetTickCount(  ),  FALSE  );
	}
}


void CDlgVideoTagCfg::OnBnClickedButtonusedefault()
{
	// TODO: Add your control notification handler code here
	QY_MC		*	pQyMc	=  QY_GET_GBUF(  );

	if  (  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askIfUseDefault  ),  _T(  "qycx.com"  ),  MB_YESNO  )  !=  IDYES  )  {
		return;		
	}

	deleteSubtitlesCfg(  m_var.iCapType,  m_var.iCapSubType,  m_var.iUsage  );	
	//
	getSubtitlesCfg(  m_var.iCapType,  m_var.iCapSubType,  0,  &m_var.tagCfgs  );		
	//		
	bShowInfo(  );
	
	//
	if  (  m_var.tagCfgs.flgs.ucbEffectiveImmediately  )  {
		//  subtitlesCfg_modify(  &m_var.tagCfgs,  GetTickCount(  ),  FALSE,  m_var.pCurCfg  );
		mysubtitlesCfg_modify(  &m_var.tagCfgs,  GetTickCount(  ),  FALSE  );
	}
}



#define CONST_FILE_FILTER_subtitles \
    TEXT("Subtitles Files (*.txt; )\0*.txt;\0")\
    TEXT("\0\0")


#define		MAX_subtitles_lines		2000		//  2013/03/25
//
void CDlgVideoTagCfg::OnBnClickedButtonfile()
{
	// TODO: Add your control notification handler code here

	QY_MC		*	pQyMc		=  QY_GET_GBUF(  );

	CQySyncFlg	syncFlg;
	if  (  syncFlg.sync(  &m_var.syncFlgs.bInSequence  )  )  return;


	HWND		hCtrl	=	::GetDlgItem(  m_hWnd,  m_var.guiData.iIDC_LIST_subtitles  );
	FILE	*	fp  =  NULL;
	
	DLG_guiData_subtitleCfg		*	p	=  &m_var.guiData;

	if  (  !p->iw_org  ||  !p->ih_org  )  return;

	RECT	rc;
	GetClientRect(  &rc  );
	int  w,  h;
	w  =  rc.right  -  rc.left;
	h  =  rc.bottom  -  rc.top;

	float  fx,  fy;
	fx  =  1.  *  w  /  p->iw_org;
	fy  =  1.  *  h  /  p->ih_org;

	if  (  m_var.bFileGot  )  {
		//  hide list
		m_var.bFileGot  =  FALSE;

		//
		::SendMessage(  hCtrl,  LB_RESETCONTENT,  0,  0  );
		//
		::SetDlgItemText(  m_hWnd,  m_var.guiData.iIDC_BUTTON_file,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_importFile  )  );
		//

		sizeAllControls(  fx,  fy  );
		bShowInfo(  );
		return;
	}

	
	LPCTSTR							lpszDefExt  =	TEXT("*\0");	
	LPCTSTR							lpszFilter	=	CONST_FILE_FILTER_subtitles;
	LPCTSTR							title		=	getResStr(  0,  &pQyMc->cusRes,  CONST_resId_utf8  );   //  _T("Open subtitles File( utf8 format )...\0");
	CQyString							pathCStr;
	DWORD								dwFlags     =	OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST;
	
	//
	if  (  qyBrowseForFile(  m_hWnd,  TRUE,  lpszDefExt,  dwFlags,  CONST_FILE_FILTER_subtitles,  title,  NULL,  pQyMc,  pathCStr  )  )  goto  errLabel;

	traceLog(  _T(  "path %s"  ),  pathCStr  );

	//
	//  show list

	//
	fp  =  _tfopen(  pathCStr,  _T(  "rt"  )  );
	if  (  !fp  )  goto  errLabel;


	char		buf[1024];
	TCHAR		tBuf[1024];
	int			i, j;
	
	::SendMessage(  hCtrl,  LB_RESETCONTENT,  0,  0  );

	for  (  i  =  0;  i  <  MAX_subtitles_lines;  i  ++  )  {
		if  (  !fgets(  buf,  mycountof(  buf  ),  fp  )  )  break;
		buf[mycountof(  buf  )  -  1]  =  0;
		myUtf82TChar(  buf,  tBuf,  mycountof(  tBuf  )  );
		tBuf[mycountof(  tBuf  )  -  1]  =  0;

		for  (  j  =  0;  tBuf[j];  j  ++  )  {
			 //  if  (  IsAscii
		}

		::SendMessage(  hCtrl,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )tBuf  );    
	}

	//
	m_var.bFileGot  =  TRUE;

	sizeAllControls(  fx,  fy  );
	

	//
	::SetDlgItemText(  m_hWnd,  m_var.guiData.iIDC_BUTTON_file,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_hideList  )  );

errLabel:

	if  (  fp  )  fclose(  fp  );
		
	return;
}



//
#define		CONST_cmdStr_title			_T(  "title"  )
#define		CONST_cmdStr_line			_T(  "line"  )
#define		CONST_cmdStr_clear			_T(  "clear"  )



void CDlgVideoTagCfg::OnLbnSelchangeListsubtitles()
{
	// TODO: Add your control notification handler code here
	int				iErr	=	-1;
	CQyMalloc		mallocObj;
	TCHAR		*	pT		=  NULL;

	HWND	hCtrl  =  ::GetDlgItem(  m_hWnd,  m_var.guiData.iIDC_LIST_subtitles  );

	int  iItemSelected  =  ::SendMessage(  hCtrl,  LB_GETCURSEL,  0,  0  );
	if  (  iItemSelected  ==  LB_ERR  )  goto  errLabel;

	int  len  =  ::SendMessage(  hCtrl, LB_GETTEXTLEN,  iItemSelected,  0  );
	if  (  len  <  0  )  goto  errLabel;

	pT  =  (  TCHAR  *  )mallocObj.mallocf(  sizeof(  TCHAR  )  *  (  len  +  1  )  );
	if  (  !pT  )  goto  errLabel;
	::SendMessage(  hCtrl,  LB_GETTEXT,  iItemSelected,  (  LPARAM  )pT  );
	pT[len]  =  0;

	//		
	int  lineIndex  =  getLineIndex_default_subtitles(  );	//  DEFAULT_lineIndex;


	//  2013/03/25
	int  index_r  =  -1;
	int  index_l  =  -1;
	int  i;
	for  (  i  =  len  -  1;  i  >=  0;  i  --  )  {
		 if  (  _istspace(  pT[i]  )  )  continue;
		 if  (  pT[i]  !=  '>'  )  break;
		 //
		 index_r  =  i;
		 break;
	}
	if  (  index_r  >=  0  )  {
		for  (  i  =  index_r  -  1;  i  >=  0;  i  --  )  {
			 if  (  pT[i]  ==  '<'  )  {
				 index_l  =  i;
				 break;
			 }
		}
	}
	if  (  index_l  >=  0  )  {
		pT[index_l]  =  0;
		//
		TCHAR  *  pT_cmd  =  pT  +  index_l  +  1;
		tTrim(  pT_cmd  );
		if  (  !_tcsnicmp(  pT_cmd,  CONST_cmdStr_line,  lstrlen(  CONST_cmdStr_line  )  )  )  {
			lineIndex  =  _ttol(  pT_cmd  +  lstrlen(  CONST_cmdStr_line  )  );
			//  2013/04/06. 不能写到title行
			if  (  bLine_title_subtitles(  lineIndex  )  )  {
				lineIndex  =  getLineIndex_default_subtitles(  );
			}
			}
		else  if  (  !_tcsnicmp(  pT_cmd,  CONST_cmdStr_title,  lstrlen(  CONST_cmdStr_title  )  )  )  {
				  for  (  i  =  0;  i  <  mycountof(  m_var.guiData.mems  );  i  ++  )  {
					   if  (  bLine_title_subtitles(  i  )  )  {
						   lineIndex  =  i;
						   break;
					   }
				  }
				  }
		else  if  (  !_tcsnicmp(  pT_cmd,  CONST_cmdStr_clear,  lstrlen(  CONST_cmdStr_clear  )  )  )  {
				  this->OnBnClickedButtonemptytxt(  );
				  iErr  =  0;  goto  errLabel;
		}

	}

	//
	if  (  lineIndex  <  0  ||  lineIndex  >=  mycountof(  m_var.guiData.mems  )  )  lineIndex  =  getLineIndex_default_subtitles(  );	//  DEFAULT_lineIndex;
	//
	::SetDlgItemText(  m_hWnd,  m_var.guiData.mems[lineIndex].iIDC_EDIT_subtitle,  pT  );

	iErr  =  0;

errLabel:
	return;

}

#define		CONST_edge_l							10
#define		CONST_edge_t							10
#define		CONST_iX_spacing						5
#define		CONST_iY_spacing						1

int  sizeAllControls_subtitlesCfg(  HWND  hDlg,   DLG_guiData_subtitleCfg  *  pGuiData,  BOOL  bShowList  )
{
	int				iErr		=  -1;

	HDWP			hDwp;
	int				idc;
	int				x, y, iW, iH;
	RECT			rc;

	int				iEdge_l							=	CONST_edge_l;
	int				iEdge_t							=	CONST_edge_t;
	int				iEdge_r							=	CONST_edge_l;
	int				iEdge_b							=	CONST_edge_t;
	//
	int				iX_spacing						=	CONST_iX_spacing;			//  
	int				iY_spacing						=	CONST_iY_spacing;			//  
	//
	int				iW_static						=	0;
	int				iH_static						=	0;

	int				iW_edit							=	0;
	int				iH_edit							=	0;

	int				iW_list							=	0;
	int				iH_list							=	0;

	GetClientRect(  hDlg,  &rc  );

	int  iw_cur,  ih_cur;
	iw_cur  =  rc.right  -  rc.left;
	ih_cur  =  rc.bottom  -  rc.top;

	float  fx  =  1.0  *  iw_cur  /  pGuiData->iw_org;
	float  fy  =  1.0  *  ih_cur  /  pGuiData->ih_org;

	iW  =  iw_cur  -  iEdge_l  -  iEdge_r;
	iH  =  ih_cur  -  iEdge_t  -  iEdge_b;

	if  (  bShowList  )  {
		iW_list  =  iW  /  3;
		//
		iW  -=  iW_list;
	}
	else  {
		iW_list  =  0;
	}

	iW_static  =  min  (  iW  *  0.1,  30  );
	iH_static  =  iH  /  16;

	iW_edit  =  iW  -  iW_static  -  iX_spacing  -  iEdge_l;
	iH_edit  =  iH  /  16;

	//
#if  0
	iH_edit  =   iH  /   15   -  iY_spacing;
	if  (  !iH_edit  )  goto  errLabel;
	iH_button  =  iH_edit;
	iH_cb  =  iH_edit;
#endif
	if  (  bShowList  )  {
		iH_list  =  iH;
	}
	else  iH_list  =  0;

	 hDwp  =  M_BeginDeferWindowPos(  32  );
	if  (  hDwp  )  {
		int		iY_static;

		//  1st (2 cb)
		idc  =  pGuiData->iIDC_CHECK_showVideoHint;
		rc  =  pGuiData->rcIDC_CHECK_showVideoHint;
		x  =  rc.left;  y  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		x  *=  fx;  y  *=  fy;  iW  *=  fx;  iH  *=  fy;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );

		idc  =  pGuiData->iIDC_CHECK_effectiveImmediately;
		rc  =  pGuiData->rcIDC_CHECK_effectiveImmediately;
		x  =  rc.left;  y  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		x  *=  fx;  y  *=  fy;  iW  *=  fx;  iH  *=  fy;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );
		iY_static  =  y  +  iH  +  iY_spacing;

		//  2nd,  (3 bu)
		idc  =  pGuiData->iIDC_BUTTON_useDefault;
		rc  =  pGuiData->rcIDC_BUTTON_useDefault;
		x  =  rc.left;  y  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		x  *=  fx;  y  *=  fy;  iW  *=  fx;  iH  *=  fy;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );

		idc  =  pGuiData->iIDC_BUTTON_file;
		rc  =  pGuiData->rcIDC_BUTTON_file;
		x  =  rc.left;  y  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		x  *=  fx;  y  *=  fy;  iW  *=  fx;  iH  *=  fy;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );

		idc  =  pGuiData->iIDC_BUTTON_subtitlesSettings;
		rc  =  pGuiData->rcIDC_BUTTON_subtitlesSettings;
		x  =  rc.left;  y  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		x  *=  fx;  y  *=  fy;  iW  *=  fx;  iH  *=  fy;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );

		//  3rd,  (3 bu)
		idc  =  pGuiData->iIDOK;
		rc  =  pGuiData->rcIDOK;
		x  =  rc.left;  y  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		x  *=  fx;  y  *=  fy;  iW  *=  fx;  iH  *=  fy;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );

		idc  =  pGuiData->iIDC_BUTTON_emptyTxt;
		rc  =  pGuiData->rcIDC_BUTTON_emptyTxt;
		x  =  rc.left;  y  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		x  *=  fx;  y  *=  fy;  iW  *=  fx;  iH  *=  fy;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );

		idc  =  pGuiData->iIDCANCEL;
		rc  =  pGuiData->rcIDCANCEL;
		x  =  rc.left;  y  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		x  *=  fx;  y  *=  fy;  iW  *=  fx;  iH  *=  fy;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );

		// 4th,  (12 static)
		int  index  =  0;
		x  =  iEdge_l;
		y  =  iEdge_t  +  iY_static;
		idc  =  pGuiData->mems[index].iIDC_STATIC_subtitle;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW_static,  iH_static,  SWP_NOZORDER  );
		y  +=  iH_static  +  iY_spacing;

		index  ++;
		idc  =  pGuiData->mems[index].iIDC_STATIC_subtitle;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW_static,  iH_static,  SWP_NOZORDER  );
		y  +=  iH_static  +  iY_spacing;

		index  ++;
		idc  =  pGuiData->mems[index].iIDC_STATIC_subtitle;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW_static,  iH_static,  SWP_NOZORDER  );
		y  +=  iH_static  +  iY_spacing;

		index  ++;
		idc  =  pGuiData->mems[index].iIDC_STATIC_subtitle;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW_static,  iH_static,  SWP_NOZORDER  );
		y  +=  iH_static  +  iY_spacing;

		index  ++;
		idc  =  pGuiData->mems[index].iIDC_STATIC_subtitle;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW_static,  iH_static,  SWP_NOZORDER  );
		y  +=  iH_static  +  iY_spacing;

		index  ++;
		idc  =  pGuiData->mems[index].iIDC_STATIC_subtitle;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW_static,  iH_static,  SWP_NOZORDER  );
		y  +=  iH_static  +  iY_spacing;

		index  ++;
		idc  =  pGuiData->mems[index].iIDC_STATIC_subtitle;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW_static,  iH_static,  SWP_NOZORDER  );
		y  +=  iH_static  +  iY_spacing;

		index  ++;
		idc  =  pGuiData->mems[index].iIDC_STATIC_subtitle;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW_static,  iH_static,  SWP_NOZORDER  );
		y  +=  iH_static  +  iY_spacing;

		index  ++;
		idc  =  pGuiData->mems[index].iIDC_STATIC_subtitle;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW_static,  iH_static,  SWP_NOZORDER  );
		y  +=  iH_static  +  iY_spacing;

		index  ++;
		idc  =  pGuiData->mems[index].iIDC_STATIC_subtitle;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW_static,  iH_static,  SWP_NOZORDER  );
		y  +=  iH_static  +  iY_spacing;

		index  ++;
		idc  =  pGuiData->mems[index].iIDC_STATIC_subtitle;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW_static,  iH_static,  SWP_NOZORDER  );
		y  +=  iH_static  +  iY_spacing;

		index  ++;
		idc  =  pGuiData->mems[index].iIDC_STATIC_subtitle;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW_static,  iH_static,  SWP_NOZORDER  );
		y  +=  iH_static  +  iY_spacing;
		x  +=  iW_static  +  iX_spacing;

		//  5th (12)
		y  =  iEdge_t  +  iY_static;
		index  =  0;
		idc  =  pGuiData->mems[index].iIDC_EDIT_subtitle;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW_edit,  iH_edit,  SWP_NOZORDER  );
		y  +=  iH_edit  +  iY_spacing;

		index  ++;
		idc  =  pGuiData->mems[index].iIDC_EDIT_subtitle;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW_edit,  iH_edit,  SWP_NOZORDER  );
		y  +=  iH_edit  +  iY_spacing;

		index  ++;
		idc  =  pGuiData->mems[index].iIDC_EDIT_subtitle;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW_edit,  iH_edit,  SWP_NOZORDER  );
		y  +=  iH_edit  +  iY_spacing;

		index  ++;
		idc  =  pGuiData->mems[index].iIDC_EDIT_subtitle;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW_edit,  iH_edit,  SWP_NOZORDER  );
		y  +=  iH_edit  +  iY_spacing;

		index  ++;
		idc  =  pGuiData->mems[index].iIDC_EDIT_subtitle;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW_edit,  iH_edit,  SWP_NOZORDER  );
		y  +=  iH_edit  +  iY_spacing;

		index  ++;
		idc  =  pGuiData->mems[index].iIDC_EDIT_subtitle;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW_edit,  iH_edit,  SWP_NOZORDER  );
		y  +=  iH_edit  +  iY_spacing;

		index  ++;
		idc  =  pGuiData->mems[index].iIDC_EDIT_subtitle;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW_edit,  iH_edit,  SWP_NOZORDER  );
		y  +=  iH_edit  +  iY_spacing;

		index  ++;
		idc  =  pGuiData->mems[index].iIDC_EDIT_subtitle;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW_edit,  iH_edit,  SWP_NOZORDER  );
		y  +=  iH_edit  +  iY_spacing;

		index  ++;
		idc  =  pGuiData->mems[index].iIDC_EDIT_subtitle;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW_edit,  iH_edit,  SWP_NOZORDER  );
		y  +=  iH_edit  +  iY_spacing;

		index  ++;
		idc  =  pGuiData->mems[index].iIDC_EDIT_subtitle;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW_edit,  iH_edit,  SWP_NOZORDER  );
		y  +=  iH_edit  +  iY_spacing;

		index  ++;
		idc  =  pGuiData->mems[index].iIDC_EDIT_subtitle;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW_edit,  iH_edit,  SWP_NOZORDER  );
		y  +=  iH_edit  +  iY_spacing;

		index  ++;
		idc  =  pGuiData->mems[index].iIDC_EDIT_subtitle;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW_edit,  iH_edit,  SWP_NOZORDER  );
		y  +=  iH_edit  +  iY_spacing;

		//  6th  (1)
		x  =  iw_cur  -  iW_list;
		y  =  iEdge_t  +  iY_static;
		idc  =  pGuiData->iIDC_LIST_subtitles;
		M_DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW_list,  (  iH_edit +  iY_spacing  ) *  12,  SWP_NOZORDER  );

		EndDeferWindowPos(  hDwp  );
	}

	iErr  =  0;
errLabel:

	return  iErr;
}

void CDlgVideoTagCfg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	DLG_guiData_subtitleCfg		*	p	=  &m_var.guiData;

	if  (  !p->iw_org  ||  !p->ih_org  )  return;
	sizeAllControls_subtitlesCfg(  m_hWnd,  p,  m_var.bFileGot  );

	/*

	RECT	rc;
	GetClientRect(  &rc  );
	int  w,  h;
	w  =  rc.right  -  rc.left;
	h  =  rc.bottom  -  rc.top;


	//  
	int	idc;
	int  iX,  iY,  iW,  iH;
	float  fx,  fy;
	fx  =  1.  *  w  /  p->iw_org;
	fy  =  1.  *  h  /  p->ih_org;


	sizeAllControls(  fx,  fy  );

	//
	Invalidate(  TRUE  );
	*/
}

 int  CDlgVideoTagCfg::sizeAllControls(  float  fxSize,  float  fySize)
{
	int								iErr  =  -1;
	int  idc;
	RECT  rc;
	int  iX, iY, iW, iH;
	float  fx,  fy;
	int  iW_fileTxt,  iH_fileTxt;

	DLG_guiData_subtitleCfg		*	p	=  &m_var.guiData;

	if  (  !p->iw_org  ||  !p->ih_org  )  goto  errLabel;

	sizeAllControls_subtitlesCfg(  m_hWnd,  p,  m_var.bFileGot  );

#if  0

	iW_fileTxt  =  0.28  *  p->iw_org;
	iH_fileTxt  =  p->rcIDC_LIST_subtitles.bottom  -  p->rcIDC_LIST_subtitles.top;

	if  (  !m_var.bFileGot  )  {		

		fx  =  1.  *  p->iw_org  /  (  p->iw_org  -  iW_fileTxt  );
		fy  =  1;
	}
	else  	{
		fx  =  1;
		fy  =  1;

	}

	fx  *=  fxSize;
	fy  *=  fySize;

	idc  =  p->iIDC_CHECK_showVideoHint;
	rc  =  p->rcIDC_CHECK_showVideoHint;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );

	idc  =  p->iIDC_CHECK_effectiveImmediately;
	rc  =  p->rcIDC_CHECK_effectiveImmediately;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );

	idc  =  p->iIDC_BUTTON_more;
	rc  =  p->rcIDC_BUTTON_more;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );


	idc  =  p->iIDC_BUTTON_useDefault;
	rc  =  p->rcIDC_BUTTON_useDefault;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );
	
	int  i;
	for  (  i  =  0;  i  <  mycountof(  m_var.guiData.mems  );  i  ++  )  {	
#if  0
		idc  =  p->mems[i].iIDC_STATIC_select;
		rc  =  p->mems[i].rcIDC_STATIC_select;
		iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;
		::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );
		
		idc  =  p->mems[i].iIDC_BUTTON_select;
		rc  =  p->mems[i].rcIDC_BUTTON_select;
		iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;
		::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );
#endif
		idc  =  p->mems[i].iIDC_EDIT_subtitle;
		rc  =  p->mems[i].rcIDC_EDIT_subtitle;
		iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;
		::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );
		
		idc  =  p->mems[i].iIDC_STATIC_subtitle;
		rc  =  p->mems[i].rcIDC_STATIC_subtitle;
		iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;
		::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );
	}

	idc  =  p->iIDC_BUTTON_file;
	rc  =  p->rcIDC_BUTTON_file;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );

	idc  =  p->iIDOK;
	rc  =  p->rcIDOK;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );

	idc  =  p->iIDC_BUTTON_emptyTxt;
	rc  =  p->rcIDC_BUTTON_emptyTxt;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );

	idc  =  p->iIDCANCEL;
	rc  =  p->rcIDCANCEL;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );

	if  (  m_var.bFileGot  )  {
		idc  =  p->iIDC_LIST_subtitles;
		rc  =  p->rcIDC_LIST_subtitles;
		iX  =  rc.left;  iY  =  rc.top;  iW  =  iW_fileTxt;  iH  =  iH_fileTxt;
		iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;
		::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );

		::ShowWindow(  ::GetDlgItem(  m_hWnd,  p->iIDC_LIST_subtitles  ),  SW_SHOW  );
	}
	else  {
			::ShowWindow(  ::GetDlgItem(  m_hWnd,  p->iIDC_LIST_subtitles  ),  SW_HIDE  );
	}
#endif
	iErr   =   0;
errLabel:
	return  iErr;
}




#if  0
void CDlgVideoTagCfg::OnBnClickedButtonmore()
{
	// TODO: Add your control notification handler code here
}
#endif



int  CDlgVideoTagCfg::doOnBnClickedButtonselect(  int  index  )
{
	if  (  index  <  0  ||  index  >=  mycountof(  m_var.tagCfgs.mems  )  )  return  -1;

	QY_MC			*	pQyMc		=  QY_GET_GBUF(  );
	//
	CQySyncFlg	syncFlg;
	if  (  syncFlg.sync(  &m_var.syncFlgs.bInSequence  )  )  return  -1;


	//
#if  0  //  ndef  __DEBUG__
	QM_SHM_CMDS	*	pShmCmds  =  QY_GET_shmCmds(  );				
	if  (  pShmCmds  )  {
		if  (  pShmCmds->ucbDaemonDemo  )  {
			myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_subtitleLimited  ),  _T(  "www.qycx.com"  ),  MB_OK  );
			return  -1;
		}	
	}
#endif


	//
	SUBTITLE_cfg	*	pTagCfg	=	&m_var.tagCfgs.mems[index].subtitle;

#if  0
	CDlgSubtitleSelect	dlg(  this  );
	memcpy(  &dlg.m_var.subtitleCfg,  pTagCfg,  sizeof(  dlg.m_var.subtitleCfg  )  );	

	if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif

	if  (  showDlgSubtitleSelect(  this->m_hWnd,  pTagCfg  )  ==  IDOK  )	
	{
		//  memcpy(  pTagCfg,  &dlg.m_var.subtitleCfg,  sizeof(  pTagCfg[0]  )  );
		bShowInfo_mem(  index  );
		//
		if  (  m_var.tagCfgs.flgs.ucbEffectiveImmediately  )  {
			//  subtitlesCfg_modify(  &m_var.tagCfgs,  GetTickCount(  ),  FALSE,  m_var.pCurCfg  );
			mysubtitlesCfg_modify(  &m_var.tagCfgs,  GetTickCount(  ),  FALSE  );
		}
	}

	return  0;

}








int  CDlgVideoTagCfg::mysubtitlesCfg_modify(  SUBTITLES_cfg  *  pCfg,  DWORD  dwTickCnt,  BOOL  bForce  )
{
	int  iErr  =  -1;
	
	if  (  !m_var.hDlgTalk_mgr  )  {
		SUBTITLES_cfg  *  pCurCfg  =  (  SUBTITLES_cfg  *  )getCurSubtitlesCfg(  m_var.iSharedObjType,  m_var.iCapType,  m_var.iCapSubType  );
		if  (  !pCurCfg  )  goto  errLabel;

		subtitlesCfg_modify(  pCfg,  dwTickCnt,  bForce,  pCurCfg,  NULL  );
		}
	else  {
			 DLG_TALK_var			*	pDlgTalkVar  =  NULL;
	 CHelp_getDlgTalkVar		help_getDlgTalkVar;
	 CHelp_getDlgTalkVar		help_getDlgTalkVar_mgr;
	 
	 HWND				hMgr  =  NULL;
	 DLG_TALK_var  *  pMgrVar  =  NULL;
	
	 if  (  !pCfg  )  return  -1;

	 pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  m_var.hDlgTalk_mgr  );
	 if  (  !pDlgTalkVar  )  return  -1;

	 hMgr  =  m_var.hDlgTalk_mgr;
	 pMgrVar  =  pDlgTalkVar;
	 if  (  !isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  goto  errLabel;
	 
	 TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	 if  (  !pShadowMgr  )  goto  errLabel;

	 BOOL  bModified  =  FALSE;
	 subtitlesCfg_modify(  pCfg,  dwTickCnt,  bForce,  &pShadowMgr->subtitles.d3dConf,  &bModified  );

	 if  (  bModified  )  {
#if  0
		 //
		 int  i;	 	
		 for  (  i  =  0;  i  <  dyn_getMaxCnt_wallMems();  i  ++  )  {
			WALLMem_common  *  pWallMem  =  (  WALLMem_common  *  )dyn_getWallMemByIndex(  dyn_get_g_D3D_context(  ),  i  );
			if  (  !pWallMem  )continue;
			if  (  pWallMem->head.uiType  !=  CONST_wallMemType_talker  )  continue;
			//
			WALLMemData_talker  *  pTalker  =  (  WALLMemData_talker  *  )dyn_getD3dTalkerData(  pWallMem  );
			if  (  !pTalker  )  continue;		 
			if  (  pTalker->hTalkerMgr  ==  hMgr  )  {
				//
				pTalker->cfg.dwModifiedTickCnt_subtitlesCfg  =  pShadowMgr->subtitles.d3dConf.dwModifiedTickCnt_any_start;
				//			
				break;		 
			}	
		 }
#endif
		 dyn_refreshDlgTalkSubtitlesCfg_d3dWall(  hMgr  );
	 }


	}

	iErr  =  0;
	
errLabel:

	return  iErr;
}


//
int  CDlgVideoTagCfg::doOnEnChangeEditsubtitle(  int  index  )
{
	int  iErr  =  -1;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	if  (  index  <  0  ||  index  >=  mycountof(  m_var.guiData.mems  )  )  return  -1;
	if  (  index  <  0  ||  index  >=  mycountof(  m_var.tagCfgs.mems  )  )  return  -1;

	//
#if  0
	if  (  m_var.iCapType  ==  CONST_capType_mosaic  )  {
		if  (  index  ==  CONST_realMax_subtitles  -  1  )  {
			TCHAR  tBuf[256];
			::GetDlgItemText(  m_hWnd,  m_var.guiData.mems[index].iIDC_EDIT_subtitle,  tBuf,  mycountof(  tBuf  )  );
			//
			MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pProcInfo->getMisCntByName(  _T(  ""  )  );
			showMsg_d3d(  m_var.hDlgTalk_mgr,  &pMisCnt->idInfo,  pMisCnt->talkerDesc,  tBuf  );
				
			iErr  =  0;  goto  errLabel;
			
		}
	}
#endif

	//
	::GetDlgItemText(  m_hWnd,  m_var.guiData.mems[index].iIDC_EDIT_subtitle,  m_var.tagCfgs.mems[index].subtitle.tag.txt,  mycountof(  m_var.tagCfgs.mems[index].subtitle.tag.txt  )  );
	if  (  m_var.tagCfgs.mems[index].subtitle.tag.txt[0]  )  m_var.tagCfgs.mems[index].subtitle.tag.ucbUseDefault  =  FALSE;
	if  (  m_var.tagCfgs.flgs.ucbEffectiveImmediately  )  {
		//  subtitlesCfg_modify(  &m_var.tagCfgs,  GetTickCount(  ),  FALSE,  m_var.pCurCfg  );
		mysubtitlesCfg_modify(  &m_var.tagCfgs,  GetTickCount(  ),  FALSE  );
	}

	iErr  =  0;

errLabel:

#ifdef  __DEBUG__
	traceLog(  _T(  "changes, %d"  ),  index  );
#endif

	return  0;
}

void CDlgVideoTagCfg::OnEnChangeEditsubtitle0()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	int	i	=	0;
	doOnEnChangeEditsubtitle(  i  );

}

void CDlgVideoTagCfg::OnEnChangeEditsubtitle1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	int	i	=	1;
	doOnEnChangeEditsubtitle(  i  );

}


void CDlgVideoTagCfg::OnEnChangeEditsubtitle2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
		int	i	=	2;
	doOnEnChangeEditsubtitle(  i  );

}


void CDlgVideoTagCfg::OnEnChangeEditsubtitle3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
		int	i	=	3;
	doOnEnChangeEditsubtitle(  i  );

}


void CDlgVideoTagCfg::OnEnChangeEditsubtitle4()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
		int	i	=	4;
	doOnEnChangeEditsubtitle(  i  );

}


void CDlgVideoTagCfg::OnEnChangeEditsubtitle5()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
		int	i	=	5;
	doOnEnChangeEditsubtitle(  i  );

}


void CDlgVideoTagCfg::OnEnChangeEditsubtitle6()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
		int	i	=	6;
	doOnEnChangeEditsubtitle(  i  );

}


void CDlgVideoTagCfg::OnEnChangeEditsubtitle7()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
		int	i	=	7;
	doOnEnChangeEditsubtitle(  i  );

}


void CDlgVideoTagCfg::OnEnChangeEditsubtitle8()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
		int	i	=	8;
	doOnEnChangeEditsubtitle(  i  );

}


void CDlgVideoTagCfg::OnEnChangeEditsubtitle9()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
		int	i	=	9;
	doOnEnChangeEditsubtitle(  i  );

}


void CDlgVideoTagCfg::OnEnChangeEditsubtitle10()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
		int	i	=	10;
	doOnEnChangeEditsubtitle(  i  );

}


void CDlgVideoTagCfg::OnEnChangeEditsubtitle11()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
		int	i	=	11;
	doOnEnChangeEditsubtitle(  i  );

}


void CDlgVideoTagCfg::OnBnClickedButtonsubtitlessettings()
{
	// TODO: Add your control notification handler code here
	doOnBnClickedButtonselect(  m_var.iCurLineIndex  );

}

void CDlgVideoTagCfg::OnEnSetfocusEditsubtitle0()
{
	// TODO: Add your control notification handler code here
	m_var.iCurLineIndex  =  0;	
	bShowInfo_btn_subtitlesSettings(  );

}

void CDlgVideoTagCfg::OnEnSetfocusEditsubtitle1()
{
	// TODO: Add your control notification handler code here
	m_var.iCurLineIndex  =  1;	
	bShowInfo_btn_subtitlesSettings(  );

}

void CDlgVideoTagCfg::OnEnSetfocusEditsubtitle2()
{
	// TODO: Add your control notification handler code here
	m_var.iCurLineIndex  =  2;	
	bShowInfo_btn_subtitlesSettings(  );

}


void CDlgVideoTagCfg::OnEnSetfocusEditsubtitle3()
{
	// TODO: Add your control notification handler code here
	m_var.iCurLineIndex  =  3;	
	bShowInfo_btn_subtitlesSettings(  );

}


void CDlgVideoTagCfg::OnEnSetfocusEditsubtitle4()
{
	// TODO: Add your control notification handler code here
	m_var.iCurLineIndex  =  4;	
	bShowInfo_btn_subtitlesSettings(  );

}


void CDlgVideoTagCfg::OnEnSetfocusEditsubtitle5()
{
	// TODO: Add your control notification handler code here
	m_var.iCurLineIndex  =  5;	
	bShowInfo_btn_subtitlesSettings(  );

}


void CDlgVideoTagCfg::OnEnSetfocusEditsubtitle6()
{
	// TODO: Add your control notification handler code here
	m_var.iCurLineIndex  =  6;	
	bShowInfo_btn_subtitlesSettings(  );

}


void CDlgVideoTagCfg::OnEnSetfocusEditsubtitle7()
{
	// TODO: Add your control notification handler code here
	m_var.iCurLineIndex  =  7;	
	bShowInfo_btn_subtitlesSettings(  );

}


void CDlgVideoTagCfg::OnEnSetfocusEditsubtitle8()
{
	// TODO: Add your control notification handler code here
	m_var.iCurLineIndex  =  8;	
	bShowInfo_btn_subtitlesSettings(  );

}


void CDlgVideoTagCfg::OnEnSetfocusEditsubtitle9()
{
	// TODO: Add your control notification handler code here
	m_var.iCurLineIndex  =  9;	
	bShowInfo_btn_subtitlesSettings(  );

}


void CDlgVideoTagCfg::OnEnSetfocusEditsubtitle10()
{
	// TODO: Add your control notification handler code here
	m_var.iCurLineIndex  =  10;	
	bShowInfo_btn_subtitlesSettings(  );

}


void CDlgVideoTagCfg::OnEnSetfocusEditsubtitle11()
{
	// TODO: Add your control notification handler code here
	m_var.iCurLineIndex  =  11;	
	bShowInfo_btn_subtitlesSettings(  );

}

