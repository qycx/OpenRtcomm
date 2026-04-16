
#include	"stdafx.h"
#include	<Windows.h>
#include	<ShlObj.h>
#include	<MMSystem.h>
#include	<stdio.h>
#include	<tchar.h>
#include	<WinSock2.h>

#include	"qyCommon.h"

#include	"msAecCommon.h"

#include	"msAecSoundDeviceSelection.h"

static  char  GUIDString[128];
char  *  printGUID(  LPGUID  p  )
{
	if  (  !p  )  return  "";
	sprintf(  GUIDString,  "{%1x, %x, %x, %x %x %x %x %x %x %x %x} @%1x",
		p->Data1,  p->Data2,  p->Data3,  p->Data4[0],  p->Data4[1],  p->Data4[2],  p->Data4[3],  
		p->Data4[4],  p->Data4[5],  p->Data4[6],  p->Data4[7],  p  );
	return  GUIDString;
}








 int  dx_snd_StopPlaying(  )
 {
	 OutputDebugString(  _T(  "Not finished: dx_snd_StopPlaying\n"  )  );
	 return  0;
 }

 int  dx_snd_StopRecording(  )
 {
	 OutputDebugString(  _T(  "Not finished: dx_snd_StopRecording\n"  )  );
	 return  0;
 }
