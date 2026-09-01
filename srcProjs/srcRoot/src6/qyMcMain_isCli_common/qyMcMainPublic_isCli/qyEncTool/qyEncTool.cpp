// qyEncTool.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

//
//#include	<d3d11.h>
//#include	<d3d11_1.h>

//#include	"d3dx11effect.h"
#include	"qyMcMainCommon.h"

#include "qyEncTool.h"

#include	"qyEncToolCommon.h"

#include	"load_isD3dFunc.h"
#include	"dynLib_isD3dFunc.h"

//
//#include	"qisD3d_open.h"
#include	"tmp_d3d11_dev_open.h"
#include	"enc_d3d11_dev_open.h"
//#include	"enc_d3d11_func.h"



//
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

//
CQyEncTool	g_tool;


//
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	if  (  g_tool.init(  lpCmdLine  )  )  goto  errLabel;

	g_tool.run(  );

errLabel:

	g_tool.exit(  );



	return (int) 0;
}





//
int  evt_encDev_YUVReader_myLoadNextFrame(	void  *  pQDC_OBJ_INFO,
						     	void									*	pENC_d3d11_devVar,
								//
								LP_ID3D11Device								m_pD3D11Device,							
								LP_ID3D11DeviceContext						m_pD3D11Ctx,			
							
								//							
								LP_ID3D11Device1							m_pd3d11Device1,
							
								//
								LP_ID3D11VideoDevice						m_pDX11VideoDevice,						   							
								LP_ID3D11VideoContext						m_pVideoContext,							
							
								//
								PKT_sharedTex_info						*	pPktSharedTexInfo,
															
								//							
								LP_ID3D11Texture2D							pRTTexture2D,
								LP_ID3D11RenderTargetView					pRTV,					

								//							
								int											m_nViews,
								//
								BOOL										g_bShowEnc_sharedTexStatus,
								//
								QIS_trace_common						*	pQtc
						   	)
{
	ENC_d3d11_devVar_head  *  p  =  (  ENC_d3d11_devVar_head  *  )pENC_d3d11_devVar;
	if  (  !p  )  return  -1;
	
	CCtxQmcEvt  *  pProcInfo  =  g_tool.m_var.pCtx;
	if  (  !pProcInfo  )  return  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  -1;
	
	DYN_LIB_isD3dFunc  *  pLib  =  (  DYN_LIB_isD3dFunc  *  )pProcInfo->m_var.pDynLib_isD3dFunc;
	if  (  !pLib  )  return  -1;

	//
	p->pCtxQyTmpl_vt  =  pProcInfo;

	//
	return  pLib->pf_encDev_YUVReader_myLoadNextFrame(  pQDC_OBJ_INFO,  pENC_d3d11_devVar,  m_pD3D11Device,  m_pD3D11Ctx,  m_pd3d11Device1,  m_pDX11VideoDevice,  
		m_pVideoContext,  pPktSharedTexInfo,  pRTTexture2D,  pRTV,  m_nViews,  g_bShowEnc_sharedTexStatus,  pQtc  );


}

//
int  evt_preForTest_encDev_YUVReader_myLoadNextFrame(	void  *  pQDC_OBJ_INFO,
						     							void									*	pENC_d3d11_devVar  								
														)
{
	ENC_d3d11_devVar_head  *  p  =  (  ENC_d3d11_devVar_head  *  )pENC_d3d11_devVar;
	if  (  !p  )  return  -1;
	
	CCtxQmcEvt  *  pProcInfo  =  g_tool.m_var.pCtx;
	if  (  !pProcInfo  )  return  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  -1;
	
	DYN_LIB_isD3dFunc  *  pLib  =  (  DYN_LIB_isD3dFunc  *  )pProcInfo->m_var.pDynLib_isD3dFunc;
	if  (  !pLib  )  return  -1;

	//
	p->pCtxQyTmpl_vt  =  pProcInfo;

	return  0;
}




//
void  *  evt_qoi_getPtrProperty(  void  *  pQdcObjInfoParam,  int  propertyId  )
{
	CCtxQmcEvt  *  pProcInfo  =  g_tool.m_var.pCtx;
	if  (  !pProcInfo  )  return  NULL;

	switch  (  propertyId  )  {

			case  CONST_qdcPropId_PF_encDev_YUVReader_myLoadNextFrame:  {
				  void  *  pf  =  evt_encDev_YUVReader_myLoadNextFrame;
				  return  pf;
				  }
				  break;
			case  CONST_qdcPropId_PF_preForTest_encDev_YUVReader_myLoadNextFrame:  {
				  void  *  pf  =  evt_preForTest_encDev_YUVReader_myLoadNextFrame;
				  return  pf;
				  }
				  break;
			default:
					break;
	}

	//
	return  get_ptr_isD3dFunc(  pProcInfo->m_var.pDynLib_isD3dFunc,  propertyId  );
}
