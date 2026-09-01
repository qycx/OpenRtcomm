
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
        TCHAR* tDev = (TCHAR*)_T("cy3014");
        TCHAR* tName = (TCHAR*)_T("CY3014 USB, Analog 01 Capture");

        //
        int  tmpiRet = _tcsnicmp(tDev, tName, lstrlen(tDev));
            //if (!_tcsnicmp(tDev, tName, lstrlen(tDev)))  continue;

        //
        printf("kk\n");
    

        



        //
        //getFakePic(_T("c:\\tttbbb\\test\\k.bmp"), 640, 480, 24, rgb, imgSize);

    } while (false);

    
    //
	return  0;
}


//
#endif  



