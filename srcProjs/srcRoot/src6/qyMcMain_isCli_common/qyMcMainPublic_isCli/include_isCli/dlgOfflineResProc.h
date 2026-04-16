


#ifndef  __dlgOfflineResProc_h__
#define  __dlgOfflineResProc_h__	//  {

//
typedef  struct  __dlgGuiDataOfflineRes_t {
	BOOL												bInited;


	int												iw_org, ih_org;

	int												iIDC_LIST_offlineRes;
	RECT												rcIDC_LIST_offlineRes;
	int												iIDC_BUTTON_download;
	RECT												rcIDC_BUTTON_download;
	int												iIDC_BUTTON_upload;
	RECT												rcIDC_BUTTON_upload;
	int												iIDC_BUTTON_refresh;
	RECT												rcIDC_BUTTON_refresh;
	int												iIDC_BUTTON_delete;
	RECT												rcIDC_BUTTON_delete;
	//
	int												iIDC_BUTTON_page1;
	RECT												rcIDC_BUTTON_page1;
	int												iIDC_BUTTON_nextPage;
	RECT												rcIDC_BUTTON_nextPage;
	int												iIDC_BUTTON_prevPage;
	RECT												rcIDC_BUTTON_prevPage;
	int												iIDC_EDIT_pageNo;
	RECT												rcIDC_EDIT_pageNo;
	int												iIDC_BUTTON_go;
	RECT												rcIDC_BUTTON_go;
	int												iIDC_STATIC_filterKeywords;
	RECT												rcIDC_STATIC_filterKeywords;
	int												iIDC_EDIT_filterKeywords;
	RECT												rcIDC_EDIT_filterKeywords;
	//
	int												iIDC_BUTTON_showAllDownloads;
	RECT												rcIDC_BUTTON_showAllDownloads;
	//
	int												iIDCANCEL;
	RECT												rcIDCANCEL;


}		 DLG_guiData_offlineRes;



//
typedef  struct  __res_inProcess_t {
	QIS_offline_res				res;
	//
	unsigned  short				usSubtype;
	//
	int							index;
	//
	int							iTaskId;
	unsigned  int					uiTranNo_real;
	//
	int							iStatus;
	//
	myTRANSFER_FILE_STATUS			transferFileStatus;
	DWORD							dwTickCnt_modified;
	//
}		 RES_inProcess;


//
typedef  struct {
	HWND							m_hParent;
	//
	int								m_nID;
	BOOL							bInfoSet;
	BOOL							bCreated;					//  这个标志位用来表明是否Create(  )成功了。成功了，则将资源的释放留给了dlg自己(在PostNcDestroy(  )中delete)
	BOOL							bInited;					//  表明htmlEdit和对话都初始化完了.

	DLG_guiData_offlineRes			guiData;					//
	//
	int								iWndContentType;
	int								iWndContentSubType;
	//
	TCHAR							title[64];

	//
	QY_MESSENGER_ID					idInfo;
	HWND							hCurTalk;
	HWND							hDlgTalk_mgr;
	unsigned char					ucbConfMgr;

	//
	//MIS_CNT* pMisCnt;

	//
	unsigned  short					usIndex_page;
	//
	struct {
		//
		unsigned  short				usCnt;
		RES_inProcess				mems[MAX_offlineRes_mems];
	}								reses_retrieved;				//  从文件服务器上取回的已存储的的文件列表信息
	//
	struct {
		unsigned  short				usCnt;
		RES_inProcess				mems[MAX_offlineRes_mems];
	}								reses_beingProced;				//  任务列表

	struct {
		HWND						hListCtrl;
		int							iSelectItem;
	}								listCtrl;



}  DlgOfflineRes_var;







#endif  //  }


