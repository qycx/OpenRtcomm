using System;
using System.Collections.Generic;
using System.Text;

namespace qy
{
    partial class qyFuncs
{
		public struct Param_chkTrans
        {
			public int iTaskId;

			//
			public bool bNeedDo;

			//
			public bool bNeedChanged_o;

        };
		

		public static unsafe int tmpHandler_chkTrans(CTX_caller ctxCaller, object p_Param_chkTrans, object p1Param, object taskElemParam)
        {
			int iErr = -1;
			Param_chkTrans* pParam = (Param_chkTrans*)(IntPtr)p_Param_chkTrans;
			//p1
			TASK_common taskElem = (TASK_common)taskElemParam;

			CCtxQyMc pQyMc = g.g_pQyMc;
			CCtxQmc pProcInfo = pQyMc.get_pProcInfo();
			MIS_CNT pMisCnt = pProcInfo.pMisCnt;

			//
			QMC_TASK_INFO pTaskInfo = getQmcTaskInfoByIndex(ctxCaller, pProcInfo, taskElem.m_index_taskInfo, "");
			if (pTaskInfo == null) goto errLabel;
			if (pTaskInfo.var.iTaskId == pParam->iTaskId) {
				TASK_transferAv task = (TASK_transferAv)taskElem;
				//
				if ( task.myTask.ucbVideoConference)
                {
					iErr = 1; goto errLabel;
                }
				//
				QMC_taskData_common pTaskData = pTaskInfo.getTaskData();
				if (pTaskData == null) goto errLabel;
				if (pTaskData.uiType != Consts.CONST_taskDataType_conf) goto errLabel;
				QMC_taskData_conf pTc = (QMC_taskData_conf)pTaskData;
				DLG_TALK_videoConference videoConference = pTc.getVideoConference();
				if (videoConference == null) goto errLabel;

				if (videoConference.usCntLimit_activeMems_from != task.myTask.usCntLimit_transforms)
                {
					goto errLabel;
                }

				bool bExists_resource = false;
				int i;

				//
				for (i = 0; i < videoConference.usCntLimit_activeMems_from; i++)
                {
					DLG_TALK_videoConferenceActiveMemFrom pActiveMem = videoConference.activeMems_from[i];
					if (0 == pActiveMem.avStream.idInfo.ui64Id) continue;
					if (pActiveMem.avStream.idInfo.ui64Id == pMisCnt.idInfo.ui64Id) continue;
                    if (pActiveMem.avStream.obj.resObj.uiObjType != 0)
                    {
						bExists_resource = true;
						break;
                    }
				}

				bool bExists_decV = false;
				for (i = 0; i < videoConference.usCntLimit_activeMems_from; i++)
                {
					DLG_TALK_videoConferenceActiveMemFrom pActiveMem = videoConference.activeMems_from[i];
					bool bNeed_decV =false;
					//
					if (!bExists_decV) {
						if (0 != pActiveMem.avStream.idInfo.ui64Id
							&& pActiveMem.avStream.idInfo.ui64Id != pMisCnt.idInfo.ui64Id)
						{
							if (!bExists_resource)
                            {
								bNeed_decV = true;
								bExists_decV = true;
                            }
							else
                            {
								if (pActiveMem.avStream.obj.resObj.uiObjType != 0)
                                {
									bNeed_decV = true;
									bExists_decV = true;
                                }
                            }						
						}
					}
					//
					string tmp_str;
					tmp_str = string.Format("decV {0}.{1}", pActiveMem.avStream.idInfo.ui64Id, pActiveMem.avStream.obj.resObj.uiObjType);
					//
					QY_TRANSFORM pTransform = task.myTask.pTransforms[i];
					if (bNeed_decV)
                    {
						if (pTransform.video.hThread == null)
                        {
							if (pParam->bNeedDo)
							{
								int ii = 0;
								pTransform.bNeed_decV = true;
								startTransformThread_v(pProcInfo, pTransform,tmp_str);

							}
							else
							{
								pParam->bNeedChanged_o = true;
								iErr = 1; goto errLabel;
							}
                        }
                    }
					else
                    {
						if ( pTransform.video.hThread!=null)
                        {
							if (pParam->bNeedDo)
							{
								pTransform.bNeed_decV = false;
								stopTransformThread_v(pProcInfo, pTransform,tmp_str);
							}
							else
							{
								pParam->bNeedChanged_o = true;
								iErr = 1; goto errLabel;
							}
                        }

                    }

					//
					continue;
                }
						
			}



			iErr = 0;
		errLabel:
			return iErr;

        }




		public static unsafe int chkTransformThreads(CCtxQmc pProcInfo, int iTaskId)
		{
			int iErr = -1;

			Param_chkTrans param = new Param_chkTrans();

			if (iTaskId == 0) return -1;

			//
			param.iTaskId = iTaskId;
			pProcInfo.processQ_media.qTraverse(null, tmpHandler_chkTrans, (IntPtr)(byte*)&param, null);

			//
			if (param.bNeedChanged_o)
            {
				param = new Param_chkTrans();
				param.iTaskId = iTaskId;
				param.bNeedDo = true;
				//
				pProcInfo.processQ_media.qTraverse_mono(null, tmpHandler_chkTrans, (IntPtr)(byte*)&param, null);
				//
			}


			//
			iErr = 0;
		errLabel:
			return iErr;
		}


	}


}


