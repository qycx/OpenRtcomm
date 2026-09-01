#pragma once


//
typedef  struct  __stateGrp_t			{
				 QY_MESSENGER_ID		idInfo;
				 int					m_cnt;
				 //
				 SYSTEMTIME				m_when;
				 int					m_last_iPos;

}		 STATE_grp;


//
typedef  struct  __dlgStateVar_t		{
				 unsigned  short		m_usStateType;
				 HWND					m_hParent;

				 //
				 int					iEdge_list_x;
				 int					iTop_list;

				 //
				 int					m_grp_maxCnt;
				 //
				 STATE_grp				grps[10];

				 //
				 int					m_maxCnt;
				 QY_SHOW_STRUCT		*	m_pShowStructs;
				 

				 //
				 CListCtrl			*	m_pListCtrl;



}  DLG_state_var;

// CDlgState 对话框

class CDlgState : public CDialog
{
	DECLARE_DYNAMIC(CDlgState)

public:
	CDlgState(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgState();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_state };
#endif


	//
public:
	DLG_state_var		m_var;


	//
	virtual  BOOL  	bQuitDlg();

	BOOL			Create(const RECT& rect);

	//
	int resetItem(int nItem);
	//
	int procShowInfo(QY_SHOW_STRUCT* pShowStruct);



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	afx_msg LRESULT OnQyComm(WPARAM  wParam, LPARAM  lParam);
	afx_msg LRESULT OnQyPostComm(WPARAM  wParam, LPARAM  lParam);

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	afx_msg void OnClose();
	virtual void OnCancel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
};
