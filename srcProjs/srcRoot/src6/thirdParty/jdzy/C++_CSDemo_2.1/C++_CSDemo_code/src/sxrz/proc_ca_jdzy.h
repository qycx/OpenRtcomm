
#ifndef  __proc_ca_h__
#define  __proc_ca_h__  //  {

//
#include	<Windows.h>
#include	"qmOpenCommon.h"
#include	"myCmdParams_open.h"

//
//#include	"ClientAuth.h"



//
#define  __USE_showInfo__
//#define  __TEST__

extern char* UnicodeToAnsi(const wchar_t* szStr, int& nLen);
extern int printLogChar(const char* log);
extern int printLog(TCHAR* log);

//
class  GBuf_jdzy  {

	//
public:

	GBuf_jdzy();
	~GBuf_jdzy();

	//
	struct {

		//
		AppParams_ca	appParams;

		//
		void  *  pShowInfoStruct;

		//
		HKEY	hKeyRoot0;

		//
		//CClientAuth* m_pClientAuth;



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
int jdzy_ca_sendData();




#endif  //  }


