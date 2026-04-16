
#include	"stdafx.h"


#include	<Windows.h>
#include	<WinSock2.h>
#include	<mmeapi.h>
#include	<tchar.h>
#include	<stdlib.h>

#include	"qmCommon.h"
//#include <ctxQmc_sm.h>
#include	"myCmdParams_open.h"


#include	"myTChar.h"
#include	"hgCommProc.h"
#include	<time.h>
#include	"qyMsgFunc.h"
#include	"qnmCommProc_mis.h"
#include	"smCommProc.h"
//#include	"smLoginProc.h"



//
int  parseHgUsr(void* p0, short  sCmd, char* dataBuf, int  dataBufLen, Param_hgUsr* pParam)
{
	int  iErr = -1;
	char* pData = dataBuf;
#if 0
	CQyMcDaemon* pDaemon = g_pDaemon;
	QY_SERVICE_INFO* pServiceInfo = pDaemon->getServiceInfo();
	MT_SOCK_IOCP* pMtSock = (MT_SOCK_IOCP*)pServiceInfo->pMtSock;
	if (!pMtSock)  return  -1;
#endif
	//
	TCHAR  tBuf[128];
	char  buf[1024];

	//
	if (sCmd == CONST_hgCmd_createGrp) {
		int  ii = 0;
	}

	//
	memset(pParam, 0, sizeof(pParam[0]));

	for (;; ) {

		char seg[1024];
		if (getSeg(pData, seg, mycountof(seg)))  break;



		//
		int objType = 0;
		char* tag_obj = (char*)"obj=";
		objType = geti64Val(seg, tag_obj);

		int len = 0;
		char* tag_len = (char*)"len=";
		len = geti64Val(seg, tag_len);

		//
		if (objType > 0 && len > 0) {
			char* pStart = pData + strlen(seg) + 2;
			//
			switch (objType) {
			case  CONST_hgType_grpMem_usrName: {
				safeStrnCpy(pStart, buf, len + 1);
				myUtf82TChar(buf, pParam->usrName, mycountof(pParam->usrName));
			}
											 //							
											 break;
			default:
				break;
			}

		}

		//
		pData = strchr(pData, '[');
		if (!pData)  break;
		pData += strlen(seg) + 2;
		if (objType > 0 && len > 0) {
			pData += len;
		}

		//
		continue;
	}


	//
	if (sCmd == CONST_hgCmd_startMeeting) {
		int  ii = 0;
		showInfo_open0(0, 0, _T("parseHgCmd_servReq: get cmd usrLoginOk"));
	}

	iErr = 0;
errLabel:
	return  iErr;

}




//
__declspec(dllexport )  int  parseHgCmd_servReq(void* p0, short  sCmd, char* dataBuf, int  dataBufLen, Param_hgCmd_servReq* pParam)
{
	int  iErr = -1;
	char* pData = dataBuf;
#if 0
	CQyMcDaemon* pDaemon = g_pDaemon;
	QY_SERVICE_INFO* pServiceInfo = pDaemon->getServiceInfo();
	MT_SOCK_IOCP* pMtSock = (MT_SOCK_IOCP*)pServiceInfo->pMtSock;
	if (!pMtSock)  return  -1;
#endif
	//
	TCHAR  tBuf[128];
	char  buf[1024];

	//
	if (sCmd == CONST_hgCmd_createGrp) {
		int  ii = 0;
	}

	//
	memset(pParam, 0, sizeof(pParam[0]));

	//
	for (;; ) {

		//
		pData = strchr(pData, '[');
		if (!pData)  break;

		//
		char seg[1024];
		if (getSeg(pData, seg, mycountof(seg)))  break;

		//
		char* tag_msgr = (char*)"msgr=";
		QY_MESSENGER_ID  idInfo_msgr;
		//
		QY_MESSENGER_ID  idInfo;
		idInfo.ui64Id = geti64Val(seg, tag_msgr);
		if (idInfo.ui64Id) {
			//
			pParam->idInfo_msgr = idInfo;
		}

		//
		char* tag_rc = (char*)"rc=";
		int rc = geti64Val(seg, tag_rc);
		if (rc) {
			pParam->iRc = rc;
		}

		//
		char* tag_org = (char*)"org=";
		int cmd_org = geti64Val(seg, tag_org);
		if (cmd_org) {
			pParam->cmd_org = cmd_org;
		}

		//
		char* tag_op = (char*)"op=";
		unsigned  short  usOp = 0;
		usOp = geti64Val(seg, tag_op);
		if (usOp) {
			pParam->usOp = usOp;
		}

		//
		int objType = 0;
		char* tag_obj = (char*)"obj=";
		objType = geti64Val(seg, tag_obj);

		int len = 0;
		char* tag_len = (char*)"len=";
		len = geti64Val(seg, tag_len);

		//
		if (objType > 0 && len > 0) {
			char* pStart = pData + strlen(seg) + 2;
			//
			switch (objType) {
			case  CONST_hgType_sxrz_serv_random:
				break;
			case  CONST_hgType_sxrz_serv_cert:
				break;
			case  CONST_hgType_sxrz_serv_signData:
				break;
			case  CONST_hgType_authType:
				pParam->usAuthType = atol(pStart);
				break;
			case  CONST_hgType_grpMem: {
				Param_hgUsr usr;
				memset(&usr, 0, sizeof(usr));
				parseHgUsr(p0, sCmd, pStart, len, &usr);
				if (usr.usrName[0]) {
					if (pParam->usCnt_usrs >= mycountof(pParam->usrs)) {
						showInfo_open0(0, 0, _T("parseHgCmd_servReq failed, too many hgUsrs"));
						goto  errLabel;
					}
					pParam->usrs[pParam->usCnt_usrs] = usr;
					pParam->usCnt_usrs++;
				}
				//
			}
									 break;
			case  CONST_hgType_grpIdInfo:
				idStr2Info(pStart, &pParam->idInfo_grp);
				break;
			case  CONST_hgType_meetingName:
				safeStrnCpy(pStart, buf, len + 1);
				myUtf82TChar(buf, pParam->meetingName, mycountof(pParam->meetingName));
				break;
			case  CONST_hgType_meetingId: {
				QY_MESSENGER_ID  tmp;
				//pParam->lMeetingId=atol(pStart);
				idStr2Info(pStart, &tmp);
				pParam->hgInfo.ui64MeetingId_hg = tmp.ui64Id;
			}
										break;
			case  CONST_hgType_meetingHz:
				pParam->iHz = atol(pStart);
				break;
			case  CONST_hgType_meetingFourcc:
				pParam->iFourccType_hg = atol(pStart);
				break;
			case  CONST_hgType_meetingType:
				pParam->hgInfo.iMeetingType_hg = atol(pStart);
				break;
			case  CONST_hgType_meetingRecord:
				pParam->hgInfo.bRecord = atol(pStart);
				break;
			case  CONST_hgType_meetingShare_2ndStream:
				pParam->hgInfo.bShare_2ndStream = atol(pStart);
				break;
			case  CONST_hgType_shareMem:
			{
				QY_MESSENGER_ID	tmp;
				idStr2Info(pStart, &tmp);
				if (pParam->tmpInternal.cnt_shareMems >= mycountof(pParam->hgInfo.shareMems)) {
					showInfo_open0(0, 0, _T("parseHgCmd_servReq failed, too big cnt_shareMems"));
					goto  errLabel;
				}
				pParam->hgInfo.shareMems[pParam->tmpInternal.cnt_shareMems].idInfo.ui64Id = tmp.ui64Id;
				pParam->tmpInternal.cnt_shareMems++;
			}
			break;
			case  CONST_hgType_meeting_level:
				pParam->hgInfo.iMeetingLevel_hg = atol(pStart);
				break;
			case  CONST_hgType_meetingDuration:
				pParam->hgInfo.iMeetingDurationInMin = atol(pStart);
				break;
			case  CONST_hgType_meetingStartTime: {
				QY_MESSENGER_ID  tmp;
				idStr2Info(pStart, &tmp);
				pParam->hgInfo.ui64_meetingStartTime = tmp.ui64Id;												  }
											   break;
			case  CONST_hgType_meetingCompere:
				safeStrnCpy(pStart, buf, min(mycountof(buf), len + 1));
				myUtf82TChar(buf, pParam->hgInfo.meetingCompere, mycountof(pParam->hgInfo.meetingCompere));
				break;

				//
			case  CONST_hgType_flow_512k:
				pParam->hgInfo.bFlow512k = atol(pStart);
				break;

				//
			case  CONST_hgType_bLive:
				pParam->hgInfo.bLive = atol(pStart);
				break;
			case  CONST_hgType_liveUrl:
				safeStrnCpy(pStart, buf, min(mycountof(buf), len + 1));
				myUtf82TChar(buf, pParam->hgInfo.liveUrl, mycountof(pParam->hgInfo.liveUrl));
				break;


				//
			case  CONST_hgType_isDisable:
				pParam->isDisable = atol(pStart);
				break;
			case  CONST_hgType_iMaxElapseInDay:
				pParam->iMaxElapseInDay = atol(pStart);
				break;
			case  CONST_hgType_iMinFree_disk_inPercent:
				pParam->iMinFree_disk_inPercent = atol(pStart);
				break;
			case CONST_hgType_bitrate_dl:
				pParam->bitrateInKbps_dl = atol(pStart);
				break;
			case CONST_hgType_bitrate_ul:
				pParam->bitrateInKbps_ul = atol(pStart);
				break;

			case CONST_hgType_nspeakers:
				pParam->iNSpeakers = atol(pStart);
				break;

			case CONST_hgType_task_type:
				pParam->iTaskType = atol(pStart);
				break;

			case CONST_hgType_share_device_grp_index:
				pParam->shareDevice_grp_index = atol(pStart);
				break;
			case  CONST_hgType_grp_usIndex:
				pParam->grp_usIndex = atol(pStart);
				break;



			
				//
			default:
				break;
			}

		}


		//
		pData += strlen(seg) + 2;
		if (objType > 0 && len > 0) {
			pData += len;
		}

		//


		//
		continue;
	}


	//
	if (sCmd == CONST_hgCmd_startMeeting) {
		int  ii = 0;
		showInfo_open0(0, 0, _T("parseHgCmd_servReq: get cmd startMeeting"));
	}

	if (sCmd == CONST_hgCmd_RestartDeamon) {
		int  ii = 0;
		showInfo_open0(0, 0, _T("parseHgCmd_servReq: get cmd restartDeamon"));
	}
	//
	if (pParam->cmd_org == CONST_hgCmd_qmdXt) {
		int  ii = 0;
	}


	//
	iErr = 0;
errLabel:
	return  iErr;

}

