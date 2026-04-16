
#include	"stdafx.h"
#include	<Windows.h>
//#include	<mmeapi.h>
#include	<mmsystem.h>
#include	<time.h>
#include	"qmOpenCommon.h"
#include <lmcons.h>
#include	"fileFunc_open.h"
#include <tchar.h>
#include	<stdio.h>
#include	"qytcharcommproc.h"
#include	"timeFunc_open.h"


//
 extern  "C"  int  getTimelStr_open(  time_t  t,  char  *  timeBuf,  unsigned  int  size  )
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


