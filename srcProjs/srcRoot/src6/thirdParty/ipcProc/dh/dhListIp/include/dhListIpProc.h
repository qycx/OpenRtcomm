
#ifndef  __dhListIpProc_h__
#define  __dhListIpProc_h__		//  {

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





//
class DhListIpProc {

	//
public:
	struct {
		QIS_pipe* pQisPipe;

		//
		//unsigned int uiSize_pOnvifMsgBuf;
		//char* pOnvifMsgBuf;

		bool  bMsgExists;

		//
		unsigned  int  	dwLastTickCnt_recvd;

		//
		AppParams_ipcProc	appParams;

		//
		NvrInfo			nvrInfo;

		//
		bool	m_bGot_nvrInfo;
		//
		bool	m_bDone_nvrInfo;

		//
		bool  m_bAutoClose_ifToolLongNoRecvd_dh;

		//
		void* pShowInfoStruct;


		//
	} m_var;
	
	//
	DhListIpProc()
	{
		memset(&m_var, 0, sizeof(m_var));
	}


};

//
extern  DhListIpProc  gBuf_dhListIp;

//
int  dhListIp_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1);


#endif  //  }


