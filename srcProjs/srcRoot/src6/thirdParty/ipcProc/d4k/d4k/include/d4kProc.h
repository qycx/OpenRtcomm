
#ifndef  __dhProc_h__
#define  __dhProc_h__	//  {

//
#include	<mmsystem.h>
#include	"qySyncObj.h"
#include	"qmOpenCommon.h"
#include	"genericqueue.h"
#include	"qisPipe_open.h"

//#include	"dyn_qisPublic.h"

#include	"qisOnvifCommProc_open.h"
#include	"ipcProc_open.h"
#include <myCmdParams_open.h>

extern int printLogChar(const char* log);
extern int printLog(TCHAR* log);

//
typedef  struct {
	TCHAR		installDir[256];
}  DhProcCfg;


//
class  DhProc {
	
	//
public:
	struct {

		//
		AppParams_ipcProc	appParams;

		//
		DhProcCfg  cfg;

		//
		HWND  hMainWnd;


		//
		struct {
			//
			QIS_pipe* pQisPipe;				// cli

			//
			bool  bMsgExists;

			//
			DWORD	dwLastTickCnt_recvd;
		}	qm;

		//
		int		g_tn;

		//
		struct {
			//
			QIS_pipe* pQisPipe;				// serv

			//
			bool  bMsgExists;

			//
			DWORD	dwLastTickCnt_recvd;

			//
			IpcProcTool		tool;

		}	dhListIp, dhDeviceControl, dhPtz;							//  listIp, 




		//
		NvrInfo			nvrInfo;

		//
		bool  m_bAutoClose_ifToolLongNoRecvd_qm;

		//
		//bool  m_bClose1;

		//
		void  *  pShowInfoStruct;

		//
	} m_var;


public:
	//
	DhProc() {
		memset(&m_var, 0, sizeof(m_var));
	}
	~DhProc() {

	}


	//
};

//
extern DhProc  gBuf_dh;


//
int  dh_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1);

int  dh_listIp_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1);
int  dh_deviceControl_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1);
int  dh_ptz_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1);


//
#endif  //  }


