// qyStatusTool.h : main header file for the QYSTATUSTOOL application
//

#if !defined(AFX_QYSTATUSTOOL_H__344D5BDC_1F3C_4D46_B91E_710D33DE48AD__INCLUDED_)
#define AFX_QYSTATUSTOOL_H__344D5BDC_1F3C_4D46_B91E_710D33DE48AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CQyStatusToolApp:
// See qyStatusTool.cpp for the implementation of this class
//

typedef  struct  __myFilter_t		{
				 unsigned  long		ulClientIp0;
				 //unsigned  long	ulClientIp1;
				 TCHAR				filter0Buf[255  +  1];
				 TCHAR				filter1Buf[255  +  1];
				 TCHAR				contentFilter2Buf[255  +  1];
				 TCHAR				contentFilter3Buf[255  +  1];
}		 MY_filter;

//
typedef  struct  __myFilters_t		{
				 MY_filter			mems[6];
}		 MY_filters;



class CQyStatusToolApp : public CWinApp
{
public:
	CQyStatusToolApp();

	//  QY_STATUS_STRUCT	m_var;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQyStatusToolApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CQyStatusToolApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QYSTATUSTOOL_H__344D5BDC_1F3C_4D46_B91E_710D33DE48AD__INCLUDED_)
