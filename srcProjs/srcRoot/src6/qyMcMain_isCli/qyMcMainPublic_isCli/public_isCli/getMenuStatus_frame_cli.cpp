
#include	"stdafx.h"
#include	"shlobj.h"
#include	<time.h>
#include	<tchar.h>

#ifndef  __WINCE__
		 #include	"myresource.h"
#endif
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"





 int  getMenuStatus_frame(  QY_MC  *  pQyMc,  void  *  p0,  void  *  p1,  void  *  piStatusParam  )
{
	 int						iErr		=	-1;
	 //  p0;
	 int						iMenuId		=	(  int  )p1;
	 int				*		piStatus	=	(  int  *  )piStatusParam;

	 if  (  !pQyMc  )  return  -1;
	 if  (  !piStatus  )  return  -1;

	 if  (  isIsCli(  pQyMc  )  )  {		 
		 switch  (  iMenuId  )  {
				 case  ID_globalGpsVWall:
				 case  ID_gpsVWall:
				 case  ID_notTestGps:
				 case  ID_testGps:
					   if  (  !bSupported_gps(  pQyMc  )  )  {
						   //  skipped
						   goto  errLabel;
					   }
					   break;
				 default:
						break;
		 }
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
 }
