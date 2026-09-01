
#include	"stdafx.h"
 
#include	<mmsystem.h>
#include	<dmo.h>
#include	<dsound.h>
#include	<stddef.h>

#include	"qyMcMainCommon.h"
#include	"qyDynLib.h"

#include	"qyMcMainRealTimeMediaProc.h"

#include	"tmpCeLib.h"

#include	"qyAvRecord.h"
#include	"qyAvRecord_dx.h"
#include	"qmcSound_dx.h"

#include	"qmcVideoCapture_isCli.h"
#include	"qyTick.h"
#include	"qyAvRecordPublic.h"


 //extern "C" DWORD WINAPI mcThreadProc_playAudio( LPVOID lpParameter );


int  startPlayAudio_dSound(  void  *  pPlayerParam  )
{
	int  iErr  =  -1;
	 QY_PLAYER				*	pPlayer  =  (  QY_PLAYER  *  )pPlayerParam;
	 PLAY_AUDIO_procInfo	*	pPlayAudio  =  &pPlayer->audio;

	 CCtxQyMc *pQyMc=g_pQyMc;
	 CCtxQmc * pProcInfo=(CCtxQmc  *  )pQyMc->get_pProcInfo();

	 //
	 pPlayAudio->cache.uiBufSize  =  max(  (  CONST_bufSize_transferAudioData  +  256  )  *  2,  pPlayAudio->ah.wfx.nAvgBytesPerSec  *  2  );
	 pPlayAudio->cache.pBuf  =  (  char  *  )malloc(  pPlayAudio->cache.uiBufSize  );
	 if  (  !pPlayAudio->cache.uiBufSize  ||  !pPlayAudio->cache.pBuf  )  goto  errLabel;

	 //
	 pPlayAudio->cache.pLeft  =  pPlayAudio->cache.pBuf;
	 pPlayAudio->cache.nLeft  =  0;
	 pPlayAudio->cache.dwTickCnt_lastAudioData3  =  myGetTickCount(  mynull  );

	 //
 	 pPlayAudio->dwTickCnt_start  =  M_GetTickCount_audio(  tickObj  );		//  2010/05/04
	 pPlayer->uiSampleTimeInMs_start  =  0;
	 memset(  &pPlayAudio->m_var,  0,  sizeof(  pPlayAudio->m_var  )  );

	 //  2018/06/16
	 pPlayAudio->bNeedStop_webRtc_my_inStream  =  FALSE;

	 //
	 pPlayAudio->bRunning  =  TRUE;

	 //
	 /*
	 if  (  voe_play_init(  pPlayer,  my_inStream,  &pPlayAudio->webRtc.pVoePlay  )  )  {
		 goto  errLabel;
	 }
	 */

	 if  (  startQThread(  mcThreadProc_playAudio,  pProcInfo,  NULL,  (  QY_qThreadProcInfo_common  *  )pPlayAudio  )  )  goto  errLabel;



	iErr  =  0;
errLabel:
	return  iErr;
}


//
int  stopPlayAudio_dSound(  void  *  pPlayerParam  )
{
	int  iErr  =  -1;
	 QY_PLAYER				*	pPlayer  =  (  QY_PLAYER  *  )pPlayerParam;
	 PLAY_AUDIO_procInfo	*	pPlayAudio  =  &pPlayer->audio;



	 //
	 //voe_play_exit(  &pPlayAudio->webRtc.pVoePlay  );
	 myWaitForQThread_infinite(  (  QY_qThreadProcInfo_common  *  )pPlayAudio,  _T(  "doApplyForPlayer"  )  );								  

	 //
	 pPlayAudio->bRunning  =  FALSE;
	 
	 //
	 MACRO_safeFree(  pPlayAudio->cache.pBuf  );


	iErr  =  0;
errLabel:
	return  iErr;


}


