
#ifndef  __COMMONFUNC_H__
#define  __COMMONFUNC_H__

#ifdef  __cplusplus
  extern  "C"  {
#endif

#ifdef WIN32
  #define	LOGDIR						"c:\\tttBbb"
#else
  #define	LOGDIR						"/tttBbb"
#endif

#define		COMMONERRLOGFILE			"err.log"
#define		COMMANDBUFSIZE				255

#define		DBG_PRESCAN 				0x01
#define		DBG_ANY						0x02


//  注意：debugLog 已被traceLog替代。 
#define		debugLog					traceLogA
int		traceLogA(  char  *  fmt,  ...  );
int		traceLogEx(  LPCTSTR  filePart,  char  *  fmt,  ...  );

int  traceLog(  TCHAR  *  fmt,  ...  );

void	clearDebugLog(  );

#ifndef  __WINCE__
	#define		mytime(  t  )	time(  t  )
	#define		mytimeGetTime(  )  timeGetTime(  )
	#define		mylocaltime(  time  )  localtime(  time  )
	#define		my_fseeki64(  stream,  offset,  origin  )	_fseeki64(  stream,  offset,  origin  )
#else
	#ifdef  __TEST__
		#define		mytime(  t  )	time(  t  )
		#define		mytimeGetTime(  )  timeGetTime(  )
		#define		mylocaltime(  time  )  localtime(  time  )
	#else
		time_t mytime( time_t *timer );
		DWORD  mytimeGetTime(VOID);
		struct tm *mylocaltime( const time_t *timer ) ;
	#endif

	#define		my_fseeki64(  stream,  offset,  origin  )	fseek(  stream,  (  long  )offset,  origin  )

#endif

time_t mymktime(struct tm* pt); 
struct tm *mygmtime(const time_t *t); 

time_t gettTimeByStr(  char  *  timeBuf  );
#define	gettTimeByBuf(  timeBuf  )	gettTimeByStr(  timeBuf  )

int				getCurTime(  char  *  timeBuf  );
int  getTimelStr(  time_t  t,  char  *  timeBuf,  unsigned  int  size  );


char * qyDisplayTime( char *buf, char *displayBuf, unsigned int size );



#ifdef WIN32	/* { */

  #define	debuglog					debugLog
  int	setDebugLogFile(  char  *  fileName  );
  __declspec(  dllexport  )  int  commonlog(  char *  fmt,  ...  );
  //  __declspec(  dllexport  )  int  debugLog(  char  *  fmt,  ...  );
  __declspec(  dllexport  )  int  logErr(  char  *  fmt,  ...  );

#else	/* } WIN32 defined above,but  not defined below{ */

  int  commonlog(  char  *  fmt,  ...  );
  int  logErr(  char  *  fmt,  ...  );
  int  cSystem(  char  *  command  );
  void  showArg(  int  argc,  char  **  argv  );

#endif	/* } WIN32 not defined */

#include <stdio.h>
//  #include <sys/types.h>

#ifndef WIN32
#if  0
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <sys/time.h>
  #include <unistd.h>
  #include <sys/wait.h>
#endif
#endif

#if  0
#include <signal.h>
#include <errno.h>
#endif

#ifndef WIN32
  extern int errno;
#endif

#define		DEBUG_SERV_TCP_PORT			2000
#define		DEBUG_SERV_IP				"127.0.0.1"

#ifndef		SUCCESS
  #define	SUCCESS 					0
#endif
#ifndef  FAILURE 
  #define	FAILURE 					-1
#endif
#ifndef  NOTEXPECTED
  #define	NOTEXPECTED 				-2
#endif

#define		FOREGROUND_DEBUG			1

#define		NETERRLOG					COMMONERRLOGFILE 

/**/
 extern  void  showErrNo(  int  errNo  );
 extern  FILE  *  openDebugLogFp(  );	
 extern  int  err_record(  FILE  *  fp,  char  err_buf[]  );
 extern  int  i_serv_tcp(  );
 extern  int  i_cli_tcp(  );
 extern  short  s_serv_getservport(  );
 extern  short  s_cli_getservport(  );
 extern  char  *  pc_getservaddr(  char  *  buf  );
 extern  int  serv_doit(  int  sockfd  );
 extern  int  cli_doit(  int  sockfd  );
/**/


void showArg( int argc, char *argv[] );

//
#define		PI							3.1415926535

#define		A2PI(  x  )					(  (  x  )  /  180.  *  PI  )
#define		PI2A(  x  )					(  (  x  )  /  PI  *  180.  )

#ifdef __cplusplus
  }
#endif


#endif
