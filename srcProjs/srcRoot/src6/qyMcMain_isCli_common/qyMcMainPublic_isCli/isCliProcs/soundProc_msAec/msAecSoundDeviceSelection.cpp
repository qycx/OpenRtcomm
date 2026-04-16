
#include	"stdafx.h"
#include	<Windows.h>
#include	<ShlObj.h>
#include	<MMSystem.h>
#include	<stdio.h>
#include	<tchar.h>

#include	"msAecCommon.h"

#include	"msAecSoundDeviceSelection.h"

#define	mmFAILED(  mm  )	(  (  mm  )  !=  MMSYSERR_NOERROR  )

BOOL  stringMatch(  LPCTSTR  a,  LPCTSTR  b  )
{
	if  (  !a  ||  !b  )  return  FALSE;
	while  (  *a  &&  *b  )
		if  (  *a  ++  !=  *b  ++  )  return  FALSE;
	return  (  !*a  &&  !*b  );
}

BOOL  stringMatchIn(  LPCTSTR  a,  LPCTSTR  b  )
{
	if  (  !a  ||  !b  )  return  FALSE;
	while  (  *a  &&  *b  )  
		if  (  *a  ++  !=  *b  ++  )  return  FALSE;
	return  (  !*b  );
}


HRESULT	GetWaveDeviceIDFromName(  LPCTSTR  lpszDesc,  DWORD  *  waveID  )
{
	UINT		totalDevices  =  mixerGetNumDevs(  );
	UINT		currentDevice;
	MIXERCAPS	mmCaps;
	MMRESULT	mmResult;

	for  (  currentDevice  =  0;  currentDevice  <  totalDevices;  currentDevice  ++  )  {
		mmResult  =  mixerGetDevCaps(  currentDevice,  &mmCaps,  sizeof(  mmCaps  )  );
		if  (  mmFAILED(  mmResult  )  )  {
			DPRINTF(  (  _T(  "mixerGetDevCaps failed"  )  )  );
		}
		else  if  (  stringMatchIn(  lpszDesc,  mmCaps.szPname  )  )  {
			*waveID  =  currentDevice;
			return  S_OK;
		}
		continue;
	}
	//
	*waveID  =  -1;
	return  ERROR_INVALID_DATA;
}
