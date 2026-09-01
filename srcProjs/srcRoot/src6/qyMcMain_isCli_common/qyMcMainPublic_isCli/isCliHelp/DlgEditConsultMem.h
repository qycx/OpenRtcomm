#pragma once


// CDlgEditConsultMem dialog

class CDlgEditConsultMem : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgEditConsultMem)

public:
	CDlgEditConsultMem(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgEditConsultMem();

// Dialog Data
	enum { IDD = IDD_editConsultMem };
	
	//
	struct  {
		QY_MESSENGER_ID  idInfo_grp;
		QY_MESSENGER_ID  idInfo_mem;

	}		m_var;

	//
	BOOL  bSetInfo(  QY_MESSENGER_ID  *  pIdInfo_grp,  QY_MESSENGER_ID  *  pIdInfo_mem  );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
