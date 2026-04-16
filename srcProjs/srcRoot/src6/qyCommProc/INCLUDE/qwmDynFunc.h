
/*  */

#ifndef  __INC_FUNCTIONS_H
#define  __INC_FUNCTIONS_H

#include	<windows.h>
#include	<windef.h>
#include	<lmcons.h>
#include	<tlhelp32.h>
#include	<IPTypes.h>

#include	<ras.h>
#include	<udpmib.h>



#ifndef  DWORD_PTR
		//#define	DWORD_PTR	unsigned  long  *
#endif
#define	ULONG_PTR	unsigned  long  *

#include	"qyDynLib.h"

//
#include	"mySetupApi.h"
//
#include	"myCfgMgr32.h"

//  #include	"myIpHlpApi.h"	//  2005/05/23
#include	<shlwapi.h>

#include <ifmib.h>
#include <IPExport.h>
#include <tcpmib.h>


//
#ifndef _WINTERNL_
	   #include	"myntqueryinformationprocess.h"
#else
	typedef  NTSYSAPI  NTSTATUS  (  NTAPI  *  PF_NtQueryInformationProcess  )(
	    IN HANDLE ProcessHandle,
	    IN PROCESSINFOCLASS ProcessInformationClass,
	    OUT PVOID ProcessInformation,
	    IN ULONG ProcessInformationLength,
	    OUT PULONG ReturnLength OPTIONAL
	    );
	//  extern  PF_NtQueryInformationProcess  pfNtQueryInformationProcess;
	
	typedef  NTSYSAPI  NTSTATUS  (  NTAPI  *  PF_NtQuerySystemInformation  )(
	      IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
	      OUT PVOID SystemInformation,
		  IN ULONG SystemInformationLength,
	      OUT PULONG ReturnLength OPTIONAL
	      );	
#endif


struct  PASSWORD_CACHE_ENTRY	{
			WORD				cbEntry;  
			WORD				cbResource;
			WORD				cbPassword;
			BYTE				iEntry;    
			BYTE				nType;     
			char				abResource[1];
};

typedef  BOOL  (FAR PASCAL *CACHECALLBACK)( struct PASSWORD_CACHE_ENTRY FAR *pce, DWORD dwRefData );

DWORD  APIENTRY  WNetCachePassword(LPSTR pbResource, WORD  cbResource, LPSTR pbPassword, WORD cbPassword, BYTE nType, UINT fnFlags);
DWORD  APIENTRY  WNetGetCachedPassword(LPSTR pbResource,WORD cbResource,LPSTR pbPassword, LPWORD pcbPassword, BYTE nType );
DWORD  APIENTRY  WNetRemoveCachedPassword(LPSTR pbResource, WORD cbResource, BYTE nType);
DWORD  APIENTRY  WNetEnumCachedPasswords(LPSTR pbPrefix,WORD cbPrefix,BYTE nType,CACHECALLBACK pfnCallback,DWORD dwRefData);

typedef  BOOL (WINAPI *MODULEWALK)(HANDLE hSnapshot, LPMODULEENTRY32 lpme); 
typedef  BOOL (WINAPI *THREADWALK)(HANDLE hSnapshot, LPTHREADENTRY32 lpte); 
typedef  BOOL (WINAPI *PROCESSWALK)(HANDLE hSnapshot, LPPROCESSENTRY32 lppe); 
typedef  HANDLE (WINAPI *CREATESNAPSHOT)(DWORD dwFlags, DWORD th32ProcessID); 
typedef  DWORD (WINAPI *REGSERVICEPROC)(DWORD dwProcessId, DWORD dwServiceType); 
typedef  HANDLE (WINAPI *CREATEREMOTETHREAD)(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes, DWORD dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);
typedef  LPVOID (WINAPI *VIRTUALALLOCEX)(HANDLE hProcess, LPVOID lpAddress, DWORD dwSize, DWORD flAllocationType, DWORD flProtect);
typedef  BOOL (WINAPI *VIRTUALFREEEX)(HANDLE hProcess, LPVOID lpAddress, DWORD dwSize, DWORD dwFreeType);
typedef  BOOL (WINAPI *VIRTUALPROTECTEX)(HANDLE hProcess, LPVOID lpAddress, DWORD dwSize, DWORD flNewProtect, PDWORD lpflOldProtect);
typedef  DWORD (WINAPI *VIRTUALQUERYEX)(HANDLE hProcess, LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, DWORD dwLength);
//  2005/09/13
typedef  WINBASEAPI  HANDLE  (  WINAPI  *  PF_CreateIoCompletionPort  )(  HANDLE FileHandle,  HANDLE ExistingCompletionPort,  DWORD CompletionKey,  DWORD NumberOfConcurrentThreads  );
typedef  WINBASEAPI  BOOL  (  WINAPI  *  PF_GetQueuedCompletionStatus  )(  HANDLE CompletionPort,  LPDWORD lpNumberOfBytesTransferred,  LPDWORD lpCompletionKey,  LPOVERLAPPED *lpOverlapped,  DWORD dwMilliseconds  );
typedef  WINBASEAPI  BOOL  (  WINAPI  *  PF_PostQueuedCompletionStatus  )(  HANDLE CompletionPort,  DWORD dwNumberOfBytesTransferred,  DWORD dwCompletionKey,  LPOVERLAPPED lpOverlapped  );
#ifndef  __WINCE__
	typedef  WINBASEAPI  BOOL  (  WINAPI  *  PF_ReadDirectoryChangesW  )(  HANDLE hDirectory,  LPVOID lpBuffer,  DWORD nBufferLength,  BOOL bWatchSubtree,  DWORD dwNotifyFilter,  LPDWORD lpBytesReturned,  LPOVERLAPPED lpOverlapped,  LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine  );
#else
	#define	PF_ReadDirectoryChangesW	void  *
#endif
//  2006/09/06
typedef  WINBASEAPI  LPWSTR  (  WINAPI  *  PF_GetCommandLineW  )(      VOID      );
//  2009/10/11
#ifndef  __WINCE__
	typedef  BOOL  (  WINAPI  *  PF_GetSystemTimes  )(  __out_opt LPFILETIME lpIdleTime,  __out_opt LPFILETIME lpKernelTime,  __out_opt LPFILETIME lpUserTime  );
#else
	#define		PF_GetSystemTimes	void  *
#endif

//  2006/03/25
typedef  WINBASEAPI  BOOL  (  WINAPI  *  PF_GetFileAttributesEx  )(  LPCTSTR lpFileName,  GET_FILEEX_INFO_LEVELS fInfoLevelId,  LPVOID lpFileInformation  );
//
typedef  enum  _myCOMPUTER_NAME_FORMAT  {
			   myComputerNameNetBIOS,
			   myComputerNameDnsHostName,
			   myComputerNameDnsDomain,
			   myComputerNameDnsFullyQualified,
			   myComputerNamePhysicalNetBIOS,
			   myComputerNamePhysicalDnsHostName,
			   myComputerNamePhysicalDnsDomain,
			   myComputerNamePhysicalDnsFullyQualified,
			   myComputerNameMax
}		 myCOMPUTER_NAME_FORMAT;
typedef  BOOL  (  WINAPI  *  PF_SetComputerNameEx  )(  myCOMPUTER_NAME_FORMAT  NameType,  LPCTSTR  lpBuffer  );
//  2007/02/04
typedef  WINBASEAPI  BOOL  (  WINAPI  *  PF_ProcessIdToSessionId  )(  IN  DWORD dwProcessId,  OUT DWORD *pSessionId  );
typedef  WINBASEAPI  DWORD  (  WINAPI  *  PF_WTSGetActiveConsoleSessionId  )(  );

//  2009/07/12
#ifndef  __WINCE__
	typedef  WINBASEAPI  VOID  (  WINAPI  *  PF_InitializeSRWLock  )(  __out PSRWLOCK SRWLock  );
	typedef  WINBASEAPI  VOID  (  WINAPI  *  PF_AcquireSRWLockShared  )(  __inout PSRWLOCK SRWLock  );
	typedef  WINBASEAPI  VOID  (  WINAPI  *  PF_ReleaseSRWLockShared  )(  __inout PSRWLOCK SRWLock  );
	typedef  WINBASEAPI  VOID  (  WINAPI  *  PF_AcquireSRWLockExclusive  )(  __inout PSRWLOCK SRWLock  );
	typedef  WINBASEAPI  VOID  (  WINAPI  *  PF_ReleaseSRWLockExclusive  )(  __inout PSRWLOCK SRWLock  );
#else
	#define		PF_InitializeSRWLock		void  *
	#define		PF_AcquireSRWLockShared		void  *
	#define		PF_ReleaseSRWLockShared		void  *
	#define		PF_AcquireSRWLockExclusive	void  *
	#define		PF_ReleaseSRWLockExclusive	void  *
#endif

//  2010/05/15
typedef  BOOL  (  WINAPI  *  PF_IsWow64Process  )(  __in  HANDLE hProcess,  __out  PBOOL Wow64Process  );



//  2007/01/15, Secur32.lib
typedef  BOOLEAN  (  WINAPI  *  PF_GetUserNameExW  )(  int  NameFormat,  LPWSTR lpNameBuffer,  PULONG nSize  );



typedef DWORD (WINAPI *ENUMPASSWORD)(LPSTR pbPrefix, WORD  cbPrefix, BYTE  nType, CACHECALLBACK pfnCallback, DWORD dwRefData);
typedef DWORD (WINAPI *WNETCLOSEENUM)(HANDLE henum);
typedef DWORD (WINAPI *WNETENUMRESOURCE)(HANDLE henum, LPDWORD lpcCount, LPVOID lpBuffer, LPDWORD lpBufferSize );
typedef DWORD (WINAPI *WNETCANCELCONNECTION2)(LPCSTR lpName, DWORD dwFlags, BOOL fForce);
#ifndef  __WINCE__
	typedef DWORD (WINAPI *WNETOPENENUM)(DWORD dwScope, DWORD dwType, DWORD dwUsage, LPNETRESOURCE lpNetResource, LPHANDLE lphEnum );
	typedef DWORD (WINAPI *WNETADDCONNECTION2)(LPNETRESOURCEA lpNetResource, LPCSTR lpPassword, LPCSTR lpUserName, DWORD dwFlags);
#else
	#define		WNETOPENENUM		void  *
	#define		WNETADDCONNECTION2	void  *
#endif

typedef  NET_API_STATUS (  NET_API_FUNCTION  *  LMS_NETSESSIONENUM)(IN LPWSTR servername OPTIONAL, IN LPWSTR UncClientName OPTIONAL, IN LPWSTR username OPTIONAL, IN DWORD level, OUT LPBYTE *bufptr,IN DWORD prefmaxlen, OUT LPDWORD entriesread, OUT LPDWORD totalentries, IN OUT LPDWORD resume_handle OPTIONAL);
typedef  NET_API_STATUS (  NET_API_FUNCTION  *  LMS_NETSHAREENUM)(IN LPWSTR servername, IN DWORD level, OUT LPBYTE *bufptr, IN DWORD prefmaxlen, OUT LPDWORD entriesread, OUT LPDWORD totalentries, IN OUT LPDWORD resume_handle);
typedef  NET_API_STATUS (  NET_API_FUNCTION  *  LMS_NETSHAREDEL)(IN LPWSTR servername, IN LPWSTR netname, IN DWORD reserved);
typedef  NET_API_STATUS (  NET_API_FUNCTION  *  LMS_NETSHAREADD)(IN  LPWSTR  servername, IN  DWORD   level, IN  LPBYTE  buf, OUT LPDWORD parm_err);
typedef  NET_API_STATUS (  NET_API_FUNCTION  *  LMS_NETSERVERGETINFO)(LPWSTR servername, DWORD level, LPBYTE *bufptr);
typedef  NET_API_STATUS (  NET_API_FUNCTION  *  LMS_NETUSERENUM)(  LPWSTR  servername,  DWORD  level,  DWORD  filter,  LPBYTE  *  bufptr,  DWORD  prefmaxlen,  LPDWORD  entriesread,  LPDWORD  totalentries,  LPDWORD  resume_handle  );
typedef  NET_API_STATUS (  NET_API_FUNCTION  *  PF_NetUserGetGroups  )(  IN  LPCWSTR  servername OPTIONAL,  IN  LPCWSTR  username,  IN  DWORD  level,  OUT LPBYTE  *bufptr,  IN  DWORD  prefmaxlen,  OUT LPDWORD  entriesread,  OUT LPDWORD  totalentries  );
typedef  NET_API_STATUS (  NET_API_FUNCTION  *  PF_NetUserGetLocalGroups  )(  IN  LPCWSTR  servername OPTIONAL,  IN  LPCWSTR  username,  IN  DWORD  level,  IN  DWORD  flags,  OUT LPBYTE  *bufptr,  IN  DWORD  prefmaxlen,  OUT LPDWORD  entriesread,  OUT LPDWORD  totalentries  );
typedef  NET_API_STATUS (  NET_API_FUNCTION  *  PF_NetApiBufferFree  )(  IN  LPVOID  Buffer  );


 
typedef DWORD (WINAPI *SVR_NETSESSIONENUM)(const char FAR *pszServer, short sLevel, char FAR *pbBuffer, unsigned short cbBuffer, unsigned short FAR * pcEntriesRead, unsigned short FAR * pcTotalAvail);
typedef DWORD (WINAPI *SVR_NETSHAREENUM)(const char FAR *pszServer, short sLevel, char FAR *pbBuffer, unsigned short cbBuffer, unsigned short FAR * pcEntriesRead, unsigned short FAR * pcTotalAvail);
typedef DWORD (WINAPI *SVR_NETSHAREDEL)(const char FAR *pszServer, const char FAR *pszNetName, unsigned short usReserved);
typedef DWORD (WINAPI *SVR_NETSHAREADD)(const char FAR * pszServer, short sLevel, const char FAR * pbBuffer, unsigned short cbBuffer);
typedef NET_API_STATUS (WINAPI *SVR_NETSERVERGETINFO)(LPWSTR servername, DWORD level, LPBYTE *bufptr);

typedef  LONG (WINAPI *REGSETKEYSECURITY)(HKEY hKey,SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor);
typedef  BOOL (WINAPI *SETSECURITYDESCRIPTORDACL)(PSECURITY_DESCRIPTOR pSecurityDescriptor, BOOL bDaclPresent, PACL pDacl, BOOL bDaclDefaulted);
typedef  BOOL (WINAPI *GETACE)(PACL pAcl, DWORD dwAceIndex, LPVOID *pAce);
typedef  BOOL (WINAPI *ADDACCESSALLOWEDACE)(PACL pAcl, DWORD dwAceRevision, DWORD AccessMask, PSID pSid);
typedef  BOOL (WINAPI *INITIALIZEACL)(PACL pAcl, DWORD nAclLength, DWORD dwAclRevision);
typedef  BOOL (WINAPI *INITIALIZESECURITYDESCRIPTOR)(PSECURITY_DESCRIPTOR pSecurityDescriptor, DWORD dwRevision);
typedef  DWORD (WINAPI *GETLENGTHSID)(PSID pSid);
typedef  BOOL (WINAPI *LOOKUPACCOUNTNAME)(LPCTSTR lpSystemName, LPCTSTR lpAccountName, PSID Sid, LPDWORD cbSid, LPTSTR ReferencedDomainName, LPDWORD cbReferencedDomainName, PSID_NAME_USE peUse);
typedef  BOOL (WINAPI *LOOKUPACCOUNTSID)(LPCTSTR lpSystemName, PSID Sid, LPTSTR Name, LPDWORD cbName, LPTSTR ReferencedDomainName, LPDWORD cbReferencedDomainName, PSID_NAME_USE peUse);
typedef  BOOL  (  WINAPI  *  PF_LookupAccountSidW  )(  LPCWSTR lpSystemName,  PSID Sid,  LPWSTR Name,  LPDWORD cbName,  LPWSTR ReferencedDomainName,  LPDWORD cbReferencedDomainName,  PSID_NAME_USE peUse  );	//  2007/01/18
typedef  BOOL (WINAPI *GETSECURITYDESCRIPTORDACL)(PSECURITY_DESCRIPTOR pSecurityDescriptor, LPBOOL lpbDaclPresent, PACL *pDacl, LPBOOL lpbDaclDefaulted);
typedef  BOOL (WINAPI *GETSECURITYDESCRIPTORGROUP)(PSECURITY_DESCRIPTOR pSecurityDescriptor, PSID *pGroup, LPBOOL lpbGroupDefaulted);
typedef  BOOL (WINAPI *GETSECURITYDESCRIPTOROWNER)(PSECURITY_DESCRIPTOR pSecurityDescriptor, PSID *pOwner, LPBOOL lpbOwnerDefaulted); 
typedef  BOOL (WINAPI *OPENPROCESSTOKEN)(HANDLE ProcessHandle, DWORD DesiredAccess, PHANDLE TokenHandle);
typedef  BOOL (WINAPI *GETTOKENINFORMATION)(HANDLE TokenHandle, TOKEN_INFORMATION_CLASS TokenInformationClass, LPVOID TokenInformation, DWORD TokenInformationLength, PDWORD ReturnLength  );
//  typedef  BOOL (WINAPI *LOOKUPPRIVILEGEVALUE)(LPCSTR lpSystemName, LPCSTR lpName, PLUID lpLuid);
typedef  BOOL (WINAPI     *LOOKUPPRIVILEGEVALUE)(LPCTSTR lpSystemName,LPCTSTR lpName,PLUID lpLuid);
typedef  BOOL (WINAPI *ADJUSTTOKENPRIVILEGES)(HANDLE TokenHandle, BOOL DisableAllPrivileges, PTOKEN_PRIVILEGES NewState, DWORD BufferLength, PTOKEN_PRIVILEGES PreviousState, PDWORD ReturnLength);
typedef  LONG (WINAPI *REGGETKEYSECURITY)(HKEY hKey, SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor, LPDWORD lpcbSecurityDescriptor);
typedef  BOOL (WINAPI *ALLOCATEANDINITIALIZESID)(PSID_IDENTIFIER_AUTHORITY pIdentifierAuthority, BYTE nSubAuthorityCount, DWORD nSubAuthority0, DWORD nSubAuthority1, DWORD nSubAuthority2, DWORD nSubAuthority3, DWORD nSubAuthority4, DWORD nSubAuthority5, DWORD nSubAuthority6, DWORD nSubAuthority7, PSID *pSid );
typedef  PVOID (WINAPI *FREESID)( PSID pSid );
typedef  BOOL (WINAPI  *ISVALIDSID)(  PSID  pSid  );
typedef  PSID_IDENTIFIER_AUTHORITY  (  WINAPI  *  GETSIDIDENTIFIERAUTHORITY  )(  PSID  pSid  );
typedef  PUCHAR  (  WINAPI  *  GETSIDSUBAUTHORITYCOUNT  )(  PSID  pSid  );
typedef  PDWORD  (  WINAPI  *  GETSIDSUBAUTHORITY  )(  PSID  pSid,  DWORD  nSubAuthority  );
typedef  BOOL  (  WINAPI  *  PF_CreateProcessAsUserW  )(  IN HANDLE hToken,  IN LPCWSTR lpApplicationName,  IN LPWSTR lpCommandLine,  IN LPSECURITY_ATTRIBUTES lpProcessAttributes,  IN LPSECURITY_ATTRIBUTES lpThreadAttributes,  IN BOOL bInheritHandles,  IN DWORD dwCreationFlags,  IN LPVOID lpEnvironment,  IN LPCWSTR lpCurrentDirectory,  IN LPSTARTUPINFOW lpStartupInfo,  OUT LPPROCESS_INFORMATION lpProcessInformation  );
typedef  BOOL  (  WINAPI  *  PF_DuplicateTokenEx  )(  IN HANDLE hExistingToken,  IN DWORD dwDesiredAccess,  IN LPSECURITY_ATTRIBUTES lpTokenAttributes,  IN SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,  IN TOKEN_TYPE TokenType,  OUT PHANDLE phNewToken  ); 

#ifdef _WINSVC_
	
	typedef SC_HANDLE (WINAPI *OPENSCMANAGER)(LPCTSTR lpMachineName,LPCTSTR lpDatabaseName,DWORD dwDesiredAccess);
	//  typedef SC_HANDLE (WINAPI *CREATESERVICE)(SC_HANDLE hSCManager, LPCSTR lpServiceName, LPCSTR lpDisplayName, DWORD dwDesiredAccess, DWORD dwServiceType, DWORD dwStartType, DWORD dwErrorControl, LPCSTR lpBinaryPathName, LPCSTR lpLoadOrderGroup, LPDWORD lpdwTagId, LPCSTR lpDependencies, LPCSTR lpServiceStartName, LPCSTR lpPassword);
	typedef  SC_HANDLE (WINAPI *CREATESERVICE   )(SC_HANDLE hSCManager, LPCTSTR lpServiceName,LPCTSTR lpDisplayName,DWORD dwDesiredAccess, DWORD dwServiceType, DWORD dwStartType, DWORD dwErrorControl, LPCTSTR lpBinaryPathName,LPCTSTR lpLoadOrderGroup,LPDWORD lpdwTagId, LPCTSTR lpDependencies,LPCTSTR lpServiceStartName,LPCTSTR lpPassword);

	typedef BOOL (WINAPI *CLOSESERVICEHANDLE)(SC_HANDLE hSCObject);
	//  typedef SC_HANDLE (WINAPI *OPENSERVICE)(SC_HANDLE hSCManager, LPCSTR lpServiceName, DWORD dwDesiredAccess);
	typedef  SC_HANDLE (WINAPI *OPENSERVICE   )(SC_HANDLE hSCManager, LPCTSTR lpServiceName,DWORD dwDesiredAccess);
	//  typedef BOOL (WINAPI *STARTSERVICECTRLDISPATCHER)(CONST SERVICE_TABLE_ENTRYA *lpServiceStartTable);
	typedef BOOL (WINAPI *STARTSERVICECTRLDISPATCHER)(CONST SERVICE_TABLE_ENTRY *lpServiceStartTable);
	typedef SERVICE_STATUS_HANDLE (WINAPI *REGISTERSERVICECTRLHANDLER)(LPCTSTR lpServiceName, LPHANDLER_FUNCTION lpHandlerProc);
	typedef BOOL (WINAPI *SETSERVICESTATUS)(SERVICE_STATUS_HANDLE hServiceStatus, LPSERVICE_STATUS lpServiceStatus);
	typedef BOOL (WINAPI *DELETESERVICE)(SC_HANDLE hService);
	typedef BOOL (WINAPI *GETSERVICEDISPLAYNAME)(SC_HANDLE hSCManager, LPCTSTR lpServiceName, LPTSTR lpDisplayName, LPDWORD lpcchBuffer);
	typedef BOOL (WINAPI *STARTSERVICE)(SC_HANDLE hService, DWORD dwNumServiceArgs, LPCTSTR *lpServiceArgVectors);

#else

	#define		OPENSCMANAGER					void  *
	#define		CREATESERVICE					void  *
	#define		CLOSESERVICEHANDLE				void  *
	#define		OPENSERVICE						void  *
	#define		STARTSERVICECTRLDISPATCHER		void  *
	#define		REGISTERSERVICECTRLHANDLER		void  *
	#define		SETSERVICESTATUS				void  *
	#define		DELETESERVICE					void  *
	#define		GETSERVICEDISPLAYNAME			void  *
	#define		STARTSERVICE					void  *

#endif

//
typedef  WINADVAPI  HANDLE  (  WINAPI  *  PF_OpenEventLog  )(  LPCTSTR   lpUNCServerName,  LPCTSTR   lpSourceName  );
typedef  WINADVAPI  BOOL  (  WINAPI  *  PF_CloseEventLog  )(  HANDLE  hEventLog  );
typedef  WINADVAPI  BOOL  (  WINAPI  *  PF_ReadEventLog  )(  HANDLE  hEventLog,  DWORD  dwReadFlags,  DWORD  dwRecordOffset,  LPVOID  lpBuffer,  DWORD  nNumberOfBytesToRead,  DWORD  *  pnBytesRead,  DWORD  *  pnMinNumberOfBytesNeeded  );
//  2006/04/23
typedef  WINADVAPI  LONG  (  APIENTRY  *  PF_RegOpenKeyW  )(  HKEY hKey,  LPCWSTR lpSubKey,  PHKEY phkResult  );
typedef  WINADVAPI  LONG  (  APIENTRY  *  PF_RegOpenKeyExW  )(  HKEY hKey,  LPCWSTR lpSubKey,  DWORD ulOptions,  REGSAM samDesired,  PHKEY phkResult  );
typedef  WINADVAPI  LONG  (  APIENTRY  *  PF_RegEnumKeyW  )(  HKEY hKey,  DWORD dwIndex,  LPWSTR lpName,  DWORD cbName  );
typedef  WINADVAPI  LONG  (  APIENTRY  *  PF_RegEnumKeyExW  )(  HKEY hKey,  DWORD dwIndex,  LPWSTR lpName,  LPDWORD lpcbName,  LPDWORD lpReserved,  LPWSTR lpClass,  LPDWORD lpcbClass,  PFILETIME lpftLastWriteTime  );
typedef  WINADVAPI  LONG  (  APIENTRY  *  PF_RegEnumValueW  )(  HKEY hKey,  DWORD dwIndex,  LPWSTR lpValueName,  LPDWORD lpcbValueName,  LPDWORD lpReserved,  LPDWORD lpType,  LPBYTE lpData,  LPDWORD lpcbData  );
typedef  WINADVAPI  LONG  (  APIENTRY  *  PF_RegQueryValueExW  )(  HKEY hKey,  LPCWSTR lpValueName,  LPDWORD lpReserved,  LPDWORD lpType,  LPBYTE lpData,  LPDWORD lpcbData  );



typedef DWORD ( WINAPI *RASENUMCONNECTIONS )( LPRASCONN lprasconn, LPDWORD lpcb, LPDWORD lpcConnections );
typedef DWORD ( WINAPI *RASHANGUP )( HRASCONN hrasconn );
typedef DWORD ( WINAPI *RASGETERRORSTRING )( UINT uErrorValue, LPTSTR lpszErrorString, DWORD cBufSize );
typedef DWORD ( WINAPI *RASGETCONNECTSTATUS )( HRASCONN hrasconn, LPRASCONNSTATUS lprasconnstatus );
typedef DWORD ( WINAPI *RASGETENTRYPROPERTIES )( LPCTSTR lpszPhonebook, LPCTSTR lpszEntry, LPRASENTRY lpRasEntry, LPDWORD lpdwEntryInfoSize, LPBYTE lpbDeviceInfo, LPDWORD lpdwDeviceInfoSize );
//typedef DWORD ( WINAPI *RASGETENTRYDIALPARAMS )( LPCTSTR lpszPhonebook, LPRASDIALPARAMS lprasdialparams, LPBOOL lpfPassword ); 
typedef DWORD ( WINAPI *RASENUMENTRIES )( LPCTSTR reserved, LPCTSTR lpszPhonebook, LPRASENTRYNAME lprasentryname, LPDWORD lpcb, LPDWORD lpcEntries  );

#ifdef  NCB_INCLUDED
	typedef UCHAR ( WINAPI *NETBIOS )( PNCB pncb );
#else
	#define		NETBIOS							void  *
#endif


#if  0
typedef  int  (  WINAPI  *  PF_WSAStartup  )(  WORD wVersionRequested,  LPWSADATA lpWSAData  );
typedef  int  (  WINAPI  *  PF_WSACleanup  )(void);
typedef  unsigned  long  (  WINAPI  *  PF_inet_addr  )(  const char FAR * cp  );
typedef  char *  (  WINAPI  *  PF_inet_ntoa  )(  struct in_addr in  );
typedef  SOCKET  (  WINAPI  *  PF_socket  )(  int af,  int type,  int protocol  );
typedef  int  (  WINAPI  *  PF_bind  )(  SOCKET s,  const struct sockaddr FAR*  name,  int namelen  );
typedef  int  (  WINAPI  *  PF_listen  )(  SOCKET s,  int backlog  );
typedef  SOCKET  (  WINAPI  *  PF_accept  )(  SOCKET s,  struct sockaddr FAR* addr,  int FAR* addrlen  );
typedef  int  (  WINAPI  *  PF_connect  )(  SOCKET s,  const struct sockaddr FAR*  name,  int namelen  );
typedef  int  (  WINAPI  *  PF_select  )(  int nfds,  fd_set FAR * readfds,  fd_set FAR * writefds,  fd_set FAR * exceptfds,  const struct timeval FAR * timeout  );
typedef  int  (  WINAPI  *  PF_getsockname  )(  SOCKET s,  struct sockaddr FAR*  name,  int FAR*  namelen  );
typedef  int  (  WINAPI  *  PF_getpeername  )(  SOCKET s,  struct sockaddr FAR*  name,  int FAR*  namelen  );
typedef  int  (  WINAPI  *  PF_closesocket  )(  SOCKET s  );
typedef  int  (  WINAPI  *  PF_recv  )(  SOCKET s,  char FAR* buf,  int len,  int flags  );
typedef  int  (  WINAPI  *  PF_send  )(  SOCKET s,  const char FAR * buf,  int len,  int flags  );
typedef  int  (  WINAPI  *  PF_WSAGetLastError  )(void);
typedef  int  (  WINAPI  *  PF_ioctlsocket  )(  SOCKET s,  long cmd,  u_long FAR* argp  );
typedef  int  (  WINAPI  *  PF_gethostname  )(  char FAR * name,  int namelen  );
typedef  struct hostent FAR *  (  WINAPI  *  PF_gethostbyname  )(  const char FAR * name  );
typedef  u_short  (  WINAPI  *  PF_htons  )(  u_short hostshort  );
typedef  int  (  WINAPI  *  PF_setsockopt  )(  SOCKET s,  int level,  int optname,  const char FAR * optval,  int optlen  );
#endif

typedef  WINSETUPAPI  HDEVINFO  (  WINAPI  *  PF_SetupDiGetClassDevs  )(  IN CONST GUID *ClassGuid,  OPTIONAL IN PCSTR  Enumerator,  OPTIONAL IN HWND hwndParent,  OPTIONAL IN DWORD Flags  );
typedef  WINSETUPAPI  BOOL  (  WINAPI  *  PF_SetupDiEnumDeviceInfo  )(  IN HDEVINFO DeviceInfoSet,  IN DWORD MemberIndex,  OUT PSP_DEVINFO_DATA DeviceInfoData  );
typedef  WINSETUPAPI  BOOL  (  WINAPI  *  PF_SetupDiDestroyDeviceInfoList  )(  IN HDEVINFO DeviceInfoSet  );
typedef  WINSETUPAPI  BOOL  (  WINAPI  *  PF_SetupDiEnumDeviceInterfaces  )(  IN HDEVINFO DeviceInfoSet,  IN PSP_DEVINFO_DATA DeviceInfoData,  OPTIONAL IN CONST GUID *InterfaceClassGuid,  IN DWORD MemberIndex,  OUT PSP_DEVICE_INTERFACE_DATA  DeviceInterfaceData  );
//  typedef  WINSETUPAPI  BOOL  (  WINAPI  *  PF_SetupDiGetDeviceInterfaceDetail  )(  IN HDEVINFO DeviceInfoSet,  IN PSP_DEVICE_INTERFACE_DATA DeviceInterfaceData,  OUT PSP_DEVICE_INTERFACE_DETAIL_DATA_A DeviceInterfaceDetailData,  OPTIONAL IN DWORD DeviceInterfaceDetailDataSize,  OUT PDWORD RequiredSize,  OPTIONAL OUT PSP_DEVINFO_DATA DeviceInfoData OPTIONAL  );
typedef  WINSETUPAPI  BOOL  (  WINAPI  *  PF_SetupDiGetDeviceInterfaceDetail  )(  IN HDEVINFO DeviceInfoSet,  IN PSP_DEVICE_INTERFACE_DATA DeviceInterfaceData,  OUT PSP_DEVICE_INTERFACE_DETAIL_DATA DeviceInterfaceDetailData,  OPTIONAL IN DWORD DeviceInterfaceDetailDataSize,  OUT PDWORD RequiredSize,  OPTIONAL OUT PSP_DEVINFO_DATA DeviceInfoData OPTIONAL  );
typedef  WINSETUPAPI  BOOL  (  WINAPI  *  PF_SetupDiGetDeviceRegistryProperty  )(  IN HDEVINFO DeviceInfoSet,  IN PSP_DEVINFO_DATA DeviceInfoData,  IN DWORD Property,  OUT PDWORD PropertyRegDataType, OPTIONAL OUT PBYTE PropertyBuffer,  IN DWORD PropertyBufferSize,  OUT PDWORD RequiredSize OPTIONAL  );
typedef  WINSETUPAPI  BOOL  (  WINAPI  *  PF_SetupDiSetClassInstallParams  )(  IN HDEVINFO DeviceInfoSet,  IN PSP_DEVINFO_DATA DeviceInfoData, OPTIONAL IN PSP_CLASSINSTALL_HEADER ClassInstallParams, OPTIONAL IN DWORD ClassInstallParamsSize  );
typedef  WINSETUPAPI  BOOL  (  WINAPI  *  PF_SetupDiCallClassInstaller  )(  IN DI_FUNCTION InstallFunction,  IN HDEVINFO DeviceInfoSet,  IN PSP_DEVINFO_DATA DeviceInfoData OPTIONAL  );
typedef  WINSETUPAPI  BOOL  (  WINAPI  *  PF_SetupDiGetDeviceInstallParams  )(  IN  HDEVINFO DeviceInfoSet,  IN  PSP_DEVINFO_DATA DeviceInfoData,  OPTIONAL OUT PSP_DEVINSTALL_PARAMS DeviceInstallParams  );

//
typedef  CMAPI  CONFIGRET  (  WINAPI  *  PF_CM_Get_Device_ID  )(  IN  DEVINST dnDevInst,  OUT PTCHAR Buffer,  IN ULONG BufferLen,  IN ULONG ulFlags  );
typedef  CMAPI  CONFIGRET  (  WINAPI  *  PF_CM_Get_DevNode_Status  )(  OUT PULONG  pulStatus,  OUT PULONG  pulProblemNumber,  IN DEVINST  dnDevInst,  IN ULONG  ulFlags  );



//  2005/05/23
typedef  DWORD  (  WINAPI  *  PF_GetAdaptersInfo  )(  PIP_ADAPTER_INFO,  PULONG  );
typedef  DWORD  (  WINAPI  *  PF_GetPerAdapterInfo  )(  ULONG,  PIP_PER_ADAPTER_INFO,  PULONG  );
//  2005/09/16
typedef  DWORD  (  WINAPI  *  PF_GetTcpTable  )(  OUT  PMIB_TCPTABLE pTcpTable,  IN OUT PDWORD  pdwSize,  IN  BOOL  bOrder  );
typedef  DWORD  (  WINAPI  *  PF_GetUdpTable  )(  OUT  PMIB_UDPTABLE pUdpTable,  IN OUT PDWORD  pdwSize,  IN  BOOL  bOrder  );
//  2006/09/10
typedef  DWORD  (  WINAPI  *  PF_GetIfTable  )(PMIB_IFTABLE,PULONG,BOOL);
typedef  DWORD  (  WINAPI  *  PF_SetIfEntry  )(PMIB_IFROW);
typedef  DWORD  (  WINAPI  *  PF_GetIfEntry  )(PMIB_IFROW);
//  2007/01/20
typedef  DWORD  (  WINAPI  *  PF_SendARP  )(IPAddr,IPAddr,PULONG,PULONG);


//  2005/06/26
typedef  DWORD  (  WINAPI  *  PF_SHDeleteKey  )(  HKEY  hkey,  LPCTSTR  pszSubKey  );
//  typedef LWSTDAPI_(DWORD)    SHDeleteKeyA(HKEY hkey, LPCSTR pszSubKey);

//  2005/12/23
#if !defined( __WINCE__ )  &&  defined(  WINMMAPI  )
	typedef  WINMMAPI  MCIERROR  (  WINAPI  *  PF_mciSendCommand  )(MCIDEVICEID mciId, UINT uMsg, DWORD dwParam1, DWORD dwParam2);
#else
	#define		PF_mciSendCommand	void  *
#endif

//  2005/12/25
typedef  RPCRTAPI  RPC_STATUS  (  RPC_ENTRY  *  PF_UuidFromString  )(  IN unsigned char __RPC_FAR * StringUuid,  OUT UUID __RPC_FAR * Uuid  );


//  2006/04/13
typedef  BOOL  (  WINAPI  *  PF_EnumProcessModules  )(  HANDLE hProcess,  HMODULE *lphModule,  DWORD cb,  LPDWORD lpcbNeeded  );
typedef  DWORD  (  WINAPI  *  PF_GetModuleFileNameExW  )(  HANDLE hProcess,  HMODULE hModule,  LPWSTR lpFilename,  DWORD nSize  );	//  2006/04/13
typedef  BOOL  (  WINAPI  *  PF_EnumProcesses  )(  DWORD * lpidProcess,  DWORD   cb,  DWORD * cbNeeded  );


//  2007/02/11
//  typedef  BOOL  (  WINAPI  *  PF_WTSSendMessageA  )(  IN HANDLE hServer,  IN DWORD SessionId,  IN LPSTR pTitle,  IN DWORD TitleLength,  IN LPSTR pMessage,  IN DWORD MessageLength,  IN DWORD Style,  IN DWORD Timeout,  OUT DWORD * pResponse,  IN BOOL bWait  );
typedef  BOOL  (  WINAPI  *  PF_WTSSendMessageW  )(  IN HANDLE hServer,  IN DWORD SessionId,  IN LPWSTR pTitle,  IN DWORD TitleLength,  IN LPWSTR pMessage,  IN DWORD MessageLength,  IN DWORD Style,  IN DWORD Timeout,  OUT DWORD * pResponse,  IN BOOL bWait  );
typedef  BOOL  (  WINAPI  *  PF_WTSRegisterSessionNotification  )(  HWND hWnd,  DWORD dwFlags  );	//  2007/02/27
typedef  BOOL  (  WINAPI  *  PF_WTSUnRegisterSessionNotification  )(  HWND hWnd  );					//  2007/02/27


//  2007/02/28
typedef  BOOL  (  WINAPI  *  PF_CreateEnvironmentBlock  )(  OUT LPVOID *lpEnvironment,  IN HANDLE  hToken,  IN BOOL    bInherit  );
typedef  BOOL  (  WINAPI  *  PF_DestroyEnvironmentBlock  )(  IN LPVOID  lpEnvironment  );

//  2007/04/06
typedef  HRESULT (  WINAPI  *  PF_SHGetFolderPathW  )(  HWND  hwnd,  int  csidl,  HANDLE  hToken,  DWORD  dwFlags,  LPWSTR  pszPath  );


//  2011/10/04
typedef  WINUSERAPI  int  (  WINAPI  *  PF_MessageBoxTimeoutW  )(  __in_opt HWND hWnd,  __in_opt LPCWSTR lpText,  __in_opt LPCWSTR lpCaption,  __in UINT uType,  __in  WORD  wLanguageId,  __in  DWORD  dwMilliseconds  );


//
typedef  struct  __qwmDynLib_t								{

				 QY_DYN_LIBS								common;

				 //
				 HINSTANCE									ghDll_NetApi32;
				 HINSTANCE									ghDll_SvrApi;
				 HINSTANCE									ghDll_Mpr;
				 HINSTANCE									ghDll_Kernel32;
				 HINSTANCE									ghDll_Shell32;
				 HINSTANCE									ghDll_AdvApi32;
				 HINSTANCE									ghDll_RasApi32;
				 HINSTANCE									ghDll_InetMib1;
				 //  HINSTANCE									ghDll_WSock32;
				 HINSTANCE									ghDll_SetupApi;			//  2005/01/05
				 HINSTANCE									ghDll_CfgMgr32;			//  2005/01/05
				 HINSTANCE									ghDll_IpHlpApi;			//  2005/05/23
				 HINSTANCE									ghDll_ShlwApi;			//  2005/06/25
				 HINSTANCE									ghDll_Winmm;			//  2005/12/23
				 HINSTANCE									ghDll_Rpcrt4;			//  2005/12/25
				 HINSTANCE									ghDll_NtDll;			//  2005/07/03
				 HINSTANCE									ghDll_PsApi;			//  2006/04/13
				 HINSTANCE									ghDll_WtsApi32;			//  2007/02/10	
				 HINSTANCE									ghDll_UserEnv;			//  2007/02/28
				 HINSTANCE									ghDll_User32;			//  2011/10/04

				 CREATESNAPSHOT								pCreateToolhelp32Snapshot; 
				 MODULEWALK									pModule32First; 
				 MODULEWALK									pModule32Next; 
				 PROCESSWALK								pProcess32First; 
				 PROCESSWALK								pProcess32Next; 
				 THREADWALK									pThread32First; 
				 THREADWALK									pThread32Next; 
				 REGSERVICEPROC								pRegisterServiceProcess;
				 CREATEREMOTETHREAD							pCreateRemoteThread;
				 VIRTUALALLOCEX								pVirtualAllocEx;
				 VIRTUALFREEEX								pVirtualFreeEx;
				 VIRTUALQUERYEX								pVirtualQueryEx;
				 VIRTUALPROTECTEX							pVirtualProtectEx;

				 //  2005/09/13
				 PF_CreateIoCompletionPort					pCreateIoCompletionPort;
				 PF_GetQueuedCompletionStatus				pGetQueuedCompletionStatus;
				 PF_PostQueuedCompletionStatus				pPostQueuedCompletionStatus;
				 PF_ReadDirectoryChangesW					pReadDirectoryChangesW;

				 //  2006/09/06
				 PF_GetCommandLineW							pGetCommandLineW;
				 //  2009/10/11
				 PF_GetSystemTimes							pGetSystemTimes;

				 //  2005/03/25
				 PF_GetFileAttributesEx						pGetFileAttributesEx;

				 //
				 PF_SetComputerNameEx						pSetComputerNameEx;
				 //  PF_GetUserNameExW						pGetUserNameExW;				//  2007/01/15

				 PF_ProcessIdToSessionId					pProcessIdToSessionId;			//  2007/02/04
				 PF_WTSGetActiveConsoleSessionId			pWTSGetActiveConsoleSessionId;	//  2007/02/04
				 
				 PF_InitializeSRWLock						pInitializeSRWLock;				//  2009/07/12
				 PF_AcquireSRWLockShared					pAcquireSRWLockShared;
				 PF_ReleaseSRWLockShared					pReleaseSRWLockShared;
				 PF_AcquireSRWLockExclusive					pAcquireSRWLockExclusive;
				 PF_ReleaseSRWLockExclusive					pReleaseSRWLockExclusive;  

				 PF_IsWow64Process							pIsWow64Process;				//  2010/05/15

				 //  ENUMPASSWORD							pWNetEnumCachedPasswords;		//  2006/03/18, Nod杀毒软件瞎报，暂时用不着，故注释掉拉倒
				 WNETCLOSEENUM								pWNetCloseEnum;
				 WNETENUMRESOURCE							pWNetEnumResource;
				 WNETOPENENUM								pWNetOpenEnum;
				 WNETCANCELCONNECTION2						pWNetCancelConnection2;
				 WNETADDCONNECTION2							pWNetAddConnection2;

				 LMS_NETSESSIONENUM							pLMSNetSessionEnum;
				 LMS_NETSHAREENUM							pLMSNetShareEnum;
				 LMS_NETSHAREDEL							pLMSNetShareDel;
				 LMS_NETSHAREADD							pLMSNetShareAdd;
				 //  LMS_NETAPIBUFFERFREE					pLMSNetApiBufferFree;
				 PF_NetApiBufferFree						pNetApiBufferFree;				//  2007/02/17, 因为pLMSNetApiBufferFree不够直观，故做修改
				 LMS_NETSERVERGETINFO						pLMSNetServerGetInfo;			//  2003/02/04 加
				 LMS_NETUSERENUM							pLMSNetUserEnum;				//  2003/11/14
				 PF_NetUserGetGroups						pNetUserGetGroups;				//  2007/02/17
				 PF_NetUserGetLocalGroups					pNetUserGetLocalGroups;			//  2007/02/17

				 NETBIOS									pNetbios;

				 SVR_NETSESSIONENUM							pSVRNetSessionEnum;
				 SVR_NETSHAREENUM							pSVRNetShareEnum;
				 SVR_NETSHAREDEL							pSVRNetShareDel;
				 SVR_NETSHAREADD							pSVRNetShareAdd;
				 SVR_NETSERVERGETINFO						pSVRNetServerGetInfo;				//  2003/02/04 加

				 //  shell32
				 PF_SHGetFolderPathW						pSHGetFolderPathW;				//  2007/04/05

				 REGSETKEYSECURITY							pRegSetKeySecurity;
				 SETSECURITYDESCRIPTORDACL					pSetSecurityDescriptorDacl;
				 GETACE										pGetAce;
				 ADDACCESSALLOWEDACE						pAddAccessAllowedAce;
				 INITIALIZEACL								pInitializeAcl;
				 INITIALIZESECURITYDESCRIPTOR				pInitializeSecurityDescriptor;
				 GETLENGTHSID								pGetLengthSid;
				 LOOKUPACCOUNTNAME							pLookupAccountName;
				 LOOKUPACCOUNTSID							pLookupAccountSid;
				 PF_LookupAccountSidW						pLookupAccountSidW;	//  2007/01/18
				 GETSECURITYDESCRIPTORDACL					pGetSecurityDescriptorDacl;
				 GETSECURITYDESCRIPTORGROUP					pGetSecurityDescriptorGroup;
				 GETSECURITYDESCRIPTOROWNER					pGetSecurityDescriptorOwner;
				 OPENPROCESSTOKEN							pOpenProcessToken;
				 GETTOKENINFORMATION						pGetTokenInformation;
				 LOOKUPPRIVILEGEVALUE						pLookupPrivilegeValue;
				 ADJUSTTOKENPRIVILEGES						pAdjustTokenPrivileges;
				 REGGETKEYSECURITY							pRegGetKeySecurity;
				 ALLOCATEANDINITIALIZESID					pAllocateAndInitializeSid; 
				 FREESID									pFreeSid;	
				 ISVALIDSID									pIsValidSid;
				 GETSIDIDENTIFIERAUTHORITY					pGetSidIdentifierAuthority;	
				 GETSIDSUBAUTHORITYCOUNT					pGetSidSubAuthorityCount;
				 GETSIDSUBAUTHORITY							pGetSidSubAuthority;	 
				 PF_CreateProcessAsUserW					pCreateProcessAsUserW;			//  2007/02/28
				 PF_DuplicateTokenEx						pDuplicateTokenEx;				//  2007/02/28

				 OPENSCMANAGER								pOpenSCManager;
				 CREATESERVICE								pCreateService;
				 CLOSESERVICEHANDLE							pCloseServiceHandle;
				 OPENSERVICE								pOpenService;
				 STARTSERVICECTRLDISPATCHER					pStartServiceCtrlDispatcher;
				 REGISTERSERVICECTRLHANDLER					pRegisterServiceCtrlHandler;
				 SETSERVICESTATUS							pSetServiceStatus;
				 DELETESERVICE								pDeleteService;
				 GETSERVICEDISPLAYNAME						pGetServiceDisplayName;
				 STARTSERVICE								pStartService;
				 //
				 PF_OpenEventLog							pOpenEventLog;
				 PF_CloseEventLog							pCloseEventLog;
				 PF_ReadEventLog							pReadEventLog;
				 //  2006/04/23
			#if  0
				 PF_RegOpenKeyW								pRegOpenKeyW;
				 PF_RegOpenKeyExW							pRegOpenKeyExW;
				 PF_RegEnumKeyW								pRegEnumKeyW;
				 PF_RegEnumKeyExW							pRegEnumKeyExW;		//  2006/07/18
				 PF_RegEnumValueW							pRegEnumValueW;		//  2006/07/23
				 PF_RegQueryValueExW						pRegQueryValueExW;
			#endif

				 RASENUMCONNECTIONS							pRasEnumConnections;
				 RASHANGUP									pRasHangUp;
				 RASGETERRORSTRING							pRasGetErrorString;
				 RASGETCONNECTSTATUS						pRasGetConnectStatus;
				 RASGETENTRYPROPERTIES						pRasGetEntryProperties;
				 //RASGETENTRYDIALPARAMS					pRasGetEntryDialParams;
				 RASENUMENTRIES								pRasEnumEntries;

				 //
#if  0
				 PF_WSAStartup								pWSAStartup;
				 PF_WSACleanup								pWSACleanup;
				 PF_inet_addr								pinet_addr;
				 PF_inet_ntoa								pinet_ntoa;
				 PF_socket									psocket;
				 PF_bind									pbind;
				 PF_listen									plisten;
				 PF_accept									paccept;
				 PF_connect									pconnect;
				 PF_select									pselect;
				 PF_getsockname								pgetsockname;
				 PF_getpeername								pgetpeername;
				 PF_closesocket								pclosesocket;
				 PF_recv									precv;
				 PF_send									psend;
				 PF_WSAGetLastError							pWSAGetLastError;
				 PF_ioctlsocket								pioctlsocket;
				 PF_gethostname								pgethostname;
				 PF_gethostbyname							pgethostbyname;
				 PF_htons									phtons;
				 PF_setsockopt								psetsockopt;
#endif

				 //  2005/01/05
				 PF_SetupDiGetClassDevs						pSetupDiGetClassDevs;
				 PF_SetupDiEnumDeviceInfo					pSetupDiEnumDeviceInfo;
				 PF_SetupDiDestroyDeviceInfoList			pSetupDiDestroyDeviceInfoList;
				 PF_SetupDiEnumDeviceInterfaces				pSetupDiEnumDeviceInterfaces;
				 PF_SetupDiGetDeviceInterfaceDetail			pSetupDiGetDeviceInterfaceDetail;
				 PF_SetupDiGetDeviceRegistryProperty		pSetupDiGetDeviceRegistryProperty;
				 PF_SetupDiSetClassInstallParams			pSetupDiSetClassInstallParams;
				 PF_SetupDiCallClassInstaller				pSetupDiCallClassInstaller;
				 PF_SetupDiGetDeviceInstallParams			pSetupDiGetDeviceInstallParams;
				 //
				 PF_CM_Get_Device_ID						pCM_Get_Device_ID;
				 PF_CM_Get_DevNode_Status					pCM_Get_DevNode_Status;
				 //  2005/05/23
				 PF_GetAdaptersInfo							pGetAdaptersInfo;
				 PF_GetPerAdapterInfo						pGetPerAdapterInfo;
				 //  2005/09/16
				 PF_GetTcpTable								pGetTcpTable;
				 PF_GetUdpTable								pGetUdpTable;
				 //  2006/09/10
				 PF_GetIfTable								pGetIfTable;
				 PF_SetIfEntry								pSetIfEntry;
				 PF_GetIfEntry								pGetIfEntry;

				 //  2007/01/20
				 PF_SendARP									pSendARP;

				 //  2005/06/26
				 PF_SHDeleteKey								pSHDeleteKey;
				 //  2005/12/23
				 PF_mciSendCommand							pmciSendCommand;
				 //  2005/12/25
				 PF_UuidFromString							pUuidFromString;

				 //  2005/07/03
				 PF_NtQueryInformationProcess				pNtQueryInformationProcess;
				 PF_NtQuerySystemInformation				pNtQuerySystemInformation;
				 
				 //  2006/04/13
				 PF_EnumProcessModules						pEnumProcessModules;
				 PF_GetModuleFileNameExW					pGetModuleFileNameExW;
				 PF_EnumProcesses							pEnumProcesses;
				 
				 //  2007/02/10, wtsapi32.dll
				 //  PF_WTSSendMessageA							pWTSSendMessageA;							//  2007/02/10
				 PF_WTSSendMessageW							pWTSSendMessageW;							//  2007/02/10
				 PF_WTSRegisterSessionNotification			pWTSRegisterSessionNotification;			//  2007/02/27
				 PF_WTSUnRegisterSessionNotification		pWTSUnRegisterSessionNotification;			//  2007/02/27

				 //  2007/02/28
				 PF_CreateEnvironmentBlock					pCreateEnvironmentBlock;					//  2007/02/28
				 PF_DestroyEnvironmentBlock					pDestroyEnvironmentBlock;

				 //  2011/10/04
				 PF_MessageBoxTimeoutW						pMessageBoxTimeoutW;

}		QWM_DYN_LIB;	

//  2007/01/21， 为了其他模块的调用方便，将下面的函数说明放入qnmCommProc.h中
//  int InitDynamicLibraries(void);	  
//  int KillDynamicLibraries(void);

BOOL  bSetupApiOk( QWM_DYN_LIB  *  pDynLibParam );
BOOL  bIpHlpApiOk( QWM_DYN_LIB  *  pDynLibParam );
BOOL  bShlwApiOk( QWM_DYN_LIB  *  pDynLibParam );



#endif