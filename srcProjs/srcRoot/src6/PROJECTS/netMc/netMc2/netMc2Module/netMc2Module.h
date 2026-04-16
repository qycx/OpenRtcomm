// netMc2Module.h : main header file for the NETMC2MODULE DLL
//

#if !defined(AFX_NETMC2MODULE_H__B2C45788_7B4D_4E07_83D9_FFA06EB4654E__INCLUDED_)
#define AFX_NETMC2MODULE_H__B2C45788_7B4D_4E07_83D9_FFA06EB4654E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNetMc2ModuleApp
// See netMc2Module.cpp for the implementation of this class
//

class CNetMc2ModuleApp : public CWinApp
{
public:
	CNetMc2ModuleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetMc2ModuleApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CNetMc2ModuleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETMC2MODULE_H__B2C45788_7B4D_4E07_83D9_FFA06EB4654E__INCLUDED_)
