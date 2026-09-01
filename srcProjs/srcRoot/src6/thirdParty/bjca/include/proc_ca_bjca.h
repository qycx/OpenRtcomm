
#ifndef  __proc_ca_h__
#define  __proc_ca_h__  //  {

//
#include	<Windows.h>
#include	"qmOpenCommon.h"
#include	"myCmdParams_open.h"

//
#define  __USE_showInfo__
//#define  __TEST__


//
typedef  struct {
	//   
	char                usrName[256];
	char                certId[128];

}                       Cert;
//
typedef  struct {
	unsigned  short     usCnt;
	Cert                mems[30];
}                       Certs;

//
int  parseCertList(char* cstrlist, Certs* pCerts);


//
class  GBuf_bjca  {

	//
public:

	GBuf_bjca();
	~GBuf_bjca();

	//
	struct {
		//
		char  ver[8  +  1];

		//
		AppParams_ca	appParams;

		//
		void  *  pShowInfoStruct;

	}		m_var;

	//



};



//
extern  GBuf_bjca  gBuf;

//
int  tmp_showInfo(void* p0, LPCTSTR  tWhere, LPCTSTR  hint);
int  tmp_set_who_showInfo(LPCTSTR  name);


//
#ifdef  __USE_showInfo__

//
extern  "C"  __declspec(dllexport)  int  initShowInfo_cli(void* p0, LPCTSTR  mutexName_syncQ, char* servIp, void** ppCtx_showInfo);
extern  "C"  __declspec(dllexport ) int  initShowInfo_func(  void  *  p0,  LPCTSTR  mutexName_syncQ,  LPCTSTR  errHintWndCls,  BOOL  bUsePipe,   BOOL  bUseSock,  char  *  servIp,  BOOL  bCli,  void  **  ppCtx_showInfo   );

extern  "C"  __declspec(dllexport)  void  exitShowInfo(void** ppCtx_showInfo);

#endif



#endif  //  }


