
#ifndef  __mixProc_h__
#define  __mixProc_h__	//  {

//
#include <qnmCommProc_mis.h>
#include	"ctxMcThread.h"





//
typedef  struct  __mixProcInfo_t {
	QY_qThreadProcInfo_common	thread;

	//
	unsigned  int				uiTranNo_openAvDev_a;

	//
	int							iIndex_localPlayer;

	//
	WAVEFORMATEX				wfx;

	//
	FILE* fp_debug;

	//
} Mix_procInfo;

//
//
typedef  struct  __ctx_mix_t {		//  2009/09/05				
				 CTX_MC_thread							common;

				 //
				 void* pAudioMixerObj;

}		  CTX_mix;



//
extern "C" DWORD WINAPI mcThreadProc_mix(LPVOID lpParameter);
int  playMixerAudioData(void* pProcInfo, int  iTaskId, unsigned  int  uiTranNo, WAVEFORMATEX* pWf, int  iSampleTimeInMs, unsigned  int  uiPts,  BYTE* pInput, unsigned  int  inputLen, Mix_procInfo* pMixProcInfo);



#endif  //  }


