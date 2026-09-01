


#ifndef  __dyn_qisPublic_h__
#define  __dyn_qisPublic_h__	//  {

//
#include	<WTypes.h>
#include	"qySyncObj.h"
#include	"genericqueue.h"
#include	"qisPipe_open.h"

//
typedef  QIS_pipe  *  (  *PF_qisPipeNew  )(  );
typedef  int  (  *PF_qisPipe_writeMsg  )(  void  *  pMsg,  unsigned  int  msgLen,  QIS_pipe  *  pQisPipe  );
typedef  int  (  *PF_initQisPipe  )(  GENERIC_Q_CFG  *  pqCfg,  LPCTSTR  pipeName,  BOOL  bStarter,  LPCTSTR  name,  PARAM_initQisPipe  *  pParam,  QIS_pipe  *  p  );
typedef  void  (  *PF_qisPipeFree  )(  QIS_pipe  **  pp  );
//
typedef  int  (  *  PF_showInfo_open  )(  void  *  p0,  LPCTSTR  tWhere,  LPCTSTR  hint  );
typedef  int  (  *  PF_set_who_showInfo  )(  LPCTSTR  name  );

//
typedef  struct  {

			//  2015/02/17
			struct											{
				HINSTANCE									hDll;
				BOOL										bOk;

				//
				PF_qisPipeNew								pf_qisPipeNew;
				PF_qisPipe_writeMsg							pf_qisPipe_writeMsg;
				PF_initQisPipe								pf_initQisPipe;
				PF_qisPipeFree								pf_qisPipeFree;

			}												qisPublic;

			//
			struct											{
				HINSTANCE									hDll;
				BOOL										bOk;

				//
				PF_showInfo_open							pf_showInfo_open;
				PF_set_who_showInfo							pf_set_who_showInfo;

			}												qyShowInfo;


}		 DynLib_qisPublic;


//
int  load_dynLib_qisPublic(  );
int  unload_dynLib_qisPublic(  );  



//
QIS_pipe  *  dyn_qisPipeNew(  );
int  dyn_qisPipeWriteMsg(  void  *  pMsg,  unsigned  int  msgLen,  QIS_pipe  *  pQisPipe  );
int  dyn_initQisPipe(  GENERIC_Q_CFG  *  pqCfg,  LPCTSTR  pipeName,  BOOL  bStarter,  LPCTSTR  name,  PARAM_initQisPipe  *  pParam,  QIS_pipe  *  p  );
void  dyn_qisPipeFree(  QIS_pipe  **  pp  );


/////////////////////////////////////////////////
int  dyn_showInfo_open(  void  *  p0,  LPCTSTR  tWhere,  LPCTSTR  hint  );
int  dyn_set_who_showInfo(  LPCTSTR  name  );

#endif  //  }

