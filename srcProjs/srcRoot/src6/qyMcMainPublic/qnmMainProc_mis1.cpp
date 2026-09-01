

#include	"stdafx.h"
#include	<stdio.h>
#include	<tchar.h>
#include	"qyMcMainCommon.h"

//  #include	"QyRcdset.h"

#include	"qycusrescommon.h"




 int  fillQyMcQuery(  CCtxQyMc  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  int  type,  void  *  pParam,  LPCTSTR  wherePart,  QY_MC_QUERY  *  pQuery  )
{
	int			iErr	=	-1;
	//QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	if  (  !pQuery  )  return  -1;
	QY_MC_QUERY	&	query	=	*pQuery;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	NULL;
	TCHAR				*	pTabName		=	NULL;

	memset(  pQuery,  0,  sizeof(  pQuery[0]  )  );
	pQuery->type  =  type;
	pQuery->iDsnIndex  =  pObjDb->iDsnIndex;


	switch  (  type  )  {
			case  CONST_qyQueryType_imMsgList:
				  pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  (  pObjDb->cfg.iAppType  ==  CONST_qyAppType_client  )  ?  CONST_resId_gpImMsgListQueryStruct_isClient  :  CONST_resId_gpImMsgListQueryStruct_isMgr  );
				  pTabName		=	(TCHAR*)CONST_tabName_qyImMsgTab;

				  if  (  setQueryColumns(  pQyMc,  NULL,  pQueryStruct,  &query  )  )  goto  errLabel;

				  //
				  _sntprintf(  query.fromPart,  mycountof(  query.fromPart  ),  _T(  "from (%s left join qyImObjRegInfoTab as B on (qyImMsgTab.misServName=B.misServName and qyImMsgTab.idStr_send=B.idStr) )"  ),  pTabName  );
				  //
				  if  (  wherePart  &&  wherePart[0]  )  {
					  if  (  query.wherePart[0]  )  _sntprintf(  query.wherePart,  mycountof(  query.wherePart  ),  _T(  "%s and"  ),  query.wherePart  );
					  _sntprintf(  query.wherePart,  mycountof(  query.wherePart  ),  _T(  "%s (%s)"  ),  query.wherePart,  CQyString(  wherePart  )  );
				  }
				  //
				  _sntprintf(  query.sortPart,  mycountof(  query.sortPart  ),  _T(  "qyImMsgTab.firstTime desc"  )  );
				  break;
			default:
					traceLog(  (TCHAR*)_T(  "fillQyMcQuery failed"  )  );
					goto  errLabel;
					break;
	}

	if  (  0  )  {
				
		OutputDebugString(  query.selectPart  );
		OutputDebugString(  _T(  " "  )  );
		OutputDebugString(  query.fromPart  );
		OutputDebugString(  _T(  " "  )  );
		OutputDebugString(  query.wherePart[0]  ?  _T(  "where"  )  :  _T(  ""  )  );
		OutputDebugString(  _T(  " "  )  );
		OutputDebugString(  query.wherePart  );
		OutputDebugString(  _T(  " "  )  );
		OutputDebugString(  query.sortPart[0]  ?  _T(  "order by"  )  :  _T(  ""  )  );
		OutputDebugString(  _T(  " "  )  );
		OutputDebugString(  query.sortPart  );
		OutputDebugString(  _T(  "\n"  )  );
	}

	iErr  =  0;
errLabel:
	return  iErr;
}



