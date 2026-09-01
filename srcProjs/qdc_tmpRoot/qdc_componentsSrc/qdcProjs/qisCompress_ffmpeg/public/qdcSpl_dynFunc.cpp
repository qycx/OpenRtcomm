
#include	"stdafx.h"

#include	<stdlib.h>
#include	<tchar.h>
#include	<stddef.h>
#include	<mmsystem.h>

#include	"qdcOpenCommon.h"

#include "mfxdefs.h"
#include "mfxsplmux.h"
  //#include	"mfxsplmux++.h"
#include	"my_mfxsplmux++.h"

typedef  struct  __funcs_spl_t	{
				 HINSTANCE							hDll;
				 //
				 PF_MFXSplitter_Init				pf_MFXSplitter_Init;
				 PF_MFXSplitter_Close				pf_MFXSplitter_Close;
				 PF_MFXSplitter_GetBitstream		pf_MFXSplitter_GetBitstream;
				 PF_MFXSplitter_ReleaseBitstream	pf_MFXSplitter_ReleaseBitstream;
				 PF_MFXSplitter_GetInfo				pf_MFXSplitter_GetInfo;
				 PF_MFXSplitter_Seek				pf_MFXSplitter_Seek;

				 //
				 BOOL								bOk;

}		 FUNCS_spl;

FUNCS_spl	g_funcs_spl;
BOOL		bZeroed_g_funcs_spl	=	FALSE;

 int  init_zero_spl(  )
{
	if  (  !bZeroed_g_funcs_spl  )  {
		memset(  &g_funcs_spl,  0,  sizeof(  g_funcs_spl  )  );
		bZeroed_g_funcs_spl  =  TRUE;
	}

	return  0;
}

//
#define  CONST_fn_spl		"sample_spl_mux.dll"
int  load_spl(  LPCTSTR  path  )
{
	int		iErr	=	-1;

	init_zero_spl(  );
	
	//
	FUNCS_spl  *  pFuncs  =  &g_funcs_spl;

	//
	if  (  pFuncs->bOk  )  return  0;

	//
	TCHAR				tmpFileName[MAX_PATH  +  1];
	 TCHAR				pathBuf[MAX_PATH  +  1];
	 TCHAR			*	filePart;
	 HINSTANCE			hDll							=		NULL;
	 

	 GetModuleFileName(  NULL,  tmpFileName,  sizeof(  tmpFileName  )  /  sizeof(  tmpFileName[0]  )  );
	 if  (  !GetFullPathName(  tmpFileName,  sizeof(  pathBuf  )  /  sizeof(  pathBuf[0]  ),  pathBuf,  &filePart  )  )  goto  errLabel;
	 filePart[0]  =  0;

	 _sntprintf(  tmpFileName,  mycountof(  tmpFileName  ),  _T(  "%s%s"  ),  pathBuf,  _T(  CONST_fn_spl  )  );
	 path  =  tmpFileName;	 

	//
	pFuncs->hDll  =  LoadLibrary(  path  );
	if  (  !pFuncs->hDll  )  goto  errLabel;

	//
	pFuncs->pf_MFXSplitter_Init  =  (  PF_MFXSplitter_Init  )GetProcAddress(  pFuncs->hDll,  "MFXSplitter_Init"  );
	pFuncs->pf_MFXSplitter_Close  =  (  PF_MFXSplitter_Close  )GetProcAddress(  pFuncs->hDll,  "MFXSplitter_Close"  );
	pFuncs->pf_MFXSplitter_GetBitstream  =  (  PF_MFXSplitter_GetBitstream  )GetProcAddress(  pFuncs->hDll,  "MFXSplitter_GetBitstream"  );
	pFuncs->pf_MFXSplitter_ReleaseBitstream  =  (  PF_MFXSplitter_ReleaseBitstream  )GetProcAddress(  pFuncs->hDll,  "MFXSplitter_ReleaseBitstream"  );
	pFuncs->pf_MFXSplitter_GetInfo  =  (  PF_MFXSplitter_GetInfo  )GetProcAddress(  pFuncs->hDll,  "MFXSplitter_GetInfo"  );
	pFuncs->pf_MFXSplitter_Seek  =  (  PF_MFXSplitter_Seek  )GetProcAddress(  pFuncs->hDll,  "MFXSplitter_Seek"  );

	//
	pFuncs->bOk  =  TRUE;

	iErr  =  0;
errLabel:
	return  iErr;

}

int  unload_spl(  )
{
	FUNCS_spl  *  pFuncs  =  &g_funcs_spl;

	if  (  !bZeroed_g_funcs_spl  )  return  0;

	if  (  pFuncs->hDll  )  {
		FreeLibrary(  pFuncs->hDll  );  
		memset(  pFuncs,  0,  sizeof(  pFuncs[0]  )  );
	}
}



mfxStatus dyn_MFXSplitter_Init(mfxDataIO *data_io, mfxSplitter *spl)
{
	FUNCS_spl  *  pFuncs  =  &g_funcs_spl;

	if  (  !pFuncs->bOk  )  return  MFX_ERR_UNKNOWN;

	mfxStatus  sts  =  pFuncs->pf_MFXSplitter_Init(  data_io,  spl  );
	return  sts;
}

mfxStatus dyn_MFXSplitter_Close(mfxSplitter spl)
{
	FUNCS_spl  *  pFuncs  =  &g_funcs_spl;

	if  (  !pFuncs->bOk  )  return  MFX_ERR_UNKNOWN;


	mfxStatus  sts  =  pFuncs->pf_MFXSplitter_Close(  spl  );
	return  sts;
}

mfxStatus dyn_MFXSplitter_GetBitstream(mfxSplitter spl, mfxU32 *track_num, mfxBitstream *bs)
{
	FUNCS_spl  *  pFuncs  =  &g_funcs_spl;

	if  (  !pFuncs->bOk  )  return  MFX_ERR_UNKNOWN;
	
	mfxStatus  sts  =  pFuncs->pf_MFXSplitter_GetBitstream(  spl,  track_num,  bs  );
	return  sts;
}

mfxStatus dyn_MFXSplitter_ReleaseBitstream(mfxSplitter spl, mfxBitstream *bs)
{
	FUNCS_spl  *  pFuncs  =  &g_funcs_spl;

	if  (  !pFuncs->bOk  )  return  MFX_ERR_UNKNOWN;
	
	mfxStatus  sts  =  pFuncs->pf_MFXSplitter_ReleaseBitstream(  spl,  bs  );
	return  sts;
}

mfxStatus dyn_MFXSplitter_GetInfo(mfxSplitter spl, mfxStreamParams *par)
{
	FUNCS_spl  *  pFuncs  =  &g_funcs_spl;

	if  (  !pFuncs->bOk  )  return  MFX_ERR_UNKNOWN;
	
	mfxStatus  sts  =  pFuncs->pf_MFXSplitter_GetInfo(  spl,  par  );
	return  sts;
}

mfxStatus dyn_MFXSplitter_Seek(mfxSplitter spl, mfxU64 timestamp)
{
	FUNCS_spl  *  pFuncs  =  &g_funcs_spl;

	if  (  !pFuncs->bOk  )  return  MFX_ERR_UNKNOWN;
	
	mfxStatus  sts  =  pFuncs->pf_MFXSplitter_Seek(  spl,  timestamp  );
	return  sts;
}
