#include  "stdafx.h"
#include  "Pelco_D.h"
#include  "Pelco_P.h"
#include  "StageLens.h"
//  #include  "YT.h"
//  #include  "YTDlg.h"

 int myPtz_write(  void  *  pDlgPtzControl,  char  *  buf,  unsigned  int  iLen  );


//
void  CStageLens::SetProtocol(  PROTOCOL  Protocol  )
{
	Protocol_ID  =  Protocol;
}

void  CStageLens::UnPackMessage(  void  )
{
	char  szBuf[7];
	memset(  szBuf,  0,  sizeof(  szBuf  )  );

	switch  (  Protocol_ID  )  {
		case  PELCO_D:
			Len  =  *  (  (  UINT  *  )  Message  );
			Message  +=  Pelco_D_Protocol::MessageHead;
			strcpy(  szBuf,  (  char  *  )Message  );
			break;
		case  PELCO_P:
			Len  =  *  (  (  UINT  *  )  Message  );
			Message  +=  Pelco_P_Protocol::MessageHead;
			break;
	}
	//  g_pMainDlg->m_CCom.write(  (  char  *  )Message,  Len  );
	myPtz_write(  this->pDlgPtzControl,  (  char  *  )Message,  Len  );
}

void  CStageLens::Up(  UINT  deviceAddress  )
{
	switch  (  Protocol_ID  )  {
		case  PELCO_D:
			Message  =  Pelco_D.CameraTilt(  deviceAddress,  Pelco_D_Protocol::CPelco_D::Tilt::Up,  m_nSpeed  );  
			break;
		case  PELCO_P:
			Message  =  Pelco_P.CameraTilt(  deviceAddress  -  1,  Pelco_P_Protocol::CPelco_P::Tilt::Up,  m_nSpeed  );
			break;
	}
	UnPackMessage(  );
}

void  CStageLens::TopRight(  UINT  deviceAddress  )
{
	switch  (  Protocol_ID  )  {
		case  PELCO_D:
			Message  =  Pelco_D.CameraPanTilt(  deviceAddress,  Pelco_D_Protocol::CPelco_D::Pan::Right,  m_nSpeed,  Pelco_D_Protocol::CPelco_D::Tilt::Up,  m_nSpeed  );  
			break;
		case  PELCO_P:
			Message  =  Pelco_P.CameraPanTilt(  deviceAddress  -  1,  Pelco_P_Protocol::CPelco_P::Pan::Right,  m_nSpeed,  Pelco_P_Protocol::CPelco_P::Tilt::Up,  m_nSpeed  );
			break;
	}
	UnPackMessage(  );
}

void  CStageLens::Right(  UINT  deviceAddress  )
{
	switch  (  Protocol_ID  )  {
		case  PELCO_D:
			Message  =  Pelco_D.CameraPan(  deviceAddress,  Pelco_D_Protocol::CPelco_D::Pan::Right,  m_nSpeed  );  
			break;
		case  PELCO_P:
			Message  =  Pelco_P.CameraPan(  deviceAddress  -  1,  Pelco_P_Protocol::CPelco_P::Pan::Right,  m_nSpeed  );
			break;
	}
	UnPackMessage(  );
}

void  CStageLens::BottomRight(  UINT  deviceAddress  )
{
	switch  (  Protocol_ID  )  {
		case  PELCO_D:
			Message  =  Pelco_D.CameraPanTilt(  deviceAddress,  Pelco_D_Protocol::CPelco_D::Pan::Right,  m_nSpeed,  Pelco_D_Protocol::CPelco_D::Tilt::Down,  m_nSpeed  );  
			break;
		case  PELCO_P:
			Message  =  Pelco_P.CameraPanTilt(  deviceAddress  -  1,  Pelco_P_Protocol::CPelco_P::Pan::Right,  m_nSpeed,  Pelco_P_Protocol::CPelco_P::Tilt::Down,  m_nSpeed  );
			break;
	}
	UnPackMessage(  );
}

void  CStageLens::Down(  UINT  deviceAddress  )
{
	switch  (  Protocol_ID  )  {
		case  PELCO_D:
			Message  =  Pelco_D.CameraTilt(  deviceAddress,  Pelco_D_Protocol::CPelco_D::Tilt::Down,  m_nSpeed  );  
			break;
		case  PELCO_P:
			Message  =  Pelco_P.CameraTilt(  deviceAddress  -  1,  Pelco_P_Protocol::CPelco_P::Tilt::Down,  m_nSpeed  );
			break;
	}
	UnPackMessage(  );
}

void  CStageLens::BottomLeft(  UINT  deviceAddress  )
{
	switch  (  Protocol_ID  )  {
		case  PELCO_D:
			Message  =  Pelco_D.CameraPanTilt(  deviceAddress,  Pelco_D_Protocol::CPelco_D::Pan::Left,  m_nSpeed,  Pelco_D_Protocol::CPelco_D::Tilt::Down,  m_nSpeed  );  
			break;
		case  PELCO_P:
			Message  =  Pelco_P.CameraPanTilt(  deviceAddress  -  1,  Pelco_P_Protocol::CPelco_P::Pan::Left,  m_nSpeed,  Pelco_P_Protocol::CPelco_P::Tilt::Down,  m_nSpeed  );
			break;
	}
	UnPackMessage(  );
}

void  CStageLens::Left(  UINT  deviceAddress  )
{
	switch  (  Protocol_ID  )  {
		case  PELCO_D:
			Message  =  Pelco_D.CameraPan(  deviceAddress,  Pelco_D_Protocol::CPelco_D::Pan::Left,  m_nSpeed  );  
			break;
		case  PELCO_P:
			Message  =  Pelco_P.CameraPan(  deviceAddress  -  1,  Pelco_P_Protocol::CPelco_P::Pan::Left,  m_nSpeed  );
			break;
	}
	UnPackMessage(  );
}

void  CStageLens::TopLeft(  UINT  deviceAddress  )
{
	switch  (  Protocol_ID  )  {
		case  PELCO_D:
			Message  =  Pelco_D.CameraPanTilt(  deviceAddress,  Pelco_D_Protocol::CPelco_D::Pan::Left,  m_nSpeed,  Pelco_D_Protocol::CPelco_D::Tilt::Up,  m_nSpeed  );  
			break;
		case  PELCO_P:
			Message  =  Pelco_P.CameraPanTilt(  deviceAddress  -  1,  Pelco_P_Protocol::CPelco_P::Pan::Left,  m_nSpeed,  Pelco_P_Protocol::CPelco_P::Tilt::Up,  m_nSpeed  );
			break;
	}
	UnPackMessage(  );
}

void  CStageLens::AutoScan(  UINT  deviceAddress  )
{
	switch  (  Protocol_ID  )  {
		case  PELCO_D:
			Message  =  Pelco_D.CameraScan(  deviceAddress,  Pelco_D_Protocol::CPelco_D::Scan::Scan_Auto  );  
			break;
		case  PELCO_P:
			Message  =  Pelco_P.CameraScan(  deviceAddress  -  1,  Pelco_P_Protocol::CPelco_P::Scan::Scan_Auto  );
			break;
	}
	UnPackMessage(  );
}

void  CStageLens::ManualScan(  UINT  deviceAddress  )
{
	switch  (  Protocol_ID  )  {
		case  PELCO_D:
			Message  =  Pelco_D.CameraScan(  deviceAddress,  Pelco_D_Protocol::CPelco_D::Scan::Scan_Manual  );  
			break;
		case  PELCO_P:
			Message  =  Pelco_P.CameraScan(  deviceAddress  -  1,  Pelco_P_Protocol::CPelco_P::Scan::Scan_Manual  );
			break;
	}
	UnPackMessage(  );
}

void  CStageLens::FocusPlus(  UINT  deviceAddress  )
{
	switch  (  Protocol_ID  )  {
		case  PELCO_D:
			Message  =  Pelco_D.CameraFocus(  deviceAddress,  Pelco_D_Protocol::CPelco_D::Focus::Near  );  
			break;
		case  PELCO_P:
			Message  =  Pelco_P.CameraFocus(  deviceAddress  -  1,  Pelco_P_Protocol::CPelco_P::Focus::Near  );
			break;
	}
	UnPackMessage(  );
}

void  CStageLens::FocusMinus(  UINT  deviceAddress  )
{
	switch  (  Protocol_ID  )  {
		case  PELCO_D:
			Message  =  Pelco_D.CameraFocus(  deviceAddress,  Pelco_D_Protocol::CPelco_D::Focus::Far  );  
			break;
		case  PELCO_P:
			Message  =  Pelco_P.CameraFocus(  deviceAddress  -  1,  Pelco_P_Protocol::CPelco_P::Focus::Far  );
			break;
	}
	UnPackMessage(  );
}

void  CStageLens::ZoomPlus(  UINT  deviceAddress  )
{
	switch  (  Protocol_ID  )  {
		case  PELCO_D:
			Message  =  Pelco_D.CameraZoom(  deviceAddress,  Pelco_D_Protocol::CPelco_D::Zoom::Wide  );  
			break;
		case  PELCO_P:
			Message  =  Pelco_P.CameraZoom(  deviceAddress  -  1,  Pelco_P_Protocol::CPelco_P::Zoom::Wide  );
			break;
	}
	UnPackMessage(  );
}

void  CStageLens::ZoomMinus(  UINT  deviceAddress  )
{
	switch  (  Protocol_ID  )  {
		case  PELCO_D:
			Message  =  Pelco_D.CameraZoom(  deviceAddress,  Pelco_D_Protocol::CPelco_D::Zoom::Tele  );  
			break;
		case  PELCO_P:
			Message  =  Pelco_P.CameraZoom(  deviceAddress  -  1,  Pelco_P_Protocol::CPelco_P::Zoom::Tele  );
			break;
	}
	UnPackMessage(  );
}


void  CStageLens::IrisPlus(  UINT  deviceAddress  )
{
	switch  (  Protocol_ID  )  {
		case  PELCO_D:
			Message  =  Pelco_D.CameraIrisSwitch(  deviceAddress,  Pelco_D_Protocol::CPelco_D::Iris::Open  );  
			break;
		case  PELCO_P:
			Message  =  Pelco_P.CameraIrisSwitch(  deviceAddress  -  1,  Pelco_P_Protocol::CPelco_P::Iris::Open  );
			break;
	}
	UnPackMessage(  );
}

void  CStageLens::IrisMinus(  UINT  deviceAddress  )
{
	switch  (  Protocol_ID  )  {
		case  PELCO_D:
			Message  =  Pelco_D.CameraIrisSwitch(  deviceAddress,  Pelco_D_Protocol::CPelco_D::Iris::Close  );  
			break;
		case  PELCO_P:
			Message  =  Pelco_P.CameraIrisSwitch(  deviceAddress  -  1,  Pelco_P_Protocol::CPelco_P::Iris::Close  );
			break;
	}
	UnPackMessage(  );
}

void  CStageLens::SearchLightOn(  UINT  deviceAddress  )
{
	switch  (  Protocol_ID  )  {
		case  PELCO_D:
			Message  =  Pelco_D.SetAuxiliary(  deviceAddress,  3,  Pelco_D_Protocol::CPelco_D::AuxAction::AuxAction_Set  );  
			break;
		case  PELCO_P:
			Message  =  Pelco_P.SetAuxiliary(  deviceAddress  -  1,  3,  Pelco_P_Protocol::CPelco_P::AuxAction::AuxAction_Set  );
			break;
	}
	UnPackMessage(  );
}

void  CStageLens::SearchLightOff(  UINT  deviceAddress  )
{
	switch  (  Protocol_ID  )  {
		case  PELCO_D:
			Message  =  Pelco_D.SetAuxiliary(  deviceAddress,  3,  Pelco_D_Protocol::CPelco_D::AuxAction::AuxAction_Clear  );  
			break;
		case  PELCO_P:
			Message  =  Pelco_P.SetAuxiliary(  deviceAddress  -  1,  3,  Pelco_P_Protocol::CPelco_P::AuxAction::AuxAction_Clear  );
			break;
	}
	UnPackMessage(  );
}

void  CStageLens::RainBrushOn(  UINT  deviceAddress  )
{
	switch  (  Protocol_ID  )  {
		case  PELCO_D:
			Message  =  Pelco_D.SetAuxiliary(  deviceAddress,  4,  Pelco_D_Protocol::CPelco_D::AuxAction::AuxAction_Set  );  
			break;
		case  PELCO_P:
			Message  =  Pelco_P.SetAuxiliary(  deviceAddress  -  1,  4,  Pelco_P_Protocol::CPelco_P::AuxAction::AuxAction_Set  );
			break;
	}
	UnPackMessage(  );
}

void  CStageLens::RainBrushOff(  UINT  deviceAddress  )
{
	switch  (  Protocol_ID  )  {
		case  PELCO_D:
			Message  =  Pelco_D.SetAuxiliary(  deviceAddress,  4,  Pelco_D_Protocol::CPelco_D::AuxAction::AuxAction_Clear  );  
			break;
		case  PELCO_P:
			Message  =  Pelco_P.SetAuxiliary(  deviceAddress  -  1,  4,  Pelco_P_Protocol::CPelco_P::AuxAction::AuxAction_Clear  );
			break;
	}
	UnPackMessage(  );
}

void  CStageLens::Noop(  UINT  deviceAddress  )
{
	switch  (  Protocol_ID  )  {
		case  PELCO_D:
			Message  =  Pelco_D.Noop(  deviceAddress  );  
			break;
		case  PELCO_P:
			Message  =  Pelco_P.Noop(  deviceAddress  -  1  );
			break;
	}
	UnPackMessage(  );
}

void  CStageLens::PreSet(  UINT  deviceAddress,  BYTE  preset,  PresetAction  action  )
{
	switch  (  Protocol_ID  )  {
		case  PELCO_D:
			if  (  action  ==  PresetAction_Set  )
				Message  =  Pelco_D.Preset(  deviceAddress,  preset,  Pelco_D_Protocol::CPelco_D::PresetAction_Set  );
			if  (  action  ==  PresetAction_Clear  )
				Message  =  Pelco_D.Preset(  deviceAddress,  preset,  Pelco_D_Protocol::CPelco_D::PresetAction_Clear  );
			if  (  action  ==  PresetAction_Goto  )
				Message  =  Pelco_D.Preset(  deviceAddress,  preset,  Pelco_D_Protocol::CPelco_D::PresetAction_Goto  );
			break;
		case  PELCO_P:
			if  (  action  ==  PresetAction_Set  )
				Message  =  Pelco_P.Preset(  deviceAddress  -  1,  preset,  Pelco_P_Protocol::CPelco_P::PresetAction_Set  );
			if  (  action  ==  PresetAction_Clear  )
				Message  =  Pelco_P.Preset(  deviceAddress  -  1,  preset,  Pelco_P_Protocol::CPelco_P::PresetAction_Clear  );
			if  (  action  ==  PresetAction_Goto  )
				Message  =  Pelco_P.Preset(  deviceAddress  -  1,  preset,  Pelco_P_Protocol::CPelco_P::PresetAction_Goto  );
			break;
	}
	UnPackMessage(  );
}

void  CStageLens::Pattern(  UINT  deviceAddress,  PatternAction  action  )
{
	switch  (  Protocol_ID  )  {
		case  PELCO_D:
			if  (  action  ==  PatternAction_Start  )
				Message  =  Pelco_D.Pattern(  deviceAddress,  Pelco_D_Protocol::CPelco_D::PatternAction_Start  );
			if  (  action  ==  PatternAction_Stop  )
				Message  =  Pelco_D.Pattern(  deviceAddress,  Pelco_D_Protocol::CPelco_D::PatternAction_Stop  );
			if  (  action  ==  PatternAction_Run  )
				Message  =  Pelco_D.Pattern(  deviceAddress,  Pelco_D_Protocol::CPelco_D::PatternAction_Run  );
			break;
		case  PELCO_P:
			if  (  action  ==  PatternAction_Start  )
				Message  =  Pelco_P.Pattern(  deviceAddress  -  1,  Pelco_P_Protocol::CPelco_P::PatternAction_Start  );
			if  (  action  ==  PatternAction_Stop  )
				Message  =  Pelco_P.Pattern(  deviceAddress  -  1,  Pelco_P_Protocol::CPelco_P::PatternAction_Stop  );
			if  (  action  ==  PatternAction_Run  )
				Message  =  Pelco_P.Pattern(  deviceAddress  -  1,  Pelco_P_Protocol::CPelco_P::PatternAction_Run  );
			break;
	}
	UnPackMessage(  );
}