
#include	"stdafx.h"
#include	"qyMcMainCommon.h"


int  WINAPI  myMessageBox(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType)
{
	return  -1;
}

//
__declspec(dllexport)  int  viewDlgShareDynBmps_isCli(BOOL  bNeed_shareWebcamInConference)
{
	return  -1;
}

__declspec(dllexport)  int  netMc_procTreeEvent(void* pQyMcParam, void* pSel, void* pEventInfoParam)
{
	return  -1;
}

__declspec(dllexport) int  netMc_procTreeSel(void* pQyMcParam, void* p0, void* p1)
{
	return  -1;
}

__declspec(dllexport)  BOOL  bViewImObjListFunc(QY_MC  * pQyMc,QY_OBJ_DB* pObjDb, LPCTSTR  docName, LPCTSTR  wherePart)
{
	return  -1;
}

__declspec(dllexport)   BOOL  bViewMessengerRegInfoList(QY_MC  *  pQyMc,QY_OBJ_DB* pObjDb)
{
	return false;
}

__declspec(dllexport)  BOOL  bViewImGrpList(QY_MC  *  pQyMc,  QY_OBJ_DB* pObjDb, LPCTSTR  docName, LPCTSTR  wherePart)
{
	return false;
}

__declspec(dllexport)  BOOL  bViewImGrpMemList_isClient(QY_MC  *  pQyMc,  QY_OBJ_DB* pObjDb, LPCTSTR  docName, LPCTSTR  wherePart)
{
	return false;
}

__declspec(dllexport)  BOOL  bViewImTaskListFunc(QY_MC  *  pQyMc,  QY_OBJ_DB* pObjDb, LPCTSTR  docName, LPCTSTR  wherePart, BOOL  bHisTab)
{
	return false;
}

__declspec(dllexport)  int  doCmd_test(int  iMenuId)
{
	return -1;
}

__declspec(dllexport)  int  toEditRtspUrlForConf(TCHAR* url, unsigned  int  cnt)
{
	return  -1;
}



__declspec(dllexport)  BOOL  bViewImObjRuleList_is(QY_MC  *  pQyMc,  QY_OBJ_DB* pObjDb)
{
	return false;
}

