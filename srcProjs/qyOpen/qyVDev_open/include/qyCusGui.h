
#ifndef  __QYCUSGUI_H__
#define  __QYCUSGUI_H__  //  {


//  输入窗口类
#define		DEFAULT_qyMcInputWndCls		_T(  "qyMcInputWndCls"  )
#define		DEFAULT_qmcCmdProcWndCls	_T(  "qmcCmdProcWndCls"  )	//  2009/12/22


//  事件类型
#define		CONST_qyEventType_null							0
#define		CONST_qyEventType_dblClick						1
#define		CONST_qyEventType_rClick						2
#define		CONST_qyEventType_cmd							3



typedef  struct  __qyEventInfo_t							{
				 int										type;
				 HWND										hWnd;							//  2007/09/06, 此窗口应为接收事件的窗口，不一定是点击所在的控件窗口.
				 HWND										hFrom;							//  此为发生事件的窗口的句柄
				 BOOL										bDlg;							//  是否对话框
				 //  HWND										hCtrl;							//  2012/07/20
				 struct										{
					 int									x,  y;
				 }											click;
				 unsigned  int								uiDefaultCmd;
				 //  
				 unsigned  char								ucbNotSelected;					//  2006/04/16加
				 unsigned  char								ucbMultiSelected;				//  2007/08/24
				 //
				 unsigned  int								uiCmd;							//  需要执行的命令。
				 //
				 unsigned  char								ucbRefreshed;					//  命令执行之后，是否需要刷新显示。
				 //
				 
}		 QY_EVENTINFO;


#define		CONST_qyMaxLvCols								30

// 以下用于表示以ListView形式显示的浏览条目内容
typedef  struct  __qyItemContent_t							{
				 int										type;
				 union										{
						char								cols[CONST_qyMaxLvCols][255  +  1];
				 }											u;
}		 QY_ITEMCONTENT;


typedef  struct  __qyMcViewSel_t							{											//  2006/12/24
				 int										type;

				 int										iDsnIndex;									//  2007/01/01

				 TCHAR										preDocName[32 + 1];
				 TCHAR										docName[CONST_qyMaxDocNameLen  +  1];
				 TCHAR										postDocName[32 + 1];

				 PF_commonHandler							pfDisplayListContent;						//  显示右边的listView, 2004/07/27

				 PF_commonHandler							pfProcEvent;
				 PF_commonHandler							pfProcCmd;									//  int  procCmdFunc(  0,  void  *  pSelParam,  void  *  pEventInfoParam  )

				 //
				 void							*			pCusRes;									//  2008/01/02
				 UINT										uPopupMenuId;
				 int										nSubMenuPos;
				 int										nSubMenuPos_multiSel;						//  2007/08/24, 多选弹出菜单
				 int										nSubMenuPos_notSel;							//  2006/04/16, 当点击列表空白处时，弹出的子菜单
				 unsigned  int								uiDefaultCmd;								//  2004/04/17加，当双击时，激发的命令
 
				 //
				 unsigned  char								ucbMultiSel;								//  2007/08/24, 是否可多选

				 int										curnItem;
				 QY_ITEMCONTENT								curItemContent;

}		 QY_MCVIEW_SEL;



BOOL  bQyOpenMcView(  QY_MCVIEW_SEL  *  pParam,  void  *  p1,  void  *  p2  );
void  qyMcView_delAllColumns(  void  *  pView,  void  *  p1,  void  *  p2  );
BOOL  qyMcView_bAddColumns(  void  *  pView,  QY_COLUMNINFO * pColumns,  void  *  p2  );






typedef  int  (  *PF_procLvEventFunc  )(  QY_EVENTINFO  *  pEventInfo,  void  *  pObjDb,  int  iLvType,  int  curnItem,  BOOL  bFirst,  void  *  pParam  );
typedef  int  (  *PF_enumLvSelEventFunc  )(  QY_EVENTINFO  *  pEventInfo,  PF_procLvEventFunc  pf,  void  *  pObjDb,  int  iLvType,  void  *  pParam  );
 //  此函数可允许取选中的行号curnItem的特定列名的字段内容.  如果没有列名，则取第一个字段
typedef  int  (  *PF_getLvColContent  )(  HWND  hParent,  HWND  hList,  int  curnItem,  LPCTSTR  colName,  TCHAR  *  buf,  unsigned  int  size  );
//
typedef  int  (  *PF_postHint2Mgr_mc_open  )(  void  *  pQyVDevParam,  WCHAR  *  who,  time_t  tStartTime,  unsigned  int  uiTranNo,  LPCTSTR  str  );
//
typedef  int  (  *PF_postStr2Mgr_mc_open  )(  void  *  pQyVDev,  unsigned  int  uiObjType_from,  unsigned  int  uiDevType_from,  WCHAR  *  wDevIdStr_from,  WCHAR  *  wReversePath,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  LPCTSTR  str,  char  *  idStr_to,  unsigned  int  uiChannelType  );
//
typedef  int  (  *PF_postReq2Mgr_mc_open  )(  void  *  pQyVDev,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  char  *  pVDevReqParam,  unsigned  int  dataLen  );



//
typedef  struct  __qyGuiOpen_vDev_t							{
	
				 PF_bCommonHandler							pf_bGetLongProperty;		//  BOOL  bGetLongProperty(  void  *  p0,  int  propertyId,  long  *  pVal  );

				 PF_commonHandler							pf_bQyOpenMcView;			//  (  QY_MCVIEW_PARAM  *  pParam,  void  *  p1,  void  *  p2  )
				 PF_commonHandler							pf_qyMcView_delAllColumns;
				 PF_commonHandler							pf_qyMcView_bAddColumns;

				 PF_enumLvSelEventFunc						pf_enumLvSelEventFunc;
				 PF_getLvColContent							pf_getLvColContent;

				 PF_postHint2Mgr_mc_open					pf_postHint2Mgr_mc_open;
				 PF_postStr2Mgr_mc_open						pf_postStr2Mgr_mc_open;
				 PF_postReq2Mgr_mc_open						pf_postReq2Mgr_mc_open;

}		 QY_GUI_OPEN_vDev;


#endif  //  }


