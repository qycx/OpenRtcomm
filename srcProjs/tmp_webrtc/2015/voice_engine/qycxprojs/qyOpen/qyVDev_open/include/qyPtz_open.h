

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


		
typedef  struct  __ptzCmdCommon_t  {
				 //  2014/09/1
				 struct												{
					 unsigned  int									uiObjType;
					 unsigned  short								usIndex_obj;
					 unsigned  short								usHelp_subIndex;
				 }													obj;

				 //  2014/09/13
				 unsigned  char										ucCmd;
				 unsigned  char										ucParam;

}	PTZ_cmd_common;



#endif  //  }


