

#ifndef  __statusDaemon_h__
#define  __statusDaemon_h__	//  {


#include	<vfw.h>
#include	<Wincrypt.h>

#include	"qmCommon.h"

#include	"qyCommCommon.h"
#include	"qyDbCommon.h"
#include	"qyGuiCommon.h"

#include	"qyTCharCommProc.h"	//  2005/11/01

#include	"qnmGuiCommProc.h"
#include	"qnmCustomGui.h"

#include	"qyMsgFunc.h"
#include	"mtSock_iOCP.h"

#include	"asrWMonCfg.h"

#include	"qmCrypt.h"

//
#include	"qyGenericDaemon.h"

//
class  CQyStatusDaemon:public CQyGenericDaemon
{
public:
	CQyStatusDaemon( );
	virtual ~CQyStatusDaemon(  );

	struct  {			
			//
			struct				{
				SOCK_TIMEOUT	to;
			}					cfg;

	}		m_var;

	//
	virtual  int	init(  );
	virtual  int	start(  );
	virtual  int	stop(  );
	virtual  void	exit(  );

	virtual  int	getInitialCfg(  );
	BOOL			bChkBeforeRunning(  );
	virtual  int	refreshCfg(  );



};


//
typedef  struct  __qmdSession_qyStatus_t					{
				 
				 QY_COMM_SESSION				comm;

#if  0
				 ENC_CTX_session				commEncCtx;							//  2008/06/08
				 unsigned  char					ucbEncInited;

				 //
				 unsigned  int					bufType;
				 union							{
				 	 char						buf[1024];							//  提供会话过程中的缓冲，比如，可存放返回到受控端的注册提示  
					 QWM_REG_HINT				hint;
				 }								bufU;
				 TCHAR							cmdDesc[256];						//  2015/09/04. //128];						//  2005/06/29
				 //
				 struct							{
					 unsigned  int				uiType;								//  缓冲类型
					 unsigned  int				unitSize;							//  信息单元数据大小
					 unsigned  int				maxCnt;								//  最多可容纳信息单元数
					 unsigned  int				cnt;								//	现在容纳的信息单元数
					 char  *					p;									//  信息单元存放区
				 }								internalBuf;						//  2007/02/15

				 HANDLE							hMutex_syncAssetMgr;

				 unsigned  char					ucbGuiTalk;							//  2006/12/10
		
				 //QY_SERVICE_INFO			*	pServiceInfo;

				 //
				 void						*	pQMemObj;							//  在管理队列中的对应节点。应该是永久性的
				 void						*	pClient;							//  客户端信息, 可以是临时性的。2007/04/01
																					//  以上2个地址不可能是一个对象。

				 //
				 unsigned  int					uiChannelType;						//  2007/07/08
				

				 //
				 unsigned  char					ucbWebSessFirstComm;				//  是否webSession刚开始的第一个通信
				 unsigned  char					ucbLastMsgInSess;					//  是否已经处理了队列中最后一个消息。那么以后，就不再把消息往发送队列放了. 2007/12/11
                 

				 //
				 TCHAR							whoBuf_showInfo_serv[32];			//  
				 TCHAR							whoBuf_showInfo_cli[32];
				 TCHAR							whereBuf_showInfo[32];				//  用来在showInfo时提供清晰的提示, 2007/05/05


				 struct							{
					 QY_MESSENGER_ID			idInfo;
				 }								debugInfo;

				 //  2015/09/04
				 DWORD							dwLastTickCnt_tooBigElapse;
#endif

}		 QMD_SESSION_qyStatus;

//
 extern  "C"  int  qmdServWork_qyStatus(  void  *  pp,  int  sockFd,  void  *  p2  );



#endif  //  }



