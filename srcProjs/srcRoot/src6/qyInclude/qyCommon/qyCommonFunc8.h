
#ifndef  __QYCOMMONFUNC8_H__
#define  __QYCOMMONFUNC8_H__	/*  {  */

#ifdef  __cplusplus
 extern  "C"  {
#endif

int		 qyX2C(  char * xBuf  );
char  *  qyC2X(  char c,  char * xBuf,  int size  );
char  *  qyBuf2X(  char  *  buf,  unsigned  int  len,  char  *  xBuf  );
char  *  qyX2Buf(  char  *  xBuf,  char  *  buf,  unsigned  int  len  );
int		 qyXStr2L(  char * buf,  long  *  pL  );
char  *  qyL2XStr(  long l,  char * buf,  int  size  );


#ifdef  __cplusplus
 }
#endif

#endif  /*  }  */

