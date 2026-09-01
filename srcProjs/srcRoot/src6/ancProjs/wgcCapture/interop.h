
#pragma once

#include <windows.h>
#include <unknwn.h>


// Windows Graphics Capture Interop
struct __declspec(uuid("3628E81B-3CAC-4C60-B7F4-23CE0E0C3356"))
    IGraphicsCaptureItemInterop : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE CreateForWindow(
        HWND window,
        REFIID riid,
        void** result) = 0;


    virtual HRESULT STDMETHODCALLTYPE CreateForMonitor(
        HMONITOR monitor,
        REFIID riid,
        void** result) = 0;
};


// Direct3D Surface Interop
struct __declspec(uuid("A9B3D012-3DF2-4EE3-B8D1-8695F457D3C1"))
    IDirect3DDxgiInterfaceAccess : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE GetInterface(
        REFIID iid,
        void** object) = 0;
};