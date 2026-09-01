// streamProc_readAndSave.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#ifndef  __STDC_CONSTANT_MACROS
#define	 __STDC_CONSTANT_MACROS
#endif

extern  "C"  {
#include "libavcodec\avcodec.h"
#include "libavformat\avformat.h"
#include "libswscale\swscale.h"
};
void SaveFrame(  AVFrame  *  pFrame,  int width,  int height,  int iFrame  )
{
	FILE  *  pFile;
	char	szFilename[32];
	int		y;

	//  open
	sprintf(  szFilename,  "frame%d.ppm",  iFrame  );
	pFile  =  fopen(  szFilename,  "wb"  );
	if  (  pFile  ==  NULL  )  return;

	//  write  header
	fprintf(  pFile,  "P6\n%d  %d\n255\n",  width,  height  );

	//  write  pixel data
	for(  y  =  0;  y  <  height;  y  ++  )
		fwrite(  pFrame->data[0]  +  y  *  pFrame->linesize[0],  1,  width  *  3,  pFile  );


	fclose(  pFile  );
}



int tmp_readAndSave(int argc, char * argv[])
{
	AVFormatContext		*	pFormatCtx  =  avformat_alloc_context();
	int						i,  videoStream;
	AVCodecContext		*	pCodecCtx;
	AVCodec				*	pCodec;
	AVFrame				*	pFrame;
	AVFrame				*	pFrameRGB;
	AVPacket				packet;
	int						frameFinished;
	int						numBytes;
	uint8_t				*	buffer;
	struct	SwsContext	*	ctx;

	if  (  argc  <  2  )  {
		printf(  "Please provide a movie file\n"  );
		return  -1;
	}

	av_register_all();

	if  (  avformat_open_input(  &pFormatCtx,  argv[1],  NULL,  NULL  )  !=  0  )
		return  -1;

	if  (  avformat_find_stream_info(  pFormatCtx, NULL)  <  0  )
		return  -1;

	av_dump_format(  pFormatCtx,  0,  argv[1],  0  );

	//  Find the first video frame
	videoStream  =  -1;
	for  (  i = 0; i < (int)pFormatCtx->nb_streams;  i ++  )
		if  (  pFormatCtx->streams[i]->codec->codec_type  ==  AVMEDIA_TYPE_VIDEO  )  {
			videoStream  =  i;
			break;
		}

	if  (  videoStream  ==  -1  )  return  -1;
	pCodecCtx = pFormatCtx->streams[videoStream]->codec;

	pCodec  =  avcodec_find_decoder( pCodecCtx->codec_id  );
	if  (  pCodec  ==  NULL  )  {
		fprintf(  stderr,  "unsupported codec !\n"  );
		return  -1;
	}

	if  (  avcodec_open2(  pCodecCtx,  pCodec,  NULL  )  <  0  )  return  -1;

	pFrame = av_frame_alloc();//avcodec_alloc_frame();

	pFrameRGB  = av_frame_alloc(); //avcodec_alloc_frame();
	if  (  pFrameRGB  ==  NULL  )  return  -1;

	numBytes  =  avpicture_get_size(  AV_PIX_FMT_RGB24,  pCodecCtx->width,  pCodecCtx->height  );
	buffer  =  (  uint8_t  *  )av_malloc(  numBytes * sizeof(  uint8_t  )  );

	avpicture_fill( ( AVPicture  *  )pFrameRGB,  buffer,  AV_PIX_FMT_RGB24,  pCodecCtx->width,  pCodecCtx->height  );

	i  =  0;
	while(  av_read_frame(  pFormatCtx,  &packet  )  >=  0  )  {
		if  (  packet.stream_index  ==  videoStream  )  {
			avcodec_decode_video2(  pCodecCtx,  pFrame,  &frameFinished,  &packet  );

			if  (  frameFinished  )  {
				ctx  =  sws_getContext(  pCodecCtx->width,  pCodecCtx->height,  pCodecCtx->pix_fmt,  pCodecCtx->width,  pCodecCtx->height,  AV_PIX_FMT_RGB24,  SWS_BICUBIC,  NULL,  NULL,  NULL  );
				sws_scale(  ctx,  pFrame->data,  pFrame->linesize,  0,  pCodecCtx->height,  &packet.data,  &packet.size  );

				//  save
				if  (  ++i <=  5  )  SaveFrame(  pFrameRGB,  pCodecCtx->width,  pCodecCtx->header_bits,  i  );
			}
		}
		av_free_packet(  &packet  );
	}
	av_free(  buffer );
	av_free(  pFrameRGB  );

	av_free(  pFrame  );
	avcodec_close(  pCodecCtx  );
	avformat_close_input(&pFormatCtx);

	return 0;
}


