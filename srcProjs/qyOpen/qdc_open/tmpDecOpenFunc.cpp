

#include	"stdafx.h"

#include	<mmsystem.h>
#include	<tchar.h>

#include	"qdcOpenCommon.h"
#include	"qySyncObj.h"
#include	"genericQueue.h"

#include	"tmpGuiOpenFunc.h"
#include	"dec_d3d11_dev_open.h"


//

extern  BOOL				g_bUsing_sharedTex_dec;
extern  BOOL				g_bShowDec_sharedTexStatus;			//  2016/04/09
extern  unsigned  int		g_uiXql_player;		



//
 //  2016/04/26
 PF_DEC_d3d11_devVar_new	g_pf_DEC_d3d11_devVar_new  =  NULL;
 PF_DEC_d3d11_devVar_free	g_pf_DEC_d3d11_devVar_free  =  NULL;
 void  *					g_pf_decDev_my_RenderFrame  =  NULL;

//
//
 extern  "C"  int  tmpDec_setFuncs(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	int  iErr  =  -1;

	//  2016/04/26
	if  (  !pQdcObjInfo->pf_qoi_getPtrProperty  )  {
		tmp_showInfo(  (TCHAR*)_T(  "qdcInitEncV failed, qoi_getPtr is null"  )  );
		return  -1;
	}
	//  2016/04/26
	if  (  !pQdcObjInfo->pf_qoi_getPtrProperty  )  {
		tmp_showInfo(  (TCHAR*)_T(  "qdcInitDecV failed, qoi_getPtr is null"  )  );
		return  -1;
	}
	g_pf_DEC_d3d11_devVar_new  =  (  PF_DEC_d3d11_devVar_new  )pQdcObjInfo->pf_qoi_getPtrProperty(  pQdcObjInfo,  CONST_qdcPropId_PF_DEC_d3d11_devVar_new  );
	if  (  !g_pf_DEC_d3d11_devVar_new  )  {
		tmp_showInfo(  (TCHAR*)_T(  "qdcInitDecV failed, g_pf_DEC_d3d11_devVar_new is null"  )  );
		return  -1;
	}
	g_pf_DEC_d3d11_devVar_free  =  (  PF_DEC_d3d11_devVar_free  )pQdcObjInfo->pf_qoi_getPtrProperty(  pQdcObjInfo,  CONST_qdcPropId_PF_DEC_d3d11_devVar_free  );
	if  (  !g_pf_DEC_d3d11_devVar_free  )  {
		tmp_showInfo(  (TCHAR*)_T(  "qdcInitDecV failed, g_pf_DEC_d3d11_devVar_free is null"  )  );
		return  -1;
	}
	g_pf_decDev_my_RenderFrame  =  (  PF_decDev_my_RenderFrame  )pQdcObjInfo->pf_qoi_getPtrProperty(  pQdcObjInfo,  CONST_qdcPropId_PF_decDev_my_RenderFrame  );
	if  (  !g_pf_decDev_my_RenderFrame  )  {
		tmp_showInfo(  (TCHAR*)_T(  "qdcInitDecV failed, g_pf_decDev_my_RenderFrame is null"  )  );
		return  -1;
	}
	iErr  =  0;
errLabel:
	return  iErr;
}


//
 extern  "C"  int  tmpDec_qdcGetProp(  int  iPropId,  void  *  pParam_input,  void  *  pParam_output  )
 {
	 int  iErr  =  -1;
	 TCHAR  tBuf[128]  =  _T(  ""  );

	 //
	 if  (  !pParam_output  )  return  -1;

	 //
	 switch  (  iPropId  )  {
			 case  CONST_qdcPropId_bSupport_sharedTex_dec:  {
				   BOOL  *  pbVal  =  (  BOOL  *  )pParam_output;		   

				   //  2015/09/28
				   *pbVal  =  g_bUsing_sharedTex_dec;
				   //
				   }
				   //
				   break;
			 case  CONST_qdcPropId_bShowDec_sharedTexStatus:  {
				   BOOL  *  pbVal  =  (  BOOL  *  )pParam_output;
				   
				   //
				   *pbVal  =  g_bShowDec_sharedTexStatus;
				   }
				   break;
			 case  CONST_qdcPropId_uiXql_player:  {  //  2016/04/14
				   unsigned  int  *  puiXql_player  =  (  unsigned  int  *  )pParam_output;
				   //
				   *puiXql_player  =  g_uiXql_player;
				   }
				   break;

			 default:
				    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "qdcGetProp failed, unprocessed propId %d"  ),  iPropId  );
					tmp_showInfo(  tBuf  );
					goto  errLabel;
	 }


	 iErr  =  0;
errLabel:
	 return  iErr;
 }


 //  2016/04/09
 extern  "C"  int  tmpDec_qdcSetProp(  int  iPropId,  void  *  pParam_input,  void  *  pParam_output  )
 {
	 int  iErr  =  -1;

	 //
	 if  (  !pParam_input  )  return  -1;

	 //
	 switch  (  iPropId  )  {
			 case  CONST_qdcPropId_bShowDec_sharedTexStatus:  {
				   BOOL  *  pbVal  =  (  BOOL  *  )pParam_input;
				   
				   //
				   g_bShowDec_sharedTexStatus  =  *pbVal;

				   //
				   }
				   //
				   break;
			 case  CONST_qdcPropId_uiXql_player:  {
				   unsigned  int  *puiXql_player  =  (  unsigned  int  *  )pParam_input;
				   //
				   g_uiXql_player  =  *puiXql_player;
				   //
				   }
				   break;
				   //
			 default:
				    tmp_showInfo(  (TCHAR*)_T(  "qdcSetProp failed, unprocessed propId"  )  );
					goto  errLabel;
	 }


	 iErr  =  0;
errLabel:
	 return  iErr;
 }



