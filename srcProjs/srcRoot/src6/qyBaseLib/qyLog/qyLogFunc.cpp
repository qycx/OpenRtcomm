

#include	<WinSock2.h>
#include <windows.h>
#include	<tchar.h>
#include "qyCommon.h"



 extern "C" int initQyFileLogContext( int serviceId, char *fileName, QY_LOG_INFO_FUNC pLogFunc, QY_LOGCONTEXT *pLogContext )
{
	 if ( strlen( fileName ) >= sizeof( pLogContext->logFile.fullFileName ) ) return -1;

	 pLogContext->methods[0] = QY_LOG_METHOD_BY_FILE;
	 pLogContext->serviceId = serviceId;
	 strcpy( pLogContext->logFile.fullFileName, fileName );
	 pLogContext->pLogFunc = pLogFunc;
	 
	 return 0;

}

 extern "C" void exitQyFileLogContext( QY_LOGCONTEXT *pLogContext )
{
	 return;
}

 extern "C" int changeQyLogFile( char *fileName, QY_LOGCONTEXT *pLogContext )
{

	 if ( strlen( fileName ) >= sizeof( pLogContext->logFile.fullFileName ) ) return -1;

	 strcpy( pLogContext->logFile.fullFileName, fileName );
	 return 0;
}

 // 将YYYYMMDD的格式可视化
 extern "C" char *qyDateFormat( char *buf, char *displayBuf, unsigned int size )
{
	 char	*ptr	=	displayBuf;

	 if  (  size  <  11  ||  strlen(  buf  )  <  8  )  return  NULL;
	 memcpy(  displayBuf,  buf,  4  );  displayBuf  +=  4;  buf  +=  4;
	 displayBuf[0]  =  '-';  displayBuf  ++  ;
	 memcpy( displayBuf, buf, 2 ); displayBuf += 2; buf += 2;
	 displayBuf[0] = '-'; displayBuf ++;
	 memcpy( displayBuf, buf, 2 ); displayBuf += 2; buf += 2;
	 displayBuf[0]  =  '\0';

	 return  ptr;
	
}





 extern "C" int qyLogInfo( QY_LOGCONTEXT *pLogContext, void *pLogRcd )
{	
	if ( !pLogContext->pLogFunc ) return -1;
	return pLogContext->pLogFunc( pLogContext, pLogRcd );	
}


 extern "C" char * qyLogTypeStr( unsigned char type )
{
	 switch ( type ) {
		case QY_LOG_TYPE_NORMAL:
			return "normal";
		case QY_LOG_TYPE_CRITICAL:
			return "serious";
		default:
			break;
	 }
	 return "\"unknown log type\"";
}

 extern "C" char * qyLogResultStr( unsigned char result )
{
	 switch ( result ) {
		case QY_LOG_RESULT_PASSED:
			return "通过";
		case QY_LOG_RESULT_LOGGED:
			return "记录";
		case QY_LOG_RESULT_DENIED:
			return "禁止";
		default:
			break;
	 }
	 return "\"未知结果!\"";
}

