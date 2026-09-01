// secChkModule.h : main header file for the SECCHKMODULE DLL
//

#if !defined(AFX_SECCHKMODULE_H__57AD1DD4_9AEE_43CE_BCCF_652F269A0537__INCLUDED_)
#define AFX_SECCHKMODULE_H__57AD1DD4_9AEE_43CE_BCCF_652F269A0537__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSecChkModuleApp
// See secChkModule.cpp for the implementation of this class
//

class CSecChkModuleApp : public CWinApp
{
public:
	CSecChkModuleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSecChkModuleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CSecChkModuleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SECCHKMODULE_H__57AD1DD4_9AEE_43CE_BCCF_652F269A0537__INCLUDED_)
