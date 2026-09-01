
#include	"stdafx.h"

#include	"qyCommonEx.h"

#include	"qyPreCustom.h"
#include	"qyCustom.h"

#include	"qyWmComm.h"
#include	"qyCommCommon.h"


#include	"qyLicense.h"
#include	"qyCommProc.h"
#include	"qyTCharCommProc.h"
#include	"traceLogA.h"
#include	"qyModuleFunc.h"
#include	"qnmCommProc.h"

 QY_LICENSE_CTX		moduleLicenseCtx;

  extern  "C"  int  qyModuleGetInitialCfg(  void  *  p1,  void  *  p2  )
 {
	 int						iErr		=	-1;
	 QY_MODULE				*	pModule		=  (  QY_MODULE  *  )p1;
	 QY_LICENSE_CTX			*	pLicenseCtx	=	NULL;
	 unsigned  char				ucbDogOk	=	TRUE;
	 BOOL						bModuleLicenseCtxInted	=	FALSE;


	 if  (  initRnbDog(  &moduleLicenseCtx  )  )  goto  errLabel;
	 bModuleLicenseCtxInted =  TRUE;
	 
	 //  pLicenseCtx  =  (  QY_LICENSE_CTX  *  )pModuleInfo->pLicenseCtx;
	 pLicenseCtx  =  &moduleLicenseCtx;
	 #ifndef  __WITHOUT_CHKDOG__
			  if  (  !pLicenseCtx  ||  !pLicenseCtx->bRnbDogInited  )  ucbDogOk  =  FALSE;
			  else  if  (  !bQyDogOk(  pLicenseCtx,  pModule->info.name  )  )  {
				  		AfxMessageBox(  _T(  "secChk: 没有找到软件狗"  )  );  ucbDogOk  =  FALSE;
			  }
	 #endif
	 if  (  !ucbDogOk  )  goto  errLabel;

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
		 if  (  bModuleLicenseCtxInted  )  exitRnbDog(  &moduleLicenseCtx  );		 
	 }
	 if  (  !iErr  )  {
		 pModule->info.pLicenseCtx  =  &moduleLicenseCtx;		//  2007/03/01, 因为圣天狗出了问题，似乎不支持动态DLL共享license, 所以改成局部的
	 }

	 return  iErr;
}


 int  qyModuleInit(  void  *  p1,  void  *  p2  )
{
	 traceLogA(  "secChkModule.dll: qyModuleInit called"  );

	 return  0;
}

  int  qyModuleExit(  void  *  p1,  void  *  p2  )
{
	QY_MODULE		*	pModule		=	(  QY_MODULE  *  )p1;

	 traceLogA(  "netMc2Module.dll: qyModuleExit called."  );
	 exitRnbDog(  &moduleLicenseCtx  );  
	 pModule->info.pLicenseCtx  =  0;

	 traceLogA(  "secChkModule.dll: qyModuleExit called"  );

	 return  0;
}

 int  testProc(  void  *  p1,  void  *  p2  )
{
	 traceLogA(  "testProkkkkkkkkkkc"  );

	 return  0;
}

 QY_DMITEM  moduleProcTable[]  =
{
	{	0,	_T(  "qyModuleInit"  ),				(  TCHAR  *  )qyModuleInit,	},
	{	1,	_T(  "qyModuleExit"  ),				(  TCHAR  *  )qyModuleExit,	},
	{	2,	_T(  "qyModuleGetInitialCfg"  ),	(  TCHAR  *  )qyModuleGetInitialCfg,		},
	{	10,	_T(  "testProc"  ),					(  TCHAR  *  )testProc,		},
	{	-1,	NULL,								},
};
  
 extern  "C"  __declspec( dllexport )  int  qyGetModuleInfo(  void  *  pModuleInfoParam,  void  *  p2  )
{
	 int				iRet		 =	-1;
	 QY_MODULE_INFO	*	pModuleInfo  =  (  QY_MODULE_INFO  *  )pModuleInfoParam;
	 unsigned  char		ucbDogOk	 =	TRUE;
	 char			*	moduleName		=	CONST_qyModuleName_secChk;
	 QY_LICENSE_CTX	*	pLicenseCtx		=	NULL;

	 if  (  !pModuleInfo  )  return  -1;

	 setDebugLogFileModuleName(  );
	 setErrHintWndCls(  CONST_qnmStatusToolWndClass  );

	 //  _snprintf(  pModuleInfo->name,  sizeof(  pModuleInfo->name  ),  "%s",  moduleName  );
	 myStr2WChar(  moduleName,  pModuleInfo->name,  mycountof(  pModuleInfo->name  )  );
	 pModuleInfo->pProcTable  =  moduleProcTable;

	 iRet  =  0;

//errLabel:

	 traceLogA(  "%s: qyGetModuleInfo returns %s",  moduleName,  iRet  ?  "失败"  :  "成功"  );
	 
	 return  iRet;

}


