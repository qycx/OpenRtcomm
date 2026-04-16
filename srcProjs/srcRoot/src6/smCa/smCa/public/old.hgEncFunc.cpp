

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


//
__declspec(dllexport)  int  getSize_myHgEnc()
{
	return  sizeof(myHgEnc);

}


//
__declspec(dllexport)  int  hgEncInit(void* p0, void* p1, void* p2, myHgEnc** ppmyHgEnc)
{
	int  iErr = -1;

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


	//
	iErr = 0;
errLabel:

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

	iErr = 0;
errLabel:
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


