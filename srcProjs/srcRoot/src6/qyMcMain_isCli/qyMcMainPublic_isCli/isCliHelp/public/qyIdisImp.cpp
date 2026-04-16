

#include	"stdafx.h"
#include	"qyIdisImp.h"

const	WCHAR  pszExtend[10]  =  L"xxyyzz";
#define	DISPID_Extend			12345

CImpIDispatch::CImpIDispatch(  void)
{
	m_cRef  =  0;
}

CImpIDispatch::~CImpIDispatch(  void)
{
#ifndef  __WINCE__
	ASSERT(  m_cRef  ==  0  );
#endif
}



STDMETHODIMP CImpIDispatch::QueryInterface(REFIID iid, LPVOID* ppvObj)
{
	if (!ppvObj)
		return E_POINTER;

	*ppvObj = NULL;

	if (IsEqualIID(iid, __uuidof(IUnknown)) || 
		IsEqualIID(iid, __uuidof(IDispatch)))
	{
		*ppvObj = this;
	}
	if  (  NULL  !=  *ppvObj  )  {
		(  (  LPUNKNOWN  )*ppvObj  )->AddRef(  );
		return  NOERROR;
	}

	return E_NOINTERFACE;
}


STDMETHODIMP_(ULONG) CImpIDispatch::AddRef()
{
	return ++m_cRef;
}

STDMETHODIMP_(ULONG) CImpIDispatch::Release()
{
	return --m_cRef;
}


STDMETHODIMP CImpIDispatch::GetTypeInfoCount(UINT *pctinfo)
{
	return  E_NOTIMPL;
}

STDMETHODIMP CImpIDispatch::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo)
{
	return  E_NOTIMPL;
}

STDMETHODIMP CImpIDispatch::GetIDsOfNames(REFIID riid, OLECHAR **rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
{
	HRESULT	hr;
	UINT	i;

	hr  =  NOERROR;

	for  (  i  =  0;  i  <  cNames;  i  ++  )  {
		 if  (  2  ==  CompareString(  lcid,  NORM_IGNOREWIDTH,  pszExtend,  3,  rgszNames[i],  3  )  )  {
			 rgDispId[i]  =  DISPID_Extend;
			}
		 else  {
			   hr  =  ResultFromScode(  DISP_E_UNKNOWNNAME  );
			   rgDispId[i]  =  DISPID_UNKNOWN;
		 }
	}
	return  hr;
}

STDMETHODIMP CImpIDispatch::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags,
	DISPPARAMS *pdispparams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
	//  for  this sample we only support a property Get on DISPID_Extend
	//  returning a BSTR with "Wibble" as the value 
	if  (  dispIdMember  ==  DISPID_Extend  )  {
		if  (  wFlags  &  DISPATCH_PROPERTYGET  )  {
			if  (  pVarResult  !=  NULL  )  {
				WCHAR  buf[10]  =  L"Wibble";
				BSTR  bstrRet  =  SysAllocString(  buf  );
				VariantInit(  pVarResult  );
				V_VT(  pVarResult  )  =  VT_BSTR;
				V_BSTR(  pVarResult  );  

				//  return  S_OK;	//  2008/11/14¼Ó
			}
		}
	}

	OutputDebugString(  _T(  "CImpIDispatch::Invoke(  ): failed. DISP_E_MEMBERNOTFOUND\n"  )  );

	return DISP_E_MEMBERNOTFOUND;
}


