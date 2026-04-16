
/* This module is designed for programs that shall be linked 
 * without	LIBC.LIB
 *			LIBCMT.LIB 
 *			MSVCRT.LIB 
 */

#include	"qyCommon\\asrPrecomp.h"

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>


#include	<windows.h>

#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<stdarg.h>
#ifndef WIN32
	//  #include	<unistd.h>
#endif
#include	<ctype.h>


#include	<tchar.h>
//  #include	<process.h>

#include	"commonDefs.h"
#include	"qyCommon\\commonFunc.h"
#include	"qyCommon\\commonFunc1.h"
#include	"qyCommon.h"



 


 extern  "C"  int  qyIsSpace(  int  c  )
{
	if  (  (  (  unsigned  char  )c  >=  0x09  &&  (  unsigned  char  )c  <=  0x0d  )  ||  (  unsigned  char  )c  ==  0x20  )
		return  1;
	return  0;
}


 extern  "C"  int  qyIsAlpha(  int  c  )
{
	 if  (  (  (  (  unsigned  char  )c   >=  'A'  )  &&  (  (  unsigned  char  )c  <=  'Z'  )  )  ||  (  (  (  unsigned  char  )c   >=  'a'  )  &&  (  (  unsigned  char  )c  <=  'z'  )  )  )
		 return  1;
	 return  0;
}


 extern  "C"  int  qyIsDigit(  int  c  )
{
	return  (  (  c  >=  '0'  )  &&  (  c  <=  '9'  )  );
}


 extern  "C"  int  qyIsXdigit(  int  c  )
{
	 if  (  (  (  (  unsigned  char  )c  >=  'A'  )  &&  (  (  unsigned  char  )c  <=  'F'  )  )  
		 ||  (  (  unsigned  char  )c  >=  'a'  &&  (  (  unsigned  char  )c  <=  'f'  )  )
			||  (  (  unsigned  char  )c  >=  '0'  &&  (  (  unsigned  char  )c  <=  '9'  )  )  )
	 {
		 return  1;
	 }
	 return  0;
}



#if  0
 extern  "C"  BOOL  bQyGetSystemVersion(  int  *  piPlatformId,  TCHAR  *  pProductStr,  unsigned  int  size,  unsigned  char  *  pucbIsWinNt  )
{
#ifndef  OSVERSIONINFOEX
	OSVERSIONINFO		osvi;
#else
	OSVERSIONINFOEX		osvi;
#endif
	BOOL				bOsVersionInfoEx;
	int					iPlatformId				=	PLATFORM_UNKNOWN;
	TCHAR				productStr[512  +  1]	=  _T(  ""  );

	traceLogA(  "注：bQyGetSystemVersion: 这里强制调用了高版本的OSVERSIONINFOEX结构，在使用高版本的Studio后，请取消这种强制。"  );

	// Try calling GetVersionEx using the OSVERSIONINFOEX structure.
	// If that fails, try using the OSVERSIONINFO structure.
	ZeroMemory(  &osvi,  sizeof(  osvi  )  );
	osvi.dwOSVersionInfoSize  =  sizeof(  osvi  );

	if  (  !(  bOsVersionInfoEx  =  GetVersionEx(  (  OSVERSIONINFO  *  )&osvi  )  )  )  {
		// If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO.
		osvi.dwOSVersionInfoSize  =  sizeof(  OSVERSIONINFO  );
		if  (  !GetVersionEx(  (  OSVERSIONINFO  *  )&osvi  )  )  return  FALSE;
	}

	switch  (  osvi.dwPlatformId  )  {
			case  VER_PLATFORM_WIN32_NT:
				  // Test for the product.
				  if  (  osvi.dwMajorVersion  <=  4  )  {
					  lstrcpyn(  productStr  +  lstrlen(  productStr  ),  _T(  "Microsoft Windows NT "  ),  mycountof(  productStr  )  -  lstrlen(  productStr  )  );
					  iPlatformId  =  PLATFORM_NT;
				  }
				  if  (  osvi.dwMajorVersion  ==  5  &&  osvi.dwMinorVersion  ==  0  )  {
					  lstrcpyn(  productStr  +  lstrlen(  productStr  ),  _T(  "Microsoft Windows 2000 "  ),  mycountof(  productStr  )  -  lstrlen(  productStr  )  );
					  iPlatformId  =  PLATFORM_WIN2K;
				  }
				  if  (  osvi.dwMajorVersion  ==  5  &&  osvi.dwMinorVersion  ==  1  )  {
					  lstrcpyn(  productStr  +  lstrlen(  productStr  ),  _T(  "Microsoft Windows XP "  ),  mycountof(  productStr  )  -  lstrlen(  productStr  )  );
					  iPlatformId  =  PLATFORM_WINXP;
				  }
				  //  Test for product type.
				  //
			#ifdef  OSVERSIONINFOEX
				  if  (  bOsVersionInfoEx  )  {
					  if  (  osvi.wProductType  ==  VER_NT_WORKSTATION  )  {
						  if  (  osvi.wSuiteMask  &  VER_SUITE_PERSONAL  )  lstrcpyn(  productStr  +  lstrlen(  productStr  ),  _T(  "Personal "  ),  mycountof(  productStr  )  -  lstrlen(  productStr  )  );
						  else  lstrcpyn(  productStr  +  lstrlen(  productStr  ),  _T(  "Professional "  ),  mycountof(  productStr  )  -  lstrlen(  productStr  )  );
						  }
					  else  if  (  osvi.wProductType  ==  VER_NT_SERVER  )  {
							    if  (  osvi.wSuiteMask  &  VER_SUITE_DATACENTER  )
									lstrcpyn(  productStr  +  lstrlen(  productStr  ),  _T(  "DataCenter Server "  ),  mycountof(  productStr  )  -  lstrlen(  productStr  )  );
								else  if  (  osvi.wSuiteMask  &  VER_SUITE_ENTERPRISE  )
										 lstrcpyn(  productStr  +  lstrlen(  productStr  ),  _T(  "Advanced Server "  ),  mycountof(  productStr  )  -  lstrlen(  productStr  )  );
								else
									lstrcpyn(  productStr  +  lstrlen(  productStr  ),  _T(  "Server "  ),  mycountof(  productStr  )  -  lstrlen(  productStr  )  );
					  }				
				
				  	  }
				  else  {
					    HKEY	hKey;
						TCHAR	szProductType[80];
						DWORD  dwBufLen;

						RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  _T(  "SYSTEM\\CurrentControlSet\\Control\\ProductOptions"  ),  0,  KEY_QUERY_VALUE,  &hKey  );
						RegQueryValueEx(  hKey, _T(  "ProductType"  ), NULL, NULL,  (LPBYTE) szProductType, &dwBufLen  );
						RegCloseKey( hKey );
						if  (  lstrcmpi(  _T(  "WINNT"  ),  szProductType  )  ==  0  )  lstrcpyn(  productStr  +  lstrlen(  productStr  ),  _T(  "Professional "  ),  mycountof(  productStr  )  -  lstrlen(  productStr  )  );
						if  (  lstrcmpi(  _T(  "LANMANNT"  ),  szProductType  )  ==  0  )  lstrcpyn(  productStr  +  lstrlen(  productStr  ),  _T(  "Server "  ),  mycountof(  productStr  )  -  lstrlen(  productStr  )  );
						if  (  lstrcmpi(  _T(  "SERVERNT"  ),  szProductType  )  ==  0  )  lstrcpyn(  productStr  +  lstrlen(  productStr  ),  _T(  "Advanced Server "  ),  mycountof(  productStr  )  -  lstrlen(  productStr  )  );
				  }
			#endif
			
				  //
				  // Display version, service pack (if any), and build number.
				  if  (  osvi.dwMajorVersion  <=  4  )  {
					  TCHAR				buf[256];

					  wsprintf(  buf,  _T(  "version %d.%d"  ),  osvi.dwMajorVersion,  osvi.dwMinorVersion  );
					  lstrcpyn(  productStr  +  lstrlen(  productStr  ),  buf,  mycountof(  productStr  )  -  lstrlen(  productStr  )  );
					  lstrcpyn(  productStr  +  lstrlen(  productStr  ),  _T(  " "  ),  mycountof(  productStr  )  -  lstrlen(  productStr  )  );
					  lstrcpyn(  productStr  +  lstrlen(  productStr  ),  osvi.szCSDVersion,  mycountof(  productStr  )  -  lstrlen(  productStr  )  );
					  lstrcpyn(  productStr  +  lstrlen(  productStr  ),  _T(  " "  ),  mycountof(  productStr  )  -  lstrlen(  productStr  )  );
					  wsprintf(  buf,  _T(  "(Build %d)"  ),  osvi.dwBuildNumber  &  0xFFFF  );
					  lstrcpyn(  productStr  +  lstrlen(  productStr  ),  buf,  mycountof(  productStr  )  -  lstrlen(  productStr  )  );
					  }
				  else  {
					    TCHAR  buf[256];

						lstrcpyn(  productStr  +  lstrlen(  productStr  ),  osvi.szCSDVersion,  mycountof(  productStr  )  -  lstrlen(  productStr  )  );
						lstrcpyn(  productStr  +  lstrlen(  productStr  ),  _T(  " "  ),  mycountof(  productStr  )  -  lstrlen(  productStr  )  );
						wsprintf(  buf,  _T(  "(Build %d)"  ),  osvi.dwBuildNumber  &  0xFFFF  );
						lstrcpyn(  productStr  +  lstrlen(  productStr  ),  buf,  mycountof(  productStr  )  -  lstrlen(  productStr  )  );
				  }
				  break;
			case  VER_PLATFORM_WIN32_WINDOWS:
				  if  (  osvi.dwMajorVersion  ==  4  &&  osvi.dwMinorVersion  ==  0  )  {
					  lstrcpyn(  productStr  +  lstrlen(  productStr  ),  _T(  "Microsoft Windows 95 "  ),  mycountof(  productStr  )  -  lstrlen(  productStr  )  );
					  iPlatformId  =  PLATFORM_WIN95;
					  if  (  osvi.szCSDVersion[1]  ==  'C'  ||  osvi.szCSDVersion[1]  ==  'B'  )
						  lstrcpyn(  productStr  +  lstrlen(  productStr  ),  _T(  "OSR2 "  ),  mycountof(  productStr  )  -  lstrlen(  productStr  )  );
				  } 
				  if  (  osvi.dwMajorVersion  ==  4  &&  osvi.dwMinorVersion  ==  10  )  {
					  lstrcpyn(  productStr  +  lstrlen(  productStr  ),  _T(  "Microsoft Windows 98 "  ),  mycountof(  productStr  )  -  lstrlen(  productStr  )  );
					  iPlatformId  =  PLATFORM_WIN98;
					  if  (  osvi.szCSDVersion[1]  ==  'A'  )  lstrcpyn(  productStr  +  lstrlen(  productStr  ),  _T(  "SE "  ),  mycountof(  productStr  )  -  lstrlen(  productStr  )  );
				  } 
				  if  (  osvi.dwMajorVersion  ==  4  &&  osvi.dwMinorVersion  ==  90  )  {
					  lstrcpyn(  productStr  +  lstrlen(  productStr  ),  _T(  "Microsoft Windows Me "  ),  mycountof(  productStr  )  -  lstrlen(  productStr  )  );
					  iPlatformId = PLATFORM_WINME;
				  } 
				  break;
			case  VER_PLATFORM_WIN32s: 
				  lstrcpyn(  productStr  +  lstrlen(  productStr  ),  _T(  "Microsoft Win32s "  ),  mycountof(  productStr  )  -  lstrlen(  productStr  )  );
				  iPlatformId  =  PLATFORM_WIN32;
				  break;
	}


	if  (  piPlatformId  )  *piPlatformId  =  iPlatformId;
	//  if  (  pProductStr  &&  size  )  safeStrnCpy(  productStr,  pProductStr,  size  );
	if  (  pProductStr  &&  size  )  lstrcpyn(  pProductStr,  productStr,  size  );
	if  (  pucbIsWinNt  )  *pucbIsWinNt  =  (  osvi.dwPlatformId  ==  VER_PLATFORM_WIN32_NT  );

   	return  TRUE; 

}
#endif

 extern  "C"  BOOL  bQyGetSystemVersionEx(  int  *  piPlatformId,  TCHAR  *  pSystemBuf,  unsigned  int  uiSystemBufSize,  TCHAR  *  pServicePackBuf,  unsigned  int  uiServicePackBufSize,  unsigned  char  *  pucbIsWinNt  )
{
#ifndef  OSVERSIONINFOEX
	OSVERSIONINFO		osvi;
#else
	OSVERSIONINFOEX		osvi;
#endif
	BOOL				bOsVersionInfoEx;
	int					iPlatformId						=  CONST_qyPlatform_unknown;	//  PLATFORM_UNKNOWN;
	//  char			productStr[512];
	TCHAR				systemBuf[128  +  1]			=  _T(  ""  );
	TCHAR				servicePackBuf[128  +  1]		=  _T(  ""  );

	//  traceLogA(  "注：bQyGetSystemVersion: 这里强制调用了高版本的OSVERSIONINFOEX结构，在使用高版本的Studio后，请取消这种强制。"  );

	// Try calling GetVersionEx using the OSVERSIONINFOEX structure.
	// If that fails, try using the OSVERSIONINFO structure.
	ZeroMemory(  &osvi,  sizeof(  osvi  )  );
	osvi.dwOSVersionInfoSize  =  sizeof(  osvi  );

	if  (  !(  bOsVersionInfoEx  =  GetVersionEx(  (  OSVERSIONINFO  *  )&osvi  )  )  )  {
		// If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO.
		osvi.dwOSVersionInfoSize  =  sizeof(  OSVERSIONINFO  );
		if  (  !GetVersionEx(  (  OSVERSIONINFO  *  )&osvi  )  )  return  FALSE;
	}

	switch  (  osvi.dwPlatformId  )  {
			case  VER_PLATFORM_WIN32_NT:
				  // Test for the product.
				  if  (  osvi.dwMajorVersion  <=  4  )  {
					  lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "Microsoft Windows NT "  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
					  iPlatformId  =  PLATFORM_NT;
				  }
				  if  (  osvi.dwMajorVersion  ==  5  &&  osvi.dwMinorVersion  ==  0  )  {	//  5.0.2195
					  lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "Microsoft Windows 2000 "  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
					  iPlatformId  =  PLATFORM_WIN2K;
				  }
				  if  (  osvi.dwMajorVersion  ==  5  &&  osvi.dwMinorVersion  ==  1  )  {	//  5.1.2600
					  lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "Microsoft Windows XP "  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
					  iPlatformId  =  PLATFORM_WINXP;
				  }
				  if  (  osvi.dwMajorVersion  ==  5  &&  osvi.dwMinorVersion  ==  2  )  {	//  5.2.3790,  2004/05/14增加对2003的支持
					  lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "Microsoft Windows Server 2003 "  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
					  iPlatformId  =  CONST_qyPlatform_win2003;
				  }
				  if  (  osvi.dwMajorVersion  ==  6  &&  osvi.dwMinorVersion  ==  0  )  {	//  6.0,	2007/01/06
					  #ifndef  OSVERSIONINFOEX
							   lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "Microsoft Windows Vista "  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
							   iPlatformId  =  CONST_qyPlatform_winVista;
					  #else
							if  (  osvi.wProductType  ==  VER_NT_WORKSTATION  )  {				//			vista,  2009/11/06
								lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "Microsoft Windows Vista "  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
								iPlatformId  =  CONST_qyPlatform_winVista;
							  }
							else  {																//          2008,   2009/11/06
								  lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "Microsoft Windows 2008 "  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
								  iPlatformId  =  CONST_qyPlatform_win2008;				
							}
					  #endif
				  }
				  if  (  osvi.dwMajorVersion  ==  6  &&  osvi.dwMinorVersion  ==  1  )  {	//  6.1,    2009/11/06
					  #ifndef  OSVERSIONINFOEX
								lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "Microsoft Windows 7 "  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
								iPlatformId  = CONST_qyPlatform_win7;
					  #else					
							if  (  osvi.wProductType  ==  VER_NT_WORKSTATION  )  {						  
								lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "Microsoft Windows 7 "  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
								iPlatformId  = CONST_qyPlatform_win7;
							    }
							else  {																//          2008,   2009/11/06
								  lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "Microsoft Windows 2008 R2"  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
								  iPlatformId  =  CONST_qyPlatform_win2008R2;
							}
					  #endif
				  }

				  if  (  osvi.dwMajorVersion  ==  6  &&  osvi.dwMinorVersion  ==  2  )  {		//  6.2,  2012/12/20
					  #ifndef  OSVERSIONINFOEX 
								lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "Microsoft Windows 8"  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
								iPlatformId  =  CONST_qyPlatform_win8;					    
					  #else
							if  (  osvi.wProductType  ==  VER_NT_WORKSTATION  )  {
								lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "Microsoft Windows 8"  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
								iPlatformId  =  CONST_qyPlatform_win8;
							}
							else  {
								lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "Microsoft Windows 2012"  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
								iPlatformId  =  CONST_qyPlatform_win2012;
							}
					  #endif
				  }

				  //  Test for product type.
				  //
			  #ifdef  OSVERSIONINFOEX

				  if  (  bOsVersionInfoEx  )  {
					  if  (  osvi.wProductType  ==  VER_NT_WORKSTATION  )  {
						  if  (  osvi.wSuiteMask  &  VER_SUITE_PERSONAL  )  lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "Personal "  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
						  else  lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "Professional "  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
						  }
					  else  if  (  osvi.wProductType  ==  VER_NT_SERVER  )  {
							    if  (  osvi.wSuiteMask  &  VER_SUITE_DATACENTER  )
									lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "DataCenter Server "  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
								else  if  (  osvi.wSuiteMask  &  VER_SUITE_ENTERPRISE  )
										 lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "Advanced Server "  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
								else
									lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "Server "  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
					  }				
				
				  	  }
				  else  {
					    HKEY	hKey;
						TCHAR	szProductType[80];
						DWORD  dwBufLen;

						RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  _T(  "SYSTEM\\CurrentControlSet\\Control\\ProductOptions"  ),  0,  KEY_QUERY_VALUE,  &hKey  );
						RegQueryValueEx(  hKey, _T(  "ProductType"  ), NULL, NULL,  (LPBYTE) szProductType, &dwBufLen  );
						RegCloseKey( hKey );
						if  (  lstrcmpi(  _T(  "WINNT"  ),  szProductType  )  ==  0  )  lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "Professional "  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
						if  (  lstrcmpi(  _T(  "LANMANNT"  ),  szProductType  )  ==  0  )  lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "Server "  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
						if  (  lstrcmpi(  _T(  "SERVERNT"  ),  szProductType  )  ==  0  )  lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "Advanced Server "  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
				  }

			#endif
			
				  //
				  // Display version, service pack (if any), and build number.
				  if  (  osvi.dwMajorVersion  <=  4  )  {
					  TCHAR				buf[256];

					  wsprintf(  buf,  _T(  "version %d.%d"  ),  osvi.dwMajorVersion,  osvi.dwMinorVersion  );
					  lstrcpyn(  servicePackBuf  +  lstrlen(  servicePackBuf  ),  buf,  mycountof(  servicePackBuf  )  -  lstrlen(  servicePackBuf  )  );
					  lstrcpyn(  servicePackBuf  +  lstrlen(  servicePackBuf  ),  _T(  " "  ),  mycountof(  servicePackBuf  )  -  lstrlen(  servicePackBuf  )  );
					  lstrcpyn(  servicePackBuf  +  lstrlen(  servicePackBuf  ),  osvi.szCSDVersion,  mycountof(  servicePackBuf  )  -  lstrlen(  servicePackBuf  )  );
					  lstrcpyn(  servicePackBuf  +  lstrlen(  servicePackBuf  ),  _T(  " "  ),  mycountof(  servicePackBuf  )  -  lstrlen(  servicePackBuf  )  );
					  wsprintf(  buf,  _T(  "(Build %d)"  ),  osvi.dwBuildNumber  &  0xFFFF  );
					  lstrcpyn(  servicePackBuf  +  lstrlen(  servicePackBuf  ),  buf,  mycountof(  servicePackBuf  )  -  lstrlen(  servicePackBuf  )  );
					  }
				  else  {
					    TCHAR  buf[256];

						lstrcpyn(  servicePackBuf  +  lstrlen(  servicePackBuf  ),  osvi.szCSDVersion,  mycountof(  servicePackBuf  )  -  lstrlen(  servicePackBuf  )  );
						lstrcpyn(  servicePackBuf  +  lstrlen(  servicePackBuf  ),  _T(  " "  ),  mycountof(  servicePackBuf  )  -  lstrlen(  servicePackBuf  )  );
						wsprintf(  buf,  _T(  "(Build %d)"  ),  osvi.dwBuildNumber  &  0xFFFF  );
						lstrcpyn(  servicePackBuf  +  lstrlen(  servicePackBuf  ),  buf,  mycountof(  servicePackBuf  )  -  lstrlen(  servicePackBuf  )  );
				  }
				  break;
			case  VER_PLATFORM_WIN32_WINDOWS:
				  if  (  osvi.dwMajorVersion  ==  4  &&  osvi.dwMinorVersion  ==  0  )  {
					  lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "Microsoft Windows 95 "  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
					  iPlatformId  =  PLATFORM_WIN95;
					  if  (  osvi.szCSDVersion[1]  ==  'C'  ||  osvi.szCSDVersion[1]  ==  'B'  )
						  lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "OSR2 "  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
				  } 
				  if  (  osvi.dwMajorVersion  ==  4  &&  osvi.dwMinorVersion  ==  10  )  {
					  lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "Microsoft Windows 98 "  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
					  iPlatformId  =  PLATFORM_WIN98;
					  if  (  osvi.szCSDVersion[1]  ==  'A'  )  lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "SE "  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
				  } 
				  if  (  osvi.dwMajorVersion  ==  4  &&  osvi.dwMinorVersion  ==  90  )  {
					  lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "Microsoft Windows Me "  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
					  iPlatformId = PLATFORM_WINME;
				  } 
				  break;
			case  VER_PLATFORM_WIN32s: 
				  lstrcpyn(  systemBuf  +  lstrlen(  systemBuf  ),  _T(  "Microsoft Win32s "  ),  mycountof(  systemBuf  )  -  lstrlen(  systemBuf  )  );
				  iPlatformId  =  PLATFORM_WIN32;
				  break;
#ifdef  __WINCE__
			case  VER_PLATFORM_WIN32_CE:
				  _sntprintf(  systemBuf,  mycountof(  systemBuf  ),  _T(  "Microsoft Windows CE %d.%d"  ),  osvi.dwMajorVersion,  osvi.dwMinorVersion  );
				  iPlatformId  =  CONST_qyPlatform_winCe;
				  break;
#endif
	}


	if  (  piPlatformId  )  *piPlatformId  =  iPlatformId;
	//  if  (  pSystemBuf  &&  uiSystemBufSize  )  safeStrnCpy(  systemBuf,  pSystemBuf,  uiSystemBufSize  );
	if  (  pSystemBuf  &&  uiSystemBufSize  )  lstrcpyn(  pSystemBuf,  systemBuf,  uiSystemBufSize  );
	//  if  (  pServicePackBuf  &&  uiServicePackBufSize  )  safeStrnCpy(  servicePackBuf,  pServicePackBuf,  uiServicePackBufSize  );
	if  (  pServicePackBuf  &&  uiServicePackBufSize  )  lstrcpyn(  pServicePackBuf,  servicePackBuf,  uiServicePackBufSize  );
	if  (  pucbIsWinNt  )  *pucbIsWinNt  =  (  osvi.dwPlatformId  ==  VER_PLATFORM_WIN32_NT  );

   	return  TRUE; 

}


 extern  "C"  BOOL  isWinNt(  void  )
{
	OSVERSIONINFO  osvi;

	osvi.dwOSVersionInfoSize  =  sizeof(  OSVERSIONINFO  );
	
	if  (  GetVersionEx(  &osvi  )  ==  FALSE  )  {
		traceLogA(  "Unable to get version info,  GetOSVersion()"  );  return  FALSE;
	}

	return  osvi.dwPlatformId == VER_PLATFORM_WIN32_NT;

}


