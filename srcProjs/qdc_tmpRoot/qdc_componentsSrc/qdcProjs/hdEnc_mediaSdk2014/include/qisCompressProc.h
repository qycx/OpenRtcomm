

#ifndef  __QISCOMPRESSPROC_H__
#define  __QISCOMPRESSPROC_H__	//  {

#include	<mmsystem.h>
#include	"qdcOpenCommon.h"
#include	"qySyncObj.h"
#include	"genericQueue.h"

//#define  CONST_fourcc_h264		MAKEFOURCC('h','2','6','4')
//#define  CONST_fourcc_YV12		MAKEFOURCC('Y','V','1','2')






extern  "C"  int  __declspec(  dllexport  )qdcExitCompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo  );
extern  "C"  int  __declspec(  dllexport  )qdcExitDecompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo  );
extern  "C"  int  __declspec(  dllexport  )qdcExitCompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo  );
extern  "C"  int  __declspec(  dllexport  )qdcExitDecompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo  );

// 
void  qdcFreeOutputs(  QDC_OBJ_INFO  *  pQdcObjInfo  );



#endif  //  }


