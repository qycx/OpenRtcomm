

#include	"stdafx.h"

#include	<windows.h>
#include	<tchar.h>
#include	<WinSock2.h>
#include	<stdlib.h>

#include	"qyCommon.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCustom.h"
#include	"qyTCharCommProc.h"

/*
#ifdef  __DEBUG__														//  2005/05/01
	#define		CONST_qnmVer								"030707d\0"__TIMESTAMP__
#else
	#define		CONST_qnmVer								"030706\0"__TIMESTAMP__
#endif
*/

//  2005/06/25
//
//
//  #define		CONST_qnmVer								"033266"
//  #define		CONST_qnmVer								"033502"		//  2005/05/26
//  #define		CONST_qnmVer								"033918"		//  2010/09/05
//  #define		CONST_qnmVer								"033919"		//  2011/08/20
//  #define		CONST_qnmVer								"034208"		//  2011/09/22
#define		CONST_qnmVer								"034301"			//  2011/11/08
//  #define		CONST_qnmDbVer								CONST_qnmVer
#define		CONST_qnmDbVer								"034101"
//
//
//
//  #define		CONST_qnmVer_is								"024705"				//  
//  #define		CONST_qnmVer_is								"025401"				//  
#if  defined(  __DEBUG__  )  &&  0
		#define		CONST_qnmVer_is							"02617501"				//    for debug. 2015/01/01
#else
		#define		CONST_qnmVer_is							"02661320"				//"02661093"  //"02660997"				//  2017/10/19	"02660258"		
#endif
//
#define			CONST_qnmDbVer_is							"015003"				//  "015002"				//  2017/07/25

//
//  031401, 2005/10/10
//  031301

 extern  "C"  char  *  qnmVerStr(  int  iServiceId  )
{
	char	*	p	=	(char*)"";

	switch  (  iServiceId  )  {
			case  CONST_qyServiceId_mis:
				  #ifdef  __DEBUG__
						  p  =  (char*)CONST_qnmVer_is"d\0";
				  #else
						  p  =  (char*)CONST_qnmVer_is"\0";
				  #endif
				  break;
			default:
				   #ifdef  __DEBUG__
						   p  =  (char*)CONST_qnmVer"d\0";
				   #else
						   p  =  (char*)CONST_qnmVer"\0";
				   #endif
				   break;
	}
	return  p;
}


 

 //
 extern  "C"  char  *  qnmDbVerStr(  int  iServiceId  )
{
	char	*	p	=	(char*)"";

	switch  (  iServiceId  )  {
			case  CONST_qyServiceId_mis:
				  #ifdef  __DEBUG__
						  p  =  (char*)CONST_qnmDbVer_is"d\0";
				  #else
						  p  =  (char*)CONST_qnmDbVer_is"\0";
				  #endif
				  break;
			default:
				   #ifdef  __DEBUG__
						   p  =  (char*)CONST_qnmDbVer"d\0";
				   #else
						   p  =  (char*)CONST_qnmDbVer"\0";
				   #endif
				   break;
	}
	return  p;
}
 


 extern  "C"  char  *  qnmDevelopTimestamp(  )
{
	 //  char	*	p  =  CONST_qnmVer;
	 char	*	p  =  qnmVerStr(  0  );	//  2005/06/25

	 return  p + strlen(  p  )  +  1;	 
}


  //  2014/09/23
 extern  "C"  int  parse_qnmVerStr(  char  *  ver,  unsigned  short  *  pshVer,  BYTE  *  pblVer,  BYTE  *  pb_mantissa_ver  )
{
	if  (  !ver  )  return  -1;
	if  (  strlen(  ver  )  <  6  )  return  -1;
	long  lhVer  =  0;
	BYTE  blVer  =  0;
	BYTE  b_mantissa_ver  =  0;

	char  buf[4  +  1];
	memcpy(  buf,  ver,  4  );
	buf[4]  =  0;
	lhVer  =  atol(  buf  );
	//
	memcpy(  buf,  ver  +  4,  2  );
	buf[2]  =  0;
	blVer  =  atol(  buf  );
	//
	memcpy(  buf,  ver  +  6,  2  );
	buf[2]  =  0;
	b_mantissa_ver  =  atol(  buf  );


	//
	if  (  pshVer  )  *pshVer  =  lhVer;
	if  (  pblVer  )  *pblVer  =  blVer;
	if  (  pb_mantissa_ver  )  *pb_mantissa_ver  =  b_mantissa_ver;	//  2015/02/15

	return  0;
}


////
//
 

//
#define		DEFAULT_qySystemId						CONST_qySystemId_messenger						//  nms			//  assetMgr			//  netMc2			//  

// 
#define		DEFAULT_subSystemId						CONST_subSystemId_standard						//  2018/10/25,    basic							//  2017/06/21

 //
#ifdef  __DEBUG__		//  2017/09/29
		#undef		DEFAULT_subSystemId
		#define		DEFAULT_subSystemId				CONST_subSystemId_standard						//  2017/09/29
#endif

			//
			//
			#if  0  ||  defined(  __isCli__  )
    				#define		DEFAULT_qyAppType						CONST_qyAppType_client		//  2007/03/11, Ò»°ãÎªCONST_qyAppType_null,CONST_qyAppType_client
			#else
  			  		#define		DEFAULT_qyAppType						CONST_qyAppType_null		//  2007/03/11, Ò»°ãÎªCONST_qyAppType_null,CONST_qyAppType_client
			#endif


//
#if  0
			#define		__SUPPORT_devAuth__			//  2011/03/21
#endif


 

 


//
///////////////////////

 //
 extern  "C"  int  qyGetSystemId(  )
{
	 return  DEFAULT_qySystemId;
}


 //  2017/06/21
 extern  "C"  int  qyGetSubSystemId_mgr(  )
 {
	 return  DEFAULT_subSystemId;
 }


 //
 extern  "C"  int  qyGetAppType(  int  iSystemId,  LPCTSTR  guiRootKey  )
{
	 int		iAppType		=	-1;
	 //  char		buf[1024];
	 //TCHAR	*	pRegValName		=	_T(  CONST_regValName_appType  );
	 //TCHAR		tBuf[256];

	 //
	 return  DEFAULT_qyAppType;
}


 


 //  2011/08/14
 extern  "C"  BOOL  bAppClient(  int  iAppType  )
{
	BOOL	bRet	=	FALSE;

	switch  (  iAppType  )  {
			case  CONST_qyAppType_client:
			case  CONST_qyAppType_client_ts:
				  bRet  =  TRUE;
				  break;
			default:
					break;
	}

	return  bRet;
}



 //
 extern  "C"  BOOL  bSupported_devAuth(  )
{
	#if defined(  __APP_qyMc__  )  &&  DEFAULT_qyAppType  !=  CONST_qyAppType_null
		return  FALSE;
	#endif
	
	#ifdef  __SUPPORT_devAuth__
			return  TRUE;
	#endif

	return  FALSE;
 }











 #ifdef  __DEBUG__
 BOOL  dbg_bNoRefreshRecentFriends(  )
 {
	 return  TRUE;
 }
#endif


 BOOL  bTEST_shareScreen(  unsigned  int  *  piW_test,  unsigned  int  *  piH_test  )
 {
	 unsigned  int  iW_test  =  640;  
	 unsigned  int  iH_test  =  480;

	#if  0
		#define		__TEST_shareScreen__					//  2012/05/06. 定义此标志,则启动全屏共享时,采用160X120的图像. 这是为了方便能点数众多的测试
	    if  (  piW_test  )  *piW_test  =  iW_test;
		if  (  piH_test  )  *piH_test  =  iH_test;
		return  TRUE;
	#endif

	 return  FALSE;
 }


 //  2017/08/07
#if  10
	//#define		DEFAULT_qyCustomId						CONST_qyCustomId_general	//  CONST_qyCustomId_zjga
	//
//#define		DEFAULT_qyCustomId						CONST_qyCustomId_cqyt
#define		DEFAULT_qyCustomId						CONST_qyCustomId_jkcs
//	#define		DEFAULT_qyCustomId						CONST_qyCustomId_business
#else
	#define		DEFAULT_qyCustomId						CONST_qyCustomId_hbwj			//  CONST_qyCustomId_hzj			//  2018/10/23
#endif


 ///
 extern  "C"  int  qyGetCustomId(  )
{
	 return  DEFAULT_qyCustomId; 

}

 //
 QY_DMITEM  CONST_customIdTable[]  =
 {
	 {		CONST_qyCustomId_shhg,				(TCHAR*)_T(  "shhg"  ),		},
	 {		CONST_qyCustomId_zjga,				(TCHAR*)_T(  "zjga"  ),		},
	 {		CONST_qyCustomId_general,			(TCHAR*)_T(  "general"  ),	},
	 {		CONST_qyCustomId_business,			(TCHAR*)_T(  "business"  ),	},
	 {		CONST_qyCustomId_bjyz,				(TCHAR*)_T(  "bjyz"  ),		},
	 {		CONST_qyCustomId_hzj,				(TCHAR*)_T(  "hzj"  ),		},

	 {		-1,		 }

 };


 extern  "C"  int  qyGetServiceId(  int  iSystemId  )	//  2007/03/07
{
	 int	iServiceId	=	0;

	 switch  (  iSystemId  )  {
			 case  CONST_qySystemId_messenger:
				   iServiceId  =  CONST_qyServiceId_mis;
				   break;
			 default:
					iServiceId  =  CONST_qyServiceId_qwm;
					break;
					
	 }

	 return  iServiceId;
}


  #define		DEFAULT_qyEncType_is									CONST_qyEncType_rsa
// #define		DEFAULT_qyEncType_is									0

extern  "C"  int  qyGetEncType(  int  iSystemId  )
{
	return  DEFAULT_qyEncType_is;
}



#ifdef  __DEBUG__

  extern  "C"  int  printSystemId(  )
{
	 //  traceLogA(  (char*)  "systemId is %s",  qyGetDesByType1(  CONST_qySystemIdTable,  qyGetSystemId(  )  )  );
	 return  0;
}


 extern  "C"  int  printDefaultQyCustomId(  )
{
	 switch  (  qyGetCustomId(  )  )  {
			 case  CONST_qyCustomId_shhg:
	 			   traceLogA(  (char*)  "DEFAULT_qyCustomId is shhg"  );
				   break;
			 case  CONST_qyCustomId_zjga:
				   traceLogA(  (char*)  "DEFAULT_qyCustomId is zjga"  );
				   break;
			 default:
					traceLogA(  (char*)  "Unknown DEFAULT_qyCustomId %d",  qyGetCustomId(  )  );
					break;
					
	 }

	 return  0;

}

#endif