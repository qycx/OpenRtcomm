
#include	"stdafx.h"

#include	<mmsystem.h>
#include	"qdcOpenCommon.h"

#if  defined(  __APP_qyMc__  )  ||  defined(  __APP_qyMc_touchscreen__  )
	#include	"stdafx.h"
	#include	"qyMcMainCommon.h"
#else
	#include	<windows.h>
#endif
#include	<tchar.h>


//
bool  is4k(int iW, int iH)
{
	if (iW * iH > (1920 + 200) * (1080 + 200)) {
		return  true;
	}
	return false;
}


 int  makeBmpInfoHeader_rgb(  unsigned  int  bits,  int  iWidth,  int  iHeight,  BITMAPINFOHEADER  *  p  )
{
	if  (  !p  )  return  -1;

	memset(  p,  0,  sizeof(  p[0]  )  );

	p->biSize  =  sizeof(  BITMAPINFOHEADER  );
	p->biWidth  =  iWidth;
	p->biHeight  =  iHeight;
	p->biPlanes  =  1;
	p->biBitCount  =  (  WORD  )bits;
	p->biCompression  =  BI_RGB;
	p->biSizeImage  =  (  p->biWidth  *  p->biBitCount  +  31  )  /  32  *  4  *  p->biHeight;
	p->biClrUsed = (bits <= 8) ? 1<<bits : 0;

	return  0;
}

 int  makeBmpInfoHeader_yuy2(  unsigned  int  bits,  int  iWidth,  int  iHeight,  BITMAPINFOHEADER  *  p  )
{
	if  (  !p  )  return  -1;

	memset(  p,  0,  sizeof(  p[0]  )  );

	p->biSize  =  sizeof(  BITMAPINFOHEADER  );
	p->biWidth  =  iWidth;
	p->biHeight  =  iHeight;
	p->biPlanes  =  1;
	p->biBitCount  =  16;	//  (  WORD  )bits;
	p->biCompression  =  CONST_fourcc_YUY2;
	p->biSizeImage  =  (  p->biWidth  *  p->biBitCount  +  31  )  /  32  *  4  *  p->biHeight;
	p->biClrUsed = (bits <= 8) ? 1<<bits : 0;

	return  0;
}


 int makeBmpInfoHeader_yv12(  unsigned int bits,  int iWidth,  int iHeight,  BITMAPINFOHEADER  *  p  )
{
	if(  !p  )  return  -1;

	//  2014/07/20
	bits  =  12;

	//
	memset(  p,  0,  sizeof(  p[0]  )  );

	p->biSize  =  sizeof(  BITMAPINFOHEADER  );
	p->biWidth  =  iWidth;
	p->biHeight  =  iHeight;
	p->biPlanes  =  1;
	p->biBitCount  =  12;
	p->biCompression  =  CONST_fourcc_YV12;
	p->biSizeImage  =  (  p->biWidth  *  p->biBitCount  +  31  )  / 32  *  4  *  p->biHeight;
	p->biClrUsed  =  (  bits  <=  8  )  ?  1<<bits  :  0;

	return  0;

}

 int makeBmpInfoHeader_i420(  unsigned int bits,  int iWidth,  int iHeight,  BITMAPINFOHEADER  *  p  )
{
	if(  !p  )  return  -1;

	//  2014/07/20
	bits  =  12;

	//
	memset(  p,  0,  sizeof(  p[0]  )  );

	p->biSize  =  sizeof(  BITMAPINFOHEADER  );
	p->biWidth  =  iWidth;
	p->biHeight  =  iHeight;
	p->biPlanes  =  1;
	p->biBitCount  =  12;
	p->biCompression  =  CONST_fourcc_I420;
	p->biSizeImage  =  (  p->biWidth  *  p->biBitCount  +  31  )  / 32  *  4  *  p->biHeight;
	p->biClrUsed  =  (  bits  <=  8  )  ?  1<<bits  :  0;

	return  0;

}

 //
 int makeBmpInfoHeader_nv12(unsigned int bits, int iWidth, int iHeight, BITMAPINFOHEADER* p)
 {
	 if (!p)  return  -1;

	 //  2014/07/20
	 bits = 12;

	 //
	 memset(p, 0, sizeof(p[0]));

	 p->biSize = sizeof(BITMAPINFOHEADER);
	 p->biWidth = iWidth;
	 p->biHeight = iHeight;
	 p->biPlanes = 1;
	 p->biBitCount = 12;
	 p->biCompression = CONST_fourcc_NV12;
	 p->biSizeImage = (p->biWidth * p->biBitCount + 31) / 32 * 4 * p->biHeight;
	 p->biClrUsed = (bits <= 8) ? 1 << bits : 0;

	 return  0;

 }


 //  2014/07/23
 int makeBmpInfoHeader_yuv(  int  iFourcc,  unsigned int bits,  int iWidth,  int iHeight,  BITMAPINFOHEADER  *  p  )
{
	  switch  (  iFourcc  )  {
			  case  CONST_fourcc_YV12:
				    return  makeBmpInfoHeader_yv12(  bits,  iWidth,  iHeight,  p  );
					break;
			  case  CONST_fourcc_I420:
				    return  makeBmpInfoHeader_i420(  bits,  iWidth,  iHeight,  p  );
				    break;
			  case  CONST_fourcc_NV12:
				    return  makeBmpInfoHeader_nv12(bits, iWidth, iHeight, p);
					break;
			  default:
					  break;
	  }

	  //
	  return  -1;
}


 //


//
 //  2012/09/11
#define		CONST_bp_compression		6500
__int64  myGetBitrate(VIDEO_COMPRESSOR_cfgCommon* pVideoCfgCommon, unsigned  int  w, unsigned  int  h)
{
	int						iErr = -1;
	__int64					bitrate = 0;
	int  framerate = pVideoCfgCommon->usMaxFps_toShareBmp;

	//
	if (pVideoCfgCommon->iAvgBitrate > 0) {
		bitrate = pVideoCfgCommon->iAvgBitrate;
	}
	else {

		//  
		if (isCapTypeScreen(pVideoCfgCommon->uiCapType))
		{
			if (pVideoCfgCommon->iAvgBitrate)  bitrate = pVideoCfgCommon->iAvgBitrate;
			else  bitrate = 500000; //300000;
		}
		else {  //  2013/03/13
			if (isCapTypeMediaFile(pVideoCfgCommon->uiCapType)
				|| isCapTypeMediaDevice(pVideoCfgCommon->uiCapType))
			{
				if (pVideoCfgCommon->iAvgBitrate)  bitrate = pVideoCfgCommon->iAvgBitrate;
			}

			//
			if (!bitrate) {
				//  2014/07/10. 这里的限制是指码流的估算，不影响帧速控制
				if (framerate > 60)  framerate = 60;
				//
				int  iFourcc = fourccStr2i(pVideoCfgCommon->fourccStr);
				//
				if (iFourcc == CONST_fourcc_HEVC
					||  iFourcc  ==  CONST_fourcc_AV01) 
				{	//  2017/10/11
					//
					float tmpBitrate_base = 1000000;
					float tmpBitrate = 1000000;
					//
					if (!w || !h) {
						tmpBitrate_base = 600000  *  1.25;
						tmpBitrate = 1200000;
						if (pVideoCfgCommon->usMaxFps_toShareBmp) {
							bitrate =  tmpBitrate_base  +  tmpBitrate * pVideoCfgCommon->usMaxFps_toShareBmp / 30.;
						}
						else {
							 bitrate =  tmpBitrate_base  +  tmpBitrate;
						}
					}
					else  if (w <= 256 && h <= 144) {
						//
						//tmpBitrate_base = 40000;
						//tmpBitrate = 5;
						bitrate = 50  *  1000;
					}
					else  if (w <= 848 && h <= 480) {
						tmpBitrate_base = 200000;
						tmpBitrate = 110000;
						bitrate = tmpBitrate_base + 1. * tmpBitrate * w * h / (848 * 480);
					}
					else  if (w <= 1280 && h <= 720) {
						tmpBitrate_base = 400000  *  1.00;
						tmpBitrate = 600000;
						bitrate = tmpBitrate_base  +  1.  *  tmpBitrate * w * h / (1280. * 720);
					}
					else  if (w <= 1920 && h <= 1080) {
						tmpBitrate_base  =  600000  *  1.00;
						tmpBitrate = 1200000;
						bitrate = tmpBitrate_base  +  tmpBitrate * w * h / (1920 * 1080);
					}
					else if (w <= 4096 && h <= 2160) {
						tmpBitrate_base = 1000000 * 1.00;
						tmpBitrate = 3000000;
						bitrate = tmpBitrate_base + tmpBitrate * w * h / (4096 * 2160);

					}
					else {
						tmpBitrate_base = 1000000  *  1.;
						tmpBitrate = 1500000;
						bitrate = tmpBitrate_base  +  tmpBitrate * w * h / (1920 * 1080);
					}
					//
					if (iFourcc == CONST_fourcc_AV01) {
						bitrate = bitrate * 0.75;
					}
				}
				else {  //  264

					//
					float  f1 = 0.3 * framerate / 60.;
					float  f = (1 + f1) * 0.8;
					//
					bitrate = (((1. * w * h) * f / CONST_bp_compression) / 1.0) * 10000;
					//
					if (w < 1280 && h < 720) {
						//bitrate  =  (((  1.  *  w  *  h  )  *  framerate  /  CONST_bp_compression  )  / 10  )  *  10000;
						if (1
							&& (framerate >= 15))
						{
							//bitrate  =  bitrate  *  0.54;	//  60  /  100; 
							bitrate = bitrate * 1.25;
						}
					}
					else  if (w < 1920 && h < 1080) {
						//bitrate  =  (((  1.  *  w  *  h  )  *  framerate  /  CONST_bp_compression  )  / 10  )  *  10000;		  
						if (1
							&& (framerate >= 15))
						{
							//bitrate  =  bitrate  *  0.48;	//  60  /  100; 
							bitrate = bitrate * 1.25;
						}
					}
					else  if (w < 3840 && h < 2160) {
						// bitrate  =  (((  1.  *  w  *  h  )  *  framerate  /  CONST_bp_compression  )  / 10  )  *  10000;		  
						if (1
							&& (framerate >= 15))
						{
							//  bitrate  =  bitrate  *  0.4;	//  60  /  100; 
						}
						//
						bitrate = min(bitrate, 6000000);
					}
					else {
						//  0表示没有设置	   
					}


				}

			}
		}

	}

	iErr = 0;
	//  errLabel:


	return  iErr ? iErr : bitrate;
}








//
float  myGetPeekFactor(  VIDEO_COMPRESSOR_cfgCommon  *  pVideoCfgCommon,  unsigned  int  w,  unsigned  int  h  )
{
	if  (  w  <  1920  &&  h  <  1080  )  {
		return  CONST_peek_factor_720p;
	}
	return  CONST_peek_factor;
}


//
 char  *  iFourcc2Str(  int  fourcc,  char  *  fourccStr,  unsigned  int  size  )
{
	unsigned  char  chs[5]			=	"";
	int				i				=	0;
	
	i  =  0;	chs[i]  =  (  unsigned  char  )fourcc;
	i  ++  ;	chs[i]  =  (  unsigned  char  )(  fourcc  >>  8  );
	i  ++  ;	chs[i]  =  (  unsigned  char  )(  fourcc  >>  16  );
	i  ++  ;	chs[i]  =  (  unsigned  char  )(  fourcc  >>  24  );
	i  ++  ;	chs[i]	=	0;

	//
	if  (  !fourccStr  )  {
		//OutputDebugString(  CQyString(  (  char  *  )chs  )  +  _T(  "\n"  )  );
	}

	//
	if  (  fourccStr  &&  size  >  4  )  {
		//
		//safeStrnCpy(  (  char  *  )chs,  fourccStr,  size  );
		strncpy(  fourccStr,  (  char  *  )chs,  size  );  
		//
		return  fourccStr;
	}

	return  NULL;
}

 //
  int  fourccStr2i(  const  char  *  fourccStr  )
{
	if  (  !fourccStr  )  return  -1;
    
	//return  mmioFOURCC(  fourccStr[0],  fourccStr[1],  fourccStr[2],  fourccStr[3]  );
	return  MAKEFOURCC(  fourccStr[0],  fourccStr[1],  fourccStr[2],  fourccStr[3]  );
}
