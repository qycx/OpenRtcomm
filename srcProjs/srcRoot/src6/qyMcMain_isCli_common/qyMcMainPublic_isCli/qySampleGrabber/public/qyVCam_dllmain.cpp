
#include	"stdafx.h"


#include	<streams.h>
#include	<olectl.h>
//  #include	<initguid.h>
#include	<dllsetup.h>
#include	"qySampleGrabberPublic.h"
#include	"qyVCam.h"

#if  0

#define  CreateComObject(  clsid,  iid,  var  )   CoCreateInstance(  clsid,  NULL,  CLSCTX_INPROC_SERVER,  iid,  (  void  **  )&var  );

STDAPI  AMovieSetupRegisterServer(  CLSID  clsServer,  LPCWSTR  szDescription,  LPCWSTR  szFileName,  LPCWSTR  szThreadingModel  =  L"Both",  LPCWSTR  szServerType  =  L"InprocServer32"  );
STDAPI  AMovieSetupUnregisterServer(  CLSID  clsServer  );

DEFINE_GUID(  CLSID_VirtualCam,  
			0x8e14549a,  0xdb61,  0x4309,  0xaf,  0xa1,  0x35,  0x78,  0xe9,  0x27,  0xe9,  0x33  );

const  AMOVIESETUP_MEDIATYPE  AMSMediaTypesVCam  =  
{
	&MEDIATYPE_Video,
	&MEDIASUBTYPE_NULL
};

const  AMOVIESETUP_PIN  AMSPinVCam  =
{
	L"Output",
	FALSE,
	TRUE,
	FALSE,
	FALSE,
	&CLSID_NULL,
	NULL,
	1,
	&AMSMediaTypesVCam
};

const  AMOVIESETUP_FILTER  AMSFilterVCam  =
{
	&CLSID_VirtualCam,
	L"Virtual  Cam",
	MERIT_DO_NOT_USE,
	1,
	&AMSPinVCam
};

CFactoryTemplate  g_Templates[]  =
{
	{
		L"Virtual Cam",
			&CLSID_VirtualCam,
			QVCam::CreateInstance,
			NULL,
			&AMSFilterVCam
	},
};

int  g_cTemplates   =  sizeof(  g_Templates  )  /sizeof(  g_Templates[0]  );

STDAPI  RegisterFilters(  BOOL  bRegister  )
{
	HRESULT  hr =  NOERROR;
	WCHAR  achFileName[  MAX_PATH  ];
	char  achTemp[  MAX_PATH  ];
	ASSERT(  g_hInst  !=  0  );

	if  (  0  ==  GetModuleFileNameA(  g_hInst,  achTemp,  sizeof(  achTemp  )  )  )
		return  AmHresultFromWin32(  GetLastError(  )  );

	MultiByteToWideChar(  CP_ACP,  0L,  achTemp,  lstrlenA(  achTemp  )  +  1,  achFileName,  NUMELMS(  achFileName  )  );

	hr  =  CoInitialize(  0  );
	if  (  bRegister  )
	{
		hr =  AMovieSetupRegisterServer(  CLSID_VirtualCam,  L"Virtual Cam",  achFileName,  L"Both",  L"InprocServer32"  );
	}

	if  (  SUCCEEDED(  hr  )  )
	{
		IFilterMapper2  *  fm  =  0;
		hr  =  CreateComObject(  CLSID_FilterMapper2,  IID_IFilterMapper2,  fm  );
		if  (  SUCCEEDED(  hr  )  )
		{
			if  (  bRegister  )
			{
				IMoniker  *  pMoniker  =  0;
				REGFILTER2  rf2;
				rf2.dwVersion  =  1;
				rf2.dwMerit  =  MERIT_DO_NOT_USE;
				rf2.cPins  =  1;
				rf2.rgPins  =  &AMSPinVCam;
				hr  =  fm->RegisterFilter(  CLSID_VirtualCam,  L"Virtual Cam",  &pMoniker,  &CLSID_VideoInputDeviceCategory,  NULL,  &rf2  );
			}
			else  
			{
				hr  =  fm->UnregisterFilter(  &CLSID_VideoInputDeviceCategory,  0,  CLSID_VirtualCam  );
			}
		}
		if  (  fm  )
			fm->Release(  );
	}
	if  (  SUCCEEDED(  hr  )  && !bRegister  )
		hr  =  AMovieSetupUnregisterServer(  CLSID_VirtualCam  );

	CoFreeUnusedLibraries(  );
	CoUninitialize(  );
	return  hr;
}

STDAPI  DllRegisterServer(  )
{
	return RegisterFilters(  TRUE  );
}

STDAPI  DllUnregisterServer(  )
{
	return RegisterFilters(  FALSE  );
}

#endif

