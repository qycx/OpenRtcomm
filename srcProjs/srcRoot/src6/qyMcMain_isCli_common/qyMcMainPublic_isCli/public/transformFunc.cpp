

#include	"stdafx.h"
#include	<stddef.h>
#include	<time.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"
#include	"tmpCeLib.h"
#include	"qmcVideoCapture.h"
#include	"qmcDmoPublic.h"
#include	"qyCusResTemp.h"

#include	"qmcCmdProc.h"

#include	"qySqlFunc.h"
#include	"qmcCfg.h"



//
//  2015/02/13
BOOL  bCapAudioQuit(  void  *  pCAP_procInfo_audioCommon,  void  *  p1,  void  *  p2  )
{
#if  0
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  FALSE;
	MC_VAR_common			*	pProcInfo	=	pQyMc->get_pProcInfo(  );//QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;
#endif

	//
	CAP_procInfo_audioCommon  *  pCapProcInfo  =  (  CAP_procInfo_audioCommon  *  )pCAP_procInfo_audioCommon;
	if  (  !pCapProcInfo  )  return  FALSE;

#if  0
	QY_SHARED_OBJ			*	pSharedObj	=	getSharedObjByIndex(  pProcInfo,  pCapProcInfo->iIndex_sharedObj  );
	if  (  !pSharedObj  )  return  FALSE;

	if  (  !bSharedObjActive(  pProcInfo,  pCapProcInfo->iIndex_sharedObj  )  )  {
		return  TRUE;
	}
#endif

	return  pCapProcInfo->thread.bQuit;
}



//
int  capAudioGetWfx(  void  *  pCAP_procInfo_audioCommon,  WAVEFORMATEX  *  pWfx,  void  *  p2  )
 {
	int  iErr  =  -1;
	CAP_procInfo_audioCommon  *  pCapProcInfo  =  (  CAP_procInfo_audioCommon  *  )pCAP_procInfo_audioCommon;

	memcpy(  pWfx,  &pCapProcInfo->compressAudio.ah_decompress.wfx,  sizeof(  pWfx[0]  )  );

	iErr  =  0;
	return  iErr;
 }



//  2016/12/10
int  transformGetWfx(  void  *  pQY_TRANSFORM,  WAVEFORMATEX  *  pWfx,  void  *  p2  )
 {
	int  iErr  =  -1;
	QY_TRANSFORM  *  pTransform  =  (  QY_TRANSFORM  *  )pQY_TRANSFORM;
	TRANSFORM_AUDIO_procInfo  *  pTransformAudio  =  &pTransform->audio;

	memcpy(  pWfx,  &pTransformAudio->ta.ah_decompress.wfx,  sizeof(  pWfx[0]  )  );

	iErr  =  0;
	return  iErr;
 }
