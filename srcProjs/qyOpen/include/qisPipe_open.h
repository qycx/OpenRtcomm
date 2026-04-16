

#ifndef  __qisPipe_open_h__
#define  __qisPipe_open_h__	//  {


//
typedef  struct  __qisPipe_t	QIS_pipe;


//
//
typedef  int  (  *  PF_qisPipe_onRead  )(  QIS_pipe  *  pQisPipe,  void  *  pMsg,  unsigned  int  msgLen,  void  *  p0,  void  *  p1  );

//
typedef  struct  __param_initQisPipe_t		{
				 void  *  p0;
				 void  *  p1;
				 //
				 PF_qisPipe_onRead			pf_onRead;

				 //
				 bool						bPrint_write;

				 //
				 unsigned  int				uiMaxToInMs_read;

				 //
}		 PARAM_initQisPipe;



//
#ifdef  __cplusplus
extern  "C"  {
#endif

//
__declspec(  dllexport  )  QIS_pipe  *  qisPipeNew(  );
__declspec(  dllexport  )  void  qisPipeFree(  QIS_pipe  **  pp  );

//
__declspec(dllexport) BOOL  bQisPipeOk(QIS_pipe * pQisPipe);

//
__declspec(  dllexport  )  int  initQisPipe(  GENERIC_Q_CFG  *  pqCfg,  LPCTSTR  pipeName,  BOOL  bStarter,  LPCTSTR  name,  PARAM_initQisPipe  *  pParam,  QIS_pipe  *  p  );
__declspec(  dllexport  )  int  exitQisPipe(  QIS_pipe  *  p  );

//
__declspec(  dllexport  )  int  qisPipe_writeMsg(  void  *  pMsg,  unsigned  int  msgLen,  QIS_pipe  *  pQisPipe  );

//
__declspec(dllexport)  int  initQisPipeA(char* q_name, char* q_mutexName_prefix, int  q_uiMaxQNodes, char* pipeName, BOOL  bStarter, char* name, PARAM_initQisPipe* pParam, QIS_pipe* p);






#ifdef  __cplusplus
}
#endif



#endif  //  }


