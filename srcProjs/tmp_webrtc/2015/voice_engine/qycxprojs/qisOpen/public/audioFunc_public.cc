

//#include	"stdafx.h"

//#include	<mmsystem.h>
//#include	<mmreg.h>

#include	"webrtc\voice_engine\qycxprojs\qisOpen\include\audioFunc_public.h"

#include	"vcruntime_string.h"





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


