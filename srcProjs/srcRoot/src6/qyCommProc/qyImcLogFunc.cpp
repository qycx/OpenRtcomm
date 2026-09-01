

#include	"stdafx.h"

#include	<stdlib.h>
#include	<string.h>
#include	<windows.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyImcLogFunc.h"
#include	"qyImcCommProc.h"
#include	"qyCommProc.h"
#include	"qyImcComm.h"
#include	"qyImcPublic.h"


#define		CONST_qyKeyType_defaultCode					0
#define		CONST_qyKeyType_defaultName					"??"
#define		CONST_qyKeyType_startCode					1



 extern  "C"  int  qyImcCreateLogRcd(  unsigned  char  cType,  char  *  url,  unsigned  char  result,
					char  *  title,  char  *  key,  char  *  keyTypeName,  char  *  context, 
					char  *  mac,
					QIM_LOGRCDX  *  pLogRcd  )
{
	 int iErr = -1;

	 traceLogA(  (char*)"qyImcCreateLogRcd( ) enters. { "  );
	 
	 /*
	 debugLog(  "qyImcCreateLogRcd( ): begins to print parameters: "  );
	 debugLog(  "	cType is [%c].",	cType  );
	 debugLog(  "	url is [%s].",		url  );
	 debugLog(  "	result is [%c].",	result  );
	 debugLog(  "	title is [%s].",	title  ?  title  :  "NULL"  );
	 debugLog(  "	key is [%s].",		key  ?  key  :  "NULL"  );
	 debugLog(  "	keyTypeName is [%s].", keyTypeName  ?  keyTypeName  : "NULL" );
	 debugLog(  "	context is [%s].",	context  ?  context  :  "NULL"  );
	 debugLog(  "	mac is [%s].",		mac  ?  mac  :  "NULL"  );
	 debugLog(  "qyImcCreateLogRcd( ):	stops."  );
	 */

	 pLogRcd->type			=			cType;
	 getCurTime(  (  char  *  )pLogRcd->time  );
	 if ( setQyBufStrn( url, &pLogRcd->url, QIM_MAXURLLOGLEN ) ) goto errLabel;
	 pLogRcd->result = result;
	 if  ( setQyBufStrn( title, &pLogRcd->title, QIM_MAXTITLELOGLEN )
		 || setQyBufStrn( key, &pLogRcd->key, QIM_MAXKEYLOGLEN ) ) 
	 {
		 goto errLabel;
	 }
	 safeStrnCpy(  (char*)(keyTypeName  ?  keyTypeName  :  CONST_qyKeyType_defaultName),  (  char  *  )pLogRcd->keyTypeName,  sizeof(  pLogRcd->keyTypeName  )  );
	 if  (  setQyBufStrn(  context,  &pLogRcd->context,  QIM_MAXCONTEXTLOGLEN  )  )  goto  errLabel;
	 if  (  pLogRcd->context.len  )  replaceChar(  '\n',  CONST_qyCharSpace,  (  char  *  )pLogRcd->context.data,  pLogRcd->context.len  -  1  );	// 需要将回车换成空白符, 以避免和作为行记录结束符标记的回车符冲突。
	 safeStrnCpy(  (char*)(mac  ?  mac  :  CONST_qyNullMac),  (  char  *  )pLogRcd->mac,  sizeof(  pLogRcd->mac  )  );
	 
	 iErr = 0;
	 
errLabel:
	 
	 if  (  iErr  )  {
		 resetQyBuf(  &pLogRcd->context  );
		 resetQyBuf(  &pLogRcd->key  );
		 resetQyBuf(  &pLogRcd->title  );
		 resetQyBuf(  &pLogRcd->url  );
	 }

	 traceLogA(  (char*)"qyImcCreateLogRcd( ) leaves. } "  );

	 return  iErr;

}

 extern "C" void qyImcFreeLogRcd( QIM_LOGRCDX *pLogRcd )
{
	 
	 resetQyBuf( &pLogRcd->context );
	 resetQyBuf( &pLogRcd->key );
	 resetQyBuf( &pLogRcd->title );
	 resetQyBuf( &pLogRcd->url );
	
}


 extern "C" int qyImcLogInfo( void *pLogContextParam, void *pLogRcdParam )
{
	 int				iErr			=	-1;
	 QY_LOGCONTEXT	*	pLogContext		=	( QY_LOGCONTEXT * )pLogContextParam;
	 QIM_LOGRCDX	*	pLogRcd			=	( QIM_LOGRCDX * )pLogRcdParam;
	 FILE			*	fpLog			=	NULL;
	 unsigned  char		szBuf[1]		=	"";
	 unsigned  char *	urlPtr			= szBuf, *titlePtr = szBuf, *keyPtr = szBuf, *contextPtr = szBuf;

	 debugLog( (char*)"qyImcLogInfo( ) enters. { " );

	 if ( !( fpLog = fopen( pLogContext->logFile.fullFileName, "a" ) ) ) {
		 debugLog( (char*)"[%s] can't be open.", pLogContext->logFile.fullFileName );
		 goto errLabel;
	 }
	 /*
	    unsigned char	type;
		unsigned char	time[14 + 1];
		QY_BUF			url;
		QY_BUF			title;
		QY_BUF			key;
		unsigned char	keyType;		// 关键字类别
		QY_BUF			context;
		unsigned char	mac[12 + 1];
	 */
	 if ( pLogRcd->url.len ) urlPtr = pLogRcd->url.data;
	 if ( pLogRcd->title.len ) titlePtr = pLogRcd->title.data;
	 if ( pLogRcd->key.len ) keyPtr = pLogRcd->key.data;
	 if ( pLogRcd->context.len ) contextPtr = pLogRcd->context.data;

	 fprintf(  fpLog,  QY_IMCLOGFMT, pLogRcd->type,
		 						     pLogRcd->time,
		 						     strlen( ( char * )urlPtr ), urlPtr,
									 pLogRcd->result,
		 						     strlen( ( char * )titlePtr ), titlePtr,
		 						     strlen( ( char * )keyPtr ), keyPtr,
		 						     pLogRcd->keyTypeName,
		 						     strlen( ( char * )contextPtr ), contextPtr,
		 						     pLogRcd->mac  );
	 

	 
	 iErr = 0;

errLabel:

	 if ( fpLog ) fclose( fpLog );

	 debugLog( (char*)"qyImcLogInfo( ) leaves. } " );

	 return iErr;
}


 // 返回非0将终止内容过滤的进一步进行
 extern "C" int qyImcCfCallback( void *pCfInfoParam, void *p2 )
{
	 int				iErr			=	-1;
	 CF_INFO		*	pCfInfo			=	( CF_INFO * )pCfInfoParam;
	 QY_LOGCONTEXT	*	pLogContext		=	( QY_LOGCONTEXT * )pCfInfo->pVoid1;
	 QIM_LOGRCDX	*	pLogRcd			=	( QIM_LOGRCDX * )pCfInfo->pVoid2;
	 QIM_LOGRCDX		tmpLogRcd;
	 
	 debugLog( (char*)"qyImcCfCallback( ) enters. { " );
 	 
	 // extern "C" int qyImcCreateLogRcd( unsigned char cType, char *url, unsigned char result, char *title, char *key, unsigned char keyType, char *context, char *mac, QY_IMC_LOG_RCD *pLogRcd );

	 // typedef struct __qy_imc_log_rcd_t {
	 //		unsigned char	type;
	 //		unsigned char	time[14 + 1];
	 //		QY_BUF			url;
	 //		unsigned char	result;
	 //		QY_BUF			title;
	 //		QY_BUF			key;
	 //		unsigned char	keyType;		// 关键字类别
	 //		QY_BUF			context;
	 //		unsigned char	mac[12 + 1];
	 //	} QY_IMC_LOG_RCD;

	 if ( pCfInfo->bCFLogOn ) {

		 memset( &tmpLogRcd, 0, sizeof( tmpLogRcd ) );
		 
		 tmpLogRcd.type  =  pLogRcd->type;
		 getCurTime( ( char * )tmpLogRcd.time );
		 if ( qyBufCpy( &pLogRcd->url, &tmpLogRcd.url ) ) goto errLabel;
		 tmpLogRcd.result = pLogRcd->result;
		 if ( qyBufCpy( &pLogRcd->title, &tmpLogRcd.title ) ) goto errLabel;
		 if ( setQyBufStrn( pCfInfo->pKey, &tmpLogRcd.key, pCfInfo->keyLen ) ) goto errLabel;
		 memcpy(  tmpLogRcd.keyTypeName,  pLogRcd->keyTypeName,  sizeof(  tmpLogRcd.keyTypeName  )  );
		 if ( setQyBufStrn( pCfInfo->pContext, &tmpLogRcd.context, pCfInfo->contextLen ) ) goto errLabel;
		 if ( tmpLogRcd.context.len ) replaceChar( '\n', ' ', ( char * )tmpLogRcd.context.data, tmpLogRcd.context.len - 1 );	// 需要将回车换成空白符, 以避免和作为行记录结束符标记的回车符冲突。
		 memcpy( tmpLogRcd.mac, pLogRcd->mac, sizeof( tmpLogRcd.mac ) );
		 
		 qyImcLogInfo( pLogContext, &tmpLogRcd );
		
	 }

	 iErr = 0;

errLabel:
 	 
	 qyImcFreeLogRcd( &tmpLogRcd );
		 
	 if ( !iErr ) {
		pCfInfo->nMatchedAndStop --;
		if ( !pCfInfo->nMatchedAndStop ) iErr = 1;
	 }
	 debugLog( (char*)"qyImcCfCallback( ) leaves. } " );

	 return iErr;

}



 //  1. pLogRcd在输入前须被复位。
 //  2. 此函数须进一步加强容错性重写，以适应各种情况.
 //  3. 分配了内存，pLogRcd须被释放
 int getNextQyImcLogRcd( FILE *fp, QIM_LOGRCDX *pLogRcd )
{
	 int iErr = -1;
	 char buf[QIM_MAXLOGLEN + 1];
	 int len, nRead;
	 char *ptr = NULL;

	 /*
	 typedef struct __qy_imc_log_rcd_t {
		  unsigned char		type;
		  unsigned char		time[14 + 1];
		  QY_BUF			url;
		  unsigned char		result;
		  QY_BUF			title;
		  QY_BUF			key;
		  unsigned char		keyTypeName[8  +  1];		// 关键字类别
		  QY_BUF			context;
		  unsigned char		mac[12 + 1];
  	} QY_IMC_LOG_RCD;
	*/
	 // #define QY_IMC_LOG_FMT	"%02x|%014s%|%08x%s|%02x|%08x%s|%08x%s|%08s|%08x%s|%012s\n"

	 for ( ; ; ) {
		if ( !fgets( buf, sizeof( buf ), fp ) ) goto errLabel;
		len = strlen( buf );
		if ( len < 1 ) continue;
		if ( len == sizeof( buf ) - 1 && buf[len - 1] != '\n' ) continue;	// 太长了 
		nRead = 0;
		if ( 2 == sscanf( buf + nRead, "%02x|%014s", &pLogRcd->type, pLogRcd->time ) ) {
			nRead += 2 + 1 + 14 + 1; 
			if ( nRead < len && !sscanfToQyBuf( buf + nRead, &pLogRcd->url ) ) {
				if ( !pLogRcd->url.len ) nRead += 8 + 1;
				else nRead += 8 + ( pLogRcd->url.len - 1 ) + 1;	// 注意对非0长度string的quBuf, len比字符串长度多1以存放'\0'.
				if ( nRead < len &&	1 == sscanf( buf + nRead, "%02x", &pLogRcd->result ) ) {
					nRead += 2 + 1;
					if ( nRead < len && !sscanfToQyBuf( buf + nRead, &pLogRcd->title ) ) {
						if ( !pLogRcd->title.len ) nRead += 8 + 1;
						else nRead += 8 + ( pLogRcd->title.len - 1 ) + 1;
						if ( nRead < len && !sscanfToQyBuf( buf + nRead, &pLogRcd->key ) ) {
							if ( !pLogRcd->key.len ) nRead += 8 + 1;
							else nRead += 8 + ( pLogRcd->key.len - 1 ) + 1;
							if  (  len  -  nRead  >  8  )  {
								memcpy(  pLogRcd->keyTypeName,  buf  +  nRead,  8  );
								nRead  +=  8  +  1;
								if ( nRead < len && !sscanfToQyBuf( buf + nRead, &pLogRcd->context ) ) {
									if ( !pLogRcd->context.len ) nRead += 8 + 1;
									else nRead += 8 + ( pLogRcd->context.len - 1 ) + 1;
									if ( nRead < len && 1 == sscanf( buf + nRead, "%012s", pLogRcd->mac ) ) {
										if ( strlen( ( const char * )pLogRcd->mac ) == 12 ) break;
									}
									resetQyBuf( &pLogRcd->context );
								}
							}

							resetQyBuf( &pLogRcd->key );
						}
						resetQyBuf( &pLogRcd->title );
					}
				}
				resetQyBuf( &pLogRcd->url );
			}			
		}
		continue;
	 }
	 
	 iErr = 0;

errLabel:
	 
	 if ( iErr ) {
		 qyImcFreeLogRcd( pLogRcd );
	 }

	 return iErr;

}


/*
 typedef struct __qy_imc_log_rcd_t {
	unsigned char	type;			// 记录类型，如：普通、警告、严重
	unsigned char	time[14 + 1];
	QY_BUF			url;
	unsigned char	result;			// 结果，如：禁止、记录、通过
	QY_BUF			title;
	QY_BUF			key;
	unsigned char	keyType;		// 关键字类别，如：色情、游戏、证券、暴力、赌博、反动等
	QY_BUF			context;
	unsigned char	mac[12 + 1];	// mac.
} QY_IMC_LOG_RCD;
*/

 void showQyImcLogRcd(  QIM_LOGRCDX  *  pLogRcd  )
{
	#ifndef  __DEBUG__
		return;
	#else

		char  buf[8192];

		sprintf(  buf,  "[%s][%s]",  qyLogTypeStr(  pLogRcd->type  ),  pLogRcd->time  );
		if  (  pLogRcd->url.len  )  sprintf(  buf,  "%s[%s]",  buf,  pLogRcd->url.data  );
		else	strcat(  buf,  "[]"  );
		strcat(  buf,  qyLogResultStr(  pLogRcd->result  )  );
		if  (  pLogRcd->title.len  )  sprintf(  buf,  "%s[%s]",  buf,  pLogRcd->title.data  );
		else	strcat(  buf,  "[]"  );
		if  (  pLogRcd->key.len  )  sprintf(  buf,  "%s[%s]",  buf,  pLogRcd->key.data  );
		else	strcat(  buf,  "[]"  );
		strcat(  buf,  (  char  *  )pLogRcd->keyTypeName  );
		if  (  pLogRcd->context.len  )  sprintf(  buf,  "%s[%s]",  buf,  pLogRcd->context.data  );
		else	strcat(  buf,  "[]"  );
		strcat(  buf,  (  char  *  )pLogRcd->mac  );

		traceLogA(  (char*)"%s",  buf  );

		return;

	#endif

 } 


 extern  "C"  int  qmPreSetupDict(  void  *  pCfFileParam,  FILE  *  fp,  void  *  pOpInfosParam  )
{
	 int						iErr			=		-1;
	 QY_CF_FILE			*		pCfFile			=		(  QY_CF_FILE  *  )pCfFileParam;
	 long						len;
	 QY_IMCPOLICY_RCD			tmpImcPolicy;
	 char						xBufKeyTypeCode[3];
	 QY_CFOP_STRUCT		*		pOpInfos		=		(  QY_CFOP_STRUCT  *  )pOpInfosParam;

	 traceLogA(  (char*)"qmPreSetupDict ..  enters."  );

	 if  (  fread(  &pCfFile->head,  sizeof(  pCfFile->head  ),  1,  fp  )  !=  1  )  goto  errLabel;
	 if  (  memcmp(  pCfFile->head.objName,  CONST_qyObjName_mcPolicyFile,  min(  strlen(  CONST_qyObjName_mcPolicyFile  ),  sizeof(  pCfFile->head.objName  )  )  )  )  goto  errLabel;

	 if  (  fread(  &pCfFile->curObjHead,  sizeof(  pCfFile->curObjHead  ),  1,  fp  )  !=  1  )  goto  errLabel;
	 if  (  memcmp(  pCfFile->curObjHead.objName,  CONST_qyObjName_mcKeyTypePolicy,  min(  strlen(  CONST_qyObjName_mcKeyTypePolicy  ),  sizeof(  pCfFile->curObjHead.objName  )  )  )  )  goto  errLabel;
	 if  (  qyXStr2L(  pCfFile->curObjHead.objLenStr,  &len  )  )  goto  errLabel;

	 traceLogA(  (char*)"qmPreSetupDict ..  len is %d",  len  );

	 for  (  ;  len  >  0;  len  -=  CONST_qyRcdLen_mcKeyTypePolicy  )  {
		  if  (  4  !=  fscanf(  fp,  CONST_qyRcdFmt_mcKeyTypePolicy,  xBufKeyTypeCode,  &tmpImcPolicy.imPolicy,  tmpImcPolicy.bmPolicy,  tmpImcPolicy.keyTypeName  )  )  goto  errLabel;
		  tmpImcPolicy.keyTypeCode  =  qyX2C(  xBufKeyTypeCode  );
		  memcpy(  pOpInfos[tmpImcPolicy.keyTypeCode].op,  tmpImcPolicy.imPolicy,  2  );
		  memcpy(  pOpInfos[tmpImcPolicy.keyTypeCode].keyTypeName,  tmpImcPolicy.keyTypeName,  sizeof(  pOpInfos[tmpImcPolicy.keyTypeCode].keyTypeName  )  );
	 }

	 if  (  fread(  &pCfFile->curObjHead,  sizeof(  pCfFile->curObjHead  ),  1,  fp  )  !=  1  )  goto  errLabel;
	 if  (  memcmp(  pCfFile->curObjHead.objName,  CONST_qyObjName_mcSite,  min(  strlen(  CONST_qyObjName_mcSite  ),  sizeof(  pCfFile->curObjHead.objName  )  )  )  )  goto  errLabel;
	 pCfFile->curLangMode	=	CS_URL;
	 pCfFile->curlTypeInfo  =	CS_URLTYPE_HTTP;
	 if  (  qyXStr2L(  pCfFile->curObjHead.objLenStr,  (  long  *  )&pCfFile->curObjLen  )  )  goto  errLabel;
	 
	 iErr		=		0;
 
errLabel:

	 traceLogA(  (char*)"qmPreSetupDict ..  leaves."  );

	 return		iErr;

}

 
 //  返回读出的keyBuf里的url的长度
 //  记录顺序: serviceType,url,name,keyTypeCode
 //  pCfFile->curLangMode	-->		lang
 //  serviceType			-->		lTypeInfo
 //	 url					-->		keyBuf
 //  keyTypeCode			-->		level
 extern  "C"  int  qmGetPhrase(  void  *  pCfFileParam,  FILE  *  fp,  char  *  keyBuf,  unsigned  int  size,  int  *  lang,  int  *  plTypeInfo,  int  *  level  )
{
	 int						iErr			=		-1;
	 QY_CF_FILE			*		pCfFile			=		(  QY_CF_FILE  *  )pCfFileParam;
	 int						n				=		0;
	 char						serviceTypeBuf[3];
	 int						len;
	 char						fmt[128];
	 char						xBuf[3];
	 int						nRead			=		0;
	 char						nameBuf[1024];
	 unsigned  char				keyTypeCode;
	 int						i;
	 
	 if  (  !pCfFile->curObjLen  )  return  0;
	 if  (  size  <  256  )  return  -1;
	 
	 if  (  fscanf(  fp,  "%02s%02s",  serviceTypeBuf,  &xBuf  )  !=  2  )  goto  errLabel;
	 nRead	+=	4;
	 if  (  (  len  =  qyX2C(  xBuf  )  ) <=  0  )  goto  errLabel;	// url不能长度为零
	 if  (  !len  )  goto  errLabel;
	 sprintf(  fmt,  "%%%ds",  len  );
	 if  (  fscanf(  fp,  fmt,  keyBuf  )  !=  1  )  goto  errLabel;
	 n		=	len;												//  n为返回值
	 nRead  +=  len;
	 if  (  fscanf(  fp, "%02s",  xBuf  )  !=  1  )  goto  errLabel;
	 if  (  (  len  =  qyX2C(  xBuf  )  )  <  0  )  goto  errLabel;	// name可以长度为零
	 nRead  +=  2;
	 if  (  len  )  {
		 sprintf(  fmt,  "%%%ds",  len  );
		 if  (  fscanf(  fp,  fmt,  nameBuf  )  !=  1  )  goto  errLabel;
		 nRead  +=  len;
	 }
	 if  (  fscanf(  fp,  "%02s",  xBuf  )  !=  1  )  goto  errLabel;
	 nRead  +=  2;
	 if  (  (  i  =  qyX2C(  xBuf  )  )  <=  0  )  goto  errLabel;
	 keyTypeCode  =  (  unsigned  char  )i;
	 
	 *lang					=	pCfFile->curLangMode;
	 *plTypeInfo			=	pCfFile->curlTypeInfo;
	 *level					=	keyTypeCode;
	 pCfFile->curObjLen	   -=  nRead;
	 
	 iErr   =   0;

errLabel:

	 if  (  iErr  )  return  -1;
	 return  n;

}



