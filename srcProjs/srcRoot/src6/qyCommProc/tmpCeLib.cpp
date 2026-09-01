
#include	"stdafx.h"

#include	"qyPrecomp.h"
#include	<stdlib.h>
#include	<winsock2.h>
#include	<windows.h>
#include	<stdio.h>
#include	<string.h>
#include	<lmcons.h>
#include	<tchar.h>
#include	<time.h>
#include	"qyCommon.h"
#include	"qyCommCommon.h"
#include	"qyWmComm.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qyTCharCommProc.h"

#include	"tmpCeLib.h"

 //  2006/12/19, 增加此文件是因为在qwm中使用了动态装载技术，使某些函数和一般使用有区别
 //  在这里重新用一般的函数来调用，以方便在管理中心等程序中使用

#ifdef  __WINCE__

#ifndef  __TEST__
		 int	errno	=	0;
#endif



#endif

 BOOL myGetComputerName(  LPTSTR lpBuffer,  LPDWORD lpnSize  )
{
#ifdef  __WINCE__
		char	name[256];
		int		len;
		if  (  gethostname(  name,  mycountof(  name  )  )  )  return  FALSE;
		if  (  !myStr2TChar(  name,  lpBuffer,  *lpnSize  )  )  return  FALSE;
		len  =  lstrlen(  lpBuffer  );
		if  (  len  ==  *lpnSize  )  return  FALSE;
		*lpnSize  =  len;
		return  TRUE;
#else
	return  GetComputerName(  lpBuffer,  lpnSize  );
#endif
}

DWORD WINAPI myGetFullPathName(  LPCTSTR lpFileName,  DWORD nBufferLength,  LPTSTR lpBuffer,  LPTSTR* lpFilePart  )
{
	#ifdef  __WINCE__
	        if  (  !lpFileName  ||  !lpBuffer  ||  !lpFilePart  )  return  0;  
			safeTcsnCpy(  lpFileName,  lpBuffer,  nBufferLength  );
			*lpFilePart  =  _tcsrchr(  lpBuffer,  _T(  '\\'  )  );
			if  (  *lpFilePart  )  (  *lpFilePart  )  ++  ;
			return  lstrlen(  lpBuffer  );
	#else
			return  GetFullPathName(  lpFileName,  nBufferLength,  lpBuffer,  lpFilePart  );
	#endif	
}


 BOOL WINAPI myGetVolumeInformation(  LPCTSTR lpRootPathName,  LPTSTR lpVolumeNameBuffer,  DWORD nVolumeNameSize,  LPDWORD lpVolumeSerialNumber,  LPDWORD lpMaximumComponentLength,  LPDWORD lpFileSystemFlags,  LPTSTR lpFileSystemNameBuffer,  DWORD nFileSystemNameSize  )
{
	#ifdef  __WINCE__
			traceLogA(  "myGetVolumeInformation not finished."  );
			return  0;
	#else
			return  GetVolumeInformation(  lpRootPathName,  lpVolumeNameBuffer,  nVolumeNameSize,  lpVolumeSerialNumber,  lpMaximumComponentLength,  lpFileSystemFlags,  lpFileSystemNameBuffer,  nFileSystemNameSize  );
	#endif	
}


 BOOL WINAPI myOpenProcessToken (  HANDLE ProcessHandle,  DWORD DesiredAccess,  PHANDLE TokenHandle  )
{
	#ifdef  __WINCE__
			traceLogA(  "myOpenProcessToken not finished."  );
			return  0;
	#else
			return  OpenProcessToken(  ProcessHandle,  DesiredAccess,  TokenHandle  );
	#endif	
}

 BOOL WINAPI myGetTokenInformation(  HANDLE TokenHandle,  TOKEN_INFORMATION_CLASS TokenInformationClass,  LPVOID TokenInformation,  DWORD TokenInformationLength,  PDWORD ReturnLength  )
{
	#ifdef  __WINCE__
			traceLogA(  "GetTokenInformation not finished."  );
			return  0;
	#else
			return  GetTokenInformation(  TokenHandle,  TokenInformationClass,  TokenInformation,  TokenInformationLength,  ReturnLength  );
	#endif	
}


 BOOL WINAPI myLookupAccountSid(  LPCTSTR lpSystemName,  PSID lpSid,  LPTSTR lpName,  LPDWORD cchName,  LPTSTR lpReferencedDomainName,  LPDWORD cchReferencedDomainName,  PSID_NAME_USE peUse  )
{
	#ifdef  __WINCE__
			traceLogA(  "GetTokenInformation not finished."  );
			return  0;
	#else
			return  LookupAccountSid(  lpSystemName,  lpSid,  lpName,  cchName,  lpReferencedDomainName,  cchReferencedDomainName,  peUse  );
	#endif	
}

 BOOL myEnumChildWindows(  HWND hWndParent,    WNDENUMPROC lpEnumFunc,    LPARAM lParam)
{
	#ifdef  __WINCE__
		for  (  HWND  hWndChild  =  ::GetWindow(  hWndParent,  GW_CHILD  );  hWndChild  !=  0;  hWndChild  =  ::GetWindow(  hWndChild,  GW_HWNDNEXT  )  )  {
			 //  TCHAR		text[256]  =  _T(  ""  );
			 //  ::GetWindowText(  hWndChild,  text,  256  );
			 //  TRACE1(  "CHILD  Window: %s\n",  text  );
			lpEnumFunc(  hWndChild,  lParam  );
		}
		return  TRUE;
	#else
		return  EnumChildWindows(  hWndParent,  lpEnumFunc,  lParam  );
	#endif
}



 ///

  

 BOOL  mySetWindowPlacement(  HWND hWnd,  WINDOWPLACEMENT *lpwndpl  )
{
#ifdef  __WINCE__
		return  FALSE;
#else
		return  SetWindowPlacement(  hWnd,  lpwndpl  );
#endif
}

 BOOL myGetWindowPlacement(  HWND hWnd,  WINDOWPLACEMENT *lpwndpl  )
{
#ifdef  __WINCE__
		return  FALSE;
#else
		return  GetWindowPlacement(  hWnd,  lpwndpl  );
#endif
}

 BOOL myGetKeyboardState(  PBYTE lpKeyState  )
{
#ifdef  __WINCE__
		return  FALSE;
#else
		return  GetKeyboardState(  lpKeyState  );
#endif
}

 int  myToAscii(  UINT uVirtKey,  UINT uScanCode,  PBYTE lpKeyState,  LPWORD lpChar,  UINT uFlags  )
{
#ifdef  __WINCE__
		return  -1;
#else
		return  ToAscii(  uVirtKey,  uScanCode,  lpKeyState,  lpChar,  uFlags  );
#endif
}





