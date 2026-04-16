

#include  "stdafx.h"

#include	<tchar.h>
#include	<WinSock2.h>
#include	<mmreg.h>
#include	<wincrypt.h>
#include	<stdlib.h>
#include	<crtdbg.h>

#include	"qmCommon.h"
#include	"qyCommProc.h"
//#include	"qmdCommon.h"
#include	"qmCrypt.h"
#include	"qmdCryptCommProc.h"
#include <cstddef>


#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <mutex>

void handleErrors() {
	ERR_print_errors_fp(stderr);
	abort();
}

std::pair<std::string, std::string> generateRSAKeyPair() {
	std::pair<std::string, std::string> keyPair;

	EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
	if (!ctx) handleErrors();

	if (EVP_PKEY_keygen_init(ctx) <= 0) handleErrors();
	if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048) <= 0) handleErrors();

	EVP_PKEY* pkey = NULL;
	if (EVP_PKEY_keygen(ctx, &pkey) <= 0) handleErrors();

	// 将私钥转换为PEM格式字符串
	BIO* privBio = BIO_new(BIO_s_mem());
	if (!PEM_write_bio_PrivateKey(privBio, pkey, NULL, NULL, 0, NULL, NULL)) {
		handleErrors();
	}

	char* privKeyBuffer;
	long privKeyLen = BIO_get_mem_data(privBio, &privKeyBuffer);
	keyPair.first.assign(privKeyBuffer, privKeyLen);

	BIO_free(privBio);

	// 将公钥转换为PEM格式字符串
	BIO* pubBio = BIO_new(BIO_s_mem());
	if (!PEM_write_bio_PUBKEY(pubBio, pkey)) {
		handleErrors();
	}

	char* pubKeyBuffer;
	long pubKeyLen = BIO_get_mem_data(pubBio, &pubKeyBuffer);
	keyPair.second.assign(pubKeyBuffer, pubKeyLen);

	BIO_free(pubBio);
	EVP_PKEY_free(pkey);
	EVP_PKEY_CTX_free(ctx);

	return keyPair;
}

int generateRSAKeyPair(std::pair<std::string, std::string>& keyPair) {
	//std::pair<std::string, std::string> keyPair;

	EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
	if (!ctx) {
		//handleErrors();
		return -1;
	}
	if (EVP_PKEY_keygen_init(ctx) <= 0) {
		//handleErrors();
		return -2;
	}
	if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048) <= 0) {
		//handleErrors();
		return -3;
	}

	EVP_PKEY* pkey = NULL;
	if (EVP_PKEY_keygen(ctx, &pkey) <= 0) {
		//handleErrors();
		return -4;
	}

	// 将私钥转换为PEM格式字符串
	BIO* privBio = BIO_new(BIO_s_mem());
	if (!PEM_write_bio_PrivateKey(privBio, pkey, NULL, NULL, 0, NULL, NULL)) {
		//handleErrors();
		return -5;
	}

	char* privKeyBuffer;
	long privKeyLen = BIO_get_mem_data(privBio, &privKeyBuffer);
	keyPair.first.assign(privKeyBuffer, privKeyLen);

	BIO_free(privBio);

	// 将公钥转换为PEM格式字符串
	BIO* pubBio = BIO_new(BIO_s_mem());
	if (!PEM_write_bio_PUBKEY(pubBio, pkey)) {
		//handleErrors();
		return -4;
	}

	char* pubKeyBuffer;
	long pubKeyLen = BIO_get_mem_data(pubBio, &pubKeyBuffer);
	keyPair.second.assign(pubKeyBuffer, pubKeyLen);

	BIO_free(pubBio);
	EVP_PKEY_free(pkey);
	EVP_PKEY_CTX_free(ctx);

	return 0;
}

std::string stripPEMHeaders(const std::string& pemKey, const std::string& header, const std::string& footer) {
	std::string key = pemKey;

	// Remove the header
	size_t headerPos = key.find(header);
	if (headerPos != std::string::npos) {
		key.erase(headerPos, header.length());
	}

	// Remove the footer
	size_t footerPos = key.find(footer);
	if (footerPos != std::string::npos) {
		key.erase(footerPos, footer.length());
	}

	// Remove newlines
	key.erase(std::remove(key.begin(), key.end(), '\n'), key.end());
	key.erase(std::remove(key.begin(), key.end(), '\r'), key.end());

	// Remove any leading/trailing whitespace
	key.erase(0, key.find_first_not_of(" \t\n\r\f\v"));
	key.erase(key.find_last_not_of(" \t\n\r\f\v") + 1);

	return key;
}

EVP_PKEY* loadPrivateKeyFromString(const std::string& keyStr) {
	BIO* bio = BIO_new_mem_buf(keyStr.c_str(), -1);
	if (!bio) {
		//handleErrors();
		return nullptr;
	}

	EVP_PKEY* pkey = PEM_read_bio_PrivateKey(bio, NULL, NULL, NULL);
	if (!pkey) {
		//handleErrors();
		return nullptr;
	}

	BIO_free(bio);
	return pkey;
}

int rsaDecrypt(const char* ciphertext, size_t ciphertextLen, std::vector<char>& plaintext, EVP_PKEY* privateKey) {
	EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(privateKey, NULL);
	if (!ctx) return -1;

	if (EVP_PKEY_decrypt_init(ctx) <= 0) {
		EVP_PKEY_CTX_free(ctx);
		return -2;
	}
	if (EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_PADDING/*RSA_PKCS1_OAEP_PADDING*/) <= 0) {
		EVP_PKEY_CTX_free(ctx);
		return -3;
	}

	size_t outLen;
	if (EVP_PKEY_decrypt(ctx, NULL, &outLen, reinterpret_cast<const unsigned char*>(ciphertext), ciphertextLen) <= 0) {
		EVP_PKEY_CTX_free(ctx);
		return -4;
	}

	plaintext.resize(outLen);
	if (EVP_PKEY_decrypt(ctx, reinterpret_cast<unsigned char*>(plaintext.data()), &outLen, reinterpret_cast<const unsigned char*>(ciphertext), ciphertextLen) <= 0) {
		EVP_PKEY_CTX_free(ctx);
		return -5;
	}

	plaintext.resize(outLen);
	EVP_PKEY_CTX_free(ctx);
	return 0;
}
//

QmdCryptInfoEx g_qmdCryptInfo;


std::string byteToString(const BYTE* byteArray, size_t byteArraySize) {
	return std::string(reinterpret_cast<const char*>(byteArray), byteArraySize);
}

std::string wideChar2string(wchar_t* pWCStrKey)
{
	std::wstring wstr(pWCStrKey);
	std::string str(wstr.length(), ' ');
	std::copy(wstr.begin(), wstr.end(), str.begin());
	return str;
}
#include <codecvt>
std::string to_string(const std::wstring& input)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.to_bytes(input);
}

char* base64Decode(const std::string& encoded, int& decodedLen) {
	BIO* bio, * b64;
	int decodeLen = encoded.length();
	char* decoded = new char[decodeLen];
	bio = BIO_new_mem_buf(encoded.data(), decodeLen);
	b64 = BIO_new(BIO_f_base64());
	bio = BIO_push(b64, bio);
	BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
	decodedLen = BIO_read(bio, decoded, decodeLen);
	BIO_free_all(bio);
	return decoded;
}


void init() {
	static bool init = false;
	if (init) {
		return;
	}

	init = true;
	OpenSSL_add_all_algorithms();
	ERR_load_crypto_strings();
}

__declspec(dllexport) int  parseAndChkAuth_mis_func(void* pSubThreadInfoParam, //QMD_SESSION* pSession
	ENC_CTX_session& commEncCtx,
	QY_COMM_SESSION& comm,
	QmdCryptInfo& qmdCryptInfo,
	unsigned  int  cfg_policy_uiCommEncCtxType,
	unsigned  int* puiChannelType, QY_COMM_AUTHINFO_MIS* pAuthInfo, AUTH_RESP_MIS* pAuthResp,
	QY_MESSENGER_INFO* pObj

)

{
	int						iErr = -1;
	MT_SOCK_SUBTHREADINFO* pSubThreadInfo = (MT_SOCK_SUBTHREADINFO*)pSubThreadInfoParam;

	init();

	/*
	CQyMcDaemon* pDaemon = (CQyMcDaemon*)pSubThreadInfo->pParentParam;
	int						iServiceId = pSubThreadInfo->iServiceId;
	QY_SERVICE_CFG* pServiceCfg = (QY_SERVICE_CFG*)pDaemon->getSpecialPtrProperty(CONST_qyPropertyId_serviceCfg, (void*)iServiceId, 0);
	if (!pServiceCfg)  return  -1;
	//
	QY_SERVICE_INFO* pServiceInfo = (QY_SERVICE_INFO*)pDaemon->getSpecialPtrProperty(CONST_qyPropertyId_serviceInfo_byServiceId, (void*)iServiceId, 0);
	if (!pServiceInfo)  return  -1;

	//
	//QM_dbFuncs* pDbFuncs = pDaemon->var.p_g_dbFuncs;	//
	//if (!pDbFuncs)  return  -1;
	//QM_dbFuncs& g_dbFuncs = *pDbFuncs;
	*/


	showInfo_open0(0, 0, _T("parseAndChkAuth_mis_func"));

	//
	QY_COMM_AUTHINFO_MIS& authInfo = *pAuthInfo;

	//
	TCHAR						sqlBuf[CONST_maxSqlBufLen + 1] = _T("");
	//  TCHAR						sqlClause[CONST_maxSqlClauseLen  +  1]		=	_T(  ""  );
	//  
	//  
	//QY_MCDAEMON_CFG* pCfg = (QY_MCDAEMON_CFG*)pSubThreadInfo->pCfg;
	//  QY_REG						reg;
	//QY_MESSENGER_INFO* pObj = (QY_MESSENGER_INFO*)pSession->pClient;
	//QMD_VAR_MIS* pVar1 = (QMD_VAR_MIS*)pServiceInfo->pVar;
	//POLICY_imAuthCond* pAuthCond = &pVar->cfg.authCond;
	int						tmpiRet;
	char* ptr;
	unsigned  int				size;
	//
	TCHAR						tBuf[128];

	//
#ifdef  __DEBUG__
	traceLogA((char*)"parseAndChkAuth_mis_func enters.");
#endif

	//
	if (!pObj)  return  -1;

	//



	//
	commEncCtx.common.type = comm.service.encType;

	switch (comm.service.encType) {
	case  CONST_qyEncType_rsa: {
		if (initCrypt_qmd(&qmdCryptInfo, CONST_cspContainer_qmd, get_DEFAULT_cspProvider(), FALSE, &commEncCtx)) {
			showInfo_open0(0, 0, _T("parseAndChkAuth_mis: initCrypt_qmd failed"));
			goto  errLabel;
		}
		commEncCtx.ucbEncInited = TRUE;

		if (!commEncCtx.key_rsa.dwBlockLen_decrypt) {
			showInfo_open0(0, 0, _T("parseAndChkAuth_mis failed: key_rsa.dwBlockLen_decrypt is 0"));
			goto  errLabel;
		}

		//  将加密的service.data解开
		QY_COMM_SERVICE_h	tmpService;
		int				dataLen = 0;
		int				nIn = 0;
		int				nOut = 0;
		int				len = 0;
		int				tmpLen = 0;

		//dataLen = min(sizeof(tmpService), comm.lenInBytes_service) - offsetof(QY_COMM_SERVICE_h, data);
		dataLen = comm.service_dataLen;
		if (dataLen <= 0) {
			showInfo_open0(0, 0, _T("parseAndChkAuth failed, dateLen <=0, line 176"));
			goto  errLabel;
		}

		memcpy(tmpService.data, comm.service.data, dataLen);
		for (nIn = 0, nOut = 0; nIn < dataLen && nOut <= sizeof(tmpService.data); ) {
			len = min((int)commEncCtx.key_rsa.dwBlockLen_decrypt, dataLen - nIn);
			tmpLen = len;

			memcpy(comm.service.data + nOut, tmpService.data + nIn, len);
			if (!CryptDecrypt(commEncCtx.key_rsa.hKey, 0, (len >= (int)(dataLen - nIn)), 0, (BYTE*)comm.service.data + nOut, (DWORD*)&tmpLen)) {
				int err = GetLastError();
				qyDisplayLastError((char*)"kk");
				//
				showInfo_open0(0, 0, _T("parseAndChkAuth_mis.CryptDecrypt failed, key_rsa .181"));
				//
				goto  errLabel;
			}
			nIn += len;
			nOut += tmpLen;
		}

	}
	break;
	case CONST_qyEncType_rsa1: {	

		if (initCrypt_qmd(&qmdCryptInfo, CONST_cspContainer_qmd, get_DEFAULT_cspProvider(), FALSE, &commEncCtx)) {
			showInfo_open0(0, 0, _T("parseAndChkAuth_mis: initCrypt_qmd failed"));
			goto  errLabel;
		}

		commEncCtx.ucbEncInited = TRUE;


		QY_COMM_SERVICE_h	tmpService;
		int				dataLen = 0;
		int				nIn = 0;
		int				nOut = 0;
		int				len = 0;
		int				tmpLen = 0;
		

		//dataLen = min(sizeof(tmpService), comm.lenInBytes_service) - offsetof(QY_COMM_SERVICE_h, data);
		dataLen = comm.service_dataLen;
		if (dataLen <= 0) {
			showInfo_open0(0, 0, _T("parseAndChkAuth failed, dateLen <=0, line 176"));
			goto  errLabel;
		}

		std::string priKey = byteToString(g_qmdCryptInfo.privateKeyBlob_1, g_qmdCryptInfo.uiBlobLen_privateKey1);

		EVP_PKEY* privateKey = loadPrivateKeyFromString(priKey);

		if (privateKey == nullptr) {
			showInfo_open0(0, 0, _T("loadPrivateKeyFromString failed"));
			goto  errLabel;
		}

		memcpy(tmpService.data, comm.service.data, dataLen);		

		std::vector<char> decryptedData;
		
		int result = rsaDecrypt(tmpService.data, dataLen, decryptedData, privateKey);

		EVP_PKEY_free(privateKey);

		if (result != 0) {			
			showInfo_open0(0, 0, _T("parseAndChkAuth_mis.CryptDecrypt failed, key_rsa .181"));
			goto  errLabel;
		}
		else {
			tmpLen = decryptedData.size();
			memset(comm.service.data, 0x00, sizeof(comm.service.data));
			memcpy(comm.service.data, decryptedData.data(), tmpLen);
		}		

	} break;
	case  CONST_qyEncType_qwm: {
		QY_ENC_CTX  encCtx;
		memset(&encCtx, 0, sizeof(encCtx));
		if (initQnmEnc(&encCtx, 0, 0, &commEncCtx)) {
			goto  errLabel;
		}
		commEncCtx.ucbEncInited = TRUE;

		//
		{
			CQyMalloc  mallocObj_enc;
			char* encBuf;
			unsigned  int			encLen = CONST_maxReqDataLen_enc_is;
			int  dataLen;

			if (!(encBuf = (char*)mallocObj_enc.mallocf(encLen)))  goto  errLabel;
			dataLen = comm.service_dataLen;
			memcpy(encBuf, comm.service.data, dataLen);

			//
			char* dataBuf;
			dataBuf = comm.service.data;
			unsigned  int   bufSize = sizeof(comm.service.data);

			//
			if (qnmDecData(&commEncCtx, encBuf, dataLen, dataBuf, &bufSize)) {
				traceLogA((char*)"qyRecvReq里qnmDecData failed");
				goto  errLabel;
			}

			//
			int  ii = 0;
		}

	}
							 break;
	default:
		break;
	}

	//  下面把authInfo解包
	//
	memset(&authInfo, 0, sizeof(authInfo));
	ptr = comm.service.data;
	size = sizeof(comm.service.data);
	if (stream2Data(&ptr, &size, filterStream_is, tmpHandler_stream2CommAuthInfo_mis, pSubThreadInfo, &authInfo)) {
		showInfo_open0(0, 0, _T("parseAndChkAuth_mis: stream2Data failed"));
		goto  errLabel;
	}

	
	if (authInfo.usAuthCmd != CONST_qnmAuthCmd_clientHello) {
		int  ii = 0;
	}

	//
	tTrim(authInfo.messengerName);		//  2011/03/22
	if (sortQwmMacs(&authInfo.macsInfo)) {
		showInfo_open0(0, 0, _T("parseAndChkAuth_mis: sortQwmMacs failed"));
		goto  errLabel;
	}

	//  下面分解authInfo  {
	//
	if (authInfo.ver[0]) {	 //  为了减少wwwQm的通信传输量，ver也不一定要每次传，故这里要先判断是否有版本号信息
		safeStrnCpy(authInfo.ver, pObj->clientVer, sizeof(pObj->clientVer));
		//		
#if  0
		pObj->lhClientVer = atol(pObj->clientVer) / 100;								//  2003/09/13
		pObj->llClientVer = atol(pObj->clientVer) % 100;								//  2005/05/23
#endif
		parse_qnmVerStr(pObj->clientVer, &pObj->shClientVer, &pObj->blClientVer, &pObj->b_mantissa_clientVer);
		//
	}
	//
	pObj->usLangId = authInfo.usLangId;
	pObj->uiDevType = authInfo.uiDevType;
	//
	safeStrnCpy(comm.clientIp, pObj->detectedIp, mycountof(pObj->detectedIp));
	safeStrnCpy(authInfo.ip, pObj->ip, mycountof(pObj->ip));

	//
	safeWcsnCpy(authInfo.messengerName, pObj->messengerName, mycountof(pObj->messengerName));	//  2007/05/29

	//  2011/02/02
	pObj->uiLogonId = authInfo.uiLogonId;

	//  2007/07/08
	if (puiChannelType)  *puiChannelType = authInfo.uiChannelType;

	//  }  分解authInfo完毕


	//  2008/06/10。根据authInfo的encType来装载密钥
	switch (comm.service.encType) {
	case  CONST_qyEncType_rsa:
		
		if (authInfo.uiBlobLen_sessionKey) {
			HCRYPTKEY  hKey;
			
			//
			switch (authInfo.usSessionEncType) {
			case  0:
				if (!CryptImportKey(commEncCtx.hCryptProv, (const  BYTE*)authInfo.sessionKeyBlob, authInfo.uiBlobLen_sessionKey, commEncCtx.key_rsa.hKey, 0, &hKey)) {
					qyDisplayLastError((char*)"Error in importing the session key \n");
					showInfo_open0(0, 0, _T("Error in importing the session key"));
					//
					goto  errLabel;
				}
				break;

			case  CONST_qyEncType_aes256: {
				//
				struct {
					BLOBHEADER	hdr;
					DWORD		len;
					BYTE		key[256];
				}				key_blob;

				memset(&key_blob, 0, sizeof(key_blob));
				key_blob.hdr.bType = PLAINTEXTKEYBLOB;
				key_blob.hdr.bVersion = CUR_BLOB_VERSION;
				key_blob.hdr.reserved = 0;
				key_blob.hdr.aiKeyAlg = CALG_AES_256;
				key_blob.len = authInfo.uiBlobLen_sessionKey;//32;

				if (authInfo.uiBlobLen_sessionKey > sizeof(key_blob.key))  goto  errLabel;
				memcpy(key_blob.key, authInfo.sessionKeyBlob, authInfo.uiBlobLen_sessionKey);

				//					   
				int len_key_blob = sizeof(key_blob);//offsetof(key_blob,key)+authInfo.uiBlobLen_sessionKey;					   
				if (!CryptImportKey(commEncCtx.hCryptProv, (const  BYTE*)&key_blob, len_key_blob, commEncCtx.key_rsa.hKey, 0, &hKey)) {
					qyDisplayLastError((char*)"Error in importing the session key \n");
					showInfo_open0(0, 0, _T("parseAndChkAuth: CryptImportKey failed"));
					goto  errLabel;
				}
				//byte myIV[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};					   
				BYTE* myIV = (BYTE*)authInfo.sessionIv;
				if (!CryptSetKeyParam(hKey, KP_IV, myIV, 0)) {
					showInfo_open0(0, 0, _T("parseAndChkAuth: CryptSetKeyParam failed"));
					goto  errLabel;
				}
				//														
			}
										break;
			default:
				showInfo_open0(0, _T(""), _T("sessionEncType err"));
				goto  errLabel;

			}

			//
			commEncCtx.key_session.hKey = hKey;

			//  设置mutexName_syncCrypt. 如果加密解密不能同时进行，把这两个名字取成一样就可以 
			_sntprintf(commEncCtx.mutexName_syncCrypt_e, mycountof(commEncCtx.mutexName_syncCrypt_e), _T("QmdCrypt%u-%u-e"), GetCurrentProcessId(), comm.uiSessionId);
			//_sntprintf(  pSession->commEncCtx.mutexName_syncCrypt_d,  mycountof(  pSession->commEncCtx.mutexName_syncCrypt_d  ),  _T(  "QmdCrypt%u-%u-d"  ),  GetCurrentProcessId(),  pSession->comm.uiSessionId  );


			//  取blockLen
			int		len = 0;
			DWORD	dwBlockLen = 0;

			len = sizeof(dwBlockLen);
			if (!CryptGetKeyParam(hKey, KP_BLOCKLEN, (BYTE*)&dwBlockLen, (DWORD*)&len, 0)) {
				showInfo_open0(0, 0, _T("parseAndChkAuth: CryptGetKeyParam failed"));
				goto  errLabel;
			}
			dwBlockLen /= 8;

			commEncCtx.key_session.dwBlockLen_encrypt = dwBlockLen;
			commEncCtx.key_session.dwBlockLen_decrypt = dwBlockLen;
		}

		//  用不到hKey_rsa了。可以关闭，以释放资源
		if (!(CryptDestroyKey(commEncCtx.key_rsa.hKey))) {
			traceLogA((char*)("Error  during CryptDestroyKey ."));
			showInfo_open0(0, 0, _T("parseAndChkAuth: CryptDestroyKey failed"));
			goto  errLabel;
		}
		commEncCtx.key_rsa.hKey = NULL;

		break;
	case CONST_qyEncType_rsa1:
		
		if (authInfo.uiBlobLen_sessionKey) {
			HCRYPTKEY  hKey;
			EVP_CIPHER_CTX* enCtx = nullptr;
			EVP_CIPHER_CTX* deCtx = nullptr;

			//std::string encodedKey = "NdlcpVagugt+IJCsCse3Cc3lHJYPEFETGmLDHD/y+kg=";
			//std::string encodedIV = "e6c81Zokxs2WWKcId/pAxQ==";

			// Base64解码
			int keyLen, ivLen;
			//char* key = base64Decode(encodedKey, keyLen);
			//char* iv = base64Decode(encodedIV, ivLen);

			//
			switch (authInfo.usSessionEncType) {
			case  0:				
				break;

			case  CONST_qyEncType_aes256: {				
			
				//byte myIV[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};					   
				//BYTE* myIV = (BYTE*)authInfo.sessionIv;				
				
				memcpy(commEncCtx.key_session.sessionKeyBlob, authInfo.sessionKeyBlob, authInfo.uiBlobLen_sessionKey);
				commEncCtx.key_session.uiBlobLen_sessionKey = authInfo.uiBlobLen_sessionKey;
				memcpy(commEncCtx.key_session.sessionIv, authInfo.sessionIv, authInfo.usLen_sessionIv);
				commEncCtx.key_session.usLen_sessionIv = authInfo.usLen_sessionIv;	
																
			}
										break;
			default:
				showInfo_open0(0, _T(""), _T("sessionEncType err"));
				goto  errLabel;

			}

		}
		
		break;
	default:
		break;
	} 
	
		

	//CONST_authType_jdzy

	//  先确定是否是helloClient, 如是，则将公钥和相关信息发回去
	if (authInfo.usAuthCmd == CONST_qnmAuthCmd_clientHello) {
		//pAuthResp->uiCommEncCtxType = cfg_policy_uiCommEncCtxType;		//  暂时不去定义这里的type
		

		if (authInfo.uiDevType == CONST_objType_android) {
			pAuthResp->uiCommEncCtxType = CONST_qyEncType_rsa1;
		}
		else {
			pAuthResp->uiCommEncCtxType = cfg_policy_uiCommEncCtxType;		//  暂时不去定义这里的type
		}
		
		std::string pubKey;
		std::string strippedPublicKey;

		switch (pAuthResp->uiCommEncCtxType) {
		case  CONST_qyEncType_rsa:
#ifdef  __DEBUG__
			if (0) {
				safeStrnCpy((char*)"Test: this is public key.", pAuthResp->publicKeyBlob, mycountof(pAuthResp->publicKeyBlob));
				pAuthResp->uiBlobLen_publicKey = strlen(pAuthResp->publicKeyBlob);
			}
#endif
			//					   
			if (qmdCryptInfo.crypt.uiBlobLen_publicKey > mycountof(pAuthResp->publicKeyBlob)) {
				_sntprintf(tBuf, mycountof(tBuf), _T("parseAndChkAuth failed, uiBlobLen_publicKey %d, too big"), qmdCryptInfo.crypt.uiBlobLen_publicKey);
				showInfo_open0(0, 0, tBuf);
				goto  errLabel;
			}			

			pAuthResp->uiBlobLen_publicKey = qmdCryptInfo.crypt.uiBlobLen_publicKey;
			memcpy(pAuthResp->publicKeyBlob, qmdCryptInfo.crypt.publicKeyBlob, pAuthResp->uiBlobLen_publicKey);
			//
			break;
		case CONST_qyEncType_rsa1:
#ifdef  __DEBUG__
			if (0) {
				safeStrnCpy((char*)"Test: this is public key.", pAuthResp->publicKeyBlob, mycountof(pAuthResp->publicKeyBlob));
				pAuthResp->uiBlobLen_publicKey = strlen(pAuthResp->publicKeyBlob);
			}
#endif
			
			pubKey = byteToString(qmdCryptInfo.crypt.publicKeyBlob_1, qmdCryptInfo.crypt.uiBlobLen_publicKey1);

			strippedPublicKey = stripPEMHeaders(pubKey, "-----BEGIN PUBLIC KEY-----", "-----END PUBLIC KEY-----");
			
			if (strippedPublicKey.length() > mycountof(pAuthResp->publicKeyBlob)) {
				_sntprintf(tBuf, mycountof(tBuf), _T("parseAndChkAuth failed, uiBlobLen_publicKey %d, too big"), qmdCryptInfo.crypt.uiBlobLen_publicKey1);
				showInfo_open0(0, 0, tBuf);
				goto  errLabel;
			}

			pAuthResp->uiBlobLen_publicKey = strippedPublicKey.length();
			memcpy(pAuthResp->publicKeyBlob, strippedPublicKey.data(), pAuthResp->uiBlobLen_publicKey);
			
			break;
		default:
			break;
		}



		iErr = CONST_qyRet_serverHello;  goto  errLabel;
	}

	iErr = 0;
errLabel:


	return  iErr;
}



