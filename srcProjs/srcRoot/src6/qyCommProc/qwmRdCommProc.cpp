
#include	<windows.h>
#include	<iphlpapi.h>
#include	<tchar.h>
#include	"qyCommon.h"
#include	"qyCommProc.h"
#include	"qwmHideProcessCommProc.h"		//  2006/02/13
#include	"qwmDynFunc.h"


#define		CONST_qyRootKey_qwm				"SOFTWARE\\Microsoft\\SharedTran"
#define		CONST_regValName_autoAcceptRd	"qimxyns"
#define		CONST_sym_autoAcceptRd			"msynwynb"

 


 int  getRdFlg(  BOOL  *  pbAutoAcceptRd  )
{
	 int	iErr		=		-1;
	 TCHAR	buf[128];

	 if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_qwm  ),  _T(  CONST_regValName_autoAcceptRd  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  goto  errLabel;
	 * pbAutoAcceptRd  =  !lstrcmp(  _T(  CONST_sym_autoAcceptRd  ),  buf  )  ?  TRUE  :  FALSE;

	 iErr  =  0;

errLabel:
	 return  iErr;
}

 int  setRdFlg(  BOOL  bAutoAcceptRd  )
{
	 if  (  !bAutoAcceptRd  )  qyDelRegCfg(  _T(  CONST_qyRootKey_qwm  ),  _T(  CONST_regValName_autoAcceptRd  )  );
	 else  qySetRegCfg(  _T(  CONST_qyRootKey_qwm  ),  _T(  CONST_regValName_autoAcceptRd  ),  _T(  CONST_sym_autoAcceptRd  )  );
	 return  0;
}

 //  2007/02/09, 在用户模式下，不允许改变选项。在系统模式下，才能改为自动允许
 BOOL  bAbleToSetRdFlg(  QNM_RD_STRUCT  *  pQnmRdStruct  )  
{
	 BOOL			bRet		=	FALSE;
	 QY_ENV		*	pEnv		=	(  QY_ENV  *  )pQnmRdStruct->pEnv;	
	 WCHAR			wBuf[512]	=	L"";

	 if  (  !pEnv  )  goto  errLabel;		//  这是在测试环境下

	 if  (  getProcessUsrAndDomain(  pEnv,  GetCurrentProcessId(  ),  wBuf,  mycountof(  wBuf  ),  0,  0  )  )  goto  errLabel;
	 if  (  wcsicmp(  wBuf,  L"System"  )  )  goto  errLabel;

	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}