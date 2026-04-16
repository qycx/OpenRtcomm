

#ifndef  __TRACELOG_H__
#define  __TRACELOG_H__	//  {

#ifdef  __cplusplus
		extern  "C"  {
#endif


#define		QY_TRACE_NOLOGTOFILE		(  1  <<  31  )
//  #define		QY_TRACE_ALL				(  0xFFFF  )

void				setTraceFilters(  int  *  pIds,  unsigned  int  cnt  );
void				setTraceLogOpen(  BOOL  bFlg );
void				setTraceLogToFile(  BOOL  bFlg  );
BOOL				bTrace(  int  id  );
TCHAR	*			getDebugLogFileName(  );
TCHAR	*			setDebugLogFileName(  LPCTSTR  fileName  );
void				setDebugLogFileModuleName(  );
int					traceLogA(  char  *  fmt,  ...  );

char  *  qyDisplaylTime(  char  *  buf,  char  *  displayBuf,  unsigned  int  size  );



#ifdef  __cplusplus  
		}  
#endif



#endif  //  }

