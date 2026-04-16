
#ifndef  __skinProc_mfc_h__
#define  __skinProc_mfc_h__		//  {


#include    "skinProc.h"

#ifndef __USE_skin__

//
#define		M_myOnLButtonUp(pWnd,  nFlags, point, pSp    )	
#define	M_myOnNcPaint(  pWnd,  pSp  )	
#define	M_myOnNcHitTest(  pWnd,  point,  pSp)	
#define  M_myOnNcLButtonDown(pWnd, nHitTest, point,pSp)						


#else


//
#define		M_myOnLButtonUp(pWnd,  nFlags, point, pSp    )	\
{																\
	if(this != GetCapture())									\
		return;													\
																\
	/* Coords are relative to window now*/						\
	CPoint pt=point;											\
	/* Adjust for client area*/									\
	point.y += GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYFRAME);	\
	point.y  +=  GetSystemMetrics(SM_CYMENUSIZE  );								\
	point.x += 5;																\
																				\
	/* Now test for button*/													\
	DWORD hitTest = myHitTest(point,  pSp);												\
																				\
	switch(pSp->m_ButtonDown) /* Release the pressed button*/						\
	{																			\
	case DHT_CLOSE:																\
			{													\
		    CWindowDC dc(this);									\
																\
			DrawFrameControl(dc.m_hDC,							\
				&pSp->m_rcClose,										\
				DFC_CAPTION,									\
				DFCS_CAPTIONCLOSE);								\
			}													\
			break;												\
	case DHT_MAX:												\
			{													\
		    CWindowDC dc(this);									\
																\
			DrawFrameControl(dc.m_hDC,							\
				&pSp->m_rcMax,										\
				DFC_CAPTION,								\
				DFCS_CAPTIONMAX);							\
			}												\
			break;											\
	case DHT_MIN:											\
			{												\
		    CWindowDC dc(this);								\
															\
			DrawFrameControl(dc.m_hDC,						\
				&pSp->m_rcMin,									\
				DFC_CAPTION,								\
				DFCS_CAPTIONMIN);							\
			}												\
			break;											\
															\
	default:												\
			break;											\
	}														\
															\
	switch(hitTest)		/* Process command if released at on a button*/		\
	{															\
	case DHT_CLOSE:												\
			PostMessage(WM_CLOSE, 0,0);							\
			break;												\
	case  DHT_MAX:												\
		  if  (  pWnd->IsZoomed(  )  )  PostMessage(WM_SYSCOMMAND,SC_RESTORE,NULL );	\
		  else  PostMessage(WM_SYSCOMMAND, SC_MAXIMIZE, NULL);		\
		  break;												\
	case  DHT_MIN:												\
		   PostMessage(WM_SYSCOMMAND, SC_MINIMIZE, NULL);		\
		   break;												\
	default:													\
			break;												\
	}															\
	pSp->m_ButtonDown = 0;											\
	/* Release mouse capture*/									\
	ReleaseCapture();											\
}



//
void myOnNcPaint(   CWnd  *  pWnd,  SKIN_proc  *  pSp  );
#define	M_myOnNcPaint(  pWnd,  pSp  )	{	\
			pWnd->Default(  );				\
			::GetWindowText(  pWnd->m_hWnd,  pSp->title,  mycountof(  pSp->title  )  );	\
			myOnNcPaint(   pWnd, pSp  );  \
			}


DWORD myHitTest(CPoint pt,  SKIN_proc  *  pSp);

//
#define	M_myOnNcHitTest(  pWnd,  point,  pSp)	\
{												\
	if(pWnd != GetCapture())					\
		return CWnd::OnNcHitTest(point);		\
												\
	/* Coords are relative to screen*/			\
	CPoint pt=point;							\
	/* Convert for relative to client area*/	\
	ScreenToClient(&pt);						\
	/* Adjust for client area	*/				\
	pt.y += GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYFRAME)  +  GetSystemMetrics(  SM_CYMENUSIZE  );	\
	pt.x += 5;																\
																			\
	/* Now test for button*/												\
	DWORD hitTest = myHitTest(pt, pSp);											\
																			\
	if(hitTest == pSp->m_LastHit)												\
		return CWnd::OnNcHitTest(point);									\
																			\
	pSp->m_LastHit = hitTest;													\
									\
	UINT pushed = 0;				\
	if(pSp->m_ButtonDown == hitTest)		\
		pushed = DFCS_PUSHED;		\
									\
	CWindowDC dc(this);				\
	switch(hitTest)					\
	{								\
	case DHT_CLOSE:					\
			{						\
			DrawFrameControl(dc.m_hDC,	\
				&pSp->m_rcClose,					\
				DFC_CAPTION,				\
				DFCS_CAPTIONCLOSE | pushed);\
			}								\
			break;							\
	default:								\
			DrawFrameControl(dc.m_hDC,		\
				&pSp->m_rcClose,					\
				DFC_CAPTION,				\
				DFCS_CAPTIONCLOSE);			\
			break;							\
	}										\
	/* return value	*/						\
	return hitTest;							\
}



////
#define  M_myOnNcLButtonDown(pWnd, nHitTest, point,pSp)						\
{																		\
	/* Coords are relative to screen*/									\
	CPoint pt=point;													\
	/* Convert for relative to client area*/							\
	ScreenToClient(&pt);												\
	/* Adjust for client area*/											\
	pt.y += GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYFRAME)  +  GetSystemMetrics(SM_CYMENUSIZE  );	\
	pt.x += 5;															\
																		\
	/* Now test for button	*/											\
	DWORD hitTest = myHitTest(pt,pSp);										\
											\
	switch(hitTest)							\
	{										\
	case DHT_CLOSE:							\
			{								\
		    CWindowDC dc(this);				\
			DrawFrameControl(dc.m_hDC,		\
			&pSp->m_rcClose,						\
			DFC_CAPTION,					\
			DFCS_CAPTIONCLOSE | DFCS_PUSHED);\
			pSp->m_LastHit = hitTest;				\
			pSp->m_ButtonDown = hitTest;				\
			/* Set capture for mouse events*/	\
			SetCapture();						\
			}									\
			break;								\
	case DHT_MAX:								\
			{									\
		    CWindowDC dc(this);					\
			DrawFrameControl(dc.m_hDC,			\
			&pSp->m_rcMax,							\
			DFC_CAPTION,						\
			DFCS_CAPTIONMAX | DFCS_PUSHED);		\
			pSp->m_LastHit = hitTest;				\
			pSp->m_ButtonDown = hitTest;				\
			/* Set capture for mouse events*/	\
			SetCapture();						\
			}									\
			break;								\
	case DHT_MIN:								\
			{									\
		    CWindowDC dc(this);					\
			DrawFrameControl(dc.m_hDC,			\
			&pSp->m_rcMin,							\
			DFC_CAPTION,						\
			DFCS_CAPTIONMIN | DFCS_PUSHED);		\
			pSp->m_LastHit = hitTest;				\
			pSp->m_ButtonDown = hitTest;				\
			/* Set capture for mouse events*/	\
			SetCapture();						\
			}									\
			break;								\
												\
	default:									\
			Default();							\
			break;								\
	}											\
} 






#endif







#endif  //  }


