
#ifndef  __qmdCryptCommProc_h__
#define  __qmdCryptCommProc_h__		//  {


//
typedef  struct  __qmdCryptInfo_t {

	struct {
		BYTE										publicKeyBlob[CONST_bufSize_publicKeyBlob];
		unsigned  int								uiBlobLen_publicKey;

		//
		BYTE										publicKeyBlob_1[CONST_bufSize_publicKeyBlob];
		unsigned  int								uiBlobLen_publicKey1;

	}												crypt;

}		 QmdCryptInfo;

typedef  struct  __qmdCryptInfoEx_t {
	struct {
		BYTE										privateKeyBlob_1[CONST_bufSize_publicKeyBlob];
		unsigned  int								uiBlobLen_privateKey1;
	};
}		 QmdCryptInfoEx;


//
typedef  struct {
	HCRYPTPROV		provider1;

}					HgEnc;

//
//
typedef  struct {
	//
	HCRYPTKEY										sessionKey;
	//
	char											rawKey[32];
	int												keySize;

}													HgSessionEnc;


//
typedef  struct {

	HgEnc		common;
	//
	//  以下增加自定义的数据成员
	int			i_reserved;

}  myHgEnc;



//
typedef  struct {

	HgSessionEnc	common;

	//
	//  以下增加自定义的数据成员
	int			i_reserved;

}  myHgSessionEnc;


////
__declspec(dllexport)  int  getSize_myHgEnc();

//int  hgEncInit(  CHgDaemon  *  pHg  );
__declspec(dllexport) int  hgEncInit(void* p0, void* p1, void* p2, myHgEnc** ppmyHgEnc);
//int  hgEncExit(  CHgDaemon  *  pHg  );
__declspec(dllexport) int  hgEncExit(void* p0, void* p1, void* p2, myHgEnc** ppmyHgEnc);


//
__declspec(dllexport) int  getSize_myHgSessionEnc();

//int hgSessionInit(CHgDaemon* pHg, QMD_SESSION_hg* pSession);
__declspec(dllexport) int hgSessionInit(myHgEnc* pmyHgEnc, myHgSessionEnc ** ppSessionEnc);

//int hgSessionExit(CHgDaemon* pHg, QMD_SESSION_hg* pSession);
__declspec(dllexport) int hgSessionExit(myHgEnc* pmyHgEnc, myHgSessionEnc ** ppSessionEnc );


//
__declspec(dllexport) int  hgEnc(QY_COMM_SESSION* pSession, myHgSessionEnc* pmyHgSessionEnc, char* input, unsigned  int  inputLen, char* output, unsigned  int* pOutputSize);
__declspec(dllexport) int  hgDec(QY_COMM_SESSION* pSession, myHgSessionEnc* pmyHgSessionEnc, char* input, unsigned  int  inputLen, char* output, unsigned  int* pOutputSize);




//
//
__declspec(dllexport) int  initCrypt_qmd(QmdCryptInfo* pVar, LPCTSTR  szContainer, LPCTSTR  szProvider, BOOL  bNewKeySetIfNotExists, ENC_CTX_session* pEncCtx);
__declspec(dllexport) void  exitCrypt_qmd(QmdCryptInfo* pVar, ENC_CTX_session* pEncCtx);
//
void  exitCrypt_qmd1(void* pQmdSession);

//
__declspec(dllexport)int  parseAndChkAuth_mis_func(void* pSubThreadInfoParam, //QMD_SESSION* pSession
	ENC_CTX_session& commEncCtx,
	QY_COMM_SESSION& comm,
	QmdCryptInfo& qmdCryptInfo,
	unsigned  int  cfg_policy_uiCommEncCtxType,
	unsigned  int* puiChannelType, QY_COMM_AUTHINFO_MIS* pAuthInfo, AUTH_RESP_MIS* pAuthResp,
	QY_MESSENGER_INFO* pObj);



#endif  //  }


