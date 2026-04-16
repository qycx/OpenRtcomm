
#include	"stdafx.h"
#include	<tchar.h>
#include	<string>

#include	"qyMcMainCommon.h"
#include	"dumpAudio.h"

//extern "C"
//{
//#include "libavutil/opt.h"
//#include "libavcodec/avcodec.h"
//#include "libavutil/imgutils.h"
//
////#include "libavcodec/avcodec.h"
//#include "libavformat/avformat.h"
//
//};




//
// Created by qycx on 2021/3/1.
//

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <string>

//
#include "..\\aac\\include\\tmpAACCommon.h"
#include	"..\\aac\\include\\qdc_AAC.h"


//
// Created by qycx on 2021/1/30.
//




#define  MAX_cntof_qdcUnits     100




CQdcAAC::CQdcAAC() {
    m_pMems=NULL;
    m_usMaxCnt=MAX_cntof_qdcUnits;
    //
    init();
}
CQdcAAC::~CQdcAAC()
{
    exit();
}


int CQdcAAC::init()
{
    int iErr=-1;
    int size=sizeof(QDC_AAC_unit) * m_usMaxCnt;
    m_pMems=(QDC_AAC_unit*)mymalloc(size);
    if ( m_pMems==NULL)goto errLabel;
    memset(m_pMems,0,size);

    iErr = 0;
    errLabel:
    if ( iErr!=0){
        exit();
    }
    return iErr;
}

void CQdcAAC::exit() {
    int  i;

    //
    if ( m_pMems!=NULL) {
        for ( i=0;i<m_usMaxCnt;i++){
            if ( this->m_pMems[i].bUsed) {
                printf("error\n");
            }
        }
        M_myfree(m_pMems);
    }
    m_usMaxCnt=0;

    return;
}

//
CQdcAAC g_qdcAAC;





