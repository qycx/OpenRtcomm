#if !defined(AFX_QYRESTRICTEDIT_H__C8B136BD_B5B8_4C8B_AEC4_4FC7FC3811F0__INCLUDED_)
#define AFX_QYRESTRICTEDIT_H__C8B136BD_B5B8_4C8B_AEC4_4FC7FC3811F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QyRestrictEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQyRestrictEdit window
#define		QY_EDITTYPE_NUM				(  1	     )
#define		QY_EDITTYPE_UINT			(  1  <<  1  )
#define		CONST_qyEditType_custom		(  1  <<  2  )


//  对下面的hookProc, 返回0表允许, 其他不允许   
typedef  int  (  *  QY_INPUT_HOOKPROC  )(  UINT nChar, UINT nRepCnt, UINT nFlags,  void  *  p  );

class CQyRestrictEdit : public CEdit
{
// Construction
public:
	CQyRestrictEdit();
	CQyRestrictEdit(  int  type  );

// Attributes
public:
	struct	{
		int							type;
		int							flg;
		QY_INPUT_HOOKPROC			inputProc;
	}								var;

// Operations
public:
	int  setType(  int  type  );
	int	 setType(  int  type,  int  flg,  QY_INPUT_HOOKPROC  hookProc  );
	void  OnUINTChar(  UINT  nChar,  UINT  nRepCnt,  UINT  nFlags  );		//  只允许0-9的输入
	void  OnCustomChar(  UINT  nChar,  UINT  nRepCnt,  UINT  nFlags  );		//  自定义的输入校验


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQyRestrictEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CQyRestrictEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CQyRestrictEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QYRESTRICTEDIT_H__C8B136BD_B5B8_4C8B_AEC4_4FC7FC3811F0__INCLUDED_)
