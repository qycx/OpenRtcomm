
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
//#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

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
#pragma include_alias( "dxtrans.h", "myqedit.h" )
#define __IDxtCompositor_INTERFACE_DEFINED__
#define __IDxtAlphaSetter_INTERFACE_DEFINED__
#define __IDxtJpeg_INTERFACE_DEFINED__
#define __IDxtKey_INTERFACE_DEFINED__

	//  #include	<Qedit.h>
	#include	"myQedit.h"
#endif
#include	<Mediaobj.h>
#include	<Dmo.h>


#include	<dvdmedia.h>


#include	"qmcDmo.h"
#include	"qmcVideoCapture.h"
#ifndef  __WINCE__
	#include	"qmcVideoCapture_dx.h"
#endif

#include	"qyDynLib.h"

#include	"mywmcodecconst.h"
#include	"mywmcodeciface.h"
#include	"myfourcc.h"

//#include	"qyAvRecord.h"
//#include	"qyAvRecord_dx.h"

#include	"qySampleGrabberPublic.h"


// Get the encoder complexity values for the codec.
 int  getComplexitySettings(  const  GUID  *  gMyClsid,  DWORD  fourcc,  DWORD* pLive, DWORD* pOffline, DWORD* pMax)
{
	int			iErr	=	-1;
    HRESULT		hr		=	S_OK;
    
    //  CComPtr<IMediaObject>	pDMO		=	NULL;
	IMediaObject			*	pDMO		=	NULL;
    //  CComPtr<IWMCodecProps>	pCodecProps		=	NULL;
	IWMCodecProps			*	pCodecProps	=	NULL;

    DWORD cbValue = sizeof(DWORD);
    WMT_PROP_DATATYPE dataType;
    

    // Create a video encoder DMO.
    hr = CoCreateInstance(  *gMyClsid,
                          NULL, 
                          CLSCTX_INPROC_SERVER, 
                          IID_IMediaObject, 
                          (void**)&pDMO);
	if  (  FAILED(  hr  )  )  goto  errLabel;

    // Get the codec properties interface.
    hr = pDMO->QueryInterface(IID_IWMCodecProps, (void**)&pCodecProps);
	if  (  FAILED(  hr  )  )  goto  errLabel;
    
    // Get the setting for live encoding.
    hr = pCodecProps->GetCodecProp(  fourcc, 
                                   g_wszWMVCComplexityExLive, 
                                   &dataType, 
                                   (BYTE*)pLive, 
                                   &cbValue);
	if  (  FAILED(  hr  )  )  goto  errLabel;

    // Get the setting for offline encoding.
    hr = pCodecProps->GetCodecProp(fourcc, 
                                   g_wszWMVCComplexityExOffline, 
                                   &dataType, 
                                   (BYTE*)pOffline, 
                                   &cbValue);
	if  (  FAILED(  hr  )  )  goto  errLabel;
    
    // Get the maximum complexity setting.
    hr = pCodecProps->GetCodecProp(fourcc, 
                                   g_wszWMVCComplexityExMax, 
                                   &dataType, 
                                   (BYTE*)pMax, 
                                   &cbValue);
	if  (  FAILED(  hr  )  )  goto  errLabel;
    
	iErr  =  0;

errLabel:
	
	MACRO_safeRelease(  pDMO  );
	MACRO_safeRelease(  pCodecProps  );


    return  iErr;

}

