

#include	"stdafx.h"



#include <iostream>

#include <Windows.h>  
#include <iostream>  
#include <DXGI.h>  
#include <vector>  
#include <sstream>
#include	<WinSock2.h>
#include	<mmeapi.h>
#include	<tchar.h>
#include	<stdlib.h>


//
#include	"qyDefs_open.h"
#include	"qmCommon.h"
//#include <ctxQmc_sm.h>
#include	"myCmdParams_open.h"


#include	"myTChar.h"
#include	"hgCommProc.h"





using namespace std;
std::string WStringToString(const std::wstring& wstr)
{
	std::string str(wstr.length(), ' ');
	std::copy(wstr.begin(), wstr.end(), str.begin());
	return str;
}





//
int getNCardsInfo(NCardsInfo& cards) {
	IDXGIFactory* pFactory;
	IDXGIAdapter* pAdapter;
	int iAdapterNum = 0;

	int ret = -1;

	//
	memset(&cards, 0, sizeof(cards));

	//
	std::stringstream ss;
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory));

	if (FAILED(hr))
		return -2;

	while (pFactory->EnumAdapters(iAdapterNum, &pAdapter) != DXGI_ERROR_NOT_FOUND) {
		DXGI_ADAPTER_DESC adapterDesc;
		pAdapter->GetDesc(&adapterDesc);
		pAdapter->Release();
		wstring aa(adapterDesc.Description);
		std::string bb = WStringToString(aa);

		if (cards.usCnt > mycountof(cards.mems  ))
			break;

		if (bb.find("NVIDIA") != std::string::npos) {
			ss << std::hex << std::uppercase << adapterDesc.VendorId << " " << adapterDesc.DeviceId << " " << adapterDesc.SubSysId;
			strncpy_s(cards.mems[cards.usCnt].id, ss.str().c_str(), sizeof(cards.mems[cards.usCnt].id));
			;
			cards.usCnt++;

			
		}

		++iAdapterNum;
	}

	pFactory->Release();

	ret = 0;

	return ret;
}


