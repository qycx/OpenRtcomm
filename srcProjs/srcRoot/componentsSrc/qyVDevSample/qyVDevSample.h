// qyVDevSample.h : main header file for the QYVDEVSAMPLE application
//

#if !defined(AFX_QYVDEVSAMPLE_H__B9A24FFE_EBFA_48BC_A89E_D5EE6E22C409__INCLUDED_)
#define AFX_QYVDEVSAMPLE_H__B9A24FFE_EBFA_48BC_A89E_D5EE6E22C409__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CQyVDevSampleApp:
// See qyVDevSample.cpp for the implementation of this class
//

class CQyVDevSampleApp : public CWinApp
{
public:
	CQyVDevSampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQyVDevSampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CQyVDevSampleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QYVDEVSAMPLE_H__B9A24FFE_EBFA_48BC_A89E_D5EE6E22C409__INCLUDED_)
