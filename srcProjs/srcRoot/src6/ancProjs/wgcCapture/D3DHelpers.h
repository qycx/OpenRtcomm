#pragma once

#include <d3d11.h>
#include <dxgi1_6.h>

#include <winrt/base.h>
#include <winrt/Windows.Graphics.DirectX.Direct3D11.h>

using namespace winrt;
using namespace winrt::Windows::Graphics::DirectX::Direct3D11;

class D3DHelpers
{
public:

    bool Initialize();

    ID3D11Device* Device() const
    {
        return m_device.get();
    }

    ID3D11DeviceContext* Context() const
    {
        return m_context.get();
    }

    winrt::Windows::Graphics::DirectX::Direct3D11::IDirect3DDevice
        WinRTDevice() const
    {
        return m_winrtDevice;
    }

private:

    winrt::com_ptr<ID3D11Device> m_device;
    winrt::com_ptr<ID3D11DeviceContext> m_context;

    winrt::Windows::Graphics::DirectX::Direct3D11::IDirect3DDevice
        m_winrtDevice;
};

