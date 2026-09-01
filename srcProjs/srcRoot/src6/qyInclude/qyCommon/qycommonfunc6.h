
#ifndef  __QYCOMMONFUNC6_H__
#define  __QYCOMMONFUNC6_H__	/* { */

#ifdef  __cplusplus
  extern  "C"  {
#endif

unsigned  char  *  trimRight(  unsigned  char  *  str  );
char  *  asrGetFullPath(  char  *  path,  char  *  file,  char  *  buf,  unsigned  int  bufSize  );
char  *  asrMdFile(  char  *  fileName,  char  *  digest  );
//  BOOL  bQyGetSystemVersion(  int  *  piPlatformId,  TCHAR  *  productStr,  unsigned  int  size,  unsigned  char  *  pucbIsWinNt  );
//  BOOL  bQyGetSystemVersionEx(  int  *  piPlatformId,  char  *  pSystemBuf,  unsigned  int  uiSystemBufSize,  char  *  pServicePackBuf,  unsigned  int  uiServicePackBufSize,  unsigned  char  *  pucbIsWinNt  );
BOOL  bQyGetSystemVersionEx(  int  *  piPlatformId,  TCHAR  *  pSystemBuf,  unsigned  int  uiSystemBufSize,  TCHAR  *  pServicePackBuf,  unsigned  int  uiServicePackBufSize,  unsigned  char  *  pucbIsWinNt  );
BOOL  isWinNt(  void  );
//  int  asrGetRegCfg(  char  *  rootKey,  char  *  cfgName,  char  *  cfgVal,  int  size  );
//  int  qyGetRegCfg(  char  *  rootKey,  char  *  cfgName,  char  *  cfgVal,  int  size  );
unsigned  char  *  trimRight(  unsigned  char  *  str  );


#ifdef __cplusplus
 }
#endif

#endif /* } */

