
#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
//#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"
#include	"qmcDmoPublic.h"
#include	"qmcCmdProc.h"
#include	"tmpCeLib.h"
//  #include	"myfourcc.h"
#include	"module_qisCamCap.h"
#include	"isCmdConst.h"
#include	"qyOpenShellCommon.h"
#include	"qyCusResTemp.h"
#include	"policyAvParams.h"
//#include	"isCliHelpPublic.h"
//#include	"funcsForIsCliHelp.h"
#include	"addTxt.h"
#include	"qmcCfg.h"

// void  CTX_mem_free(  CTX_addTxt  *  pCtx,  int  index  )
void  ADD_txt_mem_free(  ADD_txt_mem  *  pMem  )
{
	if  (  !pMem  )  return;
#if  0
	if  (  !pCtx  )  return;
	if  (  index  <  0  ||  index  >=  mycountof(  pCtx->mems  )  )  return;
#endif

	if  (  pMem->hFont  )  {
		DeleteObject(  pMem->hFont  );  pMem->hFont  =  NULL;
	}

	//  2013/03/11
	MACRO_safeFree(  pMem->pTxtBuf  );
	pMem->iTxtBufSize  =  0;

	//  2013/12/06
	memset(  pMem,  0,  sizeof(  pMem[0]  )  );

	return;
}

void  CTX_addTxt_free(  CTX_addTxt  *  pCtx  )
{
	//  CTX_addTxt  *  pCtx  =  (    CTX_addTxt  *  )pCTX_addTxt;

	if  (  !pCtx  )  return;

	int  i;
	for  (  i  =  0;  i  <  mycountof(  pCtx->mems  );  i  ++  )  {
		ADD_txt_mem_free(  &pCtx->mems[i]  );
	}

	//
	memset(  pCtx,  0,  sizeof(  pCtx[0]  )  );

	return;
}


//
SUBTITLE_cfgEx  *  addTxt_getMemCfgByIndex(  CTX_addTxt  *  pCtx_addTxt,  int  addTxtCfgIndex  )
{
	if  (  addTxtCfgIndex  <  0  ||  addTxtCfgIndex  >=  mycountof(  pCtx_addTxt->subtitlesCfg.mems  )  )  return  NULL;

	return  &pCtx_addTxt->subtitlesCfg.mems[addTxtCfgIndex];
}

ADD_txt_mem  *  addTxt_getMemByIndex(  CTX_addTxt  *  pCtx_addTxt,  int  addTxtIndex  )
{
	if  (  addTxtIndex  <  0  ||  addTxtIndex  >=  mycountof(  pCtx_addTxt->mems  )  )  return  NULL;

	return  &pCtx_addTxt->mems[addTxtIndex];
}




//  2010/09/13
#ifndef  __WINCE__


//
BOOL  bNeedUpdate_addTxt(  LPCTSTR  videoHint,  BITMAPINFO  *  pBmi_pic,  BOOL  bLine0,  	SUBTITLE_cfgEx  *  pMemCfg,  ADD_txt_mem  *  pMem,  BOOL  *  pbModified_img,  QIS_trace_txt_change  *  pChange  )
{
	BOOL  bNeedUpdate  =  FALSE;

	//
	if  (  !pChange  )  {
		MACRO_qyAssert(  0,  _T(  "bNeedUpdate_addTxt: pChange is null"  )  );
		return  FALSE;
	}
	QIS_trace_txt_change  &change  =  *pChange;

	
	//
	//
	if  (  pMem->tickCnts.dwModifiedTickCnt_font  !=  pMemCfg->tickCnts.dwModifiedTickCnt_font  
		||  pMem->tickCnts.dwModifiedTickCnt_color  !=  pMemCfg->tickCnts.dwModifiedTickCnt_color
		||  pMem->tickCnts.dwModifiedTickCnt_tag  !=  pMemCfg->tickCnts.dwModifiedTickCnt_tag  )
	{
		bNeedUpdate  =  TRUE;

		//
		#ifdef  __DEBUG__
				change.bChanged_tickCnts  =  TRUE;
				//
				M_qtc_tcsCat(  pChange,  _T(  "tickCnts changed"  )  );
		#endif
	}
	//  2016/02/13
	//
	if  (  !bNeedUpdate  )  {
		//  if  (  !index  )  //  注意: 实际上只有index为0时才使用这个videoHint. 
		if  (  videoHint  )  {
			if  (  _tcscmp(  videoHint,  pMem->subtitle0_defaultTag  )  )  {
				//
				#ifdef  __DEBUG__
						change.bChanged_defaultTag  =  TRUE;  
						_sntprintf(  change.tBuf,  mycountof(  change.tBuf  ),  _T(  "new %s, old %s"  ),  videoHint,  pMem->subtitle0_defaultTag  );
						//
						M_qtc_tcsCat(  pChange,  _T(  "tag changed"  )  );
				#endif

				//
				//safeTcsnCpy(  videoHint,  pMem->subtitle0_defaultTag,  mycountof(  pMem->subtitle0_defaultTag  )  );
				bNeedUpdate  =  TRUE;  

			}
			//  2017/07/07
			if  (  !videoHint[0]  )  {
				//if  (  pMem->bih_txt.biWidth  ||  pMem->bih_txt.biHeight  )  
				if  (  pMem->bih_txt.biWidth  &&  pMem->bih_txt.biHeight  )		//  2017/09/28
				{
					bNeedUpdate  =  TRUE;
					//
					#ifdef  __DEBUG__
							traceLog((TCHAR*)  _T(  "bNeedUpdata_addTxt: video is \"\", bih_txt is not 0"  )  );
					#endif
				}
			}
		}
	}
	if  (  !bNeedUpdate  )  {
		if  (  pMemCfg->subtitle.tag.ucbDisplayTime  )  {
			time_t				t;
			//char				timeBuf[CONST_qyTimeLen  +  1]	=	"";
			//
			time(  &t  );
			//
			//  2014/12/19
			if  (  pMem->tTime  !=  t  )  {
				pMem->tTime  =  t;
				bNeedUpdate  =  TRUE;

				//
				#ifdef  __DEBUG__
						change.bChanged_tTime  =  TRUE;
						//
						M_qtc_tcsCat(  pChange,  _T(  "time changed"  )  );
				#endif
			}
		}
	}

	return  bNeedUpdate;

}


//
int  getRealTxt_addTxt(  LPCTSTR  videoHint,  BOOL  bDemo,  BOOL  bLine0,  SUBTITLE_cfgEx  *  pMemCfg,  ADD_txt_mem  *  pMem,  TCHAR  *  txt,  int  cnt_txt  )
{
	int  iErr  =  -1;

	//
	txt[0]  =  0;

	//
#if  0  //  2016/06/08
	if  (  pMemCfg->subtitle.tag.ucbUseDefault  )  {
		//if  (  bLine0  )  
		{
			_sntprintf(  txt,  cnt_txt,  _T(  "%s%s"  ),  txt,  pMem->subtitle0_defaultTag  );
		}
		}		
	else
#endif
	{
		  if  (  videoHint  )  _sntprintf(  txt,  cnt_txt,  _T(  "%s%s"  ),  txt,  videoHint  );
		  else  _sntprintf(  txt,  cnt_txt,  _T(  "%s%s"  ),  txt,  pMemCfg->subtitle.tag.txt  );		
	}

	//  2013/03/21. 第0行在demo中不让修改
	if  (  bDemo  )  {
		if  (  bLine0  )  {
			//_sntprintf(  txt,  cnt_txt,  _T(  "%s"  ),  pMem->subtitle0_defaultTag  );
		}			
	}


	//				
	if  (  pMemCfg->subtitle.tag.ucbDisplayTime  )  {
		//
		char				timeBuf[CONST_qyTimeLen  +  1]	=	"";

		getTimelStr(  pMem->tTime,  timeBuf,  mycountof(  timeBuf  )  );		//  2013/03/25
		
		//	
		char  y2[2  +  1],  MM[2  +  1],  dd[2  +  1],  hh[2  +  1],  mm[2  +  1],  ss[2  +  1];		
		safeStrnCpy(  timeBuf  +  2,  y2,  mycountof(  y2  )  );
		safeStrnCpy(  timeBuf  +  4,  MM,  mycountof(  MM  )  );				
		safeStrnCpy(  timeBuf  +  6,  dd,  mycountof(  dd  )  );				
		safeStrnCpy(  timeBuf  +  8,  hh,  mycountof(  hh  )  );				
		safeStrnCpy(  timeBuf  +  10,  mm,  mycountof(  mm  )  );				
		safeStrnCpy(  timeBuf  +  12,  ss,  mycountof(  ss  )  );
						
		_sntprintf(  txt,  cnt_txt,  _T(  "%s %S/%S/%S %S:%S:%S"  ),  txt,  y2,  MM,  dd,  hh,  mm,  ss  );					
	}

	iErr  =  0;

	return  iErr;
}

//
 //  2016/05/15
 //  2014/01/13. 如果videoHint不为null,则使用videoHint为内容。否则，...
int  updateImg_addTxt(  QY_MC  *  pQyMc,  LPCTSTR  videoHint,  BITMAPINFO  *  pBmi_pic,  BOOL  bLine0,  	SUBTITLE_cfgEx  *  pMemCfg,  ADD_txt_mem  *  pMem,  BOOL  *  pbModified_img,  LPCTSTR  dbgHint  )
{
	int			iErr	=	-1;
	//QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  -1;
	MC_VAR_common  *  pProcInfo  =  (MC_VAR_common*)pQyMc->get_pProcInfo(  );//  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	if  (  !pQmcCfg  )  return  -1;
	//
	HWND				hWnd		=	pQyMc->gui.hMainWnd;
	HDC					hDc			=	NULL;
	HDC					hDc_mem		=	NULL;
	HBITMAP				hBmp		=	NULL;
	HBITMAP				hBmp_old	=	NULL;
	HFONT				hFont		=	NULL;
	BOOL				bModified_img  =  FALSE;
	
	//  2014/12/19
	if  (  !dbgHint  )  dbgHint  =  _T(  ""  );
	
#ifdef  __DEBUG__
	if  (  !pMem->pTxtBuf  )  {
		int  i;
		i  =  0;
	}
#endif

	//  2016/02/13
	//
	if  (  !pMemCfg  )  return  -1;

	//
	BOOL	bNeedUpdate  =  FALSE;
#if  0
	//
#ifdef  __DEBUG__
		struct			{
			BOOL		bChanged_tickCnts;
			BOOL		bChanged_defaultTag;
			BOOL		bChanged_tTime;
			//
			TCHAR		tBuf[128];
		}				change  =  {  0, };

#endif
	//
	if  (  pMem->tickCnts.dwModifiedTickCnt_font  !=  pMemCfg->tickCnts.dwModifiedTickCnt_font  
		||  pMem->tickCnts.dwModifiedTickCnt_color  !=  pMemCfg->tickCnts.dwModifiedTickCnt_color
		||  pMem->tickCnts.dwModifiedTickCnt_tag  !=  pMemCfg->tickCnts.dwModifiedTickCnt_tag  )
	{
		bNeedUpdate  =  TRUE;

		//
		#ifdef  __DEBUG__
				change.bChanged_tickCnts  =  TRUE;
		#endif
	}
	//  2016/02/13
	//
	if  (  !bNeedUpdate  )  {
		//  if  (  !index  )  //  注意: 实际上只有index为0时才使用这个videoHint. 
		if  (  videoHint  )  {
			if  (  _tcscmp(  videoHint,  pMem->subtitle0_defaultTag  )  )  {
				//
				#ifdef  __DEBUG__
						change.bChanged_defaultTag  =  TRUE;  
						_sntprintf(  change.tBuf,  mycountof(  change.tBuf  ),  _T(  "new %s, old %s"  ),  videoHint,  pMem->subtitle0_defaultTag  );
				#endif

				//
				safeTcsnCpy(  videoHint,  pMem->subtitle0_defaultTag,  mycountof(  pMem->subtitle0_defaultTag  )  );
				bNeedUpdate  =  TRUE;  

			}
		}
	}
	if  (  !bNeedUpdate  )  {
		if  (  pMemCfg->subtitle.tag.ucbDisplayTime  )  {
			time_t				t;
			//char				timeBuf[CONST_qyTimeLen  +  1]	=	"";
			//
			time(  &t  );
			//
			//  2014/12/19
			if  (  pMem->tTime  !=  t  )  {
				pMem->tTime  =  t;
				bNeedUpdate  =  TRUE;

				//
				#ifdef  __DEBUG__
						change.bChanged_tTime  =  TRUE;
				#endif
			}
		}
	}
#endif

	//
	QIS_trace_txt_change  qttc  =  {0};
	qttc.ptHint  =  (  TCHAR  *  )dbgHint;
	//  2016/05/18
	bNeedUpdate  =  bNeedUpdate_addTxt(  videoHint,  pBmi_pic,  bLine0,  pMemCfg,  pMem,  pbModified_img,  &qttc  );

	//
	if  (  !bNeedUpdate  )  {
		iErr  =  0;  goto  errLabel;
	}

	//
#ifdef  __DEBUG__
		if  (  pQmcCfg->debugStatusInfo.ucbDebugSubtitle  )  {
			//traceLog((TCHAR*)  _T(  "updateImg_addTxt,  bNeedUpdate true, (%d,%d,%d), %s, %s"  ),  change.bChanged_tickCnts,  change.bChanged_defaultTag,  change.bChanged_tTime,  change.tBuf,  dbgHint  );
		}
#endif

	//
	bModified_img  =  TRUE;

	//  2013/11/15
	QM_SHM_CMDS* pShmCmds; pShmCmds = (QM_SHM_CMDS*)pProcInfo->get_QM_SHM_CMDS();	//  QY_GET_shmCmds(  );				
	BOOL  bDemo; bDemo = (pShmCmds && pShmCmds->ucbDaemonDemo);


	//
	if  (  pMem->tickCnts.dwModifiedTickCnt_font  !=  pMemCfg->tickCnts.dwModifiedTickCnt_font  
		//||  pMem->addTxtCfgIndex  !=  addTxtCfgIndex												//  2016/02/13
		)  
	{
		if  (  pMem->hFont  )  {
			DeleteObject(  pMem->hFont  );  pMem->hFont  =  NULL;					 
		}
	}

	//
	if  (  !bDemo  ||  !bLine0  )  {
		if  (  !pMem->hFont  )  {				
			if  (  pMemCfg->subtitle.font.lf.lfFaceName[0]  )  {
				pMem->hFont  =  CreateFontIndirect(  &pMemCfg->subtitle.font.lf  );  				 
			}								 
		}
	}
			
	
	//
	TCHAR	hint[256]; hint[0] = 0;// = _T("");

	//
#if  0
	if  (  pMemCfg->subtitle.tag.ucbUseDefault  )  {
		//if  (  bLine0  )  
		{
			_sntprintf(  hint,  mycountof(  hint  ),  _T(  "%s%s"  ),  hint,  pMem->subtitle0_defaultTag  );
		}
		}		
	else  {
		  if  (  videoHint  )  _sntprintf(  hint,  mycountof(  hint  ),  _T(  "%s%s"  ),  hint,  videoHint  );
		  else  _sntprintf(  hint,  mycountof(  hint  ),  _T(  "%s%s"  ),  hint,  pMemCfg->subtitle.tag.txt  );		
	}

	//  2013/03/21. 第0行在demo中不让修改
	if  (  bDemo  )  {
		if  (  bLine0  )  {
			_sntprintf(  hint,  mycountof(  hint  ),  _T(  "%s"  ),  pMem->subtitle0_defaultTag  );
		}			
	}


	//				
	if  (  pMemCfg->subtitle.tag.ucbDisplayTime  )  {
		//
		char				timeBuf[CONST_qyTimeLen  +  1]	=	"";

		getTimelStr(  pMem->tTime,  timeBuf,  mycountof(  timeBuf  )  );		//  2013/03/25
		
		//	
		char  y2[2  +  1],  MM[2  +  1],  dd[2  +  1],  hh[2  +  1],  mm[2  +  1],  ss[2  +  1];		
		safeStrnCpy(  timeBuf  +  2,  y2,  mycountof(  y2  )  );
		safeStrnCpy(  timeBuf  +  4,  MM,  mycountof(  MM  )  );				
		safeStrnCpy(  timeBuf  +  6,  dd,  mycountof(  dd  )  );				
		safeStrnCpy(  timeBuf  +  8,  hh,  mycountof(  hh  )  );				
		safeStrnCpy(  timeBuf  +  10,  mm,  mycountof(  mm  )  );				
		safeStrnCpy(  timeBuf  +  12,  ss,  mycountof(  ss  )  );
						
		_sntprintf(  hint,  mycountof(  hint  ),  _T(  "%s %S/%S/%S %S:%S:%S"  ),  hint,  y2,  MM,  dd,  hh,  mm,  ss  );					
	}
#endif
	//
	getRealTxt_addTxt(  videoHint,  bDemo,  bLine0,  pMemCfg,  pMem,  hint,  mycountof(  hint  )  );

	//
	if  (  !hint[0]  )  {  //  这里表明没有txt
		MACRO_safeFree(  pMem->pTxtBuf  );
		//  2017/
		memset(  &pMem->bih_txt,  0,  sizeof(  pMem->bih_txt  )  );
		//
		iErr  =  0;  goto  errLabel;
	}

		//
		//  2013/03/11
	G_guiData_qyMc* pGuiData; pGuiData = (G_guiData_qyMc*)pProcInfo->get_g_guiData();  //  pFuncs->pf_get_g_guiData(  );
		if  (  !pGuiData  )  goto  errLabel;
		

		HFONT				hFont_toTextOut; hFont_toTextOut = NULL;
		int  iW_txtImg; iW_txtImg = 0;	//  pBmi_pic->bmiHeader.biWidth;
		int  iH_txtImg; iH_txtImg = 0;
		
		if  (  pMem->hFont  )  {
			hFont_toTextOut  =  pMem->hFont;
			iH_txtImg  =  abs(  pMemCfg->subtitle.font.lf.lfHeight  );
			}
		else  {
			  if  (  pBmi_pic->bmiHeader.biWidth  <=  320  )  {
				  hFont_toTextOut  =  pGuiData->hFont_videoHint_320x240;
				  iH_txtImg  =  pGuiData->lfHeight_videoHint_320x240;
				  }
			  else  if  (  pBmi_pic->bmiHeader.biWidth  <  1280  )  {
						hFont_toTextOut  =  pGuiData->hFont_videoHint_640x480;
						iH_txtImg  =  pGuiData->lfHeight_videoHint_640x480;
				        }
			  else  if  (  pBmi_pic->bmiHeader.biWidth  <  1920  )  {
						hFont_toTextOut  =  pGuiData->hFont_videoHint_1280x720;
						iH_txtImg  =  pGuiData->lfHeight_videoHint_1280x720;	
				  		}		
			  else  {
				    hFont_toTextOut  =  pGuiData->hFont_videoHint_1920x1080;
					iH_txtImg  =  pGuiData->lfHeight_videoHint_1920x1080;		  
			  }
		}


		//
		hDc  =  GetDC(  hWnd  );
		if  (  !hDc  )  goto  errLabel;

		hDc_mem  =  CreateCompatibleDC(  hDc  );
		if  (  !hDc_mem  )  goto  errLabel;


#if  10
		//
		if  (  hFont_toTextOut  )  {
			hFont  =  (  HFONT  )SelectObject(  hDc_mem,  hFont_toTextOut  );
		}

		//  2013/03/11
		GetTextExtentPoint32(  hDc_mem,  hint,  lstrlen(  hint  ),  &pMem->size_GetTextExtentPoint32  );
		if  (  pMem->size_GetTextExtentPoint32.cy  <=  0  )  goto  errLabel;

		//
		int  shadow_xOffset; shadow_xOffset = 0;
		int  shadow_yOffset; shadow_yOffset = 0;

#if 0
		if  (  pMemCfg->subtitle.color.ucb3dShadow  )  {
			shadow_xOffset  =  pMemCfg->subtitle.color.shadow_xOffset;
			shadow_yOffset  =  pMemCfg->subtitle.color.shadow_yOffset;
		}
		//
#endif

#if  10
		//if  (  pMemCfg->subtitle.color.usePath.ucbUsePath  )  
		{	//  2014/12/21. 斜体字时，会有一个斜角被切掉，所以加一点空余
			shadow_xOffset  =  3;
		}
		//  2014/12/24
		if  (  pMemCfg->subtitle.color.usePath.ucbUsePath  )  {
			shadow_yOffset  =  0;
		}
		pMem->shadow_xOffset  =  shadow_xOffset;
		pMem->shadow_yOffset  =  shadow_yOffset;
#endif
		//


		//
		iW_txtImg  =  min(  pBmi_pic->bmiHeader.biWidth,  pMem->size_GetTextExtentPoint32.cx  +  abs(  shadow_xOffset  )  );
		iH_txtImg  =  min(  pBmi_pic->bmiHeader.biHeight,  pMem->size_GetTextExtentPoint32.cy  +  abs(  shadow_yOffset  )  );
		
		if  (  iW_txtImg  <=  0  ||  iH_txtImg  <=  0  )  goto  errLabel;
		
		//
		if  (  pMem->pTxtBuf  )  {
			if  (  iW_txtImg  !=  pMem->bih_txt.biWidth  ||  iH_txtImg  !=  pMem->bih_txt.biHeight  )  {
				MACRO_safeFree(  pMem->pTxtBuf  );
			}
		}

		//
		if  (  !pMem->pTxtBuf  )  {					
			makeBmpInfoHeader_rgb(  24,  iW_txtImg,  iH_txtImg,  &pMem->bih_txt  );
			pMem->iTxtBufSize  =  pMem->bih_txt.biSizeImage;
			pMem->pTxtBuf  =  (  char  *  )mymalloc(  pMem->iTxtBufSize  );
			if  (  !pMem->pTxtBuf  )  goto  errLabel;
		}


		//  2013/03/11
		BITMAPINFO* pBmi_txt; pBmi_txt = (BITMAPINFO*)&pMem->bih_txt;
		char* pTxtBuf; pTxtBuf = pMem->pTxtBuf;
		
		if  (  !pTxtBuf  ||  !pBmi_txt->bmiHeader.biWidth  ||  !pBmi_txt->bmiHeader.biHeight  )  goto  errLabel;
#endif

		//
		hBmp  =  CreateCompatibleBitmap(  hDc,  pBmi_txt->bmiHeader.biWidth,  pBmi_txt->bmiHeader.biHeight  );
		if  (  !hBmp  )  goto  errLabel;

		hBmp_old  =  (  HBITMAP  )SelectObject(  hDc_mem,  hBmp  );
		if  (  !hBmp_old  )  goto  errLabel;

		//  
		//  brushDc(  RGB(  222,  222,  222  ),  hDc_mem,  0,  0,  pBmi_txt->bmiHeader.biWidth,  pBmi_txt->bmiHeader.biHeight  );
		brushDc(  RGB(  pMemCfg->subtitle.color.maskColor_r,  pMemCfg->subtitle.color.maskColor_g,  pMemCfg->subtitle.color.maskColor_b  ),  hDc_mem,  0,  0,  pBmi_txt->bmiHeader.biWidth,  pBmi_txt->bmiHeader.biHeight  );



		#ifdef  __DEBUG__
				//  traceLog((TCHAR*)  _T(  "iW_txtImg %d, iH_txtImg %d, size_GetTextExtentPoint32.cx %d, cy %d"  ),  iW_txtImg,  iH_txtImg,  pCtx->size_GetTextExtentPoint32.cx,  pCtx->size_GetTextExtentPoint32.cy  );
		#endif

		//
		SetBkMode(  hDc_mem,  TRANSPARENT  );
		//
		int  xStart; xStart = 0;
		int  yStart; yStart = 0;
		//
#if  0
		if  (  pMemCfg->subtitle.color.ucb3dShadow  )  {
			SetTextColor(  hDc_mem,  RGB(  pMemCfg->subtitle.color.shadowColor_r,  pMemCfg->subtitle.color.shadowColor_g,  pMemCfg->subtitle.color.shadowColor_b  )  );
			if  (  shadow_xOffset  <  0  )  xStart  =  0;
			else  xStart  =  shadow_xOffset;
			if  (  shadow_yOffset  <  0  )  yStart  =  0;
			else  yStart  =  shadow_yOffset;
			TextOut(  hDc_mem,  xStart,  yStart,  hint,  lstrlen(  hint  )  );		
		}
#endif
		//
		SetTextColor(  hDc_mem,  RGB(  pMemCfg->subtitle.color.fontColor_r,  pMemCfg->subtitle.color.fontColor_g,  pMemCfg->subtitle.color.fontColor_b  )  );
		if  (  shadow_xOffset  <  0  )  xStart  =  abs(  shadow_xOffset  );
		else  xStart  =  0;
		if  (  shadow_yOffset  <  0  )  yStart  =  abs(  shadow_yOffset  );
		else  yStart  =  0;
		//
		if  (  !pMemCfg->subtitle.color.usePath.ucbUsePath  )  {
			TextOut(  hDc_mem,  xStart,  yStart,  hint,  lstrlen(  hint  )  );		
			}
		else  {
			  HPEN  hPen  =  NULL;
			  HPEN  hOldPen  =  NULL;
			  //
			  COLORREF  color_pen  =  RGB(  pMemCfg->subtitle.color.usePath.color_edge_r,  pMemCfg->subtitle.color.usePath.color_edge_g,  pMemCfg->subtitle.color.usePath.color_edge_b  );  //  RGB(  255,255,255  );//  RGB(  165,  165,  165  );  //RGB(  75,  75,  75  );
			  COLORREF  color_internal  =  RGB(  pMemCfg->subtitle.color.fontColor_r,  pMemCfg->subtitle.color.fontColor_g,  pMemCfg->subtitle.color.fontColor_b  );  //  RGB(  255,  255,  255  );
			  //
			  int  cWidth  =  1;
			  if  (  pMemCfg->subtitle.color.usePath.cWidth_pen  )  {				
				  cWidth  =  pMemCfg->subtitle.color.usePath.cWidth_pen;
			  }
			  //
			  hPen  =  CreatePen(  PS_SOLID,  cWidth,  color_pen  );
			  if  (  hPen  )  {
				  hOldPen  =  (  HPEN  )SelectObject(  hDc_mem,  hPen  );
				  
				  BeginPath(  hDc_mem  );
				  TextOut(  hDc_mem,  xStart,  yStart,  hint,  lstrlen(  hint  )  );		
				  EndPath(  hDc_mem  );		

				  HBRUSH  br  =  NULL;
				  HBRUSH  oldbr  =  NULL;
				  br  =  CreateSolidBrush(  color_internal  );
				  if  (  br  )  {

					  oldbr  =  (  HBRUSH  )SelectObject(  hDc_mem,  br  );
				  
					  if  (  pMemCfg->subtitle.color.usePath.ucbFilled  )  {
						  StrokeAndFillPath(  hDc_mem  );
						  }
					  else  {
						    StrokePath(  hDc_mem  );
					  }

					  SelectObject(  hDc_mem,  oldbr  );

					  DeleteObject(  br  );
				  }

				  SelectObject(  hDc_mem,  hOldPen  );
				  //
				  DeleteObject(  hPen  );
			  }
		}
		//
		SetBkMode(  hDc_mem,  OPAQUE  );
		if  (  hFont  )  {
			SelectObject(  hDc_mem,  hFont  );  hFont  =  NULL;
		}

		//  
		int	nCount; nCount = GetDIBits(hDc_mem, hBmp, 0, pBmi_txt->bmiHeader.biHeight, pTxtBuf, (BITMAPINFO*)pBmi_txt, DIB_RGB_COLORS);
		
		//
		iErr  =  0;

errLabel:
			
		if  (  !iErr  )  {
			//	
			if  (  bNeedUpdate  )  {
				memcpy(  &pMem->tickCnts,  &pMemCfg->tickCnts,  sizeof(  pMem->tickCnts  )  );
				//  2016/05/18
				safeTcsnCpy(  videoHint,  pMem->subtitle0_defaultTag,  mycountof(  pMem->subtitle0_defaultTag  )  );
			}

			//
			if  (  pbModified_img  )  *pbModified_img  =  bModified_img;
		}

		//
	if  (  hFont  )  {
		SelectObject(  hDc_mem,  hFont  );  hFont  =  NULL;	
	}


	if  (  hBmp_old  )  SelectObject(  hDc_mem,  hBmp_old  );

	if  (  hBmp  )  DeleteObject(  hBmp  );
	if  (  hDc_mem  )  DeleteDC(  hDc_mem  );
	if  (  hDc  )  ReleaseDC(  hWnd,  hDc  );
	
	return  iErr;

}








//
int drawImg_addTxt(  CTX_addTxt  *  pCtx,  BITMAPINFO  *  pBmi_pic,  char  *  pPicBuf,  SUBTITLE_cfgEx  *  pMemCfg,  ADD_txt_mem  *  pMem  )
{
	int		iErr	=	-1;

	//
	if  (  !pMemCfg  ||  !pMem  )  return  -1;

	//
	BITMAPINFO	*	pBmi_txt	=	(  BITMAPINFO  *  )&pMem->bih_txt;
	char		*	pTxtBuf		=	pMem->pTxtBuf;

	if (!pTxtBuf || !pBmi_txt->bmiHeader.biWidth || !pBmi_txt->bmiHeader.biHeight)  return -1;// goto  errLabel;

	//
	int				lineBytes_txt	=	M_lineBytes_rgb(  24,  pBmi_txt->bmiHeader.biWidth  );
	int				lineBytes_pic	=	M_lineBytes_rgb(  24,  pBmi_pic->bmiHeader.biWidth  );
	int				iW			=	min(  pBmi_txt->bmiHeader.biWidth,  pBmi_pic->bmiHeader.biWidth  );
	int				iH			=	min(  pBmi_txt->bmiHeader.biHeight,  pBmi_pic->bmiHeader.biHeight  );
	int				i,  j;
	BYTE		*	pPix_txt;
	BYTE		*	pPix_pic;

	//
	int  shadow_xOffset  =  0;  		
	int  shadow_yOffset  =  0;
#if  0
	if  (  pMemCfg->subtitle.color.ucb3dShadow  )  {
		shadow_xOffset  =  pMemCfg->subtitle.color.shadow_xOffset;
		shadow_yOffset  =  pMemCfg->subtitle.color.shadow_yOffset;		
	}
#endif
	//  2014/12/24
	shadow_xOffset  =  pMem->shadow_xOffset;
	shadow_yOffset  =  pMem->shadow_yOffset;
	//
	int  shadow_xOffset_abs  =  abs(  shadow_xOffset  );
	int  shadow_yOffset_abs  =  abs(  shadow_yOffset  );

	//
	int  xStart  =  pMemCfg->subtitle.pos.xStart;
	int  yStart  =  pMemCfg->subtitle.pos.yStart;
	if  (  shadow_xOffset  <  0  )  xStart  -=  shadow_xOffset_abs;
	if  (  shadow_yOffset  <  0  )  yStart  -=  shadow_yOffset_abs;
	//  2014/12/22
	if  (  pMemCfg->subtitle.pos.ucbHorizontalCenter  )  {
		if  (  pMem->size_GetTextExtentPoint32.cx  <  pBmi_pic->bmiHeader.biWidth  )  {
			xStart  =  (  pBmi_pic->bmiHeader.biWidth  -  pMem->size_GetTextExtentPoint32.cx  )  /  2;
		}
	}
	//
	int  x;
	int	 y;
	//
	if  (  xStart  <  0  )  xStart  =  0;
	if  (  yStart  <  0  )  yStart  =  0;
	//
	for  (  j  =  0;  j  <  iH;  j  ++  )  {
		 //
		 if  (  j  >=  pMem->size_GetTextExtentPoint32.cy  +  shadow_yOffset_abs  )  {
			 #ifdef  __DEBUG__
					 //  traceLog((TCHAR*)  _T(  "j %d, size_GetTextExtentPoint32.cy %d"  ),  j,  pCtx->size_GetTextExtentPoint32.cy  );
			 #endif
			 break;
		 }

		 //
		 if  (  !pMemCfg->subtitle.pos.ucbBottomUp  )  {
			 y  =  (  j  +  pBmi_pic->bmiHeader.biHeight  -  iH  )  -  yStart;
			 }
		 else  {
			   y  =  j  +  yStart;
		 }
		 if  (  y  <  0  )  continue;
		 if  (  y  >=  pBmi_pic->bmiHeader.biHeight  )  break;

		 //
		 for  (  i  =  0;  i  <  iW;  i  ++  )  {
			  //
			  if  (  i  >=  pMem->size_GetTextExtentPoint32.cx  +  shadow_xOffset_abs  )  break;
			  //
			  pPix_txt  =  (  BYTE  *  )(  pTxtBuf  +  j  *  lineBytes_txt  +  i  *  3  );
			  if  (  pPix_txt[0]  ==  pMemCfg->subtitle.color.maskColor_b	//  222
				  &&  pPix_txt[1]  ==  pMemCfg->subtitle.color.maskColor_g	//  222
				  &&  pPix_txt[2]  ==  pMemCfg->subtitle.color.maskColor_r	//  222  
				  )  
			  {			
				  continue;
			  }
			  //
			  //  pPix_pic  =  (  BYTE  *  )(  pPicBuf  +  (  j  +  pBmi_pic->bmiHeader.biHeight  -  iH  )  *  lineBytes_pic  +  i  *  3  );
			  x  =  i  +  xStart;
			  if  (  x  <  0  )  continue;
			  if  (  x  >=  pBmi_pic->bmiHeader.biWidth  )  break;
			  //
			  pPix_pic  =  (  BYTE  *  )(  pPicBuf  +  y  *  lineBytes_pic  +  x  *  3  );			  
			  memcpy(  pPix_pic,  pPix_txt,  3  );
			  continue;
		 }
	}

	iErr  =  0;

errLabel:


	return  iErr;
	
}


 //  2013/08/20
 int  drawWarningColor(  QY_MC  *  pQyMc,  CTX_addTxt  *  pCtx,  unsigned  char  ucbDaemonDemo,  BITMAPINFO  *  pBmi_pic,  char  *  pPicBuf,  DWORD  dwTickCnt_start  )
 {
	 int				iErr		=	-1;
	 //QY_MC		*		pQyMc		=	QY_GET_GBUF(  );

	 if  (  !ucbDaemonDemo  )  return  -1;

	 			
	 int  n  =  GetTickCount(  )  -  dwTickCnt_start;	
	 n  =  n  /  1000;			
	 n  =  pQyMc->uiMaxTimeInS_videoConference  -  n;

	 //
	 if  (  n  <  0  )  n  =  0;

	 //
	 int  maxWarningInS  =  pQyMc->uiMaxWarningInS_videoConference;
	 if  (  maxWarningInS  <=  0  )  return  -1;

	 if  (  maxWarningInS  <=  n  )  {	
		 //  还没到画警告色的时间呢
		 return  0;
	 }

	 float  f  =  n  *  1.0  /  maxWarningInS;

	 

#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "drawWarningColor: f %f"  ),  f  );
#endif

	 //
	 int				lineBytes_pic	=	M_lineBytes_rgb(  24,  pBmi_pic->bmiHeader.biWidth  );
	 int  iH  =  pBmi_pic->bmiHeader.biHeight;
		
#if  10
	 int  i;
	 for  (  i  =  0;  i  <  iH;  i  ++  )  {
		  char  *  pLine  =  pPicBuf  +  i  *  lineBytes_pic;
		  int  lineBytes_valid  =  f  *  pBmi_pic->bmiHeader.biWidth  *  3;
		  memset(  pLine  +  lineBytes_valid,  255,  lineBytes_pic  -  lineBytes_valid  );
	 }
#endif
	 

	 iErr  =  0;
errLabel:

	 return  iErr;
 }



 //  2013/03/10
 //  int  addTxtToPic(  CTX_addTxt  *  pCtx,  unsigned  char  ucbDaemonDemo,  LPCTSTR  videoHint,  DWORD  dwTickCnt_start,  COMPRESS_VIDEO  *  pCompressVideo,  BITMAPINFO  *  pBmi_pic,  char  *  pPicBuf  )
 int  addTxtToPic(  QY_MC  *  pQyMc,  CTX_addTxt  *  pCtx,  unsigned  char  ucbDaemonDemo,  LPCTSTR  videoHint,  DWORD  dwTickCnt_start,  QY_SHARED_OBJ  *  pSharedObj,  COMPRESS_VIDEO  *  pCompressVideo,  BITMAPINFO  *  pBmi_pic,  char  *  pPicBuf  )
{
	int					iErr		=	-1;
	//QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	int					i;

	//  2013/03/10
	if  (  !pCompressVideo  )  return  -1;
	
	//
	SUBTITLES_cfg	*	pSubtitlesCfg  =  &pCtx->subtitlesCfg;
	
	//
	if  (  !pPicBuf  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "addTxtToPic failed, pPicBuf is null"  )  );
		#endif
		return  -1;
	}
	if  (  pBmi_pic->bmiHeader.biClrImportant  !=  BI_RGB  
		||  pBmi_pic->bmiHeader.biBitCount  !=  24  )  
	{
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "addTxtToPic failed, pPic is not rgb24"  )  );
		#endif
		return  -1;
	}
 

	//
	if  (  1  //  pCompressVideo->tLastTime_addTxt  !=  pCompressVideo->input.tStartTran  
		)  
	{
		//
		TCHAR	hint[256]	=	_T(  ""  );		
		TCHAR	*	pT		=	(TCHAR*)_T(  ""  );
		//
		if  (  ucbDaemonDemo  )  {
			//  2016/05/21
			BOOL  b_warning  =  FALSE;
			//
			if  (  dwTickCnt_start  )  {
				int  n  =  GetTickCount(  )  -  dwTickCnt_start;
				n  =  n  /  1000;			
				n  =  pQyMc->uiMaxTimeInS_videoConference  -  n;
				if  (  n  >  pQyMc->uiMaxWarningInS_videoConference  )  {
					_sntprintf(  hint,  mycountof(  hint  ),  _T(  "剩余"  )  );
					}
				else  {
					  b_warning  =  TRUE;
					  //
					  _sntprintf(  hint,  mycountof(  hint  ),  _T(  "+影."  )  );
				}
				_sntprintf(  hint,  mycountof(  hint  ),  _T(  "%s%d分%d秒. "  ),  hint,  n  /  60,  n  %  60  );
			}
	
			pT  =  (TCHAR*)_T(  ""  );
			if  (  pBmi_pic->bmiHeader.biWidth  >  320  &&  pBmi_pic->bmiHeader.biHeight  >  240  )  {		//  2013/12/27. 因为320X240的字显得太大，所以少写一点
				if  (  bQmFreeVer(  pQyMc  )  )  {
					pT  =  (TCHAR*)_T(  "www.qycx.com"  );
					}
				else  {
					  switch  (  pQyMc->env.usLangId  )  {						
							  case  CONST_langId_PRC:							  
									pT  =  (TCHAR*)_T(  "清扬 Demo. www.qycx.com"  );							  
									break;						
							  case  CONST_langId_tw:							  
								    pT  =  (TCHAR*)_T(  "清揚 Demo. www.qycx.com"  );							  
									break;						
							  default:
									  pT  =  (TCHAR*)_T(  "Qycx trial edition. www.qycx.com"  );								
									  break;				
					  }
				}
			}
			_sntprintf(  hint,  mycountof(  hint  ),  (TCHAR*)_T(  "%s%s "  ),  hint,  pT  );
			//
			if  (  !b_warning  )  {  //  2016/05/21
				#if  0
				if  (  pQyMc->ucb_tttbbbMac  )  {
					hint[0]  =  0;
				}
				#endif
			}
		}
				
		//	
		TCHAR  sep_str[2]  =  _T(  ""  );
		if  (  hint[0]  )  sep_str[0]  =  _T(  ' '  );
		//
		if  (  pCtx->subtitlesCfg.mems[0].subtitle.tag.ucbUseDefault  )  {
			if  (  videoHint  )  {
				_sntprintf(  hint,  mycountof(  hint  ),  _T(  "%s%s%s"  ),  hint,  sep_str,  videoHint  );	
			}
			}
		else  {
			  _sntprintf(  hint,  mycountof(  hint  ),  _T(  "%s%s%s"  ),  hint,  sep_str,  pCtx->subtitlesCfg.mems[0].subtitle.tag.txt  );
		}

		//  2014/12/19
		TCHAR  dbgHint[128]  =  _T(  ""  );

		//
		for  (  i  =  0;  i  <  mycountof(  pCtx->mems  );  i  ++  )  {

			 //
			 BOOL  bLine0  =  !i;
			 //
			 #ifdef  __DEBUG__
					 _sntprintf(  dbgHint,  mycountof(  dbgHint  ),  _T(  "addTxtToPic: i %d. pCtx %p"  ),  i,  pCtx  );
					 //
					 if  (  i  ==  1  )  {
						 int ii  =  0;
					 }
			 #endif
			 //
			 SUBTITLES_cfg  *  pSubtitlesCfg  =  &pCtx->subtitlesCfg;
			 SUBTITLE_cfgEx  *  pMemCfg  =  addTxt_getMemCfgByIndex(  pCtx,  i  );		 
			 ADD_txt_mem  *  pMem  =  addTxt_getMemByIndex(  pCtx,  i  );
			 
			 //  2016/05/15
			 //
			 updateImg_addTxt(pQyMc,  i  ?  NULL  :  hint,  pBmi_pic,  bLine0,  pMemCfg,  pMem,  NULL,  dbgHint  );
		}
	}

	//
	if  (  !pSubtitlesCfg->flgs.ucbShowVideoHint  )  {
		if  (  !ucbDaemonDemo  )  {	//  2013/04/06
			iErr  =  0;  goto  errLabel;
		}
	}
	
#if  10
	for  (  i  =  0;  i  <  mycountof(  pCtx->mems  );  i  ++  )  {
		 if  (  !pSubtitlesCfg->flgs.ucbShowVideoHint  )  {
			 MACRO_qyAssert(  ucbDaemonDemo,  _T(  "Demo"  )  );
			 //  要把提示行显示出来
			 if  (  i  !=  0  )  continue;
		 }
		 //
		 SUBTITLE_cfgEx  *  pMemCfg  =  addTxt_getMemCfgByIndex(  pCtx,  i  );
		 ADD_txt_mem  *  pMem  =  addTxt_getMemByIndex(  pCtx,  i  );
		 //
		 drawImg_addTxt(  pCtx,  pBmi_pic,  pPicBuf,  pMemCfg,  pMem  );
	}
#endif
	
	//  2013/08/20
	if  (  ucbDaemonDemo  )  {
		if  (  dwTickCnt_start  )  {
			drawWarningColor(  pQyMc,  pCtx,  ucbDaemonDemo,  pBmi_pic,  pPicBuf,  dwTickCnt_start  );
		}
	}

	//
	iErr  =  0;

errLabel:

	return  iErr;
}


#endif




