
#ifndef  __makeDynaMenu_h__
#define  __makeDynaMenu_h__	//  {


//
#include	"qmStruct_defs.h"


//
typedef  int  (  *PF_getMenuStatus  )(  QY_MC  *  pQyMc,  void  *  p0,  void  *  p1,  void  *  piStatusParam  );

//  2010/04/14
extern  "C"  __declspec(  dllexport  )  int  makeDynaMenu(  void  *  pResInfoParam,  HMENU  hMenu,  QY_DMITEM  *  pTable,  PF_getMenuStatus  pf,  QY_MC  *  pQyMc,  void  *  p0  );




#endif  //  }

