

#include	"stdafx.h"

#include	"qyPrecomp.h"
#include	<windows.h>
#include	<tchar.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyCommProc.h"
#include	"qyLangCommProc.h"
#include	"qyTCharCommProc.h"
//  #include	"qyCusResPublic.h"
#include	"tmpCeLib.h"

#include	"qmStr.h"
#include	"qyPreCustom.h"
#include	"qmCusModuleDefs.h"




LPCTSTR		CONST_str_serviceExits		=	(TCHAR*)_T(  "Service exits."  );	//服务退出完毕

 
//
#if  0
  QY_DMITEM  CONST_qyAppAvLevelTable_en[]  =
{
	{		CONST_qyAppAvLevel_null,	},
	{		CONST_qyAppAvLevel_mini,							(TCHAR*)_T(  "Mini"  ),			(  TCHAR  *  )CONST_resId_qyAppAvLevel_mini,	},
	{		CONST_qyAppAvLevel_sd,							(TCHAR*)_T(  "SD"  ),			(  TCHAR  *  )CONST_resId_qyAppAvLevel_basic,	},
	{		CONST_qyAppAvLevel_hd,						(TCHAR*)_T(  "HD"  ),			(  TCHAR  *  )CONST_resId_qyAppAvLevel_standard,	},
	{		CONST_qyAppAvLevel_fullHd,							(TCHAR*)_T(  "FullHD"  ),		(  TCHAR  *  )CONST_resId_qyAppAvLevel_high,	},
	{		CONST_qyAppAvLevel_top,								(TCHAR*)_T(  "4k"  ),			(  TCHAR  *  )CONST_resId_qyAppAvLevel_top,	},
	{		-1,							},

};
#endif

  //
    QY_DMITEM  CONST_subSystemIdTable_en[]  =
{
	{		CONST_subSystemId_null,	},
	{		CONST_subSystemId_basic,							(TCHAR*)_T(  "basic"  ),		(  TCHAR  *  )CONST_resId_subSystemId_basic,	},
	{		CONST_subSystemId_standard,							(TCHAR*)_T(  "standard"  ),		(  TCHAR  *  )CONST_resId_subSystemId_standard,	},
	{		-1,							},

};




   //  2014/07/30
 QY_DMITEM  CONST_moduleTypeTable_en[]  =  
{
	{		CONST_moduleType_vDev,									(TCHAR*)_T(  "vDev"  ),	},
	{		CONST_moduleType_compress,								(TCHAR*)_T(  "compress"  ),	},
	{		CONST_moduleType_camCap,								(TCHAR*)_T(  "camCap"  ),	},
	//
	{		CONST_moduleType_ipp,									(TCHAR*)_T(  "ipp"  ),		},
	{		CONST_moduleType_mediaSdk_dec,							(TCHAR*)_T(  "dec_msdk"  ),	},
	{		CONST_moduleType_mediaSdk_enc,							(TCHAR*)_T(  "enc_msdk"  ),	},
	{		CONST_moduleType_mediaSdk_enc_conf,						(TCHAR*)_T(  "enc_conf_msdk"  ),	},
	//
	{		CONST_moduleType_dec_nv,								(TCHAR*)_T(  "dec_nv"  ),	},
	{		CONST_moduleType_enc_nv,								(TCHAR*)_T(  "enc_nv"  ),	},
	//
	{		CONST_moduleType_dec_vp8,								(TCHAR*)_T(  "dec_vp8"  ),	},
	{		CONST_moduleType_enc_vp8,								(TCHAR*)_T(  "enc_vp8"  ),	},
	{		-1,		},
 };


