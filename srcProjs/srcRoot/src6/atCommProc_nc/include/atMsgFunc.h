
#ifndef  __atMsgFunc_h__
#define  __atMsgFunc_h__	//  {

//
#include	"myTypes_basic.h"

//
typedef  struct  __atMsgHead_h_t		{
	unsigned  char						ucFlg;				//  2007/04/22
	char								reserved[1];		//  
	//
	unsigned  short						usCode;				// 
	//
	unsigned  int						uiLen;				//  
	__int64								i64StartTime;		//  2007/05/07, 
	unsigned  int						uiTranNo;			//  2007/05/02
	unsigned  short						usSeqNo;			//  2007/05/02
	char								reserved1[2];		//  				 

	//
	int									l3_elapse;
	__int64								dbg_i64StartTime;

	//
}		 AT_MSG_HEAD_h;


//


//
// 在usCode<=255, uiLen用3個字節夠了，用14.如果沒有moreData. 則沒有seqNo
// 對usSeqNo, 最高位改成結束位。所以，seqNo為8  +  7個bits.
//
typedef  struct  __atMsgHead14_n_t {

	//
	unsigned  char						ucFlg_buf[1];
	unsigned  char						ucCode_buf[1];				// 
	unsigned  char						uiLen3_buf[3];				//
	char								l3_elapse_buf[3];
	unsigned  char						uiTranNo_buf[4];
	unsigned  char						usSeqNo_buf[2];

	//
#ifdef  __USE_dbg_i64StartTime__
	//char								dbg_i64StartTime_buf[8];
#endif 

}		 AT_MSG_HEAD14_n;



// 這個結構和14太接近，放棄了。
// head16
typedef  struct  __atMsgHead16_n_t {

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

}		 AT_MSG_HEAD16_n;


// 如果不用14, 就用22. 如果沒有moreData. 則沒有seqNo
// 在相對時間超過3個字節后（大約200天)，要采用22，這裏的i64StartTime是絕對時間。如果沒有moreData. 則沒有seqNo
//
typedef  struct  __atMsgHead22_n_t {

	//
	unsigned  char						ucFlg_buf[1];				//  2007/04/22
	unsigned  char						reserved[1];				//  
	unsigned  char						usCode_buf[2];				// 
	unsigned  char						uiLen_buf[4];				//  
	unsigned  char						i64StartTime_buf[8];		//  絕對時間
	unsigned  char						uiTranNo_buf[4];			//  2007/05/02
	unsigned  char						usSeqNo_buf[2];				//  2007/05/02

}		 AT_MSG_HEAD22_n;



#endif  //  }


