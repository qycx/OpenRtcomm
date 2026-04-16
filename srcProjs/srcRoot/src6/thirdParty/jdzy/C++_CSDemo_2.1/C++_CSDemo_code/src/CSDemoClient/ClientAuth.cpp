#include	"stdafx.h"
#include "ClientAuth.h"

#include <atlconv.h>
//#include <afxstr.h>

extern int printLogChar(const char* log);
extern int printLog(TCHAR* log);


//CSKFAPI* g_pGmTest = new CSKFAPI();

CSKFAPI* g_pGmTest = NULL;

void InitGm(bool jitSafeModule) {
	g_pGmTest = new CSKFAPI(jitSafeModule);
}


DWORD CClientAuth::Encode(const void* pBuffer, unsigned long nBufferSize, LPTSTR strRandOriginal, unsigned long dwFlags)
{
	static const char s_chBase64EncodingTable[64] = {
		_T('A'), _T('B'), _T('C'), _T('D'), _T('E'), _T('F'), _T('G'), _T('H'), _T('I'), _T('J'), _T('K'), _T('L'), _T('M'), _T('N'), _T('O'), _T('P'), _T('Q'),
		_T('R'), _T('S'), _T('T'), _T('U'), _T('V'), _T('W'), _T('X'), _T('Y'), _T('Z'), _T('a'), _T('b'), _T('c'), _T('d'), _T('e'), _T('f'), _T('g'),	_T('h'),
		_T('i'), _T('j'), _T('k'), _T('l'), _T('m'), _T('n'), _T('o'), _T('p'), _T('q'), _T('r'), _T('s'), _T('t'), _T('u'), _T('v'), _T('w'), _T('x'), _T('y'),
		_T('z'), _T('0'), _T('1'), _T('2'), _T('3'), _T('4'), _T('5'), _T('6'), _T('7'), _T('8'), _T('9'), _T('+'), _T('/')
	};

	DWORD nLen = 0;
	if (strRandOriginal == NULL)
	{
		return nLen;
	}

	const unsigned char* pbSrcData = (unsigned char*)pBuffer;

	if (!pbSrcData || (nBufferSize == 0))
	{
		return NULL;
	}

	int nRequiredLen = 0;
	{
		__int64 nSrcLen4 = static_cast<__int64>(nBufferSize) * 4;
		nRequiredLen = static_cast<int>(nSrcLen4 / 3);

		if ((dwFlags & BASE64_FLAG_NOPAD) == 0)
			nRequiredLen += nBufferSize % 3;

		int nCRLFs = nRequiredLen / 76 + 1;
		int nOnLastLine = nRequiredLen % 76;

		if (nOnLastLine)
		{
			if (nOnLastLine % 4)
				nRequiredLen += 4 - (nOnLastLine % 4);
		}

		nCRLFs *= 2;

		if ((dwFlags & BASE64_FLAG_CRLF) != 0)
			nRequiredLen += nCRLFs;
	}

	if (nRequiredLen == 0)
	{
		return NULL;
	}

	nRequiredLen++;

	m_apEncoded.reset(new TCHAR[nRequiredLen]);
	memset(m_apEncoded.get(), 0, nRequiredLen * sizeof(TCHAR));
	TCHAR* pszDest = m_apEncoded.get();

	int nWritten(0);
	int nLen1((nBufferSize / 3) * 4);
	int nLen2(nLen1 / 76);
	int nLen3(19);

	for (int i = 0; i <= nLen2; i++)
	{
		if (i == nLen2)
			nLen3 = (nLen1 % 76) / 4;

		for (int j = 0; j < nLen3; j++)
		{
			unsigned long dwCurr(0);
			for (int n = 0; n < 3; n++)
			{
				dwCurr |= *pbSrcData++;
				dwCurr <<= 8;
			}
			for (int k = 0; k < 4; k++)
			{
				unsigned char b = (unsigned char)(dwCurr >> 26);
				*pszDest++ = s_chBase64EncodingTable[b];
				dwCurr <<= 6;
			}
		}
		nWritten += nLen3 * 4;

		if ((dwFlags & BASE64_FLAG_CRLF) != 0)
		{
			*pszDest++ = _T('\r');
			*pszDest++ = _T('\n');
			nWritten += 2;
		}
	}

	if (nWritten && (dwFlags & BASE64_FLAG_CRLF) != 0)
	{
		pszDest -= 2;
		nWritten -= 2;
	}

	nLen2 = (nBufferSize % 3) ? (nBufferSize % 3 + 1) : 0;
	if (nLen2)
	{
		unsigned long dwCurr(0);
		for (unsigned long n = 0; n < 3; n++)
		{
			if (n < (nBufferSize % 3))
				dwCurr |= *pbSrcData++;
			dwCurr <<= 8;
		}
		for (int k = 0; k < nLen2; k++)
		{
			unsigned char b = (unsigned char)(dwCurr >> 26);
			*pszDest++ = s_chBase64EncodingTable[b];
			dwCurr <<= 6;
		}
		nWritten += nLen2;
		if ((dwFlags & BASE64_FLAG_NOPAD) == 0)
		{
			nLen3 = nLen2 ? 4 - nLen2 : 0;
			for (int j = 0; j < nLen3; j++)
			{
				*pszDest++ = _T('=');
			}
			nWritten += nLen3;
		}
	}

	m_apEncoded.get()[nWritten] = 0;

	_tcscpy(strRandOriginal, m_apEncoded.get());
	nLen = _tcslen(strRandOriginal);
	return nLen;
}

unsigned char* CClientAuth::Decode(const TCHAR* lpszSource, unsigned long* pnResultLen)
{
#define DECODE_BASE64_CHAR(x) (((x >= _T('A')) && (x <= _T('Z'))) ? (x - _T('A')) : (((x >= _T('a')) && (x <= _T('z'))) ? (x - _T('a') + 26) : (((x >= _T('0')) && (x <= _T('9'))) ? (x - _T('0') + 52) : ((x == _T('+')) ? 62 : ((x == _T('/')) ? 63 : -1)))))

	// walk the source buffer
	// each four character sequence is converted to 3 bytes
	// CRLFs and =, and any characters not in the encoding table
	// are skiped

	if (lpszSource == NULL || pnResultLen == NULL)
	{
		return NULL;
	}

	unsigned long nSrcLen = (unsigned long)_tcslen(lpszSource);
	if (nSrcLen == 0)
	{
		return NULL;
	}

	const TCHAR* szSrc = lpszSource;

	m_apDecoded.reset(new unsigned char[nSrcLen]);
	memset(m_apDecoded.get(), 0, nSrcLen);
	unsigned char* pbDest = m_apDecoded.get();

	const TCHAR* szSrcEnd = szSrc + nSrcLen;
	unsigned long nWritten = 0;

	bool bOverflow = (pbDest == NULL) ? true : false;

	while (szSrc < szSrcEnd && (*szSrc) != 0)
	{
		unsigned long dwCurr = 0;
		int i;
		int nBits = 0;
		for (i = 0; i < 4; i++)
		{
			if (szSrc >= szSrcEnd)
				break;
			int nCh = DECODE_BASE64_CHAR(*szSrc);
			szSrc++;
			if (nCh == -1)
			{
				// skip this char
				i--;
				continue;
			}
			dwCurr <<= 6;
			dwCurr |= nCh;
			nBits += 6;
		}

		if (!bOverflow && nWritten + (nBits / 8) > nSrcLen)
			bOverflow = true;

		// dwCurr has the 3 bytes to write to the output buffer
		// left to right
		dwCurr <<= 24 - nBits;
		for (i = 0; i < nBits / 8; i++)
		{
			if (!bOverflow)
			{
				*pbDest = (unsigned char)((dwCurr & 0x00ff0000) >> 16);
				pbDest++;
			}
			dwCurr <<= 8;
			nWritten++;
		}
	}

	*pnResultLen = nWritten;

	if (bOverflow)
	{
		return NULL;
	}

	return m_apDecoded.get();
}

unsigned long CClientAuth::GetEncodeRequiredLength(unsigned long nSrcLen, unsigned long dwFlags)
{
	__int64 nSrcLen4 = static_cast<__int64>(nSrcLen) * 4;
	unsigned long nRet = static_cast<unsigned long>(nSrcLen4 / 3);

	if ((dwFlags & BASE64_FLAG_NOPAD) == 0)
		nRet += nSrcLen % 3;

	unsigned long nCRLFs = nRet / 76 + 1;
	unsigned long nOnLastLine = nRet % 76;

	if (nOnLastLine)
	{
		if (nOnLastLine % 4)
			nRet += 4 - (nOnLastLine % 4);
	}

	nCRLFs *= 2;

	if ((dwFlags & BASE64_FLAG_CRLF) != 0)
		nRet += nCRLFs;

	return nRet;
}

DWORD UnicodeToUTF8(LPCTSTR str, string& tostr)
{
	char* pElementText = NULL;
	int iTextLen = 0;
	iTextLen = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset(pElementText, 0, sizeof(char) * (iTextLen + 1));

#ifdef _MSC_VER
	::WideCharToMultiByte(CP_UTF8, 0, str, -1, pElementText, iTextLen, NULL, NULL);
#else
	WideCharToMultiByte(CP_UTF8, 0, str, -1, pElementText, iTextLen, NULL, NULL);
#endif
	tostr = pElementText;
	delete[] pElementText;
	return 0;
}


///////////////////////////////////////////////////////////////////////////////
// 生成认证请求数据
///////////////////////////////////////////////////////////////////////////////
DWORD CClientAuth::buildAuthRequest(LPCTSTR strCertSettings, LPCTSTR strRootDN, LPCTSTR strRandOriginal, LPTSTR strAuthRequest, DWORD nLength, BOOL bSingleCert)
{
	DWORD dwRet = AUTH_CODE_SUCCESS, nLen = 0;
	LONG result = 0;
	USES_CONVERSION;
	LPCSTR certSetting = W2A(strCertSettings);
	string csAuthRequest;
	//TCHAR InitBuffer[] = _T("<?xml version=\"1.0\" encoding=\"gb2312\"?><authinfo><liblist><lib type=\"CSP\" version=\"1.0\" dllname=\"\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib><lib type=\"SKF\" version=\"1.1\" dllname=\"SERfR01DQUlTLmRsbA==\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib><lib type=\"SKF\" version=\"1.1\" dllname=\"U2h1dHRsZUNzcDExXzMwMDBHTS5kbGw=\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib><lib type=\"SKF\" version=\"1.1\" dllname=\"U0tGQVBJLmRsbA==\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib></liblist></authinfo>");

	if (strAuthRequest == NULL || strRandOriginal == NULL)
	{
		dwRet = AUTH_CODE_FAIL;
		return dwRet;
	}

	CoInitialize(NULL); //初始化COM

	IPNXDataTrans* pPNXClient = NULL;
	HRESULT hr = CoCreateInstance(__uuidof(PNXDataTrans), NULL, CLSCTX_INPROC_SERVER, __uuidof(IPNXDataTrans), (void**)&pPNXClient);

	if (FAILED(hr))
	{
		dwRet = AUTH_CODE_CREATE_PNXCLIENT_FAIL;
		return dwRet;
	}

	hr = pPNXClient->Initialize(_T(""), _bstr_t(certSetting), &result);
	if (FAILED(hr))
	{
		pPNXClient->Finalize(&result);
		dwRet = AUTH_CODE_INIT_PNXCLIENT_FAIL;
		return dwRet;
	}
	// 根据根证书主题过滤证书
	if (bSingleCert)
	{
		hr = pPNXClient->SetChooseSingleCert(1, &result);
	}
	else
	{
		hr = pPNXClient->SetChooseSingleCert(0, &result);
	}

	hr = pPNXClient->AddFilter(11, _bstr_t(W2A(_T("2"))), &result);

	if (FAILED(hr))
	{
		pPNXClient->Finalize(&result);
		dwRet = AUTH_CODE_SELECT_CERT_FAIL;
		return dwRet;
	}
	// 生成认证原文认证请求信息

	BSTR pSignResult = NULL;
	//	hr = pPNXClient->P7SignString(_bstr_t(W2A(strRandOriginal)),TRUE,TRUE,&pSignResult);

	std::string strCertSN = g_pGmTest->GM_GetSignCertSN();	//证书序列号
	std::string strPIN = "Aa111111";		//吉大密码模块pin码
	//std::string strPIN = "12345678";		//龙脉pin码

	printLogChar("---------strCertSN-------------begin-------");
	printLogChar(strCertSN.c_str());
	printLogChar("---------strCertSN------------end--------");

	CBase64 base64;
	CHAR* pRand = W2A(strRandOriginal);
	CString csOrigBase64 = base64.Encode(pRand, strlen(pRand));
	hr = pPNXClient->P7SignWithPin(_bstr_t(strCertSN.c_str()), _bstr_t(strPIN.c_str()), _bstr_t(W2A(csOrigBase64.GetString())), TRUE, TRUE, &pSignResult);

	//TCHAR* csOrigBase64 = base64.Encode(pRand, strlen(pRand));
	//hr = pPNXClient->P7SignWithPin(_bstr_t(strCertSN.c_str()), _bstr_t(strPIN.c_str()), _bstr_t(W2A(csOrigBase64)), TRUE, TRUE, &pSignResult);

	

	if (strlen(_bstr_t(pSignResult)) == 0 || FAILED(hr))
	{
		pPNXClient->Finalize(&result);
		dwRet = AUTH_CODE_AUTH_QUERY_FAIL;
		return dwRet;
	}

	std::string strRsp;
	UnicodeToUTF8(pSignResult, strRsp);
	Json::Value root;
	Json::Reader reader;
	bool bResult = reader.parse(strRsp, root);
	if (bResult && !root.isNull() && root.isObject())
	{
		if (root["result"].isUInt())
		{
			DWORD dwResult = root["result"].asUInt();
			if (dwResult == 0)
			{
				if (root["signdata"].isString())
				{
					std::string	strSignData = root["signdata"].asString();
					_tcscpy(strAuthRequest, _bstr_t(strSignData.c_str()));

					//签名成功 拷贝完毕 可以返回了
					dwRet = AUTH_CODE_SUCCESS;
					goto end;
				}
				else
				{
					dwRet = AUTH_CODE_AUTH_QUERY_FAIL;
					goto end;
				}
			}
			else
			{
				dwRet = AUTH_CODE_AUTH_QUERY_FAIL;
				goto end;
			}
		}
		else
		{
			dwRet = AUTH_CODE_AUTH_QUERY_FAIL;
			goto end;
		}
	}

	//内存足够大
	if (nLength >= strlen(_bstr_t(pSignResult)))
	{
		_tcscpy(strAuthRequest, _bstr_t(pSignResult));
	}
	else
	{
		dwRet = AUTH_CODE_NOT_ENOUGH_MEMORY;

	}
end:
	pPNXClient->Finalize(&result);

	pPNXClient->Release();

	CoUninitialize();
	return dwRet;
}

DWORD CClientAuth::StartAuth(LPTSTR strRequestAuthInfo, DWORD& dwLen, LPTSTR strRandOriginal, LPCTSTR strCertSettings, LPCTSTR strRootDN, LPCTSTR strUserName, LPCTSTR strPassword, DWORD bCertOrPwd, BOOL bSingleCert)
{
	///////////////////////////////////////////////////////////////////////////////
	// 生成客户端到应用服务器的认证信息
	///////////////////////////////////////////////////////////////////////////////
	static PTCHAR strAuthInfo = NULL;
	DWORD dwAuthLen = 0, nLength = 0, dwRet = AUTH_CODE_SUCCESS;

	if (strRandOriginal == NULL)
	{
		dwRet = AUTH_CODE_FAIL;
		return dwRet;
	}

	if (strRequestAuthInfo != NULL)
	{
		//第二次调用
		//返回认证请求原文
		if (strAuthInfo != NULL)
		{
			_tcscpy(strRequestAuthInfo, strAuthInfo);
			delete strAuthInfo;
			strAuthInfo = NULL;
		}
		else
		{
			dwRet = AUTH_CODE_FAIL;
		}

		return dwRet;
	}

	if (strAuthInfo == NULL)
	{
		nLength = MAX_DATA_LEN * 2;
		strAuthInfo = new TCHAR[nLength];
		if (strAuthInfo != NULL)
		{
			if (bCertOrPwd == 1)
			{
				// 生成认证请求信息
				DWORD nLen = MAX_DATA_LEN * 2;
				TCHAR csAuthRequest[MAX_DATA_LEN * 2] = { 0 }, EncodeOriginal[MAX_PATH] = { 0 };

				if (_tcslen(strRandOriginal) != 0)
				{
					dwRet = buildAuthRequest(strCertSettings, strRootDN, strRandOriginal, csAuthRequest, nLen, bSingleCert);
					if (dwRet == AUTH_CODE_SUCCESS)
					{
						dwAuthLen = 0;
						// 组织认证原文信息

						CHAR csRandOriginal[MAX_PATH] = { 0 };
						strcpy(csRandOriginal, (LPCSTR)_bstr_t(strRandOriginal));

						Encode(csRandOriginal, strlen(csRandOriginal), EncodeOriginal);

						_tcscpy(strAuthInfo + dwAuthLen, _T("<authCredential authMode=\"cert\">\r\n"));
						dwAuthLen += _tcslen(_T("<authCredential authMode=\"cert\">\r\n"));

						_tcscpy(strAuthInfo + dwAuthLen, _T("<detach>"));
						dwAuthLen += _tcslen(_T("<detach>"));

						_tcscpy(strAuthInfo + dwAuthLen, LPCTSTR(csAuthRequest));
						dwAuthLen += _tcslen(LPCTSTR(csAuthRequest));

						_tcscpy(strAuthInfo + dwAuthLen, _T("</detach>\r\n"));
						dwAuthLen += _tcslen(_T("</detach>\r\n"));

						_tcscpy(strAuthInfo + dwAuthLen, _T("<original>"));
						dwAuthLen += _tcslen(_T("<original>"));

						_tcscpy(strAuthInfo + dwAuthLen, EncodeOriginal);
						dwAuthLen += _tcslen(EncodeOriginal);

						_tcscpy(strAuthInfo + dwAuthLen, _T("</original>\r\n"));
						dwAuthLen += _tcslen(_T("</original>\r\n"));

						_tcscpy(strAuthInfo + dwAuthLen, _T("</authCredential>\r\n"));
						dwAuthLen += _tcslen(_T("</authCredential>\r\n"));
					}
					else
					{
						if (strAuthInfo != NULL)
						{
							delete strAuthInfo;
							strAuthInfo = NULL;
						}
						return dwRet;
					}
				}

			}
			else if (bCertOrPwd == 2)
			{
				dwAuthLen = 0;
				// 组织口令信息
				_tcscpy(strAuthInfo + dwAuthLen, _T("<authCredential authMode=\"password\">\r\n"));
				dwAuthLen = _tcslen(strAuthInfo);


				_tcscpy(strAuthInfo + dwAuthLen, _T("<username>"));
				dwAuthLen = _tcslen(strAuthInfo);

				_tcscpy(strAuthInfo + dwAuthLen, strUserName);
				dwAuthLen = _tcslen(strAuthInfo);

				_tcscpy(strAuthInfo + dwAuthLen, _T("</username>\r\n"));
				dwAuthLen = _tcslen(strAuthInfo);

				_tcscpy(strAuthInfo + dwAuthLen, _T("<password>"));
				dwAuthLen = _tcslen(strAuthInfo);

				_tcscpy(strAuthInfo + dwAuthLen, strPassword);
				dwAuthLen = _tcslen(strAuthInfo);

				_tcscpy(strAuthInfo + dwAuthLen, _T("</password>\r\n"));
				dwAuthLen = _tcslen(strAuthInfo);

				_tcscpy(strAuthInfo + dwAuthLen, _T("</authCredential>\r\n"));
				dwAuthLen = _tcslen(strAuthInfo);

			}
		}
	}

	dwLen = dwAuthLen;
	return dwRet;
}