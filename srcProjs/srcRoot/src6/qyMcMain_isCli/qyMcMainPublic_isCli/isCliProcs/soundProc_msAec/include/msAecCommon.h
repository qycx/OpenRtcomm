
#ifndef  __AECCOMMON_H__
#define  __AECCOMMON_H__	//  {


#ifdef  _DEBUG
	#define  DPRINTF(x)		{  _tprintf  x;  }
#else
	#define	DPRINTF(x)
#endif

//
BOOL  stringMatch(  LPCTSTR  a,  LPCTSTR  b  );
BOOL  stringMatchIn(  LPCTSTR  a,  LPCTSTR  b  );


#if  0
void  setDefaultSoundPlayer(  TCHAR  *  deviceName  );
void  setDefaultSoundRecorder(  TCHAR  *  deviceName  );
#endif

#if  0
TCHAR  *  getDefaultSoundPlayer(  );
TCHAR  *  getDefaultSoundRecorder(  );
#endif

#if  0

int  getNumberOfSoundPlayerDevices(  );
int  getNumberOfSoundRecorderDevices(  );
#endif



int  dx_snd_StopPlaying(  );
int  dx_snd_StopRecording(  );

#if  0
//
BOOL  dx_soundInit(  );
BOOL  dx_soundShutdown(  );
#endif

 BOOL  bSupported_aec(  );


#endif  //  }


