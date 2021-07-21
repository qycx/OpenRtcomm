using System;
using System.Collections.Generic;
using System.Text;

partial class Consts
{
	public const int cntof_desc = 32;
	public const int CONST_maxConfMgrMems = 20;

}


//
namespace qy
{
   partial class qyFuncs
{
	public static unsafe	int getTalkerDesc(MIS_CNT pMisCnt, QY_MESSENGER_ID idInfo, char* talkerDesc, uint talkerDescCnt, char* shortName, uint shortNameCnt)
		{
			if (null==pMisCnt) return -1;
			QY_MESSENGER_ID* pIdInfo = &idInfo;

			CCtxQyMc pQyMc = g.g_pQyMc;
			CCtxQmc pProcInfo = pQyMc.get_pProcInfo();

			FUNCS_for_isCliHelp pFuncs = (FUNCS_for_isCliHelp)pProcInfo.pFuncs_for_isCliHelp;//  QY_GET_FUNCS_for_isCliHelp(  );
			QM_dbFuncs pDbFuncs = (QM_dbFuncs)pQyMc.p_g_dbFuncs;//  
			if (null==pDbFuncs) return -1;
			QM_dbFuncs  g_dbFuncs = pDbFuncs;


			//TCHAR talkerDescBuf[128 + 1] = _T("");
			//TCHAR displayNameBuf[128 + 1] = _T("");
			TMP_tBuf128 talkerDescBuf;
			int cntof_talkerDescBuf = Consts.cntof_tBuf128;
			TMP_tBuf128 displayNameBuf;
			int cntof_displayNameBuf = Consts.cntof_tBuf128;

			string str;

			if (null==pMisCnt || null==pIdInfo) return -1;

			if (pIdInfo->ui64Id == pMisCnt.idInfo.ui64Id)
			{
				fixed(char *pTalkerDesc=pMisCnt.talkerDesc.talkerDesc){
					fixed (char* pDisplayName = pMisCnt.displayName.displayName)
					{
						mylstrcpyn((char*)talkerDescBuf.tBuf, pTalkerDesc, cntof_talkerDescBuf);
						mylstrcpyn((char*)displayNameBuf.tBuf, pDisplayName, cntof_displayNameBuf);
					}
				}
			}
			else
			{

				//  2014/12/23		  		
				QY_MESSENGER_INFO messengerInfo;
				object pDb = null;
				int i;

				using (CQnmDb tmpObjDb = new CQnmDb())
				{
					;
					pDb = tmpObjDb.getAvailableDb(pQyMc.iDsnIndex_mainSys);

					//  
					mymemset((IntPtr)(byte*)&messengerInfo, 0, sizeof(QY_MESSENGER_INFO));
					//
					//mylstrcpyn(messengerInfo.misServName, _T(""), mycountof(messengerInfo.misServName));
					messengerInfo.idInfo.ui64Id = pIdInfo->ui64Id;

					//               

					//  2014/12/23
					if (true)
					{
						//if (!pQMem->talkerDesc[0])
						{
							QY_MESSENGER_REGINFO regInfo;

							if (!g_dbFuncs.pf_bGetMessengerRegInfoBySth(pDb, pQyMc.cfg.db.iDbType, ref qyFuncs.CONST_fieldIdTable_en, Consts.CONST_tabName_qyImObjRegInfoTab, "", pIdInfo, 0, &regInfo)) mymemset((IntPtr)(byte*)&regInfo, 0, sizeof(QY_MESSENGER_REGINFO));

							MY_REG_DESC desc;

							//regInfo2Desc(0, &regInfo, &desc, pQMem->talkerDesc, mycountof(pQMem->talkerDesc), pQMem->displayName, mycountof(pQMem->displayName));
						}
					}
				}

				//
				if (true)
				{
					//mylstrcpyn(talkerDescBuf, pQMem->talkerDesc, mycountof(talkerDescBuf));
					//mylstrcpyn(displayNameBuf, pQMem->displayName, mycountof(displayNameBuf));
				}
			}

			if (0 == talkerDescBuf.tBuf[0])
			{
				//_sntprintf(talkerDescBuf, mycountof(talkerDescBuf), _T("(%I64u)"), pIdInfo->ui64Id);
				str = string.Format("({0})", pIdInfo->ui64Id);
				mytcsncpy(talkerDescBuf.tBuf, str, cntof_talkerDescBuf);
			}
			if (0 == displayNameBuf.tBuf[0]) {
				//_sntprintf(displayNameBuf, mycountof(displayNameBuf), _T("(%I64u)"), pIdInfo->ui64Id);
				str = string.Format("({0})", pIdInfo->ui64Id);
				mytcsncpy(displayNameBuf.tBuf, str, cntof_displayNameBuf);
			}

			//

			//  errLabel:

			if (null!=talkerDesc && 0!=talkerDescCnt) mylstrcpyn(talkerDesc, talkerDescBuf.tBuf, (int)talkerDescCnt);
			if (null!=shortName && 0!=shortNameCnt) mylstrcpyn(shortName, displayNameBuf.tBuf, (int)shortNameCnt);

			return 0;
		}

	}
}
