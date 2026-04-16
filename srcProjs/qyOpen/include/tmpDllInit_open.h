
#ifndef  __tmpDllInit_open_h__
#define  __tmpDllInit_open_h__	//  {

//  2017/10/09
typedef  struct  __param_qyDllInit_t		{
				 QIS_guiOpen			*	pGuiOpen;
}		 PARAM_qyDllInit;

//
typedef  struct  __param_qyDllExit_t		{
				 int						i_reserved;
}		 PARAM_qyDllExit;


//
typedef  int  (  *PF_qyDllInit  )(  void  *  p0,  void  *  p1,  PARAM_qyDllInit  *  pParam  );
typedef  int  (  *PF_qyDllExit  )(  void  *  p0,  void  *  p1,  PARAM_qyDllExit  *  pParam  );


//
extern  "C"  __declspec(  dllexport  ) int  qyDllInit(  void  *  p0,  void  *  p1,  PARAM_qyDllInit  *  pParam  );
extern  "C"  __declspec(  dllexport  ) int  qyDllExit(  void  *  p0,  void  *  p1,  PARAM_qyDllExit  *  pParam  );


#endif  //  }

