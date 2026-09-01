

#include	"stdafx.h"
#include	"resource.h"
#include	"qyVDevProc.h"


 __declspec(  dllexport  )  int  cusDlgRes(  void  *  p0,  void  *  pQnmCusResInfo,  HWND  hDlg,  int  IDD  );


 //  fullPhoneNo_to表示国家区号+手机号
 //
 int  mySendMsg_vDevComs(  LPCTSTR  msgStr,  char  *  fullPhoneNo_to,  unsigned  int  uiComIndex,  HWND  hWnd_notify,  int  iUsrData  )
{
	 int					iErr		=	-1;
	 IM_SM_PKT				content;
	 IM_SM_PKT			*	pContent	=	&content;
	 int					len			=	0;
	 CString				strNumber;
	 char					buf[2048]	=	"";

	 
	 if  (  !msgStr  ||  !fullPhoneNo_to  )  return  -1;

	 strNumber  =  fullPhoneNo_to;

#define		CONST_minPhoneNoLen		6		
	 if  (  strNumber.GetLength(  )  <=  CONST_minPhoneNoLen  )  {	//  这里的长度是因为下面要取3个数。
		 TRACE(  _T(  "Value error, strNumber is [%s]"  ),  strNumber  );
		 return  -1;
	 }
	 //
	 memset(  &content,  0,  sizeof(  content  )  );
	 //
	 pContent->uiType  =  CONST_imCommType_smPkt;
	 //
	 // 去掉号码前的"+"
	 if  (  strNumber[0]  == '+'  )  strNumber  =  strNumber.Mid(  1  );

	 // 在号码前加"86"
	 //  if  (  strNumber.Left(2)  !=  "86"  )  strNumber = "86" + strNumber;
		
	 // 填充短消息结构
	 //  if  (  !myTChar2Utf8(  strSmsc,  pContent->smPkt.SCA,  mycountof(  pContent->smPkt.SCA  )  )  )  goto  errLabel;
	 if  (  !myTChar2Utf8(  strNumber,  pContent->smPkt.TPA,  mycountof(  pContent->smPkt.TPA  )  )  )  goto  errLabel;
	 //
	 lstrcpyn(  pContent->smPkt.TP_UD,  msgStr,  mycountof(  pContent->smPkt.TP_UD  )  );
	 //
	 pContent->smPkt.TP_PID = 0;
	 pContent->smPkt.TP_DCS = GSM_UCS2;
	
	 //  2008/11/25
	 pContent->hWnd_notify  =  hWnd_notify;
	 pContent->iUsrData  =  iUsrData;

	 //
	 postMsg2Mgr_vDevComs(  pVDev,  CONST_misMsgType_talk,  uiComIndex,  (  char  *  )&content,  sizeof(  content  )  );
 

	 iErr  =  0;
errLabel:	 
	 return  iErr;
}


 int  postMsg2Mgr_vDevComs(  void  *  pVDevParam,  unsigned  int  uiMsgType,  unsigned  int  uiComIndex,  char  *  data,  unsigned  int  dataLen  )
{
	 int					iErr			=		-1;
	 CQyVDevComs		*	pVDev			=		(  CQyVDevComs  *  )pVDevParam;
	 CQyMalloc				mallocObj;
	 MIS_MSGU			*	pMsg			=		(  MIS_MSGU  *  )mallocObj.malloc(  sizeof(  MIS_MSGU  )  );
	 if  (  !pMsg  )  return  -1;
	 unsigned  int			len				=		0;

	 if  (  !pVDev  )  return  -1;

	 memset(  pMsg,  0,  sizeof(  pMsg[0]  )  );
	 pMsg->uiType  =  uiMsgType;
	 switch  (  pMsg->uiType  )  {
			 case  CONST_misMsgType_input:			
				   pMsg->input.uiCliIndex  =  uiComIndex;
				   //
				   pMsg->input.lenInBytes  =  min(  sizeof(  pMsg->input.data  ),  dataLen  );
				   memcpy(  &pMsg->input.data,  data,  pMsg->input.lenInBytes  );
				   len  =  pMsg->input.lenInBytes  +  offsetof(  MIS_MSG_INPUT,  data  );
				   break;
	         case  CONST_misMsgType_sendFinished:
				   pMsg->sendFinished.uiCliIndex  =  uiComIndex;
				   //
				   len  =  sizeof(  pMsg->sendFinished  );
				   break;
			 case  CONST_misMsgType_talk:
				   pMsg->talk.uiCliIndex  =  uiComIndex;
	 			   //
				   len  =  min(  sizeof(  pMsg->talk.data.buf  ),  dataLen  );
				   memcpy(  &pMsg->talk.data.buf,  data,  len  );
	 			   pMsg->talk.lenInBytes  =  len  +  offsetof(  MIS_MSG_routeTalkData,  buf  );
				   len  =  pMsg->talk.lenInBytes  +  offsetof(  MIS_MSG_TALK,  data  );
				   break;	
			 default:
					goto  errLabel;
					
	 }

	 //  printMisMsg(  0,  0,  &msg  );

	 if  (  qPostMsgAndTrigger(  pMsg,  len,  &pVDev->m_var.mgrQ  )  )  goto  errLabel;

	 iErr  =  0;
errLabel:
	 return  iErr;
}



 LRESULT CALLBACK dlgProc_qyTest(  HWND  hDlg,  UINT  message,  WPARAM  wParam,  LPARAM  lParam  )
{
	TCHAR			tBuf[256]	=	_T(  ""  );
	int				iCurIndex	=	0;
	char			buf[256]	=	"";
	CComPort	*	pCurPort	=	NULL;


	iCurIndex  =  pVDev->m_var.iCurIndex;
	if  (  !bComIndexValid(  pVDev,  iCurIndex  )  )  {
		EndDialog(  hDlg,  -1  );
		return  TRUE;
	}
	pCurPort  =  &pVDev->m_var.pPorts[iCurIndex];

	switch  (  message)  {
			case  WM_INITDIALOG:

				  //  SetWindowPos(  hDlg,  HWND_TOPMOST,  0,  0,  0,  0,  SWP_NOMOVE  |  SWP_NOSIZE  );

				  cusDlgRes(  0,  &pVDev->m_var.cusRes,  hDlg,  IDD_qyTest  );

				  SetDlgItemText(  hDlg,  IDC_EDIT_countryCode,  _T(  "86"  )  );
				  
				  pVDev->m_var.common.hWnd_test  =  hDlg;
				  //
				  pCurPort->setOwnerWnd(  hDlg  );

				  return TRUE;
			case  WM_COMMAND:
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "id %d"  ),  LOWORD(  wParam  )  );
				  if  (  LOWORD(  wParam  )  ==  IDOK  )  {
					  traceLogA(  "这里，就是要将edit里的信息发到com里去"  );
					  
					  GetDlgItemText(  hDlg,  IDC_EDIT_input, tBuf, mycountof(tBuf));
					  if  (  !tBuf[0]  )  return  TRUE;
					  if  (  !myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  )  )  return  TRUE;
					  if  (  strlen(  buf  )  ==  mycountof(  buf  )  -  2  )  {
						  MessageBox(  NULL,  _T(  "Too much characters."  ),  _T(  ""  ),  MB_OK  );
						  return  TRUE;
					  }
					  _snprintf(  buf,  mycountof(  buf  ),  "%s\r\n",  buf  );		//  追加一个回车
					  
					  pCurPort->WriteToPort(buf);	

					  SetDlgItemText(  hDlg,  IDC_EDIT_input,  _T(  ""  )  );
					  return  TRUE;
				  }

				  if  (  LOWORD(  wParam  )  ==  IDC_BUTTON_sendToPhone  )  {
					  char		phoneNoBuf[32  +  1]	=	"";
					  char		countryCode[32  +  1]	=	"";
					  TCHAR		tInput[256]				=	_T(  ""  );
					  //
					  //
					  GetDlgItemText(  hDlg,  IDC_EDIT_input,  tInput,  mycountof(  tInput  )  );
					  if  (  !tInput[0]  )  return  TRUE;
					  GetDlgItemText(  hDlg,  IDC_EDIT_countryCode,  tBuf,  mycountof(  tBuf  )  );
					  myTChar2Str(  tBuf,  countryCode,  mycountof(  countryCode  )  );
					  trim(  countryCode  );  
					  if  (  !countryCode[0]  )  return  TRUE;
					  GetDlgItemText(  hDlg,  IDC_EDIT_phoneNo,  tBuf,  mycountof(  tBuf  )  );
					  myTChar2Str(  tBuf,  phoneNoBuf,  mycountof(  phoneNoBuf  )  );
					  trim(  phoneNoBuf  );
					  if  (  !phoneNoBuf[0]  )  return  TRUE;
					  _snprintf(  buf,  mycountof(  buf  ),  "%s%s",  countryCode,  phoneNoBuf  );
					  //  这里应该用pdu格式来发送了
					  mySendMsg_vDevComs(  tInput,  buf,  iCurIndex,  NULL,  0  );
					  return  TRUE;
				  }

				  if  (  LOWORD(  wParam  )  ==  IDC_BUTTON_clear  )  {
					  SendMessage(  GetDlgItem(  hDlg,  IDC_LIST_talk  ),  LB_RESETCONTENT,  0,  0  );
					  SetFocus(  GetDlgItem(  hDlg,  IDC_EDIT_input  )  );
					  return  TRUE;
				  }

				  if  (  LOWORD(  wParam  )  ==  IDC_BUTTON_restart  )  {
					  TCHAR		szPort[32]  =  _T(  ""  );
					  BOOL		bGsmModem	=	FALSE;
					  //
					  CQySyncObj	syncObj;
					  //
					  if  (  syncObj.sync(  CONST_str_syncGsmModemInit  )  )  {	
						  traceLogA(  "sync failed"  );							//  failed其实也不影响的，所以不做处理
					  }
					  //
					  pCurPort->StopMonitoring(  );					  	
					  _sntprintf(  szPort,  mycountof(  szPort  ),  _T(  "\\\\.\\COM%d"  ),  pCurPort->m_var.nPortNo  );
					  if  (  bInitGsmModem(  szPort,  pCurPort->m_var.baud,  NULL,  &bGsmModem,  NULL,  0,  NULL,  0,  hDlg,  pCurPort->m_var.nPortNo  )  
						  &&  bGsmModem  )  
					  {
						  pCurPort->InitPort(  pVDev  );
						  pCurPort->StartMonitoring(  );
					  }
					  //
					  return  TRUE;
				  }
		 	
				  if  (  LOWORD(wParam) == IDOK1 || LOWORD(wParam) == IDCANCEL  )  {
					  EndDialog(hDlg, LOWORD(wParam));
					  return TRUE;
				  }
				  break;
			case  WM_COMM_CTS_DETECTED:  {
				  unsigned  int		uiComIndex;
				  long				cnt;
				  //
				  uiComIndex  =  lParam;		
				  //
				  if  (  !bComIndexValid(  pVDev,  uiComIndex  )  )  return  TRUE;

				  if  (  0  )  {
					  CString	str;
					  str  =  _T(  "Clear To Send"  );

					  SendMessage(  GetDlgItem(  hDlg,  IDC_LIST_talk  ),  LB_ADDSTRING,  0,  (  LPARAM  )str.GetBuffer(  0  )  );
					  cnt  =  SendMessage(  GetDlgItem(  hDlg,  IDC_LIST_talk  ),  LB_GETCOUNT,  0,  0  );
					  if  (  cnt  >=  1  )  SendMessage(  GetDlgItem(  hDlg,  IDC_LIST_talk  ),  LB_SETCURSEL,  cnt  -  1,  0  );
				  }

				  }

				  return  TRUE;
				  break;
			case  CONST_wmComm_EV_RXCHAR:  {
				  unsigned  int		uiComIndex;
				  long				cnt;
				  CString			str;

				  uiComIndex  =  lParam;
				  str  =  (  LPCTSTR  )wParam;
				  //
				  if  (  !bComIndexValid(  pVDev,  uiComIndex  )  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  _T(  "Gsm Modems: "  )  );
				  else  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "COM%d: "  ),  uiComIndex  +  1  );
				  //
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s"  ),  tBuf,  str.GetBuffer(  0  )  );
				  
				  SendMessage(  GetDlgItem(  hDlg,  IDC_LIST_talk  ),  LB_ADDSTRING,  0,  (  LPARAM  )tBuf  );
				  cnt  =  SendMessage(  GetDlgItem(  hDlg,  IDC_LIST_talk  ),  LB_GETCOUNT,  0,  0  );
				  if  (  cnt  >=  1  )  SendMessage(  GetDlgItem(  hDlg,  IDC_LIST_talk  ),  LB_SETCURSEL,  cnt  -  1,  0  );
				
				  }

				  return  TRUE;
				  break;
			default:
					break;	
	}

	return  FALSE;

}

 BOOL  bComIndexValid(  CQyVDevComs  *  pVDev,  unsigned  int  uiComIndex  )
{
	 return  (  pVDev->m_var.cfg.uiMaxComs  >  uiComIndex  );
}

 BOOL  bComPortSending(  CQyVDevComs  *  pVDev,  unsigned  int  uiComIndex  )
{
	 if  (  bComIndexValid(  pVDev,  uiComIndex  )  )  {
		 COM_BUF_O  *  pO  =  &pVDev->m_var.pBufOs[uiComIndex];
		 if  (  pO->ucbToSendCmd  )  return  TRUE;
	 }
	 return  FALSE;
}


//  2008/11/25, 将响应参数填入pPort中
//	 pPort->m_var.hWnd_notify  =  pContent->hWnd_notify;
//	 pPort->m_var.iSmParam  =  pContent->iSmParam;

 int  mySendCmd(  int  uiComIndex,  char  *  cmd,  char  *  pdu,  char  *  phoneNo_to_sending,  HWND  hWnd_notify,  int  iUsrData  )
{
	 int				iErr				=	-1;
	 COM_BUF_O		*	pO					=	0;

	 if  (  !bComIndexValid(  pVDev,  uiComIndex  )  )  return  -1;

	 pO  =  &pVDev->m_var.pBufOs[uiComIndex];

	 safeStrnCpy(  cmd,  pO->cmd,  mycountof(  pO->cmd  )  );
	 safeStrnCpy(  pdu,  pO->pdu,  mycountof(  pO->pdu  )  );
	 //
	 if  (  phoneNo_to_sending[0]  )  safeStrnCpy(  phoneNo_to_sending,  pO->phoneNo_to_sending,  mycountof(  pO->phoneNo_to_sending  )  );	//  这个存起来，是为了能在后续消息来时，用这个来查找发往同一个号的消息

	 //  2008/11/25
	 pVDev->m_var.pPorts[uiComIndex].m_var.hWnd_notify  =  hWnd_notify;
	 pVDev->m_var.pPorts[uiComIndex].m_var.iUsrData  =  iUsrData;

	 time(  &pO->tLastCmdStart  );

	 if  (  pVDev->m_var.pPorts[uiComIndex].WriteToPort(  pO->cmd  )  )  goto  errLabel;

	 pO->ucbToSendCmd  =  TRUE;
	 iErr  =  0;
errLabel:
	 return  iErr;
}

 int  tryToSend(  int  uiComIndex  )
{
	 int				iErr				=	-1;
	 IM_SM_PKT		*	pContent			=	NULL;
	 //
	 CComPort		*	pPort				=	NULL;
	 COM_BUF_O		*	pO					=	0;
	 //
	 CQyMalloc			mallocObj;
	 MIS_MSGU		*	pMsg				=	(  MIS_MSGU  *  )mallocObj.malloc(  sizeof(  MIS_MSGU  )  );
	 if  (  !pMsg  )  return  -1;
	 int				len					=	0;
	 GENERIC_Q		*	pOutputQ			=	NULL;
	 //
	 char				cmd[256]			=	"";		//  命令串
	 //
	 int				nPduLength			=	0;		//  PDU串长度
	 unsigned  char		nSmscLength			=	0;		//  SMSC串长度
	 char				pdu[512]			=	"";		//  PDU串
	 //
	 HWND				hWnd_notify			=	NULL;	//  2008/11/25
	 int				iUsrData			=	0;


	 traceLogA(  "doIsMgr_talk enters"  );

	 if  (  !bComIndexValid(  pVDev,  uiComIndex  )  )  return  -1;

	 if  (  bComPortSending(  pVDev,  uiComIndex  )  )  return  0;		//  如果还在发送，那么就返回。等以后有空了再发

	 pPort  =  &pVDev->m_var.pPorts[uiComIndex];
	 pO  =  &pVDev->m_var.pBufOs[uiComIndex];

	 //  应该在这里加入对一个串接后续包的发送工作。
	 pContent  =  (  IM_SM_PKT  *  )&pO->imSmPkt;
	 if  (  pContent->smPkt.tpUdhU.concatenatedSm.ucMaxNum  )  {
		 if  (  pContent->smPkt.tpUdhU.concatenatedSm.ucSeqNo  <  pContent->smPkt.tpUdhU.concatenatedSm.ucMaxNum  )  {

			 if  (  (  nPduLength  =  gsmEncodePdu(  &pContent->smPkt,  (  unsigned  char  *  )pdu,  mycountof(  pdu  )  )  )  <  0  )  goto  errLabel;	//  根据PDU参数，编码PDU串
			 strcat(pdu, "\x01a");		// 以Ctrl-Z结束

			 gsmString2Bytes(  (  const  unsigned  char  *  )pdu, &nSmscLength, 2);	// 取PDU串中的SMSC信息长度
			 nSmscLength++;		// 加上长度字节本身

			 // 命令中的长度，不包括SMSC信息长度，以数据字节计
			 _snprintf(  cmd,  mycountof(  cmd  ),  "AT+CMGS=%d\r",  nPduLength / 2 - nSmscLength   );	// 生成命令
			 //
			 traceLogA(  "%s",  cmd  );
			 traceLogA(  "%s",  pdu  );
			 //
			 if  (  pContent->smPkt.tpUdhU.concatenatedSm.ucSeqNo  ==  pContent->smPkt.tpUdhU.concatenatedSm.ucMaxNum  -  1  )  {	//  最后一个分片。2008/11/25
				 hWnd_notify  =  pContent->hWnd_notify;
				 iUsrData  =  pContent->iUsrData;
			 }
			 //
			 if  (  mySendCmd(  uiComIndex,  cmd,  pdu,  pContent->smPkt.TPA,  hWnd_notify,  iUsrData  )  )  goto  errLabel;	 

			 iErr  =  0;  goto  errLabel;
		 }
	 }

	 //  对于全新的消息，应该将缓存数据都清空。
	 memset(  pO,  0,  sizeof(  pO[0]  )  );

	 //  先看是否有要删除的，如有，则先发删除命令
	 memset(  pMsg,  0,  sizeof(  pMsg[0]  )  );
	 len  =  sizeof(  pMsg[0]  );

	 if  (  !qGetMsg(  &pPort->m_var.toBeDelMsgIndexQ,  pMsg,  (  unsigned  int  *  )&len  )  )  {
		 if  (  pMsg->uiType  !=  CONST_misMsgType_applyForWork  )  goto  errLabel;

		 traceLogA(  "将删除index为%d的消息",  pMsg->applyForWork.uiToBeDelMsgIndex  );

		 _snprintf(  cmd,  mycountof(  cmd  ),  "AT+CMGD=%d\r\n", pMsg->applyForWork.uiToBeDelMsgIndex  );	// 生成命令

		 if  (  mySendCmd(  uiComIndex,  cmd,  "",  "",  NULL,  0  )  )  goto  errLabel;

		 iErr  =  0;  goto  errLabel;
	 }	 

	 //////
	 //

	 unsigned  int	ucbMsgGot;	
	 ucbMsgGot	=	FALSE;

	 memset(  pMsg,  0,  sizeof(  pMsg[0]  )  );
	 len  =  sizeof(  pMsg[0]  );

	 //  先到outputQ里去看一下，有的话就发出去。没有的话，再到dataQ里去找一个发		 
	 pOutputQ  =  &pVDev->m_var.pOutputQs[uiComIndex];
	 if  (  !qGetMsg(  pOutputQ,  pMsg,  (  unsigned  int  *  )&len  )  )  ucbMsgGot  =  TRUE;
	 if  (  !ucbMsgGot  )  {
		 len  =  sizeof(  pMsg[0]  );
		 if  (  !qGetMsg(  &pVDev->m_var.dataQ,  pMsg,  (  unsigned  int  *  )&len)  )  ucbMsgGot  =  TRUE;
	 }

	 if  (  !ucbMsgGot  )  {  //没有消息需要发送

		 if  (  pPort->m_var.ucbNewSmArrived  )  {  //  有新消息来了，就发起收命令
			 pPort->m_var.ucbNewSmArrived  =  FALSE;

			 _snprintf(  cmd,  mycountof(  cmd  ),  "AT+CMGL=4\r\n"  );	// 生成命令
			 if  (  mySendCmd(  uiComIndex,  cmd,  "",  "",  NULL,  0  )  )  goto  errLabel;
		 }

		 iErr  =  0;  goto  errLabel;
	 }

	 if  (  pMsg->uiType  !=  CONST_misMsgType_talk  )  {
		 traceLogA(  "tryToSend: Err: msg.uiType [%d] is not msgTalk"  );  goto  errLabel;
	 }
	 
	 pContent  =  (  IM_SM_PKT  *  )&pMsg->talk.data.buf;
	 if  (  pContent->uiType  !=  CONST_imCommType_smPkt  )  goto  errLabel;
	 memcpy(  &pO->imSmPkt,  pContent,  sizeof(  pO->imSmPkt  )  );
	 pContent  =  (  IM_SM_PKT  *  )&pO->imSmPkt;


	 //  将uiComIndex对应的smsc更新到SCA中
	 safeStrnCpy(  pPort->m_var.smscBuf,  pContent->smPkt.SCA,  mycountof(  pContent->smPkt.SCA  )  );

	 // 这里承担在未发送之前的处理数据工作，比如：转换数据字节顺序等
	 
	 if  (  (  nPduLength  =  gsmEncodePdu(  &pContent->smPkt,  (  unsigned  char  *  )pdu,  mycountof(  pdu  )  )  )  <  0  )  goto  errLabel;	//  根据PDU参数，编码PDU串
	 strcat(pdu, "\x01a");		// 以Ctrl-Z结束

	 gsmString2Bytes(  (  const  unsigned  char  *  )pdu, &nSmscLength, 2);	// 取PDU串中的SMSC信息长度
	 nSmscLength++;		// 加上长度字节本身

	 if  (  nPduLength  /  2  <=  nSmscLength  )  goto  errLabel;

	 // 命令中的长度，不包括SMSC信息长度，以数据字节计
	 _snprintf(  cmd,  mycountof(  cmd  ),  "AT+CMGS=%d\r",  nPduLength / 2 - nSmscLength   );	// 生成命令
	 //
	 traceLogA(  "%s",  cmd  );
	 traceLogA(  "%s",  pdu  );
	 
	 //
	 if  (  !pContent->smPkt.tpUdhU.concatenatedSm.ucMaxNum  )  {	//  2008/11/25
		 hWnd_notify  =  pContent->hWnd_notify;
		 iUsrData  =  pContent->iUsrData;
	 }

	 //
	 if  (  mySendCmd(  uiComIndex,  cmd,  pdu,  pContent->smPkt.TPA,  hWnd_notify,  iUsrData  )  )  goto  errLabel;	 

	 iErr  =  0;
errLabel:
	 return  iErr;
}

 //  用pdu格式发出去
 int  doIsMgr_talk_vDevComs(  MIS_MSG_TALK  *  pMsg,  unsigned  int  lenInBytes_msg,  CTX_THREAD_vDev  *  pCtx  )
{
	 int				iErr				=	-1;
	 IM_SM_PKT	*	pContent;
	 //
	 CComPort		*	pPort				=	NULL;
	 COM_BUF_O		*	pO					=	0;
	 unsigned  int		uiComIndex			=	pMsg->uiCliIndex;
	 int				i;

	 traceLogA(  "doIsMgr_talk enters"  );

	 pContent  =  (  IM_SM_PKT  *  )pMsg->data.buf;
	 if  (  pContent->uiType  !=  CONST_imCommType_smPkt  )  goto  errLabel;

	 if  (  !bComIndexValid(  pVDev,  uiComIndex  )  )  {		
		 //
		 //  先搜索一下，是否有未指定的端口可以提供缺省发送。
		 for  (  i  =  0;  i  <  (  int  )pVDev->m_var.cfg.uiMaxComs;  i  ++  )  {
			  pPort  =  &pVDev->m_var.pPorts[i];
			  if  (  !pPort->m_var.ucbStarted  )  continue;
			  if  (  !pPort->m_var.smPolicy.idInfo_contact.ui64Id  )  break;
		 }
		 if  (  !bComIndexValid(  pVDev,  i  )  )  {
			 traceLogA(  "这表明没有空闲的号"  );
			 SendMessage(  pVDev->m_var.common.hWnd_test,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )_T(  "没有空闲的端口可以使用。建议查看短信管理策略，只有未指定策略的端口才能用在本地发送或缺省发送"  ),  -1  );  
			 if  (  pVDev->m_var.common.pGuiOpen->pf_postHint2Mgr_mc_open  )  pVDev->m_var.common.pGuiOpen->pf_postHint2Mgr_mc_open(  &pVDev->m_var.common,  NULL,  0,  0,  _T(  "Failed: 没有空闲的端口可以使用。建议查看短信管理策略，只有未指定策略的端口才能用在本地发送或缺省发送"  )  );
			 //
			 goto  errLabel;
		 }
		 //
		 //  uiComIndex不在有效范围内表不指定的情况，则选择一个有效的COM来发送. 这个被选的端口不能是特服号。
		 //
		 for  (  i  =  0;  i  <  (  int  )pVDev->m_var.cfg.uiMaxComs;  i  ++  )  {	//  先看是否有
			  pPort  =  &pVDev->m_var.pPorts[i];
			  if  (  !pPort->m_var.ucbStarted  )  continue;
			  if  (  pPort->m_var.smPolicy.idInfo_contact.ui64Id  )  continue;		//  不能是特服号。2008/02/10
			  //
			  pO  =  &pVDev->m_var.pBufOs[i];
			  if  (  strcmpi(  pO->phoneNo_to_sending,  pContent->smPkt.TPA  )  )  continue;
			  // 
			  //  有一个相同的号。那么就要准备用这个来发送了。
			  uiComIndex  =  i;  
			  break;
		 }

		 if  (  !bComIndexValid(  pVDev,  uiComIndex  )  )  {	//  如果没有相同的号。那么，就选择一个空闲的
			 for  (  i  =  0;  i  <  (  int  )pVDev->m_var.cfg.uiMaxComs;  i  ++  )  {
				  pPort  =  &pVDev->m_var.pPorts[i];
				  if  (  !pPort->m_var.ucbStarted  )  continue;
				  if  (  pPort->m_var.smPolicy.idInfo_contact.ui64Id  )  continue;	//  不能是特服号。2008/02/10
				  //				  
				  if  (  bComPortSending(  pVDev,  i  )  )  continue;
				  uiComIndex  =  i;
				  break;
			 }
		 }

		 if  (  !bComIndexValid(  pVDev,  uiComIndex  )  )  {	//  这表明所有的端口都忙, 那么就放如dataQ里存起来
			 if  (  qPostMsg(  pMsg,  lenInBytes_msg,  &pVDev->m_var.dataQ  )  )  goto  errLabel;
			 iErr  =  0;  goto  errLabel;
		 }		 
	 }

	 //  放入outputQ
	 if  (  qPostMsg(  pMsg,  lenInBytes_msg,  &pVDev->m_var.pOutputQs[uiComIndex]  )  )  goto  errLabel;
	 
	 if  (  tryToSend(  uiComIndex  )  )  goto  errLabel;

	 iErr  =  0;
errLabel:

	 traceLogA(  "doIsMgr_talk leaves with %s",  iErr  ?  "Err"  :  "Ok"  );

	 return  iErr;
 }


  int  doIsMgr_sendFinished_vDevComs(  MIS_MSG_sendFinished  *  pMsg,  unsigned  int  lenInBytes_msg,  CTX_THREAD_vDev  *  pCtx  )
{
	 int				iErr				=	-1;
	 COM_BUF_O		*	pO					=	0;
	 unsigned  int		uiComIndex			=	pMsg->uiCliIndex;

	 if  (  !bComIndexValid(  pVDev,  uiComIndex  )  )  return  -1;

	 //  traceLogA(  "doIsMgr_sendFinished enters"  );

	 pO  =  &pVDev->m_var.pBufOs[uiComIndex];
		 
	 //  这表明是一个数据包发完了, 
	
	 iErr  =  0;

//  errLabel:

	 //  traceLogA(  "doIsMgr_sendFinished leaves with %s",  iErr  ?  "Err"  :  "Ok"  );

	 return  iErr;
}


 int  tpScts2Display(  char  *  tpScts,  char  *  buf,  unsigned  int  size  )
{
	 if  (  !tpScts  ||  !buf  ||  !size  )  return  -1;
	 char  *  p  =  tpScts;
  	
	 _snprintf(  buf,  size,  "20%.02s - %.02s - %.02s %.02s:%.02s:%.02s",  p,  p  +  2,  p  +  4,  p  +  6,  p  +  8,  p  +  10  );
	 return  0;
}

 int  findToBeDelMsg(  void  *  p0,  void  *  p1,  void  *  pQElem  )
{
	 int			iErr		=	-1;
	 //  void  *	p0
	 MIS_MSGU	*	pMsg		=	(  MIS_MSGU  *  )p1;
	 MIS_MSGU	*	pMsgElem	=	(  MIS_MSGU  *  )pQElem;

	 if  (  !pMsg  ||  !pMsgElem  )  return  -1;

	 if  (  pMsg->uiType  ==  CONST_misMsgType_applyForWork
		 &&  pMsgElem->uiType  ==  CONST_misMsgType_applyForWork  )
	 {
		 if  (  pMsg->applyForWork.uiToBeDelMsgIndex  ==  pMsgElem->applyForWork.uiToBeDelMsgIndex  )  {
			 iErr  =  1;  goto  errLabel;
		 }
	 }

	 iErr  =  0;

errLabel:

	 return  iErr;
}

 int  doIsMgr_input_vDevComs(  MIS_MSG_INPUT  *  pMsg,  unsigned  int  lenInBytes_msg,  CTX_THREAD_vDev  *  pCtx  )
{
	 int					iErr		=	-1;
	 IM_CONTENTU		*	pContent	=	(  IM_CONTENTU  *  )&pMsg->data;
	 CComPort			*	pPort		=	NULL;
	 COM_BUF_O			*	pO			=	NULL;
	 GENERIC_Q			*	pOutputQ	=	NULL;
	 int					len			=	0;
	 int					i;
	 TCHAR					tBuf[2048]	=	_T(  ""  );
	 char					buf[256]	=	"";				

	 traceLogA(  "doIsMgr_input enters"  );
	 
	 if  (  pContent->uiType  ==  CONST_imCommType_vDevComs  )  {

		 if  (  !pContent->vDevComs.ucbResp  )  goto  errLabel;
		 if  (  !isRcOk(  pMsg->usCode  )  )  goto  errLabel;

		 pCtx->bVDevComsReported  =  TRUE;
		 traceLogA(  "得到了服务器的响应OK，COMS状态信息送上去了"  );

		 iErr  =  0;  goto  errLabel;
	 }

	 if  (  pContent->uiType  ==  CONST_imCommType_retrieveSmPolicy  )  {
		 QY_SM_CONTACT	*	pMem;
		 time_t				t;		time(  &t  );
		 unsigned  int		uiComIndex;
		 TCHAR			*	pT;

		 if  (  !pContent->retrieveSmPolicy.ucbResp  )  goto  errLabel;
		 if  (  !isRcOk(  pMsg->usCode  )  )  goto  errLabel;

		 if  (  pContent->retrieveSmPolicy.usCnt  >  mycountof(  pContent->retrieveSmPolicy.mems  )  )  goto  errLabel;

		 memset(  &pVDev->m_var.defaultSmPolicy,  0,  sizeof(  pVDev->m_var.defaultSmPolicy  )  );
		 pVDev->m_var.defaultSmPolicy.ucbDefaultSmServer  =  pContent->retrieveSmPolicy.ucbDefaultSmServer;
		 pVDev->m_var.defaultSmPolicy.tLastModifiedTime  =  t;
		 //
		 for  (  i  =  0;  i  <  pContent->retrieveSmPolicy.usCnt;  i  ++  )  {
			  pMem  =  &pContent->retrieveSmPolicy.mems[i];
			  if  (  !pMem->wDevIdStr[0]  )  {
				  pVDev->m_var.defaultSmPolicy.idInfo_contact.ui64Id  =  pMem->idInfo_contact.ui64Id;
				  pVDev->m_var.defaultSmPolicy.tLastModifiedTime  =  t;
				  continue;
			  }
			  //  下面去可以和szPort相比的设备名称
			  if  (  !(  pT  =  _tcsrchr(  pMem->wDevIdStr,  _T(  '/'  )  )  )  )  continue;
			  pT  ++  ;
			  //
			  for  (  uiComIndex  =  0;  uiComIndex  <  pVDev->m_var.cfg.uiMaxComs;  uiComIndex  ++  )  {
				   pPort  =  &pVDev->m_var.pPorts[uiComIndex];
				   if  (  !_tcsicmp(  pPort->m_var.szPort,  pT  )  )  break;
			  }
			  if  (  !bComIndexValid(  pVDev,  uiComIndex  )  )  continue;
			  //
			  pPort  =  &pVDev->m_var.pPorts[uiComIndex];

			  pPort->m_var.smPolicy.idInfo_contact.ui64Id  =  pMem->idInfo_contact.ui64Id;
			  lstrcpyn(  pPort->m_var.smPolicy.cusName,  pMem->cusName,  mycountof(  pPort->m_var.smPolicy.cusName  )  );
			  pPort->m_var.smPolicy.tLastModifiedTime  =  t;
		 }
		 //  将未刷新的port的smPolicy都清空。
		 for  (  i  =  0;  i  <  (  int  )pVDev->m_var.cfg.uiMaxComs;  i  ++  )  {
			  pPort  =  &pVDev->m_var.pPorts[i];
			  if  (  pPort->m_var.smPolicy.tLastModifiedTime  !=  t  )  memset(  &pPort->m_var.smPolicy,  0,  sizeof(  pPort->m_var.smPolicy  )  );
		 }

		 pCtx->bSmPolicyRetrieved  =  TRUE;
		 traceLogA(  "得到了服务器的响应OK，COM的策略都下载下来了。"  );

		 iErr  =  0;  goto  errLabel;
	 }

	 if  (  pContent->uiType  !=  CONST_imCommType_dataContent  )  {
		 traceLogA(  "doIsMgr_input_vDevComs: 未处理的%d",  pContent->uiType  );
		 goto  errLabel;
	 }
	 
	 char			*	inputStr;
	 unsigned  int		uiComIndex;

	 inputStr  =	(  char  *  )pContent->data.buf;
	 uiComIndex  =  pMsg->uiCliIndex;

	 if  (  !bComIndexValid(  pVDev,  uiComIndex  )  )  goto  errLabel;

	 traceLogA(  "inputStr is [%s]",  inputStr  );
	 
	 pPort  =  &pVDev->m_var.pPorts[uiComIndex];
	 pO  =  &pVDev->m_var.pBufOs[uiComIndex];

	 if  (  pVDev->m_var.common.bDebug  )  {
		 SendMessage(  pVDev->m_var.common.hWnd_test,  CONST_wmComm_EV_RXCHAR,  (  WPARAM  )CString(  CString(  "input: "  )  +  inputStr  ).GetBuffer(  0  ),  pPort->m_var.nPortNo  );
	 }
	 
	 len  =  strlen(  inputStr  );
	 if  (  len  >=  4  )  {
		 if  (  !strnicmp(  inputStr  +  len  -  4,  CONST_gsmResp_readyForPdu,  4  )  )  {
			 //
			 char  cCtrlZ  =  26;
			 //
		 	 if  (  !pO->pdu[0]  ||  pO->pdu[strlen(  pO->pdu  )  -  1]  !=  cCtrlZ  )  {
				 traceLogA(  "这里出错了，发送一个Ctrl+z,已避免死运行"  );
				 _snprintf(  pO->pdu,  mycountof(  pO->pdu  ),  "Test for sending short message%c",  cCtrlZ  );
				 if  (  pO->pdu[strlen(  pO->pdu  )  -  1]  !=  cCtrlZ  )  {
					 traceLogA(  "pdu应该用Ctrl+Z结尾"  );  goto  errLabel;
				 }
			 }
			 //				
			 if  (  pPort->WriteToPort(  pO->pdu  )  )  {
				 traceLogA(  "这时候应该是没有写的，所以就出错了"  );
				 goto  errLabel;
			 }
		 
			 iErr  =  0;  goto  errLabel;
		 }
	 }

	 if  (  !strnicmp(  inputStr,  CONST_gsmRespPhrase_cmgl,  strlen(  CONST_gsmRespPhrase_cmgl  )  )  )  {
		 traceLogA(  "得到一个cmgl响应"  );
		 safeStrnCpy(  inputStr,  pO->lastCmglResp,  mycountof(  pO->lastCmglResp  )  );
		 iErr  =  0;  goto  errLabel;
	 }
	 if  (  !strnicmp(  inputStr,  CONST_gsmPhrase_cmti,  strlen(  CONST_gsmPhrase_cmti  )  )  )  {
		 traceLogA(  "有自动消息来了"  );
		 pPort->m_var.ucbNewSmArrived  =  TRUE;
		 //
		 if  (  tryToSend(  uiComIndex  )  )  goto  errLabel;
		 //
		 iErr  =  0;  goto  errLabel;
	 }
	
	 if  (  !strnicmp(  inputStr,  CONST_gsmResp_ok,  strlen(  CONST_gsmResp_ok  )  )  )  {	
		 pO->ucbToSendCmd  =  FALSE;				//  注意：这里表明命令执行结束了 
		 //
		 traceLogA(  "得到了一个OK响应"  );
		}
	 else  if  (  !strnicmp(  inputStr,  CONST_gsmRespPhrase_err,  strlen(  CONST_gsmRespPhrase_err  )  )  )  {
			   pO->ucbToSendCmd  =  FALSE;			//  注意：这里表明命令执行结束了 
			   //
			   traceLogA(  "得到了错误的提示。"  );
			   goto  errLabel;
			}
	 else  if  (  !strnicmp(  inputStr,  CONST_gsmRespPhrase_pduErr,  strlen(  CONST_gsmRespPhrase_pduErr  )  )  )  {
			   pO->ucbToSendCmd  =  FALSE;			//  注意：这里表明命令执行结束了 
			   //
			   goto  errLabel;
			}
	 else  {
			traceLogA(  "这里应该是新的消息来了或回显。暂时忽略。"  );
			if  (  len  >  6  )  {
				BOOL  bX  =  TRUE;
				for  (  i  =  0;  i  <  5;  i  ++  )  {	//  随便检查一下，如果都是16进制，则认为是消息内容
					 if  (  !isxdigit(  inputStr[i]  )  )  bX  =  FALSE;
				}
				if  (  bX  &&  pO->lastCmglResp[0]  )  {	//  是消息内容
					char			*	p					=	NULL;
					int					iMsgIndex			=	-1;
					SM_PARAM			sm;
					TCHAR				tBuf1[256  +  1]	=	_T(  ""  );
					//
					QY_MESSENGER_ID		idInfo;
					char				idStr[32]			=	"";  
					WCHAR				wDevIdStr[128]		=	_T(  ""  );
					WCHAR				wReversePath[256]	=	_T(  ""  );
					//
					p  =  strchr(  pO->lastCmglResp,  ':'  );
					if  (  p  )  {
						p  ++  ;  trim(  p  );
						iMsgIndex  =  atol(  p  );
					}
					traceLogA(  "iMsgIndex is %d",  iMsgIndex  );
					if  (  iMsgIndex  <  0  )  {
						traceLogA(  "居然没有得到有效的iMsgIndex, 出错了"  );
						goto  errLabel;
					}
					//
					memset(  &sm,  0,  sizeof(  sm  )  );
					gsmDecodePdu(  (  const  unsigned  char  *  )inputStr, &sm  );	// PDU串解码
					//
					traceLogA(  "得到了第%d条的消息内容[%S], TPA is [%s], TP_SCTS is [%s]",  iMsgIndex,  sm.TP_UD,  sm.TPA,  sm.TP_SCTS  );
					//
					buf[0]  =  0;		tpScts2Display(  sm.TP_SCTS,  buf,  mycountof(  buf  )  );
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "From: %s <br>%s<br>%s"  ),  CString(  sm.TPA  ),  CString(  buf  ),  sm.TP_UD  );
					traceLogA(  "%S",  tBuf  );

					//  typedef  int  (  *PF_postStr2Mgr_mc_open  )(  unsigned  int  uiDevType_from,  char  *  devId_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  LPCTSTR  str,  char  *  idStr_to,  unsigned  int  uiChannelType  );

					memset(  &idInfo,  0,  sizeof(  idInfo  )  );
					if  (  pPort->m_var.smPolicy.idInfo_contact.ui64Id  )  idInfo.ui64Id  =  pPort->m_var.smPolicy.idInfo_contact.ui64Id;
					else  if  (  pVDev->m_var.defaultSmPolicy.idInfo_contact.ui64Id  )  idInfo.ui64Id  =  pVDev->m_var.defaultSmPolicy.idInfo_contact.ui64Id;
					//					
					//  safeStrnCpy(  "101",  idStr,  mycountof(  idStr  )  );	//  for test
					_snprintf(  idStr,  mycountof(  idStr  ),  "%I64u",  idInfo.ui64Id  );
					//
					_sntprintf(  wDevIdStr,  mycountof(  wDevIdStr  ),  _T(  "%s/%s"  ),  CString(  CONST_str_dev  ),  pPort->m_var.szPort  );
					_sntprintf(  wReversePath,  mycountof(  wReversePath  ),  _T(  "%s:%s"  ),  CString(  CONST_str_phone  ),  CString(  sm.TPA  )  );
					pVDev->m_var.common.pGuiOpen->pf_postStr2Mgr_mc_open(  &pVDev->m_var.common,  CONST_objType_phoneGuest,  CONST_objType_dev,  wDevIdStr,  wReversePath,  0,  0,  0,  tBuf,  idStr,  0  );

					OutputDebugString(  _T(  ""  )  );
									
					
					//  为分析的需要，暂时不删除, 2008/01/09

					if  (  pVDev->m_var.cfg.ucbAutoDel  )  {
						traceLogA(  "放此消息索引进入toBeDelMsgIndexQ，以删除此消息。"  );
						//
						MIS_MSG_applyForWork	msg;
						int						tmpiRet;
						//
						memset(  &msg,  0,  sizeof(  msg  )  );
						msg.uiType  =  CONST_misMsgType_applyForWork;
						msg.uiToBeDelMsgIndex  =  iMsgIndex;
						//
						tmpiRet  =  qTraverse(  &pPort->m_var.toBeDelMsgIndexQ,  findToBeDelMsg,  0,  &msg  );
						if  (  tmpiRet  <  0  )  goto  errLabel;
						if  (  !tmpiRet  )  {
							qPostMsg(  &msg,  sizeof(  msg  ),  &pPort->m_var.toBeDelMsgIndexQ  );
						}
					}
					

				}
			}
	 }

	 if  (  pO->ucbToSendCmd  )  {
		 traceLogA(  "命令未收到响应码，还未结束这次的处理。"  );
		 iErr  =  0;  goto  errLabel;
	 }
	 
	 //  开始新的命令动作时，象lastCmgl的数据就应该放弃		 
	 pO->lastCmglResp[0]  =  0;
	 pO->tLastCmdStart  =  0;	//  表明是结束了
	 
	 if  (  tryToSend(  uiComIndex  )  )  goto  errLabel;

	 
	 iErr  =  0;  
errLabel:

	 traceLogA(  "doIsMgr_input leaves with %s",  iErr  ?  "Err"  :  "Ok"  );

	 return  iErr;
}



 extern "C" DWORD WINAPI threadProc_mgr_vDevComs( LPVOID lpParameter )
{
	 int							iErr				=	-1;
	 int							loopCtrl			=	0;
	 DWORD							dwThreadId			=	GetCurrentThreadId(  );	 
	 CQyMalloc						mallocObj;
	 unsigned  int					uiBufSize			=	sizeof(  MIS_MSGU  );
	 MIS_MSGU					*	pMsg				=	(  MIS_MSGU  *  )mallocObj.malloc(  uiBufSize  );
	 if  (  !pMsg  )  return  -1;
	 unsigned  int					len;
	 DWORD							dwRet;
	 //  long							lPrev;
	 CTX_THREAD_vDev				ctx;
	 
	 traceLogA(  "threadProc_mgr_vDevComs:  enters"  );
	 
	 memset(  &ctx,  0,  sizeof(  ctx  )  );

	 for  (  ;  !pVDev->m_var.bQuit;  loopCtrl  ++  )  {

		  dwRet  =  WaitForSingleObject(  pVDev->m_var.mgrQ.hSemaTrigger,  3500  );
		  if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;
		  
		  for  (  ;  !pVDev->m_var.bQuit;  )  {
			   len  =  uiBufSize;
			   if  (  qGetMsg(  &pVDev->m_var.mgrQ,  pMsg,  &len  )  )  break;
			   memset(  (  (  char  *  )pMsg  )  +  len,  0,  uiBufSize  -  len  );

			   switch  (  pMsg->uiType  )  {
				       case  CONST_misMsgType_input:

						     if  (  doIsMgr_input_vDevComs(  &pMsg->input,  len,  &ctx  )  )  break;
			
							 //
							 break;
					   case  CONST_misMsgType_req:

						     break;
					   case  CONST_misMsgType_talk:

						     if  (  doIsMgr_talk_vDevComs(  &pMsg->talk,  len,  &ctx  )  )  break;

						     break;
					   case  CONST_misMsgType_sendFinished:
						     if  (  doIsMgr_sendFinished_vDevComs(  &pMsg->sendFinished,  len,  &ctx  )  )  break;
						     break;
					   default:
						        traceLogA(  "得到未处理的消息: %S",  qyGetDesByType1(  CONST_misMsgTypeTable,  pMsg->uiType  )  );
								break;
			   }
			   
		
			   dwRet  =  WaitForSingleObject(  pVDev->m_var.mgrQ.hSemaTrigger,  50  );
			   if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;			   
		  }

	
		  if  (  !(  loopCtrl  %  8  )  )  {
			  //  traceLogA(  "threadProc_mgr_vDevComs: 这里应该定期检查一下各端口的超时情况。要是一个命令执行时间过长的话，那么就要触发这个端口重起一下。"  );
			  time_t	t;
			  time(  &t  );
			  //
			  for  (  int  i  =  0;  i  <  (  int  )pVDev->m_var.cfg.uiMaxComs;  i  ++  )  {
				   CComPort  *  pPort  =  &pVDev->m_var.pPorts[i];
				   COM_BUF_O  *  pO  =  &pVDev->m_var.pBufOs[i];
				   //
				   if  (  !pPort->m_var.ucbComExists  ||  !pPort->m_var.ucbStarted  )  continue;
				   if  (  !bComPortSending(  pVDev,  i  )  )  continue;
				   if  (  t  -  pO->tLastCmdStart  >  30  )  {
					   traceLogA(  "ports[%d] is timeout, will restart.",  i  );

					   CQySyncObj	syncObj;
					   //
					   if  (  syncObj.sync(  CONST_str_syncGsmModemInit  )  )  {	//  有时，和reset时，要有冲突。所以做一个同步
						   traceLogA(  "sync failed"  );  continue;
					   }
					   
					   pPort->StopMonitoring(  );
					   pPort->InitPort(  pVDev  );
					   pPort->StartMonitoring(  );
				   }
			  }
		  }

		  if  (  !(  loopCtrl  %  3  )  )  {
			  QY_GUI_OPEN_vDev  *  pOpen  =  pVDev->m_var.common.pGuiOpen;
			  int		i;
			  //  
			  if  (  !ctx.bVDevComsReported  )  {	//  先向服务器通报所有的comPort状态
				  QY_VDEV_COMS		coms;
				  QY_VDEV_COM	*	pCom;
				  int				len;
				  //
				  memset(  &coms,  0,  sizeof(  coms  )  );
				  coms.uiType  =  CONST_imCommType_vDevComs;
				  coms.uiVDevId  =  pVDev->m_var.common.uiVDevId;
				  for  (  i  =  0;  i  <  (  int  )pVDev->m_var.cfg.uiMaxComs  &&  coms.usCnt  <  mycountof(  coms.mems  );  i  ++  )  {
					   CComPort  *  pPort  =  &pVDev->m_var.pPorts[i];
					   if  (  !pPort->m_var.ucbComExists  )  continue;
					   //
					   pCom  =  &coms.mems[coms.usCnt];
					   _sntprintf(  pCom->wDevIdStr,  mycountof(  pCom->wDevIdStr  ),  _T(  "%s/%s"  ),  CONST_str_dev,  pPort->m_var.szPort  );
					   _sntprintf(  pCom->name,  mycountof(  pCom->name  ),  _T(  "%s"  ),  pPort->m_var.szPort  );
					   lstrcpyn(  pCom->model,  CString(  pPort->m_var.modelBuf  ).GetBuffer(  0  ),  mycountof(  pCom->model  )  );
					   safeStrnCpy(  pPort->m_var.smscBuf,  pCom->smsc,  mycountof(  pCom->smsc  )  );
					   //
					   coms.usCnt  ++  ;
				  }
				  len  =  offsetof(  QY_VDEV_COMS,  mems  )  +  coms.usCnt  *  sizeof(  coms.mems[0]  );
				  //
				  if  (  pOpen->pf_postReq2Mgr_mc_open  )  pOpen->pf_postReq2Mgr_mc_open(  &pVDev->m_var.common,  0,  0,  0,  (  char  *  )&coms,  len  );

			  }
			  //
			  if  (  ctx.bVDevComsReported  &&  !ctx.bSmPolicyRetrieved  )  {		//  其次应该请求下载策略
				  RETRIEVE_SM_POLICY		req;
				  //
				  memset(  &req,  0,  sizeof(  req  )  );
				  req.uiType  =  CONST_imCommType_retrieveSmPolicy;
				  req.uiVDevId  =  pVDev->m_var.common.uiVDevId;
				  //
				  len  =  offsetof(  RETRIEVE_SM_POLICY,  mems  );
				  //
				  if  (  pOpen->pf_postReq2Mgr_mc_open  )  pOpen->pf_postReq2Mgr_mc_open(  &pVDev->m_var.common,  0,  0,  0,  (  char  *  )&req,  len  );
			  }
			  if  (  ctx.bSmPolicyRetrieved  &&  !ctx.bPhoneMsgrListAccepted  )  {	
				  BOOL  bPhoneMsgrListAccepted  =  FALSE;
				  if  (  pOpen->pf_bGetLongProperty(  0,  (  void  *  )CONST_qyPropertyId_bPhoneMsgrListAccepted,  &bPhoneMsgrListAccepted  )  
					  &&  bPhoneMsgrListAccepted  )
				  {
					  ctx.bPhoneMsgrListAccepted  =  TRUE;
				  }
			  }

			  //  下面为轮询所有的com口，要是没有start的话，就启动一下这个端口。
			  {
				  BOOL  bOnlyNetSm	=	FALSE;
	
				  if  (  !pOpen->pf_bGetLongProperty(  0,  (  void  *  )CONST_qyPropertyId_ucbOnlyNetSm,  &bOnlyNetSm  )  )  bOnlyNetSm  =  FALSE;

				  if  (  !bOnlyNetSm  ||  (  ctx.bSmPolicyRetrieved  &&  ctx.bPhoneMsgrListAccepted  )  )  {		//  然后应该启动端口读取
					  //
					  for  (  i  =  0;  i  <  (  int  )pVDev->m_var.cfg.uiMaxComs;  i  ++  )  {
						   CComPort  *  pPort  =  &pVDev->m_var.pPorts[i];
						   char		*	pCmd			=	"AT+CMGL=4";
						   //
						   if  (  !pPort->m_var.ucbComExists  )  continue;
						   if  (  pPort->m_var.ucbStarted  )  continue;
						   //

						   CQySyncObj	syncObj;
						   //
						   if  (  syncObj.sync(  CONST_str_syncGsmModemInit  )  )  {	//  有时，和reset时，要有冲突。所以做一个同步
							   traceLogA(  "sync failed"  );  continue;
						   }

						   //
						   pPort->StopMonitoring(  );		//  这样做的目的，是为了防止手工把com已经启动起来了
						   pPort->InitPort(  pVDev  );
						   pPort->StartMonitoring();
						   //
						   //  给每个com发送一条自动读取所有已有消息的命令at+cmgl=4
						   pCmd		=	"AT+CMGL=4\r\n";

						   mySendCmd(  i,  pCmd,  "",  "",  NULL,  0  );

					  }
					  //
				  }			  
			  }
			  //	
		  }


	 }

	 iErr  =  0;
	 
errLabel:
	 
	 pVDev->m_var.status.ulbMgrQuit  =  TRUE;

	 traceLogA(  "threadProc_mgr_vDevComs:  leaves"  );

	 return  iErr;
}

