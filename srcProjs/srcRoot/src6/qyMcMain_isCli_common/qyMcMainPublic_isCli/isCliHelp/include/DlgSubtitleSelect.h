#pragma once

//
#include	"subtitles.h"


// CDlgSubtitleSelect dialog

class CDlgSubtitleSelect : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSubtitleSelect)

public:
	CDlgSubtitleSelect(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSubtitleSelect();

// Dialog Data
	enum { IDD = IDD_subtitle_select };

	struct	{
			struct	{
				
				int		iIDC_CHECK_displayTime;

				int		iIDC_BUTTON_selectFont;
				int		iIDC_BUTTON_fontColor;

				int		iIDC_STATIC_staticMaskColor;
				int		iIDC_EDIT_maskColor_r;
				int		iIDC_EDIT_maskColor_g;
				int		iIDC_EDIT_maskColor_b;

				int		iIDC_STATIC_xyStart;

				int		iIDC_EDIT_xStart;
				int		iIDC_EDIT_yStart;
				
				int		iIDC_CHECK_horizontalCenter;
				int		iIDC_CHECK_bottomUp;

				//  2014/12/21
				int		iIDC_CHECK_outlineFont;
				int		iIDC_BUTTON_edgeColor;
				int		iIDC_STATIC_edgeWidth;
				int		iIDC_EDIT_edgeWidth;
				int		iIDC_CHECK_filled;
				//
				int		iIDOK;
				int		iIDCANCEL;

			}		guiData;
			SUBTITLE_cfg	subtitleCfg;
	}		m_var;

	BOOL	bShowInfo(  );
	BOOL	bShowInfo_selectFont(  );
	BOOL	bShowInfo_fontColor(  );
	BOOL	bShowInfo_edgeColor(  );



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonselectfont();
	afx_msg void OnBnClickedButtonfontcolor();
	afx_msg void OnBnClickedButtonedgecolor();
};
