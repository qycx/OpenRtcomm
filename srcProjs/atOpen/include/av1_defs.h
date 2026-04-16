

#ifndef  __av1_defs_h__
#define  __av1_defs_h__		//  {



//
#define		OBU_RESERVED_0					0
#define		OBU_SEQUENCE_HEADER				1	//序列头，包含全局编码参数（分辨率、profile 等） |
#define		OBU_TEMPORAL_DELIMITER			2	//时间分隔符，用于标记 temporal unit 边界 |
#define		OBU_FRAME_HEADER				3	//帧头信息（不含实际像素数据）              |
#define		OBU_TILE_GROUP					4	//tile 数据（实际编码的图像块数据）         |
#define		OBU_METADATA					5	//元数据（HDR、时间戳等）               |
#define		OBU_FRAME						6	//完整帧（header + tile 数据合在一起）   |
#define		OBU_REDUNDANT_FRAME_HEADER		7	//冗余帧头                        |
#define		OBU_TILE_LIST					8	//tile 列表（用于某些拼接 / 流处理场景）       |
//| 9–14 | `OBU_RESERVED_*` | 保留                          |
#define		OBU_PADDING						15	//填充数据 |


//
#define     KEY_FRAME                       0   //关键帧（I帧），可以独立解码   |
#define     INTER_FRAME                     1   //帧间预测帧（P / B帧）      |
#define     INTRA_ONLY_FRAME                2   //仅帧内编码，但不是关键帧     |
#define     SWITCH_FRAME                    3   //切换帧（用于码流切换 / 随机接入） |



//
// ================= Sequence Header =================
struct AV1SeqInfo {
    int profile = 0;
    int width = 0;
    int height = 0;
};


//
typedef  struct  __param_parseIvfFrame_t {
                 
                 //
                 bool  bGot_seqHeader;
                 //
                 char   seqHeader_buf[256];
                 int    seqHeader_len;
                 
                 //
                 bool  bGot_keyFrame;

                 //
                 AV1SeqInfo  seq;

} Param_parseIvfFrame;


//
int parse_ivf_frame(const char* data, int size, Param_parseIvfFrame* pParam);
void parse_obu(const uint8_t* data, uint32_t size, Param_parseIvfFrame* pParam);



#endif  //  }


