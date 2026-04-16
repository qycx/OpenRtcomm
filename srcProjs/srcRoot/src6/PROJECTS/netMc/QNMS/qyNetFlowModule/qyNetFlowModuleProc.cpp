

#include	<afxdb.h>
#include	<windowsx.h>

#include	"qyCommonEx.h"
#include	"qyGuiCommonEx.h"
#include	"qyDbCommon.h"

#include	"qyPreCustom.h"
#include	"qyCustom.h"

#include	"qyWmComm.h"
#include	"qyCommCommon.h"

#include	"qyLicense.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qyImcCommProc.h"
#include	"qySnmpCommProc.h"
#include	"qnmsCommProc.h"
#include	"qyLangCommProc.h"
#include	"qnmGuiCommProc.h"
#include	"qyModuleCommProc.h"

#include	"qnmPrecomp.h"

#include	"qnmCustom.h"
#include	"qnmCustomComm.h"

#include	"qmCommon.h"
#include	"qyDbCommon.h"

#include	"qyCommCommon.h"
#include	"qyGuiCommonEx.h"

#include	"qnmDb.h"
#include	"qnmGuiCommProc.h"
#include	"qySnmpCommProc.h"

#include	"qyMcMainDefs.h"
#include	"qyMcDlgBarCfg.h"
#include	"qyMcMainObj.h"
#include	"qyMcMainMenu.h"


#include	"resource.h"


 extern  "C"  int  myTest(  )
{
	 return  0;
}


 int  qyModule_menu(  QNM_GUI_MENU  *  pMenu,  void  *  p1  )
{

	 traceLogA(  "qyModuleCustomGuiMenu  enters"  );

	 traceLogA(  "qyModuleCustomGuiMenu  leaves"  );
	 return  0;
}

 int  qyModule_nmsPupupMenu(  QY_MC_SEL  *  pCurSel,  HMENU  hMenu  )
{	 
	 if  (  !pCurSel  )  return  -1;

	 switch  (  pCurSel->type  )  {
			 case  QY_SELTYPE_MCROOTTREE:			//  0
				   if  (  pCurSel->u.rootTree.bRoot  )  break;
				   switch  (  pCurSel->u.rootTree.objIndex.objType  )  {
					       case  CONST_objType_qySwitch:		{
							     InsertMenu(  hMenu,  ID_qyDel_switch,  MF_BYCOMMAND  |  MF_STRING,  ID_qyEdit_switchRule,  "编辑管理策略"  );
							     InsertMenu(  hMenu,  ID_qyDel_switch,  MF_BYCOMMAND  |  MF_SEPARATOR,  0,  ""  );
								 }
							     break;
						   case  CONST_objType_qySwitchPort:	{
								}
							     break;
						   default:
								   break;
				   }
				   break;
			 default:
					break;
	 }

	 return  0;
}


 int  qyModule_netMcProcTvEventFunc(  void  *  p1,  void  *  p2  )
{
	 traceLogA(  "qyModule_netMcProcTvEventFunc enters"  );


	 traceLogA(  "qyModule_netMcProcTvEventFunc leaves"  );
	 return  0;
}

 QY_DMITEM  CONST_qnmGuiProcTable[]  =
{
	{	0,	CONST_moduleProcName_menu,						(  char  *  )qyModule_menu,  },
	{	0,	CONST_moduleProcName_nmsPopupMenu,				(  char  *  )qyModule_nmsPupupMenu,  },
	{	0,	CONST_moduleProcName_netMcProcTvEventFunc,		(  char  *  )qyModule_netMcProcTvEventFunc,  },
	{	-1,	NULL,												},
};


 extern  "C"  __declspec( dllexport )  int  qyGetModuleInfo(  void  *  pModuleInfoParam,  void  *  p2  )
{
	 int				iRet		 =	-1;
	 QY_MODULE_INFO	*	pModuleInfo  =  (  QY_MODULE_INFO  *  )pModuleInfoParam;
	 unsigned  char		ucbDogOk		=	TRUE;
	 char			*	moduleName		=	CONST_qyModuleName_netFlow;
	 QY_LICENSE_CTX	*	pLicenseCtx		=	NULL;

	 setDebugLogFileModuleName(  );
	 setErrHintWndCls(  CONST_qnmStatusToolWndClass  );

 	 if  (  !pModuleInfo  )  goto  errLabel;
	 pLicenseCtx  =  (  QY_LICENSE_CTX  *  )pModuleInfo->pLicenseCtx;
	 #ifndef  __WITHOUT_CHKDOG__
			  if  (  !pLicenseCtx  ||  !pLicenseCtx->bRnbDogInited  )  ucbDogOk  =  FALSE;
			  else  if  (  !bQyDogOk(  pLicenseCtx,  moduleName  )  )  {
				  		AfxMessageBox(  "netMc2: cannot find usb key"  );  ucbDogOk  =  FALSE;
			  }
	 #endif
	 if  (  !ucbDogOk  )  goto  errLabel;


	 _snprintf(  pModuleInfo->name,  sizeof(  pModuleInfo->name  ),  "%s",  moduleName  );

	 if  (  !strcmpi(  pModuleInfo->callerId,  CONST_qyModuleName_gui  )  )  pModuleInfo->pProcTable  =  CONST_qnmGuiProcTable;
	 else  pModuleInfo->pProcTable  =  CONST_qyNullTable;
	 
	 iRet  =  0;

errLabel:

	 traceLogA(  "%s: qyGetModuleInfo returns %s",  moduleName,  iRet  ?  "失败"  :  "成功"  );

	 return  iRet;
}

