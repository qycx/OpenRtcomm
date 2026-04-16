#include    "stdafx.h"
#include <QList>
#include    <QDebug>
#include "SearchListModel.h"

#include    "qyMcMainCommon_qt.h"

#include "ctxQmc_qt.h"
#include <DBManager.h>


int search_fill_contact(QList<SearchInfoData > &m_infoList) {
    {
        SearchInfoData data;
        data.userId = "1";
        data.url = ":/Resources/Images/WinMain/person.png";
        data.name = QStringLiteral("张三");
        m_infoList.append(data);
    }
   
	
	return 0;
}

int search_fill_grp(QList<SearchInfoData> &m_infoList) {
    {
        SearchInfoData data;
        data.userId = "2";
        data.url = ":/Resources/Images/WinMain/person.png";
        data.name = QStringLiteral("测试群");
        m_infoList.append(data);
    }
    return 0;
}

int search_fill_msg(QList<SearchInfoData>& m_infoList , QString str) {
    {
        //
        QY_MESSENGER_ID  infoId;
        TCHAR grpName_from[125];
        TCHAR srcName_from[125];
        unsigned  int  uiObjType = 0;
#if  10
        QY_MC* pQyMc = QY_GET_GBUF();
        CCtxQmc_qt* pProcInfo = (CCtxQmc_qt*)pQyMc->get_pProcInfo();
        DBManager* pDm = (DBManager*)pProcInfo->m_var.pDBManager;
        auto map = pDm->searchMessage(str);
#endif

        for (auto each : map.toStdMap()) {
            infoId.ui64Id = each.first.toInt();

            QList<MessageData>kk = each.second;
            SearchInfoData data;
            data.userId = each.first;
       getTalkerDesc(infoId, &uiObjType, grpName_from, mycountof(grpName_from), mynull, mynull, 0, mynull, 0 , srcName_from, mycountof(srcName_from));
       if (uiObjType == CONST_objType_imGrp) {
           data.url = ":/Resources/Images/WinMain/group.png";
           data.name = QString::fromStdWString(grpName_from) + " (" + each.first +")";
       }
       else {
           data.url = ":/Resources/Images/WinMain/person.png";
           data.name = QString::fromStdWString(srcName_from) + " (" + each.first + ")";
       }
       data.isMsg = true;
       data.msg = QString::number( kk.size() ) + u8"条相关的聊天记录";
     //  data.msgs = kk;
       m_infoList.append(data);

       //
          /* for (int i = 0; i <= kk.size() - 1;i++ ) {
              
           }*/
        };


              
    }
    return 0;
}
