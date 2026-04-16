// rtspCli.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include	<tchar.h>
#include	<Windows.h>
#include	<stddef.h>

#include	"qyDefs_open.h"
#include	"qmOpenCommon.h"


//
int _tmain(int argc, _TCHAR* argv[])
{

	char	argv0[128]  =  (  "rtspCli"  );
	char	argv1[128]  =  (  "-t"  );
	char	argv2[128]  =  (  "-D"  );
	char	argv3[128]  =  (  "20"  );
#if  0
	char	argv4[128]  =  (  "rtsp://127.0.0.1:8554/stream"  );
#elif  0
	char	argv4[128]  =  (  "rtsp://127.0.0.1:8554/video.264"  );
#else
	char	argv4[128]  =  (  "rtsp://127.0.0.1/testWildLife.ts"  );
#endif

	char  *  pArgv[10];

	int		tmp_argc  =  0;
	//
	pArgv[tmp_argc]  =  argv0;  tmp_argc  ++  ;
	//pArgv[tmp_argc]  =  argv1;  tmp_argc  ++  ;
	pArgv[tmp_argc]  =  argv2;  tmp_argc  ++  ;
	pArgv[tmp_argc]  =  argv3;  tmp_argc  ++  ;
	pArgv[tmp_argc]  =  argv4;  tmp_argc  ++  ;

#ifdef  _DEBUG
#if  0
	printf(  "for test, argc = tmp_argc\n"  );
	argc  =  tmp_argc;
	argv  =  pArgv;
#endif
#endif
	
	__try  {
	  			
		  //			
		  //  rtspCliHelp_main(  tmp_argc,  pArgv  );
		  rtspCliHelp_main(  argc,  argv  );
	}
	__except  (  1  )  {
		printf(  (  "except: rtspCliHelp_main\n"  )  );

	}

	return 0;
}

