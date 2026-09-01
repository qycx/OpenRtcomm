

#include	"stdafx.h"
#include	<mmsystem.h>
#include	"qmOpenCommon.h"
#include	"qisCamCapOpenCommon.h"


QIS_guiOpen	*	g_pGuiOpen	=	NULL;

struct							{
		SAMPLE_grabberCb_var	m_var;
}		g_buf;

extern  "C"  int  __declspec(  dllexport  ) setGuiOpen(  QIS_guiOpen  *  pGuiOpen  )
{
	g_pGuiOpen  =  pGuiOpen;

	return  0;
}


 extern  "C"  int  __declspec(  dllexport  )  initVideoCapDev(  LPCTSTR  devicePath_selected,  BITMAPINFOHEADER  *  pBih_suggested,  BOOL  bForConfig,  HWND hWnd,  void  **  ppVideoCapDevParam  )
{
	memset(  &g_buf,  0,  sizeof(  g_buf  )  );
	if  (  g_pGuiOpen  )  g_pGuiOpen->pf_showNotification(  0,  0,  0,  _T(  "initVideoCapDev called"  )  );
	return  -1;
}


extern  "C"  int  __declspec(  dllexport  )  exitVideoCapDev(  void  **  ppVideoCapDevParam  )
{
	if  (  g_buf.m_var.pMsgBuf  )  free(  g_buf.m_var.pMsgBuf  );
#if  0
	if  (  g_buf.m_var.pBuf  )  free(  g_buf.m_var.pBuf  );
#endif

	if  (  g_pGuiOpen  )  g_pGuiOpen->pf_showNotification(  0,  0,  0,  _T(  "exitVideoCapDev called"  )  );
	return  -1;
}

extern  "C"  BOOL  __declspec(  dllexport  )  bGetCapturePara(  void  *  pProcInfo,  int  iIndex_capBmp,  PF_BufferCB_av  pf,  unsigned  int  uiBufSize_pMsgBuf,  unsigned  int  uiBufSize_pBuf,  void  *  pVideoCapDevParam,  QY_VIDEO_HEADER  *  pVh_org  )
{
	g_buf.m_var.uiBufSize_pMsgBuf  =  uiBufSize_pMsgBuf;
	g_buf.m_var.pMsgBuf  =  malloc(  g_buf.m_var.uiBufSize_pMsgBuf  );

#if  0
	g_buf.m_var.uiBufSize_pBuf  =  uiBufSize_pBuf;
	g_buf.m_var.pBuf  =  (  BYTE  *  )malloc(  g_buf.m_var.uiBufSize_pBuf  );
#endif
	
	//  return  TRUE;
	return  FALSE;
}


 extern  "C"  int  __declspec(  dllexport  )  startCapture(  void  *  pVideoCapDevParam  )
 {
	 return  -1;
 }

extern  "C"  int  __declspec(  dllexport  )  stopCapture(  void  *  pVideoCapDevParam  )
{
	return  -1;
}


