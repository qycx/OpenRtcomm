#pragma once

#include	"qmcStruct_defs.h"

//  一开始运行就从服务器下载refresh_ImObjRulesReq
//  将rules信息更新在数据库中
//  每次修改，都发送refreshImObjRuleReq上去，从服务器得到成功的resp, 然后更新数据库和内存的qmem



#include	"dlgImObjRuleProc.h"


// CDlgImObjRule dialog
class CDlgImObjRule : public CDialog
{
	DECLARE_DYNAMIC(CDlgImObjRule)

public:
	CDlgImObjRule(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgImObjRule();

// Dialog Data
	enum { IDD = IDD_imObjRule };

	DLG_imObjRule_var					m_var;

	BOOL								bSetDlgInfo(  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  );
	BOOL								bSetDlgInfo(  HWND  hCurTalk  );


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedChecksharewebcaminconference();
	afx_msg void OnBnClickedButtonselectavcompressor();
};
