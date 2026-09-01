
#ifndef  __dhDeviceControlProc_h__
#define  __dhDeviceControlProc_h__	//  {

//
//
//
#include	<mmsystem.h>
#include	"qySyncObj.h"
#include	"qmOpenCommon.h"
#include	"genericqueue.h"
#include	"qisPipe_open.h"

#include    <string>

//#include	"dyn_qisPublic.h"

#include	"qisOnvifCommProc_open.h"
#include "string.h"

#include	"myCmdParams_open.h"
#include	"ipcProc_open.h"


struct IpcInfoDef {
	std::string name;
	int         id;
	std::string ip;
};


class DhDeviceControlProc {
public:
	struct {

		//
		AppParams_ipcProc	appParams;

		//
		QIS_pipe* pQisPipe;


		DWORD  dwLastTickCnt_recvd;

		//
		HWND  hMainWnd;

		//
		bool  bErr;

		//
		bool  m_bAutoClose_ifToolLongNoRecvd_qm;

		//
		void* pShowInfoStruct;

		bool	m_bDone_nvrInfo;

	}  m_var;

	//
	DhDeviceControlProc()
	{
		memset(&m_var, 0, sizeof(m_var));
	}


};


//
extern  DhDeviceControlProc gBuf_dhDeviceControl;

int  dhDeviceControl_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1);



#endif  //  }


