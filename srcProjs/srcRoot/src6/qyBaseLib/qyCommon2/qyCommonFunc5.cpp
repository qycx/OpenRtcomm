
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<ctype.h>


#include	<WinSock2.h>
#include	<windows.h>
#if  0
#include	<lm.h>
#endif
#include	"qyCommon.h"


 extern "C" void resetQyBuf( QY_BUF *buf ) 
{ 
	 if ( !buf ) return;
	 switch ( buf->resourceType ) {
		case QY_BUF_AUTO_FREE:
			if ( buf->len ) free( buf->data );
			break;
		default:
			break;
	 }
	memset( buf, 0, sizeof( QY_BUF ) );
}
 
 extern  "C"  int  qyBufAllocData(  QY_BUF  *  buf,	 unsigned  int  n  )
{
	 if  (  buf->len  )  return  -1;
	 if (  !(  buf->data  =  (  unsigned  char  *  )malloc(  n  )  )  )	return  -1;
	 buf->len  =  n;
	 return  0;
}

 extern  "C"  void  qyBufFree(  QY_BUF  *  buf  )
{
	 resetQyBuf(  buf  );
}

 // 最多拷贝n bytes.
 extern "C" int setQyBufStrn( char *str, QY_BUF *buf, unsigned int n )
{
	 int iErr = -1;
	 unsigned int len = 0;

	 if ( !buf || buf->len ) return -1;

	 memset( buf, 0, sizeof( QY_BUF ) );
	 if ( !n || !str || !( len = strlen( str ) ) ) return 0;
	 if ( len > n ) len = n;
	 
	 buf->data = ( unsigned char * )malloc( len + 1 );
	 if ( !buf->data ) goto errLabel;

	 memcpy( ( char * )buf->data, str, len );
	 buf->data[len] = 0;
	 buf->len = len + 1;
	 buf->resourceType = QY_BUF_AUTO_FREE;
	 	 
	 iErr = 0;

errLabel:

	 if ( iErr ) {
		 if ( buf->data ) { free( buf->data ); memset( buf, 0, sizeof( QY_BUF ) ); }
	 }

	 return iErr;
	 
}

 extern "C" int setQyBufStr( char *str, QY_BUF *buf )
{
	 int iErr = -1;
	 int len = 0;

	 if ( !buf || buf->len ) return -1;
	 if ( !str || !( len = strlen( str ) ) ) return 0;

	 memset( buf, 0, sizeof( QY_BUF ) );
	 buf->data = ( unsigned char * )malloc( len + 1 );
	 if ( !buf->data ) goto errLabel;
	 	 
	 iErr = 0;

errLabel:

	 if ( iErr ) {
		 if ( buf->data ) { free( buf->data ); buf->data = NULL; }
	 }

	 if ( !iErr ) {
		 strcpy( ( char * )buf->data, str );
	 	 buf->len = len + 1;
	 	 buf->resourceType = QY_BUF_AUTO_FREE;
	 }

	 return iErr;
	 
}

 // qyBuf的复制，pDst永远动态分配。
 extern "C" int qyBufCpy( QY_BUF *pSrc, QY_BUF *pDst )
{
	 if ( !pDst ) return -1;
	 memset( pDst, 0, sizeof( QY_BUF ) );
	 if ( !pSrc ) return 0;
	 return setQyBufStrn( ( char * )pSrc->data, pDst, pSrc->len );

}

 extern "C" int setQyBufData( void * data, unsigned int n, QY_BUF * buf )
{
 	 int iErr = -1;
	 unsigned int len = 0;

	 if ( !buf || buf->len ) return -1;

	 if ( !n || !data ) return 0;
	 len	=		n;

	 buf->data = ( unsigned char * )malloc( len  );
	 if ( !buf->data ) goto errLabel;

	 memcpy( ( char * )buf->data, data, len );
	 buf->len = len;
	 buf->resourceType = QY_BUF_AUTO_FREE;
	 	 
	 iErr = 0;

errLabel:

	 if ( iErr ) {
		 if ( buf->data ) { free( buf->data ); memset( buf, 0, sizeof( QY_BUF ) ); }
	 }

	 return iErr;

}

 extern "C" int qyBufCmp( QY_BUF *buf1, QY_BUF *buf2 )
{
	 if ( buf1->len == buf2->len && !memcmp( buf1->data, buf2->data, buf1->len ) ) return 0;
	 return -1;
}

  extern "C" int sscanfToQyBuf( char *buf, QY_BUF *pQyBuf )
{
	 unsigned int len = 0;

	 if ( pQyBuf->len ) return -1;
	 if ( strlen( buf ) < 8 ) return -1;

	 if ( 1 == sscanf( buf, "%08x", &len ) ) {
		  if ( !setQyBufStrn( buf + 8, pQyBuf, len ) ) {
			 if ( !pQyBuf->len || pQyBuf->len == len + 1 ) return 0;
			 resetQyBuf( pQyBuf );
		 }
	 }
		 
	 return -1;
	
}


 extern "C" int debugLogQyBuf( char *name, QY_BUF *buf )
{
	 if ( !buf->len ) debugLog( "%s is 0-len." );
	 else debugLog( "%s is [%s]", buf->data );
	 return 0;
}


 extern "C" char *qySkipSpace( char *buf )
{
	 if ( !buf || !strlen( buf ) ) return NULL;
	 while ( *buf ) {
		 if ( isspace( *buf ) ) buf ++;
		 break;
	 }
	 if ( !*buf ) return NULL;
	 
	 return buf;

}

 extern "C" void replaceChar( unsigned char  replacedC, unsigned char replacingC, char *buf, unsigned int len )
{
	 //  traceLogA( "replaceChar( ): enters, buf is [%s]", buf );
	 for ( ; len; len -- ) {
		 if ( ( unsigned char )buf[len - 1] == replacedC ) buf[len - 1] = replacingC;
	 }
	 //  traceLogA( "replaceChar( ): leaves, buf is [%s]", buf );
	 return;
}



 // unsigned char outBuf[] = FILE_DATA;
 extern "C" int bufToFile( char *outBuf, unsigned long size, char *fileName )
{
	 int iErr = -1;
	 FILE *fp = NULL;
	 unsigned int i;

	 fp = fopen( fileName, "wb" );
	 if ( !fp ) {
		 debugLog( "[%s] can't be written.\n" );
		 goto errLabel;
	 }
	 // printf( "size of file is %d.\n", sizeof( outBuf ) );
	 for ( i = 0; i < size; i ++ ) {
		 fputc( outBuf[i], fp );
	 }	 

	 iErr = 0;

errLabel:

	 if ( fp ) fclose( fp );

	 return iErr;

}



 extern  "C"  BOOL  bDirExists(  TCHAR  *  dir  )
{
	 DWORD  kk;
	 
	 kk  =  GetFileAttributes(  dir  );
	 if  (  kk  ==  0xFFFFFFFF  )  {
	 	 return  FALSE;
	 }
	 if  (  !(  kk  &  FILE_ATTRIBUTE_DIRECTORY  )  )  {
		 return  FALSE;
	 }
	 return  TRUE;
}
 



 QY_DMITEM  CONST_qyNullTable[]  =
{
	{  -1,							NULL,					},
};


