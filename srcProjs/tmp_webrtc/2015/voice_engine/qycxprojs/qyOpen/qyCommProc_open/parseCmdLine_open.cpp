



#include	"stdafx.h"

#include	<stdlib.h>
#include	<tchar.h>
#include	<stddef.h>
#include	<mmsystem.h>

#include	"qdcOpenCommon.h"
#include	"parseCmdLine_open.h"

//
 int  parseCmdLine_open(  LPCTSTR  pCmdLine,  QmcAppParams_common  *  pParams  )
{
	int		iErr	=	-1;
		 
	 TCHAR	*	pT;
	 TCHAR	*	pT1;
	 TCHAR	*	pT2;
	 
	 if  (  !pParams  )  return  -1;

	 memset(  pParams,  0,  sizeof(  pParams[0]  )  );

	 //
	 TCHAR  *  pSym  =  _T(  "-aqm"  );
	 pT  =  (  TCHAR  *  )_tcsstr(  pCmdLine,  pSym  );
	 if  (  !pT  )  goto  errLabel;
	 pT  +=  lstrlen(  pSym  );
	 pParams->iSeqNoSelected_appObjPrefix  =  _ttol(  pT  );
	 _sntprintf(  pParams->appObjPrefix,  mycountof(  pParams->appObjPrefix  ),  _T(  "qm%d"  ),  pParams->iSeqNoSelected_appObjPrefix  );

	 //
	 pSym  =  _T(  "-tn="  );
	 pT  =  (  TCHAR  *  )_tcsstr(  pCmdLine,  pSym  );
	 if  (  !pT  )  goto  errLabel;
	 pT  +=  lstrlen(  pSym  );
	 pParams->tn_cliPipe  =  _ttol(  pT  );
	 

	 iErr  =  0;
errLabel:


	 return  iErr;
 }




