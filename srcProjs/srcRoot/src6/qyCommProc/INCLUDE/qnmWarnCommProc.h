

#ifndef  __QNMWARNCOMMPROC_H__
#define  __QNMWARNCOMMPROC_H__	/*  {  */

#ifdef  __cplusplus
  extern  "C"  {
#endif

typedef  struct  __qnmWarnCfg_t  			{
				 BOOL						bWarnOn;
				 BOOL						bWarnUntilUsrStopIt;
				 unsigned  int				nMaxWarnElapse;
				 //
				 char						popupToWarnStartTime[CONST_qyTimeLen  +  1];	//  2006/06/03
}											QNM_WARN_CFG;


int  getQnmWarnCfg(  void  *  pReserved,  QNM_WARN_CFG  *  pCfg  );
int  clearQnmWarnFlg(  void  *  pReserved  );
int  setQnmWarnInfo(  void  *  pReserved );
int  getQnmWarnInfo(  void  *  pReserved,  char  *  timeBuf,  int  size,  BOOL  *  pbNew  );

typedef  struct  __qnmWarningMsg_t			{
				 unsigned  int				id;
				 unsigned  int				uiType;
				 unsigned  char				ucFlg;
				 unsigned  char				reserved[3];
				 char						localTime[CONST_qyTimeLen  +  1];	//  事件发生时间
				 unsigned  long				ulIp;								//  Ip
				 char						mac0[CONST_qyMacLen  +  1];			//  
				 TCHAR						who[64];
				 TCHAR						des0[256];
}		 QNM_WARNING_MSG;

typedef  struct  __qnmWarningMsgs_t			{
				 unsigned  int				cnt;
				 unsigned  char				ucFlg;
				 QNM_WARNING_MSG			mems[1024];
}		 QNM_WARNING_MSGS;

int  qyhtonQnmWarningMsgs(  QNM_WARNING_MSGS  *  pMsgs  );
int  qyntohQnmWarningMsgs(  QNM_WARNING_MSGS  *  pMsgs  );

#ifdef  __cplusplus
  }
#endif


#endif		/*  {  */

