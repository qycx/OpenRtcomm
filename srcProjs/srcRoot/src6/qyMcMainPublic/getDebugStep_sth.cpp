

#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyMcMainCusModule.h"
#include	"qyCusResTemp.h"
#include	"qyVDev.h"
#include	"myresource.h"
#include	"qyCustom.h"
#include	"module_qisCamCap.h"

//  2015/10/03
#include	"qyDynLib.h"

//#include	"get_pf_createDXGIFactory1.h"



//
 //  2014/07/17
__declspec(  dllexport  )  void  *  getDebugStep_sth(  void  *  p0,  int  iType,  MY_DEBUG_STEP  *  pDebugStepTotal  )
 {
	 if  (  !pDebugStepTotal  )  return  NULL;

	 switch  (  iType  )  {
			case  CONST_debugStepType_dec:
				  return  &pDebugStepTotal->dec;
			default:
					break;
	 }

	 return  NULL;
  }



