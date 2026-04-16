

#include	"stdafx.h"
#include	"shlobj.h"
#include	<time.h>
#include	<tchar.h>

#ifndef  __WINCE__
		 #include	"myresource.h"
#endif
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"smCommProc.h"


#ifndef  __NOTSUPPORT_MULTIDOC__
#ifndef  __useQt__
	#include	"qyRestrictEdit.h"
	#include	"qyFile.h"
#endif
#endif
#ifdef  __isCli__
		#ifndef  __NOTSUPPORT_qyFile__
				 //#include	"qyFile.h"
		#endif
#endif
#include	"qyCusResTemp.h"
#include	"tmpCeLib.h"
//

#ifndef  __NOTSUPPORT_MULTIDOC__

#ifndef  __useQt__
	#include	"dlgMcHint.h"
	#include	"dlgQnmCfgOptions.h"
	#include	"DlgQnmCfgAdvancedOptions.h"
#endif

#endif 
#include	"qyDynLib.h"
#include	"qisGuiPublic_public.h"


//#include	"qmcVWall.h"
//#include	"qmcCmdProc.h"

#include	"qySqlFunc.h"

#include	"mmDeviceProc.h"			//  2013/05/22

#ifdef  __isCli__
		#include	"isCliHelpPublic.h"			//  2013/06/07
		#include	"qyMessengerHelpPublic.h"	//  2013/07/26
		#include	"isCliD3dPublic.h"	//  2013/07/03
		#include	"qisWallsProc.h"	//  2013/07/11
		#include	"imgProcessPublic.h"
		#include	"funcsForIsCliHelp.h"
		#include	"isCliExPublic.h"
#endif

//  201506/28
#include	"qisGuiPublic_public.h"


//int  setAllHints(  void  *  pResInfoParam,  unsigned  short  usLangId  );
int  getCustomComm(  QNM_CUSTOM_COMM  *  );
extern  QY_DMITEM  CONST_cusMenusTable[];

//  int  gGuiData_init(  unsigned short usLangId,  G_guiData_qyMc  *  pGuiData  );
//  int  gGuiData_exit(  G_guiData_qyMc  *  pGuiData  );




char  gQyCfgs[CONST_qySize_cfgs  +  1]  =  CONST_qyCfgSym
										CONST_qyCfgName_cntIp			"="		""				//  DEFAULT_qwmServIp
										" "
										CONST_qyCfgName_cntAddr1		"="		""				//  DEFAULT_qwmServAddr1
										" "
										CONST_qyCfgName_cntPort			"="		"8768"
										" "
										CONST_qyCfgName_qwmSeqNo		"="		"cz"
										" "
										CONST_qyCfgName_systemId		"="		"3"
										" "
										CONST_qyCfgName_bGetPcAsset		"="		"1"
										" "
										CONST_qyCfgName_bNetMc2			"="		"1"
										" "
										CONST_qyCfgName_bSecChk			"="		"0"				//  2005/05/01
										"\0";



 //  size  ==  0  Ê±£¬Ôò²»¶ÔpQyCfgs³¤¶È×÷³öÏÞÖÆ
 int  parseCfgs_qyMc(  QY_MC_CFG  *  pCfg  )
{
	 int				iErr		=	-1;
	 char			*	p			=	NULL;
	 char				buf[1024];
	 char			*	pQyCfgs		=	gQyCfgs;
	 unsigned  int		size		=	sizeof(  gQyCfgs  );

	 #ifdef  __DEBUG__
			 //  for test
	 #endif

	 traceLogA(  (char*)  (char*)  "parseCfgs_qyMc: pQyCfgs is [%s]",  pQyCfgs  );

	 if  (  size  )  {
		 if  (  strlen(  pQyCfgs  )  >=  (  int  )size   )  return  -1;
	 }

	 pCfg->iSystemId_wanted  =  DEFAULT_qyCfgVal_systemId;

	 //  try to get cnt
	 if  (  parseQwmDynCfg(  pQyCfgs,  size,  &pCfg->dynCfg  )  )  goto  errLabel;
	 //
	 
	 //  2005/06/24
	 p  =  qwmGetCfg(  pQyCfgs,  (char*)CONST_qyCfgName_qwmSeqNo,  buf,  sizeof(  buf  )  );
	 if  (  p  )  {
		 safeStrnCpy(  p,  pCfg->seqNo,  sizeof(  pCfg->seqNo  )  );
	 }

	 p  =  qwmGetCfg(  pQyCfgs,  (char*)CONST_qyCfgName_systemId,  buf,  sizeof(  buf  )  );
	 if  (  p  )  {
		 pCfg->iSystemId_wanted  =  (  unsigned  short  )atol(  buf  );
	 }

	 iErr  =  0;	  

errLabel:

	 return  iErr;

}


 



 BOOL bChkQyMcEnv(  QY_MC  *  pQyMc  )
{
	 BOOL						bRet								=	FALSE;
	 DWORD						dwMajor, dwMinor;
	 QY_SYSTEMINFO_RCD			systemInfo;
	 BOOL						bDbVerOk							=	FALSE;
	 //  CDatabase					db;
	 TCHAR						tBuf[512  +  1]						=	_T(  ""  );
	 TCHAR						tmplFile[MAX_PATH  +  1]			=	_T(  ""  );     
	 BOOL						bStartToChkDbVer					=	FALSE;
	 //
	 BOOL						bNeedOsUsrAdmin						=	FALSE;

#ifdef  __WINCE__
		return  TRUE;
#endif

	 //  Ð£ÑéIE°æ±¾ºÅ¡£
	 HRESULT  hr  =  qyGetComCtlVersion(  &dwMajor,  &dwMinor  );
	 if  (  FAILED( hr )  )  goto errLabel;
	 //
	 if  (  dwMajor < 4  ||  (  dwMajor  ==  4  &&  dwMinor  <  71  )  )  {
		 qyShowHint(  QY_MC_HINT_NOIE4  );
		 goto errLabel;
	 }

	 //  ÏÂÃæÐ£ÑéÔËÐÐÈ¨ÏÞ£¬2008/02/21
	 switch  (  pQyMc->env.iPlatformId  )  {
			 case  CONST_qyPlatform_winVista:
				   if  (  pQyMc->iAppType  !=  CONST_qyAppType_client  )  bNeedOsUsrAdmin  =  TRUE;
				   break;
			 default:
					break;
	 }

	 //
#ifdef  __isMgr__
		bNeedOsUsrAdmin  =  TRUE;
#endif

	 //
	 if  (  bNeedOsUsrAdmin  )  {

		 //  if  (  !bOsUsrAdmin  )  
		 if  (  !bProcessOsUsrAdmin(  )  )
		 {
			 qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_runAsAdmin  )  );  
			 goto  errLabel;
		 }
	 }

	 

	 bRet  =  TRUE;

errLabel:

	 if  (  !bRet  )  {

	 }

	 return bRet;

}


 BOOL bChkQyMcEnv_db(  QY_MC  *  pQyMc  )
{
	//
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)(  ""  ),  _T(  "Gui"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bChkQyMcEnv_db, bUseDb %d, dbType %s"  ),  bUseDb(  ),  qyGetDesByType1(  CONST_dbTypeTable,  pQyMc->cfg.db.iDbType  )  );

#ifdef  __NOTSUPPORT_DB__
		return  TRUE;
#else

	 BOOL						bRet								=	FALSE;
	 DWORD						dwMajor, dwMinor;
	 QY_SYSTEMINFO_RCD			systemInfo;
	 BOOL						bDbVerOk							=	FALSE;
	 TCHAR						tBuf[512  +  1]						=	_T(  ""  );
	 TCHAR						tmplFile[MAX_PATH  +  1]			=	_T(  ""  );     
	 BOOL						bStartToChkDbVer					=	FALSE;
	 //
	 BOOL						bNeedOsUsrAdmin						=	FALSE;


	 void				*		pDb									=	NULL;

	 //  2012/07/13
	 if  (  pQyMc->cfg.db.iDbType  ==  CONST_dbType_myDb  )  return  TRUE;

	 //  2012/07/12
	 //  pDb  =  new  CDatabase;
	 pDb  =  qyNewDb(  );
	 if  (  !pDb  )  goto  errLabel;


	 //  ÔÚaccessÊÇÎÄ¼þÊý¾Ý¿â£¬ËùÒÔ£¬ÐèÒª¹ÜÀíÔ±È¨ÏÞ²ÅÄÜºÍdaemon±£³ÖÏàÍ¬µÄ´¦ÀíÄÜÁ¦. //  2008/09/06
 	 #if  1  //  ndef  __DEBUG__
			  if  (  pQyMc->cfg.db.iDbType  ==  CONST_dbType_access  )  {
				  if  (  pQyMc->iAppType  !=  CONST_qyAppType_client  )  bNeedOsUsrAdmin  =  TRUE;
			  }
	 #endif

	 if  (  bNeedOsUsrAdmin  )  {

		 //  if  (  !bOsUsrAdmin  )  
		 if  (  !bProcessOsUsrAdmin(  )  )
		 {
			 qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_runAsAdmin  )  );  
			 goto  errLabel;
		 }
	 }



	 //  ÏÂÃæÐ£ÑéÊý¾Ý¿â
	 _sntprintf(  tmplFile,  mycountof(  tmplFile  ),  _T(  "%sdb\\%s.tmpl.mdb"  ),  pQyMc->cfg.installDir,  pQyMc->cfg.pSysCfg->defaultDbName  );
	 if  (  pQyMc->cfg.db.iDbType  ==  CONST_dbType_access  &&  pQyMc->cfg.ucbDsnless  )  {
		 BOOL						bDbFileExists						=	FALSE;

		 if  (  GetFileAttributes(  pQyMc->cfg.defaultDbName  )  !=  INVALID_FILE_ATTRIBUTES  )  bDbFileExists  =  TRUE;

		 if  (  bDbFileExists  )  {

			 if  (  pQyMc->iSystemId  ==  CONST_qySystemId_messenger  &&  pQyMc->iAppType  ==  CONST_qyAppType_client  )  {
				 //  ÒªÐ£ÑéÒ»ÏÂÊý¾Ý¿âµÄ°æ±¾ºÅ£¬Èç¹û°æ±¾²»·û£¬ÔòÌáÊ¾ÖØÃüÃûÀÏÊý¾Ý¿â£¬È»ºó¿½±´ÐÂÊý¾Ý¿â
				 TCHAR						newFileName[MAX_PATH  +  1]			=	_T(  ""  );
				 TCHAR					*	pT									=	NULL;
				 char						timeBuf[CONST_qyTimeLen  +  1]		=	"";

				 bDbVerOk  =  FALSE;
				 memset(  &systemInfo,  0,  sizeof(  systemInfo  )  );
				 if  (  bQyOpenDb(  pQyMc->cfg.db.connectStr,  pDb  )  )  {
					 if  (  bGetSystemInfo(  pDb,  pQyMc->cfg.db.iDbType,  &systemInfo  )  &&  !_strnicmp(  qnmDbVerStr(  pQyMc->iServiceId  ),  systemInfo.dbVer,  4  )  )  {
						 bDbVerOk  =  TRUE;
					 }
					 qyCloseDb(  pDb  );
				 }

				 if  (  !bDbVerOk  )  {

					 lstrcpyn(  newFileName,  pQyMc->cfg.defaultDbName,  mycountof(  newFileName  )  );
					 getCurTime(  timeBuf  );
					 pT  =  _tcsrchr(  newFileName,  _T(  '.'  )  );
					 if  (  !pT  )  _sntprintf(  newFileName,  mycountof(  newFileName  ),  _T(  "%s.%s"  ),  newFileName,  CQyString(  timeBuf  )  );
					 else  {
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s"  ),  CQyString(  timeBuf  ),  pT  );
						   pT[0]  =  0;
						   _sntprintf(  newFileName,  mycountof(  newFileName  ),  _T(  "%s%s"  ),  newFileName,  tBuf  );
					 }

					 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s,%s %s. %s %s. %s %s. %s ?"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_installedProgramDb  ),  pQyMc->cfg.defaultDbName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_verIs  ),  CQyString(  systemInfo.dbVer  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_updateProgramDbVer  ),  CQyString(  qnmDbVerStr(  pQyMc->iServiceId  )  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_renameDbIs  ),  newFileName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToUpdate  )  );		//  (  "µ±Ç°µÄÊý¾Ý¿â%s°æ±¾ºÅÎª%s, ÐèÒª¸ü»»Îª°æ±¾ºÅÎª%sµÄÐÂÊý¾Ý¿â¡£Ô­Êý¾Ý¿â½«°´ÈÕÆÚÖØÃüÃûÎª%s¡£ÊÇ·ñ¸ü»»£¿"  )
					 if  (  myMessageBox(  NULL,  tBuf,  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  goto  errLabel;

					 //  ÏÂÃæ¿ªÊ¼ÒÆ³ý¾ÉÊý¾Ý¿âÎÄ¼þ
					 if  (  !CopyFile(  pQyMc->cfg.defaultDbName,  newFileName,  FALSE  )  )  {
						 myMessageBox(  NULL,  CQyString(  _T(  "ÎÞ·¨¸²¸Ç"  )  )  +  newFileName,  _T(  ""  ),  MB_OK  );  goto  errLabel;
					 }
					 if  (  !DeleteFile(  pQyMc->cfg.defaultDbName  )  )  {
						 myMessageBox(  NULL,  CQyString(  _T(  "ÎÞ·¨É¾³ý"  )  )  +  pQyMc->cfg.defaultDbName,  _T(  ""  ),  MB_OK  );  goto  errLabel;
					 }

					 bDbFileExists  =  FALSE;
				
				 }

			 }
		 }


		 traceLogA(  (char*)  (char*)  "bCheckQyMcEnv: dbFile not exists, to copy file"  );		 
		 if  (  !bDbFileExists  )  {
			 if  (  !CopyFile(  tmplFile,  pQyMc->cfg.defaultDbName,  FALSE  )  )  {
				 qyDisplayLastError(  (char*)"bChkQyMcEnv.CopyFile failed."  );
				 //goto  errLabel;
			 }
		 }

	 }

	 
	 //  if  (  pQyMc->iServiceId  ==  CONST_qyServiceId_is  )  
	 {
		 
		 //
		 bStartToChkDbVer  =  TRUE;
	 	
		 //
		 bDbVerOk  =  FALSE;
		 
		 memset(  &systemInfo,  0,  sizeof(  systemInfo  )  );
		 if  (  !bQyOpenDb(  pQyMc->cfg.db.connectStr,  pDb  )  )  goto  errLabel;
		 
		 //
		 if  (  bGetSystemInfo(  pDb,  pQyMc->cfg.db.iDbType,  &systemInfo  )  &&  !_strnicmp(  qnmDbVerStr(  pQyMc->iServiceId  ),  systemInfo.dbVer,  4  )  )  {
			 bDbVerOk  =  TRUE;
		 }

		 qyCloseDb(  pDb  );

		 //
		 if  (  !bDbVerOk  )  {
			 if  (  pQyMc->iAppType  ==  CONST_qyAppType_client  &&  pQyMc->cfg.db.iDbType  ==  CONST_dbType_access  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s %s, %s. %s %s %s"  ), getResStr(  0,  &pQyMc->cusRes,  CONST_resId_installedProgramDb  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_verIs  ),  CQyString(  systemInfo.dbVer  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_isWrong  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_mightBe  ),  CQyString(  tmplFile  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_isWrong  )  );		//  (  "µ±Ç°µÄÊý¾Ý¿âµÄ°æ±¾Îª%s, ²»ÕýÈ·¡£Ò²ÐíÊÇ%sµÄ°æ±¾²»ÕýÈ·"  )
			 else  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s %s, %s. %s %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_installedProgramDb  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_verIs  ),  systemInfo.dbVer[0]  ?  CQyString(  systemInfo.dbVer  )  :  CQyString(  (char*)"[]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_isWrong  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_updateTo  ),  CQyString(  qnmDbVerStr(  pQyMc->iServiceId  )  )  );		//  (  "ÇëÉý¼¶Êý¾Ý¿âµ½"  )
			 myMessageBox(  NULL,  tBuf,  _T(  ""  ),  MB_OK  );  goto  errLabel;
		 }


	 }
	 

	 bRet  =  TRUE;

errLabel:

	 if  (  pDb  )  {
#if  0
		 CDatabase  *  pDb1  =  (  CDatabase  *  )pDb;
		 delete  pDb1;
#endif
		 qyFreeDb(  &pDb  );
	 }

	 //
	 if  (  !bRet  )  {
		 if  (  bStartToChkDbVer  &&  !bDbVerOk  )  {
			 #if  defined(  __APP_qyMc_touchscreen__  )  ||  defined(  __isCli__  )
					 myMessageBox(  NULL,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_dbErr  ),  _T(  ""  ),  MB_OK  );
			 #else
					if  (  myMessageBox(  NULL,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_dbErrHint  ),  _T(  ""  ),  MB_YESNO  |  MB_DEFBUTTON2  )  ==  IDYES  )  {		//  (  "ÎÞ·¨´ò¿ªÊý¾Ý¿â£¬ÇëÆô¶¯Êý¾Ý¿â»òÖØÉèÊý¾Ý¿â¡£ÊÇ·ñÒªÖØÉèÊý¾Ý¿â?"  )
#ifndef  __useQt__
						CDlgQnmCfgAdvancedOptions  dlg;
						dlg.DoModal(  );		   
#endif
					}
			 #endif
		 }
	 }

	 return bRet;
#endif
}

 //  BOOL	bDlgFontCreated  =  FALSE, bDlgBarFontCreated  =  FALSE;
#ifndef  __WINCE__
 //  CFont	gQyDlgFont, gQyDlgBarFont;
#endif

#if  0
 void qySetDlgFont(  HWND  hWnd )
{
#ifndef  __WINCE__
	CFont	*	pFont	=	NULL;
    
	if  (  !bDlgFontCreated  )  {
		if  (  gQyDlgFont.CreateFont( 14, 6, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
					ANSI_CHARSET, OUT_DEFAULT_PRECIS,
					CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
					DEFAULT_PITCH | FF_DONTCARE, QY_MC_DLGFACENAME  )  )
		{
			bDlgFontCreated  =  TRUE;			
		}
	}
	if  (  bDlgFontCreated  )  pFont = &gQyDlgFont;
	if  ( pFont  )  {
		FARPROC proc = MakeProcInstance( ( FARPROC )SetFontProc, AfxGetInstanceHandle( ) );
		EnumChildWindows( hWnd, ( WNDENUMPROC )proc, ( LPARAM )( ( HFONT )*pFont ) );
		FreeProcInstance( proc );
	}

#endif

	return;
	
}


 void qySetDlgBarFont(  HWND  hWnd )
{
#ifndef  __WINCE__
	CFont	*	pFont	=	NULL;
    
	if  (  !bDlgBarFontCreated  )  {
		if  (  gQyDlgBarFont.CreateFont( 14, 6, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
					ANSI_CHARSET, OUT_DEFAULT_PRECIS,
					CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
					DEFAULT_PITCH | FF_DONTCARE, QY_MC_DLGFACENAME  )  )
		{
			bDlgBarFontCreated  =  TRUE;			
		}
	}
	if  (  bDlgBarFontCreated  )  pFont = &gQyDlgBarFont;
	if  ( pFont  )  {
		FARPROC proc = MakeProcInstance( ( FARPROC )SetFontProc, AfxGetInstanceHandle( ) );
		EnumChildWindows( hWnd, ( WNDENUMPROC )proc, ( LPARAM )( ( HFONT )*pFont ) );
		FreeProcInstance( proc );
	}

#endif
	return;
	
}
 #endif

 
#ifdef  __DEBUG__

#ifdef  __isCli__
#include	"qmcVideoCapture_isCli.h"
#endif


	 #define		MACRO_kk(x)		(  _T(  "jjj"  )_T(  x  )_T(  "kkk"  )  )
 int  testHook(  )
{



	float	f  =  (  float  )123.456789;
	int  ii;

	ii  =  CONST_fourcc_YV12;
	ii  =  CONST_fourcc_I420;

	traceLogA(  (char*)  (char*)  "f is %.2f",  f  );

 {
	 CQyString	m;
 }
	time_t		t	=	0;
	time_t		t1	=	0;
	char		timeBuf[128]	=	"";

	mytime(  &t  );

	getTimeStr(  t,  timeBuf,  mycountof(  timeBuf  )  );

	t1  =  gettTimeByBuf(  timeBuf  );

	 return  0;
}


 
 //int  testDmoCompressAudioInit(  ); 
int  getRndStr(  char  *  buf,  unsigned  int  size  );
 char  *  iFourcc2Str(  int  fourcc,  char  *  fourccStr,  unsigned  int  size  );
	 
#include	<ddraw.h>
#include	"qyTick.h"
#ifdef  __isCli__
#include	"WallTalkers.h"
#endif

 int  showAcm(  );
BOOL  testSampleGrabber(  );
BOOL  testFilterGraph(  );
//int  testGpsFunc(  );

 int  kk(  LPCTSTR  str  )
 {
	 return  0;
 }

 int  testDx(  );

#ifdef  __isCli__
#include	"dlgTalkProc.h"
	//#include	"aecCommon.h"
#endif
#include	<stddef.h>

 #include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include	"genericHash.h"

 //  int  list_devices_a(  );


 HRESULT  RecordAudioStream(  void  *  pMySink  );

 extern  "C"  __declspec(  dllexport  )  int  voe_list_device(  char  *  recorder_buf,  int  size,  char  *  recorder_selected_utf8  );

  int  getChosenDevice(  TCHAR  *  recorder_selected,  unsigned  int  uiCnt_recorder_selected,  TCHAR  *  webcam_selected,  unsigned  int  uiCnt_webcam_selected,
						void  *  pCapParam,  BOOL  bIncludeACap,  int  *  piMenuId_selectedAudio,  int  *  piMenuId_selectedVideo  );

  int testFfmpeg_main(int argc, char* argv[]);
  int testPcm2Aac_main(int argc, char *argv[]);
  int testresampling_audio_main(int argc, char **argv);
  int testRwLock();
  int testfiltering_audio_main(int argc, char **argv);
  int testMix_main(int argc, char **argv);
  
  //
#include	"qisGuiPublic_public.h"
#ifdef  __isCli__
#include <colorSpaceFunc.h>
#endif 
#include <ancCommProc.h>

//#include <qmcVideoCapture.h>
//#include <qmcVideoCapture.h>

  //

   //
    extern  "C"  BOOL  test_showInfo(  QY_ENV  *  pEnv,  char  *  serverIp,  unsigned  short  serverPort,  void  *  pMacsInfo_notused,  int  serviceId,  char  *  ver,  QY_ENC_CTX  *  pCommEncCtx,  SOCK_TIMEOUT  *  pTo  )
{
	 BOOL						bRet  =  FALSE;
	 QY_SOCK					sock;
	 QY_COMM_SESSION			session;
	 BOOL						bSessionOpen		=		FALSE;
	 QY_COMM_RESP				tmpResp;
	 QWM_MACS_INFO				macsInfo;


	 clearQySock(  &sock  );
	 memset(  &session,  0,  sizeof(  session  )  );
	 	 
	 memset(  &macsInfo,  0,  sizeof(  macsInfo  )  );
	 getQwmMacs(  pEnv,  &macsInfo  );
	 
	 if  (  qnmOpenSession(  serverIp,  serverPort,  &macsInfo,  0,  serviceId,  ver,  pCommEncCtx,  &session,  &sock,  pTo,  NULL,  NULL  )  )  goto  errLabel;
	 bSessionOpen		=		TRUE;
	 if  (  !isRcOk(  session.usLastRespCode_i  )  )  goto  errLabel;

	 char* hint;hint = (char*)"hello";

	 if  (  qySendReq(  &session,  &sock,  pTo,  CONST_qyCmd_tryToConnectToServer,  hint,  strlen(hint)  )  )  goto  errLabel;
#if 0
	 if  (  qyRecvResp(  &session,  &sock,  pTo,  &tmpResp,  NULL,  0  )  )  goto  errLabel;
	 if  (  !isRcOk(  tmpResp.head.usCode  )  )  goto  errLabel;
#endif

	 bRet  =  TRUE;

errLabel:

	 if  (  bSessionOpen  )  qnmCloseSession(  &session,  &sock,  pTo  );

	 return  bRet;

}

#ifdef  __isCli__
	//
	int  testInMain_isCli(QY_MC* pQyMc);

		//extern  "C" __declspec(dllexport)  int  dllInit_d3d_isCli();

#endif






	//
	__declspec(dllexport)
		int iimain(int argc, char* argv[]);

	//__declspec(dllexport) int testDec();



 //
 int  testInMain(  QY_MC  *  pQyMc  )
{
	//
	if  (  !pQyMc  )  return  -1;

	int  jj;
	int  ii  =  offsetof(  TRANSFER_VIDEO_DATA,  buf  );
	ii = sizeof(myDRAW_VIDEO_DATA);


	//
	



	//
	int  i;
#ifdef  __isCli__
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	//dllInit_d3d_isCli();


	return  testInMain_isCli(pQyMc);

#endif

	







	return  0;

}





/////////////////
#if 0
CMutexRW *mtxRw=new CMutexRW();

    extern "C" DWORD WINAPI threadProc_testR( LPVOID l );
	    extern "C" DWORD WINAPI threadProc_testW( LPVOID l );

		int sync_traceLogA(char * str )
		{
			CQySyncObj syncObj;
			if(syncObj.sync(_T("syncTraceLog"))) return -1;
			traceLogA(str);
			return 0;
		}

   int testRwLock()
        {
			HANDLE *trs = new HANDLE[10];
            HANDLE *tws=new HANDLE[5];
			int trs_Length=10;
			int tws_Length=5;


			//
			DWORD threadId;
            int i;
            for ( i=0;i< trs_Length; i++)
            {
                trs[i] = CreateThread(NULL,0,threadProc_testR,(LPVOID)i,CREATE_SUSPENDED,&threadId);
                //trs[i].Start(i);
				ResumeThread(trs[i]);
            }
            for (i = 0; i < tws_Length; i++)
            {
				tws[i] = CreateThread(NULL,0,threadProc_testW,(LPVOID)i,CREATE_SUSPENDED,&threadId);
                ResumeThread(tws[i]);
            }

            for (; ; )
            {
                Sleep(5000);
            }

            return 0;
            
        }


        //
    extern "C" DWORD WINAPI threadProc_testR( LPVOID l )
        {
            int id = (int)l;
            std::string str;
            int i;
			char buf[100];

			std::string tag=std::string("rlock") + ltoa(id,buf,10);
            //
            //qyFuncs.mySleep(1000);

            //
            for (i=0; ;i++)          
            {

                //(CQyRWLock rLock=new CQyRWLock())
                {
					CQyRWLock rLock;
                    if (rLock.rLock(mtxRw, 1000) != 0) continue;

					//str = std::string("rlock {0} starts", id);
					str=tag + " starts\n";
					sync_traceLogA((char*)str.c_str());

                    Sleep(300);

                    //str = string.Format("rlock {0} ends", id);
					str=tag+" ends\n";
					sync_traceLogA((char*)str.c_str());
                }

                //
                Sleep(100);
                continue;
            }

        }

        //
    extern "C" DWORD WINAPI threadProc_testW( LPVOID l )
        {
            int id = (int)l;
            std::string str;
            int i;
			char buf[100];

			std::string tag=std::string("wlock") + ltoa(id,buf,10);

            for (i = 0; ; i++)
            {

                //using (CQyRWLock rwLock = new CQyRWLock())
                {
					CQyRWLock rwLock;
                    if (rwLock.wLock(mtxRw, 10000) != 0) {
						str=tag + " wLock failed";
						sync_traceLogA((char*)str.c_str());
						continue;
					}

                    //str = string.Format("wlock {0} starts", id);
					str=tag + " starts\n";
					sync_traceLogA((char*)str.c_str());

                    Sleep(300);

                    //str = string.Format("wlock {0} ends", id);
					str=tag+" ends\n";
					sync_traceLogA((char*)str.c_str());
                }

                //
                Sleep(1000);
                continue;
            }

        }
#endif





#endif
 
#if  0
 int  printImMsgContent_n(  void  *  pSessionParam,  MSG_ROUTE  *  pRoute,  IM_CONTENTU  *  pContent_n,  int  iContentLen,  TCHAR  *  tBuf,  unsigned  int  maxuiBufCnt  )
{
	traceLogA(  "test"  );
	return  0;
}
#endif


 int  getQyMcLogonCfg(  QY_MC  *  pQyMc,  QY_MC_logonCfg  *  p  )
{
	TCHAR			*	pRegVal				=	NULL;
	char				buf[256];
	QY_REG				reg;
	unsigned  char		ucCmd;
	TCHAR				tBuf[255  +  1]		=	_T(  ""  );
	TCHAR			*	pT;
	long				lVal;


	memset(  p,  0,  sizeof(  p[0]  )  );

	memset(  &reg,  0,  sizeof(  reg  )  );
	reg.hKeyRoot0  =  HKEY_LOCAL_MACHINE;
	//	safeStrnCpy(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	lstrcpyn(  reg.rootKey,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );
	
	lVal  =  DEFAULT_qyMc_minPasswdLen;
	pRegVal  =  (TCHAR*)_T(  CONST_regValName_minPasswdLen  );
	/*
	if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  {
		if  (  atol(  buf  )  >=  MIN_qyMc_passwdLen  )  lVal  =  atol(  buf  );
	}
	*/
	if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
		if  (  _ttol(  tBuf  )  >=  MIN_qyMc_passwdLen  )  lVal  =  _ttol(  tBuf  );
	}
	p->usMinPasswdLen  =  lVal;
	
	lVal  =  DEFAULT_qyMc_maxInvalidLogonAttempts;
	pRegVal  =  (TCHAR*)_T(  CONST_regValName_maxInvalidLogonAttempts  );
	if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )  )  {
		if  (  atol(  buf  )  >  0  &&  atol(  buf  )  <=  MAX_qyMc_invalidLogonAttempts  )  lVal  =  atol(  buf  );
	}
	p->usMaxInvalidLogonAttempts  =  lVal;


	return  0;
}


 int  getDynCfg_isClient(  QY_MC  *  pQyMc,  QNM_CNT_CFG  *  pDynCfg  )
{
	 int						iErr	=	-1;
	 QNM_CNT_CFG				cntCfg_sys;
	 QNM_CNT_CFG				cntCfg;
	 int						i;
	 //
	 if  (  !pDynCfg  )  return  -1;

	 memset(  pDynCfg,  0,  sizeof(  pDynCfg[0]  )  );
	 memset(  &cntCfg_sys,  0,  sizeof(  cntCfg_sys  )  );
	 memset(  &cntCfg,  0,  sizeof(  cntCfg  )  );
	 //
	 if  (  getQnmCntCfg(  0,  FALSE,  pQyMc->iServiceId,  HKEY_LOCAL_MACHINE,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  &cntCfg_sys  )  )  goto  errLabel;
	 if  (  !bSupported_devAuth(  )  )  {		
		 if  (  getQnmCntCfg(  0,  FALSE,  pQyMc->iServiceId,  HKEY_CURRENT_USER,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  &cntCfg  )  )  goto  errLabel;
	 }
	 //
	 if  (  bIpValid(  cntCfg_sys.cntIp  )  )  {
		 safeStrnCpy(  cntCfg_sys.cntIp,  pDynCfg->cntIp,  mycountof(  pDynCfg->cntIp  )  );
		 pDynCfg->ucbSys_cntIp  =  TRUE;
		}
	 else  if  (  bIpValid(  cntCfg.cntIp  )  )  {
			   safeStrnCpy(  cntCfg.cntIp,  pDynCfg->cntIp,  mycountof(  pDynCfg->cntIp  )  );				   
	 }
	 //
	 for  (  i  =  0;  i  <  mycountof(  cntCfg.cntAddrs  );  i  ++  )  {
		  if  (  cntCfg_sys.cntAddrs[i][0]  )  {
			  safeStrnCpy(  cntCfg_sys.cntAddrs[i],  pDynCfg->cntAddrs[i],  mycountof(  pDynCfg->cntAddrs[i]  )  );
			  pDynCfg->ucbSys_cntAddrs[i]  =  TRUE;
			  }
		  else  if  (  cntCfg.cntAddrs[i][0]  )  {
					safeStrnCpy(  cntCfg.cntAddrs[i],  pDynCfg->cntAddrs[i],  mycountof(  pDynCfg->cntAddrs[i]  )  );
		  }
	 }

	 //  
	 if  (  cntCfg_sys.usCntPort  )  {
		 pDynCfg->usCntPort  =  cntCfg_sys.usCntPort;
		 pDynCfg->ucbSys_cntPort  =  TRUE;
	 }
	 else  if  (  cntCfg.usCntPort  )  {
		       pDynCfg->usCntPort  =  cntCfg.usCntPort;
			   }
	 else  {
		   pDynCfg->usCntPort  =  qnmCntPort(  pQyMc->iServiceId  );
	 }

	 //  2010/07/27
	 if  (  pQyMc->cfg.bGetPolicyFromIni  )  {
		 char	buf[32];
	    
		 if  (  !getCfgValByName(  pQyMc->cfg.iniFullFileName,  (char*)CONST_regValName_cntIp,  buf,  sizeof(  buf  )  )  )  {
			 trim(  buf  );
			 if  (  bIpValid(  buf  )  )  {
				 safeStrnCpy(  buf,  pDynCfg->cntIp,  mycountof(  pDynCfg->cntIp  )  );
			 }
		 }
		 if  (  !getCfgValByName(  pQyMc->cfg.iniFullFileName,  (char*)CONST_regValName_cntAddr1,  buf,  sizeof(  buf  )  )  )  {
			 trim(  buf  );
			 if  (  buf[0]  )  {
				 safeStrnCpy(  buf,  pDynCfg->cntAddrs[0],  mycountof(  pDynCfg->cntAddrs[0]  )  );
			 }
		 }
		 //
		 if  (  !getCfgValByName(  pQyMc->cfg.iniFullFileName,  (char*)CONST_regValName_cntPort,  buf,  sizeof(  buf  )  )  )  {
			 trim(  buf  );			 
			 if  (  buf[0]  )  {
				 pDynCfg->usCntPort  =  atol(  buf  );
			 }
		 }
		 if  (  !pDynCfg->usCntPort  )  pDynCfg->usCntPort  =  qnmCntPort(  pQyMc->iServiceId  );

	}

	 iErr  =  0;
errLabel:
	 return  iErr;
}
 
 BOOL  bProcessOsUsrAdmin(  )
{
	BOOL	bRet	=	FALSE;

	int		iGrpFlg	=	0;

	if  (  !qyGetProcessGrps(  &iGrpFlg  )
		&&  (  iGrpFlg  &  (  1  <<  CONST_qyGrpBit_administrators  )  )  )
	{
		bRet  =  TRUE;
	}

	return  bRet;
 }

 int  getQyMcInitialCfg(  QY_MC  *  pQyMc,  QY_MC_CFG  *  pCfg  )
{
	 int		iErr		=	-1;
	 BOOL		bRet		=	FALSE;
	 TCHAR		tBuf[1024]	=	_T(  ""  );
	 char		buf[256]	=   "";
	 QY_REG		reg;

#ifdef  __DEBUG__
	    //
	    //
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s"  ),  tBuf,  _T(  "test"  )  );
		OutputDebugString(  tBuf  );
		//
		//
	    //
		testHook(  );
#endif


	
#if  0
	 {
		 int		iGrpFlg	=	0;

		 if  (  !qyGetProcessGrps(  &iGrpFlg  )
			 &&  (  iGrpFlg  &  (  1  <<  CONST_qyGrpBit_administrators  )  )  )
		 {
			 pQyMc->ucbOsUsrAdmin  =  TRUE;
		 }
	 }
#endif

	 if  (  initQnmEnc(  &pQyMc->encCtx,  NULL,  NULL,  &pQyMc->commEncCtx  )  )  goto  errLabel;
	 pQyMc->ucbEncInited  =  TRUE;

	 if  (  !(  pCfg->pSysCfg  =  getQnmSysCfgInfo(  pQyMc->iSystemId,  pQyMc->iAppType  )  )  )  {
		 traceLogA(  (char*)  "ÇëÉèÖÃsysCfgInfo"  );  goto  errLabel;
	 }
	 if  (  !(  pCfg->pGuiCfg  =  getQnmGuiCfgInfo(  pQyMc->iSystemId,  pQyMc->iAppType  )  )  )  {
		 traceLogA(  (char*)  "ÇëÉèÖÃguiCfgInfo"  );  goto  errLabel;
	 }
	 if  (  getQnmModulesLoadedInfo(  &pCfg->modulesLoadedInfo  )  )  goto  errLabel;	//  2004/08/16

	 if  (  parseCfgs_qyMc(  &pQyMc->cfg  )  )  goto  errLabel;		//  2007/06/16

	 //
//  #if defined(  __WINCE__  )  ||  defined(  __DEBUG__  )
#ifdef	__WINCE__
		pCfg->bGetPolicyFromIni  =  TRUE;
#endif

	 //
	 if  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  {


		 //
		 if  (  pQyMc->appParams.serverAddr[0]  &&  pQyMc->appParams.port  )  {
			 pQyMc->cfg.dynCfg.cnt.usCntPort  =  pQyMc->appParams.port;
			 safeStrnCpy(  pQyMc->appParams.serverAddr,  pQyMc->cfg.dynCfg.cnt.cntAddrs[0],  mycountof(  pQyMc->cfg.dynCfg.cnt.cntAddrs[0]  )  );
			 }
		 else  {

			   if  (  getDynCfg_isClient(  pQyMc,  &pQyMc->cfg.dynCfg.cnt  )  )  goto  errLabel;
		 }
		 //
	 }


	 //  2004/03/23  
 	 //  ¼ì²éÓ²¼þÉú³ÉµÄlicenseÐÅÏ¢ÊÇ·ñÕýÈ·£¬ÓÐ´íÎóÔòÍË³ö!	 
	 if  (  pQyMc->iSystemId  ==  CONST_qySystemId_secChk
		 ||  pQyMc->iSystemId  ==  CONST_qySystemId_nms  )  
	 {
#if  !defined(  __isCli__  )  &&  !defined(  __APP_qyMc_touchscreen__  )
		 if  (  !bQnmHardwareLicenseOk(  &pQyMc->env  )  )  {
			 myMessageBox(  NULL,  _T(  ""  ),  _T(  "Qycx"  ),  MB_OK  ); goto  errLabel;
		 }
#endif
	 } 


	 //  2007/11/20
	 if  (  pQyMc->iAppType  !=  CONST_qyAppType_client  )  {

#if  !defined(  __isCli__  )  &&  !defined(  __APP_qyMc_touchscreen__  )

		 //  2016/05/12
		 int  b_qm_tttMac(  QY_ENV  *  pEnv  );
		 BOOL  bTttMac  =  b_qm_tttMac(  &pQyMc->env  );
		 
		 //
	 	 #ifndef  __WITHOUT_CHKDOG__
				 //  ³õÊ¼»¯Èí¼þ¹·Ð£Ñé¹¤×÷£¬×¢Òâ£¬Ã»Çå³ý¹¤×÷£¬2003/12/05
			     if  (  initRnbDog(  &pQyMc->licenseCtx,  bTttMac,  NULL  )  )  {
					 //  traceLogA(  (char*)  "Èí¼þ¹·Ð£Ñé³õÊ¼»¯Ê§°Ü"  );		//  2005/04/20ÈÕ¼ÓÈë¶Ô²¦ºÅ¼ì²â¼àÊÓ¶ËµÄ¹ýÂË
					 #ifdef  __DEBUG__
							 traceLogA(  (char*)  "Oh! Dog, dog, my dog!"  );
					 #endif
					 //
					 if  (  pQyMc->iAppId  !=  CONST_qyAppType_interMonOfBhb  )  goto  errLabel;	 
				 }
				 //
		 #endif

#endif

	 }

	 //  traceLogA(  (char*)  "×¼±¸½¨Á¢ÓÃ»§Êý¾Ý¿â"  ); 

	 safeTcsnCpy(  pCfg->pSysCfg->rootKey_mcGui,  pCfg->rootKey,  mycountof(  pCfg->rootKey  )  );
	 /*
	 if  (  !qyGetRegCfg(  pCfg->rootKey,  _T(  QY_INSTALLDIR_VALNAME  ),  (  char  *  )pCfg->installDir,  sizeof(  pCfg->installDir  )  )  )  {
		 if  (  tTrailDir(  pCfg->installDir,  mycountof(  pCfg->installDir  )  )  )  goto  errLabel;
		 }
	 else  {
		   traceLogA(  (char*)  "getQyMcInitialCfg failed: can't get installDir"  );  
		   #ifndef  __WINCE__
				    goto  errLabel;
		   #endif
	 }
	 */
	 GetModuleFileName(NULL, pCfg->installDir,mycountof(pCfg->installDir));
	 showInfo_open0(0,_T("moduleFileName"),pCfg->installDir);
	 TCHAR* pT;pT = _tcsrchr(pCfg->installDir, _T('\\'));
	 if(pT==NULL ) goto errLabel;
	 *pT=0;
	 pT=_tcsrchr(pCfg->installDir,_T('\\'));
	 if(pT==NULL ) goto errLabel;
	 pT ++ ; *pT=0;
	 showInfo_open0(0,_T("installDir"),pCfg->installDir);
	 //
	 



	 //
	 if  (  !pQyMc->appParams.bMcu  )
	 {
		 //
		   //  if  (  !SUCCEEDED(  mySHGetFolderPathW(  &pQyMc->env,  NULL,  CSIDL_APPDATA,  NULL,  0,  pCfg->appDataDir  )  )  )  goto  errLabel;
		   if  (  !SHGetSpecialFolderPath(  NULL,  pCfg->appDataDir,  CSIDL_APPDATA,  0  )  )  {
			   showInfo_open0(  0,  0,  _T(  "getQyMcInitialCfg: SHGetSpecialFolderPath failed"  )  );
			   goto  errLabel;
		   }
		   traceLogA(  (char*)  "appDataDir is %S",  pCfg->appDataDir  );
		   if  (  tTrailDir(  pCfg->appDataDir,  mycountof(  pCfg->appDataDir  )  )  )  goto  errLabel;
		   _sntprintf(  pCfg->appDataDir,  mycountof(  pCfg->appDataDir  ),  _T(  "%sqycx\\"  ),  pCfg->appDataDir  ); 
		   bRet  =  CreateDirectory(  pCfg->appDataDir,  NULL  );
		   if  (  !bRet  &&  GetLastError(  )  !=  ERROR_ALREADY_EXISTS  )  {
			   qyDisplayLastError(  (char*)"Creating workDir"  );  goto  errLabel;
		   }
		   _sntprintf(  pCfg->appDataDir,  mycountof(  pCfg->appDataDir  ),  _T(  "%s%s\\"  ),  pCfg->appDataDir,  qyGetDesByType1(  CONST_qyServiceIdTable,  pQyMc->iServiceId  )  );
		   bRet  =  CreateDirectory(  pCfg->appDataDir,  NULL  );
		   if  (  !bRet  &&  GetLastError(  )  !=  ERROR_ALREADY_EXISTS  )  {
			   qyDisplayLastError(  (char*)"Creating workDir"  );  goto  errLabel;
		   }
		   //
		   bRet  =  CreateDirectory(  CQyString(  pCfg->appDataDir  )  +  CQyString(  _T(  CONST_qyDbSubDir  )  ),  NULL  );
		   if  (  !bRet  &&  GetLastError(  )  !=  ERROR_ALREADY_EXISTS  )  {
			   qyDisplayLastError(  (char*)"Creating dbDir"  );  goto  errLabel;
		   }
		   //
	 }
	 // 
	 _sntprintf(  pCfg->workDir,  mycountof(  pCfg->workDir  ),  _T(  "%s%s"  ),  pCfg->appDataDir,  _T(  CONST_qyWorkSubDir  )  );
	 if  (  !pQyMc->appParams.bMcu  )  {
		 bRet  =  CreateDirectory(  pCfg->workDir,  NULL  );
		 if  (  !bRet  &&  GetLastError(  )  !=  ERROR_ALREADY_EXISTS  )  {
			 qyDisplayLastError(  (char*)"Creating workDir"  );  goto  errLabel;
		 }
	 }
	 //  2008/01/10
#ifndef  __WINCE__
	 if  (  pCfg->installDir[0]  )  {
		 _sntprintf(  pCfg->cusModuleDir,  mycountof(  pCfg->cusModuleDir  ),  _T(  "%s%s"  ),  pCfg->installDir,  CQyString(  (char*)CONST_qyCusModuleSubDir  )  );
		 if  (  !pQyMc->appParams.bMcu  )  {
			 bRet  =  CreateDirectory(  pCfg->cusModuleDir,  NULL  );
			 if  (  !bRet  &&  GetLastError(  )  !=  ERROR_ALREADY_EXISTS  )  {
				 qyDisplayLastError(  (char*)"Creating cusModuleDir"  );  
			 }
		 }
	 }
#else
	 GetModuleFileName(  NULL,  pCfg->cusModuleDir,  mycountof(  pCfg->cusModuleDir  )  );
	 TCHAR  *  pT  =  _tcsrchr(  pCfg->cusModuleDir,  _T(  '\\'  )  );
	 if  (  !pT  )  goto  errLabel;
	 pT  ++  ;	*pT  =  0;
#endif
	 

	 //  
	 _sntprintf(  pCfg->singleInstanceStr,  mycountof(  pCfg->singleInstanceStr  ),  _T(  "xz8%d%d2%s"  ),  pQyMc->iSystemId,  pQyMc->iAppType,  CQyString(  (char*)CONST_qyLckFileName_qyMc  )  );  //  2003/10/05ÐÞ¸ÄÒÔÊ¹²»Í¬µÄÏµÍ³½çÃæÄÜÍ¬Ê±Æô¶¯

	 //  safeWcsnCpy(  _T(  QMG_TMPPOLICYFILENAME  ),  pCfg->tmpPolicyFileName,  mycountof(  pCfg->tmpPolicyFileName  )  );
	 //  safeWcsnCpy(  _T(  QM_POLICYFILENAME  ),  pCfg->policyFileName,  mycountof(  pCfg->policyFileName  )  );


	 //  2009/03/04
	 getQyMcLogonCfg(  pQyMc,  &pCfg->logon  );


	 //  ÒÔÏÂÊÇ½çÃæ°´Å¥ÅäÖÃ
	 pCfg->btn.horOffset		=  DEFAULT_HOR_OFFSET;
	 pCfg->btn.verOffset		=  DEFAULT_VER_OFFSET;
	 pCfg->btn.topOffset		=  DEFAULT_TOP_OFFSET;
	 pCfg->btn.bottomOffset		=  DEFAULT_BOTTOM_OFFSET;
	 pCfg->btn.width			=  DEFAULT_BTN_WIDTH;
	 pCfg->btn.height			=  DEFAULT_BTN_HEIGHT;

	 //  Ê÷µÄÍ¼±êÉèÖÃ 
	 //
	 //  ÔÚÏßÍ¼±ê
	 pCfg->image.normal.nImage_unknown						=	4;
	 pCfg->image.normal.nImage_router						=	5;
	 pCfg->image.normal.nImage_switcher3					=	6;
	 pCfg->image.normal.nImage_switcher2					=	7;
	 pCfg->image.normal.nImage_pcNormal						=	15;
	 pCfg->image.normal.nImage_pcAdminDown					=	13;
	 pCfg->image.normal.nImage_pcWait						=	14;
	 
	 //  ÀëÏßÍ¼±ê	 
	 pCfg->image.offline.nImage_unknown						=	17;
	 pCfg->image.offline.nImage_router						=	18;
	 pCfg->image.offline.nImage_switcher3					=	19;
	 pCfg->image.offline.nImage_switcher2					=	20;
	 pCfg->image.offline.nImage_pcNormal					=	16;
	 
	 //  ½ÓÈëÍ¼±ê
	 pCfg->image.directConn.nImage_unknown					=	pCfg->image.normal.nImage_unknown;
	 pCfg->image.directConn.nImage_pcNormal					=	23;
	 pCfg->image.directConn.nImage_pcAdminDown				=	21;
	 pCfg->image.directConn.nImage_pcWait					=	22;
	 	 
	 //  ÔÚÏß¸æ¾¯Í¼±ê
	 pCfg->image.normalWarn.nImage_unknown					=	29;
	 pCfg->image.normalWarn.nImage_pcAdminDown				=	25;
	 pCfg->image.normalWarn.nImage_pcWait					=	26;
	 pCfg->image.normalWarn.nImage_pcNormal					=	27;
	 pCfg->image.normalWarn.nImage_router					=	30;
	 pCfg->image.normalWarn.nImage_switcher3				=	31;
	 pCfg->image.normalWarn.nImage_switcher2				=	32;

	 //  ÀëÏß¸æ¾¯Í¼±ê
	 pCfg->image.offlineWarn.nImage_unknown					=	33;
	 pCfg->image.offlineWarn.nImage_router					=	34;
	 pCfg->image.offlineWarn.nImage_switcher3				=	35;
	 pCfg->image.offlineWarn.nImage_switcher2				=	36;
	 pCfg->image.offlineWarn.nImage_pcNormal				=	28;
	 pCfg->image.offlineWarn.nImage_pcWait					=	28;
	 pCfg->image.offlineWarn.nImage_pcAdminDown				=	28;

	 //  °ó¶¨Í¼±ê
	 pCfg->image.secureConn.nImage_unknown					=	pCfg->image.normal.nImage_unknown;
	 pCfg->image.secureConn.nImage_router					=	pCfg->image.normal.nImage_router;
	 pCfg->image.secureConn.nImage_switcher3				=	pCfg->image.normal.nImage_switcher3;
	 pCfg->image.secureConn.nImage_switcher2				=	pCfg->image.normal.nImage_switcher2;
	 pCfg->image.secureConn.nImage_pcAdminDown				=	37;
	 pCfg->image.secureConn.nImage_pcWait					=	38;
	 pCfg->image.secureConn.nImage_pcNormal					=	39;

	 //  ¶Ë¿Ú×´Ì¬ºÍÆäËûÍ¼±ê	 
	 pCfg->image.nImage_portAdminDown						=	8;
	 pCfg->image.nImage_portWait							=	9;
	 pCfg->image.nImage_portUp								=	10;
	 pCfg->image.nImage_connectedDev						=	1;
	 //
	 pCfg->image.nImage_folder								=	2;
	 pCfg->image.nImage_selectedFolder						=	3;
	 pCfg->image.nImage_col2								=	2;
	 pCfg->image.nImage_selectedCol2						=	3;
	 pCfg->image.nImage_col3								=	2;
	 pCfg->image.nImage_selectedCol3						=	3;
	 pCfg->image.nImage_col4								=   pCfg->image.normal.nImage_pcNormal;
	 pCfg->image.nImage_selectedCol4						=   pCfg->image.normal.nImage_pcNormal;
	 pCfg->image.nImage_unRegPc								=	pCfg->image.normal.nImage_pcNormal;
	 pCfg->image.nImage_selectedUnRegPc						=	pCfg->image.normal.nImage_pcNormal;
	 //
	 pCfg->image.nImage_pcUsrInfo							=	2;
	 pCfg->image.nImage_selectedPcUsrInfo					=	2;
	 pCfg->image.nImage_pcStatus							=	2;
	 pCfg->image.nImage_selectedPcStatus					=	2;
	 pCfg->image.nImage_pcOpNode							=	2;
	 pCfg->image.nImage_selectedPcOpNode					=	2;
	 pCfg->image.nImage_os									=	2;
	 pCfg->image.nImage_selectedOs							=	2;
	 //
	 pCfg->image.nImage_info								=	45;
	 pCfg->image.nImage_selectedInfo						=	45;
	 //
	 pCfg->image.nImage_pcHardwareEnv						=	2;
	 pCfg->image.nImage_selectedPcHardwareEnv				=	2;
	 pCfg->image.nImage_pcSoftwareEnv						=	2;
	 pCfg->image.nImage_selectedPcSoftwareEnv				=	2;
	 pCfg->image.nImage_pcRegistry							=	2;
	 pCfg->image.nImage_selectedPcRegistry					=	2;
	 pCfg->image.nImage_hardware							=	45;
	 pCfg->image.nImage_software							=	45;
	 //  ²¹¶¡ÅäÖÃ
	 pCfg->image.nImage_sp									=	pCfg->image.nImage_software;

	 //  isÅäÖÃ£¬2007/05/12
	 pCfg->image.nImage_messenger							=	pCfg->image.nImage_unRegPc;
	 pCfg->image.nImage_selectedMessenger					=	pCfg->image.nImage_selectedUnRegPc;
	 pCfg->image.nImage_me									=	pCfg->image.nImage_info;
	 pCfg->image.nImage_selectedMe							=	pCfg->image.nImage_selectedInfo;
	 pCfg->image.nImage_imGrps								=	pCfg->image.nImage_folder;
	 pCfg->image.nImage_selectedImGrps						=	pCfg->image.nImage_selectedFolder;
	 pCfg->image.nImage_imGrp								=	45;
	 pCfg->image.nImage_selectedImGrp						=	45;

	 pCfg->image.nImage_activeMem							=	pCfg->image.normal.nImage_pcNormal;
	 pCfg->image.nImage_requestingMem						=	pCfg->image.normal.nImage_pcWait;
	 pCfg->image.nImage_interruptedSpeakingMem				=	pCfg->image.normal.nImage_pcAdminDown;

	
	 //  2018/06/28
	 pCfg->image.nImage_screen  =  46;	
	 pCfg->image.nImage_webcam  =  47;
	 //  2018/12/27
	 pCfg->image.nImage_mic  =  48;

	 //  ÒÔÏÂÊÇÆäËûÉèÖÃ
	 pCfg->mutexTimeout  =  DEFAULT_QY_MC_MUTEX_TIMEOUT;

#ifdef  __useMfc__

#if  0
	 if  (  pQyMc->iSystemId  ==  CONST_qySystemId_bhb  )  pCfg->nIdToolBar  =  IDR_TOOLBAR_bhb;
	 else  
#endif
		 pCfg->nIdToolBar  =  IDR_MAINFRAME;
#endif


	 //
	 if  (  pCfg->installDir[0]  )  {
		 if  (  pCfg->pGuiCfg  )  _sntprintf(  pCfg->cfgFullFileName,  mycountof(  pCfg->cfgFullFileName  ),  _T(  "%s%s%s"  ),  pCfg->installDir,  CQyString(  (char*)CONST_qyResSubDir  ).GetBuffer(  0  ),  CQyString(  pCfg->pGuiCfg->qmCfgPureFile  ).GetBuffer(  0  )  );				//  2003/09/19
		 if  (  pCfg->pGuiCfg  )  _sntprintf(  pCfg->iniFullFileName,  mycountof(  pCfg->iniFullFileName  ),  _T(  "%s%s%s"  ),  pCfg->installDir,  CQyString(  (char*)CONST_qyCfgSubDir  ),  CQyString(  pCfg->pGuiCfg->qmCfgIniFile  )  );
		 }
	 else  {
		   TCHAR	module[MAX_PATH  +  1];
		   TCHAR	*	pT;
		   GetModuleFileName(  NULL,  module,  mycountof(  module  )  );
		   pT  =  _tcsrchr(  module,  _T(  '\\'  )  );
		   if  (  !pT  )  goto  errLabel;
		   pT  ++  ;  *pT  =  0;
		   
		   if  (  pCfg->pGuiCfg  )  _sntprintf(  pCfg->cfgFullFileName,  mycountof(  pCfg->cfgFullFileName  ),  _T(  "%s%s"  ),  module,  CQyString(  pCfg->pGuiCfg->qmCfgPureFile  )  );				//  2003/09/19
		   if  (  pCfg->pGuiCfg  )  _sntprintf(  pCfg->iniFullFileName,  mycountof(  pCfg->iniFullFileName  ),  _T(  "%s%s"  ),  module,  CQyString(  pCfg->pGuiCfg->qmCfgIniFile  )  );
	 }

	 
	 //  
	 if  (  pQyMc->iSystemId  ==  CONST_qySystemId_netMc2  &&  !getCfgValByName(  pCfg->cfgFullFileName,  (char*)CONST_cfgName_bThinkPad,  buf,  sizeof(  buf  )  )  &&  !_stricmp(  buf,  CONST_cfgVal_bThinkPad  )  )  pCfg->ucbThinkPad  =  TRUE;
	 if  (  !getCfgValByName(  pCfg->cfgFullFileName,  (char*)CONST_cfgName_bBhqj,  buf,  sizeof(  buf  )  )  &&  !_stricmp(  buf,  CONST_cfgVal_bBhqj  )  )  pCfg->ucbBhqj  =  TRUE;
	 if  (  !getCfgValByName(  pCfg->cfgFullFileName,  (char*)CONST_cfgName_bHaveDj,  buf,  sizeof(  buf  )  )  &&  !_stricmp(  buf,  CONST_cfgVal_bHaveDj  )  )  pCfg->ucbHaveDj  =  TRUE;		//  2005/08/27
	 if  (  !getCfgValByName(  pCfg->cfgFullFileName,  (char*)CONST_cfgName_bAdvancedOptionEnabled,  buf,  sizeof(  buf  )  )  &&  !_stricmp(  buf,  CONST_cfgVal_bAdvancedOptionEnabled  )  )  pCfg->ucbAdvancedOptionEnabled  =  TRUE;	//  2005/11/18
	 if  (  !getCfgValByName(  pCfg->cfgFullFileName,  (char*)CONST_cfgName_bRasControlNotSupported,  buf,  sizeof(  buf  )  )  &&  !_stricmp(  buf,  CONST_cfgVal_bRasControlNotSupported  )  )  pCfg->ucbRasControlNotSupported  =  TRUE;


	 pCfg->ucbAdvancedVer  =  bQmAdvancedVer(  0,  pCfg->cfgFullFileName,  0  );	//  2005/09/01
	 //  
	 pCfg->ucbAutoLogonSupported	=	FALSE;				//  2006/03/08£¬__SUPPORT_AUTOLOGON__
	 #ifndef  __NOTSUPPORT_REMOTEDESKTOP__
			  pCfg->ucbRemoteDesktopSupported  =  TRUE;		//  2006/03/08£¬__NOTSUPPORT_REMOTEDESKTOP__
	 #endif
	 #ifndef  __NOTSUPPORT_PCMON__
			  pCfg->ucbPcMonSupported  =  TRUE;				//  2006/03/08£¬__NOTSUPPORT_PCMON__
	 #endif
	 #ifndef  __NOTSUPPORT_FILEMON__
			  pCfg->ucbFileMonSupported  =  TRUE;			//  2006/03/25
	 #endif
	 

	 #ifdef  __NOTSUPPORT_dblClk__							//  2011/03/26
			 pCfg->ucbNotSupported_dblClk  =  TRUE;
	 #endif


	 //  2007/03/25
	 if  (  pQyMc->iSystemId  ==  CONST_qySystemId_messenger  &&  pQyMc->iAppType  ==  CONST_qyAppType_client  )  {


		 #if  0	//  defined(  __DEBUG__  )  
				 pCfg->ucbNotNeedLocked  =  TRUE;
		 #endif

		 pCfg->ucbUseTrayIcon  =  TRUE;
#ifndef  __WINCE__
#ifndef __qmdConn__
		 pCfg->iIDR_TRAY  =  IDR_TRAY_online;	//  
#endif
#endif
		 //  traceLogA(  (char*)  ""  );


	 }

	 //  2009/08/05
	 pQyMc->cfg.bUseDxSurface  =  TRUE;

	 setSockTimeout(  &pQyMc->cfg.to  );	//  2005/08/19
	 //
	 pQyMc->cfg.to.iSelect  =  1000;
	 //
#ifdef  __DEBUG__
	 //pQyMc->cfg.to.iRead = 30000;
#endif
	 // 
	 //
	 pQyMc->cfg.iTimeoutInMs_channelIdle_others  =  DEFAULT_iTimeoutInMs_channelIdle_others;
	 //  pQyMc->cfg.iTimeoutInMs_channelIdle_recv_others  =  DEFAULT_iTimeoutInMs_channelIdle_recv_others;
	 pQyMc->cfg.iTimeoutInMs_channelIdle_recv_talk  =  DEFAULT_iTimeoutInMs_channelIdle_recv_talk;
	 
	 //  2010/09/02
	 pQyMc->cfg.usDelayInMsToViewToolbar  =  bLikeXp(  )  ?  1500  :  800;	

	 //
#if  0
	 pQyMc->cfg.rwLockParam.uiMaxCnt_sema			=	CONST_uiInitCnt_sema_q2SyncFlg;
	 pQyMc->cfg.rwLockParam.uiInitCnt_sema			=	pQyMc->cfg.rwLockParam.uiMaxCnt_sema  -  1;
	 pQyMc->cfg.rwLockParam.uiMilliSeconds_mutex_r	=	10000;
	 pQyMc->cfg.rwLockParam.uiMilliSeconds_sema_r	=	10000;
	 pQyMc->cfg.rwLockParam.uiMilliSeconds_mutex_w	=	10000;
	 pQyMc->cfg.rwLockParam.uiMilliSeconds_sema_w	=	10000;
#endif
	 RW_lock_param_init(  &pQyMc->cfg.rwLockParam  );

	 //
	 qyRefreshRegCfg_ucb(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_startRegScan  ),  &pCfg->ucbStartRegScan  );  
	 
	 pQyMc->cfg.iType_qnmTmpTab  =  pQyMc->iSystemId;

	 //  2005/01/24
	 getCustomComm(  &pCfg->custom  );

	 //  2007/06/09
	 pCfg->usMaxDisplayedElemsPerWnd  =  DEFAULT_maxDisplayedElemsPerWnd;
	 pCfg->usMaxDisplayedWnds  =  DEFAULT_maxDisplayedWnds;
	 //  2007/06/26
	 pCfg->usMaxDisplayedTasksInDlgTalk		=	DEFAULT_maxDisplayedTasksInDlgTalk;


	 int						index;
	 QY_SERVICEGUI_CFG			serviceClientCfg;

	 index  =  0;
	 pQyMc->threadProcs[index]  =  mcThreadProc;		index  ++  ;
	 if  (  pQyMc->iServiceId  ==  CONST_qyServiceId_netMc  )  {
		 memset(  &serviceClientCfg,  0,  sizeof(  serviceClientCfg  )  );
		 serviceClientCfg.iServiceId  =  pQyMc->iServiceId;
		 //  serviceClientCfg.iDbType  =  pQyMc->cfg.db.iDbType;
		 //
		 serviceClientCfg.uiVarSize  =  getVarSize_netMc( pQyMc );
		 serviceClientCfg.pfInitVar  =  initVar_netMcGui;
		 serviceClientCfg.pfExitVar  =  exitVar_netMcGui;
		 //
		 if  (  setServiceGuiCfg(  &serviceClientCfg,  pQyMc  )  )  goto  errLabel;
		 //		 
	 }
	 if  (  pQyMc->iServiceId  ==  CONST_qyServiceId_is  )  {
		 memset(  &serviceClientCfg,  0,  sizeof(  serviceClientCfg  )  );
		 serviceClientCfg.iServiceId  =  pQyMc->iServiceId;
		 //  serviceClientCfg.iDbType  =  pQyMc->cfg.db.iDbType;
		 
		 //		 
		 serviceClientCfg.uiVarSize  =  getVarSize_is(  pQyMc  );		
		 serviceClientCfg.pfInitVar  =  initVar_isGui;
		 serviceClientCfg.pfInit_afterLogon  =  init_afterLogon_isGui;
		 serviceClientCfg.pfExitVar  =  exitVar_isGui;

		 //
		 if  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  {
#ifdef  __isCli__
			 //  2015/01/20
			 if  (  pQyMc->pfNewVar  )  {
				 if  (  !pQyMc->pfFreeVar  )  goto  errLabel;
				 //
				 serviceClientCfg.pfNewVar  =  pQyMc->pfNewVar;
				 serviceClientCfg.pfFreeVar  =  pQyMc->pfFreeVar;				 
				 }
			 else  {
#if  0
				   serviceClientCfg.pfNewVar  =  newVar_isCli;			 
				   serviceClientCfg.pfFreeVar  =  freeVar_isCli;
#endif
				   //  2016/08/12
				   showInfo_open0(  0,  0,  _T(  "getQyMcInitialCfg failed, pQyMc->pfNewVar is null"  )  );
				   #ifdef  __DEBUG__
						   MACRO_qyAssert(  0,  _T(  "getQyMcInitialCfg failed, pQyMc->pfNewVar is null"  )  );
				   #endif
				   goto  errLabel;
			 }
			 //
			 //if  (  !isQmCmd(  pQyMc  )  )  
			 {
				 pQyMc->threadProcs[index]  =  mcThreadProc_isCli;	index  ++  ;
			 }
#endif
			 }
		 else  {
			   pQyMc->threadProcs[index]  =  mcThreadProc_isMgr;  index  ++  ;
		 }
		 //
		 if  (  setServiceGuiCfg(  &serviceClientCfg,  pQyMc  )  )  goto  errLabel;
		 //
	 }

	 MACRO_qyAssert(  index  <=  mycountof(  pQyMc->threadProcs  ),  _T(  "threadProcs overflowed"  )  );
	 //


	 lstrcpyn(  pQyMc->cfg.cusModules.mutexName,  _T(  "syncCusModules"  ),  mycountof(  pQyMc->cfg.cusModules.mutexName  )  );
	 pQyMc->cfg.cusModules.uiMaxCnt_sema  =  10;
	 pQyMc->cfg.cusModules.uiInitCnt_sema  =  pQyMc->cfg.cusModules.uiMaxCnt_sema  -  1;
	 //
	 pQyMc->cfg.cusModules.uiMilliSeconds_mutex_r  =  10000;
	 pQyMc->cfg.cusModules.uiMilliSeconds_sema_r  =  10000;
	 pQyMc->cfg.cusModules.uiMilliSeconds_mutex_w  =  10000;
	 pQyMc->cfg.cusModules.uiMilliSeconds_sema_w  =  10000;



	 iErr  =  0;

errLabel:
	 return  iErr;
}



 //  2006/03/21, Ôö¼Ó´Ë´¦Îª·½±ãÄ³Ð©²»ÊÊºÏÔÚ°²×°³ÌÐòÀï×öµÄÒ»Ð©¹¤×÷ 
 int  initQyMcSys_netMc(  QY_MC  *  pQyMc  )
{
#ifdef  __isCli__
	return 0;
#else
	PC_FILEMON_RULES		oldRules;

	if  (  !bGetDefaultFileMonRules(  pQyMc->gui.pDb,  &oldRules  )  )  memset(  &oldRules,  0,  sizeof(  oldRules  )  );
	//  ÔÚµÚÒ»´Î´ò¿ª´Ë¶Ô»°¿òÊ±£¬×Ô¶¯»¯ÒýÈëÈ±Ê¡¹æÔò
	if  (  !oldRules.uiChangesId  )  {
		resetDefaultFileMonRules(  pQyMc->gui.pDb,  0,  TRUE,  &oldRules  );
		updateFileMonRules(  pQyMc->gui.pDb,  0,  &oldRules  );
	}


	 return  0;
#endif
}


 int  initQyMcSys_mis(  QY_MC  *  pQyMc  )
{
	 return  0;
}


 int  initQyMcSys(  QY_MC  *  pQyMc  )
{
	 int	iErr		=	-1;
	 int	iServiceId	=	qyGetServiceId(  pQyMc->iSystemId  );

	 switch  (  iServiceId  )  {
			 case  CONST_qyServiceId_netMc:
				   iErr  =  initQyMcSys_netMc(  pQyMc  );
				   break;
			 case  CONST_qyServiceId_mis:
				   iErr  =  initQyMcSys_mis(  pQyMc  );
				   break;
			 default:
					break;
					
	 }
	 
	 return  iErr;
}





 int  qmChkAppType(  QY_MC  *  pQM  )
{
	 int	iErr		=	-1;
	 char	buf[1024]	=	"Î´ÖªÏµÍ³ÀàÐÍ";
	 int	iAppType	=  -1;

	 iAppType  =  qyGetAppType(  pQM->iSystemId,  CQyString(  pQM->cfg.rootKey  )  );


	 if  (  iAppType  !=  pQM->iAppType  )  {
		 qyShowHint(  _T(  "ÑÏÖØ¾¯¸æ: ±¾»ú°²×°ÓÐÎª'%s', Óë±¾³ÌÐò²»ÄÜÆ¥ÅäÔËÐÐ, ³ÌÐò½«ÍË³ö"  ),  CQyString(  buf  )  );
		 goto  errLabel;
	 }

	 iErr  =  0;

errLabel:

	 return  iErr;

}











 

//
 void  exitAllDaemonThreads(  QY_MC  * pQM  )
{
	 int  i;

	 traceLogA(  (char*)  "exitAllDaemonThreads(  ) enters."  );

	 if  (  !pQM->bQuit  )  {
		 traceLogA(  (char*)  "exitAllDaemonThreads: bQuit is not false"  );
	 }
	 
	 for  (  i  =  0;  i  <  sizeof(  pQM->hDaemonThreads  )  /  sizeof(  HANDLE  );  i  ++  )  {
		  if  (  pQM->hDaemonThreads[i]  )  {
			  traceLogA(  (char*)  "Waiting for daemon thread %d",  i  );
			  //waitForObject(  &pQM->hDaemonThreads[i],  20000  );
			  waitForObject(  &pQM->hDaemonThreads[i],  200000  );
			  //
#ifdef  __DEBUG__
			  if (pQM->hDaemonThreads[i]) {
				  int  ii = 0;
			  }
#endif
		  }
	
	 }

	 traceLogA(  (char*)  "exitAllDaemonThreads(  ) leaves."  );

	 return;
}


#if  0
 BOOL CALLBACK SetFontProc( HWND hWnd, LPARAM lParam )
{
	HFONT font = ( HFONT )lParam;

	SendMessage( hWnd, WM_SETFONT, ( WPARAM )font, ( LPARAM )MAKELONG( ( WORD )TRUE, 0 ) );

	return TRUE;

}
#endif






 char  *  qyMcShowState(  int  iState  )
{
	 switch  (  iState  )  {
			 case  QY_MC_STATE_FREE:
				   return  (char*)"free";
			 case  QY_MC_STATE_INITED:
				   return  (char*)"inited";
			 case  QY_MC_STATE_USED:
				   return  (char*)"used";
			 case  QY_MC_STATE_STOPDAEMONREFRESH:
				   return  (char*)"stopDaemonRefresh";
			 case  QY_MC_STATE_UNUSE:
				   return  (char*)"unuse";
			 default:
					 break;
	 }
	 return  (char*)"\"unknown state\"";

}



 char  *  qyViewTypeStr(  int  iViewType  )
{
	 switch  (  iViewType  )  {
	         case  QY_VIEWTYPE_MCROOTTREE:
				   return  (char*)"McRootTree";
			 case  QY_VIEWTYPE_MCROOTLIST:
				   return  (char*)"McRootList";
			 case  QY_VIEWTYPE_MCSITELEFT:
				   return  (char*)"McSiteLeft";
			 case  QY_VIEWTYPE_MCSITERIGHT:
				   return  (char*)"McSiteRight";
			 default:
					 break;
	 }

	 return  (char*)"\"Unknown view type\"";

}







 


 //  ¸CVirtualView OnQyComm
 BOOL  bQnmExportCurQuery(  QY_IMEXPORTINFO  *  pExportInfo  )
{
#ifdef  __NOTSUPPORT_DB__
	return  FALSE;
#else

	 BOOL					bRet	=	FALSE;
	 QNM_WMBUF_EXPORT		commBuf;
	 TCHAR				*	pExt;
	 
	 memset(  &commBuf,  0,  sizeof(  commBuf  )  );
	 commBuf.uiType  =  CONST_qyWmParam_export;
	 memcpy(  &commBuf.exportInfo,  pExportInfo,  sizeof(  QY_IMEXPORTINFO  )  );
	 tTrim(  commBuf.exportInfo.fileName  );
	 pExt  =  _tcsrchr(  commBuf.exportInfo.fileName,  _T(  '.' )  );
	 if  (  !pExt  )  goto  errLabel;
	 pExt  ++  ;
	 if  (  !_tcsicmp(  pExt,  _T(  "html"  )  )  ||  !_tcsicmp(  pExt,  _T(  "htm"  )  )  )  commBuf.exportInfo.iFileType  =  CONST_qyFileType_html;
	 else  if  (  !_tcsicmp(  pExt,  _T(  "xls"  )  )  )  commBuf.exportInfo.iFileType  =  CONST_qyFileType_excel;
	 else  goto  errLabel;
 
	 SendMessage(  pExportInfo->hCurWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )&commBuf  );
	 
	 //  2006/02/25
	 _sntprintf(  pExportInfo->docTitle,  mycountof(  pExportInfo->docTitle  ),  _T(  "%s"  ),  commBuf.exportInfo.docTitle  );

	 bRet  =  TRUE;

errLabel:

	 return  bRet;
#endif
}




  BOOL  bQnmImportBhbCfg(  QY_IMEXPORTINFO  *  pImportInfo  )
{
#if defined(  __NOTSUPPORT_qyFile__  )  ||  defined(__useQt__)							//  2011/03/07
		return  FALSE;
#else
	 BOOL				bRet		=	FALSE;
	 CQyFile			file;
	 BOOL				bFileOpen	=	FALSE;
	 char				buf[1024];

	 if  (  !file.Open(  CQyString(  pImportInfo->fileName  ).GetBuffer(  0  ),  CFile::modeRead  )  )  goto  errLabel;
	 bFileOpen  =  TRUE;

	 try  {
	 
		 file.bImportSqlTable(  pImportInfo->pDb,  pImportInfo->iDbType,  myTChar2Str(  CONST_qyFileObjName_bhbScannedIpTab,  buf,  sizeof(  buf  )  ),  " interMonIp,officeName,subOfficeName,startIp,endIp",  0  );
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bQnmImportBhbCfg failed."  )  );
		   goto  errLabel;
	}

	 bRet  =  TRUE;

errLabel:
	 
	 if  (  bFileOpen  )  file.Close(  );

	 return  bRet;
#endif
}




				  

