

#ifndef  __QMUIFUNC_H__
#define  __QMUIFUNC_H__	//  {

//
#include	"qmStruct_defs.h"

//
//__declspec(  dllexport  )  int  qyBrowseForFile(  HWND  hwndOwner,  BOOL bOpen,  LPCTSTR  lpszDefExt,  DWORD  dwFlags,  LPCTSTR  lpszFilter,  LPCTSTR  title,  LPCTSTR  initialFile,  CQyString  &  fileStr  );
//
__declspec(  dllexport  )  int  qyBrowseForFile(  HWND  hwndOwner,  BOOL bOpen,  LPCTSTR  lpszDefExt,  DWORD  dwFlags,  LPCTSTR  lpszFilter,  LPCTSTR  title,  LPCTSTR  initialFile,  CCtxQyMcTmpl  *  pQyMcTmpl,  CQyString  &  fileStr  );

//
int  qyBrowseForDir(  HWND  hwndOwner,  LPCTSTR  title,  LPCTSTR  initialDir,  CQyString  &  dirStr  );

//
//__declspec(  dllexport  )  int  qyBrowseForFile1(  HWND  hwndOwner,  BOOL bOpen,  LPCTSTR  lpszDefExt,  DWORD  dwFlags,  LPCTSTR  lpszFilter,  LPCTSTR  title,  LPCTSTR  initialFile,  TCHAR  *  fileStr,  unsigned  int  fileStrCnt  );
__declspec(  dllexport  )  int  qyBrowseForFile1(  HWND  hwndOwner,  BOOL bOpen,  LPCTSTR  lpszDefExt,  DWORD  dwFlags,  LPCTSTR  lpszFilter,  LPCTSTR  title,  LPCTSTR  initialFile,  CCtxQyMcTmpl  *  pQyMcTmpl,  TCHAR  *  fileStr,  unsigned  int  fileStrCnt  );


#endif


