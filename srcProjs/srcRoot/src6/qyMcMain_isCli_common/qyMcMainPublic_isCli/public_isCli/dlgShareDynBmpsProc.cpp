

#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>
#include	<stddef.h>


#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

#include	<dbt.h>
#include	<mmreg.h>
#include	<msacm.h>
#ifndef  __WINCE__
	#include	<fcntl.h>
	#include	<io.h>
#endif
#include	<stdio.h>
#include	<commdlg.h>
#include	<strsafe.h>

#include	<dshow.h>

#ifndef  __WINCE__
#pragma include_alias( "dxtrans.h", "myqedit.h" )
#define __IDxtCompositor_INTERFACE_DEFINED__
#define __IDxtAlphaSetter_INTERFACE_DEFINED__
#define __IDxtJpeg_INTERFACE_DEFINED__
#define __IDxtKey_INTERFACE_DEFINED__

	//  #include	<Qedit.h>
	#include	"myQedit.h"
#endif
#include	<Mediaobj.h>
#include	<Dmo.h>

#include	"qmcDmoPublic.h"
#ifndef  __WINCE__
	#include	"qmcVideoCapture_dx.h"
#endif
#include	"myfourcc.h"

#include	"qyCusResTemp.h"

//  #include	"qyMc.h"
#include	"qyGuiCommProc.h"

#include	"tmpCeLib.h"

#include	"qyAvRecordPublic.h"

#include	"myresource.h"

#include	"qyOpenShellCommon.h"
#include	"wallTalkers.h"
#include	"DlgShareDynBmpsProc.h"

#include	"dlgTalkProc.h"
#include	"qmcCmdProc.h"

//  #include	"DlgProgress.h"
#include	"tmpCeLib.h"

#include	"qyComPortEx.h"
#include	"qmcGpsProc.h"

#include	"myDb.h"

#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"qmcCommFunc_isCli.h"

//
#define		MAX_portNo_gps		16

//
 //int  dlgShareDynBmps_sndRetrieveDynBmpsRespToMsgr(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  int  index_recvdReqs  );


 

 //
 int  dlgShareDynBmps_refreshShareStatus(  QY_MC  *  pQyMc,  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType  )
{
	if  (  !pDLG_shareDynBmps_var  )  return  -1;
	DLG_shareDynBmps_var  &  m_var  =  *(  DLG_shareDynBmps_var  *  )pDLG_shareDynBmps_var;

	if  (  !uiObjType  )  {
		dlgShareDynBmps_refreshShareStatus(  pQyMc, m_hWnd,  &m_var,  CONST_objType_screen  );
		dlgShareDynBmps_refreshShareStatus(  pQyMc, m_hWnd,  &m_var,  CONST_objType_webcam  );
		dlgShareDynBmps_refreshShareStatus(  pQyMc, m_hWnd,  &m_var,  CONST_objType_rtspStream  );
		//  2012/04/17
		dlgShareDynBmps_refreshShareStatus_gps(  pQyMc,  m_hWnd,  &m_var  );
		return  0;
	}

	int						iErr		=	-1;
	MC_VAR_isCli			*	pProcInfo	=	QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	int						i;
	int						idc;
	HWND					hCtrl		=	NULL;
	SHARE_dynBmps		*	pShare		=	(  SHARE_dynBmps  *  )dlgShareDynBmps_getShareDynBmpsBySth(  m_hWnd,  &m_var,  uiObjType  );
	//QY_MC				*	pQyMc		=	(  QY_MC  *  )pProcInfo->pQyMc;
	if  (  !pShare  )  return  -1;

	//  2014/06/02
	if  (  uiObjType  ==  CONST_objType_rtspStream  )  {
		for  (  i  =  0;  i  <  pShare->usCnt;  i  ++  )  {
#if  0
			 if  (  !pShare->mems[i].usIndex_obj  )  continue;
			  pShare->mems[i].var.bShared  =  pShare->mems[i].var.ucbLocalVideoOpen;
#endif
			  CHelp_shareDynBmp  help_shareDynBmpMem;
			  SHARE_dyn_bmp  *  pDynBmpMem  =  help_shareDynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  i  );
			  if  (  !pDynBmpMem  )  continue;
			  if  (  !pDynBmpMem->resObj.usIndex_obj  )  continue;
			  //pDynBmpMem->var.bShared  =  pDynBmpMem->var.ucbLocalVideoOpen;
		}
		//
#ifdef  __DEBUG__
		TCHAR  *  pT  =  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_startTesting  );
#endif
		//
		HWND  hCtrl  =  GetDlgItem(  m_hWnd,  m_var.guiData.iIDC_BUTTON_selfTest  );
		if  (  m_var.onvif.selfTest.bSelfTest  )  {
			//  SetWindowText(  hCtrl,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_stopTesting  )  );
		}
		else  {
			  SetWindowText(  hCtrl,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_startTesting  )  );
		}

	}

	//  2015/05/18
	if  (  uiObjType  ==  CONST_objType_webcam  )  {	
		HWND  hCtrl  =  GetDlgItem(  m_hWnd,  m_var.guiData.iIDC_BUTTON_playLocalAudio  );
		if  (  pProcInfo->cfg.ucbPlayLocalAudio_captured  )  {
			SetWindowText(  hCtrl,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_stopPlayingAudio  )  );
			}
		else  {
			  SetWindowText(  hCtrl,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_startPlayingAudio  )  );
		}
	}

	hCtrl  =  GetDlgItem(  m_hWnd,  m_var.guiData.iIDC_BUTTON_hide  );
	SetWindowText(  hCtrl,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_hide  )  );

	hCtrl  =  GetDlgItem(  m_hWnd,  m_var.guiData.iIDCANCAL  );
	SetWindowText(  hCtrl,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_quXiao  )  );	

	hCtrl  =  GetDlgItem(  m_hWnd,  m_var.guiData.iIDC_BUTTON_add  );
	SetWindowText(  hCtrl,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_ADD  )  );

	hCtrl  =  GetDlgItem(  m_hWnd,  m_var.guiData.iIDC_BUTTON_procRtsp  );
	SetWindowText(  hCtrl,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_procRtsp  )  );
	

	hCtrl  =  GetDlgItem(  m_hWnd,  m_var.guiData.iIDC_BUTTON_del  );
	SetWindowText(  hCtrl,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_DEL  )  );

	hCtrl  =  GetDlgItem(  m_hWnd,  m_var.guiData.iIDC_BUTTON_ptz  );
	SetWindowText(  hCtrl,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_ptz  )  );

	hCtrl  =  GetDlgItem(  m_hWnd,  m_var.guiData.iIDC_BUTTON_remoteStorageSettings  );
	SetWindowText(  hCtrl,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_remoteStorage  )  );

	hCtrl  =  GetDlgItem(  m_hWnd,  m_var.guiData.iIDC_CHECK_autoPopupAndHideOnStartup  );
	SetWindowText(  hCtrl,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_autoPopupAndHideOnStartup  )  );


	//
	if  (  pShare->pTable_ctrls  )  {
	 QY_DMITEM  *  pItem;	 
	 for  (  pItem  =  pShare->pTable_ctrls,  i  =  0;  pItem->type  !=  -1  &&  i  <  pShare->usCnt;  pItem  ++  )  {

		 CHelp_shareDynBmp  help_shareDynBmpMem;		
		 SHARE_dyn_bmp  *  pDynBmpMem  =  help_shareDynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  i  );			 
		 if  (  !pDynBmpMem  )  break;;

#if  0
		  if  (  uiObjType  ==  CONST_objType_webcam  )  {
			  if  (  !pShare->mems[i].iMenuId  )  break;
			  pShare->mems[i].var.bShared  =  pShare->mems[i].var.ucbLocalVideoOpen;
			  pShare->mems[i].var.bUsing  =  bWebcamUsing(  pProcInfo,  0,  getMoniker_v(  m_var.pCapStuff,  pShare->mems[i].iMenuId  ),  NULL,  NULL,  NULL  );

		  }
		  else  if  (  uiObjType  ==  CONST_objType_screen  )  {
			  pShare->mems[i].var.bShared  =  pShare->mems[i].var.ucbLocalVideoOpen;
		  }

		  idc  =  (  int  )pItem->pData;
		  hCtrl  =  GetDlgItem(  m_hWnd,  idc  );
		  if  (  !hCtrl  )  goto  errLabel;

		  if  (  pShare->mems[i].var.bUsing  &&  !pShare->mems[i].var.bShared  )  {
			  EnableWindow(  hCtrl,  FALSE  );
			  SetDlgItemText(  m_hWnd,  idc,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_running  )  );
			  }
		  else  {
			    EnableWindow(  hCtrl,  TRUE  );
				if  (  pShare->mems[i].var.bShared  )  SetDlgItemText(  m_hWnd,  idc,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_stopSharing  )  );
				else  SetDlgItemText(  m_hWnd,  idc,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_startSharing  )  );
		  }
#endif
		  
#if  10
		  if  (  uiObjType  ==  CONST_objType_webcam  )  {
			  if  (  !pDynBmpMem->iMenuId  )  break;
			  //pDynBmpMem->var.bShared  =  pDynBmpMem->var.ucbLocalVideoOpen;
			  pDynBmpMem->var.bUsing  =  bWebcamUsing(  pProcInfo,  0,  getMoniker_v(  m_var.pCapStuff1,  pDynBmpMem->iMenuId  ),  NULL,  NULL,  NULL  );

		  }
		  else  if  (  uiObjType  ==  CONST_objType_screen  )  {
			  //pDynBmpMem->var.bShared  =  pDynBmpMem->var.ucbLocalVideoOpen;
		  }

		  idc  =  (  int  )pItem->pData;
		  hCtrl  =  GetDlgItem(  m_hWnd,  idc  );
		  if  (  !hCtrl  )  goto  errLabel;

		  if  (  pDynBmpMem->var.bUsing  &&  !bShared(  pDynBmpMem  )  )  {
			  EnableWindow(  hCtrl,  FALSE  );
			  SetDlgItemText(  m_hWnd,  idc,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_running  )  );
			  }
		  else  {
			    EnableWindow(  hCtrl,  TRUE  );
				if  (  bShared(  pDynBmpMem  )  )  {
					TCHAR  tBuf[128];
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_stopSharing  )  );
					if  (  isAvFlg_unresizable(  pDynBmpMem->var.taskAvProps.v.ucAvFlg  )  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_stopUnresizable  )  );				//  _T(  "Stop (unresizable)"  )  );
					SetDlgItemText(  m_hWnd,  idc,  tBuf  );
					}
				else  {
					  SetDlgItemText(  m_hWnd,  idc,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_startSharing  )  );
				}
		  }


#endif


		  i  ++  ;
	 }
	}
	//  缺少对rtsp的状态刷新


	iErr  =  0;
errLabel:
	return  iErr;
}


int  dlgShareDynBmps_refreshShareStatus_gps(  QY_MC  *  pQyMc,  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var  )
{
	int				iErr	=	-1;
	//QY_MC		*	pQyMc	=	QY_GET_GBUF(  );

	if  (  !pDLG_shareDynBmps_var  )  return  -1;
	DLG_shareDynBmps_var  &m_var  =  *(  DLG_shareDynBmps_var  *  )pDLG_shareDynBmps_var;

	int	idc  =  m_var.guiData.iIDC_BUTTON_gps;

	if  (  m_var.share_gps.bShare  )  SetDlgItemText(  m_hWnd,  idc,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_stopSharing  )  );
	else  SetDlgItemText(  m_hWnd,  idc,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_startSharing  )  );

	iErr  =  0;
	return  iErr;
}





 










 //
  LRESULT  dlgShareDynBmps_OnQyComm( QY_MC  *  pQyMc,  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  WPARAM wParam, LPARAM lParam )
{
	if  (  !pDLG_shareDynBmps_var  )  return  -1;
	DLG_shareDynBmps_var  &  m_var  =  *(  DLG_shareDynBmps_var  *  )pDLG_shareDynBmps_var;


	long				lRet				=					-1;
	QY_WMBUF_COMM	*	pComm				=					( QY_WMBUF_COMM * )lParam;
	//QY_MC			*	pQyMc				=					QY_GET_GBUF(  );
	int					i					=					0;
	int					j					=					0;
	MC_VAR_isCli	*	pProcInfo			=					QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;

	QY_DMITEM	*	pTable				=					getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );


	if  (  !pComm  )  return  -1;

	switch  (  pComm->uiType  )  {
			case  CONST_misMsgType_procVideo_qmc:  {
				  MIS_MSG_procVideo_qmc  *  pMsg			=  (  MIS_MSG_procVideo_qmc  *  )pComm;
				  BOOL						bUseDxSurface	=	m_var.bUseDirectX;	
				  ZONE_PARAM			*	pZoneParam		=	NULL;

#if  0
				  {
				  QY_PLAYER				*	pPlayer;

				  if  (  pMsg->index_player  <  0  ||  pMsg->index_player  >=  pProcInfo->av.usCnt_players  )  goto  errLabel;
				  pPlayer  =  &pProcInfo->av.pPlayers[pMsg->index_player];
				  pZoneParam  =  &pPlayer->video.m_var.zoneParam;
				  }
#endif
				  BOOL	bExists  =  FALSE;
				  for  (  i  =  0;  !bExists  &&  i  <  mycountof(  m_var.shares  );  i  ++  )  {
					   SHARE_dynBmps  *  pShare  =  &m_var.shares[i];
					   for  (  j  =  0;  j  <  pShare->usCnt;  j  ++  )  {
						    //CHelp_shareDynBmp  help_dynBmpMem;
						    SHARE_dyn_bmp  *  pMem  =  &pShare->mems_internal[j];	//  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  pShare->uiObjType,  j  );	//&m_var.shares[i].mems[j];							
							if  (  bShared(  pMem  )  &&  pMem->var.iTaskId  ==  pMsg->iTaskId  )  {
								pZoneParam  =  &pMem->var.zoneParam;
								bExists  =  TRUE;
								break;
							}
					   }
				  }
				  if  (  !pZoneParam  )  {
					  #ifdef  __DEBUG__
							  traceLog((TCHAR*)  _T(  "dlgShareQynBmps, OnQyPostComm failed, pZoneParam is null"  )  );
					  #endif
					  goto  errLabel;
				  }
				  						
				  BOOL			bZoneOk		=	FALSE;				  
				  if  (  pZoneParam->index_capImage  >=  0  &&  pZoneParam->index_capImage  <  mycountof(  m_var.images.mems  )  )  {
					  CAP_IMAGE	*	pImg	=	&m_var.images.mems[pZoneParam->index_capImage];
					  if  (  pImg->idInfo_sender.ui64Id  ==  pMsg->idInfo_sender.ui64Id  
						  &&  pImg->uiTranNo_openAvDev  ==  pMsg->uiTranNo_openAvDev
						  &&  pImg->usIndex_activeMems_from  ==  pMsg->usIndex  )  
					  {
						  bZoneOk  =  TRUE;
					  }
				  }											   
				  //				
				  //  if  (  !bZoneOk  )  freeCapImages(  this,  m_var.idc,  NULL,  &m_var.images  );
				  if  (  !bZoneOk  )  {							
					  memset(  pZoneParam,  0,  sizeof(  pZoneParam[0]  )  );
					  //					  
					  BOOL	bExists  =  FALSE;
					  for  (  i  =  0;  !bExists  &&  i  <  mycountof(  m_var.shares  );  i  ++  )  {
						   SHARE_dynBmps  *  pShare  =  &m_var.shares[i];
						   for  (  j  =  0;  j  <  pShare->usCnt;  j  ++  )  {
							    //CHelp_shareDynBmp  help_dynBmpMem;
								SHARE_dyn_bmp  *  pMem  =  &pShare->mems_internal[j];	//  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  pShare->uiObjType,  j  );	//  &m_var.shares[i].mems[j];					
								if  (  bShared(  pMem  )  &&  pMem->var.iTaskId  ==  pMsg->iTaskId  )  {
									bExists  =  TRUE;
									break;
								}
						   }
					  }	
					  if  (  !bExists  )  goto  errLabel;				  					  
				  }
				  //  if  (  drawCapImages(  m_hWnd,  m_var.idc,  &m_var.hDc,  NULL,  FALSE,  m_var.ucbAutoClip,  pMsg,  0,  0,  m_var.iW_pic,  m_var.iH_pic,  NULL,  pZoneParam,  &m_var.images,  bUseDxSurface,  FALSE  )  )  goto  errLabel;
				  HWND  hWnd_src = m_var.hWndIDC;// old_M_GetDlgItem(m_hWnd, m_var.idc);
				  HWND  hWnd_dst  =  hWnd_src;
				  if  (  drawCapImages(  pQyMc,  hWnd_src,  m_var.ucbAutoClip,  pMsg,  0,  0,  m_var.iW_pic,  m_var.iH_pic,  NULL,  pZoneParam,  &m_var.images,  hWnd_dst,  &m_var.hDc,  NULL  )  )  goto  errLabel;

				  }				  
				  break;
			case  CONST_misMsgType_input:  {
				  MIS_MSG_INPUT		*	pMsg		=	(  MIS_MSG_INPUT  *  )pComm;
				  //  IM_CONTENTU		*	pContent	=	(  IM_CONTENTU  *  )&pMsg->data;
				  IM_CONTENTU			*	pContent	=	M_getMsgContent(  pMsg->ucFlg,  &pMsg->data  );									 
				  
				  switch  (  pContent->uiType  )  {
						  case  CONST_imCommType_refreshDynBmps:
							    if  (  pContent->refreshDynBmps.ucbResp  )  {
									m_var.tLastModifiedTime_ok  =  pContent->refreshDynBmps.tLastModifiedTime;
								}
							    break;
						  case  CONST_imCommType_verifyViewDynBmp:  
								//
							    procVerifyViewDynBmpResp(  m_hWnd,  &m_var,  pMsg  );
							    //
							    break;
						  case  CONST_imCommType_retrieveDynBmps:
								#ifdef  __DEBUG__
										  traceLog((TCHAR*)  _T(  "dlgShareDynBmps_OnQyComm: retrieveDynBmps"  )  );
								#endif
								//
								procRetrieveDynBmpsReq(  m_hWnd,  &m_var,  pMsg  );
								//
							    break;
						  default:
								  #ifdef  __DEBUG__
										  traceLog((TCHAR*)  _T(  "dlgShareDynBmps_OnQyComm: unprocessed content %d"  ),  pContent->uiType  );
								  #endif
								  break;
				  }
										
				  }
				  break;
			case  CONST_misMsgType_task:  {
				  MIS_MSG_TASK		*	pMsg		=	(  MIS_MSG_TASK  *  )pComm;
				  IM_CONTENTU		*	pContent	=	(  IM_CONTENTU  *  )&pMsg->data.buf;
				  SHARE_dynBmps		*	pShare		=	NULL;

				  switch  (  pContent->uiType  )  {
					      case  CONST_imCommType_transferAvInfo:
							    unsigned  int  uiObjType;  uiObjType  =  pContent->transferAvInfo.ass.resObj.uiObjType;	//  2014/11/01
								pShare  =  (  SHARE_dynBmps  * )dlgShareDynBmps_getShareDynBmpsBySth(  m_hWnd,  &m_var,  pContent->transferAvInfo.ass.resObj.uiObjType  );
								if  (  !pShare  )  {
									#ifdef  __DEBUG__
											traceLog((TCHAR*)  _T(  "dlgShareDynBmps_OnQyComm failed: task.transferAvInfo.getShare is null, uiObjType %d"  ),  pContent->transferAvInfo.ass.resObj.uiObjType  );
									#endif
									goto  errLabel;							    
								}

								//  2014/08/04
								unsigned  char  ucbSaveVideo_reply;  ucbSaveVideo_reply  =  FALSE;
								if  (  pContent->transferAvInfo.viewDynBmp.ucbSaveVideo  )  {
									if  (  !canPeerSaveVideo(  m_hWnd,  &m_var,  &pMsg->data.route.idInfo_from  )  )  {
										goto  errLabel;  
									}
									//  2014/09/07
									ucbSaveVideo_reply  =  TRUE;
								}


								//  2014/06/02
								int  tmp_uiObjType_req;  tmp_uiObjType_req  =  pContent->transferAvInfo.ass.resObj.uiObjType;
								int  tmp_usIndex_obj_req;  tmp_usIndex_obj_req  =  pContent->transferAvInfo.ass.resObj.usIndex_obj;
								if  (  tmp_uiObjType_req  ==  CONST_objType_rtspStream  )  {
									//
									if  (  !tmp_usIndex_obj_req  )  {  //  usIndex_obj为0时的处理，
										  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp: viewRtsp failed, usIndex_obj 0, not supported"  )  );										  
										  goto  errLabel;
									}
									
									//										
									for  (  i  =  0;  i  <  mycountof(  m_var.onvif.ipDevsInfo.mems  );  i  ++  )  {
										if  (  m_var.onvif.ipDevsInfo.mems[i].rule.usIndex_obj  ==  tmp_usIndex_obj_req  )  break;										
									}
									if  (  i  ==  mycountof(  m_var.onvif.ipDevsInfo.mems  )  )  {
											#ifdef  __DEBUG__
													traceLog((TCHAR*)  _T(  "no matched dynBmp"  )  );
											#endif
											//
											qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp: no matched dynBmp [%d,%d]"  ),  pContent->transferAvInfo.ass.resObj.uiObjType,  (  int  )pContent->transferAvInfo.ass.resObj.usIndex_obj  );										  
											goto  errLabel;									
									}

									//
										
									}
								else  {
								
									//  i  =  pContent->transferAvInfo.viewDynBmp.usIndex_obj;			
									CHelp_shareDynBmp  help_dynBmpMem;
									i  =  help_dynBmpMem.getIndexByIndex_obj(  m_hWnd,  &m_var,  uiObjType,  pContent->transferAvInfo.ass.resObj.usIndex_obj,  pContent->transferAvInfo.ass.resObj.usHelp_subIndex  );
									if  (  i  <  0  )  {
										#ifdef  __DEBUG__
												traceLog((TCHAR*)  _T(  "no matched dynBmp"  )  );
										#endif
										//
										qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp: no matched dynBmp [%d,%d]"  ),  pContent->transferAvInfo.ass.resObj.uiObjType,  (  int  )pContent->transferAvInfo.ass.resObj.usIndex_obj  );										  
										goto  errLabel;
									}
									SHARE_dyn_bmp  *  pDynBmpMem  =  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  i  );
									if  (  !pDynBmpMem  )  goto  errLabel;
									if  (  !bShared(  pDynBmpMem  )  )  {
										#ifdef  __DEBUG__
												traceLogA(  (char*)"Need to return status_stopped."  );
										#endif
										//
										qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp: skipped, the dynBmp [%d,%d] not shared "  ),  pContent->transferAvInfo.ass.resObj.uiObjType,  (  int  )pContent->transferAvInfo.ass.resObj.usIndex_obj  );										  
										break;
									}								
									

								}


								//
								int  index_store;  index_store  =  0;
								if  (  storeRecvdReq(  m_hWnd,  &m_var,  (  MIS_MSGU  *  )pMsg,  ucbSaveVideo_reply,  &index_store  )  )  goto  errLabel;



								MACRO_prepareForTran(  );
								VERIFY_viewDynBmp	req;
								int					len;

								memset(  &req,  0,  sizeof(  req  )  );
								req.uiType  =  CONST_imCommType_verifyViewDynBmp;

								req.idInfo_viewer.ui64Id  =  pMsg->addr_logicalPeer.idInfo.ui64Id;

								len  =  sizeof(  req  );
								//
								postMsg2Mgr_mc(  m_var.pMisCnt,  NULL,  CONST_misMsgType_req,  0,   CONST_qyCmd_sendVDevReq,  tStartTran,  uiTranNo,  0,  (  char  *  )&req,  len,  NULL,  0,  0,  NULL,  0  ); 

								TCHAR  tBuf[128];
								_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "sharedDynBmp: to verifyViewer %I64u. index_store %d"  ),  req.idInfo_viewer.ui64Id,  index_store  );
								_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. for req(%s, %d)"  ),  tBuf,  qyGetDesByType1(  pTable,  tmp_uiObjType_req  ),  (  int  )tmp_usIndex_obj_req  );

								qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );

								//
							    break;
						  case  CONST_imCommType_taskProcReq:

							    //
   								#if  1	
									#ifdef  __DEBUG__
											traceLog((TCHAR*)  _T(  "Note: shareDynBmp not finished"  )  );
									#endif
									qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Note: sharedDynBmp: not finished. try to removeFromMsgrs_sendLocalAv"  )  );
									goto  errLabel;
								#endif

#if  0  //  2014/08/28
							    unsigned  int  uiObjType  =  0;
								uiObjType  =  pContent->taskProcReq.viewDynBmp.uiObjType;
							    pShare  =  (  SHARE_dynBmps  *  )dlgShareDynBmps_getShareDynBmpsBySth(  m_hWnd,  &m_var,  uiObjType  );
								if  (  !pShare  )  goto  errLabel;							    							


								if  (  pContent->taskProcReq.viewDynBmp.usIndex_obj  >=  pShare->usCnt  )  {
#ifndef  __DEBUG__
		 //  serious error
#endif
									goto  errLabel;
								}
								i  =  pContent->taskProcReq.viewDynBmp.usIndex_obj;
								if  (  !pShare->mems[i].var.bUsing  ||  !pShare->mems[i].var.bShared  )  {									
									traceLogA(  "not shared."  );
									break;
								}
								QY_SHARED_OBJ	*	pSharedObj;
								pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pShare->mems[i].var.iIndex_sharedObj  );
								if  (  !pSharedObj  )  goto  errLabel;
								removeFromMsgrs_sendLocalAv(  pProcInfo,  m_var.pMisCnt,  &pMsg->data.route.idInfo_from,  pSharedObj  );
								qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp: removeFromMsgrs_sendLocalAv, %I64u"  ),  pMsg->data.route.idInfo_from.ui64Id  );

#endif

							    break;

								//  
						  case  CONST_imCommType_transferGpsInfo:	{  //  2012/04/20
							    if  (  !m_var.share_gps.bShare  )  {
								    #ifdef  __DEBUG__
											traceLog((TCHAR*)  _T(  "dlgShare: gps is not shared"  )  );
									#endif
									goto  errLabel;
								}

								//  2011/10/31. 不直接发送响应包，因为要发送到服务器上去校验下

								DWORD  dwTickCnt_cur;  dwTickCnt_cur	=	GetTickCount(  );
								for  (  j  =  0;  j  <  mycountof(  m_var.recvdReqs  );  j  ++  )  {
									 if  (  !m_var.recvdReqs[j].dwTickCnt  )  break;
									 if  (  m_var.recvdReqs[j].pMsg->task.addr_logicalPeer.idInfo.ui64Id  ==  pMsg->addr_logicalPeer.idInfo.ui64Id  )  {
										 #ifdef  __DEBUG__
												 traceLog((TCHAR*)  _T(  "recv req again"  )  );
										 #endif
										 break;
									 }
									 if  (  dwTickCnt_cur  -  m_var.recvdReqs[j].dwTickCnt  >  5000  )  {
										 m_var.recvdReqs[j].dwTickCnt  =  0;		//  将dwTickCnt设为0，表明该buf已经回收了
										 break;
									 }
								}
								if  (  j  ==  mycountof(  m_var.recvdReqs  )  )  {
									#ifdef  __DEBUG__
											traceLog((TCHAR*)  _T(  "no recvdReqBuf available"  )  );
									#endif
									qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp: warning: no recvdReqBuf available"  )  );
									goto  errLabel;
								}
								if  (  !m_var.recvdReqs[j].dwTickCnt  )  {		//  只有dwTickCnt为0的包才表明是要填充的
									memcpy(  m_var.recvdReqs[j].pMsg,  pMsg,  sizeof(  pMsg[0]  )  );
									//  2014/05/06
									memset(  &m_var.recvdReqs[j].info,  0,  sizeof(  m_var.recvdReqs[j].info  )  );
									//
									//m_var.recvdReqs[j].info.uiObjType  =  0;
									//m_var.recvdReqs[j].info.index_pShare_mem  =  0;
									m_var.recvdReqs[j].dwTickCnt  =  dwTickCnt_cur;
								}

								MACRO_prepareForTran(  );
								VERIFY_viewDynBmp	req;
								int					len;

								memset(  &req,  0,  sizeof(  req  )  );
								req.uiType  =  CONST_imCommType_verifyViewDynBmp;

								req.idInfo_viewer.ui64Id  =  pMsg->addr_logicalPeer.idInfo.ui64Id;

								len  =  sizeof(  req  );
								//
								postMsg2Mgr_mc(  m_var.pMisCnt,  NULL,  CONST_misMsgType_req,  0,   CONST_qyCmd_sendVDevReq,  tStartTran,  uiTranNo,  0,  (  char  *  )&req,  len,  NULL,  0,  0,  NULL,  0  ); 

								qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp: to verifyViewer %I64u. j %d"  ),  req.idInfo_viewer.ui64Id,  j  );

								//
								}
							    break;

								//
						  case  CONST_imCommType_ptzControlCmd:  {
								#ifdef  __DEBUG__
								#endif
							    //
							  	CHelp_shareDynBmp  help_dynBmpMem;
								SHARE_dyn_bmp  *  pMem  =  NULL;
								
								//
								unsigned  int  uiObjType  =  pContent->ptzControlCmd.cmdInfo.obj.uiObjType;
								unsigned  short  usIndex_obj  =  pContent->ptzControlCmd.cmdInfo.obj.usIndex_obj;
								unsigned  short  usHelp_subIndex  =  pContent->ptzControlCmd.cmdInfo.obj.usHelp_subIndex;	//  2016/07/24
								
								//
								i  =  help_dynBmpMem.getIndexByIndex_obj(  m_hWnd,  &m_var,  uiObjType,  usIndex_obj,  usHelp_subIndex  );
								if  (  i  <  0  )  {
									showInfo_open0(  0,  0,  _T(  "ptz can't be used if video of the device is not alive"  )  );
									goto  errLabel;	
								}
								
								pMem  =  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  i  );	
								if  (  !pMem  )  {
									#ifdef  __DEBUG__
											traceLog((TCHAR*)  _T(  "getMemByIndex failed"  )  );
									#endif
									goto  errLabel;	
								}

								PARAM_viewLocalPtzControl  param  =  {0};
								//
								param.pf_dlg_YTCmd  =  dlg_YTCmd_shareDynBmps;
								//
								param.p0  =  &m_var;
								//
							    QIS_ptz_wnd  *  pPtzWnd  =  &pMem->ptzWnd;
								//
								doRemotePtzCmd(  0,  &pContent->ptzControlCmd,  &param,  pPtzWnd  );
								}
							    break;
								//
						  default:
								  #ifdef  __DEBUG__
										  traceLog((TCHAR*)  _T(  "dlgShare, unprocessed contentType"  )  );
								  #endif
								  break;
				  }
				
				  }
				  break;
			case  CONST_qyWmParam_chkTask:  {
				  BOOL	bExists  =  FALSE;
				  for  (  i  =  0;  !bExists  &&  i  <  mycountof(  m_var.shares  );  i  ++  )  {
					   SHARE_dynBmps  *  pShare  =  &m_var.shares[i];
					   for  (  j  =  0;  j  <  pShare->usCnt;  j  ++  )  {
						    //CHelp_shareDynBmp  help_dynBmpMem;
							SHARE_dyn_bmp  *  pMem  =  &pShare->mems_internal[j];	//  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  pShare->uiObjType,  j  );	//  &m_var.shares[i].mems[j];
							if  (  !pMem  )  goto  errLabel;
							if  (  bShared(  pMem  )  &&  pMem->var.iTaskId  ==  pComm->u.chkTask.iTaskId  )  {
								//  task is active
								bExists  =  TRUE;
								break;
							}
					   }
				  }
				  //  2012/04/19
				  if  (  !bExists  )  {
					  if  (  m_var.share_gps.bShare  )  {
						  if  (  m_var.share_gps.var.iTaskId  ==  pComm->u.chkTask.iTaskId  )  {
							  //  task is active;
							  bExists  =  TRUE;
						  }
					  }
				  }
				  //
				  if  (  !bExists  )  pComm->u.chkTask.bNotExists  =  TRUE;
				  pComm->u.chkTask.bChked  =  TRUE;		//  2013/03/07
				  }
				  break;
			case  CONST_qyWmParam_chkSharedObject:  {
				  BOOL  bExists  =  FALSE;
				  for  (  i  =  0;  !bExists  &&  i  <  mycountof(  m_var.shares  );  i  ++  )  {
					   SHARE_dynBmps  *  pShare  =  &m_var.shares[i];
					   for  (  j  =  0;  j  <  pShare->usCnt;  j  ++  )  {
						    //CHelp_shareDynBmp  help_dynBmpMem;
							SHARE_dyn_bmp  *  pMem  =  &pShare->mems_internal[j];	//  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  pShare->uiObjType,  j  );	//  &m_var.shares[i].mems[j];
							if  (  !pMem  )  goto  errLabel;
							if  (  bShared(  pMem  )  &&  pMem->var.iIndex_sharedObj  ==  pComm->u.chkSharedObject.iIndex_sharedObject  )  {
								//  sharedObj is in use
								bExists  =  TRUE;
								break;
							}
							//  2014/09/11
							if  (  pMem->var.ucbLocalVideoOpen  &&  pMem->var.iIndex_sharedObj  ==  pComm->u.chkSharedObject.iIndex_sharedObject  )  {
								bExists  =  TRUE;
								break;
							}
							//  2014/09/11
							if  (  pMem->var.ucbUsed_iIndex_sharedObj  &&  pMem->var.iIndex_sharedObj  ==  pComm->u.chkSharedObject.iIndex_sharedObject  )  {
								bExists  =  TRUE;
								break;
							}

					   }
				  }
				  //  2012/04/19
				  if  (  !bExists  )  {
					  if  (  m_var.share_gps.bShare  )  {
						  if  (  m_var.share_gps.var.iIndex_sharedObj  ==  pComm->u.chkSharedObject.iIndex_sharedObject  )  {
							  //
							  bExists  =  TRUE;
						  }
					  }
				  }
				  //
				  if  (  !bExists  )  pComm->u.chkSharedObject.bNotExists  =  TRUE;
				  }
				  break;
#if  0
			case  CONST_qyWmParam_getCapImageInfo:  {
				  BOOL	bExists  =  FALSE;
				  for  (  i  =  0;  !bExists  &&  i  <  mycountof(  m_var.shares  );  i  ++  )  {
					   for  (  j  =  0;  j  <  m_var.shares[i].usCnt;  j  ++  )  {
						    SHARE_dyn_bmp  *  pMem  =  &m_var.shares[i].mems[j];
							if  (  pMem->var.bShared  &&  pMem->var.iTaskId  ==  pComm->u.getCapImageInfo.iTaskId  )  {
								bExists  =  TRUE;
							    break;
							}
					   }
				  }	
				  if  (  !bExists  )  {
					  pComm->u.getCapImageInfo.bImageInvalid  =  TRUE;
					  break;
				  }
				  }
				  break;
#endif
			default:
					break;
	}

	lRet  =  QY_RC_WMOK;

errLabel:

	return  lRet;
}

LRESULT  dlgShareDynBmps_OnQyPostComm( QY_MC  *  pQyMc,  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  WPARAM wParam, LPARAM lParam )
{
	if  (  !pDLG_shareDynBmps_var  )  return  -1;
	DLG_shareDynBmps_var  &  m_var  =  *(  DLG_shareDynBmps_var  *  )pDLG_shareDynBmps_var;

	long				lRet			=		-1;
	//QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;

	switch  (  wParam  )  {
			case  CONST_qyWmParam_guiMsgArrive:  
				  doWnd_guiMsgArrive(  pProcInfo,  lParam,  m_hWnd,  TRUE,  m_var.pMsgBuf_doWnd_guiMsgArrive  );
				  break;
				  			
			case  CONST_qyWmParam_avRecord_start:  {				  
				  int						iIndex_sharedObj;
				  int						iIndex_sharedObjUsr		=	0;
				  QY_SHARED_OBJ			*	pSharedObj				=	NULL;
				  int						iIndex_screenCapProcInfo;
				  CAP_procInfo_screen	*	pScreenCapProcInfo		=	NULL;
				  COMPRESS_VIDEO		*	pCompressVideo			=	NULL;
				  unsigned  int				uiTaskType;
				  //
				  CHelp_shareDynBmp		help_dynBmpMem;
				  SHARE_dyn_bmp		*	pDynBmpMem  =  NULL;

				  OutputDebugString(  _T(  "avRecord_start\n"  )  );

				  iIndex_sharedObj  =  newSharedObjIndex(  pProcInfo,  m_hWnd,  0,  &iIndex_sharedObjUsr,  NULL  );
				  if  (  iIndex_sharedObj  <  0  )  goto  errLabel;
				  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
				  if  (  !pSharedObj  )  goto  errLabel;
				  iIndex_screenCapProcInfo  =  newCapProcInfoBmpIndex(  pProcInfo,  iIndex_sharedObj  );	
				  pScreenCapProcInfo  =  (  CAP_procInfo_screen  *  )getCapBmpBySth(  pProcInfo,  iIndex_screenCapProcInfo,  0  );
				  if  (  !pScreenCapProcInfo  )  goto  errLabel;
				  pScreenCapProcInfo->uiType  =  CONST_capType_screen;
				  pScreenCapProcInfo->iIndex_sharedObj  =  iIndex_sharedObj;
				  pScreenCapProcInfo->uiTranNo_sharedObj  =  pSharedObj->uiTranNo;
				  pCompressVideo  =  &pScreenCapProcInfo->compressVideo;
				  
				  //
				  pSharedObj->bDirectX  =  bDirectX_avRecord(  );
				  pSharedObj->bRemoteAssist  =  bRemoteAssist_avRecord(  );		//  2008/11/09, ÊÇ·ñÔ¶³ÌÐ­Öú				
				  pSharedObj->iIndex_capBmp  =  iIndex_screenCapProcInfo;
				  int  iIndex_dynBmp  =  getiParam_avRecord(  );
				  

				  //  2015/10/11  //  2014/04/19
				  if  (  newstartQThreadToShareAv(  pProcInfo,  iIndex_sharedObj,  FALSE  )  )  {
						  goto  errLabel;									  
				  }			

				  //
				  uiTaskType  =  CONST_imTaskType_shareDynBmp;

				  //
				  unsigned  int  uiObjType  =  CONST_objType_screen;
				  SHARE_dynBmps	*	pShare  =  (  SHARE_dynBmps  *  )dlgShareDynBmps_getShareDynBmpsBySth(  m_hWnd,  &m_var,  CONST_objType_screen  );
				  if  (  !pShare  )  goto  errLabel;
				  if  (  iIndex_dynBmp  <  0  ||  iIndex_dynBmp  >=  pShare->usCnt  )  goto  errLabel;
				  //
				  pDynBmpMem  =  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  iIndex_dynBmp  );
				  if  (  !pDynBmpMem  )  goto  errLabel;
				  //
				  pDynBmpMem->var.iIndex_sharedObj  =  iIndex_sharedObj;
				  pDynBmpMem->var.ucbLocalVideoOpen  =  TRUE;	

				  //  2011/08/07
				  #if  0
						POLICY_av	policyAv;
						if  (  getPolicyAv(  FALSE,  0,  &policyAv  )  )  goto  errLabel;
				  #endif
				  AV_COMPRESSOR_CFG		screenCompressor;
				  if  (  myGetAvCompressorCfg(  CONST_capType_screen,  0,  0,  0,  &screenCompressor  )  )  goto  errLabel;

				  //
				  RECT	selectedRc;		//  ÕâÀïÒª×¢Òâ£ºbmp¿í¶ÈÊÇselectedRcµÄ¿í¶È+1¡£³¤¶ÈÒ²ÊÇÈç´Ë¡£

				  selectedRc  =  getSelectedRect(  );				  
				  //  makeBmpInfoHeader_rgb(  24,  selectedRc.right  -  selectedRc.left  +  1,  selectedRc.bottom  -  selectedRc.top  +  1,  &pCompressVideo->vh_decompress.bih  );
				  makeBmpInfoHeader_rgb(  24,  selectedRc.right  -  selectedRc.left  +  1,  selectedRc.bottom  -  selectedRc.top  +  1,  &pScreenCapProcInfo->vh_org.bih  );
				  //  2014/04/19
				  //memcpy(  &pScreenCapProcInfo->vh_org.bih,  &pCompressVideo->vh_decompress.bih,  sizeof(  pScreenCapProcInfo->vh_org  )  );
				  //  2014/04/05
				  screenCompressor.video.common.pVideoQ2  =  &pScreenCapProcInfo->thread.q2;
				  screenCompressor.video.common.pParent_transform  =  pScreenCapProcInfo;
				  //
				  if  (  initCompressVideo(  pProcInfo,  (  BITMAPINFO  *  )&pScreenCapProcInfo->vh_org.bih,  CONST_capType_screen,  &screenCompressor.video,  FALSE,  getSize_qyAvRecord(  ),  pCompressVideo  )  )  {
					  //  qyShowHint(  _T(  "Initialize video compress failed!"  )  );  
					  showNotification(  NULL,  0,  0,  0,  0,  0,  _T(  "Initialize video compress failed!"  )  );  
					  goto  errLabel;
				  }
				  //  2017/06/12
				  pDynBmpMem->usW  =  pScreenCapProcInfo->vh_org.bih.biWidth;
				  pDynBmpMem->usH  =  pScreenCapProcInfo->vh_org.bih.biHeight;
				  				  
				  //
				  TALKER_dynBmp	rule_dynBmp;
				  //  QIS_dynBmp_info	dynBmp;
				  memset(  &rule_dynBmp,  0,  sizeof(  rule_dynBmp  )   );
				  rule_dynBmp.uiType1  =  CONST_talkerObjType_dynBmp;
				  rule_dynBmp.dynBmpRule.dynBmp.resObj.uiObjType  =  uiObjType;
				  rule_dynBmp.dynBmpRule.dynBmp.resObj.usIndex_obj  =  pDynBmpMem->resObj.usIndex_obj;	//  pShare->mems[iIndex_dynBmp].usIndex_obj;	//  2014/05/31
				  //
				  int  tmp_iTaskId  =  0;  //  2014/10/29
				  {
					  void * pDb=NULL;
					  CQnmDb db;
					  if(!db.getAvailableDb(pQyMc->iDsnIndex_mainSys))goto errLabel;
					  pDb=db.m_pDbMem->pDb;
					  tmp_iTaskId=newTaskId(pDb,pQyMc->cfg.db.iDbType);
				  }
				  //
				  PARAM_startAvCall param = { 0 };
				  if  (  procSendAvInfo(  m_var.pMisCnt,  m_hWnd,  FALSE,  uiTaskType,  &param, pCompressVideo,  NULL,  iIndex_sharedObj,  iIndex_sharedObjUsr,  &rule_dynBmp,  NULL,  &tmp_iTaskId,  NULL,  NULL  )  )  goto  errLabel;
				  pDynBmpMem->var.iTaskId  =  tmp_iTaskId;
				  
				  //  »¹ÒªÆô¶¯av
				  setFps_capScreen(  screenCompressor.video.common.usMaxFps_toShareBmp  );
				  startAvRecord(  pProcInfo,  iIndex_screenCapProcInfo,  pQyMc->gui.hMainWnd  );
				  
				  //  2010/09/09
				  setCurSharedObjUsr(  pProcInfo,  iIndex_sharedObj, iIndex_sharedObjUsr);
				  
				  //
				  mytime(  &m_var.tLastModifiedTime  );

				  dlgShareDynBmps_refreshShareStatus(  pQyMc,  m_hWnd,  &m_var,  CONST_objType_screen  );

				  }
				  break;

			case  CONST_qyWmParam_gps:  {
				  CComPortEx  *  pPort  =  (  CComPortEx  *  )m_var.pComPort_gps;
				  if  (  !pPort  )  goto  errLabel;
				  //
				  if  (  pPort->m_var.dwTickCnt_modified_gpsPos  ==  m_var.share_gps.var.dwTickCnt_modified_gpsPos  )  break;
				  if  (  getGpsPos(  pPort,  &m_var.share_gps.var.gpsPos,  &m_var.share_gps.var.dwTickCnt_modified_gpsPos  )  )  goto  errLabel;
				  //
				  TCHAR	tBuf[256]  =  _T(  ""  );
				  if  (  pProcInfo->cfg.ucbTestGps  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Test: "  )  );
				  gps_DisplayStr(  &m_var.share_gps.var.gpsPos,  tBuf  +  lstrlen(  tBuf  ),  mycountof(  tBuf  )  -  lstrlen(  tBuf  )  );
				  SetDlgItemText(  m_hWnd,  m_var.guiData.iIDC_STATIC_gpsStatus,  tBuf  );

				  }
				  //
				  break;

			default:
					break;
	}
	
errLabel:

	return  lRet;

}

 int  dlgShareDynBmps_chkTask(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  int  iTaskId  )
{
	if  (  !pDLG_shareDynBmps_var  )  return  -1;
	DLG_shareDynBmps_var  &  m_var  =  *(  DLG_shareDynBmps_var  *  )pDLG_shareDynBmps_var;

	int				iErr		=	-1;
	MC_VAR_isCli  *  pProcInfo	=	QY_GET_procInfo_isCli(  );

	//  int				i;
	int					j;
	//QY_SHARED_OBJ	*	pSharedObj;
	time_t				t;				mytime(  &t  );

#ifndef  __DEBUG__
	//if  (  !(  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  )  )  )  goto  errLabel;
	int  index_taskInfo  =  getQmcTaskInfoIndexBySth(  pProcInfo,  iTaskId  );
	QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )getQmcTaskInfoByIndex(  pProcInfo,  index_taskInfo  );
	if  (  !pTaskInfo  )  goto  errLabel;

	if  (  pTaskInfo->var.curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id  )  {
		iErr  =  0;  goto  errLabel;
	}
	
	if  (  pTaskInfo->var.curRoute_sendLocalAv.route.idInfo_to.ui64Id  )  {
		if  (  t  -  pTaskInfo->var.curRoute_sendLocalAv.routeInfo.tModifiedTime  >  120  
			&&  t  -  pTaskInfo->var.curRoute_sendLocalAv.routeInfo.tRecvTime_lastResp  >  300  )  
		{				
			removeFromMsgrs_sendLocalAv(  pProcInfo,  m_var.pMisCnt,  &pTaskInfo->var.curRoute_sendLocalAv.route.idInfo_to,  &pTaskInfo->var.curRoute_sendLocalAv, false,  _T(  "dlgShareDynBmps_chkTask.952"  ));
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp: removeFromMsgrs_sendLocalAv, %I64u"  ),  pTaskInfo->var.curRoute_sendLocalAv.route.idInfo_to.ui64Id  );
		}
	}

	for  (  j  =  0;  j  <  mycountof(  pTaskInfo->var.curRoute_sendLocalAv.route.mems_to  );  j  ++  )  {
		 if  (  !pTaskInfo->var.curRoute_sendLocalAv.route.mems_to[j].idInfo.ui64Id  )  continue;		
		 if  (  t  -  pTaskInfo->var.curRoute_sendLocalAv.routeInfo.mems[j].tModifiedTime  >  120
			 &&  t  -  pTaskInfo->var.curRoute_sendLocalAv.routeInfo.mems[j].tRecvTime_lastResp  >  300  )
		 {		
			 removeFromMsgrs_sendLocalAv(  pProcInfo,  m_var.pMisCnt,  &pTaskInfo->var.curRoute_sendLocalAv.route.mems_to[j].idInfo,  &pTaskInfo->var.curRoute_sendLocalAv, false,  _T(  "dlgShareDynBmps_chkTask.962"  ));
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp: removeFromMsgrs_sendLocalAv, %I64u"  ),  pTaskInfo->var.curRoute_sendLocalAv.route.mems_to[j].idInfo.ui64Id  );
		 }
	}
#endif

	iErr  =  0;
errLabel:
	return  iErr;

}





 //
//int  dlgShareDynBmps_toShareDynBmp(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType,  int  index_pShare_mem,  void  **  ppCapStuff  )
int  dlgShareDynBmps_toShareDynBmp(  QY_MC  *  pQyMc,  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType,  int  index_pShare_mem,  void  **  ppCapStuff,  AV_COMPRESSOR_CFG  *  pCompressor_suggested,  TASK_av_props  *  pTaskAvProps  )
{
	if  (  !pDLG_shareDynBmps_var  )  return  -1;
	DLG_shareDynBmps_var	&	m_var		=	*(  DLG_shareDynBmps_var  *  )pDLG_shareDynBmps_var;
	
	int								iErr					=	-1;
	//QY_MC						*	pQyMc					=	QY_GET_GBUF(  );
	MC_VAR_isCli				*	pProcInfo				=	QY_GET_procInfo_isCli(  );//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	int								iIndex_sharedObj		=	-1;
	int								iIndex_sharedObjUsr		=	-1;
	QY_SHARED_OBJ				*	pSharedObj				=	NULL;
	int								iIndex_capBmp			=	-1;
	CAP_procInfo_video			*	pCapBmp					=	NULL;
	COMPRESS_VIDEO				*	pCompressVideo			=	NULL;	
	int								iIndex_shmCmd			=	-1;
	QM_SHM_CMD					*	pShmCmd					=	NULL;
	VIDEO_COMPRESSOR_CFG			videoCompressor;
	unsigned  int					uiTaskType				=	0;

	CHelp_shareDynBmp			help_dynBmpMem;
	SHARE_dyn_bmp			*	pDynBmpMem				=  NULL;

	switch  (  uiObjType  )  {
			case  CONST_objType_webcam:
			case  CONST_objType_rtspStream:
				  break;
			default:
					#ifdef  __DEBUG__
							traceLog((TCHAR*)  _T(  "dlgShareDynBmps_toShareDynBmp: uiObjType %d err"  ),  uiObjType  );
					#endif
					return  -1;
	}


	SHARE_dynBmps	*	pShare;
	pShare  =  (  SHARE_dynBmps  *  )dlgShareDynBmps_getShareDynBmpsBySth(  m_hWnd,  &m_var,  uiObjType  );
	if  (  !pShare  )  return  -1;
	pDynBmpMem  =  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  index_pShare_mem  );
	if  (  !pDynBmpMem  )  return  -1;


#if  0
	//  2011/10/15 在点击启动共享后，就可以不必保持置前状态了
	if  (  m_var.bNeed_shareWebcamInConference  )  {
		m_var.bNeed_shareWebcamInConference  =  FALSE;
	}
#endif


	//  2014/09/28. 2015/10/22
	//
	int iTaskId_suggested=0;
	{
		void * pDb=NULL;
		CQnmDb db;
		if(!db.getAvailableDb(pQyMc->iDsnIndex_mainSys)) goto errLabel;
		pDb=db.m_pDbMem->pDb;
		iTaskId_suggested=newTaskId(pDb,pQyMc->cfg.db.iDbType);
	}	
	if  (  toShareDynBmp(  pProcInfo,  m_hWnd,  ppCapStuff,  iTaskId_suggested,  pCompressor_suggested,  0,  pTaskAvProps,  pDynBmpMem  )  )  goto  errLabel;

	//
	mytime(  &m_var.tLastModifiedTime  );


	iErr  =  0;

errLabel:
	
	if  (  iErr  )  {
#if  0
		askSharedObjToStop(  pProcInfo,  pSharedObj,  pQyMc->gui.hMainWnd  );
		if  (  pDynBmpMem  )  {
			pDynBmpMem->var.ucbLocalVideoOpen  =  FALSE;
			//  2014/09/11
			pDynBmpMem->var.ucbUsed_iIndex_sharedObj  =  FALSE;
		}
#endif
	}

	dlgShareDynBmps_refreshShareStatus(  pQyMc, m_hWnd,  &m_var,  uiObjType  );

	return  iErr;
}





int  dlgShareDynBmps_toShareGps(  QY_MC  *  pQyMc,HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var)
{
	if  (  !pDLG_shareDynBmps_var  )  return  -1;
	DLG_shareDynBmps_var	&	m_var		=	*(  DLG_shareDynBmps_var  *  )pDLG_shareDynBmps_var;

	int		iErr	=	-1;
	CComPortEx	*	pPort	=	(  CComPortEx  *  )m_var.pComPort_gps;
	
	m_var.share_gps.bShare  =  !m_var.share_gps.bShare;

	if  (  !m_var.share_gps.bShare  )  {
		if  (  pPort  )  delete  pPort;
		m_var.pComPort_gps  =  NULL;
		dlgShareDynBmps_refreshShareStatus_gps(  pQyMc,m_hWnd,  &m_var  );
		return  0;
	}

	//
	if  (  pPort  )  {
		delete  pPort;
		m_var.pComPort_gps  =  NULL;
	}

	memset(  &m_var.share_gps.var,  0,  sizeof(  m_var.share_gps.var  )  );

	//
	//QY_MC						*	pQyMc					=	QY_GET_GBUF(  );
	MC_VAR_isCli				*	pProcInfo				=	QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	int								iIndex_sharedObj		=	-1;
	int								iIndex_sharedObjUsr		=	-1;
	QY_SHARED_OBJ				*	pSharedObj				=	NULL;
	int								iIndex_shmCmd			=	-1;
	QM_SHM_CMD					*	pShmCmd					=	NULL;
	unsigned  int					uiTaskType				=	0;

	#ifdef  __DEBUG__
	#endif
	
	iIndex_sharedObj  =  newSharedObjIndex(  pProcInfo,  m_hWnd,  0,  &iIndex_sharedObjUsr,  NULL  );
	if  (  iIndex_sharedObj  <  0  )  goto  errLabel;
	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;
	//
	iIndex_shmCmd  =  newShmCmdIndex(  pProcInfo,  iIndex_sharedObj  );
	pShmCmd  =  getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  iIndex_shmCmd  );
	if  (  !pShmCmd  )  goto  errLabel;
		    
	//
//	pSharedObj->iIndex_shmCmd  =  iIndex_shmCmd;


	//
	uiTaskType  =  CONST_imTaskType_shareGps;

	//
	m_var.share_gps.var.iIndex_sharedObj  =  iIndex_sharedObj;


	//
	dlgShareDynBmps_chkShareGps(  m_hWnd,  &m_var  );


	//
#if  10
	if  (  procSendGpsInfo(  m_var.pMisCnt,  m_hWnd,  FALSE,  uiTaskType,  iIndex_sharedObj,  iIndex_sharedObjUsr,  NULL,  &m_var.share_gps.var.iTaskId,  NULL  )  )  goto  errLabel;
#endif

	//  2010/09/09
	setCurSharedObjUsr(  pProcInfo,  iIndex_sharedObj, iIndex_sharedObjUsr);


	iErr  =  0;
errLabel:
	
	if  (  iErr  )  {
		askSharedObjToStop(  pProcInfo,  pSharedObj,  pQyMc->gui.hMainWnd,  _T(  "dlgShareDynBmps_toShareGps"  )  );
	}

	dlgShareDynBmps_refreshShareStatus_gps(  pQyMc,m_hWnd,  &m_var  );

	return  iErr;
}





//
int  dlgShareDynBmps_closeTaskAv(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType,  int  index_pShare_mem  )
{
	if  (  !pDLG_shareDynBmps_var  )  return  -1;
	DLG_shareDynBmps_var	&	m_var		=	*(  DLG_shareDynBmps_var  *  )pDLG_shareDynBmps_var;

#ifdef  __WINCE__
	return  -1;
#else
	int								iErr	=	-1;

	MC_VAR_isCli				*		pProcInfo							=	QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	QY_MC					*		pQyMc								=	(  QY_MC  *  )pProcInfo->pQyMc;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;
	//CQnmDb							db;
	//int								iDbType								=	pQyMc->cfg.db.iDbType;
	//IM_TASK_RCD						rcd;
	//CQyMalloc						mallocObj;
	//MIS_MSG_TASK			*		pMsgTask							=	(  MIS_MSG_TASK  *  )mallocObj.mallocf(  sizeof(  MIS_MSG_TASK  )  );
	//if  (  !pMsgTask  )  return  -1;
	int								lenInBytes							=	0;

	CHelp_shareDynBmp  help_dynBmpMem;
	SHARE_dyn_bmp  *  pDynBmpMem  =  NULL;

	SHARE_dynBmps			*		pShare;
	pShare  =  (  SHARE_dynBmps  *  )dlgShareDynBmps_getShareDynBmpsBySth(  m_hWnd,  &m_var,  uiObjType  );
	if  (  !pShare  )  return  -1;

	if  (  index_pShare_mem  <  0  ||  index_pShare_mem  >=  pShare->usCnt  )  return  -1;
	pDynBmpMem  =  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  index_pShare_mem  );
	if  (  !pDynBmpMem  )  return  -1;

#if  0
	//
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;


	QY_SHARED_OBJ  *  pSharedObj;
	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pDynBmpMem->var.iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;

	if  (  pDynBmpMem->var.ucbLocalVideoOpen
		||  pDynBmpMem->var.ucbUsed_iIndex_sharedObj  )		//  2014/09/11
	{
		//  
		//  if  (  pSharedObj->bCapDev  )  memset(  pSharedObj,  0,  sizeof(  pSharedObj[0]  )  );
		//  CWnd  *  pMainWnd  =  AfxGetApp(  )->m_pMainWnd;
		HWND  hMainWnd  =  pQyMc->gui.hMainWnd;
		askSharedObjToStop(  pProcInfo,  pSharedObj,  hMainWnd  );
		//
	}

	//
	if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
	//
	if  (  !g_dbFuncs.pf_bGetImTaskRcdBySth(  db.m_pDbMem->pDb,  iDbType, FALSE,  NULL,  NULL,  0,  0,  pDynBmpMem->var.iTaskId,  &rcd  )  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "dlgShareDynBmps_closeTaskAv: bGetImTaskRcdBySth failed. skipped"  )  );
		#endif
		}
	else  {

		  //
		  MIS_CNT	*	pMisCnt	=	getMisCntByName(  pProcInfo,  _T(  ""  )  );
		  
		  if  (  !taskRcd2Msg(  pMisCnt,  &rcd,  pMsgTask  )  )  goto  errLabel;
		  
		  //  
		  unsigned  short	usOp		=	CONST_imOp_send_cancel;
		  
		  TASK_PROC_REQ		taskProcReq;
		  memset(  &taskProcReq,  0,  sizeof(  taskProcReq  )  );
		  taskProcReq.uiType  =  CONST_imCommType_taskProcReq;
		  taskProcReq.usOp  =  usOp;
		  taskProcReq.tStartTime_org  =  rcd.tSendTime;
		  taskProcReq.uiTranNo_org  =  rcd.uiTranNo;
		  taskProcReq.uiSerialNo_org  =  rcd.uiSerialNo;
		  taskProcReq.uiContentType_org  =  rcd.uiContentType;	
		  //
		  lenInBytes  =  sizeof(  taskProcReq  ); 	
		  //					  
		  MACRO_prepareForTran(  );						
		  //						  
		  if  (  pFuncs->pf_postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_task,  0,  pMsgTask->usCode,  tStartTran,  uiTranNo,  0,  rcd.id,  rcd.uiType,  (  char  *  )&taskProcReq,  lenInBytes,  NULL,  &pMsgTask->idInfo_taskSender,  &pMsgTask->idInfo_taskReceiver,  &rcd.idInfo_recv,  pMsgTask->uiChannelType,  NULL,  0  )  )  goto  errLabel;
		  
		  //
		  int						idc				=	m_var.guiData.iIDC_STATIC_pic0;
		  int						idc_dst			=	idc;
		  freeCapImageByTaskId(  m_hWnd,  idc,  rcd.id,  &m_var.images,  old_M_GetDlgItem(  m_hWnd,  idc_dst  )  );
	}
	
	//
	//  memset(  &pShare->mems[index_pShare_mem].var,  0,  sizeof(  pShare->mems[index_pShare_mem].var  )  );
	memset(  &pDynBmpMem->var,  0,  sizeof(  pDynBmpMem->var  )  );
#endif

	int  iTaskId  =  pDynBmpMem->var.iTaskId;
	if  (  shareDynBmp_closeTaskAv(  pDynBmpMem  )  )  goto  errLabel;  

			  
	//	
	int						idc				=	m_var.guiData.iIDC_STATIC_pic0;		
	int						idc_dst			=	idc;		  
	old_freeCapImageByTaskId(  m_hWnd,  idc,  iTaskId,  &m_var.images,  old_M_GetDlgItem(  m_hWnd,  idc_dst  )  );


	//  2014/09/09
	mytime(  &m_var.tLastModifiedTime  );
		
	iErr  =  0;

errLabel:
	
	qmcApplyForChkingTasks_gui(  pQyMc  );

	return  iErr;
#endif
}


int  dlgShareDynBmps_chkShareGps(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var  )
{
	if  (  !pDLG_shareDynBmps_var  )  return  -1;
	DLG_shareDynBmps_var	&	m_var		=	*(  DLG_shareDynBmps_var  *  )pDLG_shareDynBmps_var;

	int		iErr	=	-1;
	CComPortEx	*	pPort	=	(  CComPortEx  *  )m_var.pComPort_gps;

	if  (  !m_var.share_gps.bShare  )  return  0;

	if  (  pPort  )  {
		DWORD	dwTickCnt  =  GetTickCount(  );

		if  (  dwTickCnt  -  pPort->m_var.dwTickCnt_modified_gpsPos  <  10000  )  {
			//  接收数据正常
			return  0;
		}

		if  (  m_var.share_gps.var.dwTickCnt_start
			&&  dwTickCnt  -  m_var.share_gps.var.dwTickCnt_start  <  10000  )  
		{
			//  还在探测中
			return  0;
		}
	}

	if  (  !pPort  )  {
#include	"unDeclareDebugNew.h"
		pPort  =  new  CComPortEx;
#include	"declareDebugNew.h"
		if  (  !pPort  )  goto  errLabel;
		m_var.pComPort_gps  =  pPort;
	}

	for  (  ;  m_var.share_gps.var.portNo  <  MAX_portNo_gps;  m_var.share_gps.var.portNo  ++  )  {
		 if  (  !m_var.share_gps.var.portNo  )  continue;
		 
		 char  parity  =  'N';
		 parity  =  NOPARITY;
		 UINT  stopbits  = 1;
		 stopbits  =  ONESTOPBIT;

		 if  (  !pPort->bInitPort(  m_hWnd,  m_var.share_gps.var.portNo,  4800,  parity,  8,  stopbits,  EV_RXCHAR  |  EV_CTS,  512,  CONST_iComPortType_gps,  m_var.share_gps.var.iIndex_sharedObj  )  )  continue;		 
		 break;
	}
	if  (  m_var.share_gps.var.portNo  ==  MAX_portNo_gps  )  {
		m_var.share_gps.var.portNo  =  0;
		goto  errLabel;
	}

	if  (  !pPort->bStartMonitoring(  )  )  goto  errLabel;
	m_var.share_gps.var.dwTickCnt_start  =  GetTickCount(  );

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		CComPortEx  *  pPort  =  (  CComPortEx  *  )m_var.pComPort_gps;
		if  (  pPort  )  {
			delete  pPort;
			m_var.pComPort_gps  =  NULL;
		}
	}

	return  iErr;

}


int  dlgShareDynBmps_sndDynBmpsInfo(   HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var  )
{
	DLG_shareDynBmps_var  &  m_var  =  *(  DLG_shareDynBmps_var  *  )pDLG_shareDynBmps_var;

	MC_VAR_isCli			*		pProcInfo							=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;


	int			iErr	=	-1;
	 
	REFRESH_DYN_BMPS		req;
	MACRO_prepareForTran(  );
	int						len;
	int						i,  j;

	if  (  !bMeOnline(  (  QY_MC  *  )pProcInfo->pQyMc  )  )  return  -1;

	memset(  &req,  0,  sizeof(  req  )  );
	req.uiType  =  CONST_imCommType_refreshDynBmps;
	req.tLastModifiedTime  =  m_var.tLastModifiedTime;
	//
	for  (  j  =  0;  j  <  mycountof(  m_var.shares  );  j  ++  )  {
		 SHARE_dynBmps	*	pShare		=	&m_var.shares[j];
		 for  (  i  =  0;  i  <  pShare->usCnt  &&  req.usCnt  <  mycountof(  req.mems  );  i  ++  )  {
			 //CHelp_shareDynBmp  help_dynBmpMem;
			 SHARE_dyn_bmp  *  pDynBmpMem  =  &pShare->mems_internal[i];  //help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  pShare->uiObjType,  i  );
			 if  (  !pDynBmpMem  )  continue;
			 
			 if  (  !bShared(  pDynBmpMem  )  )  continue;
			 req.mems[req.usCnt].qisResObj.resObj.uiObjType  =  pDynBmpMem->resObj.uiObjType;	//  pShare->uiObjType;
			 //  req.mems[req.usCnt].usIndex_obj  =  i;
			 req.mems[req.usCnt].qisResObj.resObj.usIndex_obj  =  pDynBmpMem->resObj.usIndex_obj;	//  2014/05/31
			 lstrcpyn(  req.mems[req.usCnt].name,  pDynBmpMem->name,  mycountof(  req.mems[req.usCnt].name  )  );
			 lstrcpyn(  req.mems[req.usCnt].cusName,  pDynBmpMem->cusName,  mycountof(  req.mems[req.usCnt].cusName  )  );
			 req.usCnt  ++  ;		 		 
		 }
	}
	//
	len  =  offsetof(  REFRESH_DYN_BMPS,  mems  )  +  req.usCnt  *  sizeof(  req.mems[0]  );
	//
	postMsg2Mgr_mc(  m_var.pMisCnt,  NULL,  CONST_misMsgType_req,  0,   CONST_qyCmd_sendVDevReq,  tStartTran,  uiTranNo,  0,  (  char  *  )&req,  len,  NULL,  0,  0,  NULL,  0  ); 
	//

	return  iErr;
}



int dlgShareDynBmps_testRtspUrl(  QY_MC  *  pQyMc,  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  unsigned  short  usIndex_obj,  unsigned  short  usHelp_subIndex  )
{
	int		iErr	=	-1;
	void  *  pVar  =  pDLG_shareDynBmps_var;
	DLG_shareDynBmps_var  &  m_var  =  *(  DLG_shareDynBmps_var  *  )pDLG_shareDynBmps_var;
	
	int  ii;
	int  i;
	int  uiObjType  =  CONST_objType_rtspStream;
	
	CHelp_shareDynBmp  help_dynBmpMem;
	SHARE_dyn_bmp  *  pMem  =  NULL;

	
	SHARE_dynBmps	*	pShare;																		
	pShare  =  (  SHARE_dynBmps  *  )dlgShareDynBmps_getShareDynBmpsBySth(  m_hWnd,  &m_var,  uiObjType  );	
	if  (  !pShare  )  goto  errLabel;							    

	
	for  (  ii  =  0;  ii  <  mycountof(  m_var.onvif.ipDevsInfo.mems  );  ii  ++  )  {	
		if  (  m_var.onvif.ipDevsInfo.mems[ii].rule.usIndex_obj  ==  usIndex_obj  
			&&  m_var.onvif.ipDevsInfo.mems[ii].usHelp_subIndex  ==  usHelp_subIndex  )  			
		{
			break;				 
		}
	}
	if  (  ii  ==  mycountof(  m_var.onvif.ipDevsInfo.mems  )  )  goto  errLabel;	
	//
	//Onvif_rule  url  =  m_var.onvif.rulesInfo.mems[ii];		
	IP_dev  *  pIpDev  =  &m_var.onvif.ipDevsInfo.mems[ii];
	//
	i  =  help_dynBmpMem.getIndexByIndex_obj(  m_hWnd,  &m_var,  uiObjType,  pIpDev->rule.usIndex_obj,  pIpDev->usHelp_subIndex  );
	if  (  i  <  0  )  {
		i  =  help_dynBmpMem.getNewIndex(  m_hWnd,  &m_var,  uiObjType  );
		if  (  i  <  0  )  {
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp failed: shared rtsp streams are full"  )  );	
			showNotification(  0,  0,  0,  0,  0,  0,  _T(  "sharedDynBmp failed: shared rtsp streams are full"  )  );
			goto  errLabel;		
		}
		pMem  =  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  i  );
		if  (  !pMem  )  goto  errLabel;
		//
		if  (  help_dynBmpMem.clear(  pMem  )  )  goto  errLabel;
		//
		pMem->resObj.uiObjType  =  uiObjType;	//  2014/11/27
		pMem->resObj.usIndex_obj  =  pIpDev->rule.usIndex_obj;
		pMem->resObj.usHelp_subIndex  =  pIpDev->usHelp_subIndex;	//  2016/07/24
		//
		//myUtf82TChar(  url.url,  pMem->name,  mycountof(  pMem->name  )  );
		char  realUrl[256]  =  "";
		get_realUrl(  pIpDev,  realUrl,  mycountof(  realUrl  )  );
		myUtf82TChar(  realUrl,  pMem->name,  mycountof(  pMem->name  )  );
		//
		safeTcsnCpy(  pIpDev->rule.cusName,  pMem->cusName,  mycountof(  pMem->cusName  )  );
	}

	pMem  =  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  i  );	
	if  (  !pMem  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "getMemByIndex failed"  )  );
		#endif
		goto  errLabel;
	}


	if  (  !pMem->var.ucbLocalVideoOpen  )  {

		//  2014/09/11		
		if  (  pMem->var.internalProcess.bInProcess  )  {			
			showInfo_open0(  0,  0,  _T(  "dlgShareDynBmps_testRtspUrl failed: bInProcess true"  )  );
			goto  errLabel;					 
		}

		//
		dlgShareDynBmps_toShareDynBmp(  pQyMc,  m_hWnd,  pVar,  uiObjType,  i,  NULL,  NULL,  NULL  );	
				
		//
		if  (  pMem->var.internalProcess.bInProcess  )  {
			pMem->var.internalProcess.bTest  =  TRUE;
			//
			m_var.internalProcess.bNeedProcess  =  TRUE;				
			//  2014/09/11
			iErr  =  0;  goto  errLabel;					 
		}

	}
	if  (  !pMem->var.ucbLocalVideoOpen  )  {
					 #ifdef  __DEBUG__
							 traceLog((TCHAR*)  _T(  "shareDynBmp failed, ucbLocalVideoOpen 0"  )  );
					 #endif
					 goto  errLabel;
	
	}
	
	dlgShareDynBmps_refreshShareStatus(  pQyMc,  m_hWnd,  pVar,  uiObjType  );
				 
	//		
	iErr  =  0;

errLabel:
		
	return  iErr;
 }


///////////////

int  shareDynBmpMem_internalProcess(  QY_MC  *  pQyMc,  HWND  m_hWnd,  DLG_shareDynBmps_var  *  pm_var,  unsigned  int  uiObjType,  int  index_pShare_mem  )
{
	int	iErr  =  -1;
	//QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo =   QY_GET_procInfo_isCli(  );

	CHelp_shareDynBmp	help_dynBmpMem;
	SHARE_dyn_bmp  *  pDynBmpMem  =  NULL;
	pDynBmpMem  =  help_dynBmpMem.getMemByIndex(  m_hWnd,  pm_var,  uiObjType,  index_pShare_mem  );
	if  (  !pDynBmpMem  )  return  -1;
	
	TCHAR  tHint[128];	
	_sntprintf(  tHint,  mycountof(  tHint  ),  _T(  "ind_share_mem %d"  ),  index_pShare_mem  );


	if  (  !pDynBmpMem->var.internalProcess.bInProcess  )  return  -1;

	if  (  !pDynBmpMem->var.ucbUsed_iIndex_sharedObj  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "shareDynBmpMem_internalProcess failed: ucbUsed_iIndex_sharedObj is 0"  )  );
		#endif
		showInfo_open0(  0,  0,  _T(  "shareDynBmpMem_internalProcess failed: ucbUsed_iIndex_sharedObj is 0"  )  );
		return  -1;
	}
	QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pDynBmpMem->var.iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;

	if  (  pDynBmpMem->var.internalProcess.nStep  ==  CONST_shareDynBmpMem_step_0  )  {
		BOOL  bWait  =  FALSE;
		if  (  openLocalVideo_rtsp_step1(  (  MC_VAR_common  *  )pProcInfo,  pDynBmpMem->name,  bWait,  tHint,  pDynBmpMem->var.iIndex_sharedObj  )  )  {
			iErr  =  0;  goto  errLabel;
		}
		pDynBmpMem->var.internalProcess.nStep  =  CONST_shareDynBmpMem_step_1;
	}

	if  (  pDynBmpMem->var.internalProcess.nStep  ==  CONST_shareDynBmpMem_step_1  )  {
		if  (  openLocalVideo_rtsp_step2(  (  MC_VAR_common  *  )pProcInfo,  pDynBmpMem->name,  tHint,  pDynBmpMem->var.iIndex_sharedObj  )  )  goto  errLabel;
		pDynBmpMem->var.internalProcess.nStep  =  CONST_shareDynBmpMem_step_2;
	}

	pDynBmpMem->var.ucbLocalVideoOpen  =  TRUE;
	//
	BOOL	bTest  =  pDynBmpMem->var.internalProcess.bTest;

	//
	if  (  pDynBmpMem->var.internalProcess.nStep  ==  CONST_shareDynBmpMem_step_2  )  {
		memset(  &pDynBmpMem->var.internalProcess,  0,  sizeof(  pDynBmpMem->var.internalProcess  )  );
	}

	//
	//  
	if  (  toShareDynBmp_step3(  pProcInfo,  m_hWnd,  0,  pDynBmpMem  )  )  goto  errLabel;

	//
	if  (  !bTest  )  {
		
		int		i  =  index_pShare_mem;
		int		j  =  pDynBmpMem->var.recvdReq.index_recvdReq;
		if  (  j  <  0  ||  j  >=  mycountof(  pm_var->recvdReqs  )  )  goto  errLabel;
		DLG_shareDynBmp_recvdReq  *  pRecvdReq  =  &pm_var->recvdReqs[j];
		if  (  !pRecvdReq->dwTickCnt  )  goto  errLabel;
		if  (  pRecvdReq->info.uiTranNo_storeRecvdReq  !=  pDynBmpMem->var.recvdReq.uiTranNo_storeRecvdReq  )  goto  errLabel;
		
		//
		if  (  procVerifyViewDynBmpResp_step4(  m_hWnd,  pm_var,  uiObjType,  i  )  )  goto  errLabel;
	 	
		 //  2014/09/11
		 noStoreRecvdReq(  m_hWnd,  pm_var,  j  );
	}

	iErr  =  0;
errLabel:

	if  (  iErr  )  {

		askSharedObjToStop(  pProcInfo,  pSharedObj,  pQyMc->gui.hMainWnd,  _T(  "shareDynBmpMem_internalProcess"  )  );
		if  (  pDynBmpMem  )  {
			pDynBmpMem->var.ucbLocalVideoOpen  =  FALSE;
			//  2014/09/11
			pDynBmpMem->var.ucbUsed_iIndex_sharedObj  =  FALSE;
		}

	}

	return  iErr;
}


int  dlgShareDynBmps_internalProcess(  QY_MC  *  pQyMc,  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var  )
{
	int  iErr  =  -1;
	
	//QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli			*		pProcInfo							=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp	*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	DLG_shareDynBmps_var  *  pm_var  =  (  DLG_shareDynBmps_var  *  )pDLG_shareDynBmps_var;
	DLG_shareDynBmps_var  &  m_var  =  *pm_var;
	BOOL					bFound  =  FALSE;
		


	#ifdef  __DEBUG__
			traceLog((TCHAR*)  _T(  "dlgShareDynBmps_internalProcess called"  )  );
	#endif


	//	
	SHARE_dynBmps	*	pShare;		
	unsigned  int  uiObjType  =  CONST_objType_rtspStream;
	pShare  =  (  SHARE_dynBmps  *  )dlgShareDynBmps_getShareDynBmpsBySth(  m_hWnd,  &m_var,  uiObjType  );
	if  (  !pShare  )  goto  errLabel;
	
		
	int  i;	
	for  (  i  =  0;  i  <  pShare->usCnt;  i  ++  )  {				
		 CHelp_shareDynBmp	help_dynBmpMem;
		 SHARE_dyn_bmp  *  pDynBmpMem  =  help_dynBmpMem.getMemByIndex(  m_hWnd,  &m_var,  uiObjType,  i  );
		 if  (  pDynBmpMem  )  {
			 if  (  pDynBmpMem->var.internalProcess.bInProcess  )  {						  
				 bFound  =  TRUE;
				 //
				 shareDynBmpMem_internalProcess(  pQyMc,  m_hWnd,  &m_var,  uiObjType,  i  );
				 //  如果时间太久了，就要放弃
				 if  (  pDynBmpMem->var.internalProcess.bInProcess  )  {
					 int  iDiffInMs  =  GetTickCount(  )  -  pDynBmpMem->var.internalProcess.dwTickCnt_start;
					 if  (  iDiffInMs  >  10000  )  {
						 //
						 #ifdef  __DEBUG__
								 traceLog((TCHAR*)  _T(  "Internal process too long, so call closeTaskAv "  )  );
						 #endif
						 TCHAR  tBuf[128]  =  _T(  ""  );
						 QY_DMITEM	*	pTable				=					getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );
						 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "too long %dms, so call closeTaskAv (%s, %d). ind_share_mem %d"  ),  iDiffInMs,  qyGetDesByType1(  pTable,  uiObjType  ),  pDynBmpMem->resObj.usIndex_obj,  i  );
						 showInfo_open0(  0,  _T(  "dlgSharedDynBmps_internalProcess"  ),  tBuf  );
						 //
						 pFuncs->shareDynBmps.pf_dlgShareDynBmps_closeTaskAv(  m_hWnd,  &m_var,  uiObjType,  i  );
					 }
				 }
			 }					
		 }			
	}
	
	if  (  !bFound  )  {
#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "dlgShareDynBmps_internalProcess: no internal process, flag removed"  )  );
#endif
		m_var.internalProcess.bNeedProcess  =  FALSE;
	}
		 
	
	iErr  =  0;

errLabel:
		 return  iErr;

}


