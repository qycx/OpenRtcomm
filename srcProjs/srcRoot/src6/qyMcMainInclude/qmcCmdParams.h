
#ifndef  __qmcCmdParams_h__	//  
#define  __qmcCmdParams_h__	//  {

//  2011/05/30
typedef  struct  __qmcAppParams_t								{

				 //  appObjPrefix= "qm"  +  iSeqNoSelected_appObjPrefix. 2014/02/10
				 TCHAR											appObjPrefix[32];
				 //
				 int											iSeqNoSelected_appObjPrefix;	//  
				 //  2015/02/01
				 int											tn_cliPipe;						//  2015/02/02
				 
				 //
				 char											serverAddr[64];
				 int											port;

				 //
				 TCHAR											usrName[64];						//  2014/02/10
				 TCHAR											passwd[64];

				 //
				 TCHAR											rtspUrl[128];					//  2014/12/12


				 //  2015/04/28
				 unsigned  char									ucbNoDvt;						//  2015/04/28
				 unsigned  char									ucbNoEvt;						//  2015/10/28

				 //  2016/04/26
				 unsigned  char									ucbDbgDvt;						//  2016/04/26
				 unsigned  char									ucbDbgEvt;						//  2016/05/05
				 //
				 unsigned  char									ucbDbgOnvif;					//  2016/0


				 //  2015/07/18
				 int											iTestNo;
				 

				 //
				 bool											bMcu;
				 //				 	
				 QY_MESSENGER_ID								idInfo_mcu;

				 //
				 bool											bService;

				 //
				 bool											bConfServer;
				 //
				 bool											bFileServer;

				 //
				 bool											bUseMachineKey;
				 bool											bUseAuthTypeMcu;
				 unsigned  char									ucbNotNeedLocked;							//  

				 //
				 bool											canStartConf;
				 bool											bNoPrompt_mfc;
				 bool											bNoAcceptAv;

				 //
				 bool											bInSilence;
				 bool											bNoAec;

				 //
				 bool											bNoDrawDibDraw_forConfServer;

				 //  2015/10/04
				 unsigned  short								usPktResType_suggested;


				 //
				 bool											bUse_forTest_defaultAvLevel_240p;
				 //
				 //bool											bUse_forTest_useNv;
				 bool											bUse_forTest_noLocalAv;
				 
				 //
				 bool											bUse_forTest_mediaDivceAsScreen;

				 //
				 bool											bUse_forTest_fakePic;

				 //
				 bool											bUse_decD3d_nv;
				 //
				 bool											bUse_encD3d_nv;

				 //
				 unsigned  char									ucb2Streams_forDbg;
				 //
				 int											conf_iFourcc_forDbg;
				 unsigned  char									ucHardwareAccl_forDbg;
				 //
				 int											iMeetingLevel_forDbg;
				 bool											bRecord_forDbg;

				 //
				 bool											bSmZy;  
				 
				 //
				 bool											bUse_playDev_dummy;			//  

				 //
				 bool											bUse_urgentDbg;				//  urgent debugging

				 //
				 bool											unused_bUse_dbgDetail;				//  2026/04/08

				 //
				 bool											bTest_stepByStep;			//  设置测试的步骤，设置为true时，在release版本也可以测试运行. 2026/04/13

				 //
}		 QMC_APP_PARAMS;


//
#ifdef  __cplusplus
extern  "C"  {	
#endif

__declspec(  dllexport  )  int  parseCmdLine_qyMc(  LPCTSTR  pCmdLine,  QMC_APP_PARAMS  *  pParams  );
__declspec(  dllexport  )  int  parseCmdLine_qmc_func(  LPCTSTR  pCmdLine,  QMC_APP_PARAMS  *  pParams  );

//
int  doPre_createConsoleWall(  void  *  p0,  void  *  p1,  void  *  p2  );	


#ifdef  __cplusplus
}
#endif


#endif  //  }


