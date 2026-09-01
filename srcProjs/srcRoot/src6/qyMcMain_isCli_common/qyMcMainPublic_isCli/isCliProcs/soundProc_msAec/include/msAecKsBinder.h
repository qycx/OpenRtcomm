#ifndef  __AEC_KSBINDER_H__
#define  __AEC_KSBINDER_H__

#include <comip.h>
#include <audioclient.h>
#include <MMDeviceApi.h>
#include <AudioEngineEndPoint.h>
#include <DeviceTopology.h>
#include <EndpointVolume.h>

typedef _com_ptr_t<_com_IIID<IPart, &__uuidof(IPart)> > IPartPtr;
typedef _com_ptr_t<_com_IIID<IConnector, &__uuidof(IConnector)> > IConnectorPtr;
typedef _com_ptr_t<_com_IIID<IDeviceTopology, &__uuidof(IDeviceTopology)> > IDeviceTopologyPtr;

HRESULT	EndpointIsMicArray(  IMMDevice  *  pEndpoint,  BOOL & isMicphoneArray  );
HRESULT	GetJackSubtypeForEndpoint(  IMMDevice  *  pEndpoint,  GUID  * pgSubType  );

#endif
