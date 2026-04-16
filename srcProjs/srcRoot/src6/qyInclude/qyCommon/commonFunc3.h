
#ifndef __COMMONFUNC3_H__
#define __COMMONFUNC3_H__	/* { */

#ifdef __cplusplus
 extern "C" {
#endif

unsigned  char  *  trimRight(  unsigned  char  *  str  );
char  *  asrGetFullPath(  char  *  path,  char  *  file,  char  *  buf,  unsigned  int  bufSize  );
//  int  getNetLogonLocalPath(  char  *  localPath  );
//  int  asrGetRegCfg(  char  *  rootKey,  char  *  cfgName,  char  *  cfgVal,  int  size  );
int  asrGetRegCfg(  LPCTSTR  rootKey,  LPCTSTR  cfgName,  char  *  cfgVal,  int  size  );
BOOL  bDirExists(  TCHAR  *  dir  );


#ifdef __cplusplus
 }
#endif

#endif /* } */

