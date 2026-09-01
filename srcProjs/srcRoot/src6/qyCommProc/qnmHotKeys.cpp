

#include	"stdafx.h"

//  #include  "stdafx.h"
//  #include  "resource.h"
//  #include  "qyMcMainCommon.h"
#include	<windows.h>
#include	<WinSock2.h>
#include	<tchar.h>

#include	"qyCommon.h"
#include	"qnmHotKeys.h"
//  #include	"resource.h"





 extern  "C"  BOOL bQnmAddHotKeys(  QYMC_HOTKEY  *  pHotKeys, HWND hWnd  )
{
	 int i;

	 traceLogA(  (char*)"bQnmAddHotKeys called"  );

	 //  n  =  sizeof(  gHotKeys  )  /  sizeof(  QYMC_HOTKEY  );
	 for  (  i  =  0;  pHotKeys[i].id  !=  -1;  i  ++  )  {
		 if  (  RegisterHotKey(  hWnd,  pHotKeys[i].id,  pHotKeys[i].fsModifiers,  pHotKeys[i].vk  )  )  {
			 pHotKeys[i].bRegistered  =  TRUE;
			}
		 else 
			 qyDisplayLastError(  (char*)"bQyMcAddHotKeys(  ) failed."  );
	 }
	 return  TRUE;
}


 extern  "C" void qnmRemoveHotKeys(  QYMC_HOTKEY  *  pHotKeys, HWND hWnd  )
{
	 int i;

	 traceLogA(  (char*)"qnmRemoveHotKeys called"  );

	 for  (  i  =  0;  pHotKeys[i].id  !=  -1;  i  ++  )  {
		 if  (  pHotKeys[i].bRegistered  )  {
			 if  (  UnregisterHotKey(  hWnd,  pHotKeys[i].id  )  )  {
			 	 pHotKeys[i].bRegistered  =  FALSE;
				}
			 else  {
				 traceInfo(  0,  (char*)"UnRegisterHotKey( %d ) not succeeded.",  pHotKeys[i].id  );
			 }
		 }
	 }

	 return;
}

