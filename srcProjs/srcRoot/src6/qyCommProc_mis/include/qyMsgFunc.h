

#ifndef  __QYMSGFUNC_H__
#define  __QYMSGFUNC_H__  //  {

//
#include	"ctxCaller.h"


#ifdef  __cplusplus
 extern  "C"  {
#endif

//  QY_COMM_HEAD
//
#if  0	//  2011/01/25.
typedef  struct  __qyMsgHead_t						{
				 unsigned  short					usCode;				// 
				 unsigned  char						ucFlg;				//  2007/04/22, 
				 char								reserved[1];		//  
				 unsigned  short					usLen;				//  
				 char								reserved1[2];		//  
				 __int64							i64StartTime;		//  2007/05/07, 
				 unsigned  int						uiTranNo;			//  2007/05/02
				 unsigned  int						uiSeqNo;			//  2007/05/02
}		 QY_MSG_HEAD_023523;
#endif


#if  0
//  2011/01/25
typedef  struct  __qyMsgHead_t						{
				 unsigned  short					usCode;				// 
				 unsigned  char						ucFlg;				//  2007/04/22
				 char								reserved[1];		//  
				 unsigned  int						uiLen;				//  
				 __int64							i64StartTime;		//  2007/05/07, 
				 unsigned  int						uiTranNo;			//  2007/05/02
				 unsigned  short					usSeqNo;			//  2007/05/02
				 char								reserved1[2];		//  				 
}		 QY_MSG_HEAD;
#endif 


//
//#define  __USE_old_msgHead_n__

//
#ifdef  __USE_old_msgHead_n__

//
typedef  struct  __qyMsgHead_h_t {
	unsigned  short					usCode;				// 
	unsigned  char						ucFlg;				//  2007/04/22
	char								reserved[1];		//  
	unsigned  int						uiLen;				//  
	__int64							i64StartTime;		//  2007/05/07, 
	unsigned  int						uiTranNo;			//  2007/05/02
	unsigned  short					usSeqNo;			//  2007/05/02
	char								reserved1[2];		//  				 
}		 QY_MSG_HEAD_h;

//
typedef  struct  __qyMsgHead_n_t {

	//
	unsigned  short					usCode;				// 
	unsigned  char						ucFlg;				//  2007/04/22
	char								reserved[1];		//  
	unsigned  int						uiLen;				//  
	__int64							i64StartTime;		//  2007/05/07, 
	unsigned  int						uiTranNo;			//  2007/05/02
	unsigned  short					usSeqNo;			//  2007/05/02
	char								reserved1[2];		//  			


}		 QY_MSG_HEAD_n;

#else

//
typedef  struct  __qyMsgHead_h_t {
	unsigned  short					usCode;				// 
	unsigned  char						ucFlg;				//  2007/04/22
	char								reserved[1];		//  
	unsigned  int						uiLen;				//  
	__int64							i64StartTime;		//  2007/05/07, 
	unsigned  int						uiTranNo;			//  2007/05/02
	unsigned  short					usSeqNo;			//  2007/05/02
	char								reserved1[2];		//  				 

	//
	int									l3_elapse;
	__int64								dbg_i64StartTime;


	//
}		 QY_MSG_HEAD_h;

//
//#define  __USE_dbg_i64StartTime__

//
#ifdef  __USE_atCommVer_1__
//
typedef  struct  __qyMsgHead_n_t {

	//
	unsigned  char						usCode_buf[2];				// 
	unsigned  char						ucFlg_buf[1];				
	unsigned  char						uiLen_buf[4];				//
	char								l3_elapse_buf[3];		
	unsigned  char						uiTranNo_buf[4];			
	unsigned  char						usSeqNo_buf[2];				

	//
#ifdef  __USE_dbg_i64StartTime__
	//char								dbg_i64StartTime_buf[8];
#endif 

}		 QY_MSG_HEAD_n;
#else

#define		QY_MSG_HEAD_n		AT_MSG_HEAD_n

#endif 


#endif 







//
int  qyWaitForRead(  int  fd,  int  timeout  );
int  qyWaitForWrite(  int  fd,  int  timeout  );


int  qyRecvMsg(  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo,  QY_MSG_HEAD_h * pMsgHead,  char  *  dataBuf,  unsigned  int  bufSize  );
int  qySendMsg(  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo,  unsigned  char  ucFlg,  unsigned  short  cmdCode,  time_t  uiStartTime,  unsigned  int  uiTranNo,  unsigned  short  usSeqNo,  char  *  data,  unsigned  int  dataLen  );



#define		MACRO_prepareForTran(  )							time_t  tStartTran;  unsigned  int	uiTranNo;  mytime(  &tStartTran  );  if  (  (  uiTranNo  =  getuiNextTranNo(  0,  0,  0  )  )  ==  -1  )  traceLogA(  (char*)"getNextuiTranNo failed."  );


//  int  qyTellService_msg(  unsigned  int  serviceId,  char * version,  unsigned  short  usCmd,  void  *  pCommEncCtx,  char * data,  int dataLen,  QY_SOCK * pSock,  SOCK_TIMEOUT * pTo,  QY_COMM_SESSION * pSession );
int  qyTellService_msg(  unsigned  int  serviceId,  char * version,  void  *  pCommEncCtx,  __int64  i64StartTime_base,  unsigned  short  usCmd,  time_t  tStartTime,  unsigned  int  uiTranNo,  char * data,  int dataLen,  QY_SOCK * pSock,  SOCK_TIMEOUT * pTo,  QY_COMM_SESSION * pSession );
void  qnmCloseSession_msg(  CTX_caller  *  pCtxCaller, QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo,  LPCTSTR  hint  );

#ifdef  __cplusplus
 }
#endif



#endif  //  }


