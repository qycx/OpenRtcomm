

#ifndef  __QMCSOUNDDX_H__
#define  __QMCSOUNDDX_H__	//  {

//
#include	"qisDefs.h"

//
typedef  struct  __myRecordSoundDx_t				{
					 LPDIRECTSOUNDCAPTURE			lpdsc;

					 DSCBUFFERDESC					dscbDesc;
					 LPDIRECTSOUNDCAPTUREBUFFER		lpdscb;

					 DSBPOSITIONNOTIFY		        rgdscbpn[CONST_numCaptureEvents];
					 LPDIRECTSOUNDNOTIFY			lpdsnInput;

					 //
					 DWORD							dwMyReadCursor;

					 //  DWORD							dwTickCnt_sendLocalAv;

}		 myRECORD_SOUND_dx;


typedef  struct  __myPlaySoundDx_t					{
				 DSBUFFERDESC						dsbDesc;
				 LPDIRECTSOUNDBUFFER			    lpdsb;

				 LPDIRECTSOUNDNOTIFY				lpdsnOutput;
				 //
				 DWORD								dwOffset_notify_unit;
				 DWORD								dwNotifyCount;
				 LPDSBPOSITIONNOTIFY				lpdsbpns;

				 //
				 DWORD								dwMyWriteCursor;	//		=  0xFFFFFFFF;


				 unsigned  int						uiMaxMsgWaiting;

				 //
				 BOOL								bPlayInited;
				 BOOL								bPlayStarted;
				 
}		 myPLAY_SOUND_dx;


typedef  struct  __qmcSoundMgr_t					{
	
				 BOOL								bInited;		 

				 struct								{

					 BOOL							bStop;				

					 struct							{
						 LPDIRECTSOUND		        lpds;			//  for audio player
					 }								playSound;
					 BOOL							bPlaySoundInited;	//  for audio player. 2009/02/11

					 myRECORD_SOUND_dx				myRs;

				 }									m_var;

				 //
				 __qmcSoundMgr_t(  )  {  
					 memset(  this,  0,  sizeof(  struct  __qmcSoundMgr_t  )  );  
					 OutputDebugString(  _T(  "qmcSoundMgr is inited.\n"  )  );
				 };
				 

}		 QMC_SOUND_MGR;


extern  QMC_SOUND_MGR	gQmcSoundMgr;	

//
 int  initPlay_dx(  void  *  pDynLib_dx,  QMC_SOUND_MGR	*	pMgr,  PLAY_AUDIO_procInfo  *  pPlayAudio,  DWORD  dwBufferBytes,  myPLAY_SOUND_dx  *  p  );
 int  exitPlay_dx(  void  *  pDynLib_dx,  QMC_SOUND_MGR	*	pMgr,  PLAY_AUDIO_procInfo  *  pPlayAudio,  myPLAY_SOUND_dx  *  p  );
 int  processOutput( QMC_SOUND_MGR  *  pMgr,  PLAY_AUDIO_procInfo  *  pPlayAudio,  myPLAY_SOUND_dx  *  p,  BOOL  bFillWithSilence,  LPBYTE  pbInput1,  DWORD  dwNumBytes  );

 

#endif  //  }


