/*
* C++ 客户端认证类 CClientAuth
* 为客户端应用程序提供报文认证接口。
*	
* 使用方法：
* 生成CClientAuth的实例对象；
* 调用成员函数StartAuth()
* 
* Version 2.0
*/

#ifndef CLIENTAUTH_H
#define CLIENTAUTH_H

#include <tchar.h>
#include <memory>
#include <string>

#include "CSKF_API.h"
#include "json/json.h"
#include "base64.h"

using namespace std;

#include "PNXClient_i.h"
#import "PNXClient.dll"

#define BASE64_FLAG_NONE	0
#define BASE64_FLAG_NOPAD	1
#define BASE64_FLAG_CRLF	2

#define MAX_DATA_LEN	4096

//认证时的错误代码:
#define AUTH_CODE_SUCCESS				0	//成功 
#define AUTH_CODE_FAIL					1	//失败
#define AUTH_CODE_CREATE_PNXCLIENT_FAIL		10	//创建PNXCLIENT对象失败 
#define AUTH_CODE_INIT_PNXCLIENT_FAIL		11	//初始化PNXCLIENT失败
#define AUTH_CODE_SELECT_CERT_FAIL		12	//选择认证证书失败
#define AUTH_CODE_AUTH_QUERY_FAIL		13	//生成认证原文认证请求信息失败
#define AUTH_CODE_NOT_ENOUGH_MEMORY		14	//认证请求没有足够的内存
#define AUTH_CODE_DENY				    15	//没有权限 

#ifndef CSKFAPI__
#define CSKFAPI__
//CSKFAPI* g_pGmTest = new CSKFAPI();
#endif

extern CSKFAPI* g_pGmTest;
extern void InitGm(bool jitSafeModule);

class CClientAuth
{

public:
	/*
	* 认证
	* strRequestAuthInfo	[OUT]	认证请求信息
	* dwLen					[OUT]	认证请求信息的长度
	* strRandOriginal		[IN]	随机数
	* strCertSettings		[IN]	用于显示证书选择框的证书配置信息
	* strRootDN				[IN]	根证书信息
	* strUserName			[IN]	用户名， bCertOrPwd等于2时有效
	* strPassword			[IN]	与用户对应的密码， bCertOrPwd等于2时有效
	* bCertOrPwd			[IN]	证书认证或密码认证，为1代表证书认证、为2代表口令认证
	* bSingleCert			[IN]	单证书时不显示证书选择框
	*
	*	返回 AUTH_CODE_SUCCESS 表示成功，其它值为失败。
	*/
	DWORD StartAuth(LPTSTR strRequestAuthInfo, DWORD& dwLen, 
		LPTSTR strRandOriginal, LPCTSTR strCertSettings, LPCTSTR strRootDN, 
		LPCTSTR strUserName = NULL, LPCTSTR strPassword = NULL, 
		DWORD bCertOrPwd = 1, BOOL bSingleCert = TRUE);	//bCertOrPwd 为1代表证书认证、为2代表口令认证

private:
	DWORD buildAuthRequest(LPCTSTR strCertSettings, LPCTSTR strRootDN, LPCTSTR strRandOriginal, LPTSTR strAuthRequest,DWORD nLength,BOOL bSingleCert = TRUE);

	DWORD Encode(const void *pBuffer, unsigned long nBufferSize,PTCHAR strRandOriginal, unsigned long dwFlags = BASE64_FLAG_NONE);
	unsigned char* Decode(const TCHAR *lpszSource, unsigned long *pnResultLen);

	static unsigned long GetEncodeRequiredLength(unsigned long nSrcLen, unsigned long dwFlags = BASE64_FLAG_NONE);

	std::auto_ptr<TCHAR> m_apEncoded;
	std::auto_ptr<unsigned char> m_apDecoded;
};



#endif