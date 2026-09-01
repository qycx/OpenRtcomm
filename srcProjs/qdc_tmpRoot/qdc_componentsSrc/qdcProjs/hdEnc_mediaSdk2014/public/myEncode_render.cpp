

#include	"stdafx.h"
#include "mfx_samples_config.h"


#include <windowsx.h>
#include <dwmapi.h>
#include <mmsystem.h>

#include "sample_defs.h"
#include "tmp_decode_render.h"


#include	"myEncode_render.h"




CMyEncodeD3DRender::CMyEncodeD3DRender(  )
{
}


CMyEncodeD3DRender::~CMyEncodeD3DRender(  )
{
}


LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//
mfxStatus CMyEncodeD3DRender::Init(sWindowParams pWParams)
{
    mfxStatus sts = MFX_ERR_NONE;

    // window part
    m_sWindowParams = pWParams;

    WNDCLASS window;
    MSDK_ZERO_MEMORY(window);

    window.lpfnWndProc= (WNDPROC)WindowProc;
    window.hInstance= GetModuleHandle(NULL);;
    window.hCursor= LoadCursor(NULL, IDC_ARROW);
    window.lpszClassName= m_sWindowParams.lpClassName;

    if (!RegisterClass(&window))  {
        //  return MFX_ERR_UNKNOWN;
		DWORD  dwErr  =  GetLastError(  );
		//
		if  (  dwErr  !=  ERROR_CLASS_ALREADY_EXISTS  )  {
			return  MFX_ERR_UNKNOWN;
		}
	}

	//
    EnumDisplayMonitors(NULL, NULL, &CDecodeD3DRender::MonitorEnumProc, (LPARAM)this);
    if(!m_bIsMonitorFound)
        return MFX_ERR_NOT_FOUND;

    ::RECT displayRegion = {CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT};

    //right and bottom fields consist of width and height values of displayed reqion
    if (0 != m_sWindowParams.nx )
    {
        displayRegion.right  = (m_RectWindow.right - m_RectWindow.left)  / m_sWindowParams.nx;
        displayRegion.bottom = (m_RectWindow.bottom - m_RectWindow.top)  / m_sWindowParams.ny;
        displayRegion.left   = displayRegion.right * (m_sWindowParams.ncell % m_sWindowParams.nx) + m_RectWindow.left;
        displayRegion.top    = displayRegion.bottom * (m_sWindowParams.ncell / m_sWindowParams.nx) + m_RectWindow.top;
    }
    else
    {
        displayRegion.right = pWParams.nWidth;
        displayRegion.bottom = pWParams.nHeight;
        displayRegion.left = m_RectWindow.left;
        displayRegion.top= m_RectWindow.top;
    }

    //no title window style if required
    DWORD dwStyle = NULL == m_sWindowParams.lpWindowName ?  WS_POPUP|WS_BORDER|WS_MAXIMIZE : WS_OVERLAPPEDWINDOW;

    m_Hwnd = CreateWindowEx(NULL,
        m_sWindowParams.lpClassName,
        m_sWindowParams.lpWindowName,
        !m_sWindowParams.bFullScreen ? dwStyle : (WS_POPUP),
        !m_sWindowParams.bFullScreen ? displayRegion.left : 0,
        !m_sWindowParams.bFullScreen ? displayRegion.top : 0,
        !m_sWindowParams.bFullScreen ? displayRegion.right : GetSystemMetrics(SM_CXSCREEN),
        !m_sWindowParams.bFullScreen ? displayRegion.bottom : GetSystemMetrics(SM_CYSCREEN),
        m_sWindowParams.hWndParent,
        m_sWindowParams.hMenu,
        m_sWindowParams.hInstance,
        m_sWindowParams.lpParam);

    if (!m_Hwnd)
        return MFX_ERR_UNKNOWN;

	//  2015/10/03
	if  (  bShowRenderWnd(  )  )  {
	    ShowWindow(m_Hwnd, SW_SHOWDEFAULT);
	    UpdateWindow(m_Hwnd);
	}

	//
#ifdef WIN64
    SetWindowLongPtr(m_Hwnd, GWLP_USERDATA, (LONG_PTR)this);
#else
    SetWindowLong(m_Hwnd, GWL_USERDATA, PtrToLong(this));
#endif

    m_hwdev->SetHandle((mfxHandleType)MFX_HANDLE_DEVICEWINDOW, m_Hwnd);
    sts = m_hwdev->Reset();
    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

    return sts;
}

