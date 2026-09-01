


#ifndef  __wallMemInfoSync_h__
#define  __wallMemInfoSync_h__	//  {

//
#include	"wallMemTmpl.h"


//
typedef  struct  __wm_info_sync_t								{
				 //
				 CWallMemTmpl							*		pWmObj_internal;		//  2015/11/19	

				 //
				 int											index_d3dWnd;			//  2016/05/28
				 //
				 int											iGrpType;
				 int											index_wm;

				 //
				 WM_ID											wmId_parent;			//  2017/10/21

				 //
				 SYNC_mt_cnt									m_syncMtCnt2;
}		 WM_info_sync;



//
//
#define		D3D_wallMem_sync									WM_info_sync


//
#define		CONST_mtxName_syncWallMem							NULL		//  _T(  "syncWallMem"  )


//
//
class  CWLock_wmInfoSync: public CQySyncObj  {
public:
		int  wLock(  WM_info_sync  *  pWallMemSync,  LPCTSTR  hint  )  {
				if  (  !pWallMemSync  )  return  -1;				
				return  syncMtCnt_wLock_wait(  &pWallMemSync->m_syncMtCnt2,  CONST_mtxName_syncWallMem,  this,  NULL,  hint  );
		}

		//
		int  start(  WM_info_sync  *  pWallMemSync,  PF_getuiNextTranNo  pf_getuiNextTranNo  )  {
				if  (  !pWallMemSync  )  return  -1;
				return  syncMtCnt_start(  &pWallMemSync->m_syncMtCnt2,  pf_getuiNextTranNo  );
		}
};

//
class  CRLock_wmInfoSync: public CQySyncCnt  {
public:
		int  rLock(  WM_info_sync  *  pWallMemSync,  LPCTSTR  hint  )  {
				if  (  !pWallMemSync  )  return  -1;				
				return  syncMtCnt_rLock(  &pWallMemSync->m_syncMtCnt2,  this,  hint  );
		}
};


//  2016/02/06
typedef  struct  __wmZOrder_t									{
				 WM_ID											wmId;
				 //
				 float											fz;
}		 WM_zOrder;


//
//
typedef  struct  __wmGrpVar_t									{
				 int											iGrpType;
				 //
				 TCHAR											name[8];
				 //
				 unsigned  short								usMaxCnt_wmInfoSyncs;
				 WM_info_sync							*		pWmInfoSyncs;
				 //
				 BOOL											bUseZOrder;
				 WM_zOrder								*		pWmZOrders;

				 //
				 unsigned  short								usCnt_validWmObjs;

}		 WM_grp_var;


//  2015/12/10
typedef  struct  __wmGrpSync_t									{
				 WM_grp_var										m_var;

				 //
				 SYNC_mt_cnt									syncMtCnt;
}		 WM_grp_sync;



//
//  2014/11/05
D3D_wallMem_sync  *  getWmInfoSyncByIndex(  void  *  pD3D_context ,  WM_grp_sync  *  pGrp,  int  index  );


#endif  //  }





