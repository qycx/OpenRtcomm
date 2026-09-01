
#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"dlgtalkproc.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qmcDmoPublic.h"

#include	"wallTalkers.h"
#include	"qmcGpsProc.h"
//#include	"soundProc_msAec/include/msAecCommon.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"
#include	"amCapPublic.h"
#include	"isCliD3dPublic.h"
#include	"qyMcMainWndProc.h"
#include	"imgProcessPublic.h"




	
int dyn_initAecObj(int sampleRate, void** ppObj)
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->help_audioProc.bOk  )  {
		showInfo_open0(  0,  0,  _T(  "dyn_initAecObj: aec not loaed"  )  );
		return  -1;
	}

	return  pFuncs->help_audioProc.pf_initAecObj(sampleRate,ppObj  );

}



	int dyn_exitAecObj(void** ppObj)
	{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->help_audioProc.bOk  )  {
		showInfo_open0(  0,  0,  _T(  "dyn_exitAecObj: aec not loaed"  )  );
		return  -1;
	}

	return  pFuncs->help_audioProc.pf_exitAecObj(ppObj);

	}


	
	int dyn_aecObj_doAec(void* pObjParam, char* render_data, unsigned int render_dataLen, char* mic_data, unsigned int mic_dataLen)
	{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->help_audioProc.bOk  )  {
		showInfo_open0(  0,  0,  _T(  "dyn_aecObj_doAec: aec not loaed"  )  );
		return  -1;
	}

	return  pFuncs->help_audioProc.pf_aecObj_doAec( pObjParam,  render_data,  render_dataLen,  mic_data, mic_dataLen);


	}


	//
	int dyn_initAudioMixerObj(int sampleRate, int nSources, PF_inStream4 pf, void* p0, void** ppObj)
	{
		MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
		if (!pProcInfo)  return  -1;
		FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
		if (!pFuncs)  return  -1;

		if (!pFuncs->help_audioProc.bOk) {
			showInfo_open0(0, 0, _T("dyn_aecObj_doAec: aec not loaed"));
			return  -1;
		}

		return  pFuncs->help_audioProc.pf_initAudioMixerObj(sampleRate, nSources, pf, p0, ppObj);

	}

	//
	int dyn_exitAudioMixerObj(void** ppObj)
	{
		MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
		if (!pProcInfo)  return  -1;
		FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
		if (!pFuncs)  return  -1;

		if (!pFuncs->help_audioProc.bOk) {
			showInfo_open0(0, 0, _T("dyn_aecObj_doAec: aec not loaed"));
			return  -1;
		}

		return  pFuncs->help_audioProc.pf_exitAudioMixerObj(ppObj);

	}

	//
	int dyn_audioMixerObj_doMix(void* pObjParam, char* dataBuf, unsigned int* puiSize)
	{
		MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
		if (!pProcInfo)  return  -1;
		FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
		if (!pFuncs)  return  -1;

		if (!pFuncs->help_audioProc.bOk) {
			showInfo_open0(0, 0, _T("dyn_aecObj_doAec: aec not loaed"));
			return  -1;
		}

		return  pFuncs->help_audioProc.pf_audioMixerObj_doMix(pObjParam, dataBuf, puiSize);

	}

	

