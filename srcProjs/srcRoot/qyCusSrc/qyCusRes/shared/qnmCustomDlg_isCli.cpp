
#include	"stdafx.h"
#include	<tchar.h>
//  #include	"qyCommon.h"
#include	"myresource_main_isCli.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"
#include	"qyCusResTemp.h"

#include	"qnmCustomStr_common.h"
#include	"qnmCustomStr_netMc.h"

 QY_DMITEM  CONST_dlg_mcClientLogon_isCli[]  =
{
	{	IDC_STATIC_logonServer,	},
	{	IDC_STATIC_usrName,		},
	{	IDC_STATIC_passwd,		},
	{	IDC_BUTTON_option,		},
	{	IDOK,					},
	{	IDCANCEL,				},
	{	-1,				},
};


  QY_DMITEM  CONST_dlg_qnmCfgOptions_isCli[]  =
{
	{	IDC_STATIC_cntName,		},
	{	IDC_STATIC_centerAddr,				(  TCHAR  *  )CONST_resId_STATIC_centerIp,		},
	{	IDC_STATIC_cntAddr0,	},
	{	IDC_STATIC_cntAddr1,	},
	{	IDC_STATIC_cntAddr2,	},
	{	IDC_STATIC_cntPort,		},
	{	IDC_CHECK_useDb,		},
	{	IDC_ADD,				},
	{	IDC_MODIFY,				},
	{	IDC_DEL,				},
	{	IDOK,													},
	{	IDCANCEL,											},
	{	-1,			},
};

#ifdef  __WINCE__
 QY_DMITEM  CONST_dlg_qnmCfgOptions_isClient_ce[]  =
{
	{	IDC_BUTTON_contact,		},
	{	IDC_BUTTON_group,		},
	{	IDC_BUTTON_status,		},
	{	IDCANCEL,				 },
	{	-1,						},

};
#endif

 QY_DMITEM  CONST_dlgTable_isCli[]  =
{

	{	IDD_mcClient_logon,					(  TCHAR  *  )CONST_dlg_mcClientLogon_isCli,		},
	{	IDD_qnmCfgOptions_isClient,			(  TCHAR  *  )CONST_dlg_qnmCfgOptions_isCli,		},

//
#ifdef  __WINCE__
	{	IDD_qnmCfgOptions_isClient_ce,		(  TCHAR  *  )CONST_dlg_qnmCfgOptions_isClient_ce,  },
#endif 


	{	-1,		},
};

