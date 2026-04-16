

#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"
#include	"qmcDmoPublic.h"
#include	"qmcCmdProc.h"
#include	"tmpCeLib.h"
//  #include	"myfourcc.h"
#include	"module_qisCamCap.h"
#include	"isCmdConst.h"
#include	"qyOpenShellCommon.h"
#include	"qyCusResTemp.h"
#include	"policyAvParams.h"

#include	"qmcVideoCapture_rtsp.h"

#include	"isCliHelpPublic.h"
//#include	"rtspCliHelpPublic.h"
#include	"qmcObjVarInfo.h"
#include	"funcsForIsCliHelp.h"
#include	"dlgDynBmpsProc.h"




//
int  getSize_QMC_objVar_info(  )
{
	return  sizeof(  QMC_objVar_info  );
}


//
 QMC_objVar_info  *  getQmcObjVarInfoByIndex(  MC_VAR_common  *  pProcInfoParam,  int  index  )
{
	if  (  pProcInfoParam->m_iCtxType  !=  CONST_ctxType_qmc  )  return  NULL;
	MC_VAR_isCli  *  pProcInfo  =  (  MC_VAR_isCli  *  )pProcInfoParam;

	QMC_objVar_info  *  pTalkerInfos  =  (  QMC_objVar_info  *  )pProcInfo->pQmcObjVarInfos;

	if  (  index  <  0  ||  index  >=  pProcInfo->cfg.usMaxCnt_qmcObjVarInfos  )  return  NULL;

	QMC_objVar_info				*	pTalkerInfo	=	&pTalkerInfos[index];

	return  pTalkerInfo;
}


 //  2017/10/04
 int  getObjVarInfoIndexByWnd(  MC_VAR_common  *  pProcInfoParam,  HWND  hWnd  )
 {
	 if  (  pProcInfoParam->m_iCtxType  !=  CONST_ctxType_qmc  )  return  NULL;
	 MC_VAR_isCli  *  pProcInfo  =  (  MC_VAR_isCli  *  )pProcInfoParam;

	 int  i;
	 for  (  i  =  0;  i  <  pProcInfo->cfg.usMaxCnt_qmcObjVarInfos;  i  ++  )  {
		  QMC_objVar_info  *  pObjVarInfo  =  getQmcObjVarInfoByIndex(  pProcInfo,  i  );
		  if  (  !pObjVarInfo  )  continue;
		  //
		  if  (  !pObjVarInfo->bUsed  )  continue;
		  //
		  if  (  pObjVarInfo->var.hWnd  ==  hWnd  )  break;
	 }
	 if  (  i  ==  pProcInfo->cfg.usMaxCnt_qmcObjVarInfos  )  return  -1;
	 
	 //
	 return  i;
 }



  //
 BOOL  bNoObjVarInfoExists(  MC_VAR_isCli  *  pProcInfo  )
 {
	 BOOL			bRet		=	FALSE;
	 //
	 int  i;
	 
	 //
	 if  (  !pProcInfo  )  return  FALSE;

	 //
	 for  (  i  =  0;  i  <  pProcInfo->cfg.usMaxCnt_qmcObjVarInfos;  i  ++  )  {
		  QMC_objVar_info  *  pTalkerInfo  =  getQmcObjVarInfoByIndex(  pProcInfo,  i  );

		  if  (  pTalkerInfo->bUsed  )  {
			  //
			  if (0) {
				  MACRO_qyAssert(0, _T("talkerInfo does not be freed"));
			  }
			  //
			  traceLog((TCHAR*)_T("talkerInfo does not be freed"));
			  //
			  break;
		  }
	 }
	 if  (  i  ==  pProcInfo->cfg.usMaxCnt_qmcObjVarInfos  )  {
		 bRet  =  TRUE;
	 }

	 return  bRet;
 }


 //
 //
void  *  newQmcObjVarData(  unsigned  int  uiType  )
{
	int							iErr	=	-1;
	QMC_objVarData_common	*	p		=  NULL;
	int							len		=  0;

	switch  (  uiType  )  {
			case  CONST_objVarDataType_dlgTalk:
				  len  =  sizeof(  DLG_TALK_var  );
				  break;
			case  CONST_objVarDataType_dlgDynBmps:  //  2015/11/20
				  len  =  sizeof(  DLG_dynBmps_var  );
				  break;
			default:
				    len  =  sizeof(  QMC_objVarData_common  );
					MACRO_qyAssert(  0,  _T(  "newTalkData failed"  )  );
					break;
	}
	p  =  (  QMC_objVarData_common  *  )mymalloc(  len  );
	if  (  !p  )  return  NULL;
	memset(  p,  0,  len  );
	p->uiType  =  uiType;


	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		freeQmcObjVarData(  (  void  **  )&p  );  
	}
	return  iErr  ?  NULL  :  p;
}



 //
 void  freeQmcObjVarData(  void  **  ppObjVarData  )
 {
	 if  (  !ppObjVarData  )  return;
	 QMC_objVarData_common    *  p  =  (  QMC_objVarData_common  *  )*ppObjVarData;

	 switch  (  p->uiType  )  {
			 default:
					break;
	 }

	 if  (  p  )  {
		 free(  p  );
		 *ppObjVarData  =  NULL;
	 }

	 return;
 }


 //  2015/11/11
 int  newQmcObjVarInfoIndex(  MC_VAR_isCli  *  pProcInfo,  unsigned  int  uiTalkerDataType,  HWND  hTalker  )
 {
	 int				iErr  =  -1;
	 //
	 if  (  !pProcInfo  )  return  -1;
	 FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	 if  (  !pFuncs  )  return  -1;
	 //
	 void	*	pTalkerData  =  NULL;
	 QMC_objVar_info  *  pTalkerInfo  =  NULL;;
	 int  i;

	 //
	 tryToFreeQmcObjVarInfos(   pProcInfo );


	 //  Note: start from 1.
	 for  (  i  =  1;  i  <  pProcInfo->cfg.usMaxCnt_qmcObjVarInfos;  i  ++  )  {
		  pTalkerInfo  =  getQmcObjVarInfoByIndex(  pProcInfo,  i  );
		  if  (  !pTalkerInfo->bUsed  )  break;
	 }
	 if  (  i  ==  pProcInfo->cfg.usMaxCnt_qmcObjVarInfos  )  {
		 showInfo_open0(  0,  0,  _T(  "newTalkerInfoIndex failed: no free index_talkerInfo"  )  );
		 goto  errLabel;
	 }

	 //
	 MACRO_qyAssert(  !pTalkerInfo->var.pData,  _T(  "talkerData is not null"  )  );

	 //
	 pTalkerData  =  newQmcObjVarData(  uiTalkerDataType  );
	 if  (  !pTalkerData  )  goto  errLabel;

	 //
	 memset(  &pTalkerInfo->var,  0,  sizeof(  pTalkerInfo->var  )  );
	 pTalkerInfo->var.hWnd  =  hTalker;

	 //
	 pTalkerInfo->var.pData  =  pTalkerData;  pTalkerData  =  NULL;

	 //
	 //  pTaskInfo->uiTranNo  =  getuiNextTranNo(  0,  0,  0  );
	 syncMtCnt_start(  &pTalkerInfo->syncMtCnt,  getuiNextTranNo  );
	 //
	 pTalkerInfo->bUsed  =  TRUE;

	 //
	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "newTalkerInfo %d ok"  ),  i  );
	 
	 //
	 iErr  =  0;

errLabel:

	 if  (  pTalkerData  )  {
		 freeQmcObjVarData(  &pTalkerData  );
	 }

	 return  iErr  ?  iErr  :  i;
 }


 //
  int  freeQmcObjVarInfoIndex(  MC_VAR_isCli  *  pProcInfo,  int  index_talkerInfo  )
 {
	 int				iErr  =  -1;
	 
	 //
	 if  (  !pProcInfo  )  return  -1;
	 

	 //	
	 TCHAR  tBuf[128];
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "freeQmcObjVarInfoIndex %d enters"  ),  index_talkerInfo  );
	 showInfo_open0(  0,  0,  tBuf  );

	 //
	 QMC_objVar_info  *  pTalkerInfo  =  getQmcObjVarInfoByIndex(  pProcInfo,  index_talkerInfo  );
	 if  (  !pTalkerInfo  )  return  -1;
	 if  (  !pTalkerInfo->bUsed  )  return  0;

	 //  2015/11/15
	 pTalkerInfo->var.bInvalid  =  TRUE;

	 //  2014/09/29
	 unsigned  int  tn  =  0;
	 CQySyncObj  syncObj;
	 if  (  syncMtCnt_wLock_noWait(  &pTalkerInfo->syncMtCnt,  NULL,  &syncObj,  &tn  )  )  return  -1;

	 //
	 freeQmcObjVarData(  &pTalkerInfo->var.pData  );  

	 //
	 memset(  &pTalkerInfo->var,  0,  sizeof(  pTalkerInfo->var  )  );

	 //
	 pTalkerInfo->bUsed  =  FALSE;
	 	 
	 //	
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "freeQmcObjVarInfoIndex %d leaves ok."  ),  index_talkerInfo  );
	 showInfo_open0(  0,  0,  tBuf  );


	 return  0;

 }


   //  2014/09/24. 
 int  tryToFreeQmcObjVarInfos(  MC_VAR_isCli  *  pProcInfo  )
 {
	 int				iErr  =  -1;
	 int				i;

	 if  (  !pProcInfo  )  return  -1;


	 for  (  i  =  0;  i  <  pProcInfo->cfg.usMaxCnt_qmcObjVarInfos;  i  ++  )  {
		  QMC_objVar_info  *  pTalkerInfo  =  getQmcObjVarInfoByIndex(  pProcInfo,  i  );
		  if  (  !pTalkerInfo->bUsed  )  continue;
		  //
		  if  (  !pTalkerInfo->var.bInvalid  )  continue;

		  //
		  freeQmcObjVarInfoIndex(  pProcInfo,  i  );
	 }
	 
	 //
	 iErr  =  0;
errLabel:
	 return  iErr;
 }







  //////////////////////////////
 D3D_talkerData_cfg  *  get_D3D_talkerData_cfg(  MC_VAR_common  *  pProcInfo,  int  iIndex_talkerInfo,  CQySyncCnt  *  pSyncCnt  )
{
	int  iErr  =  -1;
	D3D_talkerData_cfg  *  pD3dWallData_talker_cfg  =  NULL;

  	QMC_objVar_info  *  pTalkerInfo  =  getQmcObjVarInfoByIndex(  pProcInfo,  iIndex_talkerInfo  );
	if  (  !pTalkerInfo  )  goto  errLabel;
	
	//
	if  (  syncMtCnt_rLock(  &pTalkerInfo->syncMtCnt,  pSyncCnt,  _T(  "get_D3D_talkerData_cfg"  )  )  )  goto  errLabel;

	//
	if  (  !pTalkerInfo->bUsed  )  goto  errLabel;
	
	//  2015/11/16
	if  (  pTalkerInfo->var.bInvalid  )  goto  errLabel;

	//
	DLG_TALK_var* pDlgTalkVar;pDlgTalkVar = (DLG_TALK_var*)pTalkerInfo->var.pData;
	if  (  !pDlgTalkVar  )  goto  errLabel;
	if  (  pDlgTalkVar->uiType  !=  CONST_objVarDataType_dlgTalk  )  goto  errLabel;
	pD3dWallData_talker_cfg  =  &pDlgTalkVar->d3d_talkerData_cfg;

	iErr  =  0;
errLabel:

	return  iErr  ?  NULL  :  pD3dWallData_talker_cfg;
 }


 //  2015/11/26
 void  *  getQmcObjVarDataByIndex(  MC_VAR_common  *  pProcInfo,  int  iIndex_objVarInfo,  CQySyncCnt  *  pSyncCnt,  int  objVarDataType,  LPCTSTR  hint  )
{	 
	int  iErr  =  -1;
	QMC_objVarData_common  *  pObjVarData  =  NULL;

	//
	if  (  !hint  )  hint  =  _T(  ""  );


  	QMC_objVar_info  *  pTalkerInfo  =  getQmcObjVarInfoByIndex(  pProcInfo,  iIndex_objVarInfo  );
	if  (  !pTalkerInfo  )  goto  errLabel;
	
	//
	if  (  syncMtCnt_rLock(  &pTalkerInfo->syncMtCnt,  pSyncCnt,  _T(  "get_D3D_talkerData_cfg"  )  )  )  {
		#ifdef  __DEBUG__
				TCHAR  tBuf[128]  =  _T(  ""  );
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "getQmcObjVarDataByIndex failed, syncMtCnt_rLock failed, %s"  ),  hint  );
				traceLog(  tBuf  );
		#endif
		goto  errLabel;
	}

	//
	if  (  !pTalkerInfo->bUsed  )  goto  errLabel;
	
	//  2015/11/16
	if  (  pTalkerInfo->var.bInvalid  )  goto  errLabel;

	//
	pObjVarData  =  (  QMC_objVarData_common  *  )pTalkerInfo->var.pData;
	if  (  !pObjVarData  )  goto  errLabel;
	if  (  objVarDataType  )  {
		if  (  pObjVarData->uiType  !=  objVarDataType  )  goto  errLabel;
	}

	iErr  =  0;
errLabel:

	return  iErr  ?  NULL  :  pObjVarData;
 
 }
