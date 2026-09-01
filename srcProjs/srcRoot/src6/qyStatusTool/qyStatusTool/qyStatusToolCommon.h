
#ifndef  __QYSTATUSTOOLCOMMON_H__
#define  __QYSTATUSTOOLCOMMON_H__	/*  {  */

#include	<vfw.h>

#include	"qmCommon.h"
#include	"qyStatusStruct.h"

//
#define		CONST_maxnItemsInListBox_main				200000  *  1			//  状态窗口的列表框的最大容纳记录数
#define		CONST_maxnItemsInListBox_client				4500   * 10			//  状态窗口的列表框的最大容纳记录数

//
extern  TCHAR		gStatusToolWndCls[256];

//
extern  QY_STATUS_STRUCT* g_pStatusStruct;


DWORD  WINAPI  qyStatusToolThreadProc(  LPVOID  lpParameter  );
DWORD  WINAPI  statusPipeServThreadProc(  LPVOID  lpParameter  );


//
__declspec(dllexport)  int viewDlgState(int stateType);


#endif  /*  }  */

