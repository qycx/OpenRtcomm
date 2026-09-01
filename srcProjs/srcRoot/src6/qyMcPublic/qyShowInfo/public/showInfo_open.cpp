

#include	"stdafx.h"

#include	"qyPrecomp.h"
#include	<winsock2.h>
#include	<windows.h>
#include	<assert.h>
#include	<stddef.h>
#include	<tchar.h>
#include	<stdlib.h>
#include	"qyCommon.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qnmPcComm.h"
#include	"qnmAssetsCommProc.h"
#include	"qnmSpCommProc.h"
#include	"qwmNetworkStatusCommProc.h"
#include	"qyTCharCommProc.h"
#include	"qnmCustom.h"
#include	"qySyncCommProc.h"
#include	"genericQueue.h"
#include	"qyq2.h"
#include	"tmpCeLib.h"
#include	"qyShowInfoCommon.h"

//
static  TCHAR  sWho_showInfo[128]  =  _T(  "Gui"  );

//
extern  "C"  __declspec(  dllexport  )  int  set_who_showInfo(  LPCTSTR  name  )
{
	if  (  !name  )  return  -1;
	safeTcsnCpy(  name,  sWho_showInfo,  mycountof(  sWho_showInfo  )  );
	return  0;
}

extern  "C"  __declspec(dllexport)  int  set_who_showInfoA(char *  name)
{
	if (!name)  return  -1;
	
	myUtf82TChar(name, sWho_showInfo, mycountof(sWho_showInfo));

	return  0;
}


 //  2011/12/14
 extern  "C"  __declspec(  dllexport  )  int  showInfo_open0(  void  *  p0,  LPCTSTR  tWhere,  LPCTSTR  hint  )
{
	//MC_VAR_isCli	*	pProcInfo  =  QY_GET_procInfo_isCli(  );
	//if  (  !pProcInfo  )  return  -1;
	
	TCHAR  *  who_from  =  sWho_showInfo;

	if  (  !hint    )  return  -1;
	if  (  !tWhere  )  tWhere  =  _T(  ""  );
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  who_from,  0,  tWhere,  _T(  ""  ),  _T(  "%s"  ),  hint  );
	return  0;
}




 //
 extern  "C"  __declspec(dllexport)  int  showInfo_openA(void* p0, char  *    where, char  *  hint)
 {
	 //MC_VAR_isCli	*	pProcInfo  =  QY_GET_procInfo_isCli(  );
	 //if  (  !pProcInfo  )  return  -1;

	 TCHAR* who_from = sWho_showInfo;

	 //
	 TCHAR  tWhere[128] = _T("");
	 TCHAR  tHint[256] = _T("");;

	 myUtf82TChar(where, tWhere, mycountof(tWhere));
	 myUtf82TChar(hint, tHint, mycountof(tHint));

	 //
	 //if (!hint)  return  -1;
	 //if (!tWhere)  tWhere = _T("");
	 qyShowInfo1(CONST_qyShowType_qwmComm, 0, (""), who_from, 0, tWhere, _T(""), _T("%s"), tHint);
	 return  0;
 }



 //  
 extern  "C"  __declspec(dllexport)  int  showInfo_open(void* p0, LPCTSTR  tWhere, unsigned  int  *  puiStep, LPCTSTR  hint)
 {
	 //MC_VAR_isCli	*	pProcInfo  =  QY_GET_procInfo_isCli(  );
	 //if  (  !pProcInfo  )  return  -1;

	 TCHAR* who_from = sWho_showInfo;

	 if (!hint)  return  -1;
	 if (!tWhere)  tWhere = _T("");
	 qyShowInfo1(CONST_qyShowType_qwmComm, puiStep, (""), who_from, 0, tWhere, _T(""), _T("%s"), hint);
	 return  0;
 }




#if 0
  extern  "C"  __declspec(  dllexport  )  int  showStatus_open(  void  *  p0,  LPCTSTR  tWhere,  LPCTSTR  hint,   int  iPos_toDisplay  )
{
	//MC_VAR_isCli	*	pProcInfo  =  QY_GET_procInfo_isCli(  );
	//if  (  !pProcInfo  )  return  -1;
	
	TCHAR  *  who_from  =  sWho_showInfo;

	if  (  !hint    )  return  -1;
	if  (  !tWhere  )  tWhere  =  _T(  ""  );

	PARAM_showInfo  param  =  {0};
	param.iPos_toDisplay  =  iPos_toDisplay;

	qyShowInfo2(  &param,  CONST_qyShowType_qmdState,  0,  (  ""  ),  who_from,  0,  tWhere,  _T(  ""  ),  _T(  " %s"  ),  hint  );

	return  0;
}
#endif


  extern  "C"  __declspec(dllexport)  int showState_open(void  *  p0, LPCTSTR tWhere, LPCTSTR hint, unsigned  short usStateType, unsigned  short usStateSubtype, SYSTEMTIME *when, int iPos_toDisplay, int iTaskId)
  {
	  //MC_VAR_isCli	*	pProcInfo  =  QY_GET_procInfo_isCli(  );
	  //if  (  !pProcInfo  )  return  -1;

	  TCHAR  * who_from = sWho_showInfo;

	  if (mynull == hint) return -1;
	  if (mynull == tWhere) tWhere = _T("");

	  PARAM_showInfo param;// = new PARAM_showInfo();
	  memset(&param, 0, sizeof(param));
	  param.usStateType = usStateType;
	  param.usStateSubtype = usStateSubtype;
	  if ( when)  param.when = *when;
	  param.iPos_toDisplay = iPos_toDisplay;
	  param.iTaskId = iTaskId;

	  qyShowInfo2(&param, CONST_qyShowType_qwmState, mynull, (""), who_from, mynull, tWhere, _T(""),  _T("%s"),  hint);

	  return 0;
  }




