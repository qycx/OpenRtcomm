
#ifndef  __QYCUSTSITE_H__
#define  __QYCUSTSITE_H__	//  {


#include	<afxocc.h>		//  2007/06/02


class CCustomControlSite : public COleControlSite
{
public:
	CCustomControlSite(COleControlContainer* pParentWnd);
	~CCustomControlSite();

	//
	virtual DWORD GetStyle() const;

protected:

	BEGIN_INTERFACE_PART(DocHostUIHandler, IDocHostUIHandler)
		STDMETHOD(ShowContextMenu)(DWORD, LPPOINT, LPUNKNOWN, LPDISPATCH);
		STDMETHOD(GetHostInfo)(DOCHOSTUIINFO*);
		STDMETHOD(ShowUI)(DWORD, LPOLEINPLACEACTIVEOBJECT,
			LPOLECOMMANDTARGET, LPOLEINPLACEFRAME, LPOLEINPLACEUIWINDOW);
		STDMETHOD(HideUI)(void);
		STDMETHOD(UpdateUI)(void);
		STDMETHOD(EnableModeless)(BOOL);
		STDMETHOD(OnDocWindowActivate)(BOOL);
		STDMETHOD(OnFrameWindowActivate)(BOOL);
		STDMETHOD(ResizeBorder)(LPCRECT, LPOLEINPLACEUIWINDOW, BOOL);
		STDMETHOD(TranslateAccelerator)(LPMSG, const GUID*, DWORD);
		STDMETHOD(GetOptionKeyPath)(OLECHAR **, DWORD);
		STDMETHOD(GetDropTarget)(LPDROPTARGET, LPDROPTARGET*);
		STDMETHOD(GetExternal)(LPDISPATCH*);
		STDMETHOD(TranslateUrl)(DWORD, OLECHAR*, OLECHAR **);
		STDMETHOD(FilterDataObject)(LPDATAOBJECT , LPDATAOBJECT*);
	END_INTERFACE_PART(DocHostUIHandler)

	DECLARE_INTERFACE_MAP()
};

 class  CCustomOccManager : public COccManager
{
 public:
	 CCustomOccManager(  ){}
	 COleControlSite * CreateSite(  COleControlContainer * pCtrlCont  )
	 {
		 CCustomControlSite * pSite  = new CCustomControlSite(  pCtrlCont  );
		 return  pSite;

	 }


	 COleControlContainer* CreateContainer(CWnd* pWnd)
	 {
		 return  COccManager::CreateContainer(  pWnd  );
	 }


};


#endif  //  }

////////////////////////////////////////////////////////////////


