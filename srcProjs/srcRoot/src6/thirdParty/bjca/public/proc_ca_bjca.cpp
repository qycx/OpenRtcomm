

#include	<tchar.h>
#include	"proc_ca_bjca.h"
#include <showInfo_open.h>
#include    "dbgFunc_open.h"


char  qnmVer[]   =  "01010103";

GBuf_bjca	gBuf;


//
GBuf_bjca::GBuf_bjca()
{
	//
	memset(&m_var, 0, sizeof(m_var));

	//
	strncpy(  m_var.ver,  qnmVer,  mycountof(m_var.ver  )  );

	//
	return;
}


//
GBuf_bjca::~GBuf_bjca()
{
	return;
}


//
//
int  parseCertList(char* cstrlist, Certs* pCerts)
{
    int  iErr = -1;
    int cnt = 0;
    char* p;
    char    tmp_cstrlist[1024];

    //
    strncpy(tmp_cstrlist, cstrlist, sizeof(tmp_cstrlist));

    //
    char* pStart = tmp_cstrlist;

    //
    memset(pCerts, 0, sizeof(pCerts[0]));

    //
    for (;;) {
        if (cnt >= mycountof(pCerts->mems)) break;
        //
        char* sep = "&&&";
        p = strstr(pStart, sep);
        if (!p)break;
        *p = 0;
        //strncpy(pCerts->mems[cnt].certDesc, pStart, sizeof(pCerts->mems[cnt].certDesc));
        //
        char* sep1 = "||";
        char* p1 = strstr(pStart, sep1);
        if (!p1)break;
        *p1 = 0;
        strncpy(pCerts->mems[cnt].usrName, pStart, sizeof(pCerts->mems[cnt].usrName));
        p1 += strlen(sep1);
        strncpy(pCerts->mems[cnt].certId, p1, sizeof(pCerts->mems[cnt].certId));

        //
        cnt++;
        pStart = p + strlen(sep);
        continue;
    }
    pCerts->usCnt = cnt;


    iErr = 0;
errLabel:

    return  iErr;
}


//
int  tmp_showInfo(void* p0, LPCTSTR  tWhere, LPCTSTR  hint)
{
    showInfo_open0(p0, tWhere, hint);
    //
    logStatus(gBuf.m_var.appParams.logFile, gBuf.m_var.appParams.who_showInfo,  tWhere, 0, hint);

    //
    return  0;
}

//
int  tmp_set_who_showInfo(LPCTSTR  name)
{
    return  set_who_showInfo(name);
}



