
#include	"stdafx.h"

#include	"qyPrecomp.h"
#include	<winsock2.h>
#include	<windows.h>
#include	<stddef.h>
#include	<assert.h>
#include	<tchar.h>
#ifndef  __WINCE__
	#include	<vfw.h>
#else
	#ifdef  __TEST__
		#include	<vfw.h>
	#endif

	#include	<mmreg.h>
	#include	<MSAcm.h>
#endif
#include	<Wincrypt.h>
#include	<time.h>

#include	"qyCommon.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qmOpenCommon.h"
#include	"qyMsgFunc.h"

#include	"qySyncCommProc.h"
#include	"genericQueue.h"
#include	"qyq2.h"				//  2009/05/13

#include	"qnmCommProc_mis.h"
#include	"qnmPcComm.h"
#include	"qnmAssetsCommProc.h"
#include	"qnmSpCommProc.h"
#include	"qwmNetworkStatusCommProc.h"
#include	"qyTCharCommProc.h"
#include	"qnmCustom.h"
#include	"qySyncCommProc.h"
#include	"qmCrypt.h"
#include	"qnmFwCommProc.h"
#include <ancCommProc.h>

 

//////////////////////

 int  transferVideoDataResp2Stream(  unsigned  int  uiStreamId,  TRANSFER_VIDEO_dataResp  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;


	 //  qyShowInfo1(  CONST_qyShowType_debug,  (  ""  ),  _T(  ""  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "    transferVideoData2stream: uiTranNo_openAvDev %d"  ),  pReq->uiTranNo_openAvDev  );


	 //  2017/09/05
	 if  (  pReq->idInfo.ui64Id  )  {			//  2009/05/31
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  (  void  *  )&pReq->idInfo.ui64Id,  sizeof(  pReq->idInfo.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  pReq->uiTranNo_openAvDev  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_openVideoDev,  (  void  *  )pReq->uiTranNo_openAvDev,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->usFps  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usFps,  (  void  *  )pReq->usFps,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->tSelectTime  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tSelectTime,  (  void  *  )&pReq->tSelectTime,  sizeof(  pReq->tSelectTime  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->usCnt_pkts  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt_pkts,  (  void  *  )pReq->usCnt_pkts,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->usDiff_pkts  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usDiff_pkts,  (  void  *  )pReq->usDiff_pkts,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }


	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2TransferVideoDataResp(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int							iErr		=	-1;
	 //  p0;
	 TRANSFER_VIDEO_dataResp	*	pContent	=	(  TRANSFER_VIDEO_dataResp  *  )p1;
	 //  QY_CFGITEM					*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_transferVideoDataResp  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_start:
				   pContent->uiType  =  uiStreamId;
				   break;
			 case  CONST_qnmCfgId_messengerId:  //  2017/0
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->idInfo.ui64Id  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiTranNo_openVideoDev:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiTranNo_openAvDev  )  )  goto  errLabel;
				   //  qyShowInfo1(  CONST_qyShowType_debug,  (  ""  ),  _T(  ""  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "    tmpHandler_stream2TransferVideoData: uiTranNo_openAvDev %d"  ),  pContent->uiTranNo_openAvDev  );
				   break;
			 case  CONST_qnmCfgId_usFps:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usFps  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_tSelectTime:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->tSelectTime  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usCnt_pkts:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usCnt_pkts  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usDiff_pkts:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usDiff_pkts  )  )  goto  errLabel;
				   break;

			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}


 //
 int  transferVideoData2Stream(  unsigned  int  uiStreamId,  TRANSFER_VIDEO_DATA  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;


	 //  qyShowInfo1(  CONST_qyShowType_debug,  (  ""  ),  _T(  ""  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "    transferVideoData2stream: uiTranNo_openAvDev %d"  ),  pReq->uiTranNo_openAvDev  );


	 if  (  pReq->uiTranNo_openAvDev  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_openVideoDev,  (  void  *  )pReq->uiTranNo_openAvDev,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 
	 //
#if  0
	 if  (  pReq->uiEventId_lastRecvd_ii  )  {
		 //if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiEventId,  (  void  *  )pReq->uiEventId_lastRecvd_ii,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
#endif

	 //
	 if  (  pReq->usCnt  )  {

		 if  (  pReq->usCnt  >  mycountof(  pReq->mems  )  )  goto  errLabel;

		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt,  (  void  *  )pReq->usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;
		 //
		 for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {
			  TRANSFER_VIDEO_dataMemHead	*	pMem	=	&pReq->mems[i];

			  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_mem,  0,  &ptr,  &len  )  )  goto  errLabel;

#if  0
			  if  (  pMem->usIndex_ii  )  {
				  if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_index,  (  void  *  )pMem->usIndex_ii,  0,  &ptr,  &len  )  )  goto  errLabel;
			  }
#endif
			  //
			  if  (  pMem->idInfo.ui64Id  )  {			//  2009/05/31
				  if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  (  void  *  )&pMem->idInfo.ui64Id,  sizeof(  pMem->idInfo.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
			  }
			  //  2012/01/09
			  if  (  pMem->uiTranNo_openAvDev  )  {
				  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_openVideoDev,  (  void  *  )pMem->uiTranNo_openAvDev,  0,  &ptr,  &len  )  )  goto  errLabel;
			  }

			  //  在elapseInMs_fromLastPkt为0时，传uiSampleTimeInMs.
			  if (!pMem->usElapseInMs_fromLastPkt) 
			  {
				  if (pMem->uiSampleTimeInMs) {		//  2009/05/04
					  if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_uiSampleTimeInMs, (void*)pMem->uiSampleTimeInMs, 0, &ptr, &len))  goto  errLabel;
				  }
			  }

			  //
			  if (pMem->usElapseInMs_fromLastPkt) {
				  if (data2Stream(CONST_qyDataType_short, CONST_ancCfgId_usElapseInMs_fromLastPkt, (void*)pMem->usElapseInMs_fromLastPkt, 0, &ptr, &len)) goto  errLabel;
			  }


			  //  2015/01/15
			  if  (  pMem->uiPts  )  {
				  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiPts,  (  void  *  )pMem->uiPts,  0,  &ptr,  &len  )  )  goto  errLabel;
			  }

			  //
			  if (0 != pMem->ucbKeyFrame)
			  {
				  if (0 != data2Stream(CONST_qyDataType_byte, CONST_qnmCfgId_ucbKeyFrame, (void*)pMem->ucbKeyFrame, 0, &ptr, &len)) goto errLabel;
			  }


			  //  2013/11/15
#if  0  //  2016/12/27
			  if  (  pMem->uiEventId_lastRecvd  )  {
				  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiEventId,  (  void  *  )pMem->uiEventId_lastRecvd,  0,  &ptr,  &len  )  )  goto  errLabel;	 
			  }
#endif

			  //
			  if  (  pMem->uiLen  )  {
				  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiLen,  (  void  *  )pMem->uiLen,  0,  &ptr,  &len  )  )  goto  errLabel;
			  }


			  //
			  //
			  //   2017/09/05
			  if  (  pMem->stat.usFps  )  {		 
				  if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usFps,  (  void  *  )pMem->stat.usFps,  0,  &ptr,  &len  )  )  goto  errLabel;
			  }
			  if  (  pMem->stat.usCnt_pkts  )  {		 
				  if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt_pkts,  (  void  *  )pMem->stat.usCnt_pkts,  0,  &ptr,  &len  )  )  goto  errLabel;
			  }
			  if  (  pMem->stat.tSelectTime  )  {	//  2008/12/05	  	 
				  //
				  if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tSelectTime,  (  void  *  )&pMem->stat.tSelectTime,  sizeof(  pMem->stat.tSelectTime  ),  &ptr,  &len  )  )  goto  errLabel;
			  }



			  //
			  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }

	 }

	 if  (  pReq->uiLen  )  {
		 if  (  data2Stream(  CONST_qyDataType_lData,  CONST_qnmCfgId_rawData,  (  void  *  )pReq->buf,  pReq->uiLen,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2TransferVideoData(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 TRANSFER_VIDEO_DATA	*	pContent	=	(  TRANSFER_VIDEO_DATA  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
			 case  CONST_imCommType_transferVideoData:

				   switch  (  tmp_cfgId  )  {
							case  CONST_qnmCfgId_start:
								  pContent->uiType  =  uiStreamId;
								  break;
							case  CONST_qnmCfgId_uiTranNo_openVideoDev:
								  if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiTranNo_openAvDev  )  )  goto  errLabel;
								  //  qyShowInfo1(  CONST_qyShowType_debug,  (  ""  ),  _T(  ""  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "    tmpHandler_stream2TransferVideoData: uiTranNo_openAvDev %d"  ),  pContent->uiTranNo_openAvDev  );
								  break;
#if  0  //  2016/12/26
							case  CONST_qnmCfgId_uiEventId:
								  if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiEventId_lastRecvd_ii  )  )  goto  errLabel;
								  break;
#endif
							case  CONST_qnmCfgId_usCnt:
								  if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usCnt  )  )  goto  errLabel;
								  //  if  (  pContent->usCnt  >=  mycountof(  pContent->mems  )  )  
								  if  (  pContent->usCnt  >  mycountof(  pContent->mems  )  )  //  2011/01/17
								  {
									  #ifdef  __DEBUG__
											  traceLogA(  (char*)  "tmpHandler_stream2TransferVideoDataGrp failed: usCnt is too big"  );  
									  #endif
									  goto  errLabel;
								  }
								  int  i;	//  2009/05/20
								  for  (  i  =  0;  i  <  pContent->usCnt;  i  ++  )  {			
									   memset(  &pContent->mems[i],  0,  sizeof(  pContent->mems[i]  )  );								 
								  }
								  break;
							case  CONST_qnmCfgId_rawData:
								  pContent->uiLen  =  sizeof(  pContent->buf  );
								  if  (  getFieldData_lData(  pItem,  pContent->buf,  &pContent->uiLen  )  )  goto  errLabel;
								  break;
							default:
									break;
				   }
				   break;

			 case  CONST_imCommType_mem:  {
				   TRANSFER_VIDEO_dataMemHead  *  pMem		=	NULL;
				   //
				   if  (  pContent->tmpInternal.usCnt_mems  >=  mycountof(  pContent->mems  )  )  {
					   #ifdef  __DEBUG__
							   traceLogA(  (char*)  "tmpHandler_stream2TransferVideoDataGrp failed: usCnt_mems is too big"  );  
					   #endif
					   goto  errLabel;
				   }
				   //
				   pMem  =  &pContent->mems[pContent->tmpInternal.usCnt_mems];				   
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_start:
							     break;
								 //
						   case  CONST_qnmCfgId_messengerId:			//  2009/05/31
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pMem->idInfo.ui64Id  )  )  goto  errLabel;
							     break;
								 //  2012/01/09
						   case  CONST_qnmCfgId_uiTranNo_openVideoDev:								  
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->uiTranNo_openAvDev  )  )  goto  errLabel;
								 break;
								 //
						   case  CONST_qnmCfgId_uiSampleTimeInMs:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->uiSampleTimeInMs  )  )  goto  errLabel;
								 break;
								 //
						   case  CONST_ancCfgId_usElapseInMs_fromLastPkt:
							     if (getFieldData_short(pItem, (short*)&pMem->usElapseInMs_fromLastPkt))goto  errLabel;
							     break;
								 //  2015/01/15
						   case  CONST_qnmCfgId_uiPts:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->uiPts  )  )  goto  errLabel;
								 break;
						   case CONST_qnmCfgId_ucbKeyFrame:
							   if (0 != getFieldData_char(pItem, (char*)&pMem->ucbKeyFrame))goto errLabel;
							   break;


								 //
#if  0  //  2016/12/26
						   case  CONST_qnmCfgId_uiEventId:  //  2013/11/15
								 if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->uiEventId_lastRecvd  )  )  goto  errLabel;
								 break;
#endif
								 //
						   case  CONST_qnmCfgId_uiLen:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->uiLen  )  )  goto  errLabel;
							     break;
								 //
								 //  2017/09/05			
						   case  CONST_qnmCfgId_usFps:
								  if  (  getFieldData_short(  pItem,  (  short  *  )&pMem->stat.usFps  )  )  goto  errLabel;
								  break;
							case  CONST_qnmCfgId_tLastTime_showFrameInfo_020534:
								  if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pMem->stat.tLastTime_showFrameInfo_020534  )  )  goto  errLabel;
								  break;
							case  CONST_qnmCfgId_usCnt_pkts:
								  if  (  getFieldData_short(  pItem,  (  short  *  )&pMem->stat.usCnt_pkts  )  )  goto  errLabel;
								  break;
							case  CONST_qnmCfgId_tSelectTime:
								  if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pMem->stat.tSelectTime  )  )  goto  errLabel;
								  break;

								 //
						   case  CONST_qnmCfgId_null:
							     pContent->tmpInternal.usCnt_mems  ++  ;
							     break;
						   default:
									{
										int  ii  =  0;
									}
									break;
				   }
				   //

				   }
				   break;


			 default:
					break;
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
}



///////////////



 int  transferAudioData2Stream(  unsigned  int  uiStreamId,  TRANSFER_AUDIO_DATA  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;


	 //  qyShowInfo1(  CONST_qyShowType_debug,  (  ""  ),  _T(  ""  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "    transferVideoData2stream: uiTranNo_openAvDev %d"  ),  pReq->uiTranNo_openAvDev  );


	 if  (  pReq->uiTranNo_openAvDev  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_openAudioDev,  (  void  *  )pReq->uiTranNo_openAvDev,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->tLastTime_showFrameInfo_020534  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tLastTime_showFrameInfo_020534,  (  void  *  )&pReq->tLastTime_showFrameInfo_020534,  sizeof(  pReq->tLastTime_showFrameInfo_020534  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->usCnt_pkts  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt_pkts,  (  void  *  )pReq->usCnt_pkts,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pReq->usCnt  )  {

		 if  (  pReq->usCnt  >  mycountof(  pReq->mems  )  )  goto  errLabel;

		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt,  (  void  *  )pReq->usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;
		 //
		 for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {
			  TRANSFER_AUDIO_dataMemHead	*	pMem	=	&pReq->mems[i];

			  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_mem,  0,  &ptr,  &len  )  )  goto  errLabel;

			  //
			#if  0
			  if  (  pMem->usIndex_ii  )  {			//  2009/05/18
				  if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_index,  (  void  *  )pMem->usIndex_ii,  0,  &ptr,  &len  )  )  goto  errLabel;
			  }
			#endif

			  //
			  if  (  pMem->idInfo.ui64Id  )  {
				  if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  (  void  *  )&pMem->idInfo.ui64Id,  sizeof(  pMem->idInfo.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
			  }
			  
			  //
			  if  (  pMem->uiTranNo_openAvDev  )  {	//  2013/08/04
				  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_openAudioDev,  (  void  *  )pMem->uiTranNo_openAvDev,  0,  &ptr,  &len  )  )  goto  errLabel;
			  }

			  // elapseInms_fromLastPkt为0时，传iSampleTimeInms
			  //if (!pMem->usElapseInMs_fromLastPkt) 
			  {
				  if (pMem->uiSampleTimeInMs) {	//  2009/05/04
					  if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_uiSampleTimeInMs, (void*)pMem->uiSampleTimeInMs, 0, &ptr, &len))  goto  errLabel;
				  }
			  }

			  //
			  if (pMem->usElapseInMs_fromLastPkt) {
				  if (data2Stream(CONST_qyDataType_short, CONST_ancCfgId_usElapseInMs_fromLastPkt, (void*)pMem->usElapseInMs_fromLastPkt, 0, &ptr, &len)) goto  errLabel;
			  }

			  //
			  if  (  pMem->ui_rtTimeLen  )  {		//  2009/05/27
				  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_ui_rtTimeLen,  (  void  *  )pMem->ui_rtTimeLen,  0,  &ptr,  &len  )  )  goto  errLabel;
			  }

			  //  2015/09/10
			  if  (  pMem->uiPts  )  {
				  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiPts,  (  void  *  )pMem->uiPts,  0,  &ptr,  &len  )  )  goto  errLabel;
			  }

			  //
			  //  if  (  pMem->uiLen  )  {
			  //	  if  (  data2Stream(  CONST_qyDataType_lData,  CONST_qnmCfgId_rawData,  (  void  *  )pMem->buf,  pMem->uiLen,  &ptr,  &len  )  )  goto  errLabel;
			  //  }			  
			  if  (  pMem->uiLen  )  {
				  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiLen,  (  void  *  )pMem->uiLen,  0,  &ptr,  &len  )  )  goto  errLabel;
			  }

			  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }

	 }

	 if  (  pReq->uiLen  )  {
		 if  (  data2Stream(  CONST_qyDataType_lData,  CONST_qnmCfgId_rawData,  (  void  *  )pReq->buf,  pReq->uiLen,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2TransferAudioData(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 TRANSFER_AUDIO_DATA	*	pContent	=	(  TRANSFER_AUDIO_DATA  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
			 case  CONST_imCommType_transferAudioData:
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_start:
							     pContent->uiType  =  uiStreamId;
								 break;
						   case  CONST_qnmCfgId_uiTranNo_openAudioDev:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiTranNo_openAvDev  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_tLastTime_showFrameInfo_020534:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->tLastTime_showFrameInfo_020534  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_usCnt_pkts:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usCnt_pkts  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_usCnt:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usCnt  )  )  goto  errLabel;

								 if  (  pContent->usCnt  >  mycountof(  pContent->mems  )  )  goto  errLabel;

								 //  ÏÂÃæÒª½øÐÐ³õÊ¼»¯£¬·ÅÔÚÕâÀïÊÇÒòÎªµ£ÐÄÏÂÃæµÄÊý¾ÝÈç¹û³ö´í£¬usCnt½«°üº¬ÁËÒ»Ð©´íÎóÊý¾Ý
								 int  i;
								 for  (  i  =  0;  i  <  pContent->usCnt;  i  ++  )  {			
									  memset(  &pContent->mems[i],  0,  sizeof(  pContent->mems[i]  )  );
								 }
							     break;
						   case  CONST_qnmCfgId_rawData:
								  pContent->uiLen  =  sizeof(  pContent->buf  );
								  if  (  getFieldData_lData(  pItem,  pContent->buf,  &pContent->uiLen  )  )  goto  errLabel;
								  break;
						   default:
								  break;
				   }
				   break;
			 case  CONST_imCommType_mem:  {
				   TRANSFER_AUDIO_dataMemHead  *  pMem		=	NULL;
				   //
				   if  (  pContent->tmpInternal.usCnt_mems  >=  mycountof(  pContent->mems  )  )  {
					   traceLogA(  (char*)  "tmpHandler_stream2TransferAudioData failed: usCnt_mems is too big"  );  
					   goto  errLabel;
				   }
				   //
				   pMem  =  &pContent->mems[pContent->tmpInternal.usCnt_mems];				   
				   switch  (  tmp_cfgId  )  {
							//
						#if  0
						   case  CONST_qnmCfgId_index:		//  2009/05/18
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pMem->usIndex_ii  )  )  goto  errLabel;
								 break;
						#endif
								 //
						   case  CONST_qnmCfgId_messengerId:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pMem->idInfo.ui64Id  )  )  goto  errLabel;
							     break;
								 
								 //
						   case  CONST_qnmCfgId_uiTranNo_openAudioDev:		//  2013/08/04
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->uiTranNo_openAvDev  )  )  goto  errLabel;
								 break;

								 //
						   case  CONST_qnmCfgId_uiSampleTimeInMs:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->uiSampleTimeInMs  )  )  goto  errLabel;
							     break;
								 //
						   case  CONST_ancCfgId_usElapseInMs_fromLastPkt:
							     if (getFieldData_short(pItem, (short*)&pMem->usElapseInMs_fromLastPkt))  goto  errLabel;
							     break;
								 //
						   case  CONST_qnmCfgId_ui_rtTimeLen:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->ui_rtTimeLen  )  )  goto  errLabel;
								 break;

								 //  2015/09/10
						   case  CONST_qnmCfgId_uiPts:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->uiPts  )  )  goto  errLabel;
							     break;

								 //
						   //  case  CONST_qnmCfgId_rawData:
						   //	     pMem->uiLen  =  sizeof(  pMem->buf  );
						   //	     if  (  getFieldData_lData(  pItem,  pMem->buf,  &pMem->uiLen  )  )  goto  errLabel;
						   //	     break;
						   case  CONST_qnmCfgId_uiLen:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->uiLen  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_null:
							     pContent->tmpInternal.usCnt_mems  ++  ;
							     break;
						   default:
									break;
				   }
				   //

				   }
				   break;
			 default:
					break;
	 }


	 iErr  =  0;
errLabel:
	 return  iErr;
}


 int  transferAudioDataResp2Stream(  unsigned  int  uiStreamId,  TRANSFER_AUDIO_dataResp  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pReq->uiTranNo_openAvDev  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_openAudioDev,  (  void  *  )pReq->uiTranNo_openAvDev,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pReq->usCnt_pkts  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt_pkts,  (  void  *  )pReq->usCnt_pkts,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }


	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2TransferAudioDataResp(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int							iErr		=	-1;
	 //  p0;
	 TRANSFER_AUDIO_dataResp	*	pContent	=	(  TRANSFER_AUDIO_dataResp  *  )p1;
	 //  QY_CFGITEM					*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_transferAudioDataResp  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_start:
				   pContent->uiType  =  uiStreamId;
				   break;
			 case  CONST_qnmCfgId_uiTranNo_openAudioDev:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiTranNo_openAvDev  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usCnt_pkts:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usCnt_pkts  )  )  goto  errLabel;
				   break;
			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}


///


 int  remoteAssistReq2Stream(  unsigned  int  uiStreamId,  REMOTE_ASSIST_REQ  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pReq->uiTranNo_openAvDev  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_openAudioDev,  (  void  *  )pReq->uiTranNo_openAvDev,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //  2017/08/23
	 if  (  pReq->idInfo_imGrp_related.ui64Id  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_grp_related,  (  void  *  )&pReq->idInfo_imGrp_related.ui64Id,  sizeof(  pReq->idInfo_imGrp_related  ),  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usRaType,  (  void  *  )pReq->u.usRaType,  0,  &ptr,  &len  )  )  goto  errLabel;
	 switch  (  pReq->u.usRaType  )  {
			 case  CONST_usRaType_pointerEvent:
				   if  (  pReq->u.pointerEvent.ucButtonMask  &&  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucButtonMask,  (  void  *  )pReq->u.pointerEvent.ucButtonMask,  0,  &ptr,  &len  )  )  goto  errLabel;
				   if  (  pReq->u.pointerEvent.x  &&  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_x,  (  void  *  )pReq->u.pointerEvent.x,  0,  &ptr,  &len  )  )  goto  errLabel;
				   if  (  pReq->u.pointerEvent.y  &&  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_y,  (  void  *  )pReq->u.pointerEvent.y,  0,  &ptr,  &len  )  )  goto  errLabel;
				   //  2016/12/26
				   //if  (  pReq->u.pointerEvent.uiEventId  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiEventId,  (  void  *  )pReq->u.pointerEvent.uiEventId,  0,  &ptr,  &len  )  )  goto  errLabel;
				   break;
			 case  CONST_usRaType_keyEvent:
				   if  (  pReq->u.keyEvent.key  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_key,  (  void  *  )pReq->u.keyEvent.key,  0,  &ptr,  &len  )  )  goto  errLabel;
				   if  (  pReq->u.keyEvent.ucbDown  &&  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbDown,  (  void  *  )pReq->u.keyEvent.ucbDown,  0,  &ptr,  &len  )  )  goto  errLabel;
				   break;
			 default:
					break;
	 }


	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2RemoteAssistReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int							iErr		=	-1;
	 //  p0;
	 REMOTE_ASSIST_REQ			*	pContent	=	(  REMOTE_ASSIST_REQ  *  )p1;
	 //  QY_CFGITEM					*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_remoteAssistReq  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_start:
				   pContent->uiType  =  uiStreamId;
				   break;
			 case  CONST_qnmCfgId_uiTranNo_openAudioDev:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiTranNo_openAvDev  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_idInfo_grp_related:  //  2017/08/24
				   if  (  getFieldData_l64(  pItem,  ( __int64  *  )&pContent->idInfo_imGrp_related.ui64Id  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usRaType:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->u.usRaType  )  )  goto  errLabel;
				   break;
			 default:
					break;
	 }

	 switch  (  pContent->u.usRaType  )  {
			 case  CONST_usRaType_pointerEvent:
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_ucButtonMask:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->u.pointerEvent.ucButtonMask  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_x:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->u.pointerEvent.x  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_y:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->u.pointerEvent.y  )  )  goto  errLabel;
								 break;
#if  0  //  2016/12/27
						   case  CONST_qnmCfgId_uiEventId:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->u.pointerEvent.uiEventId  )  )  goto  errLabel;
								 break;
#endif
						   default:
								   break;
				   }
				   break;
			 case  CONST_usRaType_keyEvent:
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_key:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->u.keyEvent.key  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_ucbDown:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->u.keyEvent.ucbDown  )  )  goto  errLabel;
							   	 break;
						   default:
								   break;
				   }
				   break;
			 default:
					break;
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
}



//////////////


 int  taskInteractionReq2Stream(  unsigned  int  uiStreamId,  TASK_INTERACTION_REQ  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
	
	 //
	 if (pReq->ucbResp) {
		 if (data2Stream(CONST_qyDataType_char, CONST_qnmCfgId_ucbResp, (void*)pReq->ucbResp, 0, &ptr, &len))  goto  errLabel;
	 }

	 //
	 if (pReq->ucStep) {
		 if (data2Stream(CONST_qyDataType_char, CONST_qnmCfgId_nStep, (void*)pReq->ucStep, 0, &ptr, &len))  goto  errLabel;
	 }

	 //
	 if  (  pReq->usOp  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usOp,  (  void  *  )pReq->usOp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->tStartTime_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tStartTime_org,  &pReq->tStartTime_org,  sizeof(  pReq->tStartTime_org  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->uiTranNo_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_org,  (  void  *  )pReq->uiTranNo_org,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }


	 //  2015/02/17
	 if  (  tmp_htonAvStream( &pReq->avStream,  &ptr, &len )  )  goto errLabel;

	 //
	 if  (  pReq->talkerDesc[0]  &&  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_talkerDesc,  pReq->talkerDesc,  lstrlen(  pReq->talkerDesc  ),  &ptr,  &len  )  )  goto  errLabel;
 
	 //
	 if (pReq->idInfo_compere.ui64Id) {
		 if (data2Stream(CONST_qyDataType_l64, CONST_qnmCfgId_idInfo_compere, (void*)&pReq->idInfo_compere.ui64Id, sizeof(pReq->idInfo_compere), &ptr, &len))  goto  errLabel;
	 }



	 //  2015/07/30
	 /*
	 if  (  pReq->idInfo_speaker.ui64Id  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_speaker,  (  void  *  )&pReq->idInfo_speaker.ui64Id,  sizeof(  pReq->idInfo_speaker  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 */

	 //
	 if (pReq->iHkStatus) {
		 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_iHkStatus, (void*)pReq->iHkStatus, 0, &ptr, &len)) {
			 goto  errLabel;
		 }
	 }

	 //
	 if (pReq->ucbNvr) {
		 if (data2Stream(CONST_qyDataType_char, CONST_qnmCfgId_ucbNvr, (void*)pReq->ucbNvr, 0, &ptr, &len)) {
			 goto  errLabel;
		 }
	 }

	 //
	 if  (  pReq->idInfo_imGrp_related.ui64Id  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_grp_related,  (  void  *  )&pReq->idInfo_imGrp_related.ui64Id,  sizeof(  pReq->idInfo_imGrp_related  ),  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}

 int  tmpHandler_stream2TaskInteractionReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 TASK_INTERACTION_REQ	*	pContent	=	(  TASK_INTERACTION_REQ  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 BOOL	bProcessed  =  FALSE;	//  2015/02/17

	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 //
	 //if  (  uiStreamId  !=  CONST_imCommType_taskInteractionReq  )  goto  errLabel;

	 //
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
			 case  CONST_imCommType_taskInteractionReq:
				   switch  (  tmp_cfgId  )  {
						 case  CONST_qnmCfgId_start:
							   pContent->uiType  =  uiStreamId;
							   break;
						 case  CONST_qnmCfgId_ucbResp:
							   if (getFieldData_char(pItem, (char*)&pContent->ucbResp))  goto  errLabel;
							   break;
						 case  CONST_qnmCfgId_nStep:
							   if (getFieldData_char(pItem, (char*)&pContent->ucStep))  goto  errLabel;
							   break;

						 case  CONST_qnmCfgId_usOp:
							   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usOp  )  )  goto  errLabel;
							   break;
						 case  CONST_qnmCfgId_tStartTime_org:
							   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->tStartTime_org  )  )  goto  errLabel;
							   break;
						 case  CONST_qnmCfgId_uiTranNo_org:
							   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiTranNo_org  )  )  goto  errLabel;
							   break;
						 case  CONST_qnmCfgId_talkerDesc:
							   if  (  getFieldData_wStr(  pItem,  pContent->talkerDesc,  mycountof(  pContent->talkerDesc  )  )  )  goto  errLabel;
							   break;
						 case  CONST_qnmCfgId_idInfo_compere:
							   if (getFieldData_l64(pItem, (__int64*)&pContent->idInfo_compere.ui64Id))  goto  errLabel;
							   break;

							   /*
						 case  CONST_qnmCfgId_idInfo_speaker:  //  2015/07/30
							   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->idInfo_speaker.ui64Id  )  )  goto  errLabel;
							   break;
							   */
						 case  CONST_qnmCfgId_iHkStatus:
							   if (getFieldData_long(pItem, (long*)&pContent->iHkStatus))  goto  errLabel;
							   break;
						 case  CONST_qnmCfgId_ucbNvr:
							   if (getFieldData_char(pItem, (char*)&pContent->ucbNvr))  goto  errLabel;
							   break;
						 case  CONST_qnmCfgId_idInfo_grp_related:
							   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->idInfo_imGrp_related.ui64Id  )  )  goto  errLabel;
							   break;
						 default:
								break;
				   }
				   break;
			 case  CONST_imCommType_avStream:				   
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_start:
							     break;
						   case  CONST_qnmCfgId_null:
							     break;			
						   default:
								//  2015/02/17
								//if  (  tmp_ntohAvTranInfo(  pItem,  &pContent->tranInfo,  &bProcessed  )  )  goto  errLabel;
							    if  (  tmp_ntohAvStream(  pItem,  &pContent->avStream,  &bProcessed  )  )  goto errLabel;
								if  (  bProcessed  )  {
									iErr  =  0;  goto  errLabel;
								}
								//
								break;
				   }
				   break;
			 default:
					break;
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
}

/////////////////////////

 int tmp_htonConfRequestingMems( CONF_requesting_mems* pReq, char** ppBuf, unsigned  int* uiBufSize)
 {
	 
		 int				iErr = -1;
		 int				i = 0;
		 char* ptr = *ppBuf;
		 unsigned  int		len = *uiBufSize;

		 if (!pReq)  return  -1;
		 if (!*ppBuf)  return  -1;

		 //
		 unsigned  int  uiStreamId = CONST_imCommType_confRequestingMems;
		 //
		 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_start, (void*)uiStreamId, 0, &ptr, &len))  goto  errLabel;


		 //
		 if (pReq->usCnt) {
			 //
			 if (pReq->usCnt > mycountof(pReq->mems))  goto  errLabel;
			 //
			 if (data2Stream(CONST_qyDataType_short, CONST_qnmCfgId_usCnt, (void*)pReq->usCnt, 0, &ptr, &len))  goto  errLabel;
			 //
			 for (i = 0; i < pReq->usCnt; i++) {
				 CONF_requesting_mem* pMem = &pReq->mems[i];

				 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_start, (void*)CONST_imCommType_mem, 0, &ptr, &len))  goto  errLabel;

				 if (pMem->idInfo.ui64Id) {
					 if (data2Stream(CONST_qyDataType_l64, CONST_qnmCfgId_messengerId, (void*)&pMem->idInfo.ui64Id, sizeof(pMem->idInfo.ui64Id), &ptr, &len))  goto  errLabel;
				 }

				 //
				 if (pMem->desc[0] && data2Stream(CONST_qyDataType_wStr, CONST_qnmCfgId_talkerDesc, pMem->desc, lstrlen(pMem->desc), &ptr, &len))  goto  errLabel;


				 //
				 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_null, 0, 0, &ptr, &len))  goto  errLabel;
			 }
		 }

		 //
		 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_null, 0, 0, &ptr, &len))  goto  errLabel;


		 //
		 iErr = 0;
	 errLabel:
		 if (!iErr) {
			 *ppBuf = ptr;
			 *uiBufSize = len;
		 }
		 return  iErr;

	 }
	

 int  tmp_ntohConfRequestingMems(CTX_stream2Data* pCtx, unsigned  int  uiStreamId, QY_CFGITEM_ntoh_U* pItem,CONF_requesting_mems  *  pContent,  BOOL *pbProcessed)
 {
	 int							iErr = -1;
	 //
	 BOOL  bProcessed = FALSE;

	 if (!pContent)  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(&tmp_cfgId, &pItem->head.cfgId, sizeof(short));

	 //
	 bProcessed = true;
	 switch (uiStreamId) {
	 case  CONST_imCommType_confRequestingMems:
		 switch (tmp_cfgId) {
		 case  CONST_qnmCfgId_start:
			 break;

		 case  CONST_qnmCfgId_usCnt:
			 if (getFieldData_short(pItem, (short*)&pContent->usCnt))  goto  errLabel;
			 //
			 if (pContent->usCnt > mycountof(pContent->mems))  goto  errLabel;
			 break;
		 default:
			 break;
		 }
		 break;
	 case  CONST_imCommType_mem: {
		 CONF_requesting_mem* pMem = NULL;
		 //
		 if (pContent->tmpInternal.usCnt_mems >= mycountof(pContent->mems)) {
#ifdef  __DEBUG__
			 traceLogA((char*)"tmpHandler_stream2RefreshWebContactsInfo failed: usCnt_mems is too big");
#endif
			 goto  errLabel;
		 }
		 //
		 pMem = &pContent->mems[pContent->tmpInternal.usCnt_mems];
		 switch (tmp_cfgId) {
			 
				 case  CONST_qnmCfgId_messengerId:
					   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pMem->idInfo.ui64Id  )  )  goto  errLabel;
					   break;
					   
		 case  CONST_qnmCfgId_talkerDesc:	//  2013/07/18
			 if (getFieldData_wStr(pItem, pMem->desc,  mycountof(pMem->desc)))  goto  errLabel;
			 break;
		 case  CONST_qnmCfgId_null:
			 pContent->tmpInternal.usCnt_mems++;
			 break;
		 default:
			 bProcessed = false;

			 break;
		 }
		 //
	 }
							   break;
	 default:
		 break;

	 }
	 iErr = 0;
 errLabel:

	 if (pbProcessed)  *pbProcessed = bProcessed;

	 return  iErr;
 }


 /////////////////////////

 int tmp_htonConfLayoutParam(ConfLayoutParam* pReq, char** ppBuf, unsigned  int* uiBufSize)
 {

	 int				iErr = -1;
	 int				i = 0;
	 char* ptr = *ppBuf;
	 unsigned  int		len = *uiBufSize;

	 if (!pReq)  return  -1;
	 if (!*ppBuf)  return  -1;

	 //
	 unsigned  int  uiStreamId = CONST_imCommType_confLayoutParam;
	 //
	 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_start, (void*)uiStreamId, 0, &ptr, &len))  goto  errLabel;
	 
	 //
	 if (pReq->oneBigLayoutParam.ucbOneBigLayout) {
		 if (data2Stream(CONST_qyDataType_char, CONST_qnmCfgId_ucbOneBigLayout, (void*)pReq->oneBigLayoutParam.ucbOneBigLayout, 0, &ptr, &len))goto  errLabel;
	 }
	 //
	 if (pReq->oneBigLayoutParam.ui64Id) {
		 if (data2Stream(CONST_qyDataType_l64, CONST_qnmCfgId_messengerId_oneBig, (void*)&pReq->oneBigLayoutParam.ui64Id, sizeof(pReq->oneBigLayoutParam.ui64Id), &ptr, &len))goto  errLabel;
	 }

	 //
	 if (pReq->enlargeParam.usEnlargeType) {
		 if (data2Stream(CONST_qyDataType_short, CONST_qnmCfgId_usEnlargeType, (void*)pReq->enlargeParam.usEnlargeType, 0, &ptr, &len))  goto  errLabel;
	 }
	 //
	 if (pReq->enlargeParam.ui64Id) {
		 if (data2Stream(CONST_qyDataType_l64, CONST_qnmCfgId_messengerId, (void*)&pReq->enlargeParam.ui64Id, sizeof(pReq->enlargeParam.ui64Id), &ptr, &len))  goto  errLabel;
	 }
	 if (pReq->enlargeParam.tn_v) {
		 if (data2Stream(CONST_qyDataType_l32, CONST_qnmCfgId_uiTranNo_openVideoDev, (void*)pReq->enlargeParam.tn_v, 0, &ptr, &len))goto  errLabel;
	 }
	 if (pReq->ipcParam.iChannel) {
		 if (data2Stream(CONST_qyDataType_l32, CONST_qnmCfgId_iChannel, (void*)pReq->ipcParam.iChannel, 0, &ptr, &len))goto  errLabel;
	 }

	 if (pReq->ipcParam.channelName) {
		 if (data2Stream(CONST_qyDataType_wStr, CONST_qnmCfgId_channelName, pReq->ipcParam.channelName, lstrlen(pReq->ipcParam.channelName), &ptr, &len))goto  errLabel;
	 }


	 //
	 if (pReq->resp.ii) {
		if(data2Stream(CONST_qyDataType_l32 , CONST_qnmCfgId_ii , (void*)pReq->resp.ii , 0 , &ptr , &len))goto errLabel;
	 }
	 //
	 if (pReq->resp.curr_idinfo) {
		 if (data2Stream(CONST_qyDataType_l64, CONST_qnmCfgId_curr_idinfo, (void*)&pReq->resp.curr_idinfo, sizeof(pReq->resp.curr_idinfo), &ptr, &len))  goto  errLabel;
	 }
	 //
	 if (pReq->phoneEnlargeParam.x) {
		 if (data2Stream(CONST_qyDataType_short, CONST_qnmCfgId_enlarge_x, (void*)pReq->phoneEnlargeParam.x, 0, &ptr, &len))  goto  errLabel;
	 }
	 if (pReq->phoneEnlargeParam.y) {
		 if (data2Stream(CONST_qyDataType_short, CONST_qnmCfgId_enlarge_y, (void*)pReq->phoneEnlargeParam.y, 0, &ptr, &len))  goto  errLabel;
	 }
	 if (pReq->phoneEnlargeParam.usEnlargeType) {
		 if (data2Stream(CONST_qyDataType_short, CONST_qnmCfgId_phone_usEnlargeType, (void*)pReq->phoneEnlargeParam.usEnlargeType, 0, &ptr, &len))  goto  errLabel;
	 }

	 //
	 if (pReq->respVideoStatus.bAmplification) {
		 if (data2Stream(CONST_qyDataType_l32, CONST_qnmCfgId_amplificationType, (void*)pReq->respVideoStatus.bAmplification, 0, &ptr, &len))goto errLabel;
	 }

	 //
	 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_null, 0, 0, &ptr, &len))  goto  errLabel;


	 //
	 iErr = 0;
 errLabel:
	 if (!iErr) {
		 *ppBuf = ptr;
		 *uiBufSize = len;
	 }
	 return  iErr;

 }


 int  tmp_ntohConfLayoutParam(CTX_stream2Data* pCtx, unsigned  int  uiStreamId, QY_CFGITEM_ntoh_U* pItem, ConfLayoutParam* pContent, BOOL* pbProcessed)
 {
	 int							iErr = -1;
	 //
	 BOOL  bProcessed = FALSE;

	 if (!pContent)  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(&tmp_cfgId, &pItem->head.cfgId, sizeof(short));

	 //
	 bProcessed = true;
	 switch (uiStreamId) {
	 case  CONST_imCommType_confLayoutParam:
		 switch (tmp_cfgId) {
		 case  CONST_qnmCfgId_start:
			 break;
		 case  CONST_qnmCfgId_ucbOneBigLayout:
			 if (getFieldData_char(pItem, (char*)&pContent->oneBigLayoutParam.ucbOneBigLayout))goto  errLabel;
			 break;
		 case  CONST_qnmCfgId_messengerId_oneBig:
			 if (getFieldData_l64(pItem, (__int64*)&pContent->oneBigLayoutParam.ui64Id))goto  errLabel;
			 break;

		 case  CONST_qnmCfgId_usEnlargeType:
			 if (getFieldData_short(pItem, (short*)&pContent->enlargeParam.usEnlargeType))goto  errLabel;
			 break;
		 case  CONST_qnmCfgId_messengerId:
			 if (getFieldData_l64(pItem, (__int64*)&pContent->enlargeParam.ui64Id))goto  errLabel;
			 break;
		 case  CONST_qnmCfgId_uiTranNo_openVideoDev:
			 if (getFieldData_long(pItem, (long*)&pContent->enlargeParam.tn_v))goto  errLabel;
			 break;
			 //
		 case  CONST_qnmCfgId_iChannel:
			 if (getFieldData_long(pItem, (long*)&pContent->ipcParam.iChannel))goto  errLabel;
			 break;
		 case CONST_qnmCfgId_channelName:
			 if (getFieldData_wStr(pItem, pContent->ipcParam.channelName, mycountof(pContent->ipcParam.channelName)))goto  errLabel;
			 break;

		 case  CONST_qnmCfgId_ii:
			 if(getFieldData_long(pItem , (long*)&pContent->resp.ii)) goto errLabel;
			 break;
		 case  CONST_qnmCfgId_curr_idinfo:
			 if (getFieldData_l64(pItem, (__int64*)&pContent->resp.curr_idinfo))goto  errLabel;
			 break;
		 case  CONST_qnmCfgId_enlarge_x:
			 if (getFieldData_short(pItem, (short*)&pContent->phoneEnlargeParam.x))goto  errLabel;
			 break;
		 case  CONST_qnmCfgId_enlarge_y:
			 if (getFieldData_short(pItem, (short*)&pContent->phoneEnlargeParam.y))goto  errLabel;
			 break;
		 case  CONST_qnmCfgId_phone_usEnlargeType:
			 if (getFieldData_short(pItem, (short*)&pContent->phoneEnlargeParam.usEnlargeType))goto  errLabel;
			 break;
		 case  CONST_qnmCfgId_amplificationType:
			 if (getFieldData_long(pItem, (long*)&pContent->respVideoStatus.bAmplification)) goto errLabel;
			 break;

		 default:
			 break;
		 }
		 break;
	 default:
		 break;

	 }
	 iErr = 0;
 errLabel:

	 if (pbProcessed)  *pbProcessed = bProcessed;

	 return  iErr;
 }


 /////////////////////




 /*
 					 QY_MESSENGER_ID								idInfo;
					 unsigned  char									ucbActive;
*/

 int  confKey2Stream(  unsigned  int  uiStreamId,  CONF_KEY  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pReq->idInfo_imGrp_related.ui64Id  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_grp_related,  (  void  *  )&pReq->idInfo_imGrp_related.ui64Id,  sizeof(  pReq->idInfo_imGrp_related  ),  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if (pReq->idInfo_compere.ui64Id) {
		 if (data2Stream(CONST_qyDataType_l64, CONST_qnmCfgId_idInfo_compere, (void*)&pReq->idInfo_compere.ui64Id, sizeof(pReq->idInfo_compere.ui64Id), &ptr, &len))  goto  errLabel;
	 }

	 //  2010/12/29
	 if  (  pReq->usLayoutType_starter  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usLayoutType,  (  void  *  )pReq->usLayoutType_starter,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  pReq->usCnt  )  {
		 //
		 if  (  pReq->usCnt  >  mycountof(  pReq->mems  )  )  goto  errLabel;
		 //
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt,  (  void  *  )pReq->usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;
		 //
		 for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {
			  VIDEO_CONFERENCE_MEM	*  pMem	  =		&pReq->mems[i];
		  				
			  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_mem,  0,  &ptr,  &len  )  )  goto  errLabel;

#if  0
			  if  (  pMem->idInfo.ui64Id  )  {
				  if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  (  void  *  )&pMem->idInfo.ui64Id,  sizeof(  pMem->idInfo.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
			  }
			  				  //  2009/05/31
				  if  (  tmp_htonAvTranInfo(  &pMem->tranInfo,  &ptr,  &len  )  )  goto  errLabel;
#endif
				  //
				  if  (  tmp_htonAvStream(  &pMem->avStream,  &ptr,  &len  )  )  goto  errLabel;

				  //
#if  0
				  if  (  pMem->ucbActive  )  {
					  if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbActive,  (  void  *  )pMem->ucbActive,  0,  &ptr,  &len  )  )  goto  errLabel;
				  }
#endif

				  //  2013/07/18
				  if  (  pMem->usIndex_speaker  )  {
					  if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usIndex_speaker,  (  void  *  )pMem->usIndex_speaker,  0,  &ptr,  &len  )  )  goto  errLabel;
				  }

				  //
				  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
	 }


	 //
	 if (pReq->requestingMems.usCnt) {
		 if (tmp_htonConfRequestingMems(&pReq->requestingMems, &ptr, &len))  goto  errLabel;
	 }

	 //
	 //if (pReq->confLayoutParam.enlargeParam.ui64Id) 
	 {
		 if (tmp_htonConfLayoutParam(&pReq->confLayoutParam, &ptr, &len))goto  errLabel;
	 }


	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 

	 //
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 //
 int  tmpHandler_stream2confKey(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int							iErr		=	-1;
	 //  p0;
	 CONF_KEY	*	pContent	=	(  CONF_KEY  *  )p1;
	 //  QY_CFGITEM					*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 BOOL  bProcessed  =  FALSE;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 
	 //
	 int  uiStreamId_1; uiStreamId_1 = 0;
	 if (pCtx->index_streamId > 0) {
		 uiStreamId_1 = pCtx->uiStreamIds[1];
	 }


	 if (uiStreamId_1 == CONST_imCommType_confRequestingMems) {
		 tmp_ntohConfRequestingMems(pCtx, uiStreamId, pItem, &pContent->requestingMems,  &bProcessed);
	 }
	 else if (uiStreamId_1 == CONST_imCommType_confLayoutParam) {
		 tmp_ntohConfLayoutParam(pCtx, uiStreamId, pItem, &pContent->confLayoutParam, &bProcessed);
	 }
	 else {
		 //
		 switch (uiStreamId) {
		 case  CONST_imCommType_confKey:
			 switch (tmp_cfgId) {
			 case  CONST_qnmCfgId_start:
				 pContent->uiType = uiStreamId;
				 break;
			 case  CONST_qnmCfgId_idInfo_grp_related:
				 if (getFieldData_l64(pItem, (__int64*)&pContent->idInfo_imGrp_related.ui64Id))  goto  errLabel;
				 break;
				 //
			 case  CONST_qnmCfgId_idInfo_compere:
				 if (getFieldData_l64(pItem, (__int64*)&pContent->idInfo_compere.ui64Id))  goto  errLabel;
				 break;
				 //
			 case  CONST_qnmCfgId_usLayoutType:
				 if (getFieldData_short(pItem, (short*)&pContent->usLayoutType_starter))  goto  errLabel;
				 break;

			 case  CONST_qnmCfgId_usCnt:
				 if (getFieldData_short(pItem, (short*)&pContent->usCnt))  goto  errLabel;
				 //
				 if (pContent->usCnt > mycountof(pContent->mems))  goto  errLabel;
				 break;
			 default:
				 break;
			 }
			 break;
		 case  CONST_imCommType_mem: {
			 VIDEO_CONFERENCE_MEM* pMem = NULL;
			 //
			 if (pContent->tmpInternal.usCnt_mems >= mycountof(pContent->mems)) {
#ifdef  __DEBUG__
				 traceLogA((char*)"tmpHandler_stream2RefreshWebContactsInfo failed: usCnt_mems is too big");
#endif
				 goto  errLabel;
			 }
			 //
			 pMem = &pContent->mems[pContent->tmpInternal.usCnt_mems];
			 switch (tmp_cfgId) {
				 /*
					 case  CONST_qnmCfgId_messengerId:
						   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pMem->idInfo.ui64Id  )  )  goto  errLabel;
						   break;
						   */
#if  0
			 case  CONST_qnmCfgId_ucbActive:
				 if (getFieldData_char(pItem, (char*)&pMem->ucbActive))  goto  errLabel;
				 break;
#endif
			 case  CONST_qnmCfgId_usIndex_speaker:	//  2013/07/18
				 if (getFieldData_short(pItem, (short*)&pMem->usIndex_speaker))  goto  errLabel;
				 break;
			 case  CONST_qnmCfgId_null:
				 pContent->tmpInternal.usCnt_mems++;
				 break;
			 default:
				 /*
				 //  2009/05/31
				 if  (  tmp_ntohAvTranInfo(  pItem,  &pMem->tranInfo,  &bProcessed  )  )  goto  errLabel;
				 if  (  bProcessed  )  {
					 iErr  =  0;  goto  errLabel;
				 }
				 */
				 break;
			 }
			 //
		 }
								   break;
		 case  CONST_imCommType_avStream: {
			 VIDEO_CONFERENCE_MEM* pMem = NULL;
			 //
			 if (pContent->tmpInternal.usCnt_mems >= mycountof(pContent->mems)) {
#ifdef  __DEBUG__
				 traceLogA((char*)"tmpHandler_stream2RefreshWebContactsInfo failed: usCnt_mems is too big");
#endif
				 goto  errLabel;
			 }
			 //
			 pMem = &pContent->mems[pContent->tmpInternal.usCnt_mems];

			 //
			 switch (tmp_cfgId) {
			 case  CONST_qnmCfgId_start:
				 break;
			 default:
				 if (tmp_ntohAvStream(pItem, &pMem->avStream, &bProcessed))  goto  errLabel;
				 if (bProcessed) {
					 iErr = 0;  goto errLabel;
				 }
				 break;
			 }

			 //
		 }
										break;
		 default:
			 break;

		 }
	 }


	 iErr  =  0;
errLabel:
	 return  iErr;
}


//////////////////////////////




int  statusConfLayoutParam2Stream(unsigned  int  uiStreamId, StatusConfLayoutParam* pReq, char* buf, unsigned  int* uiBufSize)
{
	int				iErr = -1;
	int				i = 0;
	char* ptr = buf;
	unsigned  int		len = *uiBufSize;

	if (!pReq)  return  -1;
	if (!buf)  return  -1;

	if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_start, (void*)uiStreamId, 0, &ptr, &len))  goto  errLabel;

	if (pReq->idInfo_imGrp_related.ui64Id) {
		if (data2Stream(CONST_qyDataType_l64, CONST_qnmCfgId_idInfo_grp_related, (void*)&pReq->idInfo_imGrp_related.ui64Id, sizeof(pReq->idInfo_imGrp_related), &ptr, &len))  goto  errLabel;
	}



	//
	//if (pReq->confLayoutParam.enlargeParam.ui64Id) 
	{
		if (tmp_htonConfLayoutParam(&pReq->confLayoutParam, &ptr, &len))goto  errLabel;
	}


	//
	if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_null, 0, 0, &ptr, &len))  goto  errLabel;


	//
	iErr = 0;
errLabel:
	if (!iErr) {
		*uiBufSize = *uiBufSize - len;
	}
	return  iErr;

}


//
int  tmpHandler_stream2statusConfLayoutParam(CTX_stream2Data* pCtx, void* p0, void* p1, unsigned  int  uiStreamId, QY_CFGITEM_ntoh_U* pItem)
{
	int							iErr = -1;
	//  p0;
	StatusConfLayoutParam* pContent = (StatusConfLayoutParam*)p1;
	//  QY_CFGITEM					*	pItem		=	(  QY_CFGITEM  *  )p2;
	//  long						lVal;
	BOOL  bProcessed = FALSE;

	if (!pContent)  goto  errLabel;

	unsigned  short  tmp_cfgId;
	memcpy(&tmp_cfgId, &pItem->head.cfgId, sizeof(short));


	//
	int  uiStreamId_1; uiStreamId_1 = 0;
	if (pCtx->index_streamId > 0) {
		uiStreamId_1 = pCtx->uiStreamIds[1];
	}



	if (uiStreamId_1 == CONST_imCommType_confLayoutParam) {
		tmp_ntohConfLayoutParam(pCtx, uiStreamId, pItem, &pContent->confLayoutParam, &bProcessed);
	}
	else {
		//
		switch (uiStreamId) {
		case  CONST_imCommType_statusConfLayoutParam:
			switch (tmp_cfgId) {
			case  CONST_qnmCfgId_start:
				pContent->uiType = uiStreamId;
				break;
			case  CONST_qnmCfgId_idInfo_grp_related:
				if (getFieldData_l64(pItem, (__int64*)&pContent->idInfo_imGrp_related.ui64Id))  goto  errLabel;
				break;
				//
			default:
				break;
			}
			break;
		}
			//
		
	}


	iErr = 0;
errLabel:
	return  iErr;
}












////////////////////////

















 //  2010/12/27
 int  confLayout2Stream(  unsigned  int  uiStreamId,  CONF_LAYOUT  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 //
	 if (pReq->ucbResp) {
		 if (data2Stream(CONST_qyDataType_char, CONST_qnmCfgId_ucbResp, (void*)pReq->ucbResp, 0, &ptr, &len)) goto  errLabel;
	 }

	 //
	 if  (  pReq->idInfo_imGrp_related.ui64Id  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_grp_related,  (  void  *  )&pReq->idInfo_imGrp_related.ui64Id,  sizeof(  pReq->idInfo_imGrp_related  ),  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pReq->usLayoutType  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usLayoutType,  (  void  *  )pReq->usLayoutType,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if (pReq->usOp) {
		 if (data2Stream(CONST_qyDataType_short, CONST_qnmCfgId_usOp, (void*)pReq->usOp, 0, &ptr, &len))  goto  errLabel;
	 }

	 //
	 if (tmp_htonConfLayoutParam(&pReq->confLayoutParam, &ptr, &len)) {
		 goto  errLabel;
	 }


	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 //
 int  tmpHandler_stream2confLayout(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int							iErr		=	-1;
	 //  p0;
	 CONF_LAYOUT	*	pContent	=	(  CONF_LAYOUT  *  )p1;
	 //  QY_CFGITEM					*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;

	 //
	 int  uiStreamId_1; uiStreamId_1 = 0;
	 if (pCtx->index_streamId > 0) {
		 uiStreamId_1 = pCtx->uiStreamIds[1];
	 }

	 //
	 BOOL  bProcessed; bProcessed = false;

	 //
	 if (uiStreamId_1 == CONST_imCommType_confLayoutParam) {
		 tmp_ntohConfLayoutParam(pCtx, uiStreamId, pItem, &pContent->confLayoutParam, &bProcessed);
	 }
	 else {


		 unsigned  short  tmp_cfgId;
		 memcpy(&tmp_cfgId, &pItem->head.cfgId, sizeof(short));

		 switch (uiStreamId) {
		 case  CONST_imCommType_confLayout:
			 switch (tmp_cfgId) {
			 case  CONST_qnmCfgId_start:
				 pContent->uiType = uiStreamId;
				 break;
			 case  CONST_qnmCfgId_ucbResp:
				 if (getFieldData_char(pItem, (char*)&pContent->ucbResp)) goto  errLabel;
				 break;
			 case  CONST_qnmCfgId_idInfo_grp_related:
				 if (getFieldData_l64(pItem, (__int64*)&pContent->idInfo_imGrp_related.ui64Id))  goto  errLabel;
				 break;
			 case  CONST_qnmCfgId_usOp:
				 if (getFieldData_short(pItem, (short*)&pContent->usOp))  goto  errLabel;
				 break;
			 case  CONST_qnmCfgId_usLayoutType:
				 if (getFieldData_short(pItem, (short*)&pContent->usLayoutType))  goto  errLabel;
				 //
				 break;
#if 0
			 case  CONST_qnmCfgId_usEnlargeType:
				 if (getFieldData_short(pItem, (short*)&pContent->confLayoutParam.usEnlargeType))goto  errLabel;
				 break;
			 case  CONST_qnmCfgId_messengerId:
				 if (getFieldData_l64(pItem, (__int64*)&pContent->confLayoutParam.ui64Id))goto  errLabel;
				 break;
			 case  CONST_qnmCfgId_uiTranNo_openVideoDev:
				 if (getFieldData_long(pItem, (long*)&pContent->confLayoutParam.tn_v))goto  errLabel;
				 break;
#endif
			 default:
				 break;
			 }
			 break;
		 default:
			 break;
		 }

	 }

	 //
	 iErr  =  0;
errLabel:
	 return  iErr;
}



 /////////////////
 //  2010/12/27
 int  confNvrInfo2Stream(unsigned  int  uiStreamId, ConfNvrInfo* pReq, char* buf, unsigned  int* uiBufSize)
 {
	 int				iErr = -1;
	 int				i = 0;
	 char* ptr = buf;
	 unsigned  int		len = *uiBufSize;

	 if (!pReq)  return  -1;
	 if (!buf)  return  -1;

	 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_start, (void*)uiStreamId, 0, &ptr, &len))  goto  errLabel;

	 if (pReq->ucbResp) {
		 if (data2Stream(CONST_qyDataType_char, CONST_qnmCfgId_ucbResp, (void*)pReq->ucbResp, 0, &ptr, &len)) goto  errLabel;
	 }

	 if (pReq->idInfo_imGrp_related.ui64Id) {
		 if (data2Stream(CONST_qyDataType_l64, CONST_qnmCfgId_idInfo_grp_related, (void*)&pReq->idInfo_imGrp_related.ui64Id, sizeof(pReq->idInfo_imGrp_related), &ptr, &len))  goto  errLabel;
	 }
	 if (pReq->idInfo_requester.ui64Id) {
		 if (data2Stream(CONST_qyDataType_l64, CONST_qnmCfgId_idInfo_requester, (void*)&pReq->idInfo_requester.ui64Id, sizeof(pReq->idInfo_requester.ui64Id), &ptr, &len)) goto  errLabel;
	 }

	 //
	 if (pReq->nvrInfo.usCnt) {
		 //CONST_qnmCfgId_idInfo_nvr
		 if (data2Stream(CONST_qyDataType_l64, CONST_qnmCfgId_idInfo_nvr, (void*)&pReq->nvrInfo.ui64Id, 0, &ptr, &len))goto  errLabel;

		 //
		 if (data2Stream(CONST_qyDataType_short, CONST_qnmCfgId_usCnt, (void*)pReq->nvrInfo.usCnt, 0, &ptr, &len))goto  errLabel;

		 for (i = 0; i < pReq->nvrInfo.usCnt; i++) {
			 IpcInfo* pMem = &pReq->nvrInfo.mems[i];
			 //
			 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_start, (void*)CONST_imCommType_mem, 0, &ptr, &len))  goto  errLabel;

			 //
			 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_iChannel, (void*)pMem->iChannel, 0, &ptr, &len))goto  errLabel;

			 if (data2Stream(CONST_qyDataType_wStr, CONST_qnmCfgId_name, pMem->name, lstrlen(pMem->name), &ptr, &len))goto  errLabel;

			 if (data2Stream(CONST_qyDataType_str, CONST_qnmCfgId_ip, pMem->ip, strlen(pMem->ip), &ptr, &len))goto  errLabel;

			 //
			 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_null, 0, 0, &ptr, &len))  goto  errLabel;
		 }


	 }


	 //
	 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_null, 0, 0, &ptr, &len))  goto  errLabel;

	 iErr = 0;
 errLabel:
	 if (!iErr) {
		 *uiBufSize = *uiBufSize - len;
	 }
	 return  iErr;

 }


 //
 int  tmpHandler_stream2confNvrInfo(CTX_stream2Data* pCtx, void* p0, void* p1, unsigned  int  uiStreamId, QY_CFGITEM_ntoh_U* pItem)
 {
	 int							iErr = -1;
	 //  p0;
	 ConfNvrInfo* pContent = (ConfNvrInfo*)p1;
	 //  QY_CFGITEM					*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;

	 if (!pContent)  goto  errLabel;

	 //
	 int  uiStreamId_1; uiStreamId_1 = 0;
	 if (pCtx->index_streamId > 0) {
		 uiStreamId_1 = pCtx->uiStreamIds[1];
	 }

	 //
	 BOOL  bProcessed; bProcessed = false;

	 //
	 



		 unsigned  short  tmp_cfgId;
		 memcpy(&tmp_cfgId, &pItem->head.cfgId, sizeof(short));

		 switch (uiStreamId) {
		 case  CONST_imCommType_confNvrInfo:
			 switch (tmp_cfgId) {
			 case  CONST_qnmCfgId_start:
				 pContent->uiType = uiStreamId;
				 break;
			 case  CONST_qnmCfgId_ucbResp:
				 if (getFieldData_char(pItem, (char*)&pContent->ucbResp)) goto  errLabel;
				 break;
			 case  CONST_qnmCfgId_idInfo_grp_related:
				 if (getFieldData_l64(pItem, (__int64*)&pContent->idInfo_imGrp_related.ui64Id))  goto  errLabel;
				 break;
			 case  CONST_qnmCfgId_idInfo_requester:
				 if (getFieldData_l64(pItem, (__int64*)&pContent->idInfo_requester.ui64Id))goto  errLabel;
				 break;
				 //
			 case CONST_qnmCfgId_idInfo_nvr:

				 if (getFieldData_l64(pItem, (__int64*)&pContent->nvrInfo.ui64Id))goto  errLabel;
				 break;
			 case  CONST_qnmCfgId_usCnt:
				 if (getFieldData_short(pItem, (short*)&pContent->nvrInfo.usCnt))goto  errLabel;
				 //
				 if (pContent->nvrInfo.usCnt >= mycountof(pContent->nvrInfo.mems)) {
					 showInfo_open0(0, 0, _T("stream2ConfNvrInfo"));
					 goto  errLabel;
				 }
				 //
				 break;

			 default:
				 break;
			 }
			 break;
		 case  CONST_imCommType_mem:

			 if (pContent->tmpInternal.usCnt_mems >= mycountof(pContent->nvrInfo.mems)) {
#ifdef  __DEBUG__
				 traceLogA((char*)"tmpHandler_stream2ConfNvrInfo failed: usCnt_mems is too big");
#endif
				 goto  errLabel;
			 }
			 //
			 IpcInfo* pMem;
			 pMem = &pContent->nvrInfo.mems[pContent->tmpInternal.usCnt_mems];

			 switch (tmp_cfgId) {
			 case  CONST_qnmCfgId_null:
				 pContent->tmpInternal.usCnt_mems++;
				 break;
			 case  CONST_qnmCfgId_iChannel:
				 if (getFieldData_long(pItem, (long*)&pMem->iChannel))goto  errLabel;
				 break;
			 case  CONST_qnmCfgId_name:
				 if(getFieldData_wStr(pItem,pMem->name,mycountof(pMem->name)))goto  errLabel;
				 break;
			 case  CONST_qnmCfgId_ip:
				 if (getFieldData_str(pItem, pMem->ip, mycountof(pMem->ip))) {
					 goto  errLabel;
				 }
				   break;
			 }
			   break;
		 default:
			 break;
		 }

	 

	 //
	 iErr = 0;
 errLabel:
	 return  iErr;
 }






//  2017/09/17
  //  2010/12/27
 int  confState2Stream(  unsigned  int  uiStreamId,  CONF_state  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 //
	 if  (  pReq->idInfo_imGrp_related.ui64Id  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_grp_related,  (  void  *  )&pReq->idInfo_imGrp_related.ui64Id,  sizeof(  pReq->idInfo_imGrp_related  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //
	 if  (  pReq->uiTranNo_retrieveAll  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_retrieveAll,  (  void  *  )pReq->uiTranNo_retrieveAll,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->usSeqNo_retrievePart  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usSeqNo_retrievePart,  (  void  *  )pReq->usSeqNo_retrievePart,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  pReq->sendByReceiver.ucbRetrieveAll  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbRetrieveAll,  (  void  *  )pReq->sendByReceiver.ucbRetrieveAll,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  pReq->usSeqNo  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usSeqNo,  (  void  *  )pReq->usSeqNo,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->ucbEnd  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbEnd,  (  void  *  )pReq->ucbEnd,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }


	 //
	 //
	 if  (  pReq->usCnt  )  {
		 //
		 if  (  pReq->usCnt  >  mycountof(  pReq->mems  )  )  goto  errLabel;
		 //
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt,  (  void  *  )pReq->usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;
		 //
		 for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {
			  CONF_mem_state	*  pMem	  =		&pReq->mems[i];
		  				
			  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_mem,  0,  &ptr,  &len  )  )  goto  errLabel;

			  if  (  pMem->idInfo.ui64Id  )  {
				  if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  (  void  *  )&pMem->idInfo.ui64Id,  sizeof(  pMem->idInfo.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
			  }
			  if  (  pMem->usState  )  {
				  if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_status,  (  void  *  )pMem->usState,  0,  &ptr,  &len  )  )  goto  errLabel;  
			  }

			  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
	 }



	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 //
 int  tmpHandler_stream2ConfState(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int							iErr		=	-1;
	 //  p0;
	 CONF_state					*	pContent	=	(  CONF_state  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
			 case  CONST_imCommType_confState:
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_start:
							     pContent->uiType  =  uiStreamId;
								 break;
						   case  CONST_qnmCfgId_idInfo_grp_related:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->idInfo_imGrp_related.ui64Id  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_uiTranNo_retrieveAll:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiTranNo_retrieveAll  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_usSeqNo_retrievePart:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usSeqNo_retrievePart  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_ucbRetrieveAll:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->sendByReceiver.ucbRetrieveAll  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_usSeqNo:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usSeqNo  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_ucbEnd:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->ucbEnd  )  )  goto  errLabel;
							     break;
								 //
						   case  CONST_qnmCfgId_usCnt:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usCnt  )  )  goto  errLabel;
								 //
								 if  (  pContent->usCnt  >  mycountof(  pContent->mems  )  )  goto  errLabel;
				   				 break;
						   default:
								   break;
				   }
				   break;				   
			 case  CONST_imCommType_mem:  {
				   CONF_mem_state  *  pMem		=	NULL;
				   //
				   if  (  pContent->tmpInternal.usCnt_mems  >=  mycountof(  pContent->mems  )  )  {
					   #ifdef  __DEBUG__
							   traceLogA(  (char*)  "tmpHandler_stream2RefreshWebConfState failed: usCnt_mems is too big"  );  
					   #endif
					   goto  errLabel;
				   }
				   //
				   pMem  =  &pContent->mems[pContent->tmpInternal.usCnt_mems];				   
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_messengerId:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pMem->idInfo.ui64Id  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_status:		//  2009/05/31
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pMem->usState  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_null:
							     pContent->tmpInternal.usCnt_mems  ++  ;
							     break;
						   default:
							        //  2009/05/31
									break;
				   }
				   //
				   }
				   break;

			 default:
					 break;			 
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
}



 /////////////////////
 int  tmp_htonConfHgInfo(CONF_hg_info  *  pReq_hgInfo,  char  **  ppBuf,  unsigned  int  *uiBufSize  )
 {
	 int  iErr = -1;

	 char* ptr = *ppBuf;
	 unsigned  int		len = *uiBufSize;

#if 10
	 if (pReq_hgInfo->ui64MeetingId_hg) {
		 if (data2Stream(CONST_qyDataType_l64, CONST_qnmCfgId_meetingId_hg, (void*)&pReq_hgInfo->ui64MeetingId_hg, sizeof(pReq_hgInfo->ui64MeetingId_hg), &ptr, &len))  goto  errLabel;
	 }

	 //
	 if (pReq_hgInfo->iMeetingType_hg) {
		 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_meetingType_hg, (void*)pReq_hgInfo->iMeetingType_hg, 0, &ptr, &len))goto  errLabel;
	 }

	 //
	 if  (  pReq_hgInfo->iMeetingLevel_hg  )  {
		 if  (  data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_meetingLevel_hg, (void*)pReq_hgInfo->iMeetingLevel_hg,0,&ptr,&len))goto  errLabel;
	 }
	 if  (  pReq_hgInfo->iMeetingDurationInMin  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_meetingDuration_hg,(void*)pReq_hgInfo->iMeetingDurationInMin,0,&ptr,&len))goto  errLabel;
	 }

	 //
	 if  (  pReq_hgInfo->ui64_meetingStartTime  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_meetingStartTime_hg,(void*)&pReq_hgInfo->ui64_meetingStartTime, sizeof(pReq_hgInfo->ui64_meetingStartTime),&ptr,&len))goto  errLabel;
	 }
	 if  (  pReq_hgInfo->meetingCompere[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_meetingCompere_hg,(void*)pReq_hgInfo->meetingCompere,lstrlen(pReq_hgInfo->meetingCompere),&ptr,&len))goto  errLabel;
	 }

	 //
	 if (pReq_hgInfo->bRecord_conf) {
		 if (data2Stream(CONST_qyDataType_char, CONST_qnmCfgId_meetingRecord_hg, (void*)pReq_hgInfo->bRecord_conf, 0, &ptr, &len))goto  errLabel;
	 }
	 if (pReq_hgInfo->bShare_2ndStream) {
		 if (data2Stream(CONST_qyDataType_char, CONST_qnmCfgId_meetingShare_2ndStream_hg, (void*)pReq_hgInfo->bShare_2ndStream, 0, &ptr, &len))  goto  errLabel;
	 }
	 int i;
	 for (i = 0; i < mycountof(pReq_hgInfo->shareMems); i++) {
		 if (!pReq_hgInfo->shareMems[i].idInfo.ui64Id) {
			 break;
		 }
		 if (data2Stream(CONST_qyDataType_l64, CONST_qnmCfgId_shareMem_hg, (void*)&pReq_hgInfo->shareMems[i].idInfo.ui64Id, sizeof(pReq_hgInfo->shareMems[i].idInfo.ui64Id), &ptr, &len))goto  errLabel;
	 }
#endif

	 //
	 for (i = 0; i < mycountof(pReq_hgInfo->zcrs.mems); i++) {
		 if (!pReq_hgInfo->zcrs.mems[i].idInfo.ui64Id) {
			 break;
		 }
		 if (data2Stream(CONST_qyDataType_l64, CONST_qnmCfgId_zcr_hg, (void*)&pReq_hgInfo->zcrs.mems[i].idInfo.ui64Id, sizeof(pReq_hgInfo->zcrs.mems[i].idInfo.ui64Id), &ptr, &len))goto  errLabel;
	 }

	 //
	 if (pReq_hgInfo->bFlow512k) {
		 if (data2Stream(CONST_qyDataType_char, CONST_qnmCfgId_bFlow512k_hg, (void*)pReq_hgInfo->bFlow512k, 0, &ptr, &len))  goto  errLabel;
	 }

	 //
	 if (pReq_hgInfo->bLive) {
		 if (data2Stream(CONST_qyDataType_char, CONST_qnmCfgId_bLive, (void*)pReq_hgInfo->bLive, 0, &ptr, &len))goto  errLabel;
	 }
	 if (pReq_hgInfo->liveUrl[0]) {
		 if (data2Stream(CONST_qyDataType_wStr, CONST_qnmCfgId_liveUrl, (void*)pReq_hgInfo->liveUrl, lstrlen(pReq_hgInfo->liveUrl), &ptr, &len))goto  errLabel;
	 }


	 //
	 iErr = 0;
	 errLabel:

	 if (!iErr) {
		 *ppBuf = ptr;
		 *uiBufSize = len;
	 }


	 return  iErr;
 }

 //
 int  tmp_ntohConfHgInfo( QY_CFGITEM_ntoh_U* pItem, CONF_hg_info* pContent, BOOL* pbProcessed)
 {
	 int  iErr = -1;

	 BOOL  bProcessed = FALSE;

	 if (!pContent)  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(&tmp_cfgId, &pItem->head.cfgId, sizeof(short));

	 //
	 bProcessed = true;

	 switch (tmp_cfgId)
	 {

	 case  CONST_qnmCfgId_meetingId_hg:
		 if (getFieldData_l64(pItem, (__int64*)&pContent->ui64MeetingId_hg))  goto  errLabel;
		 //
		 if (1) {
			 TCHAR  tBuf[128];
			 _sntprintf(tBuf, mycountof(tBuf), _T("stream2ConfReq: meetingId_hg %I64u"), pContent->ui64MeetingId_hg);
			 showInfo_open0(0, 0, tBuf);
		 }

		 //
		 break;
		 //
	 case  CONST_qnmCfgId_meetingType_hg:
		 if (getFieldData_long(pItem, (long*)&pContent->iMeetingType_hg))  goto  errLabel;
		 break;
		 //
	 case  CONST_qnmCfgId_meetingLevel_hg:
		 if  (  getFieldData_long(pItem,(long*)&pContent->iMeetingLevel_hg))goto  errLabel;
		 break;
	 case  CONST_qnmCfgId_meetingDuration_hg:
		 if(getFieldData_long(pItem,(long*)&pContent->iMeetingDurationInMin))  goto  errLabel;
		   break;
	 case  CONST_qnmCfgId_meetingStartTime_hg:
		 if  (  getFieldData_l64(pItem,(__int64*)&pContent->ui64_meetingStartTime  )  )  goto  errLabel;
		 break;
	 case  CONST_qnmCfgId_meetingCompere_hg:
		   if  (  getFieldData_wStr(pItem,pContent->meetingCompere,  mycountof(pContent->meetingCompere)))  goto  errLabel;

		   break;
		 //
	 case  CONST_qnmCfgId_meetingRecord_hg: {
		 char  tmp_c = 0;
		 if (getFieldData_char(pItem, (char*)&tmp_c))goto  errLabel;
		 pContent->bRecord_conf = tmp_c;
		 }
		 break;
	 case  CONST_qnmCfgId_meetingShare_2ndStream_hg: {
		 char tmp_c = 0;
		 if (getFieldData_char(pItem, (char*)&tmp_c))  goto  errLabel;
		 pContent->bShare_2ndStream = tmp_c;
		 }
		 break;
	 case  CONST_qnmCfgId_shareMem_hg:
		 if (pContent->tmpInternal.cnt_shareMems >= mycountof(pContent->shareMems))  goto  errLabel;
		 if (getFieldData_l64(pItem, (__int64*)&pContent->shareMems[pContent->tmpInternal.cnt_shareMems].idInfo.ui64Id))goto  errLabel;
		 pContent->tmpInternal.cnt_shareMems++;
		 break;
	 case  CONST_qnmCfgId_zcr_hg:
		 if (pContent->tmpInternal.cnt_zcrs > mycountof(pContent->zcrs.mems))  goto  errLabel;
		 if (getFieldData_l64(pItem, (__int64*)&pContent->zcrs.mems[pContent->tmpInternal.cnt_zcrs].idInfo.ui64Id))goto  errLabel;
		 pContent->tmpInternal.cnt_zcrs++;
		 break;

	 case  CONST_qnmCfgId_bFlow512k_hg: {
		 char tmp_c = 0;
		 if (getFieldData_char(pItem, (char*)&tmp_c))goto  errLabel;
		 pContent->bFlow512k = tmp_c;
		 }
		 break;

		 //
	 case  CONST_qnmCfgId_bLive: {
		 byte  tmp_b;
		 if (getFieldData_char(pItem, (char*)&tmp_b))goto  errLabel;
		 pContent->bLive = tmp_b;

	 }
							   break;
	 case  CONST_qnmCfgId_liveUrl:
		 if (getFieldData_wStr(pItem, pContent->liveUrl, mycountof(pContent->liveUrl)))  goto  errLabel;
		 break;


		 //
	 default:
		 break;
	 }

	 iErr = 0;
 errLabel:


	 return  iErr;
 }


 ///////////////////////////
  //  2010/12/27
 int  confReq2Stream(  unsigned  int  uiStreamId,  CONF_req  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 //
	 if (pReq->ucbResp) {
		 if (data2Stream(CONST_qyDataType_char, CONST_qnmCfgId_ucbResp, (void*)pReq->ucbResp, 0, &ptr, &len))goto  errLabel;
	 }

	 //
	 if  (  pReq->idInfo_imGrp_related.ui64Id  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_grp_related,  (  void  *  )&pReq->idInfo_imGrp_related.ui64Id,  sizeof(  pReq->idInfo_imGrp_related  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 
	 //
	 if  (  pReq->usOp  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usOp,  (  void  *  )pReq->usOp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //
	 if  (  pReq->policy.usAvLevel  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usAvLevel,  (  void *  )pReq->policy.usAvLevel,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //
	 if (pReq->policy.usMaxSpeakers) {
		 if (data2Stream(CONST_qyDataType_short, CONST_qnmCfgId_usMaxSpeakers, (void*)pReq->policy.usMaxSpeakers, 0, &ptr, &len))  goto  errLabel;
	 }

	 //
	 if (pReq->policy.talkerPolicy.conf_ucAudioCompressors) {
		 if (data2Stream(CONST_qyDataType_byte, CONST_qnmCfgId_ucAudioCompressors, (void*)pReq->policy.talkerPolicy.conf_ucAudioCompressors, 0, &ptr, &len))goto  errLabel;
	 }

	 //
	 if  (  pReq->policy.talkerPolicy.conf_iFourcc  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_conf_iFourcc,  (  void  *  )pReq->policy.talkerPolicy.conf_iFourcc,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if (pReq->policy.talkerPolicy.conf_bitrateInKbps_dl) {
		 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_conf_bitrateInKbps_dl, (void*)pReq->policy.talkerPolicy.conf_bitrateInKbps_dl, 0, &ptr, &len))  goto  errLabel;
	 }
	 if (pReq->policy.talkerPolicy.conf_bitrateInKbps_ul) {
		 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_conf_bitrateInKbps_ul, (void*)pReq->policy.talkerPolicy.conf_bitrateInKbps_ul, 0, &ptr, &len))  goto  errLabel;
	 }

	 //
	 if (pReq->policy.talkerPolicy.conf_usFps) {
		 if (data2Stream(CONST_qyDataType_short, CONST_qnmCfgId_conf_usFps, (void*)pReq->policy.talkerPolicy.conf_usFps, 0, &ptr, &len))  goto  errLabel;
	 }
	 if (pReq->policy.talkerPolicy.conf_ucb100k) {
		 if (data2Stream(CONST_qyDataType_byte, CONST_qnmCfgId_conf_ucb100k, (void*)pReq->policy.talkerPolicy.conf_ucb100k, 0, &ptr, &len))goto errLabel;
	 }

	 //
	 if (pReq->policy.talkerPolicy.uiTaskType) {
		 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_uiTaskType, (void*)pReq->policy.talkerPolicy.uiTaskType, 0, &ptr, &len))goto  errLabel;
	 }
	 if (pReq->policy.talkerPolicy.shareDevice_grp_index) {
		 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_shareDevice_grp_index, (void*)pReq->policy.talkerPolicy.shareDevice_grp_index, 0, &ptr, &len))goto  errLabel;
	 }
	 //
	 if (pReq->policy.talkerPolicy.gpu_usIndex) {
		 if (data2Stream(CONST_qyDataType_short, CONST_qnmCfgId_gpu_usIndex, (void*)pReq->policy.talkerPolicy.gpu_usIndex, 0, &ptr, &len))  goto  errLabel;
	 }

#if 0
	 if (pReq->policy.talkerPolicy.ucb2Streams) {
		 if (data2Stream(CONST_qyDataType_char, CONST_qnmCfgId_ucb2Streams, (void*)pReq->policy.talkerPolicy.ucb2Streams, 0, &ptr, &len  )  )  goto  errLabel;
	 }
#endif

	 //
	 if (pReq->policy.talkerPolicy.usConfType) {
		 if (data2Stream(CONST_qyDataType_short, CONST_qnmCfgId_usConfType, (void*)pReq->policy.talkerPolicy.usConfType, 0, &ptr, &len))  goto  errLabel;
	 }

	 //
#ifdef  __DEBUG__
	 //_sntprintf(tBuf,mycountof(tBuf),  _T(  '
#endif

	 //
	 if  (  pReq->idInfo_initiator.ui64Id  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_initiator,  (  void  *  )&pReq->idInfo_initiator.ui64Id,  sizeof(  pReq->idInfo_initiator  ),  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  pReq->ucHardwareAccl  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucHardwareAccl,  (  void  *  )pReq->ucHardwareAccl,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 //
	 tmp_htonConfHgInfo(&pReq->hgInfo, &ptr, &len);
	 
	 //
	 if (pReq->idInfo_requester.ui64Id) {
		 if (data2Stream(CONST_qyDataType_l64, CONST_qnmCfgId_idInfo_requester, (void*)&pReq->idInfo_requester.ui64Id, sizeof(pReq->idInfo_requester), &ptr, &len))  goto  errLabel;
	 }


	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2ConfReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int							iErr		=	-1;
	 //  p0;
	 CONF_req	*	pContent	=	(  CONF_req  *  )p1;
	 //  QY_CFGITEM					*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
			 case  CONST_imCommType_confReq:
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_start:
							     pContent->uiType  =  uiStreamId;
								 break;
						   case  CONST_qnmCfgId_ucbResp:
							   if (getFieldData_char(pItem, (char*)&pContent->ucbResp))  goto  errLabel;
							   break;
						   case  CONST_qnmCfgId_idInfo_grp_related:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->idInfo_imGrp_related.ui64Id  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_usOp:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usOp  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_usAvLevel:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->policy.usAvLevel  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_usMaxSpeakers:
							     if (getFieldData_short(pItem, (short*)&pContent->policy.usMaxSpeakers))  goto  errLabel;
							     break;
								 //
						   case  CONST_qnmCfgId_ucAudioCompressors:
							     if (getFieldData_char(pItem, (char*)&pContent->policy.talkerPolicy.conf_ucAudioCompressors)) goto  errLabel;
							     break;
								 //
						   case  CONST_qnmCfgId_conf_iFourcc:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->policy.talkerPolicy.conf_iFourcc  )  )  goto  errLabel;
							     break;
								 //
						   case  CONST_qnmCfgId_conf_bitrateInKbps_dl:
							     if (getFieldData_long(pItem, (long*)&pContent->policy.talkerPolicy.conf_bitrateInKbps_dl))goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_conf_bitrateInKbps_ul:
							   if (getFieldData_long(pItem, (long*)&pContent->policy.talkerPolicy.conf_bitrateInKbps_ul))goto  errLabel;
							   break;
							   //
						   case  CONST_qnmCfgId_conf_usFps:
							   if (getFieldData_short(pItem, (short*) & pContent->policy.talkerPolicy.conf_usFps))goto  errLabel;
							   break;
						   case  CONST_qnmCfgId_conf_ucb100k:
							   if (getFieldData_char(pItem, (char*) & pContent->policy.talkerPolicy.conf_ucb100k))goto  errLabel;
							   break;

							   //
#if 0
						   case  CONST_qnmCfgId_ucb2Streams:
							     if  (  getFieldData_char(  pItem,  (char*)&pContent->policy.talkerPolicy.ucb2Streams  )  )  goto  errLabel;
							     break;
#endif
								 //
						   case  CONST_qnmCfgId_uiTaskType:
							     if (getFieldData_long(pItem, (long*)&pContent->policy.talkerPolicy.uiTaskType))goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_shareDevice_grp_index:
							     if (getFieldData_long(pItem, (long*)&pContent->policy.talkerPolicy.shareDevice_grp_index))goto  errLabel;
							     break;
								 //
						   case  CONST_qnmCfgId_gpu_usIndex:
							   if (getFieldData_short(pItem, (short*)&pContent->policy.talkerPolicy.gpu_usIndex))  goto  errLabel;
							   break;
						   case  CONST_qnmCfgId_usConfType:
							   if (getFieldData_short(pItem, (short*)&pContent->policy.talkerPolicy.usConfType))goto  errLabel;
							   break;
							   //
								 //
						   case  CONST_qnmCfgId_idInfo_initiator:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->idInfo_initiator.ui64Id  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_ucHardwareAccl:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->ucHardwareAccl  )  )  goto  errLabel;
							     break;
								 //
						   case  CONST_qnmCfgId_idInfo_requester:
							     if (getFieldData_l64(pItem, (__int64*)&pContent->idInfo_requester.ui64Id))  goto  errLabel;
							     break;
								 //
								 //
						   default:
						   {
							   BOOL  bProcessed = false;
							   tmp_ntohConfHgInfo( pItem, &pContent->hgInfo, &bProcessed);
						   }
								   break;
				   }
				   break;				   
			 default:
					 break;			 
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
}


 //
 //  2010/12/27
 int  confCtrlState2Stream(unsigned  int  uiStreamId, CONF_ctrl_state* pReq, char* buf, unsigned  int* uiBufSize)
 {
	 int				iErr = -1;
	 int				i = 0;
	 char* ptr = buf;
	 unsigned  int		len = *uiBufSize;

	 if (!pReq)  return  -1;
	 if (!buf)  return  -1;

	 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_start, (void*)uiStreamId, 0, &ptr, &len))  goto  errLabel;

	 if (pReq->idInfo_imGrp_related.ui64Id) {
		 if (data2Stream(CONST_qyDataType_l64, CONST_qnmCfgId_idInfo_grp_related, (void*)&pReq->idInfo_imGrp_related.ui64Id, sizeof(pReq->idInfo_imGrp_related), &ptr, &len))  goto  errLabel;
	 }

	 if (pReq->idInfo_compere.ui64Id) {
		 if (data2Stream(CONST_qyDataType_l64, CONST_qnmCfgId_idInfo_compere, (void*)&pReq->idInfo_compere.ui64Id, sizeof(pReq->idInfo_compere.ui64Id), &ptr, &len))  goto  errLabel;
	 }

	 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_null, 0, 0, &ptr, &len))  goto  errLabel;

	 iErr = 0;
 errLabel:
	 if (!iErr) {
		 *uiBufSize = *uiBufSize - len;
	 }
	 return  iErr;

 }


 //
 int  tmpHandler_stream2confCtrlState(CTX_stream2Data* pCtx, void* p0, void* p1, unsigned  int  uiStreamId, QY_CFGITEM_ntoh_U* pItem)
 {
	 int							iErr = -1;
	 //  p0;
	 CONF_ctrl_state* pContent = (CONF_ctrl_state*)p1;
	 //  QY_CFGITEM					*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;

	 if (!pContent)  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(&tmp_cfgId, &pItem->head.cfgId, sizeof(short));

	 switch (uiStreamId) {
	 case  CONST_imCommType_confCtrlState:
		 switch (tmp_cfgId) {
		 case  CONST_qnmCfgId_start:
			 pContent->uiType = uiStreamId;
			 break;
		 case  CONST_qnmCfgId_idInfo_grp_related:
			 if (getFieldData_l64(pItem, (__int64*)&pContent->idInfo_imGrp_related.ui64Id))  goto  errLabel;
			 break;
		 case  CONST_qnmCfgId_idInfo_compere:
			 if (getFieldData_l64(pItem, (__int64*)&pContent->idInfo_compere.ui64Id))  goto  errLabel;
			 //
			 break;
		 default:
			 break;
		 }
		 break;
	 default:
		 break;
	 }

	 iErr = 0;
 errLabel:
	 return  iErr;
 }






///////////////////////

 int  refreshWebContactsInfo2Stream(  unsigned  int  uiStreamId,  REFRESH_WEBCONTACTS_INFO  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pReq->ucbResp  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbResp,  (  void  *  )pReq->ucbResp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->ucbNeedDetail  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbNeedDetail,  (  void  *  )pReq->ucbNeedDetail,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pReq->usCnt  )  {
		 //
		 if  (  pReq->usCnt  >  mycountof(  pReq->mems  )  )  goto  errLabel;
		 //
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt,  (  void  *  )pReq->usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;
		 //
		 for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {
			  WEB_CONTACT_STATUS	*  pMem	  =		&pReq->mems[i];
		  				
			  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_mem,  0,  &ptr,  &len  )  )  goto  errLabel;

			  if  (  pMem->idInfo.ui64Id  )  {
				  if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  (  void  *  )&pMem->idInfo.ui64Id,  sizeof(  pMem->idInfo.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
			  }
			  if  (  pMem->uiLogonId  )  {
				  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiLogonId,  (  void  *  )pMem->uiLogonId,  0,  &ptr,  &len  )  )  goto  errLabel;
			  }
			  if  (  pMem->tLastCommTime  )  {
				  if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tLastCommTime,  (  void  *  )&pMem->tLastCommTime,  sizeof(  pMem->tLastCommTime  ),  &ptr,  &len  )  )  goto  errLabel;
			  }
			  if  (  pMem->usRunningStatus  )  {
				  if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usRunningStatus,  (  void  *  )pMem->usRunningStatus,  0,  &ptr,  &len  )  )  goto  errLabel;
			  }
			  if  (  pMem->wLocation[0]  )  {
				  if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_wLocation,  pMem->wLocation,  lstrlen(  pMem->wLocation  ),  &ptr,  &len  )  )  goto  errLabel;
			  }

			  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
	 }


	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2RefreshWebContactsInfo(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int							iErr		=	-1;
	 //  p0;
	 REFRESH_WEBCONTACTS_INFO	*	pContent	=	(  REFRESH_WEBCONTACTS_INFO  *  )p1;
	 //  QY_CFGITEM					*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
			 case  CONST_imCommType_refreshWebContactsInfo:
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_start:
							     pContent->uiType  =  uiStreamId;
								 break;
						   case  CONST_qnmCfgId_ucbResp:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->ucbResp  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_ucbNeedDetail:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->ucbNeedDetail  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_usCnt:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usCnt  )  )  goto  errLabel;
								 //
								 if  (  pContent->usCnt  >  mycountof(  pContent->mems  )  )  goto  errLabel;
				   				 break;
						   default:
								   break;
				   }
				   break;				   
			 case  CONST_imCommType_mem:  {
				   WEB_CONTACT_STATUS  *  pMem		=	NULL;
				   //
				   if  (  pContent->usCnt_mems  >=  mycountof(  pContent->mems  )  )  {
					   #ifdef  __DEBUG__
							   traceLogA(  (char*)  "tmpHandler_stream2RefreshWebContactsInfo failed: usCnt_mems is too big"  );  
					   #endif
					   goto  errLabel;
				   }
				   //
				   pMem  =  &pContent->mems[pContent->usCnt_mems];				   
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_messengerId:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pMem->idInfo.ui64Id  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_uiLogonId:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->uiLogonId  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_tLastCommTime:
							     if  (  getFieldData_l64(  pItem,  &pMem->tLastCommTime  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_usRunningStatus:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pMem->usRunningStatus  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_wLocation:
							     if  (  getFieldData_wStr(  pItem,  pMem->wLocation,  mycountof(  pMem->wLocation  )  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_null:
							     pContent->usCnt_mems  ++  ;
							     break;
						   default:
									break;
				   }
				   //
				   }
				   break;
			 
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}


////////////////

 int  qyVDevComs2Stream(  unsigned  int  uiStreamId,  QY_VDEV_COMS  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 if  (  pReq->ucbResp  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbResp,  (  void  *  )pReq->ucbResp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->uiVDevId  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiVDevId,  (  void  *  )pReq->uiVDevId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pReq->usCnt  )  {
		 //
		 if  (  pReq->usCnt  >  mycountof(  pReq->mems  )  )  goto  errLabel;
		 //
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt,  (  void  *  )pReq->usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;
		 //
		 for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {
			  QY_VDEV_COM		*  pMem	  =		&pReq->mems[i];
		  				
			  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_mem,  0,  &ptr,  &len  )  )  goto  errLabel;

			  if  (  pMem->idInfo.ui64Id  )  {
				  if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  (  void  *  )&pMem->idInfo.ui64Id,  sizeof(  pMem->idInfo.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
			  }
#if  0
			  if  (  pMem->wDevIdStr[0]  )  {
				  if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_wDevIdStr_from,  (  void  *  )pMem->wDevIdStr,  lstrlen(  pMem->wDevIdStr  ),  &ptr,  &len  )  )  goto  errLabel;
			  }
#endif 
			  if  (  pMem->name[0]  )  {
				  if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_displayName,  pMem->name,  lstrlen(  pMem->name  ),  &ptr,  &len  )  )  goto  errLabel;
			  }
			  if  (  pMem->model[0]  )  {
				  if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_model,  pMem->model,  lstrlen(  pMem->model  ),  &ptr,  &len  )  )  goto  errLabel;
			  }
			  if  (  pMem->smsc  )  {
				  if  (  data2Stream(  CONST_qyDataType_str,  CONST_qnmCfgId_smsc,  pMem->smsc,  strlen(  pMem->smsc  ),  &ptr,  &len  )  )  goto  errLabel;
			  }
			  if  (  pMem->iStatus  )  {
				  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_status,  (  void  *  )pMem->iStatus,  0,  &ptr,  &len  )  )  goto  errLabel;
			  }

			  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
	 }


	 
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2QyVDevComs(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 QY_VDEV_COMS			*	pContent	=	(  QY_VDEV_COMS  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 	 
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
			 case  CONST_imCommType_vDevComs:
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_start:
							     pContent->uiType  =  uiStreamId;
								 break;
						   case  CONST_qnmCfgId_ucbResp:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->ucbResp  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_uiVDevId:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiVDevId  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_usCnt:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usCnt  )  )  goto  errLabel;
								 //
								 if  (  pContent->usCnt  >  mycountof(  pContent->mems  )  )  goto  errLabel;
				   				 break;
						   default:
								   break;
				   }
				   break;				   
			 case  CONST_imCommType_mem:  {
				   QY_VDEV_COM  *  pMem		=	NULL;
				   //
				   if  (  pContent->usCnt_mems  >=  mycountof(  pContent->mems  )  )  {
					   #ifdef  __DEBUG__
							   traceLogA(  (char*)  "tmpHandler_stream2RefreshWebContactsInfo failed: usCnt_mems is too big"  );  
					   #endif
					   goto  errLabel;
				   }
				   //
				   pMem  =  &pContent->mems[pContent->usCnt_mems];				   
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_messengerId:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pMem->idInfo.ui64Id  )  )  goto  errLabel;
							     break;
#if  0
						   case  CONST_qnmCfgId_wDevIdStr_from:
							     if  (  getFieldData_wStr(  pItem,  pMem->wDevIdStr,  mycountof(  pMem->wDevIdStr  )  )  )  goto  errLabel;
								 break;
#endif 
						   case  CONST_qnmCfgId_displayName:
							     if  (  getFieldData_wStr(  pItem,  pMem->name,  mycountof(  pMem->name  )  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_model:
							     if  (  getFieldData_wStr(  pItem,  pMem->model,  mycountof(  pMem->model  )  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_smsc:
							     if  (  getFieldData_str(  pItem,  pMem->smsc,  mycountof(  pMem->smsc  )  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_status:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->iStatus  )  )  goto  errLabel;
								 break;								 
						   case  CONST_qnmCfgId_null:
							     pContent->usCnt_mems  ++  ;
							     break;
						   default:
									break;
				   }
				   //
				   }
				   break;
			 
	 }


	 iErr  =  0;
errLabel:
	 return  iErr;
}


/////


//  

 int  retrieveSmPolicy2Stream(  unsigned  int  uiStreamId,  RETRIEVE_SM_POLICY  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 if  (  pReq->ucbResp  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbResp,  (  void  *  )pReq->ucbResp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->uiVDevId  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiVDevId,  (  void  *  )pReq->uiVDevId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //
	 if  (  pReq->ucbDefaultSmServer  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbDefaultSmServer,  (  void  *  )pReq->ucbDefaultSmServer,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  pReq->usCnt  )  {
		 //
		 if  (  pReq->usCnt  >  mycountof(  pReq->mems  )  )  goto  errLabel;
		 //
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt,  (  void  *  )pReq->usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;
		 //
		 for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {
			  QY_SM_CONTACT		*  pMem	  =		&pReq->mems[i];
		  				
			  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_mem,  0,  &ptr,  &len  )  )  goto  errLabel;

			  if  (  pMem->idInfo_contact.ui64Id  )  {
				  if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  (  void  *  )&pMem->idInfo_contact.ui64Id,  sizeof(  pMem->idInfo_contact.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
			  }
#if  0
			  if  (  pMem->wDevIdStr[0]  )  {
				  if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_wDevIdStr_from,  pMem->wDevIdStr,  lstrlen(  pMem->wDevIdStr  ),  &ptr,  &len  )  )  goto  errLabel;
			  }
#endif 
			  if  (  pMem->cusName[0]  )  {
				  if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_cusName,  pMem->cusName,  lstrlen(  pMem->cusName  ),  &ptr,  &len  )  )  goto  errLabel;
			  }

			  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
	 }


	 
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2RetrieveSmPolicy(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 RETRIEVE_SM_POLICY		*	pContent	=	(  RETRIEVE_SM_POLICY  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 	 
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
			 case  CONST_imCommType_retrieveSmPolicy:
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_start:
							     pContent->uiType  =  uiStreamId;
								 break;
						   case  CONST_qnmCfgId_ucbResp:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->ucbResp  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_uiVDevId:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiVDevId  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_ucbDefaultSmServer:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->ucbDefaultSmServer  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_usCnt:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usCnt  )  )  goto  errLabel;
								 //
								 if  (  pContent->usCnt  >  mycountof(  pContent->mems  )  )  goto  errLabel;
				   				 break;
						   default:
								   break;
				   }
				   break;				   
			 case  CONST_imCommType_mem:  {
				   QY_SM_CONTACT  *  pMem		=	NULL;
				   //
				   if  (  pContent->usCnt_mems  >=  mycountof(  pContent->mems  )  )  {
					   traceLogA(  (char*)  "tmpHandler_stream2RetrieveSmPolicy failed: usCnt_mems is too big"  );  goto  errLabel;
				   }
				   //
				   pMem  =  &pContent->mems[pContent->usCnt_mems];				   
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_messengerId:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pMem->idInfo_contact.ui64Id  )  )  goto  errLabel;
							     break;
#if  0
						   case  CONST_qnmCfgId_wDevIdStr_from:
							     if  (  getFieldData_wStr(  pItem,  pMem->wDevIdStr,  mycountof(  pMem->wDevIdStr  )  )  )  goto  errLabel;
								 break;
#endif 
						   case  CONST_qnmCfgId_cusName:
							     if  (  getFieldData_wStr(  pItem,  pMem->cusName,  mycountof(  pMem->cusName  )  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_null:
							     pContent->usCnt_mems  ++  ;
							     break;
						   default:
									break;
				   }
				   //
				   }
				   break;
			 
	 }


	 iErr  =  0;
errLabel:
	 return  iErr;
}


//////////////////




 int  retrievePhoneMsgrs2Stream(  unsigned  int  uiStreamId,  RETRIEVE_PHONE_MSGRS  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pReq->usMaxPhoneMsgrsPerSnd  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usMaxMemsPerSnd,  (  void  *  )pReq->usMaxPhoneMsgrsPerSnd,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->wDevIdStr_lastRefreshed[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_wDevIdStr_lastRefreshed,  (  void  *  )pReq->wDevIdStr_lastRefreshed,  lstrlen(  pReq->wDevIdStr_lastRefreshed  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->ucbResp  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbResp,  (  void  *  )pReq->ucbResp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->ucbEnd  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbEnd,  (  void  *  )pReq->ucbEnd,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pReq->usCnt  )  {
		 //
		 if  (  pReq->usCnt  >  mycountof(  pReq->mems  )  )  goto  errLabel;
		 //
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt,  (  void  *  )pReq->usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;
		 //
		 for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {
			  RETRIEVE_PHONE_MSGR		*  pMem	  =		&pReq->mems[i];
		  				
			  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_mem,  0,  &ptr,  &len  )  )  goto  errLabel;

#if  0
			  if  (  pMem->wDevIdStr[0]  )  {
				  if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_wDevIdStr_from,  pMem->wDevIdStr,  lstrlen(  pMem->wDevIdStr  ),  &ptr,  &len  )  )  goto  errLabel;
			  }
#endif 
			  if  (  pMem->idInfo.ui64Id  )  {
				  if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  &pMem->idInfo.ui64Id,  sizeof(  pMem->idInfo.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
			  }
			  if  (  pMem->displayName[0]  )  {
				  if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_displayName,  pMem->displayName,  lstrlen(  pMem->displayName  ),  &ptr,  &len  )  )  goto  errLabel;
			  }

			  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
	 }


	 
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2RetrievePhoneMsgrs(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 RETRIEVE_PHONE_MSGRS	*	pContent	=	(  RETRIEVE_PHONE_MSGRS  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 	 
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
			 case  CONST_imCommType_retrievePhoneMsgrs:
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_start:
							     pContent->uiType  =  uiStreamId;
								 break;
						   case  CONST_qnmCfgId_usMaxMemsPerSnd:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usMaxPhoneMsgrsPerSnd  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_wDevIdStr_lastRefreshed:
							     if  (  getFieldData_wStr(  pItem,  pContent->wDevIdStr_lastRefreshed,  mycountof(  pContent->wDevIdStr_lastRefreshed  )  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_ucbResp:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->ucbResp  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_ucbEnd:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->ucbEnd  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_usCnt:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usCnt  )  )  goto  errLabel;
								 //
								 if  (  pContent->usCnt  >  mycountof(  pContent->mems  )  )  goto  errLabel;
				   				 break;
						   default:
								   break;
				   }
				   break;				   
			 case  CONST_imCommType_mem:  {
				   RETRIEVE_PHONE_MSGR  *  pMem		=	NULL;
				   //
				   if  (  pContent->usCnt_mems  >=  mycountof(  pContent->mems  )  )  {
					   traceLogA(  (char*)  "tmpHandler_stream2RetrieveSmPolicy failed: usCnt_mems is too big"  );  goto  errLabel;
				   }
				   //
				   pMem  =  &pContent->mems[pContent->usCnt_mems];				   
				   switch  (  tmp_cfgId  )  {
#if  0
						   case  CONST_qnmCfgId_wDevIdStr_from:
							     if  (  getFieldData_wStr(  pItem,  pMem->wDevIdStr,  mycountof(  pMem->wDevIdStr  )  )  )  goto  errLabel;
								 break;
#endif 
						   case  CONST_qnmCfgId_messengerId:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pMem->idInfo.ui64Id  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_displayName:
							     if  (  getFieldData_wStr(  pItem,  pMem->displayName,  mycountof(  pMem->displayName  )  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_null:
							     pContent->usCnt_mems  ++  ;
							     break;
						   default:
									break;
				   }
				   //
				   }
				   break;
			 
	 }


	 iErr  =  0;
errLabel:
	 return  iErr;
}


///////////////



 int  retrieveToPaths2Stream(  unsigned  int  uiStreamId,  RETRIEVE_TO_PATHS  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pReq->usMaxMemsPerSnd  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usMaxMemsPerSnd,  (  void  *  )pReq->usMaxMemsPerSnd,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->ucbResp  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbResp,  (  void  *  )pReq->ucbResp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pReq->usCnt  )  {
		 //
		 if  (  pReq->usCnt  >  mycountof(  pReq->mems  )  )  goto  errLabel;
		 //
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt,  (  void  *  )pReq->usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;
		 //
		 for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {
			  RETRIEVE_TO_PATH		*  pMem	  =		&pReq->mems[i];
		  				
			  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_mem,  0,  &ptr,  &len  )  )  goto  errLabel;

			  if  (  pMem->ucbDefaultSmServer  )  {
				  if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbDefaultSmServer,  (  void  *  )pMem->ucbDefaultSmServer,  0,  &ptr,  &len  )  )  goto  errLabel;
			  }
			  if  (  pMem->idInfo_vDev.ui64Id  )  {
				  if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  &pMem->idInfo_vDev.ui64Id,  sizeof(  pMem->idInfo_vDev.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
			  }
			  if  (  pMem->wDevIdStr[0]  )  {
				  //if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_wDevIdStr_from,  pMem->wDevIdStr,  lstrlen(  pMem->wDevIdStr  ),  &ptr,  &len  )  )  goto  errLabel;
			  }
			  if  (  pMem->cusName[0]  )  {
				  if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_cusName,  pMem->cusName,  lstrlen(  pMem->cusName  ),  &ptr,  &len  )  )  goto  errLabel;
			  }

			  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
	 }


	 
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2RetrieveToPaths(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 RETRIEVE_TO_PATHS		*	pContent	=	(  RETRIEVE_TO_PATHS  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 	 
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
			 case  CONST_imCommType_retrieveToPaths:
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_start:
							     pContent->uiType  =  uiStreamId;
								 break;
						   case  CONST_qnmCfgId_usMaxMemsPerSnd:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usMaxMemsPerSnd  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_ucbResp:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->ucbResp  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_usCnt:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usCnt  )  )  goto  errLabel;
								 //
								 if  (  pContent->usCnt  >  mycountof(  pContent->mems  )  )  goto  errLabel;
				   				 break;
						   default:
								   break;
				   }
				   break;				   
			 case  CONST_imCommType_mem:  {
				   RETRIEVE_TO_PATH  *  pMem		=	NULL;
				   //
				   if  (  pContent->usCnt_mems  >=  mycountof(  pContent->mems  )  )  {
					   traceLogA(  (char*)  "tmpHandler_stream2RetrieveToPaths failed: usCnt_mems is too big"  );  goto  errLabel;
				   }
				   //
				   pMem  =  &pContent->mems[pContent->usCnt_mems];				   
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_ucbDefaultSmServer:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pMem->ucbDefaultSmServer  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_messengerId:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pMem->idInfo_vDev.ui64Id  )  )  goto  errLabel;
							     break;
#if  0
						   case  CONST_qnmCfgId_wDevIdStr_from:
							     if  (  getFieldData_wStr(  pItem,  pMem->wDevIdStr,  mycountof(  pMem->wDevIdStr  )  )  )  goto  errLabel;
								 break;
#endif 
						   case  CONST_qnmCfgId_cusName:
							     if  (  getFieldData_wStr(  pItem,  pMem->cusName,  mycountof(  pMem->cusName  )  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_null:
							     pContent->usCnt_mems  ++  ;
							     break;
						   default:
									break;
				   }
				   //
				   }
				   break;
			 
	 }


	 iErr  =  0;
errLabel:
	 return  iErr;
}


//////////////////

/*
typedef  struct  __refreshDynBmp_t									{
				 unsigned  short									usSubtype;
				 unsigned  short									usIndex;
				 TCHAR												name[32];
				 TCHAR												cusName[32];
}		 REFRESH_DYN_BMP;

typedef  struct  __refreshDynBmps_t									{
				 unsigned  int										uiType;
				 //
				 unsigned  char										ucbResp;
				 //
				 __int64											tLastModifiedTime;
				 //
				 unsigned  short									usCnt;
				 REFRESH_DYN_BMP									mems[3];

}		 REFRESH_DYN_BMPS;
*/

 int  refreshDynBmps2Stream(  unsigned  int  uiStreamId,  REFRESH_DYN_BMPS  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pReq->ucbResp  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbResp,  (  void  *  )pReq->ucbResp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //  if  (  pReq->uiObjType  )  {
	 // 	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiObjType,  (  void  *  )pReq->uiObjType,  0,  &ptr,  &len  )  )  goto  errLabel;
	 //  }
	 if  (  pReq->tLastModifiedTime  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tLastModifiedTime,  (  void  *  )&pReq->tLastModifiedTime,  sizeof(  pReq->tLastModifiedTime  ),  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pReq->usCnt  )  {
		 //
		 if  (  pReq->usCnt  >  mycountof(  pReq->mems  )  )  goto  errLabel;
		 //
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt,  (  void  *  )pReq->usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;
		 //
		 for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {
			  QIS_dynBmp_info		*  pMem	  =		&pReq->mems[i];
		  				
			  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_mem,  0,  &ptr,  &len  )  )  goto  errLabel;

			  if  (  pMem->qisResObj.resObj.uiObjType  )  {				  	 
				  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiObjType,  (  void  *  )pMem->qisResObj.resObj.uiObjType,  0,  &ptr,  &len  )  )  goto  errLabel;
			  }

			  if  (  pMem->qisResObj.resObj.usIndex_obj  )  {
				  if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_index,  (  void  *  )pMem->qisResObj.resObj.usIndex_obj,  0,  &ptr,  &len  )  )  goto  errLabel;
			  }

			  if  (  pMem->name[0]  )  {
				  if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_name,  pMem->name,  lstrlen(  pMem->name  ),  &ptr,  &len  )  )  goto  errLabel;
			  }
			  if  (  pMem->cusName[0]  )  {
				  if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_cusName,  pMem->cusName,  lstrlen(  pMem->cusName  ),  &ptr,  &len  )  )  goto  errLabel;
			  }

			  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
	 }
	 	 
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2RefreshDynBmps(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 REFRESH_DYN_BMPS		*	pContent	=	(  REFRESH_DYN_BMPS  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 	 
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
			 case  CONST_imCommType_refreshDynBmps:
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_start:
							     pContent->uiType  =  uiStreamId;
								 break;
						   case  CONST_qnmCfgId_ucbResp:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->ucbResp  )  )  goto  errLabel;
							     break;
						   //  case  CONST_qnmCfgId_uiObjType:
						   //     if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiObjType  )  )  goto  errLabel;
						   //		 break;
						   case  CONST_qnmCfgId_tLastModifiedTime:
							     if  (  getFieldData_l64(  pItem,  &pContent->tLastModifiedTime  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_usCnt:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usCnt  )  )  goto  errLabel;
								 //
								 if  (  pContent->usCnt  >  mycountof(  pContent->mems  )  )  goto  errLabel;
				   				 break;
						   default:
								   break;
				   }
				   break;				   
			 case  CONST_imCommType_mem:  {
				   QIS_dynBmp_info  *  pMem		=	NULL;
				   //
				   if  (  pContent->usCnt_mems  >=  mycountof(  pContent->mems  )  )  {
					   traceLogA(  (char*)  "tmpHandler_stream2RefreshDynBmps failed: usCnt_mems is too big"  );  goto  errLabel;
				   }
				   //
				   pMem  =  &pContent->mems[pContent->usCnt_mems];				   
				   switch  (  tmp_cfgId  )  {					   						   
						   case  CONST_qnmCfgId_uiObjType:
							   if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->qisResObj.resObj.uiObjType  )  )  goto  errLabel;
						   		 break;
						   case  CONST_qnmCfgId_index:
							   if  (  getFieldData_short(  pItem,  (  short  *  )&pMem->qisResObj.resObj.usIndex_obj  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_name:
							     if  (  getFieldData_wStr(  pItem,  pMem->name,  mycountof(  pMem->name  )  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_cusName:
							     if  (  getFieldData_wStr(  pItem,  pMem->cusName,  mycountof(  pMem->cusName  )  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_null:
							     pContent->usCnt_mems  ++  ;
							     break;
						   default:
									break;
				   }
				   //
				   }
				   break;
			 
	 }


	 iErr  =  0;
errLabel:
	 return  iErr;
}


 //  2011/10/31
  int  verifyViewDynBmp2Stream(  unsigned  int  uiStreamId,  VERIFY_viewDynBmp  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pReq->ucbResp  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbResp,  (  void  *  )pReq->ucbResp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->idInfo_viewer.ui64Id  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  &pReq->idInfo_viewer.ui64Id,  sizeof(  pReq->idInfo_viewer.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pReq->uiCmd  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_nCmd,  (  void  *  )pReq->uiCmd,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 	 
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2VerifyViewDynBmp(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 VERIFY_viewDynBmp		*	pContent	=	(  VERIFY_viewDynBmp  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 	 
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
			 case  CONST_imCommType_verifyViewDynBmp:
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_start:
							     pContent->uiType  =  uiStreamId;
								 break;
						   case  CONST_qnmCfgId_ucbResp:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->ucbResp  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_messengerId:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->idInfo_viewer.ui64Id  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_nCmd:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiCmd  )  )  goto  errLabel;
							     break;
						   default:
								   break;
				   }
				   break;				   
			 
	 }


	 iErr  =  0;
errLabel:
	 return  iErr;
}



/////////////////////////
/*
typedef  struct  __retrieveDynBmps_t								{
				 unsigned  int										uiType;
				 //
				 unsigned  char										ucbResp;
				 //
				 __int64											tLastRefreshedTime_misServ;	//  2009/09/03
				 union												{
					 struct											{
						 unsigned  char								ucbNext;
						 QY_MESSENGER_ID							idInfo;
						 unsigned  int								uiObjType;
						 unsigned  short							usIndex;
					 }												retrieveReq;
					 struct											{
						 unsigned  char								ucbEnd;
					 }												retrieveResp;
				 }													u;

				 //
				 unsigned  short									usCnt;
				 QIS_dynBmp_info										mems[8];

				 void									*			pInternal;
				 unsigned  short									usCnt_mems;

}		 RETRIEVE_DYN_BMPS;
*/

 int  retrieveDynBmps2Stream(  unsigned  int  uiStreamId,  RETRIEVE_DYN_BMPS  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pReq->ucbResp  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbResp,  (  void  *  )pReq->ucbResp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pReq->tLastRefreshedTime_misServ  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tLastRefreshedTime,  (  void  *  )&pReq->tLastRefreshedTime_misServ,  sizeof(  pReq->tLastRefreshedTime_misServ  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->usCnt  )  {
		 if  (  pReq->usCnt  >  mycountof(  pReq->mems  )  )  {		//  2014/10/14
			 qyShowInfo1(  CONST_qyShowType_qwmComm,  NULL,  NULL,  _T(  "IsCli"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "    retrieveDynBmps2Stream: usCnt %d too big"  ),  (  int  )pReq->usCnt  );
			 goto  errLabel;
		 }
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt,  (  void  *  )pReq->usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  !pReq->ucbResp  )  {
		 //  2014/09/04
		 if  (  pReq->u.req.ucbRetrieveOne  )  {
			 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbRetrieveOne,  (  void  *  )pReq->u.req.ucbRetrieveOne,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 //
		 if  (  pReq->u.req.ucbNext  )  {
			 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbNext,  (  void  *  )pReq->u.req.ucbNext,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->u.req.idInfo.ui64Id  )  {
			 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  (  void  *  )&pReq->u.req.idInfo.ui64Id,  sizeof(  pReq->u.req.idInfo.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->u.req.uiObjType  )  {
			 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiObjType,  (  void  *  )pReq->u.req.uiObjType,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->u.req.usIndex_obj  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_index,  (  void  *  )pReq->u.req.usIndex_obj,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
		}
	 else  {
		   if  (  pReq->u.resp.ucbEnd  )  {
			   if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbEnd,  (  void  *  )pReq->u.resp.ucbEnd,  0,  &ptr,  &len  )  )  goto  errLabel;
		   }
	 }
	
	 //  2014/09/25
	 if  (  pReq->conf.idInfo_imGrp_related.ui64Id  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_grp_related,  (  void  *  )&pReq->conf.idInfo_imGrp_related.ui64Id,  sizeof(  pReq->conf.idInfo_imGrp_related  ),  &ptr,  &len  )  )  goto  errLabel;
	 }

	 // 2017/06/11
	 if  (  pReq->ucbAvConsole  )  {
		 //if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbAvConsole,  (  void  *  )pReq->ucbAvConsole,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {
		  QIS_dynBmp_info		*  pMem	  =		&pReq->mems[i];
		  				
		  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_mem,  0,  &ptr,  &len  )  )  goto  errLabel;

		  if  (  pMem->qisResObj.idInfo.ui64Id  )  {
			  if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  (  void  *  )&pMem->qisResObj.idInfo.ui64Id,  sizeof(  pMem->qisResObj.idInfo.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
		  }
		  if  (  pMem->qisResObj.resObj.uiObjType  )  {
			  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiObjType,  (  void  *  )pMem->qisResObj.resObj.uiObjType,  0,  &ptr,  &len  )  )  goto  errLabel;
		  }
		  if  (  pMem->qisResObj.resObj.usIndex_obj  )  {
			  if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_index,  (  void  *  )pMem->qisResObj.resObj.usIndex_obj,  0,  &ptr,  &len  )  )  goto  errLabel;
		  }

		  //  2016/07/23
		  if  (  pMem->qisResObj.resObj.usHelp_subIndex  )  {
			  if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_help_subIndex,  (  void  *  )pMem->qisResObj.resObj.usHelp_subIndex,  0,  &ptr,  &len  )  )  goto  errLabel;
		  }

		  //
		  if  (  pMem->name[0]  )  {
			  if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_name,  pMem->name,  lstrlen(  pMem->name  ),  &ptr,  &len  )  )  goto  errLabel;
		  }
		  if  (  pMem->cusName[0]  )  {
			  if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_cusName,  pMem->cusName,  lstrlen(  pMem->cusName  ),  &ptr,  &len  )  )  goto  errLabel;
		  }
		  //  2017/06/12
		  if  (  pMem->usW  )  {
			  if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_width,  (  void  *  )pMem->usW,  0,  &ptr,  &len  )  )  goto  errLabel;
		  }
		  if  (  pMem->usH  )  {
			  if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_height,  (  void  *  )pMem->usH,  0,  &ptr,  &len  )  )  goto  errLabel;
		  }



		  //
		  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 	 
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2RetrieveDynBmps(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 RETRIEVE_DYN_BMPS		*	pContent	=	(  RETRIEVE_DYN_BMPS  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 	 
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
			 case  CONST_imCommType_retrieveDynBmps:
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_start:
							     pContent->uiType  =  uiStreamId;
								 break;
						   case  CONST_qnmCfgId_ucbResp:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->ucbResp  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_tLastRefreshedTime:
							     if  (  getFieldData_l64(  pItem,  &pContent->tLastRefreshedTime_misServ  )  )  goto  errLabel;
							     break;
						   //
						   case  CONST_qnmCfgId_usCnt:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usCnt  )  )  goto  errLabel;
								 //
								 if  (  pContent->usCnt  >  mycountof(  pContent->mems  )  )  goto  errLabel;
				   				 break;
						   //  2014/09/04
						   case  CONST_qnmCfgId_ucbRetrieveOne:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->u.req.ucbRetrieveOne  )  )  goto  errLabel;
							     break;
								 //
						   case  CONST_qnmCfgId_ucbNext:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->u.req.ucbNext  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_messengerId:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->u.req.idInfo.ui64Id  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_uiObjType:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->u.req.uiObjType  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_index:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->u.req.usIndex_obj  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_ucbEnd:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->u.resp.ucbEnd  )  )  goto  errLabel;
							     break;
								 //  2014/09/25
						   case  CONST_qnmCfgId_idInfo_grp_related:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->conf.idInfo_imGrp_related.ui64Id  )  )  goto  errLabel;
							     break;
								 //  2017/06/11
#if  0
						   case  CONST_qnmCfgId_ucbAvConsole:
								 if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->ucbAvConsole  )  )  goto  errLabel;
								 break;
#endif
								 //
						   default:
								   break;
				   }
				   break;				   
			 case  CONST_imCommType_mem:  {
				   QIS_dynBmp_info  *  pMem		=	NULL;
				   //
				   if  (  pContent->usCnt_mems  >=  mycountof(  pContent->mems  )  )  {
					   traceLogA(  (char*)  "tmpHandler_stream2RefreshDynBmps failed: usCnt_mems is too big"  );  goto  errLabel;
				   }
				   //
				   pMem  =  &pContent->mems[pContent->usCnt_mems];				   
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_messengerId:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pMem->qisResObj.idInfo.ui64Id  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_uiObjType:
							   if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->qisResObj.resObj.uiObjType  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_index:
							   if  (  getFieldData_short(  pItem,  (  short  *  )&pMem->qisResObj.resObj.usIndex_obj  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_help_subIndex:  //  2016/07/23
							   if  (  getFieldData_short(  pItem,  (  short  *  )&pMem->qisResObj.resObj.usHelp_subIndex  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_name:
							     if  (  getFieldData_wStr(  pItem,  pMem->name,  mycountof(  pMem->name  )  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_cusName:
							     if  (  getFieldData_wStr(  pItem,  pMem->cusName,  mycountof(  pMem->cusName  )  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_width:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pMem->usW  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_height:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pMem->usH  )  )  goto  errLabel;
							     break;

						   case  CONST_qnmCfgId_null:
							     pContent->usCnt_mems  ++  ;
							     break;
						   default:
									break;
				   }
				   //
				   }
				   break;
			 
	 }


	 iErr  =  0;
errLabel:
	 return  iErr;
}


///////////////////////

//  2015/08/01
 int  procOfflineResU2Stream(  unsigned  int  uiStreamId,  PROC_offlineRes_u  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pReq->common.ucbResp  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbResp,  (  void  *  )pReq->common.ucbResp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  pReq->common.usSubtype  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_subtype,  (  void  *  )pReq->common.usSubtype,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //	 
	 switch  (  pReq->common.usSubtype  )  {
			 case  CONST_procOfflineResSubtype_getCfgs:
				   //
				   if  (  pReq->getCfgs.resp.idInfo_resServ.ui64Id  )  {
					   if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_resServ,  (  void  *  )&pReq->getCfgs.resp.idInfo_resServ.ui64Id,  sizeof(  pReq->getCfgs.resp.idInfo_resServ.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;	 
				   }
				   break;
			 case  CONST_procOfflineResSubtype_retrieve:
				   //
				   if  (  pReq->retrieve.req.idInfo_logicalPeer.ui64Id  )  {
					   if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_logicalPeer,  (  void  *  )&pReq->retrieve.req.idInfo_logicalPeer.ui64Id,  sizeof(  pReq->retrieve.req.idInfo_logicalPeer.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;	 
				   }
				   if  (  pReq->retrieve.req.ucbP2p  )  {
					   if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbP2p,  (  void  *  )pReq->retrieve.req.ucbP2p,  0,  &ptr,  &len  )  )  goto  errLabel;
				   }
				   //  2015/08/14
				   if  (  pReq->retrieve.req.usIndex_page  )  {				//  0 based index. 2015/08/13
					   if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_index_page,  (  void  *  )pReq->retrieve.req.usIndex_page,  0,  &ptr,  &len  )  )  goto  errLabel;
				   }
				   if  (  pReq->retrieve.req.max_usCnt  )  {
					   if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_max_usCnt,  (  void  *  )pReq->retrieve.req.max_usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;
				   }
				   if  (  pReq->retrieve.req.keyword[0]  )  {
					   if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_keyword,  pReq->retrieve.req.keyword,  lstrlen(  pReq->retrieve.req.keyword  ),  &ptr,  &len  )  )  goto  errLabel;
				   }
				   //
				   if  (  pReq->retrieve.resp.usCnt  )  {
					   if  (  pReq->retrieve.resp.usCnt  >  mycountof(  pReq->retrieve.resp.mems  )  )  {		//  2014/10/14
						   qyShowInfo1(  CONST_qyShowType_qwmComm,  NULL,  NULL,  _T(  "IsCli"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "    retrieveDynBmps2Stream: usCnt %d too big"  ),  (  int  )pReq->retrieve.resp.usCnt  );
						   goto  errLabel;		 
					   }
					   if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt,  (  void  *  )pReq->retrieve.resp.usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;	 
				   }
				   	 
				   //
				   for  (  i  =  0;  i  <  pReq->retrieve.resp.usCnt;  i  ++  )  {
					    QIS_offline_res		*  pMem	  =		&pReq->retrieve.resp.mems[i];
		  				
						if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_mem,  0,  &ptr,  &len  )  )  goto  errLabel;
						
						if  (  pMem->res.idInfo.ui64Id  )  {			  
							if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  (  void  *  )&pMem->res.idInfo.ui64Id,  sizeof(  pMem->res.idInfo.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;		  
						}
						if  (  pMem->res.resObj.uiObjType  )  {
							if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiObjType,  (  void  *  )pMem->res.resObj.uiObjType,  0,  &ptr,  &len  )  )  goto  errLabel;		  
						}
						if  (  pMem->res.resObj.usIndex_obj  )  {			  
							if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_index,  (  void  *  )pMem->res.resObj.usIndex_obj,  0,  &ptr,  &len  )  )  goto  errLabel;		  
						}
						
						if  (  pMem->name[0]  )  {
							if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_name,  pMem->name,  lstrlen(  pMem->name  ),  &ptr,  &len  )  )  goto  errLabel;		  
						}
						if  (  pMem->tCreationTime  )  {  //  2015/08/12
							if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tCreationTime,  &pMem->tCreationTime,  sizeof(  pMem->tCreationTime  ),  &ptr,  &len  )  )  goto  errLabel;
						}

						if  (  pMem->ui64FileLen  )  {
							if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_ui64FileLen,  (  void  *  )&pMem->ui64FileLen,  sizeof(  pMem->ui64FileLen  ),  &ptr,  &len  )  )  goto  errLabel;	 
						}
						
						if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;	 
				   }

				   break;
			 case  CONST_procOfflineResSubtype_download:
				   if  (  pReq->download.idInfo_logicalPeer.ui64Id  )  {
					   if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_logicalPeer,  (  void  *  )&pReq->download.idInfo_logicalPeer.ui64Id,  sizeof(  pReq->download.idInfo_logicalPeer.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;	 
				   }
				   if  (  pReq->download.fileName[0]  )  {
					   if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_fileName,  pReq->download.fileName,  lstrlen(  pReq->download.fileName  ),  &ptr,  &len  )  )  goto  errLabel;		  
				   }
				   if  (  pReq->download.idInfo_sender.ui64Id  )  {
					   if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_sender,  (  void  *  )&pReq->download.idInfo_sender.ui64Id,  sizeof(  pReq->download.idInfo_sender.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;	 
				   }				   	
				   if  (  pReq->download.tCreationTime  )  {  //  2015/08/12					
					   if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tCreationTime,  &pReq->download.tCreationTime,  sizeof(  pReq->download.tCreationTime  ),  &ptr,  &len  )  )  goto  errLabel;						
				   }

				   break;
			 case  CONST_procOfflineResSubtype_del:
				   if  (  pReq->del.idInfo_logicalPeer.ui64Id  )  {
					   if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_logicalPeer,  (  void  *  )&pReq->del.idInfo_logicalPeer.ui64Id,  sizeof(  pReq->del.idInfo_logicalPeer.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;	 
				   }
				   if  (  pReq->del.fileName[0]  )  {
					   if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_fileName,  pReq->del.fileName,  lstrlen(  pReq->del.fileName  ),  &ptr,  &len  )  )  goto  errLabel;		  
				   }
				   if  (  pReq->del.idInfo_sender.ui64Id  )  {
					   if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_sender,  (  void  *  )&pReq->del.idInfo_sender.ui64Id,  sizeof(  pReq->del.idInfo_sender.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;	 
				   }
				   if  (  pReq->del.tCreationTime  )  {  //  2015/08/12					
					   if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tCreationTime,  &pReq->del.tCreationTime,  sizeof(  pReq->del.tCreationTime  ),  &ptr,  &len  )  )  goto  errLabel;						
				   }

				   break;
			 default:
					break;
	 }

	 	 
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2ProcOfflineResU(  CTX_stream2Data  *  pCtx,  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 PROC_offlineRes_u		*	pContent	=	(  PROC_offlineRes_u  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 	 
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
			 case  CONST_imCommType_procOfflineRes:
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_start:
							     pContent->common.uiType  =  uiStreamId;
								 break;
						   case  CONST_qnmCfgId_ucbResp:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->common.ucbResp  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_subtype:
							     if  (  pContent->common.usSubtype  )  goto  errLabel;
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->common.usSubtype  )  )  goto  errLabel;
							     break;
						   default:
								  break;
				   }
			 default:
					break;
	 }
	 	
	 //	
	 if  (  pContent->common.usSubtype  ==  CONST_procOfflineResSubtype_getCfgs  )  {		
		 switch  (  uiStreamId  )  {
				 case  CONST_imCommType_procOfflineRes:								 
					   //								
					   switch  (  tmp_cfgId  )  {																			  
							   case  CONST_qnmCfgId_idInfo_resServ:
								     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->getCfgs.resp.idInfo_resServ.ui64Id  )  )  goto  errLabel;							     											   
									 break;
							   default:
									   break;								 								  
					   }
					   break;						
				 default:							
						break;
				   
		 }
		 //
		 iErr  =  0;  goto  errLabel;			
		 }
	 else  if  (  pContent->common.usSubtype  ==  CONST_procOfflineResSubtype_retrieve  )  {
			   switch  (  uiStreamId  )  {
				       case  CONST_imCommType_procOfflineRes:								 
						     //				
						     switch  (  tmp_cfgId  )  {			 //
									 case  CONST_qnmCfgId_idInfo_logicalPeer:
										   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->retrieve.req.idInfo_logicalPeer.ui64Id  )  )  goto  errLabel;
										   break;
									 case  CONST_qnmCfgId_ucbP2p:  //  2015/08/05
										   if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->retrieve.req.ucbP2p  )  )  goto  errLabel;
										   break;
									 case  CONST_qnmCfgId_index_page:  //  2015/08/12
										   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->retrieve.req.usIndex_page  )  )  goto  errLabel;
										   break;
									 case  CONST_qnmCfgId_max_usCnt:
										   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->retrieve.req.max_usCnt  )  )  goto  errLabel;
										   break;
									 case  CONST_qnmCfgId_keyword:
										   if  (  getFieldData_wStr(  pItem,  pContent->retrieve.req.keyword,  mycountof(  pContent->retrieve.req.keyword  )  )  )  goto  errLabel;
										   break;

										   //
									 case  CONST_qnmCfgId_usCnt:
										   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->retrieve.resp.usCnt  )  )  goto  errLabel;								 
										   //
										   if  (  pContent->retrieve.resp.usCnt  >  mycountof(  pContent->retrieve.resp.mems  )  )  goto  errLabel;				   				 
										   break;											   
									 default:								   
											 break;								
							 }
							 break;			   

					   case  CONST_imCommType_mem:  {
						     QIS_offline_res  *  pMem		=	NULL;				   
							 //
							 if  (  pContent->retrieve.usCnt_mems  >=  mycountof(  pContent->retrieve.resp.mems  )  )  {					   
								 traceLogA(  (char*)  "tmpHandler_stream2RefreshDynBmps failed: usCnt_mems is too big"  );  
								 goto  errLabel;				   
							 }				   
							 //
							 pMem  =  &pContent->retrieve.resp.mems[pContent->retrieve.usCnt_mems];				   
							 switch  (  tmp_cfgId  )  {
									 case  CONST_qnmCfgId_messengerId:
										   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pMem->res.idInfo.ui64Id  )  )  goto  errLabel;
										   break;
									 case  CONST_qnmCfgId_uiObjType:
										 if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->res.resObj.uiObjType  )  )  goto  errLabel;
										   break;
									 case  CONST_qnmCfgId_index:
										 if  (  getFieldData_short(  pItem,  (  short  *  )&pMem->res.resObj.usIndex_obj  )  )  goto  errLabel;
										   break;
									 case  CONST_qnmCfgId_name:							     
										   if  (  getFieldData_wStr(  pItem,  pMem->name,  mycountof(  pMem->name  )  )  )  goto  errLabel;
										   break;
									 case  CONST_qnmCfgId_tCreationTime:  //  2015/08/12
										   if  (  getFieldData_l64(  pItem,  &pMem->tCreationTime  )  )  goto  errLabel;
										   break;
									 case  CONST_qnmCfgId_ui64FileLen:
										   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pMem->ui64FileLen  )  )  goto  errLabel;
										   break;
									 case  CONST_qnmCfgId_null:
										   pContent->retrieve.usCnt_mems  ++  ;							     
										   break;						   
									 default:									
											 break;				   
							 }				   
							 //				   
							 }				   
							 break;
					   default:
							   break;			 
	 
			   }
			   //
			   iErr  =  0;  goto  errLabel;
	
				}
	 else  if  (  pContent->common.usSubtype  ==  CONST_procOfflineResSubtype_download  )  {
			   switch  (  uiStreamId  )  {
				       case  CONST_imCommType_procOfflineRes:								 
						     //				
						     switch  (  tmp_cfgId  )  {			 //
									 case  CONST_qnmCfgId_idInfo_logicalPeer:
										   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->download.idInfo_logicalPeer.ui64Id  )  )  goto  errLabel;
										   break;
									 case  CONST_qnmCfgId_fileName:
										   if  (  getFieldData_wStr(  pItem,  pContent->download.fileName,  mycountof(  pContent->download.fileName  )  )  )  goto  errLabel;								 
										   break;											   
									 case  CONST_qnmCfgId_idInfo_sender:
										   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->download.idInfo_sender.ui64Id  )  )  goto  errLabel;
										   break;
									 case  CONST_qnmCfgId_tCreationTime:  //  2015/08/12
										   if  (  getFieldData_l64(  pItem,  &pContent->download.tCreationTime  )  )  goto  errLabel;
										   break;
									 default:								   
											 break;								
							 }
							 break;			
					   default:
								break;
			   }
			   }
	 else  if  (  pContent->common.usSubtype  ==  CONST_procOfflineResSubtype_del  )  {
			   switch  (  uiStreamId  )  {
				       case  CONST_imCommType_procOfflineRes:								 
						     //				
						     switch  (  tmp_cfgId  )  {			 //
									 case  CONST_qnmCfgId_idInfo_logicalPeer:
										   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->del.idInfo_logicalPeer.ui64Id  )  )  goto  errLabel;
										   break;
									 case  CONST_qnmCfgId_fileName:
										   if  (  getFieldData_wStr(  pItem,  pContent->del.fileName,  mycountof(  pContent->del.fileName  )  )  )  goto  errLabel;								 
										   break;											   
									 case  CONST_qnmCfgId_idInfo_sender:
										   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->del.idInfo_sender.ui64Id  )  )  goto  errLabel;
										   break;
									 case  CONST_qnmCfgId_tCreationTime:  //  2015/08/12
										   if  (  getFieldData_l64(  pItem,  &pContent->del.tCreationTime  )  )  goto  errLabel;
										   break;
									 default:								   
											 break;								
							 }
							 break;			
					   default:
								break;
			   }
	 }



	 iErr  =  0;
errLabel:
	 return  iErr;
}















////////////////////////////

#if  0

 int  qisIntervalParams2Stream(  unsigned  int  uiStreamId,  QIS_INTERVAL_PARAMS  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usIntervalInS_refreshRecentFriends,  (  void  *  )pReq->usIntervalInS_refreshRecentFriends,  0,  &ptr,  &len  )  )  goto  errLabel;
	 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usIntervalInS_refreshContactList,  (  void  *  )pReq->usIntervalInS_refreshContactList,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2QisIntervalParams(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 QIS_INTERVAL_PARAMS	*	pContent	=	(  QIS_INTERVAL_PARAMS  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_intervalParams  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );
	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_start:
				   pContent->uiType  =  uiStreamId;   
				   break;
			 case  CONST_qnmCfgId_usIntervalInS_refreshRecentFriends:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usIntervalInS_refreshRecentFriends  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usIntervalInS_refreshContactList:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usIntervalInS_refreshContactList  )  )  goto  errLabel;
				   break;
			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}

#endif


 int  qisGetCfgsReq2Stream(  unsigned  int  uiStreamId,  QIS_getCfgs_req  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pReq->ucbResp  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbResp,  (  void  *  )pReq->ucbResp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pReq->uiSizePerSnd_media  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiSizePerSnd,  (  void  *  )pReq->uiSizePerSnd_media,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usIntervalInS_refreshRecentFriends,  (  void  *  )pReq->intervalParams.usIntervalInS_refreshRecentFriends,  0,  &ptr,  &len  )  )  goto  errLabel;
	 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usIntervalInS_refreshContactList,  (  void  *  )pReq->intervalParams.usIntervalInS_refreshContactList,  0,  &ptr,  &len  )  )  goto  errLabel;

	 //  2015/07/28
#if  0
	 if  (  pReq->ucbNotUseP2pCall  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbNotUseP2pCall,  (  void  *  )pReq->ucbNotUseP2pCall,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
#endif

	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2QisGetCfgsReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 QIS_getCfgs_req			*	pContent	=	(  QIS_getCfgs_req  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_getCfgsReq  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );
	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_start:
				   pContent->uiType  =  uiStreamId;   
				   break;
			 case  CONST_qnmCfgId_ucbResp:
				   if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->ucbResp  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiSizePerSnd:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiSizePerSnd_media  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usIntervalInS_refreshRecentFriends:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->intervalParams.usIntervalInS_refreshRecentFriends  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usIntervalInS_refreshContactList:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->intervalParams.usIntervalInS_refreshContactList  )  )  goto  errLabel;
				   break;
#if  0
			 case  CONST_qnmCfgId_ucbNotUseP2pCall:  //  2015/07/28
				   if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->ucbNotUseP2pCall  )  )  goto  errLabel;
				   break;
#endif
			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}






//////////////////////



//  
 int  transferFileReq2Stream(  unsigned  int  uiStreamId,  TRANSFER_FILE_REQ  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pReq->ui64FileLen  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_ui64FileLen,  (  void  *  )&pReq->ui64FileLen,  sizeof(  pReq->ui64FileLen  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->fileName[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_fileName, pReq->fileName,  lstrlen(  pReq->fileName  ),  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //  2014/07/13
	 if  (  pReq->uiSizePerSnd_suggest  )  {	
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiSizePerSnd,  (  void  *  )pReq->uiSizePerSnd_suggest,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //
	 if (pReq->MAX_FILE_SEND_BLOCK_suggest) {
		 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_MAX_FILE_SEND_BLOCK, (void*)pReq->MAX_FILE_SEND_BLOCK_suggest, 0, &ptr, &len))  goto  errLabel;
	 }

	 //  2015/08/05
	 if  (  pReq->usSubtype  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_subtype,  (  void  *  )pReq->usSubtype,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	
	 if  (  pReq->idInfo_logicalPeer.ui64Id  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_logicalPeer,  (  void  *  )&pReq->idInfo_logicalPeer.ui64Id,  sizeof(  pReq->idInfo_logicalPeer.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 


	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2TransferFileReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 TRANSFER_FILE_REQ		*	pContent	=	(  TRANSFER_FILE_REQ  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_transferFileReq  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_start:
				   pContent->uiType  =  uiStreamId;
				   break;
			 case  CONST_qnmCfgId_fileName:
				   if  (  getFieldData_wStr(  pItem,  pContent->fileName,  mycountof(  pContent->fileName  )  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_ui64FileLen:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->ui64FileLen  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiSizePerSnd:	//  2014/07/13
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiSizePerSnd_suggest  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_MAX_FILE_SEND_BLOCK:
				   if (getFieldData_long(pItem, (long*)&pContent->MAX_FILE_SEND_BLOCK_suggest))  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_subtype:   //  2015/08/05
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usSubtype  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_idInfo_logicalPeer:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->idInfo_logicalPeer.ui64Id  )  )  goto  errLabel;
				   break;
			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}






 int  transferFileReplyReq2Stream(  unsigned  int  uiStreamId,  TRANSFER_FILE_REPLYREQ  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
				 
	 if  (  pReq->usOp  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usOp,  (  void  *  )pReq->usOp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->tStartTime_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tStartTime_org,  &pReq->tStartTime_org,  sizeof(  pReq->tStartTime_org  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->uiTranNo_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_org,  (  void  *  )pReq->uiTranNo_org,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->uiSerialNo_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiSerialNo_org,  (  void  *  )pReq->uiSerialNo_org,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2TransferFileReplyReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 TRANSFER_FILE_REPLYREQ	*	pContent	=	(  TRANSFER_FILE_REPLYREQ  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_transferFileReplyReq  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_start:
				   pContent->uiType  =  uiStreamId;
				   break;
			 case  CONST_qnmCfgId_usOp:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usOp  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_tStartTime_org:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->tStartTime_org  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiTranNo_org:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiTranNo_org  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiSerialNo_org:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiSerialNo_org  )  )  goto  errLabel;
				   break;
			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}


 int  taskProcReq2Stream(  unsigned  int  uiStreamId,  TASK_PROC_REQ  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 //
	 if  (  pReq->usOp  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usOp,  (  void  *  )pReq->usOp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->tStartTime_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tStartTime_org,  &pReq->tStartTime_org,  sizeof(  pReq->tStartTime_org  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->uiTranNo_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_org,  (  void  *  )pReq->uiTranNo_org,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->uiSerialNo_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiSerialNo_org,  (  void  *  )pReq->uiSerialNo_org,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pReq->uiContentType_org  )  {	//  
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiContentType_org,  (  void  *  )pReq->uiContentType_org,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if (pReq->idInfo_imGrp_related.ui64Id) {
		 if (data2Stream(CONST_qyDataType_l64, CONST_qnmCfgId_idInfo_grp_related, (void*)&pReq->idInfo_imGrp_related.ui64Id, sizeof(pReq->idInfo_imGrp_related.ui64Id), &ptr, &len)) goto  errLabel;
	 }

	 //  2014/08/28
	 if  (  pReq->usTaskProcObjType  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usTaskProcObjType,  (  void  *  )pReq->usTaskProcObjType,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  pReq->usTaskProcObjType  )  {

		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_mem,  0,  &ptr,  &len  )  )  goto  errLabel;

		 switch  (  pReq->usTaskProcObjType  )  {
				 case  CONST_usTaskProcObjType_vStream:
					   //
					   if  (  pReq->vStream.uiTranNo_openAvDev  )  {
						   if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_openVideoDev,  (  void  *  )pReq->vStream.uiTranNo_openAvDev,  0,  &ptr,  &len  )  )  goto  errLabel;
					   }
					   //
#if  0
					   if  (  pReq->vStream.idInfo_src.ui64Id  )  {
						   if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId_src,  (  void  *  )&pReq->vStream.idInfo_src.ui64Id,  sizeof(  pReq->vStream.idInfo_src.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
					   }
					   if  (  pReq->vStream.uiTranNo_openAvDev_src  )  {
						   if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_openVideoDev_src,  (  void  *  )pReq->vStream.uiTranNo_openAvDev_src,  0,  &ptr,  &len  )  )  goto  errLabel;
					   }
#endif
					   //
					   break;
				 default:
						break;
		 }


		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }



	 //  2009/09/11
	 if  (  pReq->uiTaskType  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTaskType,  (  void  *  )pReq->uiTaskType,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->viewDynBmp.ros.uiObjType  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiObjType,  (  void  *  )pReq->viewDynBmp.ros.uiObjType,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->viewDynBmp.ros.usIndex_obj  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_index,  (  void  *  )pReq->viewDynBmp.ros.usIndex_obj,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}

 int  tmpHandler_stream2TaskProcReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 TRANSFER_FILE_PROCREQ	*	pContent	=	(  TRANSFER_FILE_PROCREQ  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 //if  (  uiStreamId  !=  CONST_imCommType_taskProcReq  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
			 case  CONST_imCommType_taskProcReq:
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_start:
							     pContent->uiType  =  uiStreamId;
								 break;
						   case  CONST_qnmCfgId_usOp:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usOp  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_tStartTime_org:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->tStartTime_org  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_uiTranNo_org:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiTranNo_org  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_uiSerialNo_org:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiSerialNo_org  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_uiContentType_org:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiContentType_org  )  )  goto  errLabel;				   
								 break;

								 //
						   case  CONST_qnmCfgId_idInfo_grp_related:
								 //
							     if (getFieldData_l64(pItem, (__int64*) & pContent->idInfo_imGrp_related.ui64Id))  goto  errLabel;
								 //
								 break;

								 //
						   case  CONST_qnmCfgId_usTaskProcObjType:	//  2014/08/28
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usTaskProcObjType  )  )  goto  errLabel;
							     break;
								 
								 //  2014/10/09							
						   case  CONST_qnmCfgId_uiTaskType:	//  2009/09/11
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiTaskType  )  )  goto  errLabel;								
								 break;
						   case  CONST_qnmCfgId_uiObjType:									  
							   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->viewDynBmp.ros.uiObjType  )  )  goto  errLabel;									  
								 break;
						   case  CONST_qnmCfgId_index:									  
							   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->viewDynBmp.ros.usIndex_obj  )  )  goto  errLabel;									  
								 break;
								 
						   default:
								  break;	 
				   }
				   break;
			 case  CONST_imCommType_mem:	//  2014/08/28
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_uiTranNo_openVideoDev:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->vStream.uiTranNo_openAvDev  )  )  goto  errLabel;
							     break;
#if  0
						   case  CONST_qnmCfgId_messengerId_src:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->vStream.idInfo_src.ui64Id  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_uiTranNo_openVideoDev_src:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->vStream.uiTranNo_openAvDev_src  )  )  goto  errLabel;
							     break;
#endif
								 //
						   default:
								  break;
				   }
				   break;
			 default:
					break;
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
}


///////////////

  int  taskProcResp2Stream(  unsigned  int  uiStreamId,  TASK_PROC_RESP  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
				 
	 if  (  pReq->tStartTime_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tStartTime_org,  &pReq->tStartTime_org,  sizeof(  pReq->tStartTime_org  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->uiTranNo_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_org,  (  void  *  )pReq->uiTranNo_org,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->usCmd_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCmd_org,  (  void  *  )pReq->usCmd_org,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->usOp_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usOp_org,  (  void  *  )pReq->usOp_org,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pReq->iStatus  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_status,  (  void  *  )pReq->iStatus,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pReq->idInfo_logicalPeer.ui64Id  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_logicalPeer,  (  void  *  )&pReq->idInfo_logicalPeer.ui64Id,  sizeof(  pReq->idInfo_logicalPeer.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}

 int  tmpHandler_stream2TaskProcResp(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 TASK_PROC_RESP			*	pContent	=	(  TASK_PROC_RESP  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_taskProcResp  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_start:
				   pContent->uiType  =  uiStreamId;
				   break;
			 case  CONST_qnmCfgId_tStartTime_org:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->tStartTime_org  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiTranNo_org:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiTranNo_org  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usCmd_org:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usCmd_org  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usOp_org:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usOp_org  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_status:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->iStatus  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_idInfo_logicalPeer:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->idInfo_logicalPeer.ui64Id  )  )  goto  errLabel;
				   break;
			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}



 ///////////////////
 int  transferFileDataReq2Stream(  unsigned  int  uiStreamId,  TRANSFER_FILEDATA_REQ  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
		
	 if  (  pReq->tStartTime_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tStartTime_org,  &pReq->tStartTime_org,  sizeof(  pReq->tStartTime_org  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->uiTranNo_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_org,  (  void  *  )pReq->uiTranNo_org,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->uiSerialNo_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiSerialNo_org,  (  void  *  )pReq->uiSerialNo_org,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pReq->uiSizePerSnd  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiSizePerSnd,  (  void  *  )pReq->uiSizePerSnd,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pReq->uiDataBlockIndex  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiDataBlockIndex,  (  void  *  )pReq->uiDataBlockIndex,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if (pReq->us_nBlocks) {
		 if (data2Stream(CONST_qyDataType_short, CONST_qnmCfgId_us_nBlocks, (void*)pReq->us_nBlocks, 0, &ptr, &len))  goto  errLabel;
	 }

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}

 int  tmpHandler_stream2TransferFileDataReq( CTX_stream2Data * pCtx,  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 TRANSFER_FILEDATA_REQ	*	pContent	=	(  TRANSFER_FILEDATA_REQ  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_transferFileDataReq  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_start:
				   pContent->uiType  =  uiStreamId;
				   break;
			 case  CONST_qnmCfgId_tStartTime_org:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->tStartTime_org  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiTranNo_org:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiTranNo_org  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiSerialNo_org:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiSerialNo_org  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiSizePerSnd:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiSizePerSnd  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiDataBlockIndex:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiDataBlockIndex  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_us_nBlocks:
				 if (getFieldData_short(pItem, (short*)&pContent->us_nBlocks))  goto  errLabel;
				 break;
			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}


 int  transferFileDataResp2Stream(  unsigned  int  uiStreamId,  TRANSFER_FILEDATA_RESP  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
				 
	 if  (  pReq->uiDataBlockIndex  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiDataBlockIndex,  (  void  *  )pReq->uiDataBlockIndex,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
#if  0	//  2014/07/13
	 if  (  pReq->uiLen  )  {
		 if  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_rawData,  (  void  *  )pReq->buf,  pReq->uiLen,  &ptr,  &len  )  )  goto  errLabel;
	 }
#endif
	 //  2014/07/13
	 if  (  pReq->uiLen  )  {
		 if  (  data2Stream(  CONST_qyDataType_lData,  CONST_qnmCfgId_rawData,  (  void  *  )pReq->buf,  pReq->uiLen,  &ptr,  &len  )  )  goto  errLabel;
	 }


	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}

 int  tmpHandler_stream2TransferFileDataResp( CTX_stream2Data * pCtx,  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 TRANSFER_FILEDATA_RESP	*	pContent	=	(  TRANSFER_FILEDATA_RESP  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_transferFileDataResp  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_start:
				   pContent->uiType  =  uiStreamId;
				   break;
			 case  CONST_qnmCfgId_uiDataBlockIndex:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiDataBlockIndex  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_rawData:
				   pContent->uiLen  =  sizeof(  pContent->buf  );
#if  0
				   if  (  getFieldData_data(  pItem,  pContent->buf,  &pContent->uiLen  )  )  goto  errLabel;
#endif
				   //  2014/07/13
				   if  (  getFieldData_lData(  pItem,  pContent->buf,  &pContent->uiLen  )  )  goto  errLabel;
				   break;
			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}

 int  transferFileEndReq2Stream(  unsigned  int  uiStreamId,  TRANSFER_FILEEND_REQ  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
				 
	 if  (  pReq->tStartTime_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tStartTime_org,  &pReq->tStartTime_org,  sizeof(  pReq->tStartTime_org  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->uiTranNo_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_org,  (  void  *  )pReq->uiTranNo_org,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->uiSerialNo_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiSerialNo_org,  (  void  *  )pReq->uiSerialNo_org,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}

 int  tmpHandler_stream2TransferFileEndReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 TRANSFER_FILEEND_REQ	*	pContent	=	(  TRANSFER_FILEEND_REQ  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_transferFileEndReq  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_start:
				   pContent->uiType  =  uiStreamId;
				   break;
			 case  CONST_qnmCfgId_tStartTime_org:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->tStartTime_org  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiTranNo_org:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiTranNo_org  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiSerialNo_org:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiSerialNo_org  )  )  goto  errLabel;
				   break;
			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}



 int  transferFileEndResp2Stream(  unsigned  int  uiStreamId,  TRANSFER_FILEEND_RESP  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
				 
	 if  (  pReq->uiVerifyMethod  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiVerifyMethod,  (  void  *  )pReq->uiVerifyMethod,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}
 
 int  tmpHandler_stream2TransferFileEndResp( CTX_stream2Data * pCtx,  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 TRANSFER_FILEEND_RESP	*	pContent	=	(  TRANSFER_FILEEND_RESP  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_transferFileEndResp  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_start:
				   pContent->uiType  =  uiStreamId;
				   break;
			 case  CONST_qnmCfgId_uiVerifyMethod:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiVerifyMethod  )  )  goto  errLabel;
				   break;
			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}



 ////////////
 //
 //  QY_MESSENGER_REGINFO
 int  messengerRegInfo2Stream(  unsigned  int  uiStreamId,  QY_MESSENGER_REGINFO  *  pRegInfo,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pRegInfo  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 for  (  i  =  0;  i  <  mycountof(  pRegInfo->uiFieldIds  );  i  ++  )  {
		  if  (  !pRegInfo->u.cols[i][0]  )  continue;
		  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiFieldId,  (  void  *  )pRegInfo->uiFieldIds[i],  0,  &ptr,  &len  )  )  goto  errLabel;
		  if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_hint,  pRegInfo->u.cols[i],  lstrlen(  pRegInfo->u.cols[i]  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}


 int  tmpHandler_stream2MessengerRegInfo(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 QY_MESSENGER_REGINFO	*	pRegInfo	=	(  QY_MESSENGER_REGINFO  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 long						lVal;
	 
	 if  (  !pRegInfo  )  goto  errLabel;
	 if  (  pRegInfo->index  <  0  ||  pRegInfo->index  >=  mycountof(  pRegInfo->u.cols  )  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_messengerRegInfo  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );
	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_uiFieldId:
				   if  (  getFieldData_long(  pItem,  &lVal  )  )  goto  errLabel;
				   pRegInfo->uiFieldIds[pRegInfo->index]  =  lVal;
				   break;
			 case  CONST_qnmCfgId_hint:
				   if  (  getFieldData_wStr(  pItem,  pRegInfo->u.cols[pRegInfo->index],  mycountof(  pRegInfo->u.cols[pRegInfo->index]  )  )  )  goto  errLabel;
				   pRegInfo->index  ++  ;
				   break;
			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}


 //  QY_MESSENGER_PCINFO
 int  messengerPcInfo2Stream(  unsigned  int  uiStreamId,  QY_MESSENGER_PCINFO  *  pPcInfo,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;
	 unsigned  long		ulIp	=	0;

	 if  (  !pPcInfo  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 //
	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiDevType_from,  (  void  *  )pPcInfo->uiType,  0,  &ptr,  &len  )  )  goto  errLabel;
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_iPlatformId,  (  void  *  )pPcInfo->iPlatformId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 //
	 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_pcName,  pPcInfo->pcName,  lstrlen(  pPcInfo->pcName  ),  &ptr,  &len  )  )  goto  errLabel;
	 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_domainName,  pPcInfo->domainName,  lstrlen(  pPcInfo->domainName  ),  &ptr,  &len  )  )  goto  errLabel;
	 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_osUsrName,  pPcInfo->osUsrName,  lstrlen(  pPcInfo->osUsrName  ),  &ptr,  &len  )  )  goto  errLabel;

	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}


 int  tmpHandler_stream2MessengerPcInfo(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 QY_MESSENGER_PCINFO	*	pPcInfo	=	(  QY_MESSENGER_PCINFO  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 long						lVal;
	 
	 if  (  !pPcInfo  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_messengerPcInfo  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );
	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_uiDevType_from:
				   if  (  getFieldData_long(  pItem,  &lVal  )  )  goto  errLabel;
				   pPcInfo->uiType  =  lVal;
				   break;
			 case  CONST_qnmCfgId_iPlatformId:
				   if  (  getFieldData_long(  pItem,  &lVal  )  )  goto  errLabel;
				   pPcInfo->iPlatformId  =  lVal;
				   break;
			 case  CONST_qnmCfgId_pcName:
				   if  (  getFieldData_wStr(  pItem,  pPcInfo->pcName,  mycountof(  pPcInfo->pcName  )  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_domainName:
				   if  (  getFieldData_wStr(  pItem,  pPcInfo->domainName,  mycountof(  pPcInfo->domainName  )  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_osUsrName:
				   if  (  getFieldData_wStr(  pItem,  pPcInfo->osUsrName,  mycountof(  pPcInfo->osUsrName  )  )  )  goto  errLabel;
				   break;
			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}




// REFRESH_imObjRules_req
 int  refreshImObjRulesReq2Stream_0247(  unsigned  int  uiStreamId,  REFRESH_imObjRules_req  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;
	 unsigned  long		ulIp	=	0;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 //
	 if  (  pReq->ucbResp  &&  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbResp,  (  void  *  )pReq->ucbResp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 if  (  pReq->ucbRetrieveAll  &&  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbRetrieveAll,  (  void  *  )pReq->ucbRetrieveAll,  0,  &ptr,  &len  )  )  goto  errLabel;
	 if  (  pReq->usCnt  &&  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt,  (  void  *  )pReq->usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;
	 //
	 for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {

		  if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_mem,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
		  //
		  if  (  pReq->mems[i].idInfo_related.ui64Id  )  if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  (  void  *  )&pReq->mems[i].idInfo_related.ui64Id,  sizeof(  pReq->mems[i].idInfo_related.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
		  if  (  pReq->mems[i].uiRuleType  )  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiRuleType,  (  void  *  )pReq->mems[i].uiRuleType,  0,  &ptr,  &len  )  )  goto  errLabel;
		  if  (  pReq->mems[i].uiCmd  )  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_nCmd,  (  void  *  )pReq->mems[i].uiCmd,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}


  int  tmpHandler_stream2RefreshImObjRulesReq_0247(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int							iErr		=	-1;
	 //  p0;
	 REFRESH_imObjRules_req		*	pReq		=	(  REFRESH_imObjRules_req  *  )p1;
	 long							lVal;
	 int							index		=  0;

	 
	 if  (  !pReq  )  goto  errLabel;
	 if  (  pReq->tmpInternal.usCnt_mems  >  mycountof(  pReq->mems  )  )  goto  errLabel;	 
	 if  (  uiStreamId  !=  CONST_imCommType_refreshImObjRulesReq  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );
#if  10
	 switch  (  tmp_cfgId  )  {
		     case  CONST_qnmCfgId_start:
				   pReq->uiType  =  uiStreamId;   
				   break;
			 case  CONST_qnmCfgId_ucbResp:
				   if  (  getFieldData_char(  pItem,  (  char  *  )&pReq->ucbResp  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_ucbRetrieveAll:
				   if  (  getFieldData_char(  pItem,  (  char  *  )&pReq->ucbRetrieveAll  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usCnt:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pReq->usCnt  )  )  goto  errLabel;
				   //
				   if  (  pReq->usCnt  >  mycountof(  pReq->mems  )  )  goto  errLabel;
				   //
				   break;
			 case  CONST_qnmCfgId_mem:
				   if  (  pReq->tmpInternal.usCnt_mems  >=  pReq->usCnt  )  goto  errLabel;
			 	   pReq->tmpInternal.usCnt_mems  ++;
				   break;
		     case  CONST_qnmCfgId_messengerId:
			 	   index  =  pReq->tmpInternal.usCnt_mems  -  1;
				   if  (  index  <  0  )  goto  errLabel;
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pReq->mems[index].idInfo_related.ui64Id  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiRuleType:
				   index  =  pReq->tmpInternal.usCnt_mems  -  1;
				   if  (  index  <  0  )  goto  errLabel;
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pReq->mems[index].uiRuleType  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_nCmd:
				   index  =  pReq->tmpInternal.usCnt_mems  -  1;
				   if  (  index  <  0  )  goto  errLabel;
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pReq->mems[index].uiCmd  )  )  goto  errLabel;
				   break;
			 default:
					break;
	 }
#endif
	 iErr  =  0;
errLabel:
	 return  iErr;
}


 //  2011/11/12
 int  refreshImObjRulesReq2Stream(  unsigned  int  uiStreamId,  REFRESH_imObjRules_req  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;
	 unsigned  long		ulIp	=	0;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 //
	 if  (  pReq->ucbResp  &&  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbResp,  (  void  *  )pReq->ucbResp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 if  (  pReq->ucbRetrieveAll  &&  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbRetrieveAll,  (  void  *  )pReq->ucbRetrieveAll,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pReq->usMaxMemsPerSnd  &&  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usMaxMemsPerSnd,  (  void  *  )pReq->usMaxMemsPerSnd,  0,  &ptr,  &len  )  )  goto  errLabel;

	 //  2011/11/12
	 if  (  !pReq->ucbResp  )  {
		 if  (  pReq->u.req.ucbNext  &&  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbNext,  (  void  *  )pReq->u.req.ucbNext,  0,  &ptr,  &len  )  )  goto  errLabel;
		 if  (  pReq->u.req.idInfo_related.ui64Id  &&  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  (  void  *  )&pReq->u.req.idInfo_related.ui64Id,  sizeof(  pReq->mems[i].idInfo_related.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
		 if  (  pReq->u.req.uiRuleType  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiRuleType,  (  void  *  )pReq->u.req.uiRuleType,  0,  &ptr,  &len  )  )  goto  errLabel;
		 if  (  pReq->u.req.usIndex  &&  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_index,  (  void  *  )pReq->u.req.usIndex,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->ucbEnd  &&  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbEnd,  (  void  *  )pReq->ucbEnd,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 //
	 if  (  pReq->usCnt  &&  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt,  (  void  *  )pReq->usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;
	 //
	 for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {

		  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_mem,  0,  &ptr,  &len  )  )  goto  errLabel;
		  //
		  if  (  pReq->mems[i].idInfo_related.ui64Id  )  if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  (  void  *  )&pReq->mems[i].idInfo_related.ui64Id,  sizeof(  pReq->mems[i].idInfo_related.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
		  if  (  pReq->mems[i].uiRuleType  )  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiRuleType,  (  void  *  )pReq->mems[i].uiRuleType,  0,  &ptr,  &len  )  )  goto  errLabel;
		  if  (  pReq->mems[i].usIndex  &&  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_index,  (  void  *  )pReq->mems[i].usIndex,  0,  &ptr,  &len  )  )  goto  errLabel;
		  if  (  pReq->mems[i].uiCmd  )  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_nCmd,  (  void  *  )pReq->mems[i].uiCmd,  0,  &ptr,  &len  )  )  goto  errLabel;
		  if  (  pReq->mems[i].wDesc[0]  &&  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_hint,  (  void  *  )pReq->mems[i].wDesc,  lstrlen(  pReq->mems[i].wDesc  ),  &ptr,  &len  )  )  goto  errLabel;

		  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}


  int  tmpHandler_stream2RefreshImObjRulesReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int							iErr		=	-1;
	 //  p0;
	 REFRESH_imObjRules_req		*	pReq		=	(  REFRESH_imObjRules_req  *  )p1;
	 long							lVal;
	 //  int							index		=  0;

	 
	 if  (  !pReq  )  goto  errLabel;
	 if  (  pReq->tmpInternal.usCnt_mems  >  mycountof(  pReq->mems  )  )  goto  errLabel;	 
	 //  if  (  uiStreamId  !=  CONST_imCommType_refreshImObjRulesReq  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );
#if  10
	 switch  (  uiStreamId  )  {
		 case  CONST_imCommType_refreshImObjRulesReq:
			   switch  (  tmp_cfgId  )  {
				       case  CONST_qnmCfgId_start:
						     pReq->uiType  =  uiStreamId;   
							 break;
					   case  CONST_qnmCfgId_ucbResp:
						     if  (  getFieldData_char(  pItem,  (  char  *  )&pReq->ucbResp  )  )  goto  errLabel;
							 break;
					   case  CONST_qnmCfgId_ucbRetrieveAll:
						     if  (  getFieldData_char(  pItem,  (  char  *  )&pReq->ucbRetrieveAll  )  )  goto  errLabel;
							 break;
					   case  CONST_qnmCfgId_usMaxMemsPerSnd:
						     if  (  getFieldData_short(  pItem,  (  short  *  )&pReq->usMaxMemsPerSnd  )  )  goto  errLabel;
						     break;
					   case  CONST_qnmCfgId_ucbNext:
						     if  (  getFieldData_char(  pItem,  (  char  *  )&pReq->u.req.ucbNext  )  )  goto  errLabel;
						     break;
					   case  CONST_qnmCfgId_messengerId:
						     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pReq->u.req.idInfo_related.ui64Id  )  )  goto  errLabel;
							 break;
					   case  CONST_qnmCfgId_uiRuleType:
						     if  (  getFieldData_long(  pItem,  (  long  *  )&pReq->u.req.uiRuleType  )  )  goto  errLabel;
							 break;
					   case  CONST_qnmCfgId_index:
						     if  (  getFieldData_short(  pItem,  (  short  *  )&pReq->u.req.usIndex  )  )  goto  errLabel;
						     break;
					   case  CONST_qnmCfgId_ucbEnd:
						     if  (  getFieldData_char(  pItem,  (  char  *  )&pReq->ucbEnd  )  )  goto  errLabel;
						     break;
					   case  CONST_qnmCfgId_usCnt:
						     if  (  getFieldData_short(  pItem,  (  short  *  )&pReq->usCnt  )  )  goto  errLabel;
							 //
							 if  (  pReq->usCnt  >  mycountof(  pReq->mems  )  )  goto  errLabel;
							 //
							 break;		
					   default:
							   break;
			   }
			   break;
		 case  CONST_imCommType_mem:  {
			   REFRESH_imObjRule_reqMem  *  pMem  =  NULL;
			
			   if  (  pReq->tmpInternal.usCnt_mems  >=  pReq->usCnt  )  goto  errLabel;
			   pMem  =  &pReq->mems[pReq->tmpInternal.usCnt_mems];
			   switch  (  tmp_cfgId  )  {		 
					   case  CONST_qnmCfgId_messengerId:
						     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pMem->idInfo_related.ui64Id  )  )  goto  errLabel;
							 break;
					   case  CONST_qnmCfgId_uiRuleType:
						     if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->uiRuleType  )  )  goto  errLabel;
							 break;
					   case  CONST_qnmCfgId_index:
						     if  (  getFieldData_short(  pItem,  (  short  *  )&pMem->usIndex  )  )  goto  errLabel;
						     break;
					   case  CONST_qnmCfgId_nCmd:
						     if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->uiCmd  )  )  goto  errLabel;
							 break;
					   case  CONST_qnmCfgId_hint:
						     if  (  getFieldData_wStr(  pItem,  pMem->wDesc,  mycountof(  pMem->wDesc  )  )  )  goto  errLabel;
						     break;
					   case  CONST_qnmCfgId_null:
						     pReq->tmpInternal.usCnt_mems  ++;
							 break;
					   default:
							  break;
			   }
			   }
			   break;
		 default:
					break;
	 }
#endif
	 iErr  =  0;
errLabel:
	 return  iErr;
}


  //  2012/08/05

  
 //  2011/11/12
 int  ptzControlReq2Stream(  unsigned  int  uiStreamId,  PTZ_control_req  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;
	 unsigned  long		ulIp	=	0;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 //
	 if  (  pReq->ucbReply  &&  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbReply,  (  void  *  )pReq->ucbReply,  0,  &ptr,  &len  )  )  goto  errLabel;

	 //  2011/11/12
	 if  (  pReq->ucbReply  )  {

		 if  (  pReq->u.reply.tStartTime_org  )  {
			 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tStartTime_org,  &pReq->u.reply.tStartTime_org,  sizeof(  pReq->u.reply.tStartTime_org  ),  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->u.reply.uiTranNo_org  )  {
			 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_org,  (  void  *  )pReq->u.reply.uiTranNo_org,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->u.reply.tHint[0]  )  {
			 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_hint, pReq->u.reply.tHint,  lstrlen(  pReq->u.reply.tHint  ),  &ptr,  &len  )  )  goto  errLabel;
		 }
	 }
	 
	 //
	 if  (  pReq->usCnt  &&  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt,  (  void  *  )pReq->usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;
	 //
	 for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {

		  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_mem,  0,  &ptr,  &len  )  )  goto  errLabel;
		  //
		  if  (  pReq->mems[i].nAddr  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_nAddr,  (  void  *  )pReq->mems[i].nAddr,  0,  &ptr,  &len  )  )  goto  errLabel;
		  if  (  pReq->mems[i].nPelcoType  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_nPelcoType,  (  void  *  )pReq->mems[i].nPelcoType,  0,  &ptr,  &len  )  )  goto  errLabel;
		  //
		  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}


 int  tmpHandler_stream2PtzControlReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int							iErr		=	-1;
	 //  p0;
	 PTZ_control_req		*	pReq		=	(  PTZ_control_req  *  )p1;
	 long							lVal;
	 //  int							index		=  0;

	 
	 if  (  !pReq  )  goto  errLabel;
	 if  (  pReq->tmpInternal.usCnt_mems  >  mycountof(  pReq->mems  )  )  goto  errLabel;	 
	 //  if  (  uiStreamId  !=  CONST_imCommType_refreshImObjRulesReq  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );
#if  10
	 switch  (  uiStreamId  )  {
		 case  CONST_imCommType_ptzControlReq:
			   switch  (  tmp_cfgId  )  {
				       case  CONST_qnmCfgId_start:
						     pReq->uiType  =  uiStreamId;   
							 break;
					   case  CONST_qnmCfgId_ucbReply:
						     if  (  getFieldData_char(  pItem,  (  char  *  )&pReq->ucbReply  )  )  goto  errLabel;
							 break;
					   case  CONST_qnmCfgId_tStartTime_org:
						     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pReq->u.reply.tStartTime_org  )  )  goto  errLabel;							 
							 break;
					   case  CONST_qnmCfgId_uiTranNo_org:
						     if  (  getFieldData_long(  pItem,  (  long  *  )&pReq->u.reply.uiTranNo_org  )  )  goto  errLabel;
							 break;
					   case  CONST_qnmCfgId_hint:
						     if  (  getFieldData_wStr(  pItem,  pReq->u.reply.tHint,  mycountof(  pReq->u.reply.tHint  )  )  )  goto  errLabel;
							 break;

					   case  CONST_qnmCfgId_usCnt:
						     if  (  getFieldData_short(  pItem,  (  short  *  )&pReq->usCnt  )  )  goto  errLabel;
							 //
							 if  (  pReq->usCnt  >  mycountof(  pReq->mems  )  )  goto  errLabel;
							 //
							 break;		
					   default:
							   break;
			   }
			   break;
		 case  CONST_imCommType_mem:  {
			   PTZ_control_mem  *  pMem  =  NULL;
			
			   if  (  pReq->tmpInternal.usCnt_mems  >=  pReq->usCnt  )  goto  errLabel;
			   pMem  =  &pReq->mems[pReq->tmpInternal.usCnt_mems];
			   switch  (  tmp_cfgId  )  {
					   case  CONST_qnmCfgId_nAddr:
						     if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->nAddr  )  )  goto  errLabel;
							 break;
					   case  CONST_qnmCfgId_nPelcoType:
						     if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->nPelcoType  )  )  goto  errLabel;
							 break;
					   case  CONST_qnmCfgId_null:
						     pReq->tmpInternal.usCnt_mems  ++;
							 break;
					   default:
							  break;
			   }
			   }
			   break;
		 default:
					break;
	 }
#endif
	 iErr  =  0;
errLabel:
	 return  iErr;
}


  int  ptzControlCmd2Stream(  unsigned  int  uiStreamId,  PTZ_control_cmd  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;
	 unsigned  long		ulIp	=	0;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 //

	 //
#if  0
	 if  (  pReq->v0260.uiLen  )  {
		 if  (  data2Stream(  CONST_qyDataType_lData,  CONST_qnmCfgId_rawData,  (  void  *  )pReq->v0260.cmdBuf,  pReq->v0260.uiLen,  &ptr,  &len  )  )  goto  errLabel;
	 }
#endif

	 //  2014/09/13
	 if  (  pReq->cmdInfo.obj.uiObjType  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiObjType,  (  void  *  )pReq->cmdInfo.obj.uiObjType,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->cmdInfo.obj.usIndex_obj  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_index,  (  void  *  )pReq->cmdInfo.obj.usIndex_obj,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //  2016/07/24
	 if  (  pReq->cmdInfo.obj.usHelp_subIndex  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_help_subIndex,  (  void  *  )pReq->cmdInfo.obj.usHelp_subIndex,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //
	 if (pReq->cmdInfo.idInfo.ui64Id) {
		 if (data2Stream(CONST_qyDataType_l64, CONST_qnmCfgId_messengerId, (void*)&pReq->cmdInfo.idInfo.ui64Id, sizeof(pReq->cmdInfo.idInfo.ui64Id), &ptr, &len))goto  errLabel;
	 }
	 if (pReq->cmdInfo.iChannel) {
		 if (data2Stream(CONST_qyDataType_l32, CONST_qnmCfgId_iChannel, (void*)pReq->cmdInfo.iChannel, 0, &ptr, &len))goto  errLabel;
	 }

	 //
	 if  (  pReq->cmdInfo.ucCmd  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_nCmd,  (  void  *  )pReq->cmdInfo.ucCmd,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //
	 if (pReq->cmdInfo.ucMouseStatus) {
		 if (data2Stream(CONST_qyDataType_char, CONST_qnmCfgId_mouseStatus, (void*)pReq->cmdInfo.ucMouseStatus, 0, &ptr, &len))goto  errLabel;
	 }

	 //
	 switch  (  pReq->cmdInfo.ucCmd)  {
			 case  CONST_ptzCmd_3ddw:
				 if (pReq->paramU.param3ddw.sW_video) {
					 if (data2Stream(CONST_qyDataType_short, CONST_qnmCfgId_width, (void*)pReq->paramU.param3ddw.sW_video, 0, &ptr, &len))goto  errLabel;
				 }
				 if (pReq->paramU.param3ddw.sH_video) {
					 if (data2Stream(CONST_qyDataType_short, CONST_qnmCfgId_height, (void*)pReq->paramU.param3ddw.sH_video, 0, &ptr, &len))goto  errLabel;
				 }
				 if (pReq->paramU.param3ddw.xTop) {
					 if (data2Stream(CONST_qyDataType_short, CONST_qnmCfgId_xTop, (void*)pReq->paramU.param3ddw.xTop, 0, &ptr, &len))goto  errLabel;
				 }
				 if (pReq->paramU.param3ddw.yTop) {
					 if (data2Stream(CONST_qyDataType_short, CONST_qnmCfgId_yTop, (void*)pReq->paramU.param3ddw.yTop, 0, &ptr, &len))goto  errLabel;
				 }
				 if (pReq->paramU.param3ddw.xBottom) {
					 if (data2Stream(CONST_qyDataType_short, CONST_qnmCfgId_xBottom, (void*)pReq->paramU.param3ddw.xBottom, 0, &ptr, &len))goto  errLabel;
				 }
				 if (pReq->paramU.param3ddw.yBottom) {
					 if (data2Stream(CONST_qyDataType_short, CONST_qnmCfgId_yBottom, (void*)pReq->paramU.param3ddw.yBottom, 0, &ptr, &len))goto  errLabel;
				 }


				 break;
			 default:
				 break;
				 }
				


	 
	 //
	 if (pReq->idInfo_imGrp_related.ui64Id) {
		 if (data2Stream(CONST_qyDataType_l64, CONST_qnmCfgId_idInfo_grp_related, (void*)&pReq->idInfo_imGrp_related.ui64Id, sizeof(pReq->idInfo_imGrp_related.ui64Id), &ptr, &len)) goto  errLabel;
	 }


	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}


 int  tmpHandler_stream2PtzControlCmd(  CTX_stream2Data  *  pCtx,  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int							iErr		=	-1;
	 //  p0;
	 PTZ_control_cmd		*	pReq		=	(  PTZ_control_cmd  *  )p1;
	 long							lVal;
	 //  int							index		=  0;

	 
	 if  (  !pReq  )  goto  errLabel;
	 //  if  (  uiStreamId  !=  CONST_imCommType_refreshImObjRulesReq  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );
#if  10
	 switch  (  uiStreamId  )  {
		 case  CONST_imCommType_ptzControlCmd:
			   switch  (  tmp_cfgId  )  {
				       case  CONST_qnmCfgId_start:
						     pReq->uiType  =  uiStreamId;   
							 break;
#if  0
					   case  CONST_qnmCfgId_rawData:
						     pReq->v0260.uiLen  =  sizeof(  pReq->v0260.cmdBuf  );
							 if  (  getFieldData_lData(  pItem,  pReq->v0260.cmdBuf,  &pReq->v0260.uiLen  )  )  goto  errLabel;
							 break;
#endif

							 //  2014/09/13
					   case  CONST_qnmCfgId_uiObjType:
						     if  (  getFieldData_long(  pItem,  (  long  *  )&pReq->cmdInfo.obj.uiObjType  )  )  goto  errLabel;
						     break;
					   case  CONST_qnmCfgId_index:
						     if  (  getFieldData_short(  pItem,  (  short  *  )&pReq->cmdInfo.obj.usIndex_obj  )  )  goto  errLabel;
						     break;
					   case  CONST_qnmCfgId_help_subIndex:  //  2016/07/24
						     if  (  getFieldData_short(  pItem,  (  short  *  )&pReq->cmdInfo.obj.usHelp_subIndex  )  )  goto  errLabel;
						     break;
							 //
					   case  CONST_qnmCfgId_messengerId:
						   if (getFieldData_l64(pItem, (__int64*)&pReq->cmdInfo.idInfo.ui64Id))goto  errLabel;
						   break;
					   case  CONST_qnmCfgId_iChannel:
						     if  (  getFieldData_long(pItem, (long*)&pReq->cmdInfo.iChannel))goto  errLabel;
							 break;
							 //
					   case  CONST_qnmCfgId_nCmd:
						     if  (  getFieldData_char(  pItem,  (  char  *  )&pReq->cmdInfo.ucCmd  )  )  goto  errLabel;
						     break;
					   case  CONST_qnmCfgId_mouseStatus:
						     if  (  getFieldData_char(pItem, (char*)&pReq->cmdInfo.ucMouseStatus))goto  errLabel;
							 break;

					   case  CONST_qnmCfgId_idInfo_grp_related:
						     if (getFieldData_l64(pItem, (__int64*)&pReq->idInfo_imGrp_related.ui64Id))  goto  errLabel;
						     break;

							 


					   default:
							   break;
			   }
			   //
#if  10
			   if (pReq->cmdInfo.ucCmd == CONST_ptzCmd_3ddw) {
				   switch (tmp_cfgId) {
						  case  CONST_qnmCfgId_width:
							  if (getFieldData_short(pItem, (short*)&pReq->paramU.param3ddw.sW_video))  goto  errLabel;
							  break;
						  case  CONST_qnmCfgId_height:
							  if (getFieldData_short(pItem, (short*)&pReq->paramU.param3ddw.sH_video))  goto  errLabel;
							  break;
						  case  CONST_qnmCfgId_xTop:
							  if (getFieldData_short(pItem, (short*)&pReq->paramU.param3ddw.xTop))  goto  errLabel;
							  break;
						  case  CONST_qnmCfgId_yTop:
							  if (getFieldData_short(pItem, (short*)&pReq->paramU.param3ddw.yTop))  goto  errLabel;
							  break;
						  case  CONST_qnmCfgId_xBottom:
							  if (getFieldData_short(pItem, (short*)&pReq->paramU.param3ddw.xBottom))  goto  errLabel;
							  break;
						  case  CONST_qnmCfgId_yBottom:
							  if (getFieldData_short(pItem, (short*)&pReq->paramU.param3ddw.yBottom))  goto  errLabel;
							  break;
						  default:
							  break;



				   }
			   }
#endif 

			   //
			   break;
		 default:
					break;
	 }
#endif
	 iErr  =  0;
errLabel:
	 return  iErr;
}



/////////////


  //  QY_MESSENGER_ACCOUNT
 int  messengerAccount2Stream(  unsigned  int  uiStreamId,  QY_MESSENGER_ACCOUNT  *  pPcInfo,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;
	 unsigned  long		ulIp	=	0;

	 if  (  !pPcInfo  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 //
	 if  (  data2Stream(  CONST_qyDataType_str,  CONST_qnmCfgId_messengerPasswd,  pPcInfo->messengerPasswd,  strlen(  pPcInfo->messengerPasswd  ),  &ptr,  &len  )  )  goto  errLabel;
	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}


 int  tmpHandler_stream2MessengerAccount(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 QY_MESSENGER_ACCOUNT	*	pPcInfo	=	(  QY_MESSENGER_ACCOUNT  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pPcInfo  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_messengerAccount  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );
	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_messengerPasswd:
				   if  (  getFieldData_str(  pItem,  pPcInfo->messengerPasswd,  mycountof(  pPcInfo->messengerPasswd  )  )  )  goto  errLabel;
				   break;
			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}



 //
 int  qisCaReq2Stream(unsigned  int  uiStreamId, QIS_ca_req* pReq, char* buf, unsigned  int* uiBufSize)
 {
	 int				iErr = -1;
	 int				i = 0;
	 char* ptr = buf;
	 unsigned  int		len = *uiBufSize;

	 if (!pReq)  return  -1;
	 if (!buf)  return  -1;

	 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_start, (void*)uiStreamId, 0, &ptr, &len))  goto  errLabel;


	 //
	 if (pReq->ucbResp) {
		 if (data2Stream(CONST_qyDataType_char, CONST_qnmCfgId_ucbResp, (void*)pReq->ucbResp, 0, &ptr, &len))  goto  errLabel;
	 }
	 //  2014/01/31
	 if (pReq->ca_sendDataLen) {	//  
		 if (data2Stream(CONST_qyDataType_data, CONST_qnmCfgId_ca_sendData, (void*)pReq->ca_sendData, pReq->ca_sendDataLen, &ptr, &len))  goto  errLabel;
	 }

	 //
	 if (pReq->ca_servDataLen) {	//  
		 if (data2Stream(CONST_qyDataType_data, CONST_qnmCfgId_sxrz_servReply, (void*)pReq->ca_servData, pReq->ca_servDataLen, &ptr, &len))  goto  errLabel;
	 }

	 //
	 if (pReq->ca_cliDataLen) {
		 if (data2Stream(CONST_qyDataType_data, CONST_qnmCfgId_sxrz_cliData, (void*)pReq->ca_cliData, pReq->ca_cliDataLen, &ptr, &len))  goto  errLabel;
	 }

	 //
	 if (pReq->sHgCmd) {
		 if (data2Stream(CONST_qyDataType_short, CONST_qnmCfgId_sHgCmd, (void*)pReq->sHgCmd, 0, &ptr, &len))  goto  errLabel;

	 }

	 //
	 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_null, 0, 0, &ptr, &len))  goto  errLabel;

	 iErr = 0;
 errLabel:
	 if (!iErr) {
		 *uiBufSize = *uiBufSize - len;
	 }
	 return  iErr;
 }



 int  tmpHandler_stream2QisCaReq(CTX_stream2Data* pCtx, void* p0, void* p1, unsigned  int  uiStreamId, QY_CFGITEM_ntoh_U* pItem)
 {
	 int						iErr = -1;
	 //  p0;
	 QIS_ca_req* pReq = (QIS_ca_req*)p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;

	 if (!pReq)  goto  errLabel;

	 //

	 //
	 unsigned  short  tmp_cfgId;
	 memcpy(&tmp_cfgId, &pItem->head.cfgId, sizeof(short));

	 switch (uiStreamId) {
	 case  CONST_imCommType_qisCaReq:

		 switch (tmp_cfgId) {
		 case  CONST_qnmCfgId_start:  //  2017/07/26
			 pReq->uiType = uiStreamId;
			 break;

			 //			 
		 case  CONST_qnmCfgId_ucbResp:
			 if (getFieldData_char(pItem, (char*)&pReq->ucbResp)) goto  errLabel;
			 break;
		 case  CONST_qnmCfgId_ca_sendData:
			 pReq->ca_sendDataLen = sizeof(pReq->ca_sendData);
			 if (getFieldData_data(pItem, pReq->ca_sendData, &pReq->ca_sendDataLen))  goto  errLabel;
			 break;

			 //
		 case  CONST_qnmCfgId_sxrz_servReply:
			 pReq->ca_servDataLen = sizeof(pReq->ca_servData);
			 if (getFieldData_data(pItem, pReq->ca_servData, &pReq->ca_servDataLen))  goto  errLabel;
			 break;
		 case  CONST_qnmCfgId_sxrz_cliData:
			 pReq->ca_cliDataLen = sizeof(pReq->ca_cliData);
			 if (getFieldData_data(pItem, pReq->ca_cliData, &pReq->ca_cliDataLen))goto  errLabel;
			 break;

			 //
		 case  CONST_qnmCfgId_sHgCmd:
			 if (getFieldData_short(pItem, &pReq->sHgCmd))  goto  errLabel;
			 break;

			 //
		 default:
			 break;

		 }
		 break;
	 default:
		 break;
	 }

	 iErr = 0;
 errLabel:
	 return  iErr;
 }


 ///////////////////////

 //
 int  refreshImObjMemInfo2Stream(unsigned  int  uiStreamId, RefreshImObjMemInfo* pReq, char* buf, unsigned  int* uiBufSize)
 {
	 int				iErr = -1;
	 int				i = 0;
	 char* ptr = buf;
	 unsigned  int		len = *uiBufSize;

	 if (!pReq)  return  -1;
	 if (!buf)  return  -1;

	 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_start, (void*)uiStreamId, 0, &ptr, &len))  goto  errLabel;


	 //
	 if (pReq->usOp) {
		 if (data2Stream(CONST_qyDataType_short, CONST_qnmCfgId_usOp, &pReq->usOp, 0, &ptr, &len))goto  errLabel;
	 }

	 //
	 if (data2Stream(CONST_qyDataType_long, CONST_qnmCfgId_null, 0, 0, &ptr, &len))  goto  errLabel;

	 iErr = 0;
 errLabel:
	 if (!iErr) {
		 *uiBufSize = *uiBufSize - len;
	 }
	 return  iErr;
 }



 int  tmpHandler_stream2RefreshImObjMemInfo(CTX_stream2Data* pCtx, void* p0, void* p1, unsigned  int  uiStreamId, QY_CFGITEM_ntoh_U* pItem)
 {
	 int						iErr = -1;
	 //  p0;
	 RefreshImObjMemInfo* pReq = (RefreshImObjMemInfo*)p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;

	 if (!pReq)  goto  errLabel;

	 //

	 //
	 unsigned  short  tmp_cfgId;
	 memcpy(&tmp_cfgId, &pItem->head.cfgId, sizeof(short));

	 switch (uiStreamId) {
	 case  CONST_imCommType_refreshImObjMemInfo:

		 switch (tmp_cfgId) {
		 case  CONST_qnmCfgId_start:  //  2017/07/26
			 pReq->uiType = uiStreamId;
			 break;

			 //			 

			 //
		 case  CONST_qnmCfgId_usOp:
			 if (getFieldData_short(pItem, (short*) & pReq->usOp))  goto  errLabel;
			 break;

			 //
		 default:
			 break;

		 }
		 break;
	 default:
		 break;
	 }

	 iErr = 0;
 errLabel:
	 return  iErr;
 }





///


 int  imGrpEx2Stream(  unsigned  int  uiStreamId,  IM_GRP_EX  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pReq->common.name[0]  )  {
         if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_hint, pReq->common.name,  lstrlen(  pReq->common.name  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //  2014/01/31
	 if  (  pReq->common.usSubtype  )  {	//  
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_subtype,  (  void  *  )pReq->common.usSubtype,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //
	 if  (  pReq->common.idInfo.ui64Id  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  &pReq->common.idInfo,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //
	 if  (  pReq->usOp  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usOp,  (  void  *  )pReq->usOp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }


	 //
	 if  (  pReq->usCnt  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt,  (  void  *  )pReq->usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;
		 //
		 for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {			 		  

			  //
			  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_mem,  0,  &ptr,  &len  )  )  goto  errLabel;
		
			  if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  (  void  *  )&pReq->mems[i].grpMmem_idInfo.ui64Id,  0,  &ptr,  &len  )  )  goto  errLabel;
			  
			  //				
			  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }

	 }
	 
	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}



 int  tmpHandler_stream2ImGrpEx(  CTX_stream2Data  *  pCtx,  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 IM_GRP_EX			*	pGrpInfo	=	(  IM_GRP_EX  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pGrpInfo  )  goto  errLabel;

	 //
	 IM_GRP_EX* pReq;  pReq = pGrpInfo;

	 //
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
			 case  CONST_imCommType_imGrp:
			 case  CONST_imCommType_refreshImGrp:

				   switch  (  tmp_cfgId  )  {			 
						   case  CONST_qnmCfgId_start:  //  2017/07/26
			       			     pGrpInfo->common.uiType  =  uiStreamId;   
				   				 break;
				   
								 //			 
						   case  CONST_qnmCfgId_hint:				   
							     if  (  getFieldData_wStr(  pItem,  pGrpInfo->common.name,  mycountof(  pGrpInfo->common.name  )  )  )  goto  errLabel;
				   				 break;
				   
								 //
			 			   case  CONST_qnmCfgId_subtype:	//  2014/01/31
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pGrpInfo->common.usSubtype  )  )  goto  errLabel;
								 break;
			
								 //
			 			   case  CONST_qnmCfgId_messengerId:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pGrpInfo->common.idInfo.ui64Id  )  )  goto  errLabel;
								 break;	
								 //
						   case  CONST_qnmCfgId_usOp:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pGrpInfo->usOp  )  )  goto  errLabel;
							     break;
								 //
						   case  CONST_qnmCfgId_usCnt:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pGrpInfo->usCnt  )  )  goto  errLabel;
								 //
								 if  (  pGrpInfo->usCnt  >  mycountof(  pReq->mems  )  )  goto  errLabel;
								 //							   
								 break;
								 //
						   default:					
								   break;
	 
				   }
				   break;
			 case  CONST_imCommType_mem:  {
				   ImGrpEx_mem  *  pMem  =  0;
				   //
				   if  (  pReq->tmpInternal.usCnt_mems  >=  mycountof(  pReq->mems  )  )  {
					   traceLogA(  (char*)  "tmpHandler_stream2RetrieveImGrpListResp: failed"  );  
					   goto  errLabel;
				   }
				   //
				   pMem  =  &pReq->mems[pReq->tmpInternal.usCnt_mems];				   
				   //
				   switch  (  tmp_cfgId  )  {					   
						   case  CONST_qnmCfgId_messengerId:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pMem->grpMmem_idInfo.ui64Id  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_null:
							     pReq->tmpInternal.usCnt_mems  ++  ;
							     break;
						   default:
								   break;
				   }				  
				   }
				   break;
			 default:
					break;
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
}










 //
 int  retrieveImObjListReq2Stream(  unsigned  int  uiStreamId,  RETRIEVE_IMOBJLIST_REQ  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	int					iErr	=	-1;
	char		*		ptr		=	buf;
	unsigned  int		len		=	*uiBufSize;

	if  (  !pReq  )  return  -1;

	if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	if  (  pReq->usMaxContactUpdateInfosPerSnd  )  {
		if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usMaxMemsPerSnd,  (  void  *  )pReq->usMaxContactUpdateInfosPerSnd,  0,  &ptr,  &len  )  )  goto  errLabel;
	}
	if  (  pReq->tLastRefreshedTime_contactList_misServ  )  {
		if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tLastRefreshedTime,  (  void  *  )&pReq->tLastRefreshedTime_contactList_misServ,  sizeof(  pReq->tLastRefreshedTime_contactList_misServ  ),  &ptr,  &len  )  )  goto  errLabel;
	}
	if  (  pReq->ucbNext  )  {
		if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbNext,  (  void  *  )pReq->ucbNext,  0,  &ptr,  &len  )  )  goto  errLabel;
	}
	if  (  pReq->idInfo_grp_lastRefreshed.ui64Id  )  {
		if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_grp_lastRefreshed,  (  void  *  )&pReq->idInfo_grp_lastRefreshed.ui64Id,  sizeof(  pReq->idInfo_grp_lastRefreshed.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
	}
	if  (  pReq->idInfo_lastRefreshed.ui64Id  )  {
		if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_lastRefreshed,  (  void  *  )&pReq->idInfo_lastRefreshed.ui64Id,  sizeof(  pReq->idInfo_lastRefreshed.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
	}

	//
	if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
     
	iErr  =  0;
errLabel:
	if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	}
	return  iErr;	 
}


 int  tmpHandler_stream2RetrieveImObjListReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 RETRIEVE_IMOBJLIST_REQ	*	pReq		=	(  RETRIEVE_IMOBJLIST_REQ  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pReq  )  goto  errLabel;
	 
	 switch  (  uiStreamId  )  {
			 case  CONST_imCommType_retrieveImGrpListReq:
			 case  CONST_imCommType_retrieveImGrpMemListReq:
			 case  CONST_imCommType_retrieveContactListReq:
			 case  CONST_imCommType_retrieveImObjListEndReq:
			 case  CONST_imCommType_retrieveWebContactListReq:
				   break;
			 default:
				     traceLogA(  (char*)  "tmpHandler_stream2RetrieveImObjListReq: unknown uiStreamId: %d",  uiStreamId  );
				     goto  errLabel;
	 }

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_start:
				   pReq->uiType  =  uiStreamId;
				   break;
			 case  CONST_qnmCfgId_usMaxMemsPerSnd:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pReq->usMaxContactUpdateInfosPerSnd  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_tLastRefreshedTime:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pReq->tLastRefreshedTime_contactList_misServ  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_ucbNext:
				   if  (  getFieldData_char(  pItem,  (  char  *  )&pReq->ucbNext  )  )  goto  errLabel;				   
				   break;
			 case  CONST_qnmCfgId_idInfo_grp_lastRefreshed:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pReq->idInfo_grp_lastRefreshed.ui64Id  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_idInfo_lastRefreshed:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pReq->idInfo_lastRefreshed.ui64Id  )  )  goto  errLabel;
				   break;
			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}




 int  retrieveImGrpListResp2Stream(  unsigned  int  uiStreamId,  RETRIEVE_IMGRPLIST_RESP  *  pUpdateInfos,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pUpdateInfos  )  return  -1;
	 if  (  !buf  )  return  -1;
	 //
	 if  (  pUpdateInfos->usCnt  >  mycountof(  pUpdateInfos->mems  )  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 if  (  pUpdateInfos->idInfo_lastRefreshed.ui64Id  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_lastRefreshed,  &pUpdateInfos->idInfo_lastRefreshed.ui64Id,  sizeof(  pUpdateInfos->idInfo_lastRefreshed.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
	 }		 	 

	 if  (  pUpdateInfos->ucbEnd  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbEnd,  (  void  *  )pUpdateInfos->ucbEnd,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pUpdateInfos->usCnt  )  {
	 	   //
	 	   if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt,  (  void  *  )pUpdateInfos->usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;

		   //
		   for  (  i  =  0;  i  <  pUpdateInfos->usCnt;  i  ++  )  {
			    //  ÏÂÃæ½«Ò»¸öQY_MESSENGER_REGINFO×ª»»³ÉÁ÷
			    IM_GRP_INFO  *  pRegInfo	=	&pUpdateInfos->mems[i];
		  
				if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_mem,  0,  &ptr,  &len  )  )  goto  errLabel;

				if  (  pRegInfo->idInfo.ui64Id  )  {
					if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  (  void  *  )&pRegInfo->idInfo.ui64Id,  sizeof(  pRegInfo->idInfo.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
				}
				if  (  pRegInfo->name[0]  )  {
					if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_hint, pRegInfo->name,  lstrlen(  pRegInfo->name  ),  &ptr,  &len  )  )  goto  errLabel;
				}
				
				//  2014/01/31
				if  (  pRegInfo->usSubtype  )  {
					if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_subtype,  (  void  *  )pRegInfo->usSubtype,  0,  &ptr,  &len  )  )  goto  errLabel;
				}

				//  2017/07/26
				if  (  pRegInfo->idInfo_creator.ui64Id  )  {
					if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_creator,  (  void  *  )&pRegInfo->idInfo_creator.ui64Id,  sizeof(  pRegInfo->idInfo_creator.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
				}

				//
				if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
		   }
	 }

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
     
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}

 int  tmpHandler_stream2RetrieveImGrpListResp(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int							iErr		=	-1;
	 //  p0;
	 RETRIEVE_IMGRPLIST_RESP	*	pResp		=	(  RETRIEVE_IMGRPLIST_RESP  *  )p1;
	 //  QY_CFGITEM					*	pItem		=	(  QY_CFGITEM  *  )p2;
	 
	 if  (  !pResp  )  goto  errLabel;
	 	 
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
		     case  CONST_imCommType_retrieveImGrpListResp:
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_start:
							     pResp->uiType  =  uiStreamId;
							     break;
					   	   case  CONST_qnmCfgId_ucbEnd:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pResp->ucbEnd  )  )  goto  errLabel;
								 break;
						   //
						   case  CONST_qnmCfgId_idInfo_lastRefreshed:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pResp->idInfo_lastRefreshed.ui64Id  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_usCnt:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pResp->usCnt  )  )  goto  errLabel;
								 //
								 if  (  pResp->usCnt  >  mycountof(  pResp->mems  )  )  goto  errLabel;
							     break;					
						   default:
								  break;
				   }				 
				   break;
			 case  CONST_imCommType_mem:  {
				   IM_GRP_INFO  *  pMem		=	NULL;
				   //
				   if  (  pResp->index  >=  mycountof(  pResp->mems  )  )  {
					   traceLogA(  (char*)  "tmpHandler_stream2RetrieveImGrpListResp: failed"  );  goto  errLabel;
				   }
				   //
				   pMem  =  &pResp->mems[pResp->index];				   
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_messengerId:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pMem->idInfo.ui64Id  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_hint:
							     if  (  getFieldData_wStr(  pItem,  pMem->name,  mycountof(  pMem->name  )  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_subtype:	//  2014/01/31
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pMem->usSubtype  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_idInfo_creator:	//  2017/07/27
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pMem->idInfo_creator.ui64Id  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_null:
							     pResp->index  ++  ;
							     break;
						   default:
									break;
				   }
				   //
				   }
				   break;
			 default:
					break;
	 }	 

	 iErr  =  0;
errLabel:
	 if  (  iErr  )  {
		 traceLogA(  (char*)  "tmpHandler_stream2RetrieveImGrpListResp: failed"  );
	 }
	 return  iErr;
}


 /////////////////////

 int  retrieveImGrpMemListResp2Stream(  unsigned  int  uiStreamId,  RETRIEVE_IMGRPMEMLIST_RESP  *  pUpdateInfos,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pUpdateInfos  )  return  -1;
	 if  (  !buf  )  return  -1;
	 //
	 if  (  pUpdateInfos->usCnt  >  mycountof(  pUpdateInfos->mems  )  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 if  (  pUpdateInfos->idInfo_grp_lastRefreshed.ui64Id  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_grp_lastRefreshed,  &pUpdateInfos->idInfo_grp_lastRefreshed.ui64Id,  sizeof(  pUpdateInfos->idInfo_grp_lastRefreshed.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pUpdateInfos->idInfo_lastRefreshed.ui64Id  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_lastRefreshed,  &pUpdateInfos->idInfo_lastRefreshed.ui64Id,  sizeof(  pUpdateInfos->idInfo_lastRefreshed.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
	 }		 	 

	 if  (  pUpdateInfos->ucbEnd  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbEnd,  (  void  *  )pUpdateInfos->ucbEnd,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pUpdateInfos->usCnt  )  {
	 	   //
	 	   if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt,  (  void  *  )pUpdateInfos->usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;

		   //
		   for  (  i  =  0;  i  <  pUpdateInfos->usCnt;  i  ++  )  {
			    //  ÏÂÃæ½«Ò»¸öQY_MESSENGER_REGINFO×ª»»³ÉÁ÷
			    IM_GRP_MEM  *  pRegInfo	=	&pUpdateInfos->mems[i];
		  
				if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_mem,  0,  &ptr,  &len  )  )  goto  errLabel;

				if  (  pRegInfo->idInfo_grp.ui64Id  )  {
					if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_grp1,  (  void  *  )&pRegInfo->idInfo_grp.ui64Id,  sizeof(  pRegInfo->idInfo_grp.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
				}
				if  (  pRegInfo->idInfo_mem.ui64Id  )  {
					if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  (  void  *  )&pRegInfo->idInfo_mem.ui64Id,  sizeof(  pRegInfo->idInfo_mem.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
				}
				if  (  pRegInfo->iRole  )  {
					if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_iRole,  (  void  *  )pRegInfo->iRole,  0,  &ptr,  &len  )  )  goto  errLabel;
				}
				
				if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
		   }
	 }

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
     
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}

 int  tmpHandler_stream2RetrieveImGrpMemListResp(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int							iErr		=	-1;
	 //  p0;
	 RETRIEVE_IMGRPMEMLIST_RESP	*	pResp		=	(  RETRIEVE_IMGRPMEMLIST_RESP  *  )p1;
	 //  QY_CFGITEM					*	pItem		=	(  QY_CFGITEM  *  )p2;
	 
	 if  (  !pResp  )  goto  errLabel;
	 	 
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
		     case  CONST_imCommType_retrieveImGrpMemListResp:
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_start:
							     pResp->uiType  =  uiStreamId;
							     break;
					   	   case  CONST_qnmCfgId_ucbEnd:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pResp->ucbEnd  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_idInfo_grp_lastRefreshed:
   							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pResp->idInfo_grp_lastRefreshed.ui64Id  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_idInfo_lastRefreshed:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pResp->idInfo_lastRefreshed.ui64Id  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_usCnt:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pResp->usCnt  )  )  goto  errLabel;
								 //
								 if  (  pResp->usCnt  >  mycountof(  pResp->mems  )  )  goto  errLabel;
							     break;					
						   default:
								  break;
				   }				 
				   break;
			 case  CONST_imCommType_mem:  {
				   IM_GRP_MEM  *  pMem		=	NULL;
				   //
				   if  (  pResp->index  >=  mycountof(  pResp->mems  )  )  {
					   traceLogA(  (char*)  "tmpHandler_stream2RetrieveImGrpListResp: failed"  );  goto  errLabel;
				   }
				   //
				   pMem  =  &pResp->mems[pResp->index];				   
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_idInfo_grp1:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pMem->idInfo_grp.ui64Id  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_messengerId:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pMem->idInfo_mem.ui64Id  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_iRole:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->iRole  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_null:
							     pResp->index  ++  ;
							     break;
						   default:
									break;
				   }
				   //
				   }
				   break;
			 default:
					break;
	 }	 

	 iErr  =  0;
errLabel:
	 if  (  iErr  )  {
		 traceLogA(  (char*)  "tmpHandler_stream2RetrieveImGrpMemListResp: failed"  );
	 }
	 return  iErr;
}



  int  retrieveContactListResp2Stream(  unsigned  int  uiStreamId,  RETRIEVE_CONTACTLIST_RESP  *  pUpdateInfos,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;
	 int				j;

	 if  (  !pUpdateInfos  )  return  -1;
	 if  (  !buf  )  return  -1;
	 //
	 if  (  pUpdateInfos->usCnt  >  mycountof(  pUpdateInfos->mems  )  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 if  (  pUpdateInfos->idInfo_lastRefreshed.ui64Id  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_lastRefreshed,  &pUpdateInfos->idInfo_lastRefreshed.ui64Id,  sizeof(  pUpdateInfos->idInfo_lastRefreshed.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
	 }		 	 

	 if  (  pUpdateInfos->ucbEnd  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbEnd,  (  void  *  )pUpdateInfos->ucbEnd,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pUpdateInfos->usCnt  )  {
	 	   //
	 	   if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt,  (  void  *  )pUpdateInfos->usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;
		   //
		   for  (  i  =  0;  i  <  pUpdateInfos->usCnt;  i  ++  )  {
			    //  ÏÂÃæ½«Ò»¸öQY_MESSENGER_REGINFO×ª»»³ÉÁ÷
			    RETRIEVE_contact_mem  *  pMem  =  &pUpdateInfos->mems[i];
			    QY_MESSENGER_REGINFO  *  pRegInfo	=	&pMem->regInfo;
		  
				if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_mem,  0,  &ptr,  &len  )  )  goto  errLabel;

				if  (  pRegInfo->addr.uiObjType  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiObjType,  (  void  *  )pRegInfo->addr.uiObjType,  0,  &ptr,  &len  )  )  goto  errLabel;	//  2008/01/31
				if  (  pRegInfo->addr.idInfo.ui64Id  &&  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  (  void  *  )&pRegInfo->addr.idInfo.ui64Id,  sizeof(  pRegInfo->addr.idInfo.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
				//
				if  (  pMem->iRole  )  {  //  2017/08/14
					if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_iRole,  (  void  *  )pMem->iRole,  0,  &ptr,  &len  )  )  goto  errLabel;
				}
				//
				if  (  pRegInfo->addr.uiDevType  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiDevType_from,  (  void  *  )pRegInfo->addr.uiDevType,  0,  &ptr,  &len  )  )  goto  errLabel;
				//
				//if  (  pRegInfo->addr.wDevIdStr[0]  &&  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_wDevIdStr_from,  pRegInfo->addr.wDevIdStr,  lstrlen(  pRegInfo->addr.wDevIdStr  ),  &ptr,  &len  )  )  goto  errLabel;	//  2008/01/31

				//
				for  (  j  =  0;  j  <  mycountof(  pRegInfo->uiFieldIds  );  j  ++  )  {
					 if  (  !pRegInfo->u.cols[j][0]  )  continue;
					 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiFieldId,  (  void  *  )pRegInfo->uiFieldIds[j],  0,  &ptr,  &len  )  )  goto  errLabel;
					 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_hint,  pRegInfo->u.cols[j],  lstrlen(  pRegInfo->u.cols[j]  ),  &ptr,  &len  )  )  goto  errLabel;
				}		 
		  
				if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
		   }
	 }

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
     
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}


 int  tmpHandler_stream2RetrieveContactListResp(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int							iErr		=	-1;
	 //  p0;
	 RETRIEVE_CONTACTLIST_RESP	*	pResp		=	(  RETRIEVE_CONTACTLIST_RESP  *  )p1;
	 //  QY_CFGITEM					*	pItem		=	(  QY_CFGITEM  *  )p2;
	 long							lVal;
	 
	 if  (  !pResp  )  goto  errLabel;
	 	 
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
		     case  CONST_imCommType_retrieveContactListResp:
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_start:
							     pResp->uiType  =  uiStreamId;
							     break;
					   	   case  CONST_qnmCfgId_ucbEnd:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pResp->ucbEnd  )  )  goto  errLabel;
								 break;
						   //
						   case  CONST_qnmCfgId_idInfo_lastRefreshed:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pResp->idInfo_lastRefreshed.ui64Id  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_usCnt:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pResp->usCnt  )  )  goto  errLabel;
								 //
								 if  (  pResp->usCnt  >  mycountof(  pResp->mems  )  )  goto  errLabel;
							     break;					
						   default:
								  break;
				   }				 
				   break;
			 case  CONST_imCommType_mem:  {
				   RETRIEVE_contact_mem  *  pMem  =  NULL;
				   //
				   if  (  pResp->index  >=  mycountof(  pResp->mems  )  ||  pResp->iFiledIndex  >=  mycountof(  pResp->mems[0].regInfo.uiFieldIds  )  )  {
					   traceLogA(  (char*)  "tmpHandler_stream2RetrieveContactListResp: failed"  );  
					   goto  errLabel;
				   }
				   //
				   pMem  =  &pResp->mems[pResp->index];				   
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_uiObjType:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->regInfo.addr.uiObjType  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_messengerId:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pMem->regInfo.addr.idInfo.ui64Id  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_iRole:	//  2017/08.14
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->iRole  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_uiDevType_from:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->regInfo.addr.uiDevType  )  )  goto  errLabel;
							     break;
#if  0
						   case  CONST_qnmCfgId_wDevIdStr_from:
							     if  (  getFieldData_wStr(  pItem,  pMem->regInfo.addr.wDevIdStr,  mycountof(  pMem->regInfo.addr.wDevIdStr  )  )  )  goto  errLabel;
							     break;
#endif 
					       case  CONST_qnmCfgId_uiFieldId:
				   			     if  (  getFieldData_long(  pItem,  &lVal  )  )  goto  errLabel;
								 pMem->regInfo.uiFieldIds[pResp->iFiledIndex]  =  lVal;
								 break;
						   case  CONST_qnmCfgId_hint:
							     if  (  getFieldData_wStr(  pItem,  pMem->regInfo.u.cols[pResp->iFiledIndex],  mycountof(  pMem->regInfo.u.cols[pResp->iFiledIndex]  )  )  )  goto  errLabel;
								 pResp->iFiledIndex  ++  ;
								 break;
						   case  CONST_qnmCfgId_null:
							     pResp->index  ++  ;
							     pResp->iFiledIndex  =  0;
							     break;
						   default:
									break;
				   }
				   //
				   }
				   break;
			 default:
					break;
	 }	 

	 iErr  =  0;
errLabel:
	 if  (  iErr  )  {
		 traceLogA(  (char*)  "tmpHandler_stream2RetrieveContactListResp: failed"  );
	 }
	 return  iErr;
}

////////////////////

 /*
 				 unsigned  int										uiType;
				 //
				 __int64											tLastRefreshedTime_contactList_misServ;		//  ·¢ËÍ¸ø¿Í»§¶ËÈÃÖªµÀÊÇ´ÓÊ²Ã´Ê±¼ä¿ªÊ¼Ë¢ÐÂµÄ
				 */

 int  retrieveImObjListEndResp2Stream(  unsigned  int  uiStreamId,  RETRIEVE_IMOBJLISTEND_RESP  *  pResp,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pResp  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pResp->tLastRefreshedTime_contactList_misServ  )  {
		if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tLastRefreshedTime,  (  void  *  )&pResp->tLastRefreshedTime_contactList_misServ,  sizeof(  pResp->tLastRefreshedTime_contactList_misServ  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}



 int  tmpHandler_stream2RetrieveImObjListEndResp(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int									iErr		=	-1;
	 //  p0;
	 RETRIEVE_IMOBJLISTEND_RESP			*	pResp		=	(  RETRIEVE_IMOBJLISTEND_RESP  *  )p1;
	 //  QY_CFGITEM							*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pResp  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_retrieveImObjListEndResp  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_start:
				   pResp->uiType  =  uiStreamId;
				   break;
			 case  CONST_qnmCfgId_tLastRefreshedTime:
				   if  (  getFieldData_l64(  pItem,  &pResp->tLastRefreshedTime_contactList_misServ  )  )  goto  errLabel;
				   break;
			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}




/////////////////

  int  retrieveCustomerServiceObjListReq2Stream(  unsigned  int  uiStreamId,  RETRIEVE_customerServiceObjList_req  *  pUpdateInfos,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pUpdateInfos  )  return  -1;
	 if  (  !buf  )  return  -1;
	 //
	 if  (  pUpdateInfos->usCnt  >  mycountof(  pUpdateInfos->mems  )  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 if  (  pUpdateInfos->ucbResp  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbResp,  (  void  *  )pUpdateInfos->ucbResp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pUpdateInfos->usCnt  )  {
	 	   //
	 	   if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt,  (  void  *  )pUpdateInfos->usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;
		   //
		   for  (  i  =  0;  i  <  pUpdateInfos->usCnt;  i  ++  )  {
			    //  ÏÂÃæ½«Ò»¸öQY_MESSENGER_REGINFO×ª»»³ÉÁ÷
			    CUSTOMER_service_obj  *  pRegInfo	=	&pUpdateInfos->mems[i];
		  
				if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_mem,  0,  &ptr,  &len  )  )  goto  errLabel;

				if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  (  void  *  )&pRegInfo->idInfo.ui64Id,  sizeof(  pRegInfo->idInfo.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
				//
				if  (  pRegInfo->uiLangId  )  {
					if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_langId,  (  void  *  )pRegInfo->uiLangId,  0,  &ptr,  &len  )  )  goto  errLabel;
				}
				if  (  pRegInfo->uiCategoryId  )  {
					if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_categoryId,  (  void  *  )pRegInfo->uiCategoryId,  0,  &ptr,  &len  )  )  goto  errLabel;
				}
				if  (  pRegInfo->displayName[0]  &&  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_displayName,  pRegInfo->displayName,  lstrlen(  pRegInfo->displayName  ),  &ptr,  &len  )  )  goto  errLabel;
		  
				if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
		   }
	 }

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
     
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}


 int  tmpHandler_stream2RetrieveCustomerServiceObjListReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int							iErr		=	-1;
	 //  p0;
	 RETRIEVE_customerServiceObjList_req	*	pResp		=	(  RETRIEVE_customerServiceObjList_req  *  )p1;
	 //  QY_CFGITEM					*	pItem		=	(  QY_CFGITEM  *  )p2;
	 
	 if  (  !pResp  )  goto  errLabel;
	 	 
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
		     case  CONST_imCommType_retrieveCustomerServiceObjListReq:
				   switch  (  tmp_cfgId  )  { 
						   case  CONST_qnmCfgId_start:
							     pResp->uiType  =  uiStreamId;   
								 break;
						   case  CONST_qnmCfgId_ucbResp:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pResp->ucbResp  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_usCnt:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pResp->usCnt  )  )  goto  errLabel;
								 //
								 if  (  pResp->usCnt  >  mycountof(  pResp->mems  )  )  goto  errLabel;
							     break;					
						   default:
								  break;
				   }				 
				   break;
			 case  CONST_imCommType_mem:  {
				   CUSTOMER_service_obj  *  pMem		=	NULL;
				   //
				   if  (  pResp->index  >=  mycountof(  pResp->mems  )  )  {
					   traceLogA(  (char*)  "tmpHandler_stream2RetrieveCustomerServiceObjListResp: failed"  );  goto  errLabel;
				   }

				   //
				   pMem  =  &pResp->mems[pResp->index];				   
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_messengerId:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pMem->idInfo.ui64Id  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_langId:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->uiLangId  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_categoryId:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->uiCategoryId  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_displayName:
							     if  (  getFieldData_wStr(  pItem,  pMem->displayName,  mycountof(  pMem->displayName  )  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_null:
							     pResp->index  ++  ;
							     break;
						   default:
									break;
				   }
				   //
				   }
				   break;
			 default:
					break;
	 }	 

	 iErr  =  0;
errLabel:
	 if  (  iErr  )  {
		 traceLogA(  (char*)  "tmpHandler_stream2RetrieveCustomerServiceOfficerListResp: failed"  );
	 }
	 return  iErr;
}


 ////////////
 int  queryCustomerServiceOfficerReq2Stream(  unsigned  int  uiStreamId,  QUERY_customerServiceOfficer_req  *  pUpdateInfos,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pUpdateInfos  )  return  -1;
	 if  (  !buf  )  return  -1;
	 //

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 if  (  pUpdateInfos->ucbResp  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbResp,  (  void  *  )pUpdateInfos->ucbResp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pUpdateInfos->talkerDesc[0]  &&  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_talkerDesc,  pUpdateInfos->talkerDesc,  lstrlen(  pUpdateInfos->talkerDesc  ),  &ptr,  &len  )  )  goto  errLabel;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
     
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}


 int  tmpHandler_stream2QueryCustomerServiceOfficerReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int							iErr		=	-1;
	 //  p0;
	 QUERY_customerServiceOfficer_req	*	pResp		=	(  QUERY_customerServiceOfficer_req  *  )p1;
	 //  QY_CFGITEM					*	pItem		=	(  QY_CFGITEM  *  )p2;
	 
	 if  (  !pResp  )  goto  errLabel;
	 	 
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
		     case  CONST_imCommType_queryCustomerServiceOfficerReq:
				   switch  (  tmp_cfgId  )  { 
						   case  CONST_qnmCfgId_start:
							     pResp->uiType  =  uiStreamId;   
								 break;
						   case  CONST_qnmCfgId_ucbResp:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pResp->ucbResp  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_talkerDesc:
							     if  (  getFieldData_wStr(  pItem,  pResp->talkerDesc,  mycountof(  pResp->talkerDesc  )  )  )  goto  errLabel;
							     break;
						   default:
								  break;
				   }				 
				   break;
			 default:
					break;
	 }	 

	 iErr  =  0;
errLabel:
	 if  (  iErr  )  {
		 traceLogA(  (char*)  "tmpHandler_stream2QueryCustomerServiceOfficerResp: failed"  );
	 }
	 return  iErr;
}

 int  queryCustomerServiceOfficerReplyReq2Stream(  unsigned  int  uiStreamId,  QUERY_customerServiceOfficer_replyReq  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;
	 //

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pReq->tStartTime_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tStartTime_org,  &pReq->tStartTime_org,  sizeof(  pReq->tStartTime_org  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->uiTranNo_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_org,  (  void  *  )pReq->uiTranNo_org,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pReq->talkerDesc[0]  &&  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_talkerDesc,  pReq->talkerDesc,  lstrlen(  pReq->talkerDesc  ),  &ptr,  &len  )  )  goto  errLabel;


	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
     
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}


 int  tmpHandler_stream2QueryCustomerServiceOfficerReplyReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int							iErr		=	-1;
	 //  p0;
	 QUERY_customerServiceOfficer_replyReq	*	pResp		=	(  QUERY_customerServiceOfficer_replyReq  *  )p1;
	 //  QY_CFGITEM					*	pItem		=	(  QY_CFGITEM  *  )p2;
	 
	 if  (  !pResp  )  goto  errLabel;
	 	 
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
		     case  CONST_imCommType_queryCustomerServiceOfficerReplyReq:
				   switch  (  tmp_cfgId  )  { 
						   case  CONST_qnmCfgId_start:
							     pResp->uiType  =  uiStreamId;   
								 break;
						   case  CONST_qnmCfgId_tStartTime_org:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pResp->tStartTime_org  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_uiTranNo_org:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pResp->uiTranNo_org  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_talkerDesc:
							     if  (  getFieldData_wStr(  pItem,  pResp->talkerDesc,  mycountof(  pResp->talkerDesc  )  )  )  goto  errLabel;
							     break;
						   default:
								  break;
				   }				 
				   break;
			 default:
					break;
	 }	 

	 iErr  =  0;
errLabel:
	 if  (  iErr  )  {
		 traceLogA(  (char*)  "tmpHandler_stream2QueryCustomerServiceOfficerReplyReq: failed"  );
	 }
	 return  iErr;
}

//////////////






 int  transferGpsInfo2Stream(  unsigned  int  uiStreamId,  TRANSFER_GPS_INFO  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;
	 //

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;


	 if  (  pReq->ucbResp  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbResp,  (  void  *  )pReq->ucbResp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pReq->uiTaskType  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTaskType,  (  void  *  )pReq->uiTaskType,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }



	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
     
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}


 int  tmpHandler_stream2TransferGpsInfo(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int							iErr		=	-1;
	 //  p0;
	 TRANSFER_GPS_INFO				*	pContent		=	(  TRANSFER_GPS_INFO  *  )p1;
	 //  QY_CFGITEM					*	pItem		=	(  QY_CFGITEM  *  )p2;
	 
	 if  (  !pContent  )  goto  errLabel;
	 	 
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
		     case  CONST_imCommType_transferGpsInfo:
				   switch  (  tmp_cfgId  )  { 
						   case  CONST_qnmCfgId_start:
							     pContent->uiType  =  uiStreamId;   
								 break;
						   case  CONST_qnmCfgId_ucbResp:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->ucbResp  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_uiTaskType:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiTaskType  )  )  goto  errLabel;
								 break;
						   default:
								  break;
				   }				 
				   break;
			 default:
					break;
	 }	 

	 iErr  =  0;
errLabel:
	 if  (  iErr  )  {
		 traceLogA(  (char*)  "tmpHandler_stream2TransferGpsInfo: failed"  );
	 }
	 return  iErr;
}



 int  transferGpsReplyInfo2Stream(  unsigned  int  uiStreamId,  TRANSFER_GPS_replyInfo  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;
	 //

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;


	 if  (  pReq->usOp  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usOp,  (  void  *  )pReq->usOp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->tStartTime_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tStartTime_org,  &pReq->tStartTime_org,  sizeof(  pReq->tStartTime_org  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->uiTranNo_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_org,  (  void  *  )pReq->uiTranNo_org,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
     
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}


 int  tmpHandler_stream2TransferGpsReplyInfo(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int							iErr		=	-1;
	 //  p0;
	 TRANSFER_GPS_replyInfo		*	pContent		=	(  TRANSFER_GPS_replyInfo  *  )p1;
	 //  QY_CFGITEM					*	pItem		=	(  QY_CFGITEM  *  )p2;
	 
	 if  (  !pContent  )  goto  errLabel;
	 	 
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
		     case  CONST_imCommType_transferGpsReplyInfo:
				   switch  (  tmp_cfgId  )  { 
						   case  CONST_qnmCfgId_start:
							     pContent->uiType  =  uiStreamId;   
								 break;
						   case  CONST_qnmCfgId_usOp:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usOp  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_tStartTime_org:
 							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->tStartTime_org  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_uiTranNo_org:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiTranNo_org  )  )  goto  errLabel;
								 break;
						   default:
								  break;
				   }				 
				   break;
			 default:
					break;
	 }	 

	 iErr  =  0;
errLabel:
	 if  (  iErr  )  {
		 traceLogA(  (char*)  "tmpHandler_stream2TransferGpsReplyInfo: failed"  );
	 }
	 return  iErr;
}


 int  transferGpsData2Stream(  unsigned  int  uiStreamId,  TRANSFER_GPS_DATA  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;
	 //

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;


	 if  (  pReq->tLastTime_showFrameInfo_020534  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tLastTime_showFrameInfo_020534,  (  void  *  )&pReq->tLastTime_showFrameInfo_020534,  sizeof(  pReq->tLastTime_showFrameInfo_020534  ),  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pReq->usCnt  )  {

		 if  (  pReq->usCnt  >  mycountof(  pReq->mems  )  )  goto  errLabel;

		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt,  (  void  *  )pReq->usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;
		 //
		 for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {
			  TRANSFER_GPS_dataMem	*	pMem	=	&pReq->mems[i];

			  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_mem,  0,  &ptr,  &len  )  )  goto  errLabel;

			  if  (  pMem->iLaInM10000f  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_iLaInM10000f,  (  void  *  )pMem->iLaInM10000f,  0,  &ptr,  &len  )  )  goto  errLabel;

			  if  (  pMem->iLoInM10000f  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_iLoInM10000f,  (  void  *  )pMem->iLoInM10000f,  0,  &ptr,  &len  )  )  goto  errLabel;
 

			  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }

	 }

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
     
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}


 int  tmpHandler_stream2TransferGpsData(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 TRANSFER_GPS_DATA	*	pContent	=	(  TRANSFER_GPS_DATA  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
			 case  CONST_imCommType_transferGpsData:
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_start:
							     pContent->uiType  =  uiStreamId;
								 break;
						   case  CONST_qnmCfgId_tLastTime_showFrameInfo_020534:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->tLastTime_showFrameInfo_020534  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_usCnt:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usCnt  )  )  goto  errLabel;

								 if  (  pContent->usCnt  >  mycountof(  pContent->mems  )  )  goto  errLabel;

								 //  ÏÂÃæÒª½øÐÐ³õÊ¼»¯£¬·ÅÔÚÕâÀïÊÇÒòÎªµ£ÐÄÏÂÃæµÄÊý¾ÝÈç¹û³ö´í£¬usCnt½«°üº¬ÁËÒ»Ð©´íÎóÊý¾Ý
								 int  i;
								 for  (  i  =  0;  i  <  pContent->usCnt;  i  ++  )  {			
									  memset(  &pContent->mems[i],  0,  sizeof(  pContent->mems[i]  )  );
								 }
							     break;
						   default:
								  break;
				   }
				   break;
			 case  CONST_imCommType_mem:  {
				   TRANSFER_GPS_dataMem  *  pMem		=	NULL;
				   //
				   if  (  pContent->tmpInternal.usCnt_mems  >=  mycountof(  pContent->mems  )  )  {
					   traceLogA(  (char*)  "tmpHandler_stream2TransferAudioData failed: usCnt_mems is too big"  );  goto  errLabel;
				   }
				   //
				   pMem  =  &pContent->mems[pContent->tmpInternal.usCnt_mems];				   
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_iLaInM10000f:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->iLaInM10000f  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_iLoInM10000f:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pMem->iLoInM10000f  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_null:
							     pContent->tmpInternal.usCnt_mems  ++  ;
							     break;
						   default:
									break;
				   }
				   //

				   }
				   break;
			 default:
					break;
	 }


	 iErr  =  0;
errLabel:
	 if  (  iErr  )  {
		 traceLogA(  (char*)  "tmpHandler_stream2TransferGpsData: failed"  );
	 }
	 return  iErr;
}

/////

  int  transferGpsDataResp2Stream(  unsigned  int  uiStreamId,  TRANSFER_GPS_dataResp  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;
	 //

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;


	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
     
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}


 int  tmpHandler_stream2TransferGpsDataResp(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 TRANSFER_GPS_dataResp	*	pContent	=	(  TRANSFER_GPS_dataResp  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
			 case  CONST_imCommType_transferGpsDataResp:
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_start:
							     pContent->uiType  =  uiStreamId;
								 break;
						   default:
								  break;
				   }
				   break;
			 default:
					break;
	 }


	 iErr  =  0;
errLabel:
	 if  (  iErr  )  {
		 traceLogA(  (char*)  "tmpHandler_stream2TransferGpsDataResp: failed"  );
	 }
	 return  iErr;
}




 //////////////////


  int  retrieveWebContactListResp2Stream(  unsigned  int  uiStreamId,  RETRIEVE_WEBCONTACTLIST_RESP  *  pUpdateInfos,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pUpdateInfos  )  return  -1;
	 if  (  !buf  )  return  -1;
	 //
	 if  (  pUpdateInfos->usCnt  >  mycountof(  pUpdateInfos->mems  )  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 //  2008/03/02
	 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_wAdvertisement,  pUpdateInfos->wAdvertisement,  lstrlen(  pUpdateInfos->wAdvertisement  ),  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pUpdateInfos->usCnt  )  {
	 	   //
	 	   if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt,  (  void  *  )pUpdateInfos->usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;
		   //
		   for  (  i  =  0;  i  <  pUpdateInfos->usCnt;  i  ++  )  {
			    //  ÏÂÃæ½«Ò»¸öQY_MESSENGER_REGINFO×ª»»³ÉÁ÷
			    WEB_CONTACT_INFO  *  pRegInfo	=	&pUpdateInfos->mems[i];
		  
				if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_mem,  0,  &ptr,  &len  )  )  goto  errLabel;

				if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  (  void  *  )&pRegInfo->idInfo.ui64Id,  sizeof(  pRegInfo->idInfo.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
				//
				if  (  pRegInfo->grpDisplayName[0]  &&  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_grpDisplayName,  pRegInfo->grpDisplayName,  lstrlen(  pRegInfo->grpDisplayName  ),  &ptr,  &len  )  )  goto  errLabel;
				if  (  pRegInfo->displayName[0]  &&  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_displayName,  pRegInfo->displayName,  lstrlen(  pRegInfo->displayName  ),  &ptr,  &len  )  )  goto  errLabel;
		  
				if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
		   }
	 }

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
     
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}


 int  tmpHandler_stream2RetrieveWebContactListResp(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int							iErr		=	-1;
	 //  p0;
	 RETRIEVE_WEBCONTACTLIST_RESP	*	pResp		=	(  RETRIEVE_WEBCONTACTLIST_RESP  *  )p1;
	 //  QY_CFGITEM					*	pItem		=	(  QY_CFGITEM  *  )p2;
	 
	 if  (  !pResp  )  goto  errLabel;
	 	 
	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
		     case  CONST_imCommType_retrieveWebContactListResp:
				   switch  (  tmp_cfgId  )  { 
						   case  CONST_qnmCfgId_wAdvertisement:
							     if  (  getFieldData_wStr(  pItem,  pResp->wAdvertisement,  mycountof(  pResp->wAdvertisement  )  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_usCnt:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pResp->usCnt  )  )  goto  errLabel;
								 //
								 if  (  pResp->usCnt  >  mycountof(  pResp->mems  )  )  goto  errLabel;
							     break;					
						   default:
								  break;
				   }				 
				   break;
			 case  CONST_imCommType_mem:  {
				   WEB_CONTACT_INFO  *  pMem		=	NULL;
				   //
				   if  (  pResp->index  >=  mycountof(  pResp->mems  )  )  {
					   traceLogA(  (char*)  "tmpHandler_stream2RetrieveWebContactListResp: failed"  );  goto  errLabel;
				   }

				   //
				   pMem  =  &pResp->mems[pResp->index];				   
				   switch  (  tmp_cfgId  )  {
						   case  CONST_qnmCfgId_messengerId:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pMem->idInfo.ui64Id  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_grpDisplayName:
							     if  (  getFieldData_wStr(  pItem,  pMem->grpDisplayName,  mycountof(  pMem->grpDisplayName  )  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_displayName:
							     if  (  getFieldData_wStr(  pItem,  pMem->displayName,  mycountof(  pMem->displayName  )  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_null:
							     pResp->index  ++  ;
							     break;
						   default:
									break;
				   }
				   //
				   }
				   break;
			 default:
					break;
	 }	 

	 iErr  =  0;
errLabel:
	 if  (  iErr  )  {
		 traceLogA(  (char*)  "tmpHandler_stream2RetrieveWebContactListResp: failed"  );
	 }
	 return  iErr;
}


////


 int  refreshRecentFriendsResp2Stream(  unsigned  int  uiStreamId,  REFRESH_RECENTFRIENDS_RESP_h  *  pResp,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;
	 unsigned  long		ulIp	=	0;

	 if  (  !pResp  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  pResp->usCnt  >  mycountof(  pResp->mems  )  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 //
	 //
	 if  (  data2Stream(  CONST_qyDataType_l64,	  CONST_qnmCfgId_tLastRefreshedTime,  (  void  *  )&pResp->tLastRefreshedTime_misServ,  0,  &ptr,  &len  )  )  goto  errLabel;
	 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt,  (  void  *  )pResp->usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;
	 //
	 for  (  i  =  0;  i  <  pResp->usCnt;  i  ++  )  {

		  if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_mem,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
		  //
		  if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  (  void  *  )&pResp->mems[i].idInfo.ui64Id,  0,  &ptr,  &len  )  )  goto  errLabel;
		  if  (  pResp->mems[i].usRunningStatus  )  if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usRunningStatus,  (  void  *  )pResp->mems[i].usRunningStatus,  0,  &ptr,  &len  )  )  goto  errLabel;
		  if  (  pResp->mems[i].ulIp  )  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_ulIp,  (  void  *  )pResp->mems[i].ulIp,  0,  &ptr,  &len  )  )  goto  errLabel;
		  if  (  pResp->mems[i].ulDetectedIp  )  if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_ulDetectedIp,  (  void  *  )pResp->mems[i].ulDetectedIp,  0,  &ptr,  &len  )  )  goto  errLabel;
		  //
		  if (pResp->mems[i].conf_ui64Id) {
			  if (data2Stream(CONST_qyDataType_l64, CONST_ancCfgId_conf_ui64Id, (void*)&pResp->mems[i].conf_ui64Id, sizeof(pResp->mems[i].conf_ui64Id), &ptr, &len))  goto  errLabel;
		  }

	 }
	 
	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}


 int  tmpHandler_stream2RefreshRecentFriendsResp(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int							iErr		=	-1;
	 //  p0;
	 REFRESH_RECENTFRIENDS_RESP_h	*	pResp		=	(  REFRESH_RECENTFRIENDS_RESP_h  *  )p1;
	 //  QY_CFGITEM					*	pItem		=	(  QY_CFGITEM  *  )p2;
	 long							lVal;
	 int							index;
	 
	 if  (  !pResp  )  goto  errLabel;
	 if  (  pResp->usCnt_mems  >  mycountof(  pResp->mems  )  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
		     case  CONST_imCommType_refreshRecentFriendsResp:
				   switch  (  tmp_cfgId  )  {  	
						   case  CONST_qnmCfgId_start:
							     pResp->uiType  =  uiStreamId;   
				   				 break;
						   case  CONST_qnmCfgId_tLastRefreshedTime:  //  Ö»ÔÚ½áÊø°üÖÐÆð×÷ÓÃ
							     if  (  getFieldData_l64(  pItem,  &pResp->tLastRefreshedTime_misServ  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_usCnt:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pResp->usCnt  )  )  goto  errLabel;
								 //
								 if  (  pResp->usCnt  >  mycountof(  pResp->mems  )  )  goto  errLabel;
								 //
							     break;
						   case  CONST_qnmCfgId_mem:
							     if  (  pResp->usCnt_mems  >=  pResp->usCnt  )  goto  errLabel;
							     pResp->usCnt_mems  ++  ;							     
							     break;
						   case  CONST_qnmCfgId_messengerId:
							     index  =  pResp->usCnt_mems  -  1;
								 if  (  index  <  0  )  goto  errLabel;
								 if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pResp->mems[index].idInfo.ui64Id  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_usRunningStatus:
							     index  =  pResp->usCnt_mems  -  1;
								 if  (  index  <  0  )  goto  errLabel;
								 if  (  getFieldData_short(  pItem,  (  short  *  )&pResp->mems[index].usRunningStatus  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_ulIp:
							     index  =  pResp->usCnt_mems  -  1;
								 if  (  index  <  0  )  goto  errLabel;
								 if  (  getFieldData_long(  pItem,  &lVal  )  )  goto  errLabel;
								 pResp->mems[index].ulIp  =  lVal;
								 break;
						   case  CONST_qnmCfgId_ulDetectedIp:
							     index  =  pResp->usCnt_mems  -  1;
								 if  (  index  <  0  )  goto  errLabel;
								 if  (  getFieldData_long(  pItem,  &lVal  )  )  goto  errLabel;
								 pResp->mems[index].ulDetectedIp  =  lVal;
								 break;
						   case  CONST_ancCfgId_conf_ui64Id:
							     index = pResp->usCnt_mems - 1;
							     if (index < 0)  goto  errLabel;
								 if (getFieldData_l64(pItem, (__int64*)&pResp->mems[index].conf_ui64Id))  goto  errLabel;
								 //
							     break;
						   default:
								  break;
				   }				 
				   break;
			 default:
					break;
	 }	 

	 iErr  =  0;
errLabel:
	 return  iErr;
}


//////////////////////

 int  tmp_htonImNetStat(  IM_NET_STAT  *  p  )
{
	MACRO_htonl64(  p->ui64MsgDataLenRecvd  );							//  2009/10/10
	MACRO_htonl64(  p->ui64MsgDataLenSent  );
	//
	MACRO_htonl(  p->uiInSpeedInKbps  );								//  bps
	MACRO_htonl(  p->uiOutSpeedInKbps  );

	return  sizeof(  p[0]  );
}

 int  tmp_ntohImNetStat(  IM_NET_STAT  *  p  )
{
	MACRO_ntohl64(  p->ui64MsgDataLenRecvd  );							//  2009/10/10
	MACRO_ntohl64(  p->ui64MsgDataLenSent  );
	//
	MACRO_ntohl(  p->uiInSpeedInKbps  );								//  bps
	MACRO_ntohl(  p->uiOutSpeedInKbps  );

	return  sizeof(  p[0]  );
}


 int  tmp_htonNetStatsTotal(  NET_STATS_total  *  p  )
{
	tmp_htonImNetStat(  &p->netStat_a  );
	tmp_htonImNetStat(  &p->netStat_v  );
	tmp_htonImNetStat(  &p->netStat_f  );
	tmp_htonImNetStat(  &p->netStat_others  );
	tmp_htonImNetStat(  &p->netStat_admin  );

	return  sizeof(  p[0]  );
}

 int  tmp_ntohNetStatsTotal(  NET_STATS_total  *  p  )
{
	tmp_ntohImNetStat(  &p->netStat_a  );
	tmp_ntohImNetStat(  &p->netStat_v  );
	tmp_ntohImNetStat(  &p->netStat_f  );
	tmp_ntohImNetStat(  &p->netStat_others  );
	tmp_ntohImNetStat(  &p->netStat_admin  );

	return  sizeof(  p[0]  );
}

 int  tmp_htonQmdChannelStatus(  QMD_channel_status  *  p  )
{
	
	return  sizeof(  p[0]  );
 }

 int  tmp_ntohQmdChannelStatus(  QMD_channel_status  *  p  )
{
	
	return  sizeof(  p[0]  );
 }


 int  tmp_htonQmdStatusMsgrMem(  QMD_status_msgrMem  *  p  )
{
	tmp_htonQmdChannelStatus(  &p->a  );
	tmp_htonQmdChannelStatus(  &p->v  );
	tmp_htonQmdChannelStatus(  &p->f  );
	tmp_htonQmdChannelStatus(  &p->t  );

	return  sizeof(  p[0]  );
}

 int  tmp_ntohQmdStatusMsgrMem(  QMD_status_msgrMem  *  p  )
{
	tmp_ntohQmdChannelStatus(  &p->a  );
	tmp_ntohQmdChannelStatus(  &p->v  );
	tmp_ntohQmdChannelStatus(  &p->f  );
	tmp_ntohQmdChannelStatus(  &p->t  );

	return  sizeof(  p[0]  );
}

 //  2015/09/12. 因为只在服务器本机使用，所以可以不转换
 int  tmp_htonQmdStatusChannelMem(  QMD_status_channelMem  *  p  )
{

	return  sizeof(  p[0]  );
}

 int  tmp_ntohQmdStatusChannelMem(  QMD_status_channelMem  *  p  )
{

	return  sizeof(  p[0]  );
}


 int  qmdStatus2Stream(  unsigned  int  uiStreamId,  QMD_status  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;
	 unsigned  long		ulIp	=	0;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;


	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 //

	 if  (  pReq->ucbResp  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbResp,  (  void  *  )pReq->ucbResp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pReq->iSubType  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_subtype,  (  void  *  )pReq->iSubType,  0,  &ptr,  &len  )  )  goto  errLabel;  
	 }

	 if  (  pReq->ucbGetTotal  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbGetTotal,  (  void  *  )pReq->ucbGetTotal,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->idInfo.ui64Id  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  (  void  *  )&pReq->idInfo.ui64Id,  sizeof(  pReq->idInfo.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //  2015/09/01
	 if  (  pReq->printDaemonShowInfo.ulFlgs  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_showInfoFlgs,  (  void  *  )pReq->printDaemonShowInfo.ulFlgs,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 NET_STATS_total	t;
	 int			tmpLen;
	 if  (  pReq->total.netStat_admin.ui64MsgDataLenRecvd  &&  pReq->total.netStat_admin.ui64MsgDataLenSent  )  {
		 memcpy(  &t,  &pReq->total,  sizeof(  t  )  );
		 if  (  (  tmpLen  =  tmp_htonNetStatsTotal(  &t  )  )  <  0  )  goto  errLabel;
		 if  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_netStats_total,  &t,  tmpLen,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 switch  (  pReq->iSubType  )  {			
			 case  CONST_iDaemonStatusType_msgr:
				   if  (  pReq->usCnt  )  {
					   if  (  pReq->usCnt  >  mycountof(  pReq->u.msgr.mems  )  )  goto  errLabel;
					   if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt,  (  void  *  )pReq->usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;

					   QMD_status_msgrMem			m;
					   int  i;
					   for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {
						    QMD_status_msgrMem  *  pMem  =  &pReq->u.msgr.mems[i];

							if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_mem,  0,  &ptr,  &len  )  )  goto  errLabel;

							memcpy(  &m,  pMem,  sizeof(  m  )  );
							if  (  (  tmpLen  =  tmp_htonQmdStatusMsgrMem(  &m  )  )  <  0  )  goto  errLabel;
							if  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_qmdStatus_msgrMem,  &m,  tmpLen,  &ptr,  &len  )  )  goto  errLabel;

							if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
					   }
				   }
				   break;
			 case  CONST_iDaemonStatusType_channel:
				   if  (  pReq->usCnt  )  {
					   if  (  pReq->usCnt  >  mycountof(  pReq->u.channel.mems  )  )  goto  errLabel;
					   if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt,  (  void  *  )pReq->usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;

					   QMD_status_channelMem			m;
					   int  i;
					   for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {
						    QMD_status_channelMem  *  pMem  =  &pReq->u.channel.mems[i];

							if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_mem,  0,  &ptr,  &len  )  )  goto  errLabel;

							memcpy(  &m,  pMem,  sizeof(  m  )  );
							if  (  (  tmpLen  =  tmp_htonQmdStatusChannelMem(  &m  )  )  <  0  )  goto  errLabel;
							if  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_qmdStatus_channelMem,  &m,  tmpLen,  &ptr,  &len  )  )  goto  errLabel;

							if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
					   }
				   }

				   break;
			 default:
				    traceLog((TCHAR*)  _T(  "getDaemonStatusReq2Stream failed, iSubType %d error"  ),  pReq->iSubType  );
					goto  errLabel;
	 }

	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}


 int  tmpHandler_stream2qmdStatus(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int							iErr		=	-1;
	 //  p0;
	 QMD_status	*	pReq		=	(  QMD_status  *  )p1;
	 //  QY_CFGITEM					*	pItem		=	(  QY_CFGITEM  *  )p2;
	 long							lVal;
	 int							index;
	 int						tmpLen;
	 char						buf[max(  sizeof(  NET_STATS_total  ),  sizeof(  QMD_status_msgrMem  )  )  +  1024];
	 
	 if  (  !pReq  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
		     case  CONST_imCommType_qmdStatus:
				   switch  (  tmp_cfgId  )  {  	
						   case  CONST_qnmCfgId_start:
							     pReq->uiType  =  uiStreamId;   
				   				 break;
						   case  CONST_qnmCfgId_ucbResp:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pReq->ucbResp  )  )  goto  errLabel;
								 break;
						   case  CONST_qnmCfgId_subtype:
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pReq->iSubType  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_ucbGetTotal:
							     if  (  getFieldData_char(  pItem,  (  char  *  )&pReq->ucbGetTotal  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_messengerId:
							     if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pReq->idInfo.ui64Id  )  )  goto  errLabel;
							     break;
								 //
						   case  CONST_qnmCfgId_showInfoFlgs:  //  2015/09/01
							     if  (  getFieldData_long(  pItem,  (  long  *  )&pReq->printDaemonShowInfo.ulFlgs  )  )  goto  errLabel;
							     break;
								 //
						   case  CONST_qnmCfgId_netStats_total:
							     tmpLen  =  sizeof(  buf  );
								 if  (  getFieldData_data(  pItem,  buf,  (  unsigned  int  *  )&tmpLen  )  )  goto  errLabel;
								 if  (  tmpLen  >  sizeof(  buf  )  )  goto  errLabel;											//  impossible  
								 memset(  buf  +  tmpLen,  0,  sizeof(  buf  )  -  tmpLen  );
								 if  (  tmp_ntohNetStatsTotal(  (  NET_STATS_total  *  )buf  )  <  0  )  goto  errLabel;
								 memcpy(  &pReq->total,  buf,  sizeof(  pReq->total  )  );							     
							     break;
						   case  CONST_qnmCfgId_usCnt:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pReq->usCnt  )  )  goto  errLabel;
								 if  (  pReq->iSubType  ==  CONST_iDaemonStatusType_msgr  )  {
									 if  (  pReq->usCnt  >  mycountof(  pReq->u.msgr.mems  )  )  {
										 traceLog((TCHAR*)  _T(  "tmpHandler_stream2GetDaemonStatusGrp failed: usCnt is too big"  )  );  goto  errLabel;
									 }
									 int  i;	//  2009/05/20
									 for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {			
										  memset(  &pReq->u.msgr.mems[i],  0,  sizeof(  pReq->u.msgr.mems[i]  )  );								 
									 }
									 }
								 else  if  (  pReq->iSubType  ==  CONST_iDaemonStatusType_channel  )  {
									       if  (  pReq->usCnt  >  mycountof(  pReq->u.channel.mems  )  )  {
											   traceLog((TCHAR*)  _T(  "tmpHandler_stream2GetDaemonStatusGrp failed: usCnt is too big"  )  );  goto  errLabel;
										   }
										   int  i;	//  2009/05/20
										   for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {			
											    memset(  &pReq->u.channel.mems[i],  0,  sizeof(  pReq->u.channel.mems[i]  )  );								 
										   }

										   }
								 else  
									 goto  errLabel;
							     break;
						   default:
								  break;
				   }				 
				   break;
			 case  CONST_imCommType_mem:  {
				   if  (  pReq->iSubType  ==  CONST_iDaemonStatusType_msgr  )  {				   
					   QMD_status_msgrMem  *  pMem		=	NULL;
					   //
					   if  (  pReq->tmpInternal.usCnt_mems  >=  mycountof(  pReq->u.msgr.mems  )  )  {
						   traceLogA(  (char*)  "tmpHandler_stream2GetDaemonStatus failed: usCnt_mems is too big"  );  goto  errLabel;
					   }
					   //
					   pMem  =  &pReq->u.msgr.mems[pReq->tmpInternal.usCnt_mems];				   
					   switch  (  tmp_cfgId  )  {	
							   case  CONST_qnmCfgId_qmdStatus_msgrMem:							   
								     tmpLen  =  sizeof(  buf  );
									 if  (  getFieldData_data(  pItem,  buf,  (  unsigned  int  *  )&tmpLen  )  )  goto  errLabel;
									 if  (  tmpLen  >  sizeof(  buf  )  )  goto  errLabel;											//  impossible  
									 memset(  buf  +  tmpLen,  0,  sizeof(  buf  )  -  tmpLen  );
									 if  (  tmp_ntohQmdStatusMsgrMem(  (  QMD_status_msgrMem  *  )buf  )  <  0  )  goto  errLabel;
									 memcpy(  pMem,  buf,  sizeof(  pMem[0]  )  );							     
									 break;
							   case  CONST_qnmCfgId_null:
								     pReq->tmpInternal.usCnt_mems  ++  ;
									 break;				   
					   }
					   }
				   else  if  (  pReq->iSubType  ==  CONST_iDaemonStatusType_channel  )  {
							  QMD_status_channelMem  *  pMem		=	NULL;
							  //
							  if  (  pReq->tmpInternal.usCnt_mems  >=  mycountof(  pReq->u.channel.mems  )  )  {
								  traceLogA(  (char*)  "tmpHandler_stream2GetDaemonStatus failed: usCnt_mems is too big"  );  goto  errLabel;
							  }
							  //
							  pMem  =  &pReq->u.channel.mems[pReq->tmpInternal.usCnt_mems];				   
							  switch  (  tmp_cfgId  )  {	
							   case  CONST_qnmCfgId_qmdStatus_channelMem:							   
								     tmpLen  =  sizeof(  buf  );
									 if  (  getFieldData_data(  pItem,  buf,  (  unsigned  int  *  )&tmpLen  )  )  goto  errLabel;
									 if  (  tmpLen  >  sizeof(  buf  )  )  goto  errLabel;											//  impossible  
									 memset(  buf  +  tmpLen,  0,  sizeof(  buf  )  -  tmpLen  );
									 if  (  tmp_ntohQmdStatusChannelMem(  (  QMD_status_channelMem  *  )buf  )  <  0  )  goto  errLabel;
									 memcpy(  pMem,  buf,  sizeof(  pMem[0]  )  );							     
									 break;
							   case  CONST_qnmCfgId_null:
								     pReq->tmpInternal.usCnt_mems  ++  ;
									 break;				   
					   }

				   }
				   else  
					   goto  errLabel;
				   }
				   break;
			 default:
					break;
	 }	 

	 iErr  =  0;
errLabel:
	 return  iErr;
}


//
 int  qmdMcuStatusList2Stream(  unsigned  int  uiStreamId,  QMD_mcuStatus_list  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;
	 unsigned  long		ulIp	=	0;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;


	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 //




				   if  (  pReq->usCnt  )  {
					   if  (  pReq->usCnt  >  mycountof(  pReq->mems  )  )  goto  errLabel;
					   if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCnt,  (  void  *  )pReq->usCnt,  0,  &ptr,  &len  )  )  goto  errLabel;

					   int  i;
					   for  (  i  =  0;  i  <  pReq->usCnt;  i  ++  )  {
						    QMD_mcuStatus_mem  *  pMem  =  &pReq->mems[i];

							if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_mem,  0,  &ptr,  &len  )  )  goto  errLabel;

							//
							if  (  pMem->idInfo_mcu.ui64Id  )  {
								if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_mcu,  (  void  *  )&pMem->idInfo_mcu.ui64Id,  sizeof(pMem->idInfo_mcu.ui64Id),  &ptr,  &len  )  )  goto  errLabel;
							}
							if  (  pMem->usMcuType  )  {
								if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usMcuType,  (  void  *  )pMem->usMcuType,  0,  &ptr,  &len  )  )  goto  errLabel;
							}

							//
							if  (  pMem->idInfo_conf.ui64Id  )  {
								if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_conf,  (  void  *  )&pMem->idInfo_conf.ui64Id,  sizeof(pMem->idInfo_conf.ui64Id),  &ptr,  &len  )  )  goto  errLabel;
							}
							//
							if  (  pMem->idInfo_initiator.ui64Id  )  {
								if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_initiator,  (  void  *  )&pMem->idInfo_initiator.ui64Id,  sizeof(pMem->idInfo_initiator.ui64Id),  &ptr,  &len  )  )  goto  errLabel;
							}
							//
							if  (  pMem->tStartTime_task  )  {
								if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_startTime_task,  (  void  *  )&pMem->tStartTime_task,  sizeof(  pMem->tStartTime_task  ),  &ptr,  &len  )  )  goto  errLabel;
							}
							
							//
							QMD_status_msgrMem  m;
							m  =  pMem->mcuStatus;
							int  tmpLen;
							if  (  (  tmpLen  =  tmp_htonQmdStatusMsgrMem(  &m  )  )  <  0  )  goto  errLabel;
							if  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_qmdStatus_msgrMem,  &m,  tmpLen,  &ptr,  &len  )  )  goto  errLabel;
							
							//
							if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
					   }
				   }

	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}


 int  tmpHandler_stream2qmdMcuStatusList(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int							iErr		=	-1;
	 //  p0;
	 QMD_mcuStatus_list	*	pReq		=	(  QMD_mcuStatus_list  *  )p1;
	 //  QY_CFGITEM					*	pItem		=	(  QY_CFGITEM  *  )p2;
	 long							lVal;
	 int							index;
	 int						tmpLen;
	 char						buf[max(  sizeof(  NET_STATS_total  ),  sizeof(  QMD_status_msgrMem  )  )  +  1024];
	 
	 if  (  !pReq  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
		     case  CONST_imCommType_qmdMcuStatusList:
				   switch  (  tmp_cfgId  )  {  	
						   case  CONST_qnmCfgId_start:
							     pReq->uiType  =  uiStreamId;   
				   				 break;
						   case  CONST_qnmCfgId_usCnt:
							     if  (  getFieldData_short(  pItem,  (  short  *  )&pReq->usCnt  )  )  goto  errLabel;
							     break;
						   default:
								  break;
				   }				 
				   break;
			 case  CONST_imCommType_mem:  {
				   				   
					   QMD_mcuStatus_mem  *  pMem		=	NULL;
					   //
					   if  (  pReq->tmpInternal.usCnt_mems  >=  mycountof(  pReq->mems  )  )  {
						   traceLogA(  (char*)  "tmpHandler_stream2GetDaemonConfList failed: usCnt_mems is too big"  );  
						   goto  errLabel;
					   }
					   //
					   pMem  =  &pReq->mems[pReq->tmpInternal.usCnt_mems];				   
					   switch  (  tmp_cfgId  )  {	
							   case  CONST_qnmCfgId_null:
								     pReq->tmpInternal.usCnt_mems  ++  ;
									 break;				   
							   case  CONST_qnmCfgId_idInfo_mcu:
								     if  (  getFieldData_l64(  pItem,  (__int64*)&pMem->idInfo_mcu.ui64Id  )  )  goto  errLabel;								     
								     break;
							   case  CONST_qnmCfgId_usMcuType:
								     if  (  getFieldData_short(  pItem,  (  short  *  )&pMem->usMcuType  )  )  goto  errLabel;
								     break;
							   case  CONST_qnmCfgId_idInfo_conf:
								     if  (  getFieldData_l64(  pItem,  (__int64*)&pMem->idInfo_conf.ui64Id  )  )  goto  errLabel;
								     break;
							   case  CONST_qnmCfgId_idInfo_initiator:
								     if  (  getFieldData_l64(  pItem,  (__int64*)&pMem->idInfo_initiator.ui64Id  )  )  goto  errLabel;
								     break;
							   case  CONST_qnmCfgId_startTime_task:
								     if  (  getFieldData_l64(  pItem,  (__int64*)&pMem->tStartTime_task  )  )  goto  errLabel;
								     break;
									 //
							   case  CONST_qnmCfgId_qmdStatus_msgrMem:							   
								     tmpLen  =  sizeof(  buf  );
									 if  (  getFieldData_data(  pItem,  buf,  (  unsigned  int  *  )&tmpLen  )  )  goto  errLabel;
									 if  (  tmpLen  >  sizeof(  buf  )  )  goto  errLabel;											//  impossible  
									 memset(  buf  +  tmpLen,  0,  sizeof(  buf  )  -  tmpLen  );
									 if  (  tmp_ntohQmdStatusMsgrMem(  (  QMD_status_msgrMem  *  )buf  )  <  0  )  goto  errLabel;
									 memcpy(  &pMem->mcuStatus,  buf,  sizeof(  pMem->mcuStatus  )  );							     
									 break;

							   default:
									  break;
					   }
					   }
				   break;
			 default:
					break;
	 }	 

	 iErr  =  0;
errLabel:
	 return  iErr;
}



 //////////////
  int  mcuCmd2Stream(  unsigned  int  uiStreamId,  MCU_cmd  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;
	 unsigned  long		ulIp	=	0;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;


	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 //
	 if  (  pReq->idInfo_mcu.ui64Id  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_mcu,  (  void  *  )&pReq->idInfo_mcu.ui64Id,  sizeof(  __int64  ),  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  pReq->tmpInternal.bSend_debugStatusInfo  )  {
		 char  *  pData =  (char*)&pReq->debugStatusInfo;
		 int  tmpLen  =  sizeof(  pReq->debugStatusInfo  );
		 //
		 if  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_debugStatusInfo,  pData,  tmpLen,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 
	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}


 int  tmpHandler_stream2mcuCmd(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int							iErr		=	-1;
	 //  p0;
	 MCU_cmd	*	pReq		=	(  MCU_cmd  *  )p1;
	 //  QY_CFGITEM					*	pItem		=	(  QY_CFGITEM  *  )p2;
	 long							lVal;
	 int							index;
	 int						tmpLen;
	 char						buf[max(  sizeof(  QMC_debugStatusInfo  ),  1024)];
	 
	 if  (  !pReq  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  uiStreamId  )  {
		     case  CONST_imCommType_mcuCmd:
				   switch  (  tmp_cfgId  )  {  	
						   case  CONST_qnmCfgId_start:
							     pReq->uiType  =  uiStreamId;   
				   				 break;
						   case  CONST_qnmCfgId_idInfo_mcu:
							     if  (  getFieldData_l64(  pItem,  (__int64*)&pReq->idInfo_mcu.ui64Id  )  )  goto  errLabel;
							     break;
						   case  CONST_qnmCfgId_debugStatusInfo:
							     tmpLen  =  sizeof(  buf  );
							     if  (  getFieldData_data(  pItem,  buf,  (unsigned  int  *  )&tmpLen  )  )  goto  errLabel;
								 memcpy(  &pReq->debugStatusInfo,  buf,  min(  tmpLen,  sizeof(  pReq->debugStatusInfo  )  )  );
							     break;
						   default:
								  break;
				   }				 
				   break;
			 default:
					break;
	 }	 

	 iErr  =  0;
errLabel:
	 return  iErr;
}





 //
  int  qmdPolicy2Stream(  unsigned  int  uiStreamId,  QMD_policy  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;
	 unsigned  long		ulIp	=	0;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 //
	 //
	 if  (  pReq->mcuUsrName[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_mcuUsrName,  (  void  *  )pReq->mcuUsrName,  _tcslen(  pReq->mcuUsrName  ),  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  pReq->mcuPasswd[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_str,  CONST_qnmCfgId_mcuPasswd,  (  void  *  )pReq->mcuPasswd,  strlen(  pReq->mcuPasswd  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->mcuDomainName[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_mcuDomainName,  (  void  *  )pReq->mcuDomainName,  _tcslen(  pReq->mcuDomainName  ),  &ptr,  &len  )  )  goto  errLabel;
	 }


	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}


 int  tmpHandler_stream2qmdPolicy(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 QMD_policy		*	pReq	=	(  QMD_policy  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 long						lVal;
	 
	 if  (  !pReq  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_qmdPolicy  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );
	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_start:
				   pReq->uiType  =  uiStreamId;
				   break;
			 case  CONST_qnmCfgId_mcuUsrName:
				   if  (  getFieldData_wStr(  pItem,  pReq->mcuUsrName,  mycountof(  pReq->mcuUsrName  )  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_mcuPasswd:
				   if  (  getFieldData_str(  pItem,  pReq->mcuPasswd,  mycountof(  pReq->mcuPasswd  )  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_mcuDomainName:
				   if  (  getFieldData_wStr(  pItem,  pReq->mcuDomainName,  mycountof(  pReq->mcuDomainName  )  )  )  goto  errLabel;
				   break;
			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}



 //////////////////////////////////
 //2016/12/28

 int  testSpeedReq2Stream(  unsigned  int  uiStreamId,  TEST_speed_req  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;
	 unsigned  long		ulIp	=	0;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 //
	 //
	 if  (  pReq->tn_perSend  )  {
		 //if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiDevType_from,  (  void  *  )pPcInfo->uiType,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  pReq->usLen  >  sizeof(  pReq->buf  )  )  goto  errLabel;
	 //
	 if  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_testSpeed_data,  pReq->buf,  pReq->usLen,  &ptr,  &len  )  )  goto  errLabel;

	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}


 int  tmpHandler_stream2TestSpeedReq(  CTX_stream2Data * pCtx, void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 TEST_speed_req		*	pReq	=	(  TEST_speed_req  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 long						lVal;
	 
	 if  (  !pReq  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_messengerPcInfo  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );
	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_testSpeed_data:
				   unsigned  int  tmpLen;
				   tmpLen  =  sizeof(  pReq->buf  );
				   if  (  getFieldData_data(  pItem,  pReq->buf,  &tmpLen  )  )  goto  errLabel;
				   pReq->usLen  =  tmpLen;
				   break;
#if  0
			 case  CONST_qnmCfgId_iPlatformId:
				   if  (  getFieldData_long(  pItem,  &lVal  )  )  goto  errLabel;
				   pPcInfo->iPlatformId  =  lVal;
				   break;
#endif
			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}



///////////


///////////////////



 //extern  "C"  int  qnmOpenSession_mis(  char  *  servIp,  unsigned  short  usPort,  QY_COMM_AUTHINFO_MIS  *  pAuthInfo,  unsigned  short  usAuthCmd,  unsigned  int  uiChannelType,  char  *  clientIp,  int  iServiceId,  char  *  serviceVer,  void  *  pCommEncCtx,  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo,  char  *  data,  unsigned  int  *piDataSize,  Param_dbg  *  pParam  )
 extern  "C"  int  qnmOpenSession_mis(char* servIp, unsigned  short  usPort, QY_COMM_AUTHINFO_MIS * pAuthInfo, unsigned  short  usAuthCmd, unsigned  int  uiChannelType, char* clientIp, int  iServiceId, char* serviceVer, void* pCommEncCtx, __int64  i64StartTime_base, QY_COMM_SESSION * pSession, QY_SOCK * pSock, SOCK_TIMEOUT * pTo, char* data, unsigned  int* piDataSize, Param_dbg * pParam)
{
	 int					iErr			=  -1;	 
	 QY_COMM_AUTHINFO_MIS	authInfo;
	 char					ip[16];
	 QY_MSG_HEAD_h			tmpResp;
	 char					tmpBuf[4096]	=	"";
	 unsigned  int			len;

	 if  (  !servIp  )  return  -1;
	 if  (  !usPort  )  return  -1;
	 if  (  !usAuthCmd  )  {
		 if  (  !pAuthInfo  )  {
			 traceLogA(  (char*)  "qnmOpenSession_mis failed: pAuthInfo is null"  );
			 return  -1;
		 }
	 }
	 if (!pParam) {
#ifdef  __DEBUG__
		 traceLog((TCHAR*)_T("qnmOpenSession_mis failed, pParam is null"));
#endif
		 return  -1;
	 }

	 //
	 TCHAR  tBuf[128];
#ifdef  __DEBUG__
	 if (pParam->m_bShowInfo) {
		 _sntprintf(tBuf, mycountof(tBuf), _T("qnmOpenSession_mis enters: %S:%d. %s"), servIp, (int)usPort, qyGetDesByType1(CONST_channelTypeTable, uiChannelType ));
		 showInfo_open0(0, pParam->m_pHint, tBuf);
	 }
#endif


	 if  (  pAuthInfo  )  memcpy(  &authInfo,  pAuthInfo,  sizeof(  authInfo  )  );
	 else  memset(  &authInfo,  0,  sizeof(  authInfo  )  );
	 if  (  !bQySockOpen(  pSock  )  )  {		//  Èç¹ûÇ°ÃæÒÑ½¨Á¢Á¬½Ó£¬Ôò²»ÐèÒª½¨Á¢ÐÂÁ¬½Ó
		 if  (  qyConnect(  servIp,  usPort,  pSock,  pTo->iConnect  )  )  {
			 //
			 if (pParam->m_bShowInfo) {
				 _sntprintf(tBuf, mycountof(tBuf), _T("qnmOpenSession_mis: qyConnect %S:%d failed"), servIp, (int)usPort);
				 showInfo_open0(0, pParam->m_pHint, tBuf);
			 }
			 //
			 goto  errLabel;
		 }
	 }
	 authInfo.usAuthCmd  =  usAuthCmd;
	 authInfo.uiChannelType  =  uiChannelType;	//  2007/07/08
	 //
	 if  (  bIpValid(  clientIp  )  )  safeStrnCpy(  clientIp,  authInfo.ip,  mycountof(  authInfo.ip  )  );
	 else  {
		   if  (  getLocalIpBySocket(  pSock->sockFd,  ip  )  )  goto  errLabel;
		   safeStrnCpy(  ip,  authInfo.ip,  sizeof(  authInfo.ip  )  );
	 }
	 
	 //  ½«»á»°ÃÜÔ¿·ÅÈëauthInfoÁ÷ÖÐ£¬2008/06/10
	 if  (  pCommEncCtx  )  {
		 ENC_CTX_session  *  pEncCtx  =  (  ENC_CTX_session  *  )pCommEncCtx;
		 if  (  pEncCtx->common.type  ==  CONST_qyEncType_rsa
			 &&  pEncCtx->uiBlobLen_sessionKey  )  
		 {
			 authInfo.uiBlobLen_sessionKey  =  min(  pEncCtx->uiBlobLen_sessionKey,  mycountof(  authInfo.sessionKeyBlob  )  );
			 memcpy(  authInfo.sessionKeyBlob,  pEncCtx->sessionKeyBlob,  authInfo.uiBlobLen_sessionKey  );
		 }
		 //  2015/08/28
		 #ifdef  __DEBUG__
				 int  ii;
				 switch  (  pEncCtx->common.type  )  {
						 case  0:
								ii  =  0;
								break;
						 case  3:
							    ii  =  3;
							    break;
						 case  4:
							    ii  =  4;
							    break;
						 default:
								break;
				 }
		 #endif
		 }
	 else  {
		   #ifdef  __DEBUG__
				   int  ii;
				   ii  =  0;
		   #endif
	 }
	 //
	 len  =  sizeof(  tmpBuf  );
	 if  (  commAuthInfo2Stream_mis(  &authInfo,  tmpBuf,  &len  )  )  goto  errLabel;

	 safeStrnCpy(  ip,  pSession->clientIp,  mycountof(  pSession->clientIp  )  );	//  2007/08/03

	 //
#ifdef  __DEBUG__
		//showInfo_open0(0, NULL, _T("before qyTellService_msg"));
#endif

	 //
	 MACRO_prepareForTran(  )

	 //  if  (  qyTellService_msg(  iServiceId,  serviceVer,  CONST_qyCmd_tellService,  pCommEncCtx,  tmpBuf,  len,  pSock,  pTo,  pSession  )  )  goto  errLabel;
	 if  (  qyTellService_msg(  iServiceId,  serviceVer,  pCommEncCtx,  i64StartTime_base, CONST_qyCmd_tellService,  tStartTran,  uiTranNo,  tmpBuf,  len,  pSock,  pTo,  pSession  )  )  {
		 //
		 showInfo_open0(0, 0, _T("qnmOpenSession_mis.qyTellService_msg failed"));
		 //
		 goto  errLabel;
	 }
	 if (qyRecvMsg(pSession, pSock, pTo, &tmpResp, tmpBuf, sizeof(tmpBuf))) {
		 showInfo_open0(0, 0, _T("qnmOpenSession_mis.qyRecvMsg failed"));
		 goto  errLabel;
	 }
	 //  traceLogA(  (char*)  "qwmOpenSession: get respCode of qyTellService is %s",  qyGetDesByType1(  CONST_qyRcTable,  tmpResp.head.usCode  )  );
	 
	 //  2011/10/27
	 if  (  tmpResp.i64StartTime  !=  tStartTran  
		 ||  tmpResp.uiTranNo  !=  uiTranNo  )
	 {
		 #ifdef  __DEBUG__
				 traceLog((TCHAR*)  _T(  "qnmOpenSession_mis failed, tStartTran or uiTranNo not matched"  )  );
		 #endif

		 goto  errLabel;
	 }

	 //  if  (  !isRcOk(  tmpResp.head.usCode  )  )  goto  errLabel; 

	 iErr  =  0;

errLabel:
	 
	 if  (  iErr  )  {
		 if  (  bQySockOpen(  pSock  )  )  qyDisconnect(  pSock  );
		}
	 else  {
		   if  (  piDataSize  &&  data  )  {
			   *piDataSize  =  min(  *piDataSize,  tmpResp.uiLen  );
			   memcpy(  data,  tmpBuf,  *piDataSize  );
		   }
	 }

	 return  iErr;
}











 QY_DMITEM  CONST_imOpTable_en[]  =
{
	{	CONST_imOp_says,										(TCHAR*)_T(  "says"  ),							},
	{	CONST_imOp_tryToSendFile,								(TCHAR*)_T(  "tryToSendFile"  ),				},
	//
	{	CONST_imOp_recv_accept,									(TCHAR*)_T(  "recv_accept"  ),					},
	{	CONST_imOp_recv_deny,									(TCHAR*)_T(  "recv_deny"  ),					},
	{	CONST_imOp_recvFile_saveas,								(TCHAR*)_T(  "recvFile_saveas"  ),				},
    //
	{	CONST_imOp_recv_cancel,									(TCHAR*)_T(  "recv_cancel"  ),					},
	{	CONST_imOp_send_cancel,									(TCHAR*)_T(  "send_cancel"  ),					},
	{	CONST_imOp_send_permit,									(TCHAR*)_T(  "send_permit"  ),					},
	//
	{	CONST_imOp_dual_permit,									(TCHAR*)_T(  "dual_permit"  ),					},
	//
	{	CONST_imOp_recv_applyForOrgReq,							(TCHAR*)_T(  "recv_applyForOrgReq"  ),			},
	{	CONST_imOp_recv_applyForChkTaskAlive,					(TCHAR*)_T(  "recv_applyForChkTaskAlive"  ),	},		//  2009/10/19
	//
    //  2009/02/21
	{	CONST_imOp_requestToSpeak,								(TCHAR*)_T(  "request to speak"  ),				},
	{	CONST_imOp_stopSpeaking,								(TCHAR*)_T(  "stop speaking"  ),				},
	
	//  2014/10/09
	{	CONST_imOp_requestToSend,								(TCHAR*)_T(  "request to send"  ),				},		//  2014/10/09
	{	CONST_imOp_stopSending,									(TCHAR*)_T(  "stop sending"  ),					},		//  2014/10/09

	//

	//
	{	CONST_imOp_openFile,									(TCHAR*)_T(  "openFile"  ),						},
    //
	{	CONST_imOp_myMax,										(TCHAR*)_T(  "imOp_myMax"  ),					},
	//
	{	-1,																								},
};



 


/////////


#if  0
 int  iiqyhtonRefreshRecentFriendsReq(  long  lhClientVer,  REFRESH_RECENTFRIENDS_REQ_h  *  p  )
{
	int		len  =  -1;
	int		i;

	if  (  p->usCnt  >  mycountof(  p->mems  )  )  return  -1;

	//printRefreshRecentFriendsReq(  p  );

	for  (  i  =  0;  i  <  p->usCnt;  i  ++  )  {
		 MACRO_htonl64(  p->mems[i].idInfo.ui64Id  );
		 MACRO_htonl64(  p->mems[i].tLastRefreshedTime_misServ  );
	}
	len  =  offsetof(  REFRESH_RECENTFRIENDS_REQ_h,  mems  )  +  p->usCnt  *  sizeof(  p->mems[0]  );
	MACRO_htonl(  p->uiType  );
	MACRO_htonl64(  p->tLastRefreshedTime_misServ  );
	MACRO_htons(  p->usCnt  );
	return  len;
}

 int  iiqyntohRefreshRecentFriendsReq(  long  lhClientVer,  REFRESH_RECENTFRIENDS_REQ_h  *  p  )
{
	int		len  =  -1;
	int		i;


	MACRO_ntohl(  p->uiType  );
	MACRO_ntohl64(  p->tLastRefreshedTime_misServ  );
	MACRO_ntohs(  p->usCnt  );
	if  (  p->usCnt  >  mycountof(  p->mems  )  )  return  -1;
	for  (  i  =  0;  i  <  p->usCnt;  i  ++  )  {
		 MACRO_ntohl64(  p->mems[i].idInfo.ui64Id  );
		 MACRO_ntohl64(  p->mems[i].tLastRefreshedTime_misServ  );
	}

	//printRefreshRecentFriendsReq(  p  );

	//  len  =  offsetof(  REFRESH_RECENTFRIENDS_REQ,  mems  )  +  p->usCnt  *  sizeof(  p->mems[0]  );
	len  =  sizeof(  REFRESH_RECENTFRIENDS_REQ_h  );		//  ÒòÎªÓÐÊ±ÐèÒªÊ¹ÓÃÄÚ²¿±äÁ¿£¬¹Ê×îºÃ·µ»ØÈ«²¿³¤¶È
	return  len;
}
#endif 

 int  qyhtonRefreshRecentFriendsReq(long  lhClientVer, REFRESH_RECENTFRIENDS_REQ_h* pH,AT_REFRESH_RECENTFRIENDS_REQ_n  *  pN)
 {
	 int		len = -1;
	 int		i;

	 if (pH->usCnt > mycountof(pH->mems))  return  -1;

	 //printRefreshRecentFriendsReq(  p  );

#if  0
	 for (i = 0; i < p->usCnt; i++) {
		 MACRO_htonl64(p->mems[i].idInfo.ui64Id);
		 MACRO_htonl64(p->mems[i].tLastRefreshedTime_misServ);
	 }
	 len = offsetof(REFRESH_RECENTFRIENDS_REQ_h, mems) + p->usCnt * sizeof(p->mems[0]);
	 MACRO_htonl(p->uiType);
	 MACRO_htonl64(p->tLastRefreshedTime_misServ);
	 MACRO_htons(p->usCnt);
	 return  len;
#endif 

	 //
	 unsigned  char* tmp_p;
	 int  tmpLen;

	 //
	 char  ucReqType = 0;

	 //
	 len = 0;

	 //
	 tmp_p = pN->uiType_buf;
	 M_ton_long(pH->uiType, tmp_p, tmpLen);
	 len += tmpLen;
	 //
	 tmp_p = pN->ucReqType_buf;
	 M_ton_byte(ucReqType, tmp_p, tmpLen);
	 len += tmpLen;
	 //
	 tmp_p = pN->tLastRefreshedTime_misServ_buf;
	 M_ton_l64(pH->tLastRefreshedTime_misServ, tmp_p, tmpLen);
	 len += tmpLen;
	 //
	 tmp_p = pN->usCnt_buf;
	 M_ton_short(pH->usCnt, tmp_p, tmpLen);
	 len += tmpLen;
	 //
	 tmp_p = pN->mems_buf;
	 for (i = 0; i < pH->usCnt; i++) {
		 //
		 M_ton_l64(pH->mems[i].idInfo.ui64Id, tmp_p, tmpLen);
		 len += tmpLen;
		 M_ton_l64(pH->mems[i].tLastRefreshedTime_misServ, tmp_p, tmpLen);
		 len += tmpLen;
	 }
	 	 
	 //
	 return  len;
 }

 int  qyntohRefreshRecentFriendsReq(long  lhClientVer, AT_REFRESH_RECENTFRIENDS_REQ_n*  pN,  REFRESH_RECENTFRIENDS_REQ_h* pH)
 {
	 unsigned  char* tmp_p;
	 int  tmpLen;

	 int		len = -1;
	 int		i;

	 //
	 unsigned  char  ucReqType = 0;

	 //
	 tmp_p = pN->uiType_buf;
	 M_toh_long(tmp_p,pH->uiType,tmpLen);
	 tmp_p = pN->ucReqType_buf;
	 M_toh_byte(tmp_p, ucReqType, tmpLen);
	 tmp_p = pN->tLastRefreshedTime_misServ_buf;
	 M_toh_l64(tmp_p,pH->tLastRefreshedTime_misServ,tmpLen);
	 tmp_p = pN->usCnt_buf;
	 M_toh_short(tmp_p,pH->usCnt,tmpLen);
	 //
	 if (pH->usCnt > mycountof(pH->mems))  return  -1;
	 for (i = 0; i < pH->usCnt; i++) {
		 M_toh_l64(tmp_p,pH->mems[i].idInfo.ui64Id,tmpLen);
		 M_toh_l64(tmp_p,pH->mems[i].tLastRefreshedTime_misServ,tmpLen);
	 }

	 //printRefreshRecentFriendsReq(  p  );

	 //  len  =  offsetof(  REFRESH_RECENTFRIENDS_REQ,  mems  )  +  p->usCnt  *  sizeof(  p->mems[0]  );
	 len = sizeof(REFRESH_RECENTFRIENDS_REQ_h);		//  ÒòÎªÓÐÊ±ÐèÒªÊ¹ÓÃÄÚ²¿±äÁ¿£¬¹Ê×îºÃ·µ»ØÈ«²¿³¤¶È
	 return  len;

 }

////////////



/*


*/


 /////

 int  qyhtonImSimpleResp(  long  lhClientVer,  IM_SIMPLE_RESP  *  p  )
{
	MACRO_htonl(  p->uiType  );
	MACRO_htons(  p->usCmd_org  );
	MACRO_htonl(  p->uiContentType_org  );
	MACRO_htonl(  p->iStatus  );
	//
	//  MACRO_htonl64(  p->tStartTime_org  );		//  2009/10/17
	//  MACRO_htonl(  p->uiTranNo_org  );
	//
	return  sizeof(  IM_SIMPLE_RESP  );
}

 int  qyntohImSimpleResp(  long  lhClientVer,  IM_SIMPLE_RESP  *  p  )
{
	MACRO_ntohl(  p->uiType  );
	MACRO_ntohs(  p->usCmd_org  );
	MACRO_ntohl(  p->uiContentType_org  );
	MACRO_ntohl(  p->iStatus  );
	//
	//  MACRO_ntohl64(  p->tStartTime_org  );		//  2009/10/17
	//  MACRO_ntohl(  p->uiTranNo_org  );
	//
	return  sizeof(  IM_SIMPLE_RESP  );
}


 /////

#if  0
int  qyhtonImStreamContent(  long  lhClientVer,  IM_STREAM_CONTENT  *  p  )
{
	int		len		=	-1;

	if  (  p->usStreamLen  >  sizeof(  p->buf  )  )  return  -1;

	len  =  offsetof(  IM_STREAM_CONTENT,  buf  )  +  p->usStreamLen;

	MACRO_htonl(  p->uiType  );
	MACRO_htonl(  p->uiContentType  );
	MACRO_htons(  p->usStreamLen  );

	return  len;
}


int  qyntohImStreamContent(  long  lhClientVer,  char  *  p,  IM_STREAM_CONTENT_nh  *  pStream  )
{
	int		len		=	-1;

	if  (  !p  ||  !pStream  )  {
		traceLog((TCHAR*)  _T(  "qyntohImLStream failed, p or pStream is null"  )  );
		return  -1;
	}

	memset(  pStream,  0,  sizeof(  pStream[0]  )  );
	memcpy(  pStream,  p,  offsetof(  IM_STREAM_CONTENT_nh,  buf  )  );

	MACRO_ntohl(  pStream->uiType  );
	MACRO_ntohl(  pStream->uiContentType  );
	MACRO_ntohs(  pStream->usStreamLen  );

	//
	pStream->p  =  p  +  offsetof(  IM_STREAM_CONTENT,  buf  );

	//
	if  (  pStream->usStreamLen  >  CONST_bufSize_imStreamContent  )  return  -1;

	len  =  offsetof(  IM_STREAM_CONTENT,  buf  )  +  pStream->usStreamLen;

	return  len;
}
#endif

int  qyhtonImLStream(  long  lhClientVer,  IM_L_STREAM  *  p  )
{
	int		len		=	-1;

	long  tmp_l;
	memcpy(  &tmp_l,  &p->ulStreamLen,  sizeof(  long  )  );
	if  (  tmp_l  >  sizeof(  p->buf  )  )  return  -1;

	len  =  offsetof(  IM_L_STREAM,  buf  )  +  tmp_l;	//  p->ulStreamLen;

	MACRO_htonl(  p->uiType  );
	MACRO_htonl(  p->uiContentType  );
	MACRO_htonl(  p->ulStreamLen  );

	return  len;
}

int  qyntohImLStream(  long  lhClientVer,  char  *  p,  IM_L_STREAM_nh  *  pStream  )
{
	int		len		=	-1;

	if  (  !p  ||  !pStream  )  {
		traceLog((TCHAR*)  _T(  "qyntohImLStream failed, p or pStream is null"  )  );
		return  -1;
	}

	memset(  pStream,  0,  sizeof(  pStream[0]  )  );
	memcpy(  pStream,  p,  offsetof(  IM_L_STREAM_nh,  buf  )  );

	MACRO_ntohl(  pStream->uiType  );
	MACRO_ntohl(  pStream->uiContentType  );
	MACRO_ntohl(  pStream->ulStreamLen  );

	//
	pStream->p  =  p  +  offsetof(  IM_L_STREAM,  buf  );

	//  if  (  p->ulStreamLen  >  sizeof(  p->buf  )  )  return  -1;
	unsigned  long  tmp_ul;
	memcpy(  &tmp_ul,  &pStream->ulStreamLen,  sizeof(  tmp_ul  )  );
	if  (  tmp_ul  >  CONST_bufSize_imLStream  )  return  -1;
	
	//  len  =  offsetof(  IM_L_STREAM,  buf  )  +  p->ulStreamLen;
	len  =  offsetof(  IM_L_STREAM,  buf  )  +  tmp_ul;

	return  len;
}



 int  qyhtonImContentU(  long  lhClientVer,  IM_CONTENTU  *  p  )
{
	int		len		=	-1;

	switch  (  p->uiType  )  {
			case  CONST_imCommType_simpleResp:
				  return  qyhtonImSimpleResp(  lhClientVer,  &p->simpleResp  );
				  //
#if  0
			case  CONST_imCommType_streamContent:
				  return  qyhtonImStreamContent(  lhClientVer,  &p->stream  );
#endif

			case  CONST_imCommType_lStream:
				  return  qyhtonImLStream(  lhClientVer,  &p->lStream  );
				  
			case  CONST_imCommType_htmlContent:
				  traceLogA(  (char*)  "qyhtonImMsgContentU failed, htmlContent"  );
				  break;
			default:
				   traceLogA(  (char*)  "qyhtonImMsgContentU failed, unknown uiType %d",  p->uiType  );
				   break;
	}

//  errLabel:
	return  len;
}

 int  qyntohImContentU(  long  lhClientVer,  char  *  src,  IM_CONTENTU_nh  *  p  )
{
	int				len		=	-1;
	unsigned  int	uiType	=	0;
	
	//  uiType  =  qyntohl(  p->uiType  );
	memcpy(  &uiType,  src,  sizeof(  uiType  )  );
	MACRO_ntohl(  uiType  );

	switch  (  uiType  )  {
			case  CONST_imCommType_simpleResp:
				  memcpy(  &p->simpleResp,  src,  sizeof(  p->simpleResp  )  );
				  return  qyntohImSimpleResp(  lhClientVer,  &p->simpleResp  );
				  //
#if  0
			case  CONST_imCommType_streamContent:
				  //  return  qyntohImStreamContent(  lhClientVer,  &p->stream  );					//  2010/07/10. 这里应该设计一个专门的IM_CONTENTU_ntoh
				  return  qyntohImStreamContent(  lhClientVer,  src,  &p->stream  );				//  
#endif
				  
			case  CONST_imCommType_htmlContent:
				  traceLogA(  (char*)  "qyntohImMsgContentU failed, htmlContent"  );
				  break;
			case  CONST_imCommType_lStream:
				  //  return  qyntohImLStream(  lhClientVer,  &p->lStream  );					//  2010/07/10. 这里应该设计一个专门的IM_CONTENTU_ntoh
				  return  qyntohImLStream(  lhClientVer,  src,  &p->lStream  );					//  
			default:
				    traceLogA(  (char*)  "qyntohImMsgContentU failed, unprocessed type %d",  uiType  );
					break;
	}

//  errLabel:
	return  len;
}



 
 //  2013/02/10
 int  myMACRO_setPtrs(  QY_DMITEM  *  pCONST_fieldIdTable_en,  QY_DMITEM  *  pCONST_regInfo2DbTable,  QY_MESSENGER_REGINFO  &  regInfo,  QNM_FIELD  *  fields_unused  )				
{																								
				int						Mindex		=	0;																											
				QY_DMITEM		*		MpItem		=	NULL;									

				if  (  mycountof(  regInfo.fields  )  ==  CONST_qnmMaxRegFields  &&  mycountof(  regInfo.uiFieldIds  )  ==  CONST_qnmMaxRegFields  )  {						
					memset(  regInfo.fields,  0,  sizeof(  regInfo.fields  )  );																									
					for  (  Mindex  =  0;  Mindex  <  CONST_qnmMaxRegFields;  Mindex  ++  )  {																			
					     regInfo.fields[Mindex].ptr  =  (TCHAR*)_T(  ""  );	 regInfo.fields[Mindex].pName  =  (TCHAR*)_T(  ""  );																	
					}																																				
					for  (  Mindex  =  0;  Mindex  <  mycountof(  regInfo.uiFieldIds  );  Mindex  ++  )  {																
						 if  (  !(  MpItem  =  qyGetDmItemByType(  pCONST_regInfo2DbTable,  regInfo.uiFieldIds[Mindex],  sizeof(  QY_DMITEM  )  )  )  )  continue;		
						 unsigned  int			Mi;																													
						 if  (  (  Mi  =  (  unsigned  int  )MpItem->des  )  >=  CONST_qnmMaxRegFields  )  continue;													
						 regInfo.fields[Mi].pName  =  qyGetDesByType1(  pCONST_fieldIdTable_en,  regInfo.uiFieldIds[Mindex]  );													
						 regInfo.fields[Mi].ptr  =  (  TCHAR  *  )regInfo.u.cols[Mindex];																						
						 regInfo.fields[Mi].bufSize  =  sizeof(  regInfo.u.cols[Mindex]  )  /  sizeof(  TCHAR  );																
						 regInfo.fields[Mi].iDataType  =  (  int  )MpItem->pData;																								
						 //
						 regInfo.fields[Mi].ptr[regInfo.fields[Mi].bufSize  -  1]  =  0;

					}																																							
				} 

				return  0;

 }



 //
 QY_DMITEM  CONST_procOfflineResSubtypeTable[] =
 {
	 {  CONST_procOfflineResSubtype_upload,		(TCHAR*)_T("uploading"),	},
	 {  CONST_procOfflineResSubtype_download,	(TCHAR*)_T("downloading"),	},
	 {  CONST_procOfflineResSubtype_del,		(TCHAR*)_T("del"),	},
	 {	-1,	},
 };



