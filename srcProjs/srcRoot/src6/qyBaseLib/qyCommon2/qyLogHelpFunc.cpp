

#include  <stdlib.h>
#include  <windows.h>
#include  "qyCommon.h"


 // 将缓存中的数据入库
 // 在内存中设一标志位，logFileFlg		1时当前logFile为***1.tmp,
 //										2时			  为***2.tmp
 //										其他	      不能处理
 //     qyPutLogIntoDb先处理另一个文件，设定另一文件比当前文件早，完毕后删除，
 //	然后处理当前文件。
 //     在当前文件太大时，设标志位切换logFile.等待10秒后再处理原文件，完毕后删除。
 // 处理时在注册表中设值以表明处理到的位置。删除后，须将此位置清0。
 // 


/* 
 LOG_HELP_STRUCT  * getLogHelpStruct(  )
{
	 static LOG_HELP_STRUCT  gLogHelpStruct;
	 return  & gLogHelpStruct;
}
*/
 
/*
 int initLogHelp(  char * workKey, char * workDir, char * logFile1, char * logFile2, LOG_HELP_STRUCT * pLogHelp  )
{	 
	 int	iErr	=	-1;
	 int	curProcedFileId;
	 	 
	 if  (  safeStrCpy(  workKey,  pLogHelp->cfg.workKey,  sizeof(  pLogHelp->cfg.workKey  )  )  )  goto  errLabel;
	 if  (  safeStrCpy(  workDir,  pLogHelp->cfg.workDir,  sizeof(  pLogHelp->cfg.workDir  )  )  )  goto  errLabel;

	 if  (  safeStrCpy(  QY_LOGFILEID_VAL,  pLogHelp->cfg.curLfIdVal,  sizeof(  pLogHelp->cfg.curLfIdVal  )  )  )  goto  errLabel;
	 if  (  safeStrCpy(  QY_LOGFILE1_PROCEDLEN_VAL,  pLogHelp->cfg.lf1ProcedLenVal,  sizeof(  pLogHelp->cfg.lf1ProcedLenVal  )  )  )  goto  errLabel;
	 if  (  safeStrCpy(  QY_LOGFILE2_PROCEDLEN_VAL,  pLogHelp->cfg.lf2ProcedLenVal,  sizeof(  pLogHelp->cfg.lf2ProcedLenVal  )  )  )  goto  errLabel;
	 
	 if  (  !logFile1 || !logFile1[0]  )  {
		 if  (  safeStrCpy(  QY_LOGFILE1NAME,  pLogHelp->cfg.lf1Name,  sizeof(  pLogHelp->cfg.lf1Name  )  )  )  goto  errLabel;	 
		}
	 else  {
		 if  (  safeStrCpy(  logFile1,  pLogHelp->cfg.lf1Name,  sizeof(  pLogHelp->cfg.lf1Name  )  )  )  goto  errLabel;
	 }
	 if  (  !logFile2  ||  !logFile2[0]  )  {
		 if  (  safeStrCpy(  QY_LOGFILE2NAME,  pLogHelp->cfg.lf2Name,  sizeof(  pLogHelp->cfg.lf2Name  )  )  )  goto  errLabel;
		}
	 else  {
		 if  (  safeStrCpy(  logFile2,  pLogHelp->cfg.lf2Name,  sizeof(  pLogHelp->cfg.lf2Name  )  )  )  goto  errLabel;
	 }

	 pLogHelp->cfg.maxLogFileSize  =  QY_MAX_LOGFILE_SIZE;

	 curProcedFileId  =  getCurProcedFileId(  pLogHelp  );
	 if  (  curProcedFileId  <  0  )  {
		 traceLogA(  "Critical error:  initLogHelp(  )  ---  getCurProcedFileId(  ) failed."  );
		 goto  errLabel;
	 }

	 if  (  GetFileAttributes(  pLogHelp->curProcedLfName  )  ==  0xFFFFFFFF  )  {
		 zeroLogFileProcedLen(  pLogHelp,  pLogHelp->curProcedLfId  );
	 }

	 iErr	=	0;

errLabel:

	 return  iErr;

}

 void exitLogHelp(  LOG_HELP_STRUCT  *  pLogHelp  )
{
	 return;
}




 //   这几个函数为自包含函数，所有的分析和处理都独自进行，不需要其他函数的太多管理，故
 // 如initImcProcess(  )等都仅返回0，而将错误信息自己留存


 int  getCurLogFileId(  LOG_HELP_STRUCT  *  pLogHelp  )
{
	 char  buf[256];

	 if  (  !qyGetRegCfg(  pLogHelp->cfg.workKey,  pLogHelp->cfg.curLfIdVal,  buf,  sizeof(  buf  )  ) 
		 &&  atol(  buf  )  ==  QY_LOGFILE2_ID  )
	 {
		 pLogHelp->curLfId  =  QY_LOGFILE2_ID;
		}
	 else
		 pLogHelp->curLfId  =  QY_LOGFILE1_ID;

	 return  pLogHelp->curLfId;

}

 int  getAnotherFileId(  int  fileId  )
{
	 return  (  fileId == QY_LOGFILE1_ID ? QY_LOGFILE2_ID : QY_LOGFILE1_ID  );
}

 char * getLogFileName(  LOG_HELP_STRUCT  *pLogHelp,  int  fileId,  char  *  buf, int  size  )
{
	 char  *  pLogFile  =  NULL;

	 if  (  fileId  ==  QY_LOGFILE1_ID  )  pLogFile  =  pLogHelp->cfg.lf1Name;
	 else  pLogFile  =  pLogHelp->cfg.lf2Name;

	 if  (  lstrlen(  pLogHelp->cfg.workDir  )  +  lstrlen(  pLogFile  )  >=  size  )  {
		 return  NULL;
	 }

	 wsprintf(  buf, "%s%s",  pLogHelp->cfg.workDir,  pLogFile  );
	 return  buf;

}

 void zeroLogFileProcedLen(  LOG_HELP_STRUCT  *  pLogHelp,  int  logFileId  )
{
	 char * pVal  =  NULL;

	 if  (  logFileId  ==  QY_LOGFILE1_ID  ) {
		 pVal  =  pLogHelp->cfg.lf1ProcedLenVal;
		}
	 else
		 pVal  =  pLogHelp->cfg.lf2ProcedLenVal;

	 if  (  qySetRegCfg(  pLogHelp->cfg.workKey,  pVal,  "0"  )  )  {
		 traceLogA(  "Critical error: zeroLogFileProcedLen(  ) ---  qySetRegCfg(  ) failed."  );
	 }
	 return;
}

 void setCurLogFileProcedLen(  LOG_HELP_STRUCT  *  pLogHelp,  unsigned  int  procedLen  )
{
	 char * pVal  =  NULL;
	 char	buf[32];

	 if  (  pLogHelp->curProcedLfId  ==  QY_LOGFILE1_ID  ) {
		 pVal  =  pLogHelp->cfg.lf1ProcedLenVal;
		}
	 else
		 pVal  =  pLogHelp->cfg.lf2ProcedLenVal;
	 sprintf(  buf,  "%d",  procedLen  );

	 if  (  qySetRegCfg(  pLogHelp->cfg.workKey,  pVal,  buf  )  )  {
		 traceLogA(  "Critical error: zeroLogFileProcedLen(  ) ---  qySetRegCfg(  ) failed."  );
	 }
	 return;

}

 int  getLogFileProcedLen( LOG_HELP_STRUCT  *  pLogHelp,  int  procedFileId  )
{
	 int		len		=	0;
	 char  *	pVal	=	NULL;
	 char		buf[255];

	 if  (  procedFileId  ==  QY_LOGFILE1_ID  ) {
		 pVal  =  pLogHelp->cfg.lf1ProcedLenVal;
		}
	 else
		 pVal  =  pLogHelp->cfg.lf2ProcedLenVal;

	 if  (  qyGetRegCfg(  pLogHelp->cfg.workKey,  pVal,  buf,  sizeof(  buf  )  )  )  {
		 len	=	0;		 
		}
	 else
		 len  =  atol(  buf  );

	 return  len;
	 
}


 int  getCurProcedFileId(  LOG_HELP_STRUCT  *  pLogHelp  )
{
	 int			curLogFileId	=		0;
	 int			curProcedFileId	=		0;
	 char		*	pLogFile		=		NULL;
	 char			fileNameBuf[sizeof(  pLogHelp->curProcedLfName )];
	 
	 curLogFileId		=	getCurLogFileId(  pLogHelp  );
	 curProcedFileId	=	getAnotherFileId(  curLogFileId  );

	 pLogFile		=		getLogFileName(  pLogHelp, curProcedFileId,  fileNameBuf,  sizeof(  fileNameBuf  )  );
	 if  (  !pLogFile  )	return  -1;
	 
	 if  (  GetFileAttributes(  pLogFile  )  ==  0xFFFFFFFF  )  {
		 zeroLogFileProcedLen(  pLogHelp,  curProcedFileId  );
		 curProcedFileId	=	curLogFileId;
		 pLogFile  =  getLogFileName(  pLogHelp,  curProcedFileId,  fileNameBuf,  sizeof(  fileNameBuf  )  );
		 if  (  !pLogFile  )  return  -1;
	 }
	 wsprintf(  pLogHelp->curProcedLfName,  "%s",  fileNameBuf  );
	 pLogHelp->curProcedLfId  =  curProcedFileId;

	 return  curProcedFileId;

}



 
 int  imcProcLogFile(  void  *  p,  LOG_HELP_STRUCT  *  pLogHelp  )
{
	CQmaDaemon		*	pDaemon			=	(  CQmaDaemon  *  )p;
	int					curProcedLen;
	QY_COMM_SESSION		tmpSession;

	traceLogA(  "imcProcLogFile(  ): enters."  );

	curProcedLen  =  getLogFileProcedLen(  pLogHelp,  pLogHelp->curProcedLogFileId  );

	int				iErr	=  -1;
	FILE	*		fp		=  NULL;
	char			buf[QY_IMC_MAXLOGLEN + 1];
	int				len;
	int				size;
	int				index	=  0;
	BOOL			bConnected	=	FALSE;
	QY_COMM_RESP	tmpResp;

	 		
	fp  =  fopen(  pLogHelp->curProcedLogFile,  "r"  );
	if  (  !fp  )  {
		traceLogA(  "[%s] can't be open.",  pLogHelp->curProcedLogFile  );
		goto  errLabel;
	}

	if  (  fseek(  fp,  curProcedLen,  SEEK_SET )  )  {
		fseek(  fp,  0,  SEEK_SET  );
		curProcedLen  =  0;
	}

	QY_SOCK		tmpSock;
	
	clearQySock(  &tmpSock  );

	for  (  index  =  0;  ;  index  ++  )  {
		 
		 size  =  sizeof(  buf  );
		 if ( !fgets( buf,  size, fp ) )  break;
		 len = strlen( buf);
		 if ( len < 1 ) continue;
		 if ( len == size - 1 && buf[len - 1] != '\n' ) continue;	// 太长了
		 
		 //  这里添加代码
		 if  (  !bConnected  )  {
			 if  (  qyConnect(  pDaemon->var.cfg.cnt.ip,  pDaemon->var.cfg.cnt.port,  pDaemon->var.cfg.to.iConnect, &tmpSock  )  )  goto  errLabel;
			 bConnected  =  TRUE;
			 
			 if  (  qyImcTellService(  QY_NULL_BARID,  &pDaemon->var.cfg.to,  &tmpSock,  &tmpSession  )  )  goto  errLabel;
			 if  (  qySendCmd(  &tmpSession,  QY_CMD_IMCSENDLOG,  &tmpSock,  &pDaemon->var.cfg.to  )  )	goto  errLabel;			 
		 }

		 if  (  qySendData(  &tmpSession,  buf,  len,  &tmpSock,  &pDaemon->var.cfg.to  )  )  {
			 traceLogA(  "qySendData(  )  failed."  );
			 break;
		 }
		 traceLogA(  "qySendData(  ) OK.!" );

		 curProcedLen  =  ftell(  fp  );
		 traceLogA(  "imcProcLogFile(  ): curProcedLen is %d.",  curProcedLen  );
	}

	if  (  curProcedLen  >=  0 )  setCurLogFileProcedLen(  pLogHelp,  curProcedLen  );

	if  (  qySendEndData(  &tmpSession,  &tmpSock,  &pDaemon->var.cfg.to  )  )  goto  errLabel;
	if  (  qyRecvResp(  &tmpSession,  &tmpSock,  &pDaemon->var.cfg.to,  &tmpResp  )  )  goto  errLabel;
	if  (  memcmp(  tmpResp.head.code,  QY_RCOK,  strlen(  QY_RCOK  )  )  )  goto  errLabel;

	traceLogA(  "all data has been sent."  );

	qyDisconnect(  &tmpSock  );	bConnected	=	FALSE;

	if  (  pLogHelp->curProcedLogFileId  !=  pLogHelp->curLogFileId  )  {
		if  (  feof(  fp  )  )  pLogHelp->waitCnt  ++;
		else	pLogHelp->waitCnt  =  0;
	}

	fclose(  fp  );  fp  =  NULL;

	if  (  pLogHelp->waitCnt >= 5  )  {
		char  buf[QY_MAXPATHLEN + 1];
		// sprintf(  buf,  "%s%s",  pLogHelp->cfg.workDir, getLogFileName(  pLogHelp->curProcedLogFileId  )  );
		getLogFileName(  pLogHelp, pLogHelp->curProcedLogFileId,  buf, sizeof(  buf  )  );

		DeleteFile(  buf  );
		zeroLogFileProcedLen(  pLogHelp,  0  );
	}

	if  (  pLogHelp->curProcedLogFileId  ==  pLogHelp->curLogFileId  )  {
		
		if  (  curProcedLen  > 2000000  )  {
			int fileId = getAnotherFileId(  pLogHelp->curProcedLogFileId  );
			char  buf[256];
			sprintf( buf, "%d", fileId  );
			if  (  qySetRegCfg(  pLogHelp->cfg.rootKey,  QY_IMC_TMPLOGFILEID_VAL, buf  )  )  goto errLabel;
		}

		
	}


	iErr = 0;

errLabel:

	if  (  bConnected  )  {
		qyDisconnect(  &tmpSock  );
	}

	if (  fp  ) fclose(  fp  );

	traceLogA(  "imcProcLogFile(  ): leaves."  );

	return  iErr;

}

  */
 
 
 