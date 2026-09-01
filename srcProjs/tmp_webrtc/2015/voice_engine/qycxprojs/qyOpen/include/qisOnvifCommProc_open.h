

#ifndef  __qisOnvifCommProc_open_h__
#define  __qisOnvifCommProc_open_h__	//  {

//
#include	"qisMsg_open.h"


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
typedef  struct  __onvifMsg_ptz_t			{
				 M_onvifMsgCommon_mems
				 //
				 char						deviceServiceAddr[256];
				 //
				 unsigned  char				ucCmd;

}		 OnvifMsg_ptz;




#endif


