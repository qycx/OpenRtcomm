
#include "stdafx.h"
#include	"qyMcMainCommon.h"
#include	"ctxQmc.h"
#include	"myDb.h"



#ifdef  __DEBUG__


int  tmpHandler_printContactList(void* p0, void* p1, void* p2)
{
	int  iRet = -1;
	COMMON_PARAM* pCommonParam = (COMMON_PARAM*)p0;
	//
	CMyDb* pDb = (CMyDb*)pCommonParam->p0;
	//  CListCtrl		*	pListCtrl		=  (  CListCtrl  *  )pCommonParam->p1;
	//HWND				hListCtrl = (HWND)pCommonParam->p1;
	//if (!hListCtrl)  goto  errLabel;
	int				iItem = (int)pCommonParam->p2;
	//
	BOOL				bUnprocedOnly = (BOOL)p1;
	//
	QMEM_qyImObj* pQMem = (QMEM_qyImObj*)p2;
	int				index = 0;
	QY_MC* pQyMc = g_pQyMc;// QY_GET_GBUF();

	QY_MESSENGER_REGINFO		regInfo;
	MY_REG_DESC					desc;
	TCHAR						tBuf[256];
	QY_DMITEM* pTable = getResTable(0, &pQyMc->cusRes, CONST_resId_objTypeTable);

	memset(&regInfo, 0, sizeof(regInfo));

	QM_dbFuncs* pDbFuncs = pQyMc->p_g_dbFuncs;
	if (!pDbFuncs)  goto  errLabel;
	QM_dbFuncs& g_dbFuncs = *pDbFuncs;


	if (pQMem->messengerInfo.iStatus == CONST_qyStatus_ok
		&& pQMem->messengerInfo.uiType != CONST_objType_imGrp)
	{

		_sntprintf(tBuf, mycountof(tBuf), _T("%I64u"), pQMem->messengerInfo.idInfo.ui64Id);

		if (!g_dbFuncs.pf_bGetMessengerRegInfoBySth(pDb, CONST_dbType_myDb, getResTable(0, &pQyMc->cusRes, CONST_resId_fieldIdTable), CONST_tabName_qyImObjRegInfoTab, pQMem->messengerInfo.misServName, &pQMem->messengerInfo.idInfo, 0, &regInfo)) {
			memset(&regInfo, 0, sizeof(regInfo));
		}
		int		tmpiRet;
		TCHAR	talkerDesc[128] = _T("");
		regInfo2Desc(0, &regInfo, &desc, talkerDesc, mycountof(talkerDesc), NULL, 0);

		traceLog((TCHAR*)_T("contact %I64u, %s %s %s "), pQMem->messengerInfo.idInfo.ui64Id, desc.pDw, desc.pBm, desc.pSyr);


	}

	iRet = 0;
errLabel:
	return  iRet;
}


int  tmpHandler_printImGrpList(void* p0, void* p1, void* p2)
{
	int  iRet = -1;
	COMMON_PARAM* pCommonParam = (COMMON_PARAM*)p0;
	//
	CMyDb* pDb = (CMyDb*)pCommonParam->p0;
	//  CListCtrl		*	pListCtrl		=  (  CListCtrl  *  )pCommonParam->p1;
	//HWND				hListCtrl = (HWND)pCommonParam->p1;
	//if (!hListCtrl)  goto  errLabel;
	int				iItem = (int)pCommonParam->p2;
	//
	BOOL				bUnprocedOnly = (BOOL)p1;
	//
	IM_GRP_INFO* pQMem = (IM_GRP_INFO*)p2;
	int				index = 0;
	QY_MC* pQyMc = g_pQyMc;// QY_GET_GBUF();

	QY_MESSENGER_REGINFO		regInfo;
	MY_REG_DESC					desc;
	TCHAR						tBuf[256];
	QY_DMITEM* pTable = getResTable(0, &pQyMc->cusRes, CONST_resId_objTypeTable);

	memset(&regInfo, 0, sizeof(regInfo));

	QM_dbFuncs* pDbFuncs = pQyMc->p_g_dbFuncs;
	if (!pDbFuncs)  goto  errLabel;
	QM_dbFuncs& g_dbFuncs = *pDbFuncs;


	//  if  (  pQMem->uiType  ==  CONST_objType_imGrp  )
	{

#if  0
		_sntprintf(tBuf, mycountof(tBuf), _T("%I64u"), pQMem->idInfo.ui64Id);
		index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);

		_sntprintf(tBuf, mycountof(tBuf), _T("%s"), pQMem->name);
		index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);

		_sntprintf(tBuf, mycountof(tBuf), _T("%s"), qyGetDesByType1(getResTable(0, &pQyMc->cusRes, CONST_resId_imGrpSubtypeTable), pQMem->usSubtype));
		index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);

		_sntprintf(tBuf, mycountof(tBuf), _T("%I64u"), pQMem->idInfo_creator.ui64Id);
		index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);
#endif

		//
		traceLog((TCHAR*)_T("Grp %I64u, %s, created by %I64u"), pQMem->idInfo.ui64Id, pQMem->name, pQMem->idInfo_creator.ui64Id);

	}

	iRet = 0;
errLabel:
	return  iRet;
}


int  tmpHandler_printImGrpMemList(void* p0, void* p1, void* p2)
{
	int  iRet = -1;
	COMMON_PARAM* pCommonParam = (COMMON_PARAM*)p0;
	//
	CMyDb* pDb = (CMyDb*)pCommonParam->p0;
	//  CListCtrl		*	pListCtrl		=  (  CListCtrl  *  )pCommonParam->p1;
	//HWND				hListCtrl = (HWND)pCommonParam->p1;
	//if (!hListCtrl)  goto  errLabel;
	int				iItem = (int)pCommonParam->p2;
	//
	BOOL				bUnprocedOnly = (BOOL)p1;

#if  10

	//
	IM_GRP_MEM* pQMem = (IM_GRP_MEM*)p2;
	int				index = 0;
	QY_MC* pQyMc = nullptr;// QY_GET_GBUF();
	return  -1;


	QM_dbFuncs* pDbFuncs = pQyMc->p_g_dbFuncs;
	if (!pDbFuncs)  goto  errLabel;
	QM_dbFuncs& g_dbFuncs = *pDbFuncs;


	QY_MESSENGER_REGINFO		regInfo;
	MY_REG_DESC					desc;
	TCHAR						tBuf[256];
	QY_DMITEM* pTable = getResTable(0, &pQyMc->cusRes, CONST_resId_objTypeTable);

	memset(&regInfo, 0, sizeof(regInfo));



	//  if  (  pQMem->uiType  ==  CONST_objType_imGrp  )
	{
#if  0
		_sntprintf(tBuf, mycountof(tBuf), _T(""));
		index = 0;  myListCtrl_InsertItem(hListCtrl, iItem, tBuf);

		_sntprintf(tBuf, mycountof(tBuf), _T("%s"), qyGetDesByType1(getResTable(0, &pQyMc->cusRes, CONST_resId_objTypeTable), CONST_objType_imGrp));
		index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);

		_sntprintf(tBuf, mycountof(tBuf), _T("%I64u"), pQMem->idInfo_grp.ui64Id);
		index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);

		//
		IM_GRP_INFO  grpInfo;
		if (!g_dbFuncs.pf_bGetImGrpInfoBySth(pDb, pQyMc->cfg.db.iDbType, _T(""), &pQMem->idInfo_grp, &grpInfo))  memset(&grpInfo, 0, sizeof(grpInfo));

		_sntprintf(tBuf, mycountof(tBuf), _T("%s"), grpInfo.name);
		index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);

		_sntprintf(tBuf, mycountof(tBuf), _T("%I64u"), pQMem->idInfo_mem.ui64Id);
		index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);

		if (!g_dbFuncs.pf_bGetMessengerRegInfoBySth(pDb, CONST_dbType_myDb, getResTable(0, &pQyMc->cusRes, CONST_resId_fieldIdTable), CONST_tabName_qyImObjRegInfoTab, pQMem->misServName, &pQMem->idInfo_mem, 0, &regInfo)) {
			memset(&regInfo, 0, sizeof(regInfo));
		}

		MY_REG_DESC  desc;
		regInfo2Desc(0, &regInfo, &desc, NULL, 0, NULL, 0);

		_sntprintf(tBuf, mycountof(tBuf), _T("%s"), desc.pDw);
		index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);
		_sntprintf(tBuf, mycountof(tBuf), _T("%s"), desc.pBm);
		index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);
		_sntprintf(tBuf, mycountof(tBuf), _T("%s"), desc.pSyr);
		index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);

		//
		_sntprintf(tBuf, mycountof(tBuf), _T("%s"), qyGetDesByType1(getResTable(0, &pQyMc->cusRes, CONST_resId_imGrpMemRoleTable), pQMem->iRole));
		index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);


		//
		_sntprintf(tBuf, mycountof(tBuf), _T(""));
		index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);


		_sntprintf(tBuf, mycountof(tBuf), _T("%s"), (pQMem->iStatus ? _T("Del") : _T("Ok")));
		index++;  myListCtrl_SetItemText(hListCtrl, iItem, index, tBuf);
#endif

		//
		traceLog((TCHAR*)_T("grp %I64u, mem %I64u"), pQMem->idInfo_grp.ui64Id, pQMem->idInfo_mem.ui64Id);

	}

#endif

	iRet = 0;
errLabel:
	return  iRet;
}




//
int  print_imObjs_isClient_myDb()
{
	int							iRet = -1;
	QY_MC* pQyMc = nullptr;// QY_GET_GBUF();
	return  -1;

	int						iServiceId = CONST_qyServiceId_mis;

	CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	if (!pProcInfo)  return  -1;
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName( _T(""));
	if (!pMisCnt)  return  -1;



	//
	if (pQyMc->cfg.db.iDbType != CONST_dbType_myDb) {
#ifdef  __DEBUG__
		traceLog((TCHAR*)_T("only supported with myDb"));
#endif
		return  -1;
	}


	HTREEITEM					tmphtItem = NULL;
	TCHAR						displayName[512] = _T("");
	int						iObjId = 0;
	int						nImage, nSelectedImage;
	int						iTopFieldId = 0;
	char						topLevelColName[128] = "'";
	char* p = NULL;
	int						i;
	int						iObjType = 0;
	TCHAR						tBuf[1024];
	char						buf[256];



	QY_OBJ_DB* pObjDb = getProcedObjDb(pQyMc, 0, pQyMc->iDsnIndex_mainSys);
	if (!bObjDbAvail(pObjDb))  return  -1;



	//
	CMyDb* pDb = (CMyDb*)pObjDb->pDb;

	//  2014/05/27
	//qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "displayContent_imObjs_isClient_myDb, addObjRegInfo starts ..."  )  );

	int cnt = 0;
	COMMON_PARAM	commonParam;
	//  MACRO_makeCommonParam3(  pDb,  pListCtrl,  (  void  *  )cnt,  commonParam  );
	MACRO_makeCommonParam3(pDb, 0, (void*)cnt, commonParam);

	qTraverse(pDb->m_var.pQ_qyImObjTab, tmpHandler_printContactList, &commonParam, NULL);
		
	//
	cnt = 0;
	MACRO_makeCommonParam3(pDb, 0, (void*)cnt, commonParam);

	qTraverse(pDb->m_var.pQ_qyImGrpInfoTab, tmpHandler_printImGrpList, &commonParam, NULL);

	//
	cnt = 0;
	//  MACRO_makeCommonParam3(  pDb,  pListCtrl,  (  void  *  )cnt,  commonParam  );
	MACRO_makeCommonParam3(pDb, 0, (void*)cnt, commonParam);

	qTraverse(pDb->m_var.pQ_qyImGrpMemTab, tmpHandler_printImGrpMemList, &commonParam, NULL);




	//
	iRet = 0;
errLabel:

	return  iRet;
}

#endif

