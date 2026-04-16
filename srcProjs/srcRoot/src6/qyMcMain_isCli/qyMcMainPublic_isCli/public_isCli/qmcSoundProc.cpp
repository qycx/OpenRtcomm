
#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>
#include	<mmsystem.h>
#include	<mmreg.h>

#include	"qyMcMainCommon.h"
#include	"qyDynLib.h"

#include	"qyMcMainRealTimeMediaProc.h"

#include	"qmcAcm.h"
#include	"qmcVideoCapture.h"
//#include	"qmcVideoCapture_isCli.h"
#include	"qmcDmoPublic.h"
#include	"tmpCeLib.h"

#include	"qmcCommFunc_isCli.h"


#if  0
 //  2010/08/02
 void  fillIn_wfx_mp3(  unsigned  int  cbwfx,  unsigned  int  bitRate,  WAVEFORMATEX  *  pWfx  )
 {
	 MPEGLAYER3WAVEFORMAT  *  pMp3  =  (  MPEGLAYER3WAVEFORMAT  *  )pWfx;

	 pWfx->nAvgBytesPerSec  =  bitRate  /  8;
	 if  (  cbwfx  >=  sizeof(  WAVEFORMATEX  )  )  pWfx->cbSize  =  sizeof(  MPEGLAYER3WAVEFORMAT  )  -  sizeof(  WAVEFORMATEX  );
	 if  (  cbwfx >=  sizeof(  MPEGLAYER3WAVEFORMAT  )  )  {
		 pMp3->wID  =  MPEGLAYER3_ID_MPEG;
		 pMp3->fdwFlags  =  MPEGLAYER3_FLAG_PADDING_OFF;
		 pMp3->nBlockSize  =  bitRate  *  144  /  pWfx->nSamplesPerSec;
		 pMp3->nFramesPerBlock  =  1;
		 pMp3->nCodecDelay  =  0x0571;
	 }

	 return;
 }
#endif

 //






