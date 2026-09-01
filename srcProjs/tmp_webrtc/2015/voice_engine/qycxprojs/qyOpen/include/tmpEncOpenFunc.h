
#ifndef  __tmpEncOpenFunc_h__
#define  __tmpEncOpenFunc_h__	//  {

//
#include	"enc_d3d11_dev_open.h"
#include	"qisChromakeyEffect_open.h"

//
 extern  "C"  int  tmpEnc_setFuncs(  QDC_OBJ_INFO  *  pQdcObjInfo  );
 //
 extern  "C"  int  tmpEnc_qdcGetProp(  int  iPropId,  void  *  pParam_input,  void  *  pParam_output  );
 extern  "C"  int  tmpEnc_qdcSetProp(  int  iPropId,  void  *  pParam_input,  void  *  pParam_output  );

 //
extern  void  *								g_pf_ENC_d3d11_devVar_new;
extern  void  *								g_pf_ENC_d3d11_devVar_free;
extern  void  *								g_pf_encDev_YUVReader_myLoadNextFrame;
extern  void  *								g_pf_preForTest_encDev_YUVReader_myLoadNextFrame;
 

//
extern  PF_getSize_QIS_chromaKey_effect		g_pf_getSize_QIS_chromaKey_effect;
extern  void  *								g_pf_initQisChromaKeyEffect;
extern  PF_exitQisChromaKeyEffect			g_pf_exitQisChromaKeyEffect;

//
extern  PF_createQuad						g_pf_createQuad;	
extern  PF_freeQuad							g_pf_freeQuad;
//
extern  PF_getOrtho2DMats					g_pf_getOrtho2DMats;
//
extern  void  *								g_pf_myCopyTex_rtt;



#endif  //  }

