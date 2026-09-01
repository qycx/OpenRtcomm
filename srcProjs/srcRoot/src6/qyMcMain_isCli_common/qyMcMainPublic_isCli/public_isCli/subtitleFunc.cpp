

#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"myresource.h"

//#include	"DlgVideoTagCfg.h"
//  #include	"afxdialogex.h"

#include	"qyCusResTemp.h"

//  #include	"DlgSubtitleSelect.h"

#include	"qmcCmdProc.h"

#include	"qyOpenShellCommon.h"
//  #include	"DlgTalk.h"
#include	"dlgTalkProc.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"



//  SUBTITLES_cfg  *  getCurSubtitlesCfg(  int  iSharedObjType,  int  iCapType,  int  iCapSubType  )
__declspec(  dllexport  )  SUBTITLES_cfg  *  getCurSubtitlesCfg(  int  iSharedObjType,  int  iCapType,  int  iCapSubType  )	
{
	SUBTITLES_cfg	*	pCfg	=	NULL;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	//
#if  0
	if  (  iSharedObjType  ==  CONST_sharedObjType_av  )  pCfg  =  &pProcInfo->subtitles.localVideoInConf;
	else  {
#endif

	//
	switch  (  iCapType  )  {
			case  CONST_capType_av:
				  switch  (  iCapSubType  )  {
						  case  CONST_subCapType_webcam:
								pCfg  =  &pProcInfo->subtitles.webcam;
							    break;
						  default:
							     //pCfg  =  &pProcInfo->subtitles.localVideoInConf;
								 break;
				  }
				  break;
				  //
			case  CONST_capType_mosaic:
				  pCfg  =  &pProcInfo->subtitles.d3dWall;
				  break;
			case  CONST_capType_mediaFile:	//  2014/11/18
			case  CONST_capType_mediaDevice:
				  break;
			case  CONST_capType_screen:		//  2016/02/17
				  break;
			default:
					#ifdef  __DEBUG__
							#if  10
								 traceLog(  _T(  "getCurSubtitlesCfg: not supported captype, %d"  ),  iCapType  );
							#endif
					#endif
					break;
	}
	

	return  pCfg;
}
