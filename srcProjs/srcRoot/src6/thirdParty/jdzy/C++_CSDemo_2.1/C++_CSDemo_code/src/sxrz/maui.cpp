#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include <comutil.h>
#include <strsafe.h>
#include <strsafe.h>
#include <WinInet.h>
#include <regex>
#include <string>

#include    "tmpRegFunc_open.h"
#include    "showInfo_open.h"

#include    "myCmdParams_open.h"

#include	"proc_ca_jdzy.h"

#include <stdio.h>                                                                 
#include <tchar.h> 

#include "./json/config.h"
#include "./json/reader.h"
#include "./json/writer.h"

#include "CSKF_API.h"

#include "atlstr.h"

#include "proc_ca_jdzy.h"

#pragma comment(lib,"Wininet")
#define safecountof(_Array) (_countof(_Array) - 1)
#pragma comment(lib, "comsuppw.lib")
#pragma comment(lib, "kernel32.lib")

using namespace std;

CSKFAPI* g_pGmTest = NULL;

void initGm(bool jitSafeModule) {
	g_pGmTest = new CSKFAPI(jitSafeModule);
}

class Apple{
public:
	static int a;
	Apple(){

	};
};

/*
函数作用：关闭Internet句柄
参数：
hInternet	[in] Internet句柄
hSession	[in] Internet连接句柄
hRequest	[in] Internet 请求句柄

返回值：成功返回TRUE，失败返回FALSE
*/
BOOL ClearHandle(HINTERNET &hInternet,HINTERNET &hSession,HINTERNET &hRequest)
{
	if( hInternet != NULL )
	{
		InternetCloseHandle(hInternet);
		hInternet = NULL;
	}
	if( hSession != NULL )
	{
		InternetCloseHandle(hSession);
		hSession = NULL;
	}
	if( hRequest != NULL )
	{
		InternetCloseHandle(hRequest);
		hRequest = NULL;
	}
	return TRUE;
}

/************************************************************************/
/*调用windows系统API方式向本地插件进程发送http请求*/
/************************************************************************/ 

/***
函数作用：连接服务器
参数：
  pURL		   [in] 请求页面路径，如"/api/clientAuth"
  hInternet	   [out] 返回Internet句柄
  hSession	   [out] Internet连接句柄
  hRequest	   [out] Internet 请求句柄
  pServAddress  [in] 请求地址
  wPort        [in] 请求端口
返回值:	
   TRUE 表示成功，FALSE表示失败
***/
BOOL ConnectServer(const char *pURL,HANDLE &hInternet,HANDLE &hSession,HANDLE &hRequest,const char *pServAddress,WORD wPort)
{
	printf("ConnectServer \n");
	if( pURL == NULL || pServAddress == NULL )
	{
		return FALSE;
	}

    if (wPort == 0)
    {
        wPort = 10086;   //应用服务器默认端口号
    }

	hInternet = NULL;
	hSession = NULL;
	hRequest = NULL;
	hInternet = InternetOpenA("maui",INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
	if ( hInternet == NULL )
	{
		printf("[jit]InternetOpen Fail.%u",GetLastError());
		return FALSE;
	}
	
	DWORD dwTimeOut = 1000*20;
	InternetSetOption(hInternet,INTERNET_OPTION_CONNECT_TIMEOUT,&dwTimeOut,sizeof(DWORD));
	InternetSetOption(hInternet,INTERNET_OPTION_SEND_TIMEOUT,&dwTimeOut,sizeof(DWORD));
	InternetSetOption(hInternet,INTERNET_OPTION_DATA_SEND_TIMEOUT,&dwTimeOut,sizeof(DWORD));
	InternetSetOption(hInternet,INTERNET_OPTION_RECEIVE_TIMEOUT,&dwTimeOut,sizeof(DWORD));

	if (wPort == 443)
	{
		//DWORD dwFlags;
		//DWORD dwBuffLen = sizeof(dwFlags);
		//if (InternetQueryOption(hRequest, INTERNET_OPTION_SECURITY_FLAGS, (LPVOID)&dwFlags, &dwBuffLen)) 
		//{
		//	dwFlags |= SECURITY_FLAG_IGNORE_UNKNOWN_CA | SECURITY_FLAG_IGNORE_CERT_DATE_INVALID | SECURITY_FLAG_IGNORE_CERT_CN_INVALID;
		//	InternetSetOption(hRequest, INTERNET_OPTION_SECURITY_FLAGS, &dwFlags, sizeof(dwFlags));
		//}
	}

	hSession = InternetConnectA(hInternet,pServAddress,wPort,"","",INTERNET_SERVICE_HTTP,0,0);//
	if( hSession == NULL )
	{
		printf("[jit]InternetConnect Fail. %u", GetLastError());
		ClearHandle(hInternet,hSession,hRequest);
		return FALSE;
	}
	//DWORD 	secureFlags =  INTERNET_FLAG_SECURE|INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS|INTERNET_FLAG_RELOAD|INTERNET_FLAG_KEEP_CONNECTION|INTERNET_FLAG_NO_CACHE_WRITE|INTERNET_FLAG_IGNORE_CERT_CN_INVALID;
	DWORD dwSecFlag = 0;
	if (wPort == 443)
	{
		dwSecFlag = INTERNET_FLAG_KEEP_CONNECTION 
					| INTERNET_FLAG_SECURE 
					| SECURITY_FLAG_IGNORE_UNKNOWN_CA 
					| SECURITY_FLAG_IGNORE_CERT_DATE_INVALID 
					| SECURITY_FLAG_IGNORE_CERT_CN_INVALID;
	}
	const char *pAccept = NULL;
	hRequest = HttpOpenRequestA(hSession,"POST",pURL,NULL,NULL,&pAccept, dwSecFlag,0);//secureFlags,0);  // 这里的第三个参数pUrl此时设置为NULL
	
	if( hRequest == NULL )
	{
		printf("[jit]HttpOpenRequest Fail. %u",GetLastError());
		ClearHandle(hInternet,hSession,hRequest);
		return FALSE;
	}
	
	return TRUE;
}

/*
函数作用：发送请求到应用服务器
参数：
    hRequest	[in] 该请求句柄，为ConnectServer函数第4个返回参数
    pData		[in] 附带的数据，一般为post请求的参数，注意是JSON格式
    iDataLen	[in] pData长度，字节
返回值:	
    TRUE 表示成功，FALSE表示失败
*/
BOOL SendRequestToServer(HINTERNET hRequest,const char * pData,int iDataLen)
{
	printf("SendRequestToServer \n");
	if( hRequest == NULL || pData == NULL)
	{
		return FALSE;
	}
	
	CHAR hdrs[] = "Content-Type:  text/plain"; 
	
	DWORD dwTryTime = 5;   //尝试5次
	BOOL bSendSucc = FALSE;

	while( dwTryTime -- )
	{
		bSendSucc = HttpSendRequestA(hRequest,hdrs,strlen(hdrs),(void*)pData,iDataLen);
		DWORD dwErrCode = GetLastError();
		if( bSendSucc == TRUE )
		{
			break;
		}
		if( dwErrCode == ERROR_INTERNET_CLIENT_AUTH_CERT_NEEDED)//客户端需要提交证书
		{
			printf("[jit]HttpSendRequest Fail 客户端需要提交证书. %u \n", dwErrCode);
		}
		else if( dwErrCode == ERROR_INTERNET_INVALID_CA )//服务器证书无效
		{
			printf("[jit]HttpSendRequest Fail 服务器证书无效. %u \n", dwErrCode);
		}
		else
		{
			printf("[jit]HttpSendRequest Fail. %u dwTryTime = %d \n", dwErrCode,dwTryTime);
			break;
		}
	}

	return bSendSucc;
}

/*
函数功能：
从该会话中读取服服务器返回的信息，保存到pData中，pData需要手动进行释放
参数：
    hRequest	[in]	会话句柄
    pData		[out]	服务返回数据的指针
    pLen		[out]	pData内存块大小
    bNeedReport	[in]	表示是否需要进行进度通报
返回值：
    TRUE表示成功，FALSE表示失败
*/

BOOL ReadServerBackData(HINTERNET hRequest,char *&pData,DWORD &Len,BOOL bNeedReport)
{
	printf("ReadServerBackData \n");
	if( hRequest == NULL )
	{
		printf("[jit]hRequest == NULL \n");
		return FALSE;
	}

	DWORD dwResourceSize = 0;
	DWORD dwIndex = 0;
	const int strLen = 1024;
	char strSize[strLen] = {0};
	DWORD dwSize = sizeof(strSize);
	DWORD dwBufflen = 64*1024;//64k

    //1.获取头部状态
	BOOL bRet = HttpQueryInfo(hRequest,HTTP_QUERY_STATUS_CODE ,strSize,&dwSize,&dwIndex);
	if( bRet == FALSE )
	{
		printf("[jit]HttpQueryInfo failed errcode [%u] bRet: [%u] \n", GetLastError(),bRet);
		return FALSE;
	}
	else
	{
		int ret = atoi(strSize);	
		if ( ret != HTTP_STATUS_OK )
		{
			printf("[jit]HttpQueryInfo failed, status code: [%u] strSize: [%d]\n", ret, dwSize);
		}
	}

    //2.获取头部大小
	dwSize = sizeof(strSize);
	bRet = HttpQueryInfo(hRequest,HTTP_QUERY_CONTENT_LENGTH |HTTP_QUERY_ACCEPT_ENCODING,strSize,&dwSize,&dwIndex);
	if( bRet == TRUE )
	{
		dwResourceSize = atoi(strSize);
	}
	if( dwResourceSize != 0 )
	{
		dwBufflen = dwResourceSize + 1;
	}	

    //3.申请读取返回数据缓冲区
	char *pReadData = new char[dwBufflen];
	
	if( pReadData == NULL )
	{
		printf("[jit]HttpQueryInfo failed errcode [%u] bRet: [%u] pReadData is NULL \n", GetLastError(),bRet);
		return FALSE;
	}
	memset(pReadData,0,dwBufflen);

    //4.读取返回信息
	BOOL bSucc = FALSE;
	DWORD dwTotalReadLen = 0;
	while( TRUE )
	{
		DWORD dwReadLen = 0;
		BOOL bRet = InternetReadFile(hRequest,pReadData+dwTotalReadLen,dwBufflen - dwTotalReadLen,&dwReadLen);
		DWORD dwErrCode = GetLastError();
		if( bRet == TRUE )
		{
			dwTotalReadLen += dwReadLen;//累加计数器

			if( (dwReadLen == 0)  || (dwTotalReadLen == dwResourceSize) )//读完
			{
				bSucc = TRUE;
				break;
			}
		}
		else  if((dwErrCode != ERROR_INSUFFICIENT_BUFFER) && (dwErrCode != ERROR_NO_MORE_ITEMS))
		{
			printf("[jit]InternetReadFile Fail.%u",dwErrCode);
			break;
		}
		//执行到这里，表明读取数据成功，或者错误，但是错误原因是没有缓冲区了
		if( (dwBufflen - dwTotalReadLen == 0 ) || ((bRet == FALSE) && 
			(dwErrCode == ERROR_INSUFFICIENT_BUFFER || dwErrCode == ERROR_NO_MORE_ITEMS) ))
			
		{	//空间不够
			dwBufflen *= 2;

			char *pNewData =  new char [dwBufflen];
			
			if( pNewData == NULL )
			{
				delete [] pReadData;
				break;
			}
			memset(pNewData, 0, dwBufflen);
			memcpy(pNewData,pReadData,dwTotalReadLen);
			delete [] pReadData;
			pReadData = pNewData;
		}
	}
	if( bSucc == TRUE )
	{
		pData = pReadData;
		Len = dwTotalReadLen;
	}
	else
	{
		delete [] pReadData;
		pReadData = NULL;
	}
	return bSucc;
}

/* @func:  向服务器发送数据并接受返回数据
*  @param: IN serAddr: 输入的PIN码
*		 : IN reqConnect: 请求资源的名称:例：https://127.0.0.1/reqConnect
*		 : IN serPort:    端口号
*		 : IN pReq:       请求的数据
*		 : OUT pRecvDtat: 服务器返回数据
*        : OUT LenRecvData: 返回数据长度
*
*  @返回值: True:PIN码正确   FALSE：输入PIN码失败
*/
BOOL SendAndRecvData( const char * serAddr,  const char * reqConnect,WORD serPort, const char * pReq, char *& pRecvDtat, DWORD & LenRecvData){
	//printf("SendAndRecvData \n");
#ifdef  __USE_showInfo__
	showInfo_open0(0, 0, _T("SendAndRecvData"));
#endif
	BOOL bRet = FALSE;
	HANDLE hInternet = NULL;
	HANDLE hSession = NULL;
	HANDLE hRequest = NULL;

	if(!ConnectServer(reqConnect, hInternet, hSession, hRequest,serAddr , serPort))
	{
		//printf("ConnectServer failed.\n");
#ifdef  __USE_showInfo__
		showInfo_open0(0, 0, _T("ConnectServer failed."));
#endif
		goto clean;
	}

	// 向服务器发送数据
	if(!SendRequestToServer(hRequest, pReq, strlen(pReq)))
	{
		//printf("SendRequestToServer failed.\n");
#ifdef  __USE_showInfo__
		showInfo_open0(0, 0, _T("SendRequestToServer failed."));
#endif
		goto clean;
	}

	//接受返回后数据
	if(!ReadServerBackData(hRequest, pRecvDtat, LenRecvData, FALSE))
	{
		//printf("ReadServerBackData failed.\n");
#ifdef  __USE_showInfo__
		showInfo_open0(0, 0, _T("ReadServerBackData failed."));
#endif
		goto clean;
	}

	bRet = TRUE;
clean:
	ClearHandle(hInternet,hSession,hRequest);
	return bRet;
}

std::string GetSignCertSN()
{
	std::string strSN;

	return strSN;
}

DWORD UTF8ToUnicode(LPCSTR str, wstring& tostr)
{
	int unicodeLen = ::MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	wchar_t* pUnicode = NULL;
	pUnicode = new wchar_t[unicodeLen];
	//memset(pUnicode, 0, (unicodeLen) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_UTF8, 0, str, -1, pUnicode, unicodeLen);
	tostr = pUnicode;
	delete[] pUnicode;

	return 0;
}

static std::string UnicodeToAnsi(wstring sToMatch)
{
	string sResult;
	int iLen = WideCharToMultiByte(CP_ACP, NULL, sToMatch.c_str(), -1, NULL, 0, NULL, FALSE);
	char* lpsz = new char[iLen];
	WideCharToMultiByte(CP_OEMCP, NULL, sToMatch.c_str(), -1, lpsz, iLen, NULL, FALSE);
	sResult.assign(lpsz, iLen - 1);
	delete[]lpsz; 
	return sResult;
}

string buildTAServiceReq(string clientip, string token, string appid)
{
	if (clientip.length() == 0 ||
		token.length() == 0 ||
		appid.length() == 0)
		return "";
	string strauthreq = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<message><head>\
<version>1.0</version>\
<serviceType>msg_ta_service</serviceType>\
</head>\
<body>";
	strauthreq.append("<clientInfo>");
	strauthreq.append(clientip);
	strauthreq.append("</clientInfo>");

	strauthreq.append("<token>");
	strauthreq.append(token);
	strauthreq.append("</token>");

	strauthreq.append("<appId>");
	strauthreq.append(appid);
	strauthreq.append("</appId>");

	strauthreq.append("<CustomAttributes></CustomAttributes></body></message>");

	return strauthreq;

}

string parseTAServiceRet(string authxml)
{
	//返回数据格式如下
	/*string authxml = ("<?xml version=\"1.0\" encoding=\"utf-8\"?>\
	<message>\
	<head>\
	<version>1.0</version>\
	<serviceType>AuthenService</serviceType>\
	<messageState>false</messageState>\
	</head>\
	<body>\
	<accessControlResult>Permit</accessControlResult>\
	<authResultSet allFailed=\"true\">\
	<authResult authMode=\"cert\" success=\"true\" />\
	</authResultSet>\
	<attributes>\
	<attr name=\"X509Certificate.SubjectDN\"\
	namespace=\"http://www.jit.com.cn/cinas/ias/ns/saml/sam\
	l11/X.509\">CN=测试用户A,O=JIT,C=CN</attr></attributes>\
	<token>78cf4605-f247-4111-a541-63e3402889f0</token>\
	</body>\
	</message>");*/
	size_t ibpos = 0, iepos = 0;

	ibpos = authxml.find("<accessControlResult>");
	iepos = authxml.find("</accessControlResult>", ibpos);
	string accessControlResult = authxml.substr(ibpos + strlen("<accessControlResult>"), iepos - ibpos - strlen("<accessControlResult>"));


	ibpos = authxml.find("<attr name=");
	iepos = authxml.find("</attr>", ibpos);
	string strret = authxml.substr(ibpos + strlen("<attr>"), iepos - ibpos - strlen("<attr>"));


	return strret;
}


int get_sxrz(const char* hgIp, int hgPort, bool jitSafeModule, std::string& recv, const std::string& pwd, int& remainCount)
{
	char serAddr[MAX_PATH] = "127.0.0.1";
	char reqConnect[MAX_PATH] = { 0 };
	WORD serPortQue = 10086;
	char* pRecvData = NULL;
	DWORD LenRecvData = 0;
	TCHAR  tBuf[1024];
	char  buf[1024] = { '\0' };
	int ret = 0;
	char szKeyInfo[4096] = { '\0' };
	if (jitSafeModule) {
		_snprintf(szKeyInfo, mycountof(szKeyInfo), "%s", "<?xml version=\"1.0\" encoding=\"gb2312\"?><authinfo><liblist><lib type=\"CSP\" version=\"1.0\" dllname=\"MTIzNDU2\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib><lib type=\"SKF\" version=\"1.1\" dllname=\"SklUU2FmZU1vZGVsLmRsbA\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib></liblist></authinfo>");
	}
	else {
		_snprintf(szKeyInfo, mycountof(szKeyInfo), "%s", "<?xml version=\"1.0\" encoding=\"gb2312\"?><authinfo><liblist><lib type=\"CSP\" version=\"1.0\" dllname=\"\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib><lib type=\"SKF\" version=\"1.1\" dllname=\"bXRva2VuX2dtMzAwMC5kbGw\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib></liblist></authinfo>");
	}
	
	//bXRva2VuX2dtMzAwMC5kbGw 龙脉key
	//SklUU2FmZU1vZGVsLmRsbA 密码模块
	// ================向本地插件查询当前会话的端口号================
	char pReq[MAX_PATH] = "QueryService";
	//printf("start query \n");
#ifdef  __USE_showInfo__
	showInfo_open0(0, 0, _T("start query"));
#endif
	SendAndRecvData(serAddr, reqConnect, serPortQue, pReq, pRecvData, LenRecvData);
	if (NULL == pRecvData)
	{
		//printf("query current server port is NULL");

#ifdef  __USE_showInfo__
		showInfo_open0(0, 0, _T("query current server port is NULL"));
#endif

		return -3;
	}
	//printf("query current server port : %s \n", pRecvData);

	printLogChar("query current server port-------begin--------");
	printLogChar(pRecvData);
	printLogChar("query current server port--------end--------");


	// 解析返回数据
	std::string strRecvData(pRecvData);
	std::regex str_expr("^http[s]?://([0-9.]*):(\\d*).*/");
	std::smatch sm;
    std:regex_match(strRecvData, sm, str_expr);
	if (!std::regex_match(strRecvData.cbegin(), strRecvData.cend(), sm, str_expr))
	{
		//printf("not match");

#ifdef  __USE_showInfo__
		showInfo_open0(0, 0, _T("not match"));
#endif
	}
	std::string tmp = sm[sm.size() - 1];
	WORD serPortSet = atoi(tmp.c_str());
	//printf("communicate port %d \n ", serPortSet);

#ifdef  __USE_showInfo__
	_sntprintf(tBuf, mycountof(tBuf), _T("communicate port %d"), serPortSet);
	showInfo_open0(0, 0, tBuf);
#endif

	delete[] pRecvData;
	LenRecvData = 0;

	// ================组织初始化消息数据================
	char* pInitRecv = NULL;
	Json::Value jscontent;
	Json::FastWriter jswriter;
	jscontent["strAlgType"] = Json::Value("");
	jscontent["strAuxParam"] = Json::Value(szKeyInfo);
	std::string strParam = jswriter.write(jscontent);
	std::string strInit = "Initialize:" + strParam;
	//向本地插件发送初始化消息
	SendAndRecvData(serAddr, reqConnect, serPortSet, strInit.c_str(), pInitRecv, LenRecvData);
	//解析返回数据
	std::string strInitRsp(pInitRecv);
	Json::Value root;
	Json::Reader reader;
	bool bResult = reader.parse(strInitRsp, root);
	if (bResult && !root.isNull() && root.isObject())
	{
		if (root["value"].isUInt())
		{
			DWORD dwCode = root["value"].asUInt();
			if (dwCode != 1)
			{
				//printf("初始化插件失败!");
#ifdef  __USE_showInfo__
				showInfo_open0(0, 0, _T("init plugin failed"));
#endif
				jscontent.clear();
				delete[] pInitRecv;
				LenRecvData = 0;

				//system("PAUSE");
				return -1;
			}
		}
	}

	jscontent.clear();
	delete[] pInitRecv;
	LenRecvData = 0;

	// ================获取签名证书序列号================
	std::string strCertSN = g_pGmTest->GM_GetSignCertSN();
	//printf("sign cert serialnumber : %s \n", strCertSN.c_str());

	printLogChar("sign cert serialnumber-------begin--------");
	printLogChar(strCertSN.c_str());
	printLogChar("sign cert serialnumber--------end--------");

	// ================调用p7signwithpin验证pin码是否正确================
	char* psignret = NULL;

	jscontent["bstrSN"] = Json::Value(strCertSN.c_str()); //签名证书序列号

	if (jitSafeModule)
	    jscontent["bstrPIN"] = Json::Value("Aa111111"); //key的PIN码
	else 
	    jscontent["bstrPIN"] = Json::Value(pwd); //key的PIN码

	jscontent["strValueBase64"] = Json::Value("dGhpcyBpcyB0ZXN0IHN0cmluZw"); //待签名数据
	jscontent["isDetach"] = Json::Value("true");
	jscontent["isIncludeCert"] = Json::Value("true");
	strParam = jswriter.write(jscontent);
	std::string strP7sign = "P7SignWithPin:" + strParam;

	// 向本地插件发送p7签名消息
	SendAndRecvData(serAddr, reqConnect, serPortSet, strP7sign.c_str(), psignret, LenRecvData);
	// 解析返回数据
	std::string strP7Rec;
	strP7Rec = psignret;

	bResult = reader.parse(strP7Rec, root);
	if (bResult && !root.isNull() && root.isObject())
	{
		std::string strValue = root["value"].asString();

		Json::Value nestedRoot;
		if (reader.parse(strValue, nestedRoot))
		{
			if (!nestedRoot.isNull() && nestedRoot.isObject())
			{
				std::string strResult = nestedRoot["result"].asString();
				int iResult = atoi(strResult.c_str());
				//printf("iResult：%d\n", iResult);
				printLogChar("P7SignWithPin --------begin--------");
				_snprintf(buf, sizeof(buf), "iResult：%d", iResult);
				printLogChar(buf);
				printLogChar("P7SignWithPin --------end--------");

				if (iResult == 0)
				{
					//签名成功
				}
				else
				{
					std::string strCount = nestedRoot["remainretrycount"].asString();
					int iCount = atoi(strCount.c_str());
					//printf("remainretrycount：%d\n", iCount);

					printLogChar("remainretrycount --------begin--------");
					_snprintf(buf, sizeof(buf), "iCount：%d", iCount);
					printLogChar(buf);
					printLogChar("remainretrycount --------end--------");

					if (iCount >= 0)
					{
						//pin码错误 iCount即为重试次数
						remainCount = iCount;
						return -7;
					}
					else
					{
						//其它原因导致签名失败
						return -8;
					}
				}
			}
		}
	}

	jscontent.clear();
	delete[] psignret;
	LenRecvData = 0;


	// ================防止上次未登出 登录前先登出一次================
	char* pLogoutRecv0 = NULL;
	char portBuf[8] = {'\0'};
	_snprintf(portBuf, sizeof(portBuf), "%d", hgPort);
	jscontent["ip"] = Json::Value(hgIp); //网关core1服务地址 处理登录登出请求
	jscontent["port"] = Json::Value(portBuf);	
	strParam = jswriter.write(jscontent);
	std::string strLogout0 = "LogoutGateway:" + strParam;
	// 向本地插件发送登出网关消息
	SendAndRecvData(serAddr, reqConnect, serPortSet, strLogout0.c_str(), pLogoutRecv0, LenRecvData);

	jscontent.clear();
	delete[] pLogoutRecv0;
	LenRecvData = 0;

	// ================组织登录网关消息数据================
	char* pLogonRecv = NULL;
	std::string strDN;
	std::string strToken;
	//jscontent["ip"] = Json::Value("10.0.1.135"); //网关core1服务地址 处理登录登出请求
	//jscontent["port"] = Json::Value("443");
	jscontent["ip"] = Json::Value(hgIp); //网关core1服务地址 处理登录登出请求
	jscontent["port"] = Json::Value(portBuf);
	jscontent["authType"] = Json::Value("1");
	jscontent["authParam1"] = Json::Value(strCertSN.c_str()); //签名证书序列号

	if(jitSafeModule)
	    jscontent["authParam2"] = Json::Value("Aa111111"); //key的PIN码
	else 
		jscontent["authParam2"] = Json::Value(pwd.c_str()); //key的PIN码
	jscontent["authParamReserve"] = Json::Value("0");
	strParam = jswriter.write(jscontent);
	std::string strLogin = "LoginGateway:" + strParam;
	// 向本地插件发送登录网关消息
	SendAndRecvData(serAddr, reqConnect, serPortSet, strLogin.c_str(), pLogonRecv, LenRecvData);
	// 解析返回数据
	std::wstring wsRec;
	std::string strRec;
	UTF8ToUnicode(pLogonRecv, wsRec);
	strRec = UnicodeToAnsi(wsRec);
#ifdef  __USE_showInfo__
	showInfo_open0(0, 0, _T("cert info"));
	showInfo_open0(0, 0, wsRec.c_str());
	showInfo_open0(0, 0, _T("cert info"));
#endif

	//printf("登录网关服务器 返回结果：%s\n", strRec.c_str());

#ifdef  __USE_showInfo__
	_sntprintf(tBuf, mycountof(tBuf), _T("login gateway result : %s"), wsRec.c_str());
	showInfo_open0(0, 0, tBuf);
#endif

	bResult = reader.parse(strRec, root);
	if (bResult && !root.isNull() && root.isObject())
	{
		if (root["code"].isString())
		{
			std::string strCode = root["code"].asString();
			if (strCode == "0")
			{
				if (root["data"]["dn"].isString())
				{
					strDN = root["data"]["dn"].asString();
					if (strDN.length() == 0)
					{
						std::string strMsg = root["message"].asString();
						//printf("login return message : %s \n", strMsg.c_str());

						printLogChar("login return message--------begin--------");
						printLogChar(strMsg.c_str());
						printLogChar("login return message--------end--------");

					}
					else
					{
						//printf("user dn:%s\n", strDN.c_str());
						printLogChar("user dn--------begin--------");
						printLogChar(strDN.c_str());
						printLogChar("user dn--------end--------");

					}
				}
				if (root["data"]["token"].isString())
				{
					strToken = root["data"]["token"].asString();
					if (strToken.length() == 0)
					{
						std::string strMsg = root["message"].asString();
						//printf("login return message : %s \n", strMsg.c_str());

						printLogChar("login return message --------begin--------");
						printLogChar(strMsg.c_str());
						printLogChar("login return message --------end--------");

					}
					else
					{
						//printf("token:%s\n", strToken.c_str());

						printLogChar("token --------begin--------");
						printLogChar(strToken.c_str());
						printLogChar("token--------end--------");

					}
				}
			}
		}
	}
	else
	{
		//printf("登录失败 错误信息 : %s\n", strRec.c_str());
		printLogChar("login failed, err msg --------begin--------");
		printLogChar(strRec.c_str());
		printLogChar("login failed, err msg--------end--------");

	}

	jscontent.clear();
	delete[] pLogonRecv;
	LenRecvData = 0;

	// ================组织获取登录信息数据================登录时已返回证书dn和token 此处无需调用
	//char* pGetInfoRecv = NULL;
	//jscontent["ip"] = Json::Value("192.168.9.80");
	//jscontent["port"] = Json::Value("443");
	//strParam = jswriter.write(jscontent);
	//std::string strGetUserInfo = "GetLoginInfo:" + strParam;
	//// 向本地插件发送获取登录信息的消息
	//SendAndRecvData(serAddr, reqConnect, serPortSet, strGetUserInfo.c_str(), pGetInfoRecv, LenRecvData);
	//// 解析返回数据
	//UTF8ToUnicode(pGetInfoRecv, wsRec);
	//strRec = UnicodeToAnsi(wsRec);

	//bResult = reader.parse(strRec, root);
	//if (bResult && !root.isNull() && root.isObject())
	//{
	//	if (root["code"].isString())
	//	{
	//		std::string strCode = root["code"].asString();
	//		if (strCode == "0")
	//		{
	//			if (root["data"]["dn"].isString())
	//			{
	//				std::string strDN = root["data"]["dn"].asString();
	//				printf("GetLoginInfo certDN : %s \n", strDN.c_str());
	//			}
	//		}
	//	}
	//}

	//jscontent.clear();
	//delete[] pGetInfoRecv;
	//LenRecvData = 0;

	// ================T+A认证================
	char* pTAServiceRecv = NULL;
	std::string strGWSvrIP = hgIp; //网关报文认证服务地址 处理T+A认证请求
	DWORD dwGWSvrPort = hgPort;
	//组织请求数据
	string strTAService = buildTAServiceReq("127.0.0.1", strToken, "testApp");

	//发送请求
	BOOL bRet = SendAndRecvData(strGWSvrIP.c_str(), "/MessageService", dwGWSvrPort, strTAService.c_str(),
		pTAServiceRecv, LenRecvData);
	if (bRet == FALSE)
	{
		//printf("T+A认证失败");
#ifdef  __USE_showInfo__
		showInfo_open0(0, 0, _T("cert failed"));
#endif
		ret = -2;
		goto logoutgw;
	}
	//解析返回数据
	UTF8ToUnicode(pTAServiceRecv, wsRec);
	strRec = UnicodeToAnsi(wsRec);
	//printf("T+A认证 返回数据 : %s \n", strRec.c_str());

	recv = strRec;

#ifdef  __USE_showInfo__
	_sntprintf(tBuf, mycountof(tBuf), _T("T+A cert, return data : %s"), wsRec.c_str());
	showInfo_open0(0, 0, tBuf);
#endif

	parseTAServiceRet(strRec);

	delete[] pTAServiceRecv;
	LenRecvData = 0;
logoutgw:
	// ================组织登出网关消息数据================
	char* pLogoutRecv = NULL;
	jscontent["ip"] = Json::Value(hgIp); //网关core1服务地址 处理登录登出请求
	jscontent["port"] = Json::Value(portBuf);
	strParam = jswriter.write(jscontent);
	std::string strLogout = "LogoutGateway:" + strParam;
	// 向本地插件发送登出网关消息
	SendAndRecvData(serAddr, reqConnect, serPortSet, strLogout.c_str(), pLogoutRecv, LenRecvData);
	

	jscontent.clear();
	delete[] pLogoutRecv;
	LenRecvData = 0;

	return ret;
}

void SpiltCString(CString strSrc, CString strSpilt, vector<CString>& strRst)
{
	int iPos = strSrc.Find(strSpilt);
	CString strTmp;
	int iSpiltLen = strSpilt.GetLength();

	while (iPos != -1)
	{
		strTmp = strSrc.Left(iPos);
		strRst.push_back(strTmp);
		strSrc = strSrc.Mid(iPos + iSpiltLen);
		iPos = strSrc.Find(strSpilt);
	}
	if (strSrc.GetLength() != 0)
	{
		strRst.push_back(strSrc);
	}

}

//
int jdzy_main(TCHAR* cmdLine)
{
	//
	int  iErr = -1;
	TCHAR* pT;
	int  ii;
	TCHAR  tBuf[512];
	char   buf[512] = { '\0' };



	//
	parseCmdLine_ca(cmdLine, &gBuf.m_var.appParams);

	//
#ifdef  __USE_showInfo__
	initShowInfo_cli(0, _T("syncQ_showInfo_qmc"), (char*)"127.0.0.1", &gBuf.m_var.pShowInfoStruct);
	//
#if 0
	if (gBuf.m_var.appParams.bSys) set_who_showInfo(_T("bjca.serv"));
	else  set_who_showInfo(_T("bjca.cli"));
#endif
	set_who_showInfo(gBuf.m_var.appParams.who_showInfo);
#endif

	//
#ifdef  __USE_showInfo__
	_sntprintf(tBuf, mycountof(tBuf), _T("jdzy_sx cmd %d, tn %d, sys %d, devPre %s, dev %d"), gBuf.m_var.appParams.iCmd, gBuf.m_var.appParams.tn, gBuf.m_var.appParams.bSys,
		gBuf.m_var.appParams.devPrefix, gBuf.m_var.appParams.bDev);
	showInfo_open0(0, 0, tBuf);
#endif

	printLogChar("jdzy_main ---------password------begin------");
	_snprintf(buf, sizeof(buf), "caIp=%s, caPort=%d, pwd=%s", gBuf.m_var.appParams.caGwIp, gBuf.m_var.appParams.caGwPort,  gBuf.m_var.appParams.pwd);
	printLogChar(buf);
	printLogChar("jdzy_main ---------password------end------");

	bool jitSafeModule = true;

	if (gBuf.m_var.appParams.iCmd == CONST_caCmd_usrData) {
		initGm(false);
		jitSafeModule = false;
	}
	else {
		initGm(true);
	}

	printLog(tBuf);
	std::string recv;
	std::string user;
	int iCount = -1;
	int ret = get_sxrz(gBuf.m_var.appParams.caGwIp, gBuf.m_var.appParams.caGwPort, jitSafeModule, recv, gBuf.m_var.appParams.pwd, iCount);

	printLogChar("jdzy_main ---------recv------begin------");
	printLogChar(recv.c_str());
	printLogChar("jdzy_main ---------recv------end------");

	if (ret == 0 && recv.length() > 0) {
		int pos = recv.find("name=\"dnname\"");
		if (pos != std::string::npos) {

			int start = recv.find(">", pos);
			if (start != std::string::npos) {
				int end = recv.find("</attr>", start);
				if (end != std::string::npos) {
					user = recv.substr(start + 1, end - start - 1);

					CString tmp(user.c_str());

					std::vector<CString> splitStr;

					SpiltCString(tmp, _T(","), splitStr);

					for (auto item : splitStr) {
						std::vector<CString> itemStr;
						SpiltCString(item, _T("="), itemStr);
						if (itemStr.size() == 2) {
							if (itemStr[0] == "CN") {
								user = (CT2A)itemStr[1];
								break;
							}
						}

					}

				}
			}
		}
		else if (ret == -7) {
#ifdef  __USE_showInfo__
			showInfo_open0(0, 0, _T("pin error"));
#endif
		}
		else {
#ifdef  __USE_showInfo__
			showInfo_open0(0, 0, _T("no find dnname"));
#endif
		}
	}
	else {
#ifdef  __USE_showInfo__
		_sntprintf(tBuf, mycountof(tBuf), _T("get_sxrz: ret=%d, recv.length=%d"), ret, recv.length());
		showInfo_open0(0, 0, tBuf);
#endif
	}

	gBuf.m_var.hKeyRoot0 = gBuf.m_var.appParams.bSys ? HKEY_LOCAL_MACHINE : HKEY_CURRENT_USER;	


	printLogChar(user.c_str());

	if (ret == 0 && user.length() > 0) {
		if (gBuf.m_var.appParams.iCmd == CONST_caCmd_usrData) {

			TCHAR  cfgName[128];
			_sntprintf(cfgName, mycountof(cfgName), _T("%s%d"), _T(CONST_regValName_ca_sendDataResp_prefix), gBuf.m_var.appParams.tn);
			unsigned int  uiType;
			uiType = REG_BINARY;
			char resp[1024];
			_snprintf(resp, mycountof(resp), "-%s%s", CONST_sym_usr, user.c_str());

			if (tmpSetRegCfg_open(gBuf.m_var.hKeyRoot0, _T(CONST_rootKey_ca), cfgName, uiType, resp, strlen(resp))) {
				showInfo_open0(0, 0, _T("jdzy.getuser failed, tmpSetRegCfg_open failed, resp"));
				goto  errLabel;
			}
			//
			_sntprintf(tBuf, mycountof(tBuf), _T("jdzy.getuser: tmpSetRegCfg: %s->%S"), cfgName, (char*)user.c_str());
			showInfo_open0(0, 0, tBuf);
			

		}
		else if (gBuf.m_var.appParams.iCmd == CONST_caCmd_login_auth) {

			TCHAR  cfgName_resp_cli_cert[128];
			TCHAR  cfgName_resp_cli_signData[128];

			_sntprintf(cfgName_resp_cli_cert, mycountof(cfgName_resp_cli_cert), _T("%s%d"), _T(CONST_regValName_cli_cert_prefix), gBuf.m_var.appParams.tn);
			_sntprintf(cfgName_resp_cli_signData, mycountof(cfgName_resp_cli_signData), _T("%s%d"), _T(CONST_regValName_cli_signData_prefix), gBuf.m_var.appParams.tn);


			unsigned int  uiType = 0;
			uiType = REG_BINARY;
			tmpSetRegCfg_open(gBuf.m_var.hKeyRoot0, _T(CONST_rootKey_ca), cfgName_resp_cli_cert, uiType, (char*)user.c_str(), user.length());
			tmpSetRegCfg_open(gBuf.m_var.hKeyRoot0, _T(CONST_rootKey_ca), cfgName_resp_cli_signData, uiType, (char*)user.c_str(), user.length());
		}
	}
	else if (ret == -7) {
		char resp[1024];
		_snprintf(resp, mycountof(resp), "%d", iCount);
		{
			TCHAR  cfgName[128];
			_sntprintf(cfgName, mycountof(cfgName), _T("%s%d"), _T(CONST_regValName_ca_pinRetryCountResp_prefix), gBuf.m_var.appParams.tn);
			unsigned int  uiType;
			uiType = REG_BINARY;
			tmpSetRegCfg_open(gBuf.m_var.hKeyRoot0, _T(CONST_rootKey_ca), cfgName, uiType, resp, strlen(resp));
		}

#ifdef  __USE_showInfo__
		showInfo_open0(0, 0, _T("pin error2"));
#endif
		
	}
	else {
#ifdef  __USE_showInfo__
		showInfo_open0(0, 0, _T("cert failed, no find user"));
#endif
	}
	
	//
errLabel:
END:

	//
#ifdef  __USE_showInfo__
	showInfo_open0(0, 0, _T("jdzy_xz leaves"));
	//
	exitShowInfo(&gBuf.m_var.pShowInfoStruct);
#endif

	//
	return 0;
}

int main()
{
	TCHAR* cmdLine = GetCommandLine();
	jdzy_main(cmdLine);

	return 0;

	
//	char serAddr[MAX_PATH] = "127.0.0.1";
//	char reqConnect[MAX_PATH] = {0};
//	WORD serPortQue = 10086;
//	char * pRecvData = NULL;
//	DWORD LenRecvData = 0;
//	char szKeyInfo[4096] = "<?xml version=\"1.0\" encoding=\"gb2312\"?><authinfo><liblist><lib type=\"CSP\" version=\"1.0\" dllname=\"MTIzNDU2\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib><lib type=\"SKF\" version=\"1.1\" dllname=\"SklUU2FmZU1vZGVsLmRsbA\" ><algid val=\"SHA1\" sm2_hashalg=\"sm3\"/></lib></liblist></authinfo>";
//	//bXRva2VuX2dtMzAwMC5kbGw 龙脉key
//	//SklUU2FmZU1vZGVsLmRsbA 密码模块
//	// ================向本地插件查询当前会话的端口号================
//	char pReq[MAX_PATH] = "QueryService";
//	printf("start query \n");
//	SendAndRecvData(serAddr, reqConnect, serPortQue,pReq, pRecvData,  LenRecvData);
//	if (NULL == pRecvData)
//	{
//		printf("query current server port is NULL");
//	}
//	printf("query current server port : %s \n",pRecvData);
//	
//	// 解析返回数据
//	std::string strRecvData(pRecvData);
//	std::regex str_expr("^http[s]?://([0-9.]*):(\\d*).*/");
//	std::smatch sm;
//	std:regex_match(strRecvData, sm, str_expr);
//	if(!std::regex_match ( strRecvData.cbegin(), strRecvData.cend(), sm, str_expr))
//	{
//		printf("not match");
//	}
//	std::string tmp = sm[sm.size()-1];
//	WORD serPortSet = atoi(tmp.c_str());
//	printf("communicate port %d \n ",serPortSet);
//
// 	delete[] pRecvData;
//	LenRecvData = 0;
//	
//	// ================组织初始化消息数据================
//	char* pInitRecv = NULL;
//	Json::Value jscontent;
//	Json::FastWriter jswriter;
//	jscontent["strAlgType"] = Json::Value("");
//	jscontent["strAuxParam"] = Json::Value(szKeyInfo);
//	std::string strParam = jswriter.write(jscontent);
//	std::string strInit = "Initialize:" + strParam;
//	//向本地插件发送初始化消息
//	SendAndRecvData(serAddr, reqConnect, serPortSet, strInit.c_str(), pInitRecv, LenRecvData);
//	//解析返回数据
//	std::string strInitRsp(pInitRecv);
//	Json::Value root;
//	Json::Reader reader;
//	bool bResult = reader.parse(strInitRsp, root);
//	if (bResult && !root.isNull() && root.isObject())
//	{
//		if (root["value"].isUInt())
//		{
//			DWORD dwCode = root["value"].asUInt();
//			if (dwCode != 1)
//			{
//				printf("初始化插件失败!");
//				jscontent.clear();
//				delete[] pInitRecv;
//				LenRecvData = 0;
//
//				system("PAUSE");
//				return 0;
//			}
//		}
//	}
//
//	jscontent.clear();
//	delete[] pInitRecv;
//	LenRecvData = 0;
//
//	// ================获取签名证书序列号================
//	std::string strCertSN = g_pGmTest->GM_GetSignCertSN();
//	printf("sign cert serialnumber : %s \n", strCertSN.c_str());
//
//	// ================防止上次未登出 登录前先登出一次================
//	char* pLogoutRecv0 = NULL;
//	jscontent["ip"] = Json::Value("10.0.1.135"); //网关core1服务地址 处理登录登出请求
//	jscontent["port"] = Json::Value("443");
//	strParam = jswriter.write(jscontent);
//	std::string strLogout0 = "LogoutGateway:" + strParam;
//	// 向本地插件发送登出网关消息
//	SendAndRecvData(serAddr, reqConnect, serPortSet, strLogout0.c_str(), pLogoutRecv0, LenRecvData);
//
//	jscontent.clear();
//	delete[] pLogoutRecv0;
//	LenRecvData = 0;
//
//	// ================组织登录网关消息数据================
//	char* pLogonRecv = NULL;
//	std::string strDN;
//	std::string strToken;
//
//	jscontent["ip"] = Json::Value("10.0.1.135"); //网关core1服务地址 处理登录登出请求
//	jscontent["port"] = Json::Value("443");
//	jscontent["authType"] = Json::Value("1");
//	jscontent["authParam1"] = Json::Value(strCertSN.c_str()); //签名证书序列号
//	jscontent["authParam2"] = Json::Value("Aa111111"); //key的PIN码
//	jscontent["authParamReserve"] = Json::Value("0");
//	strParam = jswriter.write(jscontent);
//	std::string strLogin = "LoginGateway:" + strParam;
//	// 向本地插件发送登录网关消息
//	SendAndRecvData(serAddr, reqConnect, serPortSet, strLogin.c_str(), pLogonRecv, LenRecvData);
//	// 解析返回数据
//	std::wstring wsRec;
//	std::string strRec;
//	UTF8ToUnicode(pLogonRecv, wsRec);
//	strRec = UnicodeToAnsi(wsRec);
//	
//	printf("登录网关服务器 返回结果：%s\n", strRec.c_str());
//
//	bResult = reader.parse(strRec, root);
//	if (bResult && !root.isNull() && root.isObject())
//	{
//		if (root["code"].isString())
//		{
//			std::string strCode = root["code"].asString();
//			if (strCode == "0")
//			{
//				if (root["data"]["dn"].isString())
//				{
//					strDN = root["data"]["dn"].asString();
//					if (strDN.length() == 0)
//					{
//						std::string strMsg = root["message"].asString();
//						printf("login return message : %s \n", strMsg.c_str());
//					}
//					else
//					{
//						printf("user dn:%s\n", strDN.c_str());
//					}
//				}
//				if (root["data"]["token"].isString())
//				{
//					strToken = root["data"]["token"].asString();
//					if (strToken.length() == 0)
//					{
//						std::string strMsg = root["message"].asString();
//						printf("login return message : %s \n", strMsg.c_str());
//					}
//					else
//					{
//						printf("token:%s\n", strToken.c_str());
//					}
//				}
//			}
//		}
//	}
//	else
//	{
//		printf("登录失败 错误信息 : %s\n", strRec.c_str());
//	}
//
//	jscontent.clear();
//	delete[] pLogonRecv;
//	LenRecvData = 0;
//
//	// ================组织获取登录信息数据================登录时已返回证书dn和token 此处无需调用
//	//char* pGetInfoRecv = NULL;
//	//jscontent["ip"] = Json::Value("192.168.9.80");
//	//jscontent["port"] = Json::Value("443");
//	//strParam = jswriter.write(jscontent);
//	//std::string strGetUserInfo = "GetLoginInfo:" + strParam;
//	//// 向本地插件发送获取登录信息的消息
//	//SendAndRecvData(serAddr, reqConnect, serPortSet, strGetUserInfo.c_str(), pGetInfoRecv, LenRecvData);
//	//// 解析返回数据
//	//UTF8ToUnicode(pGetInfoRecv, wsRec);
//	//strRec = UnicodeToAnsi(wsRec);
//
//	//bResult = reader.parse(strRec, root);
//	//if (bResult && !root.isNull() && root.isObject())
//	//{
//	//	if (root["code"].isString())
//	//	{
//	//		std::string strCode = root["code"].asString();
//	//		if (strCode == "0")
//	//		{
//	//			if (root["data"]["dn"].isString())
//	//			{
//	//				std::string strDN = root["data"]["dn"].asString();
//	//				printf("GetLoginInfo certDN : %s \n", strDN.c_str());
//	//			}
//	//		}
//	//	}
//	//}
//
//	//jscontent.clear();
//	//delete[] pGetInfoRecv;
//	//LenRecvData = 0;
//
//	// ================T+A认证================
//	char* pTAServiceRecv = NULL;
//	std::string strGWSvrIP = "10.0.1.135"; //网关报文认证服务地址 处理T+A认证请求
//	DWORD dwGWSvrPort = 443;
//	//组织请求数据
//	string strTAService = buildTAServiceReq("127.0.0.1", strToken, "testApp");
//
//	//发送请求
// 	BOOL bRet = SendAndRecvData(strGWSvrIP.c_str(), "/MessageService", dwGWSvrPort, strTAService.c_str(), 
//								pTAServiceRecv, LenRecvData);
//	if (bRet == FALSE)
//	{
//		printf("T+A认证失败");
//		goto logoutgw;
//	}
//	//解析返回数据
//	UTF8ToUnicode(pTAServiceRecv, wsRec);
//	strRec = UnicodeToAnsi(wsRec);
//	printf("T+A认证 返回数据 : %s \n", strRec.c_str());
//	parseTAServiceRet(strRec);
//
//	delete[] pTAServiceRecv;
//	LenRecvData = 0;
//logoutgw:
//	// ================组织登出网关消息数据================
//	char* pLogoutRecv = NULL;
//	jscontent["ip"] = Json::Value("10.0.1.135"); //网关core1服务地址 处理登录登出请求
//	jscontent["port"] = Json::Value("443");
//	strParam = jswriter.write(jscontent);
//	std::string strLogout = "LogoutGateway:" + strParam;
//	// 向本地插件发送登出网关消息
//	SendAndRecvData(serAddr, reqConnect, serPortSet, strLogout.c_str(), pLogoutRecv, LenRecvData);
//
//	jscontent.clear();
//	delete[] pLogoutRecv;
//	LenRecvData = 0;
//
//	system("PAUSE");
	return 0;
}