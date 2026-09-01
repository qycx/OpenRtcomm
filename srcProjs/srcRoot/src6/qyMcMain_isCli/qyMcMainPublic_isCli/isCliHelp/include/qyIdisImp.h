
#ifndef  __QYIDISIMP_H__
#define  __QYIDISIMP_H__	//  {

class CImpIDispatch : public IDispatch
{
protected:
	ULONG		m_cRef;

public:

	CImpIDispatch(  void  );
	~CImpIDispatch(  void  );

	STDMETHOD(QueryInterface)(REFIID iid, LPVOID* ppvObj);
	STDMETHOD_(ULONG, AddRef)();
	STDMETHOD_(ULONG, Release)();
	
	STDMETHOD(GetTypeInfoCount)(UINT *pctinfo);
	STDMETHOD(GetTypeInfo)(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo);
	STDMETHOD(GetIDsOfNames)(REFIID riid, OLECHAR **rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId);
	STDMETHOD(Invoke)(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags,
		DISPPARAMS *pdispparams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr);
};


#endif  //  }

