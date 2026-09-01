

#include	"qyPrecomp.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<ctype.h>

#include	<WinSock2.h>
#include	<windows.h>


#include	<time.h>
#include	<stdio.h>
#include	"qyCommon.h"

#include	<tchar.h>


#define		MAX_ERR_LOG_FILE_LEN				100000

 static  char  sErrLogFile[1024]				=	"";
 static  char  sErrLogHint[1024]				=	"";

//  extern  "C"  int  truncFileHead(  int  nTruncated,  char  *  fileName  );
extern  "C"  int  truncFileHead(  int  nTruncated,  TCHAR  *  fileName  );

 
 extern  "C"  int  setErrLogFile(  char  *  fileName  )
{
	if ( strlen( fileName ) >= sizeof( sErrLogFile ) ) return -1;
	
	strcpy( sErrLogFile, fileName );
	return 0;

}


 extern  "C"  int  setErrLogHint(  char  *  hint  )
{
	if ( strlen( hint ) >= sizeof( sErrLogHint ) ) return -1;

	strcpy( sErrLogHint, hint );
	return 0;

}



		  


 

 //  extern "C" int truncFileHead( int nTruncated, char *fileName )
 extern "C" int truncFileHead( int nTruncated, TCHAR *fileName )
{
	int iErr = -1;
	TCHAR tmpPath[1024];
	TCHAR tmpFileName[2048];
	FILE *fp = NULL, *tmpFp = NULL;
	char buf[2048];
	
	if ( !GetTempPath( mycountof( tmpPath ), tmpPath ) ) return -1;
	if ( !GetTempFileName( tmpPath, _T(  "awm"  ), 0, tmpFileName ) ) return -1;

	fp = _tfopen( fileName, _T(  "r"  ) );
	tmpFp = _tfopen( tmpFileName, _T(  "w"  ) );
	if ( !fp || !tmpFp ) goto errLabel;
	
	if ( fseek( fp, nTruncated, SEEK_SET ) ) goto errLabel;

	while ( fgets( buf, sizeof( buf ), fp ) ) {
		fputs( buf, tmpFp );
	}
	fclose( fp ); fp = NULL;
	fclose( tmpFp ); tmpFp = NULL;

	CopyFile( tmpFileName, fileName, FALSE );
	DeleteFile( tmpFileName );

	iErr = 0;

errLabel:
	if ( fp ) fclose( fp ); 
	if ( tmpFp ) fclose( tmpFp );

	return iErr;

}

