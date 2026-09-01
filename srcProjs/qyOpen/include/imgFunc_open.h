
#ifndef  __imgFunc_open_h__
#define  __imgFunc_open_h__	//  {


//
 int  yv12ToRgb24( unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height,  BOOL  bFlipImg  );
 int  rgb24ToYv12(  unsigned  char  *  rgb,  unsigned  char  *  yuv,  int  width,  int  height,  BOOL  bFlipImg  );

//
int  i420ToRgb24( unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height,  BOOL  bFlipImg  );					//  2014/07/21
int  rgb24ToI420(  unsigned  char  *  rgb,  unsigned  char  *  yuv,  int  width,  int  height,  BOOL  bFlipImg  );

//
int  i420ToRgb(unsigned  char* yuv, unsigned  char* rgb, int rgbBits, int  width, int  height, BOOL  bFlipImg);
int  yv12ToRgb(unsigned  char* yuv, unsigned  char* rgb, int rgbBits, int  width, int  height, BOOL  bFlipImg);



//
int nv12ToRgb24(unsigned char* data, unsigned char* rgb, int width, int height,bool bFlip);
int bgr24ToNv12(unsigned  char* bgr, unsigned  char* nv12, int width, int height, int bFlip);


#endif  //  }


