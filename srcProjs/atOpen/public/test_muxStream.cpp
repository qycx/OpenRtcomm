
//
#include	"stdafx.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

using namespace std;

//
#include	"myTypes.h"
#include	"qyPrecomp.h"


//
#include	"qmOpenCommon.h"
#include	"muxStream_open.h"
#include <cassert>
#include <qyCusResPublic.h>



//
int  test_getMuxStreamsCfg(  MuxStreamsCfg  *  pCfg)
{
	if (!pCfg)  return  0;

	memset(pCfg, 0, sizeof(pCfg[0]));

#if  1  //def  __DEBUG__
		int  index;

		//
		MuxStreamCfg* pMem;
		MuxStreamOutputCfg* pOutput;
		
		//
		index = 0;
		pMem = &pCfg->mems[index];
		pOutput = &pMem->output;

		//
		pMem->usIndex = index;
		pMem->usType = CONST_muxStreamType_conf;
				
		//
		pOutput->a.wFormatTag = WAVE_FORMAT_MPEGLAYER3;
		//
		pOutput->v.usW = 1920;
		pOutput->v.usH = 1080;
		//
		pOutput->v.iFourcc = CONST_fourcc_HEVC;

		//
		index++;
		pMem = &pCfg->mems[index];
		pOutput = &pMem->output;

		//
		pMem->usIndex = index;
		pMem->usType = CONST_muxStreamType_conf;

		//
		pOutput->a.wFormatTag = WAVE_FORMAT_MPEGLAYER3;
		//
		pOutput->v.usW = 848;
		pOutput->v.usH = 480;
		//
		pOutput->v.iFourcc = CONST_fourcc_HEVC;
		
		//
		index++;
		pMem = &pCfg->mems[index];
		pOutput = &pMem->output;
		//
		pMem->usIndex = index;
		pMem->usType = CONST_muxStreamType_screen;
		//
		pOutput->v.iFourcc = CONST_fourcc_HEVC;
		
		//
		pCfg->usCnt = index + 1;
		if (pCfg->usCnt > mycountof(pCfg->mems)) {
			assert(0);
		}
		
		//
		pCfg->default_usIndex = 0;
		
		
#endif 

	//
	return  0;
}



//
int  testInit_getMuxStreamsCfg(int  avLevel, MuxStreamsCfg* pCfg)
{
	if (!pCfg)  return  0;

	memset(pCfg, 0, sizeof(pCfg[0]));

#if  1  //def  __DEBUG__
	int  index;

	//
	MuxStreamCfg* pMem;
	MuxStreamOutputCfg* pOutput;

	//
	index = 0;
	pMem = &pCfg->mems[index];
	pOutput = &pMem->output;

	//
	pMem->usIndex = index;
	pMem->usType = CONST_muxStreamType_conf;

	//
	pOutput->a.wFormatTag = WAVE_FORMAT_MPEGLAYER3;
	
	//
	pOutput->v.usW = 1280;
	pOutput->v.usH = 720;
	//
	switch (avLevel) {
		case  CONST_policyAvLevel_2160p:
			  pOutput->v.usW =  1920  *  2;
			  pOutput->v.usH = 1080 * 2;
			  break;
		case  CONST_policyAvLevel_1080p:
			  pOutput->v.usW = 1920;
			  pOutput->v.usH = 1080;
			  break;
		case  CONST_policyAvLevel_720p:
			  pOutput->v.usW = 1280;
			  pOutput->v.usH = 720;
			  break;
		case  CONST_policyAvLevel_480p:
			  pOutput->v.usW = 848;
			  pOutput->v.usH = 480;
			  break;
		case  CONST_policyAvLevel_240p:
			  pOutput->v.usW = 424;
			  pOutput->v.usH = 240;
			  break;
		default:
			break;
	}	

	//
	pOutput->v.iFourcc = CONST_fourcc_HEVC;
	
	//
	pCfg->usCnt = index + 1;
	if (pCfg->usCnt > mycountof(pCfg->mems)) {
		assert(0);
	}

	//
	pCfg->default_usIndex = 0;

	//
#endif 

	//
	return  0;
}



