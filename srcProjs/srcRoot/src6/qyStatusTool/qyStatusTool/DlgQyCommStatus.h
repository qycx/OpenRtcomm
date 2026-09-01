#if !defined(AFX_DLGQYCOMMSTATUS_H__A5D46191_B0B2_471A_88E9_D5678DC6914A__INCLUDED_)
#define AFX_DLGQYCOMMSTATUS_H__A5D46191_B0B2_471A_88E9_D5678DC6914A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQyCommStatus.h : header file
//

#include <vector>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CDlgQyCommStatus dialog

#if  0	//  2014/06/24
typedef  struct  __infoElem_t					{
				 SYSTEMTIME						when;								//  2007/06/01, 将上面的时间改成下面的原因，是需要更精确的毫秒值，以确定执行步骤，方便 qyStatusTool进行排序
				 unsigned  int					uiStep;								//  2008/04/28, 第几步。这用来在时间一样时，区分前后顺序

				 WCHAR							wBuf[160];
}		 INFO_ELEM;
#endif
typedef  struct  __infoElem_t					{
				 SYSTEMTIME						when;								//  2007/06/01, 将上面的时间改成下面的原因，是需要更精确的毫秒值，以确定执行步骤，方便 qyStatusTool进行排序
				 unsigned  int					uiStep;								//  2008/04/28, 第几步。这用来在时间一样时，区分前后顺序

				 //
				 #define		MAX_cnt_info_wBuf				256  +  128	//  256

				 //
				 WCHAR							wBuf[MAX_cnt_info_wBuf];
}		 INFO_ELEM;

//
class CSampleData
{
public:
	CSampleData()
	{
		//m_name = RandomText::GetName();
		//m_slogan = RandomText::GetSlogan();
		static int i=0;
		i++;
		TCHAR tBuf[128];
		_sntprintf(tBuf, mycountof(tBuf),_T("%d times"),i);
		
		m_seqNo=tBuf;
		m_str=tBuf;

		m_image = 0;//rand()%IMAGECOUNT;
	}

	CString m_seqNo;
	CString m_str;
	int m_image;
};




//
class CDlgQyCommStatus : public CDialog
{
// Construction
public:
	CDlgQyCommStatus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgQyCommStatus)
	enum { IDD = IDD_qyCommStatus };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA



	struct								{
		int								iType;
		BOOL							bProcCurQueryOnly;
		
		union							{
			QY_IMEXPORTINFO				imExportInfo;
			QY_CLEARUPINFO				clearupInfo;
			struct						{
				int						iShowFlgs[1];		//  qyShowInfo1的开关标志
				//
				char					serviceName_netMc[128];
				BOOL					bServiceRunning_netMc;
				char					serviceName_is[128];
				BOOL					bServiceRunning_is;
				//
				QY_STATUS_STRUCT		statusStruct;
			}							showInfo;
		}								u;
		
		//
		BOOL							bAutoClearup;
#if  0
		unsigned  long					ulClientIp0;
		//unsigned  long					ulClientIp1;
		TCHAR							filter0Buf[255  +  1];
		TCHAR							filter1Buf[255  +  1];
		TCHAR							contentFilter2Buf[255  +  1];
		TCHAR							contentFilter3Buf[255  +  1];
#endif
		//
		MY_filters						filters;
		//
		int								iCurSel;

		//
		int								iEdge_list_x;
		int								iTop_list;
		//
		int								iSpacing_list_autoClearup;
		int								iX_autoClearup;
		int								iEdge_autoClearup_b;	
		//
		int								iW_toolStatus;
		int								iH_toolStatus;

		//
		GENERIC_Q						infoQ;
		BOOL							bInfoQInited;
		void					**		ppInfos_sortedByTime;

		//
		DWORD							dwLastTickCnt_postComm;

	}									m_var;

	//
	//This is the database we using
	//vector<CSampleData> m_database;


	//
	CListCtrl	* m_list;
	CImageList m_imagelist;
	CImageList m_imagelistLarge;

	//
	int test_add();
	void clear();
	
	//
	int processInputQ();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQyCommStatus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQyCommStatus)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeCOMBOselect();
	//}}AFX_MSG
	afx_msg LRESULT OnQyComm(  WPARAM  wParam,  LPARAM  lParam  );
	afx_msg LRESULT OnQyPostComm(  WPARAM  wParam,  LPARAM  lParam  );
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadioqwmcomm();
	afx_msg void OnBnClickedRadioqnmchking();
	afx_msg void OnBnClickedRadioscanningip();
	afx_msg void OnBnClickedCheckautoclearup();
protected:
	virtual void PostNcDestroy();
public:
//	afx_msg void OnMenuTask();
	afx_msg void OnMenuTasks();
	afx_msg void OnMenuPlayers();
	afx_msg void OnMenuTalks();
	afx_msg void OnQs();
	afx_msg void OnSys();
	afx_msg void OnOthers();
	afx_msg void OnLvnGetdispinfoListdisplay(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnOdfinditemListdisplay(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnOdcachehintListdisplay(NMHDR *pNMHDR, LRESULT *pResult);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQYCOMMSTATUS_H__A5D46191_B0B2_471A_88E9_D5678DC6914A__INCLUDED_)
