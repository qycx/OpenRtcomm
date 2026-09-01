

#ifndef  __QISCOMPRESSPROC_H__
#define  __QISCOMPRESSPROC_H__	//  {

#include	<mmsystem.h>
#include	"qdcOpenCommon.h"

typedef  struct  __qdcObj_test_t				{
				 
					 QDC_OUTPUT					outs[1];

}		 QDC_OBJ_test;


extern  "C"  int  __declspec(  dllexport  )qdcExitCompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo  );
extern  "C"  int  __declspec(  dllexport  )qdcExitDecompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo  );
extern  "C"  int  __declspec(  dllexport  )qdcExitCompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo  );
extern  "C"  int  __declspec(  dllexport  )qdcExitDecompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo  );



#endif  //  }


