#ifndef  __SQ_WIN32_SOUND_DEVICE_SELECTION_H__
#define  __SQ_WIN32_SOUND_DEVICE_SELECTION_H__

#include <dsound.h>
#include <dsconf.h>

#if  0
typedef  struct		{
					TCHAR  *	name;
					int			mmID;
					LPGUID		guid;
}		 DeviceInfo;

#define  DEVICE_MAX  24  //  how many devices can we handle?

typedef  struct		{
					UINT							deviceCount;
					BOOL							changed;
					UINT							enumerationCounter;
					DIRECTSOUNDDEVICE_DATAFLOW		dataflow;		//  recording or playback?
					DeviceInfo						defaultDevice;
					DeviceInfo						devices[DEVICE_MAX];
					LPGUID							guid;
}		 DeviceInfoList;


void  setDeviceGUID(  DeviceInfo  *  device,  LPGUID  lpGUID  );
#endif


HRESULT	GetWaveDeviceIDFromName(  LPCTSTR  lpszDesc,  DWORD  *  waveID  );

#if  0
extern  DeviceInfoList  playerDevices;
extern  DeviceInfoList  recorderDevices;

extern	HANDLE  hPlayEvent;
extern	HANDLE  hRecEvent;
#endif

#endif