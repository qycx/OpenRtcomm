

#include <windows.h>

#include "qyCommon.h"
#include "qyChk.h"
#include "qyChkCommon.h"


#define PMSG(msg) printf("%s line %d: %s\n",  \
    __FILE__, __LINE__, msg);



#define PrintAppStyleAPIError(ApiTxt,MsgTxt) {                     \
  DWORD dwLastError;                                               \
  dwLastError = GetLastError();                                    \
  switch (dwLastError)                                             \
  { case ERROR_FILE_NOT_FOUND :                                    \
      printf("\nFile not found (%s) line %d",MsgTxt,__LINE__);     \
      break;                                                       \
    case ERROR_INVALID_NAME   :                                    \
      printf("\nInvalid name (%s) line %d",MsgTxt,__LINE__);       \
      break;                                                       \
    case ERROR_PATH_NOT_FOUND :                                    \
      printf("\nError path not found (%s) line %d",MsgTxt,__LINE__); \
      break;                                                       \
    case ERROR_SHARING_VIOLATION :                                 \
      printf("\nSharing violation - shut down net and/or stop other sessions (%s) line %d",MsgTxt,__LINE__); \
      break;                                                       \
    case ERROR_ACCESS_DENIED  :                                    \
      printf("\nAccess denied (%s) line %d",MsgTxt,__LINE__);      \
      break;                                                       \
    default                   :                                    \
      printf("\n" #ApiTxt " - unexpected return code=%d (%s) line %d",dwLastError,MsgTxt,__LINE__); \
      break;                                                       \
  }                                                                \
  }

/****************************************************************************\
* FUNCTION PROTOTYPES
\****************************************************************************/

BOOL DoMatchingFilesInOneDir(HANDLE          hFound,
                             WIN32_FIND_DATA ffdFoundData);
BOOL DoAllDirsInOneDir(char *FilePattern);
BOOL GetFullFileOrDirName(LPTSTR lpszFileName);
BOOL DoOneFileOrDir(LPTSTR lpszFullName);
BOOL TakeOwnershipIfAppropriate(PSECURITY_DESCRIPTOR psdFileSD,
                                LPTSTR  lpszFullName);
BOOL DeleteACEsAsAppropriate   (PSECURITY_DESCRIPTOR psdFileSD,
                                LPTSTR  lpszFullName);
BOOL GetProcessSid(VOID);
BOOL CrackArgs(UINT argc, char *argv[]);
VOID DisplayHelp(VOID);

// These hold the well-known SIDs

PSID psidNullSid;
PSID psidWorldSid;
PSID psidLocalSid;
PSID psidCreatorOwnerSid;
PSID psidCreatorGroupSid;
PSID psidNtAuthoritySid;
PSID psidDialupSid;
PSID psidNetworkSid;
PSID psidBatchSid;
PSID psidInteractiveSid;
PSID psidLogonIdsSid; // But the X and Y values are bogus at first!!! (See below)
PSID psidServiceSid;
PSID psidLocalSystemSid;
PSID psidBuiltinDomainSid;


void *gpAwmChk = NULL;


 BOOL bPreDoOneFileOrDir( LPTSTR lpszFullName )
{	 
  #define				SZ_REL_SD_BUF 8096
  #define               SZ_ABS_SD_BUF  500
  #define               SZ_DACL_BUF    500
  #define               SZ_SACL_BUF    500
  #define               SZ_SID_OWN_BUF 500
  #define               SZ_SID_PG_BUF  500
  UCHAR					ucBuf             [SZ_REL_SD_BUF];
  UCHAR                ucBufAbs          [SZ_ABS_SD_BUF];
  UCHAR                ucBufDacl         [SZ_DACL_BUF];
  UCHAR                ucBufSacl         [SZ_SACL_BUF];
  UCHAR                ucBufCtrl         [sizeof(PSECURITY_DESCRIPTOR_CONTROL)];
  UCHAR                ucBufSidOwn       [SZ_SID_OWN_BUF];
  UCHAR                ucBufSidPG        [SZ_SID_PG_BUF];
  DWORD                dwSDLength       = SZ_REL_SD_BUF;
  DWORD                dwDACLLength     = SZ_DACL_BUF;
  DWORD                dwSACLLength     = SZ_SACL_BUF;
  DWORD                dwSidOwnLength   = SZ_SID_OWN_BUF;
  DWORD                dwSidPGLength    = SZ_SID_PG_BUF;
  DWORD                dwSDLengthNeeded;
  PSECURITY_DESCRIPTOR psdSrelFileSD    = (PSECURITY_DESCRIPTOR)&ucBuf;
  PSECURITY_DESCRIPTOR psdAbsFileSD     = (PSECURITY_DESCRIPTOR)&ucBufAbs;
  PSECURITY_DESCRIPTOR_CONTROL psdcCtrl = (PSECURITY_DESCRIPTOR_CONTROL)&ucBufCtrl;
  PACL                 paclDacl         = (PACL)&ucBufDacl;
  PACL                 paclSacl         = (PACL)&ucBufSacl;
  PSID                 psidSidOwn       = (PSID)&ucBufSidOwn;
  PSID                 psidSidPG        = (PSID)&ucBufSidPG;
  BOOL                 bDaclPresent;
  BOOL                 bDaclDefaulted;
  BOOL                 bSaclPresent;
  BOOL                 bSaclDefaulted;
  BOOL                 bSDSelfRelative;
  DWORD                dwRevision;
  
  if (!GetFullFileOrDirName(lpszFullName))
    return(FALSE);

  /**************************************************************************\
  *
  * Now the input argument's name is accurate:  it is expanded and lower-case
  *
  \**************************************************************************/

  printf("\nChecking %s",lpszFullName);

  if (!GetFileSecurity(lpszFullName,
         (SECURITY_INFORMATION)( DACL_SECURITY_INFORMATION ),
         psdSrelFileSD,
         dwSDLength,
         (LPDWORD)&dwSDLengthNeeded))
  { 
	  qyDisplayLastError( "KK" );
	  PERR("GetFileSecurity");    
	  return(FALSE);
  }
  
  /**************************************************************************\
  *
  * This validity check is here for demonstration pruposes.  It's not likely a
  *   real app would need to check the validity of this returned SD.  The
  *   validity check APIs are more intended to check validity after app code
  *   has manipulated the structure and is about to hand it back to the system
  *
  \**************************************************************************/

  if (!IsValidSecurityDescriptor(psdSrelFileSD))
  { PERR("IsValidSecurityDescriptor said bad SD");
    return(FALSE);
  }

  /**************************************************************************\
  *
  *  Build File SD in absolute format for potential later modification
  *
  *  First Initialize a new SD, which is by definition in absolute format
  *
  *  Then Set in the fields from the relative format SD we just fetched
  *
  \**************************************************************************/

  if (!InitializeSecurityDescriptor(psdAbsFileSD,
                 SECURITY_DESCRIPTOR_REVISION))
  { PERR("InitializeSecurityDescriptor");
    return FALSE;
  }

  /**************************************************************************\
  *
  * Get Control from relative format File SD
  *
  * This control info isn't much queried in the code that follows, as the
  *   Get/Set calls are more convienent in this case, but it does give us a
  *   change to verify that the SD is in relative format
  *
  \**************************************************************************/

  if (!GetSecurityDescriptorControl(psdSrelFileSD,
          psdcCtrl,
          &dwRevision))
  { PERR("GetSecurityDescriptorControl");
    return FALSE;
  }

  bSDSelfRelative = (SE_SELF_RELATIVE & *psdcCtrl);

  /**************************************************************************\
  *
  * Set DACL into absolute format File SD
  *
  * Note that it is possible that a NULL DACL has been explictly specified.
  *   If so the Get/Set call pair will correctly map that into the absolute
  *   format SD
  *
  * The next if statement isn't necessary, it simply shows the relationship
  *   between SE_DACL_PRESENT and SE_DACL_DEFAULTED, and lets you trace
  *   through with the debugger
  *
  \**************************************************************************/

  if (bDaclPresent = (SE_DACL_PRESENT   & *psdcCtrl))
  {                // SE_DACL_DEFAULTED ignored if SE_DACL_PRESENT not set
    bDaclDefaulted = (SE_DACL_DEFAULTED & *psdcCtrl);
  }
  else
  { // No DACL at all
  }

  if (!GetSecurityDescriptorDacl(psdSrelFileSD,
          &bDaclPresent,      // fDaclPresent flag
          &paclDacl,
          &bDaclDefaulted))   // is/is not a default DACL
  { PERR("GetSecurityDescriptorDacl");
    return FALSE;
  }
  if (!SetSecurityDescriptorDacl(psdAbsFileSD,
          bDaclPresent,       // fDaclPresent flag
          paclDacl,
          bDaclDefaulted))    // is/is not a default DACL
  { PERR("SetSecurityDescriptorDacl");
    return FALSE;
  }

  /**************************************************************************\
  *
  * Set SACL into absolute format File SD
  *
  * Note that it is possible that a NULL SACL has been explictly specified.
  *   If so the Get/Set call pair will correctly map that into the absolute
  *   format SD
  *
  * The next if statement isn't necessary, it simply shows the relationship
  *   between SE_SACL_PRESENT and SE_SACL_DEFAULTED, and lets you trace
  *   through with the debugger
  *
  \**************************************************************************/

  if (bSaclPresent = (SE_SACL_PRESENT   & *psdcCtrl))
  {                // SE_SACL_DEFAULTED ignored if SE_SACL_PRESENT not set
    bSaclDefaulted = (SE_SACL_DEFAULTED & *psdcCtrl);
  }
  else
  { // No SACL at all
  }

  if (!GetSecurityDescriptorSacl(psdSrelFileSD,
          &bSaclPresent,      // fSaclPresent flag
          &paclSacl,
          &bSaclDefaulted))   // is/is not a default SACL
  { PERR("GetSecurityDescriptorSacl");
    return FALSE;
  }
  if (!SetSecurityDescriptorSacl(psdAbsFileSD,
          bSaclPresent,       // fSaclPresent flag
          paclSacl,
          bSaclDefaulted))    // is/is not a default SACL
  { PERR("SetSecurityDescriptorSacl");
    return FALSE;
  }
  
  if (!IsValidSecurityDescriptor(psdAbsFileSD))
  { PERR("IsValidSecurityDescriptor said bad SD");
    return(FALSE);
  }


  AWM_SCRIPT_ACCESS aSA;
  memset( &aSA, 0, sizeof( aSA ) );
  if ( !bChkACEsAsAppropriate( psdAbsFileSD, lpszFullName, &aSA ) )
	  return FALSE;
  if ( !bAddACESAsNeeded( psdAbsFileSD, lpszFullName, &aSA ) )
	  return FALSE;
  
  return(TRUE);

}

 BOOL DoOneFileOrDir(LPTSTR lpszFullName)
{
  #define                                 SZ_REL_SD_BUF 8096
  #define                                 SZ_ABS_SD_BUF  500
  #define                                 SZ_DACL_BUF    500
  #define                                 SZ_SACL_BUF    500
  #define                                 SZ_SID_OWN_BUF 500
  #define                                 SZ_SID_PG_BUF  500
  UCHAR                ucBuf             [SZ_REL_SD_BUF];
  UCHAR                ucBufAbs          [SZ_ABS_SD_BUF];
  UCHAR                ucBufDacl         [SZ_DACL_BUF];
  UCHAR                ucBufSacl         [SZ_SACL_BUF];
  UCHAR                ucBufCtrl         [sizeof(PSECURITY_DESCRIPTOR_CONTROL)];
  UCHAR                ucBufSidOwn       [SZ_SID_OWN_BUF];
  UCHAR                ucBufSidPG        [SZ_SID_PG_BUF];
  DWORD                dwSDLength       = SZ_REL_SD_BUF;
  DWORD                dwDACLLength     = SZ_DACL_BUF;
  DWORD                dwSACLLength     = SZ_SACL_BUF;
  DWORD                dwSidOwnLength   = SZ_SID_OWN_BUF;
  DWORD                dwSidPGLength    = SZ_SID_PG_BUF;
  DWORD                dwSDLengthNeeded;
  PSECURITY_DESCRIPTOR psdSrelFileSD    = (PSECURITY_DESCRIPTOR)&ucBuf;
  PSECURITY_DESCRIPTOR psdAbsFileSD     = (PSECURITY_DESCRIPTOR)&ucBufAbs;
  PSECURITY_DESCRIPTOR_CONTROL psdcCtrl = (PSECURITY_DESCRIPTOR_CONTROL)&ucBufCtrl;
  PACL                 paclDacl         = (PACL)&ucBufDacl;
  PACL                 paclSacl         = (PACL)&ucBufSacl;
  PSID                 psidSidOwn       = (PSID)&ucBufSidOwn;
  PSID                 psidSidPG        = (PSID)&ucBufSidPG;
  BOOL                 bDaclPresent;
  BOOL                 bDaclDefaulted;
  BOOL                 bSaclPresent;
  BOOL                 bSaclDefaulted;
  BOOL                 bSDSelfRelative;
  DWORD                dwRevision;
  
  if (!GetFullFileOrDirName(lpszFullName))
    return(FALSE);

  /**************************************************************************\
  *
  * Now the input argument's name is accurate:  it is expanded and lower-case
  *
  \**************************************************************************/
  
  if (!GetFileSecurity(lpszFullName,
         (SECURITY_INFORMATION)( DACL_SECURITY_INFORMATION ),
         psdSrelFileSD,
         dwSDLength,
         (LPDWORD)&dwSDLengthNeeded))
  { 
	  qyDisplayLastError( "KK" );
	  PERR("GetFileSecurity");    
	  return(FALSE);
  }
  
  /**************************************************************************\
  *
  * This validity check is here for demonstration pruposes.  It's not likely a
  *   real app would need to check the validity of this returned SD.  The
  *   validity check APIs are more intended to check validity after app code
  *   has manipulated the structure and is about to hand it back to the system
  *
  \**************************************************************************/

  if (!IsValidSecurityDescriptor(psdSrelFileSD))
  { PERR("IsValidSecurityDescriptor said bad SD");
    return(FALSE);
  }

  /**************************************************************************\
  *
  *  Build File SD in absolute format for potential later modification
  *
  *  First Initialize a new SD, which is by definition in absolute format
  *
  *  Then Set in the fields from the relative format SD we just fetched
  *
  \**************************************************************************/

  if (!InitializeSecurityDescriptor(psdAbsFileSD,
                 SECURITY_DESCRIPTOR_REVISION))
  { PERR("InitializeSecurityDescriptor");
    return FALSE;
  }

  /**************************************************************************\
  *
  * Get Control from relative format File SD
  *
  * This control info isn't much queried in the code that follows, as the
  *   Get/Set calls are more convienent in this case, but it does give us a
  *   change to verify that the SD is in relative format
  *
  \**************************************************************************/

  if (!GetSecurityDescriptorControl(psdSrelFileSD,
          psdcCtrl,
          &dwRevision))
  { PERR("GetSecurityDescriptorControl");
    return FALSE;
  }

  bSDSelfRelative = (SE_SELF_RELATIVE & *psdcCtrl);

  /**************************************************************************\
  *
  * Set DACL into absolute format File SD
  *
  * Note that it is possible that a NULL DACL has been explictly specified.
  *   If so the Get/Set call pair will correctly map that into the absolute
  *   format SD
  *
  * The next if statement isn't necessary, it simply shows the relationship
  *   between SE_DACL_PRESENT and SE_DACL_DEFAULTED, and lets you trace
  *   through with the debugger
  *
  \**************************************************************************/

  if (bDaclPresent = (SE_DACL_PRESENT   & *psdcCtrl))
  {                // SE_DACL_DEFAULTED ignored if SE_DACL_PRESENT not set
    bDaclDefaulted = (SE_DACL_DEFAULTED & *psdcCtrl);
  }
  else
  { // No DACL at all
  }

  if (!GetSecurityDescriptorDacl(psdSrelFileSD,
          &bDaclPresent,      // fDaclPresent flag
          &paclDacl,
          &bDaclDefaulted))   // is/is not a default DACL
  { PERR("GetSecurityDescriptorDacl");
    return FALSE;
  }
  if (!SetSecurityDescriptorDacl(psdAbsFileSD,
          bDaclPresent,       // fDaclPresent flag
          paclDacl,
          bDaclDefaulted))    // is/is not a default DACL
  { PERR("SetSecurityDescriptorDacl");
    return FALSE;
  }

  /**************************************************************************\
  *
  * Set SACL into absolute format File SD
  *
  * Note that it is possible that a NULL SACL has been explictly specified.
  *   If so the Get/Set call pair will correctly map that into the absolute
  *   format SD
  *
  * The next if statement isn't necessary, it simply shows the relationship
  *   between SE_SACL_PRESENT and SE_SACL_DEFAULTED, and lets you trace
  *   through with the debugger
  *
  \**************************************************************************/

  if (bSaclPresent = (SE_SACL_PRESENT   & *psdcCtrl))
  {                // SE_SACL_DEFAULTED ignored if SE_SACL_PRESENT not set
    bSaclDefaulted = (SE_SACL_DEFAULTED & *psdcCtrl);
  }
  else
  { // No SACL at all
  }

  if (!GetSecurityDescriptorSacl(psdSrelFileSD,
          &bSaclPresent,      // fSaclPresent flag
          &paclSacl,
          &bSaclDefaulted))   // is/is not a default SACL
  { PERR("GetSecurityDescriptorSacl");
    return FALSE;
  }
  if (!SetSecurityDescriptorSacl(psdAbsFileSD,
          bSaclPresent,       // fSaclPresent flag
          paclSacl,
          bSaclDefaulted))    // is/is not a default SACL
  { PERR("SetSecurityDescriptorSacl");
    return FALSE;
  }
  
  if (!IsValidSecurityDescriptor(psdAbsFileSD))
  { PERR("IsValidSecurityDescriptor said bad SD");
    return(FALSE);
  }


  if (!DeleteACEsAsAppropriate(psdAbsFileSD,lpszFullName)) {
	  debugLog( "DoOneFileOrDir( ): DeleteACEsAsAppropriate( ) failed." );
	  return(FALSE);
  }

  return(TRUE);
}

 BOOL bAddACESAsNeeded( PSECURITY_DESCRIPTOR psdFileSD, LPTSTR lpszFullName, AWM_SCRIPT_ACCESS *pASA )
{
	BOOL bRet = FALSE;
	AWM_CHK *pAC = ( AWM_CHK * )gpAwmChk;
	
	if ( !pASA->bAdminsAccessAll ) {
		if ( !bAddAccessRights( pAC->gSids.psidDomainAliasAdminsSid, AWM_ACCESS_ALL, lpszFullName ) ) {
			OutputDebugString( "bAddAccessRights( ) for ADMINS_ACCESS_ALL failed.\n" );
			debugLog( "bAddAccessRights( ) for ADMINS_ACCESS_ALL failed." );
			goto errLabel;
		}
		OutputDebugString( "bAddAccessRights( ) for ADMINS_ACCESS_ALL succeeded.\n" );
		debugLog( "bAddAccessRights( ) for ADMINS_ACCESS_ALL succeeded." );
	}


	if ( !pASA->bSystemAccessAll ) {
		if ( !bAddAccessRights( pAC->gSids.psidLocalSystemSid, AWM_ACCESS_ALL, lpszFullName ) ) {
			OutputDebugString( "bAddAccessRights( ) for SYSTEM_ACCESS_ALL failed.\n" );
			debugLog( "bAddAccessRights( ) for SYSTEM_ACCESS_ALL failed." );
			goto errLabel;
		}
		OutputDebugString( "bAddAccessRights( ) for SYSTEM_ACCESS_ALL succeeded.\n" );
		debugLog( "bAddAccessRights( ) for SYSTEM_ACCESS_ALL succeeded." );
	}

	if ( !pASA->bEveryoneAccessRX ) {
		if ( !bAddAccessRights( pAC->gSids.psidSecurityWorldSid, AWM_ACCESS_RX, lpszFullName ) ) {
			OutputDebugString( "bAddAccessRights( ) for EVERYONE_ACCESS_RX failed.\n" );
			debugLog( "bAddAccessRights( ) for EVERYONE_ACCESS_RX failed." );
			goto errLabel;
		}
		OutputDebugString( "bAddAccessRights( ) for EVERYONE_ACCESS_RX succeeded.\n" );
		debugLog( "bAddAccessRights( ) for EVERYONE_ACCESS_RX succeeded." );
	}

	bRet = TRUE;

errLabel:
	
	return bRet; 
		

}


 BOOL DeleteACEsAsAppropriate(PSECURITY_DESCRIPTOR psdFileSD, LPTSTR  lpszFullName )
{
  PACL                 paclFile;
  BOOL                 bHasACL;
  BOOL                 bOwnerDefaulted;
  DWORD                dwAcl_i;
  // DWORD                dwACEsDeletedBeforeNow;
  BOOL bAdminsAccessAll = FALSE;
  BOOL bEveryoneAccessRX = FALSE;
  BOOL bSystemAccessAll = FALSE;
  BOOL bDeletedAce = FALSE;

  ACL_SIZE_INFORMATION                      asiAclSize;
  DWORD                dwBufLength = sizeof(asiAclSize);
  ACCESS_ALLOWED_ACE   *paaAllowedAce;

  if (!GetSecurityDescriptorDacl(psdFileSD,
                                 (LPBOOL)&bHasACL,
                                 (PACL *)&paclFile,
                                 (LPBOOL)&bOwnerDefaulted))
  { PERR("GetSecurityDescriptorDacl");
    return(FALSE);
  }

  if (!bHasACL)  // No ACL to process, so OK, return
    return(TRUE);

  /**************************************************************************\
  *
  * This validity check is here for demonstration pruposes.  It's not likely a
  *   real app would need to check the validity of this returned ACL.  The
  *   validity check APIs are more intended to check validity after app code
  *   has manipulated the structure and is about to hand it back to the system
  *
  \**************************************************************************/

  if (!IsValidAcl(paclFile))
  { PERR("IsValidAcl said bad ACL!");
    return(FALSE);
  }

  if (!GetAclInformation(paclFile,
                         (LPVOID)&asiAclSize,
                         (DWORD)dwBufLength,
                         (ACL_INFORMATION_CLASS)AclSizeInformation))
  { PERR("GetAclInformation");
    return(FALSE);
  }

  // dwACEsDeletedBeforeNow = dwACEsDeleted;

  /**************************************************************************\
  *
  * We loop through in reverse order, because that's simpler, given that we
  *   potentially delete ACEs as we loop through.  If started at 0 and went
  *   up, if we deleted the 0th ACE, then the 1th ACE would become the 0th,
  *   and we'd have to check the 0th ACE again
  *
  \**************************************************************************/

  {
	  char buf[128];
	  sprintf( buf, "There are %d ace for the file [%s].\n", asiAclSize.AceCount, lpszFullName );
	  OutputDebugString( buf );
//	  debugLog( "DeleteACEsAsAppropriate( ): %s", buf );
  }

  for (dwAcl_i = asiAclSize.AceCount-1;  ((int)dwAcl_i) >= 0;  dwAcl_i--)
  {
    /************************************************************************\
    *
    * It doesn't matter for this sample that we don't yet know the ACE type,
    *   because they all start with the header field and that's what we need
    *
    \************************************************************************/

    if (!GetAce(paclFile,
                dwAcl_i,
                (LPVOID *)&paaAllowedAce))
    { PERR("GetAce");
      return(FALSE);
    }
	bDeletedAce = FALSE;

    /************************************************************************\
    *
    * There are only four Ace Types pre-defined, so this next check is
    *   redundant in a real app, but useful as a sanity check and a
    *   demonstration in a sample
    *
    \************************************************************************/

    if (!( (paaAllowedAce->Header.AceType == ACCESS_ALLOWED_ACE_TYPE)
         ||(paaAllowedAce->Header.AceType == ACCESS_DENIED_ACE_TYPE )
         ||(paaAllowedAce->Header.AceType == SYSTEM_AUDIT_ACE_TYPE  )
         ||(paaAllowedAce->Header.AceType == SYSTEM_ALARM_ACE_TYPE  )))
    { PERR("Invalid AceType");
      return(FALSE);
    }

    { // Find SID of ACE, check if acct deleted
#define                      SZ_ACCT_NAME_BUF 1000
      UCHAR        ucNameBuf      [SZ_ACCT_NAME_BUF];
      DWORD        dwNameLength  = SZ_ACCT_NAME_BUF;
#define                      SZ_DMN_NAME_BUF  1000
      UCHAR        ucDomainNmBuf  [SZ_DMN_NAME_BUF];
      DWORD        dwDNameLength = SZ_DMN_NAME_BUF;
      SID_NAME_USE peAcctNameUse;
      DWORD        dwLastError   = NO_ERROR;

      /**********************************************************************\
      *
      * This validity check is here for demonstration pruposes.  It's not
      *   likely a real app would need to check the validity of the SID
      *   contained in the returned ACL.  The validity check APIs are more
      *   intended to check validity after app code has manipulated the
      *   structure and is about to hand it back to the system
      *
      \**********************************************************************/

      if (!IsValidSid((PSID)&(paaAllowedAce->SidStart)))
      { PERR("IsValidSid said bad SID!");
        return(FALSE);
      }

      if (!LookupAccountSid
             ((LPTSTR)"",         // Look on local machine
             (PSID)&(paaAllowedAce->SidStart),
             (LPTSTR)&ucNameBuf,
             (LPDWORD)&dwNameLength,
             (LPTSTR)&ucDomainNmBuf,
             (LPDWORD)&dwDNameLength,
             (PSID_NAME_USE)&peAcctNameUse))
      { dwLastError = GetLastError();
        if (ERROR_NONE_MAPPED != dwLastError)
        { PERR("LookupAccountSID");
          return(FALSE);
        }
      }
	  { 
		  char tmpBuf[1024];
	  
		  sprintf( tmpBuf, "Name of sid is %s\n", ucNameBuf );
		  OutputDebugString( tmpBuf );
	  }

	  if ( awmChkAce( gpAwmChk, paaAllowedAce, FileAccessMask ) ) {
		  if ( !DeleteAce( paclFile, dwAcl_i ) ) {
				OutputDebugString( "DeleteAce( ) failed." );
				debugLog( "DeleteAce( ) failed." );
				return FALSE;
		  }
		  OutputDebugString( "DeleteAce( ) succeeded." );
		  debugLog( "DeleteAce( ) succeeded." );
		  bDeletedAce = TRUE;
	  }
    }

  }	// 遍历整个访问列表


  {
  
    if (!IsValidAcl(paclFile))
    { PERR("IsValidAcl said bad ACL!");
      return(FALSE);
    }

    /************************************************************************\
    *
    * Modify the SD in virtual memory
    *
    \************************************************************************/

    if (!SetSecurityDescriptorDacl
           (psdFileSD,
            TRUE,                 // Yes, set the DACL
            paclFile,
            FALSE))               // New DACL explicitly specified
    { PERR("SetSecurityDescriptorDacl");
      return(FALSE);
    }

    /************************************************************************\
    *
    * This validity check is something a real app might actually like to do.
    *   We manupulated the SD, so before we write it back out to the file
    *   system, a check is worth considering
    *
    \************************************************************************/

    if (!IsValidSecurityDescriptor(psdFileSD))
    { PERR("IsValidSecurityDescriptor said bad SD");
      return(FALSE);
    }

    /************************************************************************\
    *
    * Modify the SD on the hard disk
    *
    \************************************************************************/

    if (!SetFileSecurity
           (lpszFullName,
            (SECURITY_INFORMATION)DACL_SECURITY_INFORMATION,
            psdFileSD))
    { PERR("SetFileSecurity");
      return(FALSE);
    }

    printf(" - edited ACL");
  }

  
  return(TRUE);

}

  extern "C" int initQyChk( AWM_CHK *p )
{
	int iErr = -1;
	SID_IDENTIFIER_AUTHORITY SystemSidAuthority= SECURITY_NT_AUTHORITY;
	SID_IDENTIFIER_AUTHORITY siaWorld = SECURITY_WORLD_SID_AUTHORITY;

	debugLog( "initAwmChk( ) enters." );

	if ( !bAsrGetSystemVersion( &p->iPlatformId ) ) {
		goto errLabel;
	}

	if ( p->iPlatformId != PLATFORM_NT && p->iPlatformId != PLATFORM_WIN2K ) {
		goto errLabel;
	}
	
	memset( &p->gSids, 0, sizeof( p->gSids ) );

	InitializeWellKnownSIDs( );
	
	if ( !AllocateAndInitializeSid( &SystemSidAuthority, 2, 
				SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_USER_RID_ADMIN,
				0, 0, 0, 0, 0, 0, &p->gSids.psidDomainUserAdminSid ) )
	{
		goto errLabel;
	}
	if ( !AllocateAndInitializeSid( &SystemSidAuthority, 2, 
				SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_GROUP_RID_ADMINS,
				0, 0, 0, 0, 0, 0, &p->gSids.psidDomainGroupAdminsSid ) )
	{
		goto errLabel;
	}
	if ( !AllocateAndInitializeSid( &SystemSidAuthority, 2, 
				SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_GROUP_RID_USERS,
				0, 0, 0, 0, 0, 0, &p->gSids.psidDomainGroupUsersSid ) )
	{
		goto errLabel;
	}
	if ( !AllocateAndInitializeSid( &SystemSidAuthority, 2, 
				SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,
				0, 0, 0, 0, 0, 0, &p->gSids.psidDomainAliasAdminsSid ) )
	{
		goto errLabel;
	}
	if ( !AllocateAndInitializeSid( &SystemSidAuthority, 2, 
				SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_USERS,
				0, 0, 0, 0, 0, 0, &p->gSids.psidDomainAliasUsersSid ) )
	{
		goto errLabel;
	}
	if ( !AllocateAndInitializeSid( &SystemSidAuthority, 1, 
				SECURITY_LOCAL_SYSTEM_RID, 1,
				0, 0, 0, 0, 0, 0, &p->gSids.psidLocalSystemSid ) )
	{
		goto errLabel;
	}

	
	SystemSidAuthority = siaWorld;
	if ( !AllocateAndInitializeSid( &siaWorld, 1, 
				SECURITY_WORLD_RID, 1,
				0, 0, 0, 0, 0, 0, &p->gSids.psidSecurityWorldSid ) )
	{
		goto errLabel;
	}

	gpAwmChk = p;	// 这个全局量在这里设置
	
	debugLog( "Initializing well-known sids finished." );
	
	iErr = 0;

errLabel:

	if ( iErr ) {
		
		if ( p->gSids.psidDomainUserAdminSid ) {
			FreeSid( p->gSids.psidDomainUserAdminSid ); p->gSids.psidDomainUserAdminSid = NULL; 
		}
		if ( p->gSids.psidDomainGroupAdminsSid ) {
			FreeSid( p->gSids.psidDomainGroupAdminsSid ); p->gSids.psidDomainGroupAdminsSid = NULL;
		}
		if ( p->gSids.psidDomainGroupUsersSid ) {
			FreeSid( p->gSids.psidDomainGroupUsersSid ); p->gSids.psidDomainGroupUsersSid = NULL;
		}
		if ( p->gSids.psidDomainAliasAdminsSid ) {
			FreeSid( p->gSids.psidDomainAliasAdminsSid ); p->gSids.psidDomainAliasAdminsSid = NULL;
		}
		if ( p->gSids.psidDomainAliasUsersSid ) {
			FreeSid( p->gSids.psidDomainAliasUsersSid ); p->gSids.psidDomainAliasUsersSid = NULL;
		}
		if ( p->gSids.psidDomainAliasSystemOpsSid ) {
			FreeSid( p->gSids.psidDomainAliasSystemOpsSid ); p->gSids.psidDomainAliasSystemOpsSid = NULL;
		}

	}

	debugLog( "initAwmChk( ) leaves." );

	return iErr;

}

 extern "C" void exitQyChk( AWM_CHK *p )
{
	BOOL bRet = TRUE;
		 
	if ( p->gSids.psidDomainUserAdminSid ) {
		FreeSid( p->gSids.psidDomainUserAdminSid ); p->gSids.psidDomainUserAdminSid = NULL; 
	}
	if ( p->gSids.psidDomainGroupAdminsSid ) {
		FreeSid( p->gSids.psidDomainGroupAdminsSid ); p->gSids.psidDomainGroupAdminsSid = NULL;
	}
	if ( p->gSids.psidDomainGroupUsersSid ) {
		FreeSid( p->gSids.psidDomainGroupUsersSid ); p->gSids.psidDomainGroupUsersSid = NULL;
	}
	if ( p->gSids.psidDomainAliasAdminsSid ) {
		FreeSid( p->gSids.psidDomainAliasAdminsSid ); p->gSids.psidDomainAliasAdminsSid = NULL;
	}
	if ( p->gSids.psidDomainAliasUsersSid ) {
		FreeSid( p->gSids.psidDomainAliasUsersSid ); p->gSids.psidDomainAliasUsersSid = NULL;
	}
	if ( p->gSids.psidDomainAliasSystemOpsSid ) {
		FreeSid( p->gSids.psidDomainAliasSystemOpsSid ); p->gSids.psidDomainAliasSystemOpsSid = NULL;
	}

	if ( p->gSids.psidSecurityWorldSid ) {
		FreeSid( p->gSids.psidSecurityWorldSid ); p->gSids.psidSecurityWorldSid = NULL;
	}
	
	gpAwmChk = NULL;	// 全局变量在这里复位
	
	return;

}


	 

  extern "C" BOOL LookupSIDName(PSID psidSID, LPTSTR lpszOldIndent)
{
  UCHAR        ucIndentBuf    [SZ_INDENT_BUF]    = "";
//  #define                      SZ_ACCT_NAME_BUF  60
  UCHAR        ucNameBuf      [SZ_ACCT_NAME_BUF] = "";
  DWORD        dwNameLength  = SZ_ACCT_NAME_BUF;
//  #define                      SZ_DMN_NAME_BUF   60
  UCHAR        ucDomainNmBuf  [SZ_DMN_NAME_BUF]  = "";
  DWORD        dwDNameLength = SZ_DMN_NAME_BUF;
  #define                      SZ_SID_STRING_BUF 150
  UCHAR        ucSIDStringBuf [SZ_SID_STRING_BUF] = "";
  SID_NAME_USE peAcctNameUse = SidTypeInvalid;
  DWORD        dwLookupStatus;
  BOOL         bGotBadLookupThatIsNotLocalLogonSID;

  strcpy( ( char * )ucIndentBuf,lpszOldIndent);
  strcat( ( char * )ucIndentBuf,"  ");

  if (!IsValidSid(psidSID))
  { PERR("IsValidSid");
    return(FALSE);
  }

  if (!SIDStringName(psidSID, ( char * )ucSIDStringBuf))
  { PERR("SIDStringName");
    return(FALSE);
  }

  if (!LookupAccountSid(
         (LPTSTR)"",         // Look on local machine
         psidSID,
         (LPTSTR)&ucNameBuf,
         (LPDWORD)&dwNameLength,
         (LPTSTR)&ucDomainNmBuf,
         (LPDWORD)&dwDNameLength,
         (PSID_NAME_USE)&peAcctNameUse))
  {
    dwLookupStatus = GetLastError();

    /************************************************************************\
    *
    * Got a bad Lookup, so check is SID the Local Logon SID?
    *
    * The problem is that LookupAccountSid api will find all the well-known
    *   SIDs except the Local Logon SID.  The last two sub-authorities are
    *   always different, so to check to see if the SID we're looking at is
    *   the Local Logon SID, we take the psidLogonIdsSid variable we built at
    *   initialization time, and blast into it's last two sub-authorities the
    *   last two sub-authorities that we have.  Then compare for EqualSid
    *
    \************************************************************************/

    // Must have same number of sub authorities

    bGotBadLookupThatIsNotLocalLogonSID = FALSE;  // Assume the best :)

    if ( ( *(GetSidSubAuthorityCount(psidLogonIdsSid))) !=
         ( *(GetSidSubAuthorityCount(psidSID        )))    )
    { // Not same number of sub-authorities, so can't be a match
      bGotBadLookupThatIsNotLocalLogonSID = TRUE;
    }
    else
    {
      // Force the last two sub-authorities to match
      *(GetSidSubAuthority( psidLogonIdsSid, 1 )) =
      *(GetSidSubAuthority( psidSID        , 1 ));
      *(GetSidSubAuthority( psidLogonIdsSid, 2 )) =
      *(GetSidSubAuthority( psidSID        , 2 ));

      /**********************************************************************\
      *
      * EqualPrefixSid could be used instead if we want to blast in all but
      *   the last sub-authority.  For demonstration purposes, as long as we
      *   did one of the two previous assignment statements, we may as well to
      *   the other and use EqualSID
      *
      \**********************************************************************/

      if (EqualSid(psidSID,psidLogonIdsSid))
      { ; // debugLog("\n%sSID is the Local Logon SID   %s",ucIndentBuf,ucSIDStringBuf);
      }
      else
      { bGotBadLookupThatIsNotLocalLogonSID = TRUE;
      }
    }
    if (bGotBadLookupThatIsNotLocalLogonSID)
    {
      /**********************************************************************\
      *
      * ERROR_NONE_MAPPED means account unknown.  RegEdt32.exe will show
      *   1332-error-type accounts as Account Unknown, so we will also
      *
      \**********************************************************************/

      if (ERROR_NONE_MAPPED == dwLookupStatus)
      { ; // debugLog("\n%sSID domain == %s, Name == %s    (Account Unknown)  %s",ucIndentBuf,ucDomainNmBuf,ucNameBuf,ucSIDStringBuf);
      }
      else
      { SetLastError(dwLookupStatus);
        PERR("LookupAccountSid");
        return(FALSE);
      }
    }
  }
  else
  { // Got good Lookup, so SID Is NOT the Local Logon SID
    // debugLog("\n%sSID domain == %s, Name == %s   %s",ucIndentBuf,ucDomainNmBuf,ucNameBuf,ucSIDStringBuf);

    /************************************************************************\
    *
    * For demonstration purposes see which well-known SID it might be
    * For demonstration purposes do a silly search demonstrating
    *   no two well-known SIDs are equal
    *
    \************************************************************************/

    if (EqualSid(psidSID,psidNullSid))
    { ;	// debugLog("\n%sSID is the Null SID",ucIndentBuf);
    }
    if (EqualSid(psidSID,psidWorldSid))
    { ; // debugLog("\n%sSID is the World SID",ucIndentBuf);
    }
    if (EqualSid(psidSID,psidLocalSid))
    { ; // debugLog("\n%sSID is the Local SID",ucIndentBuf);
    }
    if (EqualSid(psidSID,psidCreatorOwnerSid))
    { ; // debugLog("\n%sSID is the CreatorOwner SID",ucIndentBuf);
    }
    if (EqualSid(psidSID,psidCreatorGroupSid))
    { ; // debugLog("\n%sSID is the CreatorGroup SID",ucIndentBuf);
    }
    if (EqualSid(psidSID,psidNtAuthoritySid))
    { ; // debugLog("\n%sSID is the NtAuthority SID",ucIndentBuf);
    }
    if (EqualSid(psidSID,psidDialupSid))
    { ; // debugLog("\n%sSID is the DialUp SID",ucIndentBuf);
    }
    if (EqualSid(psidSID,psidNetworkSid))
    { ; // debugLog("\n%sSID is the Network SID",ucIndentBuf);
    }
    if (EqualSid(psidSID,psidBatchSid))
    { ; // debugLog("\n%sSID is the Batch SID",ucIndentBuf);
    }
    if (EqualSid(psidSID,psidInteractiveSid))
    { ; // debugLog("\n%sSID is the Interactive SID",ucIndentBuf);
    }
    if (EqualSid(psidSID,psidServiceSid))
    { ; // debugLog("\n%sSID is the Service SID",ucIndentBuf);
    }
    if (EqualSid(psidSID,psidLocalSystemSid))
    { ; // debugLog("\n%sSID is the LocalSystem SID",ucIndentBuf);
    }
    if (EqualSid(psidSID,psidBuiltinDomainSid))
    { ; // debugLog("\n%sSID is the Builtin Domain SID",ucIndentBuf);
    }
  }

  switch (peAcctNameUse)
  { case                      SidTypeUser           :
      // debugLog("\n%sSID type is SidTypeUser"          ,ucIndentBuf);
      break;
    case                      SidTypeGroup          :
      // debugLog("\n%sSID type is SidTypeGroup"         ,ucIndentBuf);
      break;
    case                      SidTypeDomain         :
      // debugLog("\n%sSID type is SidTypeDomain"        ,ucIndentBuf);
      break;
    case                      SidTypeAlias          :
      // debugLog("\n%sSID type is SidTypeAlias"         ,ucIndentBuf);
      break;
    case                      SidTypeWellKnownGroup :
      // debugLog("\n%sSID type is SidTypeWellKnownGroup",ucIndentBuf);
      break;
    case                      SidTypeDeletedAccount :
      // debugLog("\n%sSID type is SidTypeDeletedAccount",ucIndentBuf);
      break;
    case                      SidTypeInvalid        :
      // debugLog("\n%sSID type is SidTypeInvalid"       ,ucIndentBuf);
      break;
    case                      SidTypeUnknown        :
      // debugLog("\n%sSID type is SidTypeUnknown"       ,ucIndentBuf);
      break;
    default                   :
      // debugLog("\n%sSID type is IMPOSSIBLE!!!!  Run debugger, see value!",ucIndentBuf);
      break;
  }
  return TRUE;
}


BOOL SIDStringName(PSID psidSID, LPTSTR lpszSIDStringName)
{
  /**************************************************************************\
  *
  * Unfortunately there is no api to return the SID Revision, and the number
  *   of bytes in the Identifier Authority must be expressed as a define
  *   (since the == operator won't operate on structures so mempcy has to be
  *   used for the identifier authority compares)
  *
  \**************************************************************************/

  DWORD dwNumSubAuthorities;
  DWORD dwLen;
  DWORD dwSubAuthorityI;
  #define BytesInIdentifierAuthority  6
  SID_IDENTIFIER_AUTHORITY siaSidAuthority;
  SID_IDENTIFIER_AUTHORITY siaNullSidAuthority    = SECURITY_NULL_SID_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY siaWorldSidAuthority   = SECURITY_WORLD_SID_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY siaLocalSidAuthority   = SECURITY_LOCAL_SID_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY siaCreatorSidAuthority = SECURITY_CREATOR_SID_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY siaNtAuthority         = SECURITY_NT_AUTHORITY;

  dwLen = sprintf(lpszSIDStringName,"S-%d-",SID_REVISION);

  if (SID_REVISION != ((PISID)psidSID)->Revision)
  { dwLen += sprintf(lpszSIDStringName+dwLen,"bad_revision==%d",((PISID)psidSID)->Revision);
  }

  siaSidAuthority = *(GetSidIdentifierAuthority(psidSID));

  if      (0==memcmp(&siaSidAuthority,&siaNullSidAuthority   ,BytesInIdentifierAuthority))
  { dwLen += sprintf(lpszSIDStringName+dwLen,"0");
  }
  else if (0==memcmp(&siaSidAuthority,&siaWorldSidAuthority  ,BytesInIdentifierAuthority))
  { dwLen += sprintf(lpszSIDStringName+dwLen,"1");
  }
  else if (0==memcmp(&siaSidAuthority,&siaLocalSidAuthority  ,BytesInIdentifierAuthority))
  { dwLen += sprintf(lpszSIDStringName+dwLen,"2");
  }
  else if (0==memcmp(&siaSidAuthority,&siaCreatorSidAuthority,BytesInIdentifierAuthority))
  { dwLen += sprintf(lpszSIDStringName+dwLen,"3");
  }
  else if (0==memcmp(&siaSidAuthority,&siaNtAuthority        ,BytesInIdentifierAuthority))
  { dwLen += sprintf(lpszSIDStringName+dwLen,"5");
  }
  else
  { dwLen += sprintf(lpszSIDStringName+dwLen,"UnknownAuthority!");
  }

  dwNumSubAuthorities = (DWORD)( *(GetSidSubAuthorityCount(psidSID)) );

  for (dwSubAuthorityI=0; dwSubAuthorityI<dwNumSubAuthorities; dwSubAuthorityI++)
  { dwLen += sprintf(lpszSIDStringName+dwLen,"-%d",*(GetSidSubAuthority(psidSID,dwSubAuthorityI)));
  }

  return(TRUE);
}



 
 

 void awmUnlockFile( AWM_CHKED_FILE *p )
{
	if ( p->hFile ) {
		CloseHandle( ( void * )p->hFile ); p->hFile = NULL;
	}

}
 
 

 VOID InitializeWellKnownSIDs(VOID)
{
  DWORD dwSidWith0SubAuthorities;
  DWORD dwSidWith1SubAuthority;
  DWORD dwSidWith2SubAuthorities;
  DWORD dwSidWith3SubAuthorities;
  DWORD dwSidWith4SubAuthorities;

  SID_IDENTIFIER_AUTHORITY siaNullSidAuthority    = SECURITY_NULL_SID_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY siaWorldSidAuthority   = SECURITY_WORLD_SID_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY siaLocalSidAuthority   = SECURITY_LOCAL_SID_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY siaCreatorSidAuthority = SECURITY_CREATOR_SID_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY siaNtAuthority         = SECURITY_NT_AUTHORITY;

  //  These SID sizes need to be allocated

  dwSidWith0SubAuthorities = GetSidLengthRequired( 0 );
  dwSidWith1SubAuthority   = GetSidLengthRequired( 1 );
  dwSidWith2SubAuthorities = GetSidLengthRequired( 2 );
  dwSidWith3SubAuthorities = GetSidLengthRequired( 3 );
  dwSidWith4SubAuthorities = GetSidLengthRequired( 4 );

  //  Allocate and initialize the universal SIDs

  psidNullSid         = (PSID)LocalAlloc(LPTR,dwSidWith1SubAuthority);
  psidWorldSid        = (PSID)LocalAlloc(LPTR,dwSidWith1SubAuthority);
  psidLocalSid        = (PSID)LocalAlloc(LPTR,dwSidWith1SubAuthority);
  psidCreatorOwnerSid = (PSID)LocalAlloc(LPTR,dwSidWith1SubAuthority);
  psidCreatorGroupSid = (PSID)LocalAlloc(LPTR,dwSidWith1SubAuthority);

  InitializeSid( psidNullSid,         &siaNullSidAuthority,    1 );
  InitializeSid( psidWorldSid,        &siaWorldSidAuthority,   1 );
  InitializeSid( psidLocalSid,        &siaLocalSidAuthority,   1 );
  InitializeSid( psidCreatorOwnerSid, &siaCreatorSidAuthority, 1 );
  InitializeSid( psidCreatorGroupSid, &siaCreatorSidAuthority, 1 );

  *(GetSidSubAuthority( psidNullSid,         0 )) = SECURITY_NULL_RID;
  *(GetSidSubAuthority( psidWorldSid,        0 )) = SECURITY_WORLD_RID;
  *(GetSidSubAuthority( psidLocalSid,        0 )) = SECURITY_LOCAL_RID;
  *(GetSidSubAuthority( psidCreatorOwnerSid, 0 )) = SECURITY_CREATOR_OWNER_RID;
  *(GetSidSubAuthority( psidCreatorGroupSid, 0 )) = SECURITY_CREATOR_GROUP_RID;

  // Allocate and initialize the NT defined SIDs

  psidNtAuthoritySid   = (PSID)LocalAlloc(LPTR,dwSidWith0SubAuthorities);
  psidDialupSid        = (PSID)LocalAlloc(LPTR,dwSidWith1SubAuthority);
  psidNetworkSid       = (PSID)LocalAlloc(LPTR,dwSidWith1SubAuthority);
  psidBatchSid         = (PSID)LocalAlloc(LPTR,dwSidWith1SubAuthority);
  psidInteractiveSid   = (PSID)LocalAlloc(LPTR,dwSidWith1SubAuthority);
  psidLogonIdsSid      = (PSID)LocalAlloc(LPTR,dwSidWith3SubAuthorities);
  psidServiceSid       = (PSID)LocalAlloc(LPTR,dwSidWith1SubAuthority);
  psidLocalSystemSid   = (PSID)LocalAlloc(LPTR,dwSidWith1SubAuthority);
  psidBuiltinDomainSid = (PSID)LocalAlloc(LPTR,dwSidWith1SubAuthority);

  InitializeSid( psidNtAuthoritySid,   &siaNtAuthority, 0 );
  InitializeSid( psidDialupSid,        &siaNtAuthority, 1 );
  InitializeSid( psidNetworkSid,       &siaNtAuthority, 1 );
  InitializeSid( psidBatchSid,         &siaNtAuthority, 1 );
  InitializeSid( psidInteractiveSid,   &siaNtAuthority, 1 );
  InitializeSid( psidLogonIdsSid,      &siaNtAuthority, 3 );
  InitializeSid( psidServiceSid,       &siaNtAuthority, 1 );
  InitializeSid( psidLocalSystemSid,   &siaNtAuthority, 1 );
  InitializeSid( psidBuiltinDomainSid, &siaNtAuthority, 1 );

  *(GetSidSubAuthority( psidDialupSid,        0 )) = SECURITY_DIALUP_RID;
  *(GetSidSubAuthority( psidNetworkSid,       0 )) = SECURITY_NETWORK_RID;
  *(GetSidSubAuthority( psidBatchSid,         0 )) = SECURITY_BATCH_RID;
  *(GetSidSubAuthority( psidInteractiveSid,   0 )) = SECURITY_INTERACTIVE_RID;
  *(GetSidSubAuthority( psidLogonIdsSid,      0 )) = SECURITY_LOGON_IDS_RID;
  *(GetSidSubAuthority( psidLogonIdsSid,      1 )) = 0; // Bogus!
  *(GetSidSubAuthority( psidLogonIdsSid,      2 )) = 0; // Also bogus!
  *(GetSidSubAuthority( psidServiceSid,       0 )) = SECURITY_SERVICE_RID;
  *(GetSidSubAuthority( psidLocalSystemSid,   0 )) = SECURITY_LOCAL_SYSTEM_RID;
  *(GetSidSubAuthority( psidBuiltinDomainSid, 0 )) = SECURITY_BUILTIN_DOMAIN_RID;
}


 

 BOOL bChkACEsAsAppropriate(PSECURITY_DESCRIPTOR psdFileSD, LPTSTR  lpszFullName,
		AWM_SCRIPT_ACCESS *pASA )
{
	PACL                 paclFile;
	BOOL                 bHasACL;
	BOOL                 bOwnerDefaulted;
	DWORD                dwAcl_i;
	BOOL bAdminsAccessAll = FALSE;
	BOOL bEveryoneAccessRX = FALSE;
	BOOL bSystemAccessAll = FALSE;
  	ACL_SIZE_INFORMATION                      asiAclSize;
	DWORD                dwBufLength = sizeof(asiAclSize);
	ACCESS_ALLOWED_ACE   *paaAllowedAce;
#ifdef __DEBUG__
	char debugBuf[1024];
#endif

	if ( !GetSecurityDescriptorDacl(psdFileSD, (LPBOOL)&bHasACL,
					(PACL *)&paclFile, (LPBOOL)&bOwnerDefaulted) )
  	{
		debugLog( "GetSecurityDescriptorDacl( ) failed.");
		return(FALSE);
	}

	if (!bHasACL)  // No ACL to process, so OK, return
		return(TRUE);

	/**************************************************************************\
	 *
	 * This validity check is here for demonstration pruposes.  It's not likely a
	 *   real app would need to check the validity of this returned ACL.  The
	 *   validity check APIs are more intended to check validity after app code
	 *   has manipulated the structure and is about to hand it back to the system
	 *
	\**************************************************************************/

	if (!IsValidAcl(paclFile)) { 
		debugLog("IsValidAcl said bad ACL!");
		return(FALSE);
	}

	if (!GetAclInformation(paclFile, (LPVOID)&asiAclSize,
					(DWORD)dwBufLength, (ACL_INFORMATION_CLASS)AclSizeInformation))
	{ 
		debugLog("GetAclInformation");
		return(FALSE);
	}

	/**************************************************************************\
	 *
	 * We loop through in reverse order, because that's simpler, given that we
	 *   potentially delete ACEs as we loop through.  If started at 0 and went
	 *   up, if we deleted the 0th ACE, then the 1th ACE would become the 0th,
	 *   and we'd have to check the 0th ACE again
	 *
	\**************************************************************************/

	{
		char buf[128];
	  
		sprintf( buf, "There are %d ace for the file [%s].\n", asiAclSize.AceCount, lpszFullName );
		OutputDebugString( buf );
//		debugLog( "bChkACEsAsAppropriate( ): %s", buf );
	}

	for (dwAcl_i = asiAclSize.AceCount-1;  ((int)dwAcl_i) >= 0;  dwAcl_i--)	{
		if (!GetAce(paclFile, dwAcl_i, (LPVOID *)&paaAllowedAce)) { 
			PERR("GetAce");
			return(FALSE);
		}

		/************************************************************************\
		 *
		 * There are only four Ace Types pre-defined, so this next check is
		 *   redundant in a real app, but useful as a sanity check and a
		 *   demonstration in a sample
		 *
		\************************************************************************/

		if (!( (paaAllowedAce->Header.AceType == ACCESS_ALLOWED_ACE_TYPE)
			||(paaAllowedAce->Header.AceType == ACCESS_DENIED_ACE_TYPE )
			||(paaAllowedAce->Header.AceType == SYSTEM_AUDIT_ACE_TYPE  )
			||(paaAllowedAce->Header.AceType == SYSTEM_ALARM_ACE_TYPE  )))
		{ 
//			debugLog( "bChkACEsAsAppropriate( ): Invalid AceType." );
      		return(FALSE);
		}

		{ // Find SID of ACE, check if acct deleted
			#define		SZ_ACCT_NAME_BUF 1000
			DWORD       dwNameLength  = SZ_ACCT_NAME_BUF;
			#define     SZ_DMN_NAME_BUF  1000
			DWORD        dwDNameLength = SZ_DMN_NAME_BUF;
			DWORD        dwLastError   = NO_ERROR;

		/**********************************************************************\
		 *
		 * This validity check is here for demonstration pruposes.  It's not
		 *   likely a real app would need to check the validity of the SID
		 *   contained in the returned ACL.  The validity check APIs are more
		 *   intended to check validity after app code has manipulated the
		 *   structure and is about to hand it back to the system
		 *
		\**********************************************************************/

		if (!IsValidSid((PSID)&(paaAllowedAce->SidStart))) { 
			debugLog("IsValidSid said bad SID!");
			return(FALSE);
		}

		if ( isAdminsAccessAllAce( gpAwmChk, paaAllowedAce ) )
			bAdminsAccessAll = TRUE;
		else if ( isSystemAccessAllAce( gpAwmChk, paaAllowedAce ) )
			bSystemAccessAll = TRUE;
		else if ( isEveryoneRXAce( gpAwmChk, paaAllowedAce ) )
			bEveryoneAccessRX = TRUE;
  
		}
	
	}	// 遍历整个访问列表

	pASA->bAdminsAccessAll = bAdminsAccessAll;
	pASA->bSystemAccessAll = bSystemAccessAll;
	pASA->bEveryoneAccessRX = bEveryoneAccessRX;

// errLabel:

	#ifdef __DEBUG__
		sprintf( debugBuf, "bAdminsAccessAll is %d, bSystemAccessAll is %d, bEveryoneAccessRX is %d.\n", 
			bAdminsAccessAll, bSystemAccessAll, bEveryoneAccessRX );
		OutputDebugString( debugBuf );
//		debugLog( "bAdminsAccessAll is %d, bSystemAccessAll is %d, bEveryoneAccessRX is %d.", 
//			bAdminsAccessAll, bSystemAccessAll, bEveryoneAccessRX );
	#endif

	return(TRUE);

}





 int awmChkAce( void *pAC1, ACCESS_ALLOWED_ACE *paaAllowedAce, KINDS_OF_ACCESSMASKS_DECODED kamKindOfMask )
{
	int iErr = -1;
	AWM_CHK *pAC = ( AWM_CHK * )pAC1;
#define SZ_INDENT_BUF 80
	UCHAR ucIndentBuf[SZ_INDENT_BUF] = "";
 
	if ( paaAllowedAce->Header.AceType != ACCESS_ALLOWED_ACE_TYPE ) {
		iErr = 0;
		goto errLabel;
	}
    
	if ( EqualSid( ( PSID )&( paaAllowedAce->SidStart ), pAC->gSids.psidDomainGroupAdminsSid ) 
		|| EqualSid( ( PSID )&( paaAllowedAce->SidStart ), pAC->gSids.psidDomainAliasAdminsSid ) 
		|| EqualSid( ( PSID )&( paaAllowedAce->SidStart ), pAC->gSids.psidDomainUserAdminSid ) ) 
	{
		printf( "\nIt is the domain group admins, or the domain alias admins, or the domain user admin." );
		iErr = 0;
		goto errLabel;
	}
	if ( EqualSid( ( PSID )&( paaAllowedAce->SidStart ), pAC->gSids.psidLocalSystemSid ) ) {
		iErr = 0;
		goto errLabel;
	}
	
	if ( !LookupSIDName((PSID)&(paaAllowedAce->SidStart), ( char * )ucIndentBuf) ) { 
		perror("LookupSIDName failed");
    }
			
	if ( awmChkMask( paaAllowedAce->Mask, "", kamKindOfMask ) ) goto errLabel;

	iErr = 0;
	
errLabel:

	return iErr;

}


 
 

 int awmChkMask( ACCESS_MASK amMask, LPTSTR lpszOldIndent,
                 KINDS_OF_ACCESSMASKS_DECODED kamKindOfMask )
{
	int iErr = -1;
#define STANDARD_RIGHTS_ALL_THE_BITS 0x00FF0000L
#define GENERIC_RIGHTS_ALL_THE_BITS  0xF0000000L
	UCHAR ucIndentBuf[SZ_INDENT_BUF]     = "";
	UCHAR ucIndentBitsBuf[SZ_INDENT_BUF] = "";
	DWORD dwGenericBits;
	DWORD dwStandardBits;
	DWORD dwSpecificBits;
	DWORD dwAccessSystemSecurityBit;
	DWORD dwExtraBits;

	strcpy( ( char * )ucIndentBuf,    lpszOldIndent);
	strcat( ( char * )ucIndentBuf,    "  ");
	strcpy( ( char * )ucIndentBitsBuf,lpszOldIndent);
	strcat( ( char * )ucIndentBitsBuf,"                            ");

	dwStandardBits            = (amMask & STANDARD_RIGHTS_ALL_THE_BITS);
	dwSpecificBits            = (amMask & SPECIFIC_RIGHTS_ALL         );
	dwAccessSystemSecurityBit = (amMask & ACCESS_SYSTEM_SECURITY      );
	dwGenericBits             = (amMask & GENERIC_RIGHTS_ALL_THE_BITS );

	/**************************************************************************\
	 *
	 * Print then decode the standard rights bits
	 *
	\**************************************************************************/

	printf("\n%sStandard Rights        == 0x%.8x",ucIndentBuf,dwStandardBits);

	if ( dwStandardBits ) {
		if ((dwStandardBits & DELETE ) == DELETE ) { 
			printf("\n%s0x00010000 DELETE ",ucIndentBitsBuf);
			goto errLabel;
		}
		if ((dwStandardBits & READ_CONTROL ) == READ_CONTROL ) { 
			printf("\n%s0x00020000 READ_CONTROL            ",ucIndentBitsBuf);
		}
		if ((dwStandardBits & STANDARD_RIGHTS_READ ) == STANDARD_RIGHTS_READ ) { 
			printf("\n%s0x00020000 STANDARD_RIGHTS_READ    ",ucIndentBitsBuf);
		}
		if ((dwStandardBits & STANDARD_RIGHTS_WRITE ) == STANDARD_RIGHTS_WRITE ) { 
			printf("\n%s0x00020000 STANDARD_RIGHTS_WRITE   ",ucIndentBitsBuf);			
		}
		if ((dwStandardBits & STANDARD_RIGHTS_EXECUTE ) == STANDARD_RIGHTS_EXECUTE ) { 
			printf("\n%s0x00020000 STANDARD_RIGHTS_EXECUTE ",ucIndentBitsBuf);
		}
		if ((dwStandardBits & WRITE_DAC ) == WRITE_DAC ) { 
			printf("\n%s0x00040000 WRITE_DAC ",ucIndentBitsBuf);
			goto errLabel;
		}
		if ((dwStandardBits & WRITE_OWNER ) == WRITE_OWNER ) { 
			printf("\n%s0x00080000 WRITE_OWNER ",ucIndentBitsBuf);
			goto errLabel;
		}
		if ((dwStandardBits & SYNCHRONIZE ) == SYNCHRONIZE ) { 
			printf("\n%s0x00100000 SYNCHRONIZE ",ucIndentBitsBuf);			
		}
		if ((dwStandardBits & STANDARD_RIGHTS_REQUIRED) == STANDARD_RIGHTS_REQUIRED) { 
			printf("\n%s0x000F0000 STANDARD_RIGHTS_REQUIRED",ucIndentBitsBuf);
			goto errLabel;
    	}
    	if ((dwStandardBits & STANDARD_RIGHTS_ALL ) == STANDARD_RIGHTS_ALL ) { 
			printf("\n%s0x001F0000 STANDARD_RIGHTS_ALL     ",ucIndentBitsBuf);
			goto errLabel;
		}

		dwExtraBits = dwStandardBits & ( ~( DELETE
                                      | READ_CONTROL
                                      | STANDARD_RIGHTS_READ
                                      | STANDARD_RIGHTS_WRITE
                                      | STANDARD_RIGHTS_EXECUTE
                                      | WRITE_DAC
                                      | WRITE_OWNER
                                      | SYNCHRONIZE
                                      | STANDARD_RIGHTS_REQUIRED
                                      | STANDARD_RIGHTS_ALL) );
		if (dwExtraBits) { 
			printf("\n%sExtra standard bits == 0x%.8x <-This is a problem, should be all 0s",ucIndentBuf,dwExtraBits);
			goto errLabel;
		}
	}

	/**************************************************************************\
	 *
	 * Print then decode the specific rights bits
	 *
	\**************************************************************************/

	printf("\n%sSpecific Rights == 0x%.8x",ucIndentBuf,dwSpecificBits);

	if (dwSpecificBits) {
		if (FileAccessMask == kamKindOfMask) {
			if ((dwSpecificBits & FILE_READ_DATA ) == FILE_READ_DATA ) { 
				printf("\n%s0x00000001 FILE_READ_DATA (file & pipe) ",ucIndentBitsBuf);
			}
			if ((dwSpecificBits & FILE_LIST_DIRECTORY ) == FILE_LIST_DIRECTORY ) { 
				printf("\n%s0x00000001 FILE_LIST_DIRECTORY (directory) ",ucIndentBitsBuf);
			}
			if ((dwSpecificBits & FILE_WRITE_DATA ) == FILE_WRITE_DATA ) { 
				printf("\n%s0x00000002 FILE_WRITE_DATA (file & pipe) ",ucIndentBitsBuf);
				goto errLabel;
			}
			if ((dwSpecificBits & FILE_ADD_FILE ) == FILE_ADD_FILE ) { 
				printf("\n%s0x00000002 FILE_ADD_FILE (directory) ",ucIndentBitsBuf);
				goto errLabel;
			}
			if ((dwSpecificBits & FILE_APPEND_DATA ) == FILE_APPEND_DATA ) { 
				printf("\n%s0x00000004 FILE_APPEND_DATA (file) ",ucIndentBitsBuf);
				goto errLabel;
			}
			if ((dwSpecificBits & FILE_ADD_SUBDIRECTORY ) == FILE_ADD_SUBDIRECTORY ) { 
				printf("\n%s0x00000004 FILE_ADD_SUBDIRECTORY (directory) ",ucIndentBitsBuf);
				goto errLabel;
			}
			if ((dwSpecificBits & FILE_CREATE_PIPE_INSTANCE) == FILE_CREATE_PIPE_INSTANCE) { 
				printf("\n%s0x00000004 FILE_CREATE_PIPE_INSTANCE (named pipe) ",ucIndentBitsBuf);
				goto errLabel;
			}
			if ((dwSpecificBits & FILE_READ_EA ) == FILE_READ_EA ) { 
				printf("\n%s0x00000008 FILE_READ_EA (file & directory)",ucIndentBitsBuf);
			}
			if ((dwSpecificBits & FILE_WRITE_EA ) == FILE_WRITE_EA ) { 
				printf("\n%s0x00000010 FILE_WRITE_EA (file & directory)",ucIndentBitsBuf);
				goto errLabel;
			}
			if ((dwSpecificBits & FILE_EXECUTE ) == FILE_EXECUTE ) { 
				printf("\n%s0x00000020 FILE_EXECUTE (file) ",ucIndentBitsBuf);
      		}
      		if ((dwSpecificBits & FILE_TRAVERSE ) == FILE_TRAVERSE ) { 
				printf("\n%s0x00000020 FILE_TRAVERSE (directory) ",ucIndentBitsBuf);
			}
			if ((dwSpecificBits & FILE_DELETE_CHILD ) == FILE_DELETE_CHILD ) { 
				printf("\n%s0x00000040 FILE_DELETE_CHILD (directory) ",ucIndentBitsBuf);
			}
			if ((dwSpecificBits & FILE_READ_ATTRIBUTES ) == FILE_READ_ATTRIBUTES ) { 
				printf("\n%s0x00000080 FILE_READ_ATTRIBUTES (all) ",ucIndentBitsBuf);
			}
			if ((dwSpecificBits & FILE_WRITE_ATTRIBUTES ) == FILE_WRITE_ATTRIBUTES ) { 
				printf("\n%s0x00000100 FILE_WRITE_ATTRIBUTES (all) ",ucIndentBitsBuf);
				goto errLabel;
			}
			if (((dwStandardBits | dwSpecificBits ) & FILE_ALL_ACCESS ) == FILE_ALL_ACCESS ) { 
				printf("\n%s0x001F01FF FILE_ALL_ACCESS == (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0x1FF)",ucIndentBitsBuf);
				goto errLabel;
			}
			if (((dwStandardBits | dwSpecificBits ) & FILE_GENERIC_READ ) == FILE_GENERIC_READ ) { 
				printf("\n%s0x00120089 FILE_GENERIC_READ == (STANDARD_RIGHTS_READ | FILE_READ_DATA | FILE_READ_ATTRIBUTES | FILE_READ_EA | SYNCHRONIZE)",ucIndentBitsBuf);
      		}
      		if (((dwStandardBits | dwSpecificBits ) & FILE_GENERIC_WRITE ) == FILE_GENERIC_WRITE ) { 
				printf("\n%s0x00120116 FILE_GENERIC_WRITE == (STANDARD_RIGHTS_WRITE | FILE_WRITE_DATA | FILE_WRITE_ATTRIBUTES | FILE_WRITE_EA | FILE_APPEND_DATA | SYNCHRONIZE)",ucIndentBitsBuf);
				goto errLabel;
			}
			if (((dwStandardBits | dwSpecificBits ) & FILE_GENERIC_EXECUTE) == FILE_GENERIC_EXECUTE) { 
				printf("\n%s0x001200A0 FILE_GENERIC_EXECUTE == (STANDARD_RIGHTS_EXECUTE | FILE_READ_ATTRIBUTES | FILE_EXECUTE | SYNCHRONIZE)",ucIndentBitsBuf);
			}
			dwExtraBits = dwSpecificBits & ( ~( FILE_READ_DATA
                                        | FILE_LIST_DIRECTORY
                                        | FILE_WRITE_DATA
                                        | FILE_ADD_FILE
                                        | FILE_APPEND_DATA
                                        | FILE_ADD_SUBDIRECTORY
                                        | FILE_CREATE_PIPE_INSTANCE
                                        | FILE_READ_EA
                                        | FILE_WRITE_EA
                                        | FILE_EXECUTE
                                        | FILE_TRAVERSE
                                        | FILE_DELETE_CHILD
                                        | FILE_READ_ATTRIBUTES
                                        | FILE_WRITE_ATTRIBUTES
                                        | (FILE_ALL_ACCESS      & SPECIFIC_RIGHTS_ALL)
                                        | (FILE_GENERIC_READ    & SPECIFIC_RIGHTS_ALL)
                                        | (FILE_GENERIC_WRITE   & SPECIFIC_RIGHTS_ALL)
                                        | (FILE_GENERIC_EXECUTE & SPECIFIC_RIGHTS_ALL) ) );
      
			if (dwExtraBits) { 
				printf("\n%sExtra specific bits    == 0x%.8x <-This is a problem, should be all 0s",ucIndentBuf,dwExtraBits);
				goto errLabel;
      		}
	
		} else { 
			printf("\n%sYou will need to write some code (such as that directly",ucIndentBuf);
			printf("\n%s  above the code that wrote out this message) to decode",ucIndentBuf);
			printf("\n%s  this kind of access mask",ucIndentBuf);
			goto errLabel;
    	}
  
	}

  	/**************************************************************************\
  	 *
     * Print then decode the ACCESS_SYSTEM_SECURITY bit
     *
  	\**************************************************************************/

  	printf("\n%sAccess System Security == 0x%.8x",ucIndentBuf,dwAccessSystemSecurityBit);
	if ( dwAccessSystemSecurityBit ) {
		goto errLabel;
	}

  	/**************************************************************************\
  	 *
  	 * Print then decode the generic rights bits, which will rarely be on
  	 *
  	 * Generic bits are nearly always mapped by Windows NT before it tries to do
  	 *   anything with them.  You can ignore the fact that generic bits are
  	 *   special in any way, although it helps to keep track of what the mappings
  	 *   are so that you don't have any surprises
  	 *
  	 * The only time the generic bits are not mapped immediately is if they are
  	 *   placed in an inheritable ACE in an ACL, or in an ACL that will be
  	 *   assigned by default (such as the default DACL in an access token).  In
  	 *   that case they're mapped when the child object is created (or when the
  	 *   default DACL is used at object creation time)
  	 *
  	\**************************************************************************/

  	printf("\n%sGeneric  Rights        == 0x%.8x",ucIndentBuf,dwGenericBits);

  	if (dwGenericBits) {
		goto errLabel;
		if ((dwGenericBits & GENERIC_READ ) == GENERIC_READ ) { 
			printf("\n%s0x80000000 GENERIC_READ   ",ucIndentBitsBuf);
		}
		if ((dwGenericBits     & GENERIC_WRITE  ) == GENERIC_WRITE  ) { 
			printf("\n%s0x40000000 GENERIC_WRITE  ",ucIndentBitsBuf);
		}
		if ((dwGenericBits     & GENERIC_EXECUTE) == GENERIC_EXECUTE) { 
			printf("\n%s0x20000000 GENERIC_EXECUTE",ucIndentBitsBuf);
		}
		if ((dwGenericBits     & GENERIC_ALL    ) == GENERIC_ALL    ) { 
			printf("\n%s0x10000000 GENERIC_ALL    ",ucIndentBitsBuf);
		}

		dwExtraBits = dwGenericBits & ( ~( GENERIC_READ
                                     | GENERIC_WRITE
                                     | GENERIC_EXECUTE
                                     | GENERIC_ALL) );
		if (dwExtraBits) { 
			printf("\n%sExtra generic bits     == 0x%.8x <-This is a problem, should be all 0s",ucIndentBuf,dwExtraBits);
		}	
	}

	iErr = 0;

errLabel:

	return iErr;

}


