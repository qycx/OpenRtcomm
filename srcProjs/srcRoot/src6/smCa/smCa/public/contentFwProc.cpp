

#include	"stdafx.h"
//
#include	<WinSock2.h>
#include	"Windows.h"
//
#include	"qmOpenCommon.h"
#include	"isFwPublic.h"
#include	"showInfo_open.h"

#include	"qyCommProc.h"

#include	"qmOpenCommon.h"
#include	"qnmCommProc.h"



//
extern  "C"  SMCA_API int  contentFw_filterStream(CTX_stream2Data* pCtx, void* p0, void* p1, unsigned  int  uiStreamId, QY_CFGITEM_ntoh_U* pItem)
{
	return  0;
}