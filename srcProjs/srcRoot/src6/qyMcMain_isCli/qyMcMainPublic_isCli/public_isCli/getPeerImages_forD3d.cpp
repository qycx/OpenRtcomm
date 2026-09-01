

#include	"stdafx.h"

#include	<windowsx.h>
#include	<math.h>
#include	<time.h>
#include	<stddef.h>
#include	<ShellAPI.h>
#include	<tchar.h>

#include	"qymcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"
#include	"qyCusResTemp.h"

#include	"dlgTalkProc.h"




//
CAP_images* getLayoutPeerImages_forD3d(DLG_TALK_var* pMgrVar)
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	if (!isTalkerShadowMgr(pMgrVar->addr))  return  nullptr;

	CAP_images* pImgs = nullptr;

	//
	if  ( !pQyMc->appParams.bConfServer ) {
		pImgs = &pMgrVar->av.peerZone.images;
		return  pImgs;
	}


	//
	pImgs = &pProcInfo->av.confLayout.peerZone.images;

	//
#ifdef  __DEBUG__
	if (0) {
		pImgs = &pMgrVar->av.peerZone.images;
	}
#endif

	//
	return  pImgs;
}

//
CAP_images* getLayoutOtherImages_forD3d(DLG_TALK_var* pMgrVar)
{
	CCtxQyMc* pQyMc = g_pQyMc;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	if (!isTalkerShadowMgr(pMgrVar->addr))  return  nullptr;


	CAP_images* pImgs = nullptr;

	//
	if (!pQyMc->appParams.bConfServer) {
		pImgs = &pMgrVar->av.otherZone.images;
		return  pImgs;
	}


	//
	pImgs = &pProcInfo->av.confLayout.otherZone.images;

	//
#ifdef  __DEBUG__
	if (0) {
		pImgs = &pMgrVar->av.otherZone.images;
	}
#endif

	//
	return  pImgs;
}


