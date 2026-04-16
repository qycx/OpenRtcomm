
#ifndef  __qdc_ffmpeg_h__
#define  __qdc_ffmpeg_h__


typedef unsigned short ushort;
typedef unsigned char byte;
typedef unsigned char BYTE;
typedef unsigned int uint;
//
#define LOGD	traceLogA
#define LOGE	traceLogA
//
#define M_myfree(p) if(p){myfree(p);p=NULL;}





extern "C"
{
#include "libavutil/opt.h"
#include "libavcodec/avcodec.h"
#include "libavutil/imgutils.h"

#include "libavformat/avformat.h"

#include <libavutil/opt.h>
#include <libavutil/channel_layout.h>
#include <libavutil/samplefmt.h>
#include <libavutil/mem.h>
#include <libswresample/swresample.h>

};


typedef struct {
    byte* pBuf;
    int iBufSize;
    int len;
} CACHE_buf;

//
typedef struct __decBuf_t {
     byte * pBuf;
     int iBufSize;
     int len;
     //
     int bUsed;
} DEC_buf;

//
typedef struct __decBufs_t {
    int maxCnt_decBufMems;

    //
#define CONST_cntof_decBuf_mems2  120
#define CONST_cntof_decBuf_mems_v  30
#define CONST_cntof_decBuf_mems_a  CONST_cntof_decBuf_mems2
    //
    DEC_buf mems[CONST_cntof_decBuf_mems2];
} DEC_bufs;


typedef struct {
    SwrContext* swr;
    int out_sample_rate;
    int out_channels;
    enum AVSampleFormat out_sample_fmt;
    uint64_t out_ch_layout;
} DecA_ResampleCtx;

//
typedef struct __qdc_uint_t {
    bool bUsed;

    //
    struct {
        //
        int iFourcc;

        //
        AVCodec *codec;
        AVCodecContext *c;
        AVFrame *frame;
        AVPacket *pkt;
        //
        int pts;
        int framecnt;
    }  encV_var;

    //
    struct {
        //
        int iFourcc;

        //
        const AVCodec *codec;
        AVCodecParserContext *parser;
        AVCodecContext *c;
        FILE *f;
        AVFrame *frame;
        AVPacket *pkt;

        //
        int iFourcc_dec;
        int iW;
        int iH;

        //
        //int iBufSize_decBuf;

		//
		struct SwsContext *sws_ctx;
		//
		uint8_t *dst_data[4];    
		int dst_linesize[4];
		//
		int dst_bufsize;
		//
		bool  bInited_dst;


		
        //
        FILE * fo;

    } decV_var;

    //
    struct {
        ushort        wFormatTag;         /* format type */

        AVCodec *codec;
        AVCodecContext *c;
        AVFrame *frame;
        AVPacket *pkt;

        //
        struct {
            char * pBuf;
            int iBufSize;
            int len;
        }cache;

        //int i, j, k, ret;
        //FILE *f_i;
        FILE *f;


    } encA_var;

    //
    struct {
        AVCodec *codec;
        AVCodecContext *c;
        AVCodecParserContext *parser;
        //int len, ret;
        //FILE *f, *outfile;
        //uint8_t inbuf[AUDIO_INBUF_SIZE + AV_INPUT_BUFFER_PADDING_SIZE];
        //uint8_t *data;
        //size_t   data_size;
        AVPacket *pkt;
        AVFrame *decoded_frame;

        //
        CACHE_buf cache;

        //
        FILE * outfile;

        //
        DecA_ResampleCtx resample;

    }decA_var;

    //
    DEC_bufs    decBufs;

} QDC_unit;


//
//
class CQdc {
public:
    QDC_unit *m_pMems;
    ushort m_usMaxCnt;

    //
    bool bDone_qdc_init;

    //
    CQdc();
    ~CQdc();

private:
    int init();
    void exit();
};

extern  CQdc g_qdc;

//
class CQdcObj_ffmpeg {
public:
	int m_index_qdcUnit;
	//
	bool bDec;
	//
	struct {
		char * pBuf;
		int		iBufSize;
		int		len;
	}		output;
	//
public:
	CQdcObj_ffmpeg() {
		m_index_qdcUnit = -1;
		//
		bDec=false;
		//
		memset(&output,0,sizeof(output));
	}



};


//
QDC_unit * getQdcUnitByIndex(int index);
int freeDecBufs(int index_qdcUnit);

//
int encA_exit(int index_qdcUnit,bool bDbg);


#endif  

