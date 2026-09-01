 
#ifndef  __QNMMAINPROCMIS_H__
#define  __QNMMAINPROCMIS_H__  //  {


typedef  struct  __param_applyForServWork_t				{
				 unsigned  int							uiType;		//  对组来说，通常指CONST_imCommType_refreshImGrp
				 //
				 unsigned  short						usOp;		//  2017/07/29
				 //
				 void								*	p0;
				 void								*	p1;
				 void								*	p2;		
				 //
}		 PARAM_applyForServWork;


typedef  struct  __param_procLvEventFunc_is_t			{		
				 TCHAR									misServName[CONST_maxMisServNameLen  +  1];
				 time_t									t;
				 //
				 QY_MESSENGER_ID						idInfo;				//  2009/09/17
				 //
				 QY_MESSENGER_ID						idInfo_grp;
				 unsigned  short						usSubtype;			//  2014/07/28
				 int									nGrpMems;			//  2014/02/03
				 //
				 PARAM_applyForServWork					param_applyForServWork;

				 //  这个Q是为了形成临时组用的
				 GENERIC_Q								tmpGrpMemQ;
				 BOOL									bTmpQInited;
				 //
}		 PARAM_procLvEventFunc_is;


int  getScreenXy(  int  *  pScreenX,  int  *  pScreenY  );


int  getMessengerImages(  QY_MC  *  pQyMc,  unsigned  short  usRunningStatus,  int  *  pnImage,  int  *  pnSelectedImage  );

//
void  myPostQuitMessage(  int nExitCode  );


//
int  getSthForObjs(  QM_dbFuncs  *  pDbFuncs,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  tabName_regInfo,  QY_OBJINDEX_RCD  *  pObjIndex,  int  *  pIndexDisplayed,  int  *  pIndexToDisplay,  int  *  piObjTypeToDisplay,  TCHAR  *  whereClause,  unsigned  int  size  );


//
BOOL  bViewImMsgToday(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  wherePart  );
BOOL  bViewImMsgListFunc_isMgr(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewImMsgListFunc(   QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );

BOOL  bViewImObjView(   QY_OBJ_DB  *  pObjDb  );


//
BOOL  bViewImObjAuthList_isMgr(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewImObjAuthNeedAuditedList_isMgr(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewImAmList_isMgr(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );

BOOL  bViewPhoneMessengerList(   QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );


int  applyForServWork(  unsigned  int  uiContentType,  unsigned  short  usOp,  void  *  p0,  void  *  p1,  void  *  p2  );	//  申请服务器做一些工作

BOOL  bNewMessenger(  );
BOOL  bNewImGrp(  );
BOOL  bViewImGrpAuthList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
//
__declspec(  dllexport  ) BOOL  bViewImObjListFunc(   QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
//
BOOL  bViewMessengerList(   QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
__declspec(  dllexport  )  BOOL  bViewMessengerRegInfoList( QY_MC  *  pQyMc, QY_OBJ_DB  *  pObjDb  );
//
__declspec(  dllexport  ) BOOL  bViewImGrpList( QY_MC  *  pQyMc, QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
//  BOOL  bViewImGrpMemList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
__declspec(  dllexport  )  BOOL  bViewImGrpMemList_isClient(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
//
BOOL  bViewCustomerServiceOfficerList( QY_MC  *  pQyMc, QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,	LPCTSTR  wherePart  );
BOOL  bViewWebContactList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewIpKnowledgeList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,	LPCTSTR  wherePart  );
//
BOOL  bViewPhoneGuestList(  QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,	LPCTSTR  wherePart  );

BOOL  bViewGsmModemList_isMgr(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewSmContactList_isMgr(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );


__declspec( dllexport  )  BOOL  bViewImTaskListFunc(   QY_MC  *  pQyMc,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart,  BOOL  bHisTab  );
//
//  
__declspec(  dllexport  )  BOOL  bViewRealTimeImTaskList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
__declspec(  dllexport  )  BOOL  bViewTaskInfoList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
__declspec(  dllexport  )  BOOL  bViewSharingObjectList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
__declspec(  dllexport  )  BOOL  bViewPlayerList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
__declspec(  dllexport  )  BOOL  bViewWallList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
__declspec(  dllexport  )  BOOL  bViewIpCamList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
__declspec(  dllexport  )  BOOL  bViewImNetStatList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
__declspec(  dllexport  )  BOOL  bViewTalkerList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
__declspec(  dllexport  )  BOOL  bViewMessengerStatusList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );

//  int viewStatusCli(  int  iWndContentType,  int  iSubType,  LPCTSTR  title,  int  iResId_listColumns,  PF_commonHandler  pfDisplayListContent  );
int viewStatusDaemon(  int  index  );
__declspec(  dllexport  )  int viewQnmStatus(  );
int popupToWarn(  );

#ifdef  __SUPPORT_dlgWalls__
		//  int  viewWalls(  );		//  2011/02/28. touchscreen
		//  int  qisChkWalls(  );
#endif


//  BOOL  bViewEventListFunc_is(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause );

BOOL  bViewSharedDynBmpList_isMgr(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause  );
//__declspec(  dllexport  )  BOOL  bViewSharedDynBmpList_isClient(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause  );

BOOL  bViewSharedDynBmpRuleList( QY_MC  *  pQyMc, QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause  );



//  2014/10/29
 __declspec(  dllexport  )  int  newTaskId(  void  *  pDb,  int  iDbType  );

//
__declspec(  dllexport  )  int  postRecentFriend(  void  *  pMisCntParam,  QY_MESSENGER_ID    idInfo,  int  iOp  );




__declspec(  dllexport  )  int  doCmd_test(  int  iMenuId  );
//
__declspec(  dllexport  )  void myListCtrl_delAllColumns(  HWND  hListCtrl  );
__declspec(  dllexport  )  BOOL myListCtrl_bAddColumns(  HWND  hListCtrl,  QY_COLUMNINFO * pColumns  );
//
_declspec(  dllexport  )  int  myListCtrl_InsertItem(  HWND  hListCtrl,  int nItem, LPCTSTR lpszItem  );
__declspec(  dllexport  )  int  myListCtrl_InsertItem(  HWND  hListCtrl,  int nItem, LPCTSTR lpszItem, int nImage  );
__declspec(  dllexport  )  BOOL myListCtrl_SetItemText(  HWND  hListCtrl,  int nItem, int nSubItem, LPCTSTR lpszText);
__declspec(  dllexport  )  BOOL myListCtrl_SetItemData(  HWND  hListCtrl,  int nItem, DWORD_PTR dwData  );
__declspec(  dllexport  )  BOOL myListCtrl_DeleteAllItems(  HWND  hListCtrl  );
__declspec(  dllexport  )  int  myListCtrl_GetItemCount(  HWND  hListCtrl  );
__declspec(  dllexport  )  BOOL myListCtrl_SetItemState(  HWND  hListCtrl,  int nItem, UINT nState, UINT nMask  );
__declspec(  dllexport  )  int  myListCtrl_GetItemText(  HWND  hListCtrl,  int nItem,  int nSubItem,  LPTSTR lpszText,  int nLen  );
__declspec(  dllexport  )  int  myListCtrl_InsertColumn(  HWND  hListCtrl,  int nCol,  const LVCOLUMN* pColumn);
__declspec(  dllexport  )  BOOL myListCtrl_GetColumn(  HWND  hListCtrl,  int nCol, LVCOLUMN* pColumn  );
__declspec(  dllexport  )  int  myListCtrl_FindItem(  HWND  hListCtrl,  LVFINDINFO* pFindInfo, int nStart  );
__declspec(  dllexport  )  BOOL myListCtrl_GetItem(  HWND  hListCtrl,  LVITEM* pItem  );
__declspec(  dllexport  )  BOOL myListCtrl_SetItem(  HWND  hListCtrl,  LVITEM* pItem  );
__declspec(  dllexport  )  BOOL myListCtrl_Update(  HWND  hListCtrl,  int nItem  );
__declspec(  dllexport  )  BOOL myListCtrl_ModifyStyle(  HWND  hListCtrl,  DWORD dwRemove,   DWORD dwAdd,   UINT nFlags );
__declspec(  dllexport  )  DWORD myListCtrl_SetExtendedStyle(  HWND  hListCtrl,  DWORD dwNewStyle);
__declspec(  dllexport  )  void  *  myListCtrl_SetImageList(  HWND  hListCtrl,  void  * pImageList,  int nImageList);
//

__declspec(  dllexport  )  void  myImageList_free(  void  *  pImageListParam  );
__declspec(  dllexport  )  void  *  myImageList_new(  UINT nBitmapID, int cx, int nGrow, COLORREF crMask  );




#endif  //  }


