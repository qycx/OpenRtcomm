#pragma once


// CDlgQyMenu dialog

class CDlgQyMenu : public CDialog
{
	DECLARE_DYNAMIC(CDlgQyMenu)

public:
	CDlgQyMenu(HWND  hParent = NULL);   // standard constructor
	virtual ~CDlgQyMenu();

// Dialog Data
	enum { IDD = IDD_qyMenu };

	struct					{
		struct				{
			HWND			hParent;
		}					guiData;

		BOOL				bCreated;
    struct					{
		int					iEdge_t;
		int					iEdge_l;
		
		int					iW_btn,  iH_btn;

		int					iX_spacing;
		int					iY_spacing;

		int					iW_dlg,  iH_dlg;

	    }					oldLayout;

		DWORD				dwTickCnt_lastMouseMove;

	}						m_var;

public:
	BOOL	Create(const RECT& rect);
	BOOL	bQuitDlg(  );



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
protected:
	virtual void OnCancel();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
