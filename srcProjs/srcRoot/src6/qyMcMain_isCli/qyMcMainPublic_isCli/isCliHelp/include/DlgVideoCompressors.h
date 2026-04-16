#pragma once


// CDlgVideoCompressors dialog

class CDlgVideoCompressors : public CDialog
{
	DECLARE_DYNAMIC(CDlgVideoCompressors)

public:
	CDlgVideoCompressors(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgVideoCompressors();

// Dialog Data
	enum { IDD = IDD_videoCompressors };

	struct							{
		//  MC_VAR_isCli				*	pProcInfo;
		//  POLICY_isClient			*	pPolicy;
		//  POLICY_av				*	pTaskAv_pc;
		unsigned  int				uiCapType;
		unsigned  int				uiSubCapType;		//  2011/09/04
		int							iCapUsage;			//  2014/11/19

		int							level;

		AV_COMPRESSOR_CFG			oldCompressor;
		AV_COMPRESSOR_CFG		*	pCompressor;		//  2009/05/20

		GUID						clsid_category_audio;
		BOOL						bEnumCompressors_audio;

		GUID						clsid_category_video;
		BOOL						bEnumCompressors_video;
		
		BOOL						bInited; 

		AV_COMPRESSOR_CFG			compressor;

	}								m_var;

	//  BOOL  bSetDlgInfo(  POLICY_av  *  pPolicy,  int  level,  unsigned  int  uiCapType,  unsigned int uiSubCapType  );
	BOOL  bSetDlgInfo(  AV_COMPRESSOR_CFG  *  pAvCompressor,  unsigned  int  uiCapType,  unsigned int uiSubCapType,  int  iCapUsage,  int  level  );


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeComboaudiocompressors();
	afx_msg void OnCbnSelchangeComboaudiocompressor();
	afx_msg void OnCbnSelchangeComboaudiooutputtype();
	afx_msg void OnCbnSelchangeCombovideocompressors();
	afx_msg void OnCbnSelchangeCombovideocompressor();
	afx_msg void OnCbnSelchangeCombovideooutputtype();
	afx_msg void OnBnClickedButtoncfgwmv();
	afx_msg void OnCbnSelchangeCombovideoeffect();
	afx_msg void OnCbnSelchangeComboavgbitrate();
};
