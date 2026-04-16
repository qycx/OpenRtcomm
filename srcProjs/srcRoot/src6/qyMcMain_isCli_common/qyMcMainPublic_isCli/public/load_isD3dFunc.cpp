

#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>
#include	<mmsystem.h>
#include	<mmreg.h>
#include	<tchar.h>

//
//#include	<d3d11.h>

//
#include	"qyMcMainCommon.h"
#include	"qyDynLib.h"

#include	"qyMcMainRealTimeMediaProc.h"

#include	"qmcAcm.h"
#include	"qmcVideoCapture.h"
//
#include	"qmcDmoPublic.h"
#include	"tmpCeLib.h"

//
#include	"dynLib_isD3dFunc.h"
#include	"load_isD3dFunc.h"

//
//
#if  10
int  initDynLib_isD3dFunc(  void  **  pp  )
{
	int						iErr	=	-1;
	
	TCHAR				tmpFileName[MAX_PATH  +  1];
	 TCHAR				pathBuf[MAX_PATH  +  1];
	 TCHAR			*	filePart;
	 HINSTANCE			hDll							=		NULL;
	 PF_pCommonHandler	pf								=		NULL;
	 
	 //
	 if  (  !pp  )  return  -1;
	 if  (  *pp  )  return  -1;
	 
	 //
	 int  size  =  sizeof(  DYN_LIB_isD3dFunc  );
	 DYN_LIB_isD3dFunc  *  pLib  =  (  DYN_LIB_isD3dFunc  *  )mymalloc(  size  );
	 if  (  !pLib  )  return  -1;
	 memset(  pLib,  0,  size  );


	 //
	 GetModuleFileName(  NULL,  tmpFileName,  sizeof(  tmpFileName  )  /  sizeof(  tmpFileName[0]  )  );
	 if  (  !GetFullPathName(  tmpFileName,  sizeof(  pathBuf  )  /  sizeof(  pathBuf[0]  ),  pathBuf,  &filePart  )  )  goto  errLabel;
	 filePart[0]  =  0;

#if  10
	 _sntprintf(  tmpFileName,  mycountof(  tmpFileName  ),  _T(  "%sisD3dFunc_common.dll"  ),  pathBuf  );
	 pLib->hDll  =  LoadLibrary(  tmpFileName  );
	 if  (  !pLib->hDll  )  goto  errLabel;
#endif

	 //  2017/10/09
	 pLib->pf_qyDllInit  =  (  PF_qyDllInit  )GetProcAddress(  pLib->hDll,  "qyDllInit"  );
	 pLib->pf_qyDllExit  =  (  PF_qyDllExit  )GetProcAddress(  pLib->hDll,  "qyDllExit"  );
	 

	 //
	 //pFuncs->isCliD3d.pf_getZoneObjsInfo_d3dWall  =  (  PF_getZoneObjsInfo_d3dWall  )GetProcAddress(  pFuncs->isCliD3d.hDll,  "getZoneObjsInfo_d3dWall"  );	 
	 pLib->pf_DEC_d3d11_devVar_new  =  (  PF_DEC_d3d11_devVar_new  )GetProcAddress(  pLib->hDll,  "DEC_d3d11_devVar_new"  );
	 pLib->pf_DEC_d3d11_devVar_free  =  (  PF_DEC_d3d11_devVar_free  )GetProcAddress(  pLib->hDll,  "DEC_d3d11_devVar_free"  );
	 pLib->pf_decDev_my_RenderFrame  =  (  PF_decDev_my_RenderFrame  )GetProcAddress(  pLib->hDll,  "decDev_my_RenderFrame"  );

	 //
	 pLib->pf_ENC_d3d11_devVar_new  =  (  PF_ENC_d3d11_devVar_new  )GetProcAddress(  pLib->hDll,  "ENC_d3d11_devVar_new"  );
	 pLib->pf_ENC_d3d11_devVar_free  =  (  PF_ENC_d3d11_devVar_free  )GetProcAddress(  pLib->hDll,  "ENC_d3d11_devVar_free"  );
	 //  2016/05/02	
	 pLib->pf_encDev_YUVReader_myLoadNextFrame  =  (  PF_encDev_YUVReader_myLoadNextFrame  )GetProcAddress(  pLib->hDll,  "encDev_YUVReader_myLoadNextFrame"  );

	 //
	 pLib->pf_getSize_QIS_chromaKey_effect  =  (  PF_getSize_QIS_chromaKey_effect  )GetProcAddress(  pLib->hDll,  "getSize_QIS_chromaKey_effect"  );				
	 //
	 pLib->pf_initQisChromaKeyEffect  =  (  PF_initQisChromaKeyEffect  )GetProcAddress(  pLib->hDll,  "initQisChromaKeyEffect"  );
	 pLib->pf_exitQisChromaKeyEffect  =  (  PF_exitQisChromaKeyEffect  )GetProcAddress(  pLib->hDll,  "exitQisChromaKeyEffect"  );

	 //
	 pLib->pf_createQuad  =  (  PF_createQuad  )GetProcAddress(  pLib->hDll,  "createQuad"  );
	 pLib->pf_freeQuad  =  (  PF_freeQuad  )GetProcAddress(  pLib->hDll,  "freeQuad"  );

	 //
	 pLib->pf_getOrtho2DMats  =  (  PF_getOrtho2DMats  )GetProcAddress(  pLib->hDll,  "getOrtho2DMats"  );

	 //
	 pLib->pf_myCopyTex_rtt  =  GetProcAddress(  pLib->hDll,  "myCopyTex_rtt"  );

	 //
	 //  2015/10/30
	 pLib->pf_DXUTSaveTextureToFile  =  (  PF_DXUTSaveTextureToFile  )GetProcAddress(  pLib->hDll,  "my_DXUTSaveTextureToFile"  );


	 //
	 pLib->bOk  =  TRUE;

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
		 exitDynLib_isD3dFunc(  (  void  **  )&pLib  );
	 }
	 if  (  !iErr  )  {
		 *pp  =  pLib;
	 }

	 return  iErr;
}


//
int  exitDynLib_isD3dFunc(  void  **  pp  )
{
	if  (  !pp  ||  !*pp  )  return  0;


	DYN_LIB_isD3dFunc  *  pLib  =  (  DYN_LIB_isD3dFunc  *  )*pp;
	//
	pLib->bOk  =  FALSE;

	if  (  pLib->hDll  )  {
		FreeLibrary(  pLib->hDll  );
		pLib->hDll  =  NULL;
	}

	//
	free(  *pp  );  *pp   =  NULL;

	return  0;
}
#endif


//
int  isD3dFunc_init(  QIS_guiOpen  *  pGuiOpen,  void  *  pLibParam  )
{
	DYN_LIB_isD3dFunc  *  pLib  =  (  DYN_LIB_isD3dFunc  *  )pLibParam;
	if  (  !pLib  )  return  -1;

	if  (  !pLib->pf_qyDllInit  )  return  -1;

	//
	PARAM_qyDllInit  param  =  {0};
	param.pGuiOpen  =  pGuiOpen;
	pLib->pf_qyDllInit(  0,  0,  &param  );

	return  0;
}

//
void  *  get_ptr_isD3dFunc(  void  *  pLibParam,  int  propertyId  )
{
	DYN_LIB_isD3dFunc  *  pLib  =  (  DYN_LIB_isD3dFunc  *  )pLibParam;
	if  (  !pLib  )  return  NULL;

	//
	switch  (  propertyId  )  {
			case  CONST_qdcPropId_PF_DEC_d3d11_devVar_new:
				  return  pLib->pf_DEC_d3d11_devVar_new;
			case  CONST_qdcPropId_PF_DEC_d3d11_devVar_free:
				  return  pLib->pf_DEC_d3d11_devVar_free;
			case  CONST_qdcPropId_PF_decDev_my_RenderFrame:
				  return  pLib->pf_decDev_my_RenderFrame;
				  //
			case  CONST_qdcPropId_PF_ENC_d3d11_devVar_new:
				  return  pLib->pf_ENC_d3d11_devVar_new;
			case  CONST_qdcPropId_PF_ENC_d3d11_devVar_free:
				  return  pLib->pf_ENC_d3d11_devVar_free;
			case  CONST_qdcPropId_PF_encDev_YUVReader_myLoadNextFrame:
				  return  pLib->pf_encDev_YUVReader_myLoadNextFrame;
				  //
			case  CONST_qdcPropId_PF_getSize_QIS_chromaKey_effect:
				  return  pLib->pf_getSize_QIS_chromaKey_effect;
			case  CONST_qdcPropId_PF_initQisChromaKeyEffect:
				  return  pLib->pf_initQisChromaKeyEffect;
			case  CONST_qdcPropId_PF_exitQisChromaKeyEffect:
				  return  pLib->pf_exitQisChromaKeyEffect;
				  //
			case  CONST_qdcPropId_PF_createQuad:
				  return  pLib->pf_createQuad;
			case  CONST_qdcPropId_PF_freeQuad:
				  return  pLib->pf_freeQuad;
				  //
			case  CONST_qdcPropId_PF_getOrtho2DMats:
				  return  pLib->pf_getOrtho2DMats;
				  //
			case  CONST_qdcPropId_PF_myCopyTex_rtt:
				  return  pLib->pf_myCopyTex_rtt;

			default:
					break;
	}

	return  NULL;
}

