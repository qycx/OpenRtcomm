

#ifndef  __QWMSVRCHKCOMMPROC_H__
#define	 __QWMSVRCHKCOMMPROC_H__	//  {

#ifdef  __cplusplus
  extern  "C"  {
#endif


//  2005/05/09, 因为文件不能包含在diskio中，所以再这里再次定义，注意
#define		CONST_qyEventType_secChk_diskFileDel				909				//  检查已删除的磁盘文件


#define		CONST_numOfAbcTable					26


typedef  struct  __diskDrvInfo_			{
				 unsigned  char			ucVolName;
				 unsigned  char			fsTypeBuf[64];
}		 DISKDRV_INFO;


typedef  struct  __chkDiskStruct_t		{
				 DISKDRV_INFO			diskDrvs[CONST_numOfAbcTable  +  1];
 				 int					iDiskNum;								//  磁盘个数
 				 void			*		pSubThreadInfo;
 				 char					curDrvName[2];
 				 int					nDent;	//  用来作调试用
 				 BOOL					bTraceLog;
				 unsigned  char			ucbSecChkQuickly;
}		 CHK_DISK_STRUCT;



int  getDiskDrvInfo(  CHK_DISK_STRUCT  *  pChkDisk  );

int  displayChkDiskEvent(  void  *  pSubThreadInfoParam,  
								   long		lEventType,
						  		   char  *  localEventTime,		//  事件的本地时间
								   char  *  usrName,
								   char  *  des0,					//  事件描述
								   char  *  des1,					//  事件描述1, 2004/03/14												
								   char  *  des2			  );		//  事件描述2


#ifdef  __cplusplus
  }
#endif

#endif	//  }
