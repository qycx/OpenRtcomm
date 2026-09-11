
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

//
extern  "C"     atbool  g_bLocalService = false;



#define MAX_CFG_NAME_LEN	256
#define MAX_CFG_VAL_LEN		256
__declspec(dllexport)  extern  "C"  int  getCfgValByName(LPCTSTR  cfgFile, char* cfgName, char* cfgVal, int  size)
{

	FILE* fp = NULL;
	char buf[MAX_CFG_NAME_LEN + MAX_CFG_VAL_LEN + 1];
	char cfgNameBuf[MAX_CFG_NAME_LEN + 1], cfgValBuf[MAX_CFG_VAL_LEN + 1];
	char fmt[32];
	int iRet = -1;

	if (strlen(cfgName) > MAX_CFG_NAME_LEN || size > MAX_CFG_VAL_LEN + 1)
		return -1;

	if (!(fp = _tfopen(cfgFile, _T("r"))))  return  -1;

	sprintf(fmt, "%%%ds%%%ds", MAX_CFG_NAME_LEN, MAX_CFG_VAL_LEN);

	for (;;) {
		if (!fgets(buf, sizeof(buf), fp)) break;
		if (2 != sscanf(buf, fmt, cfgNameBuf, cfgValBuf)) continue;
		if (strcmp(cfgNameBuf, cfgName)) continue;
		iRet = 0;
		break;
	}

	if (!iRet) strcpy(cfgVal, cfgValBuf);

	fclose(fp);

	return iRet;


}


__declspec(dllexport)  extern  "C"  int  getCfgValByNameT(LPCTSTR  cfgFile, TCHAR* cfgName, TCHAR* cfgVal, int  size)
{

	FILE* fp = NULL;
	TCHAR		buf[MAX_CFG_NAME_LEN + MAX_CFG_VAL_LEN + 1];
	TCHAR		cfgNameBuf[MAX_CFG_NAME_LEN + 1], cfgValBuf[MAX_CFG_VAL_LEN + 1];
	TCHAR		fmt[32];
	int			iRet = -1;

	if (lstrlen(cfgName) > MAX_CFG_NAME_LEN || size > MAX_CFG_VAL_LEN + 1)  return  -1;

	if (!(fp = _tfopen(cfgFile, _T("r,ccs=UNICODE"))))  return  -1;

	_sntprintf(fmt, mycountof(fmt), _T("%%%ds%%%ds"), MAX_CFG_NAME_LEN, MAX_CFG_VAL_LEN);

	//
	int len_cfgName = _tcslen(cfgName);

	//
	for (; ; ) {
		if (!_fgetts(buf, mycountof(buf), fp))  break;
		//
		tTrim(buf);
		//
#if 0
		OutputDebugString(buf);  OutputDebugString(_T("\n"));
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

		iRet = 0;
		break;
	}

	if (!iRet) lstrcpyn(cfgVal, cfgValBuf, size);

	fclose(fp);

	return  iRet;

}




//
int get_iCfgVal(TCHAR* smCfgFile, TCHAR* cfgName)
{
	bool  bRet = false;

	//	 
	TCHAR  cfgVal[128] = _T("");

	//
	if (!cfgName)  return  0;


	//USB Video Device
	getCfgValByNameT(smCfgFile, (TCHAR*)cfgName, cfgVal, mycountof(cfgVal));
	tTrim(cfgVal);
	int  tmpiRet = _ttol(cfgVal);

	//bRet = tmpiRet;

	//	 
	return  tmpiRet;

}


//
atbool  get_bCfgVal(TCHAR* smCfgFile, TCHAR* cfgName)
{
	//
	return  (bool)get_iCfgVal(smCfgFile, cfgName);

}


//
int waitFor_dbg_service(char  *  hint)
{
	if (!hint)  hint = (char*)("");

#ifdef  _DEBUG
	int i;
	int max_i = 10000;

	//
	debugLog((char*)"wait for dbg_service to be true");
	//
	for (i = 0; i < max_i; i++) {
		int  iVal;
		iVal = get_iCfgVal((TCHAR*)_T("d:\\qycx\\mgr_smCfg.ini"), (TCHAR*)_T("dbg_service"));
		if (iVal) {
			break;
		}
		//
		Sleep(1000);
		continue;
	}
	debugLog((char*)"wait finished. i %d. l169", i);
#endif

	//
	return  0;
}

