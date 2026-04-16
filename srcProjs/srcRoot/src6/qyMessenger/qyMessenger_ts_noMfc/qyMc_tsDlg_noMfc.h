
#ifndef  __qyMc_tsDlg_noMfc_h__
#define  __qyMc_tsDlg_noMfc_h__		//  {


#include	"qywnd.h"
#include	"WallTalkers.h"
#include	"resource.h"


class CqyMc_tsDlg : public CQyWnd
{
// Construction
public:
	CqyMc_tsDlg();	// standard constructor
	virtual  ~CqyMc_tsDlg(  );

// Dialog Data
	enum { IDD = IDD_ts_main };

// Dialog Data
	
	struct						{
		QY_MC* pQyMc;
		QY_MC_mainWndVar		common;
		ZONE_objs_info			wall;


	}							var;
	//  CBrush						m_brush_fullScreen_dlg;


	//
	void  *  getGuiData(  )  {
				return  &var.common.guiData;
	}
	void  *  getVar(  )  {
				return  &var;
	}

	//
	BOOL	Create(const RECT& rect);
	BOOL	bQuitDlg(  );
	
	//
	void			endFullScreen(  );

	//
	virtual BOOL OnInitDialog();

	//	
	virtual void OnCancel();
	void OnClose();
	void OnDestroy();	
	void OnSize(UINT nType, int cx, int cy);	
	void Onfullscreen();
	void OnMoving(UINT fwSide, LPRECT pRect);
	void OnMove(int x, int y);
	//
	void OnTimer(UINT_PTR nIDEvent);		
	//
	LRESULT  OnQyPostComm( WPARAM, LPARAM );
	LRESULT  OnQyTrayNotify( WPARAM, LPARAM );
	LRESULT  OnQyGraphNotify_mediaFile( WPARAM, LPARAM );
	LRESULT  OnQyGraphNotify_mediaDevice( WPARAM, LPARAM );
	void OnIsCmd(  UINT nID  );
	//  void OnUpdateIsCmd(CCmdUI *pCmdUI);


	//
	virtual void PostNcDestroy();


	void OnBnClickedButtoncontact();
	void OnBnClickedButtongroup();
	void OnBnClickedButtoncustomerserviceofficer0();
	void OnBnClickedButtonbar();

};



#endif  //  }


