

#include "stdafx.h"
#include	<tchar.h>
#include	<MMSystem.h>

#include    "tmpRegFunc_open.h"
#include    "showInfo_open.h"

#include    "myCmdParams_open.h"

#include	"proc_ca_jdzy.h"

#include <stdio.h>                                                                 
#include <tchar.h> 

GBuf_jdzy	gBuf;


char* UnicodeToAnsi(const wchar_t* szStr, int& nLen)
{
    nLen = WideCharToMultiByte(CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL);
    if (nLen == 0)
    {
        return NULL;
    }
    char* pResult = new char[nLen];
    WideCharToMultiByte(CP_ACP, 0, szStr, -1, pResult, nLen, NULL, NULL);
    return pResult;
}

int printLogChar(const char* log) {
    return 0;
    FILE* pf = fopen("D:/qycx/log_sx.txt", "a+");
    if (pf == NULL)
    {
        perror("fopen failed");
        //
        return 1;
    }

    //TCHAR* pp;  


    fprintf(pf, "%s:%s  - %s \n", __DATE__, __TIME__, log);

    fclose(pf);

    return 0;

}


int printLog(TCHAR* log) {
    return 0;
    FILE* pf = fopen("D:\\qycx\\log_sx.txt", "a+");
    if (pf == NULL)
    {
        perror("fopen failed.");
        //
        return 1;
    }

    //TCHAR* pp;

    char* pBuf = NULL;
    int nLen = 0;

    pBuf = UnicodeToAnsi(log, nLen);

    if (pBuf) {
        fprintf(pf, "%s:%s  - %s \n", __DATE__, __TIME__, pBuf);
        delete[] pBuf;
    }

    fclose(pf);

}


//
GBuf_jdzy::GBuf_jdzy()
{
	//
	memset(&m_var, 0, sizeof(m_var));

	//
	return;
}


//
GBuf_jdzy::~GBuf_jdzy()
{
	return;
}






#define BUFFER_MED_SIZE 1024

inline void LogToFile(const _TCHAR* szFmt, ...)
{
    va_list args;
    TCHAR szBuf[BUFFER_MED_SIZE] = { 0 };

    va_start(args, szFmt);
    _vstprintf_s(szBuf, BUFFER_MED_SIZE, szFmt, args);
    va_end(args);
}




