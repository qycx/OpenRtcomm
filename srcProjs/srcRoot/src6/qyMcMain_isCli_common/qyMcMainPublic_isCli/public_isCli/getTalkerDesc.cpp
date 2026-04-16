
#include	"stdafx.h"
#include	<stdio.h>
#include	<stddef.h>
#include	<time.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
//  #include	"myresource.h"
#include	"qyVDev.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyMcMainRealTimeMediaProc.h"

#include	"qyDynLib.h"
#include	"qyAvRecordPublic.h"

#include	<windows.h>
#include	<windef.h>
#include	<lmcons.h>
#ifndef  __WINCE__
	#include	<lmshare.h>
#endif
#include	<tlhelp32.h>
#include	<iphlpapi.h>

//  #include	"qwmDynFunc.h"

#include	"qmcCmdProc.h"

#include	"tmpCeLib.h"
#include	"qySqlFunc.h"
#include	"qyThread.h"
#include	"isCmdConst.h"
#include	"qyCusResTemp.h"
//
#include	"policyAvParams.h"


#include	"myDb.h"

#include	"isCliHelpPublic.h"
#include	"qyMessengerHelpPublic.h"
#include	"imgProcessPublic.h"
#include	"isCliD3dPublic.h"
#include	"qisWallsProc.h"
#include	"qmcTaskPublic.h"
#include	"qmcSharePublic.h"
#include	"dlgShareDynBmpsProc.h"
#include	"funcsForIsCliHelp.h"

#include	"qmcCommFunc_isCli.h"



 int  getTalkerDesc(  QY_MESSENGER_ID    idInfo,  TCHAR  *  talkerDesc,  unsigned  int  talkerDescCnt,  TCHAR  *  shortName,  unsigned  int  shortNameCnt  )
{
	 //  
	 QY_MC* pQyMc = (QY_MC*)g_pQyMc;
	 if (!pQyMc)  return  -1;

	 MC_VAR_isCli* pProcInfo = (MC_VAR_isCli*)pQyMc->get_pProcInfo();// pMisCnt->pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	if  (  pProcInfo->m_iCtxType  !=  CONST_ctxType_qmc  )  {
		return  -1;
	}
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	if (!pMisCnt)  return  -1;
	QY_MESSENGER_ID* pIdInfo = &idInfo;

	
	FUNCS_for_isCliHelp  *  pFuncs  =  (  FUNCS_for_isCliHelp  *  )pProcInfo->pFuncs_for_isCliHelp;//  QY_GET_FUNCS_for_isCliHelp(  );
	QM_dbFuncs  *  pDbFuncs  =  (  QM_dbFuncs  *  )pQyMc->p_g_dbFuncs;//  
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	TCHAR		talkerDescBuf[128  +  1]		=	_T(  ""  );
	TCHAR		displayNameBuf[128  +  1]		=	_T(  ""  );

	if  (  !pMisCnt  ||  !pIdInfo  )  return  -1;
		
	if  (  pIdInfo->ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
		lstrcpyn(  talkerDescBuf,  pMisCnt->talkerDesc,  mycountof(  talkerDescBuf  )  );
		lstrcpyn(  displayNameBuf,  pMisCnt->displayName,  mycountof(  displayNameBuf  )  );
		}
	else  {
		  QM_OBJQ_MEM				mem;
		  QMEM_MESSENGER_CLI	*	pQMem  =  NULL;

#if  0
		  if  (  !findQMemByKey(  0,  pMisCnt->pObjQ,  pIdInfo,  &mem  )  )  {
			  pQMem  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;
		  }
#endif
		  //  2014/12/23		  		
		  QY_MESSENGER_INFO			messengerInfo;
		 void					*	pDb		=	NULL;
		 int						i;

		 CQnmDb						tmpObjDb;						
		 pDb				=		tmpObjDb.getAvailableDb(  pQyMc->iDsnIndex_mainSys  );

		 //  
		 memset(  &messengerInfo,  0,  sizeof(  messengerInfo  )  );
		 //
		 lstrcpyn(  messengerInfo.misServName,  _T(  ""  ),  mycountof(  messengerInfo.misServName  )  );
		 messengerInfo.idInfo.ui64Id  =  pIdInfo->ui64Id;

		 //               
		 if  (  !procQmObjQ(  pProcInfo->pSgiParam,  (  QM_OBJQ  *  )pMisCnt->pObjQ,  pDb,  pQyMc->cfg.db.iDbType,  CONST_objType_messenger,  &messengerInfo,  &mem  )  )  {
			 pQMem  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;
		 }
		
		 //  2014/12/23
		 if  (  pQMem  )  {
			 if  (  !pQMem->talkerDesc[0]  )  {
				 QY_MESSENGER_REGINFO  regInfo;
			 
				 if  (  !g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pDb,  pQyMc->cfg.db.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab,  messengerInfo.misServName,  pIdInfo,  0,  &regInfo  )  )  memset(  &regInfo,  0,  sizeof(  regInfo  )  );
			 
				 MY_REG_DESC				desc;
		 
				 regInfo2Desc(  0,  &regInfo,  &desc,  pQMem->talkerDesc,  mycountof(  pQMem->talkerDesc  ),  pQMem->displayName,  mycountof(  pQMem->displayName  )  );
			 }
		 }

		  //
		  if  (  pQMem  )  {				
			  lstrcpyn(  talkerDescBuf,  pQMem->talkerDesc,  mycountof(  talkerDescBuf  )  );				
			  lstrcpyn(  displayNameBuf,  pQMem->displayName,  mycountof(  displayNameBuf  )  );				  			  
		  }
	}	

	if  (  !talkerDescBuf[0]  )  _sntprintf(  talkerDescBuf,  mycountof(  talkerDescBuf  ),  _T(  "(%I64u)"  ),  pIdInfo->ui64Id  );	
	if  (  !displayNameBuf[0]  )  _sntprintf(  displayNameBuf,  mycountof(  displayNameBuf  ),  _T(  "(%I64u)"  ),  pIdInfo->ui64Id  );

	//

//  errLabel:
			      
	if  (  talkerDesc  &&  talkerDescCnt  )  lstrcpyn(  talkerDesc,  talkerDescBuf,  talkerDescCnt  );
	if  (  shortName  &&  shortNameCnt  )  lstrcpyn(  shortName,  displayNameBuf,  shortNameCnt  );

	return  0;
}


 //
 int  getTalkerDesc(QY_MESSENGER_ID idInfo, unsigned  int* puiObjType, TCHAR* grpName, int  cntof_grpName, QY_MESSENGER_ID* pidInfo_creator,
	 TCHAR* dw, int  cntof_dw, TCHAR* bm, int  cntof_bm, TCHAR* syr, int  cntof_syr)
 {
	 return  getTalkerDesc(idInfo, puiObjType, grpName, cntof_grpName, pidInfo_creator, mynull, dw, cntof_dw, bm, cntof_bm, syr, cntof_syr);
 }



 //
 int  getTalkerDesc(QY_MESSENGER_ID idInfo, unsigned  int* puiObjType, TCHAR* grpName, int  cntof_grpName, QY_MESSENGER_ID* pidInfo_creator, unsigned  short* p_grp_usSubtype,
		 TCHAR* dw, int  cntof_dw, TCHAR* bm, int  cntof_bm, TCHAR* syr, int  cntof_syr)
 {
	 int  iErr = -1;
	 CCtxQyMc* pQyMc = g_pQyMc;
	 CCtxQmc* pProcInfo = (CCtxQmc  *  )pQyMc->get_pProcInfo();
	 MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

	 //
	 QM_dbFuncs* pDbFuncs = (QM_dbFuncs*)pQyMc->p_g_dbFuncs;//  
	 if (!pDbFuncs)  return  -1;
	 QM_dbFuncs& g_dbFuncs = *pDbFuncs;

	 QY_MESSENGER_INFO  messengerInfo;
	 QY_MESSENGER_REGINFO  regInfo;

	 //
	 if (!g_dbFuncs.pf_bGetMessengerInfoBySth(pDbFuncs, pQyMc->gui.pDb, pQyMc->cfg.db.iDbType, CONST_fieldIdTable_en, _T(""), &idInfo, 0, &messengerInfo, &regInfo, NULL, mynull)) {
		 memset(&messengerInfo, 0, sizeof(messengerInfo));
		 memset(&regInfo, 0, sizeof(regInfo));
	 }
	 if  (  puiObjType  )  *puiObjType = messengerInfo.uiType;
	 if (messengerInfo.uiType == CONST_objType_imGrp) {
		 IM_GRP_INFO  grpInfo;

		 if (!g_dbFuncs.pf_bGetImGrpInfoBySth(pQyMc->gui.pDb, pQyMc->cfg.db.iDbType, _T(""  ), &idInfo, &grpInfo))  memset(&grpInfo, 0, sizeof(grpInfo));

		 //
		 safeTcsnCpy(grpInfo.name, grpName, cntof_grpName);
		 if (pidInfo_creator)  pidInfo_creator->ui64Id = grpInfo.idInfo_creator.ui64Id;
		 if (p_grp_usSubtype)*p_grp_usSubtype = grpInfo.usSubtype;
	 }
	 else {
		 MY_REG_DESC  desc;

		 regInfo2Desc(0, &regInfo, &desc, NULL, 0, NULL, 0);
		 //
		 safeTcsnCpy(desc.pDw, dw, cntof_dw);
		 safeTcsnCpy(desc.pBm, bm, cntof_bm);
		 safeTcsnCpy(desc.pSyr, syr, cntof_syr);
	 }



	 iErr = 0;

 errLabel:
	 return  iErr;
 }

