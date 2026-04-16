

#ifndef  __qmdCliHelpPublic_h__	//  {
#define  __qmdCliHelpPublic_h__

//
#include	"qmStruct_defs.h"

//  2016/10/15
//  #define		__USE_qmdCliHelp__

//
extern  "C" __declspec(  dllexport  )  int  dllInit_qmdCliHelp(  );
extern  "C" __declspec(  dllexport  )  int  dllExit_qmdCliHelp(  );



//
__declspec(  dllexport  )  int  qmdCliHelp_init(  RnDataRedirect_qyMcInfo  *  pQyMcInfo );
__declspec(  dllexport  )  int  qmdCliHelp_exit(  RnDataRedirect_qyMcInfo  *  pQyMcInfo  );


//
__declspec(  dllexport  )  int  qmdCliHelp_doLogon(  RnDataRedirect_qyMcInfo  *  pQyMcInfo  );
__declspec(  dllexport  )  int  qmdCliHelp_doLogout(  RnDataRedirect_qyMcInfo  *  pQyMcInfo  );







#endif  //  }


