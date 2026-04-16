
#include	<tchar.h>
#include	"qtimer.h"
#include <qscrollbar.h>
#include <QCloseEvent>
#include "CDlg2ndScreen.h"
#include <QLabel>
#include <qdebug.h>
#include <QDateTime>
#include <QIcon>
//
#include	"qyMcMainCommon_qt.h"
#include	"ctxQmc.h"
#include	"dlgVideosProc.h"

//
int viewDlg2ndScreen_qt()
{
    int  iErr = -1;
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

    CDlg2ndScreen* pDlg = mynull;

    if (IsWindow(pProcInfo->dlg2ndScreen.hWnd_2ndScreen)) {
        MACRO_SetForegroundWindow(pProcInfo->dlg2ndScreen.hWnd_2ndScreen);
        iErr = 0;  goto  errLabel;
    }

    pDlg = new CDlg2ndScreen();
    if (!pDlg)goto  errLabel;

    pProcInfo->dlg2ndScreen.hWnd_2ndScreen = (HWND)pDlg->winId();

    pDlg->show();


    iErr = 0;
errLabel:
    return  iErr;
}

int  closeDlg2ndScreen_qt()
{
    int  iErr = -1;
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

    //
    CDlg2ndScreen* pDlg = (CDlg2ndScreen*)CDlg2ndScreen::find((WId)pProcInfo->dlg2ndScreen.hWnd_2ndScreen);
    if (pDlg) {
        //pDlg->close();
        //SendMessage(pProcInfo->dlg2Screen.hWnd_2Screen, WM_CLOSE, 0, 0);
        delete  pDlg;

    }


    //
    iErr = 0;
errLabel:
    return  iErr;

}






//
CDlg2ndScreen::CDlg2ndScreen(QWidget* parent)
    : WinBasic(false, parent)
{
    ui.setupUi(this);

    this->setWindowIcon(QIcon(":/Resources/Images/Login/qmClient.png"));
    m_pWinTitle = new WinTitle(ui.widgetTitle);
    m_pWinTitle->setButtonType(MIN_MAX_BUTTON);
    m_pWinTitle->move(0, 0);
    m_pWinTitle->setParent(true);
    m_pWinTitle->setTitleContent(this->windowTitle(), "#000");
    connect(m_pWinTitle, SIGNAL(signalButtonMinClicked()), this, SLOT(onButtonMinClicked()));
    connect(m_pWinTitle, SIGNAL(signalButtonCloseClicked()), this, SLOT(onButtonCloseClicked()));
    connect(m_pWinTitle, SIGNAL(signalButtonRestoreClicked()), this, SLOT(onButtonRestoreClicked()));
    connect(m_pWinTitle, SIGNAL(signalButtonMaxClicked()), this, SLOT(onButtonMaxClicked()));

    //
    //this->setAttribute(Qt::WA_DeleteOnClose);

    //
    memset(&m_var, 0, sizeof(m_var));

    //
    m_var.iMAX_timeoutInS_dlgVideos = MAX_timeoutInS_dlgVideos_qt;

    //
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

    //
    HWND  hDlg = (HWND)this->winId();

    if (!scrollArea_)
    {
        scrollArea_ = new QScrollArea(ui.peerDesc);
        scrollArea_->verticalScrollBar()->setStyleSheet("width:12px");
        scrollArea_->horizontalScrollBar()->setStyleSheet("height:12px");
        scrollArea_->setMouseTracking(true);
        scrollArea_->setGeometry(0, 0, ui.peerDesc->width(), ui.peerDesc->height());
        scrollArea_->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        scrollArea_->setStyleSheet("border:none; background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30)");
        QLabel* lab_ = new QLabel();
        lab_->setMouseTracking(true);
        lab_->installEventFilter(this);
        //lab_->setStyleSheet("background:red;");
        //lab_->setFixedSize(1920, 1080);
        //lab_->show();
        scrollArea_->setWidget(lab_);
        scrollArea_->show();
        scrollArea_->raise();

        //
        m_var.hCtrl = (HWND)scrollArea_->widget()->winId();
    }

    //ui.peerDesc->installEventFilter(this);

    //
   // m_var.hCtrl = (HWND)ui.peerDesc->winId();

    //
        //
    m_var.pMsgBuf_doWnd_guiMsgArrive = (MIS_MSGU*)mymalloc(sizeof(MIS_MSGU));
    if (!m_var.pMsgBuf_doWnd_guiMsgArrive)  goto  errLabel;


    //  2012/05/05
    int  iSize;
    m_var.usCnt_zoneParams = pProcInfo->av.usCnt_players;
    iSize = m_var.usCnt_zoneParams * sizeof(ZONE_PARAM);
    m_var.pZoneParams = (ZONE_PARAM*)mymalloc(iSize);
    if (!m_var.pZoneParams)  goto  errLabel;
    memset(m_var.pZoneParams, 0, iSize);


    //  if  (  m_var.iIndex_capImage  <  0  &&  m_var.iTaskId  )  SetTimer(  1,  1000,  NULL  );
    if (m_var.nElapseInMs) {
        //SetTimer(1, m_var.nElapseInMs, NULL);
    }
    m_pWinTimer = new QTimer(this);
    connect(m_pWinTimer, SIGNAL(timeout()), this, SLOT(on_timer_winMethod()));
    m_pWinTimer->setInterval(1000);
    m_pWinTimer->start();



    //  2011/03/25
    m_var.guiData.bInited = TRUE;



    //
errLabel:

    //
    return;
}

CDlg2ndScreen::~CDlg2ndScreen()
{
    int  ii = 0;

    //
    return;
}

//双击全屏
void CDlg2ndScreen::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        if (this->isFullScreen())
        {
            ui.widgetTitle->setVisible(true);
            ui.verticalLayout->setContentsMargins(1, 1, 1, 1);
            if (m_pWinTitle)
            {
                m_pWinTitle->showNormal();
            }
            this->showNormal();
        }
        else
        {
            ui.widgetTitle->setVisible(false);
            ui.verticalLayout->setContentsMargins(0, 0, 0, 0);
            showFullScreen();
            this->showFullScreen();
        }
    }
}

//qint64 lastTim = 0;
bool CDlg2ndScreen::nativeEvent(const QByteArray& eventType, void* message, qintptr* result)
{
    Q_UNUSED(eventType);
    MSG* msg = reinterpret_cast<MSG*>(message);

    //
    switch (msg->message)
    {
    case  CONST_qyWm_comm:
    {
        //
#if 10
        HWND  hDlg = (HWND)this->winId();
        DLG_videos_var* pm_var = &m_var;

        int h = 0;
        int w = 0;
        //qint64 now = QDateTime::currentDateTime().toMSecsSinceEpoch();
        //qDebug() << "==========" << now - lastTim;
        //lastTim = now;
        //
        QY_WMBUF_COMM* pComm = (QY_WMBUF_COMM*)msg->lParam;

        if (pComm->uiType == CONST_misMsgType_procVideo_qmc) {
            MIS_MSG_procVideo_qmc* pMsg = (MIS_MSG_procVideo_qmc*)pComm;
            h = pMsg->bih.biHeight;
            w = pMsg->bih.biWidth;

#if 0
            if (ui.peerDesc && h > 0 && w > 0)
            {
                ui.peerDesc->setFixedSize(w, h);
                if (w <= this->width() && h <= this->height())
                {
                    ui.peerDesc->setGeometry((this->width() - w) / 2,
                        (this->height() - h) / 2,
                        w, h);
                }

            }
#endif
            //
#if 10
            if (m_streamInfo.m_iW_scroll != w || m_streamInfo.m_iH_scroll != h) {
                m_streamInfo.m_bExists_stream = true;

                //
                freeCapImages(hDlg, m_var.hCtrl, &m_var.images, mynull, &m_var.hDc);

                //
                bEnableScrollBar(true, w, h);
                m_streamInfo.m_iW_scroll = w;
                m_streamInfo.m_iH_scroll = h;

                //
#if 0
                RECT rc;
                GetClientRect(hDlg, &rc);
                sizeAllControls(rc);
#endif
                QRect qrc;
                qrc = this->geometry();
                int dlgW = qrc.width();
                qrc.setWidth(dlgW - 1);
                setGeometry(qrc);
                qrc.setWidth(dlgW);
                setGeometry(qrc);



            }
#endif

            //
            * result = dlgVideos_OnQyComm(hDlg, pm_var, msg->wParam, msg->lParam);
#endif
        }
        else {
        }
    }
    //						 
    return  true;
    break;
    case  CONST_qyWm_postComm:
    {
        int  ii = 0;
    }
    //
    return  true;
    break;
    case  WM_CLOSE:
        //return  true;
        break;
    default:
        //
        if (msg->message == WM_MOUSEMOVE)
        {
            int  i = 0;
        }
        //
        break;
    }

    return  WinBasic::nativeEvent(eventType, message, result);
}

//界面尺寸变化重绘
void CDlg2ndScreen::resizeEvent(QResizeEvent* event)
{
    HWND  m_hWnd = (HWND)this->winId();
    //
    RECT rc;
    GetClientRect(m_hWnd, &rc);
    sizeAllControls(rc);
    //
#if  10
    if (scrollArea_)
    {
        scrollArea_->setGeometry(0, 0, ui.peerDesc->width(), ui.peerDesc->height());
    }
#endif

    //
    QWidget::resizeEvent(event);
}


//
void CDlg2ndScreen::closeEvent(QCloseEvent* ev)
{
    HWND  m_hWnd = (HWND)this->winId();

    this->hide();
    ev->accept();

    //
    delete  m_pWinTimer;

    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
    HWND  hCtrl = (HWND)scrollArea_->widget()->winId();
    bool b = IsWindow(hCtrl);

    //
    dlgVideos_OnDestroy(m_hWnd, m_var);

    //
    clearScrollBar();
    this->deleteLater();
    //
    //delete  this;

    //
    int ii = 0;
}

bool CDlg2ndScreen::eventFilter(QObject* obj, QEvent* ev)
{
    if (scrollArea_ && obj == scrollArea_->widget())
    {
        if (ev->type() == QEvent::MouseButtonDblClick)
        {
            if (this->isFullScreen())
            {
                ui.widgetTitle->setVisible(true);
                ui.verticalLayout->setContentsMargins(1, 1, 1, 1);
                if (m_pWinTitle)
                {
                    m_pWinTitle->showNormal();
                }
                this->showNormal();
            }
            else
            {
                ui.widgetTitle->setVisible(false);
                ui.verticalLayout->setContentsMargins(0, 0, 0, 0);
                showFullScreen();
                this->showFullScreen();
            }
        }
        return true;
    }
    return QWidget::eventFilter(obj, ev);
}

void CDlg2ndScreen::onButtonMinClicked()
{
    showMinimized();
}

void CDlg2ndScreen::onButtonCloseClicked()
{
    this->close();
}

void CDlg2ndScreen::onButtonRestoreClicked()
{
    this->showNormal();
}

void CDlg2ndScreen::onButtonMaxClicked()
{
    this->showMaximized();
}


//
void CDlg2ndScreen::on_timer_winMethod()
{
    HWND  m_hWnd = (HWND)this->winId();
    dlgVideos_OnTimer(m_hWnd, m_var);
    int n = getCnt_imgs(&m_var.images);
    if (!n) {
        if (m_streamInfo.m_bExists_stream) {
            freeCapImages(m_hWnd, m_var.hCtrl, &m_var.images, mynull, &m_var.hDc);

            //
            memset(&m_streamInfo, 0, sizeof(m_streamInfo));

            //
            bEnableScrollBar(false, 0, 0);

            //
            QRect qrc;
            qrc = this->geometry();
            int dlgW = qrc.width();
            qrc.setWidth(dlgW - 1);
            setGeometry(qrc);
            qrc.setWidth(dlgW);
            setGeometry(qrc);


        }

    }

}


//
int  CDlg2ndScreen::sizeAllControls(RECT  rcParam)
{
    int					iErr = -1;
    int					i;
    //int					idc;
    //QY_DMITEM* pItem;
    HWND hCtrl = mynull;



#if 10
    //
    //for (i = 0; i < pBase->m_var.usCnt_row * pBase->m_var.usCnt_col; i++) 
    {
        //pItem = &pBase->m_var.pIdcTable[i];
        //idc = (int)pItem->des;
        //hCtrl = GetDlgItem(idc);
        //hCtrl = (HWND)ui.peerDesc->winId();
        hCtrl = m_var.hCtrl;
        //if (!pCtrl)  goto  errLabel;
        //pCtrl->Invalidate(TRUE);
        //  pCtrl->UpdateWindow(  );
        RECT  rcCtrl;
        GetClientRect(hCtrl, &rcCtrl);
        int base_iW = rcCtrl.right - rcCtrl.left;
        int base_iH = rcCtrl.bottom - rcCtrl.top;

        //
        QRect qrc;
        qrc.setWidth(base_iW);
        qrc.setHeight(base_iH);
        // ui.peerDesc->setGeometry(qrc);


         //
        if (m_var.ucbLocalAv)  myGetImageInfo_2d(TRUE, m_var.ucbAutoClip, m_var.images.mems[i].iW_org, m_var.images.mems[i].iH_org, 0, 0, base_iW, base_iH, (unsigned  int*)&m_var.images.mems[i].iW_i, (unsigned  int*)&m_var.images.mems[i].iH_i, &m_var.images.mems[i].iX_src_i, &m_var.images.mems[i].iY_src_i, &m_var.images.mems[i].iX_dst, &m_var.images.mems[i].iY_dst, &m_var.images.mems[i].iW_dst, &m_var.images.mems[i].iH_dst);
        else {
            //  
            RECT	rc;
            ::GetClientRect(hCtrl, &rc);
            int	iX, iY, iW, iH;
            iX = rc.left;
            iY = rc.top;
            iW = rc.right - rc.left;
            iH = rc.bottom - rc.top;
            //
            PARAM_getCapImages  param_getCapImages = { 0 };
            //			   		
#if 0
            if (iSubtype == CONST_dlgVideosSubtype_view) {
                param_getCapImages.bNew = TRUE;
            }
#endif
            param_getCapImages.bNew = TRUE;

            //
            getCapImages(m_var.ucbAutoClip, iX, iY, iW, iH, &param_getCapImages, &m_var.images);
            //
            static  int  n_0cnt = 0;
            //
            if (!m_var.images.head.usCnt) {
                n_0cnt++;
                if (n_0cnt < 1000)
                {
                    //PostMessage(WM_SIZE);
                }

            }
            else  n_0cnt = 0;
            //

        }


    }
#endif

    iErr = 0;
errLabel:
    return  iErr;
}

bool CDlg2ndScreen::bEnableScrollBar(bool bEnable, int  iw_scroll, int  ih_scroll)
{
    bool  bRet = false;

    // QWidget* peerDesc = ui.peerDesc;// this->findChild<QWidget*>("peerDesc");

     //
#ifdef  __DEBUG__

#endif

    //
    if (!scrollArea_)
    {
        scrollArea_ = new QScrollArea(ui.peerDesc);
        scrollArea_->verticalScrollBar()->setStyleSheet("width:12px");
        scrollArea_->horizontalScrollBar()->setStyleSheet("height:12px");
        scrollArea_->setMouseTracking(true);
        scrollArea_->setGeometry(0, 0, ui.peerDesc->width(), ui.peerDesc->height());
        scrollArea_->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        scrollArea_->setStyleSheet("background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30)");
        QLabel* lab_ = new QLabel();
        lab_->setMouseTracking(true);
        //lab_->setStyleSheet("background:red;");
        //lab_->setFixedSize(1920, 1080);
        //lab_->show();
        scrollArea_->setWidget(lab_);
        scrollArea_->show();
        scrollArea_->lower();

        //
        m_var.hCtrl = (HWND)scrollArea_->widget()->winId();
    }

    //
    QLabel* pLabel = (QLabel*)scrollArea_->widget();
    if (pLabel == mynull)  goto  errLabel;

    //
    if (!bEnable) {
        //
        //pLabel->setFixedSize(peerDesc->width() - 2, peerDesc->height() - 2);
        pLabel->setFixedSize(0, 0);
        pLabel->show();
        //
        scrollArea_->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollArea_->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    }
    else {
        pLabel->setFixedSize(iw_scroll, ih_scroll);
        pLabel->show();
        //
        if (this->isFullScreen()) {
            scrollArea_->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
            scrollArea_->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        }
        else {
            scrollArea_->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
            scrollArea_->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        }
    }


    //
    bRet = true;
errLabel:
    return  bRet;
}






void CDlg2ndScreen::clearScrollBar()
{
    HWND  hDlgTalk = (HWND)this->winId();

    //if (pm_var->av.taskInfo.bTaskExists) 
    {

        //
        freeCapImages(hDlgTalk, m_var.hCtrl, &m_var.images, mynull, &m_var.hDc);

    }

    //
    //if (scrollArea_)
    //{
    //    delete scrollArea_;
    //    scrollArea_ = nullptr;
    //}
}


