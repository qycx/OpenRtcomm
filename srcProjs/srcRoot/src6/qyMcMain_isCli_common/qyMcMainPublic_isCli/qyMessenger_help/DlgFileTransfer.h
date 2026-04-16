#pragma once

//
#include	"ctxQmc.h"

//
#include	"isCliHelpPublic.h"



//
void  free_DFT_sendTasks(  DFT_sendTasks  *  pTasks  );


//
//
typedef  struct								{

		//
		int									iType;

		//
		struct								{
			OfflineRes_var					offlineRes;
		}									recv;
		//
		struct								{
			DFT_sendTasks					tasks;
			
			//
			DFT_sendTask					curTask;

			//
			OfflineRes_var					offlineRes;
		}									send;
		//
		struct								{
			DFT_sendTasks					tasks;
		}									sent;
	
}											DFT_var;


//
#define		CONST_dftType_null		0
#define		CONST_dftType_recv		1
#define		CONST_dftType_sent		2
#define		CONST_dftType_send		3



// CDlgFileTransfer dialog

class CDlgFileTransfer : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFileTransfer)

public:
	CDlgFileTransfer(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgFileTransfer();

// Dialog Data
	enum { IDD = IDD_fileTransfer };

	//
	DFT_var		m_var;

	//
	virtual  int	sizeAllControls(  );
	//
	int  closeTool_recv(  );
	int  hideTool_send(  );
	//
	int  displayTasks_func(  DFT_sendTasks  *  pTasks,  BOOL  bDecrement  );
	int  displayTasks(  );


	//
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedRadiorecv();
	afx_msg void OnBnClickedRadiosent();
	afx_msg void OnBnClickedRadiosend();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
