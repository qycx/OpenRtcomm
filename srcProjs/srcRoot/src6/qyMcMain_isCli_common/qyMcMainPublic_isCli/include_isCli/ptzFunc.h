
#ifndef  __ptzFunc_h__
#define  __ptzFunc_h__	//  {

//
#define		CONST_ptzType_null						0
#define		CONST_ptzType_usb						1
#define		CONST_ptzType_serialPort				2
//
#define		CONST_ptzType_ipc						3

//
#define		DEFAULT_ptzType							CONST_ptzType_ipc	//  CONST_ptzType_usb


//
//  2015/09/20
#define		CONST_camType_null						0
#define		CONST_camType_conf						1
#define		CONST_camType_dynBmp					2



//
int getPtzCmdByResourceId(int nResourceID);

//
__declspec(dllexport)  int  sendPtzReq(unsigned  int  uiObjType, unsigned  short  usIndex_obj, unsigned  short  usHelp_subIndex, QY_MESSENGER_ID  idInfo, int iChannel, unsigned  char  ucCmd, unsigned  char  ucParam, unsigned  char  ucMouseStatus, PTZ_cmdParamU  *  pParam,  QY_MESSENGER_ID  idInfo_imGrp_related, QY_MESSENGER_ID idInfo_to);



//
//
void dlg_YTCmd(HWND  hDlg_ptz, int  nResourceID, int  lStep_percent, unsigned  char ucMouseStatus, int  iChannel, PTZ_control_cmd  *  pPtzControlCmd);
//
void dlg_YTCHECKBtn(HWND  hDlg, int  nResourceID);



//
void dlg_YTCmd_usb(  HWND  hDlg_ptz,  int  nResourceID  );
void dlg_YTCmd_pelco(  HWND  hDlg_ptz,  int  nResourceID  );
void dlg_YTCmd_ipc(HWND  hDlg_ptz, int  iChannel,  int  ptzCmd, unsigned  char  ucMouseStatus);






#endif  //  }



