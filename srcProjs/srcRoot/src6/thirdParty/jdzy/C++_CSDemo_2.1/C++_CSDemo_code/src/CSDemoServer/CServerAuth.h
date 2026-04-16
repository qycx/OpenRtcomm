
#ifndef CSERVERAUTH_H
#define CSERVERAUTH_H

#include <tchar.h>
#include <vector>
using namespace std;

#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
#include <memory>
#include <string>
//#include <atlcomcli.h>
//
#include <comutil.h>
#pragma comment(lib, "comsuppw.lib")

#include <openssl/ssl.h>
#include <openssl/err.h>
//#ifndef _WIN64
//#pragma comment(lib, "libeay32.lib")
//#pragma comment(lib, "ssleay32.lib")
//#else
//#pragma comment(lib, "libeay64.lib")
//#pragma comment(lib, "ssleay64.lib")
//#endif

#ifdef WIN32
#pragma comment(lib,"User32.lib")
#pragma comment(lib,"Advapi32.lib")
#pragma comment(lib,"Gdi32.lib")
#pragma comment(lib,"legacy_stdio_definitions.lib")
#pragma comment(lib,"libeay32.lib")
#pragma comment(lib,"ssleay32.lib")
#endif


#if _MSC_VER>=1900
#include "stdio.h" 
_ACRTIMP_ALT FILE* __cdecl __acrt_iob_func(unsigned);
#ifdef __cplusplus 
extern "C"
#endif 
extern FILE * __cdecl __iob_func(unsigned i);
#endif


/*
#if _MSC_VER>=1900
#include "stdio.h" 
_ACRTIMP_ALT FILE* __cdecl __acrt_iob_func(unsigned);
#ifdef __cplusplus 
extern "C"
#endif 
FILE * __cdecl __iob_func(unsigned i) {
	return __acrt_iob_func(i);
}
#endif */
/* _MSC_VER>=1900 */



#define HTTP_LINE_END                               "\r\n"
#define HTTP_LINE_END_LEN                           2

#define BASE64_FLAG_NONE	0
#define BASE64_FLAG_NOPAD	1
#define BASE64_FLAG_CRLF	2

#define MAX_DATA_LENGTH		4096


#define AUTH_CODE_SUCCESS			0	//成功 
#define AUTH_CODE_FAIL				1	//失败
#define AUTH_CODE_DENY				2	//DENY

#define AUTH_CODE_XML_INIT_FAIL			10	//XMLHTTPRequest组件初始化失败
#define AUTH_CODE_SSL_CONTEXT_FAIL		11	//获取SSL上下文信息失败
#define AUTH_CODE_SSL_OBJECT_FAIL		12	//获取SSL对象失败
#define AUTH_CODE_SSL_FD_FAIL			13	//SSL链接文件描述符失败
#define AUTH_CODE_SSL_CONNECT_FAIL		14	//SSL连接服务器失败


//extern int (WINAPIV* __vsnprintf)(char*, size_t, const char*, va_list);

//遍历子节点
//node: 要遍历的节点
//childNodeVariableName: 枚举到的子节点变量名
//childNodeNameVariableName_bstr_t: childNodeVariableName 的节点名，_bstr_t 类型的
#define BEGIN_TRAVEL_CHILDREN(node, childNodeVariableName, childNodeNameVariableName, bflag) \
	CoInitialize(NULL); \
	IXMLDOMNodeList* children = NULL; \
	IXMLDOMNode* childNodeVariableName = NULL; \
    if (FAILED(node->get_childNodes(&children))) \
    { \
		bflag = false; \
        goto End; \
    } \
    \
    long ttl = 0; \
    if (FAILED(children->get_length(&ttl))) \
    { \
		bflag = false; \
        goto End; \
    } \
    if (ttl < 0) \
    { \
		bflag = false; \
        goto End; \
    } \
    \
    for(UINT i = 0; i < (UINT)ttl; ++i) \
    { \
        if (FAILED(children->get_item(i, &childNodeVariableName))) \
        { \
			bflag = false; \
            goto End; \
        } \
        DOMNodeType nodeType; \
        if (FAILED(childNodeVariableName->get_nodeType(&nodeType))) \
        { \
			bflag = false; \
            goto End; \
        } \
        if (nodeType != NODE_ELEMENT) \
        { \
            continue; \
        } \
        BSTR bstr; \
        if (FAILED(childNodeVariableName->get_nodeName(&bstr))) \
        { \
			bflag = false; \
            goto End; \
        } \
        _bstr_t childNodeNameVariableName(bstr); \
        ::SysFreeString(bstr); \
        bstr = NULL; 
		 

#define END_TRAVEL_CHILDREN(childNodeVariableName) \
		if(childNodeVariableName != NULL) \
		{ \
			childNodeVariableName->Release(); \
			childNodeVariableName = NULL; \
		} \
    } \
End: \
	if(children != NULL) \
	{ \
		children->Release(); \
	} \
	if(childNodeVariableName != NULL) \
	{ \
		childNodeVariableName->Release(); \
	} \
	CoUninitialize();



//遍历节点属性
#define BEGIN_TRAVEL_ATTRIBUTES(node, attrNameVariableName, attrValueVariableName, bflag) \
	CoInitialize(NULL); \
	IXMLDOMNamedNodeMap* attrList = NULL; \
	IXMLDOMNode* attrNode = NULL; \
    if (FAILED(node->get_attributes(&attrList))) \
    { \
        bflag = false; \
		goto AttrEnd; \
    } \
    long ttl = 0; \
    if (FAILED(attrList->get_length(&ttl))) \
    { \
        bflag = false; \
        goto AttrEnd; \
    } \
    if (ttl < 0) \
    { \
        bflag = false; \
        goto AttrEnd; \
    } \
    \
    for(UINT i = 0; i < (UINT)ttl; ++i) \
    { \
        if (FAILED(attrList->get_item(i, &attrNode))) \
        { \
            bflag = false; \
            goto AttrEnd; \
        } \
		BSTR bstrName; \
		attrNode->get_baseName(&bstrName); \
		_bstr_t attrNameVariableName; \
		attrNameVariableName = bstrName; \
		::SysFreeString(bstrName); \
		bstrName = NULL; \
		VARIANT v; \
		attrNode->get_nodeValue(&v); \
		_bstr_t attrValueVariableName = v.bstrVal; \
		if(attrNode != NULL) \
		{ \
			attrNode->Release(); \
			attrNode = NULL; \
		} 
         
		

#define END_TRAVEL_ATTRIBUTES \
    } \
AttrEnd: \
	if(attrList != NULL) \
	{ \
		attrList->Release(); \
	} \
	if(attrNode != NULL) \
	{ \
		attrNode->Release(); \
	} \
	CoUninitialize();






typedef struct SAttributeItem
{
    PTCHAR AttributeParentName;
    PTCHAR AttributeName; //属性名字
    PTCHAR AttributeNameSpace; //属性命名空间
    PTCHAR AttributeValue; //属性值
}StructAttributeItem;

typedef struct SAuthResult
{
    PTCHAR AuthMode; //认证方式
    PTCHAR AuthStatue; //认证状态
    PTCHAR AuthMsgCode; //认证结果返回码
    PTCHAR AuthMsgDesc; //认证结果返回码描述
}StructAuthResult;

typedef struct SReponseInfo
{
    struct SHeadInfo
    {
        PTCHAR Version; //认证请求版本
        PTCHAR ServiceType; //认证请求服务类型
        PTCHAR MessageStatue; //认证请求状态
        PTCHAR MessageCode; //认证请求返回码
        PTCHAR MessageDesc; //认证请求返回码描述
    }HeadInfo; //认证请求头信息

    struct SBody
    {
        PTCHAR AttributesType; //认证请求返回属性类型
        vector<SAuthResult> AuthResults; //认证结果容器
        PTCHAR AccessControl; //访问控制（目前保留）
        vector<SAttributeItem> Attributes; //认证属性结果容器
        PTCHAR Original; //认证原文
    }Body; //认证请求体信息
}StructReponseInfo;

class CServerAuth
{


public:
	/*
	* strGateWayIP	[IN]	网关IP
	* strGatePort	[IN]	网关端口
	* strAppFlag	[IN]	应用标识符
	* bIsPlain		[IN]	明文/密文 连接方式; 0 为明文连接，1为密文连接
	* nXMLVer		[IN]	报文的版本，10为应用服务器生成并管理随机数，11为网关生成随机数，建议使用网关生成随机数。
	*/
	CServerAuth(LPCTSTR strGateWayIP, LPCTSTR strGatePort, LPCTSTR strAppFlag, bool bIsPlain, int nXMLVer);

	~CServerAuth();

	//获取属性值,dwLen为AttributeValue缓冲区长度，当dwLen的值小于要取的属性的长度时（如dwLen = 0），dwLen为要取属性的长度
	BOOL GetAttributeValue(LPCTSTR AttributeName, LPTSTR AttributeValue ,DWORD& dwLen);

	/**
	*函数名:GetAttributeSize
	*param:void
	*返回值:int	获取认证属性的个数
	*/
	int GetAttributeSize(void);
	/**
	*函数名:GetAttribute
	*param:int i
	*param:LPTSTR AttributeName
	*param:LPTSTR AttributeValue
	*param:LPTSTR AttributeNameSpace
    *param:long NameLength 当AttributeName为NULL时，返回需要的字符的个数
    *param:long ValueLength 当AttributeValue为NULL时，返回需要的字符个数
    *param:long SpaceLength 当AttributeNameSpace为NULL时，返回需要的字符个数
	*返回值:BOOL
	*/
	BOOL GetAttribute(int i, LPTSTR AttributeName, long& NameLength, LPTSTR AttributeValue, long& ValueLength, LPTSTR AttributeNameSpace, long& SpaceLength);

	BOOL GetMessageCode(LPTSTR strMessageCode, DWORD& dwLen);
	/*
	* pszReqInfo	[IN]	认证请求信息
	* lpszClientIP	[IN]	客户端IP地址
	* 
	* 返回 AUTH_CODE_SUCCESS 成功， 其它值为失败。
	*/
	DWORD StartAuth(LPCTSTR pszReqInfo, LPCTSTR lpszClientIP);
    DWORD GetRandOriginal( LPTSTR lpszRandOriginal, DWORD& dwLen);

	LPCTSTR GetAccessControlResult();

private:
	
	BOOL GetVersion(LPTSTR strVersion, DWORD& dwLen);
	BOOL MessageStatue(LPTSTR strMessageStatue, DWORD& dwLen);
	BOOL MessageDesc(LPTSTR strMessageDesc, DWORD& dwLen);
	BOOL GetOriginal(LPTSTR strOriginal, DWORD& dwLen);

	bool Parse_Root(IXMLDOMNode* node, SReponseInfo& reponseInfo);
    bool Parse_Reponse_Head(IXMLDOMNode* node, SReponseInfo& reponseInfo);
    bool Parse_Reponse_Head_Version(IXMLDOMNode* node, SReponseInfo& reponseInfo);
    bool Parse_Reponse_Head_ServiceType(IXMLDOMNode* node, SReponseInfo& reponseInfo);
    bool Parse_Reponse_Head_MessageStatue(IXMLDOMNode* node, SReponseInfo& reponseInfo);
    bool Parse_Reponse_Head_MessageCode(IXMLDOMNode* node, SReponseInfo& reponseInfo);
    bool Parse_Reponse_Head_MessageDesc(IXMLDOMNode* node, SReponseInfo& reponseInfo);
    bool Parse_Reponse_Body(IXMLDOMNode* node, SReponseInfo& reponseInfo);
    bool Parse_Reponse_Body_AuthResultSet(IXMLDOMNode* node, SReponseInfo& reponseInfo);
    bool Parse_Reponse_Body_AuthResultSet_AuthResult(IXMLDOMNode* node, SReponseInfo& reponseInfo);
    bool Parse_Reponse_Body_AuthResultSet_AuthResult_MessageCode(IXMLDOMNode* node, SAuthResult& reponseInfo);
    bool Parse_Reponse_Body_AuthResultSet_AuthResult_MessageDesc(IXMLDOMNode* node, SAuthResult& reponseInfo);
    bool Parse_Reponse_Body_ControlResult(IXMLDOMNode* node, SReponseInfo& reponseInfo);
    bool Parse_Reponse_Body_Attributes(IXMLDOMNode* node, SReponseInfo& reponseInfo);
    bool Parse_Reponse_Body_Attributes_Attribute(IXMLDOMNode* node, SAttributeItem& reponseInfo);
    bool Parse_Reponse_Body_Original(IXMLDOMNode* node, SReponseInfo& reponseInfo);

	DWORD UnicodeToUTF8(LPCTSTR str, string& tostr);
	DWORD UTF8ToUnicode(LPCSTR str, wstring& tostr);

    DWORD SendRequest_Plain(LPCTSTR pszReqInfo, LPCTSTR pszGateWayIP, unsigned short usGatePort, PTCHAR strReponseHttpBody, DWORD& nLength);
	DWORD SendRequest_SingleSSL(LPCTSTR pszReqInfo, LPCTSTR pszGateWayIP, unsigned short usGatePort, PTCHAR strReponseHttpBody, DWORD& nLength);
	
    void ParseReponseInfo(LPCTSTR pszPolicym, SReponseInfo& reponseInfo);

    DWORD BuildRequestXML(LPCTSTR pszReqInfo, LPCTSTR pszAppFlag, LPCTSTR lpszClientIP,LPTSTR lpszRequest);

    DWORD BuildRndRequestXML(LPCTSTR pszAppFlag,PTCHAR ptRequest);
	DWORD BuildHttpInfo(LPCSTR pszGateWayIP, unsigned short usGatePort, const string& pszRequestBody, string& bufRequest);
	//获取头结点值
	string GetHeaderValue(const string& strHttpInfo, LPCSTR pszHeadName);
	//获取Http返回状态信息
	DWORD  GetHttpReponseStatus(PTCHAR strHttpInfo);

    TCHAR* Encode(const void *pBuffer, unsigned long nBufferSize, unsigned long dwFlags = BASE64_FLAG_NONE);
    unsigned char* Decode(const TCHAR *lpszSource, unsigned long *pnResultLen);

    static unsigned long GetEncodeRequiredLength(unsigned long nSrcLen, unsigned long dwFlags = BASE64_FLAG_NONE);


    std::auto_ptr<TCHAR> m_apEncoded;
    std::auto_ptr<unsigned char> m_apDecoded;

	SReponseInfo m_structReponseInfo;	//保存XML解析后的信息，用于查询

	TCHAR m_strGateWayIP[MAX_PATH];
	TCHAR m_strGatePort[MAX_PATH];

	TCHAR m_strAppFlag[MAX_PATH];
	bool m_bIsPlain;
	int m_nXMLVer; //报文协议的版本号，与随机数生成相关

    PTCHAR  m_pszRequest ;
    DWORD   m_nAuthLength ;

    PTCHAR m_pReponseBody ;
    DWORD m_dwLen ;
};


#endif
