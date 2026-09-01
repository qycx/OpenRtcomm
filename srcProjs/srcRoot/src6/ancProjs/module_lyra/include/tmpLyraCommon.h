
#ifndef __tmpLyraCommon_h__
#define __tmpLyraCommon_h__ 

//#include	"tmpAACPublic.h"
//#include    "qdc_AAC.h"


#include	<tchar.h>
#include	<string>

#include	<mmeapi.h>


#include	"qmOpenCommon.h"


//#include	"qyMcMainCommon.h"
//#include	"dumpAudio.h"
//#include	"myinttypes.h"



#include    "qdc_lyra.h"
//#include	"tmpAACPublic.h"

//
#define  CONST_mutexName_syncLyra	_T("syncLyra")



#if  0
//
int decA_init_aac(int index_qdcUnit, unsigned int config, bool bDbg);
int decA_exit_aac(int index_qdcUnit, bool bDbg);
int decA_data_aac(int index_qdcUnit, byte* encData, int encData_size, int iInputBufferPaddingSize, int* pnPktDeced, int* piFmt_dec, byte* decBuf, int* piDecBufSize, bool* pbBufTooSmall, bool bDbg);
int decA_getOutputByIndexAAC(int index_qdcUnit, int index, byte* pbOutData, uint* puiDataSize, bool bDbg);
#endif 








#endif

