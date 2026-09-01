

#include	"qyPrecomp.h"

#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<stdarg.h>
#ifndef		WIN32
	//  #include  <unistd.h>
#endif
#include	<ctype.h>

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include	<windows.h>



#include	<tchar.h>
#include	<shlobj.h>


#include	"qyCommon.h"
#include	"qyGuiCommon.h"



#if  0
 // wxr写在2003/09/12
 extern  "C"  static  int  tmp_qyGetRegCfg1(  HKEY  hKeyRoot0,  LPCTSTR  rootKey,  LPCTSTR  cfgName,  LPBYTE  cfgVal,  int  size,  unsigned  int  *  puiType  )
{
	int		iRet		=	-1;
	BOOL	bKeyOpen	=	FALSE;
	HKEY	hKey;
	int		lRet		=	0;
	long	cb;
	DWORD	type;
			
	if  (  !rootKey  || !rootKey[0]  )  return  -1;
	if  (  !hKeyRoot0  )  hKeyRoot0  =  HKEY_LOCAL_MACHINE;

	//  lRet  =  RegOpenKey(  hKeyRoot0,  rootKey,  & hKey  );
	lRet  =  RegOpenKeyEx(  hKeyRoot0,  rootKey,  0,  KEY_QUERY_VALUE,  & hKey  );
	if  (  lRet  !=  ERROR_SUCCESS  )  {
		//  traceLogA(  "qyGetRegCfg(  ):  RegOpenKey( %s )  failed.",  rootKey  );
		goto  errLabel;
	}
	bKeyOpen  =  TRUE;
	
	cb  =  size;
	if  (  RegQueryValueEx(  hKey,  cfgName,  0,  & type,  (  unsigned  char  *  )cfgVal, 
			(  unsigned  long  *  ) & cb  )  !=  ERROR_SUCCESS  ) 
	{
		//  traceLogA(  "qyGetRegCfg(  ):  RegQueryValueEx( %s )  failed.",  cfgName  );
		goto errLabel;
	}
	//  2003/09/12加入了对类型的判断，仅对字符串作结尾
	if  (  type  ==  REG_SZ  ||  type  ==  REG_MULTI_SZ  ||  type  ==  REG_EXPAND_SZ   )  {
		TCHAR	*	pT  =  (  TCHAR  *  )cfgVal;
		cb  =  cb  /  sizeof(  TCHAR  );
		if  (  cb  <  1  )  pT[0]	=	0;
		else  pT[cb - 1] = 0;
	}
	
	iRet  =  0;
	
errLabel:

	if ( bKeyOpen ) RegCloseKey( hKey );

	if  (  !iRet  )  {
		if  (  puiType  )  *  puiType  =  type;		//  2004/08/06加
	}

	return iRet;

}

#endif

  // wxr写在2002/09/06
 extern  "C"  int		qyGetRegCfg( LPCTSTR rootKey, LPCTSTR cfgName, char *cfgVal, int size )
{
	 //  return  tmp_qyGetRegCfg1(  HKEY_LOCAL_MACHINE,  rootKey,  cfgName,  (  LPBYTE  )cfgVal,  size,  NULL  );
	QY_REG	reg;
	memset(  &reg,  0,  sizeof(  reg  )  );
	lstrcpyn(  reg.rootKey,  rootKey,  mycountof(  reg.rootKey  )  );
	return  tmpGetRegCfgEx(  &reg,  cfgName,  cfgVal,  (  unsigned  int  *  )&size  );
}


 extern  "C"  int  qySetRegCfg( LPCTSTR  rootKey, LPCTSTR  cfgName, LPCTSTR  cfgVal )
{
	int		iRet		=	-1;
	BOOL	bKeyCreated =	FALSE;
	HKEY	hKey		=	NULL;
	int		rc			=	-1;
	DWORD	cb			=	0;
	

	if ( ( rc = RegCreateKeyEx( HKEY_LOCAL_MACHINE, rootKey, NULL,  _T(  ""  ),  NULL,  KEY_ALL_ACCESS,  NULL,  &hKey,  NULL ) ) != ERROR_SUCCESS ) 
	{
		char buf[128];
		sprintf( buf, "RegCreate returns %d", rc );
		traceLogA( "asrSetRegCfg( ): RegCreateKey( ) failed: %s", buf );
		goto errLabel;
	}
	bKeyCreated = TRUE;
	
	cb  =  (  lstrlen(  cfgVal  )  +  1  )  *  sizeof(  TCHAR  );
	if ( RegSetValueEx( hKey, cfgName, 0, REG_SZ, ( const unsigned char * )cfgVal, cb ) != ERROR_SUCCESS ) {
		traceLogA( "asrSetRegCfg( ): RegSetValueEx( ) failed." );
		goto errLabel;
	}

	iRet = 0;

errLabel:

	if  (  bKeyCreated  )  RegCloseKey(  hKey  );

	return iRet;

}

  extern  "C"  int  qyDelRegCfg(  LPCTSTR  rootKey,  LPCTSTR  cfgName  )
{
	int		iRet		=	-1;
	BOOL	bKeyOpen	=	FALSE;
	HKEY	hKey;
	long	lRet;
			
	if  (  !rootKey  || !rootKey[0]  )  return  -1;
	//  lRet  =  RegOpenKey(  HKEY_LOCAL_MACHINE,  rootKey,  &hKey  );
	lRet  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  rootKey,  0,  KEY_SET_VALUE,  &hKey  );
	if  (  lRet  !=  ERROR_SUCCESS  )  {		
		goto  errLabel;
	}
	bKeyOpen  =  TRUE;

	if  (  ERROR_SUCCESS  !=  RegDeleteValue(  hKey,  cfgName  )  )  goto  errLabel;
	
	iRet  =  0;
	
errLabel:

	if  (  bKeyOpen  ) RegCloseKey(  hKey  );

	return  iRet;

}


  extern  "C"  void  qyTrim(  char  *  buf  )
{
	char  *  p  =  buf;
	int  len;

	if  (  !buf  ||  !buf[0]  )  return;
	while  (  (  len  =  strlen(  p  )  )  )  {
		   if  (  !asrIsSpace(  p[len  -  1]  )  )  break;
		   p[len  -  1]  =  0;
	}
	while  (  p[0]  )  {
		   if  (  !asrIsSpace(  *p  )  )  break;
		   p  ++  ;
	}
	strcpy(  buf,  p  );
	
	return;

}

 extern "C" void trim( char *buf )
{
        unsigned char *p;
		unsigned int len = strlen( buf );

		if ( !buf || !( len = strlen( buf ) ) ) return;
        p = ( unsigned char * )buf + len - 1;

        while ( isWhiteSpace( *p ) && p >= ( unsigned char * )buf ) p --;
        p[1] = '\0';

        if ( p >= ( unsigned char * )buf ) {
                p = ( unsigned char * )buf;
                while ( isWhiteSpace( *p ) ) p ++;
				//
				//strcpy( ( char * )buf, ( char * )p );
				memmove((char*)buf, (char*)p, strlen((char*)p) + 1);

        }

        return;

}


 extern  "C"  void  tTrim(  TCHAR  *  buf  )
{
        TCHAR			*	p;
		unsigned  int		len		=	lstrlen(  buf  );

		if  (  !buf  ||  !(  len  =  lstrlen(  buf  )  )  )  return;
        p  =  buf  +  len  -  1;

        while  (  _istspace(  *p  )  &&  p  >=  buf  )  p  --;
        p[1]  =  0;

        if  (  p  >=  buf  )  {
            p  =  buf;
            while  (  _istspace(  *p  )  )  p  ++;
			lstrcpy(  buf,  p  );
        }

        return;

}


#if  0
 extern  "C"  int  trailDir(  char  *  dir,  unsigned  int  size  )
{
	 trim(  dir  );
	 if  (  dir[lstrlen(  dir  )  -  1]  ==  '\\'  )  return  0;
	 if  (  !qyStrCat(  dir,  "\\",  dir,  size  )  )  return  0;
	 return  -1;
	
}
#endif

  extern  "C"  int  trailDir(  TCHAR  *  dir,  unsigned  int  size  )
{
	 unsigned  int	len;

	 tTrim(  dir  );
	 len  =  lstrlen(  dir  );
	 //
	 if  (  len  >=  1  &&  size  >=  len  +  1  )  {
		 if  (  dir[len  -  1]  ==  '\\'  )  return  0;
	 }
	 //
	 if  (  len  +  2  >  size  )  return  -1;
	 dir[len]  =  '\\';
	 dir[len  +  1]  =  0;
	 return  0;
	
}


 extern  "C"  int  qyQuoteFileName(  TCHAR  *  fileName,  unsigned  int  size  )
{
	 unsigned  int	len;
	 TCHAR			quotedFileName[MAX_PATH  +  1];

	 tTrim(  fileName  );
	 if  (  fileName[0]  ==  '\"'  )  return  0;
	 len  =  lstrlen(  fileName  );
	 if  (  len  >=  size  -  2  ||  len  +  2  >  MAX_PATH  )  return  -1;
	 _sntprintf(  quotedFileName,  mycountof(  quotedFileName  ),  _T(  "\"%s\""  ),  fileName  );
	 lstrcpy(  fileName,  quotedFileName  );
	 return  0;	 
}

 extern  "C"  int  tQyStrCat(  LPCTSTR  str1,  LPCTSTR  str2,  TCHAR  *  containedBuf,  unsigned  int  bufSize  ) 
{
	 int  iErr  =  -1;

	 if  (  str2  ==  containedBuf  )  {
		 traceLogA(  "qyStrCat( ): str2 can't be the place to contain."  );
		 goto  errLabel;
	 }
	 if  (  lstrlen(  str1  )  +  lstrlen(  str2  )  >=  (  int  )bufSize  )  {
		 traceLogA(  "qyStrCat( ): buf too small."  );
		 goto  errLabel;
	 }
	 _sntprintf(  containedBuf,  bufSize,  _T(  "%s%s"  ),  str1,  str2  );
	 iErr  =  0;

errLabel:

	 return  iErr;

}

 
 extern "C" int safeStrCpy( char *strIn, char *strOut, unsigned int size )
{
	 if  (  strlen(  strIn  )  >=  (  int  )size  ) return -1;
	 strcpy(  strOut,  strIn  );
	 return 0;
}


 
 extern  "C"  void  safeStrnCpy(  char  *  strIn,  char  *  strOut,  unsigned  int  size  )
{
	 if  (  !size  ||  !strIn  ||  !strOut  )  return;
	 unsigned  int	len  =  min(  size  -  1,  (  unsigned  int  )strlen(  strIn  )  );
	 memcpy(  strOut,  strIn,  len  );
	 strOut[len]  =  0;
	 return;
}


 extern  "C"  void  safeTcsnCpy(  LPCTSTR  strIn,  TCHAR  *  strOut,  unsigned  int  size  )
{
	 if  (  !size  ||  !strIn  ||  !strOut  )  return;
	 unsigned  int	len  =  min(  size  -  1,  (  unsigned  int  )_tcslen(  strIn  )  );
	 memcpy(  strOut,  strIn,  sizeof(  TCHAR  )  * len  );
	 strOut[len]  =  0;
	 return;
}


  extern  "C"  int  qyStrCat(  char  *  str1,  char  *  str2,  char  *  containedBuf,  unsigned  int  bufSize  ) 
{
	 int  iErr  =  -1;

	 if  (  str2  ==  containedBuf  )  {
		 traceLogA(  "qyStrCat( ): str2 can't be the place to contain."  );
		 goto  errLabel;
	 }
	 if  (  strlen(  str1  )  +  strlen(  str2  )  >=  (  int  )bufSize  )  {
		 traceLogA(  "qyStrCat( ): buf too small."  );
		 goto  errLabel;
	 }
	 sprintf(  containedBuf,  "%s%s",  str1,  str2  );
	 iErr  =  0;

errLabel:

	 return  iErr;

}


 extern  "C"  char  *  qyStrStr(  const  char  *  string,  const  char  *  strCharSet  )
{
	 if  (  !strCharSet  ||  !strCharSet[0]  )  return  (  char  *  )string;
	 
	 int	len  =  strlen(  strCharSet  );

	 for  (  ;  *string;  string  ++  )  {
		  if  (  !_strnicmp(  string,  strCharSet,  len  )  )  return  (  char  *  )string;
	 }
	 return  NULL;
}




 //  cfgVal所在的buf最好大一些，以满足下面的inputLen要求。








///////////////




   //  除了REG_BINARY这种类型需要cb外，其他的，都用cfgVal自己来判断
 extern  "C"  int  tmpSetRegCfgEx(  QY_REG  *  pReg,  LPCTSTR  cfgName,  char  *  cfgVal,  unsigned  int  cb  ) 
{
	int			iRet			=	-1;
	BOOL		bKeyCreated		=	FALSE;
	HKEY		hKey;
	int			rc				=	-1;
	TCHAR		tBuf[512]		=	_T(  ""  );
	int			dataLen			=	cb;
	char	*	p				=	cfgVal;

	if  (  !cfgVal  )  return  -1;

	//  if ( ( rc = RegCreateKey( pReg->hKeyRoot0  ?  pReg->hKeyRoot0  :  HKEY_LOCAL_MACHINE, pReg->rootKey, &hKey ) ) != ERROR_SUCCESS ) goto errLabel;
	if ( ( rc = RegCreateKeyEx( pReg->hKeyRoot0  ?  pReg->hKeyRoot0  :  HKEY_LOCAL_MACHINE, pReg->rootKey, NULL,  _T(  ""  ),  NULL,  KEY_ALL_ACCESS,  NULL,  &hKey,  NULL  ) ) != ERROR_SUCCESS ) goto errLabel;
	bKeyCreated = TRUE;

	switch  (  pReg->uiType  )  {
			case  REG_DWORD:		dataLen  =  sizeof(  DWORD  );  
									break;
			case  REG_BINARY:		break;
			case  REG_MULTI_SZ:
				  if  (  !cb  )  {
					  dataLen  =  lstrlen(  (  TCHAR  *  )cfgVal  )  +  1;			//  注意，这里需要将包含'\0'的字节也包含
					  if  (  dataLen  >=  mycountof(  tBuf  )  -  1  )  {
						  traceLogA(  "buf is too small"  );  goto  errLabel;
					  }
					  lstrcpyn(  tBuf,  (  TCHAR  *  )cfgVal,  mycountof(  tBuf  )  );
					  tBuf[dataLen]  =  '\0';  dataLen  ++  ;
					  
					  p  =  (  char  *  )tBuf;
					  dataLen  =  dataLen  *  sizeof(  TCHAR  );
				  }
				  break;
			case  REG_SZ:
			default:	
				    if  (  !cb  )  {
						dataLen  =  (  lstrlen(  (  TCHAR  *  )cfgVal  )  +  1  )  *  sizeof(  TCHAR  );			//  注意，这里需要将包含'\0'的字节也包含
					}
					break;
	}

	DWORD uiType_default  =  REG_SZ;
	if  (  RegSetValueEx(  hKey,  cfgName,  0,  pReg->uiType  ?  pReg->uiType  :  uiType_default,  (  const  unsigned char  *  )p,  dataLen  )  !=  ERROR_SUCCESS  )  {
		traceLogA( "asrSetRegCfg( ): RegSetValueEx( ) failed." );  goto errLabel;
	}

	iRet = 0;

errLabel:

	if  (  bKeyCreated  )  RegCloseKey(  hKey  );

	return  iRet;

}


  extern  "C"  int  tmpGetRegCfgEx(  QY_REG  *  pReg,  LPCTSTR  cfgName,  char  *  cfgVal,  unsigned  int  *pSize  )
{
	HKEY	hKeyRoot0  =  pReg->hKeyRoot0;
	LPCTSTR  rootKey  =  pReg->rootKey;
	unsigned  int  *  puiType  =  &pReg->uiType;
	 
	int				iRet		=	-1;
	BOOL			bKeyOpen	=	FALSE;
	HKEY			hKey;
	unsigned  int	cb;
	DWORD			type;
			
	if  (  !rootKey  || !rootKey[0]  ||  !pSize  )  return  -1;
	if  (  !hKeyRoot0  )  hKeyRoot0  =  HKEY_LOCAL_MACHINE;

	//  if  (  RegOpenKey(  hKeyRoot0,  rootKey,  &hKey  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	if  (  RegOpenKeyEx(  hKeyRoot0,  rootKey,  0,  KEY_QUERY_VALUE,  &hKey  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	bKeyOpen  =  TRUE;
	
	cb  =  *pSize;
	if  (  RegQueryValueEx(  hKey,  cfgName,  0,  &type,  (  unsigned  char  *  )cfgVal,  (  unsigned  long  *  )&cb  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	
	//  2003/09/12加入了对类型的判断，仅对字符串作结尾
	if  (  type  ==  REG_SZ  ||  type  ==  REG_MULTI_SZ  ||  type  ==  REG_EXPAND_SZ   )  {
		TCHAR	*	pT	=	(  TCHAR  *  )cfgVal;
		cb  =  cb  /  sizeof(  TCHAR  );
		if  (  cb  <  1  )  pT[0]	=	0;
		else  pT[cb - 1] = 0;
	}
	
	iRet  =  0;
	
errLabel:

	if  (  bKeyOpen )  RegCloseKey(  hKey  );

	if  (  !iRet  )  {
		if  (  puiType  )  *puiType  =  type;		//  2004/08/06加
		if  (  pSize  )  *pSize  =  cb;

	}

	return  iRet;

}




//////////////////////





  //  extern  "C"  int  qyRefreshRegCfg_ucb(  char  *  rootKey,  char  *  regValName,  unsigned  char  *  pucbVal  )
 extern  "C"  int  qyRefreshRegCfg_ucb(  LPCTSTR  rootKey,  LPCTSTR  regValName,  unsigned  char  *  pucbVal  )
{
	 unsigned  char   	ucbStarted  =  FALSE;
	 char				buf[32];

	 if  (  !qyGetRegCfg(  rootKey,  regValName,  buf,  sizeof(  buf  )  )  )  {
		 if  (  atol(  buf  )  ==  1  )  ucbStarted  =  TRUE;
	 }
	 if  (  ucbStarted  !=  *pucbVal  )  *pucbVal  =  ucbStarted;
	 return  0;
}


 /*
 extern  "C"  char  *  qwmGetCfg(  char  *  input,  char  *  cfgName,  char  *  cfgVal,  unsigned  int  size  )
{
	 char  *  pRet  =  cfgVal;
	 char  *  p  =  input;
	 unsigned  int  cfgLen  =  (  unsigned  int  )lstrlen(  cfgName  );

	 MACRO_qyAssert(  input  &&  cfgName  &&  cfgVal  &&  size  &&  cfgLen,  "test"  );
	 for  (  p  =  input;  *p;  p  ++  )  {
		  if  (  strnicmp(  p,  cfgName,  cfgLen  )  )  continue;
		  p  +=  cfgLen;
		  if  (  *p  !=  '='  )  return  NULL;
		  p  ++  ;
		  for  (  ;  *p  &&  !asrIsSpace(  *p  ) &&  size  >  1  ;  p  ++,  cfgVal  ++,  size  --  )  {
			   *cfgVal  =  *p;
		  }
		  *cfgVal  =  0;
		  return  pRet;
	 }

	 return  NULL;
}
 */

 //  注意：qwmGetCfg在处理=时作了改进，2003/12/16，旧版见上
 extern  "C"  char  *  qwmGetCfg(  char  *  input,  char  *  cfgName,  char  *  cfgVal,  unsigned  int  size  )
{
	 char  *  pRet  =  cfgVal;
	 char  *  p  =  input;
	 unsigned  int  cfgLen  =  (  unsigned  int  )strlen(  cfgName  );

	 //MACRO_qyAssert(  input  &&  cfgName  &&  cfgVal  &&  size  &&  cfgLen,  _T(  "test"  )  );
	 //
	 for  (  p  =  input;  *p;  p  ++  )  {
		  if  (  _strnicmp(  p,  cfgName,  cfgLen  )  ||  p[cfgLen]  !=  '='  )  continue;
		  p  +=  cfgLen  +  1;		//  指向=后面的字节
		  for  (  ;  *p  &&  !asrIsSpace(  *p  ) &&  size  >  1  ;  p  ++,  cfgVal  ++,  size  --  )  {
			   *cfgVal  =  *p;
		  }
		  *cfgVal  =  0;
		  return  pRet;
	 }

	 return  NULL;
}

/*
 extern  "C"  int  qyGetFileRootName(  LPSTR  pFile,  char  *  RootName,  unsigned  int  size  ) 
{     
	 int		iErr	=	-1;
	 //  char	RootName[MAX_PATH];     
	 LPSTR		ptmp;    //required arg     
	 
	 // need to find path for root directory on drive containing     
	 // this file.      
	 if  (  !GetFullPathName(  pFile,  size,  RootName,  &ptmp  )  )  goto  errLabel;
	 // truncate this to the name of the root directory (god how tedious)     
	 if  (  RootName[0]  ==  '\\'  &&  RootName[1]  ==  '\\'  )  {  
		 // path begins with  \\server\share\path so skip the first 
		 // three backslashes 
		 ptmp = &RootName[2]; 
		 while  (  *ptmp  &&  (  *ptmp  !=  '\\'  )  )  { 
			    ptmp  ++  ; 
		 }
		 if  (  *ptmp  )  {     
			 // advance past the third backslash     
			 ptmp  ++  ;
			 }
		 } 
	 else  { 
		 // path must be drv:\path 
		 ptmp = RootName;     
	 }      
	 // find next backslash and put a null after it     
	 while  (  *ptmp  &&  (  *ptmp  !=  '\\'  )  )  { 
		    ptmp  ++  ;     
	 }     
	 // found a backslash ?     
	 if  (  *ptmp  )  { 
		 // skip it and insert null 
		 ptmp  ++  ;  *ptmp  =  '\0';     
	 }      

	 iErr  =  0;

errLabel:
	 
	 return  iErr;

}    
*/


 //  extern  "C"  BOOL  bQyCopyFileEx(  char  *  srcFile,  char  *  dstFile,  unsigned  int  totalnCopies  )
 extern  "C"  BOOL  bQyCopyFileEx(  LPCTSTR  srcFile,  LPCTSTR  dstFile,  unsigned  int  totalnCopies  )
{	
	for  (  ;  totalnCopies;  totalnCopies  --  )  {
		 if  (  CopyFile(  srcFile,  dstFile,  FALSE  )  )  return  TRUE;
		 if  (  totalnCopies  >  1  )  Sleep( 1000 );
	}

	return  FALSE;
}


 UINT  myGetWindowsDirectory(  LPTSTR lpBuffer,  UINT uSize  )
{
#ifdef  __WINCE__
		TCHAR szPath[MAX_PATH];

		if(SHGetSpecialFolderPath(NULL,
							 szPath,  
                             CSIDL_WINDOWS, 
							 FALSE)  ) 
		{
			safeTcsnCpy(  szPath,  lpBuffer,  uSize  );
			return  lstrlen(  lpBuffer  );
		}
		return  0;
#else
	return  GetWindowsDirectory(  lpBuffer,  uSize  );
#endif
}

 UINT  myGetSystemDirectory(  LPTSTR lpBuffer,  UINT uSize  )
{
#ifdef  __WINCE__
		TCHAR szPath[MAX_PATH];

		if(SHGetSpecialFolderPath(NULL,
							 szPath,  
                             CSIDL_WINDOWS, 
							 FALSE)  ) 
		{
			safeTcsnCpy(  szPath,  lpBuffer,  uSize  );
			return  lstrlen(  lpBuffer  );
		}
				return  0;

#else
	return  GetSystemDirectory(  lpBuffer,  uSize  );
#endif
}



 extern  "C"  int  qyFullLibName(  LPCTSTR  libName,  TCHAR  *  fullLibName,  unsigned  int  size  )
{
	 TCHAR	systemDir[MAX_PATH  +  1];

	 myGetSystemDirectory(  systemDir,  mycountof(  systemDir  )  );
	 if  (  trailDir(  systemDir,  mycountof(  systemDir  )  )
		 ||  tQyStrCat(  systemDir,  libName,  fullLibName,  size  )  )
	 {
		 return  -1;
	 }
	 return  0;
}

 extern  "C"  int  qyFullWinLibName(  LPCTSTR  libName,  TCHAR  *  fullLibName,  unsigned  int  size  )
{
	 TCHAR	winDir[MAX_PATH  +  1];

	 myGetWindowsDirectory(  winDir,  mycountof(  winDir  )  );
	 if  (  trailDir(  winDir,  sizeof(  winDir  )  )
		 ||  tQyStrCat(  winDir,  libName,  fullLibName,  size  )  )
	 {
		 return  -1;
	 }
	 return  0;
}


 extern  "C"  int  qyOutputResourceFile(  unsigned  short  idrData,  LPCTSTR  fileName  )
{
	int					iErr		=  -1;
	HMODULE				hModule		=  GetModuleHandle(  NULL  );
	HRSRC				hr			=  NULL;
	HGLOBAL				hg			=  NULL;
	LPVOID				pv			=  NULL;
	//  FILE	*		fp			=  NULL;
	HANDLE				hFile		=	INVALID_HANDLE_VALUE;
	unsigned long		nWritten	=	0;


	hr  =  FindResource(  hModule,  MAKEINTRESOURCE(  idrData  ),  RT_RCDATA  ); 
	if  (  !hr  )  goto  errLabel;
	hg  =  LoadResource(  hModule,  hr  );
	if  (  !hg  )  goto  errLabel;
	//  traceLogA(  "sizeof resource is %d",  SizeofResource(  ghModule,  hr  )  );
	pv  =  LockResource(  hg  );	//  pv指向内存块的第一个字节，为单字节指针 
	if  (  !pv  )  goto  errLabel;

	//	Read data from resource (memory block) 
	//  fp  =  fopen(  fileName,  "wb"  );
	//  if  (  !fp  )  goto  errLabel;

	hFile  =  CreateFile( fileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, NULL );
	if  (  !isHandleValid(  hFile  )  )  {
		qyDisplayLastError(  "qyOutputResourceFile failed"  );  goto  errLabel;
	}

	//  if  (  fwrite(  pv,  SizeofResource(  ghModule,  hr  ),  1,  fp  )  !=  1  )  goto  errLabel;
	if  (  !WriteFile(  hFile,  pv,  SizeofResource(  hModule,  hr  ),  &nWritten,  NULL  )  )  goto  errLabel;
	if  (  nWritten  !=  SizeofResource(  hModule,  hr  )  )  goto  errLabel;
	
	iErr  =  0;

errLabel:

	if  (  isHandleValid(  hFile  )  )  CloseHandle(  hFile  );
	//  if  (  fp  )  fclose(  fp  );
	
#ifndef  __WINCE__
	if  (  pv  )  UnlockResource(  hg  );
	if  (  hg  )  FreeResource(  hr  ); 
#endif
	
	return  iErr;

}



 


 QY_DMITEM  CONST_qyIdcTypeTable[]  =
{
	{	CONST_qyIdcType_edit,				_T(  "edit"  ),				},
	{	CONST_qyIdcType_combo,				_T(  "combo"  ),			},
	{	CONST_qyIdcType_static,				_T(  "static"  ),			},
	{	CONST_qyIdcType_button,				_T(  "botton"  ),			},
	{	CONST_qyIdcType_progress,			_T(  "progress"  ),			},
	{	CONST_qyIdcType_ip,					_T(  "ip"  ),				},
	{	CONST_qyIdcType_time,				_T(  "time"  ),				},
	{	CONST_qyIdcType_comboDesc,			_T(  "comboDesc"  ),		},
	{	CONST_qyIdcType_chk,				_T(  "chk"  ),				},
	{	-1,									NULL,				},
};


#ifdef  __DEBUG__

 extern  "C"  int  showIdcItem(  QY_IDCITEM  *  pIdcItem,  char  *  hint  )
{
	 //  traceLogA(  "idc is %d, idcType is %s,  des is %s, name is %s, flg is %d, %s",  pIdcItem->idc,  qyGetDesByType1(  CONST_qyIdcTypeTable,  pIdcItem->idcType  ),  pIdcItem->des  ?  pIdcItem->des  :  "",  pIdcItem->name ? pIdcItem->name  :  "",  pIdcItem->flg,  hint  ?  hint  :  ""  );

	 /*
				 long								idc;				//	控件ID
				 long								idcType;			//  idc的类型
				 char			*					des;				//  对edit表示初始值; 对comboBox表示初始选项,  使用NULL表不操作,  或者由程序员来定义操作
				 long								lIdc, rIdc;			//  左边的idc, 右边的idc
				 QY_DMITEM		*					pTable;				//  comboBox的初始化值; 对checkBox, 此项可用于表示对数据库的查询分类
				 long								maxBytes;			//  对edit输入字节数限制; 对checkBox, 0表unchecked,  非0表checked
				 long								x, y, w, h;			//  x, y表左上点的坐标
				 long								flg;
				 char			*					sqlColName;			//  对查询，标志该控件代表的列名
				 char			*					comment;			//	提供调试用的注释
		*/


	 return   0;
}


#endif