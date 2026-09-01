
#include	"stdafx.h"
#include	"tmpFfmpegCommon.h"


	 
//
typedef  struct  __ctx_resample_t  {

	__int64  src_ch_layout;
	int src_rate;
	int src_sample_fmt;
	//
	int src_nb_samples;
	//
	__int64  dst_ch_layout;
	int  dst_rate;
	int  dst_sample_fmt;

	//	
	struct SwrContext *swr_ctx;
	//
    int src_nb_channels;
	int dst_nb_channels;
	//
	uint8_t **src_data;
	uint8_t **dst_data;
	//
    int src_linesize, dst_linesize;
	//
    int dst_nb_samples, max_dst_nb_samples;

	
}		  CTX_resample;



int  initResample(  	__int64  src_ch_layout, int src_rate, int src_sample_fmt, int src_nb_samples,  __int64  dst_ch_layout,  int  dst_rate,  int  dst_sample_fmt,  void  **  ppCtx  )
{
		 int  iErr  =  -1;

		 if (  !ppCtx  )  return  -1;

		 CTX_resample  *  pCtx  =  (  CTX_resample  *  )mymalloc(  sizeof(  CTX_resample  )  );
		 if  (  pCtx  ==  NULL  )  return -1;
		 memset(  pCtx,  0,  sizeof(  pCtx  )  );

		 pCtx->src_ch_layout  =  src_ch_layout;
		 pCtx->src_rate  =  src_rate;
		 pCtx->src_sample_fmt  =  src_sample_fmt;
		 //
		 pCtx->src_nb_samples  =  src_nb_samples;
		 //
		 pCtx->dst_ch_layout  =  dst_ch_layout;
		 pCtx->dst_rate  =  dst_rate;
		 pCtx->dst_sample_fmt  =  dst_sample_fmt;
		 
		 /*
		     int64_t src_ch_layout = AV_CH_LAYOUT_STEREO, dst_ch_layout = AV_CH_LAYOUT_SURROUND;
    int src_rate = 48000, dst_rate = 44100;
	*/
	/*
    int src_nb_samples = 1024, dst_nb_samples, max_dst_nb_samples;
    enum AVSampleFormat src_sample_fmt = AV_SAMPLE_FMT_DBL, dst_sample_fmt = AV_SAMPLE_FMT_S16;
    const char *dst_filename = NULL;
    FILE *dst_file;
    int dst_bufsize;
    const char *fmt;
    double t;
*/
    int ret;


		 //
		     /* create resampler context */
    pCtx->swr_ctx = swr_alloc();
    if (!pCtx->swr_ctx) {
        fprintf(stderr, "Could not allocate resampler context\n");
        ret = AVERROR(ENOMEM);
        goto end;
    }
	//
    struct SwrContext* swr_ctx; swr_ctx = pCtx->swr_ctx;


    /* set options */
    av_opt_set_int(swr_ctx, "in_channel_layout",    src_ch_layout, 0);
    av_opt_set_int(swr_ctx, "in_sample_rate",       src_rate, 0);
    av_opt_set_sample_fmt(swr_ctx, "in_sample_fmt", (AVSampleFormat)src_sample_fmt, 0);

    av_opt_set_int(swr_ctx, "out_channel_layout",    dst_ch_layout, 0);
    av_opt_set_int(swr_ctx, "out_sample_rate",       dst_rate, 0);
    av_opt_set_sample_fmt(swr_ctx, "out_sample_fmt", (AVSampleFormat)dst_sample_fmt, 0);

    /* initialize the resampling context */
    if ((ret = swr_init(swr_ctx)) < 0) {
        fprintf(stderr, "Failed to initialize the resampling context\n");
        goto end;
    }

    /* allocate source and destination samples buffers */

    pCtx->src_nb_channels = av_get_channel_layout_nb_channels(src_ch_layout);
    ret = av_samples_alloc_array_and_samples(&pCtx->src_data, &pCtx->src_linesize, pCtx->src_nb_channels,
                                             src_nb_samples, (AVSampleFormat)src_sample_fmt, 0);
    if (ret < 0) {
        fprintf(stderr, "Could not allocate source samples\n");
        goto end;
    }

    /* compute the number of converted samples: buffering is avoided
     * ensuring that the output buffer will contain at least all the
     * converted input samples */
    pCtx->max_dst_nb_samples = pCtx->dst_nb_samples =
        av_rescale_rnd(src_nb_samples, dst_rate, src_rate, AV_ROUND_UP);

    /* buffer is going to be directly written to a rawaudio file, no alignment */
    pCtx->dst_nb_channels = av_get_channel_layout_nb_channels(dst_ch_layout);
    ret = av_samples_alloc_array_and_samples(&pCtx->dst_data, &pCtx->dst_linesize, pCtx->dst_nb_channels,
                                             pCtx->dst_nb_samples, (AVSampleFormat)dst_sample_fmt, 0);
    if (ret < 0) {
        fprintf(stderr, "Could not allocate destination samples\n");
        goto end;
    }
	
	
	//	
	*ppCtx  =  pCtx;  pCtx  =  NULL;

	//	
	iErr  =  0;

end:
errLabel:

		 if  (  pCtx  )  {
			 exitResample(  pCtx  );
		 }

		 return  iErr;
}

 int  exitResample(  void  *  pCtxParam  )
 {
	 if (  pCtxParam  ==  NULL  )  return  0;
	 CTX_resample  *  pCtx = (  CTX_resample *  )pCtxParam;

	 	//
    if (pCtx->src_data)
        av_freep(&pCtx->src_data[0]);
    av_freep(&pCtx->src_data);

    if (pCtx->dst_data)
        av_freep(&pCtx->dst_data[0]);
    av_freep(&pCtx->dst_data);

    swr_free(&pCtx->swr_ctx);


	 myfree(  pCtx  );

	 return  0;
 }


 int  doResample(  void  *  pCtxParam,  char  *  pInput,  int  inputLen,  char  *  pOutput,  int  *  pOutputSize  )
 {
	 int  iErr  = -1;
	 CTX_resample  *  pCtx  =  (  CTX_resample  *  )pCtxParam;
	 int  ret;

	 int  i;
	 for  (  i  =  0;  i  <  1;  i  ++  )
	 {
        /* generate synthetic audio */
        //fill_samples((double *)src_data[0], src_nb_samples, src_nb_channels, src_rate, &t);
		int src_bufsize=av_samples_get_buffer_size(NULL,pCtx->src_nb_channels,pCtx->src_nb_samples,(AVSampleFormat)pCtx->src_sample_fmt,1);
		if(  src_bufsize  !=  inputLen  )  {
			return  -1;
		}
		//if(1!=fread(src_data[0],src_bufsize,1,src_file))break;
		memcpy(  pCtx->src_data[0],  pInput,  src_bufsize  );

        /* compute destination number of samples */
        pCtx->dst_nb_samples = av_rescale_rnd(swr_get_delay(pCtx->swr_ctx, pCtx->src_rate) +
                                        pCtx->src_nb_samples, pCtx->dst_rate, pCtx->src_rate, AV_ROUND_UP);
        if (pCtx->dst_nb_samples > pCtx->max_dst_nb_samples) {
            av_freep(&pCtx->dst_data[0]);
            ret = av_samples_alloc(pCtx->dst_data, &pCtx->dst_linesize, pCtx->dst_nb_channels,
                                   pCtx->dst_nb_samples, (AVSampleFormat)pCtx->dst_sample_fmt, 1);
            if (ret < 0)
                break;
            pCtx->max_dst_nb_samples = pCtx->dst_nb_samples;
        }

        /* convert to destination format */
        ret = swr_convert(pCtx->swr_ctx, pCtx->dst_data, pCtx->dst_nb_samples, (const uint8_t **)pCtx->src_data, pCtx->src_nb_samples);
        if (ret < 0) {
            fprintf(stderr, "Error while converting\n");
            goto end;
        }
        int  dst_bufsize = av_samples_get_buffer_size(&pCtx->dst_linesize, pCtx->dst_nb_channels,
                                                 ret, (AVSampleFormat)pCtx->dst_sample_fmt, 1);
        if (dst_bufsize < 0) {
            fprintf(stderr, "Could not get sample buffer size\n");
            goto end;
        }
        //printf("t:%f in:%d out:%d\n", t, src_nb_samples, ret);
        //fwrite(dst_data[0], 1, dst_bufsize, dst_file);
		if  (  dst_bufsize  >  *pOutputSize  )  {
			goto  errLabel;
		}
		memcpy(  pOutput,  pCtx->dst_data[0],  dst_bufsize  );
		*pOutputSize  =  dst_bufsize;

		//
		iErr  =  0;  break;
    }
	 	 
end:
errLabel:

	 return  iErr;
 }


