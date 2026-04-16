

#ifndef  __TMPLIB_H__
#define	 __TMPLIB_H__	//  {

extern  "C"  BOOL  mybDir(  LPCTSTR  dir  );
extern  "C"  int  tmpqyOutputResourceFile(  HMODULE  hModule,  unsigned  short  idrData,  LPCTSTR  fileName  );

extern  "C"  TCHAR  *  tmpqyGetFullPath(  LPCTSTR  path,  LPCTSTR  file,  TCHAR  *  buf,  unsigned  int  bufSize  );
extern  "C"  BOOL  tmpbQyUpdateImageData(  LPCTSTR  svPath,  char  *  symbol,  char  *  data,  unsigned  int  dataLen  );





 BOOL  bQnmCntCfgValid(  QNM_CNT_CFG  *  pCfg  );
 //  int  getFileLen(  char  *  fileName  );

int  WINAPI  myMessageBox(  HWND hWnd ,  LPCWSTR lpText,  LPCWSTR lpCaption,  UINT uType  );
//  2013/02/16
 //  int  WINAPI  qyMessageBox(  HWND hWnd ,  LPCWSTR lpText,  LPCWSTR lpCaption,  UINT uType,  UINT  nTimeoutInS,  BOOL  *  pbSyncFlg  );


#endif	//  }



