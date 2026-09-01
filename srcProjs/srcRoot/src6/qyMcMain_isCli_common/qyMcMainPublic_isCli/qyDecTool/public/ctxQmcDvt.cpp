
#include	"stdafx.h"
#include	"ctxQmcDvt.h"

#include	"policyAvParams.h"
#include	"qyMcMainCommon.h"
//#include	"isD3dFunc_public.h"


CCtxQmcDvt::CCtxQmcDvt(  )
{
	//  2015/02/08
	this->m_iCtxType  =  CONST_ctxType_dvt;

	memset(  &m_var,  0,  sizeof(  m_var  )  );
	//
	safeTcsnCpy(  _T(  "dvt"  ),  this->who_showInfo,  mycountof(  this->who_showInfo  )  );
}


CCtxQmcDvt::~CCtxQmcDvt(  )
{
}


	RW_lock_param  *  CCtxQmcDvt::get_qyMc_rwLockParam(  )  
	{
		return  &m_var.qyMc_cfg.rwLockParam;
	}
	//

	TCHAR  *  CCtxQmcDvt::get_appObjPrefix(  )
	{
		return  m_var.cmdLine.appObjPrefix;
	}


	void  *  CCtxQmcDvt::get_qmc_cfg(  )
	{
		return  &m_var.cfg;
	}

	QNM_CUSRES_INFO  *  CCtxQmcDvt::get_qyMc_cusRes(  )  
	{
		//  not finished
		return  NULL;
	}

	QMC_status  *  CCtxQmcDvt::get_qmc_status(  )  
	{
		//  
		return  &m_var.status;
	}

	QMC_cfg_debugStatusInfo  *  CCtxQmcDvt::get_qmc_cfg_debugStatusInfo(  )  
	{
		//
		return  NULL;
	}


	QY_sharedObj_sync  *  CCtxQmcDvt::getSharedObjSyncByIndex(  int  index  )  
	{
		return  &m_var.sharedObjSync;
	}
	

	CAP_procInfo_bmpU  *  CCtxQmcDvt::getCapBmpBySth(  int  index,  unsigned  int  uiCapType  )  
	{
		return  &m_var.capBmp;
	}

	CAP_procInfo_audioU  *  CCtxQmcDvt::getCapAudioBySth(  int  index,  unsigned  int  uiCapType  )  
	{
		return  NULL;
	}

	//	
	int  CCtxQmcDvt::newShmCmdIndex(  int  iIndex_sharedObj  )
	{
		return  -1;
	}

	//	
	void  *  CCtxQmcDvt::getQmShmCmdByIndex(  int  iIndex  )
	{
		return  NULL;
	}


	//
	MIS_CNT  *  CCtxQmcDvt::getMisCntByName(  LPCTSTR  misServName  )  
	{
		//
		return  NULL;
	}

	//
	MIS_CNT  *  CCtxQmcDvt::getMisCntByIndex(  int  iIndex  )  
	{
		//
		return  NULL;
	}

	//
	HWND  CCtxQmcDvt::get_hMainWnd(  )  
	{
		//
		return  NULL;
	}


	//
	void  *  CCtxQmcDvt::getPolicyAvParams(  )  
	{	
		//
		return  m_var.p_gAvParams;
	}

	void  *  CCtxQmcDvt::getCusModules(  )  
	{
		QY_MC  *  pQyMc  =  (  QY_MC  *  )this->pQyMc;	
		if  (  !pQyMc  )  return  NULL;
		
		return  &pQyMc->cusModules;
	}


	//
	int  CCtxQmcDvt::setQmDbFuncs(  int  iDbType,  QM_dbFuncs  *  pDbFuncs  )
	{
		return  -1;
	}


	BOOL  CCtxQmcDvt::b_qyMc_quit(  )  
	{
		//
		return  FALSE;
	}



	BOOL  CCtxQmcDvt::bWebcamUsing(  unsigned  int  uiCamCapType,  void  *  pMoniker_v,  LPCTSTR  camName,  int  *  piIndex_capBmp,  int  *  piIndex_sharedObj  )
	{
		return  FALSE;
	}



	BOOL  CCtxQmcDvt::bMediaTaskExists(  int  iTaskId  )
	{
		return  FALSE;
	}



	BOOL  CCtxQmcDvt::bAudioChannelReady(  )
	{
		return  TRUE;
	}

	BOOL  CCtxQmcDvt::bVideoChannelReady(  )
	{
		return  TRUE;
	}


int  CCtxQmcDvt::drawVideoData(  myDRAW_VIDEO_DATA  *  pkts,  int  pktsLen,  BOOL  *  pbPktsRedirected,  void  *  pQY_TRANSFORM  )
{
	return  -1;
}



int  CCtxQmcDvt::playAudioData(  int  iSampleTimeInMs,  unsigned  int  uiPts,  BYTE  *  pInput,  unsigned  int  inputLen,  int  iIndex_player  )
{
	return  -1;
}



int  CCtxQmcDvt::showNotification(  void  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiContentType,  LPCTSTR  hint  )
{
	return  -1;
}


	
int  CCtxQmcDvt::qisChkTasks_gui(  )			//  2009/09/10
{
	return  -1;
}


int  CCtxQmcDvt::applyForRemovingInvalidTasks(  unsigned  int  uiChannelType  )
{
	return  -1;
}



int  CCtxQmcDvt::removeInvalidTasks(  unsigned  int  uiChannelType  )			//  2009/09/10
{
	return  -1;
}



//  2015/10/04
#if  0
unsigned  short  CCtxQmcDvt::get_pktResType_suggested(  int  pktUsage,  unsigned  int  uiModuleType  )
{
	return  this->m_var.cmdLine.usPktResType_suggested;
}
#endif

//
int  CCtxQmcDvt::get_deced_pktResType(  unsigned  int  uiModuleType,  int  iFourcc,  unsigned  short  *  pusPktResType_o  )				//  2015/10/04
{
	if  (  pusPktResType_o  )  {
		*pusPktResType_o  =  m_var.cmdLine.usPktResType_suggested;
	}
	return  0;
}

//
int  CCtxQmcDvt::get_pktResType_toEnc(  unsigned  short  usPktResType_src,  unsigned  int  uiModuleType,  int  iFourcc,  unsigned  short  *  pusPktResType_i  )				//  2015/10/04
{
	return  -1;
}




//
void  *  dvt_qoi_getPtrProperty(  void  *  pQdcObjInfoParam,  int  propertyId  );


//
int  CCtxQmcDvt::set_qoi_funcs(  MY_qoi  *  pMyQoi  )
{
	//
	pMyQoi->common.pf_qoi_getPtrProperty  =  dvt_qoi_getPtrProperty;


	return  0;
}

