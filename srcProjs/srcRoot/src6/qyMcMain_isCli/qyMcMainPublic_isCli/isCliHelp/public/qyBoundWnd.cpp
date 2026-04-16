//********************************************************************************
//* QyBoundWnd.CPP
//*
//********************************************************************************

#include	"stdafx.h"
#include	"qyCommon.h"
#include	"QyBoundWnd.h"

#include <assert.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*
#define		THICKNESS			8
#define		SMALLTHICKNESS		4
#define		SIDELEN				12
#define		SIDELEN2			24
*/

#define		THICKNESS			3
#define		SMALLTHICKNESS		2


//ver 1.8




//********************************************************************************
//* Constructor
//********************************************************************************

CQyBoundWnd::CQyBoundWnd()
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );

	m_var.cursorMove=::LoadCursor(NULL,IDC_SIZEALL);
}


//********************************************************************************
//* Destructor
//********************************************************************************

CQyBoundWnd::~CQyBoundWnd()
{
	if (m_var.cursorMove) DeleteObject(m_var.cursorMove);
}


BEGIN_MESSAGE_MAP(CQyBoundWnd, CWnd)
	//{{AFX_MSG_MAP(CQyBoundWnd)
	ON_WM_ERASEBKGND()		
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//********************************************************************************
//* CreateFlashing()
//*
//* Creates the main application window Flashing
//********************************************************************************

void CQyBoundWnd::CreateFlashing(LPCTSTR pTitle, RECT &rect)
{
	BOOL  bRet  =  FALSE;
	bRet  =  CreateEx(	WS_EX_TOPMOST  ,
						AfxRegisterWndClass(0,LoadCursor(NULL, IDC_ARROW)),						
						pTitle,
						WS_POPUP ,
						rect,
						NULL,
						NULL,
						NULL );

	oldregion = NULL;

}


//********************************************************************************
//* SetupRegion()
//*
//* Set the Window Region for transparancy outside the mask region
//********************************************************************************
void CQyBoundWnd::SetUpRegion(int x, int y, int width, int height, int type)
{

	CRgn  wndRgn, rgnTemp, rgnTemp2,rgnTemp3;

		
	cRect.left= x;
	cRect.top= y;
	cRect.right = cRect.left + width -1;
	cRect.bottom = cRect.top + height -1;	

	/*
	if (type == 0) {

		wndRgn.CreateRectRgn(0,0, cRect.Width()+THICKNESS+THICKNESS, cRect.Height()+THICKNESS+THICKNESS);
		rgnTemp.CreateRectRgn(THICKNESS, THICKNESS, cRect.Width()+THICKNESS+1, cRect.Height()+THICKNESS+1);
		rgnTemp2.CreateRectRgn(0, SIDELEN2, cRect.Width()+THICKNESS+THICKNESS, cRect.Height()-SIDELEN+1);
		rgnTemp3.CreateRectRgn(SIDELEN2,0, cRect.Width()-SIDELEN+1, cRect.Height()+THICKNESS+THICKNESS);
	
		wndRgn.CombineRgn(&wndRgn,&rgnTemp,RGN_DIFF);
		wndRgn.CombineRgn(&wndRgn,&rgnTemp2,RGN_DIFF);
		wndRgn.CombineRgn(&wndRgn,&rgnTemp3,RGN_DIFF);

		wndRgn.OffsetRgn( cRect.left-THICKNESS, cRect.top-THICKNESS );	

	}
	*/
	//  else 
	{

		wndRgn.CreateRectRgn(0,0, cRect.Width()+SMALLTHICKNESS+SMALLTHICKNESS, cRect.Height()+SMALLTHICKNESS+SMALLTHICKNESS);
		rgnTemp.CreateRectRgn(SMALLTHICKNESS, SMALLTHICKNESS, cRect.Width()+SMALLTHICKNESS+1, cRect.Height()+SMALLTHICKNESS+1);

		wndRgn.CombineRgn(&wndRgn,&rgnTemp,RGN_DIFF);

		wndRgn.OffsetRgn( cRect.left-SMALLTHICKNESS, cRect.top-SMALLTHICKNESS );	

	}		
	
	HRGN newregion = (HRGN) wndRgn.Detach();
	SetWindowRgn((HRGN) newregion, TRUE); 
	
	if (oldregion) DeleteObject(oldregion);
	oldregion = newregion;

}


void CQyBoundWnd::SetUpRect(int x, int y, int width, int height)
{		
	cRect.left= x;
	cRect.top= y;
	cRect.right = cRect.left + width -1;
	cRect.bottom = cRect.top + height -1;
	
}

//********************************************************************************
//* CQyBoundWnd message handlers
//********************************************************************************


void CQyBoundWnd::PaintBorder(  COLORREF  colorval  )
{

	// Add your drawing code here!
	HDC hdc = ::GetDC(m_hWnd);
	if ((cRect.right>cRect.left) && (cRect.bottom>cRect.top)) {	
		
		HBRUSH newbrush = (HBRUSH) CreateSolidBrush( colorval);
		HBRUSH newpen = (HBRUSH) ::CreatePen(PS_SOLID,1, colorval);
		HBRUSH oldbrush = (HBRUSH) SelectObject(hdc,newbrush);
		HBRUSH oldpen = (HBRUSH) SelectObject(hdc,newpen);

		
		Rectangle(hdc,cRect.left-THICKNESS,cRect.top-THICKNESS,cRect.right+THICKNESS,cRect.bottom+THICKNESS); 
		
		SelectObject(hdc,oldpen);
		SelectObject(hdc,oldbrush);
		DeleteObject(newpen);	
		DeleteObject(newbrush);	

	}
   
	::ReleaseDC(m_hWnd,hdc);
}


void CQyBoundWnd::PaintInvertedBorder(COLORREF colorval)
{

	// Add your drawing code here!
	HDC hdc = ::GetDC(m_hWnd);
	if ((cRect.right>cRect.left) && (cRect.bottom>cRect.top)) {	
		
		HBRUSH newbrush = (HBRUSH) CreateSolidBrush( colorval);
		HBRUSH newpen = (HBRUSH) ::CreatePen(PS_SOLID,1, colorval);
		HBRUSH oldbrush = (HBRUSH) SelectObject(hdc,newbrush);
		HBRUSH oldpen = (HBRUSH) SelectObject(hdc,newpen);

		
		PatBlt(hdc, 0, 0, gQyAvRecordMgr.m_var.maxxScreen, gQyAvRecordMgr.m_var.maxyScreen, PATINVERT);		
		//PatBlt(hdc, cRect.left-THICKNESS, cRect.left-THICKNESS, cRect.right+THICKNESS - (cRect.left-THICKNESS) + 1, cRect.bottom+THICKNESS - (cRect.top-THICKNESS) + 1, PATINVERT);
		
		SelectObject(hdc,oldpen);
		SelectObject(hdc,oldbrush);
		DeleteObject(newpen);	
		DeleteObject(newbrush);	

	}
   
	::ReleaseDC(m_hWnd,hdc);
}




//ver 1.8
BOOL CQyBoundWnd::OnEraseBkgnd(CDC* pDC) 
{	
	return TRUE;
}

void CQyBoundWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	if  (  !gQyAvRecordMgr.m_var.supportMouseDrag  )  return;
		
	if  (  m_var.m_type  ==  0  )  {

		GetCursorPos( &m_var.startPoint ); 
		m_var.m_startDrag = 1;
		SetCapture(  );

	}
	
	
	//CWnd::OnLButtonDown(nFlags, point);
	
}

void CQyBoundWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if  (  !gQyAvRecordMgr.m_var.supportMouseDrag  )  return;
	

	if  (  m_var.m_type == 0) {

		POINT currPoint;
		GetCursorPos( &currPoint ); 

		if  (  m_var.m_startDrag  ) {
			m_var.m_startDrag = 0;
			ReleaseCapture();

			int diffx, diffy;
			diffx = currPoint.x  -  m_var.startPoint.x;
			diffy = currPoint.y  -  m_var.startPoint.y;
			MoveRegion(diffx, diffy);
		}

	}
	
	//CWnd::OnLButtonUp(nFlags, point);
}

void CQyBoundWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	if  (  gQyAvRecordMgr.m_var.supportMouseDrag  )  {		
	
		if  (  m_var.m_type  ==  0  )  {

			if  (  m_var.m_startDrag  ) 
			{
				
				/*
				POINT currPoint;
				GetCursorPos( &currPoint ); 

				int diffx, diffy;
				diffx = currPoint.x-startPoint.x;
				diffy = currPoint.y-startPoint.y;
				MoveRegion(diffx, diffy);

				startPoint = currPoint;
				*/
				

			}

			if  (  m_var.cursorMove  )  SetCursor(  m_var.cursorMove  );

		}	

	}
	
	CWnd::OnMouseMove(nFlags, point);
}


void CQyBoundWnd::MoveRegion(int diffx, int diffy)
{
	CRgn  wndRgn, rgnTemp, rgnTemp2,rgnTemp3;
	
	CheckRect(diffx,diffy);	
	
	if  (  m_var.m_type  ==  0  )  {

		MakeFixedRegion(wndRgn,rgnTemp, rgnTemp2,rgnTemp3);

		//while (capturingRegion) {

		//}
		//settingRegion = 1;
		
		HRGN newregion = (HRGN) wndRgn.Detach();
		SetWindowRgn((HRGN) newregion, TRUE); 		
	
		if (oldregion) DeleteObject(oldregion);
		oldregion = newregion;
		UpdateRegionMove();

		//settingRegion = 0;

		

	}	

}


void CQyBoundWnd::CheckRect(int diffx, int diffy)
{
	CRect saveRect;

	saveRect = cRect;
		
	cRect.left += diffx;
	cRect.top += diffy;
	cRect.right +=  diffx;
	cRect.bottom += diffy;	
	
	if (cRect.left < 0) {
		
		cRect.left = 0;	
		cRect.right = cRect.left + saveRect.right - saveRect.left;

	}
	
	
	if (cRect.top < 0) {
		
		cRect.top = 0;	
		cRect.bottom = cRect.top + saveRect.bottom - saveRect.top;

	}

	
	if (cRect.right >  gQyAvRecordMgr.m_var.maxxScreen-1) {
		
		cRect.right = gQyAvRecordMgr.m_var.maxxScreen-1;		
		cRect.left = cRect.right-(saveRect.right - saveRect.left);	
	
	}
		
	
	if (cRect.bottom >  gQyAvRecordMgr.m_var.maxyScreen-1) {
		
		cRect.bottom = gQyAvRecordMgr.m_var.maxyScreen-1;		
		cRect.top = cRect.bottom-(saveRect.bottom - saveRect.top);	
	
	}

}


void CQyBoundWnd::UpdateRegionMove()
{
		m_var.writingRegion = 0;
		while (  m_var.readingRegion  )  {

		}		
		m_var.writingRegion = 1;

		newRect = cRect;
		m_var.newRegionUsed = 1;

		m_var.writingRegion = 0;




}


void CQyBoundWnd::MakeFixedRegion(CRgn  &wndRgn, CRgn  &rgnTemp, CRgn  &rgnTemp2,CRgn  &rgnTemp3)
{
	/*
		wndRgn.CreateRectRgn(0,0, cRect.Width()+THICKNESS+THICKNESS, cRect.Height()+THICKNESS+THICKNESS);
		rgnTemp.CreateRectRgn(THICKNESS, THICKNESS, cRect.Width()+THICKNESS+1, cRect.Height()+THICKNESS+1);
		rgnTemp2.CreateRectRgn(0, SIDELEN2, cRect.Width()+THICKNESS+THICKNESS, cRect.Height()-SIDELEN+1);
		rgnTemp3.CreateRectRgn(SIDELEN2,0, cRect.Width()-SIDELEN+1, cRect.Height()+THICKNESS+THICKNESS);
	
		wndRgn.CombineRgn(&wndRgn,&rgnTemp,RGN_DIFF);
		wndRgn.CombineRgn(&wndRgn,&rgnTemp2,RGN_DIFF);
		wndRgn.CombineRgn(&wndRgn,&rgnTemp3,RGN_DIFF);

		wndRgn.OffsetRgn( cRect.left-THICKNESS, cRect.top-THICKNESS );	
		*/


		wndRgn.CreateRectRgn(0,0, cRect.Width()+SMALLTHICKNESS+SMALLTHICKNESS, cRect.Height()+SMALLTHICKNESS+SMALLTHICKNESS);
		rgnTemp.CreateRectRgn(SMALLTHICKNESS, SMALLTHICKNESS, cRect.Width()+SMALLTHICKNESS+1, cRect.Height()+SMALLTHICKNESS+1);

		wndRgn.CombineRgn(&wndRgn,&rgnTemp,RGN_DIFF);

		wndRgn.OffsetRgn( cRect.left-SMALLTHICKNESS, cRect.top-SMALLTHICKNESS );	



}