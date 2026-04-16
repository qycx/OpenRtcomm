
#ifndef  __qnmCommProc_is_open_h__
#define  __qnmCommProc_is_open_h__	//  {

//
#include <tchar.h>
#include	"qmOpenCommon.h"




//
#ifdef  __cplusplus
extern  "C" {
#endif 

	class Param_dbg {
	public:
		bool	m_bShowInfo;
		TCHAR* m_pHint;

		//
		Param_dbg()
		{
			m_bShowInfo = true;
			// m_pHint = (TCHAR*)_T("");
			m_pHint = nullptr;
			return;
		}
	};


#ifdef  __cplusplus
}
#endif 


//
//
typedef  struct  __myDebugStep_t									{										
				 M_debugStep_common

				 //
				 unsigned  int										uiCnt_DMO_E_NOTACCEPTING;
				 unsigned  int										nErrs_ProcessInput;
				 unsigned  int										nErrs_ProcessOutput;
				 unsigned  int										nErrs_pOutputBuffers_index;
				 //
				 struct												{
					 BOOL											bInited;
					 BOOL											bStarted;
					 //
					 HRESULT										hr_GetState_beforeStart;
					 int											fs_beforeStart;
					 //
					 BOOL											bBeforeRun;
					 HRESULT										hr_run;
					 //
					 DWORD											dwTickCnt_startToQuit;
					 //
					 HRESULT										hr_GetState_beforeStop;
					 int											fs_beforeStop;
					 //
					 struct											{
						M_debugStep_common
						//
						HRESULT										hr;
						BOOL										bPktGot;
						BOOL										bParentQuit;						
						//
						BOOL										bFailed;
						//
					 }												FillBuffer;


					 //
				 }													fg;
				 //  2014/07/17
				 DEBUG_step_dec										dec;
				 //
				 int												iErr_thread;								//  2012/09/08
				 //
				 struct												{											//  2014/05/08
					TCHAR											tWhere[16];
					unsigned  int									uiStep;
				 }													showInfo;
				 //
}		 MY_DEBUG_STEP;


//
#define		MACRO_qyQThreadProcInfo_common		QY_Q2			q2;							\
												BOOL			bQInited;					\
												DWORD			dwThreadId;					\
												HANDLE			hThread;					\
												BOOL			bQuit;						\
												DWORD			dwTickCnt_start;			\
												BOOL			bRunning;					\
												MY_DEBUG_STEP	debugStep;


//
typedef  struct  __audioPlayCfg_t									{
				 unsigned  short									usMinTimeInMsOfAudioDataPlaying;					//  2009/06/14
				 //  
				 unsigned  short									usAudioDataAddedToPlayEveryTime;					//  2009/06/16
				 //
				 unsigned  short									usNotifyIntervalInMs_needMoreAudioData;				//  2009/06/14. = CONST_notifyInterval
				 //
				 unsigned  short									usMinTimeInMsToPlay;								//  2012/01/27
				 //
				 unsigned  short									usMaxTimeInMsToPlay;								//  2009/06/03
				 unsigned  short									usMaxTimeInMsToBeRemoved;							//  2009/06/03
}		 AUDIO_PLAY_CFG;


#endif  }



