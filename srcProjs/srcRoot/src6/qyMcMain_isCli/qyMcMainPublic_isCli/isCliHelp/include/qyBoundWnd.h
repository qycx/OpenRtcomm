//********************************************************************************
//* QyBoundWnd.CPP
//********************************************************************************

#if !defined(AFX_QYBOUNDWND_H__INCLUDED_)
#define AFX_QYBOUNDWND_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef  __WINCE__
	#include	<d3d9.h>
	//  #include	<d3dx9.h>
#endif
#include	"qyDynLib.h"
#include	"qyAvRecord.h"

class CQyBoundWnd : public CWnd
{

public:
	CQyBoundWnd();

	void CreateFlashing(LPCTSTR pTitle, RECT &rect);
	void SetUpRegion(int x, int y, int width, int height, int type);
	void SetUpRect(int x, int y, int width, int height);
	void PaintBorder(COLORREF colorval);
	void PaintInvertedBorder(COLORREF colorval);	
	void MoveRegion(int diffx, int diffy);
	void CheckRect(int diffx, int diffy);
	void UpdateRegionMove();
	void MakeFixedRegion(CRgn  &wndRgn, CRgn  &rgnTemp, CRgn  &rgnTemp2,CRgn  &rgnTemp3);


public:
	CRect			cRect;
	HRGN			oldregion;

	CRect			newRect;

	struct			{

		int			newRegionUsed;		//  = 0;
		int			readingRegion;		//  = 0;
		int			writingRegion;		//  = 0;
		int			settingRegion;		//  = 0;
		int			capturingRegion;	//  = 0;

		HCURSOR		cursorMove;			//  = NULL;
		POINT		startPoint;
		int			m_type;				//  = 0;
		int			m_startDrag;		//  = 0;

	}				m_var;



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQyBoundWnd)
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CQyBoundWnd();

protected:
	

	// Generated message map functions
protected:
	//{{AFX_MSG(CQyBoundWnd)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
