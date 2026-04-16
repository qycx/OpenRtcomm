

//
#include	"stdafx.h"

#include	<stdlib.h>
#include	<tchar.h>
#include	<stddef.h>
#include	<mmsystem.h>

//
#include	"qmOpenCommon.h"

//
#include	"dyn_qisPublic.h"

//
DynLib_qisPublic  g_dynLib_qisPublic  =  {0};


//
//
int  load_dynLib_qisPublic(  )
{
	 int						iErr	=	-1;
	
	 TCHAR				tmpFileName[MAX_PATH  +  1];
	 TCHAR				pathBuf[MAX_PATH  +  1];
	 TCHAR			*	filePart;
	 HINSTANCE			hDll							=		NULL;
	 //PF_pCommonHandler	pf								=		NULL;
	 
	 DynLib_qisPublic  *  pFuncs  =  &g_dynLib_qisPublic;

	 //
	 GetModuleFileName(  NULL,  tmpFileName,  sizeof(  tmpFileName  )  /  sizeof(  tmpFileName[0]  )  );
	 if  (  !GetFullPathName(  tmpFileName,  sizeof(  pathBuf  )  /  sizeof(  pathBuf[0]  ),  pathBuf,  &filePart  )  )  goto  errLabel;
	 filePart[0]  =  0;

	 //
	 _sntprintf(  tmpFileName,  mycountof(  tmpFileName  ),  _T(  "%sqisPublic.dll"  ),  pathBuf  );
	 pFuncs->qisPublic.hDll  =  LoadLibrary(  tmpFileName  );
	 if  (  !pFuncs->qisPublic.hDll  )  goto  errLabel;

	 //
	 pFuncs->qisPublic.pf_qisPipeNew  =  (  PF_qisPipeNew  )GetProcAddress(  pFuncs->qisPublic.hDll,  "qisPipeNew"  );
	 pFuncs->qisPublic.pf_qisPipe_writeMsg  =  (  PF_qisPipe_writeMsg  )GetProcAddress(  pFuncs->qisPublic.hDll,  "qisPipe_writeMsg"  );
	 pFuncs->qisPublic.pf_initQisPipe  =  (  PF_initQisPipe  )GetProcAddress(  pFuncs->qisPublic.hDll,  "initQisPipe"  );
	 pFuncs->qisPublic.pf_qisPipeFree  =  (  PF_qisPipeFree  )GetProcAddress(  pFuncs->qisPublic.hDll,  "qisPipeFree"  );


	 //
	 pFuncs->qisPublic.bOk  =  TRUE;


	 //
	 _sntprintf(  tmpFileName,  mycountof(  tmpFileName  ),  _T(  "%sqyShowInfo.dll"  ),  pathBuf  );
	 pFuncs->qyShowInfo.hDll  =  LoadLibrary(  tmpFileName  );
	 if  (  !pFuncs->qyShowInfo.hDll  )  goto  errLabel;

	 //
	 pFuncs->qyShowInfo.pf_showInfo_open  =  (  PF_showInfo_open  )GetProcAddress(  pFuncs->qyShowInfo.hDll,  "showInfo_open0"  );
	 pFuncs->qyShowInfo.pf_set_who_showInfo  =  (  PF_set_who_showInfo  )GetProcAddress(  pFuncs->qyShowInfo.hDll,  "set_who_showInfo"  );

	 //
	 pFuncs->qyShowInfo.bOk  =  TRUE;


	 //
	 iErr  =  0;

errLabel:
	 return  iErr;
}


//
int  unload_dynLib_qisPublic(  )  
{
	//  FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );
	DynLib_qisPublic  *  pFuncs  =  &g_dynLib_qisPublic;


	//
	pFuncs->qyShowInfo.bOk  =  FALSE;
	//
	if  (  pFuncs->qyShowInfo.hDll  )  {
		FreeLibrary(  pFuncs->qyShowInfo.hDll  );
		pFuncs->qyShowInfo.hDll  =  NULL;
	}
	
	//
	pFuncs->qisPublic.bOk  =  FALSE;

	//
	if  (  pFuncs->qisPublic.hDll  )  {
		FreeLibrary(  pFuncs->qisPublic.hDll  );
		pFuncs->qisPublic.hDll  =  NULL;
	}

	return  0;
}




//
QIS_pipe  *  dyn_qisPipeNew(  )
{
	DynLib_qisPublic  *  pFuncs  =  &g_dynLib_qisPublic;
	if  (  !pFuncs  )  return  NULL;

	if  (  !pFuncs->qisPublic.bOk  )  return  NULL;

	return  pFuncs->qisPublic.pf_qisPipeNew(  );
}

int  dyn_qisPipeWriteMsg(  void  *  pMsg,  unsigned  int  msgLen,  QIS_pipe  *  pQisPipe  )
{
	DynLib_qisPublic  *  pFuncs  =  &g_dynLib_qisPublic;
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->qisPublic.bOk  )  return  -1;

	return  pFuncs->qisPublic.pf_qisPipe_writeMsg(  pMsg,  msgLen,  pQisPipe  );
}

int  dyn_initQisPipe(  GENERIC_Q_CFG  *  pqCfg,  LPCTSTR  pipeName,  BOOL  bStarter,  LPCTSTR  name,  PARAM_initQisPipe  *  pParam,  QIS_pipe  *  p  )
{
	DynLib_qisPublic  *  pFuncs  =  &g_dynLib_qisPublic;
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->qisPublic.bOk  )  return  -1;

	return  pFuncs->qisPublic.pf_initQisPipe(  pqCfg,  pipeName,  bStarter,  name,  pParam,  p  );
}

void  dyn_qisPipeFree(  QIS_pipe  **  pp  )
{
	DynLib_qisPublic  *  pFuncs  =  &g_dynLib_qisPublic;
	if  (  !pFuncs  )  return;

	if  (  !pFuncs->qisPublic.bOk  )  return;

	return  pFuncs->qisPublic.pf_qisPipeFree(  pp  );
}









//////////////////////////////////////////////////////////////////////////// qyShowInfo.cpp
//
int  dyn_showInfo_open(  void  *  p0,  LPCTSTR  tWhere,  LPCTSTR  hint  )
{
	DynLib_qisPublic  *  pFuncs  =  &g_dynLib_qisPublic;
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->qyShowInfo.bOk  )  return  -1;

	return  pFuncs->qyShowInfo.pf_showInfo_open(  p0,  tWhere,  hint  );
}

int  dyn_set_who_showInfo(  LPCTSTR  name  )
{
	DynLib_qisPublic  *  pFuncs  =  &g_dynLib_qisPublic;
	if  (  !pFuncs  )  return  -1;

	if  (  !pFuncs->qyShowInfo.bOk  )  return  -1;

	return  pFuncs->qyShowInfo.pf_set_who_showInfo(  name  );
}