

#ifndef  __dlgAvResCommon_h__
#define  __dlgAvResCommon_h__	//  {

//
#include	"dropTree.h"

//
typedef  	struct				{
		
		//
		HWND			m_hParent;
		int				m_nID;

		//
		int								iWndContentType;			//  2009/09/07
		int								iSubtype;					//  2012/04/02

		//
		BOOL			bCreated;


		//			
		HTREEITEM				htMyRootItem0;	
		HTREEITEM				htMyRootItem;	

		//		
		BOOL					bInitialized;			
		//HTREEITEM				htInitialItem;
	

		//
		struct			{
			int			iIDC_COMBO_layout;
			int			iIDC_COMBO_grp;
			int			iIDC_tree;
			//
			HWND		hDlgDynBmps;
			//
			int			iVwSubtype;
		}				guiData;


		//
		QY_MESSENGER_ID			idInfo_grp_sel;

		//
		DWORD			dwTickCnt_lastMouseMove;

		//
		BOOL			bLocked;

		//  2018/11/16
		struct				{
			IM_GRP_EX		imGrpEx;
		}					hzj;


	}	DLG_avRes_var;


//
extern  BOOL  g_fDragging;
extern  HIMAGELIST g_hDragImageList;





#endif  //  }


