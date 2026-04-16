

#include	"stdafx.h"
#include    "dhProc.h"
#include <qisOnvifCommProc_open.h>
#include <stdio.h>
#include <ctxQmThread.h>
#include <showInfo_open.h>



//
int  dh_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1)
{
	int  iErr = -1;
	unsigned  int    dwByte = msgLen;
	//	
	TCHAR  tBuf[128];

	//	
	if (dwByte < sizeof(OnvifMsg_common)) {
		//dyn_showInfo_open(0, 0, _T("pipeThread_cli err: read too small bytes < sizeof(  Onvif_msg_common  )"));
		return  -1;
	}
#if 0
	if (dwByte > gBuf_dh.m_var.qm.uiSize_pOnvifMsgBuf)
	{
		_sntprintf(tBuf, mycountof(tBuf), _T("onvifMsgBuf too small, dwByte %d > size_msgBuf %d"), dwByte, gBuf_dh.m_var.qm.uiSize_pOnvifMsgBuf);
		//dyn_showInfo_open(0, 0, tBuf);
		return  -1;
	}
#endif



	//
	OnvifMsg_common* pMsgCommon = (OnvifMsg_common*)pMsg;
	if (pMsgCommon->uiType != CONST_qisMsgType_onvif)  return  -1;

	//
	gBuf_dh.m_var.qm.dwLastTickCnt_recvd = myGetTickCount(nullptr);

	//
	//
	switch  (  pMsgCommon->iSubtype) {
			case  CONST_onvifMsg_subtype_dbg:
				{
				OnvifMsg_dbg* pDbg = (OnvifMsg_dbg*)pMsgCommon;
				OnvifMsg_dbg  m = { 0 };
				m.uiType = CONST_qisMsgType_onvif;
				m.iSubtype = CONST_onvifMsg_subtype_dbg;
				m.ucbResp = true;
				_snprintf(m.buf, mycountof(m.buf), "dh recvd: %s", pDbg->buf);
				qisPipe_writeMsg(&m, sizeof(m), gBuf_dh.m_var.qm.pQisPipe);
				
				}
				  break;
			case  CONST_onvifMsg_subtype_ping:
				{
				OnvifMsg_ping* pPing = (OnvifMsg_ping*)pMsgCommon;
				//
				OnvifMsg_ping m = { 0 };
				m.uiType = CONST_qisMsgType_onvif;
				m.iSubtype = CONST_onvifMsg_subtype_ping;
				//
				if (0) {
					showInfo_open0(0, 0, _T("recv ping, redirect to listIp"));
				}
				//
				m.tn = gBuf_dh.m_var.dhListIp.tool.tn;
				if (m.tn) {
					qisPipe_writeMsg(&m, sizeof(m), gBuf_dh.m_var.dhListIp.pQisPipe);
				}
				m.tn = gBuf_dh.m_var.dhDeviceControl.tool.tn;
				if (m.tn) {
					qisPipe_writeMsg(&m, sizeof(m), gBuf_dh.m_var.dhDeviceControl.pQisPipe);
				}
				m.tn = gBuf_dh.m_var.dhPtz.tool.tn;
				if (m.tn) {
					qisPipe_writeMsg(&m, sizeof(m), gBuf_dh.m_var.dhPtz.pQisPipe);
				}

				}
				break;
			case  CONST_onvifMsg_subtype_close:
				  //
				  //gBuf_dh.m_var.m_bClose = true;
				  //
				  showInfo_open0(0, 0, _T("recv close msg"));
				  //
				  PostMessage(gBuf_dh.m_var.hMainWnd, WM_CLOSE, 0, 0);
				  //
				  break;

			case  CONST_onvifMsg_subtype_nvrInfo:
			{
				//  œ»∆Ù∂ØdhListIp
				showInfo_open0(0,0,_T(  "dh: redirect to dhListIp.pQisPipe\n"));

				//
				int  ii = 0;
				qisPipe_writeMsg(pMsg, msgLen, gBuf_dh.m_var.dhListIp.pQisPipe);
			}
				break;
			case  CONST_onvifMsg_subtype_nvrControl:
			{
				//
				qisPipe_writeMsg(pMsg, msgLen, gBuf_dh.m_var.dhDeviceControl.pQisPipe);
			}
				break;
			case  CONST_onvifMsg_subtype_ptz:
			{
				OnvifMsg_ptz* pPtz = (OnvifMsg_ptz*)pMsgCommon;


				//
				qisPipe_writeMsg(pMsg, msgLen, gBuf_dh.m_var.dhPtz.pQisPipe);

			}
			break;
	default:
		//dyn_showInfo_open(0, 0, _T("onvifCli_qisPipe_onRead: unprocessed subtype"));
		break;
	}


	//
	iErr = 0;

errLabel:

	//
	return  iErr;
}


//
int  dh_listIp_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1)
{
	int  iErr = -1;
	unsigned  int    dwByte = msgLen;
	//	
	TCHAR  tBuf[128];

	//	
	if (dwByte < sizeof(OnvifMsg_common)) {
		//dyn_showInfo_open(0, 0, _T("pipeThread_cli err: read too small bytes < sizeof(  Onvif_msg_common  )"));
		return  -1;
	}
#if 0
	if (dwByte > gBuf_dh.m_var.tool.uiSize_pOnvifMsgBuf)
	{
		_sntprintf(tBuf, mycountof(tBuf), _T("onvifMsgBuf too small, dwByte %d > size_msgBuf %d"), dwByte, gBuf_dh.m_var.tool.uiSize_pOnvifMsgBuf);
		//dyn_showInfo_open(0, 0, tBuf);
		return  -1;
	}
#endif


	//
	//gBuf_dh.status.dwTickCnt_lastMsg = GetTickCount();

	//
	OnvifMsg_common* pMsgCommon = (OnvifMsg_common*)pMsg;
	if (pMsgCommon->uiType != CONST_qisMsgType_onvif)  return  -1;

	//
	gBuf_dh.m_var.dhListIp.dwLastTickCnt_recvd = myGetTickCount(nullptr);

	//
	//
	switch (pMsgCommon->iSubtype) {
	case  CONST_onvifMsg_subtype_dbg:
	{
		OnvifMsg_dbg* pDbg = (OnvifMsg_dbg*)pMsgCommon;


	}
	break;
	//
	case  CONST_onvifMsg_subtype_nvrInfo:
	{
		OnvifMsg_nvrInfo* pOn = (OnvifMsg_nvrInfo*)pMsgCommon;
		if (!pOn->ucbResp)  break;
		int  ii = 0;

		//
		showInfo_open0(0, 0, _T("dh: recv from dhListIp, and send it to app"));

		//
		qisPipe_writeMsg(pMsg, msgLen, gBuf_dh.m_var.qm.pQisPipe);

	}
	break;
	//
	default:
		//dyn_showInfo_open(0, 0, _T("onvifCli_qisPipe_onRead: unprocessed subtype"));
		break;
	}


	//
	iErr = 0;

errLabel:

	//
	return  iErr;
}


//
//
int  dh_deviceControl_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1)
{
	int  iErr = -1;
	unsigned  int    dwByte = msgLen;
	//	
	TCHAR  tBuf[128];

	//	
	if (dwByte < sizeof(OnvifMsg_common)) {
		//dyn_showInfo_open(0, 0, _T("pipeThread_cli err: read too small bytes < sizeof(  Onvif_msg_common  )"));
		return  -1;
	}
#if 0
	if (dwByte > gBuf_dh.m_var.tool.uiSize_pOnvifMsgBuf)
	{
		_sntprintf(tBuf, mycountof(tBuf), _T("onvifMsgBuf too small, dwByte %d > size_msgBuf %d"), dwByte, gBuf_dh.m_var.tool.uiSize_pOnvifMsgBuf);
		//dyn_showInfo_open(0, 0, tBuf);
		return  -1;
	}
#endif


	//
	//gBuf_dh.status.dwTickCnt_lastMsg = GetTickCount();

	//
	OnvifMsg_common* pMsgCommon = (OnvifMsg_common*)pMsg;
	if (pMsgCommon->uiType != CONST_qisMsgType_onvif)  return  -1;

	//
	gBuf_dh.m_var.dhDeviceControl.dwLastTickCnt_recvd = myGetTickCount(nullptr);

	//
	//
	switch (pMsgCommon->iSubtype) {
	case  CONST_onvifMsg_subtype_dbg:
	{
		OnvifMsg_dbg* pDbg = (OnvifMsg_dbg*)pMsgCommon;


	}
	break;
	//
	//
	default:
		//dyn_showInfo_open(0, 0, _T("onvifCli_qisPipe_onRead: unprocessed subtype"));
		break;
	}


	//
	iErr = 0;

errLabel:

	//
	return  iErr;
}




//
int  dh_ptz_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1)
{
	int  iErr = -1;
	unsigned  int    dwByte = msgLen;
	//	
	TCHAR  tBuf[128];

	//	
	if (dwByte < sizeof(OnvifMsg_common)) {
		//dyn_showInfo_open(0, 0, _T("pipeThread_cli err: read too small bytes < sizeof(  Onvif_msg_common  )"));
		return  -1;
	}
#if 0
	if (dwByte > gBuf_dh.m_var.tool.uiSize_pOnvifMsgBuf)
	{
		_sntprintf(tBuf, mycountof(tBuf), _T("onvifMsgBuf too small, dwByte %d > size_msgBuf %d"), dwByte, gBuf_dh.m_var.tool.uiSize_pOnvifMsgBuf);
		//dyn_showInfo_open(0, 0, tBuf);
		return  -1;
	}
#endif


	//
	//gBuf_dh.status.dwTickCnt_lastMsg = GetTickCount();

	//
	OnvifMsg_common* pMsgCommon = (OnvifMsg_common*)pMsg;
	if (pMsgCommon->uiType != CONST_qisMsgType_onvif)  return  -1;

	//
	gBuf_dh.m_var.dhListIp.dwLastTickCnt_recvd = myGetTickCount(nullptr);

	//
	//
	switch (pMsgCommon->iSubtype) {
	case  CONST_onvifMsg_subtype_dbg:
	{
		OnvifMsg_dbg* pDbg = (OnvifMsg_dbg*)pMsgCommon;


	}
	break;
	//
	case  CONST_onvifMsg_subtype_nvrInfo:
	{
		OnvifMsg_nvrInfo* pOn = (OnvifMsg_nvrInfo*)pMsgCommon;
		if (!pOn->ucbResp)  break;
		int  ii = 0;

		//
		showInfo_open0(0, 0, _T("dh: recv from dhListIp, and send it to app"));

		//
		qisPipe_writeMsg(pMsg, msgLen, gBuf_dh.m_var.qm.pQisPipe);

	}
	break;
	//
	default:
		//dyn_showInfo_open(0, 0, _T("onvifCli_qisPipe_onRead: unprocessed subtype"));
		break;
	}


	//
	iErr = 0;

errLabel:

	//
	return  iErr;
}
