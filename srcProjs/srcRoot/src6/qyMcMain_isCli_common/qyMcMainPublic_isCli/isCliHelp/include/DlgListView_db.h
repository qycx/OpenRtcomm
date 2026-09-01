#pragma once

//
#include	"qyRcdset.h"


// CDlgListView_db dialog

class CDlgListView_db : public CDialog
{
	DECLARE_DYNAMIC(CDlgListView_db)

public:
	CDlgListView_db(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgListView_db();

// Dialog Data
	enum { IDD = IDD_listView_db };

private:
	CImageList					m_LargeImageList;
	CImageList					m_SmallImageList;
public:

	struct		{

			CWnd					*		m_pParent;
			int								m_nID;
			//  BOOL							bInfoSet;
			BOOL							bCreated;					//  这个标志位用来表明是否Create(  )成功了。成功了，则将资源的释放留给了dlg自己(在PostNcDestroy(  )中delete)
			BOOL							bInited;					//  表明htmlEdit和对话都初始化完了.

			//
			int								iIDC_list;

			//
			int								iEdge_list_x;
			int								iEdge_list_y;

			//
			int					m_nItemSelected;
			int					m_nColSelected;
			BOOL				bDesc;
			PF_qyLvConvrtProc	data2DisplayProc;
			PF_qyLvConvrtProc	display2DataProc;


	}			m_var;



	QY_MC_DOCSTRUCT			m_docStruct;
	CQyRcdset				m_rs;		
	CString					m_title;

	//
	BOOL  bSetQyMcDoc(  QY_MC_SEL  *  pSel  );
	BOOL	bDocAvail(  );

	void					qySetTitle(  LPCTSTR  docName );
	BOOL					bSortData(  LPCTSTR  sortStr  );



	//
	BOOL Create(const RECT& rect);
	BOOL  bQuitDlg(  );		
	int  list(  );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
protected:
	virtual void PostNcDestroy();
public:
	afx_msg void OnLvnColumnclicklist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClicklist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnQyComm(  WPARAM  wParam,  LPARAM  lParam  );

	afx_msg void OnNMDblclklist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDestroy();
};
