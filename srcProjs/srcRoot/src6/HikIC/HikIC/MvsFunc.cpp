
// testOpenCVDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MvsFunc.h"
#include "MvsFunc.h"
#include "afxdialogex.h"

#include <opencv2/opencv.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/video/video.hpp>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace cv;
using namespace std;



// CtestOpenCVDlg 对话框



CtestOpenCVDlg::CtestOpenCVDlg()	
{
}
CtestOpenCVDlg::~CtestOpenCVDlg()
{
}




#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/video/video.hpp>
#include <opencv2/opencv.hpp>
#include "camera_class.h"

#include <sstream>

#include <iomanip>
#include <chrono>
#include <sstream>
#include <ctime>
#include <fstream>

#include <stdio.h>
#include <tchar.h>
char* UnicodeToAnsi(const wchar_t* szStr, int& nLen)
{
	nLen = WideCharToMultiByte(CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL);
	if (nLen == 0)
	{
		return NULL;
	}
	char* pResult = new char[nLen];
	WideCharToMultiByte(CP_ACP, 0, szStr, -1, pResult, nLen, NULL, NULL);
	return pResult;
}


#include <chrono>
#include <sstream>
#include <iomanip>
#include <string>



std::string getDT() {
	auto now = std::chrono::system_clock::now();
	std::time_t now_time = std::chrono::system_clock::to_time_t(now);
	std::tm* now_tm = std::localtime(&now_time);

	std::stringstream ss;

	ss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S.");

	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
	ss << std::setw(3) << std::setfill('0') << millis.count();

	return ss.str();
}



int printLogChar(const char* log) {
	//return 0;

	if (log == nullptr)
		return 2;

	FILE* pf = fopen("D:/qycx/hik_ic.txt", "a+");
	if (pf == NULL)
	{
		perror("open hik_ic.txt failed.");
		//
		return 1;
	}

	//TCHAR* pp;


	//fprintf(pf, "%s:%s  - %s \n", __DATE__, __TIME__, log);
	fprintf(pf, "[%s]  - %s \n", getDT().c_str(), log);

	fclose(pf);

	return 0;

}


int printLog(TCHAR* log) {
	//return 0;

	if (log == nullptr)
		return 2;

	FILE* pf = fopen("D:\\qycx\\hik_ic.txt", "a+");
	if (pf == NULL)
	{
		perror("open hik_ic.txt failed.");
		//
		return 1;
	}

	//TCHAR* pp;

	char* pBuf = NULL;
	int nLen = 0;

	pBuf = UnicodeToAnsi(log, nLen);

	if (pBuf) {
		fprintf(pf, "[%s]  - %s \n", getDT().c_str(), pBuf);
		delete[] pBuf;
	}

	fclose(pf);

}


// 定义钩子函数类型
typedef void (*ImageDataHook)(void* p, unsigned char* pData, size_t size);

// 全局钩子函数指针
extern "C" __declspec(dllexport) ImageDataHook g_ImageDataHook = nullptr;

// 设置钩子函数的函数
extern "C" __declspec(dllexport) void SetImageDataHook(ImageDataHook hook) {
	g_ImageDataHook = hook;
}

extern "C" __declspec(dllexport) int GetImageSize(int& width, int& height) {
	int ret = -1;
	int nRet = MV_CC_Initialize();
	if (MV_OK != nRet)
	{
		std::cout << "SDK 初始化失败! Error code: " << nRet << std::endl;
		return -1;
	}

	MV_CC_DEVICE_INFO_LIST stDeviceList = { 0 };
	memset(&stDeviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
	nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList);
	if (MV_OK != nRet)
	{
		std::cout << "Enum devices failed! nRet [" << nRet << "]" << std::endl;
		return -1;
	}



	void* handle = nullptr;

	do {

		if (stDeviceList.nDeviceNum <= 0) {
			std::cout << "No devices found!" << std::endl;
			break;
		}


		MV_CC_DEVICE_INFO* pDeviceInfo = stDeviceList.pDeviceInfo[0];
		if (pDeviceInfo == nullptr) {
			std::cout << "Invalid device info!" << std::endl;
			break;
		}


		nRet = MV_CC_CreateHandle(&handle, pDeviceInfo);
		if (MV_OK != nRet)
		{
			std::cout << "Create handle failed! nRet [" << nRet << "]" << std::endl;
			break;
		}


		nRet = MV_CC_OpenDevice(handle);
		if (MV_OK != nRet)
		{
			std::cout << "Open device failed! nRet [" << nRet << "]" << std::endl;
			break;
		}

		MVCC_INTVALUE nWidth;
		nRet = MV_CC_GetIntValue(handle, "Width", &nWidth);
		if (nRet != MV_OK) {
			cout << "Get width failed!" << endl;
		}

		width = nWidth.nCurValue;

		MVCC_INTVALUE nHeight;
		nRet = MV_CC_GetIntValue(handle, "Height", &nHeight);
		if (nRet != MV_OK) {
			cout << "Get height failed!" << endl;
		}
		height = nHeight.nCurValue;
		ret = 0;

	} while (false);

	if (handle) {
		MV_CC_StopGrabbing(handle);
		MV_CC_CloseDevice(handle);
		MV_CC_DestroyHandle(handle);
	}

	//
	//MV_CC_FreeDeviceList(&stDeviceList);

	MV_CC_Finalize();

	return ret;
}

struct MVS_Param {
	void* handle = nullptr;
	void* p = nullptr;
};

void __stdcall ImageCallBack(unsigned char* pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser)
{
	static int i = 0;
	MVS_Param* param = (MVS_Param*)pUser;

	if (param == nullptr)
		return;
	

	if (pFrameInfo)
	{


#if  0
		using namespace std::chrono;
		auto now = system_clock::now();
		time_t now_c = system_clock::to_time_t(now);
		auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
		std::stringstream ss;
		ss << std::put_time(std::localtime(&now_c), "%Y%m%d%H%M%S_");
		ss << std::setw(3) << std::setfill('0') << ms.count();
		std::stringstream ssFile;
		ssFile << ".\\ouput_" << i << "_" << ss.str() << ".png\r\n";
		i++;

		static  bool  bClean = FALSE;
		FILE* fp = NULL;
		char* fn = ".\\kk.txt";
		if (!bClean) {
			fp = fopen(fn, "w");
			fclose(fp);  fp = NULL;
			bClean = TRUE;;
		}
		if (bClean) {
			fp = fopen(fn, "a+");
			if (fp) {
				fwrite(ssFile.str().c_str(), ssFile.str().length(), 1, fp);
				fclose(fp);  fp = NULL;
			}
		}
#endif

		using namespace std::chrono;
		auto now = system_clock::now();
		time_t now_c = system_clock::to_time_t(now);
		auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
		std::stringstream ss;
		ss << std::put_time(std::localtime(&now_c), "%Y%m%d%H%M%S_");
		ss << std::setw(3) << std::setfill('0') << ms.count();
		std::stringstream ssFile;
		ssFile << "C:\\tttbbb\\duli\\ouput_" << i << "_" << ss.str();
		std::string ssFileRaw = ssFile.str() + ".raw";
		i++;

		
		{
			int BufSizeForSaveImage = pFrameInfo->nWidth * pFrameInfo->nHeight * 3;
			unsigned char*  m_pBufForSaveImage = (unsigned char*)malloc(BufSizeForSaveImage);

			MV_CC_PIXEL_CONVERT_PARAM stConvertParam = { 0 };
			stConvertParam.nWidth = pFrameInfo->nWidth;
			stConvertParam.nHeight = pFrameInfo->nHeight;
			stConvertParam.pSrcData = pData;
			stConvertParam.nSrcDataLen = pFrameInfo->nFrameLen;
			stConvertParam.enSrcPixelType = pFrameInfo->enPixelType;
			stConvertParam.enDstPixelType = PixelType_Gvsp_BGR8_Packed;// PixelType_Gvsp_YUV422_Packed;//PixelType_Gvsp_BGR8_Packed;
			stConvertParam.pDstBuffer = m_pBufForSaveImage;
			stConvertParam.nDstBufferSize = BufSizeForSaveImage;

		
			int nRet = MV_CC_ConvertPixelType(param->handle, &stConvertParam);
			if (MV_OK != nRet)
			{
				std::cout << "Convert pixel type failed! nRet [" << nRet << "]" << std::endl;
				return;
			}

			// 调用钩子函数
			if (g_ImageDataHook) {
				g_ImageDataHook(param->p, m_pBufForSaveImage, BufSizeForSaveImage);
			}
#if 0
			FILE* fp = NULL;
			fp = fopen(ssFileRaw.c_str(), "wb");
			if(fp) {
			fwrite(m_pBufForSaveImage, BufSizeForSaveImage, 1, fp);

			fclose(fp);  fp = NULL;
			}
#endif
			

			
			free(m_pBufForSaveImage);

			const char* filePath = "D:/qycx/hikic.d";
			std::ifstream fileToCheck(filePath);
			if (fileToCheck.good()) {
				fileToCheck.close();
				std::stringstream ss;
				ss << "DoMvs:ImageCallBack，width=" << pFrameInfo->nWidth << ", height=" << pFrameInfo->nHeight << ", FrameLen=" << pFrameInfo->nFrameLen
					<< ", PixelType=" << pFrameInfo->enPixelType;
				printLogChar(ss.str().c_str());
			}

			Sleep(800);
			
		}
#if 0
		{
			cv::Mat image(pFrameInfo->nHeight, pFrameInfo->nWidth, CV_8UC3);


			MV_CC_PIXEL_CONVERT_PARAM stConvertParam = { 0 };
			stConvertParam.nWidth = pFrameInfo->nWidth;
			stConvertParam.nHeight = pFrameInfo->nHeight;
			stConvertParam.pSrcData = pData;
			stConvertParam.nSrcDataLen = pFrameInfo->nFrameLen;
			stConvertParam.enSrcPixelType = pFrameInfo->enPixelType;
			stConvertParam.enDstPixelType = PixelType_Gvsp_BGR8_Packed;
			stConvertParam.pDstBuffer = (unsigned char*)image.data;
			stConvertParam.nDstBufferSize = image.total() * image.elemSize();

			int nRet = MV_CC_ConvertPixelType(pUser, &stConvertParam);
			if (MV_OK != nRet)
			{
				std::cout << "Convert pixel type failed! nRet [" << nRet << "]" << std::endl;
				return;
			}

		
			std::string ssFileImg = ssFile.str() + ".png";

			//cv::imshow("Camera Image", image);
			//cv::waitKey(1);
			cv::imwrite(ssFileImg.c_str(), image);
		}
		
#endif
		
#if 0
		cv::Mat image(pFrameInfo->nHeight, pFrameInfo->nWidth, CV_8UC3);

	
		MV_CC_PIXEL_CONVERT_PARAM stConvertParam = { 0 };
		stConvertParam.nWidth = pFrameInfo->nWidth;
		stConvertParam.nHeight = pFrameInfo->nHeight;
		stConvertParam.pSrcData = pData;
		stConvertParam.nSrcDataLen = pFrameInfo->nFrameLen;
		stConvertParam.enSrcPixelType = pFrameInfo->enPixelType;
		stConvertParam.enDstPixelType = PixelType_Gvsp_YUV420SP_NV12;// PixelType_Gvsp_YUV422_Packed;//PixelType_Gvsp_BGR8_Packed;
		stConvertParam.pDstBuffer = (unsigned char*)image.data;
		stConvertParam.nDstBufferSize = image.total() * image.elemSize();

		int nRet = MV_CC_ConvertPixelType(pUser, &stConvertParam);
		if (MV_OK != nRet)
		{
			std::cout << "Convert pixel type failed! nRet [" << nRet << "]" << std::endl;
			return;
		}

		//
		//fwrite(buf, size, 1, fp);
		//matToYV12(image, )


		//
		using namespace std::chrono;
		auto now = system_clock::now();
		time_t now_c = system_clock::to_time_t(now);
		auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
		std::stringstream ss;
		ss << std::put_time(std::localtime(&now_c), "%Y%m%d%H%M%S_");
		ss << std::setw(3) << std::setfill('0') << ms.count();
		
、
		std::stringstream ssFile;
		ssFile << ".\\ouput_" << i << "_" << ss.str() << ".png";
		i++;

		//cv::imshow("Camera Image", image);
		//cv::waitKey(1);
		cv::imwrite(ssFile.str().c_str(), image);
		//

#endif
	}
}
// 自定义的钩子函数实现
void CustomImageDataHook(unsigned char* pData, size_t size) {
	std::cout << "Received m_pBufForSaveImage data of size: " << size << std::endl;
	// 这里可以对pData进行进一步处理
}



extern "C" __declspec(dllexport) int DoMvs(void* p, bool& stop) {

	printLogChar("DoMvs begin");
	
	int nRet = MV_CC_Initialize();
	if (MV_OK != nRet)
	{
		//std::cout << "SDK 初始化失败! Error code: " << nRet << std::endl;
		std::stringstream ss;
		ss << "DoMvs:MV_CC_Initialize failed,nRet=" << nRet;
		printLogChar(ss.str().c_str());
		return -1;
	}

	MV_CC_DEVICE_INFO_LIST stDeviceList = { 0 };
	memset(&stDeviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
	nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList);
	if (MV_OK != nRet)
	{
		//std::cout << "Enum devices failed! nRet [" << nRet << "]" << std::endl;
		std::stringstream ss;
		ss << "DoMvs:Enum devices failed,nRet=" << nRet;
		printLogChar(ss.str().c_str());
		return -1;
	}



	void* handle = nullptr;

		do  {

			if (stDeviceList.nDeviceNum <= 0) {
				//std::cout << "No devices found!" << std::endl;
				std::stringstream ss;
				ss << "DoMvs:No devices found!";
				printLogChar(ss.str().c_str());
				break;
			}	


			MV_CC_DEVICE_INFO* pDeviceInfo = stDeviceList.pDeviceInfo[0];
			if (pDeviceInfo == nullptr) {
				//std::cout << "Invalid device info!" << std::endl;
				std::stringstream ss;
				ss << "DoMvs:Invalid device info!";
				printLogChar(ss.str().c_str());
				break;
			}


			nRet = MV_CC_CreateHandle(&handle, pDeviceInfo);
			if (MV_OK != nRet)
			{
				//std::cout << "Create handle failed! nRet [" << nRet << "]" << std::endl;

				std::stringstream ss;
				ss << "DoMvs:Create handle failed， nRet" << nRet;
				printLogChar(ss.str().c_str());
				break;
			}


			nRet = MV_CC_OpenDevice(handle);
			if (MV_OK != nRet)
			{
				//std::cout << "Open device failed! nRet [" << nRet << "]" << std::endl;
				std::stringstream ss;
				ss << "DoMvs:Open device failed， nRet" << nRet;
				printLogChar(ss.str().c_str());
				break;
			}

			//MVCC_INTVALUE nWidth;
			//nRet = MV_CC_GetIntValue(handle, "Width", &nWidth);
			//if (nRet != MV_OK) {
			//	cout << "Get width failed!" << endl;
			//}

			//// 获取图像高度
			//MVCC_INTVALUE nHeight;
			//nRet = MV_CC_GetIntValue(handle, "Height", &nHeight);
			//if (nRet != MV_OK) {
			//	cout << "Get height failed!" << endl;
			//}

			nRet = MV_CC_SetEnumValue(handle, "TriggerMode", 0);
			if (MV_OK != nRet)
			{
				//std::cout << "Set trigger mode failed! nRet [" << nRet << "]" << std::endl;
				std::stringstream ss;
				ss << "DoMvs:Set trigger mode failed， nRet" << nRet;
				printLogChar(ss.str().c_str());
				break;
			}

			MVS_Param param;

			param.handle = handle;
			param.p = p;

			nRet = MV_CC_RegisterImageCallBackEx(handle, ImageCallBack, &param);
			if (MV_OK != nRet)
			{
				//std::cout << "Register image callback failed! nRet [" << nRet << "]" << std::endl;
				std::stringstream ss;
				ss << "DoMvs:Register image callback failed， nRet" << nRet;
				printLogChar(ss.str().c_str());
				break;
			}

			nRet = MV_CC_StartGrabbing(handle);
			if (MV_OK != nRet)
			{
				//std::cout << "Start grabbing failed! nRet [" << nRet << "]" << std::endl;
				std::stringstream ss;
				ss << "DoMvs:Start grabbing failed， nRet" << nRet;
				printLogChar(ss.str().c_str());
				break;
			}

			//std::cout << "Press any key to exit..." << std::endl;
			//std::cin.get();

			//int i = 0;
			printLogChar("DoMvs running........");
			while (!stop) {
				Sleep(1000);
				//i++;
				/*if (i > 100)
					break;*/
			}

		}  while (false);

		if (handle) {
			//MV_CC_StopGrabbing(handle);
			//MV_CC_CloseDevice(handle);
			//MV_CC_DestroyHandle(handle);

			int nRet = MV_CC_StopGrabbing(handle);
			if (nRet != MV_OK)
			{
				//std::cerr << "Stop grabbing failed! nRet = " << std::hex << nRet << std::endl;
				std::stringstream ss;
				ss << "DoMvs:Stop grabbing failed， nRet" << nRet;
				printLogChar(ss.str().c_str());
			}

			//nRet = MV_CC_UnRegisterImageCallBack(handle);
			//if (nRet != MV_OK)
			//{
			//	std::cerr << "Unregister callback failed! nRet = " << std::hex << nRet << std::endl;
			//}

			nRet = MV_CC_CloseDevice(handle);
			if (nRet != MV_OK)
			{
				//std::cerr << "Close device failed! nRet = " << std::hex << nRet << std::endl;
				std::stringstream ss;
				ss << "DoMvs:Close device failed， nRet" << nRet;
				printLogChar(ss.str().c_str());
			}

			nRet = MV_CC_DestroyHandle(handle);
			if (nRet != MV_OK)
			{
				//std::cerr << "Destroy handle failed! nRet = " << std::hex << nRet << std::endl;
				std::stringstream ss;
				ss << "DoMvs:Destroy handle failed， nRet" << nRet;
				printLogChar(ss.str().c_str());
			}


		}
	
		//
		//MV_CC_FreeDeviceList(&stDeviceList);
		nRet = MV_CC_Finalize();
		if (nRet != MV_OK)
		{
			//std::cerr << "Finalize SDK failed! nRet = " << std::hex << nRet << std::endl;

			std::stringstream ss;
			ss << "DoMvs:Finalize SDK failed， nRet" << nRet;
			printLogChar(ss.str().c_str());
		}

		printLogChar("DoMvs end");

	return 0;
}
