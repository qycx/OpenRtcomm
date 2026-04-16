
#ifndef __QYCHK_H__
#define __QYCHK_H__	/* { */

#define DEFAULT_AWM_CHKED_METHOD		0

#define MAX_DIGEST_LEN					256
#define DEFAULT_DIGEST_LEN				16

// 需要校验的程序总数
#define AWM_TOTAL_FILES					3


#if MAX_DIGEST_LEN < DEFAULT_DIGEST_LEN
 #error MAX_DIGEST can't be less than DEFAULT_DIGEST_LEN
#endif


#define AWM_CHK_FILE_STATE_UNKNOWN	-1
#define AWM_CHK_FILE_NOT_EXISTS		-2
#define AWM_CHK_FILE_INVALID		-3
#define AWM_CHK_FILE_OK				1

#define AWM_ACCESS_ALL	0x1f01ff
#define AWM_ACCESS_RX	0x1200a9
#define AWM_ACCESS_RW	(  FILE_GENERIC_READ | FILE_GENERIC_WRITE )

#define SZ_INDENT_BUF 80
#define PERR(api) printf("%s: Error %d from %s on line %d\n",  \
    __FILE__, GetLastError(), api, __LINE__);

typedef struct __awm_chked_file_t {
	
	char path[2048];
	char fileName[256];
	char fullPathName[2048];

	HFILE hFile;
	unsigned int size;
	// int chkedVal;
	
	char digest[MAX_DIGEST_LEN];
	int digestLen;

	int chkedMethod;

} AWM_CHKED_FILE;


typedef struct __awm_chk_t {

	int iPlatformId;

	struct __gsids_t {
		PSID psidDomainUserAdminSid;
		PSID psidDomainGroupAdminsSid;
		PSID psidDomainGroupUsersSid;
		PSID psidDomainAliasAdminsSid;
		PSID psidDomainAliasUsersSid;
		PSID psidLocalSystemSid;			// SECURITY_LOCAL_SYSTEM_RID
		PSID psidDomainAliasSystemOpsSid;	// DOMAIN_ALIAS_RID_SYSTEM_OPS
		PSID psidSecurityWorldSid;			// SECURITY_WORLD_RID
	} gSids;
	
	
} AWM_CHK;

typedef struct __awm_script_access_t {
		BOOL bAdminsAccessAll;
		BOOL bSystemAccessAll;
		BOOL bEveryoneAccessRX;
		BOOL bEveryoneAccessRW;
} AWM_SCRIPT_ACCESS;


typedef enum _KINDS_OF_ACCESSMASKS_DECODED {
    FileAccessMask,
    ProcessAccessMask,
    WindowStationAccessMask,
    DesktopAccessMask,
    RegKeyAccessMask,
    ServiceAccessMask,
    DefaultDaclInAccessTokenAccessMask
} KINDS_OF_ACCESSMASKS_DECODED, * PKINDS_OF_ACCESSMASKS_DECODED;

// These hold the well-known SIDs

extern PSID psidNullSid;
extern PSID psidWorldSid;
extern PSID psidLocalSid;
extern PSID psidCreatorOwnerSid;
extern PSID psidCreatorGroupSid;
extern PSID psidNtAuthoritySid;
extern PSID psidDialupSid;
extern PSID psidNetworkSid;
extern PSID psidBatchSid;
extern PSID psidInteractiveSid;
extern PSID psidLogonIdsSid; // But the X and Y values are bogus at first!!! (See below)
extern PSID psidServiceSid;
extern PSID psidLocalSystemSid;
extern PSID psidBuiltinDomainSid;


int awmChkAce( void *pAC1, ACCESS_ALLOWED_ACE *paaAllowedAce, KINDS_OF_ACCESSMASKS_DECODED kamKindOfMask );
BOOL DoOneFileOrDir(LPTSTR lpszFullName);
void DisplayLastError( LPSTR szAPI );
BOOL SIDStringName(PSID psidSID, LPTSTR lpszSIDStringName);
int awmChkMask( ACCESS_MASK amMask, LPTSTR lpszOldIndent, KINDS_OF_ACCESSMASKS_DECODED kamKindOfMask );
VOID InitializeWellKnownSIDs(VOID);
void awmLockAndChkFile( AWM_CHK *pAC, AWM_CHKED_FILE *p, int chkedMethod, int *piState );
extern "C" int showHint( char *hint, char *caption, char type );
void awmUnlockFile( AWM_CHKED_FILE *p );
int getChkedVal( char *fileName, char *digest );
BOOL bChkACEsAsAppropriate(PSECURITY_DESCRIPTOR psdFileSD, LPTSTR  lpszFullName, AWM_SCRIPT_ACCESS *pASA );
BOOL bAddACESAsNeeded( PSECURITY_DESCRIPTOR psdFileSD, LPTSTR lpszFullName, AWM_SCRIPT_ACCESS *pASA );



#ifdef __cplusplus
 extern "C" {
#endif




int initQyChk( AWM_CHK *p );
void exitQyChk( AWM_CHK *p );
void qyChkLogFile( AWM_CHK *pAC, char *fullPathName, int *piState );
BOOL bPreDoOneLogFileOrDir( LPTSTR lpszFullName );
BOOL bChkLogACEsAsAppropriate(PSECURITY_DESCRIPTOR psdFileSD, LPTSTR  lpszFullName, AWM_SCRIPT_ACCESS *pASA );
BOOL DoOneLogFileOrDir(LPTSTR lpszFullName);
int awmChkLogMask( ACCESS_MASK amMask, LPTSTR lpszOldIndent, KINDS_OF_ACCESSMASKS_DECODED kamKindOfMask );
int awmChkLogAce( void *pAC1, ACCESS_ALLOWED_ACE *paaAllowedAce, KINDS_OF_ACCESSMASKS_DECODED kamKindOfMask );
BOOL DeleteLogACEsAsAppropriate(PSECURITY_DESCRIPTOR psdFileSD, LPTSTR  lpszFullName );
BOOL bAddLogACESAsNeeded( PSECURITY_DESCRIPTOR psdFileSD, LPTSTR lpszFullName, AWM_SCRIPT_ACCESS *pASA );
BOOL LookupSIDName(PSID psidSID, LPTSTR lpszOldIndent);




#ifdef __cplusplus
 }
#endif



#endif /* } */

