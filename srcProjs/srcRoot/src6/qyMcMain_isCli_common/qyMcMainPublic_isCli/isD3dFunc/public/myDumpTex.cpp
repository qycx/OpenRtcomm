

#include "stdafx.h"
#include	<stdlib.h>
#include	<tchar.h>

#include	"DXUT.h"
#include	"DXUTgui.h"
#include	"SDKmisc.h"

//  2014/10/23
#include	"D3dx11effect.h"


#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"qySyncCommProc.h"
#include	"qmcVideoCapture_isCli.h"



//
#include	"isCliHelpPublic.h"

//

#include	"isCmdConst.h"
#include	"qyCusResTemp.h"
#include	"imgProcessPublic.h"
#include	"dlgTalkProc.h"
#include	"funcsForisCliHelp.h"
#include	"subtitlesCfg.h"

#include	"qmcDirectXPublic.h"

#include	"qisChromaKeyEffect.h"


#include	"imgProcessPublic.h"
#include	"qyCusResTemp.h"
#include	"dlgTalkPublic.h"
#include	"isCliHelpPublic.h"
#include	"funcsforisCliHelp.h"

#include	"qmcCmdProc.h"

#include	"meshLoaderpublic.h"

#include	"qisD3d_open.h"
#include	"qisTexture.h"

//
#include	"isD3dFunc_public.h"


//
//
extern  "C"  __declspec(  dllexport  )  HRESULT WINAPI my_DXUTSaveTextureToFile( ID3D11DeviceContext* pContext, ID3D11Resource* pSource, bool usedds, const wchar_t* szFileName )
 {
	 return  DXUTSaveTextureToFile( pContext, pSource, usedds, szFileName ); 
 }
