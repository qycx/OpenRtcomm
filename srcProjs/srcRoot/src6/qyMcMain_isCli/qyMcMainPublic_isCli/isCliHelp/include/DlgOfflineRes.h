#pragma once


#include  "dlgOfflineResProc.h"


//





// CDlgOfflineRes dialog

class CDlgOfflineRes : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOfflineRes)

public:
	CDlgOfflineRes(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgOfflineRes();

// Dialog Data
	enum { IDD = IDD_offlineRes };

	//
	DlgOfflineRes_var	m_var;


	//
	BOOL  bSetDlgInfo(  int  iWndContentType,  int  iSubType,  LPCTSTR  title  );


	//
	BOOL Create(const RECT& rect);
	BOOL  bQuitDlg(  );		
	int  sizeAllControls(  );
	
	//
	BOOL  bRefresh(  );
	int  getDisplayStr_res_retrieved(  RES_inProcess  *  pMem,  TCHAR  *  tBuf,  int  cnt  );
	int  getDisplayStr_res_beingProced(  RES_inProcess  *  pMem,  TCHAR  *  tBuf,  int  cnt  );
	BOOL  bDisplay(  );
	BOOL  bRefreshBtns(  );
	BOOL  bDisplay_usIndex_page(  );



	//
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	afx_msg void OnClose();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnQyComm(  WPARAM, LPARAM  );

	afx_msg void OnBnClickedButtonupload();
	afx_msg void OnBnClickedButtondownload();
	afx_msg void OnBnClickedButtonrefresh();
	afx_msg void OnBnClickedButtondelete();
	afx_msg void OnBnClickedButtonshowalldownloads();
	afx_msg void OnNMClickListofflineres(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListofflineres(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonpage1();
	afx_msg void OnBnClickedButtonnextpage();
	afx_msg void OnBnClickedButtonprevpage();
	afx_msg void OnBnClickedButtongo();
	afx_msg void OnEnChangeEditfilterkeywords();
	afx_msg void OnBnClickedCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
