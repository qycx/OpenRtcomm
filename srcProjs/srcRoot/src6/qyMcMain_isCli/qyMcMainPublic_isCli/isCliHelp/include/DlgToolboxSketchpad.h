#pragma once

#include	"ctxQmc.h"

// CDlgToolboxSketchPad dialog

#define		CONST_toolbox_btns			10

class CDlgToolboxSketchPad : public CDialog
{
	DECLARE_DYNAMIC(CDlgToolboxSketchPad)

public:
	CDlgToolboxSketchPad(HWND hParent = NULL);   // standard constructor
	virtual ~CDlgToolboxSketchPad();

// Dialog Data
	enum { IDD = IDD_toolbox_sketchPad };

	struct									{
			MC_VAR_isCli				*	pProcInfo;
			
			HWND							m_hParent;
			void						*	m_pParentVar;		//  2013/06/10

			BOOL							bCreated;

			//  UINT_PTR					wTimerID;

			HBITMAP							hBmp_btns[CONST_toolbox_btns];
			unsigned  short					usCnt_btns;

	}										m_var;

#ifndef  __WINCE__
	CToolTipCtrl							m_toolTips[CONST_toolbox_btns];
#endif

	BOOL Create(const RECT& rect);
	int	refreshBtns(  );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnCancel();
public:
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedCheckselect();
	afx_msg void OnBnClickedCheckrectangle();
	afx_msg void OnBnClickedCheckpoint();
	afx_msg void OnBnClickedChecksegment();
	afx_msg void OnBnClickedCheckcircle();
	afx_msg void OnClose();
};
