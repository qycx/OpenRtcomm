
#ifndef  __ctxQmcTmpl_public_h__
#define  __ctxQmcTmpl_public_h__	//  {

#include	<mmeapi.h>

#include	"webrtc\voice_engine\qycxprojs\qyOpen\include\ctxqyTmpl.h"
#include	"qmcStruct_defs.h"

//
class  CCtxQmcTmpl_public: public CCtxQyTmpl  {

public:
	CCtxQmcTmpl_public(  );
	virtual  ~CCtxQmcTmpl_public(  );

public:


	virtual  int  broadcastRecorderStatus( )  {  return  -1;  }
	virtual  int  MACRO_getuiBytesRecorded_perBlockAlign(  AUDIO_COMPRESSOR_CFG  *pAudioCompressor,  WAVEFORMATEX  *  pWf_org  )  {  return  -1;  }		



};




#endif  //  }


