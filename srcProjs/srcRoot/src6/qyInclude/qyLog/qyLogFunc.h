
#ifndef __QYLOGFUNC_H__
#define __QYLOGFUNC_H__	/* { */

typedef int ( *QY_LOG_INFO_FUNC )( void *pLogContext, void *pLogRcd );

#ifdef __cplusplus
 extern "C" {
#endif

#include "qyCommon\\asrObjs.h"

#define QY_LOG_METHOD_BY_FILE	1
#define QY_LOG_METHOD_BY_SOCK	2


typedef  struct  __qy_logContext_t  {
				 char				methods[4];
				 int				serviceId;
				 ASR_LOGICAL_SERVER logServer;
				 struct {
						char		fullFileName[QY_MAXPATHLEN + 1];
				 }					logFile;
				 QY_LOG_INFO_FUNC	pLogFunc;
}		 QY_LOGCONTEXT;


#define RCD_LEN				90 //76 + 12 mac地址占用12个字节  
#define RULE_LEN			51	//21 lastScanTime14个字节，mac 12个字节
#define REM_REC_LEN			95	//81 + 14 新增加了[mac]

// log信息类型
#define QY_LOG_TYPE_NORMAL			'1'
#define QY_LOG_TYPE_CRITICAL		'2'

#define QY_LOG_RESULT_PASSED		'1'
#define QY_LOG_RESULT_LOGGED		'2'
#define	QY_LOG_RESULT_DENIED		'3'


typedef struct __qy_logRcd_t {
	void *p;
	//	AWM_LOG_RCD *pAwmLogRcd;
	//	QY_IMC_LOG_RCD	*p;	
} QY_LOGRCD;




int initQyFileLogContext( int serviceId, char *fileName, QY_LOG_INFO_FUNC pLogFunc, QY_LOGCONTEXT *pLogContext );
void exitQyFileLogContext( QY_LOGCONTEXT *pLogContext );
int changeQyLogFile( char *fileName, QY_LOGCONTEXT *pLogContext );
int qyLogInfo( QY_LOGCONTEXT *pQyLogContext, void *p );
char *qyLogTypeStr( unsigned char type );
char *qyLogResultStr( unsigned char result );
char *qyDateFormat( char *buf, char *displayBuf, unsigned int size );



#ifdef __cplusplus
 }
#endif


#endif /* } */

