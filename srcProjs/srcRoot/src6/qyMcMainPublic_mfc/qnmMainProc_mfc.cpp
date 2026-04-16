

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyWmComm.h"
#include	"myresource.h"
#include	"qyRestrictEdit.h"

#ifndef  __isCli__
#include	"dlgCfgStandardName.h"
#endif

#ifndef  __isCli__
#include	"dlgPropPcNetwork.h"
#endif
#include	"qyOpenShellCommon.h"

#ifndef  __isCli__
	#include	"dlgImGrp.h"
#endif


#ifndef  __isCli__
#include	"dlgWwwQmContact.h"
#include	"dlgCfgIpKnowledge.h"
#include	"dlgPropIpKnowledge.h"

#include	"DlgMessenger.h"

#include	"dlgCfgPhoneMessenger.h"
#include	"dlgCfgGsmModem.h"
#endif


#ifndef  __isCli__
#include	"DlgCfgCustomerService.h"
#endif
//
//#include	"qmcDynBmp.h"
//
#include	"qyCusResTemp.h"
#include	"tmpCeLib.h"

#include	"myDb.h"

//  #include	"qyMcDoc.h"
#include	<afxcview.h>



 int  enumLvSelEventFunc(  QY_EVENTINFO  *  pEventInfo,  PF_procLvEventFunc  pf,  void  *  pObjDb,  int  iLvType,  void  *  pParam  )
{
	int				iErr			=	-1;
	int				tmpiRet			=	-1;
	BOOL			bFirst			=	TRUE;


	if  (  !pEventInfo  )  return  -1;
	CListCtrl	*	pListCtrl		=	NULL;
	if  (  !pEventInfo->bDlg  )  {
		if  (  !pEventInfo->hWnd  )  return  -1;
		CListView	*	pListView		=	(  CListView  *  )CWnd::FromHandle(  pEventInfo->hWnd  );
		if  (  !pListView  )  return  -1;
		pListCtrl  =  &pListView->GetListCtrl(  );
		}
	else  {
		  if  (  !pEventInfo->hFrom  )  return  -1;
		  pListCtrl  =  (  CListCtrl  *  )CWnd::FromHandle(  pEventInfo->hFrom  );
		  if  (  !pListCtrl  )  return  -1;
	}
	
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if  (  pos  ==  NULL  )   {
		TRACE0("No items were selected!\n");
		if  (  pf  )  {
			//	
			if  (  (  tmpiRet  =  pf(  pEventInfo,  pObjDb,  iLvType,  -1,  bFirst,  pParam  )  )  )  {
				iErr  =  tmpiRet;  goto  errLabel;
			}
		}   
		//
		}
	else  {
   		  while  (  pos  )  {
			     int  nItem  =  pListCtrl->GetNextSelectedItem(pos);
      			 TRACE1("Item %d was selected!\n", nItem);
      			 // you could do your own processing on nItem here
				 if  (  pf  )  {
					 //	
					 if  (  (  tmpiRet  =  pf(  pEventInfo,  pObjDb,  iLvType,  nItem,  bFirst,  pParam  )  )  )  {
						 iErr  =  tmpiRet;  goto  errLabel;
					 }
					 bFirst  =  FALSE;
				 }   
		  }
	}

	iErr  =  0;
errLabel:
	if  (  !iErr  )  {
	}
	return  iErr;

}
