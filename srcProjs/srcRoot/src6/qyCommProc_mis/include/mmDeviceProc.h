
#ifndef  __MMDEVICEPROC_H__
#define  __MMDEVICEPROC_H__	//  {

typedef  struct  __old_audioDevice_t		{
				 int						iMenuIds_audio;
				 TCHAR						names_audio[128  +  1];
				 GUID						guid_audio;				//  2011/10/23				 
}		 OLD_audioDevice;

	//  2012/01/04
typedef  struct  __old_audioDevices_t		{
				 OLD_audioDevice			mems[10];
				 //
				 int						iNumADevices;
				 //
				 GUID						default_guid_audio;				//  2011/10/23				 
				 //
				 int						iMenuId_selectedAudio;
	
}		 OLD_audioDevices;


//
typedef  struct  __old_videoDevice_t {
	int						iMenuIds_video;
	TCHAR					names_video[128 + 1];
	TCHAR					monikerDisplayName[256 + 1];
}		 OLD_videoDevice;

//  2012/01/04
typedef  struct  __old_videoDevices_t {
	OLD_videoDevice			mems[10];
	//
	int						iNumVDevices;
	//
	//GUID						default_guid_audio;				//  2011/10/23				 
	//
	//int						iMenuId_selectedAudio;

}		 OLD_videoDevices;








//  EDataFlow  iEFlow
int  list_devices_a(  BOOL  b_eCapture,  OLD_audioDevices  *  pAudioDevices );
int  getDefaultADevice(  BOOL  b_eCapture,  OLD_audioDevice  *  pAudioDevice );


//  int  getDefaultPlaybackDevice(  OLD_audioDevice  *  pAudioDevice );
#define		getDefaultPlaybackDevice(  pAudioDevice )	getDefaultADevice(  FALSE,  pAudioDevice  )

//
int  list_devices_v(OLD_videoDevices* pVideoDevices);




//
#endif  //  }


