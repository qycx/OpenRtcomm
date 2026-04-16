

#include	"stdafx.h"

#include	<tchar.h>

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



QY_DMITEM  CONST_mediaSubtypeTable[] =  { 
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_RGB1,			(TCHAR*)L"RGB Monochrome",   },
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_RGB4,			(TCHAR*)L"RGB VGA",          },
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_RGB8,			(TCHAR*)L"RGB 8",            },
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_RGB565,			(TCHAR*)L"RGB 565 (16 bit)", },
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_RGB555,			(TCHAR*)L"RGB 555 (16 bit)", },
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_RGB24,			(TCHAR*)L"RGB 24",           },
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_RGB32,			(TCHAR*)L"RGB 32",			},
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_ARGB32,			(TCHAR*)L"ARGB 32",			},
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_Overlay,		(TCHAR*)L"Overlay",          },
	//
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_I420,		(TCHAR*)L"I420",				},
	//  {	0,	(  TCHAR  *  )&MEDIASUBTYPE_IYUV,			(TCHAR*)L"IYUV",				},
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_YV12,			(TCHAR*)L"YV12",				},
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_NV11,			(TCHAR*)L"NV11",				},
	//  {	0,	(  TCHAR  *  )&MEDIASUBTYPE_NV12,			(TCHAR*)L"NV12",				},
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_YUY2,			(TCHAR*)L"YUY2",				},
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_YVYU,			(TCHAR*)L"YVYU",				},
	//	
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_UYVY,			(TCHAR*)L"UYVY",				},
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_HDYC,			(TCHAR*)L"HDYC",				},	//  2012/01/03
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_v210,			(TCHAR*)L"v210",				},	//  2012/02/23
	//
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_VIDEOIMAGE,	(TCHAR*)L"VIDEOIMAGE",		},
	//
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_MJPG,			(TCHAR*)L"MJPG",			},
	//
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_MSS1,		(TCHAR*)L"MSS1",			},
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_MSS2,		(TCHAR*)L"MSS2",			},
	//
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_WMV1,		(TCHAR*)L"WMV1",			},
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_WMV2,		(TCHAR*)L"WMV2",			},
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_WMV3,		(TCHAR*)L"WMV3",			},
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_WMVA,		(TCHAR*)L"WMVA",			},
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_WMVP,		(TCHAR*)L"WMVP",			},
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_WMVR,			(TCHAR*)L"WMVR",			},
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_WVC1,			(TCHAR*)L"WVC1",			},
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_WVP2,			(TCHAR*)L"WVP2",			},

	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_Line21_VBIRawData,	(TCHAR*)L"Line21_VBIRawData",	},
	//
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_PCM,			(TCHAR*)L"PCM",				},

	//
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_WAVE,			(TCHAR*)L"WAVE",			},
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_MSA1,		(TCHAR*)L"MSA1",			},
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_WMA9,		(TCHAR*)L"WMA9",			},
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_WMA9Pro,		(TCHAR*)L"WMA9Pro",			},
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_WMA9Lossless,(TCHAR*)L"WMA9Lossless",	},
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_WMA9Voice,	(TCHAR*)L"WMA9Voice",		},

	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_ADPCM,		(TCHAR*)L"ADPCM",			},
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_GSM610,		(TCHAR*)L"GSM610",			},
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_MP3,			(TCHAR*)L"MP3",				},


	{	-1, NULL,	},
};

 TCHAR  *  getMediaTypeName(  GUID  &  clsid  )
 {
	 if  (  clsid  ==  MEDIATYPE_Video  )  return  (TCHAR*)_T(  "Video"  );
	 if  (  clsid  ==  MEDIATYPE_Audio  )  return  (TCHAR*)_T(  "Audio"  );
	 return  (TCHAR*)_T(  "Unknown mediaType"  );
 }

 TCHAR  *  getMediaSubtypeName(  GUID  &  clsid  )
{
	QY_DMITEM	*	pItem;
	for  (  pItem  =  CONST_mediaSubtypeTable;  pItem->type  !=  -1;  pItem  ++  )  {
		 if  (  *(  GUID  *  )pItem->des  ==  clsid  )  return const_cast<TCHAR*>(pItem->pData);
	}
	return  (TCHAR*)_T(  ""  );		//  _T(  "Unknown subtype"  );
}

 int  getMediaSubtypeByName(  LPCTSTR  name,  GUID  *  pclsid  )
{
	QY_DMITEM  *  pItem;
	for  (  pItem  =  CONST_mediaSubtypeTable;  pItem->type  !=  -1;  pItem  ++  )  {
		if  (  !_tcsicmp(  name,  pItem->pData  )  )  {
			*pclsid  =  *(  GUID  *  )pItem->des;
			return  0;
		}
	}
	return  -1;
}

 TCHAR  *  getFormatTypeName(  GUID  &  clsid  )
 {
	 if  (  clsid  ==  FORMAT_VideoInfo  )  return  (TCHAR*)_T(  "Format_video"  );
	 if  (  clsid  ==  FORMAT_VideoInfo2  )  return  (TCHAR*)_T(  "Format_video2"  );
	 if  (  clsid  ==  FORMAT_WaveFormatEx  )  return  (TCHAR*)_T(  "Format_wave"  );
	 if  (  clsid  ==  GUID_NULL  )  return  (TCHAR*)_T(  "Format_null"  );
	 return  (TCHAR*)_T(  "Unknown format"  );
 }


