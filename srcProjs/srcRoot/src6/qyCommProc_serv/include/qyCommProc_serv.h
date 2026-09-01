
#ifndef  __qyCommProc_serv_h__
#define  __qyCommProc_serv_h__	//  {

//
#include	"qnmCommProc_mis.h"





//
//  2007/04/15
#define		DEFAULT_usCliThreads_io							40		// 20
#define		DEFAULT_usMgrThreads_cs							13							//  2016/12/30	//  10							//  2008/05/15, mtMgrThreadProc_mis
#define		DEFAULT_usMgrThreads_route						80		// 40	//30							//  11							//  2008/05/15, mtMgrThreadProc_mis
#define		DEFAULT_usMgrThreads_switch_route				80		// 50							//  12							//  2008/05/15, mtMgrThreadProc_mis

//
#define		CONST_maxSendMsgs_is							40		//	20  *  10					//  2015/09/04  //20							//  2007/12/09, iocp


/////////////////////////
//
//
#define		DEFAULT_cntof_qmdConfMems								100
//
#define		MAX_cntof_mcus											DEFAULT_cntof_qmdConfMems
#define		MIN_cntof_mcus											3
#define		DEFAULT_cntof_mcus										10

//
#define		DEFAULT_cntof_qmdConnMems								100



//
#define		CONST_misMsgType_sendFinishedFailed				CONST_misMsgType_serv_base  +  1
#define		CONST_misMsgType_hg								CONST_misMsgType_serv_base  +  2		//  2023/03/22


//
typedef  struct  __misMsg_sendFinishedFailed_t				{						//  ÓÃÀ´ÔÚclientÎ´ÈÏÖ¤Ç°µÄmgrºÍclientµÄ´¦ÀíÄ£¿éÖ®¼äµÄÊý¾Ý´«Êä
				 MACRO_misMsg_common

				 //
				 QY_MESSENGER_ID							idInfo_mcu;

}		 MIS_MSG_sendFinishedFailed;


//
typedef  struct  __misMsg_hg_t								{
				 MACRO_misMsg_common

				 //
				 IM_CONTENTU								content;

}		 MIS_MSG_hg;


//
//
  typedef  struct  __qyLoginRcd_t					{	
				   TCHAR							misServName[128];
				   QY_MESSENGER_ID					idInfo;
				   unsigned  int					uiLoginId;
				   
  }		   QyLoginRcd;

//
  int  insertLoginRcd(  void  *  pDb,  int  iDbType,  TCHAR  *  misServName,  QY_MESSENGER_ID  idInfo,  unsigned  int uiLoginId  );
 int  updateLoginRcd(  void  *  pDb,  int  iDbType,  TCHAR  *  misServName,  QY_MESSENGER_ID  idInfo,  unsigned  int uiLoginId  );
  bool  bGetQyLoginRcd(  void  *  pDb,  int iDbType,  TCHAR  *  misServName,  QY_MESSENGER_ID  idInfo,  QyLoginRcd  *  pRcd  );



//
#endif  //  }





