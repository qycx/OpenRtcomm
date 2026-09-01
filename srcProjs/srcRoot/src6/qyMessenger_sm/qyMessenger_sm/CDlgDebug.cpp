#include "CDlgDebug.h"
//
//#include <QDesktopWidget>
#include    <qscreen.h>
//#include    <windows.h>
#include    <WinSock2.h>
#include    <tchar.h>
#include <QStorageInfo>
#include    "qyMcMainCommon_qt.h"
#include    "ctxQmc_sm.h"
#include <QDebug>

#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <functiondiscoverykeys_devpkey.h>

#pragma comment(lib, "ole32.lib")


//
int viewDlgDbg(  HWND  hParent  )
{

    int  iErr = -1;
    CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)QY_GET_procInfo_isCli();

    //
    if (IsWindow(pProcInfo->m_var.hWnd_dbg)) {
        return  0;
    }

    QWidget* pParent = QWidget::find((WId)hParent);
    if (!pParent)  return  -1;


    CDlgDebug* pDlg = new CDlgDebug(pParent);
    if (!pDlg)  goto  errLabel;

    pProcInfo->m_var.hWnd_dbg = (HWND)pDlg->winId();


    pDlg->show();


    iErr = 0;
    errLabel:


    return  iErr ;
}


int  closeDlgDbg()
{
    CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)QY_GET_procInfo_isCli();

    if (IsWindow(pProcInfo->m_var.hWnd_dbg)) {
        CDlgDebug* pDlg = (CDlgDebug*)QWidget::find((WId)pProcInfo->m_var.hWnd_dbg);
        if (pDlg) {
            delete  pDlg;
        }
    }
    pProcInfo->m_var.hWnd_dbg = nullptr;

    return  0;

}




//
CDlgDebug::CDlgDebug(QWidget *parent  , QString m_status)
	: QDialog(parent)
	, ui(new Ui::CDlgDebugClass)
{



	this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

    //
	ui->setupUi(this);
  

    sheetBackgroundImage();

    QScreen* pScreen; pScreen = QApplication::primaryScreen();

    connect(pScreen, &QScreen::geometryChanged, this, &CDlgDebug::refResolution);
    //填充内容
   // initData(parent->objectName());

    m_pParent = parent;

    //
    refreshData();
    
    //
    m_pWinTimer = new QTimer(this);
    connect(m_pWinTimer, SIGNAL(timeout()), this, SLOT(refreshData()));

    m_pWinTimer->setInterval(3000);
    m_pWinTimer->start();
}




void CDlgDebug::refreshData()
{
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)pQyMc->get_pProcInfo();

    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
    
    //
    QRect rc = QApplication::primaryScreen()->geometry();
    
    
   // ui->listWidget->clear();
  
    char localIp[128]{};
    char confMcu[128]{};
    char str1stMcu[128]{};
    char str2ndMcu[128]{};
    getIpInfo(str1stMcu, sizeof(str1stMcu) , str2ndMcu , sizeof(str2ndMcu), confMcu,sizeof(confMcu) , localIp , sizeof(localIp));


    QString commEnc = "";
    QString localIpStr = u8"本地IP地址：" + QString::fromUtf8(localIp);
    QString str1stMcuStr = u8"主MCU地址：" + QString::fromUtf8(str1stMcu);
    QString str2ndMcuStr = u8"辅MCU地址：" + QString::fromUtf8(str2ndMcu);
    QString confMcuStr = u8"当前MCU地址：" + QString::fromUtf8(confMcu);
    QString idInfo = "";
    QString terminalType = "";
 
    if (bCommEnc()) {
        commEnc = u8"通信加密：已加密";
    }
    else {
        commEnc = u8"通信加密：未加密";
    }

    //获取终端类型 

    if (pProcInfo->uiTerminalType != CONST_terminalType_mon)
    {
        terminalType = u8"会议";
    }
    else {
        terminalType = u8"传输";
    }

    idInfo = u8"终端ID：" + QString::number(pMisCnt->idInfo.ui64Id) + u8"  终端类型：" + terminalType;
    
    //getDiskSize();
    QString diskSize = u8"磁盘容量：可用 " + QString::number(pProcInfo->status.iDiskUsage.availableDiskSize) + u8"MB / 总容量 " + QString::number(pProcInfo->status.iDiskUsage.sumDiskSize) + "MB";
  
    //版本号
    bool  bDebug = false;
    int  iVer;
    TCHAR  tBuf[128];
    //
    char verBuf[128];

    _snprintf(verBuf, sizeof(verBuf), "%s", qnmVerStr(pQyMc->iServiceId));
    if (verBuf[0] && verBuf[strlen(verBuf) - 1] == 'd')  bDebug = TRUE;
    iVer = atol(verBuf);
    _sntprintf(tBuf, mycountof(tBuf), _T("Ver: V%d.%02d.%02d.%02d%s"), iVer / 1000000, (iVer / 10000) % 100, (iVer / 100) % 100, iVer % 100, bDebug ? _T("Debug") : _T(""));

    //编解码方式
    int ucHardwareAccl = get_ucHardwareAccl(g_pQyMc);
    TCHAR  tBufP[128];
    //丢包率
    _sntprintf(tBufP, mycountof(tBufP), _T("%.02f%%"), pMisCnt->status.fDiscards * 100.);
    ui->packet->setText(u8"丢包率：" + QString::fromUtf16((char16_t*)tBufP));

    //
    ui->io->setText(u8"下行：" + QString::number(pProcInfo->status.netStat.ins.uiInSpeedInKbps) + u8"，上行：" + QString::number(pProcInfo->status.netStat.ins.uiOutSpeedInKbps) + " kbps");


    ui->isNv->setText(u8"编解码方式：" + QString::number(ucHardwareAccl));

    //已选音频默认输入输出设备
    ui->audioDeviceIn->setText(u8"已选麦克风设备：" + getDefaultCommunicationSpeakerDevice());
    ui->audioDeviceOut->setText(u8"已选喇叭设备：" + getDefaultCommunicationMicrophoneDevice());


    ui->version->setText(QString::fromUtf16((char16_t*)tBuf));
    ui->localIpStr->setText(localIpStr);
    ui->str1stMcu->setText(str1stMcuStr);
    ui->str2ndMcu->setText(str2ndMcuStr);
    ui->confMcu->setText(confMcuStr);
    ui->idInfo->setText(idInfo);
    ui->commEnc->setText(commEnc);
    ui->diskSize->setText(diskSize);


    ui->meeting_lab->setVisible(false);
    ui->meetingId->setVisible(false);
    ui->meetingConvener->setVisible(false);
    ui->meetingType->setVisible(false);
    ui->meetingCompere->setVisible(false);
    ui->meetingDurationInMin->setVisible(false);
    ui->meetingStartTime->setVisible(false);
    ui->fps->setVisible(false);
    ui->meeting_lab2->setVisible(false);
    ui->meeting_item1->setVisible(false);
    ui->meeting_item2->setVisible(false);
    ui->meeting_item3->setVisible(false);



    if (m_pParent->objectName() == "CDlgTalk_qt") {

        ui->meeting_lab->setVisible(true);
        ui->meetingId->setVisible(true);
        ui->meetingConvener->setVisible(true);
        ui->meetingType->setVisible(true);
        ui->meetingCompere->setVisible(true);
        ui->meetingDurationInMin->setVisible(true);
        ui->meetingStartTime->setVisible(true);
        ui->fps->setVisible(true);
        ui->meeting_lab2->setVisible(true);
        ui->meeting_item1->setVisible(true);
        ui->meeting_item2->setVisible(true);
        ui->meeting_item3->setVisible(true);


       CDlgTalk_qt* pWin_cdlgtalk = (CDlgTalk_qt*)m_pParent;
        DLG_TALK_var* pm_var = pWin_cdlgtalk->get_pm_var();
        if (!pm_var)return ;
        //
        QString meetingType = "";
    //   
        DLG_TALK_var* pCurVar = pm_var;
        HWND  hCurTalk = (HWND)pWin_cdlgtalk->winId();

     //
        HWND  hMgr = mynull;
        DLG_TALK_var* pMgrVar = mynull;
        if (isTalkerShadowMgr(pCurVar->addr)) {
            hMgr = hCurTalk;
        }
        else {
            TALKER_shadow* pShadowInfo = (TALKER_shadow*)pCurVar->pShadowInfo;
            hMgr = pShadowInfo->hMgr;
        }
        CHelp_getDlgTalkVar getDlgTalkVar_mgr;
        pMgrVar = (DLG_TALK_var*)getDlgTalkVar_mgr.getVar(hMgr);
       if (pMgrVar == mynull)return;

        if (pMgrVar->av.taskInfo.hgInfo.iMeetingType_hg == 1)
        {
           meetingType = u8"当前会议类型：普通会议";
        }
        else {
            meetingType = u8"当前会议类型：点对点会议";
        }
        
        QString meetingId = u8"当前会议ID:" + QString::number(pm_var->addr.idInfo.ui64Id);

        QString meetingCompere = u8"当前会议主持人：" + QString::fromUtf16((char16_t*)pMgrVar->av.taskInfo.hgInfo.meetingCompere);

        QString str_time = QString::number(pMgrVar->av.taskInfo.hgInfo.ui64_meetingStartTime);
       qint64 int_time = str_time.toULongLong();
        QDateTime dt;
        //
        //dt.setTime_t(int_time / 1000);
        dt.setSecsSinceEpoch(int_time / 1000);
        //
        QString meetingStartTime = u8"当前会议开始时间：" + dt.toString("yyyy-MM-dd hh:mm:ss");

        QString meetingDurationInMin = u8"当前会议时长：" + QString::number(pMgrVar->av.taskInfo.hgInfo.iMeetingDurationInMin) + u8"分钟";

       

        QString fps = u8"分辨率：" + QString::number(pMgrVar->av.taskInfo.confState.iW_conf) + "x" + QString::number(pMgrVar->av.taskInfo.confState.iH_conf) + u8"  帧数:" + QString::number(pMgrVar->av.taskInfo.confState.usMaxFps) + u8"  显示分辨率:" + QString::number(rc.width()) + "x" + QString::number(rc.height());


        ui->meeting_lab->setText(u8"当前会议名称：");
        ui->meetingConvener->setText(u8"当前会议召集人：");
        ui->meetingId->setText(meetingId);
        ui->meetingType->setText(meetingType);
        ui->meetingCompere->setText(meetingCompere);
      
        ui->meetingDurationInMin->setText(meetingDurationInMin);
        ui->meetingStartTime->setText(meetingStartTime);
        ui->fps->setText(fps);
       
        //
        ui->meeting_lab2->setText (u8"其它会议：----------------");
        int index_i = 0;
        //
        if (QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[index_i].meetingName) != "") {

            if (pm_var->addr.idInfo.ui64Id == pProcInfo->m_var.ctxSm.hg.meetingInfos[index_i].meetingId) {
               
                ui->meeting_lab->setText(u8"当前会议名称：" + QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[index_i].meetingName));
                ui->meetingConvener->setText(u8"当前会议召集人：" + QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[index_i].meetingConvener));

                index_i++;
                ui->meeting_item1->setVisible(false);
            }
            else {
                ui->meeting_item1->setText( u8"会议名称：" + QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[index_i].meetingName) + u8"\n会议ID：" + QString::number(pProcInfo->m_var.ctxSm.hg.meetingInfos[index_i].meetingId) + u8"\n召集人：" + QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[index_i].meetingConvener) + u8"\n会议日期：" + QString::fromUtf8(pProcInfo->m_var.ctxSm.hg.meetingInfos[index_i].meetingData) + " " + QString::fromUtf8(pProcInfo->m_var.ctxSm.hg.meetingInfos[index_i].meetingTime) + u8"\n召集部门：" + QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[index_i].meetingDepartment));
                index_i++;
            }
        }
        else {

            ui->meeting_lab2->setVisible(false);
            ui->meeting_item1->setVisible(false);
        }

        if (QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[index_i].meetingName) != "") {
        
           ui->meeting_item2->setText(u8"会议名称：" + QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[index_i].meetingName) + u8"\n会议ID：" + QString::number(pProcInfo->m_var.ctxSm.hg.meetingInfos[index_i].meetingId) + u8"\n召集人：" + QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[index_i].meetingConvener) + u8"\n会议日期：" + QString::fromUtf8(pProcInfo->m_var.ctxSm.hg.meetingInfos[index_i].meetingData) + " " + QString::fromUtf8(pProcInfo->m_var.ctxSm.hg.meetingInfos[index_i].meetingTime) + u8"\n召集部门：" + QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[index_i].meetingDepartment));
            index_i++;
        }
        else {
            ui->meeting_item2->setVisible(false);
        }

        if (QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[index_i].meetingName) != "") {
    
            ui->meeting_item3->setText(u8"会议名称：" + QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[index_i].meetingName) + u8"\n会议ID：" + QString::number(pProcInfo->m_var.ctxSm.hg.meetingInfos[index_i].meetingId) + u8"\n召集人：" + QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[index_i].meetingConvener) + u8"\n会议日期：" + QString::fromUtf8(pProcInfo->m_var.ctxSm.hg.meetingInfos[index_i].meetingData) + " " + QString::fromUtf8(pProcInfo->m_var.ctxSm.hg.meetingInfos[index_i].meetingTime) + u8"\n召集部门：" + QString::fromUtf16((char16_t*)pProcInfo->m_var.ctxSm.hg.meetingInfos[index_i].meetingDepartment));
            index_i++;
        }
        else {
            ui->meeting_item3->setVisible(false);
        }
    }
  
    
    
}

//获取磁盘容量
void CDlgDebug::getDiskSize()
{
    sumSize = 0;
    availableSize = 0;

    QList<QStorageInfo> storageInfoList = QStorageInfo::mountedVolumes();

    foreach(QStorageInfo storage, storageInfoList) {
        
            // qDebug() << "isReadOnly:" << storage.isReadOnly();
        // qDebug() << "fileSystemType:" << storage.fileSystemType();
      //   qDebug() << "size:" << storage.bytesTotal() / 1024 / 1024 << "MB";
        // qDebug() << "availableSize:" << storage.bytesAvailable() / 1024 / 1024 << "MB";
            sumSize += storage.bytesTotal() / 1024 / 1024;
            availableSize += storage.bytesAvailable() / 1024 / 1024;
        
    }
}


void CDlgDebug::sheetBackgroundImage()
{
    QRect rc = QApplication::primaryScreen()->geometry();
    if (rc.width() > 3500) {
        resize(1000, 1400);
      
        ui->widget->setStyleSheet("background:rgba(30, 39, 71, 0.9);color:#fff;font-size:38px");
     
        


    }
    else {
        resize(450, 700);
        ui->widget->setStyleSheet("background:rgba(30, 39, 71, 0.9);color:#fff;font-size:18px");
       
      //  ui->widget->setFixedSize(450, 900);
    }

    move(rc.width() - this->width(), 0);
   // move(400, 0);

}

//刷新分辨率
void CDlgDebug::refResolution()
{

    sheetBackgroundImage();
}



//获取当前在用的音频输入设备名称
QString CDlgDebug::getDefaultCommunicationMicrophoneDevice()
{
    CoInitialize(NULL);

    IMMDeviceEnumerator* pEnumerator = NULL;
    IMMDevice* pDevice = NULL;
    IPropertyStore* pProps = NULL;
    QString deviceName;

    HRESULT hr = CoCreateInstance(
        __uuidof(MMDeviceEnumerator), NULL,
        CLSCTX_ALL, __uuidof(IMMDeviceEnumerator),
        (void**)&pEnumerator
    );

    if (SUCCEEDED(hr)) {
        // 获取默认通信音频输入设备（关键区别：使用eCapture参数）
        hr = pEnumerator->GetDefaultAudioEndpoint(
            eCapture,  // 音频输入（捕获）
            eCommunications,  // 通信类型
            &pDevice
        );

        if (SUCCEEDED(hr)) {
            hr = pDevice->OpenPropertyStore(STGM_READ, &pProps);

            if (SUCCEEDED(hr)) {
                PROPVARIANT varName;
                PropVariantInit(&varName);

                // 获取设备友好名称
                hr = pProps->GetValue(PKEY_Device_FriendlyName, &varName);

                if (SUCCEEDED(hr)) {
                    deviceName = QString::fromWCharArray(varName.pwszVal);
                }

                PropVariantClear(&varName);
                pProps->Release();
            }

            pDevice->Release();
        }

        pEnumerator->Release();
    }

    CoUninitialize();
    return deviceName;
}

//获取当前在用的音频输出设备名称  通信设备 
QString CDlgDebug::getDefaultCommunicationSpeakerDevice()
{
    CoInitialize(NULL);

    IMMDeviceEnumerator* pEnumerator = NULL;
    IMMDevice* pDevice = NULL;
    IPropertyStore* pProps = NULL;
    QString deviceName;

    HRESULT hr = CoCreateInstance(
        __uuidof(MMDeviceEnumerator), NULL,
        CLSCTX_ALL, __uuidof(IMMDeviceEnumerator),
        (void**)&pEnumerator
    );

    if (SUCCEEDED(hr)) {
        // 获取默认通信音频输出设备
        hr = pEnumerator->GetDefaultAudioEndpoint(
            eRender,  // 音频输出
            eCommunications,  // 通信类型
            &pDevice
        );

        if (SUCCEEDED(hr)) {
            hr = pDevice->OpenPropertyStore(STGM_READ, &pProps);

            if (SUCCEEDED(hr)) {
                PROPVARIANT varName;
                PropVariantInit(&varName);

                // 获取设备友好名称
                hr = pProps->GetValue(PKEY_Device_FriendlyName, &varName);

                if (SUCCEEDED(hr)) {
                    deviceName = QString::fromWCharArray(varName.pwszVal);
                }

                PropVariantClear(&varName);
                pProps->Release();
            }

            pDevice->Release();
        }

        pEnumerator->Release();
    }

    CoUninitialize();
    return deviceName;
}



CDlgDebug::~CDlgDebug()
{
    delete ui;
    if (m_pWinTimer)
    {
        delete m_pWinTimer;
        m_pWinTimer = nullptr;
    }
}
