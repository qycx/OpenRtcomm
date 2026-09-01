// isCliSaveAv.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include	<stdlib.h>
#include	"isCliSaveAvCommon.h"


//
extern  "C"  __declspec(dllexport)  int getSize_SAVE_av_procInfo()
{
	mySAVE_av_procInfo* p = nullptr;

	int size = sizeof(mySAVE_av_procInfo);

	//
	return  size;
}





