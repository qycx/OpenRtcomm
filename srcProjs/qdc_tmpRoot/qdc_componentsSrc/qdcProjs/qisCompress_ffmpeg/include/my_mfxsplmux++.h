/* ****************************************************************************** *\

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013 Intel Corporation. All Rights Reserved.


File Name: mfxsplmux++.h

\* ****************************************************************************** */

#ifndef __MFXSPLMUXPLUSPLUS_H
#define __MFXSPLMUXPLUSPLUS_H

#include "mfxsplmux.h"

class MFXStreamParams : public mfxStreamParams {
public:
    MFXStreamParams() {
        SystemType = MFX_UNDEF_STREAM;
        Duration = 0;
        NumTracks = 0;
        NumTracksAllocated = 0;
        TrackInfo = 0;
        Flags = 0;
    }
};

class MFXDataIO
{
public:
    virtual ~MFXDataIO() { }
    virtual mfxI32 Read (mfxBitstream *bs) = 0;
    virtual mfxI32 Write (mfxBitstream *bs) = 0;
    virtual mfxI64 Seek (mfxI64 offset, mfxSeekOrigin origin) = 0;
};

class MFXDataIOAdapter
{
    mfxDataIO m_data_io;
public:
    MFXDataIOAdapter (MFXDataIO& data_io) {
        m_data_io.pthis = &data_io;
        m_data_io.Read = staticRead;
        m_data_io.Seek = staticSeek;
        m_data_io.Write = staticWrite;
    }
    operator mfxDataIO () const {
        return m_data_io;
    }
private:
    static mfxI32 staticRead (mfxHDL pthis, mfxBitstream *bs)
    {
        return reinterpret_cast<MFXDataIO *>(pthis)->Read(bs);
    }
    static mfxI64 staticSeek (mfxHDL pthis, mfxI64 offset, mfxSeekOrigin origin)
    {
        return reinterpret_cast<MFXDataIO *>(pthis)->Seek(offset, origin);
    }
    static mfxI32 staticWrite (mfxHDL pthis, mfxBitstream *bs)
    {
        return reinterpret_cast<MFXDataIO *>(pthis)->Write(bs);
    }
};

//
mfxStatus dyn_MFXSplitter_Init(mfxDataIO *data_io, mfxSplitter *spl);
mfxStatus dyn_MFXSplitter_Close(mfxSplitter spl);
mfxStatus dyn_MFXSplitter_GetBitstream(mfxSplitter spl, mfxU32 *track_num, mfxBitstream *bs);
mfxStatus dyn_MFXSplitter_ReleaseBitstream(mfxSplitter spl, mfxBitstream *bs);
mfxStatus dyn_MFXSplitter_GetInfo(mfxSplitter spl, mfxStreamParams *par);
mfxStatus dyn_MFXSplitter_Seek(mfxSplitter spl, mfxU64 timestamp);

//
typedef  mfxStatus (  *PF_MFXSplitter_Init  )(mfxDataIO *data_io, mfxSplitter *spl);
typedef  mfxStatus (  *PF_MFXSplitter_Close  )(mfxSplitter spl);
typedef  mfxStatus (  *PF_MFXSplitter_GetBitstream  )(mfxSplitter spl, mfxU32 *track_num, mfxBitstream *bs);
typedef  mfxStatus (  *PF_MFXSplitter_ReleaseBitstream  )(mfxSplitter spl, mfxBitstream *bs);
typedef  mfxStatus (  *PF_MFXSplitter_GetInfo  )(mfxSplitter spl, mfxStreamParams *par);
typedef  mfxStatus (  *PF_MFXSplitter_Seek  )(mfxSplitter spl, mfxU64 timestamp);

//
class CMyMFXSplitter
{
public:
    CMyMFXSplitter() : m_spl(), io(), m_trackInfo(NULL), m_tracksNum(0) { }
    virtual ~CMyMFXSplitter()
    {
        freeTrackInfo();
        Close();
    }
    virtual mfxStatus Init(MFXDataIO &data_io)
    {
        io = MFXDataIOAdapter(data_io) ;
        return dyn_MFXSplitter_Init(&io, &m_spl);
    }
    virtual mfxStatus Close() { 
        mfxStatus sts = dyn_MFXSplitter_Close(m_spl);
        m_spl = (mfxSplitter)0;
        return sts;
    }
    virtual mfxStatus GetInfo(MFXStreamParams &par)
    {
        mfxStatus sts = MFX_ERR_NONE;
        mfxStreamParams *splitterPar = &par;
        sts = dyn_MFXSplitter_GetInfo(m_spl, splitterPar);
        if (sts == MFX_ERR_NONE)
        {
            freeTrackInfo();
            m_trackInfo = (mfxTrackInfo**) malloc(sizeof(mfxTrackInfo*)*splitterPar->NumTracks);
            if (!m_trackInfo)
                sts = MFX_ERR_MEMORY_ALLOC;
            m_tracksNum = splitterPar->NumTracks;
        }
        if (sts == MFX_ERR_NONE)
        {
            memset(m_trackInfo, 0, sizeof(mfxTrackInfo*)*splitterPar->NumTracks);
            for (mfxU32 i = 0; i < splitterPar->NumTracks && sts == MFX_ERR_NONE; i++)
            {
                m_trackInfo[i] = (mfxTrackInfo*) malloc(sizeof(mfxTrackInfo));
                if (!m_trackInfo[i])
                    sts = MFX_ERR_MEMORY_ALLOC;
            }
        }
        if (sts == MFX_ERR_NONE)
        {
            splitterPar->NumTracksAllocated = splitterPar->NumTracks;
            splitterPar->TrackInfo = m_trackInfo;
            sts = dyn_MFXSplitter_GetInfo(m_spl, splitterPar);
        }
        if (sts != MFX_ERR_NONE)
        {
            freeTrackInfo();
        }
        return sts;
    }
    virtual mfxStatus GetBitstream(mfxU32 *track_num, mfxBitstream *bs) { return dyn_MFXSplitter_GetBitstream(m_spl, track_num, bs); }
    virtual mfxStatus ReleaseBitstream(mfxBitstream *bs) { return dyn_MFXSplitter_ReleaseBitstream(m_spl, bs); }
    virtual mfxStatus Seek(mfxU64 timestamp) { return dyn_MFXSplitter_Seek(m_spl, timestamp); }

protected:
    void freeTrackInfo()
    {
        if (m_trackInfo)
        {
            for (int i = 0; i < m_tracksNum; i++)
            {
                if (m_trackInfo[i])
                {
                    free (m_trackInfo[i]);
                    m_trackInfo[i] = NULL;
                }
            }
            free(m_trackInfo);
            m_trackInfo = NULL;
        }
    }

    mfxTrackInfo **m_trackInfo;
    mfxU16      m_tracksNum;
    mfxDataIO   io;
    mfxSplitter m_spl;
};

class MFXMuxer
{
public:
    MFXMuxer() : m_mux(), io() { }
    virtual ~MFXMuxer() { Close(); }
    virtual mfxStatus Init(MFXStreamParams &par, MFXDataIO &data_io) {
        io = MFXDataIOAdapter(data_io) ;
        return MFXMuxer_Init(&par, &io, &m_mux);
    }
    virtual mfxStatus Close() { 
        mfxStatus sts = MFXMuxer_Close(m_mux);
        m_mux = (mfxMuxer)0;
        return sts;
    }
    virtual mfxStatus PutBitstream(mfxU32 track_num, mfxBitstream *bs, mfxU64 duration) { return MFXMuxer_PutBitstream(m_mux, track_num, bs, duration); }

protected:
    mfxDataIO io;
    mfxMuxer  m_mux;
};

#endif // __MFXSPLMUXPLUSPLUS_H