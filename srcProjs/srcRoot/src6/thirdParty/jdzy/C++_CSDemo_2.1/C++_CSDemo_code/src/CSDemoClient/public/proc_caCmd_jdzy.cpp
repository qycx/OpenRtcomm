
#include	"stdafx.h"

#include	<Windows.h>
#include	<tchar.h>
#include	<MMSystem.h>

#include	"tmpRegFunc_open.h"

#include	"proc_ca_jdzy.h"
#include	"resource.h"
#include <CSDemoClientDlg.h>


//
DWORD getCertSettings(char* strCertSettings)
{
	//char sKeyInfo[MAX_DATA_LEN] = "<?xml version=\"1.0\" encoding=\"gb2312\"?><authinfo><liblist><lib type=\"CSP\" version=\"1.0\" dllname=\"\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib><lib type=\"SKF\" version=\"1.1\" dllname=\"SERfR01DQUlTLmRsbA==\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib><lib type=\"SKF\" version=\"1.1\" dllname=\"U2h1dHRsZUNzcDExXzMwMDBHTS5kbGw=\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib><lib type=\"SKF\" version=\"1.1\" dllname=\"U0tGQVBJLmRsbA==\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib><lib type=\"SKF\" version=\"1.1\" dllname=\"U0tGQVBJMjAwNzkuZGxs\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib></liblist></authinfo>";
	
		//使用密码模块证书
	char sKeyInfo[MAX_DATA_LEN] = "<?xml version=\"1.0\" encoding=\"gb2312\"?><authinfo><liblist><lib type=\"CSP\" version=\"1.0\" dllname=\"\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib><lib type=\"SKF\" version=\"1.1\" dllname=\"SklUU2FmZU1vZGVsLmRsbA\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib></liblist></authinfo>";

	//使用龙脉key证书
	//char sKeyInfo[MAX_DATA_LEN] = "<?xml version=\"1.0\" encoding=\"gb2312\"?><authinfo><liblist><lib type=\"CSP\" version=\"1.0\" dllname=\"\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib><lib type=\"SKF\" version=\"1.1\" dllname=\"bXRva2VuX2dtMzAwMC5kbGw\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib></liblist></authinfo>";

	
	
	if (NULL != strCertSettings)
		strcpy_s(strCertSettings, MAX_DATA_LEN, sKeyInfo);

	/*
	int nReadLen = 0;
	FILE *fp = NULL;
	fp = fopen("KeySettings.txt", "rb"); //在本示例中，假设 KEY类型管理信息 存放在 KeySettings.txt 文件中。
	if(fp != NULL)
	{
		nReadLen = fread(strCertSettings, sizeof(CHAR), 4096, fp);
		fclose(fp);
		fp = NULL;
		return nReadLen;
	}
	*/
	return 0;
}

#include    "showInfo_open.h"

int jdzy_ca_sendData()
{
	int  iErr = -1;

	/*
#ifdef  __USE_showInfo__
	initShowInfo_cli(0, _T("syncQ_showInfo_qmc"), (char*)"127.0.0.1", &gBuf.m_var.pShowInfoStruct);
	//
#if 0
	if (gBuf.m_var.appParams.bSys) set_who_showInfo(_T("bjca.serv"));
	else  set_who_showInfo(_T("bjca.cli"));
#endif
	set_who_showInfo(gBuf.m_var.appParams.who_showInfo);
#endif
*/

	//

	TCHAR  cfgName_caRandom[128];
	_sntprintf(cfgName_caRandom, mycountof(cfgName_caRandom), _T("%s%d"), _T(CONST_regValName_caRandom_prefix), gBuf.m_var.appParams.tn);
	//char* caRandom = (char*)(pMisCnt->commEncCtx.ucbCaRandomOk ? pMisCnt->commEncCtx.caRandom : "");
	
	unsigned  int  uiType = 0;
	char caRandom[256];
	unsigned  int len = sizeof(caRandom);
	if (tmpGetRegCfg_open(gBuf.m_var.hKeyRoot0, _T(CONST_rootKey_ca), cfgName_caRandom, &uiType, caRandom, &len))  goto  errLabel;
	caRandom[len] = 0;
	printLogChar("-----tmpGetRegCfg_open-------caRandom-----begin----------");
	printLogChar(caRandom);
	printLogChar("----tmpGetRegCfg_open--------caRandom-----end----------");

	//
	DWORD nLen = 0, dwError = 0;
	DWORD dwRet = AUTH_CODE_SUCCESS;


	///////////////////////////////////////////////////////////////////////////////
// 生成客户端到应用服务器的认证信息
///////////////////////////////////////////////////////////////////////////////
	TCHAR strOriginal[MAX_PATH] = { 0 };
	LPTSTR pAuthInfo = NULL;

	TCHAR tmpBuffer[] = _T("renzheng failed");
	//
	_tcscpy_s(strOriginal, MAX_PATH, (LPCTSTR)_bstr_t(caRandom));
	if ((_tcsicmp(strOriginal, tmpBuffer) == 0) || (0 == _tcslen(strOriginal)))
	{
		dwRet = AUTH_CODE_FAIL;
	}
	else
	{
		DWORD nLen = _tcslen((LPCTSTR)_bstr_t(caRandom));
		strOriginal[nLen] = _T('\0');

	}
	if (dwRet)  goto  errLabel;


	//
		// 获取根证书主题
	TCHAR strRootDN[STRING_LENGTH] = { 0 };
	//GetDlgItemText(IDC_EDITRootDN, strRootDN, STRING_LENGTH);

	//获取KEY类型管理信息, 此信息由网关服务器导出
	char szCertSettings[MAX_DATA_LEN] = { 0 };
	getCertSettings(szCertSettings);
	TCHAR* strCertSettings = _bstr_t(szCertSettings);


	
		///////////////////////////////////////////////////////////////////////////////
		// 证书认证，生成认证请求XML
		///////////////////////////////////////////////////////////////////////////////
		//获取缓冲区大小

	showInfo_open0(0, 0, _T("jdzy_ca_sendData -----begin-----------"));
	showInfo_open0(0, 0, strOriginal);
	showInfo_open0(0, 0, strCertSettings);
	showInfo_open0(0, 0, strRootDN);
	showInfo_open0(0, 0, _T("jdzy_ca_sendData -------end------------"));

	printLogChar("Original ----------- begin");
	printLog(strOriginal);
	printLog(strCertSettings);


		dwError = gBuf.m_var.m_pClientAuth->StartAuth(NULL, nLen, strOriginal, strCertSettings, strRootDN, NULL, NULL, 1);
		if (dwError == AUTH_CODE_SUCCESS)
		{
			if (nLen > 0)
			{
				pAuthInfo = new TCHAR[nLen + 1];
				if (pAuthInfo != NULL)
				{
					memset(pAuthInfo, 0, sizeof(TCHAR) * (nLen + 1));
					dwError = gBuf.m_var.m_pClientAuth->StartAuth(pAuthInfo, nLen, strOriginal, strCertSettings, strRootDN, NULL, NULL, 1);
					showInfo_open0(0, 0, pAuthInfo);
				}
			}
		}

		if (dwError) {
			goto  errLabel;
		}

		printLog(pAuthInfo);
		printLogChar("Original ----------- end");
	

	TCHAR* strRequesInfo = pAuthInfo;

	{
		//
		//dwError = verifyAuthRequest(strServerIP, strServerPort, pAuthInfo);
		string strSendMsg = (LPCSTR)(_bstr_t(strRequesInfo));
		DWORD   dwLens = strSendMsg.length();

		//
		TCHAR  cfgName_sendData[128];
		_sntprintf(cfgName_sendData, mycountof(cfgName_sendData), _T("%s%d"), _T(CONST_regValName_ca_sendData_prefix), gBuf.m_var.appParams.tn);
		tmpSetRegCfg_open(gBuf.m_var.hKeyRoot0, _T(  CONST_rootKey_ca  ), cfgName_sendData, REG_BINARY, (char*)strSendMsg.c_str(), strSendMsg.length());


	}

	//
	iErr = 0;
errLabel:

	if (pAuthInfo) {
		delete  pAuthInfo;  pAuthInfo = NULL;
	}

	return  iErr;
}


