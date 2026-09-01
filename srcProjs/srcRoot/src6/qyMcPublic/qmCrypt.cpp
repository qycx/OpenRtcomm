
#include	"stdafx.h"

#ifndef  __WINCE__
	#include	<vfw.h>
#else
	#ifdef  __TEST__
			#include	<vfw.h>
	#endif
	#include	<mmreg.h>
	#include	<MSAcm.h>
#endif

#include	<Wincrypt.h>
#include	<WinSock2.h>

#include	<tchar.h>

#include	"qmCommon.h"
#include	"qmCrypt.h"

//
#define  __USE_aes__

//
TCHAR  *  get_DEFAULT_cspProvider()
{
	TCHAR  *  tmp_DEFAULT_cspProvider	=(TCHAR*)MS_ENHANCED_PROV;

#ifdef  __USE_aes__
		tmp_DEFAULT_cspProvider  =  (TCHAR*)MS_ENH_RSA_AES_PROV;	//
#endif

	return  tmp_DEFAULT_cspProvider;
}

DWORD  get_provType()
{
	DWORD  dwProvType  =  PROV_RSA_FULL;

#ifdef  __USE_aes__
		dwProvType  =  PROV_RSA_AES;
#endif

	return  dwProvType;

}

unsigned  int  get_algId()
{
	ALG_ID algId=CALG_RC4;

#ifdef  __USE_aes__
	algId = CALG_AES_128;
#endif

	return  algId;
}



//
 BOOL  bGetExportedKey(  HCRYPTKEY hKey, DWORD dwBlobType,  LPBYTE *ppbKeyBlob, LPDWORD pdwBlobLen  )
{
    DWORD dwBlobLength;
    *ppbKeyBlob = NULL;
    *pdwBlobLen = 0;

    // Export the public key. Here the public key is exported to a 
    // PUBLICKEYBLOB. This BLOB can be written to a file and
    // sent to another user.

    if(CryptExportKey(   
        hKey,    
        NULL,    
        dwBlobType,
        0,    
        NULL, 
        &dwBlobLength)) 
    {
        printf("Size of the BLOB for the public key determined. \n");
    }
    else
    {
        printf("Error computing BLOB length.\n");
        return FALSE;
    }

    // Allocate memory for the pbKeyBlob.
    if(*ppbKeyBlob = (LPBYTE)mymalloc(dwBlobLength)) 
    {
        printf("Memory has been allocated for the BLOB. \n");
    }
    else
    {
        printf("Out of memory. \n");
        return FALSE;
    }

    // Do the actual exporting into the key BLOB.
    if(CryptExportKey(   
        hKey, 
        NULL,    
        dwBlobType,    
        0,    
        *ppbKeyBlob,    
        &dwBlobLength))
    {
        printf("Contents have been written to the BLOB. \n");
        *pdwBlobLen = dwBlobLength;
    }
    else
    {
        printf("Error exporting key.\n");
        free(*ppbKeyBlob);
        *ppbKeyBlob = NULL;

        return FALSE;
    }

    return TRUE;
}


