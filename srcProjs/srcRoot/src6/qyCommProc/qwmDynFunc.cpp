
#include	"stdafx.h"
#include	"qyPrecomp.h"
#include	<winsock2.h>
#include	<windows.h>
#include	<windef.h>
#include	<lmcons.h>
#ifndef  __WINCE__
		 #include	<Winternl.h>
		 #include	<lmshare.h>
#endif
#include	<tlhelp32.h>
#include	<iphlpapi.h>


#include	"qyCommon.h"
#include	"qwmDynFunc.h"
#include	"qyCommCommon.h"
#include	"qyWmComm.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	<tchar.h>
#include	"qyTCharCommProc.h"
#include	"qySyncCommProc.h"



 //  QWM_DYN_LIB	gDynLib;

 extern  "C"  int  initDynLib(  void  **  pp  )
{
	int				iErr				=	-1;
	int				iPlatformId			=	-1;		//  2005/07/03
	BOOL			bRasManExists		=	FALSE;
	TCHAR			systemDir[MAX_PATH  +  1],  svLibName[MAX_PATH  +  1];
	HINSTANCE		hDll				=	NULL;

	traceLogA(  (char*)"InitDynamicLibraries( ) enters."  );

	if  (  !pp  )  return  -1;
	if  (  *pp  )  {
		traceLogA(  (char*)"*pp is not null"  );  return  -1;
	}

	QWM_DYN_LIB	*	pDynLib	=	(  QWM_DYN_LIB  *  )mymalloc(  sizeof(  QWM_DYN_LIB  )  );
	if  (  !pDynLib  )  goto  errLabel;
	memset(  pDynLib,  0,  sizeof(  pDynLib[0]  )  );

	//GetOSVersion(  );
	if  (  !bQyGetSystemVersionEx( &iPlatformId,  NULL,  0,  NULL,  0,  NULL  )  )  goto  errLabel;

	myGetSystemDirectory(  systemDir,  mycountof(  systemDir  )  );
	if  (  tTrailDir(  systemDir,  mycountof(  systemDir  )  )  )  goto  errLabel;
	
#ifndef  __WINCE__
	if  (  g_bIsWinNT  )  {
		if  (  tQyStrCat(  systemDir,  _T(  "NETAPI32.DLL"  ),  svLibName,  mycountof(  svLibName  )  )  )  goto  errLabel;
		//  ghDll_NetApi32 = LoadLibrary("NETAPI32.DLL");
		pDynLib->ghDll_NetApi32  =  LoadLibrary(  svLibName  );
		if  (  pDynLib->ghDll_NetApi32  ==  NULL  )  return  -1;
		pDynLib->pLMSNetSessionEnum = (LMS_NETSESSIONENUM)myGetProcAddress(pDynLib->ghDll_NetApi32, "NetSessionEnum");
		pDynLib->pLMSNetShareEnum = (LMS_NETSHAREENUM)myGetProcAddress(pDynLib->ghDll_NetApi32, "NetShareEnum");
		pDynLib->pLMSNetShareDel = (LMS_NETSHAREDEL)myGetProcAddress(pDynLib->ghDll_NetApi32, "NetShareDel");
		pDynLib->pLMSNetShareAdd = (LMS_NETSHAREADD)myGetProcAddress(pDynLib->ghDll_NetApi32, "NetShareAdd");
		pDynLib->pNetApiBufferFree  =  (  PF_NetApiBufferFree  )myGetProcAddress(pDynLib->ghDll_NetApi32, "NetApiBufferFree");
		pDynLib->pLMSNetServerGetInfo  =  (  LMS_NETSERVERGETINFO  )myGetProcAddress(  pDynLib->ghDll_NetApi32,  "NetServerGetInfo"  );
		pDynLib->pLMSNetUserEnum  =  (  LMS_NETUSERENUM  )myGetProcAddress(  pDynLib->ghDll_NetApi32,  "NetUserEnum"  );
		pDynLib->pNetUserGetGroups  =  (  PF_NetUserGetGroups  )myGetProcAddress(  pDynLib->ghDll_NetApi32,  "NetUserGetGroups"  );					//  2007/02/17
		pDynLib->pNetUserGetLocalGroups  =  (  PF_NetUserGetLocalGroups  )myGetProcAddress(  pDynLib->ghDll_NetApi32,  "NetUserGetLocalGroups"  );	//  2007/02/17

		pDynLib->pNetbios = (NETBIOS)myGetProcAddress( pDynLib->ghDll_NetApi32, "Netbios" );
		} 
	else  {
		if  (  tQyStrCat(  systemDir,  _T(  "NETAPI32.DLL"  ),  svLibName,  mycountof(  svLibName  )  )  )  goto  errLabel; 
		// pDynLib->ghDll_NetApi32 = LoadLibrary("NETAPI32.DLL");
		pDynLib->ghDll_NetApi32  =  LoadLibrary(  svLibName  );
		if  (  tQyStrCat(  systemDir,  _T(  "SVRAPI.DLL"  ),  svLibName,  mycountof(  svLibName  )  )  )  goto  errLabel;
		//  pDynLib->ghDll_SvrApi = LoadLibrary("SVRAPI.DLL"); 
		pDynLib->ghDll_SvrApi  =  LoadLibrary(  svLibName  );
		if  (  !pDynLib->ghDll_NetApi32  ||  !pDynLib->ghDll_SvrApi  )  return  -1;
		pDynLib->pSVRNetSessionEnum = (SVR_NETSESSIONENUM)myGetProcAddress(pDynLib->ghDll_SvrApi, "NetSessionEnum");
		pDynLib->pSVRNetShareEnum = (SVR_NETSHAREENUM)myGetProcAddress(pDynLib->ghDll_SvrApi, "NetShareEnum");
		pDynLib->pSVRNetShareDel = (SVR_NETSHAREDEL)myGetProcAddress(pDynLib->ghDll_SvrApi, "NetShareDel");
		pDynLib->pSVRNetShareAdd = (SVR_NETSHAREADD)myGetProcAddress(pDynLib->ghDll_SvrApi, "NetShareAdd");
		pDynLib->pSVRNetServerGetInfo  =  (  SVR_NETSERVERGETINFO  )myGetProcAddress(  pDynLib->ghDll_SvrApi,  "NetServerGetInfo"  );

		pDynLib->pNetbios = (NETBIOS)myGetProcAddress( pDynLib->ghDll_NetApi32, "Netbios" );
	}
	

	if  (  tQyStrCat(  systemDir,  _T(  "MPR.DLL"  ),  svLibName,  mycountof(  svLibName  )  )  )  goto  errLabel;
	//  pDynLib->ghDll_Mpr  =  LoadLibrary(  "MPR.DLL"  );
	pDynLib->ghDll_Mpr  =  LoadLibrary(  svLibName  );
	if  (  pDynLib->ghDll_Mpr  ==  NULL  )  goto  errLabel;
	if  (  !g_bIsWinNT  )  {
		//  pWNetEnumCachedPasswords = (ENUMPASSWORD)myGetProcAddress(pDynLib->ghDll_Mpr, "WNetEnumCachedPasswords");	//  2006/03/18, Nod杀毒软件瞎报，暂时用不着，故注释掉拉倒
	}	
	pDynLib->pWNetCloseEnum = (WNETCLOSEENUM)myGetProcAddress(pDynLib->ghDll_Mpr, "WNetCloseEnum");
	pDynLib->pWNetEnumResource = (WNETENUMRESOURCE)myGetProcAddress(pDynLib->ghDll_Mpr, "WNetEnumResourceA");
	pDynLib->pWNetOpenEnum = (WNETOPENENUM)myGetProcAddress(pDynLib->ghDll_Mpr, "WNetOpenEnumA");
	pDynLib->pWNetCancelConnection2 = (WNETCANCELCONNECTION2)myGetProcAddress(pDynLib->ghDll_Mpr, "WNetCancelConnection2A");
	pDynLib->pWNetAddConnection2 = (WNETADDCONNECTION2)myGetProcAddress(pDynLib->ghDll_Mpr, "WNetAddConnection2A");
	
	if  (  tQyStrCat(  systemDir,  _T(  "KERNEL32.DLL"  ),  svLibName,  mycountof(  svLibName  )  )  )  goto  errLabel;
	//  pDynLib->ghDll_Kernel32=LoadLibrary("KERNEL32.DLL");
	pDynLib->ghDll_Kernel32  =  LoadLibrary(  svLibName  );
	if  (  pDynLib->ghDll_Kernel32  ==  NULL  )  goto  errLabel;
  	if  (  !g_bIsWinNT  )  {
		pDynLib->pRegisterServiceProcess = (REGSERVICEPROC)myGetProcAddress(pDynLib->ghDll_Kernel32,  "RegisterServiceProcess");
		} 
	else  {
	
		pDynLib->pCreateRemoteThread=(CREATEREMOTETHREAD) myGetProcAddress(pDynLib->ghDll_Kernel32,  "CreateRemoteThread");
        pDynLib->pVirtualProtectEx = (VIRTUALPROTECTEX)myGetProcAddress(pDynLib->ghDll_Kernel32,  "VirtualProtectEx"); 
        pDynLib->pVirtualAllocEx = (VIRTUALALLOCEX)myGetProcAddress(pDynLib->ghDll_Kernel32,  "VirtualAllocEx"); 
        pDynLib->pVirtualQueryEx   = (VIRTUALQUERYEX)myGetProcAddress(pDynLib->ghDll_Kernel32,  "VirtualQueryEx"); 
        pDynLib->pVirtualFreeEx   = (VIRTUALFREEEX)myGetProcAddress(pDynLib->ghDll_Kernel32,  "VirtualFreeEx"); 
		
		//  2005/09/13
		pDynLib->pCreateIoCompletionPort  =  (  PF_CreateIoCompletionPort  )myGetProcAddress(  pDynLib->ghDll_Kernel32,  "CreateIoCompletionPort"  );
		pDynLib->pGetQueuedCompletionStatus  =  (  PF_GetQueuedCompletionStatus  )myGetProcAddress(  pDynLib->ghDll_Kernel32,  "GetQueuedCompletionStatus"  );		
		pDynLib->pPostQueuedCompletionStatus  =  (  PF_PostQueuedCompletionStatus  )myGetProcAddress(  pDynLib->ghDll_Kernel32,  "PostQueuedCompletionStatus"  );		
		pDynLib->pReadDirectoryChangesW  =  (  PF_ReadDirectoryChangesW  )myGetProcAddress(  pDynLib->ghDll_Kernel32,  "ReadDirectoryChangesW"  );  

		//  2006/09/06
		pDynLib->pGetCommandLineW  =	(  PF_GetCommandLineW  )myGetProcAddress(  pDynLib->ghDll_Kernel32,  "GetCommandLineW"  );

		//  2009/10/11
		pDynLib->pGetSystemTimes  =  (  PF_GetSystemTimes  )myGetProcAddress(  pDynLib->ghDll_Kernel32,  "GetSystemTimes"  );

	}
	//  2006/03/25
	if  (  g_bIsWinNT  )  pDynLib->pGetFileAttributesEx	=	(  PF_GetFileAttributesEx  )myGetProcAddress(  pDynLib->ghDll_Kernel32,  "GetFileAttributesExW"  );
	//		
	if  (  g_bIsWinNT  &&  iPlatformId  !=  CONST_qyPlatform_nt  )  {  //  2000以上才支持
		pDynLib->pSetComputerNameEx  =  (  PF_SetComputerNameEx  )myGetProcAddress(  pDynLib->ghDll_Kernel32,  "SetComputerNameExW"  );
		//		
	}
	if  (  iPlatformId  !=  CONST_qyPlatform_nt  )  {	//  仅NT4.0不能支持运行
		pDynLib->pCreateToolhelp32Snapshot = (CREATESNAPSHOT)myGetProcAddress(pDynLib->ghDll_Kernel32,  "CreateToolhelp32Snapshot"); 
		
        pDynLib->pModule32First  = (MODULEWALK)myGetProcAddress(pDynLib->ghDll_Kernel32,  "Module32FirstW"); 
        pDynLib->pModule32Next   = (MODULEWALK)myGetProcAddress(pDynLib->ghDll_Kernel32,  "Module32NextW"); 
		
        pDynLib->pProcess32First = (PROCESSWALK)myGetProcAddress(pDynLib->ghDll_Kernel32,  "Process32FirstW"); 
        pDynLib->pProcess32Next  = (PROCESSWALK)myGetProcAddress(pDynLib->ghDll_Kernel32,  "Process32NextW"); 
		
        pDynLib->pThread32First  = (THREADWALK)myGetProcAddress(pDynLib->ghDll_Kernel32,  "Thread32First"); 
        pDynLib->pThread32Next   = (THREADWALK)myGetProcAddress(pDynLib->ghDll_Kernel32,  "Thread32Next"); 

	}
	if  (  g_bIsWinNT  )  {
		pDynLib->pProcessIdToSessionId  =  (  PF_ProcessIdToSessionId  )myGetProcAddress(  pDynLib->ghDll_Kernel32,  "ProcessIdToSessionId"  );
		if  (  iPlatformId  !=  CONST_qyPlatform_nt  &&  iPlatformId  !=  CONST_qyPlatform_win2k  )	{	//  2007/02/04, 仅xp以上支持
			pDynLib->pWTSGetActiveConsoleSessionId  =  (  PF_WTSGetActiveConsoleSessionId  )myGetProcAddress(  pDynLib->ghDll_Kernel32,  "WTSGetActiveConsoleSessionId"  );
		}
	}

	switch  (  iPlatformId  )  {
			case  CONST_qyPlatform_win98:
			case  CONST_qyPlatform_winme:
			case  CONST_qyPlatform_winnt:
			case  CONST_qyPlatform_win2k:
			case  CONST_qyPlatform_winxp:
			case  CONST_qyPlatform_win2003:
				  break;
			default:
					pDynLib->pInitializeSRWLock  =  (  PF_InitializeSRWLock  )myGetProcAddress(  pDynLib->ghDll_Kernel32,  "InitializeSRWLock"  );				//  2009/07/12
					pDynLib->pAcquireSRWLockShared  =  (  PF_AcquireSRWLockShared  )myGetProcAddress(  pDynLib->ghDll_Kernel32,  "AcquireSRWLockShared"  );
					pDynLib->pReleaseSRWLockShared  =  (  PF_ReleaseSRWLockShared  )myGetProcAddress(  pDynLib->ghDll_Kernel32,  "ReleaseSRWLockShared"  );
					pDynLib->pAcquireSRWLockExclusive  =  (  PF_AcquireSRWLockExclusive  )myGetProcAddress(  pDynLib->ghDll_Kernel32,  "AcquireSRWLockExclusive"  );
					pDynLib->pReleaseSRWLockExclusive  =  (  PF_ReleaseSRWLockExclusive	 )myGetProcAddress(  pDynLib->ghDll_Kernel32,  "ReleaseSRWLockExclusive"  );
				 break;
	}

	switch  (  iPlatformId  )  {
			case  CONST_qyPlatform_win98:
			case  CONST_qyPlatform_winme:
			case  CONST_qyPlatform_winnt:
			case  CONST_qyPlatform_win2k:
				  break;
			default:
				  pDynLib->pIsWow64Process  =  (  PF_IsWow64Process  )myGetProcAddress(  pDynLib->ghDll_Kernel32,  "IsWow64Process"  );
				  break;
	}


	//  if  (  qyFullLibName(  "shell32.dll",  svLibName,  sizeof(  svLibName  )  )  )  goto  errLabel;
	if  (  tQyStrCat(  systemDir,  _T(  "shell32.dll"  ),  svLibName,  mycountof(  svLibName  )  )  )  goto  errLabel;
	if  (  !(  pDynLib->ghDll_Shell32  =  LoadLibrary(  svLibName  )  )  )  goto  errLabel;
	if  (  g_bIsWinNT  )  {
		if  (  iPlatformId  !=  CONST_qyPlatform_nt  )  {
			pDynLib->pSHGetFolderPathW  =  (  PF_SHGetFolderPathW  )myGetProcAddress(  pDynLib->ghDll_Shell32,  "SHGetFolderPathW"  );
		}
	}

	if  (  tQyStrCat(  systemDir,  _T(  "ADVAPI32.DLL"  ),  svLibName,  mycountof(  svLibName  )  )  )  goto  errLabel;
	//  pDynLib->ghDll_AdvApi32  =  LoadLibrary("ADVAPI32.DLL");
	pDynLib->ghDll_AdvApi32  =  LoadLibrary(  svLibName  );
	if  (  pDynLib->ghDll_AdvApi32  ==  NULL  )  goto  errLabel;
    if  (  g_bIsWinNT  )  {
		pDynLib->pRegSetKeySecurity = (REGSETKEYSECURITY)myGetProcAddress(pDynLib->ghDll_AdvApi32,  "RegSetKeySecurity");
		pDynLib->pSetSecurityDescriptorDacl = (SETSECURITYDESCRIPTORDACL)myGetProcAddress(pDynLib->ghDll_AdvApi32,  "SetSecurityDescriptorDacl");
		pDynLib->pGetAce = (GETACE)myGetProcAddress(pDynLib->ghDll_AdvApi32,  "GetAce");
		pDynLib->pAddAccessAllowedAce = (ADDACCESSALLOWEDACE)myGetProcAddress(pDynLib->ghDll_AdvApi32,  "AddAccessAllowedAce");
		pDynLib->pInitializeAcl = (INITIALIZEACL)myGetProcAddress(pDynLib->ghDll_AdvApi32,  "InitializeAcl");
		pDynLib->pInitializeSecurityDescriptor = (INITIALIZESECURITYDESCRIPTOR)myGetProcAddress(pDynLib->ghDll_AdvApi32,  "InitializeSecurityDescriptor");
		pDynLib->pGetLengthSid = (GETLENGTHSID)myGetProcAddress(pDynLib->ghDll_AdvApi32,  "GetLengthSid");
		pDynLib->pLookupAccountName = (LOOKUPACCOUNTNAME)myGetProcAddress(pDynLib->ghDll_AdvApi32,  "LookupAccountNameA");
		//  pDynLib->pLookupAccountSid = (LOOKUPACCOUNTSID)myGetProcAddress(pDynLib->ghDll_AdvApi32,  "LookupAccountSidA");
		pDynLib->pLookupAccountSid = (LOOKUPACCOUNTSID)myGetProcAddress(pDynLib->ghDll_AdvApi32,  "LookupAccountSidW");
		pDynLib->pLookupAccountSidW  =  (  PF_LookupAccountSidW  )myGetProcAddress(  pDynLib->ghDll_AdvApi32,  "LookupAccountSidW"  );	//  2007/01/18
		pDynLib->pGetSecurityDescriptorDacl = (GETSECURITYDESCRIPTORDACL)myGetProcAddress(pDynLib->ghDll_AdvApi32,  "GetSecurityDescriptorDacl");
		pDynLib->pGetSecurityDescriptorGroup = (GETSECURITYDESCRIPTORGROUP)myGetProcAddress(pDynLib->ghDll_AdvApi32,  "GetSecurityDescriptorGroup");
		pDynLib->pGetSecurityDescriptorOwner = (GETSECURITYDESCRIPTOROWNER)myGetProcAddress(pDynLib->ghDll_AdvApi32,  "GetSecurityDescriptorOwner");
		pDynLib->pOpenProcessToken = (OPENPROCESSTOKEN)myGetProcAddress(pDynLib->ghDll_AdvApi32,  "OpenProcessToken");
		pDynLib->pGetTokenInformation  =  (GETTOKENINFORMATION)myGetProcAddress(pDynLib->ghDll_AdvApi32,  "GetTokenInformation"  );	//  20030326加
		//  pDynLib->pLookupPrivilegeValue = (LOOKUPPRIVILEGEVALUE)myGetProcAddress(pDynLib->ghDll_AdvApi32,  "LookupPrivilegeValueA");
		pDynLib->pLookupPrivilegeValue = (LOOKUPPRIVILEGEVALUE)myGetProcAddress(pDynLib->ghDll_AdvApi32,  "LookupPrivilegeValueW");
		pDynLib->pAdjustTokenPrivileges = (ADJUSTTOKENPRIVILEGES)myGetProcAddress(pDynLib->ghDll_AdvApi32,  "AdjustTokenPrivileges");
		pDynLib->pRegGetKeySecurity = (REGGETKEYSECURITY)myGetProcAddress(pDynLib->ghDll_AdvApi32,  "RegGetKeySecurity");
		pDynLib->pAllocateAndInitializeSid = ( ALLOCATEANDINITIALIZESID )myGetProcAddress( pDynLib->ghDll_AdvApi32,  "AllocateAndInitializeSid" );
		pDynLib->pFreeSid = ( FREESID )myGetProcAddress(  pDynLib->ghDll_AdvApi32,  "FreeSid"  );
		pDynLib->pIsValidSid  =  (  ISVALIDSID  )myGetProcAddress(  pDynLib->ghDll_AdvApi32,  "IsValidSid"  );
		pDynLib->pGetSidIdentifierAuthority  =  (  GETSIDIDENTIFIERAUTHORITY  )myGetProcAddress(  pDynLib->ghDll_AdvApi32,  "GetSidIdentifierAuthority"  );
		pDynLib->pGetSidSubAuthorityCount  =  (  GETSIDSUBAUTHORITYCOUNT  )myGetProcAddress(  pDynLib->ghDll_AdvApi32,  "GetSidSubAuthorityCount"  );
		pDynLib->pGetSidSubAuthority  =  (  GETSIDSUBAUTHORITY  )myGetProcAddress(  pDynLib->ghDll_AdvApi32,  "GetSidSubAuthority"  );	 
		pDynLib->pCreateProcessAsUserW  =  (  PF_CreateProcessAsUserW  )myGetProcAddress(  pDynLib->ghDll_AdvApi32,  "CreateProcessAsUserW"  );	//  2007/02/28
		pDynLib->pDuplicateTokenEx  =  (  PF_DuplicateTokenEx  )myGetProcAddress(  pDynLib->ghDll_AdvApi32,  "DuplicateTokenEx"  );
		

		pDynLib->pOpenSCManager=(OPENSCMANAGER) myGetProcAddress(pDynLib->ghDll_AdvApi32,  "OpenSCManagerW");
		//  pDynLib->pCreateService=(CREATESERVICE) myGetProcAddress(pDynLib->ghDll_AdvApi32,  "CreateServiceA");
		pDynLib->pCreateService=(CREATESERVICE) myGetProcAddress(pDynLib->ghDll_AdvApi32,  "CreateServiceW");
		pDynLib->pCloseServiceHandle=(CLOSESERVICEHANDLE) myGetProcAddress(pDynLib->ghDll_AdvApi32,  "CloseServiceHandle");
		//  pDynLib->pOpenService=(OPENSERVICE) myGetProcAddress(pDynLib->ghDll_AdvApi32,  "OpenServiceA");
		pDynLib->pOpenService=(OPENSERVICE) myGetProcAddress(pDynLib->ghDll_AdvApi32,  "OpenServiceW");
		//  pDynLib->pStartServiceCtrlDispatcher=(STARTSERVICECTRLDISPATCHER) myGetProcAddress(pDynLib->ghDll_AdvApi32,  "StartServiceCtrlDispatcherA");
		pDynLib->pStartServiceCtrlDispatcher=(STARTSERVICECTRLDISPATCHER) myGetProcAddress(pDynLib->ghDll_AdvApi32,  "StartServiceCtrlDispatcherW");

		pDynLib->pRegisterServiceCtrlHandler=(REGISTERSERVICECTRLHANDLER) myGetProcAddress(pDynLib->ghDll_AdvApi32,  "RegisterServiceCtrlHandlerW");
		pDynLib->pSetServiceStatus=(SETSERVICESTATUS) myGetProcAddress(pDynLib->ghDll_AdvApi32,  "SetServiceStatus");
		pDynLib->pDeleteService=(DELETESERVICE) myGetProcAddress(pDynLib->ghDll_AdvApi32,  "DeleteService");
		pDynLib->pGetServiceDisplayName=(GETSERVICEDISPLAYNAME) myGetProcAddress(pDynLib->ghDll_AdvApi32,  "GetServiceDisplayNameW");
		pDynLib->pStartService=(STARTSERVICE) myGetProcAddress(pDynLib->ghDll_AdvApi32,  "StartServiceW");
	
	
		//  2005/08/30, 加入处理系统日志的支持
		pDynLib->pOpenEventLog  =  (  PF_OpenEventLog  )myGetProcAddress(  pDynLib->ghDll_AdvApi32,  "OpenEventLogW"  );
		pDynLib->pCloseEventLog  =  (  PF_CloseEventLog  )myGetProcAddress(  pDynLib->ghDll_AdvApi32,  "CloseEventLog"  );
		pDynLib->pReadEventLog  =  (  PF_ReadEventLog  )myGetProcAddress(  pDynLib->ghDll_AdvApi32,  "ReadEventLogW"  );

		//  2006/04/23, 加入对注册表UNICODE的支持
#if  0
		pDynLib->pRegOpenKeyW  =  (  PF_RegOpenKeyW  )myGetProcAddress(  pDynLib->ghDll_AdvApi32,  "RegOpenKeyW"  );
		pDynLib->pRegOpenKeyExW  =  (  PF_RegOpenKeyExW  )myGetProcAddress(  pDynLib->ghDll_AdvApi32,  "RegOpenKeyExW"  );
		pDynLib->pRegEnumKeyW  =  (  PF_RegEnumKeyW  )myGetProcAddress(  pDynLib->ghDll_AdvApi32,  "RegEnumKeyW"  );
		pDynLib->pRegEnumKeyExW  =  (  PF_RegEnumKeyExW  )myGetProcAddress(  pDynLib->ghDll_AdvApi32,  "RegEnumKeyExW"  );		//  2006/07/18
		pDynLib->pRegEnumValueW  =  (  PF_RegEnumValueW  )myGetProcAddress(  pDynLib->ghDll_AdvApi32,  "RegEnumValueW"  );		//  2006/07/23
		pDynLib->pRegQueryValueExW  =  (  PF_RegQueryValueExW  )myGetProcAddress(  pDynLib->ghDll_AdvApi32,  "RegQueryValueExW"  );
#endif

	}
	
	//  2004/05/20，由于98在登录脚本运行时未能装载rasapi32.dll, 故不再在这里装载
	if  (  g_bIsWinNT  )  {
		char  buf[256];

		if  (  !qyGetRegCfg(  _T(  "System\\CurrentControlSet\\Services\\RasMan"  ),  _T(  "ObjectName"  ),  buf,  sizeof(  buf  )  )  )  {
			bRasManExists  =  TRUE;
		}
	}
	
	if  (  !g_bIsWinNT  ||  bRasManExists  )  {
		if  (  tQyStrCat(  systemDir,   _T(  "rasapi32.dll"  ),  svLibName,  mycountof(  svLibName  )  )  )  goto  errLabel;
		pDynLib->ghDll_RasApi32  =  LoadLibrary(  svLibName  );
		if  (  pDynLib->ghDll_RasApi32  )  {
			pDynLib->pRasEnumConnections = ( RASENUMCONNECTIONS )myGetProcAddress( pDynLib->ghDll_RasApi32, "RasEnumConnectionsW" );
			pDynLib->pRasHangUp = ( RASHANGUP )myGetProcAddress( pDynLib->ghDll_RasApi32, "RasHangUpW" );
			//  pDynLib->pRasGetErrorString = ( RASGETERRORSTRING )myGetProcAddress( pDynLib->ghDll_RasApi32, "RasGetErrorStringW" );
			pDynLib->pRasGetErrorString = ( RASGETERRORSTRING )myGetProcAddress( pDynLib->ghDll_RasApi32, "RasGetErrorStringW" );
			pDynLib->pRasGetConnectStatus = ( RASGETCONNECTSTATUS )myGetProcAddress( pDynLib->ghDll_RasApi32, "RasGetConnectStatusW" );
			pDynLib->pRasGetEntryProperties = ( RASGETENTRYPROPERTIES )myGetProcAddress( pDynLib->ghDll_RasApi32, "RasGetEntryPropertiesW" );
			// pDynLib->pRasGetEntryDialParams = ( RASGETENTRYDIALPARAMS )myGetProcAddress( pDynLib->ghDll_RasApi32, "RasGetEntryDialParamsW" );
			//  pDynLib->pRasEnumEntries  =  (  RASENUMENTRIES  )myGetProcAddress(  pDynLib->ghDll_RasApi32,  "RasEnumEntriesW"  );
			char  buf[256];			//  2005/04/23, Macfee瞎报错误，做以下修改
			_snprintf(  buf,  sizeof(  buf  ),  "Ras"  );
			_snprintf(  buf,  sizeof(  buf  ),  "%s%s",  buf,  "EnumEntriesW"  );
			#ifndef  __WINCE__
					 pDynLib->pRasEnumEntries  =  (  RASENUMENTRIES  )GetProcAddress(  pDynLib->ghDll_RasApi32,  buf  );
			#else
				TCHAR	tBuf[256];
				myStr2TChar(  buf,  tBuf,  mycountof(  tBuf  )  );
				pDynLib->pRasEnumEntries  =  (  RASENUMENTRIES  )GetProcAddress(  pDynLib->ghDll_RasApi32,  tBuf  );
			#endif
		}
	}
	traceLogA(  (char*)"InitDynamicLibraries( ): %s",  pDynLib->ghDll_RasApi32  ?  "rasapi32 loaded successfully."  :  "rasapi32 not loaded."  );
	
#endif
	
	//  2004/05/20增加了对98的排除，因为98的登录脚本运行环境的限制
#ifndef  __WINCE__
	int				i;
	for  (  i  =  0;  i  <  5;  i  ++  )  {
		 if  (  !qyInitSnmp( &pDynLib->ghDll_InetMib1 )  )  break;
		 Sleep(  3000  );
	}
	traceLogA(  (char*)"InitDynamicLibraries( ):  %s %s",  "InetMib1",  pDynLib->ghDll_InetMib1  ?  " loaded successfully."  :  " not loaded."  );
#endif

	//  2004/05/21添加
#if  0
	if  (  tQyStrCat(  systemDir,   _T(  "wsock32.dll"  ),  svLibName,  mycountof(  svLibName  )  )  )  goto  errLabel;
	pDynLib->ghDll_WSock32  =  LoadLibrary(  svLibName  );
	if  (  pDynLib->ghDll_WSock32  )  {
		pDynLib->pWSAStartup			=	(  PF_WSAStartup  )myGetProcAddress(  pDynLib->ghDll_WSock32,  "WSAStartup"  );
		pDynLib->pWSACleanup			=	(  PF_WSACleanup  )myGetProcAddress(  pDynLib->ghDll_WSock32,  "WSACleanup"  );					
		pDynLib->pinet_addr			=	(  PF_inet_addr  )myGetProcAddress(  pDynLib->ghDll_WSock32,  "inet_addr"  );
		pDynLib->pinet_ntoa			=	(  PF_inet_ntoa  )myGetProcAddress(  pDynLib->ghDll_WSock32,  "inet_ntoa"  );
		pDynLib->psocket				=	(  PF_socket  )myGetProcAddress(  pDynLib->ghDll_WSock32,  "socket"  );
		pDynLib->pbind				=	(  PF_bind  )myGetProcAddress(  pDynLib->ghDll_WSock32,  "bind"  );	;
		pDynLib->plisten				=	(  PF_listen  )myGetProcAddress(  pDynLib->ghDll_WSock32,  "listen"  );;
		pDynLib->paccept				=	(  PF_accept  )myGetProcAddress(  pDynLib->ghDll_WSock32,  "accept"  );;
		pDynLib->pconnect			=	(  PF_connect  )myGetProcAddress(  pDynLib->ghDll_WSock32,  "connect"  );;
		pDynLib->pselect				=	(  PF_select  )myGetProcAddress(  pDynLib->ghDll_WSock32,  "select"  );;
		pDynLib->pgetsockname		=	(  PF_getsockname  )myGetProcAddress(  pDynLib->ghDll_WSock32,  "getsockname"  );
		pDynLib->pgetpeername		=	(  PF_getpeername  )myGetProcAddress(  pDynLib->ghDll_WSock32,  "getpeername"  );
		pDynLib->pclosesocket		=	(  PF_closesocket  )myGetProcAddress(  pDynLib->ghDll_WSock32,  "closesocket"  );
		pDynLib->precv				=	(  PF_recv  )myGetProcAddress(  pDynLib->ghDll_WSock32,  "recv"  );
		pDynLib->psend				=	(  PF_send  )myGetProcAddress(  pDynLib->ghDll_WSock32,  "send"  );
		pDynLib->pWSAGetLastError	=	(  PF_WSAGetLastError  )myGetProcAddress(  pDynLib->ghDll_WSock32,  "WSAGetLastError"  );
		pDynLib->pioctlsocket		=	(  PF_ioctlsocket  )myGetProcAddress(  pDynLib->ghDll_WSock32,  "ioctlsocket"  );
		pDynLib->pgethostname		=	(  PF_gethostname  )myGetProcAddress(  pDynLib->ghDll_WSock32,  "gethostname"  );
		pDynLib->pgethostbyname		=	(  PF_gethostbyname  )myGetProcAddress(  pDynLib->ghDll_WSock32,  "gethostbyname"  );
		pDynLib->phtons				=	(  PF_htons  )myGetProcAddress(  pDynLib->ghDll_WSock32,  "htons"  );
		pDynLib->psetsockopt			=	(  PF_setsockopt  )myGetProcAddress(  pDynLib->ghDll_WSock32,  "setsockopt"  );
	}
	traceLogA(  "InitDynamicLibraries( ):  %s %s",  "wsock32",  pDynLib->ghDll_WSock32  ?  " loaded successfully."  :  " not loaded."  );
#endif


	if  (  tQyStrCat(  systemDir,   _T(  "setupApi.dll"  ),  svLibName,  mycountof(  svLibName  )  )  )  goto  errLabel;
	pDynLib->ghDll_SetupApi  =  LoadLibrary(  svLibName  );
	if  (  pDynLib->ghDll_SetupApi  )  {
		pDynLib->pSetupDiGetClassDevs				=	(  PF_SetupDiGetClassDevs  )myGetProcAddress(  pDynLib->ghDll_SetupApi,  "SetupDiGetClassDevsA"  );
		pDynLib->pSetupDiEnumDeviceInfo				=	(  PF_SetupDiEnumDeviceInfo  )myGetProcAddress(  pDynLib->ghDll_SetupApi,  "SetupDiEnumDeviceInfo"  );			
		pDynLib->pSetupDiDestroyDeviceInfoList		=	(  PF_SetupDiDestroyDeviceInfoList  )myGetProcAddress(  pDynLib->ghDll_SetupApi,  "SetupDiDestroyDeviceInfoList"  );
		pDynLib->pSetupDiEnumDeviceInterfaces		=	(  PF_SetupDiEnumDeviceInterfaces  )myGetProcAddress(  pDynLib->ghDll_SetupApi,  "SetupDiEnumDeviceInterfaces"  );
		//  pDynLib->pSetupDiGetDeviceInterfaceDetail	=	(  PF_SetupDiGetDeviceInterfaceDetail  )myGetProcAddress(  pDynLib->ghDll_SetupApi,  "SetupDiGetDeviceInterfaceDetailA"  );
		pDynLib->pSetupDiGetDeviceInterfaceDetail	=	(  PF_SetupDiGetDeviceInterfaceDetail  )myGetProcAddress(  pDynLib->ghDll_SetupApi,  "SetupDiGetDeviceInterfaceDetailW"  );
		pDynLib->pSetupDiGetDeviceRegistryProperty	=	(  PF_SetupDiGetDeviceRegistryProperty  )myGetProcAddress(  pDynLib->ghDll_SetupApi,  "SetupDiGetDeviceRegistryPropertyW"  );
		pDynLib->pSetupDiSetClassInstallParams		=	(  PF_SetupDiSetClassInstallParams  )myGetProcAddress(  pDynLib->ghDll_SetupApi,  "SetupDiSetClassInstallParamsA"  );
		pDynLib->pSetupDiCallClassInstaller			=	(  PF_SetupDiCallClassInstaller  )myGetProcAddress(  pDynLib->ghDll_SetupApi,  "SetupDiCallClassInstaller"  );
		pDynLib->pSetupDiGetDeviceInstallParams		=	(  PF_SetupDiGetDeviceInstallParams	 )myGetProcAddress(  pDynLib->ghDll_SetupApi,  "SetupDiGetDeviceInstallParamsW"  );

	}
	traceLogA(  (char*)"InitDynamicLibraries( ):  %s %s",  "setupapi",  pDynLib->ghDll_SetupApi  ?  " loaded successfully."  :  " not loaded."  );

	if  (  tQyStrCat(  systemDir,   _T(  "cfgMgr32.dll"  ),  svLibName,  mycountof(  svLibName  )  )  )  goto  errLabel;
	pDynLib->ghDll_CfgMgr32  =  LoadLibrary(  svLibName  );
	if  (  pDynLib->ghDll_CfgMgr32  )  {
		pDynLib->pCM_Get_Device_ID					=	(  PF_CM_Get_Device_ID  )myGetProcAddress(  pDynLib->ghDll_CfgMgr32,  "CM_Get_Device_IDW"  );
		pDynLib->pCM_Get_DevNode_Status				=	(  PF_CM_Get_DevNode_Status  )myGetProcAddress(  pDynLib->ghDll_CfgMgr32,  "CM_Get_DevNode_Status"  );
	}
	traceLogA(  (char*)"InitDynamicLibraries( ):  %s %s",  "cfgMgr32",  pDynLib->ghDll_CfgMgr32  ?  " loaded successfully."  :  " not loaded."  );


	if  (  tQyStrCat(  systemDir,   _T(  "ipHlpApi.dll"  ),  svLibName,  mycountof(  svLibName  )  )  )  goto  errLabel;
	pDynLib->ghDll_IpHlpApi  =  LoadLibrary(  svLibName  );
	if  (  pDynLib->ghDll_IpHlpApi  )  {
		pDynLib->pGetAdaptersInfo  =  (  PF_GetAdaptersInfo  )myGetProcAddress(  pDynLib->ghDll_IpHlpApi,  "GetAdaptersInfo"  );
		//  GetPerAdapterInfo在2000以上支持
		pDynLib->pGetPerAdapterInfo  =  (  PF_GetPerAdapterInfo  )myGetProcAddress(  pDynLib->ghDll_IpHlpApi,  "GetPerAdapterInfo"  );
		//
		pDynLib->pGetTcpTable  =  (  PF_GetTcpTable  )myGetProcAddress(  pDynLib->ghDll_IpHlpApi,  "GetTcpTable"  );
		pDynLib->pGetUdpTable  =  (  PF_GetUdpTable  )myGetProcAddress(  pDynLib->ghDll_IpHlpApi,  "GetUdpTable"  );
		//
		pDynLib->pGetIfTable  =  (  PF_GetIfTable  )myGetProcAddress(  pDynLib->ghDll_IpHlpApi,  "GetIfTable"  );
		pDynLib->pSetIfEntry  =  (  PF_SetIfEntry  )myGetProcAddress(  pDynLib->ghDll_IpHlpApi,  "SetIfEntry"  );
		pDynLib->pGetIfEntry	 =  (  PF_GetIfEntry  )myGetProcAddress(  pDynLib->ghDll_IpHlpApi,  "GetIfEntry"  );
		//  2007/01/20
		pDynLib->pSendARP  =  (  PF_SendARP  )myGetProcAddress(  pDynLib->ghDll_IpHlpApi,  "SendARP"  );

	}
	traceLogA(  (char*)"InitDynamicLibraries( ):  %s %s",  "ipHlpApi",  pDynLib->ghDll_IpHlpApi  ?  " loaded successfully."  :  " not loaded."  );

	//  2005/06/26
	if  (  tQyStrCat(  systemDir,   _T(  "shlwApi.dll"  ),  svLibName,  mycountof(  svLibName  )  )  )  goto  errLabel;
	pDynLib->ghDll_ShlwApi  =  hDll  =  LoadLibrary(  svLibName  );
	if  (  hDll  )  {
		pDynLib->pSHDeleteKey  =  (  PF_SHDeleteKey  )myGetProcAddress(  hDll,  "SHDeleteKeyW"  );
	}
	traceLogA(  (char*)"InitDynamicLibraries( ):  %s %s",  "shlwApi",  hDll  ?  " loaded successfully."  :  " not loaded."  );

	//  2005/12/23
	if  (  tQyStrCat(  systemDir,   _T(  "Winmm.dll"  ),  svLibName,  mycountof(  svLibName  )  )  )  goto  errLabel;
	pDynLib->ghDll_Winmm  =  hDll  =  LoadLibrary(  svLibName  );
	if  (  hDll  )  {
		pDynLib->pmciSendCommand  =  (  PF_mciSendCommand  )myGetProcAddress(  hDll,  "mciSendCommandA"  );
	}
	traceLogA(  (char*)"InitDynamicLibraries( ):  %s %s",  "Winmm",  hDll  ?  " loaded successfully."  :  " not loaded."  );


	//  2005/12/25
	if  (  tQyStrCat(  systemDir,   _T(  "Rpcrt4.dll"  ),  svLibName,  mycountof(  svLibName  )  )  )  goto  errLabel;
	pDynLib->ghDll_Rpcrt4  =  hDll  =  LoadLibrary(  svLibName  );
	if  (  hDll  )  {
		pDynLib->pUuidFromString  =  (  PF_UuidFromString  )myGetProcAddress(  hDll,  "UuidFromStringA"  );
	}
	traceLogA(  (char*)"InitDynamicLibraries( ):  %s %s",  "Rpcrt4",  hDll  ?  " loaded successfully."  :  " not loaded."  );
	
	
	//  2005/07/03
	if  (  g_bIsWinNT  )  {
		if  (  tQyStrCat(  systemDir,   _T(  "ntDll.dll"  ),  svLibName,  mycountof(  svLibName  )  )  )  goto  errLabel;
		pDynLib->ghDll_NtDll  =  hDll  =  LoadLibrary(  svLibName  );
		if  (  hDll  )  {
			pDynLib->pNtQueryInformationProcess  =  (  PF_NtQueryInformationProcess  )myGetProcAddress(  hDll,  "NtQueryInformationProcess"  );
			pDynLib->pNtQuerySystemInformation  =  (  PF_NtQuerySystemInformation  )myGetProcAddress(  hDll,  "NtQuerySystemInformation"  );
		}
	}
	traceLogA(  (char*)"InitDynamicLibraries( ):  %s %s",  "ntDll",  hDll  ?  " loaded successfully."  :  " not loaded."  );

	//  2006/04/13
	if  (  g_bIsWinNT  )  {
		if  (  tQyStrCat(  systemDir,   _T(  "psApi.dll"  ),  svLibName,  mycountof(  svLibName  )  )  )  goto  errLabel;
		pDynLib->ghDll_PsApi  =  hDll  =  LoadLibrary(  svLibName  );
		if  (  hDll  )  {
			pDynLib->pEnumProcessModules  =  (  PF_EnumProcessModules  )myGetProcAddress(  hDll,  "EnumProcessModules"  );
			pDynLib->pGetModuleFileNameExW  =  (  PF_GetModuleFileNameExW  )myGetProcAddress(  hDll,  "GetModuleFileNameExW"  );
			pDynLib->pEnumProcesses  =  (  PF_EnumProcesses  )myGetProcAddress(  hDll,  "EnumProcesses"  );
		}
	}
	traceLogA(  (char*)"InitDynamicLibraries( ):  %s %s",  "psApi",  hDll  ?  " loaded successfully."  :  " not loaded."  );

	if  (  g_bIsWinNT  )  {
		if  (  tQyStrCat(  systemDir,   _T(  "WtsApi32.dll"  ),  svLibName,  mycountof(  svLibName  )  )  )  goto  errLabel;
		pDynLib->ghDll_WtsApi32  =  hDll  =  LoadLibrary(  svLibName  );
		if  (  hDll  )  {
			//  pDynLib->pWTSSendMessageA  =  (  PF_WTSSendMessageA  )myGetProcAddress(  hDll,  "WTSSendMessageA"  );
			pDynLib->pWTSSendMessageW  =  (  PF_WTSSendMessageW  )myGetProcAddress(  hDll,  "WTSSendMessageW"  );
			if  (  iPlatformId  !=  CONST_qyPlatform_winnt  &&  iPlatformId  !=  CONST_qyPlatform_win2k  )  {
				pDynLib->pWTSRegisterSessionNotification  =  (  PF_WTSRegisterSessionNotification  )myGetProcAddress(  hDll,  "WTSRegisterSessionNotification"  );			//  2007/02/27
				pDynLib->pWTSUnRegisterSessionNotification  =  (  PF_WTSUnRegisterSessionNotification  )myGetProcAddress(  hDll,  "WTSUnRegisterSessionNotification"  );			//  2007/02/27
			}
		}
	}
	traceLogA(  (char*)"InitDynamicLibraries( ):  %s %s",  "WtsApi32",  hDll  ?  " loaded successfully."  :  " not loaded."  );

	if  (  g_bIsWinNT  )  {
		if  (  tQyStrCat(  systemDir,   _T(  "UserEnv.dll"  ),  svLibName,  mycountof(  svLibName  )  )  )  goto  errLabel;
		pDynLib->ghDll_UserEnv  =  hDll  =  LoadLibrary(  svLibName  );
		if  (  hDll  )  {
			pDynLib->pCreateEnvironmentBlock  =  (  PF_CreateEnvironmentBlock  )myGetProcAddress(  hDll,  "CreateEnvironmentBlock"  );
			pDynLib->pDestroyEnvironmentBlock  =  (  PF_DestroyEnvironmentBlock  )myGetProcAddress(  hDll,  "DestroyEnvironmentBlock"  );
		}
	}
	traceLogA(  (char*)"InitDynamicLibraries( ):  %s %s",  "WtsApi32",  hDll  ?  " loaded successfully."  :  " not loaded."  );

	//  2011/10/04
	if  (  g_bIsWinNT  )  {
		if  (  tQyStrCat(  systemDir,   _T(  "User32.dll"  ),  svLibName,  mycountof(  svLibName  )  )  )  goto  errLabel;
		pDynLib->ghDll_User32  =  hDll  =  LoadLibrary(  svLibName  );
		if  (  hDll  )  {
			pDynLib->pMessageBoxTimeoutW  =  (  PF_MessageBoxTimeoutW  )myGetProcAddress(  hDll,  "MessageBoxTimeoutW"  );
		}
	}
	traceLogA(  (char*)"InitDynamicLibraries( ):  %s %s",  "User32",  hDll  ?  " loaded successfully."  :  " not loaded."  );



	iErr = 0;

errLabel:

	if  (  iErr  )  {
		if  (  pDynLib  )  exitDynLib(  (  void  **  )&pDynLib  );
	}
	if  (  !iErr  )  *pp  =  pDynLib;

	return  iErr;

}


 extern  "C"  int  exitDynLib(  void  **  pp  )
{
	// below is added by asr.

	if  (  !pp  )  return  -1;
	if  (  !*pp  )  {  
		traceLogA(  (char*)"exitDynLib(  )  failed. *pp is null"  );  return  -1;
	}

	QWM_DYN_LIB	*	pDynLib	=	(  QWM_DYN_LIB  *  )*pp;

	if  (  pDynLib->ghDll_User32  )  {		//  2011/10/04
		FreeLibrary(  pDynLib->ghDll_User32  );  pDynLib->ghDll_User32  =  NULL;
	}

	if  (  pDynLib->ghDll_UserEnv  )  {		//  2007/02/28
		FreeLibrary(  pDynLib->ghDll_UserEnv  );  pDynLib->ghDll_UserEnv  =  NULL;
	}
	if  (  pDynLib->ghDll_WtsApi32  )  {	//  2007/02/10
		FreeLibrary(  pDynLib->ghDll_WtsApi32  );  pDynLib->ghDll_WtsApi32  =  NULL;
	}

	if  (  pDynLib->ghDll_PsApi  )  {		//  2006/04/13
		FreeLibrary(  pDynLib->ghDll_PsApi  );  pDynLib->ghDll_PsApi  =  NULL;
	}

	if  (  pDynLib->ghDll_NtDll  )  {		//  2005/07/03
		FreeLibrary(  pDynLib->ghDll_NtDll  );  pDynLib->ghDll_NtDll  =  NULL;
	}

	if  (  pDynLib->ghDll_ShlwApi  )  {		//  2005/06/26
		FreeLibrary(  pDynLib->ghDll_ShlwApi  );  pDynLib->ghDll_ShlwApi  =  NULL;
	}

	if  (  pDynLib->ghDll_IpHlpApi  )  {		//  2005/05/23
		FreeLibrary(  pDynLib->ghDll_IpHlpApi  );  pDynLib->ghDll_IpHlpApi  =  NULL;
	}

	if  (  pDynLib->ghDll_CfgMgr32  )  {
		FreeLibrary(  pDynLib->ghDll_CfgMgr32  );  pDynLib->ghDll_CfgMgr32  =  NULL;
	}

	if  (  pDynLib->ghDll_SetupApi  )  {
		FreeLibrary(  pDynLib->ghDll_SetupApi  );  pDynLib->ghDll_SetupApi  =  NULL;
	}

#if  0
	if  (  pDynLib->ghDll_WSock32  )  {
		FreeLibrary(  pDynLib->ghDll_WSock32  );  pDynLib->ghDll_WSock32  =  NULL;
	}
#endif

#ifndef  __WINCE__
	if  (  pDynLib->ghDll_InetMib1  )  {
		qyExitSnmp( &pDynLib->ghDll_InetMib1 );
	}
#endif

	if ( pDynLib->ghDll_RasApi32 ) {	
		FreeLibrary( pDynLib->ghDll_RasApi32 ); pDynLib->ghDll_RasApi32 = NULL;
	}
	
	if  (  pDynLib->ghDll_AdvApi32  )  {
		FreeLibrary(pDynLib->ghDll_AdvApi32); pDynLib->ghDll_AdvApi32 = NULL;
	}
	if  (  pDynLib->ghDll_Shell32  )  {
		FreeLibrary(  pDynLib->ghDll_Shell32  );  pDynLib->ghDll_Shell32  =  NULL;
	}
	if  (  pDynLib->ghDll_Kernel32  ) {
		FreeLibrary(pDynLib->ghDll_Kernel32); pDynLib->ghDll_Kernel32 = NULL;
	}
	if  (  pDynLib->ghDll_Mpr  )  {
		FreeLibrary(pDynLib->ghDll_Mpr); pDynLib->ghDll_Mpr = NULL;
	}
	if  (  pDynLib->ghDll_NetApi32  )  {
		FreeLibrary(pDynLib->ghDll_NetApi32); pDynLib->ghDll_NetApi32 = NULL;
	}
	if  (  pDynLib->ghDll_SvrApi  )  {
		FreeLibrary(pDynLib->ghDll_SvrApi); pDynLib->ghDll_SvrApi = NULL;
	}

	free(  *pp  );  *pp  =  0;

	return  0;
}

 BOOL  bSetupApiOk(  QWM_DYN_LIB  *  pDynLibParam  )
{
	 QWM_DYN_LIB  *  pDynLib  =  (  QWM_DYN_LIB  *  )pDynLibParam;
	 
	 if  (  !pDynLib  )  return  FALSE;

	 if  (  pDynLib->ghDll_SetupApi  &&  pDynLib->ghDll_CfgMgr32
		 &&  pDynLib->pSetupDiGetClassDevs
			&&  pDynLib->pSetupDiEnumDeviceInfo
				&&  pDynLib->pSetupDiDestroyDeviceInfoList
					&&  pDynLib->pSetupDiEnumDeviceInterfaces
						&&  pDynLib->pSetupDiGetDeviceInterfaceDetail
							&&  pDynLib->pSetupDiGetDeviceRegistryProperty
								&&  pDynLib->pSetupDiSetClassInstallParams
									&&  pDynLib->pSetupDiCallClassInstaller
										&&  pDynLib->pSetupDiGetDeviceInstallParams
											&&  pDynLib->pCM_Get_Device_ID
											&&  pDynLib->pCM_Get_DevNode_Status  )
	 {
		 return  TRUE;
	 }

	 //
	 traceLog(  (TCHAR*)_T("seupApi library not ok"  ));  
	 //
	 return  FALSE;
}


 BOOL  bIpHlpApiOk(  QWM_DYN_LIB  *  pDynLibParam  )
{
	 QWM_DYN_LIB  *  pDynLib  =  (  QWM_DYN_LIB  *  )pDynLibParam;

	 if  (  !pDynLib  )  return  FALSE;

 	 if  (  pDynLib->ghDll_IpHlpApi  
		 &&  pDynLib->pGetAdaptersInfo  )  
	 {
		 return  TRUE;
	 }
		 
	 traceLogA(  (char*)"IpHelpApi.dll not ok"  );  

	 return  FALSE;
}

 BOOL  bShlwApiOk(  QWM_DYN_LIB  *  pDynLibParam  )
{
	 QWM_DYN_LIB  *  pDynLib  =  (  QWM_DYN_LIB  *  )pDynLibParam;

	 if  (  !pDynLib  )  return  FALSE;

	 if  (  pDynLib->ghDll_ShlwApi
		 &&  pDynLib->pSHDeleteKey  )
	 {
		 return  TRUE;
	 }

	 traceLogA(  (char*)"ShlwApi.dll not ok"  );
	 
	 return  FALSE;
}




#if  0
  extern  "C"  LONG  APIENTRY  myRegOpenKey(  QY_ENV  *  pEnv,  HKEY hKey,  LPCWSTR lpSubKey,  PHKEY phkResult  )
{
	 QWM_DYN_LIB  *  pDynLib  =  (  QWM_DYN_LIB  *  )pEnv->pDynLibs;

	 if  (  !pDynLib->pRegOpenKeyW  )  return  ERROR_ACCESS_DENIED;
	 return  pDynLib->pRegOpenKeyW(  hKey,  lpSubKey,  phkResult  );
}

 extern  "C"  LONG  APIENTRY  myRegOpenKeyEx(  QY_ENV  *  pEnv,  HKEY hKey,  LPCWSTR lpSubKey,  DWORD ulOptions,  REGSAM samDesired,  PHKEY phkResult  )
{
	 QWM_DYN_LIB  *  pDynLib  =  (  QWM_DYN_LIB  *  )pEnv->pDynLibs;

	 if  (  !pDynLib->pRegOpenKeyExW  )  return  ERROR_ACCESS_DENIED;
	 return  pDynLib->pRegOpenKeyExW(  hKey,  lpSubKey,  ulOptions,  samDesired,  phkResult  );
}

 extern  "C"  LONG  APIENTRY  myRegEnumKey(  QY_ENV  *  pEnv,  HKEY hKey,  DWORD dwIndex,  LPWSTR lpName,  DWORD cbName  )
{
	 QWM_DYN_LIB  *  pDynLib  =  (  QWM_DYN_LIB  *  )pEnv->pDynLibs;

	 if  (  !pDynLib->pRegEnumKeyW  )  return  ERROR_ACCESS_DENIED;
	 return  pDynLib->pRegEnumKeyW(  hKey,  dwIndex,  lpName,  cbName  );
}

 //  2006/07/18
 extern  "C"  LONG  APIENTRY  myRegEnumKeyEx(  QY_ENV  *  pEnv,  HKEY hKey,  DWORD dwIndex,  LPWSTR lpName,  LPDWORD lpcbName,  LPDWORD lpReserved,  LPWSTR lpClass,  LPDWORD lpcbClass,  PFILETIME lpftLastWriteTime  )
{
	 QWM_DYN_LIB  *  pDynLib  =  (  QWM_DYN_LIB  *  )pEnv->pDynLibs;

	 if  (  !pDynLib->pRegEnumKeyExW  )  return  ERROR_ACCESS_DENIED;
	 return  pDynLib->pRegEnumKeyExW(  hKey,  dwIndex,  lpName,  lpcbName,  lpReserved,  lpClass,  lpcbClass,  lpftLastWriteTime  );  
}


 extern  "C"  LONG  APIENTRY  myRegEnumValue(  QY_ENV  *  pEnv,  HKEY hKey,  DWORD dwIndex,  LPWSTR lpValueName,  LPDWORD lpcbValueName,  LPDWORD lpReserved,  LPDWORD lpType,  LPBYTE lpData,  LPDWORD lpcbData  )
{
	 QWM_DYN_LIB  *  pDynLib  =  (  QWM_DYN_LIB  *  )pEnv->pDynLibs;

	 if  (  !pDynLib->pRegEnumValueW  )  return  ERROR_ACCESS_DENIED;
	 return  pDynLib->pRegEnumValueW(  hKey,  dwIndex,  lpValueName,  lpcbValueName,  lpReserved,  lpType,  lpData,  lpcbData  );  
}

 extern  "C"  LONG  APIENTRY  myRegQueryValueEx(  QY_ENV  *  pEnv,  HKEY hKey,  LPCWSTR lpValueName,  LPDWORD lpReserved,  LPDWORD lpType,  LPBYTE lpData,  LPDWORD lpcbData  )
{
	 QWM_DYN_LIB  *  pDynLib  =  (  QWM_DYN_LIB  *  )pEnv->pDynLibs;

	 if  (  !pDynLib->pRegQueryValueExW  )  return  ERROR_ACCESS_DENIED;
	 return  pDynLib->pRegQueryValueExW(  hKey,  lpValueName,  lpReserved,  lpType,  lpData,  lpcbData  );
}
#endif

  // wxr写在2003/09/12
 extern  "C"  int  qyGetRegCfg1W(  QY_ENV  *  pEnv,  HKEY  hKeyRoot0,  LPCWSTR  rootKey,  LPCWSTR  cfgName,  WCHAR  *  cfgVal,  int  size,  unsigned  int  *  puiType  )
{
	int		iRet		=	-1;
	BOOL	bKeyOpen	=	FALSE;
	HKEY	hKey;
	int		lRet		=	0;
	long	cb;
	DWORD	type;
			
	if  (  !rootKey  || !rootKey[0]  )  return  -1;
	if  (  !hKeyRoot0  )  hKeyRoot0  =  HKEY_LOCAL_MACHINE;

	lRet  =  RegOpenKeyEx(  hKeyRoot0,  rootKey,  0,  KEY_QUERY_VALUE,  & hKey  );
	if  (  lRet  !=  ERROR_SUCCESS  )  {
		//  traceLogA(  "qyGetRegCfg(  ):  RegOpenKey( %s )  failed.",  rootKey  );
		goto  errLabel;
	}
	bKeyOpen  =  TRUE;
	
	cb  =  size  *  sizeof(  WCHAR  );		//  注意这里，应将字符的宽度给乘进去，因为需要的是字节的容量
	if  (  RegQueryValueEx(  hKey,  cfgName,  0,  & type,  (  unsigned  char  *  )cfgVal, 
			(  unsigned  long  *  ) & cb  )  !=  ERROR_SUCCESS  ) 
	{
		//  traceLogA(  "qyGetRegCfg(  ):  RegQueryValueEx( %s )  failed.",  cfgName  );
		goto errLabel;
	}
	//  2003/09/12加入了对类型的判断，仅对字符串作结尾
	if  (  type  ==  REG_SZ  ||  type  ==  REG_MULTI_SZ  ||  type  ==  REG_EXPAND_SZ   )  {
		if  (  cb  <  2  )  cfgVal[0]	=	0;
		else  cfgVal[cb  /  2  -  1] = 0;
	}
	
	iRet  =  0;
	
errLabel:

	if ( bKeyOpen ) RegCloseKey( hKey );

	if  (  !iRet  )  {
		if  (  puiType  )  *  puiType  =  type;		//  2004/08/06加
	}

	return iRet;

}

  // wxr写在2002/09/06
#if  0
 extern  "C"  int  qyGetRegCfgW(  QY_ENV  *  pEnv,  LPCWSTR  rootKey,  LPCWSTR  cfgName,  WCHAR  *  cfgVal,  int  size  )
{
	 return  qyGetRegCfg1W(  pEnv,  HKEY_LOCAL_MACHINE,  rootKey,  cfgName,  cfgVal,  size,  NULL  );
}
#endif


 //  2007/04/06
 extern  "C"  HRESULT WINAPI  mySHGetFolderPathW(  QY_ENV  *  pEnv,  HWND  hwnd,  int  csidl,  HANDLE  hToken,  DWORD  dwFlags,  LPWSTR  pszPath  )
{
	 QWM_DYN_LIB  *  pDynLib  =  (  QWM_DYN_LIB  *  )pEnv->pDynLibs;

	 if  (  !pDynLib->pSHGetFolderPathW  )  return  E_FAIL;
	 return  pDynLib->pSHGetFolderPathW(  hwnd,  csidl,  hToken,  dwFlags,  pszPath  );
}

 extern  "C"  BOOL  WINAPI  myGetSystemTimes(  QY_ENV  *  pEnv,  LPFILETIME lpIdleTime,  LPFILETIME lpKernelTime,  LPFILETIME lpUserTime  )
{
	 QWM_DYN_LIB  *  pDynLib  =  (  QWM_DYN_LIB  *  )pEnv->pDynLibs;

#ifdef  __WINCE__
		return  FALSE;
#else
	 if  (  !pDynLib->pGetSystemTimes  )  return  FALSE;
	 return  pDynLib->pGetSystemTimes(  lpIdleTime,  lpKernelTime,  lpUserTime  );
#endif
 }


 BOOL WINAPI myIsWow64Process(  QY_ENV  *  pEnv,  HANDLE hProcess,  PBOOL Wow64Process  )
 {
	 QWM_DYN_LIB  *  pDynLib  =  (  QWM_DYN_LIB  *  )pEnv->pDynLibs;

#ifdef  __WINCE__
		return  FALSE;
#else
	 if  (  !pDynLib->pIsWow64Process  )  return  FALSE;

	 return  pDynLib->pIsWow64Process(  hProcess,  Wow64Process  );
#endif
 }

 BOOL  WINAPI  myWTSSendMessage(  QY_ENV  *  pEnv,  IN HANDLE hServer,  IN DWORD SessionId,  __in_bcount(TitleLength) LPWSTR pTitle,  IN DWORD TitleLength,  __in_bcount(MessageLength) LPWSTR pMessage,  IN DWORD MessageLength,  IN DWORD Style,  IN DWORD Timeout,  __out DWORD * pResponse,  IN BOOL bWait  )
{
	QWM_DYN_LIB  *  pDynLib  =  (  QWM_DYN_LIB  *  )pEnv->pDynLibs;

#ifdef  __WINCE__
		return  FALSE;
#else

	if  (  !pDynLib->pWTSSendMessageW  )  return  FALSE;
	
	return  pDynLib->pWTSSendMessageW(  hServer,  SessionId,  pTitle,  TitleLength,  pMessage,  MessageLength,  Style,  Timeout,  pResponse,  bWait  );
#endif
}


 //  2011/10/04
 BOOL  bExists_MessageBoxTimeout(  QY_ENV  *  pEnv  )
{
	QWM_DYN_LIB  *  pDynLib  =  (  QWM_DYN_LIB  *  )pEnv->pDynLibs;

	if  (  !pDynLib->pMessageBoxTimeoutW  )  return FALSE;
	return  TRUE;
}

 int  WINAPI  myMessageBoxTimeout(  QY_ENV  *  pEnv,  __in_opt HWND hWnd,  __in_opt LPCWSTR lpText,  __in_opt LPCWSTR lpCaption,  __in UINT uType,  __in  WORD  wLanguageId,  __in  DWORD  dwMilliseconds  )
{
	QWM_DYN_LIB  *  pDynLib  =  (  QWM_DYN_LIB  *  )pEnv->pDynLibs;

	if  (  !pDynLib->pMessageBoxTimeoutW  )  return -1;
	return  pDynLib->pMessageBoxTimeoutW(  hWnd,  lpText,  lpCaption,  uType,  wLanguageId,  dwMilliseconds  );
}


 UINT  WINAPI  qwmGetSystemDirectory(  QY_ENV  *  pEnv,  LPTSTR lpBuffer,  UINT uSize  )
{
	UINT		uLen;
	TCHAR	*	pT;

	return  myGetSystemDirectory(  lpBuffer,  uSize  );

#if  0
	if  (  !pEnv->bWow64Process  )  {
		return  GetSystemDirectory(  lpBuffer,  uSize  );
	}

	uLen  =  GetSystemDirectory(  lpBuffer,  uSize  );
	if  (  uLen  >  uSize  )  return  uLen;
	tTrim(  lpBuffer  );
	if  (  lpBuffer[lstrlen(  lpBuffer  )  -  1]  ==  _T(  '\\'  )  )  lpBuffer[lstrlen(  lpBuffer  )  -  1]  =  0;
	pT  =  _tcsrchr(  lpBuffer,  _T(  '\\'  )  );
	if  (  !pT  )  return  0;
	pT  ++  ;  *pT  =  0;
	lstrcpyn(  lpBuffer  +  lstrlen(  lpBuffer  ),  _T(  "SysWow64"  ),  uSize  -  lstrlen(  lpBuffer  )  );
	return  lstrlen(  lpBuffer  );
#endif
}


 extern  "C"  int  getProcessUsrAndDomain(  void  *  pEnvParam,  DWORD  processId,  WCHAR  *  wAccountNameBuf,  unsigned  int  uiAccountNameBufSize,  WCHAR  *  wDomainNameBuf,  unsigned  int  uiDomainNameBufSize  )
{
	 int				iErr				=	-1;
	 HANDLE				hProcess			=	NULL;
	 HANDLE				hAccessToken		=	NULL;
	 WCHAR				wDomainName[200]	=	L"",  wAccountName[200]  =  L"";
	 DWORD				dwAccountSize		=	0,  dwDomainSize  =  0;
	 PTOKEN_USER		ptiUser				=	NULL;
   	 DWORD				cbti				=	0;
   	 SID_NAME_USE		snu;
	 BOOL				bTokenOpen			=	FALSE;
	 QY_ENV			*	pEnv				=	(  QY_ENV  *  )pEnvParam;
	 QWM_DYN_LIB	*	pDynLib				=	(  QWM_DYN_LIB  *  )pEnv->pDynLibs;	

	 if  (  !pDynLib  ||  !pDynLib->pOpenProcessToken  ||  !pDynLib->pGetTokenInformation  ||  !pDynLib->pLookupAccountSidW  )  goto  errLabel;

	 hProcess  =  OpenProcess(  PROCESS_QUERY_INFORMATION,  FALSE,  processId  );
	 if  (  !hProcess  )  goto  errLabel;

	 if  (  !pDynLib->pOpenProcessToken(  hProcess,  TOKEN_QUERY,  &hAccessToken  )  )  goto  errLabel;
	 bTokenOpen  =  TRUE;

	 if  (  pDynLib->pGetTokenInformation(  hAccessToken,  TokenUser,  0,  0,  &cbti  )  )  {
		 traceLogA(  (char*)"Call should have failed due to zero-length buffer"  );  goto  errLabel;
	 }
	 if  (  GetLastError(  )  !=  ERROR_INSUFFICIENT_BUFFER  )  goto  errLabel;

	 if  (  !(  ptiUser  =  (  PTOKEN_USER  )mymalloc(  cbti  )  )  )  goto  errLabel;

	 if  (  !pDynLib->pGetTokenInformation(  hAccessToken,  TokenUser,  ptiUser,  cbti,  &cbti  )  )  goto  errLabel;

	 dwAccountSize		=	mycountof(  wDomainName  ),  dwDomainSize  =  mycountof(  wAccountName  );
	 if  (  !pDynLib->pLookupAccountSidW(  0,  ptiUser->User.Sid,  wAccountName,  &dwAccountSize,  wDomainName,  &dwDomainSize,  &snu  )  )  goto  errLabel;
	 
	 iErr  =  0;

errLabel:

	 if  (  ptiUser  )  free(  ptiUser  );
	 if  (  bTokenOpen  )  CloseHandle(  hAccessToken  );
	 if  (  hProcess  )  CloseHandle(  hProcess  );

	 if  (  iErr  )  traceLogA(  (char*)"getProcessSthById: can't get userName of %d(  pid  )",  processId  );
	 else  traceLogA(  (char*)"getProcessSthById: pid is %d, %S@%S",  processId,  wAccountName,  wDomainName  );

	 if  (  !iErr  )  {
		 if  (  wAccountNameBuf  )  wcsncpy(  wAccountNameBuf,  wAccountName,  uiAccountNameBufSize  );
		 if  (  wDomainNameBuf  )  wcsncpy(  wDomainNameBuf,  wDomainName,  uiDomainNameBufSize  );
	 }

	 return  iErr;

}

 int  getWtsSessionId(  QY_ENV  *  pEnv,  DWORD  *  pCurSessionId,  DWORD  *  pActiveSessionId  )
{
	 int				iErr		=	-1;
	 QWM_DYN_LIB	*	pDynLib		=	(  QWM_DYN_LIB  *  )pEnv->pDynLibs;
	 DWORD				curSessionId  =  -1,  activeSessionId  =  -1;

	 if  (  !pDynLib  )  return  -1;

	 if  (  !pDynLib->pProcessIdToSessionId  )  curSessionId  =  0;
	 else  pDynLib->pProcessIdToSessionId(  GetCurrentProcessId(  ),  &curSessionId  );
	 if  (  !pDynLib->pWTSGetActiveConsoleSessionId  )  activeSessionId  =  0;
	 else  activeSessionId  =  pDynLib->pWTSGetActiveConsoleSessionId(  );

	 iErr  =  0;

//  errLabel:
	 if  (  !iErr  )  {
		 if  (  pCurSessionId  )  *pCurSessionId  =  curSessionId;
		 if  (  pActiveSessionId  )  *pActiveSessionId  =  activeSessionId;
	 }

	 return  iErr;
}

 
