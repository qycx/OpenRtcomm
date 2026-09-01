#include <qyDefs_open.h>


#ifndef  __qyPtz_open_h__
#define  __qyPtz_open_h__	//  {


//  2014/09/13
#define		CONST_ptzCmd_null					0
#define		CONST_ptzCmd_up						1
#define		CONST_ptzCmd_down					2
#define		CONST_ptzCmd_left					3
#define		CONST_ptzCmd_right					4
#define		CONST_ptzCmd_topLeft				5
#define		CONST_ptzCmd_topRight				6
#define		CONST_ptzCmd_bottomLeft				7
#define		CONST_ptzCmd_bottomRight			8
#define		CONST_ptzCmd_noop					9
#define		CONST_ptzCmd_focusIn				10
#define		CONST_ptzCmd_focusOut				11
#define		CONST_ptzCmd_irisIn					12
#define		CONST_ptzCmd_irisOut				13
#define		CONST_ptzCmd_zoomIn					14
#define		CONST_ptzCmd_zoomOut				15

//
#define		CONST_ptzCmd_3ddw					20






//
typedef  struct  __ptzCmdCommon_t  {
				 //  2014/09/1
				 struct												{
					 unsigned  int									uiObjType;
					 unsigned  short								usIndex_obj;
					 unsigned  short								usHelp_subIndex;
				 }													obj;

				 //
				 QY_MESSENGER_ID									idInfo;
				 int												iChannel;

				 //  2014/09/13
				 unsigned  char										ucCmd;
				 unsigned  char										ucParam;
				 //
				 unsigned  char										ucMouseStatus;		//  用来区分鼠标按下放开的两个状态

}	PTZ_cmd_common;


//
typedef  struct  __ptcCmdParam3ddw_t {

				 //	
				 short												sW_video;	// = 1920; // 图像长宽
				 short												sH_video;	// = 1080;

				 //
				 short												xTop;
				 short												yTop;
				 short												xBottom;
				 short												yBottom;//方框结束点的y坐标

}		 PTZ_cmdParam_3ddw;


//
typedef  struct  __ptzCmd3ddw_t {
				 PTZ_cmd_common										common;
				 //
				 PTZ_cmdParam_3ddw									param;


}		PTZ_cmd_3ddw;;

//
typedef  union  __ptzCmdParamU_t {
				PTZ_cmdParam_3ddw									param3ddw;

}		 PTZ_cmdParamU;



//
typedef  struct  __nvrCmdCommon_t {

				 //
				 unsigned  short									usCmd;
				 int												iChannel;

}		 NVR_cmd_common;



//
#endif  //  }


