#pragma once

//
#include	"qmcStruct_defs.h"


// CDlgMessengerIsClient dialog

class CDlgMessengerIsClient : public CDialog
{
	DECLARE_DYNAMIC(CDlgMessengerIsClient)

public:
	CDlgMessengerIsClient(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgMessengerIsClient();

// Dialog Data
	enum { IDD = IDD_messenger_isClient };

	struct				{
		MIS_CNT		*	pMisCnt;
	}					m_var;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
