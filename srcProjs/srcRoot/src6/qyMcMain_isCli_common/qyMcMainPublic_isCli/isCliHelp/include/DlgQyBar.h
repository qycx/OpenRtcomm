#pragma once




// CDlgQyBar dialog

class CDlgQyBar : public CDialog
{
	DECLARE_DYNAMIC(CDlgQyBar)

public:
	CDlgQyBar(HWND  hParent = NULL);   // standard constructor
	virtual ~CDlgQyBar();

// Dialog Data
	enum { IDD = IDD_qyBar };

	//
	struct					{
			
		//		
		int								iWndContentType;			//  2009/09/07			
		int								iSubtype;					//  2012/04/02

		//
		struct				{
			HWND			hParent;

			//
			HWND			hDlgWalls;		//  2012/05/24
		}					guiData;

		BOOL				bCreated;

		UINT_PTR			wTimerID;
		//
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
	afx_msg void OnBnClickedButtonmenu();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
protected:
	virtual void OnCancel();
};
