

#pragma once

#include <windows.h>
#include <d3d11.h>

#include <winrt/base.h>

#include <winrt/Windows.Graphics.Capture.h>
#include <winrt/Windows.Graphics.DirectX.Direct3D11.h>

#include "D3DHelpers.h"
#include "interop.h"


class WGCCapture
{
public:

    WGCCapture();

    bool Initialize(D3DHelpers& d3d);

    void Start();

    void Stop();


    bool GetFrame(
        winrt::com_ptr<ID3D11Texture2D>& texture);


private:

    bool CreateCaptureItem();

    bool CreateFramePool();


private:

    D3DHelpers* m_d3d = nullptr;

    HMONITOR m_monitor = nullptr;


    winrt::Windows::Graphics::Capture::GraphicsCaptureItem
        m_item{ nullptr };


    winrt::Windows::Graphics::Capture::Direct3D11CaptureFramePool
        m_pool{ nullptr };


    winrt::Windows::Graphics::Capture::GraphicsCaptureSession
        m_session{ nullptr };
};

