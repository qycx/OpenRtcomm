// isCliHelp.h : main header file for the isCliHelp DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CisCliHelpApp
// See isCliHelp.cpp for the implementation of this class
//

class CisCliHelpApp : public CWinApp
{
public:
	CisCliHelpApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};
