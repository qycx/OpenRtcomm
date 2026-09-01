
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include <map>
#include <string>
#include <iostream>

//#include	"ancTaskAvOutput_mcu.h"


//
int  testInMain_isCli(QY_MC* pQyMc)
{
	std::map<__int64,std::string> kkMap;

	kkMap[25] = "kkkk";

	//
	kkMap[25] = "mmm";

	//
	kkMap[27] = "m27";

	//
	kkMap[26] = "m26";

	kkMap[28] = "m28";



	//
	int  ii  =  kkMap.size();

	//
	for (auto it = kkMap.begin(); it != kkMap.end();) {
		//
		if (it->first == 25) {
			it = kkMap.erase(it);
		}
		else {
			++it;
		}
	}


	//
	for (auto&pair : kkMap) {
		__int64 id = pair.first;
		std::string& locStr = pair.second;
		std::cout <<"id=" << id << " loc=" << locStr;

	}

	


	return  0;
}




