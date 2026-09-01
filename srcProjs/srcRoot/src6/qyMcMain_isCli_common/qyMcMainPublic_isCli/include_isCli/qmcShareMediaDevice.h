



#ifndef  __QMCSHAREMEDIADEVICE_H__
#define  __QMCSHAREMEDIADEVICE_H__	//  {

#include	"amCapProc.h"


typedef  struct  __shareMediaDevice_t			{
			
				 BOOL							bInited;

				 //  AV_capStuff					gcap;
				 void						*	p_gcap;

				 //
				 TCHAR							displayName_aDev[128];
				 TCHAR							displayName_vDev[128];

				 //				 
				 BOOL							bAudio;
				 BOOL							bVideo;

				 //
				 SAMPLE_grabber_info			audio,  video;

}		 SHARE_MEDIA_DEVICE;


#endif  //  }


