
#include	"stdafx.h"

#include	"qyPrecomp.h"
#include	<windows.h>
#include	<tchar.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyCommProc.h"
#include	"qyLangCommProc.h"
#include	"qyTCharCommProc.h"
#include	"qyCusResPublic.h"
#include	"qnmResDefs.h"
#include	"tmpCeLib.h"




 extern  "C"  int  initQnmRes(  void  *  p0,  unsigned  short  usLangId,  int  iResId_sys,  QNM_CUSRES_INFO  *  pInfo  )
{
	 int				iErr							=		-1;
	 QY_IDCITEM		*	pItem							=		NULL;
	 TCHAR				tmpFileName[MAX_PATH  +  1];
	 TCHAR				pathBuf[MAX_PATH  +  1];
	 TCHAR			*	filePart;
	 HINSTANCE			hDll							=		NULL;
	 PF_pCommonHandler	pf								=		NULL;
	 
	 if  (  !(  pItem  =  (  QY_IDCITEM  *  )qyGetDmItemByType(  (  QY_DMITEM  *  )CONST_langStrTable,  usLangId,  sizeof(  CONST_langStrTable[0]  )  )  )  )  goto  errLabel;
	 if  (  pItem->lIdc  )  myTChar2WChar(  (  TCHAR  *  )pItem->lIdc,  pInfo->suffix,  mycountof(  pInfo->suffix  )  );

	 GetModuleFileName(  NULL,  tmpFileName,  sizeof(  tmpFileName  )  /  sizeof(  tmpFileName[0]  )  );
	 if  (  !myGetFullPathName(  tmpFileName,  sizeof(  pathBuf  )  /  sizeof(  pathBuf[0]  ),  pathBuf,  &filePart  )  )  goto  errLabel;
	 filePart[0]  =  0;
	  
	 if  (  pInfo->suffix[0]  )  {
		 _sntprintf(  tmpFileName,  sizeof(  tmpFileName  )  /  sizeof(  tmpFileName[0]  ),  _T(  "%sqyCusRes.%s.dll"  ),  pathBuf,  pInfo->suffix  );
		 if  (  !(  hDll  =  LoadLibrary(  tmpFileName  )  )  )  {
			 qyDisplayLastError(  (char*)""  );  traceLogA(  (char*)  "没找到%S",  tmpFileName  );  
		 }
	 }
	 if  (  !hDll  )  {
		 _sntprintf(  tmpFileName,  sizeof(  tmpFileName  )  /  sizeof(  tmpFileName[0]  ),  _T(  "%sqyCusRes.dll"  ),  pathBuf  );
		 if  (  !(  hDll  =  LoadLibrary(  tmpFileName  )  )  )  {
			 traceLogA(  (char*)  "LoadLibrary failed, %S",  tmpFileName  );
			 goto  errLabel;
		 }
	 }		 

	 if  (  !(  pf  =  (  PF_pCommonHandler  )myGetProcAddress(  hDll,  CONST_fn_getResTable  )  )  )  {
		 traceLogA(  (char*)  "没有找到资源文件%S的公共资源接口%s",  tmpFileName,  CONST_fn_getResTable  );  goto  errLabel;
	 }
	 if  (  !(  pInfo->pResTable  =  (  void  *  )pf(  0,  0,  0  )  )  )  {
		 traceLogA(  (char*)  "没有找到资源"  );  goto  errLabel;
	 }
#if  0
	 if  (  !(  pInfo->pSysResTable  =  (  QY_DMITEM  *  )qyGetDesByType(  (  QY_DMITEM  *  )pInfo->pResTable,  iResId_sys  )  )  )  {
		 traceLogA(  (char*)  "没找到该系统的资源"  );  goto  errLabel;
	 }
	 if  (  !(  pInfo->pCusStrTable  =  (  QY_DMITEM  *  )qyGetDesByType(  pInfo->pSysResTable,  CONST_resType_str  )  )  )  {
		 traceLogA(  (char*)  "没找到字符资源"  );  goto  errLabel;
	 }
	 if  (  !(  pInfo->pCusMenuTable  =  (  QY_DMITEM  *  )qyGetDesByType(  pInfo->pSysResTable,  CONST_resType_menu  )  )  )  {
		 traceLogA(  (char*)  "没找到菜单资源"  );  goto  errLabel;
	 }
	 if  (  !(  pInfo->pCusDlgTable  =  (  QY_DMITEM  *  )qyGetDesByType(  pInfo->pSysResTable,  CONST_resType_dlg  )  )  )  {
		 traceLogA(  (char*)  "没找到对话框资源"  );  goto  errLabel;
	 }
#endif
	 if  (  addModuleMem_qnmRes(  iResId_sys,  pInfo  )  )  goto  errLabel;

	 iErr  =  0;
errLabel:
	 if  (  iErr  )  {
		 if  (  hDll  )  FreeLibrary(  hDll  );
	 }
	 if  (  !iErr  )  {
		 if  (  pInfo  )  {
			 pInfo->hDll  =  hDll;
		 }
	 }

	 traceLogA(  (char*)  "initQnmRes %s",  iErr  ?  "Failed"  :  "Ok"  );

	 return  iErr;
}

 extern  "C"  void  exitQnmRes(  void  *  p0,  QNM_CUSRES_INFO  *  pInfo  )
{
	 if  (  pInfo  )  {
		 if  (  pInfo->hDll  )  {
			 FreeLibrary(  pInfo->hDll  );  pInfo->hDll  =  NULL;
		 }
	 }
	 return;
}

 extern  "C"  int  addModuleMem_qnmRes(  int  iResId_sys,  QNM_CUSRES_INFO  *  pInfo  )
 {
	 int			iErr	=	-1;

	 QNM_cusRes_moduleMem  *  pMem  =  NULL;
	 int						i;

	 //
	 for  (  i  =  0;  i  <  mycountof(  pInfo->mems  );  i  ++  )  {
		  pMem  =  &pInfo->mems[i];
		  if  (  pMem->iResId_sys  ==  iResId_sys  )  break;
	 }
	 if  (  i  <  mycountof(  pInfo->mems  )  )  {
		 iErr  =  0;  goto  errLabel;
	 }

	 //
	 for  (  i  =  0;  i  <  mycountof(  pInfo->mems  );  i  ++  )  {
		  pMem  =  &pInfo->mems[i];
		  if  (  !pMem->iResId_sys  )  break;
	 }
	 if  (  i  ==  mycountof(  pInfo->mems  )  )  {
		 goto  errLabel;
	 }

	 //
	 pMem->iResId_sys  =  iResId_sys;

	 if  (  !(  pMem->pSysResTable  =  (  QY_DMITEM  *  )qyGetDesByType(  (  QY_DMITEM  *  )pInfo->pResTable,  iResId_sys  )  )  )  {
		 //
		 //traceLogA(  (char*)  "没找到该系统的资源"  );  
		 //
		 goto  errLabel;
	 }
	 if  (  !(  pMem->pCusStrTable  =  (  QY_DMITEM  *  )qyGetDesByType(  pMem->pSysResTable,  CONST_resType_str  )  )  )  {
		 //
		 //traceLogA(  (char*)  "没找到字符资源"  );  
		 //
		 goto  errLabel;
	 }
	 if  (  !(  pMem->pCusMenuTable  =  (  QY_DMITEM  *  )qyGetDesByType(  pMem->pSysResTable,  CONST_resType_menu  )  )  )  {
		 //
		 //traceLogA(  (char*)  "没找到菜单资源"  );  
		 //
		 goto  errLabel;
	 }
	 if  (  !(  pMem->pCusDlgTable  =  (  QY_DMITEM  *  )qyGetDesByType(  pMem->pSysResTable,  CONST_resType_dlg  )  )  )  {
		 //
		 //traceLogA(  (char*)  "没找到对话框资源"  );  
		 //
		 goto  errLabel;
	 }

	 iErr  =  0;
	 
errLabel:

	 if  (  iErr  )  {
		 #ifdef  __DEBUG__
				 traceLog((TCHAR*)  _T(  "addModuleMem_qnmRes failed, iResId_sys %d"  ),  iResId_sys  );
		 #endif
	 }

	 return  iErr;
 }

 //
 static  int  siCurResId_sys  =  0;	//  每个模块自己定义. 2013/06/14

 extern  "C"  int  set_cur_iResId_sys(  int  iResId_sys  )
{
	MACRO_qyAssert(  !siCurResId_sys,  _T(  "iCurResId_sys has been set"  )  );
	
	if  (  siCurResId_sys  )  return  -1;

	siCurResId_sys  =  iResId_sys;

	return  0;
}

 //
 //  2015/06/30
 static  QNM_CUSRES_INFO  *  spCurQnmCusResInfo  =  NULL;

 //  2015/06/28
 extern  "C"  int   set_cur_pQnmCusResInfo(  void  *  pQnmCusResInfo  )
{
	  if  (  !pQnmCusResInfo  )  return  -1;
	  if  (  spCurQnmCusResInfo  )  return  -1;

	  //
	  spCurQnmCusResInfo  =  (  QNM_CUSRES_INFO  *  )pQnmCusResInfo;
	  return  0;
}

 //
 extern  "C"  QNM_CUSRES_INFO  *  get_cur_pQnmCusResInfo(  )
{
	  return  spCurQnmCusResInfo;
}


 //
 extern  "C"  QNM_cusRes_moduleMem  *  getCurCusResModuleMem(  QNM_CUSRES_INFO  *  pInfo  )
 {
	 int		i;
	 int		iCurResId_sys  =  siCurResId_sys;

	 //
	 if  (  !siCurResId_sys  )  {
		 MACRO_qyAssert(  siCurResId_sys,  _T(  "iCurResId_sys not set"  )  );
	 }
	
	 if  (  !pInfo  )  {
		 #ifdef  __DEBUG__
				 traceLog((TCHAR*)  _T(  "getCurCusResModuleMem failed, pInfo is null"  )  );
		 #endif
		 return  NULL;
	 }

	 //
	 for  (  i  =  0;  i  <  mycountof(  pInfo->mems  );  i  ++  )  {
		  if  (  iCurResId_sys  ==  pInfo->mems[i].iResId_sys  )  break;
	 }
	 if  (  i  ==  mycountof(  pInfo->mems  )  )  {
#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "Warning: getCurModuleMem_qnmRes returns NULL"  )  );
		MACRO_qyAssert(  0,  _T(  "getCurModuleMem_qnmRes returns NULL"  )  );
#endif
		 return  NULL;
	 }

	 return  &pInfo->mems[i];
 }

 __declspec(  dllexport  )  TCHAR  *  getResStr(  void  *  p0,  void  *  pQnmCusResInfo,  int  iResId  )
{	
	TCHAR			*	p			=	NULL;

	 QNM_CUSRES_INFO  *  pInfo		=	(  QNM_CUSRES_INFO  *  )pQnmCusResInfo;
	 //
	 if  (  !pInfo->hDll  )  goto  errLabel;
	 //
	 QNM_cusRes_moduleMem* pResMem;pResMem = getCurCusResModuleMem(pInfo);
	 if  (  !pResMem  )  goto  errLabel;

	 if  (  pInfo  )  {
		 p  =  (  TCHAR  *  )qyGetDesByType(  pResMem->pCusStrTable,  iResId  );
	 }
errLabel:

	 return    (TCHAR*)(p  ?  p  :  _T(  ""  ));
}

 //  2011/08/14
 extern  "C"  TCHAR  *  getTableResStr(  void  *  p0,  QY_DMITEM  *  pTable,  void  *  pQnmCusResInfo,  int  type  )
{	 
	 QNM_CUSRES_INFO  *  pInfo		=	(  QNM_CUSRES_INFO  *  )pQnmCusResInfo;
	 TCHAR			*	p			=	NULL;

	 if  (  !pTable  )  return  (TCHAR*)_T(  ""  );

	 QY_DMITEM	*	pItem	=	qyGetDmItemByType(  pTable,  type,  sizeof(  QY_DMITEM  )  );
	 if  (  !pItem  )  return  (TCHAR*)_T(  ""  );
	 int  iResId  =  (  int  )pItem->pData;
	 if  (  !iResId  )  return  (TCHAR*)_T(  ""  );

	 return  getResStr(  p0,  pQnmCusResInfo,  iResId  );
}


 extern  "C"  QY_DMITEM  *  getResItem(  void  *  p0,  QNM_CUSRES_INFO  *  pInfo,  int  iResId  )
{
	 void		*	pRet	=	NULL;
	 
	 QNM_cusRes_moduleMem  *  pResMem  =  getCurCusResModuleMem(  pInfo  );
	 if  (  !pResMem  )  goto  errLabel;

	 if  (  pInfo  )  {
		 pRet  =  qyGetDmItemByType(  pResMem->pCusStrTable,  iResId,  sizeof(  QY_DMITEM  )  );
	 }

errLabel:
	 return  (  QY_DMITEM  *  )pRet;
}

 extern  "C"  QY_DMITEM  *  getResTable(  void  *  p0,  QNM_CUSRES_INFO  *  pInfo,  int  iResId  )
{
	 void  *  pRet  =  NULL;

	 //  2015/07/08
	 if  (  !pInfo->hDll  )  goto  errLabel;

	 //
	 QNM_cusRes_moduleMem* pResMem;pResMem = getCurCusResModuleMem(pInfo);
	 if  (  !pResMem  )  goto  errLabel;

	 if  (  pInfo  )  {
		 QY_DMITEM	*	pTable  =  qyGetDmItemByType(  pResMem->pSysResTable,  CONST_resType_table,  sizeof(  QY_DMITEM  )  );
		 if  (  !pTable  )  goto  errLabel;
		 pRet  =  qyGetDesByType(  (  QY_DMITEM  *  )pTable->des,  iResId  );
	 }
errLabel:
	 return  pRet  ?  (  QY_DMITEM  *  )pRet  :  CONST_qyNullTable;

}

 extern  "C"  void  *  getResSearch(  void  *  p0,  QNM_CUSRES_INFO  *  pInfo,  int  iResId  )
{
	 void  *  pRet  =  NULL;

	 QNM_cusRes_moduleMem  *  pResMem  =  getCurCusResModuleMem(  pInfo  );
	 if  (  !pResMem  )  goto  errLabel;

	 QY_DMITEM* pTable;pTable = qyGetDmItemByType(pResMem->pSysResTable, CONST_resType_search, sizeof(QY_DMITEM));
	 if  (  !pTable  )  goto  errLabel;
	 pRet  =  qyGetDesByType(  (  QY_DMITEM  *  )pTable->des,  iResId  );

errLabel:
	 return  pRet;

}

 extern  "C"  void  *  getResQueryStruct(  void  *  p0,  QNM_CUSRES_INFO  *  pInfo,  int  iResId  )
{
	 void  *  pRet  =  NULL;

	 QNM_cusRes_moduleMem  *  pResMem  =  getCurCusResModuleMem(  pInfo  );
	 if  (  !pResMem  )  goto  errLabel;

	 QY_DMITEM* pTable;pTable = qyGetDmItemByType(pResMem->pSysResTable, CONST_resType_query, sizeof(QY_DMITEM));
	 if  (  !pTable  )  goto  errLabel;
	 pRet  =  qyGetDesByType(  (  QY_DMITEM  *  )pTable->des,  iResId  );

errLabel:
	 return  pRet;

}

extern  "C"  void  *  getResColumnInfo(  void  *  p0,  QNM_CUSRES_INFO  *  pInfo,  int  iResId  )
{
	 void  *  pRet  =  NULL;
	 
	 QNM_cusRes_moduleMem  *  pResMem  =  getCurCusResModuleMem(  pInfo  );
	 if  (  !pResMem  )  goto  errLabel;


	 QY_DMITEM* pTable;pTable = qyGetDmItemByType(pResMem->pSysResTable, CONST_resType_columnInfo, sizeof(QY_DMITEM));
	 if  (  !pTable  )  goto  errLabel;
	 pRet  =  qyGetDesByType(  (  QY_DMITEM  *  )pTable->des,  iResId  );

errLabel:
	 return  pRet;

}


 BOOL  CALLBACK  myEnumChildProc(  HWND  hCtrl,  LPARAM  lParam  )
{
	COMMON_PARAM	*	pCommonParam	=	(  COMMON_PARAM  *  )lParam;
	HWND				hParent			=  GetParent(  hCtrl  );
	int					id;
	//  char				buf[256];
	//  char				buf1[256];
	QNM_CUSRES_INFO	*	pCusRes			=	(  QNM_CUSRES_INFO  *  )pCommonParam->p1;
	QY_DMITEM		*	pTable			=	(  QY_DMITEM  *  )pCommonParam->p2;
	QY_DMITEM		*	pItem;
	int					iResId			=	0;

	id  =  GetDlgCtrlID(  hCtrl  );
	//  GetDlgItemText(  hParent,  id,  buf,  sizeof(  buf  ) );
	//  _snprintf(  buf1,  sizeof(  buf1  ),  "id is %d, title is %s\n",  id,  buf  );
	//  OutputDebugString(  buf1  );
	//  if  (  id  ==  IDC_STATIC_item  )  SetDlgItemText(  hParent,  id,  "Hello"  );
	pItem  =  qyGetDmItemByType(  pTable,  id,  sizeof(  QY_DMITEM  )  );
	if  (  pItem  )  iResId  =  (  int  )pItem->des  ?  (  int  )pItem->des  :  pItem->type;
	SetDlgItemText(  hParent,  id,  getResStr(  0,  pCusRes,  iResId  )    );

	return  TRUE;
}
 


 int  cusDlgRes(  void  *  p0,  void  *  pQnmCusResInfo,  HWND  hDlg,  int  IDD  )
{
	 int				iErr	=	-1;
	 QNM_CUSRES_INFO  *  pInfo	=	(  QNM_CUSRES_INFO  *  )pQnmCusResInfo;
	 COMMON_PARAM		commonParam;
	 QY_DMITEM		*	pItem	=	NULL;
	 
	 QNM_cusRes_moduleMem  *  pResMem  =  getCurCusResModuleMem(  pInfo  );
	 if  (  !pResMem  )  goto  errLabel;


	 if  (  !(  pItem  =  qyGetDmItemByType(  pResMem->pCusDlgTable,  IDD,  sizeof(  QY_DMITEM  )  )  )  )  {
		 traceLogA(  (char*)  "no cusRes for dialog IDD %d",  IDD  );  goto  errLabel;
	 }
	 SetWindowText(  hDlg,  getResStr(  0,  pInfo,  (  int  )pItem->pData  ?  (  int  )pItem->pData  :  pItem->type  )  );
	 MACRO_makeCommonParam3(  0,  pInfo,  (  QY_DMITEM  *  )pItem->des,  commonParam  );
	 myEnumChildWindows(  hDlg,  myEnumChildProc,  (  LPARAM  )&commonParam  );

	 iErr  =  0;
errLabel:
	 return  iErr;
}


