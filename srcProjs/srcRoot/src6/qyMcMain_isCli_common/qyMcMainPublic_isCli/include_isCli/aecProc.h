

#ifndef  __aecProc_h__
#define  __aecProc_h__	//  {

#include	"aecPublic.h"

//
#if  0
typedef  struct  __aecObjInfo_t							{
				 AEC_player_cfg							cfg;
				 //
				 void						*			pObj;
}		 AEC_obj_info;
#endif

//
typedef  struct  __ctx_aec_t							{		//  2009/09/05				
				 CTX_MC_thread							common;

				 //
#if  0
				 AEC_layout								layout;
				 //
				 unsigned  short						usCnt_aecObjs;
				 AEC_obj_info							mems[CONST_cntof_aecPlayers];
#endif
				 //
				 void* pAecObj;
				 
}		  CTX_aec;





#endif  //  }



