

#ifndef  __QMCDYNBMP_H__
#define  __QMCDYNBMP_H__	//  {

__declspec(  dllexport  )  int  sndRetrieveDynBmpsReq_qmc(  MIS_CNT  *  pMisCnt,  BOOL  bRetrieveAll  );

//  2014/05/03
__declspec(  dllexport  )  int  sndRetrieveDynBmpsReqToMsgr_qmc(  MIS_CNT  *  pMisCnt,  BOOL  bNeedProgress,  unsigned  int  uiObjType,  BOOL  bRetrieveOne,  QY_MESSENGER_ID  *  pIdInfo_imGrp_conf,  BOOL  bAvConsole,  QY_MESSENGER_ID  *  pIdInfo_dst,  unsigned  int  *puiTranNo  );



#endif  //  }


