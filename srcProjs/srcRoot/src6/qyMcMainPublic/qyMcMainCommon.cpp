
#include	"stdafx.h"
#include	<tchar.h>
#include	"qyMcMainCommon.h"
#include	"myresource.h"
#include	"qyCusResTemp.h"



 






 //
  int  tmpHandler_listProcedObjs(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int			iErr	=	-1;	
	 QY_MC		*	pQyMc				=	(  QY_MC  *  )p0;
	 if  (  !pQyMc  )  return  -1;

	 CQyString		str;
	 char			regValName[256];
	 int			id;
	 WCHAR			connectStr[1024];
	 char			buf[1024];
	 DWORD			len;

	 QY_PC_REGISTRYVAL	*	pVal	=	(  QY_PC_REGISTRYVAL  *  )p2;
	 if  (  pVal->ucbKey  )  goto  errLabel;
	 if  (  pVal->iValType  !=  REG_SZ  )  goto  errLabel;
	 str  =  CQyString(  (char*)CONST_regValName_procedSysStr  );
	 //  traceLogA(  "str len is %d",  str.GetLength(  )  );
	 if  (  _tcsnicmp(  pVal->wCfgName,  str,  str.GetLength(  )  )  )  goto  errLabel;
	 
	 QY_REG	reg;
	 memset(  &reg,  0,  sizeof(  reg  )  );	
	 //	if  (  safeStrCpy(   pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  reg.rootKey,  sizeof(  reg.rootKey  )  )  )  goto  errLabel;
	 lstrcpyn(  reg.rootKey,  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  mycountof(  reg.rootKey  )  );
	 reg.pEncCtx  =  &pQyMc->encCtx;

	 myTChar2Str(  pVal->wCfgName,  regValName,  mycountof(  regValName  )  );

	 id  =  atol(  regValName  +  strlen(  CONST_regValName_procedSysStr  )  );

	 connectStr[0]  =  0;
	 len  =  mycountof(  buf  );
	 if  (  qyGetRegDataEx(  &reg,  CQyString(  regValName  ),  buf,  &len  )  )  goto  errLabel;
	 buf[len]  =  0;
	 myUtf82WChar(  buf,  connectStr,  mycountof(  connectStr  )  );

	 if  (  id  >=  mycountof(  pQyMc->procedObjDbs  )  )  goto  errLabel;

	 if  (  pQyMc->procedObjDbs[id].ucbUsed  )  goto  errLabel;

	 QY_OBJ_DB	obj;
	 
	 memset(  &obj,  0,  sizeof(  obj  )  );
	 //
	 unsigned  long		ulOpenOptions; ulOpenOptions = 0;
	 ulOpenOptions  =  get_CONST_qyDbOpenOptions(  );
	 //
	 if  (  parseDbParams(  connectStr,  ulOpenOptions,  &obj.cfg  )  )  goto  errLabel;
	 obj.iDsnIndex  =  id;
	 obj.ucbUsed  =  TRUE;

	 memcpy(  &pQyMc->procedObjDbs[id],  &obj,  sizeof(  pQyMc->procedObjDbs[id]  )  );
 

errLabel:
	 return  0;		//  这里返回为0， 以避免枚举中断
}




 int  getProcedObjsCfg(  QY_MC  *  pQyMc  )
{
	 int			id;

	 //
	 if  (  !pQyMc  )  return  -1;

	 //
	 memset(  pQyMc->procedObjDbs,  0,  sizeof(  pQyMc->procedObjDbs  )  );

	 //  把基本系统的配置放入procedObjDbs中，放在第一个单元中（id=0），不能修改和删除
	 id  =  0;  
	 memcpy(  &pQyMc->procedObjDbs[id].cfg,  &pQyMc->cfg.db,  sizeof(  pQyMc->procedObjDbs[id].cfg  )  );
	 lstrcpyn(  pQyMc->procedObjDbs[id].cfg.sysName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_baseSystem  ),  mycountof(  pQyMc->procedObjDbs[id].cfg.sysName  )  );
	 setProcedObjSth(  &pQyMc->procedObjDbs[id]  );
	 pQyMc->procedObjDbs[id].ucbUsed		=  TRUE;
	 //
	 pQyMc->iDsnIndex_mainSys  =  id;	//  2006/12/23

	 enumReg(  &pQyMc->env,  0,  HKEY_LOCAL_MACHINE,  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,   tmpHandler_listProcedObjs,  pQyMc,  0  );
	 

	 return  0;
}


 int  setProcedObjSth(  QY_OBJ_DB  *  pObjDb  )
{
	int					iErr			=		-1;

	switch  (  pObjDb->cfg.iSystemId  )  {			//  作产品功能上的分流,  2006/06/12
			 case  CONST_qySystemId_netMc2:
				   pObjDb->ucbShowPcOpNode		=	TRUE;
				   pObjDb->ucbDisplayPcStatus		=	TRUE;
				   pObjDb->ucbPcRegistryMgr		=	TRUE;
				   break;
			 case  CONST_qySystemId_assetMgr:
				   pObjDb->ucbPcAssetMgr			=  TRUE;
				   break;
			 case  CONST_qySystemId_messenger:
				   if  (  pObjDb->cfg.iAppType  !=  CONST_qyAppType_client  )  {
					   pObjDb->ucbShowPcOpNode		=	TRUE;
					   pObjDb->ucbDisplayPcStatus		=	TRUE;
				   }
				   break;
			 default:	
				     break;
	 }

	iErr  =  0;
//  errLabel:
	return  iErr;
}

 //
  int  loadProcedObj(  QY_MC  *  pQyMc,  void  *  p1,  void  *  p2  )
{
	 int			iErr	=	-1;
	 int			index	=	(  int  )p2;
	 QY_OBJ_DB	*	pObjDb	=	NULL;

	 //
	 if  (  !pQyMc  )  return  -1;

	 //
	 if  (  index  >=  (  int  )getProcedObjDbsMaxCnt(   pQyMc  )  )  return  -1;
	 pObjDb  =  &getProcedObjDbs(  pQyMc  )[index];
	 if  (  !pObjDb  )  return  -1;
	 if  (  pObjDb->ucbLoaded  )  return  0;

	 //  2012/07/13
	 if  (  pObjDb->cfg.iDbType  ==  CONST_dbType_myDb  )  {
		 #ifdef  __DEBUG__
				 traceLog(  (TCHAR*)_T(  "loadProcedObj failed, myDb is not supported"  )  );
		 #endif
		 return  -1;
	 }

	 //
	 if  (  initQyMcDb(  0,  0,  pObjDb  )  )  goto  errLabel;

	 {
         QY_SYSTEMINFO_RCD	systemInfo;
	
		 if  (  bGetSystemInfo(  pObjDb->pDb,  pObjDb->cfg.iDbType,  &systemInfo  )  )  {
             pObjDb->cfg.iAppType  =  systemInfo.iAppType;
		 }
	 }

	 if  (  setProcedObjSth(  pObjDb  )  )  goto  errLabel;

	 pObjDb->pLogObjDb	=	getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  );
	 pObjDb->pUsrInfo		=	&pQyMc->curUsrInfo;

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
		 if  (  pObjDb->ucbLoaded  )  exitQyMcDb(  0,  0,  pObjDb  );
	 }

	 return  iErr;
}
