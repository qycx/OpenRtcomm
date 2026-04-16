

#ifndef  __dlgImObjRuleProc_h__
#define  __dlgImObjRuleProc_h__		//  {



typedef  struct  __dlgGuiData_imObjRule_t {
	BOOL												bInited;
	int												iWndContentType;
	//
	int												w_org, h_org;

	int												iIDC_STATIC_hint_imObjRule;
	RECT												rcIDC_STATIC_hint_imObjRule;

	int												iIDC_STATIC_autoAnswer_av;
	RECT												rcIDC_STATIC_autoAnswer_av;

	int												iIDC_COMBO_autoAnswer_av;
	RECT												rcIDC_COMBO_autoAnswer_av;

	int												iIDC_STATIC_autoAnswer_screen;
	RECT												rcIDC_STATIC_autoAnswer_screen;

	int												iIDC_COMBO_autoAnswer_screen;
	RECT												rcIDC_COMBO_autoAnswer_screen;

	int												iIDC_STATIC_autoAnswer_mediaFile;
	RECT												rcIDC_STATIC_autoAnswer_mediaFile;

	int												iIDC_COMBO_autoAnswer_mediaFile;
	RECT												rcIDC_COMBO_autoAnswer_mediaFile;

	int												iIDOK;
	RECT												rcIDOK;
	int												iIDCANCEL;
	RECT												rcIDCANCEL;


}		 DLG_guiData_imObjRule;

typedef  struct  __dlgImObjRuleVar_t {
	DLG_guiData_imObjRule								guiData;

	//MIS_CNT* pMisCnt;
	QY_MESSENGER_ID									idInfo;

	QY_im_rules										imRules;
	QY_imObj_rules										rules;

	//
	HWND												m_hCurTalk;


}		 DLG_imObjRule_var;


#endif

