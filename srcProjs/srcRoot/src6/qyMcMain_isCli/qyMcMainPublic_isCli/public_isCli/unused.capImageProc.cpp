

#include	"stdafx.h"
#include	<math.h>
#include	<stddef.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"tmpCeLib.h"
#include	"qmcVideoCapture.h"
#include	"qyOpenShellCommon.h"
#include	"qisD3dDefs.h"
#include	"isCliD3dPublic.h"


 //  2012/05/08
 void  exitCapSubWnds(  CAP_subWnds  *  p  )
{
	if  (  !p  )  return;
	MACRO_safeFree(  p->pMems  );
	p->usMaxCnt  =  0;
	return;
}


 int  initCapSubWnds(  unsigned  short  usMaxCnt,  CAP_subWnds  *  p  )
{
	int		iErr	=	-1;

	if  (  !usMaxCnt  )  return  -1;
	if  (  !p  )  return  -1;

	if  (  p->usMaxCnt  ||  p->pMems  )  return  -1;
	int  iSize;
	iSize  =  usMaxCnt  *  sizeof(  CAP_subWnd  );
	p->pMems  =  (  CAP_subWnd  *  )mymalloc(  iSize  );
	if  (  !p->pMems  )  goto  errLabel;
	memset(  p->pMems,  0,  iSize  );
	p->usMaxCnt  =  usMaxCnt;

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		exitCapSubWnds(  p  );
	}
	return  iErr;
}

 //  2012/05/08
int  registerSubWnd(  HWND  hWnd,  int  iWndContentType,  int  iWndContentSubType,  int  iTaskId,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  int  uiObjType,  unsigned  short  usIndex_obj,  CAP_subWnds  *  p,  int  *  pIndex_subWnd  )
{
	int		iErr	=	-1;
	int		i;

	if  (  !p  )  return  -1;
	if  (  !p->usMaxCnt  ||  !p->pMems  )  {
		return  -1;
	}
	if  (  !IsWindow(  hWnd  )  )  return  -1;

	for  (  i  =  0;  i  <  p->usMaxCnt;  i  ++  )  {
		 if  (  p->pMems[i].hWnd  ==  hWnd  )  {
			 iErr  =  0;  goto  errLabel;
		 }
	}
	for  (  i  =  0;  i  <  p->usMaxCnt;  i  ++  )  {
		 if  (  IsWindow(  p->pMems[i].hWnd  )  )  continue;
		 memset(  &p->pMems[i],  0,  sizeof(  p->pMems[i]  )  );
		 break;
	}
	if  (  i  ==  p->usMaxCnt  )  goto  errLabel;
	
	p->pMems[i].hWnd  =  hWnd;
	p->pMems[i].iWndContentType  =  iWndContentType;
	p->pMems[i].iWndContentSubType  =  iWndContentSubType;
	p->pMems[i].iTaskId  =  iTaskId;
	if  (  pIdInfo  )  p->pMems[i].idInfo.ui64Id  =  pIdInfo->ui64Id;
	p->pMems[i].uiObjType  =  uiObjType;
	p->pMems[i].usIndex_obj  =  usIndex_obj;
	
	iErr  =  0;
errLabel:
	if  (  !iErr  )  {
		if  (  pIndex_subWnd  )  *pIndex_subWnd  =  i;
	}
	if  (  iErr  )  {	//  2012/05/08
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "registerSubWnd failed"  )  );
	}

	return  iErr;
}

 int  closeSubWnds(  CAP_subWnds  *  p  )
{
	 int  i;		//  2009/09/07

	 if  (  !p  )  return  -1;
	 if  (  !p->usMaxCnt  ||  !p->pMems  )  {
		 return  -1;
	 }

	 //
	 for  (  i  =  0;  i  <  p->usMaxCnt;  i  ++  )  {
		  if  (  !IsWindow(  p->pMems[i].hWnd  )  )  continue;
		  ::SendMessage(  p->pMems[i].hWnd,  WM_CLOSE,  0,  0  );
	 }

	 return  0;
}


 //  2012/04/29
 HWND  findSubWnd(  CAP_subWnds  *  p,  int  iWndContentType,  int  iWndContentSubType  )
{
	HWND	hWnd	=	NULL;
	int		i;

	if  (  !p  )  return  NULL;
	if  (  !p->usMaxCnt  ||  !p->pMems  )  {
		return  NULL;
	}

	for  (  i  =  0;  i  <  p->usMaxCnt;  i  ++  )  {
		if  (  IsWindow(  p->pMems[i].hWnd  )  
			&&  p->pMems[i].iWndContentType  ==  iWndContentType
			&&  p->pMems[i].iWndContentSubType  ==  iWndContentSubType  )
		{
			hWnd  =  p->pMems[i].hWnd;
			break;
		}
	}

	return  hWnd;
}


 BOOL  bExists_capSubWnd(  CAP_subWnds  *  p  )
 {
	 BOOL	bRet	=	FALSE;

	 if  (  !p  )  return  FALSE;
	 if  (  !p->usMaxCnt  ||  !p->pMems  )  return  FALSE;

	 int  i;
	 for  (  i  =  0;  i  <  p->usMaxCnt;  i  ++  )  {
		 if  (  IsWindow(  p->pMems[i].hWnd  )  )  {
			 bRet  =  TRUE;
			 break;
		 }
	 }

	 return  bRet;
}



 ////////////////////////
 //  2014/04/06
 int getCnt_imgs(CAP_images* pImgs)
 {
	 int cnt;
	 int i;

	 int uiMaxCnt_imgMems = mycountof(pImgs->mems);
	 CAP_image* pImg;
	 void* pImgMems = &pImgs->mems;
	 int  uiSize_pImgMem = sizeof(CAP_image);

	 cnt = 0;
	 for (i = 0; i < uiMaxCnt_imgMems; i++) {
		 pImg = (CAP_IMAGE*)(((char*)pImgMems) + i * uiSize_pImgMem);	//  &pImages->mems[i];
		 if (pImg->iW_org && pImg->iH_org
			 && pImg->iTaskId)
		 {
			 cnt++;
		 }
	 }

	 return cnt;
 }



 //
   __declspec(  dllexport  )  int  new_myGetImageInfo(	unsigned  char  ucbFixedSize,			//  
					    unsigned  char	ucbAutoClip,											//  根据目标矩形自动裁剪，使目标矩形被充满
						unsigned  char  ucb3d,													//  3d显示用， 2014/11/14
						int  iW_org,  int  iH_org,  
						int  iX,  int  iY,  unsigned  int  iW,  unsigned  int  iH,  
						unsigned  int  *  piW_i,  unsigned  int  *  piH_i,
						int  *  piX_src_i,  int  *  piY_src_i,  
						int  *  piX_dst,  int  *  piY_dst,  unsigned  int  *  piW_dst,  unsigned  int  *  piH_dst  )
{
	TCHAR  tBuf[256];

	if  (  !piX_dst  ||  !piY_dst  ||  !piW_dst  ||  !piH_dst  )  return  -1;
	if  (  !iW_org  ||  !iH_org  )  return  -1;
	if  (  !iW  ||  !iH  )  {
		*piW_i  =  *piH_i  =  0;
		*piX_src_i  =  *piY_src_i  =  0;
		*piX_dst  =  *piY_dst  =  *piW_dst  =  *piH_dst  =  0;
		return  0;
	}

	if  (  ucbFixedSize  )  {					//  2??ü·?′ó??D?
		//
		*piW_i  =  iW_org;
		*piH_i  =  iH_org;
		//
		if  (  iW_org  >  (  int  )iW  )  *piX_dst  =  0;  
		else  *piX_dst  =  iX  +  (  iW  -  iW_org  )  /  2;
		
		if  (  iH_org  >  (  int  )iH  )  *piY_dst  =  0;  
		else  *  piY_dst  =  iY  +  (  iH  -  iH_org  )  /  2;
		//
		*piX_src_i  =  *piY_src_i  =  0;		
		//
		*piW_dst  =  iW_org;
		*piH_dst  =  iH_org;

		return  0;
	}


	//
	if  (  0  &&  ucbAutoClip  )  {

		//  2014/04/11
		
		//
		double	ff;
		int		n;
		//int		nUnit  =  8;	//  16;

		//
		*piW_dst  =  iW;
		*piH_dst  =  iH;
		//		
		if  (  iW  >=  *piW_dst  )  *piX_dst  =  iX  +  (  iW  -  *piW_dst  )  /  2;
		else  *piX_dst  =  iX;
		if  (  iH  >=  *piH_dst  )  *piY_dst  =  iY  +  (  iH  -  *piH_dst  )  /  2;
		else  *piY_dst  =  iY;

		//
		if  (  !*piH_dst  )  return  -1;
		
		//
		ff  =  *piW_dst  /  (  *piH_dst  *  1.  );
		if  (  iW_org  /  (  iH_org  *  1.  )  >  ff  )  {
			//
			*piH_i  =  *piH_dst;
			*piW_i  =  *piH_i  *  iW_org  /  (  1.0  *  iH_org  );
			
			//
			*piX_src_i  =  (  *piW_i  -  *piW_dst  )  /  2;
			*piY_src_i  =  0;

#if  0
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "src:(%d,%d)%dX%d, dst:(%d,%d)%dX%d, org:%dX%d, zone:(%d,%d)%dX%d"  ),  *piX_src,  *piY_src,  *piW_src,  *piH_src,  *piX_dst,  *piY_dst,  *piW_dst,  *piH_dst,  iW_org,  iH_org,  iX,  iY,  iW,  iH  );
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );
#endif
			//
			return  0;
		}
		//
		*piW_i  =  *piW_dst;
		*piH_i  =  *piW_i  *  iH_org  /  (  1.0  *  iW_org  );
		//
		*piX_src_i  =  0;
		*piY_src_i  =  (  *piH_i  -  *piH_dst  )  /  2;

		//
#if  0
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "src:(%d,%d)%dX%d, dst:(%d,%d)%dX%d, org:%dX%d, zone:(%d,%d)%dX%d"  ),  *piX_src,  *piY_src,  *piW_src,  *piH_src,  *piX_dst,  *piY_dst,  *piW_dst,  *piH_dst,  iW_org,  iH_org,  iX,  iY,  iW,  iH  );
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "%s"  ),  tBuf  );
#endif
		//
		return  0;
	}

	double	f;
	
	//
	f  =  iW_org  /  (  iH_org  *  1.  );
	if  (  f  *  iH  >  iW  )  {				//  ì??-
		//
		int  tmp_iW  =  iW;
		if  (  !ucb3d  )  {
			//tmp_iW  =  tmp_iW  /  4  *  4;
			//tmp_iW  =  tmp_iW  /  4  *  4;
		}
		//
		*piX_src_i  =  *piY_src_i  =  0;		
		*piW_i  =  tmp_iW;
		*piH_i  =  tmp_iW  /  f;			//  iW  /  f;
		//
		*piW_dst  =  *piW_i;	//  iW;
		*piH_dst  =  *piH_i;	//  (  int  )(  iW  /  f  );
		*piX_dst  =  (  int  )(  iX  +  (  iW  -  *piW_dst  )  /  2.  );
		*piY_dst  =  (  int  )(  iY  +  (  iH  -  *piH_dst  )  /  2.  );
		return  0;
	}

	//
	*piX_src_i  =  *piY_src_i  =  0;				
	*piH_i  =  iH;
	*piW_i  =  iH  *  f;
	//  ì??í
	*piH_dst  =  iH;
	*piW_dst  =  (  int  )(  iH  *  f  );
	*piY_dst  =  iY;
	*piX_dst  =  (  int  )(  iX  +  (  iW  -  *piW_dst  )  /  2.  );

	return  0;
}







 //
__declspec(  dllexport  )  int  new_getCapImagesFunc(  unsigned  char  ucbAutoClip,  unsigned  char  ucb3d,  int  iX_desc,  int  iY_desc,  int  iW_desc,  int  iH_desc,  PARAM_getCapImages  *  pParam,  CAP_images_head  *  pImgsHead,  CAP_IMAGE  *  pImgMems,  int  uiSize_pImgMem,  unsigned  int  uiMaxCnt_imgMems  )
{
	 int					iErr	=	-1;
	 int					i;
	 CAP_IMAGE			*	pImg;
	 int					cnt;
	 int					iRows;
	 int  iX,  iY,  iW,  iH;
	 //	
	 unsigned  int  iW_i,  iH_i;
	 int  iX_src_i,  iY_src_i;
	 int  iX_dst,  iY_dst;					
	 unsigned  int  iW_dst,  iH_dst;
	 
	 //
	 if  (  !pParam  )  return  -1;

	 //
	 int  tmp_iW_org  =  16;
	 int  tmp_iH_org  =  9;


	 //
	 cnt  =  0;
	 for  (  i  =  0;  i  <  uiMaxCnt_imgMems;  i  ++  )  {
		  pImg  =  (  CAP_IMAGE  *  )(  (  (  char  *  )pImgMems  )  +  i  *  uiSize_pImgMem  );	//  &pImages->mems[i];
		  if  (  pImg->iW_org  &&  pImg->iH_org  
			  &&  pImg->iTaskId  )  
		  {
			  cnt  ++  ;
		  }
	 }
	 
	 pImgsHead->usCnt  =  (  unsigned  short  )cnt;

	 //
	 if (pParam->pConfLayoutParam) {
		 //
#ifdef  __DEBUG__
		 //pParam->pConfLayoutParam->oneBigLayoutParam.ucbOneBigLayout = true;
#endif
		 //
		 //
		 if (pParam->pConfLayoutParam->enlargeParam.usEnlargeType == CONST_enlargeType_img
			 && pParam->pConfLayoutParam->enlargeParam.ui64Id
			 )
		 {			 
				 //
				 int					index = 0;

				 for (i = 0, index = 0; i < uiMaxCnt_imgMems && index < cnt; i++) {
					 pImg = (CAP_IMAGE*)(((char*)pImgMems) + i * uiSize_pImgMem);	//&pImages->mems[i];
					 if (!pImg->iW_org || !pImg->iH_org)  continue;

					 //
					 bool  bNeedEnlarge = false;
					 if (pParam->pConfLayoutParam->enlargeParam.ui64Id == pImg->idInfo_sender.ui64Id) {
						 bNeedEnlarge = true;
					 }

					 //
					 if (bNeedEnlarge) {

						 //
						 iW = iW_desc;
						 iH = iH_desc;
						 iX = iX_desc;// +index * iW;
						 iY = iY_desc;

						 //
						 //			  
						 new_myGetImageInfo(0, ucbAutoClip, ucb3d, tmp_iW_org, tmp_iH_org, iX, iY, iW, iH,
							 &iW_i, &iH_i, &iX_src_i, &iY_src_i,
							 &iX_dst, &iY_dst, &iW_dst, &iH_dst);

						 //		
						 iX = iX_dst;
						 iY = iY_dst;

						 if (iY == iY_dst) {
							 iX = iX + iW - iW_dst;
						 }
						 //
						 iW = iW_dst;
						 iH = iH_dst;
					 }
					 else  {
						 //
						 iW = 0;// iW_desc / 2.0;
						 iH = iH_desc;
						 iX = iX_desc + index * iW;
						 iY = iY_desc;
						 //
										 //
										 //			  
						 new_myGetImageInfo(0, ucbAutoClip, ucb3d, tmp_iW_org, tmp_iH_org, iX, iY, iW, iH,
							 &iW_i, &iH_i, &iX_src_i, &iY_src_i,
							 &iX_dst, &iY_dst, &iW_dst, &iH_dst);


						 //		
						 iX = iX_dst;
						 iY = iY_dst;

						 if (iY == iY_dst) {
							 //
							 iX = iX;
						 }
						 //
						 iW = iW_dst;
						 iH = iH_dst;

					 }


					 //
					 myGetImageInfo(0, ucbAutoClip, ucb3d, pImg->iW_org, pImg->iH_org, iX, iY, iW, iH,
						 &iW_i, &iH_i, &iX_src_i, &iY_src_i,
						 &iX_dst, &iY_dst, &iW_dst, &iH_dst);

					 if (pImg->iW_i != iW_i
						 || pImg->iH_i != iH_i
						 || pImg->iX_src_i != iX_src_i
						 || pImg->iY_src_i != iY_src_i
						 || pImg->iX_dst != iX_dst
						 || pImg->iY_dst != iY_dst
						 || pImg->iW_dst != iW_dst
						 || pImg->iH_dst != iH_dst
						 )
					 {
						 pImg->bResized = TRUE;

						 //
						 pImg->iW_i = iW_i;
						 pImg->iH_i = iH_i;
						 pImg->iX_src_i = iX_src_i;
						 pImg->iY_src_i = iY_src_i;
						 //
						 pImg->iX_dst = iX_dst;
						 pImg->iY_dst = iY_dst;
						 pImg->iW_dst = iW_dst;
						 pImg->iH_dst = iH_dst;
					 }
					 //  traceLog((TCHAR*)  _T(  "case is  2, index is %d,  pImg  iX  %d, iY %d, iW %d,iH %d"  ),  cnt,  pImg->iX,  pImg->iY,  pImg->iW,  pImg->iH  );

					 //
					 index++;
				 }

			
			 //
			 iErr = 0;  goto  errLabel;
		 }


		 if (pParam->pConfLayoutParam->oneBigLayoutParam.ucbOneBigLayout) {

			 //
			 int					index = 0;


			 //
			 if (cnt == 1) {

				 //
				 for (i = 0, index = 0; i < uiMaxCnt_imgMems && index < cnt; i++) {
					 pImg = (CAP_IMAGE*)(((char*)pImgMems) + i * uiSize_pImgMem);	//&pImages->mems[i];
					 if (!pImg->iW_org || !pImg->iH_org)  continue;

					 //
					 bool  bNeedEnlarge = false;
					 int   nEx_enlarge = 0;

#if 10
					 if (pImg->idInfo_sender.ui64Id == pParam->pConfLayoutParam->oneBigLayoutParam.ui64Id) {
						 bNeedEnlarge = true;
					 }
					 else {
						 //continue;
						 nEx_enlarge = 1;
					 }
#endif

					 //
					 float fw = 0.75;
					 float fh = 0.75;
					 int iw_0 = fw * iW_desc;
					 int ih_0 = fh * iH_desc;
					 int iw_1 = iW_desc / 4;
					 int ih_1 = iH_desc / 4;

					 //
#if 0
					 if (cnt == 1) {
						 iw_0 = iW_desc;
						 ih_0 = iH_desc;
						 iw_1 = 0;
						 ih_1 = 0;
					 }
#endif

					 //

					 //
					 if (bNeedEnlarge) {

						 //
						 iW = iw_0;
						 iH = ih_0;
						 iX = iX_desc;// +index * iW;
						 iY = iY_desc;

						 //
						 //			  
						 new_myGetImageInfo(0, ucbAutoClip, ucb3d, tmp_iW_org, tmp_iH_org, iX, iY, iW, iH,
							 &iW_i, &iH_i, &iX_src_i, &iY_src_i,
							 &iX_dst, &iY_dst, &iW_dst, &iH_dst);

						 //		
						 iX = iX_dst;
						 iY = iY_dst;

						 if (iY == iY_dst) {
							 iX = iX + iW - iW_dst;
						 }
						 //
						 iW = iW_dst;
						 iH = iH_dst;
					 }
					 else {
						 switch (index  +  nEx_enlarge) {

						 case  1:
							 //
							 iW = iw_1;// iW_desc / 2.0;
							 iH = ih_1;
							 iX = iX_desc + iw_0;
							 iY = iY_desc;
							 break;
						 case  2:
							 iW = iw_1;
							 iH = ih_1;
							 iX = iX_desc + iw_0;
							 iY = iY_desc + ih_1;
							 break;
						 case  3:
							 iW = iw_1;
							 iH = ih_1;
							 iX = iX_desc + iw_0;
							 iY = iY_desc + 2 * ih_1;
							 break;
						 case  4:
							 iW = iw_1;
							 iH = ih_1;
							 iX = iX_desc + iw_0;
							 iY = iY_desc + ih_0;
							 break;
						 case  5:
							 iW = iw_1;
							 iH = ih_1;
							 iX = iX_desc + 2 * iw_1;
							 iY = iY_desc + ih_0;
							 break;
						 case  6:
							 iW = iw_1;
							 iH = ih_1;
							 iX = iX_desc + iw_1;
							 iY = iY_desc + ih_0;
							 break;
						 case  7:
							 iW = iw_1;
							 iH = ih_1;
							 iX = iX_desc;
							 iY = iY_desc + ih_0;
							 break;

						 default:
							 //
							 iW = 0;// iW_desc / 2.0;
							 iH = iH_desc;
							 iX = iX_desc + (index) * iW;
							 iY = iY_desc;
							 break;
						 }

						 //					
						 //			  
						 new_myGetImageInfo(0, ucbAutoClip, ucb3d, tmp_iW_org, tmp_iH_org, iX, iY, iW, iH,
							 &iW_i, &iH_i, &iX_src_i, &iY_src_i,
							 &iX_dst, &iY_dst, &iW_dst, &iH_dst);


						 //		
						 iX = iX_dst;
						 iY = iY_dst;

						 if (iY == iY_dst) {
							 //
							 iX = iX;
						 }
						 //
						 iW = iW_dst;
						 iH = iH_dst;

					 }


					 //
					 myGetImageInfo(0, ucbAutoClip, ucb3d, pImg->iW_org, pImg->iH_org, iX, iY, iW, iH,
						 &iW_i, &iH_i, &iX_src_i, &iY_src_i,
						 &iX_dst, &iY_dst, &iW_dst, &iH_dst);

					 if (pImg->iW_i != iW_i
						 || pImg->iH_i != iH_i
						 || pImg->iX_src_i != iX_src_i
						 || pImg->iY_src_i != iY_src_i
						 || pImg->iX_dst != iX_dst
						 || pImg->iY_dst != iY_dst
						 || pImg->iW_dst != iW_dst
						 || pImg->iH_dst != iH_dst
						 )
					 {
						 pImg->bResized = TRUE;

						 //
						 pImg->iW_i = iW_i;
						 pImg->iH_i = iH_i;
						 pImg->iX_src_i = iX_src_i;
						 pImg->iY_src_i = iY_src_i;
						 //
						 pImg->iX_dst = iX_dst;
						 pImg->iY_dst = iY_dst;
						 pImg->iW_dst = iW_dst;
						 pImg->iH_dst = iH_dst;
					 }
					 //  traceLog((TCHAR*)  _T(  "case is  2, index is %d,  pImg  iX  %d, iY %d, iW %d,iH %d"  ),  cnt,  pImg->iX,  pImg->iY,  pImg->iW,  pImg->iH  );

					 //
					 index++;
				 }

				 //
				 iErr = 0;  goto  errLabel;

			 }  //  end of cnt ==  1

			 //
			 bool  bExists_enlarge = false;
			 //
			 for (i = 0, index = 0; i < uiMaxCnt_imgMems && index < cnt; i++) {
				 pImg = (CAP_IMAGE*)(((char*)pImgMems) + i * uiSize_pImgMem);	//&pImages->mems[i];
				 if (!pImg->iW_org || !pImg->iH_org)  continue;

				 //
				 bool  bNeedEnlarge = false;

				 if (pImg->idInfo_sender.ui64Id == pParam->pConfLayoutParam->oneBigLayoutParam.ui64Id) {
					 bNeedEnlarge = true;
					 //
					 bExists_enlarge = true;
				 }
				 else {
					 continue;
				 }

				 //
				 float fw = 0.75;
				 float fh = 0.75;
				 int iw_0 = fw * iW_desc;
				 int ih_0 = fh * iH_desc;
				 int iw_1 = iW_desc / 4;
				 int ih_1 = iH_desc / 4;

				 //
#if 0
				 if (cnt == 1) {
					 iw_0 = iW_desc;
					 ih_0 = iH_desc;
					 iw_1 = 0;
					 ih_1 = 0;
				 }
#endif

				 //
				 if (bNeedEnlarge) {

					 //
					 iW = iw_0;
					 iH = ih_0;
					 iX = iX_desc;// +index * iW;
					 iY = iY_desc;

					 //
					 //			  
					 new_myGetImageInfo(0, ucbAutoClip, ucb3d, tmp_iW_org, tmp_iH_org, iX, iY, iW, iH,
						 &iW_i, &iH_i, &iX_src_i, &iY_src_i,
						 &iX_dst, &iY_dst, &iW_dst, &iH_dst);

					 //		
					 iX = iX_dst;
					 iY = iY_dst;

					 if (iY == iY_dst) {
						 iX = iX + iW - iW_dst;
					 }
					 //
					 iW = iW_dst;
					 iH = iH_dst;
				 }
				 else {
					 switch (index) {

					 case  1:
						 //
						 iW = iw_1;// iW_desc / 2.0;
						 iH = ih_1;
						 iX = iX_desc + iw_0;
						 iY = iY_desc;
						 break;
					 case  2:
						 iW = iw_1;
						 iH = ih_1;
						 iX = iX_desc + iw_0;
						 iY = iY_desc + ih_1;
						 break;
					 case  3:
						 iW = iw_1;
						 iH = ih_1;
						 iX = iX_desc + iw_0;
						 iY = iY_desc + 2 * ih_1;
						 break;
					 case  4:
						 iW = iw_1;
						 iH = ih_1;
						 iX = iX_desc + iw_0;
						 iY = iY_desc + ih_0;
						 break;
					 case  5:
						 iW = iw_1;
						 iH = ih_1;
						 iX = iX_desc + 2 * iw_1;
						 iY = iY_desc + ih_0;
						 break;
					 case  6:
						 iW = iw_1;
						 iH = ih_1;
						 iX = iX_desc + iw_1;
						 iY = iY_desc + ih_0;
						 break;
					 case  7:
						 iW = iw_1;
						 iH = ih_1;
						 iX = iX_desc;
						 iY = iY_desc + ih_0;
						 break;

					 default:
						 //
						 iW = 0;// iW_desc / 2.0;
						 iH = iH_desc;
						 iX = iX_desc + index * iW;
						 iY = iY_desc;
						 break;
					 }

					 //					
					 //			  
					 new_myGetImageInfo(0, ucbAutoClip, ucb3d, tmp_iW_org, tmp_iH_org, iX, iY, iW, iH,
						 &iW_i, &iH_i, &iX_src_i, &iY_src_i,
						 &iX_dst, &iY_dst, &iW_dst, &iH_dst);


					 //		
					 iX = iX_dst;
					 iY = iY_dst;

					 if (iY == iY_dst) {
						 //
						 iX = iX;
					 }
					 //
					 iW = iW_dst;
					 iH = iH_dst;

				 }


				 //
				 myGetImageInfo(0, ucbAutoClip, ucb3d, pImg->iW_org, pImg->iH_org, iX, iY, iW, iH,
					 &iW_i, &iH_i, &iX_src_i, &iY_src_i,
					 &iX_dst, &iY_dst, &iW_dst, &iH_dst);

				 if (pImg->iW_i != iW_i
					 || pImg->iH_i != iH_i
					 || pImg->iX_src_i != iX_src_i
					 || pImg->iY_src_i != iY_src_i
					 || pImg->iX_dst != iX_dst
					 || pImg->iY_dst != iY_dst
					 || pImg->iW_dst != iW_dst
					 || pImg->iH_dst != iH_dst
					 )
				 {
					 pImg->bResized = TRUE;

					 //
					 pImg->iW_i = iW_i;
					 pImg->iH_i = iH_i;
					 pImg->iX_src_i = iX_src_i;
					 pImg->iY_src_i = iY_src_i;
					 //
					 pImg->iX_dst = iX_dst;
					 pImg->iY_dst = iY_dst;
					 pImg->iW_dst = iW_dst;
					 pImg->iH_dst = iH_dst;
				 }
				 //  traceLog((TCHAR*)  _T(  "case is  2, index is %d,  pImg  iX  %d, iY %d, iW %d,iH %d"  ),  cnt,  pImg->iX,  pImg->iY,  pImg->iW,  pImg->iH  );

				 //
				 index++;
			 }


			 //
			 int   nEx_enlarge = 0;
			 //if (!bExists_enlarge) 
			 {
				 nEx_enlarge = 1;
			 }

			 //
			 for (i = 0, index = 0; i < uiMaxCnt_imgMems && index < cnt; i++) {
				 pImg = (CAP_IMAGE*)(((char*)pImgMems) + i * uiSize_pImgMem);	//&pImages->mems[i];
				 if (!pImg->iW_org || !pImg->iH_org)  continue;

				 //
				 bool  bNeedEnlarge = false;
				 if (pImg->idInfo_sender.ui64Id == pParam->pConfLayoutParam->oneBigLayoutParam.ui64Id) {
					 bNeedEnlarge = true;
					 //
					 nEx_enlarge = 0;
					 index++;
					 continue;
				 }

				 //
				 float fw = 0.75;
				 float fh = 0.75;
				 int iw_0 = fw * iW_desc;
				 int ih_0 = fh * iH_desc;
				 int iw_1 = iW_desc / 4;
				 int ih_1 = iH_desc / 4;

				 //
				 if (cnt == 1) {
					 iw_0 = iW_desc;
					 ih_0 = iH_desc;
					 iw_1 = 0;
					 ih_1 = 0;
				 }

				 //
				 if (bNeedEnlarge) {

					 //
					 iW = iw_0;
					 iH = ih_0;
					 iX = iX_desc;// +index * iW;
					 iY = iY_desc;

					 //
					 //			  
					 new_myGetImageInfo(0, ucbAutoClip, ucb3d, tmp_iW_org, tmp_iH_org, iX, iY, iW, iH,
						 &iW_i, &iH_i, &iX_src_i, &iY_src_i,
						 &iX_dst, &iY_dst, &iW_dst, &iH_dst);

					 //		
					 iX = iX_dst;
					 iY = iY_dst;

					 if (iY == iY_dst) {
						 iX = iX + iW - iW_dst;
					 }
					 //
					 iW = iW_dst;
					 iH = iH_dst;
				 }
				 else {
					 switch (index  +  nEx_enlarge) {

					 case  1:
						 //
						 iW = iw_1;// iW_desc / 2.0;
						 iH = ih_1;
						 iX = iX_desc + iw_0;
						 iY = iY_desc;
						 break;
					 case  2:
						 iW = iw_1;
						 iH = ih_1;
						 iX = iX_desc + iw_0;
						 iY = iY_desc + ih_1;
						 break;
					 case  3:
						 iW = iw_1;
						 iH = ih_1;
						 iX = iX_desc + iw_0;
						 iY = iY_desc + 2 * ih_1;
						 break;
					 case  4:
						 iW = iw_1;
						 iH = ih_1;
						 iX = iX_desc + iw_0;
						 iY = iY_desc + ih_0;
						 break;
					 case  5:
						 iW = iw_1;
						 iH = ih_1;
						 iX = iX_desc + 2 * iw_1;
						 iY = iY_desc + ih_0;
						 break;
					 case  6:
						 iW = iw_1;
						 iH = ih_1;
						 iX = iX_desc + iw_1;
						 iY = iY_desc + ih_0;
						 break;
					 case  7:
						 iW = iw_1;
						 iH = ih_1;
						 iX = iX_desc;
						 iY = iY_desc + ih_0;
						 break;

					 default:
						 //
						 iW = 0;// iW_desc / 2.0;
						 iH = iH_desc;
						 iX = iX_desc + index * iW;
						 iY = iY_desc;
						 break;
					 }

					 //					
					 //			  
					 new_myGetImageInfo(0, ucbAutoClip, ucb3d, tmp_iW_org, tmp_iH_org, iX, iY, iW, iH,
						 &iW_i, &iH_i, &iX_src_i, &iY_src_i,
						 &iX_dst, &iY_dst, &iW_dst, &iH_dst);


					 //		
					 iX = iX_dst;
					 iY = iY_dst;

					 if (iY == iY_dst) {
						 //
						 iX = iX;
					 }
					 //
					 iW = iW_dst;
					 iH = iH_dst;

				 }


				 //
				 myGetImageInfo(0, ucbAutoClip, ucb3d, pImg->iW_org, pImg->iH_org, iX, iY, iW, iH,
					 &iW_i, &iH_i, &iX_src_i, &iY_src_i,
					 &iX_dst, &iY_dst, &iW_dst, &iH_dst);

				 if (pImg->iW_i != iW_i
					 || pImg->iH_i != iH_i
					 || pImg->iX_src_i != iX_src_i
					 || pImg->iY_src_i != iY_src_i
					 || pImg->iX_dst != iX_dst
					 || pImg->iY_dst != iY_dst
					 || pImg->iW_dst != iW_dst
					 || pImg->iH_dst != iH_dst
					 )
				 {
					 pImg->bResized = TRUE;

					 //
					 pImg->iW_i = iW_i;
					 pImg->iH_i = iH_i;
					 pImg->iX_src_i = iX_src_i;
					 pImg->iY_src_i = iY_src_i;
					 //
					 pImg->iX_dst = iX_dst;
					 pImg->iY_dst = iY_dst;
					 pImg->iW_dst = iW_dst;
					 pImg->iH_dst = iH_dst;
				 }
				 //  traceLog((TCHAR*)  _T(  "case is  2, index is %d,  pImg  iX  %d, iY %d, iW %d,iH %d"  ),  cnt,  pImg->iX,  pImg->iY,  pImg->iW,  pImg->iH  );

				 //
				 index++;
			 }


			 //
			 iErr = 0;  goto  errLabel;
		 }



		 //
	 }


	 //  2013/08/18
	 if  (  cnt  ==  2  )  {
		 iRows  =  1;

		 int					index  =  0;	 

		 for  (  i  =  0,index = 0;  i  <  uiMaxCnt_imgMems  &&  index  <  cnt;  i  ++  )  {
				pImg =  (  CAP_IMAGE  *  )(  (  (  char  *  )pImgMems  )  +  i  *  uiSize_pImgMem  );	//&pImages->mems[i];
				if  (  !pImg->iW_org  ||  !pImg->iH_org  )  continue;

				//
				switch  (  index  )  {
						case  0:

							   //
							   iW  =  iW_desc  /  2.0;
							   iH  =  iH_desc;
							   iX  =  iX_desc  +  index  *  iW;
							   iY  =  iY_desc;

							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

							   //		
							   iX  =  iX_dst;								
							   iY  =  iY_dst;
		
							   if  (  iY  ==  iY_dst  )  {
								   iX  =  iX  +  iW  -  iW_dst;  
							   }
							   //
							   iW  =  iW_dst;
							   iH  =  iH_dst;

							   break;
						case  1:
							   //
							   iW  =  iW_desc  /  2.0;
							   iH  =  iH_desc;
							   iX  =  iX_desc  +  index  *  iW;
							   iY  =  iY_desc;
			   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

		
							   //		
							   iX  =  iX_dst;								
							   iY  =  iY_dst;
		
							   if  (  iY  ==  iY_dst  )  {
									 //
									 iX  =  iX;
							   }
							   //
							   iW  =  iW_dst;							   	
							   iH  =  iH_dst;

							   //
							   break;


				
				}


				//
				myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  pImg->iW_org,  pImg->iH_org,  iX,  iY,  iW,  iH,
									&iW_i,  &iH_i,  &iX_src_i,  &iY_src_i, 
									  &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );
								
				if  (  pImg->iW_i  !=  iW_i
					||  pImg->iH_i  !=  iH_i
					||  pImg->iX_src_i  !=  iX_src_i
					||  pImg->iY_src_i  !=  iY_src_i
					||  pImg->iX_dst  !=  iX_dst				
					||  pImg->iY_dst  !=  iY_dst
					||  pImg->iW_dst  !=  iW_dst
					||  pImg->iH_dst  !=  iH_dst
					)				
				{
						  pImg->bResized  =  TRUE;
						  
						  //
						  pImg->iW_i  =  iW_i;
						  pImg->iH_i  =  iH_i;
						  pImg->iX_src_i  =  iX_src_i;
						  pImg->iY_src_i  =  iY_src_i;
						  //
						  pImg->iX_dst  =  iX_dst;				  
						  pImg->iY_dst  =  iY_dst;
						  pImg->iW_dst  =  iW_dst;
						  pImg->iH_dst  =  iH_dst;					  
				}
				//  traceLog((TCHAR*)  _T(  "case is  2, index is %d,  pImg  iX  %d, iY %d, iW %d,iH %d"  ),  cnt,  pImg->iX,  pImg->iY,  pImg->iW,  pImg->iH  );
				
				//
				index  ++  ;
		 }

		 //
		 iErr  =  0;  goto  errLabel;
	 }
	 if  (  cnt  ==  3  )  {
		 iRows  =  2;
		 int  index  =  0,  iRow  =  0,  iCol  =  0;  
		 //int  iX,  iY,  iW,  iH;
		 
		 for  (  i  =  0,index = 0;  i  <  uiMaxCnt_imgMems  &&  index  <  cnt;  i  ++  )  {
				pImg =  (  CAP_IMAGE  *  )(  (  (  char  *  )pImgMems  )  +  i  *  uiSize_pImgMem  );	//  &pImages->mems[i];
				if  (  !pImg->iW_org  ||  !pImg->iH_org  )  continue;
				//
				switch  (  index  )  {
						case  0:
							   iW  =  iW_desc;
							   iH  =  iH_desc  /  2;
							   iX  =  iX_desc;
							   iY  =  iY_desc;
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

							   //
							   if  (  iX  ==  iX_dst  )  {
								   iY  =  iY  +  iH  -  iH_dst;  
								   }
							   else  {
									 //
									 iX  =  iX_dst;
									 iY  =  iY_dst;
							   }
							   //
							   iW  =  iW_dst;
							   iH  =  iH_dst;

							   break;
						case  1:
							   iW  =  iW_desc  /  2;
							   iH  =  iH_desc  /  2.0;
							   iX  =  iX_desc;
							   iY  =  iY_desc  +  iH_desc  /  2;
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );


							   if  (  iY  ==  iY_dst  )  {
									 //
							   	     iX  =  iX  +  iW  -  iW_dst;
							   }
							   //
							   //
							   iW  =  iW_dst;							   	
							   iH  =  iH_dst;

							   //
							   break;
						case  2:
							   iW  =  iW_desc  /  2;
							   iH  =  iH_desc  /  2.0;
							   iX  =  iX_desc  +  iW_desc  /  2;
							   iY  =  iY_desc  +  iH_desc  /  2.0;
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );


							   if  (  iY  ==  iY_dst  )  {
							   }
							   //
							   iW  =  iW_dst;							   	
							   iH  =  iH_dst;

							   break;
						default:
								goto  errLabel;
				}



				//
				myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  pImg->iW_org,  pImg->iH_org,  iX,  iY,  iW,  iH,  
									&iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,									  
									  &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );				

				if  (  pImg->iW_i  !=  iW_i
					||  pImg->iH_i  !=  iH_i
					||  pImg->iX_src_i  !=  iX_src_i
					||  pImg->iY_src_i  !=  iY_src_i
					||  pImg->iX_dst  !=  iX_dst				
					||  pImg->iY_dst  !=  iY_dst
					||  pImg->iW_dst  !=  iW_dst
					||  pImg->iH_dst  !=  iH_dst
					)				
				{
						  pImg->bResized  =  TRUE;
						  
						  //
						  pImg->iW_i  =  iW_i;
						  pImg->iH_i  =  iH_i;
						  pImg->iX_src_i  =  iX_src_i;
						  pImg->iY_src_i  =  iY_src_i;
						  //
						  pImg->iX_dst  =  iX_dst;				  
						  pImg->iY_dst  =  iY_dst;
						  pImg->iW_dst  =  iW_dst;
						  pImg->iH_dst  =  iH_dst;					  
				}

				//  traceLog((TCHAR*)  _T(  "case is  3, index is %d,  pImg  iX  %d, iY %d, iW %d,iH %d"  ),  index,  pImg->iX,  pImg->iY,  pImg->iW,  pImg->iH  );
				
				index  ++  ;
		 }

		 iErr  =  0;  goto  errLabel;
	 }

	 if  (  cnt  ==  4  )
	 {
		 iRows  =  2;
		 int  index  =  0,  iRow  =  0,  iCol  =  0;  
		 //int  iX,  iY,  iW,  iH;
		 
		 for  (  i  =  0,index = 0;  i  <  uiMaxCnt_imgMems  &&  index  <  cnt;  i  ++  )  {
				pImg =  (  CAP_IMAGE  *  )(  (  (  char  *  )pImgMems  )  +  i  *  uiSize_pImgMem  );	//  &pImages->mems[i];
				if  (  !pImg->iW_org  ||  !pImg->iH_org  )  continue;
				//
				switch  (  index  )  {
						case  0:
							   iW  =  iW_desc  /  2;
							   iH  =  iH_desc  /  2;
							   iX  =  iX_desc;
							   iY  =  iY_desc;
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

							   //
							   if  (  iX  ==  iX_dst  )  {
								   iY  =  iY  +  iH  -  iH_dst;  
								   }
							   else  {
									 //
									 iX  =  iX  +  iW  -  iW_dst;
									 iY  =  iY_dst;
							   }
							   //
							   iW  =  iW_dst;
							   iH  =  iH_dst;

							   break;
						case  1:
							   iW  =  iW_desc  /  2;
							   iH  =  iH_desc  /  2.0;
							   iX  =  iX_desc  +  iW_desc  /  2;
							   iY  =  iY_desc;
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

							   //
							   if  (  iX  ==  iX_dst  )  {
									 //
							   	     iX  =  iX_dst;
							   		 //iY  =  iY_dst;
									 iY  =  iY  +  iH  -  iH_dst;
							   }


							   //
							   iW  =  iW_dst;							   	
							   iH  =  iH_dst;

							   //
							   break;
						case  2:
							   iW  =  iW_desc  /  2;
							   iH  =  iH_desc  /  2.0;
							   iX  =  iX_desc;
							   iY  =  iY_desc  +  iH_desc  /  2.0;
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

							   
							   if  (  iY  ==  iY_dst  )  {
								   iX  =  iX  +  iW  -  iW_dst;
								   iY  =  iY_dst;
							   }
							   //
							   iW  =  iW_dst;							   	
							   iH  =  iH_dst;


							   break;
						case  3:
							   iW  =  iW_desc  /  2;
							   iH  =  iH_desc  /  2.0;
							   iX  =  iX_desc  +  iW_desc  /  2;
							   iY  =  iY_desc  +  iH_desc  /  2.0;
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

							   //
							   iW  =  iW_dst;							   	
							   iH  =  iH_dst;

							   if  (  iY  ==  iY_dst  )  {
								   iX  =  iX_dst;
								   iY  =  iY_dst;
							   }

							   break;
						default:
								goto  errLabel;
				}



				//
				myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  pImg->iW_org,  pImg->iH_org,  iX,  iY,  iW,  iH,  
									&iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,									  
									  &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );				

				if  (  pImg->iW_i  !=  iW_i
					||  pImg->iH_i  !=  iH_i
					||  pImg->iX_src_i  !=  iX_src_i
					||  pImg->iY_src_i  !=  iY_src_i
					||  pImg->iX_dst  !=  iX_dst				
					||  pImg->iY_dst  !=  iY_dst
					||  pImg->iW_dst  !=  iW_dst
					||  pImg->iH_dst  !=  iH_dst
					)				
				{
						  pImg->bResized  =  TRUE;
						  
						  //
						  pImg->iW_i  =  iW_i;
						  pImg->iH_i  =  iH_i;
						  pImg->iX_src_i  =  iX_src_i;
						  pImg->iY_src_i  =  iY_src_i;
						  //
						  pImg->iX_dst  =  iX_dst;				  
						  pImg->iY_dst  =  iY_dst;
						  pImg->iW_dst  =  iW_dst;
						  pImg->iH_dst  =  iH_dst;					  
				}

				//  traceLog((TCHAR*)  _T(  "case is  3, index is %d,  pImg  iX  %d, iY %d, iW %d,iH %d"  ),  index,  pImg->iX,  pImg->iY,  pImg->iW,  pImg->iH  );
				
				index  ++  ;
		 }

		 iErr  =  0;  goto  errLabel;
	 }

	 if  ( cnt  ==  5  ) {
		 iRows  =  2;
		 int  index  =  0,  iRow  =  2,  iCol  =  3;  
		 //int  iX,  iY,  iW,  iH;
		 
		 for  (  i  =  0,index = 0;  i  <  uiMaxCnt_imgMems  &&  index  <  cnt;  i  ++  )  {
				pImg =  (  CAP_IMAGE  *  )(  (  (  char  *  )pImgMems  )  +  i  *  uiSize_pImgMem  );	//  &pImages->mems[i];
				if  (  !pImg->iW_org  ||  !pImg->iH_org  )  continue;
				//
				switch  (  index  )  {
						case  0:
							   iW  =  iW_desc  /  2;
							   iH  =  iH_desc  /  2;
							   iX  =  iX_desc;
							   iY  =  iY_desc;
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

							   //
							   if  (  iX  ==  iX_dst  )  {
								   iY  =  iY  +  iH  -  iH_dst;  
								   }
							   else  {
									 //
									 iX  =  iX  +  iW  -  iW_dst;
									 //iY  =  iY_dst;
							   }
							   //
							   iW  =  iW_dst;
							   iH  =  iH_dst;

							   break;
						case  1:
							   iW  =  iW_desc  /  2;
							   iH  =  iH_desc  /  2.0;
							   iX  =  iX_desc  +  iW_desc  /  2;
							   iY  =  iY_desc;
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

							   //
							   if  (  iX  ==  iX_dst  )  {
									 //
							   	     iX  =  iX_dst;
							   		 //iY  =  iY_dst;
									 iY  =  iY  +  iH  -  iH_dst;
							   }
							   else  {
								     //iX  =  iX  +  iW  *  3  /  2  -  iW_dst  /  2;
							   }


							   //
							   iW  =  iW_dst;							   	
							   iH  =  iH_dst;

							   //
							   break;
						case  2:
							   iW  =  iW_desc  /  3;
							   iH  =  iH_desc  /  2.0;
							   iX  =  iX_desc;
							   iY  =  iY_desc  +  iH_desc  /  2.0;
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

							   
							   if  (  iY  ==  iY_dst  )  {
								   iX  =  iX  +  iW  *  3  /  2  -  iW_dst  *  3  /  2;
								   iY  =  iY_dst;
							   }
							   else  {
								     //iX  =  iX  +  iW  *  3  /  2  +  iW_dst  /  2;
							   }
							   //
							   iW  =  iW_dst;							   	
							   iH  =  iH_dst;


							   break;
						case  3:
							   iW  =  iW_desc  /  3;
							   iH  =  iH_desc  /  2.0;
							   iX  =  iX_desc  +  iW_desc  /  3;
							   iY  =  iY_desc  +  iH_desc  /  2.0;
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );


							   if  (  iY  ==  iY_dst  )  {
								   iX  =    iX  +  iW  /  2  -  iW_dst  /  2;
								   iY  =  iY_dst;
							   }
							   //
							   iW  =  iW_dst;							   	
							   iH  =  iH_dst;


							   break;
						case  4:
							   iW  =  iW_desc  /  3;
							   iH  =  iH_desc  /  2.0;
							   iX  =  iX_desc  +  iW_desc  /  3 * 2;
							   iY  =  iY_desc  +  iH_desc  /  2.0;
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );


							   if  (  iY  ==  iY_dst  )  {
								   iX  =  iX  -  iW  /  2  +  iW_dst  /  2;
								   iY  =  iY_dst;
							   }
							   //
							   iW  =  iW_dst;							   	
							   iH  =  iH_dst;


							   break;
						default:
								goto  errLabel;
				}



				//
				myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  pImg->iW_org,  pImg->iH_org,  iX,  iY,  iW,  iH,  
									&iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,									  
									  &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );				

				if  (  pImg->iW_i  !=  iW_i
					||  pImg->iH_i  !=  iH_i
					||  pImg->iX_src_i  !=  iX_src_i
					||  pImg->iY_src_i  !=  iY_src_i
					||  pImg->iX_dst  !=  iX_dst				
					||  pImg->iY_dst  !=  iY_dst
					||  pImg->iW_dst  !=  iW_dst
					||  pImg->iH_dst  !=  iH_dst
					)				
				{
						  pImg->bResized  =  TRUE;
						  
						  //
						  pImg->iW_i  =  iW_i;
						  pImg->iH_i  =  iH_i;
						  pImg->iX_src_i  =  iX_src_i;
						  pImg->iY_src_i  =  iY_src_i;
						  //
						  pImg->iX_dst  =  iX_dst;				  
						  pImg->iY_dst  =  iY_dst;
						  pImg->iW_dst  =  iW_dst;
						  pImg->iH_dst  =  iH_dst;					  
				}

				//  traceLog((TCHAR*)  _T(  "case is  3, index is %d,  pImg  iX  %d, iY %d, iW %d,iH %d"  ),  index,  pImg->iX,  pImg->iY,  pImg->iW,  pImg->iH  );
				
				index  ++  ;
		 }

		 iErr  =  0;  goto  errLabel;
	 } 


	 //  2015/06/20
	 if  (  cnt  ==  6  )  {
		 iRows  =  2;
		 int  index  =  0,  iRow  =  0,  iCol  =  3;  
		 
		 for  (  i  =  0,index = 0;  i  <  uiMaxCnt_imgMems  &&  index  <  cnt;  i  ++  )  {
				pImg =  (  CAP_IMAGE  *  )(  (  (  char  *  )pImgMems  )  +  i  *  uiSize_pImgMem  );	//  &pImages->mems[i];
				if  (  !pImg->iW_org  ||  !pImg->iH_org  )  continue;

				int  iW_average  =  iW_desc  *  0.33;
				int  iH_half  =  iH_desc  /  2.0;
					 
				switch  (  index  )  {
						case  0:
							   iW  =  iW_desc  /  3;
							   iH  =  iH_desc  /  2;
							   iX  =  iX_desc;
							   iY  =  iY_desc;
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

							   //
							   if  (  iX  ==  iX_dst  )  {
								   iY  =  iY  +  iH  -  iH_dst;  
								   }
							   else  {
									 //
									 iX  =  iX  +  iW  *  3  /  2   -  iW_dst  *  3  /  2;
									 iY  =  iY_dst;
							   }
							   //
							   iW  =  iW_dst;
							   iH  =  iH_dst;

							   break;
						case  1:
							   iW  =  iW_desc  /  3;
							   iH  =  iH_desc  /  2.0;
							   iX  =  iX_desc  +  iW_desc  /  3;
							   iY  =  iY_desc;
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

							   //
							   if  (  iX  ==  iX_dst  )  {
									 //
							   	     iX  =  iX_dst;
							   		 //iY  =  iY_dst;
									 iY  =  iY  +  iH  -  iH_dst;
							   }
							   else  {
								     iX  =  iX  +  iW  /  2  -  iW_dst  /  2;
							   }


							   //
							   iW  =  iW_dst;							   	
							   iH  =  iH_dst;

							   //
							   break;
						case  2:
							   iW  =  iW_desc  /  3;
							   iH  =  iH_desc  /  2.0;
							   iX  =  iX_desc  +  iW_desc  /  3  *  2;
							   iY  =  iY_desc;
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

							   //
							   if  (  iX  ==  iX_dst  )  {
									 //
							   	     iX  =  iX_dst;
							   		 //iY  =  iY_dst;
									 iY  =  iY  +  iH  -  iH_dst;
							   }
							   else  {
								     iX  =  iX  -  iW  /  2  +  iW_dst  /  2;
							   }


							   //
							   iW  =  iW_dst;							   	
							   iH  =  iH_dst;

							   //
							   break;
						case  3:
							   iW  =  iW_desc  /  iCol;
							   iH  =  iH_desc  /  2.0;
							   iX  =  iX_desc;
							   iY  =  iY_desc  +  iH_desc  /  2.0;
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

							   
							   if  (  iY  ==  iY_dst  )  {
								   iX  =  iX  +  iW  *  3  /  2  -  iW_dst  *  3  /  2;
								   iY  =  iY_dst;
							   }
							   //
							   iW  =  iW_dst;							   	
							   iH  =  iH_dst;


							   break;
						case  4:
							   iW  =  iW_desc  /  iCol;
							   iH  =  iH_desc  /  2.0;
							   iX  =  iX_desc  +  iW_desc  /  iCol;
							   iY  =  iY_desc  +  iH_desc  /  2.0;
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );


							   if  (  iY  ==  iY_dst  )  {
								   iX  =    iX  +  iW  /  2  -  iW_dst  /  2;
								   iY  =  iY_dst;
							   }
							   //
							   iW  =  iW_dst;							   	
							   iH  =  iH_dst;


							   break;
						case  5:
							   iW  =  iW_desc  /  iCol;
							   iH  =  iH_desc  /  2.0;
							   iX  =  iX_desc  +  iW_desc  /  iCol * 2;
							   iY  =  iY_desc  +  iH_desc  /  2.0;
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );


							   if  (  iY  ==  iY_dst  )  {
								   iX  =  iX  -  iW  /  2  +  iW_dst  /  2;
								   iY  =  iY_dst;
							   }
							   //
							   iW  =  iW_dst;							   	
							   iH  =  iH_dst;


							   break;
						default:
								goto  errLabel;
				}
				
				//
				myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  pImg->iW_org,  pImg->iH_org,  iX,  iY,  iW,  iH,  
									&iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,									  
									  &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );				

				if  (  pImg->iW_i  !=  iW_i
					||  pImg->iH_i  !=  iH_i
					||  pImg->iX_src_i  !=  iX_src_i
					||  pImg->iY_src_i  !=  iY_src_i
					||  pImg->iX_dst  !=  iX_dst				
					||  pImg->iY_dst  !=  iY_dst
					||  pImg->iW_dst  !=  iW_dst
					||  pImg->iH_dst  !=  iH_dst
					)				
				{
						  pImg->bResized  =  TRUE;
						  
						  //
						  pImg->iW_i  =  iW_i;
						  pImg->iH_i  =  iH_i;
						  pImg->iX_src_i  =  iX_src_i;
						  pImg->iY_src_i  =  iY_src_i;
						  //
						  pImg->iX_dst  =  iX_dst;				  
						  pImg->iY_dst  =  iY_dst;
						  pImg->iW_dst  =  iW_dst;
						  pImg->iH_dst  =  iH_dst;					  
				}

				//  traceLog((TCHAR*)  _T(  "case is  3, index is %d,  pImg  iX  %d, iY %d, iW %d,iH %d"  ),  index,  pImg->iX,  pImg->iY,  pImg->iW,  pImg->iH  );
				
				index  ++  ;
		 }

		 iErr  =  0;  goto  errLabel;
	 }

	 //
	 if  (  cnt  ==  7  )  {
		 iRows  =  3;
		 int  index  =  0,  iRow  =  0,  iCol  =  3;  

		 //
		 //  先计算1的iH/dst
		 if  (  1  )  {								
								   iW  =  iW_desc  /  3;							   
								   iH  =  iH_desc  /  3;							   
								   iX  =  iX_desc;							   
								   iY  =  iY_desc  +  iH_desc  /  3;  							   
								   //							   
								   //							   
								   //			  							   
								   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
									   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
									   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );
		 }
		 int  tmp_iH_dst_2Row;  tmp_iH_dst_2Row  =  iH_dst;

		 //
		 for  (  i  =  0,index = 0;  i  <  uiMaxCnt_imgMems  &&  index  <  cnt;  i  ++  )  {
				pImg =  (  CAP_IMAGE  *  )(  (  (  char  *  )pImgMems  )  +  i  *  uiSize_pImgMem  );	//  &pImages->mems[i];
				if  (  !pImg->iW_org  ||  !pImg->iH_org  )  continue;

				int  iW_average  =  iW_desc  *  0.33;
				int  iH_half  =  iH_desc  /  2.0;
					 
				switch  (  index  )  {
						case  0:
							   //

							   //
							   iW  =  iW_desc;
							   iH  =  iH_desc  /  3;
							   iX  =  iX_desc;
							   iY  =  iY_desc;
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

							   //
							   iX  =  iX_dst;
							   iY  =  iY_desc  +  iH_desc  /  2  -  tmp_iH_dst_2Row  /  2  -  iH_dst;
							   //
							   iW  =  iW_dst;
							   iH  =  iH_dst;

							   break;
						case  1:
							   iW  =  iW_desc  /  3;
							   iH  =  iH_desc  /  3;
							   iX  =  iX_desc;
							   iY  =  iY_desc  +  iH_desc  /  3;  
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

							   //
							   if  (  iX  ==  iX_dst  )  {
								   iY  =  iY_desc  +  iH_desc  /  2  -  iH_dst  / 2;  
								   }
							   else  {
									 //
									 iX  =  iX  +  iW  *  3  /  2   -  iW_dst  *  3  /  2;
									 iY  =  iY_dst;
							   }
							   //
							   iW  =  iW_dst;
							   iH  =  iH_dst;

							   break;
						case  2:
							   iW  =  iW_desc  /  3;
							   iH  =  iH_desc  /  3;
							   iX  =  iX_desc  +  iW_desc  /  3;
							   iY  =  iY_desc  +  iH_desc  /  3;  
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

							   //
							   if  (  iX  ==  iX_dst  )  {
									 //
							   	     iY  =  iY_desc  +  iH_desc  /  2  -  iH_dst  / 2;  
								   }
							   else  {
								     iX  =  iX  +  iW  /  2  -  iW_dst  /  2;
							   }


							   //
							   iW  =  iW_dst;							   	
							   iH  =  iH_dst;

							   //
							   break;
						case  3:
							   iW  =  iW_desc  /  3;
							   iH  =  iH_desc  /  3;
							   iX  =  iX_desc  +  iW_desc  /  3  *  2;
							   iY  =  iY_desc  +  iH_desc  /  3;  
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

							   //
							   if  (  iX  ==  iX_dst  )  {
									iY  =  iY_desc  +  iH_desc  /  2  -  iH_dst  / 2;  
								   
							   }
							   else  {
								     iX  =  iX  -  iW  /  2  +  iW_dst  /  2;
							   }


							   //
							   iW  =  iW_dst;							   	
							   iH  =  iH_dst;

							   //
							   break;
						case  4:
							   iW  =  iW_desc  /  iCol;
							   iH  =  iH_desc  /  3;
							   iX  =  iX_desc;
							   iY  =  iY_desc  +  iH_desc  /  3  *  2.0;
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

							   
							   if  (  iX  ==  iX_dst  )  {
								   iY  =  iY_desc  +  iH_desc  /  2  -  tmp_iH_dst_2Row  /  2  +  tmp_iH_dst_2Row;
								   }
							   else  {
								   iX  =  iX  +  iW  *  3  /  2  -  iW_dst  *  3  /  2;
								   iY  =  iY_dst;
							   }
							   //
							   iW  =  iW_dst;							   	
							   iH  =  iH_dst;


							   break;
						case  5:
							   iW  =  iW_desc  /  iCol;
							   iH  =  iH_desc  /  3;
							   iX  =  iX_desc  +  iW_desc  /  iCol;
							   iY  =  iY_desc  +  iH_desc  /  3  *  2.0;
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

							   //
							   if  (  iX  ==  iX_dst  )  {
								   iY  =  iY_desc  +  iH_desc  /  2  -  tmp_iH_dst_2Row  /  2  +  tmp_iH_dst_2Row;
								   }
							   else  {
								   iX  =    iX  +  iW  /  2  -  iW_dst  /  2;
								   iY  =  iY_dst;
							   }
							   //
							   iW  =  iW_dst;							   	
							   iH  =  iH_dst;


							   break;
						case  6:
							   iW  =  iW_desc  /  iCol;
							   iH  =  iH_desc  /  3;
							   iX  =  iX_desc  +  iW_desc  /  iCol * 2;
							   iY  =  iY_desc  +  iH_desc  /  3  *  2.0;
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );


							   if  (  iX  ==  iX_dst  )  {
								   iY  =  iY_desc  +  iH_desc  /  2  -  tmp_iH_dst_2Row  /  2  +  tmp_iH_dst_2Row;
								   }
							   else  {
								   iX  =  iX  -  iW  /  2  +  iW_dst  /  2;
								   iY  =  iY_dst;
							   }
							   //
							   iW  =  iW_dst;							   	
							   iH  =  iH_dst;


							   break;
						default:
								goto  errLabel;
				}
				//
#ifdef  __DEBUG__
				//traceLog((TCHAR*)  _T(  "mem[%d], iX %d, iY %d, iW %d, iH %d"  ),  index,  iX,  iY,  iW,  iH  );
#endif
				
				//
				myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  pImg->iW_org,  pImg->iH_org,  iX,  iY,  iW,  iH,  
									&iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,									  
									  &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );				

				if  (  pImg->iW_i  !=  iW_i
					||  pImg->iH_i  !=  iH_i
					||  pImg->iX_src_i  !=  iX_src_i
					||  pImg->iY_src_i  !=  iY_src_i
					||  pImg->iX_dst  !=  iX_dst				
					||  pImg->iY_dst  !=  iY_dst
					||  pImg->iW_dst  !=  iW_dst
					||  pImg->iH_dst  !=  iH_dst
					)				
				{
						  pImg->bResized  =  TRUE;
						  
						  //
						  pImg->iW_i  =  iW_i;
						  pImg->iH_i  =  iH_i;
						  pImg->iX_src_i  =  iX_src_i;
						  pImg->iY_src_i  =  iY_src_i;
						  //
						  pImg->iX_dst  =  iX_dst;				  
						  pImg->iY_dst  =  iY_dst;
						  pImg->iW_dst  =  iW_dst;
						  pImg->iH_dst  =  iH_dst;					  
				}

				//  traceLog((TCHAR*)  _T(  "case is  3, index is %d,  pImg  iX  %d, iY %d, iW %d,iH %d"  ),  index,  pImg->iX,  pImg->iY,  pImg->iW,  pImg->iH  );
				
				index  ++  ;
		 }

		 iErr  =  0;  goto  errLabel;
	 }

	 //  2015/06/20，上二下三下三的方案被否决了，下面采用左2右3右3的3列方案
	 if  (  cnt  ==  8  )  {
		 iRows  =  3;
		 int  index  =  0,  iRow  =  0,  iCol  =  3;  


		 //  先计算1的iH/dst
		 {								
								   iW  =  iW_desc  /  3;							   
								   iH  =  iH_desc  /  3;							   
								   iX  =  iX_desc;							   
								   iY  =  iY_desc  +  iH_desc  /  3;  							   
								   //							   
								   //							   
								   //			  							   
								   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
									   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
									   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );
		 }							   
		 int  tmp_iH_dst_2Row;  tmp_iH_dst_2Row  =  iH_dst;

		 //
		 for  (  i  =  0,index = 0;  i  <  uiMaxCnt_imgMems  &&  index  <  cnt;  i  ++  )  {
				pImg =  (  CAP_IMAGE  *  )(  (  (  char  *  )pImgMems  )  +  i  *  uiSize_pImgMem  );	//  &pImages->mems[i];
				if  (  !pImg->iW_org  ||  !pImg->iH_org  )  continue;

				int  iW_average  =  iW_desc  *  0.33;
				int  iH_half  =  iH_desc  /  2.0;


				//
				switch  (  index  )  {
						case  0:
							   //

							   //
							   iW  =  iW_desc  /  2;
							   iH  =  iH_desc  /  3;
							   iX  =  iX_desc;
							   iY  =  iY_desc;
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

							   //
							   if  (  iX  ==  iX_dst  )  {
								   iY  =  iY_desc  +  iH_desc  /  2  -  tmp_iH_dst_2Row  /  2  -  iH_dst;
								   }
							   else  {
									 //
									 iX  =  iX_desc  +  iW_desc  /  2  -  iW_dst;
									 iY  =  iY_desc  +  iH_desc  /  2  -  tmp_iH_dst_2Row  /  2  -  iH_dst;
							   }

							   //
							   iW  =  iW_dst;
							   iH  =  iH_dst;

							   break;
						case  1:
							   iW  =  iW_desc  /  2;
							   iH  =  iH_desc  /  3;
							   iX  =  iX_desc  +  iW;
							   iY  =  iY_desc;

							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

							   if  (  iX  ==  iX_dst  )  {
								   iY  =  iY_desc  +  iH_desc  /  2  -  tmp_iH_dst_2Row  /  2  -  iH_dst;
								   }
							   else  {
								     //
								     iY  =  iY_desc  +  iH_desc  /  2  -  tmp_iH_dst_2Row  /  2  -  iH_dst;
							   }

							   //
							   iW  =  iW_dst;
							   iH  =  iH_dst;

							   break;
						case  2:
							   iW  =  iW_desc  /  3;
							   iH  =  iH_desc  /  3;
							   iX  =  iX_desc;
							   iY  =  iY_desc  +  iH_desc  /  3;  
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

							   //
							   if  (  iX  ==  iX_dst  )  {
								   iY  =  iY  +  iH  /  2  -  iH_dst  / 2;  
								   }
							   else  {
									 //
									 iX  =  iX  +  iW  *  3  /  2   -  iW_dst  *  3  /  2;
									 iY  =  iY_dst;
							   }
							   //
							   iW  =  iW_dst;
							   iH  =  iH_dst;

							   break;
						case  3:
							   iW  =  iW_desc  /  3;
							   iH  =  iH_desc  /  3;
							   iX  =  iX_desc  +  iW_desc  /  3;
							   iY  =  iY_desc  +  iH_desc  /  3;  
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

							   //
							   if  (  iX  ==  iX_dst  )  {
									 //
							   	     iY  =  iY  +  iH  /  2  -  iH_dst  / 2;  
								   }
							   else  {
								     iX  =  iX  +  iW  /  2  -  iW_dst  /  2;
							   }


							   //
							   iW  =  iW_dst;							   	
							   iH  =  iH_dst;

							   //
							   break;
						case  4:
							   iW  =  iW_desc  /  3;
							   iH  =  iH_desc  /  3;
							   iX  =  iX_desc  +  iW_desc  /  3  *  2;
							   iY  =  iY_desc  +  iH_desc  /  3;  
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

							   //
							   if  (  iX  ==  iX_dst  )  {
									iY  =  iY  +  iH  /  2  -  iH_dst  / 2;  
								   
							   }
							   else  {
								     iX  =  iX  -  iW  /  2  +  iW_dst  /  2;
							   }


							   //
							   iW  =  iW_dst;							   	
							   iH  =  iH_dst;

							   //
							   break;
						case  5:
							   iW  =  iW_desc  /  3;
							   iH  =  iH_desc  /  3;
							   iX  =  iX_desc;
							   iY  =  iY_desc  +  iH_desc  /  3  *  2.0;
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

							   
							   if  (  iX  ==  iX_dst  )  {
													   iY  =  iY_desc  +  iH_desc  /  2  -  tmp_iH_dst_2Row  /  2  +  tmp_iH_dst_2Row;
			   }
							   else  {
								   iX  =  iX  +  iW  *  3  /  2  -  iW_dst  *  3  /  2;
								   iY  =  iY_dst;
							   }
							   //
							   iW  =  iW_dst;							   	
							   iH  =  iH_dst;


							   break;
						case  6:
							   iW  =  iW_desc  /  iCol;
							   iH  =  iH_desc  /  3;
							   iX  =  iX_desc  +  iW_desc  /  iCol;
							   iY  =  iY_desc  +  iH_desc  /  3  *  2.0;
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

							   //
							   if  (  iX  ==  iX_dst  )  {
								   iY  =  iY_desc  +  iH_desc  /  2  -  tmp_iH_dst_2Row  /  2  +  tmp_iH_dst_2Row;
								   }
							   else  {
								   iX  =    iX  +  iW  /  2  -  iW_dst  /  2;
								   iY  =  iY_dst;
							   }
							   //
							   iW  =  iW_dst;							   	
							   iH  =  iH_dst;


							   break;
						case  7:
							   iW  =  iW_desc  /  iCol;
							   iH  =  iH_desc  /  3;
							   iX  =  iX_desc  +  iW_desc  /  iCol * 2;
							   iY  =  iY_desc  +  iH_desc  /  3  *  2.0;
							   //
							   //
							   //			  
							   new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW,  iH,  
								   &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
								   &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );


							   if  (  iX  ==  iX_dst  )  {
								   iY  =  iY_desc  +  iH_desc  /  2  -  tmp_iH_dst_2Row  /  2  +  tmp_iH_dst_2Row;
								   }
							   else  {
								   iX  =  iX  -  iW  /  2  +  iW_dst  /  2;
								   iY  =  iY_dst;
							   }
							   //
							   iW  =  iW_dst;							   	
							   iH  =  iH_dst;


							   break;
						default:
								goto  errLabel;
				}
				
				//
				myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  pImg->iW_org,  pImg->iH_org,  iX,  iY,  iW,  iH,  
									&iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,									  
									  &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );				

				if  (  pImg->iW_i  !=  iW_i
					||  pImg->iH_i  !=  iH_i
					||  pImg->iX_src_i  !=  iX_src_i
					||  pImg->iY_src_i  !=  iY_src_i
					||  pImg->iX_dst  !=  iX_dst				
					||  pImg->iY_dst  !=  iY_dst
					||  pImg->iW_dst  !=  iW_dst
					||  pImg->iH_dst  !=  iH_dst
					)				
				{
						  pImg->bResized  =  TRUE;
						  
						  //
						  pImg->iW_i  =  iW_i;
						  pImg->iH_i  =  iH_i;
						  pImg->iX_src_i  =  iX_src_i;
						  pImg->iY_src_i  =  iY_src_i;
						  //
						  pImg->iX_dst  =  iX_dst;				  
						  pImg->iY_dst  =  iY_dst;
						  pImg->iW_dst  =  iW_dst;
						  pImg->iH_dst  =  iH_dst;					  
				}

				//  traceLog((TCHAR*)  _T(  "case is  3, index is %d,  pImg  iX  %d, iY %d, iW %d,iH %d"  ),  index,  pImg->iX,  pImg->iY,  pImg->iW,  pImg->iH  );
				
				index  ++  ;
		 }

		 iErr  =  0;  goto  errLabel;
	 }


	 //
	 if  (  cnt  )  {
		 iRows  =  (  int  )sqrt(  (  double  )cnt  );
		 if  (  iRows  *  iRows  <  cnt  )  iRows  ++  ;
		 //

		 cnt  =  0;
		 for  (  i  =  0;  i  <  uiMaxCnt_imgMems;  i  ++  )  {
			  pImg  =  (  CAP_IMAGE  *  )(  (  (  char  *  )pImgMems  )  +  i  *  uiSize_pImgMem  );	//  &pImages->mems[i];
			  if  (  !pImg->iW_org  ||  !pImg->iH_org  )  continue;

			  int  iRow,  iCol;
			  iRow  =  cnt  %  iRows;
			  iCol  =  cnt  /  iRows;

			  //  int  iX,  iY;
			  iX  =  iX_desc  +  (  int  )(  iRow  *  iW_desc  /  (  float  )iRows  );
			  iY  =  iY_desc  +  (  int  )(  iCol  *  iH_desc  /  (  float  )iRows  );

			  //
			  new_myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  tmp_iW_org,  tmp_iH_org,  iX,  iY,  iW_desc  /  iRows,  iH_desc  /  iRows,  
				  &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
				  &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );

			  //
			  iX  =  iX_dst;
			  iY  =  iY_dst;
			  iW  =  iW_dst;
			  iH  =  iH_dst;

			  //
			  myGetImageInfo(  0,  ucbAutoClip,  ucb3d,  pImg->iW_org,  pImg->iH_org,  iX,  iY,  iW,  iH,  
				  &iW_i,  &iH_i,  &iX_src_i,  &iY_src_i,
				  &iX_dst,  &iY_dst,  &iW_dst,  &iH_dst  );
			  
			  if  (  pImg->iW_i  !=  iW_i
					||  pImg->iH_i  !=  iH_i
					||  pImg->iX_src_i  !=  iX_src_i
					||  pImg->iY_src_i  !=  iY_src_i
					||  pImg->iX_dst  !=  iX_dst				
					||  pImg->iY_dst  !=  iY_dst
					||  pImg->iW_dst  !=  iW_dst
					||  pImg->iH_dst  !=  iH_dst
					)				
				{
						  pImg->bResized  =  TRUE;
						  
						  //
						  pImg->iW_i  =  iW_i;
						  pImg->iH_i  =  iH_i;
						  pImg->iX_src_i  =  iX_src_i;
						  pImg->iY_src_i  =  iY_src_i;
						  //
						  pImg->iX_dst  =  iX_dst;				  
						  pImg->iY_dst  =  iY_dst;
						  pImg->iW_dst  =  iW_dst;
						  pImg->iH_dst  =  iH_dst;					  
				}

			  cnt  ++  ;
		 }
	 }

	 iErr  =  0;
errLabel:

	return  iErr;
}

 
 





//
 int  getCapImages(  unsigned  int  ucbAutoClip,  int  iX_desc,  int  iY_desc,  int  iW_desc,  int  iH_desc,  PARAM_getCapImages  *  pParam,  CAP_IMAGES  *  pImages  )
{
	 unsigned  char  ucb3d  =  FALSE;

	 //
	 PARAM_getCapImages  param  =  {0};
	 if  (  pParam  )  param  =  *pParam;

	 //
#if  10
	 if  (  param.bNew  )  {
		 ucb3d  =  TRUE;
		 return  new_getCapImagesFunc(  ucbAutoClip,  ucb3d,  iX_desc,  iY_desc,  iW_desc,  iH_desc,  pParam,  &pImages->head,  pImages->mems,  sizeof(  pImages->mems[0]  ),  mycountof(  pImages->mems  )  );
	 }
#endif

	 //
	 return  getCapImagesFunc(  ucbAutoClip,  ucb3d,  iX_desc,  iY_desc,  iW_desc,  iH_desc,  &param,  &pImages->head,  pImages->mems,  sizeof(  pImages->mems[0]  ),  mycountof(  pImages->mems  )  );
}




//
 int  redrawImage(  HWND    hDlg,  int  idc,  int  iX,  int  iY,  unsigned  int  iW,  unsigned  int  iH  )
{
	RECT		rect;
	HWND		hWnd	=	NULL;

	rect.left  =  iX;
	rect.top  =  iY;				//  ¿Ø¼þµÄ×óÉÏ½ÇÎ»ÖÃ
	rect.right  =  iX  +  iW;
	rect.bottom  =  iY  +  iH;

	if  (  idc  )  {
		hWnd  =  GetDlgItem(  hDlg,  idc  );
		if  (  !hWnd  )  return  -1;
		
		//  MapWindowPoints(  hWnd,  hDlg,  (  LPPOINT  )&rect,  2  );

		InvalidateRect(  hWnd,  NULL,  TRUE  );
		UpdateWindow(  hWnd  );

		return  0;
	}

	InvalidateRect(  hDlg,  &rect,  TRUE  );
	UpdateWindow(  hDlg  );

	return  0;
}



#include	<ddraw.h>
//#include	"qmcDxSurface.h"
//#include	"qmcDxSurfacePublic.h"

 BOOL  ishRet_bFailed_dxSurface(  HRESULT  hRet,  BOOL  *  pbFailed_dxSurface  )
{
	if  (  !pbFailed_dxSurface  )  return  FALSE;

	//  2012/06/26
	switch  (  hRet  )  {
			case  DDERR_INVALIDRECT:
				  #ifdef  __DEBUG__
						  traceLog((TCHAR*)  _T(  "hRet, invalidRect"  )  );
				  #endif
				  break;
			default:
					break;
	}


	//
	switch  (  hRet  )  {
			case  DDERR_SURFACELOST:			
			//  case  DDERR_INVALIDRECT:		
			case  DDERR_CANTCREATEDC:
				  *pbFailed_dxSurface  =  TRUE;
				  break;
			default:
				    *pbFailed_dxSurface  =  FALSE;
					break;
	}


	//
	return  *pbFailed_dxSurface;
}


 //  此函数用来关闭capImage的绘制动作和句柄, 2012/02/06
void  capImageDrawClose(  CAP_IMAGE  *  pImg,  LPCTSTR  hint  )  
{
	if (!hint)  hint = _T("");

	if  (  !pImg  )  return;

	if  (  pImg->hOffscreenDc  )  {
		DeleteDC(  pImg->hOffscreenDc  );  pImg->hOffscreenDc  =  NULL;
	}
	if  (  pImg->hBitmap  )  {
		DeleteObject(  pImg->hBitmap  );  pImg->hBitmap  =  NULL;
	}

	//
		if  (  pImg->hDib  )  {			//  2008/03/22
#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "capImageDrawClose: taskId %d. %s"  ),  pImg->iTaskId,  hint  );
#endif

		::DrawDibEnd(  pImg->hDib  );
		::DrawDibClose(  pImg->hDib  );
		pImg->hDib  =  NULL;
	}

	//  2012/02/06
#if  0  //  def  __USE_vmr__
	if  (  pImg->dmoInfo.pDmo  )  {
		CloseClip(  &pImg->dmoInfo  );
	}
#endif


}












 
//  2015/10/06
 //  2014/07/31   
int  drawCapImages(  QY_MC  *  pQyMc,  HWND    hWnd_src,  unsigned  char  ucbAutoClip,  MIS_MSG_procVideo_qmc  *  pMsg,  
	int  iX,  int  iY,  unsigned  int  iW,  unsigned  int  iH,  CAP_subWnds  *  pSubWnds,  ZONE_PARAM  *  pZoneParam,  
	CAP_IMAGES  *  pImgs,  HWND  hWnd_dst,  HDC  *  phDc_dst,  PARAM_dc_draw  *  pDcDrawParam  )
{
	int				iErr				=	-1;
	int				i;
	CAP_IMAGE	*	pImg				=	NULL;
	int				iIndex_img;
	BOOL			tmpbRet;
	HRESULT			hRet;
	BOOL			bFailed_dxSurface	=	FALSE;
	BOOL			bHintSkipped		=	FALSE;
	RECT			rc;
	
	unsigned  char  ucbFixedSize		=	FALSE;
	//BOOL			bUseDxSurface		=	FALSE;
	BOOL			bDlgHidden			=	FALSE;
	BOOL			bBgWall				=	FALSE;			//  2014/10/02
	//
	BOOL			bDrawOffscreen		=	10;	//  TRUE;	//  2014/04/11

	//  2015/11/27
	BOOL			bModified_capImg	=	FALSE;	

	//
	if  (  pDcDrawParam  )  {
		ucbFixedSize  =  pDcDrawParam->ucbFixedSize;
		//bUseDxSurface  =  pDcDrawParam->bUseDxSurface;
		bDlgHidden  =  pDcDrawParam->bDlgHidden;
		bBgWall  =  pDcDrawParam->bBgWall;					//  2014/10/02
	}
	#if  1	//  2012/06/26. 暂时不再使用dxSurface;
		//bUseDxSurface  =  FALSE;
	#endif
	

    //
	if  (  !pMsg  )  return  -1;
	if  (  !pMsg->bih.biWidth  ||  !pMsg->bih.biHeight  )  goto  errLabel;
	//  if  (  !pMsg->data  )  goto  errLabel;
	if  (  pMsg->pkt.usPktResType  !=  CONST_pktResType_sharedTex  )  {
		if  (  !pMsg->pkt.memory.m_pBuf  )  {
			showInfo_open0(  0,  _T(  "drawCapImages"  ),  _T(  " failed, pkt.memory.m_pBuf null"  )  );
			goto  errLabel;
		}
	}
	if  (  !phDc_dst  )  goto  errLabel;
	if  (  !pMsg->iTaskId  )  {
		goto  errLabel;
	}

	//
	if (pImgs->mems[0].iW_org > 1000) {
		int  mm = 0;
	}
	if (pMsg->bih.biWidth > 1000) {
		int  ii = 0;
	}

	//
	BOOL	bOk_index_capImage; bOk_index_capImage = FALSE;
	if  (  pZoneParam  )  {	//  2012/05/06
		if  (  pZoneParam->index_capImage  >=  0  &&  pZoneParam->index_capImage  <  mycountof(  pImgs->mems  )  )  {
			pImg  =  &pImgs->mems[pZoneParam->index_capImage];
			if  (  pImg->iW_org  &&  pImg->iH_org  
				&&  pImg->idInfo_sender.ui64Id  ==  pMsg->idInfo_sender.ui64Id
				&&  pImg->uiTranNo_openAvDev  ==  pMsg->uiTranNo_openAvDev
				&&  pImg->iTaskId  ==  pMsg->iTaskId							//  2015/10/06
				&&  pImg->usIndex_activeMems_from  ==  pMsg->usIndex  
				)
			{
				iIndex_img  =  pZoneParam->index_capImage;
				bOk_index_capImage  =  TRUE;
			}
		}
	}
	if  (  !bOk_index_capImage  )  {
		//
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "drawCapImages: try to find new index_capImage"  )  );
		#endif
		//
		for  (  i  =  0;  i  <  mycountof(  pImgs->mems  );  i  ++  )  {		//  
			 pImg  =  &pImgs->mems[i];
			 if  (  !pImg->iW_org  ||  !pImg->iH_org  )  continue;
			 if  (  pImg->idInfo_sender.ui64Id  ==  pMsg->idInfo_sender.ui64Id  
				 &&  pImg->uiTranNo_openAvDev  ==  pMsg->uiTranNo_openAvDev
				 &&  pImg->iTaskId  ==  pMsg->iTaskId							//  2015/10/06
				 &&  pImg->usIndex_activeMems_from  ==  pMsg->usIndex  )  
			 {
				 bOk_index_capImage  =  TRUE;
				 break;					  
			 }
		}
		if  (  i  ==  mycountof(  pImgs->mems  )  )  {							//  
			//
			BOOL  bNewImgFound  =  FALSE;
			//
#if  10
			//  2016/03/12
			if  (  pDcDrawParam  )  {
				if  (  pDcDrawParam->usIndex_active  <  mycountof(  pImgs->mems  )  )  {
					i  =  pDcDrawParam->usIndex_active;
					pImg  =  &pImgs->mems[i];
					if  (  !pImg->iW_org
						||  !pImg->iH_org
						||  !pImg->iTaskId  )
					{
						bNewImgFound  =  TRUE;
					}
				}
			}
#endif
			//
			if  (  !bNewImgFound  )  {
				//
				for  (  i  =  0;  i  <  mycountof(  pImgs->mems  );  i  ++  )  {
					 pImg  =  &pImgs->mems[i];
					 if  (  !pImg->iW_org  
						 ||  !pImg->iH_org  
						 ||  !pImg->iTaskId  ) 					 
					 {
						 break;					
					 }
				}
			}
		}
		if  (  i  ==  mycountof(  pImgs->mems  )  )  goto  errLabel;
		iIndex_img  =  i;
	}

	//  2009/10/07
	if  (  pZoneParam  )  {
		if  (  pZoneParam->index_capImage  !=  iIndex_img  )  pZoneParam->index_capImage  =  iIndex_img;
	}

	
	//
	if  (  !bOk_index_capImage  )
	{
		//
		pImg->idInfo_sender.ui64Id  =  pMsg->idInfo_sender.ui64Id;
		//  pImg->uiObjType  =  pMsg->ui
		pImg->uiTranNo_openAvDev  =  pMsg->uiTranNo_openAvDev;
		pImg->usIndex_activeMems_from  =  pMsg->usIndex;
		pImg->iTaskId  =  pMsg->iTaskId;

		//  2015/11/10
		pImg->ucbUnresizable_srcInfo  =  pMsg->pkt.decInfo.ucbUnresizable;

		//  2013/07/20
		//
#if  0
		if  (  pDcDrawParam  )  {
			pDcDrawParam->bModified_capImg  =  TRUE;
		}
#endif
		//  2015/11/27
		bModified_capImg  =  TRUE;

	}


	//
	pImg->dwTickCnt_lastDrawing  =  GetTickCount(  );							//  2009/09/10




	//  2014/12/10
	if  (  pImg->playerId.index_player  !=  pMsg->playerId.index_player
		||  pImg->playerId.uiTranNo_player  !=  pMsg->playerId.uiTranNo_player  )  
	{	//  2013/08/20
		pImg->playerId  =  pMsg->playerId;

		//  2015/11/27
		bModified_capImg  =  TRUE;

	}
	//  2015/10/01
	if  (  pImg->usPktResType  !=  pMsg->pkt.usPktResType  )  {
		pImg->usPktResType  =  pMsg->pkt.usPktResType;
#if  0
		if  (  pDcDrawParam  )  {
			pDcDrawParam->bModified_capImg  =  TRUE;
		}
#endif
		//  2015/11/27
		bModified_capImg  =  TRUE;

	}


	//  if  (  !pMsg->ucbLocalAv  )  
	{
		if  (  pImg->hWnd_remoteAv  )  {
			//  pMsg->curhWnd_toDisplay  =  pImg->hWnd_remoteAv;						  					  							
			if  (  SendMessage(  pImg->hWnd_remoteAv,  CONST_qyWm_comm,  0,  (  LPARAM  )pMsg  )  !=  QY_RC_WMOK  )  {
				if  (  !IsWindow(  pImg->hWnd_remoteAv  )  )  {
					pImg->hWnd_remoteAv  =  NULL;
				}
			}
			pMsg->ucbDisplayAllFrames  =  TRUE;
			iErr  =  0;  goto  errLabel;
		}
	}

	if  (  !iW  &&  !iH  )  return  0;		//  minimized. 2010/09/01
	if  (  !iW  ||  !iH  )  {
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "drawCapImages failed, iW %d, iH %d"  ),  iW,  iH  );
		#endif
		goto  errLabel;
	}
					   
	//  ¼ì²é±ÈÀýÊÇ·ñ±ä»¯.
	if  (  pImgs->head.bResized
		||  pImg->iW_org  !=  pMsg->bih.biWidth
			||  pImg->iH_org  !=  pMsg->bih.biHeight  )							
	{
		if  (  pImgs->head.bResized  )  {
			pImgs->head.bResized  =  FALSE;
			//
			for  (  i  =  0;  i  <  mycountof(  pImgs->mems  );  i  ++  )  {
				 pImg  =  &pImgs->mems[i];
				 
				 capImageDrawClose(  pImg,  _T(  "drawCapImages.2095")  );
			}
		}
		//
		pImg  =  &pImgs->mems[iIndex_img];
		//
		capImageDrawClose(  pImg,  _T(  "drawCapImages.2101"  ));
		//
		//
		pImg->iW_org  =  pMsg->bih.biWidth;
		pImg->iH_org  =  pMsg->bih.biHeight;	
		//
		//  redrawImage(  hDlg,  idc,  iX,  iY,  iW,  iH  );
		SetRect(  &rc,  iX,  iY,  iX  +  iW,  iY  +  iH  );
		MapWindowPoints(  hWnd_src,  hWnd_dst,  (  LPPOINT  )&rc,  2  );
		redrawImage(  hWnd_dst,  0,  rc.left,  rc.top,  rc.right  -  rc.left,  rc.bottom  -  rc.top  );
		//
#ifdef  __DEBUG__
		if  (  pDcDrawParam  )  {
			if  (  pDcDrawParam->dbgInfo.ucbDbgImgs  )  {
				int  iiii;
				iiii  =  0;
				//
				traceLog((TCHAR*)  _T(  "drawCapImgs: called"  )  );
			}
		}
#endif
		//
		if  (  ucbFixedSize  )  
			myGetImageInfo_2d(  TRUE,  ucbAutoClip,  pImg->iW_org,  pImg->iH_org,  iX,  iY,  iW,  iH,  (  unsigned  int  *  )&pImg->iW_i, 
				(  unsigned  int  *  )&pImg->iH_i,  &pImg->iX_src_i,  &pImg->iY_src_i,  &pImg->iX_dst,  &pImg->iY_dst,  
				(  unsigned  int  *  )&pImg->iW_dst,  (  unsigned  int  *  )&pImg->iH_dst  );
		else  {
			  //
			  PARAM_getCapImages  param_g  =  {0};
			  //
			  #if  0
				   if  (  ucbAutoClip  )  {
					   param_g.bNew  =  TRUE;
				   }
			  #endif
			  //
			  if  (  pDcDrawParam  )  {
				  param_g  =  pDcDrawParam->param_getCapImages;
			  }
			  //
			  getCapImages(  ucbAutoClip,  iX,  iY,  iW,  iH,  &param_g,  pImgs  );
			  //
			  #ifdef  __DEBUG__
					  if  (  pImgs->head.usCnt  ==  2  )  {
						  int  ii  =  0;
					  }
			  #endif
		}
		//
	}
	if  (  pImg->bResized  )  {
		pImg->bResized  =  FALSE;
		//
		capImageDrawClose(  pImg,  _T(  "drawCapImages.2151"  ));
	}




	//  2012/05/08
	if  (  bDlgHidden  )  {		//  如果窗口没显示,就不需要做下面的绘制动作了
		#ifdef  __DEBUG__
				#if  0
					traceLog((TCHAR*)  _T(  "drawCapImaged: bDlgHidden is true. drawing skipped"  )  );
				#endif
		#endif
		iErr  =  0;  goto  errLabel;
	}
	//  2015/10/04
	if  (  pMsg->pkt.usPktResType  ==  CONST_pktResType_sharedTex  )  {  // 2015/10/04. 不需要做下面的绘制动作了
		//
		TEX2_props  props;
		if  (  dyn_getTex2Props(  0,  pMsg->playerId.index_player,  &props  ) 
			||  !props.bAvail  )
		{
			//  2015/10/06
#if  0
			if  (  pDcDrawParam  )  {
				pDcDrawParam->bModified_capImg  =  TRUE;
			}
#endif
			//  2015/11/27
			bModified_capImg  =  TRUE;

		}
		//
		iErr  =  0;  goto  errLabel;
	}

	//
	if  (  !pImg->hDib  )  {
		//
		//  2015/10/06
#if  0
		if  (  pDcDrawParam  )  {
			pDcDrawParam->bModified_capImg  =  TRUE;
		}
#endif
		//  2015/11/27
		bModified_capImg  =  TRUE;


	}


	//
	if  (  !*phDc_dst  )  {
		//if  (  !bUseDxSurface  )  
		{
			{
				  HWND    hCtrl  =  hWnd_dst;
				  if  (  !hCtrl  )  goto  errLabel;
				  *phDc_dst  =  GetDC(  hCtrl  );
				  //
				  //  2013/02/27
				  if  (  pDcDrawParam  )  {
					#if  0  //  2014/10/02
					  for  (  i  =  0;  i  <  mycountof(  pDcDrawParam->hWnds_excludeClip  );  i  ++  )  {
						   if  (  IsWindow(  pDcDrawParam->hWnds_excludeClip[i]  )  )  {
							   RECT	rc;
							   int	tmpiRet;
							   GetWindowRect(  pDcDrawParam->hWnds_excludeClip[i],  &rc  );
							   MapWindowPoints(  NULL,  hCtrl,  (  LPPOINT  )&rc,  2  );
							   tmpiRet  =  ExcludeClipRect(  *phDc_dst,  rc.left,  rc.top,  rc.right,  rc.bottom  );
							   if  (  tmpiRet  ==  ERROR  )  {
								   #ifdef  __DEBUG__
										   traceLog((TCHAR*)  _T(  "ExcludeClipRect failed"  )  );
								   #endif
								   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "drawCapImages: ExcludeClipRect failed."  )  );
								   goto  errLabel;
							   }
						   }
					  }
					#endif
				  }
				}
			}
	}

			
	//
	//if  (  !bUseDxSurface  )  
	{
		//
		HDC	hDc = *phDc_dst;

		//
		if (bDrawOffscreen) {
			if (!pImg->hBitmap) {
				pImg->hBitmap = CreateCompatibleBitmap(*phDc_dst, pImg->iW_i, pImg->iH_i);
				if (!pImg->hBitmap)  goto  errLabel;
			}
			if (!pImg->hOffscreenDc) {
				pImg->hOffscreenDc = CreateCompatibleDC(*phDc_dst);
				if (!pImg->hOffscreenDc)  goto  errLabel;
				pImg->hOldBitmap = (HBITMAP)SelectObject(pImg->hOffscreenDc, pImg->hBitmap);
				if (pImg->hOldBitmap == HGDI_ERROR)  goto  errLabel;
			}
			//
			hDc = pImg->hOffscreenDc;
		}

		//		
		if (!pImg->hDib) {
			//  Initialize DIB for drawing...
			pImg->hDib = ::DrawDibOpen();
			if (pImg->hDib) {
				tmpbRet = ::DrawDibBegin(pImg->hDib,
					hDc,	//  *phDc_dst,								
					pImg->iW_i,								//  -1,				// don't stretch
					pImg->iH_i,								//  -1,				// don't stretch
					&pMsg->bih,
					pImg->iW_org,	//  pImg->iW_org,							//  IMAGE_WIDTH,         // width of image
					pImg->iH_org,	//  pImg->iH_org,							//  IMAGE_HEIGHT,        // height of image
					DDF_BUFFER		//  0																
				);
				if (!tmpbRet) {
					qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("drawCapImages failed, DrawDibBegin failed"));
					goto  errLabel;
				}
			}

		}

		//
#ifdef  __DEBUG__
#if  0
		static  int  kk = 0;
		kk++;
		if (!(kk % 5)) {
			traceLog((TCHAR*)_T("Note: for test"));
			goto  errLabel;
		}
#endif
#endif


		//
		SetRect(&rc, pImg->iX_dst, pImg->iY_dst, pImg->iX_dst + pImg->iW_dst, pImg->iY_dst + pImg->iH_dst);
		MapWindowPoints(hWnd_src, hWnd_dst, (LPPOINT)&rc, 2);

		if (pImg->hDib) {
			HDC  hDc = *phDc_dst;
			//
			if (bDrawOffscreen) {
				hDc = pImg->hOffscreenDc;
			}
			//
			//CCtxQyMc* pQyMc = QY_GET_GBUF();
			if (!pQyMc->appParams.bNoDrawDibDraw_forConfServer) {
				//
				try {
					if (!bDrawOffscreen) {
						qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("drawCapImages failed, bDrawOffscreen is false"));
						goto  errLabel;
#if  0  ndef  __DEBUG__
						tmpbRet = ::DrawDibDraw(pImg->hDib,
							hDc,	//  *phDc_dst,	
							rc.left,									//  dest : left pos
							rc.top,										//  dest : top pos
							rc.right - rc.left,						//  -1,							// don't zoom x
							rc.bottom - rc.top,						//  -1,							// don't zoom y
							&pMsg->bih,									//  bmp header info
							pMsg->memory.m_pBuf,									//  bmp data
							pImg->iX_src,	//  0,											//  src :left
							pImg->iY_src,	//  0,											//  src :top
							pImg->iW_src,	//  pImg->iW_org,								//  IMAGE_WIDTH,					// src : width
							pImg->iH_src,	//  pImg->iH_org,								//  IMAGE_HEIGHT,					// src : height
							DDF_DONTDRAW	//  0											//  DDF_SAME_DRAW								//  use prev params....
						);
						if (tmpbRet) {
							tmpbRet = ::DrawDibDraw(pImg->hDib,
								hDc,	//  *phDc_dst,	
								rc.left,									//  dest : left pos
								rc.top,										//  dest : top pos
								rc.right - rc.left,						//  -1,							// don't zoom x
								rc.bottom - rc.top,						//  -1,							// don't zoom y
								&pMsg->bih,									//  bmp header info
								pMsg->memory.m_pBuf,									//  bmp data
								pImg->iX_src,	//  0,											//  src :left
								pImg->iY_src,	//  0,											//  src :top
								pImg->iW_src,	//  pImg->iW_org,								//  IMAGE_WIDTH,					// src : width
								pImg->iH_src,	//  pImg->iH_org,								//  IMAGE_HEIGHT,					// src : height
								DDF_UPDATE	//  0											//  DDF_SAME_DRAW								//  use prev params....
							);

						}
#endif
					}
					else {

						tmpbRet = ::DrawDibDraw(pImg->hDib,
							hDc,	//  *phDc_dst,	
							0,									//  dest : left pos
							0,										//  dest : top pos
							pImg->iW_i,						//  -1,							// don't zoom x
							pImg->iH_i,						//  -1,							// don't zoom y
							&pMsg->bih,									//  bmp header info
							pMsg->pkt.memory.m_pBuf,									//  bmp data
							0,											//  src :left
							0,											//  src :top
							pImg->iW_org,								//  IMAGE_WIDTH,					// src : width
							pImg->iH_org,								//  IMAGE_HEIGHT,					// src : height
							DDF_DONTDRAW	//  0											//  DDF_SAME_DRAW								//  use prev params....
						);
						if (tmpbRet) {
							tmpbRet = ::DrawDibDraw(pImg->hDib,
								hDc,	//  *phDc_dst,	
								0,									//  dest : left pos
								0,										//  dest : top pos
								pImg->iW_i,						//  -1,							// don't zoom x
								pImg->iH_i,						//  -1,							// don't zoom y
								&pMsg->bih,									//  bmp header info
								pMsg->pkt.memory.m_pBuf,									//  bmp data
								0,											//  src :left
								0,											//  src :top
								pImg->iW_org,								//  IMAGE_WIDTH,					// src : width
								pImg->iH_org,								//  IMAGE_HEIGHT,					// src : height
								DDF_UPDATE	//  0											//  DDF_SAME_DRAW								//  use prev params....
							);

						}
						if (tmpbRet) {
							if (!pImgs->head.hWnd_notifyToDraw) {
								BitBlt(*phDc_dst, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, pImg->hOffscreenDc, pImg->iX_src_i, pImg->iY_src_i, SRCCOPY);
							}
							else {
								pImg->bNeedUpdated_doPost_drawCapImages = TRUE;
								pImgs->head.hWnd_src = hWnd_src;
#ifdef  __DEBUG__
								//  traceLog((TCHAR*)  _T(  "Note: for temporary. pImgs->hWnd_src should be set before this function called"  )  );
#endif
								pImgs->head.cnt_needUpdated++;
								//							   
								if (pImgs->head.cnt_needUpdated == 1 || !(pImgs->head.cnt_needUpdated % 5))
								{
									PostMessage(pImgs->head.hWnd_notifyToDraw, CONST_qyWm_postComm, CONST_qyWmParam_doPost_drawCapImages, 0);
									// doPost_drawCapImages(  hWnd_dst,  *phDc_dst,  0,  pImgs  );
								}
							}
#ifdef  __DEBUG__
							if (pImgs->head.lUserData) {
								//  traceLog((TCHAR*)  _T(  "img:%d,%d,%d,%d, rc %d,%d,%d,%d. hWnd_src %d,hWnd_dst %d"  ),  pImg->iX,  pImg->iY,  pImg->iW,  pImg->iY,  rc.left,  rc.top,  rc.right  -  rc.left,  rc.bottom  -  rc.top,  (  int  )hWnd_src,  (  int  )hWnd_dst  );
							}
#endif
						}

					}
				}
#ifdef  __useMfc__
				catch (CException* e) {
					e->Delete();
					tmpbRet = FALSE;
				}
#endif
				catch (...) {
					tmpbRet = FALSE;
				}
				if (!tmpbRet) {
					qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), _T("IsClient"), 0, _T(""), _T(""), _T("DrawDibDraw failed"));
					goto  errLabel;
				}
			}
		}
	}

	iErr  =  0;

errLabel:

	//  2015/11/27
	if  (  bModified_capImg  )  {
		if  (  pDcDrawParam  )  {
			pDcDrawParam->bModified_capImg  =  TRUE;		
		}
		//pImgs->head.dwModifiedTickCnt_images  =  GetTickCount(  );
		timestamp_renew(  NULL,  &pImgs->head.ts_images,  _T("drawCapImages.l3143"));  //  2017/10/17
	}

	//
	if  (  iErr  )  {
		if  (  !bHintSkipped  )  {
			//CCtxQyMc* pQyMc = QY_GET_GBUF();
			CCtxQmc* pProcInfo = (CCtxQmc  *  )pQyMc->get_pProcInfo();
			qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "drawCapImages: failed"  )  );				
		}
		//  2014/07/31
		old_freeCapImages(  hWnd_src,  0,  pImgs,  hWnd_dst,  phDc_dst,  _T(  "drawCapImages.2445"  ));
	}

	return  iErr;

}






/////////
int  doPost_drawCapImages(  HWND  hWnd_dst,  HDC  hDc_dst,  LPARAM  lParam,  CAP_IMAGES  *  pImages  )
{
	if  (  !hDc_dst  )  return  -1;

	if  (  !pImages->head.cnt_needUpdated  )  return  0;
	

	RECT	rc;
	int  i;
	for  (  i  =  0;  i  <  mycountof(  pImages->mems  );  i  ++  )  {
		 CAP_IMAGE  *  pImg  =  &pImages->mems[i];
		 if  (  pImg->bNeedUpdated_doPost_drawCapImages  )  {
			 pImg->bNeedUpdated_doPost_drawCapImages  =  FALSE;

			 //
			 if  (  !pImg->hOffscreenDc  )  continue;
			 	
			 //
			 SetRect(  &rc,  pImg->iX_dst,  pImg->iY_dst,  pImg->iX_dst  +  pImg->iW_dst,  pImg->iY_dst  +  pImg->iH_dst  );
			 MapWindowPoints(  pImages->head.hWnd_src,  hWnd_dst,  (  LPPOINT  )&rc,  2  );
			 //
			 #ifdef  __DEBUG__
					 HWND  hWnd_src  =  pImages->head.hWnd_src;
					 //  traceLog((TCHAR*)  _T(  "post:%d,%d,%d,%d, rc %d,%d,%d,%d. hWnd_src %d,hWnd_dst %d"  ),  pImg->iX,  pImg->iY,  pImg->iW,  pImg->iY,  rc.left,  rc.top,  rc.right  -  rc.left,  rc.bottom  -  rc.top,  (  int  )hWnd_src,  (  int  )hWnd_dst  );

			 #endif

			 //
			 BitBlt(  hDc_dst,  rc.left,  rc.top,  rc.right  -  rc.left,  rc.bottom  -  rc.top,  pImg->hOffscreenDc,  pImg->iX_src_i,  pImg->iY_src_i,  SRCCOPY  );
		 }
	}

	//
	pImages->head.cnt_needUpdated  =  0;

	return  0;
}


 //  2013/03/02
 int  old_freeCapImage(  HWND    hDlg,  int  idc,  CAP_IMAGE  *  pImg,  HWND  hWnd_dst,  LPCTSTR  hint  )  
{	
	int	iErr	=	-1;
	TCHAR  tHint[256] = _T("");

	if (!hint)  hint = _T("");

	//
	if  (  !pImg->iW_org  ||  !pImg->iH_org  )  return  0;

	HWND  hWnd_src  =  idc  ?  GetDlgItem(  hDlg,  idc  )  :  hDlg;
	if  (  !hWnd_src  )  goto  errLabel;
	
	if  (  IsWindow(  pImg->hWnd_remoteAv  )  )  {
		SendMessage(  pImg->hWnd_remoteAv,  WM_CLOSE,  0,  0  );
	}


	RECT	rc;
	SetRect(  &rc,  pImg->iX_dst,  pImg->iY_dst,  pImg->iX_dst  +  pImg->iW_dst,  pImg->iY_dst  +  pImg->iH_dst  );
	MapWindowPoints(  hWnd_src,  hWnd_dst,  (  LPPOINT  )&rc,  2  );
	//  redrawImage(  hDlg,  idc,  pImg->iX,  pImg->iY,  pImg->iW,  pImg->iH  );
	redrawImage(  hWnd_dst,  0,  rc.left,  rc.top,  rc.right  -  rc.left,  rc.bottom  -  rc.top  );

#ifdef  __DEBUG__
	_sntprintf(tHint, mycountof(tHint), _T("Old_freeCapImage.2519. %s"), hint);
#endif
	capImageDrawClose(  pImg,  tHint);

	//
	memset(  pImg,  0,  sizeof(  pImg[0]  )  );

	//
	//  pImgs->bResized  =  TRUE;

	iErr  =  0;

errLabel:

	 return  iErr;
}


 int  old_freeCapImage(HWND    hDlg, HWND  hWndIDC, CAP_IMAGE* pImg, HWND  hWnd_dst, LPCTSTR  hint)
 {
	 int	iErr = -1;
	 TCHAR  tHint[256] = _T("");

	 if (!hint)  hint = _T("");

	 //
	 if (!pImg->iW_org || !pImg->iH_org)  return  0;

	 HWND  hWnd_src = hWndIDC;//idc ? GetDlgItem(hDlg, idc) : hDlg;
	 if (!hWnd_src)  goto  errLabel;

	 if (IsWindow(pImg->hWnd_remoteAv)) {
		 SendMessage(pImg->hWnd_remoteAv, WM_CLOSE, 0, 0);
	 }


	 RECT	rc;
	 SetRect(&rc, pImg->iX_dst, pImg->iY_dst, pImg->iX_dst + pImg->iW_dst, pImg->iY_dst + pImg->iH_dst);
	 MapWindowPoints(hWnd_src, hWnd_dst, (LPPOINT)&rc, 2);
	 //  redrawImage(  hDlg,  idc,  pImg->iX,  pImg->iY,  pImg->iW,  pImg->iH  );
	 redrawImage(hWnd_dst, 0, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);

#ifdef  __DEBUG__
	 _sntprintf(tHint, mycountof(tHint), _T("Old_freeCapImage.2519. %s"), hint);
#endif
	 capImageDrawClose(pImg, tHint);

	 //
	 memset(pImg, 0, sizeof(pImg[0]));

	 //
	 //  pImgs->bResized  =  TRUE;

	 iErr = 0;

 errLabel:

	 return  iErr;
 }

 //
 int  freeCapImage(HWND    hDlg, HWND  hCtrl, CAP_IMAGE* pImg, HWND  hWnd_dst)
 {
	 int	iErr = -1;

	 //
	 if (!pImg->iW_org || !pImg->iH_org)  return  0;

	 HWND  hWnd_src = hCtrl ? hCtrl : hDlg;
	 if (!hWnd_src)  goto  errLabel;

	 if (IsWindow(pImg->hWnd_remoteAv)) {
		 SendMessage(pImg->hWnd_remoteAv, WM_CLOSE, 0, 0);
	 }


	 RECT	rc;
	 SetRect(&rc, pImg->iX_dst, pImg->iY_dst, pImg->iX_dst + pImg->iW_dst, pImg->iY_dst + pImg->iH_dst);
	 MapWindowPoints(hWnd_src, hWnd_dst, (LPPOINT)&rc, 2);
	 //  redrawImage(  hDlg,  idc,  pImg->iX,  pImg->iY,  pImg->iW,  pImg->iH  );
	 redrawImage(hWnd_dst, 0, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);

	 capImageDrawClose(pImg,_T("freeCapImage.2557"));

	 //
	 memset(pImg, 0, sizeof(pImg[0]));

	 //
	 //  pImgs->bResized  =  TRUE;

	 iErr = 0;

 errLabel:

	 return  iErr;
 }


  //


  //  2013/03/02
  int  old_freeCapImageByTaskId(  HWND    hDlg,  int  idc,  int  iTaskId,  CAP_IMAGES  *  pImgs,  HWND  hWnd_dst  )
 {
	 int				i;
	 CAP_IMAGE		*	pImg;

#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "freeCapImageByTaskId called"  )  );
#endif

	 for  (  i  =  0;  i  <  mycountof(  pImgs->mems  );  i  ++  )  {
		  pImg  =  &pImgs->mems[i];
		  //
		  if  (  !pImg->iW_org  ||  !pImg->iH_org  )  continue;
		  //  
		  if  (  pImg->iTaskId  ==  iTaskId  )  {

			  old_freeCapImage(  hDlg,  idc,  pImg,  hWnd_dst,  _T(  "old_freeCapImageByTaskId.2598"  ));

			  //
			  pImgs->head.bResized  =  TRUE;

			  //  2016/02/21
			  //pImgs->head.dwModifiedTickCnt_images  =  GetTickCount(  );
			  timestamp_renew(  NULL,  &pImgs->head.ts_images,_T("old_freeCapImageByTaskId.l3357"));
		  }
	 }

	 return  0;
}


  //
  int  freeCapImageByTaskId(HWND    hDlg, HWND  hCtrl, int  iTaskId, CAP_IMAGES* pImgs, HWND  hWnd_dst)
  {
	  int				i;
	  CAP_IMAGE* pImg;

#ifdef  __DEBUG__
	  traceLog((TCHAR*)_T("freeCapImageByTaskId called"));
#endif

	  for (i = 0; i < mycountof(pImgs->mems); i++) {
		  pImg = &pImgs->mems[i];
		  //
		  if (!pImg->iW_org || !pImg->iH_org)  continue;
		  //  
		  if (pImg->iTaskId == iTaskId) {

			  freeCapImage(hDlg, hCtrl, pImg, hWnd_dst);

			  //
			  pImgs->head.bResized = TRUE;

			  //  2016/02/21
			  //pImgs->head.dwModifiedTickCnt_images  =  GetTickCount(  );
			  timestamp_renew(NULL, &pImgs->head.ts_images,_T("freeCapImageByTaskId.l3389"));
		  }
	  }

	  return  0;
  }



  //  2013/03/02
  //  2010/09/12

  //int  iifreeCapImageBySth(  HWND    hDlg,  int  idc,  int  iTaskId,  QY_MESSENGER_ID	*	pIdInfo,  CAP_IMAGES  *  pImgs,  HWND  hWnd_dst  )
 int  old_freeCapImageBySth(  CTX_qm_thread  *  pCqt,  HWND    hDlg,  int  idc,  int  iTaskId,  QY_MESSENGER_ID	*	pIdInfo,  CAP_IMAGES  *  pImgs,  HWND  hWnd_dst  )
{
	 int				i;
	 CAP_IMAGE		*	pImg;

	 if  (  !pImgs  )  return  -1;

#ifdef  __DEBUG__
		traceLog((TCHAR*)  _T(  "freeCapImageBySth called"  )  );
#endif

	 //
	 for  (  i  =  0;  i  <  mycountof(  pImgs->mems  );  i  ++  )  {
		  pImg  =  &pImgs->mems[i];
		  //
		  if  (  !pImg->iW_org  ||  !pImg->iH_org  )  continue;
		  //  
		  if  (  pImg->iTaskId  !=  iTaskId  )  continue;
		  if  (  pIdInfo  &&  pIdInfo->ui64Id  )  {
			  if  (  pImg->idInfo_sender.ui64Id  !=  pIdInfo->ui64Id  )  continue;
		  }

		  old_freeCapImage(  hDlg,  idc,  pImg,  hWnd_dst,  _T(  "old_freeCapImageBySth.2640"  ));

		  pImgs->head.bResized  =  TRUE;
		  //
		  //pImgs->head.dwModifiedTickCnt_images  =  myGetTickCount(  pCqt  );  //  2017/09/28
		  timestamp_renew(  pCqt,  &pImgs->head.ts_images,_T("old_freeCapImageBySth.l3429"));
	 }

	 return  0;
}


 //
 int  freeCapImageBySth(CTX_qm_thread* pCqt, HWND    hDlg, HWND  hCtrl, int  iTaskId, QY_MESSENGER_ID* pIdInfo, CAP_IMAGES* pImgs, HWND  hWnd_dst)
 {
	 int				i;
	 CAP_IMAGE* pImg;

	 if (!pImgs)  return  -1;

#ifdef  __DEBUG__
	 traceLog((TCHAR*)_T("freeCapImageBySth called"));
#endif

	 //
	 for (i = 0; i < mycountof(pImgs->mems); i++) {
		 pImg = &pImgs->mems[i];
		 //
		 if (!pImg->iW_org || !pImg->iH_org)  continue;
		 //  
		 if (pImg->iTaskId != iTaskId)  continue;
		 if (pIdInfo && pIdInfo->ui64Id) {
			 if (pImg->idInfo_sender.ui64Id != pIdInfo->ui64Id)  continue;
		 }

		 freeCapImage(hDlg, hCtrl, pImg, hWnd_dst);

		 pImgs->head.bResized = TRUE;
		 //
		 //pImgs->head.dwModifiedTickCnt_images  =  myGetTickCount(  pCqt  );  //  2017/09/28
		 timestamp_renew(pCqt, &pImgs->head.ts_images,_T("freeCapImageBySth.l3464"));
	 }

	 return  0;
 }



 //  2013/03/02
 int  old_freeCapImages(  HWND    hDlg,  int  idc,  CAP_IMAGES  *  pImgs,  HWND  hWnd_dst,  HDC  *  phDc_dst,  LPCTSTR  hint  )
{
	 int  i;
	 CAP_IMAGE		*	pImg;
	 TCHAR				tHint[256] = _T("");

	 //
	 if (!hint)  hint = _T("");

	 //
	 for  (  i  =  0;  i  <  mycountof(  pImgs->mems  );  i  ++  )  {
		  pImg  =  &pImgs->mems[i];

		  //
#ifdef  __DEBUG__
		  _sntprintf(tHint, mycountof(tHint), _T("old_freeCapImages.2663 %s"), hint);
#endif
		  //
		  old_freeCapImage(  hDlg,  idc,  pImg,  hWnd_dst,  tHint);
		  //
		  pImgs->head.bResized  =  TRUE;
	 }
	 pImgs->head.usCnt  =  0;
	 //
	 //pImgs->head.dwModifiedTickCnt_images  =  0;	//  2017/09/28
	 timestamp_renew(  NULL,  &pImgs->head.ts_images,_T("old_freeCapImages.l3498"));	//  2017/10/17
	 //
	 if  (  hWnd_dst  &&  phDc_dst  &&  *phDc_dst  )  {
		 int		iRet;

		 #ifndef  __WINCE__
				  _ASSERT(  IsWindow(  hWnd_dst  )  );
		 #endif

		 iRet  =  ::ReleaseDC(  hWnd_dst,  *phDc_dst  );  *phDc_dst  =  NULL;
		 #ifdef  __DEBUG__
				 traceLogA(  (char*)"freeCapImages: iRet %d",  iRet  );
		 #endif
	 }

	 return  0;
}

 int  old_freeCapImages(HWND    hDlg, HWND hWndIDC, CAP_IMAGES* pImgs, HWND  hWnd_dst, HDC* phDc_dst, LPCTSTR  hint)
 {
	 int  i;
	 CAP_IMAGE* pImg;
	 TCHAR				tHint[256] = _T("");

	 //
	 if (!hint)  hint = _T("");

	 //
	 for (i = 0; i < mycountof(pImgs->mems); i++) {
		 pImg = &pImgs->mems[i];

		 //
#ifdef  __DEBUG__
		 _sntprintf(tHint, mycountof(tHint), _T("old_freeCapImages.2663 %s"), hint);
#endif
		 //
		 old_freeCapImage(hDlg, hWndIDC, pImg, hWnd_dst, tHint);
		 //
		 pImgs->head.bResized = TRUE;
	 }
	 pImgs->head.usCnt = 0;
	 //
	 //pImgs->head.dwModifiedTickCnt_images  =  0;	//  2017/09/28
	 timestamp_renew(NULL, &pImgs->head.ts_images,_T("old_freeCapImages.l3541"));	//  2017/10/17
	 //
	 if (hWnd_dst && phDc_dst && *phDc_dst) {
		 int		iRet;

#ifndef  __WINCE__
		 _ASSERT(IsWindow(hWnd_dst));
#endif

		 iRet = ::ReleaseDC(hWnd_dst, *phDc_dst);  *phDc_dst = NULL;
#ifdef  __DEBUG__
		 traceLogA((char*)"freeCapImages: iRet %d", iRet);
#endif
	 }

	 return  0;
 }
 //
 int  freeCapImages(HWND    hDlg, HWND  hCtrl, CAP_IMAGES* pImgs, HWND  hWnd_dst, HDC* phDc_dst)
 {
	 int  i;
	 CAP_IMAGE* pImg;

	 for (i = 0; i < mycountof(pImgs->mems); i++) {
		 pImg = &pImgs->mems[i];

		 freeCapImage(hDlg, hCtrl, pImg, hWnd_dst);
		 //
		 pImgs->head.bResized = TRUE;
	 }
	 pImgs->head.usCnt = 0;
	 //
	 //pImgs->head.dwModifiedTickCnt_images  =  0;	//  2017/09/28
	 timestamp_renew(NULL, &pImgs->head.ts_images,_T("freeCapImages.l3574"));	//  2017/10/17
	 //
	 if (hWnd_dst && phDc_dst && *phDc_dst) {
		 int		iRet;

#ifndef  __WINCE__
		 _ASSERT(IsWindow(hWnd_dst));
#endif

		 iRet = ::ReleaseDC(hWnd_dst, *phDc_dst);  *phDc_dst = NULL;
#ifdef  __DEBUG__
		 traceLogA((char*)"freeCapImages: iRet %d", iRet);
#endif
	 }

	 return  0;
 }

