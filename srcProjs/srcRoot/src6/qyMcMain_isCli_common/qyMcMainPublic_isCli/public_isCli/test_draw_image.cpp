

#include	"stdafx.h"
/*    Trim fat from windows*/

#include <stdio.h>
#include <windows.h>
#include	<Vfw.h>
#include <cstddef>
#include <iostream>
#include <iostream>

#include	"qyMcMainCommon.h"


char* bmp_image = NULL; // data for the bitmap image

//HDC HDC_handle; // pointer for HDC handle

BITMAPINFOHEADER bmp_head;

//
//int width = 0;
//int height = 0;
//int bitCount = 0;
//char* pRGBQUAD = NULL;

//
bool readBmpFile(char* filename)
{
	FILE* pf;
	char* pData = NULL;

	pf = fopen(filename, "rb");
	if (NULL == pf)
	{
		//cout << "文件打开失败!" << endl;
		//fclose(pf);
		return false;
	}
	BITMAPFILEHEADER bitMapFileHeader;
	BITMAPINFOHEADER bitMapInfoHeader;
	fread(&bitMapFileHeader, sizeof(BITMAPFILEHEADER), 1, pf);
	if (0x4D42 != bitMapFileHeader.bfType)
	{
		//cout << "此文件不是BMP文件！" << endl;
		return false;
	}
	fread(&bitMapInfoHeader, sizeof(BITMAPINFOHEADER), 1, pf);
	//cout << "位图文件头：" << endl;
	//cout << "位图文件类型: " << bitMapFileHeader.bfType << endl;
	//cout << "位图文件大小: " << bitMapFileHeader.bfSize << endl;
	//cout << "偏移的字节数: " << bitMapFileHeader.bfOffBits << endl;

	//width = bitMapInfoHeader.biWidth;
	//height = bitMapInfoHeader.biHeight;
	//bitCount = bitMapInfoHeader.biBitCount;
	//cout << "\n位图信息头：" << endl;
	//cout << "信息头占用字节数：" << bitMapInfoHeader.biSize << endl;
	//cout << "位图宽度： " << bitMapInfoHeader.biWidth << endl;
	//cout << "位图高度： " << bitMapInfoHeader.biHeight << endl;
	//cout << "位图压缩类型： " << bitMapInfoHeader.biCompression << endl;
	//cout << "位图每像素占用位数： " << bitMapInfoHeader.biBitCount << endl;
	//cout << "位图数据占用字节数： " << bitMapInfoHeader.biSizeImage << endl;


	if (8 == bitMapInfoHeader.biBitCount)
	{
		//pRGBQUAD = (char*)new RGBQUAD[256];
		//fread(pRGBQUAD, sizeof(RGBQUAD), 256, pf);
		goto errLabel;
	}
	//数据每行字节数为4的倍数
	int lineByte = (bitMapInfoHeader.biWidth * bitMapInfoHeader.biBitCount / 8 + 3) / 4 * 4;
	pData = (char*)malloc(bitMapInfoHeader.biHeight * lineByte);
	fread(pData, sizeof(unsigned char), bitMapInfoHeader.biHeight * lineByte, pf);





errLabel:


	fclose(pf);

	//
	bmp_head = bitMapInfoHeader;
	bmp_image = pData;


	//
	return true;
}


#ifdef  __DEBUG__

//
void test_draw_image(HDC hDC)
{
	HDRAWDIB img_handle; // pointer for a handle

	img_handle = DrawDibOpen();

	//
	readBmpFile((char*)"c:\\tttbbb\\kk.bmp");


	//
	DrawDibDraw(img_handle, hDC, 64, 48, 512, 384, &bmp_head, bmp_image, 64, 48,
		512, 384, 0); // still not sure about the first group of numbers
	DrawDibClose(img_handle); // free the resources
	//
	free(bmp_image);
}

#endif

