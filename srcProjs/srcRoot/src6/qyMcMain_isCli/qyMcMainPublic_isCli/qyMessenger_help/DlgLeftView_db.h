#pragma once


#include	"WallTalkers.h"
#include	"qyRcdset.h"
#include	"genericHash.h"

#include	"skinProc_mfc.h"


// CDlgLeftView_db dialog

class CDlgLeftView_db : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLeftView_db)

public:
	CDlgLeftView_db(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgLeftView_db();

// Dialog Data
	enum { IDD = IDD_leftView_db };

	
	struct		{

			//  2017/01/04
			//  QY_MC_mainWndVar		common;
			
			//
			int						iWndContentType;

			//
			CWnd			*		m_pParent;
			int						m_nID;
			//  BOOL							bInfoSet;
			BOOL					bCreated;					//  Create(  ) dlg(PostNcDestroy(  )delete)
			BOOL					bInited;					//  

			//
			int						iIDC_tree;

			//  2014/04/14
			LP_hashTbl				pHashTbl_tree;

			//
			HTREEITEM				htMyRootItem;		
			TCHAR					misServName[32  +  1];			//  这个值应该跟htMyRootItem关联。因为以后将有多个服务器，一个服务器相当与一个顶节点。服务器以misServName为键值，还可以定义各种显示名;
																//  服务器目前只有一个，并且为""值
		
			TCHAR					misServDisplayName[64  +  1];
			//
			BOOL					bInitialized;
			HTREEITEM				htInitialItem;
		
			QY_MC_DISPLAYCFG		m_displayCfg;
				
			////	
			MC_CTX_DISPLAYEDWND		displayCtx;		
			BOOL					bDisplayCtxInited;

	}								m_var;
	
	//
	CTreeCtrl					*	m_TreeCtrl;
	CImageList						m_ImageList;


	QY_MC_DOCSTRUCT					m_docStruct;
	CQyRcdset						m_rs;		
	CString							m_title;

	//
	SKIN_proc						m_skinProc;

	//
	BOOL  bSetQyMcDoc(  QY_MC_SEL  *  pSel  );
		 
	void  qySetTitle(  LPCTSTR  name  );
	
	//
	BOOL Create(const RECT& rect);
	BOOL  bQuitDlg(  );		

	//
#ifdef  __DEBUG__
		void  showItem(  HTREEITEM  htItem  );
#endif

	//
	BOOL	bInitialDisplay(  );
	BOOL	bDisplayContent(  );
	BOOL	bRefreshItem(  HTREEITEM  hItem  );
	

	virtual HTREEITEM GetLastItem( HTREEITEM hItem );
	virtual HTREEITEM GetNextItem( HTREEITEM hItem );
	virtual HTREEITEM GetPrevItem( HTREEITEM hItem );
	virtual HTREEITEM FindItem( CString &sSearch, BOOL bCaseSensitive = FALSE, BOOL bDownDir = TRUE, BOOL bWholeWord = FALSE, HTREEITEM hItem = NULL );
	virtual HTREEITEM FindItemData( DWORD lParam, BOOL bDownDir = TRUE, HTREEITEM hItem = NULL );
protected:
	virtual BOOL IsFindValid( HTREEITEM );
	BOOL bGetNodePath( HTREEITEM h, char *path, unsigned int size );
	BOOL bRootTreeGetSel(  CTreeCtrl &	treeCtrl,  HTREEITEM  hRoot,  HTREEITEM  hCur,  QY_MC_SEL  *pCurSel  );


	//
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnDestroy();

	//
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	//
	afx_msg  LRESULT  OnQyHotKey( WPARAM, LPARAM );
	afx_msg  LRESULT  OnQyComm( WPARAM, LPARAM );
	afx_msg  LRESULT  OnQyPostComm( WPARAM, LPARAM );
	afx_msg  LRESULT  OnQyTrayNotify( WPARAM, LPARAM );
	afx_msg  LRESULT  OnQyGraphNotify_mediaFile( WPARAM, LPARAM );
	afx_msg  LRESULT  OnQyGraphNotify_mediaDevice( WPARAM, LPARAM );


	//
	afx_msg void OnHelp();
	afx_msg void OnIsCmd(  UINT nID  );
	afx_msg void OnUpdateIsCmd(CCmdUI *pCmdUI);
	afx_msg void Onqysearch();
	//afx_msg void OnViewDebugStatus(  UINT nID  );
 	//afx_msg void OnUpdateViewDebugStatus(CCmdUI *pCmdUI);
	afx_msg void OnqyClearUp();
	afx_msg void OnUpdateqyClearUp(CCmdUI* pCmdUI);

	//
	virtual void PostNcDestroy();

	//
	afx_msg void OnTvnSelchangedimobjtree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickimobjtree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkimobjtree(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnBnClickedButtonfiletransfer();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcPaint();
};
