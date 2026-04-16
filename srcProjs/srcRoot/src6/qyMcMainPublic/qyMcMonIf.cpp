

#include	"stdafx.h"
#include	"myresource.h"
#include	"qyMcMainCommon.h"
#include	"qyFile.h"

#include	"qyMc.h"
//  #include	"qyMcDoc.h"

#include	"qyMcView.h"
#include	"dlgMcHint.h"
#include	"qyCusResTemp.h"



 BOOL  bDisplayMcViewContent_procedObjs(  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  );


 BOOL  bNetMcMonIfFlow(  QY_MC  *  pQyMc,  char  *  switchMac,  int  iPortIfIndex  )
{
	 BOOL			bRet		=		FALSE;
	 QY_MC_SEL		sel;

	 traceLogA(  "bNetMcMonIfFlow enters"  );

	 memset(  &sel,  0,  sizeof(  sel  )  );

	 sel.type  =  CONST_qySelType_mcView;
	 sel.u.mcView.type  =  CONST_qyLvType_monIfFlow;	//  2007/01/01

	 bQyMcNewMcView(  &sel  );

	 traceLogA(  "bNetMcMonIfFlow leaves"  );

	 return  bRet;
}



 void  qyMcView_delAllColumns(  void  *  pViewParam,  void  *  p1,  void  *  p2  )
{
	 if  (  !pViewParam  )  return;
	 CQyMcView	*	pView  =  (  CQyMcView  *  )pViewParam;

	 pView->delAllColumns(  );

	 return;
}



 BOOL  qyMcView_bAddColumns(  void  *  pViewParam,  QY_COLUMNINFO * pColumns,  void  *  p2  )
{
	 if  (  !pViewParam  )  return  FALSE;

	 CQyMcView  *  pView  =  (  CQyMcView  *  )pViewParam;

	 return  pView->bAddColumns(  pColumns  );
}


////////////////////////////////////////


/*

 BOOL  bDisplayMcViewContent_anyObjs(  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
{
	 BOOL								bRet					=			FALSE;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 CListCtrl						&	ListCtrl				=			pMcView->GetListCtrl();
	 int								i;
	 QY_OBJ_DB						*	pObj;
	 char								buf[256];
	 int								cnt						=			0;

	 pMcView->delAllColumns(  );
	 if  (  !pMcView->bAddColumns(  CONST_procedObjsViewTable  )  )  goto  errLabel;

	 ListCtrl.DeleteAllItems(  );

	 for  (  i  =  0;  i  <  (  int  )getProcedObjDbsMaxCnt(  );  i  ++  )  {
		  pObj  =  &getProcedObjDbs(  )[i];
		  if  (  !pObj->ucbUsed  )  continue;
		  
		  ListCtrl.InsertItem(  cnt,  CString(  ltoa(  pObj->iDsnIndex,  buf,  10  )  ),  0  );
		  ListCtrl.SetItemText(  cnt,  1,  pObj->cfg.sysName  );
		  ListCtrl.SetItemText(  cnt,  2,  qyGetDesByType1(  CONST_qySystemIdTable,  pObj->cfg.iSystemId  )  );
		  ListCtrl.SetItemText(  cnt,  3,  pObj->pDb  ?  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_loaded  )  :  _T(  ""  )  );

		  cnt  ++  ;
		  
	 }


	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}

*/


 //  数据源列表，2007/01/02
 BOOL  bQyOpenMcView(  QY_MCVIEW_SEL  *  pParam,  void  *  p1,  void  *  p2  )
{
	 BOOL				bRet		=		FALSE;
	 QY_MC			*	pQyMc		=		QY_GET_GBUF(  );  
	 QY_MC_SEL			sel;

	 traceLogA(  "bViewAnyObjs enters"  );

	 if  (  !pParam  )  return  FALSE;

	 memset(  &sel,  0,  sizeof(  sel  )  );

	 sel.type  =  CONST_qySelType_mcView;
	 memcpy(  &sel.u.mcView,  pParam,  sizeof(  sel.u.mcView  )  );

	 sel.u.mcView.type  =  CONST_qyLvType_anyObjList;
	 sel.u.mcView.iDsnIndex  =  pQyMc->iDsnIndex_mainSys;					//  用基本系统的数据库
	 sel.u.mcView.pfProcEvent  =  netMc_procMcViewEvent;

	 bQyMcNewMcView(  &sel  );

	 traceLogA(  "ViewAnyObjs leaves"  );

	 return  bRet;
}














////////////////////////////////////////////




 //  数据源列表，2007/01/02
 BOOL  bViewAllProcedObjs(  QY_MC  *  pQyMc,  void  *  p1,  void  *  p2  )
{
	 BOOL			bRet		=		FALSE;
	 QY_MC_SEL		sel;

	 traceLogA(  "bNetMcViewProcedObjs enters"  );

	 memset(  &sel,  0,  sizeof(  sel  )  );

	 sel.type  =  CONST_qySelType_mcView;
	 sel.u.mcView.type  =  CONST_qyLvType_procedObjList;
	 sel.u.mcView.iDsnIndex  =  pQyMc->iDsnIndex_mainSys;					//  用基本系统的数据库
	 sel.u.mcView.pfDisplayListContent  =  (  PF_commonHandler  )bDisplayMcViewContent_procedObjs;

	 sel.u.mcView.pfProcEvent			=  netMc_procMcViewEvent;
	 sel.u.mcView.uPopupMenuId			=  IDR_QYMCPOPUP;
	 sel.u.mcView.nSubMenuPos			=  pQyMc->cfg.pGuiCfg->iResId_popupMenu_procedObj;

	 _sntprintf(  sel.u.mcView.docName,  mycountof(  sel.u.mcView.docName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_dataSourceList  )  );

	 bQyMcNewMcView(  &sel  );

	 traceLogA(  "bNetMcViewProcedObjs leaves"  );

	 return  bRet;
}


 BOOL  bDisplayMcViewContent_procedObjs(  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
{
	 BOOL								bRet					=			FALSE;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 CListCtrl						&	ListCtrl				=			pMcView->GetListCtrl();
	 int								i;
	 QY_OBJ_DB						*	pObj;
	 char								buf[256];
	 int								cnt						=			0;

	 pMcView->delAllColumns(  );
	 if  (  !pMcView->bAddColumns(  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_COLUMNINFO_procedObjsViewTable  )  )  )  goto  errLabel;

	 ListCtrl.DeleteAllItems(  );

	 for  (  i  =  0;  i  <  (  int  )getProcedObjDbsMaxCnt(  pQyMc  );  i  ++  )  {
		  pObj  =  &getProcedObjDbs(  pQyMc  )[i];
		  if  (  !pObj->ucbUsed  )  continue;
		  
		  ListCtrl.InsertItem(  cnt,  CString(  ltoa(  pObj->iDsnIndex,  buf,  10  )  ),  0  );
		  ListCtrl.SetItemText(  cnt,  1,  pObj->cfg.sysName  );
		  ListCtrl.SetItemText(  cnt,  2,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qySystemIdTable  ),  pObj->cfg.iSystemId  )  );
		  ListCtrl.SetItemText(  cnt,  3,  pObj->pDb  ?  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_loaded  ) :  _T(  ""  )  );

		  cnt  ++  ;
		  
	 }


	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}


