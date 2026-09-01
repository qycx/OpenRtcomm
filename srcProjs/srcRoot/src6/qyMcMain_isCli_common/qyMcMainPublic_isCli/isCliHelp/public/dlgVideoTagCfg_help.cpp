
#include	"stdafx.h"

#include	"qyMcMainCommon.h"
#include	"myresource.h"

//#include	"DlgVideoTagCfg.h"
//#include	"afxdialogex.h"

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


__declspec(dllexport) int  getSubtitlesCfg_d3dWall(int  iCapType, int  iCapSubType, int  iUsage, SUBTITLES_cfg* pSubtitlesCfg)
{
	if (!pSubtitlesCfg)  return  -1;

	if (iCapType != CONST_capType_mosaic)  return  -1;
	if (iUsage != CONST_usage_mosaic_sys) {
		return  -1;
	}

	memset(pSubtitlesCfg, 0, sizeof(pSubtitlesCfg[0]));

	QY_MC* pQyMc = QY_GET_GBUF();
	if (!pQyMc) {
		traceLog(_T("getSubtitlesCfg failed: pQyMc is null"));
		return  -1;
	}


	int  wnd_w = 848;
	int  wnd_h = 480;

	//
	pSubtitlesCfg->wnd_w_org_unused = wnd_w;
	pSubtitlesCfg->wnd_h_org = wnd_h;
	//
	pSubtitlesCfg->flgs.ucbShowVideoHint = DEFAULT_subtitles_ucbShowVideoHint;
	pSubtitlesCfg->flgs.ucbEffectiveImmediately = DEFAULT_subtitles_ucbEffectiveImmediately;
	//
	int  i;
	for (i = 0; i < mycountof(pSubtitlesCfg->mems); i++) {
		//
		SUBTITLE_cfg* pVideoTagCfg = &pSubtitlesCfg->mems[i].subtitle;
		//		 
		lstrcpyn(pVideoTagCfg->font.lf.lfFaceName, DEFAULT_faceName_d3dWall, mycountof(pVideoTagCfg->font.lf.lfFaceName));
		//lstrcpyn(  pVideoTagCfg->font.lf.lfFaceName,  _T("simhei"),  mycountof(  pVideoTagCfg->font.lf.lfFaceName  )  );


		//  注册表里要存rgb指.读出后用GetRValue(  ), GetGValue(  ),  GetBValue(  )分解出r,g,b		
		COLORREF	fontColor = DEFAULT_fontColor_addTxt;

		//  2014/12/21
		COLORREF	edgeColor = DEFAULT_edgeColor;
		pVideoTagCfg->color.usePath.ucbUsePath = DEFAULT_ucbUsePath;
		pVideoTagCfg->color.usePath.cWidth_pen = DEFAULT_edge_width;
		pVideoTagCfg->color.usePath.ucbFilled = DEFAULT_bFilled;

		//
		pVideoTagCfg->font.lf.lfWeight = FW_NORMAL; //FW_BOLD;//FW_NORMAL;
		pVideoTagCfg->font.lf.lfCharSet = ANSI_CHARSET;		//  2013/12/22
		pVideoTagCfg->font.lf.lfItalic = DEFAULT_fontItalic;		//  2013/12/22
		//
		pVideoTagCfg->font.lf.lfHeight = DEFAULT_fontHeight_d3dWall;
		switch (i) {
		case  0:
			lstrcpyn(pVideoTagCfg->font.lf.lfFaceName, _T("Tahoma"), mycountof(pVideoTagCfg->font.lf.lfFaceName));
			//
			pVideoTagCfg->font.lf.lfHeight = DEFAULT_fontHeight_d3dWall_wizard;
			//
			pVideoTagCfg->font.ucbFixedSize = TRUE;
			break;
		case  CONST_addTxtCfgIndex_menu:
			//pVideoTagCfg->font.lf.lfHeight  =  56;	
			//
			pVideoTagCfg->font.ucbFixedSize = TRUE;
			break;
		case  CONST_addTxtCfgIndex_importantNote:
			//
			pVideoTagCfg->font.lf.lfHeight = DEFAULT_fontHeight_d3dWall_importantNote / 480.f * wnd_h;
			pVideoTagCfg->font.lf.lfWidth = 0;
			//
			//pVideoTagCfg->color.usePath.ucbUsePath  =  TRUE;
			//
			break;
		case  CONST_addTxtCfgIndex_warning_mosaic:
			fontColor = RGB(255, 255, 255);			//DEFAULT_fontColor_addTxt_warning;
			pVideoTagCfg->font.lf.lfHeight = 15;	//DEFAULT_fontHeight_d3dWall_warning;
			pVideoTagCfg->font.lf.lfWidth = 0;
			//
			pVideoTagCfg->color.usePath.ucbUsePath = FALSE;//TRUE;					   
			break;
			//  2016/01/03
		case  CONST_addTxtCfgIndex_prop_wall:
		case  CONST_addTxtCfgIndex_menu_wall:
			//  
			pVideoTagCfg->font.lf.lfHeight = 13;	//  16;	
			//
			pVideoTagCfg->font.ucbFixedSize = TRUE;

			break;
		case  CONST_addTxtCfgIndex_title:  //  2016/02/05
			pVideoTagCfg->font.lf.lfHeight = 13;

			pVideoTagCfg->font.ucbFixedSize = TRUE;
			break;

			//					   
		case  CONST_addTxtCfgIndex_tool_title:								//  2016/02/28
			lstrcpyn(pVideoTagCfg->font.lf.lfFaceName, CONST_faceName_Tahoma, mycountof(pVideoTagCfg->font.lf.lfFaceName));
			//
			pVideoTagCfg->font.lf.lfHeight = DEFAULT_fontHeight_d3dWall_wizard;
			//
			pVideoTagCfg->font.ucbFixedSize = TRUE;
			break;
		case  CONST_addTxtCfgIndex_tool_item:											//  2016/02/28
			lstrcpyn(pVideoTagCfg->font.lf.lfFaceName, CONST_faceName_Tahoma, mycountof(pVideoTagCfg->font.lf.lfFaceName));
			//
			pVideoTagCfg->font.lf.lfHeight = DEFAULT_fontHeight_d3dWall_wizard;
			//
			pVideoTagCfg->font.ucbFixedSize = TRUE;
			break;
		case  CONST_addTxtCfgIndex_peerImgTag:
			lstrcpyn(pVideoTagCfg->font.lf.lfFaceName, CONST_faceName_Tahoma, mycountof(pVideoTagCfg->font.lf.lfFaceName));
			//
			pVideoTagCfg->font.lf.lfHeight = 20;

			//					   
			edgeColor = RGB(0, 255, 0);

			//					   
#if  0
			pVideoTagCfg->color.usePath.ucbUsePath = 1;//DEFAULT_ucbUsePath;		 
			pVideoTagCfg->color.usePath.cWidth_pen = 2;//DEFAULT_edge_width;		 
			pVideoTagCfg->color.usePath.ucbFilled = DEFAULT_bFilled;
#endif

			//		 
			pVideoTagCfg->font.lf.lfWeight = FW_BOLD;//FW_NORMAL;

			//
			pVideoTagCfg->font.ucbFixedSize = TRUE;
			break;
		default:
			break;
		}


		//  
		pVideoTagCfg->color.fontColor_r = GetRValue(fontColor);
		pVideoTagCfg->color.fontColor_g = GetGValue(fontColor);
		pVideoTagCfg->color.fontColor_b = GetBValue(fontColor);

		//
		pVideoTagCfg->color.usePath.color_edge_r = GetRValue(edgeColor);
		pVideoTagCfg->color.usePath.color_edge_g = GetGValue(edgeColor);
		pVideoTagCfg->color.usePath.color_edge_b = GetBValue(edgeColor);

	}

	return 0;
}

