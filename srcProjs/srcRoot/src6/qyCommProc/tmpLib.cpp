
#include	"stdafx.h"

#include	"qyPrecomp.h"
#include	<winsock2.h>
#include	<stdlib.h>
#include	<windows.h>
#include	<stdio.h>
#include	<string.h>
#include	<lmcons.h>
#include	<tchar.h>
#include	"qyCommon.h"
#include	"qyCommCommon.h"
#include	"qyWmComm.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qyTCharCommProc.h"
#include	"tmpCeLib.h"

 extern  "C"  BOOL  mybDir(  LPCTSTR  dir  )
{
	 DWORD  dwFileAttributes  =  0;

 	 if  (  (  dwFileAttributes  =  GetFileAttributes(  dir  )  )  !=  -1
		&&  (  dwFileAttributes  &  FILE_ATTRIBUTE_DIRECTORY  )  )
	{
		return  TRUE;
	}
	 return  FALSE;
}


 extern  "C"  int  tmpqyOutputResourceFile(  HMODULE  hModule,  unsigned  short  idrData,  LPCTSTR  fileName  )
{
	int					iErr		=  -1;	
	//  HMODULE				hModule		=  GetModuleHandle(  NULL  );
	HRSRC				hr			=  NULL;
	HGLOBAL				hg			=  NULL;
	LPVOID				pv			=  NULL;
	//  FILE	*		fp			=  NULL;
	HANDLE				hFile		=	INVALID_HANDLE_VALUE;
	unsigned long		nWritten	=	0;


	if  (  !hModule  )  goto  errLabel;
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
		qyDisplayLastError(  (char*)"qyOutputResourceFile failed"  );  goto  errLabel;
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



 extern "C"  TCHAR  *  tmpqyGetFullPath(  LPCTSTR  path,  LPCTSTR  file,  TCHAR  *  buf,  unsigned  int  bufSize  )
{

	lstrcpyn(  buf,  path,  bufSize  );
	tTrim(  buf  );
	if  (  buf[lstrlen(  buf  )  -  1]  ==  _T(  '\\'  )  )  {
		if  (  lstrlen(  buf  )  +  lstrlen(  file  )  >=  (  int  )bufSize  )  return  NULL;
		_sntprintf(  buf,  bufSize,  _T(  "%s%s"  ),  buf,  file  );
		}
	else  {
		  if  (  lstrlen(  buf  )  +  1  +  lstrlen(  file  )  >=  (  int  )bufSize  )  return  NULL;
		  _sntprintf( buf,  bufSize,  _T(  "%s\\%s"  ),  buf,  file  );
	}

	return  buf;
	
}



 
static  BOOL  bQyUpdatePeVar(  char  *  pBuffer,  DWORD  dwLen,  char  *  symbol,  char  *  data,  DWORD  dataLen  );

 extern  "C"  BOOL  tmpbQyUpdateImageData(  LPCTSTR  svPath,  char  *  symbol,  char  *  data,  unsigned  int  dataLen  )
{
	BOOL				bRet			=	FALSE;
	HANDLE				hSvrFile		=	NULL;
	HANDLE				m_hSvrMapping	=	NULL;
	void		*		m_pSvrView		=	NULL;
	DWORD				m_dwRawFileSize;			// Size of server file map without all the plugins

	// Open server file
	hSvrFile  =  CreateFile(  svPath,  GENERIC_READ  |  GENERIC_WRITE,  0,  NULL,  OPEN_EXISTING,  0,  NULL  );
	if  (  hSvrFile  ==  INVALID_HANDLE_VALUE  )  goto  errLabel;
	m_dwRawFileSize  =  GetFileSize(  hSvrFile,  NULL  );
	
	// Memory map it
	m_hSvrMapping  =  CreateFileMapping(  hSvrFile,  NULL,  PAGE_READWRITE,  0,  0,  NULL  );
	CloseHandle(  hSvrFile  );  hSvrFile  =  NULL;
	if  (  m_hSvrMapping  ==  NULL  )  goto  errLabel;
	
	m_pSvrView  =  (  BYTE  *  )MapViewOfFile(  m_hSvrMapping,  FILE_MAP_ALL_ACCESS,  0,  0,  0  );
	if  (  m_pSvrView  ==  NULL  )  goto  errLabel;

	if  (  !bQyUpdatePeVar(  (  char  *  )m_pSvrView,  m_dwRawFileSize,  symbol,  data,  dataLen  )  )  goto  errLabel;

	if  (  !FlushViewOfFile(  m_pSvrView,  0  )  )  {
		qyDisplayLastError(  (char*)""  );
		goto  errLabel;
	}

	bRet  =  TRUE;

errLabel:

	if  (  m_pSvrView  )  UnmapViewOfFile(m_pSvrView);
	if  (  m_hSvrMapping  )  CloseHandle(  m_hSvrMapping  );
	if  (  hSvrFile  )  CloseHandle(  hSvrFile  );

	return  bRet;

}

 static  BOOL  bQyUpdatePeVar(  char  *  pBuffer,  DWORD  dwLen,  char  *  symbol,  char  *  data,  DWORD  dataLen  )  
{
	BOOL		bRet	=  FALSE;
	DWORD		pos;
	DWORD		symLen  =  strlen(  symbol  );
	
	if  (  symLen  >  dwLen  )  goto  errLabel;		//  2003/11/04

	for  (  pos  =  0;  pos  <  dwLen  -  symLen;  pos  ++  )  {
		
		 if  (  memcmp(  pBuffer  +  pos,  symbol,  symLen  )  )  continue;

		 pos  +=  symLen;
		 if  (  dwLen  -  symLen  -  pos  <  dataLen  )  goto  errLabel;
		 memcpy(  pBuffer  +  pos,  data,  dataLen  );
		 break;
		
	}

	bRet  =  TRUE;

errLabel:

	return  bRet;

}




 #define		CONST_dllName_schedulerHelp			"schedulerHelp.dll"
 BOOL  bProcMakeClients(  BOOL  bMakeClients  )
{
	//  extern  "C"  __declspec(  dllexport  )  int _cdecl  qyChkSecurityMain(  );
	/*
	int  awmChkSecurityMain(  );
	
	awmChkSecurityMain( );
	*/

	 BOOL		bRet		=	FALSE;
	 HINSTANCE	hInstance	=	NULL;
	 int  (  _cdecl  *  pf  )(  void  *  p0,  void  *  p1,  void  *  p2  );
	 //  pf_qyChkSecurityMain
	 //  char	ver[32];

	 

	 TCHAR		tmpFileName[MAX_PATH  +  1];
	 TCHAR		pathBuf[MAX_PATH  +  1];
	 TCHAR	*	filePart;

	 GetModuleFileName(  NULL,  tmpFileName,  mycountof(  tmpFileName  )  );
	 if  (  !myGetFullPathName(  tmpFileName,  mycountof(  pathBuf  ),  pathBuf,  &filePart  )  )  return  -1;
	 filePart[0]  =  0;
	 _sntprintf(  tmpFileName,  mycountof(  tmpFileName  ),  _T(  "%s%s"  ),  pathBuf,  _T(  CONST_dllName_schedulerHelp  )  );

	 hInstance  =  LoadLibrary(  tmpFileName  );
	 if  (  !hInstance  )  {
		 OutputDebugString(  _T(  "bProcMakeClients failed: dll can't loaded"  )  );  goto  errLabel;
	 }
				
	 pf  =  (  int(*)(  void  *,  void  *,  void  *  )  )myGetProcAddress(hInstance,  "qyChkSecurityMain"  );
	 if  (  !pf  )  goto  errLabel;
	 if  (  pf(  hInstance,  (  void  *  )bMakeClients,  0  )  )  goto  errLabel;

	 bRet  =  TRUE;

errLabel:

	 if  (  hInstance  )  FreeLibrary(  hInstance  );

	 return  bRet;
}

 BOOL  bQnmCntCfgValid(  QNM_CNT_CFG  *  pCfg  )
{
	 BOOL  bRet  =  FALSE;

	 if  (  pCfg->ucbAutoCntIp  )  {
		 if  (  !bulIpValid(  inet_addr(  pCfg->cntIp  )  )  ||  inet_addr(  pCfg->cntIp  )  ==  inet_addr(  "127.0.0.1"  )  )  goto  errLabel;
		}
	 else  if  (  !pCfg->cntAddrs[0][0]  &&  !pCfg->cntAddrs[1][0]  &&  !pCfg->cntAddrs[2][0]  )  goto  errLabel;

	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}


#if  0
 extern  "C"  int  getFileLen(  char  *  fileName  )
{
	struct  _stat  tmpStat;

	if  (  _stat(  fileName,  &tmpStat  )  )  return  -1;

	return  tmpStat.st_size;
	
}
#endif


