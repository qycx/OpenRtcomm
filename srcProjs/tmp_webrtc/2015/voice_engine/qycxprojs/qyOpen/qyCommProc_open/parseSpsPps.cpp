
#include	"stdafx.h"

#include	<stdlib.h>
#include	<tchar.h>
#include	<stddef.h>
#include	<mmsystem.h>

#include	"qdcOpenCommon.h"



 int  parseSpsPps(  char  *  spsPps,  int  spsPpsLen,  char  *  spsBuf,  unsigned  int  *  puiSpsSize,  char  *  ppsBuf,  unsigned  int  *  puiPpsSize,  char  *  kk,  unsigned  int  *  puiKkSize  )
{
	int			iErr	=	-1;
	 unsigned  char  buf[2048];
	 unsigned  int	naluLen  =  0;
	 unsigned  int	uiSpsLen	=	0;
	 unsigned  int	uiPpsLen	=	0;

	 //
	 if  (  spsPpsLen  >  sizeof(  buf  )  )  {
		 //  return  -1;
		 OutputDebugString(  _T(  "parseSpsPps :inputLen > sizeof(  buf  )"  )  );
	 }
	 //  int  len  =  spsPpsLen;
	 int  len  =  min(  spsPpsLen,  sizeof(  buf  )  );
	 if  (  !len  )  {
		 *puiSpsSize  =  0;
		 *puiPpsSize  =  0;
		 return  0;
	 }
	 memcpy(  buf,  spsPps,  len  );
	 
	 
	 int  ii;

	 unsigned  char  *  pStart  =  buf;
	 BOOL				bStart	=	FALSE;
	 BOOL			   bNextNalu  =  FALSE;
	 BOOL				bStartCode_4	=	FALSE;
	 for  (  ii  =  0;  ii  <  len  -  3;  ii  ++  )  {
		  if  (  buf[ii]  ==  0
			  &&  buf[ii  +  1]  ==  0
			  &&  buf[ii  +  2]  ==  0
			  &&  buf[ii  +  3]  ==  1  )
		  {
			  if  (  !bStart  )  {
				  bStart  =  TRUE;
				  pStart  =  buf  +  ii;
				  ii  +=  3;
				  continue;
				  }
			  else  {
					bNextNalu  =  TRUE;
					bStartCode_4  =  TRUE;
			  }
		  }
		  if  (  buf[ii]  ==  0
			  &&  buf[ii  +  1]  ==  0
			  &&  buf[ii  +  2]  ==  1  )
		  {
			  if  (  !bStart  )  {
				  bStart  =  TRUE;
				  pStart  =  buf  +  ii;
				  ii  +=  2;
				  continue;
				  }
			  else  {
				    bNextNalu  =  TRUE;
					bStartCode_4  =  FALSE;
			  }
		  }
		  //
		  if  (  !bNextNalu  )  continue;
		  //
		  naluLen  =  buf  +  ii  -  pStart;
		  if  (  naluLen  >  3  )  {
			  int  nalType  =  M_nalType(  pStart  );
			  switch  (  nalType  )  {
					  case  7:
						     if  (  naluLen  >  *puiSpsSize  )  goto  errLabel;
						     memcpy(  spsBuf,  pStart,  naluLen  );
							 uiSpsLen  =  naluLen;
							 break;
					  case  8:
						    if  (  naluLen  >  *puiPpsSize  )  goto  errLabel;
							memcpy(  ppsBuf,  pStart,  naluLen  );
							uiPpsLen  =  naluLen;
						    break;
					  default:
						     break;
			  }
		  }
		  //
		  bNextNalu  =  FALSE;
		  bStart  =  TRUE;
		  pStart  =  buf  +  ii;
		  if  (  bStartCode_4  )  ii  +=  3;
		  else  ii  +=  2;
		  continue;
	 }

	 //
	 if  (  bStart  )  {
		 naluLen  =  buf  +  len  -  pStart;
		  if  (  naluLen  >  3  )  {
			  int  nalType  =  M_nalType(  pStart  );
			  switch  (  nalType  )  {
					  case  7:
						     if  (  naluLen  >  *puiSpsSize  )  goto  errLabel;
						     memcpy(  spsBuf,  pStart,  naluLen  );
							 uiSpsLen  =  naluLen;
							 break;
					  case  8:
						    if  (  naluLen  >  *puiPpsSize  )  goto  errLabel;
							memcpy(  ppsBuf,  pStart,  naluLen  );
							uiPpsLen  =  naluLen;
						    break;
					  default:
						     break;
			  }
		  }
	 }

	 *puiSpsSize  =  uiSpsLen;
	 *puiPpsSize  =  uiPpsLen;

	 iErr  =  0;
errLabel:
	 
	 //
	 return  iErr;

}


//
int  makeSpsPps(  VH_stream  *  pVh_stream,  char  *  spsPpsParam,  unsigned  int  *  puiSize  )
{
	int  iErr  =  -1;
	char  spsPps[512]  =  "";
	int	spsLen  =  0;
	int  i;

	if  (  !pVh_stream  ||  !spsPps  ||  !puiSize  )  return  -1;

	if  (  pVh_stream->usCnt  )   {
		 if  (  pVh_stream->usCnt  >  mycountof(  pVh_stream->mems  )  )  goto  errLabel;
		 for  (  i  =  0;  i  <  pVh_stream->usCnt;  i  ++  )  {
			  if  (  spsLen  +  pVh_stream->mems[i].usLen  >  sizeof(  spsPps  )  )  {
				  //qyShowInfo1(  CONST_qyShowType_qwmComm,  NULL,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "htonAvTranInfo failed: spsLen too small"  )  );
				  goto  errLabel;
			  }
			  memcpy(  spsPps  +  spsLen,  pVh_stream->mems[i].spsPps,  pVh_stream->mems[i].usLen  );
			  spsLen  +=  pVh_stream->mems[i].usLen;
		 }
	}
	if  (  *puiSize  <  spsLen  )  goto  errLabel;
	memcpy(  spsPpsParam,  spsPps,  spsLen  );
	*puiSize  =  spsLen;

	iErr  =  0;
errLabel:

	if  (  !iErr  )  {

	}

	return  iErr;

}