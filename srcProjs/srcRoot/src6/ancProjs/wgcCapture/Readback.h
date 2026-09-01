#pragma once

#include <d3d11.h>
#include <vector>

#include <winrt/base.h>


class Readback
{
public:

    bool Copy(
        ID3D11Device* device,
        ID3D11DeviceContext* context,
        ID3D11Texture2D* src,
        std::vector<unsigned char>& buffer,
        int& width,
        int& height
    );


private:

    winrt::com_ptr<ID3D11Texture2D>
        m_staging;

    //
    UINT m_width = 0;
    UINT m_height = 0;

};

