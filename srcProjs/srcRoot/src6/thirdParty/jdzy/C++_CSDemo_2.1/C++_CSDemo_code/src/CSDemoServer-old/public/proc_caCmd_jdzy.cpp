

#include	"stdafx.h"

#include	<tchar.h>

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string.h>

#include    <tchar.h>
//
#include    "tmpRegFunc_open.h"
#include <showInfo_open.h>

#include	"proc_ca_jdzy.h"
#include    "resource.h"
#include    "CSDemoServerDlg.h"



//
int  jdzy_ca_getRandom()
{
    int  iErr = -1;

	DWORD  dwError;

    //
	{
		// 发送到认证服务器，取得认证原文，同时回应客户端
		DWORD dwLen = 0;
		LPTSTR pRndResponeInfo = NULL;
		string strRndReponse;
		dwError = gBuf.m_var.m_pServerAuth->GetRandOriginal(NULL, dwLen);
		if (dwError == AUTH_CODE_SUCCESS)
		{
			if (dwLen > 0)
			{
				pRndResponeInfo = new TCHAR[dwLen + 1];
				if (pRndResponeInfo != NULL)
				{
					dwError = gBuf.m_var.m_pServerAuth->GetRandOriginal(pRndResponeInfo, dwLen);
					if (dwError == AUTH_CODE_SUCCESS)
					{
						//成功则发送原文信息
						strRndReponse = _bstr_t(pRndResponeInfo);

					}

					delete pRndResponeInfo;
					pRndResponeInfo = NULL;
				}
			}
		}
		if (dwError != AUTH_CODE_SUCCESS)
		{
			//失败
			TCHAR strRndResponeInfo[MAX_PATH] = { 0 };
			_tcscpy(strRndResponeInfo, _T("认证失败！"));
			strRndReponse = _bstr_t(strRndResponeInfo);
		}

		//发送随机数回客户端 
		//send(clientsocket, strRndReponse.c_str(), (int)strRndReponse.length(), 0);
		//closesocket(clientsocket);

		//
		//
		char resp[1024]  =  "";
		//_snprintf(resp, mycountof(resp), "-%s%s", CONST_sym_usr, usrName);
		_snprintf(resp, mycountof(resp), "%s", strRndReponse.c_str());
		if (strlen(resp) != strRndReponse.length()) {
			goto  errLabel;
		}

		//
		{
			TCHAR  cfgName[128];
			_sntprintf(cfgName, mycountof(cfgName), _T("%s%d"), _T(CONST_regValName_ca_getRandomResp_prefix), gBuf.m_var.appParams.tn);
			unsigned int  uiType;
			uiType = REG_BINARY;
			tmpSetRegCfg_open(gBuf.m_var.hKeyRoot0, _T(CONST_rootKey_ca), cfgName, uiType, resp, strlen(resp));
		}

		//
		showInfo_open0(0, 0, _T("jdzy: getRandom ok"));



		//continue;
	}




    iErr = 0;
    errLabel:

    return  iErr;

}


//
int getUsrName(TCHAR* str, TCHAR* tUsrName, int  usrNameLen)
{
	int  iErr = -1;
	TCHAR  tBuf[256];

	if (!str)  return -1;
	if (!tUsrName)  return  -1;
	if (!usrNameLen)return  -1;


	lstrcpyn(tBuf, str, mycountof(tBuf));
	TCHAR* tag = _T("CN=");
	TCHAR* pT = tBuf;
	for (; *pT; pT++) {
		if (!_tcsnicmp(pT, tag, lstrlen(tag))) {
			break;
		}
	}
	if (!*pT) goto  errLabel;
	pT+=_tcslen(tag);
	TCHAR* pT1 = _tcschr(pT, _T(','));
	if (!pT1)  goto  errLabel;
	*pT1 = 0;
	lstrcpyn(tUsrName, pT, usrNameLen);


	iErr = 0;
errLabel:
	return  iErr;
}


//
void myDisplayAuthResult(TCHAR  *  tUsrName,  int usrNameLen)
{
	DWORD dwLen = 0, nLength = 0;
	TCHAR strAuthResult[MAX_DATA_LENGTH] = { 0 };
	long lTotalLength = MAX_DATA_LENGTH;
	TCHAR* strResult = new TCHAR[MAX_DATA_LENGTH];
	memset(strResult, 0, MAX_DATA_LENGTH * sizeof(TCHAR));
	PTCHAR pMessageCode = NULL;
	BOOL bIsSuccess = FALSE;

	if (gBuf.m_var.m_pServerAuth->GetMessageCode(NULL, nLength) == FALSE)
	{
		if (nLength == 0)
		{
			//当返回FALSE并且错误码长度为0时，表示认证成功
			bIsSuccess = TRUE;
		}
	}

	_stprintf_s(strResult, lTotalLength - dwLen - 1, _T("=====================================================\r\n"));
	dwLen += _tcslen(strResult);
	memset(strAuthResult, 0, MAX_DATA_LENGTH * sizeof(TCHAR));
	if (bIsSuccess)
	{
		LPCTSTR sAcr = gBuf.m_var.m_pServerAuth->GetAccessControlResult();
		if (NULL != sAcr && 0 == _tcsicmp(sAcr, _T("Deny")))
		{
			_stprintf_s(strAuthResult, _T("认证状态：true（true：成功，false：失败）\r\n没有权限!"));
		}
		else
			_stprintf_s(strAuthResult, _T("认证状态：true（true：成功，false：失败）\r\n"));
		_tcscpy(strResult + dwLen, strAuthResult);
		dwLen += _tcslen(strAuthResult);
	}
	else
	{
		_stprintf_s(strAuthResult, _T("认证状态：false（true：成功，false：失败）\r\n"));
		_tcscpy(strResult + dwLen, strAuthResult);
		dwLen += _tcslen(strAuthResult);
		//获取错误码
		if (gBuf.m_var.m_pServerAuth->GetMessageCode(NULL, nLength))
		{
			if (nLength > 0)
			{
				pMessageCode = new TCHAR[nLength + 1];
				if (pMessageCode != NULL)
				{
					if (gBuf.m_var.m_pServerAuth->GetMessageCode(pMessageCode, nLength))
					{
						memset(strAuthResult, 0, MAX_DATA_LENGTH * sizeof(TCHAR));
						_stprintf_s(strAuthResult, _T("错误码：%s\r\n"), pMessageCode);
						_tcscpy(strResult + dwLen, strAuthResult);
						dwLen += _tcslen(strAuthResult);
					}
					delete[] pMessageCode;
					pMessageCode = NULL;
				}
			}
		}
	}

	if (bIsSuccess)
	{
		_tcscpy(strResult + dwLen, _T("\r\n"));
		dwLen += _tcslen(_T("\r\n"));

		_tcscpy(strResult + dwLen, _T("-----------------------------------------------------\r\n"));
		dwLen += _tcslen(_T("-----------------------------------------------------\r\n"));
		int nAttributesCount = gBuf.m_var.m_pServerAuth->GetAttributeSize();
		for (int i = 0; i < nAttributesCount; i++)
		{
			TCHAR* cAttName = NULL;
			TCHAR* AttributeValue = NULL;
			TCHAR* AttributeNameSpace = NULL;
			long NameLength = 0, ValueLength = 0, SpaceLength = 0;
			gBuf.m_var.m_pServerAuth->GetAttribute(i, cAttName, NameLength, AttributeValue, ValueLength, AttributeNameSpace, SpaceLength);
			if (NameLength != 0)
			{
				cAttName = new TCHAR[NameLength];
			}
			if (ValueLength != 0)
			{
				AttributeValue = new TCHAR[ValueLength];
			}
			if (SpaceLength != 0)
			{
				AttributeNameSpace = new TCHAR[SpaceLength];
			}
			gBuf.m_var.m_pServerAuth->GetAttribute(i, cAttName, NameLength, AttributeValue, ValueLength, AttributeNameSpace, SpaceLength);

			long lTmpLength = NameLength + ValueLength + SpaceLength + 256;
			TCHAR* strAuthResultTmp = new TCHAR[lTmpLength];
			memset(strAuthResultTmp, 0, lTmpLength * sizeof(TCHAR));
			_stprintf_s(strAuthResultTmp, lTmpLength, _T("属性名称：%s\r\n属性值：%s\r\n名字空间：%s\r\n"), cAttName, AttributeValue, AttributeNameSpace);
			if (cAttName != NULL)
			{
				//
#define			CONST_attName_usrName	L"X509Certificate.SubjectDN"
				//
				if (!_tcsicmp(cAttName, CONST_attName_usrName)) {
					//
					getUsrName(AttributeValue, tUsrName, usrNameLen);
					//
				}
				
				//
				delete[] cAttName;
			}
			if (AttributeValue != NULL)
			{
				delete[] AttributeValue;
			}
			if (AttributeNameSpace != NULL)
			{
				delete[] AttributeNameSpace;
			}

			if (lTotalLength - dwLen < lTmpLength)
			{
				int i = lTmpLength / MAX_DATA_LENGTH;
				long lIncrementLength = (i + 1) * MAX_DATA_LENGTH;
				lTotalLength += lIncrementLength;
				TCHAR* pNewBuf = new TCHAR[lTotalLength];
				memset(pNewBuf, 0, lTotalLength * sizeof(TCHAR));
				memcpy(pNewBuf, strResult, dwLen * sizeof(TCHAR));
				delete[] strResult;
				strResult = pNewBuf;
			}

			_tcscpy(strResult + dwLen, strAuthResultTmp);
			dwLen += _tcslen(strAuthResultTmp);
			if (strAuthResultTmp != NULL)
			{
				delete[] strAuthResultTmp;
			}
		}



	}

	//SetDlgItemText(IDC_EDIT_STATUS, strResult);

	if (strResult != NULL)
	{
		delete[] strResult;
	}
}



//
int  jdzy_ca_login_auth()
{
	int  iErr = -1;

	//
	DWORD  dwError;

	//
	TCHAR  cfgName[128];
	_sntprintf(cfgName, mycountof(cfgName), _T("%s%d"), _T(CONST_regValName_ca_sendData_prefix), gBuf.m_var.appParams.tn);
	unsigned int  uiType;
	char pchrecvBuf[8192];
	unsigned  int len = sizeof(pchrecvBuf);
	if (tmpGetRegCfg_open(gBuf.m_var.hKeyRoot0, _T(CONST_rootKey_ca), cfgName, &uiType, pchrecvBuf, &len))  goto  errLabel;
	pchrecvBuf[len] = 0;

	//
	TCHAR  tBuf[256];
	_sntprintf(tBuf, mycountof(tBuf), _T("jdzy.auth: len %d,[%S]"), len,  pchrecvBuf);
	showInfo_open0(0, 0, tBuf);



	//
	sockaddr_in stClientInfo = { 0 };
	int nLen = sizeof(stClientInfo);

#if  10
	//getpeername(clientsocket, (sockaddr*)&stClientInfo, &nLen);
	// 发送到认证服务器认证，并处理服务器响应信息，同时回应客户端认证成功

	LPCTSTR  clientIp = _T("1.1.1.1");
	//clientIp = (LPCTSTR)_bstr_t(inet_ntoa(stClientInfo.sin_addr));

	TCHAR strAuthReponseInfo[MAX_PATH] = { 0 };
	dwError = gBuf.m_var.m_pServerAuth->StartAuth(_bstr_t((LPCSTR)pchrecvBuf), clientIp);
	if (dwError != AUTH_CODE_SUCCESS) {
		showInfo_open0(0, 0, _T("auth failed"));
		goto  errLabel;
	}

	showInfo_open0(0, 0, _T("auth ok"));

	//
	TCHAR  tUsrName[256];
	tUsrName[0] = 0;
	myDisplayAuthResult(tUsrName,mycountof(tUsrName));
	if (!tUsrName[0])goto  errLabel;

	{
		std::string str1;
		str1 = _bstr_t(tUsrName);
		//

		char resp[1024];
		_snprintf(resp, mycountof(resp), "-%s%s", CONST_sym_usr, str1.c_str());

		//
		{
			TCHAR  cfgName[128];
			_sntprintf(cfgName, mycountof(cfgName), _T("%s%d"), _T(CONST_regValName_ca_sendDataResp_prefix), gBuf.m_var.appParams.tn);
			unsigned int  uiType;
			uiType = REG_BINARY;
			tmpSetRegCfg_open(gBuf.m_var.hKeyRoot0, _T(CONST_rootKey_ca), cfgName, uiType, resp, strlen(resp));
		}


	}

	//
#endif


	iErr = 0;
errLabel:
	return  iErr;

}




