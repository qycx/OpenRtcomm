
#include	"stdafx.h"
#include	<tchar.h>

//#include	"qyMcMainCommon.h"

#include	"ctxQmcTmpl.h"
#include	"qmcVideoCapture.h"

typedef unsigned int uint_t;
typedef unsigned char uint8_t;

// read the first 10 bit sample from the least significant bits of the 4 bytes pointed to by 'data'
//
inline uint_t readv210sample_pos2of3(  uint8_t  *  data  )
{
	const uint_t lsb  =  (  data[2]  &  0xf0  )  >>  4;
	const uint_t msb  =  (  data[3]  &  0x3f  )  <<  4;
	return  msb | lsb;
}

// read the second 10 bit sample from the middle bits of the 4 bytes pointed to by 'data'
inline uint_t readv210sample_pos1of3(  uint8_t  *  data  )
{
	const uint_t lsb  =  (  data[1]  &  0xfc  )  >>  2;
	const uint_t msb  =  (  data[2]  &  0x0f  )  <<  6;
	return  msb | lsb;
}

//  read the third 10 bit sample from the more significant bits of the 4 bytes pointed to by 'data'
inline uint_t readv210sample_pos0of3(  uint8_t  *  data  )
{
	const uint_t lsb  =  (  data[0]  &  0xff  );
	const uint_t msb  =  (  data[1]  &  0x03  )  <<  8;
	return  msb | lsb;
}

void unpackv210line(  uint8_t * dst,  uint8_t  * src,  uint_t  luma_width  )
{
	//  number ot blocks completely filled with active samples (  6 per block  ) 
	const uint_t num_firstpass_samples  =  2  *  (  luma_width  / 6  )  *  6;
	uint_t  x;
	for  (  x = 0; x < num_firstpass_samples;  src += 16  )  {
		 dst[ x++ ]  =  readv210sample_pos0of3(  src + 0 ) >> 2;  //  Cb
		 dst[ x++ ]  =  readv210sample_pos1of3(  src + 0 ) >> 2;  //  Y'
		 dst[ x++ ]  =  readv210sample_pos2of3(  src + 0 ) >> 2;  //  Cr
		 dst[ x++ ]  =  readv210sample_pos0of3(  src + 4 ) >> 2;  //  Y'

		 dst[ x++ ]  =  readv210sample_pos1of3(  src + 4 ) >> 2;
		 dst[ x++ ]  =  readv210sample_pos2of3(  src + 4 ) >> 2;
		 dst[ x++ ]  =  readv210sample_pos0of3(  src + 8 ) >> 2;
		 dst[ x++ ]  =  readv210sample_pos1of3(  src + 8 ) >> 2;

		 dst[ x++ ]  =  readv210sample_pos2of3(  src + 8 ) >> 2;
		 dst[ x++ ]  =  readv210sample_pos0of3(  src + 12 ) >> 2;
		 dst[ x++ ]  =  readv210sample_pos1of3(  src + 12 ) >> 2;
		 dst[ x++ ]  =  readv210sample_pos2of3(  src + 12 ) >> 2;
	}

	//  mop up last subblock ( 4 or 2 active samples )
	if  (  x < 2 * luma_width  )  {
		 dst[ x++ ]  =  readv210sample_pos0of3(  src + 0 ) >> 2;  //  Cb
		 dst[ x++ ]  =  readv210sample_pos1of3(  src + 0 ) >> 2;  //  Y'
		 dst[ x++ ]  =  readv210sample_pos2of3(  src + 0 ) >> 2;  //  Cr
		 dst[ x++ ]  =  readv210sample_pos0of3(  src + 4 ) >> 2;  //  Y'
	}
	if  (  x < 2 * luma_width  )  {
		 dst[ x++ ]  =  readv210sample_pos1of3(  src + 4 ) >> 2;
		 dst[ x++ ]  =  readv210sample_pos2of3(  src + 4 ) >> 2;
		 dst[ x++ ]  =  readv210sample_pos0of3(  src + 8 ) >> 2;
		 dst[ x++ ]  =  readv210sample_pos1of3(  src + 8 ) >> 2;
	}
}

#if  0
//  utility function to convert v210 data into something easier to display 
//  it is too difficult to do this in the openGL shader
void VideoData::convertv210(  )
{
	// pad to a multiple of 48 luma samples
	// nb, 48 luma samples becomes 128 bytes
	const uint_t padded_w  =  (  (  Ywitdh  + 47  )  /  48  )  *  48;	//  number of luma samples, padded
	const uint_t padded_line_length  =  (  2  *  padded_w  *  4  )  /  3;  //  number of bytes on each line in the file , including padding data

	uint8_t * dst  =  (  uint8_t * )data;  //  destination for 8bit uyvy, may = src
	uint8_t * src  =  (  uint8_t * )data;  //  source of v210 data

	for (  int y = 0;  y < Yheight;  y ++  )  {
		unpackv210line(  dst,  src,  Ywidth  );
		src +=  padded_line_length;
		dst +=  Ywidth * 2;
	}

	//  change the description of the data to match UYVY
	//  note that the datasize stays the same
	renderFormat  =  UYVY;
	glYTextureWidth  =  Ywidth  /  2;		//  2 Y samples per RGBA quad
	YdataSize  =  Ywidth * Yheight * 2;
	UdataSize  =  0;
	VdataSize  =  0;
}

#endif

int  convertV210(  unsigned  char  *  src,  unsigned  char  *  dst,  int  Ywidth,  int  Yheight  )
{
	// pad to a multiple of 48 luma samples
	// nb, 48 luma samples becomes 128 bytes
	const uint_t padded_w  =  (  (  Ywidth  + 47  )  /  48  )  *  48;	//  number of luma samples, padded
	const uint_t padded_line_length  =  (  2  *  padded_w  *  4  )  /  3;  //  number of bytes on each line in the file , including padding data

#if  0
	uint8_t * dst  =  (  uint8_t * )data;  //  destination for 8bit uyvy, may = src
	uint8_t * src  =  (  uint8_t * )data;  //  source of v210 data
#endif

	for (  int y = 0;  y < Yheight;  y ++  )  {
		unpackv210line(  dst,  src,  Ywidth  );
		src +=  padded_line_length;
		dst +=  Ywidth * 2;
	}


#if  0
	//  change the description of the data to match UYVY
	//  note that the datasize stays the same
	renderFormat  =  UYVY;
	glYTextureWidth  =  Ywidth  /  2;		//  2 Y samples per RGBA quad
	YdataSize  =  Ywidth * Yheight * 2;
	UdataSize  =  0;
	VdataSize  =  0;
#endif


	return  0;
}


 int  v210ToRgb24(  void  *  pCusModulesParam,  unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height,  BOOL  bFlipImg  )
{
	int			iErr	=	-1;


	//  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "v210ToRgb24 failed: not supported"  )  );

	convertV210(  yuv,  yuv,  width,  height  );
	//  µÃµ½ÁËuyvy

	if  (  uyvyToRgb24(  pCusModulesParam,  yuv,  rgb,  width,  height,  bFlipImg  )  )  goto  errLabel;

	iErr  =  0;

errLabel:

	return  iErr;
}
