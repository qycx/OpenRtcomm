// open_test.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include	<initguid.h>
#include <d3d9.h>

#include <windows.h>
#include <d3d11_1.h>


//
#include <d3d9.h>

#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>

//
#include	<tchar.h>


//
#include	"qyDefs_open.h"
#include	"qisD3dDefs_open.h"
#include	"qisD3d_open.h"




__declspec(  dllexport  )  int  test_ttttt_myCopyTex(  PARAM_copyTex  *  pParam,  int  CropW,  int  CropH,  ID3D11Texture2D  *  pTex_src,  ID3D11Texture2D  *  pTex_dst,  QIS_trace_common  *  pQtc  )
{
	//
	D3D11_TEXTURE2D_DESC  src_desc,  dst_desc;

	pTex_dst->GetDesc(  &dst_desc  );
	pTex_src->GetDesc(  &src_desc  );

	//return  myCopyTex(  pParam,  CropW,  CropH,  pTex_src,  pTex_dst,  pQtc  );
	pParam->context->CopyResource(  pTex_dst,  pTex_src  );
	//
	//  present1
	pParam->context->Flush(  );
	//
	return  0;
}


