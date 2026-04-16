#include "CServerAuth.h"
#include "Shlwapi.h"

#include	<tchar.h>

#include "CServerDefine.h"
#include <showInfo_open.h>
#include "define_head.h"

//int (WINAPIV* __vsnprintf)(char*, size_t, const char*, va_list) = _vsnprintf;


#if _MSC_VER>=1900
#include "stdio.h" 
_ACRTIMP_ALT FILE* __cdecl __acrt_iob_func(unsigned);
#ifdef __cplusplus 
extern "C"
#endif 
FILE * __cdecl __iob_func(unsigned i) {
	return __acrt_iob_func(i);
}
#endif 
/* _MSC_VER>=1900 */

extern int printLogChar(const char* log);
extern int printLog(TCHAR* log);


TCHAR* CServerAuth::Encode(const void* pBuffer, unsigned long nBufferSize, unsigned long dwFlags)
{
	static const char s_chBase64EncodingTable[64] = {
		_T('A'), _T('B'), _T('C'), _T('D'), _T('E'), _T('F'), _T('G'), _T('H'), _T('I'), _T('J'), _T('K'), _T('L'), _T('M'), _T('N'), _T('O'), _T('P'), _T('Q'),
		_T('R'), _T('S'), _T('T'), _T('U'), _T('V'), _T('W'), _T('X'), _T('Y'), _T('Z'), _T('a'), _T('b'), _T('c'), _T('d'), _T('e'), _T('f'), _T('g'),	_T('h'),
		_T('i'), _T('j'), _T('k'), _T('l'), _T('m'), _T('n'), _T('o'), _T('p'), _T('q'), _T('r'), _T('s'), _T('t'), _T('u'), _T('v'), _T('w'), _T('x'), _T('y'),
		_T('z'), _T('0'), _T('1'), _T('2'), _T('3'), _T('4'), _T('5'), _T('6'), _T('7'), _T('8'), _T('9'), _T('+'), _T('/')
	};

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
	return m_apEncoded.get();
}

unsigned char* CServerAuth::Decode(const TCHAR* lpszSource, unsigned long* pnResultLen)
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

unsigned long CServerAuth::GetEncodeRequiredLength(unsigned long nSrcLen, unsigned long dwFlags)
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


DWORD CServerAuth::UnicodeToUTF8(LPCTSTR str, string& tostr)
{
	char* pElementText = NULL;
	int iTextLen = 0;
	iTextLen = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset(pElementText, 0, sizeof(char) * (iTextLen + 1));
	::WideCharToMultiByte(CP_UTF8, 0, str, -1, pElementText, iTextLen, NULL, NULL);
	tostr = pElementText;
	delete[] pElementText;
	return 0;
}

DWORD CServerAuth::UTF8ToUnicode(LPCSTR str, wstring& tostr)
{
	wchar_t* pElementText = NULL;
	int iTextLen = 0;
	iTextLen = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	pElementText = new wchar_t[iTextLen + 1];
	memset(pElementText, 0, sizeof(wchar_t) * (iTextLen + 1));
	::MultiByteToWideChar(CP_UTF8, 0, str, -1, pElementText, iTextLen);
	tostr = pElementText;
	delete[] pElementText;
	return 0;
}

CServerAuth::CServerAuth(LPCTSTR strGateWayIP, LPCTSTR strGatePort, LPCTSTR strAppFlag, bool bIsPlain, int nXMLVer)
{
	_tcscpy_s(m_strGateWayIP, strGateWayIP);
	_tcscpy_s(m_strGatePort, strGatePort);

	_tcscpy_s(m_strAppFlag, strAppFlag);
	m_bIsPlain = bIsPlain;
	m_nXMLVer = nXMLVer;

	m_pszRequest = NULL;
	m_nAuthLength = 0;

	//memset(&m_structReponseInfo.HeadInfo,0,sizeof(SReponseInfo)); 
	m_structReponseInfo.HeadInfo.MessageCode = NULL;
	m_structReponseInfo.HeadInfo.MessageDesc = NULL;
	m_structReponseInfo.HeadInfo.MessageStatue = NULL;
	m_structReponseInfo.HeadInfo.ServiceType = NULL;
	m_structReponseInfo.HeadInfo.Version = NULL;
	m_structReponseInfo.Body.AccessControl = NULL;
	m_structReponseInfo.Body.AttributesType = NULL;
	m_structReponseInfo.Body.Original = NULL;

	m_pReponseBody = NULL;
	m_dwLen = 0;

}

CServerAuth::~CServerAuth()
{

	//如果已经分配内存，则释放结构体动态分配的内存
	if (m_structReponseInfo.HeadInfo.Version != NULL)
	{
		delete[] m_structReponseInfo.HeadInfo.Version;
		m_structReponseInfo.HeadInfo.Version = NULL;
	}
	if (m_structReponseInfo.HeadInfo.ServiceType != NULL)
	{
		delete[] m_structReponseInfo.HeadInfo.ServiceType;
		m_structReponseInfo.HeadInfo.ServiceType = NULL;
	}
	if (m_structReponseInfo.HeadInfo.MessageStatue != NULL)
	{
		delete[] m_structReponseInfo.HeadInfo.MessageStatue;
		m_structReponseInfo.HeadInfo.MessageStatue = NULL;
	}
	if (m_structReponseInfo.HeadInfo.MessageDesc != NULL)
	{
		delete[] m_structReponseInfo.HeadInfo.MessageDesc;
		m_structReponseInfo.HeadInfo.MessageDesc = NULL;
	}
	if (m_structReponseInfo.HeadInfo.MessageCode != NULL)
	{
		delete[] m_structReponseInfo.HeadInfo.MessageCode;
		m_structReponseInfo.HeadInfo.MessageCode = NULL;
	}

	if (m_structReponseInfo.Body.AttributesType != NULL)
	{
		delete[] m_structReponseInfo.Body.AttributesType;
		m_structReponseInfo.Body.AttributesType = NULL;
	}
	if (m_structReponseInfo.Body.AccessControl != NULL)
	{
		delete[] m_structReponseInfo.Body.AccessControl;
		m_structReponseInfo.Body.AccessControl = NULL;
	}

	if (m_structReponseInfo.Body.Original != NULL)
	{
		delete[] m_structReponseInfo.Body.Original;
		m_structReponseInfo.Body.Original = NULL;
	}
	//
	//释放动态分配的内存
	for (vector<SAuthResult>::iterator iter = m_structReponseInfo.Body.AuthResults.begin(); iter != m_structReponseInfo.Body.AuthResults.end(); ++iter)
	{

		if ((*iter).AuthMode != NULL)
		{
			delete[](*iter).AuthMode;
		}
		if ((*iter).AuthMsgCode != NULL)
		{
			delete[](*iter).AuthMsgCode;
		}
		if ((*iter).AuthMsgDesc != NULL)
		{
			delete[](*iter).AuthMsgDesc;
		}
		if ((*iter).AuthStatue != NULL)
		{
			delete[](*iter).AuthStatue;
		}
	}
	//清空向量
	m_structReponseInfo.Body.AuthResults.erase(m_structReponseInfo.Body.AuthResults.begin(), m_structReponseInfo.Body.AuthResults.end());

	//
	//释放动态分配的内存
	for (vector<SAttributeItem>::iterator iter = m_structReponseInfo.Body.Attributes.begin(); iter != m_structReponseInfo.Body.Attributes.end(); ++iter)
	{
		if ((*iter).AttributeName != NULL)
		{
			delete[](*iter).AttributeName;
		}
		if ((*iter).AttributeNameSpace != NULL)
		{
			delete[](*iter).AttributeNameSpace;
		}
		if ((*iter).AttributeParentName != NULL)
		{
			delete[](*iter).AttributeParentName;
		}
		if ((*iter).AttributeValue != NULL)
		{
			delete[](*iter).AttributeValue;
		}
	}
	m_structReponseInfo.Body.Attributes.erase(m_structReponseInfo.Body.Attributes.begin(), m_structReponseInfo.Body.Attributes.end());


	if (m_pReponseBody)
	{
		delete[] m_pReponseBody;
		m_pReponseBody = NULL;
	}
}




// 发送到认证服务器认证，并处理服务器响应信息
DWORD CServerAuth::StartAuth(LPCTSTR pszReqInfo, LPCTSTR lpszClientIP)
{
	///////////////////////////////////////////////////
	// 参数检查
	///////////////////////////////////////////////////

	DWORD dwRet = AUTH_CODE_SUCCESS;
	PTCHAR pRequestBuffer = NULL, strReponseHttpBody = NULL;


	if (pszReqInfo == NULL)
	{
		dwRet = AUTH_CODE_FAIL;
		return dwRet;
	}

	///////////////////////////////////////////////////
	// 生成认证请求报文
	///////////////////////////////////////////////////
	DWORD dwRequest = BuildRequestXML(pszReqInfo, m_strAppFlag, lpszClientIP, NULL);
	if (dwRequest > 0)
	{
		pRequestBuffer = new TCHAR[dwRequest + 1];
		if (pRequestBuffer != NULL)
		{
			memset(pRequestBuffer, 0, sizeof(TCHAR) * (dwRequest + 1));
			dwRequest = BuildRequestXML(pszReqInfo, m_strAppFlag, lpszClientIP, pRequestBuffer);

			printLogChar("--------pRequestBuffer-------------begin---------");
			printLog(pRequestBuffer);
			printLogChar("--------pRequestBuffer-------------end---------");

		}

	}

	///////////////////////////////////////////////////
	// 发送请求报文到认证服务器
	///////////////////////////////////////////////////
	unsigned short usPort = atoi(_bstr_t(m_strGatePort));
	DWORD nLength = 0;

	if (m_bIsPlain == false)
	{
		//单向SSL
		dwRet = SendRequest_SingleSSL(pRequestBuffer, m_strGateWayIP, usPort, NULL, nLength);
		if (dwRet == AUTH_CODE_SUCCESS && nLength > 1)
		{
			strReponseHttpBody = new TCHAR[nLength + 1];
			if (strReponseHttpBody != NULL)
			{
				memset(strReponseHttpBody, 0, sizeof(TCHAR) * (nLength + 1));
				dwRet = SendRequest_SingleSSL(pRequestBuffer, m_strGateWayIP, usPort, strReponseHttpBody, nLength);
				if (nLength <= 1)
				{
					return dwRet;
				}
			}


		}
		else
		{
			return dwRet;
		}
	}
	else
	{
		//明文
		dwRet = SendRequest_Plain(pRequestBuffer, m_strGateWayIP, usPort, NULL, nLength);
		if (dwRet == AUTH_CODE_SUCCESS && nLength > 1)
		{
			strReponseHttpBody = new TCHAR[nLength + 1];
			if (strReponseHttpBody != NULL)
			{
				memset(strReponseHttpBody, 0, sizeof(TCHAR) * (nLength + 1));
				dwRet = SendRequest_Plain(pRequestBuffer, m_strGateWayIP, usPort, strReponseHttpBody, nLength);
				if (nLength <= 1)
				{
					return dwRet;
				}
			}

		}
		else
		{
			return dwRet;
		}
	}


	///////////////////////////////////////////////////
	// 解析服务回应请求到结构体
	///////////////////////////////////////////////////



	//解析XML
	ParseReponseInfo(strReponseHttpBody, m_structReponseInfo);

	if (strReponseHttpBody) {
		printLogChar("----------strReponseHttpBody-----------begin------");
		printLog(strReponseHttpBody);
		printLogChar("----------strReponseHttpBody-----------end------");
	}


	if (strReponseHttpBody != NULL)
	{
		delete[] strReponseHttpBody;
		strReponseHttpBody = NULL;
	}
	if (pRequestBuffer != NULL)
	{
		delete[] pRequestBuffer;
		pRequestBuffer = NULL;
	}

	if (_tcsicmp(m_structReponseInfo.HeadInfo.MessageStatue, _T("true")) == 0)
	{
		dwRet = AUTH_CODE_FAIL;
#ifdef  __USE_showInfo__
		showInfo_open0(0, 0, _T("StartAuth:AUTH_CODE_FAIL 1"));
#endif
		return dwRet;
	}
	vector<SAuthResult>::iterator iter;
	for (iter = m_structReponseInfo.Body.AuthResults.begin(); iter != m_structReponseInfo.Body.AuthResults.end(); ++iter)
	{
		if (_tcsicmp((*iter).AuthStatue, _T("false")) == 0)
		{
			dwRet = AUTH_CODE_FAIL;
#ifdef  __USE_showInfo__
			showInfo_open0(0, 0, _T("StartAuth:AUTH_CODE_FAIL 2"));
#endif
			return dwRet;
		}
	}

	if (NULL != m_structReponseInfo.Body.AccessControl && _tcsicmp(m_structReponseInfo.Body.AccessControl, _T("Deny")) == 0)
	{
		dwRet = AUTH_CODE_DENY;
#ifdef  __USE_showInfo__
		showInfo_open0(0, 0, _T("StartAuth:AUTH_CODE_DENY"));
#endif
		return dwRet;
	}

#ifdef  __USE_showInfo__

	TCHAR buf[1024] = { 0 };
	_stprintf_s(buf, _T("StartAuth:dwRet=%d"), dwRet);
	showInfo_open0(0, 0, buf);
#endif

	return dwRet;
}

DWORD CServerAuth::SendRequest_Plain(LPCTSTR pszReqInfo, LPCTSTR pszGateWayIP, unsigned short usGatePort, PTCHAR strReponseHttpBody, DWORD& nLength)
{
	// 	static PTCHAR pReponseBody = NULL;
	// 	static DWORD dwLen = 0;
	DWORD dwRet = AUTH_CODE_SUCCESS;

	if (strReponseHttpBody != NULL && m_pReponseBody != NULL)
	{
		_tcscpy_s(strReponseHttpBody, nLength, m_pReponseBody);
		delete[] m_pReponseBody;
		m_pReponseBody = NULL;
		nLength = m_dwLen;
		m_dwLen = 0;
		return dwRet;
	}


	// 准备请求对象
	CoInitialize(NULL);
	IXMLHttpRequest* spHttp = NULL;

	HRESULT hr = CoCreateInstance(__uuidof(XMLHTTPRequest), NULL, CLSCTX_INPROC_SERVER, __uuidof(IXMLHttpRequest), (void**)&spHttp);
	if (FAILED(hr) || !spHttp)
	{
		dwRet = AUTH_CODE_XML_INIT_FAIL;
		return dwRet;
	}
	TCHAR strURL[MAX_PATH] = { 0 };
	_variant_t varp(false);
	_variant_t vusername(_T(""));
	_variant_t vpassword(_T(""));
	BSTR bstrResponse = NULL;

	_stprintf_s(strURL, _T("http://%s:%d/MessageService"), pszGateWayIP, usGatePort);
	spHttp->open(_bstr_t("POST"), _bstr_t(strURL), varp, vusername, vpassword);
	spHttp->setRequestHeader(_bstr_t("Connection"), _bstr_t("close"));
	spHttp->send(_variant_t(_bstr_t(pszReqInfo)));
	spHttp->get_responseText(&bstrResponse);
	if (NULL == bstrResponse)
	{
		dwRet = AUTH_CODE_RECV_INFO_FAIL;
		return dwRet;
	}


	LPTSTR tempReponseHttpBody = (LPTSTR)_bstr_t(bstrResponse);
	DWORD tempLen = _tcslen(tempReponseHttpBody);
	if (m_pReponseBody)
	{
		delete[] m_pReponseBody;
		m_pReponseBody = NULL;
	}
	m_pReponseBody = new TCHAR[tempLen + 1];
	if (m_pReponseBody != NULL)
	{
		memset(m_pReponseBody, 0, sizeof(TCHAR) * tempLen + 1);
		_tcscpy_s(m_pReponseBody, tempLen + 1, tempReponseHttpBody);
		nLength = tempLen + 1;
		m_dwLen = nLength;
	}

#ifdef  __USE_showInfo__
	TCHAR buf[1024] = { 0 };
	_stprintf_s(buf, _T("SendRequest_Plain:dwRet=%d,nLength=%d"), dwRet, nLength);
	showInfo_open0(0, 0, buf);
#endif

	return dwRet;
}

DWORD CServerAuth::SendRequest_SingleSSL(LPCTSTR pszReqInfo, LPCTSTR pszGateWayIP, unsigned short usGatePort, PTCHAR strReponseHttpBody, DWORD& nLength)
{
	SSL_CTX* sslCtx = NULL;
	SSL* ssl = NULL;
	DWORD dwError = AUTH_CODE_SUCCESS, nLen = 0;


	if (strReponseHttpBody != NULL && m_pReponseBody != NULL)
	{
		//第二次调用

		_tcscpy(strReponseHttpBody, m_pReponseBody);
		delete[] m_pReponseBody;
		m_pReponseBody = NULL;
		nLength = m_dwLen;
		m_dwLen = 0;
		return dwError;
	}


	if (pszReqInfo == NULL)
	{
		dwError = AUTH_CODE_FAIL;
		return dwError;
	}

	SOCKET socketConn = (int)::socket(AF_INET, SOCK_STREAM, 0);
	if (socketConn == INVALID_SOCKET)
	{
		dwError = AUTH_CODE_SOCKET_FAIL;
		return dwError;
	}
	sockaddr_in connServerAddr;
	connServerAddr.sin_family = AF_INET;
	connServerAddr.sin_port = htons(usGatePort);
	connServerAddr.sin_addr.s_addr = inet_addr(_bstr_t(pszGateWayIP));
	// 开始连接应用服务器
	int error = ::connect(socketConn, (struct sockaddr*)&connServerAddr, sizeof(struct sockaddr));
	if (error == SOCKET_ERROR)
	{
		closesocket(socketConn);
		dwError = AUTH_CODE_CONNECT_FAIL;
		return dwError;
	}

	do
	{
		//初始化OpenSSL库
		::SSL_library_init();

		// 加载错误信息
		::SSL_load_error_strings();

		if (sslCtx == NULL)
		{
			sslCtx = SSL_CTX_new(TLSv1_client_method());//TLSv1_client_method//SSLv3_client_method
			if (sslCtx == NULL)
			{
				//dwError = ::ERR_get_error();
				dwError = AUTH_CODE_SSL_CONTEXT_FAIL;
				break;
			}
		}

		if (ssl == NULL)
		{
			ssl = ::SSL_new(sslCtx);
			if (ssl == NULL)
			{
				//dwError = ::ERR_get_error();
				dwError = AUTH_CODE_SSL_OBJECT_FAIL;
				break;
			}
		}

		if (::SSL_set_fd(ssl, (int)socketConn) == 0)
		{

			//dwError = ::ERR_get_error();
			dwError = AUTH_CODE_SSL_FD_FAIL;
			break;
		}

		// 连接服务器
		if (::SSL_connect(ssl) <= 0)
		{
			//dwError = ::ERR_get_error();
			dwError = AUTH_CODE_SSL_CONNECT_FAIL;
			break;
		}

		//先将报文部分进行转码
		string sRequestBody = "";
		UnicodeToUTF8(pszReqInfo, sRequestBody);

		string sGatewayIP = "";
		UnicodeToUTF8(pszGateWayIP, sGatewayIP);

		//生成Http报文协议格式
		string sRequestInfo = "";
		BuildHttpInfo(sGatewayIP.c_str(), usGatePort, sRequestBody.c_str(), sRequestInfo);

		int totalSend = 0;
		int requestLen = (int)sRequestInfo.length();
		while (totalSend < requestLen)
		{
			int send = ::SSL_write(ssl, sRequestInfo.c_str() + totalSend, requestLen - totalSend);
			if (send == -1)
			{
				break;
			}
			totalSend += send;
		}

		// 接收认证原文响应结果
		char charBuffer[MAX_DATA_LENGTH + 1] = { 0 };

		//		TCHAR strReponseHttp[MAX_DATA_LENGTH + 1] = {0};

		TCHAR* pszReponseHttp = NULL;
		TCHAR* pszReponseHttpOld = NULL;
		int     nRecvLen = 1;

		while (1)
		{
			memset(charBuffer, 0, MAX_DATA_LENGTH + 1);
			int n = ::SSL_read(ssl, charBuffer, MAX_DATA_LENGTH);

			if (n == 0)
			{
				break;
			}

			nRecvLen = nRecvLen + n;
			if (pszReponseHttpOld)
			{
				delete[] pszReponseHttpOld;
			}
			pszReponseHttpOld = new TCHAR[nRecvLen];
			memset(pszReponseHttpOld, 0, nRecvLen);
			if (pszReponseHttp)
			{
				_tcscat(pszReponseHttpOld, pszReponseHttp);
			}

			wstring wstrHttpBuffer;
			UTF8ToUnicode(charBuffer, wstrHttpBuffer);
			_tcscat(pszReponseHttpOld, wstrHttpBuffer.c_str());
			//_tcscat(pszReponseHttpOld, (LPCTSTR)_bstr_t(charBuffer));

			if (pszReponseHttp)
			{
				delete[] pszReponseHttp;
				pszReponseHttp = NULL;
			}
			pszReponseHttp = new TCHAR[nRecvLen];
			memset(pszReponseHttp, 0, nRecvLen);
			_tcscat(pszReponseHttp, pszReponseHttpOld);
		}


		//_tcscpy(strReponseHttp, (LPCTSTR)_bstr_t(charBuffer));

		if (GetHttpReponseStatus(pszReponseHttp) == 0)
		{
			//获取Http Body长度信息
			string strLength = GetHeaderValue((LPCSTR)_bstr_t(pszReponseHttp), "Content-Length");
			int nBodySize = atoi(strLength.c_str());

			if (nBodySize != 0)
			{
				DWORD tempLen = _tcslen(pszReponseHttp);

				DWORD tempLen1 = tempLen - nBodySize;
				TCHAR* pFind = _tcsstr(pszReponseHttp, _T("\r\n\r\n"));
				if (NULL != pFind)
					tempLen1 = pFind - pszReponseHttp + _tcslen(_T("\r\n\r\n"));
				if (m_pReponseBody)
				{
					delete[] m_pReponseBody;
					m_pReponseBody = NULL;
				}
				m_pReponseBody = new TCHAR[nBodySize + 1];
				if (m_pReponseBody != NULL)
				{
					memset(m_pReponseBody, 0, nBodySize + 1);
					_tcscpy(m_pReponseBody, pszReponseHttp + tempLen1);
					nLength = _tcslen(m_pReponseBody);
					m_dwLen = nLength;
				}
			}
		}

		if (pszReponseHttp)
		{
			delete[] pszReponseHttp;
			pszReponseHttp = NULL;
		}
		if (pszReponseHttpOld)
		{
			delete[] pszReponseHttpOld;
			pszReponseHttpOld = NULL;
		}
	} while (FALSE);



	if (NULL != ssl)
	{
		::SSL_shutdown(ssl);
		::SSL_free(ssl);
		ssl = NULL;
	}

	if (NULL != sslCtx)
	{
		::SSL_CTX_free(sslCtx);
		sslCtx = NULL;
	}

	if (socketConn != INVALID_SOCKET)
	{
		closesocket(socketConn);
		socketConn = INVALID_SOCKET;
	}

	return dwError;
}

DWORD CServerAuth::GetHttpReponseStatus(PTCHAR strHttpInfo)
{
	int iLineSize = 0;
	TCHAR pszBuffer[MAX_DATA_LENGTH] = { 0 };
	PTCHAR ptemp = _tcsstr(strHttpInfo, _T("\r\n"));
	iLineSize = ptemp - strHttpInfo + 1;
	memcpy(pszBuffer, strHttpInfo, iLineSize * sizeof(TCHAR));
	//CString sFirstLine = strHttpInfo.Mid(0, iLineSize);
	if (_tcsstr(strHttpInfo, _T("200")) != NULL)
	{
		return 0;
	}
	return -1;
}


string CServerAuth::GetHeaderValue(const string& strHttpInfo, LPCSTR pszHeadName)
{
	std::string strResult = "";
	LPCSTR pHeader = strHttpInfo.c_str();
	LPCSTR pToken = NULL;
	LPCSTR pLineEnd = NULL;
	while (*pHeader != '\0')
	{
		pToken = StrStrIA(pHeader, pszHeadName);
		if (pToken != NULL)
		{
			pToken += strlen(pszHeadName);

			if (memcmp(pToken, HTTP_LINE_END, HTTP_LINE_END_LEN) == 0)
			{
				pHeader = pToken + HTTP_LINE_END_LEN;
				continue;
			}

			while (pToken[0] == 0x20 || pToken[0] == ':')
			{
				pToken++;
			}

			if (memcmp(pToken, HTTP_LINE_END, HTTP_LINE_END_LEN) == 0)
			{
				pHeader = pToken + HTTP_LINE_END_LEN;
				continue;
			}

			pLineEnd = StrStrIA(pToken, HTTP_LINE_END);
			if (pLineEnd != NULL)
			{
				int ilen = (int)(pLineEnd - pToken);
				char* pszValue = NULL;

				try
				{
					pszValue = new char[ilen + 1];
				}
				catch (const std::bad_alloc&)
				{
					break;
				}

				memset(pszValue, 0, ilen + 1);
				memcpy(pszValue, pToken, ilen);

				strResult = pszValue;
				delete[] pszValue;
				break;
			}
			else
			{
				break;
			}
		}
		else
		{
			break;
		}
	}

	return strResult;
}

DWORD CServerAuth::BuildHttpInfo(LPCSTR pszGateWayIP, unsigned short usGatePort, const string& sRequestBody, string& sRequest)
{
	string sTemp = "POST /MessageService HTTP/1.1\r\n";
	sRequest.append(sTemp.c_str());

	sTemp = "Accept: */*\r\n";
	sRequest.append(sTemp);

	sTemp = "Accept-Language: zh-cn\r\n";
	sRequest.append(sTemp);

	char szTemp[256] = { 0 };
	sprintf_s(szTemp, "Host: %s:%d\r\n", pszGateWayIP, usGatePort);
	sRequest.append(szTemp);

	if (sRequestBody.length() != 0)
	{
		sprintf_s(szTemp, "Content-Length: %d\r\n", strlen(sRequestBody.c_str()));
		sRequest.append(szTemp);

		sTemp = "Connection: Close\r\n\r\n";
		sRequest.append(sTemp.c_str());

		sRequest.append(sRequestBody.c_str());
		sRequest.append("\r\n");
	}

	return 0;
}

// 生成认证请求报文，第一次调用lpszRequest为空，返回数据长度。第二次调用获取数据
DWORD CServerAuth::BuildRequestXML(LPCTSTR pszReqInfo, LPCTSTR pszAppFlag, LPCTSTR lpszClientIP, LPTSTR lpszRequest)
{
	DWORD nLen = 0, nLength = 0, strLength = MAX_DATA_LENGTH;
	TCHAR tcTempBuffer[MAX_DATA_LENGTH] = { 0 };
	//static PTCHAR csRequest = NULL;
	//static DWORD nAuthLength = 0;
	PTCHAR tempRequest = NULL;


	if (lpszRequest != NULL)
	{
		//第二次调用
		if (m_pszRequest != NULL && m_nAuthLength > 0)
		{
			_tcscpy(lpszRequest, m_pszRequest);
			delete[] m_pszRequest;
			m_pszRequest = NULL;
			nLen = m_nAuthLength;
			m_nAuthLength = 0;
		}
		return nLen;
	}


	if (pszReqInfo == NULL)
	{
		return nLen;
	}


	//动态分配内存
	nLength = 0;
	m_pszRequest = new TCHAR[MAX_DATA_LENGTH];
	memset(m_pszRequest, 0, sizeof(TCHAR) * MAX_DATA_LENGTH);

	//随机数 版本
	if (m_nXMLVer == 10)
	{
		_tcscpy(m_pszRequest, _T("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n<message>\r\n<head>\r\n<version>1.0</version>\r\n<serviceType>AuthenService</serviceType>\r\n</head>\r\n<body>\r\n"));
	}
	else
	{
		_tcscpy(m_pszRequest, _T("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n<message>\r\n<head>\r\n<version>1.1</version>\r\n<serviceType>AuthenService</serviceType>\r\n</head>\r\n<body>\r\n"));
	}

	nLength = _tcslen(m_pszRequest);
	m_nAuthLength = nLength;

	_stprintf_s(tcTempBuffer, _T("<clientInfo><clientIP>%s</clientIP></clientInfo>\r\n"), lpszClientIP);
	nLength += _tcslen(tcTempBuffer);
	if (nLength >= strLength)
	{
		//内存不足
		if (m_pszRequest != NULL)
		{

			strLength = nLength * 2;
			tempRequest = new TCHAR[strLength];
			if (tempRequest == NULL)
			{
				delete[] m_pszRequest;
				return nLen;
			}

			_tcscpy(tempRequest, m_pszRequest);
			delete[] m_pszRequest;
			m_pszRequest = tempRequest;
			tempRequest = NULL;
		}
	}

	_tcscpy(m_pszRequest + m_nAuthLength, tcTempBuffer);
	m_nAuthLength = nLength;

	memset(tcTempBuffer, 0, MAX_DATA_LENGTH);
	_stprintf_s(tcTempBuffer, _T("<appId>%s</appId>\r\n"), pszAppFlag);
	nLength += _tcslen(tcTempBuffer);
	if (nLength >= strLength)
	{
		//内存不足
		if (m_pszRequest != NULL)
		{
			strLength = nLength * 2;
			tempRequest = new TCHAR[strLength];
			if (tempRequest == NULL)
			{
				delete[] m_pszRequest;
				return nLen;
			}

			_tcscpy(tempRequest, m_pszRequest);
			delete[] m_pszRequest;
			m_pszRequest = tempRequest;
			tempRequest = NULL;
		}
	}

	_tcscpy(m_pszRequest + m_nAuthLength, tcTempBuffer);
	m_nAuthLength = nLength;

	memset(tcTempBuffer, 0, MAX_DATA_LENGTH);
	_stprintf_s(tcTempBuffer, _T("<authen>%s</authen>\r\n"), pszReqInfo);
	nLength += _tcslen(tcTempBuffer);
	if (nLength >= strLength)
	{
		//内存不足
		if (m_pszRequest != NULL)
		{
			strLength = nLength * 2;
			tempRequest = new TCHAR[strLength];
			if (tempRequest == NULL)
			{
				delete[] m_pszRequest;
				return nLen;
			}

			_tcscpy(tempRequest, m_pszRequest);
			delete[] m_pszRequest;
			m_pszRequest = tempRequest;
			tempRequest = NULL;
		}
	}

	_tcscpy(m_pszRequest + m_nAuthLength, tcTempBuffer);
	m_nAuthLength = nLength;

	nLength += _tcslen(_T("<accessControl>true</accessControl>\r\n<attributes attributeType=\"all\">\r\n"));
	if (nLength >= strLength)
	{
		//内存不足
		if (m_pszRequest != NULL)
		{
			strLength = nLength * 2;
			tempRequest = new TCHAR[strLength];
			if (tempRequest == NULL)
			{
				delete[] m_pszRequest;
				return nLen;
			}

			_tcscpy(tempRequest, m_pszRequest);
			delete[] m_pszRequest;
			m_pszRequest = tempRequest;
			tempRequest = NULL;
		}
	}
	_tcscpy(m_pszRequest + m_nAuthLength, _T("<accessControl>true</accessControl>\r\n<attributes attributeType=\"all\">\r\n"));
	m_nAuthLength = nLength;


	////证书认证时注释掉
	//csRequest.Format(_T("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n")
	//    _T("<message>\r\n")
	//    _T("<head>\r\n")
	//    _T("<version>1.0</version>\r\n")
	//    _T("<serviceType>AuthenService</serviceType>\r\n")
	//    _T("</head>\r\n")
	//    _T("<body>\r\n")
	//    _T("<clientInfo><clientIP>%s</clientIP></clientInfo>\r\n")
	//    _T("<appId>%s</appId>\r\n")
	//    _T("<authen>%s</authen>\r\n")
	//    _T("<accessControl>false</accessControl>\r\n")
	//    _T("<attributes attributeType=\"all\">\r\n"),
	//    lpszClientIP, pszAppFlag, pszReqInfo);

	if (_tcsstr(pszReqInfo, _T("<authCredential authMode=\"cert\">")) != NULL)
	{
		nLength += _tcslen(_T("<attr name=\"X509Certificate.NotBefore\" namespace=\"http://www.jit.com.cn/cinas/ias/ns/saml/saml11/X.509\"></attr>\r\n<attr name=\"X509Certificate.NotAfter\" namespace=\"http://www.jit.com.cn/cinas/ias/ns/saml/saml11/X.509\"></attr>\r\n<attr name=\"X509Certificate.SubjectDN\" namespace=\"http://www.jit.com.cn/cinas/ias/ns/saml/saml11/X.509\"></attr>\r\n<attr name=\"X509Certificate.SerialNumber\" namespace=\"http://www.jit.com.cn/cinas/ias/ns/saml/saml11/X.509\"></attr>\r\n<attr name=\"X509Certificate.IssuerDN\" namespace=\"http://www.jit.com.cn/cinas/ias/ns/saml/saml11/X.509\"></attr>\r\n"));
		if (nLength >= strLength)
		{
			//内存不足
			if (m_pszRequest != NULL)
			{
				strLength = nLength * 2;
				tempRequest = new TCHAR[strLength];
				if (tempRequest == NULL)
				{
					delete[] m_pszRequest;
					return nLen;
				}

				_tcscpy(tempRequest, m_pszRequest);
				delete[] m_pszRequest;
				m_pszRequest = tempRequest;
				tempRequest = NULL;
			}
		}
		_tcscpy(m_pszRequest + m_nAuthLength, _T("<attr name=\"X509Certificate.NotBefore\" namespace=\"http://www.jit.com.cn/cinas/ias/ns/saml/saml11/X.509\"></attr>\r\n<attr name=\"X509Certificate.NotAfter\" namespace=\"http://www.jit.com.cn/cinas/ias/ns/saml/saml11/X.509\"></attr>\r\n<attr name=\"X509Certificate.SubjectDN\" namespace=\"http://www.jit.com.cn/cinas/ias/ns/saml/saml11/X.509\"></attr>\r\n<attr name=\"X509Certificate.SerialNumber\" namespace=\"http://www.jit.com.cn/cinas/ias/ns/saml/saml11/X.509\"></attr>\r\n<attr name=\"X509Certificate.IssuerDN\" namespace=\"http://www.jit.com.cn/cinas/ias/ns/saml/saml11/X.509\"></attr>\r\n"));
		m_nAuthLength = nLength;

		/*CString csCertInfo(_T("<attr name=\"X509Certificate.NotBefore\" namespace=\"http://www.jit.com.cn/cinas/ias/ns/saml/saml11/X.509\"></attr>\r\n")
			_T("<attr name=\"X509Certificate.NotAfter\" namespace=\"http://www.jit.com.cn/cinas/ias/ns/saml/saml11/X.509\"></attr>\r\n")
			_T("<attr name=\"X509Certificate.SubjectDN\" namespace=\"http://www.jit.com.cn/cinas/ias/ns/saml/saml11/X.509\"></attr>\r\n")
			_T("<attr name=\"X509Certificate.SerialNumber\" namespace=\"http://www.jit.com.cn/cinas/ias/ns/saml/saml11/X.509\"></attr>\r\n")
			_T("<attr name=\"X509Certificate.IssuerDN\" namespace=\"http://www.jit.com.cn/cinas/ias/ns/saml/saml11/X.509\"></attr>\r\n"));*/


	}
	if (_tcsstr(pszReqInfo, _T("<authCredential authMode=\"password\">")) != NULL)
	{

		nLength += _tcslen(_T("<attr name=\"UMS.UserID\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n<attr name=\"UMS.Username\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n<attr name=\"UMS.LogonName\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n"));
		if (nLength >= strLength)
		{
			//内存不足
			if (m_pszRequest != NULL)
			{
				strLength = nLength * 2;
				tempRequest = new TCHAR[strLength];
				if (tempRequest == NULL)
				{
					delete[] m_pszRequest;
					return nLen;
				}

				_tcscpy(tempRequest, m_pszRequest);
				delete[] m_pszRequest;
				m_pszRequest = tempRequest;
				tempRequest = NULL;
			}
		}
		_tcscpy(m_pszRequest + m_nAuthLength, _T("<attr name=\"UMS.UserID\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n<attr name=\"UMS.Username\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n<attr name=\"UMS.LogonName\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n"));
		m_nAuthLength = nLength;


		/*CString csPasswordInfo(_T("<attr name=\"UMS.UserID\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n")
			_T("<attr name=\"UMS.Username\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n")
			_T("<attr name=\"UMS.LogonName\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n"));*/


	}


	/////////////////
	nLength += _tcslen(_T(R"(
<attr name="privilege" namespace="http://www.jit.com.cn/pmi/pms/ns/privilege"></attr>
<attr name="role" namespace="http://www.jit.com.cn/pmi/pms/ns/role"></attr>
<attr name="性别" namespace="http://www.jit.com.cn/ums/ns/user"></attr>
<attr name="职务" namespace="http://www.jit.com.cn/ums/ns/user"></attr>
<attr name="身份证" namespace="http://www.jit.com.cn/ums/ns/user"></attr>
<attr name="部门" namespace="http://www.jit.com.cn/ums/ns/user"></attr>
<attr name="机构字典" namespace="http://www.jit.com.cn/ums/ns/user"></attr>
</attributes>
</body>
</message>
)"));



	//nLength += _tcslen(_T("<attr name=\"privilege\" namespace=\"http://www.jit.com.cn/pmi/pms/ns/privilege\"></attr>\r\n<attr name=\"role\" namespace=\"http://www.jit.com.cn/pmi/pms/ns/role\"></attr>\r\n<attr name=\"性别\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n<attr name=\"职务\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n<attr name=\"身份证\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n<attr name=\"部门\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n<attr name=\"机构字典\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n</attributes>\r\n</body>\r\n</message>"));
	//nLength += _tcslen(_T("<attr name=\"privilege\" namespace=\"http://www.jit.com.cn/pmi/pms/ns/privilege\"></attr>\r\n<attr name=\"role\" namespace=\"http://www.jit.com.cn/pmi/pms/ns/role\"></attr>\r\n<attr name=\"性别\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n<attr name=\"职务\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n<attr name=\"身份证\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n<attr name=\"部门\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n<attr name=\"机构字典\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n</attributes>\r\n</body>\r\n</message>"));

	//
	if (nLength >= strLength)
	{
		//内存不足
		if (m_pszRequest != NULL)
		{
			strLength = nLength * 2;
			tempRequest = new TCHAR[strLength];
			if (tempRequest == NULL)
			{
				delete[] m_pszRequest;
				return nLen;
			}

			_tcscpy(tempRequest, m_pszRequest);
			delete[] m_pszRequest;
			m_pszRequest = tempRequest;
			tempRequest = NULL;
		}
	}
	
	//_tcscpy(m_pszRequest + m_nAuthLength, _T("<attr name=\"privilege\" namespace=\"http://www.jit.com.cn/pmi/pms/ns/privilege\"></attr>\r\n<attr name=\"role\" namespace=\"http://www.jit.com.cn/pmi/pms/ns/role\"></attr>\r\n<attr name=\"性别\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n<attr name=\"职务\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n<attr name=\"身份证\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n<attr name=\"部门\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n<attr name=\"机构字典\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n</attributes>\r\n</body>\r\n</message>"));
	// 方法1：使用 _T 和原始字符串
	_tcscpy(m_pszRequest + m_nAuthLength,
		_T(R"(<attr name="privilege" namespace="http://www.jit.com.cn/pmi/pms/ns/privilege"></attr>
<attr name="role" namespace="http://www.jit.com.cn/pmi/pms/ns/role"></attr>
<attr name="性别" namespace="http://www.jit.com.cn/ums/ns/user"></attr>
<attr name="职务" namespace="http://www.jit.com.cn/ums/ns/user"></attr>
<attr name="身份证" namespace="http://www.jit.com.cn/ums/ns/user"></attr>
<attr name="部门" namespace="http://www.jit.com.cn/ums/ns/user"></attr>
<attr name="机构字典" namespace="http://www.jit.com.cn/ums/ns/user"></attr>
</attributes>
</body>
</message>)")
);

	//
	m_nAuthLength = nLength;


	/*csRequest += _T("<attr name=\"privilege\" namespace=\"http://www.jit.com.cn/pmi/pms/ns/privilege\"></attr>\r\n")
		_T("<attr name=\"role\" namespace=\"http://www.jit.com.cn/pmi/pms/ns/role\"></attr>\r\n")
		_T("<attr name=\"性别\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n")
		_T("<attr name=\"职务\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n")
		_T("<attr name=\"身份证\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n")
		_T("<attr name=\"部门\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n")
		_T("<attr name=\"机构字典\" namespace=\"http://www.jit.com.cn/ums/ns/user\"></attr>\r\n")
		_T("</attributes>\r\n")
		_T("</body>\r\n")
		_T("</message>");*/

	m_pszRequest[m_nAuthLength] = _T('\0');
	m_nAuthLength += 1;
	nLen = m_nAuthLength;


	return nLen;
}

// 解析回应信息
void CServerAuth::ParseReponseInfo(LPCTSTR pszPolicym, SReponseInfo& reponseInfo)
{
	CoInitialize(NULL);

	IXMLDOMElement* spRoot = NULL;

	//CComPtr<IXMLDOMDocument> spDoc;
	IXMLDOMDocument* spDoc = NULL;

	HRESULT hr = CoCreateInstance(__uuidof(DOMDocument), NULL, CLSCTX_INPROC_SERVER, __uuidof(IXMLDOMDocument), (void**)&spDoc);
	//spDoc.CoCreateInstance(__uuidof(DOMDocument));
	if (FAILED(hr) || !spDoc)
	{
		goto End;
		//return;
	}

	// 加载服务器返回的结果
	VARIANT_BOOL vbSuccess = VARIANT_FALSE;
	if (FAILED(spDoc->loadXML(_bstr_t(pszPolicym), &vbSuccess)) || (vbSuccess == VARIANT_FALSE))
	{
		goto End;
		//return;
	}

	// 获得根节点
	//CComPtr<IXMLDOMElement> spRoot;

	if (FAILED(spDoc->get_documentElement(&spRoot)) || !spRoot)
	{
		goto End;
		//return;
	}

	//从根节点开始解析
	if (!Parse_Root(spRoot, reponseInfo))
	{
		goto End;
		//return;
	}


End:
	if (spRoot != NULL)
	{
		spRoot->Release();
	}

	if (spDoc != NULL)
	{
		spDoc->Release();
	}

	CoUninitialize();

	return;
}

bool CServerAuth::Parse_Root(IXMLDOMNode* node, SReponseInfo& reponseInfo)
{
	bool bflag = true;


	{
		BEGIN_TRAVEL_CHILDREN(node, childNode, childNodeName, bflag);

		if (!_tcsicmp(childNodeName, _T("head")))
		{
			if (!Parse_Reponse_Head(childNode, reponseInfo))
			{
				bflag = false;
				goto End;
				//return false;
			}
		}
		else if (!_tcsicmp(childNodeName, _T("body")))
		{
			if (!Parse_Reponse_Body(childNode, reponseInfo))
			{
				bflag = false;
				goto End;
				//return false;
			}
		}

		END_TRAVEL_CHILDREN(childNode);

	}


	return bflag;
}

bool CServerAuth::Parse_Reponse_Head(IXMLDOMNode* node, SReponseInfo& reponseInfo)
{
	bool bflag = true;

	{
		BEGIN_TRAVEL_CHILDREN(node, childNode, childNodeName, bflag);

		if (!_tcsicmp(childNodeName, _T("version")))
		{
			if (!Parse_Reponse_Head_Version(childNode, reponseInfo))
			{
				bflag = false;
				goto End;
				//return false;
			}
		}
		else if (!_tcsicmp(childNodeName, _T("serviceType")))
		{
			if (!Parse_Reponse_Head_ServiceType(childNode, reponseInfo))
			{
				bflag = false;
				goto End;
				//return false;
			}
		}
		else if (!_tcsicmp(childNodeName, _T("messageState")))
		{
			if (!Parse_Reponse_Head_MessageStatue(childNode, reponseInfo))
			{
				bflag = false;
				goto End;
				//return false;
			}
		}
		else if (!_tcsicmp(childNodeName, _T("messageCode")))
		{
			if (!Parse_Reponse_Head_MessageCode(childNode, reponseInfo))
			{
				bflag = false;
				goto End;
				//return false;
			}
		}
		else if (!_tcsicmp(childNodeName, _T("messageDesc")))
		{
			if (!Parse_Reponse_Head_MessageDesc(childNode, reponseInfo))
			{
				bflag = false;
				goto End;
				//return false;
			}
		}


		END_TRAVEL_CHILDREN(childNode);
	}

	return bflag;
}

bool CServerAuth::Parse_Reponse_Head_Version(IXMLDOMNode* node, SReponseInfo& reponseInfo)
{
	_bstr_t bstr;
	DWORD dwLen = 0;
	if (FAILED(node->get_text(bstr.GetAddress())))
	{
		return false;
	}

	dwLen = _tcslen((LPCTSTR)bstr);
	if (dwLen > 0)
	{
		if (reponseInfo.HeadInfo.Version != NULL)
		{
			delete[] reponseInfo.HeadInfo.Version;
			reponseInfo.HeadInfo.Version = NULL;
		}

		reponseInfo.HeadInfo.Version = new TCHAR[dwLen + 1];
		if (reponseInfo.HeadInfo.Version != NULL)
		{
			memset(reponseInfo.HeadInfo.Version, 0, sizeof(TCHAR) * (dwLen + 1));
			_tcscpy(reponseInfo.HeadInfo.Version, (LPCTSTR)bstr);
			reponseInfo.HeadInfo.Version[dwLen] = _T('\0');
		}
	}

	return true;
}

bool CServerAuth::Parse_Reponse_Head_ServiceType(IXMLDOMNode* node, SReponseInfo& reponseInfo)
{
	_bstr_t bstr;
	DWORD dwLen = 0;
	if (FAILED(node->get_text(bstr.GetAddress())))
	{
		return false;
	}

	dwLen = _tcslen((LPCTSTR)bstr);
	if (dwLen > 0)
	{
		if (reponseInfo.HeadInfo.ServiceType != NULL)
		{
			delete[] reponseInfo.HeadInfo.ServiceType;
			reponseInfo.HeadInfo.ServiceType = NULL;
		}

		reponseInfo.HeadInfo.ServiceType = new TCHAR[dwLen + 1];
		if (reponseInfo.HeadInfo.ServiceType != NULL)
		{
			memset(reponseInfo.HeadInfo.ServiceType, 0, sizeof(TCHAR) * (dwLen + 1));
			_tcscpy(reponseInfo.HeadInfo.ServiceType, (LPCTSTR)bstr);
			reponseInfo.HeadInfo.ServiceType[dwLen] = _T('\0');
		}
	}


	return true;
}

bool CServerAuth::Parse_Reponse_Head_MessageStatue(IXMLDOMNode* node, SReponseInfo& reponseInfo)
{
	_bstr_t bstr;
	DWORD dwLen = 0;
	if (FAILED(node->get_text(bstr.GetAddress())))
	{
		return false;
	}

	dwLen = _tcslen((LPCTSTR)bstr);
	if (dwLen > 0)
	{
		if (reponseInfo.HeadInfo.MessageStatue != NULL)
		{
			delete[] reponseInfo.HeadInfo.MessageStatue;
			reponseInfo.HeadInfo.MessageStatue = NULL;
		}

		reponseInfo.HeadInfo.MessageStatue = new TCHAR[dwLen + 1];
		if (reponseInfo.HeadInfo.MessageStatue != NULL)
		{
			memset(reponseInfo.HeadInfo.MessageStatue, 0, sizeof(TCHAR) * (dwLen + 1));
			_tcscpy(reponseInfo.HeadInfo.MessageStatue, (LPCTSTR)bstr);
			reponseInfo.HeadInfo.MessageStatue[dwLen] = _T('\0');
		}
	}


	return true;
}

bool CServerAuth::Parse_Reponse_Head_MessageCode(IXMLDOMNode* node, SReponseInfo& reponseInfo)
{
	_bstr_t bstr;
	DWORD dwLen = 0;
	if (FAILED(node->get_text(bstr.GetAddress())))
	{
		return false;
	}

	dwLen = _tcslen((LPCTSTR)bstr);
	if (dwLen > 0)
	{
		if (reponseInfo.HeadInfo.MessageCode != NULL)
		{
			delete[] reponseInfo.HeadInfo.MessageCode;
			reponseInfo.HeadInfo.MessageCode = NULL;
		}

		reponseInfo.HeadInfo.MessageCode = new TCHAR[dwLen + 1];
		if (reponseInfo.HeadInfo.MessageCode != NULL)
		{
			memset(reponseInfo.HeadInfo.MessageCode, 0, sizeof(TCHAR) * (dwLen + 1));
			_tcscpy(reponseInfo.HeadInfo.MessageCode, (LPCTSTR)bstr);
			reponseInfo.HeadInfo.MessageCode[dwLen] = _T('\0');
		}
	}


	return true;
}

bool CServerAuth::Parse_Reponse_Head_MessageDesc(IXMLDOMNode* node, SReponseInfo& reponseInfo)
{
	_bstr_t bstr;
	DWORD dwLen = 0;
	if (FAILED(node->get_text(bstr.GetAddress())))
	{
		return false;
	}

	dwLen = _tcslen((LPCTSTR)bstr);
	if (dwLen > 0)
	{
		if (reponseInfo.HeadInfo.MessageDesc != NULL)
		{
			delete[] reponseInfo.HeadInfo.MessageDesc;
			reponseInfo.HeadInfo.MessageDesc = NULL;
		}
		reponseInfo.HeadInfo.MessageDesc = new TCHAR[dwLen + 1];
		if (reponseInfo.HeadInfo.MessageDesc != NULL)
		{
			memset(reponseInfo.HeadInfo.MessageDesc, 0, sizeof(TCHAR) * (dwLen + 1));
			_tcscpy(reponseInfo.HeadInfo.MessageDesc, (LPCTSTR)bstr);
			reponseInfo.HeadInfo.MessageDesc[dwLen] = _T('\0');
		}
	}


	return true;
}

bool CServerAuth::Parse_Reponse_Body(IXMLDOMNode* node, SReponseInfo& reponseInfo)
{
	bool bflag = true;
	{
		BEGIN_TRAVEL_CHILDREN(node, childNode, childNodeName, bflag);

		if (!_tcsicmp(childNodeName, _T("authResultSet")))
		{
			if (!Parse_Reponse_Body_AuthResultSet(childNode, reponseInfo))
			{
				bflag = false;
				goto End;
				//return false;
			}
		}
		else if (!_tcsicmp(childNodeName, _T("accessControlResult")))
		{
			if (!Parse_Reponse_Body_ControlResult(childNode, reponseInfo))
			{
				bflag = false;
				goto End;
				//return false;
			}
		}
		else if (!_tcsicmp(childNodeName, _T("attributes")))
		{
			if (!Parse_Reponse_Body_Attributes(childNode, reponseInfo))
			{
				bflag = false;
				goto End;
				//return false;
			}
		}
		else if (!_tcsicmp(childNodeName, _T("original")))
		{
			if (!Parse_Reponse_Body_Original(childNode, reponseInfo))
			{
				bflag = false;
				goto End;
				//return false;
			}
		}


		END_TRAVEL_CHILDREN(childNode);
	}

	return bflag;
}

bool CServerAuth::Parse_Reponse_Body_AuthResultSet(IXMLDOMNode* node, SReponseInfo& reponseInfo)
{
	bool bflag = true;
	{
		BEGIN_TRAVEL_CHILDREN(node, childNode, childNodeName, bflag);

		if (!_tcsicmp(childNodeName, _T("authResult")))
		{
			if (!Parse_Reponse_Body_AuthResultSet_AuthResult(childNode, reponseInfo))
			{
				bflag = false;
				goto End;
				//return false;
			}
		}


		END_TRAVEL_CHILDREN(childNode);
	}

	return bflag;
}

bool CServerAuth::Parse_Reponse_Body_AuthResultSet_AuthResult(IXMLDOMNode* node, SReponseInfo& reponseInfo)
{
	bool bflag = true;
	DWORD dwLen = 0;
	SAuthResult authResultTemp = { 0 };
	{
		BEGIN_TRAVEL_ATTRIBUTES(node, attrName, attrValue, bflag);


		if (!_tcsicmp(attrName, _T("authMode")))
		{
			dwLen = _tcslen((LPCTSTR)_bstr_t(_variant_t(attrValue)));
			if (dwLen > 0)
			{
				if (authResultTemp.AuthMode != NULL)
				{
					delete[] authResultTemp.AuthMode;
					authResultTemp.AuthMode = NULL;
				}
				authResultTemp.AuthMode = new TCHAR[dwLen + 1];
				if (authResultTemp.AuthMode != NULL)
				{
					memset(authResultTemp.AuthMode, 0, sizeof(TCHAR) * (dwLen + 1));
					_tcscpy(authResultTemp.AuthMode, (LPCTSTR)_bstr_t(_variant_t(attrValue)));
					authResultTemp.AuthMode[dwLen] = _T('\0');
				}
			}
			//authResultTemp.AuthMode = (LPCTSTR)_bstr_t(_variant_t(attrValue));
		}
		else if (!_tcsicmp(attrName, _T("success")))
		{
			dwLen = _tcslen((LPCTSTR)_bstr_t(_variant_t(attrValue)));
			if (dwLen > 0)
			{
				if (authResultTemp.AuthStatue != NULL)
				{
					delete[] authResultTemp.AuthStatue;
					authResultTemp.AuthStatue = NULL;
				}
				authResultTemp.AuthStatue = new TCHAR[dwLen + 1];
				if (authResultTemp.AuthStatue != NULL)
				{
					memset(authResultTemp.AuthStatue, 0, sizeof(TCHAR) * (dwLen + 1));
					_tcscpy(authResultTemp.AuthStatue, (LPCTSTR)_bstr_t(_variant_t(attrValue)));
					authResultTemp.AuthStatue[dwLen] = _T('\0');
				}
			}
			//authResultTemp.AuthStatue = (LPCTSTR)_bstr_t(_variant_t(attrValue));
		}

		END_TRAVEL_ATTRIBUTES;
	}

	if (bflag == false)
	{
		return bflag;
	}

	{
		BEGIN_TRAVEL_CHILDREN(node, childNode, childNodeName, bflag);

		if (!_tcsicmp(childNodeName, _T("authMessageCode")))
		{
			if (!Parse_Reponse_Body_AuthResultSet_AuthResult_MessageCode(childNode, authResultTemp))
			{
				bflag = false;
				goto End;
				//return false;
			}
		}
		else if (!_tcsicmp(childNodeName, _T("authMessageDesc")))
		{
			if (!Parse_Reponse_Body_AuthResultSet_AuthResult_MessageDesc(childNode, authResultTemp))
			{
				bflag = false;
				goto End;
				//return false;
			}
		}


		END_TRAVEL_CHILDREN(childNode);
	}

	reponseInfo.Body.AuthResults.push_back(authResultTemp);


	return bflag;
}

bool CServerAuth::Parse_Reponse_Body_AuthResultSet_AuthResult_MessageCode(IXMLDOMNode* node, SAuthResult& reponseInfo)
{
	_bstr_t bstr;
	if (FAILED(node->get_text(bstr.GetAddress())))
	{
		return false;
	}

	DWORD dwLen = _tcslen((LPCTSTR)bstr);
	if (dwLen > 0)
	{
		if (reponseInfo.AuthMsgCode != NULL)
		{
			delete[] reponseInfo.AuthMsgCode;
			reponseInfo.AuthMsgCode = NULL;
		}
		reponseInfo.AuthMsgCode = new TCHAR[dwLen + 1];
		if (reponseInfo.AuthMsgCode != NULL)
		{
			memset(reponseInfo.AuthMsgCode, 0, sizeof(TCHAR) * (dwLen + 1));
			_tcscpy(reponseInfo.AuthMsgCode, (LPCTSTR)bstr);
			reponseInfo.AuthMsgCode[dwLen] = _T('\0');
		}
	}
	//reponseInfo.AuthMsgCode = (LPCTSTR)bstr;

	return true;
}

bool CServerAuth::Parse_Reponse_Body_AuthResultSet_AuthResult_MessageDesc(IXMLDOMNode* node, SAuthResult& reponseInfo)
{
	_bstr_t bstr;
	if (FAILED(node->get_text(bstr.GetAddress())))
	{
		return false;
	}

	DWORD dwLen = _tcslen((LPCTSTR)bstr);
	if (dwLen > 0)
	{
		if (reponseInfo.AuthMsgDesc != NULL)
		{
			delete[] reponseInfo.AuthMsgDesc;
			reponseInfo.AuthMsgDesc = NULL;
		}
		reponseInfo.AuthMsgDesc = new TCHAR[dwLen + 1];
		if (reponseInfo.AuthMsgDesc != NULL)
		{
			memset(reponseInfo.AuthMsgDesc, 0, sizeof(TCHAR) * (dwLen + 1));
			_tcscpy(reponseInfo.AuthMsgDesc, (LPCTSTR)bstr);
			reponseInfo.AuthMsgDesc[dwLen] = _T('\0');
		}
	}
	//reponseInfo.AuthMsgDesc = (LPCTSTR)bstr;

	return true;
}

bool CServerAuth::Parse_Reponse_Body_ControlResult(IXMLDOMNode* node, SReponseInfo& reponseInfo)
{
	_bstr_t bstr;
	if (FAILED(node->get_text(bstr.GetAddress())))
	{
		return false;
	}

	DWORD dwLen = _tcslen((LPCTSTR)bstr);
	if (dwLen > 0)
	{
		if (reponseInfo.Body.AccessControl != NULL)
		{
			delete[] reponseInfo.Body.AccessControl;
			reponseInfo.Body.AccessControl = NULL;
		}
		reponseInfo.Body.AccessControl = new TCHAR[dwLen + 1];
		if (reponseInfo.Body.AccessControl != NULL)
		{
			memset(reponseInfo.Body.AccessControl, 0, sizeof(TCHAR) * (dwLen + 1));
			_tcscpy(reponseInfo.Body.AccessControl, (LPCTSTR)bstr);
			reponseInfo.Body.AccessControl[dwLen] = _T('\0');
		}
	}
	//reponseInfo.Body.AccessControl = (LPCTSTR)bstr;

	return true;
}

bool CServerAuth::Parse_Reponse_Body_Attributes(IXMLDOMNode* node, SReponseInfo& reponseInfo)
{
	bool bflag = true;

	{
		BEGIN_TRAVEL_ATTRIBUTES(node, attrName, attrValue, bflag);

		if (!_tcsicmp(attrName, _T("attributeType")))
		{
			DWORD dwLen = _tcslen((LPCTSTR)_bstr_t(_variant_t(attrValue)));
			if (dwLen > 0)
			{
				if (reponseInfo.Body.AttributesType != NULL)
				{
					delete[] reponseInfo.Body.AttributesType;
					reponseInfo.Body.AttributesType = NULL;
				}
				reponseInfo.Body.AttributesType = new TCHAR[dwLen + 1];
				if (reponseInfo.Body.AttributesType != NULL)
				{
					memset(reponseInfo.Body.AttributesType, 0, sizeof(TCHAR) * (dwLen + 1));
					_tcscpy(reponseInfo.Body.AttributesType, (LPCTSTR)_bstr_t(_variant_t(attrValue)));
					reponseInfo.Body.AttributesType[dwLen] = _T('\0');
				}
			}
			//reponseInfo.Body.AttributesType = (LPCTSTR)_bstr_t(_variant_t(attrValue));
		}

		END_TRAVEL_ATTRIBUTES;
	}

	if (bflag == false)
	{
		return bflag;
	}

	{
		BEGIN_TRAVEL_CHILDREN(node, childNode, childNodeName, bflag);

		SAttributeItem authAttributeTemp = { 0 };
		if (!_tcsicmp(childNodeName, _T("attr")))
		{
			if (!Parse_Reponse_Body_Attributes_Attribute(childNode, authAttributeTemp))
			{
				bflag = false;
				goto End;
				//return false;
			}
		}

		reponseInfo.Body.Attributes.push_back(authAttributeTemp);


		END_TRAVEL_CHILDREN(childNode);
	}

	return bflag;
}

bool CServerAuth::Parse_Reponse_Body_Attributes_Attribute(IXMLDOMNode* node, SAttributeItem& reponseInfo)
{
	bool bflag = true;
	DWORD dwLen = 0;
	{
		BEGIN_TRAVEL_ATTRIBUTES(node, attrName, attrValue, bflag);

		if (!_tcsicmp(attrName, _T("name")))
		{
			dwLen = _tcslen((LPCTSTR)_bstr_t(_variant_t(attrValue)));
			if (dwLen > 0)
			{
				if (reponseInfo.AttributeName != NULL)
				{
					delete[] reponseInfo.AttributeName;
					reponseInfo.AttributeName = NULL;
				}
				reponseInfo.AttributeName = new TCHAR[dwLen + 1];
				if (reponseInfo.AttributeName != NULL)
				{
					memset(reponseInfo.AttributeName, 0, sizeof(TCHAR) * (dwLen + 1));
					_tcscpy(reponseInfo.AttributeName, (LPCTSTR)_bstr_t(_variant_t(attrValue)));
					reponseInfo.AttributeName[dwLen] = _T('\0');
				}
			}
			//reponseInfo.AttributeName = (LPCTSTR)_bstr_t(_variant_t(attrValue));
		}
		else if (!_tcsicmp(attrName, _T("parentName")))
		{
			dwLen = _tcslen((LPCTSTR)_bstr_t(_variant_t(attrValue)));
			if (dwLen > 0)
			{
				if (reponseInfo.AttributeParentName != NULL)
				{
					delete[] reponseInfo.AttributeParentName;
					reponseInfo.AttributeParentName = NULL;
				}
				reponseInfo.AttributeParentName = new TCHAR[dwLen + 1];
				if (reponseInfo.AttributeParentName != NULL)
				{
					memset(reponseInfo.AttributeParentName, 0, sizeof(TCHAR) * (dwLen + 1));
					_tcscpy(reponseInfo.AttributeParentName, (LPCTSTR)_bstr_t(_variant_t(attrValue)));
					reponseInfo.AttributeParentName[dwLen] = _T('\0');
				}
			}
			//reponseInfo.AttributeParentName = (LPCTSTR)_bstr_t(_variant_t(attrValue));
		}
		else if (!_tcsicmp(attrName, _T("namespace")))
		{
			dwLen = _tcslen((LPCTSTR)_bstr_t(_variant_t(attrValue)));
			if (dwLen > 0)
			{
				if (reponseInfo.AttributeNameSpace != NULL)
				{
					delete[] reponseInfo.AttributeNameSpace;
					reponseInfo.AttributeNameSpace = NULL;
				}
				reponseInfo.AttributeNameSpace = new TCHAR[dwLen + 1];
				if (reponseInfo.AttributeNameSpace != NULL)
				{
					memset(reponseInfo.AttributeNameSpace, 0, sizeof(TCHAR) * (dwLen + 1));
					_tcscpy(reponseInfo.AttributeNameSpace, (LPCTSTR)_bstr_t(_variant_t(attrValue)));
					reponseInfo.AttributeNameSpace[dwLen] = _T('\0');
				}
			}
			//reponseInfo.AttributeNameSpace = (LPCTSTR)_bstr_t(_variant_t(attrValue));
		}

		END_TRAVEL_ATTRIBUTES;
	}

	_bstr_t bstr;
	if (FAILED(node->get_text(bstr.GetAddress())))
	{
		return false;
	}

	dwLen = _tcslen((LPCTSTR)bstr);
	if (dwLen > 0)
	{
		if (reponseInfo.AttributeValue != NULL)
		{
			delete[] reponseInfo.AttributeValue;
			reponseInfo.AttributeValue = NULL;
		}
		reponseInfo.AttributeValue = new TCHAR[dwLen + 1];
		if (reponseInfo.AttributeValue != NULL)
		{
			memset(reponseInfo.AttributeValue, 0, sizeof(TCHAR) * (dwLen + 1));
			_tcscpy(reponseInfo.AttributeValue, (LPCTSTR)bstr);
			reponseInfo.AttributeValue[dwLen] = _T('\0');
		}
	}
	//reponseInfo.AttributeValue = (LPCTSTR)bstr;

	return bflag;
}

bool CServerAuth::Parse_Reponse_Body_Original(IXMLDOMNode* node, SReponseInfo& reponseInfo)
{
	_bstr_t bstr;
	if (FAILED(node->get_text(bstr.GetAddress())))
	{
		return false;
	}

	DWORD dwLen = _tcslen((LPCTSTR)bstr);
	if (dwLen > 0)
	{
		if (reponseInfo.Body.Original != NULL)
		{
			delete[] reponseInfo.Body.Original;
			reponseInfo.Body.Original = NULL;
		}
		reponseInfo.Body.Original = new TCHAR[dwLen + 1];
		if (reponseInfo.Body.Original != NULL)
		{
			memset(reponseInfo.Body.Original, 0, sizeof(TCHAR) * (dwLen + 1));
			_tcscpy(reponseInfo.Body.Original, (LPCTSTR)bstr);
			reponseInfo.Body.Original[dwLen] = _T('\0');
		}
	}
	//reponseInfo.Body.Original = (LPCTSTR)bstr;

	return true;
}

// 生成认证原文请求报文
DWORD CServerAuth::BuildRndRequestXML(LPCTSTR pszAppFlag, PTCHAR ptRequest)
{
	TCHAR csRequest[MAX_DATA_LENGTH] = { 0 }, tempBuffer[MAX_PATH] = { 0 };
	DWORD nLen = 0;

	_tcscpy(csRequest, _T("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n<message>\r\n<head>\r\n<version>1.0</version>\r\n<serviceType>OriginalService</serviceType>\r\n</head>\r\n<body>\r\n"));
	nLen = _tcslen(_T("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n<message>\r\n<head>\r\n<version>1.0</version>\r\n<serviceType>OriginalService</serviceType>\r\n</head>\r\n<body>\r\n"));

	_stprintf(tempBuffer, _T("<appId>%s</appId>\r\n</body>\r\n</message>\r\n"), pszAppFlag);

	_tcscpy(csRequest + nLen, tempBuffer);
	nLen += _tcslen(tempBuffer);
	csRequest[nLen] = _T('\n');

	_tcscpy(ptRequest, csRequest);
	/*csRequest.Format(_T("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n")
		_T("<message>\r\n")
		_T("<head>\r\n")
		_T("<version>1.0</version>\r\n")
		_T("<serviceType>OriginalService</serviceType>\r\n")
		_T("</head>\r\n")
		_T("<body>\r\n")
		_T("<appId>%s</appId>\r\n")
		_T("</body>\r\n")
		_T("</message>\r\n"),
		pszAppFlag);*/

	return nLen;
}

DWORD CServerAuth::GetRandOriginal(LPTSTR lpszRandOriginal, DWORD& dwLen)
{
	///////////////////////////////////////////////////
	// 参数检查
	///////////////////////////////////////////////////
	TCHAR csRequest[MAX_DATA_LENGTH] = { 0 };
	DWORD dwRet = AUTH_CODE_SUCCESS;

	if (lpszRandOriginal != NULL)
	{
		//返回原文
		if (m_structReponseInfo.Body.Original != NULL)
		{
			_tcscpy(lpszRandOriginal, m_structReponseInfo.Body.Original);
		}
		else
		{
			dwRet = AUTH_CODE_FAIL;
		}
		return dwRet;
	}
	///////////////////////////////////////////////////
	// 生成认证请求报文
	///////////////////////////////////////////////////
	DWORD nLen = BuildRndRequestXML(m_strAppFlag, csRequest);

	///////////////////////////////////////////////////
	// 发送请求报文到认证服务器
	///////////////////////////////////////////////////
	unsigned short usPort = atoi(_bstr_t(m_strGatePort));
	PTCHAR strReponseHttpBody = NULL;
	DWORD nLength = 0;

	if (m_bIsPlain == false)
	{
		//单向SSL

		dwRet = SendRequest_SingleSSL(csRequest, m_strGateWayIP, usPort, NULL, nLength);
		if (dwRet == AUTH_CODE_SUCCESS && nLength > 1)
		{
			strReponseHttpBody = new TCHAR[nLength + 1];
			if (strReponseHttpBody != NULL)
			{
				memset(strReponseHttpBody, 0, sizeof(TCHAR) * (nLength + 1));
				dwRet = SendRequest_SingleSSL(csRequest, m_strGateWayIP, usPort, strReponseHttpBody, nLength);
				if (nLength <= 1)
				{
					return dwRet;
				}
			}


		}
		else
		{
			return dwRet;
		}
	}
	else
	{
		//明文
		dwRet = SendRequest_Plain(csRequest, m_strGateWayIP, usPort, NULL, nLength);
		if (dwRet == AUTH_CODE_SUCCESS && nLength > 1)
		{
			strReponseHttpBody = new TCHAR[nLength + 1];
			if (strReponseHttpBody != NULL)
			{
				memset(strReponseHttpBody, 0, sizeof(TCHAR) * (nLength + 1));
				dwRet = SendRequest_Plain(csRequest, m_strGateWayIP, usPort, strReponseHttpBody, nLength);
				if (nLength <= 1)
				{
					return dwRet;
				}
			}

		}
		else
		{
			return dwRet;
		}
	}


	//如果已经分配内存，则释放结构体动态分配的内存
	if (m_structReponseInfo.HeadInfo.Version != NULL)
	{
		delete[] m_structReponseInfo.HeadInfo.Version;
		m_structReponseInfo.HeadInfo.Version = NULL;
	}
	if (m_structReponseInfo.HeadInfo.ServiceType != NULL)
	{
		delete[] m_structReponseInfo.HeadInfo.ServiceType;
		m_structReponseInfo.HeadInfo.ServiceType = NULL;
	}
	if (m_structReponseInfo.HeadInfo.MessageStatue != NULL)
	{
		delete[] m_structReponseInfo.HeadInfo.MessageStatue;
		m_structReponseInfo.HeadInfo.MessageStatue = NULL;
	}
	if (m_structReponseInfo.HeadInfo.MessageDesc != NULL)
	{
		delete[] m_structReponseInfo.HeadInfo.MessageDesc;
		m_structReponseInfo.HeadInfo.MessageDesc = NULL;
	}
	if (m_structReponseInfo.HeadInfo.MessageCode != NULL)
	{
		delete[] m_structReponseInfo.HeadInfo.MessageCode;
		m_structReponseInfo.HeadInfo.MessageCode = NULL;
	}

	if (m_structReponseInfo.Body.AttributesType != NULL)
	{
		delete[] m_structReponseInfo.Body.AttributesType;
		m_structReponseInfo.Body.AttributesType = NULL;
	}
	if (m_structReponseInfo.Body.AccessControl != NULL)
	{
		delete[] m_structReponseInfo.Body.AccessControl;
		m_structReponseInfo.Body.AccessControl = NULL;
	}

	if (m_structReponseInfo.Body.Original != NULL)
	{
		delete[] m_structReponseInfo.Body.Original;
		m_structReponseInfo.Body.Original = NULL;
	}
	//
	//释放动态分配的内存
	vector<SAuthResult>::iterator iter;
	for (iter = m_structReponseInfo.Body.AuthResults.begin(); iter != m_structReponseInfo.Body.AuthResults.end(); ++iter)
	{

		if ((*iter).AuthMode != NULL)
		{
			delete[](*iter).AuthMode;
		}
		if ((*iter).AuthMsgCode != NULL)
		{
			delete[](*iter).AuthMsgCode;
		}
		if ((*iter).AuthMsgDesc != NULL)
		{
			delete[](*iter).AuthMsgDesc;
		}
		if ((*iter).AuthStatue != NULL)
		{
			delete[](*iter).AuthStatue;
		}
	}
	//清空向量
	m_structReponseInfo.Body.AuthResults.erase(m_structReponseInfo.Body.AuthResults.begin(), m_structReponseInfo.Body.AuthResults.end());

	//
	//释放动态分配的内存
	vector<SAttributeItem>::iterator iter1;
	for (iter1 = m_structReponseInfo.Body.Attributes.begin(); iter1 != m_structReponseInfo.Body.Attributes.end(); ++iter1)
	{
		if ((*iter1).AttributeName != NULL)
		{
			delete[](*iter1).AttributeName;
		}
		if ((*iter1).AttributeNameSpace != NULL)
		{
			delete[](*iter1).AttributeNameSpace;
		}
		if ((*iter1).AttributeParentName != NULL)
		{
			delete[](*iter1).AttributeParentName;
		}
		if ((*iter1).AttributeValue != NULL)
		{
			delete[](*iter1).AttributeValue;
		}
	}
	m_structReponseInfo.Body.Attributes.erase(m_structReponseInfo.Body.Attributes.begin(), m_structReponseInfo.Body.Attributes.end());

	///////////////////////////////////////////////////
	// 解析服务回应请求到结构体
	///////////////////////////////////////////////////

	ParseReponseInfo(strReponseHttpBody, m_structReponseInfo);



	if (strReponseHttpBody != NULL)
	{
		delete[] strReponseHttpBody;
		strReponseHttpBody = NULL;

	}

	if (NULL != m_structReponseInfo.Body.Original)
		dwLen = _tcslen(m_structReponseInfo.Body.Original);

	return dwRet;
}

LPCTSTR CServerAuth::GetAccessControlResult()
{
	return m_structReponseInfo.Body.AccessControl;
}

//通过属性名获取属性值
BOOL CServerAuth::GetAttributeValue(LPCTSTR AttributeName, LPTSTR AttributeValue, DWORD& dwLen)
{
	BOOL bRet = FALSE;

	//获取属性
	if (AttributeName == NULL)
	{
		return bRet;
	}

	vector<SAttributeItem>::iterator iter;
	for (iter = m_structReponseInfo.Body.Attributes.begin(); iter != m_structReponseInfo.Body.Attributes.end(); ++iter)
	{
		if ((*iter).AttributeName != NULL)
		{
			if (_tcsicmp((*iter).AttributeName, AttributeName) == 0)
			{

				if (AttributeValue != NULL)
				{
					if ((*iter).AttributeValue != NULL)
					{
						_tcscpy(AttributeValue, (*iter).AttributeValue);
						dwLen = _tcslen(AttributeValue);
						AttributeValue[dwLen] = _T('\0');
					}
					bRet = TRUE;
				}
				else
				{
					//返回需要的长度

					if ((*iter).AttributeValue)
					{
						dwLen = _tcslen((*iter).AttributeValue);
					}

					bRet = TRUE;
				}

			}
			if ((*iter).AttributeParentName != NULL)
			{
				//判断parentname_name组件合属性
				TCHAR tmpBuf[MAX_PATH * 2] = { 0 };
				_tcscpy(tmpBuf, (*iter).AttributeParentName);
				DWORD dwLeng = _tcslen(tmpBuf);
				_tcscpy(tmpBuf + dwLeng, _T("_"));
				dwLeng += _tcslen(_T("_"));
				_tcscpy(tmpBuf + dwLeng, (*iter).AttributeName);

				if (_tcsicmp(tmpBuf, AttributeName) == 0)
				{

					if (AttributeValue != NULL)
					{
						if ((*iter).AttributeValue != NULL)
						{
							_tcscpy(AttributeValue, (*iter).AttributeValue);
							dwLen = _tcslen(AttributeValue);
							AttributeValue[dwLen] = _T('\0');
						}
						bRet = TRUE;
					}
					else
					{
						//返回需要的长度

						if ((*iter).AttributeValue)
						{
							dwLen = _tcslen((*iter).AttributeValue);
						}

						bRet = TRUE;
					}

				}
			}

		}
	}

	return bRet;
}

int CServerAuth::GetAttributeSize(void)
{
	return m_structReponseInfo.Body.Attributes.size();
}

BOOL CServerAuth::GetAttribute(int i, LPTSTR AttributeName, long& NameLength, LPTSTR AttributeValue, long& ValueLength, LPTSTR AttributeNameSpace, long& SpaceLength)
{
	BOOL bRet = TRUE;

	if (i > m_structReponseInfo.Body.Attributes.size() - 1)
		return bRet = FALSE;

	// 拷贝属性名
	if (AttributeName != NULL)
	{
		if (m_structReponseInfo.Body.Attributes[i].AttributeName != NULL)
		{
			_tcscpy_s(AttributeName, NameLength, m_structReponseInfo.Body.Attributes[i].AttributeName);
		}
	}
	else
	{
		if (m_structReponseInfo.Body.Attributes[i].AttributeName != NULL)
		{
			long length = _tcslen(m_structReponseInfo.Body.Attributes[i].AttributeName);
			NameLength = length + 1;
		}
	}

	//拷贝属性值
	if (AttributeValue != NULL)
	{
		if (m_structReponseInfo.Body.Attributes[i].AttributeValue != NULL)
		{
			_tcscpy_s(AttributeValue, ValueLength, m_structReponseInfo.Body.Attributes[i].AttributeValue);
		}
	}
	else
	{
		if (m_structReponseInfo.Body.Attributes[i].AttributeValue != NULL)
		{
			long length = _tcslen(m_structReponseInfo.Body.Attributes[i].AttributeValue);
			ValueLength = length + 1;
		}
	}

	// 拷贝命名空间
	if (AttributeNameSpace != NULL)
	{
		if (m_structReponseInfo.Body.Attributes[i].AttributeNameSpace != NULL)
		{
			_tcscpy_s(AttributeNameSpace, SpaceLength, m_structReponseInfo.Body.Attributes[i].AttributeNameSpace);
		}
	}
	else
	{
		if (m_structReponseInfo.Body.Attributes[i].AttributeNameSpace != NULL)
		{
			long length = _tcslen(m_structReponseInfo.Body.Attributes[i].AttributeNameSpace);
			SpaceLength = length + 1;
		}
	}
	/*
	vector<SAttributeItem>::iterator iter;
	for (iter= m_structReponseInfo.Body.Attributes.begin(); iter != m_structReponseInfo.Body.Attributes.end(); ++iter)
	{
		if((*iter).AttributeName != NULL)
		{
			if(_tcsicmp((*iter).AttributeName,AttributeName) == 0)
			{

				if(AttributeValue != NULL)
				{
					if((*iter).AttributeValue != NULL)
					{
						_tcscpy(AttributeValue ,(*iter).AttributeValue);
						dwLen = _tcslen(AttributeValue);
						AttributeValue[dwLen] = _T('\0');
					}
					bRet = TRUE;
				}
				else
				{
					//返回需要的长度

					if((*iter).AttributeValue)
					{
						dwLen = _tcslen((*iter).AttributeValue);
					}

					bRet = TRUE;
				}

			}
			if((*iter).AttributeParentName != NULL)
			{
				//判断parentname_name组件合属性
				TCHAR tmpBuf[MAX_PATH *2] ={0};
				_tcscpy(tmpBuf, (*iter).AttributeParentName);
				DWORD dwLeng = _tcslen(tmpBuf);
				_tcscpy(tmpBuf + dwLeng, _T("_"));
				dwLeng += _tcslen(_T("_"));
				_tcscpy(tmpBuf + dwLeng, (*iter).AttributeName);

				if(_tcsicmp( tmpBuf, AttributeName) == 0)
				{

					if(AttributeValue != NULL)
					{
						if((*iter).AttributeValue != NULL)
						{
							_tcscpy(AttributeValue ,(*iter).AttributeValue);
							dwLen = _tcslen(AttributeValue);
							AttributeValue[dwLen] = _T('\0');
						}
						bRet = TRUE;
					}
					else
					{
						//返回需要的长度

						if((*iter).AttributeValue)
						{
							dwLen = _tcslen((*iter).AttributeValue);
						}

						bRet = TRUE;
					}

				}
			}

		}
	}
	*/
	return bRet;
}

BOOL CServerAuth::GetMessageCode(LPTSTR strMessageCode, DWORD& dwLen)
{
	BOOL dwRet = TRUE;

	if (strMessageCode != NULL && m_structReponseInfo.HeadInfo.MessageCode != NULL)
	{
		_tcscpy(strMessageCode, m_structReponseInfo.HeadInfo.MessageCode);
		dwLen = _tcslen(strMessageCode);
		strMessageCode[dwLen] = _T('\0');
		dwLen += 1;
		return TRUE;
	}

	if (m_structReponseInfo.HeadInfo.MessageCode != NULL)
	{
		dwLen = _tcslen(m_structReponseInfo.HeadInfo.MessageCode);

	}
	else
	{
		dwLen = 0;
		dwRet = FALSE;
	}
	return dwRet;
}

BOOL CServerAuth::GetVersion(LPTSTR strVersion, DWORD& dwLen)
{
	BOOL dwRet = TRUE;

	if (strVersion != NULL && m_structReponseInfo.HeadInfo.Version != NULL)
	{
		_tcscpy(strVersion, m_structReponseInfo.HeadInfo.Version);
		dwLen = _tcslen(strVersion);
		strVersion[dwLen] = _T('\0');
		dwLen += 1;
		return TRUE;
	}

	if (m_structReponseInfo.HeadInfo.Version != NULL)
	{
		dwLen = _tcslen(m_structReponseInfo.HeadInfo.Version);

	}
	else
	{
		dwLen = 0;
		dwRet = FALSE;
	}
	return dwRet;
}

BOOL CServerAuth::MessageStatue(LPTSTR strMessageStatue, DWORD& dwLen)
{
	BOOL dwRet = TRUE;

	if (strMessageStatue != NULL && m_structReponseInfo.HeadInfo.MessageStatue != NULL)
	{
		_tcscpy(strMessageStatue, m_structReponseInfo.HeadInfo.MessageStatue);
		dwLen = _tcslen(strMessageStatue);
		strMessageStatue[dwLen] = _T('\0');
		dwLen += 1;
		return TRUE;
	}

	if (m_structReponseInfo.HeadInfo.MessageStatue != NULL)
	{
		dwLen = _tcslen(m_structReponseInfo.HeadInfo.MessageStatue);

	}
	else
	{
		dwLen = 0;
		dwRet = FALSE;
	}
	return dwRet;
}

BOOL CServerAuth::MessageDesc(LPTSTR strMessageDesc, DWORD& dwLen)
{
	BOOL dwRet = TRUE;

	if (strMessageDesc != NULL && m_structReponseInfo.HeadInfo.MessageDesc != NULL)
	{
		_tcscpy(strMessageDesc, m_structReponseInfo.HeadInfo.MessageDesc);
		dwLen = _tcslen(strMessageDesc);
		strMessageDesc[dwLen] = _T('\0');
		dwLen += 1;
		return TRUE;
	}

	if (m_structReponseInfo.HeadInfo.MessageDesc != NULL)
	{
		dwLen = _tcslen(m_structReponseInfo.HeadInfo.MessageDesc);

	}
	else
	{
		dwLen = 0;
		dwRet = FALSE;
	}
	return dwRet;
}

BOOL CServerAuth::GetOriginal(LPTSTR strOriginal, DWORD& dwLen)
{
	BOOL dwRet = TRUE;

	if (strOriginal != NULL && m_structReponseInfo.Body.Original != NULL)
	{
		_tcscpy(strOriginal, m_structReponseInfo.Body.Original);
		dwLen = _tcslen(strOriginal);
		strOriginal[dwLen] = _T('\0');
		dwLen += 1;
		return TRUE;
	}

	if (m_structReponseInfo.Body.Original != NULL)
	{
		dwLen = _tcslen(m_structReponseInfo.Body.Original);

	}
	else
	{
		dwLen = 0;
		dwRet = FALSE;
	}
	return dwRet;
}