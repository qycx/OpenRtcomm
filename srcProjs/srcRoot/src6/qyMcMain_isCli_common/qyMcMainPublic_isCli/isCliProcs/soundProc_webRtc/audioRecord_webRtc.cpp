

#include	"stdafx.h"
#include	<Windows.h>
#include	<ShlObj.h>
#include	<MMSystem.h>
#include	<stdio.h>
#include	<tchar.h>
#include	<WinSock2.h>

#include	"qyCommon.h"

#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyMcMainRealTimeMediaProc.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"
#include	"qyPlaySound_wave.h"
//  #include	"QyRecordSound_wave.h"
#include	"module_qisCamCap.h"

#include	"mmDeviceProc.h"
#include	"qmcCommFunc_isCli.h"
#include	"ctxMcThread.h"
#include	"qisWebRtcPublic.h"
#include <help_webrtc1Public.h>


//
static  BOOL  g_bInited_webRtc  =  FALSE;

//
int  init_webRtc(  )
{
	CCtxQyMc* pQyMc = g_pQyMc;

	//
	if (!g_bInited_webRtc) {
		g_bInited_webRtc = TRUE;
		//
		if (!pQyMc->b__USE_webrtc1__) {
			voe_init();

			//
			char* pVer = voe_ver();
			if (!pVer)  pVer = (char*)"";
			TCHAR  tBuf[128];
			_sntprintf(tBuf, mycountof(tBuf), _T("init_webRtc: ver %S"), pVer);
			showInfo_open0(0, 0, tBuf);
		}
	}


	return  0;
}

//
int  exit_webRtc()
{
	CCtxQyMc* pQyMc = g_pQyMc;

	//
	if  (  g_bInited_webRtc  )  {
		g_bInited_webRtc  =  FALSE;
		//
		if (!pQyMc->b__USE_webrtc1__) {
			voe_exit();
		}
	}

	return  0;
}

//
int  my_outStream(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	CAP_procInfo_recordSound  *  pRecord  =  (  CAP_procInfo_recordSound  *  )p0;
	char  *  buf  =  (  char  *  )p1;
	int  len  =  (  int )  p2;

	//
	TCHAR  tBuf[128];
#if  0
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "my_outStream: len %d\n"  ),  len  );
	OutputDebugString(  tBuf  );
#endif

	//如果音频输出开关为true  说明直接闭掉声音输出
	if (pProcInfo->av.hk.portStatus.bDisable_lb_out) {
		return -1;
	}

	//
	int  dataLength  =  len;
						
	//
	if  (  dataLength  +  pRecord->cache.dataLen_pAudioDataBuf  <  pRecord->cache.bufSize_pAudioDataBuf  )  {						
		memcpy(  pRecord->cache.pAudioDataBuf  +  pRecord->cache.dataLen_pAudioDataBuf,  buf,  dataLength  );						
		pRecord->cache.dataLen_pAudioDataBuf  +=  dataLength;					
	}

	//
	for  (  ;  ;  )  {
		 if  (  pRecord->cache.dataLen_pAudioDataBuf  <  pRecord->cache.nBytes_toRecord  )  break;											 
		 //
#if  0
		 TCHAR  tBuf[128];
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "nAvgBytesPerSec %d"  ),  pRecord->cache.nAvgBytesPerSec  );
		 showInfo_open0(  0,  _T(  "my_outStream"  ),  tBuf  );
#endif
		 //
		 processInput_post(  pProcInfo,  pRecord->cache.nAvgBytesPerSec,  (  BYTE  *  )pRecord->cache.pAudioDataBuf,  pRecord->cache.nBytes_toRecord,  (  MIS_MSGU  *  )pRecord->cache.pMsgBuf  );				    					
		 memcpy(  pRecord->cache.pAudioDataBuf,  pRecord->cache.pAudioDataBuf  +  pRecord->cache.nBytes_toRecord,  pRecord->cache.dataLen_pAudioDataBuf  -  pRecord->cache.nBytes_toRecord  );
		 pRecord->cache.dataLen_pAudioDataBuf  -=  pRecord->cache.nBytes_toRecord;			 
		
	}			

	//  2017/06/19
	pRecord->dwTickCnt_lastAudioGot  =  GetTickCount(  );

	//
	return  0;
}

//
int  startRecord_webRtc(unsigned short usCntLimit_activeMems_from)
{
	int  iErr  =  -1;

	//
	CCtxQyMc* pQyMc = g_pQyMc;
	MC_VAR_isCli			*	pProcInfo				=		QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	CAP_procInfo_recordSound  *  pRecord  =  &pProcInfo->av.localAv.recordSoundProcInfo;

	//
	showInfo_open0(  0,  0,  _T(  "startRecord_webRtc"  )  );

	//
	pRecord->cache.bufSize_pAudioDataBuf  =  pProcInfo->cfg.uiBufSize_myPlayAudioData;
	if  (  !(  pRecord->cache.pAudioDataBuf  =  (  char  *  )malloc(  pRecord->cache.bufSize_pAudioDataBuf  )  )  )  goto  errLabel;
	pRecord->cache.nBytes_toRecord  =  pRecord->compressAudio.compressor.uiBytesRecorded_perBlockAlign  *  pRecord->compressAudio.ah_decompress.wfx.nBlockAlign;
	pRecord->cache.nAvgBytesPerSec  =  pRecord->compressAudio.ah_decompress.wfx.nAvgBytesPerSec;
	pRecord->cache.pMsgBuf  =  malloc(  sizeof(  MIS_MSGU  )  );
	if  (  !pRecord->cache.pMsgBuf  )  goto  errLabel;

	//
	//pRecord->recThread.bRunning  =  TRUE;
	
	//
	if (pQyMc->b__USE_webrtc1__) {
		if (dyn_help_webrtc_init(usCntLimit_activeMems_from,  my_inStream4_toMix,  pProcInfo,  my_outStream,pRecord, &pRecord->u.webRtc.pObj)) {
			showInfo_open0(0, 0, _T("help_webrtc_init failed"));
			goto  errLabel;
		}

	}
	else {

		//
		if (voe_record_init(&pProcInfo->av.localAv.recordSoundProcInfo, my_outStream)) {
			goto  errLabel;
		}

		//
			//get_reor
		TCHAR  recorder_selected[256] = _T("");
		TCHAR  webcam_selected[256] = _T("");

		char  recorder_sel_utf8[256] = "";

		//
		if (pProcInfo->cfg.policy.audio.ucbNot_selectDefaultRecorder) {
			getChosenDevice(recorder_selected, mycountof(recorder_selected), webcam_selected, mycountof(webcam_selected), NULL, 0, NULL, NULL);
			//
			myTChar2Utf8(recorder_selected, recorder_sel_utf8, mycountof(recorder_sel_utf8));
		}

		//
		BOOL  bSel = false;
		if (recorder_sel_utf8[0]) {
			int  index = 0;
			if (!voe_getADeviceIndex(recorder_sel_utf8, &index)) {
				voe_record_setDevice(&pProcInfo->av.localAv.recordSoundProcInfo, index);
				//
				bSel = true;
				//
				showInfo_open0(0, _T("select"), recorder_selected);
			}
		}
		if (!bSel) {
			voe_record_setDevice(&pProcInfo->av.localAv.recordSoundProcInfo, -2);  //  -2 means default device
			//
			showInfo_open0(0, _T("select"), _T("-2, default microphone"));
		}

		//
		voe_record_start(&pProcInfo->av.localAv.recordSoundProcInfo);
	}

	//
	iErr  =  0;
errLabel:
	return  iErr;
}

int  stopRecord_webRtc()
{
	int  iErr = -1;

	//
	CCtxQyMc* pQyMc = g_pQyMc;
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
	if (!pProcInfo)  return  -1;
	CAP_procInfo_recordSound* pRecord = &pProcInfo->av.localAv.recordSoundProcInfo;

	//
	showInfo_open0(0, 0, _T("stopRecord_webRtc"));

	if (pQyMc->b__USE_webrtc1__) {
		dyn_help_webrtc_exit(&pRecord->u.webRtc.pObj);
	}
	else {
		//
		voe_record_exit();
	}

	//
	//pRecord->recThread.bRunning  =  FALSE;

	//
	MACRO_safeFree(  pRecord->cache.pAudioDataBuf  );
	MACRO_safeFree(  pRecord->cache.pMsgBuf  );


	iErr  =  0;
errLabel:
	return  iErr;
}





