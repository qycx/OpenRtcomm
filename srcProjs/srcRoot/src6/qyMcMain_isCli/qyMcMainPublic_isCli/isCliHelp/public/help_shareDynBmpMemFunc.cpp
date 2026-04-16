
#include	"stdafx.h"
#include	<time.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

#include	<dbt.h>
#include	<mmreg.h>
#include	<msacm.h>
#ifndef  __WINCE__
	#include	<fcntl.h>
	#include	<io.h>
#endif
#include	<stdio.h>
#include	<commdlg.h>
#include	<strsafe.h>

#include	<dshow.h>

#ifndef  __WINCE__
#pragma include_alias( "dxtrans.h", "myqedit.h" )
#define __IDxtCompositor_INTERFACE_DEFINED__
#define __IDxtAlphaSetter_INTERFACE_DEFINED__
#define __IDxtJpeg_INTERFACE_DEFINED__
#define __IDxtKey_INTERFACE_DEFINED__
	//  #include	<Qedit.h>
	#include	"myQedit.h"
#endif
#include	<Mediaobj.h>
#include	<Dmo.h>

#include	"qmcDmoPublic.h"
#ifndef  __WINCE__
	#include	"qmcVideoCapture_dx.h"
#endif
#include	"myfourcc.h"

#include	"qyCusResTemp.h"

//  #include	"qyMc.h"
#include	"qyGuiCommProc.h"

#include	"tmpCeLib.h"

#include	"qyAvRecordPublic.h"

#include	"myresource.h"

#include	"qyOpenShellCommon.h"
#include	"wallTalkers.h"
#include	"DlgShareDynBmpsProc.h"

#include	"dlgTalkProc.h"
#include	"qmcCmdProc.h"

//  #include	"DlgProgress.h"
#include	"tmpCeLib.h"

#include	"qyComPortEx.h"
#include	"qmcGpsProc.h"

#include	"myDb.h"

#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"





//  2014/09/11
__declspec(  dllexport  ) BOOL  bShared(  SHARE_dyn_bmp  *  pMem  )
 {
	 return  pMem->var.ucbLocalVideoOpen;
 }

 //
__declspec(  dllexport  ) int  shareDynBmp_clear(  SHARE_dyn_bmp  *  pDynBmpMem  )
 {
	 if  (  !pDynBmpMem  )  return  -1;
	 memset(  pDynBmpMem,  0,  sizeof(  pDynBmpMem[0]  )  );
	 return  0;
 }

 //  SHARE_dynBmps	*	dlgShareDynBmps_getShareDynBmpsBySth(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  int  uiObjType  )
__declspec(  dllexport  )   void  *  dlgShareDynBmps_getShareDynBmpsBySth(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  int  uiObjType  )
{
	if  (  !pDLG_shareDynBmps_var  )  return  NULL;
	DLG_shareDynBmps_var  &m_var  =  *(  DLG_shareDynBmps_var  *  )pDLG_shareDynBmps_var;

	switch  (  uiObjType  )  {
			case  CONST_objType_screen:
				  return  &m_var.shares[0];
		    case  CONST_objType_webcam:
				  return  &m_var.shares[1];
			case  CONST_objType_rtspStream:	//  2014/06/01
				  return  &m_var.shares[2];
			case  CONST_objType_smallStream:
				  return  &m_var.shares[3];	//  2018/12/14
			case   CONST_objType_ic:
				   return  &m_var.shares[4];
				   break;
			default:
					break;
	}
	return  NULL;
}

//
 __declspec(  dllexport  )  SHARE_dyn_bmp  *  help_shareDynBmp_getMemByIndex(  CHelp_shareDynBmp  *  pHelp,  HWND  hDlg_shareDynBmps,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType,  unsigned  int  index  )
{
	SHARE_dynBmps  *  pShare  =  (  SHARE_dynBmps  *  )dlgShareDynBmps_getShareDynBmpsBySth(  hDlg_shareDynBmps,  pDLG_shareDynBmps_var,  uiObjType  );
	if  (  !pShare  )  return  NULL;

	if  (  index  <  0  ||  index  >=  pShare->usCnt  )  return  NULL;

#ifdef  __DEBUG__
		//traceLog(  _T(  "Not finished: CHelp_shareDynBmp::getMem. 可以在这里加上状态的判断，以便让rtsp的流的漫长的过程能够正确的逐步执行。同时也需要加锁，避免操作同一个单元"  )  );
#endif

	 return   &pShare->mems_internal[index];
}


__declspec(  dllexport  )  SHARE_dyn_bmp  *  help_shareDynBmp_getMemByIndex(  CHelp_shareDynBmp  *  pHelp,  SHARE_dynBmps  *  pShare,  unsigned  int  index  )
{
	if  (  !pShare  )  return  NULL;

	if  (  index  <  0  ||  index  >=  pShare->usCnt  )  return  NULL;

#ifdef  __DEBUG__
		//traceLog(  _T(  "Not finished: CHelp_shareDynBmp::getMem. 可以在这里加上状态的判断，以便让rtsp的流的漫长的过程能够正确的逐步执行。同时也需要加锁，避免操作同一个单元"  )  );
#endif

	 return   &pShare->mems_internal[index];
}



 //__declspec(  dllexport  )  int  help_shareDynBmp_getIndexByIndex_obj(  CHelp_shareDynBmp  *  pHelp,  HWND  hDlg_shareDynBmps,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType,  unsigned  int  index_obj  )
 __declspec(  dllexport  )  int  help_shareDynBmp_getIndexByIndex_obj(  CHelp_shareDynBmp  *  pHelp,  HWND  hDlg_shareDynBmps,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType,  unsigned  int  index_obj,  unsigned  short  usHelp_subIndex  )
{
	SHARE_dynBmps  *  pShare  =  (  SHARE_dynBmps  *  )dlgShareDynBmps_getShareDynBmpsBySth(  hDlg_shareDynBmps,  pDLG_shareDynBmps_var,  uiObjType  );
	if  (  !pShare  )  return  -1;

	if  (  !index_obj  )  return  -1;

#ifdef  __DEBUG__
		//traceLog(  _T(  "Not finished: CHelp_shareDynBmp::getMem. 可以在这里加上状态的判断，以便让rtsp的流的漫长的过程能够正确的逐步执行。同时也需要加锁，避免操作同一个单元"  )  );
#endif

	int  i;
	for  (  i  =  0;  i  <  pShare->usCnt;  i  ++  )  {
		if  (  pShare->mems_internal[i].resObj.usIndex_obj  ==  index_obj
			&&  pShare->mems_internal[i].resObj.usHelp_subIndex  ==  usHelp_subIndex  )  //  2016/07/24  			
		{		
			break;
		}
	}
	if  (  i  ==  pShare->usCnt  )  return  -1;

	 return   i;
}
 



 //
 __declspec(  dllexport  )  int  help_shareDynBmp_getNewIndex(  CHelp_shareDynBmp  *  pHelp,  HWND  hDlg_shareDynBmps,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType  )
 {
	 int	iErr  =  -1;
	 int  i;
	 
	 SHARE_dynBmps  *  pShare  =  (  SHARE_dynBmps  *  )dlgShareDynBmps_getShareDynBmpsBySth(  hDlg_shareDynBmps,  pDLG_shareDynBmps_var,  uiObjType  );
	 if  (  !pShare  )  return  -1;
	  			
	 for  (  i  =  0;  i  <  pShare->usCnt;  i  ++  )  {
		 if  (  !pShare->mems_internal[i].resObj.usIndex_obj  )  break;					 
	 }
	
	 //
	 if  (  i  ==  pShare->usCnt  )  {
		 //  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp failed: shared rtsp streams are full"  )  );								 
		 goto  errLabel;					 
	 }

	 iErr  =  0;

errLabel:
	 return  iErr  ?  -1  :  i;
 }
