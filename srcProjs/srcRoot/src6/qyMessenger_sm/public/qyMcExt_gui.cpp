
#include	"stdafx.h"

#include	"qmOpenCommon.h"
#include	"qyMcExt_gui.h"
#include	"qmCfg_isCli.h"
#include	"ctxQyMc.h"
#include	"smCommProc.h"




//
int QyMcExt_gui::getSmCfgInfo(TCHAR* cfgDirName, int cfgDirNameLen)
{
	CCtxQyMc* pQyMc = m_var.m_pQyMc;

	//
	::getSmCfgDir_cli(cfgDirName, cfgDirNameLen);
	//
	TCHAR* tDir = cfgDirName;
	//CCtxQmc* pProcInfo = this;
	if (bDir(tDir)) {
		_sntprintf(pQyMc->cfg.tmInitFile, mycountof(pQyMc->cfg.tmInitFile), _T("%s%s"), tDir, CONST_cfgFileName_tmInit);

		//
		_sntprintf(pQyMc->cfg.smCfgFile, mycountof(pQyMc->cfg.smCfgFile), _T("%s%s"), tDir, CONST_cfgFileName_cli_smCfg);

		//
		//if (m_bUseKeyToLogin_forQmcGui) 
		{
			//_sntprintf(pQyMc->cfg.tmInitFile, mycountof(pQyMc->cfg.tmInitFile), _T("%s.%d"), pQyMc->cfg.tmInitFile, pQyMc->appParams.iSeqNoSelected_appObjPrefix);

		}

		//
		_sntprintf(pQyMc->cfg.smTmpLogFile, mycountof(pQyMc->cfg.smTmpLogFile), _T("%s%s"), tDir, CONST_logFileName_smTmp);
		//
		_sntprintf(pQyMc->cfg.hkPortStatusFile, mycountof(pQyMc->cfg.hkPortStatusFile), _T("%s%s"), tDir, CONST_cfgFileName_hkPortStatus);
		//
		TCHAR  tLogDir[256];
		_sntprintf(tLogDir, mycountof(tLogDir), _T("%s\\log\\"), tDir);
		if (!bDir(tLogDir)) {
			CreateDirectory(tLogDir, NULL);
		}
		//
		_sntprintf(pQyMc->cfg.qmcLogFile, mycountof(pQyMc->cfg.qmcLogFile), _T("%s\\log\\%s"), tDir, CONST_logFileName_qmcStatus);

		//
		_sntprintf(pQyMc->cfg.ipcProcInitFile, mycountof(pQyMc->cfg.ipcProcInitFile), _T("%s%s"), tDir, CONST_cfgFileName_ipcProcInit);

		//
	}


	//
	return  0;
}

