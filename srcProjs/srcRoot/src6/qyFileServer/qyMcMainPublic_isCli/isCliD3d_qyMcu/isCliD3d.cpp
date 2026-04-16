// isCliD3d.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include	<stdlib.h>
#include	<tchar.h>

//#include <d3dx9.h>

#include	"qyMcMainCommon.h"

#include	"isCliD3dCommon.h"
#include	"wallMemMgr.h"
#include	"dynFuncs_d3dCall.h"
#include	"GuiShare.h"

//

  extern  "C" __declspec(dllexport)  int   set_g_pQyMc_isCliD3d(  void  *  pQyMc  )
{

#ifdef  __DEBUG__
		traceLog(  _T(  "set_g_pQyMc called"  )  );
#endif

	//  2013/07/31
	//set_g_pShowInfoStruct(  g_pQyMc->pShowInfoStruct  );


	return  0;
}




//
D3D_context	g_d3dContext  =  {  NULL,  };


//
extern  "C" __declspec(  dllexport  )  void  *  GBuf_d3d_isCli_new(  )
{
	int					iErr	=	-1;
	GBuf_d3d_isCli  *	p  =  NULL;
	int					size;

	size  =  sizeof(  GBuf_d3d_isCli  );
	p  =  (  GBuf_d3d_isCli  *  )mymalloc(  size  );
	if  (  !p  )  goto  errLabel;
	memset(  p,  0,  size  );

	//  2016/05/28
   size  =  sizeof(  D3D_wnd_mgr  );
   p->pD3dWndMgr  =  (  D3D_wnd_mgr  *  )mymalloc(  size  );
   if  (  !p->pD3dWndMgr  )  goto  errLabel;
   memset(  p->pD3dWndMgr,  0,  size  );
   p->pD3dWndMgr->ucMaxCnt  =  mycountof(  p->pD3dWndMgr->mems  );

   //
   showInfo_open0(  0,  0,  _T(  "GBuf_d3d_isCli_new: malloc pD3dWndMgr"  )  );


	//
	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		GBuf_d3d_isCli_free(  (  void  **  )&p  );
	}
	return  iErr  ?  NULL  :  p;
}


extern  "C" __declspec(  dllexport  )  void  GBuf_d3d_isCli_free(  void  **  ppGBuf_d3d_isCli  )
{
	if  (  !ppGBuf_d3d_isCli  )  return;
	GBuf_d3d_isCli  *  p  =  *(  GBuf_d3d_isCli  **  )ppGBuf_d3d_isCli;
	if  (  !p  )  return;
	int  i;

	//
	if  (  p->pD3dWndMgr  )  {			
		D3D_wnd  *  pD3dWnd  =  NULL;
		for  (  i  =  0;  i  <  p->pD3dWndMgr->ucMaxCnt;  i  ++  )  {						   
			 pD3dWnd  =  &p->pD3dWndMgr->mems[i];						  
			 if  (  pD3dWnd->hWnd  )  {			
				 MACRO_qyAssert(  0,  _T(  "d3dWnd still exists."  )  );						   
			 }					  
		}
				
		//		
		showInfo_open0(  0,  0,  _T(  "GBuf_d3d_isCli_free: free pD3dWndMgr"  )  );
		
		//  2016/05/28
		MACRO_safeFree(  p->pD3dWndMgr  );
	}

	//
	free(  p  );
	*ppGBuf_d3d_isCli  =  NULL;
	return;
}

