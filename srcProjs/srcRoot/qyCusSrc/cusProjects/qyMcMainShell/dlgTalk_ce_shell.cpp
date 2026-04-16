

#include	"stdafx.h"
#include	"qyDefs_open.h"
#include	"qyCusResPublic.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"



/////////////////////////////////
TCHAR	g_inputBuf[256]	=	_T(  ""  );

INT_PTR CALLBACK dlgProc_input(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	void	*	pDlg	=	(  void  *  )GetWindowLong(  hDlg,  GWLP_USERDATA  );

	UNREFERENCED_PARAMETER(lParam);
	switch  (  message  ) {
		   	case  WM_INITDIALOG:
				  pDlg  =  (  void  *  )lParam;
				  SetWindowLong(  hDlg,  GWLP_USERDATA,  (  LONG )pDlg  );

				  return (INT_PTR)TRUE;

			case  WM_COMMAND:  {
				  WORD  wNotifyCode = HIWORD(wParam); 
				  WORD  wID = LOWORD(wParam); 
				  HWND  hwndCtl = (HWND) lParam;

				  switch  (  wID  )  {
						  case  IDCANCEL:
							    EndDialog(  hDlg,  -1  );
								return  TRUE;
						  case  IDOK:
							    GetDlgItemText(  hDlg,  IDC_EDIT_input,  g_inputBuf,  sizeof(  g_inputBuf  )  /  sizeof(  g_inputBuf[0]  )  );
								if  (  !g_inputBuf[0]  )  return  TRUE;
								EndDialog(  hDlg,  IDOK  );							    
							    return  TRUE;
						  default:
								 break;
				  }

				 }
				 break;

			default:
					break;
	}

	return (INT_PTR)FALSE;
}



//////////////////////////////////
#define		DEFAULT_iPageType	CONST_iPageType_av

int  setPage_talk_ce(  void  *  pDlg,  HWND  hDlg,  int  iPageType  )
{
	int		idc_hidden			=	0;
	BOOL	bListHidden			=	FALSE;
	BOOL	bTaskStatusHidden	=  FALSE;
	BOOL	bOp0Hidden			=	FALSE;
	BOOL	bOp1Hidden			=  TRUE;
	BOOL	bChanged			=	FALSE;

	DLG_guiData_talk  *  pGuiData  =  (  DLG_guiData_talk  *  )qyWnd_getGuiData(  pDlg  );
	if  (  !iPageType  )  {
		pGuiData->param.iPageType  =  DEFAULT_iPageType;
		bChanged  =  TRUE;
		}
	else  if  (  pGuiData->param.iPageType  !=  iPageType  )  {
			  pGuiData->param.iPageType  =  iPageType;	
			  bChanged  =  TRUE;
	}

	switch  (  pGuiData->param.iPageType  )  {
			case  CONST_iPageType_msg:
				  idc_hidden  =  IDC_BUTTON_msg;
				  bTaskStatusHidden  =  TRUE;
				  break;
			case  CONST_iPageType_task:
				  idc_hidden  =  IDC_BUTTON_task;
				  bTaskStatusHidden  =  TRUE;
				  //
				  break;
			case  CONST_iPageType_av:
			default:
				  idc_hidden  =  IDC_BUTTON_av;
				  bListHidden  =  TRUE;
				  break;
	}

	if  (  pGuiData->idc_hidden  !=  idc_hidden  )  {
		pGuiData->idc_hidden  =  idc_hidden;
		bChanged  =  TRUE;
	}
	if  (  pGuiData->bListHidden  !=  bListHidden  )  {
		pGuiData->bListHidden  =  bListHidden;
		bChanged  =  TRUE;
	}
	if  (  pGuiData->bTaskStatusHidden  !=  bTaskStatusHidden  ) {
		pGuiData->bTaskStatusHidden  =  bTaskStatusHidden;
		bChanged  =  TRUE;
	}
	if  (  pGuiData->bOp0Hidden  !=  bOp0Hidden  )  {
		pGuiData->bOp0Hidden  =  bOp0Hidden;
		bChanged  =  TRUE;
	}
	if  (  pGuiData->bOp1Hidden  !=  bOp1Hidden  )  {
		pGuiData->bOp1Hidden  =  bOp1Hidden;
		bChanged  =  TRUE;
	}

	if  (  bChanged  )  pGuiData->bChanged_layout  =  TRUE;

	return  0;
}

 //  int  refreshDlg_talk_ce(  void  *  pDlg,  HWND  hDlg,  void  *  p2  )
int  refreshDlg_talk_ce(  HWND  hDlg,  void  *  pGuiDataParam,  void  *  p2  )
{
	DLG_guiData_talk	*	pGuiData		=  (  DLG_guiData_talk  *  )pGuiDataParam;	//  qyWnd_getGuiData(  pDlg  );
	BOOL					bHidden_op0		=	FALSE;
	TCHAR				*	pT_op0			=	_T(  ""  );

	switch  (  pGuiData->param.iPageType  )  {
			case  CONST_iPageType_msg:
				  pT_op0  =  _T(  "Send"  );
				  break;
			case  CONST_iPageType_task:  {
				  int			nCurSel;
				  int			len;
				  TCHAR		*	pT;
				  HWND			hCtl  =  GetDlgItem(  hDlg,  IDC_LIST_task  );

				  memset(  &pGuiData->task.curSel,  0,  sizeof(  pGuiData->task.curSel  )  );

				  nCurSel  =  SendMessage(  hCtl,  LB_GETCURSEL,  0,  0  );
				  if  (  nCurSel  >=  0  )  {
					  //
					  len  =  SendMessage(  hCtl,  LB_GETTEXTLEN,  nCurSel,  0  );
					  if  (  len  >  0  )  {										
						  pT  =  (  TCHAR  *  )malloc(  (  len  +  1  )  *  sizeof(  TCHAR  )  );
						  if  (  pT  )  {
							  if  (  SendMessage(  hCtl,  LB_GETTEXT,  nCurSel,  (  LPARAM  )pT  )  !=  LB_ERR  )  {
								  pT[len]  =  0;
								  dlgTalk_bSelTask(  hDlg,  pT  );										
							  }
							  free(  pT  );
						  }
					  }
				  }
				  if  (  pGuiData->task.nCurSel  !=  nCurSel  )  pGuiData->task.nCurSel  =  nCurSel;

				  if  (  !pGuiData->task.curSel.bTaskAlive  )  {
					  bHidden_op0  =  TRUE;
					  break;
				  }
				  if  (  pGuiData->task.curSel.uiTaskType  ==  CONST_imTaskType_transferAvInfo  )  {
					  bHidden_op0  =  TRUE;
					  break;
				  }

				#if  10
				  TCHAR	tBuf[128];
				  _sntprintf(  tBuf,  123,  _T(  "refreshDlg_talk_ce: taskType %d, status %d\n"  ),  pGuiData->task.curSel.uiTaskType,  pGuiData->task.curSel.iStatus  );
				  OutputDebugString(  tBuf  );
				#endif

				  switch  (  pGuiData->task.curSel.iStatus  )  {
						  case  CONST_imTaskStatus_req:
						  case  CONST_imTaskStatus_acceptedByReceiver:
						  case  CONST_imTaskStatus_dualByReceiver:							    
						  case  CONST_imTaskStatus_waitToRecv:
							    bHidden_op0  =  TRUE;
							    break;
						  case  CONST_imTaskStatus_resp:
						  case  CONST_imTaskStatus_applyToRecv:
							    pT_op0  =  _T(  "accept"  );
							    break;								
						  default:
							     bHidden_op0  =  TRUE;
								 break;
				  }
				  //
				  }
				  break;
			case  CONST_iPageType_av:

				  switch  (  pGuiData->av.iStatus  )  {
						  case  CONST_imTaskStatus_req:
						  case  CONST_imTaskStatus_acceptedByReceiver:
						  case  CONST_imTaskStatus_dualByReceiver:
						  case  CONST_imTaskStatus_waitToRecv:
							    if  (  !pGuiData->bImGrp  )  {
									bHidden_op0  =  TRUE;
									}
								else  {
								      if  (  dlgTalk_canSpeak(  hDlg  )  )  pT_op0  =  _T(  "stop"  );									
									  else  pT_op0  =  _T(  "speak"  );									  
								}
								break;
						  case  CONST_imTaskStatus_applyToSend:
						  case  CONST_imTaskStatus_waitToSend:
							    break;
						  case  CONST_imTaskStatus_resp:  
						  case  CONST_imTaskStatus_applyToRecv:
							    pT_op0  =  _T(  "accept"  );
							    break;
						  default:
							      if  (  pGuiData->bImGrp  )  {
									  bHidden_op0  =  TRUE;
									  }
								  else  {  
									    pT_op0  =  _T(  "call"  );							
								  }
								  break;				
				  }
				  				  
				  break;
			default:
					break;
	}

	ShowWindow(  GetDlgItem(  hDlg,  IDC_BUTTON_op0  ),  bHidden_op0  ?  SW_HIDE  :  SW_SHOW  );
	SetDlgItemText(  hDlg,  IDC_BUTTON_op0,  pT_op0  );

#if  0
	if  (  pGuiData->param.iPageType  ==  CONST_iPageType_av  )  {
		SetDlgItemText(  hDlg,  IDC_STATIC_taskStatus,  pGuiData->av.statusDesc  );
	}
#endif

	return  0;
}


  //  int  sizeAllControls_talk_ce(  void  *  pDlg,  HWND  hDlg,  void  *  p2  )
int  sizeAllControls_talk_ce(  HWND  hDlg,  void  *  pGuiDataParam,  void  *  p2  )
{
		int			iErr							=	-1;
		HDWP		hDwp;
	    RECT		rc;

		int			iW_total						=	0;
		int			iH_total						=	0;

		int			iEdge_left						=	0;
		int			iEdge_top						=	0;
		int			iEdge_right						=	iEdge_left;
		int			iEdge_bottom					=	23;
		//
		int			iX_spacing						=	3;			//  Á½¸ö¿Ø¼þ¼äµÄºáÏò¼ä¸ô
		int			iY_spacing						=	3;			//  Á½¸ö¿Ø¼þ¼äµÄ×ÝÏò¼ä¸ô

		int			iW_btn  =  0,  iW_sBtn  =  0;
		int			iH_btn  =  0;

		int			iW_cancel						=	0;

		int			iH_peerDesc_small				=	20;

		int			x, y;
		HWND		hWnd							=	NULL;
		int			idc;
		//	 
		int			iW,  iH;

		DLG_guiData_talk  *  pGuiData	=	(  DLG_guiData_talk  *  )pGuiDataParam;	//  qyWnd_getGuiData(  pDlg  );
		if  (  !pGuiData  )  return  -1;

		//
		iEdge_bottom  *=  pGuiData->fy;
		//
		iH_peerDesc_small  *=  pGuiData->fy;

		//
		GetClientRect(  hDlg,  &rc  );
		iW_total  =  rc.right  -  rc.left;
		iH_total  =  rc.bottom  -  rc.top;
	 
		idc  =  pGuiData->iIDC_BUTTON_status;
		hWnd  =  GetDlgItem(  hDlg,  idc  );
		if  (  !hWnd  )  goto  errLabel;
		GetWindowRect(  hWnd,  &rc  );
		iW_btn  =  iW_total  -  iEdge_left  -  iEdge_right;
		iH_btn  =  rc.bottom  -  rc.top;

		idc  =  pGuiData->iIDCANCEL;
		hWnd  =  GetDlgItem(  hDlg,  idc  );
		if  (  !hWnd  )  goto  errLabel;
		GetWindowRect(  hWnd,  &rc  );
		iW_cancel  =  rc.right  -  rc.left;

		iX_spacing  =  (  iW_total  -  iEdge_left  -  iEdge_right  -  6  *  iW_cancel  )  /  5;

		//
		idc  =  pGuiData->iIDC_STATIC_peerDesc;				//  这个隐藏是为了引起peerDesc的强制重画。
		ShowWindow(  GetDlgItem(  hDlg,  idc  ),  SW_SHOW  );
		idc  =  pGuiData->iIDC_STATIC_meDesc;
		ShowWindow(  GetDlgItem(  hDlg,  idc  ),  SW_SHOW  );

		//
		hDwp  =  BeginDeferWindowPos(  11  );
		if  (  hDwp  )  {		 
			x  =  iEdge_left;
			y  =  iEdge_top;
			//
			idc  =  pGuiData->iIDC_STATIC_peerDesc;
			iW  =  iW_btn;  
			if  (  pGuiData->param.iPageType  !=  CONST_iPageType_av  )  iH  =  iH_peerDesc_small;
			else  iH  =  iH_total  -  iEdge_top  -  iEdge_bottom  -  iH_btn * 2  - iY_spacing * 2;
#ifndef  __WINCE__
			DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
#else
			DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
#endif

			pGuiData->peerCapRect.iX  =  x;  pGuiData->peerCapRect.iY  =  y;
			pGuiData->peerCapRect.iW  =  iW;  pGuiData->peerCapRect.iH  =  iH;

#if  0
			idc  =  pGuiData->iIDC_STATIC_taskStatus;
			if  (  pGuiData->param.iPageType  ==  CONST_iPageType_av  )  {
				y  =  y  +  iH + iY_spacing;
				iW  =  iW_btn;
				iH  =  iH_btn;
				DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
				}
			else
				DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
#endif

			idc  =  pGuiData->iIDC_LIST_msg;
			if  (  pGuiData->param.iPageType  ==  CONST_iPageType_msg  )  {
				x  =  iEdge_left;
				y  =  y  +  iH  +  iY_spacing;
				iW  =  iW_btn;
				iH  =  iH_total  -  iEdge_top  -  iEdge_bottom  -  iH_btn  *  2  -  iY_spacing  *  3  -  iH_peerDesc_small;
				DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
			}
			else
				DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );

			idc  =  pGuiData->iIDC_LIST_task;
			if  (  pGuiData->param.iPageType  ==  CONST_iPageType_task  )  {
				x  =  iEdge_left;
				y  =  y  +  iH  +  iY_spacing;
				iW  =  iW_btn;
				iH  =  iH_total  -  iEdge_top  -  iEdge_bottom  -  iH_btn  *  2  -  iY_spacing  *  3  -  iH_peerDesc_small;
				DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
			}
			else
				DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );


			idc  =  pGuiData->iIDC_BUTTON_status;
			x  =  iEdge_left;
			y  =  y  +  iH  +  iY_spacing;
			iW  =  iW_btn  -  iX_spacing  -  iW_cancel;
			iH  =  iH_btn;
			DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );

			//
			idc  =  pGuiData->iIDC_STATIC_meDesc;
			x  =  x  +  iW  +  iX_spacing;
			iW  =  iW_cancel;
			DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );

			pGuiData->meCapRect.iX  =  x;  pGuiData->meCapRect.iY  =  y;
			pGuiData->meCapRect.iW  =  iW;  pGuiData->meCapRect.iH  =  iH;

			//
			idc  =  pGuiData->iIDCANCEL;
			x  =  iEdge_left;
			y  =  y  +  iH  +  iY_spacing;
			iW  =  iW_cancel;
			DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );

			idc  =  pGuiData->iIDC_BUTTON_msg;
			x  =  x  +  iW  +  iX_spacing;
			if  (  pGuiData->idc_hidden  !=  idc  )  {
				//  OutputDebugString(  _T(  "msg shown\n"  )  );

				DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
				}
			else  {
				  //OutputDebugString(  _T(  "msg hidden\n"  )  );

				  DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
			}

			idc  =  pGuiData->iIDC_BUTTON_task;
			x  =  x  +  iW  +  iX_spacing;
			if  (  pGuiData->idc_hidden  !=  idc  )  {
				//  OutputDebugString(  _T(  "task shown\n"  )  );

				DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
				}
			else  {
				  // OutputDebugString(  _T(  "task hidden\n"  )  );

				  DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
			}

			idc  =  pGuiData->iIDC_BUTTON_av;
			x  =  x  +  iW  +  iX_spacing;
			if  (  pGuiData->idc_hidden  !=  idc  )  {
				//  OutputDebugString(  _T(  "av shown\n"  )  );

				DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
				}
			else  {
				  //  OutputDebugString(  _T(  "av hidden\n"  )  );

				  DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );
			}


			idc  =  pGuiData->iIDC_BUTTON_op1;
			x  =  x  +  iW  +  iX_spacing;
			if  (  !pGuiData->bOp1Hidden  )
				DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
			else
				DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );

			idc  =  pGuiData->iIDC_BUTTON_op0;
			x  =  x  +  iW  +  iX_spacing;
			if  (  !pGuiData->bOp0Hidden  )  
				DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_SHOWWINDOW  )  );
			else
				DeferWindowPos(  hDwp,  GetDlgItem(  hDlg,  idc  ),  NULL,  x,  y,  iW,  iH,  (  SWP_NOZORDER  |  SWP_HIDEWINDOW  )  );

			EndDeferWindowPos(  hDwp  );
	 }
	
	 


errLabel:
		return  iErr;
}


 //  int  displayNotification_talk_ce(  void  *  pWnd,  HWND  hDlg,  LPCTSTR  hint  )
int  displayNotification_talk_ce(  HWND  hDlg,  void  *  pGuiDataParam,  LPCTSTR  hint  )
{
	DLG_guiData_talk	*	pGuiData  =  (  DLG_guiData_talk  *  )pGuiDataParam;	//  qyWnd_getGuiData(  pWnd  );
	if  (  !pGuiData  )  return  -1;
	SetDlgItemText(  hDlg,  pGuiData->iIDC_BUTTON_status,  hint  );
	return  0;
}

 int  dlgLayout_talk_ce(   void *  pDlg,  HWND  hDlg  )
{
#if  !defined(  __WINCE__  )  ||  defined(  __TEST__  )
	     return  0;
#else
		 DLG_guiData_talk			*	p		=  (  DLG_guiData_talk  * )qyWnd_getGuiData(  pDlg  );  
		 if  (  !p  )  goto  errLabel;

		 int  w,  h;
		 int  w_org,  h_org;
		 HDC  hScreenDC  =  ::GetDC(  NULL  );
		 int  maxxScreen  =  GetDeviceCaps(  hScreenDC,  HORZRES  );
		 int  maxyScreen  =  GetDeviceCaps(  hScreenDC,  VERTRES  );
		 ::ReleaseDC(  NULL,  hScreenDC  );

		 RECT  rc;
		 GetWindowRect(  hDlg,  &rc  );
		 w_org  =  rc.right  -  rc.left;
		 h_org  =  rc.bottom  -  rc.top;

		 if  (  !w_org  ||  !h_org  )  goto  errLabel;

		 RECT  rcIDC_BUTTON_status;
		 GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_BUTTON_status  ),  &rcIDC_BUTTON_status  );
		 MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&rcIDC_BUTTON_status,  2  );
		 
		 RECT  rcIDCANCEL;
		 GetWindowRect(  GetDlgItem(  hDlg,  p->iIDCANCEL  ),  &rcIDCANCEL  );
		 MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&rcIDCANCEL,  2  );

		 RECT  rcIDC_BUTTON_msg;
		 GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_BUTTON_msg  ),  &rcIDC_BUTTON_msg  );
		 MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&rcIDC_BUTTON_msg,  2  );

		 RECT  rcIDC_BUTTON_task;
		 GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_BUTTON_task  ),  &rcIDC_BUTTON_task  );
		 MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&rcIDC_BUTTON_task,  2  );

		 RECT  rcIDC_BUTTON_av;
		 GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_BUTTON_av  ),  &rcIDC_BUTTON_av  );
		 MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&rcIDC_BUTTON_av,  2  );

		 RECT  rcIDC_BUTTON_op1;
		 GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_BUTTON_op1  ),  &rcIDC_BUTTON_op1  );
		 MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&rcIDC_BUTTON_op1,  2  );

		 RECT  rcIDC_BUTTON_op0;
		 GetWindowRect(  GetDlgItem(  hDlg,  p->iIDC_BUTTON_op0  ),  &rcIDC_BUTTON_op0  );
		 MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&rcIDC_BUTTON_op0,  2  );

		 w  =  maxxScreen;  h  =  maxyScreen;
		 MoveWindow(  hDlg,  0,  0,  w,  h,  TRUE  );
		 GetClientRect(  hDlg,  &rc  );
		 w  =  rc.right  -  rc.left;
		 h  =  rc.bottom  -  rc.top;

		 int	idc;

		 int  iX,  iY,  iW,  iH;
		 float  fx,  fy;
		 fx  =  1.  *  w  /  w_org;
		 fy  =  1.  *  h  /  h_org;

		 //
		 p->fx  =  fx;
		 p->fy  =  fy;


		 //
		 idc  =  p->iIDC_BUTTON_status;
		 rc  =  rcIDC_BUTTON_status;
		 iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		 iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
		 MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

		 idc  =  p->iIDCANCEL;
		 rc  =  rcIDCANCEL;
		 iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		 iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
		 MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

		 idc  =  p->iIDC_BUTTON_msg;
		 rc  =  rcIDC_BUTTON_msg;
		 iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		 iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
		 MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

		 idc  =  p->iIDC_BUTTON_task;
		 rc  =  rcIDC_BUTTON_task;
		 iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		 iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
		 MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

		 idc  =  p->iIDC_BUTTON_av;
		 rc  =  rcIDC_BUTTON_av;
		 iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		 iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
		 MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

		 idc  =  p->iIDC_BUTTON_op1;
		 rc  =  rcIDC_BUTTON_op1;
		 iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		 iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
		 MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

		 idc  =  p->iIDC_BUTTON_op0;
		 rc  =  rcIDC_BUTTON_op0;
		 iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
		 iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
		 MoveWindow(  GetDlgItem(  hDlg,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );  

		 //
		 {		
			 G_guiData_qyMc	*	pGuiData  =  (  G_guiData_qyMc  *  )g_getGuiData(  );

			 HWND	hList_msg  =  GetDlgItem(  hDlg,  p->iIDC_LIST_msg  );
			 HWND	hList_task  =  GetDlgItem(  hDlg,  p->iIDC_LIST_task  );

			 if  (  pGuiData->hFont_list_text  )  {
				 SendMessage(  hList_msg,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_list_text,  TRUE  );
			 }
			 if  (  pGuiData->hFont_list  )  {
				 SendMessage(  hList_task,  WM_SETFONT,  (  WPARAM  )pGuiData->hFont_list,  TRUE  );
			 }
		 }

errLabel:
		 return  0;



#endif 

}



INT_PTR CALLBACK dlgProc_talk_ce(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	void	*	pDlg	=	(  void  *  )GetWindowLong(  hDlg,  GWLP_USERDATA  );

	UNREFERENCED_PARAMETER(lParam);
	switch  (  message  ) {
		   	case  WM_INITDIALOG:
				  pDlg  =  (  void  *  )lParam;
				  //
				  setPage_talk_ce(  pDlg,  hDlg,  0  );
				  //
				  SetWindowLong(  hDlg,  GWLP_USERDATA,  (  LONG )pDlg  );
				  //
				  dlgLayout_talk_ce(   pDlg,  hDlg  );
				  //
				  myDialogProc_talk_ce(  pDlg,  hDlg,  message,  wParam,  lParam  );
				  return (INT_PTR)TRUE;

			case  WM_COMMAND:  {
				  WORD  wNotifyCode = HIWORD(wParam); 
				  WORD  wID			= LOWORD(wParam); 
				  HWND  hCtl		= (HWND) lParam;

				  DLG_guiData_talk  *  pGuiData  =  (  DLG_guiData_talk  *  )qyWnd_getGuiData(  pDlg  );

				  switch  (  wID  )  {
						  case  IDC_BUTTON_op0:
							    if  (  pGuiData->param.iPageType  ==  CONST_iPageType_msg  )  {
									if  (  DialogBox(  g_hInst,  MAKEINTRESOURCE(  IDD_input  ),  hDlg,  dlgProc_input  )  !=  IDOK  )  return  TRUE;
									procTalkTo(  hDlg,  g_inputBuf  );
									return   TRUE;
								}
							    break;
						  case  IDC_BUTTON_msg:
							    setPage_talk_ce(  pDlg,  hDlg,  CONST_iPageType_msg  );
								dlgTalk_bRefresh(  pDlg,  _T(  "dlgProc_talk_ce, IDC_BUTTON_msg"  )  );
								return  TRUE;
							    break;
						  case  IDC_BUTTON_task:  {
							    setPage_talk_ce(  pDlg,  hDlg,  CONST_iPageType_task  );
								dlgTalk_bRefresh(  pDlg,  _T(  "dlgProc_talk_ce,  IDC_BUTTON_task"  ),  FALSE,  TRUE  );
								}
								return  TRUE;
							    break;
						  case  IDC_BUTTON_av:
							    setPage_talk_ce(  pDlg,  hDlg,  CONST_iPageType_av  );
								dlgTalk_bRefresh(  pDlg,  _T(  "dlgProc_talk_ce, IDC_BUTTON_av"  )  );
								return  TRUE;
								break;
						  case  IDC_BUTTON_status:  {
							    DLG_guiDataParam_objs  param;
								memset(  &param,  0,  sizeof(  param  )  );
								param.uiType  =  0;
								if  (  showDlgObjs(  g_hInst,  hDlg,  &param  )  )  return  TRUE;

								talkToMessenger(  param.ui64Id_selected,  FALSE,  TRUE,  NULL  );
								}
								return  TRUE;
								break;
						  case  IDC_LIST_task:  {
							    int				nCurSel;

								nCurSel  =  SendMessage(  hCtl,  LB_GETCURSEL,  0,  0  );
								if  (  pGuiData->task.nCurSel  ==  nCurSel  )  break;
														    								
								dlgTalk_bRefresh(  pDlg,  _T(  "dlgProc_talk_ce, IDC_LIST_task"  ),  FALSE,  TRUE  );

								}
								return  TRUE;
							    break;
						  default:
								  break;
				 }
				 }
				 break;				  
			default:
					break;
	}


	if  (  myDialogProc_talk_ce(  pDlg,  hDlg,  message,  wParam,  lParam  )  )  return  TRUE;


	return (INT_PTR)FALSE;
}


void  *  newDlgTalk_ce(  HINSTANCE  g_hInst,  HWND  hParent,  DLG_guiDataParam_talk  *  pParam  )
{
	int			iErr	=	-1;
	void	*	pWnd	=	NULL;

	if  (  !pParam  )  return  NULL;

	pWnd  =  newQyWnd(  CONST_qyWndContentType_talker  );
	if  (  !pWnd  )  goto  errLabel;

	DLG_guiData_talk  *  p	=	(  DLG_guiData_talk  *  )qyWnd_getGuiData(  pWnd  );
	if  (  !p  )  goto  errLabel;

	memcpy(  &p->param,  pParam,  sizeof(  p->param  )  );

	p->iIDC_STATIC_peerDesc  =  IDC_STATIC_peerDesc;
	p->iIDC_STATIC_meDesc  =  IDC_STATIC_meDesc;
	p->iIDC_LIST_msg  =  IDC_LIST_msg;
	p->iIDC_LIST_task  =  IDC_LIST_task;
	//  p->iIDC_STATIC_taskStatus  =  IDC_STATIC_taskStatus;
	p->iIDC_BUTTON_status  =  IDC_BUTTON_status;
	p->iIDCANCEL  =  IDCANCEL;
	p->iIDC_BUTTON_msg  =  IDC_BUTTON_msg;
	p->iIDC_BUTTON_task  =  IDC_BUTTON_task;
	p->iIDC_BUTTON_av  =  IDC_BUTTON_av;
	p->iIDC_BUTTON_op1  =  IDC_BUTTON_op1;
	p->iIDC_BUTTON_op0  =  IDC_BUTTON_op0;

	p->pf_refreshDlg_talk_ce  =  refreshDlg_talk_ce;
	p->pf_sizeAllControls_talk_ce  =  sizeAllControls_talk_ce;
	p->pf_displayNotification_talk_ce  =  displayNotification_talk_ce;
	
	//
	if  (  !CreateDialogParam(  g_hInst,  MAKEINTRESOURCE(  IDD_talk_ce  ),  hParent,  dlgProc_talk_ce,  (  LPARAM  )pWnd  )  )  {
		OutputDebugString(  _T(  "DlgTalk_ce: CreateDialogParam failed\n"  )  );
		goto  errLabel;
	}
	p->bCreated  =  TRUE;

	if  (  !p->bInited  )  {	//  for ce, dialog should be inited in CreateDialogParam
		OutputDebugString(  _T(  "DlgTalk_ce::Create failed, not inited\n"  )  );

		//
		dlgTalk_bQuitDlg(  &pWnd,  TRUE  );

		goto  errLabel;
	}


	iErr  =  0;
errLabel:
	
	if  (  iErr  )  {
		if  (  pWnd  )  freeQyWnd(  pWnd  );
	}

	return  iErr  ?  NULL  :  pWnd;
}


