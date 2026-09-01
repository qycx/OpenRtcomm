

#ifndef  __hk3ddw_h__
#define  __hk3ddw_h__	//  {

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

#include <string>

extern int printLogChar(const char* log);
extern int printLogChar(int log);
extern int printLogChar(const char* des, int log);
extern int printLog(const wchar_t* log);
extern void my_printlog(const char* format, ...);
extern void my_printlog_w(const wchar_t* format, ...);
//
class Hk3ddwProc {

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
	Hk3ddwProc()
	{
		memset(&m_var, 0, sizeof(m_var));
	}


};

//
extern  Hk3ddwProc  gBuf_hk3ddw;

//
int  hk3ddw_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1);


//
int  hk_init(const std::string& devAddress, const std::string& username, const std::string& passwd);
int  hk_exit();
int  hk_do3ddw(int channel, int std_cols, int std_rows, int xTop, int  yTop, int xBottom, int yBottom);





#endif  //  }


