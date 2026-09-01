
#ifndef  __qyTypes_open_h__
#define  __qyTypes_open_h__		//  {

//
#if  0
typedef  struct  __qyBuf_t				{
				 UINT4					resourceType;		// 资源类型
				 UINT4					len;
				 unsigned  char		*	data;	
}		 QY_BUF;

//
typedef  struct  __qyStr_t {
	UINT4					len;
	UINT4					resourceType;
	unsigned  char* szData;
}		 QY_STR;

typedef  struct  __qyDmItem_t {
	long					type;
	TCHAR* des;
	TCHAR* pData;
	//  long				flg;
	//  long				data;
}		 QY_DMITEM;

#endif 

//
typedef  struct  __qyBuf_t				{
				 int					resourceType;		// 资源类型
				 int					len;
				 unsigned  char		*	data;	
}		 QY_BUF;


//
typedef  struct  __qyStr_t {
	int					len;
	int					resourceType;
	unsigned  char* szData;
}		 QY_STR;


typedef  struct  __qyDmItem_t {
	long					type;
	const TCHAR* des;
	const TCHAR* pData;
	//  long				flg;
	//  long				data;
}		 QY_DMITEM;


//
#endif  //  }

