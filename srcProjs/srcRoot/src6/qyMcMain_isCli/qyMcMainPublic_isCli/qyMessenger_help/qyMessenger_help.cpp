// qyMessenger_help.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "qyMessenger_help.h"

#include	"qyMcMainCommon.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

//

  __declspec(dllexport)  int   set_g_pQyMc_qyMessengerHelp(  void  *  pQyMc  )
{

#ifdef  __DEBUG__
		traceLog(  _T(  "set_g_pQyMc called"  )  );
#endif

	//  2013/07/31
//	set_g_pShowInfoStruct(  g_pQyMc->pShowInfoStruct  );


	return  0;
}

   __declspec(dllexport)  int   set_g_dbPool_qyMessengerHelp(  void  *  pPool  )
{
	if  (  CQnmDb::useDbPool(  (  QNM_db_pool  *  )pPool  )  )  return  -1;
	return  0;
 }


// CqyMessenger_helpApp

BEGIN_MESSAGE_MAP(CqyMessenger_helpApp, CWinApp)
END_MESSAGE_MAP()


// CqyMessenger_helpApp construction

CqyMessenger_helpApp::CqyMessenger_helpApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CqyMessenger_helpApp object

CqyMessenger_helpApp theApp;


 //  2012/12/21. 伪装的某些license函数
#ifdef  __isCli__
BOOL  bQnmDemo(  )
{
	return  FALSE;
}

int  getnMaxConns_netMc(  QY_LICENSE_CTX  *  pCtx  )
{
	return  0;
}

int  getnMaxConns_is(  QY_LICENSE_CTX  *  pCtx  )
{
	return  0;
}

unsigned  int	qnmMaxPcs(  QY_LICENSE_CTX  *  pCtx  )
{
	return  0;
}


#endif


 __declspec(  dllexport  )  BOOL  dll_PreTranslateMessage_qyMessengerHelp(  MSG  *  pMsg  )
{

	   AFX_MANAGE_STATE(AfxGetStaticModuleState());

	   return  theApp.PreTranslateMessage(  pMsg  );
}


 //  2013/06/10. 每个模块自己定义
 HINSTANCE  get_my_hInst(  )
{
	//QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	//return  pQyMc->g_hInst;
	return  theApp.m_hInstance;		//  2016/09/25
}


// CqyMessenger_helpApp initialization

BOOL CqyMessenger_helpApp::InitInstance()
{
	CWinApp::InitInstance();

	//  2013/07/26
	set_cur_iResId_sys(  CONST_resId_sys_qyMessengerHelp  );


	return TRUE;
}



 BOOL  bQyMcNewQueryView(  QY_MC_SEL  *  pSel  )
{
	 
	BOOL					bRet			=			FALSE;
	//
	QY_MC				*	pQyMc			=			QY_GET_GBUF(  );
	
	if  (  !pSel  )  goto  errLabel;
	if  (  pSel->type  !=  CONST_qySelType_mcQuery  )  goto  errLabel;
	if  (  !pSel->u.query.selectPart[0]  ||  !pSel->u.query.fromPart  )  goto  errLabel;
  
	if  (  viewDlgListView_db(  pQyMc->gui.hMainWnd,  0,  pSel  )  )  goto  errLabel;

	bRet  =  TRUE;

errLabel:

	return  bRet;

}

