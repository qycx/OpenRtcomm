

#include	"stdafx.h"
#include	<tchar.h>
#include	"shlobj.h"
#ifndef  __WINCE__
		 //#include	"myresource.h"
#endif
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#ifdef  __isCli__
		#include	"qmcCommFunc_iscli.h"
#endif
#include	"qyVDev.h"





  int  getSelectPartFromColumns(  int  nSqlFields,  QY_COLUMNINFO  *  pSqlColumns,  TCHAR  *  selectPart,  unsigned  int  size  )
{
	int		iErr  =  -1;
	int		i;
	
	for  (  i  =  0;  i  <  nSqlFields;  i  ++  )  {
		 //  if  (  !myTChar2Str(  pSqlColumns[i].label,  buf,  sizeof(  buf  )  )  )  goto  errLabel;
		 if  (  !i  )  _sntprintf(  selectPart,  size,  _T(  "select %s"  ),  pSqlColumns[i].label  );
		 else  _sntprintf(  selectPart,  size,  _T(  "%s,%s"  ),  selectPart,  pSqlColumns[i].label  );
	}
	//  traceLogA(  (char*)  "selectPart is %s",  selectPart  );
	iErr  =  0;

//  errLabel:
	return  iErr;
}

  int  setQueryColumns(  QY_MC  *  pQyMc,  void  *  p0,  QNM_QUERY_STRUCT  *  pQueryStruct,  QY_MC_QUERY  *  pQuery  )
{
	 int					iErr			=	-1;
	 //QY_MC				*	pQyMc			=	QY_GET_GBUF(  );
	 QNM_CUSTOM_COMM	*	pCustom			=	&pQyMc->cfg.custom;
	 QY_COLUMNINFO		*	pSql			=	NULL;
	 QY_COLUMNINFO		*	pDisplay		=	NULL;
	 int					i				=	0;

	 if  (  !pQueryStruct  ||  !pQueryStruct->pSql  ||  !pQueryStruct->pDisplay  )  return  -1;

	 for  (  i  =  0;  ;  i  ++  )  {
		  pSql  =		&pQueryStruct->pSql[i];  
		  pDisplay	=	&pQueryStruct->pDisplay[i];
		  if  (  pSql->type  ==  -1  ||  pDisplay->type  ==  -1  )  break;
		  if  (  bFieldLikeDw(  pSql->type  )  &&  pSql->ucLevel  >=  pCustom->nDwLevels  )  continue;
		  if  (  bFieldLikeZcbh(  pSql->type,  0  )  &&  pSql->ucLevel  >=  pCustom->nZcbhs  )  continue;
		  if  (  pQuery->nSqlFields  >=  CONST_qyMaxQueryCols  -  1  ||  pQuery->nFields  >=  CONST_qyMaxQueryCols  -  1  )  {
			  //
			  //traceLogA(  (char*)  "setQueryColumns failed: CONST_qyMaxQueryCols太小了"  );  
			  //
			  goto  errLabel;
		  }
		  memcpy(  &pQuery->sqlColumns[pQuery->nSqlFields],  pSql,  sizeof(  QY_COLUMNINFO  )  );
		  pQuery->nSqlFields  ++  ;
		  memcpy(  &pQuery->columns[pQuery->nFields],  pDisplay,  sizeof(  QY_COLUMNINFO  )  );
		  pQuery->nFields  ++  ;		  
	 }
	 pQuery->sqlColumns[pQuery->nSqlFields].type  =  -1;
	 pQuery->columns[pQuery->nFields].type  =  -1;

	 if  (  getSelectPartFromColumns(  pQuery->nSqlFields,  pQuery->sqlColumns,  pQuery->selectPart,  sizeof(  pQuery->selectPart  )  /  sizeof(  pQuery->selectPart[0]  )  )  )  goto  errLabel;

	 iErr  =  0;
errLabel:
	 return  iErr;
}



