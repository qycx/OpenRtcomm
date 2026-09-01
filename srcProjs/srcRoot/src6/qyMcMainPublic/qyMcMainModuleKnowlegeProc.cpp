

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyMcMainCommonObj.h"
#include	"qyWmComm.h"
#include	"qyFile.h"
#include	"myresource.h"
#include	"DlgModuleKnowlegeOptions.h"
#include	"qyCusResTemp.h"
#include	"qyPs.h"
#include	"pcCommType_defs.h"





#define		CONST_maxModuleKnowlegeFileLineLen		4096
char		CONST_sym_unicode[3]	=				{	(  char  )0xff,  (  char  )0xfe,	};
#define		CONST_maxCols_knowlege					60	 


 BOOL  bImportKnowledge(  unsigned  int  uiType  )
{
	 BOOL							bRet			=	FALSE;
	 QY_MC						*	pQyMc			=	QY_GET_GBUF(  );
	 int							iDbType			=	pQyMc->cfg.db.iDbType;
	 CDlgModuleKnowlegeOptions		dlg;
	 unsigned  char					ucbAudited		=	FALSE;
	 CQyString						pathCStr;
	 unsigned  char					ucbUnicode		=	FALSE;
	 CQyFile						file;
	 BOOL							bFileOpen		=	FALSE;
	 TCHAR							tBuf[CONST_maxModuleKnowlegeFileLineLen  +  1];
	 QY_COLUMNINFO					sqlCols[CONST_maxCols_knowlege  +  1];
	 //  QY_COLUMNINFO				*	pColumn			=	NULL;
	 QNM_QUERY_STRUCT			*	pQueryStruct	=	NULL;
	 int							i,  j;
	 TCHAR						*	pT				=	NULL;
	 TCHAR						*	pT1				=	NULL;
	 CString						str;
	 CString						insertColsStr,  insertValsStr,  updateStr1,  updateStr2;
	 CString						tabNameStr;
	 //
	 CString						moduleNameStr;	int							moduleNameIndex		=	-1;
	 CString						cmdLineStr;		int							cmdLineIndex		=	-1;
	 //
	 CString						iRootKeyStr;	int							iRootKeyIndex		=	-1;
	 CString						subKeyStr;		int							subKeyIndex			=	-1;
	 CString						cfgNameStr;		int							cfgNameIndex		=	-1;
	 //
	 CString						startIpStr;		int							startIpIndex		=	-1;
	 CString						endIpStr;		int							endIpIndex			=	-1;
	 //
	 CString						misServNameStr;	int							misServNameIndex	=	-1;
	 CString						uiDevTypeStr;	int							uiDevTypeIndex		=	-1;
	 CString						wDevIdStr;		int							wDevIdStrIndex		=	-1;
	 // 
	 char							timeBuf[CONST_qyTimeLen  +  1];
	 TCHAR							tBuf1[256];
	 char							buf[255  +  1];
	 LPCTSTR						lpszFilter		=	NULL;
	 TCHAR							tBuf_filter[256];
	 TCHAR						*	pStop;
	 TCHAR							sqlBuf[CONST_maxSqlBufLen  +  1];


	 switch  (  uiType  )  {
			 case  CONST_pcCommType_pcProcessKnowledge:
				   pQueryStruct  =  (  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpPcProcessKnowledgeListQueryStruct  );
				   //  lpszFilter  =  _T(  "QY-A进程/模块知识库(*.xls)|*.xls|QY-A进程/模块知识库(*.txt)|*.txt||"  );
				   _sntprintf(  tBuf_filter,  mycountof(  tBuf_filter  ),  _T(  "QY-A %s(*.xls)|*.xls|QY-A %s(*.txt)|*.txt||"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyCfgModuleInfo  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyCfgModuleInfo  )  );
				   lpszFilter  =  _T("QY-A Process Bases (*.xls; *.txt)\0*.xls; *.txt\0\0");
				   tabNameStr  =  CString(  "qyPcProcessKnowledgeTab"  );
				   //
				   if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;
				   ucbAudited  =  dlg.m_var.ucbAudited;
				   break;
			 case  CONST_pcCommType_pcRegistryKnowledge:
				   if  (  !dlg.bSetDlgInfo(  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_unAudited_pcRegistry  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_audited_pcRegistry  )  )  )  goto  errLabel;   
				   pQueryStruct  =  (  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpPcRegistryKnowledgeListQueryStruct  );
				   _sntprintf(  tBuf_filter,  mycountof(  tBuf_filter  ),  _T(  "QY-A %s(*.xls)|*.xls|QY-A %s(*.txt)|*.txt||"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_registryKnowledge  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_registryKnowledge  )  );
				   lpszFilter  =  _T("QY-A Registry Bases (*.xls; *.txt)\0*.xls; *.txt\0\0");
				   tabNameStr  =  CString(  "qyPcRegistryKnowledgeTab"  );
				   //
				   if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;
				   ucbAudited  =  dlg.m_var.ucbAudited;
				   break;
			 case  CONST_imCommType_ipKnowledge:
				   pQueryStruct  =  (  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpIpKnowledgeListQueryStruct_is  );
				   _sntprintf(  tBuf_filter,  mycountof(  tBuf_filter  ),  _T(  "QY-B %s(*.xls)|*.xls|QY-B %s(*.txt)|*.txt||"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_ipKnowledge  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_ipKnowledge  )  );
				   lpszFilter  =  _T("QY-B IP Bases (*.xls; *.txt)\0*.xls; *.txt\0\0");
				   tabNameStr  =  CONST_tabName_qyIpKnowledgeTab;
				   //
				   break;
			 case  CONST_imCommType_phoneGuest:
				   pQueryStruct  =  (  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpPhoneGuestListQueryStruct_is  );
				   //	lpszFilter  =  _T(  "QY 手机通信录(*.xls)|*.xls|QY 手机通信录(*.txt)|*.txt||"  );
				   _sntprintf(  tBuf_filter,  mycountof(  tBuf_filter  ),  _T(  "QY-B %s(*.xls)|*.xls|QY-B %s(*.txt)|*.txt||"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_phoneGuest  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_phoneGuest  )  );
				   lpszFilter  =  _T("QY-B Phone Books (*.xls; *.txt)\0*.xls; *.txt\0\0");
				   tabNameStr  =  CONST_tabName_qyImOtherRegInfoTab;
				   //
				   break;
			 default:	
					 goto  errLabel;
	 }

	 qyBrowseForFile(  NULL,  TRUE,  _T(  "xls\0"  ),  OFN_FILEMUSTEXIST,  lpszFilter,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_selectFilenameFormat  ),  NULL,  pQyMc,  pathCStr  );
	 if  (  !pathCStr.GetLength(  )  )  goto  errLabel;

	 {

	 CWaitCursor	cur;

	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  ""  ),  _T(  " ..."  ),  _T(  ""  )  ); 

	 getCurTime(  timeBuf  );

	 if  (  !file.Open(  pathCStr.GetBuffer(  0  ),  CFile::modeRead  |  CFile::shareDenyNone  )  )  goto  errLabel;
	 bFileOpen  =  TRUE;

	 if  (  !file.gets(  (  char  *  )tBuf,  3  )  )  goto  errLabel;
	 if  (  !_strnicmp(  (  char  *  )tBuf,  CONST_sym_unicode,  strlen(  CONST_sym_unicode  )  )  )  ucbUnicode  =  TRUE;

	 if  (  !ucbUnicode  )  {
		 AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_unicodeImportFmt  )  );  goto  errLabel;
	 }

	 memset(  sqlCols,  0,  sizeof(  sqlCols  )  );

	 if  (  !file.gets(  tBuf,  mycountof(  tBuf  )  )  )  {
		 AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_errOfImportFmt  )  );  goto  errLabel;
	 }
	 for  (  pT  =  tBuf,  i  =  0;  ;  )  {
		  		 
		  pT1  =  _tcschr(  pT,  _T(  '\t'  )  );
		  if  (  pT1  )  {  *pT1  =  0;  pT1  ++  ;  }
		  tTrim(  pT  );

		  traceLogA(  "[%S]",  pT  );

		  for  (  j  =  0;  pQueryStruct->pDisplay[j].type  !=  -1;  j  ++  )  {
			   str  =  CString(  pQueryStruct->pDisplay[j].label  );  MACRO_CStringTrim(  str  );
			   if  (  !_tcsicmp(  str,  pT  )  )  break;

		  }		  

		  if  (  i  +  1  +  1  >  mycountof(  sqlCols  )  )  {
			  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_tooMoreColumn  )  );  goto  errLabel;
		  }
		  //
		  if  (  pQueryStruct->pDisplay[j].type  ==  -1  )  sqlCols[i].type  =  -2;
		  else  if  (  _tcsstr(  pQueryStruct->pSql[j].label,  _T(  ".id"  )  )  )  sqlCols[i].type  =  -2;
		  else  if  (  _tcsstr(  pQueryStruct->pSql[j].label,  _T(  ".auditTime"  )  )  )  sqlCols[i].type  =  -2;
		  else  {
			    BOOL  bSkipped  =  FALSE;

			    //  这里先要取一些必要的项
			    switch  (  uiType  )  {
						case  CONST_pcCommType_pcProcessKnowledge:
							  if  (  _tcsstr(  pQueryStruct->pSql[j].label,  _T(  ".fileName"  )  )  )  moduleNameIndex  =  i;
							  if  (  _tcsstr(  pQueryStruct->pSql[j].label,  _T(  ".cmdLine"  )  )  )  cmdLineIndex  =  i;		//  2006/09/06
							  break;
						case  CONST_pcCommType_pcRegistryKnowledge:
							  if  (  _tcsstr(  pQueryStruct->pSql[j].label,  _T(  ".iRootKey"  )  )  )  iRootKeyIndex  =  i;
							  else  if  (  _tcsstr(  pQueryStruct->pSql[j].label,  _T(  ".subKey"  )  )  )  subKeyIndex  =  i;
							  else  if  (  _tcsstr(  pQueryStruct->pSql[j].label,  _T(  ".cfgName"  )  )  )  cfgNameIndex  =  i;
							  break;
						case  CONST_imCommType_ipKnowledge:
							  if  (  _tcsstr(  pQueryStruct->pSql[j].label,  _T(  "startIp"  )  )  )  startIpIndex  =  i;
							  else  if  (  _tcsstr(  pQueryStruct->pSql[j].label,  _T(  "endIp"  )  )  )  endIpIndex  =  i;
							  break;
						case  CONST_imCommType_phoneGuest:
							  if  (  _tcsstr(  pQueryStruct->pSql[j].label,  _T(  "misServName"  )  )  )  misServNameIndex  =  i;
							  else  if  (  _tcsstr(  pQueryStruct->pSql[j].label,  _T(  "uiDevType"  )  )  )  uiDevTypeIndex  =  i;
							  else  if  (  _tcsstr(  pQueryStruct->pSql[j].label,  _T(  "wDevIdStr"  )  )  )  wDevIdStrIndex  =  i;
							  else  if  (  _tcsstr(  pQueryStruct->pSql[j].label,  CONST_tabName_qyPhoneGuestTab  )  )  bSkipped  =  TRUE;
							  //
							  break;
						default:
								break;
				}
				//
				if  (  bSkipped  )  sqlCols[i].type  =  -2;		//  某些列要忽略
				else  {
					  memcpy(  &sqlCols[i],  &pQueryStruct->pSql[j],  sizeof(  sqlCols[i]  )  );
					  sqlCols[i].type  =  j;
				}
		  }
		  i  ++  ;
		  
		  if  (  !pT1  )  break;	//  表明最后一列
		  pT  =  pT1;		  
	 }
	 //
	 sqlCols[i].type  =  -1;	//  表明结尾
	 i  ++  ;

	 switch  (  uiType  )  {
			 case  CONST_pcCommType_pcProcessKnowledge:
	 			   if  (  moduleNameIndex  <  0  )  {		 
					   AfxMessageBox(  CString(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_needColumn  )  )  +  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_moKuaiMingChen  )  );
					   goto  errLabel;
	 			   }
				   if  (  cmdLineIndex  <  0  )  {
					   AfxMessageBox(  CString(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_needColumn  )  )  +  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_cmdLine  )  );
					   goto  errLabel;
				   }
				   break;
			 case  CONST_pcCommType_pcRegistryKnowledge:
				   if  (  iRootKeyIndex  <  0  ||  subKeyIndex  <  0  ||  cfgNameIndex  <  0  )  {
					   AfxMessageBox(  CString(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_needColumn  )  )  +  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_iRootKey  )  +  ","  +  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_subKey  )  +  ","  +  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_cfgName  )  );
					   goto  errLabel;
				   }
				   break;
			 case  CONST_imCommType_ipKnowledge:
				   if  (  startIpIndex  <  0  ||  endIpIndex  <  0  )  {
					   AfxMessageBox(  CString(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_needColumn  )  )  +  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_startIp  )  +  ","  +  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_endIp  )  );
					   goto  errLabel;
				   }
				   break;
			 case  CONST_imCommType_phoneGuest:
				   if  (  misServNameIndex  <  0  ||  uiDevTypeIndex  <  0  ||  wDevIdStrIndex  <  0  )  {
					   AfxMessageBox(  CString(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_needColumn  )  )  +  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_misServName  )  +  ","  +  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_uiDevType  )  +  ","  +  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_wDevIdStr  )  );
					   goto  errLabel;
				   }
				   break;
			 default:
					break;
	 }

 
	 unsigned  char  ucbFirst;
	 ucbFirst  =  FALSE;
	 insertColsStr  =  CString(  "insert into "  )  +  tabNameStr  +  "(";
	 for  (  j  =  0;  sqlCols[j].type  !=  -1;  j  ++  )  {
		  if  (  sqlCols[j].type  ==  -2  )  continue;
		  pT  =  _tcschr(  sqlCols[j].label,  _T(  '.'  )  );
		  pT  =  pT  ?  (  pT  +  1  )  :  sqlCols[j].label;
		  if  (  ucbFirst  )  insertColsStr  +=  CString(  _T(  ","  )  );
		  insertColsStr  +=  CString(  pT  );
		  ucbFirst  =  TRUE;
	 }
	 if  (  ucbAudited  )  insertColsStr  +=  CString(  ",auditTime"  );
	 insertColsStr  +=  CString(  _T(  ") values("  )  );

	 updateStr1  =  CString(  "update "  )  +  tabNameStr  +  " set ";

	 
	 for  (  j  =  0;  ;  j  ++  )  {
		  
		  if  (  !file.gets(  tBuf,  mycountof(  tBuf  )  )  )  break;

		  insertValsStr  =  CString(  ""  );
		  updateStr2  =  CString(  ""  );
		  moduleNameStr  =  CString(  ""  );
		  cmdLineStr  =  CString(  ""  );
		  ucbFirst  =  FALSE;
		  for  (  pT  =  tBuf,  i  =  0;  sqlCols[i].type  !=  -1;  i  ++  )  {
		  		 
			   if  (  pT  )  {
				   pT1  =  _tcschr(  pT,  _T(  '\t'  )  );
				   if  (  pT1  )  {  *pT1  =  0;  pT1  ++  ;  }
					}
			   else  {
				     pT  =  _T(  ""  );  pT1  =  NULL;
			   }
			   
			   filterStr2Display(  pT,  -1  );							//  这里过滤一下，免得有非法字符
			   if  (  lstrlen(  pT  )  >=  255  )  pT[255]  =  0;		//  确保字段长度不超过255个字符
			   

			   traceLogA(  "[%S]",  pT  );		  
			   
			   //  将数据内容由显示格式转换到可以存储的格式
			   if  (  sqlCols[i].type  !=  -2  )  {			//  -2, 表明要略过的列. 
				   if  (  ucbFirst  )  {
					   insertValsStr  +=  CString(  ","  );
					   updateStr2  +=  CString(  ","  );
				   }
				   //
				   switch  (  pQueryStruct->pDisplay[sqlCols[i].type].type  )  {
						   case  CONST_qyColumnDisplayType_bool:
							     str  =  CString(  pT  );
								 if  (  !_tcsicmp(  str,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_y  )  )
									 ||  !_tcsicmp(  str,  _T(  "y"  )  )
										||  !_tcsicmp(  str,  _T(  "yes"  )  )
											||  !_tcsicmp(  str,  _T(  "1"  )  )  )
								 {
									 pT  =  _T(  "1"  );
									 }
								 else  
									 pT  =  _T(  ""  );
							     break;
						   case  CONST_qyColumnDisplayType_pcCommType:
							     pT  =  _ltot(  qyGetTypeByDes(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_pcCommTypeTable  ),  pT  ),  tBuf1,  10  );
								 break;
						   case  CONST_qyColumnDisplayType_iRootKey:
							     pT  =  _ltot(  qyGetTypeByDes(  CONST_iRootKeyTable_abbr,  pT  ),  tBuf1,  10  );
								 break;
						   case  CONST_qyColumnDisplayType_ip12:  {
							     unsigned  long		ulIp			=	0;
								 char				ip12[12  +  1]	=	"";
							     buf[0]  =  0;
							     myTChar2Str(  pT,  buf,  mycountof(  buf  )  );
								 ulIp  =  inet_addr(  buf  );
								 ulIp2Str(  ulIp,  buf,  mycountof(  buf  )  );
								 qyStdToIp12(  buf,  ip12  );
								 myStr2TChar(  ip12,  tBuf1,  mycountof(  tBuf1  )  );
								 pT  =  tBuf1;							     
								 }
							     break;
						   case  CONST_qyColumnDisplayType_objType:
							     pT  =  _ltot(  qyGetTypeByDes(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  ),  pT  ),  tBuf1,  10  );
							     break;
						   default:
								   break;
				   }


				   //  记录几个键值
				   switch  (  uiType  )  {

						   case  CONST_pcCommType_pcProcessKnowledge:
				   			     if  (  i  ==  moduleNameIndex  )  {		//  对主键值，要trim  
									 tTrim(  pT  );		moduleNameStr  =  CString(  pT  );
			   					 }
								 if  (  i  ==  cmdLineIndex  )  {
									 tTrim(  pT  );		cmdLineStr  =  CString(  pT  );
								 }
								 break;
						   case  CONST_pcCommType_pcRegistryKnowledge:
							     if  (  i  ==  iRootKeyIndex  )  {
									 tTrim(  pT  );		iRootKeyStr  =  CString(  pT  );
									}
								 else  if  (  i  ==  subKeyIndex  )  {
										   tTrim(  pT  );		subKeyStr  =  CString(  pT  );
											}
								 else  if  (  i  ==  cfgNameIndex  )  {
								 		   tTrim(  pT  );		cfgNameStr  =  CString(  pT  );							
								 }								   								 
							     break;
						   case  CONST_imCommType_ipKnowledge:
							     if  (  i  ==  startIpIndex  )  {
								     tTrim(  pT  );  startIpStr  =  CString(  pT  );
									}
								 else  if  (  i  ==  endIpIndex  )  {
									       tTrim(  pT  );  endIpStr  =  CString(  pT  );
								 }
							     break;
						   case  CONST_imCommType_phoneGuest:
							     if  (  i  ==  misServNameIndex  )  {
									 tTrim(  pT  );  misServNameStr  =  CString(  pT  );
									}
								 else  if  (  i  ==  uiDevTypeIndex  )  {
										   tTrim(  pT  );  uiDevTypeStr  =  CString(  pT  );
										   }
								 else  if  (  i  ==  wDevIdStrIndex  )  {
										   tTrim(  pT  );  wDevIdStr  =  CString(  pT  );
								 }
							     break;
						   default:
									break;
				   }


				   //
				   if  (  sqlCols[i].iDataType  ==  SQL_INTEGER  )  {
					   TCHAR	tBuf1[256];  TCHAR  *  pStop;
					   _sntprintf(  tBuf1,  mycountof(  tBuf1  ),  _T(  "%d"  ),  _tcstol(  pT,  &pStop,  10  )  );
					   str  =  CString(  ""  )  +  tBuf1;
						}
				   else  {
					     str  =  CString(  "'"  )  +  pT  +  CString(  "'"  );
				   }
				   insertValsStr  +=  str;
				   //
				   pT  =  _tcschr(  sqlCols[i].label,  _T(  '.'  )  );
				   pT  =  pT  ?  (  pT  +  1  )  :  sqlCols[i].label;
				   updateStr2  +=  CString(  ""  )  +  pT  +  "="  +  str;
				   //
				   ucbFirst  =  TRUE;
			   }

			   //  OutputDebugString(  insertValsStr  );
			   //  OutputDebugString(  _T(  "\n"  )  );
			   //  OutputDebugString(  updateStr2  );
			   //  OutputDebugString(  _T(  "\n"  )  );
			   
			   pT  =  pT1;		  
		  }
		  if  (  ucbAudited  )  insertValsStr  +=  CString(  ",'"  )  +  timeBuf  +  CString(  "'"  );
		  insertValsStr  +=  CString(  ")"  );
		  if  (  ucbAudited  )  updateStr2  +=  CString(  ",auditTime="  )  +  CString(  "'"  )  +  timeBuf  +  CString(  "'"  );

		  //
		  unsigned  char				ucbRcdExists;
		  char							auditTime[CONST_qyTimeLen  +  1];
		  //
		  ucbRcdExists  =  FALSE;
		  auditTime[0]  =  0;

		  switch  (  uiType  )  {
				  case  CONST_pcCommType_pcProcessKnowledge:  {
					    QY_PCMODULEKNOWLEDGE_RCD		rcd;
						//
						if  (  !moduleNameStr.GetLength(  )  )  continue;	//  主键值不能为空
						//
						updateStr2  +=  CString(  " where fileName='"  )  +  moduleNameStr  +  "' and cmdLine='"  +  cmdLineStr  +  "'";
						//						
						if  (  bGetPcModuleKnowledgeBySth(  pQyMc->gui.pDb,  pQyMc->cfg.db.iDbType,  moduleNameStr,  cmdLineStr,  0,  &rcd  )  )  {
							safeStrnCpy(  rcd.auditTime,  auditTime,  sizeof(  auditTime  )  );
							ucbRcdExists  =  TRUE;
						}
						//
						}
					  	break;
				  case  CONST_pcCommType_pcRegistryKnowledge:  {
					    QY_PCREGISTRYKNOWLEDGE_RCD		rcd;
						//
						if  (  !iRootKeyStr.GetLength(  )  ||  !subKeyStr.GetLength(  )  )  continue;
						//
						updateStr2  +=  CString(  " where iRootKey="  )  +  iRootKeyStr  +  " and subKey='"  +  subKeyStr  +  "' and cfgName='"  +  cfgNameStr  +  "'";
						//
						if  (  bGetPcRegistryKnowledgeBySth(  pQyMc->gui.pDb,  pQyMc->cfg.db.iDbType,  _tcstol(  iRootKeyStr,  &pStop,  10  ),  subKeyStr,  cfgNameStr,  0,  &rcd  )  )  {
							safeStrnCpy(  rcd.auditTime,  auditTime,  sizeof(  auditTime  )  );
							ucbRcdExists  =  TRUE;
						}
						//
						}
					    break;
				  case  CONST_imCommType_ipKnowledge:  {
					    if  (  !startIpStr.GetLength(  )  ||  !endIpStr.GetLength(  )  )  continue;
						if  (  !lstrcmpi(  endIpStr,  _T(  "000000000000"  )  )  )  continue;
						//
						updateStr2  +=  CString(  " where startIp='"  )  +  startIpStr  +  "' and endIp='"  +  endIpStr  +  "'";
						//
						_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(*) from %s where startIp='%s' and endIp='%s'"  ),  CONST_tabName_qyIpKnowledgeTab,  CString(  startIpStr  ),  CString(  endIpStr  )  );
						if  (  bSqlObjExists(  pQyMc->gui.pDb,  sqlBuf  )  )  ucbRcdExists  =  TRUE;
					    
						}
					    break;
				  case  CONST_imCommType_phoneGuest:  {
					    unsigned  int  uiDevType  =  0;
						//
					    if  (  !uiDevTypeStr.GetLength(  )  )  continue;
					    if  (  !wDevIdStr.GetLength(  )  )  continue;
						if  (  !(  uiDevType  =  _ttol(  uiDevTypeStr  )  )  )  continue;
						//
						//  如果qyPhoneGuestTab中已经有了，就不要再处理了
						if  (  bGetPhoneGuestRcdBySth(  pQyMc->gui.pDb,  iDbType,  misServNameStr,  uiDevType,  wDevIdStr,  0,  NULL  )  )  continue;
						//
						//  没有就先将记录存入qyPhoneGuestTab中, 
						_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into %s(misServName,uiDevType,wDevIdStr,iStatus,startTime,tLastModifiedTime) values(%s,%d,%s,0,'%s','%s')"  ),  CONST_tabName_qyPhoneGuestTab,  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServNameStr  ),  uiDevType,  getDbValStr(  iDbType,  CONST_iDataType_wDevIdStr,  wDevIdStr  ),  CString(  timeBuf  ),  CString(  timeBuf  )  );
						if  (  !bQyExecSql(  pQyMc->gui.pDb,  sqlBuf  )  )  continue;
						//
						updateStr2  +=  CString(  " where misServName="  )  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServNameStr  )  +  " and uiDevType="  +  uiDevTypeStr  +  " and wDevIdStr="  +  getDbValStr(  iDbType,  CONST_iDataType_wDevIdStr,  wDevIdStr  );
						//
						_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(*) from %s where misServName=%s and uiDevType=%d and wDevIdStr=%s"  ),  CONST_tabName_qyImOtherRegInfoTab,  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServNameStr  ),  uiDevType,  getDbValStr(  iDbType,  CONST_iDataType_wDevIdStr,  wDevIdStr  )  );
						if  (  bSqlObjExists(  pQyMc->gui.pDb,  sqlBuf  )  )  ucbRcdExists  =  TRUE;
						}
					    break;
				  default:
						  break;

		  }

		  if  (  ucbRcdExists  )  {
			  if  (  !ucbAudited  &&  strlen(  auditTime  )  ==  CONST_qyTimeLen  )  continue;
			  str  =  updateStr1  +  updateStr2;
				}
		  else  {
			    str  =  insertColsStr  +  insertValsStr;
		  }

		  /*
		  AfxMessageBox(  str  );
		  if  (  j  ==  14  )  {
			  traceLogA(  "here"  );
		  }
		  */

		  if  (  !bQyExecSql(  pQyMc->gui.pDb,  str  )  )  {
			  traceLogA(  "sql[%d] failed: [%S]",  j,  str  );
		  }

		  if  (  !(  j  %  20  )  )  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  ""  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_importRecords  ),  _T(  " %d "  ),  j,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_countOfRecords  )  ); 


	 }

	 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  ""  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_importFinished  ),  _T(  ""  )  ); 

	}

	 bRet  =  TRUE;

errLabel:
	 
	 if  (  bFileOpen  )  file.Close(  );

	 return  bRet;
}

 void  doMainFrameExportSth(  BOOL  bProcCurQueryOnly  );

 BOOL  bExportKnowledge(  unsigned  int  uiType  )
{
	 BOOL							bRet		=		FALSE;
	 unsigned  char					ucbAudited  =		FALSE;
	 CDlgModuleKnowlegeOptions		dlg;
	 CString						sqlStr;
	 QY_MC						*	pQyMc		=		QY_GET_GBUF(  );
	 

	 switch  (  uiType  )  {
			 case  CONST_pcCommType_pcProcessKnowledge:
				   //
				   if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;
				   ucbAudited  =  dlg.m_var.ucbAudited;
				   //
				   if  (  !bNetMcCfgPcProcessKnowledge(  pQyMc,ucbAudited  ?  _T(  " auditTime is not null and auditTime<>''"  )  :  _T(  " auditTime is null or auditTime=''"  )  )  )  goto  errLabel;
				   break;
			 case  CONST_pcCommType_pcRegistryKnowledge:
				   dlg.bSetDlgInfo(  0,  getResStr(  0, &pQyMc->cusRes,  CONST_resId_unAudited_pcRegistry  ),   getResStr(  0, &pQyMc->cusRes,  CONST_resId_audited_pcRegistry  )  );   
				   //
				   if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;
				   ucbAudited  =  dlg.m_var.ucbAudited;
				   //
				   if  (  !bNetMcCfgPcRegistryKnowledge(  pQyMc,  ucbAudited  ?  _T(  " auditTime is not null and auditTime<>''"  )  :  _T(  " auditTime is null or auditTime=''"  )  )  )  goto  errLabel;
				   break;
			 case  CONST_imCommType_ipKnowledge:
				   if  (  !bViewIpKnowledgeList(  pQyMc,getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  ),  _T(  ""  ),  _T(  ""  )  )  )  goto  errLabel;
				   break;
			 case  CONST_imCommType_phoneGuest:
				   if  (  !bViewPhoneGuestList(  pQyMc,getProcedObjDb(  pQyMc,  0,  pQyMc->iDsnIndex_mainSys  ),  _T(  ""  ),  _T(  ""  )  )  )  goto  errLabel;
				   break;
			 default:
					goto  errLabel;
	 }

	 
	 doMainFrameExportSth(  TRUE  );

	 
	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}



 BOOL  bClearupKnowledge(  unsigned  int  uiType  )
{
	 BOOL							bRet		=		FALSE;
	 unsigned  char					ucbAudited  =		FALSE;
	 CDlgModuleKnowlegeOptions		dlg;
	 CString						sqlStr;
	 QY_MC						*	pQyMc		=		QY_GET_GBUF(  );
	 CString						tabNameStr;
	 CString						whereStr;

	 switch  (  uiType  )  {
			 case  CONST_pcCommType_pcProcessKnowledge:
				   tabNameStr  =  CString(  "qyPcProcessKnowledgeTab"  );
				   //
				   if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;
				   //
				   ucbAudited  =  dlg.m_var.ucbAudited;
				   //
				   if  (  AfxMessageBox(  ucbAudited  ?  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_clearupAuditedKnowledge  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_clearupUnAuditedKnowledge  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  ) goto  errLabel;
				   if  (  !ucbAudited  )  sqlStr  =  CString(  "delete from "  )  +  tabNameStr  +  CString(  " where auditTime is null or auditTime=''"  );
				   else  sqlStr  =  CString(  "delete from "  )  +  tabNameStr  +  CString(  " where auditTime is not null and auditTime <>''"  );
				   //
				   if  (  !bQyExecSql(  pQyMc->gui.pDb,  sqlStr  )  )  goto  errLabel;
				   //
				   break;
			 case  CONST_pcCommType_pcRegistryKnowledge:
				   tabNameStr  =  CString(  "qyPcRegistryKnowledgeTab"  );
				   //
				   dlg.bSetDlgInfo(  0,  getResStr(  0, &pQyMc->cusRes,  CONST_resId_unAudited_pcRegistry  ),   getResStr(  0, &pQyMc->cusRes,  CONST_resId_audited_pcRegistry  )  );   
				   if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;
				   //
				   ucbAudited  =  dlg.m_var.ucbAudited;
				   //
				   if  (  AfxMessageBox(  ucbAudited  ?  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_clearupAuditedKnowledge  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_clearupUnAuditedKnowledge  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  ) goto  errLabel;
				   if  (  !ucbAudited  )  sqlStr  =  CString(  "delete from "  )  +  tabNameStr  +  CString(  " where auditTime is null or auditTime=''"  );
				   else  sqlStr  =  CString(  "delete from "  )  +  tabNameStr  +  CString(  " where auditTime is not null and auditTime <>''"  );
				   //
				   if  (  !bQyExecSql(  pQyMc->gui.pDb,  sqlStr  )  )  goto  errLabel;
				   //
				   break;
			 case  CONST_imCommType_ipKnowledge:
				   tabNameStr  =  CString(  CONST_tabName_qyIpKnowledgeTab  );
				   //
				   if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_clearupKnowledge  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  ) goto  errLabel;
				   sqlStr  =  CString(  "delete from "  )  +  tabNameStr;				   
				   //
				   if  (  !bQyExecSql(  pQyMc->gui.pDb,  sqlStr  )  )  goto  errLabel;
				   //
				   break;
			 case  CONST_imCommType_phoneGuest:
				   if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_clearupPhoneBook  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
				   //
				   tabNameStr  =  CString(  CONST_tabName_qyImOtherRegInfoTab  );
				   sqlStr  =  CString(  "delete from "  )  +  tabNameStr;
				   if  (  !bQyExecSql(  pQyMc->gui.pDb,  sqlStr  )  )  goto  errLabel;
				   //
				   tabNameStr  =  CString(  CONST_tabName_qyPhoneGuestTab  );
				   sqlStr  =  CString(  "delete from "  )  +  tabNameStr;
				   if  (  !bQyExecSql(  pQyMc->gui.pDb,  sqlStr  )  )  goto  errLabel;
				   //
				   break;
			 default:
					goto  errLabel;
	 }

	 bRet  =  TRUE;
errLabel:
	 return  bRet;
 }
