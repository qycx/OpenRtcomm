

#ifndef  __QMCFG_H__
#define  __QMCFG_H__	/*  {  */

#define		DEFAULT_QY_MC_DSNNAME							CONST_qyDsn_netMc

#define		DEFAULT_QY_MC_CHILD_FRM_TIMER_ID				1
#define		CONST_qyPsTimerId								2


#if 0
//  2007/04/15
#define		DEFAULT_usCliThreads_io							20
#define		DEFAULT_usMgrThreads_cs							13							//  2016/12/30	//  10							//  2008/05/15, mtMgrThreadProc_mis
#define		DEFAULT_usMgrThreads_route						80	//40	//30							//  11							//  2008/05/15, mtMgrThreadProc_mis
#define		DEFAULT_usMgrThreads_switch_route				80	//50							//  12							//  2008/05/15, mtMgrThreadProc_mis
#endif


//
#define		CONST_qmdMaxTalksASession						128							//  


//  #define		CONST_nRcdsPerBatch_forBar						99999
//  #define		CONST_nRcdsPerBatch								150
#define		CONST_QY_nQueryStopInterval						2000						//  
#define		CONST_QMD_nSenderInterval						10000						//  10
#define		CONST_QMD_nProcessingInterval					1000						//  1
#ifndef	 __DEBUG__
	#define		CONST_QMD_nSenderRequestInterval			(  10  *  60  *  1000  )	//  10				
	#define		CONST_QMD_nProcessQmObjQIntervalLoops		(  5  *  60  )				//  5, 2006/12/09
	#define		CONST_QMD_nRefreshQmObjQStatusInDbLoops		(  1  *  60  )				//  7
#else
	#define		CONST_QMD_nSenderRequestInterval			(  3  *  1  *  1000  )		//  10
	#define		CONST_QMD_nProcessQmObjQIntervalLoops		(  1  *  10  )				//  , 2006/12/09
	#define		CONST_QMD_nRefreshQmObjQStatusInDbLoops		(  1  *  60  )				//  1
#endif
#define			CONST_QMD_nGetDaemonStatusLoops				(  1  *  3  )				//  2010/01/10


#define		CONST_usIntervalAheadInS_refreshTime_forDb		1  *  60					//  1分钟，2007/08/05
																						//  
#define		CONST_usIntervalAheadInS_refreshTime_forMem		5							//  1 2007/08/05



//
#define		CONST_max_nMgrThreads_others					4							//  2015/09/02. 比如qmdLogThreadProc，qmdProcessingThreadProc，qmdWarnThreadProc, qmdPhProcThreadProc 等辅助线程

//#define		CONST_qmdMaxThreads							200							//  2007/04/20
//  2015/09/02
#define		CONST_qmdMaxThreads								(  CONST_max_nMgrThreads_others  +  CONST_max_nMgrThreads_cs  +  CONST_max_nMgrThreads_route  +  CONST_max_nMgrThreads_switch_route  )
			


#define		CONST_qnmMaxStatCols							CONST_qyMaxQueryCols

#define		DEFAULT_qrtTitle								_T(  "Computer registration"  )	//  2005/07/27
//  
#define		DEFAULT_qrtHint									_T(  "Fill in the following blanks before 2009-9-30"  )	//  	//  2005/05/02



#define		CONST_maxCnt_sema_mgrQ_is						0  //10020					//  
#define		CONST_uiMaxQNodes_mgrQ_is						10000					//  
#define		CONST_mutexName_syncMisQ_cs						_T(  "misQ_sync_cs"  )
#define		CONST_mutexName_syncMisQ_route					_T(  "misQ_sync_r"  )
#define		CONST_mutexName_syncMisQ_switch_route			_T(  "misQ_sync_sr"  )

//
#define		DEFAULT_uiBufSize_misMsgGrpData					4  *  1024  *  1024		//  2008/05/27


#define		CONST_maxCnt_sema_webAuthQ_is					1000					//  2007/11/22
#define		CONST_mutexName_syncWebAuthQ					_T(  "webAuthQ_sync"  )	//  2007/11/22
//
#define		CONST_mutexname_syncGetNextMessengerId			_T(  "getNextMsgId"  )

#define		CONST_uiMaxQNodes_messengerProcessQ				1000
//
#define		CONST_uiMaxQNodes_messengerBtQ					300	 *  10					//  2011/04/18
//
#define		CONST_uiMaxQNodes_messengerOutputQ				150  *  25	//  200  *  3						//  2007/05/29, messenger.outputQ
#define		CONST_uiMaxQNodes_messengerOutputQ_warning		100  *  25	//  150  *  3						//  messenger.outputQ
//
#if  1  //  def  __DEBUG__
#define		CONST_uiMaxQNodes_sendFinishedQ					200  *  10					//  2015/08/18
#endif

//
#define		CONST_uiMaxQNodes_messengerTalkingFriendQ		30						//  2007/09/01, messenger
//
#define		CONST_uiMaxQNodes_imGrpMems						1000					//  2007/09/01, imGrp
																					//  imGrptalkingFriendQ. 

//
#define		CONST_usMaxMsgrRecentFriends					230						//  2007/06/04, 2007/09/09

//


//
#define		CONST_cfgName_dbServIp							"dbServIp"
#define		CONST_cfgName_dbName							"dbName"
#define		CONST_cfgName_dbPasswd							"dbPasswd"

//
#define		CONST_cfgName_bNoEnc_forTest					"bNoEnc_forTest"

//
#define		CONST_cfgName_nIntervalInS_qmdXt				"nIntervalInS_qmdXt"				//  20

//
#define		CONST_cfgName_ucHardwareAccl					"ucHardwareAccl"

//
#define		CONST_cfgName_bChannelRedirect					"bChannelRedirect"

//
#define		CONST_cfgName_fMinFree_disk						"fMinFree_disk"
#define		CONST_cfgName_iMaxElapseInDay					"iMaxElapseInDay"


//
typedef  struct  {


		//
		char				dbServIp[CONST_qyMaxIpLen + 1];
		char				dbName[64];
		char				dbUsr[64];
		char				dbPasswd[128];
	
		//
		bool				bNoEnc_forTest;

		//
		unsigned  char		ucHardwareAccl;

		//
		int					nIntervalInS_qmdXt;

		//
		bool				bChannelRedirect;

}  Qm_initCfg;



//
typedef  struct  {

		//
		int					iMaxElapseInDay;
		float				fMinFree_disk;

}		 Hg_mcuCfg;





//
int outputVerInfo(TCHAR* filePrefix);

//
bool bGetQmInitCfg(TCHAR* smCfgFile, Qm_initCfg* pCfg);
int  getQnmDbParams(  QY_REG  *  pReg, LPCTSTR  smCfgFile,  int  iDefaultSystemId,  unsigned  char  ucbDefaultDsnless,  LPCTSTR  defaultDbName,  unsigned  long  ulOpenOptions,  QNM_DB_CFG  *  pDb  );

//
bool  bGetHgMcuCfg(  TCHAR  *  cfgFile,  Hg_mcuCfg  *  pCfg  );
int  saveHgMcuCfg(Hg_mcuCfg  *  pCfg,  TCHAR  *  cfgFile  );




//
#endif  /*  }  */



