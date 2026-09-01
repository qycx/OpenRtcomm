
#ifndef  __qmcShareDynBmp_h__
#define  __qmcShareDynBmp_h__	//  {


//
#include	"qisOnvifCommProc_open.h"
#include	"qisPtzWnd.h"
//
#include	"qmcStruct_defs.h"
#include	"qyGuiCommProc.h"


//
typedef  struct	 __onvifRule_t					{
				 unsigned  short  				usIndex_obj;

				 //
				 int							iOnvifRuleType;									//  2016/06/16

				 //
				 char							url[MAX_rtspUrlLen  +  1];				
				 TCHAR							cusName[32];

				 //  2016/06/16
				 char  							usrName[128];
				 char							passwd[128];

				 //
				 char							defToken[128];									//  2016/07/13

				 //  2014/06/10
				 struct							{
					 //
					 unsigned  int				uiTranNo_changeContent;
					 //
					 BOOL						bDel;
				 }								status;

}		 Onvif_rule;


//  2016/06/25
typedef  struct  __ipDev_t													{

				 //
				 Onvif_rule													rule;
				 
				 //
				 int														iType;				//  2016/06/16
				 //
				 unsigned  short											usHelp_subIndex;	//  2016/07/07. qufen自动扫描出的多个结果
				 
				 //
				 char														ip[15  +  1];				  

				 //
				 unsigned  char												ucCnt_urls;
				 Onvif_url													urls[3];
				 //		 
				 char														deviceServiceAddr[256];		 


				 //
				 struct														{					 
					 //
					 BOOL													toBeStopped;
					 //
					 DWORD													dwLastProcessedTickCnt;
				 }															status;

}		 IP_dev;


//
BOOL  isSame_resObj(  RES_obj_simple  *  p1,  RES_obj_simple  *  p2  );
BOOL  isSame_qisResObj(  QIS_res_obj  *  p1,  QIS_res_obj  *  p2  );

//
BOOL  isSame_onvifRule(  Onvif_rule  *  p1,  Onvif_rule  *  p2  );
//
BOOL  isSame_ipDev(  IP_dev  *  p1,  IP_dev  *  p2  );


//
__declspec(  dllexport  )  int  getRegVal_webcam_rtspUrl(  Onvif_rule  *  pItemUrl,  TCHAR  *  tVal,  int  cnt  );
__declspec(  dllexport  )  int  parseRegVal_webcam_rtspUrl(  LPCTSTR  regVal,  Onvif_rule  *  pItemUrl  );



 //  2014/09/11
#define		CONST_shareDynBmpMem_step_0		0
#define		CONST_shareDynBmpMem_step_1		1
#define		CONST_shareDynBmpMem_step_2		2



//
typedef  struct  __shareDynBmpMem_t			{
				 //	
#if  0
				 unsigned  int				uiObjType;								//  2014/11/01
				 unsigned  short			usIndex_obj;							//  2014/05/31
#endif
				 //  2016/07/24
				 RES_obj_simple					resObj;

				 //
				 int						iMenuId;
				 TCHAR						name[MAX_rtspUrlLen  +  1];
				 TCHAR						cusName[32];
				 
				 // 2017/06/12
				 unsigned  short			usW,  usH;								//  2017/06/12

				 
				 //
				 BOOL						bAudioExists;							//  2015/05/18. ÓÐÒôÆµ²¿·Ö
				 BOOL						bVideoExists;							//  2015/05/18. ÓÐÊÓÆµ²¿·Ö				 
				 
				 //
				 int						iIndex_sharedObj_master;				//  2014/09/29. ÓÃ×÷makeSlaveStreamÊ±ÓÐÐèÒª
				 //
				 BITMAPINFOHEADER			bih_mosaic;								//  2014/10/31. ÓÃ×÷makePhotomosaicµÄÐèÒª
				
				 

				 //
				 struct						{
					BOOL					bUsing;
					//BOOL					bShared;
					//
					int						iIndex_sharedObj;
					int						iIndex_sharedObjUsr;					//  2014/09/11
					unsigned  int			uiTaskType;
					unsigned  char			ucbUsed_iIndex_sharedObj;				//  2014/09/11.
					//
					BOOL					bSupported_pktResType_sharedTex3;		//  2015/10/20
					
					//
					TASK_av_props			taskAvProps;							//  2015/10/23
					
					//
					DWORD					dwTickCnt_start;						//  2014/09/12

					//
					unsigned  char			ucbLocalVideoOpen;		
					int						iTaskId;								//  2009/09/13

					//
					//  2012/05/06
					ZONE_PARAM				zoneParam;

					//
					struct					{
						unsigned  int		uiTranNo_storeRecvdReq;					//  2014/09/11
						int					index_recvdReq;
					}						recvdReq;

					//  2014/09/11
					struct					{
						DWORD				dwTickCnt_start;
						BOOL				bInProcess;
						int					nStep;
						//
						int					iTaskId_suggested;
						//
						BOOL				bTest;
					}						internalProcess;

				 }							var;

				 //
				 QIS_ptz_wnd				ptzWnd;

}		 SHARE_dyn_bmp,  SHARE_DYN_BMP;								



//
//  #define		CONST_shareDynBmpMems			3
#define			CONST_shareDynBmpMems			6		//  2014/06/12

typedef  struct  __shareDynBmps_t			{
				 //  unsigned  int				uiObjType;
				 QY_DMITEM				*	pTable_ctrls;
				 unsigned  short			usCnt;
				 //  SHARE_dyn_bmp			mems[CONST_shareDynBmpMems];
				 SHARE_dyn_bmp			mems_internal[CONST_shareDynBmpMems];		//  2014/09/09
}		 SHARE_dynBmps;





//
//
#define		CONST_onvifRuleType_null				0
#define		CONST_onvifRuleType_rtspUrl				1
#define		CONST_onvifRuleType_discovery			2
#define		CONST_onvifRuleType_probe				3


//
QY_DMITEM  CONST_onvifRuleTypeTable[];
















//
//  2014/09/28
//
int  toShareDynBmp(  CCtxQmc  *  pProcInfo,  HWND  m_hWnd,  void  **  ppCapStuff,  int  iTaskId_suggested,  AV_COMPRESSOR_CFG  *  pCompressor_suggested,  int  iFourcc_suggested,  TASK_av_props  *  pTaskAvProps,  SHARE_dyn_bmp  *  pDynBmpMem  );
int  toShareDynBmp_step3(  CCtxQmc  *  pProcInfo,  HWND  m_hWnd,  int  iTaskId_suggested,  SHARE_dyn_bmp  *  pDynBmpMem  );






//
#endif  //  }


