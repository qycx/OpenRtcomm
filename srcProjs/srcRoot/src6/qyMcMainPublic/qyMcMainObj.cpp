
#include "stdafx.h"
#include	<tchar.h>
#include "qyMcMainCommon.h"


 QY_SERVICEGUI_INFO  *  getServiceGuiInfo(  QY_MC  *  pQyMc,  int  iServiceId  )
{
	 QY_SERVICEGUI_INFO	*	p		=	NULL;
	 int						index	=	0;

	 for  (  index  =  0;  index  <  mycountof(  pQyMc->serviceGuiInfos  );  index  ++  )  {
		  p  =  &pQyMc->serviceGuiInfos[index];
		  if  (  p->cfg.iServiceId  ==  iServiceId  )  return  p;
	 }
	 return  NULL;
}


  int  setServiceGuiCfg(  QY_SERVICEGUI_CFG  *  pServiceCliCfg,  QY_MC  *  pQyMc  )
{
	 int	iErr	=	-1;
	 int	i;

	 for  (  i  =  0;  i  <  mycountof(  pQyMc->serviceGuiInfos  );  i  ++  )  {
		  if  (  pServiceCliCfg->iServiceId  ==  pQyMc->serviceGuiInfos[i].cfg.iServiceId  )  goto  errLabel;
	 }
	 for  (  i  =  0;  i  <  mycountof(  pQyMc->serviceGuiInfos  );  i  ++  )  {
		  if  (  !pQyMc->serviceGuiInfos[i].cfg.iServiceId  )  break;
	 }
	 if  (  i  ==  mycountof(  pQyMc->serviceGuiInfos  )  )  goto  errLabel;
	 memcpy(  &pQyMc->serviceGuiInfos[i].cfg,  pServiceCliCfg,  sizeof(  pQyMc->serviceGuiInfos[i].cfg  )  );

	 iErr  =  0;
errLabel:
	 return  iErr;
}


  //
  BOOL  bLikeXp(  )
{
	BOOL		bRet	=	FALSE;

	if  (  !g_pEnv  )  return  FALSE;

	#ifdef  __DEBUG__
			#if  0
			  traceLog(  _T(  "bLikeXp(  ) is set to true for debug"  )  );
			  return  TRUE;		//  ÎªÁË²âÊÔÄÚ´æ³ö´í£¬¹ÊÒâ·µ»Øfalse
			#endif
	#endif

	switch  (  g_pEnv->iPlatformId  )  {
			case  CONST_qyPlatform_win2k:
			case  CONST_qyPlatform_winxp:
			case  CONST_qyPlatform_win2003:		//  2017/09/24
				  bRet  =  TRUE;
				  break;
			default:
					break;
	}

	return  bRet;
}

 //  2016/06/10
 //  less than or equal to
 BOOL  bLeWin7(  )
{
	BOOL		bRet	=	FALSE;

	if  (  !g_pEnv  )  return  FALSE;

	#ifdef  __DEBUG__
			#if  0
			  traceLog(  _T(  "bLeWin7(  ) is set to true for debug"  )  );
			  return  TRUE;		//  ÎªÁË²âÊÔÄÚ´æ³ö´í£¬¹ÊÒâ·µ»Øfalse
			#endif
	#endif

	switch  (  g_pEnv->iPlatformId  )  {
			case  CONST_qyPlatform_win2k:
			case  CONST_qyPlatform_winxp:
			case  CONST_qyPlatform_win2003:
			case  CONST_qyPlatform_winVista:
			case  CONST_qyPlatform_win2008:							//  2009/11/06
			case  CONST_qyPlatform_win7:
			case  CONST_qyPlatform_win2008R2:
				  bRet  =  TRUE;
				  break;
			default:
					break;
	}

	return  bRet;
}



  //  2014/05/08
 BOOL  bAppX64(  )
 {
	 if  (  !g_pEnv  )  return  FALSE;

	 //
	 if  (  !bLikeXp(  )
		 &&  !g_pEnv->bWow64Process  )
	 {
		 return  TRUE;
	 }
	 return  FALSE;
 }


  BOOL  isWinCe(  )
{
	BOOL	bRet	=	FALSE;

	if  (  !g_pEnv  )  return  FALSE;

	switch  (  g_pEnv->iPlatformId  )  {
			case  CONST_qyPlatform_winCe:
				  bRet  =  TRUE;
				  break;
			default:
					break;
	}
	return  bRet;
}



 ///////////////////////////
 /////
 //

 CQyString  getMcQueryCntStr(  QY_MC_QUERY  *  pQuery  )
{
	 return  CQyString(  (char*)"select count( * ) "  )  +  CQyString(  pQuery->fromPart  )  +  CQyString(  _T(  " "  )  )  +  CQyString(  pQuery->wherePart  );
}


 CQyString  getMcQueryCurnItemStr(  QY_MC_QUERY  *  pQuery  )
{	
	//traceLogA(  (char*)  "getMcQueryCurnItemStr .. 这个函数不应再被调用。"  );
	
	return  CQyString( (char*)""  );

}


