

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

#include    <string>
#include <sstream>

//-------------------------------------------------------------------
// Declare and initialize variables.


extern int generateRSAKeyPair(std::pair<std::string, std::string>& keyPair);
extern  std::string byteToString(const BYTE* byteArray, size_t byteArraySize);

extern QmdCryptInfoEx g_qmdCryptInfo;;
	
//-------------------------------------------------------------------
// Attempt to acquire a context and a key
// container. The context will use the default CSP
// for the RSA_FULL provider type. DwFlags is set to zero
// to attempt to open an existing key container.

 //int  initCrypt_qmd(  QMD_VAR_MIS  *  pVar,  LPCTSTR  szContainer,  LPCTSTR  szProvider,  BOOL  bNewKeySetIfNotExists,  ENC_CTX_session  *  pEncCtx  )
__declspec(dllexport)int  initCrypt_qmd(QmdCryptInfo* pVar, LPCTSTR  szContainer, LPCTSTR  szProvider, BOOL  bNewKeySetIfNotExists, ENC_CTX_session* pEncCtx)
{	

	int				iErr			=		-1;
	HCRYPTPROV		hCryptProv		=		NULL;	       // handle for a cryptographic
	BOOL			bAcquired		=		FALSE;

	HCRYPTKEY		hKey_rsa		=		NULL;
	BYTE		*	pbKeyBlob		=		NULL;
	DWORD			dwBlobLen;
	

	if (bNewKeySetIfNotExists && !pVar->crypt.uiBlobLen_publicKey1) {
		std::pair<std::string, std::string> keyPair;
		int ret = generateRSAKeyPair(keyPair);
		if (ret == 0) {

			//
#if  0
			pVar->crypt.uiBlobLen_publicKey1 = keyPair.second.length();
			memcpy(pVar->crypt.publicKeyBlob_1, keyPair.second.data(), sizeof(pVar->crypt.publicKeyBlob_1));
			
			g_qmdCryptInfo.uiBlobLen_privateKey1 = keyPair.first.length();
			memcpy(g_qmdCryptInfo.privateKeyBlob_1, keyPair.first.data(), sizeof(g_qmdCryptInfo.privateKeyBlob_1));
#endif 
			//
			pVar->crypt.uiBlobLen_publicKey1 = keyPair.second.length();
			if (pVar->crypt.uiBlobLen_publicKey1 > mycountof(pVar->crypt.publicKeyBlob_1)) {
				showInfo_open0(0, 0, _T("initCrypt_qmd err, pVar->crypt.uiBlobLen_publicKey1 too big"));
			}
			else {
				 memcpy(pVar->crypt.publicKeyBlob_1, keyPair.second.data(), pVar->crypt.uiBlobLen_publicKey1);
			}

			//
			g_qmdCryptInfo.uiBlobLen_privateKey1 = keyPair.first.length();
			if (g_qmdCryptInfo.uiBlobLen_privateKey1 > mycountof(g_qmdCryptInfo.privateKeyBlob_1)) {
				showInfo_open0(0, 0, _T("initCrypt_qmd err, g_qmdCryptInfo.uiBlobLen_privateKey too big"));
			}
			else {
				 memcpy(g_qmdCryptInfo.privateKeyBlob_1, keyPair.first.data(), g_qmdCryptInfo.uiBlobLen_privateKey1);
			}

		}
	}
	

	DWORD  dwProvType  =  get_provType();
	//
	if  (  !CryptAcquireContext(  &hCryptProv,  szContainer,  szProvider,  dwProvType,  0  )  )  {
		  //-------------------------------------------------------------------
		  // An error occurred in acquiring the context. This could mean
		  // that the key container requested does not exist. In this case,
		  // the function can be called again to attempt to create a new key 
		  // container. Error codes are defined in Winerror.h.
		DWORD  dwErr = GetLastError();
		  if  (  dwErr  !=  NTE_BAD_KEYSET  )  {
			  traceLogA(  (char*)"A cryptographic service handle could not be acquired.\n"  );
			  goto  errLabel;	  
		  }
	
		  if  (  !bNewKeySetIfNotExists  )  goto  errLabel;

		  {
			  CQySyncObj	syncObj;
			  if  (  syncObj.sync(  CONST_mutexName_syncKey_qmc  )  )  goto  errLabel;			//  这里的同步是因为CRYPT_NEWKEYSET 不是thread safe

			  if  (  !CryptAcquireContext(  &hCryptProv,  szContainer,  szProvider,  dwProvType,  CRYPT_NEWKEYSET  )  )  {     
      			    printf("Could not create a new key container.\n");
					goto  errLabel;                    
			  }	
			  
		  }
		  
	} // End of else.

	bAcquired  =  TRUE;

	//-------------------------------------------------------------------
	// A cryptographic context and a key container are available. Perform
	// any functions that require a cryptographic provider handle.


	//  下面取得公钥

	if  (  !CryptGetUserKey(  hCryptProv,  AT_KEYEXCHANGE,  &hKey_rsa  )  )  {
		if  (  GetLastError(  )  != NTE_NO_KEY  )  goto  errLabel;

		//  Check to determine whether an exchange key needs to be created.
		//  Create a key exchange key pair.
		{
			CQySyncObj	syncObj;
			if  (  syncObj.sync(  CONST_mutexName_syncKey_qmc  )  )  goto  errLabel;		//  这里的同步是因为CryptGenKey 不是thread safe

			traceLogA(  (char*)"The exchange key dose not exist,Attempting to create an exchange key pair. \n"  );
			if  (  !CryptGenKey(  hCryptProv,	AT_KEYEXCHANGE,  0,  &hKey_rsa  )  )   goto  errLabel;
			traceLogA(  (char*)" Exchange key pair created.\n"  );
		}
	}

	//
	int		len;len = 0;
	DWORD	dwBlockLen_encrypt; dwBlockLen_encrypt = 0;
	DWORD	dwBlockLen_decrypt; dwBlockLen_decrypt = 0;

	len  =  sizeof(  dwBlockLen_decrypt  );
	if  (  !CryptGetKeyParam(  hKey_rsa,  KP_KEYLEN,  (  BYTE  *  )&dwBlockLen_decrypt,  (  DWORD  *  )&len,  0  )  )  goto  errLabel;
	dwBlockLen_decrypt  /=  8;	
	dwBlockLen_encrypt  =  dwBlockLen_decrypt;
	if  (  dwBlockLen_encrypt  <=  11  )  goto  errLabel;
	dwBlockLen_encrypt  -=  11;


	//  导出公钥
	if  (  !pVar->crypt.uiBlobLen_publicKey  )  {
		if  (  !bGetExportedKey(  hKey_rsa,  PUBLICKEYBLOB,  &pbKeyBlob,  &dwBlobLen  )  )  goto  errLabel;
	
		if  (  dwBlobLen  >  mycountof(  pVar->crypt.publicKeyBlob  )  )  {
			goto  errLabel;
		}


		pVar->crypt.uiBlobLen_publicKey  =  dwBlobLen;
		memcpy(  pVar->crypt.publicKeyBlob,  pbKeyBlob,  pVar->crypt.uiBlobLen_publicKey  );
	}


	if  (  pEncCtx  )  {
		pEncCtx->key_rsa.hKey  =  hKey_rsa;  hKey_rsa  =  NULL;
		pEncCtx->key_rsa.dwBlockLen_decrypt  =  dwBlockLen_decrypt;									//  密钥长度的字节数
		pEncCtx->key_rsa.dwBlockLen_encrypt  =  dwBlockLen_encrypt;

		pEncCtx->hCryptProv  =  hCryptProv;		hCryptProv  =  NULL;
	}


	iErr  =  0;

errLabel:

	if  (  pbKeyBlob  )	 free(  pbKeyBlob  );

	//  Destroy the exchange key
	if  (  hKey_rsa  )  {
		if  (  !(  CryptDestroyKey(  hKey_rsa  )  )  )  traceLogA(  (char*)(  "Error  during CryptDestroyKey ."  )  );
	}

	if  (  bAcquired  )  {  
		// When the handle is no longer needed, it must be released.
		if  (  hCryptProv  )  {
            if  (  !CryptReleaseContext(  hCryptProv,  0  )  )  traceLogA((char*)"The handle could not be released.\n");			
		}
	}

	traceLogA(  (char*)"initCrypt_qmd %s",  iErr  ?  "failed."  :  "ok"  );

	return  iErr;
}


 __declspec(dllexport) void  exitCrypt_qmd(  QmdCryptInfo  *  pVar,  ENC_CTX_session  *  pEncCtx  )
{

	if  (  !pEncCtx  )  return;

	if  (  pEncCtx->key_session.hKey  )  {
		if  (  !(  CryptDestroyKey(  pEncCtx->key_session.hKey  )  )  )  traceLogA(  (char*)(  "Error  during CryptDestroyKey ."  )  );
	}
	if  (  pEncCtx->key_rsa.hKey  )  {
		if  (  !(  CryptDestroyKey(  pEncCtx->key_rsa.hKey  )  )  )  traceLogA(  (char*)(  "Error  during CryptDestroyKey ."  )  );
	}
	if  (  pEncCtx->hCryptProv  )  {
          if  (  !CryptReleaseContext(  pEncCtx->hCryptProv,  0  )  )  traceLogA((char*)"The handle could not be released.\n");			
	}

	traceLogA(  (char*)"exitCrypt_qmd ok"  );
	return;
}



 //////////////


