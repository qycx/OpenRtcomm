#if !defined(AFX_DLGPROPMESSENGER_H__A7EB2884_F101_4C9C_B4FE_8F03CDFFFAA4__INCLUDED_)
#define AFX_DLGPROPMESSENGER_H__A7EB2884_F101_4C9C_B4FE_8F03CDFFFAA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPropMessenger.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPropMessenger dialog

class CDlgPropMessenger : public CDialog
{
// Construction
public:
	CDlgPropMessenger(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPropMessenger)
	enum { IDD = IDD_prop_messenger };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct  {
			QY_OBJ_DB						*	pObjDb;
			int									iObjType;

			union								{
				struct							{
					MSGR_ADDR					addr;
					//
					QY_MESSENGER_INFO			info;
					QY_MESSENGER_REGINFO		regInfo;

				}								messenger;



			}									u;

	}											m_var;

	BOOL  bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  int  iObjType,  QY_MESSENGER_ID  *  pIdInfo  );
	BOOL  bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  MSGR_ADDR  *  pAddr  );



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPropMessenger)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPropMessenger)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROPMESSENGER_H__A7EB2884_F101_4C9C_B4FE_8F03CDFFFAA4__INCLUDED_)
