
#include	"stdafx.h"
#include	"skinProc_mfc.h"




//pWnd->Default(  ) called before OnNcPaint(  )
void myOnNcPaint(   CWnd  *  pWnd,  SKIN_proc  *  pSp  ) 
{
		// If you only change the menu bar, let the framework draw 
		// the window first
		//pWnd->Default();

        // To accesses the entire screen area of a CWnd 
		// (both client and nonclient areas).
        CWindowDC dc(pWnd);

        CRect rc;
        pWnd->GetWindowRect(rc);

        // Size of menu bar (non-client area) is smaller
        rc.bottom = GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYFRAME);
		//
			int  ii  =  GetSystemMetrics(SM_CYFRAME);
		rc.bottom  +=  ii;


		// Compute color increment
        double decrement = (double)(LIGHT_COLOR - DARK_COLOR) / rc.Width();

        // Draw menu bar
        for(int i = 2; i < rc.Width()-2; i++)
        {
          double color;
          CPen* oldPen;
		  //
          color = LIGHT_COLOR - decrement * (double) i;
          //CPen pen(PS_SOLID, 1, RGB(0,0,(int)color));
		  CPen pen(PS_SOLID, 1, RGB(29,157,38));
		  //  CPen pen(PS_SOLID, 1, RGB(50,194,235));
		  //
          dc.MoveTo(i,1);
          oldPen = dc.SelectObject(&pen);
          dc.LineTo(i,rc.bottom-1);
          dc.SelectObject(oldPen);
        }
		int  oldMode  =  dc.SetBkMode(  TRANSPARENT  );
		COLORREF  oldColor  =  dc.SetTextColor(  RGB(255,255,255));
		dc.TextOut(  8,  8,  pSp->title,  lstrlen(  pSp->title  )  );
		dc.SetBkMode(  oldMode  );
		dc.SetTextColor(  oldColor  );


        // Area for buttons
        CRect closeRect;
        closeRect.left = rc.right - rc.left - 20;
        closeRect.top = GetSystemMetrics(SM_CYFRAME);
        closeRect.right = rc.right - rc.left - 5;
        closeRect.bottom = GetSystemMetrics( SM_CYSIZE );

        // Put the close button on the caption
        dc.DrawFrameControl(closeRect,
        DFC_CAPTION,
        DFCS_CAPTIONCLOSE );

		// Save button position
		pSp->m_rcClose = closeRect;

		//
		CRect maxRect, minRect;
        maxRect.left = rc.right - rc.left - 20  -  20;
        maxRect.top = GetSystemMetrics(SM_CYFRAME);
        maxRect.right = rc.right - rc.left - 5  -  20;
        maxRect.bottom = GetSystemMetrics( SM_CYSIZE );
		//
		minRect.left = rc.right - rc.left - 20  -  40;
        minRect.top = GetSystemMetrics(SM_CYFRAME);
        minRect.right = rc.right - rc.left - 5  -  40;
        minRect.bottom = GetSystemMetrics( SM_CYSIZE );
		

        // Put the close button on the caption
        dc.DrawFrameControl(maxRect,
        DFC_CAPTION,
        DFCS_CAPTIONMAX );

		dc.DrawFrameControl(minRect,
        DFC_CAPTION,
        DFCS_CAPTIONMIN );

		// Save button position
		pSp->m_rcMax = maxRect;
		pSp->m_rcMin = minRect;


		return;

}


int  edgeRect(  CRect  &  rect  )
{
	int  nEdge  =  5;
	
	rect.left  -=  nEdge;
	rect.right  +=  nEdge;
	rect.top  -=  nEdge;
	rect.bottom  +=  nEdge;

	return  0;
}

//
DWORD myHitTest(CPoint pt,  SKIN_proc  *  pSp)
{
	// Check for buttons

	
	CRect rect;
	rect  =pSp->m_rcClose;

	edgeRect(  rect  );

	//
	if(rect.PtInRect(pt))
		return (DWORD) DHT_CLOSE;

	rect  =  pSp->m_rcMin;
	edgeRect(  rect  );
	if  (  rect.PtInRect(pt  )  )
		return  (  DWORD  )DHT_MIN;

	rect  =  pSp->m_rcMax;
	edgeRect(  rect  );

	if  (  rect.PtInRect(pt)  )
		return  (  DWORD  )DHT_MAX;



	//else
		return (DWORD) DHT_CAPTION;
}



void myOnLButtonUp(CWnd  *  pWnd,  UINT nFlags, CPoint point,  SKIN_proc  *  pSp) 
{
	if(pWnd->m_hWnd != GetCapture())
		return;
	
	// Coords are relative to window now
	CPoint pt=point;
	// Adjust for client area
	point.y += GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYFRAME);
	point.x += 5;

	// Now test for button
	DWORD hitTest = myHitTest(point,  pSp);

	switch(pSp->m_ButtonDown) // Release the pressed button
	{
	case DHT_CLOSE:
			{
		    CWindowDC dc(pWnd);

			DrawFrameControl(dc.m_hDC,
				&pSp->m_rcClose,
				DFC_CAPTION,
				DFCS_CAPTIONCLOSE);
			}
			break;
	case DHT_MAX:
			{
		    CWindowDC dc(pWnd);

			DrawFrameControl(dc.m_hDC,
				&pSp->m_rcMax,
				DFC_CAPTION,
				DFCS_CAPTIONMAX);
			}
			break;
	case DHT_MIN:
			{
		    CWindowDC dc(pWnd);

			DrawFrameControl(dc.m_hDC,
				&pSp->m_rcMin,
				DFC_CAPTION,
				DFCS_CAPTIONMIN);
			}
			break;

	default:
			break;
	}

	switch(hitTest)		// Process command if released at on a button
	{
	case DHT_CLOSE:
			pWnd->SendMessage(WM_CLOSE, 0,0);
			break;
	case  DHT_MAX:
		  pWnd->SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, NULL);
		  break;
	case  DHT_MIN:
		   pWnd->SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, NULL);
		   break;
	default:
			break;
	}
	pSp->m_ButtonDown = 0;
	// Release mouse capture
	ReleaseCapture();
}



