
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyMcMainRealTimeMediaProc.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"
#include	"qyPlaySound_wave.h"
//  #include	"QyRecordSound_wave.h"
#include	"module_qisCamCap.h"

#include	<MMSystem.h>
#include	<InitGuid.h>
#include	<mmdeviceapi.h>
#include	<FunctionDiscoveryKeys_devpkey.h>
#include	<devicetopology.h>
#include	<dsound.h>

#include	"mmDeviceProc.h"

#include	"qyCusResTemp.h"


//-----------------------------------------------------------
// Get the IKsJackDescription interface that describes the
// audio jack or jacks that the endpoint device plugs into.
//-----------------------------------------------------------
#define EXIT_ON_ERROR(hres)  \
              if (FAILED(hres)) { goto Exit; }
#define SAFE_RELEASE(punk)  \
              if ((punk) != NULL)  \
                { (punk)->Release(); (punk) = NULL; }

HRESULT GetJackInfo(IMMDevice *pDevice,
                    IKsJackDescription **ppJackDesc)
{
    HRESULT hr = S_OK;
    IDeviceTopology *pDeviceTopology = NULL;
    IConnector *pConnFrom = NULL;
    IConnector *pConnTo = NULL;
    IPart *pPart = NULL;
    IKsJackDescription *pJackDesc = NULL;

    if (NULL != ppJackDesc)
    {
        *ppJackDesc = NULL;
    }
    if (NULL == pDevice || NULL == ppJackDesc)
    {
        return E_POINTER;
    }

    // Get the endpoint device's IDeviceTopology interface.
    hr = pDevice->Activate(__uuidof(IDeviceTopology), CLSCTX_ALL,
                           NULL, (void**)&pDeviceTopology);
    EXIT_ON_ERROR(hr)

    // The device topology for an endpoint device always
    // contains just one connector (connector number 0).
    hr = pDeviceTopology->GetConnector(0, &pConnFrom);
    EXIT_ON_ERROR(hr)

    // Step across the connection to the jack on the adapter.
    hr = pConnFrom->GetConnectedTo(&pConnTo);
    if (HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND) == hr)
    {
        // The adapter device is not currently active.
        hr = E_NOINTERFACE;
    }
    EXIT_ON_ERROR(hr)

    // Get the connector's IPart interface.
    hr = pConnTo->QueryInterface(__uuidof(IPart), (void**)&pPart);
    EXIT_ON_ERROR(hr)

    // Activate the connector's IKsJackDescription interface.
    hr = pPart->Activate(CLSCTX_INPROC_SERVER,
                         __uuidof(IKsJackDescription), (void**)&pJackDesc);
    EXIT_ON_ERROR(hr)

    *ppJackDesc = pJackDesc;

Exit:
    SAFE_RELEASE(pDeviceTopology)
    SAFE_RELEASE(pConnFrom)
    SAFE_RELEASE(pConnTo)
    SAFE_RELEASE(pPart)
    return hr;
}



QY_DMITEM  CONST_jack_GeoLocationTable[]  =
{
	{	eGeoLocRear,						(  TCHAR  *  )CONST_resId_eGeoLocRear,	},
	{	eGeoLocFront,						(  TCHAR  *  )CONST_resId_eGeoLocFront,	},
	{	eGeoLocLeft,						(  TCHAR  *  )CONST_resId_eGeoLocLeft,	},
	{	eGeoLocRight,						(  TCHAR  *  )CONST_resId_eGeoLocRight,	},
	{	eGeoLocTop,							(  TCHAR  *  )CONST_resId_eGeoLocTop,	},
	{	eGeoLocBottom,						(  TCHAR  *  )CONST_resId_eGeoLocBottom,	},
	{	eGeoLocRearPanel,					(  TCHAR  *  )CONST_resId_eGeoLocRearPanel,	},
	{	eGeoLocRiser,						(  TCHAR  *  )CONST_resId_eGeoLocRiser,	},
	{	eGeoLocInsideMobileLid,				(  TCHAR  *  )CONST_resId_eGeoLocInsideMobileLid,	},
	{	eGeoLocDrivebay,					(  TCHAR  *  )CONST_resId_eGeoLocDrivebay,	},
	{	eGeoLocHDMI,						(  TCHAR  *  )CONST_resId_eGeoLocHDMI,	},
	{	eGeoLocOutsideMobileLid,			(  TCHAR  *  )CONST_resId_eGeoLocOutsideMobileLid,	},
	{	eGeoLocATAPI,						(  TCHAR  *  )CONST_resId_eGeoLocATAPI,	},
	{	-1,	},
};



QY_DMITEM  CONST_jack_ConnectionTypeTable[]  =
{
	{	eConnTypeUnknown,					(  TCHAR  *  )CONST_resId_eConnTypeUnknown,	},
	{	eConnType3Point5mm,					(  TCHAR  *  )CONST_resId_eConnType3Point5mm,	},	//  _T(  "1/8-inch jack"  ),	},
	{	eConnTypeQuarter,					(  TCHAR  *  )CONST_resId_eConnTypeQuarter,	},
	{	eConnTypeAtapiInternal,				(  TCHAR  *  )CONST_resId_eConnTypeAtapiInternal,	},
	{	eConnTypeRCA,						(  TCHAR  *  )CONST_resId_eConnTypeRCA,	},
	{	eConnTypeOptical,					(  TCHAR  *  )CONST_resId_eConnTypeOptical,	},
	{	eConnTypeOtherDigital,				(  TCHAR  *  )CONST_resId_eConnTypeOtherDigital,	},
	{	eConnTypeOtherAnalog,				(  TCHAR  *  )CONST_resId_eConnTypeOtherAnalog,	},
	{	eConnTypeMultichannelAnalogDIN,		(  TCHAR  *  )CONST_resId_eConnTypeMultichannelAnalogDIN,	},
	{	eConnTypeXlrProfessional,			(  TCHAR  *  )CONST_resId_eConnTypeXlrProfessional,	},
	{	eConnTypeRJ11Modem,					(  TCHAR  *  )CONST_resId_eConnTypeRJ11Modem,	},
	{	eConnTypeCombination,				(  TCHAR  *  )CONST_resId_eConnTypeCombination,	},
	{	-1,	},
};

 int  printJack(  int  ii,  KSJACK_DESCRIPTION  *pKsJack,  TCHAR  *  tDesc,  unsigned  int  cnt_tDesc  )
 {
	 QY_MC* pQyMc = nullptr;// QY_GET_GBUF();
	 if (!pQyMc)  return -1;
	 int		iResId_GeoLocation;
	 int		iResId_ConnectionType;

	 iResId_GeoLocation  =  (  int  )qyGetDesByType(  CONST_jack_GeoLocationTable,  pKsJack->GeoLocation  );
	 iResId_ConnectionType  =  (  int  )qyGetDesByType(  CONST_jack_ConnectionTypeTable,  pKsJack->ConnectionType  );

	 _sntprintf(  tDesc,  cnt_tDesc,  _T(  "%s %s %s"  ),  tDesc,  
		 getResStr(  0,  &pQyMc->cusRes,  iResId_GeoLocation  ),  
		 getResStr(  0,  &pQyMc->cusRes,  iResId_ConnectionType  )  );
		 
	 return  0;
 }


int  list_devices_a(  BOOL  b_eCapture,  OLD_audioDevices  *  pAudioDevices )
{
	int						iErr					=	-1;
	HRESULT					hr						=  S_OK;
	IMMDeviceEnumerator  *  pMMDeviceEnumerator		=  NULL;

#ifdef  __DEBUG__
		#if  0
			 traceLog((TCHAR*)  _T(  "TEST: not use list_devices_a(  )"  )  );
			 return  -1;
		#endif
#endif

	//
	memset(  pAudioDevices,  0,  sizeof(  pAudioDevices[0]  )  );

	//
	hr  =  CoCreateInstance(  __uuidof(  MMDeviceEnumerator  ),  NULL,  CLSCTX_ALL,  __uuidof(  IMMDeviceEnumerator  ),  (  void  **  )&pMMDeviceEnumerator  );

	if  (  SUCCEEDED(  hr  )  )  {

		IMMDeviceCollection	*	pMMDeviceCollection  =  NULL;
		EDataFlow  eFlow  =  b_eCapture  ?  eCapture  :  eRender;

		hr  =  pMMDeviceEnumerator->EnumAudioEndpoints(  eFlow,  DEVICE_STATE_ACTIVE,  &pMMDeviceCollection  );
		if  (  SUCCEEDED(  hr  )  )  {

			UINT  count  =  0;
			hr  =  pMMDeviceCollection->GetCount(  &count  );
			if  (  SUCCEEDED(  hr  )  )  {

				int  i;
				for  (  i  =  0;  i  <  count;  i  ++  )  {
					 IMMDevice  *  pMMDevice  =  NULL;

					 hr  =  pMMDeviceCollection->Item(  i,  &pMMDevice  );
					 if  (  FAILED(  hr  )  )  break;

					 TCHAR	tName[256]	=  _T(  ""  );
					 GUID	guid_dev  =  GUID_NULL;
					 TCHAR	tDesc[256]	=	_T(  ""  );

					 //
					 IPropertyStore  *  pPropertyStore  =  NULL;
					 hr  =  pMMDevice->OpenPropertyStore(  STGM_READ,  &pPropertyStore  );
					 if  (  SUCCEEDED(  hr  )  )  {

						 //
						 PROPVARIANT  pv;  
						 PropVariantInit(  &pv  );
						 hr  =  pPropertyStore->GetValue(  PKEY_Device_FriendlyName,  &pv  );
						 if  (  SUCCEEDED(  hr  )  )  {
							 if  (  pv.vt  ==  VT_LPWSTR  )  {
								 safeTcsnCpy(  pv.pwszVal,  tName,  mycountof(  tName  )  );
							 }
						 }
						 PropVariantClear(  &pv  );

						 //
						 PropVariantInit(  &pv  );
						 hr  =  pPropertyStore->GetValue(  PKEY_AudioEndpoint_GUID,  &pv  );
						 if  (  SUCCEEDED(  hr  )  )  {
							 if  (  pv.vt  ==  VT_LPWSTR  )  {
								 hr  =  CLSIDFromString(  pv.pwszVal,  &guid_dev  );
							 }
						 }
						 PropVariantClear(  &pv  );

						 //
						 pPropertyStore->Release(  );
					 }					 
					 
					 //
					 IKsJackDescription  *  pJackDesc  =  NULL;
					 hr  =  GetJackInfo(  pMMDevice,  &pJackDesc  );
					 if  (  SUCCEEDED(  hr  )  )  {
						 
						 UINT  nJacks  =  1;
						 hr  =  pJackDesc->GetJackCount(  &nJacks  );
						 if  (  SUCCEEDED(  hr  )  )  {
							 						 
							 KSJACK_DESCRIPTION  ksjack;
							 for  (  int  ii  =  0;  ii  <  nJacks;  ii  ++  )  {
							 
								 hr  =  pJackDesc->GetJackDescription(  ii,  &ksjack  );
								 if  (  SUCCEEDED(  hr  )  )  {
									 printJack(  ii,  &ksjack,  tDesc,  mycountof(  tDesc  )  );

								 }						 
							 
							 }
						 }

						 //
						 pJackDesc->Release(  );
					 }

					 #ifdef  __DEBUG__
							 traceLog((TCHAR*)  _T(  "audioDevice: %d, %s, %s"  ),  i,  tName,  tDesc  );
					 #endif
					 //
					 if  (  pAudioDevices->iNumADevices  <  mycountof(  pAudioDevices->mems  )  )  {
						 _sntprintf(  pAudioDevices->mems[pAudioDevices->iNumADevices].names_audio,  mycountof(  pAudioDevices->mems[pAudioDevices->iNumADevices].names_audio  ),  _T(  "%s %s"  ),  tName,  tDesc  );
						 pAudioDevices->mems[pAudioDevices->iNumADevices].guid_audio  =  guid_dev;
						 pAudioDevices->iNumADevices  ++;

					 }


					 //
					 pMMDevice->Release(  );
				}

			}

			//
			pMMDeviceCollection->Release(  );
		}

		//
		pMMDeviceEnumerator->Release(  );
	}

	//  2014/07/31
	if  (  pAudioDevices->iNumADevices  )  {
		OLD_audioDevice  mm;
		memset(  &mm,  0,  sizeof(  mm  )  );
		if  (  !getDefaultADevice(  b_eCapture,  &mm  )  )  {
			pAudioDevices->default_guid_audio  =  mm.guid_audio;
		}
	}


	//
	iErr  =  0;

	return  iErr;
}







 //int  getDefaultPlaybackDevice(  OLD_audioDevice  *  pAudioDevice )
 int  getDefaultADevice(  BOOL  b_eCapture,  OLD_audioDevice  *  pAudioDevice )
{
	int						iErr					=	-1;
	HRESULT					hr						=  S_OK;
	IMMDeviceEnumerator  *  pMMDeviceEnumerator		=  NULL;
	BOOL					bGot					=	FALSE;

#ifdef  __DEBUG__
		#if  0
			 traceLog((TCHAR*)  _T(  "TEST: not use list_devices_a(  )"  )  );
			 return  -1;
		#endif
#endif

	//
	memset(  pAudioDevice,  0,  sizeof(  *pAudioDevice  )  );

	//
	hr  =  CoCreateInstance(  __uuidof(  MMDeviceEnumerator  ),  NULL,  CLSCTX_ALL,  __uuidof(  IMMDeviceEnumerator  ),  (  void  **  )&pMMDeviceEnumerator  );

	if  (  SUCCEEDED(  hr  )  )  {

		EDataFlow  eFlow  =  b_eCapture  ?  eCapture  :  eRender;
		ERole  eRole  =  eConsole;	//  eCommunications;	//  2014/08/31


		IMMDevice  *  pMMDevice  =  NULL;

		hr  =  pMMDeviceEnumerator->GetDefaultAudioEndpoint(  eFlow,  eRole,  &pMMDevice  );  
		if  (  SUCCEEDED(  hr  )  )  {

			bGot  =  TRUE;

			//				
			TCHAR	tName[256]	=  _T(  ""  );				
			GUID	guid_dev  =  GUID_NULL;
			TCHAR	tDesc[256]	=	_T(  ""  );
			
			//			
			IPropertyStore  *  pPropertyStore  =  NULL;				
			hr  =  pMMDevice->OpenPropertyStore(  STGM_READ,  &pPropertyStore  );
			if  (  SUCCEEDED(  hr  )  )  {

						 //
						 PROPVARIANT  pv;  
						 PropVariantInit(  &pv  );
						 hr  =  pPropertyStore->GetValue(  PKEY_Device_FriendlyName,  &pv  );
						 if  (  SUCCEEDED(  hr  )  )  {
							 if  (  pv.vt  ==  VT_LPWSTR  )  {
								 safeTcsnCpy(  pv.pwszVal,  tName,  mycountof(  tName  )  );
							 }
						 }
						 PropVariantClear(  &pv  );

						 //
						 PropVariantInit(  &pv  );
						 hr  =  pPropertyStore->GetValue(  PKEY_AudioEndpoint_GUID,  &pv  );
						 if  (  SUCCEEDED(  hr  )  )  {
							 if  (  pv.vt  ==  VT_LPWSTR  )  {
								 hr  =  CLSIDFromString(  pv.pwszVal,  &guid_dev  );
							 }
						 }
						 PropVariantClear(  &pv  );

						 //
						 pPropertyStore->Release(  );
					 
			}					 
						
			//			
			IKsJackDescription  *  pJackDesc  =  NULL;				
			hr  =  GetJackInfo(  pMMDevice,  &pJackDesc  );
			if  (  SUCCEEDED(  hr  )  )  {
						 
						 UINT  nJacks  =  1;
						 hr  =  pJackDesc->GetJackCount(  &nJacks  );
						 if  (  SUCCEEDED(  hr  )  )  {
							 						 
							 KSJACK_DESCRIPTION  ksjack;
							 for  (  int  ii  =  0;  ii  <  nJacks;  ii  ++  )  {
							 
								 hr  =  pJackDesc->GetJackDescription(  ii,  &ksjack  );
								 if  (  SUCCEEDED(  hr  )  )  {
									 printJack(  ii,  &ksjack,  tDesc,  mycountof(  tDesc  )  );

								 }						 
							 
							 }
						 }

						 //
						 pJackDesc->Release(  );
					 
			}

			#ifdef  __DEBUG__
					traceLog((TCHAR*)  _T(  "audioDevice: %d, %s, %s"  ),  0,  tName,  tDesc  );
			#endif
			
			//			
			_sntprintf(  pAudioDevice->names_audio,  mycountof(  pAudioDevice->names_audio  ),  _T(  "%s %s"  ),  tName,  tDesc  );									
			pAudioDevice->guid_audio  =  guid_dev;


			//			
			pMMDevice->Release(  );
				
		}
			
		//
		pMMDeviceEnumerator->Release(  );
	}

	iErr  =  0;

	return  bGot  ?  0  :  -1;
}
