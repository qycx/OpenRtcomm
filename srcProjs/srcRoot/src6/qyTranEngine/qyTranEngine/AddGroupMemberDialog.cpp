


#include "AddGroupMemberDialog.h"
#include <QButtonGroup>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QIcon>
#include    <tchar.h>

#include <QDebug>
#include "ctxQmc_qt.h"
#include	"FuncsForIsCliHelp.h"
#include <dlgtalkproc.h>
#include <QScrollBar>


namespace {
    QButtonGroup list_buttons;
    AddGroupMemberDialog* dlg;
    QList<FriendInfo> select_friends;
    QMap<QString, QListWidgetItem*> left_items;
}

AddGroupMemberDialog::AddGroupMemberDialog(QList<QString>& members, QWidget* parent)
    : WinBaseDialog(parent)
{
    ui.setupUi(this);
    dlg = this;
    this->setWindowFlags(this->windowFlags() | Qt::SubWindow);
    ui.btnClose->setIcon(QIcon(":/Resources/Images/Title/sysbtn_close_normal.png"));
    ui.lab_count->setText(QStringLiteral("0/200人"));
    members_ = members;
    memset(&m_var, 0, sizeof(m_var));
    //listWidget
    ui.listWidget->verticalScrollBar()->setStyleSheet("QScrollBar{width:10px;}");

    //
    fill_usrs();

    //
    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    HWND  m_hWnd = (HWND)this->winId();
    pProcInfo->cfgGrp.hWnd_cfgGrp = m_hWnd;

}

AddGroupMemberDialog::~AddGroupMemberDialog()
{
    select_friends.clear();

    free_usrs();
  
}


int subDevListSort(const FriendInfo& info1, const FriendInfo& info2)
{
    int iRet =  _tcsicmp((wchar_t*)(info1.name).utf16(), (wchar_t*)(info2.name).utf16());  //升序排列  
    if (iRet < 0) return true;
    return false;

 //return info1->posid < info2->posid;     //降序排列  
}


void AddGroupMemberDialog::setAllFriends(QList<FriendInfo> friends)
{
    friends_.clear();
    qSort(friends.begin(), friends.end(), subDevListSort);
 
    friends_ = friends;

#if 0 
    QMap<QString, QList<FriendInfo>> map;
    for (size_t i = 0; i < friends.size(); i++)
    {
        if (friends[i].dw.isEmpty())
        {
            friends[i].dw = "none";
        }
        if (!map.keys().contains(friends[i].dw))
        {
            QList<FriendInfo> ls;
            ls.append(friends[i]);
            map[friends[i].dw] = ls;
        }
        else
        {
            auto& ls = map[friends[i].dw];
            ls.append(friends[i]);
        }
    }
    for (int i = 0; i < map.values().size(); i++)
    {
        QList<FriendInfo> ls = map.values()[i];
        for (int k = 0; k < ls.size(); k++)
        {
            friends_.append(ls[k]);
        }
    }
#endif

    loadFriends();
 
}

void AddGroupMemberDialog::clearListWidget(QListWidget* list)
{
    int counter = list->count();
    for (int index = 0; index < counter; index++)
    {
        QListWidgetItem* item = list->takeItem(index);
        QWidget* widget = list->itemWidget(item);
        delete widget;
    }
    list->clear();
}

void AddGroupMemberDialog::updateSelectItems()
{
    clearListWidget(ui.listWidget_2);
    for (int i = 0; i < select_friends.size(); i++)
    {
        SelectMemberItemWidget* button = new SelectMemberItemWidget(select_friends[i]);
        QListWidgetItem* item = new QListWidgetItem();
        item->setData(Qt::UserRole, select_friends[i].userId);
        item->setFlags(Qt::ItemFlag::NoItemFlags);
        QSize sz = item->sizeHint();
        sz.setHeight(button->height());
        item->setSizeHint(sz);//设置每个item的大小
        ui.listWidget_2->addItem(item);
        ui.listWidget_2->setItemWidget(item, button);
    }
    ui.lab_count->setText(QStringLiteral("%1/200人").arg(select_friends.size()));
    ui.pushButton->setEnabled(select_friends.size() > 0);
}

void AddGroupMemberDialog::loadFriends(QString str)
{
    clearListWidget(ui.listWidget);
    left_items.clear();
    QY_MC* pQyMc = QY_GET_GBUF();
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    if (!pProcInfo)  return ;
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    QList<FriendInfo> friends;
    for (size_t i = 0; i < friends_.size(); i++)
    {
        if ( QString::number(pMisCnt->idInfo.ui64Id) == friends_[i].userId) {
            continue;
        }
        if (friends_[i].name.contains(str))
        {
            friends.append(friends_[i]);
        }
    }

    for (int i = 0; i < friends.size(); i++)
    {
        if (QString::number(pMisCnt->idInfo.ui64Id) == friends[i].userId) {
            continue;
        }
        if (members_.contains(friends[i].userId))
        {
            continue;
        }
        MemberItemWidget* button = new MemberItemWidget(friends[i], isInSelected(friends[i].userId));
        connect(button, &MemberItemWidget::clicked, this, &AddGroupMemberDialog::slot_membertem_clicked);
        QListWidgetItem* item = new QListWidgetItem();
        item->setData(Qt::UserRole, friends[i].userId);
        item->setFlags(Qt::ItemFlag::NoItemFlags);
        QSize sz = item->sizeHint();
        sz.setHeight(button->height());
        item->setSizeHint(sz);//设置每个item的大小
        ui.listWidget->addItem(item);
        ui.listWidget->setItemWidget(item, button);
        left_items[friends[i].userId] = item;
    }
}



bool AddGroupMemberDialog::isInSelected(QString userId)
{
    for (int i = 0; i < select_friends.size(); i++)
    {
        if (select_friends[i].userId == userId)
        {
            return true;
        }
    }
    return false;
}


void AddGroupMemberDialog::slot_text_changed(QString str)
{
    loadFriends(str);
}

void AddGroupMemberDialog::slot_membertem_clicked()
{
    MemberItemWidget* button = (MemberItemWidget*)sender();
    if (!button->isSelected() && select_friends.size() >= 200)
    {
        return;
    }
    button->setSelected(!(button->isSelected()));
}


bool AddGroupMemberDialog::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
    Q_UNUSED(eventType);
    MSG* msg = reinterpret_cast<MSG*>(message);
    UINT m = msg->message;
    if (m == WM_COMMAND || m == CONST_qyWm_comm || m == CONST_qyWm_postComm)
    {
        return postMessageQt(msg, result);
    }


    return  false;
}


bool AddGroupMemberDialog::postMessageQt(MSG* message, long* result)
{
    /*if (message->message == CONST_qyWm_postComm) {
        OnQyPostComm(message->wParam, message->lParam);
    }*/
    if (message->message == CONST_qyWm_comm) {
        OnQyComm(message->wParam, message->lParam);
    }
    return true;
}


LRESULT  AddGroupMemberDialog::OnQyComm(WPARAM  wParam, LPARAM  lParam)
{
    long				lRet = -1;
    QY_WMBUF_COMM* pComm = (QY_WMBUF_COMM*)lParam;
    QY_MC* pQyMc = QY_GET_GBUF();
    CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

    if (!pComm)  return  -1;

    switch (pComm->uiType) {
    case  CONST_misMsgType_input: {
        MIS_MSG_INPUT* pMsgInput = (MIS_MSG_INPUT*)pComm;
        IM_CONTENTU* pContent = M_getMsgContent(pMsgInput->ucFlg, &pMsgInput->data);
        switch (pContent->uiType) {
        case  CONST_imCommType_imGrp:
            int  ill;
            ill = 0;
            //
            m_var.idInfo_tmpGrp.ui64Id = pContent->imGrpEx.common.idInfo.ui64Id;
            //
            notifyProgressEnd(&pQyMc->gui.progress, pMsgInput->uiTranNo, 0);
            //
            break;
        default:
            break;
        }
    }
                                break;
    default:
        break;
    }

    lRet = QY_RC_WMOK;

    //  errLabel:

    return  lRet;

}

QList<FriendInfo> AddGroupMemberDialog::getSelects()
{
    return select_friends;
}


BOOL  tmpHandle_bImGrp(void* p0, void* p1, void* p2)
{
    BOOL  bRet = FALSE;
    QY_MESSENGER_ID* pIdInfo_grp = (QY_MESSENGER_ID*)p0;
    //
    IM_GRP_MEM* pQMem = (IM_GRP_MEM*)p2;

    if (pQMem->idInfo_grp.ui64Id == pIdInfo_grp->ui64Id) {
        bRet = TRUE;
    }


    return  bRet;


}

//
int  tmpHandler_bFillUsrs_myDb(void* p0, void* p1, void* p2)
{
    int					iRet = -1;

    COMMON_PARAM* pCommonParam = (COMMON_PARAM*)p0;
    TMP_usrs* pUsrs = (TMP_usrs*)p1;
    //
    HWND				hDlgTalk = (HWND)pCommonParam->p0;
    PARAM_PROC_ROW* pParam = (PARAM_PROC_ROW*)pCommonParam->p1;
    CMyDb* pDb = (CMyDb*)pCommonParam->p2;
    //
    QMEM_qyImObj* pQMem = (QMEM_qyImObj*)p2;

    //
    QY_MC* pQyMc = QY_GET_GBUF();
    if (!pQyMc)  return  -1;
    QM_dbFuncs* pDbFuncs = pQyMc->p_g_dbFuncs;
    if (!pDbFuncs)  return  -1;
    QM_dbFuncs& g_dbFuncs = *pDbFuncs;
    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    if (!pMisCnt)  return  -1;

    //
    if (!pParam) {
        return  -1;
    }

    //
    int  iDbType = CONST_dbType_myDb;


    //
    QY_MESSENGER_REGINFO		regInfo;
    QY_MESSENGER_REGINFO* pRegInfo = &regInfo;


    if (pQMem->messengerInfo.uiType != CONST_objType_imGrp)
    {
        //  2014/04/20
        int  id_imGrpMem = 0;//pQMem->id;

        //

        int  iDbType = CONST_dbType_myDb;
        if (!g_dbFuncs.pf_bGetMessengerRegInfoBySth(pDb, iDbType, getResTable(0, &pQyMc->cusRes, CONST_resId_fieldIdTable), CONST_tabName_qyImObjRegInfoTab, _T(""), &pQMem->messengerInfo.idInfo, 0, &regInfo)) {
            memset(&regInfo, 0, sizeof(regInfo));
        }


        QY_MC* pQyMc = QY_GET_GBUF();
        MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;

        //
        MY_REG_DESC				desc;
        TCHAR						talkerDesc[128 + 1];
        TCHAR						displayName[64 + 1];
        int						nImage, nSelectedImage;

        if (regInfo2Desc(0, pRegInfo, &desc, talkerDesc, mycountof(talkerDesc), displayName, mycountof(displayName)))  goto  errLabel;

        nImage = pQyMc->cfg.image.nImage_messenger;  nSelectedImage = pQyMc->cfg.image.nImage_selectedMessenger;

        {	 //  
            QM_OBJQ_MEM				mem;
            QMEM_MESSENGER_CLI* pQMem = NULL;
            QY_MESSENGER_INFO			messengerInfo;
            void* pDb = NULL;
            int						i;

            CQnmDb						tmpObjDb;
            pDb = tmpObjDb.getAvailableDb(pQyMc->iDsnIndex_mainSys);

            //  ÏÈÓÃregInfoÌî³äÒ»ÏÂmessengerInfo, ÒòÎªÏÂÃæµÄpClientÖ»ÄÜÖ¸ÏòmessengerInfo
            memset(&messengerInfo, 0, sizeof(messengerInfo));
            //
            lstrcpyn(messengerInfo.misServName, regInfo.addr.misServName, mycountof(messengerInfo.misServName));
            messengerInfo.idInfo.ui64Id = regInfo.addr.idInfo.ui64Id;

            //               
            if (procQmObjQ(pProcInfo->pSgiParam, (QM_OBJQ*)pMisCnt->pObjQ, pDb, pQyMc->cfg.db.iDbType, CONST_objType_messenger, &messengerInfo, &mem))  goto  errLabel;
            if (!mem.pQMemObj)  goto  errLabel;

            pQMem = (QMEM_MESSENGER_CLI*)mem.pQMemObj;

            //  ÕâÀïÔÝÊ±ÔÚÕâÀï¸üÐÂÏÔÊ¾Ãû³Æ  
            lstrcpyn(pQMem->talkerDesc, talkerDesc, mycountof(pQMem->talkerDesc));
            lstrcpyn(pQMem->displayName, displayName, mycountof(pQMem->displayName));		//  2007/09/02

            //
            getMessengerImages(pQyMc, pQMem->usRunningStatus, &nImage, &nSelectedImage);

            //  2017/08/08
            if (pParam->ucbNoMe) {
                if (pMisCnt->idInfo.ui64Id == pQMem->idInfo.ui64Id) {
                    iRet = 0;  goto  errLabel;
                }
            }

            //
            if (pUsrs) {
                if (pUsrs->usCnt < pUsrs->usMaxCnt) {
                    TMP_usr* pMem = &pUsrs->pMems[pUsrs->usCnt];
                    pMem->idInfo.ui64Id = pQMem->idInfo.ui64Id;
                    //
                    //pMem->id_imGrpMem  =  id_imGrpMem;
                    //
                    safeTcsnCpy(displayName, pMem->displayName, mycountof(pMem->displayName));
                    safeTcsnCpy(talkerDesc, pMem->talkerDesc, mycountof(pMem->talkerDesc));
                    //
                    pUsrs->usCnt++;

                }

            }

            //
            pParam->nItem++;

        }


    }

    iRet = 0;
errLabel:
    return  iRet;
}


__declspec(dllexport)  BOOL  bFillUsrs_myDb(HWND  hDlgTalkParam, void* pDbParam, void* pParam, TMP_usrs* pUsrs)
{
    BOOL				bRet = FALSE;
    CMyDb* pDb = (CMyDb*)pDbParam;
    COMMON_PARAM		commonParam;
    MACRO_makeCommonParam3(hDlgTalkParam, pParam, pDb, commonParam);

    //
    qTraverse(pDb->m_var.pQ_qyImObjTab, tmpHandler_bFillUsrs_myDb, &commonParam, pUsrs);

    bRet = TRUE;
errLabel:
    return  bRet;
}






int  AddGroupMemberDialog::add_mem(QY_MESSENGER_ID* pIdInfo)
{
    TMP_usrs* p = &m_var.tmpGrp;

    int  i;

    //
    if (isGrpMem(pIdInfo))  return  0;

    if (p->usCnt >= p->usMaxCnt)  return  -1;

    TMP_usr* pMem = &p->pMems[p->usCnt];
    pMem->idInfo.ui64Id = pIdInfo->ui64Id;
    getDescByIdInfo(0, pIdInfo, pMem->talkerDesc, mycountof(pMem->talkerDesc), pMem->displayName, mycountof(pMem->displayName));

    p->usCnt++;


    return  0;
}

//
bool  AddGroupMemberDialog::isGrpMem( QY_MESSENGER_ID * pIdInfo )
{
    BOOL  bRet = FALSE;

    int  i;
    TMP_usrs* p = &m_var.tmpGrp;

    for (i = 0; i < p->usCnt; i++) {
        if (p->pMems[i].idInfo.ui64Id == pIdInfo->ui64Id)  return  TRUE;
    }


    return  bRet;
}


int  AddGroupMemberDialog::fill_usrs()
{
    int  iErr = -1;
    QY_MC* pQyMc = QY_GET_GBUF();
    MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    if (!pMisCnt)  return  -1;

    //
    PARAM_PROC_ROW		param;

    memset(&param, 0, sizeof(param));

    //
    {
        CQnmDb				db;

        if (!db.getAvailableDb(pQyMc->iDsnIndex_mainSys))  goto  errLabel;


        //
        memset(&param, 0, sizeof(param));
        bFillUsrs_myDb(0, db.m_pDbMem->pDb, &param, 0);

        //
        TMP_usrs* p = &m_var.tmpUsrs;

        //
        free_usrs();

        //
        p->usMaxCnt = param.nItem;
        int  size = sizeof(TMP_usr) * p->usMaxCnt;
        p->pMems = (TMP_usr*)malloc(size);
        if (!p->pMems)  goto  errLabel;
        memset(p->pMems, 0, size);

        //
        memset(&param, 0, sizeof(param));
        //
        if (m_var.iType == CONST_dcgType_sendFile) {
            param.ucbNoMe = TRUE;
        }
        //
        bFillUsrs_myDb(0, db.m_pDbMem->pDb, &param, p);

        //
        int  i;
        TCHAR  tBuf[128];

        //
        p = &m_var.tmpGrp;

        //
        p->usMaxCnt = m_var.tmpUsrs.usMaxCnt;
        size = sizeof(TMP_usr) * p->usMaxCnt;
        p->pMems = (TMP_usr*)malloc(size);
        if (!p->pMems)  goto  errLabel;
        memset(p->pMems, 0, size);


        //
        if (m_var.iType == CONST_dcgType_createTmpGrp) {
            //
            i = 0;
            TMP_usr* pMem = &p->pMems[i];
            pMem->idInfo.ui64Id = pMisCnt->idInfo.ui64Id;
            getDescByIdInfo(0, &pMem->idInfo, pMem->talkerDesc, mycountof(pMem->talkerDesc), pMem->displayName, mycountof(pMem->displayName));
            p->usCnt++;
        }
        else  if (m_var.iType == CONST_dcgType_modifyTmpGrp) {
            //
            for (i = 0; i < p->usMaxCnt; i++) {
                if (i >= m_var.pImGrpEx_input->usCnt)  break;
                TMP_usr* pMem = &p->pMems[i];
                pMem->idInfo.ui64Id = m_var.pImGrpEx_input->mems[i].grpMmem_idInfo.ui64Id;
                getDescByIdInfo(0, &pMem->idInfo, pMem->talkerDesc, mycountof(pMem->talkerDesc), pMem->displayName, mycountof(pMem->displayName));
                p->usCnt++;
            }

        }



    }


    iErr = 0;

errLabel:

    return  iErr;
}

//
int  AddGroupMemberDialog::free_usrs()
{
    if (m_var.tmpUsrs.pMems) {
        free(m_var.tmpUsrs.pMems);  m_var.tmpUsrs.pMems = 0;
    }
    memset(&m_var.tmpUsrs, 0, sizeof(m_var.tmpUsrs));

    //
    MACRO_safeFree(m_var.tmpGrp.pMems);
    memset(&m_var.tmpGrp, 0, sizeof(m_var.tmpGrp));

    return  0;
}

void AddGroupMemberDialog::slot_button()
{
    if (sender() == ui.pushButton)
    {
        QY_MESSENGER_ID idinfo;
        groupName = ui.groupName->text();
        for (int i = 0; i < select_friends.size(); i++)
        {
            idinfo.ui64Id = (select_friends[i].userId).toInt();
            add_mem(&idinfo);

        }
        
   
        //
        int  iErr = -1;
        QY_MC* pQyMc = QY_GET_GBUF();
        MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();
        MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
        if (!pMisCnt)  return;

        //再添加一次本人
        idinfo.ui64Id = pMisCnt->idInfo.ui64Id;
        add_mem(&idinfo);
        FUNCS_for_isCliHelp* pFuncs = QY_GET_FUNCS_for_isCliHelp(pProcInfo);
        if (!pFuncs)  return;

        CQnmDb  db;
        if (!db.getAvailableDb(pQyMc->iDsnIndex_mainSys))  goto  errLabel;

        //
        if (m_var.iType == CONST_dcgType_createTmpGrp
            || m_var.iType == CONST_dcgType_modifyTmpGrp)
        {

            //
            TCHAR  grpName[128] = _T("");
            QString groupName = ui.groupName->text();
           
           // GetDlgItemText(IDC_EDIT_grpName, grpName, mycountof(grpName));

            //
            MACRO_prepareForTran();

            //
            IM_GRP_EX	req = { 0 };
            {
                CQyMalloc					mallocObj;
                IM_L_STREAM* pStream = NULL;

                if (!(pStream = (IM_L_STREAM*)mallocObj.mallocf(sizeof(IM_L_STREAM)))) {
#ifdef  __DEBUG__
              //      traceLogA("sndDevInfo_qmc . malloc failed.");
#endif
                    goto  errLabel;
                }

                unsigned  int		len;
                char				buf[256];

                //
                IM_GRP_INFO* pReq = &req.common;

                //
                memset(&req, 0, sizeof(req));
                req.common.uiType = CONST_imCommType_imGrp;
                //myTChar2Utf8(  passwd0,  buf,  mycountof(  buf  )  );
                //	

                if (groupName == "") {

                    for (int i = 0; i < m_var.tmpGrp.usCnt; i++) {
                        TCHAR syr[125];
                        if (m_var.tmpGrp.usCnt >= 3) {
                            if (i >= 3) {
                             break;
                            }
                            getTalkerDesc(m_var.tmpGrp.pMems[i].idInfo, 0, null, 0, null, null, 0, null, 0, syr, mycountof(syr));
                            if (QString::fromStdWString(syr) == "") {
                                groupName = groupName + " (" + QString::number(m_var.tmpGrp.pMems[i].idInfo.ui64Id) + ")";
                            }
                            else {
                                groupName = groupName + " " + QString::fromStdWString(syr);
                            }
                        }
                        else {
                            getTalkerDesc(m_var.tmpGrp.pMems[i].idInfo, 0, null, 0, null, null, 0, null, 0, syr, mycountof(syr));
                            if (QString::fromStdWString(syr) == "") {
                                groupName = groupName + " (" + QString::number(m_var.tmpGrp.pMems[i].idInfo.ui64Id) + ")";
                            }
                            else {
                                groupName = groupName + " " + QString::fromStdWString(syr);
                            }
                        }
                        
                       
                        
                        
                        continue;
                    }


                }


                lstrcpyn(grpName, (TCHAR*)groupName.utf16(), mycountof(grpName));
                lstrcpyn(pReq->name, grpName, mycountof(pReq->name));
                pReq->usSubtype = CONST_imGrpSubtype_av;	//  pGrpInfo->usSubtype;
                //
                if (m_var.iType == CONST_dcgType_createTmpGrp) {
                    req.usOp = CONST_imOp_new;
                }
                else {
                    req.usOp = CONST_imOp_modify;
                    req.common.idInfo.ui64Id = m_var.pImGrpEx_input->common.idInfo.ui64Id;
                }
                //
                int  i;
                for (i = 0; i < m_var.tmpGrp.usCnt; i++) {
                    if (req.usCnt >= mycountof(req.mems))  break;
                    req.mems[req.usCnt].grpMmem_idInfo.ui64Id = m_var.tmpGrp.pMems[i].idInfo.ui64Id;
                    req.usCnt++;
                    continue;
                }


                //  2010/08/14
                pFuncs->pf_startProgress(&pQyMc->gui.progress, uiTranNo);

                //
                MACRO_memset_imLStream(pStream);
                pStream->uiType = CONST_imCommType_lStream;
                pStream->uiContentType = req.common.uiType;
                len = sizeof(pStream->buf);
                if (imGrpEx2Stream(pStream->uiContentType, &req, pStream->buf, &len))  goto  errLabel;
                pStream->ulStreamLen = len;
                len += offsetof(IM_L_STREAM, buf);
                //
                postMsg2Mgr_mc(pMisCnt, NULL, CONST_misMsgType_req, 0, CONST_qyCmd_refreshImObjListReq, tStartTran, uiTranNo, 0, (char*)pStream, len, NULL, 0, 0, NULL, 0);
            }

            //  pProcInfo->bInProgress_toSetPasswd  =  TRUE;
            HWND  m_hWnd = (HWND)this->winId();
            //
            if (showProgress(&pQyMc->gui.progress, &pQyMc->cusRes, m_hWnd, _T("Please waiting"), NULL, 30, -1, uiTranNo) != IDOK) {
                goto  errLabel;
            }

            //
            QM_dbFuncs* pDbFuncs = pQyMc->p_g_dbFuncs;
            if (!pDbFuncs)  goto  errLabel;
            QM_dbFuncs& g_dbFuncs = *pDbFuncs;


            //
          
            req.common.idInfo.ui64Id = m_var.idInfo_tmpGrp.ui64Id;
            req.common.idInfo_creator.ui64Id = pMisCnt->idInfo.ui64Id;

            //
            time_t  t;  time(&t);
            recoverImGrp(&g_dbFuncs, db.m_pDbMem->pDb, db.m_pDbMem->iDbType, CONST_fieldIdTable_en, CONST_objType_imGrp, &req.common, t, FALSE);

            CMyDb* pDb = (CMyDb*)db.m_pDbMem->pDb;
            //
            qRemoveMsg(pDb->m_var.pQ_qyImGrpMemTab, tmpHandle_bImGrp, &req.common.idInfo, 0);

            //
            int  i;
            for (i = 0; i < m_var.tmpGrp.usCnt; i++) {
                IM_GRP_MEM   imGrpMem = { 0 };
                imGrpMem.idInfo_grp.ui64Id = req.common.idInfo.ui64Id;
                imGrpMem.idInfo_mem.ui64Id = m_var.tmpGrp.pMems[i].idInfo.ui64Id;
                //
                recoverImGrpMem(&g_dbFuncs, db.m_pDbMem->pDb, db.m_pDbMem->iDbType, &imGrpMem, t);
            }

        }

        //
        iErr = 0;

    errLabel:
        if (iErr) {
            return;
        }
        this->accept();
    }
}

#pragma region MemberItemWidget
MemberItemWidget::MemberItemWidget(FriendInfo friendInfo, bool selected, QWidget* parent /*= nullptr*/) :QPushButton(parent)
{
    friendInfo_ = friendInfo;
    this->setObjectName("MemberItem");
    this->setCheckable(true);
    this->setFixedHeight(60);
    QHBoxLayout* layout = new QHBoxLayout;
    layout->setContentsMargins(12, 0, 12, 0);
    layout->setSpacing(12);
    this->setLayout(layout);
    lab_img_ = new QLabel(this);
    lab_img_->setFixedSize(34, 34);
    layout->addWidget(lab_img_);
    QLabel* lab_name_ = new QLabel(friendInfo.name, this);
    lab_name_->setStyleSheet(QStringLiteral("font:12px 微软雅黑;color:#333333;"));
    layout->addWidget(lab_name_);

    list_buttons.addButton(this);
    this->setStyleSheet("QPushButton#MemberItem{border:none;background:transparent;}QPushButton#MemberItem:hover{border:none;background:#e8e7e7;}QPushButton#MemberItem:checked{border:none;background:#d5d4d4;}");
    lab_sel_ = new QLabel(this);
    lab_sel_->setFixedSize(20, 20);
    layout->addWidget(lab_sel_);
    isSelected_ = selected;
    lab_sel_->setPixmap(selected ? QPixmap(":/Resources/Images/WinMain/rad_pressed.png") : QPixmap(":/Resources/Images/WinMain/rad.png"));
    lab_img_->setPixmap(QPixmap(":/Resources/Images/WinMain/Av_person.png").scaled(lab_img_->size()));
}

MemberItemWidget::~MemberItemWidget()
{
    list_buttons.removeButton(this);
    disconnect();
}

void MemberItemWidget::setSelected(bool b)
{
    isSelected_ = b;
    lab_sel_->setPixmap(b ? QPixmap(":/Resources/Images/WinMain/rad_pressed.png") : QPixmap(":/Resources/Images/WinMain/rad.png"));
    if (isSelected_)
    {
        select_friends.append(friendInfo_);
    }
    else
    {
        for (int i = 0; i < select_friends.size(); i++)
        {
            if (select_friends[i].userId == friendInfo_.userId)
            {
                select_friends.removeAt(i);
                break;
            }
        }
    }
    dlg->updateSelectItems();
}


void MemberItemWidget::slot_download_finished(QString md5, QString path, QString custom)
{
    if (md5_avator_ == md5 && custom == this->metaObject()->className())
    {

    }
}

#pragma endregion
#pragma region SelectMemberItemWidget
SelectMemberItemWidget::SelectMemberItemWidget(FriendInfo friendInfo, QWidget* parent /*= nullptr*/) :QWidget(parent)
{
    friendInfo_ = friendInfo;
    this->setObjectName("SelectMemberItemWidget");
    this->setFixedHeight(60);
    QHBoxLayout* layout = new QHBoxLayout;
    layout->setContentsMargins(12, 0, 12, 0);
    layout->setSpacing(12);
    this->setLayout(layout);
    lab_img_ = new QLabel(this);
    lab_img_->setFixedSize(34, 34);
    layout->addWidget(lab_img_);
    QLabel* lab_name_ = new QLabel(friendInfo.name, this);
    lab_name_->setStyleSheet(QStringLiteral("font:12px 微软雅黑;color:#333333;"));
    layout->addWidget(lab_name_);


    this->setStyleSheet("QPushButton#SelectMemberItemWidget{border:none;background:transparent;}");
    QPushButton* btn_remove = new QPushButton(this);
    connect(btn_remove, &QPushButton::clicked, this, &SelectMemberItemWidget::slot_button);
    btn_remove->setFixedSize(20, 20);
    btn_remove->setStyleSheet("border:none;image:url(:/Resources/Images/WinMain/close.png)");
    layout->addWidget(btn_remove);
    lab_img_->setPixmap(QPixmap(":/Resources/Images/WinMain/Av_person.png").scaled(lab_img_->size()));
}

SelectMemberItemWidget::~SelectMemberItemWidget()
{
    // disconnect();
}


void SelectMemberItemWidget::slot_download_finished(QString md5, QString path, QString custom)
{
    if (md5_avator_ == md5 && custom == this->metaObject()->className())
    {

    }
}

void SelectMemberItemWidget::slot_button()
{
    if (left_items.keys().contains(friendInfo_.userId))
    {
        QListWidgetItem* item = left_items[friendInfo_.userId];
        MemberItemWidget* widget = dynamic_cast<MemberItemWidget*>(item->listWidget()->itemWidget(item));
        if (widget)
        {
            widget->setSelected(false);
        }
    }
    else
    {
        for (int i = 0; i < select_friends.size(); i++)
        {
            if (select_friends[i].userId == friendInfo_.userId)
            {
                select_friends.removeAt(i);
                break;
            }
        }
    }
    dlg->updateSelectItems();
}


#pragma endregion

