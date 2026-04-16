

#ifndef  __QMCSOUNDDX_H__
#define  __QMCSOUNDDX_H__	//  {

#include	<mmreg.h>
#include	<mmeapi.h>
#include <dsound.h>

//
#include	"qmcCommFunc_is_open.h"



//
#define		CONST_numCaptureEvents					3	//			3


typedef  struct  __myRecordSoundDx_t				{
					 LPDIRECTSOUNDCAPTURE			lpdsc;

					 DSCBUFFERDESC					dscbDesc;
					 LPDIRECTSOUNDCAPTUREBUFFER		lpdscb;

					 //
					 DWORD							dwOffset_notify_unit;
					 DWORD							dwNotifyCount;

					 //
					 DSBPOSITIONNOTIFY		        rgdscbpn[CONST_numCaptureEvents];
					 LPDIRECTSOUNDNOTIFY			lpdsnInput;
					 
					 //  2009/02/13				 
					 HANDLE							hEvents[CONST_numCaptureEvents];

					 //
					 DWORD							dwMyReadCursor;

					 //  DWORD						dwTickCnt_sendLocalAv;



}		 myRECORD_SOUND_dx;


//
#define		CONST_playerNotifyCnt					20


//
typedef  struct  __myPlaySoundDx_t					{
				 DSBUFFERDESC						dsbDesc;
				 LPDIRECTSOUNDBUFFER			    lpdsb;

				 LPDIRECTSOUNDNOTIFY				lpdsnOutput;
				 //
				 DWORD								dwOffset_notify_unit;
				 DWORD								dwNotifyCount;
				 LPDSBPOSITIONNOTIFY				lpdsbpns;

				 //
				 HANDLE								notifEvents[CONST_playerNotifyCnt];
				 
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
int  initPlay_dx2(void* pDynLib_dx, PLAY_AUDIO_procInfo* pPlayAudio, DWORD  dwBufferBytes, myPLAY_SOUND_dx* p);
int  exitPlay_dx2(void* pDynLib_dx, PLAY_AUDIO_procInfo* pPlayAudio, myPLAY_SOUND_dx* p);
int startOutputBuf2(QMC_SOUND_MGR* pMgr, PLAY_AUDIO_procInfo* pPlayAudio, myPLAY_SOUND_dx* p);
//
int  processOutput2(QMC_SOUND_MGR* pMgr, PLAY_AUDIO_procInfo* pPlayAudio, myPLAY_SOUND_dx* p, BOOL  bFillWithSilence, LPBYTE  pbInput1, DWORD  dwNumBytes);




#endif  //  }


