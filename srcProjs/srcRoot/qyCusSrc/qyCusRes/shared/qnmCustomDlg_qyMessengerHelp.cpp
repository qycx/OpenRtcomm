
#include	"stdafx.h"
#include	<tchar.h>
//  #include	"qyCommon.h"
#include	"myresource_main_qyMessengerHelp.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"
#include	"qyCusResTemp.h"

#include	"qnmCustomStr_common.h"
#include	"qnmCustomStr_netMc.h"


 QY_DMITEM  CONST_dlg_fileTransfer_qyMessengerHelp[]  =  
 {
	 {  IDC_RADIO_recv,  },
	 {  IDC_RADIO_sent,  },
	 {  IDC_RADIO_send,  },
	 {	IDCANCEL,		 },

	 {	-1,				},
 };

 QY_DMITEM  CONST_dlg_opAvDev_qyMessengerHelp[]  =  
 {
	 {  IDC_STATIC_aDev,  },
	 {  IDC_STATIC_vDev,  },
	 {  IDC_BUTTON_cfgCaptureFilter_v,  },
	 {  IDC_BUTTON_cfgCapturePin_v,  },
	 {	IDC_BUTTON_cfgCrossBar_v,  },
	 {  IDC_STATIC_name,  },
	 {  IDC_CHECK_ucbUnresizable, 	 },
	 {  IDC_CHECK_autoOpenOnStartup,  },
	 {	IDOK,			},
	 {	IDCANCEL,		},

	 {	-1,				},
 };


 
 QY_DMITEM  CONST_dlg_opScreen_qyMessengerHelp[]  =  
 {
	 {  IDC_STATIC_name,  },
	 {  IDC_CHECK_autoOpenOnStartup,  },
	 {	IDOK,			},
	 {	IDCANCEL,		},
	 {	-1,				},
 };



 QY_DMITEM  CONST_dlgTable_qyMessengerHelp[]  =
{

	{	IDD_opAvDev,					(  TCHAR  *  )CONST_dlg_opAvDev_qyMessengerHelp,		},
	{	IDD_opScreen,					(  TCHAR  *  )CONST_dlg_opScreen_qyMessengerHelp,		},
	{	IDD_fileTransfer,				(  TCHAR  *  )CONST_dlg_fileTransfer_qyMessengerHelp,		},
//
	{	-1,		},
};

