
#include	"stdafx.h"

#include	"qyPrecomp.h"
#include	<winsock2.h>
#include	<windows.h>
#include	<assert.h>
#include	<tchar.h>
#include	<iphlpapi.h>

#ifndef  __WINCE__
	#include	<vfw.h>
#else
	#ifdef  __TEST__
		#include	<vfw.h>
	#endif

	#include	<mmreg.h>
	#include	<MSAcm.h>
#endif
#include	<Wincrypt.h>
#include	<time.h>

#include	"qyCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qySyncCommProc.h"

#include	"qmOpenCommon.h"
#include	"qyMsgFunc.h"

#include	"qySyncCommProc.h"
#include	"genericQueue.h"
#include	"qyq2.h"				//  2009/05/13

#include	"qnmCommProc_mis.h"


//  #include	<lmshare.h>

//  #include	"qwmDynFunc.h"

#include	"qnmCommProc_mis.h"



////////////////////////


 // 1需要修改qRemoveMsg等函数，增加initGenericQ的一个节点自动清除的函数pfQElemRemove，和pfQElemExit不同，在qGetMsg时不起作用，在qRemoveMsg和emptyQ时要起作用。
//  2。在从需要释放的包里读取数据时，最好专门作一个函数，将一个局部的CQyMalloc变量引入，在读取到数据时，直接和mallocObj->attach. 可以确保数据的自动释放。


 //  2009/12/08
 void  clean_myPLAY_AUDIO_DATA(  myPLAY_AUDIO_DATA  *  p,  LPCTSTR  hint  )
{
	if  (  !p  )  return;

	//  traceLogA(  "clean_myPLAY_AUDIO_DATA"  );

	//  MACRO_safeFree(  p->pBuf  );
	freeMemory(  &p->memory  );

	return;
}

 //
  //  2015/02/12
 void  cleanEx_myPLAY_AUDIO_DATA(  myPLAY_AUDIO_DATA  *  p,  size_t	size,  LPCTSTR  hint  )
 {
	 int	nPkts  =  size  /  sizeof(  myPLAY_AUDIO_DATA  );

	 TCHAR	tBuf[128]	=	_T(  ""  );
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  hint  ?  hint  :  _T(  ""  ),  _T(  "Ex"  )  );
	 
	 int  i;
	 for  (  i  =  0;  i  <  nPkts;  i  ++  )  {
		  clean_myPLAY_AUDIO_DATA(  &p[i],  tBuf  );
	 }
	 return;
 }



 //
 void  clean_myDRAW_VIDEO_DATA(  myDRAW_VIDEO_DATA  *  p,  LPCTSTR  hint  )
{
	if  (  !p  )  return;
	
	TCHAR	tBuf[128]	=	_T(  ""  );
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  hint  ?  hint  :  _T(  ""  ),  _T(  "clean_myDRAW_VIDEO_DATA: free"  )  );

	//  traceLogA(  "clean_myDRAW_VIDEO-DATA"  );
	M_pkt_showNo(  *p,  tBuf  );

	//  MACRO_safeFree(  p->pBuf  );
	freeMemory(  &p->memory  );

	return;
}

 //  2012/11/10
 void  cleanEx_myDRAW_VIDEO_DATA(  myDRAW_VIDEO_DATA  *  p,  size_t	size,  LPCTSTR  hint  )
 {
	 int	nPkts  =  size  /  sizeof(  myDRAW_VIDEO_DATA  );

	 TCHAR	tBuf[128]	=	_T(  ""  );
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  hint  ?  hint  :  _T(  ""  ),  _T(  "Ex"  )  );
	 
	 int  i;
	 for  (  i  =  0;  i  <  nPkts;  i  ++  )  {
		  clean_myDRAW_VIDEO_DATA(  &p[i],  tBuf  );
	 }
	 return;
 }

 //  2011/12/15. player.displayQ用到了
 void  clean_MIS_MSG_procVideo_qmc(  MIS_MSG_procVideo_qmc  *  p,  LPCTSTR  hint  )
{
	if  (  !p  )  return;
	
	TCHAR	tBuf[128]	=	_T(  ""  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  hint  ?  hint  :  _T(  ""  ),  _T(  "clean_MIS_MSG_procVideo_qmc: free"  )  );
	 
#ifdef  __DEBUG__
	assert(  p->uiType  ==  CONST_misMsgType_procVideo_qmc  );
#endif

	if  (  p->uiType  ==  CONST_misMsgType_procVideo_qmc  )  {
		//  2012/11/09
		M_msg_showNo(  *p,  tBuf  );
		//
		freeMemory(  &p->pkt.memory  );
	}
	return;
}

 void  cleanEx_MIS_MSG_procVideo_qmc(  MIS_MSG_procVideo_qmc  *  p,  size_t  size,  LPCTSTR  hint )
 {
	 int	nPkts  =  size  /  sizeof(  MIS_MSG_procVideo_qmc  );

	 TCHAR	tBuf[128]	=	_T(  ""  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  hint  ?  hint  :  _T(  ""  ),  _T(  "Ex"  )  );
	 
	 int  i;
	 for  (  i  =  0;  i  <  nPkts;  i  ++  )  {
		  clean_MIS_MSG_procVideo_qmc(  &p[i],  tBuf  );
	 }
	 return;
 }


