
#ifndef  __dlgDesktopsMonProc_h__
#define  __dlgDesktopsMonProc_h__	//  {



typedef  struct  __paramLayout_dlgDesktopsMon_t		{
				 int								iEdge_l;					//	=	10;
				 int								iEdge_t;					//	=	10;
				 int								iEdge_r;					//	=	10;
				 int								iEdge_b;					//	=	10;
				 //
				 int								iX_spacing;					//	=	10;			//  两个控件间的横向间隔
				 int								iY_spacing;					//	=	10;
				 //
				 int								iW_btn;						//	=	10;
				 int								iH_btn;						//	=	10;
				 //
				 int								iH_static;					//	=	30;			//  和pic相关的标签的高度，固定
				 //
				 int								iY_spacing_pic_static;		//	=	2;			//  两个控件间的纵向间隔
				 int								iY_spacing_static_pic;		//	=	4;			
				 //
				 int								iY_spacing_static_btn;		//	=	10;

}		 PARAM_layout_dlgDesktopsMon;


typedef  struct									{
			//  CWnd					*		m_pParent;
			HWND							m_hParent;
			int								m_nID;
			//
			int								iWndContentType;			//  2009/09/07
			int								iSubtype;					//  2012/04/02
			//
			int								iResId_menu;
			
			//
			PARAM_layout_dlgDesktopsMon		layoutParam;
			
			//  2017/02/13			
			unsigned  char					param_bValid_pos;
			unsigned  char					param_bFullScreen;
			
			//
			unsigned  short					usCnt_row;					//  水平有几个
			unsigned  short					usCnt_col;					//  纵向有几个窗口
			//
			unsigned  int					uiInitW_pic;
			unsigned  int					uiInitH_pic;

			//  2016/01/04
			//
			BOOL							bInfoSet;
			BOOL							bCreated;					//  这个标志位用来表明是否Create(  )成功了。成功了，则将资源的释放留给了dlg自己(在PostNcDestroy(  )中delete)
			BOOL							bDlgInited;					//  

			QY_DMITEM				*		pIdcTable;
			
			//
			RECT							m_rect;
			
			// 2008/11/06. 为提供滚动条
			BOOL							bScrollBarEnabled;
			BOOL							notOnOffScrollBar;			//  2009/10/08

			int								m_nCurWidth;
			int								m_nScrollPos_h;
			int								m_nCurHeight;
			int								m_nScrollPos_v;

			//  2010/08/26
			unsigned  char 					ucbHideStatic_idc;
			unsigned  char 					ucbHideStatic_idcHint;


			//  
			CAP_RECT						mems_org[CONST_maxMonedDesktops];
			CAP_RECT						mems[CONST_maxMonedDesktops];				//  2012/05/04

			//  2009/10/06
			WINDOWPLACEMENT					m_oldWndPlacement;
			struct							{
				HMENU						hOldMenu;								//  2012/07/07
				long						lOldStyle;								//  2012/07/07
			}								m_fullScreenInfo;
			// 
			BOOL							m_bFullScreen;
			RECT							m_fullScreenRect;
			PARAM_layout_dlgDesktopsMon		m_oldLayoutParam;

			//  2010/12/25
			unsigned  char					ucbBkBlack;

			//
			PF_commonHandler				pf_OnMove;	//  HWND  hWnd,  int  x,  int  y
			PF_commonHandler				pf_OnSize;	//  HWND  hWnd,  int  cx,  int  cy

	}		DLG_desktopsMon_var;


#endif  //  }

