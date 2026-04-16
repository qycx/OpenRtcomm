
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include <colorSpaceFunc.h>
#include	<ctxQmc.h>


//
int  getFakePic(LPCTSTR  img_src, int bits, int iW, int iH,  char* rgb_dst,  int  rgbSize_dst  )
{
	int  iErr = -1;
	//
	FILE* fp = nullptr;
	char* rgb_src = nullptr;
	CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();

	//
	int neededRgbSize = M_sizeImage(bits, iW, iH);
	if (neededRgbSize > rgbSize_dst) return  -1;

	do {

		fp = _tfopen(img_src, _T("rb"));
		if (!fp)  break;

		BITMAPFILEHEADER FileHeader;
		BITMAPINFOHEADER bih;


		//
		if (1 != fread(&FileHeader, sizeof(BITMAPFILEHEADER), 1, fp))break;    //1.陣列or結構的指標 2.陣列or結構的大小
		if  (1!=fread(&bih, sizeof(BITMAPINFOHEADER), 1, fp))break;    //3.陣列的元素數量，如果是結構就等同 1 個陣列元素 4.指向結構 FILE 的指標

		if (bih.biBitCount != 24) break;

		//
		int ImageX = bih.biWidth;        // 取得寬高
		int ImageY = bih.biHeight;

		int imgSize_src = M_sizeImage(bih.biBitCount, bih.biWidth, bih.biHeight);
		CQyMalloc mallocObj_rgb_src;
		rgb_src = mallocObj_rgb_src.mallocf(imgSize_src);
		if (!rgb_src) break;
		RGBTRIPLE rgb;  memset(&rgb, 0, sizeof(rgb));
		RGBTRIPLE* color = (RGBTRIPLE*)rgb_src;
		  
		//
		for (int i = 0; i < ImageY; i++)        //逐列掃描
		{
			for (int j = 0; j < ImageX; j++)    //逐行掃描
			{
				if (1 != fread(&rgb, sizeof(RGBTRIPLE), 1, fp)) {
					break;        //將每格的pixel BGR 寫入 color matrix 中
				}
				color[i * ImageX + j].rgbtBlue = rgb.rgbtBlue;
				color[i * ImageX + j].rgbtGreen = rgb.rgbtGreen;
				color[i * ImageX + j].rgbtRed = rgb.rgbtRed;
			}
		}
		fclose(fp);  fp = nullptr;     //檔案fp讀取完成，關閉

		//
		//mySaveBitmap(&bih, rgb_src, false, _T("c:\\tttbbb\\test\\my.bmp"));

		//
		pProcInfo->resizeRgb24((unsigned  char *)rgb_src, bih.biWidth, bih.biHeight, (unsigned  char  *  )rgb_dst, iW, iH);

		//
#if 0
		BITMAPINFOHEADER bih_dst;
		makeBmpInfoHeader_rgb(bits, iW, iH, &bih_dst);
		mySaveBitmap(&bih_dst, rgb_dst, false, _T("c:\\tttbbb\\test\\resize.bmp"));
#endif

		




		//
		iErr = 0;


	} while (false);

errLabel:
	if (fp) {
		fclose(fp);
	}
	return  iErr;
}

