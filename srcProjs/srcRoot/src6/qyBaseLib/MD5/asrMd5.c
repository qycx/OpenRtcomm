

#ifndef MD
#define MD 5
#endif

#include	<stdio.h>
#include	<time.h>
#include	<string.h>

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#include	<windows.h>
#include	"qyCommon.h"
#include	"global.h"

#if MD == 5
#include "md5.h"
#endif


#if MD == 5
#define MD_CTX MD5_CTX
#define MDInit MD5Init
#define MDUpdate MD5Update
#define MDFinal MD5Final
#endif


 // Digests a file and prints the result.
 //
 // digest is a buffer of 16 bytes.

 BOOL  bQyGetFileMd5(  char  *  fileName,  char  *  digest,  unsigned  int  *  pLen  )
{
	BOOL			bRet	=	FALSE;
	FILE	*		file	=	NULL;
	MD_CTX			context;
	int				len;
	unsigned  char	buffer[1024];
	unsigned  char	tmpBuf[1024];
	int				i;

	if  (  *pLen  <  CONST_qyMd5Len  )  goto  errLabel;

	if  (  (  file  =  fopen(  fileName,  "rb"  )  )  ==  NULL  )  {
		traceLogA(  "%s can't be opened\n",  fileName  );
		goto  errLabel;
	}
	MDInit(  &context  );
	while  (  (  len  =  fread(  buffer,  1,  1024,  file  )  )  )
   		   MDUpdate(  &context,  buffer,  len  );
 	MDFinal(  digest,  &context  );
	fclose (  file);  file  =  NULL;
	sprintf(  tmpBuf,  "MD%d (%s) = ",  MD,  fileName  );
	for  (  i  =  0;  i  <  16;  i  ++  )
		 sprintf(  tmpBuf,  "%s%02x",  tmpBuf,  (  unsigned  char )digest[i]  );
	sprintf(  tmpBuf,  "%s%s",  tmpBuf,  "\n"  );
	// debugLog( "asrMdFile():[%s], digest is [%s]", fileName, tmpBuf );
	
	bRet	=	TRUE;

errLabel:

	if  (  file  )  fclose(  file  );

	if  (  bRet  )  {
		if  (  *pLen  >  CONST_qyMd5Len  )  {
			digest[CONST_qyMd5Len]  =  0;
			*pLen  =  CONST_qyMd5Len;
		}
	}

	return  bRet;

}


