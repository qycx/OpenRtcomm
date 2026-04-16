#include "DeviceSelectDialog.h"
#include <QDebug>
#include    <qbuttongroup.h>
#include    "stdafx.h"
#include "qyMcMainCommon_qt.h"
#include <qyAvRecordPublic.h>


#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <QString>

#include <mmdeviceapi.h>
#include "PolicyConfig.h"
#include "Propidl.h"
#include "Functiondiscoverykeys_devpkey.h"
#include <string>
using namespace std;
#pragma comment(lib, "Winmm.lib")

#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "uuid.lib")

#ifdef UNICODE
#define tcout wcout
#else
#define tcout cout
#endif

//


//
namespace {
    DeviceSelectDialog* dlg = nullptr;
}




HRESULT SetDefaultAudioPlaybackDevice(LPCWSTR devID)
{
    IPolicyConfigVista* pPolicyConfig;
    ERole reserved = eConsole;

    HRESULT hr = CoCreateInstance(__uuidof(CPolicyConfigVistaClient),
        NULL, CLSCTX_ALL, __uuidof(IPolicyConfigVista), (LPVOID*)&pPolicyConfig);
    if (SUCCEEDED(hr))
    {
        hr = pPolicyConfig->SetDefaultEndpoint(devID, reserved);
        pPolicyConfig->Release();
    }
    return hr;
}
//切换默认音频输出设备
void InitDefaultAudioDevice(const QString& audioName)
{
    // 将QString转换为std::wstring用于后续匹配
    std::wstring targetAudioName = audioName.toStdWString();

    HRESULT hr = CoInitialize(NULL);
    if (SUCCEEDED(hr))
    {
        IMMDeviceEnumerator* pEnum = NULL;
        // Create a multimedia device enumerator.
        hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL,
            CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pEnum);
        if (SUCCEEDED(hr))
        {
            // 判断是否是默认的音频设备,是就退出
            bool bExit = false;
            IMMDevice* pDefDevice = NULL;
            hr = pEnum->GetDefaultAudioEndpoint(eRender, eMultimedia, &pDefDevice);
            if (SUCCEEDED(hr))
            {
                IPropertyStore* pStore;
                hr = pDefDevice->OpenPropertyStore(STGM_READ, &pStore);
                if (SUCCEEDED(hr))
                {
                    PROPVARIANT friendlyName;
                    PropVariantInit(&friendlyName);
                    hr = pStore->GetValue(PKEY_Device_FriendlyName, &friendlyName);
                    if (SUCCEEDED(hr))
                    {
                        std::wstring strTmp(friendlyName.pwszVal);
                        if (strTmp.find(targetAudioName) != std::wstring::npos)
                        {
                            bExit = true;
                        }
                        PropVariantClear(&friendlyName);
                    }
                    pStore->Release();
                }
                pDefDevice->Release();
            }
            if (bExit)
            {
                pEnum->Release();
                return;
            }

            IMMDeviceCollection* pDevices;
            // Enumerate the output devices.
            hr = pEnum->EnumAudioEndpoints(eRender, DEVICE_STATE_ACTIVE, &pDevices);
            if (SUCCEEDED(hr))
            {
                UINT count;
                pDevices->GetCount(&count);
                if (SUCCEEDED(hr))
                {
                    for (UINT i = 0; i < count; i++)
                    {
                        bool bFind = false;
                        IMMDevice* pDevice;
                        hr = pDevices->Item(i, &pDevice);
                        if (SUCCEEDED(hr))
                        {
                            LPWSTR wstrID = NULL;
                            hr = pDevice->GetId(&wstrID);
                            if (SUCCEEDED(hr))
                            {
                                IPropertyStore* pStore;
                                hr = pDevice->OpenPropertyStore(STGM_READ, &pStore);
                                if (SUCCEEDED(hr))
                                {
                                    PROPVARIANT friendlyName;
                                    PropVariantInit(&friendlyName);
                                    hr = pStore->GetValue(PKEY_Device_FriendlyName, &friendlyName);
                                    if (SUCCEEDED(hr))
                                    {
                                        // if no options, print the device
                                        // otherwise, find the selected device and set it to be default
                                        std::wstring strTmp(friendlyName.pwszVal);
                                        if (strTmp.find(targetAudioName) != std::wstring::npos)
                                        {
                                            SetDefaultAudioPlaybackDevice(wstrID);
                                            bFind = true;
                                        }
                                        PropVariantClear(&friendlyName);
                                    }
                                    pStore->Release();
                                }
                                CoTaskMemFree(wstrID);
                            }
                            pDevice->Release();
                        }

                        if (bFind)
                        {
                            break;
                        }
                    }
                }
                pDevices->Release();
            }
            pEnum->Release();
        }
    }
    CoUninitialize();
}


// 获取所有音频输出设备列表（名称和ID）
QList<QPair<QString, QString>> getAudioOutputDevices(bool* defaultDeviceFound = nullptr) {
    QList<QPair<QString, QString>> devices;
    bool defaultFound = false;
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr)) {
        if (defaultDeviceFound) *defaultDeviceFound = defaultFound;
        return devices;
    }

    IMMDeviceEnumerator* enumerator = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL,
        CLSCTX_INPROC_SERVER,
        __uuidof(IMMDeviceEnumerator),
        (void**)&enumerator);
    if (FAILED(hr) || !enumerator) {
        CoUninitialize();
        if (defaultDeviceFound) *defaultDeviceFound = defaultFound;
        return devices;
    }

    // 获取默认设备
    IMMDevice* defaultDevice = NULL;
    hr = enumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &defaultDevice);
    QString defaultDeviceId;
    if (SUCCEEDED(hr) && defaultDevice) {
        LPWSTR id = NULL;
        hr = defaultDevice->GetId(&id);
        if (SUCCEEDED(hr) && id) {
            defaultDeviceId = QString::fromUtf16(reinterpret_cast<const ushort*>(id));
            CoTaskMemFree(id);
            defaultFound = true;
        }
        defaultDevice->Release();
    }

    // 获取所有设备
    IMMDeviceCollection* collection = NULL;
    hr = enumerator->EnumAudioEndpoints(eRender, DEVICE_STATE_ACTIVE, &collection);
    if (FAILED(hr) || !collection) {
        enumerator->Release();
        CoUninitialize();
        if (defaultDeviceFound) *defaultDeviceFound = defaultFound;
        return devices;
    }

    UINT count = 0;
    collection->GetCount(&count);

    for (UINT i = 0; i < count; i++) {
        IMMDevice* device = NULL;
        hr = collection->Item(i, &device);
        if (FAILED(hr) || !device) continue;

        LPWSTR deviceId = NULL;
        hr = device->GetId(&deviceId);
        if (FAILED(hr) || !deviceId) {
            device->Release();
            continue;
        }

        IPropertyStore* props = NULL;
        hr = device->OpenPropertyStore(STGM_READ, &props);
        if (SUCCEEDED(hr) && props) {
            PROPVARIANT varName;
            PropVariantInit(&varName);
            hr = props->GetValue(PKEY_Device_FriendlyName, &varName);
            if (SUCCEEDED(hr) && varName.vt == VT_LPWSTR) {
                QString name = QString::fromUtf16(reinterpret_cast<const ushort*>(varName.pwszVal));
                QString id = QString::fromUtf16(reinterpret_cast<const ushort*>(deviceId));

                // 如果是默认设备，添加标记
                if (id == defaultDeviceId) {
                    name += u8"[已选]";
                }

                devices.append(qMakePair(name, id));
            }
            PropVariantClear(&varName);
            props->Release();
        }

        CoTaskMemFree(deviceId);
        device->Release();
    }

    collection->Release();
    enumerator->Release();
    CoUninitialize();

    if (defaultDeviceFound) *defaultDeviceFound = defaultFound;
    return devices;
}



DeviceSelectDialog::DeviceSelectDialog(QWidget* parent)
    : WinBaseDialog(parent)
{
    ui.setupUi(this);
    this->setWindowFlags(this->windowFlags()| Qt::Dialog);
    this->setAttribute(Qt::WA_DeleteOnClose);


    QString qstr;

    //
    memset(&m_var, 0, sizeof(m_var));
    list_devices_v(&m_var.vd);  
    list_devices_a(true, &m_var.ad);

    TCHAR  v_sel[256];
    TCHAR a_sel[256];

    v_sel[0] = 0;
    a_sel[0] = 0;
    
    getChosenDevice(a_sel, mycountof(a_sel), v_sel, mycountof(v_sel), mynull, 0, mynull, mynull);


    //
    this->m_btnGroup_v = new QButtonGroup;
    this->m_btnGroup_a = new QButtonGroup;
    //
    this->m_btnGroup_a_out = new QButtonGroup;


    //
    for (int i = 0; i < m_var.vd.iNumVDevices; i++)
    {
        QRadioButton* radio = new QRadioButton(this);
        qstr = QString::number(i)+": "+QString::fromUtf16((char16_t*)m_var.vd.mems[i].names_video);
        radio->setText(qstr);
        //
        if (!_tcsicmp(v_sel, m_var.vd.mems[i].monikerDisplayName)) {
            radio->setChecked(true);
            //
            m_var.v_index_sel = i;
        }
        //
        connect(radio, &QRadioButton::toggled, this, &DeviceSelectDialog::onVideoToggled);
        dev_videos_ << radio;
        ui.verticalLayout_5->addWidget(radio);

        //
        m_btnGroup_v->addButton(radio);
    }

    //
#if  10
    QRadioButton* radio = new QRadioButton(this);
    qstr = QString::number(0) + ":" + u8"选择默认麦克风";
    radio->setText(qstr);
    radio->setChecked(true);
    connect(radio, &QRadioButton::toggled, this, &DeviceSelectDialog::onAudioToggled);
    dev_audios_ << radio;
    ui.verticalLayout_6->addWidget(radio);
    //
    m_btnGroup_a->addButton(radio);
    
    //
    for (int i = 0; i < m_var.ad.iNumADevices; i++)
    {
        QRadioButton* radio = new QRadioButton(this);
        qstr = QString::number(i  +  1)+":"+QString::fromUtf16((char16_t*)m_var.ad.mems[i].names_audio);
        radio->setText(qstr);
        radio->setEnabled(false);
        connect(radio, &QRadioButton::toggled, this, &DeviceSelectDialog::onAudioToggled);
        dev_audios_ << radio;
        ui.verticalLayout_6->addWidget(radio);
        //
        m_btnGroup_a->addButton(radio);
    }
#endif



    qDebug() << u8"可用音频输出设备:";
    out_device = getAudioOutputDevices();
    for (int i = 0; i < out_device.size(); i++) {
        /* qDebug() << QString(u8"[%1] 名称: %2, ID: %3")
             .arg(i)
             .arg(devices[i].first)
             .arg(devices[i].second);*/

             //
        QRadioButton* radio = new QRadioButton(this);
        radio->setText(out_device[i].first);
        //
        if (out_device[i].first.contains("[")) {
            radio->setChecked(true);
        }
        //
        connect(radio, &QRadioButton::toggled, this, &DeviceSelectDialog::onOutAudioToggled);
        dev_videos_ << radio;
        ui.verticalLayout_7->addWidget(radio);

        //
        m_btnGroup_a_out->addButton(radio);
    }

}

DeviceSelectDialog::~DeviceSelectDialog()
{
    //
    if (this->m_btnGroup_a)  delete this->m_btnGroup_a;
    if (this->m_btnGroup_v)delete this->m_btnGroup_v;

    //
    dlg = nullptr;


}

void DeviceSelectDialog::showDialog(QWidget* parent)
{
    if (!dlg)
    {
        dlg = new DeviceSelectDialog(parent);

    }
    dlg->show();
    dlg->activateWindow();
}

void DeviceSelectDialog::closeDialog() {
    if (dlg) {
        dlg->close();
    }
}

void DeviceSelectDialog::closeEvent(QCloseEvent* ev)
{
    this->hide();
    ev->accept();
}

void DeviceSelectDialog::onVideoToggled(bool b)
{
    int  iErr = -1;

    if (!b)
    {
        return;
    }
    //TODO:选中了一个视频设备
    QRadioButton* button = (QRadioButton*)sender();
    QString str = button->text();
    TCHAR tBuf[256];
    safeTcsnCpy((TCHAR*)str.utf16(), tBuf, mycountof(tBuf));
    TCHAR* pT;
    pT = _tcschr(tBuf, _T(':'));
    if (!pT) goto  errLabel;
    *pT = 0;
    int index; index = _ttol(tBuf);

    //
    m_var.v_index_sel = index;

    iErr = 0;
    //
errLabel:
    return;

}

void DeviceSelectDialog::onAudioToggled(bool b)
{
    int  iErr = -1;

    if (!b)
    {
        return;
    }
    //TODO:选中了一个音频设备
    QRadioButton* button = (QRadioButton*)sender();
    QString str = button->text();
    TCHAR tBuf[256];
    safeTcsnCpy((TCHAR*)str.utf16(), tBuf, mycountof(tBuf));
    TCHAR* pT;
    pT = _tcschr(tBuf, _T(':'));
    if (!pT) goto  errLabel;
    *pT = 0;
    int index; index = _ttol(tBuf);

    //


    //
    iErr = 0;
errLabel:
    return;

}



void DeviceSelectDialog::onOutAudioToggled(bool b)
{
    int  iErr = -1;

    if (!b)
    {
        return;
    }
    //TODO:选中了一个视频输出设备
    QRadioButton* button = (QRadioButton*)sender();
    QString str = button->text();

    //调用切换
    InitDefaultAudioDevice(str);




    iErr = 0;
    //
errLabel:
    return;

}



int  selectDefaultADevice()
{
    	//  2014/7/31
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();


    
        //
        QY_REG  reg;
        memset(&reg, 0, sizeof(reg));

        reg.hKeyRoot0 = HKEY_CURRENT_USER;
        lstrcpyn(reg.rootKey, (pQyMc->cfg.pSysCfg->rootKey_qnmScheduler), mycountof(reg.rootKey));

        qyDelRegCfgT(reg.hKeyRoot0, reg.rootKey, _T(CONST_regValName_ucbNot_selectDefaultRecorder));
        pProcInfo->cfg.policy.audio.ucbNot_selectDefaultRecorder = FALSE;

        //
        return  0;

    
}



//
void DeviceSelectDialog::on_btnAccept_clicked() {
    //点击确认
    qDebug() << "111";

    CCtxQyMc* pQyMc = g_pQyMc;
    QY_REG			reg;
    memset(&reg, 0, sizeof(reg));
    reg.hKeyRoot0 = HKEY_CURRENT_USER;
    lstrcpyn(reg.rootKey, CQyString(pQyMc->cfg.pSysCfg->rootKey_qnmScheduler), mycountof(reg.rootKey));

    if (m_var.v_index_sel >= m_var.vd.iNumVDevices)  return;
    qySetRegCfgT(reg.hKeyRoot0, reg.rootKey, _T(CONST_regValName_webcam_selected), m_var.vd.mems[m_var.v_index_sel].monikerDisplayName);

    //
    selectDefaultADevice();

}

