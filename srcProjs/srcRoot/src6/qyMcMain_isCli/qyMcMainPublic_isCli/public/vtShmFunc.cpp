


#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
//#include	"qmcVideoCapture_isCli.h"
//#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"
#include	"qmcDmoPublic.h"
#include	"qmcCmdProc.h"
#include	"tmpCeLib.h"
//  #include	"myfourcc.h"
#include	"module_qisCamCap.h"
#include	"isCmdConst.h"
#include	"qyOpenShellCommon.h"
#include	"qyCusResTemp.h"
#include	"policyAvParams.h"

#include	"qmcVideoCapture_rtsp.h"
#include	"qmcCopyData.h"
#include	"rtspUsrData.h"
//#include	"CtxQmcDvt.h"
#include	"vtShmFunc.h"


int  writeShmPkt(   myDRAW_VIDEO_DATA  *  pPkt,  VT_shm_content  *  pShmContent,  BITMAPINFOHEADER  *  pBih,  unsigned  char  ucCnt_shmPktBufs,  int  index_toWrite  )
{
	BYTE  *  pImg_o  =  NULL;
	TCHAR  tBuf[128]  =  _T(  ""  );

	//
	if  (  ucCnt_shmPktBufs  >  mycountof(  pShmContent->mems  )  )  return  -1;
	if  (  index_toWrite  <  0  ||  index_toWrite  >=  ucCnt_shmPktBufs  )  return  -1;
	//
#ifdef  __DEBUG__
		#if  0
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "writeShmPkt: pkt.dataLen %d"  ),  pPkt->memory.uiBufSize  );
			//_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "writeShmPkt failed, err: bih.%dX%d, biSizeImg %d != pkt.%dX%d, %d"  ),  pBih->biWidth,  pBih->biHeight,  pBih->biSizeImage,  pPkt->bih.biWidth,  pPkt->bih.biHeight,  pPkt->bih.biSizeImage  );		

			showInfo_open0(  0,  0,  tBuf  );
		#endif
#endif
	//
	//  2015/10/17
	if  (  pPkt->usPktResType  ==  CONST_pktResType_sharedTex  )  {
		if  (  pBih->biWidth  !=  pPkt->bih.biWidth
			||  pBih->biHeight  !=  pPkt->bih.biHeight  )  
		{
			showInfo_open0(  0,  0,  _T(  "writeShmPkt failed, bih != pkt.bih"  )  );
			return  -1;
		}
		}
	else  {
		  if  (  pBih->biSizeImage  !=  pPkt->bih.biSizeImage  )  {
			  //
			  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "writeShmPkt failed, err: bih.%dX%d, biSizeImg %d != pkt.%dX%d, %d"  ),  pBih->biWidth,  pBih->biHeight,  pBih->biSizeImage,  pPkt->bih.biWidth,  pPkt->bih.biHeight,  pPkt->bih.biSizeImage  );		
			  showInfo_open0(  0,  0,  tBuf  );
			  //
			  return  -1;	
		  }
	}
	
	//
	if  (  pShmContent->mems[index_toWrite].bDataReady  )  {
		#ifdef  __DEBUG__
				showInfo_open0(  0,  0,  _T(  "writeShmPkt failed, bDataReady is true"  )  );
		#endif
		return  -1;
	}

	//
	pShmContent->mems[index_toWrite].usPktResType  =  pPkt->usPktResType;
	if  (  pPkt->usPktResType  ==  CONST_pktResType_sharedTex  )  {		//2015/10/03
		pShmContent->mems[index_toWrite].pktSharedTexInfo  =  pPkt->sharedTex.pktSharedTexInfo;
		}
	else  {

		  //
		  pImg_o  =  (  BYTE  *  )pShmContent->buf  +  index_toWrite  *  pPkt->bih.biSizeImage;
	
		  //  2015/10/08
		  if  (  pPkt->memory.uiBufSize  <  pPkt->bih.biSizeImage  )  {
			  #ifdef  __DEBUG__
			  #endif
			  showInfo_open0(  0,  0,  _T(  "writeShmPkt failed, pkt.bufSize < biSizeImage"  )  );
			  return  -1;
		  }
		  //
		  memcpy(  pImg_o,  pPkt->memory.m_pBuf,  pPkt->bih.biSizeImage  );
	}
	//
	pShmContent->mems[index_toWrite].bDataReady  =  TRUE;

	//
#ifdef  __DEBUG__
	    if  (  pShmContent->u.dvt.i.ucbShowPostDecVStatus  )  {			
			//showInfo_open0(  0,  0,  _T(  "writeShm ok"  )  );
		}
#endif

	return  0;
}


//
int  shm_img_to_yuv(  void  *  pQdcObjInfoParam,  void  *  pImg,  unsigned  int  cropW,  unsigned  int  cropH,  unsigned  int  pitch,  unsigned  int  w,  unsigned  int  h,  void  *  pYUVWriter_var  )
{
	 QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )pQdcObjInfoParam;

	 if  (  !pYUVWriter_var  )  return  -1;
	 YUVWriter_var  &  m_var  =  *(  YUVWriter_var  *  )pYUVWriter_var;

	 BYTE  *  yuv  =  m_var.outputInfo.pBuf;

	 if  (  !pImg  )  return  -1;
	 if  (  cropW  !=  w  ||  cropH  !=  h  )  return  -1;

	 BITMAPINFOHEADER  bih;
	 makeBmpInfoHeader_yv12(  12,  w,  h,  &bih  );  

	 //	 
	 if  (  bih.biSizeImage  >  m_var.outputInfo.uiOutputSize  )  return  -1;
	 memcpy(  yuv,  pImg,  bih.biSizeImage  );

	 return  0;
}
