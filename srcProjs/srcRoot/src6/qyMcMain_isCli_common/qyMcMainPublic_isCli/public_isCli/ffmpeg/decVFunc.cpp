
#include	"stdafx.h"
#include "tmpFfmpegCommon.h"


//
int decV_init(int index_qdcUnit, int iFourcc, bool bUseNv, bool bDbg)
{
    int iErr = -1;
    QDC_unit *pUnit = getQdcUnitByIndex(index_qdcUnit);
    if (!pUnit) return -1;

    AVCodecID codec_id = AV_CODEC_ID_H264;

    if (!g_qdc.bDone_qdc_init) return -1;

	//
	AVCodecID codecId;

    //
    pUnit->decV_var.iFourcc = iFourcc;
    switch (iFourcc) {
        case CONST_fourcc_h264:
			codecId  =  AV_CODEC_ID_H264;
            break;
		case  CONST_fourcc_MJPG:
			codecId  =  AV_CODEC_ID_MJPEG;
			  break;
        default:
            return -1;
    }

    //
    //
    pUnit->decV_var.pkt = av_packet_alloc();
    if (!pUnit->decV_var.pkt) {
        goto errLabel;
    }

    /* set end of buffer to 0 (this ensures that no overreading happens for damaged MPEG streams) */
    //memset(inbuf + INBUF_SIZE, 0, AV_INPUT_BUFFER_PADDING_SIZE);

    /* find the MPEG-1 video decoder */
		if ( bUseNv  )  {
		#define NVIDIA_H264_DECODER "h264_cuvid"
		//
		//av_register_all();
		//
		
	
		pUnit->decV_var.codec=avcodec_find_decoder_by_name(NVIDIA_H264_DECODER );
		
		}
	else {

    pUnit->decV_var.codec = avcodec_find_decoder(codecId);//AV_CODEC_ID_H264);
	}
    if (!pUnit->decV_var.codec) {
        fprintf(stderr, "Codec not found\n");
        goto errLabel;
    }

    pUnit->decV_var.parser = av_parser_init(pUnit->decV_var.codec->id);
    if (!pUnit->decV_var.parser) {
        fprintf(stderr, "parser not found\n");
        goto errLabel;
    }

    pUnit->decV_var.c = avcodec_alloc_context3(pUnit->decV_var.codec);
    if (!pUnit->decV_var.c) {
        fprintf(stderr, "Could not allocate video codec context\n");
        goto errLabel;
    }

    /* For some codecs, such as msmpeg4 and mpeg4, width and height
       MUST be initialized there because this information is not
       available in the bitstream. */

    /* open it */
    if (avcodec_open2(pUnit->decV_var.c, pUnit->decV_var.codec, NULL) < 0) {
        fprintf(stderr, "Could not open codec\n");
        goto errLabel;
    }

    //
    pUnit->decV_var.frame = av_frame_alloc();
    if (!pUnit->decV_var.frame) {
        fprintf(stderr, "Could not allocate video frame\n");
        goto errLabel;
    }


    //
    pUnit->decBufs.maxCnt_decBufMems=CONST_cntof_decBuf_mems_v;



    iErr = 0;
    errLabel:
        if ( iErr ){
            decV_exit(index_qdcUnit,bDbg);
        }
    return iErr;
}

int decV_exit(int index_qdcUnit,bool bDbg)
{
    int iErr = -1;
    QDC_unit *pUnit = getQdcUnitByIndex(index_qdcUnit);
    if (!pUnit) return -1;

    //
    freeDecBufs(index_qdcUnit);

    //
    av_parser_close(pUnit->decV_var.parser);
    avcodec_free_context(&pUnit->decV_var.c);
    av_frame_free(&pUnit->decV_var.frame);
    av_packet_free(&pUnit->decV_var.pkt);

	//
	if  (  pUnit->decV_var.bInited_dst  )  {
		av_freep(&pUnit->decV_var.dst_data[0]);
	}
	if  (  pUnit->decV_var.sws_ctx  )  {
		sws_freeContext(pUnit->decV_var.sws_ctx);
	}

	//
    iErr = 0;
    errLabl:
    return iErr;
}

#if  0
static AVFrame *alloc_picture(enum AVPixelFormat pix_fmt, int width, int height)
{
    AVFrame *picture;
    int ret;

    picture = av_frame_alloc();
    if (!picture)
        return NULL;

    picture->format = pix_fmt;
    picture->width  = width;
    picture->height = height;

    /* allocate the buffers for the frame data */
    ret = av_frame_get_buffer(picture, 0);
    if (ret < 0) {
        fprintf(stderr, "Could not allocate frame data.\n");
        //exit(1);
		showInfo_open0(  0,  0,  _T(  "Could not allocate frame data"  )  );
		return  NULL;
    }

    return picture;
}
#endif


//
int frame2Buf_v(int index_qdcUnit,  AVCodecContext*c,AVFrame * frame, byte * yuv,int w,int h)
{
	int  iErr  =  -1;
	QDC_unit *pUnit = getQdcUnitByIndex(index_qdcUnit);
    if (!pUnit) return -1;

	//
	if  (  pUnit->decV_var.c->pix_fmt  !=  AV_PIX_FMT_YUV420P  )  {

			int  src_w  =  w;
			int  src_h  =  h;
			enum AVPixelFormat src_pix_fmt  =  c->pix_fmt;
			int  dst_w  =  w;
			int  dst_h  =  h;
			enum AVPixelFormat dst_pix_fmt  =  AV_PIX_FMT_YUV420P;

		//
		if  (  !pUnit->decV_var.sws_ctx  )  {
					    /* create scaling context */
			pUnit->decV_var.sws_ctx  = sws_getContext(src_w, src_h, src_pix_fmt,
                             dst_w, dst_h, dst_pix_fmt,
                             SWS_BILINEAR, NULL, NULL, NULL);
			if  (  !pUnit->decV_var.sws_ctx  )  {
				goto  errLabel;
			}
		}
		//
		if  (  !pUnit->decV_var.bInited_dst  )  {
			    /* buffer is going to be written to rawvideo file, no alignment */
			int  ret;
			if ((ret = av_image_alloc(pUnit->decV_var.dst_data, pUnit->decV_var.dst_linesize,
                              dst_w, dst_h, dst_pix_fmt, 1)) < 0) {
				fprintf(stderr, "Could not allocate destination image\n");
				goto errLabel;
			}
			pUnit->decV_var.dst_bufsize = ret;
			//
			pUnit->decV_var.bInited_dst  =  true;
		}
		//
		sws_scale(pUnit->decV_var.sws_ctx, (const uint8_t * const *) frame->data,
			frame->linesize, 0, c->height, pUnit->decV_var.dst_data,
			pUnit->decV_var.dst_linesize);
		//
		memcpy(  yuv,  pUnit->decV_var.dst_data[0],  pUnit->decV_var.dst_bufsize  );

		}
	else  {


	//
    int y;
	//
    int y_size,u_size,v_size;
    y_size = c->width * c->height;
    u_size=y_size/4;
    v_size=y_size/4;

    for ( y=0;y<c->height;y++){
        memcpy(yuv+y*c->width,frame->data[0]+y*frame->linesize[0], c->width);
    }

    for ( y=0;y<c->height/2;y++) {
        memcpy(yuv+y_size+y*c->width/2,frame->data[1]+y*frame->linesize[1],c->width/2);
        memcpy(yuv+y_size+u_size+y*c->width/2,frame->data[2]+y*frame->linesize[2],c->width/2);
    }

	}

	//
	iErr  =  0;

errLabel:

    return iErr;
}

//
int mysaveFrame_v(int index_qdcUnit, AVFrame * picture,int w,int h,
                int *pnPktDeced,
                byte * decBuf, int *piDecBufSize, bool *pbBufTooSmall,
                FILE * fo,
                bool bDbg)
{
    int iErr = -1;
    QDC_unit *pUnit = getQdcUnitByIndex(index_qdcUnit);
    if (!pUnit) return -1;

    //
    int yLine=w*h;
    byte * p;

    /*
    fwrite(picture->data[0],yLine,1,fo);
    fwrite(picture->data[1],yLine/4,1,fo);
    fwrite(picture->data[2],yLine/4,1,fo);
     */
    (*pnPktDeced)++;


    //
    int imgSize=w*h*3/2;
    if ( decBuf==NULL || imgSize>*piDecBufSize) {
        *pbBufTooSmall=true;
    }


    if ( *pbBufTooSmall||*pnPktDeced>1) {
        int i;
        //
        for (i = 0; i < pUnit->decBufs.maxCnt_decBufMems; i++) {
            DEC_buf *pMem = &pUnit->decBufs.mems[i];
            if (!pMem->bUsed) break;
        }
        if (i == pUnit->decBufs.maxCnt_decBufMems) {
            LOGD((char*)"maxCnt_decBufMems too small");
            goto errLabel;
        }

        DEC_buf *pMem = &pUnit->decBufs.mems[i];

        if( pMem->iBufSize<imgSize) {
            myfree(pMem->pBuf);pMem->pBuf=NULL;
        }

        if (!pMem->pBuf) {
            pMem->iBufSize=imgSize;
            pMem->pBuf = (byte *) mymalloc(pMem->iBufSize);
            if (!pMem->pBuf)goto errLabel;
        }
        p = pMem->pBuf;
        //
        /*
        memcpy(p, picture->data[0], yLine);
        memcpy(p + yLine, picture->data[1], yLine / 4);
        memcpy(p + yLine + yLine / 4, picture->data[2], yLine / 4);
         */
        frame2Buf_v(index_qdcUnit,  pUnit->decV_var.c,picture,p,w,h);
        //
        if(bDbg){
            LOGE((char*)"mySaveFrame_v: after frame2Buf_v");
        }
        //
        pMem->len=imgSize;
        //
        pMem->bUsed = true;
        }
    else {
        p=decBuf;
        //
        /*
         memcpy(p,picture->data[0],yLine);
         memcpy(p+yLine,picture->data[1],yLine/4);
         memcpy(p+yLine+yLine/4,picture->data[2],yLine/4);
         */
        frame2Buf_v(index_qdcUnit,  pUnit->decV_var.c,picture,p,w,h);
         //
         *piDecBufSize=imgSize;

         //
         //fwrite(decBuf,imgSize,1,fo);
    }

    iErr = 0;
    errLabel:
    return iErr;
}



//
static int mydecodeV(int index_qdcUint, AVCodecContext *dec_ctx, AVFrame *frame, AVPacket *pkt,
                    int *pnPktDeced, byte * decBuf, int *piDecBufSize, bool *pbBufTooSmall,
                   FILE * fo,
                   bool bDbg)
{
    int iErr = -1;
    char buf[1024];
    int ret;

    ret = avcodec_send_packet(dec_ctx, pkt);
    if (ret < 0) {
        fprintf(stderr, "Error sending a packet for decoding\n");
        //exit(1);
        goto errLabel;
    }

    while (ret >= 0) {
        ret = avcodec_receive_frame(dec_ctx, frame);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
            //return;
            break;
        }
        else if (ret < 0) {
            fprintf(stderr, "Error during decoding\n");
            //exit(1);
            goto errLabel;
        }

        //printf("saving frame %3d\n", dec_ctx->frame_number);
        //fflush(stdout);

        /* the picture is allocated by the decoder. no need to
           free it */
        //snprintf(buf, sizeof(buf), "%s-%d", filename, dec_ctx->frame_number);
        //pgm_save(frame->data[0], frame->linesize[0],   frame->width, frame->height, buf);
        mysaveFrame_v(index_qdcUint,  frame,dec_ctx->width,dec_ctx->height,pnPktDeced,decBuf, piDecBufSize,pbBufTooSmall, fo,bDbg);
    }

    iErr = 0;
    errLabel:
    return iErr;
}


int decV_data(int index_qdcUnit, byte * data,int data_size, int iInputBufferPaddingSize, int *pnPktDeced, int * piFourcc_dec, int *piW,int *piH, byte * decBuf, int *piDecBufSize, bool *pbBufTooSmall, bool bDbg)
{
    int iErr = -1;
    QDC_unit *pUnit = getQdcUnitByIndex(index_qdcUnit);
    if (!pUnit) return -1;
    int ret;
    int nPktDeced=0;

    if (iInputBufferPaddingSize<AV_INPUT_BUFFER_PADDING_SIZE) return -1;
    if (
     !pnPktDeced
    ||!piFourcc_dec
    || !piW
    || !piH
    || !pbBufTooSmall
    )
    {
        return -1;
    }


    //
    //data_size = fread(inbuf, 1, INBUF_SIZE, f);
    if (!data_size) {
        if ( mydecodeV(index_qdcUnit,  pUnit->decV_var.c, pUnit->decV_var.frame, NULL, &nPktDeced, decBuf,piDecBufSize,pbBufTooSmall,pUnit->decV_var.fo,bDbg) ) {
            goto errLabel;
        }
        iErr = 0; goto errLabel;
    }

    /* use the parser to split the data into frames */
    //data = inbuf;
    while (data_size > 0) {
        ret = av_parser_parse2(pUnit->decV_var.parser, pUnit->decV_var.c, &pUnit->decV_var.pkt->data, &pUnit->decV_var.pkt->size,
                               data, data_size, AV_NOPTS_VALUE, AV_NOPTS_VALUE, 0);
        if (ret < 0) {
            fprintf(stderr, "Error while parsing\n");
            //exit(1);
            goto errLabel;
        }
        data      += ret;
        data_size -= ret;

        if (pUnit->decV_var.pkt->size) {
            if ( mydecodeV(index_qdcUnit,  pUnit->decV_var.c, pUnit->decV_var.frame, pUnit->decV_var.pkt, &nPktDeced,decBuf,piDecBufSize,pbBufTooSmall,pUnit->decV_var.fo,bDbg) ) {
                goto errLabel;
            }
        }
    }

    //
    if (nPktDeced>0) {
        int iFourcc_dec;
		//
        switch (pUnit->decV_var.c->pix_fmt) {
            case AV_PIX_FMT_YUV420P:
                iFourcc_dec = CONST_fourcc_I420;
                break;
            default:
				iFourcc_dec = CONST_fourcc_I420;
				break;
        }
		//
        if (*piFourcc_dec != iFourcc_dec) *piFourcc_dec = iFourcc_dec;
        if (*piW != pUnit->decV_var.c->width)*piW = pUnit->decV_var.c->width;
        if (*piH != pUnit->decV_var.c->height)*piH = pUnit->decV_var.c->height;
    }

    iErr = 0;
    errLabel:

        if ( !iErr){
            *pnPktDeced=nPktDeced;
        }
    return iErr;
}

//
 int decV_getOutputByIndex(int index_qdcUnit, int index, byte * pbOutData, uint * puiDataSize,bool bDbg)
{
    int iErr = -1;
    QDC_unit *pUnit = getQdcUnitByIndex(index_qdcUnit);
    if (!pUnit) return -1;

    if ( index <0||index >=pUnit->decBufs.maxCnt_decBufMems) return -1;
    DEC_buf  *pMem=&pUnit->decBufs.mems[index];
    if ( !pMem->bUsed) return -1;

    if ( *puiDataSize<pMem->len)return -1;
    memcpy(pbOutData,pMem->pBuf,pMem->len);
    *puiDataSize=pMem->len;
    pMem->bUsed=false;

    //
    return 0;
}

 int decV_clearOutputs(int index_qdcUnit,bool bDbg)
 {
     int iErr = -1;
     QDC_unit *pUnit = getQdcUnitByIndex(index_qdcUnit);
     if (!pUnit) return -1;

     int i;
     for ( i=0;i<pUnit->decBufs.maxCnt_decBufMems;i++){
         DEC_buf  *pMem=&pUnit->decBufs.mems[i];
         if(pMem->bUsed ) {
             pMem->bUsed=false;
         }
     }

     return 0;
 }


