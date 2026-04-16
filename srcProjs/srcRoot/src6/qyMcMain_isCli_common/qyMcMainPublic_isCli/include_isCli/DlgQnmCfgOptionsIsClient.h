#if !defined(AFX_DLGQNMCFGOPTIONSISCLIENT_H__B04A1FD3_6E6E_43F8_8229_55C21307F127__INCLUDED_)
#define AFX_DLGQNMCFGOPTIONSISCLIENT_H__B04A1FD3_6E6E_43F8_8229_55C21307F127__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmCfgOptionsIsClient.h : header file
//

extern  "C"  int getLogonServerCfg(  QY_MC  *  pQyMc,  QNM_CNT_CFG  *  pCntCfg,  int  index,  unsigned short  *  pSeqNo,  TCHAR  *  pCntName,  unsigned int cntNameSize   );

typedef  struct  __dlgQnmCfgOptionsIsClientVar_t		{
				 int									qyDlgType;
				 //
				 QNM_CNT_CFG							cntCfg[CONST_maxOfVideoConferencingServers];
				 TCHAR									cntName[CONST_maxOfVideoConferencingServers][255+1];
				 unsigned short							seqNo[CONST_maxOfVideoConferencingServers];
				 unsigned short							usItemCount;
				 int									iItemSelected;
				 //
				 QY_COLUMNINFO						*	pColumn;
				 unsigned short							usColumnCount;
				 //


				 //
				 DLG_guiData_qnmCfgOptionsIsClient		guiData;

				 unsigned char							ucbUseDb;			//  2013/02/21

}		  DLG_qnmCfgOptionsIsClient_var;


/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgOptionsIsClient dialog



#include	"qyWnd.h"

class CDlgQnmCfgOptionsIsClient : public CQyWnd
{
// Construction
public:
	CDlgQnmCfgOptionsIsClient(  HWND  hParent  =  NULL  );   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgQnmCfgOptionsIsClient)
#ifndef  __WINCE__
	//  enum { IDD = IDD_qnmCfgOptions_isClient };
#else
	//  enum { IDD = IDD_qnmCfgOptions_isClient_ce };
#endif
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	DLG_qnmCfgOptionsIsClient_var	m_var;

#ifdef  __WINCE__
		#ifndef  __TEST__
				 CCeMenuBar						m_menuBar;
		#endif
#endif

	//  int		showServerCfg(  int  iSeqNo  );
	//  int		listVideoConferencingServer(  );
	//  BOOL	bModifyItem(  );

public:
	
	virtual  void  *  getGuiData(  )  {  return  &m_var.guiData;  }
	virtual  void  *  getVar(  )  {  return  &m_var;  }

public:

	//  virtual BOOL OnInitDialog();
	void OnLvnItemchangedListvcserver(NMHDR *pNMHDR, LRESULT *pResult);
	void OnNMDblclkListvcserver(NMHDR *pNMHDR, LRESULT *pResult);
	void OnBnClickedAdd();
	void OnBnClickedModify();
	void OnBnClickedDel();
#if  0
	CListCtrl m_vcServerList;
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);

#endif

};



#endif // !defined(AFX_DLGQNMCFGOPTIONSISCLIENT_H__B04A1FD3_6E6E_43F8_8229_55C21307F127__INCLUDED_)
