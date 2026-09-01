
#ifndef  __QYDEBUGFUNC_H__
#define  __QYDEBUGFUNC_H__	/* { */

#ifdef  __cplusplus
 extern "C" {
#endif


typedef  struct  __qyLogCtx_t				{
				 unsigned  char				ucbLogOn;
				 char						filePart[256];
				 QY_REG						reg;
				 char						regValName[32  +  1];
}		 QY_LOG_CTX;


#define		CONST_qyTraceFilterIdCf			100

#define		CONST_qyTraceFilterIdBase		10000



int  traceInfo(  void  *  pLogCtx,  char  *  fmt,  ... );
int  traceInReg(  void  *  pLogCtxParam,  char  *  fmt,  ...  );



#ifdef  __cplusplus
 }
#endif

#endif  /* }  */


