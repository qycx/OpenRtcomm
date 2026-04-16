

#ifndef  __QISCOMPRESSPROC_H__
#define  __QISCOMPRESSPROC_H__	//  {

#include	<mmsystem.h>
#include	"qdcOpenCommon.h"
#include	"tmpGuiOpenFunc.h"


typedef  struct  __qdcObj_test_t			{
				 QDC_OBJ_transCommon			common;
				 
					 QDC_OUTPUT					outs[1];
					 					 
					 //
					 struct						{
						 long					old_lPktId;		//  用来防止getNextPkt出错，得到的是重复包
					 }							input;

					 int						iWidth;
					 int						iHeight;

					 //
					 struct						{
						 YUVWriter_var			m_var;
					 }							yuvWriter;

					 //
					 struct						{
						 BOOL					bDone_run;

					 }							status;

}		 QDC_OBJ_test;


extern  "C"  int  __declspec(  dllexport  )qdcExitCompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo  );
extern  "C"  int  __declspec(  dllexport  )qdcExitDecompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo  );
extern  "C"  int  __declspec(  dllexport  )qdcExitCompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo  );
extern  "C"  int  __declspec(  dllexport  )qdcExitDecompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo  );

//
 void  qdcFreeOutputs(  QDC_OBJ_INFO  *  pQdcObjInfo  );


extern QIS_guiOpen  *  g_pGuiOpen;


#endif  //  }


