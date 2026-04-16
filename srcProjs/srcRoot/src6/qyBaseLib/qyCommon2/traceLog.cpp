

#include	"qyPrecomp.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	<WinSock2.h>
#include	<windows.h>
#include	"qyCommon.h"
#include	"commondefs.h"
#include	"qyCommon\\commonfunc.h"
#include	<tchar.h>
#include	<time.h>
//#include	"qyCommCommon.h"

#include	"traceLog.h"

#ifdef  __DEBUG__
		#undef  LOGDIR
		#define	LOGDIR						"c:\\tttBbb"		//  2007/12/10， 因为一台机器的目录坏了，要改个名字才能用，故用tttBbb
#endif


// traceFilterId为允许log的id, spiQyTraceFilterIds须指向一整数数组，数组须以0结尾.
 static  int	*		spiQyTraceFilterIds		=	NULL;
 static  unsigned  int	siQyTraceFilterCnt		=	0;
 static  TCHAR			sDebugLogFile[256] = { 0 };// (TCHAR*)_T("");
 static  BOOL			sbTraceLogFlg			=	TRUE;
 static  BOOL			sbTraceLogToFile		=	FALSE;

 
 extern  "C"  void  setTraceFilters(  int * pIds,  unsigned  int  cnt  )
{
	 spiQyTraceFilterIds	=	pIds;
	 siQyTraceFilterCnt		=	cnt;	 
}



 extern  "C"  void  setTraceLogOpen(  BOOL  bFlg )
{
	 sbTraceLogFlg		=	bFlg;
}

 //  2010/05/10
 extern  "C"  void  setTraceLogToFile(  BOOL  bFlg  )
{
	sbTraceLogToFile  =  bFlg;
}


 extern  "C"  BOOL  bTrace(  int  id  )
{
	 unsigned  int	i  =  0;

	 for  (  i  =  0;  i  <  siQyTraceFilterCnt;  i  ++  )  {
		  if  (  id  ==  spiQyTraceFilterIds[i]  )  return  TRUE;
	 }

	 return  FALSE;
}



 extern  "C"  TCHAR  *  setDebugLogFileName(  LPCTSTR  fileName  )
{
	 if  (  lstrlen(  fileName  )  >=  mycountof(  sDebugLogFile  )  )  return  NULL;
	 //  lstrcpy(  sDebugLogFile,  fileName  );
	 safeTcsnCpy(  fileName,  sDebugLogFile,  mycountof(  sDebugLogFile  )  );
	 return  sDebugLogFile;
}

 extern  "C"  void  setDebugLogFileModuleName(  )
{
		TCHAR		moduleFileName[MAX_PATH  +  1];
		//  char		pathBuf[MAX_PATH  +  1];
		TCHAR	*	filePart							=	NULL;
		TCHAR		debugLogFileName[MAX_PATH  +  1];
		TCHAR	*	ptr									=	NULL;


		GetModuleFileName(  NULL,  moduleFileName,  mycountof(  moduleFileName  )  );
		//  GetLongPathName(
		//  GetFullPathName(  moduleFileName,  mycountof(  pathBuf  ),  pathBuf,  &filePart  );
		filePart  =  _tcsrchr(  moduleFileName,  _T(  '\\'  )  );
		if  (  !filePart  )  goto  errLabel;
		filePart  ++  ;

		//  wsprintf(  debugLogFileName,  "%s.log",  filePart  );
		safeTcsnCpy(  filePart,  debugLogFileName,  mycountof(  debugLogFileName  )  );
		tTrim(  debugLogFileName  );

		//  这里将.exe后缀去除
		ptr  =  _tcsrchr(  debugLogFileName,  _T(  '.'  )  );
		if  (  ptr  &&  !_tcsicmp(  ptr,  _T(  ".exe"  )  )  )  {
			*ptr  =  0;
		}

		safeTcsnCpy(  _T(  ".log"  ),  debugLogFileName  +  lstrlen(  debugLogFileName  ),  mycountof(  debugLogFileName  )  -  lstrlen(  debugLogFileName  )  );
		setDebugLogFileName(  debugLogFileName  );

errLabel:
		return;
}

 extern  "C"  TCHAR  *  getDebugLogFileName(  )
{
	 return  sDebugLogFile;
}


 ////////////////////////
 // globals 
 const __int64 _onesec_in100ns = (__int64)10000000; 
 //int   timezone, _timezone, altzone; 
 //int   daylight; 
 //  char *tzname[2]; 
  
  
 /* __int64 <--> FILETIME */ 
 static __int64 wce_FILETIME2int64(FILETIME f) 
 { 
         __int64 t; 
  
         t = f.dwHighDateTime; 
         t <<= 32; 
         t |= f.dwLowDateTime; 
         return t; 
 } 
  
 static FILETIME wce_int642FILETIME(__int64 t) 
 { 
         FILETIME f; 
  
         f.dwHighDateTime = (DWORD)((t >> 32) & 0x00000000FFFFFFFF); 
         f.dwLowDateTime  = (DWORD)( t        & 0x00000000FFFFFFFF); 
         return f; 
 } 
  
 /* FILETIME utility */ 
 static FILETIME wce_getFILETIMEFromYear(WORD year) 
 { 
         SYSTEMTIME s={0}; 
         FILETIME f; 
  
         s.wYear      = year; 
         s.wMonth     = 1; 
         s.wDayOfWeek = 1; 
         s.wDay       = 1; 
  
         SystemTimeToFileTime( &s, &f ); 
         return f; 
 } 
  
 static time_t wce_getYdayFromSYSTEMTIME(const SYSTEMTIME* s) 
 { 
         __int64 t; 
         FILETIME f1, f2; 
  
         f1 = wce_getFILETIMEFromYear( s->wYear ); 
         SystemTimeToFileTime( s, &f2 ); 
  
         t = wce_FILETIME2int64(f2)-wce_FILETIME2int64(f1); 
  
         return (time_t)((t/_onesec_in100ns)/(60*60*24)); 
 } 
  
 /* tm <--> SYSTEMTIME */ 
 static SYSTEMTIME wce_tm2SYSTEMTIME(struct tm *t) 
 { 
         SYSTEMTIME s; 
  
         s.wYear      = t->tm_year + 1900; 
         s.wMonth     = t->tm_mon  + 1; 
         s.wDayOfWeek = t->tm_wday; 
         s.wDay       = t->tm_mday; 
         s.wHour      = t->tm_hour; 
         s.wMinute    = t->tm_min; 
         s.wSecond    = t->tm_sec; 
         s.wMilliseconds = 0; 
  
         return s; 
 } 
  
 static struct tm wce_SYSTEMTIME2tm(SYSTEMTIME *s) 
 { 
         struct tm t; 
  
         t.tm_year  = s->wYear - 1900; 
         t.tm_mon   = s->wMonth- 1; 
         t.tm_wday  = s->wDayOfWeek; 
         t.tm_mday  = s->wDay; 
         t.tm_yday  = wce_getYdayFromSYSTEMTIME(s); 
         t.tm_hour  = s->wHour; 
         t.tm_min   = s->wMinute; 
         t.tm_sec   = s->wSecond; 
         t.tm_isdst = 0; 
  
         return t; 
 } 
  
 /* FILETIME <--> time_t */ 
 time_t wce_FILETIME2time_t(const FILETIME* f) 
 { 
         FILETIME f1601, f1970; 
         __int64 t, offset; 
  
         f1601 = wce_getFILETIMEFromYear(1601); 
         f1970 = wce_getFILETIMEFromYear(1970); 
  
         offset = wce_FILETIME2int64(f1970) - wce_FILETIME2int64(f1601); 
  
         t = wce_FILETIME2int64(*f); 
  
         t -= offset; 
         return (time_t)(t / _onesec_in100ns); 
 } 
  
 FILETIME wce_time_t2FILETIME(const time_t t) 
 { 
         FILETIME f, f1970; 
         __int64 time; 
  
         f1970 = wce_getFILETIMEFromYear(1970); 
  
         time = t; 
         time *= _onesec_in100ns; 
         time += wce_FILETIME2int64(f1970); 
  
         f = wce_int642FILETIME(time); 
  
         return f; 
 } 
  
 /* time.h difinition */ 
#ifdef  __WINCE__
 time_t mytime( time_t *timer ) 
 { 
         SYSTEMTIME s; 
         FILETIME   f; 
  
         if( timer==NULL ) return 0; 
  
         GetSystemTime( &s ); 
  
         SystemTimeToFileTime( &s, &f ); 
  
         *timer = wce_FILETIME2time_t(&f); 
         return *timer; 
 } 

 DWORD  mytimeGetTime(VOID)
{
	return  GetTickCount(  );	
}

  
 struct tm *mylocaltime( const time_t *timer ) 
 { 
         SYSTEMTIME ss, ls, s; 
         FILETIME   sf, lf, f; 
         __int64 t, diff; 
         static struct tm tms; 
  
         GetSystemTime(&ss); 
         GetLocalTime(&ls); 
  
         SystemTimeToFileTime( &ss, &sf ); 
         SystemTimeToFileTime( &ls, &lf ); 
  
         diff = wce_FILETIME2int64(sf) - wce_FILETIME2int64(lf); 
  
         f = wce_time_t2FILETIME(*timer); 
         t = wce_FILETIME2int64(f) - diff; 
         f = wce_int642FILETIME(t); 
  
         FileTimeToSystemTime( &f, &s ); 
  
         tms = wce_SYSTEMTIME2tm(&s); 
  
         return &tms; 
 } 
  
 #endif

 time_t mymktime(struct tm* pt) 
 { 
         SYSTEMTIME ss, ls, s; 
         FILETIME   sf, lf, f; 
         __int64 diff; 
  
         GetSystemTime(&ss); 
         GetLocalTime(&ls); 
         SystemTimeToFileTime( &ss, &sf ); 
         SystemTimeToFileTime( &ls, &lf ); 
  
         diff = (wce_FILETIME2int64(lf)-wce_FILETIME2int64(sf))/_onesec_in100ns; 
  
         s = wce_tm2SYSTEMTIME(pt); 
         SystemTimeToFileTime( &s, &f ); 
         return wce_FILETIME2time_t(&f) - (time_t)diff; 
 } 
  
 struct tm *mygmtime(const time_t *t) 
 { 
         FILETIME f; 
         SYSTEMTIME s; 
         static struct tm tms; 
          
         f = wce_time_t2FILETIME(*t); 
         FileTimeToSystemTime(&f, &s); 
         tms = wce_SYSTEMTIME2tm(&s); 
         return &tms; 
 } 
  
 char* myctime( const time_t *t ) 
 { 
         // Wed Jan 02 02:03:55 1980\n\0 
         static char buf[30]={0}; 
         char week[] = "Sun Mon Tue Wed Thr Fri Sat "; 
         char month[]= "Jan Feb Mar Apl May Jun Jul Aug Sep Oct Nov Dec "; 
         struct tm tms; 
  
         tms = *mylocaltime(t); 
  
         strncpy( buf,    week+tms.tm_wday*4, 4 ); 
        strncpy( buf+4,  month+tms.tm_mon*4, 4 ); 
         sprintf( buf+8,  "%02d ", tms.tm_mday ); 
         sprintf( buf+11, "%02d:%02d:%02d %d\n",  
                 tms.tm_hour, tms.tm_min, tms.tm_sec, tms.tm_year+1900 ); 
         return buf; 
 } 
  
 char *myasctime(const struct tm *pt) 
 { 
         static char buf[30]={0}; 
         char week[] = "Sun Mon Tue Wed Thr Fri Sat "; 
         char month[]= "Jan Feb Mar Apl May Jun Jul Aug Sep Oct Nov Dec "; 
  
         strncpy( buf,    week+pt->tm_wday*4, 4 ); 
         strncpy( buf+4,  month+pt->tm_mon*4, 4 ); 
        sprintf( buf+8,  "%02d ", pt->tm_mday ); 
         sprintf( buf+11, "%02d:%02d:%02d %d\n",  
                 pt->tm_hour, pt->tm_min, pt->tm_sec, pt->tm_year+1900 ); 
         return buf; 
 } 
 // globals 
 



  //  The system time is expressed in Coordinated Universal Time (UTC).
 //  2007/09/23, ???°?????????í???§??????????±????±???????ó??????????UTC
 extern  "C"  int  getCurTime(  char  *  timeBuf  )
{
	SYSTEMTIME  when;
	
	GetSystemTime(  &when  );

	sprintf(  timeBuf,  
				"%04d%02d%02d%02d%02d%02d", 
					when.wYear,  
						when.wMonth,  
							when.wDay,  
								when.wHour,  
									when.wMinute,  
										when.wSecond  );

	return  0;

}


 extern  "C"  int  getTimelStr(  time_t  t,  char  *  timeBuf,  unsigned  int  size  )
{
	 struct  tm		*	p		=	NULL;
	 struct  tm			when;
     
	 if  (  !(  p  =  mylocaltime(  &t  )  )  )  return  -1;

     when  =  *p;		 
	 _snprintf(  timeBuf,  size,  "%04d%02d%02d%02d%02d%02d",  when.tm_year  +  1900,
				when.tm_mon  +  1,  when.tm_mday,  when.tm_hour,  when.tm_min,
		 		when.tm_sec  );        
   
	 return  0;

}



   extern  "C"  time_t  gettTimeByStr(  char  *  timeBuf  )
{
	int			iErr	=	-1;
	char		buf[5];
	struct tm	tm;
	time_t		t1 = 0;

	if  (  !timeBuf  ||  !timeBuf[0]  )  return  0;		//  2011/08/02

	memset( &tm, 0, sizeof( struct tm ) );
	memcpy( buf, timeBuf, 4 );
	buf[4] = 0;
	tm.tm_year += atol( buf ) - 1900;
	memcpy( buf, timeBuf + 4, 2 );
	buf[2] = 0;
	tm.tm_mon += atol( buf ) - 1;
	memcpy( buf, timeBuf + 6, 2 );
	tm.tm_mday += atol( buf );
	memcpy( buf, timeBuf + 8, 2 );
	tm.tm_hour += atol( buf );
	memcpy( buf, timeBuf + 10, 2 );
	tm.tm_min += atol( buf );
	memcpy( buf, timeBuf + 12, 2 );
	tm.tm_sec += atol( buf );

	t1  =  mymktime( &tm );
	if  (  t1  ==  -1  )  goto  errLabel;


	TIME_ZONE_INFORMATION	tzi;
	DWORD					dwRet;

	dwRet  =  GetTimeZoneInformation(  &tzi  );

	if  (  dwRet == TIME_ZONE_ID_STANDARD  ||  dwRet  ==  TIME_ZONE_ID_UNKNOWN  )  ;
	else  if  (  dwRet  ==  TIME_ZONE_ID_DAYLIGHT  )  ;
	else  goto  errLabel;

	t1  =  t1  -  tzi.Bias  *  60;

	iErr  =  0;
    
errLabel:
	  
	return  iErr  ?  iErr  :  t1;

}


 extern  "C"  char  *  qyDisplayTime(  char  *  buf1,  char  *  displayBuf,  unsigned  int  size  )
{
	char		tmpBuf[128]	=	"";
	char	*	buf			=	tmpBuf;
	char	*	ptr			=  displayBuf;
	time_t		t;

	if  (  size  <  20  ||  strlen(  buf1  )  <  14  ||  !bQyTimeValid(  buf1  )  )  return  NULL;

	t  =  gettTimeByBuf(  buf1  );
	if  (  t  ==  -1  )  return  NULL;

	getTimelStr(  t,  tmpBuf,  mycountof(  tmpBuf  )  );

	memcpy(  displayBuf,  buf,  4  );  displayBuf  +=  4;	buf  +=  4;
	displayBuf[0]  =  '-';  displayBuf  ++;
	memcpy(  displayBuf, buf, 2 ); displayBuf += 2; buf += 2;
	displayBuf[0]  =  '-';  displayBuf  ++;
	memcpy(  displayBuf, buf, 2 ); displayBuf += 2; buf += 2;
	displayBuf[0] = ' '; displayBuf ++;
	memcpy(  displayBuf, buf, 2 ); displayBuf += 2; buf += 2;
	displayBuf[0] = ':'; displayBuf ++;
	memcpy(  displayBuf, buf, 2 ); displayBuf += 2; buf += 2;
	displayBuf[0] = ':'; displayBuf ++;
	memcpy(  displayBuf, buf, 2 ); displayBuf += 2; buf += 2;
	displayBuf[0] = '\0';
	
	return ptr;

}

 extern  "C"  char  *  qyDisplaylTime(  char  *  buf,  char  *  displayBuf,  unsigned  int  size  )
{
	char	*	ptr			=  displayBuf;
	//  time_t		t;

	if  (  size  <  20  ||  strlen(  buf  )  <  14  ||  !bQyTimeValid(  buf  )  )  return  NULL;

	memcpy(  displayBuf,  buf,  4  );  displayBuf  +=  4;	buf  +=  4;
	displayBuf[0]  =  '-';  displayBuf  ++;
	memcpy(  displayBuf, buf, 2 ); displayBuf += 2; buf += 2;
	displayBuf[0]  =  '-';  displayBuf  ++;
	memcpy(  displayBuf, buf, 2 ); displayBuf += 2; buf += 2;
	displayBuf[0] = ' '; displayBuf ++;
	memcpy(  displayBuf, buf, 2 ); displayBuf += 2; buf += 2;
	displayBuf[0] = ':'; displayBuf ++;
	memcpy(  displayBuf, buf, 2 ); displayBuf += 2; buf += 2;
	displayBuf[0] = ':'; displayBuf ++;
	memcpy(  displayBuf, buf, 2 ); displayBuf += 2; buf += 2;
	displayBuf[0] = '\0';
	
	return ptr;

}



  extern  "C"  static  int  sTraceLog2Ex(  LPCTSTR  filePart1,  char  *  str1,  char  *  str2  )
{
	#if  defined(__WITHOUT_DEBUG_LOG__)  
		 return 0;
	#else

		int					iErr						=	-1;
		TCHAR				fileNameBuf[257];	
		char				timeBuf[32];
		char				displayBuf[64];
		unsigned long		nWritten					=	0;
		DWORD				processId;
		char				buf[256];
		TCHAR			*	ptr							=	NULL;
		FILE			*	fp							=	NULL;
	

		getCurTime(  timeBuf  );
		if  (  !qyDisplayTime(  timeBuf,  displayBuf,  sizeof(  displayBuf  )  )  )  goto  errLabel;
		processId  =  GetCurrentProcessId(  );
		GetModuleFileName(  NULL,  fileNameBuf,  mycountof(  fileNameBuf  )  );
		
		TCHAR  *  filePart;

		filePart  =  _tcsrchr(  fileNameBuf,  _T(  '\\'  )  );
		if  (  !filePart  )  goto  errLabel;
		filePart  ++  ;

		if  (  (  ptr  =  _tcsrchr(  filePart,  _T(  '.'  )  )  )  &&  !_tcsicmp(  ptr,  _T(  ".exe"  )  )  )  *ptr  =  0;
		_snprintf(  buf,  mycountof(  buf  ),  "%6lu|%5lu|%S",  processId,  GetCurrentThreadId( ),  filePart  );


		if  (  !filePart1  ||  !filePart1[0]  )  filePart1  =  _T(  COMMONERRLOGFILE  );
		//
		#if  1
			_sntprintf(  fileNameBuf,  mycountof(  fileNameBuf  ),  _T(  "%s\\%s"  ),  _T(  LOGDIR  ),  filePart1  );
		#else
			//  sprintf(  fileNameBuf,  "%s/%s%d",  LOGDIR,  filePart1  );
		#endif

		//
		TCHAR	tBuf[512];
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%S"  ),  displayBuf  );
		OutputDebugString(  tBuf  );
		OutputDebugString(  _T(  "  "  )  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%S"  ),  str1  );
		OutputDebugString(  tBuf  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%S"  ),  str2  );
		OutputDebugString(  tBuf  );
		OutputDebugString(  _T(  "\n"  )  );

		if  (  sbTraceLogToFile  )  {
			if  (  !(  fp  =  _tfopen(  fileNameBuf,  _T(  "a"  )  )  )  )  goto  errLabel;
			fprintf(  fp,  "%s|%s|%s%s\n",  displayBuf,  buf,  str1,  str2  );
		}

		iErr  =  0;	

errLabel:
		
		if  (  fp  )  fclose(  fp  );

		return  iErr;

	#endif

}




 extern  "C"  int  traceLogEx(  LPCTSTR  filePart,  char  *  fmt,  ...  )
{
	
	#if  defined(__WITHOUT_DEBUG_LOG__)
		 return 0;
	#else

		if  (  !sbTraceLogFlg  )  return  0;

		va_list			args;
		char			buf[4096]			=	"";
		int				n					=	0;
				
		va_start(  args,  fmt  );

		n  =  _vsnprintf(  buf,  sizeof(  buf  )  -  1,  fmt,  args  );
		if  (  n  >  sizeof(  buf  ) - 1  )  {
			sTraceLog2Ex(  filePart,  "traceLogA(  ):  buf too small to contain the output string.",  ""  );
			}
		else  {
			sTraceLog2Ex(  filePart,  buf,  ""  );
		}
	
		va_end(  args  );
	
		return 0;

	#endif
}

 extern  "C"  int  traceLogA(  char  *  fmt,  ...  )
{
 
	#if  defined(__WITHOUT_DEBUG_LOG__)
		 return 0;
	#else

		if  (  !sbTraceLogFlg  )  return  0;

		va_list			args;
		char			buf[2048]			=	"";
		int				n					=	0;
				
		va_start(  args,  fmt  );
		n  =  _vsnprintf(  buf,  sizeof(  buf  )  -  1,  fmt,  args  );
		va_end(  args  );
	
		buf[mycountof(  buf  )  -  1]  =  0;

		sTraceLog2Ex(  getDebugLogFileName(  ),  buf,  ""  );
				
		return 0;

	#endif
}


 ///////////////// 

  extern  "C"  int  traceLog(  TCHAR  *  fmt,  ...  )
{
 
	#if  defined(__WITHOUT_DEBUG_LOG__)
		 return 0;
	#else

		if  (  !sbTraceLogFlg  )  return  0;

		va_list				args;
		int					n							=	0;
			
		int					iErr						=	-1;
		char				timeBuf[32];
		char				displayBuf[64];
		TCHAR			*	ptr							=	NULL;
		FILE			*	fp							=	NULL;
		TCHAR				tBuf[512]					=	_T(  ""  );
	
		if  (  sbTraceLogToFile  )  {
			TCHAR		*		filePart1			=	getDebugLogFileName(  );

			#if  1
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\\%s"  ),  _T(  LOGDIR  ),  filePart1  );
			#else
					//  sprintf(  fileNameBuf,  "%s/%s%d",  LOGDIR,  filePart1  );
			#endif

			if  (  !(  fp  =  _tfopen(  tBuf,  _T(  "a"  )  )  )  )  goto  errLabel;			
		}

		getCurTime(  timeBuf  );
		if  (  !qyDisplayTime(  timeBuf,  displayBuf,  sizeof(  displayBuf  )  )  )  goto  errLabel;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%S"  ),  displayBuf  );
		OutputDebugString(  tBuf  );
		OutputDebugString(  _T(  "  "  )  );
		if  (  fp  )  {
			_ftprintf(  fp,  _T(  "%s"  ),  tBuf  );
		}

		TCHAR  *  filePart;
		GetModuleFileName(  NULL,  tBuf,  mycountof(  tBuf  )  );
		filePart  =  _tcsrchr(  tBuf,  _T(  '\\'  )  );
		if  (  !filePart  )  goto  errLabel;
		filePart  ++  ;
		if  (  (  ptr  =  _tcsrchr(  filePart,  _T(  '.'  )  )  )  &&  !_tcsicmp(  ptr,  _T(  ".exe"  )  )  )  *ptr  =  0;
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "|%6lu|%5lu|%s"  ),  GetCurrentProcessId(  ),  GetCurrentThreadId( ),  filePart  );
		tBuf[mycountof(  tBuf  )  -  1]  =  0;
		OutputDebugString(  tBuf  );
		OutputDebugString(  _T(  "  "  )  );
		if  (  fp  )  {
			_ftprintf(  fp,  _T(  "%s"  ),  tBuf  );
		}

		va_start(  args,  fmt  );
		n  =  _vsntprintf(  tBuf,  mycountof(  tBuf  )  -  1,  fmt,  args  );
		va_end(  args  );

		tBuf[mycountof(  tBuf  )  -  1]  =  0;
		OutputDebugString(  tBuf  );
		OutputDebugString(  _T(  "\n"  )  );
		if  (  fp  )  {
			_ftprintf(  fp,  _T(  "%s"  ),  tBuf  );
			_ftprintf(  fp,  _T(  "\n"  )  );
		}

		iErr  =  0;	

errLabel:
		
		if  (  fp  )  fclose(  fp  );

		return 0;

	#endif
}

