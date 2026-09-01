

#ifndef  __QYDROPTARGET_H__
#define  __QYDROPTARGET_H__  //  {

#include  "AFXOLE.h"

//Drag & Drop User define Messages
#define DROPM_DRAGENTER				WM_USER + 1976
#define DROPM_DRAGOVER				WM_USER + 1977
#define DROPM_DROP					WM_USER + 1978
#define DROPM_DROPEX				WM_USER + 1979
#define DROPM_DRAGLEAVE				WM_USER + 1980


//
//Drop info class
//
class COleDropInfo : public CObject
{
public:
	COleDropInfo();
	COleDropInfo(COleDataObject* pDataObject,DWORD dwKeyState,
		DROPEFFECT dropEffect,DROPEFFECT dropEffectList,CPoint point );
	virtual ~COleDropInfo();

public:
	//COleDropTargetEx member functions params
	COleDataObject* m_pDataObject;
	DWORD m_dwKeyState;
	DROPEFFECT m_dropEffect;
	DROPEFFECT m_dropEffectList;
	CPoint m_point;

	DECLARE_DYNAMIC( COleDropInfo );
};




//
class  CDropTarget  :  public  COleDropTarget
{
public:
        CDropTarget(  );
		virtual ~CDropTarget(  );

		//

		
		
		//
		virtual DROPEFFECT OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject,	DWORD dwKeyState, CPoint point);
		virtual DROPEFFECT OnDragOver(CWnd* pWnd, COleDataObject* pDataObject,	DWORD dwKeyState, CPoint point);
		virtual BOOL OnDrop(CWnd* pWnd, COleDataObject* pDataObject,	DROPEFFECT dropEffect, CPoint point);
		virtual DROPEFFECT OnDropEx(CWnd* pWnd, COleDataObject* pDataObject,	DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point);
		virtual void OnDragLeave(CWnd* pWnd);
		virtual DROPEFFECT OnDragScroll(CWnd* pWnd, DWORD dwKeyState,CPoint point);
		

#if  0
		// Interface Maps
public:
	BEGIN_INTERFACE_PART(DropTarget, IDropTarget)
		INIT_INTERFACE_PART(COleDropTarget, DropTarget)
		STDMETHOD(DragEnter)(LPDATAOBJECT, DWORD, POINTL, LPDWORD);
		STDMETHOD(DragOver)(DWORD, POINTL, LPDWORD);
		STDMETHOD(DragLeave)();
		STDMETHOD(Drop)(LPDATAOBJECT, DWORD, POINTL pt, LPDWORD);
	END_INTERFACE_PART(DropTarget)

	DECLARE_INTERFACE_MAP()
#endif

	
 };




#endif  //  }

