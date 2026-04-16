
#ifndef  __QYDEFS_H__
#define  __QYDEFS_H__	/*  {  */

// 此文件包含不常变化的常量参数，可以配置的可变化的在"qyCfg.h"里

//
#include	"qyDefs_open.h"



//
#define		FF_FILE_HANDLE											( HANDLE )0xffffffff

#define		CONST_qyCfgName_ntRunKey								"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"
#define		CONST_qyCfgName_98RunKey								"Software\\Microsoft\\Windows\\CurrentVersion\\RunServices"
#define		CONST_qyCfgName_runOnceKey								"Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce"



#ifdef  MAX_PATH
	#define		CONST_qyMaxPathLen										MAX_PATH
#else 
	#define		CONST_qyMaxPathLen										_MAX_PATH
#endif
#define		QY_MAXPATHLEN											CONST_qyMaxPathLen

#define		CONST_qyMacLen											12
#define		CONST_qyMaxIpLen										15

#define		QY_MACLEN												CONST_qyMacLen
#define		CONST_qnmMaxMacs										3
#define		QY_MAXIPLEN												CONST_qyMaxIpLen
#define		QY_MCIPLEN												12
#define		QY_TIMELEN												14
#define		QY_DATELEN												8
#define		CONST_qyMaxKeyLen										255
#define		QY_MAXKEYLEN											CONST_qyMaxKeyLen

#define		CONST_qyMaxPreDocNameLen								32
#define		CONST_qyMaxDocNameLen									128
#define		CONST_qyMaxPostDocNameLen								64


#define		CONST_maxSqlClauseLen									2048
#define		CONST_qyMaxSqlClauseLen									CONST_maxSqlClauseLen
#define		CONST_maxSqlBufLen										4096
#define		CONST_qyMaxSqlBufLen									CONST_maxSqlBufLen
#define		MAX_SQLBUFLEN											CONST_qyMaxSqlBufLen
#define		QY_SQLBUFLEN											CONST_qyMaxSqlBufLen
#define		QY_MAXSQLBUFLEN											CONST_qyMaxSqlBufLen
#define		MAX_SQLCLAUSELEN										CONST_qyMaxSqlClauseLen
#define		QY_MAXSQLCLAUSELEN										CONST_qyMaxSqlClauseLen
#define		QY_SQLCLAUSEBUFLEN										CONST_qyMaxSqlClauseLen
#define		CONST_qyColumnNameLen									256


#define		CONST_qySnSize											128




/////////////////
//

#define		CONST_qyDbOpenOptions									(  CDatabase::useCursorLib  |  CDatabase::noOdbcDialog  )


#define		QY_MAXCOLS												128		//  40

			// 将字符串安全拷入缓存中
#define		MACRO_safeStrMemCpy(  strIn,  mem,  size  )				{  memcpy(  (  mem  ),  (  strIn  ), min( strlen(  (  strIn  )  ),  (  size  )  )  );  } 

#define		MACRO_szBuf(  buf  )									if  (  sizeof(  buf  )  )  {  (  (  buf  )[sizeof(  buf  )  -  1]  )  =  0;  };


#define		MACRO_CStringTrim( x )									{  (  x  ).TrimLeft(  );  (  x  ).TrimRight(  );  }
#define		MACRO_GetDlgItemText(  idc,  buf  )						{  GetDlgItemText(  (  idc  ),  (  buf  ),  sizeof(  buf  )  );  trim(  buf  );  }
#define		MACRO_chkNotNull(  idc,  buf,  hint  )					{  if  (  !buf[0]  )  {															\
																			MessageBeep(  -1  );													\
																			if  (  hint  &&  hint[0]  )  qyShowHint(  hint  );						\
																			GetDlgItem( idc )->SetFocus(  );										\
																			return;																	\
																			}																		\
																	}
#define		MACRO_chkFixedLen(  idc,  buf,  len,  hint  )			{  if  (  (  (  int  )strlen(  buf  )  )  !=  (  len  )  )  {					\
																			if  (  hint  &&  (  hint  )[0]  )  qyShowHint(  hint  );				\
																			GetDlgItem( idc )->SetFocus(  );										\
																			return;																	\
																			}																		\
																	}
#define		MACRO_insertHint(  bHint,  objName  )					{	if  (  bHint  )  {															\
																			char	hintBuf[256],	*fmt  =  "是否将添加%s?";						\
																			int		len  =  strlen(  fmt  );										\
																																					\
																			if  (  strlen(  objName  )  +  len  >=  sizeof(  hintBuf  )  )  return;	\
																			sprintf(  hintBuf,  fmt,  objName  );									\
																			if  (  IDOK  !=  AfxMessageBox( hintBuf,  MB_OKCANCEL  )  )  return;	\
																		}																			\
																	}
#define		MACRO_updateHint(  objName  )							{	char	hintBuf[256],  *fmt  =  "是否保存对%s的修改?";						\
																		int		len  =  strlen(  fmt  );											\
																																					\
																		if  (  strlen(  objName  ) +  len  >=  sizeof(  hintBuf  )  )  return;		\
																		sprintf(  hintBuf,  fmt,  objName   );										\
																		if  (  IDOK  !=  AfxMessageBox( hintBuf,  MB_OKCANCEL  )  )  return;		\
																																					\
																	}
#define		MACRO_deleteHint(  objName  )							{	char	hintBuf[256],	*fmt  =  "是否删除%s?";								\
																		int		len		=	strlen(  fmt  );										\
																																					\
																		if  (  strlen(  objName  )  +  len  >=  sizeof(  hintBuf  )  )  return;		\
																		sprintf(  hintBuf,  fmt,  objName  );										\
																		if  (  IDOK  !=  AfxMessageBox(  hintBuf,  MB_OKCANCEL  )  )  return;		\
																	}

#ifndef  __DEBUG__
	#define		MACRO_chkSfz(  idc,  buf,  hint  )					error	"Attention: MACRO_chkSfz(  ) not finished."	
#else
	#define		MACRO_chkSfz(  idc,  buf,  hint  )						;	
#endif

//  2008/06/20
#define		M_free(  p  )											{   if  (  p  )  {  free(  (  void  *  )(  p  )  );  (  p  )  =  NULL;  }  }

#define		MACRO_qyNullThread(  h  )								{	if  (  h  )  {									\
																			::WaitForSingleObject(  h,  INFINITE  );	\
																			CloseHandle(  h  );	h	=	NULL;			\
																		}												\
																	}

#define		CONST_qyWorkSubDir										"work\\"
#define		QY_WORKSUBDIRNAME										CONST_qyWorkSubDir
#define		CONST_qyResSubDir										"resource\\"
#define		CONST_qyCfgSubDir										"cfg\\"					//  2011/04/10
#define		CONST_qyHelpSubDir										"help\\"
#define		CONST_qyBinSubDir										"bin\\"
#define		CONST_qyDbSubDir										"db\\"
#define		CONST_qyCusModuleSubDir									"cusModule\\"
#define		CONST_qyClientSubDir									"client\\"				//  2011/03/25
#define		CONST_qvwSubDir											"qvw\\"					//  2018/07/05


//
#define		CONST_qyNullMac											"000000000000"
#define		QY_NULLCSTR												CString(  ""  )
#define		CONST_qyNullTime										"00000000000000"
#define		CONST_qyNullIp12										"000000000000"			//  2011/04/10


#define		QY_STATUS_OK											0
#define		QY_STATUS_ERR											1
#define		QY_STATUS_DEL											2
#define		QY_STATUS_BASE											3

#define		QY_BOOL_TRUESTR											"01"
#define		QY_BOOL_FALSESTR										"00"

#define		CONST_qyCharSpace										(  0x20  )
//#define		CONST_qyTimeLen											14
#define		CONST_qyMaxVerLen										8
#define		CONST_qyMaxOsNameLen									64
#define		CONST_qyMaxServicePackLen								64
#define		CONST_qyMaxUsrNameLen									64

#define		MACRO_qyStatusStr( status )								qyStatusStr(  status,  statusBuf,  sizeof(  statusBuf  )  )

#ifdef  __DEBUG__

#ifdef  __cplusplus
		extern  "C"  {
#endif
	 
__declspec(  dllexport  ) int  WINAPI  assert_MessageBox(  HWND hWnd ,  LPCWSTR lpText,  LPCWSTR lpCaption,  UINT uType  );

#ifdef  __cplusplus
		}
#endif



//
#define		MACRO_qyAssert(  x,  hint  )							if  (  !(  x  )  )  {															\
																		TCHAR  buf[128];															\
																																					\
																		_sntprintf(  buf,  mycountof(  buf  ),  _T(  "%s"  ),  (  (  hint  )  ?  (  hint  )  :  _T(  ""  )  )  );	\
																		assert_MessageBox(  NULL,  buf,  _T(  "Error"  ),  MB_SETFOREGROUND  |  MB_TOPMOST  );							\
																		ExitProcess(  0  );																							\
																	}
#else
  #define		MACRO_qyAssert(  x,  hint  )
#endif


#ifndef  isHandleValid
		 #define		isHandleValid(  h  )									(  (  h  )  !=  NULL  &&  (  h  )  !=  INVALID_HANDLE_VALUE  )
#endif


//  这里的0,1,2,3不是指内存中的物理字节顺序，而是指从小到大的字节顺序
#define		MACRO_byte0(  l  )										(  (  l  &  0x000000ff  )  )
#define		MACRO_byte1(  l  )										(  (  l  &  0x0000ff00  )  >>  8  )
#define		MACRO_byte2(  l  )										(  (  l  &  0x00ff0000  )  >>  16  )
#define		MACRO_byte3(  l  )										(  (  l  &  0xff000000  )  >>  24  )


#define		MACRO_getnItems(  pTable, lType,  n  )  {	for  (  n  =  0;  pTable[n].lType  !=  -1;  n  ++  );  }

#define		CONST_qyStatType_others				99999
#define		CONST_qyStatType_all				999991


#if 0
typedef  struct  __commonParam_t	{
				 void	*			p0;
				 void	*			p1;
				 void	*			p2;
				 //  void	*			p3;
				 //  void	*			p4;
}		 COMMON_PARAM;
#define		MACRO_makeCommonParam3(  p0Param,  p1Param,  p2Param,  commonParam  )	{  commonParam.p0  =  p0Param;  commonParam.p1  =  p1Param;  commonParam.p2  =  p2Param;  }  
#endif



#ifdef  __WINCE__		//  2010/03/19. for winCe
		#undef  lstrcpyn
		#define  lstrcpyn(  strOut,  strIn,  size  )  safeTcsnCpy(  strIn,  strOut,  size  )
#endif


#endif	/*  }  */


