
#include	"stdafx.h"
#include	<tchar.h>
#include	<stdlib.h>
#include	<Dshow.h>

#include	<assert.h>

//
#include	"tmpGuiOpenFunc.h"
#include	"tmpDllInit_open.h"






extern  "C"  __declspec(  dllexport  ) int  qyDllInit(  void  *  p0,  void  *  p1,  PARAM_qyDllInit  *  pParam  )
{
	if  (  !pParam  )  return  -1;

	//
	g_pGuiOpen  =  pParam->pGuiOpen;

	return  0;
}

//
extern  "C"  __declspec(  dllexport  ) int  qyDllExit(  void  *  p0,  void  *  p1,  PARAM_qyDllExit  *  pParam  )
{
	return  0;
}