
#include	"stdafx.h"
#include	<math.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"tmpCeLib.h"

#include	"myresource.h"

#include	"qyStatic.h"
#include	"DlgNotification.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"



__declspec(  dllexport  ) int  myDrawTxt(  LPCTSTR  str,  int nPointSize,  LPCTSTR lpszFaceName,  COLORREF crColor,  int  iX,  int iY,  int  iW,  int  iH,  HWND  hWnd_dst,  HDC  hDc  )
{	
	int  iErr  =  -1;

	CRect				rect;
	CFont				font;
	BOOL				bFontCreated  =  FALSE;
	CFont			*	def_font  =  NULL;
	BOOL				bFontSelected  =  FALSE;
	COLORREF			oldColor  =  0;
	BOOL				bColorSet  =  FALSE;
	int					oldBkMode	=	0;
	BOOL				bBkModeSet  =  FALSE;

	if  (  !str  )  return  -1;

#ifdef  __DEBUG__
		//traceLog(  _T(  "myDrawTxt called %s, iX %d, iY %d, iW %d, iH %d"  ),  str,  iX,  iY,  iW,  iH  );
#endif

	//
	rect.SetRect(iX, iY, iX+iW, iY+iH);
	//  ASSERT(rect == CRect(256, 256, 512, 512));


	//  CClientDC  dc(  pWnd  );
	CDC  *  pDc  =  CDC::FromHandle(  hDc  );
	if  (  !pDc  )  goto  errLabel;
	CDC  &	dc  =  *pDc;

	{

	if  (  !font.CreatePointFont(  nPointSize,  lpszFaceName  )  )  goto  errLabel;
	bFontCreated  =  TRUE;

	def_font  =  dc.SelectObject(  &font  );
	bFontSelected  =  TRUE;
	oldColor  =  dc.SetTextColor(  crColor  );
	bColorSet  =  TRUE;
	oldBkMode  =  dc.SetBkMode(  TRANSPARENT  );
	bBkModeSet  =  TRUE;


	//  	
	RECT  rc  =  rect;
	RECT  tmpRc  =  rect;
			 UINT uFormat  =  DT_CENTER  |  DT_WORDBREAK;
		 dc.DrawText(  str,  lstrlen(  str  ),  &tmpRc,  uFormat  |  DT_CALCRECT    );
		 int  iW_t  =  tmpRc.right  -  tmpRc.left;
		 int  iH_t  =  tmpRc.bottom  -  tmpRc.top;
		 int  iW  =  rc.right  -  rc.left;
		 int  iH  =  rc.bottom  -  rc.top;
		 int  iEdge_l  =  iW  >  iW_t  ?  (  iW  -  iW_t  )  /  2  :  0;
		 int  iEdge_t  =  iH  >  iH_t  ?  (  iH  -  iH_t  )  /  2  :  0;
		 tmpRc.left  =  rc.left  +  iEdge_l;
		 tmpRc.right  =  rc.right  -  iEdge_l;
		 tmpRc.top  =  rc.top  +  iEdge_t;
		 tmpRc.bottom  =  rc.bottom  -  iEdge_t;

		 //
#ifdef  __DEBUG__
		 //traceLog(  _T(  "tmpRc: l %d, t %d, r %d, b %d"  ),  tmpRc.left,  tmpRc.top,  tmpRc.right,  tmpRc.bottom  );
#endif

		 //
		 dc.DrawText(  str,  lstrlen(  str  ),  &tmpRc,  uFormat    );

	}

		 iErr  =  0;
errLabel:

		 if  (  bBkModeSet  )  dc.SetBkMode(  oldBkMode  );
		 if  (  bColorSet  )  dc.SetTextColor(  oldColor  );
		 if  (  bFontSelected  )  dc.SelectObject(  def_font  );

		 if  (  bFontCreated  )  font.DeleteObject(  );


		 return  iErr;

}


