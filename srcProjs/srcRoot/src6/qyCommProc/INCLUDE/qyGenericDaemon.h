

#ifndef  __QYDAEMONOBJ_H__
#define  __QYDAEMONOBJ_H__	/*  {  */

#include	"qyMtSock.h"
#include	"ctxQyTmpl.h"  //  2015/07/18

//
#define		CONST_qyPropertyId_null								0			//  不用, 200703/12
//  #define		CONST_qyPropertyId_dsnName						10
#define		CONST_qyPropertyId_lckFileName						11
#define		CONST_qyPropertyId_db								12
#define		CONST_qyPropertyId_nInterval						13
//  #define		CONST_qyPropertyId_sysRootKey						14		//  整个应用系统的根键
#define		CONST_qyPropertyId_moduleIdName						15			//  Daemon在每一module中的标识, 是字符串
#define		CONST_qyPropertyId_licenseCtx						16			//  
//  #define		CONST_qyPropertyId_dbTypeName					17		
//  #define		CONST_qyPropertyId_connectStr					18
//  #define		CONST_qyPropertyId_autoOpenDb					19
#define		CONST_qyPropertyId_logCtx							20
#define		CONST_qyPropertyId_installDir						21
//  #define		CONST_qyPropertyId_dbType						22			//  2006/005/03
//  #define		CONST_qyPropertyId_dynLib							23		//  2007/01/22
#define		CONST_qyPropertyId_serviceCfg						24			//  2007/03/12
#define		CONST_qyPropertyId_mtSock							25			//  2007/03/13
#define		CONST_qyPropertyId_serviceInfo_byServiceId			26			//  2007/03/13
#define		CONST_qyPropertyId_serviceInfo_byIndex				27			//  2007/03/13
#define		CONST_qyPropertyId_env								28			//  2007/03/13
//
#define		CONST_qyPropertyId_vDev								1000		//  2008/01/01, 在增加的客户端的虚拟设备里使用。
#define		CONST_qyPropertyId_bPhoneMsgrListAccepted			1001		//  2008/02/05
#define		CONST_qyPropertyId_ucbOnlyNetSm						1002		//  2008/02/10  
#define		CONST_qyPropertyId_baud								1003		//  2008/11/22	



typedef  struct  __qyServiceCfg_t					{
				 int								iServiceId;
				 char								ver[CONST_qyMaxVerLen  +  1];				//  版本号
				 WCHAR								sysRootKey[QY_MAXKEYLEN  +  1];				//  应用系统的根键
								
				 unsigned  char						ucbAutoOpenDb;								//  是否自动建立数据库连接，2004/08/19
				 //				 
				 unsigned  char						ucbDsnless;									//  数据库是否采用DNSLESS的连接方式，2007/06/13
				 TCHAR								defaultDbName[MAX_PATH  +  1];				//  缺省的数据库名称，在ACCESS的无DSN方式里，指文件全路径
				 //
				 QNM_DB_CFG							db;
				 

				 int								iObjQType;									//  2007/04/05
				 WCHAR								mutexName_syncQmObjQ[32  +  1];
				 WCHAR								semaphoreName_syncQmObjQ[32  +  1];
				 unsigned  int						uiMaxCnt_semaphore_qmObjQ;	
				 //
				 void					*			pfCompare;
				 void					*			pfExitQMemObj;
				 void					*			pfFillQmObjMemInfo;
				 PF_commonHandler					tmp_pfAddToQmObjQ;
				 //
				 PF_commonHandler					pfPrintQ;

				 //
				 //  QY_LOGICAL_SERVER				localService;								//  本地服务的配置
				 QNM_CNT_CFG						cntCfg;										//  2010/09/23
				 MT_SERVWORK						mtServWork;
				 //
				 unsigned  short					usCnt_mgrThreads_cs;						//  管理线程数, 2008/05/15
				 unsigned  short					usCnt_mgrThreads_route;						//  管理线程数, 2008/05/15
				 unsigned  short					usCnt_mgrThreads_switch_route;				//  管理线程数, 2008/05/15

				 //
				 PF_commonHandler					pfNewVar;							//  2015/01/20
				 PF_commonHandler					pfFreeVar;

				 //
				 unsigned  int						uiVarSize;									//  全局空间的大小
				 PF_commonHandler					pfInitVar;
				 PF_commonHandler					pfExitVar;									//
				 
}		  QY_SERVICE_CFG;


typedef  struct  __qyServiceInfo_t					{
				 QY_SERVICE_CFG						cfg;
				 TCHAR								name[32  +  1];
				 void					*			pParent;			//  指向daemon
				 void					*			pMtSock;
				 void					*			pDb;
				 void					*			pVar;				//  指向各服务单独的一个全局空间
				 unsigned  char						ucbVarInited;
				 //
				 void					*			pObjQ;				//  2007/04/01
				 unsigned  char						ucbQmObjQInited;	//  200612/07
				 
}		 QY_SERVICE_INFO;


//  #define		CONST_maxQyServices					10
#define		CONST_maxQyServices						1					//  2011/01/10


//
typedef  struct  __qyGenericDaemon_t		{
	
				 struct						{
						 char				rootKey[QY_MAXKEYLEN + 1];					//  服务的注册表根键
						 BOOL				bQuit;										//  退出标志
						 BOOL				bRestart;									//	重启标志	
						 BOOL				bStop;										//  暂停标志
						 BOOL				bPanic;										//  崩溃标志
						 unsigned  int		nInterval;									//	刷新间隔，毫秒计
						 TCHAR				installDir[QY_MAXPATHLEN + 1];				//  安装目录
						 TCHAR				appDataDir[CONST_qyMaxPathLen  +  1];		//  通常为applicationData\\qycx\\服务名
						 TCHAR				workDir[QY_MAXPATHLEN + 1];					//  工作目录
						 char				daemonName[16];								//  为方便调试。
						 TCHAR				lckFileName[16  +  1];						//  加锁文件名
						 TCHAR				moduleIdName[CONST_qyNameLen_dsn  +  1];	//  Daemon在每一module中的标识, 是字符串
				 }							cfg;

				 QY_SERVICE_INFO			serviceInfos[CONST_maxQyServices];

				 //  外界传入
				 void				*		pEnv;
				 void				*		pLicenseCtx;
				 void				*		pLogCtx;

				 //  genericDaemon自动生成
				 void				*		pLckFile;									//  锁定文件

				 struct						{
						BOOL				bInited;
				 }							status;

				 QY_MODULES					modules;

}		 QY_GENERIC_DAEMON;


//
class CQyGenericDaemon : public  CCtxQyTmpl {

public:
	CQyGenericDaemon(  );
	~CQyGenericDaemon(  );

private:
	QY_GENERIC_DAEMON		var;

public:
	char				*	getRootKey(  );
	TCHAR				*	getAppDataDir(  );
	TCHAR				*	getWorkDir(  );
	TCHAR				*	getInstallDir(  );
	//  char				*	getVer(  );
	void				*	getModules(  );

	//
	BOOL					bSetStrProperty(  int  propertyId,  LPCTSTR  val  );
	TCHAR				*	getStrPtrProperty(  int  propertyId  );
	BOOL					bSetLongProperty(  int  propertyId,  long  val  );
	BOOL					bGetLongProperty(  int  propertyId,  long  *  pVal  );
	long					unused_getLongProperty(  int  propertyId,  BOOL  *  pbFailed  =  NULL  );
	BOOL					bSetPtrProperty(  int  propertyId,  void  *  ptr  );
	void				*	getPtrProperty(  int  propertyId  );
	BOOL					bSetSpecialProperty(  int  propertyId,  void  *  p0,  void  *  p1,  void  *  p2  );
	void				*	getSpecialPtrProperty(  int  propertyId,  void  *  p0,  void  *  p1  );


public:
	virtual  int			preInit(  QY_ENV  *  pEnv,  char  *  rootKey,  unsigned  int  nInterval,  char  *  daemonName  );
	virtual  int			preInit(  QY_ENV  *  pEnv,  char  *  rootKey  );
	virtual  int			init(  );
	virtual  int			start(  );
	virtual  int			stop(  );
	virtual  void			exit(  );
	//
	virtual  BOOL			bQuit(  );
	virtual  void			startToQuit(  );
	virtual  BOOL			bStop(  );
	virtual  void			startToStop(  );
	virtual  BOOL			bRestart(  );
	virtual  void			startToRestart(  );
	virtual int				getInitialCfg(  );
	virtual int				refreshCfg(  );
	void					notifyPanic(  LPCTSTR  hint  );
	void					clearRestartFlg(  );
	//  int						qyLoadAllModules(  );
	
public:
	virtual  int			runAsApp(  );
	//
	virtual  int			refreshCfg_app(  );
	//
	virtual  BOOL			bUseGui(  );
	virtual  int			gui_run(  );


	
};


#endif	/*  }  */

