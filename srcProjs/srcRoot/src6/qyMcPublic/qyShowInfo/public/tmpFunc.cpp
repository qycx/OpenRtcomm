
#include	"stdafx.h"

#include	"qyPrecomp.h"
#include	<winsock2.h>
#include	<windows.h>
#include	<assert.h>
#include	<stddef.h>
#include	<tchar.h>
#include	<stdlib.h>
#include	"qyCommon.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qnmPcComm.h"
#include	"qnmAssetsCommProc.h"
#include	"qnmSpCommProc.h"
#include	"qwmNetworkStatusCommProc.h"
#include	"qyTCharCommProc.h"
#include	"qnmCustom.h"
#include	"qySyncCommProc.h"
#include	"genericQueue.h"
#include	"qyq2.h"
#include	"tmpCeLib.h"
#include	"qyShowInfoCommon.h"

//
 BOOL WINAPI myIsWow64Process(  QY_ENV  *  pEnv,  HANDLE hProcess,  PBOOL Wow64Process  )
 {
	 return  false;
 }

  BOOL myGetComputerName(  LPTSTR lpBuffer,  LPDWORD lpnSize  )
  {
	  return  true;
  }

