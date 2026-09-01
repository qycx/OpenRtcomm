
#include    "stdafx.h"

#include	<WinSock2.h>
#include <windows.h>



//

BOOL isLocalService()
{
    HANDLE hToken = NULL;

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
        return FALSE;

    BYTE buffer[SECURITY_MAX_SID_SIZE];
    DWORD sidSize = sizeof(buffer);

    BOOL result = CreateWellKnownSid(
        WinLocalServiceSid,
        NULL,
        buffer,
        &sidSize
    );

    if (!result) {
        CloseHandle(hToken);
        return FALSE;
    }

    DWORD tokenInfoSize = 0;
    GetTokenInformation(
        hToken,
        TokenUser,
        NULL,
        0,
        &tokenInfoSize
    );

    auto tokenUser =
        (PTOKEN_USER)malloc(tokenInfoSize);

    result = GetTokenInformation(
        hToken,
        TokenUser,
        tokenUser,
        tokenInfoSize,
        &tokenInfoSize
    );

    BOOL isLocalService = FALSE;

    if (result) {
        isLocalService =
            EqualSid(tokenUser->User.Sid, buffer);
    }

    free(tokenUser);
    CloseHandle(hToken);

    return isLocalService;
}


