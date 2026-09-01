
#include	"stdafx.h"
#include	"qyDropTarget.h"

void  DropData(  HWND  hwnd,  IDataObject  *  pDataObject  );

//
//COleDropInfo Construction/Destruction
IMPLEMENT_DYNAMIC( COleDropInfo, CObject );

COleDropInfo::COleDropInfo()
{
	m_pDataObject = NULL;
	m_dwKeyState = 0;
	m_dropEffect = (DROPEFFECT)-1;
	m_dropEffectList = DROPEFFECT_NONE;
}

COleDropInfo::COleDropInfo(COleDataObject* pDataObject,DWORD dwKeyState,
				DROPEFFECT dropEffect,DROPEFFECT dropEffectList,CPoint point )
{
	m_pDataObject = pDataObject;
	m_dwKeyState = dwKeyState;
	m_dropEffect = dropEffect;
	m_dropEffectList = dropEffectList;
	m_point = point;
}

COleDropInfo::~COleDropInfo()
{
	m_pDataObject = NULL;
}













//
#if  0
BEGIN_INTERFACE_MAP(CDropTarget, COleDropTarget)
	INTERFACE_PART(CDropTarget, IID_IDropTarget, DropTarget)
END_INTERFACE_MAP()
#endif


CDropTarget::CDropTarget(  )
{
}

CDropTarget::~CDropTarget(  )
{
	OutputDebugString(  _T(  "CDropTarget::~CDropTarget(  )\n"  )  );
}


//




#if  0
void  PositionCursor(  HWND  hwndEdit,  POINTL  pt  )
{
	DWORD	curpos;

	ScreenToClient(  hwndEdit,  (  POINT  *  )&pt  );
	curpos  =  SendMessage(  hwndEdit,  EM_CHARFROMPOS,  0,  MAKELPARAM(  pt.x,  pt.y  )  );

	SendMessage(  hwndEdit,  EM_SETSEL,  LOWORD(  curpos  ),  LOWORD(  curpos  )  );

}
#endif

//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////


/*
		//  virtual DROPEFFECT OnDropEx(CWnd* pWnd, COleDataObject* pDataObject,	DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point);
		*/


DROPEFFECT CDropTarget::OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject,	DWORD dwKeyState, CPoint point)
{
#if  0
	pWnd->ClientToScreen(  &point  );

	return  DROPEFFECT_NONE;
#endif
	//
		ASSERT_VALID(this);
	ASSERT(::IsWindow(pWnd->m_hWnd));

	if (pWnd->IsKindOf(RUNTIME_CLASS(CView)))//if CView,Call base class
		return COleDropTarget::OnDragEnter(pWnd,pDataObject, dwKeyState, point);

	COleDropInfo DropInfo( pDataObject, dwKeyState, 0, 0, point );
	
	return ::SendMessage( pWnd->GetSafeHwnd(), DROPM_DRAGENTER, (WPARAM)&DropInfo, 0 );


}

DROPEFFECT CDropTarget::OnDropEx(CWnd* pWnd, COleDataObject* pDataObject,	DROPEFFECT dropEffect, DROPEFFECT dropEffectList, CPoint point)
{
	//return  DROPEFFECT_NONE;

		ASSERT_VALID(this);
	ASSERT(::IsWindow(pWnd->m_hWnd));

	if (pWnd->IsKindOf(RUNTIME_CLASS(CView)))//if CView,Call base class
		return COleDropTarget::OnDropEx( pWnd, pDataObject, dropEffect, dropEffectList, point) ;

	COleDropInfo DropInfo( pDataObject, 0, dropEffect, dropEffectList, point );

	return ::SendMessage( pWnd->GetSafeHwnd(), DROPM_DROPEX, (WPARAM)&DropInfo, 0 );



}
		


void CDropTarget::OnDragLeave(CWnd* pWnd)
{
	//COleDropTarget::OnDragLeave(  pWnd  );

		ASSERT_VALID(this);
	ASSERT(::IsWindow(pWnd->m_hWnd));

	if (pWnd->IsKindOf(RUNTIME_CLASS(CView)))//if CView,Call base class
	{
		COleDropTarget::OnDragLeave( pWnd );
		return;
	}

	::SendMessage( pWnd->GetSafeHwnd(), DROPM_DRAGLEAVE, 0, 0 );

	return;

}


DROPEFFECT CDropTarget::OnDragOver(CWnd* pWnd, COleDataObject* pDataObject,	DWORD dwKeyState, CPoint point)
{

	//return  DROPEFFECT_NONE;
		ASSERT_VALID(this);
	ASSERT(::IsWindow(pWnd->m_hWnd));

	if (pWnd->IsKindOf(RUNTIME_CLASS(CView)))//if CView,Call base class
		return COleDropTarget::OnDragOver(pWnd,pDataObject, dwKeyState, point);
	
	COleDropInfo DropInfo( pDataObject, dwKeyState, 0, 0, point );

	return ::SendMessage( pWnd->GetSafeHwnd(), DROPM_DRAGOVER, (WPARAM)&DropInfo, 0 );


}





 BOOL CDropTarget::OnDrop(CWnd* pWnd, COleDataObject* pDataObject,	DROPEFFECT dropEffect, CPoint point)
{

	//return  TRUE;
		ASSERT_VALID(this);
	ASSERT(::IsWindow(pWnd->m_hWnd));

	if (pWnd->IsKindOf(RUNTIME_CLASS(CView)))//if CView,Call base class
		return COleDropTarget::OnDrop(pWnd, pDataObject,dropEffect,point);

	COleDropInfo DropInfo( pDataObject, 0, dropEffect, 0, point );

	return ::SendMessage( pWnd->GetSafeHwnd(), DROPM_DROP, (WPARAM)&DropInfo, 0 );


}

 DROPEFFECT CDropTarget::OnDragScroll(CWnd* pWnd, DWORD dwKeyState,CPoint point)
 {
	 return  DROPEFFECT_NONE;
 }



#if  0
 STDMETHODIMP_(ULONG) CDropTarget::XDropTarget::AddRef()
{
	METHOD_PROLOGUE_EX_(CDropTarget, DropTarget)
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CDropTarget::XDropTarget::Release()
{
	METHOD_PROLOGUE_EX_(CDropTarget, DropTarget)
	return pThis->ExternalRelease();
}

STDMETHODIMP CDropTarget::XDropTarget::QueryInterface(
		  REFIID iid, LPVOID far* ppvObj)     
{
	METHOD_PROLOGUE_EX_(CDropTarget, DropTarget)
	return pThis->ExternalQueryInterface(&iid, ppvObj);
}



STDMETHODIMP CDropTarget::XDropTarget::DragEnter(THIS_ LPDATAOBJECT lpDataObject,
	DWORD dwKeyState, POINTL pt, LPDWORD pdwEffect)
{
	METHOD_PROLOGUE_EX_(CDropTarget, DropTarget)


	return  E_NOTIMPL;
}

STDMETHODIMP CDropTarget::XDropTarget::DragOver(THIS_ DWORD dwKeyState,
	POINTL pt, LPDWORD pdwEffect)
{
	METHOD_PROLOGUE_EX(CDropTarget, DropTarget)
	ASSERT_VALID(pThis);

	return  E_NOTIMPL;
}


 STDMETHODIMP CDropTarget::XDropTarget::DragLeave(THIS)
{
	METHOD_PROLOGUE_EX(CDropTarget, DropTarget)
	ASSERT_VALID(pThis);

	return  E_NOTIMPL;
 }

 STDMETHODIMP CDropTarget::XDropTarget::Drop(THIS_ LPDATAOBJECT lpDataObject,
	DWORD dwKeyState, POINTL pt, LPDWORD pdwEffect)
{
	METHOD_PROLOGUE_EX(CDropTarget, DropTarget)
	ASSERT_VALID(pThis);

	return  E_NOTIMPL;
 }
#endif


 

/*
void  DropData(  HWND  hwnd,  IDataObject  *  pDataObject  )
{
	FORMATETC  fmtetc  =  {  CF_TEXT,  0,  DVASPECT_CONTENT,  -1,  TYMED_HGLOBAL  };
	STGMEDIUM  stgmed;

	if  (  pDataObject->QueryGetData(  &fmtetc  )  ==  S_OK  )
	{
		if  (  pDataObject->GetData(  &fmtetc,  &stgmed  )  ==  S_OK  )
		{
			PVOID  data  =  GlobalLock(  stgmed.hGlobal  );
			SetWindowText(  hwnd,  (  TCHAR  *  )data  );
			GlobalUnlock(  stgmed.hGlobal  );

			ReleaseStgMedium(  &stgmed  );
		}
	}

}
*/

