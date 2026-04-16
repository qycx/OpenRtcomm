// qisCamCap.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "qisCamCap.h"


// This is an example of an exported variable
QISCAMCAP_API int nqisCamCap=0;

// This is an example of an exported function.
QISCAMCAP_API int fnqisCamCap(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see qisCamCap.h for the class definition
CqisCamCap::CqisCamCap()
{
	return;
}
