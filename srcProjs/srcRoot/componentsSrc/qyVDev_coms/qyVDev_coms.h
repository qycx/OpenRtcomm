// qyVDev_coms.h : main header file for the QYVDEV_COMS DLL
//

#if !defined(AFX_QYVDEV_COMS_H__C55D4782_A99B_4BC9_8A05_A177FD85F4A6__INCLUDED_)
#define AFX_QYVDEV_COMS_H__C55D4782_A99B_4BC9_8A05_A177FD85F4A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CQyVDev_comsApp
// See qyVDev_coms.cpp for the implementation of this class
//

class CQyVDev_comsApp : public CWinApp
{
public:
	CQyVDev_comsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQyVDev_comsApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CQyVDev_comsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QYVDEV_COMS_H__C55D4782_A99B_4BC9_8A05_A177FD85F4A6__INCLUDED_)
