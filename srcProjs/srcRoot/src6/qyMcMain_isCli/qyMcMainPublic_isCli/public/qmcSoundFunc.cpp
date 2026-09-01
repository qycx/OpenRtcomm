
#include	"stdafx.h"

#include	<tchar.h>
#include	<mmsystem.h>
#include	<mmreg.h>

#include	"qyMcMainCommon.h"
#include	"qyDynLib.h"

#include	"qyMcMainRealTimeMediaProc.h"

#include	"qmcAcm.h"
#include	"qmcVideoCapture.h"
#include	"qmcDmoPublic.h"
#include	"tmpCeLib.h"


#include	"myfourcc.h"



 int  makeWaveFormat_pcm(  WORD  nChannels,  int  iHertz,  WORD  wBitsPerSample,  WAVEFORMATEX  *  p  )
{
	memset(  p,  0x00,  sizeof(  p[0]  )  );	
	p->wFormatTag			=	WAVE_FORMAT_PCM;
	p->nChannels			=	nChannels;										//  DEFAULT_audio_nChannels;		//  2;
	p->wBitsPerSample		=	wBitsPerSample  ?  wBitsPerSample  :  16;		//  DEFAULT_audio_wBitsPerSample;	//  16;
	p->cbSize				=	0;
	p->nSamplesPerSec		=	iHertz;  //  22.05 KHz

	p->nBlockAlign		=	(  p->wBitsPerSample  /  8  )  *  p->nChannels;
	//  p->nAvgBytesPerSec	=	p->nSamplesPerSec  *  (  p->wBitsPerSample  /  8  );
	p->nAvgBytesPerSec	=	p->nSamplesPerSec  *  p->nBlockAlign;

	return  0;
}

  //CString  getWaveFormatExStr(  unsigned  char  ucCompressors,  WAVEFORMATEX  *  pWfx  )
 TCHAR  *  getWaveFormatExStr(  unsigned  char  ucCompressors,  WAVEFORMATEX  *  pWfx,  TCHAR  *  tBuf,  unsigned  int  cnt  )
{
	 GUID	clsid;

	 clsid  =  FOURCCMap(  pWfx->wFormatTag  );
	 _sntprintf(  tBuf,  cnt,  _T(  "%s"  ),  getMediaSubtypeName(  clsid  )  );

	 switch  (  ucCompressors  )  {
			 case  CONST_audioCompressors_acm:
				   _sntprintf(  tBuf,  cnt,  _T(  "%s:0x%x,%d,%d,%d"  ),  tBuf,  pWfx->wFormatTag,  pWfx->nChannels,  pWfx->nSamplesPerSec,  pWfx->wBitsPerSample  );
				   break;
			 default:
				     _sntprintf(  tBuf,  cnt,  _T(  "%s:0x%x,%d,%d,%d,%d"  ),  tBuf,  pWfx->wFormatTag,  pWfx->nChannels,  pWfx->nSamplesPerSec,  pWfx->wBitsPerSample,  pWfx->nAvgBytesPerSec  );
				     break;
	 }

	 return  tBuf;
}

 int  getWaveFormatExByStr(  LPCTSTR  str,  WAVEFORMATEX  *  pWfx  )
{
	TCHAR			tBuf[256];
	TCHAR		*	pT;

	lstrcpyn(  tBuf,  str,  mycountof(  tBuf  )  );

	pT  =  _tcschr(  tBuf,  _T(  ':'  )  );
	if  (  !pT  )  return  -1;
	
	pT  ++  ;

	WAVEFORMATEX	wfx;
	TCHAR			*	pT1,  *  pT2;
	memset(  &wfx,  0,  sizeof(  wfx  )  );


	pT1  =  _tcschr(  pT,  _T(  ','  )  );
	if  (  !pT1  )  return  -1;
	pT1[0]  =  0;
	wfx.wFormatTag  =  (  WORD  )_tcstol(  pT,  &pT2,  16  );
	pT  =  pT1  +  1;

	pT1  =  _tcschr(  pT,  _T(  ','  )  );
	if  (  pT1  )  {
		pT1[0]  =  0;
		wfx.nChannels  =  (  WORD  )_tcstol(  pT,  &pT2,  10  );
		pT  =  pT1  +  1;
		pT1  =  _tcschr(  pT,  _T(  ','  )  );
		if  (  pT1  )  {
			pT1[0]  =  0;
			wfx.nSamplesPerSec  =  (  WORD  )_tcstol(  pT,  &pT2,  10  );
			pT  =  pT1  +  1;
			pT1  =  _tcschr(  pT,  _T(  ','  )  );
			if  (  !pT1  )  wfx.wBitsPerSample  =  (  WORD  )_tcstol(  pT,  &pT2,  10  );
			else  {
				  pT1[0]  =  0;
				  wfx.wBitsPerSample  =  (  WORD  )_tcstol(  pT,  &pT2,  10  );
				  pT  =  pT1  +  1;
				  //
				  wfx.nAvgBytesPerSec  =  _tcstol(  pT,  &pT2,  10  );				
			}
		}
	}

	memcpy(  pWfx,  &wfx,  sizeof(  pWfx[0]  )  );
	return  0;
}
