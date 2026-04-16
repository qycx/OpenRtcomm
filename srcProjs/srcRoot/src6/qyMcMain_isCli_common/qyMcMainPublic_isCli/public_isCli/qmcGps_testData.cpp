

#include	"stdafx.h"
#include	"qyMcMainCommon.h"

#include	"gpsCommProc.h"
#include	"qmcGpsProc.h"

#include	"qmcVideoCapture_isCli.h"

#include	"qyComPortEx.h"
#include	"qyFile.h"

#include	"qmcCommFunc_isCli.h"

typedef  struct  __gpsDataMem_t	{
				 double			lng;
				 double			lat;
}		 GPS_DATA_mem;

#if  0
GPS_DATA_mem  gpsDataTable_default[]  =
{
        {       116.305741666687850, 40.038022221989102,        },
        {       116.305827777650620, 40.037827777862546,        },
        {       116.305886111259450, 40.037711111174687,        },
        {       116.305966666539500, 40.037513888941866,        },
        {       116.306063888867700, 40.037283333407508,        },
        {       116.306166666878600, 40.037044444349078,        },
        {       116.306266666518310, 40.036830555597938,        },
        {       116.306333333121400, 40.036677777767181,        },
        {       116.306341666645470, 40.036591666539508,        },
        {       116.306433333290940, 40.036444444391464,        },
        {       116.306566666497120, 40.036461111174688,        },
        {       116.306708333227360, 40.036513888835906,        },
        {       116.306888888676950, 40.036555555661515,        },
        {       116.307116666899790, 40.036625000105964,        },
        {       116.307297222349380, 40.036674999925822,        },
        {       116.307469444274900, 40.036725000010591,        },
        {       116.307663888931270, 40.036761111153496,        },
        {       116.307877777947310, 40.036836111015745,        },
        {       116.308086111280640, 40.036888888941867,        },
        {       116.308355555534360, 40.036977777745989,        },
        {       116.308597222434140, 40.037027777830758,        },
        {       116.308841666645480, 40.037094444433848,        },
        {       116.309052777820160, 40.037152777777777,        },
        {       116.309116666581890, 40.037008333206174,        },

		//
        {       116.308777777883730, 40.037083333333328,        },
        {       116.308933333290950, 40.037136110994552,        },
        {       116.309066666497120, 40.037163888878290,        },
        {       116.309094444910680, 40.037097222275200,        },
        {       116.309127777947310, 40.037024999989399,        },
        {       116.309152777989710, 40.036955555544957,        },
        {       116.309180555343630, 40.036891666783227,        },
        {       116.309202778074480, 40.036822222338778,        },
        {       116.309224999745680, 40.036766666571296,        },
        {       116.309261111153490, 40.036691666709054,        },
        {       116.309283332824710, 40.036625000105964,        },
        {       116.309311111238260, 40.036555555661515,        },
        {       116.309341666963360, 40.036494444476233,        },
        {       116.309369444317280, 40.036416666772631,        },
        {       116.309397222730850, 40.036347222328182,        },
        {       116.309427777396310, 40.036277777883740,        },
        {       116.309416667090520, 40.036219444539810,        },
        {       116.309358332951860, 40.036183333396913,        },
        {       116.309277778201630, 40.036161111195881,        },
        {       116.309197222391760, 40.036144444412656,        },
        {       116.309127777947310, 40.036127777894336,        },
        {       116.309052777820160, 40.036116666793824,        },
        {       116.309002777735390, 40.036097222169239,        },
        {       116.308927777608230, 40.036088888910079,        },
        {       116.308847222328180, 40.036061111026335,        },
        {       116.308763888676960, 40.036041666666662,        },
        {       116.308702777756580, 40.036024999883438,        },
        {       116.308777777883730, 40.036011111206477,        },
        {       116.308547222349380, 40.035991666581893,        },
        {       116.308483333587650, 40.035972222222220,        },
        {       116.308430555661520, 40.035963888963060,        },
        {       116.308383333418110, 40.035938888920676,        },
        {       116.308311111132300, 40.035933333237963,        },
        {       116.308230555322440, 40.035919444561003,        },
        {       116.308194444444440, 40.035902777777778,        },
        {       116.308211110962760, 40.036083333227367,        },


	{	-1.,	},
};

GPS_DATA_mem  gpsDataTable_101[]  =
{


	{	-1.,	},
};
#endif

//
BOOL	bInited_testGps  =  FALSE;

struct				{

	int				n;
	GPS_DATA_mem	mems[500];

}		g_testGps;

__declspec(  dllexport  )  int  initTestGps(  )
{
	int			iErr	=	-1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	CQyFile						file;
	BOOL		bFileOpen	=	FALSE;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	MIS_CNT	*	pMisCnt	=	getMisCntByName(  pProcInfo,  _T(  ""  )  );
	

	if  (  !bSupported_gps(  pQyMc  )  )  {
		 return  -1;
	}

	 if  (  bInited_testGps  )  return  -1;

	 //
	 TCHAR	fileName[MAX_PATH]	=	_T(  ""  );
	 _sntprintf(  fileName,  mycountof(  fileName  ),  _T(  "%s\\test\\%I64u.gps.txt"  ),  pQyMc->cfg.installDir,  pMisCnt->idInfo.ui64Id  );
	 if  (  !file.Open(  fileName,  CFile::modeRead  |  CFile::shareDenyNone  )  )  goto  errLabel;
	 bFileOpen  =  TRUE;

	 char	buf[256];
	 char	*	p;
	 int  n  =  0;
	 for  (  ;  n  <  mycountof(  g_testGps.mems  );  )  {
		 if  (  !file.gets(  buf,  mycountof(  buf  )  )  )  break;
		 trim(  buf  );
		 g_testGps.mems[n].lng  =  atof(  buf  );
		 //
		 p  =  strchr(  buf,  (  ','  )  );
		 if  (  !p  )  continue;
		 p  ++  ;
		 trim(  p  );
		 g_testGps.mems[n].lat  =  atof(  p  );
		 n  ++  ;
	 }

	 g_testGps.n  =  n;


	 bInited_testGps  =  TRUE;
	 iErr  =  0;
errLabel:
	 if  (  bFileOpen  )  file.Close(  );
	 if  (  iErr  )  {
		 exitTestGps(  );
	 }
	 return  iErr;
}

__declspec(  dllexport  )  void  exitTestGps(  )
{
	//

	//
	bInited_testGps  =  FALSE;
	return;
}

#if  0
int  get_n_gpsTable(  GPS_DATA_mem  *  pTable  )
{
	int	n	=	0;

	if  (  !pTable  )  return  0;

	for  (  ;  abs(  pTable->lat  -  (  -1  )  )  >  0.0001;  pTable  ++  )  {
		 n  ++  ;
	}

	return  n;
}
#endif

 __declspec(  dllexport  )  int  myTestData_gps(  QY_MESSENGER_ID  *  pIdInfo,  unsigned  int  nCtrls_test,  void  *  pmyGPS_POSITION  )
{
	 myGPS_POSITION  *  pGpsPos  =  (   myGPS_POSITION  *  )pmyGPS_POSITION;
	 if  (  !pGpsPos  )  return  -1;
	myGPS_POSITION  &  pos  =  *pGpsPos;

#ifdef  __TEST_useXyAsLngLat__

		int	x_start,y_start;
	float k,nStep_x,nStep_y;


	// 这个测试数据假装lo,la 就是 x,y
	if  (  pIdInfo->ui64Id  <  233  )  {
		x_start  = (  pIdInfo->ui64Id  %  100  )  *  10;
		y_start  = (  pIdInfo->ui64Id  %  100  )  *  2;

		k  =  (  nCtrls_test  *  (  pIdInfo->ui64Id  /  100  )  )  %  900;
		//  k  =  1;
		nStep_x  =  (  pIdInfo->ui64Id  /  200  )  %  5;
		nStep_y  =  (  pIdInfo->ui64Id  /  200  )  %  2;
	}
	else  if  (  pIdInfo->ui64Id  <  250  )  {
		x_start  = (  pIdInfo->ui64Id  %  100  )  *  12;
		y_start  = (  pIdInfo->ui64Id  %  100  )  *  2;

		k  =  (  nCtrls_test  *  (  pIdInfo->ui64Id  /  100  )  )  %  900;
		//  k  =  1;
		nStep_x  =  (  pIdInfo->ui64Id  /  200  )  %  5;
		nStep_y  =  (  pIdInfo->ui64Id  /  200  )  %  2;
	}
	else  {
		x_start  = (  pIdInfo->ui64Id  %  100  )  *  15;
		y_start  = (  pIdInfo->ui64Id  %  100  )  *  2;

		k  =  (  nCtrls_test  *  (  pIdInfo->ui64Id  /  100  )  )  %  800;
		//  k  =  1;
		nStep_x  =  (  pIdInfo->ui64Id  /  200  )  %  4;
		nStep_y  =  (  pIdInfo->ui64Id  /  200  )  %  2;
	}
	pos.dblLongitude  =  x_start  +  k  *  nStep_x;
	pos.dblLatitude  =  y_start  +  k  *  nStep_y;
#else

	nCtrls_test  =  nCtrls_test  /  2;
	//

	int  n  =  	0;	//  get_n_gpsTable(  pTable  );
	n  =  g_testGps.n;

	if  (  !n  ||  n  >  mycountof(  g_testGps.mems  )  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "myTestData_gps failed, n is %d,  %I64u"  ),  n,  pIdInfo->ui64Id  );
		return  -1;
	}

	unsigned  int  k  =  nCtrls_test  %  n;

	if  (  k  >=  mycountof(  g_testGps.mems  )  )  {
		qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "myTestData_gps failed, k is %d,  %I64u"  ),  k,  pIdInfo->ui64Id  );
		return  -1;
	}

	pos.dblLatitude  =  g_testGps.mems[k].lat;
	pos.dblLongitude  =  g_testGps.mems[k].lng;

	return  0;

#if  0
	//
	switch  (  k  )  {
			case  0:
				pos.dblLatitude  =  40.038022221989102;
				pos.dblLongitude  =  116.305741666687850;
					break;
			case  1:
				pos.dblLatitude  =  40.037827777862546;
				pos.dblLongitude  =  116.305827777650620;
					break;
			case  2:
				pos.dblLatitude  =  40.037711111174687;
				pos.dblLongitude  =  116.305886111259450;
					break;
			case  3:
				pos.dblLatitude  =  40.037513888941866;
				pos.dblLongitude  =  116.305966666539500;
					break;
			case  4:
				pos.dblLatitude  =  40.037283333407508;
				pos.dblLongitude  =  116.306063888867700;
					break;
			case  5:
				pos.dblLatitude  =  40.037044444349078;
				pos.dblLongitude  =  116.306166666878600;
					break;
			case  6:
				pos.dblLatitude  =  40.036830555597938;
				pos.dblLongitude  =  116.306266666518310;
					break;
			case  7:
				pos.dblLatitude  =  40.036677777767181;
				pos.dblLongitude  =  116.306333333121400;
					break;
			case  8:
				pos.dblLatitude  =  40.036591666539508;
				pos.dblLongitude  =  116.306341666645470;
					break;
			case  9:
				pos.dblLatitude  =  40.036444444391464;
				pos.dblLongitude  =  116.306433333290940;
					break;
			case  10:
				pos.dblLatitude  =  40.036461111174688;
				pos.dblLongitude  =  116.306566666497120;
					break;
			case  11:
				pos.dblLatitude  =  40.036513888835906;
				pos.dblLongitude  =  116.306708333227360;
					break;
			case  12:
				pos.dblLatitude  =  40.036555555661515;
				pos.dblLongitude  =  116.306888888676950;
					break;
			case  13:
				pos.dblLatitude  =  40.036625000105964;
				pos.dblLongitude  =  116.307116666899790;
					break;
			case  14:
				pos.dblLatitude  =  40.036674999925822;
				pos.dblLongitude  =  116.307297222349380;
					break;
			case  15:
				pos.dblLatitude  =  40.036725000010591;
				pos.dblLongitude  =  116.307469444274900;
					break;
			case  16:
				pos.dblLatitude  =  40.036761111153496;
				pos.dblLongitude  =  116.307663888931270;
					break;
			case  17:
				pos.dblLatitude  =  40.036836111015745;
				pos.dblLongitude  =  116.307877777947310;
					break;
			case  18:
				pos.dblLatitude  =  40.036888888941867;
				pos.dblLongitude  =  116.308086111280640;
					break;
			case  19:
				pos.dblLatitude  =  40.036977777745989;
				pos.dblLongitude  =  116.308355555534360;
					break;
			case  20:
				pos.dblLatitude  =  40.037027777830758;
				pos.dblLongitude  =  116.308597222434140;
					break;
			case  21:
				pos.dblLatitude  =  40.037094444433848;
				pos.dblLongitude  =  116.308841666645480;
					break;
			case  22:
				pos.dblLatitude  =  40.037152777777777;
				pos.dblLongitude  =  116.309052777820160;
					break;
			case  23:
				pos.dblLatitude  =  40.037008333206174;
				pos.dblLongitude  =  116.309116666581890;
					break;
			default:
					break;
	}
#endif



#endif

	return  0;

}
