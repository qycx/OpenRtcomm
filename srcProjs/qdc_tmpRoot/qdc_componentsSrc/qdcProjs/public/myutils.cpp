
#include	"stdafx.h"
#include	<tchar.h>
#include	<stdlib.h>
#include	<Dshow.h>

#include	"qdcOpenCommon.h"
#include	"qySyncObj.h"
#include	"genericqueue.h"

#include	"myutils.h"

int  tmp_qPostMsg(  Q_ELEM_T  *  pQElem,  unsigned  int  size,  GENERIC_Q  *  pQ  );
 int  tmp_qGetMsg(  GENERIC_Q  *  pQ,  Q_ELEM_T  *  pQElem,  unsigned  int  *  puiSize  );

 //
#ifdef _DEBUG
 //
 #define		CONST_fn_dump_h264_enc		"c:\\tttbbb\\test\\dump_hdEnc.264"
 //
 bool ucb__Dump_h264_enc__=false;

#endif

 //
CMySmplYUVReader::CMySmplYUVReader(  ):CSmplYUVReader(  )
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}



//
#if  0  //  2017/10/07
mfxStatus CMySmplYUVReader::old_Init(const msdk_char *strFileName, const mfxU32 ColorFormat, const mfxU32 numViews, std::vector<msdk_char*> srcFileBuff)
{
    Close();

#if  0
    CHECK_ERROR(_tclen(strFileName), 0, MFX_ERR_NULL_PTR);

    //open source YUV file
    _tfopen_s(&m_fSource, strFileName, _T("rb"));
    CHECK_POINTER(m_fSource, MFX_ERR_NULL_PTR);
#endif

    //set init state to true in case of success
    m_bInited = true;

    if (ColorFormat == MFX_FOURCC_NV12 || ColorFormat == MFX_FOURCC_YV12)
    {
        m_ColorFormat = ColorFormat;
    }
    else
    {
        return MFX_ERR_UNSUPPORTED;    
    }
    
    return MFX_ERR_NONE;
}
#endif

//  2017/10/07
mfxStatus CMySmplYUVReader::Init(std::list<msdk_string> inputs, mfxU32 ColorFormat, bool shouldShiftP010)
{
    Close();

    if( MFX_FOURCC_NV12 != ColorFormat &&
        MFX_FOURCC_YV12 != ColorFormat &&
        MFX_FOURCC_I420 != ColorFormat &&
        MFX_FOURCC_YUY2 != ColorFormat &&
        MFX_FOURCC_RGB4 != ColorFormat &&
        MFX_FOURCC_BGR4 != ColorFormat &&
        MFX_FOURCC_P010 != ColorFormat &&
        MFX_FOURCC_P210 != ColorFormat)
    {
        return MFX_ERR_UNSUPPORTED;
    }

    if(MFX_FOURCC_P010 == ColorFormat)
    {
        shouldShiftP010High = shouldShiftP010;
    }

    if (!inputs.size())
    {
        return MFX_ERR_UNSUPPORTED;
    }

	//  2017/10/07
#if  0
    for (ls_iterator it = inputs.begin(); it != inputs.end(); it++)
    {
        FILE *f = 0;
        MSDK_FOPEN(f, (*it).c_str(), MSDK_STRING("rb"));
        MSDK_CHECK_POINTER(f, MFX_ERR_NULL_PTR);

        m_files.push_back(f);
    }
#endif

	//
    m_ColorFormat = ColorFormat;

    m_bInited = true;

    return MFX_ERR_NONE;
}



#if  0  //  2017/10/07
//
mfxStatus iiCMySmplYUVReader::myLoadNextFrame(  BYTE  *  pInput,  unsigned  int  uiInputSize,  mfxFrameSurface1* pSurface)
{
    // check if reader is initialized
    CHECK_ERROR(m_bInited, false, MFX_ERR_NOT_INITIALIZED);
    CHECK_POINTER(pSurface, MFX_ERR_NULL_PTR);

	//  2015/10/29
	if  (  !pInput  ||  !uiInputSize  )  {
		tmp_showInfo(  _T(  "CMySmplYUVReader::myLoadNextFrame failed, pInput or inputSize is 0"  )  );
		return  MFX_ERR_UNKNOWN;
	}

	//
    mfxU32 nBytesRead;
    mfxU16 w, h, i, pitch;
    mfxU8 *ptr, *ptr2;
    mfxFrameInfo* pInfo = &pSurface->Info;
    mfxFrameData* pData = &pSurface->Data;

    // this reader supports only NV12 mfx surfaces for code transparency, 
    // other formats may be added if application requires such functionality
    if (MFX_FOURCC_NV12 != pInfo->FourCC && MFX_FOURCC_YV12 != pInfo->FourCC)  
    {
        return MFX_ERR_UNSUPPORTED;
    }

    if (pInfo->CropH > 0 && pInfo->CropW > 0) 
    {
        w = pInfo->CropW;
        h = pInfo->CropH;
    } 
    else 
    {
        w = pInfo->Width;
        h = pInfo->Height;
    }

    pitch = pData->Pitch;
    ptr = pData->Y + pInfo->CropX + pInfo->CropY * pData->Pitch;

    // read luminance plane
    for(i = 0; i < h; i++) 
    {
        //  nBytesRead = (mfxU32)fread(ptr + i * pitch, 1, w, m_fSource);
		memcpy(ptr + i * pitch, pInput, w);
		pInput  +=  w;
		nBytesRead  =  w;

        if (w != nBytesRead)
        {
            return MFX_ERR_MORE_DATA;
        }
    }

    // read chroma planes
    switch (m_ColorFormat) // color format of data in the input file
    {
    case MFX_FOURCC_YV12: // YUV420 is implied  
        switch (pInfo->FourCC)
        {
        case MFX_FOURCC_NV12:

            mfxU8 buf[2048]; // maximum supported chroma width for nv12
            mfxU32 j;
            w /= 2;
            h /= 2;            
            ptr = pData->UV + pInfo->CropX + (pInfo->CropY / 2) * pitch;
            if (w > 2048)
            {
                return MFX_ERR_UNSUPPORTED;
            }

			// load V
            for (i = 0; i < h; i++) 
            {
                //  nBytesRead = (mfxU32)fread(buf, 1, w, m_fSource);
				memcpy(  buf,  pInput,  w  );
				pInput  +=  w;
				nBytesRead  =  w;

                if (w != nBytesRead)
                {
                    return MFX_ERR_MORE_DATA;
                }
                for (j = 0; j < w; j++)
                {
                    ptr[i * pitch + j * 2 + 1] = buf[j];
                }
            }

            // load U
            for (i = 0; i < h; i++) 
            {
                //  nBytesRead = (mfxU32)fread(buf, 1, w, m_fSource);
				memcpy(buf,  pInput,  w  );
				pInput  +=  w;
				nBytesRead  =  w;

                if (w != nBytesRead)
                {
                    return MFX_ERR_MORE_DATA;
                }
                for (j = 0; j < w; j++)
                {
                    ptr[i * pitch + j * 2] = buf[j];
                }
            }
        
            break;
        case MFX_FOURCC_YV12:
            w /= 2;
            h /= 2;
            pitch /= 2;

            ptr  = pData->U + (pInfo->CropX / 2) + (pInfo->CropY / 2) * pitch;
            ptr2 = pData->V + (pInfo->CropX / 2) + (pInfo->CropY / 2) * pitch;

            for(i = 0; i < h; i++) 
            {
                //  nBytesRead = (mfxU32)fread(ptr + i * pitch, 1, w, m_fSource);
				memcpy(  ptr2 + i * pitch, pInput, w  );
				pInput  +=  w;
				nBytesRead  =  w;

                if (w != nBytesRead)
                {
                    return MFX_ERR_MORE_DATA;
                }
            }
            for(i = 0; i < h; i++) 
            {
                //  nBytesRead = (mfxU32)fread(ptr2 + i * pitch, 1, w, m_fSource);
				memcpy(ptr + i * pitch, pInput, w);
				pInput  +=  w;
				nBytesRead  =  w;				

                if (w != nBytesRead)
                {
                    return MFX_ERR_MORE_DATA;
                }
            }  

            break;
        default:
            return MFX_ERR_UNSUPPORTED;
            }
        break;
    case MFX_FOURCC_NV12:   
        h /= 2;
        ptr  = pData->UV + pInfo->CropX + (pInfo->CropY / 2) * pitch;
        for(i = 0; i < h; i++) 
        {
            //  nBytesRead = (mfxU32)fread(ptr + i * pitch, 1, w, m_fSource);
			memcpy(ptr + i * pitch, pInput, w);
			pInput  +=  w;
			nBytesRead  =  w;

            if (w != nBytesRead)
            {
                return MFX_ERR_MORE_DATA;
            }
        }             
         
        break;
    default:
        return MFX_ERR_UNSUPPORTED;
    }   


#ifdef  _DEBUG
		#if  0
			 TCHAR  tBuf[128];
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "YUVReader::LoadNextFrame"  )  );
			tmp_showInfo(  tBuf  );
		#endif
#endif


    return MFX_ERR_NONE;    
}
#endif



//  2017/10/07
#define	M_fread(  nBytesRead,  pDst,  size, count, fp  )  {								\
					memcpy(  (  pDst  ),  pInput,  (  size  )  *  (  count  )  );		\
					pInput  +=  (  size  )  *  (  count  );								\
					nBytesRead  =  (  size  )  *  (  count  );  }




//  2017/10/07
mfxStatus CMySmplYUVReader::myLoadNextFrame(  BYTE  *  pInput,  unsigned  int  uiInputSize,  mfxFrameSurface1* pSurface)
{
    // check if reader is initialized
    MSDK_CHECK_ERROR(m_bInited, false, MFX_ERR_NOT_INITIALIZED);
    MSDK_CHECK_POINTER(pSurface, MFX_ERR_NULL_PTR);


	//  2015/10/29
	if  (  !pInput  ||  !uiInputSize  )  {
		tmp_showInfo(  _T(  "CMySmplYUVReader::myLoadNextFrame failed, pInput or inputSize is 0"  )  );
		return  MFX_ERR_UNKNOWN;
	}


	//
    mfxU32 nBytesRead;
    mfxU16 w, h, i, pitch;
    mfxU8 *ptr, *ptr2;
    mfxFrameInfo& pInfo = pSurface->Info;
    mfxFrameData& pData = pSurface->Data;

    mfxU32 vid = pInfo.FrameId.ViewId;

    if (vid > m_files.size())
    {
        return MFX_ERR_UNSUPPORTED;
    }

    if (pInfo.CropH > 0 && pInfo.CropW > 0)
    {
        w = pInfo.CropW;
        h = pInfo.CropH;
    }
    else
    {
        w = pInfo.Width;
        h = pInfo.Height;
    }

    mfxU32 nBytesPerPixel = (pInfo.FourCC == MFX_FOURCC_P010 || pInfo.FourCC == MFX_FOURCC_P210) ? 2 : 1;

    if (MFX_FOURCC_YUY2 == pInfo.FourCC || MFX_FOURCC_RGB4 == pInfo.FourCC || MFX_FOURCC_BGR4 == pInfo.FourCC)
    {
        //Packed format: Luminance and chrominance are on the same plane
        switch (m_ColorFormat)
        {
        case MFX_FOURCC_RGB4:
        case MFX_FOURCC_BGR4:

            pitch = pData.Pitch;
            ptr = MSDK_MIN( MSDK_MIN(pData.R, pData.G), pData.B);
            ptr = ptr + pInfo.CropX + pInfo.CropY * pData.Pitch;

            for(i = 0; i < h; i++)
            {
                //nBytesRead = (mfxU32)fread(ptr + i * pitch, 1, 4*w, m_files[vid]);
				M_fread(  nBytesRead,  ptr + i * pitch, 1, 4*w, m_files[vid])  ;
				
                if ((mfxU32)4*w != nBytesRead)
                {
                    return MFX_ERR_MORE_DATA;
                }
            }
            break;
        case MFX_FOURCC_YUY2:
            pitch = pData.Pitch;
            ptr = pData.Y + pInfo.CropX + pInfo.CropY * pData.Pitch;

            for(i = 0; i < h; i++)
            {
                //nBytesRead = (mfxU32)fread(ptr + i * pitch, 1, 2*w, m_files[vid]);
				M_fread(  nBytesRead,  ptr + i * pitch, 1, 2*w, m_files[vid]  );

                if ((mfxU32)2*w != nBytesRead)
                {
                    return MFX_ERR_MORE_DATA;
                }
            }
            break;
        default:
            return MFX_ERR_UNSUPPORTED;
        }
    }
    else if (MFX_FOURCC_NV12 == pInfo.FourCC || MFX_FOURCC_YV12 == pInfo.FourCC || MFX_FOURCC_P010 == pInfo.FourCC || MFX_FOURCC_P210 == pInfo.FourCC)
    {
        pitch = pData.Pitch;
        ptr = pData.Y + pInfo.CropX + pInfo.CropY * pData.Pitch;

        // read luminance plane
        for(i = 0; i < h; i++)
        {
            //nBytesRead = (mfxU32)fread(ptr + i * pitch, nBytesPerPixel, w, m_files[vid]);
			M_fread(  nBytesRead,  ptr + i * pitch, nBytesPerPixel, w, m_files[vid]);

            if (w != nBytesRead)
            {
                return MFX_ERR_MORE_DATA;
            }

            // Shifting data if required
            if((MFX_FOURCC_P010 == pInfo.FourCC || MFX_FOURCC_P210 == pInfo.FourCC) && shouldShiftP010High)
            {
                mfxU16* shortPtr = (mfxU16*)(ptr + i * pitch);
                for(int idx = 0; idx < w; idx++)
                {
                    shortPtr[idx]<<=6;
                }
            }
        }

        // read chroma planes
        switch (m_ColorFormat) // color format of data in the input file
        {
        case MFX_FOURCC_I420:
        case MFX_FOURCC_YV12:
            switch (pInfo.FourCC)
            {
            case MFX_FOURCC_NV12:

                mfxU8 buf[2048]; // maximum supported chroma width for nv12
                mfxU32 j, dstOffset[2];
                w /= 2;
                h /= 2;
                ptr = pData.UV + pInfo.CropX + (pInfo.CropY / 2) * pitch;
                if (w > 2048)
                {
                    return MFX_ERR_UNSUPPORTED;
                }

                if (m_ColorFormat == MFX_FOURCC_I420) {
                    dstOffset[0] = 0;
                    dstOffset[1] = 1;
                } else {
                    dstOffset[0] = 1;
                    dstOffset[1] = 0;
                }

                // load first chroma plane: U (input == I420) or V (input == YV12)
                for (i = 0; i < h; i++)
                {
                    //  nBytesRead = (mfxU32)fread(buf, 1, w, m_files[vid]);
					M_fread(  nBytesRead,  buf, 1, w, m_files[vid]);
					//
                    if (w != nBytesRead)
                    {
                        return MFX_ERR_MORE_DATA;
                    }
                    for (j = 0; j < w; j++)
                    {
                        ptr[i * pitch + j * 2 + dstOffset[0]] = buf[j];
                    }
                }

                // load second chroma plane: V (input == I420) or U (input == YV12)
                for (i = 0; i < h; i++)
                {

                    //nBytesRead = (mfxU32)fread(buf, 1, w, m_files[vid]);
					M_fread(  nBytesRead,  buf, 1, w, m_files[vid]);

                    if (w != nBytesRead)
                    {
                        return MFX_ERR_MORE_DATA;
                    }
                    for (j = 0; j < w; j++)
                    {
                        ptr[i * pitch + j * 2 + dstOffset[1]] = buf[j];
                    }
                }

                break;
            case MFX_FOURCC_YV12:
                w /= 2;
                h /= 2;
                pitch /= 2;

                if (m_ColorFormat == MFX_FOURCC_I420) {
                    ptr  = pData.U + (pInfo.CropX / 2) + (pInfo.CropY / 2) * pitch;
                    ptr2 = pData.V + (pInfo.CropX / 2) + (pInfo.CropY / 2) * pitch;
                } else {
                    ptr  = pData.V + (pInfo.CropX / 2) + (pInfo.CropY / 2) * pitch;
                    ptr2 = pData.U + (pInfo.CropX / 2) + (pInfo.CropY / 2) * pitch;
                }

                for(i = 0; i < h; i++)
                {

                    //nBytesRead = (mfxU32)fread(ptr + i * pitch, 1, w, m_files[vid]);
					M_fread(  nBytesRead,  ptr + i * pitch, 1, w, m_files[vid]);

                    if (w != nBytesRead)
                    {
                        return MFX_ERR_MORE_DATA;
                    }
                }
                for(i = 0; i < h; i++)
                {
                    //nBytesRead = (mfxU32)fread(ptr2 + i * pitch, 1, w, m_files[vid]);
					M_fread(  nBytesRead,  ptr2 + i * pitch, 1, w, m_files[vid]);

                    if (w != nBytesRead)
                    {
                        return MFX_ERR_MORE_DATA;
                    }
                }
                break;
            default:
                return MFX_ERR_UNSUPPORTED;
            }
            break;
        case MFX_FOURCC_NV12:
        case MFX_FOURCC_P010:
        case MFX_FOURCC_P210:
            if (MFX_FOURCC_P210 != pInfo.FourCC)
            {
                h /= 2;
            }
            ptr  = pData.UV + pInfo.CropX + (pInfo.CropY / 2) * pitch;
            for(i = 0; i < h; i++)
            {
                //nBytesRead = (mfxU32)fread(ptr + i * pitch, nBytesPerPixel, w, m_files[vid]);
				M_fread(  nBytesRead,  ptr + i * pitch, nBytesPerPixel, w, m_files[vid]);

                if (w != nBytesRead)
                {
                    return MFX_ERR_MORE_DATA;
                }

                // Shifting data if required
                if((MFX_FOURCC_P010 == pInfo.FourCC || MFX_FOURCC_P210 == pInfo.FourCC) && shouldShiftP010High)
                {
                    mfxU16* shortPtr = (mfxU16*)(ptr + i * pitch);
                    for(int idx = 0; idx < w; idx++)
                    {
                        shortPtr[idx]<<=6;
                    }
                }
            }

            break;
        default:
            return MFX_ERR_UNSUPPORTED;
        }
    }

    return MFX_ERR_NONE;
}




//
int  CMySmplYUVReader_myLoadNextFrame_msdk(  unsigned  short  usPktResType,  void  *  p0_pInput,  void  *  p1_uiInputSize,  PARAM_CMySmplYUVReader_myLoadNextFrame_msdk  *  pParam  )
{
	if  (  !pParam  )  return  -1;
	CMySmplYUVReader  *  pYUVReader  =  pParam->p;
	if  (  !pYUVReader  )  return  -1;

	if  (  usPktResType  ==  CONST_pktResType_sharedTex  )  {

		//  2015/10/29
		if  (  !pYUVReader->m_var.pf_CMySmplYUVReader_myLoadNextFrame_msdk  )  return  -1;
		//
		if  (  pYUVReader->m_var.pf_CMySmplYUVReader_myLoadNextFrame_msdk(  pYUVReader->m_var.pPipeline,  usPktResType,  p0_pInput,  p1_uiInputSize,  pParam  )  )  {
			return  -1;
		}

		//
		return  0;
	}

	return  pYUVReader->myLoadNextFrame(  (  BYTE  *  )p0_pInput,  (  unsigned  int  )p1_uiInputSize,  pParam->pSurface  );
}

	
//
mfxStatus CMySmplYUVReader::LoadNextFrame(mfxFrameSurface1* pSurface)
{
	mfxStatus  sts_ret  =  MFX_ERR_UNKNOWN;	//  MFX_ERR_MORE_DATA;	//  似乎这个才是标志退出的返回值

#if  0
	mfxStatus  sts  =  MFX_ERR_MORE_DATA;	

	BYTE  *  pInput  =  m_var.m_pInput;
	unsigned  int  uiInputSize  =  m_var.m_uiInputSize;
	TCHAR  tBuf[256];
#endif

	//	
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.m_pQdcObjInfoParam;
	if  (  !pQdcObjInfo  )  {
		tmp_showInfo(  _T(  "CMySmpl::ReadNextFrame failed, pQdcObjInfo is null"  )  );
		goto  errLabel;
	}

	//
	 PARAM_CMySmplYUVReader_myLoadNextFrame_msdk  param;
	 memset(  &param,  0,  sizeof(  param  )  );
	 param.p  =  this;
	 param.pSurface  =  pSurface;
	 if  (  pQdcObjInfo->cfg.v.enc.pf_smplYUVReader_LoadNextFrame(  pQdcObjInfo,  &m_var.old_lPktId,  (  PF_myLoadNextFrame  )CMySmplYUVReader_myLoadNextFrame_msdk,  &param,  &pQdcObjInfo->var.encInfo.bNeed_forceKeyFrame  )  )  {
		 goto  errLabel;
	 }


	 sts_ret  =  MFX_ERR_NONE;

errLabel:

	 return  sts_ret;

}


void CMySmplYUVReader::Close()
{
#if  0
    if (m_fSource)
    {
        fclose(m_fSource);
        m_fSource = NULL;

    }
#endif

    m_bInited = false;
}


CMySmplBitstreamWriter::CMySmplBitstreamWriter(  ):CSmplBitstreamWriter(  )
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CMySmplBitstreamWriter::~CMySmplBitstreamWriter()
{
	int ii = 0;
	Close();

}




mfxStatus CMySmplBitstreamWriter::Init(  void  *  pQdcObjInfoParam)
{
	if  (  !pQdcObjInfoParam  )  return  MFX_ERR_NULL_PTR;
#if  0
    CHECK_POINTER(strFileName, MFX_ERR_NULL_PTR);
    CHECK_ERROR(_tcslen(strFileName), 0, MFX_ERR_NOT_INITIALIZED);
#endif

    Close();

	m_var.m_pQdcObjInfoParam  =  pQdcObjInfoParam;


	//
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.m_pQdcObjInfoParam;

	//
#if  10
	m_var.size_pPkt  =  pQdcObjInfo->cfg.v.size_pCurPkt;
	if  (  m_var.pPkt  )  {
		tmp_showInfo(  _T(  "encPipeline::InitWriter failed, fileWriter.pPkt is not null"  )  );
		return  MFX_ERR_UNKNOWN;
	}
	m_var.pPkt  =  malloc(  m_var.size_pPkt  );
	if  (  !m_var.pPkt  )  {
		tmp_showInfo(  _T(  "encPipeline::InitWriter failed, fileWriter.pPkt malloc failed"  )  );
		return  MFX_ERR_UNKNOWN;
	}
	memset(  m_var.pPkt,  0,  m_var.size_pPkt  );	//  2015/02/08
#endif

#ifdef _DEBUG  
    //init file to write encoded data
	if ( ucb__Dump_h264_enc__ ) {
    //_tfopen_s(&m_fSource, strFileName, _T("wb+"));
	_tfopen_s(&m_fSource, _T(CONST_fn_dump_h264_enc), _T("wb+"));
    CHECK_POINTER(m_fSource, MFX_ERR_NULL_PTR);
	}
#endif

    //set init state to true in case of success
    m_bInited = true;
    return MFX_ERR_NONE;
}


 mfxStatus CMySmplBitstreamWriter::Init(const msdk_char *strFileName)
 {
	 if  (  !m_var.m_pQdcObjInfoParam  )  {
		 #ifdef  _DEBUG
				 OutputDebugString(  _T(  "CMySmplBitstreamWriter::Init failed, m_var.pQdcObjInfo is null\n"  )  );
		 #endif
		 return  MFX_ERR_UNKNOWN;
	 }

	 return  Init(  m_var.m_pQdcObjInfoParam  );
 }

mfxStatus CMySmplBitstreamWriter::WriteNextFrame(mfxBitstream *pMfxBitstream, bool isPrint)
{    
    // check if writer is initialized
    CHECK_ERROR(m_bInited, false, MFX_ERR_NOT_INITIALIZED);
    CHECK_POINTER(pMfxBitstream, MFX_ERR_NULL_PTR);

    mfxU32 nBytesWritten = 0;


#ifdef _DEBUG
	if(ucb__Dump_h264_enc__ ){
	//  nBytesWritten = (mfxU32)fwrite(pMfxBitstream->Data + pMfxBitstream->DataOffset, 1, pMfxBitstream->DataLength, m_fSource);
		(mfxU32)fwrite(pMfxBitstream->Data + pMfxBitstream->DataOffset, 1, pMfxBitstream->DataLength, m_fSource);
	}
#endif

	//
	if  (  m_var.m_pQdcObjInfoParam  )  {
		QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.m_pQdcObjInfoParam;
#if  0
		unsigned  char  ucb__USE_hdEnc_conf__  =  pQdcObjInfo->cfg.enc.ucb__USE_hdEnc_conf__;
		//
		if  (  !ucb__USE_hdEnc_conf__  )  {	
			int  outputIndex;
			outputIndex  =  qdcFindOutputIndex(  m_var.m_pQdcObjInfoParam  );
			qdcOutput(  m_var.m_pQdcObjInfoParam,  outputIndex,  (  char  *  )(  pMfxBitstream->Data + pMfxBitstream->DataOffset  ),  pMfxBitstream->DataLength  );
			}
		else  
#endif
		{
			  //  2014/04/03
			  if  (  m_var.m_pQdcObjInfoParam  )  {		  
				  if  (  pQdcObjInfo->var.ucbTransformFuncsOk  )  {
					  char  *  pInput  =  (  char  *  )(  pMfxBitstream->Data + pMfxBitstream->DataOffset  );
					  int  inputSize  =  pMfxBitstream->DataLength;
					  int  iSampleTimeInMs  =  pMfxBitstream->DecodeTimeStamp  /  1000;
					  //
					  unsigned  int  uiPts  =  0;  //  2016/12/09
					  //
					  pQdcObjInfo->cfg.v.enc.pf_doPostEnc(  pQdcObjInfo,  pInput,  inputSize,  iSampleTimeInMs,  uiPts,  m_var.pPkt  );		  
				  }	
			  }

		}	
		nBytesWritten  =  pMfxBitstream->DataLength;
	}

    CHECK_NOT_EQUAL(nBytesWritten, pMfxBitstream->DataLength, MFX_ERR_UNDEFINED_BEHAVIOR);   

    // mark that we don't need bit stream data any more
    pMfxBitstream->DataLength = 0;

    m_nProcessedFramesNum++;

    // print encoding progress to console every certain number of frames (not to affect performance too much)
    if (isPrint && 0 == (m_nProcessedFramesNum - 1) % 100)
    {
        _tcprintf(_T("Frame number: %hd\r"), m_nProcessedFramesNum); 
    }    

#ifdef  _DEBUG
		#if  0
			TCHAR  tBuf[128];
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "BitstreamWriter::WriteNextFrame"  )  );
			tmp_showInfo(  tBuf  );
		#endif
#endif


    return MFX_ERR_NONE;
}

void CMySmplBitstreamWriter::Close()
{
	if  (  m_var.pPkt  )  {
		free(  m_var.pPkt  );  m_var.pPkt  =  NULL;
	}

	//
    if (m_fSource)
    {
        fclose(m_fSource);
        m_fSource = NULL;
    }

    m_bInited = false;
    m_nProcessedFramesNum = 0;
}


CMySmplBitstreamReader::CMySmplBitstreamReader(  ):	CSmplBitstreamReader(  )
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}



void CMySmplBitstreamReader::Close()
{
#if  0
    if (m_fSource)
    {
        fclose(m_fSource);
        m_fSource = NULL;
    }
#endif

    m_bInited = false;
}


mfxStatus CMySmplBitstreamReader::Init(const TCHAR *strFileName)
{
#if  0
    CHECK_POINTER(strFileName, MFX_ERR_NULL_PTR);
    CHECK_ERROR(_tcslen(strFileName), 0, MFX_ERR_NOT_INITIALIZED);
#endif

	//
    Close();

#if  0
    //open file to read input stream
    _tfopen_s(&m_fSource, strFileName, _T("rb"));
    CHECK_POINTER(m_fSource, MFX_ERR_NULL_PTR);
#endif

    m_bInited = true;
    return MFX_ERR_NONE;
}

#if  0
mfxStatus CMySmplBitstreamReader::ReadNextFrame(mfxBitstream *pBS)
{
    MSDK_CHECK_POINTER(pBS, MFX_ERR_NULL_PTR);
    pBS->DataFlag = MFX_BITSTREAM_COMPLETE_FRAME;

    if (m_lastBs.Data == NULL)
    {
        //alloc same bitstream
        m_bsBuffer.resize(pBS->MaxLength);
        m_lastBs.Data =  &m_bsBuffer.front();
        m_lastBs.MaxLength = pBS->MaxLength;
    }

    //checking for available nalu
    int nNalu;
    int pos2ndNaluStart = 0;
    //check nalu in input bs, it always=1 if decoder didnt take a frame
    if ((nNalu = FindSlice(pBS, pos2ndNaluStart)) < 1)
    {
        //copy nalu from internal buffer
        if ((nNalu = FindSlice(&m_lastBs, pos2ndNaluStart)) < 2)
        {
            //  mfxStatus sts = CSmplBitstreamReader::ReadNextFrame(&m_lastBs);
			mfxStatus sts = ReadNextTotalFrame_func(&m_lastBs);
			//
            if (MFX_ERR_MORE_DATA == sts)
            {
                //lets feed last nalu if present
                if (nNalu == 1)
                {
                    sts = MoveMfxBitstream(pBS, &m_lastBs, m_lastBs.DataLength);
                    MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);

                    return MFX_ERR_NONE;
                }

                return MFX_ERR_MORE_DATA;
            }
            //buffer is to small to accept whole frame
            MSDK_CHECK_NOT_EQUAL(FindSlice(&m_lastBs, pos2ndNaluStart) == 2, true, MFX_ERR_NOT_ENOUGH_BUFFER);
        }
        mfxU32 naluLen = pos2ndNaluStart-m_lastBs.DataOffset;
        mfxStatus sts = MoveMfxBitstream(pBS, &m_lastBs, naluLen);
        MSDK_CHECK_RESULT(sts, MFX_ERR_NONE, sts);
    }

    return MFX_ERR_NONE;
}
#endif



  mfxStatus CMySmplBitstreamReader::ReadNextFrame_func(mfxBitstream *pBS)
{
    CHECK_POINTER(pBS, MFX_ERR_NULL_PTR);
    CHECK_ERROR(m_bInited, false, MFX_ERR_NOT_INITIALIZED);

#ifdef  _DEBUG
		//OutputDebugString(  _T(  "MySmplBitstreamReader::ReadNextFrame_func called\n"  )  );
#endif

	//
    mfxU32 nBytesRead = 0;

	if  (  pBS->DataOffset  )  {
	    memcpy(pBS->Data, pBS->Data + pBS->DataOffset, pBS->DataLength);
	    pBS->DataOffset = 0;
	}


	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.m_pQdcObjInfoParam;
	if  (  !pQdcObjInfo  )  {
		tmp_showInfo(  _T(  "CMySmpl::ReadNextFrame failed, pQdcObjInfo is null"  )  );
		return    MFX_ERR_UNKNOWN;
	}


	 //
	 unsigned  int  uiToInMs  =  0;
#ifdef  _DEBUG
		//uiToInMs  =  2000;
		//  for test
#endif
	 //
	 nBytesRead  =  pBS->MaxLength - pBS->DataLength;
	 unsigned  int  uiSampleTimeInMs  =  0;
	 if  (  pQdcObjInfo->cfg.v.dec.pf_smplBitstreamReader_ReadNextFrame_func(  pQdcObjInfo,  &m_var.old_lPktId,  uiToInMs,  (  char  *  )(  pBS->Data  +  pBS->DataLength  ),  &nBytesRead,  &uiSampleTimeInMs  )  )  {
		 return  MFX_ERR_UNKNOWN;
	 }
	 pBS->DataLength += nBytesRead;    

	//
    return MFX_ERR_NONE;
}


////
mfxStatus CMySmplBitstreamReader::ReadNextFrame(  mfxBitstream *pBS)
{
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.m_pQdcObjInfoParam;
	if  (  !pQdcObjInfo  )  {
		tmp_showInfo(  _T(  "CMySmpl::ReadNextFrame failed, pQdcObjInfo is null"  )  );
		return    MFX_ERR_UNKNOWN;
	}
	QDC_OBJ_trans	*	pObj	=	(  QDC_OBJ_trans  *  )pQdcObjInfo->var.pObj;
	//CMyDecPipeline  *  pPipeline  =  (  CMyDecPipeline  *  )pObj->pPipeline;
	int  i;
	TCHAR	tBuf[128];
	mfxStatus  sts;

	//
	if  (  !pQdcObjInfo->var.ucbTransformFuncsOk  )  return  MFX_ERR_UNKNOWN;

	//
	if  (  pBS->DataOffset  )  {
	    memcpy(pBS->Data, pBS->Data + pBS->DataOffset, pBS->DataLength);
	    pBS->DataOffset = 0;
	}

	//
	if  (  !pObj->common.bInited2  )  {
		int  nSize  =  pBS->MaxLength  -  pBS->DataLength;
		if  (  pQdcObjInfo->cfg.v.pf_transformGetSpsPps(  pQdcObjInfo->cfg.v.uiTransformType_pParent,  pQdcObjInfo->cfg.v.pParent_transform,  pQdcObjInfo->cfg.v.iDecParam_index_pMems_from,  (  char  *  )(pBS->Data  +  pBS->DataLength),  (  unsigned  int  *  )&nSize  )  )  return  MFX_ERR_UNKNOWN;
		pBS->DataLength  +=  nSize;
		//
		#if  0
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Decline: spsPpsLen %d"  ),  nSize  );
			 tmp_showInfo(  tBuf  );	
		#endif
	}

	

	//
	sts  =  this->ReadNextFrame_func(  pBS  );
	return  sts;
}




////


#ifdef  _DEBUG
		//  #define		__TEST_save__
#endif


CMySmplYUVWriter::CMySmplYUVWriter(  ):CSmplYUVWriter(  )
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CMySmplYUVWriter::Close()
{   
	if  (  m_var.pPkt  )  {
		QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.pQdcObjInfoParam;
		if  (  pQdcObjInfo  )  {
			if  (  pQdcObjInfo->cfg.v.pf_clean_myDRAW_VIDEO_DATA  )  {
				pQdcObjInfo->cfg.v.pf_clean_myDRAW_VIDEO_DATA(  m_var.pPkt,  _T(  "YUVWriter close"  )  );
			}
		}
		//
		free(  m_var.pPkt  );  m_var.pPkt  =  NULL;
	}

	//
#ifdef  __TEST_save__
    if (m_fDest)
    {
        fclose(m_fDest);
        m_fDest = NULL;
    } 
#endif

	m_numCreatedFiles = 0;
 
    m_bInited = false;
}



//  mfxStatus CMySmplYUVWriter::Init(const TCHAR *strFileName)
mfxStatus CMySmplYUVWriter::Init(const msdk_char *strFileName, const mfxU32 numViews)
{
#if  0
    CHECK_POINTER(strFileName, MFX_ERR_NULL_PTR);
    CHECK_ERROR(_tcslen(strFileName), 0, MFX_ERR_NOT_INITIALIZED);    
#endif

    Close();  

   if (!m_bIsMultiView)
    {
#ifdef  __TEST_save__
        MSDK_FOPEN(m_fDest, strFileName, MSDK_STRING("wb"));
        MSDK_CHECK_POINTER(m_fDest, MFX_ERR_NULL_PTR);
#endif
        ++m_numCreatedFiles;
    }
    else if (m_bIsMultiView)
    {
        mfxU32 i;
        //  m_fDestMVC = new FILE*[numViews];
        for (i = 0; i < numViews; ++i)
        {
#if  0
            MSDK_FOPEN(m_fDestMVC[i], FormMVCFileName(strFileName, i).c_str(), MSDK_STRING("wb"));
            MSDK_CHECK_POINTER(m_fDestMVC[i], MFX_ERR_NULL_PTR);
#endif
            ++m_numCreatedFiles;
        }        
    }

    //
    m_bInited = true;

    return MFX_ERR_NONE;
}


//  2015/01/17
#if 0
#define		old_CMySmplYUVWriter_qdcOutput(  pOutput,  uiOutputSizeParam  )  {													\
				if  (  (  uiOutputSizeParam  )  +  m_var.outputInfo.DataOffset  +  m_var.outputInfo.len  >  m_var.outputInfo.uiOutputSize    )  {				\
					m_var.outputInfo.bBufTooSmall  =  TRUE;																	\
					}																										\
				else  {																										\
                      memcpy(  m_var.outputInfo.pBuf  +  m_var.outputInfo.DataOffset  +  m_var.outputInfo.len,  (  pOutput  ),  (  uiOutputSizeParam  )  );	\
					  m_var.outputInfo.len  +=  (  uiOutputSizeParam  );													\
				}  }
#endif



#if  0	//  2015/01/11
 int  iimsdk_surface_to_yuv(  void  *  pQdcObjInfoParam,  void  *  pSurfaceParam,  unsigned  int  cropW,  unsigned  int  cropH,  unsigned  int  pitch,  unsigned  int  imgW,  unsigned  int  imgH,  void  *  pYUVWriter_var  )
{	
	int  iErr  =  -1;
	mfxFrameSurface1 *pSurface  =  (  mfxFrameSurface1 *)pSurfaceParam;
	YUVWriter_var  &m_var  =  *(  YUVWriter_var  *  )pYUVWriter_var;
	
	//
    mfxFrameInfo *pInfo = &pSurface->Info;
    mfxFrameData *pData = &pSurface->Data;
	if  (  !pInfo  ||  !pData  )  return  -1;
	
	mfxU32 i, j, h, w;   

	
	int  minW,  minH;
    switch (pInfo->FourCC)
    {
    case MFX_FOURCC_NV12:
		minH  =  min(  pInfo->CropH,  imgH  );
		minW  =  min(  pInfo->CropW,  imgW  );
        for (i = 0; i < minH; i++)
        {
#if  0
            CHECK_NOT_EQUAL(
                fwrite(pData->Y + (pInfo->CropY * pData->Pitch + pInfo->CropX)+ i * pData->Pitch, 1, pInfo->CropW, m_fDest), 
                pInfo->CropW, MFX_ERR_UNDEFINED_BEHAVIOR);
#else
			m_var.outputInfo.DataOffset  =  imgW  *  i;	//  pInfo->Width  *  i;
			m_var.outputInfo.len  =  0;
			CMySmplYUVWriter_qdcOutput(  (  char  *  )(  pData->Y + (pInfo->CropY * pData->Pitch + pInfo->CropX)+ i * pData->Pitch  ),  minW  );  
#endif
        }

		//
		h = imgH  /  2;	//  pInfo->Height / 2;
		w = imgW;		//  pInfo->Width;

		m_var.outputInfo.DataOffset  =  imgW  *  imgH;	//  pInfo->Width  *  pInfo->Height;
		m_var.outputInfo.len  =  0;
        for (i = 0; i < h; i++)
        {
			if  (  i  >=  pInfo->CropH  /  2  )  break;

            for (j = 1; j < w; j += 2)
            {
#if  0
                CHECK_NOT_EQUAL(
                    fwrite(pData->UV + (pInfo->CropY * pData->Pitch / 2 + pInfo->CropX) + i * pData->Pitch + j, 1, 1, m_fDest),
                    1, MFX_ERR_UNDEFINED_BEHAVIOR);
#else
				//  CMySmplYUVWriter_qdcOutput(  (  char  *  )(  pData->UV + (pInfo->CropY * pData->Pitch / 2 + pInfo->CropX) + i * pData->Pitch + j  ),  1  );
				BYTE  b  =  0;
				if  (  j  <  pInfo->CropW  )  b  =  *(  char  *  )(  pData->UV + (pInfo->CropY * pData->Pitch / 2 + pInfo->CropX) + i * pData->Pitch + j  );
				CMySmplYUVWriter_qdcOutput(  (  char  *  )&b,  1  );
#endif
            }
        }

		//
		m_var.outputInfo.DataOffset  =  imgW  *  imgH  *  5  /  4;	//  pInfo->Width  *  pInfo->Height  *  5  /  4;
		m_var.outputInfo.len  =  0;
		for (i = 0; i < h; i++)
        {
			if  (  i  >=  pInfo->CropH  /  2  )  break;

            for (j = 0; j < w; j += 2)
            {
#if  0
                CHECK_NOT_EQUAL(
                    fwrite(pData->UV + (pInfo->CropY * pData->Pitch / 2 + pInfo->CropX)+ i * pData->Pitch + j, 1, 1, m_fDest),
                    1, MFX_ERR_UNDEFINED_BEHAVIOR);
#else
				//  CMySmplYUVWriter_qdcOutput(  (  char  *  )(  pData->UV + (pInfo->CropY * pData->Pitch / 2 + pInfo->CropX)+ i * pData->Pitch + j  ),  1  );
				BYTE  b  =  0;
				if  (  j  <  pInfo->CropW  )  b  =  *(  char  *  )(  pData->UV + (pInfo->CropY * pData->Pitch / 2 + pInfo->CropX)+ i * pData->Pitch + j  );
				CMySmplYUVWriter_qdcOutput(  (  char  *  )&b,  1  );
#endif
            }
        }

		//
		if  (  m_var.outputInfo.bBufTooSmall  )  {
			TCHAR  tBuf[128];
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "yuvWrite::write err, bufTooSmall. bufSize %d, w %d, h %d"  ),  m_var.outputInfo.uiOutputSize,  pInfo->Width,  pInfo->Height  );
			tmp_showInfo(  tBuf  );
			OutputDebugString(  _T(  "qdcSetOutput failed: uiOutputSize too big\n"  )  );							
		}

		break;
	default:
			break;
	}
    
	iErr  =  0;
	
errLabel:

	return  iErr;

}
#endif


//  2015/01/17
#if  0
//  mfxStatus CSmplYUVWriter::WriteNextFrame(mfxFrameSurface1 *pSurface)
int  old_msdk_surface_to_yuv(  void  *  pQdcObjInfoParam,  void  *  pSurfaceParam,  unsigned  int  cropW,  unsigned  int  cropH,  unsigned  int  pitch,  unsigned  int  imgW,  unsigned  int  imgH,  void  *  pYUVWriter_var  )
{
	int  iErr  =  -1;
	mfxFrameSurface1 *pSurface  =  (  mfxFrameSurface1 *)pSurfaceParam;
	YUVWriter_var  &m_var  =  *(  YUVWriter_var  *  )pYUVWriter_var;
	
	//  2015/01/15
	BOOL  m_bIsMultiView  =  FALSE;

    //MSDK_CHECK_ERROR(m_bInited, false,   MFX_ERR_NOT_INITIALIZED);
    //MSDK_CHECK_POINTER(pSurface,         MFX_ERR_NULL_PTR);

    mfxFrameInfo *pInfo = &pSurface->Info;
    mfxFrameData *pData = &pSurface->Data;
    //MSDK_CHECK_POINTER(pData, MFX_ERR_NULL_PTR);
	if  (  !pInfo  ||  !pData  )  return  -1;

	if  (  pInfo->FourCC  !=  MFX_FOURCC_NV12  )  {
		tmp_showInfo(  _T(  "msdk_surface_to_yuv, info.fourcc is not nv12, not supported"  )  );
		return  -1;
	}

    mfxU32 i, j, h, w;
    mfxU32 vid = pSurface->Info.FrameId.ViewId;

	//
	int  minW,  minH;

    switch (pInfo->FourCC)
    {
        case MFX_FOURCC_YV12:
        case MFX_FOURCC_NV12:
			//
			minH  =  min(  pInfo->CropH,  imgH  );
			minW  =  min(  pInfo->CropW,  imgW  );
			//
        for (i = 0; i < minH; i++)
        {
            if (!m_bIsMultiView)
            {
#if  0
                MSDK_CHECK_NOT_EQUAL(
                    fwrite(pData->Y + (pInfo->CropY * pData->Pitch + pInfo->CropX)+ i * pData->Pitch, 1, pInfo->CropW, m_fDest),
                    pInfo->CropW, MFX_ERR_UNDEFINED_BEHAVIOR);
#else

				m_var.outputInfo.DataOffset  =  imgW  *  i;	//  pInfo->Width  *  i;	
				m_var.outputInfo.len  =  0;			
				CMySmplYUVWriter_qdcOutput(  (  char  *  )(  pData->Y + (pInfo->CropY * pData->Pitch + pInfo->CropX)+ i * pData->Pitch  ),  minW  );  

#endif

            }
            else
            {
#if  0
                MSDK_CHECK_NOT_EQUAL(
                    fwrite(pData->Y + (pInfo->CropY * pData->Pitch + pInfo->CropX)+ i * pData->Pitch, 1, pInfo->CropW, m_fDestMVC[vid]),
                    pInfo->CropW, MFX_ERR_UNDEFINED_BEHAVIOR);
#else
				goto  errLabel;
#endif
            }
        }
        break;
        default:
            return MFX_ERR_UNSUPPORTED;
    }
    switch (pInfo->FourCC)
    {
#if  0
        case MFX_FOURCC_YV12:
        for (i = 0; i < (mfxU32) pInfo->CropH/2; i++)
        {
            MSDK_CHECK_NOT_EQUAL(
                fwrite(pData->U + (pInfo->CropY * pData->Pitch / 2 + pInfo->CropX / 2)+ i * pData->Pitch / 2, 1, pInfo->CropW/2, m_fDest),
                (mfxU32)pInfo->CropW/2, MFX_ERR_UNDEFINED_BEHAVIOR);
        }
        for (i = 0; i < (mfxU32)pInfo->CropH/2; i++)
        {
            MSDK_CHECK_NOT_EQUAL(
                fwrite(pData->V + (pInfo->CropY * pData->Pitch / 2 + pInfo->CropX / 2)+ i * pData->Pitch / 2, 1, pInfo->CropW/2, m_fDest),
                (mfxU32)pInfo->CropW/2, MFX_ERR_UNDEFINED_BEHAVIOR);
        }
        break;
#endif
        case MFX_FOURCC_NV12:
			//
#if  0
        h = pInfo->CropH / 2;
        w = pInfo->CropW;
#else
		h = imgH  /  2;	//  pInfo->Height / 2;
		w = imgW;		//  pInfo->Width;

		m_var.outputInfo.DataOffset  =  imgW  *  imgH;	//  pInfo->Width  *  pInfo->Height;
		m_var.outputInfo.len  =  0;
#endif
		        for (i = 0; i < h; i++)
        {
			//
			if  (  i  >=  pInfo->CropH  /  2  )  break;

            for (j = 1; j < w; j += 2)
            {
                if (!m_bIsMultiView)
                {
#if  0
                    MSDK_CHECK_NOT_EQUAL(
                        fwrite(pData->UV + (pInfo->CropY * pData->Pitch / 2 + pInfo->CropX)+ i * pData->Pitch + j, 1, 1, m_fDest),
                        1, MFX_ERR_UNDEFINED_BEHAVIOR);
#else

					//  CMySmplYUVWriter_qdcOutput(  (  char  *  )(  pData->UV + (pInfo->CropY * pData->Pitch / 2 + pInfo->CropX) + i * pData->Pitch + j  ),  1  );			
					BYTE  b  =  0;
					if  (  j  <  pInfo->CropW  )  b  =  *(  char  *  )(  pData->UV + (pInfo->CropY * pData->Pitch / 2 + pInfo->CropX) + i * pData->Pitch + j  );
					CMySmplYUVWriter_qdcOutput(  (  char  *  )&b,  1  );

#endif
                }
                else
                {
					#if  0
                    MSDK_CHECK_NOT_EQUAL(
                        fwrite(pData->UV + (pInfo->CropY * pData->Pitch / 2 + pInfo->CropX)+ i * pData->Pitch + j, 1, 1, m_fDestMVC[vid]),
                        1, MFX_ERR_UNDEFINED_BEHAVIOR);
					#else
						goto  errLabel;
					#endif
                }
            }
        }
				
		//
		m_var.outputInfo.DataOffset  =  imgW  *  imgH  *  5  /  4;	//  pInfo->Width  *  pInfo->Height  *  5  /  4;
		m_var.outputInfo.len  =  0;

		//
        for (i = 0; i < h; i++)
        {
			//
			if  (  i  >=  pInfo->CropH  /  2  )  break;

			//
            for (j = 0; j < w; j += 2)
            {
                if (!m_bIsMultiView)
                {
#if  0
                    MSDK_CHECK_NOT_EQUAL(
                        fwrite(pData->UV + (pInfo->CropY * pData->Pitch / 2 + pInfo->CropX) + i * pData->Pitch + j, 1, 1, m_fDest),
                        1, MFX_ERR_UNDEFINED_BEHAVIOR);
#else

					//  CMySmplYUVWriter_qdcOutput(  (  char  *  )(  pData->UV + (pInfo->CropY * pData->Pitch / 2 + pInfo->CropX)+ i * pData->Pitch + j  ),  1  );
					BYTE  b  =  0;
					if  (  j  <  pInfo->CropW  )  b  =  *(  char  *  )(  pData->UV + (pInfo->CropY * pData->Pitch / 2 + pInfo->CropX)+ i * pData->Pitch + j  );
					CMySmplYUVWriter_qdcOutput(  (  char  *  )&b,  1  );

#endif
                }
                else
                {
#if  0
                    MSDK_CHECK_NOT_EQUAL(
                        fwrite(pData->UV + (pInfo->CropY * pData->Pitch / 2 + pInfo->CropX) + i * pData->Pitch + j, 1, 1, m_fDestMVC[vid]),
                        1, MFX_ERR_UNDEFINED_BEHAVIOR);
#else
					goto  errLabel;
#endif
                }
            }
        }

				//
		if  (  m_var.outputInfo.bBufTooSmall  )  {
			TCHAR  tBuf[128];
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "yuvWrite::write err, bufTooSmall. bufSize %d, w %d, h %d"  ),  m_var.outputInfo.uiOutputSize,  pInfo->Width,  pInfo->Height  );
			tmp_showInfo(  tBuf  );
			OutputDebugString(  _T(  "qdcSetOutput failed: uiOutputSize too big\n"  )  );							
		}


        break;

    default:
        return MFX_ERR_UNSUPPORTED;
    }

	iErr  =  0;
errLabel:
	
    return  iErr;	//  MFX_ERR_NONE;
}
#endif


//  char  *  pLeft_outputInfo  =  m_var.outputInfo.pBuf  +  m_var.outputInfo.DataOffset  +  m_var.outputInfo.len;
//  nLeft_outputInfo  =  m_var.outputInfo.uiOutputSize  -  (  m_var.outputInfo.DataOffset  +  m_var.outputInfo.len  )    
//  2015/01/17
#define		CMySmplYUVWriter_qdcOutput(  pOutput,  uiOutputSizeParam  )  {													\
				if  (  (  uiOutputSizeParam  )  >  nLeft_outputInfo    )  {				\
					m_var.outputInfo.bBufTooSmall  =  TRUE;																	\
					}																										\
				else  {																										\
                      memcpy(  pLeft_outputInfo,  (  pOutput  ),  (  uiOutputSizeParam  )  );								\
					  m_var.outputInfo.len  +=  (  uiOutputSizeParam  );													\
					  pLeft_outputInfo  +=  (  uiOutputSizeParam  );														\
					  nLeft_outputInfo  -=  (  uiOutputSizeParam  );														\
				}  }


//  2015/01/17
//  mfxStatus CSmplYUVWriter::WriteNextFrame(mfxFrameSurface1 *pSurface)
int  msdk_surface_to_yuv(  void  *  pQdcObjInfoParam,  void  *  pSurfaceParam,  unsigned  int  cropW,  unsigned  int  cropH,  unsigned  int  pitch,  unsigned  int  imgW,  unsigned  int  imgH,  void  *  pYUVWriter_var  )
{
	int  iErr  =  -1;
	mfxFrameSurface1 *pSurface  =  (  mfxFrameSurface1 *)pSurfaceParam;
	YUVWriter_var  &m_var  =  *(  YUVWriter_var  *  )pYUVWriter_var;
	
	//  2015/01/15
	BOOL  m_bIsMultiView  =  FALSE;

    //MSDK_CHECK_ERROR(m_bInited, false,   MFX_ERR_NOT_INITIALIZED);
    //MSDK_CHECK_POINTER(pSurface,         MFX_ERR_NULL_PTR);

    mfxFrameInfo *pInfo = &pSurface->Info;
    mfxFrameData *pData = &pSurface->Data;
    //MSDK_CHECK_POINTER(pData, MFX_ERR_NULL_PTR);
	if  (  !pInfo  ||  !pData  )  return  -1;

	if  (  pInfo->FourCC  !=  MFX_FOURCC_NV12  )  {
		tmp_showInfo(  _T(  "msdk_surface_to_yuv, info.fourcc is not nv12, not supported"  )  );
		return  -1;
	}

    mfxU32 i, j, h, w;
    mfxU32 vid = pSurface->Info.FrameId.ViewId;

	//
	int  nLeft_outputInfo;
	BYTE  *  pLeft_outputInfo;
	//
	int  minW,  minH;

    switch (pInfo->FourCC)
    {
        case MFX_FOURCC_YV12:
        case MFX_FOURCC_NV12:
			//
			minH  =  min(  pInfo->CropH,  imgH  );
			minW  =  min(  pInfo->CropW,  imgW  );
			//
        for (i = 0; i < minH; i++)
        {
            if (!m_bIsMultiView)
            {
#if  0
                MSDK_CHECK_NOT_EQUAL(
                    fwrite(pData->Y + (pInfo->CropY * pData->Pitch + pInfo->CropX)+ i * pData->Pitch, 1, pInfo->CropW, m_fDest),
                    pInfo->CropW, MFX_ERR_UNDEFINED_BEHAVIOR);
#else

				m_var.outputInfo.DataOffset  =  imgW  *  i;	//  pInfo->Width  *  i;	
				m_var.outputInfo.len  =  0;		
				//
				pLeft_outputInfo  =  m_var.outputInfo.pBuf  +  m_var.outputInfo.DataOffset  +  m_var.outputInfo.len;
				nLeft_outputInfo  =  m_var.outputInfo.uiOutputSize  -  (  m_var.outputInfo.DataOffset  +  m_var.outputInfo.len  );
				//
				CMySmplYUVWriter_qdcOutput(  (  char  *  )(  pData->Y + (pInfo->CropY * pData->Pitch + pInfo->CropX)+ i * pData->Pitch  ),  minW  );  

#endif

            }
            else
            {
#if  0
                MSDK_CHECK_NOT_EQUAL(
                    fwrite(pData->Y + (pInfo->CropY * pData->Pitch + pInfo->CropX)+ i * pData->Pitch, 1, pInfo->CropW, m_fDestMVC[vid]),
                    pInfo->CropW, MFX_ERR_UNDEFINED_BEHAVIOR);
#else
				goto  errLabel;
#endif
            }
        }
        break;
        default:
            return MFX_ERR_UNSUPPORTED;
    }
    switch (pInfo->FourCC)
    {
#if  0
        case MFX_FOURCC_YV12:
        for (i = 0; i < (mfxU32) pInfo->CropH/2; i++)
        {
            MSDK_CHECK_NOT_EQUAL(
                fwrite(pData->U + (pInfo->CropY * pData->Pitch / 2 + pInfo->CropX / 2)+ i * pData->Pitch / 2, 1, pInfo->CropW/2, m_fDest),
                (mfxU32)pInfo->CropW/2, MFX_ERR_UNDEFINED_BEHAVIOR);
        }
        for (i = 0; i < (mfxU32)pInfo->CropH/2; i++)
        {
            MSDK_CHECK_NOT_EQUAL(
                fwrite(pData->V + (pInfo->CropY * pData->Pitch / 2 + pInfo->CropX / 2)+ i * pData->Pitch / 2, 1, pInfo->CropW/2, m_fDest),
                (mfxU32)pInfo->CropW/2, MFX_ERR_UNDEFINED_BEHAVIOR);
        }
        break;
#endif
        case MFX_FOURCC_NV12:
			//
#if  0
        h = pInfo->CropH / 2;
        w = pInfo->CropW;
#else
		h = imgH  /  2;	//  pInfo->Height / 2;
		w = imgW;		//  pInfo->Width;

		m_var.outputInfo.DataOffset  =  imgW  *  imgH;	//  pInfo->Width  *  pInfo->Height;
		m_var.outputInfo.len  =  0;
		//
		pLeft_outputInfo  =  m_var.outputInfo.pBuf  +  m_var.outputInfo.DataOffset  +  m_var.outputInfo.len;			
		nLeft_outputInfo  =  m_var.outputInfo.uiOutputSize  -  (  m_var.outputInfo.DataOffset  +  m_var.outputInfo.len  );
		
#endif	
		int  tmp_h;
		BYTE  b;
		//
		tmp_h  =  min(  h,  pInfo->CropH  /  2  );
		for (i = 0; i < tmp_h; i++)
        {
			//
			//if  (  i  >=  pInfo->CropH  /  2  )  break;

			//
            for (j = 1; j < w; j += 2)
            {
                if (!m_bIsMultiView)
                {
#if  0
                    MSDK_CHECK_NOT_EQUAL(
                        fwrite(pData->UV + (pInfo->CropY * pData->Pitch / 2 + pInfo->CropX)+ i * pData->Pitch + j, 1, 1, m_fDest),
                        1, MFX_ERR_UNDEFINED_BEHAVIOR);
#else

					//  CMySmplYUVWriter_qdcOutput(  (  char  *  )(  pData->UV + (pInfo->CropY * pData->Pitch / 2 + pInfo->CropX) + i * pData->Pitch + j  ),  1  );			
					if  (  j  <  pInfo->CropW  )  b  =  *(  char  *  )(  pData->UV + (pInfo->CropY * pData->Pitch / 2 + pInfo->CropX) + i * pData->Pitch + j  );
					else  b  =  0;
					//
					CMySmplYUVWriter_qdcOutput(  (  char  *  )&b,  1  );

#endif
                }
                else
                {
					#if  0
                    MSDK_CHECK_NOT_EQUAL(
                        fwrite(pData->UV + (pInfo->CropY * pData->Pitch / 2 + pInfo->CropX)+ i * pData->Pitch + j, 1, 1, m_fDestMVC[vid]),
                        1, MFX_ERR_UNDEFINED_BEHAVIOR);
					#else
						goto  errLabel;
					#endif
                }
            }
        }
				
		//
		m_var.outputInfo.DataOffset  =  imgW  *  imgH  *  5  /  4;	//  pInfo->Width  *  pInfo->Height  *  5  /  4;
		m_var.outputInfo.len  =  0;
		//
		pLeft_outputInfo  =  m_var.outputInfo.pBuf  +  m_var.outputInfo.DataOffset  +  m_var.outputInfo.len;			
		nLeft_outputInfo  =  m_var.outputInfo.uiOutputSize  -  (  m_var.outputInfo.DataOffset  +  m_var.outputInfo.len  );
		//
        for (i = 0; i < tmp_h; i++)
        {
			//
			//if  (  i  >=  pInfo->CropH  /  2  )  break;

			//
            for (j = 0; j < w; j += 2)
            {
                if (!m_bIsMultiView)
                {
#if  0
                    MSDK_CHECK_NOT_EQUAL(
                        fwrite(pData->UV + (pInfo->CropY * pData->Pitch / 2 + pInfo->CropX) + i * pData->Pitch + j, 1, 1, m_fDest),
                        1, MFX_ERR_UNDEFINED_BEHAVIOR);
#else

					//  CMySmplYUVWriter_qdcOutput(  (  char  *  )(  pData->UV + (pInfo->CropY * pData->Pitch / 2 + pInfo->CropX)+ i * pData->Pitch + j  ),  1  );
					if  (  j  <  pInfo->CropW  )  b  =  *(  char  *  )(  pData->UV + (pInfo->CropY * pData->Pitch / 2 + pInfo->CropX)+ i * pData->Pitch + j  );
					else  b  =  0;
					//
					CMySmplYUVWriter_qdcOutput(  (  char  *  )&b,  1  );

#endif
                }
                else
                {
#if  0
                    MSDK_CHECK_NOT_EQUAL(
                        fwrite(pData->UV + (pInfo->CropY * pData->Pitch / 2 + pInfo->CropX) + i * pData->Pitch + j, 1, 1, m_fDestMVC[vid]),
                        1, MFX_ERR_UNDEFINED_BEHAVIOR);
#else
					goto  errLabel;
#endif
                }
            }
        }

				//
		if  (  m_var.outputInfo.bBufTooSmall  )  {
			TCHAR  tBuf[128];
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "yuvWrite::write err, bufTooSmall. bufSize %d, w %d, h %d"  ),  m_var.outputInfo.uiOutputSize,  pInfo->Width,  pInfo->Height  );
			tmp_showInfo(  tBuf  );
			OutputDebugString(  _T(  "qdcSetOutput failed: uiOutputSize too big\n"  )  );							
		}


        break;

    default:
        return MFX_ERR_UNSUPPORTED;
    }

	iErr  =  0;
errLabel:
	
    return  iErr;	//  MFX_ERR_NONE;
}


//  2015/09/30
int  msdk_surface_to_yuv_doNothing(  void  *  pQdcObjInfoParam,  void  *  pSurfaceParam,  unsigned  int  cropW,  unsigned  int  cropH,  unsigned  int  pitch,  unsigned  int  imgW,  unsigned  int  imgH,  void  *  pYUVWriter_var  )
{
	return  0;
}

//
mfxStatus CMySmplYUVWriter::WriteNextFrame(mfxFrameSurface1 *pSurface)
{
	mfxStatus  sts  =  MFX_ERR_UNKNOWN;

	if  (  this->WriteNextFrame_pre(  )  )  goto  errLabel;
	if  (  this->WriteNextFrame0(  pSurface  )  )  goto  errLabel;
	if  (  this->WriteNextFrame1(  )  )  goto  errLabel;

	sts  =  MFX_ERR_NONE;

errLabel:
	return  MFX_ERR_NONE;	//  sts;
}

//
mfxStatus CMySmplYUVWriter::WriteNextFrame_pre()
{ 
	mfxStatus  sts  =  MFX_ERR_UNKNOWN;
	//BOOL  bMsgGot  =  FALSE;

	//
    CHECK_ERROR(m_bInited, false,   MFX_ERR_NOT_INITIALIZED);
	
	//  2011/12/04. 因为只能存放一祯，所以需要清0
	if  (  !m_var.pQdcObjInfoParam
		||  !m_var.pPkt  )		
	{
		tmp_showInfo(  _T(  "yuvWrite::write failed, pPkt is null. skipped"  )  );
		return  MFX_ERR_NONE;
	}
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.pQdcObjInfoParam;
	QDC_OBJ_trans  *  pObj  =  (  QDC_OBJ_trans  *  )pQdcObjInfo->var.pObj;

	
	if  (  pQdcObjInfo->cfg.v.dec.pf_smplYUVWriter_WriteNextFrame_pre(  pQdcObjInfo,  &pObj->common,  &m_var  )  )  {
		//  tmp_showInfo(  _T(  "YUVWriter: smpl_writeNextFrame failed. skipped"  )  );
		goto  errLabel;
	}
	
	sts  =  MFX_ERR_NONE;
	
errLabel:
	
    return sts;	//  MFX_ERR_NONE;
	
}


//
mfxStatus CMySmplYUVWriter::WriteNextFrame0(mfxFrameSurface1 *pSurface)
{ 
	mfxStatus  sts  =  MFX_ERR_UNKNOWN;
	//BOOL  bMsgGot  =  FALSE;

	//
    CHECK_ERROR(m_bInited, false,   MFX_ERR_NOT_INITIALIZED);
    CHECK_POINTER(pSurface,         MFX_ERR_NULL_PTR);

#ifdef  _DEBUG
		#if  0
			 TCHAR  tBuf[128];
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "YUVWriter::WriteNextFrame "  )  );
			 tmp_showInfo(  tBuf  );
		#endif
#endif

	//
    mfxFrameInfo *pInfo = &pSurface->Info;
    mfxFrameData *pData = &pSurface->Data;
    CHECK_POINTER(pData, MFX_ERR_NULL_PTR);
	
	//  2011/12/04. 因为只能存放一祯，所以需要清0
	if  (  !m_var.pQdcObjInfoParam
		||  !m_var.pPkt  )		
	{
		tmp_showInfo(  _T(  "yuvWrite::write failed, pPkt is null. skipped"  )  );
		return  MFX_ERR_NONE;
	}
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.pQdcObjInfoParam;
	QDC_OBJ_trans  *  pObj  =  (  QDC_OBJ_trans  *  )pQdcObjInfo->var.pObj;

	int  iFourcc  =  CONST_fourcc_YV12;
	mfxF64 dFrameRate = 0;
	if  (  !pObj->common.bInited2  )  {
		dFrameRate  =  CalculateFrameRate(pInfo->FrameRateExtN, pInfo->FrameRateExtD);
		msdk_printf(MSDK_STRING("Frame rate\t%.2f\n"), dFrameRate);
	}
	
	//  2015/09/30
	PF_img_to_yuv  pf_img_to_yuv  =  msdk_surface_to_yuv;
	//
	if  (  pQdcObjInfo->var.usPktResType_dec  ==  CONST_pktResType_sharedTex  )  {
		pf_img_to_yuv  =  msdk_surface_to_yuv_doNothing;
	}

	//
	if  (  pQdcObjInfo->cfg.v.dec.pf_smplYUVWriter_WriteNextFrame0(  pQdcObjInfo,  &pObj->common,  iFourcc,  &m_var,  pSurface,  pInfo->CropW,  pInfo->CropH,  pData->Pitch,  pf_img_to_yuv,  dFrameRate,  _T(  ""  )  )  )  {
		tmp_showInfo(  _T(  "WritenextFrame0 failed"  )  );
		goto  errLabel;
	}
	
	sts  =  MFX_ERR_NONE;
	
errLabel:
	
    return sts;	//  MFX_ERR_NONE;
	
}

mfxStatus CMySmplYUVWriter::WriteNextFrame1()
{ 
	mfxStatus  sts  =  MFX_ERR_UNKNOWN;
	//BOOL  bMsgGot  =  FALSE;

	//
    CHECK_ERROR(m_bInited, false,   MFX_ERR_NOT_INITIALIZED);
	
	//  2011/12/04. 因为只能存放一祯，所以需要清0
	if  (  !m_var.pQdcObjInfoParam
		||  !m_var.pPkt  )		
	{
		tmp_showInfo(  _T(  "yuvWrite::write failed, pPkt is null. skipped"  )  );
		return  MFX_ERR_NONE;
	}
	QDC_OBJ_INFO  *  pQdcObjInfo  =  (  QDC_OBJ_INFO  *  )m_var.pQdcObjInfoParam;
	QDC_OBJ_trans  *  pObj  =  (  QDC_OBJ_trans  *  )pQdcObjInfo->var.pObj;

	
	if  (  pQdcObjInfo->cfg.v.dec.pf_smplYUVWriter_WriteNextFrame1(  pQdcObjInfo,  &pObj->common,  &m_var  )  )  {
		//tmp_showInfo(  _T(  "YUVWriter: smpl_writeNextFrame1 failed.  )  );
		goto  errLabel;
	}
	
	sts  =  MFX_ERR_NONE;
	
errLabel:
	
    return sts;	//  MFX_ERR_NONE;
	
}



 //
BOOL  bTransformFuncsOk(  QDC_OBJ_INFO  *  pQdcObjInfo  )
{

	if  (  !pQdcObjInfo->cfg.v.pf_bTransformVideoQuit
		||  !pQdcObjInfo->cfg.v.pf_getNextVPkt
		//||  !pQdcObjInfo->cfg.v.pf_parseVPkt_i
		||  !pQdcObjInfo->cfg.v.pf_parseDecVPkt_o
		||  !pQdcObjInfo->cfg.v.pf_detachPkt 
		||  !pQdcObjInfo->cfg.v.pf_clean_myDRAW_VIDEO_DATA
		)
	{
		return  FALSE;
	}

	switch  (  pQdcObjInfo->cfg.v.uiTransformType_pParent  )  {
			case  CONST_uiTransformType_dec:
				  if  (  !pQdcObjInfo->cfg.v.dec.pf_updateDecVideoParam
					  ||  !pQdcObjInfo->cfg.v.dec.pf_postVPktToRender
					  )
				  {
					  return  FALSE;
				  }				  
			case  CONST_uiTransformType_encVideo:				
				  break;
			default:
					#ifdef  _DEBUG	
							OutputDebugString(  _T(  "bTransformFuncsOk failed, transformType err\n"  )  );
					#endif
					return  FALSE;
	}

	return  TRUE;
}

