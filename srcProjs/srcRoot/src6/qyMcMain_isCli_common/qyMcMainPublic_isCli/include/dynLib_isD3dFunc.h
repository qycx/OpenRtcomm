
#ifndef  __dynLib_isD3dFunc_h__	
#define  __dynLib_isD3dFunc_h__	//  {

//
#include			"dec_d3d11_dev_open.h"
#include			"enc_d3d11_dev_open.h"
#include			"qisChromakeyEffect_open.h"
#include			"tmpDllInit_open.h"


//  2015/02/17
typedef  struct												{
				HINSTANCE									hDll;
				BOOL										bOk;

				//  2017/10/09
				PF_qyDllInit								pf_qyDllInit;
				PF_qyDllExit								pf_qyDllExit;


				//
				PF_DEC_d3d11_devVar_new						pf_DEC_d3d11_devVar_new;
				PF_DEC_d3d11_devVar_free					pf_DEC_d3d11_devVar_free;
				
				//
				PF_decDev_my_RenderFrame					pf_decDev_my_RenderFrame;


				//
				PF_ENC_d3d11_devVar_new						pf_ENC_d3d11_devVar_new;
				PF_ENC_d3d11_devVar_free					pf_ENC_d3d11_devVar_free;
				
				//  2016/05/02	
				PF_encDev_YUVReader_myLoadNextFrame			pf_encDev_YUVReader_myLoadNextFrame;

				//  2016/05/06
				PF_getSize_QIS_chromaKey_effect				pf_getSize_QIS_chromaKey_effect;
				//
				PF_initQisChromaKeyEffect					pf_initQisChromaKeyEffect;
				PF_exitQisChromaKeyEffect					pf_exitQisChromaKeyEffect;

				//				
				PF_createQuad								pf_createQuad;
				PF_freeQuad									pf_freeQuad;

				//
				PF_getOrtho2DMats							pf_getOrtho2DMats;

				//
				void  *										pf_myCopyTex_rtt;

				//
				//  2015/10/30
				PF_DXUTSaveTextureToFile					pf_DXUTSaveTextureToFile;


}															DYN_LIB_isD3dFunc;




#endif  //  }




