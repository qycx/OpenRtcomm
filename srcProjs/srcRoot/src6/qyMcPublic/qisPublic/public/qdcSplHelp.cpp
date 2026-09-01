

#include	"stdafx.h"

#include	<stddef.h>
#include	<mmsystem.h>
#include	<dmo.h>
#include	<dsound.h>

#include	<WinSock2.h>
#include	<tchar.h>

#include	"qyCommonEx.h"

#include	"qysynccommproc.h"
#include	"genericQueue.h"
#include	"qyq2.h"

#include	"qycommproc.h"

#if  0
#include	"qyMcMainCommon.h"
#include	"qyDynLib.h"

#include	"qyMcMainRealTimeMediaProc.h"

#include	"tmpCeLib.h"

#include	"qyAvRecord.h"
#include	"qyAvRecord_dx.h"
#include	"qmcSound_dx.h"

#include	"qmcVideoCapture_isCli.h"
#endif

#include	"qmOpenCommon.h"


		




#define		CONST_mutexName_streamDataQ				"streamDQ"  
#define		CONST_uiMaxQNodes_streamDataQ_is		120
 //
 __declspec(  dllexport  )  int  isCliHelp_streamDataQ_init(  int  tn,  void  *  pGBUF_rtspCliHelp  )
 {
	 int					iErr	=	-1;
	 GBUF_rtspCliHelp  *  pGBuf  =  (  GBUF_rtspCliHelp  *  )pGBUF_rtspCliHelp;
	 TCHAR	tBuf[128]  =  _T(  CONST_mutexName_streamDataQ  );

	 if  (  pGBuf->pStreamDataQ  )  return  -1;

#if  0
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%u"  ),  _T(  CONST_mutexName_streamDataQ  ),  tn  );
	 pGBuf->pStreamDataQ  =  genericQNew(  tBuf,  tBuf,  0,  100,  malloc,  free  );
	 if  (  !pGBuf->pStreamDataQ  )  return  -1;
#endif
	 QY_Q2	*	pQ2  =  NULL;
	 int		size;

	 size  =  sizeof(  QY_Q2  );
	 pGBuf->pStreamDataQ  =  mymalloc(  size  );
	 if  (  !pGBuf->pStreamDataQ  )  goto  errLabel;
	 memset(  pGBuf->pStreamDataQ,  0,  size  );
	 pQ2  =  (  QY_Q2  *  )pGBuf->pStreamDataQ;


	 //
	 GENERIC_Q_CFG	qCfg;
	 memset(  &qCfg,  0,  sizeof(  qCfg  )  );
	 _sntprintf(  qCfg.name,  mycountof(  qCfg.name  ),  _T(  "%s"  ),  _T(  "streamDataQ"  )  );
	 _sntprintf(  qCfg.mutexName_prefix,  mycountof(  qCfg.mutexName_prefix  ),  _T(  "%s%u"  ),  _T(  CONST_mutexName_streamDataQ  ),  tn  );
	 //  qCfg.uiMaxCnt_semaTrigger  =  CONST_maxCnt_sema_showInfoQ_is;
	 qCfg.uiMaxQNodes  =  CONST_uiMaxQNodes_streamDataQ_is;

	 RW_lock_param	rwLockParam;
	 memset(  &rwLockParam,  0,  sizeof(  rwLockParam  )  );
	 rwLockParam.uiMaxCnt_sema			=	CONST_uiInitCnt_sema_q2SyncFlg;
	 rwLockParam.uiInitCnt_sema			=	rwLockParam.uiMaxCnt_sema  -  1;
	 rwLockParam.uiMilliSeconds_mutex_r	=	10000;
	 rwLockParam.uiMilliSeconds_sema_r	=	10000;
	 rwLockParam.uiMilliSeconds_mutex_w	=	10000;
	 rwLockParam.uiMilliSeconds_sema_w	=	10000;



	 //  if  (  initGenericQ(  _T(  "showInfoQ"  ),  sShowInfoStruct.mutexName_syncQ,  CONST_maxCnt_sema_showInfoQ_is,  CONST_uiMaxQNodes_showInfoQ_is,  malloc,  free,  &sShowInfoStruct.q  )  )  goto  errLabel;
	 if  (  initQyQ2(  &qCfg,  &rwLockParam,  1,  NULL,  mallocMemory,  mymalloc,  0,  0,  freeMemory,  myfree,  NULL,  pQ2  )  )  goto  errLabel;
	 pGBuf->bInited_streamDataQ  =  TRUE;

	 //
	 pGBuf->uiMaxQNodes_streamDataQ  =  qCfg.uiMaxQNodes;

	 //
	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
		 isCliHelp_streamDataQ_exit(  pGBuf  );
	 }

	 return  iErr;
 }

  __declspec(  dllexport  )  int  isCliHelp_streamDataQ_exit(  void  *  pGBUF_rtspCliHelp  )
  {
	  GBUF_rtspCliHelp  *  pGBuf  =  (  GBUF_rtspCliHelp  *  )pGBUF_rtspCliHelp;
	  //
	  if  (  pGBuf->pStreamDataQ  )  {
		  QY_Q2  *  pQ2  =  (  QY_Q2  *  )pGBuf->pStreamDataQ;
		  if  (  pGBuf->bInited_streamDataQ  )  {
			  exitQyQ2(  pQ2  );
			  pGBuf->bInited_streamDataQ  =  FALSE;
		  }
		  MACRO_safeFree(  pGBuf->pStreamDataQ  );
	  }
	  return  0;
  }

 __declspec(  dllexport  )  int  isCliHelp_streamDataQ_qPostMsg(  void  *  pQElem,  unsigned  int  size,  void  *  pGENERIC_Q  )
{
#ifdef  __DEBUG__
	 if (1) {
		 QY_Q2* pQ2 = (QY_Q2*)pGENERIC_Q;
		 int nQNodes = getQ2Nodes(pQ2);
		 TCHAR  tBuf[128];
		 _sntprintf(tBuf, mycountof(tBuf), _T("isCliHelp_streamDataQ_qPostMsg: qNodes %d\n"), nQNodes);
		 OutputDebugString(tBuf);
	 }

#endif 

	 //
	   return  q2PostMsg(  pQElem,  size,  (  QY_Q2  *  )pGENERIC_Q,  _T(  "isCliHelp_streamDataQ_qPostMsg"  )  );
}

 __declspec(  dllexport  )  int  isCliHelp_streamDataQ_debug(  void  *  pGENERIC_Q  )
 {
	 QY_Q2	  *  pQ2  =  (  QY_Q2  *  )pGENERIC_Q;
	 return  0;
 }


 //
 __declspec(  dllexport  )  int  isCliHelp_tmpHandler_readData_forSpl(  void  *  pQDC_spl_info,  void  *  p1,  void  *  pMEDIA_data_forSpl  )
 {
	 QDC_spl_info  *  pSplInfo  =  (  QDC_spl_info  *  )pQDC_spl_info;
	 unsigned  int  iSize  =  sizeof(  QDC_MEDIA_data  );
	 int  tmpiRet  =  -1;
	 tmpiRet  =  q2GetMsg(  (  QY_Q2  *  )pSplInfo->cfg.pStreamDataQ,  pMEDIA_data_forSpl,  &iSize,  _T(  "forSpl"  ));
	 return  tmpiRet;
 }

 __declspec(  dllexport  )  int  isCliHelp_streamDataQ_qNodes(  void  *  pStreamDataQ,  void  *  p1,  void  *  p2  )
 {
	 QY_Q2  *  pQ2  =  (  QY_Q2  *  )pStreamDataQ;
	 return  pQ2->qs[0].uiQNodes  +  pQ2->qs[1].uiQNodes;
 }



#if  10
 __declspec(  dllexport  )  int  isCliHelp_initShowInfo(  void  **  ppCtx_showInfo  )
 {
 	 LPCTSTR		errHintWndCls	=  CONST_qnmStatusToolWndClass_client;

	 //  setErrHintWndCls(  errHintWndCls  );
	 initShowInfo(  0,  _T(  "syncQ_showInfo_qmc"  ),  errHintWndCls,  FALSE,  TRUE,  ppCtx_showInfo  );
	 return  0;
 }

 __declspec(  dllexport  )  void  isCliHelp_exitShowInfo(  void  **  ppCtx_showInfo  )
 {
	 exitShowInfo(   ppCtx_showInfo  );
	 return;
 }

 __declspec(  dllexport  )  int  isCliHelp_showInfo(  void  *  pCtx_showInfo,  LPCTSTR  hint  )
{
	if  (  !hint  )  return  -1;
	qyShowInfo(  pCtx_showInfo,  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "Gui"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  hint  );
	return  0;
}
#endif



