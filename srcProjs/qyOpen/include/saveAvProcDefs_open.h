
#ifndef  __saveAvProcDefs_open_h__
#define  __saveAvProcDefs_open_h__	//  {

//
#include	"ctxQmThread.h"

//
//
typedef  int  (*PF_q2GetMsg)(QY_Q2* pQ2, Q_ELEM_T* pQElem, unsigned  int* puiSize, LPCTSTR  hint);
typedef  DWORD(*PF_myGetTickCount)(CTX_qm_thread* pCtx);
//
typedef  int  (*PF_getTimelStr)(time_t  t, char* timeBuf, unsigned  int  size);
typedef  time_t(*PF_gettTimeBylStr)(char* timeBuf);


//
typedef  struct									{

	//
	PF_q2GetMsg									pf_q2GetMsg;
	PF_myGetTickCount							pf_myGetTickCount;
	PF_showInfo									pf_showInfo;				//  2011/12/14
	PF_getTimelStr								pf_getTimelStr;
	PF_gettTimeBylStr							pf_gettTimeBylStr;
	//




}		 QIS_guiOpen_saveAv;



#endif  //  }

