
#ifndef  __qisD3dDefs_open_h__
#define  __qisD3dDefs_open_h__	//  {


//
//  #define  	__USE_dx9__
//  #define  	__USE_dx10__
#define		__USE_dx11__
#define		__USE_dx12__



//
#define		CONST_i3dType_null									0
#define		CONST_i3dType_d3d9									1
#define		CONST_i3dType_d3d10									2
#define		CONST_i3dType_d3d11									3
#define		CONST_i3dType_d3d12									4



//  2015/10/03
#define		MAX_sharedTexes_dec										5			//  60		//  2016/04/13	//  30	//  2016/04/08	//  20
#define		MAX_sharedTexes_enc										20

//
//#define		M_get_ucMaxCnt(  uiMax_intervalInMs_renderFrame,  uiFrameTimeInMs  )	uiFrameTimeInMs  ?  (  uiMax_intervalInMs_renderFrame  /  uiFrameTimeInMs  /  4  *  4  +  6  )  :  0
#define		M_get_ucMaxCnt(  uiMax_intervalInMs_renderFrame,  uiFrameTimeInMs  )	uiFrameTimeInMs  ?  (  uiMax_intervalInMs_renderFrame  /  uiFrameTimeInMs  /  4  *  4  +  1  )  :  0


//
//#define		M_getTexName_enc(  dwProcessId,  tn_sharedTex,  real_index,  tName,  cnt  )		_sntprintf(  tName,  cnt,  _T(  "qmste%d-%d-%d"  ),  dwProcessId,  tn_sharedTex,  0  );
#define		M_getTexName_enc(  dwProcessId,  index_mosaic,  tn_sharedTex,  real_index,  tName,  cnt  )		_sntprintf(  tName,  cnt,  _T(  "qmste%d-%d-%d-%d"  ),  dwProcessId,  index_mosaic,  tn_sharedTex,  0  );
//
//#define		M_getTexName_dec(  dwProcessId,  tn_sharedTex,  real_index,  tName,  cnt  )		_sntprintf(  tName,  cnt,  _T(  "qmstd%d-%d-%d"  ),  dwProcessId,  tn_sharedTex,  real_index  );
#define		M_getTexName_dec(  dwProcessId,  tn_sharedTex,  real_index,  tName,  cnt  )		_sntprintf(  tName,  cnt,  _T(  "qmstd%d-%d-%d"  ),  dwProcessId,  tn_sharedTex,  0  );




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


//
//  下面这个结构的前一部分要跟PKT_sharedTex_info一样。否则要出错
typedef  struct  __pktSharedTexInfo1_t								{
				 DWORD												dwProcessId;
				 unsigned  int										tn;
				 unsigned  int										uiSeqNo;
				 unsigned  char										ucMaxCnt_sharedTexes;
				 //
				 BOOL												bTexShared;
				 //
				 unsigned  short									usMax_intervalInMs_renderFrame;
				 
				 //
				 HANDLE												m_sharedHandle_HW;
				 int												index_mosaic;

				 /////////////
				 
				 //
				 unsigned  __int64									dbg_ui64Id;
				 int												dbg_pts;			//  2024/10/01

}		 PKT_sharedTex_info1;



//  2015/10/06
#define		CONST_send_reqKey										0
#define		CONST_send_relKey										1							
//
#define		CONST_recv_reqKey										1
#define		CONST_recv_relKey										0							




#endif	//  }




