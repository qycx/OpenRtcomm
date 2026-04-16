

#include	"stdafx.h"

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"qyWmComm.h"

#include	"qyCusResTemp.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qmcDynBmp.h"
#include	"qmcVWall.h"
#include	"qyDynLib.h"
#include	"qmcCmdProc.h"
//
#include	"isCmdConst.h"
//
#include	"myDb.h"
#include	"qyMessengerHelpPublic.h"

#include	"myresource.h"
#include	"qyMcMainWndProc.h"
#include	"DlgLeftView_db.h"
#include	"myTreeCtrlFunc.h"
#include	"genericHash.h"
#include	"imObjHash.h"
#include	"qmcCommFunc_isCli.h"
#include	"objType_tmp.h"
#include	"ctxQmc.h"


 int  getObjId_myDb(  LP_hashTbl  pHashTbl_tree,  int  iObjType,  char  *  pKeyStr  )
{
	int		iErr	=	-1;
	int		iObjId	=	0;

	BOOL						bNeedFree_elem_o		=				FALSE;
	 HashTblElementType			elem_o;


			HashTblElementType	elem;
		HashData_imObj  data_imObj;
		
#if  0
		iObjType  =  CONST_objType_dw;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  desc.pDw  );
		myTChar2Utf8(  tBuf,  buf,  mycountof(  buf  )  );
#endif
		memset(  &elem,  0,  sizeof(  elem  )  );
		elem.iKeyType  =  CONST_hashKeyType_imObj;
		elem.pKeyStr  =  pKeyStr;
		memset(  &data_imObj,  0,  sizeof(  data_imObj  )  );
		//  data.iObjId  
		data_imObj.iObjType  =  iObjType;
		elem.pData  =  &data_imObj;
		elem.uiSize_pData  =  sizeof(  data_imObj  );
		//
		memset(  &elem_o,  0,  sizeof(  elem_o  )  );
		//
		if  (  !hashTbl_find(  pHashTbl_tree,  &elem,  NULL,  &elem_o  )  )  {
			bNeedFree_elem_o  =  TRUE;

			HashData_imObj  *  pData  =  (  HashData_imObj  *  )elem_o.pData;
			iObjId  =  pData->iObjId;

			imObj_hash_free(  &elem_o  );  
			bNeedFree_elem_o  =  FALSE;
			}
		else  {

			iObjId  =  getuiNextTranNo(  0,  0,  0  );
			unsigned  int  uiHashIndex  =  0;
			//
			data_imObj.iObjId  =  iObjId;
			//
			if  (  hashTbl_insert(  &elem,  &uiHashIndex,  pHashTbl_tree  )  )  goto  errLabel;
			
			//
			HashData_iObjId	data_iObjId;
			memset(  &data_iObjId,  0,  sizeof(  data_iObjId  )  );
			data_iObjId.uiHashIndex  =  uiHashIndex;

			//
			memset(  &elem,  0,  sizeof(  elem  )  );
			elem.bKeyInt  =  TRUE;
			elem.iKeyVal  =  iObjId;
			elem.iKeyType  =  CONST_hashKeyType_iObjId;
			elem.pData  =  &data_iObjId;
			elem.uiSize_pData  =  sizeof(  data_iObjId  );
			if  (  !hashTbl_find(  pHashTbl_tree,  &elem,  NULL,  NULL  )  )  {
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "tmpHandler_addImObjRegInfo failed: iObjId is in conflict."  )  );
				#ifdef  __DEBUG__
						traceLog(  _T(  "tmpHandler_addImObjRegInfo failed: iObjId is in conflict"  )  );
				#endif
				goto  errLabel;
			}
			if  (  hashTbl_insert(  &elem,  NULL,  pHashTbl_tree  )  )  goto  errLabel;
		}

		iErr  =  0;

errLabel:


		if  (  bNeedFree_elem_o  )  {
			imObj_hash_free(  &elem_o  );
		}

		return  iErr  ?  0  :  iObjId;

}

 

int  tmpHandler_addImObjRegInfo(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;
	int  i;
	QY_MC					*  pQyMc		=	 QY_GET_GBUF(  );

	
	CDlgLeftView_db			*	pLeftView			=				(  CDlgLeftView_db  *  )p0;
	 CTreeCtrl				*	m_TreeCtrl			=				pLeftView->m_TreeCtrl;	//  GetTreeCtrl(  );
	 //
	 COMMON_PARAM			*	pCommonParam		=	(  COMMON_PARAM  *  )p1;
	 QY_MESSENGER_REGINFO	*  pRegInfo		=	 (  QY_MESSENGER_REGINFO  *  )pCommonParam->p2;
	QMEM_qyImObjRegInfo		*  pQMem		=	 (  QMEM_qyImObjRegInfo  *  )p2;


	HTREEITEM					tmphtItem				=				NULL;
	 TCHAR						displayName[512]		=				_T(  ""  );		
	 int						iObjType				=				0;
	 int						iObjId					=				0;
	 int						nImage,  nSelectedImage;
	 
#if  0
	 BOOL						bNeedFree_elem_o		=				FALSE;
	 HashTblElementType			elem_o;
#endif
	 		
		memset(  pRegInfo,  0,  sizeof(  pRegInfo[0]  )  );
		pRegInfo->uiType  =  CONST_imCommType_messengerRegInfo;
		//  id
		pRegInfo->iCustomId  =  qyGetCustomId(  );

		memcpy(  &pRegInfo->addr,  &pQMem->myRegInfo.addr,  sizeof(  pRegInfo->addr  )  );
		
		memcpy(  pRegInfo->uiFieldIds,  pQMem->myRegInfo.uiFieldIds,  sizeof(  pQMem->myRegInfo.uiFieldIds  )  );
		memcpy(  pRegInfo->u.cols,  pQMem->myRegInfo.u.cols,  sizeof(  pRegInfo->u.cols  )  );
		
		//
		MACRO_setPtrs(  CONST_fieldIdTable_en,  pRegInfo[0],  pRegInfo->fields  );

		//
		MY_REG_DESC				desc;
		//
		if  (  regInfo2Desc(  0,  pRegInfo,  &desc,  NULL,  0,  NULL,  0  )  )  goto  errLabel;

#ifdef  __DEBUG__
		CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
		if (pProcInfo->cfg.debugStatusInfo.bDbgDetail) {
			traceLog(_T("tmpHandler_addImObjRegInfo: %s - %s - %s: %I64u"), desc.pDw, desc.pBm, desc.pSyr, pRegInfo->addr.idInfo.ui64Id);
		}
#endif
		TCHAR	tBuf[256]  =  _T(  ""  );
		char	buf[256]	=	"";

		iObjType  =  CONST_objType_dw;		
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  desc.pDw  );
		myTChar2Utf8(  tBuf,  buf,  mycountof(  buf  )  );


		//
		iObjId  =  getObjId_myDb(  pLeftView->m_var.pHashTbl_tree,  iObjType,  buf  );
					
						
			//
			_sntprintf(  displayName,  sizeof(  displayName  )  /  sizeof(  displayName[0]  ),  _T(  "%s"  ),  desc.pDw  );
			   nImage  =  pQyMc->cfg.image.nImage_col2;  nSelectedImage  =  pQyMc->cfg.image.nImage_col3;
			   //  getSnmpObjImages(  pQyMc,  pObj,  &nImage,  &nSelectedImage  );

			   if  (  !(  tmphtItem  =  pLeftView->FindItemData(  iObjId,  TRUE,  pLeftView->m_var.htMyRootItem  )  )  )  {
				   tmphtItem  =  m_TreeCtrl->InsertItem(  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE  |  TVIF_PARAM,  
														  CString(  displayName  ).GetBuffer(  0  ),  
														  nImage,  
														  nSelectedImage,  
														  TVIS_EXPANDPARTIAL,  
														  TVIS_STATEIMAGEMASK, 
														  iObjId,  
														  pLeftView->m_var.htMyRootItem,  
														  TVI_LAST  );
				   //  m_TreeCtrl->SortChildren(  pLeftView->m_var.htMyRootItem  );
				   
				   }
			   else  {				  
				     //  只刷新展开节点
					 TVITEM				tvItem;
					 
					 tvItem.mask  =  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE;
					 tvItem.hItem  =  tmphtItem;
					 tvItem.pszText  =  tBuf;
					 tvItem.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );
					 m_TreeCtrl->GetItem(  &tvItem  );
					 
					 if  (  _tcsicmp(  tBuf,  displayName  )  ||  tvItem.iImage  !=  nImage  ||  tvItem.iSelectedImage  !=  nSelectedImage  )  {
						 _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s"  ),  displayName  );
						 tvItem.iImage  =  nImage;
						 tvItem.iSelectedImage  =  nSelectedImage;
						 m_TreeCtrl->SetItem(  &tvItem  );
					 }

#if  0	//  2014/05/27. 不展开了，否则下面有很多节点时，会造成不响应
					 //  刷新展开节点
					 //  if  (  tvItem.state  &  TVIS_EXPANDED   )  pLeftView->bRefreshItem(  tmphtItem  );				   
					 if  (  pLeftView->m_TreeCtrl->ItemHasChildren(  tmphtItem  )  )  pLeftView->bRefreshItem(  tmphtItem  );				   
#endif

			   }



		

		//
		//  pLeftView->FindItem(  



		iRet  =  0;
errLabel:

#if  0
		if  (  bNeedFree_elem_o  )  {
			imObj_hash_free(  &elem_o  );
		}
#endif

	return  iRet;

}

int  tmpHandler_addImObjRegInfo_bm(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;
	int  i;
	QY_MC					*  pQyMc		=	 QY_GET_GBUF(  );

	
	CDlgLeftView_db			*	pLeftView			=				(  CDlgLeftView_db  *  )p0;
	 CTreeCtrl				*	m_TreeCtrl			=				pLeftView->m_TreeCtrl;	//  GetTreeCtrl(  );
	 //
	 COMMON_PARAM			*	pCommonParam		=	(  COMMON_PARAM  *  )p1;
	 MY_REG_DESC  *  pDescParam  =  (  MY_REG_DESC  *  )pCommonParam->p0;
	 HTREEITEM							htItem				=				(  HTREEITEM  )pCommonParam->p1;
	 QY_MESSENGER_REGINFO	*  pRegInfo		=	 (  QY_MESSENGER_REGINFO  *  )pCommonParam->p2;
	 //
	QMEM_qyImObjRegInfo		*  pQMem		=	 (  QMEM_qyImObjRegInfo  *  )p2;


	HTREEITEM					tmphtItem				=				NULL;
	 TCHAR						displayName[512]		=				_T(  ""  );		
	 int						iObjId					=				0;
	 int						iObjType				=				0;
	 int						nImage,  nSelectedImage;

#if  0
	 BOOL						bNeedFree_elem_o		=				FALSE;
	 HashTblElementType			elem_o;
#endif


			memset(  pRegInfo,  0,  sizeof(  pRegInfo[0]  )  );
		pRegInfo->uiType  =  CONST_imCommType_messengerRegInfo;
		//  id
		pRegInfo->iCustomId  =  qyGetCustomId(  );

		memcpy(  &pRegInfo->addr,  &pQMem->myRegInfo.addr,  sizeof(  pRegInfo->addr  )  );
		
		memcpy(  pRegInfo->uiFieldIds,  pQMem->myRegInfo.uiFieldIds,  sizeof(  pQMem->myRegInfo.uiFieldIds  )  );
		memcpy(  pRegInfo->u.cols,  pQMem->myRegInfo.u.cols,  sizeof(  pRegInfo->u.cols  )  );
		
		//
		MACRO_setPtrs(  CONST_fieldIdTable_en,  pRegInfo[0],  pRegInfo->fields  );

		//
		MY_REG_DESC				desc;
		//
		if  (  regInfo2Desc(  0,  pRegInfo,  &desc,  NULL,  0,  NULL,  0  )  )  goto  errLabel;

		//
		if  (  _tcscmp(  desc.pDw,  pDescParam->pDw  )  )  {
			iRet  =  0;  goto  errLabel;
		}

		//
#ifdef  __DEBUG__
		traceLog(  _T(  "%s - %s - %s: %I64u"  ),  desc.pDw,  desc.pBm,  desc.pSyr,  pRegInfo->addr.idInfo.ui64Id  );
#endif
		
		//
		TCHAR	tBuf[256]  =  _T(  ""  );
		char	buf[256]	=	"";

		iObjType  =  CONST_objType_bm;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\\%s"  ),  desc.pDw,  desc.pBm  );
		myTChar2Utf8(  tBuf,  buf,  mycountof(  buf  )  );

		//
		iObjId  =  getObjId_myDb(  pLeftView->m_var.pHashTbl_tree,  iObjType,  buf  );
				
		//		
		_sntprintf(  displayName,  sizeof(  displayName  )  /  sizeof(  displayName[0]  ),  _T(  "%s"  ),  desc.pBm  );			
		nImage  =  pQyMc->cfg.image.nImage_col3;  nSelectedImage  =  pQyMc->cfg.image.nImage_col3;

		//
		if  (  myAddOrRefreshTreeItem(  pLeftView,  htItem,  iObjId,  displayName,  nImage,  nSelectedImage  )  )  goto  errLabel;
		
		//
		iRet  =  0;
errLabel:

#if  0
		if  (  bNeedFree_elem_o  )  {
			imObj_hash_free(  &elem_o  );
		}
#endif

	return  iRet;

}


int  tmpHandler_addImObjRegInfo_syr(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;
	int  i;
	QY_MC					*  pQyMc		=	 QY_GET_GBUF(  );

	
	CDlgLeftView_db			*	pLeftView			=				(  CDlgLeftView_db  *  )p0;
	 CTreeCtrl				*	m_TreeCtrl			=				pLeftView->m_TreeCtrl;	//  GetTreeCtrl(  );
	 //
	 COMMON_PARAM			*	pCommonParam		=	(  COMMON_PARAM  *  )p1;
	 MY_REG_DESC  *  pDescParam  =  (  MY_REG_DESC  *  )pCommonParam->p0;
	 HTREEITEM							htItem				=				(  HTREEITEM  )pCommonParam->p1;
	 QY_MESSENGER_REGINFO	*  pRegInfo		=	 (  QY_MESSENGER_REGINFO  *  )pCommonParam->p2;
	 //
	QMEM_qyImObjRegInfo		*  pQMem		=	 (  QMEM_qyImObjRegInfo  *  )p2;


	QY_OBJ_DB						*	pObjDb				=				getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  );
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  -1;

		 int								iServiceId			=				CONST_qyServiceId_mis;
	 QY_SERVICEGUI_INFO			*	pSci					=				getServiceGuiInfo(  pQyMc,  iServiceId  );
	 if  (  !pSci  )  return  -1;
	 MC_VAR_isCli					*	pProcInfo				=				(  MC_VAR_isCli  *  )pSci->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 MIS_CNT						*	pMisCnt				=				getMisCntByName(  pProcInfo,  _T(  ""  )  );
	 if  (  !pMisCnt  )  return  -1;
	 CQnmDb								tmpObjDb;
	 
	 if  (  !tmpObjDb.getAvailableDb(  pObjDb->iDsnIndex  )  )  {
		 traceLogA(  "得不到可用的连接数了"  );  goto  errLabel;
	 }


	HTREEITEM					tmphtItem				=				NULL;
	 TCHAR						displayName[512]		=				_T(  ""  );		
	 int						iObjId					=				0;
	 int						iObjType				=				0;
	 int						nImage,  nSelectedImage;

#if  0
	 BOOL						bNeedFree_elem_o		=				FALSE;
	 HashTblElementType			elem_o;
#endif


			memset(  pRegInfo,  0,  sizeof(  pRegInfo[0]  )  );
		pRegInfo->uiType  =  CONST_imCommType_messengerRegInfo;
		//  id
		pRegInfo->iCustomId  =  qyGetCustomId(  );

		memcpy(  &pRegInfo->addr,  &pQMem->myRegInfo.addr,  sizeof(  pRegInfo->addr  )  );
		
		memcpy(  pRegInfo->uiFieldIds,  pQMem->myRegInfo.uiFieldIds,  sizeof(  pQMem->myRegInfo.uiFieldIds  )  );
		memcpy(  pRegInfo->u.cols,  pQMem->myRegInfo.u.cols,  sizeof(  pRegInfo->u.cols  )  );
		
		//
		MACRO_setPtrs(  CONST_fieldIdTable_en,  pRegInfo[0],  pRegInfo->fields  );

		//
		MY_REG_DESC				desc;
		//
		if  (  regInfo2Desc(  0,  pRegInfo,  &desc,  NULL,  0,  NULL,  0  )  )  goto  errLabel;

		//
		if  (  _tcscmp(  desc.pDw,  pDescParam->pDw  )
			||  _tcscmp(  desc.pBm,  pDescParam->pBm  )  )  
		{
			iRet  =  0;  goto  errLabel;
		}

		//
#ifdef  __DEBUG__
		traceLog(  _T(  "%s - %s - %s: %I64u"  ),  desc.pDw,  desc.pBm,  desc.pSyr,  pRegInfo->addr.idInfo.ui64Id  );
#endif
		
		//
		TCHAR	tBuf[256]  =  _T(  ""  );
		char	buf[256]	=	"";

#if  0
		iObjType  =  CONST_objType_syr;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\\%s\\%s"  ),  desc.pDw,  desc.pBm,  desc.pSyr  );
		myTChar2Utf8(  tBuf,  buf,  mycountof(  buf  )  );
#endif
		iObjType  =  CONST_objType_messenger;
		idInfo2Str(  &pRegInfo->addr.idInfo,  buf,  mycountof(  buf  )  );

		//
		iObjId  =  getObjId_myDb(  pLeftView->m_var.pHashTbl_tree,  iObjType,  buf  );
			

		//////////////////
		QY_MESSENGER_INFO					messengerInfo;
									
		//  先用regInfo填充一下messengerInfo, 因为下面的pClient只能指向messengerInfo		
		memset(  &messengerInfo,  0,  sizeof(  messengerInfo  )  );		
		//

		//  lstrcpyn(  messengerInfo.misServName,  pMisCnt->cfg.misServName,  mycountof(  messengerInfo.misServName  )  );
		messengerInfo.idInfo.ui64Id  =  pRegInfo->addr.idInfo.ui64Id;
        			
		//  2007/06/03, 这里要加入内存中的管理队列								
		QMOBJQ_PARAM_MISCLIENT		qmObjQParam;
		//		
		memset(  &qmObjQParam,  0,  sizeof(  qmObjQParam  )  );			
		//  uiType
		qmObjQParam.pSci  =  pSci;					
		qmObjQParam.pMisCnt  =  pMisCnt;
		qmObjQParam.pDb  =  tmpObjDb.getAvailableDb(  pObjDb->iDsnIndex  );
		qmObjQParam.iDbType  =  pObjDb->cfg.iDbType;
		qmObjQParam.iObjType  =  CONST_objType_messenger;
		qmObjQParam.pClient  =  &messengerInfo;
		
		if  (  desc.pSyr[0]  )  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s"  ),  desc.pSyr  );		
		else  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "(%I64u)"  ),  pRegInfo->addr.idInfo.ui64Id  );
					  			 
		nImage  =  pQyMc->cfg.image.nImage_col4;  nSelectedImage  =  pQyMc->cfg.image.nImage_selectedCol4;
				
		if  (  myAddOrRefreshTreeItem(  pLeftView,  htItem,  iObjId,  displayName,  nImage,  nSelectedImage,  &qmObjQParam  )  )  goto  errLabel;
		
		//
		iRet  =  0;
errLabel:

#if  0
		if  (  bNeedFree_elem_o  )  {
			imObj_hash_free(  &elem_o  );
		}
#endif

	return  iRet;

}



//
int  tmpHandler_addImObj_unRegMessenger(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;
	int  i;
	QY_MC					*  pQyMc		=	 QY_GET_GBUF(  );

	
	CDlgLeftView_db			*	pLeftView			=				(  CDlgLeftView_db  *  )p0;
	 CTreeCtrl				*	m_TreeCtrl			=				pLeftView->m_TreeCtrl;	//  GetTreeCtrl(  );
	 //
	 COMMON_PARAM			*	pCommonParam		=	(  COMMON_PARAM  *  )p1;
	 //MY_REG_DESC  *  pDescParam  =  (  MY_REG_DESC  *  )pCommonParam->p0;
	 HTREEITEM							htItem				=				(  HTREEITEM  )pCommonParam->p1;
	 QY_MESSENGER_REGINFO	*  pRegInfo		=	 (  QY_MESSENGER_REGINFO  *  )pCommonParam->p2;
	 //
	 QMEM_qyImObj  *  pQMem  =  (  QMEM_qyImObj  *  )p2;



	QY_OBJ_DB						*	pObjDb				=				getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  );
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  -1;

		 int								iServiceId			=				CONST_qyServiceId_mis;
	 QY_SERVICEGUI_INFO			*	pSci					=				getServiceGuiInfo(  pQyMc,  iServiceId  );
	 if  (  !pSci  )  return  -1;
	 MC_VAR_isCli					*	pProcInfo				=				(  MC_VAR_isCli  *  )pSci->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 MIS_CNT						*	pMisCnt				=				getMisCntByName(  pProcInfo,  _T(  ""  )  );
	 if  (  !pMisCnt  )  return  -1;
	 
	 QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;



	 CQnmDb								tmpObjDb;
	 
	 if  (  !tmpObjDb.getAvailableDb(  pObjDb->iDsnIndex  )  )  {
		 traceLogA(  "得不到可用的连接数了"  );  goto  errLabel;
	 }


	HTREEITEM					tmphtItem				=				NULL;
	 TCHAR						displayName[512]		=				_T(  ""  );		
	 int						iObjId					=				0;
	 int						iObjType				=				0;
	 int						nImage,  nSelectedImage;

#if  0
	 BOOL						bNeedFree_elem_o		=				FALSE;
	 HashTblElementType			elem_o;
#endif




#if  0		//
		if  (  _tcscmp(  desc.pDw,  pDescParam->pDw  )
			||  _tcscmp(  desc.pBm,  pDescParam->pBm  )  )  
		{
			iRet  =  0;  goto  errLabel;
		}
#endif
		if  (  pQMem->messengerInfo.uiType  ==  CONST_objType_imGrp  )  {
			iRet  =  0;  goto  errLabel;
		}
		TCHAR  *  misServName  =  _T(  ""  );
		QY_MESSENGER_ID  *  pIdInfo  =  &pQMem->messengerInfo.idInfo;
		if  (  g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab,  misServName,  pIdInfo,  0,  pRegInfo  )  )  {
			iRet  =  0;  goto  errLabel;
		}
		if  (  pQMem->messengerInfo.idInfo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
			iRet  =  0;  goto  errLabel;
		}
						
		//
#ifdef  __DEBUG__
		traceLog(  _T(  "%I64u"  ),  pQMem->messengerInfo.idInfo.ui64Id  );
#endif

		QY_MESSENGER_INFO	messengerInfo;

		memcpy(  &messengerInfo,  &pQMem->messengerInfo,  sizeof(  messengerInfo  )  );
				
		
		//
		TCHAR	tBuf[256]  =  _T(  ""  );
		char	buf[256]	=	"";

		iObjType  =  CONST_objType_messenger;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  messengerInfo.idInfo.ui64Id  );
		myTChar2Utf8(  tBuf,  buf,  mycountof(  buf  )  );
		

		iObjId  =  getObjId_myDb(  pLeftView->m_var.pHashTbl_tree,  iObjType,  buf  );

								//  2007/06/03, 这里要加入内存中的管理队列
						QMOBJQ_PARAM_MISCLIENT		qmObjQParam;
						//
						memset(  &qmObjQParam,  0,  sizeof(  qmObjQParam  )  );
						//  uiType
						qmObjQParam.pSci  =  pSci;
						qmObjQParam.pMisCnt  =  pMisCnt;
						qmObjQParam.pDb  =  tmpObjDb.getAvailableDb(  pObjDb->iDsnIndex  );
						qmObjQParam.iDbType  =  pObjDb->cfg.iDbType;
						qmObjQParam.iObjType  =  iObjType;	//  CONST_objType_messenger;
						qmObjQParam.pClient  =  &messengerInfo;
						
						_sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "(%I64u)"  ),  messengerInfo.idInfo.ui64Id  );
						nImage  =  pQyMc->cfg.image.nImage_selectedMessenger;  nSelectedImage  =  pQyMc->cfg.image.nImage_selectedMessenger;
						//  getSnmpPortImages(  pQyMc,  &switchPort,  &nImage,  &nSelectedImage  );

						if  (  myAddOrRefreshTreeItem(  pLeftView,  htItem,  iObjId,  displayName,  nImage,  nSelectedImage,  &qmObjQParam  )  )  goto  errLabel;


		//
		iRet  =  0;
errLabel:


	return  iRet;

}


//
int  tmpHandler_addImObj_imGrps_av(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;
	int  i;
	QY_MC					*  pQyMc		=	 QY_GET_GBUF(  );

	
	CDlgLeftView_db			*	pLeftView			=				(  CDlgLeftView_db  *  )p0;
	 CTreeCtrl				*	m_TreeCtrl			=				pLeftView->m_TreeCtrl;	//  GetTreeCtrl(  );
	 //
	 COMMON_PARAM			*	pCommonParam		=	(  COMMON_PARAM  *  )p1;
	 //MY_REG_DESC  *  pDescParam  =  (  MY_REG_DESC  *  )pCommonParam->p0;
	 HTREEITEM							htItem				=				(  HTREEITEM  )pCommonParam->p1;
	 //  QY_MESSENGER_REGINFO	*  pRegInfo		=	 (  QY_MESSENGER_REGINFO  *  )pCommonParam->p2;
	 //
	 IM_GRP_INFO		*	pMem		=	(  IM_GRP_INFO  *  )p2;
	  


	QY_OBJ_DB						*	pObjDb				=				getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  );
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  -1;

		 int								iServiceId			=				CONST_qyServiceId_mis;
	 QY_SERVICEGUI_INFO			*	pSci					=				getServiceGuiInfo(  pQyMc,  iServiceId  );
	 if  (  !pSci  )  return  -1;
	 MC_VAR_isCli					*	pProcInfo				=				(  MC_VAR_isCli  *  )pSci->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 MIS_CNT						*	pMisCnt				=				getMisCntByName(  pProcInfo,  _T(  ""  )  );
	 if  (  !pMisCnt  )  return  -1;
	 
	 QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;



	 CQnmDb								tmpObjDb;
	 
	 if  (  !tmpObjDb.getAvailableDb(  pObjDb->iDsnIndex  )  )  {
		 traceLogA(  "得不到可用的连接数了"  );  
		 goto  errLabel;
	 }


	HTREEITEM					tmphtItem				=				NULL;
	 TCHAR						displayName[512]		=				_T(  ""  );		
	 int						iObjId					=				0;
	 int						iObjType				=				0;
	 int						nImage,  nSelectedImage;

	 //
	 if  (  pMem->usSubtype  ==  CONST_imGrpSubtype_msg  )  {
		 iRet  =  0;  goto  errLabel;
	 }
	 if  (  pMem->idInfo_creator.ui64Id  )  {
		 iRet  =  0;  goto  errLabel;
	 }
						
		//
#ifdef  __DEBUG__
		traceLog(  _T(  "imGrp: %I64u"  ),  pMem->idInfo.ui64Id  );
#endif
				
		
		//
		TCHAR	tBuf[256]  =  _T(  ""  );
		char	buf[256]	=	"";

		iObjType  =  CONST_objType_imGrp;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pMem->idInfo.ui64Id  );
		myTChar2Utf8(  tBuf,  buf,  mycountof(  buf  )  );
		
		IM_GRP_INFO	grpInfo;
		memcpy(  &grpInfo,  pMem,  sizeof(  grpInfo  )  );

		iObjId  =  getObjId_myDb(  pLeftView->m_var.pHashTbl_tree,  iObjType,  buf  );

								_sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s"  ),  grpInfo.name  );
						nImage  =  pQyMc->cfg.image.nImage_imGrp;  nSelectedImage  =  pQyMc->cfg.image.nImage_selectedImGrp;

						if  (  myAddOrRefreshTreeItem(  pLeftView,  htItem,  iObjId,  displayName,  nImage,  nSelectedImage,  NULL  )  )  goto  errLabel;


		//
		iRet  =  0;
errLabel:


	return  iRet;

}


//
int  tmpHandler_addImObj_imGrps_tmp(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;
	int  i;
	QY_MC					*  pQyMc		=	 QY_GET_GBUF(  );

	
	CDlgLeftView_db			*	pLeftView			=				(  CDlgLeftView_db  *  )p0;
	 CTreeCtrl				*	m_TreeCtrl			=				pLeftView->m_TreeCtrl;	//  GetTreeCtrl(  );
	 //
	 COMMON_PARAM			*	pCommonParam		=	(  COMMON_PARAM  *  )p1;
	 //MY_REG_DESC  *  pDescParam  =  (  MY_REG_DESC  *  )pCommonParam->p0;
	 HTREEITEM							htItem				=				(  HTREEITEM  )pCommonParam->p1;
	 //  QY_MESSENGER_REGINFO	*  pRegInfo		=	 (  QY_MESSENGER_REGINFO  *  )pCommonParam->p2;
	 //
	 IM_GRP_INFO		*	pMem		=	(  IM_GRP_INFO  *  )p2;
	  


	QY_OBJ_DB						*	pObjDb				=				getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  );
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  -1;

		 int								iServiceId			=				CONST_qyServiceId_mis;
	 QY_SERVICEGUI_INFO			*	pSci					=				getServiceGuiInfo(  pQyMc,  iServiceId  );
	 if  (  !pSci  )  return  -1;
	 MC_VAR_isCli					*	pProcInfo				=				(  MC_VAR_isCli  *  )pSci->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 MIS_CNT						*	pMisCnt				=				getMisCntByName(  pProcInfo,  _T(  ""  )  );
	 if  (  !pMisCnt  )  return  -1;
	 
	 QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;



	 CQnmDb								tmpObjDb;
	 
	 if  (  !tmpObjDb.getAvailableDb(  pObjDb->iDsnIndex  )  )  {
		 traceLogA(  "得不到可用的连接数了"  );  
		 goto  errLabel;
	 }


	HTREEITEM					tmphtItem				=				NULL;
	 TCHAR						displayName[512]		=				_T(  ""  );		
	 int						iObjId					=				0;
	 int						iObjType				=				0;
	 int						nImage,  nSelectedImage;

	 //
	 if  (  pMem->usSubtype  ==  CONST_imGrpSubtype_msg  )  {
		 iRet  =  0;  goto  errLabel;
	 }
	
	 //
	 if  (  !pMem->idInfo_creator.ui64Id  )   {
		 iRet  =  0;  goto  errLabel;
	 }

		//
#ifdef  __DEBUG__
		traceLog(  _T(  "imGrp: %I64u"  ),  pMem->idInfo.ui64Id  );
#endif
				
		
		//
		TCHAR	tBuf[256]  =  _T(  ""  );
		char	buf[256]	=	"";

		iObjType  =  CONST_objType_imGrp;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pMem->idInfo.ui64Id  );
		myTChar2Utf8(  tBuf,  buf,  mycountof(  buf  )  );
		
		IM_GRP_INFO	grpInfo;
		memcpy(  &grpInfo,  pMem,  sizeof(  grpInfo  )  );

		iObjId  =  getObjId_myDb(  pLeftView->m_var.pHashTbl_tree,  iObjType,  buf  );

								_sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s"  ),  grpInfo.name  );
						nImage  =  pQyMc->cfg.image.nImage_imGrp;  nSelectedImage  =  pQyMc->cfg.image.nImage_selectedImGrp;

						if  (  myAddOrRefreshTreeItem(  pLeftView,  htItem,  iObjId,  displayName,  nImage,  nSelectedImage,  NULL  )  )  goto  errLabel;


		//
		iRet  =  0;
errLabel:


	return  iRet;

}



//
int  tmpHandler_addImObj_imGrps_msg(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;
	int  i;
	QY_MC					*  pQyMc		=	 QY_GET_GBUF(  );

	
	CDlgLeftView_db			*	pLeftView			=				(  CDlgLeftView_db  *  )p0;
	 CTreeCtrl				*	m_TreeCtrl			=				pLeftView->m_TreeCtrl;	//  GetTreeCtrl(  );
	 //
	 COMMON_PARAM			*	pCommonParam		=	(  COMMON_PARAM  *  )p1;
	 //MY_REG_DESC  *  pDescParam  =  (  MY_REG_DESC  *  )pCommonParam->p0;
	 HTREEITEM							htItem				=				(  HTREEITEM  )pCommonParam->p1;
	 //  QY_MESSENGER_REGINFO	*  pRegInfo		=	 (  QY_MESSENGER_REGINFO  *  )pCommonParam->p2;
	 //
	 IM_GRP_INFO		*	pMem		=	(  IM_GRP_INFO  *  )p2;
	  


	QY_OBJ_DB						*	pObjDb				=				getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  );
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  -1;

		 int								iServiceId			=				CONST_qyServiceId_mis;
	 QY_SERVICEGUI_INFO			*	pSci					=				getServiceGuiInfo(  pQyMc,  iServiceId  );
	 if  (  !pSci  )  return  -1;
	 MC_VAR_isCli					*	pProcInfo				=				(  MC_VAR_isCli  *  )pSci->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 MIS_CNT						*	pMisCnt				=				getMisCntByName(  pProcInfo,  _T(  ""  )  );
	 if  (  !pMisCnt  )  return  -1;
	 
	 QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;



	 CQnmDb								tmpObjDb;
	 
	 if  (  !tmpObjDb.getAvailableDb(  pObjDb->iDsnIndex  )  )  {
		 traceLogA(  "得不到可用的连接数了"  );  goto  errLabel;
	 }


	HTREEITEM					tmphtItem				=				NULL;
	 TCHAR						displayName[512]		=				_T(  ""  );		
	 int						iObjId					=				0;
	 int						iObjType				=				0;
	 int						nImage,  nSelectedImage;

	 //
	 if  (  pMem->usSubtype  !=  CONST_imGrpSubtype_msg  )  {
		 iRet  =  0;  goto  errLabel;
	 }
						
		//
#ifdef  __DEBUG__
		traceLog(  _T(  "imGrp: %I64u"  ),  pMem->idInfo.ui64Id  );
#endif
				
		
		//
		TCHAR	tBuf[256]  =  _T(  ""  );
		char	buf[256]	=	"";

		iObjType  =  CONST_objType_imGrp;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pMem->idInfo.ui64Id  );
		myTChar2Utf8(  tBuf,  buf,  mycountof(  buf  )  );
		
		IM_GRP_INFO	grpInfo;
		memcpy(  &grpInfo,  pMem,  sizeof(  grpInfo  )  );

		iObjId  =  getObjId_myDb(  pLeftView->m_var.pHashTbl_tree,  iObjType,  buf  );

								_sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s"  ),  grpInfo.name  );
						nImage  =  pQyMc->cfg.image.nImage_imGrp;  nSelectedImage  =  pQyMc->cfg.image.nImage_selectedImGrp;

						if  (  myAddOrRefreshTreeItem(  pLeftView,  htItem,  iObjId,  displayName,  nImage,  nSelectedImage,  NULL  )  )  goto  errLabel;


		//
		iRet  =  0;
errLabel:


	return  iRet;

}


//
int  displayContent_imObjs_isClient_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int							iRet				=				-1;
	 QY_MC						*	pQyMc				=				QY_GET_GBUF(  );
	 CDlgLeftView_db			*	pLeftView			=				(  CDlgLeftView_db  *  )p0;
	 CTreeCtrl					*	m_TreeCtrl			=				pLeftView->m_TreeCtrl;	//  GetTreeCtrl(  );
	 //  CQyMcDoc					*	pDoc				=				pLeftView->GetDocument(  );
	 QY_MC_DOCSTRUCT  &  m_docStruct  =  pLeftView->m_docStruct;
	 
	 int						iServiceId				=				CONST_qyServiceId_mis;
	 QY_SERVICEGUI_INFO		*	pSci					=				getServiceGuiInfo(  pQyMc,  iServiceId  );
	 if  (  !pSci  )  return  -1;
	 MC_VAR_isCli				*	pProcInfo				=				(  MC_VAR_isCli  *  )pSci->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 MIS_CNT				*	pMisCnt					=				getMisCntByName(  pProcInfo,  pLeftView->m_var.misServName  );
	 if  (  !pMisCnt  )  return  -1;


	 if  (  m_docStruct.iDocType  !=  CONST_qyDocType_mcRootTree  )  return  -1;
	 
	 //
	 if  (  pQyMc->cfg.db.iDbType  !=  CONST_dbType_myDb  )  {
		 #ifdef  __DEBUG__
				 traceLog(  _T(  "only supported with myDb"  )  );
		 #endif
		 return  -1;
	 }


	 HTREEITEM					tmphtItem				=				NULL;
	 TCHAR						displayName[512]		=				_T(  ""  );		
	 int						iObjId					=				0;
	 int						nImage,  nSelectedImage;
	 int						iTopFieldId				=				0;
	 char						topLevelColName[128]	=				"'";
	 char					*	p						=				NULL;
	 int						i;
	 int						iObjType				=				0;
	 COMMON_PARAM				commonParam;
	 TCHAR						tBuf[1024];
	 char						buf[256];



	 QY_OBJ_DB					*	pObjDb				=				getProcedObjDb(  pQyMc,  0,  m_docStruct.u.treeList.tree.iDsnIndex  );
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  -1;

	 //
	 if  (  !pLeftView->m_var.pHashTbl_tree  )  {
		 showInfo_open0(  0,  0,  _T(  "displayContent_imObjs_isClient_myDb failed, pHashTbl_tree is null"  )  );
		 return  -1;
	 }	 
	 //  2014/04/17
	 pObjDb->pHashTbl_tree  =  pLeftView->m_var.pHashTbl_tree;


	 //
	 CMyDb				*	pDb	=	(  CMyDb  *  )pObjDb->pDb;

	 //  2014/05/27
	 //qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "displayContent_imObjs_isClient_myDb, addObjRegInfo starts ..."  )  );

	 //  下面增加新增的节点	
	 //
	 //  先将注册用户的单位放入视图
	 QY_MESSENGER_REGINFO	regInfo;
	 //
	 MACRO_makeCommonParam3(  0,  0,  &regInfo,  commonParam  );
	 qTraverse(  pDb->m_var.pQ_qyImObjRegInfoTab,  tmpHandler_addImObjRegInfo,  pLeftView,  &commonParam  );

	 //  2014/05/27
	 //qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "displayContent_imObjs_isClient_myDb, addObjRegInfo ends."  )  );

	 		
#if  0
		  //
		  //
		  //  再为未注册用户增加一个"未注册用户组"并刷新这个组
		  //
		  iObjType  =  CONST_objType_unRegGrp;
		  myTChar2Utf8(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_objIdStr_unRegGrp  ),  buf,  mycountof(  buf  )  );
		  iObjId  =  getObjId_myDb(  pLeftView->m_var.pHashTbl_tree,  iObjType,  buf  );  

		  _sntprintf(  displayName,  sizeof(  displayName  )  /  sizeof(  displayName[0]  ),  _T(  "%s"  ),  CString(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_objIdStr_unRegGrp  )  )  );
		  nImage  =  pQyMc->cfg.image.nImage_col2;  nSelectedImage  =  pQyMc->cfg.image.nImage_col3;
				
		  if  (  !(  tmphtItem  =  pLeftView->FindItemData(  iObjId,  TRUE,  pLeftView->m_var.htMyRootItem  )  )  )  {
			  tmphtItem  =  m_TreeCtrl->InsertItem(  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE  |  TVIF_PARAM,  
													  displayName,  
													  nImage,  
													  nSelectedImage,  
													  TVIS_EXPANDPARTIAL,  
													  TVIS_STATEIMAGEMASK, 
													  iObjId,  
													  pLeftView->m_var.htMyRootItem,  
													  TVI_LAST  );
			   //  m_TreeCtrl->SortChildren(  pLeftView->m_var.htMyRootItem  );  //  
				   
			   }
		   else  {				  
			     //  只刷新展开节点
				 TVITEM				tvItem;
				 
				 tvItem.mask  =  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE;
				 tvItem.hItem  =  tmphtItem;
				 tvItem.pszText  =  tBuf;
				 tvItem.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );
				 m_TreeCtrl->GetItem(  &tvItem  );
				 
				 if  (  _tcsicmp(  tBuf,  displayName  )  ||  tvItem.iImage  !=  nImage  ||  tvItem.iSelectedImage  !=  nSelectedImage  )  {
					 _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s"  ),  displayName  );
					 tvItem.iImage  =  nImage;
					 tvItem.iSelectedImage  =  nSelectedImage;
					 m_TreeCtrl->SetItem(  &tvItem  );
				 }

				 //  刷新展开节点
				 //  if  (  tvItem.state  &  TVIS_EXPANDED   )  pLeftView->bRefreshItem(  tmphtItem  );				   
				 if  (  pLeftView->m_TreeCtrl->ItemHasChildren(  tmphtItem  )  )  pLeftView->bRefreshItem(  tmphtItem  );				   

		   }
#endif

		   /////////////////////		   	
		   //
		  //  再增加一个"消息组",并刷新这个组
		  //
		  iObjType  =  CONST_objType_imGrps_msg;
		  myTChar2Utf8(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_objIdStr_imGrps_msg  ),  buf,  mycountof(  buf  )  );
		  iObjId  =  getObjId_myDb(  pLeftView->m_var.pHashTbl_tree,  iObjType,  buf  );
		  if  (  iObjId  <  0  )  goto  errLabel;;

		  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s"  ),  CString(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_objIdStr_imGrps_msg  )  )  );
		  nImage  =  pQyMc->cfg.image.nImage_imGrps;  nSelectedImage  =  pQyMc->cfg.image.nImage_selectedImGrps;
				
		  if  (  !(  tmphtItem  =  pLeftView->FindItemData(  iObjId,  TRUE,  pLeftView->m_var.htMyRootItem  )  )  )  {
			  tmphtItem  =  m_TreeCtrl->InsertItem(  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE  |  TVIF_PARAM,  
													  displayName,  
													  nImage,  
													  nSelectedImage,  
													  TVIS_EXPANDPARTIAL,  
													  TVIS_STATEIMAGEMASK, 
													  iObjId,  
													  pLeftView->m_var.htMyRootItem,  
													  TVI_LAST  );
			   //  m_TreeCtrl->SortChildren(  pLeftView->m_var.htMyRootItem  );  //  
				   
			   }
		   else  {				  
			     //  只刷新展开节点
				 TVITEM				tvItem;
				 
				 tvItem.mask  =  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE;
				 tvItem.hItem  =  tmphtItem;
				 tvItem.pszText  =  tBuf;
				 tvItem.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );
				 m_TreeCtrl->GetItem(  &tvItem  );
				 
				 if  (  _tcsicmp(  tBuf,  displayName  )  ||  tvItem.iImage  !=  nImage  ||  tvItem.iSelectedImage  !=  nSelectedImage  )  {
					 _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s"  ),  displayName  );
					 tvItem.iImage  =  nImage;
					 tvItem.iSelectedImage  =  nSelectedImage;
					 m_TreeCtrl->SetItem(  &tvItem  );
				 }

#if  0	//  2014/05/27
				 //  刷新展开节点
				 //  if  (  tvItem.state  &  TVIS_EXPANDED   )  pLeftView->bRefreshItem(  tmphtItem  );				   
				 if  (  pLeftView->m_TreeCtrl->ItemHasChildren(  tmphtItem  )  )  pLeftView->bRefreshItem(  tmphtItem  );				   
#endif

		   }


		   //
		   //
		  //  再增加一个"视频组",并刷新这个组
		  //
		  iObjType  =  CONST_objType_imGrps_av;
		  myTChar2Utf8(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_objIdStr_imGrps_av  ),  buf,  mycountof(  buf  )  );
		  iObjId  =  getObjId_myDb(  pLeftView->m_var.pHashTbl_tree,  iObjType,  buf  );
		  if  (  iObjId  <  0  )  goto  errLabel;;

		  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s"  ),  CString(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_objIdStr_imGrps_av  )  )  );
		  nImage  =  pQyMc->cfg.image.nImage_imGrps;  nSelectedImage  =  pQyMc->cfg.image.nImage_selectedImGrps;
				
		  if  (  !(  tmphtItem  =  pLeftView->FindItemData(  iObjId,  TRUE,  pLeftView->m_var.htMyRootItem  )  )  )  {
			  tmphtItem  =  m_TreeCtrl->InsertItem(  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE  |  TVIF_PARAM,  
													  displayName,  
													  nImage,  
													  nSelectedImage,  
													  TVIS_EXPANDPARTIAL,  
													  TVIS_STATEIMAGEMASK, 
													  iObjId,  
													  pLeftView->m_var.htMyRootItem,  
													  TVI_LAST  );
			   //  m_TreeCtrl->SortChildren(  pLeftView->m_var.htMyRootItem  );  //  
				   
			   }
		   else  {				  
			     //  只刷新展开节点
				 TVITEM				tvItem;
				 
				 tvItem.mask  =  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE;
				 tvItem.hItem  =  tmphtItem;
				 tvItem.pszText  =  tBuf;
				 tvItem.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );
				 m_TreeCtrl->GetItem(  &tvItem  );
				 
				 if  (  _tcsicmp(  tBuf,  displayName  )  ||  tvItem.iImage  !=  nImage  ||  tvItem.iSelectedImage  !=  nSelectedImage  )  {
					 _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s"  ),  displayName  );
					 tvItem.iImage  =  nImage;
					 tvItem.iSelectedImage  =  nSelectedImage;
					 m_TreeCtrl->SetItem(  &tvItem  );
				 }

#if  0	//  2014/05/27
				 //  刷新展开节点
				 //  if  (  tvItem.state  &  TVIS_EXPANDED   )  pLeftView->bRefreshItem(  tmphtItem  );				   
				 if  (  pLeftView->m_TreeCtrl->ItemHasChildren(  tmphtItem  )  )  pLeftView->bRefreshItem(  tmphtItem  );	
#endif

		   }


		   //		   		   
		   //
		   //
		  //  再增加一个"临时组",并刷新这个组。 2017/07/28
		  //
		  iObjType  =  CONST_objType_imGrps_tmp;
		  myTChar2Utf8(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_objIdStr_imGrps_tmp  ),  buf,  mycountof(  buf  )  );
		  iObjId  =  getObjId_myDb(  pLeftView->m_var.pHashTbl_tree,  iObjType,  buf  );
		  if  (  iObjId  <  0  )  goto  errLabel;;

		  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s"  ),  CString(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_objIdStr_imGrps_tmp  )  )  );
		  nImage  =  pQyMc->cfg.image.nImage_imGrps;  nSelectedImage  =  pQyMc->cfg.image.nImage_selectedImGrps;
				
		  if  (  !(  tmphtItem  =  pLeftView->FindItemData(  iObjId,  TRUE,  pLeftView->m_var.htMyRootItem  )  )  )  {
			  tmphtItem  =  m_TreeCtrl->InsertItem(  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE  |  TVIF_PARAM,  
													  displayName,  
													  nImage,  
													  nSelectedImage,  
													  TVIS_EXPANDPARTIAL,  
													  TVIS_STATEIMAGEMASK, 
													  iObjId,  
													  pLeftView->m_var.htMyRootItem,  
													  TVI_LAST  );
			   //  m_TreeCtrl->SortChildren(  pLeftView->m_var.htMyRootItem  );  //  
				   
			   }
		   else  {				  
			     //  只刷新展开节点
				 TVITEM				tvItem;
				 
				 tvItem.mask  =  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE;
				 tvItem.hItem  =  tmphtItem;
				 tvItem.pszText  =  tBuf;
				 tvItem.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );
				 m_TreeCtrl->GetItem(  &tvItem  );
				 
				 if  (  _tcsicmp(  tBuf,  displayName  )  ||  tvItem.iImage  !=  nImage  ||  tvItem.iSelectedImage  !=  nSelectedImage  )  {
					 _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s"  ),  displayName  );
					 tvItem.iImage  =  nImage;
					 tvItem.iSelectedImage  =  nSelectedImage;
					 m_TreeCtrl->SetItem(  &tvItem  );
				 }

#if  0	//  2014/05/27
				 //  刷新展开节点
				 //  if  (  tvItem.state  &  TVIS_EXPANDED   )  pLeftView->bRefreshItem(  tmphtItem  );				   
				 if  (  pLeftView->m_TreeCtrl->ItemHasChildren(  tmphtItem  )  )  pLeftView->bRefreshItem(  tmphtItem  );	
#endif

		   }




		   //
		   //  下面增加一个我节点
		   //
		   iObjType  =  CONST_objType_me;
		   myTChar2Utf8(  _T(  "me"  ),  buf,  mycountof(  buf  )  );
		   iObjId  =  getObjId_myDb(  pLeftView->m_var.pHashTbl_tree,  iObjType,  buf  );
		   if  (  iObjId  <  0  )  goto  errLabel;

		   
		   QM_OBJQ_MEM				mem;
		   unsigned  short			usRunningStatus;
		   //
		   _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s(%I64u)"  ),  pMisCnt->displayName,  pMisCnt->idInfo.ui64Id  );
		   if  (  findQMemByKey(  0,  pMisCnt->pObjQ,  &pMisCnt->idInfo,  &mem  )  )  usRunningStatus  =  CONST_usRunningStatus_offline;
		   else  {
			     QMEM_MESSENGER_CLI	*	pQMem;
			     pQMem  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;
				 usRunningStatus  =  pQMem->usRunningStatus;
		   }
		   //
		   getMessengerImages(  pQyMc,  usRunningStatus,  &nImage,  &nSelectedImage  );
				
		   if  (  !(  tmphtItem  =  pLeftView->FindItemData(  iObjId,  TRUE,  pLeftView->m_var.htMyRootItem  )  )  )  {
			   tmphtItem  =  m_TreeCtrl->InsertItem(  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE  |  TVIF_PARAM,  
													  displayName,  
													  nImage,  
													  nSelectedImage,  
													  TVIS_EXPANDPARTIAL,  
													  TVIS_STATEIMAGEMASK, 
													  iObjId,  
													  pLeftView->m_var.htMyRootItem,  
													  TVI_LAST  );
			   //  m_TreeCtrl->SortChildren(  pLeftView->m_var.htMyRootItem  );  //  
				   
			   QMOBJQ_PARAM_MISCLIENT	qmObjQParam;
			   //
			   memset(  &qmObjQParam,  0,  sizeof(  qmObjQParam  )  );
			   //  uiType
			   qmObjQParam.pSci  =  pSci;
			   qmObjQParam.pMisCnt  =  pMisCnt;
			   qmObjQParam.iObjType  =  CONST_objType_me;
			   
			   if  (  addToDisplayedObjQ(  &pLeftView->m_var.displayCtx,  &qmObjQParam,  pLeftView->m_hWnd,  tmphtItem  )  )  goto  errLabel;

				}
		   else  {				  
			     //  只刷新展开节点
				 TVITEM				tvItem;
				 
				 tvItem.mask  =  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE;
				 tvItem.hItem  =  tmphtItem;
				 tvItem.pszText  =  tBuf;
				 tvItem.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );
				 m_TreeCtrl->GetItem(  &tvItem  );
				 
				 if  (  _tcsicmp(  tBuf,  displayName  )  ||  tvItem.iImage  !=  nImage  ||  tvItem.iSelectedImage  !=  nSelectedImage  )  {
					 _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s"  ),  displayName  );
					 tvItem.iImage  =  nImage;
					 tvItem.iSelectedImage  =  nSelectedImage;
					 m_TreeCtrl->SetItem(  &tvItem  );
				 }

#if  0	//  2014/05/27
				 //  刷新展开节点
				 //  if  (  tvItem.state  &  TVIS_EXPANDED   )  pLeftView->bRefreshItem(  tmphtItem  );				   
				 if  (  pLeftView->m_TreeCtrl->ItemHasChildren(  tmphtItem  )  )  pLeftView->bRefreshItem(  tmphtItem  );				   
#endif

		   }


	 //
	 iRet  =  0;
errLabel:

	return  iRet;
 }


 //
#ifdef  __DEBUG__
int  tmpHandler_printHashElem(  void  *  p0,  void  *  p1,  HashTblElementType  *  pElem  )
{
	TCHAR				tBuf[256];
				  
	switch  (  pElem->iKeyType  )  {
			case  CONST_hashKeyType_imObj:  {
				  HashData_imObj  *  pData;
				  pData  =  (  HashData_imObj  *  )pElem->pData;
				  myUtf82TChar(  pElem->pKeyStr,  tBuf,  mycountof(  tBuf  )  );
				  traceLog(  _T(  "imObj: iObjType %d, %s"  ),  pData->iObjType,  tBuf  );
				  }
				  break;
			case  CONST_hashKeyType_iObjId:  {
				  HashData_iObjId  *  pData;
				  pData  =  (  HashData_iObjId  *  )pElem->pData;
				  traceLog(  _T(  "iObjId: iObjId %d,  hashIndex %d"  ),  pElem->iKeyVal,  pData->uiHashIndex  );
				  }
				  break;
			default:
				    traceLog(  _T(  "Unknown keyType %d"  ),  pElem->iKeyType  );
					break;
	}
	return  0;
}
#endif

 int  refreshItem_imObjs_isClient_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int								iRet				=				-1;
	 QY_MC							*	pQyMc				=				QY_GET_GBUF(  );
	 CDlgLeftView_db				*	pLeftView			=				(  CDlgLeftView_db  *  )p0;
	 HTREEITEM							htItem				=				(  HTREEITEM  )p1;
	 CTreeCtrl						*	m_TreeCtrl			=				pLeftView->m_TreeCtrl;	
	 //  CQyMcDoc						*	pDoc				=				pLeftView->GetDocument(  );
	 QY_MC_DOCSTRUCT				&	m_docStruct			=				pLeftView->m_docStruct;
	 if  (  m_docStruct.iDocType  !=  CONST_qyDocType_mcRootTree  )  return  -1;
	 QY_OBJ_DB						*	pObjDb				=				getProcedObjDb(  pQyMc,  0,  m_docStruct.u.treeList.tree.iDsnIndex  );
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  -1;
	 CMyDb				*	pDb	=	(  CMyDb  *  )pObjDb->pDb;

	 //
	 int								curiObjId,  iObjId,  iObjType;
	 QY_MESSENGER_REGINFO				regInfo;
	 QY_MESSENGER_INFO					messengerInfo;
	 //
	 QY_OBJINDEX_RCD					objIndex;
	 //  CRecordset							rs( ( CDatabase * )pObjDb->pDb );
	 //  CDBVariant							varVals[10];
	 int								index,  nFields;
	 //  TCHAR								sqlBuf[1024]		=				_T(  ""  );
	 //  TCHAR								whereClause[1024]	=				_T(  ""  );
	 int								nImage,  nSelectedImage;
	 HTREEITEM							tmphtItem			=				NULL;
	 TCHAR								displayName[512]	=				_T(  ""  );		
	 int								indexDisplayed,  indexToDisplay;
	 COMMON_PARAM						commonParam;
	 TCHAR								tBuf[256];
	 char								buf[256];
	 char								ip12Buf[128]		=				"";
	 //
	 int								iServiceId			=				CONST_qyServiceId_mis;
	 QY_SERVICEGUI_INFO			*	pSci					=				getServiceGuiInfo(  pQyMc,  iServiceId  );
	 if  (  !pSci  )  return  -1;
	 MC_VAR_isCli					*	pProcInfo				=				(  MC_VAR_isCli  *  )pSci->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 MIS_CNT						*	pMisCnt				=				getMisCntByName(  pProcInfo,  _T(  ""  )  );
	 if  (  !pMisCnt  )  return  -1;
	 CQnmDb								tmpObjDb;

	 BOOL								bNeedFree_elem_o	=				FALSE;
	 BOOL								bNeedFree_elem_obj	=				FALSE;
	 

	 //
	 QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	if  (  !tmpObjDb.getAvailableDb(  pObjDb->iDsnIndex  )  )  {
		 traceLogA(  "得不到可用的连接数了"  );  goto  errLabel;
	 }
	 
	 if  (  htItem  ==  pLeftView->m_var.htMyRootItem  )  {
		 iRet  =  0;  goto  errLabel;
	 }

#ifdef  __DEBUG__
		#if  0
			hashTbl_traverse(  pLeftView->m_var.pHashTbl_tree,  (  PF_commonHandler  )tmpHandler_printHashElem,  0,  0  );
		#endif
#endif

	 //
	 curiObjId  =  m_TreeCtrl->GetItemData(  htItem  );
	 //  if  (  g_dbFuncs.pf_getObjIndex(  pObjDb,  curiObjId,  &objIndex  )  )  goto  errLabel;
	 HashTblElementType  elem,  elem_o;
	 memset(  &elem,  0,  sizeof(  elem  )  );
	 elem.bKeyInt  =  TRUE;
	 elem.iKeyVal  =  curiObjId;
	 elem.iKeyType  =  CONST_hashKeyType_iObjId;
	 HashData_iObjId  data;
	 memset(  &data,  0,  sizeof(  data  )  );
	 elem.pData  =  &data;
	 elem.uiSize_pData  =  sizeof(  data  );
	 //
	 memset(  &elem_o,  0,  sizeof(  elem_o  )  );
	 //
	 if  (  hashTbl_find(  pLeftView->m_var.pHashTbl_tree,  &elem,  NULL,  &elem_o  )  )  {
		 goto  errLabel;
	 }
	 bNeedFree_elem_o  =  TRUE;

	 //
	 unsigned  int  uiHashIndex  =  0;
	 HashData_iObjId  *  pData  =  (  HashData_iObjId  *  )elem_o.pData;
	 if  (  !pData  )  goto  errLabel;
	 uiHashIndex  =  pData->uiHashIndex;

	 imObj_hash_free(  &elem_o  );
	 bNeedFree_elem_o  =  FALSE;

	 //	  
	 HashTblElementType  elem_obj;
	 memset(  &elem_obj,  0,  sizeof(  elem_obj  )  );
	 if  (  hashTbl_findEx(  pLeftView->m_var.pHashTbl_tree,  uiHashIndex,  &elem_o,  NULL,  &elem_obj  )  )  goto  errLabel;
	 bNeedFree_elem_obj  =  TRUE;

	 if  (  elem_obj.iKeyType  !=  CONST_hashKeyType_imObj  )  goto  errLabel;
	 HashData_imObj  *  pData_imObj  =  (  HashData_imObj  *  )elem_obj.pData;
	 iObjType  =  pData_imObj->iObjType;
	 
	 try  {
		  if  (  iObjType  ==  CONST_objType_dw  )  {
			  myUtf82TChar(  elem_obj.pKeyStr,  tBuf,  mycountof(  tBuf  )  );
			  //
			  MY_REG_DESC  desc;
			  memset(  &desc,  0,  sizeof(  desc  )  );
			  desc.pZb  =  _T(  ""  );
			  desc.pBb  =  _T(  ""  );
			  desc.pDw  =  tBuf;
			  desc.pBm  =  _T(  ""  );
			  desc.pSyr  =  _T(  ""  );
			  //
			  MACRO_makeCommonParam3(  &desc,  htItem,  &regInfo,  commonParam  );
			  qTraverse(  pDb->m_var.pQ_qyImObjRegInfoTab,  tmpHandler_addImObjRegInfo_bm,  pLeftView,  &commonParam  );

			  }
		  else  if  (  iObjType  ==  CONST_objType_bm  )  {
			  myUtf82TChar(  elem_obj.pKeyStr,  tBuf,  mycountof(  tBuf  )  );
			  //
			  MY_REG_DESC  desc;
			  memset(  &desc,  0,  sizeof(  desc  )  );
			  desc.pZb  =  _T(  ""  );
			  desc.pBb  =  _T(  ""  );
			  desc.pDw  =  tBuf;
			  desc.pBm  =  _T(  ""  );
			  desc.pSyr  =  _T(  ""  );

			  TCHAR  *  pT  =  _tcschr(  tBuf,  _T(  '\\'  )  );
			  if  (  !pT  )  goto  errLabel;
			  *pT  =  0;
			  pT  ++  ;
			  desc.pBm  =  pT;
			  //
			  MACRO_makeCommonParam3(  &desc,  htItem,  &regInfo,  commonParam  );
			  qTraverse(  pDb->m_var.pQ_qyImObjRegInfoTab,  tmpHandler_addImObjRegInfo_syr,  pLeftView,  &commonParam  );


		  }

		  else  if  (  iObjType  ==  CONST_objType_unRegGrp  )  {


			  MACRO_makeCommonParam3(  0,  htItem,  &regInfo,  commonParam  );

			  qTraverse(  pDb->m_var.pQ_qyImObjTab,  tmpHandler_addImObj_unRegMessenger,  pLeftView,  &commonParam  );
		  }
		  else  if  (  iObjType  ==  CONST_objType_syr  )  {
		  }

#if  0
		  else  if  (  objIndex.objType  ==  CONST_objType_syr  )  {
			        QY_MESSENGER_ID  idInfo;
					//
			        myTChar2Str(  objIndex.objIdStr0,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &idInfo  );
			        if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pObjDb->pDb,  pSci->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  pMisCnt->cfg.misServName,  &idInfo,  0,  &messengerInfo,  &regInfo,  NULL,  NULL  )  )  goto  errLabel;  

					//  2007/06/03, 这里要加入内存中的管理队列						
					QMOBJQ_PARAM_MISCLIENT		qmObjQParam;
					//
					memset(  &qmObjQParam,  0,  sizeof(  qmObjQParam  )  );
					//  uiType
					qmObjQParam.pSci  =  pSci;
					qmObjQParam.pMisCnt  =  pMisCnt;
					qmObjQParam.pDb  =  tmpObjDb.getAvailableDb(  pObjDb->iDsnIndex  );
					qmObjQParam.iDbType  =  pObjDb->cfg.iDbType;
					qmObjQParam.iObjType  =  CONST_objType_messenger;
					qmObjQParam.pClient  =  &messengerInfo;

					if  (  postRecentFriend(  qmObjQParam.pSci,  qmObjQParam.pMisCnt,  &qmObjQParam.pClient->idInfo,  0  )  )  traceLogA(  "postRecentFriend failed"  );  
		 			}
#endif
		  else  if  (  iObjType  ==  CONST_objType_messenger  )  {
			        QY_MESSENGER_ID  idInfo;
					//
					safeStrnCpy(  elem_obj.pKeyStr,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &idInfo  );
			        if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pDbFuncs,  pObjDb->pDb,  pSci->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  pMisCnt->cfg.misServName,  &idInfo,  0,  &messengerInfo,  &regInfo,  NULL,  NULL  )  )  goto  errLabel;  

					//  2007/06/03, 这里要加入内存中的管理队列						
					QMOBJQ_PARAM_MISCLIENT		qmObjQParam;
					//
					memset(  &qmObjQParam,  0,  sizeof(  qmObjQParam  )  );
					//  uiType
					qmObjQParam.pSci  =  pSci;
					qmObjQParam.pMisCnt  =  pMisCnt;
					qmObjQParam.pDb  =  tmpObjDb.getAvailableDb(  pObjDb->iDsnIndex  );
					qmObjQParam.iDbType  =  pObjDb->cfg.iDbType;
					qmObjQParam.iObjType  =  CONST_objType_messenger;
					qmObjQParam.pClient  =  &messengerInfo;

					if  (  postRecentFriend(    qmObjQParam.pMisCnt,  qmObjQParam.pClient->idInfo,  0  )  )  traceLogA(  "postRecentFriend failed"  );  

		  }
		  else  if  (  iObjType  ==  CONST_objType_me  )  {
		  }
		  else  if  (  iObjType  ==  CONST_objType_imGrps_av  )  {
			  
					MACRO_makeCommonParam3(  0,  htItem,  0,  commonParam  );

					qTraverse(  pDb->m_var.pQ_qyImGrpInfoTab,  tmpHandler_addImObj_imGrps_av,  pLeftView,  &commonParam  );
		  }
		  else  if  (  iObjType  ==  CONST_objType_imGrps_msg  )  {
					MACRO_makeCommonParam3(  0,  htItem,  0,  commonParam  );

					qTraverse(  pDb->m_var.pQ_qyImGrpInfoTab,  tmpHandler_addImObj_imGrps_msg,  pLeftView,  &commonParam  );
		  }
		  else  if  (  iObjType  ==  CONST_objType_imGrps_tmp  )  {
					MACRO_makeCommonParam3(  0,  htItem,  0,  commonParam  );

					qTraverse(  pDb->m_var.pQ_qyImGrpInfoTab,  tmpHandler_addImObj_imGrps_tmp,  pLeftView,  &commonParam  );
		  }

 

		}
	 catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "refreshItem_imObjs_isClient failed."  )  );
		   goto  errLabel;
	 }
	
	 iRet  =  0;

errLabel:
	 

	 if  (  bNeedFree_elem_o  )  {
		 imObj_hash_free(  &elem_o  );  
	 }
	 if  (  bNeedFree_elem_obj  )  {
		 imObj_hash_free(  &elem_obj  );
	 }
	 //if  (  rs.IsOpen(  )  )  rs.Close(  );

	 return  iRet;
}
