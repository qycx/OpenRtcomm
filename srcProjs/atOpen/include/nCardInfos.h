

#ifndef  __nCardsInfo_h__
#define  __nCardsInfo_h__		//  {


//
typedef  struct  __nCardInfo_t {
				 char  uuid[128];
}		 NCardInfo;


//
typedef  struct  __nCardInfos_t {
				 unsigned  short	usCnt;
				 //
				 NCardInfo			mems[8];

}		 NCardInfos;

//
int  getNCardInfos(NCardInfos* pCardInfos);



#endif  //  }


