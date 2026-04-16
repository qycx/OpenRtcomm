

#pragma once

//
//
#include	<mmsystem.h>
#include	"qySyncObj.h"
#include	"qmOpenCommon.h"
#include	"genericqueue.h"
#include	"qisPipe_open.h"

//#include	"dyn_qisPublic.h"

#include	"qisOnvifCommProc_open.h"
#include "string.h"

#include	"myCmdParams_open.h"
#include	"ipcProc_open.h"





class DhPtzProc {
public:
	struct {

		//
		AppParams_ipcProc	appParams;

		//
		QIS_pipe* pQisPipe;

		//
		bool  m_bAutoClose_ifToolLongNoRecvd_qm;

		DWORD  dwLastTickCnt_recvd;

		//
		HWND  hMainWnd;

		//
		bool  bErr1;

		//
		void* pShowInfoStruct;

	}  m_var;

	//
	DhPtzProc()
	{
		memset(&m_var, 0, sizeof(m_var));
	}


};


//
extern  DhPtzProc gBuf_dhPtz;

int  dhPtz_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1);

