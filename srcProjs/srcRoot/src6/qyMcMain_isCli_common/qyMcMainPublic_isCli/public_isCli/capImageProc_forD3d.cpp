
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
int  diff_imgs(CAP_IMAGES* p1, CAP_IMAGES* p2,LPCTSTR  hint)
{
	if (!hint)  hint = _T("");

	//
	if (p1->head.bResized != p2->head.bResized) {
		showInfo_open0(0, _T("diff_imgs"), _T("bResized"));
	}
	if (p1->head.cnt_needUpdated != p2->head.cnt_needUpdated) {
		showInfo_open0(0, _T("diff_imgs"), _T("cnt_needUpdated"));
	}
	if (p1->head.hWnd_src != p2->head.hWnd_src) {
		showInfo_open0(0, _T("diff_imgs"), _T("hWnd_src"));
	}
	if (p1->head.hWnd_notifyToDraw != p2->head.hWnd_notifyToDraw) {
		showInfo_open0(0, _T("diff_imgs"), _T("hWnd_notifyToDraw"));
	}
	//
	if  (  p1->head.lUserData!=p2->head.lUserData)  {
		showInfo_open0(0, _T("diff_imgs"), _T("lUserData"));
	}
	if (!timestamp_isSame(&p1->head.ts_images, &p2->head.ts_images)) {
		showInfo_open0(0, _T("diff_imgs"), _T("ts_images"));
	}
	if (p1->head.ts_images.dbg_iType != p2->head.ts_images.dbg_iType) {
		showInfo_open0(0, _T("diff_imgs"), _T("dbg_iType"));
	}
	if (p1->head.usCnt != p2->head.usCnt) {
		showInfo_open0(0, _T("diff_imgs"), _T("usCnt"));
	}
	else {
		int  i;
		TCHAR  tBuf[128];
		for (i = 0; i < p1->head.usCnt; i++) {
			CAP_IMAGE* pImg1 = &p1->mems[i];
			CAP_IMAGE* pImg2 = &p2->mems[i];
			//
			if (memcmp(pImg1, pImg2, sizeof(CAP_IMAGE))) {
				_sntprintf(tBuf, mycountof(tBuf), _T("imgs[%d]:"), i);
				showInfo_open0(0, _T("diff_imgs"), tBuf);
				//
				if (pImg1->iW_org != pImg2->iW_org) {
					showInfo_open0(0, _T("diff_img"), _T("iW_org"));
				}
				if (pImg1->iH_org != pImg2->iH_org) {
					showInfo_open0(0, _T("diff_img"), _T("iH_org"));
				}
				if (pImg1->iW_i != pImg2->iW_i) {
					showInfo_open0(0, _T("diff_img"), _T("iW_i"));
				}
				if (pImg1->iH_i != pImg2->iH_i) {
					showInfo_open0(0, _T("diff_img"), _T("iH_i"));
				}
				if (pImg1->iX_src_i != pImg2->iX_src_i) {
					showInfo_open0(0, _T("diff_img"), _T("iX_src_i"));
				}
				if (pImg1->iY_src_i != pImg2->iY_src_i) {
					showInfo_open0(0, _T("diff_img"), _T("iY_src_i"));
				}
				if (pImg1->iX_dst != pImg2->iX_dst) {
					showInfo_open0(0, _T("diff_img"), _T("iX_dst"));
				}
				if (pImg1->iY_dst != pImg2->iY_dst) {
					showInfo_open0(0, _T("diff_img"), _T("iY_dst"));
				}
				if (pImg1->iW_dst != pImg2->iW_dst) {
					showInfo_open0(0, _T("diff_img"), _T("iW_dst"));
				}
				if (pImg1->iH_dst != pImg2->iH_dst) {
					showInfo_open0(0, _T("diff_img"), _T("iH_dst"));
				}
				if (pImg1->idInfo_sender.ui64Id != pImg2->idInfo_sender.ui64Id) {
					showInfo_open0(0, _T("diff_img"), _T("idInfo_sender"));
				}
				if (pImg1->uiTranNo_openAvDev != pImg2->uiTranNo_openAvDev) {
					showInfo_open0(0, _T("diff_img"), _T("tn_openAvDev"));
				}
				if (pImg1->tn_a != pImg2->tn_a) {
					showInfo_open0(0, _T("diff_img"), _T("tn_a"));
				}
				if (pImg1->iTaskId != pImg2->iTaskId) {
					showInfo_open0(0, _T("diff_img"), _T("iTaskId"));
				}
				if (pImg1->usIndex_activeMems_from != pImg2->usIndex_activeMems_from) {
					showInfo_open0(0, _T("diff_img"), _T("usIndex_activeMems_from"));
				}
				if (pImg1->ucbUnresizable_srcInfo != pImg2->ucbUnresizable_srcInfo) {
					showInfo_open0(0, _T("diff_img"), _T("ucbUnresizable_srcInfo"));
				}
				if (!isSame_playerId(&pImg1->playerId, &pImg2->playerId)) {
					_sntprintf(tBuf, mycountof(tBuf), _T("playerId: 1(%I64u,index_player %d, tn %d). 2(%I64u,%d,%d). %s"),
						pImg1->idInfo_sender.ui64Id,
						pImg1->playerId.index_player, pImg1->playerId.uiTranNo_player,
						pImg2->idInfo_sender.ui64Id,
						pImg2->playerId.index_player, pImg2->playerId.uiTranNo_player,
						hint
					);
					
					//
					showInfo_open0(0, _T("diff_img"), tBuf);
				}
				if (pImg1->usPktResType != pImg2->usPktResType) {
					showInfo_open0(0, _T("diff_img"), _T("usPktResType"));				
				}
				if (pImg1->dwTickCnt_lastDrawing != pImg2->dwTickCnt_lastDrawing) {
					showInfo_open0(0, _T("diff_img"), _T("dwTickCnt_lastDrawing"));
				}
				if (pImg1->hWnd_remoteAv != pImg2->hWnd_remoteAv) {
					showInfo_open0(0, _T("diff_img"), _T("hWnd_remoteAv"));
				}
				if (pImg1->hDib != pImg2->hDib) {
					showInfo_open0(0, _T("diff_img"), _T("hDib"));
				}
				if (pImg1->hOffscreenDc != pImg2->hOffscreenDc) {
					showInfo_open0(0, _T("diff_img"), _T("hOffScreenDc"));
				}
				if (pImg1->hBitmap != pImg2->hBitmap) {
					showInfo_open0(0, _T("diff_img"), _T("hBitmap"));
				}
				if (pImg1->hOldBitmap != pImg2->hOldBitmap) {
					showInfo_open0(0, _T("diff_img"), _T("hOldBitmap"));
				}
				if (pImg1->bNeedUpdated_doPost_drawCapImages != pImg2->bNeedUpdated_doPost_drawCapImages) {
					showInfo_open0(0, _T("diff_img"), _T("bNeedUpdated_doPost_drawCapImages"));
				}
				if (pImg1->bResized != pImg2->bResized) {
					showInfo_open0(0, _T("diff_img"), _T("bResized"));
				}
				
			}
		  
		}
	}
	
	
	


	//
	return  0;
}

//
//  为3d渲染用的，不需要player等值
bool  isSame_layoutCapImages_forD3d(CAP_IMAGES* pImgs1, tmp_CAP_IMAGES* pImgs1_int, CAP_IMAGES* pImgs2, bool  bBreakIfNotSame,LPCTSTR  hint)
{
	int  iErr = -1;
	BOOL  bSame = FALSE;
	MC_VAR_isCli* pProcInfo = QY_GET_procInfo_isCli();

	//
	if (!hint)  hint = _T("");


	if (!pImgs1 || !pImgs1_int || !pImgs2)  return  false;

	CAP_IMAGES& capImages = pImgs1_int->imgs;

	//
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
			if  (  pCapImg->tn_a
				&&  pCapImg->iTaskId)  
			{ 
				bImgExists = true;
			}
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
		diff_imgs(&capImages, pImgs2,hint);


		//
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
			//
#ifdef  __DEBUG__
			TCHAR  tBuf[128];
			_sntprintf(tBuf,mycountof(tBuf),(TCHAR*)_T("refreshLayoutCapImages_forD3d: img[%d].%I64u,playId changed (%d,%d)->(%d,%d)"),
				i,
				pImg->idInfo_sender.ui64Id,
				pImg->playerId.index_player, pImg->playerId.uiTranNo_player, pMsg->playerId.index_player, pMsg->playerId.uiTranNo_player);
			showInfo_open0(0, 0, tBuf);
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