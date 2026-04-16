
#include	"stdafx.h"

#include	<tchar.h>

#include <streams.h>
#include <strsafe.h>

#include "DShowUtil.h"

//  #include	"qyMcMainCommon.h"
//  #include	"qmcVideoCapture_isCli.h"
//  #include	"qyAvRecordPublic.h"
//  #include	"qyDynLib.h"

#include	<mmsystem.h>

#include	<dbt.h>
#include	<mmreg.h>
#include	<msacm.h>
#ifndef  __WINCE__
	#include	<fcntl.h>
	#include	<io.h>
#endif
#include	<stdio.h>
#include	<commdlg.h>
#include	<strsafe.h>

#include	<dshow.h>

#ifndef  __WINCE__
	//  #include	<Qedit.h>
#endif
#include	<Mediaobj.h>
#include	<Dmo.h>


#include	<vfw.h>
#include	<WinSock2.h>

#include	"qyCommonEx.h"
#include	"qyMtSock.h"

#include	"qyPreCustom.h"
#include	"qyCustom.h"

#include	"qyWmComm.h"
#include	"qyCommCommon.h"

#include	"qyLicense.h"
#include	"qyCommProc.h"

#include	"qmOpenCommon.h"

#include	"qyString.h"							//  2010/07/04

#include	"traceLog.h"
#include	"qyLangCommProc.h"						//  2005/01/24
#include	"qySyncCommProc.h"
#include	"genericqueue.h"
#include	"qyq2.h"								//  2009/05/13

#include	"qnmCommProc.h"
#include	"qnmCommProc1.h"
#include	"qyMsgFunc.h"
#include	"qnmCommProc_mis.h"						//  2007/04/02

#include	"qmcDmoPublic.h"

//  #include	"qmcVideoCapture_dx.h"

#include "crossbar.h"
#include "SampleCGB.h"

#define		__SUPPORT_ISampleCaptureGraphBuilder__
#define		__SUPPORT_CCrossbar__

#include	"amCapProc.h"
#include	"isCmdConst.h"

#define ABS(x) (((x) > 0) ? (x) : -(x))
//  #define WM_FGNOTIFY WM_USER+1
#define WM_FGNOTIFY CONST_qyWm_graphNotify_mediaDevice		//  2012/02/27



HWND ghwndStatus=0;


 __declspec(dllexport)  void  *  get_ICaptureGraphBuilder(  void  *  pBuilderParam  )
{
	ISampleCaptureGraphBuilder  *  pBuilder  =  (  ISampleCaptureGraphBuilder  *  )pBuilderParam;
	
	//  2012/02/17
	if  (  !pBuilder  )  return  NULL;

	return  pBuilder->graphBuilder2_;
}


 void statusUpdateStatus(HWND hwnd, LPCTSTR lpsz)
 {
 }


void ErrMsg(LPTSTR szFormat,...)
{
}

void ErrMsg_amCap(LPTSTR szFormat,...)
{
}

__declspec(dllexport) void IMonRelease(IMoniker *&pm)
{
    if(pm)
    {
        pm->Release();
        pm = 0;
    }
}


// Make a graph builder object we can use for capture graph building
//
BOOL MakeBuilder(  AV_capStuff  &  gcap  )
{
    // we have one already
    if(gcap.pBuilder)
        return TRUE;

    gcap.pBuilder = new ISampleCaptureGraphBuilder( );
    if( NULL == gcap.pBuilder )
    {
        return FALSE;
    }

    return TRUE;
}



// Make a graph object we can use for capture graph building
//
BOOL MakeGraph(  AV_capStuff  &  gcap  )
{
    // we have one already
    if(gcap.pFg)
        return TRUE;

    HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC,
                                  IID_IGraphBuilder, (LPVOID *)&gcap.pFg);

    return (hr == NOERROR) ? TRUE : FALSE;
}

int statusGetHeight(void)
{
	//  临时
	return  0;
}

int statusGetHeight_amCap(void)
{
	return  0;
}

// make sure the preview window inside our window is as big as the
// dimensions of captured video, or some capture cards won't show a preview.
// (Also, it helps people tell what size video they're capturing)
// We will resize our app's window big enough so that once the status bar
// is positioned at the bottom there will be enough room for the preview
// window to be w x h
//
int gnRecurse = 0;


void ResizeWindow(HWND ghwndApp,int w, int h)
{
#if  1
	#ifdef  __DEBUG__
			traceLog(  _T(  "不使用ResizeWindow"  )  );
	#endif
	return;
#endif

	if  (  !IsWindow(  ghwndApp  )  )  return;		

    RECT rcW, rcC;
    int xExtra, yExtra;
    int cyBorder = GetSystemMetrics(SM_CYBORDER);

    gnRecurse++;

    GetWindowRect(ghwndApp, &rcW);
    GetClientRect(ghwndApp, &rcC);
    xExtra = rcW.right - rcW.left - rcC.right;
    yExtra = rcW.bottom - rcW.top - rcC.bottom + cyBorder + statusGetHeight();

    rcC.right = w;
    rcC.bottom = h;
    SetWindowPos(ghwndApp, NULL, 0, 0, rcC.right + xExtra,
        rcC.bottom + yExtra, SWP_NOZORDER | SWP_NOMOVE);

    // we may need to recurse once.  But more than that means the window cannot
    // be made the size we want, trying will just stack fault.
    //
    if(gnRecurse == 1 && ((rcC.right + xExtra != rcW.right - rcW.left && w > GetSystemMetrics(SM_CXMIN)) ||
        (rcC.bottom + yExtra != rcW.bottom - rcW.top)))
        ResizeWindow(ghwndApp,w,h);

    gnRecurse--;
}

void ResizeWindow_amCap(HWND  ghwndApp,  int w, int h)
{
	ResizeWindow(  ghwndApp,  w,  h  );
}

// Tear down everything downstream of a given filter
void NukeDownstream(AV_capStuff  &  gcap,  IBaseFilter *pf)
{
    IPin *pP=0, *pTo=0;
    ULONG u;
    IEnumPins *pins = NULL;
    PIN_INFO pininfo;

    if (!pf)
        return;

    HRESULT hr = pf->EnumPins(&pins);
    pins->Reset();

    while(hr == NOERROR)
    {
        hr = pins->Next(1, &pP, &u);
        if(hr == S_OK && pP)
        {
            pP->ConnectedTo(&pTo);
            if(pTo)
            {
                hr = pTo->QueryPinInfo(&pininfo);
                if(hr == NOERROR)
                {
                    if(pininfo.dir == PINDIR_INPUT)
                    {
                        NukeDownstream(gcap,  pininfo.pFilter);
                        gcap.pFg->Disconnect(pTo);
                        gcap.pFg->Disconnect(pP);
                        gcap.pFg->RemoveFilter(pininfo.pFilter);
                    }
                    pininfo.pFilter->Release();
                }
                pTo->Release();
            }
            pP->Release();
        }
    }

    if(pins)
        pins->Release();
}



// Tear down everything downstream of the capture filters, so we can build
// a different capture graph.  Notice that we never destroy the capture filters
// and WDM filters upstream of them, because then all the capture settings
// we've set would be lost.
//
__declspec(dllexport) void TearDownGraph(  AV_capStuff  &  gcap )
{
    SAFE_RELEASE(gcap.pSink);
    SAFE_RELEASE(gcap.pConfigAviMux);
    SAFE_RELEASE(gcap.pRender);
    SAFE_RELEASE(gcap.pME);
    SAFE_RELEASE(gcap.pDF);

    if(gcap.pVW)
    {
        // stop drawing in our window, or we may get wierd repaint effects
        gcap.pVW->put_Owner(NULL);
        gcap.pVW->put_Visible(OAFALSE);
        gcap.pVW->Release();
        gcap.pVW = NULL;
    }

    // destroy the graph downstream of our capture filters
    if(gcap.pVCap)
        NukeDownstream(gcap,gcap.pVCap);
    if(gcap.pACap)
        NukeDownstream(gcap,gcap.pACap);
    if(gcap.pVCap)
        gcap.pBuilder->ReleaseFilters();

    // potential debug output - what the graph looks like
    // if (gcap.pFg) DumpGraph(gcap.pFg, 1);

#ifdef REGISTER_FILTERGRAPH
    // Remove filter graph from the running object table
    if(g_dwGraphRegister)
    {
        RemoveGraphFromRot(g_dwGraphRegister);
        g_dwGraphRegister = 0;
    }
#endif

    gcap.fCaptureGraphBuilt = FALSE;
    gcap.fPreviewGraphBuilt = FALSE;
    gcap.fPreviewFaked = FALSE;
}

#if  10
 __declspec(dllexport) BOOL InitCapFilters(  AV_capStuff  &  gcap  )
{
    HRESULT hr=S_OK;
    BOOL f;

    gcap.fCCAvail = FALSE;  // assume no closed captioning support

    f = MakeBuilder(gcap);
    if(!f)
    {
        ErrMsg(TEXT("Cannot instantiate graph builder"));
        return FALSE;
    }

    //
    // First, we need a Video Capture filter, and some interfaces
    //
    gcap.pVCap = NULL;

    if(gcap.pmVideo != 0)
    {
        IPropertyBag *pBag;
        gcap.wachFriendlyName[0] = 0;

        hr = gcap.pmVideo->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
        if(SUCCEEDED(hr))
        {
            VARIANT var;
            var.vt = VT_BSTR;

            hr = pBag->Read(L"FriendlyName", &var, NULL);
            if(hr == NOERROR)
            {
                hr = StringCchCopyW(gcap.wachFriendlyName, sizeof(gcap.wachFriendlyName) / sizeof(gcap.wachFriendlyName[0]), var.bstrVal);
                SysFreeString(var.bstrVal);
            }

            pBag->Release();
        }

        hr = gcap.pmVideo->BindToObject(0, 0, IID_IBaseFilter, (void**)&gcap.pVCap);
    }

    if(gcap.pVCap == NULL)
    {
        ErrMsg(TEXT("Error %x: Cannot create video capture filter"), hr);
        goto InitCapFiltersFail;
    }

    //
    // make a filtergraph, give it to the graph builder and put the video
    // capture filter in the graph
    //

    f = MakeGraph(gcap);
    if(!f)
    {
        ErrMsg(TEXT("Cannot instantiate filtergraph"));
        goto InitCapFiltersFail;
    }

    hr = gcap.pBuilder->SetFiltergraph(gcap.pFg);
    if(hr != NOERROR)
    {
        ErrMsg(TEXT("Cannot give graph to builder"));
        goto InitCapFiltersFail;
    }

    // Add the video capture filter to the graph with its friendly name
    hr = gcap.pFg->AddFilter(gcap.pVCap, gcap.wachFriendlyName);
    if(hr != NOERROR)
    {
        ErrMsg(TEXT("Error %x: Cannot add vidcap to filtergraph"), hr);
        goto InitCapFiltersFail;
    }

    // Calling FindInterface below will result in building the upstream
    // section of the capture graph (any WDM TVTuners or Crossbars we might
    // need).

    // we use this interface to get the name of the driver
    // Don't worry if it doesn't work:  This interface may not be available
    // until the pin is connected, or it may not be available at all.
    // (eg: interface may not be available for some DV capture)
    hr = gcap.pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                                      &MEDIATYPE_Interleaved, gcap.pVCap,
                                      IID_IAMVideoCompression, (void **)&gcap.pVC);
    if(hr != S_OK)
    {
        hr = gcap.pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                                          &MEDIATYPE_Video, gcap.pVCap,
                                          IID_IAMVideoCompression, (void **)&gcap.pVC);
    }

    // !!! What if this interface isn't supported?
    // we use this interface to set the frame rate and get the capture size
    hr = gcap.pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                                      &MEDIATYPE_Interleaved,
                                      gcap.pVCap, IID_IAMStreamConfig, (void **)&gcap.pVSC);

    if(hr != NOERROR)
    {
        hr = gcap.pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                                          &MEDIATYPE_Video, gcap.pVCap,
                                          IID_IAMStreamConfig, (void **)&gcap.pVSC);
        if(hr != NOERROR)
        {
            // this means we can't set frame rate (non-DV only)
            ErrMsg(TEXT("Error %x: Cannot find VCapture:IAMStreamConfig"), hr);
        }
    }

    gcap.fCapAudioIsRelevant = TRUE;

    AM_MEDIA_TYPE *pmt;

    // default capture format
    if(gcap.pVSC && gcap.pVSC->GetFormat(&pmt) == S_OK)
    {
        // DV capture does not use a VIDEOINFOHEADER
        if(pmt->formattype == FORMAT_VideoInfo)
        {
            // resize our window to the default capture size
			ResizeWindow(gcap.ghwndApp,HEADER(pmt->pbFormat)->biWidth,
                         ABS(HEADER(pmt->pbFormat)->biHeight));
        }
        if(pmt->majortype != MEDIATYPE_Video)
        {
            // This capture filter captures something other that pure video.
            // Maybe it's DV or something?  Anyway, chances are we shouldn't
            // allow capturing audio separately, since our video capture
            // filter may have audio combined in it already!
            gcap.fCapAudioIsRelevant = FALSE;
            gcap.fCapAudio = FALSE;
        }
        DeleteMediaType(pmt);
    }

    // we use this interface to bring up the 3 dialogs
    // NOTE:  Only the VfW capture filter supports this.  This app only brings
    // up dialogs for legacy VfW capture drivers, since only those have dialogs
    hr = gcap.pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                                      &MEDIATYPE_Video, gcap.pVCap,
                                      IID_IAMVfwCaptureDialogs, (void **)&gcap.pDlg);

    // Use the crossbar class to help us sort out all the possible video inputs
    // The class needs to be given the capture filters ANALOGVIDEO input pin
    {
        IPin        *pP = 0;
        IEnumPins   *pins=0;
        ULONG        n;
        PIN_INFO     pinInfo;
        BOOL         Found = FALSE;
        IKsPropertySet *pKs=0;
        GUID guid;
        DWORD dw;
        BOOL fMatch = FALSE;

        gcap.pCrossbar = NULL;

        if(SUCCEEDED(gcap.pVCap->EnumPins(&pins)))
        {
            while(!Found && (S_OK == pins->Next(1, &pP, &n)))
            {
                if(S_OK == pP->QueryPinInfo(&pinInfo))
                {
                    if(pinInfo.dir == PINDIR_INPUT)
                    {
                        // is this pin an ANALOGVIDEOIN input pin?
                        if(pP->QueryInterface(IID_IKsPropertySet,
                            (void **)&pKs) == S_OK)
                        {
                            if(pKs->Get(AMPROPSETID_Pin,
                                AMPROPERTY_PIN_CATEGORY, NULL, 0,
                                &guid, sizeof(GUID), &dw) == S_OK)
                            {
                                if(guid == PIN_CATEGORY_ANALOGVIDEOIN)
                                    fMatch = TRUE;
                            }
                            pKs->Release();
                        }

                        if(fMatch)
                        {
                            HRESULT hrCreate=S_OK;
                            gcap.pCrossbar = new CCrossbar(pP, &hrCreate);
                            if (!gcap.pCrossbar || FAILED(hrCreate))
                                break;

                            hr = gcap.pCrossbar->GetInputCount(&gcap.NumberOfVideoInputs);
                            Found = TRUE;
                        }
                    }
                    pinInfo.pFilter->Release();
                }
                pP->Release();
            }
            pins->Release();
        }
    }

    // there's no point making an audio capture filter
    if(gcap.fCapAudioIsRelevant == FALSE)
        goto SkipAudio;

    // create the audio capture filter, even if we are not capturing audio right
    // now, so we have all the filters around all the time.

    //
    // We want an audio capture filter and some interfaces
    //

    if(gcap.pmAudio == 0)
    {
        // there are no audio capture devices. We'll only allow video capture
        gcap.fCapAudio = FALSE;
        goto SkipAudio;
    }
    gcap.pACap = NULL;


    hr = gcap.pmAudio->BindToObject(0, 0, IID_IBaseFilter, (void**)&gcap.pACap);

    if(gcap.pACap == NULL)
    {
        // there are no audio capture devices. We'll only allow video capture
        gcap.fCapAudio = FALSE;
        ErrMsg(TEXT("Cannot create audio capture filter"));
        goto SkipAudio;
    }

    //
    // put the audio capture filter in the graph
    //
    {
        WCHAR wachAudioFriendlyName[256];
        IPropertyBag *pBag;

        wachAudioFriendlyName[0] = 0;

        // Read the friendly name of the filter to assist with remote graph
        // viewing through GraphEdit
        hr = gcap.pmAudio->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
        if(SUCCEEDED(hr))
        {
            VARIANT var;
            var.vt = VT_BSTR;

            hr = pBag->Read(L"FriendlyName", &var, NULL);
            if(hr == NOERROR)
            {
                hr = StringCchCopyW(wachAudioFriendlyName, 256, var.bstrVal);
                SysFreeString(var.bstrVal);
            }

            pBag->Release();
        }

        // We'll need this in the graph to get audio property pages
        hr = gcap.pFg->AddFilter(gcap.pACap, wachAudioFriendlyName);
        if(hr != NOERROR)
        {
            ErrMsg(TEXT("Error %x: Cannot add audio capture filter to filtergraph"), hr);
            goto InitCapFiltersFail;
        }
    }

    // Calling FindInterface below will result in building the upstream
    // section of the capture graph (any WDM TVAudio's or Crossbars we might
    // need).

    // !!! What if this interface isn't supported?
    // we use this interface to set the captured wave format
    hr = gcap.pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Audio, gcap.pACap,
                                      IID_IAMStreamConfig, (void **)&gcap.pASC);

    if(hr != NOERROR)
    {
        ErrMsg(TEXT("Cannot find ACapture:IAMStreamConfig"));
    }

SkipAudio:

    // Can this filter do closed captioning?
    IPin *pPin;
    hr = gcap.pBuilder->FindPin(gcap.pVCap, PINDIR_OUTPUT, &PIN_CATEGORY_VBI,
                                NULL, FALSE, 0, &pPin);
    if(hr != S_OK)
        hr = gcap.pBuilder->FindPin(gcap.pVCap, PINDIR_OUTPUT, &PIN_CATEGORY_CC,
                                    NULL, FALSE, 0, &pPin);
    if(hr == S_OK)
    {
        pPin->Release();
        gcap.fCCAvail = TRUE;
    }
    else
    {
        gcap.fCapCC = FALSE;    // can't capture it, then
    }

    // potential debug output - what the graph looks like
    // DumpGraph(gcap.pFg, 1);

    return TRUE;

InitCapFiltersFail:
    FreeCapFilters(gcap);
    return FALSE;
}
#endif


#if  10
// all done with the capture filters and the graph builder
//
__declspec(dllexport) void FreeCapFilters(  AV_capStuff  &  gcap  )
{
    SAFE_RELEASE(gcap.pFg);
    if( gcap.pBuilder )
    {
        delete gcap.pBuilder;
        gcap.pBuilder = NULL;
    }
    SAFE_RELEASE(gcap.pVCap);
    SAFE_RELEASE(gcap.pACap);
    SAFE_RELEASE(gcap.pASC);
    SAFE_RELEASE(gcap.pVSC);
    SAFE_RELEASE(gcap.pVC);
    SAFE_RELEASE(gcap.pDlg);

    if(gcap.pCrossbar)
    {
        delete gcap.pCrossbar;
        gcap.pCrossbar = NULL;
    }
}
#endif



// build the preview graph!
//
// !!! PLEASE NOTE !!!  Some new WDM devices have totally separate capture
// and preview settings.  An application that wishes to preview and then
// capture may have to set the preview pin format using IAMStreamConfig on the
// preview pin, and then again on the capture pin to capture with that format.
// In this sample app, there is a separate page to set the settings on the
// capture pin and one for the preview pin.  To avoid the user
// having to enter the same settings in 2 dialog boxes, an app can have its own
// UI for choosing a format (the possible formats can be enumerated using
// IAMStreamConfig) and then the app can programmatically call IAMStreamConfig
// to set the format on both pins.
//
#if  10
__declspec(dllexport) BOOL BuildPreviewGraph(  AV_capStuff  &  gcap  )
{
    int cy, cyBorder;
    HRESULT hr;
    AM_MEDIA_TYPE *pmt;

    // we have one already
    if(gcap.fPreviewGraphBuilt)
        return TRUE;

    // No rebuilding while we're running
    if(gcap.fCapturing || gcap.fPreviewing)
        return FALSE;

    // We don't have the necessary capture filters
    if(gcap.pVCap == NULL)
        return FALSE;
    if(gcap.pACap == NULL && gcap.fCapAudio)
        return FALSE;

    // we already have another graph built... tear down the old one
    if(gcap.fCaptureGraphBuilt)
        TearDownGraph(gcap);

    //
    // Render the preview pin - even if there is not preview pin, the capture
    // graph builder will use a smart tee filter and provide a preview.
    //
    // !!! what about latency/buffer issues?

    // NOTE that we try to render the interleaved pin before the video pin, because
    // if BOTH exist, it's a DV filter and the only way to get the audio is to use
    // the interleaved pin.  Using the Video pin on a DV filter is only useful if
    // you don't want the audio.

    if( gcap.fMPEG2 )
    {
        hr = gcap.pBuilder->RenderStream(&PIN_CATEGORY_PREVIEW,
                                         &MEDIATYPE_Stream, gcap.pVCap, NULL, NULL);
        if( FAILED( hr ) )
        {
            ErrMsg(TEXT("Cannot build MPEG2 preview graph!"));
        }

    }
    else
    {
        hr = gcap.pBuilder->RenderStream(&PIN_CATEGORY_PREVIEW,
                                         &MEDIATYPE_Interleaved, gcap.pVCap, NULL, NULL);
        if(hr == VFW_S_NOPREVIEWPIN)
        {
            // preview was faked up for us using the (only) capture pin
            gcap.fPreviewFaked = TRUE;
        }
        else if(hr != S_OK)
        {
            // maybe it's DV?
            hr = gcap.pBuilder->RenderStream(&PIN_CATEGORY_PREVIEW,
                                             &MEDIATYPE_Video, gcap.pVCap, NULL, NULL);
            if(hr == VFW_S_NOPREVIEWPIN)
            {
                // preview was faked up for us using the (only) capture pin
                gcap.fPreviewFaked = TRUE;
            }
            else if(hr != S_OK)
            {
                ErrMsg(TEXT("This graph cannot preview!"));
                gcap.fPreviewGraphBuilt = FALSE;
                return FALSE;
            }
        }

        //
        // Render the closed captioning pin? It could be a CC or a VBI category pin,
        // depending on the capture driver
        //

        if(gcap.fCapCC)
        {
            hr = gcap.pBuilder->RenderStream(&PIN_CATEGORY_CC, NULL,
                                             gcap.pVCap, NULL, NULL);
            if(hr != NOERROR)
            {
                hr = gcap.pBuilder->RenderStream(&PIN_CATEGORY_VBI, NULL,
                                                 gcap.pVCap, NULL, NULL);
                if(hr != NOERROR)
                {
                    ErrMsg(TEXT("Cannot render closed captioning"));
                }
            }
        }
    }

    //
    // Get the preview window to be a child of our app's window
    //

    // This will find the IVideoWindow interface on the renderer.  It is
    // important to ask the filtergraph for this interface... do NOT use
    // ICaptureGraphBuilder2::FindInterface, because the filtergraph needs to
    // know we own the window so it can give us display changed messages, etc.

    hr = gcap.pFg->QueryInterface(IID_IVideoWindow, (void **)&gcap.pVW);
    if(hr != NOERROR)
    {
        ErrMsg(TEXT("This graph cannot preview properly"));
    }
    else
    {
        //Find out if this is a DV stream
        AM_MEDIA_TYPE * pmtDV;

        if(gcap.pVSC && SUCCEEDED(gcap.pVSC->GetFormat(&pmtDV)))
        {
            if(pmtDV->formattype == FORMAT_DvInfo)
            {
                // in this case we want to set the size of the parent window to that of
                // current DV resolution.
                // We get that resolution from the IVideoWindow.
                SmartPtr<IBasicVideo> pBV;

				// If we got here, gcap.pVW is not NULL 
				ASSERT(gcap.pVW != NULL);
				hr = gcap.pVW->QueryInterface(IID_IBasicVideo, (void**)&pBV);

                if(SUCCEEDED(hr))
                {
                    HRESULT hr1, hr2;
                    long lWidth, lHeight;

                    hr1 = pBV->get_VideoHeight(&lHeight);
                    hr2 = pBV->get_VideoWidth(&lWidth);
                    if(SUCCEEDED(hr1) && SUCCEEDED(hr2))
                    {
                        ResizeWindow(gcap.ghwndApp,lWidth, abs(lHeight));
                    }
                }
            }
        }

        RECT rc;
        gcap.pVW->put_Owner((OAHWND)gcap.ghwndApp);    // We own the window now
        gcap.pVW->put_WindowStyle(WS_CHILD);    // you are now a child

        // give the preview window all our space but where the status bar is
        GetClientRect(gcap.ghwndApp, &rc);
        cyBorder = GetSystemMetrics(SM_CYBORDER);
        cy = statusGetHeight() + cyBorder;
        rc.bottom -= cy;

        gcap.pVW->SetWindowPosition(0, 0, rc.right, rc.bottom); // be this big
        gcap.pVW->put_Visible(OATRUE);
    }

    // now tell it what frame rate to capture at.  Just find the format it
    // is capturing with, and leave everything alone but change the frame rate
    // No big deal if it fails.  It's just for preview
    // !!! Should we then talk to the preview pin?
    if(gcap.pVSC && gcap.fUseFrameRate)
    {
        hr = gcap.pVSC->GetFormat(&pmt);

        // DV capture does not use a VIDEOINFOHEADER
        if(hr == NOERROR)
        {
            if(pmt->formattype == FORMAT_VideoInfo)
            {
                VIDEOINFOHEADER *pvi = (VIDEOINFOHEADER *)pmt->pbFormat;
                pvi->AvgTimePerFrame = (LONGLONG)(10000000 / gcap.FrameRate);

                hr = gcap.pVSC->SetFormat(pmt);
                if(hr != NOERROR)
                    ErrMsg(TEXT("%x: Cannot set frame rate for preview"), hr);
            }
            DeleteMediaType(pmt);
        }
    }

    // make sure we process events while we're previewing!
    hr = gcap.pFg->QueryInterface(IID_IMediaEventEx, (void **)&gcap.pME);
    if(hr == NOERROR)
    {
        gcap.pME->SetNotifyWindow((OAHWND)gcap.ghwndApp, WM_FGNOTIFY, 0);
    }

    // potential debug output - what the graph looks like
    // DumpGraph(gcap.pFg, 1);

    // Add our graph to the running object table, which will allow
    // the GraphEdit application to "spy" on our graph
#ifdef REGISTER_FILTERGRAPH
    hr = AddGraphToRot(gcap.pFg, &g_dwGraphRegister);
    if(FAILED(hr))
    {
        ErrMsg(TEXT("Failed to register filter graph with ROT!  hr=0x%x"), hr);
        g_dwGraphRegister = 0;
    }
#endif

    // All done.
    gcap.fPreviewGraphBuilt = TRUE;
    return TRUE;
}
#endif


// Start previewing
//
__declspec(dllexport) BOOL StartPreview(  AV_capStuff  &  gcap  )
{
    // way ahead of you
    if(gcap.fPreviewing)
        return TRUE;

    if(!gcap.fPreviewGraphBuilt)
        return FALSE;

    // run the graph
    IMediaControl *pMC = NULL;
    HRESULT hr = gcap.pFg->QueryInterface(IID_IMediaControl, (void **)&pMC);
    if(SUCCEEDED(hr))
    {
        hr = pMC->Run();
        if(FAILED(hr))
        {
            // stop parts that ran
            pMC->Stop();
        }
        pMC->Release();
    }
    if(FAILED(hr))
    {
        ErrMsg(TEXT("Error %x: Cannot run preview graph"), hr);
        return FALSE;
    }

    gcap.fPreviewing = TRUE;
    return TRUE;
}




// stop the preview graph
//
__declspec(dllexport) BOOL StopPreview(  AV_capStuff  &  gcap  )
{
    // way ahead of you
    if(!gcap.fPreviewing)
    {
        return FALSE;
    }

    // stop the graph
    IMediaControl *pMC = NULL;
    HRESULT hr = gcap.pFg->QueryInterface(IID_IMediaControl, (void **)&pMC);
    if(SUCCEEDED(hr))
    {
        hr = pMC->Stop();
        pMC->Release();
    }
    if(FAILED(hr))
    {
        ErrMsg(TEXT("Error %x: Cannot stop preview graph"), hr);
        return FALSE;
    }

    gcap.fPreviewing = FALSE;

    // get rid of menu garbage
    //  InvalidateRect(ghwndApp, NULL, TRUE);

    return TRUE;
}


// stop the capture graph
//
__declspec(dllexport) BOOL StopCapture(AV_capStuff  &  gcap)
{
    // way ahead of you
    if(!gcap.fCapturing)
    {
        return FALSE;
    }

    // stop the graph
    IMediaControl *pMC = NULL;
    HRESULT hr = gcap.pFg->QueryInterface(IID_IMediaControl, (void **)&pMC);
    if(SUCCEEDED(hr))
    {
        hr = pMC->Stop();
        pMC->Release();
    }
    if(FAILED(hr))
    {
        ErrMsg(TEXT("Error %x: Cannot stop graph"), hr);
        return FALSE;
    }

    // when the graph was stopped
    gcap.lCapStopTime = timeGetTime();

    // no more status bar updates
    KillTimer(gcap.ghwndApp, 1);

    // one last time for the final count and all the stats
    //  UpdateStatus(TRUE);

    gcap.fCapturing = FALSE;

    // get rid of menu garbage
    InvalidateRect(gcap.ghwndApp, NULL, TRUE);

    return TRUE;
}

void MakeMenuOptions()
{
	traceLog(  _T(  "MakeMenuOptions: Not finished"  )  );
}

__declspec(dllexport) void ChooseDevices(AV_capStuff  &  gcap,IMoniker *pmVideo, IMoniker *pmAudio)
{
#define VERSIZE 40
#define DESCSIZE 80

    int versize = VERSIZE;
    int descsize = DESCSIZE;
    WCHAR wachVer[VERSIZE]={0}, wachDesc[DESCSIZE]={0};
    TCHAR tachStatus[VERSIZE + DESCSIZE + 5]={0};


    // they chose a new device. rebuild the graphs
    if(gcap.pmVideo != pmVideo || gcap.pmAudio != pmAudio)
    {
        if(pmVideo)
        {
            pmVideo->AddRef();
        }
        if(pmAudio)
        {
            pmAudio->AddRef();
        }

        IMonRelease(gcap.pmVideo);
        IMonRelease(gcap.pmAudio);
        gcap.pmVideo = pmVideo;
        gcap.pmAudio = pmAudio;

        if(gcap.fPreviewing)
            StopPreview(gcap);
        if(gcap.fCaptureGraphBuilt || gcap.fPreviewGraphBuilt)
            TearDownGraph(gcap);

        FreeCapFilters(gcap);
        InitCapFilters(gcap);

        if(gcap.fWantPreview)   // were we previewing?
        {
            BuildPreviewGraph(gcap);
            StartPreview(gcap);
        }

        MakeMenuOptions();      // the UI choices change per device
    }

#if  10
    // Set the check marks for the devices menu.
	if  (  IsWindow(  gcap.ghwndApp  )  )  
	{

	BOOL  bChecked;
    int i;
    for(i = 0; i < NUMELMS(gcap.rgpmVideoMenu); i++)
    {
        if(gcap.rgpmVideoMenu[i] == NULL)
            break;

		bChecked  =  FALSE;
		if  (  gcap.pmVideo  &&  S_OK == gcap.rgpmVideoMenu[i]->IsEqual(gcap.pmVideo)  )  bChecked  =  TRUE;
        CheckMenuItem(GetMenu(gcap.ghwndApp),
            MENU_VDEVICE0 + i,
			bChecked ? MF_CHECKED : MF_UNCHECKED);
    }

    for(i = 0; i < NUMELMS(gcap.rgpmAudioMenu); i++)
    {
        if(gcap.rgpmAudioMenu[i] == NULL)
            break;

		bChecked  =  FALSE;
		if  (  gcap.pmAudio  &&  S_OK == gcap.rgpmAudioMenu[i]->IsEqual(gcap.pmAudio)  )  bChecked  =  TRUE;
        CheckMenuItem(GetMenu(gcap.ghwndApp), MENU_ADEVICE0 + i,
			bChecked ? MF_CHECKED : MF_UNCHECKED);
    }

	}
#endif

    // Put the video driver name in the status bar - if the filter supports
    // IAMVideoCompression::GetInfo, that's the best way to get the name and
    // the version.  Otherwise use the name we got from device enumeration
    // as a fallback.
    if(gcap.pVC)
    {
        HRESULT hr = gcap.pVC->GetInfo(wachVer, &versize, wachDesc, &descsize,
                                       NULL, NULL, NULL, NULL);
        if(hr == S_OK)
        {
            // It's possible that the call succeeded without actually filling
            // in information for description and version.  If these strings
            // are empty, just display the device's friendly name.
            if(wcslen(wachDesc) && wcslen(wachVer))
            {
                hr = StringCchPrintf(tachStatus, VERSIZE + DESCSIZE + 5, TEXT("%s - %s\0"), wachDesc, wachVer);
                statusUpdateStatus(ghwndStatus, tachStatus);
                return;
            }
        }
    }

    // Since the GetInfo method failed (or the interface did not exist),
    // display the device's friendly name.
    statusUpdateStatus(ghwndStatus, gcap.wachFriendlyName);
}

__declspec(dllexport) void ChooseDevices(AV_capStuff  &  gcap,TCHAR *szVideo, TCHAR *szAudio)
{
    WCHAR wszVideo[1024],  wszAudio[1024];

    StringCchCopyN(wszVideo, NUMELMS(wszVideo), szVideo, NUMELMS(wszVideo)-1);
    StringCchCopyN(wszAudio, NUMELMS(wszAudio), szAudio, NUMELMS(wszAudio)-1);
    wszVideo[1023] = wszAudio[1023] = 0;    // Null-terminate

    IBindCtx *lpBC=0;
    IMoniker *pmVideo = 0, *pmAudio = 0;

    HRESULT hr = CreateBindCtx(0, &lpBC);
    if(SUCCEEDED(hr))
    {
        DWORD dwEaten;
        hr = MkParseDisplayName(lpBC, wszVideo, &dwEaten, &pmVideo);
        hr = MkParseDisplayName(lpBC, wszAudio, &dwEaten, &pmAudio);

        lpBC->Release();
    }

    // Handle the case where the video capture device used for the previous session
    // is not available now.
    BOOL bFound = FALSE;

    if(pmVideo != NULL)
    {
        for(int i = 0; i < NUMELMS(gcap.rgpmVideoMenu); i++)
        {
            if(gcap.rgpmVideoMenu[i] != NULL &&
               S_OK == gcap.rgpmVideoMenu[i]->IsEqual(pmVideo))
            {
                bFound = TRUE;
                break;
            }
        }
    }

    if(!bFound)
    {
        if(gcap.iNumVCapDevices > 0)
        {
            IMonRelease(pmVideo);
            //  ASSERT(gcap.rgpmVideoMenu[0] != NULL);
            pmVideo = gcap.rgpmVideoMenu[0];
            pmVideo->AddRef();
        }
        else
            goto CleanUp;
    }

    ChooseDevices(gcap,pmVideo, pmAudio);

CleanUp:
    IMonRelease(pmVideo);
    IMonRelease(pmAudio);
}


///////////////////////

 __declspec(dllexport)  int   cfgCaptureFilter(  void  *  pAvCapStuff,  HWND  hwndParent  )
{
	int							iErr	=	-1;
	HRESULT						hr;

	AV_capStuff  &  gcap  =  *(  AV_capStuff  *  )pAvCapStuff;
	if  (  !gcap.pVCap  )  return  -1;
	
	HWND hwndOwner  =  NULL;
#if  0	//  2012/05/14
	hwndOwner  =  gcap.ghwndApp;
#endif
	hwndOwner  =  hwndParent;


{
                ISpecifyPropertyPages *pSpec;
                CAUUID cauuid;

                hr = gcap.pVCap->QueryInterface(IID_ISpecifyPropertyPages,
                    (void **)&pSpec);
                if(hr == S_OK)
                {
                    hr = pSpec->GetPages(&cauuid);

                    hr = OleCreatePropertyFrame(hwndOwner, 30, 30, NULL, 1,
                        (IUnknown **)&gcap.pVCap, cauuid.cElems,
                        (GUID *)cauuid.pElems, 0, 0, NULL);

                    CoTaskMemFree(cauuid.pElems);
                    pSpec->Release();
                }
            }

	iErr  =  0;
	return  iErr;
}



 __declspec(dllexport)  int   cfgCapturePin(  void  *  pAvCapStuff,  HWND  hwndParent  )
{

#ifdef  __WINCE__
		return  -1;
#else
	int							iErr	=	-1;
    HRESULT						hr;

	AV_capStuff  &  gcap  =  *(  AV_capStuff  *  )pAvCapStuff;
	if  (  !gcap.pBuilder  )  return  -1;


	{

                // You can change this pin's output format in these dialogs.
                // If the capture pin is already connected to somebody who's
                // fussy about the connection type, that may prevent using
                // this dialog(!) because the filter it's connected to might not
                // allow reconnecting to a new format. (EG: you switch from RGB
                // to some compressed type, and need to pull in a decoder)
                // I need to tear down the graph downstream of the
                // capture filter before bringing up these dialogs.
                // In any case, the graph must be STOPPED when calling them.
                if(gcap.fWantPreview)
                    StopPreview(gcap);  // make sure graph is stopped

                // The capture pin that we are trying to set the format on is connected if
                // one of these variable is set to TRUE. The pin should be disconnected for
                // the dialog to work properly.
                if(gcap.fCaptureGraphBuilt || gcap.fPreviewGraphBuilt)
                {
                    TearDownGraph(gcap);    // graph could prevent dialog working
                }

                IAMStreamConfig *pSC;
                hr = gcap.pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                    &MEDIATYPE_Interleaved, gcap.pVCap,
                    IID_IAMStreamConfig, (void **)&pSC);

                if(hr != NOERROR)
                    hr = gcap.pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                        &MEDIATYPE_Video, gcap.pVCap,
                        IID_IAMStreamConfig, (void **)&pSC);

                ISpecifyPropertyPages *pSpec;
                CAUUID cauuid;

                hr = pSC->QueryInterface(IID_ISpecifyPropertyPages,
                    (void **)&pSpec);

                if(hr == S_OK)
                {
                    hr = pSpec->GetPages(&cauuid);
                    hr = OleCreatePropertyFrame(hwndParent, 30, 30, NULL, 1,
                        (IUnknown **)&pSC, cauuid.cElems,
                        (GUID *)cauuid.pElems, 0, 0, NULL);

                    // !!! What if changing output formats couldn't reconnect
                    // and the graph is broken?  Shouldn't be possible...

                    if(gcap.pVSC)
                    {
                        AM_MEDIA_TYPE *pmt;
                        // get format being used NOW
                        hr = gcap.pVSC->GetFormat(&pmt);

                        // DV capture does not use a VIDEOINFOHEADER
                        if(hr == NOERROR)
                        {
                            if(pmt->formattype == FORMAT_VideoInfo)
                            {
                                // resize our window to the new capture size
                                ResizeWindow_amCap(hwndParent,  HEADER(pmt->pbFormat)->biWidth,
                                    abs(HEADER(pmt->pbFormat)->biHeight));
                            }
                            DeleteMediaType(pmt);
                        }
                    }

                    CoTaskMemFree(cauuid.pElems);
                    pSpec->Release();
                }

                pSC->Release();
                if(gcap.fWantPreview)
                {
                    BuildPreviewGraph(gcap);
                    StartPreview(gcap);
                }
            }

	iErr  =  0;
	return  iErr;
#endif
}


  __declspec(dllexport)  int   cfgCrossBar(  void  *  pAvCapStuff,  HWND  hwndParent  )
{
	int							iErr	=	-1;
    HRESULT						hr;

	AV_capStuff  &  gcap  =  *(  AV_capStuff  *  )pAvCapStuff;
	if  (  !gcap.pBuilder  )  return  -1;

	  {
                IAMCrossbar *pX;

                hr = gcap.pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                    &MEDIATYPE_Interleaved, gcap.pVCap,
                    IID_IAMCrossbar, (void **)&pX);
                if(hr != NOERROR)
                    hr = gcap.pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,
                        &MEDIATYPE_Video, gcap.pVCap,
                        IID_IAMCrossbar, (void **)&pX);

				if  (  hr  ==  S_OK  )  {
					ISpecifyPropertyPages *pSpec;
					CAUUID cauuid;

					hr = pX->QueryInterface(IID_ISpecifyPropertyPages,
						(void **)&pSpec);
					if(hr == S_OK)
					{
	                    hr = pSpec->GetPages(&cauuid);

		                hr = OleCreatePropertyFrame(hwndParent, 30, 30, NULL, 1,
			                (IUnknown **)&pX, cauuid.cElems,
				            (GUID *)cauuid.pElems, 0, 0, NULL);

		                CoTaskMemFree(cauuid.pElems);
			            pSpec->Release();
		            }
			        pX->Release();
				}
            
	  }

	  iErr  =  0;
	  return  iErr;
}
