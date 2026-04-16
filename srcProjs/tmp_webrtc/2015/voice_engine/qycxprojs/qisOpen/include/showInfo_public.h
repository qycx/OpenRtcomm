
#ifndef  __showInfo_public_h__
#define  __showInfo_public_h__		//  {


//  ???????
#define		CONST_qyShowType_scanningNetworkSegment				1
#define		CONST_qyShowType_scanningIp							2
#define		CONST_qyShowType_serviceStatus						3
#define		CONST_qyShowType_refresh							4
#define		CONST_qyShowType_qwmComm							5
#define		CONST_qyShowType_qnmChking							6
#define		CONST_qyShowType_qmdState							7
#define		CONST_qyShowType_qnmProxyChking						8
#define		CONST_qyShowType_bhbScanningNetworkSegment			9
#define		CONST_qyShowType_bhbScanningIp						10
#define		CONST_qyShowType_addChkingType						11
#define		CONST_qyShowType_sysInfo							12		//	2007/04/15
#define		CONST_qyShowType_debug								13		//
#define		CONST_qyShowType_debugWarning						14		//  2007/05/07
#define		CONST_qyShowType_warning							15		//  2007/05/07
#define		CONST_qyShowType_detail								16


//
#ifdef  __cplusplus
  extern  "C"  {
#endif

//
//
__declspec(  dllexport  )  int  qyShowInfo(  void  *  pCtx_showInfo,  int  iShowType,  unsigned  int  *  puiStep,  char  *  clientIp,  LPCWSTR  who_from,  LPCWSTR  who_to,  LPCWSTR  where,  LPCWSTR  doStr,  LPCWSTR  fmt,  ...  );
//
__declspec(  dllexport  )  int  qyShowInfo1(  int  iShowType,  unsigned  int  *  puiStep,  char  *  clientIp,  LPCWSTR  who_from,  LPCWSTR  who_to,  LPCWSTR  where,  LPCWSTR  doStr,  LPCWSTR  fmt,  ...  );


//
#ifdef  __cplusplus
  }
#endif



#endif  //  }


