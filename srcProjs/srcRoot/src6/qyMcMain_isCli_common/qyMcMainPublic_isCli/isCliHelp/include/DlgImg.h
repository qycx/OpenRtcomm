#pragma once

#include	"dlgDesktopsMon.h"
#include	"imgProcessPublic.h"


typedef  struct  __dlgImgVar_t						{
				 TCHAR								title[128];

				 MIS_MSG_procVideo_qmc				msg;

				 //
				 KEYING_img_datas					datas;

				 //
				 KEYING_ctx							keyingCtx;
				 BOOL								bKeyed;

				 //
				 HWND								hTool;
				 
				 struct								{
					 BOOL							bInited;							//  2011/03/25
				 }									guiData;

				 //
				 int								idc;		
				 HDC								hDc;
				 CAP_IMAGES							images;

				 ZONE_PARAM							zoneParam;

				 //  2014/04/06
				 unsigned  char						ucbAutoClip;

}		 DLG_img_var;


 int  dlgImg_pickColor(  HWND  hDlgImg  );
 int  dlgImg_xyColor(  HWND  hDlgImg,  unsigned int img_x,  unsigned int img_y  );
 int  dlgImg_testKeying(  HWND  hDlgImg  );

// CDlgImg dialog

class CDlgImg : public CDlgDesktopsMon
{
	DECLARE_DYNAMIC(CDlgImg)

public:
	CDlgImg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgImg();

// Dialog Data

	DLG_img_var		m_var;

	//
	BOOL			bSetDlgInfo(  int  iWndContentType,  int  iSubType,  LPCTSTR  title,  int  iResId_menu,  MIS_CNT  *  pMisCnt,  unsigned  short  usCnt_row,  unsigned  short  usCnt_col,  unsigned  int  uiInitW_pc,  unsigned  int  uiInitH_pic  );
	
	virtual  int	sizeAllControls(  RECT  rcParam  );
	
	int  mallocDatas(  );
	void  freeDatas(  );


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();


	virtual  afx_msg LRESULT OnQyComm( WPARAM, LPARAM );

	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
