
#ifndef  __isFwPublic_h__
#define  __isFwPublic_h__	//  {

//
#ifdef SMCA_EXPORTS
#define SMCA_API __declspec(dllexport)
#else
#define SMCA_API __declspec(dllimport)
#endif



//
#include	"qyDefs_open.h"
#include	"mtSockDebugStatusInfo.h"


//
class  CtxFw_and;


//
//
#define		CONST_mtxName_andFw		"andFw"


//
typedef  struct {
	//
	char  ip[CONST_qyMaxIpLen + 1];

}		 AndIsFwCfgItem;


//
typedef  struct {
	unsigned  int		cnt;
	//
	AndIsFwCfgItem* pMems;


}		 AndIsFwCfg;





//
typedef  struct  __param_isFwFilterIp_t {
	void* p0;
	//
	MtSockDbgStatusInfo* pMtSockDbgStatusInfo;


}		 Param_isFwFilterIp;

//
typedef  struct  __isCliInfo_t {
	char  cliIp[CONST_qyMaxIpLen + 1];

}		 IsCliInfo;




//
//
extern  "C"  SMCA_API  int  hgFw_refeshCfg(CtxFw_and* pCtx);
extern  "C"  __declspec(dllexport)  int hgFw_filterIp(CtxFw_and* pCtx, Param_isFwFilterIp* pParam, void* p0, void* p1, IsCliInfo* pHgCliInfo);



//
//
extern  "C"  SMCA_API  CtxFw_and* andFw_newCtx();
extern  "C"  SMCA_API  void  andFw_freeCtx(CtxFw_and** pp);

//
extern  "C"  SMCA_API  int  andFw_init(CtxFw_and* pCtx);
extern  "C"  SMCA_API  int  andFw_exit(CtxFw_and* pCtx);
extern  "C"  SMCA_API  int  andFw_refeshCfg(CtxFw_and* pCtx);

//
extern "C" SMCA_API int andFw_filterIp(CtxFw_and* pCtx, Param_isFwFilterIp* pParam, void* p0, void* p1, IsCliInfo* pCliInfo);

//
//extern  "C"  SMCA_API int  contentFw_filterStream(CTX_stream2Data* pCtx, void* p0, void* p1, unsigned  int  uiStreamId, QY_CFGITEM_ntoh_U* pItem);








//
#endif  //  }


