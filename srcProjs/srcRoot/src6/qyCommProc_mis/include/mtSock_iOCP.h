


#ifndef  __MTSOCKIOCP_H__
#define  __MTSOCKIOCP_H__	//  {

#include	"qyMtSock.h"
#include	"qyq2.h"

//
#define		CONST_mutexName_mtSockCliInfo										"mtSockCliInfo"

//
#define		CONST_uiMaxQNodes_perSocketContextInputQ							160				//  2007/08/16

//
#define		CONST_uiMaxQNodes_perSocketContextOutputQ							160  *  10		//  160  *  10				//  2007/08/16
#define		CONST_uiQNodes_warningInterval_perSocketContextOutputQ				160				//  20				//  2008/03/21				

//
#define		CONST_uiMaxQNodes_sendOkQ											200				//  2015/08/18

//
#define		CONST_uiMaxQNodes_perSocketContextInCacheQ							3  *  10				//  2008/05/25, Õâ¸ö½ÚµãÊýÊÇÖ¸²»Í¬µÄÏûÏ¢.²»ÊÇÖ¸·Ö°ü.ËùÒÔºÍÏÂÃæ²»Ò»Ñù.²»¹ý,²»Ó¦¸ÃÊÇÕâ¸ö¸ÅÄî.½«À´Ó¦¸Ã¸Ä³É·Ö°ü.
//
#define		CONST_uiMaxQNodes_perSocketContextOutCacheQ							100  *  3				//  100  *  10				//  200				//  2015/08/27	//  64		//  2008/05/27, Êä³ö»º´æ½Úµã¸öÊý.
#define		CONST_uiQNodes_warningInterval_perSocketContextOutCacheQ			20						//50  				//  100				//  2008/03/21				

//
#define		CONST_uiMaxCnt_sema_syncSessionOnOff								50

//
#define		CONST_uiMaxQNodes_ctrl_toSendQ										5000	//500				//  2015/09/02

//
#define		CONST_mutexName_ctrl_toSendQ										_T(  "ctrl_toSendQ"  )

//
typedef  struct  __mtSockCliInfo_iOCP_t				{

				 //  int							cliSockFd;							 
				 SOCKET								cliSockFd;									//  2014/02/07
				 BOOL								bUsed;

				 TCHAR								mutexName_syncPerSocketContext[32  +  1];	//  

				 CMutexRW						*	pRw_syncSessionOnOff1;						//  

				 //
				 //GENERIC_Q							inputQ_cs;								//  2015/08/23. client comm with server directly
				 QY_Q2								inputQ2_cs;
				 BOOL								bInited_inputQ_cs;
				 //
				 //  GENERIC_Q							inputQ_route;							//  2015/08/23. clent send it to other clents
				 QY_Q2								inputQ2_route;
				 BOOL								bInited_inputQ_route;

				 //
				 GENERIC_Q							outputQ;									//  2007/05/03, 
				 BOOL								bInited_outputQ;							//  2007/08/15, 
				 
				 //
				 GENERIC_Q							sendOkQ;									//  2015/08/25
				 BOOL								bInited_sendOkQ;

				 //  2015/08/27
				 GENERIC_Q							inCacheQ;									//  CONST_commFlg_moreData			
				 BOOL								bInited_inCacheQ;	
				 //
				 //  GENERIC_Q						outCacheQ;									//  cliInfo.outputQ
				 QY_Q2								outCacheQ2;
				 BOOL								bInited_outCacheQ;

				 //
				 unsigned  int						uiSessionId;
				 //
				 struct								{
					 //  
					 unsigned  __int64				ui64Id_cli;
					 unsigned  int					uiChannelType;
					 //
					 unsigned  int					uiSizePerSnd_media;
					 
					 //  2015/08/25
					 BOOL							bAdmin1;
					 //
					 unsigned  short				usLastReqCode_i;
					 unsigned  short				usLastRespCode_i;

					 //  2015/08/25
					 TCHAR							whoBuf_showInfo_serv[32];			//  
					 TCHAR							whoBuf_showInfo_cli[32];
					 TCHAR							whereBuf_showInfo[32];				//  用来在showInfo时提供清晰的提示, 2007/05/05

					 //
					 BOOL							bMgrRespGot;

				 }									sessionData;

				 //  2015/08/28
				 struct								{
					 int							iUnused;
				 }									status;

				 //
				 BOOL								bSync_input_cs_mgr;							//  mtMgr读取时，用此标志位来保证同时只有一个线程在读
				 BOOL								bSync_input_route_mgr;						//  mtMgr读取时，用此标志位来保证同时只有一个线程在读
				 //
				 BOOL								bSync_sendFinished_mgr1;						//  mtMgr用来保证只有一个线程在sendFinished
				 //
				 //BOOL								bSync_send_iocp;							//  iocp用来确保只有一个线程处理procMsgFromMgr

				 //
				 __int64							i64StartTime_base;

				 //
}		 MT_SOCK_CLIINFO_IOCP;


//
typedef  struct  __mt_sock_iOCP_t					{

				 MACRO_mtSock_common

				 TCHAR								mutexName_syncModifyingObjInfo[64  +  1];
					 
				 HANDLE								hIocp;

				 HANDLE								hEventAccept;
				 LPFN_ACCEPTEX						lpfnAcceptEx;
				 LPFN_GETACCEPTEXSOCKADDRS			lpfnGetAcceptExSockAddrs;		//  2007/04/19
				 //
				 void						*		pPerSocketContexts_serv;		//  2007/04/15
				 				 
				 MT_SOCK_CLIINFO_IOCP				cliInfos[MAX_CONNS];			//  2007/04/16
				 void						*		pPerSocketContexts[MAX_CONNS];	//  2007/04/15
				 //void						*		pSessions[MAX_CONNS];			//  2007/04/15				
				 
				 //
				 HANDLE								hCliThreads[MAX_cliThreads_iocp];	//[MAX_CONNS];
				 DWORD								dwThreadIds[MAX_cliThreads_iocp];	//[MAX_CONNS];			//  2007/03/29
				 
				 //  2015/09/02
				 struct								{
					 HANDLE							hThread;
					 DWORD							dwThreadId;

					//
					long							nCnt_procMsgFromMgr;

					//
					GENERIC_Q						ctrl_toSend_q;
					BOOL							bInited_ctrl_toSend_q;

				 }									ctrl_toSend;
				 
				 //	
				 unsigned  int						uiMilliSeconds_mutex_syncCli;	//  2007/04/23

				 //		
				 unsigned  int						uiMilliSeconds_mutex_syncPerSocketContext;	//  2007/05/03

				 //	
				 RW_lock_param						rwLockParam;								//  2009/05/13
#if  0
				 unsigned  int						uiMaxCnt_sema;		
				 unsigned  int						uiInitCnt_sema;
				 unsigned  int						uiMilliSeconds_mutex_r;
				 unsigned  int						uiMilliSeconds_sema_r;
				 unsigned  int						uiMilliSeconds_mutex_w;
				 unsigned  int						uiMilliSeconds_sema_w;
#endif

				 //
				 long								nBusyConns;									//  2007/08/14
				 long								nFreeCliThreads;							//  2015/08/26

				 struct								{											//  2011/01/10
					 IM_NET_STAT					netStat_admin;
					 IM_NET_STAT					oldNetStat_admin;
				 }									status;

}		MT_SOCK_IOCP;




typedef enum	_enumIoOperation					{
				CONST_io_null,
				CONST_io_read,					
				CONST_io_write,
				CONST_io_accept,
				CONST_io_timeout	
}	    ENUM_IO_OPERATION;


typedef  struct  __perIoContext_t					{
				 OVERLAPPED							overlapped;
				 WSABUF								wsaBuf;
	 			 DWORD								nTotalBytes;
				 DWORD								dwIoBytes;
				 ENUM_IO_OPERATION				    ioOperation;
				 QY_MSG_HEAD_h						msgHead;
				 unsigned  short					usCode_org;							//  2007/05/03, 
				 //  unsigned  char						ucbIoInited;
				 unsigned  char						ucbCommHeadDone;
				 unsigned  char						ucbDataDone;
				 char								buf[CONST_dataBufSize_iocp];				 
}		 PER_IO_CONTEXT,  *  PPER_IO_CONTEXT;

//  
#define		MACRO_memset_perIoContext(  ioContext  )	memset(  &(  ioContext  ),  0,  offsetof(  PER_IO_CONTEXT,  buf  )  );

typedef  struct  __perSocketContext_t				{	

				 SOCKET								sockFd;								//  2012/02/25

				 unsigned  int						uiCliIndex;							//  mtSock index
				 PER_IO_CONTEXT						inputContext;
				 PER_IO_CONTEXT						outputContext;
				 
				 //
				 //unsigned  int						uiSessionId;
				 char								clientIp[CONST_qyMaxIpLen  +  1];	//  2007/04/01

				 //
				 char						*		pMsgInput_cache;					//  
		 
																						//  
																						//  
				 struct								{
				 																		
#if  0
					 GENERIC_Q						inCacheQ_cli;						//  CONST_commFlg_moreData			
					 BOOL							bInCacheQInited;
#endif
					 //
					 GENERIC_Q						outCacheQ;							//  cliInfo.outputQ
					 BOOL							bOutCacheQInited;
				 }									cli;								//  2015/08/27. 只用在客户端

				 //
				 struct								{

					 //
					 char							unused;
				 }									debugInfo;

				 struct								{									//  2011/01/10
					 struct							{
						 DWORD						dwTickCnt_accepted;
						 //
						 unsigned  char				ucCnt_timeout;
					 }								accept;
					 struct							{
						 DWORD						dwTickCnt_recv_start;				//  开始读取的时间，一般都是等待状态.
						 DWORD						dwTickCnt_recv_first;				//  读到第一个字节的时刻
						 //  DWORD						dwTimeInMs_recv;				//  
						 DWORD						dwTickCnt_recvd;					//  
						 DWORD						dwTickCnt_recvd_end;
						 //
						 unsigned  char				ucCnt_timeout;
					 }								recv;
					 struct							{
						 DWORD						dwTickCnt_snd_start;				//  
						 //  DWORD						dwTimeInMs_snd;					//  
						 //
						 unsigned  char				ucCnt_timeout;
					 }								snd;
					 
					 //
					 unsigned  char					ucbSending;							//  2011/01/25
					 
					 //
					 IM_NET_STAT					netStat;
					 IM_NET_STAT					oldNetStat;
				 }									status;


}		 PER_SOCKET_CONTEXT,  *  PPER_SOCKET_CONTEXT;


//
int initQyMtSock_iocp( char *servIp, unsigned short port, MT_SERVWORK * pServWork, void * pParentParam,  int  iType_pParentParam,  void  **  ppMtSock  );
void exitQyMtSock_iocp(  void  *  pMtSockParam  );

BOOL  bCliIndexValid(  MT_SOCK_IOCP  *  pMtSock,  unsigned  int  uiCliIndex  );

//  void  setIoTime(  MT_SOCK_IOCP  *  pMtSock,  unsigned  int  uiCliIndex,  ENUM_IO_OPERATION  io,  BOOL  bStart  );
void  setIoTime(  PER_SOCKET_CONTEXT  *  p,  ENUM_IO_OPERATION  io,  BOOL  bStart  );

int  getChannelStatus(  MT_SOCK_IOCP  *  pMtSock,  int  uiCliIndex,  IM_NET_STAT  *  pStat,  CHANNEL_status_io  *  pIo  );

//
#if  1	//  def  __DEBUG__
int  qyRecvMsg_iocp(  MT_SOCK_IOCP  *  pMtSock,  PER_SOCKET_CONTEXT  *  pPerSocketContext,  PER_IO_CONTEXT  *  pIoContext,  unsigned  char  *  pucbDataDone  );
int  qySendMsg_iocp(  MT_SOCK_IOCP  *  pMtSock,  PER_SOCKET_CONTEXT  *  pPerSocketContext,  PER_IO_CONTEXT  *  pIoContext,  unsigned  char  ucFlg,  unsigned  short  cmdCode,  unsigned  short  usCode_org,  time_t  uiStartTime,  unsigned  int  uiTranNo,  unsigned  short  usSeqNo,  char  *  data,  unsigned  int  dataLen  );
#endif

int  qyRecvMsg_iocp(  PER_SOCKET_CONTEXT  *  pPerSocketContext,  QY_COMM_SESSION  *  pSession,  IM_NET_STAT  *  pNetStat_admin,  PER_IO_CONTEXT  *  pIoContext,  unsigned  char  *  pucbDataDone  );
int  qySendMsg_iocp(  PER_SOCKET_CONTEXT  *  pPerSocketContext,  QY_COMM_SESSION	*	pSession,  IM_NET_STAT  *  pNetStat_admin,  PER_IO_CONTEXT  *  pIoContext,  unsigned  char  ucFlg,  unsigned  short  cmdCode,  unsigned  short  usCode_org,  time_t  uiStartTime,  unsigned  int  uiTranNo,  unsigned  short  usSeqNo,  char  *  data,  unsigned  int  dataLen  );



//
extern  "C"  int  getRemoteIpBySocket_iocp(  MT_SOCK_IOCP  *  pMtSock,  PER_IO_CONTEXT  *  pIoContext_servSock,  char  *  remoteIp,  unsigned  int  size  );


int  getMutexName_syncCli(  unsigned  int  uiCliIndex,  char  io,  TCHAR  *  mutexName_syncCli,  unsigned  int  size  );

//
int  postMsg2Mgr(  MT_SOCK_IOCP  *  pMtSock,  unsigned  int  uiMsgType,  unsigned  int  uiCliIndex,  unsigned  int  uiChannelType,  unsigned  int  uiSessionId,  unsigned  char  ucFlg,  unsigned  short  usCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  short  usSeqNo,  char  *  data,  unsigned  int  dataLen,  void  *  pMIS_MSGU_buff  );

//
BOOL  closeClient(  MT_SOCK_IOCP  *  pMtSock,  unsigned  int  uiCliIndex,  BOOL  bGraceful,  void  *  pMIS_MSGU_buff  );



#endif  //  }




