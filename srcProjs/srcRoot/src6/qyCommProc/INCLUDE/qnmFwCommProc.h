

#ifndef  __QNMFWCOMMPROC_H__
#define  __QNMFWCOMMPROC_H__	/*  {  */

#ifdef  __cplusplus
  extern  "C"  {
#endif


int  fwReplaceChrInStr(  char  c,  char  *  str,  unsigned  int  size  );
int  filterStr2Display(  TCHAR  *  str,  unsigned  int  cnt  );

int  fwFilterBuf(  char  *  strSearch,  char  *  buf,  unsigned  int  cnt  );
int  fwFilterTBuf(  TCHAR  *  strSearch,  TCHAR  *  tBuf,  unsigned  int  cnt  );

int  escapeTStr(  TCHAR  *  str,  unsigned  int  cnt  );
int  unescapeTStr(  TCHAR  *  str,  unsigned  int  cnt  );


#ifdef  __cplusplus
  }
#endif


#endif  /*  }  */

