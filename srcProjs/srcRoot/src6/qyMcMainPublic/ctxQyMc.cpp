

#include	"stdafx.h"
#include	<tchar.h>


#include	"ctxQyMc.h"
//
#include	"myDb.h"
//
#include	"qyMcMainProc.h"
#include	"imgFunc_open.h"

//
#ifdef  __isCli__
  __declspec(dllexport)  int   set_g_dbPool_isCliHelp(  void  *  pPool  );

#endif




CCtxQyMc::CCtxQyMc(  )
{
		//
#ifdef  __DEBUG__
		this->test1  =  567;
		this->test2  =  901;
#endif

	//
	int  size  =  &this->_bEnd  -  &this->_start;
	memset(  &this->_start,  0,  size  );

	//
	memset(  &m_var,  0,  sizeof(  m_var  )  );

}


CCtxQyMc::~CCtxQyMc(  )
{

}



/////////////
		
int  CCtxQyMc::initQnmRes(  void  *  p0,  unsigned  short  usLangId,  int  iResId_sys  )
{
	return  ::initQnmRes(  p0,  usLangId,  iResId_sys,  &this->cusRes  );
}


void  CCtxQyMc::exitQnmRes(  void  *  p0  )
{
	::exitQnmRes(  p0,  &this->cusRes  );
	return;
}


//
int  CCtxQyMc::addModuleMem_qnmRes(  int  iResId_sys  )
{
	return  ::addModuleMem_qnmRes(  iResId_sys,  &this->cusRes  );

}

//
int  CCtxQyMc::set_g_dbPool_isCliHelp(  void  *  pPool  )
{
#ifdef  __isCli__
	return  ::set_g_dbPool_isCliHelp(  pPool  );
#endif
	return  -1;
}

//  2015/07/19
 BOOL  tmp_bChkQyMcEnv_mis(  void  *  pQY_MC  );



//
BOOL  CCtxQyMc::bChkQyMcEnv_mis(  )
{
	return  ::tmp_bChkQyMcEnv_mis(  this  );
}


//
QY_SERVICEGUI_INFO	*	CCtxQyMc::get_pSci(  )
{
	 QY_MC						*	pQyMc						=	this;
	 //
	 int  iServiceId  =  pQyMc->iServiceId;
	 if  (  iServiceId  !=  CONST_qyServiceId_is  )  {
		 return  NULL;
	 }
	 QY_SERVICEGUI_INFO	*	pSci		=		getServiceGuiInfo(  pQyMc,  iServiceId  );
	 if  (  !pSci  )  return  NULL;

	 return  pSci;
}



//  2015/10/14
void  *  CCtxQyMc::get_pProcInfo(  )
{
	 QY_MC						*	pQyMc						=	this;
	 //
	 int  iServiceId  =  pQyMc->iServiceId;
	 if  (  iServiceId  !=  CONST_qyServiceId_is  )  {
		 return  NULL;
	 }
	 QY_SERVICEGUI_INFO	*	pSci		=		getServiceGuiInfo(  pQyMc,  iServiceId  );
	 if  (  !pSci  )  return  NULL;
	 void					*	pProcInfo					=	(  void  *  )pSci->pVar;
	 //  if (  !pProcInfo  )  return  -1;
	 return  pProcInfo;

}


//
 int  qyMc_setQmDbFuncs(  int  iDbType,  QM_dbFuncs  *  pDbFuncs  );

//
//  2016/09/26	
int  CCtxQyMc::setQmDbFuncs(  int  iDbType,  QM_dbFuncs  *  pDbFuncs  )
{
	/*
	MC_VAR_common  *  pProcInfo  =  get_pProcInfo(  );
	if  (  !pProcInfo  )  return  -1;

	return  pProcInfo->setQmDbFuncs(  iDbType,  pDbFuncs  );
	*/
	return  qyMc_setQmDbFuncs(  iDbType,  pDbFuncs  );
}



//
int  CCtxQyMc::setModalWnd_func(  HWND  hDlg,  BOOL  bFileDialog  )
{
	return  ::setModalWnd_func(  this,  hDlg,  bFileDialog  );
}


//
int  CCtxQyMc::yv12ToRgb24( unsigned  char  *  yuv,  unsigned  char  *  rgb,  int  width,  int  height,  BOOL  bFlipImg  )
{
#if  0
#ifdef  __SUPPORT_qyMc_ipp__
		QY_MC	*	pQyMc	=	this;

		if  (  pQyMc->cusModules.pIpp  
			&&  pQyMc->cusModules.pIpp->compress.mgr.pf_yv12ToRgb24  
			//  &&  bFlipImg  
			)  
		{	
			//  2011/12/03
			return  pQyMc->cusModules.pIpp->compress.mgr.pf_yv12ToRgb24(  (  BYTE  *  )yuv,  (  BYTE  *  )rgb,  width,  height,  bFlipImg  );								 
		}
#endif
#endif 


		//
	return  ::yv12ToRgb24( yuv,  rgb,  width,  height,  bFlipImg  );
}


//
int  CCtxQyMc::rgb24ToYv12(  unsigned  char  *  rgb,  unsigned  char  *  yuv,  int  width,  int  height,  BOOL  bFlipImg  )
{
#if  0
#ifdef  __SUPPORT_qyMc_ipp__
	QY_MC	*	pQyMc	=	this;

	if (height > 240) {
		if (pQyMc->cusModules.pIpp
			&& pQyMc->cusModules.pIpp->compress.mgr.pf_rgb24ToYv12
			// &&  bFlipImg  
			)
		{
			//  2011/12/03
			return  pQyMc->cusModules.pIpp->compress.mgr.pf_rgb24ToYv12((BYTE*)rgb, (BYTE*)yuv, width, height, bFlipImg);
		}
	}

#endif
#endif 


	//
	return  ::rgb24ToYv12(  rgb,  yuv,  width,  height,  bFlipImg  );
}


//
 int  CCtxQyMc::rgb24ToI420(  unsigned  char  *  rgb,  unsigned  char  *  yuv,  int  width,  int  height,  BOOL  bFlipImg  )
 {

#ifdef  __SUPPORT_qyMc_ipp__
	QY_MC	*	pQyMc	=	this;

#if  0
	if  (  pQyMc->cusModules.pIpp  
		&&  pQyMc->cusModules.pIpp->compress.mgr.pf_rgb24ToI420  
		 // &&  bFlipImg  
		)  
	{	  
		//  2011/12/03
		return  pQyMc->cusModules.pIpp->compress.mgr.pf_rgb24ToI420(  (  BYTE  *  )rgb,  (  BYTE  *  )yuv,  width,  height,  bFlipImg  );									
	}
#endif

#endif

	 //
	 return  ::rgb24ToI420(  rgb,  yuv,  width,  height,  bFlipImg  );
 }
