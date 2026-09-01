
#include	"stdafx.h"
#include	<Windows.h>
//#include	<mmeapi.h>
#include	<mmsystem.h>
#include	"qmOpenCommon.h"
#include <lmcons.h>
#include	"fileFunc_open.h"
#include <tchar.h>
#include	"qytcharcommproc.h"


//
extern  "C"  BOOL  bDir(LPCTSTR  dir)
{
	DWORD  dwFileAttributes = 0;

	if ((dwFileAttributes = GetFileAttributes(dir)) != -1
		&& (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		return  TRUE;
	}
	return  FALSE;
}


extern  "C"  bool  bFileExists(  LPCTSTR  fileName  )
{
	bool  bRet  =  false;

	if  (  !fileName  )  return  false;

	if  (  GetFileAttributes(  fileName  )  !=  INVALID_FILE_ATTRIBUTES  )  bRet  =  TRUE;

	return  bRet;
}



//
extern  "C"  int  enumUsrDir_open(LPCTSTR  usrsRootDir, PF_enumUsrDir  pF, void* p0, void* p1)
{
	int							iErr = -1;
	TCHAR						scanName[PATHLEN];
	WIN32_FIND_DATA				FindData;
	HANDLE						fh = NULL;
	TCHAR* p = NULL;
	int							iRet = -1;
	TCHAR						tBuf[1024];

	/*
	 * check to see if filename is a directory
	 */
	if (!bDir(usrsRootDir)) {
		//traceLogA((char*)"非目录");  
		goto  errLabel;
	}

	/*
	 * Create the search pattern
	 */
	//safeTcsnCpy(usrsRootDir, scanName, mycountof(scanName));
	lstrcpyn(scanName, usrsRootDir, mycountof(scanName));

	if (_tcschr(_T("/\\"), *(scanName + lstrlen(scanName) - 1)) == NULL)  p = (TCHAR*)_T("\\*");
	else  p = (TCHAR*)_T("*");
	if (tQyStrCat_open(scanName, p, scanName, mycountof(scanName)))  goto  errLabel;
	

	/*
	 * do the FindFirstFile call
	 */
	fh = FindFirstFile(scanName, &FindData);
	if (fh == INVALID_HANDLE_VALUE)  goto  errLabel;

	do {
		TmpFileResult tfr = { 0 };
		//
		//safeTcsnCpy(FindData.cFileName, scanName, mycountof(scanName));
		lstrcpyn(tfr.fileName, FindData.cFileName, mycountof(tfr.fileName));
		tTrim_open(tfr.fileName);
		WIN32_FIND_DATA* pData = &FindData;
		tfr.ui64FileLen = (pData->nFileSizeHigh * (MAXDWORD + 1)) + pData->nFileSizeLow;

		//  traceLogA(  (char*)  "搜索到%s",  FindData.cFileName  );  

		if (pF) {
			iRet = pF(p0, p1, &tfr);
			//if (iRet > 0 || iRet == CONST_qyRet_quit) 
			if  (  iRet  )
			{
				//traceLogA((char*)"得到停止枚举的返回值");  
				break;
			}
		}

	} while (FindNextFile(fh, &FindData) || GetLastError() != ERROR_NO_MORE_FILES);

	iErr = 0;

errLabel:

	if (isHandleValid_open(fh))  FindClose(fh);

	return  iErr;

}

