
#include	"qyPrecomp.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<ctype.h>
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#include	<windows.h>
#ifndef  __WINCE__
	#include	<lm.h>
	#include	<lmshare.h>
#endif
#include	"qyCommon.h"

/*
 extern  "C"  int  getNetLogonLocalPath(  char  *  localPath  )
{
	int				iErr		=  -1;
	PSHARE_INFO_502 BufPtr		=  NULL;
	BOOL			bInfoGot	=  FALSE;
	NET_API_STATUS	res;
	LPTSTR			lpszServer  =  NULL,  lpszShare  =  "NetLogon";
	char			buf[2048];
	WCHAR			wShareBuf[256];
	char			inBuf[32]		=  "NetLogon";
	int				iRet			=  999;

	iRet = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, inBuf, strlen( inBuf ), wShareBuf, sizeof( wShareBuf ) );
	if ( !iRet ) goto errLabel;
	wShareBuf[iRet] = 0;

	// Call the NetShareGetInfo function, specifying level 502.
	if ( ( res = NetShareGetInfo( lpszServer, ( char * )( unsigned short * )wShareBuf, 502, ( LPBYTE *) &BufPtr ) ) != ERROR_SUCCESS ) 
		goto errLabel;
	bInfoGot = TRUE;

	// Print the retrieved data.
	// sprintf(buf, "%S\t%S\t%u\n", BufPtr->shi502_netname, BufPtr->shi502_path, BufPtr->shi502_current_uses);
	sprintf( buf, "%S", BufPtr->shi502_path );
	// Validate the value of the 
	//  shi502_security_descriptor member.
	if ( IsValidSecurityDescriptor( BufPtr->shi502_security_descriptor ) )
		printf("It has a valid Security Descriptor.\n");
	else
		printf("It does not have a valid Security Descriptor.\n");

	strcpy( localPath, buf );

	iErr = 0;	

errLabel:
	
	if ( bInfoGot ) {
		// Free the allocated memory.
		NetApiBufferFree(BufPtr);
	}
	
	return iErr;

}
*/


 //  ÊÇ·ñÓò¿ØÖÆÆ÷
 extern  "C"  BOOL  bDomainCtrl(  )
{
#ifdef  __WINCE__
		return  FALSE;
#else
	BOOL				bRet	=	FALSE;
 	NET_API_STATUS		nas;
	PSERVER_INFO_101	si101	=	NULL;         
	DWORD				Type;         
		
	nas  =  NetServerGetInfo(  NULL,  101,  (  LPBYTE  *  )&si101  );         
	if  (  nas  !=  NERR_Success  )  goto  errLabel;
	Type  =  si101->sv101_type;     
			
    if  (  Type  &  SV_TYPE_DOMAIN_CTRL  )  bRet  =  TRUE;

errLabel:

	if  (  nas  ==  NERR_Success  )  NetApiBufferFree(  si101  );
	return  bRet;
#endif
}