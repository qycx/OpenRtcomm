
#include	"stdafx.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

using namespace std;

//
#include    "av1_defs.h"



//
char* getObuTypeStr(int obuType)
{
    char* str = (char*)"";

    switch (obuType) {
    case  OBU_RESERVED_0:
        break;
    case  OBU_SEQUENCE_HEADER:
        str = (char*)"seqHeader";
        break;
    case  OBU_TEMPORAL_DELIMITER:
        str = (char*)"tempDelimiter";
        break;
    case  OBU_FRAME_HEADER:
        str = (char*)"frameHeader";
        break;
    case  OBU_TILE_GROUP:
        str = (char*)"tileGrp";
        break;
    case  OBU_METADATA:
        str = (char*)"metaData";
        break;
    case  OBU_FRAME:
        str = (char*)"frame";
        break;
    case  OBU_REDUNDANT_FRAME_HEADER:
        str = (char*)"redundantFrameHeader";
        break;
    case  OBU_TILE_LIST:
        str = (char*)"tileList";
        break;
        //| 9–14 | `OBU_RESERVED_*` | 保留 
    case  OBU_PADDING:
        str = (char*)"padding";
        break;
    default:
        break;
    }

    return str;
}

// ================= BitReader =================
// --------------------------------------------
// 简单 BitReader（按 bit 读取）

struct BitReader {
    const uint8_t* data;
    size_t size;
    size_t byte_pos = 0;
    uint8_t bit_pos = 0;

    BitReader(const uint8_t* d, size_t s) : data(d), size(s) {}

    uint32_t readBits(int n) {
        uint32_t value = 0;
        for (int i = 0; i < n; ++i) {
            if (byte_pos >= size) return 0;
            value <<= 1;
            value |= (data[byte_pos] >> (7 - bit_pos)) & 1;
            bit_pos++;
            if (bit_pos == 8) {
                bit_pos = 0;
                byte_pos++;
            }
        }
        return value;
    }

    uint32_t readBit() { return readBits(1); }

    // 读取 leb128
    uint32_t readLEB128() {
        uint32_t result = 0;
        int shift = 0;
        while (true) {
            uint8_t byte = readBits(8);
            result |= (byte & 0x7F) << shift;
            if ((byte & 0x80) == 0) break;
            shift += 7;
        }
        return result;
    }
};




// ================= LEB128 =================
// ================= leb128 =================
uint64_t read_leb128(const uint8_t* data, size_t& offset) {
    uint64_t value = 0;
    int shift = 0;
    while (true) {
        uint8_t byte = data[offset++];
        value |= (byte & 0x7F) << shift;
        if (!(byte & 0x80)) break;
        shift += 7;
    }
    return value;
}

// ================= IVF Frame =================
struct IVFFrame {
    uint32_t size;
    uint64_t timestamp;
    vector<uint8_t> data;
};

bool read_ivf_frame(ifstream& fin, IVFFrame& frame) {
    uint8_t header[12];

    if (!fin.read((char*)header, 12)) return false;

    frame.size =
        header[0] |
        (header[1] << 8) |
        (header[2] << 16) |
        (header[3] << 24);

    frame.timestamp =
        (uint64_t)header[4] |
        ((uint64_t)header[5] << 8) |
        ((uint64_t)header[6] << 16) |
        ((uint64_t)header[7] << 24) |
        ((uint64_t)header[8] << 32) |
        ((uint64_t)header[9] << 40) |
        ((uint64_t)header[10] << 48) |
        ((uint64_t)header[11] << 56);

    frame.data.resize(frame.size);

    if (!fin.read((char*)frame.data.data(), frame.size)) {
        return false;
    }

    return true;
}




// ================= Sequence Header =================
//void parse_sequence_header(const uint8_t* data, size_t size) 
// 针对 13 字节 VPL seq header
void parse_seq_header(const uint8_t* data, size_t size,AV1SeqInfo &seqInfo) 
{
    BitReader br(data, size);

    std::cout << "    [Sequence Header]\n";

    uint32_t profile = br.readBits(3);
    std::cout << "      profile = " << profile << "\n";

    br.readBit(); // still_picture
    br.readBit(); // reduced_still_picture_header

    uint32_t timing_info_present_flag = br.readBit();
    if (timing_info_present_flag) {
        br.readBits(32); // num_units_in_display_tick
        br.readBits(32); // time_scale

        uint32_t equal_picture_interval = br.readBit();
        if (equal_picture_interval) {
            while (br.readBit()); // skip UVLC
        }

        uint32_t decoder_model_info_present_flag = br.readBit();
        if (decoder_model_info_present_flag) {
            br.readBits(5 + 32 + 5 + 5); // simplified skip
        }
    }

    uint32_t initial_display_delay_present_flag = br.readBit();
    (void)initial_display_delay_present_flag;

    uint32_t operating_points_cnt_minus_1 = br.readBits(5);
    for (uint32_t i = 0; i <= operating_points_cnt_minus_1; i++) {
        br.readBits(12); // idc
        uint32_t level = br.readBits(5);
        (void)level;

        if (level > 7) br.readBit();

        uint32_t decoder_model_present = 0;
        if (timing_info_present_flag) {
            decoder_model_present = br.readBit();
        }

        if (decoder_model_present) {
            br.readBits(32); // buffer_delay
            br.readBits(32); // buffer_delay
            br.readBit();
        }

        if (initial_display_delay_present_flag) {
            uint32_t present = br.readBit();
            if (present) br.readBits(4);
        }
    }

    // 修正宽高读取
    uint32_t frame_width_bits_minus_1 = br.readBits(4);
    uint32_t frame_height_bits_minus_1 = br.readBits(4);

    uint32_t width = br.readBits(frame_width_bits_minus_1 + 1) + 1;
    uint32_t height = br.readBits(frame_height_bits_minus_1 + 1) + 1;

    std::cout << "      width   = " << width << "\n";
    std::cout << "      height  = " << height << "\n";
}















//
#if  0
//
{ // OBU_SEQUENCE_HEADER
    std::cout << "==== Found Sequence Header ====\n";

    BitReader br(p, payload_size);

    int profile = br.readBits(3);
    bool still_picture = br.readBit();
    bool reduced_header = br.readBit();

    std::cout << "profile: " << profile << "\n";
    std::cout << "still_picture: " << still_picture << "\n";
    std::cout << "reduced_header: " << reduced_header << "\n";

    if (!reduced_header) {
        bool timing_info_present = br.readBit();
        if (timing_info_present) {
            std::cout << "timing_info_present: 1\n";
            // 简化：跳过 timing_info
        }
        else {
            std::cout << "timing_info_present: 0\n";
        }
    }

    int max_width_bits = br.readBits(4) + 1;
    int max_height_bits = br.readBits(4) + 1;

    int width = br.readBits(max_width_bits) + 1;
    int height = br.readBits(max_height_bits) + 1;

    std::cout << "width: " << width << "\n";
    std::cout << "height: " << height << "\n";

    int frame_id_numbers_present_flag = br.readBit();
    (void)frame_id_numbers_present_flag;

    int use_128x128 = br.readBit();
    (void)use_128x128;

    int enable_filter_intra = br.readBit();
    (void)enable_filter_intra;

    int bit_depth = 8;
    if (profile == 2) {
        bit_depth = br.readBit() ? 12 : 10;
    }
    else {
        bit_depth = br.readBit() ? 10 : 8;
    }

    std::cout << "bit_depth: " << bit_depth << "\n";

    std::cout << "===============================\n";
}
//
#endif 



// ================= Frame Header =================
struct AV1FrameInfo {
    int frame_type = -1;
};

void parse_frame_header(const uint8_t* data, int size, AV1FrameInfo& info) {
    BitReader br(data, size);

    int show_existing = br.readBit();
    if (show_existing) return;

    info.frame_type = br.readBits(2);

    if (info.frame_type == 0) {
        cout << "  → KEY FRAME" << endl;
    }
}



//
//  这里应该是parse_frame, 一个frame包含很多obu
int parse_ivf_frame(const char* data, int size, Param_parseIvfFrame* pParam)
{
    parse_obu((const uint8_t*)data, size, pParam);
    return  0;
}

//
// ================= OBU Parser =================
//void parse_obu(const uint8_t* data, uint32_t size, AV1SeqInfo& seq) 
void parse_obu(const uint8_t* data, uint32_t size, Param_parseIvfFrame  *  pParam)
{
    uint32_t offset = 0;

    while (offset < size) {
        //
        int offset_start;
        offset_start = offset;

        //
        uint8_t header = data[offset++];

        uint8_t obu_type = (header >> 3) & 0x0F;
        uint8_t ext_flag = (header >> 2) & 1;
        uint8_t has_size = (header >> 1) & 1;

        if (ext_flag) offset += 1;

        //
        uint64_t obu_size = 0;

        //
        size_t leb = 0;
        if (has_size) {
            obu_size = read_leb128(data + offset, leb);
            offset += leb;
        }
        else {
            obu_size = size - offset;
        }
        
        //
        int headLen;
        headLen = 1;
        if (ext_flag)  headLen++;
        headLen += leb;

        //
        char* obuTypeStr;
        obuTypeStr = getObuTypeStr(obu_type);

        //
        cout << "OBU type=" << (int)obu_type
            << " "  <<  obuTypeStr
            << " len=" << headLen  +  obu_size 
            << " size=" << obu_size << endl;

        if (offset + obu_size > size) {
            cout << "  [ERROR] overflow" << endl;
            break;
        }

        //
        //  data  +  offset_start开始，一共是headLen  + obu_size字节。这个是完整的obu
        //

        //
        const uint8_t* payload = data + offset;

        // ===== 解析关键类型 =====
        if (obu_type == 1) {
            //
            int seqHeader_len = headLen + obu_size;
            if (seqHeader_len <= sizeof(pParam->seqHeader_buf)) {
                memcpy(pParam->seqHeader_buf, data + offset_start, seqHeader_len);
                pParam->seqHeader_len = seqHeader_len;
            }
            //
            parse_seq_header(payload, obu_size, pParam->seq);

            //
            pParam->bGot_seqHeader = true;

        }
        else if (obu_type == 3 || obu_type == 6) {

            AV1FrameInfo info;
            parse_frame_header(payload, obu_size, info);
            
            //
            if (info.frame_type == KEY_FRAME) {
                pParam->bGot_keyFrame = true;
            }

        }
        else if (obu_type == 7) {
            cout << "  → TILE DATA size=" << obu_size << endl;
        }

        offset += obu_size;
    }
}

// ================= MAIN =================
//int test_ivf_main(int argc, char* argv[]) 
int test_ivf_main( char* fn_in)
{

    ifstream fin(fn_in, ios::binary);
    if (!fin) {
        cout << "Cannot open file\n";
        return -1;
    }

    // 跳过 IVF 文件头
    fin.seekg(32);

    AV1SeqInfo seq;
    IVFFrame frame;

    int index = 0;

    while (read_ivf_frame(fin, frame)) {

        cout << "\n===== Frame " << index++
            << " ts=" << frame.timestamp
            << " size=" << frame.size << " =====" << endl;

        Param_parseIvfFrame param = { 0 };

        parse_obu(frame.data.data(), frame.size, &param);
    }

    return 0;
}

