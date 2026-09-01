

#ifndef  __QMCRYPT_H__
#define  __QMCRYPT_H__	//  {



#define		CONST_cspContainer_qmd								_T(  "QmdKeyContainer"  )			//  name of the key container to be used

#define		CONST_cspContainer_qmc								_T(  "QmcKeyContainer"  )			//  name of the key container to be used
#define		CONST_mutexName_syncKey_qmc							_T(  "QmcSyncKey"  )





//
#define		CONST_encryptBlockSize								8 



typedef  struct  __encCtx_session_t								{
				 QY_ENC_CTX										common;
				 //
				 HCRYPTPROV										hCryptProv;										// handle for a cryptographic

				 struct											{
                     HCRYPTKEY									hKey;										//  在messenger, 表示公钥. //  在daemon, 表示private/public pairs
					 DWORD										dwBlockLen_encrypt;							//  加密的blockLen, 密钥长度的字节数 - 11
					 DWORD										dwBlockLen_decrypt;							//  解密的blockLen, 密钥长度的字节数
				 }												key_rsa;

				 struct											{
				 	 HCRYPTKEY									hKey;

					 unsigned  int								uiBlobLen_sessionKey;					
					 char										sessionKeyBlob[CONST_bufSize_sessionKeyBlob];

					 unsigned  short							usLen_sessionIv;
					 char										sessionIv[CONST_bufSize_sessionIv];
					 //
					 DWORD										dwBlockLen_encrypt;							//  加密的blockLen 
					 //
					 DWORD										dwBlockLen_decrypt;							//  解密的blockLen
					 //
				 }												key_session;

				 //
				 unsigned  int									uiBlobLen_sessionKey;
				 char											sessionKeyBlob[CONST_bufSize_sessionKeyBlob];

				 //
				 TCHAR											mutexName_syncCrypt_e[24];					//  2008/10/12, 对每个会话密钥，要保证线程同步。微软的api不支持在2个线程里同时用一个密钥
				 //TCHAR											mutexName_syncCrypt_d[24];					//  2008/10/12, 对每个会话密钥，要保证线程同步。微软的api不支持在2个线程里同时用一个密钥

				 //
				 bool  ucbEncInited;

				 //
}		 ENC_CTX_session;


//
TCHAR  *  get_DEFAULT_cspProvider();
DWORD  get_provType();
unsigned  int  get_algId();


//
BOOL  bGetExportedKey(  HCRYPTKEY hKey, DWORD dwBlobType,  LPBYTE *ppbKeyBlob, LPDWORD pdwBlobLen  );

__declspec(dllexport) int  encryptData(  ENC_CTX_session  *  pEncCtx,  QY_BUF  *  pBuf_help,  char  *  data,  unsigned  int  *  puiDataLen,  unsigned  int  uiBufLen  );
__declspec(dllexport) int  decryptData(  ENC_CTX_session  *  pEncCtx,  QY_BUF  *  pBuf_help,  char  *  encData,  unsigned  int  *  puiEncDataLen  );


#endif

