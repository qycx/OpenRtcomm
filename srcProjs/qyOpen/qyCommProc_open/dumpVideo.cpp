

#include "stdafx.h"
#include <cstdio>
#include <myTypes.h>
#include	"qyOpenShellCommon.h"
#include    "dumpVideo.h"
#include    "qyDefs_open.h"
#include    "..\\qyCommProc_open\\include\\qyCommProc_open.h"



//
#define     CONST_dumpFn    _T("d:\\tttbbb\\kkav1.ivf")

//
//int  dumpVideo_init(BOOL* p_static_bReset, LPCTSTR  dir, LPCTSTR  fn, char* video, int  len)
int  dumpVideo_init(Param_anDumpVideo* pParam, BOOL* p_static_bReset, LPCTSTR  dir, LPCTSTR  fn, char* video, int  len, AnDumpVideoObj* pDvo)
{
    int  iErr = -1;
    Param_anDumpVideo  tmp_param = { 0 };
    if (!pParam)  pParam = &tmp_param;

    IVFFileWriter* pObj = mynull;

    do {
        //
        if (pParam->iFourcc == CONST_fourcc_AV01  &&  !pParam->b_noIvf  ) {
            //
            if (pDvo->pObj) return  -1;
            
            //
            char  fullFn[256];
            _snprintf(fullFn, mycountof(fullFn), ("%s\\%S"), "c:\\tttbbb\\", fn);
            pObj = new IVFFileWriter(fullFn, pParam->iW, pParam->iH);
            //
            if (!pObj->isValid())  break;

            //
#if 10
            if (video && len) {
                pObj->writeFrame(video, len, pDvo->index_timestamp);
                pDvo->index_timestamp++;
            }
#endif

            //
            pDvo->pObj = pObj;  pObj = mynull;
            //
            pDvo->param = *pParam;



        }
        else
        {


            //
            if (!*p_static_bReset) {
                *p_static_bReset = true;
                //
                FILE* fp;
                //
                fn = CONST_dumpFn;
                //
                fp = _tfopen(fn, _T("w"));
                if (fp) {
                    fclose(fp);
                }
            }


            //
            if (video && len) {
                FILE* fp;
                fp = _tfopen(fn, _T("ab+"));
                if (fp) {
                    fwrite(video, 1, len, fp);
                    fclose(fp);
                }
            }
        }

        //
        iErr = 0;

    } while (false);


    //
    if (pObj)  delete  pObj;



	//
	return  iErr;
}

int  dumpVideo_exit(AnDumpVideoObj* pDvo)
{
    if (pDvo) {
        if (pDvo->param.iFourcc == CONST_fourcc_AV01) {
            IVFFileWriter* pObj = (IVFFileWriter*)pDvo->pObj;
            //
            if (pObj) {
                delete  pObj;
            }
            //
            pDvo->pObj = mynull;

        }
    }

    //
    return 0;
}

//int  dumpVideo(LPCTSTR  dir, LPCTSTR  fn, char* video, int  len)
int  dumpVideo(LPCTSTR  dir, LPCTSTR  fn, char* video, int  len, AnDumpVideoObj* pDvo)
{
    if (pDvo
        &&  pDvo->param.iFourcc  ==  CONST_fourcc_AV01
        &&  !pDvo->param.b_noIvf  ) 
    {
            IVFFileWriter* pObj = (IVFFileWriter*)pDvo->pObj;
            //
            if (pObj) {
                pObj->writeFrame(video, len, pDvo->index_timestamp);
                pDvo->index_timestamp++;
            }
        
    }
    else 
    {



        //
        if (video && len) {
            FILE* fp;
            //
            fn = CONST_dumpFn;
            //
            fp = _tfopen(fn, _T("ab+"));
            if (fp) {
                fwrite(video, 1, len, fp);
                fclose(fp);
            }
        }
    }


	return  0;
}

//////////////////////////

/* OBU类型名称 */
static const char* obu_type_names[16] = {
    "RESERVED_0",
    "SEQUENCE_HEADER",
    "TEMPORAL_DELIMITER",
    "FRAME_HEADER",
    "TILE_GROUP",
    "METADATA",
    "FRAME",
    "REDUNDANT_FRAME_HEADER",
    "TILE_LIST",
    "RESERVED_9",
    "RESERVED_10",
    "RESERVED_11",
    "RESERVED_12",
    "RESERVED_13",
    "RESERVED_14",
    "PADDING"
};

/* 读取LEB128变长整数，返回读取的字节数，值存储在*val */
static int read_leb128(const uint8_t* data, size_t max_len, uint64_t* val) {
    uint64_t v = 0;
    int i = 0;
    uint8_t byte;

    do {
        if (i >= max_len) return -1; // 数据不足
        byte = data[i];
        v |= ((uint64_t)(byte & 0x7F)) << (i * 7);
        i++;
    } while (byte & 0x80);

    *val = v;
    return i;
}

//



//////////////////////




/**
 * 简单易用的函数版本：保存单帧或多帧AV1数据到IVF文件
 *
 * @param filename 输出文件名
 * @param frames 帧数据向量，每个元素是一帧的完整AV1数据
 * @param width 视频宽度
 * @param height 视频高度
 * @param framerate 帧率（如30表示30fps）
 * @return true表示成功，false表示失败
 *
 * 使用示例：
 *
 * // 准备两帧数据（示例数据，实际请替换为真实的AV1帧）
 * std::vector<std::vector<uint8_t>> frames;
 * frames.push_back({0x0A, 0x0B, 0x0C, ...});  // 第一帧（可能是关键帧）
 * frames.push_back({0x1A, 0x1B, 0x1C, ...});  // 第二帧
 *
 * // 保存为IVF文件
 * saveAV1ToIVF("output.ivf", frames, 1920, 1080, 30);
 */
bool saveAV1ToIVF(const char* filename,
    const std::vector<std::vector<uint8_t>>& frames,
    uint16_t width,
    uint16_t height,
    uint32_t framerate = 30) {

    // 创建IVF写入器
    IVFFileWriter writer(filename, width, height, framerate, 1);
    if (!writer.isValid()) {
        return false;
    }

    // 逐帧写入
    for (size_t i = 0; i < frames.size(); i++) {
        if (!writer.writeFrame(frames[i].data(), frames[i].size(), i)) {
            return false;
        }
    }

    return true;
}

/**
 * 更底层的函数版本：逐帧写入（适合实时编码或大文件）
 * 使用方式参考main函数
 */

 // ------------------- 使用示例 -------------------
 // 注意：下面是一个完整的演示程序，展示如何使用上述类
#ifdef EXAMPLE_USAGE
#include <iostream>

int main() {
    // 示例1：使用类手动写入（适合实时流）
    {
        IVFFileWriter writer("test1.ivf", 1920, 1080, 30, 1);
        if (!writer.isValid()) {
            std::cerr << "无法创建文件" << std::endl;
            return -1;
        }

        // 模拟写入两帧（这里用假数据演示）
        std::vector<uint8_t> frame1 = { 0x00, 0x01, 0x02, 0x03 };  // 实际应该是完整的AV1帧
        std::vector<uint8_t> frame2 = { 0x10, 0x11, 0x12, 0x13 };

        writer.writeFrame(frame1.data(), frame1.size(), 0);  // 第0帧
        writer.writeFrame(frame2.data(), frame2.size(), 1);  // 第1帧

        std::cout << "test1.ivf 写入完成" << std::endl;
    }  // 离开作用域时，writer析构函数会自动更新总帧数

    // 示例2：使用便捷函数（适合已有完整数据）
    {
        std::vector<std::vector<uint8_t>> frames;
        frames.push_back({ 0x00, 0x01, 0x02, 0x03 });  // 帧0
        frames.push_back({ 0x10, 0x11, 0x12, 0x13 });  // 帧1
        frames.push_back({ 0x20, 0x21, 0x22, 0x23 });  // 帧2

        if (saveAV1ToIVF("test2.ivf", frames, 1280, 720, 25)) {
            std::cout << "test2.ivf 写入完成" << std::endl;
        }
        else {
            std::cerr << "写入失败" << std::endl;
        }
    }

    return 0;
}
#endif

/**
 * 如果你不想用C++的vector，可以用纯C风格函数：
 */

#include <stdio.h>
#include <stdint.h>

 // 纯C风格的IVF写入函数
int save_av1_to_ivf_c(const char* filename,
    const uint8_t** frames,     // 帧数据指针数组
    const uint32_t* frame_sizes, // 每帧大小数组
    uint32_t frame_count,        // 总帧数
    uint16_t width,
    uint16_t height,
    uint32_t framerate) {

    FILE* f = fopen(filename, "wb");
    if (!f) return -1;

    // 写入文件头
    IVFHeader header;
    memcpy(header.signature, "DKIF", 4);
    header.version = 0;
    header.header_size = 32;
    memcpy(header.fourcc, "AV01", 4);
    header.width = width;
    header.height = height;
    header.timebase_num = 1;
    header.timebase_den = framerate;
    header.frame_count = frame_count;
    header.unused = 0;

    fwrite(&header, sizeof(header), 1, f);

    // 写入每一帧
    for (uint32_t i = 0; i < frame_count; i++) {
        IVFFrameHeader frame_header;
        frame_header.frame_size = frame_sizes[i];
        frame_header.timestamp = i;  // 时间戳从0开始

        fwrite(&frame_header, sizeof(frame_header), 1, f);
        fwrite(frames[i], 1, frame_sizes[i], f);
    }

    fclose(f);
    return 0;
}


