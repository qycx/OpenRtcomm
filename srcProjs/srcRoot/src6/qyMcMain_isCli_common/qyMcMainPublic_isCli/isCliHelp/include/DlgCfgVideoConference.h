#if !defined(AFX_DLGCFGVIDEOCONFERENCE_H__74F64EE1_F718_4570_9A18_FB9E53F81078__INCLUDED_)
#define AFX_DLGCFGVIDEOCONFERENCE_H__74F64EE1_F718_4570_9A18_FB9E53F81078__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCfgVideoConference.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgVideoConference dialog



class CDlgCfgVideoConference : public CDialog
{
// Construction
public:
	CDlgCfgVideoConference(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCfgVideoConference)
	enum { IDD = IDD_cfgVideoConference };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct						{

		VIDEO_CONFERENCE_CFG	videoConferenceCfg;

	}							m_var;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCfgVideoConference)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCfgVideoConference)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCFGVIDEOCONFERENCE_H__74F64EE1_F718_4570_9A18_FB9E53F81078__INCLUDED_)
