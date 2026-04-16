

#include	"stdafx.h"
#include	<qwidget.h>
#include	"qyMcMainCommon_qt.h"
#include	"AddGroupMemberDialog.h"
#include <myDb.h>





int  tmpHandler_printContactList_newGroup(void* p0, void* p1, void* p2)
{
    int  iRet = -1;
    COMMON_PARAM* pCommonParam = (COMMON_PARAM*)p0;
    COMMON_PARAM* pCommonParam1 = (COMMON_PARAM*)p1;
    //
    CMyDb* pDb = (CMyDb*)pCommonParam->p0;
    //  CListCtrl		*	pListCtrl		=  (  CListCtrl  *  )pCommonParam->p1;
    //HWND				hListCtrl = (HWND)pCommonParam->p1;
    //if (!hListCtrl)  goto  errLabel;
    int				iItem = (int)pCommonParam->p2;
    //
    //BOOL				bUnprocedOnly = (BOOL)p1;
    QList<FriendInfo>* pList = (QList<FriendInfo>*)pCommonParam1->p0;
    //
    QMEM_qyImObj* pQMem = (QMEM_qyImObj*)p2;
    int				index = 0;
    QY_MC* pQyMc = QY_GET_GBUF();

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



        FriendInfo fi;
        fi.dw = QString::fromUtf16((char16_t*)desc.pDw);
        fi.name = QString::fromUtf16((char16_t*)desc.pDw) + "  " + QString::fromUtf16((char16_t*)desc.pBm) + "  " + QString::fromUtf16((char16_t*)desc.pSyr) + "(" + QString::number(pQMem->messengerInfo.idInfo.ui64Id) + ")";
        fi.userId = QString::number(pQMem->messengerInfo.idInfo.ui64Id);

        //
        pList->append(fi);
    }

    iRet = 0;



errLabel:
    return  iRet;
}


__declspec(dllexport)  int  createTmpGrp_qt(HWND  hParent, IM_GRP_EX* p)
{
	
	int  iErr = -1;
	QY_MC* pQyMc = QY_GET_GBUF();

	//
	//
	QWidget* pParent = QWidget::find((WId)hParent);
	if (pParent == NULL)  return  -1;



    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    if (!pProcInfo)  return -1;
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    if (!pMisCnt)  return -1;



    //
    if (pQyMc->cfg.db.iDbType != CONST_dbType_myDb) {
#ifdef  __DEBUG__
        traceLog((TCHAR*)_T("only supported with myDb"));
#endif
        return -1;
    }
    QY_OBJ_DB* pObjDb = getProcedObjDb(pQyMc, 0, pQyMc->iDsnIndex_mainSys);
    if (!bObjDbAvail(pObjDb))  return -1;


    QList<QString> members;
    AddGroupMemberDialog dlg(members);
    QList<FriendInfo> friends;
    FriendInfo fs;
    QList<FriendInfo>* pList = &friends;


    //
    CMyDb* pDb = (CMyDb*)pObjDb->pDb;
    int cnt = 0;
    COMMON_PARAM	commonParam;
    COMMON_PARAM  commonParam1;
    //  MACRO_makeCommonParam3(  pDb,  pListCtrl,  (  void  *  )cnt,  commonParam  );
    MACRO_makeCommonParam3(pDb, 0, (void*)cnt, commonParam);
    MACRO_makeCommonParam3(pList, 0, 0, commonParam1);

    qTraverse(pDb->m_var.pQ_qyImObjTab, tmpHandler_printContactList_newGroup, &commonParam, &commonParam1);

    // //设置好友列表
    dlg.setAllFriends(friends);


	//CDlgCfgGrp		dlg(CWnd::FromHandle(hParent));
	//
	dlg.m_var.iType = CONST_dcgType_createTmpGrp;
	//
	//if (dlg.DoModal() != IDOK)  goto  errLabel;
    
	//
	//			
	p->common.uiType = CONST_imCommType_imGrp;
	p->common.usSubtype = CONST_imGrpSubtype_av;
	//
	p->usOp = 0;
	//
	int  i;
	for (i = 0; i < dlg.m_var.tmpGrp.usCnt; i++) {
		if (p->usCnt >= mycountof(p->mems))  break;
		p->mems[p->usCnt].grpMmem_idInfo.ui64Id = dlg.m_var.tmpGrp.pMems[i].idInfo.ui64Id;
		p->usCnt++;
		continue;
	}


	//
	

	//	req.common.idInfo_creator.ui64Id  =  pMisCnt->idInfo.ui64Id;


    if (dlg.exec() == 1)
    {
       
       // dlg.m_var.idInfo_tmpGrp.ui64Id;
      
        p->common.idInfo.ui64Id = dlg.m_var.idInfo_tmpGrp.ui64Id;
      

        return 0;
      
    }

errLabel:
	return  iErr;
}