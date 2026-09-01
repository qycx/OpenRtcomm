
#ifndef  __qmdConnPublic_h__
#define  __qmdConnPublic_h__	//  {

//
//#include	"qmdConnMgr.h"
typedef  struct  __qmdConn_t {
	//
	bool  bQuit;
	//
	HANDLE		hThread;
	DWORD		dwThreadId;
}		 QmdConnMem;


//
__declspec(dllexport) int qmdConn_init(HINSTANCE hInst,int iIDD,QmdConnMem*pMem);
__declspec(dllexport) int qmdConn_exit(HINSTANCE hInst,QmdConnMem*pMem);
__declspec(dllexport)bool qmdConn_bRunning(QmdConnMem* pMem);





#endif  //  }

