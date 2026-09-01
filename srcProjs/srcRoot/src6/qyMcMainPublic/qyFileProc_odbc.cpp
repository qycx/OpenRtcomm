

#include	"stdafx.h"
#include	"shlobj.h"
#ifndef  __WINCE__
		 #include	"myresource.h"
#endif
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"


#ifndef  __NOTSUPPORT_MULTIDOC__
	#include	"qyRestrictEdit.h"
	#include	"qyFile.h"
#endif
#ifdef  __isCli__
	#include	"qyFile.h"
#endif
#include	"qyCusResTemp.h"
#include	"tmpCeLib.h"
//

#ifndef  __NOTSUPPORT_MULTIDOC__
	#include	"qyMc.h"
	//  #include	"qyMcDoc.h"
	#include	"qyMcView.h"
	#include	"dlgMcHint.h"
	#include	"dlgQnmCfgOptions.h"
	#include	"DlgQnmCfgAdvancedOptions.h"
#endif 
#include	"qyDynLib.h"


//#include	"qmcVWall.h"
//#include	"qmcCmdProc.h"

#include	"qySqlFunc.h"





 QY_DMITEM		CONST_bakDataTable_netMc[]  =  
{
	{	0,	CONST_tabName_qyPcTab,								CONST_qyColsStr_qyPcTab,				},
	{	0,	CONST_tabName_qyPcRegInfoTab,						CONST_qyColsStr_qyPcRegInfoTab,			},
	//  {	0,	CONST_qyFileObjName_qyPcSpTab,					CONST_qyColsStr_qyPcSpTab,				},	//  2006/04/25, 暂时略去
	{	0,	CONST_tabName_qyCusNameTab,							CONST_qyColsStr_qyCusNameTab,			},
	{	0,	CONST_qyFileObjName_qyOsSpTab,						CONST_qyColsStr_qyOsSpTab,				},		//  2006/05/21
	{	0,	CONST_qyFileObjName_bhbScannedIpTab,				CONST_qyColsStr_bhbScannedIpTab,		},
	{	0,	CONST_qyFileObjName_qnmMacDesTab,					CONST_qyColsStr_qnmMacDesTab,			},
	{	0,	CONST_qyFileObjName_qnmIpScanTab,					CONST_qyColsStr_qnmIpScanTab,			},
	{	0,	CONST_qyFileObjName_qnmPcGrpTab,					CONST_qyColsStr_qnmPcGrpTab,			},
	{	0,	CONST_qyFileObjName_qySnmpObjTab,					CONST_qyColsStr_qySnmpObjTab,			},
	{	0,	CONST_qyFileObjName_qySwitchPortTab,				CONST_qyColsStr_qySwitchPortTab,		},
	{	0,	CONST_qyFileObjName_qySwitchConnectedPcTab,			CONST_qyColsStr_qySwitchConnectedPcTab,	},
	{	0,	CONST_qyFileObjName_qySnmpPolicyGrpTab,				CONST_qyColsStr_qySnmpPolicyGrpTab,		},
	{	0,	CONST_qyFileObjName_qySnmpObjPolicyTab,				CONST_qyColsStr_qySnmpObjPolicyTab,		},
	{	0,	CONST_qyFileObjName_qySnmpObjRuleTab,				CONST_qyColsStr_qySnmpObjRuleTab,		},		//  2005/10/23
	//
	{	0,	CONST_qyFileObjName_qyPcRuleTab,					CONST_qyColsStr_qyPcRuleTab,			},		//  2006/03/08
	{	0,	CONST_qyFileObjName_qyPcProcessRuleTab,				CONST_qyColsStr_qyPcProcessRuleTab,		},		//  2006/03/08
	{	0,	CONST_qyFileObjName_qyPcFileMonRuleTab,				CONST_qyColsStr_qyPcFileMonRuleTab,		},		//  2006/03/25
	{	0,	CONST_qyFileObjName_qyPcAdapterTab,					CONST_qyColsStr_qyPcAdapterTab,			},
	//
	{	0,	CONST_qyFileObjName_qyPcProcessKnowledgeTab,		CONST_qyColsStr_qyPcProcessKnowledgeTab,	},	//  2006/08/17
	{	0,	CONST_qyFileObjName_qyPcRegistryKnowledgeTab,		CONST_qyColsStr_qyPcRegistryKnowledgeTab,	},	//  2006/08/17
	{	0,	CONST_qyFileObjName_qyPcRegistryRuleTab,			CONST_qyColsStr_qyPcRegistryRuleTab,		},	//  2006/08/17

	//
	{	0,	CONST_qyFileObjName_qyGrpTab,						CONST_qyColsStr_qyGrpTab,					},	//  2008/09/03
	{	0,	CONST_qyFileObjName_qyUsrTab,						CONST_qyColsStr_qyUsrTab,					},	//  2008/09/03
	{	0,	CONST_qyFileObjName_qyGrpUsrRelationTab,			CONST_qyColsStr_qyGrpUsrRelationTab,		},	//  2008/09/03
	
	#ifdef  __DEBUG__
			{	0,	CONST_qyFileObjName_qyTestTab,				CONST_qyColsStr_qyTestTab,		},		//  2006/04/25
	#endif

	{	-1,	NULL,																				},
};


 QY_DMITEM		CONST_bakDataTable_isMgr[]  =
{
	{	0,	CONST_tabName_qyImObjAuthTab,				CONST_qyColsStr_qyImObjAuthTab,		},
	{	0,	CONST_tabName_qyImAmTab,					CONST_qyColsStr_qyImAmTab,			},
	{	0,	CONST_tabName_qyImObjRegInfoTab,			CONST_qyColsStr_qyImObjRegInfoTab,	},
	{	0,	CONST_tabName_qyImObjRegInfoTab1,			CONST_qyColsStr_qyImObjRegInfoTab,	},
	{	0,	CONST_tabName_qyCusNameTab,					CONST_qyColsStr_qyCusNameTab,		},
	{	0,	CONST_tabName_qyImGrpInfoTab,				CONST_qyColsStr_qyImGrpInfoTab,		},
	{	0,	CONST_tabName_qyImGrpMemTab,				CONST_qyColsStr_qyImGrpMemTab,		},
	{	0,	CONST_tabName_qyImObjTab,					CONST_qyColsStr_qyImObjTab,			},
	{	0,	CONST_tabName_qyImTaskTab,					CONST_qyColsStr_qyImTaskTab,		},
	//
	{	0,	CONST_tabName_qyImObjRuleTab,				CONST_qyColsStr_qyImObjRuleTab,		},
	//
	{	0,	CONST_tabName_qyWebContactTab,				CONST_qyColsStr_qyWebContactTab,	},
	{	0,	CONST_tabName_qyIpKnowledgeTab,				CONST_qyColsStr_qyIpKnowledgeTab,	},
	//
	{	0,	CONST_tabName_qyMessengerPhoneInfoTab,		CONST_qyColsStr_qyMessengerPhoneInfoTab,	},
	{	0,	CONST_tabName_qySmContactTab,				CONST_qyColsStr_qySmContactTab,				},
	//
	{	0,	CONST_tabName_qyDynBmpTab,					CONST_qyColsStr_qyDynBmpTab,				},
	{	0,	CONST_tabName_qyDynBmpRuleTab,				CONST_qyColsStr_qyDynBmpRuleTab,			},
	{	-1,	NULL,		},
};

  QY_DMITEM		CONST_bakDataTable_isClient[]  =
{
	{	0,	CONST_tabName_qyImObjAuthTab,				CONST_qyColsStr_qyImObjAuthTab,		},
	{	0,	CONST_tabName_qyImObjRegInfoTab,			CONST_qyColsStr_qyImObjRegInfoTab,	},
	{	0,	CONST_tabName_qyImObjRegInfoTab1,			CONST_qyColsStr_qyImObjRegInfoTab,	},
	{	0,	CONST_tabName_qyCusNameTab,					CONST_qyColsStr_qyCusNameTab,		},
	{	0,	CONST_tabName_qyImGrpInfoTab,				CONST_qyColsStr_qyImGrpInfoTab,		},
	{	0,	CONST_tabName_qyImGrpMemTab,				CONST_qyColsStr_qyImGrpMemTab,		},
	{	0,	CONST_tabName_qyImObjTab,					CONST_qyColsStr_qyImObjTab,			},
	{	0,	CONST_tabName_qyImTaskTab,					CONST_qyColsStr_qyImTaskTab,		},
	//
	{	0,	CONST_tabName_qyPhoneGuestTab,				CONST_qyColsStr_qyPhoneGuestTab,	},
	{	0,	CONST_tabName_qyImOtherRegInfoTab,			CONST_qyColsStr_qyImOtherRegInfoTab,},

	{	-1,	NULL,		},
};


 QY_DMITEM  *  getBakDataTable(  int  iServiceId,  int  iAppType  )
{
	 QY_DMITEM		*	pBakDataTable	=		NULL;

	 switch  (  iServiceId  )  {
			 case  CONST_qyServiceId_is:
				   pBakDataTable  =  (  iAppType  ==  CONST_qyAppType_client  )  ?  CONST_bakDataTable_isClient  :  CONST_bakDataTable_isMgr;
				   break;
			 case  CONST_qyServiceId_netMc:
				   pBakDataTable  =  CONST_bakDataTable_netMc;
				   break;
			 default:
					goto  errLabel;
	 }

errLabel:
	 return  pBakDataTable;
}

 BOOL  bQnmImportBakData(  int  iServiceId,  int  iAppType,  QY_IMEXPORTINFO  *  pImportInfo  )
{
#ifdef  __NOTSUPPORT_qyFile__							//  2011/03/07
		return  FALSE;
#else
	 BOOL				bRet			=		FALSE;
	 QY_MC			*	pQyMc			=		QY_GET_GBUF(  );
	 CQyFile			file;
	 BOOL				bFileOpen		=		FALSE;
	 char				ver[32  +  1];
	 QY_DMITEM		*	pItem			=		NULL;
	 char				buf[1024];
	 char				buf1[1024];
	 TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1];
	 unsigned  char		ucbUtf8			=		TRUE;
	 unsigned  char		ucb0319			=		FALSE;
	 unsigned  char		ucb0339			=		FALSE;
	 //
	 unsigned  char		ucb0148			=		FALSE;
	 //
	 unsigned  char		ucb0149			=		FALSE;	//  2017/08/15
	 //
	 QY_DMITEM		*	pBakDataTable	=		NULL;

	 if  (  !(  pBakDataTable  =  getBakDataTable(  iServiceId,  iAppType  )  )  )  goto  errLabel;
	 
	 if  (  iServiceId  ==  CONST_qyServiceId_netMc  )  {
		 //  2006/03/25
		 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from qyPcFileMonRuleTab"  )  );
		 if  (  !bQyExecSql(  pImportInfo->pDb,  sqlBuf  )  )  goto  errLabel;
	 }


	 if  (  !file.Open(  CQyString(  pImportInfo->fileName  ).GetBuffer(  0  ),  CFile::modeRead  )  )  goto  errLabel;
	 bFileOpen  =  TRUE;

	 try  {
		  
		  if  (  !file.bGetObjData(  CONST_qyFileObj_ver,  ver,  sizeof(  ver  )  )  )  goto  errLabel;

		  if  (  iServiceId  ==  CONST_qyServiceId_netMc  )  {

			  //  0319
			  if  (  strncmp(  ver,  CONST_ver_0319,  strlen(  CONST_ver_0319  )  )   <=  0  )  {
				  ucbUtf8  =  FALSE;  ucb0319  =  TRUE;
			  }
			  //  0339
			  if  (  strncmp(  ver,  CONST_ver_0339,  strlen(  CONST_ver_0339  )  )   <=  0  )  {
				  ucb0339  =  TRUE;
			  }

			  //  处理0206以下版(含0206)的备份数据
			  if  (  strncmp(  ver,  CONST_ver_0206,  strlen(  CONST_ver_0206  )  )   <=  0  )  {
				  file.bImportSqlTable(  pImportInfo->pDb,  pImportInfo->iDbType,  myTChar2Str(  CONST_tabName_qyPcTab,  buf,  sizeof(  buf  )  ),  myTChar2Str(  CONST_qyColsStr_qyPcTab0206,  buf1,  sizeof(  buf1  )  ),  ucbUtf8  );
				  file.bImportSqlTable(  pImportInfo->pDb,  pImportInfo->iDbType,  myTChar2Str(  CONST_tabName_qyPcRegInfoTab,  buf,  sizeof(  buf  )  ),  myTChar2Str(  CONST_qyColsStr_qyPcRegInfoTab0206,  buf1,  sizeof(  buf1  )  ),  ucbUtf8  );
				  bRet  =  TRUE;  goto  errLabel;
			  }
		  }
		  if  (  iServiceId  ==  CONST_qyServiceId_is  )  {		//  2014/02/03
			  if  (  strncmp(  ver,  CONST_ver_0148,  strlen(  CONST_ver_0148  )  )  <=  0  )  {
				  ucb0148  =  TRUE;
			  }
			  //  2017/08/14
			  if  (  strncmp(  ver,  CONST_ver_0149,  strlen(  CONST_ver_0149  )  )  <=  0  )  {
				  ucb0149  =  TRUE;
			  }


		  }

		  //  处理更高版的备份数据	 
		  //  
		  for  (  pItem  =  pBakDataTable;  pItem->type  !=  -1;  pItem  ++  )  {
			   if  (  iServiceId  ==  CONST_qyServiceId_netMc  )  {
				   //
				   if  (  ucb0339  )  {
					   if  (  !_tcsicmp(  pItem->des,  CONST_qyFileObjName_qyPcRuleTab  )  )  pItem->pData  =  CONST_qyColsStr_qyPcRuleTab0339;
				   }
				   //
			   	   if  (  ucb0319  )  {
					   if  (  !_tcsicmp(  pItem->des,  CONST_qyFileObjName_qySnmpObjRuleTab  )  )  pItem->pData  =  CONST_qyColsStr_qySnmpObjRuleTab0319;
				   }
			   }
			   if  (  iServiceId  ==  CONST_qyServiceId_is  )  {
				   //
				   if  (  ucb0149  )  {  //  2017/08/14		
					   //
					   if  (  !_tcsicmp(  pItem->des,  CONST_tabName_qyImObjAuthTab  )  )  pItem->pData  =  CONST_qyColsStr_qyImObjAuthTab_0149;
					   //		
					   if  (  !_tcsicmp(  pItem->des,  CONST_tabName_qyImObjTab  )  )  pItem->pData  =  CONST_qyColsStr_qyImObjTab_0149;
				   }
				   //
				   if  (  ucb0148  )  {
					   if  (  !_tcsicmp(  pItem->des,  CONST_tabName_qyImGrpInfoTab  )  )  pItem->pData  =  CONST_qyColsStr_qyImGrpInfoTab_0148;
				   }

			   }

			   file.bImportSqlTable(  pImportInfo->pDb,  pImportInfo->iDbType,  myTChar2Str(  pItem->des,  buf,  sizeof(  buf  )  ),  myTChar2Str(  pItem->pData,  buf1,  sizeof(  buf1  )  ),  ucbUtf8  );

			   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  ""  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_Import  ),  _T(  " %s %s"  ),  pItem->des,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_completed  )  ); 

		  }

		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bQnmImportBakData failed."  )  );
		   goto  errLabel;
	}

	 bRet  =  TRUE;

errLabel:
	 
	 if  (  bFileOpen  )  file.Close(  );

	 return  bRet;
#endif
}


 


 BOOL  bQnmExportBakData(  int  iServiceId,  int  iAppType,  QY_IMEXPORTINFO  *  pExportInfo  )
{
#ifdef  __NOTSUPPORT_qyFile__
		return  FALSE;
#else

	 BOOL				bRet			=	FALSE;
	 QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	 CQyFile			file;
	 BOOL				bFileOpen		=	FALSE;
	 CQyString			sqlStr;
	 CRecordset			rs(  (  (  CDatabase  *  )pExportInfo->pDb  )  );
	 QY_DMITEM		*	pItem			=	NULL;
	 char				timeBuf[CONST_qyTimeLen  +  1];
	 char				hVerBuf[CONST_qyMaxVerLen  +  1];
	 char				sqlBuf[CONST_maxSqlBufLen  +  1];
	 char				buf[1024];
	 QY_DMITEM		*	pBakDataTable	=	NULL;
	 
	 //
	 int  iDbType  =  pQyMc->cfg.db.iDbType;

	 //
	 if  (  !(  pBakDataTable  =  getBakDataTable(  iServiceId,  iAppType  )  )  )  goto  errLabel;

	 if  (  !file.Open(  CQyString(  pExportInfo->fileName  ).GetBuffer(  0  ),  CFile::modeCreate | CFile::modeWrite  )  )  goto  errLabel;
	 bFileOpen  =  TRUE;

	 try  {
		  //  先写题头
		  file.bExportCls(  CONST_qyFileCls_file  );
		  file.bExportObj(  CONST_qyFileObj_name,  CONST_qyFileObjName_qrgBak  );
		  file.bExportObj(  CONST_qyFileObj_customId,  qyGetCustomId(  )  );
		  //  _snprintf(  hVerBuf,  sizeof(  hVerBuf  ),  "%04d",  atol(  qnmVerStr(  iServiceId  )  )  /  100  );
		  _snprintf(  hVerBuf,  sizeof(  hVerBuf  ),  "%04d",  atol(  qnmDbVerStr(  iServiceId  )  )  /  100  );
		  file.bExportObj(  CONST_qyFileObj_ver,  hVerBuf  );
		  getCurTime(  timeBuf  );
		  file.bExportObj(  CONST_qyFileObj_createTime,  timeBuf  );
		  file.bExportObj(  CONST_qyFileObj_comment,  "Note: Don't modify this file."  );	//  严禁修改文件内容，否则将破坏数据的正确性"  );
		  file.bExportObj(  CONST_qyFileObj_end  );

		  file.writeEndLine(  );
		  file.writeEndLine(  );
		  file.writeEndLine(  );

		  file.bExportCls(  CONST_qyFileCls_data  );

		  //
		  
		  QY_SYSTEMINFO_RCD		dbInfo;
		  unsigned  char		ucbLe0335			=	FALSE;	//  0335以前(含)，qyUsrTab里没加限制用户信息
		  
		  if  (  !bGetSystemInfo(  pExportInfo->pDb,  iDbType,  &dbInfo  )  //  早期的版本的qySystemInfoTab的格式和现在不同，所以，读取不能成功
			  ||  strncmp(  dbInfo.dbVer,  CONST_ver_0335,  strlen(  CONST_ver_0335  )  )   <=  0  )  
		  {
			  ucbLe0335  =  TRUE;			  
		  }


		  for  (  pItem  =  pBakDataTable;  pItem->type  !=  -1;  pItem  ++  )  {

			   if  (  ucbLe0335  )  {
				   if  (  !_tcsicmp(  pItem->des,  CONST_qyFileObjName_qyGrpTab  )  )  continue;
				   if  (  !_tcsicmp(  pItem->des,  CONST_qyFileObjName_qyUsrTab  )  )  continue;
				   if  (  !_tcsicmp(  pItem->des,  CONST_qyFileObjName_qyGrpUsrRelationTab  )  )  continue;				   
			   }

	   		   sqlStr  =  CQyString(  "select "  )  +  CQyString(  pItem->pData  )  +  CQyString(  " from  "  )  +  CQyString(  pItem->des  );
			   myTChar2Str(  sqlStr.GetBuffer(  0  ),  sqlBuf,  sizeof(  sqlBuf  )  );
			   file.bExportSqlQuery(  pExportInfo->pDb,  pExportInfo->iDbType,  myTChar2Str(  pItem->des,  buf,  sizeof(  buf  )  ),  sqlBuf  );

			   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  ""  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_Export  ),  _T(  " %s %s"  ),  pItem->des,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_completed  )  ); 

 		  }

		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bQnmExportBakData failed."  )  );
		   goto  errLabel;
	}

	 bRet  =  TRUE;

errLabel:

	 if  (  bFileOpen  )  file.Close(  );

	 return  bRet;
#endif
}

