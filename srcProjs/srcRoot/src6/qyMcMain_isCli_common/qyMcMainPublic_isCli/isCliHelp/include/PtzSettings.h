#pragma once
#include "afxwin.h"

#include	"comPortCfg.h"

// CPtzSettings dialog

class CPtzSettings : public CDialog
{
	DECLARE_DYNAMIC(CPtzSettings)

public:
	CPtzSettings(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPtzSettings();

// Dialog Data
	enum { IDD = IDD_ptzSettings };

	struct				{
		COM_PORT_cfg	cfg;
		TCHAR			memoBuf[256];

	}					m_var;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

public:
	CComboBox m_combo_protocolType;
	CEdit m_edit_addrCode;
	//
	CComboBox m_combo_name;
	CComboBox m_combo_rate;
	CComboBox m_combo_parity;
	CComboBox m_combo_data;
	CComboBox m_combo_stopBit;
	afx_msg void OnBnClickedOk();
	CEdit m_edit_remotePtzUsers;
	CEdit m_edit_memoAppending;
};
