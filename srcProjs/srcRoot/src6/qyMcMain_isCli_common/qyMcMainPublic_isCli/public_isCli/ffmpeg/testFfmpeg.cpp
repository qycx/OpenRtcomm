
#include	"stdafx.h"
#include	<tchar.h>
#include	<string>

//#include	"qyMcMainCommon.h"

extern "C"
{
#include "libavutil/opt.h"
#include "libavcodec/avcodec.h"
#include "libavutil/imgutils.h"

//#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"

};

//
int flush_encoder(AVFormatContext *fmt_ctx,unsigned int stream_index){
	int ret;
	int got_frame;
	AVPacket enc_pkt;
	if (!(fmt_ctx->streams[stream_index]->codec->codec->capabilities &
		AV_CODEC_CAP_DELAY))
		return 0;
	while (1) {
		enc_pkt.data = NULL;
		enc_pkt.size = 0;
		av_init_packet(&enc_pkt);
		ret = avcodec_encode_audio2 (fmt_ctx->streams[stream_index]->codec, &enc_pkt,
			NULL, &got_frame);
		av_frame_free(NULL);
		if (ret < 0)
			break;
		if (!got_frame){
			ret=0;
			break;
		}
		printf("Flush Encoder: Succeed to encode 1 frame!\tsize:%5d\n",enc_pkt.size);
		/* mux encoded frame */
		ret = av_write_frame(fmt_ctx, &enc_pkt);
		if (ret < 0)
			break;
	}
	return ret;
}


//
int testFfmpeg_main(int argc, char* argv[])
{
	AVFormatContext* pFormatCtx;
	AVOutputFormat* fmt;
	AVStream* audio_st;
	AVCodecContext* pCodecCtx;
	AVCodec* pCodec;

	uint8_t* frame_buf;
	AVFrame* pFrame;
	AVPacket pkt;

	int got_frame=0;
	int ret=0;
	int size=0;

	FILE *in_file=NULL;	                        //Raw PCM data
	int framenum=1000;                          //Audio frame number
	std::string out_file;
	int i;

	bool bAac=false;
	bool bUseDumpPcm=true;

	std::string testDir="c:\\tttbbb\\test\\";

	//char filename_in[]="tdjm.pcm";
	std::string filename_in=testDir + "tdjm.pcm";
	out_file = testDir+ "tdjm.aac";          //Output URL
	if ( bUseDumpPcm ){
		filename_in=testDir+"dump_pcm.pcm";
		out_file=testDir+"dump_pcm.aac";
		if(!bAac ) {
			out_file=testDir+"dump_pcm.mp3";
		}
	}


	in_file= fopen(filename_in.c_str(), "rb");

	av_register_all();

	//Method 1.
	pFormatCtx = avformat_alloc_context();
	fmt = av_guess_format(NULL, out_file.c_str(), NULL);
	pFormatCtx->oformat = fmt;


	//Method 2.
	//avformat_alloc_output_context2(&pFormatCtx, NULL, NULL, out_file);
	//fmt = pFormatCtx->oformat;

	//Open output URL
	if (avio_open(&pFormatCtx->pb,out_file.c_str(), AVIO_FLAG_READ_WRITE) < 0){
		printf("Failed to open output file!\n");
		return -1;
	}

	audio_st = avformat_new_stream(pFormatCtx, 0);
	if (audio_st==NULL){
		return -1;
	}
	pCodecCtx = audio_st->codec;
	pCodecCtx->codec_id = fmt->audio_codec;
	pCodecCtx->codec_type = AVMEDIA_TYPE_AUDIO;
	pCodecCtx->sample_fmt = AV_SAMPLE_FMT_S16;
	//
	pCodecCtx->sample_rate= 44100;
	pCodecCtx->channel_layout=AV_CH_LAYOUT_STEREO;
	pCodecCtx->channels = av_get_channel_layout_nb_channels(pCodecCtx->channel_layout);
	pCodecCtx->bit_rate = 64000;  

	//
	if(bUseDumpPcm){
		pCodecCtx->sample_rate=16000;
		pCodecCtx->channel_layout=AV_CH_LAYOUT_MONO;
		pCodecCtx->channels = av_get_channel_layout_nb_channels(pCodecCtx->channel_layout);
		pCodecCtx->bit_rate=4*pCodecCtx->sample_rate;
	}

	//Show some information
	av_dump_format(pFormatCtx, 0, out_file.c_str(), 1);

	pCodec = avcodec_find_encoder(pCodecCtx->codec_id);
	if (!pCodec){
		printf("Can not find encoder!\n");
		return -1;
	}
	if (avcodec_open2(pCodecCtx, pCodec,NULL) < 0){
		printf("Failed to open encoder!\n");
		return -1;
	}
	pFrame = av_frame_alloc();
	pFrame->nb_samples= pCodecCtx->frame_size;
	pFrame->format= pCodecCtx->sample_fmt;
	
	size = av_samples_get_buffer_size(NULL, pCodecCtx->channels,pCodecCtx->frame_size,pCodecCtx->sample_fmt, 1);
	frame_buf = (uint8_t *)av_malloc(size);
	avcodec_fill_audio_frame(pFrame, pCodecCtx->channels, pCodecCtx->sample_fmt,(const uint8_t*)frame_buf, size, 1);
	
	//Write Header
	avformat_write_header(pFormatCtx,NULL);

	av_new_packet(&pkt,size);

	for (i=0; i<framenum; i++){
		//Read PCM
		if (fread(frame_buf, 1, size, in_file) <= 0){
			printf("Failed to read raw data! \n");
			return -1;
		}else if(feof(in_file)){
			break;
		}
		pFrame->data[0] = frame_buf;  //PCM Data

		pFrame->pts=i*100;
		got_frame=0;
		//Encode
		ret = avcodec_encode_audio2(pCodecCtx, &pkt,pFrame, &got_frame);
		if(ret < 0){
			printf("Failed to encode!\n");
			return -1;
		}
		if (got_frame==1){
			printf("Succeed to encode 1 frame! \tsize:%5d\n",pkt.size);
			pkt.stream_index = audio_st->index;
			ret = av_write_frame(pFormatCtx, &pkt);
			//
			//fwrite(pkt.data, 1, pkt.size, fp_out);
			//
			av_free_packet(&pkt);
		}
	}
	
	//Flush Encoder
	ret = flush_encoder(pFormatCtx,0);
	if (ret < 0) {
		printf("Flushing encoder failed\n");
		return -1;
	}

	//Write Trailer
	av_write_trailer(pFormatCtx);

	//Clean
	if (audio_st){
		avcodec_close(audio_st->codec);
		av_free(pFrame);
		av_free(frame_buf);
	}
	avio_close(pFormatCtx->pb);
	avformat_free_context(pFormatCtx);

	fclose(in_file);

	return 0;
}




//
int testFfmpeg_main_pure(int argc, char* argv[])
{
	AVCodec *pCodec;
    AVCodecContext *pCodecCtx= NULL;
    int i, ret, got_output;
    FILE *fp_in;
	FILE *fp_out;

    AVFrame *pFrame;
	uint8_t* frame_buf;
	int size=0;

	AVPacket pkt;
	int y_size;
	int framecnt=0;

	//
	std::string testDir="c:\\tttbbb\\test\\";

	//char filename_in[]="tdjm.pcm";
	std::string filename_in=testDir + "tdjm.pcm";
	
	//
	bool bAac=false;
	//bAac=true;

	//
	bool bUseDumpPcm=false;
	if ( !bAac ) {
		bUseDumpPcm=true;
	}
	if(bUseDumpPcm){
		filename_in=testDir + "dump_pcm.pcm";
	}


	//
	AVCodecID codec_id=AV_CODEC_ID_MP3;//AV_CODEC_ID_AAC;
	std::string filename_out=testDir+"tdjm.mp3";//"tdjm.aac";
	if ( bAac){
		codec_id=AV_CODEC_ID_AAC;
		filename_out=testDir+"tdjm.aac";
	}
	if(bUseDumpPcm)
	{
		filename_out=testDir+"dumpPcm.mp3";
		if(bAac)filename_out=testDir+ "dumpPcm.aac";
	}
	 


	//
	int framenum=1000;	

	avcodec_register_all();

    pCodec = avcodec_find_encoder(codec_id);
    if (!pCodec) {
        printf("Codec not found\n");
        return -1;
    }
    pCodecCtx = avcodec_alloc_context3(pCodec);
    if (!pCodecCtx) {
        printf("Could not allocate video codec context\n");
        return -1;
    }

	pCodecCtx->codec_id = codec_id;
	pCodecCtx->codec_type = AVMEDIA_TYPE_AUDIO;
	pCodecCtx->sample_fmt = AV_SAMPLE_FMT_S16;
	if(!bUseDumpPcm){
		pCodecCtx->sample_rate= 44100;
		pCodecCtx->channel_layout=AV_CH_LAYOUT_STEREO;
	}
	else {
		pCodecCtx->sample_rate=16000;
		pCodecCtx->channel_layout=AV_CH_LAYOUT_MONO;
	}
	pCodecCtx->channels = av_get_channel_layout_nb_channels(pCodecCtx->channel_layout);
	pCodecCtx->bit_rate = 64000;  
	//
	if ( bUseDumpPcm ) {
		pCodecCtx->bit_rate=4*pCodecCtx->sample_rate;
	}

	//
    if ((ret=avcodec_open2(pCodecCtx, pCodec, NULL)) < 0) {
        printf("Could not open codec\n");
        return -1;
    }
    
	pFrame = av_frame_alloc();
	pFrame->nb_samples= pCodecCtx->frame_size;
	pFrame->format= pCodecCtx->sample_fmt;
	size = av_samples_get_buffer_size(NULL, pCodecCtx->channels,pCodecCtx->frame_size,pCodecCtx->sample_fmt, 1);
	frame_buf = (uint8_t *)av_malloc(size);
	avcodec_fill_audio_frame(pFrame, pCodecCtx->channels, pCodecCtx->sample_fmt,(const uint8_t*)frame_buf, size, 1);

	//Input raw data
	fp_in = fopen(filename_in.c_str(), "rb");
	if (!fp_in) {
		printf("Could not open %s\n", filename_in);
		return -1;
	}
	//Output bitstream
	fp_out = fopen(filename_out.c_str(), "wb");
	if (!fp_out) {
		printf("Could not open %s\n", filename_out);
		return -1;
	}

    //Encode
    for (i = 0; i < framenum; i++) {
        av_init_packet(&pkt);
        pkt.data = NULL;    // packet data will be allocated by the encoder
        pkt.size = 0;
		//Read raw data
		if (fread(frame_buf, 1, size, fp_in) <= 0){
			printf("Failed to read raw data! \n");
			return -1;
		}else if(feof(fp_in)){
			break;
		}

        pFrame->pts = i;
        ret = avcodec_encode_audio2(pCodecCtx, &pkt, pFrame, &got_output);
        if (ret < 0) {
            printf("Error encoding frame\n");
            return -1;
        }
        if (got_output) {
            printf("Succeed to encode frame: %5d\tsize:%5d\n",framecnt,pkt.size);
			framecnt++;
            fwrite(pkt.data, 1, pkt.size, fp_out);
            av_free_packet(&pkt);
        }
    }
    //Flush Encoder
    for (got_output = 1; got_output; i++) {
        ret = avcodec_encode_audio2(pCodecCtx, &pkt, NULL, &got_output);
        if (ret < 0) {
            printf("Error encoding frame\n");
            return -1;
        }
        if (got_output) {
            printf("Flush Encoder: Succeed to encode 1 frame!\tsize:%5d\n",pkt.size);
            fwrite(pkt.data, 1, pkt.size, fp_out);
            av_free_packet(&pkt);
        }
    }

    fclose(fp_out);
    avcodec_close(pCodecCtx);
    av_free(pCodecCtx);
    av_freep(&pFrame->data[0]);
    av_frame_free(&pFrame);

	return 0;
}
