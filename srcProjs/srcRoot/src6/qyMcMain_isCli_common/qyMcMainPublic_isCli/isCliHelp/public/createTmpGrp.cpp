

#include	"stdafx.h"

#include	<windowsx.h>
#include	<math.h>
#include	<time.h>
#include	<stddef.h>

#include	"qymcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"

#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture_isCli.h"

#ifdef  __SUPPORT_HTMLEDIT__
	//  #include	"myHtmlEditCtrl.h"
#endif

#include	"tmpCeLib.h"
#include	"qyWnd.h"

#include	"qyRtcCommProc.h"
#include	"qyCusResTemp.h"
#ifndef  __WINCE__
//		 #include	"DlgVideos.h"
		 //  #include	"DlgCfgVideoConference.h"
		 //  #include	"DlgPolicyIsClient.h"
		 //  #include	"DlgInstantAssistant.h"
#endif
#include	<assert.h>
#ifndef  __WINCE__
	//  #include	"qyPs.h"
#endif
#include	"qmcDxSurfacePublic.h"
#ifndef  __WINCE__
#include	"qmcConferenceWall.h"
//  #include	"dlgProgress.h"
#endif
#include	"qmcCmdProc.h"

#include	"policyAvParams.h"

#ifndef  __WINCE__
		 //  #include	"qyStatic.h"
#endif
#include	"dlgTalkProc.h"
#include	"qmcSharePublic.h"

#if  1  //  def  __APP_qyMc_touchscreen__
		#include	"DlgWalls.h"
#endif

#include	"gpsCommProc.h"
#include	"qmcGpsProc.h"


#include	"qmcVWall.h"
//  #include	"DlgDynBmps.h"

#include	"sp.h"
#include	"isCliHelpPublic.h"

#include	"dlgCfgGrp.h"
#include	"genericHash.h"
#include	"guishare.h"


//
__declspec(  dllexport  )  int  createTmpGrp(  HWND  hParent,  IM_GRP_EX    *  p )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int  iErr  =  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

	//
	//
	CDlgCfgGrp		dlg(  CWnd::FromHandle(  hParent  )  );
	//
	dlg.m_var.iType  =  CONST_dcgType_createTmpGrp;
	//
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;

	//
	//			
	p->common.uiType  =  CONST_imCommType_imGrp;
	p->common.usSubtype  =  CONST_imGrpSubtype_av;
	//
	p->usOp  =  0;
	//
	int  i;
	for (  i= 0; i < dlg.m_var.tmpGrp.usCnt;  i ++  )  {
		if  (  p->usCnt  >= mycountof(  p->mems )  )  break;
		p->mems[p->usCnt].grpMmem_idInfo.ui64Id  =  dlg.m_var.tmpGrp.pMems[i].idInfo.ui64Id;
		p->usCnt  ++;
		continue;
	}
				

	//
	p->common.idInfo.ui64Id  =  dlg.m_var.idInfo_tmpGrp.ui64Id;
	
	//	req.common.idInfo_creator.ui64Id  =  pMisCnt->idInfo.ui64Id;





	iErr  =  0;
errLabel:
	return  iErr;
}


//  not finished
__declspec(  dllexport  )  int  modifyTmpGrp(  HWND  hParent,  IM_GRP_EX  *  p  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int  iErr  =  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

	//
	

	//
	CDlgCfgGrp		dlg(  CWnd::FromHandle(  hParent  )  );
	//
	dlg.m_var.iType  =  CONST_dcgType_modifyTmpGrp;
	dlg.m_var.pImGrpEx_input  =  p;
	
	//
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;

		//
	memset(  p,  0,  sizeof(  p[0]  )  );
	//			
	p->common.uiType  =  CONST_imCommType_imGrp;
	p->common.usSubtype  =  CONST_imGrpSubtype_av;
	//
	p->usOp  =  0;
	//
	int  i;
	for (  i= 0; i < dlg.m_var.tmpGrp.usCnt;  i ++  )  {
		if  (  p->usCnt  >= mycountof(  p->mems )  )  break;
		p->mems[p->usCnt].grpMmem_idInfo.ui64Id  =  dlg.m_var.tmpGrp.pMems[i].idInfo.ui64Id;
		p->usCnt  ++;
		continue;
	}
				

	//
	p->common.idInfo.ui64Id  =  dlg.m_var.idInfo_tmpGrp.ui64Id;
	
	//	req.common.idInfo_creator.ui64Id  =  pMisCnt->idInfo.ui64Id;

	iErr  =  0;

errLabel:
	return  iErr;
}



//
__declspec(  dllexport  )  int  selectMsgrsToSend(  TMP_usrs  *  pTmpUsrs   )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int  iErr  =  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );

	//
	HWND  hParent  =  pQyMc->gui.hGuiWnd;


	//
	CDlgCfgGrp		dlg(  CWnd::FromHandle(  hParent  )  );
	//
	dlg.m_var.iType  =  CONST_dcgType_sendFile;
	//
	if  (  IDOK  !=  dlg.DoModal(  )  )  goto  errLabel;

	//
	pTmpUsrs->usMaxCnt  =  dlg.m_var.tmpGrp.usMaxCnt;
	int  size  =  sizeof(  TMP_usr  )  *  dlg.m_var.tmpGrp.usCnt;
	pTmpUsrs->pMems  =  (  TMP_usr  *  )malloc(  size  );
	if  (  !pTmpUsrs->pMems  )  goto  errLabel;
	memcpy(  pTmpUsrs->pMems,  dlg.m_var.tmpGrp.pMems,  size  );
	pTmpUsrs->usCnt  =  dlg.m_var.tmpGrp.usCnt;


	//
	iErr  =  0;
errLabel:
	return  iErr;
}







