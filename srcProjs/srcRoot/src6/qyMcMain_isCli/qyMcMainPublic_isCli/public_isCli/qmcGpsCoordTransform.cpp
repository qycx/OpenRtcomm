

#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCommon.h"

#include	"gpsCommProc.h"
#include	"qmcGpsProc.h"


#include	<math.h>

/////////////////////////


//  经度到像素x
static double lngToPixelX(  double lng,  int zoom  )  
{
	return  (  lng  +  180  )  *  (  256L  <<  zoom  )  /  360;
}

//  纬度到像素y
static double latToPixelY(  double lat,  int zoom  )  {
	double siny  =  sin(  lat  *  PI  /  180  );

	//
	if  (  1  -  siny  <  0.0001
		||  1  +  siny  <  0.0001  )  
	{
		#ifdef  __DEBUG__
				traceLog((TCHAR*)  _T(  "latToPixelY failed, siny is equal to 1"  )  );
		#endif
		return  0;
	}

	//
	double  y  =  log(  (  1  +  siny  )  /  (  1  -  siny  )  );
	return  (  128  <<  zoom  )  *  (  1  -  y  /  (  2  *  PI  )  );

}

#ifdef  __DEBUG__
		
int  testGpsFunc(  )
{

	double  k;
	k  =  sin(  -0.5  *  PI  );

	k  =  lngToPixelX(  0,  0  );

	return  0;	
}

#endif

////////////////////////////////////


 int  gps2Pnt(  void  *  p0,  myGPS_POSITION  *  pGpsPos,  int  zoom, POINT  *  pPnt  )
{
	int		iErr	=	-1;

	if  (  !pGpsPos  ||  !pPnt  )  return  -1;

#ifdef  __TEST_useXyAsLngLat__
		#if  0
			traceLog((TCHAR*)  _T(  "Not finished: gps2Pnt"  )  );
		#endif

		pPnt->x  =  pGpsPos->dblLongitude;
		pPnt->y  =  pGpsPos->dblLatitude;

		iErr  =  0;
#else

	pPnt->x  =  lngToPixelX(  pGpsPos->dblLongitude,  zoom  );
	pPnt->y  =  latToPixelY(  pGpsPos->dblLatitude,  zoom  );

	iErr  =  0;

#endif

errLabel:

	return  iErr;
}