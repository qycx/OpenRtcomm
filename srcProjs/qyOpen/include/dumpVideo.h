

#ifndef  __dumpVideo_h__
#define  __dumpVideo_h__	//  {

//
#include    "myTypes_basic.h"


//
typedef  struct  __param_anDumpVideo_t      {
                 //
                 int                        iFourcc;
                 int                        iW;
                 int                        iH;
                 short                      usFps;

                 //
                 bool                       b_noIvf;        //  对nv，输出直接是ivf, 所以需要设置这个标志，不要加ivf的头

                 //
}        Param_anDumpVideo;


//
typedef  struct  __anDumpVideoObj_t         {
                 //
                 Param_anDumpVideo          param;
                 
                 //
                 int                        index_timestamp;       //  

                 //
                 void                   *   pObj;

}        AnDumpVideoObj;



//
int  dumpVideo_init(Param_anDumpVideo  *  pParam,  BOOL* p_static_bReset, LPCTSTR  dir, LPCTSTR  fn, char* video, int  len, AnDumpVideoObj  *  pDvo);
int  dumpVideo_exit(AnDumpVideoObj* pDvo);
int  dumpVideo(LPCTSTR  dir, LPCTSTR  fn, char* video, int  len, AnDumpVideoObj* pDvo);



//
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <vector>

/**
 * IVF文件头结构体（32字节）
 * 结构参考：https://wiki.multimedia.cx/index.php/IVF
 */
#pragma pack(push, 1)  // 确保结构体按1字节对齐
struct IVFHeader {
    char     signature[4];      // 签名，固定为"DKIF"
    uint16_t version;           // 版本号，通常为0
    uint16_t header_size;       // 头部长度，通常为32
    char     fourcc[4];         // 编码器标识，AV1为"AV01"
    uint16_t width;             // 视频宽度（像素）
    uint16_t height;            // 视频高度（像素）
    uint32_t timebase_den;      // 时间基分母
    uint32_t timebase_num;      // 时间基分子（帧率 = denominator/numerator）
    uint32_t frame_count;       // 总帧数（可先填0，写完再更新）
    uint32_t unused;            // 未使用字段，填0
};
#pragma pack(pop)

/**
 * IVF帧头结构体（12字节）
 * 每帧数据前都要加上这个头
 */
#pragma pack(push, 1)
struct IVFFrameHeader {
    uint32_t frame_size;    // 当前帧的大小（字节数）
    uint64_t timestamp;     // 时间戳（按timebase单位计算）
};
#pragma pack(pop)


//
#ifdef  __cplusplus
extern  "C" {
#endif 


    /**
     * IVF文件写入器类
     * 封装了写入头、写入帧、更新头等操作
     */
    class IVFFileWriter {
    public:
        /**
         * 构造函数
         * @param filename 输出文件名
         * @param width 视频宽度
         * @param height 视频高度
         * @param framerate_numerator 帧率分子（如30/1的话分子=30）
         * @param framerate_denominator 帧率分母（如30/1的话分母=1）
         */
        IVFFileWriter(const char* filename,
            uint16_t width,
            uint16_t height,
            uint32_t fps_num = 30,
            uint32_t fps_den = 1)
            : m_file(nullptr)
            , m_frame_count(0)
        {
            // 初始化文件头
            memcpy(m_header.signature, "DKIF", 4);
            m_header.version = 0;
            m_header.header_size = 32;
            memcpy(m_header.fourcc, "AV01", 4);
            m_header.width = width;
            m_header.height = height;
            m_header.timebase_num = fps_den;    // IVF的timebase是"每帧的持续时间"
            m_header.timebase_den = fps_num;    // 所以分母是帧率，分子是1
            m_header.frame_count = 0;   // 暂时填0，最后再更新
            m_header.unused = 0;

            // 打开文件
            m_file = fopen(filename, "wb");
            if (m_file) {
                // 先写入文件头（帧数暂时填0）
                fwrite(&m_header, sizeof(IVFHeader), 1, m_file);
            }
        }

        /**
         * 析构函数：关闭文件并更新总帧数
         */
        ~IVFFileWriter() {
            if (m_file) {
                // 回到文件开头，更新总帧数
                fseek(m_file, offsetof(IVFHeader, frame_count), SEEK_SET);
                fwrite(&m_frame_count, sizeof(uint32_t), 1, m_file);
                fclose(m_file);
            }
        }

        /**
         * 写入一帧AV1数据
         * @param data 帧数据指针
         * @param size 帧数据大小
         * @param timestamp 时间戳（按timebase单位，通常帧号从0开始）
         * @return 是否写入成功
         */
        bool writeFrame(const void* data, size_t size, uint64_t timestamp) {
            if (!m_file || !data || size == 0) {
                return false;
            }

            // 准备帧头
            IVFFrameHeader frame_header;
            frame_header.frame_size = static_cast<uint32_t>(size);
            frame_header.timestamp = timestamp;

            // 写入帧头
            if (fwrite(&frame_header, sizeof(IVFFrameHeader), 1, m_file) != 1) {
                return false;
            }

            // 写入帧数据
            if (fwrite(data, 1, size, m_file) != size) {
                return false;
            }

            // 刷新到磁盘（可选，避免缓冲区过大）
            fflush(m_file);

            m_frame_count++;
            return true;
        }

        /**
         * 检查文件是否成功打开
         */
        bool isValid() const {
            return m_file != nullptr;
        }

    private:
        FILE* m_file;
        IVFHeader m_header;
        uint32_t m_frame_count;
    };


#ifdef  __cplusplus
}
#endif 



#endif  //  }


