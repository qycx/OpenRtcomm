
#include	"stdafx.h"

#include	"dhPtzProc.h"
#include <ctxQmThread.h>
#include <showInfo_open.h>



int  dhPtz_qisPipe_onRead(QIS_pipe* pQisPipe, void* pMsg, unsigned  int  msgLen, void* p0, void* p1)
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
	if (dwByte > gBuf_dhListIp.m_var.uiSize_pOnvifMsgBuf)
	{
		_sntprintf(tBuf, mycountof(tBuf), _T("onvifMsgBuf too small, dwByte %d > size_msgBuf %d"), dwByte, gBuf_dhListIp.m_var.uiSize_pOnvifMsgBuf);
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
	gBuf_dhPtz.m_var.dwLastTickCnt_recvd = myGetTickCount(nullptr);

	//
	//
	switch (pMsgCommon->iSubtype) {
#if 0
	case  CONST_onvifMsg_subtype_dbg:
	{
		OnvifMsg_dbg* pDbg = (OnvifMsg_dbg*)pMsgCommon;
		OnvifMsg_dbg  m = { 0 };
		m.uiType = CONST_qisMsgType_onvif;
		m.iSubtype = CONST_onvifMsg_subtype_dbg;
		_snprintf(m.buf, mycountof(m.buf), "dhPtz recvd: %s", pDbg->buf);
		qisPipe_writeMsg(&m, sizeof(m), gBuf_dhPtz.m_var.pQisPipe);

	}
	break;
#endif
	case  CONST_onvifMsg_subtype_ping:
	{
		OnvifMsg_ping* pPing = (OnvifMsg_ping*)pMsgCommon;
		//
		if (0) {
			showInfo_open0(0, 0, _T("ptz: recv ping"));
		}
		//
		if (pPing->tn != gBuf_dhPtz.m_var.appParams.tn) {
			TCHAR  tBuf[128];
			_sntprintf(tBuf, mycountof(tBuf), _T("ptz err: ping.tn %d != appParams.tn %d"), pPing->tn, gBuf_dhPtz.m_var.appParams.tn);
			showInfo_open0(0, 0, tBuf);
			//
			gBuf_dhPtz.m_var.bErr1 = true;
		}

	}
	break;
	case  CONST_onvifMsg_subtype_ptz:
	{
		OnvifMsg_ptz* pPtz = (OnvifMsg_ptz*)pMsgCommon;
		//
		int  ii = 0;

		//
		COPYDATASTRUCT		tmpCopyData;

		tmpCopyData.lpData = pPtz;
		tmpCopyData.cbData = sizeof(*pPtz);
		int  iRet = ::SendMessageTimeout(gBuf_dhPtz.m_var.hMainWnd, WM_COPYDATA, NULL, (LPARAM)&tmpCopyData,0,1000,NULL);


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
