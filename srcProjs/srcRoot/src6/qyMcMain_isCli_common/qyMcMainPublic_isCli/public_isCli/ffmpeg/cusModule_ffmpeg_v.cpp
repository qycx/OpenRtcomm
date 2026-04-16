
#include	"stdafx.h"
#include	"mytypes.h"
#include	"tmpFfmpegCommon.h"

//
 int qdcInitCompressVideo_ffmpeg(  void  *  pVideoCompressorCfg_reserved,  QY_VIDEO_HEADER  *  pVh_decompress,  QY_VIDEO_HEADER  *  pVh_compress,  QDC_OBJ_INFO  *  pQdcObjInfo  )
  
 {
            int iErr = -1;
            int iFourcc;
            bool bDbg = false;

            CCtxQyMc *pQyMc = g_pQyMc;
            //CCtxQmc *pProcInfo = pQyMc->get_pProcInfo();


            //
            if (pQdcObjInfo->var.pObj != mynull) return -1;

			VIDEO_COMPRESSOR_CFG *pVideoCompressorCfg = ( VIDEO_COMPRESSOR_CFG * )pVideoCompressorCfg_reserved;

            //
            pQdcObjInfo->cfg.v = pVideoCompressorCfg->common;

            //
            pQdcObjInfo->var.pObj = new CQdcObj_ffmpeg();
            if (pQdcObjInfo->var.pObj == mynull) goto errLabel;
            CQdcObj_ffmpeg* pObj; pObj = (CQdcObj_ffmpeg*)pQdcObjInfo->var.pObj;

			{
				CQySyncObj syncObj;
		
				if(syncObj.sync(CONST_mutexName_syncFfmpeg))goto errLabel;


                pObj->m_index_qdcUnit = newQdcUnitIndex();
                if (pObj->m_index_qdcUnit < 0)
                {
                    traceLogA(  (char*)"qdcInitCompressV failed, newQdcUnitIndex failed");
                    goto errLabel;
                }
			}




            //fixed (byte* fourccStr = pVideoCompressorCfg.common.fourccStr)
            {
                iFourcc = fourccStr2i(pVideoCompressorCfg->common.fourccStr);
            }

			//
            int fps; fps = pVideoCompressorCfg->common.usMaxFps_toShareBmp;
            int bitrate; bitrate = pVideoCompressorCfg->common.iAvgBitrate;
			//
            if (encV_init(pObj->m_index_qdcUnit, iFourcc, pVh_decompress->bih.biWidth, pVh_decompress->bih.biHeight, fps,bitrate,bDbg) != 0) return -1;

			//
			pVh_compress->bih = pVh_decompress->bih;

            //
            //pQdcObjInfo.v.iFourcc = iFourcc;

            //
            //pQdcObjInfo.bb_input = ByteBuffer.AllocateDirect(pVh_decompress.bih.biSizeImage);
			pObj->output.iBufSize=CONST_bufSize_transferVideoData;
			pObj->output.pBuf = (char*)mymalloc(CONST_bufSize_transferVideoData);
			if ( pObj->output.pBuf==NULL ) goto errLabel;
			pObj->output.len = 0;
            //pQdcObjInfo.bHeadLen = 1 + 12;


            iErr = 0;
            errLabel:

            if(iErr != 0)
            {
                qdcExitCompressVideo_ffmpeg( pQdcObjInfo);
            }

            return iErr;
        }
        
 int qdcExitCompressVideo_ffmpeg( QOI_common *pQdcObjInfo)
        {
            bool bDbg = true;

#if DEBUG
            if (bDbg)
            {
                qyFuncs.traceLog("qdcExitCompressVideo_android enters");
            }
#endif
            //CCtxQyMc pQyMc = g.g_pQyMc;
            //CCtxQmc pProcInfo = pQyMc.get_pProcInfo();


            if (mynull == pQdcObjInfo->var.pObj) return 0;
            CQdcObj_ffmpeg *pObj = (CQdcObj_ffmpeg*)pQdcObjInfo->var.pObj;


            //
            if (0 != encV_exit(pObj->m_index_qdcUnit, bDbg))
            {
                traceLogA(  (char*)"qdcExitCompressVideo_android: enc_exit failed");
            }

            //
            //pQdcObjInfo.bb_output = null;
			if ( pObj->output.pBuf  )  {
				myfree(pObj->output.pBuf  ); pObj->output.pBuf=mynull;
			}
            //pQdcObjInfo.bb_input = null;

            //
			{		
				CQySyncObj syncObj;
				if(!syncObj.sync(CONST_mutexName_syncFfmpeg )){
					freeQdcUnitIndex(pObj->m_index_qdcUnit);
                    pObj->m_index_qdcUnit = -1;
		
				}
			}

            //
			delete pObj;
            pQdcObjInfo->var.pObj = mynull;


#if DEBUG
            if (bDbg)
            {
                qyFuncs.traceLog("qdcExitCompressVideo_android leaves");
            }
#endif

            return 0;

        }

        int qdcGetSpsPps_ffmpeg( QOI_common *pQdcObjInfo, char * spsBuf, uint *puiSpsSize, char * ppsBuf,  uint *puiPpsSize, char * vps, uint * puiVpsSize)
        {
            int iErr = -1;
#if 0
            ByteBuffer bb;
            bb = ByteBuffer.AllocateDirect(1024);
            int[] lens = new int[3];
#endif
            byte* p;
            int k;
            bool bDbg = false;

            CQdcObj_ffmpeg *pObj = (CQdcObj_ffmpeg*)pQdcObjInfo->var.pObj;

			if (0 != encV_getSpsPps(pObj->m_index_qdcUnit, (byte*)spsBuf, (int*)puiSpsSize,(byte*)ppsBuf,(int*)puiPpsSize,(byte*)vps,(int*)puiVpsSize, bDbg)) return -1;

#if 0
            p = (byte*)bb.GetDirectBufferAddress();
            k = 0;
            //
            switch (pQdcObjInfo.cfg.v.head.iFourcc)
            {
                case Consts.CONST_fourcc_h264:
                    //
                    qyFuncs.mymemcpy(spsBuf, (IntPtr)p, (uint)lens[k]);
                    puiSpsSize = (uint)lens[k];
                    p += lens[k];
                    k++;
                    qyFuncs.mymemcpy(ppsBuf, (IntPtr)p, (uint)lens[k]);
                    puiPpsSize = (uint)lens[k];
                    p += lens[k];
                    //
                    puiVpsSize = 0;
                    //
                    break;
                default:
                    goto errLabel;
            }
#endif

            iErr = 0;
        errLabel:

            return iErr;

        }


        //
        int qdcCompressVideo_ffmpeg(  QDC_OBJ_INFO  *  pQdcObjInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput,  int  iSampleTimeInMs  )

        {
            int iErr = -1;
            //
            bool bDbg = false;
#if DEBUG
            string str;
#endif
            CQdcObj_ffmpeg *pObj = (CQdcObj_ffmpeg*)pQdcObjInfo->var.pObj;

            //
#if 0
            if (pQdcObjInfo.bb_input == null || pQdcObjInfo.bb_output == null) return -1;
            ByteBuffer bb_input = (ByteBuffer)pQdcObjInfo.bb_input;
            ByteBuffer bb_output = (ByteBuffer)pQdcObjInfo.bb_output;
            byte* pBbInput = (byte*)bb_input.GetDirectBufferAddress();
            if (null == pBbInput) goto errLabel;
            byte* pBbOutput = (byte*)bb_output.GetDirectBufferAddress();
            if (null == pBbOutput) goto errLabel;


            if (pBmpInfo_input.biSizeImage > bb_input.Capacity()) goto errLabel;
            qyFuncs.mymemcpy((IntPtr)pBbInput, pInput, (uint)pBmpInfo_input.biSizeImage);

            if (pQdcObjInfo.nLeft_output != 0)
            {
                qyFuncs.showNotification_open(0, 0, 0, "Err: qdcCompressVideo_android; nLeft is not 0");
                goto errLabel;
            }
            int bufSize_output = bb_output.Capacity();
            if (bufSize_output <= pQdcObjInfo.bHeadLen) goto errLabel;
            int len_output0;
            int len_output1;
            int len_output2;
            //
            len_output0 = bufSize_output - pQdcObjInfo.bHeadLen;
            //
            uint len = 0;
            *pBbOutput = pQdcObjInfo.bHeadLen; len = sizeof(byte);
            *(int*)(pBbOutput + len) = len_output0;
#endif
			//
			int bufSize_output=pObj->output.iBufSize;
			//
			bool  bNeed_forceKeyFrame  =  false;
			//
					//  2014/08/25
		if  (  pQdcObjInfo->var.encInfo.bNeed_forceKeyFrame  )  {
			DWORD  dwTickCnt  =  myGetTickCount(  mynull  );
			if  (  dwTickCnt  -   pQdcObjInfo->var.encInfo.dwLastTickCnt_insertKeyFrame1  >  1000  )  {
				pQdcObjInfo->var.encInfo.dwLastTickCnt_insertKeyFrame1  =  dwTickCnt;
				//
				showInfo_open0(0,mynull,_T(  "ffmpeg_enc: insertKeyFrame"  )  );			
				//
				bNeed_forceKeyFrame=true;
			}
		}


            //
			if (0 != encV_data(pObj->m_index_qdcUnit, pInput, pBmpInfo_input->bmiHeader.biSizeImage, (byte*)pObj->output.pBuf, &bufSize_output, bNeed_forceKeyFrame, bDbg))
            {
                traceLogA(  (char*)"qdcCompressVideo_android: enc_data failed");
                goto errLabel;
            }
            //
#if 0
            len = sizeof(byte);
            len_output0 = *(int*)(pBbOutput + len); len += sizeof(int);
            len_output1 = *(int*)(pBbOutput + len); len += sizeof(int);
            len_output2 = *(int*)(pBbOutput + len); len += sizeof(int);
            if (len > pQdcObjInfo.bHeadLen)
            {
                goto errLabel;
            }
#endif
            //
			pObj->output.len = bufSize_output;
			if (pObj->output.len != 0)
            {
                int ii = 0;
            }
            //
#if DEBUG
            if (bDbg)
            {
                str = string.Format("qdcCompressVideo_android: enc_data ok,len_output {0}", pQdcObjInfo.nLeft_output);
                qyFuncs.traceLog(str);
            }
#endif
            //
            int kk;
            
			//
            iErr = 0;
        errLabel:

            return iErr;

        }


//
int  qdcInitDecompressVideo_ffmpeg(  void  *  pVideoCompressorCfg_reserved,  QY_VIDEO_HEADER  *  pVh_compress,  QY_VIDEO_HEADER  *  pVh_decompress,  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
	int iErr = -1;
	bool bDbg = true;

		if(pQdcObjInfo->var.pObj) return -1;

	pQdcObjInfo->var.pObj=new CQdcObj_ffmpeg();
	if ( !pQdcObjInfo->var.pObj ) goto errLabel;
    CQdcObj_ffmpeg* pObj; pObj = (CQdcObj_ffmpeg*)pQdcObjInfo->var.pObj;

	{
		CQySyncObj syncObj;
		if(syncObj.sync(CONST_mutexName_syncFfmpeg))goto errLabel;

		pObj->m_index_qdcUnit=newQdcUnitIndex();
		if(pObj->m_index_qdcUnit<0)goto errLabel;
	}
	//
	pObj->bDec=true;

	//
    VIDEO_COMPRESSOR_CFG* pCfg; pCfg = (VIDEO_COMPRESSOR_CFG*)pVideoCompressorCfg_reserved;
	//
    int  iFourcc; iFourcc = fourccStr2i(pCfg->common.fourccStr);//CONST_fourcc_MJPG;
	//
    bool bUseNv; bUseNv = false;
	if ( iFourcc==CONST_fourcc_h264 )bUseNv = true;


	//
	if(decV_init(pObj->m_index_qdcUnit,iFourcc,bUseNv,bDbg ) ) goto errLabel;
	

	iErr = 0;
errLabel:
	if(iErr ){
		qdcExitCompressAudio_ffmpeg(pQdcObjInfo);
	}
	return iErr;
}


//
int  qdcExitDecompressVideo_ffmpeg(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{
		bool bDbg=true;

	if( !pQdcObjInfo->var.pObj )  return 0;
	CQdcObj_ffmpeg * pObj=(CQdcObj_ffmpeg*)pQdcObjInfo->var.pObj;

	decV_exit(pObj->m_index_qdcUnit,bDbg );
	
	{
		CQySyncObj syncObj;
		if(!syncObj.sync(CONST_mutexName_syncFfmpeg )){
			freeQdcUnitIndex(pObj->m_index_qdcUnit);
			pObj->m_index_qdcUnit=-1;
		}
	}
	
	//
	if(pObj->output.pBuf){
		myfree(pObj->output.pBuf);pObj->output.pBuf=NULL;
	}

	//
	delete pObj;
	pQdcObjInfo->var.pObj=NULL;

	return 0;
}


//
int  qdcDecompressVideo_ffmpeg(  QDC_OBJ_INFO  *  pQdcObjInfo,  BITMAPINFO  *  pBmpInfo_input,  BYTE  *  pInput,  int  iSampleTimeInMs  )
{
	int iErr = -1;
	bool bDbg=false;//true;

	if( !pQdcObjInfo->var.pObj )  return -1;
	CQdcObj_ffmpeg * pObj=(CQdcObj_ffmpeg*)pQdcObjInfo->var.pObj;

	//
	unsigned  int  uiInputLen  =  pBmpInfo_input->bmiHeader.biSizeImage;

	//
	int inputPaddingSize=64;
	int nPktDeced=0;
	int iFmt_dec=0;
	bool bBufTooSmall=false;
	int  iW  =  0;
	int  iH  =  0;

	if(decV_data(pObj->m_index_qdcUnit,pInput,uiInputLen,inputPaddingSize,&nPktDeced,&iFmt_dec,&iW,&iH,NULL,  NULL,  &bBufTooSmall,bDbg )) goto errLabel;

	iErr = 0;
errLabel:
	return iErr;
}



//
//typedef  int  (*PF_qdcDecompressVideoAndOutput)(QDC_OBJ_INFO* pQdcObjInfo, BITMAPINFO* pBmpInfo_input, BYTE* pInput, BITMAPINFO* pBmpInfo_output, BYTE* pOutput);
int  qdcDecompressVideoAndOutput_ffmpeg(QDC_OBJ_INFO* pQdcObjInfo, BITMAPINFO* pBmpInfo_input, BYTE* pInput, BITMAPINFO* pBmpInfo_output, BYTE* pOutput)
{
    int iErr = -1;
    bool bDbg = false;//true;

    if (!pQdcObjInfo->var.pObj)  return -1;
    CQdcObj_ffmpeg* pObj = (CQdcObj_ffmpeg*)pQdcObjInfo->var.pObj;

    //
    unsigned  int  uiInputLen = pBmpInfo_input->bmiHeader.biSizeImage;

    //
    int inputPaddingSize = 64;
    int nPktDeced = 0;
    int iFmt_dec = 0;
    bool bBufTooSmall = false;
    int  iW = 0;
    int  iH = 0;

    //
    byte* decBuf = pOutput;
    int iDecBufSize = pBmpInfo_output->bmiHeader.biSizeImage;

    //
    if (decV_data(pObj->m_index_qdcUnit, pInput, uiInputLen, inputPaddingSize, &nPktDeced, &iFmt_dec, &iW, &iH, decBuf, &iDecBufSize, &bBufTooSmall, bDbg)) goto errLabel;
    //
    if (nPktDeced) {
        //
        pBmpInfo_output->bmiHeader.biSizeImage = iDecBufSize;
    }
    else {
        pBmpInfo_output->bmiHeader.biSizeImage = 0;
    }

    //
    iErr = 0;
errLabel:
    return iErr;
}
