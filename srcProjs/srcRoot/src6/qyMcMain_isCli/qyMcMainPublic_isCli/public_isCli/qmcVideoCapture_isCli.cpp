

#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>


#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
//  #include	"qmcVideoCapture_isCli.h"
//#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"
#include	"qmcDmoPublic.h"
#include	"qmcCmdProc.h"
#include	"tmpCeLib.h"
//  #include	"myfourcc.h"
#include	"module_qisCamCap.h"
#include	"isCmdConst.h"
#include	"qyOpenShellCommon.h"
#include	"qyCusResTemp.h"
#include	"policyAvParams.h"

//#include	"isCliHelpPublic.h"
//#include	"dlgShareDynBmpsProc.h"
//#include	"isClid3dpublic.h"
#include	"qmcTaskPublic.h"

#include	"qmcCommFunc_isCli.h"
#include	"qmcCfg.h"

#include	"qmcVideoCapture_isCli.h"





//  2014/10/31
int  getVal_bExists_sharedObjUsr(  MC_VAR_common  *  pProcInfo,  int  iIndex_sharedObj,  BOOL  *  pbExists  )
{
	int  iErr  =  -1;
	BOOL  bExists  =  FALSE;
	
	//  
	if  (  !pbExists  )  return  -1;

	QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  return  -1;
	
	if  (  !bSharedObjActive(  pProcInfo,  iIndex_sharedObj  )  )  return  -1;

	int  j;	
	for  (  j  =  0;  j  <  mycountof(  pSharedObj->usrs  );  j  ++  )  {			
		 SHARED_OBJ_USR	*	pSharedObjUsr  =  &pSharedObj->usrs[j];
		 
		 if  (  !IsWindow(  pSharedObjUsr->hWnd_starter  )  )  continue;
		 
		 //  2014/10/31		
		 if  (  pSharedObj->usSubtype  ==  CONST_sharedObjSubtype_mosaic  )  {					  
			 BOOL  tmp_bExists  =  FALSE;
			 if  (  getVal_bExists_taskInWnd(  pProcInfo->pQyMc,  pSharedObjUsr->iTaskId,  pSharedObjUsr->hWnd_starter,  &tmp_bExists  )  )  goto  errLabel;  

			 if  (  !tmp_bExists  )  continue;				
			 				  
			 break;
		 }


		 QY_WMBUF_COMM	wmBuf;		
		 memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
		 wmBuf.uiType  =  CONST_qyWmParam_chkSharedObject;
		 wmBuf.u.chkSharedObject.iIndex_sharedObject  =  iIndex_sharedObj;
		 wmBuf.u.chkSharedObject.iTaskId  =  pSharedObjUsr->iTaskId;	//  2014/12/23
		 if  (  CONST_qyWmRc_ok  !=  SendMessage(  pSharedObjUsr->hWnd_starter,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  )  )  goto  errLabel;		 	
		 if  (  wmBuf.u.chkSharedObject.bNotExists  )  {						  
			 continue;						  					  			 
		 }
		 //
		 break;			
	}

	if  (  j  <  mycountof(  pSharedObj->usrs  )  )  bExists  =  TRUE;
		
	iErr  =  0;

errLabel:

	if  (  !iErr  )  {
		*pbExists  =  bExists;
	}
	
	return  iErr;

}


//
  int  tryToFreeSharedObjs(  MC_VAR_isCli  *  pProcInfo )
{

	if  (  !pProcInfo  )  return  -1;
	QY_MC					*		pQyMc				=	(  QY_MC  *  )pProcInfo->pQyMc;	//  
	if  (  !pQyMc  )  return  -1;
	

	#ifdef  __DEBUG__
			traceLogA(  (char*)  "tryToFreeSharedObjs(  ) enters"  );
	#endif

	//
	for  (  int  index  =  0;  index  <  pProcInfo->cfg.usMaxCnt_pSharedObjs;  index  ++  )  {
		 QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  index  );

		 if  (  !pSharedObj->bUsed  )  continue;
		
		 //  try to find sharedObj whick need be stopped
		 if  (  bSharedObjActive(  pProcInfo,  index  )  )  {

			 //
			 BOOL  tmp_bExists  =  FALSE;
			 if  (  !getVal_bExists_sharedObjUsr(  pProcInfo,  index,  &tmp_bExists  )  )  {
				 if  (  !tmp_bExists  )  {
					 #ifdef  __DEBUG__
							 traceLogA(  (char*)  "tryToFreeSharedObjs: objs[%d] no hWnd_starter, shall be stopped.",  index  );
					 #endif
					 askSharedObjToStop(  pProcInfo,  pSharedObj,  NULL,  _T(  "tryToFreeSharedObjs. no usr"  )  );
				 }
			 }

		 }
		
		 //
		 if  (  !bSharedObjActive(  pProcInfo,  index  )  )  {
			 #ifdef  __DEBUG__
					 traceLog((TCHAR*)  _T(  "freeSharedObjByIndex(  ): index is %d\n"  ),  index  );	
			 #endif

			 //
			 freeSharedObjByIndex(  pProcInfo,  index  );	
			 continue;
		 }

		 //
		 continue;
	}

	#ifdef  __DEBUG__
			traceLogA(  (char*)  "tryToFreeSharedObjs(  ) leaves"  );
	#endif

	return  0;
}

  //
  int freeAllSharedObjs(CCtxQmc  *  pProcInfo)
  {
	  int  i;
	  for (i = 0; i < pProcInfo->cfg.usMaxCnt_pSharedObjs; i++) {
		  QY_SHARED_OBJ* pSharedObj = getSharedObjByIndex(pProcInfo, i);
		  if (!pSharedObj->bUsed) {
			  //
			  if (pSharedObj->bQuit) {
				  pSharedObj->bQuit = false;
			  }
			  //
			  continue;
		  }
		  pSharedObj->bQuit = true;
		  continue;
	  }
	  tryToFreeSharedObjs(pProcInfo);
	  tryToFreeSharedObjs(pProcInfo);

	  return  0;
  }



  //
BOOL  bNoSharedObjExists(  MC_VAR_isCli  *  pProcInfo  )
{
	//int								iServiceId			=	CONST_qyServiceId_mis;
	//QY_SERVICEGUI_INFO		*		pSci				=	getServiceGuiInfo(  pQyMc,  iServiceId  );
	//
	//MC_VAR_isCli				*		pProcInfo			=	(  MC_VAR_isCli  *  )pSci->pVar;
	//
	if  (  !pProcInfo  )  return  FALSE;
	QY_MC					*		pQyMc				=	(  QY_MC  *  )pProcInfo->pQyMc;
	if  (  !pQyMc  )  return  FALSE;

	//
	int								i;

	if  (  !pProcInfo  )  return  TRUE;
	if  (  !pProcInfo->pSharedObjSyncs  )  return  TRUE;

	for  (  i  =  0;  i  <  pProcInfo->cfg.usMaxCnt_pSharedObjs;  i  ++  )  {
		 QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  i  );
		 if  (  pSharedObj->bUsed  )  return  FALSE;
	}

	return  TRUE;
}


 void  stopAll_sharedObjs(  MC_VAR_isCli  *  pProcInfo  )
 {
	if  (  !pProcInfo  )  return;
	QY_MC					*		pQyMc				=	(  QY_MC  *  )pProcInfo->pQyMc;	//
	if  (  !pQyMc  )  return;

	//
	if  (  !pProcInfo->pSharedObjSyncs  )  return;

	int								i;
	
	for  (  i  =  0;  i  <  pProcInfo->cfg.usMaxCnt_pSharedObjs;  i  ++  )  {
		 QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  i  );
		 askSharedObjToStop(  pProcInfo,  pSharedObj,  NULL,  _T(  "stopAll_sharedObjs"  )  );
	}

	return;
}


 int  newCapProcInfoBmpIndex(  MC_VAR_isCli  *  pProcInfo,  int  iIndex_sharedObj  )
{
	if  (  iIndex_sharedObj  <  0  ||  iIndex_sharedObj  >=  pProcInfo->cfg.usMaxCnt_capProcInfoBmps  )  return  -1;
	return  iIndex_sharedObj;
}

 int  newCapProcInfoAudioIndex(  MC_VAR_isCli  *  pProcInfo,  int  iIndex_sharedObj  )
{
	if  (  iIndex_sharedObj  <  0  ||  iIndex_sharedObj  >=  pProcInfo->cfg.usMaxCnt_capProcInfoAudios  )  return  -1;
	return  iIndex_sharedObj;
}






 
 



