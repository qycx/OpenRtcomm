
#ifndef __QYCHKCOMMON_H__
#define __QYCHKCOMMON_H__	/* { */

#ifdef __cplusplus
 extern "C" {
#endif

#define SZ_NAME_BUF MAX_PATH

#include "qyChk.h"

extern void *gpAwmChk;


BOOL GetFullFileOrDirName(LPTSTR lpszFileName);
BOOL isAdminsAccessAllAce( void *pAC1, ACCESS_ALLOWED_ACE *paaAllowedAce );
BOOL isSystemAccessAllAce( void *pAC1, ACCESS_ALLOWED_ACE *paaAllowedAce );
BOOL isEveryoneRXAce( void *pAC1, ACCESS_ALLOWED_ACE *paaAllowedAce );
BOOL isEveryoneRWAce( void *pAC1, ACCESS_ALLOWED_ACE *paaAllowedAce );


BOOL bAddAccessRights( PSID pSid, DWORD accessMask, CHAR *pFileName );

#ifdef __cplusplus
 }
#endif

#endif /* } */
