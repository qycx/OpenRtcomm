

#include <windows.h>
#include "qyCommon.h"
#include "qyChkCommon.h"


// 此函数使LogFile对administrators和system开放权限，对Everyone开放rw权限，对其他封闭。
 extern "C" void qyChkLogFile( AWM_CHK *pAC, char *fullPathName, int *piState )
{
	int iState = AWM_CHK_FILE_INVALID;
			
	
	if ( !bPreDoOneLogFileOrDir( fullPathName ) ) {
		debugLog( "bPreDoOneFileOrDir( ) failed." );
		OutputDebugString( "bPreDoOneFileOrDir( ) failed.\n" );
		goto errLabel;
	}
	


	if ( !DoOneLogFileOrDir( fullPathName ) ) {
		debugLog( "DoOneFileOrDir( ) failed." );
		OutputDebugString( "DoOneFileOrDir( ) failed." );
		goto errLabel;
	}
	// debugLog( "DoOneFileOrDir( ) Ok." );
	OutputDebugString( "DoOneFileOrDir( ) Ok.\n" );

	iState = AWM_CHK_FILE_OK;
	
errLabel:

	*piState = iState;

	return;

}





 extern "C" int awmChkLogAce( void *pAC1, ACCESS_ALLOWED_ACE *paaAllowedAce, KINDS_OF_ACCESSMASKS_DECODED kamKindOfMask )
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
			
	if ( awmChkLogMask( paaAllowedAce->Mask, "", kamKindOfMask ) ) goto errLabel;

	iErr = 0;
	
errLabel:

	return iErr;

}


  extern "C" int awmChkLogMask( ACCESS_MASK amMask, LPTSTR lpszOldIndent,
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
			}
			if ((dwSpecificBits & FILE_ADD_FILE ) == FILE_ADD_FILE ) { 
				printf("\n%s0x00000002 FILE_ADD_FILE (directory) ",ucIndentBitsBuf);				
			}
			if ((dwSpecificBits & FILE_APPEND_DATA ) == FILE_APPEND_DATA ) { 
				printf("\n%s0x00000004 FILE_APPEND_DATA (file) ",ucIndentBitsBuf);
			}
			if ((dwSpecificBits & FILE_ADD_SUBDIRECTORY ) == FILE_ADD_SUBDIRECTORY ) { 
				printf("\n%s0x00000004 FILE_ADD_SUBDIRECTORY (directory) ",ucIndentBitsBuf);
			}
			if ((dwSpecificBits & FILE_CREATE_PIPE_INSTANCE) == FILE_CREATE_PIPE_INSTANCE) { 
				printf("\n%s0x00000004 FILE_CREATE_PIPE_INSTANCE (named pipe) ",ucIndentBitsBuf);
			}
			if ((dwSpecificBits & FILE_READ_EA ) == FILE_READ_EA ) { 
				printf("\n%s0x00000008 FILE_READ_EA (file & directory)",ucIndentBitsBuf);
			}
			if ((dwSpecificBits & FILE_WRITE_EA ) == FILE_WRITE_EA ) { 
				printf("\n%s0x00000010 FILE_WRITE_EA (file & directory)",ucIndentBitsBuf);
			}
			if ((dwSpecificBits & FILE_EXECUTE ) == FILE_EXECUTE ) { 
				printf("\n%s0x00000020 FILE_EXECUTE (file) ",ucIndentBitsBuf);
				goto errLabel;
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
			}
			if (((dwStandardBits | dwSpecificBits ) & FILE_GENERIC_EXECUTE) == FILE_GENERIC_EXECUTE) { 
				printf("\n%s0x001200A0 FILE_GENERIC_EXECUTE == (STANDARD_RIGHTS_EXECUTE | FILE_READ_ATTRIBUTES | FILE_EXECUTE | SYNCHRONIZE)",ucIndentBitsBuf);
				goto errLabel;
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
			goto errLabel;
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

 extern "C" BOOL DoOneLogFileOrDir(LPTSTR lpszFullName)
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


  if (!DeleteLogACEsAsAppropriate(psdAbsFileSD,lpszFullName)) {
	  debugLog( "DoOneFileOrDir( ): DeleteACEsAsAppropriate( ) failed." );
	  return(FALSE);
  }

  return(TRUE);
}


 extern "C" BOOL bChkLogACEsAsAppropriate(PSECURITY_DESCRIPTOR psdFileSD, LPTSTR  lpszFullName,
		AWM_SCRIPT_ACCESS *pASA )
{
	PACL                 paclFile;
	BOOL                 bHasACL;
	BOOL                 bOwnerDefaulted;
	DWORD                dwAcl_i;
	BOOL bAdminsAccessAll = FALSE;
	// BOOL bEveryoneAccessRX = FALSE;
	BOOL bSystemAccessAll = FALSE;
	BOOL bEveryoneAccessRW = FALSE;
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
		else if ( isEveryoneRWAce( gpAwmChk, paaAllowedAce ) )
			bEveryoneAccessRW = TRUE;
  
		}
	
	}	// 遍历整个访问列表

	pASA->bAdminsAccessAll = bAdminsAccessAll;
	pASA->bSystemAccessAll = bSystemAccessAll;
	pASA->bEveryoneAccessRW = bEveryoneAccessRW;

// errLabel:

	#ifdef __DEBUG__
		sprintf( debugBuf, "bAdminsAccessAll is %d, bSystemAccessAll is %d, bEveryoneAccessRW is %d.\n", 
			bAdminsAccessAll, bSystemAccessAll, bEveryoneAccessRW );
		OutputDebugString( debugBuf );
//		debugLog( "bAdminsAccessAll is %d, bSystemAccessAll is %d, bEveryoneAccessRX is %d.", 
//			bAdminsAccessAll, bSystemAccessAll, bEveryoneAccessRX );
	#endif

	return(TRUE);

}


 extern "C" BOOL bPreDoOneLogFileOrDir( LPTSTR lpszFullName )
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
  if ( !bChkLogACEsAsAppropriate( psdAbsFileSD, lpszFullName, &aSA ) )
	  return FALSE;
  if ( !bAddLogACESAsNeeded( psdAbsFileSD, lpszFullName, &aSA ) )
	  return FALSE;
  
  return(TRUE);

}

 extern "C" BOOL DeleteLogACEsAsAppropriate(PSECURITY_DESCRIPTOR psdFileSD, LPTSTR  lpszFullName )
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

	  if ( awmChkLogAce( gpAwmChk, paaAllowedAce, FileAccessMask ) ) {
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

 extern "C" BOOL bAddLogACESAsNeeded( PSECURITY_DESCRIPTOR psdFileSD, LPTSTR lpszFullName, AWM_SCRIPT_ACCESS *pASA )
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

	if ( !pASA->bEveryoneAccessRW ) {
		if ( !bAddAccessRights( pAC->gSids.psidSecurityWorldSid, AWM_ACCESS_RW, lpszFullName ) ) {
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

