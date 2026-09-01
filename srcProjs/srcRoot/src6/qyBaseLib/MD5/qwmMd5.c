
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


/* Digests a string and prints the result.
 */
 BOOL  bQyGetStrMd5(  char  *  string,  char  *  digest,  unsigned  int  *  pLen  )
{
  BOOL		bRet	=	FALSE;
  MD_CTX	context;
  //  unsigned char digest[16];
  unsigned int len = strlen (string);

  if  (  !string  ||  !string[0]  )  return  FALSE;
  if  (  !digest  ||  !pLen  ||  *pLen  <  CONST_qyMd5Len  )  return  FALSE;

  MDInit (&context);
  MDUpdate (&context, string, len);
  MDFinal (digest, &context);

  bRet  =  TRUE;

  if  (  bRet  )  {
		if  (  *pLen  >  CONST_qyMd5Len  )  {
			digest[CONST_qyMd5Len]  =  0;
			*pLen  =  CONST_qyMd5Len;
		}
  }

  return  bRet;

}

 BOOL  bQyGetStrMd5_x(  char  *  string,  char  *  digest,  unsigned  int  *  pLen  )
{
	//  BOOL		bRet							=	FALSE;
	char			md5Buf[CONST_qyMd5Len  +  1]	=	"";
	unsigned  int	len;

	if  (  !digest  ||  !pLen  )  return  FALSE;

	len  =  sizeof(  md5Buf  );
	if  (  !bQyGetStrMd5(  string,  md5Buf,  &len  )  )  return  FALSE;
	if  (  *pLen  <=  2  *  len  )  return  FALSE;
	qyBuf2X(  md5Buf,  len,  digest  );
	*pLen  =  2  *  len;
	digest[*pLen]  =  0;

	return  TRUE;
}



 // Digests a file and prints the result.
 //
 // digest is a buffer of 16 bytes.
 //  BOOL  bQwmGetFileMd5(  char  *  fileName,  char  *  digest,  unsigned  int  *  pLen  )
 BOOL  bQwmGetFileMd5(  LPCTSTR  fileName,  char  *  digest,  unsigned  int  *  pLen  )
{
	BOOL			bRet	=	FALSE;
	HANDLE			hFile	=	NULL;
	MD_CTX			context;
	int				len;
	unsigned  char	buffer[1024];
	unsigned  char	tmpBuf[1024];
	int				i;
	BOOL			bResult;
	unsigned  long  nBytesToRead;

	if  (  *pLen  <  CONST_qyMd5Len  )  goto  errLabel;

	hFile  =  CreateFile(  fileName,  GENERIC_READ,  FILE_SHARE_READ,  NULL,  OPEN_EXISTING,  FILE_ATTRIBUTE_NORMAL,  NULL  );
	if  (  hFile  ==  INVALID_HANDLE_VALUE  )  {
		traceLogA(  "CreateFile failed."  );
		goto  errLabel;
	}

	MDInit(  &context  );
	for  (  ;  ;  )  {
		 nBytesToRead  =  sizeof(  buffer  );
		 bResult  =  ReadFile(  hFile,  &buffer,  sizeof(  buffer  ),  &len,  NULL  ); 
		 if  (  !bResult  ||  len  ==  0 )  break;
		 MDUpdate(  &context,  buffer,  len  );
	}
	MDFinal(  digest,  &context  );
	CloseHandle(  hFile  );  hFile  =  NULL;
	sprintf(  tmpBuf,  "MD%d (%s) = ",  MD,  fileName  );
	for  (  i  =  0;  i  <  16;  i  ++  )
		 sprintf(  tmpBuf,  "%s%02x",  tmpBuf,  (  unsigned  char )digest[i]  );
	sprintf(  tmpBuf,  "%s%s",  tmpBuf,  "\n"  );
	
	bRet	=	TRUE;

errLabel:

	if  (  hFile  &&  hFile  !=  INVALID_HANDLE_VALUE  )  CloseHandle(  hFile  );

	if  (  bRet  )  {
		if  (  *pLen  >  CONST_qyMd5Len  )  {
			digest[CONST_qyMd5Len]  =  0;
			*pLen  =  CONST_qyMd5Len;
		}
	}

	return  bRet;

}
