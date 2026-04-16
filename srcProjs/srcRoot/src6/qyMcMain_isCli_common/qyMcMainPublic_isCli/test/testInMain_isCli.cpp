
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include    "ctxQmc.h"


//
#ifdef  __DEBUG__

//
int testMp4_main();
int testMux_main(int argc, char** argv);




//
int  testInMain_isCli(QY_MC* pQyMc)
{
    //
    int iW = 640;
    int iH = 480;
    int bits = 24;
    int imgSize = M_sizeImage_open(bits, iW, iH);

    do {
        CQyMalloc mallocObj_rgb;
        char* rgb = mallocObj_rgb.mallocf(imgSize);
        if (!rgb)  break;
        

        //
        int ii;
        ii = sizeof(TRANSFER_AUDIO_DATA);
        ii = sizeof(TRANSFER_VIDEO_DATA);
        


        //
        //getFakePic(_T("c:\\tttbbb\\test\\k.bmp"), 640, 480, 24, rgb, imgSize);

    } while (false);

    
    //
	return  0;
}


//
#endif  



