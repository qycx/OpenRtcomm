

#ifndef  __roadDefs_h__
#define  __roadDefs_h__		//  {

//
#define		CONST_rnType_null							0
#define		CONST_rnType_redirect						10


//
typedef  struct  __roadNodeHead_t						{
				 unsigned  int							uiType;
				 //
				 BOOL									bInited;
}		 RoadNode_head;

//
typedef  struct  __roadNode_t							{
				 RoadNode_head							head;
}		 RnCommon;



//
//
struct  __rnDataRedirect_qyMcInfo_t			{
				 
				 //
				 CCtxQyMc	*		pQyMc;				  
				 
};





#endif  //  }


