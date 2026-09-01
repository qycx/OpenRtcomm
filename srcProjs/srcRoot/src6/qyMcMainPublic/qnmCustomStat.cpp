
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"resource.h"
#include	"qyCommon.h"
#include	"qyGuiCommonEx.h"
#include	"qyWmComm.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommCommon.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qyLangCommProc.h"
#include	"qnmCustom.h"
#include	"qnmCustomGui.h"
#include	"qyCusResPublic.h"





 //  定制一些东西  
 int  myCustomStat(  int  iSystemId,  QNM_CUSRES_INFO  *  pCusRes,  QNM_CUSTOM_COMM	*	pCustom,  void  *  p1  )
{
	QY_MC		*	pQyMc				=	QY_GET_GBUF(  );
 	QY_DMITEM	*	pTable				=	getResTable(  0,  &pQyMc->cusRes,  CONST_resId_myCONST_yhGrpTable_netMc  );
	QY_DMITEM	*	pEventYhGrpTable	=	(  iSystemId  ==  CONST_qySystemId_secChk  )  ?  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_myCONST_yhGrpTable_netMc  )  :  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_myCONST_eventYhGrpTable_netMc  );
	int				i					=	0;
	QY_DMITEM	*	pgYhGrpTable		=	getResTable(  0,  pCusRes,  CONST_resId_gYhGrpTable  );
	QY_DMITEM	*	pgEventYhGrpTable	=	getResTable(  0,  pCusRes,  CONST_resId_gEventYhGrpTable  );

	switch  (  qyGetServiceId(  iSystemId  )  )  {
			case  CONST_qyServiceId_is:
				  pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_myCONST_yhGrpTable_is  );
				  pEventYhGrpTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_myCONST_eventYhGrpTable_is  );
				  break;
			default:
					break;
	}

	for  (  ;  pTable->type  !=  -1;  pTable  ++  )  {
		 if  (  pTable->type  >=  pCustom->nDwLevels  )  continue;
		 if  (  i  >=  CONST_maxnYhGrpTable  )  break;
		 memcpy(  &pgYhGrpTable[i],  pTable,  sizeof(  pgYhGrpTable[i]  )  );
		 i  ++  ;
	}
	pgYhGrpTable[i].type  =  -1;

	i  =  0;
	for  (  ;  pEventYhGrpTable->type  !=  -1;  pEventYhGrpTable  ++  )  {
		 if  (  pEventYhGrpTable->type  >=  pCustom->nDwLevels  )  continue;
		 if  (  i  >=  CONST_maxnYhGrpTable  )  break;
		 memcpy(  &pgEventYhGrpTable[i],  pEventYhGrpTable,  sizeof(  pgEventYhGrpTable[i]  )  );
		 i  ++  ;
	}
	pgEventYhGrpTable[i].type  =  -1;
  
	return  0;
}


