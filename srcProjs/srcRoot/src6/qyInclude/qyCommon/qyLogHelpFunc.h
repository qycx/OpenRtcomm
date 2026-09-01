
#ifndef  __QYLOGHELPFUNC_H__
#define	 __QYLOGHELPFUNC_H__	/*  {  */

/*
#define		QY_LOGFILEID_VAL						( "lf" )			// 若设为"2"则取TMPLOGFILE2, 
																		// 否则取TMPLOGFILE1

#define		QY_LOGFILE1_PROCEDLEN_VAL				( "lf1L" )
#define		QY_LOGFILE2_PROCEDLEN_VAL				( "lf2L" )

#define		QY_LOGFILE1_ID							1
#define		QY_LOGFILE2_ID							2

#ifndef   __DEBUG__
	#define		QY_LOGFILE1NAME							"~zysm1.tmp"				//	qma的日志文件
	#define		QY_LOGFILE2NAME							"~zysm2.tmp"				//	qma的日志文件
	#define		QMD_LOGFILE1NAME						"~xxsc1.tmp"				//  qmd for police的日志文件
	#define		QMD_LOGFILE2NAME						"~xxsc2.tmp"				//  qmd for police的日志文件
	#define		QMA_TMPPOLICYFILENAME					"~lswa.tmp"					//  qma生成策略文件的临时文件
	#define		QMG_TMPPOLICYFILENAME					"~lswg.tmp"					//  qyMc生成策略文件的临时文件
	#define		QMD_TMPPOLICYFILENAME					"~lswd.tmp"					//  qyMcDaemon生成策略文件的临时文件
	#define		QMA_POLICYFILENAME						"~zsca.tmp"					//  qma生成的策略文件
	#define		QM_POLICYFILENAME						"~zscl.tmp"					//  qyMc生成的策略文件
	#define		QMD_POLICYFILENAME						QM_POLICYFILENAME			//	qmd for police的策略文件
	#define		QMD_SENDINGFILENAME						"~fscg.tmp"					//	qmd for police的发送临时文件
	#define		QMD_RETRIEVECFGFILENAME					"~mhmt.tmp"					//  qmd for police获取配置的临时文件
	#define		QMD_FORBAR_LOGFILE1NAME					"~xqgg1.tmp"				//	qmd for bar的日志文件
	#define		QMD_FORBAR_LOGFILE2NAME					"~xqgg2.tmp"				//	qmd for bar的日志文件
	#define		QMD_FORBAR_SENDINGFILENAME				"~jjfs.tmp"					//	qmd for bar的发送临时文件
	#define		QMD_FORBAR_RETRIEVECFGFILENAME			"~mhmt.tmp"					//  qmd for bar获取配置的临时文件
	#define		QMD_FORBAR_POLICYFILENAME				"~mhjt.tmp"					//  qmd for bar的策略文件
#else
	#define		QY_LOGFILE1NAME							"qma1.log"					//	qma的日志文件
	#define		QY_LOGFILE2NAME							"qma2.log"					//	qma的日志文件
	#define		QMD_LOGFILE1NAME						"qmd1.log"					//  qmd for police的日志文件
	#define		QMD_LOGFILE2NAME						"qmd2.log"					//  qmd for police的日志文件
	#define		QMA_TMPPOLICYFILENAME					"ATmpPolicy.log"			//  qma生成策略文件的临时文件
	#define		QMG_TMPPOLICYFILENAME					"GTmpPolicy.log"			//  qyMc生成策略文件的临时文件
	#define		QMD_TMPPOLICYFILENAME					"DTmpPolicy.log"			//  qyMcDaemon生成策略文件的临时文件
	#define		QMA_POLICYFILENAME						"APolicy.log"				//  qma生成的策略文件
	#define		QM_POLICYFILENAME						"Policy.log"				//  qyMc生成的策略文件
	#define		QMD_POLICYFILENAME						QM_POLICYFILENAME			//	qmd for police的策略文件
	#define		QMD_SENDINGFILENAME						"Sending.log"				//	qmd for police的发送临时文件
	#define		QMD_RETRIEVECFGFILENAME					"RetrCfg.log"				//  qmd for police获取配置的临时文件
	#define		QMD_FORBAR_LOGFILE1NAME					"qmdForBar1.log"			//	qmd for bar的日志文件
	#define		QMD_FORBAR_LOGFILE2NAME					"qmdForbar2.log"			//	qmd for bar的日志文件
	#define		QMD_FORBAR_SENDINGFILENAME				"BarSending.log"			//	qmd for bar的发送临时文件
	#define		QMD_FORBAR_RETRIEVECFGFILENAME			"BarRetrCfg.log"			//  qmd for bar获取配置的临时文件
	#define		QMD_FORBAR_POLICYFILENAME				"BarPolicy.log"				//  qmd for bar的策略文件
#endif


#define		QY_MAX_LOGFILE_SIZE						2000000


typedef  struct  __logHelpStruct_t  {

				 BOOL								bInited;		
	
				 struct {
						char						workKey[QY_MAXKEYLEN + 1];
						char						workDir[QY_MAXPATHLEN + 1];
																		//  这用的val是指注册表里的配置名
						char						curLfIdVal[8];		//	QY_IMC_TMPLOGFILEID_VAL
						char						lf1ProcedLenVal[8];	//	QY_IMC_TMPLOGFILE1PROCEDLEN_VAL
						char						lf2ProcedLenVal[8];	//  QY_IMC_TMPLOGFILE2PROCEDLEN_VAL
						char						lf1Name[16];
						char						lf2Name[16];

						unsigned  long				maxLogFileSize;		//  QY_IMC_MAXTMPLOGSIZE
				 }									cfg;

				 int								curLfId;
				 int								curProcedLfId;
				 char								curProcedLfName[QY_MAXPATHLEN  +  1];

				 char								waitCnt;			//  在文件切换后，若文件已到文件尾，则等待5次后将文件删除。

}		 LOG_HELP_STRUCT;

*/

//  int		initLogHelp(  char * workKey, char * workDir, char * logFile1, char * logFile2, LOG_HELP_STRUCT * pLogHelp  );
//  void	exitLogHelp(  LOG_HELP_STRUCT  *  pLogHelp  );
//  int		getCurProcedFileId(  LOG_HELP_STRUCT  *  pLogHelp  );
//  void	setCurLogFileProcedLen(  LOG_HELP_STRUCT  *  pLogHelp,  unsigned  int  procedFileId  );
//  void	zeroLogFileProcedLen(  LOG_HELP_STRUCT  *  pLogHelp,  int  logFileId  );
//  int		getCurLogFileId(  LOG_HELP_STRUCT  *  pLogHelp  );
//  char *	getLogFileName(  LOG_HELP_STRUCT  *pLogHelp,  int  fileId,  char  *  buf, int  size  );
//  int		getLogFileProcedLen( LOG_HELP_STRUCT  *  pLogHelp,  int  procedFileId  );



#endif

