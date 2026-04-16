

#ifndef  __rtspUsrData_h__
#define  __rtspUsrData_h__	//  {


//
#define		CONST_rtspUsrDataType_null				0
#define		CONST_rtspUsrDataType_commInfo			1
#define		CONST_rtspUsrDataType_info				2
#define		CONST_rtspUsrDataType_resp				3
//
#define		CONST_rtspUsrDataType_encData			4		//  2015/10/16


//
typedef  struct  __rtspUsrData_common_t				{
				 unsigned  int						uiType;
}		 RTSP_usrData_common;


//
typedef  struct  __rtspUsrData_commInfo_t			{
				 unsigned int  						uiType;
				 //
				 BOOL								bShmReady;
}		 RTSP_usrData_commInfo;


//  2015/01/30. dvt从管道里直接发给decodeVideo_tool
//  Note: decodeVideo_tool发送的是rtsp_msg.
//		  接收的是rtsp_usrData_resp
//		  decodeVideo_tool发送一个特殊的消息给dvt. 那么就取消响应，只接收
//		  缺省时，一发一收
typedef  struct  __rtspUsrDataResp_t				{
				 unsigned  int						uiType;
				 //
				 BITMAPINFOHEADER					bih_dec;
				 //
				 double								dFrameRate;
				 //
				 BOOL								bShmOpen;

				 //
#ifdef  __DEBUG__
				 char								buf[1024  *  1024];
#endif
}		 RTSP_usrData_resp;


//
typedef  struct  __rtspUsrData_info_t				{
				 unsigned  int						uiType;
				 //
				 int								kk;

}		 RTSP_usrData_info;





#endif  //  }


