
#ifndef  __QYVDEVPROC_H__
#define  __QYVDEVPROC_H__  //  {
  
#include	<vfw.h>

//
#include	"qyCommon.h"
#include	"traceLog.h"
#include	"qyLangCommProc.h"
#include	"qyTCharCommProc.h"
//
#include	"qyCusResPublic.h"
#include	"qyCusResTemp.h"
//
#include	"qyCusGui.h"
//
#include	"qySyncCommProc.h"
#include	"genericQueue.h"

#include	"qyCommCommon.h"
#include	"qyWmComm.h"

#include	"qyCommProc.h"
#include	"qyCommProc_open.h"
#include	"qySyncCommProc.h"
#include	"qnmPcComm.h"
#include	"qnmCommProc.h"
#include	"qyq2.h"
#include	"qyVDevCommProc_open.h"
#include	"qdcCommProc_open.h"
#include	"qnmCommProc_mis.h"

#include	"sms.h"
#include	"comm.h"

#include	"qyVDev.h"


 //  以下为com口做

#include	"qyComPort.h"


typedef  struct  __im_smPkt_t									{
				 unsigned  int									uiType;								//  
				 SM_PKT											smPkt;
				 HWND											hWnd_notify;
				 int											iUsrData;
}		 IM_SM_PKT;









typedef  struct  __comBuf_o_t									{

				 IM_SM_PKT										imSmPkt;						//  转换前
				 //
				 unsigned  char									ucSeqNo;						//  在发长短信时，需要分包。这个为上次发的序号。从1开始
				 unsigned  short								usSent;							//  已发送的字符数。
				 //
				 char											cmd[16];						//  命令串
				 char											pdu[512];						//  PDU串
				 char											ans[128];						//  应答串
				 //
				 char											lastCmglResp[256];				//  因为有时是响应数据是分成2行，所以需要将上一行给记忆了.
				 //
				 unsigned  char									ucbToSendCmd;
				 //
				 char											phoneNo_to_sending[32  +  1];	//  正在发送的目的手机号码
				 //
				 
				 time_t											tLastCmdStart;					//  最后一次命令启动的时间，主要是怕协议出错了，导致程序死了。

				 //
				 
}		 COM_BUF_O;





class  CQyVDevComs												{

public:
		struct													{
				QY_VDEV											common;

				unsigned  short									usLangId;

				struct											{
					GENERIC_Q_CFG								mgrQ;
					GENERIC_Q_CFG								dataQ;
					//
					unsigned  int								uiMaxComs;
					//
					unsigned  char								ucbAutoDel;
					//
				}												cfg;

				QNM_CUSRES_INFO									cusRes;				
				unsigned  char									ucbCusResInited;

				GENERIC_Q										mgrQ;
				GENERIC_Q										dataQ;				//  用来存储要发送的消息。发走一个删一个，顺序进行。

				HANDLE											hThread_mgr;				
				DWORD											dwThreadId_mgr;
				//
				HANDLE											hThread_dlg;		//  2008/01/14		
				DWORD											dwThreadId_dlg;
				//


				BOOL											bQuit;
				BOOL											bStop;
				
				int												iCurIndex;
	
				struct											{					//  2008/01/28, 缺省短信策略。
					unsigned  char								ucbDefaultSmServer;	//  是否缺省发送服务器
					//
					QY_MESSENGER_ID								idInfo_contact;		//  缺省短信接收管理员
					time_t										tLastModifiedTime;
					//
				}												defaultSmPolicy;


				CComPort							*			pPorts;
				COM_BUF_O							*			pBufOs;
				GENERIC_Q							*			pOutputQs;			//  如果有同一个手机号的消息来了，而前面的消息又没有发完，则消息存在这个outputQ中。顺序发送
							
				struct											{					
					unsigned  char								ulbMgrQuit;
				}												status;

		}														m_var;

		//  CComPort											m_Ports[CONST_maxComs];


public:
		CQyVDevComs();
		virtual		~CQyVDevComs();
		

};	


typedef  struct  __ctxThreadVDev_t								{

				 BOOL											bVDevComsReported;
				 BOOL											bSmPolicyRetrieved;
				 BOOL											bPhoneMsgrListAccepted;

}		  CTX_THREAD_vDev;

#define		CONST_str_syncGsmModemInit							_T(  "syncGsm"  )

#define		CONST_uiMaxCnt_sema_mgrQ_vDevComs					1000
#define		CONST_uiMaxQNodes_mgrQ_vDevComs						1100
//
#define		CONST_uiMaxQNodes_dataQ_vDevComs					10000
//

extern  CQyVDevComs  *	pVDev;


int  postMsg2Mgr_vDevComs(  void  *  pVDev,  unsigned  int  uiMsgType,  unsigned  int  uiCliIndex,  char  *  data,  unsigned  int  dataLen  );

BOOL  bComIndexValid(  CQyVDevComs  *  pVDev,  unsigned  int  uiComIndex  );

int  mySendMsg_vDevComs(  LPCTSTR  msgStr,  char  *  fullPhoneNo_to,  unsigned  int  uiComIndex,  HWND  hWnd_notify,  int  iUsrData  );

 LRESULT CALLBACK dlgProc_qyTest(HWND hDlg, UINT message, WPARAM wParam, LPARAM);
 extern "C" DWORD WINAPI threadProc_mgr_vDevComs( LPVOID lpParameter );

 BOOL  bInitGsmModem(  CString  m_strPort,  int  nRate,  BOOL  *  pbComExists,  BOOL  *  pbGsmModem,  char  *  smscBuf,  unsigned  int  uiSmscBufSize,  char  *  modelBuf,  unsigned  int  uiModelBufSize,  HWND  hWnd_test,  int  iPortNo  );


#endif  //  }

