

#include	"stdafx.h"

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

//#include	"qyFile.h"

//#include	"myresource.h"

#include	"qmcVWall.h"
//  #include	"DlgDynBmps.h"

#include	"qyCusResTemp.h"

#include	"sp.h"

#include	"qmcConferenceWall.h"



#if  0	//  2012/05/06
 int  viewConferenceWall(  HWND  hDlg_org,  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  BOOL  bNewVirtualWall,  LPCTSTR  fileName,  HWND  *  phWnd_wall  )
{
	int						iErr			=		-1;
	QY_MC				*	pQyMc			=		QY_GET_GBUF(  );
	QY_SERVICEGUI_INFO	*	pSci			=		getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSci  )  return  -1;	
	MC_VAR_isCli			*	pProcInfo		=		(  MC_VAR_isCli  *  )pSci->pVar;
	if  (  !pProcInfo  )  return  -1;
	//  
	CDlgDynBmps			*	pDlg			=		NULL;
	RECT					rect;
	CWaitCursor				cur;

	//  int						i;
	MIS_CNT				*	pMisCnt			=		getMisCntByName(  pProcInfo,  misServName  );
	if  (  !pMisCnt  )  return  -1;
	int						iWndContentType	=		CONST_qyWndContentType_vWall;

	traceLogA(  "viewConferenceWall enters"  );

	if  (  !pIdInfo  )  return  -1;


	//  2010/08/30
	closeInstantAssistant(  hDlg_org  );


	//  为了将对远程的申请能及时取消，在dlgTalk里建立一个数组，方便对监控任务的跟踪，当监控窗口被关闭时，及时发现是监控任务，于是发消息给对方，要求不需要对方发数据过来了。
	//  应该先起监控窗口，在监控窗口里如有需要，可以启动talk窗口。然后，将监控窗口句柄放在msg里，填入监控任务数组。然后发送监控请求
	//  在这个函数里，需要先在talkers队列里，靠talk的数组去检索是否有这样窗口在。如果在，则激活。如果不在，才启动。


	//
	{
		unsigned  short		usCnt_monPics_row	=	1;
		unsigned  short		usCnt_monPics_col	=	1;
		//
		//
		unsigned  int  uiInitW  =  DEFAULT_uiInitW_wall;
		unsigned  int  uiInitH  =  DEFAULT_uiInitH_wall;
		//
		//  pDlg  =  new  CDlgDynBmps(  CWnd::GetDesktopWindow(  )  );
		pDlg  =  new  CDlgDynBmps(  CWnd::FromHandle(  hDlg_org  )  );
		if  (  !pDlg  )  goto  errLabel;

		TCHAR	talkerDesc[128]  =  _T(  ""  );
		QY_MESSENGER_REGINFO		regInfo;
		MY_REG_DESC					desc;
						
		if  (  !bGetMessengerRegInfoBySth(  pDb,  iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab,  misServName,  pIdInfo,  0,  &regInfo  )  )  memset(  &regInfo,  0,  sizeof(  regInfo  )  );
		regInfo2Desc(  0,  &regInfo,  &desc,  talkerDesc,  mycountof(  talkerDesc  ),  NULL,  0  );

		if  (  !pDlg->bSetDlgInfo(  iWndContentType,  0,  talkerDesc,  CONST_resId_menu_dlgVWall,  pMisCnt,  usCnt_monPics_row,  usCnt_monPics_col,  uiInitW,  uiInitH  )  )  goto  errLabel;
		pDlg->m_var.bUseDirectX  =  FALSE;
		
		pDlg->m_var.u.vWall.idInfo.ui64Id  =  pIdInfo->ui64Id;
		pDlg->m_var.u.vWall.ucbVideoConference  =  TRUE;
		pDlg->m_var.u.vWall.hDlg_org  =  hDlg_org;

		if  (  !pDlg->Create(  rect  )  )  goto  errLabel;		
		//
		if  (  bNewVirtualWall  )  {
			pDlg->Onstarttoedit(  );
			pDlg->Onstarttoshowrules(  );
			}
		else  {
			  pDlg->bEnableScrollBar(  FALSE  );		//  2009/08/06
			  //
			  pDlg->openFile(  fileName  );
		}

		//
		pDlg->ShowWindow(  SW_SHOW  );
		//

	}

	iErr  =  0;
errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}
	if  (  !iErr  )  {
		if  (  phWnd_wall  )  *phWnd_wall  =  pDlg->m_hWnd;
	}

	traceLogA(  "viewConferenceWall leaves with %s",  iErr  ?  "Failed"  :  "OK"  );

	return  iErr;
}
#endif



