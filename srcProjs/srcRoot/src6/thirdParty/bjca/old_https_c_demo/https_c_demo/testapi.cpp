#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string.h>

#include    <tchar.h>
#include    "proc_ca_bjca.h"
//
#include    "tmpRegFunc_open.h"
//#include <showInfo_open.h>

//
#include "curl_conn.h"
#include "cJSON.h"


//
#define DPRINT printf
#define EPRINT printf
#import "C:\\Program Files (x86)\\BJCAClient\\CertAppEnvV3.8\\Program\\XTXAppCOM.dll" no_namespace
using namespace std;




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

int genRandom(char  *  caGwIp,  int caGwPort,  char *ucRandom, unsigned int *uiRandomLen)
{
    int ret = -1;
    char resp_data[1024] = {0};
    int resp_data_len = sizeof(resp_data);

    //初始化st_curl_params相关参数
    char* url = "";// "https://218.240.128.210:7075/--auth-pre--/aaa/cert/random";
    char  urlBuf[256];
    _snprintf(urlBuf, mycountof(urlBuf), "https://%s:%d/--auth-pre--/aaa/cert/random", caGwIp,caGwPort);
    url = urlBuf;
    
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

//
int loginAuth(char  *  caGwIp,  int caGwPort,  char* reqData,char *ucSID,int sidSize, char *ucHash, int ucHashSize, char * usrName, int usrNameSize)//
{
    int nCode = -1;

    int ret = -1;
	char resp_data[1024] = {0};
    int resp_data_len = sizeof(resp_data);

	char cresp_data[1024] = {0};
    int cresp_data_len = sizeof(resp_data);

    //初始化st_curl_params相关参数
    char* url = "https://218.240.128.210:7075/--auth-pre--/aaa/cert/login";
    char urlBuf[256];
    _snprintf(urlBuf, mycountof(urlBuf), "https://%s:%d/--auth-pre--/aaa/cert/login", caGwIp,caGwPort);
    url = urlBuf;

    //
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
		//KEY_VALUE_DATA obS[2] = {{"SID",ucSID},{"Hash",ucHash}};//初始化一个数组来装json数据,拿到random
        KEY_VALUE_DATA obS[3] = { {"SID",ucSID},{"Hash",ucHash},{"Username",usrName}};//初始化一个数组来装json数据,拿到random
		//parseKeyValue(resp_data, obS, 2);//解析json数据
        parseKeyValue(resp_data, obS, 3);//解析json数据

		//
		TCHAR  tBuf[128];
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "loginAuth: strlogindata [%S]"  ),  resp_data  );
		tmp_showInfo(0,0,tBuf  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "loginAuth: sid [%S], usrName[%S]"  ),  ucSID,  usrName  );
		tmp_showInfo(  0,  0,  tBuf  );


        //
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
	char* url = "https://218.240.128.210:7075/--auth-pre--/aaa/bypass/userinfo";

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


//
#ifdef  _DEBUG


#endif





//int main()
int _tmain(int argc, TCHAR* argv[])
{
    //
    int  iErr = -1;
    TCHAR* pT;
    TCHAR  cmdLine[1024]  =  _T("");
    int  ii;
    TCHAR  tBuf[256];

    for (ii = 0; ii < argc; ii++) {
        _sntprintf(cmdLine, mycountof(cmdLine), _T("%s %s"), cmdLine,  argv[ii]);
    }

    //
    parseCmdLine_ca(cmdLine, &gBuf.m_var.appParams);

    //
    char* caGwIp = "218.240.128.210";
    int caGwPort = 7075;
    //
    caGwIp = gBuf.m_var.appParams.caGwIp;
    caGwPort = gBuf.m_var.appParams.caGwPort;

    //
#ifdef  __USE_showInfo__
		//initShowInfo_cli(0, _T("syncQ_showInfo_qmc"), (char*)"127.0.0.1", &gBuf.m_var.pShowInfoStruct);
	bool  bCli  =  true;
	if  (gBuf.m_var.appParams.bSys)bCli=false;

		 //
	bool  bShowInfoInited   =  false;
	 TCHAR  *  errHintWndCls  =  _T(  "mmsmsm"  );//CONST_qnmStatusToolWndClass;
	 //if  (  initShowInfo(  0,  _T(  "syncQ_showInfo_qmd"  ),  errHintWndCls,  TRUE,  FALSE,  &mcDaemon.var.pShowInfoStruct  )  )  goto  errLabel;
	 if  (  initShowInfo_func(  0,  _T(  "syncQ_showInfo_bjca"  ),  errHintWndCls,  false, true, "127.0.0.1",  bCli,  &gBuf.m_var.pShowInfoStruct  )  )  goto  errLabel;
	 bShowInfoInited  =  TRUE;

    //
#if 0
    if (gBuf.m_var.appParams.bSys) set_who_showInfo(_T("bjca.serv"));
    else  set_who_showInfo(_T("bjca.cli"));
#endif
    tmp_set_who_showInfo(gBuf.m_var.appParams.who_showInfo);
#endif

    //
#ifdef  __USE_showInfo__
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "bjca enters, %S"  ),  gBuf.m_var.ver  );
	tmp_showInfo(0,0,tBuf);
	//
    TCHAR* cmdLine_devPrefix = _T(  "devPre" );
    if (gBuf.m_var.appParams.bFullCmp) {
        cmdLine_devPrefix = _T(  "devName"  );
    }
    _sntprintf(tBuf, mycountof(tBuf), _T("bjca cmd %d, tn %d, sys %d, %s %s, dev %d"), gBuf.m_var.appParams.iCmd, gBuf.m_var.appParams.tn,  gBuf.m_var.appParams.bSys,
                                                                                            cmdLine_devPrefix,  gBuf.m_var.appParams.devPrefix,  gBuf.m_var.appParams.bDev );
    //
    tmp_showInfo(0, 0, tBuf);
    _sntprintf(tBuf,mycountof(tBuf),_T("bjca gw %S:%d"),  gBuf.m_var.appParams.caGwIp, gBuf.m_var.appParams.caGwPort  );
    tmp_showInfo(0, 0, tBuf);

#endif

    //
    bool  bDbg = true;

    //
    HKEY  hKeyRoot0 = gBuf.m_var.appParams.bSys ? HKEY_LOCAL_MACHINE : HKEY_CURRENT_USER;

    //
    bool  bGet_sendData = false;
    bool  bGet_loginAuth = false;

    //
    switch  (  gBuf.m_var.appParams.iCmd){
            case  CONST_caCmd_login_sendData:
                  bGet_sendData = true;
                  break;
            case  CONST_caCmd_login_auth:
                  bGet_loginAuth = true;
                  break;
            case  CONST_caCmd_usrData:
                  bGet_sendData = true;
                  bGet_loginAuth = true;
                  break;
            case  CONST_caCmd_chkUsrKey:
                  bGet_sendData=true;
                  break;
            default:
                break;                
    }

    //
#ifdef  _DEBUG
    if (0) {
        bGet_sendData = true;
        bGet_loginAuth = true;
    }
#endif



    //
    if (bGet_sendData) {

        //
        if (bDbg) {
            tmp_showInfo(0, 0, _T("before CoCreateInstance IXTXApp"));
        }

        //
        CoInitialize(NULL);
        CLSID clsid;
        HRESULT hr_xtx = CLSIDFromProgID(OLESTR("XTXAppCom.XTXApp"), &clsid);
        IXTXApp* ptr = NULL;
        hr_xtx = CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER, __uuidof(IXTXApp), (LPVOID*)&ptr);
        //
        if (bDbg) {
            tmp_showInfo(0, 0, _T("after CoCreateInstance IXTXApp"));
        }
        //
#ifdef  _DEBUG
        //doTest(ptr);
#endif
        //
        //int result = ptr-> lo
        BSTR userlist = ptr->SOF_GetUserList();

        string strlist = (_bstr_t)userlist;
        int len = strlist.length();
        char cstrlist[2060] = { 0 };
        char CertId[60] = { 0 };//CerId
        char username[60] = { 0 };//使用者名字username

        if (!len) {
            tmp_showInfo(0, 0, _T("failed: userlist is empty"));
            goto  errLabel;
        }

        //
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
        //
        //
        memcpy(CertId, temp_p + 2, (end_p)-(temp_p + 2));
        memcpy(username, buff_p, temp_p - buff_p);
        //
        Certs certs;
        parseCertList(cstrlist, &certs);
        //
        if (!certs.usCnt) {
            tmp_showInfo(0, 0, _T("failed, no key"));
            goto  errLabel;
        }
        //
        if (gBuf.m_var.appParams.devPrefix[0]) {
            string str_devPrefix = (_bstr_t)gBuf.m_var.appParams.devPrefix;
            char  buf_devPrefix[256];
            len = str_devPrefix.length();
            for (i = 0; i < len; i++) {
                buf_devPrefix[i] = str_devPrefix[i];
            }
            buf_devPrefix[i] = 0;


#if 10
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
                tmp_showInfo(0, 0, _T("failed, no matched key"));
                goto  errLabel;
            }
            _snprintf(CertId, mycountof(CertId), "%s", certs.mems[j].certId);
            _snprintf(username, mycountof(username), "%s", certs.mems[j].usrName);

#endif

            //
            if (gBuf.m_var.appParams.iCmd == CONST_caCmd_chkUsrKey) {
                //

                //
                char resp[1024];
                _snprintf(resp, mycountof(resp), "%s%d", CONST_sym_bExists_usrKey, 1);

                //
                {
                    TCHAR  cfgName[128];
                    _sntprintf(cfgName, mycountof(cfgName), _T("%s%d"), _T(CONST_regValName_ca_chkUsrKeyResp_prefix), gBuf.m_var.appParams.tn);
                    unsigned int  uiType;
                    uiType = REG_BINARY;
                    tmpSetRegCfg_open(hKeyRoot0, _T(CONST_rootKey_ca), cfgName, uiType, resp, strlen(resp));
                }

                //
                iErr = 0;  goto  errLabel;
            }

        }
        //
        
        // 
        //
        BSTR UserCert = ptr->SOF_ExportUserCert(CertId);
        int hr_cert = ptr->SOF_ValidateCert(UserCert);//验证证书有效性
        switch (hr_cert)
        {
        case 0:printf("证书有效性验证成功 %d\n"); break;
        case -1:printf("证书不被信任 %d\n"); break;
        case -2:printf("超过有效期范围  %d\n"); break;
        case -3:printf("证书已作废 %d\n"); break;
        case -4:printf("证书已冻结  %d\n"); break;
        case -5:printf("证书未生效  %d\n"); break;
        case -6:printf("其他错误 %d\n"); break;
        }
        char* cUserCert = _com_util::ConvertBSTRToString(UserCert);//证书

        int ret = 0;
        char random[32] = { 0 };
        unsigned int nRandomLen = sizeof(random);
        //char* cert = "MIICzDCCAnCgAwIBAgISEAIEAyIRAhnNODlOlnCmBZbwMAwGCCqBHM9VAYN1BQAwQjELMAkGA1UEBhMCQ04xDTALBgNVBAoMBEJKQ0ExDTALBgNVBAsMBEJKQ0ExFTATBgNVBAMMDHRlc3RTZWNvbmRDQTAeFw0yMjExMDIxMTExMDFaFw0yNzExMDExMTExMDFaMFcxCzAJBgNVBAYTAkNOMQswCQYDVQQIDAJCSjELMAkGA1UEBwwCQkoxDTALBgNVBAoMBGJqY2ExDTALBgNVBAsMBEJKQ0ExEDAOBgNVBAMMB1JTQUNlcnQwWTATBgcqhkjOPQIBBggqgRzPVQGCLQNCAASRHNPkcc2zaqgIXuGQva9P/PG7LYYXv0m1W6Xx1iRr8CivHiYV0UlEq0MSXacQ2Hm+OENHXWfWB9MKpWURjwVoo4IBLTCCASkwDgYDVR0PAQH/BAQDAgbAMAkGA1UdEwQCMAAwEAYIYIZIAYb4RAIEBFhYWFgwEgYKKoEchu8yAgEBFwQEWFhYWDCBpQYDVR0fBIGdMIGaMEqgSKBGpEQwQjEVMBMGA1UEAwwMdGVzdFNlY29uZENBMQ0wCwYDVQQLDARCSkNBMQ0wCwYDVQQKDARCSkNBMQswCQYDVQQGEwJDTjBMoEqgSIZGaHR0cDovLzE5Mi4xNjguMTE4LjExOToxODA2MC9jYXdlYi9jcmwvdGVzdFNlY29uZENBL3Rlc3RTZWNvbmRDQV8wLmNybDAdBgNVHQ4EFgQUw/zv3ktU8mDYKj3e0YZvkuq4+bgwHwYDVR0jBBgwFoAUgvh1UX5pSiGb6REWUUA+SwdLbEswDAYIKoEcz1UBg3UFAANIADBFAiBfZxdk89Y23znAAfcVHI1njRylpurdr62qh38/PCrTvQIhAIpPii44K9aYgfgJjexkFi+bF0JzktUVMhmBByWUFriP";
        //char* rhash = "NpRZLwa4Ee/t98QdHwURkXz6hpnfsYURAk9+KxH53/c=";
        char loginMsg[1024] = { 0 };
        //全局资源初始化，放在主线程
        ret = curl_global_init_resource();

        //请求随机数


        memset(random, 0, nRandomLen);
        ret = genRandom(caGwIp,  caGwPort,  random, &nRandomLen);
        if (ret != CURLE_OK) {
            //
            printf("genRandom error:return %d\n", ret);
            tmp_showInfo(0, 0, _T("getRandom error"));
            //
            iErr = CONST_caRet_getRandomErr;
            //
            goto END;
        }

        //
        if (bDbg) {
            tmp_showInfo(0, 0, _T("befossre SOF_Login"));
        }

        //认证
        char* passwdcert = "111111";
        //
        if (gBuf.m_var.appParams.pwd[0]) {
            passwdcert = gBuf.m_var.appParams.pwd;
        }
        //
#ifdef  _DEBUG

        //
#endif
        //
        bool flag = ptr->SOF_Login(CertId, passwdcert);
        if (flag != true) {
            printf("Cert password error,return %d\n", ret);
            //
            tmp_showInfo(0, 0, _T("Cert password error"));
            //
            LONG l = ptr->SOF_GetPinRetryCount(CertId);
            //
            if (1) {
                //
                char resp[1024];
                _snprintf(resp, mycountof(resp), "%d", l);
                {
                    TCHAR  cfgName[128];
                    _sntprintf(cfgName, mycountof(cfgName), _T("%s%d"), _T(CONST_regValName_ca_pinRetryCountResp_prefix), gBuf.m_var.appParams.tn);
                    unsigned int  uiType;
                    uiType = REG_BINARY;
                    tmpSetRegCfg_open(hKeyRoot0, _T(CONST_rootKey_ca), cfgName, uiType, resp, strlen(resp));
                }
            }

            //
            printf("Kk");
            //
            goto END;
        }

        //
        if (bDbg) {
            tmp_showInfo(0, 0, _T("after SOF_Login, before SOF_SignData"));
        }

        //
        BSTR SignRandom = ptr->SOF_SignData(CertId, random);
        char* cSignRandom = _com_util::ConvertBSTRToString(SignRandom);//签名随机数

        //
        if (bDbg) {
            tmp_showInfo(0, 0, _T("after SOF_SignData"));
        }

        //
        char nSID[50] = { 0 };
        char nHash[50] = { 0 };
        char* nappid = "30a4ca3947fa4cad929a645f530867b8";
        char send_data[2048] = { 0 };
        int send_data_Len = sizeof(send_data);
        ret = buildjsondata(0, send_data, &send_data_Len, 3, "Cert", cUserCert, "Random", random, "Sign", cSignRandom);
        if (ret != CURLE_OK) {
            printf("login auth:buildjsondata error,return %d\n", ret);
            goto END;
        }

        //
        TCHAR  cfgName[128];
        _sntprintf(cfgName, mycountof(cfgName), _T("%s%d"), _T(CONST_regValName_ca_sendData_prefix), gBuf.m_var.appParams.tn);
        unsigned int  uiType = REG_BINARY;
        tmpSetRegCfg_open(hKeyRoot0, _T(CONST_rootKey_ca), cfgName, uiType, send_data, send_data_Len);

        //
#if  0
        char  buf[2048];
        unsigned  int  uiType1 = 0;
        unsigned  int  bufLen;

        bufLen = sizeof(buf);
        tmpGetRegCfg_open(hKeyRoot0, _T(CONST_rootKey_ca), cfgName, &uiType1, buf, &bufLen);

        if (!memcmp(buf, send_data, bufLen)) {
            int  ii;
            ii = 1;
        }
#endif

        //
#ifdef  __USE_showInfo__
        _sntprintf(tBuf, mycountof(tBuf), _T("ca_sendData %dbytes"), send_data_Len);
        tmp_showInfo(0, 0, tBuf);
#endif

    }


    int ret = 0;
    if (bGet_loginAuth) {

		//
		tmp_showInfo(  0,  0,  _T(  "bjca.auth: here"  )  );


		//
        char send_data[2048] = { 0 };
        char nSID[50] = { 0 };
        char nHash[50] = { 0 };

		//
        TCHAR  cfgName[128];
        _sntprintf(cfgName, mycountof(cfgName), _T("%s%d"), _T(CONST_regValName_ca_sendData_prefix), gBuf.m_var.appParams.tn);


		char  buf[2048];
        unsigned  int  uiType1  =  0;
        unsigned  int  bufLen;

        bufLen = sizeof(buf);
        tmpGetRegCfg_open(hKeyRoot0, _T(CONST_rootKey_ca), cfgName, &uiType1, buf, &bufLen);

		if  (  bufLen  ==  0  ||  bufLen  >  mycountof(  send_data  )  -   1  )  goto  errLabel;
		memcpy(  send_data,  buf,  bufLen  );
		send_data[bufLen]  =  0;

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "bjca.auth: read sendData %dB, [%S]"  ),  bufLen,  send_data  );
		tmp_showInfo( 0,0,tBuf  );



		char usrName[128]="";
        //
        ret = loginAuth(caGwIp,  caGwPort,  send_data, nSID, mycountof(nSID),nHash, mycountof(nHash),usrName,mycountof(usrName));
        if (ret != CURLE_OK) {
            printf("login auth:send https error,return %d\n", ret);
            goto END;
        }
		//
		if  (  !usrName[0]  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "bjca.auth: failed, sid [%S], usrName[0] is 0"  ),  nSID  );
			tmp_showInfo(  0,  0,  tBuf  );
			goto  errLabel;
		}
        //
#if  10
        {
        std::string s1 = usrName;
        std::string s2 = UTF8ToGBK(s1);
        int  ii = 0;
		//
        
        }
#endif
		//
        char resp[1024];
        _snprintf(resp, mycountof(resp), "-%s%s", CONST_sym_usr,  usrName);

        //
        {
            TCHAR  cfgName[128];
            _sntprintf(cfgName, mycountof(cfgName), _T("%s%d"), _T(CONST_regValName_ca_sendDataResp_prefix), gBuf.m_var.appParams.tn);
            unsigned int  uiType;  
            uiType = REG_BINARY;
            if  (  tmpSetRegCfg_open(hKeyRoot0, _T(CONST_rootKey_ca), cfgName, uiType, resp, strlen(resp))  )  {
				tmp_showInfo(0,0,_T(  "bjca.auth failed, tmpSetRegCfg_open failed, resp"  )  );
				goto  errLabel;
			}
			//
			_sntprintf(  tBuf,  mycountof(tBuf),  _T(  "bjca.auth: tmpSetRegCfg: %s->%S"  ),  cfgName,  resp  );
			tmp_showInfo(0,0,tBuf);
        }

		//
		tmp_showInfo(  0,0,  _T(  "bjca.auth: loginAuth ok"  )  );

    }


	//
#if  0
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
	//char *b_secret = "11011111000011000001100010111001100010010110001010110110100110000010000110000111100100101110010111111110011101101101000101110000";
	char *secret_base = "MTEwMTExMTEwMDAwMTEwMDAwMDExMDAwMTAxMTEwMDExMDAwMTAwMTAxMTAwMDEwMTAxMTAxMTAxMDAxMTAwMDAwMTAwMDAxMTAwMDAxMTExMDAxMDAxMDExMTAwMTAxMTExMTExMTAwMTExMDExMDExMDEwMDAxMDExMTAwMDA=";
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
#endif


    //
    iErr = 0;

    //
errLabel:
END:
    //全局资源清除，放在主线程中
    ret = curl_global_cleanup_resource();


    //
#ifdef  __USE_showInfo__
    tmp_showInfo(0, 0, _T("bjca leaves"));
	//
	//exitShowInfo( &gBuf.m_var.pShowInfoStruct  );
#endif

    //
    return iErr;
}


