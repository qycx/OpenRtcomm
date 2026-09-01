
#include	"stdafx.h"

#include	"qyMcMainCommon.h"
#include	"myQmcExt.h"
#include <hgCommProc.h>
#include <policyIsClientFunc.h>
#include	"ctxQmc.h"

//
extern int  newstartQThreadToSaveIC(MC_VAR_common* pProcInfo);
extern int  newstartQThreadToCheckICFile(MC_VAR_common* pProcInfo);


myQmcExt::myQmcExt()
{
	
}


myQmcExt::~myQmcExt()
{
	return;
}



//
atbool myQmcExt::bQyMcLogon_post(void* p0)
{
	CCtxQmc* pProcInfo = m_var.pProcInfo;

	//
	newstartQThreadToSaveIC(pProcInfo);
	newstartQThreadToCheckICFile(pProcInfo);

	//
	return  true;
}


void myQmcExt::qyMcLogoff_pre(void* p0)
{
	return;
}



//
extern  DWORD g_dwLastTickCnt_requestAFile;





//
int myQmcExt::doAnHgData(AnHgData* p)
{
	Param_hgCmd_servReq param;
	memset(&param, 0, sizeof(param));

	//


	//
	TCHAR  tBuf[25600];
	

	char* dataBuf = (char*)p->hg_cliData;
	int  dataLen = p->hg_cliDataLen;

	//
	int  ii = 0;
	if (parseHgCmd_servReq(0, 0, dataBuf, dataLen, &param)) {
		showInfo_open0(0, 0, _T("parseHgCmd_servReq failed"));
		goto  errLabel;
	}


	//
	if (param.cmd_org == CONST_hgCmd_requestAFile) {
		int  ii = 0;
		char* subStr = (char*)"[obj=240";
		char* pData = strstr(dataBuf, subStr);
		if (pData) {
			subStr = (char*)"len=";
			pData = strstr(pData, subStr);
			if (pData) {
				pData += strlen(subStr);
				int len;
				len = atol(pData);
				//
				pData = strstr(pData, "]");
				if (pData) {
					pData++;
					//
					int  ii = 0;
					//
#ifdef  __DEBUG__
					if (10) {
						FILE* fp;
						fp = fopen("d:\\tttbbb\\o1.png", "wb");
						if (fp) {
							fwrite(pData, 1, len, fp);
							fclose(fp);
							//
							int  ii = 0;
							//
							DWORD  dwTickCnt = myGetTickCount(mynull);
							int  iDiffInMs = dwTickCnt - g_dwLastTickCnt_requestAFile;

							//
							traceLog((TCHAR*)_T("doAnHgData: save file ok. iDiffInMs %dms"),  iDiffInMs);

						}
					}
#endif 
				}
			}

		}
	}

errLabel:

	return  0;
}






