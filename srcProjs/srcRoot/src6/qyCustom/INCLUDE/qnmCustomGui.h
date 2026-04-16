#include <myTypes.h>


#ifndef	 __QNMCUSTOMGUI_H__
#define	 __QNMCUSTOMGUI_H__	 /*  {  */



typedef  struct  __qnmQueryStruct_t  {
				 //  int							iQueryId;		//  查询的种类，暂时不用
				 QY_COLUMNINFO		*				pSql;
				 QY_COLUMNINFO		*				pDisplay;
}		 QNM_QUERY_STRUCT;

//
extern  QRT_CUSTOM_INFO		qyCustomInfo;							//  标题等信息


extern  QY_IDCITEM		*	gpTable0;								//  总的控件列表
extern  QY_IDCITEM		*	gpCb0Tables[];
extern  QY_IDCITEM		*	gpCb1Tables[];
extern  QY_IDCITEM		*	gpCb2Tables[];
extern  QY_IDCITEM		*	gpCb3Tables[];
extern  QY_IDCITEM		*	gpCb4Tables[];


//  
extern      QY_IDCITEM				CONST_updateTable[];
//  
extern		QY_IDCITEM				CONST_secChkTable0[];
extern		QY_IDCITEM				CONST_secChkTable0_smallScreen[];  	//  主要为640  *  480做的布局，2005/08/20





int  myCustomStat(  int  iSystemId,  QNM_CUSRES_INFO  *  pCusRes,  QNM_CUSTOM_COMM	*	pCustom,  void  *  p1  );


//  遗留问题
extern		QY_DMITEM				CONST_shhgRegYhlxTable[];
extern		QY_DMITEM				CONST_shhgYhlxTable[];

	//
#if  0
	#define		CONST_yhlx_bdwyh		_T(  "本单位用户"  )				//  CONST_shhgYhlxTable[0].des
	//
	#define		CONST_yhlx_wdwlsyh		_T(  "外单位临时用户"  )			//	CONST_shhgYhlxTable[1].des
	#define		CONST_yhlx_wzcyh		_T(  "未注册用户"  )				//  CONST_shhgYhlxTable[2].des
	#define		CONST_yhlx_qtdwyh		_T(  "其它单位用户"  )				//  
#endif
//
extern  TCHAR* CONST_yhlx_bdwyh;
extern  TCHAR* CONST_yhlx_wdwlsyh;
extern  TCHAR* CONST_yhlx_wzcyh;
extern  TCHAR* CONST_yhlx_qtdwyh;



	//
extern		QY_DMITEM				CONST_shhgJqlxTable[];
	//
	#define		CONST_jqlx_wj				0
	#define		CONST_jqlx_bxj				1
	#define		CONST_jqlx_fwq				2
	#define		CONST_jqlx_xxj				3
	#define		CONST_jqlx_qt				4


//  #define		DEFAULT_qwmRegToolWndTitle				"regTool"
#define		DEFAULT_qwmRegToolWndTitle				_T(  "QYCX"  )				//  2004/06/18更改


extern  "C"  QY_IDCITEM  **  getCbxTables(  int  idc  );
extern  "C"  int  getnTables(  QY_IDCITEM  *  pTables[]  );
//  void  qnmSizeSearchControls(  HWND  hDlg,  	 QY_IDCITEM  *  pTable0,	QY_IDCITEM		*	pCurTable  );
void  qnmSizeSearchControls(  QNM_CUSRES_INFO  *  pCusRes,  HWND  hDlg,  	 QY_IDCITEM  *  pTable0,	QY_IDCITEM		*	pCurTable  );
extern  "C"  QY_IDCITEM  *  qyGetIdcItemByIdc(  QY_IDCITEM  *  pTable,  int  idc  );

#endif  /*  }  */


