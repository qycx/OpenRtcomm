// DlgCfgGrp.cpp : implementation file
//

#include "stdafx.h"

#include	"qyMcMainCommon.h"
//  #include	"qymc.h"
#include	"myresource.h"
#include	"DlgCfgVideoConference.h"
#include	"qmCommonFunc_mis.h"
#include	"qyCusResTemp.h"
//#include	"qmshell_open.h"

#include	"msAecCommon.h"
#include	"isCliHelpPublic.h"
#include	"FuncsForIsCliHelp.h"

#include "DlgCfgGrp.h"
#include "afxdialogex.h"

#include	"dlgtalkproc.h"
#include	"myTChar.h"

//
__declspec(  dllexport  )  void  free_TMP_usrs(  TMP_usrs  *  pTmpUsrs  )
{
	if  (  !pTmpUsrs  )  return;

	MACRO_safeFree(  pTmpUsrs->pMems  );
	memset(  pTmpUsrs,  0,  sizeof(  pTmpUsrs[0]  )  );

}



// CDlgCfgGrp dialog

IMPLEMENT_DYNAMIC(CDlgCfgGrp, CDialogEx)

CDlgCfgGrp::CDlgCfgGrp(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCfgGrp::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );

}

CDlgCfgGrp::~CDlgCfgGrp()
{
	//
	free_usrs(  );

}

void CDlgCfgGrp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgCfgGrp, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgCfgGrp::OnBnClickedOk)
	ON_WM_DESTROY()
	ON_EN_CHANGE(IDC_EDIT_selUsr, &CDlgCfgGrp::OnEnChangeEditselusr)
	ON_BN_CLICKED(IDC_BUTTON_add, &CDlgCfgGrp::OnBnClickedButtonadd)
	ON_BN_CLICKED(IDC_BUTTON_del, &CDlgCfgGrp::OnBnClickedButtondel)
	ON_MESSAGE( QY_WM_COMM, OnQyComm )
	ON_EN_CHANGE(IDC_EDIT_grpName, &CDlgCfgGrp::OnEnChangeEditgrpname)
END_MESSAGE_MAP()


// CDlgCfgGrp message handlers


//
BOOL  tmpHandle_bImGrp(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	BOOL  bRet  =  FALSE;
	QY_MESSENGER_ID  *  pIdInfo_grp  =  (  QY_MESSENGER_ID  *  )p0;
	//
		 IM_GRP_MEM	*	pQMem			=  (  IM_GRP_MEM  *  )p2;

		 if  (  pQMem->idInfo_grp.ui64Id  ==  pIdInfo_grp->ui64Id  )  {
			 bRet  =  TRUE;
		 }


		 return  bRet;


}



//
void CDlgCfgGrp::OnBnClickedOk()
{
	//
	int  iErr  =  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	if  (  !pMisCnt  )  return;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	
	//
	CQnmDb  db;
	if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;

	//
	if  (  m_var.iType  ==  CONST_dcgType_createTmpGrp
		||  m_var.iType  ==  CONST_dcgType_modifyTmpGrp  )  
	{

		//
		TCHAR  grpName[128]  =  _T(  ""  );
		GetDlgItemText(  IDC_EDIT_grpName,  grpName,  mycountof(  grpName  )  );
	
		//
		MACRO_prepareForTran(  );
	
		//
		IM_GRP_EX	req  =  {0};
		{
			CQyMalloc					mallocObj;
			IM_L_STREAM				*	pStream								=	NULL;

			if  (  !(  pStream  =  (  IM_L_STREAM  *  )mallocObj.mallocf(  sizeof(  IM_L_STREAM  )  )  )  )  {
				#ifdef  __DEBUG__
						traceLogA(  "sndDevInfo_qmc . malloc failed."  );  
				#endif
				goto  errLabel;
			}
					
			unsigned  int		len;
			char				buf[256];
			
			//
			IM_GRP_INFO  *  pReq  =  &req.common;
				
			//
			memset(  &req,  0,  sizeof(  req  )  );
			req.common.uiType  =  CONST_imCommType_imGrp;
			//myTChar2Utf8(  passwd0,  buf,  mycountof(  buf  )  );
			//	
			lstrcpyn(  pReq->name,  grpName,  mycountof(  pReq->name  )  );			
			pReq->usSubtype  =  CONST_imGrpSubtype_av;	//  pGrpInfo->usSubtype;
			//
			if  (  m_var.iType  ==  CONST_dcgType_createTmpGrp  )  {
				req.usOp  =  CONST_imOp_new;
			}
			else  {
				  req.usOp  =  CONST_imOp_modify;
				  req.common.idInfo.ui64Id  =  m_var.pImGrpEx_input->common.idInfo.ui64Id;
			}
			//
			int  i;
			for  (  i  =  0;  i  <  m_var.tmpGrp.usCnt;  i  ++  )  {
				if  (  req.usCnt  >=  mycountof(  req.mems  )  )  break;
				req.mems[req.usCnt].grpMmem_idInfo.ui64Id  =  m_var.tmpGrp.pMems[i].idInfo.ui64Id;
				req.usCnt  ++  ;
				continue;
			}


			//  2010/08/14
			pFuncs->pf_startProgress(  &pQyMc->gui.progress,  uiTranNo  );

			//
			MACRO_memset_imLStream(  pStream  );
			pStream->uiType  =  CONST_imCommType_lStream;
			pStream->uiContentType  =  req.common.uiType;
			len  =  sizeof(  pStream->buf  );
			if  (  imGrpEx2Stream(  pStream->uiContentType,  &req,  pStream->buf,  &len  )  )  goto  errLabel;
			pStream->ulStreamLen  =  len;
			len  +=  offsetof(  IM_L_STREAM,  buf  ); 
			//
			postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_req,  0,   CONST_qyCmd_refreshImObjListReq,  tStartTran,  uiTranNo,  0,  (  char  *  )pStream,  len,  NULL,  0,  0,  NULL,  0  ); 
		}

		//  pProcInfo->bInProgress_toSetPasswd  =  TRUE;

		//
		if  (  showProgress(  &pQyMc->gui.progress,  &pQyMc->cusRes,  this->m_hWnd,  _T(  "Please waiting"  ),  NULL,  30,  -1,  uiTranNo  )  !=  IDOK  )  {
			goto  errLabel;
		}
		
		//
		QM_dbFuncs		*	pDbFuncs	=	pQyMc->p_g_dbFuncs;
		if  (  !pDbFuncs  )  goto  errLabel;
		QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;


		//
		req.common.idInfo.ui64Id  =  m_var.idInfo_tmpGrp.ui64Id;
		req.common.idInfo_creator.ui64Id  =  pMisCnt->idInfo.ui64Id;

		//
		time_t  t;  time(&t );
		recoverImGrp(  &g_dbFuncs,  db.m_pDbMem->pDb,  db.m_pDbMem->iDbType,  CONST_fieldIdTable_en,  CONST_objType_imGrp,  &req.common,  t,  FALSE  );

		CMyDb  *  pDb  =  (  CMyDb  *  )db.m_pDbMem->pDb;
		//
		qRemoveMsg(  pDb->m_var.pQ_qyImGrpMemTab,  tmpHandle_bImGrp,  &req.common.idInfo,  0  );

		//
		int  i;
		for  (  i  =  0;  i  <  m_var.tmpGrp.usCnt;  i  ++  )  {
			IM_GRP_MEM   imGrpMem  =  {0};
			imGrpMem.idInfo_grp.ui64Id  =  req.common.idInfo.ui64Id;
			imGrpMem.idInfo_mem.ui64Id  =  m_var.tmpGrp.pMems[i].idInfo.ui64Id;
			//
			recoverImGrpMem(  &g_dbFuncs,  db.m_pDbMem->pDb,  db.m_pDbMem->iDbType,  &imGrpMem,  t  );
		}

	}


	//
#ifdef  __DEBUG__
		traceLogA(  "kk"  );
#endif

	//
	iErr  =  0;

errLabel:
	if  (  iErr  )  {
		return;
	}

	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


//
 //
int  tmpHandler_bFillUsrs_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int					iRet										=  -1;

	COMMON_PARAM	*	pCommonParam								=	(  COMMON_PARAM  *  )p0;
	TMP_usrs   *  pUsrs  =  (  TMP_usrs  *  )p1;
	//
	HWND				hDlgTalk									=	(  HWND  )pCommonParam->p0;
	PARAM_PROC_ROW	*	pParam										=	(  PARAM_PROC_ROW  *  )pCommonParam->p1;
	CMyDb			*	pDb											=	(  CMyDb  *  )pCommonParam->p2;
	//
	QMEM_qyImObj		*   pQMem			=		(  QMEM_qyImObj  *  )p2;

	//
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	if  (  !pQyMc  )  return  -1;
	QM_dbFuncs  *  pDbFuncs  =  pQyMc->p_g_dbFuncs;
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	if  (  !pMisCnt  )  return  -1;

	//
	if  (  !pParam  )  {
		return  -1;
	}

	//
	int  iDbType  =  CONST_dbType_myDb;


	//
	QY_MESSENGER_REGINFO		regInfo;
	QY_MESSENGER_REGINFO	*	pRegInfo			=	&regInfo;


	if  (  pQMem->messengerInfo.uiType  !=  CONST_objType_imGrp  )
	{
		//  2014/04/20
		int  id_imGrpMem  =  0;//pQMem->id;

		//
		
			int  iDbType  =  CONST_dbType_myDb;
			if  (  !g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pDb,  iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab,  _T(  ""  ),  &pQMem->messengerInfo.idInfo,  0,  &regInfo  )  )  {
				memset(  &regInfo,  0,  sizeof(  regInfo  )  );
			}

		 
			 QY_MC					*	pQyMc				=  QY_GET_GBUF(  );
			 MC_VAR_isCli			*	pProcInfo			=	QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;

			 //
			 MY_REG_DESC				desc;
			 TCHAR						talkerDesc[128  +  1];
			 TCHAR						displayName[64  +  1];
			 int						nImage,  nSelectedImage;
		 
			 if  (  regInfo2Desc(  0,  pRegInfo,  &desc,  talkerDesc,  mycountof(  talkerDesc  ),  displayName,  mycountof(  displayName  )  )  )  goto  errLabel;

			 nImage  =  pQyMc->cfg.image.nImage_messenger;  nSelectedImage  =  pQyMc->cfg.image.nImage_selectedMessenger;

		   {	 //  
			 QM_OBJQ_MEM				mem;
			 QMEM_MESSENGER_CLI		*	pQMem	=	NULL;
			 QY_MESSENGER_INFO			messengerInfo;
			 void					*	pDb		=	NULL;
			 int						i;

			 CQnmDb						tmpObjDb;						
			 pDb				=		tmpObjDb.getAvailableDb(  pQyMc->iDsnIndex_mainSys  );

			 //  ÏÈÓÃregInfoÌî³äÒ»ÏÂmessengerInfo, ÒòÎªÏÂÃæµÄpClientÖ»ÄÜÖ¸ÏòmessengerInfo
			 memset(  &messengerInfo,  0,  sizeof(  messengerInfo  )  );
			 //
			 lstrcpyn(  messengerInfo.misServName,  regInfo.addr.misServName,  mycountof(  messengerInfo.misServName  )  );
			 messengerInfo.idInfo.ui64Id  =  regInfo.addr.idInfo.ui64Id;

			 //               
			 if  (  procQmObjQ(  pProcInfo->pSgiParam,  (  QM_OBJQ  *  )pMisCnt->pObjQ,  pDb,  pQyMc->cfg.db.iDbType,  CONST_objType_messenger,  &messengerInfo,  &mem  )  )  goto  errLabel;
			 if  (  !mem.pQMemObj  )  goto  errLabel;

			 pQMem  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;

			 //  ÕâÀïÔÝÊ±ÔÚÕâÀï¸üÐÂÏÔÊ¾Ãû³Æ  
			 lstrcpyn(  pQMem->talkerDesc,  talkerDesc,  mycountof(  pQMem->talkerDesc  )  );
			 lstrcpyn(  pQMem->displayName,  displayName,  mycountof(  pQMem->displayName  )  );		//  2007/09/02

			 //
			 getMessengerImages(  pQyMc,  pQMem->usRunningStatus,  &nImage,  &nSelectedImage  );

			 //  2017/08/08
			 if  (  pParam->ucbNoMe  )  {
				 if  (  pMisCnt->idInfo.ui64Id  ==  pQMem->idInfo.ui64Id  )  {
					 iRet  =  0;  goto  errLabel;
				 }
			 }

			 //
			 if  (  pUsrs  )  {
				 if  (  pUsrs->usCnt  <  pUsrs->usMaxCnt  )  {
					 TMP_usr  *  pMem  =  &pUsrs->pMems[pUsrs->usCnt];
					 pMem->idInfo.ui64Id  =  pQMem->idInfo.ui64Id;
					 //
					 //pMem->id_imGrpMem  =  id_imGrpMem;
					 //
					 safeTcsnCpy(  displayName,  pMem->displayName,  mycountof(  pMem->displayName  )  );
					 safeTcsnCpy(  talkerDesc,  pMem->talkerDesc,  mycountof(  pMem->talkerDesc  )  );
					 //
					 pUsrs->usCnt  ++  ;
					 
				 }

			 }

			 //
			 pParam->nItem  ++  ;

		   }
		 

	}

	iRet  =  0;
errLabel:
	return  iRet;
}



//
__declspec(  dllexport  )  BOOL  bFillUsrs_myDb(  HWND  hDlgTalkParam,  void  *  pDbParam,  void  *  pParam,  TMP_usrs  *  pUsrs  )
{
	BOOL				bRet										=   FALSE;
	CMyDb			*	pDb											=	(  CMyDb  *  )pDbParam;
	COMMON_PARAM		commonParam;
	MACRO_makeCommonParam3(  hDlgTalkParam,  pParam,  pDb,  commonParam  );

	//
	qTraverse(  pDb->m_var.pQ_qyImObjTab,  tmpHandler_bFillUsrs_myDb,  &commonParam,  pUsrs  );
	
	bRet  =  TRUE;
errLabel:
	return  bRet;
}




//
int  CDlgCfgGrp::fill_usrs(  )
{
	int  iErr  =  -1;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	if  (  !pMisCnt  )  return  -1;

	 //
	 PARAM_PROC_ROW		param;
	
	 memset(  &param,  0,  sizeof(  param  )  );
	
	 //
	 {	 
		 CQnmDb				db;
				
		 if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
				
		 
		 //
		 memset(  &param,  0,  sizeof(  param  )  );
		 bFillUsrs_myDb(  0,  db.m_pDbMem->pDb,  &param,  0  );						

		 //
		 TMP_usrs  *  p  =  &m_var.tmpUsrs;

		 //
		 free_usrs(  );
		 
		 //
		 p->usMaxCnt  =  param.nItem;
		 int  size  =  sizeof(  TMP_usr  )  *  p->usMaxCnt;
		 p->pMems  =  (  TMP_usr  *  )malloc(  size  );
		 if  (  !p->pMems  )  goto  errLabel;
		 memset(  p->pMems,  0,  size  );
		 
		 //
		 memset(  &param,  0,  sizeof(  param  )  );
		 //
		 if  (  m_var.iType  ==  CONST_dcgType_sendFile  )  {
			 param.ucbNoMe  =  TRUE;
		 }
		 //
		 bFillUsrs_myDb(  0,  db.m_pDbMem->pDb,  &param,  p  );		

		 //
		 int  i;
		 TCHAR  tBuf[128];

		 //
		 p  =  &m_var.tmpGrp;

		 //
		 p->usMaxCnt  =  m_var.tmpUsrs.usMaxCnt;
		 size  =  sizeof(  TMP_usr  )  *  p->usMaxCnt;
		 p->pMems  =  (  TMP_usr  *  )malloc(  size  );
		 if  (  !p->pMems  )  goto  errLabel;
		 memset(  p->pMems,  0,  size  );


		 //
		 if  (  m_var.iType  ==  CONST_dcgType_createTmpGrp  )  {
			 //
			 i  =  0;
			 TMP_usr  *  pMem  =  &p->pMems[i];
			 pMem->idInfo.ui64Id  =  pMisCnt->idInfo.ui64Id;
			 getDescByIdInfo(  0,  &pMem->idInfo,  pMem->talkerDesc,  mycountof(  pMem->talkerDesc  ),  pMem->displayName,  mycountof(  pMem->displayName  )  );
			 p->usCnt  ++  ;
		 }
		 else  if  (  m_var.iType  ==  CONST_dcgType_modifyTmpGrp  )  {
				   //
			 for  (  i  =  0;  i  <  p->usMaxCnt;  i  ++  )  {
				  if  (  i  >=  m_var.pImGrpEx_input->usCnt  )  break;
					    TMP_usr  *  pMem  =  &p->pMems[i];
						pMem->idInfo.ui64Id  =  m_var.pImGrpEx_input->mems[i].grpMmem_idInfo.ui64Id;
						getDescByIdInfo(  0,  &pMem->idInfo,  pMem->talkerDesc,  mycountof(  pMem->talkerDesc  ),  pMem->displayName,  mycountof(  pMem->displayName  )  );
						p->usCnt  ++  ;
				   }

		 }



	 }

	
	 iErr  =  0;

errLabel:
	 
	return  iErr;
}


//
BOOL  CDlgCfgGrp::isGrpMem(  QY_MESSENGER_ID  * pIdInfo  )
{
	BOOL  bRet  =  FALSE;

	int  i;
	TMP_usrs  *  p  =  &m_var.tmpGrp;

	for  (  i  =  0;  i  <  p->usCnt;  i  ++  )  {
		 if  (  p->pMems[i].idInfo.ui64Id  ==  pIdInfo->ui64Id  )  return  TRUE;
	}


	return  bRet;
}


//
int  CDlgCfgGrp::add_mem(  QY_MESSENGER_ID  *  pIdInfo  )
{
	TMP_usrs  *  p  =  &m_var.tmpGrp;

	int  i;
	
	//
	if  (  isGrpMem(  pIdInfo  )  )  return  0;

	if  (  p->usCnt  >=  p->usMaxCnt  )  return  -1;

	TMP_usr  *  pMem  =  &p->pMems[p->usCnt];
	pMem->idInfo.ui64Id  =  pIdInfo->ui64Id;
	getDescByIdInfo(  0,  pIdInfo,  pMem->talkerDesc,  mycountof(  pMem->talkerDesc  ),  pMem->displayName,  mycountof(  pMem->displayName  )  );

	p->usCnt  ++  ;

	
	return  0;
}


//
int  CDlgCfgGrp::del_mem(  QY_MESSENGER_ID  *  pIdInfo  )
{
	TMP_usrs  *  p  =  &m_var.tmpGrp;

	int  i;

	for  (  i  =  0;  i  <  p->usCnt;  i  ++  )  {
		 TMP_usr  *  pMem  =  &p->pMems[i];
		 //
		 if  (  pMem->idInfo.ui64Id  ==  pIdInfo->ui64Id  )  {
			 if  (  i  !=  p->usCnt  -  1  )  {
				 int  j;
				 for  (  j  =  i;  j  <  p->usCnt;  j  ++  )  {
					  p->pMems[j]  =  p->pMems[j  +  1];
				 }
			 }
			 //
			 p->usCnt  --  ;
		 }
	}

	return  0;
}


//
int  CDlgCfgGrp::free_usrs(  )
{
	if  (  m_var.tmpUsrs.pMems  )  {
		free(  m_var.tmpUsrs.pMems  );  m_var.tmpUsrs.pMems  =  0;
	}
	memset(  &m_var.tmpUsrs,  0,  sizeof(  m_var.tmpUsrs  )  );

	//
	MACRO_safeFree(  m_var.tmpGrp.pMems  );
	memset(  &m_var.tmpGrp,  0,  sizeof(  m_var.tmpGrp  )  );

	return  0;
}


//
int  CDlgCfgGrp::display(  TCHAR  *  tSelUsrs  )
{
	TMP_usrs  *  p;
	TCHAR  tBuf[128];
	int  i;

	//
	tTrim(  tSelUsrs  );
	
		 //
		 p  =  &m_var.tmpUsrs;
		 //
		 ::SendMessage(  ::GetDlgItem(  m_hWnd,  IDC_LIST_usr  ),  LB_RESETCONTENT,  (  WPARAM  )-1,  (  LPARAM  )tBuf  );    
		 //
		 for  (  i  =  0;  i  <  p->usCnt;  i  ++  )  {
			  TMP_usr  *  pMem  =  &p->pMems[i];

			  //
			  if  (  isGrpMem(  &pMem->idInfo  )  )  continue;
			  //
			  if  (  tSelUsrs  )  {				
				  if  (  !my_tcsistr(  pMem->talkerDesc,  tSelUsrs  )  )  continue;  
			  }
			  //
			  _sntprintf(  tBuf,  mycountof(  tBuf ),  _T(  "%s %I64u"  ),  pMem->talkerDesc,  pMem->idInfo.ui64Id  );

			  //			  
			  ::SendMessage(  ::GetDlgItem(  m_hWnd,  IDC_LIST_usr  ),  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )tBuf  );    
		 }


		 //
		 p  =  &m_var.tmpGrp;
		 //
		 ::SendMessage(  ::GetDlgItem(  m_hWnd,  IDC_LIST_mem  ),  LB_RESETCONTENT,  (  WPARAM  )-1,  (  LPARAM  )tBuf  );    
		 //
		 for  (  i  =  0;  i  <  p->usCnt;  i  ++  )  {
			  TMP_usr  *  pMem  =  &p->pMems[i];
			  _sntprintf(  tBuf,  mycountof(  tBuf ),  _T(  "%s %I64u"  ),  pMem->talkerDesc,  pMem->idInfo.ui64Id  );

			  //			  
			  ::SendMessage(  ::GetDlgItem(  m_hWnd,  IDC_LIST_mem  ),  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )tBuf  );    
		 }

		 return  0;

}



//
BOOL CDlgCfgGrp::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

	//
	pProcInfo->cfgGrp.hWnd_cfgGrp  =  m_hWnd;

	//
	fill_usrs(  );
	display(  _T(  ""  )  );

	//
	if  (  m_var.iType  ==  CONST_dcgType_sendFile  )  {
		::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_STATIC_grpName  ),  SW_HIDE  );
		::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_EDIT_grpName  ),  SW_HIDE  );
	}


	//
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgCfgGrp::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}


void CDlgCfgGrp::OnEnChangeEditselusr()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	TCHAR  tBuf[128];

	GetDlgItemText(  IDC_EDIT_selUsr,  tBuf,  mycountof(  tBuf  )  );
	//
	safeTcsnCpy(  tBuf,  m_var.tSelUsrs,  mycountof(  m_var.tSelUsrs  )  );

	//
	display(  m_var.tSelUsrs  );

}


void CDlgCfgGrp::OnBnClickedButtonadd()
{
	// TODO: Add your control notification handler code here
	//
	//
	CQyMalloc	mallocObj;
	TCHAR  *	pT	=	NULL;

	//
	HWND  hDlg  =  m_hWnd;

	//
	HWND	hCtrl  =  ::GetDlgItem(  hDlg,  IDC_LIST_usr  );

	int			iItemSelected	=	::SendMessage(  hCtrl,  LB_GETCURSEL,  0,  0  );	
	if  (  iItemSelected  <  0  )  goto  errLabel;

	int		len  =  ::SendMessage(  hCtrl,  LB_GETTEXTLEN,  iItemSelected,  0  );
	if  (  len  <  0  )  goto  errLabel;
	len  ++  ;

	pT  =  (  TCHAR  *  )mallocObj.mallocf(  sizeof(  TCHAR  )  *  len  );
	if  (  !pT  )  goto  errLabel;
	::SendMessage(  hCtrl,  LB_GETTEXT,  iItemSelected,  (  LPARAM  )pT  );

	//
	traceLog(  _T(  "sel %s"  ),  pT  );

	//
	TCHAR  *  pT1;

	//
	pT1  =  _tcsrchr(  pT,  _T( ' ' )  );
	if  (  !pT1  )  goto  errLabel;
	
	char  buf[128];
	myTChar2Utf8(  pT1,  buf,  mycountof(  buf  )  );

	QY_MESSENGER_ID  idInfo;
	idStr2Info(  buf,  &idInfo  );

	//
	add_mem( &idInfo  );

	//

	//
	display(  m_var.tSelUsrs  );

	//



errLabel:
	return;

}


void CDlgCfgGrp::OnBnClickedButtondel()
{
	// TODO: Add your control notification handler code here
		//
	//
	CQyMalloc	mallocObj;
	TCHAR  *	pT	=	NULL;

	//
	HWND  hDlg  =  m_hWnd;

	//
	HWND	hCtrl  =  ::GetDlgItem(  hDlg,  IDC_LIST_mem  );

	int			iItemSelected	=	::SendMessage(  hCtrl,  LB_GETCURSEL,  0,  0  );	
	if  (  iItemSelected  <  0  )  goto  errLabel;

	int		len  =  ::SendMessage(  hCtrl,  LB_GETTEXTLEN,  iItemSelected,  0  );
	if  (  len  <  0  )  goto  errLabel;
	len  ++  ;

	pT  =  (  TCHAR  *  )mallocObj.mallocf(  sizeof(  TCHAR  )  *  len  );
	if  (  !pT  )  goto  errLabel;
	::SendMessage(  hCtrl,  LB_GETTEXT,  iItemSelected,  (  LPARAM  )pT  );

	//
	traceLog(  _T(  "sel %s"  ),  pT  );

	//
	TCHAR  *  pT1;

	//
	pT1  =  _tcsrchr(  pT,  _T( ' ' )  );
	if  (  !pT1  )  goto  errLabel;
	
	char  buf[128];
	myTChar2Utf8(  pT1,  buf,  mycountof(  buf  )  );

	QY_MESSENGER_ID  idInfo;
	idStr2Info(  buf,  &idInfo  );

	//
	MC_VAR_isCli  *  pProcInfo   =  QY_GET_procInfo_isCli(  );
	MIS_CNT  *  pMisCnt  =  pProcInfo->getMisCntByName(  _T(  ""  )  );
	if  (  !pMisCnt  )  goto  errLabel;

	//
	if  (  pMisCnt->idInfo.ui64Id  ==  idInfo.ui64Id  )  goto errLabel;


	//
	del_mem(  &idInfo  );

	//
	display(  m_var.tSelUsrs  );


errLabel:
	return;

}


//
LRESULT  CDlgCfgGrp::OnQyComm( WPARAM  wParam, LPARAM  lParam )
{
	long				lRet				=					-1;
	QY_WMBUF_COMM	*	pComm				=					( QY_WMBUF_COMM * )lParam;
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	CCtxQmc  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	
	if  (  !pComm  )  return  -1;

	switch  (  pComm->uiType  )  {
			case  CONST_misMsgType_input:  {
				  MIS_MSG_INPUT  *  pMsgInput  =  (  MIS_MSG_INPUT  *  )pComm;
				  IM_CONTENTU			*	pContent	=	M_getMsgContent(  pMsgInput->ucFlg,  &pMsgInput->data  );
				  switch  (  pContent->uiType  )  {
						  case  CONST_imCommType_imGrp:
							    int  ill;
								ill  =  0;
								//
								m_var.idInfo_tmpGrp.ui64Id  =  pContent->imGrpEx.common.idInfo.ui64Id;
								//
								notifyProgressEnd(  &pQyMc->gui.progress,  pMsgInput->uiTranNo,  0  );  
								//
							    break;
						  default:
								  break;
				  }
				  }
				  break;
			default:
					break;
	}

	lRet  =  QY_RC_WMOK;

//  errLabel:

	return  lRet;

}


void CDlgCfgGrp::OnEnChangeEditgrpname()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

//#1015

	// TODO:  Add your control notification handler code here
	int  ii  =  0;



	return;
}
