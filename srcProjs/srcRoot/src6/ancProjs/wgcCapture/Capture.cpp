


#include "Capture.h"

#include <winrt/base.h>

#include <winrt/Windows.Foundation.h>

#include <winrt/Windows.Graphics.h>

#include <winrt/Windows.Graphics.Capture.h>

#include <winrt/Windows.Graphics.DirectX.h>

#include <winrt/Windows.Graphics.DirectX.Direct3D11.h>

//#include <windows.graphics.directx.direct3d11.interop.h>
#include    "interop.h"

#include <iostream>






using namespace winrt;




WGCCapture::WGCCapture()
{
}


bool WGCCapture::Initialize(D3DHelpers& d3d)
{
    m_d3d = &d3d;


    m_monitor =
        MonitorFromPoint(
            POINT{ 0,0 },
            MONITOR_DEFAULTTOPRIMARY);


    if (!CreateCaptureItem())
        return false;


    if (!CreateFramePool())
        return false;


    return true;
}



bool WGCCapture::CreateCaptureItem()
{
    using namespace winrt::Windows::Graphics::Capture;


    auto factory =
        winrt::get_activation_factory<GraphicsCaptureItem>();


    auto interop =
        factory.as<IGraphicsCaptureItemInterop>();



    winrt::Windows::Graphics::Capture::GraphicsCaptureItem item{ nullptr };


    HRESULT hr =
        interop->CreateForMonitor(
            m_monitor,
            guid_of<winrt::Windows::Graphics::Capture::GraphicsCaptureItem>(),
            put_abi(item));


    if (FAILED(hr))
    {
        std::cout
            << "CreateForMonitor failed "
            << std::hex
            << hr
            << "\n";

        return false;
    }


    m_item = item;


    return true;
}



bool WGCCapture::CreateFramePool()
{

    m_pool =
        winrt::Windows::Graphics::Capture::Direct3D11CaptureFramePool::Create(
            m_d3d->WinRTDevice(),

            winrt::Windows::Graphics::DirectX::DirectXPixelFormat::
            B8G8R8A8UIntNormalized,

            2,

            m_item.Size()
        );


    m_session =
        m_pool.CreateCaptureSession(
            m_item);


    return true;
}



void WGCCapture::Start()
{
    if (m_session)
        m_session.StartCapture();
}



void WGCCapture::Stop()
{
    if (m_session)
    {
        m_session.Close();
        m_session = nullptr;
    }


    if (m_pool)
    {
        m_pool.Close();
        m_pool = nullptr;
    }
}



bool WGCCapture::GetFrame(
    winrt::com_ptr<ID3D11Texture2D>& texture)
{

    if (!m_pool)
        return false;



    auto frame =
        m_pool.TryGetNextFrame();



    if (!frame)
        return false;



    auto surface =
        frame.Surface();



    auto access =
        surface.as<
        IDirect3DDxgiInterfaceAccess>();


    HRESULT hr =
        access->GetInterface(
            __uuidof(ID3D11Texture2D),
            texture.put_void());


    if (FAILED(hr))
    {
        texture = nullptr;
        return false;
    }



    return true;
}
