#pragma once

#include	"qmcStruct_defs.h"

// CDlgMsgList dialog

class CDlgMsgList : public CDialog
{
	DECLARE_DYNAMIC(CDlgMsgList)

public:
	CDlgMsgList(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgMsgList();

// Dialog Data
	enum { IDD = IDD_msgList };

	struct								{
		DLG_guiData_msgList				guiData;

		//
		MIS_CNT						*	pMisCnt;
		QY_MESSENGER_ID					idInfo;
		//
		//
		QY_OBJ_DB					*	pObjDb;

		int								idcList;
		int								nFields;
		QY_COLUMNINFO				*	pColumns;
		
		QY_MC_QUERY						query;

	}									m_var;

	BOOL								bSetDlgInfo(  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  );
	int									listObjs(  );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonexport();
	afx_msg void OnBnClickedButtonclear();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnQyComm(  WPARAM  wParam,  LPARAM  lParam  );

};
