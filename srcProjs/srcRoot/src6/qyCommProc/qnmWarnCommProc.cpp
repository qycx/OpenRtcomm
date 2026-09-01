
#include	"stdafx.h"

#include	<windows.h>
#include	<stddef.h>
#include	<stdlib.h>
#include	<tchar.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyCommProc.h"
#include	"qnmWarnCommProc.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"

#include	"qnmCommProc.h"
#include	"qyTCharCommProc.h"


 extern  "C"  int  clearQnmWarnFlg(  void  *  pReserved  )
{
	 qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_newEmergency  ),  _T(  "0"  )  );
	 return  0;
}

 // 对拨号、外联、受控端异常、陌生主机接入事件,进行报警处理.
 extern  "C"  int  setQnmWarnInfo(  void  *  pReserved )
{
	 char	timeBuf[14  +  1];
	 TCHAR	tBuf[32];

	 if  (  getCurTime(  timeBuf  )  )  return  -1;
	 
	 myStr2TChar(  timeBuf,  tBuf,  mycountof(  tBuf  )  );
	 qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_emergencyTime  ),  tBuf  );
	 qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_newEmergency  ),  _T(  "1"  )  );
	 
	 return  0;

}

 extern  "C"  int  getQnmWarnInfo(  void  *  pReserved,  char  *  timeBuf,  int  size,  BOOL  *  pbNew  )
{
	 int	iErr  =  -1;
	 TCHAR	tBuf[128];
	 char	tmpTimeBuf[14  +  1];
	 char	bNewBuf[2];
	 
	 if  (  size  <=  14  )  return  -1;

	 if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_emergencyTime  ),  (  char  *  )tBuf,  sizeof(  tBuf  )  )  )  tBuf[0]  =  0;
	 myTChar2Utf8(  tBuf,  tmpTimeBuf,  sizeof(  tmpTimeBuf  )  );
	 if  (  strlen(  tmpTimeBuf  )  !=  14  )  goto  errLabel;
	 
	 if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_newEmergency  ),  (  char  *  )tBuf,  sizeof(  tBuf  )  )  )  tBuf[0]  =  0;
	 myTChar2Utf8(  tBuf,  bNewBuf,  sizeof(  bNewBuf  )  );
	 
	 strcpy(  timeBuf,  tmpTimeBuf  );
	 *pbNew  =  (  bNewBuf[0]  ==  '1'  );

#ifdef  __DEBUG__
#if  0
	    if  (  *pbNew  )  {	 	
			qyShowInfo1(  CONST_qyShowType_qnmChking,  0,  0,  _T(  "Server"  ),  0,  0,  _T(  ""  ),  _T(  "need to warn"  )  );
			//  MessageBeep(  -1  );
			Beep( 750, 300 );
		}
#endif
#endif

	 iErr  =  0;

errLabel:

	 return  iErr;

}



 extern  "C"  int  getQnmWarnCfg(  void  *  pReserved,  QNM_WARN_CFG  *  pCfg  )
{
	 char	buf[128]	=	"";
	 
	 //  读取告警配置
	 if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_warnOn  ),  buf,  sizeof(  buf  )  )
				 &&  atol(  buf  )  ==  1  )
		 {
			 pCfg->bWarnOn  =  TRUE;
			 if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_warnUntilUsrStopIt  ),  buf,  sizeof(  buf  )  )  
				 &&  atol(  buf  )  ==  1  )  
			 {
				 pCfg->bWarnUntilUsrStopIt  =  TRUE;
				 }
			 else  {
				   pCfg->bWarnUntilUsrStopIt  =  FALSE;

				   if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_maxWarnElapseInSecond  ),  buf,  sizeof(  buf  )  )
					   &&  atol(  buf  )  >  5  )
				   {
					   pCfg->nMaxWarnElapse   =  atol(  buf  )  *  1000;
					   }
				   else
					   pCfg->nMaxWarnElapse  =  5000;

			 }

		}
	 else  
			 pCfg->bWarnOn  =  FALSE;			



	 if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_popupToWarnStartTime  ),  buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
	 trim(  buf  );
	 if  (  _stricmp(  buf,  pCfg->popupToWarnStartTime  )  )  safeStrnCpy(  buf,  pCfg->popupToWarnStartTime,  sizeof(  pCfg->popupToWarnStartTime  )  );


	 return  0;
}




  extern  "C"  int  qyhtonQnmWarningMsgs(  QNM_WARNING_MSGS  *  pMsgs  )
{
	 int	len	=	-1;
	 int	i;

	 if  (  pMsgs->cnt  >  mycountof(  pMsgs->mems  )  )  goto  errLabel;

	 for  (  i  =  0;  i  <  (  int  )pMsgs->cnt;  i  ++  )  {
		  MACRO_htonl(  pMsgs->mems[i].id  );
		  MACRO_htonl(  pMsgs->mems[i].uiType  );
		  MACRO_htonl(  pMsgs->mems[i].ulIp  );
	 }
	 len  =  offsetof(  QNM_WARNING_MSGS,  mems  )  +  pMsgs->cnt  *  sizeof(  pMsgs->mems[0]  );
	 
	 MACRO_htonl(  pMsgs->cnt  );

errLabel:
	 return  len;
}

 extern  "C"  int  qyntohQnmWarningMsgs(  QNM_WARNING_MSGS  *  pMsgs  )
{
	 int	len	=	-1;
	 int	i;

	 MACRO_ntohl(  pMsgs->cnt  );

	 if  (  pMsgs->cnt  >  mycountof(  pMsgs->mems  )  )  goto  errLabel;

	 for  (  i  =  0;  i  <  (  int  )pMsgs->cnt;  i  ++  )  {
		  MACRO_ntohl(  pMsgs->mems[i].id  );
		  MACRO_ntohl(  pMsgs->mems[i].uiType  );
		  MACRO_ntohl(  pMsgs->mems[i].ulIp  );
	 }
	 len  =  offsetof(  QNM_WARNING_MSGS,  mems  )  +  pMsgs->cnt  *  sizeof(  pMsgs->mems[0]  );

errLabel:
	 return  len;
}
