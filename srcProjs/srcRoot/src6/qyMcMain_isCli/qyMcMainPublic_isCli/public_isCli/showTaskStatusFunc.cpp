

#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>
#include	"qyMcMainCommon.h"
#include	"qyWnd.h"
#include	"qmcCmdProc.h"
#include	"qmcVWall.h"
#include	"dlgTalkPublic.h"
#include	"qmcVideoCapture_isCli.h"



 int  showTaskStatusFunc(  void  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_taskSender,  QY_MESSENGER_ID  *  pIdInfo_mem,  BOOL  bImGrpMem,  unsigned  short  cmdCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiContentType,  int  iTaskId,  int  iStatus,  unsigned  char  ucbNotification,  QY_MESSENGER_ID	*	pIdInfo_from,  unsigned  char  ucPercent,  unsigned  __int64  ui64Len_recvd,  LPCTSTR  fileName,  LPCTSTR  fullFilePath  )
{
	QY_MC				*	pQyMc				=	QY_GET_GBUF(  );
	//  CWnd				*	pMainWnd			=	AfxGetApp(  )->m_pMainWnd;
	MIS_MSG_TASKSTATUS		msgTaskStatus;

	//  if  (  !pIdInfo_taskSender->ui64Id  ||  !pIdInfo_taskReceiver->ui64Id  )  {
	//  	traceLogA(  "showTaskStatus err:"  );  return  -1;
	//  }
   
	//  ±¨¸æ×´Ì¬
	memset(  &msgTaskStatus,  0,  sizeof(  msgTaskStatus  )  );
	msgTaskStatus.uiType  =  CONST_misMsgType_taskStatus;
	msgTaskStatus.pMisCnt  =  pMisCnt;
	if  (  pIdInfo_logicalPeer  )  msgTaskStatus.idInfo_logicalPeer.ui64Id  =  pIdInfo_logicalPeer->ui64Id;
	//
	if  (  pIdInfo_taskSender  )  msgTaskStatus.idInfo_taskSender.ui64Id  =  pIdInfo_taskSender->ui64Id;
	if  (  pIdInfo_mem  )  msgTaskStatus.idInfo_mem.ui64Id  =  pIdInfo_mem->ui64Id;
	//
	msgTaskStatus.bImGrpMem  =  bImGrpMem;			//  
	//
	msgTaskStatus.cmdCode  =  cmdCode;				//  2009/10/18
	msgTaskStatus.tStartTime  =  tStartTime;		//  2009/10/18
	msgTaskStatus.uiTranNo  =  uiTranNo;			//  2009/10/18
	msgTaskStatus.uiContentType  =  uiContentType;	//  
	msgTaskStatus.iTaskId  =  iTaskId;
	msgTaskStatus.iStatus  =  iStatus;
	if  (  ucbNotification  )  {
		msgTaskStatus.ucbNotification  =  TRUE;
		if  (  pIdInfo_from  )  msgTaskStatus.u.notification.idInfo_from.ui64Id  =  pIdInfo_from->ui64Id;
		safeTcsnCpy(  fileName,  msgTaskStatus.u.notification.tBuf,  mycountof(  msgTaskStatus.u.notification.tBuf  )  );
		}
	else  {
		  msgTaskStatus.u.transferFileStatus.ucPercent	=	ucPercent;
		  msgTaskStatus.u.transferFileStatus.ui64Len_recvd  =  ui64Len_recvd;
		  if  (  fileName  )  lstrcpyn(  msgTaskStatus.u.transferFileStatus.fileName,  fileName,  mycountof(  msgTaskStatus.u.transferFileStatus.fileName  )  );
		  if  (  fullFilePath  )  lstrcpyn(  msgTaskStatus.u.transferFileStatus.fullFilePath,  fullFilePath,  mycountof(  msgTaskStatus.u.transferFileStatus.fullFilePath  )  );
	}

	//
#ifdef  __DEBUG__
	if (iStatus == CONST_imTaskStatus_canceledByReceiver) {
		int ii = 0;
		}
#endif 


	//
	qPostMsg(  &msgTaskStatus,  sizeof(  msgTaskStatus  ),  &pQyMc->gui.processQ,  _T(  "showTaskStatus"  ));
	PostMessage(  g_pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );    

	return  0;
}



 //
 //
 __declspec(  dllexport  )  int  showNotification_open(  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiContentType,  LPCTSTR  hint  )
{
	 CCtxQyMc* pQyMc = g_pQyMc;
	 CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	 if (pProcInfo->bAppQt()) {
		 if (uiContentType)  return 0;
	 }

	return  showTaskStatusFunc(  NULL,  NULL,  NULL,  NULL,  0,  0,  tStartTime,  uiTranNo,  uiContentType,  0,  0,  TRUE,  NULL,  0,  0,  hint,  NULL  );
}


 //
 
 __declspec(  dllexport  )  int  showNotification(  void  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiContentType,  LPCTSTR  hint  )
{
	 CCtxQyMc* pQyMc = g_pQyMc;
	 CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	 if (pProcInfo->bAppQt()) {
		 if (uiContentType)  return 0;
	 }

	return  showTaskStatusFunc(  pMisCnt,  pIdInfo_logicalPeer,  NULL,  NULL,  0,  0,  tStartTime,  uiTranNo,  uiContentType,  0,  0,  TRUE,  pIdInfo_from,  0,  0,  hint,  NULL  );
}


 //
 

 //
// int  showTaskStatusFunc(  void  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_taskSender,  QY_MESSENGER_ID  *  pIdInfo_taskReceiver,  BOOL  bImGrpMem,  unsigned  short  cmdCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiContentType,  int  iTaskId,  int  iStatus,  unsigned  char  ucbNotification,  QY_MESSENGER_ID	*	pIdInfo_from,  unsigned  char  ucPercent,  unsigned  __int64  ui64Len_recvd,  LPCTSTR  fileName,  LPCTSTR  fullFilePath  );

__declspec(  dllexport  ) int  showTaskStatus(  void  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_taskSender,  QY_MESSENGER_ID  *  pIdInfo_mem,  BOOL  bImGrpMem,  unsigned  int  uiContentType,  int  iTaskId,  int  iStatus,  unsigned  char  ucPercent,  unsigned  __int64  ui64Len_recvd,  LPCTSTR  fileName,  LPCTSTR  fullFilePath  )
{
	return  showTaskStatusFunc(  pMisCnt,  pIdInfo_logicalPeer,  pIdInfo_taskSender,  pIdInfo_mem,  bImGrpMem,  0,  0,  0,  uiContentType,  iTaskId,  iStatus,  FALSE,  NULL,  ucPercent,  ui64Len_recvd,  fileName,  fullFilePath  );
}

 __declspec(  dllexport  )  int  showTaskStatus(  void  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_taskSender,  QY_MESSENGER_ID  *  pIdInfo_mem,  BOOL  bImGrpMem,  unsigned  short  cmdCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiContentType,  int  iTaskId,  int  iStatus  )
{
	return  showTaskStatusFunc(  pMisCnt,  pIdInfo_logicalPeer,  pIdInfo_taskSender,  pIdInfo_mem,  bImGrpMem,  cmdCode,  tStartTime,  uiTranNo,  uiContentType,  iTaskId,  iStatus,  FALSE,  NULL,  0,  0,  NULL,  NULL  );
}
