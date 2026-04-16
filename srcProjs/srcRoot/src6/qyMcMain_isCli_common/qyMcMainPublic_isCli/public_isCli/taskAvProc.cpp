
#include	"stdafx.h"
#include	<time.h>
#include	<stddef.h>
#include	<tchar.h>

//#include	"qyMcMainCommon.h"
#include	"ctxQmcTmpl.h"

#include	"qyGuiCommProc.h"

#include	"subtitles.h"

#include	"qmcVideoCapture.h"
#include	"qyMcMainRealTimeMediaProc.h"
#include	"qmcAcm.h"
//#include	"qyAvRecordPublic.h" 
#include	"qyVk.h"
#include	"qyMcMainInternalBak.h"
#include	<assert.h>
#include	"qmcDmoPublic.h"
#include	"tmpCeLib.h"

#include	"myDb.h"
#include	"qyMcMainCusModule.h"
#include	"taskAv.h"
 
//  
#include	"saveAvProc_open.h"
#include	"qmcCfg.h"
#include	"qmcTaskInfo.h"


//
#include <Windows.h>  
#include <iostream>  
#include <DXGI.h>  
#include <vector>  
#include <qmcVideoCapture_isCli.h>
#include <dumpVideo.h>

using namespace std;
std::string WStringToString(const std::wstring& wstr)
{
	std::string str(wstr.length(), ' ');
	std::copy(wstr.begin(), wstr.end(), str.begin());
	return str;
}


/*
//int CheckDisplayCard() 
int get_default_ucHardwareAccl()
{
	// 参数定义  
	IDXGIFactory* pFactory  =  null;
	IDXGIAdapter* pAdapter  =  null;
	std::vector <IDXGIAdapter*> vAdapters;            // 显卡  


	// 显卡的数量  
	int iAdapterNum = 0;


	// 创建一个DXGI工厂  
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory));

	if (FAILED(hr))
		return -1;

	// 枚举适配器  
	while (pFactory->EnumAdapters(iAdapterNum, &pAdapter) != DXGI_ERROR_NOT_FOUND)
	{
		vAdapters.push_back(pAdapter);
		++iAdapterNum;
	}

	// 信息输出   
	cout << "===============获取到" << iAdapterNum << "块显卡===============" << endl;

	int ret = -1;
	for (size_t i = 0; i < vAdapters.size(); i++)
	{
		// 获取信息  
		DXGI_ADAPTER_DESC adapterDesc;
		vAdapters[i]->GetDesc(&adapterDesc);
		wstring aa(adapterDesc.Description);
		std::string bb = WStringToString(aa);

		auto pos = bb.find("NVIDIA");

		if (pos != std::string::npos) {
			//ret = 2;
			ret = CONST_hdAccl_nv;
			break;
		}
		else {
			pos = bb.find("Intel");

			if (pos != std::string::npos) {
				ret = CONST_hdAccl_msdk_hardware;
			}
		}

	}


	for (auto const& item : vAdapters) {
		if(item)
			item->Release();
	}


	vAdapters.clear();

	//if (pAdapter) {
	//	pAdapter->Release();
	//}

	if (pFactory) {
		pFactory->Release();
	}

	//
	return ret;
}
*/


// 读取注册表字符串值
bool ReadRegistryString(HKEY rootKey, const wchar_t* subKey, const wchar_t* valueName, std::wstring& result) {
	HKEY hKey;
	LONG lResult = RegOpenKeyEx(rootKey, subKey, 0, KEY_QUERY_VALUE, &hKey);

	if (lResult != ERROR_SUCCESS) {
		std::wcerr << L"无法打开注册表项，错误码: " << lResult << std::endl;
		return false;
	}

	// 获取值的类型和大小
	DWORD dataType = REG_SZ;
	DWORD dataSize = 0;

	// 第一次调用获取数据大小
	lResult = RegQueryValueEx(hKey, valueName, 0, &dataType, NULL, &dataSize);

	if (lResult != ERROR_SUCCESS) {
		std::wcerr << L"无法获取值大小，错误码: " << lResult << std::endl;
		RegCloseKey(hKey);
		return false;
	}

	// 检查数据类型是否为字符串
	if (dataType != REG_SZ && dataType != REG_EXPAND_SZ) {
		std::wcerr << L"值类型不是字符串类型" << std::endl;
		RegCloseKey(hKey);
		return false;
	}

	// 分配内存并读取值
	std::wstring buffer(dataSize / sizeof(wchar_t), L'\0');
	lResult = RegQueryValueEx(hKey, valueName, 0, NULL,
		reinterpret_cast<LPBYTE>(&buffer[0]), &dataSize);

	if (lResult != ERROR_SUCCESS) {
		std::wcerr << L"无法读取值，错误码: " << lResult << std::endl;
		RegCloseKey(hKey);
		return false;
	}

	// 移除可能的终止空字符
	buffer.resize(wcslen(buffer.c_str()));
	result = buffer;

	RegCloseKey(hKey);
	return true;
}


//
//int CheckDisplayCard()
int get_default_ucHardwareAccl()
{
	// 参数定义
	IDXGIFactory* pFactory  =  mynull;
	IDXGIAdapter* pAdapter  =  mynull;
	//std::vector <IDXGIAdapter*> vAdapters;            // 显卡

	//
#ifdef  __DEBUG__
	//
#if 0
	if (0) {
		showInfo_open0(0, 0, _T("for test: set ucHardwareAccl to intel"));
		return  CONST_hdAccl_msdk_hardware;
	}
#endif
	//
#endif



	// 创建一个DXGI工厂
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory));

	if (FAILED(hr))
		return -1;

	int ret = -1;

	// 显卡的数量
	int iAdapterNum = 0;


	if (10) {
		iAdapterNum = 0;
		// 枚举适配器
		while (pFactory->EnumAdapters(iAdapterNum, &pAdapter) != DXGI_ERROR_NOT_FOUND)
		{
			//vAdapters.push_back(pAdapter);

				// 获取信息
			DXGI_ADAPTER_DESC adapterDesc;
			pAdapter->GetDesc(&adapterDesc);
			wstring aa(adapterDesc.Description);
			std::string bb = WStringToString(aa);

			auto pos = bb.find("NVIDIA");

			if (pos != std::string::npos) {
				//ret = 2;
					std::wstring registryValue;
				ReadRegistryString(HKEY_CURRENT_USER, L"Software\\Qycx\\misClient\\Scheduler", L"ucHardwareAccl_qt", registryValue);
				//qt专用
				if (registryValue == L"2") {
					ret = 2;
				}
				else {
					ret = CONST_hdAccl_nv;
				}
							}

			//
			MACRO_safeRelease(pAdapter);

			//
			if (ret > 0) {
				break;
			}

			//
			++iAdapterNum;
		}
	}


	if (ret < 0) {
		iAdapterNum = 0;
		// 枚举适配器
		while (pFactory->EnumAdapters(iAdapterNum, &pAdapter) != DXGI_ERROR_NOT_FOUND)
		{
			//vAdapters.push_back(pAdapter);

				// 获取信息
			DXGI_ADAPTER_DESC adapterDesc;
			pAdapter->GetDesc(&adapterDesc);
			wstring aa(adapterDesc.Description);
			std::string bb = WStringToString(aa);

			auto pos = bb.find("Intel");

			if (pos != std::string::npos) {
				//ret = 2;
				ret = CONST_hdAccl_msdk_hardware;
			}

			//
			MACRO_safeRelease(pAdapter);

			//
			if (ret > 0) {
				break;
			}

			//
			++iAdapterNum;
		}

	}



	//vAdapters.clear();
#if  0
	if (pAdapter) {
		pAdapter->Release();
	}
#endif

	//
	if (pFactory) {
		pFactory->Release();
	}

	//
	return ret;
}








//
int  get_ucHardwareAccl(  QY_MC  *  pQyMc  )
{
	int  iRet  =  -1;
			
	//CCtxQyMc *pQyMc = QY_GET_GBUF();
	CCtxQmc *pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();
	QMC_cfg *pQmcCfg=(QMC_cfg*)pProcInfo->get_qmc_cfg();


	if  (  pQyMc->appParams.bMcu  )  {	
		iRet  =  pProcInfo->av.doConf.confReq.ucHardwareAccl;  goto  errLabel;
	}


#if 0
	if  (  pQmcCfg  )  {
		iRet  =  pQmcCfg->policy.ucHardwareAccl;  goto  errLabel;
	}
#endif

	int iVal; iVal = pProcInfo->iDefault_ucHardwareAccl;
	if (iVal > 0) {
			iRet = iVal;   goto  errLabel;

	}
	

			


	//
	iRet  =  0;

	
errLabel:

	TCHAR  tBuf[128];

	//
#if 0
	if ( pQyMc->appParams.bUse_forTest_useNv  )  {
		showInfo_open0(  0, 0,  _T(  "for test:  get_ucHardwareAccl, use Nv"  )  );
		iRet  = CONST_hdAccl_nv;
	}
#endif

#ifdef  __DEBUG__
		//
	if (!iRet) {
		CCtxQyMc* pQyMc = g_pQyMc;
		iRet = pQyMc->appParams.ucHardwareAccl_forDbg;
		//
		showInfo_open0(0, 0, _T("for test:  get_ucHardwareAccl, use ucHardwareAccl_forDbg"));
	}
#endif



	//
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "get_ucbHardwarwAccl %d"  ),  iRet  );
	showInfo_open0(  0,  0,  tBuf  );

	return  iRet;
			
}


//
 int adjustModuleType_decV( QY_MC  *  pQyMc,  uint *uiModuleType_toDec)
        {
			//CCtxQyMc *pQyMc = QY_GET_GBUF();
			CCtxQmc *pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

			//
#if 0
		 if  (  bLikeXp(  )  )  {
			 if  (  *uiModuleType_toDec  ==  CONST_moduleType_mediaSdk_dec  )  {
				 *uiModuleType_toDec  =  CONST_moduleType_ipp;
				 //
				 qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Adjusted: for Xp, use ipp to decode h264"  )  );
			 }
			 }
		 else  
#endif
		 {

			   /////////
			   //
			   if  (  *uiModuleType_toDec  ==  CONST_moduleType_ipp  )  {					   				
				   *uiModuleType_toDec  =  CONST_moduleType_mediaSdk_dec;							 
				   //
				   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Adjusted: for x64, use mediaSdk to decode h264"  )  );			 				   					
			   }				   
		 }

		 //  2014/06/25
		 unsigned  char  ucHardwareAccl  =  get_ucHardwareAccl(pQyMc);
		 
		
		 switch  (  ucHardwareAccl  )  {
					 case  CONST_hdAccl_nv:
						   if  (  *uiModuleType_toDec  ==  CONST_moduleType_mediaSdk_dec  )  {

							   if (pQyMc->appParams.bUse_decD3d_nv) {
								   *uiModuleType_toDec = CONST_moduleType_decD3d_nv;
								   //
								   showInfo_open0(0, 0, _T("Adjusted: for nv, use decD3d_nv to decode h264."));

								   }
							   else 
							   {
								   *uiModuleType_toDec = CONST_moduleType_dec_nv;
								   //
								   showInfo_open0(0, 0, _T("Adjusted: for nv, use nv to decode h264."));
							   }

						   }
						   break;
					 case  CONST_hdAccl_amf:	//  2015/04/30
						   if  (  *uiModuleType_toDec  ==  CONST_moduleType_mediaSdk_dec  )  {
							   *uiModuleType_toDec  =  CONST_moduleType_dec_amf;
							   //
							   qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Adjusted: for amf, use amf to decode msdk h264."  )  );				   
						   }
						   break;
					 default:
						 //
						 if (!pQyMc->bUse_msdk) {
							 if (*uiModuleType_toDec == CONST_moduleType_mediaSdk_dec) {
								 *uiModuleType_toDec = CONST_moduleType_dec_vpl;
							 }
						 }
						 //	
						 break;	 
		 }

			return 0;
		}


		int adjustModuleType_encV(  uint *uiModuleType)
        {
			CCtxQyMc *pQyMc = g_pQyMc;
			CCtxQmc *pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

			//
            switch (*uiModuleType)
            {
				case  CONST_moduleType_enc_nv:
					//
					if (pQyMc->appParams.bUse_encD3d_nv) {
						*uiModuleType = CONST_moduleType_encD3d_nv;
					}
					//
#if 0 
					*uiModuleType  =  CONST_moduleType_ffmpeg;
					//
					qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Adjusted: for nv, use ffmpeg to encode h264."  )  );				   
#endif
					int  ii;
					ii = 0;
					//
                    break;
				default:
					//
					if (!pQyMc->bUse_msdk) {
						if (*uiModuleType == CONST_moduleType_mediaSdk_enc) {
							*uiModuleType = CONST_moduleType_enc_vpl;
						}
					}
					//
					break;
			}

			return 0;
        }


		//

		int adjustModuleType_decA( uint *uiModuleType)
		{
			CCtxQyMc *pQyMc = g_pQyMc;
			CCtxQmc *pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

#if 0
			//
			switch (uiModuleType)
			{
				case Consts.CONST_moduleType_ffmpeg:
					{ 
						uiModuleType = Consts.CONST_moduleType_mediaCodec;
					}
					break;
				default:
					break;
			}
#endif

			return 0;
		}

		//
		int adjustAudioBitrate(AUDIO_COMPRESSOR_cfgCommon* pCompressor)
		{
			//
			if (1) {

			}

			//
			return  0;
		}

		//
		int  getModuleType_encV(VIDEO_COMPRESSOR_cfgCommon* pCompressor, unsigned  int* puiModuleType)
		{
			int  iErr = -1;
			CCtxQyMc* pQyMc = g_pQyMc;
			CCtxQmc* pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

			//
			unsigned  int  uiModuleType = 0;

			//
			switch (pCompressor->ucCompressors) {
			case  CONST_videoCompressors_ipp:		//  2011/07/31
				//  
				uiModuleType = CONST_moduleType_ipp;
				//
				break;
			case  CONST_videoCompressors_hwAccl:
				//  
				uiModuleType = CONST_moduleType_mediaSdk_enc;

				//if (pQmcCfg->ucb__USE_hdEnc_conf__)  uiModuleType = CONST_moduleType_mediaSdk_enc_conf;	//  2014/07/01
				//
				//  2014/07/05
				unsigned  char  ucHardwareAccl;
				ucHardwareAccl = get_ucHardwareAccl(pQyMc);
				//
				switch (ucHardwareAccl) {
				case  CONST_hdAccl_msdk_hardware:
					//
					uiModuleType = CONST_moduleType_mediaSdk_enc;
					//
					break;
				case  0:
				case  CONST_hdAccl_nv:
					uiModuleType = CONST_moduleType_enc_nv;
					//
					qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", _T("IsClient"), 0, _T(""), _T(""), _T("Adjusted: for nv, use nv to enc haccl h264."));
					break;
				case  CONST_hdAccl_amf:
					uiModuleType = CONST_moduleType_enc_amf;
					//
					qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)"", _T("IsClient"), 0, _T(""), _T(""), _T("Adjusted: for amf, use amf to enc haccl h264."));
					break;
				default:
					break;
				}
				//
				break;
#if  0
			case  CONST_videoCompressors_cuda:	//  2012/06/18
				//  
				uiModuleType = CONST_moduleType_enc_nv;
				break;
#endif
			case  CONST_videoCompressors_vp8:		//  2014/07/19
				//
				uiModuleType = CONST_moduleType_enc_vp8;
				break;
			case  CONST_videoCompressors_custom:
				//  
				uiModuleType = CONST_moduleType_compress;
				break;
			default:
#ifdef  __DEBUG__
				traceLogA((char*)"initCompressVideo: ucCompressors err: %d", (int)pCompressor->ucCompressors);
#endif
				qyShowInfo1(CONST_qyShowType_qwmComm, 0, (char*)(""), pProcInfo->who_showInfo, 0, _T(""), _T(""), _T("initCompressVideo: ucCompressors err: %d"), (int)pCompressor->ucCompressors);
				goto  errLabel;
				break;
			}

			//
			adjustModuleType_encV(&uiModuleType);


			*puiModuleType = uiModuleType;

			//
			iErr = 0;

		errLabel:
			return  iErr;

		}


		//
		int  getInputFourcc_encV(unsigned  int  uiModuleType, int* piFourcc)
		{
			int  iFourcc = 0;

			iFourcc = CONST_fourcc_I420;

			switch (uiModuleType) {
			case  CONST_moduleType_enc_vpl:
				iFourcc = CONST_fourcc_NV12;
				break;
			default:
				break;
			}

			if (piFourcc)  *piFourcc = iFourcc;
			return  0;
		}




//  2014/03/25
int  transformGetSpsPps(  unsigned  int  uiTransformType,  void  *  pQY_TRANSFORM,  int  index_pMems_from,  char  *  pBuf,  unsigned  int  *  puiSize  );








 //


int  initTaskAvFrom_video(  void  *  pMC_VAR_common,  DLG_TALK_videoConferenceActiveMemFrom  *  pActiveMem_from,  int  index_activeMems_from,  int  iTaskId,  unsigned  int  uiModuleType_suggested,  BOOL  bUseDecTool_suggested,  QY_TRANSFORM  *  pTransform  )
{
	int							iErr				=	-1;

	CCtxQmc  *  pProcInfo  =  (  CCtxQmc  *  )pMC_VAR_common;
	QY_MC* pQyMc = pProcInfo->pQyMc;

	//
	TCHAR						tHintBuf[256]		=	_T(  ""  );
	int							tmpiRet				=	-1;
	int							i;
	TCHAR						tBuf[128];

	//
	QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	if  (  !pQmcCfg  )  return  -1;

	//
	CUS_MODULES  *  pCusModules  =  (  CUS_MODULES  *  )pProcInfo->getCusModules(  );
	if  (  !pCusModules  )  return  -1;

	//
	PROC_TASK_AV				*	pTask		=	(  PROC_TASK_AV  *  )pTransform->pTask;
	if  (  !pTask  )  {  //  2014/08/04
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initTaskAvFrom_video failed: pTask is null."  )  );
		return  -1;
	}
	TRANSFORM_VIDEO_procInfo  *  pTransformVideo  =  &pTransform->video;

	//
	MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));
	pMisCnt->status.dwLastTickCnt_initTaskAvFrom_video = myGetTickCount(nullptr);


	//
	pTransformVideo->idInfo.ui64Id = pActiveMem_from->avStream.idInfo.ui64Id;
	if (pTransform->index_activeMems_from != index_activeMems_from) {
		int  ii = 0;
	}

	//
	if  (  1  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "initTaskAvFrom_video actives[%d] %I64u enters"  ),  index_activeMems_from,  pActiveMem_from->avStream.idInfo.ui64Id  );
			//
			char  buf[128];
			#if  10
				iFourcc2Str(  pActiveMem_from->avStream.obj.tranInfo.video.vh_stream.dwFourcc,  buf,  mycountof(  buf  )  );
				_sntprintf(  tBuf,  mycountof(  tBuf ),  _T(  "%s vh_stream.%S"  ),  tBuf,  buf  );
			#else
				iFourcc2Str(  pFrom->video.tv_recvd.vh_compress.bih.biCompression,  buf,  mycountof(  buf  )  );
				_sntprintf(  tBuf,  mycountof(  tBuf ),  _T(  "%s vh_compress.%S"  ),  tBuf,  buf  );
			#endif
			//
			traceLog((TCHAR*)  tBuf  );
			showInfo_open0(  0,  0,  tBuf  );
	}

	//  2012/03/19
	MACRO_setMyStep(  pTransformVideo->debugStep,  31  );

	//
	if  (  pTransformVideo->ucbInited  )  {	//  2009/05/29
		traceLogA(  (char*)  "initTaskAvFrom_video failed: already inited."  );
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initTaskAvFrom_video failed: already inited."  )  );
		goto  errLabel;
	}

	if  (  !pTransformVideo->ucbInited  )  {  				
		//  DWORD				biSizeImage;

#ifdef  __DEBUG__	//  for test. 2015/01/15
		//pTransformVideo->decInfo.pts.uiPts_lastRecvd  =  99;
#endif

		try  {

			//  2009/05/28
			{
				CQySyncObj	syncObj;
				TCHAR		mutexName[128];
				//  2011/07/03
				//  _sntprintf(  mutexName,  mycountof(  mutexName  ),  _T(  "%s%d"  ),  pProcInfo->cfg_mutexName_syncActiveMem_prefix,  iTaskId  );
				M_getMutexName_syncActiveMem(  pQmcCfg,  iTaskId,  mutexName,  mycountof(  mutexName  )  );
				if  (  syncObj.sync(  mutexName,  1000  )  )  goto  errLabel;

				pTransformVideo->idInfo.ui64Id  =  pActiveMem_from->avStream.idInfo.ui64Id;
				pTransformVideo->tv.uiTranNo_openAvDev  =  pActiveMem_from->avStream.obj.tranInfo.video.uiTranNo_openAvDev;
				//
				pTransformVideo->tv.compressor.common.ucCompressors  =  pActiveMem_from->avStream.obj.tranInfo.video.compressor.common.ucCompressors;
				pTransformVideo->tv.compressor.common.usMaxFps_toShareBmp  =  pActiveMem_from->avStream.obj.tranInfo.video.compressor.common.usMaxFps_toShareBmp;		//  2014/08/07
				//pTransformVideo->tv.compressor.common.ucbOutputFlippedImg  =  pFrom->video.tv_recvd.compressor.common.ucbOutputFlippedImg;		//  2011/12/11
				//
				memcpy(  &pTransformVideo->tv.vh_compress,  &pActiveMem_from->avStream.obj.tranInfo.video.vh_compress,  sizeof(  pTransformVideo->tv.vh_compress  )  );

				//  2014/02/25
				memcpy(  &pTransformVideo->tv.vh_stream,  &pActiveMem_from->avStream.obj.tranInfo.video.vh_stream,  sizeof(  pTransformVideo->tv.vh_stream  )  );
				if  (  !pTransformVideo->tv.vh_stream.dwFourcc  )  {
					pTransformVideo->tv.vh_stream.dwFourcc  =   pActiveMem_from->avStream.obj.tranInfo.video.vh_compress.bih.biCompression;
					#ifdef  __DEBUG__
							traceLog((TCHAR*)  _T(  "vh_stream.dwFourcc is set to vh_compress_recvd"  )  );
					#endif
				}
				
				//  2014/09/23
				if  (  bSupported_sendVhDec(  )  )  {
					memcpy(  &pTransformVideo->tv.vh_decompress,  &pActiveMem_from->avStream.obj.tranInfo.video.vh_decompress,  sizeof(  pTransformVideo->tv.vh_decompress  )  );
					}
				else  {  //  2014/09/23. 用vh_compress的信息来填充vh_decompress
					  switch  (  pTransformVideo->tv.compressor.common.ucCompressors  )  {
							  case  CONST_videoCompressors_vcm:
							  case  CONST_videoCompressors_dmo:
								    makeBmpInfoHeader_rgb(  24,  pTransformVideo->tv.vh_compress.bih.biWidth,  pTransformVideo->tv.vh_compress.bih.biHeight,  &pTransformVideo->tv.vh_decompress.bih  );
								    break;
							  default:
									 break;
					  }
				}


				//  2014/08/05
				pTransformVideo->dwLastmodifiedTickCnt_keyParams  =  GetTickCount(  );
			}

			//  2014/08/30
			char  fourcc[4  +  1]  =  "";
			iFourcc2Str(  pTransformVideo->tv.vh_stream.dwFourcc,  fourcc,  mycountof(  fourcc  )  );
			_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%sfourcc %S."  ),  tHintBuf,  fourcc  );
			if  (  pTransformVideo->tv.vh_stream.usCnt  )  {
				_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%sspspps [cnt %d] %d,%d."  ),  tHintBuf,  (  int  )pTransformVideo->tv.vh_stream.usCnt,  (  int  )pTransformVideo->tv.vh_stream.mems[0].usLen,  (  int  )pTransformVideo->tv.vh_stream.mems[1].usLen  );
			}
			

			}
#ifdef  __useMfc__
		catch  (  CException  *  e  )  {
				e->Delete(  );
				goto  errLabel;
		}
#endif
		catch  (  ...  )  {
				goto  errLabel;
		}

		//
		memset(  &pTransformVideo->debugStep,  0,  sizeof(  pTransformVideo->debugStep  )  );	//  2014/08/11
		memset(  &pTransformVideo->status,  0,  sizeof(  pTransformVideo->status  )  );
		//  2015/01/15
		memset(  &pTransformVideo->decInfo,  0,  sizeof(  pTransformVideo->decInfo  )  );

		//  2012/03/19
		MACRO_setMyStep(  pTransformVideo->debugStep,  33  );


		//
		if  (  !pActiveMem_from->avStream.obj.tranInfo.video.compressor.common.ucCompressors  )  pTransformVideo->tv.compressor.common.ucCompressors  =  CONST_videoCompressors_vcm;		//  2009/03/30

		//  2014/0325
		memset(  &pTransformVideo->u,  0,  sizeof(  pTransformVideo->u  )  );

		//
#ifdef  __DEBUG__
		//showInfo_open0(  0,  0,  _T(  "initTaskAvFrom_video ...8885"  )  );
#endif

		//
		if  (  pTransformVideo->tv.compressor.common.ucCompressors  ==  CONST_videoCompressors_vcm  )  {
			DWORD				fccHandler	=	0;
			int					iFormatSize	=	0;
			BITMAPINFO		*	pBmpInfo	=	NULL;

			//
			if  (  !pActiveMem_from->avStream.obj.tranInfo.video.compressor.common.fourccStr[0]  )  {
				traceLogA(  (char*)  "tmpHandler_findOrgMsgAndProc_is err . no fourccStr"  );  
				_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  " no fourcc"  )  );
				goto  errLabel;
			}
			fccHandler  =  fourccStr2i(  (  char  *  )pActiveMem_from->avStream.obj.tranInfo.video.compressor.common.fourccStr  );

#ifndef  __WINCE__
			//
			if  (  !pTransformVideo->u.vcm.hicDecompress  )  
			{
				pTransformVideo->u.vcm.hicDecompress  =  ICOpen(  ICTYPE_VIDEO,  fccHandler,  ICMODE_FASTDECOMPRESS  );
				//  
				if  (  !pTransformVideo->u.vcm.hicDecompress  )  
				{
					traceLogA(  (char*)  "tmpHandler_findOrgMsgAndProc_is err . ICOpen failed."  );  
					_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "  ICOpen failed, fourcc is %s"  ),  CQyString(  pActiveMem_from->avStream.obj.tranInfo.video.compressor.common.fourccStr  )  );
					goto  errLabel;
				}	
			}
			//
			//  
			iFormatSize  =  ICDecompressGetFormat(  (  HIC  )pTransformVideo->u.vcm.hicDecompress,  &pTransformVideo->tv.vh_compress.bih,  0  );
			if  (  iFormatSize  <=  0  )  goto  errLabel;
			if  (  !(  pBmpInfo  =  (  BITMAPINFO  *  )mymalloc(  iFormatSize  )  )  )  goto  errLabel;
			else  {  
				  //  
				  tmpiRet  =  ICDecompressGetFormat(  (  HIC  )pTransformVideo->u.vcm.hicDecompress,  &pTransformVideo->tv.vh_compress.bih,  pBmpInfo  );
				  traceLogA(  (char*)  ""  );
				  if  (  tmpiRet  !=  ICERR_OK  )  _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s ICDecompressGetFormat failed, skipped."  ),  tHintBuf  );
				  free(  pBmpInfo  );
			}
			//  
			if  (  ICDecompressQuery(  (  HIC  )pTransformVideo->u.vcm.hicDecompress,  &pTransformVideo->tv.vh_compress.bih,  &pTransformVideo->tv.vh_decompress.bih  )  !=  ICERR_OK  )  
			{
				traceLogA(  (char*)  "tmpHandler_findOrgMsgAndProc_is. ICDecompressQuery failed."  );
				goto  errLabel;
			}
#else
			traceLog((TCHAR*)  _T(  "vcm is not supported in winCe"  )  );
			goto  errLabel;
#endif
			}
		else  if  (  pTransformVideo->tv.compressor.common.ucCompressors  ==  CONST_videoCompressors_dmo  )  {			

				  #if  0
			      		//  pFrom->video.u.dmo.usCnt  =  pFrom->ucbVideoConferenceStarter  ?  mycountof(  pFrom->video.u.dmo.dmoInfos  )  :  1;
						pTransformVideo->u.dmo.usCnt  =  pFrom->ucbVideoConferenceStarter  ?  mycountof(  pTransformVideo->u.dmo.dmoInfos  )  :  1;
				
						//  for  (  i  =  0;  i  <  pFrom->video.u.dmo.usCnt;  i  ++  )  
						for  (  i  =  0;  i  <  pTransformVideo->u.dmo.usCnt;  i  ++  )  
					  {
						  //  if  (  initDmoDecompressVideo(  &pFrom->video.compressor,  &pFrom->video.vh_compress,  &pFrom->video.vh_decompress,  &pFrom->video.u.dmo.dmoInfos[i]  )  )  
						  if  (  initDecompressVideo_dmo(  &pFrom->video.compressor,  &pTransformVideo->vh_compress,  &pTransformVideo->vh_decompress,  &pTransformVideo->u.dmo.dmoInfos[i]  )  )  
						   {
							   traceLogA(  (char*)  "initTaskAvFrom_video: initDmoDecompressVideo failed."  );
							   goto  errLabel;
						   }
					  }
				  #endif
 
				  if  (  pQmcCfg->ucb__SUPPORT_dmoToDec__  )  {				  
					  if  (  initDecompressVideo_dmo(  &pActiveMem_from->avStream.obj.tranInfo.video.compressor,  &pTransformVideo->tv.vh_compress,  &pTransformVideo->tv.vh_decompress,  &pTransformVideo->debugStep,  &pTransformVideo->u.dmo  )  )  {
						  traceLogA(  (char*)  "initTaskAvFrom_video: initDmoDecompressVideo failed."  );
						  _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s initDecompressVideo_dmo failed."  ),  tHintBuf  );
						  goto  errLabel;
					  }
					  }
				  else  {
					    //if  (  initDecompressVideo_filterGraph(  &pFrom->video.tv_recvd.compressor,  &pTransformVideo->tv.vh_compress,  &pTransformVideo->tv.vh_decompress,  &pTransformVideo->debugStep,  &pTransformVideo->u.dmo  )  )  
						{
						    traceLogA(  (char*)  "initTaskAvFrom_video: initDmoDecompressVideo failed."  );
							_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s initDecompressVideo_filterGraph failed."  ),  tHintBuf  );
							goto  errLabel;
						}
				  }

				  }

		else  {
			  CUS_MODULE_U	*	pModule			=	NULL;
			  unsigned  int		uiModuleType	=	0;				//  2012/09/09

			  //
	  		//
#ifdef  __DEBUG__
		showInfo_open0(  0,  0,  _T(  "initTaskAvFrom_video ...8888"  )  );
#endif


			  //
			  switch  (  pTransformVideo->tv.compressor.common.ucCompressors  )  {
					  case  CONST_videoCompressors_ipp:				//  2011/07/31
				  		    //  pModule	=	pQyMc->cusModules.pIpp;
							uiModuleType  =  CONST_moduleType_ipp;	//  2012/09/09
							break;
					  case  CONST_videoCompressors_hwAccl:		//  2011/11/25
					  case  CONST_videoCompressors_ffmpeg:
						#if  0
							#ifdef  __USE_ippToDecMediaSdk__
									pModule  =  pQyMc->cusModules.pIpp;		//  暂时采用ipp来替
							#else						    
									pModule  =  pQyMc->cusModules.pMediaSdk;
							#endif
						#endif
							if  (  pCusModules->pMediaSdk_dec
								&&  pCusModules->pMediaSdk_dec->compress.hModule
								&&  !pCusModules->pMediaSdk_dec->compress.mgr.ucbNotSupported_dec_h264  )  
							{
									uiModuleType  =  CONST_moduleType_mediaSdk_dec;
									}
							else  {
								  //uiModuleType  =  CONST_moduleType_ipp;
								  uiModuleType  =  CONST_moduleType_mediaSdk_dec;
							}
						    break;
#if  0
					  case  CONST_videoCompressors_cuda:				//  2012/06/18
							#if  0
							#ifdef  __USE_ippToDecCuda__
									pModule  =  pQyMc->cusModules.pIpp;
							#else
									pModule  =  pQyMc->cusModules.pCuda;
							#endif
							#endif
							uiModuleType  =  CONST_moduleType_ipp;
						    break;
#endif
					  case  CONST_videoCompressors_stream:
						    switch  (  pTransformVideo->tv.vh_stream.dwFourcc  )  {
									case  CONST_fourcc_h264:
									case  CONST_fourcc_HEVC:	//  2017/10/08
										  break;
									default:  {							
											  #ifdef  __DEBUG__
													  char  fourccStr[5]  =  "";
													  iFourcc2Str(  pTransformVideo->tv.vh_stream.dwFourcc,  fourccStr,  mycountof(  fourccStr  )  );
													  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "initTaskAvFrom_video failed, stream, fourcc err, %S"  ),  fourccStr  );
													  traceLog((TCHAR*)  tBuf  );
													  showInfo_open0(  0,  0,  tBuf  );
											  #endif
											  goto  errLabel;						  							
											  }
											  break;
							}
						    uiModuleType  =  CONST_moduleType_ipp;
							//
						    break;
					  case  CONST_videoCompressors_vp8:		//  2014/07/21
						    uiModuleType  =  CONST_moduleType_dec_vp8;
						    break;
					  case  CONST_videoCompressors_custom:
						    //  pModule	=	getCusModule(  pProcInfo->pQyMc,  CONST_moduleType_compress  );
							uiModuleType  =  CONST_moduleType_compress;
							break;						    
					  default:
							 #ifdef  __DEBUG__
									 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "initTaskAvFrom_video: ucCompressors error, %d"  ),  (  int  )pTransformVideo->tv.compressor.common.ucCompressors  );
									 traceLog((TCHAR*)  tBuf  );
									 showInfo_open0(  0,  0,  tBuf  );
							 #endif
							 _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s ucCompressors error, %d"  ),  tHintBuf,  (  int  )pTransformVideo->tv.compressor.common.ucCompressors  );
							 goto  errLabel;
							 break;
			  }
			  //
			  switch  (  uiModuleType_suggested  )  {
					  case  CONST_moduleType_mediaSdk_dec:
					  case  CONST_moduleType_dec_nv:
					  case  CONST_moduleType_dec_amf:	//  
						    switch  (  uiModuleType  )  {
									case  CONST_moduleType_ipp:
									case  CONST_moduleType_mediaSdk_dec:
										  uiModuleType  =  uiModuleType_suggested;
										  break;
									default:
											break;
							}
						    break;
					  default:
							 break;
			  }
			  //
			  adjustModuleType_decV(pQyMc,&uiModuleType);
			  //
#ifdef  __DEBUG__
		showInfo_open0(  0,  0,  _T(  "initTaskAvFrom_video ...8889"  )  );
#endif
		if (uiModuleType == CONST_moduleType_decD3d_nv) {
			showInfo_open(0, 0, 0, _T("initTaskAvFrom_video l1013: use decD3d_nv"));
		}

			  //
			  M_getCompressModule(  pCusModules,  uiModuleType,  pModule  );	//  2012/09/09
			  if  (  !pModule  ||  !pModule->compress.pf_qdcInitDecompressVideo  )  {
				  _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s pModule or initDecV is null. moduleType %d"  ),  tHintBuf,  uiModuleType  );
				  //
				  TCHAR  tBuf[128];
				  char  fourcc[4  +  1];
				  iFourcc2Str(  pTransformVideo->tv.vh_stream.dwFourcc,  fourcc,  mycountof(  fourcc  )  );
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "decV: %S not supported. %s"  ),  fourcc,  tHintBuf  );
				  pProcInfo->showNotification(  0,  0,  0,  0,  0,  0,  tBuf  );
				  //
				  goto  errLabel;
			  }
			  pTransformVideo->uiModuleType_toDec  =  uiModuleType;	//  2012/09/09
			  pTransformVideo->bUseDecTool  =  bUseDecTool_suggested;	//  2015/01/19
			  
			  //  2017/10/11
			  int  iFourcc  =  pTransformVideo->tv.vh_stream.dwFourcc;
			  if  (  !iFourcc  )  iFourcc  =  fourccStr2i(  pTransformVideo->tv.compressor.common.fourccStr  );

			  //  2016/04/28
			  unsigned  short  real_usPktResType  =  0;	//  pProcInfo->get_pktResType_suggested(  CONST_pktUsage_dec,  uiModuleType  );
			  if  (  pProcInfo->get_deced_pktResType(  uiModuleType,  iFourcc,  &real_usPktResType  )  )  goto  errLabel;
			  //
			  //  2017/10/13
			  char  fourccStr[4  +  1]  =  "";
			  iFourcc2Str(  iFourcc,  fourccStr,  mycountof(  fourccStr  )  );
			  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "initTaskAvFrom_video: fourcc %S, real_usPktResType %d. dec %dX%d"  ),  fourccStr,  (  int  )real_usPktResType,  pTransformVideo->tv.vh_decompress.bih.biWidth,  pTransformVideo->tv.vh_decompress.bih.biHeight  );
			  showInfo_open0(  0,  0,  tBuf  );
			  //
#if  0
			  int  tmp_pktResType  =  pProcInfo->get_pktResType_suggested(  CONST_pktUsage_dec,  uiModuleType  );
			  if  (  tmp_pktResType  ==  CONST_pktResType_sharedTex  )  {
				  //
				  int  propId  =  CONST_qdcPropId_bSupport_sharedTex_dec;			
				  //
				  BOOL  bVal  =  FALSE;
				  if  (  !getVal_bSupported_pktResType_sharedTex(  pProcInfo,  uiModuleType,  propId,  &bVal  )  
					  &&  bVal  )			
				  {
					  //  2015/11/01
					  real_usPktResType  =  CONST_pktResType_sharedTex;			
				  }		 
			  }
#endif
			  pTransformVideo->usPktResType  =  real_usPktResType;

			  //  2014/03/25
			  VIDEO_COMPRESSOR_CFG  compressor;
			  //
			  memcpy(  &compressor,  &pActiveMem_from->avStream.obj.tranInfo.video.compressor,  sizeof(  compressor  )  );
			  //
			  compressor.common.pCurPkt  =  pTransformVideo->pCurPkt;
			  compressor.common.size_pCurPkt  =  sizeof(  pTransformVideo->pCurPkt[0]  );
			  compressor.common.pInDataCacheQ  =  pTransformVideo->pInDataCacheQ;
			  compressor.common.pVideoQ2  =  &pTransformVideo->q2;
			  compressor.common.pTmpDataQ  =  pTransformVideo->pTmpDataQ;
			  //
			  compressor.common.pParent_transform  =  pTransform;
			  compressor.common.uiTransformType_pParent  =  CONST_uiTransformType_dec;
			  //
			  compressor.common.pf_bTransformVideoQuit  =  bTransformVideoQuit;
			  compressor.common.pf_transformGetSpsPps  =  transformGetSpsPps;
			  compressor.common.pf_transformGetBih  =  (  PF_commonHandler  )transformGetBih;
			  compressor.common.pf_getNextVPkt  =  (  PF_commonHandler  )getNextVPkt;
			  //compressor.common.pf_parseVPkt_i  =  dec_parseEncVPkt_i;
			  compressor.common.pf_parseDecVPkt_o  =  parseDecVPkt_o;

			  compressor.common.pf_detachPkt  =  detachVPkt;
			  compressor.common.pf_clean_myDRAW_VIDEO_DATA  =  (  PF_clean_myDRAW_VIDEO_DATA  )clean_myDRAW_VIDEO_DATA;

			  //  2014/09/07
			  compressor.common.iDecParam_index_pMems_from  =  -1;//index_pMems_from;
			  //  2014/07/09
			  compressor.common.dec.pf_smplBitstreamReader_ReadNextFrame_func  =  smplBitstreamReader_ReadNextFrame_func_v;
			  //  2015/01/17
			  compressor.common.dec.pf_smplYUVWriter_WriteNextFrame_pre  =  smplYUVWriter_WriteNextFrame_pre;	//  2015/01/17
			  compressor.common.dec.pf_smplYUVWriter_WriteNextFrame0  =  smplYUVWriter_WriteNextFrame0;			//  2014/07/23
			  compressor.common.dec.pf_smplYUVWriter_WriteNextFrame1  =  smplYUVWriter_WriteNextFrame1;			//  2014/07/23
			  //
			  compressor.common.dec.pf_smplYUVWriter_WriteNextFrame_all  =  smplYUVWriter_WriteNextFrame_all;		//  2014/07/23
			  //
			  compressor.common.dec.pf_updateDecVideoParam  =  updateDecVideoParam;
			  //
			  //compressor.common.dec.pf_mychkFromPlayerIndex_v  =  (  PF_commonHandler  )chkFromPlayerIndex_v;
			  //
			  compressor.common.dec.pf_postVPktToRender  =  (  PF_commonHandler  )postVPktToRender;
			  //  2014/03/29
			  compressor.common.ucHardwareAccl  =  pQmcCfg->policy.ucHardwareAccl;
			  //  2015/10/04
			  compressor.common.usPktResType_suggested  =  real_usPktResType;	//  2016/04/28	//  pProcInfo->get_pktResType_suggested(  CONST_pktUsage_dec  );
			  //  2014/07/17
			  pTransformVideo->u.qoi.myQoi.common.var.pDebugStep  =  &pTransform->video.debugStep;
			  
			  //
			  if (uiModuleType == CONST_moduleType_decD3d_nv) {
				  compressor.common.dec.pf_smplYUVWriter_WriteNextFrame_pre = smplYUVWriter_WriteNextFrame_pre_1;	//  2015/01/17
				  compressor.common.dec.pf_smplYUVWriter_WriteNextFrame0 = smplYUVWriter_WriteNextFrame0_1;			//  2014/07/23
				  compressor.common.dec.pf_smplYUVWriter_WriteNextFrame1 = smplYUVWriter_WriteNextFrame1_1;			//  2014/07/23
				  //
				  compressor.common.dec.pf_smplYUVWriter_WriteNextFrame_all = smplYUVWriter_WriteNextFrame_all_1;		//  2014/07/23
			  }

			  //  2024/10/20
			  compressor.adapterLuid_LowPart = pProcInfo->av.gpu.adapterLuid_LowPart;
			  compressor.adapterLuid_HighPart = pProcInfo->av.gpu.adapterLuid_HighPart;


			  //  2015/01/19
			  if  (  !pTransformVideo->bUseDecTool  )  {

				  //  2016/04/26
				  pProcInfo->set_qoi_funcs(  &pTransformVideo->u.qoi.myQoi  );

				  //
				   //
				  if (pModule->compress.pf_qdcSetProp) {
				  }

				  //
				  if  (  pModule->compress.pf_qdcInitDecompressVideo(  &compressor,  &pTransformVideo->tv.vh_compress,  &pTransformVideo->tv.vh_decompress,  &pTransformVideo->u.qoi.myQoi.common  )  )  
				  {
					  _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s qdcInitDecVideo failed."  ),  tHintBuf  );
					  traceLogA(  (char*)  "initTaskAvFrom_video: initQdcDecVideo failed."  );
					  goto  errLabel;
				  }

				  //
				  if (pModule->compress.pf_qdcSetProp) {
					  TCHAR  dbgName[128] = _T("dec ");
					  _sntprintf(dbgName, mycountof(dbgName), _T("dec[%d] %I64u "), index_activeMems_from, pActiveMem_from->avStream.idInfo.ui64Id);
					  COMMON_PARAM  commonParam;
					  MACRO_makeCommonParam3(&pTransformVideo->u.qoi.myQoi.common, dbgName, 0, commonParam);
					  pModule->compress.pf_qdcSetProp(CONST_qdcPropId_dbgName, &commonParam, mynull);
					  //
					  bool* g_pbMon = &pQmcCfg->debugStatusInfo.bMon_decV;
					  pModule->compress.pf_qdcSetProp(CONST_qdcPropId_pbMon, g_pbMon, mynull);
				  }



				  //
#ifdef  __DEBUG__
				  if (pQmcCfg->debugStatusInfo.ucb__Dump_h265_dec__) {
					  static  BOOL  bReset = FALSE;
					  for (int j = 0; j < pTransform->video.tv.vh_stream.usCnt; j++) {
						  char* video = pTransform->video.tv.vh_stream.mems[j].spsPps;
						  int  len = pTransform->video.tv.vh_stream.mems[j].usLen;
						  dumpVideo_init(mynull,& bReset, NULL, _T(CONST_fn_dump_h265_dec), video, len,mynull);
					  }
				  }
#endif

				  }
			  else  {  //  2015/01/28
				    QDC_OBJ_INFO  *  pQdcObjInfo  =  &pTransformVideo->u.qoi.myQoi.common;
					memcpy(  &pQdcObjInfo->cfg.v,  &compressor.common,  sizeof(  pQdcObjInfo->cfg.v  )  );
					pQdcObjInfo->var.ucbTransformFuncsOk  =  TRUE;
			  }
		}

		//  2014/08/04
		if  (  pTask->saveVideo.ucbSaveVideo_req  )  {
			pTransformVideo->saveVideo.uiSize_pSaveVideoPkt  =  sizeof(  SAVE_video_pkt  );
			if  (  pTransformVideo->saveVideo.pSaveVideoPkt  )  {
				qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initTaskAvFrom_video failed: pSaveVideoPkt is not null."  )  );
				goto  errLabel;
			}
			pTransformVideo->saveVideo.pSaveVideoPkt  =  mymalloc(  pTransformVideo->saveVideo.uiSize_pSaveVideoPkt  );
			if  (  !pTransformVideo->saveVideo.pSaveVideoPkt  )  goto  errLabel;
			memset(  pTransformVideo->saveVideo.pSaveVideoPkt,  0,  pTransformVideo->saveVideo.uiSize_pSaveVideoPkt  );
		}

		//
		if  (  pTransformVideo->tv.compressor.common.ucCompressors  !=  CONST_videoCompressors_stream  )  {
			switch  (  pTransformVideo->tv.vh_decompress.bih.biCompression  )  {
					case  BI_RGB:
						  if  (  pTransformVideo->tv.vh_decompress.bih.biPlanes  !=  1  )  {
							  _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  " vh_dec.biPlanes %d"  ),  (  int  )pTransformVideo->tv.vh_decompress.bih.biPlanes  );
							  //goto  errLabel;			
						  }
						  if  (  pTransformVideo->tv.vh_decompress.bih.biBitCount  !=  24  )  {
							  _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%s bitCount %d"  ),  tHintBuf,  (  int  )pTransformVideo->tv.vh_decompress.bih.biBitCount  );				
						  }
						  break;
					case  CONST_fourcc_YV12:
					case  CONST_fourcc_I420:
					case  CONST_fourcc_NV12:
						  break;

					default:							
							_sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  " vh_dec not RGB"  ),  pTransformVideo->tv.vh_decompress.bih.biCompression  );
							traceLogA(  (char*)  "not rgb."  );  
							goto  errLabel;							
							break;
			}
		}
		#ifdef  __DEBUG__
				//  pTransformVideo->biSizeImage_decompress  =  (  pTransformVideo->vh_decompress.bih.biWidth  *  pTransformVideo->vh_decompress.bih.biBitCount  +  31  )  /  32  *  4  *  pTransformVideo->vh_decompress.bih.biHeight;
		#endif
		//  pTransformVideo->iDecompressBufSize  =  max(  pTransformVideo->vh_decompress.bih.biSizeImage,  biSizeImage  )  +  iFormatSize  +  4096;	//  ²»ÖªµÀ¾«È·µÄÓ¦¸ÃÊÇ¶àÉÙ£¬ËùÒÔºýÅªÒ»¸öÔÚÕâÀï£®£²£°£°£¸£¯£°£³£¯£±£¹
		//
		//  if  (  !(  pTransformVideo->pDecompressBuf  =  (  char  *  )mymalloc(  pTransformVideo->iDecompressBufSize  )  )  )  goto  errLabel;

		//
		pTransformVideo->index_activeMems_from  =  index_activeMems_from;//index_pMems_from;

		pTransformVideo->ucbInited  =  TRUE;
	}

	iErr  =  0;

errLabel:


	//  2012/03/19
	MACRO_setMyStep(  pTransformVideo->debugStep,  41  );


	//
	if  (  iErr  )  {
		exitTaskAvFrom_video(  pProcInfo,  pTransform  );
	}


	//  2012/03/19
	MACRO_setMyStep(  pTransformVideo->debugStep,  42  );

	//  if  (  iErr  ||  tHintBuf[0]  )  
	{
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initTaskAvFrom_video actives[%d] %I64u leaves %s %s"  ),  index_activeMems_from,  pActiveMem_from->avStream.idInfo.ui64Id,  (  iErr  ?  _T(  "failed"  )  :  _T(  ""  )  ),  tHintBuf  );
	}

	traceLogA(  (char*)  "initTaskAvFrom_video: %I64u leaves with %s",  pActiveMem_from->avStream.idInfo.ui64Id,  iErr  ?  "error"  :  "ok"  );

	return  iErr;
}


//
void  exitTaskAvFrom_video(  void  *  pMC_VAR_common,  QY_TRANSFORM  *  pTransform  )
{
	MC_VAR_common  *  pProcInfo  =  (  MC_VAR_common  *  )pMC_VAR_common;

	int		i;

	//
	QMC_cfg  *  pQmcCfg  =  (  QMC_cfg  *  )pProcInfo->get_qmc_cfg(  );
	if  (  !pQmcCfg  )  {
		MACRO_qyAssert(  0,  _T(  "exitTaskAvFrom_video: pQmcCfg is null"  )  );
		return;
	}
	CUS_MODULES  *  pCusModules  =  (  CUS_MODULES  *  )pProcInfo->getCusModules(  );
	if  (  !pCusModules  )  {
		MACRO_qyAssert(  0,  _T(  "exitTaskAvFrom_video: pCusModules is null"  )  );
		return;
	}



	//
	TRANSFORM_VIDEO_procInfo  *  pTransformVideo  =  &pTransform->video;


	//
#ifdef  __DEBUG__
	traceLogA(  (char*)  "exitTaskAvFrom_video: %I64u enters",  pTransform->video.idInfo.ui64Id  );
#endif


	//  2014/07/17
	MACRO_setMyStep(  pTransformVideo->debugStep,  102  );

	//
	QY_PLAYER* pPlayer = getPlayerByIndex((CCtxQmc*)pProcInfo, pTransform->iIndex_player);
	if (pPlayer) {
		//
		pPlayer->bNeedEnd1 = true;
	}


	//  if  (  pFrom->video.ucbInited  )  
	{
		if  (  !pTransformVideo->tv.compressor.common.ucCompressors  )  ;
		else  if  (  pTransformVideo->tv.compressor.common.ucCompressors  ==  CONST_videoCompressors_vcm  )  {
				  if  (  pTransformVideo->u.vcm.hicDecompress  )  {
					  #ifdef  __DEBUG__
							  traceLogA(  (char*)  "ÕâÀïÒª¹Ø±Õ´ò¿ªµÄ½âÑ¹ËõÒýÇæ¡£"  );
					  #endif
					  ICClose(  pTransformVideo->u.vcm.hicDecompress  );  pTransformVideo->u.vcm.hicDecompress  =  NULL;
				  }
				  }
		else  if  (  pTransformVideo->tv.compressor.common.ucCompressors  ==  CONST_videoCompressors_dmo  )  {
				  #if  0
					   for  (  i  =  0;  i  <  pTransformVideo->u.dmo.usCnt;  i  ++  )  {
					   		exitDecompressVideo_dmo(  &pTransformVideo->u.dmo.dmoInfos[i]  );
					   }
				  #endif

				  if  (  pQmcCfg->ucb__SUPPORT_dmoToDec__  )  {
					  exitDecompressVideo_dmo(  &pTransformVideo->u.dmo  );
					  }
				  else  {
					    //exitDecompress_filterGraph(  &pTransformVideo->u.dmo,  &pTransformVideo->debugStep  );
				  }
					   
				  }

		else  {
			  CUS_MODULE_U	*	pModule  =  NULL;

			  M_getCompressModule(  pCusModules,  pTransformVideo->uiModuleType_toDec,  pModule  );	//  2012/09/09

			  //  2015/01/19
			  if  (  !pTransformVideo->bUseDecTool  )  {

				  //
				  if  (  pModule  &&  pModule->compress.pf_qdcExitDecompressVideo  )  {
					  pModule->compress.pf_qdcExitDecompressVideo(  &pTransformVideo->u.qoi.myQoi.common  );
				  }

			  }
		}
		//
		//  2014/08/04
		MACRO_safeFree(  pTransformVideo->saveVideo.pSaveVideoPkt  );

		//  2012/09/09
		pTransformVideo->uiModuleType_toDec  =  0;
		pTransformVideo->bUseDecTool  =  FALSE;	//  2015/01/19

		//  2010/05/04
		memset(  &pTransformVideo->u,  0,  sizeof(  pTransformVideo->u  )  );

		//  if  (  pTransformVideo->pDecompressBuf  )  M_free(  pTransformVideo->pDecompressBuf  );  

		//  2012/03/19
		memset(  &pTransformVideo->status,  0,  sizeof(  pTransformVideo->status  )  );
		
		//
		pTransformVideo->ucbInited  =  FALSE;
	}

//  errLabel:


	//  2014/07/17
	MACRO_setMyStep(  pTransformVideo->debugStep,  108  );


	int  index_activeMems_from  =  0;	//  pTransform->index_activeMems_from
	qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (char*)  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "exitTaskAvFrom_video %d"  ),  index_activeMems_from  );

	//  traceLogA(  (char*)  "exitTaskAvFrom_video: %I64u leaves",  pFrom->idInfo.ui64Id  );
#ifdef  __DEBUG__
	traceLogA((char*)"exitTaskAvFrom_video: %I64u leaves", pTransform->video.idInfo.ui64Id);
#endif

	return;
}



