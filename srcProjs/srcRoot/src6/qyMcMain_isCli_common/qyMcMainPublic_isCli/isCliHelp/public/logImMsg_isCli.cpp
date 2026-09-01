

#include	"stdafx.h"
//#include	<afxdb.h>
#include	<windowsx.h>
#include	<winsock2.h>
#include	<vfw.h>

#include	"qmCommon.h"
#include	"qyDbCommon.h"
#include	"qyTCharCommProc.h"
#include	"myDb.h"

#ifdef  __isCli__
		#include	"qyMcMainCommon.h"
		//#include	"QyFile.h"

#include	"qyMcMainCommon.h"

#include	"tmpCeLib.h"

#include	"qyOpenShellCommon.h"
#include	"dlgTalkProc.h"
#include	"WallTalkers.h"
#include	"myresource.h"
//#include	"DlgInstantAssistant.h"
#include	"qyCusResTemp.h"
#include	"qmcVideoCapture_isCli.h"

#include	"qyAvRecordPublic.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"


		#include	"funcsForisCliHelp.h"
#endif


//
  __declspec(  dllexport  )  int  logImMsg_isCli(  void  *  pDb,  int  iDbType,  void  *  pDBManager,  QY_DMITEM  *  pFieldIdTable,  IM_MSG_RCD  *  pRcd  )
{
	int				iErr = -1;

	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	QY_MC  *  pQyMc  =  pProcInfo->pQyMc;
	if  (  !pQyMc  )  return  -1;
	MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pProcInfo->getMisCntByName(  _T(  ""  )  );
	if  (  !pMisCnt  )  return  -1;

	//
	return  pProcInfo->do_logImMsg_isCli(pDb, iDbType, pDBManager,  pRcd);


#if 0


	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;


	//
	//if  (  !pProcInfo->cfg.policy.ucbSaveMsg  )  return  0;



	
	TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1]				=	_T(  ""  );
	char			idStr_send[CONST_qyMessengerIdStrLen  +  1]		=	"";
	char			sendTime[CONST_qyTimeLen  +  1]					=	"";
	//CDBVariant		varVals[2];
	char			tStartTime_serv[CONST_qyTimeLen  +  1]			=	"";
	char			idStr_recv[CONST_qyMessengerIdStrLen  +  1]		=	"";
	char			recvTime[CONST_qyTimeLen  +  1]					=	"";
	char			firstTime[CONST_qyTimeLen  +  1]				=	"";
	char			lastTime[CONST_qyTimeLen  +  1]					=	"";
	char			lastModifiedTime[CONST_qyTimeLen  +  1]			=	"";
	char 			displayTime[64]									=	"";
	//
	TCHAR			contents[10][120  +  1];
	TCHAR			txtContents[10][120  +  1];
	int				i;
	TCHAR		*	pT;
	int				len;
	int				len1;
	unsigned  int	uiContentType;

	FILE  *  fp  =  NULL;


	QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs  &g_dbFuncs  =  *pDbFuncs;



	if  (  !idInfo2Str(  &pRcd->idInfo_send,  idStr_send,  mycountof(  idStr_send  )  )  )  goto  errLabel;
	getTimeStr(  pRcd->tSendTime,  sendTime,  mycountof(  sendTime  )  );

#if  0
	//
	if  (  !pRcd->senderDesc[0]  ||  !pRcd->receiverDesc[0]  )  {	//  如果没有用户信息，则补充用户信息. 这是记流水帐的需要
		QY_MESSENGER_REGINFO	regInfo;
		MY_REG_DESC				desc;
		IM_GRP_INFO				grpInfo;

		//if (  pRcd->uiType  !=  CONST_objType_imGrp  )  
		{
		//
		if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pDb,  iDbType,  pFieldIdTable,  pRcd->misServName,  &pRcd->idInfo_send,  0,  NULL,  &regInfo,  NULL,  NULL  )  )  memset(  &regInfo,  0,  sizeof(  regInfo  )  );
		if  (  regInfo2Desc(  0,  &regInfo,  &desc,  NULL,  0,  NULL,  0  )  )  goto  errLabel;
		if  (  desc.pSyr[0]  )  _sntprintf(  pRcd->senderDesc,  mycountof(  pRcd->senderDesc  ),  _T(  "%s - %s - %s"  ),  desc.pDw,  desc.pBm,  desc.pSyr  );  
		if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pDb,  iDbType,  pFieldIdTable,  pRcd->misServName,  &pRcd->idInfo_recv,  0,  NULL,  &regInfo,  NULL,  NULL  )  )  memset(  &regInfo,  0,  sizeof(  regInfo  )  );
		if  (  regInfo2Desc(  0,  &regInfo,  &desc,  NULL,  0,  NULL,  0  )  )  goto  errLabel;
		if  (  desc.pSyr[0]  )  _sntprintf(  pRcd->receiverDesc,  mycountof(  pRcd->receiverDesc  ),  _T(  "%s - %s - %s"  ),  desc.pDw,  desc.pBm,  desc.pSyr  );  
		}
#if 0
		else  {
			getTalkerDesc(  0,  &pRcd->idInfo_send,  NULL,  0,  &pRcd->taskDisplay.displayName_sender,  mycountof(  taskDisplay.displayName_sender  )  );  
		}
#endif
	}
#endif


	//getTalkerDesc(  0,  &pRcd->idInfo_send,  NULL,  0,  &pRcd->>taskDisplay.displayName_sender,  mycountof(  taskDisplay.displayName_sender  )  );  

	//
	getTimeStr(  pRcd->tStartTime_serv,  tStartTime_serv,  mycountof(  tStartTime_serv  )  );
	if  (  !idInfo2Str(  &pRcd->idInfo_recv,  idStr_recv,  mycountof(  idStr_recv  )  )  )  goto  errLabel;
	getTimeStr(  (  time_t  )pRcd->tRecvTime,  recvTime,  mycountof(  recvTime  )  );
	getTimeStr(  pRcd->firstTime,  firstTime,  mycountof(  firstTime  )  );
	getTimeStr(  pRcd->lastTime,  lastTime,  mycountof(  lastTime  )  );
	getTimeStr(  pRcd->tLastModifiedTime,  lastModifiedTime,  mycountof(  lastModifiedTime  )  );


	//  2008/10/24, 这里要过滤下，不能让内容里有 ' 
	escapeTStr(  pRcd->content,  mycountof(  pRcd->content  )  );
	escapeTStr(  pRcd->txtContent,  mycountof(  pRcd->txtContent  )  );

	//
	uiContentType  =  pRcd->uiType;

	memset(  contents,  0,  sizeof(  contents  )  );
	if  (  pRcd->content[0]  )  {
		//
		//
		pT  =  pRcd->content;
		len  =  lstrlen(  pT  );
		//
		#ifdef  __DEBUG__
				traceLogA(  "mycountof(  contents  )  is %d,  mycountof(  contents[i]  ) is %d",  mycountof(  contents  ),  mycountof(  contents[0]  )  );
		#endif
		//
		for  (  i  =  0;  len  &&  i<  mycountof(  contents  );  i  ++  )  {
			 lstrcpyn(  contents[i],  pT,  mycountof(  contents[i]  )  );
			 len1  =  lstrlen(  contents[i]  );
			 pT  +=  len1;  len  -=  len1;  
		}
	}

	memset(  txtContents,  0,  sizeof(  txtContents  )  );
	if  (  pRcd->txtContent[0]  )  {
			
		//
		pT  =  pRcd->txtContent;
		len  =  lstrlen(  pT  );
		for  (  i  =  0;  len  &&  i<  mycountof(  txtContents  );  i  ++  )  {
			 lstrcpyn(  txtContents[i],  pT,  mycountof(  txtContents[i]  )  );
			 len1  =  lstrlen(  txtContents[i]  );
			 pT  +=  len1;  len  -=  len1;  
		}
	}

	//
	{
		//  CQyFile	file;

		TCHAR	fileName[MAX_PATH  +  1]  =  _T(  ""  );
		BOOL	bSentByMe  =  FALSE,  bRecvByMe  =  FALSE;
		//if  (  pRcd->idInfo_send.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  bSentByMe  =  TRUE;
		if  (  pRcd->idInfo_recv.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  bRecvByMe  =  TRUE;
		TCHAR	peerDesc[128]  =  _T(   ""  );
		TCHAR	talkerDesc[128]  =  _T(  ""  );
		TCHAR  shortName[128]  =  _T(  ""  );
		//
		//if  (  bSentByMe  )  
		if  (  !bRecvByMe    )
		{

			//
			pFuncs->pf_getTalkerDesc(  pMisCnt,  &pRcd->idInfo_send,  talkerDesc,  mycountof(  talkerDesc  ),  shortName,  mycountof(  shortName  )  );  
			_sntprintf(  pRcd->senderDesc,  mycountof(  pRcd->senderDesc  ),  _T(  "%s"  ),  talkerDesc  );
			pFuncs->pf_getTalkerDesc(  pMisCnt,  &pRcd->idInfo_recv,  talkerDesc,  mycountof(  talkerDesc  ),  shortName,  mycountof(  shortName  )  );  

			//  _sntprintf(  fileName,  mycountof(  fileName  ),  _T(  "%s%s%I64u.txt"  ),  pProcInfo->cfg.policy.dirToSaveMsg,  talkerDesc,  pRcd->idInfo_recv.ui64Id   );
			//_sntprintf(  fileName,  mycountof(  fileName  ),  _T(  "%s%s_%I64u.txt"  ),  pProcInfo->cfg.policy.dirToSaveMsg,  talkerDesc,  pRcd->idInfo_recv.ui64Id   );
			_sntprintf(fileName, mycountof(fileName), _T("%s%I64u.txt"), pProcInfo->cfg.policy.dirToSaveMsg, pRcd->idInfo_logicalPeer.ui64Id);
			//

			}
		else  
		{
			pFuncs->pf_getTalkerDesc(  pMisCnt,  &pRcd->idInfo_send,  talkerDesc,  mycountof(  talkerDesc  ),  shortName,  mycountof(  shortName  )  );  
			_sntprintf(  pRcd->senderDesc,  mycountof(  pRcd->senderDesc  ),  _T(  "%s"  ),  talkerDesc  );
			//  _sntprintf(  fileName,  mycountof(  fileName  ),  _T(  "%s%s.txt"  ),  pProcInfo->cfg.policy.dirToSaveMsg,  pRcd->senderDesc  );
			//_sntprintf(  fileName,  mycountof(  fileName  ),  _T(  "%s%s_%I64u.txt"  ),  pProcInfo->cfg.policy.dirToSaveMsg,  talkerDesc,  pRcd->idInfo_send.ui64Id   );
			_sntprintf(fileName, mycountof(fileName), _T("%s%I64u.txt"), pProcInfo->cfg.policy.dirToSaveMsg, pRcd->idInfo_logicalPeer.ui64Id);
		}

		fp  =  _tfopen(  fileName,  _T(  "at,ccs=UTF-8"  )  );
		if  (  !fp  )  goto  errLabel;    
		
		//  _ftprintf(  fp,  _T(  "%s\n"  ),  pRcd->content  );
		qyDisplayTime(  firstTime,  displayTime,  mycountof(  displayTime  )  );
		//_ftprintf(  fp,  _T(  "%s %s: %s\n"  ),  pRcd->senderDesc,  CQyString( displayTime  ),  pRcd->content  );
		_ftprintf(fp, _T("%I64u %s: %s\n"), pRcd->idInfo_send.ui64Id, CQyString(displayTime), pRcd->logMsgContent);

	}

	//


	iErr  =  0;
errLabel:

	if  (  fp  )  fclose(  fp  );
#endif

	return  iErr;

}


