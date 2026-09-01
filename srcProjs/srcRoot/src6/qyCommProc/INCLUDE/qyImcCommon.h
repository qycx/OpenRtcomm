
#ifndef  __QYIMCCOMMON_H__
#define  __QYIMCCOMMON_H__	/*  {  */


typedef  struct  __qyImcInfoHead_t  {
		   UCHAR	magic[QY_INFO_FILE_MAGIC_LEN];
		   UINT4	version;
}		 QY_IMC_INFO_HEAD;
typedef  struct  __qyImcCtlInfo_t {
		   UCHAR	flg;
}		 QY_IMC_CTL_INFO;
typedef  struct  __qyImcInfoData_t {
		   QY_IMC_CTL_INFO		ctlInfo;
}		 QY_IMC_INFO_DATA;
typedef  struct  __qyImcInfoTail_t {
		   UCHAR	tailMagic[QY_INFO_FILE_MAGIC_LEN];
}		 QY_IMC_INFO_TAIL;

typedef  struct  __qyImcInfo_t {
		   QY_BUF	head;
		   QY_BUF	data;
		   QY_BUF	tail;
}		 QY_IMC_INFO;

typedef  struct  __qyImcEnv_t {
		   DWORD dwTotalPhys;
}		 QY_IMC_ENV;

typedef  struct  __qyImcStatus_t {
		   BOOL bInited;
		   BOOL bInfoSet;
		   BOOL bLogContextInited;
		   BOOL	bIeActive;
}		 QY_IMC_STATUS;

typedef  struct  __qmaImcCfg_t  {
				 char	rootKey[QY_MAXKEYLEN  +  1];
				 char	installDir[QY_MAXPATHLEN  +  1];
				 char	workDir[QY_MAXPATHLEN  +  1];
				 int	infoFileSize;
				 BOOL	bDictRefreshed;				
}		 QMA_IMC_CFG;

typedef  struct  __qmaImcStruct_t  {

				 QY_IMC_ENV		env;
				 QMA_IMC_CFG	cfg;
				 QY_IMC_STATUS	status;

				 int			curLogFileId;
				 int			curProcedLogFileId;
				 char			curProcedLogFile[QY_MAXPATHLEN  +  1];

				 char			waitCnt;	//  在文件切换后，若文件已到文件尾，则等待5次后将文件删除。

				 HANDLE			hMap;
				 QY_BUF			sharedBuf;
	
				 QY_IMC_INFO	qI;
				 HANDLE			hInfoFile;		//	用于共享内存的输入句柄
				 
				 HANDLE			hIeLckFile;		//  用于判断ie全关闭时更新url列表
				 
				 int			ieCnt;
				 time_t			timeOfIeCnt;		//  测出ieCnt变化的时间

}		 QMA_IMC_STRUCT;



int getImcEnv( QY_IMC_ENV *pEnv );
int  setQmInfo(  BOOL  bCreator, char * workDir,  char * policyFile, BOOL * pbDictRefreshed,  QY_IMC_INFO * pQI, QY_BUF * pSharedBuf  );
void resetQmInfo( QY_BUF *pSharedBuf );



#endif	/*  }  */

