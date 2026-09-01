

#ifndef  __QISCOMPRESSPROC_dec_H__
#define  __QISCOMPRESSPROC_dec_H__	//  {

#include	<mmsystem.h>
#include	"qdcOpenCommon.h"
#include	"qisCompressProc.h"


//
typedef  struct  __qdcObj_test_decA_t				{
		 QDC_OBJ_test					common;
				 
		 //
		 QDC_OBJ_transCommon			transCommon;

		 //
		 			 //QDC_OUTPUT					outs[1];

					 //  2016/12/06
					 long						old_lPktId;
					 

					 //
					 struct						{
						 YUVWriter_var			m_var;
					 }							yuvWriter;

					 //
#if  0
					 struct	{
						 BOOL	bDone_run;

					 }		status;
#endif

}		 QDC_OBJ_test_decA;


extern  "C"  int  __declspec(  dllexport  )qdcExitCompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo  );
extern  "C"  int  __declspec(  dllexport  )qdcExitDecompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo  );
extern  "C"  int  __declspec(  dllexport  )qdcExitCompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo  );
extern  "C"  int  __declspec(  dllexport  )qdcExitDecompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo  );

//
 void  qdcFreeOutputs(  QDC_OBJ_INFO  *  pQdcObjInfo  );


extern QIS_guiOpen  *  g_pGuiOpen;


#endif  //  }


