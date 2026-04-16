

#include	"stdafx.h"
#include	<windows.h>
#include	<stddef.h>
#include	<tchar.h>
#include	<time.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qnmPcComm.h"
#include	"qnmAssetsCommProc.h"
#include	"qnmSpCommProc.h"
#include	"qwmNetworkStatusCommProc.h"
#include	"qyTCharCommProc.h"
#include	"qnmCustom.h"



  //  从qwmSvr那里摘了一个函数
 extern  "C"  BOOL  bServConnected(  QY_ENV  *  pEnv,  char  *  serverIp,  unsigned  short  serverPort,  void  *  pMacsInfo_notused,  int  serviceId,  char  *  ver,  QY_ENC_CTX  *  pCommEncCtx,  SOCK_TIMEOUT  *  pTo  )
{
	 BOOL						bRet  =  FALSE;
	 QY_SOCK					sock;
	 QY_COMM_SESSION			session;
	 BOOL						bSessionOpen		=		FALSE;
	 QY_COMM_RESP				tmpResp;
	 QWM_MACS_INFO				macsInfo;


	 clearQySock(  &sock  );
	 memset(  &session,  0,  sizeof(  session  )  );
	 	 
	 memset(  &macsInfo,  0,  sizeof(  macsInfo  )  );
	 getQwmMacs(  pEnv,  &macsInfo  );
	 
	 if  (  qnmOpenSession(  serverIp,  serverPort,  &macsInfo,  0,  serviceId,  ver,  pCommEncCtx,  &session,  &sock,  pTo,  NULL,  NULL  )  )  goto  errLabel;
	 bSessionOpen		=		TRUE;
	 if  (  !isRcOk(  session.usLastRespCode_i  )  )  goto  errLabel;

	 if  (  qySendReq(  &session,  &sock,  pTo,  CONST_qyCmd_tryToConnectToServer,  NULL,  0  )  )  goto  errLabel;
	 if  (  qyRecvResp(  &session,  &sock,  pTo,  &tmpResp,  NULL,  0  )  )  goto  errLabel;
	 if  (  !isRcOk(  tmpResp.head.usCode  )  )  goto  errLabel;

	 bRet  =  TRUE;

errLabel:

	 if  (  bSessionOpen  )  qnmCloseSession(  &session,  &sock,  pTo  );

	 return  bRet;

}



