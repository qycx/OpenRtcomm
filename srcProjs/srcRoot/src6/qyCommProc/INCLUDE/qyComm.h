

#ifndef  __QYCOMM_H__
#define  __QYCOMM_H__	/*  {  */

 //  严重警告：
 //		 这里的定义禁止修改
 //

#include	"ancCommProc_open.h"


 //  all service_ids
//  #define		CONST_qyServiceId_rasMonoring			ASR_SERVICE_RAS_MONITORING
#define		CONST_qyServiceId_base					10						// service_id的基数
//  #define		CONST_qyServiceId_imc					(  CONST_qyServiceId_base  +  1  )
#define		CONST_qyServiceId_netMc					(  CONST_qyServiceId_base  +  2  )		//  2007/03/31
#define		CONST_qyServiceId_qwm					CONST_qyServiceId_netMc
//  #define		CONST_qyServiceId_internetMgr			(  CONST_qyServiceId_base  +  110  )
#define		CONST_qyServiceId_is					(  CONST_qyServiceId_base  +  120  )	//  2007/03/07
#define		CONST_qyServiceId_mis					CONST_qyServiceId_is
//
#define		CONST_qyServiceId_showInfo				(  CONST_qyServiceId_base  +  130  )


 //  命令码, !!! 严重警告：以下命令码，只能添加，不能修改，以避免出现各产品不兼容的局面
 //			 类型：unsigned  short
 //			 低端保留：
#define		CONST_qyCmd_tellService					0								//  "启动服务"
#define		CONST_qyCmd_end							255								//  "结束会话"


 //			 用户定义:
#define		CONST_qyCmd_base							2000	//  2048
 //					  其他定义在qyCommProc.h中，须>CONST_qyCmd_base大，<CONST_qyCmd_upReserved

 //			 高端保留：
#define		CONST_qyCmd_upReserved					(  (  unsigned  short  )0xe000  )	//  57344
#define		CONST_qyCmd_update						(  (  unsigned  short  )0xe001  )
#define		CONST_qyCmd_getFile						(  (  unsigned  short  )0xe002  )
#define		CONST_qyCmd_getDigest					(  (  unsigned  short  )0xe003  )


 //  
 //			 unsigned  short
 //			 
#define		CONST_qyRc_ok							(  (  unsigned  short  )0  )
#define		CONST_qyRc_err							(  (  unsigned  short  )255  )
 //			 
#define		CONST_qyRc_user							(  (  unsigned  short  )2000  )		// (  (  unsigned  short  )2048  )
#define		CONST_qyRc_redirect						(  (  unsigned  short  )(  CONST_qyRc_user  +  1  )  )
#define		CONST_qyRc_needAutoReg					(  (  unsigned  short  )(  CONST_qyRc_user  +  2  )  )
//  #define		CONST_qyRc_notFound						(  (  unsigned  short  )(  CONST_qyRc_user  +  3  )  )	//  2005/02/01
#define		CONST_qyRc_needVerified					(  (  unsigned  short  )(  CONST_qyRc_user  +  4  )  )		//  2007/04/22
#define		CONST_qyRc_anotherLogonExists			(  (  unsigned  short  )(  CONST_qyRc_user  +  5  )  )		//  2011/02/02


#define		CONST_qyRc_peerOffline					(  (  unsigned  short  )CONST_qyRc_user  +  100  )			//  2007/05/29
#define		CONST_qyRc_servBusy						(  (  unsigned  short  )CONST_qyRc_user  +  101  )			//  2007/05/29
#define		CONST_qyRc_unknown						(  (  unsigned  short  )CONST_qyRc_user  +  102  )			//  2007/07/01

 //			 
#define		CONST_qyRc_upReserved					(  (  unsigned  short  )0xe000  )	//  57344
#define		CONST_qyRc_quit							(  (  unsigned  short  )0xe001  )
#define		CONST_qyRc_update						(  (  unsigned  short  )0xe002  )
#define		CONST_qyRc_hint							(  (  unsigned  short  )0xe003  )

 //			
#define		isRcQuit(  x  )							(  (  x  )  ==  CONST_qyRc_quit  )
#define		isRcOk(  x  )							(  (  x  )  ==  CONST_qyRc_ok  )
#define		isRcRedirect(  x  )						(  (  x  )  ==  CONST_qyRc_redirect  )
#define		isRcUpdate(  x  )						(  (  x  )  ==  CONST_qyRc_update  )
#define		isRcHint(  x  )							(  (  x  )  ==  CONST_qyRc_hint  )
#define		isRcNeedVerified(  x  )					(  (  x  )  ==  CONST_qyRc_needVerified  )


//
#define		CONST_ucCommServiceType_null				0
#define		CONST_ucCommServiceType_1					1		//  增加了commServiceType,startTime_base


//
//#define	__USE_old_commService__


#ifdef  __USE_old_commService__
//
typedef  struct  __qyCommService_t					{
				 unsigned  int						serviceId;
				 char								version[CONST_qyMaxVerLen];			//  
				 unsigned  int						encType;
				 char								data[8192];
}		 QY_COMM_SERVICE;
//
#else

typedef  struct  __atCommService_h_t					{
				 unsigned  int						serviceId;
				 char								version[CONST_qyMaxVerLen];			//  
				 unsigned  int						encType;
				 unsigned  char						ucCommServiceType;
				 __int64							i64StartTime_base;
				 char								data[8192];
}		 AT_COMM_SERVICE_h;

//
typedef  struct  __atCommService_n_t {
	unsigned  int						serviceId;
	char								version[CONST_qyMaxVerLen];			//  
	unsigned  int						encType;
	unsigned  char						ucCommServiceType;
	char								i64StartTime_base_buf[8];
	char								data[8192];
}		 AT_COMM_SERVICE_n;


//
typedef  AT_COMM_SERVICE_h					QY_COMM_SERVICE_h;
typedef  AT_COMM_SERVICE_n					QY_COMM_SERVICE_n;


//
#endif 



//
typedef  struct  __qyCommBufSize_t					{
				 unsigned  int						len;
				 char							*	data;
}		 QY_COMM_BUFSIZE;

/*
typedef  struct  __qyCommHead_t  {
				 unsigned  short					usCode;				// 
				 char								reserved[2];			
				 unsigned  int						len;				// 
}		 QY_COMM_HEAD;
*/

//  2007/04/22, 
typedef  struct  __qyCommHead_t						{
				 unsigned  short					usCode;				// 
				 unsigned  char						ucFlg;				//  2007/04/22, 
				 char								reserved[1];			
				 unsigned  int						len;				//  
}		 QY_COMM_HEAD;


#ifdef  __USE_atCommVer_1__

//
#define		CONST_commFlg_resp						(  1  <<  7  )
#define		CONST_commFlg_moreData					(  1  <<  6  )									//  2007/05/07
#define		CONST_commFlg_talkData					(  1  <<  5  )									//  数据区的格式为MIS_MSG_TALKDATA，否则为IM_MSG_CONTENTU
#define		CONST_commFlg_routeTalkData				(  1  <<  4  )									//  数据区的格式为用MSG_ROUTE+IM_MSG_CONTENTU

//
#else

#define		CONST_commFlg_resp						CONST_atCommFlg_resp
#define		CONST_commFlg_moreData					CONST_atCommFlg_moreData
#define		CONST_commFlg_talkData					CONST_atCommFlg_talkData
#define		CONST_commFlg_routeTalkData				CONST_atCommFlg_routeTalkData


#endif 


//	
#define		isUcFlgResp(  ucFlg  )					(  ucFlg  &  CONST_commFlg_resp  )				//  2007/04/22
#define		isUcFlgMoreData(  ucFlg  )				(  ucFlg  &  CONST_commFlg_moreData  )			//  2007/05/07
#define		isUcFlgTalkData(  ucFlg  )				(  ucFlg  &  CONST_commFlg_talkData  )			//  2007/07/11
#define		isUcFlgRouteTalkData(  ucFlg  )			(  ucFlg  &  CONST_commFlg_routeTalkData  )		//  2007/11/29


#define		QY_COMM_REQHEAD							QY_COMM_HEAD
#define		QY_COMM_RESPHEAD						QY_COMM_HEAD


typedef  struct  __qyCommReq_t						{
				 QY_COMM_REQHEAD					head;
				 union	 {
						 QY_COMM_SERVICE_h			service;		//  这个service好象没有什么用处。2007/04/18
				 }									u;
}		 QY_COMM_REQ;


typedef  struct  __qyCommResp_t						{
				 QY_COMM_RESPHEAD					head;
}		 QY_COMM_RESP;



//
typedef  int  (*PF_enc)(void* pSession, void* pmyHgSessionEnc, char* input, unsigned  int  inputLen, char* output, unsigned  int* pOutputSize);
typedef  int  (*PF_dec)(void* pSession, void* pmyHgSessionEnc, char* input, unsigned  int  inputLen, char* output, unsigned  int* pOutputSize);

//typedef  int  (*PF_enc)(void* pQY_COMM_SESSION, char* input, unsigned  int  inputLen, char* output, unsigned  int* pOutputSize);
//typedef  int  (*PF_dec)(void* pQY_COMM_SESSION, char* input, unsigned  int  inputLen, char* output, unsigned  int* pOutputSize);




//
typedef  struct  __qyCommSession_t					{
				 //
				 unsigned  int						uiType;								//  2015/08/24
				 //
				 QY_COMM_SERVICE_h					service;
				 unsigned  int						lenInBytes_service_n;				//  接收到的QY_COMM_SERVICE 的字节熟. 2008/06/10
				 //
				 unsigned  int						service_dataLen;
				 //
				 QY_ENC_CTX							encCtx;
				 QY_ENC_CTX							quitEncCtx;
				 QY_ENC_CTX							updateEncCtx;
				 QY_ENC_CTX							commEncCtx;							//  2004/01/03
				 //
				 char								startTime[CONST_qyTimeLen  +  1];	//  2004/07/26
				 char								clientIp[CONST_qyMaxIpLen  +  1];	//  2007/04/01
				 //
				 unsigned  int						uiSessionId;						//  会话序号，2004/09/11
				 //
				 unsigned  short					usLastReqCode_i;					//  2007/04/24, 输入的
				 unsigned  short					usLastRespCode_i;					//  最后一个响应的响应码
				 unsigned  short					usLastReqCode_o;					//  2007/04/24, 输出的
				 unsigned  short					usLastRespCode_o;					//  最后一个响应的响应码
				 //
				 unsigned  int						nTalks;								//  与客户机交流的次数
				 //
				 BOOL								bAdmin;								//  2011/01/10

				 //
				 void						*		pmyHgSessionEnc;

				 //
				 PF_enc								pf_enc;
				 PF_dec								pf_dec;

				 //
				 TCHAR								hintForDbg[128];

				 //
}		 QY_COMM_SESSION;



#endif	/*  }  */





