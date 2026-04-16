// DlgVideos.h: interface for the CDlgVideos class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGVIDEOS_H__27CADE8D_85C6_48D4_9F73_71DF11F835D5__INCLUDED_)
#define AFX_DLGVIDEOS_H__27CADE8D_85C6_48D4_9F73_71DF11F835D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DlgDesktopsMon.h"

#include	"dlgVideosProc.h"

class CDlgVideos : public CDlgDesktopsMon  
{
public:
	CDlgVideos(  CWnd* pParent = NULL  );
	virtual ~CDlgVideos();

	//
	DLG_videos_var						m_var;

	//  
	BOOL			bSetDlgInfo(  int  iWndContentType,  int  iSubtype,  LPCTSTR  title,  int  iResId_menu,  HWND  hDlgTalk,  int  iTaskId,  QY_MESSENGER_ID  *  pIdInfo_sender,  unsigned  int  uiTranNo_openAvDev,  MIS_CNT  *  pMisCnt,  unsigned  short  usCnt_row,  unsigned  short  usCnt_col,  unsigned  int  uiInitW_pc,  unsigned  int  uiInitH_pic,  unsigned  char  ucbLocalAv,  unsigned  int  nElapseInMs  );

	//
	BOOL			bEnableRemoteAssist(  BOOL  bRemoteAssist  );

	virtual  int	sizeAllControls(  RECT  rcParam  );

	//
	int				processPointerEvent(  int  x,  int  y,  UINT  nFlags,  BOOL  bMouseMove  =  FALSE,  BOOL  bSendForce  =  FALSE  );
	int				sendKeyEvent(  unsigned  int  key, unsigned  char  ucbDown  );
	virtual  int	processKeyEvent(  UINT  nChar, DWORD  keyData  );
	int				resetKeyEvent(  );

	//
	//int				dlgVideos_procVideo(  MIS_MSG_procVideo_qmc  *	pMsg    );


	//
	virtual BOOL OnInitDialog();


	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	virtual  afx_msg LRESULT OnQyComm( WPARAM, LPARAM );
	virtual  afx_msg LRESULT OnQyPostComm( WPARAM, LPARAM );

	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void OnCancel();
public:
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};




#endif // !defined(AFX_DLGVIDEOS_H__27CADE8D_85C6_48D4_9F73_71DF11F835D5__INCLUDED_)
