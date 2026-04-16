// QyFile.cpp: implementation of the CQyFile class.
//
//////////////////////////////////////////////////////////////////////

#include	"stdafx.h"
#include	"qyCommon.h"
#include	"qyCommProc.h"
#include	"qyCommCommon.h"
#include	"qyWmComm.h"
#include	"qnmCommProc.h"
#include	"qyString.h"
#include	"qyDbcommon.h"
#include	"QyFile.h"
#include	"qyTCharCommProc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

 CQyFile::CQyFile()
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

 CQyFile::~CQyFile()
{

}


 void  CQyFile::writeEndLine(  )
{
	 Write(  "\r\n",  2  );	 
}

 char	*	CQyFile::gets(  char  *  string,  unsigned  int  n  )
{
	 char		*	p	=	string;

	 if  (  !n  )  return  NULL;
	 if  (  n  ==  1  )  {
		 p[0]  =  0;  return  string;
	 }
	 if  (  1  !=  Read(  p,  1  )  )  return  NULL;
	 p  ++  ;
	 for  (  ;  n  -  2;  n  --,  p  ++  )  {
		  if  (  1  !=  this->Read(  p,  1  )  )  break;
		  if  (  !p[0]  ||  p[0]  ==  '\n'  )  {
			  p  ++  ;
			  break;
		  }
	 }
	 *p  =  0;
	 return  string;
}

 WCHAR	*	CQyFile::gets(  WCHAR  *  string,  unsigned  int  n  )	//  2006/04/30
{
	 WCHAR		*	p	=	string;

	 if  (  !n  )  return  NULL;
	 if  (  n  ==  1  )  {
		 p[0]  =  0;  return  string;
	 }
	 if  (  sizeof(  WCHAR  )  !=  Read(  p,  sizeof(  WCHAR  )  )  )  return  NULL;
	 p  ++  ;
	 for  (  ;  n  -  2;  n  --,  p  ++  )  {
		  if  (  sizeof(  WCHAR  )  !=  this->Read(  p,  sizeof(  WCHAR  )  )  )  break;
		  if  (  !p[0]  ||  p[0]  ==  _T(  '\n'  )  )  {
			  p  ++  ;
			  break;
		  }
	 }
	 *p  =  0;

	 return  string;
}

 //  定位目标
 BOOL  CQyFile::bFindObj(  char  *  objName,  char  *  objContent  )
{
	 BOOL		bRet							=	FALSE;
	 char		buf[CONST_maxQyFileLineLen];
	 CString	str								=	CString(  objName  )  +  _T(  "="  )  +  CString(  objContent  );

	 SeekToBegin(  );
	 while  (  gets(  buf,  sizeof(  buf  )  )  )  {
			if  (  !buf[0]  )  goto  errLabel;
			if  (  buf[strlen(  buf  )  -  1]  !=  '\n'  )  continue;
			trim(  buf  );
			if  (  str  ==  buf  )  {
				bRet  =  TRUE;
				break;
			}
	 }
	 
errLabel:
	 return  bRet;
}


 BOOL  CQyFile::bGetObjData(  char  *  objName,  char  *  data,  unsigned  int  size  )
{
	 BOOL			bRet							=	FALSE;
	 char			buf[CONST_maxQyFileLineLen];
	 unsigned  int	objNameLen						=	strlen(  objName  );

	 if  (  !objName  ||  !objName[0]  ||  !data  ||  !size  )  goto  errLabel;

	 SeekToBegin(  );
	 while  (  gets(  buf,  sizeof(  buf  )  )  )  {
			if  (  !buf[0]  )  goto  errLabel;
			if  (  buf[strlen(  buf  )  -  1]  !=  '\n'  )  continue;
			trim(  buf  );
			if  (  _strnicmp(  objName,  buf,  objNameLen  )  )  continue;
			if  (  buf[objNameLen]  !=  '='  )  continue;
			_snprintf(  data,  size,  "%s",  buf  +  objNameLen  +  1  );
			break;
	 }
	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}


 BOOL  CQyFile::bGetNextLine(  char  *  objName,  unsigned  int  objNameSize,  char  *  data,  unsigned  int  size  )
{
	 BOOL			bRet							=	FALSE;
	 char			buf[CONST_maxQyFileLineLen];
	 char		*	p								=	NULL;


	 if  (  !objName  ||  !objNameSize  ||  !data  ||  !size  )  goto  errLabel;

	 if  (  !gets(  buf,  sizeof(  buf  )  )  )  goto  errLabel;
	 if  (  buf[strlen(  buf  )  -  1]  !=  '\n'  )  goto  errLabel;
	 trim(  buf  );
	 p  =  strchr(  buf,  '='  );
	 if  (  !p  )  {
		 safeStrnCpy(  buf,  objName,  objNameSize  );
		 bRet  =  TRUE;  goto  errLabel;
	 }
	 *p  =  0;
	 trim(  buf  );
	 safeStrnCpy(  buf,  objName,  objNameSize  );

	 p  ++  ;
	 trim(  p  );
	 safeStrnCpy(  p,  data,  size  );
	
	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}



 BOOL  CQyFile::bExportCls(  char  *  clsName  )
{
	 return  bExportData(  "[%s]\r\n",  clsName  );
}

 BOOL  CQyFile::bExportObj(  char  *  objName  )
{
	 return  bExportData(  "%s\r\n",  objName  ?  objName  :  ""  );
}

 BOOL  CQyFile::bExportObj(  char  *  objName,  int  iObjContent  )
{
	 return  bExportData(  "%s=%d\r\n",  objName  ?  objName  :  "",  iObjContent  );
}

 BOOL  CQyFile::bExportObj(  char  *  objName,  char  *  objContent  )
{
	 return  bExportData(  "%s=%s\r\n",  objName  ?  objName  :  "",  objContent  ?  objContent  :  ""  );

}

 BOOL  CQyFile::bExportData(  char  *  fmt,  ...  )
{
	 BOOL				bRet		=	FALSE;
	 va_list			args;
	 char				buf[CONST_maxQyFileLineLen  +  1];

	 va_start(  args,  fmt  );
	 _vsnprintf(  buf, sizeof(  buf  ),  fmt,  args  );
	 
	 Write(  buf,  strlen(  buf  )  );
	 
	 bRet  =  TRUE;

//  errLabel:

	 va_end(  args  );

	 return  bRet;

}


 BOOL  CQyFile::bImportSqlTable(  void  *  pDb,  int  iDbType,  char  *  tableName,  char  *  colsStr,  unsigned  char  ucbUtf8  )
{
	//  2013/02/20
	if  (  iDbType  ==  CONST_dbType_myDb  )  {
#ifdef  __DEBUG__
		traceLog(  _T(  "CQyFile::bImportSqlTable is not supported in myDb"  )  );
#endif
		return  FALSE;
	}

#ifdef  __WINCE__
	return  FALSE;
#else
	 BOOL				bRet		=	FALSE;
	 CString			sqlStr;
	 CString			valsStr,  realColsStr;
	 CRecordset			rs(  (  CDatabase  *  )pDb  );
	 CODBCFieldInfo		fieldInfos[CONST_qyMaxExportCols];
	 int				nFields;
	 int				i;
	 char				buf[CONST_maxQyFileLineLen  +  1];
	 char			*	p,  *  pComma;
	 char				colBuf[CONST_maxQyFileLineLen  +  1];
	 TCHAR				tColBuf[CONST_maxQyFileLineLen  +  1];
	 TCHAR				tBuf[CONST_maxQyFileLineLen  +  1];
	 unsigned  int		len;
	 unsigned  int		len_objEnd							=	strlen(  CONST_qyFileObj_end  );
	 unsigned  int		len_replaceStr_singleQuatotation	=	strlen(  CONST_replaceStr_singleQuatotation  );
	 unsigned  int		len_replaceStr_comma				=	strlen(  CONST_replaceStr_comma  );
	 unsigned  int		len_replaceStr_newLine				=	strlen(  CONST_replaceStr_newLine  );


	 try  {
		  sqlStr  =  CString(  "select "  )  +  CString(  colsStr  )  +  CString(  " from "  )  +  CString(  tableName  );
		  if  (  !rs.Open(  CRecordset::forwardOnly,  sqlStr  )  )  goto  errLabel;
		  nFields  =  rs.GetODBCFieldCount(  );
		  if  (  nFields  >  CONST_qyMaxExportCols  )  goto  errLabel;
		  for  (  i  =  0;  i  <  nFields;  i  ++  )  rs.GetODBCFieldInfo(  i,  fieldInfos[i]  );
		  rs.Close(  );

		  if  (  !bFindObj(  CONST_qyFileObj_name,  tableName  )  )  goto  errLabel;

		  traceLogA(  "现在开始导入%s",  tableName  );
		  traceLogA(  ""  );

		  while  (  gets(  buf,  sizeof(  buf  )  )  )  {
				 //  trim(  buf  );		//  2006/04/25, 为了防止把一些值为空的数据给漏掉了，不能采用trim的办法。只能要求用户不能修改数据
				 if  (  !strnicmp(  buf,  CONST_qyFileObj_end,  len_objEnd  )  )  {
					 traceLogA(  "导入%s结束",  tableName  );  break;
				 }
			
				 p  =  buf;
				 valsStr  =  realColsStr  =  CString(  ""  );
				 for  (  i  =  0;  i  <  nFields;  i  ++,  p  =  pComma  +  1  )  {
					  pComma  =  strstr(  p,  ","  );
					  if  (  !pComma  )  break;
					  *pComma  =  0;
					  tColBuf[0]  =  0;
					  colBuf[0]  =  0;  len  =  0;
					  switch  (  fieldInfos[i].m_nSQLType  )  {
							  case  SQL_CHAR:
							  case  SQL_VARCHAR:
							  case  SQL_WCHAR:
							  case  SQL_WVARCHAR:
								    //  colBuf[0]  =  '\'';  len  =  1;
								    for  (  ;  *p;  )  {
										if  (  !strncmp(  p,  CONST_replaceStr_singleQuatotation,  len_replaceStr_singleQuatotation  )  )   {		//  2006/04/25
											colBuf[len]  =  '\'';  len  ++  ;
											colBuf[len]  =  '\'';  len  ++  ;
											p  +=  len_replaceStr_singleQuatotation;  continue;
										}
										if  (  !strncmp(  p,  CONST_replaceStr_comma,  len_replaceStr_comma  )  )  {
											colBuf[len]  =  ',';  len  ++  ;  p  +=  len_replaceStr_comma;  continue;
										}
										if  (  !strncmp(  p,  CONST_replaceStr_newLine,  len_replaceStr_newLine  )  )  {
											colBuf[len]  =  '\n';  len  ++  ;  p  +=  len_replaceStr_newLine;  continue;
										}
										colBuf[len]  =  *p;  len  ++  ;  p  ++  ;
									}
									//  colBuf[len]  =  '\'';  len  ++  ;
									colBuf[len]  =  0;
									//
									tBuf[0]  =  0;
									if  (  ucbUtf8  )  myUtf82TChar(  colBuf,  tBuf,  mycountof(  tBuf  )  );
									else  myStr2TChar(  colBuf,  tBuf,  mycountof(  tBuf  )  );
									//
									lstrcpyn(  tColBuf,  getDbValStr(  iDbType,  fieldInfos[i].m_nSQLType,  tBuf  ),  mycountof(  tColBuf  ) );
									break;
							  case  SQL_INTEGER:
							  case  SQL_SMALLINT:
								    if  (  !p[0]  )  {
										continue;	//  当数值为空时，应在insert语句中略去
									}
								    _snprintf(  colBuf,  sizeof(  colBuf  ),  "%s",  p  );
									if  (  ucbUtf8  )  myUtf82TChar(  colBuf,  tColBuf,  mycountof(  tColBuf  )  );
									else  myStr2TChar(  colBuf,  tColBuf,  mycountof(  tColBuf  )  );
									break;
							  default:
									  MACRO_qyAssert(  0,  _T(  "dataType err"  )  );
									  traceLogA(  "dataType err"  );
									  //
									  goto  errLabel;
					  }
					  if  (  i  )  {	//  2006/04/25, 为了避免(col0,)的现象，必须在新加入一项时加这个分隔符
					      valsStr  +=  ",";  realColsStr  +=  ",";
					  }
					  valsStr  +=  tColBuf;  realColsStr  +=  fieldInfos[i].m_strName;
					  //  if  (  i  !=  nFields  -  1  )  {
					  //	  valsStr  +=  ",";  realColsStr  +=  ",";
					  // }
				 }

				 sqlStr  =  CString(  "insert into "  )  +  CString(  tableName  )  +  CString(  " ("  )  +  CString(  realColsStr  )  +  CString(  ")"  )
					+  CString(  " Values("  )  +  valsStr  +  CString(  ")"  );
				 traceLogA(  "sqlStr is %S",  sqlStr.GetBuffer(  0  )  );

				 bQyExecSql(  pDb,  sqlStr.GetBuffer(  0  )  );

		  }

		}
	 catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CQyFile::bImportSqlTable failed."  )  );
		   goto  errLabel;
	 }


	 bRet  =  TRUE;

errLabel:

	 if  (  rs.IsOpen(  )  )  rs.Close(  );

	 return  bRet;
#endif
}
		
 BOOL  CQyFile::bExportSqlQuery(  void  *  pDb,  int  iDbType,  char  *  objName,  char  *  sqlStr  )
{
	//  2013/02/22
	if  (  iDbType  ==  CONST_dbType_myDb  )  return  FALSE;

#ifdef  __WINCE__
	return FALSE;
#else
	 BOOL				bRet								=	FALSE;
	 CRecordset			rs(  (  CDatabase  *  )pDb  );
	 CODBCFieldInfo		fieldInfos[CONST_qyMaxExportCols];
	 CDBVariant			varVals[CONST_qyMaxExportCols];
	 int				nFields;
	 int				i;
	 char				buf[CONST_maxQyFileLineLen  +  1]	=	"";
	 char			*	p									=	NULL;
	 unsigned  int		len;
	 unsigned  int		nWritten							=	0;
	 char				tmpBuf[1024];
	 TCHAR				tBuf[1024];
	 
	 try  {

		  bExportObj(  CONST_qyFileObj_name,  objName  );

		  traceLogA(  "现在开始导出%s",  objName  );
		  traceLogA(  ""  );

		  OutputDebugString(  CQyString(  sqlStr  )  +  "\n"  );
  		  if  (  rs.Open(  CRecordset::forwardOnly,  CString(  sqlStr  ).GetBuffer(  0  )  )  )  {
		
			  nFields  =  rs.GetODBCFieldCount(  );
			  if  (  nFields  >  CONST_qyMaxExportCols  )  {
				  MACRO_qyAssert(  0,  _T(  "field content too long"  )  );  
				  goto  errLabel;
			  }
			  for  (  i  =  0;  i  <  nFields;  i  ++  )  rs.GetODBCFieldInfo(  i,  fieldInfos[i]  );
				   
			  //  for  (  i  =  0;  i  <  nFields;  i  ++  )  traceLogA(  "fieldInfos[%d] %s, m_nSQLType is %d",  i,  fieldInfos[i].m_strName,  fieldInfos[i].m_nSQLType  );
						
			  for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {
					    
				   for  (  i  =  0;  i  <  nFields;  i  ++  )  {
						rs.GetFieldValue(  i,  varVals[i]  );
						switch  (  fieldInfos[i].m_nSQLType  )  {
								case  SQL_CHAR:
								case  SQL_VARCHAR:
								case  SQL_WCHAR:
								case  SQL_WVARCHAR:								
									  MACRO_sqlRawStr(  varVals[i],  tBuf,  mycountof(  tBuf  )  );		//  2006/04/25
									  if  (  !tBuf[0]  )  {
										    bExportData(  ","  );  break;
									  }
									  
									  len  =  0;
									  //  myTChar2Str(  tBuf,  tmpBuf,  sizeof(  tmpBuf  )  );
									  myTChar2Utf8(  tBuf,  tmpBuf,  sizeof(  tmpBuf  )  );
									  for  (  p  =  tmpBuf;  *p;  p  ++  )  {
										   switch  (  *p  )  {
												   case  '\'':
															 //  MACRO_qyAssert(  0,  "导出格式中有符号\'"  );
															 nWritten  =  _snprintf(  buf  +  len,  sizeof(  buf  )  -  len,  "%s",  CONST_replaceStr_singleQuatotation  );
															 if  (  nWritten  <=  0  )  break;
															 len  +=  nWritten;
															 break;
												   case  '\n':
															 nWritten  =  _snprintf(  buf  +  len,  sizeof(  buf  )  -  len,  "%s",  CONST_replaceStr_newLine  );
															 if  (  nWritten  <=  0  )  break;
															 len  +=  nWritten;
															 break;
												   case  ',':
															 nWritten  =  _snprintf(  buf  +  len,  sizeof(  buf  )  -  len,  "%s",  CONST_replaceStr_comma  );
															 if  (  nWritten  <=  0  )  break;
															 len  +=  nWritten;
															 break;
												   default:
													       if  (  sizeof(  buf  )  -  len  <=  1  )  break;
														   buf[len]  =  *p;  len  ++  ;
														   break;
										   }										   
									  } 
									  buf[len]  =  0;
									  bExportData(  "%s,",  buf  );	 									  
									  break;
								case  SQL_INTEGER:
									  if  (  varVals[i].m_dwType  ==  DBVT_LONG  )  bExportData(  "%d,",  varVals[i].m_lVal  );
									  else  {
											 MACRO_qyAssert(  varVals[i].m_dwType  ==  DBVT_NULL,  _T(  "m_nSQLType错误"  )  );
											 bExportData(  ","  );
									   }
									   break;
								case  SQL_SMALLINT:
									  if  (  varVals[i].m_dwType  ==  DBVT_SHORT  )  bExportData(  "%d,",  varVals[i].m_iVal  );
									  else  {
									  		 MACRO_qyAssert(  varVals[i].m_dwType  ==  DBVT_NULL,  _T(  "m_nSQLType错误"  )  );
											 bExportData(  ","  );
									  }
									  break;
								default:
									    traceLogA(  "fieldInfos[%d] %s, m_nSQLType is %d",  i,  fieldInfos[i].m_strName,  fieldInfos[i].m_nSQLType  );
										MACRO_qyAssert(  0,  _T(  "dataType not ok"  )  );
										bExportData(  ","  );
										break;
							}					  
						
						}
						writeEndLine(  );
				   }
			   }
			   if  (  rs.IsOpen(  )  )  rs.Close(  );
			   bExportObj(  CONST_qyFileObj_end  );

		}
	 catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CQyFile::bExportSqlQuery failed."  )  );
		   goto  errLabel;
	 }

	 bRet  =  TRUE;

errLabel:

	 if  (  rs.IsOpen(  )  )  rs.Close(  );

	 return  bRet;
#endif
}

