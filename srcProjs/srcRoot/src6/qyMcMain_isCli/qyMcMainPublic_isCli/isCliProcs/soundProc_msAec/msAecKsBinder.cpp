
#include	"stdafx.h"
#include <comdef.h>
#include  "msAecKsBinder.h"
#include  "strsafe.h"
#include  "functiondiscoverykeys.h"

#ifndef  IF_FAILED_JUMP
#define  IF_FAILED_JUMP(hr,label)  if(FAILED(hr)) goto label;
#endif

#ifndef  IF_FAILED_RETURN
#define  IF_FAILED_RETURN(hr)  if(FAILED(hr)) 	return  hr;
#endif

HRESULT	EndpointIsMicArray(  IMMDevice  *  pEndpoint,  BOOL & isMicphoneArray  )
{
	if  (  pEndpoint  ==  NULL  )  return  E_POINTER;

	GUID  subType =  {0};

	HRESULT  hr =  GetJackSubtypeForEndpoint(  pEndpoint,  &subType  );

	isMicphoneArray  =  ( subType == KSNODETYPE_MICROPHONE_ARRAY )  ?true:false;

	return  hr;

}

HRESULT	GetJackSubtypeForEndpoint(  IMMDevice  *  pEndpoint,  GUID  * pgSubType  )
{
	HRESULT  hr  =  S_OK;

	if  (  pEndpoint  ==  NULL  )  return  E_POINTER;

	IDeviceTopologyPtr  spEndpointTopology;
	IConnectorPtr  spPlug;
	IConnectorPtr  spJack;
	IPartPtr  spJackAsPart;

	//
	hr  =  pEndpoint->Activate(__uuidof(IDeviceTopology), CLSCTX_INPROC_SERVER,  NULL,  (void**)&spEndpointTopology  );
	IF_FAILED_JUMP( hr, Error);

	hr  =  spEndpointTopology->GetConnector(0,&spPlug);
	IF_FAILED_JUMP( hr, Error);

	hr  =  spPlug->GetConnectedTo(&spJack);
	IF_FAILED_JUMP( hr, Error);

	spJackAsPart  =  spJack;

	hr  =  spJackAsPart->GetSubType(pgSubType);
Error:
	return  hr;

}