#include  "stdafx.h"
#include  "Pelco_P.h"

namespace  Pelco_P_Protocol  {

//  Extended Command Set
BYTE  *  CPelco_P::Preset(  UINT  deviceAddress,  BYTE  preset,  PresetAction  action  )
{
	BYTE  m_action;
	switch  (  action  )  {
			case  PresetAction_Set:
				  m_action  =  0x03;
				  break;
			case  PresetAction_Clear:
				  m_action  =  0x05;
				  break;
			case  PresetAction_Goto:
				  m_action  =  0x07;
				  break;
			default:
				  m_action  =  0x03;
				  break;
	}
	return  Package(  deviceAddress,  0x00,  m_action,  0x00,  preset  );
}

BYTE  *  CPelco_P::Flip(  UINT  deviceAddress  )
{
	return  Package(  deviceAddress,  0x00,  0x07,  0x00, 0x21  );
}

BYTE  *  CPelco_P::ZeroPanPosition(  UINT  deviceAddress  )
{
	return  Package(  deviceAddress,  0x00,  0x07,  0x00, 0x22  );
}

BYTE  *  CPelco_P::SetAuxiliary(  UINT  deviceAddress,  BYTE  auxiliaryID,  AuxAction  action  )
{
	if  (  auxiliaryID  <  0x00  )  
		auxiliaryID  =  0x00;
	else  if  ( auxiliaryID  >  0x08  )  
		auxiliaryID  =  0x08;
	return  Package(  deviceAddress,  0x00,  (  BYTE  )action,  0x00, auxiliaryID  );
}

BYTE  *  CPelco_P::RemoteReset(  UINT  deviceAddress  )
{
	return  Package(  deviceAddress,  0x00,  0x0F,  0x00, 0x00  );
}

BYTE  *  CPelco_P::Zone(  UINT  deviceAddress,  BYTE  zone,  Action  action  )
{
	if  (  zone  <  0x01  )  
		zone  =  0x01;
	else  if  (  zone  >  0x08  )  
		zone  =  0x08;
	BYTE  m_action;
	if (  action  ==  Action_Start  )  
		m_action  =  0x11;
	else  
		m_action  =  0x13;
	
	return  Package(  deviceAddress,  0x00,  m_action,  0x00, zone  );
}

BYTE  *  CPelco_P::WriteToScreen(  UINT  deviceAddress,  char  *  text  )
{
	if  (  strlen(  text  )  >  40  )  
		text[40]  =  '\0';
	int  i  =  0;
	UINT  m_scrPosition;
	BYTE  m_ASCIIchr;
	int  len;
	BYTE  *  Message;
	len  =  strlen(  text  );
	*  (  (  UINT  *  )MessageBuffer  )  =  strlen(  text  )  *  MessageLen;
	for  (  i = 0;  i < len;  i ++  ){
		m_scrPosition  =  i;
		m_ASCIIchr  =  text[i];
		Message  =  Package(  deviceAddress,  0x00,  0x15,  m_scrPosition,  m_ASCIIchr  );
		memcpy(  MessageBuffer  +  i  *  MessageLen  +  MessageHead,  Message  +  MessageHead,  MessageLen  );
	}
	return  MessageBuffer;
}

BYTE  *  CPelco_P::ClearScreen(  UINT  deviceAddress  )
{
	return  Package(  deviceAddress,  0x00,  0x17,  0x00, 0x00  );
}

BYTE  *  CPelco_P::AlarmAcknowledge(  UINT  deviceAddress,  UINT  alarmID  )
{
	if  (  alarmID  <  1  ||  alarmID  >  8  )  {
		return  Package(  deviceAddress,  0x00,  0x00,  0x00,  0x00  );
	}
	return  Package(  deviceAddress,  0x00,  0x19,  0x00,  (  BYTE  )alarmID  );
}

BYTE  *  CPelco_P::ZoneScan(  UINT  deviceAddress,  Action  action  )
{
	BYTE  m_action;
	if  (  action  ==  Action_Start  )  
		m_action  =  0x1B;
	else  
		m_action  =  0x1D;

	return  Package(  deviceAddress,  0x00,  m_action,  0x00,  0x00  );
}

BYTE  *  CPelco_P::Pattern(  UINT  deviceAddress,  PatternAction  action  )
{
	BYTE  m_action;
	switch(  action  )  {
		case  PatternAction_Start:
			  m_action  =  0x1F;
			  break;
		case  PatternAction_Stop:
			  m_action  =  0x21;
			  break;
		case  PatternAction_Run:
			  m_action  =  0x23;
			  break;
		default:
			  m_action  =  0x23;
			  break;
	}
	return  Package(  deviceAddress,  0x00,  m_action,  0x00,  0x00  );
}

BYTE  *  CPelco_P::SetZoomLensSpeed(  UINT  deviceAddress,  LensSpeed  speed  )
{
	return  Package(  deviceAddress,  0x00,  0x25,  0x00, (  BYTE  )speed  );
}

BYTE  *  CPelco_P::SetFocusLensSpeed(  UINT  deviceAddress,  LensSpeed  speed  )
{
	return  Package(  deviceAddress,  0x00,  0x27,  0x00, (  BYTE  )speed  );
}

//  Base Command Set
BYTE  *  CPelco_P::CameraSwitch(  UINT  deviceAddress,  Switch  action  )
{
	BYTE  m_action  =  CameraOnOff;
	if  (  action  ==  Switch_On  )  
		m_action  +=  CameraOnOff;
	return  Package(  deviceAddress,  m_action,  0x00,  0x00,  0x00  );
}

BYTE  *  CPelco_P::CameraIrisSwitch(  UINT  deviceAddress,  Iris  action  )
{
	return  Package(  deviceAddress,  (  BYTE  )action,  0x00,  0x00,  0x00  );
}

BYTE  *  CPelco_P::CameraFocus(  UINT  deviceAddress,  Focus  action  )
{
	return  Package(  deviceAddress,  (  BYTE  )action,  0x00,  0x00,  0x00  );
}

BYTE  *  CPelco_P::CameraZoom(  UINT  deviceAddress,  Zoom  action  )
{
	return  Package(  deviceAddress,  0x00,  (  BYTE  )action,  0x00,  0x00  );
}

BYTE  *  CPelco_P::CameraTilt(  UINT  deviceAddress,  Tilt  action,  UINT  speed  )
{
	if  (  speed  <  TiltSpeedMin  )  
		speed  =  TiltSpeedMin;
	if  (  speed  >  TiltSpeedMax  )  
		speed  =  TiltSpeedMax;

	return  Package(  deviceAddress,  0x00,  (  BYTE  )action,  0x00,  (  BYTE  )speed  );
}

BYTE  *  CPelco_P::CameraPan(  UINT  deviceAddress,  Pan  action,  UINT  speed  )
{
	if  (  speed  <  PanSpeedMin  )  
		speed  =  PanSpeedMin;
	if  (  speed  >  PanSpeedMax  )  
		speed  =  PanSpeedMax;

	return  Package(  deviceAddress,  0x00,  (  BYTE  )action,  (  BYTE  )speed,  0x00  );
}

BYTE  *  CPelco_P::CameraPanTilt(  UINT  deviceAddress,  Pan  panAction,  UINT  panSpeed,  Tilt  tiltAction,  UINT  tiltSpeed  )
{
	BYTE  PanCmd,  TiltCmd,  PanSpeed,  TiltSpeed;
	BYTE  *  m_tiltMessage  =  CameraTilt(  deviceAddress,  tiltAction,  tiltSpeed  );
	TiltCmd  =  m_tiltMessage[MessageHead  +  3];
	TiltSpeed  =  m_tiltMessage[MessageHead  +  5];
	BYTE  *  m_panMessage  =  CameraPan(  deviceAddress,  panAction,  panSpeed  );
	PanCmd  =  m_panMessage[MessageHead  +  3];
	PanSpeed  =  m_panMessage[MessageHead  +  4];

	return  Package(  deviceAddress,  0x00,  (  BYTE  )(  TiltCmd  |  PanCmd  ),  PanSpeed,  TiltSpeed  );
}

BYTE  *  CPelco_P::CameraStop(  UINT  deviceAddress  )
{
	return  Package(  deviceAddress,  0x00,  0x00,  0x00, 0x00  );
}

BYTE  *  CPelco_P::CameraScan(  UINT  deviceAddress,  Scan  scan  )
{
	BYTE  m_byte  =  0x00;  //  AutoManualScan;
	if  (  scan  ==  Scan_Auto  )  
		m_byte  =  AutoscanOn;
	return  Package(  deviceAddress,  m_byte,  0x00,  0x00,  0x00  );
}

BYTE  *  CPelco_P::Noop(  UINT  deviceAddress  )
{
	return  Package(  deviceAddress,  0x00,  0x00,  0x00, 0x00  );
}

//  private:
BYTE  *  CPelco_P::Package(  BYTE Address,  BYTE Data1,  BYTE  Data2,  BYTE  Data3,  BYTE  Data4  )
{
	Pelco_P.STX  =  STX;
	Pelco_P.Address  =  Address;
	Pelco_P.Data1  =  Data1;
	Pelco_P.Data2  =  Data2;
	Pelco_P.Data3  =  Data3;
	Pelco_P.Data4  =  Data4;
	Pelco_P.ETX  =  ETX;
	Pelco_P.CheckSum  =  (  BYTE  )(  Pelco_P.STX^Pelco_P.Address^Pelco_P.Data1^Pelco_P.Data2^Pelco_P.Data3^Pelco_P.Data4^Pelco_P.ETX  );
	*  (  (  UINT  *  )  Message  )  =  (  UINT  )MessageLen;
	Message[MessageHead  +  0  ]  =  Pelco_P.STX;
	Message[MessageHead  +  1  ]  =  Pelco_P.Address;
	Message[MessageHead  +  2  ]  =  Pelco_P.Data1;
	Message[MessageHead  +  3  ]  =  Pelco_P.Data2;
	Message[MessageHead  +  4  ]  =  Pelco_P.Data3;
	Message[MessageHead  +  5  ]  =  Pelco_P.Data4;
	Message[MessageHead  +  6  ]  =  Pelco_P.ETX;
	Message[MessageHead  +  7  ]  =  Pelco_P.CheckSum;
	return  Message;
}

};