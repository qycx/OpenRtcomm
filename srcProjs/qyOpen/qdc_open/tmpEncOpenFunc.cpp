

#include	"stdafx.h"

#include	<mmsystem.h>
#include	<tchar.h>

#include	"qdcOpenCommon.h"
#include	"qySyncObj.h"
#include	"genericQueue.h"

#include	"tmpGuiOpenFunc.h"
#include	"enc_d3d11_dev_open.h"
#include	"qisChromakeyEffect_open.h"


//
extern  BOOL				g_bUsing_sharedTex_enc;

//
//  2016/04/26
 void  *								g_pf_ENC_d3d11_devVar_new  =  NULL;
 void  *								g_pf_ENC_d3d11_devVar_free  =  NULL;
 void  *								g_pf_encDev_YUVReader_myLoadNextFrame  =  NULL;
 void  *								g_pf_preForTest_encDev_YUVReader_myLoadNextFrame  =  NULL;
 //
 //  2016/05/06
 PF_getSize_QIS_chromaKey_effect		g_pf_getSize_QIS_chromaKey_effect  =  NULL;
 void  *								g_pf_initQisChromaKeyEffect  =  NULL;
 PF_exitQisChromaKeyEffect				g_pf_exitQisChromaKeyEffect  =  NULL;
 //
 PF_createQuad							g_pf_createQuad  =  NULL;	
 PF_freeQuad							g_pf_freeQuad  =  NULL;
 //
 PF_getOrtho2DMats						g_pf_getOrtho2DMats  =  NULL;
 //
 void  *								g_pf_myCopyTex_rtt  =  NULL;

//
 extern  "C"  int  tmpEnc_setFuncs(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	int  iErr  =  -1;

	//  2016/04/26
	if  (  !pQdcObjInfo->pf_qoi_getPtrProperty  )  {
		tmp_showInfo(  (TCHAR*)_T(  "qdcInitEncV failed, qoi_getPtr is null"  )  );
		return  -1;
	}
	g_pf_ENC_d3d11_devVar_new  =  (  PF_ENC_d3d11_devVar_new  )pQdcObjInfo->pf_qoi_getPtrProperty(  pQdcObjInfo,  CONST_qdcPropId_PF_ENC_d3d11_devVar_new  );
	if  (  !g_pf_ENC_d3d11_devVar_new  )  {
		tmp_showInfo((TCHAR*)_T(  "qdcInitEncV failed, g_pf_ENC_d3d11_devVar_new is null"  )  );
		return  -1;
	}
	g_pf_ENC_d3d11_devVar_free  =  (  PF_ENC_d3d11_devVar_free  )pQdcObjInfo->pf_qoi_getPtrProperty(  pQdcObjInfo,  CONST_qdcPropId_PF_ENC_d3d11_devVar_free  );
	if  (  !g_pf_ENC_d3d11_devVar_free  )  {
		tmp_showInfo((TCHAR*)_T(  "qdcInitEncV failed, g_pf_ENC_d3d11_devVar_free is null"  )  );
		return  -1;
	}
	g_pf_encDev_YUVReader_myLoadNextFrame  =  (  PF_encDev_YUVReader_myLoadNextFrame  )pQdcObjInfo->pf_qoi_getPtrProperty(  pQdcObjInfo,  CONST_qdcPropId_PF_encDev_YUVReader_myLoadNextFrame  );
	if  (  !g_pf_encDev_YUVReader_myLoadNextFrame  )  {
		tmp_showInfo((TCHAR*)_T(  "qdcInitEncV failed, g_pf_encDev_YUVReader_myLoadNextFrame is null"  )  );
		return  -1;
	}
	g_pf_preForTest_encDev_YUVReader_myLoadNextFrame  =  pQdcObjInfo->pf_qoi_getPtrProperty(  pQdcObjInfo,  CONST_qdcPropId_PF_preForTest_encDev_YUVReader_myLoadNextFrame  );
	if  (  !g_pf_preForTest_encDev_YUVReader_myLoadNextFrame  )  {
		tmp_showInfo((TCHAR*)_T(  "qdcInitEncV warning, g_pf_preForTest_encDev_YUVReader_myLoadNextFrame is null"  )  );
		return  -1;
	}
 
	//
	g_pf_getSize_QIS_chromaKey_effect  =  (  PF_getSize_QIS_chromaKey_effect  )pQdcObjInfo->pf_qoi_getPtrProperty(  pQdcObjInfo,  CONST_qdcPropId_PF_getSize_QIS_chromaKey_effect  );
	if  (  !g_pf_getSize_QIS_chromaKey_effect  )  {
		tmp_showInfo((TCHAR*)_T(  "qdcInitEncV failed, g_pf_getSize_QIS_chromaKey_effect is null"  )  );
		return  -1;
	}
	g_pf_initQisChromaKeyEffect  =  (  PF_initQisChromaKeyEffect  )pQdcObjInfo->pf_qoi_getPtrProperty(  pQdcObjInfo,  CONST_qdcPropId_PF_initQisChromaKeyEffect  );
	if  (  !g_pf_initQisChromaKeyEffect  )  {
		tmp_showInfo((TCHAR*)_T(  "qdcInitEncV failed, g_pf_initQisChromaKeyEffect is null"  )  );
		return  -1;
	}
	g_pf_exitQisChromaKeyEffect  =  (  PF_exitQisChromaKeyEffect  )pQdcObjInfo->pf_qoi_getPtrProperty(  pQdcObjInfo,  CONST_qdcPropId_PF_exitQisChromaKeyEffect  );
	if  (  !g_pf_exitQisChromaKeyEffect  )  {
		tmp_showInfo((TCHAR*)_T(  "qdcInitEncV failed, g_pf_exitQisChromaKeyEffect is null"  )  );
		return  -1;
	}

	//
	g_pf_createQuad  =  (  PF_createQuad  )pQdcObjInfo->pf_qoi_getPtrProperty(  pQdcObjInfo,  CONST_qdcPropId_PF_createQuad  );
	if  (  !g_pf_createQuad  )  {
		return  -1;
	}
	//
	g_pf_freeQuad  =  (  PF_freeQuad  )pQdcObjInfo->pf_qoi_getPtrProperty(  pQdcObjInfo,  CONST_qdcPropId_PF_freeQuad  );
	if  (  !g_pf_freeQuad  )  {
		return  -1;
	}
	//
	g_pf_getOrtho2DMats  =  (  PF_getOrtho2DMats  )pQdcObjInfo->pf_qoi_getPtrProperty(  pQdcObjInfo,  CONST_qdcPropId_PF_getOrtho2DMats  );
	if  (  !g_pf_getOrtho2DMats  )  {
		return  -1;
	}
	//
	g_pf_myCopyTex_rtt  =  pQdcObjInfo->pf_qoi_getPtrProperty(  pQdcObjInfo,  CONST_qdcPropId_PF_myCopyTex_rtt  );
	if  (  !g_pf_myCopyTex_rtt  )  {
		return  -1;
	}


	iErr  =  0;
errLabel:
	return  iErr;
}






//
  extern  "C"  int  tmpEnc_qdcGetProp(  int  iPropId,  void  *  pParam_input,  void  *  pParam_output  )
 {
	 int  iErr  =  -1;

	 //
	 if  (  !pParam_output  )  return  -1;

	 //
	 switch  (  iPropId  )  {
			 case  CONST_qdcPropId_bSupport_sharedTex_enc:  {
				   PARAM_bSupport_sharedTex_enc  *  pParam_bse  =  (  PARAM_bSupport_sharedTex_enc  *  )pParam_input;
				   BOOL  *  pbVal  =  (  BOOL  *  )pParam_output;

				   //
				   if  (  !pParam_bse  )  {
					   #ifdef  __DEBUG__
							   assert(  0  );
					   #endif
					   goto  errLabel;
				   }
				   //  2017/10/13
				   //  暂时不用共享纹理的压缩方案，原因见CMyPipeline::InitMfxEncParams()前的说明
				   //
				   //if  (  pParam_bse->iFourcc  ==  CONST_fourcc_h264  )  //  
				   {
					   *pbVal  =  FALSE;
					   break;
				   }
				   
				   //
				   *pbVal  =  g_bUsing_sharedTex_enc;
				   //
				   }
				   //
				   break;
			 default:
				    tmp_showInfo((TCHAR*)_T(  "qdcGetProp failed, unprocessed propId"  )  );
					goto  errLabel;
	 }


	 iErr  =  0;
errLabel:
	 return  iErr;
 }




