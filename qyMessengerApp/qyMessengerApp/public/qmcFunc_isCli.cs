using System;
using System.Collections.Generic;
using System.Text;

namespace qy
{
    partial class qyFuncs
{
		public static unsafe IM_TASK_RCD* msg2TaskRcd(MIS_CNT pMisCnt, MIS_MSG_INPUT* pMsg, ushort usRespCode, IM_TASK_RCD* pRcd)
		{
			int iErr = -1;
			MIS_MSG_routeTalkData* pTalkData = null;
			IM_CONTENTU* pContent = null;
			//char buf[255 + 1] = "";
			string str;

			if (null==pMisCnt || null==pMsg || null==pRcd) return null;

			pTalkData = &pMsg->data;
			pContent = (IM_CONTENTU*)pTalkData->buf;

			if (null==pTalkData || null==pContent) goto errLabel;

			mymemset((IntPtr)pRcd, 0, sizeof(IM_TASK_RCD));
			//
			//mylstrcpyn(pRcd->misServName, pMisCnt.cfg.misServName, mycountof(pRcd->misServName));
			pRcd->idInfo_send.ui64Id = pMsg->idInfo_taskSender.ui64Id;
			pRcd->tSendTime = pMsg->tStartTime;
			pRcd->uiTranNo = pMsg->uiTranNo;
			pRcd->idInfo_recv.ui64Id = pMsg->idInfo_taskReceiver.ui64Id;
			//
			pRcd->uiContentType = pContent->uiType; //  2008/05/29
													//
			mytime(&pRcd->tRecvTime);
			pRcd->usRespCode = usRespCode;
			//
			pRcd->id = pMsg->iTaskId;                   //  2010/04/23
			pRcd->uiMode = 0;
			pRcd->uiType = pMsg->uiTaskType;
			pRcd->iStatus = pMsg->iStatus;

			switch (pContent->uiType)
			{
				case Consts.CONST_imCommType_transferFileReq:
					//
					mylstrcpyn(pRcd->subject, pContent->transferFileReq.fileName, Consts.cntof_subject);
					mylstrcpyn(pRcd->content, pContent->transferFileReq.fullFilePath, Consts.cntof_content);
					//
					//_sntprintf(pRcd->propStrs[0], mycountof(pRcd->propStrs[0]), _T("%I64u"), pContent->transferFileReq.ui64FileLen);
					str = string.Format("{0}", pContent->transferFileReq.ui64FileLen);
					mytcsncpy(pRcd->propStr0, str, Consts.cntof_propStr);
					break;
				case Consts.CONST_imCommType_rtcCallReq:
					//
					//ulIp2Str(pContent->rtcCallReq.ulIp_caller, buf, mycountof(buf));
					//myStr2TChar(buf, pRcd->subject, mycountof(pRcd->subject));
					//
					break;
				case Consts.CONST_imCommType_transferAvInfo:
					//
					//_sntprintf(pRcd->subject, mycountof(pRcd->subject), _T("%d * %d"), pContent->transferAvInfo.tranInfo.video.vh_decompress.bih.biWidth, pContent->transferAvInfo.tranInfo.video.vh_decompress.bih.biHeight);
					str = string.Format("{0}*{1}", pContent->transferAvInfo.ass.tranInfo.video.vh_decompress.bih.biWidth, pContent->transferAvInfo.ass.tranInfo.video.vh_decompress.bih.biHeight);
					mytcsncpy(pRcd->subject, str, Consts.cntof_subject);
					//
					break;
				case Consts.CONST_imCommType_queryCustomerServiceOfficerReq:       //  2011/04/06
					break;
				case Consts.CONST_imCommType_transferGpsInfo:                      //  2012/04/19
					break;
				default:
# if  __DEBUG__
					traceLog(_T("msg2TaskRcd failed, unknown contentType"));
#endif
					goto errLabel;
					break;
			}


			iErr = 0;
		errLabel:

			return iErr!=0 ? null : pRcd;
		}

		public static unsafe IM_TASK_RCD* msg2TaskRcd(MIS_CNT pMisCnt, MIS_MSG_TASK* pMsg, ushort usRespCode, IM_TASK_RCD* pRcd)
		{
			int iErr = -1;
			MIS_MSG_routeTalkData* pTalkData = null;
			IM_CONTENTU* pContent = null;
			//char buf[255 + 1] = "";
			string str;

			if (null == pMisCnt || null == pMsg || null == pRcd) return null;

			pTalkData = &pMsg->data;
			pContent = (IM_CONTENTU*)pTalkData->buf;

			if (null == pTalkData || null == pContent) goto errLabel;

			mymemset((IntPtr)pRcd, 0, sizeof(IM_TASK_RCD));
			//
			//mylstrcpyn(pRcd->misServName, pMisCnt.cfg.misServName, mycountof(pRcd->misServName));
			pRcd->idInfo_send.ui64Id = pMsg->idInfo_taskSender.ui64Id;
			pRcd->tSendTime = pMsg->tStartTime;
			pRcd->uiTranNo = pMsg->uiTranNo;
			pRcd->idInfo_recv.ui64Id = pMsg->idInfo_taskReceiver.ui64Id;
			//
			pRcd->uiContentType = pContent->uiType; //  2008/05/29
													//
			mytime(&pRcd->tRecvTime);
			pRcd->usRespCode = usRespCode;
			//
			pRcd->id = pMsg->iTaskId;                   //  2010/04/23
			pRcd->uiMode = 0;
			pRcd->uiType = pMsg->uiTaskType;
			pRcd->iStatus = pMsg->iStatus;

			switch (pContent->uiType)
			{
				case Consts.CONST_imCommType_transferFileReq:
					//
					mylstrcpyn(pRcd->subject, pContent->transferFileReq.fileName, Consts.cntof_subject);
					mylstrcpyn(pRcd->content, pContent->transferFileReq.fullFilePath, Consts.cntof_content);
					//
					//_sntprintf(pRcd->propStrs[0], mycountof(pRcd->propStrs[0]), _T("%I64u"), pContent->transferFileReq.ui64FileLen);
					str = string.Format("{0}", pContent->transferFileReq.ui64FileLen);
					mytcsncpy(pRcd->propStr0, str, Consts.cntof_propStr);
					break;
				case Consts.CONST_imCommType_rtcCallReq:
					//
					//ulIp2Str(pContent->rtcCallReq.ulIp_caller, buf, mycountof(buf));
					//myStr2TChar(buf, pRcd->subject, mycountof(pRcd->subject));
					//
					break;
				case Consts.CONST_imCommType_transferAvInfo:
					//
					//_sntprintf(pRcd->subject, mycountof(pRcd->subject), _T("%d * %d"), pContent->transferAvInfo.tranInfo.video.vh_decompress.bih.biWidth, pContent->transferAvInfo.tranInfo.video.vh_decompress.bih.biHeight);
					str = string.Format("{0}*{1}", pContent->transferAvInfo.ass.tranInfo.video.vh_decompress.bih.biWidth, pContent->transferAvInfo.ass.tranInfo.video.vh_decompress.bih.biHeight);
					mytcsncpy(pRcd->subject, str, Consts.cntof_subject);
					//
					break;
				case Consts.CONST_imCommType_queryCustomerServiceOfficerReq:       //  2011/04/06
					break;
				case Consts.CONST_imCommType_transferGpsInfo:                      //  2012/04/19
					break;
				default:
#if __DEBUG__
					traceLog(_T("msg2TaskRcd failed, unknown contentType"));
#endif
					goto errLabel;
					break;
			}


			iErr = 0;
		errLabel:

			return iErr != 0 ? null : pRcd;
		}

	}
}
