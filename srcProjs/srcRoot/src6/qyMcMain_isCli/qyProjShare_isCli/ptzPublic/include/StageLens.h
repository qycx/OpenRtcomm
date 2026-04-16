//
#include	"Pelco_D.h"
#include	"Pelco_P.h"

#ifndef  STAGELENS_H
#define  STAGELENS_H

//
#include	"ptzCommProc.h"

class  CStageLens
{
	public:
		CStageLens()  {  Protocol_ID  =  PELCO_D;  };
		~CStageLens()  {};
	public:
		enum  PROTOCOL  {
			PELCO_D		=	CONST_ptzProto_PELCO_D,
			PELCO_D_1	=	CONST_ptzProto_PELCO_D_1,
			PELCO_P		=	CONST_ptzProto_PELCO_P,
			PELCO_P_1	=	CONST_ptzProto_PELCO_P_1,
			PELCO_P_2	=	CONST_ptzProto_PELCO_P_2,
			XENON		=	CONST_ptzProto_XENON,
			PICO2000	=	CONST_ptzProto_PICO2000,
			PICASO		=	CONST_ptzProto_PICASO,
			KODICOM_RX	=	CONST_ptzProto_KODICOM_RX,
			KODICOM_KRE	=	CONST_ptzProto_KODICOM_KRE,
			KALATAL		=	CONST_ptzProto_KALATAL,
			VICON		=	CONST_ptzProto_VICON,
			SCANDOME_II	=	CONST_ptzProto_SCANDOME_II,
		};
		enum  PresetAction {  PresetAction_Set,  PresetAction_Clear,  PresetAction_Goto  };
		enum  PatternAction  {  PatternAction_Start,  PatternAction_Stop,  PatternAction_Run  };

	public:
		void  SetSpeed( int  nSpeed  = 0x17 )  {  m_nSpeed  =  nSpeed;  }
		void  SetProtocol(  PROTOCOL  Protocol  );
		void  Up(  UINT  deviceAddress  );
		void  TopRight(  UINT  deviceAddress  );
		void  Right(  UINT  deviceAddress  );
		void  BottomRight(  UINT  deviceAddress  );
		void  Down(  UINT  deviceAddress  );
		void  BottomLeft(  UINT  deviceAddress  );
		void  TopLeft(  UINT  deviceAddress  );
		void  Left(  UINT  deviceAddress  );
		void  AutoScan(  UINT  deviceAddress  );
		void  ManualScan(  UINT  deviceAddress  );
		void  FocusPlus(  UINT  deviceAddress  );
		void  FocusMinus(  UINT  deviceAddress  );
		void  ZoomPlus(  UINT  deviceAddress  );
		void  ZoomMinus(  UINT  deviceAddress  );
		void  IrisPlus(  UINT  deviceAddress  );
		void  IrisMinus(  UINT  deviceAddress  );
		void  SearchLightOn(  UINT  deviceAddress  );
		void  SearchLightOff(  UINT  deviceAddress  );
		void  RainBrushOn(  UINT  deviceAddress  );
		void  RainBrushOff(  UINT  deviceAddress  );
		void  Noop(  UINT  deviceAddress  );
		void  PreSet(  UINT  deviceAddress,  BYTE  preset,  PresetAction  action  );
		void  Pattern(  UINT  deviceAddress,  PatternAction  action  );
	private:
		void  UnPackMessage(  void  );
	private:
		PROTOCOL  Protocol_ID; 
		Pelco_D_Protocol::CPelco_D  Pelco_D; 
		Pelco_P_Protocol::CPelco_P  Pelco_P; 
	public:
		int  m_nSpeed;
		BYTE  *Message;
		UINT  Len;	

		//
		void  *  pDlgPtzControl;
};
#endif