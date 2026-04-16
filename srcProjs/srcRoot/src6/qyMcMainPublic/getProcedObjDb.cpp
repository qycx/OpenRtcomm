



#include	"stdafx.h"
#include	<tchar.h>
#include	"qyMcMainCommon.h"
//#include	"myresource.h"
#include	"qyCusResTemp.h"





 QY_OBJ_DB  *  getProcedObjDbs(  QY_MC  *  pQyMc  )
{
	if  (  !pQyMc  )  return  NULL;

	return  pQyMc->procedObjDbs;
}

 unsigned  int  getProcedObjDbsMaxCnt(  QY_MC  *  pQyMc  )
{
	if  (  !pQyMc  )  return  0;

	return  mycountof(  pQyMc->procedObjDbs  );
}

 
 QY_OBJ_DB  *  getProcedObjDb(  QY_MC  *  pQyMc,  void  *  p0,  int  iDsnIndex  )
{
	 if  (  !pQyMc  )  return  NULL;

	 if  (  iDsnIndex  <  0  )  return  NULL;
	 if  (  iDsnIndex  >=  (  int  )getProcedObjDbsMaxCnt(  pQyMc  )  )  return  NULL;
	 return  &getProcedObjDbs(  pQyMc  )[iDsnIndex];
}




