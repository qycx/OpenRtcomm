

#ifndef  __QISCOMPRESSPROC_H__
#define  __QISCOMPRESSPROC_H__	//  {

#include	<mmsystem.h>
#include	"qdcOpenCommon.h"
#include	"tmpGuiOpenFunc.h"


//
#define  CONST_qdcObjType_null					0
#define	 CONST_qdcObjType_encA					1
#define	 CONST_qdcObjType_decA					2




//
typedef  struct  __qdcObj_test_t				{
				 unsigned  int					uiType;
				 
					 QDC_OUTPUT					outs[1];

#if  0

					 //  2016/12/06
					 long						old_lPktId;

					 //
					 BitstreamWriter_var			bsWriter;
#endif

					 //
					 struct	{
						 BOOL	bDone_run;

					 }		status;


}		 QDC_OBJ_test;


extern  "C"  int  __declspec(  dllexport  )qdcExitCompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo  );
extern  "C"  int  __declspec(  dllexport  )qdcExitDecompressAudio(  QDC_OBJ_INFO  *  pQdcObjInfo  );
extern  "C"  int  __declspec(  dllexport  )qdcExitCompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo  );
extern  "C"  int  __declspec(  dllexport  )qdcExitDecompressVideo(  QDC_OBJ_INFO  *  pQdcObjInfo  );

//
 void  qdcFreeOutputs(  QDC_OBJ_INFO  *  pQdcObjInfo  );


extern QIS_guiOpen  *  g_pGuiOpen;


#endif  //  }


