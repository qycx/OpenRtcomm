

#ifndef  __qisOnvifCommProc_open_h__
#define  __qisOnvifCommProc_open_h__	//  {

//
#include	"qisMsg_open.h"
#include	"..\\qyVDev_open\\include\\qyPtz_open.h"


//
#define		CONST_mtxName_syncOnvifMsgBuf	_T(  "SyncOnvifMsgBuf"  )



//
//
#define		MAX_rtspUrlLen								256

//
//
typedef  struct  __rtspUrl_t							{
				 char									url[MAX_rtspUrlLen  +  1];	
}		 RTSP_url;


//
#define		CONST_onvifMsg_subtype_null					0
//
#define		CONST_onvifMsg_subtype_quit					3
//
#define		CONST_onvifMsg_subtype_discovery			11
#define		CONST_onvifMsg_subtype_probe				12
//
#define		CONST_onvifMsg_subtype_ipCams				20
//
#define		CONST_onvifMsg_subtype_ptz					30				//  2016/07/20
#define		CONST_onvifMsg_subtype_nvrControl			31
//
#define		CONST_onvifMsg_subtype_dbg					40


//
#define		CONST_onvifMsg_subtype_ping					100
#define		CONST_onvifMsg_subtype_close				101
//
#define		CONST_onvifMsg_subtype_nvrInfo				110




//
#define		M_onvifMsgCommon_mems			unsigned  int	uiType;  	\
											int				iSubtype;	\
											int				iUsage;		\
											unsigned  char  ucbResp;	\
											unsigned  char	ucbDbg;		\
											unsigned  int	uiTranNo;	\
											int				iErrCode;

//  
//  iErrcode valid if ucbResp is true. 2016/08/03
//


//
typedef  struct  __onvifMsgCommon_t		{
		 M_onvifMsgCommon_mems			
}	 OnvifMsg_common;


//
//
typedef  struct  __onvifMsg_quit_t	{
				 M_onvifMsgCommon_mems			
}		 OnvifMsg_quit;



//
typedef  struct  __onvifMsg_discovery_t	{
				 M_onvifMsgCommon_mems			
}		 OnvifMsg_discovery;


//
typedef  struct  __onvifMsg_probe_t			{
		 M_onvifMsgCommon_mems			
		 //
		 char  								uri[256];
}	 OnvifMsg_probe;


//
typedef  struct  __onvif_url_t				{
				 char						token[64];
				 RTSP_url					rtspUrl;
}		 Onvif_url;

//
typedef  struct  __onvif_ipCam_t			{
				 char						ip[15  +  1];
				 //
				 Onvif_url					urls[3];
				 //		 
				 char						deviceServiceAddr[256];		 
				 //
}	 Onvif_ipCam;


//
typedef  struct  __onvifMsg_ipCams_t		{
				 M_onvifMsgCommon_mems
				 //
				 unsigned  short			usCnt;
				 Onvif_ipCam				mems[8];
}		 OnvifMsg_ipCams;



//
#define		CONST_mouseStatus_lBtnDown			1
#define		CONST_mouseStatus_lBtnUp			2


//
typedef  struct  __onvifMsg_ptz_t						{
				 M_onvifMsgCommon_mems
				 
				 //
				 char									deviceServiceAddr[256];
				 //
				 int									iChannel;

				 //
				 unsigned  char							ucCmd;
				 //
				 unsigned  char							ucMouseStatus;

				 //
				 PTZ_cmdParamU							paramU;

				 //
}		 OnvifMsg_ptz;



//
#define		CONST_nvrControlCmd_selectChannel			1		//  


//
typedef  struct  __onvifMsg_nvrControl_t				{
				 M_onvifMsgCommon_mems
				 //
				 unsigned  short						usCmd;
				 //
				 int									iChannel;

}		 OnvifMsg_nvrControl;



//
typedef  struct  __onvifMsg_dbg_t {
				 M_onvifMsgCommon_mems

				 char  buf[128];

}		 OnvifMsg_dbg;


#endif





