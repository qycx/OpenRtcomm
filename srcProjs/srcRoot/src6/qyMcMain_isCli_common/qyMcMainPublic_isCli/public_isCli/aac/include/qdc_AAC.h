#ifndef  __qdc_aac_h__
#define  __qdc_aac_h__


typedef unsigned short ushort;
typedef unsigned char byte;
typedef unsigned char BYTE;
typedef unsigned int uint;
//
#define LOGD	traceLogA
#define LOGE	traceLogA
//
#define M_myfree(p) if(p){myfree(p);p=NULL;}




/*
extern "C"
{
#include "libavutil/opt.h"
#include "libavcodec/avcodec.h"
#include "libavutil/imgutils.h"

    //#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"

};

*/

#include "fdk-aac/aacdecoder_lib.h"



//
typedef struct __decBufAAC_t {
    INT_PCM* pBuf;
    int iBufSize;
    int len;
    //
    int bUsed;
} DEC_buf_aac;

//
typedef struct __decBufsAAC_t {
    int maxCnt_decBufMems;

    //
#define CONST_cntof_decBuf_mems2  120
#define CONST_cntof_decBuf_mems_v  30
#define CONST_cntof_decBuf_mems_a  CONST_cntof_decBuf_mems2
    //
    DEC_buf_aac mems[CONST_cntof_decBuf_mems2];
} DEC_bufs_aac;

//
typedef struct __qdc_aac_uint_t {
    bool bUsed;

    //
    //struct {
    //    ushort        wFormatTag;         /* format type */

    //    AVCodec* codec;
    //    AVCodecContext* c;
    //    AVFrame* frame;
    //    AVPacket* pkt;

    //    //
    //    struct {
    //        char* pBuf;
    //        int iBufSize;
    //        int len;
    //    }cache;

    //    //int i, j, k, ret;
    //    //FILE *f_i;
    //    FILE* f;


    //} encA_var;


    //
    struct {
        //AVCodec* codec;
        //AVCodecContext* c;
        //AVCodecParserContext* parser;
        ////int len, ret;
        ////FILE *f, *outfile;
        ////uint8_t inbuf[AUDIO_INBUF_SIZE + AV_INPUT_BUFFER_PADDING_SIZE];
        ////uint8_t *data;
        ////size_t   data_size;
        //AVPacket* pkt;
        //AVFrame* decoded_frame;

        HANDLE_AACDECODER aacDecoder = nullptr;

        //
        struct {
            char* pBuf;//[AUDIO_INBUF_SIZE + AV_INPUT_BUFFER_PADDING_SIZE];
            int iBufSize;
            int len;
        } cache;

        //
        FILE* outfile;


    }decA_var;

    //
    DEC_bufs_aac    decBufs;

} QDC_AAC_unit;


//
//
class CQdcAAC {
public:
    QDC_AAC_unit* m_pMems;
    ushort m_usMaxCnt;

    //
    bool bDone_qdc_init;

    //
    CQdcAAC();
    ~CQdcAAC();

private:
    int init();
    void exit();
};

extern  CQdcAAC g_qdcAAC;

//
class CQdcObj_aac {
public:
    int m_index_qdcUnit;
    //
    bool bDec;
    //
    struct {
        char* pBuf;
        int		iBufSize;
        int		len;
    }		output;
    //
public:
    CQdcObj_aac() {
        m_index_qdcUnit = -1;
        //
        bDec = false;
        //
        memset(&output, 0, sizeof(output));
    }



};


//
QDC_AAC_unit* getQdcAACUnitByIndex(int index);
int freeDecBufs(int index_qdcUnit);

//
int encA_exit(int index_qdcUnit, bool bDbg);





#endif