
#ifndef   __QMOBJS_H__
#define   __QMOBJS_H__	/*  {  */


//  
#define		CONST_qyPsType_export							1
#define		CONST_qyPsType_import							2
#define		CONST_qyPsType_clearup							3
#define		CONST_qyPsType_show								4
#define		CONST_qyPsType_stat								5

//  导入导出信息设定
#define		CONST_qyPsTask_procCurQuery						1
//  #define		CONST_qyPsTask_procRegInfo						3
//  #define		CONST_qyPsTask_procCfg							4
#define		CONST_qyPsTask_procBhbCfg						5
#define		CONST_qyPsTask_procBakData						6
#define		CONST_qyPsTask_clearupScannedIp					100
#define		CONST_qyPsTask_clearupEvent						102
#define		CONST_qyPsTask_procDjData						103		//  
#define		CONST_qyPsTask_procDj98							104
#define		CONST_qyPsTask_procPcProcessKnowledge			105
#define		CONST_qyPsTask_procPcRegistryKnowledge			106
#define		CONST_qyPsTask_procImMsg						107
#define		CONST_qyPsTask_procImHisTask					108
#define		CONST_qyPsTask_procIpKnowledge					109
#define		CONST_qyPsTask_procPhoneGuest					110
//
#define		CONST_qyPsTask_exportClient_default				120		//  2011/03/25
#define		CONST_qyPsTask_exportClient_ts_logon			121
#define		CONST_qyPsTask_exportClient_ts_dev				122

//
#define		CONST_qyFileType_html							1
#define		CONST_qyFileType_excel							2
#define		CONST_qyFileType_qpl							3



typedef  struct  __qyImExportInfo_t							{
				 int										iTask;
				 HWND										hCurWnd;
				 TCHAR										fileName[CONST_qyMaxPathLen  +  1];
				 int										iFileType;
				 //
				 TCHAR										docTitle[256];			//  2006/02/25  
				 
				 void							*			pDb;
				 int										iDbType;				//  2006/05/06

}		 QY_IMEXPORTINFO;


typedef  struct  __qyClearupInfo_t							{
				 int										iTask;
				 char										fromTimeBuf[CONST_qyTimeLen  +  1];
				 char										toTimeBuf[CONST_qyTimeLen  +  1];
}		 QY_CLEARUPINFO;



typedef  struct  __qnmWmBufExport_t							{
				 MACRO_qyWmBuf_commHead

				 QY_IMEXPORTINFO							exportInfo;
}		 QNM_WMBUF_EXPORT;



// 该实体的信息
/*
typedef  struct  __qyMcRcd_t								{
				 BOOL										bRoot;
				 char										sjName[64 + 1];
				 char										sjIp[15 + 1];
				 char										name[64 + 1];
}		 QYMC_RCD;
*/

typedef  struct  __qyUsrRcd_t								{		//  2008/09/04
				 char										name[256  +  1];
				 char										passwd_unused[1];
				 //
				 TCHAR										zbStr[64  +  1];
				 TCHAR										bbStr[64  +  1];
				 TCHAR										dwStr[64  +  1];
				 TCHAR										bmStr[64  +  1];
}		 QY_USR_RCD;


BOOL  bGetQyUsrInfoBySth(  void  *  pDbParam,  int  iDbType,  char  *  name,  QY_USR_RCD  *  pUsrInfo  );


typedef  struct  __qySystemInfoRcd_t						{		//  2007/08/08
				 int										iServiceId;
				 int										iSystemId;
				 int										iAppType;
				 TCHAR										name[15  +  1];
				 char										dbVer[32  +  1];
}		 QY_SYSTEMINFO_RCD;


__declspec(  dllexport  )  BOOL  bGetSystemInfo(  void  *  pDbParam,  int  iDbType,  QY_SYSTEMINFO_RCD  *  pSystemInfo  );





#endif   /*  }  */


