// qisGuiPublic.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"

//
#define  __noDbg_new__

//
#include "qisGuiPublic.h"

//
#include	"qyCommon.h"
//#include	"qyMcMainCommon.h"
#include	"qyLangCommProc.h"
#include	"qnmResDefs.h"


//
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


//  2015/06/28
  __declspec(dllexport)  int   set_g_pQnmCusResInfo_qisGuiPublic(  void  *  pQnmCusResInfo  )
  {
	  set_cur_pQnmCusResInfo(  pQnmCusResInfo  );

	  return  0;
  }




// CqisGuiPublicApp

BEGIN_MESSAGE_MAP(CqisGuiPublicApp, CWinApp)
END_MESSAGE_MAP()


// CqisGuiPublicApp construction

CqisGuiPublicApp::CqisGuiPublicApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CqisGuiPublicApp object

CqisGuiPublicApp theApp;


// CqisGuiPublicApp initialization

BOOL CqisGuiPublicApp::InitInstance()
{
	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	//  2015/07/02
	set_cur_iResId_sys(  CONST_resId_sys_qisGuiPublic  );


	return TRUE;
}
