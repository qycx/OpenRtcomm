

#ifndef  __TMPCELIB_H__
#define  __TMPCELIB_H__		//  {



BOOL myGetComputerName(  LPTSTR lpBuffer,  LPDWORD lpnSize  );
DWORD WINAPI myGetFullPathName(  LPCTSTR lpFileName,  DWORD nBufferLength,  LPTSTR lpBuffer,  LPTSTR* lpFilePart  );
BOOL WINAPI myGetVolumeInformation(  LPCTSTR lpRootPathName,  LPTSTR lpVolumeNameBuffer,  DWORD nVolumeNameSize,  LPDWORD lpVolumeSerialNumber,  LPDWORD lpMaximumComponentLength,  LPDWORD lpFileSystemFlags,  LPTSTR lpFileSystemNameBuffer,  DWORD nFileSystemNameSize  );
BOOL WINAPI myOpenProcessToken (  HANDLE ProcessHandle,  DWORD DesiredAccess,  PHANDLE TokenHandle  );
BOOL WINAPI myGetTokenInformation(  HANDLE TokenHandle,  TOKEN_INFORMATION_CLASS TokenInformationClass,  LPVOID TokenInformation,  DWORD TokenInformationLength,  PDWORD ReturnLength  );
BOOL WINAPI myLookupAccountSid(  LPCTSTR lpSystemName,  PSID lpSid,  LPTSTR lpName,  LPDWORD cchName,  LPTSTR lpReferencedDomainName,  LPDWORD cchReferencedDomainName,  PSID_NAME_USE peUse  );
BOOL myEnumChildWindows(  HWND hWndParent,    WNDENUMPROC lpEnumFunc,    LPARAM lParam);


#ifdef  __WINCE__  //  {

#ifndef  __TEST__
extern  "C"  void * bsearch( 
   const void *key,
   const void *base,
   size_t num,
   size_t width,
   int ( __cdecl *compare ) ( const void *, const void *) 
);

 BOOL DrawDibEnd(  HDRAWDIB hdd  );
 BOOL DrawDibClose(  HDRAWDIB hdd  );
 HDRAWDIB DrawDibOpen(VOID);
 BOOL DrawDibBegin(  HDRAWDIB hdd,  HDC hdc,  int dxDest,  int dyDest,  LPBITMAPINFOHEADER lpbi,  int dxSrc, int dySrc, UINT wFlags );
 BOOL DrawDibDraw(  HDRAWDIB hdd,  HDC hdc,  int xDst, int yDst,  int dxDst,  int dyDst,  LPBITMAPINFOHEADER lpbi, LPVOID lpBits, int xSrc, int ySrc, int dxSrc, int dySrc, UINT wFlags  );

#endif

#ifndef  DDBLT_WAIT
	#define DDBLT_WAIT                              0x01000000l
#endif

#ifndef  LPCGUID
	typedef const GUID *LPCGUID;
#endif

#if  0
	#ifndef  DDSCAPS_OFFSCREENPLAIN
		#define DDSCAPS_OFFSCREENPLAIN                  0x00000040l
	#endif
#endif

#ifndef  __TEST__		//  {

#ifndef  WINDOWPLACEMENT
typedef struct tagWINDOWPLACEMENT {
    UINT  length;
    UINT  flags;
    UINT  showCmd;
    POINT ptMinPosition;
    POINT ptMaxPosition;
    RECT  rcNormalPosition;
#ifdef _MAC
    RECT  rcDevice;
#endif
} WINDOWPLACEMENT;
#endif


#ifndef  MINMAXINFO
typedef struct tagMINMAXINFO {
    POINT ptReserved;
    POINT ptMaxSize;
    POINT ptMaxPosition;
    POINT ptMinTrackSize;
    POINT ptMaxTrackSize;
} MINMAXINFO, *PMINMAXINFO, *LPMINMAXINFO;
#endif



#ifndef  HDROP
	DECLARE_HANDLE(HDROP);
#endif

#endif	//  }

	#define ICMODE_DECOMPRESS	2
	#define ICMODE_FASTDECOMPRESS   3
	#define ICMODE_FASTCOMPRESS     5

#define VIDCF_QUALITY        0x0001  // supports quality

#define ICM_USER          (DRV_USER+0x0000)

#define ICM_COMPRESS_GET_FORMAT     (ICM_USER+4)    // get compress format or size
#define ICM_COMPRESS_GET_SIZE       (ICM_USER+5)    // get output size
#define ICM_COMPRESS_QUERY          (ICM_USER+6)    // query support for compress
#define ICM_COMPRESS_BEGIN          (ICM_USER+7)    // begin a series of compress calls.
#define ICM_COMPRESS_END            (ICM_USER+9)    // end of a series of compress calls.


#define ICM_DECOMPRESS_GET_FORMAT   (ICM_USER+10)   // get decompress format or size
#define ICM_DECOMPRESS_QUERY        (ICM_USER+11)   // query support for dempress
#define ICM_DECOMPRESS_BEGIN        (ICM_USER+12)   // start a series of decompress calls
#define ICM_DECOMPRESS              (ICM_USER+13)   // decompress a frame
#define ICM_DECOMPRESS_END          (ICM_USER+14)   // end a series of decompress calls

#define ICERR_OK                0L

	#define ICM_RESERVED      ICM_RESERVED_LOW
#define ICM_RESERVED_LOW  (DRV_USER+0x1000)

	#define ICM_GETDEFAULTQUALITY       (ICM_RESERVED+30)   // get the default value for quality

#ifndef  __TEST__
#ifndef  ICINFO
typedef struct {
    DWORD   dwSize;                 // sizeof(ICINFO)
    DWORD   fccType;                // compressor type     'vidc' 'audc'
    DWORD   fccHandler;             // compressor sub-type 'rle ' 'jpeg' 'pcm '
    DWORD   dwFlags;                // flags LOWORD is type specific
    DWORD   dwVersion;              // version of the driver
    DWORD   dwVersionICM;           // version of the ICM used
    //
    // under Win32, the driver always returns UNICODE strings.
    //
    WCHAR   szName[16];             // short name
    WCHAR   szDescription[128];     // long name
    WCHAR   szDriver[128];          // driver that contains compressor
}   ICINFO;
#endif

LRESULT ICClose(  HIC hic  );
HIC ICOpen(  DWORD fccType,  DWORD fccHandler, UINT wMode  );
HIC ICLocate(  DWORD fccType,  DWORD fccHandler, LPBITMAPINFOHEADER lpbiIn, LPBITMAPINFOHEADER lpbiOut, WORD wFlags  );
LRESULT ICGetInfo( HIC hic, ICINFO * lpicinfo, DWORD cb );
DWORD ICDecompress(  HIC hic, DWORD dwFlags, LPBITMAPINFOHEADER lpbiFormat, LPVOID lpData, LPBITMAPINFOHEADER lpbi, LPVOID lpBits  );
DWORD ICCompress(  HIC hic, DWORD dwFlags, LPBITMAPINFOHEADER lpbiOutput, LPVOID lpData, LPBITMAPINFOHEADER lpbiInput, LPVOID lpBits, LPDWORD lpckid, LPDWORD lpdwFlags, LONG lFrameNum, DWORD dwFrameSize, DWORD dwQuality, LPBITMAPINFOHEADER lpbiPrev, LPVOID lpPrev  );

LRESULT ICSendMessage(  HIC hic, UINT wMsg, DWORD dw1, DWORD dw2  );
#define ICDecompressGetFormat(hic, lpbiInput, lpbiOutput) \
    ((LONG) ICSendMessage(hic, ICM_DECOMPRESS_GET_FORMAT, (DWORD_PTR)(LPVOID)(lpbiInput), (DWORD_PTR)(LPVOID)(lpbiOutput)))
#define ICDecompressQuery(hic, lpbiInput, lpbiOutput) \
    ICSendMessage(hic, ICM_DECOMPRESS_QUERY, (DWORD_PTR)(LPVOID)(lpbiInput), (DWORD_PTR)(LPVOID)(lpbiOutput))
#define ICDecompressBegin(hic, lpbiInput, lpbiOutput) \
    ICSendMessage(hic, ICM_DECOMPRESS_BEGIN, (DWORD_PTR)(LPVOID)(lpbiInput), (DWORD_PTR)(LPVOID)(lpbiOutput))
#define ICDecompressEnd(hic) \
    ICSendMessage(hic, ICM_DECOMPRESS_END, 0, 0)
#define ICDecompressGetFormat(hic, lpbiInput, lpbiOutput) \
    ((LONG) ICSendMessage(hic, ICM_DECOMPRESS_GET_FORMAT, (DWORD_PTR)(LPVOID)(lpbiInput), (DWORD_PTR)(LPVOID)(lpbiOutput)))
#define ICDecompressQuery(hic, lpbiInput, lpbiOutput) \
    ICSendMessage(hic, ICM_DECOMPRESS_QUERY, (DWORD_PTR)(LPVOID)(lpbiInput), (DWORD_PTR)(LPVOID)(lpbiOutput))
#define ICDecompressBegin(hic, lpbiInput, lpbiOutput) \
    ICSendMessage(hic, ICM_DECOMPRESS_BEGIN, (DWORD_PTR)(LPVOID)(lpbiInput), (DWORD_PTR)(LPVOID)(lpbiOutput))
#define ICDecompressEnd(hic) \
    ICSendMessage(hic, ICM_DECOMPRESS_END, 0, 0)

#define ICCompressGetFormat(hic, lpbiInput, lpbiOutput) \
    ICSendMessage(hic, ICM_COMPRESS_GET_FORMAT, (DWORD_PTR)(LPVOID)(lpbiInput), (DWORD_PTR)(LPVOID)(lpbiOutput))
#define ICCompressQuery(hic, lpbiInput, lpbiOutput) \
    ICSendMessage(hic, ICM_COMPRESS_QUERY, (DWORD_PTR)(LPVOID)(lpbiInput), (DWORD_PTR)(LPVOID)(lpbiOutput))
#define ICCompressBegin(hic, lpbiInput, lpbiOutput) \
    ICSendMessage(hic, ICM_COMPRESS_BEGIN, (DWORD_PTR)(LPVOID)(lpbiInput), (DWORD_PTR)(LPVOID)(lpbiOutput))
#define ICCompressEnd(hic) \
    ICSendMessage(hic, ICM_COMPRESS_END, 0, 0)

static DWORD dwICValue;

#define ICGetDefaultQuality(hic) \
    (ICSendMessage(hic, ICM_GETDEFAULTQUALITY, (DWORD_PTR)(LPVOID)&dwICValue, sizeof(DWORD)), dwICValue)
#define ICCompressGetSize(hic, lpbiInput, lpbiOutput) \
    (DWORD) ICSendMessage(hic, ICM_COMPRESS_GET_SIZE, (DWORD_PTR)(LPVOID)(lpbiInput), (DWORD_PTR)(LPVOID)(lpbiOutput))

typedef struct tagCapDriverCaps {
    UINT        wDeviceIndex;               // Driver index in system.ini
    BOOL        fHasOverlay;                // Can device overlay?
    BOOL        fHasDlgVideoSource;         // Has Video source dlg?
    BOOL        fHasDlgVideoFormat;         // Has Format dlg?
    BOOL        fHasDlgVideoDisplay;        // Has External out dlg?
    BOOL        fCaptureInitialized;        // Driver ready to capture?
    BOOL        fDriverSuppliesPalettes;    // Can driver make palettes?

// following always NULL on Win32.
    HANDLE      hVideoIn;                   // Driver In channel
    HANDLE      hVideoOut;                  // Driver Out channel
    HANDLE      hVideoExtIn;                // Driver Ext In channel
    HANDLE      hVideoExtOut;               // Driver Ext Out channel
} CAPDRIVERCAPS, *PCAPDRIVERCAPS, FAR *LPCAPDRIVERCAPS;

#define WM_CAP_START                    WM_USER

#define WM_CAP_SET_CALLBACK_VIDEOSTREAM (WM_CAP_START+  6)
#define WM_CAP_SET_USER_DATA		(WM_CAP_START+  9)
#define WM_CAP_DRIVER_CONNECT           (WM_CAP_START+  10)
#define WM_CAP_DRIVER_DISCONNECT        (WM_CAP_START+  11)

#define WM_CAP_DRIVER_GET_CAPS          (WM_CAP_START+  14)

#define WM_CAP_SEQUENCE_NOFILE          (WM_CAP_START+  63)
#define WM_CAP_STOP                     (WM_CAP_START+  68)
#define WM_CAP_ABORT                    (WM_CAP_START+  69)


#define AVICapSM(hwnd,m,w,l) ( (::IsWindow(hwnd)) ? ::SendMessage(hwnd,m,w,l) : 0)
//
#define capCaptureSequenceNoFile(hwnd)             ((BOOL)AVICapSM(hwnd, WM_CAP_SEQUENCE_NOFILE, (WPARAM)0, (LPARAM)0L))
#define capCaptureStop(hwnd)                       ((BOOL)AVICapSM(hwnd, WM_CAP_STOP, (WPARAM)0, (LPARAM)0L))
#define capCaptureAbort(hwnd)                      ((BOOL)AVICapSM(hwnd, WM_CAP_ABORT, (WPARAM)0, (LPARAM)0L))
#define capSetUserData(hwnd, lUser)        ((BOOL)AVICapSM(hwnd, WM_CAP_SET_USER_DATA, 0, (LPARAM)lUser))
#define capSetCallbackOnVideoStream(hwnd, fpProc)  ((BOOL)AVICapSM(hwnd, WM_CAP_SET_CALLBACK_VIDEOSTREAM, 0, (LPARAM)(LPVOID)(fpProc)))
#define capDriverConnect(hwnd, i)                  ((BOOL)AVICapSM(hwnd, WM_CAP_DRIVER_CONNECT, (WPARAM)(i), 0L))
#define capDriverGetCaps(hwnd, s, wSize)           ((BOOL)AVICapSM(hwnd, WM_CAP_DRIVER_GET_CAPS, (WPARAM)(wSize), (LPARAM)(LPVOID)(LPCAPDRIVERCAPS)(s)))
#define capDriverDisconnect(hwnd)                  ((BOOL)AVICapSM(hwnd, WM_CAP_DRIVER_DISCONNECT, (WPARAM)0, 0L))

HWND capCreateCaptureWindow(  LPCTSTR lpszWindowName,  DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWnd, int nID  );
BOOL capGetDriverDescription( WORD wDriverIndex,  LPTSTR lpszName,  INT cbName, LPTSTR lpszVer, INT cbVer  );

#define SM_SWAPBUTTON           23

//

SHORT VkKeyScan(  TCHAR ch  );

#ifndef  HELPINFO
typedef struct tagHELPINFO      /* Structure pointed to by lParam of WM_HELP */
{
    UINT    cbSize;             /* Size in bytes of this struct  */
    int     iContextType;       /* Either HELPINFO_WINDOW or HELPINFO_MENUITEM */
    int     iCtrlId;            /* Control Id or a Menu item Id. */
    HANDLE  hItemHandle;        /* hWnd of control or hMenu.     */
    DWORD_PTR dwContextId;      /* Context Id associated with this item */
    POINT   MousePos;           /* Mouse Position in screen co-ordinates */
}  HELPINFO, FAR *LPHELPINFO;
#endif

#endif  //  }


#ifndef _SHFOLDER_H_
#define CSIDL_FLAG_CREATE               0x8000        // combine with CSIDL_ value to force folder creation in SHGetFolderPath()
#endif // _SHFOLDER_H_

#ifndef  TPM_RIGHTBUTTON
	#define TPM_RIGHTBUTTON 0x0002L
#endif

#ifndef  WM_NCLBUTTONDOWN
	#define WM_NCLBUTTONDOWN                0x00A1
#endif

#ifndef  SS_TYPEMASK
	#define SS_TYPEMASK         0x0000001FL
#endif

#ifndef  __TEST__
EXTERN_GUID( IID_IMediaBuffer, 0x59eff8b9, 0x938c, 0x4a26, 0x82, 0xf2, 0x95, 0xcb, 0x84, 0xcd, 0xc8, 0x37);
//  MIDL_INTERFACE("59eff8b9-938c-4a26-82f2-95cb84cdc837")
    
EXTERN_GUID( IID_IMediaObject, 0xd8ad0f58, 0x5494, 0x4102, 0x97, 0xc5, 0xec, 0x79, 0x8e, 0x59, 0xbc, 0xf4);
//  MIDL_INTERFACE("d8ad0f58-5494-4102-97c5-ec798e59bcf4")
#endif

#ifndef  WAVR_FORMAT_WMAUDIO2
	#define  WAVE_FORMAT_WMAUDIO2                   0x0161 /* Microsoft Corporation */
#endif

#ifdef  __TEST__		//

#define KEYEVENTF_SILENT      0x0004

#endif  //  }



#endif  //  }



//
BOOL  mySetWindowPlacement(  HWND hWnd,  WINDOWPLACEMENT *lpwndpl  );
BOOL  myGetWindowPlacement(  HWND hWnd,  WINDOWPLACEMENT *lpwndpl  );
BOOL myGetKeyboardState(          PBYTE lpKeyState  );
int  myToAscii(  UINT uVirtKey,  UINT uScanCode,  PBYTE lpKeyState,  LPWORD lpChar,  UINT uFlags  );


#ifdef  __WINCE__
#ifndef  __TEST__
extern  int	errno;
#endif
#endif

#endif  //  }

