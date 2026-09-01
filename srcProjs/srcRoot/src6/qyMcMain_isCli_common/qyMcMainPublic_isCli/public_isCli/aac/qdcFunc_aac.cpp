
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

#include "..\\aac\\include\\tmpAACCommon.h"
#include	"..\\aac\\include\\qdc_AAC.h"



#include <stdlib.h>
#include <stdio.h>
#include <string.h>



  //
  int qdc_aac_init()
  {
      //avcodec_register_all();

      g_qdcAAC.bDone_qdc_init = true;

      return 0;
  }

  int qdc_aac_exit()
  {
      g_qdcAAC.bDone_qdc_init=false;

      return 0;
  }

// need sync by mutex before called
int newQdcAACUnitIndex()
{
    int i;

    if (g_qdcAAC.m_pMems==NULL)return -1;

    for ( i=0;i< g_qdcAAC.m_usMaxCnt;i++){
        if (g_qdcAAC.m_pMems[i].bUsed)continue;
        break;
    }
    if ( i== g_qdcAAC.m_usMaxCnt)return -1;
    QDC_AAC_unit *pUnit=&g_qdcAAC.m_pMems[i];
    //
    pUnit->bUsed=true;


    //memset(&pUnit->encA_var,0,sizeof(pUnit->encA_var));
    memset(&pUnit->decA_var,0,sizeof(pUnit->decA_var));    //
    memset(&pUnit->decBufs,0,sizeof(pUnit->decBufs));

    //
    return i;
}

// need sync by mutex before called
void freeQdcAACUnitIndex(int index)
{
    if (g_qdcAAC.m_pMems==NULL)return;
    if(index <0||index>= g_qdcAAC.m_usMaxCnt)return;
    QDC_AAC_unit *pUnit=&g_qdcAAC.m_pMems[index];

    //
    freeDecBufsAAC(index);

    //
    pUnit->bUsed=false;

    // do clean

    return;
}

QDC_AAC_unit * getQdcAACUnitByIndex(int index)
{
    if (g_qdcAAC.m_pMems==NULL)return NULL;
    if(index <0||index>= g_qdcAAC.m_usMaxCnt)return NULL;
    return &g_qdcAAC.m_pMems[index];
}

//
int freeDecBufsAAC(int index_qdcUnit)
{
    QDC_AAC_unit *pUnit = getQdcAACUnitByIndex(index_qdcUnit);
    if (!pUnit) return -1;
    int i;
    for ( i=0;i<pUnit->decBufs.maxCnt_decBufMems;i++){
        DEC_buf_aac  *pMem=&pUnit->decBufs.mems[i];
        if ( pMem->pBuf) myfree(pMem->pBuf);
        memset(pMem,0,sizeof(DEC_buf_aac));
    }
    return 0;
}




