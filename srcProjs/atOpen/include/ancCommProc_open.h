
#ifndef  __ancCommProc_open_h__
#define  __ancCommProc_open_h__		//  {

#include	"myTypes_basic.h"


//
//
//  
//																0				//  空着未用
#define		CONST_atDataType_byte								1				//  
#define		CONST_atDataType_short								2				//  
#define		CONST_atDataType_l32								3				//  
#define		CONST_atDataType_l64								4				//  
#define		CONST_atDataType_str								5				//  ascii字符串
#define		CONST_atDataType_utf8Str							6				//  unicode字符串
#define		CONST_atDataType_lData								7				//  
//  
//  以上最重要的基本数据类型要<8, 占据3个bit
//  所有的数据类型要<128. 占据7个bit
//
#define		CONST_atDataType_wStr								10				//  
#define		CONST_atDataType_data								11				//  


//
//  新的标志位，需要把msb空出来，提供最重要的包结构区分

//
#define		CONST_atCommFlg_msb							(  1  <<  7  )
//
#define		CONST_atCommFlg_resp						(  1  <<  6  )
#define		CONST_atCommFlg_moreData					(  1  <<  5  )									//  
//
//#define		CONST_atCommFlg_talkData					(  1  <<  4  )									//  数据区的格式为MIS_MSG_TALKDATA，否则为IM_MSG_CONTENTU
//
#define		CONST_atCommFlg_routeTalkData				(  1  <<  3  )									//  数据区的格式为用MSG_ROUTE+IM_MSG_CONTENTU



//
#define		MAX_12bits		(  16  *  256  -  1  )



//
//  用在线程间传临时音频数据
//
typedef  struct  __tmpAPkt_t    {
                 int            iSampleTimeInMs;
                 int            uiPts;
                 //
                 int            len;
                 char           buf[4096];
}        TmpAPkt;



//
#endif  //  }


