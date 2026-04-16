#include	"stdafx.h"
#include	<math.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"tmpCeLib.h"

//#include	"myresource.h"

//  #include	"DlgVideos.h"
#include	"qmcVideoCapture_isCli.h"
//  #include	"DlgCfgVideoConference.h"
#include	"qyVk.h"


 QY_DMITEM	CONST_qyKeyTable[]  = 
{
	{	VK_CANCEL,  (  TCHAR  *  )CONST_qK_CANCEL,		(  TCHAR  *  )1,	},

    {	VK_BACK,	(  TCHAR  *  )CONST_qK_BACK,			},
    {	VK_TAB,		(  TCHAR  *  )CONST_qK_TAB,				},

    {	VK_CLEAR,	(  TCHAR  *  )CONST_qK_CLEAR,			},
    {	VK_RETURN,	(  TCHAR  *  )CONST_qK_RETURN,		(  TCHAR  *  )1,	},

    {	VK_SHIFT,   (  TCHAR  *  )CONST_qK_SHIFT,			},
    {	VK_CONTROL,	(  TCHAR  *  )CONST_qK_CONTROL,		(  TCHAR  *  )1,	},
    {	VK_MENU,	(  TCHAR  *  )CONST_qK_MENU,			},

    {	VK_PAUSE,	(  TCHAR  *  )CONST_qK_PAUSE,			},
    {	VK_CAPITAL,	(  TCHAR  *  )CONST_qK_CAPITAL,			},

    {	VK_ESCAPE,	(  TCHAR  *  )CONST_qK_ESCAPE,			},

    {	VK_SPACE,	(  TCHAR  *  )CONST_qK_SPACE,			},

    {	VK_PRIOR,	(  TCHAR  *  )CONST_qK_PRIOR,		(  TCHAR  *  )1,	},
    {	VK_NEXT,	(  TCHAR  *  )CONST_qK_NEXT,		(  TCHAR  *  )1,	},
    {	VK_END,		(  TCHAR  *  )CONST_qK_END,			(  TCHAR  *  )1,	},
    {	VK_HOME,	(  TCHAR  *  )CONST_qK_HOME,		(  TCHAR  *  )1,	},
    {	VK_LEFT,	(  TCHAR  *  )CONST_qK_LEFT,		(  TCHAR  *  )1,	},
    {	VK_UP,		(  TCHAR  *  )CONST_qK_UP,			(  TCHAR  *  )1,	},
    {	VK_RIGHT,	(  TCHAR  *  )CONST_qK_RIGHT,		(  TCHAR  *  )1,	},
    {	VK_DOWN,	(  TCHAR  *  )CONST_qK_DOWN,		(  TCHAR  *  )1,	},
    {	VK_SELECT,	(  TCHAR  *  )CONST_qK_SELECT,			},
    {	VK_EXECUTE,	(  TCHAR  *  )CONST_qK_EXECUTE,			},
    {	VK_SNAPSHOT,(  TCHAR  *  )CONST_qK_SNAPSHOT,		},
    {	VK_INSERT,	(  TCHAR  *  )CONST_qK_INSERT,		(  TCHAR  *  )1,	},
    {	VK_DELETE,	(  TCHAR  *  )CONST_qK_DELETE,		(  TCHAR  *  )1,	},
    {	VK_HELP,	(  TCHAR  *  )CONST_qK_HELP,			},

    {	VK_NUMPAD0,	(  TCHAR  *  )CONST_qK_NUMPAD0,			},
    {	VK_NUMPAD1,	(  TCHAR  *  )CONST_qK_NUMPAD1,			},
    {	VK_NUMPAD2,	(  TCHAR  *  )CONST_qK_NUMPAD2,			},
    {	VK_NUMPAD3,	(  TCHAR  *  )CONST_qK_NUMPAD3,			},
    {	VK_NUMPAD4,	(  TCHAR  *  )CONST_qK_NUMPAD4,			},
    {	VK_NUMPAD5,	(  TCHAR  *  )CONST_qK_NUMPAD5,			},
    {	VK_NUMPAD6,	(  TCHAR  *  )CONST_qK_NUMPAD6,			},
    {	VK_NUMPAD7,	(  TCHAR  *  )CONST_qK_NUMPAD7,			},
    {	VK_NUMPAD8,	(  TCHAR  *  )CONST_qK_NUMPAD8,			},
    {	VK_NUMPAD9,	(  TCHAR  *  )CONST_qK_NUMPAD9,			},

    {	VK_MULTIPLY,	(  TCHAR  *  )CONST_qK_MULTIPLY,	},
    {	VK_ADD,			(  TCHAR  *  )CONST_qK_ADD,			},
    {	VK_SEPARATOR,	(  TCHAR  *  )CONST_qK_SEPARATOR,	},   // often comma
    {	VK_SUBTRACT,	(  TCHAR  *  )CONST_qK_SUBTRACT,	},
    {	VK_DECIMAL,		(  TCHAR  *  )CONST_qK_DECIMAL,		},
    {	VK_DIVIDE,		(  TCHAR  *  )CONST_qK_DIVIDE,		(  TCHAR  *  )1,	},

    {	VK_F1,			(  TCHAR  *  )CONST_qK_F1,			},
    {	VK_F2,			(  TCHAR  *  )CONST_qK_F2,			},
    {	VK_F3,			(  TCHAR  *  )CONST_qK_F3,			},
    {	VK_F4,			(  TCHAR  *  )CONST_qK_F4,			},
    {	VK_F5,			(  TCHAR  *  )CONST_qK_F5,			},
    {	VK_F6,			(  TCHAR  *  )CONST_qK_F6,			},
    {	VK_F7,			(  TCHAR  *  )CONST_qK_F7,			},
    {	VK_F8,			(  TCHAR  *  )CONST_qK_F8,			},
    {	VK_F9,			(  TCHAR  *  )CONST_qK_F9,			},
    {	VK_F10,			(  TCHAR  *  )CONST_qK_F10,			},
    {	VK_F11,			(  TCHAR  *  )CONST_qK_F11,			},
    {	VK_F12,			(  TCHAR  *  )CONST_qK_F12,			},
    {	VK_F13,			(  TCHAR  *  )CONST_qK_F13,			},
    {	VK_F14,			(  TCHAR  *  )CONST_qK_F14,			},
    {	VK_F15,			(  TCHAR  *  )CONST_qK_F15,			},
    {	VK_F16,			(  TCHAR  *  )CONST_qK_F16,			},
    {	VK_F17,			(  TCHAR  *  )CONST_qK_F17,			},
    {	VK_F18,			(  TCHAR  *  )CONST_qK_F18,			},
    {	VK_F19,			(  TCHAR  *  )CONST_qK_F19,			},
    {	VK_F20,			(  TCHAR  *  )CONST_qK_F20,			},
    {	VK_F21,			(  TCHAR  *  )CONST_qK_F21,			},
    {	VK_F22,			(  TCHAR  *  )CONST_qK_F22,			},
    {	VK_F23,			(  TCHAR  *  )CONST_qK_F23,			},
    {	VK_F24,			(  TCHAR  *  )CONST_qK_F24,			},

    {	VK_NUMLOCK,		(  TCHAR  *  )CONST_qK_NUMLOCK,		},
    {	VK_SCROLL,		(  TCHAR  *  )CONST_qK_SCROLL,		},
    //  {VK_KEYPAD_ENTER,	},

	{	VK_LSHIFT,		(  TCHAR  *  )CONST_qK_LSHIFT,		},
    {	VK_RSHIFT,		(  TCHAR  *  )CONST_qK_RSHIFT,		},
    {	VK_LCONTROL,	(  TCHAR  *  )CONST_qK_LCONTROL,	},
    {	VK_RCONTROL,	(  TCHAR  *  )CONST_qK_RCONTROL,	(  TCHAR  *  )1,	},
	{	VK_LMENU,		(  TCHAR  *  )CONST_qK_LMENU,		},
    {	VK_RMENU,		(  TCHAR  *  )CONST_qK_RMENU,		(  TCHAR  *  )1,	},

	{	-1,				},
};
