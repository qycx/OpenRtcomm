
#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"ctxQmc.h"
#include	"qmCrypt.h"


//
bool  bUseMachineKey_qmc(  CCtxQyMc  *  pQyMc  )
{
	//CCtxQyMc  *  pQyMc  =  QY_GET_GBUF(  );
	if  (  pQyMc->appParams.bUseMachineKey  )   return  true;
	return  false;
}



 // 连接csp, import服务器公钥, 生成session key, export 到blob
  int  initCrypt_qmc(  MC_VAR_isCli  *  pVar,   MIS_CNT  *  pMisCnt,  LPCTSTR  szContainer,  LPCTSTR  szProvider,  BOOL  bMachineKey,  BOOL  bNewKeySetIfNotExists,  ENC_CTX_session  *  pEncCtx  )
{
	int				iErr						=		-1;
	HCRYPTPROV		hCryptProv					=		NULL;	       // handle for a cryptographic
	BOOL			bAcquired					=		FALSE;

	HCRYPTKEY		hPublicKey					=		NULL;
	DWORD			dwBlockLen_rsa_encrypt		=		0;
	
	HCRYPTKEY		hKey_session				=		NULL;
	DWORD			dwBlockLen_session_encrypt	=		0;
	DWORD			dwBlockLen_session_decrypt	=		0;
	//
	DWORD			dwBlobLen					=		0;

	int				len							=		0;
	DWORD			dwBlockLen					=		0;

	if  (  !pEncCtx->common.type  )  return  0;


	//
	DWORD  dwFlags  =  0;

	//
	dwFlags  =  0;
	if  (  bMachineKey  )  dwFlags  |=  CRYPT_MACHINE_KEYSET;


	//
	DWORD  dwProvType = get_provType();
	//
	//
	if  (  !CryptAcquireContext(  &hCryptProv,  szContainer,  szProvider,  dwProvType,  dwFlags  )  )  {	  
		  //-------------------------------------------------------------------
		  // An error occurred in acquiring the context. This could mean
		  // that the key container requested does not exist. In this case,
		  // the function can be called again to attempt to create a new key 
		  // container. Error codes are defined in Winerror.h.
		  DWORD  dwErr;
		  TCHAR  tBuf[128];

		  if  (  (  dwErr  =  GetLastError()  )  !=  NTE_BAD_KEYSET  )  {
			  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "initCrypt_qmc: CryptAcquireContext failed, dwErr %d"  ),  dwErr  );
			  showInfo_open0(  0,  0,  tBuf  );
			  traceLogA(  (char*)  "A cryptographic service handle could not be acquired.\n"  );		
			  //
			  goto  errLabel;	  
		  }       

		  if  (  !bNewKeySetIfNotExists  )  goto  errLabel;		//  只有talking通道可以

		  {
			  CQySyncObj	syncObj;
			  if  (  syncObj.sync(  CONST_mutexName_syncKey_qmc  )  )  goto  errLabel;			//  这里的同步是因为CRYPT_NEWKEYSET 不是thread safe

			  //
			  dwFlags  =  CRYPT_NEWKEYSET;
			  if  (  bMachineKey  )  dwFlags  |=  CRYPT_MACHINE_KEYSET;
			  
			  //
			  //ERROR_ACCESS_DENIED
			  //
			  if  (  !CryptAcquireContext(  &hCryptProv,  szContainer, szProvider, dwProvType, dwFlags  )  )  {
				  //
				  dwErr  =  GetLastError(  );
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "initCrypt_qmc: CryptAcquireContext newKeyset failed, dwErr 0x%x"  ),  dwErr  );
				  showInfo_open0(  0,  0,  tBuf  );
				  traceLogA(  (char*)  "Could not create a new key container.\n"  );
				  //
				  goto  errLabel;                    
			  }
		  }
	} 

	bAcquired  =  TRUE;

	//-------------------------------------------------------------------
	// A cryptographic context and a key container are available. Perform
	// any functions that require a cryptographic provider handle.

	if  (  !CryptImportKey(  hCryptProv,  (  const  BYTE  *  )pMisCnt->commEncCtx.publicKeyBlob,  pMisCnt->commEncCtx.uiBlobLen_publicKey,  0,  0,  &hPublicKey ) )  {
		traceLogA(  (char*)  "Error 0x%08x in importing the Des key \n", GetLastError()  );  goto  errLabel;   
	}

	//  取blockLen
	len  =  sizeof(  dwBlockLen  );
	if  (  !CryptGetKeyParam(  hPublicKey,  KP_KEYLEN,  (  BYTE  *  )&dwBlockLen,  (  DWORD  *  )&len,  0  )  )  goto  errLabel;
	dwBlockLen  /=  8;
	if  (  dwBlockLen  <=  11  )  goto  errLabel;
	dwBlockLen  -=  11;

	dwBlockLen_rsa_encrypt  =  dwBlockLen;

	//  生成session key
	{
		CQySyncObj	syncObj;
		if  (  syncObj.sync(  CONST_mutexName_syncKey_qmc  )  )  goto  errLabel;		//  这里的同步是因为CryptGenKey 不是thread safe

		//
		ALG_ID algId = get_algId();// CALG_RC4;

		// Generate a session key.
		if  (  !CryptGenKey(  hCryptProv,  algId,  CRYPT_EXPORTABLE,  &hKey_session  )  )  {  
			int err = GetLastError();
			switch (err) {
			case  ERROR_INVALID_HANDLE:
			case  ERROR_INVALID_PARAMETER:
			case  NTE_BAD_ALGID:
			case  NTE_BAD_FLAGS:
			case  NTE_BAD_UID:
			case  NTE_FAIL:
			case  NTE_SILENT_CONTEXT:
				  break;
			default:
				break;
			}
			traceLogA(  (char*)"ERROR -- CryptGenKey.");  
			goto  errLabel;
		}
	}

	//  取blockLen
	len  =  sizeof(  dwBlockLen  );
	if  (  !CryptGetKeyParam(  hKey_session,  KP_BLOCKLEN,  (  BYTE  *  )&dwBlockLen,  (  DWORD  *  )&len,  0  )  )  goto  errLabel;
	dwBlockLen  /=  8;

	dwBlockLen_session_encrypt  =  dwBlockLen;
	dwBlockLen_session_decrypt  =  dwBlockLen;

	// Determine the size of the key BLOB and allocate memory.
	if  (  !CryptExportKey(  hKey_session,  hPublicKey, SIMPLEBLOB, 0, NULL, &dwBlobLen  )  ) {
		traceLogA(  (char*)  "Error computing BLOB length."  );  goto  errLabel;
	}
	if  (  dwBlobLen  >  mycountof(  pEncCtx->sessionKeyBlob  )  )  goto  errLabel;

	// Export the key into a simple key BLOB.
	pEncCtx->uiBlobLen_sessionKey  =  dwBlobLen;
	if  (  !CryptExportKey(  hKey_session,  hPublicKey, SIMPLEBLOB, 0, (  BYTE  *  )pEncCtx->sessionKeyBlob, (  DWORD  *  )&pEncCtx->uiBlobLen_sessionKey  )  )  {
		qyDisplayLastError(  (char*)"Error during CryptExportKey."  );  goto  errLabel;
	}

	//--------------------------------------------------------------------

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  hKey_session  )  {
			if  (  !(  CryptDestroyKey(  hKey_session  )  )  )  traceLogA(  (char*)  (  "Error  during CryptDestroyKey ."  )  );
		}

		//  Destroy the exchange key
		if  (  hPublicKey  )  {
			if  (  !(  CryptDestroyKey(  hPublicKey  )  )  )  traceLogA(  (char*)  (  "Error  during CryptDestroyKey ."  )  );
		}

		if  (  bAcquired  )  {
			if  (  !CryptReleaseContext(  hCryptProv,  0  )  )  traceLogA(  (char*)"The handle could not be released.\n");
		}
	}

	if  (  !iErr  )  {
		pEncCtx->key_session.hKey  =  hKey_session;
		pEncCtx->key_session.dwBlockLen_encrypt  =  dwBlockLen_session_encrypt;
		pEncCtx->key_session.dwBlockLen_decrypt  =  dwBlockLen_session_decrypt;

		//
		pEncCtx->key_rsa.hKey  =  hPublicKey;
		pEncCtx->key_rsa.dwBlockLen_encrypt  =  dwBlockLen_rsa_encrypt;
		
		//
		pEncCtx->hCryptProv  =  hCryptProv;
	}

	//
	traceLogA(  (char*)  "initCrypt_qmc %s",  iErr  ?  "failed."  :  "ok"  );

	//
	return  iErr;
}


 void  exitCrypt_qmc(  MC_VAR_isCli  *  pVar,  MIS_CNT  *  pMisCnt,  ENC_CTX_session  *  pEncCtx  )
{
	if  (  !pEncCtx->common.type  )  return;

	if  (  pEncCtx->key_session.hKey  )  {
		if  (  !(  CryptDestroyKey(  pEncCtx->key_session.hKey  )  )  )  traceLogA(  (char*)  (  "Error  during CryptDestroyKey ."  )  );
	}
	//  Destroy the exchange key
	if  (  pEncCtx->key_rsa.hKey  )  {
		if  (  !(  CryptDestroyKey(  pEncCtx->key_rsa.hKey  )  )  )  traceLogA(  (char*)  (  "Error  during CryptDestroyKey ."  )  );
	}
	if  (  pEncCtx->hCryptProv  )  {			
		if  (  !CryptReleaseContext(  pEncCtx->hCryptProv,  0  )  )  traceLogA(  (char*)"The handle could not be released.\n");		
	}

	//
	traceLogA(  (char*)  "exitCrypt_qmc ok"  );

	//
	return;
}


 



