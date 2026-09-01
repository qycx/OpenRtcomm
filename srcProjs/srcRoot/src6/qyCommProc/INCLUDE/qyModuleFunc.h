
#ifndef  __QYMODULEFUNC_H__
#define  __QYMODULEFUNC_H__	//  {  


#ifdef  __cplusplus
  extern  "C"  {
#endif


typedef  struct  {
				 TCHAR				name[64];
				 unsigned  int		uiType;
				 char				ver[CONST_qyMaxVerLen  +  1];
				 void			*	pProcTable;		//  接口表
				 TCHAR				callerId[64];
				 void			*	pLicenseCtx;
				 union				{
					 char			buf[1024];
				 }					u;
}		 QY_MODULE_INFO;


typedef  int  (  *PF_qyModuleProc  )(  void  *  p1,  void  *  p2  );	//  模块接口函数类型

typedef  struct  {

				 HINSTANCE				hModule;
				 PF_qyModuleProc		pfGetModuleInfo;
				 
				 QY_MODULE_INFO			info;
				 int					iStatus;

				 PF_qyModuleProc		pfInit;
				 PF_qyModuleProc		pfExit; 
				 PF_qyModuleProc		pfGetInitialCfg;
				 PF_qyModuleProc		pfRefreshCfg;

				 void				*	p1;	
				 void				*	p2;

}		 QY_MODULE;



#define		CONST_qyMaxModules		32


typedef  struct  {
				 unsigned  int		uiCnt;
				 QY_MODULE			mems[CONST_qyMaxModules];
}		 QY_MODULES;

int		qyLoadModule(  QY_ENV  *  pEnv,  LPCTSTR  callId,  LPCTSTR  path,  void  *  pLicenseCtx,  QY_MODULES  *  pModules  );		//  装载一个模块
int  qyLoadModuleByKeyName(  QY_ENV  *  pEnv,  LPCTSTR  sysRootKey,  LPCTSTR  moduleIdName,  LPCTSTR  installDir,  void  *  pLicenseCtx,  LPCTSTR  moduleKeyName,  QY_MODULES  *  pModules  );
int  qyLoadAllModules(  QY_ENV  *  pEnv,  LPCTSTR  sysRootKey,  LPCTSTR  moduleIdName,  LPCTSTR  installDir,  void  *  pLicenseCtx,  QY_MODULES  *  pModules  );	//  装载所有的模块
void	qyUnloadAllModules(  QY_ENV  *  pEnv,  QY_MODULES  *  pModules  );	//  卸载所有的模块
QY_MODULE  *	qyGetModuleByName(  QY_MODULES  *  pModules,  LPCTSTR  name  );
PF_qyModuleProc  qyGetModuleProcByName(  QY_MODULE  *  pModule,  LPCTSTR  name  );

/*
//  下面是模块标准接口
__declspec( dllexport ) int  qyModuleInit(  void  *  p1,  void  *  p2  );
__declspec( dllexport ) int  qyModuleExit(  void  *  p1,  void  *  p2  );
__declspec( dllexport ) int  qyModuleGetInitialCfg(  void  *  p1,  void  *  p2  );
__declspec( dllexport ) int  qyModuleRefreshCfg(  void  *  p1,  void  *  p2  );
*/

//
//	接口表项，{	序号，接口名，接口函数,}
//

//  统一接口函数，提供接口信息
__declspec( dllexport ) int  qyGetModuleInfo(  void  *  pModuleInfo,  void  *  p2  );	  


#ifdef  __cplusplus
  }
#endif


#endif  //  }  



