
#include	"stdafx.h"
#include	<tchar.h>
#include	"qyMcMainCommon.h"
#include	"MyDb.h"


 //  


 //  2012/07/12
 int  initQyMcDb(  void  *  p0,  void  *  p1,  QY_OBJ_DB  *  pObj  )
{
	 int			iErr	=	-1;

	 if  (  !pObj  )  return  -1;
	 if  (  pObj->ucbLoaded  )  return  -1;

	 //  
	 if  (  pObj->cfg.iDbType  ==  CONST_dbType_myDb  )  {  //  2012/07/14
		 try  {
			  #include	"undeclareDebugNew.h"
			  pObj->pDb  =  new  CMyDb;
			  #include	"declareDebugNew.h"
			  if  (  !pObj->pDb  )  goto  errLabel;
			  CMyDb  *  pDb  =  (  CMyDb  *  )pObj->pDb;
			  if  (  !pDb->bQyOpenDb(  pObj->cfg.connectStr  )  )  goto  errLabel;
			  //
			  }
#ifdef  __useMfc__
		 catch  (  CException  *  e  )  {
			   e->Delete(  );
			   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initQyMcDb failed."  )  );
			   goto  errLabel;				
		 }
#endif
		 catch  (  ...  )  {
			   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initQyMcDb failed."  )  );
			   goto  errLabel;				
		 }

		 //
		 if  (  CQnmDb::makeDbPool_myDb(  pObj->pDb,  8,  pObj->iDsnIndex  )  )  goto  errLabel;

		 }
	 else  {

		 try  {  
	
			  pObj->pDb  =  qyNewDb(  );	//  new  CDatabase;
			  if  (  !pObj->pDb  )  goto  errLabel;
			  if  (  !bQyOpenDb(  pObj->cfg.connectStr,  pObj->pDb  )  )  {
				  debugLog( (char*)"localDb.OpenEx( %s ) failed.", pObj->cfg.connectStr );
				  goto errLabel;
			  }
			 }
#ifdef  __useMfc__
		catch  (  CException  *  e  )  {
			   e->Delete(  );
			   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initQyMcDb failed."  )  );
			   goto  errLabel;
		}
#endif
		catch  (  ...  )  {
			   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initQyMcDb failed."  )  );
			   goto  errLabel;
		}

		//
		if  (  CQnmDb::makeDbPool(  pObj->cfg.connectStr,  8,  pObj->iDsnIndex  )  )  goto  errLabel;
	 }


	//  traceLogA( "localDb.OpenEx( %s ) success.", pQyMc->cfg.db.connectStr  );
	traceLogA( (char*)"localDb.OpenEx( ) success."  );


	iErr = 0;

errLabel:

	if  (  iErr  )  {

		exitQyMcDb(  p0,  p1,  pObj  );
	
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "qyMc"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initQyMcDb failed"  )  );
	}

	if  (  !iErr  )  {
		pObj->ucbLoaded  =  TRUE;

		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "qyMc"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initQyMcDb ok"  )  );
	}

	return  iErr;

}



 void  exitQyMcDb(  void  *  p0,  void  *  p1,  QY_OBJ_DB  *  pObj  )
{
	 CQnmDb::freeDbPool(  pObj->iDsnIndex  );	//  2007/01/02

	 if  (  pObj->pDb  )  {
		 if  (  pObj->cfg.iDbType  ==  CONST_dbType_myDb  )  {
			 CMyDb  *  pDb  =  (  CMyDb  *  )pObj->pDb;
			 pDb->qyCloseDb(  );
			 delete  pDb;
			 pObj->pDb  =  NULL;
			 }
		 else  {
#if  0
			   CDatabase *pDb = ( CDatabase * )pObj->pDb;

			   qyCloseDb(  pDb  );  
			   delete  pDb;  
			   pObj->pDb  =  NULL;
#endif
			   qyFreeDb(  &pObj->pDb  );
		 }
	 }
	 pObj->ucbLoaded  =  FALSE;
	 
}


 //
 int  exitProcedObjDbs(  QY_MC  *  pQyMc  )
{
	int				i;
	QY_OBJ_DB	*	pObj;

	//
	if  (  !pQyMc  )  return  -1;

	//
	for  (  i  =  0;  i  <  (  int  )getProcedObjDbsMaxCnt(  pQyMc  );  i  ++  )  {
		 pObj  =  &getProcedObjDbs(  pQyMc  )[i];
		 /*
		 if  (  pObj->pDb  )  {
			 qyCloseDb(  pObj->pDb  );  
			 delete  (  CDatabase  *  )pObj->pDb;							//  2006/12/24, CDatabase  *  delete 
			 pObj->pDb  =  NULL;
		 }	
		 pObj->ucbLoaded  =  FALSE;
		 */
		 exitQyMcDb(  0,  0,  pObj  );
	}

	return  0;
}

 






 







 











