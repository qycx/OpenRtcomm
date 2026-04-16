#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string.h>
#include "curl_conn.h"
#include "cJSON.h"
#define DPRINT printf
#define EPRINT printf
#import "C:\\Program Files (x86)\\BJCAClient\\CertAppEnvV3.8\\Program\\XTXAppCOM.dll" no_namespace
using namespace std;

#include    <tchar.h>
#include    "proc_ca_bjca.h"
//
#include    "tmpRegFunc_open.h"
#include <showInfo_open.h>



/*
	* 通过GET发送数据示例,delete类似
*/
string strlogindata;

void test_get_method()
{
	int nCode = -1;
	
	//初始化st_curl_params相关参数
    char* url = "10.200.0.225";
    int   format = FORMAT_JSON;
	st_curl_params curl_params;
    curl_init_params(&curl_params, url, format);
	
	
	//设置返回数据结构体
    st_curl_rec curl_rec; 
	
	
	//使用GET方式发送数据method = 0,数据格式为默认format = 0,msg发送数据为空,curl_rec为返回数据
	char* msg = NULL;
	int method = METHOD_GET;
    CURL* curl = NULL; 
    curl = curl_init_resource();
	nCode = send_msg(curl, &curl_params, msg, method, &curl_rec);
	DPRINT("get:\n%s\nsize:%d\n", curl_rec.rec, curl_rec.len);
    curl_release_resource(curl);
	
}
 
/*
	* 通过POST发送数据示例，put类似
*/
void test_post_method()
{
	int nCode = -1;
	
	//初始化st_curl_params关参数 ,数据格式为json即format = 2
    char* url = "10.200.0.225";
	char* url_path = NULL;
	int   port = 80;
	char* user = "USER";
	char* pwd = "PWD";
    int   format = FORMAT_JSON;
	st_curl_params curl_params;
    curl_init_params(&curl_params, url, format);
  
	//设置返回数据结构体
    st_curl_rec curl_rec; 
	
	//使用POST方式发送数据method = 1，msg发送数据,curl_rec为返回数据
	int method = METHOD_PUT;
	//存放要发送的数据，下列为json数据
	char* msg = "{\"UserName\":\"user\",\"UserPwd\":\"pwd\"}";
    CURL* curl = NULL; 
    curl = curl_init_resource();
	nCode = send_msg(curl, &curl_params, msg, method, &curl_rec);
	DPRINT("post:\n%s\nsize:%d\n", curl_rec.rec, curl_rec.len);
    curl_release_resource(curl);
}

 

//组织通信json数据
int buildjsondata(int nIsArray, char *strJsonData, int *nJsonDatLen, unsigned int nDataNum, ...)
{
    va_list      args;
    unsigned int i = 0;
    cJSON *jsondata = NULL;
    char *strData = NULL;
    int nDataLen = 0;
    int nRet = -1;
    char strKeyData[1024] = {0};
    char strValueData[4096] = {0};
    cJSON *JsonArray = NULL;

    jsondata = cJSON_CreateObject();
    if(jsondata == NULL) {
        return -1;
    }

    va_start(args, nDataNum);
    for (i = 0; i < nDataNum; ++i) {
        /* arg i */
        memset(strKeyData, 0, sizeof(strKeyData));
        memset(strValueData, 0, sizeof(strValueData));
        sprintf(strKeyData, va_arg(args, char *));
        sprintf(strValueData, va_arg(args, char *));
        cJSON_AddStringToObject(jsondata, strKeyData, strValueData);
    }
    va_end(args);
    if(nIsArray == 1) { //创建数组，返回[]数据
        JsonArray = cJSON_CreateArray();
        cJSON_AddItemToArray(JsonArray, jsondata);
        strData = cJSON_PrintUnformatted(JsonArray);
    } else {
        strData = cJSON_PrintUnformatted(jsondata);
    }
    if(strData == NULL) {
        goto END;
    }
    nDataLen = strlen(strData);
    if(nDataLen > *nJsonDatLen) {
        goto END;
    }
    memcpy(strJsonData, strData, nDataLen);
    *nJsonDatLen = nDataLen;
    nRet = 0;
END:
    if(strData != NULL) {
        free(strData);
        strData = NULL;
    }

    if(nIsArray == 1 && JsonArray != NULL) {
        cJSON_Delete(JsonArray);
        JsonArray = NULL;
    } else if(jsondata != NULL) {
        cJSON_Delete(jsondata);
        jsondata = NULL;
    }
    return nRet;
}

typedef struct key_Value{
    char strkey[256];
    char* strValue;
}KEY_VALUE_DATA;

int parseKeyValue(char *strRespData, KEY_VALUE_DATA* list, int num)
{
    cJSON *rootItem = NULL;
    cJSON *objectItem = NULL;
    int i = 0;
    char *tmpdata = NULL;
    int nRet = -1;

    if(list == NULL || strRespData == NULL || num <= 0) {
        return -1;
    }

    //解析json
    rootItem = cJSON_Parse(strRespData);

    //解析第一层数据值 cJSON_Parse
    for (i = 0; i < num; i++) {
        objectItem = cJSON_GetObjectItem(rootItem, list[i].strkey);
        if(objectItem == NULL || objectItem->valuestring == NULL) {
            goto END;
        }
        sprintf(list[i].strValue, objectItem->valuestring);
    }

    nRet = 0;
END:
    if(rootItem != NULL) {
        cJSON_Delete(rootItem);
    }

    if(nRet == 0) {
        return 0;
    } else {
        return -1;
    }
}
int parseJson(char* resp, char* cResdata, int *nResDataLen)
{
    int ret = 0;
    cJSON *httpRet = NULL;
    cJSON *itemstatus = NULL;
    cJSON *itemmessage = NULL;
    cJSON *itemdata = NULL;
    char *strData = NULL;
    int nDataLen = 0;

    httpRet = cJSON_Parse(resp);
    if (httpRet == NULL) {
        ret = -1;
        goto END;
    }
    itemstatus = cJSON_GetObjectItem(httpRet,"error");
    if(itemstatus == NULL){
        ret = -1;
        goto END;
    }
    if (itemstatus->valueint != 0) {
        ret = itemstatus->valueint;//服务端返回的error
        goto END;
    }

    itemdata = cJSON_GetObjectItem(httpRet,"data");
    if (itemdata == NULL) {
        ret = -1;
        goto END;
    }
    strData = cJSON_PrintUnformatted(itemdata);
    if(strData == NULL) {
        ret = -2;
        goto END;
    }
    nDataLen = strlen(strData);
    if(*nResDataLen < nDataLen) {
        ret = -3;
        goto END;
    }
    memcpy(cResdata, strData, nDataLen);
    *nResDataLen = nDataLen;
    ret = 0;

END:
    if(strData != NULL) {
        free(strData);
        strData = 0;
    }
    if(httpRet != NULL) {
        cJSON_Delete(httpRet);
    }
    return ret;
}

int genRandom(char *ucRandom, unsigned int *uiRandomLen)
{
    int ret = -1;
    char resp_data[1024] = {0};
    int resp_data_len = sizeof(resp_data);

    //初始化st_curl_params相关参数
    char* url = "https://223.70.139.221:2059/--auth-pre--/aaa/cert/random";
    
    int   format = FORMAT_JSON;
    st_curl_params curl_params;
    curl_init_params(&curl_params, url, format);

    //设置返回数据结构体
    st_curl_rec curl_rec;

    //使用GET方式发送数据method = 0,数据格式为默认format = 0,msg发送数据为空,curl_rec为返回数据
    char* msg = NULL;
    int method = METHOD_GET;
    CURL* curl = NULL; 
    curl = curl_init_resource();
    ret = send_msg(curl, &curl_params, msg, method, &curl_rec);
    if (ret == CURLE_OK) {
        ret = parseJson(curl_rec.rec, resp_data, &resp_data_len);
        if (ret == 0) {
			KEY_VALUE_DATA obj[2] = {{"Random", ucRandom},};//初始化一个数组来装json数据,拿到random
			parseKeyValue(resp_data, obj, 1);//解析json数据
            printf("resp_data:%s\n", resp_data);
        }else{
            printf("parseJson resp_data error\n");
        }
        
    }else{
        printf("send_msg failed\n");
    }



    curl_release_resource(curl);
    return ret;
}
string UTF8ToGBK(const std::string& strUTF8)  
{  
    int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);  
    WCHAR* wszGBK = new WCHAR[len+1];
    memset(wszGBK, 0, len * 2 + 2);  
    MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, wszGBK, len);  

    len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);  
    char *szGBK = new char[len + 1];  
    memset(szGBK, 0, len + 1);  
    WideCharToMultiByte(CP_ACP,0, wszGBK, -1, szGBK, len, NULL, NULL);   
    std::string strTemp(szGBK);  
    delete[]szGBK;  
    delete[]wszGBK;  
    return strTemp;  
} 
int loginAuth(char* reqData,char *ucSID,char *ucHash)//
{
    int nCode = -1;

    int ret = -1;
	char resp_data[1024] = {0};
    int resp_data_len = sizeof(resp_data);

	char cresp_data[1024] = {0};
    int cresp_data_len = sizeof(resp_data);

    //初始化st_curl_params相关参数
    char* url = "https://223.70.139.221:2059/--auth-pre--/aaa/cert/login";

    int   format = FORMAT_JSON;
    st_curl_params curl_params;
    curl_init_params(&curl_params, url, format);

    //设置返回数据结构体
    st_curl_rec curl_rec;

    //使用GET方式发送数据method = 0,数据格式为默认format = 0,msg发送数据为空,curl_rec为返回数据
    char* msg = NULL;
    int method = METHOD_POST;
    CURL* curl = NULL; 
    curl = curl_init_resource();
    nCode = send_msg(curl, &curl_params, reqData, method, &curl_rec);
    if (nCode == CURLE_OK) {
        //string strdata = UTF8ToGBK(curl_rec.rec);
		strlogindata = UTF8ToGBK(curl_rec.rec);
		ret = parseJson(curl_rec.rec, resp_data, &resp_data_len);
		KEY_VALUE_DATA obS[2] = {{"SID",ucSID},{"Hash",ucHash}};//初始化一个数组来装json数据,拿到random
		parseKeyValue(resp_data, obS, 2);//解析json数据
		//KEY_VALUE_DATA obH[1] = {{"Hash",nHash}};//初始化一个数组来装json数据,拿到random
		//parseKeyValue(cresp_data, obH, 1); 
		
        printf("loginAuth response data is %s\n", strlogindata);
    }else{
        printf("loginAuth send request error, ret = %d\n", nCode);
    }
    curl_release_resource(curl);
    return nCode;
}


int InfoAuth(char* reqData)
{
	int nCode = -1;

	//初始化st_curl_params相关参数
	char* url = "https://223.70.139.221:2059/--auth-pre--/aaa/bypass/userinfo";

	int   format = FORMAT_JSON;
	st_curl_params curl_params;
	curl_init_params(&curl_params, url, format);

	//设置返回数据结构体
	st_curl_rec curl_rec;

	//使用GET方式发送数据method = 0,数据格式为默认format = 0,msg发送数据为空,curl_rec为返回数据
	char* msg = NULL;
	int method = METHOD_POST;
	CURL* curl = NULL;
	curl = curl_init_resource();
	nCode = send_msg(curl, &curl_params, reqData, method, &curl_rec);
	if (nCode == CURLE_OK) {
		string strdata = UTF8ToGBK(curl_rec.rec);
		printf("InfoAuth response data is %s\n", strdata);
	}
	else{
		printf("InfoAuth send request error, ret = %d\n", nCode);
	}
	curl_release_resource(curl);
	return nCode;
}
/*
	* 传送数据方式，分为下列几步
	* 1.全局初始化，放在主线程中
	* 2.初始化st_curl_params相关参数
	    char url[168]     curl请求的url地址
	* 3.调用发送数据函数send_msg
	* 4.释放全局资源，放在主线程中
*/



//int main()
int _tmain(int argc, TCHAR* argv[])

{
    //
    int  iErr = -1;
    TCHAR* pT;
    TCHAR  cmdLine[1024] = _T("");
    int  ii;
    TCHAR  tBuf[256];

    for (ii = 0; ii < argc; ii++) {
        _sntprintf(cmdLine, mycountof(cmdLine), _T("%s %s"), cmdLine, argv[ii]);
    }

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
    _sntprintf(tBuf, mycountof(tBuf), _T("bjca1 cmd %d, tn %d, sys %d, devPre %s, dev %d"), gBuf.m_var.appParams.iCmd, gBuf.m_var.appParams.tn, gBuf.m_var.appParams.bSys,
        gBuf.m_var.appParams.devPrefix, gBuf.m_var.appParams.bDev);
    showInfo_open0(0, 0, tBuf);
#endif

    //
    HKEY  hKeyRoot0 = gBuf.m_var.appParams.bSys ? HKEY_LOCAL_MACHINE : HKEY_CURRENT_USER;




	 /*
        会议终端调用XTXAppcom组件
     */
	CoInitialize(NULL);
    CLSID clsid;
    HRESULT hr_xtx=CLSIDFromProgID(OLESTR("XTXAppCom.XTXApp"),&clsid);
    IXTXApp *ptr = NULL;
    hr_xtx=CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER, __uuidof(IXTXApp),(LPVOID*)&ptr);
	

	/*
		双向认证1.1  会议终端通过Socket协议请求会管，获得认证信息（服务端证书，随机数，服务端签名）
	*/

	//服务器证书（此为示例数据，实际中为1.1 socket通信的返回值）
	char* m_Cert =  "MIIEFjCCA7ygAwIBAgIKGhAAAAAAAJL31TAKBggqgRzPVQGDdTBEMQswCQYDVQQGEwJDTjENMAsGA1UECgwEQkpDQTENMAsGA1UECwwEQkpDQTEXMBUGA1UEAwwOQmVpamluZyBTTTIgQ0EwHhcNMTgwMjA2MTYwMDAwWhcNMjgwMjA3MTU1OTU5WjB3MQowCAYDVQQpDAExMQwwCgYDVQQDDANzbTIxDDAKBgNVBAsMA3NtMjENMAsGA1UECgwEQkpDQTEMMAoGA1UECgwDc20yMREwDwYDVQQHDAggQmVpSmluZzEQMA4GA1UECAwHQmVpSmluZzELMAkGA1UEBgwCQ04wWTATBgcqhkjOPQIBBggqgRzPVQGCLQNCAAToU+7s+YYPBosQocUX9PVSp0UyABsIlnuymWRnvshfrU65EOYKnfsm1H2Qe4t95F04YD3z/Ivdwr1V3myj9lY2o4ICYTCCAl0wHwYDVR0jBBgwFoAUH+bP1I/FIiqXSimKFecWyZI0xLYwHQYDVR0OBBYEFNE+FNNcrF3MuuEME+jJIwTEJILbMAsGA1UdDwQEAwIGwDCBnQYDVR0fBIGVMIGSMGCgXqBcpFowWDELMAkGA1UEBhMCQ04xDTALBgNVBAoMBEJKQ0ExDTALBgNVBAsMBEJKQ0ExFzAVBgNVBAMMDkJlaWppbmcgU00yIENBMRIwEAYDVQQDEwljYTIxY3JsNDkwLqAsoCqGKGh0dHA6Ly9jcmwuYmpjYS5vcmcuY24vY3JsL2NhMjFjcmw0OS5jcmwwEwYKKoEchu8yAgEBAQQFDANKSjEwYAYIKwYBBQUHAQEEVDBSMCMGCCsGAQUFBzABhhdPQ1NQOi8vb2NzcC5iamNhLm9yZy5jbjArBggrBgEFBQcwAoYfaHR0cDovL2NybC5iamNhLm9yZy5jbi9jYWlzc3VlcjBABgNVHSAEOTA3MDUGCSqBHIbvMgICATAoMCYGCCsGAQUFBwIBFhpodHRwOi8vd3d3LmJqY2Eub3JnLmNuL2NwczARBglghkgBhvhCAQEEBAMCAP8wEQYKKoEchu8yAgEBCAQDDAExMBMGCiqBHIbvMgIBAgIEBQwDSkoxMB8GCiqBHIbvMgIBAQ4EEQwPMTAyMDAwMDA3OTI4ODUyMBMGCiqBHIbvMgIBAQQEBQwDSkoxMB4GCiqBHIbvMgIBARcEEAwOMjI1QDIxNTAwOUpKMDEwDwYIKoEc0BQEAQQEAwwBMTATBgoqgRyG7zICAQEeBAUMAzY1NDAKBggqgRzPVQGDdQNIADBFAiBMuG7FWxnPftms9VbmcXxVXILv3XdfUP3R/KJ+FEKozwIhAPhCowM0pbAxeUYd+76nMrAxTjW7S6eom9QLztsZ2eJP";
	//服务器获随机数 （此为示例数据，实际中为1.1 socket通信的返回值）
	char* m_Random = "5m9flmZobGYkMhd1a0TCnZ+bJ4wIkhW1"; 
	//服务器对随机数的签名值 （此为示例数据，实际中为1.1 socket通信的返回值）
	char* m_SignRandom = "MEQCIEOK3QykBO0n5mDd3lRL7N1J9WaZROMjOBYMWxcbAa99AiBIcFPu7h5WTBFLA1budxV0IbJZqF9Q4YJgLtTvNLe2VA==" ;



	/*
		双向认证1.3 验证服务端返回的认证信息，获取Ukey列表，并让证书（CertId）对随机数做签名
   */


    //////////////////////////
    //
    char serv_random[2048] = { 0 };
    char serv_cert[4096] = { 0 };
    char serv_signData[2048] = { 0 };

    //
    TCHAR  cfgName_serv_random[128];
    _sntprintf(cfgName_serv_random, mycountof(cfgName_serv_random), _T("%s%d"), _T(CONST_regValName_serv_random_prefix), gBuf.m_var.appParams.tn);
    TCHAR  cfgName_serv_cert[128];
    _sntprintf(cfgName_serv_cert, mycountof(cfgName_serv_cert), _T("%s%d"), _T(CONST_regValName_serv_cert_prefix), gBuf.m_var.appParams.tn);
    TCHAR  cfgName_serv_signData[128];
    _sntprintf(cfgName_serv_signData, mycountof(cfgName_serv_signData), _T("%s%d"), _T(CONST_regValName_serv_signData_prefix), gBuf.m_var.appParams.tn);


    char  buf[4096];
    unsigned  int  uiType1 = 0;
    unsigned  int  bufLen;

    //
    bufLen = sizeof(buf);
    tmpGetRegCfg_open(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_serv_random, &uiType1, buf, &bufLen);

    if (bufLen == 0 || bufLen > mycountof(serv_random) - 1)  goto  errLabel;
    memcpy(serv_random, buf, bufLen);
    serv_random[bufLen] = 0;

    _sntprintf(tBuf, mycountof(tBuf), _T("bjca.auth: read serv_random %dB, [%S]"), bufLen, serv_random);
    showInfo_open0(0, 0, tBuf);

    //
    bufLen = sizeof(buf);
    tmpGetRegCfg_open(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_serv_cert, &uiType1, buf, &bufLen);

    if (bufLen == 0 || bufLen > mycountof(serv_cert) - 1)  goto  errLabel;
    memcpy(serv_cert, buf, bufLen);
    serv_cert[bufLen] = 0;

    _sntprintf(tBuf, mycountof(tBuf), _T("bjca.auth: read serv_cert %dB, [%S]"), bufLen, serv_cert);
    showInfo_open0(0, 0, tBuf);

    //
    bufLen = sizeof(buf);
    tmpGetRegCfg_open(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_serv_signData, &uiType1, buf, &bufLen);

    if (bufLen == 0 || bufLen > mycountof(serv_signData) - 1)  goto  errLabel;
    memcpy(serv_signData, buf, bufLen);
    serv_signData[bufLen] = 0;

    _sntprintf(tBuf, mycountof(tBuf), _T("bjca.auth: read serv_signData %dB, [%S]"), bufLen, serv_signData);
    showInfo_open0(0, 0, tBuf);

    //
    m_Random = serv_random;
    m_Cert = serv_cert;
    m_SignRandom = serv_signData;







	//1.3.1 验证服务端返回的认证信息（服务端证书，随机数，服务端签名）
    {
        //判断布尔型变量                                         
        bool nflag = false;
        //验签数据的函数：SOF_VerifySignedData   参数依次是：1，Base64编码的证书  2，签名原文  3,Base64编码的签名值
        nflag = ptr->SOF_VerifySignedData(m_Cert, m_Random, m_SignRandom);
        if (nflag != true) {
            printf("验签失败，结束流程");
            return 0;
        }
        else {
            printf("验签成功");
        }

        //1.3.2获取Ukey列表，并获取证书的CertId对随机数做签名

        BSTR userlist = ptr->SOF_GetUserList();
        string strlist = (_bstr_t)userlist;
        int len = strlist.length();
        char cstrlist[2060] = { 0 };
        //从userlist中获取CertId
        char CertId[60] = { 0 };
        char username[60] = { 0 };//使用者名字username

        int i;
        for (i = 0; i < len; i++) {
            cstrlist[i] = strlist[i];
        }
        cstrlist[i] = '\0';
        char* temp_p = NULL;
        char* end_p = NULL;
        char* buff_p = cstrlist;
        temp_p = strstr(buff_p, "|");
        end_p = strstr(buff_p, "&");
        memcpy(CertId, temp_p + 2, (end_p)-(temp_p + 2));
        //以上为获取CerId的分割函数

        Certs  certs;
        parseCertList(cstrlist, &certs);

        //
        if (gBuf.m_var.appParams.devPrefix[0]) {
            string str_devPrefix = (_bstr_t)gBuf.m_var.appParams.devPrefix;
            char  buf_devPrefix[256];
            len = str_devPrefix.length();
            for (i = 0; i < len; i++) {
                buf_devPrefix[i] = str_devPrefix[i];
            }
            buf_devPrefix[i] = 0;


            int j;
            for (j = 0; j < certs.usCnt; j++) {
                if (gBuf.m_var.appParams.bDev) {
                    if (!gBuf.m_var.appParams.bFullCmp) {
                        if (!strnicmp(certs.mems[j].usrName, buf_devPrefix, strlen(buf_devPrefix))) {
                            break;
                        }
                    }
                    else {
                        if (!stricmp(certs.mems[j].usrName, buf_devPrefix)) {
                            break;
                        }
                    }
                    //
                }
                else {
                    //
                    if (strnicmp(certs.mems[j].usrName, buf_devPrefix, strlen(buf_devPrefix))) {
                        break;
                    }
                }
            }
            if (j == certs.usCnt) {
                goto  errLabel;
            }
            _snprintf(CertId, mycountof(CertId), "%s", certs.mems[j].certId);
            _snprintf(username, mycountof(username), "%s", certs.mems[j].usrName);

        }

        //1.3.3 通过CertId调用设备Ukey对随机数做签名，并获取CertId对应的签名证书(客户端证书)

        //证书口令
        char* passwdcert = "Aa970521";
        //
        passwdcert = "111111";
        //
        //校验证书口令函数（为方便签名，导出证书） 参数依次是：1，证书操作唯一标识（CertId）  2，证书口令   正确返回TRUE 失败返回FALSE
        bool flag = ptr->SOF_Login(CertId, passwdcert);
        if (flag != true) {
            printf("Cert password error,return %d\n");
            return 0;
        }

        //签名数据函数：SOF_SignData  参数依次是：1，证书操作唯一标识（CertId）  2，签名原文   返回参数：签名值（sign_data） 
        BSTR sign_data = ptr->SOF_SignData(CertId, m_Random);

        //导出用户证书函数：SOF_ExportUserCert  参数是：证书操作唯一标识（CertId）  返回参数：Base64编码的证书（UserCert）
        BSTR UserCert = ptr->SOF_ExportUserCert(CertId);

        //
        char* cUserCert = _com_util::ConvertBSTRToString(UserCert);//证书
        char* cSignData = _com_util::ConvertBSTRToString(sign_data);

        //
        {
            TCHAR  cfgName_cli_cert[128];
            _sntprintf(cfgName_cli_cert, mycountof(cfgName_cli_cert), _T("%s%d"), _T(CONST_regValName_cli_cert_prefix), gBuf.m_var.appParams.tn);
            unsigned int  uiType;
            uiType = REG_BINARY;
            tmpSetRegCfg_open(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_cli_cert, uiType, cUserCert, strlen(cUserCert));

            //
            TCHAR  cfgName_cli_signData[128];
            _sntprintf(cfgName_cli_signData, mycountof(cfgName_cli_signData), _T("%s%d"), _T(CONST_regValName_cli_signData_prefix), gBuf.m_var.appParams.tn);
            uiType = REG_BINARY;
            tmpSetRegCfg_open(hKeyRoot0, _T(CONST_rootKey_ca), cfgName_cli_signData, uiType, cSignData, strlen(cSignData));

            showInfo_open0(0, 0, _T("cli sign ok"));
        }



        /*
             接口1.3.4 将客户端认证信息（客户端证书，客户端签名）通过Socket上传到会管服务端
        */
        //应用根据私有协议自行上传



    }




	/* 以下是安全认证网关的示例 
	char* cUserCert = _com_util::ConvertBSTRToString(UserCert);//证书转换成char
    int ret = 0;
    char random[32] = {0};
    unsigned int nRandomLen = sizeof(random);
    //char* cert = "MIICzDCCAnCgAwIBAgISEAIEAyIRAhnNODlOlnCmBZbwMAwGCCqBHM9VAYN1BQAwQjELMAkGA1UEBhMCQ04xDTALBgNVBAoMBEJKQ0ExDTALBgNVBAsMBEJKQ0ExFTATBgNVBAMMDHRlc3RTZWNvbmRDQTAeFw0yMjExMDIxMTExMDFaFw0yNzExMDExMTExMDFaMFcxCzAJBgNVBAYTAkNOMQswCQYDVQQIDAJCSjELMAkGA1UEBwwCQkoxDTALBgNVBAoMBGJqY2ExDTALBgNVBAsMBEJKQ0ExEDAOBgNVBAMMB1JTQUNlcnQwWTATBgcqhkjOPQIBBggqgRzPVQGCLQNCAASRHNPkcc2zaqgIXuGQva9P/PG7LYYXv0m1W6Xx1iRr8CivHiYV0UlEq0MSXacQ2Hm+OENHXWfWB9MKpWURjwVoo4IBLTCCASkwDgYDVR0PAQH/BAQDAgbAMAkGA1UdEwQCMAAwEAYIYIZIAYb4RAIEBFhYWFgwEgYKKoEchu8yAgEBFwQEWFhYWDCBpQYDVR0fBIGdMIGaMEqgSKBGpEQwQjEVMBMGA1UEAwwMdGVzdFNlY29uZENBMQ0wCwYDVQQLDARCSkNBMQ0wCwYDVQQKDARCSkNBMQswCQYDVQQGEwJDTjBMoEqgSIZGaHR0cDovLzE5Mi4xNjguMTE4LjExOToxODA2MC9jYXdlYi9jcmwvdGVzdFNlY29uZENBL3Rlc3RTZWNvbmRDQV8wLmNybDAdBgNVHQ4EFgQUw/zv3ktU8mDYKj3e0YZvkuq4+bgwHwYDVR0jBBgwFoAUgvh1UX5pSiGb6REWUUA+SwdLbEswDAYIKoEcz1UBg3UFAANIADBFAiBfZxdk89Y23znAAfcVHI1njRylpurdr62qh38/PCrTvQIhAIpPii44K9aYgfgJjexkFi+bF0JzktUVMhmBByWUFriP";
	//char* rhash = "NpRZLwa4Ee/t98QdHwURkXz6hpnfsYURAk9+KxH53/c=";
    char loginMsg[1024] = {0};
    //全局资源初始化，放在主线程
    ret = curl_global_init_resource();  
    //请求随机数
    memset(random, 0, nRandomLen);
    ret = genRandom(random, &nRandomLen);
    if (ret != CURLE_OK) {
        printf("genRandom error:return %d\n", ret);
        goto END;
    }
    //认证
	char *passwdcert = "111111";
	bool flag = ptr->SOF_Login(CertId,passwdcert);
	if (flag != true) {
		printf("Cert password error,return %d\n", ret);
		goto END;
	}
	BSTR SignRandom = ptr->SOF_SignData(CertId,random);
	char* cSignRandom = _com_util::ConvertBSTRToString(SignRandom);//签名随机数
	char nSID[50] = {0};
    char nHash[50] = {0};
	char *nappid = "30a4ca3947fa4cad929a645f530867b8";
    char send_data[2048] = {0};
    int send_data_Len = sizeof(send_data);
    ret = buildjsondata(0, send_data, &send_data_Len, 3, "Cert", cUserCert, "Random", random, "Sign", cSignRandom);
    if (ret != CURLE_OK) {
        printf("login auth:buildjsondata error,return %d\n", ret);
        goto END;
    }
    ret = loginAuth(send_data,nSID,nHash);
    if (ret != CURLE_OK) {
        printf("login auth:send https error,return %d\n", ret);
        goto END;
    }
    //获取用户信息
	int nret = 0;
	long nshid_num = 0x00000004;
	char *buff_nhash =  "Hash=";
	char *buff_SID = "&SID=";
	char *buff_appid = "&appid=";
	char new_data[512] = {0}; 
	strcat(new_data, buff_nhash); 
	strcat(new_data, nHash); 
	strcat(new_data, buff_SID);
	strcat(new_data, nSID);
	strcat(new_data, buff_appid);
	strcat(new_data, nappid);
	char *secret_data = "df0c18b98962b698218792e5fe76d170";
	//char *b_secret = "11011111000011000001100010111001100010010110001010110110100110000010000110000111100100101110010111111110011101101101000101110000";//将16进制数据化成二进制数据
	char *secret_base = "MTEwMTExMTEwMDAwMTEwMDAwMDExMDAwMTAxMTEwMDExMDAwMTAwMTAxMTAwMDEwMTAxMTAxMTAxMDAxMTAwMDAwMTAwMDAxMTAwMDAxMTExMDAxMDAxMDExMTAwMTAxMTExMTExMTAwMTExMDExMDExMDEwMDAxMDExMTAwMDA=";//做base64编码
	BSTR new_signature = ptr->SOF_HMAC(nshid_num,secret_base,new_data);
	char* cnew_signature = _com_util::ConvertBSTRToString(new_signature);
	memset(send_data, 0, send_data_Len);
	send_data_Len = sizeof(send_data);
	nret = buildjsondata(0, send_data, &send_data_Len, 4, "Hash",nHash, "SID", nSID, "appid", "30a4ca3947fa4cad929a645f530867b8", "signature", cnew_signature);
	if (nret != CURLE_OK) {
		printf("login auth: get buildjsondata error,return %d\n", nret);
		goto END;
	}
	nret = InfoAuth(send_data);
	if (nret != CURLE_OK) {
		printf("login auth:get send https error,return %d\n", nret);
		goto END;
	}
*/

    errLabel:
END:
    //全局资源清除，放在主线程中
    int ret = 0;
    ret = curl_global_cleanup_resource();




//
#ifdef  __USE_showInfo__
    showInfo_open0(0, 0, _T("bjca1 leaves"));
    //
    //exitShowInfo(&gBuf.m_var.pShowInfoStruct);
#endif


    return 0;
}