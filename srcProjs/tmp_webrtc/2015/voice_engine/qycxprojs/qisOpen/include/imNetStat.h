
#ifndef  __imNetStat_h__
#define  __imNetStat_h__	//  {

//
typedef  struct  __imNetStat_t										{
				 //
				 unsigned  __int64									ui64MsgDataLenRecvd;							//  2009/10/10
				 unsigned  __int64									ui64MsgDataLenSent;
				 //
				 unsigned  int										uiInSpeedInKbps;								//  bps
				 unsigned  int										uiOutSpeedInKbps;
				 //
				 //  unsigned  __int64								ui64MsgDataLenRecvd_dec;
				 //  unsigned  __int64								ui64MsgDataLenSent_dec;
				 //
				 //  unsigned  long									nMsgRecvd;
				 //  unsigned  long									nMsgSent;
				 //
				 //
}		 IM_NET_STAT;

//
//  2015/06/18
typedef  struct  __trans_ptsInfo_t									{
				 //
				 struct												{
					 
					 //
					 DWORD											dwTickCnt_calc_start;						//  ?????????????????

					 //
					 unsigned  int									uiCnt_ptsErr;								//  pts??????
					 unsigned  int									uiCnt_notRecvd_pts;							//  ??pts??

				 }													v;
}		 TRANS_pts_info;


#endif  //  }

