

#ifndef  __QISCOMPRESSPROC_H__
#define  __QISCOMPRESSPROC_H__	//  {

#include	<mmsystem.h>
#include	"qdcOpenCommon.h"
#include	"qySyncObj.h"
#include	"genericQueue.h"

#include	"tmpGuiOpenFunc.h"

//#define  CONST_fourcc_h264		MAKEFOURCC('h','2','6','4')
//#define  CONST_fourcc_YV12		MAKEFOURCC('Y','V','1','2')


#if  0
typedef  struct  __qdcObj_test_t				{
				 
				 QDC_OBJ_h264Common				common;

				 //  2012/06/27
				 unsigned  char					ucbFlippedImg;

				 //
				 struct							{
					 QY_VIDEO_HEADER			vh_decompress_real;
					 char					*	pBuf;
					 unsigned int				uiBufSize;
				 }								inputForEnc;

				 void						*	pPipeline;
				 void						*	p_init_params;		//  2012/09/01

}		 QDC_OBJ_test;
#endif



extern  "C"  int  __declspec(  dllexport  )qdcExitCompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo  );
extern  "C"  int  __declspec(  dllexport  )qdcExitDecompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo  );
extern  "C"  int  __declspec(  dllexport  )qdcExitCompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo  );
extern  "C"  int  __declspec(  dllexport  )qdcExitDecompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo  );

// 
//int makeBmpInfoHeader_yv12(  unsigned int bits,  int iWidth,  int iHeight,  BITMAPINFOHEADER  *  p  );
void  qdcFreeOutputs(  QDC_OBJ_INFO  *  pQdcObjInfo  );
int  tmp_showInfo(  TCHAR  *  hint  );



#endif  //  }


