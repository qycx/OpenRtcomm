

#ifndef  __qyTimestamp_h__
#define  __qyTimestamp_h__	//  {

//
#include <myTypes.h>
#include <ctxQmThread.h>


//
typedef  struct  __qyTimestamp_t					{
 				 DWORD								dwModifiedTickCnt;
                 //
                 int                                dbg_iType;
                 //
}	     QY_timestamp;


//
#define         CONST_tsType_null                   0
#define         CONST_tsType_peerImgs               1
#define         CONST_tsType_otherImgs              2
#define         CONST_tsType_meImgs                 3
//
#define         CONST_tsType_layout                 4



//  2016/06/04
#define		timestamp_isSame(  pTs1,  pTs2  )					(	(  pTs1  )->dwModifiedTickCnt  ==  (  pTs2  )->dwModifiedTickCnt  )

//
int  timestamp_renew(CTX_qm_thread* p_ctx_qm_thread, QY_timestamp* pTs,LPCTSTR  hint);
int  timestamp_assign(QY_timestamp src, QY_timestamp* pDst);
int		timestamp_reset(QY_timestamp* pTs, LPCTSTR  hint);


//  2017/10/17




#endif  //  }


