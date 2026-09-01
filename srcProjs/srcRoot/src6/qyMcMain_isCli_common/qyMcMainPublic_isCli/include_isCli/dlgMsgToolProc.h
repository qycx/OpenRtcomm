

#ifndef  __DLGMSGTOOLPROC_H__
#define  __DLGMSGTOOLPROC_H__	//  {

typedef  struct  __dlgGuiDataMsgTool_t									{

				 //  DLG_guiDataParam_talk								param;
				 BOOL												bInfoSet;

				 //  2012/05/18
				 int												iIDC_LIST_task;
				 int												iIDC_STATIC_instantStatus;
				 int												iIDC_STATIC_recentMsgList;
				 int												iIDC_STATIC_input;

				 //
				 BOOL												bFinished_createCtrls;
				 BOOL												bCreated;					//  这个标志位用来表明是否Create(  )成功了。成功了，则将资源的释放留给了dlg自己(在PostNcDestroy(  )中delete)


}		 DLG_guiData_msgTool;


typedef	struct  __dlgMsgToolVar_t			{
			HWND							m_hParent;
			int								m_nID;
			//  BOOL							bInfoSet;
			
			//
			BOOL							bInitFailed;				//  2007/09/04

			//
			unsigned  char					ucbUseHtmlEdit;				//  2012/05/17. 只有需要输入的窗口才使用HtmlEdit, 主窗口和墙上的小talk窗口都不需要使用


			//
			HWND							hDlgTalk;

			//
			MSG_tool_common					msgToolCommon;

			//
			DLG_guiData_msgTool				guiData;


			//  2013/07/04			
			void							*		pm_LargeImageList;
			void							*		pm_SmallImageList;


			//
			DLG_syncFlgs					syncFlgs;

	}		DLG_msgTool_var;


#endif  //  }



