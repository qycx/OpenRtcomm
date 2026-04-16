

#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCommon.h"

#include	"gpsCommProc.h"
#include	"qmcGpsProc.h"

#include	"qmcVideoCapture_isCli.h"

#include	"qyComPortEx.h"


 int  gps_DisplayStr(  myGPS_POSITION  *  pPos,  TCHAR  *  tBuf,  unsigned  int  cnt  )
 {
	 if  (  !tBuf  ||  !cnt  )  return  -1;

	 my_Latitude	la;
	 my_Longitude	lo;
	 float  f;
	 char	cNS;
	 char	cEW;

	 f  =  pPos->dblLatitude;
	 if  (  f  <  0  )  {
		 cNS  =  'S';
		 f  =  f  *  -1;
		 }
	 else  {
		   cNS  =  'N';
	 }

	 la.dd  =  f;
	 f  =  f  -  la.dd;
	 f  *=  60;
	 la.mm  =  f;
	 f  =  f  -  la.mm;
	 f  *=  60;
	 la.ss100  =  f  *  100;

	 f  =  pPos->dblLongitude;
	 if  (  f  <  0  )  {
		 cEW  =  'W';
		 f  =  f  *  -1;
	     }
	 else  {
		   cEW  =  'E';
	 }

	 lo.ddd  =  f;
	 f  =  f  -  lo.ddd;
	 f  *=  60;
	 lo.mm  =  f;
	 f  =  f  -  lo.mm;
	 f  *=  60;
	 lo.ss100  =  f  *  100;


	 tBuf[0]  =  0;
	 _sntprintf(  tBuf,  cnt,  _T(  "%s %d?d'%d.%d\" %c."  ),  tBuf,  la.dd,  la.mm,  la.ss100  /  100,  la.ss100  %  100,  cNS  );
	 _sntprintf(  tBuf,  cnt,  _T(  "%s %d?d'%d.%d\" %c."  ),  tBuf,  lo.ddd,  lo.mm,  lo.ss100  /  100,  lo.ss100  %  100,  cEW  );
	 _sntprintf(  tBuf,  cnt,  _T(  "%s UTC: %02d:%02d:%02d"  ),  tBuf,  (  int  )pPos->stUTCTime.wHour,  (  int  )pPos->stUTCTime.wMinute,  (  int  )pPos->stUTCTime.wSecond  );

	 return  0;
 }

 BOOL  bSupported_gps(  QY_MC  *  pQyMc  )
{

	//  2014/08/03
	//if  (  qyGetAppAvLevel_qyMc(  )  ==  CONST_qyAppAvLevel_sd  )  return  FALSE;

	return  pQyMc->ucbSupported_gps_default;	//  bSupported_gps_default(  );
 }


int  setGpsPos(  void  *  pComPortEx,  myGPS_POSITION  *  pPos  )
{
	CComPortEx  *  pPort  =  (  CComPortEx  *  )pComPortEx;
	if  (  !pPort  )  return  -1;

	{
		CQySyncObj	syncObj;

		if  (  syncObj.sync(  CONST_mutexName_syncComPort  )  )  return  -1;

		memcpy(  &pPort->m_var.gpsPos,  pPos,  sizeof(  pPort->m_var.gpsPos  )  );
		pPort->m_var.dwTickCnt_modified_gpsPos  =  GetTickCount(  );

	}

	//
	if  (  pPort->m_var.hWndOwner  )  {
		PostMessage(  pPort->m_var.hWndOwner,  CONST_qyWm_postComm,  CONST_qyWmParam_gps,  0  );
	}

	return  0;
}
