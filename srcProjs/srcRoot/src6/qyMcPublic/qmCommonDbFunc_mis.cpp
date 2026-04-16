
#include	"stdafx.h"
//#include	<afxdb.h>
#include	<windowsx.h>
#include	<winsock2.h>
#include	<vfw.h>
#include	<time.h>

#include	"qmCommon.h"
#include	"qyDbCommon.h"
#include	"qyTCharCommProc.h"
#include	"myDb.h"

#ifdef  __isCli__
		#include	"qyMcMainCommon.h"	
#endif
#if  defined(  __DLL_isCliHelp__  )  ||  defined(  __DLL_qyMessenger_help__  )
		#include	"ctxQmc.h"
#endif





 //int  qisRegUsrInfoInTab(  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  QY_MESSENGER_INFO  *  pMessengerInfo,  QY_MESSENGER_REGINFO  *  pRegInfo,  LPCTSTR  tabName  )
 int  qisRegUsrInfoInTab(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  QY_MESSENGER_INFO  *  pMessengerInfo,  QY_MESSENGER_REGINFO  *  pRegInfo,  LPCTSTR  tabName  )
{
	 int						iErr										=	-1;
#if  0
	 CString					sqlStr;
	 int						i;
	 int						iQwmVer										=	0;
	 CDBVariant					varVals[5];
	 unsigned  char				ucbAudited									=	FALSE;
	 unsigned  char				ucbReged									=	FALSE;
	 TCHAR						tBuf[1024];
	 char						idStr[CONST_qyMessengerIdStrLen  +  1]		=	"";
#endif
#ifdef  __DEBUG__
	 //traceLogA(  "qisRegUsrInfoInTab enters"  );
#endif

	 
	 //
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs  &g_dbFuncs  =  *pDbFuncs;


	 if  (  !pRegInfo  )  goto  errLabel;
	 if  (  !pMessengerInfo  )  {
		 if  (  !bMessengerIdValid(  &pRegInfo->addr.idInfo  )  )  goto  errLabel;
		}
	 else  {
		   if  (  !bMessengerIdValid(  &pMessengerInfo->idInfo  )  )  goto errLabel;
		   pRegInfo->addr.idInfo.ui64Id  =  pMessengerInfo->idInfo.ui64Id;
	 }

	 //  if  (  !idInfo2Str(  &pRegInfo->addr.idInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;

	 getCurTime(  pRegInfo->tLastModifiedTime  );

	 MACRO_setPtrs(  pFieldIdTable,  pRegInfo[0],  pRegInfo->fields  );
	 for  (  int i  =  0;  i  <  CONST_qnmMaxRegFields;  i  ++  )  {
		  if  (  pRegInfo->fields[i].bufSize  )  pRegInfo->fields[i].ptr[pRegInfo->fields[i].bufSize  -  1]  =  0;
	 }

	 
	 //

	 if  (  !g_dbFuncs.pf_bIdInfoExistedInImObjRegInfoTab(  pDb,  iDbType,  &pRegInfo->addr.idInfo,  tabName  )  )  {
		 if  (  g_dbFuncs.pf_insertImObjRegInfo_qisRegUsrInfoInTab(  pDb,  iDbType,  pRegInfo,  tabName  )  )  goto  errLabel;
		 iErr  =  0;  goto  errLabel;  
	 }


	 if  (  g_dbFuncs.pf_updateImObjRegInfo_qisRegUsrInfoInTab(  pDb,  iDbType,  pRegInfo,  tabName  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:

#ifdef  __DEBUG__
	 //traceLogA(  "qisRegUsrInfoInTab leaves"  );
#endif

	 return  iErr;

}



   __declspec(  dllexport  )  int  logEvent_is(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_MESSENGER_INFO  *  pMessengerInfo,  QIS_EVENT  *  pEvent  )
{	 
	int							iErr			=  -1;
	static  long				slHelpRand		=	0;

	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;

	getCurTime(  pEvent->cntEventTime  );
	
	switch  (  pEvent->lEventType  )  {
			case  CONST_qyEventType_im_connErr:
				  if  (  !bIpValid(  pEvent->detectedIp  )  )  goto  errLabel;
				  pEvent->lHelpRand  =  slHelpRand;  slHelpRand  ++  ;		//  
				  break;
			case  CONST_qyEventType_im_memoryErr:
				  break;
			case  CONST_qyEventType_im_daemonStart:
			case  CONST_qyEventType_im_daemonStop:
				  break;
			case  CONST_qyEventType_im_messengerLogon:
			case  CONST_qyEventType_im_messengerLogoff:
				  pEvent->lHelpRand  =  slHelpRand;  slHelpRand  ++  ;
				  if  (  pMessengerInfo  )  {
						safeStrnCpy(  pMessengerInfo->detectedIp,  pEvent->detectedIp,  mycountof(  pEvent->detectedIp  )  );
						safeStrnCpy(  pMessengerInfo->ip,  pEvent->ip,  mycountof(  pEvent->ip  )  );
						//
						lstrcpyn(  pEvent->misServName,  pMessengerInfo->misServName,  mycountof(  pEvent->misServName  )  );
						pEvent->idInfo.ui64Id  =  pMessengerInfo->idInfo.ui64Id;
				  }
				  //
				  if  (  g_dbFuncs.pf_getEventInfoBySth(  pDb,  iDbType,  pEvent  )  )  {
						#ifdef  __DEBUG__
								traceLog(  _T(  "logEvent_is failed. getEventInfoBySth failed"  )  );
						#endif
						goto  errLabel;				  
				  }
				  break;
			default:
					if  (  pMessengerInfo  )  {
						safeStrnCpy(  pMessengerInfo->detectedIp,  pEvent->detectedIp,  mycountof(  pEvent->detectedIp  )  );
						safeStrnCpy(  pMessengerInfo->ip,  pEvent->ip,  mycountof(  pEvent->ip  )  );
						//
						lstrcpyn(  pEvent->misServName,  pMessengerInfo->misServName,  mycountof(  pEvent->misServName  )  );
						pEvent->idInfo.ui64Id  =  pMessengerInfo->idInfo.ui64Id;
					}
					//
					if  (  g_dbFuncs.pf_getEventInfoBySth(  pDb,  iDbType,  pEvent  )  )  {
						#ifdef  __DEBUG__
								traceLog(  _T(  "logEvent_is failed. getEventInfoBySth failed"  )  );
						#endif
						goto  errLabel;
					}
				  	break;
	}

	if  (  !g_dbFuncs.pf_bLogEventFunc_is(  pDbFuncs,  pDb,  iDbType,  pEvent  )  )  goto  errLabel;

	iErr  =  0;

errLabel:

	return  iErr;

}


#ifdef  __isCli__
     __declspec(  dllexport  )  int  logImMsg_isCli(  void  *  pDb,  int  iDbType,  void  *  pDBManager,  QY_DMITEM  *  pFieldIdTable,  IM_MSG_RCD  *  pRcd  );
#endif

    __declspec(  dllexport  )  int  logImMsg(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  void  *  pDBManager,  QY_DMITEM  *  pFieldIdTable,  IM_MSG_RCD  *  pRcd  )
{
	int				iErr											=	-1;

	//
	if  (  !pDbFuncs  )  return  -1;
	 QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;

#ifdef  __isCli__
		return  logImMsg_isCli(  pDb,  iDbType,  pDBManager,  pFieldIdTable,  pRcd  );
#endif
		

	if  (  g_dbFuncs.pf_bSelectImMsg_logImMsg(  pDb,  iDbType,  pFieldIdTable,  pRcd  )  )  {
		iErr  =  0;  goto  errLabel;
	}


	if  (  g_dbFuncs.pf_insertImMsg_logImMsg(  pDbFuncs,  pDb,  iDbType,  pFieldIdTable,  pRcd  )  )  goto  errLabel;

	iErr  =  0;
errLabel:
	return  iErr;

}


//__declspec(  dllexport  )  int  recoverImGrp(  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  unsigned  int  uiObjType,  IM_GRP_INFO  *  pGrpInfo,  time_t  tLastModifiedTime,  BOOL  bNoGrpName  )
__declspec(  dllexport  )  int  recoverImGrp(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  unsigned  int  uiObjType,  IM_GRP_INFO  *  pGrpInfo,  time_t  tLastModifiedTime,  BOOL  bNoGrpName  )
{
	 int				iErr										=  -1;

	 if  (  !pDbFuncs  )  return  -1;
	 QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;
#if  0
	 TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1]			=	_T(  ""  );
	 char				timeBuf[CONST_qyTimeLen  +  1];
	 char				idStr[CONST_qyMessengerIdStrLen  +  1];
#endif

	 if  (  !pGrpInfo  )  return  -1;

#if  0
	 if  (  !idInfo2Str(  &pGrpInfo->idInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
	 getCurTime(  timeBuf  );
#endif
	 //  再在qyImObjTab中记录
	 QY_MESSENGER_INFO	objInfo;
	 //
	 if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pDbFuncs,  pDb,  iDbType,  pFieldIdTable,  pGrpInfo->misServName,  &pGrpInfo->idInfo,  0,  &objInfo,  0,  0,  0  )  )  { 

		 if  (  g_dbFuncs.pf_insertImObj_recoverImGrp(  pDb,  iDbType,  uiObjType,  pGrpInfo,  tLastModifiedTime  )  )  goto  errLabel;
		 }
	 else  {
		   if  (  objInfo.uiType  !=  uiObjType  ||  objInfo.iStatus  !=  CONST_qyStatus_ok  )  {

			   if  (  g_dbFuncs.pf_updateImObj_recoverImGrp(  pDb,  iDbType,  uiObjType,  pGrpInfo,  tLastModifiedTime,  objInfo.iRcdId  )  )  goto  errLabel;
		   }
		   else  {
			      if  (  tLastModifiedTime  )  {			      
					  if  (  g_dbFuncs.pf_updateImObj_recoverImGrp2(  pDb,  iDbType,  uiObjType,  pGrpInfo,  tLastModifiedTime,  objInfo.iRcdId  )  )  goto  errLabel;
				  }
			     
		   }
	 }


	 //	 如果没有组名，那就只修复上面的imObjTab. 2014/02/03
	 if  (  bNoGrpName  )  {
		 #ifdef  __DEBUG__
				 traceLog(  _T(  "recoverImGrp: no grpInfo, skipped"  )  );
		 #endif
		 }
	 else  {

		 IM_GRP_INFO	grpInfo  =  {0};

		 //  再在qyImGrpInfoTab留下组名
		 if  (   !g_dbFuncs.pf_bGetImGrpInfoBySth(  pDb,  iDbType,  pGrpInfo->misServName,  &pGrpInfo->idInfo,  &grpInfo  )  )  {

			 g_dbFuncs.pf_insertImGrp_recoverImGrp(  pDb,  iDbType,  pGrpInfo  );

			}
		 else  {
			   if  (  (  pGrpInfo->name[0]  &&  lstrcmpi(  pGrpInfo->name,  grpInfo.name  )  )
				   ||  pGrpInfo->usSubtype  !=  grpInfo.usSubtype
				   ||  pGrpInfo->idInfo_creator.ui64Id  !=  grpInfo.idInfo_creator.ui64Id  )  
			  {
				   g_dbFuncs.pf_updateImGrp_recoverImGrp(  pDb,  iDbType,  pGrpInfo,  grpInfo.id  );
			   }
		 }
	 }
		 
	 iErr  =  0;
errLabel:
	 return  iErr;
}


//  
int  recoverImGrpMem(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  IM_GRP_MEM  *  pGrpMem,  time_t  tLastModifiedTime  )
{
	 int				iErr										=  -1;

	 if  (  !pDbFuncs  )  return  -1;
	 QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;
	 //
	 TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1]			=	_T(  ""  );
	 char				timeBuf[CONST_qyTimeLen  +  1];

	 if  (  !pGrpMem  )  return  -1;
	 
	 getCurTime(  timeBuf  );

	 //  
	 IM_GRP_MEM			objInfo;
	 //
	 if  (  !g_dbFuncs.pf_bGetImGrpMemBySth(  pDb,  iDbType,  pGrpMem->misServName,  &pGrpMem->idInfo_grp,  &pGrpMem->idInfo_mem,  0,  &objInfo  )  )  {

		 //  if  (  g_dbFuncs.pf_insertImGrpMem_recoverImGrpMem(  pDb,  iDbType,  pGrpMem  )  )  goto  errLabel;
		 if  (  g_dbFuncs.pf_insertImGrpMem_recoverImGrpMem(  pDb,  iDbType,  pGrpMem,  tLastModifiedTime  )  )  goto  errLabel;
		 }
	 else  {
		   if  (  objInfo.iRole  !=  pGrpMem->iRole  ||  objInfo.iStatus  !=  pGrpMem->iStatus  )  {

			   //  if  (  g_dbFuncs.pf_updateImGrpMem_recoverImGrpMem(  pDb,  iDbType,  pGrpMem,  objInfo.id  )  )  goto  errLabel;
			   if  (  g_dbFuncs.pf_updateImGrpMem_recoverImGrpMem(  pDb,  iDbType,  pGrpMem,  tLastModifiedTime,  objInfo.id  )  )  goto  errLabel;
		   
			   }
		   else  {

			      if  (  tLastModifiedTime  )  {			   
					  if  (  g_dbFuncs.pf_updateImGrpMem_recoverImGrpMem2(  pDb,  iDbType,  pGrpMem,  tLastModifiedTime,  objInfo.id  )  )  goto  errLabel;
				  }
			     
		   }
	 }
		 
	 iErr  =  0;
errLabel:
	 return  iErr;
}


 __declspec(  dllexport  )  int  recoverMessenger(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  QY_MESSENGER_INFO  *  pObj,  QY_MESSENGER_REGINFO  *  pRegInfo,  time_t  tLastModifiedTime,  BOOL  bLog,  GENERIC_Q  *  pLogQ  )
{
	 int						iErr											=	-1;
	 //
	   //
#if  10
	 if  (  !pDbFuncs  )  {
		 #ifdef  __DEBUG__
				 traceLog(  _T(  "recoverMessenger failed, p_g_dbFuncs is null"  )  );
		 #endif
		 return  -1;
	 }
	 QM_dbFuncs  &  g_dbFuncs  =  *(  QM_dbFuncs  *  )pDbFuncs;
#endif
	 //
#if 0
	 TCHAR						sqlBuf[CONST_maxSqlBufLen  +  1];
#endif			
	 QY_MESSENGER_INFO			messengerInfo;

	 char						ip12Buf[CONST_qyMaxIpLen  +  1]					=	"";					//  2007/02/20
	 char						detectedIp12Buf[CONST_qyMaxIpLen  +  1]			=	"";
	 char						idStr[CONST_qyMessengerIdStrLen  +  1]			=	"";
	 char						startTimeBuf[CONST_qyTimeLen  +  1]				=	"";
	 char						tLastModifiedTimeBuf[CONST_qyTimeLen  +  1]		=	"";

	 if  (  !pObj  &&  !pRegInfo  )  return  -1;


	 //
	 if  (  !pObj  )  {
		 memset(  &messengerInfo,  0,  sizeof(  messengerInfo  )  );
		 //
		 lstrcpyn(  messengerInfo.misServName,  pRegInfo->addr.misServName,  mycountof(  messengerInfo.misServName  )  );
		 messengerInfo.idInfo.ui64Id  =  pRegInfo->addr.idInfo.ui64Id;
		 messengerInfo.uiType  =  pRegInfo->addr.uiObjType;		//  CONST_objType_messenger;
		 messengerInfo.iStatus  =  0;			
		 //
		 pObj  =  &messengerInfo;
	 }

	 if  (  !pObj  ||  !bMessengerIdValid(  &pObj->idInfo  )  )  goto  errLabel;

	 if  (  !pObj->startTime  )  time(  &pObj->startTime  );
	 if  (  !pObj->tLastModifiedTime  )  time(  &pObj->tLastModifiedTime  );
	 
	 //
	 if  (  !idInfo2Str(  &pObj->idInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
	 //
	 getTimeStr(  pObj->startTime,  startTimeBuf,  mycountof(  startTimeBuf  )  );
	 getTimeStr(  pObj->tLastModifiedTime,  tLastModifiedTimeBuf,  mycountof(  tLastModifiedTimeBuf  )  );
	 //		    
	 qyStdToIp12(  pObj->ip,  ip12Buf  );	//  2007/02/20
	 qyStdToIp12(  pObj->detectedIp,  detectedIp12Buf  );
	 
	 //
	 //  2012/07/15

	 //
	 QY_MESSENGER_INFO		rcd;

	 if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pDbFuncs,  pDb, iDbType,  pFieldIdTable,  pObj->misServName,  &pObj->idInfo,  0,  &rcd,  NULL,  NULL,  NULL  )  )  {  

		 if  (  g_dbFuncs.pf_insertImObj_recoverMessenger(  pDbFuncs,  pDb,  iDbType,  pObj,  tLastModifiedTime  )  )  goto  errLabel;

		 if  (  bLog  )  {
			 if  (  postEvent2Log_is(  pObj->misServName,  CONST_qyEventType_im_newMessenger,  pObj->detectedIp,  pObj->ip,  &pObj->idInfo,  NULL,  pLogQ  )  )  traceLogA(  "postEvent2Log_is failed."  );
		 }
	 
		}
	 else  {
		   //if  (  rcd.uiType  !=  CONST_objType_me  )  
		   {
			   if  (  rcd.uiType  !=  pObj->uiType  ||  rcd.iRole  !=  pObj->iRole  ||  pObj->iStatus  !=  rcd.iStatus  )  {

				   if  (  g_dbFuncs.pf_updateImObj_recoverMessenger(  pDb,  iDbType,  pObj,  tLastModifiedTime,  rcd.iRcdId  )  )  goto  errLabel;
			   }
			   else  {
				     if  (  tLastModifiedTime  )  {
						 if  (  g_dbFuncs.pf_updateImObj_recoverMessenger2(  pDb,  iDbType,  pObj,  tLastModifiedTime,  rcd.iRcdId  )  )  goto  errLabel;
					 }
			   }
		   }
	 }

	 if  (  pRegInfo  )  {

		 g_dbFuncs.pf_qisRegUsrInfo(  pDbFuncs,  pDb,  iDbType,  pFieldIdTable,  pObj,  pRegInfo,  bLog  );

	 	 g_dbFuncs.pf_recoverMessengerPhoneInfo(  pDbFuncs,  pDb,  iDbType,  &pRegInfo->addr,  0  );
	 
	 }

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
		 traceLogA(  "recoverMessenger failed."  );
	 }
	 return  iErr;

}

    //  2010/08/15
 __declspec(  dllexport  )  int  recoverImObjRules(  QM_dbFuncs  *  pDbFuncs,  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRules_req	*	pReq,  time_t  tLastModifiedTime  )
{
	 int						iErr											=	-1;

	 if  (  !pDbFuncs  )  return  -1;
	 QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;
	 #if  0
	 char						idStr[CONST_qyMessengerIdStrLen  +  1]			=	"";
	 char						idStr_related[CONST_qyMessengerIdStrLen  +  1]	=	"";
	 TCHAR						sqlBuf[CONST_maxSqlBufLen  +  1];
	 time_t						t;
	 char						startTimeBuf[CONST_qyTimeLen  +  1]				=	"";
	 char						tLastModifiedTimeBuf[CONST_qyTimeLen  +  1]		=	"";
	 #endif		

	 if  (  !misServName  ||  !bMessengerIdValid(  pIdInfo  )  )  goto  errLabel;
	 #if  0
	 if  (  !idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;

	 if  (  !tLastModifiedTime  )  time(  &t  );
	 else  t  =  tLastModifiedTime;
	 getTimeStr(  t,  startTimeBuf,  mycountof(  startTimeBuf  )  );
	 getTimeStr(  t,  tLastModifiedTimeBuf,  mycountof(  tLastModifiedTimeBuf  )  );
	 #endif		    

	 QY_imObjRule_rcd		rcd;

	 for  (  int  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {
		  //  if  (  !pReq->mems[i].idInfo_related.ui64Id  )  continue;
		  if  (  !pReq->mems[i].uiRuleType  )  continue;

		  #if  0
			   idInfo2Str(  &pReq->mems[i].idInfo_related,  idStr_related,  mycountof(  idStr_related  )  );
		  #endif

		  if  (  !g_dbFuncs.pf_bGetImObjRuleRcdBySth(  pDb, iDbType,  misServName,  pIdInfo,  &pReq->mems[i],  0,  &rcd  )  )  {  
			  
			  if  (  !pReq->mems[i].uiCmd  )  continue;

			  if  (  g_dbFuncs.pf_insertImObjRule_recoverImObjRules(  pDb,  iDbType,  misServName,  pIdInfo,  &pReq->mems[i],  tLastModifiedTime  )  )  goto errLabel;
			  }	
		  else  {

			    if  (  !pReq->mems[i].uiCmd  )  {

					if  (  g_dbFuncs.pf_deleteImObjRule_recoverImObjRules(  pDb,  iDbType,  misServName,  pIdInfo,  &pReq->mems[i],  rcd.id  )  )  goto  errLabel;

					continue;
				}
				if  (  rcd.uiCmd  !=  pReq->mems[i].uiCmd
					||  lstrcmpi(  rcd.col0,  pReq->mems[i].wDesc  )  )  
				{				

					if  (  g_dbFuncs.pf_updateImObjRule_recoverImObjRules(  pDb,  iDbType,  misServName,  pIdInfo,  &pReq->mems[i],  tLastModifiedTime,  rcd.id  )  )  goto  errLabel;

					continue;	//  2013/06/19
				}
				if  (  tLastModifiedTime  )  {

					if  (  g_dbFuncs.pf_updateImObjRule_recoverImObjRules2(  pDb,  iDbType,  misServName,  pIdInfo,  &pReq->mems[i],  tLastModifiedTime,  rcd.id  )  )  goto  errLabel;
				}
				continue;
		  }
	 
	 }

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
		 traceLogA(  "recoverImObjRules failed."  );
	 }
	 return  iErr;

}


 int  postEvent2Log_is(  LPCTSTR  misServName,  long  lEventType,  char  *  detectedIp,  char  *  ip,  QY_MESSENGER_ID  *  pIdInfo,  QIS_EVENT  *  pEventInput,  GENERIC_Q  *  pLogQ  ) 
{
	int						iErr			=	-1;
	MIS_MSG_EVENT			msg;
	
	if  (  !misServName  ||  !pLogQ  )  return  -1;
	if  (  isQFull(  pLogQ  )  )  return  -1;		//  队列满了就没法记了

	memset(  &msg,  0,  sizeof(  msg  )  );
	msg.uiType  =  CONST_misMsgType_event;
	if  (  pEventInput  )  memcpy(  &msg.event,  pEventInput,  sizeof(  msg.event  )  );
	msg.event.lEventType  =  lEventType;
	lstrcpyn(  msg.event.misServName,  misServName,  mycountof(  msg.event.misServName  )  );
	safeStrnCpy(  detectedIp,  msg.event.detectedIp,  mycountof(  msg.event.detectedIp  )  );
	safeStrnCpy(  ip,  msg.event.ip,  mycountof(  msg.event.ip  )  );
	if  (  pIdInfo  )  msg.event.idInfo.ui64Id  =  pIdInfo->ui64Id;

	getCurTime(  msg.event.localEventTime  );
	getCurTime(  msg.event.cntEventTime  );
	//
	if  (  qPostMsgAndTrigger(  &msg,  sizeof(  msg  ),  pLogQ,  _T(  "postEvent2Log_is"  )  )  )  goto  errLabel;

	iErr  =  0;

errLabel:

	return  iErr;
			
}

























