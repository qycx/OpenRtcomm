#pragma once

// CDlgShareDynBmps dialog




#include	"DlgShareDynBmpsProc.h"
#include	"qisOnvifCommProc_open.h"


//
class CDlgShareDynBmps : public CDialog
{
	DECLARE_DYNAMIC(CDlgShareDynBmps)

public:
	//  CDlgShareDynBmps(CWnd* pParent = NULL);   // standard constructor
	CDlgShareDynBmps(HWND hParent = NULL);   // standard constructor
	virtual ~CDlgShareDynBmps();

	BOOL Create(const RECT& rect);
	BOOL  bQuitDlg(  );		
	int  sizeAllControls(  );
	SHARE_dynBmps	*	getShareDynBmpsBySth(  int  uiObjType  );
	int  refreshShareStatus(  unsigned  int  uiObjType  );
	//
	int  refreshShareCfg_screen(  unsigned  int  uiObjType,  int  index_obj  );
	//
	int  refreshShareCfg_webcam(  unsigned  int  uiObjType,  int  index_obj  );
	//
	//int  sndDynBmpsInfo(  );
	int  toShareScreen(  int  index_pShare_mem  );
	int  toShareScreen_func(  int  index_pShare_mem  );
	//
	int  toShareWebcam(  int objType,  int  index_pShare_mem  );
	int  toShareWebcam_func(  int objType,  int  index_pShare_mem,  void  **  ppCapStuff,   int  iMenuId_v,  BOOL  bUnresizable  );
	//
	int  closeTaskAv(  unsigned  int  uiObjType,  int  index_pShare_mem  );
	int	 toShareGps(  );
	int	 chkShareGps(  );
	int  refreshShareStatus_gps(  );
	//
	int  reloadOnvifList(  );
	//
	int  displayOnvifList(  );
	//
	int  refreshIpDevs(  );

	//
	int  chkAutoOpen(  );
	int  doAutoOpen_webcam(  int  objType,  int  index_pShare_mem,  WEBCAM_info  *  p  );
	int  doAutoOpen_screen(  int  index_pShare_mem,  WEBCAM_info  *  p  );

// Dialog Data
	enum { IDD = IDD_shareDynBmps };

	//
	DLG_shareDynBmps_var								m_var;

	//
	virtual  afx_msg LRESULT OnQyComm( WPARAM, LPARAM );
	virtual  afx_msg LRESULT OnQyPostComm(  WPARAM, LPARAM  );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual void OnOK();
	virtual void OnCancel();

public:
//	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
protected:
public:
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonsharingscreen0();
	afx_msg void OnBnClickedButtonwebcam0();
	afx_msg void OnBnClickedButtonwebcam1();
	afx_msg void OnBnClickedButtonwebcam2();
	afx_msg void OnBnClickedButtongps();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedButtonadd();
	afx_msg void OnBnClickedButtondel();
	afx_msg void OnBnClickedButtonselftest();
	afx_msg void OnBnClickedButtonplaylocalaudio();
	afx_msg void OnBnClickedButtonremotestoragesettings();
	afx_msg void OnBnClickedButtonptz();
	afx_msg void OnBnClickedCheckautopopupandhideOnStartup();
	afx_msg void OnBnClickedButtonhide();
};
