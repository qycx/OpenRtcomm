
#include	"stdafx.h"
#include	<math.h>
#include	<stddef.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"tmpCeLib.h"
#include	"qmcVideoCapture.h"
#include	"qyOpenShellCommon.h"
#include <qmcVideoCapture_isCli.h>

//
//  为3d渲染用的，不需要player等值
bool  isSame_layoutCapImages_forD3d(CAP_IMAGES* pImgs1, tmp_CAP_IMAGES* pImgs1_int, CAP_IMAGES* pImgs2, bool  bBreakIfNotSame, LPCTSTR  hint)
{
	int  iErr = -1;
	BOOL  bSame = FALSE;
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();

	if (!pImgs1 || !pImgs1_int || !pImgs2)  return  false;

	CAP_IMAGES& capImages = pImgs1_int->imgs;

	memset(&capImages, 0, sizeof(capImages));


	//
	CAP_IMAGES  tmp_imgs;
	tmp_imgs = *pImgs2;
	int  i;
	for (i = 0; i < mycountof(tmp_imgs.mems); i++) {
		tmp_imgs.mems[i].bResized = false;
	}
	pImgs2 = &tmp_imgs;


	//
	CAP_IMAGES* pImages1 = pImgs1;
	int  j;
	for (j = 0; j < mycountof(pImages1->mems); j++) {
		CAP_image* pCapImg = &pImages1->mems[j];
		//
		BOOL  bImgExists = FALSE;

		//
		//if  (  pImages->locations[j].rect.iW  )  bImgExists  =  TRUE;

		//
		if (!bImgExists) {

			//	
			if (pCapImg->iW_org
				&& pCapImg->iH_org
				&& pCapImg->iTaskId
				//&& isPlayerIndexValid(pProcInfo, pCapImg->playerId.index_player)
				)
			{
				bImgExists = TRUE;
			}
		}

		//
		if (!bImgExists)  continue;

		//
		CAP_IMAGE* pImg = &capImages.mems[capImages.head.usCnt];
		memcpy(pImg, pCapImg, sizeof(pImg[0]));
		//
		pImg->dwTickCnt_lastDrawing = 0;
		pImg->bNeedUpdated_doPost_drawCapImages = FALSE;
		//
		capImages.head.usCnt++;
	}
	//  2016/02/24
	capImages.head.ts_images = pImgs2->head.ts_images;
	
	//
	if (!memcmp(&capImages, pImgs2, sizeof(capImages))) {
		bSame = TRUE;
	}

	//
#ifdef  __DEBUG__
	if (!bSame) {
		int  ii;
		ii = 0;
		//
		if (bBreakIfNotSame) {
			int  ii = 0;
		}
		//
		if (memcmp(&capImages.head, &pImgs2->head, sizeof(capImages.head))) {
			ii = 1;
		}
		//
#if  0
		if (memcmp(&capImages.locations, &pImgs2->locations, sizeof(capImages.locations))) {
			ii = 2;
		}
#endif
		//
		if (memcmp(&capImages.mems, &pImgs2->mems, sizeof(capImages.mems))) {
			ii = 3;
			//
			int  i;
			for (i = 0; i < mycountof(capImages.mems); i++) {
				if (memcmp(&capImages.mems[i], &pImgs2->mems[i], sizeof(capImages.mems[i]))) {
					ii = 4;
				}
			}
		}
	}
#endif


	iErr = 0;

errLabel:

	if (!iErr) {
		//if  (  pbVal  )  *pbVal  =  bSame;
		return  bSame;
	}

	return  false;
}




 int refreshLayoutCapImages_forD3d(MIS_MSG_procVideo_qmc* pMsg, CAP_IMAGES* pImgs,  bool  *pbNeedRefreshImgs  )
{
	int  iErr = -1;
	bool  bNeedRefreshImgs = false;

	//
	int  i;

	//
	if (pMsg->idInfo_sender.ui64Id == 107) {
		int  ii = 0;
	}


	//
	do {

		CAP_image* pImg=nullptr;
		for (i = 0; i < mycountof(pImgs->mems); i++) {
			pImg = &pImgs->mems[i];
			if (pImg->idInfo_sender.ui64Id == pMsg->idInfo_sender.ui64Id
				&& pImg->uiTranNo_openAvDev == pMsg->uiTranNo_openAvDev)
			{
				break;
			}
		}
		if (i == mycountof(pImgs->mems)) {
			break;
		}
		//
		if (!isSame_playerId(&pImg->playerId, &pMsg->playerId)) {
#ifdef  __DEBUG__
			traceLog((TCHAR*)_T("refreshLayoutCapImages: img[%d].playId changed (%d,%d)->(%d,%d)"),
				i,
				pImg->playerId.index_player, pImg->playerId.uiTranNo_player, pMsg->playerId.index_player, pMsg->playerId.uiTranNo_player);
#endif

			//
			pImg->playerId = pMsg->playerId;
			bNeedRefreshImgs = true;
			//
		}
		if (pImg->usPktResType != pMsg->pkt.usPktResType) {
#ifdef  __DEBUG__
			traceLog((TCHAR*)_T("refreshLayoutCapImages: img[%d].pktType changed %d->%d"),
				i,
				(int)pImg->usPktResType, (int)pMsg->pkt.usPktResType);
#endif

			//
			pImg->usPktResType = pMsg->pkt.usPktResType;
			bNeedRefreshImgs = true;
			//
		}
		//
		pImg->dwTickCnt_lastDrawing = GetTickCount();

		//
		iErr = 0;
	} while (false);


errLabel:

	if (pbNeedRefreshImgs) {
		*pbNeedRefreshImgs = bNeedRefreshImgs;
	}

	//
	return  iErr;

}