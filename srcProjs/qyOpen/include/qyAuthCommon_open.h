
#ifndef  __qyAuthCommon_open_h__
#define  __qyAuthCommon_open_h__	//  {

//
typedef  struct  __qyRightCommon_t  {
				 int				i;
}		 QY_RIGHT_COMMON;

typedef  struct  __qyGrpCommon_t  {
				 int				type;
				 unsigned  __int64	id;
				 QY_RIGHT_COMMON	right;
}		  QY_GRP_COMMON;

typedef  struct  __qyUsrCommon_t {
				 int				type;
				 unsigned  __int64	id;
				 QY_GRP_COMMON		grp;
}			QY_USR_COMMON;

//
#endif  //  }

