
#include	"stdafx.h"
#include	<stdlib.h>
#include	<stdio.h>
#include	<tchar.h>
#include	<winsock2.h>

#include	"qyCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyLicense.h"
#include	"qyCommProc.h"
#include	"qyLangCommProc.h"
#include	"qnmCommProc.h"

//  #include	"qmCommon.h"



 


 //
 __declspec(  dllexport  )  extern  "C"  BOOL  bQmAdvancedVer(  void  *  p0,  LPCTSTR  cfgFullFileName,  void  *  p2  )
{
	 char	buf[128];
	 
	 traceLogA(  (char*)  "bQmAdvancedVer return  TRUE"  );

	 return  TRUE;	 


	 if  (  !getCfgValByName(  cfgFullFileName,  (char*)CONST_cfgName_bAdvancedVer,  buf,  sizeof(  buf  )  )    
		 &&  !_stricmp(  buf,  CONST_cfgVal_bAdvancedVer  )  )
	 {	
		 return  TRUE;
	 }

	 return  FALSE;
}





  BOOL  b4Core(  )
{
	BOOL	bRet	=	FALSE;
	
#ifdef  __DEBUG__
		#if  0
			//  test
		    traceLog(  _T(  "b4Core(  ) is set to false for debug"  )  );
			return  FALSE;
		#endif
#endif

	SYSTEM_INFO	si;
	GetSystemInfo(  &si  );
	if  (  si.dwNumberOfProcessors  <  4  )  goto  errLabel;

	bRet  =  TRUE;
			
errLabel:
	return  bRet;
}

 //  2014/07/13
 BOOL  b2Core(  )
{
	BOOL	bRet	=	FALSE;
	
#ifdef  __DEBUG__
		#if  0
			//  test
		    traceLog(  _T(  "b4Core(  ) is set to false for debug"  )  );
			return  FALSE;
		#endif
#endif

	SYSTEM_INFO	si;
	GetSystemInfo(  &si  );
	if  (  si.dwNumberOfProcessors  <  2  )  goto  errLabel;

	bRet  =  TRUE;
			
errLabel:
	return  bRet;
}


 //
#include	"ctxQyTmpl.h"

 //
 LPCTSTR  get_who_showInfo(  void  *  pCtx,  int  iCtxType  )
 {
	 static  TCHAR  sttt[]  =  _T(  ""  );
	 TCHAR  *  pT  =  sttt;
	 //
	 switch  (  iCtxType  )  {
			 case  CONST_ctxType_qmc:
			 case  CONST_ctxType_dvt:
			 case  CONST_ctxType_evt:
			 case  CONST_ctxType_qmd:
				   CCtxQyTmpl  *  pBase;
				   pBase  =  (  CCtxQyTmpl  *  )pCtx;
				   pT  =  pBase->who_showInfo;
				   break;
			 default:
					break;
	 }

	 return  pT;
 }