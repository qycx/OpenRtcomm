
#ifndef  __QYMD5PUBLIC_H__
#define	 __QYMD5PUBLIC_H__	/*  {  */

#ifdef  __cplusplus
  extern  "C"  {
#endif

#define		CONST_qyMd5Len				16


 // Digests a file and prints the result.
 //
 // digest is a buffer of 16 bytes.
//  BOOL  bQyGetStrMd5(  char  *  string,  char  *  digest,  unsigned  int  *  pLen  );
BOOL  bQyGetStrMd5_x(  char  *  string,  char  *  digest,  unsigned  int  *  pLen  );
BOOL  bQyGetFileMd5(  char  *  fileName,  char  *  digest,  unsigned  int  *  pLen  );
//  BOOL  bQwmGetFileMd5(  char  *  fileName,  char  *  digest,  unsigned  int  *  pLen  );
BOOL  bQwmGetFileMd5(  LPCTSTR  fileName,  char  *  digest,  unsigned  int  *  pLen  );


#ifdef  __cplusplus
  }
#endif

#endif	/*  }  */


