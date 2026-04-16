
#ifndef  __qmcDebugStatusInfo_h__
#define  __qmcDebugStatusInfo_h__		//  

#include "../../qyInclude/qyCommon/qyObjs.h"


//
typedef  struct  __qmc_debugStatusInfo_t								{															//  2009/02/27
						 unsigned  char									ucbViewAudioStatus;
						 unsigned  char									ucbViewVideoStatus;											//  2009/04/16
						 unsigned  char									ucbViewFileStatus;
						 //
						 unsigned  char									ucbViewIoStatus;											//  2009/04/16
						 //
						 unsigned  char									ucbViewMgrStatus;											//  2017/10/11
						 //
						 unsigned  char									ucbPrint_a_in;												//  2010/06/25
						 unsigned  char									ucbPrint_a_out;
						 unsigned  char									ucbPrint_v_in;
						 unsigned  char									ucbPrint_v_out;
						 //
						 unsigned  char									ucbPrint_v_draw;											//  2010/09/12
						 //
						 unsigned  char									ucbPrint_a_mt;												//  2013/03/21
						 //
						 unsigned  char									ucbShowVideoCapStatus;										//  2012/11/11
						 unsigned  char									ucbShowAudioCapStatus;										//  2012/11/11
						 //
						 unsigned  char									ucbShowPreDrawStatus;										//  2012/01/26
						 unsigned  char									ucbShowToDrawStatus;										//  2012/01/26
						 //
						 unsigned  char									ucbShowRenderStatus;										//  2015/10/07
						 //
						 unsigned  char									ucbShowPlayAudioStatus;										//  2012/11/11
						 //
						 unsigned  char									ucbShowVPktInputInfo;										//  2012/03/16
						 unsigned  char									ucbShowEncVStatus;											//  2014/06/23
						 //
						 unsigned  char									ucbShowDec_pipeStatus;										//  2016/04/13
						 //
						 unsigned  char									ucbShowPreDecV_pts;											//  2015/06/18
						 unsigned  char									ucbShowPreDecAStatus;										//  2015/09/11
						 unsigned  char									ucbShowPreDecVStatus;										//  2014/06/23
						 unsigned  char									ucbShowPostDecAStatus;										//  2015/09/11
						 unsigned  char									ucbShowPostDecVStatus;										//  2014/06/23
						 //
						 unsigned  char									ucbShowDec_sharedTexStatus;									//  2016/04/08
						 //
						 unsigned  char									ucbPrint_rtt;												//  2014/11/26
						 //
						 unsigned  char									ucbPrint_d3d;												//  2014/12/09
						 //
						 unsigned  char									ucbShowDlgTalkStatus;										//  2012/05/25
						 
						 //
						 unsigned  char									ucbShow_onvif;												//  2016/07/31
						 unsigned  char									ucbPrint_ptz;												//  2015/09/19

						 //
						 unsigned  char									ucbShowRtspCliControl;										//  2014/03/23

						 //
						 unsigned  char									ucbPrint_rtsp;												//  2014/09/29

						 //
						 unsigned  char									ucbDebugSubtitle;											//  2014/11/07
						 unsigned  char									ucbDebugIa;													//  2014/11/30
						 //
						 unsigned  char									ucbDebug_newMsgArrives;										//  2014/12/03
						 unsigned  char									ucbDebug_fillData_d3d;										//  2014/12/03
						 //
						 unsigned  char									ucbDebug_d3d_touch_contains;								

						 //
						 bool											bMon_decV;
						 bool											bMon_encV;

						 //
						 //#define		CONST_fn_dump_h264_enc			"dump_h264_enc.264"
						 #define		CONST_fn_dump_h265_enc			"d:\\tttbbb\\124\\dump_h265_enc.265"
						 unsigned  char									ucb__Dump_h265_enc__;										//  2014/03/30

						 //
						 #define		CONST_fn_dump_h265_dec			"d:\\tttbbb\\124\\dump_h265_dec.265"
						 unsigned  char									ucb__Dump_h265_dec__;										//  2014/03/30

						 //
						 #define  CONST_dump_dir						"d:\\tttbbb\\124\\"
						 
						 //
						 unsigned  int									tn_dumpAv;

						 //
						 #define		CONST_fn_dump_mic_pcm			"mic.pcm"
						 unsigned  char									ucb__Dump_mic_pcm__;

						 //
						 #define		CONST_fn_dump_mp3_enc			"c:\\tttbbb\\test\\dump_mp3_enc.mp3"
						 unsigned  char									ucb__Dump_mp3_enc__;
						 
						 //
						 unsigned  char									ucb__Dump_mp3_dec__;

						 //
						 #define	CONST_fn_dump_deced_pcm				"deced.pcm"
						 unsigned  char									ucb__Dump_deced_pcm__;

						 //
						 bool											bDbg_use_dsound_toPlay;

						 //
						 unsigned  char									ucb_draw_talkers_frm;								//  2016/06/02
						 unsigned  char									ucb_draw_walls_frm;

						 //
						 unsigned  char									ucb_noSlave;

						 //
						 unsigned  char									bDbgDetail;
						 //
						 unsigned  char									bDbgDetail_playA;
						 unsigned  char									bDbgDetail_playV;
						 //
						 unsigned  char									bDbgDetail_saveAv;
						 //
						 unsigned  char									bDbgDetail_switch_a;								//  audio的交换过程
						 unsigned  char									bDbgDetail_switch_v;								//  video的交换过程

						 //
						 unsigned  char									ucbPrint_triggerD3d;

						 //
						 unsigned  char									ucbPrint_lPktId_alloc;
					 
						 //
						 unsigned  char									bDbg_startToBreak;									//  2026/04/13. 编程设置某特定debug条件

}		QMC_debugStatusInfo;



//
void debugStatusInfo_OnIsCmd(  UINT nID,  QY_ENV  *  pEnv,  QMC_debugStatusInfo  *  pDebugStatusInfo  );
void  debugStatusInfo_OnUpdateIsCmd(QY_ENV  *  pEnv,  QMC_debugStatusInfo  *  pDebugStatusInfo,  void *pCmdUIParam);


#endif  //  }


