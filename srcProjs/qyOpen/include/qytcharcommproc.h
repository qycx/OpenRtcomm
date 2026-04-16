

#ifndef  __QYTCHARCOMMPROC_H__
#define  __QYTCHARCOMMPROC_H__	//  {


#ifdef  __cplusplus
  extern  "C"  {
#endif

TCHAR  *  myStr2TChar(  char  *  buf,  TCHAR  *  tBuf,  unsigned  int  tBufSize  );
char  *  myTChar2Str(  LPCTSTR  tBuf,  char  *  buf,  unsigned  int  bufSize  );
#define		myStr2TChar1(  buf,  tBuf,  tBufSize  )  (  myStr2TChar(  buf,  tBuf,  tBufSize  )  ?  tBuf  :  _T(  ""  )  )  
#define		myTChar2Str1(  tbuf,  buf,  bufSize  )  (  myTChar2Str(  tBuf,  buf,  bufSize  )  ?  buf  :  ""  )  
//
char  *  myTChar2Utf8(  LPCTSTR  tBuf,  char  *  buf,  unsigned  int  bufSize  );
TCHAR  *  myUtf82TChar(  char  *  buf,  TCHAR  *  tBuf,  unsigned  int  tBufSize  );

WCHAR  *  myTChar2WChar(  LPCTSTR  tBuf,  WCHAR  *  wBuf,  unsigned  int  wBufSize  );	//  2005/11/27
TCHAR  *  myWChar2TChar(  LPCWSTR  wBuf,  TCHAR  *  tBuf,  unsigned  int  tBufSize  );


void  tTrim_open(  TCHAR  *  buf  );
void  safeStrnCpy_open(char* strIn, char* strOut, unsigned  int  size);


int  tTrailDir(  TCHAR  *  dir,  unsigned  int  size  );
int  tQyQuoteFileName(  TCHAR  *  fileName,  unsigned  int  charSize  );
//
int  tQyStrCat_open(TCHAR * str1, TCHAR * str2, TCHAR * containedBuf, unsigned  int  bufSize);


#ifdef  __cplusplus
  }
#endif


#endif  //  }


