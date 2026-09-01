
#include	"stdafx.h"

#include	<string.h>
#include	<tchar.h>
#include	<stdlib.h>

#include	"myCmdParams_open.h"
#include	"tmpDefs_open.h"
#include	"tmpStrFunc.h"
#include	"qytcharcommproc.h"




//
int  parseCmdLine_ca(TCHAR* pCmdLine, AppParams_ca* pParams)
{
	int		iErr = -1;

	TCHAR* pT;
	TCHAR* pT1;
	TCHAR* pT2;
	//
	TCHAR		tBuf[256];

	//
	if (!pParams)  return  -1;

	memset(pParams, 0, sizeof(pParams[0]));

	for (pT = (TCHAR*)pCmdLine; pT; ) {
		if (!(pT = _tcschr(pT, _T('-'))))  break;
		pT++;
		switch (*pT) {
		case  _T('a'):
		case  _T('A'):
			break;
		case  _T('c'):
		case  _T('C'):
			//
			pT1 = (TCHAR*)CONST_qmCmdLine_ca;
			if (!_tcsnicmp(pT, pT1, _tcslen(pT1))) {
				//
				pT += _tcslen(pT1);
				pParams->iCmd = _ttol(pT);
				break;
			}
			//
			pT1 = (TCHAR*)CONST_qmCmdLine_caServ;
			if (!_tcsnicmp(pT, pT1, _tcslen(pT1))) {
				//
				pT += _tcslen(pT1);
				//
				TCHAR  tBuf[256];
				M_getCmd(pT, tBuf, mycountof(tBuf));
				myTChar2Utf8(tBuf, pParams->caGwIp, mycountof(pParams->caGwIp));
				break;
			}
			//
			pT1 = (TCHAR*)CONST_qmCmdLine_caPort;
			if (!_tcsnicmp(pT, pT1, _tcslen(pT1))) {
				//
				pT += _tcslen(pT1);
				//
				TCHAR  tBuf[256];
				M_getCmd(pT, tBuf, mycountof(tBuf));
				pParams->caGwPort = _ttol(tBuf);
				break;
			}
			//
			break;
			//
		case  _T(  'd'):
		case  _T(  'D'):
			//
			pT1 = (TCHAR*)CONST_qmCmdLine_devPrefix;
			if (!_tcsnicmp(pT, pT1, _tcslen(pT1))) {
				//
				pT += _tcslen(pT1);
				//
				//_tcsncpy(pParams->devPrefix, pT, sizeof(pParams->devPrefix)/sizeof(pParams->devPrefix[0]));
				M_getCmd(pT, pParams->devPrefix, mycountof(pParams->devPrefix));
				//
				break;
			}
			//
			pT1 = (TCHAR*)CONST_qmCmdLine_devName;
			if (!_tcsnicmp(pT, pT1, _tcslen(pT1))) {
				//
				pT += _tcslen(pT1);
				//
				//_tcsncpy(pParams->devPrefix, pT, sizeof(pParams->devPrefix)/sizeof(pParams->devPrefix[0]));
				M_getCmd(pT, pParams->devPrefix, mycountof(pParams->devPrefix));
				//
				pParams->bFullCmp = true;
				//
				break;
			}
			//
			pT1 = (TCHAR*)CONST_qmCmdLine_dev;
			if (!_tcsnicmp(pT, pT1, _tcslen(pT1))) {
				//
				pT += _tcslen(pT1);
				pParams->bDev = _ttol(pT);
				break;
			}
			//
			break;
			//
		case  _T('l'):
		case  _T('L'):
			//
			pT1 = (TCHAR*)CONST_qmCmdLine_log;
			if (!_tcsnicmp(pT, pT1, _tcslen(pT1))) {
				//
				pT += _tcslen(pT1);
				M_getCmd(pT, pParams->logFile, mycountof(pParams->logFile));
				break;
			}
			break;
		case  _T(  'P'):
		case  _T(  'p'):
			//
			pT1 = (TCHAR*)CONST_qmCmdLine_pwd;
			if (!_tcsnicmp(pT, pT1, _tcslen(pT1))) {
				//
				pT += _tcslen(pT1);
				M_getCmd(pT, tBuf, mycountof(tBuf));
				myTChar2Utf8(tBuf, pParams->pwd, mycountof(pParams->pwd));
				break;
			}			  
			break;
			//
		case  _T('s'):
		case  _T(  'S'  ):
			//
			pT1 = (TCHAR*)CONST_qmCmdLine_sys;
			if (!_tcsnicmp(pT, pT1, _tcslen(pT1))) {
				//
				pT += _tcslen(pT1);
				pParams->bSys = _ttol(pT);
				break;
			}
			  break;
			//
		case  _T('t'):
			//
			pT1 = (TCHAR*)CONST_qmCmdLine_tn;
			if (!_tcsnicmp(pT, pT1, _tcslen(pT1))) {
				//
				pT += _tcslen(pT1);
				int  tn = _tcstoul(pT, &pT2, 10);
				//
				pParams->tn = tn;
				//
				break;
			}
			//  2015/07/18
#ifdef  __DEBUG__
			pT1 = (TCHAR*)CONST_qmCmdLine_sym_test;
			if (!_tcsnicmp(pT, pT1, _tcslen(pT1))) {
				pT += _tcslen(pT1);
				pParams->iTestNo = _ttol(pT);
				//
				break;
			}
#endif

			break;
		case  _T('w'):
		case  _T('W'):
			//
			pT1 = (TCHAR*)CONST_qmCmdLine_who_showInfo;
			if (!_tcsnicmp(pT, pT1, _tcslen(pT1))) {
				//
				pT += _tcslen(pT1);
				//
				M_getCmd(pT, pParams->who_showInfo, mycountof(pParams->who_showInfo));
				//
				break;
			}
			break;
			//


		default:
			break;
		}
	}



	//
	iErr = 0;
	//errLabel:
	return  iErr;
}


//
int parseCmdLine_ipcProc(TCHAR* pCmdLine, AppParams_ipcProc* pParams)
{
	int  iErr = -1;

	TCHAR* pT;
	TCHAR* pT1;
	TCHAR* pT2;
	//
	TCHAR		tBuf[256];

	//
	if (!pParams)  return  -1;

	memset(pParams, 0, sizeof(pParams[0]));

	for (pT = (TCHAR*)pCmdLine; pT; ) {
		if (!(pT = _tcschr(pT, _T('-'))))  break;
		pT++;
		switch (*pT) {

			//
		case  _T('i'):
		case  _T('I'):
			//
			pT1 = (TCHAR*)CONST_qmCmdLine_ip;
			if (!_tcsnicmp(pT, pT1, _tcslen(pT1))) {
				//
				pT += _tcslen(pT1);
				M_getCmd(pT, tBuf, mycountof(tBuf));
				myTChar2Utf8(tBuf, pParams->nvrIp, mycountof(pParams->nvrIp));
				break;
			}
			break;
		case  _T('P'):
		case  _T('p'):
			//
			pT1 = (TCHAR*)CONST_qmCmdLine_pwd;
			if (!_tcsnicmp(pT, pT1, _tcslen(pT1))) {
				//
				pT += _tcslen(pT1);
				M_getCmd(pT, tBuf, mycountof(tBuf));
				myTChar2Utf8(tBuf, pParams->nvrPwd, mycountof(pParams->nvrPwd));
				break;
			}
			break;
			//
		case  _T('t'):
			//
			pT1 = (TCHAR*)CONST_qmCmdLine_tn;
			if (!_tcsnicmp(pT, pT1, _tcslen(pT1))) {
				//
				pT += _tcslen(pT1);
				int  tn = _tcstoul(pT, &pT2, 10);
				//
				pParams->tn = tn;
				//
				break;
			}
			break;
			//
			
		case  _T('l'):
		case  _T('L'):
			//
			pT1 = (TCHAR*)CONST_qmCmdLine_log;
			if (!_tcsnicmp(pT, pT1, _tcslen(pT1))) {
				//
				pT += _tcslen(pT1);
				int  log = _tcstoul(pT, &pT2, 10);
				//
				pParams->log = log;
				//
				break;
			}
			break;

		case  _T('d'):
		case  _T('D'):
			//
			pT1 = (TCHAR*)CONST_qmCmdLine_devType;
			if (!_tcsnicmp(pT, pT1, _tcslen(pT1))) {
				//
				pT += _tcslen(pT1);
				int  type = _tcstoul(pT, &pT2, 10);
				//
				pParams->devType = type;
				//
				break;
			}
			break;
			
			//
		case  _T(  'u'):
		case  _T(  'U'):
			//
			//
			pT1 = (TCHAR*)CONST_qmCmdLine_usr;
			if (!_tcsnicmp(pT, pT1, _tcslen(pT1))) {
				//
				pT += _tcslen(pT1);
				M_getCmd(pT, tBuf, mycountof(tBuf));
				lstrcpyn(pParams->nvrUsr, tBuf, mycountof(pParams->nvrUsr));
				break;
			}
			break;

			//
		default:
			break;
		}
	}



	//
	iErr = 0;
	//errLabel:
	return  iErr;

}

