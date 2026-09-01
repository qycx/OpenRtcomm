// AssetMgrModuleDaemon.cpp: implementation of the CAssetMgrModuleDaemon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "qyString.h"
#include "assetMgrModule.h"
#include "AssetMgrModuleDaemon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAssetMgrModuleDaemon::CAssetMgrModuleDaemon()
{
	memset(  &var,  0,  sizeof(  var  )  );

}

CAssetMgrModuleDaemon::~CAssetMgrModuleDaemon()
{

}
