#pragma once

//
#include	"qmcShareDynBmp.h"

// CDlgRtspUrl dialog

class CDlgRtspUrl : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRtspUrl)

public:
	CDlgRtspUrl(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgRtspUrl();

	struct						{
		//  2016/06/16
		BOOL					bEditRtspUrlForConf;
		//
		BOOL					bNew;
		//
		Onvif_rule				rule;

		//
		unsigned  int			uiCapType;
		unsigned  int			uiSubCapType;
	}							m_var;

// Dialog Data
	enum { IDD = IDD_rtspUrl };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();

	BOOL		bSetDlgInfo(  BOOL  bNew,  unsigned  int  usIndex_obj,  int  iOnvifRuleType,  LPCTSTR  cusName,  char  *  url,  char  *  usrName,  char  *  passwd,  char  *  defToken  );
	BOOL		bSetDlgInfo(  BOOL  bEditRtspUrlForConf  );
	//
	afx_msg void OnCbnSelchangeCombotype();
};
