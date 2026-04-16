
#pragma once





//
#define		CONST_dcgType_null					0
#define		CONST_dcgType_createTmpGrp			1
#define		CONST_dcgType_sendFile				2
#define		CONST_dcgType_modifyTmpGrp			3




// CDlgCfgGrp dialog
class CDlgCfgGrp : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCfgGrp)

public:
	CDlgCfgGrp(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgCfgGrp();

// Dialog Data
	enum { IDD = IDD_cfgGrp };

	//
	struct					{
		//
		int					iType;

		//
		IM_GRP_EX		*	pImGrpEx_input;			//  

		//
		TMP_usrs  			tmpUsrs;

		//
		TMP_usrs			tmpGrp;

		//
		TCHAR				tSelUsrs[256];

		//
		QY_MESSENGER_ID		idInfo_tmpGrp;

	}						m_var;

	//
	int  fill_usrs(  );
	//
	BOOL  isGrpMem(  QY_MESSENGER_ID  * pIdInfo  );

	//
	int  add_mem(  QY_MESSENGER_ID  *  pIdInfo  );
	int  del_mem(  QY_MESSENGER_ID  *  pIdInfo  );

	//
	int  free_usrs(  );

	//
	int  display(  TCHAR  *  tSelUsrs  );

	//
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnEnChangeEditselusr();
	afx_msg void OnBnClickedButtonadd();
	afx_msg void OnBnClickedButtondel();
	afx_msg  LRESULT  OnQyComm( WPARAM, LPARAM );

	afx_msg void OnEnChangeEditgrpname();
};
