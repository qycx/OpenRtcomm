


#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"tmpCeLib.h"

#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

//  #include	"qyFile.h"

//#include	"myresource.h"

#include	"qmcVWall.h"
//  #include	"DlgDynBmps.h"

#include	"qyCusResTemp.h"

#include	"isCliHelpPublic.h"

 //  2013/06/10
 void * vw_getCurSp(  void  *  pCQyVWall  )
 {
	 CQyVWall  *  p  =  (  CQyVWall  *  )pCQyVWall;

	 if  (  !p  )  return  NULL;
	 return  p->getCurSp(  );
 }


//
CQyVWall::CQyVWall(  )
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CQyVWall::~CQyVWall(  )
{
	_ASSERT(  !m_var.usCnt  );
	return;
}

//  2012/03/25. CONST_uiMaxQNodes_vwRuleQ取值过大,会引起视频实时任务的CreateThread失败,rc为8,表示内存不足.同时dmo经常死了. 因此限制为50.
//  注: 此限制也许是32位软件的缘故. 64位版本可能会不止这个限制.



int  CQyVWall::addSubWall(  int  idc,  int  idcHint  )
{
	int				iErr		=	-1;
	int				i;
	SUB_V_WALL	*	pSubWall	=	NULL;

	if  (  m_var.usCnt  >=  mycountof(  m_var.memPtrs  )  )  return  -1;

	for  (  i  =  0;  i  <  m_var.usCnt;  i  ++  )  {
		 if  (  !m_var.memPtrs[i]  )  goto  errLabel;
		 if  (  m_var.memPtrs[i]->idc  ==  idc  )  break;
	}
	if  (  i  <  m_var.usCnt  )  {
		iErr  =  0;  goto  errLabel;
	}
	
	pSubWall  =  (  SUB_V_WALL  *  )mymalloc(  sizeof(  SUB_V_WALL  )  );
	if  (  !pSubWall  )  goto  errLabel;
	memset(  pSubWall,  0,  sizeof(  SUB_V_WALL  )  );
	if  (  !IsWindow(  m_var.hWnd  )  )  {
		traceLogA(  (char*)  "QyVWall::addSubWall failed, hWnd is not a valid window."  );
		goto  errLabel;
	}

	pSubWall->idc  =  idc;
	pSubWall->idcHint  =  idcHint;
	pSubWall->hWnd_subWall  =  idc  ?  GetDlgItem(  this->m_var.hWnd,  idc  )  :  this->m_var.hWnd;
	if  (  !pSubWall->hWnd_subWall  )  goto  errLabel;

	if  (  initSp(  &pSubWall->pSp  )  ) goto  errLabel;
	pSubWall->bSpInited  =  TRUE;

	if  (  !(  pSubWall->pRuleQ  =  genericQNew(  _T(  "ruleQ"  ),  NULL,  0,  get_uiMaxQNodes_vwRuleQ(  ),  mymalloc,  myfree  )  )  )  goto  errLabel;

	m_var.memPtrs[i]  =  pSubWall;
	m_var.usCnt  ++  ;

	iErr  =  0;
errLabel:

	if  (  iErr  )  {
		if  (  pSubWall->pRuleQ  )  genericQFree(  pSubWall->pRuleQ  );
		if  (  pSubWall->bSpInited  )  exitSp(  &pSubWall->pSp  );
		if  (  pSubWall  )  free(  pSubWall  );
	}

	return  iErr;
}

 SUB_V_WALL  *	 CQyVWall::getSubWall(  int  index  )
{
	if  (  index  <  0  ||  index  >  m_var.usCnt  )  return  NULL;
	return  m_var.memPtrs[index];
}

 void  CQyVWall::removeSubWall(  int  index  )
{
	SUB_V_WALL	*	pSubWall	=	NULL;
	int				i, j;

	pSubWall  =  getSubWall(  index  );
	if  (  !pSubWall  )  return;

	for  (  i  =  index;  i  <  m_var.usCnt  -  1;  i  ++  )  {
		 m_var.memPtrs[i]  =  m_var.memPtrs[i  +  1];
	}
	m_var.usCnt  --  ;

	//  CWnd	*	pWnd	=	CWnd::FromHandle(  m_var.hWnd  );
	HWND  hWnd  =  m_var.hWnd;

	if  (  pSubWall->hBmp_background  )  {		//  2009/10/05
		DeleteObject(  pSubWall->hBmp_background  );  pSubWall->hBmp_background  =  NULL;
	}

	if  (  pSubWall->bSpInited  )  exitSp(  &pSubWall->pSp  );
	if  (  pSubWall->pRuleQ  )  genericQFree(  pSubWall->pRuleQ  );
	for  (  j  =  0;  j  <  pSubWall->usCnt;  j  ++  )  {
		 old_freeCapImages(  hWnd,  pSubWall->idc,  &pSubWall->mems[j].images,  pSubWall->hWnd_dst,  &pSubWall->hDc_dst,  _T(  "removeSubWall.132"  ));
	}
	free(  pSubWall  );

}

 void  CQyVWall::removeAllSubWalls(  )
{
	int  i;
	for  (  i  =  m_var.usCnt  -  1;  i  >=  0;  i  --  )  {
		 removeSubWall(  i  );
	}
	return;
}


 //
 void  CQyVWall::resetSubWall(  int  index  )
{
	SUB_V_WALL	*	pSubWall	=	NULL;
	int				j;

	pSubWall  =  getSubWall(  index  );
	if  (  !pSubWall  )  return;

	//  CWnd	*	pWnd	=	CWnd::FromHandle(  m_var.hWnd  );
	HWND	hWnd  =  m_var.hWnd;

	if  (  pSubWall->hBmp_background  )  {		//  2009/10/05
		DeleteObject(  pSubWall->hBmp_background  );  pSubWall->hBmp_background  =  NULL;
	}

	if  (  pSubWall->bSpInited  )  {
		resetSp(  pSubWall->pSp  );
	}
	if  (  pSubWall->pRuleQ  )  emptyGenericQ(  pSubWall->pRuleQ  );
	for  (  j  =  0;  j  <  pSubWall->usCnt;  j  ++  )  {
		 old_freeCapImages(  hWnd,  pSubWall->idc,  &pSubWall->mems[j].images,  pSubWall->hWnd_dst,  &pSubWall->hDc_dst,  _T(  "resetSubWall.169"  ));
	}

	return;
}


 //
 SUB_V_WALL  *  CQyVWall::getCurSubWall(  )
 {
	 return  getSubWall(  m_var.curSpIndex  );
 }

  void  *  CQyVWall::getCurSp(  )
 {
	 SUB_V_WALL	*	pSubWall	=	getCurSubWall(  );
	 if  (  !pSubWall  )  return  NULL;

	 if  (  !pSubWall->bSpInited  )  return  NULL;
	 return  pSubWall->pSp;
 }

  int  CQyVWall::setBitmap(  LPCTSTR  szFileName,  int  index  )
{
	int				iErr	=	-1;
	SUB_V_WALL	*	pSubWall	=	getSubWall(  index  );
	if  (  !pSubWall  )  return  -1;

	if  (  !szFileName  ||  !szFileName[0]  )  return  -1;

	if  (  pSubWall->hBmp_background  )  {
		DeleteObject(  pSubWall->hBmp_background  );  pSubWall->hBmp_background  =  NULL;
	}

	unsigned  int  fuLoad  =  0;
#ifndef  __WINCE__
	fuLoad  =  LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE;
#endif
	pSubWall->hBmp_background  =  (  HBITMAP  )LoadImage(  NULL,  szFileName,  IMAGE_BITMAP,  0,  0,  fuLoad  );
	if  (  pSubWall->hBmp_background  ==  NULL  )  goto  errLabel;
	
	BITMAP	bitmap;
	GetObject(  pSubWall->hBmp_background,sizeof(BITMAP),&bitmap) ;
	pSubWall->iX_org  =  0;
	pSubWall->iY_org  =  0;
	pSubWall->iW_org  =  bitmap.bmWidth;
	pSubWall->iH_org  =  bitmap.bmHeight;

	pSubWall->iX  =  pSubWall->iX_org;
	pSubWall->iY  =  pSubWall->iY_org;
	pSubWall->iW  =  pSubWall->iW_org;
	pSubWall->iH  =  pSubWall->iH_org;

	lstrcpyn(  pSubWall->fileName_background,  szFileName,  mycountof(  pSubWall->fileName_background  )  );

	iErr  =  0;
errLabel:

	return  iErr;

}


  int  CQyVWall::resetBitmap(  int  index  )
{
	SUB_V_WALL	*	pSubWall	=	getSubWall(  index  );
	if  (  !pSubWall  )  return  -1;

	if  (  pSubWall->hBmp_background  )  {
		DeleteObject(  pSubWall->hBmp_background  );  pSubWall->hBmp_background  =  NULL;
	}

	return  0;
}









QY_DMITEM  CONST_qyPropTypeTable[]  =
{
	{	CONST_qyPropType_pos,							(TCHAR*)_T(  "pos"  ),		},
	{	CONST_qyPropType_dep,							(TCHAR*)_T(  "dep"  ),		},
	{	CONST_qyPropType_horz,							(TCHAR*)_T(  "horz"  ),		},
	{	CONST_qyPropType_vert,							(TCHAR*)_T(  "vert"  ),		},
	//
	{	CONST_qyPropType_save,							(TCHAR*)_T(  "save"  ),		},		//  2014/08/08
	//
	{	CONST_qyPropType_dynBmp,						(TCHAR*)_T(  "dynBmp"  ),	},
	{	CONST_qyPropType_imGrp,							(TCHAR*)_T(  "imGrp"  ),	},
	{	CONST_qyPropType_messenger,						(TCHAR*)_T(  "msgr"  ),		},
	//
	{	-1,		},
};









__declspec(  dllexport  ) int  myGetProps_vw(  char  *  buf,  void  *  pQY_props  )
{
	//  AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int				iErr	=	-1;
	char		*	p,  *  p1;
	char			phrase[128];
	char			content[2048];
	int				iType;

	QY_props	*   pProps  =  (  QY_props  *  )pQY_props;
	
	for  (  p  =  buf,	p1  =  strchr(  p,  '='  );  ;  )  {
		 if  (  !p  ||  !p1  )  break;
		 safeStrnCpy(  p,  phrase,  min(  mycountof(  phrase  ),  p1  -  p  +  1  )  );
		 iType  =  qyGetTypeByDes(  CONST_qyPropTypeTable,  CQyString(  phrase  )  );
		 if  (  iType  <  0  )  goto  errLabel;

		 p1  ++  ;
		 p  =  strchr(  p1,  ':'  );
		 if  (  !p  )  safeStrnCpy(  p1,  content,  mycountof(  content  )  );
		 else  {
			   safeStrnCpy(  p1,  content,  min(  mycountof(  content  ),  p  -  p1  +  1  )  );
			   p  ++  ;
		 }

		 if  (  pProps->usCnt  >=  mycountof(  pProps->mems  )  )  goto  errLabel;
		 QY_propMem	*	pProp	=	&pProps->mems[pProps->usCnt];
		 memset(  pProp,  0,  sizeof(  pProp[0]  )  );
		 pProp->uiType  =  iType;

		 char		*	p2  =	content;
		 //  char		*	p3	=	NULL;
		 switch  (  iType  )  {
				 case  CONST_qyPropType_pos:  {
					   SP_COORD  *  pPos  =  (  SP_COORD  *  )&pProp->u.pos.coord;
					   //
					   pPos->rect.x  =  atol(  p2  );
					   if  (  !(  p2  =  strchr(  p2,  ','  )  )  )  goto  errLabel;
					   p2  ++  ;
					   pPos->rect.y  =  atol(  p2  );
					   }
					   break;
				 case  CONST_qyPropType_dep:  {
					   for  (  ;  ;  )  {
						    if  (  pProp->u.dep.usCnt  >=  mycountof(  pProp->u.dep.uiTranNo_spObjs  )  )  goto  errLabel;
							pProp->u.dep.uiTranNo_spObjs[pProp->u.dep.usCnt]  =  atol(  p2  );
							pProp->u.dep.usCnt  ++  ;
							if  (  !(  p2  =  strchr(  p2,  ','  )  )  )  break;
							p2  ++  ;
					   }
					   }
					   break;
				 case  CONST_qyPropType_horz:
				 case  CONST_qyPropType_vert:
					   break;
				 case  CONST_qyPropType_save:		//  2014/08/08
					   break;
				 case  CONST_qyPropType_dynBmp:
					   idStr2Info(  p2,  &pProp->u.dynBmp.idInfo  );
					   if  (  !(  p2  =  strchr(  p2,  ','  )  )  )  goto  errLabel;
					   p2  ++  ;
					   pProp->u.dynBmp.uiObjType  =  atol(  p2  );
					   if  (  !(  p2  =  strchr(  p2,  ','  )  )  )  goto  errLabel;
					   p2  ++  ;
					   pProp->u.dynBmp.usIndex_obj  =  atol(  p2  );
					   break;
				 case  CONST_qyPropType_imGrp:
					   idStr2Info(  p2,  &pProp->u.imGrp.idInfo  );
					   break;
				 case  CONST_qyPropType_messenger:
					   idStr2Info(  p2,  &pProp->u.messenger.idInfo  );
					   break;
				 default:
					     break;
			 
		 }
		 pProps->usCnt  ++  ;

		 if  (  !p  )  break;
		 p1  =  strchr(  p,  '='  );
		 continue;
	}
	

	iErr  =  0;
errLabel:
	return  iErr;	
}

 

 













