#pragma once

//  #include	"qyMcDoc.h"
#include	"myresource.h"

// CDlgListView dialog

class CDlgListView : public CDialog
{
	DECLARE_DYNAMIC(CDlgListView)

public:
	CDlgListView(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgListView();

// Dialog Data
	enum { IDD = IDD_listView };

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
			int								iTop_list;

			//
			int								m_nItemSelected;
			int								m_nColSelected;
			BOOL							bDesc;
			//  PF_qyLvConvrtProc				data2DisplayProc;
			//  PF_qyLvConvrtProc				display2DataProc;


	}										m_var;



	QY_MC_DOCSTRUCT			m_docStruct;
	//  CQyRcdset				m_rs;		
	CString					m_title;

	//
	BOOL  bSetQyMcDoc(  QY_MC_SEL  *  pSel  );
	BOOL	bDocAvail(  );

	void					qySetTitle(  LPCTSTR  docName );


	//
	BOOL Create(const RECT& rect);
	BOOL  bQuitDlg(  );		

	BOOL	bDisplayContent(  );


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
protected:
	virtual void PostNcDestroy();
};
