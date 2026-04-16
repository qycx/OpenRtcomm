

#include	"stdafx.h"
#include	<time.h>
#include	<tchar.h>


#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"

//#include	"qmcVideoCapture_isCli.h"
//
#include	"qyDynLib.h"
#include	"qmcDmoPublic.h"
#include	"qmcCmdProc.h"
#include	"tmpCeLib.h"
#include	"module_qisCamCap.h"
#include	"isCmdConst.h"
#include	"qyOpenShellCommon.h"
#include	"qyCusResTemp.h"
#include	"policyAvParams.h"

#include	"qmcTaskPublic.h"

#include	"qmcCfg.h"


//
 __declspec(dllexport)  int  doAll_setFlg_forceKeyFrame(CCtxQmc* pProcInfo)
{
	//
	showInfo_open(0, 0, 0, _T("doAll_setFlg_forceKeyFrame called"));

	//
	for (int index = 0; index < pProcInfo->cfg.usMaxCnt_pSharedObjs; index++) {
		QY_SHARED_OBJ* pSharedObj = getSharedObjByIndex(pProcInfo, index);

		if (!pSharedObj->bUsed)  continue;

		//
		setFlg_forceKeyFrame(pProcInfo, index);
	}

	//
	return  0;
}




//  2014/08/25
__declspec(  dllexport  )  int  setFlg_forceKeyFrame(  MC_VAR_common  *  pProcInfo,  int  iIndex_sharedObj  )
 {
	 int				iErr			=  -1;
	 //  MC_VAR_isCli	*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  -1;

	 QY_SHARED_OBJ	*	pSharedObj		=  NULL;
	 CAP_procInfo_bmpU			*	pCapBmp					=	NULL;
	 TCHAR  tBuf[128]  =  _T(  ""  );


	 pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );	
	 if  (  !pSharedObj  )  goto  errLabel;
	 pCapBmp													=	getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
	if  (  !pCapBmp  )  goto  errLabel;

	
	//
	DWORD  dwTickCnt  =  GetTickCount(  );

	//
	int  iElapseInMs  =  dwTickCnt  -  pCapBmp->common.compressVideo.encInfo.dwTickCnt_startToForceKeyFrame;

	if  (  abs(  iElapseInMs  )  >  500  )  {
		//	
		pCapBmp->common.compressVideo.encInfo.dwTickCnt_startToForceKeyFrame  =  dwTickCnt;

		//  2017/10/14
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, iIndex_sharedObj %d"  ),  _T(  "setFlg_forceKeyFrame ok"  ),  iIndex_sharedObj  );
		 showInfo_open0(  0,  0,  tBuf  );

	}
	

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, iIndex_sharedObj %d"  ),  _T(  "setFlg_forceKeyFrame failed"  ),  iIndex_sharedObj  );
		 showInfo_open0(  0,  0,  tBuf  );
	 }

	 return  iErr;

 }


