#ifndef __UKEYMGR_H__
#define __UKEYMGR_H__

#include "skfapi_dll.h"

#define	TRUE	1
#define FALSE	0

#define  DECPRY_DATA_SIZE  1024

#define ERROR_THROW(r) {if((r) != SAR_OK) goto END_OF_FUN;}

HMODULE LoadSKFAPI(LPCTSTR lpSKFLibPath, GmDll * pUkeyLib);

void PrintByteStr(BYTE *str);

#endif