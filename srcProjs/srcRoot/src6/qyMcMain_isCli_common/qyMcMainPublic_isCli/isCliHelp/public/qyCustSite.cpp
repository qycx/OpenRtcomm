

#include	"stdafx.h"

#define  __noDbg_new__

#include	"qyCommon.h"
#include	"qyWmComm.h"
#include	"qyCustSite.h"
 ///////////////////////////////////////////////////////////////

IDispatch		*	gpDispOM		=	NULL;
 



BEGIN_INTERFACE_MAP(CCustomControlSite, COleControlSite)
	INTERFACE_PART(CCustomControlSite, IID_IDocHostUIHandler, DocHostUIHandler)
END_INTERFACE_MAP()


CCustomControlSite::CCustomControlSite(COleControlContainer* pContainer)
: COleControlSite(pContainer)
{
	OutputDebugString(  _T(  "CCustomControlSite::CCustomControlSite(  )\n"  )  );
}

CCustomControlSite::~CCustomControlSite()
{
	OutputDebugString(  _T(  "CCustomControlSite::~CCustomControlSite(  )\n"  )  );
}

//  2013/12/13
DWORD CCustomControlSite::GetStyle() const
{
	DWORD dwStyle = m_dwStyle;

	//For windowed ActiveX controls, get visible and disabled styles from Win32 HWND.
	if(!m_bIsWindowless)
	{
		dwStyle |= (::GetWindowLong(m_hWnd, GWL_STYLE) & (WS_VISIBLE|WS_DISABLED) );
	}

#if  0
	TRY
	{
		//Override Win32 with DISPID_ENABLED, if control implement it.
		BOOL bEnabled = TRUE;
		GetProperty(DISPID_ENABLED, VT_BOOL, &bEnabled);
		dwStyle = bEnabled ? dwStyle & ~WS_DISABLED : dwStyle | WS_DISABLED;		
	}
	END_TRY

	TRY
	{
		short sBorderStyle = 0;
		GetProperty(DISPID_BORDERSTYLE, VT_I2, &sBorderStyle);
		if (sBorderStyle == 1)
			dwStyle |= WS_BORDER;
	}
	END_TRY
#endif

	return dwStyle;
}


STDMETHODIMP_(ULONG) CCustomControlSite::XDocHostUIHandler::AddRef()
{
	METHOD_PROLOGUE_EX_(CCustomControlSite, DocHostUIHandler)
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CCustomControlSite::XDocHostUIHandler::Release()
{
	METHOD_PROLOGUE_EX_(CCustomControlSite, DocHostUIHandler)
	return pThis->ExternalRelease();
}

STDMETHODIMP CCustomControlSite::XDocHostUIHandler::QueryInterface(
		  REFIID iid, LPVOID far* ppvObj)     
{
	METHOD_PROLOGUE_EX_(CCustomControlSite, DocHostUIHandler)
	return pThis->ExternalQueryInterface(&iid, ppvObj);
}


STDMETHODIMP CCustomControlSite::XDocHostUIHandler::GetHostInfo(
	DOCHOSTUIINFO *pInfo)
{
	METHOD_PROLOGUE_EX_(CCustomControlSite, DocHostUIHandler)
	//  pInfo->dwFlags  =  DOCHOSTUIFLAG_NO3DBORDER;
	pInfo->dwFlags  =  0;								//  2007/05/24, 注意这里的参数表明是有边框，还是没边框

	pInfo->dwDoubleClick  =  DOCHOSTUIDBLCLK_DEFAULT;

	return  S_OK;
}

STDMETHODIMP CCustomControlSite::XDocHostUIHandler::ShowUI(
	DWORD dwID, LPOLEINPLACEACTIVEOBJECT pActiveObject,
	LPOLECOMMANDTARGET pCommandTarget, LPOLEINPLACEFRAME pFrame,
	LPOLEINPLACEUIWINDOW pDoc)
{
	METHOD_PROLOGUE_EX_(CCustomControlSite, DocHostUIHandler)

	return S_OK;
}


STDMETHODIMP CCustomControlSite::XDocHostUIHandler::HideUI(void)
{
	METHOD_PROLOGUE_EX_(CCustomControlSite, DocHostUIHandler)

	return S_OK;
}


STDMETHODIMP CCustomControlSite::XDocHostUIHandler::UpdateUI(void)
{
	METHOD_PROLOGUE_EX_(CCustomControlSite, DocHostUIHandler)

	return S_OK;
}

STDMETHODIMP CCustomControlSite::XDocHostUIHandler::EnableModeless(BOOL fEnable)
{
	METHOD_PROLOGUE_EX_(CCustomControlSite, DocHostUIHandler)
	return E_NOTIMPL;
}


STDMETHODIMP CCustomControlSite::XDocHostUIHandler::OnDocWindowActivate(BOOL fActivate)
{
	METHOD_PROLOGUE_EX_(CCustomControlSite, DocHostUIHandler)

	return E_NOTIMPL;
}


STDMETHODIMP CCustomControlSite::XDocHostUIHandler::OnFrameWindowActivate(
	BOOL fActivate)
{
	METHOD_PROLOGUE_EX_(CCustomControlSite, DocHostUIHandler)

	return E_NOTIMPL;
}

STDMETHODIMP CCustomControlSite::XDocHostUIHandler::ResizeBorder(
	LPCRECT prcBorder, LPOLEINPLACEUIWINDOW pUIWindow, BOOL fFrameWindow)
{
	METHOD_PROLOGUE_EX_(CCustomControlSite, DocHostUIHandler)
	return E_NOTIMPL;
}

STDMETHODIMP CCustomControlSite::XDocHostUIHandler::ShowContextMenu(
	DWORD dwID, LPPOINT ppt, LPUNKNOWN pcmdtReserved, LPDISPATCH pdispReserved)
{
	METHOD_PROLOGUE_EX_(CCustomControlSite, DocHostUIHandler)

	return S_OK;
}

STDMETHODIMP CCustomControlSite::XDocHostUIHandler::TranslateAccelerator(
	LPMSG lpMsg, const GUID* pguidCmdGroup, DWORD nCmdID)
{
	METHOD_PROLOGUE_EX_(CCustomControlSite, DocHostUIHandler)

	return S_FALSE;
}


STDMETHODIMP CCustomControlSite::XDocHostUIHandler::GetOptionKeyPath(
	LPOLESTR* pchKey, DWORD dwReserved)
{
	METHOD_PROLOGUE_EX_(CCustomControlSite, DocHostUIHandler)
	return E_NOTIMPL;
}


STDMETHODIMP CCustomControlSite::XDocHostUIHandler::GetDropTarget(
	LPDROPTARGET pDropTarget, LPDROPTARGET* ppDropTarget)
{
	METHOD_PROLOGUE_EX_(CCustomControlSite, DocHostUIHandler)

	
	if  (  pThis->m_hWnd  )  {
		//  
		HWND  hParent  =  GetParent(  pThis->m_hWnd  );
		if  (  hParent  )  {
			QY_WMBUF_COMM	wmBuf;
			memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
			wmBuf.uiType  =  CONST_qyWmParam_getDropTarget;
			wmBuf.u.getIDropTarget.hWnd  =  pThis->m_hWnd;
			if  (  SendMessage(  hParent,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  )  ==  CONST_qyWmRc_ok  )  {
				if  (  wmBuf.u.getIDropTarget.pIDropTarget  )  {
				
					*ppDropTarget  =  (  IDropTarget  *  )wmBuf.u.getIDropTarget.pIDropTarget;
				
					return  S_OK;	
				}
			}

		}
		
	}

	return  E_NOTIMPL;
}


STDMETHODIMP CCustomControlSite::XDocHostUIHandler::GetExternal(LPDISPATCH *lppDispatch)
{
	//  METHOD_PROLOGUE_EX_(CCustomControlSite, DocHostUIHandler)
	IDispatch  *  pDisp  =  gpDispOM;

	if  (  !pDisp  )  return  E_NOTIMPL;

	pDisp->AddRef(  );
	*lppDispatch  =  pDisp;
	return  S_OK;
}



STDMETHODIMP CCustomControlSite::XDocHostUIHandler::TranslateUrl(
	DWORD dwTranslate, OLECHAR* pchURLIn, OLECHAR** ppchURLOut)
{
	METHOD_PROLOGUE_EX_(CCustomControlSite, DocHostUIHandler)
	return E_NOTIMPL;
}


STDMETHODIMP CCustomControlSite::XDocHostUIHandler::FilterDataObject(
	LPDATAOBJECT pDataObject, LPDATAOBJECT* ppDataObject)
{
	METHOD_PROLOGUE_EX_(CCustomControlSite, DocHostUIHandler)

	return E_NOTIMPL;
}


