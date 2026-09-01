
#ifndef  __qmcStatus_h__
#define  __qmcStatus_h__	//  {

//
#include	"imNetStat.h"


//  2015/01/21
struct  __qmcStatus_t									{
					 unsigned  long								ulbThreadProcInited:1;										//  mcThreadProc_mis 2007/09/02
					 //
					 unsigned  long								ulbMgrQuit:1;												//  
					 unsigned  long								ulbDisplayQuit:1;											//  display
					 unsigned  long								ulbWorkQuit:1;												//  work
					 unsigned  long								ulbSchedulerQuit:1;											//  scheduler
					 unsigned  long								ulbRobotQuit:1;												//  svr
					 unsigned  long								ulbMediaQuit:1;												//  media
					 unsigned  long								ulbRealTimeMediaQuit:1;										//  realTimeMedia
					 unsigned  long								ulbRtOpQuit:1;												//  2016/12/26
					 unsigned  long								ulbLogQuit:1;												//  log
					 
					 //
					 struct										{
						 unsigned  long							ulbImGrpExists:1;											//  ??????????2011/04/10.
						 unsigned  long							ulbContactExists:1;											//  ?????contact??
						//
						unsigned  long							ulbAllContactsRetrieved:1;									//  ??????????. 2013/08/01
						//
						unsigned  short							nTimes_refresh;												//  ??access????,??,??????????,?????????. ??3?
						DWORD									dwTickCnt_lastRefreshed;
					 }											retrieveImObjList;

					 //
					 struct										{
						 DWORD									dwTickCnt_start;
						 DWORD									dwTimeInMs;
					 }											waitToQuit;													//  2011/02/02

					 //
					 DWORD										dwTickCnt_toStat;											//  2009/10/11
					 //
					 struct										{											 				//  for cpu usage. 2009/10/10
						 LARGE_INTEGER							oldIdleTime;
						 LARGE_INTEGER							oldKernelTime;
						 LARGE_INTEGER							oldUsrTime;
						 //
						 DWORD									dwTickCnt_start_ce;
						 DWORD									dwIdleTime_start_ce;
						 //
						 int									iCpuUsage;
					 }											cpu;
					 IM_NET_STAT								netStat;													//  2009/10/10
					 MEMORYSTATUS								memory;														//  201007/28

					 //
					 struct										{
						 DWORD									dwTickCnt_lastDisplayed;
						 TCHAR									tBuf[256];					 
						 int									len;
					 }											notification;

					 //  2010/08/14
					 struct										{
						 HWND									hWnd;
						 unsigned  int							uiTranNo;
						 //
						 unsigned  char							ucbProgessEnd;
						 int									nResult;
						 //
					 }											progress;
					 BOOL										bInSequence_showDlgProgress;			//  2014/05/07

					 //  2012/03/25
					 long										nThreads_dec;
					 long										nThreads_dispatch;						//  2013/08/26
					 long										nUsed_players;
					 long										nThreads_aTrans;						//  2014/03/15
					 long										nThreads_vTrans;						//  2014/03/15
					 long										nThreads_talkerProc;					//  2016/03/15
					 long										nThreads_shareDynBmps;					//  2016/06/15

					 //  2013/03/07
					 DWORD										dwTickCnt_chkDb;
					 
					 //  2013/07/19
					 struct										{
						 int									xPos_screen;  
						 int									yPos_screen;
						 //
						 HWND									hParent_ia;								//  2012/05/03					
						 //
					 }											param_viewInstantAssistant;						

					 //  2014/02/04
					 struct                          			{
						 struct									{
							 int								xPos;  
							 int								yPos;
							 //
							 DWORD								dwLastTickCnt;
						 }										mousemove,  lButtonDown,  command;
						 //  2016/01/15
						 struct									{
							 BOOL								bSetCaptured;
							 unsigned  int						uiTranNo_wm;
							 
							 //
							 RECT								bgScreenRect_wm;
							 
							 //
							 int								sx_mouse,  sy_mouse;


						 }										SetCapture;
						 //
					 }											param_d3dWall;

					 //  2014/02/11
					 struct										{
						 int									uiQNodes_displayedObjQ;
					 }											display;								//  thread_display???.
					 //  2014/05/27
					 struct										{
						 int									maxiTotal;
						 int									nTotal;
					 }											hashTbl_leftView_db;

					 //  2014/12/22
					 struct										{
						 BOOL									bFailed_newSharedObj;
					 }											sysErr;

					 //  2015/06/18
					 struct										{
						 TRANS_pts_info							transPtsInfo_sum;
						 TRANS_pts_info							transPtsInfo_sum_last;
						 //
						 BOOL									bTooManyPtsErr;
						 unsigned  char							ucCnt_bTooManyPtsErr;
						 DWORD									dwTickCnt_lastModified_bTooManyPtsErr;
						 //
						 BOOL									bWarning;

					 }											ptsStat;
				 
};






#endif  //  }