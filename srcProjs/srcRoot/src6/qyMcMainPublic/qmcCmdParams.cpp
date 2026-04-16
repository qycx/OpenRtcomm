

#include	"stdafx.h"
#include	<windows.h>

#ifndef  __WINCE__
	#include	<vfw.h>
#else
	#ifdef  __TEST__
		#include	<vfw.h>
	#endif
	#include	<mmreg.h>
	#include	<MSAcm.h>
#endif

#include	<Wincrypt.h>

#include	<tchar.h>
#include	<WinSock2.h>

#include	"qmcommon.h"
#include	"myCmdParams_open.h"
#include	"qmcCmdParams.h"



 //  TCHAR	*	pCmdLine  =  GetCommandLine(  );
 extern  "C"  __declspec(  dllexport  )  int  parseCmdLine_qmc_func(  LPCTSTR  pCmdLine,  QMC_APP_PARAMS  *  pParams  )
{
	int		iErr	=	-1;
		 
	 TCHAR	*	pT;
	 TCHAR	*	pT1;
	 TCHAR	*	pT2;
	 //
	 TCHAR		tBuf[256];

	 //
	 if  (  !pParams  )  return  -1;

	 memset(  pParams,  0,  sizeof(  pParams[0]  )  );

	 for  (  pT  =  (  TCHAR  *  )pCmdLine;  pT;  )  {
		  if  (  !(  pT  =  _tcschr(  pT,  _T(  '-'  )  )  )  )  break;
		  pT  ++  ;
		  switch  (  *pT  )  {
				 case  _T(  'a'  ):
				 case  _T(  'A'  ):					 				
					   break;
				 case  _T(  'c'  ):
				 case  _T(  'C'  ):
					   //
					   pT1  =  (TCHAR*)CONST_qmCmdLine_confServer;
					   if  (  !_tcsnicmp(  pT,  pT1,  _tcslen(  pT1  )  )  )  {
						   //
						   pT  +=  _tcslen(  pT1  );
						   pParams->bConfServer  =  true;
						   break;
					   }
					   //
					   break;
					   //
				 case  _T(  'd'  ):  //  2016/04/26
				 case  _T(  'D'  ):
					   //
					   pT1  =  (TCHAR*)CONST_qmCmdLine_sym_dbgDvt;
					   if  (  !_tcsnicmp(  pT,  pT1,  _tcslen(  pT1  )  )  )  {
						   //
						   pParams->ucbDbgDvt  =  TRUE;
						   //
						   break;
					   }
					   //  2016/05/05
					   pT1  =  (TCHAR*)CONST_qmCmdLine_sym_dbgEvt;
					   if  (  !_tcsnicmp(  pT,  pT1,  _tcslen(  pT1  )  )  )  {
						   //
						   pParams->ucbDbgEvt  =  TRUE;
						   //
						   break;
					   }
					   //  2016/07/03					   
					   pT1  = (TCHAR*)CONST_qmCmdLine_sym_dbgOnvif;
					   if  (  !_tcsnicmp(  pT,  pT1,  _tcslen(  pT1  )  )  )  {
						   //
						   pParams->ucbDbgOnvif  =  TRUE;
						   //
						   break;
					   }
					   //					   
					   break;
					   //
				 case  _T(  'f'  ):
					   //
					   //  2015/08/04
					   #if  1  //  def  __DEBUG__
							   pT1  = (TCHAR*)CONST_qmCmdLine_fileServer;
							   if  (  !_tcsnicmp(  pT,  pT1,  _tcslen(  pT1  )  )  )  {
								   //
								   pParams->bFileServer  =  TRUE;
								   //
								   break;
							   }
					   #endif
					   //
					   break;
				 case  _T(  'm'  ):
					   //
					   pT1  = (TCHAR*)CONST_qmCmdLine_mcu;
					   if  (  !_tcsnicmp(  pT,  pT1,  _tcslen(  pT1  )  )  )  {
						   //
						   pT  +=  _tcslen(  pT1  );
						   pParams->idInfo_mcu.ui64Id  =  _tcstoul(  pT,  &pT2,  10  );
						   //
						   #ifdef  __DEBUG__
								   //  qyShowHint(  _T(  "cmdLine %s, uiTranNo_sharedObj %d"  ),  pCmdLine,  pQM->cmd.uiTranNo_sharedObj  );
						   #endif
						   break;
					   }
					   break;
				 case  _T(  'n'  ):
					   //
					   //  2015/02/17
					   pT1  = (TCHAR*)CONST_qmCmdLine_sym_noDvt;
					   if  (  !_tcsnicmp(  pT,  pT1,  _tcslen(  pT1  )  )  )  {
						   //
						   pParams->ucbNoDvt  =  TRUE;
						   //
						   break;
					   }
					   //  2015/10/28
					   pT1  = (TCHAR*)CONST_qmCmdLine_sym_noEvt;
					   if  (  !_tcsnicmp(  pT,  pT1,  _tcslen(  pT1  )  )  )  {
						   //
						   pParams->ucbNoEvt  =  TRUE;
						   //
						   break;
					   }

					   //
					   break;

				 case  _T(  'p'  ):
				 case  _T(  'P'  ):
					   //
					   pT1  = (TCHAR*)CONST_qmCmdLine_passwd;
					   if  (  !_tcsnicmp(  pT,  pT1,  _tcslen(  pT1  )  )  )  {
						   //
						   pT  +=  _tcslen(  pT1  );
						   //
						   M_getCmd(  pT,  pParams->passwd,  mycountof(  pParams->passwd  )  );					   
						   //
						   break;
					   }
					   //
					   pT1  = (TCHAR*)CONST_qmCmdLine_port;
					   if  (  !_tcsnicmp(  pT,  pT1,  _tcslen(  pT1  )  )  )  {
						   //
						   pT  +=  _tcslen(  pT1  );
						   int  port  =  _tcstoul(  pT,  &pT2,  10  );
						   //
						   pParams->port  =  port;
						   //
						   break;
					   }				   

					   //  2015/10/04
					   pT1  = (TCHAR*)CONST_qmCmdLine_pktResType_suggested;
					   if  (  !_tcsnicmp(  pT,  pT1,  _tcslen(  pT1  )  )  )  {
						   //
						   pT  +=  _tcslen(  pT1  );
						   int  type  =  _tcstoul(  pT,  &pT2,  10  );
						   //
						   pParams->usPktResType_suggested  =  type;
						   //
						   break;
					   }
					   //
					   break;
				 case  _T(  'q'  ):
				 case  _T(  'Q'  ):
					   //
					   pT1  = (TCHAR*)CONST_qmCmdLine_sym_appObjPrefix;
					   if  (  !_tcsnicmp(  pT,  pT1,  _tcslen(  pT1  )  )  )  {
						   //
						   pT  +=  _tcslen(  pT1  );
						   int  iSeqNoSelected_appObjPrefix  =  _tcstoul(  pT,  &pT2,  10  );
						   //
						   if  (  iSeqNoSelected_appObjPrefix  <  0  ||  iSeqNoSelected_appObjPrefix  >=  CONST_maxOfVideoConferencingServers  )  {
							   #ifdef  __DEBUG__
									   traceLog((TCHAR*)_T(  "parseCmd_qmc err: iSeqNo err"  )  );
							   #endif
							   break;
						   }
						   //
						   pParams->iSeqNoSelected_appObjPrefix  =  iSeqNoSelected_appObjPrefix;
						   _sntprintf(  pParams->appObjPrefix,  mycountof(  pParams->appObjPrefix  ),  _T(  "%s%d"  ),  CONST_qmCmdLine_sym_appObjPrefix, pParams->iSeqNoSelected_appObjPrefix  );
						   //
						   break;
					   }
					   break;
				 case  _T(  'r'  ):		//  2014/12/12
				 case  _T(  'R'  ):
					   pT  ++  ;
					   M_getCmd(  pT,  pParams->rtspUrl,  mycountof(  pParams->rtspUrl  )  );
					   break;
				 case  _T(  's'  ):
				 case  _T(  'S'  ):
					   //
					   pT1  = (TCHAR*)CONST_qmCmdLine_server;
					   if  (  !_tcsnicmp(  pT,  pT1,  _tcslen(  pT1  )  )  )  {
						   //
						   pT  +=  _tcslen(  pT1  );
						   //
						   M_getCmd(  pT,  tBuf,  mycountof(  tBuf  )  );
						   myTChar2Utf8(  tBuf,  pParams->serverAddr,  mycountof(  pParams->serverAddr  )  );
						   //
						   break;
					   }

					   break;
				 case  _T(  't'  ):
					   //
					   pT1  = (TCHAR*)CONST_qmCmdLine_sym_tn;
					   if  (  !_tcsnicmp(  pT,  pT1,  _tcslen(  pT1  )  )  )  {
						   //
						   pT  +=  _tcslen(  pT1  );
						   int  tn  =  _tcstoul(  pT,  &pT2,  10  );
						   //
						   pParams->tn_cliPipe  =  tn;
						   //
						   break;
					   }
					   //  2015/02/17
					   pT1  = (TCHAR*)CONST_qmCmdLine_sym_tag;
					   if  (  !_tcsnicmp(  pT,  pT1,  _tcslen(  pT1  )  )  )  {
						   //
						   //  skip the field. 忽略此字段，因为纯粹为了显示一个标识
						   //
						   break;
					   }
					   //  2015/07/18
   					   #ifdef  __DEBUG__
							   pT1  = (TCHAR*)CONST_qmCmdLine_sym_test;
							   if  (  !_tcsnicmp(  pT,  pT1,  _tcslen(  pT1  )  )  )  {
								   pT  +=  _tcslen(  pT1  );
								   pParams->iTestNo  =  _ttol(  pT  );			
								   //
								   break;
							   }
					   #endif

					   break;

				 case  _T(  'u'  ):
				 case  _T(  'U'  ):
					   //
					   pT1  = (TCHAR*)CONST_qmCmdLine_user;
					   if  (  !_tcsnicmp(  pT,  pT1,  _tcslen(  pT1  )  )  )  {
						   //
						   pT  +=  _tcslen(  pT1  );
						   //
						   M_getCmd(  pT,  pParams->usrName,  mycountof(  pParams->usrName  )  );
						   //
						   break;
					   }

					   break;
				 default:
						break;
		 }	 
	 }



	 //
	iErr  =  0;
//errLabel:
	return  iErr;
}


#if  0
 extern  "C"  __declspec(  dllexport  )  int  makeCmdLine_qmc(  QMC_APP_PARAMS  *  pParams,  TCHAR  *  cmdLineBuf,  unsigned  int  cnt  )
{
	TCHAR	*	cmdStr  =  _T(  ""  );
	if  (  pParams->ucbAv  )  cmdStr  =  CONST_qmCmdLine_av;
	else  if  (  pParams->ucbMediaFile  )  cmdStr  =  CONST_qmCmdLine_mediaFile;
	else  return  -1;

	_sntprintf(  cmdLineBuf,  cnt,  _T(  "-c%s%u -a%s"  ),  cmdStr,  pParams->uiTranNo_sharedObj,  pParams->appObjPrefix  );    
	return  0;
}
#endif