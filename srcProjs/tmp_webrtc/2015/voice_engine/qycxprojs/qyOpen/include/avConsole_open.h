

#ifndef  __avConsole_open_h__
#define  __avConsole_open_h__	//  {

//
#include	"qisMsg_open.h"

//
#define		CONST_avConsole_cmd_null					0
//#define		CONST_avConsole_cmd_enlarge					1
#define		CONST_avConsole_cmd_view					2
#define		CONST_avConsole_cmd_close					3
#define		CONST_avConsole_cmd_closeAll				4




//
typedef  struct  __avConsole_req_t						{
				 int 									iType;
				 //
				 int 									iCmd;
				 
				 //
				 unsigned  __int64						ui64Id;		
				 unsigned  int							uiObjType;
				 unsigned  short  						usIndex_obj;

				 //
				 BOOL									bDesktop;
				 TCHAR									unique_wndTitle_parent[64];			//  必须是独一无二的窗口题头。
				 //
				 int									x, y, w, h;
				 BOOL									bFullScreen;
				 
}	 AV_console_req;



#endif  //  }




