

#ifndef  __qyPipeFunc_h__
#define  __qyPipeFunc_h__	//  {

//
#include	"qyPipeFunc_open.h"

//
//
__declspec(  dllexport  )  int  myConnectToNewClient(HANDLE hPipe, LPOVERLAPPED lpo,  BOOL  *  pfPendingIO  );


//
__declspec(  dllexport  )  int  closeQyPipeThread(  QY_pipe  *  pPipe  );


#endif  //  }



