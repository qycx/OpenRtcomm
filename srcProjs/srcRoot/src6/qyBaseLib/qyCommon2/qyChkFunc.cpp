

#include <windows.h>
#include "qyCommon.h"
#include "qyChkCommon.h"

 extern "C" BOOL GetFullFileOrDirName(LPTSTR lpszFileName)
{
  UCHAR   ucPathBuf[SZ_NAME_BUF];
  DWORD   dwSzReturned;
  LPTSTR  lpszLastNamePart;
  LPTSTR  lpszFullName;

  dwSzReturned = GetFullPathName
                   (lpszFileName,
                    (DWORD)SZ_NAME_BUF,
                    (LPTSTR)&ucPathBuf,
                    (LPTSTR *)&lpszLastNamePart);
  if (0 == dwSzReturned)
    switch (GetLastError())
    { case ERROR_INVALID_NAME   :
        printf("\nError invalid file full-name (on GetFullPathName)");
        return(FALSE);
      default                   :
        PERR("GetFullPathName - unexpected return code");
        return(FALSE);
    }

  if (dwSzReturned > SZ_NAME_BUF)
  { PERR("GetFullPathName - buffer too small");
    return(FALSE);
  }

  lpszFullName = CharLower((LPTSTR)&ucPathBuf);

  if (!lpszFullName)
  { PERR("CharLower failure");
    return(FALSE);
  }

  /**************************************************************************\
  *
  * Copy the expanded and upper-case-shifted name to the buffer pointed to by
  *   the input argument
  *
  \**************************************************************************/

  strcpy(lpszFileName,lpszFullName);
  return TRUE;
}



#define SD_SIZE (65536 + SECURITY_DESCRIPTOR_MIN_LENGTH)

 extern "C" BOOL bAddAccessRights( PSID pSid, DWORD accessMask, CHAR *pFileName ) 
{
	// AWM_CHK *pAC = ( AWM_CHK * )gpAwmChk;
   
   // File SD variables

   UCHAR          ucSDbuf[SD_SIZE];
   PSECURITY_DESCRIPTOR pFileSD=(PSECURITY_DESCRIPTOR)ucSDbuf;
   DWORD          dwSDLengthNeeded;

   // ACL variables

   PACL           pACL;
   BOOL           bDaclPresent;
   BOOL           bDaclDefaulted;
   ACL_SIZE_INFORMATION AclInfo;

   // New ACL variables

   PACL           pNewACL;
   DWORD          dwNewACLSize;

   // New SD variables

   UCHAR                NewSD[SECURITY_DESCRIPTOR_MIN_LENGTH];
   PSECURITY_DESCRIPTOR psdNewSD=(PSECURITY_DESCRIPTOR)NewSD;

   // Temporary ACE

   PVOID          pTempAce;
   UINT           CurrentAceIndex;
      
   if(!GetFileSecurity(pFileName,
                 (SECURITY_INFORMATION)(DACL_SECURITY_INFORMATION),
                 pFileSD,
                 SD_SIZE,
                 (LPDWORD)&dwSDLengthNeeded))
   {
      printf("Error %d:GetFileSecurity\n",GetLastError());
      return(FALSE);
   }

   // STEP 4: Initialize new SD

   if(!InitializeSecurityDescriptor(psdNewSD,SECURITY_DESCRIPTOR_REVISION))
   {
      printf("Error %d:InitializeSecurityDescriptor\n",GetLastError());
      return(FALSE);
   }

   // STEP 5: Get DACL from SD

   if (!GetSecurityDescriptorDacl(pFileSD,
                    &bDaclPresent,
                    &pACL,
                    &bDaclDefaulted))
   {
      printf("Error %d:GetSecurityDescriptorDacl\n",GetLastError());
      return(FALSE);
   }

   // STEP 6: Get file ACL size information

   if(!GetAclInformation(pACL,&AclInfo,sizeof(ACL_SIZE_INFORMATION),
      AclSizeInformation))
   {
      printf("Error %d:GetAclInformation\n",GetLastError());
      return(FALSE);
   }

   // STEP 7: Compute size needed for the new ACL

   // dwNewACLSize = AclInfo.AclBytesInUse +
   //               sizeof(ACCESS_ALLOWED_ACE) +
   //               GetLengthSid(UserSID) - sizeof(DWORD);

   dwNewACLSize = AclInfo.AclBytesInUse +
                  sizeof(ACCESS_ALLOWED_ACE) +
                  GetLengthSid( pSid ) - sizeof(DWORD);


   // STEP 8: Allocate memory for new ACL

   pNewACL = (PACL)LocalAlloc(LPTR, dwNewACLSize);

   // STEP 9: Initialize the new ACL

   if(!InitializeAcl(pNewACL, dwNewACLSize, ACL_REVISION2))
   {
      printf("Error %d:InitializeAcl\n",GetLastError());
      LocalFree((HLOCAL) pNewACL);
      return(FALSE);
   }

   // STEP 10: If DACL is present, copy it to a new DACL

   if(bDaclPresent)  // only copy if DACL was present
   {
      // STEP 11: Copy the file's ACEs to our new ACL

      if(AclInfo.AceCount)
      {
         for(CurrentAceIndex = 0; CurrentAceIndex < AclInfo.AceCount;
            CurrentAceIndex++)
         {
            // STEP 12: Get an ACE

            if(!GetAce(pACL,CurrentAceIndex,&pTempAce))
            {
              printf("Error %d: GetAce\n",GetLastError());
              LocalFree((HLOCAL) pNewACL);
              return(FALSE);
            }

             // STEP 13: Add the ACE to the new ACL

            if(!AddAce(pNewACL, ACL_REVISION, MAXDWORD, pTempAce,
               ((PACE_HEADER)pTempAce)->AceSize))
            {
               printf("Error %d:AddAce\n",GetLastError());
               LocalFree((HLOCAL) pNewACL);
               return(FALSE);
            }
          }
      }
   }

   // STEP 14: Add the access-allowed ACE to the new DACL

   if(!AddAccessAllowedAce(pNewACL,ACL_REVISION2, accessMask, pSid )) {
		printf("Error %d:AddAccessAllowedAce",GetLastError());
		LocalFree((HLOCAL) pNewACL);
		return(FALSE);
	}
   
   
   // STEP 15: Set our new DACL to the file SD

   if (!SetSecurityDescriptorDacl(psdNewSD,
                     TRUE,
                     pNewACL,
                     FALSE))
   {
      printf("Error %d:SetSecurityDescriptorDacl",GetLastError());
      LocalFree((HLOCAL) pNewACL);
      return(FALSE);
   }

   // STEP 16: Set the SD to the File

   if (!SetFileSecurity(pFileName, DACL_SECURITY_INFORMATION,psdNewSD))
   {
      printf("Error %d:SetFileSecurity\n",GetLastError());
      LocalFree((HLOCAL) pNewACL);
      return(FALSE);
   }

   // STEP 17: Free the memory allocated for the new ACL

   LocalFree((HLOCAL) pNewACL);
   return(TRUE);

} 

 extern "C" BOOL isAdminsAccessAllAce( void *pAC1, ACCESS_ALLOWED_ACE *paaAllowedAce )
{
	AWM_CHK *pAC = ( AWM_CHK * )pAC1;
#define STANDARD_RIGHTS_ALL_THE_BITS 0x00FF0000L
	
	if ( !EqualSid( ( PSID )&paaAllowedAce->SidStart, pAC->gSids.psidDomainAliasAdminsSid ) )
		return FALSE;
	if ( paaAllowedAce->Mask != AWM_ACCESS_ALL )
		return FALSE;
	
	return TRUE;		

}

 extern "C" BOOL isSystemAccessAllAce( void *pAC1, ACCESS_ALLOWED_ACE *paaAllowedAce )
{
	AWM_CHK *pAC = ( AWM_CHK * )pAC1;
#define STANDARD_RIGHTS_ALL_THE_BITS 0x00FF0000L
	
	if ( !EqualSid( ( PSID )&paaAllowedAce->SidStart, pAC->gSids.psidLocalSystemSid ) )
		return FALSE;
	if ( paaAllowedAce->Mask != AWM_ACCESS_ALL )
		return FALSE;
	
	return TRUE;		

}

 extern "C" BOOL isEveryoneRXAce( void *pAC1, ACCESS_ALLOWED_ACE *paaAllowedAce )
{
	AWM_CHK *pAC = ( AWM_CHK * )pAC1;
#define STANDARD_RIGHTS_ALL_THE_BITS 0x00FF0000L
//	DWORD dwStandardBits;
	
	if ( !EqualSid( ( PSID )&paaAllowedAce->SidStart, pAC->gSids.psidSecurityWorldSid ) )
		return FALSE;
	if ( paaAllowedAce->Mask != AWM_ACCESS_RX ) return FALSE;
	
	return TRUE;		

}

 extern "C" BOOL isEveryoneRWAce( void *pAC1, ACCESS_ALLOWED_ACE *paaAllowedAce )
{
	AWM_CHK *pAC = ( AWM_CHK * )pAC1;
#define STANDARD_RIGHTS_ALL_THE_BITS 0x00FF0000L
//	DWORD dwStandardBits;
	
	if ( !EqualSid( ( PSID )&paaAllowedAce->SidStart, pAC->gSids.psidSecurityWorldSid ) )
		return FALSE;
	if ( paaAllowedAce->Mask != AWM_ACCESS_RW ) return FALSE;
	
	return TRUE;		

}

