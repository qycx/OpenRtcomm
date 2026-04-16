
#include "stdafx.h"
#include "qyMcMainCommon_qt.h"

QYMC_HOTKEY	gHotKeys_main[] =
{
	//  {  ID_HKF5, 0, VK_F5, 0  },		//  不要热键了，不方便, 容易和别的软件冲突
	//  {  ID_HKF6, 0, VK_F6, 0  },
	//  {  ID_HKF7, 0, VK_F7, 0  },
	{	-1,					},
};


int  WINAPI  myMessageBox(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType)
{
	return  -1;
}

int  showDlgMcClientLogon(HINSTANCE  g_hInst, HWND  hMainWnd, void* pQyMcParam, PARAM_showDlgMcLogon* pParam)
{
	return  -1;
}

int  qnmLogOpEvent(int  iServiceId, QM_dbFuncs* pDbFuncs, QY_OBJ_DB* pObjDb, int  iEventType, LPCTSTR  des)		//  2007/01/02
{
	return  -1;
}
int  qnmLogOpEvent(int  iServiceId, QM_dbFuncs* pDbFuncs, void* pDbParam, int  iDbType, int  iEventType, LPCTSTR  usr, LPCTSTR  dsnName, LPCTSTR  des)
{
	return  -1;
}
int  qnmLogOpEvent(int  iServiceId, QM_dbFuncs* pDbFuncs, void* pDbParam, int  iDbType, int  iEventType, LPCTSTR  usr, LPCTSTR  des)
{
	return  -1;
}

unsigned  int  getVarSize_netMc(void* pQyMc)
{
	return  -1;
}
int  initVar_netMcGui(void* p0, void* p1, void* p2)
{
	return  -1;
}
int  exitVar_netMcGui(void* p0, void* p1, void* p2)
{
	return  -1;
}


extern "C" DWORD WINAPI mcThreadProc(LPVOID lpParameter)
{
	return  0;
}
extern "C" DWORD WINAPI mcThreadProc_isMgr(LPVOID lpParameter)
{
	return  0;
}

int  gGuiData_init(unsigned short usLangId, G_guiData_qyMc* pGuiData)
{
	return  0;
}

int  gGuiData_exit(G_guiData_qyMc* pGuiData)
{
	return  0;
}

int  enumLvSelEventFunc(QY_EVENTINFO* pEventInfo, PF_procLvEventFunc  pf, void* pObjDb, int  iLvType, void* pParam)
{
	return  -1;
}

BOOL  bQyOpenMcView(QY_MCVIEW_SEL* pParam, void* p1, void* p2)
{
	return  FALSE;
}
void  qyMcView_delAllColumns(void* pView, void* p1, void* p2)
{
	return;
}
BOOL  qyMcView_bAddColumns(void* pView, QY_COLUMNINFO* pColumns, void* p2)
{
	return  FALSE;
}

int  getLvColContent(HWND  hParent, HWND  hList, int  curnItem, LPCTSTR  colName, TCHAR* buf, unsigned  int  size)
{
	return  -1;
}

BOOL WINAPI  mySetDlgItemText(HWND hDlg, int nIDDlgItem, LPCTSTR lpString)
{
	return  false;
}

INT_PTR CALLBACK dlgProc_mcClientLogon(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	return  0;
}

int  showDlgQnmCfgOptionsIsClient(HINSTANCE  g_hInst, HWND  hParent, DLG_guiData_qnmCfgOptionsIsClient* pParam, QY_MC* pQyMc)
{
	return  -1;
}


int  displayNotification_talk_ts(HWND  hDlg, void* pGuiDataParam, LPCTSTR  hint)
{
	return  -1;
}

int  initVar_isGui_mgr(void* p0, void* p1, void* p2)
{
	return  -1;
}
int  exitVar_isGui_mgr(void* p0, void* p1, void* p2)
{
	return  -1;
}



int  closeOtherWnds_isMgr(BOOL* pbOtherWndExists)
{
	//traceLog(_T("closeOtherWnds_isMgr,  test_touchscreen"));
	return  -1;
}


  __declspec(dllexport)  int   set_g_pQnmCusResInfo_qisGuiPublic(  void  *  pQnmCusResInfo  )
  {
	  return 0;
  }

  __declspec(dllexport)  extern  "C"  BOOL  bQyOpenDb(LPCWSTR  connectStr, void* pDbParam)
  {
	  return false;
  }

  __declspec(dllexport)  extern  "C"  void* qyNewDb()
  {
	  return NULL;
  }

  __declspec(dllexport)  extern  "C"  void  qyFreeDb(void** ppDbParam)
  {
	  return;
  }

  __declspec(dllexport)  extern  "C"  void  qyCloseDb(void* pDbParam)
  {
	  return;
  }


  __declspec(dllexport)  BOOL  bGetSystemInfo(void* pDbParam, int  iDbType, QY_SYSTEMINFO_RCD* pSystemInfo)
  {
	  return false;
  }
  
  __declspec(dllexport)  extern  "C"  DWORD  get_CONST_qyDbOpenOptions()
  {
	  return 0;
  }

  DWORD WINAPI mcThreadProc_writeShm_dvt(LPVOID lpParameter)
  {
	  return  -1;
  }
