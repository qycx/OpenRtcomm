 

#include "qyCommon\\asrPrecomp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>


#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
 #include <windows.h>


#if 0
	#include <unistd.h>
	#include <process.h>
#endif


#include "commondefs.h"
#include "qyCommon\\commonfunc.h"

#include "qyCommon\\commonSock.h"


 //  
 static  int sgetcurtime(char *timebuf)
{
	 struct tm when;
     time_t now;
     
	 mytime(&now);
     when = *mylocaltime(&now);
	 sprintf(timebuf,"%04d%02d%02d%02d%02d%02d",when.tm_year+1900,
		 when.tm_mon+1,when.tm_mday,when.tm_hour,when.tm_min,
		 when.tm_sec);
        
   return 0;

}


extern "C" int commonlog(char *fmt,...)
{	
	va_list args;
	
	char filenamebuf[257];
	char timebuf[50];
	FILE *fperr;

	va_start(args,fmt);
	

#ifdef WIN32
	sprintf(filenamebuf,"%s\\%s",LOGDIR,COMMONERRLOGFILE);
#else
	sprintf(filenamebuf,"%s/%s",LOGDIR,COMMONERRLOGFILE);
#endif


	sgetcurtime(timebuf);
	if ( ( fperr = fopen( filenamebuf,"a" ) ) ) {
		fprintf(fperr,"%s|",timebuf);
		vfprintf(fperr,fmt,args);
		fprintf(fperr,"\n");
		fclose(fperr);
		}
	else 
		printf("fopen failed\n");


	va_end(args);
	return 0;
}


 extern "C" void clearDebugLog( )
{
	 return;

	char fileNameBuf[256];
	FILE *fp = NULL;

#ifndef __DEBUG__
	 return;
#else
 #ifdef WIN32
	sprintf(fileNameBuf,"%s\\%s",LOGDIR,COMMONERRLOGFILE);
 #else
	sprintf(fileNameBuf,"%s/%s%d",LOGDIR,COMMONERRLOGFILE,getpid());
 #endif
#endif

	fp = fopen( fileNameBuf,"w" );
	
	if ( fp ) fclose( fp );

	return;

}






#ifndef WIN32
 extern "C" int cSystem( char *command )
{
	extern  char **environ;
	int pid,status;

	if ( !command ) return -1;

	pid = fork();
	if ( pid==-1 ) 
		return -1;
	if ( pid==0 ) {
		char *argv[4];
		argv[0]="sh";
		argv[1]="-c";
		argv[2]=command;
		argv[3]=NULL;
		execve("/bin/sh",argv,environ);
		exit(-1);
		}
	do { 
		if ( waitpid(pid,&status,0)==-1 ) {
			if ( errno!=EINTR )
				return -1;
			} 
		else
			return status;
	} while( 1 );

	
} 

#endif



#ifndef WIN32
 int showReadErr( int tmpErrNo )
{
	switch( tmpErrNo ) {
		case EINTR:   
			logErr( "The call was interrupted by a signal before any data was read." );
			break;
		case EAGAIN:
			logErr( "Non-blocking  I/O  has  been selected using O_NONBLOCK and no data was  immediately available for reading." );
			break;
		case EIO:
			logErr( "I/O  error.  This will happen for example when the process is in a background process group, tries to read  from  its  controlling tty, and either it is ignoring or blocking SIGTTIN or its process  group is  orphaned.   It  may also occur when there is a low-level I/O error while reading from a  disk  or tape." );
			break;
		case EISDIR:
			logErr( "fd refers to a directory." );
			break;
		case EBADF:
			logErr( "fd  is  not a valid file descriptor or is not open for reading."  );
			break;
		case EINVAL:
			logErr( "fd is attached to an object  which  is  unsuitable for reading."  );
			break;
		case EFAULT:
			logErr( "buf is outside your accessible address space." );
			break;
		default:
			logErr( "unknown error happens during read()." );
			break;
		}
	return 0;
}
#endif


#ifndef WIN32
 extern "C" void showErrNo( int errNo )
{
	switch( errNo ) {
		case 0:
			debuglog("No error.");
			break;
		case EINTR:
			debuglog("Interruptted by signal.");
			break;
		case EACCES:
			debuglog("The calling process has no  access \
permissions needed to execute cmd.");
			break;
		case EFAULT:
			debuglog("The  address pointed to by arg.buf or \
arg.array isn't accessible.");
			break;
		case EIDRM:
			debuglog("The semaphore set was removed.");
			break;
		case EINVAL:
			debuglog("Invalid value for cmd or semid.");
			break;
		case EPERM:
			debuglog("The argument cmd has value IPC_SET or \
IPC_RMID but  the  calling process effective user-ID has insufficient \
privileges to execute the command.");
			break;
		case ERANGE:
			debuglog( "The argument cmd has value SETALL or \
SETVAL and." );
			break;
		case EAGAIN:
			debuglog( " The message can't be sent due to the \
msg_qbytes limit for the queue and IPC_NOWAIT was asserted in mgsflg." );
			break;
		case ENOMEM:
			debuglog( "The system has not enough memory \
to make a copy of the supplied msgbuf." );
			break;

		default:
			debuglog("Unknown error.\n");
			break;
		}

	return;

}

#endif


 extern  "C"  void  showArg(  int  argc,  char  *  argv[]  )
{
	int			i			=	0;
	char		buf[4096]	=	"";
	int			len			=	0;

	for  (  i  =  0;  i  <  argc;  i  ++  )  {
		 _snprintf(  buf  +  len,  sizeof(  buf  )  -  len,  "%s  ",  argv[i]  );
		 len  +=  strlen(  buf  +  len  );
	}

	traceLogA(  "%s",  buf  );

	return;

}

 







