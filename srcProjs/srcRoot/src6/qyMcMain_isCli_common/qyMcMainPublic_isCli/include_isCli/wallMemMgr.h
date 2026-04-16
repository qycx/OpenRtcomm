

#ifndef  __wallMemMgr_h__
#define  __wallMemMgr_h__	//  {


#include	"isCliD3dCommon.h"

//
int  initWmGrp(  int  index_d3dWnd,  int  iGrpType,  unsigned  int  usMaxCnt,  BOOL  bUseZOrder,  WM_grp_sync  *  pGrp  );
int  exitWmGrp(  WM_grp_sync  *  pGrp  );
//
int  emptyWmGrp(  WM_grp_sync  *  pGrp  );

//
int  newIndex_wmInfoSync(  WM_grp_sync  *  pGrp  );



#endif  //  }



