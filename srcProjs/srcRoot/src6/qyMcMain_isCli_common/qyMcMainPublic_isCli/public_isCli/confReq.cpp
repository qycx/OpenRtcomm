
#include	"stdafx.h"
#include	<time.h>
#include	"qyMcMainCommon.h"

#include	"qmcCommFunc_mis.h"
#include	"help_getDlgTalkVar.h"
#include	"dlgTalkProc.h"
#include	"qyMsgFunc.h"

//
 //
  int  set_doConf(  CONF_req  *  pConfReq,  LPCTSTR  hint  )
  {
	  CCtxQmc  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	  if  (  !pConfReq  )  return  -1;

	  if  (  !hint  )  hint  =  _T(  ""  );

	  //
	  if  (  pProcInfo->av.doConf.confReq.idInfo_imGrp_related.ui64Id  )  {
		  showInfo_open0(  0,  0,  _T(  "Serious error: set_doConf, idInfo_conf is not 0"  )  );
	  }

	  //
	  pProcInfo->av.doConf.confReq  =  *pConfReq;

	  //


	  //
	  TCHAR  tBuf[128];
	  char  buf[128];
	  iFourcc2Str(  pConfReq->policy.talkerPolicy.conf_iFourcc,  buf,  mycountof(  buf  )  );
	  //
	  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "set_doConf ok, confReq: idInfo_conf %I64u,  level %d, conf_iFourcc %S, 2Streams %d, ucHardwareAccl %d, %s"  ),  
		  pConfReq->idInfo_imGrp_related.ui64Id,  
		  (int)pConfReq->policy.usAvLevel,
		  buf,
		  (int)pConfReq->hgInfo.bShare_2ndStream,
		  (int)pConfReq->ucHardwareAccl,
		  hint  );
	  showInfo_open0(  0,  0,  tBuf  );
	  _sntprintf(tBuf, mycountof(tBuf), _T("confReq: meetingId_hg %I64u"), pConfReq->hgInfo.ui64MeetingId_hg);
	  showInfo_open0(0, 0, tBuf);
	  _sntprintf(tBuf, mycountof(tBuf), _T("confReq: initiator %I64u"), pConfReq->idInfo_initiator.ui64Id);
	  showInfo_open0(0, 0, tBuf);

	  //
	  return  0;
  }

  int  clear_doConf(  QY_MESSENGER_ID  idInfo_conf,  LPCTSTR  hint  )
  {
	  CCtxQmc  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	  TCHAR  tBuf[128];

	  if  (  !hint  )  hint  =  _T(  ""  );

	  //
		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Serious error: clear_doConf: idInfo_conf %I64u != doConf.%I64u"  ),  idInfo_conf.ui64Id,  pProcInfo->av.doConf.confReq.idInfo_imGrp_related.ui64Id  );
	  if  (  idInfo_conf.ui64Id  !=  pProcInfo->av.doConf.confReq.idInfo_imGrp_related.ui64Id  )  {
		  showInfo_open0(  0,  0,  tBuf  );
	  }


	  //
	  memset(  &pProcInfo->av.doConf,  0,  sizeof(  pProcInfo->av.doConf  )  );

	  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "set_doConf ok, %s"  ),  hint  );
	  showInfo_open0(  0,  0,  tBuf  );

	  return  0;
  }




//
//int  sendConfReq(  void  *  p,  HWND  hDlgTalk,  QY_MESSENGER_ID  idInfo_conf,  unsigned  short  usOp,  unsigned  short  usAvLevel,  int  conf_iFourcc,  unsigned  short  conf_usMaxSpeakers  )
 int  sendConfReq(void* p, HWND  hDlgTalk, QY_MESSENGER_ID  idInfo_conf, unsigned  short  usOp, unsigned  short  usAvLevel, unsigned  short  conf_usMaxSpeakers, TALKER_policy* pTalkerPolicy, CONF_hg_info * pHgInfo)
{
	int  iErr  =  -1;
		CHelp_getDlgTalkVar				help_getDlgTalkVar;
	DLG_TALK_var				*	pm_var		=		(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  hDlgTalk  );
	if  (  !pm_var  )  return  -1;
	DLG_TALK_var				&	m_var		=		*pm_var;
	MC_VAR_isCli					*	pProcInfo	=		QY_GET_procInfo_isCli(  );//(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;

	int  lenInBytes  =  0;

	//
	QY_MESSENGER_ID		idInfo_to;

	//
	TALKER_policy talkerPolicy;
	memset(&talkerPolicy, 0, sizeof(talkerPolicy));
	if (pTalkerPolicy) talkerPolicy = *pTalkerPolicy;

	//
	if  (  !idInfo_conf.ui64Id  )  return  -1;
	
	//
	CONF_req  req;
	memset(&req, 0, sizeof(req));
	req.uiType  =  CONST_imCommType_confReq;
	req.idInfo_imGrp_related=idInfo_conf;
	req.usOp  =  usOp;
	req.policy.usAvLevel  =  usAvLevel;
	//
	req.policy.usMaxSpeakers = conf_usMaxSpeakers;
	//
	//req.policy.talkerPolicy.conf_iFourcc  =  pTalkerPolicy->conf_iFourcc;
	req.policy.talkerPolicy = talkerPolicy;

	//
	if (pHgInfo) {
		req.hgInfo = *pHgInfo;
	}

	//
	lenInBytes  =  sizeof(  req  );			
	//					
	MACRO_prepareForTran(  );

	
	//	
	pProcInfo->postMsg2Mgr_mc(  m_var.pMisCnt,  NULL,  CONST_misMsgType_req,  0,  CONST_qyCmd_sendReq,  tStartTran,  uiTranNo,  0,  (  char  *  )&req,  lenInBytes,  NULL,  0,  0,  NULL,  FALSE  );
	

	iErr  =  0;
errLabel:

	//
	TCHAR  tBuf[128];
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "sendReq: conf %I64u %s"  ),  idInfo_conf.ui64Id,  qyGetDesByType1(  CONST_imOpTable_en,  usOp  )  );
	char  buf[128];
	iFourcc2Str(  talkerPolicy.conf_iFourcc,  buf,  mycountof(  buf  )  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s conf_iFourcc %S"  ),  tBuf,  buf  );
	showInfo_open0(  0,  0,  tBuf  );

	//
	return  iErr;
}

