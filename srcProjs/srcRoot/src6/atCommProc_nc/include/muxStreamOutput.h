

#ifndef  __muxStreamOutput_h__
#define  __muxStreamOutput_h__	//  {

//
#include	"qyq2.h"

//
//
typedef  struct  __muxStreamOutputQ_t {

	//  
	struct {

		//
		QY_Q2* pOutputQ2;

		//
		time_t										tLastTime_showFrameInfo;
		unsigned  short								usCnt_pkts;

	}													mixer;

	//	
	struct {

		//
		QY_Q2* pOutputQ2;									//  2009/07/26

		//
#ifdef  __DEBUG__					 
		TRANSFER_videoData_stat				stat;										//  2011/01/26
#endif

	}													photomosaic;								//  


}		 MuxStreamOutputQ;

//
int  initMuxStreamOutputQ(int  iTaskId,  int muxStreamIndex, MuxStreamOutputQ* pMuxStreamOutput);
int  exitMuxStreamOutputQ(MuxStreamOutputQ* pMuxStreamOutput);


#endif  //  }


