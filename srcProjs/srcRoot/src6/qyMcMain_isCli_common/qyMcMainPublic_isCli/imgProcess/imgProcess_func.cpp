
#include	"stdafx.h"

#include	"shlobj.h"
#include	<time.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"imgProcessCommon.h"

#include	"bmpExPublic.h"


#ifdef  __DEBUG__
__declspec(  dllexport  )  int  testFunc_imgProcess(  )
{
	ATOM	a;
	//  HINSTANCE	hInst  =  get_my_hInst(  );

	double  d  =  1.5;

	d  =  -1.5;
	int  i  =  true;

	myRound(  d  );

	//
#if  0
	{
		CBitmapEx	bmp;
		//
		bmp.Load(  _T(  "c:\\tttbbb\\test.bmp"  )  );
		bmp.Scale(  200,  200  );
		bmp.Save(  _T(  "c:\\tttbbb\\test200.bmp"  )  );
		
		bmp.Load(  _T(  "c:\\tttbbb\\test.bmp"  )  );
		bmp.SetResampleMode( RM_BILINEAR  ); 
		bmp.Scale(  200,  200  );
		bmp.Save(  _T(  "c:\\tttbbb\\test200.bl.bmp"  )  );


		bmp.Load(  _T(  "c:\\tttbbb\\test.bmp"  )  );
		bmp.SetResampleMode( RM_BICUBIC  ); 
		bmp.Scale(  200,  200  );
		bmp.Save(  _T(  "c:\\tttbbb\\test200.bc.bmp"  )  );

	}
#endif


	//
	float  alphaArray[256];

	BYTE  alpha_in  =  18;
	BYTE  alpha_out  =  28;
	float  fMaskGamma  =  1;

	calculateAlphaTables(  alpha_in,  alpha_out,  fMaskGamma,  alphaArray  );

	//
	BYTE  r  =  27;	
	BYTE  g  =  47;	
	BYTE  b  =  32;	//  83;

						  float  fh, fs, fl;
						  rgbToHsl_f(  r,  g,  b,  0xff,  &fh,  &fs,  &fl,  NULL  );
						  WORD  wh, ws, wl;
						  float  f;
						  f  =  fh  *  MAX_h_ms;
						  wh  =  myRound(  f  );
						  f  =  fs  *  240;
						  ws  =  myRound(  f  );
						  f  =  fl  *  240;
						  wl  =  myRound(  f  );
						  //
						  //
						  BYTE  ucR,  ucG,  ucB;
						  hslToRgb_f(  fh,  fs,  fl,  1.,  &ucR,  &ucG,  &ucB,  NULL  );
						  if  (  ucR  !=  r  ||  ucG  !=  g  ||  ucB  !=  b  )  {
							  traceLog(  _T(  "not ok"  )  );
						  }



	return  0;
}
#endif


#if  0
 int  printImMsgContent_n(  void  *  pSessionParam,  MSG_ROUTE  *  pRoute,  IM_CONTENTU  *  pContent_n,  int  iContentLen,  TCHAR  *  tBuf,  unsigned  int  maxuiBufCnt  )
{
	traceLogA(  "test"  );
	return  0;
}
#endif


