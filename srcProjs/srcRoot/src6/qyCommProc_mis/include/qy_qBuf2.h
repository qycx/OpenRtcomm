

#ifndef  __qy_qBuf2_h__
#define  __qy_qBuf2_h__		//  {

//
#include    "myTypes.h"

//
#include    "qyq2.h"
//#include    "qnmCommProc.h"
//#include	"qnmCommProc_mis.h"



//
typedef  struct 
{
    int m_qType;

    uint uiMaxQNodes;
    int maxDataBufLen;        //  

    //
    bool b_showInfoQ;
} Tmp_qBuf_cfg;


typedef struct 
{
    int m_qType;

    //
    uint uiMaxQNodes;

    //
    RW_lock_param rwLockParam_syncFlg;

}   Tmp_qBuf2_cfg;


//
typedef struct 
{
}Tmp_qBuf_memHead;




 //
 class QY_qBuf {

 public:

     //
     Tmp_qBuf_cfg cfg;
     TCHAR name[128];

     //
     void* memHeads;

     //
     atbyte* pBuf;

     //
     int startIndex_memHead;
     int uiQNodes;

     //            
     int startPos_data;
     int dataLen;

     //
     //
     bool bNeedSync;

     //CRITICAL_SECTION cs;
     //BOOL bCsInited;

#if 0
     SYNC_OBJ_PARAM syncObjParam;
     HANDLE hMutex;
#endif
     TCHAR   mutexName[64];

     //
 public:
	 QY_qBuf();


	 //
     bool is_QFull();
     bool is_QWarning(int uiQNodes_warningInterval);
     bool is_QEmpty();

     //
     int init(int qType, uint uiMaxQNodes, int maxDataBufLen, bool bAlloc, LPCTSTR name);
     void exit();
     int alloc(int maxDataBufLen);
     void dofree();
     int qPostMsg(void* pHeadData, void* pQElem0, uint size);
     int tmp_qGetMsg(void* pHeadData, void* pQElem, uint* puiSize, bool bNotShowInfo);
     int qGetMsg(void* pHeadData, void* pQElem, uint* puiSize);


 };

 //
 class QY_qBuf2
 {
 public:
     //
     Tmp_qBuf2_cfg cfg;
     TCHAR  name[128];

     //
     bool bFlag_toPostMsg_q1;
     CMutexRW* pRw_syncFlg;

     //
     TCHAR											mutexName_syncR[64];

     //
     uint dwTickCnt_lastData;

     //

     //
     QY_qBuf qs0, qs1;

     //
     HANDLE hEvent0;

	 //
	 QY_qBuf2();


     //
     int initQyQ2(int qType, uint uiMaxQNodes, int maxDataBufLen, RW_lock_param pRwLockParam_syncFlg, bool bAlloc, LPCTSTR name);
     void exitQyQ2();
     int alloc(int maxDataBufLen);
     void dofree();
     bool is_Q2Warning(int uiQNodes_warningInterval);
     bool is_Q2Empty();
     int q2PostMsg(void* pHeadData, void* pQElem, uint size,  LPCTSTR  hint );
     int q2PostMsgAndTrigger(void* pHeadData, void* pQElem, uint size,  LPCTSTR  hint );
     int q2GetMsg(void* pHeadData, void* pQElem, uint* puiSize,  LPCTSTR  hint);
     int get_Q2Nodes();






 };






#endif  //  }


