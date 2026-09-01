
#include	"stdafx.h"
#include	<tchar.h>
#include	<stdlib.h>
//#include	<Dshow.h>

#include	<assert.h>

#include	"tmpGuiOpenFunc.h"
//#include	"qisCompressProc.h"

//

//  2014/07/18
QIS_guiOpen		*  g_pGuiOpen					=	NULL;
BOOL				g_bOk_qdcInit				=	FALSE;
int  g_iDebugStepType  =  0;

//
bool* g_pbMon = NULL;


//
int  tmp_showInfo(  TCHAR  *  hint  )
{
	if  (  g_pGuiOpen  )g_pGuiOpen->pf_showInfo(  0,  0,  hint  );
	return  0;
}


//
int  tmp_showInfo(TCHAR  *  tWhere,  TCHAR* hint)
{
	if (g_pGuiOpen)g_pGuiOpen->pf_showInfo(0, tWhere, hint);
	return  0;
}



//
bool  tmp_bMon()
{
	if (g_pbMon) {
		return  *g_pbMon;
	}
	//
	return false;
}



//  2014/06/20
 int  tmp_qPostMsg(  Q_ELEM_T  *  pQElem,  unsigned  int  size,  GENERIC_Q  *  pQ  )
 {
	 if  (  !g_pGuiOpen  )  return  -1;
	 return  (  (  PF_qPostMsg  )g_pGuiOpen->pf_qPostMsg  )(  pQElem,  size,  pQ  );
 }

int  tmp_qGetMsg(  GENERIC_Q  *  pQ,  Q_ELEM_T  *  pQElem,  unsigned  int  *  puiSize  )
{
	if  (  !g_pGuiOpen  )  return  -1;
	return  (  (  PF_qGetMsg  )g_pGuiOpen->pf_qGetMsg  )(  pQ,  pQElem,  puiSize  );
}


int  tmp_mySetDebugStep(  void  *  p0,  void  *  pDebugStep,  int  nStep  )
{
	if  (  !g_pGuiOpen  )  return  -1;
	return  g_pGuiOpen->pf_setDebugStep(  (  void  *  )g_iDebugStepType,  pDebugStep,  (  void  *  )nStep  );
}


void  *  tmp_getDebugStep_sth(  void  *  p0,  int  iType,  void  *  pDebugStep  )
{
	if  (  !g_pGuiOpen  )  return  NULL;
	return  g_pGuiOpen->pf_getDebugStep_sth(  p0,  (  void  *  )iType,  pDebugStep  );
}


//  2015/10/30
 HRESULT  WINAPI tmp_DXUTSaveTextureToFile( _In_ void  *  pID3D11DeviceContext, _In_ void  *  pID3D11Resource_pSource, _In_ bool usedds, _In_z_ const wchar_t* szFileName )
 {
	if  (  !g_pGuiOpen  )  return  -1;
	PF_DXUTSaveTextureToFile  pf  =  (  PF_DXUTSaveTextureToFile  )g_pGuiOpen->pf_DXUTSaveTextureToFile;
	if  (  !pf  )  return  -1;
	return  pf(  pID3D11DeviceContext, pID3D11Resource_pSource, usedds, szFileName );

 }
