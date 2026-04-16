

#ifndef  __qmcVideoTool_h__
#define  __qmcVideoTool_h__	//  {


//
int  toShareVideo_post_qmc(  MC_VAR_isCli  *	pProcInfo,		unsigned  int  uiCapType,  int  iIndex_capProcInfo,  myDRAW_VIDEO_DATA  *  pkts,  unsigned  int  nPkts,  COMPRESS_VIDEO  *  pCompressVideo,  QY_SHARED_OBJ  *  pSharedObj,  MIS_MSGU  *  pMsgBuf  );


//
//  2015/01/19
int  doDecodeVideo_dvtCli(  QY_TRANSFORM  *  pTransform,  int  index_pMems_from,  unsigned  int  uiModuleType_toDec,  MIS_MSGU  *  pMsgBuf  );


//
int  qdcInitCompressVideo_evtCli(  void  *  pVideoCompressorCfg_reserved,  QY_VIDEO_HEADER  *  pVh_decompress,  QY_VIDEO_HEADER  *  pVh_compress,  unsigned  int  uiModuleType,  QDC_OBJ_INFO  *  pQdcObjInfo  );
int  qdcExitCompressVideo_evtCli(  QDC_OBJ_INFO  *  pQdcObjInfo  );
int  qdcGetSpsPps_evtCli(  QDC_OBJ_INFO  *  pQdcObjInfo,  char  *  spsBuf,  unsigned  int  *  puiSpsSize,  char  *  ppsBuf,  unsigned  int  *  puiPpsSize,  char  *  vpsBuf,  unsigned  int  *  puiVpsSize  );

//
int  doEncodeVideo_evtCli_run(  MC_VAR_common  *  pProcInfo,  CAP_procInfo_bmpCommon  *  pCapProcInfo,  void  *  pMIS_CNT,  MIS_MSGU  *  pMsgBuf  );



#endif  //  }



