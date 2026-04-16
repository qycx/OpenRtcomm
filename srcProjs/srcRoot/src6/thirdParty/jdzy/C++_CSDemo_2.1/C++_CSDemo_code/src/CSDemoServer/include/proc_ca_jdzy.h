
#ifndef  __proc_ca_jdzy_h__
#define  __proc_ca_jdzy_h__		//  {


//
#include	<Windows.h>
//#include	<mmeapi.h>
#include	<MMSystem.h>

#include	"qmOpenCommon.h"
#include	"myCmdParams_open.h"

#include	"resource.h"
#include	"CSDemoServerDlg.h"
#include	"CServerAuth.h"


//

//#define  __TEST__

extern int printLogChar(const char* log);
extern int printLog(TCHAR* log);

//
class  GBuf_jdzy {

	//
public:

	GBuf_jdzy();
	~GBuf_jdzy();

	//
	struct {

		//
		AppParams_ca	appParams;

		//
		void* pShowInfoStruct;

		//
		HKEY		hKeyRoot0;


		//
		CServerAuth* m_pServerAuth;



	}		m_var;

	//



};



//
extern  GBuf_jdzy  gBuf;

//
#ifdef  __USE_showInfo__

//
extern  "C"  __declspec(dllexport)  int  initShowInfo_cli(void* p0, LPCTSTR  mutexName_syncQ, char* servIp, void** ppCtx_showInfo);

extern  "C"  __declspec(dllexport)  void  exitShowInfo(void** ppCtx_showInfo);

#endif

//
int  jdzy_ca_getRandom();
int  jdzy_ca_login_auth();




#endif  //  }


