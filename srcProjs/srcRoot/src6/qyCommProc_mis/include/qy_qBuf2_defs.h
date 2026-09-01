
#ifndef  __qy_qBuf2_defs_h__
#define  __qy_qBuf2_defs_h__  //  {


//
#include    "qnmCommProc.h"
#include    "qnmCommProc_mis.h"


 //
typedef  struct
 {
    Tmp_qBuf_memHead    common;

     TRANSFER_AUDIO_dataMemHead dataMemHead;
 }Tmp_qBuf_memHead_decA;

//
 typedef struct 
 {
     uint uiPts;         //  2017/10/13
     uint uiSize_dec;     //  2017/10/13
 }  HeadData_playA;

 typedef  struct  
 {
     Tmp_qBuf_memHead   common;

     HeadData_playA headData;
 }Tmp_qBuf_memHead_playA;

 //
 typedef struct
 {
     int len_showInfo;

 }HeadData_showInfo;

 //
 typedef  struct   
 {
     Tmp_qBuf_memHead   common;

     HeadData_showInfo headData;
 }Tmp_qBuf_memHead_showInfo;



#endif  //  }


