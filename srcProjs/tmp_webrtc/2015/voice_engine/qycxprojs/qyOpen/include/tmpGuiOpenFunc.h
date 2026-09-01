

#ifndef  __tmpGuiOpenFunc_h__
#define  __tmpGuiOpenFunc_h__  //  {


#include	"qySyncObj.h"
#include	"qyDefs_open.h"
#include	"genericqueue.h"



int  tmp_showInfo(  TCHAR  *  hint  );

int  tmp_qPostMsg(  Q_ELEM_T  *  pQElem,  unsigned  int  size,  GENERIC_Q  *  pQ  );
int  tmp_qGetMsg(  GENERIC_Q  *  pQ,  Q_ELEM_T  *  pQElem,  unsigned  int  *  puiSize  );

//  2014/07/17
int  tmp_mySetDebugStep(  void  *  p0,  void  *  pDebugStep,  int  nStep  );

//
void  *  tmp_getDebugStep_sth(  void  *  p0,  int  iType,  void  *  pDebugStep  );

//  2015/10/30
HRESULT  WINAPI tmp_DXUTSaveTextureToFile( _In_ void  *  pID3D11DeviceContext, _In_ void  *  pID3D11Resource_pSource, _In_ bool usedds, _In_z_ const wchar_t* szFileName );

 
//
extern  QIS_guiOpen		*  g_pGuiOpen;
extern  BOOL				g_bOk_qdcInit;
extern  int  g_iDebugStepType;


#endif  //  }

