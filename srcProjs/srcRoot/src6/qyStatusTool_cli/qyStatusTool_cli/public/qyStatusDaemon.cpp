
#include	"stdafx.h"
#include	"qyStatusDaemon.h"
#include	"qyPs.h"


	CQyStatusDaemon::CQyStatusDaemon( ):CQyGenericDaemon()
	{
		memset(  &m_var,  0,  sizeof(  m_var  )  );
	}


	CQyStatusDaemon::~CQyStatusDaemon(  )
	{
	}



	int	CQyStatusDaemon::init(  )
	{
		return  0;
	}


	int	CQyStatusDaemon::start(  )
	{
		int  iErr  =  -1;
		int  index;

		//
		int  iType_pParentParam  =  CONST_ctxType_qyStatus;

		//
		for  (  index  =  0;  ;  index  ++  )  {
		  QY_SERVICE_INFO	*	pServiceInfo	=	(  QY_SERVICE_INFO  *  )getSpecialPtrProperty(  CONST_qyPropertyId_serviceInfo_byIndex,  (  void  *  )index,  0  );
		  void				*	pMtSock			=	0;
		  //
		  if  (  !pServiceInfo  )  break;	//  Ã¶¾Ù½áÊøÁË
		  if  (  !pServiceInfo->cfg.iServiceId  )  continue;	//  Ã»ÓÐÏàÓ¦µÄiServiceId
		  
		  switch  (  pServiceInfo->cfg.mtServWork.iType  )  {
				  default:
					      if  (  initQyMtSock(  NULL,  pServiceInfo->cfg.cntCfg.usCntPort,  &pServiceInfo->cfg.mtServWork,  (  LPVOID ) this,  iType_pParentParam,  &pMtSock  )  )  {
							  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  "无法启动网络服务"  ),  _T(  ""  )  ); 
							  traceLogA(  "initQyMcSock failed."  );  
							  goto  errLabel;
		  				  }
		  				  break;
		  }
		  pServiceInfo->pMtSock  =  pMtSock;
						
	 }
		iErr   =  0;
errLabel:


		return  iErr;
	}

	int	CQyStatusDaemon::stop(  )
	{
		int  index;
	
	
		for  (  index  =  0;  ;  index  ++  )  {
		  QY_SERVICE_INFO  *  pServiceInfo  =  (  QY_SERVICE_INFO  *  )getSpecialPtrProperty(  CONST_qyPropertyId_serviceInfo_byIndex,  (  void  *  )index,  0  );
		  //
		  if  (  !pServiceInfo  )  break;
		  if  (  !pServiceInfo->cfg.iServiceId  )  continue;
		  
		  //
		  switch  (  pServiceInfo->cfg.mtServWork.iType  )  {
				  default:
					     exitQyMtSock(  pServiceInfo->pMtSock  );  
						 break;
		  }

	}

		return  0;
	}

	void  CQyStatusDaemon::exit(  )
	{
		return;
	}


	int	CQyStatusDaemon::getInitialCfg(  )
	{
		int  iErr  =  -1;
		QY_SERVICE_CFG		serviceCfg;

		//
		setSockTimeout(  &this->m_var.cfg.to  );



		//
		memset(  &serviceCfg,  0,  sizeof(  serviceCfg  )  );
		//
		serviceCfg.iServiceId  =  CONST_qyServiceId_showInfo;
		//
		if  (  safeStrCpy(  qnmVerStr(  serviceCfg.iServiceId  ),  serviceCfg.ver,  sizeof(  serviceCfg.ver  )  )  )  goto  errLabel;
		if  (  safeWcsCpy(  _T(  CONST_qyRootKey_mc  ),  serviceCfg.sysRootKey,  mycountof(  serviceCfg.sysRootKey  )  )  )  goto  errLabel;
		//
		serviceCfg.ucbAutoOpenDb  =  TRUE;
		
		//
		serviceCfg.ucbDsnless  =  FALSE;	//  2007/06/13
		if  (  !serviceCfg.ucbDsnless  )  lstrcpyn(  serviceCfg.defaultDbName,  _T(  CONST_qyDsn_netMc  ),  mycountof(  serviceCfg.defaultDbName  )  );
		else  _sntprintf(  serviceCfg.defaultDbName,  mycountof(  serviceCfg.defaultDbName  ),  _T(  "%s%s%s.mdb"  ),  this->getAppDataDir(  ),  _T(  CONST_qyDbSubDir  ),  _T(  CONST_qyDbNamePrefix_netMc  )  );
		//
		//lstrcpyn(  reg.rootKey,  _T(  CONST_qyRootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );
		//reg.pEncCtx  =  &var.encCtx;
		//
		unsigned  long		ulOpenOptions						=	0;				
		//ulOpenOptions  =  get_CONST_qyDbOpenOptions(  );
		//
		//if  (  getQnmDbParams(  &reg,  0,  serviceCfg.ucbDsnless,  serviceCfg.defaultDbName,  ulOpenOptions,  &serviceCfg.db  )  )  goto  errLabel;

		// 
		serviceCfg.iObjQType  =  CONST_objQType_netMc;
		_sntprintf(  serviceCfg.mutexName_syncQmObjQ,  mycountof(  serviceCfg.mutexName_syncQmObjQ  ),  _T(  "%s%u"  ),  DEFAULT_mutexName_syncQmObjQ,  serviceCfg.iServiceId  );	//  2007/01/16
		_sntprintf(  serviceCfg.semaphoreName_syncQmObjQ,  mycountof(  serviceCfg.semaphoreName_syncQmObjQ  ),  _T(  "%s%u"  ),  DEFAULT_semaphoreName_syncQmObjQ,  serviceCfg.iServiceId  );	//  2007/01/16
		serviceCfg.uiMaxCnt_semaphore_qmObjQ  =  CONST_maxCnt_sema_syncQmObjQ;
#if  0
		serviceCfg.pfCompare  =  myCompare_mac;
		serviceCfg.pfExitQMemObj  =  NULL;
		serviceCfg.pfFillQmObjMemInfo  =  fillQmObjMemInfo_netMc;
		serviceCfg.tmp_pfAddToQmObjQ  =  (  PF_commonHandler  )tmp_addToQmObjQ_netMc;
#endif

		//
		//getQnmCntCfg(  0,  TRUE,  serviceCfg.iServiceId,  HKEY_LOCAL_MACHINE,  _T(  CONST_qyRootKey_qnmScheduler  ),  &serviceCfg.cntCfg  );
		if ( bAppClient(  qyGetAppType(  0,  NULL  ) )  ) {
			serviceCfg.cntCfg.usCntPort  =  DEFAULT_qyPort_showInfo_cli;
		}
		else {
			serviceCfg.cntCfg.usCntPort  =  DEFAULT_qyPort_showInfo_serv;
		}


		//
		//
		serviceCfg.mtServWork.iType  =  CONST_mtSockType_general;
		serviceCfg.mtServWork.iServiceId  =  serviceCfg.iServiceId;				//  2007/03/12
#if  10
		//serviceCfg.mtServWork.pfInitServWork	=	qmdInitServWork;
		serviceCfg.mtServWork.pfDoServWork  =  (  PF_commonHandler  )qmdServWork_qyStatus;
		//serviceCfg.mtServWork.pfExitServWork	=	qmdExitServWork;
#endif
		_sntprintf(  serviceCfg.mtServWork.mutexName,  mycountof(  serviceCfg.mtServWork.mutexName  ),  _T(  "%s"  ),  _T(  CONST_qyMtSockSubThreadMutexName  )  );
		memcpy(  &serviceCfg.mtServWork.sT,  &m_var.cfg.to,  sizeof(  SOCK_TIMEOUT  )  );
		serviceCfg.mtServWork.usMaxConns  =  50;//getQnmnConns(  &var.licenseCtx,  serviceCfg.iServiceId  );
		serviceCfg.mtServWork.usMaxTalks  =  CONST_qmdMaxTalksASession;
		serviceCfg.mtServWork.usSessionSize  =  0;//sizeof(  QMD_SESSION  );		//  2007/04/20
		//
#if  0
		serviceCfg.uiVarSize  =  getVarSize_netMc(  ); 
		serviceCfg.pfInitVar  =  initVar_netMc;
		serviceCfg.pfExitVar  =  exitVar_netMc;
#endif
		//
		if  (  !bSetSpecialProperty(  CONST_qyPropertyId_serviceCfg,  &serviceCfg,  0,  0  )  )  goto  errLabel;
	
		//
		extern  QY_STATUS_STRUCT  *g_pStatusStruct;
		g_pStatusStruct->sock.usPort  =  serviceCfg.cntCfg.usCntPort;
		g_pStatusStruct->sock.maxConns  =  serviceCfg.mtServWork.usMaxConns;


		//
		iErr  =  0;
errLabel:

	
		return  iErr;
	}

	BOOL  CQyStatusDaemon::bChkBeforeRunning(  )
	{
		return  0;
	}


	int	CQyStatusDaemon::refreshCfg(  )
	{
		return  0;
	}

	





