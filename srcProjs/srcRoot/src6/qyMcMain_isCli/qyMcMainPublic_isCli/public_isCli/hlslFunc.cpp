
#include	"stdafx.h"
#include	<Windows.h>
#include	<stdio.h>
#include	<math.h>
#include	<stdlib.h>
#include	<tchar.h>
#include	<Shlwapi.h>

#include	"colorSpaceFunc.h"
#include	"imgProcessPublic.h"


//
MY_float3  to_MY_float3(  float  x,  float  y,  float  z  )
{
	MY_float3  f3;
	f3.x  =  x;
	f3.y  =  y;
	f3.z  =  z;

	return  f3;
}

MY_float4  to_MY_float4(  float  x,  float  y,  float  z,  float  w  )
{
	MY_float4  f4;
	f4.x  =  x;
	f4.y  =  y;
	f4.z  =  z;
	f4.w  =  w;

	return  f4;
}


MY_RGB  to_MY_RGB(  float  x,  float  y,  float  z  )
{
	MY_RGB  f3;
	f3.r  =  x;
	f3.g  =  y;
	f3.b  =  z;

	return  f3;
}

BYTE  toByte_rgb(  float  f_rgb  )
{
	WORD  w_rgb;
	w_rgb  =  f_rgb  *  255;
	myRound(  w_rgb  );
	return  w_rgb;
}

BYTE  toByte_hsl(  float  f_hsl  )
{
	WORD  w_hsl;
	w_hsl  =  f_hsl  *  240;
	myRound(  w_hsl  );
	return  w_hsl;
}

float toFloat_rgb(  BYTE  uc_rgb  )
{
	return  uc_rgb  /  255.;
}

float toFloat_hsl(  BYTE  uc_hsl  )
{
	return  uc_hsl  /  240.;
}





