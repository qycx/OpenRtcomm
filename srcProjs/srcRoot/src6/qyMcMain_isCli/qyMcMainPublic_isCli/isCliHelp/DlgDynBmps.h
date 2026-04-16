
#pragma once


#include	"dlgDesktopsMon.h"

#include	"dlgDynBmpsProc.h"

// CDlgDynBmps dialog


using namespace std;
#include	<vector>
#include	<algorithm>


//
class CDlgDynBmps : public CDlgDesktopsMon
{
	//  DECLARE_DYNAMIC(CDlgDynBmps)

public:
	CDlgDynBmps(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgDynBmps();

	//
	int									iIndex_objVarInfo;


	//
	DLG_dynBmps_var  *  get_pm_var();

	//
	vector<VW_ruleU> csVector_rules;

	//  2019/01/23
	CBrush				m_brush_desc_normal;
	CBrush				m_brush_desc_fullScreen;


	//  
	BOOL			bSetDlgInfo(  int  iWndContentType,  int  iSubType,  LPCTSTR  title,  int  iResId_menu,  MIS_CNT  *  pMisCnt,  unsigned  short  usCnt_row,  unsigned  short  usCnt_col,  unsigned  int  uiInitW_pc,  unsigned  int  uiInitH_pic  );

	//
	int				toChkTask(  QY_WMBUF_COMM  *  pComm  );
	int				processKeyEvent(  UINT  nChar, DWORD  keyData  );

	int				refreshWallBySp(  int  spIndex  );
	int				refreshWallByRules(  int  spIndex  );
	int				showRules(  int  spIndex  );
	//
	int				findZoneParam(  BOOL  bTalkers,  ZONE_PARAM  *  pParam  );

	//
	int				getZoneInfo(  POINT  point_dlg,  ZONE_PARAM  *  pParam,  VW_ruleU  *  pRule  );

	int				sizeZone(  SUB_V_WALL  *  pSubWall,  myZONE  *  pZone  );
	virtual  int	sizeAllControls(  RECT  rcParam  );

	//
	int				sizeSubWallBg(  int  spIndex  );
 	int				drawSubWall(  int  spIndex,  HWND  hWnd_dst,  HDC  hDc_dst  );	//  2013/03/02

	//
	int				storeSpRules(  );
	int				restoreSpRules(  );

	//
	int				openFile(  LPCTSTR  fileName  );
	int				doAutoLayout_talker(  );

	//
	int				tryToSetRule(  POINT  screenPoint,  LPCTSTR  dropStr  );


	//
	virtual  BOOL	bPrepareToQuit(  );
	virtual  BOOL  	bQuitDlg(  );

	virtual BOOL	OnInitDialog();
	virtual BOOL	PreTranslateMessage(MSG* pMsg);
	
	//
	//
	CDropTarget							m_drop;			//  2018/07/03
	virtual LRESULT  OnDropEx(WPARAM pDropInfoClass, LPARAM lParm);
	virtual LRESULT OnDrop(WPARAM pDropInfoClass, LPARAM lParm);
	virtual LRESULT OnDragOver(WPARAM pDropInfoClass,LPARAM lParm);

protected:

	DECLARE_MESSAGE_MAP()
public:
	virtual  afx_msg LRESULT OnQyComm( WPARAM, LPARAM );
	virtual  afx_msg LRESULT OnQyPostComm( WPARAM, LPARAM );
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void Onviewtoolbox();
	afx_msg void OnUpdateviewtoolbox(CCmdUI *pCmdUI);
	afx_msg void Onstopediting();
	afx_msg void OnUpdatestopediting(CCmdUI *pCmdUI);
	afx_msg void Onstarttoedit();
	afx_msg void OnUpdatestarttoedit(CCmdUI *pCmdUI);
	afx_msg void Onstopshowingrules();
	afx_msg void OnUpdatestopshowingrules(CCmdUI *pCmdUI);
	afx_msg void Onstarttoshowrules();
	afx_msg void OnUpdatestarttoshowrules(CCmdUI *pCmdUI);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void Onopen();
	afx_msg void OnUpdateopen(CCmdUI *pCmdUI);
	afx_msg void Onsave();
	afx_msg void OnUpdatesave(CCmdUI *pCmdUI);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnIsCmd(  UINT nID  );
	afx_msg void OnUpdateIsCmd(CCmdUI *pCmdUI);

	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
