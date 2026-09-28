
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


#if  0
// 根据 DeviceId 简单判断 GPU Generation
int getIntelGPUGen(UINT deviceId) {
    // Gen9: 0x1902–0x1912
    // Gen12: 0x9A49–0x9AFB
    // 这里只是示例，可按 Intel DeviceId 表更新
    if (deviceId >= 0x9A00) return 12; // Gen12+
    if (deviceId >= 0x1900) return 9;  // Gen9
    return 0; // Unknown / old
}
#endif 



// qyIntelGpuInfo.h
// Intel GPU 代际判断 + DXGI 枚举辅助（header-only，可直接加入工程）
// 用途：bIntelGpu / oneVPL vs MSDK 分流的兜底探测
// 规则：gen >= 12 -> oneVPL runtime (libmfx-gen.dll, ver 2.x)
//       gen 9~11  -> MSDK legacy 路径 (libmfx64.dll, ver 1.x)
//       返回 0    -> 未知/更老平台（Haswell 0x04xx、Broadwell 0x16xx 等）
//
// 注意：Intel DeviceId 不按代际单调递增，禁止用 >= 阈值判断，必须查表。
// 本表只做兜底；首选还是 oneVPL dispatcher 的 runtime 版本探测
// （param_getModuleInfo.usMajor == 2 即 VPL 平台）。
// 编码：UTF-8（若工程未开 /utf-8，请确认文件带 BOM，避免中文注释乱码）

#pragma once

#include <windows.h>
#include <dxgi.h>
#pragma comment(lib, "dxgi.lib")

// ---------------------------------------------------------------------------
// 根据 DeviceId 查表判断 GPU Generation
// 返回 9 / 11 / 12；0 = 未知
// ---------------------------------------------------------------------------
 int getIntelGPUGen(UINT deviceId)
{
    static const struct { UINT lo, hi; int gen; } kTable[] = {
        // Gen9  (Skylake)
        { 0x1902, 0x193B,  9 },
        // Gen9.5 (Kaby Lake / Coffee Lake / Amber Lake / CML 刷新)
        { 0x5902, 0x593B,  9 },
        { 0x3E90, 0x3EA9,  9 },
        { 0x9B21, 0x9BCF,  9 },
        // Gen11 (Ice Lake) —— 旧阈值法会把这段误判成 Gen9，必须单列
        { 0x8A50, 0x8A5D, 11 },
        // Gen12 (Tiger Lake)
        { 0x9A40, 0x9AC9, 12 },
        // Gen12 (Rocket Lake)
        { 0x4C80, 0x4C8B, 12 },
        // Gen12 (DG1 独显 / SDV)
        { 0x4905, 0x4908, 12 },
        // Gen12 (Alder Lake iGPU)
        { 0x4680, 0x46A8, 12 },
        // Gen12 (Raptor Lake iGPU)
        { 0xA780, 0xA7A9, 12 },
        // Xe-HPG (Arc DG2 桌面/移动，Alchemist)
        { 0x5670, 0x56A6, 12 },
        // Gen12.x (Meteor Lake Xe-LPG，0x7D4x / 0x64xx 两段)
        { 0x7D40, 0x7D5F, 12 },
        { 0x6420, 0x64A0, 12 },
        // Core Ultra 5 225U (Arrow Lake-U) DeviceId = 0x7D41，落在 0x7D40 段内
        // 新平台出现未知 DeviceId 时按 Intel ARK 补表即可
    };

    for (const auto& r : kTable) {
        if (deviceId >= r.lo && deviceId <= r.hi)
            return r.gen;
    }
    //return 0;
    return  12;     //  新显卡都当12代处理
}

// ---------------------------------------------------------------------------
// 枚举 DXGI 适配器，找第一块 Intel GPU（VendorId == 0x8086）
// 输出：pDeviceId = PCI DeviceId，pGen = 代际（可为 NULL）
// 返回：找到 Intel GPU 返回 true
//
// 新显卡策略：查表未命中（返回 0）时乐观假设 gen = 12 走 VPL——
// 2015 年后的 Intel GPU 均为 Gen12+/VPL 原生方向，VPL runtime 加载失败
// 由会话建立处的实测兜底降级。DeviceId 会经 pDeviceId 带回，
// 调用方应把未知 DeviceId 打进日志（dev 0x%04X），事后按 Intel ARK 补表。
// ---------------------------------------------------------------------------






