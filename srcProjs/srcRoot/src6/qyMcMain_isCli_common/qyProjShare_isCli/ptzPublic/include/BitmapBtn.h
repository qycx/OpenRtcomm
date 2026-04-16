#pragma  once

class  CZBitmap : public CBitmapButton
{
public:
	CZBitmap(  );
	virtual  ~CZBitmap(  );

private:
	BOOL  m_bDown;
	CToolTipCtrl  m_toolTip;

protected:
	//  {{  AFX_MSG(  CZBITMAP  )
	virtual  BOOL  PreTranslateMessage(  MSG  *  pMsg  );
	//  }}AFX_MSG

	DECLARE_MESSAGE_MAP(  )

private:
	void  initToolTip(  );
public:
	void  setToolTipText(  int  nText,  BOOL  bActivate  =  TRUE  );
	void  setToolTipText(  LPCTSTR  lpszText,  BOOL  bActivate  =  TRUE  );
	void  activateToolTip(  BOOL  bEnable  =  TRUE  );

public:
	afx_msg  void  OnLButtonDown(  UINT  nFlags,  CPoint  point  );
	afx_msg  void  OnLButtonUp(  UINT  nFlags,  CPoint  point  );
};