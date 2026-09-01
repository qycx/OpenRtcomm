// qisGuiPublic.h : main header file for the qisGuiPublic DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CqisGuiPublicApp
// See qisGuiPublic.cpp for the implementation of this class
//

class CqisGuiPublicApp : public CWinApp
{
public:
	CqisGuiPublicApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
