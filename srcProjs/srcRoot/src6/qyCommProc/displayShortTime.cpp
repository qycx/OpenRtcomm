

#include	"stdafx.h"
#include	<WinSock2.h>
#include	<mmsystem.h>

#include	"qmCommon.h"



//
 char  *  displayShortTime(  time_t  t,  char  *  timeBuf,  unsigned  int  len  )
{
	char	timeBuf_t[CONST_qyTimeLen  +  1]	=	"";
	char	curTimeBuf[CONST_qyTimeLen  +  1]	=	"";
	char	displayBuf[128  +  1]				=	"";

	getCurTime(  curTimeBuf  );
	getTimeStr(  t,  timeBuf_t,  mycountof(  timeBuf_t  )  );

	qyDisplayTime(  timeBuf_t,  displayBuf,  mycountof(  displayBuf  )  );

	if  (  _strnicmp(  timeBuf_t,  curTimeBuf,  4  )  )  safeStrnCpy(  displayBuf,  timeBuf,  min(  len,  4  +  1  )  );
	else  if  (  _strnicmp(  timeBuf_t  +  4,  curTimeBuf  +  4,  4  )  )  safeStrnCpy(  displayBuf  +  5,  timeBuf,  min(  len,  5  +  1  )  );
	else  safeStrnCpy(  displayBuf  +  11,  timeBuf,  min(  len,  8  +  1  )  );

	return  timeBuf;
}



