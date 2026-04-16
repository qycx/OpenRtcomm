//
// Created by qycx on 2021/3/3.
//
#include	"stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "..\\aac\\include\\tmpAACCommon.h"

//
#define myAUDIO_REFILL_THRESH 4096


int decA_init_aac(int index_qdcUnit, unsigned int config, bool bDbg) {
    int iErr = -1;
    QDC_AAC_unit *pUnit = getQdcAACUnitByIndex(index_qdcUnit);
    if (!pUnit) return -1;

    pUnit->decA_var.aacDecoder = aacDecoder_Open(TT_MP4_RAW/*TT_MP4_ADTS*/, 1);
    if (pUnit->decA_var.aacDecoder == nullptr) {
        //std::cerr << "Failed to open AAC decoder." << std::endl;
        goto errLabel;
    }
    

    {
        //UCHAR config[] = { 0x11, 0x88 }; 
        //UCHAR config3[] = { 0x14, 0x08 };
        UCHAR config3[] = { (config & 0xff00) >> 8, config & 0xff };
        UCHAR config2[] = { 0xBA, 0x08,0x00, 0x00 };
        //UINT configSize = 2;

        UCHAR* conf[] = { config3 };
        static UINT conf_len = sizeof(conf);

        AAC_DECODER_ERROR err; err = aacDecoder_ConfigRaw(pUnit->decA_var.aacDecoder, conf, &conf_len);
        if (err != AAC_DEC_OK) {
            goto errLabel;
        }


        pUnit->decA_var.cache.iBufSize = 200000;
        pUnit->decA_var.cache.pBuf = (char*)mymalloc(pUnit->decA_var.cache.iBufSize);
        if (pUnit->decA_var.cache.pBuf == NULL)goto errLabel;

        //
        pUnit->decBufs.maxCnt_decBufMems = CONST_cntof_decBuf_mems_a;    //
    }

    //
    iErr = 0;
errLabel:
    if (iErr) {
        decA_exit_aac(index_qdcUnit, bDbg);
    }

    return iErr;


}

int decA_exit_aac(int index_qdcUnit,bool bDbg) {
    int iErr = -1;
    QDC_AAC_unit *pUnit = getQdcAACUnitByIndex(index_qdcUnit);
    if (!pUnit) return -1;

    //
    if(pUnit->decA_var.cache.pBuf){
        myfree(pUnit->decA_var.cache.pBuf); pUnit->decA_var.cache.pBuf=NULL;
    }

    //
    freeDecBufsAAC(index_qdcUnit);

    if (pUnit->decA_var.aacDecoder != nullptr) {
        aacDecoder_Close(pUnit->decA_var.aacDecoder);
    }

  

    iErr = 0;
    errLabel:
    return iErr;
}

//int frame2Buf_a(AVCodecContext*dec_ctx,AVFrame * frame, int bytes_per_sample, byte * pcm,FILE * outfile)
//{
//    int i;
//    int ch;
//
//    /*
//    int data_size=bytes_per_sample;
//    for (i = 0; i < frame->nb_samples; i++)
//        for (ch = 0; ch < dec_ctx->channels; ch++)
//            fwrite(frame->data[ch] + data_size*i, 1, data_size, outfile);
//            */
//
//
//    byte *p=pcm;
//    for ( i=0;i<frame->nb_samples;i++){
//        for (ch=0;ch<dec_ctx->channels;ch ++){
//            //
//            memcpy(p,frame->data[ch]+bytes_per_sample*i,bytes_per_sample);
//            p+=bytes_per_sample;
//        }
//    }
//
//
//    return 0;
//}
//
//
//int mysaveFrame_a(int index_qdcUnit, AVCodecContext *dec_ctx, AVFrame * frame,int bytes_per_sample,
//                  int *pnPktDeced,
//                  byte * decBuf, int *piDecBufSize, bool *pbBufTooSmall,
//                  FILE * fo,
//                  bool bDbg)
//{
//    int iErr = -1;
//    QDC_unit *pUnit = getQdcUnitByIndex(index_qdcUnit);
//    if (!pUnit) return -1;
//
//    //
//    byte * p;
//
//    /*
//    fwrite(picture->data[0],yLine,1,fo);
//    fwrite(picture->data[1],yLine/4,1,fo);
//    fwrite(picture->data[2],yLine/4,1,fo);
//     */
//    (*pnPktDeced)++;
//
//
//    //
//    int imgSize=frame->nb_samples*dec_ctx->channels*bytes_per_sample;//frame-> w*h*3/2;
//    if ( decBuf==NULL || imgSize>*piDecBufSize) {
//        *pbBufTooSmall=true;
//    }
//
//
//    if ( *pbBufTooSmall||*pnPktDeced>1) {
//        int i;
//        //
//        for (i = 0; i < pUnit->decBufs.maxCnt_decBufMems; i++) {
//            DEC_buf *pMem = &pUnit->decBufs.mems[i];
//            if (!pMem->bUsed) break;
//        }
//        if (i == pUnit->decBufs.maxCnt_decBufMems) {
//            LOGD((char*)"maxCnt_decBufMems too small");
//            goto errLabel;
//        }
//
//        DEC_buf *pMem = &pUnit->decBufs.mems[i];
//
//        if( pMem->iBufSize<imgSize) {
//            myfree(pMem->pBuf);pMem->pBuf=NULL;
//        }
//
//        if (!pMem->pBuf) {
//            pMem->iBufSize=imgSize;
//            pMem->pBuf = (byte *) mymalloc(pMem->iBufSize);
//            if (!pMem->pBuf)goto errLabel;
//        }
//        p = pMem->pBuf;
//        //
//        /*
//        memcpy(p, picture->data[0], yLine);
//        memcpy(p + yLine, picture->data[1], yLine / 4);
//        memcpy(p + yLine + yLine / 4, picture->data[2], yLine / 4);
//         */
//        frame2Buf_a(pUnit->decA_var.c,frame,bytes_per_sample,p,fo);
//        //
//        if(bDbg){
//            LOGE((char*)"mySaveFrame: after frame2Buf");
//        }
//        //
//        pMem->len=imgSize;
//        //
//        pMem->bUsed = true;
//    }
//    else {
//        p=decBuf;
//        //
//        /*
//         memcpy(p,picture->data[0],yLine);
//         memcpy(p+yLine,picture->data[1],yLine/4);
//         memcpy(p+yLine+yLine/4,picture->data[2],yLine/4);
//         */
//        frame2Buf_a(pUnit->decA_var.c,frame,bytes_per_sample,p,fo);
//        //
//        *piDecBufSize=imgSize;
//
//        //
//        //fwrite(decBuf,imgSize,1,fo);
//    }
//
//    iErr = 0;
//    errLabel:
//    return iErr;
//}
//
//
//
////
//static int mydecodeA(int index_qdcUint, AVCodecContext *dec_ctx, AVPacket *pkt, AVFrame *frame,
//                      int *pnPktDeced, byte * decBuf, int *piDecBufSize, bool *pbBufTooSmall,
//                      FILE *outfile,
//                      bool bDbg )
//{
//    int iErr = -1;
//    int i, ch;
//    int ret, data_size;
//
//    //
//    if(bDbg){
//        LOGE((char*)"mydecodeA enters");
//    }
//
//    /* send the packet with the compressed data to the decoder */
//    ret = avcodec_send_packet(dec_ctx, pkt);
//    if (ret < 0) {
//        fprintf(stderr, "Error submitting the packet to the decoder\n");
//        //exit(1);
//        iErr = 0; goto errLabel;
//        //return 0;
//    }
//
//    /* read all the output frames (in general there may be any number of them */
//    while (ret >= 0) {
//        ret = avcodec_receive_frame(dec_ctx, frame);
//        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
//            iErr = 0; goto errLabel;
//            //return 0;
//        }
//        else if (ret < 0) {
//            fprintf(stderr, "Error during decoding\n");
//            goto errLabel;
//        }
//        data_size = av_get_bytes_per_sample(dec_ctx->sample_fmt);
//        if (data_size < 0) {
//            /* This should not occur, checking just for paranoia */
//            fprintf(stderr, "Failed to calculate data size\n");
//            goto errLabel;
//        }
//        /*
//        for (i = 0; i < frame->nb_samples; i++)
//            for (ch = 0; ch < dec_ctx->channels; ch++)
//                fwrite(frame->data[ch] + data_size*i, 1, data_size, outfile);
//                */
//        mysaveFrame_a(index_qdcUint,dec_ctx,frame,data_size,pnPktDeced,decBuf,piDecBufSize,pbBufTooSmall,outfile,bDbg);
//
//    }
//
//    iErr = 0;
//
//errLabel:
//    //
//    if(bDbg){
//        LOGE((char*)"mydecodeA leaves with %d",iErr);
//    }
//
//    return iErr;
//}



//
int decA_data_aac(int index_qdcUnit, byte * encData,int encData_size, int iInputBufferPaddingSize, int *pnPktDeced, int * piFmt_dec, byte * decBuf, int *piDecBufSize, bool *pbBufTooSmall, bool bDbg)
{
    int iErr = -1;
    QDC_AAC_unit *pUnit = getQdcAACUnitByIndex(index_qdcUnit);
    if (!pUnit) return -1;

    uint8_t *data;
    size_t   data_size;
    int ret;

    if ( !encData||!encData_size) {
        LOGE((char*)"decA_data failed, encData NULL or encData_size 0");
        return -1;
    }

    //
    if(encData_size+pUnit->decA_var.cache.len>pUnit->decA_var.cache.iBufSize){
        LOGE((char*)"decA_data failed, cache.iBufSize too small");
        return -1;
    }
    memcpy(pUnit->decA_var.cache.pBuf+pUnit->decA_var.cache.len,encData,encData_size);
    pUnit->decA_var.cache.len+=encData_size;

    //
    data=(uint8_t*)pUnit->decA_var.cache.pBuf;
    data_size=pUnit->decA_var.cache.len;

    while (data_size > 0) {
        UCHAR* inBuffer[1] = { data };
        UINT inBufferLength[1] = { data_size };
        UINT bytesValid = data_size;

        AAC_DECODER_ERROR err = aacDecoder_Fill(pUnit->decA_var.aacDecoder, inBuffer, inBufferLength, &bytesValid);
        if (err != AAC_DEC_OK) {
            goto errLabel;
        }
        else {

            data += data_size - bytesValid;
            data_size -= data_size - bytesValid;

            if (bytesValid > 0) {
               /* int j = 1;
                j++;*/

                memmove(pUnit->decA_var.cache.pBuf, data, data_size);                
            }

            pUnit->decA_var.cache.len = data_size;

            CStreamInfo* info = aacDecoder_GetStreamInfo(pUnit->decA_var.aacDecoder);
            if (info != nullptr) {
                //int bufLen = 1024 * 2;
                //INT_PCM* pcmBuffer = new INT_PCM[bufLen];

                int i;
                //
                for (i = 0; i < pUnit->decBufs.maxCnt_decBufMems; i++) {
                    DEC_buf_aac* pMem = &pUnit->decBufs.mems[i];
                    if (!pMem->bUsed) break;
                }
                if (i == pUnit->decBufs.maxCnt_decBufMems) {
                    LOGD((char*)"maxCnt_decBufMems too small");
                    goto errLabel;
                }

                DEC_buf_aac* pMem = &pUnit->decBufs.mems[i];

                if (pMem->pBuf == NULL) {
                    pMem->iBufSize = 1024 * 2;
                    pMem->pBuf = new INT_PCM[pMem->iBufSize];
                }              

                err = aacDecoder_DecodeFrame(pUnit->decA_var.aacDecoder, (INT_PCM*)pMem->pBuf, pMem->iBufSize, 0);
                if (err != AAC_DEC_OK) {               
                    goto errLabel;
                }

                pMem->bUsed = true;

                // 获取解码后的PCM信息
                CStreamInfo* streamInfo = aacDecoder_GetStreamInfo(pUnit->decA_var.aacDecoder);
                if (!streamInfo) {
                 
                }

                int samples = streamInfo->frameSize * streamInfo->numChannels;

                samples = samples;

                pMem->len = samples * 2;

//#ifdef  _DEBUG
//
//#if  10
//                static  bool  bClean = FALSE;
//                FILE* fp = NULL;
//                char* fn = "c:\\tttbbb\\kk2.pcm";
//                if (!bClean) {
//                    fp = fopen(fn, "wb");
//                    if (fp) {
//                        fclose(fp);  fp = NULL;
//                    }
//                    bClean = TRUE;
//                }
//                if (bClean) {
//                    fp = fopen(fn, "ab+");
//                    if (fp) {
//                        int elSize = sizeof(INT_PCM);
//                        //fwrite(pcmBuffer, elSize, samples, fp);
//                        fwrite(pcmBuffer, 1, samples * 2, fp);
//                        fclose(fp);  fp = NULL;
//                    }
//                }
//#endif
//
//#endif

              
            }
        }
    }

    //


    iErr = 0;
    errLabel:

    return iErr;
}


int decA_getOutputByIndexAAC(int index_qdcUnit, int index, byte* pbOutData, uint* puiDataSize, bool bDbg)
{
    int iErr = -1;
    QDC_AAC_unit* pUnit = getQdcAACUnitByIndex(index_qdcUnit);
    if (!pUnit) return -1;

    if (index < 0 || index >= pUnit->decBufs.maxCnt_decBufMems) return -1;
    DEC_buf_aac* pMem = &pUnit->decBufs.mems[index];
    if (!pMem->bUsed) return -1;

    if (*puiDataSize < pMem->len)return -1;
    memcpy(pbOutData, pMem->pBuf, pMem->len);
    *puiDataSize = pMem->len;
    pMem->bUsed = false;

    //
    return 0;
}
