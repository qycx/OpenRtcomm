
#include	"stdafx.h"

//
#include	<windows.h>
//
#include	<tchar.h>
#include	"imgFunc_open.h"

//#define  u_char  unsigned  char

//

//
void yuvNV12ToYV12(char* NV12, int w, int h, char* YV12)
{

    memcpy(YV12, NV12, w * h);//y分量

    //
    int W = w;
    int H = h;

    //
    for (int i = 0, j = 0; i < w * h / 4; i++, j += 2)

    {

        memcpy(YV12 + W * H + i + W * H / 4, NV12 + W * H + j, 1);//u分量

        memcpy(YV12 + W * H + i, NV12 + W * H + j + 1, 1);//v分量

    }

    return;
}


#if 10

typedef unsigned char UINT8;
typedef unsigned int UINT32;

static UINT8 RTable[256][256];
static UINT8 GTable[256][256][256];
static UINT8 BTable[256][256];

static void NV12_T_RGB_Table()
{
    int y, u, v, res;
    for (y = 0; y <= 255; y++)
        for (v = 0; v <= 255; v++)
        {
            res = y + 1.402 * (v - 128);  //r
            if (res > 255)	res = 255;
            if (res < 0)	res = 0;
            RTable[y][v] = res;
        }

    for (y = 0; y <= 255; y++)
        for (u = 0; u <= 255; u++)
            for (v = 0; v <= 255; v++)
            {
                res = y - 0.34414 * (u - 128) - 0.71414 * (v - 128); //g
                if (res > 255)	res = 255;
                if (res < 0)	res = 0;
                GTable[y][u][v] = res;
            }

    for (y = 0; y <= 255; y++)
        for (u = 0; u <= 255; u++)
        {
            res = y + 1.772 * (u - 128); //b
            if (res > 255)	res = 255;
            if (res < 0)	res = 0;
            BTable[y][u] = res;
        }
}

// 
class  CNV12Tab {
public:
    CNV12Tab() {
        NV12_T_RGB_Table();
    }
};

//
CNV12Tab g_nv12Tab;


//
static void NV12_T_BGR(unsigned int width, unsigned int height, unsigned char* yuyv, unsigned char* rgb,bool bFlipImg)
{
    const int nv_start = width * height;
    UINT32  i, j, index = 0, rgb_index = 0;
    UINT8 y, u, v;
    int r, g, b, nv_index = 0;

    //
    int					nBytesPerLine_rgb24 = (width * 24 + 31) / 32 * 4;
    unsigned  int		out;
    int rgbIncrement = 3;
    //bool bFlipImg = false;


    //
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++) {
            //nv_index = (rgb_index / 2 - width / 2 * ((i + 1) / 2)) * 2;
            nv_index = (i >> 1) * width + j - j % 2;

            y = yuyv[rgb_index];
            u = yuyv[nv_start + nv_index];
            v = yuyv[nv_start + nv_index + 1];

            r = RTable[y][v];
            g = GTable[y][u][v];
            b = BTable[y][u];

            //index = rgb_index % width + (height - i - 1) * width;
            index = rgb_index % width + i * width;
            //
            // 
            if (!bFlipImg) {
                out = (height - i - 1) * nBytesPerLine_rgb24 + j * 3;
            }
            else {
                out = (i)*nBytesPerLine_rgb24 + j * 3;
            }

            //
            rgb[out + 0] = b;
            rgb[out + 1] = g;
            rgb[out + 2] = r;

            //
            rgb_index++;
        }
    }
}

#endif




//
int nv12ToRgb24(unsigned char* data, unsigned char* rgb, int width, int height, bool bFlip) 
{

    NV12_T_BGR(width, height, data, rgb,bFlip);
    
    //
    return  0;

#if 0
    int yuvLen = width * height * 3 / 2;
    char* yv12 = (char*)malloc(yuvLen);
    //nv12ToYv12(width, height, data, yv12);
    yuvNV12ToYV12((char*)data, width, height, yv12);
    yv12ToRgb24((unsigned char*)yv12, rgb, width, height, false);
    free(yv12);
    return;
#endif


}


/////////////////////////////////////////


#include <stdint.h>

static inline uint8_t clip(int v)
{
    if (v < 0)   return 0;
    if (v > 255) return 255;
    return (uint8_t)v;
}

/*
 * BGR24 -> NV12
 * - BT.601
 * - U V interleaved (NV12)
 * - no float
 */

int bgr24ToNv12(
    unsigned  char  * bgr,
    unsigned  char  * nv12,
    int width,
    int height,
    int bflip
)
{
    uint8_t* yPlane = nv12;
    uint8_t* uvPlane = nv12 + width * height;

    // ---------- Y plane ----------
    for (int y = 0; y < height; y++)
    {
        int srcY = bflip ? (height - 1 - y) : y;

        const uint8_t* pBGR = bgr + srcY * width * 3;
        uint8_t* pY = yPlane + y * width;

        for (int x = 0; x < width; x++)
        {
            int B = pBGR[x * 3 + 0];
            int G = pBGR[x * 3 + 1];
            int R = pBGR[x * 3 + 2];

            // BT.601
            int Y = (66 * R + 129 * G + 25 * B + 128) >> 8;
            pY[x] = clip(Y + 16);
        }
    }

    // ---------- UV plane (2x2 subsample) ----------
    for (int y = 0; y < height; y += 2)
    {
        int srcY0 = bflip ? (height - 1 - y) : y;
        int srcY1 = bflip ? (height - 1 - (y + 1)) : (y + 1);

        const uint8_t* pBGR0 = bgr + srcY0 * width * 3;
        const uint8_t* pBGR1 = bgr + srcY1 * width * 3;

        uint8_t* pUV = uvPlane + (y / 2) * width;

        for (int x = 0; x < width; x += 2)
        {
            int U = 0, V = 0;

            // 2x2 block 平均
            for (int dy = 0; dy < 2; dy++)
            {
                const uint8_t* p = (dy == 0) ? pBGR0 : pBGR1;

                for (int dx = 0; dx < 2; dx++)
                {
                    int idx = (x + dx) * 3;
                    int B = p[idx + 0];
                    int G = p[idx + 1];
                    int R = p[idx + 2];

                    U += (-38 * R - 74 * G + 112 * B + 128) >> 8;
                    V += (112 * R - 94 * G - 18 * B + 128) >> 8;
                }
            }

            U = (U / 4) + 128;
            V = (V / 4) + 128;

            pUV[x + 0] = clip(U);
            pUV[x + 1] = clip(V);
        }
    }
    return 0;
}


