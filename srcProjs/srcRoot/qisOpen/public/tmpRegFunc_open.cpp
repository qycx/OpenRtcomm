
#include	"stdafx.h"
//#include	<Windows.h>
#include	<MMSystem.h>
#include	<tchar.h>

#include	"qmOpenCommon.h"
#include	"tmpRegFunc_open.h"


 //
 extern  "C"  int  tmpGetRegCfg_open(  HKEY  hKeyRoot0,  LPCTSTR  rootKey,  LPCTSTR  cfgName,  unsigned  int  *  puiType,  char  *  cfgVal,  unsigned  int  *pSize  )
{
	unsigned  int  uiType  =  0;
	 
	int				iRet		=	-1;
	BOOL			bKeyOpen	=	FALSE;
	HKEY			hKey;
	unsigned  int	cb;
	DWORD			type;

	//			
	if  (  !rootKey  || !rootKey[0]  ||  !pSize  )  return  -1;
	if  (  !hKeyRoot0  )  hKeyRoot0  =  HKEY_LOCAL_MACHINE;

	//  if  (  RegOpenKey(  hKeyRoot0,  rootKey,  &hKey  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	if  (  RegOpenKeyEx(  hKeyRoot0,  rootKey,  0,  KEY_QUERY_VALUE,  &hKey  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	bKeyOpen  =  TRUE;
	
	cb  =  *pSize;
	if  (  RegQueryValueEx(  hKey,  cfgName,  0,  &type,  (  unsigned  char  *  )cfgVal,  (  unsigned  long  *  )&cb  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	
	//  2003/09/12加入了对类型的判断，仅对字符串作结尾
	if  (  type  ==  REG_SZ  ||  type  ==  REG_MULTI_SZ  ||  type  ==  REG_EXPAND_SZ   )  {
		TCHAR	*	pT	=	(  TCHAR  *  )cfgVal;
		cb  =  cb  /  sizeof(  TCHAR  );
		if  (  cb  <  1  )  pT[0]	=	0;
		else  pT[cb - 1] = 0;
	}
	
	iRet  =  0;
	
errLabel:

	if  (  bKeyOpen )  RegCloseKey(  hKey  );

	if  (  !iRet  )  {
		if  (  puiType  )  *puiType  =  type;		//  2004/08/06加
		if  (  pSize  )  *pSize  =  cb;

	}

	return  iRet;

}



 //
	//  除了REG_BINARY这种类型需要cb外，其他的，都用cfgVal自己来判断
 extern  "C"  int  tmpSetRegCfg_open(HKEY  hKeyRoot0, LPCTSTR  rootKey, LPCTSTR  cfgName, unsigned  int  uiType, char* cfgVal, unsigned  int  cb)
 {
	 int			iRet = -1;
	 BOOL		bKeyCreated = FALSE;
	 HKEY		hKey;
	 int			rc = -1;
	 TCHAR		tBuf[512] = _T("");
	 int			dataLen = cb;
	 char* p = cfgVal;

	 if (!cfgVal)  return  -1;

	 if (!hKeyRoot0)  hKeyRoot0 = HKEY_LOCAL_MACHINE;

	 //  if ( ( rc = RegCreateKey( pReg->hKeyRoot0  ?  pReg->hKeyRoot0  :  HKEY_LOCAL_MACHINE, pReg->rootKey, &hKey ) ) != ERROR_SUCCESS ) goto errLabel;
	 if ((rc = RegCreateKeyEx(hKeyRoot0, rootKey, NULL, (TCHAR*)_T(""), NULL, KEY_ALL_ACCESS, NULL, &hKey, NULL)) != ERROR_SUCCESS) goto errLabel;
	 bKeyCreated = TRUE;

	 switch (uiType) {
	 case  REG_DWORD:		dataLen = sizeof(DWORD);
		 break;
	 case  REG_BINARY:		break;
	 case  REG_MULTI_SZ:
		 if (!cb) {
			 dataLen = lstrlen((TCHAR*)cfgVal) + 1;			//  注意，这里需要将包含'\0'的字节也包含
			 if (dataLen >= mycountof(tBuf) - 1) {
				 //traceLogA("buf is too small");  
				 goto  errLabel;
			 }
			 lstrcpyn(tBuf, (TCHAR*)cfgVal, mycountof(tBuf));
			 tBuf[dataLen] = '\0';  dataLen++;

			 p = (char*)tBuf;
			 dataLen = dataLen * sizeof(TCHAR);
		 }
		 break;
	 case  REG_SZ:
	 default:
		 if (!cb) {
			 dataLen = (lstrlen((TCHAR*)cfgVal) + 1) * sizeof(TCHAR);			//  注意，这里需要将包含'\0'的字节也包含
		 }
		 break;
	 }

	 DWORD uiType_default; uiType_default = REG_SZ;
	 if (RegSetValueEx(hKey, cfgName, 0, uiType ? uiType : uiType_default, (const  unsigned char*)p, dataLen) != ERROR_SUCCESS) {
		 //traceLogA("asrSetRegCfg( ): RegSetValueEx( ) failed.");  
		 goto errLabel;
	 }

	 iRet = 0;

 errLabel:

	 if (bKeyCreated)  RegCloseKey(hKey);

	 return  iRet;

 }




