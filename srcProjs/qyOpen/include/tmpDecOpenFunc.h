
#ifndef  __tmpDecOpenFunc_h__
#define  __tmpDecOpenFunc_h__	//  {

//
#include	"dec_d3d11_dev_open.h"

//
extern  "C"  int  tmpDec_setFuncs(  QDC_OBJ_INFO  *  pQdcObjInfo  );

//
 extern  "C"  int  tmpDec_qdcGetProp(  int  iPropId,  void  *  pParam_input,  void  *  pParam_output  );
 extern  "C"  int  tmpDec_qdcSetProp(  int  iPropId,  void  *  pParam_input,  void  *  pParam_output  );


 //  2016/04/26
extern PF_DEC_d3d11_devVar_new	g_pf_DEC_d3d11_devVar_new;
extern PF_DEC_d3d11_devVar_free	g_pf_DEC_d3d11_devVar_free;
extern void  *					g_pf_decDev_my_RenderFrame;



#endif  //  }

