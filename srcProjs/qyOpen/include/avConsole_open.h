

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
#define		CONST_avConsole_cmd_retrieveUsrs			5
#define		CONST_avConsole_cmd_retrieveDynBmps			6
#define		CONST_avConsole_cmd_move					7
//
#define		CONST_avConsole_cmd_avTalk					8				//  2017/07/17
#define		CONST_avConsole_cmd_closeAvTalk				9				//  2017/07/17
//
#define		CONST_avConsole_cmd_initMsg					10				//  2017/07/17
#define		CONST_avConsole_cmd_msg						11				//  2017/07/17
//
#define		CONST_avConsole_cmd_view3dWall				12				//  2017/07/17



//
//  #define		M_avConsole_req_head						int  iType;  int  iCmd;	
//  2017/06/11
#define		M_avConsole_req_head						int  iType;						\
														unsigned  short  usCmd;			\
														unsigned  char  ucbReply;


//
typedef  struct  __avConsole_req_head_t					{
				 M_avConsole_req_head
}		  AvConsole_req_head;


//

//
//  2017/06/11
typedef  struct  __avConsole_req_view_t						{
				 //
				 M_avConsole_req_head
				 
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
				 
}	 AvConsole_req_view,  AvConsole_req_close,  AvConsole_req_closeAll;

//
typedef  struct  __avConsole_req_move_t						{
				 //
				 M_avConsole_req_head
				 
				 //
				 unsigned  __int64						ui64Id;		
				 unsigned  int							uiObjType;
				 unsigned  short  						usIndex_obj;

				 //
				 BOOL									bDesktop;
				 TCHAR									unique_wndTitle_parent[64];			//  必须是独一无二的窗口题头。
				 //
				 BOOL									bHide;
				 int									x, y, w, h;
				 BOOL									bFullScreen;
				 
}	 AvConsole_req_move;


//
//  2017/07/17
typedef  struct  __avConsole_req_avTalk_t				{
				 //
				 M_avConsole_req_head
				 
				 //
				 unsigned  __int64						ui64Id;		

				 //
				 BOOL									bDesktop;
				 TCHAR									unique_wndTitle_parent[64];			//  必须是独一无二的窗口题头。
				 //
				 BOOL									bHide;
				 int									x, y, w, h;
				 BOOL									bFullScreen;
				 
}	 AvConsole_req_avTalk, AvConsole_req_closeAvTalk;


//
typedef  struct  __avConsole_req_initMsg_t					{
				 //
				 M_avConsole_req_head
				 
				 //
				 TCHAR									unique_wndTitle_parent[64];			//  必须是独一无二的窗口题头。
				 
}	 AvConsole_req_initMsg;

//
typedef  struct  __avConsole_req_msg_t					{
				 //
				 M_avConsole_req_head
				 
				 //
				 unsigned  __int64						ui64Id_dst;
				 unsigned  __int64						ui64Id_from;
				 
				 //
				 TCHAR									unique_wndTitle_parent[64];			//  必须是独一无二的窗口题头。

				 //
				 TCHAR									tTxt[256];
				 
}	 AvConsole_req_msg;


//
typedef  struct  __avConsole_req_view3dWall_t					{
				 //
				 M_avConsole_req_head
				 
				 
				 //
				 TCHAR									unique_wndTitle_parent[64];			//  必须是独一无二的窗口题头。

				 
}	 AvConsole_req_view3dWall;



//
typedef  struct  __avConsole_req_retrieveUsr_t			{
				 unsigned  __int64						ui64Id;
				 TCHAR									dw[32];
				 TCHAR									bm[32];
				 TCHAR									syr[32];
				 //
				 int									iStatus;

}		 AvConsole_req_retrieveUsr;


//
typedef  struct  __avConsole_req_retrieveUsrs_t			{
				 M_avConsole_req_head
				 //
				 TCHAR									unique_wndTitle_parent[64];			//  必须是独一无二的窗口题头。
				 unsigned  __int64						ui64Id_lastRecvd;
				 //
				 unsigned  short						usCnt;
				 AvConsole_req_retrieveUsr				mems[32];

}		 AvConsole_req_retrieveUsrs;


//
typedef  struct  __avConsole_req_retrieveDynBmp_t		{
			 	 unsigned  int							uiObjType;					
				 unsigned  short						usIndex_obj;				
				 unsigned  short						usHelp_subIndex;
				 //
				 TCHAR									cusName[32];
				 //
				 int									w,  h;

				 
}		 AvConsole_req_retrieveDynBmp;

//
typedef  struct  __avConsole_retrieveDynBmps_t			{
				 M_avConsole_req_head
				 //
				 TCHAR									unique_wndTitle_parent[64];			//  必须是独一无二的窗口题头。
				 //
				 unsigned  __int64						ui64Id_toBeRetrieved;
				 //
				 unsigned  short						usCnt;
				 AvConsole_req_retrieveDynBmp			mems[10];
	
}		 AvConsole_req_retrieveDynBmps;




#endif  //  }




