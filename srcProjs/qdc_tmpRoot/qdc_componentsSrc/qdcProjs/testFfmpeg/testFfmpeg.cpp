// testFfmpeg.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include	<Windows.h>

#include	<stdlib.h>
#include	<tchar.h>
#include	<stddef.h>
#include	<mmsystem.h>

#include	"qdcOpenCommon.h"

#if  0
#include "mfxdefs.h"
#include "mfxsplmux.h"
#include	"mfxsplmux++.h"
#endif

__declspec(  dllexport  )  int  qdcInitSplInfo(  QDC_spl_cfg  *  pCfg,  void  *  p0,  void  *  p1,  QDC_spl_info  *  pSplInfo  );

int _tmain(int argc, _TCHAR* argv[])
{
	//
	qdcInitSplInfo(  0,  0,  0,  0  );

	return 0;
}

