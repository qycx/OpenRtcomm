

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <lm.h>
#include <lmshare.h>
#include "commonDefs1.h"


extern "C" unsigned char *trimRight( unsigned char *str )
{
	int len;

	if ( !str || !strlen( ( const char * )str ) ) return NULL;
	len = strlen( ( const char * )str );
	while ( len ) {
		if ( !isspace( str[len - 1] ) ) break;
		str[len - 1] = '\0';
		len --;
	}
	if ( !len ) return NULL;

	return str;

}

 extern "C" char *asrGetFullPath( char *path, char *file, char *buf, unsigned int bufSize )
{

	if ( !trimRight( ( unsigned char * )path ) ) return NULL;
	if ( path[strlen( path ) -1] == '\\' ) {
		if ( strlen( path ) + strlen( file ) >= bufSize ) return NULL;
		sprintf( buf, "%s%s", path, file );
		}
	else {
		if ( strlen( path ) + 1 + strlen( file ) >= bufSize ) return NULL;
		sprintf( buf, "%s\\%s", path, file );
	}

	return buf;
	
}


 extern "C" BOOL bAsrGetSystemVersion( int *piPlatformId )
{
	OSVERSIONINFOEX osvi;
	BOOL bOsVersionInfoEx;
	int iPlatformId = PLATFORM_UNKNOWN;

	// Try calling GetVersionEx using the OSVERSIONINFOEX structure.
	// If that fails, try using the OSVERSIONINFO structure.

	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	if( !(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)) ) {
		// If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO.
		osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
		if (! GetVersionEx ( (OSVERSIONINFO *) &osvi) ) 
			return FALSE;
	}

	switch (osvi.dwPlatformId) {
		case VER_PLATFORM_WIN32_NT:
			// Test for the product.
			if ( osvi.dwMajorVersion <= 4 ) {
				printf("Microsoft Windows NT ");
				iPlatformId = PLATFORM_NT;
			}
			if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0 ) {
				printf ("Microsoft Windows 2000 ");
				iPlatformId = PLATFORM_WIN2K;
			}
			if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1 ) {
				printf ("Microsoft Windows XP ");
				iPlatformId = PLATFORM_WINXP;
			}
			// Test for product type.
			//
			// if( bOsVersionInfoEx ) {
			//	if ( osvi.wProductType == VER_NT_WORKSTATION ) {
			//		if( osvi.wSuiteMask & VER_SUITE_PERSONAL )
			//			printf ( "Personal " );
			//		else
			//			printf ( "Professional " );
			//		}
			//	else if ( osvi.wProductType == VER_NT_SERVER ) {
			//		if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
			//			printf ( "DataCenter Server " );
			//		else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
			//			printf ( "Advanced Server " );
			//		else
			//			printf ( "Server " );
			//	}
			//	}
			//else {
			//	HKEY hKey;
			//	char szProductType[80];
			//	DWORD dwBufLen;

			//	RegOpenKeyEx( HKEY_LOCAL_MACHINE,
			//		"SYSTEM\\CurrentControlSet\\Control\\ProductOptions",
			//		0, KEY_QUERY_VALUE, &hKey );
			//	RegQueryValueEx( hKey, "ProductType", NULL, NULL,
			//		(LPBYTE) szProductType, &dwBufLen);
			//	RegCloseKey( hKey );
			//	if ( lstrcmpi( "WINNT", szProductType) == 0 )
			//		printf( "Professional " );
			//	if ( lstrcmpi( "LANMANNT", szProductType) == 0 )
			//		printf( "Server " );
			//	if ( lstrcmpi( "SERVERNT", szProductType) == 0 )
			//		printf( "Advanced Server " );
			//}
			//
			// Display version, service pack (if any), and build number.
			if ( osvi.dwMajorVersion <= 4 ) {
				printf ("version %d.%d %s (Build %d)\n",
					osvi.dwMajorVersion,
					osvi.dwMinorVersion,
					osvi.szCSDVersion,
					osvi.dwBuildNumber & 0xFFFF);
				}
			else { 
				printf ("%s (Build %d)\n",
					osvi.szCSDVersion,
					osvi.dwBuildNumber & 0xFFFF);
			}
			break;
		case VER_PLATFORM_WIN32_WINDOWS:
			if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 0) {
				printf ("Microsoft Windows 95 ");
				iPlatformId = PLATFORM_WIN95;
				if ( osvi.szCSDVersion[1] == 'C' || osvi.szCSDVersion[1] == 'B' )
					printf("OSR2 " );
			} 
			if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 10) {
				printf ("Microsoft Windows 98 ");
				iPlatformId = PLATFORM_WIN98;
				if ( osvi.szCSDVersion[1] == 'A' )
					printf("SE " );
			} 
			if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 90) {
				printf ("Microsoft Windows Me ");
				iPlatformId = PLATFORM_WINME;
			} 
			break;
		case VER_PLATFORM_WIN32s: 
			printf ("Microsoft Win32s ");
			iPlatformId = PLATFORM_WIN32;
			break;
		
	}
	*piPlatformId = iPlatformId;

   	return TRUE; 

}


 extern "C" int asrGetRegCfg( char *rootKey, char *cfgName, char *cfgVal, int size )
{
	int iRet = -1;
	BOOL bKeyOpen = FALSE;
	HKEY hKey;
	int lRet = 0;
	long cb;
	DWORD type;
			
	lRet = RegOpenKey( HKEY_LOCAL_MACHINE, rootKey, &hKey );
	if ( lRet != ERROR_SUCCESS ) goto errLabel;
	bKeyOpen = TRUE;
	
	cb = size;
	if ( RegQueryValueEx( hKey, cfgName, 0, &type, ( unsigned char * )cfgVal, 
			( unsigned long * )&cb ) != ERROR_SUCCESS ) 
	{
		goto errLabel;
	}
	cfgVal[cb - 1] = 0;
	
	iRet = 0;
	
errLabel:

	if ( bKeyOpen ) RegCloseKey( hKey );

	return iRet;

}


