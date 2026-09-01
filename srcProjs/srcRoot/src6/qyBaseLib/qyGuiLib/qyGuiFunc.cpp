

#include	"qyPrecomp.h"
#include	<stdio.h>
#include	<stdlib.h>

#include    <WinSock2.h>
#include	<windows.h>
#include	<shlwapi.h>
#include	"qyCommon.h"
#include	"qyGuiCommon.h"

#include	<tchar.h>



 extern "C" HRESULT qyGetComCtlVersion(LPDWORD pdwMajor, LPDWORD pdwMinor)
{
	 HINSTANCE  hComCtl;
	 TCHAR		svLibName[MAX_PATH  +  1];

	 if  (  IsBadWritePtr(  pdwMajor,  sizeof(  DWORD  )  )  || 
		 IsBadWritePtr(  pdwMinor,  sizeof(  DWORD  )  )  )
	 {
   		 return E_INVALIDARG;
	 }

	 //load the DLL
	 if  (  qyFullLibName(  _T(  "comctl32.dll"  ),  svLibName,  mycountof(  svLibName  )  )  )  goto  errLabel;
	 hComCtl  =  LoadLibrary(  svLibName  );
	 if  (  hComCtl  )  {
   		 HRESULT           hr = S_OK;
   
		 DLLGETVERSIONPROC pDllGetVersion;
   		 /*
   			You must get this function explicitly because earlier versions of the DLL 
		 don't implement this function. That makes the lack of implementation of the 
		 function a version marker in itself.
   		 */
#ifdef  __WINCE__
   		 pDllGetVersion = (DLLGETVERSIONPROC)GetProcAddress(hComCtl, _T("DllGetVersion"));
#else
   		 pDllGetVersion = (DLLGETVERSIONPROC)GetProcAddress(hComCtl, ("DllGetVersion"));
#endif
      	 if  (  pDllGetVersion  )
      	 {
      		 DLLVERSIONINFO    dvi;
      
      		 ZeroMemory(&dvi, sizeof(dvi));
      		 dvi.cbSize = sizeof(dvi);
   
      		 hr = (*pDllGetVersion)(&dvi);
            if(SUCCEEDED(hr))
      		{
      			*pdwMajor = dvi.dwMajorVersion;
      			*pdwMinor = dvi.dwMinorVersion;
      			}
      		else
      		{
      			hr = E_FAIL;
      		}   
      	 }
   		 else
    	 {
    	 /*
    		If GetProcAddress failed, then the DLL is a version previous to the one 
		shipped with IE 3.x.
        */
      		 *pdwMajor = 4;
      		 *pdwMinor = 0;
      	 }
   
   
		 FreeLibrary(hComCtl);

   		 return hr;
   
	 }
errLabel:
	 return E_FAIL;
}


