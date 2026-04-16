
#include	"stdafx.h"

#include	<windows.h>
#include	<tchar.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyCommon.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qySnmpCommProc.h"
#include	"qnmCommProc.h"
#include	"qnmCustom.h"
#include	"qnmAssetsCommProc.h"
#include	"qwmDjCommProc.h"
#include	"qyTCharCommProc.h"


 extern  "C"  int  getQwmFileObj(  LPCTSTR  fileName,  char  *  objName,  char  *  val,  unsigned  int  size  )
{
	 int				iErr		=		-1;
	 FILE			*	fp			=		NULL;
	 long				lPos;
	 int				djEndLen	=		strlen(  CONST_qyFileObj_djEnd  );
	 int				objNameLen	=		strlen(  objName  );
	 char				buf[1024];
	 
	 if  (  !(  fp  =  _tfopen(  fileName,  _T(  "r"  )  )  )  )  goto  errLabel;

	 for  (  ;  ;  )  {
		  lPos  =  ftell(  fp  );
		  if  (  !fgets(  buf,  mycountof(  buf  ),  fp  )  )  goto  errLabel;
		  if  (  !_strnicmp(  buf,  CONST_qyFileObj_djEnd,  djEndLen  )  )  goto  errLabel;
		  if  (  _strnicmp(  buf,  objName,  objNameLen  )  )  continue;
		  break;
	 }

	 if  (  val  &&  size  )  {
		 trim(  buf  );
		 if  (  *(  buf  +  objNameLen  )  ==  '='  )  strncpy(  val,  buf  +  objNameLen  +  1,  size  );
		 else  strncpy(  val,  "",  size  );
	 }

	 iErr  =  0;
errLabel:
	 if  (  fp  )  fclose(  fp  );
	 return  iErr;
}


