
#include	"stdafx.h"
#include	<tchar.h>
#include	"shlobj.h"
#ifndef  __WINCE__
		 #include	"myresource.h"
#endif
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#ifdef  __isCli__
		#include	"qmcCommFunc_iscli.h"
#endif
#include	"qyVDev.h"




#if  0
 //  2012/06/17
 BOOL  bSupported_mediaSdk_enc(  )
{
	QY_MC	*	pQyMc	=	;

	CUS_MODULE_U	*	pModule	=	NULL;

#ifdef  __DEBUG__
		//  return  TRUE;
#endif

	pModule  =  pQyMc->cusModules.pMediaSdk_enc;
	if  (  pModule
		&&  pModule->common.hModule  
		//  &&  !pModule->compress.mgr.ucbNotSupported_hw  
		)  return  TRUE;

	return  FALSE;

}

 BOOL  bSupported_mediaSdk_dec(  )
{
	QY_MC	*	pQyMc	=	;

	CUS_MODULE_U	*	pModule	=	NULL;

#ifdef  __DEBUG__
		//  return  TRUE;
#endif

	pModule  =  pQyMc->cusModules.pMediaSdk_dec;
	if  (  pModule
		&&  pModule->common.hModule  
		//  &&  !pModule->compress.mgr.ucbNotSupported_hw
		)  return  TRUE;

	return  FALSE;

}
#endif

 
 //
 BOOL  bSupported_vwRuleType_messenger(  QY_MC  *  pQyMc  )
{
#if  0
	if  (  qyGetAppAvLevel_qyMc(  pQyMc  )  ==  CONST_qyAppAvLevel_sd  )  {
		return  FALSE;
	}
#endif

	return  TRUE;	
}


 

  //
   QY_DMITEM  CONST_qyTreeTypeTable[]  =
{
	{	CONST_qyTreeType_general,	(TCHAR*)_T(  "ÆÕÍ¨Ê÷"  ),		},
	{	CONST_qyTreeType_switch,	(TCHAR*)_T(  "½»»»»úÊ÷"  ),		},
	{	-1,											},
};


   void showMcSel(  QY_MC_SEL  *  pSelParam  )
{
	 switch  (  pSelParam->type  )  {
		 
			 case  QY_SELTYPE_MCROOTTREE:  {
				   QY_MCROOTTREE_SEL  *  pSel  =  (  QY_MCROOTTREE_SEL  *  )&pSelParam->u.rootTree;
				   traceLogA(  (char*)  "QY_SELTYPE_MCROOTTREE,  treeType is %s, bRoot is %d,  iHelpId is %d",  qyGetDesByType1(  CONST_qyTreeTypeTable,  pSel->type  ),  pSel->bRoot,  pSel->iHelpId  );
				   }
				   break;
			 case  QY_SELTYPE_MCROOTLIST:
				   break;
			 case  QY_SELTYPE_MCSITELEFT:
				   break;
			 case  CONST_qySelType_mcQuery:  {
				   QY_MC_QUERY	*	pQuery  =  &pSelParam->u.query;
				   traceLogA(  (char*)  "%S %S %S %S %S",  pQuery->selectPart,  pQuery->fromPart,  pQuery->wherePart,  pQuery->groupPart,  pQuery->sortPart  );
					}
				   break;
			 default:
					break;				   
	 }
	 
	 return;

}



 GENERIC_Q  *  getDisplayQ(  QY_MC  *  pQyMc,  void  *  p1,  void  *  p2  )
{
	GENERIC_Q				*	pQ		=	NULL;
	QY_SERVICEGUI_INFO		*	pSci	=	NULL;

#ifdef  __isCli__
	if  (  pQyMc->iServiceId  ==  CONST_qyServiceId_mis  &&  pQyMc->iAppType  ==  CONST_qyAppType_client  )  {
		pSci  =  getServiceGuiInfo(  pQyMc,  pQyMc->iServiceId  );
		if  (  pSci  )  {
            pQ  =  &(  (  MC_VAR_isCli  *  )pSci->pVar  )->displayQ;
		}
	}
#endif

//  errLabel:
		
	return  pQ;

}


///  ÊÇ·ñÄÚ´æ <= 512M
 BOOL  isMem512(  QY_MC  *  pQyMc  )
{
	if  (  !pQyMc  )  return  FALSE;

	//
	#ifdef  __DEBUG__
			//  return  FALSE;		//  ÎªÁË²âÊÔÄÚ´æ³ö´í£¬¹ÊÒâ·µ»Øfalse
	#endif

	return  (  (  pQyMc->uiTotalPhys_memStatus  )  <  (  512  +  100  )  *  1024  *  1024  );
}



 //
 BOOL  bSupported_avLevel(  QY_MC  *  pQyMc,  unsigned  int  uiCapType,  BITMAPINFO  *  pBmpInfo_input,  VIDEO_COMPRESSOR_CFG  *  pCompressor  )
{
	BOOL			bRet	=	FALSE;
	//unsigned  short  usAppAvLevel  =  qyGetAppAvLevel_qyMc(  pQyMc  );

	if  (  !pBmpInfo_input  ||  !pCompressor  )  return  FALSE;

#ifdef  __isCli__
	switch  (  uiCapType  )  {
			case  CONST_capType_screen:
			case  CONST_capType_qvcf:
				  bRet  =  TRUE;  goto  errLabel;
				  break;
			case  CONST_capType_mosaic:
				  if  (  pCompressor->common.uiSubCapType  ==  CONST_subCapType_mosaic_resource  )  {
					  bRet  =  TRUE;  goto  errLabel;
				  }
				  break;
			default:
					break;
	}

	//
#if  0
	if  (  usAppAvLevel  <  CONST_qyAppAvLevel_fullHd  )  {
		if  (  pBmpInfo_input->bmiHeader.biWidth  *  pBmpInfo_input->bmiHeader.biHeight  >  1280  *  720
			&&  pCompressor->common.usMaxFps_toShareBmp  >  10  )
		{
			goto  errLabel;
		}
	}
	if  (  usAppAvLevel  <  CONST_qyAppAvLevel_hd  )  {
		if  (  pBmpInfo_input->bmiHeader.biWidth  *  pBmpInfo_input->bmiHeader.biHeight  >  800  *  600
			&&  pCompressor->common.usMaxFps_toShareBmp  >  10  )
		{
			goto  errLabel;
		}
	}
#endif

	//
#endif

	bRet  =  TRUE;

errLabel:


	return  bRet;
}


 //  2014/08/03
  BOOL  bSupported_remoteStorage(  QY_MC  *  pQyMc  )
{
	if  (  !pQyMc  )  return  FALSE;

	//if  (  qyGetAppAvLevel_qyMc(  )  ==  CONST_qyAppAvLevel_sd  )  return  FALSE;

	return  pQyMc->ucbSupported_remoteStorage_default;	//  
 }

  //  2015/08/04
  BOOL  bSupported_fileServer(  QY_MC  *  pQyMc  )
  {
	  if  (  !pQyMc  )  return  FALSE;
	  	
	  //
#if  1  //  def  __DEBUG__
	    if  (  pQyMc->appParams.bFileServer
			||  pQyMc->ucbSupported_fileServer_default  )  			
		{		
			return  TRUE;
			}
		else  {
			  return  FALSE;
		}
#endif

	return  pQyMc->ucbSupported_fileServer_default;	//  
  }



  


