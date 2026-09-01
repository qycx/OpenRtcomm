
#pragma once

//
#include	"qmcStruct_defs.h"


//
typedef  struct  __tmp_cntCfg_t {
	TCHAR	cntName[64];
	char	cntAddr[64];
	int	port;
}		 TMP_cntCfg;

typedef  struct  __tmp_cntCfgs_t {
	TMP_cntCfg		mems[CONST_maxOfVideoConferencingServers];
}		 TMP_cntCfgs;


//


typedef  struct  __tmp_cnt_display_t {
	int	index;
	TCHAR displayName[64];
}  TMP_cnt_display;

typedef  struct  __tmp_cnt_displays_t {
	TMP_cnt_display	mems[CONST_maxOfVideoConferencingServers];
}  TMP_cnt_displays;


//
struct __smLoginVar_t {
	TMP_cnt_displays  m_tmpCntDisplays;

	HANDLE		m_hThread_ca;

};


//
struct  __smUsrLoginVar_t{

	//
	HANDLE		m_hThread_ca;

};



//
struct	 __dlgMcClientLogonVar_t {
		 int							qyDlgType;
	
		 //
		 QNM_CNT_CFG					cntCfg[CONST_maxOfVideoConferencingServers];
		 TCHAR							cntName[CONST_maxOfVideoConferencingServers][255 + 1];
		 unsigned short					seqNo[CONST_maxOfVideoConferencingServers];
		 unsigned short					usItemCount;
		 int							iSeqNoSelected;
		 //
		 HANDLE							hMutex_singleInstance;

		 //
		 unsigned  int					uiTimerId;		//  2011/03/23

		 //
		 int							nTries_triggerIDOK;
		 BOOL							bLogonFailed;

		 TCHAR							respHint[128];	//  2011/08/15

		 //
		 DLG_guiData_mcClientLogon		guiData;

		 //
		 TMP_cntCfgs					cntCfgs;

		 //
		 bool							ucbSavePasswd;
		 bool							ucbAutoLogon;

		 //
		 bool							bDone_AutoLogon;

		 //
		 SmLoginVar						m_smLoginVar;

		 //
		 //
		 bool							m_bStartToUsrLogin;
		 DWORD							dwTickCnt_startToUsrLogin;
		 //
		 SmUsrLoginVar					m_smUsrLoginVar;
		 
		 //
		 bool							bDone_devLogin;

		 //
};










//
#if  0

#include "afxwin.h"

// CDlgMcClientLogon dialog
class CDlgMcClientLogon : public CDialog
{
	DECLARE_DYNAMIC(CDlgMcClientLogon)

public:
	CDlgMcClientLogon(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgMcClientLogon();

// Dialog Data
	enum { IDD = IDD_mcClient_logon };

	struct	{
			int						qyDlgType;
			//
			QNM_CNT_CFG				cntCfg[CONST_maxOfVideoConferencingServers];
			TCHAR					cntName[CONST_maxOfVideoConferencingServers][255+1];
			unsigned short			seqNo[CONST_maxOfVideoConferencingServers];
			unsigned short			usItemCount;
			int						iSeqNoSelected;
			//
			int						nTries;
	}		m_var;
#ifdef  __WINCE__
	#ifndef  __TEST__
		CCeMenuBar					m_menuBar;
	#endif
#endif

	int  bNotSeleceted(  );
	int	 resetComboBox(  );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonoption();
	CComboBox m_logonServer;
	afx_msg void OnCbnSelchangeCombologonserver();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
};


#else

#include	"qyWnd.h"

class CDlgMcClientLogon : public CQyWnd
{

public:
	CDlgMcClientLogon(  );   // standard constructor
	virtual ~CDlgMcClientLogon();

// Dialog Data
	//  enum { IDD = IDD_mcClient_logon };

	DLG_mcClientLogon_var			m_var;

	//
#ifdef  __WINCE__
	#ifndef  __TEST__
		CCeMenuBar					m_menuBar;
	#endif
#endif

	virtual  void  *  getGuiData(  )  {  return  &m_var.guiData;  }
	virtual  void  *  getVar(  )  {  return  &m_var;	}

	//  int  bNotSeleceted(  );
	//  int	 resetComboBox(  );

public:
	//  virtual BOOL OnInitDialog();
	//  void OnBnClickedOk();
	//  void OnDestroy();
	//  void OnCbnSelchangeCombologonserver();
	//  void OnBnClickedButtonoption();

};


#endif

 

