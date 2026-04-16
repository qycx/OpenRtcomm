
#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>
#include	"qyMcMainCommon.h"
#include	"qyWnd.h"
#include	"qmcCmdProc.h"
//#include	"qmcVWall.h"
//#include	"dlgTalkPublic.h"
//#include	"qmcVideoCapture_isCli.h"


//
int  getScreenRes(  PARAM_getScreenRes  *  p0,  unsigned  int  *  puixScreen,  unsigned  int  *  puiyScreen  )
{
		int  iErr  =  -1;

		if  (  !puixScreen  ||  !puiyScreen  )  return  -1;

		//
		PARAM_getScreenRes  param  =  {0};
		if  (  p0  )  param  =  *p0;

		//
		if  (  param.bService  )  {
			*puixScreen = 1920;
			*puiyScreen = 1080;
			}
		else  {
			//
			HDC hScreenDC=::GetDC(NULL);
			if  (  !hScreenDC  )  goto  errLabel;
			//
			#if  0	//  2016/10/12
				p->m_var.maxxScreen = GetDeviceCaps(hScreenDC,HORZRES);
				p->m_var.maxyScreen = GetDeviceCaps(hScreenDC,VERTRES);
			#endif
			//
			*puixScreen = GetDeviceCaps(hScreenDC,DESKTOPHORZRES);
			*puiyScreen = GetDeviceCaps(hScreenDC,DESKTOPVERTRES);		

			//
			::ReleaseDC(NULL,hScreenDC);		
		}


		iErr  =  0;
errLabel:

		return  iErr;

}



//
int  brushDc(  COLORREF  color,  HDC  hDc,  int  x,  int  y,  int  iW,  int  iH  )
{
	int		iErr	=	-1;

	HBRUSH	hBrush		=	NULL;
	HBRUSH	oldhBrush	=	NULL;

	hBrush  =	CreateSolidBrush(  color  );
	if  (  !hBrush  )  goto  errLabel;
	oldhBrush = ( HBRUSH )SelectObject( hDc, hBrush );
	if  (  !isHandleValid(  oldhBrush  )  )  goto  errLabel;
	
	if  (  !PatBlt( hDc, x, y, iW, iH, PATCOPY )  )  goto  errLabel;

	iErr  =  0;
errLabel:

	if  (  isHandleValid(  oldhBrush  )  )  {
		SelectObject(  hDc,  oldhBrush  );
	}
	if  (  isHandleValid(  hBrush  )  )  DeleteObject(  hBrush  );
	return  iErr;
}
