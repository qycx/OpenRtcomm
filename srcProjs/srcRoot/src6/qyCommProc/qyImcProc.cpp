
#include	<windows.h>
#include	"qyCommon.h"
#include	"qyImcCommonCfg.h"
#include	"qyImcCommon.h"
#include	"qyImcLogFunc.h"
 
 int  getImcEnv(  QY_IMC_ENV  *  pEnv  )
{
	 MEMORYSTATUS  memStatus;

	 memStatus.dwLength  =  sizeof(  memStatus  );
	 GlobalMemoryStatus(  &memStatus  );
	 pEnv->dwTotalPhys  =  memStatus.dwTotalPhys;
	 debugLog(  "%d bytes physical memory.",  pEnv->dwTotalPhys  );
	 
	 return 0;
}

 
 int  setQmInfo(  BOOL  bShmCreator,  char * workDir,  char * policyFile, BOOL * pbDictRefreshedParam,  QY_IMC_INFO * pQI,  QY_BUF * pSharedBuf  )
{
	 int			iErr								=	-1;
	 QY_IMC_INFO	qI;
	 char			magic[QY_INFO_FILE_MAGIC_LEN + 1];
	 int			magicLen							=	QY_INFO_FILE_MAGIC_LEN;
	 char			urlDictFile[QY_MAXPATHLEN + 1];
	 BOOL			bCfInited							=	FALSE;
	 BOOL			tmpbDictRefreshed					=	*pbDictRefreshedParam;

	 traceLogA(  "setQmInfo ..  enters."  );

	 if  (  qyStrCat(  workDir,  QY_IMC_URLDICTNAME,  urlDictFile,  sizeof(  urlDictFile  )  )  )  goto errLabel;

	 qI.head.len	=	QY_INFO_FILE_MAGIC_LEN;
	 qI.head.data	=	pSharedBuf->data;
	 qI.tail.len	=	QY_INFO_FILE_MAGIC_LEN;
	 qI.tail.data	=	pSharedBuf->data + pSharedBuf->len - qI.tail.len;
	 qI.data.len	=	pSharedBuf->len - qI.head.len - qI.tail.len; 
	 qI.data.data	=	pSharedBuf->data + qI.head.len;

	 if  (  !tmpbDictRefreshed  )  {
		 if ( memcmp( qI.head.data, QY_INFO_FILE_MAGIC, QY_INFO_FILE_MAGIC_LEN ) 
			|| memcmp( qI.tail.data, QY_INFO_FILE_TAIL_END_MAGIC, QY_INFO_FILE_MAGIC_LEN ) )
		 {
			 debugLog(  "setQmInfo(  ):  文件格式不对."  );
			 tmpbDictRefreshed  =  TRUE;
		 }
	 }

	 if  (  !bShmCreator  &&  tmpbDictRefreshed  )  goto  errLabel;

	 if  (  tmpbDictRefreshed  )  {
	 	 traceLogA( "setQmInfo(  ): 字典需要刷新." );
		 memset( pSharedBuf->data, 0, pSharedBuf->len );
		 memcpy( pSharedBuf->data, QY_INFO_FILE_MAGIC, QY_INFO_FILE_MAGIC_LEN );

		 // 改变前，先设置起始标志
		 strcpy( magic, QY_INFO_FILE_TAIL_START_MAGIC );
		 memcpy( qI.tail.data, magic, magicLen );
	 }
		 
	 QY_CF_STRUCT tmpCf;
	 QY_CF_FILE tmpCfFiles[1];

	 memset(  &tmpCf,  0,  sizeof(  tmpCf  )  );
	 memset(  (  char  *  )tmpCfFiles,  0,  sizeof(  tmpCfFiles  )  );

	 if  (  safeStrCpy(  policyFile,  tmpCfFiles[0].fileName,  sizeof(  tmpCfFiles[0].fileName  )  )  )  goto  errLabel;
	 tmpCfFiles[0].preSetupDict		=		qmPreSetupDict;
	 tmpCfFiles[0].getPhrase		=		qmGetPhrase;
	 tmpCfFiles[0].curLangMode		=		CS_URL;
	 tmpCf.cfFileCnt				=		1;
	 tmpCf.pCfFiles					=		tmpCfFiles;
	 tmpCf.pDictDir					=		(  const  char  *  )workDir;
	 tmpCf.pSharedDataBuf			=	&	qI.data; 
	 tmpCf.bDictRefreshed			=		tmpbDictRefreshed;
		 
	 if ( initCF( &tmpCf ) ) goto errLabel;
	 bCfInited = TRUE;

	 if	 (  tmpbDictRefreshed  )  {
		 // 改变后，再设置结束标志
		 strcpy( magic, QY_INFO_FILE_TAIL_END_MAGIC );
		 memcpy( qI.tail.data, magic, magicLen );
	 }

	 if  (  !FlushViewOfFile(  pSharedBuf->data,  pSharedBuf->len  )  )  {
		 qyDisplayLastError(  "FlushViewOfFile(  )"  );
		 debugLog(  "FlushViewOfFile( ) failed."  );
		 goto  errLabel;
	 }
		 	 	 
	 memcpy( pQI, &qI, sizeof( qI ) );

	 iErr = 0;

errLabel:

	 if  (  iErr  )  {
		 if  (  bCfInited  )  exitCF( );
	 }
	 if  (  !iErr  )  {
		 *pbDictRefreshedParam  =  tmpbDictRefreshed;
	 }

	 traceLogA(  "setQmInfo ..  leaves."  );

	 return iErr;

}

 void resetQmInfo( QY_BUF *pSharedBuf )
{
	 exitCF( );
	 return;
}


