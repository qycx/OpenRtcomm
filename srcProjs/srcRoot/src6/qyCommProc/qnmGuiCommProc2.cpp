
#include	"stdafx.h"

#include	"qyPrecomp.h"

#include	<windows.h>
#include	<tchar.h>
#include	<stdlib.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyGuiCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qyTCharCommProc.h"
#include	"qyLangCommProc.h"
#include	"qnmGuiCommProc.h"
#include	"qnmCustom.h"
#include	"qnmCustomGui.h"
#include	"qwmAllHints.h"

#include	<WtsApi32.h>

#include	"qisGuiPublic_public.h"		//  2013/06/09


//
extern  "C"  BOOL  bFieldLikeDw(  int  fieldId  )  
{ 
	  switch  (  fieldId  )  {
			  case  CONST_fieldId_zb:  
			  case  CONST_fieldId_bb:
			  case  CONST_fieldId_dw:
			  case  CONST_fieldId_bm:
			  case  CONST_fieldId_syr:
				    return  TRUE;
			  default:
					break;
	  }
	  return  FALSE;
}
 
 extern  "C"  BOOL  bFieldLikeZcbh(  int  fieldId,  BOOL  *  pbRealZcbh  )
{
	 BOOL	bRet		=	FALSE;
	 BOOL	bRealZcbh	=	FALSE;	

	 switch  (  fieldId  )  {
			 case  CONST_fieldId_zcbh0:
			 case  CONST_fieldId_zcbh1:
			 case  CONST_fieldId_zcbh2:
				   bRealZcbh  =  TRUE;
				   break;
			 //  case  CONST_fieldId_zcsm0:
			 case  CONST_fieldId_zcsm1:
			 case  CONST_fieldId_zcsm2:
				   break;
			 default:
				    goto  errLabel;			
	 }
	 bRet  =  TRUE;
errLabel:
	 if  (  bRet  )  {
		 if  (  pbRealZcbh  )  *pbRealZcbh  =  bRealZcbh;
	 }
	 return  bRet;
}
