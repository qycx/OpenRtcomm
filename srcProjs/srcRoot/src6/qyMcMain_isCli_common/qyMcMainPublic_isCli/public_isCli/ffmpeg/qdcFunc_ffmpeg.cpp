
#include	"stdafx.h"
#include	<tchar.h>
#include	<string>

#include	"qyMcMainCommon.h"
#include	"dumpAudio.h"

extern "C"
{
#include "libavutil/opt.h"
#include "libavcodec/avcodec.h"
#include "libavutil/imgutils.h"

//#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"

};




//
// Created by qycx on 2021/3/1.
//

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <string>

//
//#include "tmpFfmpegCommon.h"
#include	"qdc_ffmpeg.h"



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include "tmpFfmpegCommon.h"



  //
  int qdc_init()
  {
      avcodec_register_all();

      g_qdc.bDone_qdc_init = true;

      return 0;
  }

  int qdc_exit()
  {
      g_qdc.bDone_qdc_init=false;

      return 0;
  }

// need sync by mutex before called
int newQdcUnitIndex()
{
    int i;

    if ( g_qdc.m_pMems==NULL)return -1;

    for ( i=0;i<g_qdc.m_usMaxCnt;i++){
        if ( g_qdc.m_pMems[i].bUsed)continue;
        break;
    }
    if ( i==g_qdc.m_usMaxCnt)return -1;
    QDC_unit *pUnit=&g_qdc.m_pMems[i];
    //
    pUnit->bUsed=true;

    memset(&pUnit->encV_var,0,sizeof(pUnit->encV_var));
    memset(&pUnit->decV_var,0,sizeof(pUnit->decV_var));
    memset(&pUnit->encA_var,0,sizeof(pUnit->encA_var));
    memset(&pUnit->decA_var,0,sizeof(pUnit->decA_var));

    //
    memset(&pUnit->decBufs,0,sizeof(pUnit->decBufs));

    //
    return i;
}

// need sync by mutex before called
void freeQdcUnitIndex(int index)
{
    if ( g_qdc.m_pMems==NULL)return;
    if(index <0||index>=g_qdc.m_usMaxCnt)return;
    QDC_unit *pUnit=&g_qdc.m_pMems[index];

    //
    freeDecBufs(index);

    //
    pUnit->bUsed=false;

    // do clean

    return;
}

QDC_unit * getQdcUnitByIndex(int index)
{
    if ( g_qdc.m_pMems==NULL)return NULL;
    if(index <0||index>=g_qdc.m_usMaxCnt)return NULL;
    return &g_qdc.m_pMems[index];
}

//
int freeDecBufs(int index_qdcUnit)
{
    QDC_unit *pUnit = getQdcUnitByIndex(index_qdcUnit);
    if (!pUnit) return -1;
    int i;
    for ( i=0;i<pUnit->decBufs.maxCnt_decBufMems;i++){
        DEC_buf  *pMem=&pUnit->decBufs.mems[i];
        if ( pMem->pBuf) myfree(pMem->pBuf);
        memset(pMem,0,sizeof(DEC_buf));
    }
    return 0;
}






