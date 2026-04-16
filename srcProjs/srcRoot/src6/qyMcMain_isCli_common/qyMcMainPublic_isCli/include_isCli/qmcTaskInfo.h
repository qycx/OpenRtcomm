
#ifndef  __qmcTaskData_h__
#define  __qmcTaskData_h__

//
#include	"syncMtCnt.h"

//
#include	"qmcTaskPublic.h"
//
#include	"qmcVWall.h"
#include	"qmcStruct_defs.h"

//
#define		CONST_taskDataType_null					0
#define		CONST_taskDataType_conf					1
#define		CONST_taskDataType_transferFile			2


//


//
typedef  struct  __qmcTaskDataCommon_t				{
				 unsigned  int  uiType; 
				 
				 //
				 MIS_MSGU	msgU;				 
				 
}		 QMC_taskData_common;



//
typedef  struct  __dlgTalkVideoConferenceActiveMemFrom_t		{
				 //
				 AV_stream										avStream;
				 //
				 TCHAR											desc[128];
				 //
				 DWORD											dwLastTickCnt_aData;
				 DWORD											dwLastTickCnt_vData;
				 //
				 int											nTimes_tooLong;
				 
				 //
				 int											iHkStatus;			//  2023/05/04
				 //
				 unsigned  char									ucbNvr;

				 //
}		 DLG_TALK_videoConferenceActiveMemFrom;

//
typedef  struct  __dlgTalkVideoConference_t						{


				 //
				 unsigned  short								usMaxSpeakers;
				 unsigned  short								usCntLimit_activeMems_from;
				 DLG_TALK_videoConferenceActiveMemFrom			activeMems_from[MAX_conf_activeMems];
				 BOOL											bNeedRefresh_activeMems_from;
				 
				 //
				 struct											{
					 AV_stream									avStream;
					 //
					 TCHAR										desc[32];
				 }												requestingMems_from[MAX_conf_requestingMems];

				 //
				 //  Note: fromList 仅由界面使用。activeMems_from可以由其他线程使用
				 unsigned  short								usCntLimit_mems_from;							//  from
				 //
				 TASK_AV_FROM								*	pMems_from;
				 //
				 unsigned  int									uiTranNo_lastModified_pMems_from;				//  if  dwTickCnt_lastModified_pMems_from is not the same as the value is myTask, then the pMems_from will be retrieved from myTask...
				 BOOL											bNeedRefresh_fromList;							//  2015/02/17
				 
				 //
				 ConfLayoutParam								confLayoutParam1;								//  2023/10/13

				 //
}		DLG_TALK_videoConference;



//
//
typedef  struct  __confMem_t						{
				 QY_MESSENGER_ID					idInfo;

				 //
				 struct								{
					 unsigned  int					uiTranNo_retrieve;
					 DWORD							dwTickCnt_toRetrieve;
					 //
					 QIS_res_obj					mem;
				 }									dynBmps;

				 //
				 struct								{
					 struct							{
						 TALKER_dynBmp				talkerDynBmp;
						 DWORD						dwTickCnt_start;
						 //
						 //DWORD						dwTickCnt_lastRefreshed1;
						 //
						 //int						nTries_toView;				//  
					 }								mem;
				 }									view;


}		 CONF_mem;





//
#define		CONST_taskRespInfoMemState_null									0
//
#define		CONST_taskRespInfoMemState_join									1
#define		CONST_taskRespInfoMemState_leave								2
//
#define		CONST_taskRespInfoMemState_ok									3
#define		CONST_taskRespInfoMemState_warning								4
#define		CONST_taskRespInfoMemState_notInConf							5
//
#define		CONST_taskRespInfoMemState_offline								10

//
extern  QY_DMITEM  CONST_taskRespInfoMemStateTable[];


//
typedef  struct  __confLog_t										{
				 int												iState;
				 time_t												tTime;
}		 CONF_log;


//
typedef  struct  __confStat_t										{
				 time_t												tTime_join;
				 time_t												tTime_leave;
				 //
				 int												iTimeInS_inConf;
				 //
}		 CONF_stat;


//
typedef  struct  __confLogs_t										{
				 unsigned  short									usCnt;
				 CONF_log											mems[10];

				 //
				 CONF_stat											stat;

}		 CONF_logs;

//
typedef  struct  __taskRespInfoMem_t								{
				 
				 //
				 QY_MESSENGER_ID									idInfo;

				 //
				 struct												{

					 //
					 struct											{
						 //
						 time_t										tRecvTime_lastResp;							//  2009/09/11
					 }												avReply;
					 //
					 struct											{
						 //
						 time_t										tRecvTime_lastResp;							//  2009/09/11
					 }												taskProcReq_cancel;


					 //
					 struct											{
						 time_t										tSelectTime;
					
						 unsigned  int								uiCnt_pkts_fromSelect;						//  ´tSelectTime
						 int  										iDiff_pkts_fromSelect;
					 
						 unsigned  short							usDelay;									//  
						 time_t										tRecvTime_lastResp;							//  2009/09/11
					 }												audio;
					 				
					 //				 
					 struct											{
						 time_t										tSelectTime;
					
						 unsigned  int								uiCnt_pkts_fromSelect;						//  ´tSelectTime
						 int  										iDiff_pkts_fromSelect;
					 					
						 unsigned  short							usDelay;									//  
					 	 time_t										tRecvTime_lastResp;							//  2009/09/11
						 
						 //
						 struct										{
							 QY_MESSENGER_ID						idInfo;
							 unsigned  int							uiTran_openAvDev;
							 
							 time_t									tSelectTime;
							 //
							 unsigned  int							uiCnt_pkts_fromSelect;						//  ´tSelectTime						 
							 unsigned  int							iDiff_pkts_fromSelect;

							 time_t									tRecvTime_lastResp;
						 }											lastErr;

		
				 	 }												video;
		

					 //				
					 unsigned  short								usState_byDlgTalk;					
					 DWORD											dwLastModifiedTickCnt_usState;
											
					 //					
					 BOOL											bNeedCalc_byProcTaskDataResp;

					 //
					 CONF_logs										logs;

				 }													var;

}		 TASK_respInfo_mem;

//  comments
//  procTaskVideoDataResp计算出iState, 如果与istate_byDlgTalk不符，那么设置taskRespInfoMem里的bNeedCalc
//  然后再设置taskRespInfo里的bNeedCalc
//  dlgTalk.timer, 发现taskRespInfo里的bNeedCalc,就去遍历所有的mems
//  发现taskRespInfoMem里的bNeedcalc, 就去计算iState. 然后清除mem.bNeedcalc.再清除respInfo.bNeedCalc
//  dlgTalk在某个时间，会遍历计算所有的mems,因为在客户端离线后，就不会自动计算了。

//
#define		MAX_taskRespInfoMems								360


//  2017/09/06
typedef  struct  __task_respInfo_t  							{
				
				 unsigned  short								usCnt;				
				 TASK_respInfo_mem								mems[MAX_taskRespInfoMems];									//  2009/09/11. mems_to[3];
				 
				 //
				 BOOL											bNeedCalc_byProcTaskDataResp;
				 
}		TASK_respInfo;


//
__declspec(  dllexport  )  TASK_respInfo  *  get_respInfo(  void   *  pProcInfoParam,  int  index_taskInfo  );




//
//
__declspec(  dllexport  )  int __cdecl bCmp_respInfoMem(const void *key, const void *pMem);


//
typedef  struct  __qmcTaskData_conf_t							{
				 QMC_taskData_common							common;

				 //
				 BOOL											bInited;

				 //
				 struct											{
					 QY_MESSENGER_ID							idInfo_initiator;
				 }												grp;

				 //
				 DLG_TALK_videoConference						videoConference;
				 
				 //  2023/01/24
				 unsigned  char									ucb2Streams;

				 //
				 unsigned  char									ucbNotSendData;												//  2009/02/22
				 
				 //
				 struct											{
					 bool										bTaskExists;
					 int										index_sharedObj;
					 //
				 }												shareScreen;

				 //
				 struct {
					 bool										bTaskExists;
					 int										index_sharedObj;
					 //
				 }												shareMediaDevice;

				 
				 //
				 unsigned  short								usCnt_pMems;
				 CONF_mem						*				pMems;											//  是否显示的状态应该存在qmcWallMem里
				 
				 //
				 unsigned  short								usMaxToDisplay;
				 unsigned  short								usPollingIntervalInS;							//  每一个批次显示的时间.

				 //
				 struct											{
					 unsigned  short							usStartMemIndex;								//  cur表示当前正试图显示，每次都从iStartMemIndex开始。一共显示maxToDisplay个. 		
					 unsigned  short							usCnt;
					 DWORD										dwTickCnt_adjustWhichToBeDisplayed;				//  试图显示的操作时刻

					 //
					 DWORD										dwTickCnt_chkIfActive;

				 }												cur_toDisplay;

				 //
				 bool											bResizeToPlay;
				 				
				 //
}		 QMC_taskData_conf;


typedef  struct  __qmcTaskData_transferFile_t	{
				 QMC_taskData_common	common;

				 //
				 //BOOL					bInited;

				 //
				 DWORD												dwStartTickCnt;						//  
				 DWORD												dwLastReportTickCnt;				//  


}		 QMC_taskData_transferFile;


//
void  *  newQmcTaskData(  unsigned  int  uiType  );
void  freeQmcTaskData(  void  *  p  );


//  2014/09/24
struct  __qmcTaskInfo_t											{
				 BOOL											bUsed;

				 //
				 struct											{
					 DWORD										dwTickCnt_start;
					 //
					 DWORD										dwTickCnt_recv_lastRefreshed;		// 最新收到数据的时刻,或者其他被更新状态的时刻
					 //
					 HWND										hWnd_task;
					 //
					 int										iTaskId;	

					 //
					 bool										m_bReplyTask;

					 //				 
					 BOOL										bTaskInvalid;								//  2009/09/14
					 //
					 BOOL										bNeedRemoved;								//  2015/09/08
					 					 					 
					 //
					 bool										bClosed;

					 //
					 QMC_taskData_common				*		pTaskData;

					 //
					 ROUTE_sendLocalAv							curRoute_sendLocalAv;						//  2014/10/29

					 //
					 TASK_respInfo								taskRespInfo;



					 //

				 }												var;


};



//
//
BOOL  isMemFromActive(  DLG_TALK_videoConference  *  pDLG_TALK_videoConference,  QY_MESSENGER_ID  *  pIdInfo_from,  RES_obj_simple  *  pResObj_from,  int  *  pIndex_activeMems_from  );

BOOL  isVideoActive(  MIS_CNT  *  pMisCnt,  DLG_TALK_videoConference  *  pVc,  QY_MESSENGER_ID  *  pIdInfo_from,  unsigned  int  tn_video,  int  *  pIndex_activeMems_from  );


int  addTo_activeMems_from(  MIS_CNT  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo,  AV_stream_simple  *  pAss,  DLG_TALK_videoConference  *  pVc  );
int  removeFrom_activeMems_from(  MIS_CNT  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo,  AV_stream_simple  *  pAss,  DLG_TALK_videoConference  *  pVc  );



//  
BOOL  isMemFromRequesting(  DLG_TALK_videoConference  *  pVc,  QY_MESSENGER_ID  *  pIdInfo_from  );

int  addTo_requestingMems_from(  MIS_CNT  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo,  LPCTSTR  talkerDesc,  DLG_TALK_videoConference  *  pVc  );


//
__declspec(  dllexport  )  int  procBgWallMem(  HWND  hDlgTalk,  void  *  pDLG_TALK_var,  CONF_mem  *  pConfMem,  myZONE  *  pZone  );


#endif

