

#include	"stdafx.h"
#include	<tchar.h>
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

//
#ifdef  __isCli__
#include	"ctxQmc.h"
#endif 


//
#include	"myresource.h"
#if  !defined(  __isCli__  )  &&  !defined(  __APP_qyMc_touchscreen__  )	//  __SUPPORT_SERV__
	#include	"dlgMcLogon.h"
#endif

#ifdef  __WINCE__
#ifndef  __TEST__
		#include	"ceMenuBar.h"
#endif
#endif

#ifdef  __isCli__
#include	"DlgMcClientLogon.h"
#include <ctxQmcTmpl.h>

extern int  newstartQThreadToSaveIC(MC_VAR_common* pProcInfo);
extern int  newstartQThreadToCheckICFile(MC_VAR_common* pProcInfo);
#endif

extern bool  createSaveICPath();

//
BOOL	bQyMcLogon(  QY_MC  * pQyMc,  PF_showDlgMcLogon  pf_showDlgLogon,  PARAM_showDlgMcLogon  *  pParam  )
{
	 BOOL				bRet			=	FALSE;
	 QY_OBJ_DB		*	pObjDb			=	NULL;

	 //
	 if  (  !pQyMc  )  {
		 showInfo_open0(  0,  0,  _T(  "bQyMcLogon failed, pQyMc is null"  )  );
		 return  FALSE;
	 }

	 //
	 if  (  pQyMc->iAppType  !=  CONST_qyAppType_client  )  {
		 #if  !defined(  __isCli__  )  &&  !defined(  __APP_qyMc_touchscreen__  )	//  __SUPPORT_SERV__
				  CDlgMcLogon		dlg;
				  if  (  IDOK  !=  dlg.DoModal( )  )  goto  errLabel;
		 #endif
		 }
	 else  {
			//
			if  (  !pf_showDlgLogon  )  {
				#ifdef  __DEBUG__
						traceLog((TCHAR*)  _T(  "bQyMcLogon failed, pf_showDlgLogon is null"  )  );
			    #endif
				goto  errLabel;
			}
			//  if  (  pf_showDlgLogon(  pQyMc->g_hInst,  pQyMc->gui.hMainWnd,  0  )  )  goto  errLabel;
			//  2016/09/16
			if  (  pf_showDlgLogon(  pQyMc->g_hInst,  pQyMc->gui.hMainWnd,  pQyMc,  pParam  )  )  goto  errLabel;

	 }
	 
	 //  2005/09/30, 加上了对用户权限的校验
	 if  (  !pQyMc->curUsrInfo.right.bAdmin  &&  !pQyMc->curUsrInfo.right.bXtpz  &&  !pQyMc->curUsrInfo.right.bRzsj  )  {
		 traceLogA(  (char*)  "not permitted"  );  
		 goto  errLabel;
	 }
		 
	 pObjDb  =  getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  );
	 if  (  !pObjDb  )  goto  errLabel;
	 pObjDb->pLogObjDb  =  pObjDb;		//  指向自己，因为是用来记日志的
	 pObjDb->pUsrInfo	=	&pQyMc->curUsrInfo;

	 bRet  =  TRUE;
	 
errLabel:

	 if  (  !bRet  )  {
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pQyMc->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bQyMcLogon failed."  )  );
	 }

	 if  (  bRet  )  {
		 pQyMc->bLogon = TRUE;	 
		 pQyMc->dwTickCnt_logon  =  myGetTickCount( NULL );

		 //  2016/09/05
#if  1   //  def  __DEBUG__
		 QM_dbFuncs  *  pDbFuncs  =  NULL;
#endif

		 //
#ifdef  __DEBUG__
		 int testHaha();

		 //testHaha();
#endif

		 //

		 //
		 qnmLogOpEvent(  pQyMc->iServiceId,  pDbFuncs,  pObjDb,  CONST_qyEventType_nm_logon,  _T(  ""  )  );
#ifdef  __isCli__
		 MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();

		 newstartQThreadToSaveIC(pProcInfo);
		 newstartQThreadToCheckICFile(pProcInfo);
#endif 

		/* if (createSaveICPath()) {
			 newstartQThreadToSaveIC(pProcInfo);
			 newstartQThreadToCheckICFile(pProcInfo);
		 }
		 else {
			 showInfo_open0(0, _T("save_ic"), _T("createSaveICPath failed!"));
		 }*/

		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  pQyMc->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bQyMcLogon ok."  )  );
	 }

	 return  bRet;

}


 void  old_qyMcLogoff(  QY_MC  *  pQyMc  )
{
	 if  (  !pQyMc->bLogon  )  return;

	 QY_OBJ_DB	*	pObjDb	=	NULL;

	 //  2016/09/05
#if  1  //  def  __DEBUG__
	 QM_dbFuncs  *  pDbFuncs  =  NULL;
#endif

	 //
	 pObjDb  =  getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  );


	 //
	 qnmLogOpEvent(  pQyMc->iServiceId,  pDbFuncs,  pObjDb,  CONST_qyEventType_nm_logoff,  _T(  ""  )  );

	 memset(  &pQyMc->curUsrInfo,  0,  sizeof(  pQyMc->curUsrInfo  )  );

	 pQyMc->bLogon  =  FALSE;

	 return;
}

