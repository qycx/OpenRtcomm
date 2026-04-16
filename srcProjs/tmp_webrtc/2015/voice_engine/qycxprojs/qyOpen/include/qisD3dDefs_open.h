
#ifndef  __qisD3dDefs_open_h__
#define  __qisD3dDefs_open_h__	//  {


//
//  #define  	__USE_dx9__
//  #define  	__USE_dx10__
#define		__USE_dx11__



//
#define		CONST_i3dType_null									0
#define		CONST_i3dType_d3d9									1
#define		CONST_i3dType_d3d10									2
#define		CONST_i3dType_d3d11									3


//  2015/10/03
#define		MAX_sharedTexes_dec										60		//  2016/04/13	//  30	//  2016/04/08	//  20
#define		MAX_sharedTexes_enc										20

//
//#define		M_get_ucMaxCnt(  uiMax_intervalInMs_renderFrame,  uiFrameTimeInMs  )	uiFrameTimeInMs  ?  (  uiMax_intervalInMs_renderFrame  /  uiFrameTimeInMs  /  4  *  4  +  6  )  :  0
#define		M_get_ucMaxCnt(  uiMax_intervalInMs_renderFrame,  uiFrameTimeInMs  )	uiFrameTimeInMs  ?  (  uiMax_intervalInMs_renderFrame  /  uiFrameTimeInMs  /  4  *  4  +  1  )  :  0



//  2015/10/03
typedef  struct  __pktSharedTexInfo_t								{
				 DWORD												dwProcessId;
				 unsigned  int										tn;
				 unsigned  int										uiSeqNo;
				 unsigned  char										ucMaxCnt_sharedTexes;
				 //
				 BOOL												bTexShared;
				 //
				 unsigned  short									usMax_intervalInMs_renderFrame;

}		 PKT_sharedTex_info;


//  2015/10/06
#define		CONST_send_reqKey										0
#define		CONST_send_relKey										1							
//
#define		CONST_recv_reqKey										1
#define		CONST_recv_relKey										0							




#endif	//  }




