#pragma once

#include	"remoteStorageCfg.h"


// CDlgRemoteStorageSettings dialog

class CDlgRemoteStorageSettings : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRemoteStorageSettings)

public:
	CDlgRemoteStorageSettings(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgRemoteStorageSettings();

// Dialog Data
	enum { IDD = IDD_remoteStorageSettings };

	struct											{
			REMOTE_storage_cfg						cfg;
			
	}	m_var;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
