

#ifndef  __QISCOMPRESSPROC_enc_H__
#define  __QISCOMPRESSPROC_enc_H__	//  {

#include	<mmsystem.h>
#include	"qdcOpenCommon.h"
#include	"qisCompressProc.h"

//
typedef  struct  __qdcObj_test_encA_t				{

		 QDC_OBJ_test					common;
				 
					 //QDC_OUTPUT					outs[1];

					 //  2016/12/06
					 long						old_lPktId;

					 //
					 BitstreamWriter_var			bsWriter;

					 //
					 struct	{
						 BOOL	bDone_run;

					 }		status;


}		 QDC_OBJ_test_encA;


extern  "C"  int  __declspec(  dllexport  )qdcExitCompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo  );
extern  "C"  int  __declspec(  dllexport  )qdcExitDecompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo  );
extern  "C"  int  __declspec(  dllexport  )qdcExitCompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo  );
extern  "C"  int  __declspec(  dllexport  )qdcExitDecompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo  );

//
 void  qdcFreeOutputs(  QDC_OBJ_INFO  *  pQdcObjInfo  );


 //
 extern  "C"  int  qdcGetVorbisHeaders(  QDC_OBJ_INFO  *  pQdcObjInfo,  char  *  pBuf_header0,  unsigned  int  *  puiBufSize_header0,  char  *  pBuf_header1,  unsigned  int  *  puiBufSize_header1,  char  *  pBuf_header2,  unsigned  int  *  puiByfSize_header2  );


 //
extern QIS_guiOpen  *  g_pGuiOpen;


#endif  //  }


