// isCliEx.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include	"isCliExPublic.h"



#if  0
			#define		__SUPPORT_remoteStorage__				//  2014/08/03
#endif

#if  0
			#define		__SUPPORT_fileServer__					//  2015/08/04
#endif
 
//
#if  !defined(  __SUPPORT_remoteStorage__  )  &&  !defined(  __SUPPORT_fileServer__  )

		#if  10
				#define		__SUPPORT_rtsp__			//  2014/04/10
		#endif

		#if  0
				#define		__SUPPORT_gps__				//  2012/05/23
		#endif

#endif

////////////////////
#ifdef  _DEBUG
		#if  0
				#define		__SUPPORT_rtsp__			//  2014/04/10
		#endif

#endif

///////////////////////////////////////////////
//
//

 //  2014/04/10 
extern  "C"  _declspec(  dllexport  )  BOOL  bSupported_rtsp(  )
 {
#ifdef  __SUPPORT_rtsp__
		return  TRUE;
#endif
		return  FALSE;
 }




extern  "C"  _declspec(  dllexport  )  BOOL  bSupported_gps_default(  )
{
	#ifdef  __SUPPORT_gps__
			return   TRUE;
	#endif

	 return  FALSE;
 }


  //  2014/08/03
extern  "C"  _declspec(  dllexport  )  BOOL  bSupported_remoteStorage_default(  )
 {
	#ifdef  __SUPPORT_remoteStorage__
			return  TRUE;
	#endif

	return  FALSE;
 }


extern  "C"  __declspec(  dllexport  )  BOOL  bSupported_fileServer_default(  )
{
	#ifdef  __SUPPORT_fileServer__
			return  TRUE;
	#endif

	return  FALSE;
}

