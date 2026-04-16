
#ifndef  __atMsgFunc_h__
#define  __atMsgFunc_h__	//  {

//
#include	"myTypes_basic.h"

//
typedef  struct  __atMsgHead_n_t {

	//
	unsigned  char						ucFlg_buf[1];				
	unsigned  char						usCode_buf[2];				// 
	unsigned  char						uiLen_buf[4];				//
	char								l3_elapse_buf[3];		
	unsigned  char						uiTranNo_buf[4];			
	unsigned  char						usSeqNo_buf[2];				

	//
#ifdef  __USE_dbg_i64StartTime__
	//char								dbg_i64StartTime_buf[8];
#endif 

}		 AT_MSG_HEAD_n;




#endif  //  }


