
#include    "QGuiApplication.h"
#include    "QScreen.h"

#include "ShareStreamWidget.h"
#include "ctxQmc_sm.h"
#include "dlgVideosProc.h"
#include "qdebug.h"

ShareStreamWidget::ShareStreamWidget(QWidget* parent)
    : QWidget(parent)
{
    this->setWindowFlag(Qt::Dialog);
    memset(&m_var, 0, sizeof(m_var));
    setWindowFlag(Qt::FramelessWindowHint);
    m_peer = new QFrame(this);
    m_peer->setStyleSheet("background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30)");
    
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();
    pProcInfo->dlg2ndScreen.hWnd_2ndScreen = (HWND)this->winId();
    //
    m_var.iMAX_timeoutInS_dlgVideos = MAX_timeoutInS_dlgVideos_qt;
    m_var.hCtrl = (HWND)m_peer->winId();
    m_var.pMsgBuf_doWnd_guiMsgArrive = (MIS_MSGU*)mymalloc(sizeof(MIS_MSGU));

    int  iSize;
    m_var.usCnt_zoneParams = pProcInfo->av.usCnt_players;
    iSize = m_var.usCnt_zoneParams * sizeof(ZONE_PARAM);
    m_var.pZoneParams = (ZONE_PARAM*)mymalloc(iSize);
    memset(m_var.pZoneParams, 0, iSize);
    m_var.guiData.bInited = TRUE;

    m_pWinTimer = new QTimer(this);
    connect(m_pWinTimer, SIGNAL(timeout()), this, SLOT(on_timer_winMethod()));
    m_pWinTimer->setInterval(1000);
    m_pWinTimer->start();
}

ShareStreamWidget::~ShareStreamWidget()
{
    int ii = 0;
}


void ShareStreamWidget::on_timer_winMethod()
{
    m_loopCtrl++;

    HWND  m_hWnd = (HWND)this->winId();
    dlgVideos_OnTimer(m_hWnd, m_var);


    do {

        //
        if (!(m_loopCtrl % 5)) {
            CCtxQyMc* pQyMc = g_pQyMc;
            QWidget* pWnd = QWidget::find((WId)pQyMc->gui.hMainWnd);
            if (!pWnd)  break;
            QRect  mainRc = pWnd->geometry();
            int main_cntx = mainRc.x() + mainRc.width() / 2;
            int  main_cnty = mainRc.y() + mainRc.height() / 2;

            //
            QList<QScreen*> screen_list = QGuiApplication::screens();
            for (int i = 0; i < screen_list.count(); i++)
            {
                //if (QGuiApplication::primaryScreen() != screen_list.at(i))
                {
                    QRect qr_screen = screen_list.at(i)->geometry();
                    //
                    if (qr_screen.contains(main_cntx, main_cnty)) {
                        //  避开主窗口的那个屏
                        continue;
                    }
                    //
                    QRect  qr = this->geometry();
                    if (qr != qr_screen) {
                        this->setGeometry(qr_screen);
                        //
                        showInfo_open0(0, 0, _T("ShareStreamWidget: geometry changed"));
                    }
                }
            }

            //


            //shareStreamWidget
        }

    } while (false);

    return;
}



bool ShareStreamWidget::nativeEvent(const QByteArray& eventType, void* message, qintptr* result)
{
    Q_UNUSED(eventType);
    MSG* msg = reinterpret_cast<MSG*>(message);
    //
    CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

    //
    switch (msg->message)
    {
    case  CONST_qyWm_comm:
    {
        //
#if 10
        HWND  hDlg = (HWND)this->winId();
        DLG_videos_var* pm_var = &m_var;
        int h = pm_var->images.mems->iH_org;
        int w= pm_var->images.mems->iW_org;
        int desx = pm_var->images.mems->iX_dst;
        int desy= pm_var->images.mems->iY_dst;
        //
#if 0
        QY_WMBUF_COMM* pWmBuf = (QY_WMBUF_COMM*)msg->lParam;
        if (msg->wParam == CONST_qyWmParam_getObjAddr) {
            pWmBuf->u.getObjAddr.pObjAddr = this;
            *result = CONST_qyWmRc_ok;
            return  true;
        }
#endif
        //
        if (m_peer && h>0 && w >0)
        {

           // QSize sz(pm_var->images.mems->iW_i + pm_var->images.mems->iX_dst * 2, 
              //  pm_var->images.mems->iH_i + pm_var->images.mems->iY_dst * 2);
            QSize sz(w, h);
           
            m_peer->setGeometry( (sz.width()>this->width())? 0 :(this->width()-sz.width())/2,
                         (sz.height() > this->height()) ? 0 : (this->height() - sz.height()) / 2,
                          sz.width(), sz.height());
            
        }
        //
        do {
            if (pProcInfo->av.hk.portStatus.bDisable_hdmi2Out_dvi) {
                break;
            }
         
            //
            *result = dlgVideos_OnQyComm(hDlg, pm_var, msg->wParam, msg->lParam);
            
            //
        } while (false);
#endif
    }
    //						 
    return  true;
    break;
    default:
        break;
    }

    return  QWidget::nativeEvent(eventType, message, result);
}

void ShareStreamWidget::resizeEvent(QResizeEvent* event)
{
    if (m_peer)
    {
        qDebug() << width() << "=mmmm =========" << height();
        m_peer->setGeometry(0, 0, width(), height());
    }
}

