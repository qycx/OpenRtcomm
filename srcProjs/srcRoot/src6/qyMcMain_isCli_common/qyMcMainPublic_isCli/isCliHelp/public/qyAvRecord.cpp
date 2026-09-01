

#include	"stdafx.h"

#include	<windowsx.h>
#ifndef  __WINCE__
	#include	<vfw.h>
#endif
#include	<dmoreg.h>
#include	<time.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture_isCli.h"

#include	"tmpCeLib.h"

#include	"qyAvRecord.h"
#include	"qyAvRecord_dx.h"
#ifndef  __WINCE__
		 //#include	"qyBoundWnd.h"
#endif
#include	"qyDynLib.h"
#include	"..\\qyHookHelp\\qyHookHelp.h"
//  #include	"myresource.h"

#include	"qmcCmdProc.h"
#include	"qyOpenShellCommon.h"

#include	"funcsForIsCliHelp.h"
#include	"isCliHelpPublic.h"
#include	"guishare.h"
 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


QY_AV_recordMgr					gQyAvRecordMgr;		


//AVI functions  and #defines
#define		AVIIF_KEYFRAME		0x00000010L // this frame is a key frame.
#define		BUFSIZE				260
#define		LPLPBI				LPBITMAPINFOHEADER *
#define		N_FRAMES			50
#define		TEXT_HEIGHT			20
//
#define		ModeAVI				0
#define		ModeFlash			1


UINT	WM_avRecord_cursor			= ::RegisterWindowMessage(  CONST_wmStr_avRecord_cursor  );
UINT	WM_avRecord_start			= ::RegisterWindowMessage(  CONST_wmStr_avRecord_start  );
UINT	WM_avRecord_stop			= ::RegisterWindowMessage(  CONST_wmStr_avRecord_stop  );

//  ICINFO * compressor_info  =  NULL;
//  CQyString  strCodec("MS Video 1"); 


//  2013/03/12
typedef  struct  __ctx_screen_t	{
				 CTX_addTxt		addTxt;
}		 CTX_screen;


//
extern "C" DWORD WINAPI recordAvThread( LPVOID lpParameter );

void FixRectSizePos(LPRECT prc,int maxxScreen, int maxyScreen);

int  doCreate_avRecord(  QY_DYN_LIBS  *  pDynLibs,  HWND  hWnd,  COMPRESS_VIDEO  *  pCompressVideo,  BOOL  bUseDirectX,  QY_AV_RECORD  *  pAvRecord  );
void  cleanUp_avRecord(  QY_AV_RECORD  *  pAvRecord  );  


int  adjustRectToCorrect(  QY_AV_recordMgr  *  pMgr  );
 

int GetOperatingSystem() 
{

	OSVERSIONINFO osv;
	osv.dwOSVersionInfoSize  = sizeof(OSVERSIONINFO);


	if (GetVersionEx(&osv))
	{
		return osv.dwMajorVersion;
	}		
	
	return 0;

}


 __declspec(  dllexport  )  int  initAvRecordMgr(  HINSTANCE  g_hInst  )
{
	 int				iErr	=	-1;
	 QY_AV_recordMgr	*	p		=	&gQyAvRecordMgr;

	 if  (  p->bInited  )  return  0;

	 memset(  &p->m_var,  0,  sizeof(  p->m_var  )  );

	 //  ±äÁ¿µÄ³õÊ¼»¯
	 p->m_var.supportMouseDrag  =  1;
	 p->m_var.bits  =  24;
	 p->m_var.nColors  =  24;

	 //  p->m_var.frames_per_second  =  200;
	 p->m_var.frames_per_second  =  2;	//  DEFAULT_usMaxFps_screen;			//  ×¢Òâ£ºÕâÀï½«À´Òª×÷³É¿Éµ÷²ÎÊý£¬µ±¿¼ÂÇµçÓ°Â¼ÖÆÊ±£¬´Ë²ÎÊýÓ¦ÔÚ24Ö¡Ö®ÉÏ¡£2008/11/22


	 p->m_var.flashingRect	=	1;

	 p->m_var.captureTrans	=	1;

	 p->m_var.bRecordCursor	=  TRUE; 

	 p->m_var.selected_compressor	=	-1;

	 p->m_var.compquality		=	7000;

	 p->m_var.CompressorStateIsFor = 0;

	 p->m_var.CompressorStateSize = 0;


	 //
	 p->m_var.pVideoCompressParams = NULL; 
	 p->m_var.CompressorStateIsFor = 0;
	 p->m_var.CompressorStateSize = 0;

	 p->m_var.pParamsUse = NULL; 

	 //
	 p->m_var.RecordingMode = 0;

	 /*
	 p->m_var.timelapse  =  5;
	 if  (  p->m_var.frames_per_second  )  {
		 p->m_var.timelapse  =  1000  /  p->m_var.frames_per_second;
		 if  (  p->m_var.timelapse  *  p->m_var.frames_per_second  <  1000  )  {
			 p->m_var.timelapse  ++  ;
		 }
	 }
	 traceLogA(  "initAvRecordMgr: frames_per_second %d,  timelapse %d",  p->m_var.frames_per_second,  p->m_var.timelapse  );
	 */

	 //
	 //

	 p->m_var.threadPriority  =  THREAD_PRIORITY_NORMAL;
	 p->m_var.ucbNotAutoResizeCapScreen	 =  FALSE;

	 p->m_var.versionOp = 0;


	 //
	 p->m_var.versionOp = GetOperatingSystem();		
	   
	 if  (  createMouseCaptureWnd(  g_hInst,  p  )  )  goto  errLabel;
	 

	 /*  //  ÒòÎªÍ¨ÐÅÊý¾ÝÊÇÒÔ24Î»bmpÎª»ù±¾Ô´Êý¾Ý£¬ËùÒÔÕâÀï²»Òª¸Ä±äÁË¡£2008/10/03
	 {
		 HDC hScreenDC = ::GetDC(NULL);	
		 p->m_var.bits = ::GetDeviceCaps(hScreenDC, BITSPIXEL );	
		 p->m_var.nColors = p->m_var.bits;
		 ::ReleaseDC(NULL,hScreenDC);		
	 }
	 */
		
	 p->m_var.compfccHandler = mmioFOURCC('M', 'S', 'V', 'C');	
	
	//Ver 1.1
	//SuggestRecordingFormat();
	//SuggestCompressFormat();

	//ver 1.6
	//  initialSaveMMMode();

	srand( (unsigned)mytime( NULL ) );


	 iErr  =  0;

errLabel:
	 
	 if  (  !iErr  )  {
		 p->bInited  =  TRUE;		
	 }

	 if  (  iErr  )  {	//  ÕâÀïÊÇ³ö´í´¦Àí

		 if  (  IsWindow(  p->m_var.hWndMgr  )  )  destroyMouseCaptureWnd(  p  );

	 }

	 return  iErr;
}


 __declspec(  dllexport  )  void  exitAvRecordMgr(  )
{
	 QY_AV_recordMgr	*	p		=	&gQyAvRecordMgr;

	 //
	 //showInfo_open0(0, 0, _T("211.exitAvRecordMgr "));

	 //
	 if  (  !p->bInited  )  return;
	 
	 destroyMouseCaptureWnd(  p  );

	 //
	 //showInfo_open0(0, 0, _T("219.after destroyMouseCaptrue"));
	 //Sleep(50);


	/* 
	 if  (compressor_info != NULL) {			
		free(compressor_info);
		//  num_compressor = 0;
	}
	*/
	

	if  (  p->m_var.savedBitmap) {
		DeleteObject(  p->m_var.savedBitmap  );
		p->m_var.savedBitmap = NULL;
	}



	/*
	if  (  p->m_var.pFrame  ) {
		p->m_var.pFrame->DestroyWindow();
		delete  p->m_var.pFrame;
	}
	*/

	 p->bInited  =  FALSE;
	 return;
}



  //  2012/10/29
 __declspec(  dllexport  )  int  toSelectRegion1(  HWND  hWndStarter,  BOOL  bCapFullScreen,  BOOL  bRemoteAssist,  BOOL  bDirectX,  int  level,  int  iParam  )	
{
	int						iErr	=	-1;
	QY_AV_recordMgr  *		pMgr	=	&gQyAvRecordMgr;  
	
	pMgr->m_var.hWndStarter  =  hWndStarter;
	pMgr->m_var.bCapFullScreen  =  bCapFullScreen;
	pMgr->m_var.bRemoteAssist  =  bRemoteAssist;
	pMgr->m_var.bDirectX  =  bDirectX;
	pMgr->m_var.level1  =  level;	//  2012/10/29
	pMgr->m_var.iParam  =  iParam;

	if  (  !pMgr->m_var.bCapFullScreen  )  {

		::ShowWindow(  pMgr->m_var.hWndMgr,  SW_MAXIMIZE  );
		::UpdateWindow(  pMgr->m_var.hWndMgr  );
		
		}
	else  {

		  pMgr->m_var.rcUse.left  =  0;
		  pMgr->m_var.rcUse.top  =  0;
		  pMgr->m_var.rcUse.right  =  pMgr->m_var.maxxScreen  -  1;
		  pMgr->m_var.rcUse.bottom  =  pMgr->m_var.maxyScreen  -  1;

		  //  2012/05/06
		  unsigned  int  uiW_test,  uiH_test;
		  if  (  bTEST_shareScreen(  &uiW_test,  &uiH_test  )  )  {
				  pMgr->m_var.rcUse.right  =  uiW_test  -  1;
				  pMgr->m_var.rcUse.bottom  =  uiH_test  -  1;
				  //
				  showNotification(  0,  0,  0,  0,  0,  0,  _T(  "Test: shareScreen"  )  );
		  }
		  
		  //  2013/04/25. 对1366的屏幕,ipp压缩变形,所以调整为1360				  
		  adjustRectToCorrect(  pMgr  );

		  //
		  ::PostMessage(  pMgr->m_var.hWndStarter,  CONST_qyWm_postComm, CONST_qyWmParam_avRecord_start,  0  ); 

	}

	iErr  =  0;
//  errLabel:
	return  iErr;
}


 //
#if  0  //  2017/08/23
 __declspec(  dllexport  ) int  toSelectRegion(  HWND  hWndStarter,  BOOL  bCapFullScreen,  BOOL  bRemoteAssist,  BOOL  bDirectX,  int  iParam  )	
{
	return  toSelectRegion1(  hWndStarter,  bCapFullScreen,  bRemoteAssist,  bDirectX,  0,  iParam  );
}
#endif

 //
 __declspec(  dllexport  )  int  getSize_qyAvRecord(  )
{
	return  sizeof(  QY_AV_RECORD  );
}

 __declspec(  dllexport  ) RECT  getSelectedRect(  )
{
	 return  gQyAvRecordMgr.m_var.rcUse;
}

/*
 int  setSelectedRect(  int  biWidth,  int  biHeight  )
{
	gQyAvRecordMgr.m_var.rcUse.right  =  gQyAvRecordMgr.m_var.rcUse.left  +  biWidth;
	gQyAvRecordMgr.m_var.rcUse.bottom  =  gQyAvRecordMgr.m_var.rcUse.top  +  biHeight;
	return  0;

 }
 */

 __declspec(  dllexport  )  BOOL  bRemoteAssist_avRecord(  )
{
	return  gQyAvRecordMgr.m_var.bRemoteAssist;
}

 __declspec(  dllexport  )  BOOL  bDirectX_avRecord(  )
{
	return  gQyAvRecordMgr.m_var.bDirectX;
}

 __declspec(  dllexport  )  int  getLevel_avRecord(  )		//  2012/10/29
 {
	 return  gQyAvRecordMgr.m_var.level1;
 }
 
 __declspec(  dllexport  )  int  getiParam_avRecord(  )	//  2009/09/13
{
	 return  gQyAvRecordMgr.m_var.iParam;
}

 __declspec(  dllexport  )  int  setFps_capScreen(  int  fps  )
{
	if  (  fps  <=  0  ||  fps  >  MAX_usFps_toShareBmp  )  return  -1;
	gQyAvRecordMgr.m_var.frames_per_second  =  fps;
	return  0;
}

//  Æô¶¯µÄ´°¿ÚºÍÊÍ·ÅµÄ´°¿Ú²»Í¬£®ÒòÎªÊÍ·ÅµÄ´°¿ÚÒªÎÈ¶¨´æÔÚ£®ËùÒÔ£¬ÒªÑ¡mainWnd.

 __declspec(  dllexport  )  int  startAvRecord(  MC_VAR_common  *  pProcInfo,  int  iIndex_screenCapProcInfo,  HWND  hWnd_notifyEnd  )
{
#ifdef  __NOTSUPPORT_qyAvRecord__
	return  -1;
#else
	int					iErr			=	-1;
	CAP_procInfo_screen  *  pScreenCapProcInfo	=	(  CAP_procInfo_screen  *  )getCapBmpBySth(  pProcInfo,  iIndex_screenCapProcInfo,  0  );
	if  (  !pScreenCapProcInfo  )  return  -1;
	QY_AV_recordMgr	*	pMgr			=	&gQyAvRecordMgr;
	QY_SHARED_OBJ	*	pSharedObj		=	getSharedObjByIndex(  pProcInfo,  pScreenCapProcInfo->iIndex_sharedObj  );
	if  (  !pSharedObj  )  return  -1;
	COMPRESS_VIDEO  *	pCompressVideo	=	&pScreenCapProcInfo->compressVideo;
	QY_AV_RECORD	*	pAvRecord		=	(  QY_AV_RECORD  *  )pCompressVideo->pData;
	CQySyncObj			syncObj;

	if  (  !pCompressVideo->pData  )  return  -1;

	/*
	//  Check validity of rc and fix it		
	HDC hScreenDC = ::GetDC(NULL);	
	gQyAvRecordMgr.m_var.maxxScreen = GetDeviceCaps(hScreenDC,HORZRES);
	gQyAvRecordMgr.m_var.maxyScreen = GetDeviceCaps(hScreenDC,VERTRES);		
	FixRectSizePos(  &gQyAvRecordMgr.m_var.rc,  gQyAvRecordMgr.m_var.maxxScreen,  gQyAvRecordMgr.m_var.maxyScreen  );		
	::ReleaseDC(NULL,hScreenDC);	
	*/

	pSharedObj->bQuit  =  FALSE;
	//
	pMgr->m_var.bStop  =  FALSE;

	pAvRecord->rcUse  =  pMgr->m_var.rcUse;
	pAvRecord->hWnd_notifyEnd  =  hWnd_notifyEnd;

	//  2008/11/10, ÉèÖÃ±ß¿òÑÕÉ«
	if  (  pSharedObj->bRemoteAssist  )  pAvRecord->borderColor  =  RGB(  255,  0,  0  );
	else  pAvRecord->borderColor  =  RGB(  0,  255,  0  );

	//
	//pAvRecord->pFrame = new CQyBoundWnd;	
	if  (  !pAvRecord  )  goto errLabel;

	{	
		 //CRect rect(0, 0, gQyAvRecordMgr.m_var.maxxScreen-1, gQyAvRecordMgr.m_var.maxyScreen-1);
		 //pAvRecord->pFrame->CreateFlashing(  _T(  "Rectangle - Qycx "  ), rect);		
	}

	if  (  syncObj.sync(  CONST_mutexName_syncAvRecord  )  )  goto  errLabel;

	if  (  !pMgr->m_var.usCnt_avRecords  )  {
		traceLogA(  "startAvRecord: now call InstallMyHook."  );
		InstallMyHook(  gQyAvRecordMgr.m_var.hWndMgr,  WM_avRecord_cursor  );	
	}
	pMgr->m_var.usCnt_avRecords  ++  ;
	
#if  0
	CWinThread		*	pThread;

	pThread  =  AfxBeginThread(  recordAvThread,  (  LPVOID  )iIndex_screenCapProcInfo,  gQyAvRecordMgr.m_var.threadPriority,  0,  CREATE_SUSPENDED,  0  );	
	if  (  pThread  )  {
		pSharedObj->hThread  =  pThread->m_hThread;
		pThread->ResumeThread(  );
	}
#endif
	DWORD  dwThreadId;
	pSharedObj->hThread=CreateThread( NULL,  0,  recordAvThread,  (LPVOID)iIndex_screenCapProcInfo,  CREATE_SUSPENDED,  &dwThreadId  );
	if  (  !pSharedObj->hThread  )  goto  errLabel;
	if  (  ResumeThread(  pSharedObj->hThread  )  ==  -1  )  goto  errLabel;									 
	
	//
	iErr  =  0;

errLabel:

	return  iErr;
#endif
}



 //  ×îºóÇåÀíÓÃµÄ
 __declspec(  dllexport  )  void  exitAvRecord(  void  *  pCOMPRESS_VIDEO  )
{
#ifdef  __NOTSUPPORT_qyAvRecord__
	return;
#else

	COMPRESS_VIDEO  *  pCompressVideo  =  (  COMPRESS_VIDEO  *  )pCOMPRESS_VIDEO;

	//
	QY_AV_recordMgr	*	pMgr		=	(  QY_AV_recordMgr  *  )&gQyAvRecordMgr;
	QY_AV_RECORD	*	pAvRecord	=	(  QY_AV_RECORD  *  )pCompressVideo->pData;
	CQySyncObj			syncObj;

	if  (  pAvRecord  )  {

		if  (  pAvRecord->pFrame  ) {
#if  0
			//  pAvRecord->pFrame->DestroyWindow();
			HWND  hWnd  =  pAvRecord->pFrame->m_hWnd;
			if  (  IsWindow(  hWnd  )  )  {
				DestroyWindow(  hWnd  );
			}
#endif
			delete  pAvRecord->pFrame;
		}

		if  (  syncObj.sync(  CONST_mutexName_syncAvRecord  )  )  goto  errLabel;

		if  (  pMgr->m_var.usCnt_avRecords  )  {
			pMgr->m_var.usCnt_avRecords  --  ;
			if  (  !pMgr->m_var.usCnt_avRecords  )  {
				traceLogA(  "exitAvRecord: now call UninstallMyHook."  );
				UninstallMyHook(  pMgr->m_var.hWndMgr  );	
			}
		}

	}

errLabel:
	return;
#endif
}


//  ¼ì²âËùÓÐµÄavRecordÐÐÎª£¬²¢Í£Ö¹
__declspec(  dllexport  )  void  stopAll_avRecord(  )
{
	traceLogA(  "stopAll_avRecord called"  );

	gQyAvRecordMgr.m_var.bStop  =  TRUE;

	return;
}

/*
 void FreeFrame(LPBITMAPINFOHEADER alpbi)
{
 
	if (!alpbi)
		return ;
	
	GlobalFreePtr(alpbi);
	//GlobalFree(alpbi);
	alpbi = NULL;
}
*/


 void SaveBitmapCopy(HDC hdc,HDC hdcbits, int x, int y, int sx, int sy) 
{

	if (gQyAvRecordMgr.m_var.savedBitmap) DeleteObject(gQyAvRecordMgr.m_var.savedBitmap);
	gQyAvRecordMgr.m_var.savedBitmap = NULL;

	gQyAvRecordMgr.m_var.savedBitmap = (HBITMAP) CreateCompatibleBitmap(hdc,sx, sy);
	HBITMAP oldbitmap = (HBITMAP) SelectObject(hdcbits,  gQyAvRecordMgr.m_var.savedBitmap);	
	BitBlt(hdcbits, 0, 0, sx, sy, hdc, x, y, SRCCOPY);
	
	SelectObject(hdcbits,oldbitmap);


}


 void RestoreBitmapCopy(HDC hdc,HDC hdcbits, int x, int y, int sx, int sy) 
 {

	if (gQyAvRecordMgr.m_var.savedBitmap) {

		HBITMAP oldbitmap = (HBITMAP) SelectObject(hdcbits,gQyAvRecordMgr.m_var.savedBitmap);
		BitBlt(hdc, x, y, sx, sy, hdcbits, 0, 0, SRCCOPY);
		SelectObject(hdcbits,oldbitmap);

		if (gQyAvRecordMgr.m_var.savedBitmap) DeleteObject(gQyAvRecordMgr.m_var.savedBitmap);
		gQyAvRecordMgr.m_var.savedBitmap = NULL;

	}

}



 void DrawSelect(HDC hdc, BOOL fDraw, LPRECT lprClip)
{
#ifdef  __WINCE__
	return;
#else
    TCHAR	sz[80];
    DWORD	dw;
    int		x, y, len, dx, dy;
    HDC		hdcBits;    
    RECT	rectDraw;
    SIZE	sExtent;

    rectDraw = *lprClip;
    if (!IsRectEmpty(&rectDraw))
    {

        // If a rectangular clip region has been selected, draw it
		HBRUSH newbrush = (HBRUSH) CreateHatchBrush(  HS_CROSS,  RGB(  0,  0, 255  )  );

		HBRUSH oldbrush = (HBRUSH) SelectObject(hdc,newbrush);

		//PatBlt SRCINVERT regardless fDraw is TRUE or FALSE
        PatBlt(hdc, rectDraw.left, rectDraw.top, rectDraw.right-rectDraw.left, DINV, PATINVERT);
        PatBlt(hdc, rectDraw.left, rectDraw.bottom-DINV, DINV, -(rectDraw.bottom-rectDraw.top-2*DINV),  PATINVERT);
        PatBlt(hdc, rectDraw.right-DINV, rectDraw.top+DINV, DINV, rectDraw.bottom-rectDraw.top-2*DINV,   PATINVERT);
        PatBlt(hdc, rectDraw.right, rectDraw.bottom-DINV, -(rectDraw.right-rectDraw.left), DINV,  PATINVERT);

		SelectObject(hdc,oldbrush);
		DeleteObject(newbrush);
		
		
		hdcBits = CreateCompatibleDC(hdc);
		HFONT newfont = (HFONT) GetStockObject(  SYSTEM_FONT  );
		HFONT oldfont = (HFONT) SelectObject(hdc, newfont);            
		//HFONT oldfont = (HFONT) SelectObject(hdcBits, newfont);            
		
		wsprintf(sz, _T(  "Left: %d  Top: %d  Width: %d  Height: %d"  ), rectDraw.left, rectDraw.top, rectDraw.right - rectDraw.left+1, rectDraw.bottom -  rectDraw.top+1);
        len = lstrlen(sz);        
		dw = GetTextExtentPoint(hdc, sz, len, &sExtent);
		//dw = GetTextExtentPoint(hdcBits, sz, len, &sExtent);
        
		dx = sExtent.cx;
        dy = sExtent.cy;
		x=  rectDraw.left + 5;
		
		if (rectDraw.top < (dy + DINV + 2)) 
			y=  rectDraw.bottom + DINV + 2;
		else
			y=  rectDraw.top - dy - DINV - 2;
        

		
		if (fDraw)	{		
			
			//Save Original Picture
			SaveBitmapCopy(hdc,hdcBits,  x-4, y-4, dx+8, dy+8); 
			
			
			//Text
			COLORREF oldtextcolor = SetTextColor(hdc,RGB(0,0,0));
			COLORREF oldbkcolor = SetBkColor(hdc,RGB(255,255,255));
			SetBkMode(hdc,TRANSPARENT);
			
			//Rectangle(hdc,x-1,y-1,x+dx, y+dy);
			
			Rectangle(  hdc,  x  -  3,  y  -  2,  x  +  dx  +  3,  y  +  dy  +  3  );
			
			//  RoundRect(hdc,x-4,y-4,x+dx+4, y+dy+4,10,10);

			SetBkMode(hdc,OPAQUE);

			ExtTextOut(hdc, x, y, 0, NULL, sz, len, NULL);
			SetBkColor(hdc,oldbkcolor);
			SetTextColor(hdc,oldtextcolor);
			SelectObject(hdc, oldfont);	
		}
		else 
			RestoreBitmapCopy(hdc,hdcBits,  x-4, y-4, dx+8, dy+8);


        DeleteDC(hdcBits);
    }
#endif	
}

#define SWAP(x,y)   ((x)^=(y)^=(x)^=(y))

void WINAPI NormalizeRect(LPRECT prc)
{
    if (prc->right  < prc->left) SWAP(prc->right,  prc->left);
    if (prc->bottom < prc->top)  SWAP(prc->bottom, prc->top);
}





//ver 1.6
/*
HANDLE  Bitmap2Dib( HBITMAP hbitmap, UINT bits )
{
	HANDLE               hdib ;
	HDC                 hdc ;
	BITMAP              bitmap ;
	UINT                wLineLen ;
	DWORD               dwSize ;
	DWORD               wColSize ;
	LPBITMAPINFOHEADER  lpbi ;
	LPBYTE              lpBits ;
	
	GetObject(hbitmap,sizeof(BITMAP),&bitmap) ;

	//
	// DWORD align the width of the DIB
	// Figure out the size of the colour table
	// Calculate the size of the DIB
	//
	wLineLen = (bitmap.bmWidth*bits+31)/32 * 4;
	wColSize = sizeof(RGBQUAD)*((bits <= 8) ? 1<<bits : 0);
	dwSize = sizeof(BITMAPINFOHEADER) + wColSize +
		(DWORD)(UINT)wLineLen*(DWORD)(UINT)bitmap.bmHeight;

	//
	// Allocate room for a DIB and set the LPBI fields
	//
	hdib = GlobalAlloc(GHND,dwSize);
	if (!hdib)
		return hdib ;

	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hdib) ;

	lpbi->biSize = sizeof(BITMAPINFOHEADER) ;
	lpbi->biWidth = bitmap.bmWidth ;
	lpbi->biHeight = bitmap.bmHeight ;
	lpbi->biPlanes = 1 ;
	lpbi->biBitCount = (WORD) bits ;
	lpbi->biCompression = BI_RGB ;
	lpbi->biSizeImage = dwSize - sizeof(BITMAPINFOHEADER) - wColSize ;
	lpbi->biXPelsPerMeter = 0 ;
	lpbi->biYPelsPerMeter = 0 ;
	lpbi->biClrUsed = (bits <= 8) ? 1<<bits : 0;
	lpbi->biClrImportant = 0 ;

	//
	// Get the bits from the bitmap and stuff them after the LPBI
	//
	lpBits = (LPBYTE)(lpbi+1)+wColSize ;

	hdc = CreateCompatibleDC(NULL) ;

	GetDIBits(hdc,hbitmap,0,bitmap.bmHeight,lpBits,(LPBITMAPINFO)lpbi, DIB_RGB_COLORS);

	lpbi->biClrUsed = (bits <= 8) ? 1<<bits : 0;

	DeleteDC(hdc) ;
	GlobalUnlock(hdib);

	return hdib ;
}
*/

#if  0  //  2011/07/26
 int  myBitmap2Dib(  HBITMAP hbitmap,  UINT  bits,  QY_AV_RECORD  *  pAvRecord  )
{
#ifdef  __WINCE__
	return  -1;
#else
	int					iErr			=	-1;
	HDC                 hdc				=	NULL;
	BITMAP              bitmap;
	UINT                wLineLen ;
	DWORD               dwSize ;
	DWORD               wColSize ;
	LPBITMAPINFOHEADER  lpbi			=	NULL;
	LPBYTE              lpBits			=	NULL;

	if  (  !GetObject(hbitmap,sizeof(BITMAP),&bitmap)  )  goto  errLabel;

	//
	// DWORD align the width of the DIB
	// Figure out the size of the colour table
	// Calculate the size of the DIB
	//
	wLineLen = (bitmap.bmWidth*bits+31)/32 * 4;
	wColSize = sizeof(RGBQUAD)*((bits <= 8) ? 1<<bits : 0);
	dwSize = sizeof(BITMAPINFOHEADER) + wColSize +
		(DWORD)(UINT)wLineLen*(DWORD)(UINT)bitmap.bmHeight;
	
	if  (  sizeof(  BITMAPINFOHEADER  )  +  wColSize  >  sizeof(  pAvRecord->bmpInfo  )  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  _T(  "IsClient"  ),  0,  _T(  "capScreen"  ),  _T(  ""  ),  _T(  "myBitmap2Dib failed, wColSize maybe not 0"  )  );
		goto  errLabel;
	}
	//
	// Allocate room for a DIB and set the LPBI fields
	//

	/*
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hdib) ;

	lpbi->biSize = sizeof(BITMAPINFOHEADER) ;
	lpbi->biWidth = bitmap.bmWidth ;
	lpbi->biHeight = bitmap.bmHeight ;
	lpbi->biPlanes = 1 ;
	lpbi->biBitCount = (WORD) bits ;
	lpbi->biCompression = BI_RGB ;
	lpbi->biSizeImage = dwSize - sizeof(BITMAPINFOHEADER) - wColSize ;
	lpbi->biXPelsPerMeter = 0 ;
	lpbi->biYPelsPerMeter = 0 ;
	lpbi->biClrUsed = (bits <= 8) ? 1<<bits : 0;
	lpbi->biClrImportant = 0 ;


	//
	// Get the bits from the bitmap and stuff them after the LPBI
	//
	lpBits = (LPBYTE)(lpbi+1)+wColSize ;
	*/

	hdc = CreateCompatibleDC(NULL) ;
	if  (  !hdc  )  goto  errLabel;

	lpbi  =  &pAvRecord->bmpInfo.bmiHeader;
	lpBits  =  (  LPBYTE  )pAvRecord->pBits;

	if  (  !GetDIBits(hdc,hbitmap,0,bitmap.bmHeight,lpBits,(LPBITMAPINFO)lpbi, DIB_RGB_COLORS)  )  goto  errLabel;

	lpbi->biClrUsed = (bits <= 8) ? 1<<bits : 0;

	iErr  =  0;

errLabel:

	if  (  hdc  )  DeleteDC(hdc) ;

	return  iErr;
#endif
}
#endif


 int  myBitmap2Dib(  HDC  hdc,  HBITMAP hbitmap,  UINT  bits,  QY_AV_RECORD  *  pAvRecord  )
{
#ifdef  __WINCE__
	return  -1;
#else
	int					iErr			=	-1;
	BITMAP              bitmap;
	UINT                wLineLen ;
	DWORD               dwSize ;
	DWORD               wColSize ;
	LPBITMAPINFOHEADER  lpbi			=	NULL;
	LPBYTE              lpBits			=	NULL;

	if  (  !GetObject(hbitmap,sizeof(BITMAP),&bitmap)  )  goto  errLabel;

	//
	// DWORD align the width of the DIB
	// Figure out the size of the colour table
	// Calculate the size of the DIB
	//
	wLineLen = (bitmap.bmWidth*bits+31)/32 * 4;
	wColSize = sizeof(RGBQUAD)*((bits <= 8) ? 1<<bits : 0);
	dwSize = sizeof(BITMAPINFOHEADER) + wColSize +
		(DWORD)(UINT)wLineLen*(DWORD)(UINT)bitmap.bmHeight;
	
	if  (  sizeof(  BITMAPINFOHEADER  )  +  wColSize  >  sizeof(  pAvRecord->bmpInfo  )  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  _T(  "IsClient"  ),  0,  _T(  "capScreen"  ),  _T(  ""  ),  _T(  "myBitmap2Dib failed, wColSize maybe not 0"  )  );
		goto  errLabel;
	}
	//
	// Allocate room for a DIB and set the LPBI fields
	//

	/*
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hdib) ;

	lpbi->biSize = sizeof(BITMAPINFOHEADER) ;
	lpbi->biWidth = bitmap.bmWidth ;
	lpbi->biHeight = bitmap.bmHeight ;
	lpbi->biPlanes = 1 ;
	lpbi->biBitCount = (WORD) bits ;
	lpbi->biCompression = BI_RGB ;
	lpbi->biSizeImage = dwSize - sizeof(BITMAPINFOHEADER) - wColSize ;
	lpbi->biXPelsPerMeter = 0 ;
	lpbi->biYPelsPerMeter = 0 ;
	lpbi->biClrUsed = (bits <= 8) ? 1<<bits : 0;
	lpbi->biClrImportant = 0 ;


	//
	// Get the bits from the bitmap and stuff them after the LPBI
	//
	lpBits = (LPBYTE)(lpbi+1)+wColSize ;
	*/


	lpbi  =  &pAvRecord->bmpInfo.bmiHeader;
	lpBits  =  (  LPBYTE  )pAvRecord->pBits;

	if  (  !GetDIBits(hdc,hbitmap,0,bitmap.bmHeight,lpBits,(LPBITMAPINFO)lpbi, DIB_RGB_COLORS)  )  goto  errLabel;

	lpbi->biClrUsed = (bits <= 8) ? 1<<bits : 0;

	iErr  =  0;

errLabel:


	return  iErr;
#endif
}


 HCURSOR FetchCursorHandle() 
{
	 if  (  gQyAvRecordMgr.m_var.hSavedCursor  ==  NULL  ) 			
		 gQyAvRecordMgr.m_var.hSavedCursor  =  GetCursor();

	 return  gQyAvRecordMgr.m_var.hSavedCursor;
}


 int  doCaptureScreen(  QY_AV_recordMgr  *  pMgr,  QY_AV_RECORD  *  pAvRecord,  CTX_screen  *  pCtx,  int left,int top,int width, int height,int tempDisableRect,  POINT  *  pCursorPoint  )
{
#ifdef  __WINCE__
	return  -1;
#else
	int				iErr		=	-1;
	HDC				hScreenDC	=	NULL;
	HDC				hMemDC		=	NULL;
	HBITMAP			hbm			=	NULL;
	HBITMAP			oldbm		=	NULL;

	
	hScreenDC = ::GetDC(NULL);
	if  (  !hScreenDC  )  goto errLabel;
	
	hMemDC = ::CreateCompatibleDC(hScreenDC);     
	if  (  !hMemDC  )  goto  errLabel;
	
    hbm = CreateCompatibleBitmap(hScreenDC, width, height);
	if  (  !hbm  )  goto  errLabel;
	oldbm = (HBITMAP) SelectObject(hMemDC, hbm);	 
	if  (  !isHandleValid(  oldbm  )  )  goto  errLabel;
	//ver 1.6
	DWORD bltFlags = SRCCOPY;
	if  (  (  pMgr->m_var.captureTrans  )  &&  (  pMgr->m_var.versionOp  >  4  )  )  bltFlags |= CAPTUREBLT;
	if  (  !BitBlt(hMemDC, 0, 0, width, height, hScreenDC, left, top, bltFlags)  )  goto  errLabel;	 	
	
	//Get Cursor Pos
	POINT		xPoint; 
	GetCursorPos(  &xPoint  ); 
	HCURSOR		hcur  =  FetchCursorHandle();
	xPoint.x  -=  left;
	xPoint.y  -=  top;

	if  (  pCursorPoint  )  {	//  2008/11/11, ÕâÀï×¢Òâ,ÊÇÊ¹ÓÃµÄÏà¶Ô´°¿ÚµÄ×ø±ê.ÕâÊÇÒòÎª´°¿Ú¿ÉÄÜ»áÒÆ¶¯.ËùÒÔ,ÐèÒªÊ¹ÓÃÏà¶Ô×ø±ê
		pCursorPoint->x  =  xPoint.x;
		pCursorPoint->y  =  xPoint.y;
	}
	
	//Draw the Cursor	
	if  (  gQyAvRecordMgr.m_var.bRecordCursor  )  {	
		ICONINFO	iconinfo ;	
		BOOL		ret;

		ret	 =  GetIconInfo(  hcur,  &iconinfo  ); 
		if  (  ret  )  {

			xPoint.x -= iconinfo.xHotspot;
			xPoint.y -= iconinfo.yHotspot;

			//need to delete the hbmMask and hbmColor bitmaps
			//otherwise the program will crash after a while after running out of resource
			if (iconinfo.hbmMask) DeleteObject(iconinfo.hbmMask);
			if (iconinfo.hbmColor) DeleteObject(iconinfo.hbmColor);

		}		
		
		::DrawIcon( hMemDC,  xPoint.x,  xPoint.y, hcur); 							
	}
	

#ifndef  __WINCE__

	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  goto  errLabel;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  goto  errLabel;
	QM_SHM_CMDS	*	pShmCmds  =  QY_GET_shmCmds(  pProcInfo  );

	if  (  pShmCmds  )  {
		if  (  pFuncs  )  {
			//
			#if  0			
			{
				//
				SUBTITLES_cfg  *  pCurCfg  =  (  SUBTITLES_cfg  *  )getCurSubtitlesCfg(  0,  CONST_capType_screen,  0  );	
				if  (  !pCurCfg  )  goto  errLabel;
				SUBTITLES_cfg  *  pSubtitlesCfg  =  &pCtx->addTxt.subtitlesCfg;
	 	
				//			
				if  (  pCurCfg->dwModifiedTickCnt_any_start  !=  pSubtitlesCfg->dwModifiedTickCnt_any_start  )  {			
					SUBTITLES_cfg	tmpCfg;
					memcpy(  &tmpCfg,  pCurCfg,  sizeof(  tmpCfg  )  );
					if  (  tmpCfg.dwModifiedTickCnt_any_start  !=  tmpCfg.dwModifiedTickCnt_any_end  )  goto  errLabel;			 
					//
					memcpy(  pSubtitlesCfg,  &tmpCfg,  sizeof(  pSubtitlesCfg[0]  )  );			 
					//				 
				}	 	 
			}
			
			//
			pFuncs->pf_addTxtToPic_screen(  &pCtx->addTxt,  pShmCmds->ucbDaemonDemo,  width,  height,  hMemDC  );		

			#endif

		}
	}
#endif


	
	SelectObject(hMemDC,oldbm);  oldbm  =  NULL;    			

	//  LPBITMAPINFOHEADER pBM_HEADER = (LPBITMAPINFOHEADER)GlobalLock(myBitmap2Dib(hbm, gQyAvRecordMgr.m_var.bits,  pAvRecord));	
	//  if (pBM_HEADER == NULL) { 			
	//  	myMessageBox(  NULL,  _T(  "Failed to read a frame!"  ),  _T(  "Error"  ),  MB_OK  |  MB_ICONEXCLAMATION  );					
	//  	exit(1);
	//  }    
	if  (  myBitmap2Dib(  hMemDC,  hbm,  gQyAvRecordMgr.m_var.bits,  pAvRecord  )  )  goto  errLabel;

	iErr  =  0;

errLabel:

	if  (  isHandleValid(  oldbm  )  )  SelectObject(  hMemDC,  oldbm  );
	if  (  hbm  )  DeleteObject(hbm);			
	if  (  hMemDC  )  DeleteDC(hMemDC);	
	if  (  hScreenDC  )  ReleaseDC(NULL,hScreenDC) ;	

	if  (  iErr  )  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  _T(  "IsClient"  ),  0,  _T(  "capScreen"  ),  _T(  ""  ),  _T(  "doCaptureScreen failed"  )  );

	return  iErr;
#endif
}


/*
 LPBITMAPINFOHEADER  captureScreenFrame_20090923(  QY_AV_recordMgr  *  pMgr,  QY_AV_RECORD  *  pAvRecord,  int left,int top,int width, int height,int tempDisableRect,  POINT  *  pCursorPoint  )
{
	HDC hScreenDC = ::GetDC(NULL);
	
	//if flashing rect
	//  if  (  pMgr->m_var.flashingRect && !tempDisableRect  )  {
	//	    DrawFlashingRect(  pAvRecord,  TRUE,  0  );
	//  }	
	
	
	HDC hMemDC = ::CreateCompatibleDC(hScreenDC);     
	HBITMAP hbm;
	
    hbm = CreateCompatibleBitmap(hScreenDC, width, height);
	HBITMAP oldbm = (HBITMAP) SelectObject(hMemDC, hbm);	 
	
	//ver 1.6
	DWORD bltFlags = SRCCOPY;
	if  (  (  pMgr->m_var.captureTrans  )  &&  (  pMgr->m_var.versionOp  >  4  )  )  bltFlags |= CAPTUREBLT;
	BitBlt(hMemDC, 0, 0, width, height, hScreenDC, left, top, bltFlags);	 	
	
	//Get Cursor Pos
	POINT		xPoint; 
	GetCursorPos(  &xPoint  ); 
	HCURSOR		hcur  =  FetchCursorHandle();
	xPoint.x  -=  left;
	xPoint.y  -=  top;

	if  (  pCursorPoint  )  {	//  2008/11/11, ÕâÀï×¢Òâ,ÊÇÊ¹ÓÃµÄÏà¶Ô´°¿ÚµÄ×ø±ê.ÕâÊÇÒòÎª´°¿Ú¿ÉÄÜ»áÒÆ¶¯.ËùÒÔ,ÐèÒªÊ¹ÓÃÏà¶Ô×ø±ê
		pCursorPoint->x  =  xPoint.x;
		pCursorPoint->y  =  xPoint.y;
	}
	
	//Draw the Cursor	
	if  (  gQyAvRecordMgr.m_var.bRecordCursor  )  {	
		ICONINFO	iconinfo ;	
		BOOL		ret;

		ret	 =  GetIconInfo(  hcur,  &iconinfo  ); 
		if  (  ret  )  {

			xPoint.x -= iconinfo.xHotspot;
			xPoint.y -= iconinfo.yHotspot;

			//need to delete the hbmMask and hbmColor bitmaps
			//otherwise the program will crash after a while after running out of resource
			if (iconinfo.hbmMask) DeleteObject(iconinfo.hbmMask);
			if (iconinfo.hbmColor) DeleteObject(iconinfo.hbmColor);

		}		
		
		::DrawIcon( hMemDC,  xPoint.x,  xPoint.y, hcur); 							
	}
	
	
	SelectObject(hMemDC,oldbm);    			
	LPBITMAPINFOHEADER pBM_HEADER = (LPBITMAPINFOHEADER)GlobalLock(Bitmap2Dib(hbm, gQyAvRecordMgr.m_var.bits));	
	//LPBITMAPINFOHEADER pBM_HEADER = (LPBITMAPINFOHEADER)GlobalLock(Bitmap2Dib(hbm, 24));	
	if (pBM_HEADER == NULL) { 
			
		myMessageBox(  NULL,  _T(  "Failed to read a frame!"  ),  _T(  "Error"  ),  MB_OK  |  MB_ICONEXCLAMATION  );					
		//  MessageOut(NULL,IDS_STRING_ERRFRAME ,IDS_STRING_NOTE,MB_OK | MB_ICONEXCLAMATION);

		exit(1);
	}    

	DeleteObject(hbm);			
	DeleteDC(hMemDC);	
	
	
	//if flashing rect
	//  if (  gQyAvRecordMgr.m_var.flashingRect && !tempDisableRect) {
	//  	DrawFlashingRect(  pAvRecord,  FALSE , 0);
	//  }	
	
	
	ReleaseDC(NULL,hScreenDC) ;	


	return pBM_HEADER;

	
    
}
*/

/*
LPBITMAPINFOHEADER captureScreenFrame(int left,int top,int width, int height,int tempDisableRect)
{

	
	HDC hScreenDC = ::GetDC(NULL);

	
	//if flashing rect
	if (  gQyAvRecordMgr.m_var.flashingRect && !tempDisableRect) {

		if (  gQyAvRecordMgr.m_var.autopan) {				
						
			gQyAvRecordMgr.m_var.pFrame->SetUpRegion(left,top,width,height,1);				
			DrawFlashingRect( TRUE , 1);			

		}
		else		
			DrawFlashingRect( TRUE , 0);

	}	
	
	
	HDC hMemDC = ::CreateCompatibleDC(hScreenDC);     
	HBITMAP hbm;
	
    hbm = CreateCompatibleBitmap(hScreenDC, width, height);
	HBITMAP oldbm = (HBITMAP) SelectObject(hMemDC, hbm);	 
	
	//BitBlt(hMemDC, 0, 0, width, height, hScreenDC, left, top, SRCCOPY);	 	
	
	
	//ver 1.6
	DWORD bltFlags = SRCCOPY;
	if ((  gQyAvRecordMgr.m_var.captureTrans) && (gQyAvRecordMgr.m_var.versionOp>4))
	//if (captureTrans)
		bltFlags |= CAPTUREBLT;
	BitBlt(hMemDC, 0, 0, width, height, hScreenDC, left, top, bltFlags);	 	
	
	
	
	//Get Cursor Pos
	POINT xPoint; 
	GetCursorPos( &xPoint ); 
	HCURSOR hcur= FetchCursorHandle();
	xPoint.x-=left;
	xPoint.y-=top;

	
	//Draw the HighLight	
	if (  gQyAvRecordMgr.m_var.g_highlightcursor==1) {	

		POINT highlightPoint; 		

		highlightPoint.x = xPoint.x -64 ;
		highlightPoint.y = xPoint.y -64 ;		
		
		InsertHighLight( hMemDC, highlightPoint.x, highlightPoint.y);

	}
	
	//Draw the Cursor	
	if (  gQyAvRecordMgr.m_var.g_recordcursor==1) {
	
	
		
		ICONINFO iconinfo ;	
		BOOL ret;
		ret	= GetIconInfo( hcur,  &iconinfo ); 
		if (ret) {

			xPoint.x -= iconinfo.xHotspot;
			xPoint.y -= iconinfo.yHotspot;

			//need to delete the hbmMask and hbmColor bitmaps
			//otherwise the program will crash after a while after running out of resource
			if (iconinfo.hbmMask) DeleteObject(iconinfo.hbmMask);
			if (iconinfo.hbmColor) DeleteObject(iconinfo.hbmColor);

		}		
		
		
		::DrawIcon( hMemDC,  xPoint.x,  xPoint.y, hcur); 							

	}
	
	
	SelectObject(hMemDC,oldbm);    			
	LPBITMAPINFOHEADER pBM_HEADER = (LPBITMAPINFOHEADER)GlobalLock(Bitmap2Dib(hbm, gQyAvRecordMgr.m_var.bits));	
	//LPBITMAPINFOHEADER pBM_HEADER = (LPBITMAPINFOHEADER)GlobalLock(Bitmap2Dib(hbm, 24));	
	if (pBM_HEADER == NULL) { 
			
		myMessageBox(NULL,"Error reading a frame!","Error",MB_OK | MB_ICONEXCLAMATION);					
		//  MessageOut(NULL,IDS_STRING_ERRFRAME ,IDS_STRING_NOTE,MB_OK | MB_ICONEXCLAMATION);

		exit(1);
	}    

	DeleteObject(hbm);			
	DeleteDC(hMemDC);	
	
	
	//if flashing rect
	if (  gQyAvRecordMgr.m_var.flashingRect && !tempDisableRect) {
		
		if (  gQyAvRecordMgr.m_var.autopan)	{
			DrawFlashingRect(FALSE , 1);
		}
		else
			DrawFlashingRect(FALSE , 0);

	}	
	
	
	ReleaseDC(NULL,hScreenDC) ;	


	return pBM_HEADER;

	
    
}
*/


void FreeParamsUse() {

	if ( gQyAvRecordMgr.m_var.pParamsUse) {

		GlobalFreePtr(  gQyAvRecordMgr.m_var.pParamsUse);
		gQyAvRecordMgr.m_var.pParamsUse = NULL;
	}

}


BOOL MakeCompressParamsCopy(DWORD paramsSize, LPVOID pOrg) {

	if (gQyAvRecordMgr.m_var.pParamsUse) {		
		//Free Existing
		FreeParamsUse();
	}	
	
	gQyAvRecordMgr.m_var.pParamsUse = (LPVOID) GlobalAllocPtr(GHND, paramsSize);
	if (NULL == gQyAvRecordMgr.m_var.pParamsUse)
	{	
		OutputDebugString(  _T(  "Failure allocating Video Params or compression\n"  )  );
		return FALSE;
	}
	
	memcpy(  gQyAvRecordMgr.m_var.pParamsUse,pOrg,paramsSize);	
	return TRUE;

}

#if  0
void SetTitleBar(CString title) {
	
	CWinApp* app = NULL;
	app	= AfxGetApp();
	if (app) {

		HWND mainwnd = NULL;
		mainwnd= app->m_pMainWnd->m_hWnd;
		if (mainwnd)
			::SetWindowText(mainwnd, LPCTSTR(title));

	}
}
#endif

#ifdef  __DEBUG__
/*
 int  getBmpInfo_avRecord(  int  left,  int  top,  int  width,  int  height,  BITMAPINFO  *  pBmpInfo  )
{
	LPBITMAPINFOHEADER				alpbi	=	NULL;

	alpbi=captureScreenFrame(  &gQyAvRecordMgr,  left,top,width, height,1);
	if  (  !alpbi  )  return  -1;

	memcpy(  &pBmpInfo->bmiHeader,  alpbi,  sizeof(  pBmpInfo->bmiHeader  )  );

	FreeFrame(  alpbi  );
	return  0;
}
*/

#endif


 int  recordVideo(  MC_VAR_isCli  *  pProcInfo,  QY_AV_recordMgr  *  pMgr,  CTX_screen  *  pCtx,  int  iIndex_screenCapProcInfo,  int  top,  int  left,  int  width,  int  height,  int  fps,  LPCTSTR  szFileName  ) 
{
#ifdef  __NOTSUPPORT_qyAvRecord__
	return  -1;
#else  
	if  (  !pProcInfo  )  return  -1;
	QY_MC					*		pQyMc				=	(  QY_MC  *  )pProcInfo->pQyMc;
	if  (  !pQyMc  )  return  -1;
	FUNCS_for_isCliHelp		*		pFuncs				=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	CAP_procInfo_screen		*		pScreenCapProcInfo	=	(  CAP_procInfo_screen  *  )getCapBmpBySth(  pProcInfo,  iIndex_screenCapProcInfo,  0  );
	if  (  !pScreenCapProcInfo  )  return  -1;
	QY_SHARED_OBJ  *  pSharedObj  =	getSharedObjByIndex(  pProcInfo,  pScreenCapProcInfo->iIndex_sharedObj  );
	if  (  !pSharedObj  )  return  -1;
	COMPRESS_VIDEO			*		pCompressVideo		=	&pScreenCapProcInfo->compressVideo;
	LPBITMAPINFOHEADER				alpbi1				=	NULL;
	AVISTREAMINFO					strhdr;
	PAVIFILE						pfile				=	NULL;
	PAVISTREAM						ps  =  NULL,  psCompressed  =  NULL;
	AVICOMPRESSOPTIONS				opts;
	AVICOMPRESSOPTIONS FAR *		aopts[1]			=	{  &opts  };
	HRESULT							hr;
	WORD							wVer;
	char							szTitle[BUFSIZE];

	//
	QY_AV_RECORD			*		pAvRecord			=	(  QY_AV_RECORD  *  )pCompressVideo->pData;
#if  0
	CWnd					*		pWnd				=	AfxGetMainWnd(  );
	if  (  !pWnd  )  return  -1;
#endif
	POINT							cursorPoint;
	
	myDRAW_VIDEO_DATA				pkts[1];				//  2011/07/15

	CQyMalloc						mallocObj_pMsgBuf;
	MIS_MSGU				*		pMsgBuf				=	(  MIS_MSGU  *  )mallocObj_pMsgBuf.mallocf(  sizeof(  MIS_MSGU  )  );
	if  (  !pMsgBuf  )  return  -1;

	wVer = HIWORD(VideoForWindowsVersion());
	if  (  wVer  <  0x010a  )  {	  		
		OutputDebugString(  _T(  "Error! Video for Windows version too old!\n"  )  );
		return  FALSE;
	}

	//
	int				timelapse;				// =5;
	DWORD			nFrames					=	0;		//  2011/07/25

	timelapse  =  5;
	if  (  fps  )  {
		timelapse  =  1000  /  fps;
		if  (  timelapse  *  fps  <  1000  )  {
			timelapse  ++  ;
		}
		//
		//  2011/07/25. 因为实际上抓屏压缩发送也要占用时间，所以上面的timelapse作为时间间隔是不对的.
	}
	traceLogA(  "initAvRecordMgr: fps %d,  timelapse %d",  fps,  timelapse  );

	//  2011/07/15
	memset(  pkts,  0,  sizeof(  pkts  )  );

	//  2009/09/23
	HWND  hWnd  =  pQyMc->gui.hMainWnd;	//  pWnd->m_hWnd
	if  (  doCreate_avRecord(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs,  hWnd,  pCompressVideo,  FALSE,  pAvRecord  )  )  goto  error;

	////////////////////////////////////////////////
	// CAPTURE FIRST FRAME
	////////////////////////////////////////////////	
	if  (  doCaptureScreen(  pMgr,  pAvRecord,  pCtx,  left,  top,  width,  height,  1,  &cursorPoint  )  )  goto  error;
	alpbi1  =  &pAvRecord->bmpInfo.bmiHeader;
	
	if  (  pMgr->m_var.flashingRect  )  {
#if  0
		pAvRecord->pFrame->SetUpRegion(left,top,width,height,0);
		//pAvRecord->pFrame->ShowWindow(  SW_SHOW  );
		//  2019/04/10
		if  (  qyGetCustomId(  )  ==  CONST_qyCustomId_hbwj  )  {
			pAvRecord->pFrame->ShowWindow(  SW_HIDE  );
			pAvRecord->pFrame->ModifyStyleEx(  WS_EX_APPWINDOW,  WS_EX_TOOLWINDOW,  0  );
		}
		pAvRecord->pFrame->PaintBorder(  pAvRecord->borderColor  );
#endif
	}

	if  (  pMgr->m_var.bSaveToAviFile  )  {
		
		////////////////////////////////////////////////
		// INIT AVI USING FIRST FRAME
		////////////////////////////////////////////////
		AVIFileInit();

		//
		// Open the movie file for writing....
		//
		strcpy(szTitle,"AVI Movie");
	 
		hr = AVIFileOpen(&pfile, szFileName, OF_WRITE | OF_CREATE, NULL);	
		if  (  hr  !=  AVIERR_OK  )  goto  error;


		// Fill in the header for the video stream....
		// The video stream will run in 15ths of a second....
		_fmemset(&strhdr, 0, sizeof(strhdr));
		strhdr.fccType                = streamtypeVIDEO;// stream type
	
		//strhdr.fccHandler             = compfccHandler;
		strhdr.fccHandler             = 0;
	
		strhdr.dwScale                = 1;
		strhdr.dwRate                 = fps;		    
		strhdr.dwSuggestedBufferSize  = alpbi1->biSizeImage;
		// rectangle for stream
		SetRect(&strhdr.rcFrame, 0, 0,  (int) alpbi1->biWidth,  (int) alpbi1->biHeight);

		// And create the stream;
		hr = AVIFileCreateStream(pfile,	&ps, &strhdr);
		if (hr != AVIERR_OK) 	goto error; 
	
		memset(&opts, 0, sizeof(opts)); 
		aopts[0]->fccType			 = streamtypeVIDEO;
		//aopts[0]->fccHandler		 = mmioFOURCC('M', 'S', 'V', 'C');
		aopts[0]->fccHandler		 = pMgr->m_var.compfccHandler;
		aopts[0]->dwKeyFrameEvery	   = pMgr->m_var.keyFramesEvery;		// keyframe rate 
		aopts[0]->dwQuality		 = pMgr->m_var.compquality;        // compress quality 0-10,000 
		aopts[0]->dwBytesPerSecond	         = 0;		// bytes per second 
		aopts[0]->dwFlags			 = AVICOMPRESSF_VALID | AVICOMPRESSF_KEYFRAMES;    // flags 		
		aopts[0]->lpFormat			 = 0x0;                         // save format 
		aopts[0]->cbFormat			 = 0;
		aopts[0]->dwInterleaveEvery = 0;			// for non-video streams only 
	
		//ver 2.26
		if  (  pMgr->m_var.RecordingMode == ModeFlash  )  {
			//  Internally adjust codec to MSVC 100 Quality 
			aopts[0]->fccHandler = mmioFOURCC('M', 'S', 'V', 'C');	 //msvc
			//  strCodec = CQyString("MS Video 1");
			aopts[0]->dwQuality = 10000;
			}
		else  {	
			  //  Ver 1.2
			  //
			  if  (  (  pMgr->m_var.compfccHandler == pMgr->m_var.CompressorStateIsFor) && (  pMgr->m_var.compfccHandler != 0)) {
				  //make a copy of the pVideoCompressParams just in case after compression, this variable become messed up
				  if  (  MakeCompressParamsCopy(  pMgr->m_var.CompressorStateSize, pMgr->m_var.pVideoCompressParams)) {
					  aopts[0]->lpParms			 = pMgr->m_var.pParamsUse;    
					  aopts[0]->cbParms			 = pMgr->m_var.CompressorStateSize;
				  }
			  }
		}
	
		//  The 1 here indicates only 1 stream
		//  if (!AVISaveOptions(NULL, 0, 1, &ps, (LPAVICOMPRESSOPTIONS *) &aopts)) 
		//        goto error;
	
		hr = AVIMakeCompressedStream(&psCompressed, ps, &opts, NULL);
		if (hr != AVIERR_OK)  	goto error; 

		hr = AVIStreamSetFormat(psCompressed, 0, 
			       alpbi1,	    // stream format
			       alpbi1->biSize +   // format size
			       alpbi1->biClrUsed * sizeof(RGBQUAD));
		if (hr != AVIERR_OK) goto error;	

	}
	
 	//  FreeFrame(  alpbi  );	alpbi  =  NULL;
			

	//////////////////////////////////////////////
	// Recording Audio
	//////////////////////////////////////////////	
	/*
	if ((recordaudio==2) || (useMCI)) 
	{
		
		mciRecordOpen();
		mciSetWaveFormat();
		mciRecordStart();
	
		
		if (shiftType == 1)
		{
			mciRecordPause(tempaudiopath);
			unshifted = 1;
		
		}
		

	}
	else if (recordaudio) {
		InitAudioRecording();
		StartAudioRecording(&m_Format);

	}


	if (shiftType == 2)
	{		
		Sleep(timeshift);
	}
	*/


	DWORD  timeexpended,  frametime,  oldframetime;	
	BOOL   bFirstCapture;			//	=  0;
	
	pAvRecord->initialtime = timeGetTime();		
	bFirstCapture  =  TRUE;	
	oldframetime = 0;
	pAvRecord->nCurrFrame = 0;
	pAvRecord->nActualFrame = 0;

	//timeshift = 100;

	

	//////////////////////////////////////////////
	// WRITING FRAMES
	//////////////////////////////////////////////	

	long  divx,  oldsec;
	divx  =  0;
	oldsec  =  0;
	while  (  !pSharedObj->bQuit  &&  pSharedObj->bUsed  &&  !pMgr->m_var.bStop  ) {  //repeatedly loop

		   /*
		   char  tBuf[256];
		   static  int  iLoops  =  0;  iLoops  ++  ;
		   _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "RecordVideo %d\n"  ),  iLoops  );
		   OutputDebugString(  tBuf  );
		   */
	
		   if  (  !bFirstCapture  )  {			 
			   timeexpended  =  timeGetTime()  -  pAvRecord->initialtime;			
			   }
		   else {
			    frametime = 0;
				timeexpended = 0;			
		   }		
		
		   //  moving region
#if  0
		   pAvRecord->pFrame->m_var.readingRegion = 0;
		   while  (  pAvRecord->pFrame->m_var.writingRegion)
		   {
		   }
		   pAvRecord->pFrame->m_var.readingRegion = 1;

		   if  (   pAvRecord->pFrame->m_var.newRegionUsed   )  {

			   left  =  pAvRecord->pFrame->newRect.left;
			   top  =  pAvRecord->pFrame->newRect.top;
			   pAvRecord->pFrame->m_var.newRegionUsed = 0;
			   //  width and height unchanged
		   }
		   pAvRecord->pFrame->m_var.readingRegion = 0;			
			
		   if  (  left  !=  pCompressVideo->left  ||  top  !=  pCompressVideo->top  )  {	//  2008/11/17£¬½«×óÉÏ½Ç¼ÇÂ¼ÏÂÀ´¡£ÔÚÔ¶³ÌÐ­ÖúÊ±ÓÐÓÃ
			   pCompressVideo->left  =  left;
			   pCompressVideo->top  =  top;

			   pAvRecord->pFrame->PaintBorder(  pAvRecord->borderColor  );
		   }
#endif

		   if  (  doCaptureScreen(  pMgr,  pAvRecord,  pCtx,  left, top,  width,  height,  0,  &cursorPoint  )  )  {
			   traceLogA(  "doCaptureScreen failed"  );
			   Sleep(  1000  );
			   continue;
		   }
		   alpbi1  =  &pAvRecord->bmpInfo.bmiHeader;
			
		   if  (  !bFirstCapture  ) {
			   if  (  timelapse  >  1000  )  frametime  ++  ;
			   else  frametime  =  (  DWORD  )(  (  (  double  )timeexpended  /  1000.0  )  *  (  double  )(  1000.0  /  timelapse  )  );
			   }
		   else  {
			     bFirstCapture  =  FALSE;			//  ÉèÖÃÎª0±íÃ÷ºóÐø¹¤×÷ÊÇµÚ2´ÎÁË
		   }
		
		   pAvRecord->fTimeLength = ((float) timeexpended) /((float) 1000.0);
		
		   /*
		   if ((shiftType == 1) && (unshifted))
		   {
			cc++;
			unsigned long thistime = timeGetTime();
			int diffInTime = thistime - initialtime;
			if (diffInTime >= timeshift)
			{
				
				ErrMsg("cc %d diffInTime %d",cc-1,diffInTime);
				
				if ((recordaudio==2) || (useMCI)) 
				{
					mciRecordResume(tempaudiopath);					
					unshifted = 0;
				}
			

			}

			}
			*/
		
		   if  (  (frametime==0) || (frametime>oldframetime)) { 
			
			   /*
			   //ver 1.8
			   if (shiftType == 1)
			   {
				   if (frametime==0)
				   {
				   //Discard .. do nothing
					}
					else {
						//writr old frame time instead
						hr = AVIStreamWrite(psCompressed,	// stream pointer
						oldframetime,				// time of this frame
						1,				// number to write
						(LPBYTE) alpbi +		// pointer to data
							alpbi->biSize +
							alpbi->biClrUsed * sizeof(RGBQUAD),
							alpbi->biSizeImage,	// size of this frame
						//AVIIF_KEYFRAME,			 // flags....
						0,    //Dependent n previous frame, not key frame
						NULL,
						NULL);
					}
				}
				else {
				*/


			   //
			   SAMPLE_grabberCb_var	var;
			   memset(  &var,  0,  sizeof(  var  )  );
			   //
			   pkts[0].head.uiSampleTimeInMs  =  timeGetTime(  );
			   //
			   pFuncs->pf_BufferCB_av(  pProcInfo,  iIndex_screenCapProcInfo,  &var,  pkts[0].head.uiSampleTimeInMs,  (  BYTE  *  )pAvRecord->pBits,  pAvRecord->bmpInfo.bmiHeader.biSizeImage  );


			   //
				if  (  pMgr->m_var.bSaveToAviFile  )  {
			
					//  if frametime repeats (frametime == oldframetime) ...the avistreamwrite will cause an error
					hr  =  AVIStreamWrite(  psCompressed,	// stream pointer
											frametime,				// time of this frame
											1,				// number to write
											(LPBYTE) alpbi1 +		// pointer to data
												alpbi1->biSize +
												alpbi1->biClrUsed * sizeof(RGBQUAD),
												alpbi1->biSizeImage,	// size of this frame
												//AVIIF_KEYFRAME,			 // flags....
											0,    //Dependent n previous frame, not key frame
											NULL,
											NULL  );
					if  (  hr  !=  AVIERR_OK  )  break;		

				}

				pAvRecord->nActualFrame ++ ;
				pAvRecord->nCurrFrame = frametime;
				pAvRecord->fRate  =  (  (  float  )pAvRecord->nCurrFrame  )  /  pAvRecord->fTimeLength;						
				pAvRecord->fActualRate  =  (  (  float  )pAvRecord->nActualFrame  )  /  pAvRecord->fTimeLength;
			
				//Update recording stats every half a second
				//  divx = timeexpended / 500;
				divx  =  timeexpended  / 30000;		//  20ÃëÏÔÊ¾Ò»´Î×´Ì¬ÐÅÏ¢
				if  (  divx  !=  oldsec  )  {				
					oldsec  =  divx;
					//  InvalidateRect(  pMgr->m_var.hWndMgr,NULL, FALSE);	
					//  traceLogA(  "fRate %f, fActualRate %f",  pAvRecord->fRate,  pAvRecord->fActualRate  );
					qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  _T(  "IsClient"  ),  0,  _T(  "capScreen"  ),  _T(  ""  ),  _T(  "fps %.2f, actual fps %.2f"  ),  pAvRecord->fRate,  pAvRecord->fActualRate  );
				}			
			
				//free memory
				//  FreeFrame(  alpbi  );  alpbi  =  NULL;

				oldframetime  =  frametime;

		   } // if frametime is different


		   nFrames  ++  ;	//  2011/07/25

		   DWORD  timeexpended1  =  timeGetTime()  -  pAvRecord->initialtime;			
		   DWORD	timeexpended_needed  =  nFrames  *  timelapse;
		   int  remainlapse  =  5;
		   if  (  timeexpended_needed  >  timeexpended1  +  5  )  {
			   remainlapse  =  timeexpended_needed  -  timeexpended1;
		   }
		   Sleep(  remainlapse  );

#ifdef  __DEBUG__
		   int  n  =  timeexpended  /  timelapse;
		   #if  0
				traceLog(  _T(  "timeexpended %d, n%d, nFrames %d, remainlaps %d"  ),  timeexpended,  n,  nFrames,  remainlapse  );
		   #endif
#endif

#if  0
		   {
			   //  introduce time lapse
			   //  maximum lapse when recordstate changes will be less than 100 milliseconds
			   int  no_iteration  =  timelapse  /  50;
			   int  remainlapse  =  timelapse  -  no_iteration  *  50;		 
			   for  (  int  j  =  0;  j  <  no_iteration;  j  ++  )  {
				    ::Sleep(  50  ); //  Sleep for 50 milliseconds many times
					if (  pSharedObj->bQuit  )  break;
			   }		
			   if (  !pSharedObj->bQuit  )  Sleep(  remainlapse  );
		   }
#endif

	}  //  for loop
	
error:	
	
	if (  pMgr->m_var.flashingRect) {
#if  0
		pAvRecord->pFrame->ShowWindow(SW_HIDE);
#endif
	}

	OutputDebugString(  _T("1\n" )  );

	if  (  pMgr->m_var.bSaveToAviFile  )  {

		//
		//  Now close the file
		//		

		//  Ver 1.2
		//
		if  (  (  pMgr->m_var.compfccHandler == pMgr->m_var.CompressorStateIsFor) && (  pMgr->m_var.compfccHandler != 0  )  )  {

			//Detach pParamsUse from AVICOMPRESSOPTIONS so AVISaveOptionsFree will not free it
			//(we will free it ourselves)

			//Setting this is no harm even if pParamsUse is not attached to lpParams
			aopts[0]->lpParms			 = 0;    
			aopts[0]->cbParms			 = 0;		
		}
		AVISaveOptionsFree(1,(LPAVICOMPRESSOPTIONS FAR *) &aopts);	

		//////////////////////////////////////////////
		// Recording Audio
		//////////////////////////////////////////////	
		/*
		if  ((recordaudio==2) || (useMCI))  {	
			GetTempWavePath();	
			mciRecordStop(tempaudiopath);
			mciRecordClose();
			//restoreWave();
			}
		else if (recordaudio) {
				StopAudioRecording();
				ClearAudioFile();
		}
		*/

		if  (  pfile  )  AVIFileClose(pfile);
		
		if  (  ps  )  AVIStreamClose(ps);

		if  (  psCompressed  )  AVIStreamClose(psCompressed);

		AVIFileExit();	

		if  (  hr  !=  NOERROR  )  {
			OutputDebugString(  _T(  "Error Creating AVI File"  )  );
		}
		//  Save the file on success
	}

	cleanUp_avRecord(  pAvRecord  );

	OutputDebugString(  _T(  "recordVideo leaves\n"  )  );

	return 0;
#endif
}


 extern "C" DWORD WINAPI recordAvThread( LPVOID pParam )
{
	int								iIndex_screenCapProcInfo	=	(  int  )pParam;

	QY_MC					*		pQyMc						=	QY_GET_GBUF(  );
	int								iServiceId					=	CONST_qyServiceId_mis;
	QY_SERVICEGUI_INFO		*		pSci						=	getServiceGuiInfo(  pQyMc,  iServiceId  );
	//
	MC_VAR_isCli			*		pProcInfo					=	(  MC_VAR_isCli  *  )pSci->pVar;

	//
	FUNCS_for_isCliHelp		*		pFuncs						=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	//
	CAP_procInfo_screen		*		pScreenCapProcInfo			=	(  CAP_procInfo_screen  *  )getCapBmpBySth(  pProcInfo,  iIndex_screenCapProcInfo,  0  );
	if  (  !pScreenCapProcInfo  )  return  -1;

	QY_SHARED_OBJ			*		pSharedObj					=	getSharedObjByIndex(  pProcInfo,  pScreenCapProcInfo->iIndex_sharedObj  );
	if  (  !pSharedObj  )  return  -1;
	COMPRESS_VIDEO			*		pCompressVideo				=	&pScreenCapProcInfo->compressVideo;
	QY_AV_RECORD			*		pAvRecord					=	(  QY_AV_RECORD  *  )pCompressVideo->pData;
	if  (  !pAvRecord  )  return  -1;

	//  2013/03/12
	CTX_screen						ctx;
	memset(  &ctx,  0,  sizeof(  ctx  )  );


	int top		=  pAvRecord->rcUse.top;
	int left	=  pAvRecord->rcUse.left;
	int width	=  pAvRecord->rcUse.right  -  pAvRecord->rcUse.left  +  1;
	int height	=  pAvRecord->rcUse.bottom -  pAvRecord->rcUse.top + 1;
	int fps		=  gQyAvRecordMgr.m_var.frames_per_second;

	pCompressVideo->left  =  left;
	pCompressVideo->top  =  top;
	pCompressVideo->width  =  width;
	pCompressVideo->height  =  height;

	#ifdef  __DEBUG__
			gQyAvRecordMgr.m_var.bSaveToAviFile  =  FALSE;
	#endif

	TCHAR	tBuf[256];
	_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "c:\\tttbbb\\temp%d.avi"  ),  GetTickCount(  )  );
	
	//
	recordVideo(  pProcInfo,  &gQyAvRecordMgr,  &ctx,  iIndex_screenCapProcInfo,  top,  left,  width,  height,  fps,  tBuf  );
	
	//
	OutputDebugString(  _T(  "RecordAVIThread leaves\n"  )  );

	//  2013/03/12
	CTX_addTxt_free(  &ctx.addTxt  );

	//
	pSharedObj->bThreadEnd  =  TRUE;

	PostMessage(  pAvRecord->hWnd_notifyEnd,  CONST_qyWm_postComm,  CONST_qyWmParam_task_end,  0  );	

	return 0;
}

 void FixRectSizePos(LPRECT prc,int maxxScreen, int maxyScreen)
{
	NormalizeRect(prc);
    
	int width=((prc->right)-(prc->left))+1;
	int height=((prc->bottom)-(prc->top))+1;
	
	if (width>maxxScreen) {
		
		prc->left=0;
		prc->right=maxxScreen-1;

	}

	if (height>maxyScreen) {
		
		prc->top=0;
		prc->bottom=maxyScreen-1;

	}

	if (prc->left <0) {

		prc->left= 0;
		prc->right=width-1;

	}

	if (prc->top <0) {

		prc->top= 0;
		prc->bottom=height-1;

	}

	if (prc->right > maxxScreen-1 ) {

		prc->right = maxxScreen-1;
		prc->left= maxxScreen-width;

	}

	if (prc->bottom > maxyScreen-1 ) {

		prc->bottom = maxyScreen-1;
		prc->top= maxyScreen-height;

	}
	
}

#if  0
//  ÏÂÃæµÄÓ¦Ë³ÐòÔö´ó
QY_DMITEM  CONST_normalDpiTable[]  =
{
	{	160,	(  TCHAR  *  )120,	},
	{	176,	(  TCHAR  *  )144,	},	//  
	{	320,	(  TCHAR  *  )240,	},	//  
	{	352,	(  TCHAR  *  )288,	},	//  10Íò
	{	640,	(  TCHAR  *  )480,	},	//  30Íò
	{	648,	(  TCHAR  *  )488,	},	//  35Íò
	{	800,	(  TCHAR  *  )600,	},	//  50Íò
	{	1024,	(  TCHAR  *  )768,	},	//  80Íò
	{	1280,	(  TCHAR  *  )1024,	},	//  130Íò
	{	-1,			},
};
#endif


 int  adjustRectToNormal(  QY_AV_recordMgr  *  pMgr  )
{
	int				iErr	=	-1;
	//  QY_DMITEM	*	pItem	=	CONST_normalDpiTable;
	int				iW;
	int				iH;

	iW  =  pMgr->m_var.rcUse.right  -  pMgr->m_var.rcUse.left  +  1;
	iH  =  pMgr->m_var.rcUse.bottom  -  pMgr->m_var.rcUse.top  +  1;

#if  0
	for  (  ;  pItem->type  !=  -1;	pItem  ++  )  {
		 if  (  iW  <=  pItem->type  &&  iH  <=  (  int  )pItem->des  )  break;
	}
	if  (  pItem->type  ==  -1  )  {		//  Èç¹û³¬¹ý×î´óµÄ¾ÍÈ«ÆÁ
		pMgr->m_var.rcUse.left  =  0;
		pMgr->m_var.rcUse.top  =  0;
		pMgr->m_var.rcUse.right  =  pMgr->m_var.maxxScreen  -  1;
		pMgr->m_var.rcUse.bottom  =  pMgr->m_var.maxyScreen  -  1;
		iErr  =  0;  goto  errLabel;
	}

	if  (  pItem->type  >  pMgr->m_var.maxxScreen  ||  (  int  )pItem->des  >  pMgr->m_var.maxyScreen  )  {		//  Èç¹û×î´óÑ¡Ôñ³¬¹ýÁËÈ«ÆÁ£¬ÄÇÃ´Ò²Ñ¡ÔñÈ«ÆÁ
		pMgr->m_var.rcUse.left  =  0;
		pMgr->m_var.rcUse.top  =  0;
		pMgr->m_var.rcUse.right  =  pMgr->m_var.maxxScreen  -  1;
		pMgr->m_var.rcUse.bottom  =  pMgr->m_var.maxyScreen  -  1;
		iErr  =  0;  goto  errLabel;
	}
	
	if  (  pMgr->m_var.rcUse.left  +  pItem->type  >  pMgr->m_var.maxxScreen  -  1  )  {
		pMgr->m_var.rcUse.left  =  pMgr->m_var.maxxScreen  -  1  -  pItem->type;
	}
	if  (  pMgr->m_var.rcUse.top  +   (  int  )pItem->des  >  pMgr->m_var.maxyScreen  -  1  )  {
		pMgr->m_var.rcUse.top  =  pMgr->m_var.maxyScreen  -  1  -  (  int  )pItem->des;
	}

	pMgr->m_var.rcUse.right  =  pMgr->m_var.rcUse.left  +  pItem->type  -  1;
	pMgr->m_var.rcUse.bottom  =  pMgr->m_var.rcUse.top  +  (  int  )pItem->des  -  1;
#endif

	//  不能太小
	iW  =  max(  iW,  64  );
	iH  =  max(  iH,  64  );

	//
	if  (  iW  %  4  )  iW  =  (  iW  /  4  +  1  )  *  4;
	if  (  iH  %  4  )  iH  =  (  iH  /  4  +  1  )  *  4;
	
	//
	if  (  iW  >  pMgr->m_var.maxxScreen  ||  iH  >  pMgr->m_var.maxyScreen  )  {
		pMgr->m_var.rcUse.left  =  0;
		pMgr->m_var.rcUse.top  =  0;
		pMgr->m_var.rcUse.right  =  pMgr->m_var.maxxScreen  -  1;
		pMgr->m_var.rcUse.bottom  =  pMgr->m_var.maxyScreen  -  1;
		iErr  =  0;  goto  errLabel;
	}
	//
	if  (  pMgr->m_var.rcUse.left  +  iW  >  pMgr->m_var.maxxScreen  -  1  )  {
		pMgr->m_var.rcUse.left  =  pMgr->m_var.maxxScreen  -  1  -  iW;
	}
	//
	if  (  pMgr->m_var.rcUse.top  +  iH  >  pMgr->m_var.maxyScreen  -  1  )  {
		pMgr->m_var.rcUse.top =  pMgr->m_var.maxyScreen  -  1  -  iH;
	}
	//
	pMgr->m_var.rcUse.right  =  pMgr->m_var.rcUse.left  +  iW  -  1;
	pMgr->m_var.rcUse.bottom  =  pMgr->m_var.rcUse.top  +  iH  -  1;

	//
	iErr  =  0;
errLabel:
	
	traceLogA(  "left %d, top %d, width %d, heigth %d",  pMgr->m_var.rcUse.left,  pMgr->m_var.rcUse.top,  pMgr->m_var.rcUse.right  -  pMgr->m_var.rcUse.left,  pMgr->m_var.rcUse.bottom  -  pMgr->m_var.rcUse.top  );

	return  iErr;
}

 //
 int  adjustRectToCorrect(  QY_AV_recordMgr  *  pMgr  )
 {
#if  0
	 if  (  pMgr->m_var.maxxScreen  ==  1366  )  {	
		 pMgr->m_var.rcUse.right  =  1360  -  1;
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  _T(  "IsClient"  ),  0,  _T(  "capScreen"  ),  _T(  ""  ),  _T(  "toSelectRegion: 1366 -> 1360"  )  );
	 }
#endif
	 int  iW,  iH;
	 	 
	 iW  =  pMgr->m_var.rcUse.right  -  pMgr->m_var.rcUse.left  +  1;	
	 iH  =  pMgr->m_var.rcUse.bottom  -  pMgr->m_var.rcUse.top  +  1;

	 //	 	
	 if  (  iW  %  4  ||  iH  %  4  )  {	//  这里要稍微缩小一点，避免超出屏幕范围
		 iW  =  (  iW  /  4  )  *  4;		 
		 iH  =  (  iH  /  4  )  *  4;
		 //
		 pMgr->m_var.rcUse.right  =  pMgr->m_var.rcUse.left  +  iW  -  1;
		 pMgr->m_var.rcUse.bottom  =  pMgr->m_var.rcUse.top  +  iH  -  1;
		 //
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  _T(  "IsClient"  ),  0,  _T(  "capScreen"  ),  _T(  ""  ),  _T(  "toSelectRegion: adjustRectToCorrect"  )  );
	 }
	 
	 return  0;
 }



 long WINAPI avRecordMgrWndProc(HWND hWnd, UINT wMessage, WPARAM wParam, LPARAM lParam)
{
	if  (  wMessage  ==  WM_avRecord_start  )  {
		OutputDebugString(  _T(  "avRecord_start\n" )  );
		return  0;		
	}
	if  (  wMessage  ==  WM_avRecord_stop  )  {
		OutputDebugString(  _T(  "avRecord stop\n"  )  );
		return  0;
	}
	if  (  wMessage  ==  WM_avRecord_cursor  )  {
		//  OutputDebugString(  _T(  "avRecord cursor\n"  )  );

		gQyAvRecordMgr.m_var.hSavedCursor  =  (HCURSOR) wParam;		

		return  0;
	}

    
    switch (wMessage)
    {

		case WM_MOUSEMOVE:
        {


			//  else if (MouseCaptureMode==1) 
			{ //Variable Region

				    if (  gQyAvRecordMgr.m_var.bCapturing)
					{						
						POINT pt;
						GetCursorPos(&pt);

						HDC hScreenDC = GetDC(hWnd);	
						
						DrawSelect(hScreenDC, FALSE, &gQyAvRecordMgr.m_var.rcClip);  // erase old rubber-band
						
						gQyAvRecordMgr.m_var.rcClip.left = gQyAvRecordMgr.m_var.ptOrigin.x;
						gQyAvRecordMgr.m_var.rcClip.top = gQyAvRecordMgr.m_var.ptOrigin.y;					
						gQyAvRecordMgr.m_var.rcClip.right = pt.x;
						gQyAvRecordMgr.m_var.rcClip.bottom = pt.y;
						
						NormalizeRect(&gQyAvRecordMgr.m_var.rcClip);
						DrawSelect(hScreenDC, TRUE, &gQyAvRecordMgr.m_var.rcClip); // new rubber-band
						//TextOut(hScreenDC,pt.x,pt.y,"Lolo",4);

						ReleaseDC(hWnd,hScreenDC);
					}

			}	

			return DefWindowProc(hWnd, wMessage, wParam, lParam);

        }
		case WM_LBUTTONUP:
		{
			
			//else if (MouseCaptureMode==1) 
			{

				NormalizeRect(&gQyAvRecordMgr.m_var.rcClip);
				gQyAvRecordMgr.m_var.old_rcClip=gQyAvRecordMgr.m_var.rcClip;
				gQyAvRecordMgr.m_var.bCapturing = FALSE;				

			}				
			
			ShowWindow(hWnd,SW_HIDE);

			if (!IsRectEmpty(&gQyAvRecordMgr.m_var.old_rcClip)) {
			
				NormalizeRect(&gQyAvRecordMgr.m_var.old_rcClip);
				CopyRect(&gQyAvRecordMgr.m_var.rcUse, &gQyAvRecordMgr.m_var.old_rcClip);
				
				if  (  !gQyAvRecordMgr.m_var.ucbNotAutoResizeCapScreen  )  {
					//  ÕâÀïÒªÐ£Õýµ½³£ÓÃ·Ö±æÂÊ
					adjustRectToNormal(  &gQyAvRecordMgr  );
				}

				//  2013/04/26
				adjustRectToCorrect(  &gQyAvRecordMgr  );

				//
				PostMessage(  gQyAvRecordMgr.m_var.hWndStarter,  CONST_qyWm_postComm,  CONST_qyWmParam_avRecord_start,  0  ); 

			}		        

            return DefWindowProc(hWnd, wMessage, wParam, lParam);    
		
		}		
		case WM_LBUTTONDOWN:
        {
             // User pressed left button, initialize selection
             // Set origin to current mouse position (in window coords)			

			//  if (MouseCaptureMode==1) 
			{

                POINT pt;
				GetCursorPos(&pt);
				
				gQyAvRecordMgr.m_var.ptOrigin=pt;

                gQyAvRecordMgr.m_var.rcClip.left = gQyAvRecordMgr.m_var.rcClip.right = pt.x;
                gQyAvRecordMgr.m_var.rcClip.top = gQyAvRecordMgr.m_var.rcClip.bottom = pt.y;                
				
				NormalizeRect(&gQyAvRecordMgr.m_var.rcClip);     // Make sure it is a normal rect
				HDC hScreenDC = GetDC(hWnd);
                DrawSelect(hScreenDC, TRUE, &gQyAvRecordMgr.m_var.rcClip); // Draw the rubber-band box
				ReleaseDC(hWnd,hScreenDC);

                gQyAvRecordMgr.m_var.bCapturing = TRUE;

			}

			return DefWindowProc(hWnd, wMessage, wParam, lParam);    
        }
		
		case WM_RBUTTONDOWN:
        {			

			return DefWindowProc(hWnd, wMessage, wParam, lParam);    

		}		
		case WM_KEYDOWN:
        /*
		{
			int nVirtKey = (int) wParam;    // virtual-key code 
			int lKeyData = lParam;          // key data 			

			//ver 1.2
 			if (nVirtKey==(int) keyRecordCancel) { //Cancel the operation
			//if (nVirtKey==VK_ESCAPE) { 

				if (MouseCaptureMode==0) {
				
					//erase final
					HDC hScreenDC = GetDC(hWnd);		
					DrawSelect(hScreenDC, FALSE, &old_rcClip);    
					ReleaseDC(hWnd,hScreenDC);

				}
				else if (MouseCaptureMode==1) {

					NormalizeRect(&rcClip);
					old_rcClip=rcClip;
					if (bCapturing) bCapturing = FALSE;				

				}		
				
				ShowWindow(hWnd,SW_HIDE);				

				//ver 1.2
				AllowNewRecordStartKey = TRUE; 

			} //VK_ESCAPE (keyRecordCancel)

			return DefWindowProc(hWnd, wMessage, wParam, lParam);    

		}
		*/

        
		default:
			return DefWindowProc(hWnd, wMessage, wParam, lParam);    
            
    }
	
	
	return 0;
	
}


 int  createMouseCaptureWnd(  HINSTANCE  g_hInst,  QY_AV_recordMgr  *  p  )
{
	    HINSTANCE hInstance = g_hInst;	//  AfxGetInstanceHandle( );

		WNDCLASS wndclass;

		wndclass.style = 0;
        wndclass.lpfnWndProc = (WNDPROC)avRecordMgrWndProc;
        wndclass.cbClsExtra = 0;
        wndclass.cbWndExtra = 0;
        wndclass.hInstance = hInstance;
        wndclass.hIcon = LoadIcon(  hInstance,  _T(  "AvRecord"  )  );
        
		HICON  hcur  =  LoadCursor(  NULL,  IDC_CROSS  );
		wndclass.hCursor = hcur;
        
        wndclass.hbrBackground = NULL;

        //wndclass.lpszMenuName = (LPSTR)"MAINMENU";
		wndclass.lpszMenuName = NULL;
        wndclass.lpszClassName = _T(  "AvRecordMgrWindow"  );

        if (!RegisterClass(&wndclass))  return 0;
        
		//
#if  0
		HDC hScreenDC=::GetDC(NULL);
		//
		#if  0	//  2016/10/12
				p->m_var.maxxScreen = GetDeviceCaps(hScreenDC,HORZRES);
				p->m_var.maxyScreen = GetDeviceCaps(hScreenDC,VERTRES);
		#else
				p->m_var.maxxScreen = GetDeviceCaps(hScreenDC,DESKTOPHORZRES);
				p->m_var.maxyScreen = GetDeviceCaps(hScreenDC,DESKTOPVERTRES);		
		#endif
		//
		::ReleaseDC(NULL,hScreenDC);		
#endif
		//  2017/10/10
		getScreenRes(  0,  (  unsigned  int  *  )&p->m_var.maxxScreen,  (  unsigned  int  *  )&p->m_var.maxyScreen  );

		//
		p->m_var.hWndMgr = CreateWindowEx(WS_EX_TOPMOST,  _T(  "AvRecordMgrWindow"  ), _T(  "AvRecord"  ),WS_POPUP,0,0,p->m_var.maxxScreen,p->m_var.maxyScreen,NULL,NULL, hInstance,  NULL);

		return 0;

}


 int  destroyMouseCaptureWnd(  QY_AV_recordMgr  *  p  )
{
	if  (  p->m_var.hWndMgr  ) ::DestroyWindow(  p->m_var.hWndMgr  );
	return  0;
}


