

#ifndef  __qmcTalkerPublic_h__
#define  __qmcTalkerPublic_h__	//  {

//
#include	"ctxQmc.h"

//
int  getSize_QMC_objVar_info(  );

 BOOL  bNoObjVarInfoExists(  MC_VAR_isCli  *  pProcInfo  );


 //
 //  2015/11/10
int  newQmcObjVarInfoIndex(  MC_VAR_isCli  *  pProcInfo,  unsigned  int  uiTalkerDataType,  HWND  hTalker  ); 
int  freeQmcObjVarInfoIndex(  MC_VAR_isCli  *  pProcInfo,  int  index_talkerInfo  );

//
 int  tryToFreeQmcObjVarInfos(  MC_VAR_isCli  *  pProcInfo  );


 

#endif  //  }


