

#include	"stdafx.h"

#ifndef  __WINCE__
#include	<vfw.h>
#else
#ifdef  __TEST__
#include	<vfw.h>
#endif
#include	<mmreg.h>
#include	<MSAcm.h>
#endif

#include	<Wincrypt.h>
#include	<WinSock2.h>

#include	<tchar.h>

#include	"qmCommon.h"
#include	"qmCrypt.h"

#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/err.h>

#include <string>
#include <sstream>

extern char* base64Decode(const std::string& encoded, int& decodedLen);

std::string base64Encode(const char* buffer, int length) {
	BIO* bio, * b64;
	BUF_MEM* bufferPtr;
	b64 = BIO_new(BIO_f_base64());
	bio = BIO_new(BIO_s_mem());
	bio = BIO_push(b64, bio);
	BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
	BIO_write(bio, buffer, length);
	BIO_flush(bio);
	BIO_get_mem_ptr(bio, &bufferPtr);
	std::string encodedData(bufferPtr->data, bufferPtr->length);
	BIO_free_all(bio);
	return encodedData;
}

__declspec(dllexport)int  encryptData(ENC_CTX_session* pEncCtx, QY_BUF* pBuf_help, char* data, unsigned  int* puiDataLen, unsigned  int  uiBufLen)
{
	int				iErr = -1;
	unsigned  int	uiDataLen = 0;
	//  int				nIn;
	//  int				nOut;
	//  int				bufLen				=	0;
	//  int				len;
	//  DWORD			dwBlockLen			=	0;
	CQySyncObj			syncObj;


	if (!pEncCtx || !pBuf_help || !data || !puiDataLen)  return  -1;
	uiDataLen = *puiDataLen;

	//  2015/08/28
	if (pEncCtx->common.type == CONST_qyEncType_qwm) {

		//
		char* pBuf = data;
		int  len = uiDataLen;
		unsigned  int  uiBufSize_pBuf = uiBufLen;

		CQyMalloc				mallocObj_encBuf;
		unsigned  int			encLen = CONST_maxReqDataLen_enc_is;
		char* encBuf = mallocObj_encBuf.mallocf(encLen);
		if (!encBuf)  goto  errLabel;


		char* data = pBuf;
		int  dataLen = len;


		//												    				
		if (qnmEncData(pEncCtx, data, dataLen, encBuf, &encLen)) {
			traceLogA((char*)"qySendReqÀïqnmEncData failed.");
			goto  errLabel;
		}

		//		
		if (encLen > uiBufSize_pBuf) {
			goto  errLabel;
		}

		memcpy(pBuf, encBuf, encLen);
		len = encLen;
		//
		uiDataLen = len;

#ifdef  __DEBUG__
#if  0
		char  output[1024];
		unsigned  int  outputLen = sizeof(output);
		qnmDecData(&pSession->commEncCtx, pBuf, len, output, &outputLen);
#endif		
#endif

		//
		iErr = 0;  goto  errLabel;

	}
	else if (pEncCtx->common.type == CONST_qyEncType_rsa1) {


		if (pEncCtx->mutexName_syncCrypt_e && pEncCtx->mutexName_syncCrypt_e[0]) {
			if (syncObj.sync(pEncCtx->mutexName_syncCrypt_e))  goto  errLabel;
		}

		char* pBuf = data;
		int  len = uiDataLen;
		unsigned  int  uiBufSize_pBuf = uiBufLen;

		CQyMalloc				mallocObj_encBuf;
		unsigned  int			encLen = *puiDataLen + AES_BLOCK_SIZE;
		char* encBuf = mallocObj_encBuf.mallocf(encLen);
		if (!encBuf) {			
			goto  errLabel;
		}


		char* data = pBuf;
		int  dataLen = len;

		//		
		if (encLen > uiBufSize_pBuf) {
			showInfo_open0(0, 0, _T("encryptData: encLen > uiBufSize_pBuf"));
			goto  errLabel;
		}

		EVP_CIPHER_CTX* enCtx = EVP_CIPHER_CTX_new();
		if (!enCtx) {
			showInfo_open0(0, 0, _T("Failed to create de cipher context"));
			goto  errLabel;
		}

		//if (EVP_DecryptInit_ex(deCtx, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char*>(authInfo.sessionKeyBlob),
		//	reinterpret_cast<const unsigned char*>(myIV)) != 1) {
		if (EVP_EncryptInit_ex(enCtx, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char*>(pEncCtx->key_session.sessionKeyBlob),
			reinterpret_cast<const unsigned char*>(pEncCtx->key_session.sessionIv)) != 1) {
			EVP_CIPHER_CTX_free(enCtx);
			showInfo_open0(0, 0, _T("Failed to initialize de encryption"));
			goto  errLabel;
		}
		int lenEn;
		if (EVP_EncryptUpdate(enCtx, reinterpret_cast<unsigned char*>(encBuf), &lenEn,
			reinterpret_cast<const unsigned char*>(data), dataLen) != 1) {
			EVP_CIPHER_CTX_free(enCtx);

			showInfo_open0(0, 0, _T("encryptData:EVP_EncryptUpdate failed"));
			goto  errLabel;
		}

		encLen = lenEn;
		if (EVP_EncryptFinal_ex(enCtx, reinterpret_cast<unsigned char*>(encBuf) + lenEn, &lenEn) != 1) {
			EVP_CIPHER_CTX_free(enCtx);
			showInfo_open0(0, 0, _T("encryptData:EVP_EncryptFinal_ex failed"));
			goto  errLabel;
		}

		EVP_CIPHER_CTX_free(enCtx);
		

		encLen += lenEn;		

		memcpy(pBuf, encBuf, encLen);		
		uiDataLen = encLen;

	
		//
		iErr = 0;  goto  errLabel;

	}

	//
	if (!pEncCtx->common.type
		|| !uiDataLen
		|| !pEncCtx->key_session.hKey)
	{					//  没有加密，所以不需要解密
		iErr = 0;  goto  errLabel;
	}

	//  2015/08/28
	if (pEncCtx->common.type != CONST_qyEncType_rsa) {
		goto  errLabel;
	}


	//
	if (pEncCtx->mutexName_syncCrypt_e && pEncCtx->mutexName_syncCrypt_e[0]) {
		if (syncObj.sync(pEncCtx->mutexName_syncCrypt_e))  goto  errLabel;
	}

	/*
	// Determine the number of bytes to encrypt at a time.
	// This must be a multiple of ENCRYPT_BLOCK_SIZE.
	// ENCRYPT_BLOCK_SIZE is set by a #define statement.

	dwBlockLen = 1000 - 1000 % ENCRYPT_BLOCK_SIZE;

	//-------------------------------------------------------------------
	// Determine the block size. If a block cipher is used,
	// it must have room for an extra block.

	if(ENCRYPT_BLOCK_SIZE > 1)
		dwBufferLen = dwBlockLen + ENCRYPT_BLOCK_SIZE;
	else
		dwBufferLen = dwBlockLen;
	*/

	if (!pEncCtx->key_session.dwBlockLen_encrypt) {	//  流式加密的情况

		/*
		dwBlockLen  =  1000;

		for  (  nIn  =  0,  nOut  =  0;  nIn  <  (  int  )uiDataLen  &&  nOut  <=  (  int  )uiBufLen;  )  {
			 len  =  min(  uiDataLen  -  nIn,  dwBlockLen  );
			 bufLen  =  len;

			 if  (  !CryptEncrypt(  pEncCtx->key_session.hKey,  0,  (  len  >=  (  int  )uiDataLen  -  nIn  ),  0,  (  BYTE  *  )data  +  nIn,  (  DWORD  *  )&bufLen,  uiBufLen  -  nOut  )  )  goto  errLabel;
			 if  (  bufLen  !=  len  )  {
				 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  _T(  "IsClient"  ),  _T(  ""  ),  _T(  ""  ),  _T(  "encryptData err. "  ),  _T(  "流式加密：输出数据和输入长度不同"  )  );
				 goto  errLabel;
			 }

			 nIn  +=  len;
			 nOut  +=  bufLen;
		}

		uiDataLen  =  nOut;
		*/

		try {
			if (!CryptEncrypt(pEncCtx->key_session.hKey, 0, TRUE, 0, (BYTE*)data, (DWORD*)&uiDataLen, uiBufLen)) {
				traceLogA((char*)"encryptData: CryptEncrypt failed.");
				goto  errLabel;
			}
		}
#ifdef  __useMfc__
		catch (CException* e) {
			e->Delete();
			traceLogA((char*)"encryptData: CryptEncrypt failed. exception caught.");
			goto  errLabel;
		}
#endif
		catch (...) {
			traceLogA((char*)"encryptData: CryptEncrypt failed. exception caught.");
			goto  errLabel;
		}

		iErr = 0;  goto  errLabel;
	}

	//  块式加密的情况
	//
#if  0
	//
	DWORD  dwBlockLen;
	DWORD  dwBufferLen;
	int  nIn, nOut;
	int len;
	int bufLen;

	//
	//char* pBuf = data;
	//if (pBuf_help->len < uiDataLen)  goto  errLabel;
	//memcpy(pBuf_help->data, data, uiDataLen);

	//
	int encryptBlockSize = pEncCtx->key_session.dwBlockLen_encrypt;//16;
	//
	dwBlockLen = uiDataLen - uiDataLen % encryptBlockSize; //pEncCtx->key_session.dwBlockLen_encrypt;
	if (encryptBlockSize > 1) {
		dwBufferLen = dwBlockLen + encryptBlockSize;// pEncCtx->key_session.dwBufferLen_encrypt;
	}
	else {
		dwBufferLen = dwBlockLen;
	}
	bool  bFinal = false;

	int nLeft = uiDataLen - dwBlockLen;
	if (nLeft > 0) {
		if (pBuf_help->len < nLeft)  goto  errLabel;
		memcpy(pBuf_help->data, data + dwBlockLen, nLeft);
	}


	for (nIn = 0, nOut = 0; ; ) {
		len = min(uiDataLen - nIn, dwBlockLen);
		if (len < dwBlockLen)bFinal = true;
		if (uiBufLen - nOut < dwBufferLen) {
			goto  errLabel;
		}
		bufLen = dwBufferLen;
		//
		int inputLen = len;
		//
		if (!CryptEncrypt(pEncCtx->key_session.hKey, 0, bFinal, 0, (BYTE*)data + nOut, (DWORD*)&len, bufLen)) {
			//
			int err = GetLastError();
			switch (err) {
			case  ERROR_INVALID_HANDLE:
			case  ERROR_INVALID_PARAMETER:
			case  NTE_BAD_DATA:
				break;
			}
			//
			goto  errLabel;
		}
		nIn += inputLen;
		nOut += len;
		//
		if (bFinal)break;
		//
		if (nLeft) {
			memcpy(data + nOut, pBuf_help->data, nLeft);
		}
		nLeft = 0;
	}

	uiDataLen = nOut;
#endif

	try {
		if (!CryptEncrypt(pEncCtx->key_session.hKey, 0, TRUE, 0, (BYTE*)data, (DWORD*)&uiDataLen, uiBufLen)) {
			traceLogA((char*)"encryptData: CryptEncrypt failed.");
			goto  errLabel;
		}
	}
#ifdef  __useMfc__
	catch (CException* e) {
		e->Delete();
		traceLogA((char*)"encryptData: CryptEncrypt failed. exception caught.");
		goto  errLabel;
	}
#endif
	catch (...) {
		traceLogA((char*)"encryptData: CryptEncrypt failed. exception caught.");
		goto  errLabel;
	}


	//
	iErr = 0;

errLabel:
	if (!iErr) {
		*puiDataLen = uiDataLen;
	}
	return  iErr;
}

__declspec(dllexport) int  decryptData(ENC_CTX_session* pEncCtx, QY_BUF* pBuf_help, char* data, unsigned  int* puiDataLen)
{
	int				iErr = -1;
	unsigned  int	uiDataLen = 0;
	//  int				nIn					=	0;
	//  int				nOut				=	0;
	//  int				len					=	0;
	//  int				tmpLen				=	0;
	//  DWORD			dwBlockLen			=	0;


	CQySyncObj			syncObj;

	if (!pEncCtx || !pBuf_help || !data || !puiDataLen)  return  -1;
	uiDataLen = *puiDataLen;

	//
	if (pEncCtx->common.type == CONST_qyEncType_qwm) {
		unsigned  int		encLen = uiDataLen;
		CQyMalloc			mallocObj_encBuf;
		char* encBuf = mallocObj_encBuf.mallocf(encLen);
		//
		memcpy(encBuf, data, uiDataLen);
		//
		if (qnmDecData(pEncCtx, encBuf, encLen, data, &uiDataLen)) {
			traceLogA((char*)"qyRecvReq qnmDecData failed");
			goto  errLabel;
		}
		//
		iErr = 0;  goto  errLabel;
	}
	else if (pEncCtx->common.type == CONST_qyEncType_rsa1) {	


		//iErr = 0;  goto  errLabel;

		if (uiDataLen <= 0) {
			showInfo_open0(0, 0, _T("decryptData: failed - uiDataLen <= 0"));
			goto  errLabel;
		}

		std::string decryptData = base64Encode(data, uiDataLen);

		if (pEncCtx->mutexName_syncCrypt_e && pEncCtx->mutexName_syncCrypt_e[0]) {
			if (syncObj.sync(pEncCtx->mutexName_syncCrypt_e))  goto  errLabel;
		}

		unsigned  int		encLen = uiDataLen;
		CQyMalloc			mallocObj_encBuf;
		char* encBuf = mallocObj_encBuf.mallocf(encLen);
		//
		memcpy(encBuf, data, uiDataLen);


		//char* decryptedText = new char[uiDataLen]; 

		EVP_CIPHER_CTX* deCtx = EVP_CIPHER_CTX_new();
		if (!deCtx) {
			showInfo_open0(0, 0, _T("Failed to create de cipher context"));
			goto  errLabel;
		}


		if (EVP_DecryptInit_ex(deCtx, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char*>(pEncCtx->key_session.sessionKeyBlob),
			reinterpret_cast<const unsigned char*>(pEncCtx->key_session.sessionIv)) != 1) {
			EVP_CIPHER_CTX_free(deCtx);
			showInfo_open0(0, 0, _T("Failed to initialize de decryption"));
			goto  errLabel;
		}

		//EVP_MAX_BLOCK_LENGTH;

		int len;
		if (EVP_DecryptUpdate(deCtx, reinterpret_cast<unsigned char*>(data), &len,
			reinterpret_cast<const unsigned char*>(encBuf), encLen) != 1) {
			EVP_CIPHER_CTX_free(deCtx);
			showInfo_open0(0, 0, _T("EVP_DecryptUpdate failed"));
			goto  errLabel;
		}

		uiDataLen = len;
		if (EVP_DecryptFinal_ex(deCtx, reinterpret_cast<unsigned char*>(data) + len, &len) != 1) {
			EVP_CIPHER_CTX_free(deCtx);
			std::string errstr = ERR_error_string(ERR_get_error(), NULL);
			errstr = "EVP_DecryptFinal_ex failed:" + errstr;

			showInfo_open0(0, 0, _T("Failed to finalize decryption"));
			goto  errLabel;
		}

		EVP_CIPHER_CTX_free(deCtx);
		uiDataLen += len;


		//
		iErr = 0;  goto  errLabel;
	}


	//
	if (!pEncCtx->common.type
		|| !uiDataLen
		|| !pEncCtx->key_session.hKey)
	{
		iErr = 0;  goto  errLabel;
	}


	//
	if (pEncCtx->mutexName_syncCrypt_e && pEncCtx->mutexName_syncCrypt_e[0]) {
		if (syncObj.sync(pEncCtx->mutexName_syncCrypt_e))  goto  errLabel;
	}

	if (!pEncCtx->key_session.dwBlockLen_decrypt) {

		/*
		dwBlockLen  =  1000;

		for  (  nIn  =  0, nOut  =  0;  nIn  <  (  int  )uiDataLen  &&  nOut  <=  (  int  )uiDataLen;  )  {
			 len  =  min(  (  int  )dwBlockLen,  uiDataLen  -  nIn  );
			 tmpLen  =  len;

			 if  (  !CryptDecrypt(  pEncCtx->key_session.hKey,  0,  (  len  >=  (  int  )(  uiDataLen  -  nIn  )  ),  0,  (  BYTE  *  )data  +  nOut,  (  DWORD  *  )&tmpLen  )  )  goto  errLabel;
			 if  (  tmpLen  !=  len  )  {
				 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  _T(  "IsClient"  ),  _T(  ""  ),  _T(  ""  ),  _T(  "decryptData err. "  ),  _T(  "流式解密：输出数据和输入长度不同"  )  );
				 goto  errLabel;
			 }

			 nIn  +=  len;
			 nOut  +=  tmpLen;
		}

		uiDataLen  =  nOut;
		*/

		try {
			if (!CryptDecrypt(pEncCtx->key_session.hKey, 0, TRUE, 0, (BYTE*)data, (DWORD*)&uiDataLen)) {
				traceLogA((char*)"decryptData: CryptDecrypt failed.");
				goto  errLabel;
			}
		}
#ifdef  __useMfc__
		catch (CException* e) {
			e->Delete();
			traceLogA((char*)"decryptData: CryptDecrypt failed. exception caught.");
			goto  errLabel;
		}
#endif
		catch (...) {
			traceLogA((char*)"decryptData: CryptDecrypt failed. exception caught.");
			goto  errLabel;
		}


		iErr = 0;  goto  errLabel;
	}

	//  块式解密
	//

	try {
		if (!CryptDecrypt(pEncCtx->key_session.hKey, 0, TRUE, 0, (BYTE*)data, (DWORD*)&uiDataLen)) {
			traceLogA((char*)"decryptData: CryptDecrypt failed.");
			goto  errLabel;
		}
	}
#ifdef  __useMfc__
	catch (CException* e) {
		e->Delete();
		traceLogA((char*)"decryptData: CryptDecrypt failed. exception caught.");
		goto  errLabel;
	}
#endif
	catch (...) {
		traceLogA((char*)"decryptData: CryptDecrypt failed. exception caught.");
		goto  errLabel;
	}


	iErr = 0;

errLabel:
	if (!iErr) {
		*puiDataLen = uiDataLen;
	}
	return  iErr;

}
