#if !defined(AFX_DLGQNMEDITPCUSRINFO_H__3AFE6C72_9979_45BE_ACB8_F7D863574947__INCLUDED_)
#define AFX_DLGQNMEDITPCUSRINFO_H__3AFE6C72_9979_45BE_ACB8_F7D863574947__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmEditPcUsrInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmEditPcUsrInfo dialog

class CDlgQnmEditPcUsrInfo : public CDialog
{
// Construction
public:
	CDlgQnmEditPcUsrInfo(CWnd* pParent = NULL);   // standard constructor

	struct									{
		QRT_LAYOUT_CFG						layout;
		//
		unsigned  char						ucbChanged;
		QY_OBJ_DB						*	pObjDb;

		int									iObjType;

		union								{
			struct							{
				char						mac0[CONST_qyMacLen  +  1];
				//
				QNM_REG_INFO				regInfo;
			}								pc;
			struct							{
                TCHAR						misServName[CONST_maxMisServNameLen  +  1];
				MSGR_ADDR					addr;
				int							id;
				//
				QY_MESSENGER_REGINFO		regInfo;
			}								messenger;
		}									u;

		unsigned  char						ucbInTab1;

	}										m_var;

	BOOL  bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  int  iObjType,  char  *  mac,  unsigned  char  ucbInTab1  );
	BOOL  bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  int  iObjType,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  char  ucbInTab1  );
	BOOL  bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  MSGR_ADDR  *  pAddr,  int  id,  unsigned  char  ucbInTab1  );


// Dialog Data
	//{{AFX_DATA(CDlgQnmEditPcUsrInfo)
	enum { IDD = IDD_qnmEditPcUsrInfo };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmEditPcUsrInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmEditPcUsrInfo)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeCombo0();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnSelchangeCombo2();
	afx_msg void OnSelchangeCombo3();
	afx_msg void OnSelchangeCombo4();
	//}}AFX_MSG
	afx_msg LRESULT OnQyComm(  WPARAM  wParam,  LPARAM  lParam  );
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMEDITPCUSRINFO_H__3AFE6C72_9979_45BE_ACB8_F7D863574947__INCLUDED_)
