
#ifndef  __COMMONFUNC1_H__
#define  __COMMONFUNC1_H__  /*  {  */

#ifdef  __cplusplus
  extern  "C"  {
#endif



extern  int			myArgc;
extern  char  *		myArgv[];
int					getArgcv(  char  *  prog,  char  *  lpCmdLine  );


int					qyIsSpace(  int  c  );
int					qyIsAlpha(  int  c  );
#define				asrIsSpace(  c  )		qyIsSpace(  c  )	
int					qyIsDigit(  int  c  );
int					qyIsXdigit(  int  c  );




#ifdef __cplusplus
  }
#endif

#endif  /*  }  */

