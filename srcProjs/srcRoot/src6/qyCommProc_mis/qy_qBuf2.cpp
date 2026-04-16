


#include	"stdafx.h"

#include	"qyPrecomp.h"

#include	<windows.h>
#include	<assert.h>
#include	<tchar.h>
#ifndef  __WINCE__
#include	<vfw.h>
#else
#ifdef  __TEST__
#include	<vfw.h>
#endif
#include	<mmreg.h>
#include	<MSAcm.h>
#endif
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyCommCommon.h"
#include	"qyWmComm.h"
#include	"qyCommProc.h"
#include	"qmOpenCommon.h"

#include	"qySyncCommProc.h"
#include	"genericQueue.h"
//#include	"qyq2.h"				//  2009/05/13
#include    "qy_qBuf2.h"

//
//
#include	"qnmCommProc.h"
//#include	"qnmCommProc_mis.h"
//#include	"qyWmComm_is.h"
#include    "ctxQmThread.h"
#include    "qy_qBuf2_defs.h"


//
#if 0
public partial class Consts
{
    public const int CONST_qType_decA = 1;
    public const int CONST_qType_playA = 2;
    //
    public const int CONST_qType_showInfo = 10;


};
#endif

//
int myEventSet(HANDLE hEvent)
{
    SetEvent(hEvent);

    return  0;
}


#if 10

	 QY_qBuf::QY_qBuf()
	 {
		 
		      //
		 memset(&cfg,0,sizeof(cfg));
		 name[0]=0;
		 //
		 memHeads=mynull;
		 pBuf=mynull;
		 
		 //
     startIndex_memHead=0;
	 uiQNodes=0;

     //            
     startPos_data=0;
     dataLen=0;

     //
     //
     bNeedSync=false;

	 //
	 mutexName[0]=0;


	 }


    //
    bool QY_qBuf::is_QFull()
    {
        QY_qBuf *pQ = this;
        if (pQ == mynull) return false;
        if (pQ->cfg.uiMaxQNodes != 0 && pQ->uiQNodes >= pQ->cfg.uiMaxQNodes) return true;
        return false;
    }

    bool QY_qBuf::is_QWarning(int uiQNodes_warningInterval)
    {
        QY_qBuf *pQ = this;
        if (pQ == mynull) return false;
        if (pQ->cfg.uiMaxQNodes != 0 && pQ->uiQNodes + uiQNodes_warningInterval >= pQ->cfg.uiMaxQNodes) return true;
        return false;
    }


    //
    bool QY_qBuf::is_QEmpty()
    {
        if (this->uiQNodes == 0) return true;
        return false;

    }

    //
    int QY_qBuf::init(int qType, uint uiMaxQNodes, int maxDataBufLen, bool bAlloc, LPCTSTR name)
    {
        int iErr = -1;

        QY_qBuf* bufInfo = this;
        QY_qBuf *pQ = this;

        if (maxDataBufLen == 0) return -1;
        if (bufInfo->pBuf != mynull) return -1;

        //
        if (name == mynull) name = _T("");
        //pQ->name = name;
        safeTcsnCpy(name, pQ->name, mycountof(pQ->name));
        pQ->cfg.m_qType = qType;

        //
        bufInfo->cfg.uiMaxQNodes = uiMaxQNodes;


        //
        pQ->bNeedSync = true;

        //
#if 0
        pQ->hMutex = new Mutex();
        if (pQ->hMutex == null) goto errLabel;
#endif
        _sntprintf(pQ->mutexName, mycountof(pQ->mutexName), _T("synQBuf%d-%d"), GetCurrentProcessId(), getuiNextTranNo(mynull, 0, mynull));

        //
        if (qType == CONST_qType_showInfo)
        {
            pQ->cfg.b_showInfoQ = true;
        }

        //
        if (bAlloc)
        {
            if (0 != alloc(maxDataBufLen))
            {
                goto errLabel;
            }
        }


        iErr = 0;


    errLabel:
        if (iErr != 0)
        {
            exit();
        }
        return iErr;
    }

    void QY_qBuf::exit()
    {
        QY_qBuf* qBuf = this;
        QY_qBuf* pQ = this;

        //
        dofree();

        //
#if 0//false
        if (pQ.hMutex != null)
        {
            pQ.hMutex.Close();
            pQ.hMutex = null;
        }
#endif


    }

    //
    int QY_qBuf::alloc(int maxDataBufLen)
    {
        int iErr = -1;
        QY_qBuf* pQ = this;
        QY_qBuf* bufInfo = this;

        //
        bufInfo->cfg.maxDataBufLen = maxDataBufLen;

        //        
        {
            CQySyncObj syncObj;// = new CQySyncObj())

            //if (pQ->bNeedSync && syncObj.sync( &pQ->syncObjParam, pQ.hMutex) != 0)
            if (pQ->bNeedSync && syncObj.sync(pQ->mutexName) != 0)
            {
                //qyShowInfo_internal(CONST_qyShowType_warning, 0, "", pQ->cfg.name, NULL, NULL, _T(""), _T("qPostMsg failed: sync failed"));
                goto errLabel;
            }

            //
            if (pQ->pBuf != mynull || pQ->memHeads != mynull)
            {
                goto errLabel;
            }

            //
#if 0
            bufInfo->memHeads = new Tmp_qBuf_memHead[bufInfo->cfg.uiMaxQNodes];

            int i;
            for (i = 0; i < bufInfo->cfg.uiMaxQNodes; i++)
            {
                switch (bufInfo->cfg.m_qType)
                {
                case CONST_qType_decA:
                    bufInfo.memHeads[i] = new Tmp_qBuf_memHead_decA();
                    break;
                case Consts.CONST_qType_showInfo:
                    bufInfo.memHeads[i] = new Tmp_qBuf_memHead_showInfo();
                    break;
                case Consts.CONST_qType_playA:
                    bufInfo.memHeads[i] = new Tmp_qBuf_memHead_playA();
                    break;
                default:
                    goto errLabel;
                }
            }
#endif
            int memHeadSize = 0;
            switch (bufInfo->cfg.m_qType)
            {
            case CONST_qType_decA:
                memHeadSize = sizeof(Tmp_qBuf_memHead_decA);
                break;
            case CONST_qType_showInfo:
                memHeadSize = sizeof(Tmp_qBuf_memHead_showInfo);
                break;
            case CONST_qType_playA:
                memHeadSize = sizeof(Tmp_qBuf_memHead_playA);
                break;
            default:
                goto errLabel;
            }
            int size = memHeadSize * bufInfo->cfg.uiMaxQNodes;
            if (size == 0)goto  errLabel;
            bufInfo->memHeads = mymalloc(size);
            if (bufInfo->memHeads == mynull)goto  errLabel;
            memset(bufInfo->memHeads, 0, size);

            //
            bufInfo->pBuf = (byte*)mymalloc(bufInfo->cfg.maxDataBufLen);
            if (bufInfo->pBuf == mynull) goto errLabel;

        }

        iErr = 0;
    errLabel:
        if (0 != iErr)
        {
            dofree();
        }
        return iErr;
    }

    void QY_qBuf::dofree()
    {
        QY_qBuf* pQ = this;
        QY_qBuf* qBuf = this;

        //using (CQySyncObj syncObj = new CQySyncObj())
        {
            CQySyncObj syncObj;

            //if (pQ.bNeedSync && syncObj.sync(ref pQ.syncObjParam, pQ.hMutex) != 0)
            if (pQ->bNeedSync && syncObj.sync(pQ->mutexName) != 0)
            {
                //qyShowInfo_internal(CONST_qyShowType_warning, 0, "", pQ->cfg.name, NULL, NULL, _T(""), _T("qPostMsg failed: sync failed"));
                goto errLabel;
            }

            //
            //qBuf->memHeads = null;
            if (qBuf->memHeads != mynull) {
                myfree(qBuf->memHeads);  qBuf->memHeads = mynull;
            }
            if (qBuf->pBuf != mynull)
            {
                myfree(qBuf->pBuf);
                qBuf->pBuf = mynull;
            }


        }

    errLabel:

        return;
    }

    //
    int QY_qBuf::qPostMsg(void * pHeadData, void * pQElem0, uint size)
    {
        int iErr = -1;
        QY_qBuf* pQ = this;
        TCHAR str[128];

        //
        if (pHeadData == mynull) return -1;
        if (pQElem0 == mynull) return -1;
        if (size == 0) return -1;

        //
        //using (CQySyncObj syncObj = new CQySyncObj())
        {
            CQySyncObj syncObj;

            //if (pQ.bNeedSync && syncObj.sync(ref pQ.syncObjParam, pQ.hMutex) != 0)
            if (pQ->bNeedSync && syncObj.sync( pQ->mutexName) != 0)
            {
                //qyShowInfo_internal(CONST_qyShowType_warning, 0, "", pQ->cfg.name, NULL, NULL, _T(""), _T("qPostMsg failed: sync failed"));
                goto errLabel;
            }

            //
            if (pQ->pBuf == mynull)
            {
                if (!pQ->cfg.b_showInfoQ)
                {
                    showInfo_open0(0, _T(""), _T("qbuf.qPostMsg failed, pBuf is null"));

                }
                goto errLabel;
            }

            //
            if (pQ->uiQNodes >= pQ->cfg.uiMaxQNodes)
            {
                //str = string.Format(pQ.name + " qFull");
                _sntprintf(str, mycountof(str), _T("%s qFull"), pQ->name);
                if (pQ->cfg.b_showInfoQ)
                {
                    traceLog(str);
                }
                else
                {
                    showInfo_open0(0, _T(  ""  ), str);
                }
                //
                iErr = CONST_qyRet_qFull;  goto errLabel;
            }

            //
            if (pQ->dataLen + size > pQ->cfg.maxDataBufLen)
            {
                _sntprintf(  str,mycountof(str),  _T(  "%s qFull"  ),pQ->name);
                if (pQ->cfg.b_showInfoQ)
                {
                    traceLog(str);
                }
                else
                {
                    showInfo_open0(0, _T(""), str);
                }
                //
                goto errLabel;
            }

            //
            switch (pQ->cfg.m_qType)
            {
            case CONST_qType_showInfo:
            {
                Tmp_qBuf_memHead_showInfo* pQ_memHeads = (Tmp_qBuf_memHead_showInfo*)pQ->memHeads;
                Tmp_qBuf_memHead_showInfo *head = &pQ_memHeads[pQ->uiQNodes];
                //
                head->headData.len_showInfo = (int)size;
                //

            }
            break;
            case CONST_qType_decA:
            {
                Tmp_qBuf_memHead_decA* pQ_memHeads = (Tmp_qBuf_memHead_decA*)pQ->memHeads;
                Tmp_qBuf_memHead_decA *head = &pQ_memHeads[pQ->uiQNodes];
                //
                head->dataMemHead = *(TRANSFER_AUDIO_dataMemHead*)pHeadData;

            }
            break;
            case CONST_qType_playA:
            {
                Tmp_qBuf_memHead_playA* pQ_memHeads = (Tmp_qBuf_memHead_playA*)pQ->memHeads;
                Tmp_qBuf_memHead_playA* head = &pQ_memHeads[pQ->uiQNodes];
                //
                head->headData = *(HeadData_playA*)pHeadData;

            }
            break;
            default:
                traceLog((TCHAR*)_T("qPostMsg failed: unprocessed qType"));
                goto errLabel;
            }
            pQ->uiQNodes++;
            //
            if (pQElem0 != mynull)
            {
                memcpy((pQ->pBuf + pQ->dataLen), pQElem0, size);
            }
            //
            pQ->dataLen += (int)size;

        }

        iErr = 0;
    errLabel:

        return iErr;
    }

    //
    int QY_qBuf::tmp_qGetMsg(void * pHeadData, void * pQElem, uint *puiSize, bool bNotShowInfo)
    {
        int iErr = -1;
        QY_qBuf* pQ = this;

        if (pQ->uiQNodes == 0) return -1;
        if (pQ->uiQNodes + pQ->startIndex_memHead > pQ->cfg.uiMaxQNodes)
        {
            traceLog((TCHAR*)_T("qBuf.tmp_qGetMsg failed, err"));
            return -1;
        }

        int dataLen = 0;
        switch (pQ->cfg.m_qType)
        {
        case CONST_qType_showInfo:
        {
            Tmp_qBuf_memHead_showInfo* pQ_memHeads = (Tmp_qBuf_memHead_showInfo*)pQ->memHeads;

            Tmp_qBuf_memHead_showInfo *head = &pQ_memHeads[pQ->startIndex_memHead];
            dataLen = head->headData.len_showInfo;
        }
        break;
        case CONST_qType_decA:
        {
            Tmp_qBuf_memHead_decA* pQ_memHeads = (Tmp_qBuf_memHead_decA*)pQ->memHeads;
            
            Tmp_qBuf_memHead_decA * head = &pQ_memHeads[pQ->startIndex_memHead];
            dataLen = (int)head->dataMemHead.uiLen;
            *(TRANSFER_AUDIO_dataMemHead*)pHeadData = head->dataMemHead;
        }
        break;
        case CONST_qType_playA:
        {
            Tmp_qBuf_memHead_playA* pQ_memHeads = (Tmp_qBuf_memHead_playA*)pQ->memHeads;
            Tmp_qBuf_memHead_playA *head = &pQ_memHeads[pQ->startIndex_memHead];
            dataLen = (int)head->headData.uiSize_dec;
            *(HeadData_playA*)pHeadData = head->headData;
        }
        break;
        default:
            traceLog((TCHAR*)_T("tmp_qGetMsg failed: unprocessed qType"));
            goto errLabel;
        }
        if (dataLen > *puiSize) goto errLabel;
        if (dataLen + pQ->startPos_data > pQ->cfg.maxDataBufLen)
        {
            goto errLabel;
        }
        memcpy(pQElem, pQ->pBuf + pQ->startPos_data, (uint)dataLen);
        *puiSize = (uint)dataLen;
        pQ->startIndex_memHead++;
        pQ->startPos_data += dataLen;
        pQ->dataLen -= dataLen;
        pQ->uiQNodes--;

        //
        if (pQ->uiQNodes == 0)
        {
            if (pQ->dataLen != 0)
            {
                int ii = 0;
            }
            //
            pQ->startIndex_memHead = 0;
            pQ->startPos_data = 0;
        }


        //
        iErr = 0;
    errLabel:

        return iErr;

    }

    int QY_qBuf::qGetMsg(void * pHeadData, void  * pQElem, uint* puiSize)
    {
        QY_qBuf* pQ = this;

        if (pQ == mynull) return -1;
        if (mynull == pQElem || mynull == puiSize) return -1;

        //using (CQySyncObj syncObj = new CQySyncObj())
        {
            CQySyncObj syncObj;

            //if (pQ.bNeedSync && syncObj.sync(ref pQ.syncObjParam, pQ.hMutex) != 0) return -1;
            if (pQ->bNeedSync && syncObj.sync(pQ->mutexName) != 0) return -1;

            if (pQ->pBuf == mynull)
            {
                if (!pQ->cfg.b_showInfoQ)
                {
                    showInfo_open0(0, _T(""), _T("qBuf.getMsg failed, pBuf is null"));
                }
                //
                return -1;
            }

            return tmp_qGetMsg(pHeadData, pQElem,  puiSize, false);
        }
    }



#endif

//

//
class CQy_qBuf2Help : CQyRWLock
{

    struct {
        QY_qBuf2* pQ2;
        //
        QY_qBuf* pQ_toGetMsg;
        QY_qBuf* pQ_toPostMsg;
    }       m_var;

    //
    CQySyncObj		syncObj_syncR;


    //
public:
    CQy_qBuf2Help()
    {
        //m_pQ2 = null;
        memset(&m_var, 0, sizeof(m_var));
    }

    //
    ~CQy_qBuf2Help()
    { }

    QY_qBuf *getQ_toPostMsg(QY_qBuf2* pQ2)
    {
        if (mynull == pQ2) return mynull;
        if (m_var.pQ2 != mynull)
        {
            if (m_var.pQ2 != pQ2) return mynull;
        }
        else
            m_var.pQ2 = pQ2;

        if (m_var.pQ_toPostMsg != mynull) return m_var.pQ_toPostMsg;

        if (this->rLock(pQ2->pRw_syncFlg, (int)pQ2->cfg.rwLockParam_syncFlg.uiMilliSeconds_sema_r) != 0) return mynull;

        m_var.pQ_toPostMsg = pQ2->bFlag_toPostMsg_q1 ? &pQ2->qs1 : &pQ2->qs0;
        m_var.pQ_toGetMsg = pQ2->bFlag_toPostMsg_q1 ? &pQ2->qs0 : &pQ2->qs1;

        return m_var.pQ_toPostMsg;
    }


    QY_qBuf* getQ_toGetMsg(QY_qBuf2 *pQ2,  LPCTSTR  hint)
    {
        //
        if (hint == NULL)  hint = _T("");

        //
        if (mynull == pQ2)
        {
            return mynull;
        }

        if (m_var.pQ2 != mynull)
        {
            if (m_var.pQ2 != pQ2)
            {
                return mynull;
            }
        }
        else
            m_var.pQ2 = pQ2;

        if (m_var.pQ_toGetMsg != mynull) return m_var.pQ_toGetMsg;

        //
#if 10
//
        TCHAR  tBuf[128];
        //
#ifdef  __DEBUG__
    //
#if 0
        _sntprintf(tBuf, mycountof(tBuf), _T("qyq2Help.getQ_toGetMsg failed, %s, %s"), pQ2->mutexName_syncR, hint);
#endif
        //
#endif

    //
        if (this->syncObj_syncR.sync(pQ2->mutexName_syncR, 0)) {
            //
            _sntprintf(tBuf, mycountof(tBuf), _T("qyqBuf2Help.getQ_toGetMsg failed, %s, %s"), pQ2->mutexName_syncR, hint);
            if (pQ2->cfg.m_qType == CONST_qType_showInfo) {
                traceLog(tBuf);
            }
            else {
                tmp_showInfo_open_internal(0, _T(""), tBuf);
            }
            //
            return  NULL;
        }
#endif


        //
        QY_qBuf* pQ_toGetMsg;
        QY_qBuf* pQ_toPostMsg;
        if (pQ2->bFlag_toPostMsg_q1)
        {
            pQ_toGetMsg = &pQ2->qs0;
            pQ_toPostMsg = &pQ2->qs1;
        }
        else
        {
            pQ_toGetMsg = &pQ2->qs1;
            pQ_toPostMsg = &pQ2->qs0;
        }

        if ((pQ_toGetMsg->is_QEmpty()))
        {
            if (!(pQ_toPostMsg->is_QEmpty()))
            {
                //  try to switch outputQ
                if (this->wLock(pQ2->pRw_syncFlg, (int)pQ2->cfg.rwLockParam_syncFlg.uiMilliSeconds_sema_w) != 0)
                {
                    return mynull;
                }
                pQ2->bFlag_toPostMsg_q1 = !pQ2->bFlag_toPostMsg_q1;
                this->unlock();
            }
        }

        /*
    #if  0
        if  (  this->rLock(  pQ2->mutexName_syncFlg,  pQ2->cfg.rwLockParam_syncFlg.uiMilliSeconds_mutex_r,  pQ2->hSema_syncFlg,  pQ2->cfg.rwLockParam_syncFlg.uiMilliSeconds_sema_r  )  )  return  NULL;
    #else
        if  (  this->rLock(  pQ2->pRw_syncFlg,  pQ2->cfg.rwLockParam_syncFlg.uiMilliSeconds_sema_r  )  )  return  NULL;
    #endif
        */

        /*
        m_var.pQ_toPostMsg  =  pQ2->bFlag_toPostMsg_q1  ?  &pQ2->qs[1]  :  &pQ2->qs[0];
        m_var.pQ_toGetMsg  =  pQ2->bFlag_toPostMsg_q1  ?  &pQ2->qs[0]  :  &pQ2->qs[1];
        */
        if (pQ2->bFlag_toPostMsg_q1)
        {
            m_var.pQ_toGetMsg = &pQ2->qs0;
            m_var.pQ_toPostMsg = &pQ2->qs1;
        }
        else
        {
            m_var.pQ_toGetMsg = &pQ2->qs1;
            m_var.pQ_toPostMsg = &pQ2->qs0;
        }

        return m_var.pQ_toGetMsg;

    }


    int qPostMsgAndTrigger(void* pHeadData, void* pQElem, uint size, QY_qBuf2 *pQ2)
    {

        int tmpiRet = 0;
        bool ucbTriggerErr = false;

        if (pQ2 == mynull) return -1;

        if (pQElem != mynull && size != 0)
        {
            QY_qBuf* q_toPostMsg = getQ_toPostMsg(pQ2);
            if (q_toPostMsg != mynull)
            {
                tmpiRet = q_toPostMsg->qPostMsg(pHeadData, pQElem, size);
                if (tmpiRet != 0)
                {
                    //traceLogA("qyQ2Help::qPostMsgAndTrigger: qPostMsg returns %d", tmpiRet);
                }
            }
        }

        try
        {
#if 0//false
            //if (pQ2->hSemaTrigger1 && !ReleaseSemaphore(pQ2->hSemaTrigger1, 1, &pQ2->lPrevCnt_semaTrigger))
            if (pQ2.hSemaTrigger1 != null)
            {
                qyFuncs.mySemaRelease(pQ2.hSemaTrigger1, 1);

                //qyDisplayLastError("ReleaseSemaphore failed");

                //ucbTriggerErr = true;

                //  traceLogA(  "%S qPostMsgAndTrigger err: uiQNodes %d, lPrevCnt_semaTrigger %d",  pQ2->cfg.name,  pQ->uiQNodes,  pQ2->lPrevCnt_semaTrigger  );
            }
            else
            {
            }
#endif
            if (pQ2->hEvent0 != mynull)
            {
                //SetEvent(pQ2->hEvents[0]);
                myEventSet(pQ2->hEvent0);
            }
        }
        catch (...)
        {
            //Console.WriteLine(e.ToString());
        }

        //  2008/11/21
#if 0//false
        if (ucbTriggerErr != pQ2.ucbTriggerErr)
        {
            pQ2.ucbTriggerErr = ucbTriggerErr;
        }
#endif

    errLabel:

        return tmpiRet;

    }

};





	 QY_qBuf2::QY_qBuf2()
	 {
		 bFlag_toPostMsg_q1=false;
		 //
		 pRw_syncFlg=mynull;
		 //
		 hEvent0=mynull;
	 }



        //
        int QY_qBuf2::initQyQ2(int qType,uint uiMaxQNodes,int maxDataBufLen, RW_lock_param pRwLockParam_syncFlg,bool bAlloc, LPCTSTR name)
        {
            int iErr = -1;

            QY_qBuf2* pQ2 = this;
            //CQyString str;
            TCHAR  tBuf[128];

            //
            if (0 == uiMaxQNodes) return -1;

            //
            this->cfg.m_qType = qType;
            this->cfg.uiMaxQNodes = uiMaxQNodes;
            this->cfg.rwLockParam_syncFlg = pRwLockParam_syncFlg;

            if (name == mynull) name = _T("");
            //this.name = name;
            safeTcsnCpy(name, this->name, mycountof(this->name));
            //
            try {
                this->pRw_syncFlg = new CMutexRW();
                if (mynull == this->pRw_syncFlg) goto errLabel;

                //
                //qs0 = new QY_qBuf();
                //qs1 = new QY_qBuf();
            }
            catch (...) {
                goto  errLabel;
            }

            //
            _sntprintf(pQ2->mutexName_syncR, mycountof(pQ2->mutexName_syncR), _T("qBuf2_syncR%d-%d"), GetCurrentProcessId(), getuiNextTranNo(NULL, 0, NULL));



            _sntprintf(tBuf, mycountof(tBuf), _T("%s0"), name);
            if (qs0.init(qType, uiMaxQNodes, maxDataBufLen,bAlloc,tBuf) != 0) goto errLabel;
            _sntprintf(tBuf, mycountof(tBuf), _T("%s1"), name);
            if (qs1.init(qType, uiMaxQNodes, maxDataBufLen,bAlloc,tBuf) != 0) goto errLabel;

            //
            //pQ2->hEvent0 = new EventWaitHandle(false, EventResetMode.AutoReset);
            pQ2->hEvent0 = CreateEvent(mynull, false, false, mynull);
            if (pQ2->hEvent0 == mynull) goto errLabel;



            //
            iErr = 0;

        
        errLabel:
            if ( iErr != 0)
            {
                exitQyQ2();
            }
            return iErr;
        }

         void QY_qBuf2::exitQyQ2()
        {
            QY_qBuf2 *pQ2 = this;

            //if (qs0 != null)
            {
                qs0.exit();
                //qs0 = null;
            }
            //if (qs1 != null)
            {
                qs1.exit();
                //qs1 = null;
            }

            if (pQ2->hEvent0 != mynull)
            {
                //CloseHandle(pQ2->hEvents[j]); pQ2->hEvents[j] = NULL;
                CloseHandle(pQ2->hEvent0); pQ2->hEvent0 = mynull;

            }


            if (this->pRw_syncFlg != mynull)
            {
                //this->pRw_syncFlg->Close();
                delete this->pRw_syncFlg;
                this->pRw_syncFlg = mynull;
            }

            return;
        }

        //
         int QY_qBuf2::alloc(int maxDataBufLen)
        {
            int iErr = -1;

            if (0 != this->qs0.alloc(maxDataBufLen)) goto errLabel;
            if (0 != this->qs1.alloc(maxDataBufLen)) goto errLabel;

            iErr = 0;
        errLabel:
            if (0 != iErr)
            {
                dofree();
            }
            return iErr;
        }

        void QY_qBuf2::dofree()
        {
            this->qs0.dofree();
            this->qs1.dofree();
        }

        //
        bool QY_qBuf2::is_Q2Warning( int uiQNodes_warningInterval)
        {
            QY_qBuf2 *pQ2 = this;

            if (mynull == pQ2) return false;
            if (pQ2->bFlag_toPostMsg_q1) return pQ2->qs1.is_QWarning( uiQNodes_warningInterval);
            else return pQ2->qs0.is_QWarning( uiQNodes_warningInterval);
        }

        bool QY_qBuf2::is_Q2Empty()
        {
            QY_qBuf2 *pQ2 = this;

            if (mynull == pQ2) return false;
            return (pQ2->qs0.is_QEmpty() && pQ2->qs1.is_QEmpty());
        }

        //
        int QY_qBuf2::q2PostMsg(void * pHeadData, void * pQElem, uint size,  LPCTSTR  hint)
        {
            int iErr = -1;

            QY_qBuf2 *pQ2 = this;

            //
            pQ2->dwTickCnt_lastData = myGetTickCount(mynull);


            //
            //using (CQyQ2Help q2Help = new CQyQ2Help())
            {
                CQy_qBuf2Help q2Help;

                if (q2Help.getQ_toPostMsg(pQ2) == mynull)
                {
                    traceLogA((char*)"q2PostMsg failed, getQ_toPostMsg returns null");
                    return -1;
                }


                return q2Help.getQ_toPostMsg(pQ2)->qPostMsg(pHeadData, pQElem, size);
            }
        }


        //


        //
         int QY_qBuf2::q2PostMsgAndTrigger(void * pHeadData, void * pQElem, uint size,  LPCTSTR  hint)
        {
            QY_qBuf2 *pQ2 = this;
            //
            pQ2->dwTickCnt_lastData = myGetTickCount(mynull);

            //
            //using (CQyQ2Help q2Help = new CQyQ2Help())
            {
                CQy_qBuf2Help q2Help;

                return q2Help.qPostMsgAndTrigger(pHeadData,pQElem, size, pQ2);
            }
        }

        //
        int QY_qBuf2::q2GetMsg( void * pHeadData,void * pQElem, uint* puiSize,  LPCTSTR  hint)
        {
            QY_qBuf2* pQ2 = this;

            //using (CQyQ2Help q2Help = new CQyQ2Help())
            {
                CQy_qBuf2Help q2Help;

                if (q2Help.getQ_toGetMsg(pQ2,hint) == mynull) return -1;

                return q2Help.getQ_toGetMsg(pQ2,hint)->qGetMsg( pHeadData, pQElem, puiSize);
            }
        }


        //
        int QY_qBuf2::get_Q2Nodes()
        {
            QY_qBuf2 *pQ2 = this;

            if (mynull == (pQ2)) return -1;
            //if (null == pQ2.qs0 || null == pQ2.qs1) return -1;
            return (int)((pQ2)->qs0.uiQNodes + (pQ2)->qs1.uiQNodes);
        }



        //
 


    



