

#ifndef  __QYLANGCOMMPROC_H__
#define  __QYLANGCOMMPROC_H__	/*  {  */


#define		CONST_langId_tw					0x0404			//  Chinese (Taiwan Region) 
#define		CONST_langId_PRC				0x0804			//  Chinese (PRC) 
#define		CONST_langId_hk					0x0c04			//  Chinese (Hong Kong SAR, PRC) 
#define		CONST_langId_Singapore			0x1004			//  Chinese (Singapore) 

#define		CONST_langId_US					0x0409			//  English (United States) 
#define		CONST_langId_UK					0x0809			//	English (United Kingdom) 
#define		CONST_langId_Australian			0x0c09			//  English (Australian) 
#define		CONST_langId_Candian			0x1009			//  English (Canadian) 
#define		CONST_langId_NewZealand			0x1409			//  English (New Zealand) 
#define		CONST_langId_Ireland			0x1809			//	English (Ireland) 
#define		CONST_langId_SouthAfrica		0x1c09			//  English (South Africa) 
#define		CONST_langId_Jamaica			0x2009			//  English (Jamaica) 
#define		CONST_langId_Caribbean			0x2409			//	English (Caribbean) 
#define		CONST_langId_Belize				0x2809			//  English (Belize) 
#define		CONST_langId_Trinidad			0x2c09			//  English (Trinidad) 

#define		CONST_langId_Japanese			0x0411			//	Japanese 
#define		CONST_langId_Korean				0x0412			//  Korean 
#define		CONST_langId_KoreanJohab		0x0812			//  Korean (Johab) 
#define		CONST_langId_Russian			0x0419			//  Russian 
#define		CONST_langId_RussianMoldavia	0x0819			//  Russian(Moldavia) 



#ifdef  __cplusplus
  extern  "C"  {
#endif

	  
extern  QY_IDCITEM  CONST_langStrTable[];				//  Locale,  ISO 369 abbreviated (no hyphen) language string,  ISO 369 standard accept language string 

extern  QY_DMITEM	CONST_qyLangTable[];
extern  QY_DMITEM	CONST_qyLangTable_en[];

typedef  struct  __qnmCusResModuleMem_t						{
				 int										iResId_sys;
				 QY_DMITEM							*		pSysResTable;		//  本系统应用的资源库			//  2005/11/06
				 QY_DMITEM							*		pCusStrTable;		//  本系统的字符库
				 QY_DMITEM							*		pCusMenuTable;		//  本系统的菜单库
				 QY_DMITEM							*		pCusDlgTable;		//  本系统的对话框资源库
}		 QNM_cusRes_moduleMem;


typedef  struct  __qnmCusResInfo_t							{
				 WCHAR										suffix[32];			//  区分资源的后缀符号
				 HINSTANCE									hDll;
				 void								*		pResTable;			//  全部的资源库
#if  0
				 QY_DMITEM							*		pSysResTable;		//  本系统应用的资源库			//  2005/11/06
				 QY_DMITEM							*		pCusStrTable;		//  本系统的字符库
				 QY_DMITEM							*		pCusMenuTable;		//  本系统的菜单库
				 QY_DMITEM							*		pCusDlgTable;		//  本系统的对话框资源库
#endif
				 QNM_cusRes_moduleMem						mems[5];

}		 QNM_CUSRES_INFO;

#define		CONST_fn_getResTable		"getQnmResTable"


int  initQnmRes(  void  *  p0,  unsigned  short  usLangId,  int  iResId_sys,  QNM_CUSRES_INFO  *  pInfo  );
void  exitQnmRes(  void  *  p0,  QNM_CUSRES_INFO  *  pInfo  );
int  addModuleMem_qnmRes(  int  iResId_sys,  QNM_CUSRES_INFO  *  pInfo  );

int  set_cur_iResId_sys(  int  iResId_sys  );
//
int   set_cur_pQnmCusResInfo(  void  *  pQnmCusResInfo  );
QNM_CUSRES_INFO  *  get_cur_pQnmCusResInfo(  );

//
QNM_cusRes_moduleMem  *  getCurCusResModuleMem(  QNM_CUSRES_INFO  *  pInfo  );

//
TCHAR  *  getTableResStr(  void  *  p0,  QY_DMITEM  *  pTable,  void  *  pQnmCusResInfo,  int  type  );
QY_DMITEM  *  getResItem(  void  *  p0,  QNM_CUSRES_INFO  *  pInfo,  int  iResId  );
QY_DMITEM  *  getResTable(  void  *  p0,  QNM_CUSRES_INFO  *  pInfo,  int  iResId  );
void  *  getResQueryStruct(  void  *  p0,  QNM_CUSRES_INFO  *  pInfo,  int  iResId  );
void  *  getResSearch(  void  *  p0,  QNM_CUSRES_INFO  *  pInfo,  int  iResId  );
void  *  getResColumnInfo(  void  *  p0,  QNM_CUSRES_INFO  *  pInfo,  int  iResId  );





#ifdef  __cplusplus
  }
#endif




#endif  /*  }  */


