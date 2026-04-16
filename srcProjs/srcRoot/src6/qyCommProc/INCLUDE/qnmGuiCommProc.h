
#ifndef  __QNMGUICOMMPROC_H__
#define  __QNMGUICOMMPROC_H__	/*  {  */


#ifdef  __cplusplus
  extern  "C"  {
#endif

typedef  struct  __qwmRegStruct_t			{

				 int						iSystemId_wanted;	//  2005/09/24
				 unsigned  int				uiQwmType;			//  2004/05/14添加
				 QWM_DYN_CFG				dynCfg;				//  2006/07/01修改
				 //  QY_LOGICAL_SERVER			cnt;
				 unsigned  char				ucbSecChkQuickly;	//  是否快速安检
				 unsigned  char				ucbNoGui;			//  是否无界面
				 unsigned  char				ucbGetPcAsset;		//  是否进行资产管理
				 unsigned  char				ucbDj;				//  是否单机版			2005/08/18

				 void					*	pRegInfoParam;		//  可以用作输入赋初值. 当pRegInfo为NULL时为新注册。
				 unsigned  char				ucbInstall;
				 unsigned  short			idrData;
				 QY_DMITEM				*	pSecChkTaskTable;
				 unsigned  int				uiSecChkCnt;		//  已使用检查次数
				 
}		 QWM_REG_STRUCT;


typedef  struct  __qrtLayoutCfg_t			{												//  以开发环境中的手工设置单位为单位
				 
				 unsigned  short			bj,  staticW,  staticEditHjg,  editW,  midHjg;	//  边距，static宽度，static与edit的水平间隔，edit宽度，中间的水平间隔
				 unsigned  short			idcH,  comboH,  idcVjg;							//  最高的编制的顶，控件高度，控件纵向间隔
				 unsigned  short			staticHint1Vjg,  hint1ProgressVjg;
				 unsigned  short			progressOkVjg;
				 unsigned  short			dlgTitleHeight;									//  窗口的题头
				 unsigned  short			titleW,  titleH;								//	我们的题头
				 unsigned  short			hint0H;											//  提示0的高度
				 unsigned  short			okW,  okCancelHjg;
				 unsigned  short			bbj;											//  底边距
				 //
				 unsigned  long				ulDlgWidth,  ulDlgHeight;				 
}		 QRT_LAYOUT_CFG;


typedef  struct  __qnmGuiMenu_t				{
				 HMENU						hSubMenuMcMgr;
				 HMENU						hSubMenuMcSystem;
				 HMENU						hSubMenuMcCfg;
}		 QNM_GUI_MENU;


//
//  自定义菜单命令
//
#define		CONST_qyMenuId_base				20000
#define		ID_qyEdit_switchRule			(  CONST_qyMenuId_base  +  1  )


//
//
//

extern  LONG				gQyOldEditProc;

LPARAM  CALLBACK	qyRestrictEditProc(  HWND  hWnd,  UINT  msg,  WPARAM  wParam,  LPARAM  lParam  );
//  void  qnmSizeRegToolControls(  HWND  hDlg,  QY_IDCITEM  *  pTotalTable,  QY_IDCITEM  *  pCurTable,  BOOL  bEdit  );
void  qnmSizeRegToolControls(  QNM_CUSRES_INFO  *  pCusRes,  HWND  hDlg,  QY_IDCITEM  *	 pTotalTable,  QY_IDCITEM  *  pCurTable,  BOOL  bEdit  );
//  int  procCbSelChange(  QY_IDCITEM  *  pTotalTable,  QY_IDCITEM  **  ppTables,  HWND  hDlg,  int  idc,  BOOL  bEdit  );
int  procCbSelChange(  QNM_CUSRES_INFO  *  pCusRes,  QY_IDCITEM  *  pTotalTable,  QY_IDCITEM  **  ppTables,  HWND  hDlg,  int  idc,  BOOL  bEdit  );
int  qwmRegProc(  void  *  pDynLib,  QWM_REG_STRUCT  *  pQwmRegStruct  );

BOOL  bQrtQuit(  );
int  initSecChk(  QY_DMITEM  *  pSecChkTaskTable  );
void  exitSecChk(  );
int  doNoGuiChkPcInfo(  LPVOID  lpParameter  );
int  setDlgIdcSize(  int  iIDC_title,  int  iIDC_hint0,  int  iIDC_hint1,  int  iIDC_PROGRESS_reg,  QNM_CUSTOM_COMM  *  pCustom,  QRT_LAYOUT_CFG  *  pIdcCfg,  QY_IDCITEM  *  pTable0  );
int  setDlgIdcParams(  QRT_LAYOUT_CFG  *  pIdc  );

BOOL  bFieldLikeDw(  int  fieldId  );  
BOOL  bFieldLikeZcbh(  int  fieldId,  BOOL  *  pbRealZcbh  );


#ifdef  __cplusplus
  }
#endif


BOOL  bGetRegInfoFromDlg(  QNM_CUSRES_INFO  *  pCusRes,  HWND  hWnd,  QY_IDCITEM  *  gpTable0,  unsigned  char  ucbUtf8,  QNM_REG_INFO  *  pRegInfo  );
BOOL  bSetDlgRegInfo(  QNM_CUSRES_INFO  *  pCusRes,  QNM_REG_INFO  *  pRegInfo,  HWND  hWnd,  QY_IDCITEM  *  gpTable0,  BOOL  bEdit  );


#endif  /*  }  */

