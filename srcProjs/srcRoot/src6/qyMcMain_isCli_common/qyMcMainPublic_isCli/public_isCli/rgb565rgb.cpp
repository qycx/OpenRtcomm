
#include  "stdafx.h"
#include	<tchar.h>

 int  rgb565ToRgb24(  unsigned  char  *  src,  unsigned  char  *  rgb,  int  width,  int  height  )
{
	if  (  width  <=  0  ||  height  <=  0  )  {
		OutputDebugString(  _T(  "yuy2reg24 failed, width or height <=  0"  )  );
		return  -1;
	}

	unsigned  int	in,  out  =  0;
	//  unsigned  int	pixel_16;
	int	i, j;
	int				nBytesPerLine_rgb24	=	(  width  *  24  +  31  )  /  32  *  4;

	for  (  j  =  0;  j  <  height;  j  ++  )  {
		 for  (  i  =  0;  i  <  width;  i  ++  )  {

			  in  =  j  *  width  *  2  +  i  *  2;
			  out  =  j  *  nBytesPerLine_rgb24  +  i  *  3;  

			  rgb[out]	 =  (  src[  in  ]  & 0x1F  )  *  8;
			  rgb[out+1]  =  (  ((  src[  in  +  1  ]  <<  5  )  >>  2  )  +  (  src[  in  ]  >>  5  )  )  *  4;
			  rgb[out+2]  =  (  src[  in  +  1  ]  >>  3   )  *  8;
		 }
	}

	return  0;
}
