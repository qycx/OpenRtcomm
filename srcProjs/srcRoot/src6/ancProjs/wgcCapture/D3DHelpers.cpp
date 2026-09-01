#include "D3DHelpers.h"

#include <windows.graphics.directx.direct3d11.interop.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"windowsapp.lib")

//using namespace winrt;
//using namespace winrt::Windows::Graphics::DirectX::Direct3D11;

extern "C"
HRESULT __stdcall CreateDirect3D11DeviceFromDXGIDevice(
    IDXGIDevice* dxgiDevice,
    IInspectable** graphicsDevice);

bool D3DHelpers::Initialize()
{
    UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#ifdef _DEBUG
    flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL levels[] =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1
    };

    D3D_FEATURE_LEVEL level;

    HRESULT hr = D3D11CreateDevice(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        flags,
        levels,
        ARRAYSIZE(levels),
        D3D11_SDK_VERSION,
        m_device.put(),
        &level,
        m_context.put());

    if (FAILED(hr))
        return false;

    auto dxgi = m_device.as<IDXGIDevice>();

    com_ptr<IInspectable> inspectable;

    hr = CreateDirect3D11DeviceFromDXGIDevice(
        dxgi.get(),
        inspectable.put());

    if (FAILED(hr))
        return false;

    m_winrtDevice =
        inspectable.as<IDirect3DDevice>();

    return true;
}


