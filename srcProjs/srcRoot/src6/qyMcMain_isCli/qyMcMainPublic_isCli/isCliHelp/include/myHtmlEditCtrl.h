

#ifndef  __MYHTMLEDITCTRL_H__
#define  __MYHTMLEDITCTRL_H__	//  {


class  CMyHtmlEditCtrl:public  CHtmlEditCtrl
{
public:
	CMyHtmlEditCtrl(  );
	virtual  ~CMyHtmlEditCtrl(  );

	DECLARE_DYNCREATE(  CMyHtmlEditCtrl  )

	virtual BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, int nID, CCreateContext *pContext=NULL);

	virtual  LPCTSTR  GetStartDocument(  );

	BOOL				m_bDesignMode;

	CDropTarget			m_dropTarget;
	
	unsigned  int		m_uiType;					//		用来指名控件的用途,  2007/05/25
	BOOL				m_bDisplayInited;			//		显示了隐含的table, 才算显示初始化完毕
	
	//
	int					m_iWndContentType_hParent;	//  2014/01/25

private:
	CString				m_strHtmlAbout;
	//
	BOOL				m_bInited;
	
protected:
	
	DECLARE_MESSAGE_MAP(  )
	DECLARE_EVENTSINK_MAP(  )


	void _OnBeforeNavigate2(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Flags, VARIANT FAR* TargetFrameName, VARIANT FAR* PostData, VARIANT FAR* Headers, BOOL FAR* Cancel);
	void  _OnNavigateComplete2(  LPDISPATCH,  VARIANT  *  URL  );
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	
//
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

typedef  class  CMyHtmlEditCtrl  *		LP_MyHtmlEditCtrl;

BOOL  bQmInternalUrl(  LPCTSTR  url  );
int  insertCell(  void  *  pIHTMLTableRow,  int  i,  LPCTSTR  pCssTag,  LPCTSTR  tId,  LPCTSTR  pContent,  BOOL  bScrollIntoView,  TCHAR  *  tTxtBuf,  unsigned  int  tTxtBufCnt  );


int  initHtmlDisplay(  void  *  pIHTMLDocument2,  CString  strInfo  );





#endif


