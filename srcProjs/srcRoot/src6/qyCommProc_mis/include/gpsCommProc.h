
#ifndef  __GPSCOMMPROC_H__
#define  __GPSCOMMPROC_H__		//  {


typedef struct _myGPS_POSITION {
   DWORD dwVersion;
   DWORD dwSize;

   DWORD dwValidFields;

   DWORD dwFlags;

   SYSTEMTIME stUTCTime;

   double dblLatitude;
   double dblLongitude;
   float  flSpeed;
   float  flHeading;
   double dblMagneticVariation;
   float  flAltitudeWRTSeaLevel;
   float  flAltitudeWRTEllipsoid;

#if  0

   GPS_FIX_QUALITY     FixQuality;
   GPS_FIX_TYPE        FixType;
   GPS_FIX_SELECTION   SelectionType;
   float flPositionDilutionOfPrecision;
   float flHorizontalDilutionOfPrecision;
   float flVerticalDilutionOfPrecision;

   DWORD dwSatelliteCount;
   DWORD rgdwSatellitesUsedPRNs[GPS_MAX_SATELLITES];

   DWORD dwSatellitesInView;
   DWORD rgdwSatellitesInViewPRNs[GPS_MAX_SATELLITES];
   DWORD rgdwSatellitesInViewElevation[GPS_MAX_SATELLITES];
   DWORD rgdwSatellitesInViewAzimuth[GPS_MAX_SATELLITES];
   DWORD rgdwSatellitesInViewSignalToNoiseRatio[GPS_MAX_SATELLITES];
#endif

} myGPS_POSITION;

//
typedef  struct		{
			int		dd;
			int		mm;
			int		ss100;
}		 my_Latitude;		//  latitude

typedef  struct		{
			int		ddd;
			int		mm;
			int		ss100;
}		 my_Longitude;		//  longitude



int  setGpsPos(  void  *  pComPortEx,  myGPS_POSITION  *  pPos  );
int  getGpsPos(  void  *  pComPortEx,  myGPS_POSITION  *  pPos,  DWORD  *  pdwTickCnt_modified  );

int  gps_DisplayStr(  myGPS_POSITION  *  pPos,  TCHAR  *  tBuf,  unsigned  int  cnt  );


typedef  int (  *PF_parseGpsStr  )(  void  *  pCComPortEx,  char  *  str  );


#endif  //  }




