
#include  "stdafx.h"
#include	"skinProc.h"



void myOnNcPaint_win32(   HWND  hWnd,  SKIN_proc  *  pSp  )
{
        // If you only change the menu bar, let the framework draw
        // the window first
        //pWnd->Default();

        // To accesses the entire screen area of a CWnd
        // (both client and nonclient areas).
        CWindowDC dc(pWnd);

        CRect rc;
        GetWindowRect(hWnd,  rc);

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
