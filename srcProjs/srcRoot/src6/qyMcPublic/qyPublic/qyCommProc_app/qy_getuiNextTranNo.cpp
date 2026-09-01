

#include	"stdafx.h"

#include	<windows.h>
#include	<tchar.h>
#include	<time.h>
#include	<stdlib.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyDefs_open.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCustom.h"
#include	"qyTCharCommProc.h"

#include	"tmpCeLib.h"




 //  2010/09/04
 extern  "C"  __declspec(  dllexport  )  unsigned  int	getuiNextTranNo(  void  *  p0,  long  val,  long  *  puiTranNo  )
{
	static	 long	suiTranNo		=	0;

	if  (  !val  )  val  =  1;
	if  (  !puiTranNo  )  puiTranNo  =  &suiTranNo;

	return  InterlockedExchangeAdd(  puiTranNo,  val  )  +  1;
}




