
#ifndef __SKETCHPAD_H__
#define __SKETCHPAD_H__ /* { */

#include	<stdio.h>
#include	<stdlib.h>
#include	<malloc.h>
#include	<string.h>
#include	<math.h>
#include	<stdarg.h>

#include	<windows.h>

//  2015/11/21
#include	<WinSock2.h>
#include	<tchar.h>

//
#include	"qyCommon.h"

#include	"qySyncCommProc.h"
#include	"genericqueue.h"
#include	"qyCommProc.h"

#ifdef  __DEBUG__
		#define __SP_DEBUG__
#endif


#include	"spconf.h"
#include	"spobj.h"
#include	"spfunc.h"
#include	"issameplacespobj.h"
#include	"isspobjselected.h"
#include	"spdisplay.h"
#include	"preopsp.h"
#include	"refreshconstraintedopsp.h"
#include	"opsp.h"
#include	"spconstruct.h"
#include	"sptransform.h"
#include	"sptranslate.h"
#include	"sprotate.h"
#include	"spdilate.h"
#include	"spreflect.h"
#include	"spdiscmd.h"
#include	"spproc.h"
#include	"tempsp.h"

#define CONST_PI	3.1415926535897932


#ifndef SQUARE
	#define SQUARE( x ) ( ( x ) * ( x ) )
#endif

#define A1802PI( x )	( ( x ) / 180. * CONST_PI )
#define API2180( x )	( ( x ) / CONST_PI * 180. )


#define	logErr					debugLog


#ifdef __cplusplus
 extern "C" {
#endif

 /* status of system */
#define STATUS_SELECT				1
#define STATUS_CREATE_A_POINT		2
#define STATUS_CREATE_A_SEGMENT		3
#define STATUS_CREATE_A_CIRCLE		4
#define STATUS_CREATE_A_MEMO		5
#define STATUS_HELP					6
#define STATUS_CONSTRUCT			7
#define STATUS_ANIMATED				8
#define STATUS_CREATE_A_RECTANGLE	9			//  2009/09/24

 /* status of spobj */
#define STATUS_SELECTED				0x01
#define STATUS_OPED					0x02
#define STATUS_INVALID				0x04
#define STATUS_DELETED				0x08
#define STATUS_PROCED				0x10
#define STATUS_INVISIBLE			0x20

#define NO_TRAN							0
#define CREATE_OBJS_TRAN				1
#define DRAW_A_RGN_TRAN					2
#define MOVE_OBJS_TRAN					3
#define CONSTRUCT_TRAN					4
#define DELETE_TRAN						5
#define DISCMD_ANIMATE_TRAN				6


#define ERR_NOTHING			0
#define ERR_WARNING			-1
#define ERR_SERIOUS			-2



//  extern SP_STRUCT gSp;

#ifdef __SP_DEBUG__
 extern char debugStr[1024];
#endif

//  extern int initSp( SP_STRUCT *pSp );
//  extern void exitSp( SP_STRUCT *pSp );
__declspec(  dllexport  )  int initSp( void **ppSp );
__declspec(  dllexport  )  void exitSp( void **ppSp );
__declspec(  dllexport  )  void  resetSp(  void  *  pSp  );
__declspec(  dllexport  )  int  initTran(  SP_STRUCT  *  pSp,  BYTE  tranType  );
__declspec(  dllexport  )  void exitTran( SP_STRUCT *pSp );
extern void resetOpSp( SP_STRUCT *pSp );

__declspec(  dllexport  )  BOOL  bHideSp(  SP_STRUCT  *  pSp,  BOOL  bHide  );
__declspec(  dllexport  )  BOOL  bEditSp(  SP_STRUCT  *  pSp,  BOOL  bEditable  );
//
__declspec(  dllexport  )  int  getSpRect(  SP_RECTANGLE	*	pRectangle,  RECT  *  pRect  );

__declspec(  dllexport  )  int  newCadRectangle(  SP_STRUCT  *  pSp,  int  iX,  int  iY,  int  iW,  int  iH,  SP_RECTANGLE  &  tmpRectangle  );

__declspec(  dllexport  )  Q_NODE  *  findSpQNode(  SP_STRUCT  *  pSp,  unsigned  int  uiTranNo_spObj  );


#ifdef __cplusplus
 }
#endif

#endif /* } __SKETCHPAD_H__ defined */

