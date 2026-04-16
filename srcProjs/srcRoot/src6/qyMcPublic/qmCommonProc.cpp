
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

#define MAX_CFG_NAME_LEN	256
#define MAX_CFG_VAL_LEN		256
 __declspec(  dllexport  )  extern  "C"  int  getCfgValByName(  LPCTSTR  cfgFile,  char  *  cfgName,  char  *  cfgVal,  int  size  )
{
	
	FILE *fp=NULL;
	char buf[MAX_CFG_NAME_LEN+MAX_CFG_VAL_LEN+1];
	char cfgNameBuf[MAX_CFG_NAME_LEN+1],cfgValBuf[MAX_CFG_VAL_LEN+1];
	char fmt[32];
	int iRet=-1;
	
	if( strlen(cfgName)>MAX_CFG_NAME_LEN || size>MAX_CFG_VAL_LEN+1 ) 
		return -1;

	if  (  !(  fp  =  _tfopen(  cfgFile,  _T(  "r"  )  )  )  )  return  -1;

	sprintf(fmt,"%%%ds%%%ds",MAX_CFG_NAME_LEN,MAX_CFG_VAL_LEN);

	for(;;){
		if(!fgets(buf,sizeof(buf),fp)) break;
		if(2!=sscanf(buf,fmt,cfgNameBuf,cfgValBuf)) continue;
		if(strcmp(cfgNameBuf,cfgName)) continue;
		iRet=0;
		break;
	}

	if(!iRet) strcpy(cfgVal,cfgValBuf);

	fclose(fp);

	return iRet;

	
}


 __declspec(  dllexport  )  extern  "C"  int  getCfgValByNameT(  LPCTSTR  cfgFile,  TCHAR  *  cfgName,  TCHAR  *  cfgVal,  int  size  )
{
	
	FILE	*	fp	=	NULL;
	TCHAR		buf[MAX_CFG_NAME_LEN+MAX_CFG_VAL_LEN+1];
	TCHAR		cfgNameBuf[MAX_CFG_NAME_LEN+1],cfgValBuf[MAX_CFG_VAL_LEN+1];
	TCHAR		fmt[32];
	int			iRet=-1;
	
	if  (  lstrlen(  cfgName  )  >  MAX_CFG_NAME_LEN  ||  size  >  MAX_CFG_VAL_LEN  +  1  )  return  -1;

	if  (  !(  fp  =  _tfopen(  cfgFile,  _T(  "r,ccs=UNICODE"  )  )  )  )  return  -1;

	_sntprintf(  fmt,  mycountof(  fmt  ),  _T(  "%%%ds%%%ds"  ),  MAX_CFG_NAME_LEN,  MAX_CFG_VAL_LEN  );

	//
	int len_cfgName = _tcslen(cfgName);

	//
	for  (  ;  ;  ){
		 if  (  !_fgetts(  buf,  mycountof(  buf  ),  fp  )  )  break;
		 //
		 tTrim(buf);
		 //
#if 0
		 OutputDebugString(  buf  );  OutputDebugString(  _T(  "\n"  )  );
#endif

		 //
#if  0
		 if (2 != _stscanf(buf, fmt, cfgNameBuf, cfgValBuf))  continue;
		 if (lstrcmpi(cfgNameBuf, cfgName))  continue;
#endif

		 //
		 if (_tcslen(buf) < len_cfgName)  continue;
		 if (_tcsnicmp(buf, cfgName, len_cfgName)) continue;
		 //
		 TCHAR* pT = buf + len_cfgName;
		 if (!pT[0]) {
			 cfgValBuf[0] = 0;
			 break;
		 }
		 if (!isWhiteSpace(pT[0]))  continue;
		 tTrim(pT);
		 lstrcpyn(cfgValBuf, pT, size);

		 iRet  =  0;
		 break;
	}

	if  (  !iRet  ) lstrcpyn(  cfgVal,  cfgValBuf,  size  );

	fclose(  fp  );

	return  iRet;

}

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