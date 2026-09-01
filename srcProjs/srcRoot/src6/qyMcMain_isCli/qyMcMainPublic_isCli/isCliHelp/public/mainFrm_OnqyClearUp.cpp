
#include "stdafx.h"
#include	<afxpriv.h>

#include	<iphlpapi.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainWndProc.h"

#include	"qyAvRecordPublic.h"
#include	"qmcDxSurfacePublic.h"
#include	"qmcSharePublic.h"

#include	"myresource.h"

#include	"qyPs.h"
#include	"ppQnmClearup.h"
#include	"ppClearupEventCond.h"


#include	"qmcVideoCapture_isCli.h"
#include	"qyMcMainRealTimeMediaProc.h"
#include	"qmcVWall.h"

#include	"qyCusResTemp.h"

#include	"myDb.h"


__declspec(  dllexport  )  void mainFrm_OnqyClearUp(  HWND  hMainWnd  ) 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	QY_MC				*	pQyMc				=	QY_GET_GBUF(  );
	CQyPs					ps(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_emptyWizard  )  );
	CPpQnmClearup			ppQnmClearup;
	CPpClearupEventCond		ppClearupEventCond;
	QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	ps.m_var.iType  =  CONST_qyPsType_clearup;

	ps.AddPage(  &ppQnmClearup  );
	ps.AddPage(  &ppClearupEventCond  );
	
	ps.SetWizardMode(  );
	
	if  (  ps.DoModal(  )  !=  ID_WIZFINISH  )  return;

	switch  (  ps.m_var.u.clearupInfo.iTask  )  {
#if  0
			case  CONST_qyPsTask_clearupScannedIp:
				  bClearupScannedIp_netMc(  &ps.m_var.u.clearupInfo  );
				  break;
#endif
			case  CONST_qyPsTask_clearupEvent:
				  bClearupEvent(  pDbFuncs,  &ps.m_var.u.clearupInfo  );
				  break;
#if  0
			case  CONST_qyPsTask_procPcProcessKnowledge:
				  bClearupKnowledge(  CONST_pcCommType_pcProcessKnowledge  );
				  break;
			case  CONST_qyPsTask_procPcRegistryKnowledge:
  				  bClearupKnowledge(  CONST_pcCommType_pcRegistryKnowledge  );
				  break;
#endif
			case  CONST_qyPsTask_procImMsg:
				  g_dbFuncs.pf_bClearupImMsg(  &ps.m_var.u.clearupInfo  );
				  break;
			case  CONST_qyPsTask_procImHisTask:
				  g_dbFuncs.pf_bClearupImHisTask(  &ps.m_var.u.clearupInfo  );
				  break;				 
			default:
					break;
	}

#if  1  //  ndef  __DEBUG__
	qyMcRefreshAll(  );
#endif

	return;
}


