#ifndef __tmpAACCommon_h__
#define __tmpAACCommon_h__ 

//#include	"tmpAACPublic.h"
//#include    "qdc_AAC.h"


#include	<tchar.h>
#include	<string>

#include	"qyMcMainCommon.h"
#include	"dumpAudio.h"
#include	"myinttypes.h"

//extern "C"
//{
//#include "libavutil/opt.h"
//#include "libavcodec/avcodec.h"
//#include "libavutil/imgutils.h"
//
//	//#include "libavcodec/avcodec.h"
//#include "libavformat/avformat.h"
//
//#include <libavutil/channel_layout.h>
//#include <libavutil/samplefmt.h>
//#include <libswresample/swresample.h>
//
//
//#include <libavfilter/buffersink.h>
//#include <libavfilter/buffersrc.h>
//
//	//
//#include <libswscale/swscale.h>
//
//
//
//
//};



#include    "qdc_AAC.h"
#include	"tmpAACPublic.h"

//
#define  CONST_mutexName_syncAAC	_T("syncAAC")


//
int newQdcAACUnitIndex();
void freeQdcAACUnitIndex(int index);
QDC_AAC_unit* getQdcAACUnitByIndex(int index);

//
//int doTest(int index_qdcUnit, char* i_str, char* o_str, int bufSize_o_str);
//int saveFrame(AVFrame* picture, int w, int h, FILE* fo);
int freeDecBufsAAC(int index_qdcUnit);

//
int qdc_aac_init();
int qdc_aac_exit();





//
//int encV_init(int index_qdcUnit, int iFourcc, int in_w, int in_h, int fps, int bitrate, bool bDbg);
//int encV_exit(int index_qdcUnit, bool bDbg);
//int encV_getSpsPps(int index_qdcUnit, byte* spsBuf, int* puiSpsSize, byte* ppsBuf, int* puiPpsSize, byte* vps, int* puiVpsSize, bool bDbg);
//int encV_data(int index_qdcUnit, byte* yuv, int yuvLen, byte* raw, int* pLen_raw, bool bNeed_forceKeyFrame, bool bDbg);
//
//
////
//int decV_init(int index_qdcUnit, int iFourcc, bool bNv, bool bDbg);
//int decV_exit(int index_qdcUnit, bool bDbg);
//int decV_data(int index_qdcUnit, byte* data, int data_size, int iInputBufferPaddingSize, int* pnPktDeced, int* piFourcc_dec, int* piW, int* piH, byte* decBuf, int* piDecBufSize, bool* pbBufTooSmall, bool bDbg);
//int decV_getOutputByIndex(int index_qdcUnit, int index, byte* pbOutData, uint* puiDataSize, bool bDbg);
//int decV_clearOutputs(int index_qdcUnit, bool bDbg);
//
////
//
////
//int encA_init(int index_qdcUnit, short wFormatTag, int bitrate, bool bDbg);
//int encA_exit(int index_qdcUnit, bool bDbg);
//int encA_data(int index_qdcUnit, byte* pcm, int pcmLen, byte* raw, int* pLen_raw, bool bDbg);

//
int decA_init_aac(int index_qdcUnit, unsigned int config, bool bDbg);
int decA_exit_aac(int index_qdcUnit, bool bDbg);
int decA_data_aac(int index_qdcUnit, byte* encData, int encData_size, int iInputBufferPaddingSize, int* pnPktDeced, int* piFmt_dec, byte* decBuf, int* piDecBufSize, bool* pbBufTooSmall, bool bDbg);
int decA_getOutputByIndexAAC(int index_qdcUnit, int index, byte* pbOutData, uint* puiDataSize, bool bDbg);






#endif