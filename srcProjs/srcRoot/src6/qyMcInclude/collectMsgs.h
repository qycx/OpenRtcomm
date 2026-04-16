
#ifndef  __collectMsgs_h__
#define  __collectMsgs_h__	//  {

//
#define		MAX_collectMsgs					10  *  5
 //
#define		DEFAULT_collectMsgs				5  *  5

 //  2015/08/28
 typedef  struct  __collectMsgs_t	{
				  unsigned  int		uiBufSize_tmppMsg;
				  MIS_MSGU		*	tmppMsgs[MAX_collectMsgs];
				  unsigned  short	usMaxCnt_tmppMsgs;
				  //
				  struct			{
					  int			cnt;
				  }					var;
 }		  COLLECT_msgs;





#endif  //  }


