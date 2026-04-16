
#include	"stdafx.h"

#include	<stdlib.h>
#include	<tchar.h>
#include	<stddef.h>
#include	<mmsystem.h>

#include	"qdcOpenCommon.h"

#include "mfxdefs.h"
#include "mfxsplmux.h"
  //#include	"mfxsplmux++.h"
#include	"my_mfxsplmux++.h"

//
int		tmp_showInfo(  TCHAR  *  hint  );
//
 __declspec(  dllexport  )  int  qdcExitSplInfo(  QDC_spl_info  *  pSplInfo  );


//
typedef  struct  __qdcSpl_t			{
				 //
				 //Splitter		*	pSplitter;
				 CMyMFXSplitter	*	pSplitter;
				 //
				 void			*	pMyDataIO;
				 //
				 mfxTrackInfo		audioTrackInfo;
				 int				track_num_a;
				 int				iCodecType_a;
				 int				m_nAudioTracks;
				 
				 //
				 mfxTrackInfo		videoTrackInfo;
				 int				track_num_v;
				 int				iCodecType_v;
				 int				m_nVideoTracks;

				 //
				 BOOL				bQuit;

}		 QDC_spl;


//
class  CMyDataIO	:public MFXDataIO
{
	public:
	CMyDataIO(){  memset(  &m_var,  0,  sizeof(  m_var  )  );	}
    virtual ~CMyDataIO() { }
    virtual mfxI32 Read (mfxBitstream *bs);
    virtual mfxI32 Write (mfxBitstream *bs);
    virtual mfxI64 Seek (mfxI64 offset, mfxSeekOrigin origin);
	//
	struct	{
		QDC_spl_info	*	pSplInfo;
	}						m_var;


};

mfxI32 CMyDataIO::Read (mfxBitstream *outBitStream)
{
	int				iErr  =  -1;
	CMyDataIO  *	pIO  =  (  CMyDataIO  *  )this;
	TCHAR			tBuf[128]	=	_T(  ""  );
	


	if  (  !pIO->m_var.pSplInfo  )  return  0;

#ifdef  _DEBUG
		if  (  outBitStream->DataOffset  )  {
			int  i;
			i  =  1;
		}
		if  (  outBitStream->DataLength  )  {
			int  i;
			i  =  1;
		}
#endif
	
	mfxI32 nBytesRead = 0;
#if  0
    nBytesRead = (mfxI32)fread(outBitStream->Data + outBitStream->DataOffset + outBitStream->DataLength, sizeof(mfxU8),
        outBitStream->MaxLength - outBitStream->DataOffset, !f ? stdin : f);
#endif
	
	//	
	QDC_spl_info		*	pSplInfo	=	(  QDC_spl_info  *  )pIO->m_var.pSplInfo;
	QDC_spl				*	pObj		=	(  QDC_spl  *  )pSplInfo->pObj;
	QDC_MEDIA_data  *  pMediaData  =  (  QDC_MEDIA_data  *  )pIO->m_var.pSplInfo->pMediaDataForSpl_toGet;
	QDC_stream_buf  *  pStreamBuf  =  pSplInfo->cfg.pStreamBuf;

	//
	if  (  !pSplInfo->bInited  )  {
		//
		if  (  pStreamBuf->uiBufSize  <  4  *  sizeof(  pMediaData->buf  )  )  {
			tmp_showInfo(  _T(  "dataIo::Read failed: streamBuf.bufSize < 4 * sizeof(  mediaData.buf  )"  )  );
			goto  errLabel;
		}
		//
		for  (  ;  ;  )  {
			 pMediaData->head.uiLen  =  0;
			 if  (  pSplInfo->cfg.pf_readData(  pSplInfo,  0,  pMediaData  )  )  break;
			 if  (  pMediaData->head.uiLen  >  pStreamBuf->uiBufSize  -  pStreamBuf->uiLen  )  {
				 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "dataIO::Read failed, MediaData.uiLen %d > streamBuf.uiBufSize %d - uiLen %d\n"  ),  pMediaData->head.uiLen,  pStreamBuf->uiBufSize,  pStreamBuf->uiLen  );
				 tmp_showInfo(  tBuf  );
				 goto  errLabel;
			 }
			 //
			 memcpy(  pStreamBuf->pBuf  +  pStreamBuf->uiLen,  pMediaData->buf,  pMediaData->head.uiLen  );
			 pStreamBuf->uiLen  +=  pMediaData->head.uiLen;
			 //
			 continue;
		}

		//
		nBytesRead  =  min(  pStreamBuf->uiLen  -  pStreamBuf->nBytes_processed,  outBitStream->MaxLength - outBitStream->DataOffset  -  outBitStream->DataLength  );		
		memcpy(  outBitStream->Data + outBitStream->DataOffset + outBitStream->DataLength,  pStreamBuf->pBuf  +  pStreamBuf->nBytes_processed,  nBytesRead  );

		pStreamBuf->nBytes_processed  +=  nBytesRead;

		iErr  =  0;  goto  errLabel;

	}



	//  这里因该是streamBuf的填充
	if  (  pStreamBuf->nBytes_processed  >  pStreamBuf->uiLen
		||  pStreamBuf->uiLen  >  pStreamBuf->uiBufSize  )
	{
		goto  errLabel;
	}

	//
	if  (  pStreamBuf->nBytes_processed  
		&&  pStreamBuf->uiLen  ==  pStreamBuf->nBytes_processed  )
	{
		pStreamBuf->uiLen  =  0;
		pStreamBuf->nBytes_processed  =  0;
	}
	//
	BOOL  bNeedRead  =  TRUE;
	//
	if  (  pStreamBuf->uiLen  )  {
		if  (  pStreamBuf->uiBufSize  -  pStreamBuf->uiLen  <  sizeof(  pMediaData->buf  )  )  {
			bNeedRead  =  FALSE;		//  可用空间太小，会造成包无法存入而丢弃，所以不能读了
		}
	}
	if  (  bNeedRead  )  {
		for  (  ;  ;  )  {
			 if  (  pObj->bQuit  )  goto  errLabel;
			 //
			 pMediaData->head.uiLen  =  0;
			 if  (  !pSplInfo->cfg.pf_readData(  pSplInfo,  0,  pMediaData  )  )  break;
			 //
			 if  (  pStreamBuf->uiLen  )  {		
				 //  还有数据，不等了，先处理吧
				 break;
			 }
			 //
			 Sleep(  40  );	
			 continue;
		}
		
		if  (  pMediaData->head.uiLen  )  {
			if  (  pMediaData->head.uiLen  >  pStreamBuf->uiBufSize  -  pStreamBuf->uiLen  )  {	
				OutputDebugString(  _T(  "dataIO::Read failed, MediaData.uiLen > streamBuf.uiBufSize-uiLen\n"  )  );
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "dataIO::Read failed, MediaData.uiLen %d > streamBuf.uiBufSize %d - uiLen %d\n"  ),  pMediaData->head.uiLen,  pStreamBuf->uiBufSize,  pStreamBuf->uiLen  );				 
				tmp_showInfo(  tBuf  );
				goto  errLabel;			 
			}
			memcpy(  pStreamBuf->pBuf  +  pStreamBuf->uiLen,  pMediaData->buf,  pMediaData->head.uiLen  );	
			pStreamBuf->uiLen  +=  pMediaData->head.uiLen;
		}
	}


	nBytesRead  =  min(  pStreamBuf->uiLen  -  pStreamBuf->nBytes_processed,  outBitStream->MaxLength - outBitStream->DataOffset  -  outBitStream->DataLength  );
	memcpy(  outBitStream->Data + outBitStream->DataOffset + outBitStream->DataLength,  pStreamBuf->pBuf  +  pStreamBuf->nBytes_processed,  nBytesRead  );
	pStreamBuf->nBytes_processed  +=  nBytesRead;
	

	iErr  =  0;

errLabel:
	//
	#ifdef  _DEBUG
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "dataIO::Read, %d bytes, iErr %d\n"  ),  nBytesRead,  iErr  );
			OutputDebugString(  tBuf  );	     
			//tmp_showInfo(  tBuf  );
	#endif

	//
    outBitStream->DataLength = nBytesRead;
    return nBytesRead;

}


  mfxI32 CMyDataIO::Write (mfxBitstream *bs)
{
	return  0;
}


mfxI64 CMyDataIO::Seek (mfxI64 offset, mfxSeekOrigin origin)
{
	QDC_spl_info  *  pSplInfo  =  m_var.pSplInfo;

	mfxI64  res  =  -1;
	switch  (  origin  )  {
			case  MFX_SEEK_ORIGIN_BEGIN:
				  if  (  pSplInfo->bInited  )  {
					  return  -1;
				  }
				  //
				  if  (  offset  >  pSplInfo->cfg.pStreamBuf->uiLen  )  {
					  return  -1;
				  }

				  pSplInfo->cfg.pStreamBuf->nBytes_processed  =  offset;				  
				  res  =  0;
				  //
				  break;				  
			case  MFX_SEEK_ORIGIN_CURRENT:
				  #ifdef  _DEBUG
				{
					int  i;
					i  =  1;
				}
				  #endif
				  //
				  res  =  0;
				  //
				  break;
			case  MFX_SEEK_ORIGIN_END:
				  #ifdef  _DEBUG
				{
					int  i;
					i  =  1;
				}
				  #endif
				  //
				  res  =  0;
				  //
				  break;
			default:
				  #ifdef  _DEBUG
				{
					int  i;
					i  =  1;
				}
				  #endif
					break;
	}

	return  res;
}

//
//#define		M_nalType_h264(  p  )	p[2]  ==  1  ?  (  p[3]  &  0x1f  )  :  (  p[4]  &  0x1f  )

__declspec(  dllexport  )  int  qdcSplGetSpsPps(  QDC_spl_info  *  pSplInfo,  char  *  spsBuf,  unsigned  int  *  puiSpsSize,  char  *  ppsBuf,  unsigned  int  *  puiPpsSize,  char  *  kk,  unsigned  int  *  puiKkSize  )
{
	int			iErr	=	-1;
	 unsigned  char  buf[2048];
	 unsigned  int	naluLen  =  0;
	 unsigned  int	uiSpsLen	=	0;
	 unsigned  int	uiPpsLen	=	0;

	 //
	 QDC_spl  *  pObj  =  (  QDC_spl  *  )pSplInfo->pObj;

	 return  parseSpsPps(  CONST_fourcc_h264,  (  char  *  )pObj->videoTrackInfo.Header,  pObj->videoTrackInfo.HeaderLength,  spsBuf,  puiSpsSize,  ppsBuf,  puiPpsSize,  kk,  puiKkSize  );

#if  0

	 if  (  pObj->videoTrackInfo.HeaderLength  >  sizeof(  buf  )  )  return  -1;
	 int  len  =  pObj->videoTrackInfo.HeaderLength;
	 if  (  !len  )  {
		 *puiSpsSize  =  0;
		 *puiPpsSize  =  0;
		 return  0;
	 }
	 memcpy(  buf,  pObj->videoTrackInfo.Header,  len  );
	 
	 
	 int  ii;

	 unsigned  char  *  pStart  =  buf;
	 BOOL				bStart	=	FALSE;
	 BOOL			   bNextNalu  =  FALSE;
	 BOOL				bStartCode_4	=	FALSE;
	 for  (  ii  =  0;  ii  <  len  -  3;  ii  ++  )  {
		  if  (  buf[ii]  ==  0
			  &&  buf[ii  +  1]  ==  0
			  &&  buf[ii  +  2]  ==  0
			  &&  buf[ii  +  3]  ==  1  )
		  {
			  if  (  !bStart  )  {
				  bStart  =  TRUE;
				  pStart  =  buf  +  ii;
				  ii  +=  3;
				  continue;
				  }
			  else  {
					bNextNalu  =  TRUE;
					bStartCode_4  =  TRUE;
			  }
		  }
		  if  (  buf[ii]  ==  0
			  &&  buf[ii  +  1]  ==  0
			  &&  buf[ii  +  2]  ==  1  )
		  {
			  if  (  !bStart  )  {
				  bStart  =  TRUE;
				  pStart  =  buf  +  ii;
				  ii  +=  2;
				  continue;
				  }
			  else  {
				    bNextNalu  =  TRUE;
					bStartCode_4  =  FALSE;
			  }
		  }
		  //
		  if  (  !bNextNalu  )  continue;
		  //
		  naluLen  =  buf  +  ii  -  pStart;
		  if  (  naluLen  >  3  )  {
			  int  nalType  =  M_nalType_h264(  pStart  );
			  switch  (  nalType  )  {
					  case  7:
						     if  (  naluLen  >  *puiSpsSize  )  goto  errLabel;
						     memcpy(  spsBuf,  pStart,  naluLen  );
							 uiSpsLen  =  naluLen;
							 break;
					  case  8:
						    if  (  naluLen  >  *puiPpsSize  )  goto  errLabel;
							memcpy(  ppsBuf,  pStart,  naluLen  );
							uiPpsLen  =  naluLen;
						    break;
					  default:
						     break;
			  }
		  }
		  //
		  bNextNalu  =  FALSE;
		  bStart  =  TRUE;
		  pStart  =  buf  +  ii;
		  if  (  bStartCode_4  )  ii  +=  3;
		  else  ii  +=  2;
		  continue;
	 }

	 //
	 if  (  bStart  )  {
		 naluLen  =  buf  +  len  -  pStart;
		  if  (  naluLen  >  3  )  {
			  int  nalType  =  M_nalType_h264(  pStart  );
			  switch  (  nalType  )  {
					  case  7:
						     if  (  naluLen  >  *puiSpsSize  )  goto  errLabel;
						     memcpy(  spsBuf,  pStart,  naluLen  );
							 uiSpsLen  =  naluLen;
							 break;
					  case  8:
						    if  (  naluLen  >  *puiPpsSize  )  goto  errLabel;
							memcpy(  ppsBuf,  pStart,  naluLen  );
							uiPpsLen  =  naluLen;
						    break;
					  default:
						     break;
			  }
		  }
	 }

	 *puiSpsSize  =  uiSpsLen;
	 *puiPpsSize  =  uiPpsLen;

	 iErr  =  0;
errLabel:
	 
	 //
	 return  iErr;
#endif

 }



__declspec(  dllexport  )  int  qdcInitSplInfo(  QDC_spl_cfg  *  pCfg,  void  *  p0,  void  *  p1,  QDC_spl_info  *  pSplInfo  )
 {
	 int		iErr	=	-1;

	 if  (  !pSplInfo  )  return  -1;
	 if  (  pSplInfo->pObj  )  return  -1;
	 if  (  pSplInfo->bInited  )  return  -1;

	 int		size;
	 QDC_spl  *  pObj  =  NULL;

	 //
	 memcpy(  &pSplInfo->cfg,  pCfg,  sizeof(  pSplInfo->cfg  )  );

	 //
	 size  =  sizeof(  QDC_spl  );
	 pObj  =  (  QDC_spl  *  )malloc(  size  );
	 if  (  !pObj  )  goto  errLabel;
	 memset(  pObj,  0,  size  );
	 pSplInfo->pObj  =  pObj;

	 //
	 if  (  pSplInfo->pMediaDataForSpl_toGet  )  goto  errLabel;
	 pSplInfo->pMediaDataForSpl_toGet  =  malloc(  sizeof(  QDC_MEDIA_data  )  );
	 if  (  !pSplInfo->pMediaDataForSpl_toGet  )  goto  errLabel;

	 //
	 if  (  pSplInfo->pMediaDataForSpl_pkt  )  goto  errLabel;
	 pSplInfo->pMediaDataForSpl_pkt  =  (  QDC_media_data  *  )malloc(  sizeof(  QDC_MEDIA_data  )  );
	 if  (  !pSplInfo->pMediaDataForSpl_pkt  )  goto  errLabel;


	 	 //  params
	//  BUF_pretrans  *  pBufPretrans  =  (  BUF_pretrans  *  )pCfg->pBUF_pretrans;
#if  0
	params.m_pBuffer  =  (  Ipp8u  *  )pBufPretrans->pBuf;
	params.m_iBufferSize  =  (  Ipp64u  )1024  *  1024  *  1024  *  1024;		//  pBufPretrans->uiLen;
	params.m_pQDC_spl_info  =  pSplInfo;
#endif

		try  {
		 pObj->pSplitter  =  new  CMyMFXSplitter;
		 if  (  !pObj->pSplitter  )  goto  errLabel;
		 CMyMFXSplitter  *  pSpl  =  pObj->pSplitter;

		 pObj->pMyDataIO  =  new  CMyDataIO;
		 if  (  !pObj->pMyDataIO  )  goto  errLabel;

		 CMyDataIO  *  pdata_io  =  (  CMyDataIO  *  )pObj->pMyDataIO;
		 pdata_io->m_var.pSplInfo  =  pSplInfo;
		 if  (  pSpl->Init(  *pdata_io  )  )  {
			 goto  errLabel;
		 }

		 //
		 mfxStatus	sts;
		 MFXStreamParams	params;
		 sts  =  pSpl->GetInfo(  params  );
		 if  (  sts  )  {
			 OutputDebugString(  _T(  "GetInfo err\n"  )  );
			 goto  errLabel;

		 }
		 //
		 pObj->track_num_a  =  -1;
		 pObj->track_num_v  =  -1;
		 //
		 int  i;
		 for  (  i  =  0;  i  <  params.NumTracks;  i  ++  )  {
			  if ( params.TrackInfo[i]->Type & MFX_TRACK_ANY_AUDIO) {
				  pObj->m_nAudioTracks ++;
				  //
				  if  (  !pObj->audioTrackInfo.Type  )  {
					  pObj->audioTrackInfo  =  *params.TrackInfo[i];
					  pObj->track_num_a  =  i;
				  }
			  }
			  if (params.TrackInfo[i]->Type & MFX_TRACK_ANY_VIDEO) {
				  pObj->m_nVideoTracks ++;      
				  //
				  if  (  !pObj->videoTrackInfo.Type  )  {
					  pObj->videoTrackInfo  =  *params.TrackInfo[i];
					  pObj->track_num_v  =  i;
					  switch  (  pObj->videoTrackInfo.Type  )  {
							  case  MFX_TRACK_H264:
								    pObj->iCodecType_v  =  CONST_codecType_h264;
									break;
							  default:
								      OutputDebugString(  _T(  "Unprocessed trackType\n"  )  );
									  break;
					  }
				  }
			  }


		 }

	}
	catch  (  ...  )  {
		   goto  errLabel;
	}

	//
	pSplInfo->bInited  =  TRUE;

		//
	 iErr  =  0;
errLabel:
	 if  (  iErr  )  {
		 qdcExitSplInfo(  pSplInfo  );
	 }
	 return  iErr;



}


 __declspec(  dllexport  )  int  qdcExitSplInfo(  QDC_spl_info  *  pSplInfo  )
 {
	 int		iErr	=	-1;

	 //
	 //tmp_showInfo(  _T(  "qdcExitSplInfo enters"  )  );

	 //
	 if  (  !pSplInfo  )  return  0;
	 QDC_spl  *  pObj  =  (  QDC_spl  *  )pSplInfo->pObj;
	 if  (  pObj  )  {
		 //
		 pObj->bQuit  =  TRUE;

		 //UMC_DELETE(pObj->pSplitter);
		 if  (  pObj->pSplitter  )  {
			 CMyMFXSplitter  *  pSplitter  =  pObj->pSplitter;
			 delete  pSplitter;
			 pObj->pSplitter  =  NULL;
		 }

		 if  (  pObj->pMyDataIO  )  {
			 CMyDataIO  *  pDataIO  =  (  CMyDataIO  *  )pObj->pMyDataIO;
			 delete  pDataIO;
			 pObj->pMyDataIO  =  NULL;
		 }

		 //
		 free(  pObj  );	pSplInfo->pObj  =  NULL;
	 }

	 //
	 if  (  pSplInfo->pMediaDataForSpl_pkt  )  {
		 free(  pSplInfo->pMediaDataForSpl_pkt  );  pSplInfo->pMediaDataForSpl_pkt  =  NULL;
	 }

	 //
	 if  (  pSplInfo->pMediaDataForSpl_toGet  )  {
		 free(  pSplInfo->pMediaDataForSpl_toGet  );  pSplInfo->pMediaDataForSpl_toGet  =  NULL;
	 }

	 //
	 pSplInfo->bInited  =  FALSE;

	 //
	 iErr  =  0;

errLabel:

	 //tmp_showInfo(  _T(  "qdcExitSplInfo leaves"  )  );

	 //
	 return  iErr;

 }


   __declspec(  dllexport  )  int  qdcSplGetNextData(  QDC_spl_info  *  pSplInfo,  QDC_media_data  *  pMediaData  )
 {
	 int		iErr	=	-1;
	 	     
	 QDC_spl  *  pObj  =  (  QDC_spl  *  )pSplInfo->pObj;

	 if  (  !pSplInfo->bInited  )  return  -1;
	 if  (  !pMediaData  )  return  -1;

#if  0
	 	 UMC::Status sts;

	 UMC::Splitter  &  Splitter  =  *(  UMC::Splitter  *  )pObj->pSplitter;

	 //  while (UMC::UMC_ERR_NOT_ENOUGH_DATA == (sts = Splitter.GetNextData(&in, videoTrack)))
	 sts = Splitter.GetNextData(&in, pObj->videoTrack);
	 if  (  sts  )  return  -1;
#endif
	 CMyMFXSplitter  *  pSplitter  =  pObj->pSplitter;

	 mfxU32  track_num  =  0;
	 mfxBitstream  bs  =  {};

	 mfxStatus	sts;
	 BOOL		bGot  =  FALSE;

	 //
	 memset(  &pMediaData->head,  0,  sizeof(  pMediaData->head  )  );
	 
	 //
	 sts  =  pSplitter->GetBitstream(  &track_num,  &bs  );
	 switch  (  sts  )  {
		 case  0:
			   if  (  sizeof(  pMediaData->buf  )  <  bs.DataLength  )  {
				   OutputDebugString(  _T(  "err\n"  )  );
			   }
			   else  {
				     if  (  track_num  ==  pObj->track_num_a  )  {
						 OutputDebugString(  _T(  "skipped, a\n"  )  );						 
					 }
					 else  if  (  track_num  ==  pObj->track_num_v  )  {
							   pMediaData->head.iMediumType  =  CONST_mediumType_video;
							   pMediaData->head.iCodecType  =  pObj->iCodecType_v;
					 }
					 //
				     memcpy(  pMediaData->buf,  bs.Data,  bs.DataLength  );
					 pMediaData->head.uiLen  =  bs.DataLength;
					 //
					 pMediaData->head.iSampleTimeInMs  =  bs.TimeStamp;
			   }
			   //  bs.
			   pSplitter->ReleaseBitstream(  &bs  );
			   break;
		 default:  {
			    TCHAR	tBuf[128]  =  _T(  ""  );
				if  (  track_num  ==  pObj->track_num_a  )  {
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "qdcSplGetNextData err, a, sts %d\n"  ),  sts  );
					//  tmp_showInfo(  tBuf  );
					}
				else  if  (  track_num  ==  pObj->track_num_v  )  {
						  #ifdef  _DEBUG
								  int  i;
								  i  =  1;
						  #endif
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "qdcSplGetNextData err, v, sts %d\n"  ),  sts  );
						  tmp_showInfo(  tBuf  );
						  }
				else  {
				}
				}
				break;
	 }

	 //
	 return  0;
 }
