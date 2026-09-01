
#include	"stdafx.h"
#include	<tchar.h>

#include	<mmeapi.h>
#include	<WinSock2.h>
#include	<stdlib.h>

#include	"qmOpenCommon.h"
#include	"tmpDefs_open.h"
#include	"smCommProc.h"

#include <qytcharcommproc.h>
#include	"qmCommon.h"



int parseCaServCfg(char* caServCfg, char* ip, int cntof_ip, int* piPort, char* hg_ip, int cntof_hg_ip, int* hgPort)
{
	int  iErr = -1;
	do {
		char  buf[1024];
		safeStrnCpy(caServCfg, buf, mycountof(buf));
		char* p = strchr(buf, ':');
		if (!p)  break;
		*p = 0;  p++;

		safeStrnCpy(buf, ip, cntof_ip);
		//*piPort = atol(p);

		
		char* pTF;
		pTF = strchr(p, ';');
		if (!pTF)  break;
		*pTF = 0;  pTF++;

		*piPort = atol(p);

		char* pTHg;
		pTHg = strchr(pTF, '=');

		if (!pTHg) break;
		pTHg++;


		p = strchr(pTHg, ':');
		if (!p)  break;
		*p = 0;  p++;

		safeStrnCpy(pTHg, hg_ip, cntof_hg_ip);

		*hgPort = atol(p);
		

		iErr = 0;
	} while (false);

	return  iErr;
}


