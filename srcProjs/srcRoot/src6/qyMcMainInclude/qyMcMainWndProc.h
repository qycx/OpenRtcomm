
#ifndef  __QYMCMAINWNDPROC_H__
#define  __QYMCMAINWNDPROC_H__	//  {


//
typedef  struct 
{
	bool bExists_task;
	bool bAvCall;
	//
	//int index_taskInfo;
	int  iTaskId;

	//
	//public NotifyTaskStatus_curNotify curNotify;

	//
	HWND	hTool_dlgAvAccept;

	//
} NOTIFY_task_status;

//
typedef  struct
{
	
	//
	HWND	hTool_dlgHintAccept;

	//
} HINT_task_status;


typedef  struct  __qyMcMainWndVar_t							{								//  2010/04/13
				 QY_MC						*				pQyMc;							//  2016/09/21
				 //  void						*				pProcInfo;

				 //
				 UINT										uiTimerId;
		
				 //
				 MIS_MSGU					*				pMsgBuf_msgArrive;				//  2009/12/10

				 #ifdef  __useMfc__
						  CStatusBar		*				pm_wndStatusBar;
				 #endif

				 WND_guiData_main							guiData;

				 //
				 NOTIFY_task_status							notifyTaskStatus;
				 
				 //
				 HINT_task_status                           hintTaskStatus;

				 //
				 unsigned  char								ucbVisible;						//  2012/07/17

				 //
				 int										loopCtrl;


}		QY_MC_mainWndVar;


int mainWnd_OnQyPostComm(  HWND  hMainWnd,  void  *  pVar,  UINT  wParam,  LONG  lParam  );
LRESULT mainWnd_OnQyGraphNotify_mediaDevice(  QY_MC  * pQyMc,  HWND  hMainWnd,  void  *  pVar,  WPARAM  wParam,  LPARAM  lParam  );
//int  mainWnd_OnQyShowMainWnd(  HWND  hMainWnd  );

int  dlgAbout_OnInitDialog_qyMc(  HWND  hDlg,  int  iIDD  );

BOOL  bViewActiveImObjList(  );


#endif


