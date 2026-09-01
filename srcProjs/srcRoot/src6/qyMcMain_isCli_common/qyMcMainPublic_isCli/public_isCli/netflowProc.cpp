



#include	"stdafx.h"


#include    <tchar.h>
#include    "qyMcMainCommon.h"
#include	"qyCusResTemp.h"

#include "ctxQmc.h"

#include	"qmcCommFunc_isCli.h"
#include	"isCliHelpPublic.h"

#include <qmcVideoCapture_isCli.h>


#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "IPHLPAPI.lib")

#include <iphlpapi.h>

#include <stdio.h>
#include <stdlib.h>

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

/* Note: could also use malloc() and free() */

        //
struct {
    DWORD  dw_i;
    DWORD  dw_o;
    DWORD  dwTickCnt;
}  sBuf = { 0 };


//
int netflow_main()
{
    CCtxQmc* pProcInfo = QY_GET_procInfo_isCli();
    MIS_CNT* pMisCnt = pProcInfo->getMisCntByName(_T(""));

    float  fRand = rand();

    while (1) {
        if (fRand < 10)  break;
        fRand /= 10;
        continue;        
    }

    //
    MIS_CHANNEL* pChannel = getChannelByType(pMisCnt, 0);
    
    do {
        if (!bChannelOk(pChannel, nullptr))  fRand = 0;
        else {
            DWORD  dwTickCnt = myGetTickCount(mynull);
            int iEInMs = dwTickCnt - pMisCnt->status.dwLastTickCnt_initTaskAvFrom_video;
            if (iEInMs) {
                float f  =  1000. / iEInMs;
                if (f < 0.1)  f = 0.1;
                fRand *= f;
            }
        }

        //
        float fDiscards = fRand / 1000.;

        //
        pMisCnt->status.fDiscards = fDiscards;

        //
#ifdef  __DEBUG__
        //traceLog((TCHAR*)_T("fDiscards %f"), pMisCnt->status.fDiscards);
#endif

        //
    } while (false);

    return  0;
}




#if 0
int iinetflow_main()
{

    // Declare and initialize variables.

    DWORD dwSize = 0;
    DWORD dwRetVal = 0;

    unsigned int i, j;

    /* variables used for GetIfTable and GetIfEntry */
    MIB_IFTABLE* pIfTable;
    MIB_IFROW* pIfRow;

    //
    char* devDesc;
    devDesc  = "Realtek Gaming GbE Family Controller";


    // Allocate memory for our pointers.
    pIfTable = (MIB_IFTABLE*)MALLOC(sizeof(MIB_IFTABLE));
    if (pIfTable == NULL) {
        printf("Error allocating memory needed to call GetIfTable\n");
        return 1;
    }
    // Make an initial call to GetIfTable to get the
    // necessary size into dwSize
    dwSize = sizeof(MIB_IFTABLE);
    if (GetIfTable(pIfTable, &dwSize, FALSE) == ERROR_INSUFFICIENT_BUFFER) {
        FREE(pIfTable);
        pIfTable = (MIB_IFTABLE*)MALLOC(dwSize);
        if (pIfTable == NULL) {
            printf("Error allocating memory needed to call GetIfTable\n");
            return 1;
        }
    }
    // Make a second call to GetIfTable to get the actual
    // data we want.
    if ((dwRetVal = GetIfTable(pIfTable, &dwSize, FALSE)) == NO_ERROR) {
        
        //
#ifdef  __DEBUG__
        //traceLog((TCHAR*)_T("\tNum Entries: %ld\n\n"), pIfTable->dwNumEntries);
#endif


        //
        for (i = 0; i < pIfTable->dwNumEntries; i++) {
            pIfRow = (MIB_IFROW*)&pIfTable->table[i];
            printf("\tIndex[%d]:\t %ld\n", i, pIfRow->dwIndex);
            //
            //traceLog((TCHAR*)_T("\tInterfaceName[%d]:\t %ws"), i, pIfRow->wszName);
            printf("\n");
            //
                        //
            if (pIfRow->dwType == IF_TYPE_IEEE80211
                || pIfRow->dwType == IF_TYPE_ETHERNET_CSMACD)
            {
                int  ii = 0;
            }
            else {
                //
                continue;
            }
            if (pIfRow->dwPhysAddrLen != 6)  continue;
            char* sym = (char*)"microsoft";
            if (!_strnicmp(sym, (char*)pIfRow->bDescr, strlen(sym)))  continue;
            switch (pIfRow->dwOperStatus) {
            case  IF_OPER_STATUS_OPERATIONAL:
                break;
            default:
                continue;
            }
            if (pIfRow->dwAdminStatus != 1)  continue;


            //
            if (6 != pIfRow->dwPhysAddrLen)  continue;
            //traceLog((TCHAR*)_T("dwPhysAddrLen % d"), pIfRow->dwPhysAddrLen);

            //
            printf("\tDescription[%d]:\t ", i);
            for (j = 0; j < pIfRow->dwDescrLen; j++)
                printf("%c", pIfRow->bDescr[j]);
            
            //
            //char* desc = (char*)"Intel(R) Wi-Fi 6E AX211 160MHz";
            char descBuf[256];
            if (pIfRow->dwDescrLen >= mycountof(descBuf)) continue;
            safeStrnCpy((char*)pIfRow->bDescr, descBuf, pIfRow->dwDescrLen  +  1);
            //
            //if (stricmp(devDesc, (char*)descBuf)) continue;


            //
            //traceLog((TCHAR*)_T("wsz[%d] %s"), i, pIfRow->wszName);

            traceLog((TCHAR*)_T("desc[%d], %S"), i, pIfRow->bDescr);
            printf("\n");
            //
            //traceLog((TCHAR*)_T("Type[%d]: %d"), i,  pIfRow->dwType);
            //



            //
            //printf("\tMtu[%d]:\t\t %ld\n", i, pIfRow->dwMtu);
            //printf("\tSpeed[%d]:\t %ld\n", i, pIfRow->dwSpeed);
            //printf("\tPhysical Addr:\t ");
            char buf[128]  =  "";
            if (pIfRow->dwPhysAddrLen == 0)
                printf("\n");
            for (j = 0; j < pIfRow->dwPhysAddrLen; j++) {
                if (j == (pIfRow->dwPhysAddrLen - 1))
                    _snprintf(buf,  mycountof(buf),  ("%s%.2X"), buf, (int)pIfRow->bPhysAddr[j]);
                else
                    _snprintf(buf,mycountof(buf), ("%s%.2X-"), buf,  (int)pIfRow->bPhysAddr[j]);
            }
            traceLog((TCHAR*)_T("physical addr: %S"), buf);
            //traceLog((TCHAR*)_T("\tAdmin Status[%d]:\t %ld"), i, pIfRow->dwAdminStatus);

            //
            //traceLog((TCHAR*)_T(  "\tOper Status[%d]:%d "), i, pIfRow->dwOperStatus);
            //
            traceLog((TCHAR*)_T("i %u, o %u, d_i %u, d_o %u, e_i %u, e_o %u"), pIfRow->dwInOctets, pIfRow->dwOutOctets, pIfRow->dwInDiscards, pIfRow->dwOutDiscards, pIfRow->dwInErrors,  pIfRow->dwOutErrors);
            
            //pIfRow->ddwOutDiscards

            //
            DWORD  curTickCnt = myGetTickCount(nullptr);
            if (sBuf.dwTickCnt) {
                int  iDiffInMs = curTickCnt - sBuf.dwTickCnt;
                if (iDiffInMs) {
                    float v_i = (pIfRow->dwInOctets - sBuf.dw_i) / (float)iDiffInMs * 8 ;
                    float v_o = (pIfRow->dwOutOctets - sBuf.dw_o) / (float)iDiffInMs * 8 ;
                    traceLog((TCHAR*)_T("v_i %fkbps, v_o %fkbps"), v_i, v_o);
                }
            }
            sBuf.dw_i = pIfRow->dwInOctets;
            sBuf.dw_o = pIfRow->dwOutOctets;
            sBuf.dwTickCnt = curTickCnt;


        }
    }
    else {
        printf("GetIfTable failed with error: \n", dwRetVal);
        if (pIfTable != NULL) {
            FREE(pIfTable);
            pIfTable = NULL;
        }
        return 1;
        // Here you can use FormatMessage to find out why 
        // it failed.
    }
    if (pIfTable != NULL) {
        FREE(pIfTable);
        pIfTable = NULL;
    }
    return 0;
}
#endif







