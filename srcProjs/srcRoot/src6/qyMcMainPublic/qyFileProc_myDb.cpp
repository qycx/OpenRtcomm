

#include	"stdafx.h"
#include	"shlobj.h"
#ifndef  __WINCE__
		 #include	"myresource.h"
#endif
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"


#ifndef  __NOTSUPPORT_MULTIDOC__
	#include	"qyRestrictEdit.h"
	#include	"qyFile.h"
#endif
#ifdef  __isCli__
	#include	"qyFile.h"
#endif
#include	"qyCusResTemp.h"
#include	"tmpCeLib.h"
//

#ifndef  __NOTSUPPORT_MULTIDOC__
	#include	"qyMc.h"
	//  #include	"qyMcDoc.h"
	#include	"qyMcView.h"
	#include	"dlgMcHint.h"
	#include	"dlgQnmCfgOptions.h"
	#include	"DlgQnmCfgAdvancedOptions.h"
#endif 
#include	"qyDynLib.h"


#include	"qmcVWall.h"
#include	"qmcCmdProc.h"

#include	"qySqlFunc.h"
