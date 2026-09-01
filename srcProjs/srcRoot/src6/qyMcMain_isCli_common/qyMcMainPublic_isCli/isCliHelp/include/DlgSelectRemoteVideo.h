#pragma once

#include	"dlgSelect_isCli_public.h"


// CDlgSelectRemoteVideo dialog

class CDlgSelectRemoteVideo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSelectRemoteVideo)

public:
	CDlgSelectRemoteVideo(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSelectRemoteVideo();

// Dialog Data
	enum { IDD = IDD_select_remoteVideo };

	struct								{
		int								iSelectType;
		int								iObjType;
		QY_OBJ_DB					*	pObjDb;
		TCHAR							hint[255  +  1];

		//
		TCHAR							misServName[CONST_maxMisServNameLen  +  1];
		union							{
			struct						{
				QY_MESSENGER_ID			idInfo_grp;
			}							selectImGrpMem;
		}								inputU;

		//
		DlgSelect_isCli_o_U				u;
		
	}									m_var;
	
	BOOL			bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  int  iSelectType,  int  iObjType,  LPCTSTR  hint,  void  *  p0,  void  *  p1  );  

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBnClickedOk();
};
