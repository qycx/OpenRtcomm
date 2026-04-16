#pragma once


#include	"dlgAvResCommon.h"



// CDlgAvRes dialog

class CDlgAvRes : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAvRes)

public:
	CDlgAvRes(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgAvRes();

// Dialog Data
	enum { IDD = IDD_avRes };

	

	//
	DLG_avRes_var		m_var;

	//
	CDropTree						m_dropTree;
	CTreeCtrl					*	m_TreeCtrl;
	CImageList						m_ImageList;


	//
	virtual  BOOL  	bQuitDlg(  );
	
	BOOL			Create(const RECT& rect);


	//
		BOOL	bInitialDisplay(  );
	int  resetRootItems(  );
	BOOL	bDisplayContent(  );
	BOOL	bRefreshItem(  HTREEITEM  hItem  );

	int   proc_applyForOrgReq(  IM_GRP_EX  *  p,  QY_MESSENGER_ID  *  pIdInfo_from  );
	 int  refreshAvResGrpInfo(  IM_GRP_EX  *  p  );
	 int  refreshAvResCallStatus(  );

	 int  getCallStatus(  BOOL  *  pbConfStarted,  BOOL  *  pbCanSpeak,  BOOL  *  pbConnStarted  );


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombogrp();
	afx_msg void OnTvnBegindragavrestree(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnCbnSelchangeCombolayout();
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnBnClickedButtonav();
	afx_msg void OnBnClickedButtoncfgconf();
	afx_msg void OnBnClickedButtoncall();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNMRClickavrestree(NMHDR *pNMHDR, LRESULT *pResult);
};
