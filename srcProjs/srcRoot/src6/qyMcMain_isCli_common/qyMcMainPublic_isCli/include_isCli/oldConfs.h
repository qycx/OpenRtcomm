
#ifndef  __oldConfs_h__
#define  __oldConfs_h__		//  {

//
typedef  struct  __oldConfMem_t     {
                 int                iTaskId;
                 QY_MESSENGER_ID    idInfo_peer;
                 unsigned  int      uiElapseInms_lastRefreshed;
}        OldConfMem;

//
typedef  struct  __oldConfs_t       {
                 unsigned  short    usCnt;
                 OldConfMem         mems[5];
}        OldConfs;


//
int findOldRecvdConfActive(HWND  hTalk, int* piTaskId);


//
int findOldRecvdConfsActive(OldConfs* pOldConfs);


//
int findRecvdConfsActive(OldConfs* pOldConfs);



#endif  //  }

