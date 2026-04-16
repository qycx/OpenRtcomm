#pragma once


// CDlgStatusCli dialog

typedef  struct  __status_qList_mem_t				{
				 void						*		pQ;			
				 unsigned  int						uiMaxQNodes;
				 int								iNodes0,  iNodes1;		
				 //
}		 STATUS_qList_mem;

typedef  struct  __status_qList_t					{
				 unsigned  int						uiType;
				 unsigned  short					usCnt;
				 STATUS_qList_mem					mems[256];
}		 STATUS_qList;


typedef  struct							{
			CWnd					*		m_pParent;
			int								m_nID;
			BOOL							bInfoSet;
			BOOL							bCreated;					//  这个标志位用来表明是否Create(  )成功了。成功了，则将资源的释放留给了dlg自己(在PostNcDestroy(  )中delete)
			BOOL							bInited;					//  表明htmlEdit和对话都初始化完了.

			//
			int								iWndContentType;
			int								iWndContentSubType;
			//
			TCHAR							title[64];
			int								iResId_listColumns;
			//
			PF_commonHandler				pfInitDisplayListContent;						//  显示右边的listView, 2004/07/27
			PF_commonHandler				pfDisplayListContent;							//  显示右边的listView, 2014/04/19
			
			//
			union							{
				unsigned  int				uiType;
				STATUS_qList				qList;
			}								u;

			int								iEdge_list_x;
			int								iTop_list;


}			DLG_statusCli_var;


class CDlgStatusCli : public CDialog
{
	DECLARE_DYNAMIC(CDlgStatusCli)

public:
	CDlgStatusCli(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgStatusCli();

// Dialog Data
	enum { IDD = IDD_status_cli };

	DLG_statusCli_var						m_var;

	//
	BOOL  bSetDlgInfo(  int  iWndContentType,  int  iSubType,  LPCTSTR  title,  int  iResId_listColumns,  PF_commonHandler  pfInitDisplayListContent,  PF_commonHandler  pfDisplayListContent  );


	//
	BOOL Create(const RECT& rect);
	BOOL  bQuitDlg(  );		
	int  sizeAllControls(  );
	int  listClientStatus(  );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


	virtual  afx_msg LRESULT OnQyPostComm(  WPARAM, LPARAM  );
	DECLARE_MESSAGE_MAP()
public:
protected:
	virtual void PostNcDestroy();
public:
	afx_msg void OnClose();

	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonupdatedynbmplist();
};
