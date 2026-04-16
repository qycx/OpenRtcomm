#ifndef  PELCO_P_H
#define  PELCO_P_H
/*** Pelco_P Protocol ***************************/
typedef struct  {
				BYTE  STX;
				BYTE  Address;
				BYTE  Data1;
				BYTE  Data2;
				BYTE  Data3;			//  Pan Speed
				BYTE  Data4;			//  Tilt Speed
				BYTE  ETX;
				BYTE  CheckSum;
}		PELCO_P_PROTOCOL;

#ifdef  ZZZ

#define  PELCO_P_STX  0xA0
#define  PELCO_P_ETX  0xAF

/***** Pelco_P : Address *****/
#define  PELCO_P_ADDRESS_MIN	0x00
#define  PELCO_P_ADDRESS_MAX	0x1F
/***** Pelco_P : Data1 *****/
enum  {
	  PELCO_P_D1_CAMERA_ON				=	0x40;
	  PELCO_P_D1_AUTOSCAN_ON			=	0x20;
	  PELCO_P_D1_CAMERA_ON_OFF			=	0x10;
	  PELCO_P_D1_IRIS_CLOSE				=	0x08;
	  PELCO_P_D1_IRIS_OPEN				=	0x04;
	  PELCO_P_D1_FOCUS_NEAR				=	0x02;
	  PELCO_P_D1_FOCUS_FAR				=	0x01;
};
/***** Pelco_P : Data2 *****/
enum  {
	  PELCO_P_D2_ZOOM_WIDE				=	0x40;
	  PELCO_P_D2_ZOOM_TELE				=	0x20;
	  PELCO_P_D2_TILT_DOWN				=	0x10;
	  PELCO_P_D2_TILT_UP				=	0x08;
	  PELCO_P_D2_PAN_LEFT				=	0x04;
	  PELCO_P_D2_PAN_RIGHT				=	0x02;
};
/***** Pelco_P : Data3 *****/
#define	  PELCO_P_D3_PAN_SPEED_MIN			0x00
#define	  PELCO_P_D3_PAN_SPEED_MAX			0x3F
#define	  PELCO_P_D3_PAN_SPEED_TURBO		0x40
/***** Pelco_P : Data4 *****/
#define	  PELCO_P_D3_TILT_SPEED_MIN			0x00
#define	  PELCO_P_D3_TILT_SPEED_MIN			0x3F

#endif

namespace  Pelco_P_Protocol  {
	const  UINT  MessageLen  =  8;
	const  UINT  MessageHead  =  sizeof(  UINT  );
	const  BYTE  STX  =  0xA0;
	const  BYTE  ETX  =  0xAF;
	//  Pan and Tilt commands
	//  Data1
	const  byte  FocusFar  =  0x01;
	const  byte  FocusNear  =  0x02;
	const  byte  IrisOpen  =  0x04;
	const  byte  IrisClose  =  0x08;
	const  byte  CameraOnOff  =  0x10;
	const  byte  AutoscanOn  =  0x20;
	const  byte  CameraOn  =  0x40;
	//  Data2
	const  byte  PanRight  =  0x02;
	const  byte  PanLeft  =  0x04;
	const  byte  TiltUp  =  0x08;
	const  byte  TiltDown  =  0x10;
	const  byte  ZoomTele  =  0x20;
	const  byte  ZoomWide  =  0x40;
	//  Data3
	const  byte  PanSpeedMin  =  0x00;
	const  byte  PanSpeedMax  =  0x40;
	//  Data4
	const  byte  TiltSpeedMin  =  0x00;
	const  byte  TiltSpeedMax  =  0x3F;

	class  CPelco_P  {
		public:
			CPelco_P(  )  {};
			~CPelco_P(  )  {};
			//  Enum
			enum  PresetAction {  PresetAction_Set,  PresetAction_Clear,  PresetAction_Goto  };
			enum  PatternAction  {  PatternAction_Start,  PatternAction_Stop,  PatternAction_Run  };
			enum  AuxAction  {  AuxAction_Set  =  0x09,  AuxAction_Clear  =  0x0B  };
			enum  Action  {  Action_Start,  Action_Stop  };
			enum  LensSpeed  {  LensSpeed_Low  =  0x00,  LensSpeed_Medium  =  0x01,  LensSpeed_High  =  0x02,  LensSpeed_Turbo  =  0x03  };
			enum  Pan  {  Left  =  PanLeft,  Right  =  PanRight  };
			enum  Tilt  {  Up  =  TiltUp,  Down  =  TiltDown  };
			enum  Iris  {  Open  =  IrisOpen,  Close  =  IrisClose  };
			enum  Zoom  {  Wide  =  ZoomWide,  Tele  =  ZoomTele  };
			enum  Switch  {  Switch_On,  Switch_Off  };
			enum  Focus  {  Near  =  FocusNear,  Far  =  FocusFar  };
			enum  Scan  {  Scan_Auto,  Scan_Manual  };
		public:
			//  Extended Command Set
			BYTE  *  Preset(  UINT  deviceAddress,  BYTE  preset,  PresetAction  action  );
			BYTE  *  Flip(  UINT  deviceAddress  );
			BYTE  *  ZeroPanPosition(  UINT  deviceAddress  );
			BYTE  *  SetAuxiliary(  UINT  deviceAddress,  BYTE  auxiliaryID,  AuxAction  action  );
			BYTE  *  RemoteReset(  UINT  deviceAddress  );
			BYTE  *  Zone(  UINT  deviceAddress,  BYTE  zone,  Action  action  );
			BYTE  *  WriteToScreen(  UINT  deviceAddress,  char  *  text  );
			BYTE  *  ClearScreen(  UINT  deviceAddress  );
			BYTE  *  AlarmAcknowledge(  UINT  deviceAddress,  UINT  alarmID  );
			BYTE  *  ZoneScan(  UINT  deviceAddress,  Action  action  );
			BYTE  *  Pattern(  UINT  deviceAddress,  PatternAction  action  );
			BYTE  *  SetZoomLensSpeed(  UINT  deviceAddress,  LensSpeed  speed  );
			BYTE  *  SetFocusLensSpeed(  UINT  deviceAddress,  LensSpeed  speed  );
			//  Base Command Set
			BYTE  *  CameraSwitch(  UINT  deviceAddress,  Switch  action  );
			BYTE  *  CameraIrisSwitch(  UINT  deviceAddress,  Iris  action  );
			BYTE  *  CameraFocus(  UINT  deviceAddress,  Focus  action  );
			BYTE  *  CameraZoom(  UINT  deviceAddress,  Zoom  action  );
			BYTE  *  CameraTilt(  UINT  deviceAddress,  Tilt  action,  UINT  speed  );		
			BYTE  *  CameraPan(  UINT  deviceAddress,  Pan  action,  UINT  speed  );
			BYTE  *  CameraPanTilt(  UINT  deviceAddress,  Pan  panAction,  UINT  panSpeed,  Tilt  tiltAction,  UINT  tiltSpeed  );
			BYTE  *  CameraStop(  UINT  deviceAddress  );
			BYTE  *  CameraScan(  UINT  deviceAddress,  Scan  scan  );
			BYTE  *  Noop(  UINT  deviceAddress  );
		private:
			BYTE  *  Package(  BYTE Address,  BYTE Data1,  BYTE  Data2,  BYTE  Data3,  BYTE  Data4  );
		private:
			PELCO_P_PROTOCOL  Pelco_P; 
			BYTE  Message[16];
			BYTE  MessageBuffer[512];
	};
};

#endif