
#include	"stdafx.h"
#include	"qyCommon.h"
#include	"qmcDebugStatusInfo.h"
#include	"isCmdConst.h"


void debugStatusInfo_OnIsCmd(  UINT nID,  QY_ENV  *  pEnv,  QMC_debugStatusInfo  *  pDebugStatusInfo  )
{
	QY_ENV  &  env  =  *pEnv;
	QMC_debugStatusInfo  &  debugStatusInfo  =  *pDebugStatusInfo;

	switch  (  nID  )  {
			case  ID_notViewAudioStatus:
				  debugStatusInfo.ucbViewAudioStatus  =  FALSE;
				  break;
			case  ID_viewAudioStatus:
				  env.bDebugInfo  =  TRUE;
				  debugStatusInfo.ucbViewAudioStatus  =  TRUE;
				  break;
			case  ID_notViewVideoStatus:
				  debugStatusInfo.ucbViewVideoStatus  =  FALSE;
				  break;
			case  ID_viewVideoStatus:
				  env.bDebugInfo  =  TRUE;
				  debugStatusInfo.ucbViewVideoStatus  =  TRUE;
				  break;
				  //
			case  ID_notViewFileStatus:
				  debugStatusInfo.ucbViewFileStatus  =  FALSE;
				  break;
			case  ID_viewFileStatus:
				  env.bDebugInfo  =  TRUE;
				  debugStatusInfo.ucbViewFileStatus  =  TRUE;
				  break;
				  //
			case  ID_notViewIoStatus:
				  debugStatusInfo.ucbViewIoStatus  =  FALSE;
				  break;
			case  ID_viewIoStatus:
				  env.bDebugInfo  =  TRUE;
				  debugStatusInfo.ucbViewIoStatus  =  TRUE;
				  break;
			case  ID_notViewMgrStatus:
				  debugStatusInfo.ucbViewMgrStatus  =  FALSE;		//  2017/10/11
				  break;
			case  ID_viewMgrStatus:
				  env.bDebugInfo  =  TRUE;
				  debugStatusInfo.ucbViewMgrStatus  =  TRUE;		//  2017/10/11
				  break;

			case  ID_notPrintAudioMediaType:  {
			
				  debugStatusInfo.ucbPrint_a_mt  =  FALSE;
				  }
				  break;
			case  ID_printAudioMediaType:  {
			
				  debugStatusInfo.ucbPrint_a_mt  =  TRUE;
				  }
				  break;
			case  ID_notShowVideoCapStatus:		{											//  2012/11/11
			
				  debugStatusInfo.ucbShowVideoCapStatus  =  FALSE;
				  }
				  break;
			case  ID_showVideoCapStatus:		{
			
				  debugStatusInfo.ucbShowVideoCapStatus  =  TRUE;
				  }
				  break;
			case  ID_notShowAudioCapStatus:		{
			
				  debugStatusInfo.ucbShowAudioCapStatus  =  FALSE;
				  }
				  break;
			case  ID_showAudioCapStatus:		{
			
				  debugStatusInfo.ucbShowAudioCapStatus  =  TRUE;
				  }
				  break;
			case  ID_notShowPreDrawStatus:  {
			
				  debugStatusInfo.ucbShowPreDrawStatus  =  FALSE;
				  }
				  break;
			case  ID_showPreDrawStatus:  {
			
				  debugStatusInfo.ucbShowPreDrawStatus  =  TRUE;
				  }
				  break;
			case  ID_notShowToDrawStatus:  {
			
				  debugStatusInfo.ucbShowToDrawStatus  =  FALSE;
				  }
				  break;
			case  ID_showToDrawStatus:  {
			
				  debugStatusInfo.ucbShowToDrawStatus  =  TRUE;
				  }
				  break;
			case  ID_notShowRenderStatus:{
			
				  debugStatusInfo.ucbShowRenderStatus  =  FALSE;				  
				  }
				  break;
			case  ID_showRenderStatus:{
			
				  debugStatusInfo.ucbShowRenderStatus  =  TRUE;
				  }
				  break;
			case  ID_notShowPlayAudioStatus:	{											//  2012/11/11
				  
				  debugStatusInfo.ucbShowPlayAudioStatus  =  FALSE;
				  }
				  break;
			case  ID_showPlayAudioStatus:{											//  2012/11/11
				  
				  debugStatusInfo.ucbShowPlayAudioStatus  =  TRUE;
				  }
				  break;

			case  ID_notShowDlgTalkStatus:	{  //  2014/05/07
				  
				  debugStatusInfo.ucbShowDlgTalkStatus  =  FALSE;
				  }
				  break;
			case  ID_showDlgTalkStatus:  {
				  
				  debugStatusInfo.ucbShowDlgTalkStatus  =  TRUE;
				  }
				  break;

			case  ID_notShowVPktInputInfo:  {
				  
				  debugStatusInfo.ucbShowVPktInputInfo  =  FALSE;
				  }
				  break;
			case  ID_showVPktInputInfo:  {
			
				  debugStatusInfo.ucbShowVPktInputInfo  =  TRUE;				  
				  }
				  break;
			case  ID_notPrintRtt:  {
				  
				  debugStatusInfo.ucbPrint_rtt  =  FALSE;
				  }
				  break;
			case  ID_printRtt:  {
				  
				  debugStatusInfo.ucbPrint_rtt  =  TRUE;
				  }
				  break;
			case  ID_notShowOnvifStatus:  {
				  
				  debugStatusInfo.ucbShow_onvif  =  FALSE;
				  }
				  break;
			case  ID_showOnvifStatus:  {
				  
				  debugStatusInfo.ucbShow_onvif  =  TRUE;
				  }
				  break;
			case  ID_notPrintPtz:  {
				  
				  debugStatusInfo.ucbPrint_ptz  =  FALSE;
				  }
				  break;
			case  ID_printPtz:  {
				  
				  debugStatusInfo.ucbPrint_ptz  =  TRUE;
				  }
				  break;
			case  ID_notPrintD3d:  {
				  
				  debugStatusInfo.ucbPrint_d3d  =  FALSE;
				  }
				  break;
			case  ID_printD3d:  {
				  
				  debugStatusInfo.ucbPrint_d3d  =  TRUE;
				  }
				  break;
			case  ID_notShowEncVStatus:  {
			
				  debugStatusInfo.ucbShowEncVStatus  =  FALSE;
				  }
				  break;
			case  ID_showEncVStatus:  {
			
				  debugStatusInfo.ucbShowEncVStatus  =  TRUE;
				  }
				  break;
			case  ID_notShowPreDecAStatus:  {
			
				  debugStatusInfo.ucbShowPreDecAStatus  =  FALSE;
				  }
				  break;
			case  ID_showPreDecAStatus:  {
			
				  debugStatusInfo.ucbShowPreDecAStatus  =  TRUE;
				  }
				  break;
			case  ID_notShowPreDecV_pts:  {
			
				  debugStatusInfo.ucbShowPreDecV_pts  =  FALSE;
				  }
				  break;
			case  ID_showPreDecV_pts:  {
			
				  debugStatusInfo.ucbShowPreDecV_pts  =  TRUE;
				  }
				  break;
			case  ID_notShowPreDecVStatus:  {
			
				  debugStatusInfo.ucbShowPreDecVStatus  =  FALSE;
				  }
				  break;
			case  ID_showPreDecVStatus:  {
			
				  debugStatusInfo.ucbShowPreDecVStatus  =  TRUE;
				  }
				  break;
			case  ID_notShowPostDecVStatus:  {
			
				  debugStatusInfo.ucbShowPostDecVStatus  =  FALSE;
				  }
				  break;
			case  ID_showPostDecVStatus:  {
			
				  debugStatusInfo.ucbShowPostDecVStatus  =  TRUE;
				  }
				  break;


			case  ID_notTestStream:{
				  //
				  debugStatusInfo.ucbShowRtspCliControl  =  FALSE;
				  }
 				  break;
			case  ID_testStream:{
				  //
				  debugStatusInfo.ucbShowRtspCliControl  =  TRUE;				
				  }
 				  break;


			default:
					break;
	}

errLabel:
	return;
}



//	
void  debugStatusInfo_OnUpdateIsCmd(QY_ENV  *  pEnv,  QMC_debugStatusInfo  *  pDebugStatusInfo,  void *pCmdUIParam)
{
	
	CCmdUI  *  pCmdUI  =  (  CCmdUI  *  )pCmdUIParam;

	//
	BOOL				bState		=	TRUE;

	//
	QY_ENV  &env  =  *pEnv;
	QMC_debugStatusInfo  &  debugStatusInfo  =  *pDebugStatusInfo;

	//
	switch  (  pCmdUI->m_nID  )  {
			case  ID_notViewAudioStatus:
 				  if  (  !env.bDebugInfo  ||  !debugStatusInfo.ucbViewAudioStatus  )  bState  =  FALSE;
				  break;
			case  ID_viewAudioStatus:
				  if  (  env.bDebugInfo  &&  debugStatusInfo.ucbViewAudioStatus  )  bState  =  FALSE;
				  break;
			case  ID_notViewVideoStatus:
				  if  (  !env.bDebugInfo  ||  !debugStatusInfo.ucbViewVideoStatus  )  bState  =  FALSE;				  
				  break;
			case  ID_viewVideoStatus:
				  if  (  env.bDebugInfo  &&  debugStatusInfo.ucbViewVideoStatus  )  bState  =  FALSE; 
				  break;

			case  ID_notViewFileStatus:
				  if  (  !env.bDebugInfo  ||  !debugStatusInfo.ucbViewFileStatus  )  bState  =  FALSE;				  
				  break;
			case  ID_viewFileStatus:
				  if  (  env.bDebugInfo  &&  debugStatusInfo.ucbViewFileStatus  )  bState  =  FALSE; 
				  break;

			case  ID_notViewIoStatus:
				  if  (  !env.bDebugInfo  ||  !debugStatusInfo.ucbViewIoStatus  )  bState  =  FALSE;				  
				  break;				  
			case  ID_viewIoStatus:
  				  if  (  env.bDebugInfo  &&  debugStatusInfo.ucbViewIoStatus  )  bState  =  FALSE; 
				  break;

			case  ID_notViewMgrStatus:
				  if  (  !env.bDebugInfo  ||  !debugStatusInfo.ucbViewMgrStatus  )  bState  =  FALSE;
				  break;
			case  ID_viewMgrStatus:
				  if  (  env.bDebugInfo  &&  debugStatusInfo.ucbViewMgrStatus  )  bState  =  FALSE;
				  break;
				  				  //
			case  ID_notPrintAudioMediaType:
				  if  (  !debugStatusInfo.ucbPrint_a_mt  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_printAudioMediaType:
				  if  (  debugStatusInfo.ucbPrint_a_mt  )  pCmdUI->Enable(  FALSE  );
				  break;

#if  10
			case  ID_notShowVideoCapStatus:				//  2012/11/11
				  if  (  !debugStatusInfo.ucbShowVideoCapStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showVideoCapStatus:
				  if  (  debugStatusInfo.ucbShowVideoCapStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notShowAudioCapStatus:
				  if  (  !debugStatusInfo.ucbShowAudioCapStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showAudioCapStatus:
				  if  (  debugStatusInfo.ucbShowAudioCapStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notShowPreDrawStatus:
				  if  (  !debugStatusInfo.ucbShowPreDrawStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showPreDrawStatus:
				  if  (  debugStatusInfo.ucbShowPreDrawStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notShowToDrawStatus:
				  if  (  !debugStatusInfo.ucbShowToDrawStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showToDrawStatus:
				  if  (  debugStatusInfo.ucbShowToDrawStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notShowRenderStatus:
				  if  (  !debugStatusInfo.ucbShowRenderStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showRenderStatus:
				  if  (  debugStatusInfo.ucbShowRenderStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notShowPlayAudioStatus:				//  2012/11/11
				  if  (  !debugStatusInfo.ucbShowPlayAudioStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showPlayAudioStatus:
				  if  (  debugStatusInfo.ucbShowPlayAudioStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notShowDlgTalkStatus:
				  if  (  !debugStatusInfo.ucbShowDlgTalkStatus  )  pCmdUI->Enable(  FALSE  );				  
				  break;
			case  ID_showDlgTalkStatus:
				  if  (  debugStatusInfo.ucbShowDlgTalkStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notShowVPktInputInfo:
				  if  (  !debugStatusInfo.ucbShowVPktInputInfo  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showVPktInputInfo:
				  if  (  debugStatusInfo.ucbShowVPktInputInfo  )  pCmdUI->Enable(  FALSE  );
				  break;				  
			case  ID_notPrintRtt:
				  if  (  !debugStatusInfo.ucbPrint_rtt  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_printRtt:
				  if  (  debugStatusInfo.ucbPrint_rtt  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notShowOnvifStatus:
				  if  (  !debugStatusInfo.ucbShow_onvif  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showOnvifStatus:
				  if  (  debugStatusInfo.ucbShow_onvif  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notPrintPtz:
				  if  (  !debugStatusInfo.ucbPrint_ptz  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_printPtz:
				  if  (  debugStatusInfo.ucbPrint_ptz  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notPrintD3d:
				  if  (  !debugStatusInfo.ucbPrint_d3d  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_printD3d:
				  if  (  debugStatusInfo.ucbPrint_d3d  )  pCmdUI->Enable(  FALSE  );
				  break;
				  
			case  ID_notShowEncVStatus:
				  if  (  !debugStatusInfo.ucbShowEncVStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showEncVStatus:
				  if  (  debugStatusInfo.ucbShowEncVStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notShowPreDecAStatus:
				  if  (  !debugStatusInfo.ucbShowPreDecAStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showPreDecAStatus:
				  if  (  debugStatusInfo.ucbShowPreDecAStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notShowPreDecV_pts:
				  if  (  !debugStatusInfo.ucbShowPreDecV_pts  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showPreDecV_pts:
				  if  (  debugStatusInfo.ucbShowPreDecV_pts  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notShowPreDecVStatus:
				  if  (  !debugStatusInfo.ucbShowPreDecVStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showPreDecVStatus:
				  if  (  debugStatusInfo.ucbShowPreDecVStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_notShowPostDecVStatus:
				  if  (  !debugStatusInfo.ucbShowPostDecVStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_showPostDecVStatus:
				  if  (  debugStatusInfo.ucbShowPostDecVStatus  )  pCmdUI->Enable(  FALSE  );
				  break;
#if 0
			case  ID_notUseDmo:			
				  if  (  !pProcInfo->cfg.ucb__SUPPORT_dmoToDec__  )  pCmdUI->Enable(  FALSE  );
				  break;
			case  ID_useDmo:			
				  if  (  pProcInfo->cfg.ucb__SUPPORT_dmoToDec__  )  pCmdUI->Enable(  FALSE  );
				  break;
#endif
			case  ID_notTestStream:{
				  if  (  !debugStatusInfo.ucbShowRtspCliControl  )  pCmdUI->Enable(  FALSE  );
				  }
 				  break;
			case  ID_testStream:{
				  if  (  debugStatusInfo.ucbShowRtspCliControl  )  pCmdUI->Enable(  FALSE  );
				  }
 				  break;
#endif

			default:
					break;
	}

	if  (  !bState  )  pCmdUI->Enable(  FALSE  );

errLabel:
	return;
}



