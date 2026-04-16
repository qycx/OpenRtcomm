
#include    "stdafx.h"

#include <windows.h>
#include <dxgi.h>
#include <wrl/client.h>
#include <iostream>
#include    "gpuFunc.h"


// 简单函数判断是否 Intel GPU 并获取 DeviceId
bool bDetectIntelGPU(UINT& deviceId) 
{
    Microsoft::WRL::ComPtr<IDXGIFactory> factory;
    if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(factory.GetAddressOf())))) {
        std::cerr << "Failed to create DXGIFactory\n";
        return false;
    }

    UINT i = 0;
    Microsoft::WRL::ComPtr<IDXGIAdapter> adapter;
    while (factory->EnumAdapters(i++, adapter.GetAddressOf()) != DXGI_ERROR_NOT_FOUND) {
        DXGI_ADAPTER_DESC desc;
        adapter->GetDesc(&desc);

        if (desc.VendorId == 0x8086) { // Intel Vendor ID
            std::wcout << L"Found Intel GPU: " << desc.Description << L" DeviceId: 0x"
                << std::hex << desc.DeviceId << std::dec << std::endl;
            deviceId = desc.DeviceId;
            return true;
        }
    }
    return false;
}


// 根据 DeviceId 简单判断 GPU Generation
int getIntelGPUGen(UINT deviceId) {
    // Gen9: 0x1902–0x1912
    // Gen12: 0x9A49–0x9AFB
    // 这里只是示例，可按 Intel DeviceId 表更新
    if (deviceId >= 0x9A00) return 12; // Gen12+
    if (deviceId >= 0x1900) return 9;  // Gen9
    return 0; // Unknown / old
}


