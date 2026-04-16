
#include	"stdafx.h"

#include	<stdlib.h>
#include	<tchar.h>

#ifndef  __WINCE__
	#include	<Winsock2.h>
	#include	<vfw.h>

	#include	<time.h>

#else
	#include	<Winsock2.h>
	#ifdef  __TEST__
			#include	<vfw.h>
	#endif
	#include	<mmreg.h>
	#include	<MSAcm.h>
	#include	<time.h>
#endif

#include	"qmCommon.h"
#include	"qmObjQProc.h"

#include	"tmpCeLib.h"



 int  getQmObjQMaxCnt(  void  *  pLicenseCtx,  int  iObjQType  )
{

	 if  (  iObjQType  ==  CONST_objQType_misClient  )  return  CONST_qmObjQMaxCnt_misClient;

#if  !defined(  __isCli__  )  &&  !defined(  __APP_qyMc_touchscreen__  )
	 if  (  iObjQType  ==  CONST_objQType_mis  )  {
		 unsigned  int  nMaxMessengers	=	qnmMaxMessengers0(  (  QY_LICENSE_CTX  *  )pLicenseCtx  );
		 unsigned  int	nMaxGrps	=	0;
		 unsigned  int  nMaxTmpMessengers  =  CONST_maxTmpMessengers;			//  2007/12/18.
		 //
		 //  nMaxGrps  =  (  unsigned  int  )(  0.2  *  nMaxMessengers  );
		 nMaxGrps  =  qnmMaxImGrps(  (  QY_LICENSE_CTX  *  )pLicenseCtx  );
		 if  (  nMaxGrps  <  10  )  nMaxGrps  =  10;
		 //
		 return  nMaxGrps  +  nMaxMessengers  +  nMaxTmpMessengers  +  10;
	 }

	 return  qnmMaxPcs(  (  QY_LICENSE_CTX  *  )pLicenseCtx  )  +  10;
#else
	 return  0;
#endif
}



__declspec(  dllexport  )  int  initQmObjQ(  void  *  p0,  void  *  pLicenseCtx,  int  iObjQType,  LPCTSTR  qName,  LPCTSTR  mutexName,  LPCTSTR  semaName,  unsigned  uiMaxCnt_sema,  
				PF_compare_qmObjQ  pfCompare,  PF_commonHandler  pfExitQMemObj,  PF_fillQmObjMemInfo  pfFillQmObjMemInfo,  PF_commonHandler  tmp_pfAddToQmObjQ,
				QM_OBJQ  *  pQParam  )
{
	 int			iErr	=	-1;
	 QM_OBJQ	*	pQ		=	(  QM_OBJQ  *  )pQParam;
	 CQySyncObj		syncObj;
	 unsigned  int	size	=	0;

	 if  (  !pQ  )  return  -1;
	 if  (  !iObjQType  ||  !mutexName  ||  !semaName  )  return  -1;
	 if  (  uiMaxCnt_sema  <=  1  )  return  -1;

	 if  (  syncObj.sync(  mutexName  )  )  goto  errLabel;

	 memset(  pQ,  0,  sizeof(  pQ  )  );
	 //
	 pQ->iType  =  iObjQType;
	 if  (  qName  )  lstrcpyn(  pQ->name,  qName,  mycountof(  pQ->name  )  );
	 pQ->uiMaxCnt_sema  =  uiMaxCnt_sema;
	 pQ->uiInitCnt_sema  =  pQ->uiMaxCnt_sema  -  1;	//  这里比最大的少一个，是为了在 exit时，能用releaseSemaphore来加一个，并取得一个当前的值

	 _sntprintf(  pQ->mutexName,  mycountof(  pQ->mutexName  ),  _T(  "%s"  ),  mutexName  );
#if  0
	 pQ->hSema  =  CreateSemaphore(  0,  pQ->uiInitCnt_sema,  pQ->uiMaxCnt_sema,  semaName  ); 
	 if  (  !pQ->hSema  )  goto  errLabel;
#else
	 pQ->pRw  =  new  CMutexRW(  );
	 if  (  !pQ->pRw  )  goto  errLabel;
#endif

	 //
	 pQ->maxCnt  =  getQmObjQMaxCnt(  pLicenseCtx,  iObjQType  );
	 size  =  pQ->maxCnt  *  sizeof(  QM_OBJQ_MEM  );
	 pQ->pMems  =  (  QM_OBJQ_MEM  *  )mymalloc(  size  );
	 if  (  !pQ->pMems  )  goto  errLabel;
	 memset(  pQ->pMems,  0,  size  );
	 //
	 pQ->uiMilliSeconds_mutex_r  =  10000;
	 pQ->uiMilliSeconds_sema_r  =  10000;
	 pQ->uiMilliSeconds_mutex_w  =  10000;
	 pQ->uiMilliSeconds_sema_w  =  10000;

	 //
	 pQ->pfCompare  =  pfCompare;
	 pQ->pfExitQMemObj  =  pfExitQMemObj;
	 pQ->pfFillQmObjMemInfo  =  pfFillQmObjMemInfo;
	 pQ->tmp_pfAddToQmObjQ  =  tmp_pfAddToQmObjQ;
	 
	 iErr  =  0;

errLabel:
	 
	 if  (  iErr  )  {
		 if  (  pQ->pMems  )  {  free(  pQ->pMems  );  pQ->pMems  =  NULL;  }
		 pQ->maxCnt  =  0;
#if  0
		 if  (  pQ->hSema  )  {
			 CloseHandle(  pQ->hSema  );  pQ->hSema  =  0;  
		 }
#else
		 MACRO_safeDelete(  pQ->pRw  );
#endif
		 pQ->iType  =  0;
	 }


	 traceLogA(  "initQmObjQ: %S %s",  pQ->name,  iErr  ?  "failed"  :  "ok"  );

	 return  iErr;

}


 //  其他操作申请时，就是waitForSingleObject前，应该取得mutex, 然后waitFor，然后关掉mutex；在release是，不用了。
 //  这是为了用releaseSemaphore取得当前记数时，不再有waitFor在运行
 __declspec(  dllexport  )  void  exitQmObjQ(  void  *  p0,  QM_OBJQ  *  pQParam  )
{
	 int			iErr	=	-1;
	 QM_OBJQ	*	pQ		=	(  QM_OBJQ  *  )pQParam;
	 long			i;

	 if  (  !pQ  ||  !pQ->iType  )  return;
	 
	 //
#ifdef  __DEBUG__
	 //printQmObjQ(  pQ  );
#endif

	 //
	 if  (  pQ->pMems  )  {
		 CQyRWLock	syncObj;
		 //
#if  0
		 if  (  syncObj.wLock(  pQ->mutexName,  pQ->uiMilliSeconds_mutex_w,  pQ->hSema,  pQ->uiMilliSeconds_sema_w,  pQ->uiInitCnt_sema  )  )  goto  errLabel;
#else
		 if  (  syncObj.wLock(  pQ->pRw,  pQ->uiMilliSeconds_sema_w  )  )  goto  errLabel;
#endif

		 for  (  i  =  0;  i  <  (  long  )pQ->cnt;  i  ++  )  {	//  2007/04/20, 注意这里要释放
			  if  (  pQ->pMems[i].pQMemObj  )  {
				  if  (  pQ->pfExitQMemObj  )  pQ->pfExitQMemObj(  0,  0,  pQ->pMems[i].pQMemObj  );
				  free(  pQ->pMems[i].pQMemObj  );
		 	  }		 	  
		 }
		 free(  pQ->pMems  );  pQ->pMems  =  NULL;  
	 }
	 pQ->maxCnt  =  0;
#if  0
	 if  (  pQ->hSema  )  {
		 CloseHandle(  pQ->hSema  );  pQ->hSema  =  0;  
	 }
#else
	 MACRO_safeDelete(  pQ->pRw  );
#endif

	 pQ->iType  =  0;

	 traceLogA(  "exitQmObjQ: %S",  pQ->name  );

errLabel:

	 return;

}

 int __cdecl myCompare_mac( const void * key, const void * pMemParam) 
{
	 QM_OBJQ_MEM  *  pMem  =  (  QM_OBJQ_MEM  *  )pMemParam;

	 return  _stricmp( (  const  char  *  )key,  (  (  QMEM_PC  *  )pMem->pQMemObj  )->mac );
}


 static  int  sfindNetMcQMemByMac(  void  *  p0,  void  *  pQParam,  char  *  mac,  QM_OBJQ_MEM  *  pMemParam  )
{
	 int					iErr	=	-1;
	 QM_OBJQ			*	pQ		=	(  QM_OBJQ  *  )pQParam;
	 int					i		=	0;
	 unsigned  int			cnt		=	0;
	 QM_OBJQ_MEM		*	pMem	=	NULL;

	 if  (  !pQ->pfCompare  )  return  -1;

	 cnt  =  min(  pQ->maxCnt,  pQ->cnt  );	//  防止越界

	 pMem  =  (  QM_OBJQ_MEM  *  )bsearch(  mac,  pQ->pMems,  cnt,  sizeof(  pQ->pMems[0]  ),  pQ->pfCompare  );
	 if  (  !pMem  )  goto  errLabel;

	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 if  (  pMemParam  )  memcpy(  pMemParam,  pMem,  sizeof(  QM_OBJQ_MEM  )  );
	 }
	 return  iErr;;
}


 __declspec(  dllexport  )  int  tmp_findMisQMemById(  void  *  p0,  void  *  pQParam,  void  *  pKeyInfo,  QM_OBJQ_MEM  *  pMemParam  )
{
	 int					iErr	=	-1;
	 QM_OBJQ			*	pQ		=	(  QM_OBJQ  *  )pQParam;
	 int					i		=	0;
	 unsigned  int			cnt		=	0;
	 QM_OBJQ_MEM		*	pMem	=	NULL;

	 if  (  !pQ->pfCompare  )  return  -1;

	 cnt  =  min(  pQ->maxCnt,  pQ->cnt  );	//  防止越界

	 pMem  =  (  QM_OBJQ_MEM  *  )bsearch(  pKeyInfo,  pQ->pMems,  cnt,  sizeof(  pQ->pMems[0]  ),  pQ->pfCompare  );
	 if  (  !pMem  )  goto  errLabel;

	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 if  (  pMemParam  )  memcpy(  pMemParam,  pMem,  sizeof(  QM_OBJQ_MEM  )  );
	 }
	 return  iErr;
}


 //  2007/04/05
/*
 static  int  sfindMisQMemById(  void  *  p0,  void  *  pQParam,  QY_MESSENGER_ID  *  pIdInfo,  QM_OBJQ_MEM  *  pMemParam  )
{
	 int					iErr	=	-1;
	 QM_OBJQ			*	pQ		=	(  QM_OBJQ  *  )pQParam;
	 int					i		=	0;
	 unsigned  int			cnt		=	0;
	 QM_OBJQ_MEM		*	pMem	=	NULL;

	 cnt  =  min(  pQ->maxCnt,  pQ->cnt  );	//  防止越界

	 pMem  =  (  QM_OBJQ_MEM  *  )bsearch(  pIdInfo,  pQ->pMems,  cnt,  sizeof(  pQ->pMems[0]  ),  myCompare_mis  );
	 if  (  !pMem  )  goto  errLabel;

	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 if  (  pMemParam  )  memcpy(  pMemParam,  pMem,  sizeof(  QM_OBJQ_MEM  )  );
	 }
	 return  iErr;
}
*/





//  注意：下面2个函数是加了rwLock的，但是sfind...是一个辅助函数，没有rwLock对内存的保护
 __declspec(  dllexport  )  int  findQMemByKey(  void  *  p0,  void  *  pQParam,  void  *  pKeyInfo,  QM_OBJQ_MEM  *  pMemParam  )
{
	 int					iErr	=	-1;
	 QM_OBJQ			*	pQ		=	(  QM_OBJQ  *  )pQParam;
	 CQyRWLock				syncObj;

	 if  (  !pQ  ||  !pKeyInfo  )  return  -1;

#if  0
	 if  (  syncObj.rLock(  pQ->mutexName,  pQ->uiMilliSeconds_mutex_r,  pQ->hSema,  pQ->uiMilliSeconds_sema_r  )  )  goto  errLabel;
#else
	 if  (  syncObj.rLock(  pQ->pRw,  pQ->uiMilliSeconds_sema_r  )  )  goto  errLabel;
#endif

	 switch  (  pQ->iType  )  {
			 case  CONST_objQType_netMc:
				   return  sfindNetMcQMemByMac(  p0,  pQParam,  (  char  *  )pKeyInfo,  pMemParam  );
			 case  CONST_objQType_mis:
			 case  CONST_objQType_misClient:
				   return  tmp_findMisQMemById(  p0,  pQParam,  (  QY_MESSENGER_ID  *  )pKeyInfo,  pMemParam  );
			 default:
					break;
					
	 }
errLabel:
	 return  -1;
}


 __declspec(  dllexport  )  int  findQMemByObj(  void  *  p0,  void  *  pQParam,  void  *  pClient,  QM_OBJQ_MEM  *  pMem  )
{
	 int					iErr	=	-1;
	 QM_OBJQ			*	pQ		=	(  QM_OBJQ  *  )pQParam;
	 CQyRWLock		syncObj;
	 
	 if  (  !pQ  ||  !pClient  )  return  -1;

#if  0
	 if  (  syncObj.rLock(  pQ->mutexName,  pQ->uiMilliSeconds_mutex_r,  pQ->hSema,  pQ->uiMilliSeconds_sema_r  )  )  goto  errLabel;
#else
	 if  (  syncObj.rLock(  pQ->pRw,  pQ->uiMilliSeconds_sema_r  )  )  goto  errLabel;
#endif

	 switch  (  pQ->iType  )  {
		     case  CONST_objQType_netMc:
				   return  sfindNetMcQMemByMac(  p0,  pQParam,  (  (  QNM_PC_INFO  *  )pClient  )->macs[0],  pMem  );
			 case  CONST_objQType_mis:
			 case  CONST_objQType_misClient:  
				   return  tmp_findMisQMemById(  p0,  pQParam,  &(  (  QY_MESSENGER_INFO  *  )pClient  )->idInfo,  pMem  );
			 default:
					goto  errLabel;
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
}


 __declspec(  dllexport  )  BOOL  bQmObjQFull(  void  *  p0,  void  *  pQParam  )
{
	 QM_OBJQ			*	pQ		=	(  QM_OBJQ  *  )pQParam;

	 return  pQ->cnt  >=  pQ->maxCnt;
}



 int  fillQmObjMemInfo_netMc(  QY_SERVICE_INFO  *  pSci,  void  *  pQParam,  void  *  pDb,  int  iDbType,  QNM_PC_INFO  *  pPcInfo,  QM_OBJQ_MEM  *  pMem  )
{
	 int				iErr			=	-1;
	 QMEM_PC		*	pMemPc			=	0;
	 QY_DMITEM		*	pFieldIdTable	=	CONST_fieldIdTable_en;

	 //
	 if  (  !pSci  )  return  -1;
	 //  CQyMcDaemon  *  pDaemon  =  pSci->pParent;
	 QM_dbFuncs  *  pDbFuncs  =  NULL;
	 if  (  !pDbFuncs  )  {
		 #ifdef  __DEBUG__
				 MACRO_qyAssert(  0,  _T(  "fillQmObjMemInfo_netMc failed, pDbFuncs is null"  )  );
		 #endif
		 return  -1;
	 }


	 //
	 memset(  pMem,  0,  sizeof(  pMem[0]  )  );
	 pMem->iType  =  0;	//  暂时不用
	 //
	 pMemPc  =  (  QMEM_PC  *  )mymalloc(  sizeof(  pMemPc[0]  )  );
	 if  (  !pMemPc  )  goto  errLabel;
	 memset(  pMemPc,  0,  sizeof(  pMemPc[0]  )  );
	 //
	 safeStrnCpy(  pPcInfo->macs[0],  pMemPc->mac,  sizeof(  pMemPc->mac  )  );
	 pMemPc->ulIp  =  inet_addr(  pPcInfo->ip  );
	 time_t  t;
	 mytime(  &t  );  pMemPc->lLastCommTime  =  (  long  )t;			//  取最近联系时间

	 //  这里填写一下其他的信息，比如实时操作等策略
	 PC_STATUS_INFO	pcStatus;
	 memset(  &pcStatus,  0,  sizeof(  pcStatus  )  );
	 if  (  getPcStatusInfo(  pDbFuncs,  pDb,  pMemPc->mac,  pFieldIdTable,  &pcStatus  )  )  memset(  &pcStatus,  0,  sizeof(  pcStatus  )  );

	 QNM_CMDPARAM_getOpCmd	cmdParam;

	 memset(  &cmdParam,  0,  sizeof(  cmdParam  )  );
	 cmdParam.ucbOped  =  pcStatus.ucbOped;				//  2006/03/23
	 cmdParam.ucbViewRemoteDesktop  =  pcStatus.ucbOped  &&  pcStatus.ucbViewRemoteDesktop;	 
	 cmdParam.ucbMonDesktop  =  pcStatus.ucbOped  &&  pcStatus.ucbMonDesktop;				//  2006/03/06  

	 memcpy(  &pMemPc->getOpCmd,  &cmdParam,  sizeof(  cmdParam  )  );

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
		 if  (  pMemPc  )  free(  pMemPc  );
	 }
	 if  (  !iErr  )  {
		 pMem->pQMemObj  =  pMemPc;
	 }

	 return  iErr;
}







/*
 int  fillQmObjMemInfo(  QY_SERVICE_INFO  *  pSci,  void  *  pQParam,  void  *  pDb,  int  iDbType,  void  *  pClient,  QM_OBJQ_MEM  *  pMem  )
{
	 QM_OBJQ			*	pQ		=	(  QM_OBJQ  *  )pQParam;

	 switch  (  pQ->iType  )  {
			 case  CONST_objQType_netMc:
				   return  fillQmObjMemInfo_netMc(  pSci,  pQParam,  pDb,  iDbType,  (  QNM_PC_INFO  *  )pClient,  pMem  );
			 case  CONST_objQType_mis:
				   return  fillQmObjMemInfo_mis(  pSci,  pQParam,  pDb,  iDbType,  (  QY_MESSENGER_INFO  *  )pClient,  pMem  );
			 default:
					break;
					
	 }

	 return  -1;
}
*/


 int  tmp_addToQmObjQ_netMc(  void  *  p0,  QM_OBJQ_MEM  *  tmppMem,  void  *  pQParam  )	//  add失败，可以当作严重后果，可以要求daemon重起
{
	 int					iErr	=	-1;
	 QM_OBJQ			*	pQ		=	(  QM_OBJQ  *  )pQParam;
	 //  CQySyncObj				syncObj;	 
	 QM_OBJQ_MEM		*	pMem	=	0;
	 int					iRet;
	 int					i;


	 //  if  (  syncObj.sync(  pQ->mutexName  )  )  goto  errLabel;

	 if  (  !sfindNetMcQMemByMac(  p0,  pQParam,  (  (  QMEM_PC  *  )tmppMem->pQMemObj  )->mac,  NULL  )  )  {
		 //  iErr  =  0;	//  2007/09/03
		 goto  errLabel;	//  在这里调用一次，以防止多线程同时加入MAC
	 }
	 if  (  bQmObjQFull(  p0,  pQParam  )  )  {
		 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  ""  )  );
		 goto  errLabel;					//  防止越界
	 }

	 if  (  !pQ->cnt  )  {
		 //  pMem  =  pQ->pMems;
		 memcpy(  pQ->pMems,  tmppMem,  sizeof(  pQ->pMems[0]  )  );
		 pQ->cnt  ++  ;
		 iErr  =  0;  goto  errLabel;
	 }

	 for  (  i  =  pQ->cnt  -  1;  i  >=0;  i  --  )  {					//  队列按升序存放
		  iRet  =  _stricmp(  (  (  QMEM_PC  *  )tmppMem->pQMemObj  )->mac,  (  (  QMEM_PC  *  )pQ->pMems[i].pQMemObj  )->mac  );
		  if  (  !iRet  )  {
			  //traceLogA(  "这是错误的，不应该出现"  );  
			  goto  errLabel;
		  }
		  if  (  iRet  <  0  )  {
			  memcpy(  &pQ->pMems[i  +  1],  &pQ->pMems[i],  sizeof(  pQ->pMems[0]  )  );
			  continue;
		  }
		  pMem  =  &pQ->pMems[i  +  1];						//  发现了比该MAC小的，于是放在后面
		  memcpy(  pMem,  tmppMem,  sizeof(  pQ->pMems[0]  )  );
		  pQ->cnt  ++  ;
		  iErr  =  0;  goto  errLabel;
	 }

	 pMem  =  &pQ->pMems[0];		//  这里是发现找完队列，也没有比该MAC小的，只好放最前面了
	 memcpy(  pMem,  tmppMem,  sizeof(  pQ->pMems[0]  )  );
	 pQ->cnt  ++  ;
	 iErr  =  0;  

errLabel:

	 return  iErr;	 

}






 int  addToQmObjQ(  void  *  p0,  QM_OBJQ_MEM  *  tmppMem,  void  *  pQParam,  PF_commonHandler  tmp_pfAddToQmObjQ  )	//  add失败，可以当作严重后果，可以要求daemon重起
{
	 QM_OBJQ			*	pObjQ  =  (  QM_OBJQ  *  )pQParam;
	 CQyRWLock				syncObj;

#if  0
	 if  (  syncObj.wLock(  pObjQ->mutexName,  pObjQ->uiMilliSeconds_mutex_w,  pObjQ->hSema,  pObjQ->uiMilliSeconds_sema_w,  pObjQ->uiInitCnt_sema  )  )  goto  errLabel;
#else
	 if  (  syncObj.wLock(  pObjQ->pRw,  pObjQ->uiMilliSeconds_sema_w  )  )  goto  errLabel;
#endif

	 /*
	 switch  (  pObjQ->iType  )  {
			 case  CONST_objQType_netMc:
				   return  saddToQmObjQ_netMc(  p0,  tmppMem,  pQParam  );
			 case  CONST_objQType_mis:
				   return  tmp_addToQmObjQ_mis(  p0,  tmppMem,  pQParam  );
			 case  CONST_objQType_misClient:
				   return  saddToQmObjQ_misClient(  p0,  tmppMem,  pQParam  );
			 default:
					break;
					
	 }
	 */

	 if  (  tmp_pfAddToQmObjQ  )  return  tmp_pfAddToQmObjQ(  p0,  tmppMem,  pQParam  );

errLabel:
	 return  -1;


}


  __declspec(  dllexport  )  int  procQmObjQ(  void  *  pServiceInfo,  QM_OBJQ  *  pObjQ,  void  *  pDb,  int  iDbType,  int  iObjType,  void  *  pClient,  QM_OBJQ_MEM  *  pMem  )
{
	 int						iErr			=	-1;
	 QM_OBJQ_MEM				mem;
	 time_t						t;
	 

	 switch  (  iObjType  )  {
			 case  CONST_objType_pc:
				   if  (  !bMacValid(  (  (  QNM_PC_INFO  *  )pClient  )->macs[0]  )  )  goto  errLabel;
				   break;
			 case  CONST_objType_me:
			 case  CONST_objType_admin:
			 case  CONST_objType_messenger:
			 case  CONST_objType_imGrp:
			 case  CONST_objType_tmpMsgr:	//  2018/11/11
				   break;
			 default:
					#ifdef  __DEBUG__
							traceLog(  _T(  "procQmObjQ failed:  unprocessed iObjType %d"  ),  iObjType  );  
					#endif
					goto  errLabel;					
					break;
	 }

	 if  (  !findQMemByObj(  0,  pObjQ,  pClient,  &mem  )  )  {
		 mytime(  &t  );
		 switch  (  iObjType  )  {
				 case  CONST_objType_messenger:
		 			   //  (  (  QMEM_MESSENGER  *  )mem.pQMemObj  )->lLastCommTime  =  t;	//  
					   //  2007/06/09, 
					   break;
				 default:
						break;
		 }
		 iErr  =  0;  goto  errLabel;
	 }

#ifdef  __DEBUG__
		traceLogA(  "procQmObjQ: not found in objQ, so will be add to objQ"  );
		//  printQmObjQ(  pObjQ  );
#endif

	 if  (  !pObjQ->pfFillQmObjMemInfo  )  goto  errLabel;	 					
	 if  (  (  (  PF_fillQmObjMemInfo  )pObjQ->pfFillQmObjMemInfo  )(  pServiceInfo,  pObjQ,  pDb,  iDbType,  pClient,  &mem  )  )  goto  errLabel;
	 //
	 if  (  addToQmObjQ(  0,  &mem,  pObjQ,  pObjQ->tmp_pfAddToQmObjQ  )  )  goto  errLabel;		//  add失败，可以当作严重后果，可以要求daemon重起

	 iErr  =  0;

errLabel:
	 
	 if  (  iErr  )  {
		 //  2007/04/22, 注意，这里可以fillQmObjMemInfo成功了，而add失败，这里，应该将在fillQm中分配的内存给释放掉。
		 //  还没做
	 }
	 if  (  !iErr  )  {
		 if  (  pMem  )  memcpy(  pMem,  &mem,  sizeof(  pMem[0]  )  );
	 }

#ifdef  __DEBUG__
		//  printQmObjQ(  pObjQ  );
#endif

	 return  iErr;
}

  __declspec(  dllexport  )  int  qmObjQTraverse(  void  *  pServiceInfo,  void  *  pQParam,  PF_commonHandler pf_visit,  void  *  p0,  void  *  p1  )
{
	 int					iErr	=	-1;
	 QM_OBJQ			*	pQ		=	(  QM_OBJQ  *  )pQParam;
	 CQyRWLock				syncObj;
	 int					i;
	 int					tmpiRet	=	-1;

	 if  (  !pQ  )  return  -1;

#if  0
	 if  (  syncObj.rLock(  pQ->mutexName,  pQ->uiMilliSeconds_mutex_r,  pQ->hSema,  pQ->uiMilliSeconds_sema_r  )  )  goto  errLabel;
#else
	 if  (  syncObj.rLock(  pQ->pRw,  pQ->uiMilliSeconds_sema_r  )  )  goto  errLabel;
#endif

	 for  (  i  =  0;  i  <  pQ->cnt;  i  ++  )  {
		 tmpiRet  =  (  *  pf_visit  )(  p0,  p1,  &pQ->pMems[i]  );
		 if  (  tmpiRet  )  {
			 iErr  =  tmpiRet;  goto  errLabel;
		 }	
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}

 __declspec(  dllexport  )  int  printQmObjQ(  QM_OBJQ  *  pQ  )
{
	
#ifdef  __DEBUG__

	    //return  0;

		traceLogA(  "start to print QM_OBJQ ..."  );
		unsigned  int								i;
		char				*						p;
		char	timeBuf[128];

		if  (  !pQ  )  return  -1;

		traceLogA(  "\tmaxCnt is %d",  pQ->maxCnt  );		//  最多容纳个数；这同时意味着分配的空间大小=maxCnt  *  sizeof(  QM_OBJQ_MEM  )
		traceLogA(  "\tcnt is %d",  pQ->cnt  );				//  有效个数

		if  (  pQ->pfPrintQ  )  pQ->pfPrintQ(  0, 0,  pQ  );
		else  {

			  switch  (  pQ->iType  )  {
				      case  CONST_objQType_netMc:
					  
						   for  (  i  =  0;  i  <  pQ->cnt;  i  ++  )  {
						   	    p  =  inet_ntoa(  *(  struct  in_addr  *  )&(  (  QMEM_PC  *  )pQ->pMems[i].pQMemObj  )->ulIp  );
						   		getTimeStr(  (  (  QMEM_PC  *  )pQ->pMems[i].pQMemObj  )->lLastCommTime,  timeBuf,  sizeof(  timeBuf  )  );
						   		traceLogA(  "\t第%d个pc的mac is %s, ip is %s, lastCommTime is %s",  i,  (  (  QMEM_PC  *  )pQ->pMems[i].pQMemObj  )->mac,  p  ?  p  :  "",  timeBuf  );
					  	   }
					  	   break;
					  default:
						      break;
			  }

		}

		traceLogA(  "end printing QM_OBJQ ..."  );

#endif
	 return  0;
}



 int  tmpHandler_procMisMsg_moreData(  void  *  p0,  void  *  p1,  void  *  pMsgElemParam  )
{
	int					iErr			=	-1;
	BOOL				bFindOnly		=	(  BOOL  )p0;
	MIS_MSG_INPUT	*	pMsgInput		=	(  MIS_MSG_INPUT  *  )p1;
	MIS_MSG_INPUT	*	pMsgElem		=	(  MIS_MSG_INPUT  *  )pMsgElemParam;
	//
	
	if  (  pMsgInput->tStartTime  ==  pMsgElem->tStartTime  
		&&  pMsgInput->uiTranNo  ==  pMsgElem->uiTranNo  )
	{
		//  found

		if  (  bFindOnly  )  {			//  这里用来寻找某类包。可以用来删除包等
			iErr  =  1;  goto  errLabel;
		}

		//
#ifdef  __DEBUG__

#endif

		//
		if  (  pMsgInput->usSeqNo  !=  pMsgElem->usSeqNo  +  1  )  {	//  
			//
			traceLogA(  "tmpHandler_procMisMsg_moreData: usSeqNo error"  );  
			#if  10
				 TCHAR  tBuf[128];
				 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "tmpHandler_procMisMsg_moreData: usSeqNo error, input.sn %d != 1+ msgElem.sn %d"  ),  (int)pMsgInput->usSeqNo,  (int)pMsgElem->usSeqNo  );
				 showInfo_open0(  0,  0,  tBuf  );
			#endif
			//
			goto  errLabel;
		}
		if  (  pMsgInput->lenInBytes  +  pMsgElem->lenInBytes  >  sizeof(  MIS_MSG_routeTalkData  )  )  {
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "procMoreData failed: 存储空间不够，数据太长了， tranNo [%d], seqNo [%d]"  ),  pMsgInput->uiTranNo,  (  int  )pMsgInput->usSeqNo  );
			traceLogA(  "tmpHandler_procMisMsg_moreData: failed"  );  goto  errLabel;
		}
		memcpy(  (  (  char  *  )&pMsgElem->data  )  +  pMsgElem->lenInBytes,  (  char  *  )&pMsgInput->data,  pMsgInput->lenInBytes  );
		pMsgElem->lenInBytes  +=  pMsgInput->lenInBytes;
		pMsgElem->usSeqNo  =  pMsgInput->usSeqNo;	//  

		//  traceLogA(  "uiSeqNo [%d] ",  pMsgInput->uiSeqNo  );

		if  (  !isUcFlgMoreData(  pMsgInput->ucFlg  )  )  {	//  
			memcpy(  (  char  *  )&pMsgInput->data,  &pMsgElem->data,  pMsgElem->lenInBytes  );
			pMsgInput->lenInBytes  =  pMsgElem->lenInBytes;
			pMsgInput->usSeqNo  =  0;		

			//  traceLogA(  "tmpHandler_procMisMsg_moreData;  "  );
		}

		iErr  =  1;  goto  errLabel;
	}

	iErr  =  0;
errLabel:
	return  iErr;
}

 //  当ucFlg的CONST_commFlg_moreData为0时，表明包发完了
 //  当不为0时，放在cacheQ里
 //  当为0时，如uiSeqNo为0，则是独立包。如不为0，则从cacheQ里取出所有的tStartTime和tranNo相同的包，按uiSeqNo组成一个完整包。
 // 
 //  这里的包，限制在一个MIS_MSG_TALK的buf里。
 //  对更大的包，也许要用队列或其他来表示了。暂不考虑. 或者，应该在客户端自己在内容数据里来分拆合并了
 __declspec(  dllexport  )  int  procMisMsg_moreData(  GENERIC_Q  *  pCacheQ,  MIS_MSG_INPUT  *  pMsgInput,  BOOL  *  pbMsgSkipped  )
{
	int							iErr				=	-1;
	BOOL						bMsgSkipped			=	FALSE;

	int							tmpiRet;

	//  当Q满时，简单的处理是将队列清空
	if  (  isQFull(  pCacheQ  )  )  emptyGenericQ(  pCacheQ  );

	if  (  isUcFlgMoreData(  pMsgInput->ucFlg  )  )  {		//  找到前面的包加进去

		tmpiRet  =  qTraverse(  pCacheQ,  tmpHandler_procMisMsg_moreData,  0,  pMsgInput  );
		if  (  tmpiRet  <  0  )  {  
			qRemoveMsg(  pCacheQ,  tmpHandler_procMisMsg_moreData,  0,  pMsgInput  );
			}
		if  (  !tmpiRet  )  {  //  没找到就要加进去. 注意，在这里要将整个MIS_MSG_INPUT都放进去，是因为需要将后面的数据都跟在msg的data里
			if  (  qPostMsg(  pMsgInput,  sizeof(  MIS_MSG_INPUT  ),  pCacheQ,  _T(  "procMisMsg_moreData"  )  )  )  goto  errLabel;						
		}		
		iErr  =  0;  goto  errLabel;
	}

	if  (  !pMsgInput->usSeqNo  )  {	//  这是指不需要在这里处理的
		iErr  =  0;  goto  errLabel;
	}

	//  要准备把数据取出来，放到pMsgInput中

	tmpiRet  =  qTraverse(  pCacheQ,  tmpHandler_procMisMsg_moreData,  0,  pMsgInput  );
	if  (  tmpiRet  )  qRemoveMsg(  pCacheQ,  tmpHandler_procMisMsg_moreData,  (  void  *  )TRUE,  pMsgInput  );
	if  (  tmpiRet  <=  0  )  {
		bMsgSkipped  =  TRUE;
		iErr  =  0;  goto  errLabel;
	}

	iErr  =  0;

errLabel:

	if  (  !iErr  )  {
		if  (  pbMsgSkipped  )  *pbMsgSkipped  =  bMsgSkipped;
	}

	if  (  iErr  )  {	//  2011/01/24
		#ifdef  __DEBUG__
				traceLog(  _T(  "procMisMsg_moreData failed"  )  );
		#endif
	}

	return  iErr;
}



