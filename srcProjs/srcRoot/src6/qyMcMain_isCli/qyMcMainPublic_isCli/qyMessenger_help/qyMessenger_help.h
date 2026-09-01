// qyMessenger_help.h : main header file for the qyMessenger_help DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CqyMessenger_helpApp
// See qyMessenger_help.cpp for the implementation of this class
//

class CqyMessenger_helpApp : public CWinApp
{
public:
	CqyMessenger_helpApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
