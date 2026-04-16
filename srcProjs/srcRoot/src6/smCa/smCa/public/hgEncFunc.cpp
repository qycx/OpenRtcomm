

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
#include <qmdCryptCommProc.h>
#include <hgCommProc.h>

#include "AesCrypto.h"



#include <locale> 
#include <codecvt> 
std::wstring
to_wstring(
	const std::string& str)
{
	return std::wstring_convert<
		std::codecvt_utf8<WCHAR>, WCHAR>().from_bytes(str);
}
//


#if 1
__declspec(dllexport)  int  getSize_myHgEnc()
{
	return  sizeof(myHgEnc);

}


__declspec(dllexport)  int  hgEncInit(void* p0, void* p1, void* p2, myHgEnc** ppmyHgEnc)
{
	int  iErr = -1;
	TCHAR tBuf[128];

#ifdef ENC_LOG
	_sntprintf(tBuf, mycountof(tBuf), _T("hgEncInit -------------111111111------------"));
	showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif


	if (!ppmyHgEnc)  return  -1;
	if (*ppmyHgEnc)  return  -1;

#ifdef ENC_LOG
	_sntprintf(tBuf, mycountof(tBuf), _T("hgEncInit -------------222222222------------"));
	showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif

	int  size = getSize_myHgEnc();
	if (!size)  return  -1;
	*ppmyHgEnc = (myHgEnc*)mymalloc(size);
	if (!*ppmyHgEnc)  return  -1;
	memset(*ppmyHgEnc, 0, size);

#ifdef ENC_LOG
	_sntprintf(tBuf, mycountof(tBuf), _T("hgEncInit -------------333333333------------"));
	showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif

	//
	myHgEnc* pmyHgEnc = *ppmyHgEnc;


	//pmyHgEnc->common.provider1 = provider;

	int ret = OpenSSL_add_all_algorithms();
	_sntprintf(tBuf, mycountof(tBuf), _T("hgEncInit:OpenSSL_add_all_algorithms:ret=%d"), ret);
	showInfo_open0(0, _T("hgEncFunc"), tBuf);


	ret = ERR_load_crypto_strings();
	_sntprintf(tBuf, mycountof(tBuf), _T("hgEncInit:ERR_load_crypto_strings:ret=%d"), ret);
	showInfo_open0(0, _T("hgEncFunc"), tBuf);
	
#ifdef ENC_LOG
	_sntprintf(tBuf, mycountof(tBuf), _T("hgEncInit -------------4444444444444------------"));
	showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif
	
	//
	iErr = 0;
errLabel:

	if (iErr) {
		hgEncExit(p0, p1, p2, ppmyHgEnc);
	}

	return  iErr;

}

__declspec(dllexport)  int  hgEncExit(void* p0, void* p1, void* p2, myHgEnc** ppmyHgEnc)
{
	int   iErr = -1;

	if (!ppmyHgEnc)  return 0;
	if (!*ppmyHgEnc)  return  0;
	myHgEnc* pmyHgEnc = *ppmyHgEnc;

	EVP_cleanup();
	ERR_free_strings();

	MACRO_mysafeFree(*ppmyHgEnc);

	iErr = 0;
	return  iErr;
}


__declspec(dllexport) int  getSize_myHgSessionEnc()
{
	return  sizeof(myHgSessionEnc);
}


//
//int hgSessionInit(myHgEnc  *  pmyHgEnc,  QMD_SESSION_hg  *  pSession)
__declspec(dllexport) int hgSessionInit(myHgEnc* pmyHgEnc, myHgSessionEnc** ppmyHgSessionEnc)
{
	int  iErr = -1;

	//
	if (!pmyHgEnc)  return  -1;
	if (!ppmyHgSessionEnc)  return  -1;
	if (*ppmyHgSessionEnc)  return  -1;

	int  size;
	size = getSize_myHgSessionEnc();
	*ppmyHgSessionEnc = (myHgSessionEnc*)mymalloc(size);
	if (!*ppmyHgSessionEnc)  return  -1;
	memset(*ppmyHgSessionEnc, 0, size);
	myHgSessionEnc* pSessionEnc = *ppmyHgSessionEnc;

	TCHAR tBuf[128];
#ifdef ENC_LOG
    _sntprintf(tBuf, mycountof(tBuf), _T("hgSessionInit 111111------------"));
	showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif

	int  i;
	//
#if  0
	//
	BYTE myPrivateKey[] =
	{ 1,2,3,4,5,6,7,8,9,10,
	11,12,13,14,15,16,17,18,19,20,
	21,22,23,24,25,26,27,28,29,30,
	31,32 };
	BYTE myIV[] =
	{ 1,2,3,4,5,6,7,8,9,10,
	11,12,13,14,15,16 };


	//
	int n = mycountof(myPrivateKey);
	
	for (i = 0; i < n; i++) {
		myPrivateKey[i] = (BYTE)rand();
	}
#endif
#ifdef ENC_LOG
	_sntprintf(tBuf, mycountof(tBuf), _T("hgSessionInit -------------222222------------"));
	showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif

	pSessionEnc->aesCrypto = new AES_Crypto();

	if (pSessionEnc->aesCrypto == nullptr)
		goto errLabel;
#ifdef ENC_LOG
	_sntprintf(tBuf, mycountof(tBuf), _T("hgSessionInit -------------3333333------------"));
	showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif
	try {

		static std::vector<unsigned char> key = pSessionEnc->aesCrypto->generate_key();

#if 0
		for (i = 0; i < key.size(); i++) {
			key[i] = i;
		}
#endif

		std::vector<unsigned char> iv(16);
#ifdef ENC_LOG
		_sntprintf(tBuf, mycountof(tBuf), _T("hgSessionInit -------------44444444444------------"));
		showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif
		for (i = 0; i < iv.size(); i++) {
			iv[i] = 0;
		}
#ifdef ENC_LOG
		_sntprintf(tBuf, mycountof(tBuf), _T("hgSessionInit -------------555555555555------------"));
		showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif
		if (!pSessionEnc->aesCrypto->init(key, iv)) goto errLabel;
#ifdef ENC_LOG
		_sntprintf(tBuf, mycountof(tBuf), _T("hgSessionInit -------------666666666------------"));
		showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif
		pSessionEnc->common.keySize = key.size();

		for (i = 0; i < pSessionEnc->common.keySize; i++) {
			pSessionEnc->common.rawKey[i] = key[i];
		}
#ifdef ENC_LOG
		_sntprintf(tBuf, mycountof(tBuf), _T("hgSessionInit -------------777777777------keysize=%d------"), pSessionEnc->common.keySize);
		showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif
	}
	catch (const std::exception& e) {
		goto errLabel;
	}
	

	iErr = 0;
errLabel:
	if (iErr) {
		hgSessionExit(pmyHgEnc, ppmyHgSessionEnc);
	}
	return  iErr;

}

__declspec(dllexport) int hgSessionExit(myHgEnc* pHgEnc, myHgSessionEnc** ppHgSessionEnc)
{
	if (!ppHgSessionEnc)  return  0;
	if (!*ppHgSessionEnc)  return  0;

	myHgSessionEnc* pHgSessionEnc = *ppHgSessionEnc;

	// destroy session key
	if (pHgSessionEnc->aesCrypto) {
		delete pHgSessionEnc->aesCrypto;
		pHgSessionEnc->aesCrypto = nullptr;
	}

	//
	MACRO_mysafeFree(*ppHgSessionEnc);

	//
	return  0;
}

__declspec(dllexport) int  hgEnc(QY_COMM_SESSION* pSession, myHgSessionEnc* pmyHgSessionEnc, char* input, unsigned  int  inputLen, char* output, unsigned  int* pOutputSize)
{
	int   iErr = -1;

	TCHAR tBuf[2048] = { 0 };

	static  BOOL  bReset = FALSE;

#if  0
	const char* fn = "d:\\qycx\\enc.log";
	FILE* fp = NULL;
	if (!bReset) {
		fp = fopen(fn, "w");
		if (fp) {
			fclose(fp);
		}
		bReset = TRUE;
	}
	fp = fopen(fn, "ab+");
	if (fp) {
		fwrite(input, inputLen, 1, fp);
		const char* windows_newline = "\r\n";
		fwrite(windows_newline, sizeof(char), strlen(windows_newline), fp);
		fclose(fp);
	}
#endif

#ifdef ENC_LOG
	_sntprintf(tBuf, mycountof(tBuf), _T("hgEnc ----------------111111------inputLen=%d------"), inputLen);
	showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif



#if  0
	//QMD_SESSION_hg* pSession = (QMD_SESSION_hg*)pQY_COMM_SESSION;

	CQyMcDaemon* pDaemon = g_pDaemon;
	int  iServiceId = CONST_qyServiceId_is;
	QY_SERVICE_INFO* pServiceInfo = (QY_SERVICE_INFO*)pDaemon->getSpecialPtrProperty(CONST_qyPropertyId_serviceInfo_byServiceId, (void*)iServiceId, 0);
	if (!pServiceInfo)  return  -1;
	QMD_VAR_MIS* pVar = (QMD_VAR_MIS*)pServiceInfo->pVar;
	if (!pVar)  return  -1;

	CHgDaemon* pHg = pVar->pHg;
#endif 

	// Encrypt message
#if  0
	BYTE encryptedMessage[1024];
	const char* message = "1Decryption Works -- using multiple blocks2";
	BYTE messageLen = (BYTE)strlen(message);
	memcpy(encryptedMessage, message, messageLen);
	DWORD encryptedMessageLen = messageLen;
	CryptEncrypt(sessionKey, NULL, TRUE, 0, encryptedMessage, &encryptedMessageLen, sizeof(encryptedMessage));
#endif

#ifdef ENC_LOG
	_sntprintf(tBuf, mycountof(tBuf), _T("hgEnc ----------------22222-------inputLen=%d-----"), inputLen);
	showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif


	//
	if (pSession->usLastReqCode_i == CONST_hgCmd_getKey) {

#ifdef ENC_LOG
		_sntprintf(tBuf, mycountof(tBuf), _T("hgEnc ----------------22222---aa----inputLen=%d-----"), inputLen);
		showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif

		if (*pOutputSize < inputLen)  goto  errLabel;
		memcpy(output, input, inputLen);
		*pOutputSize = inputLen;

#ifdef ENC_LOG
		_sntprintf(tBuf, mycountof(tBuf), _T("hgEnc ----------------CONST_hgCmd_getKey-------inputLen=%d-----"), inputLen);
		showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif

	}
	else {

#ifdef ENC_LOG
		_sntprintf(tBuf, mycountof(tBuf), _T("hgEnc ----------------3333333333-----inputLen=%d-------"), inputLen);
		showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif


		//
		if (*pOutputSize < inputLen)  goto  errLabel;		

#ifdef ENC_LOG
		_sntprintf(tBuf, mycountof(tBuf), _T("hgEnc ----------------4444444444------------"));
		showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif


		if (pmyHgSessionEnc->aesCrypto == nullptr) goto errLabel;

#ifdef ENC_LOG
		_sntprintf(tBuf, mycountof(tBuf), _T("hgEnc ----------------4444444444---aa---------"));
		showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif


		std::vector<unsigned char> plaintext;
		plaintext.reserve(inputLen); // 预分配空间以提高效率

		for (size_t i = 0; i < inputLen; ++i) {
			plaintext.push_back(static_cast<unsigned char>(input[i]));
		}
	
		//_sntprintf(tBuf, mycountof(tBuf), _T("hgEnc -5-:%s,%d"), to_wstring(str).c_str(), str.length());
		//showInfo_open0(0, _T("hgEncFunc"), tBuf);

		
		static  BOOL  bReset2 = FALSE;

#if  0
		std::string str(plaintext.begin(), plaintext.end());
		const char* fn2 = "d:\\qycx\\enc2.log";
		FILE* fp2 = NULL;
		if (!bReset2) {
			fp2 = fopen(fn2, "w");
			if (fp2) {
				fclose(fp2);
			}
			bReset2 = TRUE;
		}
		fp2 = fopen(fn2, "ab+");
		if (fp2) {
			fwrite(str.c_str(), str.length(), 1, fp2);
			const char* windows_newline = "\r\n";
			fwrite(windows_newline, sizeof(char), strlen(windows_newline), fp2);
			fclose(fp2);
		}
#endif


#ifdef ENC_LOG
		_sntprintf(tBuf, mycountof(tBuf), _T("hgEnc ----------------4444444444---bb---------"));
		showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif

		
		try {
			std::vector<unsigned char> outputVec = pmyHgSessionEnc->aesCrypto->encrypt(plaintext);

#ifdef ENC_LOG
			_sntprintf(tBuf, mycountof(tBuf), _T("hgEnc ----------------666666666------------"));
			showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif

			if (outputVec.size() > *pOutputSize) goto errLabel;

			//TCHAR tTmp[1024] = { 0 };

			for (int i = 0; i < outputVec.size(); ++i) {
				output[i] = outputVec[i];
				//_sntprintf(tTmp, mycountof(tTmp), _T("%s,%d"), tTmp, output[i]);
			}

			*pOutputSize = outputVec.size();

#ifdef ENC_LOG
			_sntprintf(tBuf, mycountof(tBuf), _T("hgEnc -8-:%s,%d"), tTmp, outputVec.size());
			showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif

		}
		catch (const std::exception& e) {
			_sntprintf(tBuf, mycountof(tBuf), _T("hgEnc:%s"), to_wstring(e.what()).c_str());
			showInfo_open0(0, _T("hgEncFunc"), tBuf);
			goto errLabel;
		}
	

	}

	iErr = 0;
errLabel:

	return  iErr;
}


__declspec(dllexport) int  hgDec(QY_COMM_SESSION* pSession, myHgSessionEnc* pmyHgSessionEnc, char* input, unsigned  int  inputLen, char* output, unsigned  int* pOutputSize)
{
	int  iErr = -1;

	TCHAR tBuf[256];
	TCHAR tTmp[128] = { 0 };
#ifdef ENC_LOG
	_sntprintf(tBuf, mycountof(tBuf), _T("hgDec ----------------111111------------"));
	showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif

#if  0
	QMD_SESSION_hg* pSession = (QMD_SESSION_hg*)pQY_COMM_SESSION;

	CQyMcDaemon* pDaemon = g_pDaemon;
	int  iServiceId = CONST_qyServiceId_is;
	QY_SERVICE_INFO* pServiceInfo = (QY_SERVICE_INFO*)pDaemon->getSpecialPtrProperty(CONST_qyPropertyId_serviceInfo_byServiceId, (void*)iServiceId, 0);
	if (!pServiceInfo)  return  -1;
	QMD_VAR_MIS* pVar = (QMD_VAR_MIS*)pServiceInfo->pVar;
	if (!pVar)  return  -1;

	CHgDaemon* pHg = pVar->pHg;
#endif 


#if  0
	DWORD  nn = encryptedMessageLen;
	CryptDecrypt(sessionKey, NULL, TRUE, 0, (BYTE*)&encryptedMessage, &nn);
	encryptedMessage[nn] = 0;
#endif

	std::vector<unsigned char> ciphertext(inputLen);

#ifdef ENC_LOG
	_sntprintf(tBuf, mycountof(tBuf), _T("hgDec ----------------22222222------------"));
	showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif

	if (*pOutputSize < inputLen)  goto  errLabel;
	//memcpy(output, input, inputLen);
#ifdef ENC_LOG
	_sntprintf(tBuf, mycountof(tBuf), _T("hgDec ----------------3333333333------------"));
	showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif

	if (pmyHgSessionEnc->aesCrypto == nullptr) goto errLabel;

#ifdef ENC_LOG
	_sntprintf(tBuf, mycountof(tBuf), _T("hgDec ----------------444444444------------"));
	showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif

	
	
	for (int i = 0; i < inputLen; ++i) {
		ciphertext[i] = (unsigned char)input[i];
		//_sntprintf(tTmp, mycountof(tTmp), _T("%s,%d"), tTmp, input[i]);
	}

#ifdef ENC_LOG
	_sntprintf(tBuf, mycountof(tBuf), _T("hgDec ----------------555555555555------inputLen=%d------%s"), inputLen, tTmp);
	showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif

	try {
		std::vector<unsigned char> outputVec = pmyHgSessionEnc->aesCrypto->decrypt(ciphertext);
#ifdef ENC_LOG
		_sntprintf(tBuf, mycountof(tBuf), _T("hgDec ----------------decrypt-----inputLen=%d----outputLen=%d---"), inputLen, outputVec.size());
		showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif

		if (outputVec.size() > *pOutputSize) goto errLabel;

#ifdef ENC_LOG
		_sntprintf(tBuf, mycountof(tBuf), _T("hgDec ----------------6666666------------"));
		showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif

		for (int i = 0; i < outputVec.size(); ++i) {
			output[i] = outputVec[i];
		}

		*pOutputSize = outputVec.size();
		
#ifdef ENC_LOG
		std::string str(outputVec.begin(), outputVec.end());
		_sntprintf(tBuf, mycountof(tBuf), _T("hgDec-7-:%s"), to_wstring(str).c_str());
		showInfo_open0(0, _T("hgEncFunc"), tBuf);
#endif
	}
	catch (const std::exception& e) {
		_sntprintf(tBuf, mycountof(tBuf), _T("hgDec:%s"), to_wstring(e.what()).c_str());
		showInfo_open0(0, _T("hgEncFunc"), tBuf);
		
		goto errLabel;
	}

	iErr = 0;
errLabel:
	return  iErr;
}

#else

__declspec(dllexport)  int  getSize_myHgEnc()
{
	return  sizeof(myHgEnc);

}

//

__declspec(dllexport)  int  hgEncInit(void* p0, void* p1, void* p2, myHgEnc** ppmyHgEnc)
{
	int  iErr = -1;
	TCHAR tBuf[128];
	_sntprintf(tBuf, mycountof(tBuf), _T("hgEncInit ----------------1111111111111------------"));
	showInfo_open0(0, _T("hgEncFunc"), tBuf);


	if (!ppmyHgEnc)  return  -1;
	if (*ppmyHgEnc)  return  -1;

	int  size = getSize_myHgEnc();
	if (!size)  return  -1;
	*ppmyHgEnc = (myHgEnc*)mymalloc(size);
	if (!*ppmyHgEnc)  return  -1;
	memset(*ppmyHgEnc, 0, size);

	//
	myHgEnc* pmyHgEnc = *ppmyHgEnc;

	//
	// init and gen key
	HCRYPTPROV provider;
	if (!CryptAcquireContext(&provider, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))  goto  errLabel;

	//
	pmyHgEnc->common.provider1 = provider;

	_sntprintf(tBuf, mycountof(tBuf), _T("hgEncInit ----------------222222222222------------"));
	showInfo_open0(0, _T("hgEncFunc"), tBuf);

	//
	iErr = 0;
errLabel:
	_sntprintf(tBuf, mycountof(tBuf), _T("hgEncInit ----------------333333333333------------"));
	showInfo_open0(0, _T("hgEncFunc"), tBuf);

	if (iErr) {
		hgEncExit(p0, p1, p2, ppmyHgEnc);
	}

	return  iErr;
}



//int  hgEncExit(  CHgDaemon  *  pHg  )
__declspec(dllexport)  int  hgEncExit(void* p0, void* p1, void* p2, myHgEnc** ppmyHgEnc)
{
	int   iErr = -1;

	if (!ppmyHgEnc)  return 0;
	if (!*ppmyHgEnc)  return  0;
	myHgEnc* pmyHgEnc = *ppmyHgEnc;

	//
	if (pmyHgEnc->common.provider1) {
		CryptReleaseContext(pmyHgEnc->common.provider1, 0);
		pmyHgEnc->common.provider1 = NULL;
	}

	//
	MACRO_mysafeFree(*ppmyHgEnc);



	iErr = 0;
	return  iErr;
}



__declspec(dllexport) int  getSize_myHgSessionEnc()
{
	return  sizeof(myHgSessionEnc);
}


//
//int hgSessionInit(myHgEnc  *  pmyHgEnc,  QMD_SESSION_hg  *  pSession)
__declspec(dllexport) int hgSessionInit(myHgEnc* pmyHgEnc, myHgSessionEnc** ppmyHgSessionEnc)
{
	int  iErr = -1;

	TCHAR tBuf[128];

	_sntprintf(tBuf, mycountof(tBuf), _T("hgSessionInit ----------------111111------------"));
	showInfo_open0(0, _T("hgEncFunc"), tBuf);

	//
	if (!pmyHgEnc)  return  -1;
	if (!ppmyHgSessionEnc)  return  -1;
	if (*ppmyHgSessionEnc)  return  -1;

	int  size;
	size = getSize_myHgSessionEnc();
	*ppmyHgSessionEnc = (myHgSessionEnc*)mymalloc(size);
	if (!*ppmyHgSessionEnc)  return  -1;
	memset(*ppmyHgSessionEnc, 0, size);
	myHgSessionEnc* pSessionEnc = *ppmyHgSessionEnc;



	//
#if  10
	//
	BYTE myPrivateKey[] =
	{ 1,2,3,4,5,6,7,8,9,10,
	11,12,13,14,15,16,17,18,19,20,
	21,22,23,24,25,26,27,28,29,30,
	31,32 };
	BYTE myIV[] =
	{ 1,2,3,4,5,6,7,8,9,10,
	11,12,13,14,15,16 };


	//
	int n = mycountof(myPrivateKey);
	int  i;
	for (i = 0; i < n; i++) {
		myPrivateKey[i] = (BYTE)rand();
	}


	//
	struct aes256keyBlob
	{
		BLOBHEADER hdr;
		DWORD keySize;
		BYTE bytes[32];
	} blob;

	memset(&blob, 0, sizeof(blob));

	blob.hdr.bType = PLAINTEXTKEYBLOB;
	blob.hdr.bVersion = CUR_BLOB_VERSION;
	blob.hdr.reserved = 0;
#if  0
	blob.hdr.aiKeyAlg = CALG_AES_128;// CALG_AES_256;
	blob.keySize = 16;// 32;
	memcpy(blob.bytes, myPrivateKey, 16);// 32);
#else
	blob.hdr.aiKeyAlg = CALG_AES_256;
	blob.keySize = 32;
	memcpy(blob.bytes, myPrivateKey, 32);
#endif


	//
	HCRYPTKEY hKey;
	hKey = NULL;
	//
	if (CryptImportKey(pmyHgEnc->common.provider1, (BYTE*)&blob, sizeof(aes256keyBlob), NULL, CRYPT_EXPORTABLE, &hKey))
	{
#if 0
		if (CryptSetKeyParam(hKey, KP_IV, myIV, 0))
		{
			//do decryption here
		}
		else {/*error*/ }

		//CryptDestroyKey(hKey);
#endif

	}
	else {/*error*/
		goto  errLabel;
	}




	// Use symmetric key encryption
	HCRYPTKEY sessionKey;
	DWORD exportKeyLen;
	BYTE iv[32];
	memset(iv, 0, sizeof(iv));
	DWORD padding; padding = PKCS5_PADDING;
	DWORD mode; mode = CRYPT_MODE_CBC;

	//CryptGenKey(provider, CALG_AES_128, CRYPT_EXPORTABLE, &sessionKey);
	sessionKey = hKey;

	//
	pSessionEnc->common.sessionKey = sessionKey;

	//
#if 10
//
	CryptSetKeyParam(sessionKey, KP_IV, iv, 0);
	CryptSetKeyParam(sessionKey, KP_PADDING, (BYTE*)&padding, 0);
	CryptSetKeyParam(sessionKey, KP_MODE, (BYTE*)&mode, 0);
#endif


	// Export key
	bool  tmpbRet;
	BYTE exportKey[1024];
	tmpbRet = CryptExportKey(sessionKey, NULL, PLAINTEXTKEYBLOB, 0, exportKey, &exportKeyLen);
	if (!tmpbRet) {
		showInfo_open0(0, 0, _T("hgSessionInit: CryptExportKey failed"));
		goto  errLabel;;
	}

	// skip PLAINTEXTKEYBLOB header
	//      { uint8_t bType, uint8_t version, uint16_t reserved, uint32_t aiKey, uint32_t keySize }
	DWORD keySize; keySize  = *((DWORD*)(exportKey + 8));
	BYTE* rawKey;  rawKey = exportKey + 12;

	//
	if (keySize > sizeof(pSessionEnc->common.rawKey))  goto  errLabel;
	memcpy(pSessionEnc->common.rawKey, rawKey, keySize);
	pSessionEnc->common.keySize = keySize;

#endif

	_sntprintf(tBuf, mycountof(tBuf), _T("hgSessionInit ----------------22222222222------------"));
	showInfo_open0(0, _T("hgEncFunc"), tBuf);

	iErr = 0;
errLabel:
	_sntprintf(tBuf, mycountof(tBuf), _T("hgSessionInit ----------------333333333333------------"));
	showInfo_open0(0, _T("hgEncFunc"), tBuf);
	if (iErr) {
		hgSessionExit(pmyHgEnc, ppmyHgSessionEnc);
	}
	return  iErr;

}


//int hgSessionExit(myHgEnc* pHgEnc, QMD_SESSION_hg* pSession)
__declspec(dllexport) int hgSessionExit(myHgEnc* pHgEnc, myHgSessionEnc** ppHgSessionEnc)
{
	if (!ppHgSessionEnc)  return  0;
	if (!*ppHgSessionEnc)  return  0;

	myHgSessionEnc* pHgSessionEnc = *ppHgSessionEnc;

	// destroy session key
	if (pHgSessionEnc->common.sessionKey) {
		CryptDestroyKey(pHgSessionEnc->common.sessionKey);
		pHgSessionEnc->common.sessionKey = NULL;
	}

	//
	MACRO_mysafeFree(*ppHgSessionEnc);

	//
	return  0;
}


//

//int  hgEnc(void* pQY_COMM_SESSION, char* input, unsigned  int  inputLen, char* output, unsigned  int* pOutputSize)
//


__declspec(dllexport) int  hgEnc(QY_COMM_SESSION* pSession, myHgSessionEnc* pmyHgSessionEnc, char* input, unsigned  int  inputLen, char* output, unsigned  int* pOutputSize)
{
	int   iErr = -1;

	TCHAR tBuf[128];

	_sntprintf(tBuf, mycountof(tBuf), _T("hgEnc ----------------111111------------"));
	showInfo_open0(0, _T("hgEncFunc"), tBuf);

#if  0
	//QMD_SESSION_hg* pSession = (QMD_SESSION_hg*)pQY_COMM_SESSION;

	CQyMcDaemon* pDaemon = g_pDaemon;
	int  iServiceId = CONST_qyServiceId_is;
	QY_SERVICE_INFO* pServiceInfo = (QY_SERVICE_INFO*)pDaemon->getSpecialPtrProperty(CONST_qyPropertyId_serviceInfo_byServiceId, (void*)iServiceId, 0);
	if (!pServiceInfo)  return  -1;
	QMD_VAR_MIS* pVar = (QMD_VAR_MIS*)pServiceInfo->pVar;
	if (!pVar)  return  -1;

	CHgDaemon* pHg = pVar->pHg;
#endif 

	// Encrypt message
#if  0
	BYTE encryptedMessage[1024];
	const char* message = "1Decryption Works -- using multiple blocks2";
	BYTE messageLen = (BYTE)strlen(message);
	memcpy(encryptedMessage, message, messageLen);
	DWORD encryptedMessageLen = messageLen;
	CryptEncrypt(sessionKey, NULL, TRUE, 0, encryptedMessage, &encryptedMessageLen, sizeof(encryptedMessage));
#endif

	//
	if (pSession->usLastReqCode_i == CONST_hgCmd_getKey) {
		if (*pOutputSize < inputLen)  goto  errLabel;
		memcpy(output, input, inputLen);
		*pOutputSize = inputLen;

		_sntprintf(tBuf, mycountof(tBuf), _T("hgEnc -----CONST_hgCmd_getKey-----------inputLen=%d------------"), inputLen);
		showInfo_open0(0, _T("hgEncFunc"), tBuf);

	}
	else {

		//
		if (*pOutputSize < inputLen)  goto  errLabel;
		memcpy(output, input, inputLen);

		//
		//CryptEncrypt(pHg->m_var.enc.sessionKey,NULL,TRUE,0,(BYTE*)data,(DWORD*)piDataLen, (DWORD)*piDataLen  );
		if (!CryptEncrypt(pmyHgSessionEnc->common.sessionKey, NULL, TRUE, 0, (BYTE*)output, (DWORD*)&inputLen, (DWORD)*pOutputSize))  goto  errLabel;
		*pOutputSize = inputLen;

	}

	iErr = 0;
errLabel:

	return  iErr;
}



//__declspec(dllexport) int  hgDec(void* pQY_COMM_SESSION, char* input, unsigned  int  inputLen, char* output, unsigned  int* pOutputSize)
__declspec(dllexport) int  hgDec(QY_COMM_SESSION* pSession, myHgSessionEnc* pmyHgSessionEnc, char* input, unsigned  int  inputLen, char* output, unsigned  int* pOutputSize)
{
	int  iErr = -1;

#if  0
	QMD_SESSION_hg* pSession = (QMD_SESSION_hg*)pQY_COMM_SESSION;

	CQyMcDaemon* pDaemon = g_pDaemon;
	int  iServiceId = CONST_qyServiceId_is;
	QY_SERVICE_INFO* pServiceInfo = (QY_SERVICE_INFO*)pDaemon->getSpecialPtrProperty(CONST_qyPropertyId_serviceInfo_byServiceId, (void*)iServiceId, 0);
	if (!pServiceInfo)  return  -1;
	QMD_VAR_MIS* pVar = (QMD_VAR_MIS*)pServiceInfo->pVar;
	if (!pVar)  return  -1;

	CHgDaemon* pHg = pVar->pHg;
#endif 


#if  0
	DWORD  nn = encryptedMessageLen;
	CryptDecrypt(sessionKey, NULL, TRUE, 0, (BYTE*)&encryptedMessage, &nn);
	encryptedMessage[nn] = 0;
#endif

	if (*pOutputSize < inputLen)  goto  errLabel;
	memcpy(output, input, inputLen);

	//CryptDecrypt(pHg->m_var.enc.sessionKey,  NULL,  TRUE,  0,  (BYTE*)data,  (DWORD*)piDataLen  );

	if (!CryptDecrypt(pmyHgSessionEnc->common.sessionKey, NULL, TRUE, 0, (BYTE*)output, (DWORD*)&inputLen))  goto  errLabel;
	*pOutputSize = inputLen;


	iErr = 0;
errLabel:
	return  iErr;
}

#endif
