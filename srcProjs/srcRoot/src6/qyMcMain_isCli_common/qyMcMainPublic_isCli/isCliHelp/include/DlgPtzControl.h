#pragma once
#include "afxcmn.h"
#include  "BitmapBtn.h"
#include  "myButton.h"
#include "afxwin.h"

//
#include	"qyComPortEx.h"
#include	"isCliHelpPublic.h"


//
typedef  struct  __dlgGuiData_ptzControl_t			 {
				 BOOL								 bInited;
				 int								 iWndContentType;
				 //
				 int								 iw_org,  ih_org;
				 //  header
				 int								 iIDC_BUTTON_ptzSettings;
				 RECT								 rcIDC_BUTTON_ptzSettings;
				 int								 iIDC_STATIC_hint;
				 RECT								 rcIDC_STATIC_hint;
				 int								 iIDC_STATIC_speed;
				 RECT								 rcIDC_STATIC_speed;
				 int								 iIDC_SLIDER_speed;
				 RECT								 rcIDC_SLIDER_speed;
				 //
				 //  body
				 int				 				 iIDC_BUTTON_TOP_LEFT;
				 RECT				 				 rcIDC_BUTTON_TOP_LEFT;
				 int				 				 iIDC_BUTTON_UP;
				 RECT				 				 rcIDC_BUTTON_UP;
				 int				 				 iIDC_BUTTON_TOP_RIGHT;
				 RECT				 				 rcIDC_BUTTON_TOP_RIGHT;

				 int				 				 iIDC_BUTTON_LEFT;
				 RECT				 				 rcIDC_BUTTON_LEFT;
				 int				 				 iIDC_BUTTON_AUTO_SCAN;
				 RECT				 				 rcIDC_BUTTON_AUTO_SCAN;
				 int				 				 iIDC_BUTTON_RIGHT;
				 RECT				 				 rcIDC_BUTTON_RIGHT;

				 int				 				 iIDC_BUTTON_BOTTOM_LEFT;
				 RECT				 				 rcIDC_BUTTON_BOTTOM_LEFT;
				 int				 				 iIDC_BUTTON_DOWN;
				 RECT				 				 rcIDC_BUTTON_DOWN;
				 int				 				 iIDC_BUTTON_BOTTOM_RIGHT;
				 RECT				 				 rcIDC_BUTTON_BOTTOM_RIGHT;

				 int								 iIDC_BUTTON_noop;				//  2013/04/07
				 RECT								 rcIDC_BUTTON_noop;

				 int				 				 iIDC_BUTTON_FOCUS_OUT;
				 RECT				 				 rcIDC_BUTTON_FOCUS_OUT;
				 int				 				 iIDC_BUTTON_IRIS_OUT;
				 RECT				 				 rcIDC_BUTTON_IRIS_OUT;
				 int				 				 iIDC_BUTTON_ZOOM_OUT;
				 RECT				 				 rcIDC_BUTTON_ZOOM_OUT;

				 int				 				 iIDC_STATIC_focus;
				 RECT				 				 rcIDC_STATIC_focus;
				 int				 				 iIDC_STATIC_iris;
				 RECT				 				 rcIDC_STATIC_iris;
				 int				 				 iIDC_STATIC_zoom;
				 RECT				 				 rcIDC_STATIC_zoom;


				 int				 				 iIDC_BUTTON_FOCUS_IN;
				 RECT				 				 rcIDC_BUTTON_FOCUS_IN;
				 int				 				 iIDC_BUTTON_IRIS_IN;
				 RECT				 				 rcIDC_BUTTON_IRIS_IN;
				 int				 				 iIDC_BUTTON_ZOOM_IN;
				 RECT				 				 rcIDC_BUTTON_ZOOM_IN;

				 int								 iIDCANCEL;
				 RECT								 rcIDCANCEL;
				 //  tailer
				 int								 iIDC_BUTTON_RAIN_BRUSH;
				 RECT								 rcIDC_BUTTON_RAIN_BRUSH;
				 int								 iIDC_BUTTON_SEARCH_LIGHT;
				 RECT							     rcIDC_BUTTON_SEARCH_LIGHT;
				 int								 iIDC_STATIC_preset;
				 RECT								 rcIDC_STATIC_preset;
				 int								 iIDC_EDIT_PRE;
				 RECT								 rcIDC_EDIT_PRE;
				 int								 iIDC_BUTTON_PRE_GO;
				 RECT								 rcIDC_BUTTON_PRE_GO;
				 int								 iIDC_BUTTON_PRE_SET;
				 RECT								 rcIDC_BUTTON_PRE_SET;
				 int								 iIDC_BUTTON_PRE_CLEAR;
				 RECT								 rcIDC_BUTTON_PRE_CLEAR;


}		 DLG_guiData_ptzControl;

// CDlgPtzControl dialog

class CDlgPtzControl : public CDialog
{
	DECLARE_DYNAMIC(CDlgPtzControl)

public:
	CDlgPtzControl(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPtzControl();

// Dialog Data
	enum { IDD = IDD_ptzControl };


	struct  {

			CWnd							*		m_pParent;
			int										m_nID;
			//  BOOL								bInfoSet;
			BOOL									bCreated;							//  Create(  ) PostNcDestroy(  ) delete)


			//
			BOOL									bRemote;
			//
			struct									{					
				//
				BOOL								bManual;							//  2014/10/14. 
				//
				RES_obj_simple								resObj_camera;
				//
				PARAM_viewLocalPtzControl			param;
				//
				QIS_ptz_wnd					*		pPtzWnd;							//  2016/07/20

			}										local;
			
			//
			struct									{
				HWND								hDlgTalk;
				
				//
				QIS_dynBmp_info						remoteCamera;

			}										remote;



			//
			void							*		pStageLens;
			//
			CComPortEx						*		pComPort;							//  2015/09/20

			//
			int										iPtzType;							//  2015/09/18
			//
			int										m_nAddr;
			int										m_pelcoType;
			TCHAR									tHint[255  +  1];
			//
			int										m_nSpeed;
			int										m_nPre;

			//
			BOOL									m_bnDown_autoScan;
			BOOL									m_bnDown_rainBrush;
			BOOL									m_bnDown_searchLight;

			DLG_guiData_ptzControl					guiData;

			//  2014/10/14
			UINT_PTR								wTimerID;
							
			DWORD									dwTickCnt_lastPtzCmdRecvd;			//  2010/08/29
			
			//


			//  2013/02/17			
			//  DLG_syncFlgs							syncFlgs;


	}										m_var;

private:
	CZBitmap  m_btnUp,  m_btnDown,  m_btnLeft,  m_btnRight,  m_btnTopLeft,  m_btnTopRight,  m_btnBottomLeft,  m_btnBottomRight;
	CZBitmap  m_btnNoop;	//  2013/04/07
	CZBitmap  m_btnIrisIn,  m_btnIrisOut,  m_btnFocusIn,  m_btnFocusOut,  m_btnZoomIn,  m_btnZoomOut;
	//  CCheckButton  m_cbtnAutoScan,  m_cbtnRainBrush,  m_cbtnSearchLight;
	CMyButton  m_buStatus_autoScan,  m_buStatus_rainBrush,  m_buStatus_searchLight;

	BYTE  m_byStatus_autoScan,  m_byStatus_rainBrush,  m_byStatus_searchLight;

	//
public:
	CSliderCtrl m_slider_speed;

	//
	CEdit m_edit_nPrePoint;

public:
	//
	//
	BOOL Create(const RECT& rect);
	BOOL  bQuitDlg(  );		

	void  InitBtn(  );
	int		refreshStatus(  );
	int  sizeAllControls(  );


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(  WPARAM  wParam,  LPARAM  lParam  );

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
protected:
	virtual void PostNcDestroy();
public:
	afx_msg void OnBnClickedButtonptzsettings();
protected:
	virtual void OnCancel();
public:
	afx_msg void OnNMReleasedcaptureSliderspeed(NMHDR *pNMHDR, LRESULT *pResult);

protected:
	void  OnChangeStatus(  UINT  nID  );
public:
	afx_msg void OnEnChangeEditPre();
	afx_msg void OnBnClickedButtonPreGo();
	afx_msg void OnBnClickedButtonPreSet();
	afx_msg void OnBnClickedButtonPreClear();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
