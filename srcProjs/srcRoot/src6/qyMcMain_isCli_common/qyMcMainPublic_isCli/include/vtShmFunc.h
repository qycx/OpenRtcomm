
#ifndef  __vtShmFunc_h__
#define  __vtShmFunc_h__	//  {

int  writeShmPkt(   myDRAW_VIDEO_DATA  *  pPkt,  VT_shm_content  *  pShmContent,  BITMAPINFOHEADER  *  pBih,  unsigned  char  ucCnt_shmPktBufs,  int  index_toWrite  );


//
int  shm_img_to_yuv(  void  *  pQdcObjInfoParam,  void  *  pImg,  unsigned  int  cropW,  unsigned  int  cropH,  unsigned  int  pitch,  unsigned  int  w,  unsigned  int  h,  void  *  pYUVWriter_var  );


#endif  //  }



