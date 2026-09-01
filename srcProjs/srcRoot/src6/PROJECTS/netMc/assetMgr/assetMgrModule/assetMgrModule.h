// assetMgrModule.h : main header file for the ASSETMGRMODULE DLL
//

#if !defined(AFX_ASSETMGRMODULE_H__E35A472B_CF6A_43ED_AC40_6DF36672205E__INCLUDED_)
#define AFX_ASSETMGRMODULE_H__E35A472B_CF6A_43ED_AC40_6DF36672205E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAssetMgrModuleApp
// See assetMgrModule.cpp for the implementation of this class
//

class CAssetMgrModuleApp : public CWinApp
{
public:
	CAssetMgrModuleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAssetMgrModuleApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CAssetMgrModuleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASSETMGRMODULE_H__E35A472B_CF6A_43ED_AC40_6DF36672205E__INCLUDED_)
