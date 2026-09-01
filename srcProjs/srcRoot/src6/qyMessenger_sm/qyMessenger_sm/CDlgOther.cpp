#include "CDlgOther.h"
//
//#include <QDesktopWidget>
#include    <qscreen.h>
//
#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <QString>
#include <QDebug>
#include    <qbuttongroup.h>
#include <mmdeviceapi.h>
#include "PolicyConfig.h"
#include "Propidl.h"
#include "Functiondiscoverykeys_devpkey.h"
#include <QRegularExpression>
#include <endpointvolume.h>
#include <string>

#include <atlbase.h>
#include <vector>
using namespace std;
#pragma comment(lib, "Winmm.lib")

#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "uuid.lib")

const QString DEFAULT_CHECKED = u8"[已选]";

#ifdef UNICODE
#define tcout wcout
#else
#define tcout cout
#endif


HRESULT SetDefaultAudioPlaybackDevice(LPCWSTR devID)
{
    IPolicyConfigVista* pPolicyConfig;
    // ERole reserved = eConsole; 默认设备
    ERole reserved = eCommunications; //默认通信设备

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
            // hr = pEnum->GetDefaultAudioEndpoint(eRender, eMultimedia, &pDefDevice); //默认设备
            hr = pEnum->GetDefaultAudioEndpoint(eRender, eCommunications, &pDefDevice);  //默认通信设备
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

bool SetDefaultMicrophone(const QString& deviceId) {
    HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(hr)) {
        // qDebug() << "Failed to initialize COM library:" << _com_error(hr).ErrorMessage();
        return false;
    }

    // 使用IPolicyConfig接口 (Windows Vista+)
    const CLSID CLSID_PolicyConfigClient = __uuidof(CPolicyConfigClient);
    const IID IID_IPolicyConfig = __uuidof(IPolicyConfig);

    IPolicyConfig* pPolicyConfig = nullptr;
    hr = CoCreateInstance(CLSID_PolicyConfigClient, nullptr, CLSCTX_ALL,
        IID_IPolicyConfig, (LPVOID*)&pPolicyConfig);

    bool result = false;
    if (SUCCEEDED(hr) && pPolicyConfig) {
        // 将QString转换为LPWSTR（Qt 5.12及以下版本）
        const wchar_t* wstrDeviceId = reinterpret_cast<const wchar_t*>(deviceId.utf16());

        // hr = pPolicyConfig->SetDefaultEndpoint(wstrDeviceId, eConsole);  //默认设备
        hr = pPolicyConfig->SetDefaultEndpoint(wstrDeviceId, eCommunications);  //默认通信设备
        result = SUCCEEDED(hr);

        if (!result) {
            //  qDebug() << "Failed to set default endpoint:" << _com_error(hr).ErrorMessage();
        }

        pPolicyConfig->Release();
    }
    else {
        //qDebug() << "Failed to create IPolicyConfig instance:" << _com_error(hr).ErrorMessage();
    }

    CoUninitialize();
    return result;
}

//切换默认音频输入设备
bool SetDefaultMicrophoneByName(const QString& deviceName) {
    // 初始化COM库
    HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(hr)) {
        //  qDebug() << "Failed to initialize COM library:" << _com_error(hr).ErrorMessage();
        return false;
    }

    // 创建设备枚举器
    IMMDeviceEnumerator* pEnumerator = nullptr;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr,
        CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator),
        (LPVOID*)&pEnumerator);

    if (FAILED(hr) || !pEnumerator) {
        //qDebug() << "Failed to create device enumerator:" << _com_error(hr).ErrorMessage();
        CoUninitialize();
        return false;
    }

    // 获取所有音频输入设备
    IMMDeviceCollection* pDevices = nullptr;
    hr = pEnumerator->EnumAudioEndpoints(eCapture, DEVICE_STATE_ACTIVE, &pDevices);

    if (FAILED(hr) || !pDevices) {
        //qDebug() << "Failed to enumerate audio devices:" << _com_error(hr).ErrorMessage();
        pEnumerator->Release();
        CoUninitialize();
        return false;
    }

    // 查找匹配名称的设备ID
    QString targetDeviceId;
    UINT count = 0;
    hr = pDevices->GetCount(&count);

    for (UINT i = 0; i < count; i++) {
        IMMDevice* pDevice = nullptr;
        hr = pDevices->Item(i, &pDevice);

        if (FAILED(hr) || !pDevice) continue;

        // 获取设备ID
        LPWSTR deviceId = nullptr;
        hr = pDevice->GetId(&deviceId);

        // 获取设备友好名称
        IPropertyStore* pProps = nullptr;
        hr = pDevice->OpenPropertyStore(STGM_READ, &pProps);

        if (SUCCEEDED(hr) && pProps) {
            PROPVARIANT varName;
            PropVariantInit(&varName);

            // 获取设备友好名称
            hr = pProps->GetValue(PKEY_Device_FriendlyName, &varName);

            if (SUCCEEDED(hr) && varName.vt == VT_LPWSTR) {
                QString currentName = QString::fromWCharArray(varName.pwszVal);

                // 比较设备名称（不区分大小写）
                if (currentName.compare(deviceName, Qt::CaseInsensitive) == 0) {
                    targetDeviceId = QString::fromWCharArray(deviceId);
                    break;
                }
            }

            PropVariantClear(&varName);
            pProps->Release();
        }

        if (deviceId) CoTaskMemFree(deviceId);
        pDevice->Release();
    }

    pDevices->Release();
    pEnumerator->Release();

    // 如果找到匹配的设备，则设置为默认
    if (!targetDeviceId.isEmpty()) {
        // 使用之前的SetDefaultMicrophone函数设置默认设备
        return SetDefaultMicrophone(targetDeviceId);
    }
    else {
        qDebug() << "Device not found with name:" << deviceName;
        CoUninitialize();
        return false;
    }
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

    // 获取默认设备（普通播放）
    IMMDevice* defaultPlaybackDevice = NULL;
    hr = enumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &defaultPlaybackDevice);
    QString defaultPlaybackDeviceId;
    if (SUCCEEDED(hr) && defaultPlaybackDevice) {
        LPWSTR id = NULL;
        hr = defaultPlaybackDevice->GetId(&id);
        if (SUCCEEDED(hr) && id) {
            defaultPlaybackDeviceId = QString::fromUtf16(reinterpret_cast<const ushort*>(id));
            CoTaskMemFree(id);
        }
        defaultPlaybackDevice->Release();
    }

    // 获取默认通信设备
    IMMDevice* defaultCommDevice = NULL;
    hr = enumerator->GetDefaultAudioEndpoint(eRender, eCommunications, &defaultCommDevice);
    QString defaultCommDeviceId;
    if (SUCCEEDED(hr) && defaultCommDevice) {
        LPWSTR id = NULL;
        hr = defaultCommDevice->GetId(&id);
        if (SUCCEEDED(hr) && id) {
            defaultCommDeviceId = QString::fromUtf16(reinterpret_cast<const ushort*>(id));
            CoTaskMemFree(id);
        }
        defaultCommDevice->Release();
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

    // 标记是否找到默认通信设备
    bool hasCommDevice = !defaultCommDeviceId.isEmpty();

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

                // 检查是否为默认通信设备或默认设备
                bool isSelected = false;
                if (!defaultCommDeviceId.isEmpty() && id == defaultCommDeviceId) {
                    isSelected = true;
                }
                else if (defaultCommDeviceId.isEmpty() && !defaultPlaybackDeviceId.isEmpty() && id == defaultPlaybackDeviceId) {
                    isSelected = true;
                }

                // 如果是选中的设备，添加标记
                if (isSelected) {
                    name += DEFAULT_CHECKED;
                    defaultFound = true;
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

//获取所有音频输入设备列表
QList<MicrophoneDevice> getWindowsMicrophoneDevices()
{
    QList<MicrophoneDevice> result;

    HRESULT hr = CoInitialize(nullptr);
    if (FAILED(hr)) return result;

    // 创建设备枚举器
    IMMDeviceEnumerator* pEnumerator = nullptr;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr,
        CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator),
        (LPVOID*)&pEnumerator);

    if (FAILED(hr) || !pEnumerator) {
        CoUninitialize();
        return result;
    }

    // 获取默认设备（普通播放）
    IMMDevice* pDefaultDevice = nullptr;
    hr = pEnumerator->GetDefaultAudioEndpoint(eCapture, eConsole, &pDefaultDevice);
    LPWSTR defaultDeviceId = nullptr;
    if (SUCCEEDED(hr) && pDefaultDevice) {
        pDefaultDevice->GetId(&defaultDeviceId);
        pDefaultDevice->Release();
    }

    // 获取默认通信设备
    IMMDevice* pDefaultCommDevice = nullptr;
    hr = pEnumerator->GetDefaultAudioEndpoint(eCapture, eCommunications, &pDefaultCommDevice);
    LPWSTR defaultCommDeviceId = nullptr;
    if (SUCCEEDED(hr) && pDefaultCommDevice) {
        pDefaultCommDevice->GetId(&defaultCommDeviceId);
        pDefaultCommDevice->Release();
    }

    // 枚举所有音频输入设备
    IMMDeviceCollection* pDevices = nullptr;
    hr = pEnumerator->EnumAudioEndpoints(eCapture, DEVICE_STATE_ACTIVE, &pDevices);

    if (FAILED(hr) || !pDevices) {
        pEnumerator->Release();
        CoUninitialize();
        return result;
    }

    UINT count = 0;
    hr = pDevices->GetCount(&count);

    // 标记是否找到默认通信设备
    bool hasDefaultComm = false;

    for (UINT i = 0; i < count; i++) {
        IMMDevice* pDevice = nullptr;
        hr = pDevices->Item(i, &pDevice);
        if (FAILED(hr) || !pDevice) continue;

        // 获取设备ID
        LPWSTR deviceId = nullptr;
        hr = pDevice->GetId(&deviceId);
        if (FAILED(hr)) {
            pDevice->Release();
            continue;
        }

        // 获取设备友好名称
        IPropertyStore* pProps = nullptr;
        hr = pDevice->OpenPropertyStore(STGM_READ, &pProps);

        if (SUCCEEDED(hr) && pProps) {
            PROPVARIANT varName;
            PropVariantInit(&varName);

            hr = pProps->GetValue(PKEY_Device_FriendlyName, &varName);
            if (SUCCEEDED(hr) && varName.vt == VT_LPWSTR) {
                MicrophoneDevice mic;
                mic.name = QString::fromWCharArray(varName.pwszVal);
                mic.id = QString::fromWCharArray(deviceId);

                // 判断是否为默认设备
                mic.isDefault = (defaultDeviceId != nullptr &&
                    wcscmp(deviceId, defaultDeviceId) == 0);

                // 判断是否为默认通信设备
                mic.isDefaultComm = (defaultCommDeviceId != nullptr &&
                    wcscmp(deviceId, defaultCommDeviceId) == 0);

                // 根据规则设置是否选中
                if (mic.isDefaultComm) {
                    mic.isSelected = true;
                    hasDefaultComm = true;

                    mic.name = QString::fromWCharArray(varName.pwszVal) + DEFAULT_CHECKED;
                }
                else {
                    mic.isSelected = false;

                    mic.name = QString::fromWCharArray(varName.pwszVal);
                }

                result.append(mic);
            }

            PropVariantClear(&varName);
            pProps->Release();
        }

        if (deviceId) CoTaskMemFree(deviceId);
        pDevice->Release();
    }

    // 如果没有找到默认通信设备，则选择默认设备
    if (!hasDefaultComm && defaultDeviceId != nullptr) {
        for (auto& device : result) {
            if (device.isDefault) {
                device.isSelected = true;
                break;
            }
        }
    }

    // 清理资源
    if (defaultDeviceId) CoTaskMemFree(defaultDeviceId);
    if (defaultCommDeviceId) CoTaskMemFree(defaultCommDeviceId);
    pDevices->Release();
    pEnumerator->Release();
    CoUninitialize();

    return result;
}


CDlgOther::CDlgOther(QWidget* parent)
    : QDialog(parent),
    ui(new Ui::CDlgOtherClass)

{
    ui->setupUi(this);

    //
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);



    //
    connect(this, SIGNAL(to_returnMain_signal()), parent, SLOT(on_closeOther_slots()));

    //样式加载
    sheetBackgroundImage();


    //音频播放设备列表加载
    audioOutDeviceList();

    //麦克风设备列表加载
    audioInDeviceList();

}

//样式加载
void CDlgOther::sheetBackgroundImage()
{
    QRect rc = QApplication::primaryScreen()->geometry();

    ui->widget->setStyleSheet("#widget{background-color:qradialgradient(cx:0.5,cy:0.7,radius:0.5,fx:0.5,fy:1.0,stop:0 #0F2E75, stop:0.99 #0C1D30)}");

    if (rc.width() > 3500) {
        resize(1000, 1100);
        ui->label_t1->setStyleSheet("font-size:80px;font-weight:bold;color:#fff;font-family: Microsoft YaHei;");
        ui->widget_4->setStyleSheet("border-bottom:4px solid  #fff;font-size:50px;color:#fff;font-family: Microsoft YaHei;");
        ui->widget_6->setStyleSheet("border-bottom:4px solid  #fff;font-size:50px;color:#fff;font-family: Microsoft YaHei;");
        ui->widget_8->setStyleSheet("border-bottom:4px solid  #fff;font-size:50px;color:#fff;font-family: Microsoft YaHei;");

        ui->widget_2->setStyleSheet("font-size:38px;");
        ui->widget_audioOut->setStyleSheet("font-size:38px;");


        // 设置按钮样式
        ui->restNvrBtn->setStyleSheet(
            "QPushButton { border: 2px solid #555;border-radius: 5px;background-color: #333;color: white;font-size: 40px;padding: 5px;}"
            "QPushButton:checked { background-color: #0F2E75; border-color: #0F2E75; }"
            "QPushButton:hover { background-color: #444; }"
            "QPushButton:pressed { background-color: #0F2E75; }"
            "QPushButton:focus { border: 4px solid #0088FF; }");

        ui->otherBtnRet->setStyleSheet("QPushButton{font-size:70px;color:#fff;background:#5C8CFC;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");

        ui->restNvrBtn->setMinimumHeight(80);
        ui->otherBtnRet->setFixedHeight(140);
        ui->otherBtnRet->setFixedWidth(400);
    }
    else {
        ui->label_t1->setStyleSheet("font-size:30px;font-weight:bold;color:#fff;font-family: Microsoft YaHei;");
        ui->widget_4->setStyleSheet("border-bottom:2px solid  #fff;font-size:25px;color:#fff;font-family: Microsoft YaHei;");
        ui->widget_6->setStyleSheet("border-bottom:2px solid  #fff;font-size:25px;color:#fff;font-family: Microsoft YaHei;");
        ui->widget_8->setStyleSheet("border-bottom:2px solid  #fff;font-size:25px;color:#fff;font-family: Microsoft YaHei;");

        ui->widget_2->setStyleSheet("font-size:20px;");
        ui->widget_audioOut->setStyleSheet("font-size:20px;");
        // 设置按钮样式
        ui->restNvrBtn->setStyleSheet(
            "QPushButton { border: 2px solid #555;border-radius: 5px;background-color: #333;color: white;font-size: 18px;padding: 5px;}"
            "QPushButton:checked { background-color: #0F2E75; border-color: #0F2E75; }"
            "QPushButton:hover { background-color: #444; }"
            "QPushButton:pressed { background-color: #0F2E75; }"
            "QPushButton:focus { border: 2px solid #0088FF; }");

        ui->otherBtnRet->setStyleSheet("QPushButton{font-size:35px;color:#fff;background:#5C8CFC;font-weight:bold;font-family: Microsoft YaHei;border-radius:10px}QPushButton:focus {font-family: Microsoft YaHei;background:#1C56F1;color:#fff}");

        ui->restNvrBtn->setMinimumHeight(40);
        ui->otherBtnRet->setFixedHeight(80);
        ui->otherBtnRet->setFixedWidth(230);
    }

}

//音频输出设备列表
void CDlgOther::audioOutDeviceList()
{
    // 清空原有控件
    clearLayout(ui->verticalLayout_3);
    m_audioButtons.clear();
    m_outAudioselectedIndex = -1;

    // 创建一个QWidget作为容器
    QWidget* buttonContainer = new QWidget(this);
    QVBoxLayout* containerLayout = new QVBoxLayout(buttonContainer);
    containerLayout->setContentsMargins(0, 0, 0, 0);

    // 当前选中的按钮索引
   //int outAudioselectedIndex = -1;

    QList<QPair<QString, QString>> audioOutputDevices;
    out_device = getAudioOutputDevices();
    for (int i = 0; i < out_device.size(); i++) {

        audioOutputDevices.append(qMakePair(out_device[i].first, "outAudioDeviceBtn" + i));
    }

    // 创建按钮并添加到布局
    for (int i = 0; i < audioOutputDevices.size(); i++) {
        const auto& device = audioOutputDevices[i];

        // 创建按钮
        QPushButton* btn = new QPushButton(device.first, buttonContainer);
        btn->setCheckable(true);
        btn->setMinimumHeight(40);
        btn->setFocusPolicy(Qt::TabFocus);
        btn->setObjectName("outAudioDeviceBtn" + QString::number(i));
        btn->setProperty("outAudioDeviceIndex", i); // 存储按钮对应的设备索引

        // 设置按钮样式
        btn->setStyleSheet(
            "QPushButton {"
            "    border: 2px solid #555;"
            "    border-radius: 5px;"
            "    background-color: #333;"
            "    color: white;"
            "    padding: 5px;"
            "}"
            "QPushButton:checked {"
            "    background-color: #0F2E75;"
            "    border-color: #0F2E75;"
            "}"
            "QPushButton:hover {"
            "    background-color: #444;"
            "}"
            "QPushButton:pressed {"
            "    background-color: #0F2E75;"
            "}"
            "QPushButton:focus {"
            "border: 2px solid #0088FF;" /* 更明显的焦点边框 */
            "}");

        // 如果设备名称包含"["，则默认选中
        if (device.first.contains("[")) {
            btn->setChecked(true);
            m_outAudioselectedIndex = i;
        }

        // 连接按钮点击事件到统一的槽函数
        connect(btn, &QPushButton::clicked, this, &CDlgOther::onAudioOutputSelected);

        // 添加按钮到容器布局和按钮列表
        containerLayout->addWidget(btn);
        m_audioButtons.append(btn);
    }

    // 将容器添加到主布局
    ui->verticalLayout_3->addWidget(buttonContainer);

}

//音频输入设备列表
void CDlgOther::audioInDeviceList() {




    // 清空原有控件
    clearLayout(ui->verticalLayout_5);
    m_inAudioButtons.clear();
    m_inAudioselectedIndex = -1;

    // 创建一个QWidget作为容器
    QWidget* buttonContainer = new QWidget(this);
    QVBoxLayout* containerLayout = new QVBoxLayout(buttonContainer);
    containerLayout->setContentsMargins(0, 0, 0, 0);

    // 当前选中的按钮索引
   //int outAudioselectedIndex = -1;

    //QList<MicrophoneDevice> audioInputDevices;
    in_device = getWindowsMicrophoneDevices();

    // 创建按钮并添加到布局
    for (int i = 0; i < in_device.size(); i++) {
        const auto& device = in_device[i];

        // 创建按钮
        QPushButton* btn = new QPushButton(device.name, buttonContainer);
        btn->setCheckable(true);
        btn->setMinimumHeight(40);
        btn->setFocusPolicy(Qt::TabFocus);
        btn->setObjectName("inAudioDeviceBtn" + QString::number(i));
        btn->setProperty("inAudioDeviceIndex", i); // 存储按钮对应的设备索引

        // 设置按钮样式
        btn->setStyleSheet(
            "QPushButton {"
            "    border: 2px solid #555;"
            "    border-radius: 5px;"
            "    background-color: #333;"
            "    color: white;"
            "    padding: 5px;"
            "}"
            "QPushButton:checked {"
            "    background-color: #0F2E75;"
            "    border-color: #0F2E75;"
            "}"
            "QPushButton:hover {"
            "    background-color: #444;"
            "}"
            "QPushButton:pressed {"
            "    background-color: #0F2E75;"
            "}"
            "QPushButton:focus {"
            "border: 2px solid #0088FF;" /* 更明显的焦点边框 */
            "}");

        // 如果设备名称包含"["，则默认选中
        if (device.name.contains("[")) {
            btn->setChecked(true);
            m_inAudioselectedIndex = i;
        }

        // 连接按钮点击事件到统一的槽函数
        connect(btn, &QPushButton::clicked, this, &CDlgOther::onAudioInputSelected);

        // 添加按钮到容器布局和按钮列表
        containerLayout->addWidget(btn);
        m_inAudioButtons.append(btn);
    }

    // 将容器添加到主布局
    ui->verticalLayout_5->addWidget(buttonContainer);



}

CDlgOther::~CDlgOther()
{

    delete ui;
}

// 清空布局中的所有控件
void CDlgOther::clearLayout(QLayout* layout)
{
    if (!layout) return;

    while (QLayoutItem* item = layout->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            delete widget;
        }
        delete item;
    }
}


//点击重启NVR
void CDlgOther::on_restNvrBtn_clicked() {

    //这里出发重启NVR动作
    int i = 1;

    //调用提示
    QString strHint = u8"编解码器设备重启成功，请等待1-2分钟后重新进入！";

    showHint(strHint, "red", 2500);
}

// 处理音频输出设备选择的槽函数
void CDlgOther::onAudioOutputSelected()
{
    QString oldNameBtn;
    QPushButton* senderBtn = qobject_cast<QPushButton*>(sender());
    if (!senderBtn) return;

    // 获取按钮对应的设备索引
    int index = senderBtn->property("outAudioDeviceIndex").toInt();




    // 取消之前选中的按钮
    if (m_outAudioselectedIndex >= 0 && m_outAudioselectedIndex < m_audioButtons.size()) {
        QPushButton* prevBtn = m_audioButtons[m_outAudioselectedIndex];
        if (prevBtn && prevBtn != senderBtn) {
            prevBtn->setChecked(false);


            //变更上一个选中的按钮信息
            oldNameBtn = m_audioButtons[m_outAudioselectedIndex]->text();
            QString oldPattern = "[" + QRegularExpression::escape(DEFAULT_CHECKED) + "]";
            QRegularExpression re(oldPattern);
            m_audioButtons[m_outAudioselectedIndex]->setText(oldNameBtn.replace(re, ""));
        }
    }

    // 更新选中的按钮索引
    m_outAudioselectedIndex = index;


    QString nameBtn = senderBtn->text();
    // 构建正则表达式模式：[,!]
    QString pattern = "[" + QRegularExpression::escape(DEFAULT_CHECKED) + "]";
    QRegularExpression re(pattern);

    QString btnStr = nameBtn.replace(re, "");



    // 处理设备选择
    InitDefaultAudioDevice(btnStr);
    senderBtn->setText(btnStr + DEFAULT_CHECKED);


    //
    //ui->widget_txt->setVisible(true);
    QString strHint = u8"音频输出设备切换成功！";

    showHint(strHint, "red", 2500);
}

// 处理音频输入设备选择的槽函数
void CDlgOther::onAudioInputSelected()
{
    QString oldNameBtn;
    QPushButton* senderBtn = qobject_cast<QPushButton*>(sender());
    if (!senderBtn) return;

    // 获取按钮对应的设备索引
    int index = senderBtn->property("inAudioDeviceIndex").toInt();

    // 取消之前选中的按钮
    if (m_inAudioselectedIndex >= 0 && m_inAudioselectedIndex < m_inAudioButtons.size()) {
        QPushButton* prevBtn = m_inAudioButtons[m_inAudioselectedIndex];
        if (prevBtn && prevBtn != senderBtn) {
            prevBtn->setChecked(false);


            //变更上一个选中的按钮信息
            oldNameBtn = m_inAudioButtons[m_inAudioselectedIndex]->text();
            QString oldPattern = "[" + QRegularExpression::escape(DEFAULT_CHECKED) + "]";
            QRegularExpression re(oldPattern);
            m_inAudioButtons[m_inAudioselectedIndex]->setText(oldNameBtn.replace(re, ""));
        }
    }

    // 更新选中的按钮索引
    m_inAudioselectedIndex = index;


    QString nameBtn = senderBtn->text();
    // 构建正则表达式模式：[,!]
    QString pattern = "[" + QRegularExpression::escape(DEFAULT_CHECKED) + "]";
    QRegularExpression re(pattern);

    QString btnStr = nameBtn.replace(re, "");



    // 处理设备选择
    SetDefaultMicrophoneByName(btnStr);
    senderBtn->setText(btnStr + DEFAULT_CHECKED);


    //
    //ui->widget_txt->setVisible(true);
    QString strHint = u8"麦克风设备切换成功！";

    showHint(strHint, "red", 2500);
}

//遥控器按下 返回按钮
void CDlgOther::on_otherBtnRet_clicked(QString objname)
{
    emit to_returnMain_signal();
}


//红外菜单
void CDlgOther::on_infraredMenu()
{

    //
//	if (!m_pInfraredMenu)
//	{
//		m_pInfraredMenu = new CInfraredDialogMenu(this, "CDlgPortSetting");
//	}
//
//	//
////	if  (  m_pInfraredMenu->winId()  !=  pQyMc)
//
//	//
//	if (!m_pInfraredMenu->isVisible())
//	{
//		//窗口只打开一次
//
//		m_pInfraredMenu->show();
//
//
//
//		return;
//
//	}
}

//菜单关闭
void CDlgOther::infraredMenu_quit()
{
    if (!m_pInfraredMenu)
    {
        return;
    }

    //if (m_pInfraredMenu->isVisible()) 
    {

        m_pInfraredMenu->close();
        if (m_pInfraredMenu)
        {
            delete m_pInfraredMenu;
            m_pInfraredMenu = nullptr;
        }

    }

    return;

}

//下箭头
void CDlgOther::Infrared_down()
{


    this->focusNextPrevChild(true);
}

//上箭头
void CDlgOther::Infrared_up()
{

    this->focusNextPrevChild(false);
}

//显示提示窗
void CDlgOther::showHint(QString msg, QString fontColor, qint64 out_time) {

    NoticeWidget::showNotice(this, msg, fontColor, out_time);

}