

#include	"stdafx.h"
#include	<tchar.h>
#include	<string>

#include	"qyMcMainCommon.h"
#include	"dumpAudio.h"

extern "C"
{
#include "libavutil/opt.h"
#include "libavcodec/avcodec.h"
#include "libavutil/imgutils.h"

//#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"

};

struct __dumpA {

	AVFormatContext* pFormatCtx;
	AVOutputFormat* fmt;
	AVStream* audio_st;
	AVCodecContext* pCodecCtx;
	AVCodec* pCodec;

	uint8_t* frame_buf;
	AVFrame* pFrame;

}		g_dumpA;
bool g_bInited_dumpA=false;



int dumpAudio_init()
{
	if(g_bInited_dumpA) return -1;

		int got_frame=0;
	int ret=0;
	int size=0;


	std::string testDir="c:\\tttbbb\\test\\";

	//char filename_in[]="tdjm.pcm";
	std::string filename_in=testDir + "tdjm.pcm";
	std::string out_file;
	out_file = testDir+ "tdjm.aac";          //Output URL


	bool bAac=false;
	bool bUseDumpPcm=true;

	//
	if ( bUseDumpPcm ){
		filename_in=testDir+"dump_pcm.pcm";
		out_file=testDir+"dump_pcm.aac";
		if(!bAac ) {
			out_file=testDir+"dump_pcm.mp3";
		}
	}



	av_register_all();

	//Method 1.
	g_dumpA.pFormatCtx = avformat_alloc_context();
	g_dumpA.fmt = av_guess_format(NULL, out_file.c_str(), NULL);
	g_dumpA.pFormatCtx->oformat = g_dumpA.fmt;


	//Method 2.
	//avformat_alloc_output_context2(&pFormatCtx, NULL, NULL, out_file);
	//fmt = pFormatCtx->oformat;

	//Open output URL
	if (avio_open(&g_dumpA.pFormatCtx->pb,out_file.c_str(), AVIO_FLAG_READ_WRITE) < 0){
		printf("Failed to open output file!\n");
		return -1;
	}

	g_dumpA.audio_st = avformat_new_stream(g_dumpA.pFormatCtx, 0);
	if (g_dumpA.audio_st==NULL){
		return -1;
	}
	g_dumpA.pCodecCtx = g_dumpA.audio_st->codec;
	g_dumpA.pCodecCtx->codec_id = g_dumpA.fmt->audio_codec;
	g_dumpA.pCodecCtx->codec_type = AVMEDIA_TYPE_AUDIO;
	g_dumpA.pCodecCtx->sample_fmt = AV_SAMPLE_FMT_S16;
	//
	g_dumpA.pCodecCtx->sample_rate= 44100;
	g_dumpA.pCodecCtx->channel_layout=AV_CH_LAYOUT_STEREO;
	g_dumpA.pCodecCtx->channels = av_get_channel_layout_nb_channels(g_dumpA.pCodecCtx->channel_layout);
	g_dumpA.pCodecCtx->bit_rate = 64000;  

	//
	if(bUseDumpPcm){
		g_dumpA.pCodecCtx->sample_rate=16000;
		g_dumpA.pCodecCtx->channel_layout=AV_CH_LAYOUT_MONO;
		g_dumpA.pCodecCtx->channels = av_get_channel_layout_nb_channels(g_dumpA.pCodecCtx->channel_layout);
		g_dumpA.pCodecCtx->bit_rate=4*g_dumpA.pCodecCtx->sample_rate;
	}

	//Show some information
	av_dump_format(g_dumpA.pFormatCtx, 0, out_file.c_str(), 1);

	g_dumpA.pCodec = avcodec_find_encoder(g_dumpA.pCodecCtx->codec_id);
	if (!g_dumpA.pCodec){
		printf("Can not find encoder!\n");
		return -1;
	}
	if (avcodec_open2(g_dumpA.pCodecCtx, g_dumpA.pCodec,NULL) < 0){
		printf("Failed to open encoder!\n");
		return -1;
	}
	g_dumpA.pFrame = av_frame_alloc();
	g_dumpA.pFrame->nb_samples= g_dumpA.pCodecCtx->frame_size;
	g_dumpA.pFrame->format= g_dumpA.pCodecCtx->sample_fmt;
	
	size = av_samples_get_buffer_size(NULL, g_dumpA.pCodecCtx->channels,g_dumpA.pCodecCtx->frame_size,g_dumpA.pCodecCtx->sample_fmt, 1);
	g_dumpA.frame_buf = (uint8_t *)av_malloc(size);
	avcodec_fill_audio_frame(g_dumpA.pFrame, g_dumpA.pCodecCtx->channels, g_dumpA.pCodecCtx->sample_fmt,(const uint8_t*)g_dumpA.frame_buf, size, 1);
	
	//Write Header
	avformat_write_header(g_dumpA.pFormatCtx,NULL);
	
	g_bInited_dumpA=true;

	return 0;
}

int dumpAudio_exit()
{
	if(!g_bInited_dumpA)return -1;

	av_write_trailer(g_dumpA.pFormatCtx);

	//Clean
	if (g_dumpA.audio_st){
		avcodec_close(g_dumpA.audio_st->codec);
		av_free(g_dumpA.pFrame);
		av_free(g_dumpA.frame_buf);
	}
	avio_close(g_dumpA.pFormatCtx->pb);
	avformat_free_context(g_dumpA.pFormatCtx);

	//fclose(in_file);

	g_bInited_dumpA=false;

	return 0;
	//

}


int dumpAudio(char * data,int size)
{
	AVPacket pkt;

	if ( !data ||!size ) {
		return -1;
	}

	av_init_packet(&pkt);
	pkt.data=(uint8_t*)data;
	pkt.size=size;

	int ret;
	ret = av_write_frame(g_dumpA.pFormatCtx, &pkt);


	return 0;
}






