
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"qyWmComm.h"

#include	"myresource.h"

#include	"qyCusResTemp.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qmcDynBmp.h"
#include	"qmcVWall.h"
//  #include	"DlgDynBmps.h"
#include	"dlgDynBmpsProc.h"
//  #include	"dlgTalk.h"
#include	"dlgtalkproc.h"
#include	"qyDynLib.h"
#include	"qmcCmdProc.h"
//
#include	"isCmdConst.h"
//
#include	"myDb.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"
#include	"qmcTaskInfo.h"
#include	"isCliD3dPublic.h"
#include	"ctxQmc.h"

#include	"qmcCommFunc_iscli.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




// 
__declspec(  dllexport  )   void myListCtrl_delAllColumns(  HWND  hListCtrl  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CListCtrl  *  pListCtrl  =  (  CListCtrl  *  )CListCtrl::FromHandle(  hListCtrl  );

	if  (  !pListCtrl  )  return;

	 for ( ; ; )  {
		 if  (  !pListCtrl->DeleteColumn( 0  )  )  break;
	 }
}

   __declspec(  dllexport  )  BOOL myListCtrl_bAddColumns(  HWND  hListCtrl,  QY_COLUMNINFO * pColumns  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CListCtrl  *  pListCtrl  =  (  CListCtrl  *  )CListCtrl::FromHandle(  hListCtrl  );

	 if  (  !pListCtrl  )  return  FALSE;
	 if  (  !pColumns  )  return  TRUE;
	 
	 int		i;
	 LV_COLUMN	lvc;

	 lvc.mask  =  LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	
	 for  (  i  =  0;  pColumns[i].type  !=  -1  &&  pColumns[i].label[0];  i  ++  )  {
		   lvc.iSubItem		=	i;
		   lvc.pszText		=	pColumns[i].label;
		   lvc.cx			=	pColumns[i].width;
		   lvc.fmt			=	pColumns[i].fmt;
		   pListCtrl->InsertColumn(  i,  &lvc  );
	  }
	
	 return  TRUE;
}

//	int InsertItem(_In_ const LVITEM* pItem);
//  int InsertItem(_In_ int nItem, _In_z_ LPCTSTR lpszItem);

__declspec(  dllexport  )  int  myListCtrl_InsertItem(  HWND  hListCtrl,  int nItem, LPCTSTR lpszItem  )
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );
	if  (  !pListCtrl  )  return  -1;

	return  pListCtrl->InsertItem(  nItem, lpszItem  );
}


__declspec(  dllexport  )  int  myListCtrl_InsertItem(  HWND  hListCtrl,  int nItem, LPCTSTR lpszItem, int nImage  )
{

	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );
	if  (  !pListCtrl  )  return  -1;

	return  pListCtrl->InsertItem(  nItem, lpszItem, nImage );
}


__declspec(  dllexport  )  BOOL myListCtrl_SetItemText(  HWND  hListCtrl,  int nItem, int nSubItem, LPCTSTR lpszText)
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );
	if  (  !pListCtrl  )  return  FALSE;

	return  pListCtrl->SetItemText(  nItem, nSubItem, lpszText);
}


__declspec(  dllexport  )  BOOL myListCtrl_SetItemData(  HWND  hListCtrl,  int nItem, DWORD_PTR dwData  )
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );
	if  (  !pListCtrl  )  return  FALSE;

	return  pListCtrl->SetItemData(  nItem, dwData  );
}


__declspec(  dllexport  )  BOOL  myListCtrl_DeleteAllItems(  HWND  hListCtrl  )
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );

	if  (  !pListCtrl  )  return  FALSE;

	return  pListCtrl->DeleteAllItems(  );
}

__declspec(  dllexport  )  int  myListCtrl_GetItemCount(  HWND  hListCtrl  )
{

	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );
	if  (  !pListCtrl  )  return  -1;

	return  pListCtrl->GetItemCount(   );
}

__declspec(  dllexport  )  BOOL myListCtrl_SetItemState(  HWND  hListCtrl,  int nItem, UINT nState, UINT nMask  )
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );

	if  (  !pListCtrl  )  return  FALSE;

	return  pListCtrl->SetItemState(  nItem,  nState,  nMask  );
}

__declspec(  dllexport  )  BOOL myListCtrl_Update(  HWND  hListCtrl,  int nItem  )
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );

	if  (  !pListCtrl  )  return  FALSE;

	return  pListCtrl->Update(  nItem  );
}

__declspec(  dllexport  )  int  myListCtrl_GetItemText(  HWND  hListCtrl,  int nItem,  int nSubItem,  LPTSTR lpszText,  int nLen  )
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );
	if  (  !pListCtrl  )  return  -1;

	return  pListCtrl->GetItemText(  nItem,  nSubItem,  lpszText,  nLen  );
}

__declspec(  dllexport  )  BOOL myListCtrl_ModifyStyle(  HWND  hListCtrl,  DWORD dwRemove,   DWORD dwAdd,   UINT nFlags )
{
	//  if  (  !::IsWindow(hListCtrl)  )  return  FALSE;

	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );
	if  (  !pListCtrl  )  return  FALSE;

	return  pListCtrl->ModifyStyle(  dwRemove, dwAdd, nFlags  );
}

__declspec(  dllexport  )  DWORD myListCtrl_SetExtendedStyle(  HWND  hListCtrl,  DWORD dwNewStyle)
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );
	if  (  !pListCtrl  )  return  -1;

	return  pListCtrl->SetExtendedStyle(  dwNewStyle  );
}

__declspec(  dllexport  )  void  *  myListCtrl_SetImageList(  HWND  hListCtrl,  void  * pImageList,  int nImageList)
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );
	if  (  !pListCtrl  )  return  NULL;

	return  pListCtrl->SetImageList(  (  CImageList  *  )pImageList,  nImageList  );
}

__declspec(  dllexport  )  int  myListCtrl_InsertColumn(  HWND  hListCtrl,  int nCol,  const LVCOLUMN* pColumn)
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );
	if  (  !pListCtrl  )  return  -1;

	return  pListCtrl->InsertColumn(  nCol,  pColumn  );
}
__declspec(  dllexport  )  BOOL myListCtrl_GetColumn(  HWND  hListCtrl,  int nCol, LVCOLUMN* pColumn  )
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );

	if  (  !pListCtrl  )  return  FALSE;

	return  pListCtrl->GetColumn(  nCol,  pColumn  );
}

__declspec(  dllexport  )  int  myListCtrl_FindItem(  HWND  hListCtrl,  LVFINDINFO* pFindInfo, int nStart  )
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );
	if  (  !pListCtrl  )  return  -1;

	return  pListCtrl->FindItem(  pFindInfo,  nStart  );
}

__declspec(  dllexport  )  BOOL myListCtrl_GetItem(  HWND  hListCtrl,  LVITEM* pItem  )
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );

	if  (  !pListCtrl  )  return  FALSE;

	return  pListCtrl->GetItem(  pItem  );
}
__declspec(  dllexport  )  BOOL myListCtrl_SetItem(  HWND  hListCtrl,  LVITEM* pItem  )
{
	CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );

	if  (  !pListCtrl  )  return  FALSE;

	return  pListCtrl->SetItem(  pItem  );
}



///////////////////////////////////////////////////
#if  0
__declspec(  dllexport  )  BOOL myImageList_Create(  void  *  pImageList,  UINT nBitmapID, int cx, int nGrow, COLORREF crMask  )
{
	if  (  !pImageList  )  return  FALSE;

	return  (  (  CImageList  *  )pImageList  )->Create( nBitmapID,  cx,  nGrow,  crMask );
}

__declspec(  dllexport  )  BOOL myImageList_DeleteImageList(  void  *  pImageList  )
{
	if  (  !pImageList  )  return  FALSE;

	return  (  (  CImageList  *  )pImageList  )->DeleteImageList(  );
}
#endif

////////
__declspec(  dllexport  )  void  myImageList_free(  void  *  pImageListParam  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CImageList  *  pImageList  =  (  CImageList  *  )pImageListParam;
	if  (  !pImageList  )  return;

	delete  pImageList;
}

__declspec(  dllexport  )  void  *  myImageList_new(  UINT nBitmapID, int cx, int nGrow, COLORREF crMask  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int				iErr  =  -1;
	CImageList  *  pImageList	=	NULL;

	pImageList  =  new  CImageList(  );
	if  (  !pImageList  )  return  NULL;

	try  {
		 if  (  !(  (  CImageList  *  )pImageList  )->Create( nBitmapID,  cx,  nGrow,  crMask )  )  goto  errLabel;
	}
	catch  (  ...  )  {
		   showInfo_open0(  0,  0,  _T(  "myImageList_new exception"  )  );
		   goto  errLabel;
	}

	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		myImageList_free(  pImageList  );
		return  NULL;
	}
	return  pImageList;
}


//////////////////////////////////////////////////

 

//  2014/12/01
int  tmp_displayTaskAvFrom(  CListCtrl  *  pListCtrl,  MIS_MSGU  *  pMsgElem,  IM_CONTENTU  *  pContent,  PROC_TASK_AV  *  pTask,  TASK_AV_FROM  *  pFrom,  int  j,  int  &  index    )
{
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	TCHAR  tBuf[256];
	char  timeBuf[CONST_qyTimeLen  +  1];
	char  displayBuf[128];
	int  i;
	  

						   if  (  !pFrom->idInfo.ui64Id  )  return  -1;

						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );
						   i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
						   tBuf[0]  =  0;  //  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf    );
						   i  ++  ; pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );
						   i  ++  ;	
						   i  ++  ;	
						   i  ++  ;

						   tBuf[0]  =  0;
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "from %d: %I64u"  ),  j,  pFrom->idInfo.ui64Id  );
						   //  2014/09/04
						#if  0
						   if  (  pFrom->video.dynBmp.usIndex_obj  )  {
							   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ind_obj %d"  ),  tBuf,  (  int  )pFrom->video.dynBmp.usIndex_obj  );
						   }
						#endif
						   //
						   char	fourccStr[16];
						   //  iFourcc2Str(  pFrom->video.vh_compress_recvd.bih.biCompression,  fourccStr,  mycountof(  fourccStr  )  );
						   safeStrnCpy(  pFrom->video.tv_recvd.compressor.common.fourccStr,  fourccStr,  mycountof(  fourccStr  )  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( a %d, %d, 0x%x,%d,%d,%d,%d )"  ),  tBuf,  pFrom->audio.ta_recvd.uiTranNo_openAvDev,  (  int  )pFrom->audio.ta_recvd.compressor.common.ucCompressors,  pFrom->audio.ta_recvd.ah_compress.wfx.wFormatTag,  pFrom->audio.ta_recvd.ah_compress.wfx.nChannels,  pFrom->audio.ta_recvd.ah_compress.wfx.nSamplesPerSec,  pFrom->audio.ta_recvd.ah_compress.wfx.wBitsPerSample,  pFrom->audio.ta_recvd.ah_compress.wfx.nAvgBytesPerSec  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( v %d, %dfps, %d, %s, %dX%d, %s. stream %d,%d,%d )"  ),  tBuf,  pFrom->video.tv_recvd.uiTranNo_openAvDev,  (  int  )pFrom->video.tv_recvd.compressor.common.usMaxFps_toShareBmp,  (  int  )pFrom->video.tv_recvd.compressor.common.ucCompressors,  CString(  fourccStr  ),   pFrom->video.tv_recvd.vh_compress.bih.biWidth,  pFrom->video.tv_recvd.vh_compress.bih.biHeight,  (  0  ?  _T(  "flip"  )  :  _T(  ""  )  ),  
							   (  int  )pFrom->video.tv_recvd.vh_stream.usCnt,  (  int  )pFrom->video.tv_recvd.vh_stream.mems[0].usLen,  (  int  )pFrom->video.tv_recvd.vh_stream.mems[1].usLen    ); 
						   //  2011/12/24
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s.  audio player:"  ),  tBuf  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %dms, %dms, %dms"  ),  tBuf,  (  int  )pFrom->audio.ta_recvd.compressor.playCfg.usMinTimeInMsOfAudioDataPlaying,  (  int  )pFrom->audio.ta_recvd.compressor.playCfg.usAudioDataAddedToPlayEveryTime,  (  int  )pFrom->audio.ta_recvd.compressor.playCfg.usNotifyIntervalInMs_needMoreAudioData  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %dms, %dms, %dms"  ),  tBuf,  (  int  )pFrom->audio.ta_recvd.compressor.playCfg.usMinTimeInMsToPlay,  (  int  )pFrom->audio.ta_recvd.compressor.playCfg.usMaxTimeInMsToPlay,  (  int  )pFrom->audio.ta_recvd.compressor.playCfg.usMaxTimeInMsToBeRemoved  );
						   //
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

						   i  ++  ;	

						   getTimelStr(  pMsgElem->task.tStartTime,  timeBuf,  mycountof(  timeBuf  )  );
						   qyDisplayTime(  timeBuf,  displayBuf,  mycountof(  displayBuf  )  );
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  CString(  displayBuf  )  );		

						   index  ++  ;


						   return  0;
					  
}


//
int  tmp_displayTrans(  CListCtrl  *  pListCtrl,  MIS_MSGU  *  pMsgElem,  IM_CONTENTU  *  pContent,  PROC_TASK_AV  *  pTask,  QY_TRANSFORM  *  pTransform,  int  j,  int  &  index,  LPCTSTR  trans_prefix   )
{		
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	TCHAR  tBuf[256];
	char  timeBuf[CONST_qyTimeLen  +  1];
	char  displayBuf[128];
	int  i;

	if  (  !trans_prefix  )  trans_prefix  =  _T(  ""  );

	
	
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );
						   i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
						   tBuf[0]  =  0;	//  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );
						   i  ++  ; pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );
						   i  ++  ;	
						   i  ++  ;
						   i  ++  ;	

						   tBuf[0]  =  0;
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s trans %d:"  ),  trans_prefix,  j  );
						   if  (  pTransform->audio.bRunning  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( a %d, active_from %d )"  ),  tBuf,  pTransform->audio.ta.uiTranNo_openAvDev,  pTransform->audio.index_activeMems_from  );
						   if  (  pTransform->video.bRunning  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( v %d, active_from %d )"  ),  tBuf,  pTransform->video.tv.uiTranNo_openAvDev,  pTransform->video.index_activeMems_from  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s.  a: nodes (%d,%d), nStep %d, elp %dms"  ),  tBuf,  getQ2Nodes_toGetMsg(  &pTransform->audio.q2  ),  getQ2Nodes_toPostMsg(  &pTransform->audio.q2  ),  pTransform->audio.debugStep.nStep_debug,  GetTickCount(  )  -  pTransform->audio.debugStep.dwTickCnt_step_debug  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s,  v_pre: nStep %d, elp %dms, iErr %d"  ),  tBuf,  pTransform->v_preTransThread.debugStep.nStep_debug,  GetTickCount(  )  -  pTransform->v_preTransThread.debugStep.dwTickCnt_step_debug,  pTransform->v_preTransThread.debugStep.iErr_thread  );	//  2012/09/07
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s,  v: decMod %s, nodes (%d,%d), nStep %d, elp %dms"  ),  tBuf,  qyGetDesByType1(  CONST_moduleTypeTable_en,  pTransform->video.uiModuleType_toDec  ),  getQ2Nodes_toGetMsg(  &pTransform->video.q2  ),  getQ2Nodes_toPostMsg(  &pTransform->video.q2  ),  pTransform->video.debugStep.nStep_debug,  GetTickCount(  )  -  pTransform->video.debugStep.dwTickCnt_step_debug  );
						   
						   //
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, pts_first %d, time_dec %dms, pts_last %d"  ),  tBuf,  pTransform->video.decInfo.pts.uiPts_first,  GetTickCount(  )  -  pTransform->video.decInfo.pts.dwTickCnt_start,  pTransform->video.decInfo.pts.uiPts_lastRecvd  );
						   //
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s,  errs: notAccept %d, Input %d, output %d, index %d"  ),  tBuf,  pTransform->video.debugStep.uiCnt_DMO_E_NOTACCEPTING,  pTransform->video.debugStep.nErrs_ProcessInput,  pTransform->video.debugStep.nErrs_ProcessOutput,  pTransform->video.debugStep.nErrs_pOutputBuffers_index  ); 
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

						   i  ++  ;	

						   i  ++  ;	

						   index  ++  ;

#if  0
						   //  2015/01/15						   		
						   if  (  pTransform->video.uiModuleType_toDec  ==  CONST_moduleType_mediaSdk_dec  )  {
							   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );
							   i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
							   i  ++  ;	
							   i  ++  ; 
							   i  ++  ;	
							   i  ++  ;
							   i  ++  ;	

							   tBuf[0]  =  0;
							   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  " more of trans %d:"  ),  j  );
							   //  2015/01/11
							   //if  (  pTransform->video.debugStep.dec.nStep_debug  )  
							   {
								   DEBUG_step_dec  *  pStep_dec  =  &pTransform->video.debugStep.dec;
								   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, {nStep_dec %d, elp %dms, excpt %d, sts_run %d"  ),  tBuf,  pStep_dec->nStep_debug,  GetTickCount(  )  -  pStep_dec->dwTickCnt_step_debug,  pStep_dec->bException,  pStep_dec->sts_run  );
								   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, call_Init %d, sts_Init %d, call_RunDec %d"  ),  tBuf,  pStep_dec->bCalled_pipeline_Init,  pStep_dec->sts_pipeline_Init,  pStep_dec->bCalled_RunDecoding  );
								   
								   //
								   DEBUG_step_dec  *  p  =  pStep_dec;
								   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s,sts_ReadNextFrame %d,sts_SyncOSurf370 %d, sts_SyncOSurf396 %d, sts_m_pDeliv %d, sts_Dec %d, sts_SyncOSurf452 %d, sts_SyncOSurf482 %d, bHere_%d"  ),  
															tBuf,
															p->sts_ReadNextFrame,
															p->sts_SyncOutputSurface370,
															p->sts_SyncOutputSurface396,
															p->sts_m_pDeliveredEvent_TimedWait,
															p->sts_DecodeFrameAsync,
															p->sts_SyncOutputSurface452,
															p->sts_SyncOutputSurface482,
															p->bHere_PrintPerFrameStat  );					

								   //
								   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s}"  ),  tBuf  );
							   }
							   //
							   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

							   i  ++  ;	

							   i  ++  ;	

							   index  ++  ;

							   //							   						
							   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );
							   i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
							   i  ++  ;	
							   i  ++  ; 
							   i  ++  ;	
							   i  ++  ;
							   i  ++  ;	

							   tBuf[0]  =  0;
							   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  " more of trans %d:"  ),  j  );
							   //  2015/01/11
							   //if  (  pTransform->video.debugStep.dec.nStep_debug  )  
							   {
								   DEBUG_step_dec  *  pStep_dec  =  &pTransform->video.debugStep.dec;
								   //
								   DEBUG_step_dec  *  p  =  pStep_dec;
								   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, SyncOSurf( sts_SyncOp324 %d, sts_DeliverO347 %d, bHere_375 %d"  ),  
															tBuf,  p->sts_SyncOperation324,  p->sts_DeliverOutput347,  p->bHere_375_SyncOutputSurface  );

								   //
								   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s}"  ),  tBuf  );
							   }
							   //
							   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

							   i  ++  ;	

							   i  ++  ;	

							   index  ++  ;

						   }
#endif
					  
						   return  0;
}


//
 int  tmpHandler_displayRealTimeTasks(  QY_MC  *  pQyMc,  void * p0,  void * p1,  TASK_common * taskElem  )
{
	TCHAR		tBuf[512]							=	_T(  ""  );
	int			index;
	int			i									=	0;
	char		timeBuf[CONST_qyTimeLen  +  1]		=	"";
	char		displayBuf[255  +  1]				=	"";
	int			j;
	//QY_MC	*	pQyMc								=	QY_GET_GBUF(  );
	CCtxQmc *  pProcInfo = (CCtxQmc*)pQyMc->get_pProcInfo();

	CListCtrl  *  pListCtrl  =  ( CListCtrl  *  )p0;
	int  *  piCnt=(int  *  )p1;

	//
	QMC_TASK_INFO * pTaskInfo=(QMC_TASK_INFO*)getQmcTaskInfoByIndex(pProcInfo, taskElem->m_index_taskInfo);
	if(!pTaskInfo) return -1;

	MIS_MSGU  *  pMsgElem=&pTaskInfo->var.pTaskData->msgU;

	//
	if  (  !pListCtrl  ||  !piCnt  ||  !pMsgElem  )  return  -1;

	index  =  *piCnt;


	if  (  pMsgElem->uiType  ==  CONST_misMsgType_task  )  {
		IM_CONTENTU		*	pContent		=	(  IM_CONTENTU  *  )pMsgElem->task.data.buf;
		MIS_CNT			*	pMisCnt			=  (  MIS_CNT  *  )pMsgElem->task.pMisCnt;
		MC_VAR_isCli		*	pProcInfo			=	NULL;
		if  (  pMisCnt  )  pProcInfo		=  QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;

		switch  (  pContent->uiType  )  {
				case  CONST_imCommType_transferAvInfo:  
					{
					  TRAN_conf_cfg  *  pConfCfg  =  NULL;
  					  AV_TRAN_INFO  *  pAvTran  =  NULL;
					  MOSAIC_TRAN_INFO  *  pMosaicTran_video  =  NULL;
					  MOSAIC_TRAN_INFO  *  pMosaicTran_resource  =  NULL;
					  //QY_MESSENGER_ID	content_idInfo_logicalPeer;  content_idInfo_logicalPeer.ui64Id  =  0;
					  PROXIED_TRAN_INFO  *  pProxiedTranInfo  =  NULL;
					  PROC_TASK_AV  *  pTask  =  NULL;
					  //
					  TRAN_conf_cfg		tmp_confCfg;
					  MOSAIC_TRAN_INFO	tmp_mosaicTran;
					  memset(  &tmp_confCfg,  0,  sizeof(  tmp_confCfg  )  );
					  pConfCfg  =  &tmp_confCfg;
					  memset(  &tmp_mosaicTran,  0,  sizeof(  tmp_mosaicTran  )  );
					  pMosaicTran_video  =  &tmp_mosaicTran;
					  pMosaicTran_resource  =  &tmp_mosaicTran;
					  //
					  if  (  pTaskInfo->var.pTaskData->uiType  !=  CONST_taskDataType_conf  )  {
						  break;
					  }
					  QMC_taskData_conf  *  pTc  =  ( QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;

					  //
					  if  (  pContent->uiType  ==  CONST_imCommType_transferAvInfo  )  {
						  pConfCfg  =  &pContent->transferAvInfo.confCfg;
						  pMosaicTran_video  =  &pContent->transferAvInfo.confMosaicTranInfo_video;
						  pMosaicTran_resource  =  &pContent->transferAvInfo.confMosaicTranInfo_resource;
						  //content_idInfo_logicalPeer.ui64Id  =  pContent->transferAvInfo.idInfo_logicalPeer.ui64Id;
						  pProxiedTranInfo  =  &pContent->transferAvInfo.proxiedTranInfo;
						  
						  pAvTran  =  &pContent->transferAvInfo.ass.tranInfo;
						  //
						  TASK_transferAv  *  task=(TASK_transferAv*)taskElem;
						  //pTask  =  &pTransferAvTask->myTask;
						  pTask  =  &task->myTask;//get_transferAvInfo_pTask(  &pContent->transferAvInfo,  _T(  ""  )  );						
					  }
					  if  (  !pTask  )  break;

					  //  2015/09/08					  				
					  
					  //
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );
					  i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
					  tBuf[0]  =  0;
					  if  (  pMsgElem->task.uiTaskType  )  {
						  if  (  pTaskInfo->var.m_bReplyTask  )  {
							  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%sReply: "  ),  tBuf  );
							  //_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%stn_org %d."  ),  tBuf,  pContent->transferAvReplyInfo.uiTranNo_org  );
							  }
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s"  ),  tBuf,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsgElem->task.uiTaskType  )  );
						  }
					  else  {
						    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s"  ),  tBuf,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );  							
					  }
					  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

					  i  ++  ;	pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pMsgElem->task.idInfo_taskSender.ui64Id  );
					  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pMsgElem->task.idInfo_taskReceiver.ui64Id  );
					  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pMsgElem->task.addr_logicalPeer.idInfo.ui64Id  );
					  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );
					  //
					  tBuf[0]  =  0;
					  //
					  if  (  pContent->uiType  ==  CONST_imCommType_transferAvInfo  )  {
						  switch  (  pMsgElem->task.uiTaskType  )  {
								  case  CONST_imTaskType_shareDynBmp:
								  case  CONST_imTaskType_viewDynBmp:
									    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s, %d "  ),  tBuf,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  ),  pContent->transferAvInfo.ass.resObj.uiObjType  ),  pContent->transferAvInfo.ass.resObj.usIndex_obj  );
										if  (  pContent->transferAvInfo.viewDynBmp.ucbSaveVideo  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s save"  ),  tBuf  );
										break;
							  default:
									  break;
						  }
					  }
					  //					  
					  //_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%stn %d"  ),  tBuf,  pMsgElem->task.uiTranNo  );
					  //
					  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );
					  index  ++  ;


					  //
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );			
					  i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
					  i  ++  ;
					  i  ++  ;  pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );
					  i  ++  ;
					  i  ++  ;
					  i  ++  ;
					  //
					  tBuf[0]  =  0;
					  if  (  pTask->bTaskInvalid  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "INVALID! "  )  );
					  //
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%sver:%d.%d."  ),  tBuf,  pAvTran->head.shClientVer  /  100,  pAvTran->head.shClientVer  %  100  );
					  //
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s a %d, v %d"  ),  tBuf,  pAvTran->audio.uiTranNo_openAvDev,  pAvTran->video.uiTranNo_openAvDev  );
					  char	fourccStr[16];
					  //  iFourcc2Str(  pAvTran->video.vh_compress.bih.biCompression,  fourccStr,  mycountof(  fourccStr  )  );
					  safeStrnCpy(  pAvTran->video.compressor.common.fourccStr,  fourccStr,  mycountof(  fourccStr  )  );
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( a %d, 0x%x,%d,%d,%d,%d )"  ),  tBuf,  pAvTran->audio.uiTranNo_openAvDev,  pAvTran->audio.ah_compress.wfx.wFormatTag,  pAvTran->audio.ah_compress.wfx.nChannels,  pAvTran->audio.ah_compress.wfx.nSamplesPerSec,  pAvTran->audio.ah_compress.wfx.wBitsPerSample,  pAvTran->audio.ah_compress.wfx.nAvgBytesPerSec  );
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( v %d, %s, %dX%d )"  ),  tBuf,  pAvTran->video.uiTranNo_openAvDev,  CString(  fourccStr  ),   pAvTran->video.vh_compress.bih.biWidth,  pAvTran->video.vh_compress.bih.biHeight  ); 				  
					  if  (  pTask->video.usMaxFps_toShareBmp_conf  )  {
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, fps_conf %d"  ),  tBuf,  (  int  )pTask->video.usMaxFps_toShareBmp_conf  );
					  }
					  if  (  pConfCfg->conf.iWidth_pic_conf  ||  pConfCfg->conf.iHeight_pic_conf  )  {
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, wh_conf %dX%d"  ),  tBuf,  pConfCfg->conf.iWidth_pic_conf,  pConfCfg->conf.iHeight_pic_conf  );
					  }
					  //
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. aPlayer:"  ),  tBuf  );
					  //  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, minPlaying %dms, maxPlaying %dms, notify %dms"  ),  tBuf,  pTask->audio.playCfg.uiMinTimeInMsOfAudioDataPlaying,  pTask->audio.playCfg.uiAudioDataAddedToPlayEveryTime,  pTask->audio.playCfg.uiNotifyIntervalInMs_needMoreAudioData  );
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %d, %d, %d"  ),  tBuf,  (  int  )pTask->audio.playCfg.usMinTimeInMsOfAudioDataPlaying,  (  int  )pTask->audio.playCfg.usAudioDataAddedToPlayEveryTime,  (  int  )pTask->audio.playCfg.usNotifyIntervalInMs_needMoreAudioData  );
					  //  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, maxToPlay %dms, toBeRemoved %dms"  ),  tBuf,  pTask->audio.playCfg.uiMaxTimeInMsToPlay,  pTask->audio.playCfg.uiMaxTimeInMsToBeRemoved  );
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %d, %d, %d"  ),  tBuf,  (  int  )pTask->audio.playCfg.usMinTimeInMsToPlay,  (  int  )pTask->audio.playCfg.usMaxTimeInMsToPlay,  (  int  )pTask->audio.playCfg.usMaxTimeInMsToBeRemoved  );
					  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

					  tBuf[0]  =  0;
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %d"  ),  qyGetDesByType1(  CONST_qyStatusTable_en,  pMsgElem->task.iStatus  ),  pMsgElem->task.iStatus  );
					  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

					  getTimelStr(  pMsgElem->task.tStartTime,  timeBuf,  mycountof(  timeBuf  )  );
					  qyDisplayTime(  timeBuf,  displayBuf,  mycountof(  displayBuf  )  );
					  //
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %d"  ),  CQyString(  displayBuf  ),  pMsgElem->task.uiTranNo  );
					  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );		
					  index  ++  ;


					  //  2014/11/22
#if  0
					  if  (  pContent->uiType  ==  CONST_imCommType_transferAvInfo  )  {
						  TRANSFER_AV_INFO  *  pTransferAvInfo  =  &pContent->transferAvInfo;
						  if  (  pTransferAvInfo->idInfo_logicalPeer.ui64Id  ||  pTransferAvInfo->uiTranNo_avTask_starter  )  {
							  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );			
							  i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
							  i  ++  ;
							  i  ++  ;
							  i  ++  ;
							  i  ++  ;
							  i  ++  ;  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "talker %I64u, tn_starter %d"  ),  pTransferAvInfo->idInfo_logicalPeer.ui64Id,  pTransferAvInfo->uiTranNo_avTask_starter  );
							  pListCtrl->SetItemText(  index,  i,  tBuf  );
							  i  ++  ;
							  index  ++  ;
						  }
					  }
#endif


					  //  2014/11/21
					  if  (  pProxiedTranInfo  &&  pProxiedTranInfo->idInfo.ui64Id  )  {
							  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );			
							  i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
							  i  ++  ;
							  i  ++  ;
							  i  ++  ;
							  i  ++  ;
							  i  ++  ;  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "proxied: [%I64u,%d]  a %d, v %d"  ),  pProxiedTranInfo->idInfo.ui64Id,  pProxiedTranInfo->uiObjType,  pProxiedTranInfo->ti.audio.uiTranNo_openAvDev,  pProxiedTranInfo->ti.video.uiTranNo_openAvDev  );
							  pListCtrl->SetItemText(  index,  i,  tBuf  );
							  i  ++  ;
							  index  ++  ;

					  }

					  //  2014/11/09
					  int  tmp_i;
					  for  (  tmp_i  =  0;  tmp_i  <  2;  tmp_i  ++  )  {
						   //
						   TCHAR  *  tag  =  _T(  ""  );
						   MOSAIC_TRAN_INFO  *  pMosaicTran  =  NULL;
						   int  iIndex_sharedObj_mosaic  =  -1;
						   //
						   //
						   switch  (  tmp_i  )  {
								   case  0:
									     tag  =  _T(  "mosaicV"  );
									     pMosaicTran  =  pMosaicTran_video;
										 iIndex_sharedObj_mosaic  =  pTask->confMosaicMaker.iIndex_sharedObj_video;
										 break;
								   case  1:
									     tag  =  _T(  "mosaicR"  );
									     pMosaicTran  =  pMosaicTran_resource;
										 iIndex_sharedObj_mosaic  =  pTask->confMosaicMaker.iIndex_sharedObj_resource;
										 break;
								   default:
										  break;
						   }
						   if  (  !pMosaicTran  )  break;
						   //
						   //
						  if  (  pMosaicTran->resObj.uiObjType  )  {
							  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );			
							  i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
							  i  ++  ;
							  i  ++  ;
							  i  ++  ;
							  i  ++  ;
							  i  ++  ;
							  i  ++  ;  
							  char	fourccStr[16];
							  safeStrnCpy(  pMosaicTran->video.compressor.common.fourccStr,  fourccStr,  mycountof(  fourccStr  )  );							  
							  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s: %d, %dfps, %d, %s, %dx%d"  ),  tag,  pMosaicTran->video.uiTranNo_openAvDev,  (  int  )pMosaicTran->video.compressor.common.usMaxFps_toShareBmp,  (  int  )pMosaicTran->video.compressor.common.ucCompressors,  CQyString(  fourccStr  ),  pMosaicTran->video.vh_compress.bih.biWidth,  pMosaicTran->video.vh_compress.bih.biHeight  );
							  pListCtrl->SetItemText(  index,  i,  tBuf  );
							  i  ++  ;
							  index  ++  ;

							  //
							  if  (  pTask->ucbStarter  )
							  {
								  QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj_mosaic  );
								  if  (  pSharedObj  )  {
									  SHARED_OBJ_USR  *  pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  pSharedObj->iIndex_curUsr  );
									  if  (  pSharedObjUsr  )  {

							  
									  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );			
									  i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
									  tBuf[0]  =  0;
									  //_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s share[%d]"  ),  tag,  iIndex_sharedObj_mosaic  );
									  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );
									  i  ++  ; pListCtrl->SetItemText(  index,  i,  _ltot(  pSharedObjUsr->iTaskId,  tBuf,  10  )  );
									  i  ++  ;	
									  i  ++  ;
									  i  ++  ;	
									  //snprintRoute(  &pTaskInfo->var.curRoute_sendLocalAv,  tBuf,  mycountof(  tBuf  )  );
									  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "index_sharedObj %d"  ),  iIndex_sharedObj_mosaic  );
									  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );
									  index  ++  ;
									  }
								  }
							  }
						  }
					  }


					  //  2014/09/25
					  //if  (  pTask->iIndex_taskInfo  )  
					  {
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );			
						  i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
						  i  ++  ;
						  i  ++  ;  pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );
						  i  ++  ;
						  i  ++  ;
						  i  ++  ;
						  i  ++  ;  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "index_taskInfo %d"  ),  pTask->iIndex_taskInfo  );
						  pListCtrl->SetItemText(  index,  i,  tBuf  );
						  i  ++  ;
						  index  ++  ;
					  }


					  //  2009/09/10
					  
					  //
#if  0
						  TASK_AV_FROM  *  pFrom  =  &pTask->mem0_from;						  						  
						  tmp_displayTaskAvFrom(  pListCtrl,  pMsgElem,  pContent,  pTask,  pFrom,  0,  index  );
#endif

						  //
						  //QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pTask->iIndex_sharedObj  );
						  //if  (  pSharedObj  )  
						  {

							  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );			
							  i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
							  tBuf[0]  =  0;
							  //_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "share objs[%d]"  ),  pTask->iIndex_sharedObj  );								  
							  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );
							  i  ++  ; pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );
							  i  ++  ;	
							  i  ++  ;
							  i  ++  ;	
							  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "index_sharedObj %d"  ),  pTask->iIndex_sharedObj  );
							  //
							  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. %s"  ),  tBuf,  pTc->ucbNotSendData  ?  _T(  "noSending"  )  :  _T(  "canSend"  )  );
							  //
							  //snprintRoute(  &pTaskInfo->var.curRoute_sendLocalAv,  tBuf,  mycountof(  tBuf  )  );
							  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );
							  
							  //
							  index  ++  ;

							  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );			
							  i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
							  tBuf[0]  =  0;
							  //_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "share objs[%d]"  ),  pTask->iIndex_sharedObj  );								  
							  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );
							  i  ++  ; pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );
							  i  ++  ;	
							  i  ++  ;
							  i  ++  ;	
							  snprintRoute(  &pTaskInfo->var.curRoute_sendLocalAv,  tBuf,  mycountof(  tBuf  )  );
							  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );
							  
							  //
							  index  ++  ;



						  }
					  
					  
					  					  //  2015/09/09
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );
					  i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
					  i  ++  ;
					  i  ++  ;  pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );							 
					  i  ++  ;							  
					  i  ++  ;							  
					  i  ++  ;  							  
					  i  ++  ;  
					  //_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "activeMems %d, froms %d, dispatchs %d, trans %d"  ),  (  int  )pTask->usCntLimit_activeMems_from,  (  int  )pTask->usCntLimit_mems_from,  (  int  )pTask->usCntLimit_dispatchs,  (  int  )pTask->usCntLimit_transforms  );							  
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "activeMems %d, froms %d, maxSpeakers %d, dispatchs %d, trans %d"  ),  (  int  )pTc->videoConference.usCntLimit_activeMems_from,  (  int  )pTc->videoConference.usCntLimit_mems_from,  (int)pTc->videoConference.usMaxSpeakers,  (  int  )pTask->usCntLimit_dispatchs,  (  int  )pTask->usCntLimit_transforms  );							  
					  pListCtrl->SetItemText(  index,  i,  tBuf  );
					  index  ++  ;


					  //
					  if  (  pContent->uiType  ==  CONST_imCommType_transferAvInfo
						  &&  pTaskInfo->var.m_bReplyTask  )  
					  {
						  //TASK_AV_FROM  *  pFrom  =  &pTask->mem0_from;
						  AV_TRAN_INFO  *  pTranInfo  =  &pTask->reply_avTranInfo;
						  						   
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );
						   i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
						   tBuf[0]  =  0;
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );
						   i  ++  ; pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );
						   i  ++  ;	
						   i  ++  ;	
						   i  ++  ;

						   tBuf[0]  =  0;
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Reply of %I64u."  ),  pMisCnt->idInfo.ui64Id  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ver %d.%d"  ),  tBuf,  pTranInfo->head.shClientVer  /  100,  pTranInfo->head.shClientVer  %  100  );
						   char	fourccStr[16];
						   //  iFourcc2Str(  pFrom->video.vh_compress_recvd.bih.biCompression,  fourccStr,  mycountof(  fourccStr  )  );
						   safeStrnCpy(  pTranInfo->video.compressor.common.fourccStr,  fourccStr,  mycountof(  fourccStr  )  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( a %d, 0x%x,%d,%d,%d,%d )"  ),  tBuf,  pTranInfo->audio.uiTranNo_openAvDev,  pTranInfo->audio.ah_compress.wfx.wFormatTag,  pTranInfo->audio.ah_compress.wfx.nChannels,  pTranInfo->audio.ah_compress.wfx.nSamplesPerSec,  pTranInfo->audio.ah_compress.wfx.wBitsPerSample,  pTranInfo->audio.ah_compress.wfx.nAvgBytesPerSec  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( v %d, %s, %d * %d, %s )"  ),  tBuf,  pTranInfo->video.uiTranNo_openAvDev,  CString(  fourccStr  ),   pTranInfo->video.vh_compress.bih.biWidth,  pTranInfo->video.vh_compress.bih.biHeight,  (  0  ?  _T(  "flip"  )  :  _T(  ""  )  )  ); 
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

						   i  ++  ;	
						   i  ++  ;

						   getTimelStr(  pMsgElem->task.tStartTime,  timeBuf,  mycountof(  timeBuf  )  );
						   qyDisplayTime(  timeBuf,  displayBuf,  mycountof(  displayBuf  )  );
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  CString(  displayBuf  )  );		

						   index  ++  ;
					  }

					  //
					  for  (  j  =  0;  j  <  pTc->videoConference.usCntLimit_activeMems_from;  j  ++  )  {
						   DLG_TALK_videoConferenceActiveMemFrom  *  pFrom  =  &pTc->videoConference.activeMems_from[j];
						   DLG_TALK_videoConferenceActiveMemFrom * pActiveMem_from  =  &pTc->videoConference.activeMems_from[j];

						   //
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );
						   i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
						   tBuf[0]  =  0;  //  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );
						   i  ++  ; pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );
						   i  ++  ;	
						   i  ++  ;	
						   i  ++  ;

						   tBuf[0]  =  0;
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "active %d:"  ),  j  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %I64u"  ),  tBuf,  pFrom->avStream.idInfo.ui64Id  );
						   //
						   if  (  pActiveMem_from->avStream.obj.resObj.uiObjType  )  {
							   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s (%d %s,%d)"  ),  tBuf,  pFrom->avStream.obj.resObj.uiObjType,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  ),  pFrom->avStream.obj.resObj.uiObjType  ),  pFrom->avStream.obj.resObj.usIndex_obj  );
							   }
						   else  {
							     _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s  "  ),  tBuf  );
						   }
						   //
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ver %d.%d"  ),  tBuf,  pFrom->avStream.obj.tranInfo.head.shClientVer  /  100,  pFrom->avStream.obj.tranInfo.head.shClientVer  %  100  );
						   char	fourccStr[16];
						   //  iFourcc2Str(  pFrom->video.vh_compress_recvd.bih.biCompression,  fourccStr,  mycountof(  fourccStr  )  );
						   safeStrnCpy(  pFrom->avStream.obj.tranInfo.video.compressor.common.fourccStr,  fourccStr,  mycountof(  fourccStr  )  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( a %d, 0x%x,%d,%d,%d,%d )"  ),  tBuf,  pFrom->avStream.obj.tranInfo.audio.uiTranNo_openAvDev,  pFrom->avStream.obj.tranInfo.audio.ah_compress.wfx.wFormatTag,  pFrom->avStream.obj.tranInfo.audio.ah_compress.wfx.nChannels,  pFrom->avStream.obj.tranInfo.audio.ah_compress.wfx.nSamplesPerSec,  pFrom->avStream.obj.tranInfo.audio.ah_compress.wfx.wBitsPerSample,  pFrom->avStream.obj.tranInfo.audio.ah_compress.wfx.nAvgBytesPerSec  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( v %d, %s, %d * %d, %s )"  ),  tBuf,  pFrom->avStream.obj.tranInfo.video.uiTranNo_openAvDev,  CString(  fourccStr  ),   pFrom->avStream.obj.tranInfo.video.vh_compress.bih.biWidth,  pFrom->avStream.obj.tranInfo.video.vh_compress.bih.biHeight,  (  0  ?  _T(  "flip"  )  :  _T(  ""  )  )  ); 
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

						   i  ++  ;	

						   i  ++  ;	

						   index  ++  ;
					  }


					  


					  //  2014/12/04
					  for  (  j  =  0;  j  <  pTask->usCntLimit_dispatchs;  j  ++  )  {
						  QIS_DISPATCH  *  pDispatch  =  &pTask->pDispatchs[j];
						  
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );
						   i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );
						   tBuf[0]  =  0;
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );
						   i  ++  ; pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );
						   i  ++  ;	
						   i  ++  ;	
						   i  ++  ;

						   tBuf[0]  =  0;
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "dispatch %d:"  ),  j  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s a %d,%d, v %d,%d"  ),  tBuf,  getQ2Nodes_toGetMsg(  &pDispatch->audio.q2  ),  getQ2Nodes_toPostMsg(  &pDispatch->audio.q2  ),  getQ2Nodes_toGetMsg(  &pDispatch->video.q2  ),  getQ2Nodes_toPostMsg(  &pDispatch->video.q2  )  );
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

						   i  ++  ;	

						   i  ++  ;	

						   index  ++  ;

					  }

					  //

					  //  2015/01/13
					  if  (  pTask->ucbVideoConference  
						  &&  !pTask->ucbVideoConferenceStarter  )  
					  {
						  QY_TRANSFORM  *  pTransform  =  NULL;
#if  0
						  if  (  pTask->confMosaicTrans.confMosaic_video.transform.bMosaicVideo  )  {
							  pTransform  =  &pTask->confMosaicTrans.confMosaic_video.transform;
							  tmp_displayTrans(  pListCtrl,  pMsgElem,  pContent,  pTask,  pTransform,  0,  index,  _T(  " mosaicV"  )  );
						  }
						  if  (  pTask->confMosaicTrans.confMosaic_resource.transform.bMosaicResource  )  {
							  pTransform  =  &pTask->confMosaicTrans.confMosaic_resource.transform;
							  tmp_displayTrans(  pListCtrl,  pMsgElem,  pContent,  pTask,  pTransform,  1,  index,  _T(  " mosaicR"  )  );
						  }
#endif
					  }


					  //
					  for  (  j  =  0;  j  <  pTask->usCntLimit_transforms;  j  ++  )  {
						   QY_TRANSFORM  *  pTransform  =  &pTask->pTransforms[j];

						   tmp_displayTrans(  pListCtrl,  pMsgElem,  pContent,  pTask,  pTransform,  j,  index,  _T(  ""  )  );


#if  0
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );
						   i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );
						   i  ++  ; pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );
						   i  ++  ;	
						   i  ++  ;
						   i  ++  ;	

						   tBuf[0]  =  0;
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "trans %d:"  ),  j  );
						   if  (  pTransform->audio.bRunning  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( a %d,%d, from %d )"  ),  tBuf,  getQ2Nodes_toGetMsg(  &pTransform->audio.q2  ),  getQ2Nodes_toPostMsg(  &pTransform->audio.q2  ),  pTransform->audio.index_pMems_from  );
						   if  (  pTransform->video.bRunning  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( v %d,%d, from %d )"  ),  tBuf,  getQ2Nodes_toGetMsg(  &pTransform->video.q2  ),  getQ2Nodes_toPostMsg(  &pTransform->video.q2  ),  pTransform->video.index_pMems_from  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s.  a: nStep %d, elp %dms"  ),  tBuf,  pTransform->audio.debugStep.nStep_debug,  GetTickCount(  )  -  pTransform->audio.debugStep.dwTickCnt_step_debug  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s,  v_pre: nStep %d, elp %dms, iErr %d"  ),  tBuf,  pTransform->v_preTransThread.debugStep.nStep_debug,  GetTickCount(  )  -  pTransform->v_preTransThread.debugStep.dwTickCnt_step_debug,  pTransform->v_preTransThread.debugStep.iErr_thread  );	//  2012/09/07
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s,  v: decMod %s, nStep %d, elp %dms"  ),  tBuf,  qyGetDesByType1(  CONST_moduleTypeTable_en,  pTransform->video.uiModuleType_toDec  ),  pTransform->video.debugStep.nStep_debug,  GetTickCount(  )  -  pTransform->video.debugStep.dwTickCnt_step_debug  );
#if  0
						   if  (  pTransform->video.debugStep.fg.FillBuffer.nStep_debug  )  {
							   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, nStep_fg %d, elapse %dms"  ),  tBuf,  pTransform->video.debugStep.fg.FillBuffer.nStep_debug,  GetTickCount(  )  -  pTransform->video.debugStep.fg.FillBuffer.dwTickCnt_step_debug  );
						   }
#endif
						   
						   //
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s,  errs: notAccept %d, Input %d, output %d, index %d"  ),  tBuf,  pTransform->video.debugStep.uiCnt_DMO_E_NOTACCEPTING,  pTransform->video.debugStep.nErrs_ProcessInput,  pTransform->video.debugStep.nErrs_ProcessOutput,  pTransform->video.debugStep.nErrs_pOutputBuffers_index  ); 
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

						   i  ++  ;	

						   i  ++  ;	

						   index  ++  ;

						   //  2015/01/15						   		
						   if  (  pTransform->video.uiModuleType_toDec  ==  CONST_moduleType_mediaSdk_dec  )  {
							   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );
							   i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
							   i  ++  ;	
							   i  ++  ; 
							   i  ++  ;	
							   i  ++  ;
							   i  ++  ;	

							   tBuf[0]  =  0;
							   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "more of trans %d:"  ),  j  );
							   //  2015/01/11
							   //if  (  pTransform->video.debugStep.dec.nStep_debug  )  
							   {
								   DEBUG_step_dec  *  pStep_dec  =  &pTransform->video.debugStep.dec;
								   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, {nStep_dec %d, elp %dms, excpt %d, sts_run %d"  ),  tBuf,  pStep_dec->nStep_debug,  GetTickCount(  )  -  pStep_dec->dwTickCnt_step_debug,  pStep_dec->bException,  pStep_dec->sts_run  );
								   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, call_Init %d, sts_Init %d, call_RunDec %d, syncOSurf(sts %d, bE %d)"  ),  tBuf,  pStep_dec->bCalled_pipeline_Init,  pStep_dec->sts_pipeline_Init,  pStep_dec->bCalled_RunDecoding,  pStep_dec->sts_SyncOutputSurface,  pStep_dec->bMFX_ERR_UNKNOWN_SyncOutputSurface  );
								   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s}"  ),  tBuf  );
							   }
							   //
							   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

							   i  ++  ;	

							   i  ++  ;	

							   index  ++  ;
						   }
#endif


					  }

					  //  2014/12/01
#if  0
					  if  (  pTask->confMosaicTrans.bExists_confMosaic  )  {
						  TASK_AV_FROM  *  pFrom  =  &pTask->confMosaicTrans.confMosaic_video.taskAvFrom;

						  tmp_displayTaskAvFrom(  pListCtrl,  pMsgElem,  pContent,  pTask,  pFrom,  0,  index  );
						  pFrom  =  &pTask->confMosaicTrans.confMosaic_resource.taskAvFrom;
						  tmp_displayTaskAvFrom(  pListCtrl,  pMsgElem,  pContent,  pTask,  pFrom,  1,  index  );
						  
					  }
#endif

					  //
					  if  (  pTc->videoConference.pMems_from  )  {
						  //
						  for  (  j  =  0;  j  <  pTc->videoConference.usCntLimit_mems_from;  j  ++  )  {  
						   TASK_AV_FROM  *  pFrom  =  &pTc->videoConference.pMems_from[j];

#if  0
						   if  (  !pFrom->idInfo.ui64Id  )  continue;

						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );
						   i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );
						   i  ++  ; pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );
						   i  ++  ;	
						   i  ++  ;	
						   i  ++  ;

						   tBuf[0]  =  0;
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "from %d: %I64u"  ),  j,  pFrom->idInfo.ui64Id  );
						   //  2014/09/04
						#if  0
						   if  (  pFrom->video.dynBmp.usIndex_obj  )  {
							   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ind_obj %d"  ),  tBuf,  (  int  )pFrom->video.dynBmp.usIndex_obj  );
						   }
						#endif
						   //
						   char	fourccStr[16];
						   //  iFourcc2Str(  pFrom->video.vh_compress_recvd.bih.biCompression,  fourccStr,  mycountof(  fourccStr  )  );
						   safeStrnCpy(  pFrom->video.tv_recvd.compressor.common.fourccStr,  fourccStr,  mycountof(  fourccStr  )  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( a %d, %d, 0x%x,%d,%d,%d,%d )"  ),  tBuf,  pFrom->audio.ta_recvd.uiTranNo_openAvDev,  (  int  )pFrom->audio.ta_recvd.compressor.common.ucCompressors,  pFrom->audio.ta_recvd.ah_compress.wfx.wFormatTag,  pFrom->audio.ta_recvd.ah_compress.wfx.nChannels,  pFrom->audio.ta_recvd.ah_compress.wfx.nSamplesPerSec,  pFrom->audio.ta_recvd.ah_compress.wfx.wBitsPerSample,  pFrom->audio.ta_recvd.ah_compress.wfx.nAvgBytesPerSec  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( v %d, %d, %s, %dX%d, %s. stream %d,%d,%d )"  ),  tBuf,  pFrom->video.tv_recvd.uiTranNo_openAvDev,  (  int  )pFrom->video.tv_recvd.compressor.common.ucCompressors,  CString(  fourccStr  ),   pFrom->video.tv_recvd.vh_compress.bih.biWidth,  pFrom->video.tv_recvd.vh_compress.bih.biHeight,  (  pFrom->video.tv_recvd.compressor.common.ucbOutputFlippedImg  ?  _T(  "flip"  )  :  _T(  ""  )  ),  
							   (  int  )pFrom->video.tv_recvd.vh_stream.usCnt,  (  int  )pFrom->video.tv_recvd.vh_stream.mems[0].usLen,  (  int  )pFrom->video.tv_recvd.vh_stream.mems[1].usLen    ); 
						   //  2011/12/24
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s.  audio player:"  ),  tBuf  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %dms, %dms, %dms"  ),  tBuf,  (  int  )pFrom->audio.ta_recvd.compressor.playCfg.usMinTimeInMsOfAudioDataPlaying,  (  int  )pFrom->audio.ta_recvd.compressor.playCfg.usAudioDataAddedToPlayEveryTime,  (  int  )pFrom->audio.ta_recvd.compressor.playCfg.usNotifyIntervalInMs_needMoreAudioData  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %dms, %dms, %dms"  ),  tBuf,  (  int  )pFrom->audio.ta_recvd.compressor.playCfg.usMinTimeInMsToPlay,  (  int  )pFrom->audio.ta_recvd.compressor.playCfg.usMaxTimeInMsToPlay,  (  int  )pFrom->audio.ta_recvd.compressor.playCfg.usMaxTimeInMsToBeRemoved  );
						   //
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

						   i  ++  ;	

						   getTimelStr(  pMsgElem->task.tStartTime,  timeBuf,  mycountof(  timeBuf  )  );
						   qyDisplayTime(  timeBuf,  displayBuf,  mycountof(  displayBuf  )  );
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  CString(  displayBuf  )  );		

						   index  ++  ;
#endif
						   tmp_displayTaskAvFrom(  pListCtrl,  pMsgElem,  pContent,  pTask,  pFrom,  j,  index  );
					  }
					  }

					  //  2009/09/11
					  {
						  //QY_SHARED_OBJ  *  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pTask->iIndex_sharedObj  );
						  //if  (  pSharedObj  )  
						  {
					  
							  if  (  !pTaskInfo->var.curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id
								  &&  pTaskInfo->var.curRoute_sendLocalAv.route.idInfo_to.ui64Id  )  {
								  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );
								  i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
								  tBuf[0]  =  0;
								  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );
								  i  ++  ; pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );
								  i  ++  ;	
								  i  ++  ;	
								  i  ++  ;

								  time_t	t;	time(  &t  );
								  tBuf[0]  =  0;
								  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Last resp:"  )  );
								  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %I64u, -%ds"  ),  tBuf,  pTaskInfo->var.curRoute_sendLocalAv.route.idInfo_to.ui64Id,  (  int  )(  t  -  pTaskInfo->var.curRoute_sendLocalAv.routeInfo.tRecvTime_lastResp  )  );
								  for  (  j  =  0;  j  <  mycountof(  pTaskInfo->var.curRoute_sendLocalAv.route.mems_to  );  j  ++  )  {
									   if  (  !pTaskInfo->var.curRoute_sendLocalAv.route.mems_to[j].idInfo.ui64Id  )  continue;
									   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %I64u, -%ds"  ),  tBuf,  pTaskInfo->var.curRoute_sendLocalAv.route.mems_to[j].idInfo.ui64Id,  (  int  )(  t  -  pTaskInfo->var.curRoute_sendLocalAv.routeInfo.mems[j].tRecvTime_lastResp  )  );  
								  }

								  i  ++  ;  pListCtrl->SetItemText(  index,  i,  tBuf  );

								  index  ++  ;
							  }

						  }
					  }

					  }
					  break;
					  
				case  CONST_imCommType_transferGpsInfo:  {
					  QY_SHARED_OBJ	*	pSharedObj	=	NULL;			

#if  0
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );
					  i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	

					  tBuf[0]  =  0;				
					  if  (  pMsgElem->task.uiTaskType  )  {
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s"  ),  tBuf,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsgElem->task.uiTaskType  )  );
						  }
					  else  {
						    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );  													
					  }
					  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

					  i  ++  ; pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pMsgElem->task.idInfo_taskSender.ui64Id  );
					  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pMsgElem->task.idInfo_taskReceiver.ui64Id  );
					  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );
			
					  tBuf[0]  =  0;							
					  if  (  pContent->transferGpsInfo.myTask.iIndex_sharedObj  )  {									
						  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pContent->transferGpsInfo.myTask.iIndex_sharedObj  );									 
					  }	
					  if  (  pSharedObj  )  {
						  snprintRoute(  &pTc->curRoute_sendLocalAv,  tBuf,  mycountof(  tBuf  )  );						
					  }									 
									 
					  //
					  i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

					  i  ++  ;	

					  getTimelStr(  pMsgElem->task.tStartTime,  timeBuf,  mycountof(  timeBuf  )  );
					  qyDisplayTime(  timeBuf,  displayBuf,  mycountof(  displayBuf  )  );
					  i  ++  ;	pListCtrl->SetItemText(  index,  i,  CString(  displayBuf  )  );		

					  index  ++  ;

					  if  (  pSharedObj  )  {
						  if  (  !pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id
							  &&  pSharedObj->curRoute_sendLocalAv.route.idInfo_to.ui64Id  )  {
							  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );
							  i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	
							  i  ++  ;	pListCtrl->SetItemText(  index,  i,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );
							  i  ++  ; pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );
							  i  ++  ;	
							  i  ++  ;	

							  time_t	t;	time(  &t  );
							  tBuf[0]  =  0;
							  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Last resp:"  )  );
							  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %I64u, -%ds"  ),  tBuf,  pSharedObj->curRoute_sendLocalAv.route.idInfo_to.ui64Id,  (  int  )(  t  -  pSharedObj->curRoute_sendLocalAv.routeInfo.tRecvTime_lastResp  )  );
							  for  (  j  =  0;  j  <  mycountof(  pSharedObj->curRoute_sendLocalAv.route.mems_to  );  j  ++  )  {
								   if  (  !pSharedObj->curRoute_sendLocalAv.route.mems_to[j].idInfo.ui64Id  )  continue;
								   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %I64u, -%ds"  ),  tBuf,  pSharedObj->curRoute_sendLocalAv.route.mems_to[j].idInfo.ui64Id,  (  int  )(  t  -  pSharedObj->curRoute_sendLocalAv.routeInfo.mems[j].tRecvTime_lastResp  )  );  
							  }

							  i  ++  ;  pListCtrl->SetItemText(  index,  i,  tBuf  );

							  index  ++  ;
						  }
					  }

#endif
					  }
					  break;

				default:
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  index  );
						   i  =  0;	pListCtrl->InsertItem(  index,  tBuf  );	

						   tBuf[0]  =  0;				
						   if  (  pMsgElem->task.uiTaskType  )  {
							   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s"  ),  tBuf,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  ),  pMsgElem->task.uiTaskType  )  );
							  }
						   else  {
							    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );  							
						   }
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

						   i  ++  ; pListCtrl->SetItemText(  index,  i,  _ltot(  pMsgElem->task.iTaskId,  tBuf,  10  )  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pMsgElem->task.idInfo_taskSender.ui64Id  );
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );
						   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pMsgElem->task.idInfo_taskReceiver.ui64Id  );
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

						   tBuf[0]  =  0;
						   if  (  pContent->uiType  ==  CONST_imCommType_transferFileReq  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s fileLen %I64u"  ),  tBuf,  pContent->transferFileReq.ui64FileLen  );
						   //else  if  (  pContent->uiType  ==  CONST_imCommType_transferFileReplyReq  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s fileLen %I64u"  ),  tBuf,  pContent->transferFileReplyReq.ui64FileLen  );
						   else  {
							     ;								 
						   }
						   //
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  tBuf  );

						   i  ++  ;	

						   getTimelStr(  pMsgElem->task.tStartTime,  timeBuf,  mycountof(  timeBuf  )  );
						   qyDisplayTime(  timeBuf,  displayBuf,  mycountof(  displayBuf  )  );
						   i  ++  ;	pListCtrl->SetItemText(  index,  i,  CString(  displayBuf  )  );		

						   index  ++  ;

						   break;
		}

	}

	(  *piCnt  )  =  index  ;

	return  0;
}

//


  //  BOOL  bDisplayMcViewContent_realTimeImTasks(  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
BOOL  bDisplayMcViewContent_realTimeImTasks(  CListCtrl  * pListCtrl,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
{
	 BOOL								bRet					=			FALSE;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 QY_SERVICEGUI_INFO				*	pSgi					=			getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	 if  (  !pSgi  )  return  -1;
	 MC_VAR_isCli						*	pProcInfo				=			(  MC_VAR_isCli  *  )pSgi->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 //  CListCtrl						&	ListCtrl				=			pMcView->GetListCtrl();
	 if  (  !pListCtrl  )  return  FALSE;
	 CListCtrl						&	ListCtrl				=			*pListCtrl;

	 //  int								i;
	 //  QY_OBJ_DB						*	pObj;
	 //  char								buf[256];
	 int								cnt						=			0;


	 myListCtrl_delAllColumns(  pListCtrl->m_hWnd  );
	 if  (  !myListCtrl_bAddColumns(  pListCtrl->m_hWnd,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_realTimeImTaskListColumns  )  )  )  goto  errLabel;

	 ListCtrl.DeleteAllItems(  );

	 pProcInfo->processQ_media.qTraverse(  tmpHandler_displayRealTimeTasks,  &ListCtrl,  &cnt  );
	 //pProcInfo->processQ_robot.qTraverse(  (  PF_commonHandler  )tmpHandler_displayRealTimeTasks,  &ListCtrl,  &cnt  );


	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}



//
__declspec(  dllexport  )  BOOL  bViewRealTimeImTaskList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL						bRet			=	FALSE;
	QY_MC					*	pQyMc			=	QY_GET_GBUF(  );		
	QY_SERVICEGUI_INFO		*	pSgi			=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSgi  )  return  -1;
	MC_VAR_isCli				*	pProcInfo		=	(  MC_VAR_isCli  *  )pSgi->pVar;
	if  (  !pProcInfo  )  return  -1;
	QY_MC_SEL					sel;

	traceLogA(  "bViewRealTimeImTaskList enters."  );

	//
	viewStatusCli(  CONST_qyLvType_realTimeImTaskList,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyRealTimeTaskList  ),  CONST_resId_realTimeImTaskListColumns,  (  PF_commonHandler  )bDisplayMcViewContent_realTimeImTasks,  NULL  );    

	traceLogA(  "bViewRealTimeImTaskList leaves."  );

	return  bRet;
}


   BOOL  bDisplayMcViewContent_taskInfos(  CListCtrl  * pListCtrl,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
 {
	 BOOL								bRet					=			FALSE;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 QY_SERVICEGUI_INFO				*	pSgi					=			getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	 if  (  !pSgi  )  return  -1;
	 MC_VAR_isCli						*	pProcInfo				=			(  MC_VAR_isCli  *  )pSgi->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 if  (  !pListCtrl  )  return  FALSE;
	 //  CListCtrl						*	pListCtrl				=			&pMcView->GetListCtrl();
	 int								i,  j;
	 TCHAR								tBuf[256];
	 int								cnt						=			0;
	 int								index;
	 MIS_CNT						*	pMisCnt					=			getMisCntByName(  pProcInfo,  _T(  ""  )  );

	 myListCtrl_delAllColumns(  pListCtrl->m_hWnd  );
	 if  (  !myListCtrl_bAddColumns(  pListCtrl->m_hWnd,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_taskInfoListColumns  )  )  )  goto  errLabel;

	 pListCtrl->DeleteAllItems(  );

	 for  (  i  =  0;  i  <  pProcInfo->cfg.usMaxCnt_taskInfos;  i  ++  )  {
		 QMC_TASK_INFO				*	pTaskInfo	=	(  QMC_TASK_INFO  *  )pProcInfo->getQmcTaskInfoByIndex(  i  );
		 if  (  !pTaskInfo  )  continue;
		 
		 //
		 if  (  !pTaskInfo->bUsed  )  continue;
		  


			   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  i  );
			   index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	

			   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pTaskInfo->var.iTaskId  );
			   index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

			   tBuf[0]  =  0;				   
			   index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

			   tBuf[0]  =  0;
			   index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

			   tBuf[0]  =  0;
			   index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

			   tBuf[0]  =  0;
			   index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );


			   cnt  ++  ;
		  

	 }
	 bRet  =  TRUE;

errLabel:
	 return  bRet;
 }


  //  2014/09/25
  __declspec(  dllexport  )    BOOL  bViewTaskInfoList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL						bRet			=	FALSE;
	QY_MC					*	pQyMc			=	QY_GET_GBUF(  );		
	QY_SERVICEGUI_INFO		*	pSgi			=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSgi  )  return  -1;
	MC_VAR_isCli				*	pProcInfo		=	(  MC_VAR_isCli  *  )pSgi->pVar;
	if  (  !pProcInfo  )  return  -1;
	QY_MC_SEL					sel;

	traceLogA(  "bViewTaskInfoList enters."  );

	//
	viewStatusCli(  CONST_qyLvType_taskInfoList,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_taskInfoList  ),  CONST_resId_taskInfoListColumns,  (  PF_commonHandler  )bDisplayMcViewContent_taskInfos,  NULL  );    

	traceLogA(  "bViewTaskInfoList leaves."  );

	return  bRet;
}


     //  BOOL  bDisplayMcViewContent_sharingObjects(  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
 BOOL  bDisplayMcViewContent_sharingObjects(  CListCtrl  * pListCtrl,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
 {
	 BOOL								bRet					=			FALSE;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 QY_SERVICEGUI_INFO				*	pSgi					=			getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	 if  (  !pSgi  )  return  -1;
	 MC_VAR_isCli						*	pProcInfo				=			(  MC_VAR_isCli  *  )pSgi->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 if  (  !pListCtrl  )  return  FALSE;
	 //  CListCtrl						*	pListCtrl				=			&pMcView->GetListCtrl();
	 int								i,  j;
	 TCHAR								tBuf[256];
	 int								cnt						=			0;
	 int								index;
	 MIS_CNT						*	pMisCnt					=			getMisCntByName(  pProcInfo,  _T(  ""  )  );

	 myListCtrl_delAllColumns(  pListCtrl->m_hWnd  );
	 if  (  !myListCtrl_bAddColumns(  pListCtrl->m_hWnd,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_sharingObjectListColumns  )  )  )  goto  errLabel;

	 pListCtrl->DeleteAllItems(  );

	 for  (  i  =  0;  i  <  pProcInfo->cfg.usMaxCnt_pSharedObjs;  i  ++  )  {
		  QY_SHARED_OBJ				*	pSharedObj	=	getSharedObjByIndex(  pProcInfo,  i  );	//  &pProcInfo->pSharedObjs[i];

		  if  (  !i  )  {
			  if  (  !pProcInfo->av.localAv.videoCaptureProcInfo.bCapDevConnected  &&  !pProcInfo->av.localAv.recordSoundProcInfo.thread.hThread  )  continue;
			  }
		  else  {
			    if  (  !pSharedObj->bUsed  )  continue;
		  }

		  //
		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  i  );			
		  index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	
		  		     
		  index  ++  ;
		  index  ++  ;

		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "tn:%d"  ),  pSharedObj->uiTranNo  );		  
		  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		  //
		  cnt  ++  ;


		  //
		  for  (  j  =  0;  j  <  mycountof(  pSharedObj->usrs  );  j  ++  )  {
			   SHARED_OBJ_USR	*	pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  j  );

			   if  (  j  )  {
				   if  (  !IsWindow(  pSharedObjUsr->hWnd_starter  )  )  continue;
			   }

			   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d, %d"  ),  i,  j  );
			   index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	

			   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pSharedObjUsr->iTaskId  );
			   index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

			   tBuf[0]  =  0;				   
			   if  (  j  ==  pSharedObj->iIndex_curUsr  )  {
				   //snprintRoute(  &pSharedObj->curRoute_sendLocalAv,  tBuf,  mycountof(  tBuf  )  );
#if  0
				   if  (  memcmp(  &pSharedObj->route_sendLocalAv,  &pSharedObj->curRoute_sendLocalAv,  sizeof(  pSharedObj->route_sendLocalAv  )  )  )  {
					   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s |cur "  ),  tBuf  );
					   snprintRoute(  &pSharedObj->curRoute_sendLocalAv,  tBuf  +  lstrlen(  tBuf  ),  mycountof(  tBuf  )  -  lstrlen(  tBuf  )  );				   
				   }
#endif
				   }				   
			   else  {
				     //_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Dst: %I64u"  ),  pSharedObjUsr->idInfo_to.ui64Id  );				   
			   }
			   //
			   if  (  pSharedObj->bSlave  )  {
				   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. slave -> %d"  ),  tBuf,  pSharedObj->slave.masterKey.iIndex_sharedObj  );
			   }
			   //  2015/05/23
			   if  (  pSharedObjUsr->bIn3DConf  )  {
				   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. in3DConf"  ),  tBuf  );
			   }
			   //
			   index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

			   tBuf[0]  =  0;
			   //  if  (  j  ==  pSharedObj->iIndex_curUsr  )  
			   {
				   CAP_procInfo_audioU	*	pCapAudio  =  getCapAudioBySth(  pProcInfo,  pSharedObj->iIndex_capAudio,  0  );
				   if  (  pCapAudio  )  {
					   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s a: %d."  ),  tBuf,  pSharedObjUsr->uiTranNo_openAvDev_a  );
				   }
				   CAP_procInfo_bmpU	*	pCapBmp  =  getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
				   if  (  pCapBmp  )  {
					   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s v: %d, %dX%d->%dX%d, fps: max %d, min %d, cur %d. input %d, toSend %d, sending %.2f."  ),  tBuf,  
						   pSharedObjUsr->uiTranNo_openAvDev_v,  pCapBmp->common.vh_org.bih.biWidth,  pCapBmp->common.vh_org.bih.biHeight,  pCapBmp->common.compressVideo.vh_decompress.bih.biWidth,  pCapBmp->common.compressVideo.vh_decompress.bih.biHeight,
						   pCapBmp->common.compressVideo.compressor.common.usMaxFps_toShareBmp,  pCapBmp->common.compressVideo.compressor.common.usMinFps_toShareBmp,  pCapBmp->common.compressVideo.usFrames_perSecond_expected,  (  int  )pCapBmp->common.compressVideo.input_BufferCB.videoInputInfo.usFps,  (  int  )pCapBmp->common.compressVideo.usFps_toSend,  pCapBmp->common.compressVideo.fFps_sending  );
					   if  (  pCapBmp->common.compressVideo.compressor.common.ucSeconds_perFrame  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s spf: %ds."  ),  tBuf,  (  int  )pCapBmp->common.compressVideo.compressor.common.ucSeconds_perFrame  );
				   }
			   }
			   index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

			   tBuf[0]  =  0;
			   if  (  j  ==  pSharedObj->iIndex_curUsr  )  
			   {
				   //if  (  !pSharedObjUsr->ucbNotSendData  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "sending"  )  );
			   }
			   //  2016/03/28
			   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  tBuf,  pSharedObjUsr->tDbgHint  );			   
			   //  2014/12/02
			   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, hWnd %I64u"  ),  tBuf,  (  __int64  )pSharedObjUsr->hWnd_starter  );
			   //  2010/12/28			   				 
			   CAP_procInfo_bmpU	*	pCapBmp  =  getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
			   if  (  pCapBmp  )  {
				   char  timeBuf[32];
				   getTimelStr(  pCapBmp->common.compressVideo.debugInfo.tStart,  timeBuf,  mycountof(  timeBuf  )  );
				   getTimelStr(  pCapBmp->common.compressVideo.input_BufferCB.videoInputInfo.tStartTran,  timeBuf,  mycountof(  timeBuf  )  );
				   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, tLast_vCap %s"  ),  tBuf,  CString(  timeBuf  )  );
				   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, nStep %d"  ),  tBuf,  pCapBmp->common.compressVideo.debugInfo.nStep  );
				   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, nStep_progress %d"  ),  tBuf,  pProcInfo->debugInfo.nStep_progress  );
				   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, tStart %s"  ),  tBuf,  CString(  timeBuf  )  );
			   }
			   //
			   index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

			   tBuf[0]  =  0;
#if  0
			   QM_SHM_CMD	*	pShmCmd  =  getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  pSharedObj->iIndex_shmCmd  );
			   if  (  pShmCmd  )  {
				   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  tBuf,  pShmCmd->path  );
			   }
#endif
			   index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );


			   cnt  ++  ;
		  }

	 }
	 bRet  =  TRUE;

errLabel:
	 return  bRet;
 }

 //
 __declspec(  dllexport  )   BOOL  	bViewSharingObjectList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL						bRet			=	FALSE;
	QY_MC					*	pQyMc			=	QY_GET_GBUF(  );		
	QY_SERVICEGUI_INFO		*	pSgi			=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSgi  )  return  -1;
	MC_VAR_isCli				*	pProcInfo		=	(  MC_VAR_isCli  *  )pSgi->pVar;
	if  (  !pProcInfo  )  return  -1;
	QY_MC_SEL					sel;

	traceLogA(  "bViewSharingObjectList enters."  );

	//
	viewStatusCli(  CONST_qyLvType_sharingObjectList,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_sharingObjectList  ),  CONST_resId_sharingObjectListColumns,  (  PF_commonHandler  )bDisplayMcViewContent_sharingObjects,  NULL  );     

	traceLogA(  "bViewSharingObjectList leaves."  );

	return  bRet;

}

    //  BOOL  bDisplayMcViewContent_players(  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
  BOOL  bDisplayMcViewContent_players(  CListCtrl  * pListCtrl,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
{
	 BOOL								bRet					=			FALSE;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;
	
	 FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );

	 //  CListCtrl						*	pListCtrl				=			&pMcView->GetListCtrl();
	 if  (  !pListCtrl  )  return  FALSE;
	 int								i;
	 //  QY_OBJ_DB						*	pObj;
	 TCHAR								tBuf[256];
	 int								cnt						=			0;
	 int								index;
	 MIS_CNT						*	pMisCnt					=			getMisCntByName(  pProcInfo,  _T(  ""  )  );
	 int								nWaitingInMs			=			0;

	 myListCtrl_delAllColumns(  pListCtrl->m_hWnd  );
	 if  (  !myListCtrl_bAddColumns(  pListCtrl->m_hWnd,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_playerListColumns  )  )  )  goto  errLabel;

	 pListCtrl->DeleteAllItems(  );


	 //
	 DWORD	dwTickCnt_now  =  GetTickCount(  );

	 //
	 for  (  i  =  0;  i  <  pProcInfo->av.usCnt_players;  i  ++  )  {
		  QY_PLAYER				*	pPlayer	=	&pProcInfo->av.pPlayers[i];

		  if  (  !pPlayer->idInfo_recorder.ui64Id  &&  !pPlayer->audio.uiTranNo  &&  !pPlayer->video.uiTranNo  )  continue;
		  if  (  !pPlayer->audio.bRunning  &&  !pPlayer->video.bRunning  )  continue;

		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  i  );
		 index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	
		
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pPlayer->iTaskId  );
		 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pPlayer->idInfo_recorder.ui64Id  );
		 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		 pFuncs->pf_getTalkerDesc(  pPlayer->idInfo_recorder,  tBuf,  mycountof(  tBuf  ),  NULL,  0  );
		 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d,%d"  ),  pPlayer->audio.uiTranNo,  pPlayer->video.uiTranNo  );
		 index  ++  ;  pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		 tBuf[0]  =  0;
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( %d,%d,%d )"  ),  tBuf,  (  int  )pPlayer->audio.ah.wfx.nChannels,  pPlayer->audio.ah.wfx.nSamplesPerSec,  (  int  )pPlayer->audio.ah.wfx.wBitsPerSample  );
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( %dX%d,%d, %dfps )"  ),  tBuf,  pPlayer->video.vh.bih.biWidth,  pPlayer->video.vh.bih.biHeight,  pPlayer->video.vh.bih.biSizeImage,  (  int  )pPlayer->video.usFps  );
		 index  ++  ;  pListCtrl->SetItemText(  cnt,  index,  tBuf  );


		 //
		 tBuf[0]  =  0;
		 if  (  pPlayer->audio.bRunning  )  {
			 nWaitingInMs  =  MACRO_getnWaitingInMs_audio_syncRecv(  pPlayer->audio,  dwTickCnt_now  );
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "audio playing: "  )  );
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %d,%d"  ),  tBuf,  getQ2Nodes_toGetMsg(  &pPlayer->audio.q2  ),  getQ2Nodes_toPostMsg(  &pPlayer->audio.q2  )  );  
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %dms"  ),  tBuf,  pPlayer->audio.m_var.uiSampleTimeInMs  );
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %dms waiting."  ),  tBuf,  nWaitingInMs  );		 
		 }
		 if  (  pPlayer->video.bRunning  )  {
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, video playing: "  ),  tBuf  );
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %d,%d"  ),  tBuf,  getQ2Nodes_toGetMsg(  &pPlayer->video.q2  ),  getQ2Nodes_toPostMsg(  &pPlayer->video.q2  )  );		 
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %dms"  ),  tBuf,  pPlayer->video.m_var.uiSampleTimeInMs  );	 
		 }
		 if  (  pPlayer->audio.bRunning  )  {
			 #if  0
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s | minPlaying %dms, addedEveryTime %dms, notify %dms"  ),  tBuf,  (  int  )pPlayer->audio.playCfg.usMinTimeInMsOfAudioDataPlaying,  (  int  )pPlayer->audio.playCfg.usAudioDataAddedToPlayEveryTime,  (  int  )pPlayer->audio.playCfg.usNotifyIntervalInMs_needMoreAudioData  );
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, minToPlay %dms, maxToPlay %dms, toBeRemoved %dms"  ),  tBuf,  (  int  )pPlayer->audio.playCfg.usMinTimeInMsToPlay,  (  int  )pPlayer->audio.playCfg.usMaxTimeInMsToPlay,  (  int  )pPlayer->audio.playCfg.usMaxTimeInMsToBeRemoved  );
			 #endif
			 //
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s | %d, %d, %d"  ),  tBuf,  (  int  )pPlayer->audio.playCfg.usMinTimeInMsOfAudioDataPlaying,  (  int  )pPlayer->audio.playCfg.usAudioDataAddedToPlayEveryTime,  (  int  )pPlayer->audio.playCfg.usNotifyIntervalInMs_needMoreAudioData  );				
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %d, %d, %d"  ),  tBuf,  (  int  )pPlayer->audio.playCfg.usMinTimeInMsToPlay,  (  int  )pPlayer->audio.playCfg.usMaxTimeInMsToPlay,  (  int  )pPlayer->audio.playCfg.usMaxTimeInMsToBeRemoved  );
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s | %s"  ),  tBuf,  pPlayer->audio.playbackDevDesc  );
		 }
		 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );
		 
		 cnt  ++  ;

	 }

	 PLAY_AUDIO_procInfo  *  p  =  &pProcInfo->av.localAv.player.audio;
	 QY_PLAYER				*	pPlayer  =  &pProcInfo->av.localAv.player;

	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
	 index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	
		
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
	 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
	 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

	 lstrcpyn(  tBuf,  _T(  "Local player"  ),  mycountof(  tBuf  )  );
	 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  p->uiTranNo  );
	 index  ++  ;  pListCtrl->SetItemText(  cnt,  index,  tBuf  );

	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d,%d,%d"  ),  (  int  )p->ah.wfx.nChannels,  p->ah.wfx.nSamplesPerSec,  (  int  )p->ah.wfx.wBitsPerSample  );
	 index  ++  ;  pListCtrl->SetItemText(  cnt,  index,  tBuf  );

	 tBuf[0]  =  0;
	 if  (  p->bRunning  )  {
		 nWaitingInMs  =  MACRO_getnWaitingInMs_audio_syncRecv(  pPlayer->audio,  dwTickCnt_now  );
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "audio playing: "  )  );
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %d,%d"  ),  tBuf,  getQ2Nodes_toGetMsg(  &pPlayer->audio.q2  ),  getQ2Nodes_toPostMsg(  &pPlayer->audio.q2  )  );  
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %dms"  ),  tBuf,  pPlayer->audio.m_var.uiSampleTimeInMs  );
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %dms waiting."  ),  tBuf,  nWaitingInMs  );		 
	 }
#if  0
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, video: %d,%d"  ),  tBuf,  getQ2Nodes_toGetMsg(  &pQyMc->gui.guiQ2  ),  getQ2Nodes_toPostMsg(  &pQyMc->gui.guiQ2  )  );
#endif
	 if  (  p->bRunning  )  {			
		 //
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s | %d, %d, %d"  ),  tBuf,  (  int  )pPlayer->audio.playCfg.usMinTimeInMsOfAudioDataPlaying,  (  int  )pPlayer->audio.playCfg.usAudioDataAddedToPlayEveryTime,  (  int  )pPlayer->audio.playCfg.usNotifyIntervalInMs_needMoreAudioData  );				
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %d, %d, %d"  ),  tBuf,  (  int  )pPlayer->audio.playCfg.usMinTimeInMsToPlay,  (  int  )pPlayer->audio.playCfg.usMaxTimeInMsToPlay,  (  int  )pPlayer->audio.playCfg.usMaxTimeInMsToBeRemoved  );
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s | %s"  ),  tBuf,  pPlayer->audio.playbackDevDesc  );
	 }
	 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );
		 
	 cnt  ++  ;

	 //
	 {
		 CAP_procInfo_video  *  p  =  &pProcInfo->av.localAv.videoCaptureProcInfo;

		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
		 index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	
		
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
		 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
		 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		 lstrcpyn(  tBuf,  _T(  "Local video capture"  ),  mycountof(  tBuf  )  );
		 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  p->compressVideo.uiTranNo_openAvDev_org  );
		 index  ++  ;  pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "maxFps %d, minFps %d, curFps %d"  ),  p->compressVideo.compressor.common.usMaxFps_toShareBmp,  p->compressVideo.compressor.common.usMinFps_toShareBmp,  p->compressVideo.usFrames_perSecond_expected  );
		 index  ++  ;  pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  p->bCaptureStarted  ?  _T(  "Capturing"  )  :  _T(  ""  )  );
		 
		 cnt  ++  ;

	 }


	 CAP_procInfo_recordSound  *  pRecordSoundProcInfo  =  &pProcInfo->av.localAv.recordSoundProcInfo;

	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
	 index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	
		
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
	 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
	 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

	 lstrcpyn(  tBuf,  _T(  "Local sound recorder"  ),  mycountof(  tBuf  )  );
	 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pRecordSoundProcInfo->compressAudio.uiTranNo_openAvDev_org  );
	 index  ++  ;  pListCtrl->SetItemText(  cnt,  index,  tBuf  );

	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d,%d,%d | %d  -- %d"  ),  (  int  )pRecordSoundProcInfo->compressAudio.ah_decompress.wfx.nChannels,  pRecordSoundProcInfo->compressAudio.ah_decompress.wfx.nSamplesPerSec,  (  int  )pRecordSoundProcInfo->compressAudio.ah_decompress.wfx.wBitsPerSample,  pRecordSoundProcInfo->compressAudio.compressor.uiBytesRecorded_perBlockAlign,  (  int  )pRecordSoundProcInfo->usErrors_processInput  );
	 index  ++  ;  pListCtrl->SetItemText(  cnt,  index,  tBuf  );
	 
	 tBuf[0]  =  0;
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  tBuf,  pRecordSoundProcInfo->capDevDesc  );
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  tBuf,  pRecordSoundProcInfo->thread.bRunning  ?  _T(  "Recording"  )  :  _T(  ""  )  );
	 TCHAR  *  pT  =  _T(  ""  );
	 switch  (  pRecordSoundProcInfo->uiRecordType  )  {
			 case  CONST_recordType_dSound:
				   pT  =  _T(  "dSound"  );
				   break;
			 case  CONST_recordType_msAec:
				   pT  =  _T(  "AEC"  );
				   break;
			 default:
				    pT  =  _T(  "unknown recordType"  );
					break;
	 }
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %s"  ),  tBuf,  pT  );
	 if  (  pRecordSoundProcInfo->uiRecordType  ==  CONST_recordType_msAec  )  {
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. (%s)"  ),  tBuf,  pRecordSoundProcInfo->aec_rendDevDesc  );
	 }
	 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );
		 
	 cnt  ++  ;





	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}



//
__declspec(  dllexport  )  BOOL  bViewPlayerList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL						bRet			=	FALSE;
	QY_MC					*	pQyMc			=	QY_GET_GBUF(  );		
	QY_SERVICEGUI_INFO		*	pSgi			=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSgi  )  return  -1;
	MC_VAR_isCli				*	pProcInfo		=	(  MC_VAR_isCli  *  )pSgi->pVar;
	if  (  !pProcInfo  )  return  -1;
	QY_MC_SEL					sel;

	traceLogA(  "bViewAudioPlayerList enters."  );

#if  0
	 memset(  &sel,  0,  sizeof(  sel  )  );

	 sel.type  =  CONST_qySelType_mcView;
	 sel.u.mcView.type  =  CONST_qyLvType_realTimeImTaskList;
	 sel.u.mcView.iDsnIndex  =  pQyMc->iDsnIndex_mainSys;					//  用基本系统的数据库
	 sel.u.mcView.pfDisplayListContent  =  (  PF_commonHandler  )bDisplayMcViewContent_players;

	 sel.u.mcView.pfProcEvent			=  netMc_procMcViewEvent;
	 sel.u.mcView.uPopupMenuId			=  IDR_QYMCPOPUP;
	 //  sel.u.mcView.nSubMenuPos			=  pQyMc->cfg.pGuiCfg->iResId_popupMenu_procedObj;

	 _sntprintf(  sel.u.mcView.docName,  mycountof(  sel.u.mcView.docName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_playerList  )  );

	 bQyMcNewMcView(  &sel  );
#endif
	 viewStatusCli(  CONST_qyLvType_playerList,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_playerList  ),  CONST_resId_playerListColumns,  (  PF_commonHandler  )bDisplayMcViewContent_players,  NULL  );

	traceLogA(  "bViewAudioPlayerList leaves."  );

	return  bRet;
}

  
//  BOOL  bDisplayMcViewContent_walls(  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
  BOOL  bDisplayMcViewContent_walls(  CListCtrl  * pListCtrl,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
{
	 BOOL								bRet					=			FALSE;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 QY_SERVICEGUI_INFO				*	pSgi					=			getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	 if  (  !pSgi  )  return  -1;
	 MC_VAR_isCli						*	pProcInfo				=			(  MC_VAR_isCli  *  )pSgi->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 if  (  !pListCtrl  )  return  FALSE;
	 //  CListCtrl						*	pListCtrl				=			&pMcView->GetListCtrl();
	 int								i;
	 //  QY_OBJ_DB						*	pObj;
	 TCHAR								tBuf[256];
	 int								cnt						=			0;
	 int								index;
	 MIS_CNT						*	pMisCnt					=			getMisCntByName(  pProcInfo,  _T(  ""  )  );
	 int								nWaitingInMs			=			0;

	 myListCtrl_delAllColumns(  pListCtrl->m_hWnd  );
	 if  (  !myListCtrl_bAddColumns(  pListCtrl->m_hWnd,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_wallListColumns  )  )  )  goto  errLabel;

	 pListCtrl->DeleteAllItems(  );
	 
	 if  (  !pMisCnt->subWnds.usMaxCnt  ||  !pMisCnt->subWnds.pMems  )  {
		 goto  errLabel;
	 }
	 for  (  i  =  0;  i  <  pMisCnt->subWnds.usMaxCnt;  i  ++  )  {
		  if  (  !IsWindow(  pMisCnt->subWnds.pMems[i].hWnd  )  )  continue;
		  if  (  pMisCnt->subWnds.pMems[i].iWndContentType  !=  CONST_qyWndContentType_vWall  )  continue;
		  
#if  0
		  CDlgDynBmps	*	pDlg	=	(  CDlgDynBmps  *  )CDialoglgDynBmps::FromHandle(  pMisCnt->subWnds.pMems[i].hWnd  );
		  if  (  !pDlg  )  continue;
#endif
		  HWND					hDlg  =  pMisCnt->subWnds.pMems[i].hWnd;
		  DLG_dynBmps_var	*	pVar  =  (  DLG_dynBmps_var  *  )getDlgDynBmpsVar(  hDlg  );
		  if  (  !pVar  )  continue;
		  DLG_dynBmps_var  &  m_var  =  *pVar;


		  //  pDlg->GetWindowText(  tBuf,  mycountof(  tBuf  )  );
		  GetWindowText(  hDlg,  tBuf,  mycountof(  tBuf  )  );
		  index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	

		  cnt  ++  ;

		  int  j,  k, l;
		  for  (  j  =  0;  j  <  m_var.pWall->m_var.usCnt;  j  ++  )  {
			   SUB_V_WALL	*	pSubWall	=	m_var.pWall->getSubWall(  j  );

			   Q_NODE	*	pQNode;
			   for  (  pQNode  =  pSubWall->pRuleQ->front.pNext;  pQNode  &&  pQNode->qElemMemory.m_pBuf;  pQNode  =  pQNode->pNext  )  {
				    VW_ruleU	*	pRule	=	(  VW_ruleU  *  )pQNode->qElemMemory.m_pBuf;
					
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
					index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	

					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Rule %s"  ),  qyGetDesByType1(  CONST_vwRuleTypeTable,  pRule->common.uiType  )  );
					index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );	

					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pRule->common.uiTranNo_spObj  );
					index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

					switch  (  pRule->common.uiType  )  {
							case  CONST_vwRuleType_dynBmp:

								  tBuf[0]  =  0;
								  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

								  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u,%s,%d"  ),  pRule->dynBmp.ruleDynBmp.dynBmp.idInfo.ui64Id,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  ),  pRule->dynBmp.ruleDynBmp.dynBmp.resObj.uiObjType  ),  pRule->dynBmp.ruleDynBmp.dynBmp.resObj.usIndex_obj  );
								  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

								  break;
							case  CONST_vwRuleType_conference_imGrp:

								  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
								  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

								  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pRule->conference_imGrp.idInfo.ui64Id  );
								  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

								  break;
							case  CONST_vwRuleType_conference_imGrpMem:

								  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
								  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

								  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pRule->conference_imGrpMem.idInfo.ui64Id  );
								  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

								  break;
							default:
								    traceLogA(  "bDisplayMcViewContent_walls: unknown ruleType %d",  pRule->common.uiType  );
									break;
					}

					cnt  ++  ;
			   }

			   for  (  k  =  0;  k  <  pSubWall->usCnt;  k  ++  )  {

				   if  (  !pSubWall->mems[k].images.head.usCnt  )  {

						_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
						 index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	
		
						 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Zone"  )  );
						 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );	

						 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d: %d,%d"  ),  pSubWall->mems[k].uiTranNo_spObj,  j,  k  );
						 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

						 cnt  ++  ;
						 continue;
					}

				    for  (  l  =  0;  l  <  mycountof(  pSubWall->mems[k].images.mems  );  l  ++  )  {
						 CAP_IMAGE	*	pImg	=	&pSubWall->mems[k].images.mems[l];

						 if  (  !pImg->iW_org  &&  !pImg->iH_org  )  continue;

						 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ""  )  );
						 index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	
		
						 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Zone"  )  );
						 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );	

		
						 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d: %d,%d, %d"  ),  pSubWall->mems[k].uiTranNo_spObj,  j,  k,  l  );
						 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

						 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pImg->iTaskId  );
						 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

						 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u,%d,%d"  ),  pImg->idInfo_sender.ui64Id,  pImg->uiTranNo_openAvDev,  pImg->usIndex_activeMems_from  );
						 index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

						 cnt  ++  ;
					}
			   }
		  }

	 }
	 
	 //
	 HWND  hListCtrl  =  pListCtrl->m_hWnd;

	 //  2014/11/05	 		 
	 FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );

	 if  (  pFuncs  )  {
		 pFuncs->isCliD3d.PF_bDisplayMcViewContent_d3dWall(  hListCtrl,  &cnt  );
	 }


	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}

 __declspec(  dllexport  )   BOOL  bViewWallList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL						bRet			=	FALSE;
	QY_MC					*	pQyMc			=	QY_GET_GBUF(  );		
	QY_SERVICEGUI_INFO		*	pSgi			=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSgi  )  return  -1;
	MC_VAR_isCli				*	pProcInfo		=	(  MC_VAR_isCli  *  )pSgi->pVar;
	if  (  !pProcInfo  )  return  -1;
	QY_MC_SEL					sel;

	traceLogA(  "bViewWallList enters."  );

#if  0
	 memset(  &sel,  0,  sizeof(  sel  )  );

	 sel.type  =  CONST_qySelType_mcView;
	 sel.u.mcView.type  =  CONST_qyLvType_realTimeImTaskList;
	 sel.u.mcView.iDsnIndex  =  pQyMc->iDsnIndex_mainSys;					//  用基本系统的数据库
	 sel.u.mcView.pfDisplayListContent  =  (  PF_commonHandler  )bDisplayMcViewContent_walls;

	 sel.u.mcView.pfProcEvent			=  netMc_procMcViewEvent;
	 sel.u.mcView.uPopupMenuId			=  IDR_QYMCPOPUP;
	 //  sel.u.mcView.nSubMenuPos			=  pQyMc->cfg.pGuiCfg->iResId_popupMenu_procedObj;

	 _sntprintf(  sel.u.mcView.docName,  mycountof(  sel.u.mcView.docName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_redId_wallList  )  );

	 bQyMcNewMcView(  &sel  );
#endif
	 viewStatusCli(  CONST_qyLvType_wallList,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_wallList  ),  CONST_resId_wallListColumns,  (  PF_commonHandler  )bDisplayMcViewContent_walls,  NULL  );

	traceLogA(  "bViewWallList leaves."  );

	return  bRet;
}

 



//    BOOL  bDisplayMcViewContent_imNetStatList(  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
  BOOL  bDisplayMcViewContent_imNetStatList(  CListCtrl  * pListCtrl,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
{
	 BOOL								bRet					=			FALSE;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 QY_SERVICEGUI_INFO				*	pSgi					=			getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	 if  (  !pSgi  )  return  -1;
	 MC_VAR_isCli						*	pProcInfo				=			(  MC_VAR_isCli  *  )pSgi->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 if  (  !pListCtrl  )  return  FALSE;
	 //  CListCtrl						*	pListCtrl				=			&pMcView->GetListCtrl();
	 int								i;
	 //  QY_OBJ_DB						*	pObj;
	 TCHAR								tBuf[256];
	 int								cnt						=			0;
	 int								index;
	 MIS_CNT						*	pMisCnt					=			getMisCntByName(  pProcInfo,  _T(  ""  )  );

	 myListCtrl_delAllColumns(  pListCtrl->m_hWnd  );
	 if  (  !myListCtrl_bAddColumns(  pListCtrl->m_hWnd,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_imNetStatListColumns  )  )  )  goto  errLabel;

	 pListCtrl->DeleteAllItems(  );

	 for  (  i  =  0;  i  <  mycountof(  pMisCnt->channels  );  i  ++  )  {
		  MIS_CHANNEL  *  pChannel  =  &pMisCnt->channels[i];

		  if  (  !pChannel->uiType  )  continue;

		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  i  );				
		  index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	
		
		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  )  );
		  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );	

		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u bytes"  ),  pChannel->status.netStat.ui64MsgDataLenRecvd  );
		  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u bytes"  ),  pChannel->status.netStat.ui64MsgDataLenSent  );
		  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%dkbps"  ),  pChannel->status.netStat.uiInSpeedInKbps  );
		  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%dkbps"  ),  pChannel->status.netStat.uiOutSpeedInKbps  );
		  index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );

		  cnt  ++  ;

	 }


	 
	 
	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}


  //
  __declspec(  dllexport  )  BOOL  bViewImNetStatList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL						bRet			=	FALSE;
	QY_MC					*	pQyMc			=	QY_GET_GBUF(  );		
	QY_SERVICEGUI_INFO		*	pSgi			=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSgi  )  return  -1;
	MC_VAR_isCli				*	pProcInfo		=	(  MC_VAR_isCli  *  )pSgi->pVar;
	if  (  !pProcInfo  )  return  -1;
	QY_MC_SEL					sel;

	traceLogA(  "bViewImNetStatList enters."  );

#if  0
	 memset(  &sel,  0,  sizeof(  sel  )  );

	 sel.type  =  CONST_qySelType_mcView;
	 sel.u.mcView.type  =  CONST_qyLvType_realTimeImTaskList;
	 sel.u.mcView.iDsnIndex  =  pQyMc->iDsnIndex_mainSys;					//  用基本系统的数据库
	 sel.u.mcView.pfDisplayListContent  =  (  PF_commonHandler  )bDisplayMcViewContent_imNetStatList;

	 sel.u.mcView.pfProcEvent			=  netMc_procMcViewEvent;
	 sel.u.mcView.uPopupMenuId			=  IDR_QYMCPOPUP;
	 //  sel.u.mcView.nSubMenuPos			=  pQyMc->cfg.pGuiCfg->iResId_popupMenu_procedObj;

	 _sntprintf(  sel.u.mcView.docName,  mycountof(  sel.u.mcView.docName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_redId_imNetStatList  )  );

	 bQyMcNewMcView(  &sel  );
#endif
	 viewStatusCli(  CONST_qyLvType_imNetStatList,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_imNetStatList  ),  CONST_resId_imNetStatListColumns,  (  PF_commonHandler  )bDisplayMcViewContent_imNetStatList,  (  PF_commonHandler  )bDisplayMcViewContent_imNetStatList  );

	traceLogA(  "bViewImNetStatList leaves."  );

	return  bRet;
}


  int  tmpHandler_displayTalker(  void  *  p0,  void  *  pCommonParam1Param,  void  *  pQElem  )
{
	 int					iErr				=	-1;
	 //  p0;
	 COMMON_PARAM		*	pCommonParam1		=	(  COMMON_PARAM  *  )pCommonParam1Param;
	 MIS_CNT			*	pMisCnt				=	(  MIS_CNT  *  )pCommonParam1->p0;
	 CListCtrl			*	pListCtrl			=	(  CListCtrl  *  )pCommonParam1->p1;
	 int				*	piCnt				=	(  int  *  )pCommonParam1->p2;
	 //  
	 MIS_MSGU			*	pMsg				=	(  MIS_MSGU  *  )pQElem;
	 //
	 MC_VAR_isCli		*	pProcInfo			=	QY_GET_procInfo_isCli(  );
	 //
	 int					index;
	 TCHAR					tBuf[256];
	 char					timeBuf[CONST_qyTimeLen  +  1];
	 char					displayBuf[128];

	 if  (  pMsg->uiType  ==  CONST_misMsgType_talkingFriend_qmc  )  {
		 HWND			hDlgTalk  =  pMsg->talkingFriend_qmc.hWnd;
		 //  CDlgTalk	*	pDlg	=	(  CDlgTalk  *  )CWnd::FromHandle(  pMsg->talkingFriend_qmc.hWnd  );
		 CHelp_getDlgTalkVar	help_getDlgTalkVar;
		 DLG_talk_var  *  pDlgTalkVar  =  (  DLG_talk_var  *  )help_getDlgTalkVar.getVar(  hDlgTalk  );
		 if  (  !pDlgTalkVar  )  goto  errLabel;
		 DLG_talk_var  &  m_var  =  *pDlgTalkVar;


		 printQ_mis(  m_var.m_pProcessQ,  FALSE  );

		 tBuf[0]  =  0;
		 index  =  0;	pListCtrl->InsertItem(  *piCnt,  tBuf  );	

		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u, tn_shadow %d"  ),  m_var.addr.idInfo.ui64Id,  m_var.addr.uiTranNo_shadow  );
		 index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );
		 index  ++  ;
		 index  ++  ;
		 index  ++  ;
		 index  ++  ;
		 GetWindowText(  hDlgTalk,  tBuf,  mycountof(  tBuf  )  );
		 index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );
		 tBuf[0]  =  0;
		 if  (  m_var.ucbTmpMsgr  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Tmp."  )  );
		 if  (  m_var.m_pProcessQ  )  {
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s qNodes %d."  ),  tBuf,  m_var.m_pProcessQ->uiQNodes  );
		 }

		 //  2014/12/02
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s hWnd %I64u."  ),  tBuf,  (  __int64  )hDlgTalk  );
		 //
		 if  (  !IsWindowVisible(  hDlgTalk  )  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s invisible"  ),  tBuf  );

		 index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );

		 (  *piCnt  )  ++  ;

		 //  2017/02/13		 	
		 tBuf[0]  =  0;			
		 index  =  0;	pListCtrl->InsertItem(  *piCnt,  tBuf  );	
		 index  ++  ;
		 index  ++  ;
		 index  ++  ;
		 index  ++  ;
		 index  ++  ;

		 _sntprintf(  tBuf, mycountof(  tBuf  ),  _T(  "iIndex_talkerInfo %d"  ),  m_var.iIndex_talkerInfo  );	
		 index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );			

		 (  *piCnt  )  ++  ;

		 
		 //  2014/05/30
		 if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
			 TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;	
			 if  (  !pShadowMgr  )  goto  errLabel;
	
			 VW_rule_messengerCmd  *  pCmd;

			 tBuf[0]  =  0;
			 index  =  0;	pListCtrl->InsertItem(  *piCnt,  tBuf  );	
			 index  ++  ;
			 index  ++  ;
			 index  ++  ;
			 index  ++  ;
			 index  ++  ;

			 _sntprintf(  tBuf, mycountof(  tBuf  ),  _T(  "cmd_manual"  )  );	
			 index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );			

			 pCmd  =  &pShadowMgr->vwRuleCmd_manual;

			 tBuf[0]  =  0;
			 //  2014/06/03
			 int  i;
			 for  (  i  =  0;  i  <  mycountof(  pCmd->dynBmpRules  );  i  ++  )  {
				  DYN_BMP_RULE  dynBmp  =  pCmd->dynBmpRules[i];
				  if  (  tmpF_bViewRemoteVideo(  pCmd,  dynBmp.dynBmp.resObj.uiObjType,  dynBmp.dynBmp.resObj.usIndex_obj,  dynBmp.dynBmp.resObj.usHelp_subIndex  )  )  {
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s[%d]: %d,%d"  ),  tBuf,  i,  dynBmp.dynBmp.resObj.uiObjType,  dynBmp.dynBmp.resObj.usIndex_obj  );
					  if  (  dynBmp.ucbSaveVideo  )  {	//  2014/08/04
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s save"  ),  tBuf  );
					  }
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. "  ),  tBuf  );

				  }
			 }
			 //
			 if  (  pCmd->ucbViewGps  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s viewGps"  ),  tBuf  );					//  2012/04/25


			 index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );			
			
			 (  *piCnt  )  ++  ;

			 //
			 tBuf[0]  =  0;
			 index  =  0;	pListCtrl->InsertItem(  *piCnt,  tBuf  );	
			 index  ++  ;
			 index  ++  ;
			 index  ++  ;
			 index  ++  ;
			 index  ++  ;

			 _sntprintf(  tBuf, mycountof(  tBuf  ),  _T(  "cmd"  )  );
			 index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );			

			 pCmd  =  &pShadowMgr->vwRuleCmd;

			 tBuf[0]  =  0;
			 //  2014/06/03
			 for  (  i  =  0;  i  <  mycountof(  pCmd->dynBmpRules  );  i  ++  )  {
				  DYN_BMP_RULE  dynBmp  =  pCmd->dynBmpRules[i];
				  if  (  tmpF_bViewRemoteVideo(  pCmd,  dynBmp.dynBmp.resObj.uiObjType,  dynBmp.dynBmp.resObj.usIndex_obj,  dynBmp.dynBmp.resObj.usHelp_subIndex  )  )  {
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s[%d]: %d,%d"  ),  tBuf,  i,  dynBmp.dynBmp.resObj.uiObjType,  dynBmp.dynBmp.resObj.usIndex_obj  );
					  if  (  dynBmp.ucbSaveVideo  )  {	//  2014/08/04
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s save"  ),  tBuf  );
					  }
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. "  ),  tBuf  );
				  }
			 }
			 //
			 if  (  pCmd->ucbViewGps  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s viewGps"  ),  tBuf  );					//  2012/04/25


			 index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );			
			
			 (  *piCnt  )  ++  ;

			 //  2014/09/05
			 tBuf[0]  =  0;
			 index  =  0;	pListCtrl->InsertItem(  *piCnt,  tBuf  );	
			 index  ++  ;
			 index  ++  ;
			 index  ++  ;
			 index  ++  ;
			 index  ++  ;

			 _sntprintf(  tBuf, mycountof(  tBuf  ),  _T(  "talkerObj"  )  );
			 index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );			


			 tBuf[0]  =  0;
			 //  2014/06/03
			 for  (  i  =  0;  i  <  mycountof(  pShadowMgr->talkerDynBmps  );  i  ++  )  {
				  TALKER_dynBmp dynBmp  =  pShadowMgr->talkerDynBmps[i];
				  if  (  tmpF_bViewRemoteVideo(  pCmd,  dynBmp.dynBmpRule.dynBmp.resObj.uiObjType,  dynBmp.dynBmpRule.dynBmp.resObj.usIndex_obj,  dynBmp.dynBmpRule.dynBmp.resObj.usHelp_subIndex  )  )  {
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s[%d]: %d,%d"  ),  tBuf,  i,  dynBmp.dynBmpRule.dynBmp.resObj.uiObjType,  dynBmp.dynBmpRule.dynBmp.resObj.usIndex_obj  );
					  if  (  dynBmp.dynBmpRule.ucbSaveVideo  )  {
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s save"  ),  tBuf  );
					  }
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s taskId %d"  ),  tBuf,  dynBmp.taskInfo.iTaskId  );  
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %dX%d %s"  ),  tBuf,  dynBmp.taskInfo.srcInfo.iW,  dynBmp.taskInfo.srcInfo.iH,  (  dynBmp.taskInfo.srcInfo.ucbUnresizable  ?  _T(  "Unresize"  )  :  _T(  ""  )  )  );
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. "  ),  tBuf  );
				  }
			 }

			 index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );			
			
			 (  *piCnt  )  ++  ;


		 }


		 //  2012/05/06
		 if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
			 TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
			 if  (  pShadowMgr  )  {
				 //
				 int  i;
				 for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
					  TALKER_shadow_mgrMem  *  pMem  =  &pShadowMgr->shadows[i];
					  if  (  pMem->hWall  )  {
						  if  (  IsWindow(  pMem->hShadow  )  )  {
							  	CHelp_getDlgTalkVar	help_getDlgTalkVar;
								DLG_TALK_var	*	pm_var	=	(  DLG_TALK_var	*	)help_getDlgTalkVar.getVar(  pMem->hShadow  );
								if  (  pm_var  )  {								
									tBuf[0]  =  0;		
									index  =  0;	pListCtrl->InsertItem(  *piCnt,  tBuf  );	
									index  ++  ;
									index  ++  ;
									index  ++  ;
									index  ++  ;
									index  ++  ;

									tBuf[0]  =  0;
									_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "shadows[%d]. %d"  ),  i,  pm_var->addr.uiTranNo_shadow  );					 								
									index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );
								
									(  *piCnt  )  ++  ;
								}
							    }
						  else  {		//  2014/02/04
									tBuf[0]  =  0;		
									index  =  0;	pListCtrl->InsertItem(  *piCnt,  tBuf  );	
									index  ++  ;
									index  ++  ;
									index  ++  ;
									index  ++  ;
									index  ++  ;

									tBuf[0]  =  0;
									_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "shadows[%d]: %s(%d)"  ),  i,  qyGetDesByType1(  CONST_qyWndContentTypeTable,  pMem->iWndContentType_wall  ),  pMem->iWndContentType_wall  );					 								
									if  (  pMem->iWndContentType_wall  ==  CONST_qyWndContentType_consoleWall  )  {
										_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s %d %d"  ),  tBuf,  qyGetDesByType1(  CONST_wmGrpTypeTable,  pMem->wdId.iGrpType  ),  pMem->wdId.index_wm,  pMem->wdId.uiTranNo_wm  );

									}
									index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );
									
									(  *piCnt  )  ++  ;
						    
						  }
					  }
					  
				 }
				 //
				 if  (  pShadowMgr->vwRuleCmd.ucbViewGps  )  {
					 tBuf[0]  =  0;		
					 index  =  0;	pListCtrl->InsertItem(  *piCnt,  tBuf  );	
					 index  ++  ;
					 index  ++  ;
					 index  ++  ;
					 gps_DisplayStr(  &pShadowMgr->viewGps.gpsPos,  tBuf,  mycountof(  tBuf  )  );
					 if  (  pShadowMgr->viewGps.dwTickCnt_lastRecvd  )  {
						 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. -%dms"  ),  tBuf,  GetTickCount(  )  -  pShadowMgr->viewGps.dwTickCnt_lastRecvd  );
					 }
					 index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );

					 (  *piCnt  )  ++  ;
				 }

			 }
			 }			 
		 else  {
			   TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )m_var.pShadowInfo;
			   if  (  pShadow  )  {
				   if  (  pShadow->viewGps.dwTickCnt_lastRefreshed  )  {
				   
					   tBuf[0]  =  0;		
					   index  =  0;	pListCtrl->InsertItem(  *piCnt,  tBuf  );	
					   index  ++  ;
					   index  ++  ;
					   index  ++  ;
					   tBuf[0]  =  0;
					   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "gps -> (%d,%d) -> (%d,%d). -%dms"  ),  pShadow->viewGps.point_xy.x,  pShadow->viewGps.point_xy.y,  pShadow->viewGps.point.x,  pShadow->viewGps.point.y,  GetTickCount(  )  -  pShadow->viewGps.dwTickCnt_lastRefreshed  );  
					   index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );

					   (  *piCnt  )  ++  ;
				   }				   			   
			   }
		 }

		 //
		 if  (  isTalkerShadowMgr(  m_var.addr  )  
			 &&  m_var.av.taskInfo.bTaskExists  )  
		 {
			 //
			 tBuf[0]  =  0;				
			 index  =  0;	pListCtrl->InsertItem(  *piCnt,  tBuf  );	
			 index  ++  ;
			 index  ++  ;
			 index  ++  ;
			 index  ++  ;
			 index  ++  ;
			 
			 tBuf[0]  =  0;		
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "tn_org %d"  ),  m_var.av.taskInfo.uiTranNo_org  );
			 index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );
					   
			 tBuf[0]  =  0;			
			 index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );

					   
			 (  *piCnt  )  ++  ;			
			 //

			 //
			 QMC_TASK_INFO  *  pTaskInfo  =  (  QMC_TASK_INFO  *  )pProcInfo->getQmcTaskInfoByIndex(  m_var.av.taskInfo.iIndex_taskInfo  );	
			 if  (  pTaskInfo  
				 &&  pTaskInfo->bUsed  
				 &&  pTaskInfo->var.iTaskId  ==  m_var.av.taskInfo.iTaskId  )  
			 {	

				 QMC_taskData_conf  *  pTaskData  =  (  QMC_taskData_conf  *  )pTaskInfo->var.pTaskData;
				 if  (  pTaskData  
					 &&  pTaskData->common.uiType  ==  CONST_taskDataType_conf  )  
				 {
					 TCHAR  tBuf1[512]  =  _T(  ""  );
					 int  i;
					 for  (  i  =  0;  i  <  pTaskData->usCnt_pMems;  i  ++  )  {
						   CONF_mem  *  pMem  =  &pTaskData->pMems[i];
						  _sntprintf(  tBuf1,  mycountof(  tBuf1  ),  _T(  "%s mems[%d]: %I64u, taskId %d "  ),  tBuf1,  i,  pMem->idInfo.ui64Id,  pMem->view.mem.talkerDynBmp.taskInfo.iTaskId  );						  
					 }
					   tBuf[0]  =  0;
					   index  =  0;	pListCtrl->InsertItem(  *piCnt,  tBuf  );	
					   index  ++  ;
					   index  ++  ;
					   index  ++  ;
					   index  ++  ;
					   index  ++  ;

					   tBuf[0]  =  0;
					   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "bgWall: %s"  ),  tBuf1  );
					   index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );
					   tBuf[0]  =  0;
					   index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );

					   (  *piCnt  )  ++  ;
					 //

				 }
			 }
		 }

		 CAP_images  *  pImgs;


		 //  2014/12/10
					   tBuf[0]  =  0;
					   index  =  0;	pListCtrl->InsertItem(  *piCnt,  tBuf  );	
					   index  ++  ;
					   index  ++  ;
					   index  ++  ;
					   index  ++  ;
					   index  ++  ;

					   tBuf[0]  =  0;
					   pImgs  =  &m_var.av.meZone.images;	//  .meImages;
					   snprintCapImages(  _T(  "meImgs:"  ),  &pImgs->head,  pImgs->mems,  sizeof(  pImgs->mems[0]  ),  mycountof(  pImgs->mems  ),  tBuf,  mycountof(  tBuf  )  );
					   index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );
					   tBuf[0]  =  0;
					   //  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "gps -> (%d,%d) -> (%d,%d). -%dms"  ),  pShadow->viewGps.point_xy.x,  pShadow->viewGps.point_xy.y,  pShadow->viewGps.point.x,  pShadow->viewGps.point.y,  GetTickCount(  )  -  pShadow->viewGps.dwTickCnt_lastRefreshed  );  
					   index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );

					   (  *piCnt  )  ++  ;

		 //  2014/12/10
					   tBuf[0]  =  0;
					   index  =  0;	pListCtrl->InsertItem(  *piCnt,  tBuf  );	
					   index  ++  ;
					   index  ++  ;
					   index  ++  ;
					   index  ++  ;
					   index  ++  ;

					   tBuf[0]  =  0;
					   pImgs  =  &m_var.av.peerZone.images;
					   snprintCapImages(  _T(  "peerImgs:"  ),  &pImgs->head,  pImgs->mems,  sizeof(  pImgs->mems[0]  ),  mycountof(  pImgs->mems  ),  tBuf,  mycountof(  tBuf  )  );
					   index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );
					   tBuf[0]  =  0;
					   //  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "gps -> (%d,%d) -> (%d,%d). -%dms"  ),  pShadow->viewGps.point_xy.x,  pShadow->viewGps.point_xy.y,  pShadow->viewGps.point.x,  pShadow->viewGps.point.y,  GetTickCount(  )  -  pShadow->viewGps.dwTickCnt_lastRefreshed  );  
					   index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );

					   (  *piCnt  )  ++  ;


					   //  2014/12/25
					   tBuf[0]  =  0;
					   index  =  0;	pListCtrl->InsertItem(  *piCnt,  tBuf  );	
					   index  ++  ;
					   index  ++  ;
					   index  ++  ;
					   index  ++  ;
					   index  ++  ;

					   tBuf[0]  =  0;
					   pImgs  =  &m_var.av.otherZone.images;
					   snprintCapImages(  _T(  "otherImgs:"  ),  &pImgs->head,  pImgs->mems,  sizeof(  pImgs->mems[0]  ),  mycountof(  pImgs->mems  ),  tBuf,  mycountof(  tBuf  )  );
					   index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );
					   tBuf[0]  =  0;
					   //  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "gps -> (%d,%d) -> (%d,%d). -%dms"  ),  pShadow->viewGps.point_xy.x,  pShadow->viewGps.point_xy.y,  pShadow->viewGps.point.x,  pShadow->viewGps.point.y,  GetTickCount(  )  -  pShadow->viewGps.dwTickCnt_lastRefreshed  );  
					   index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );

					   (  *piCnt  )  ++  ;

					   //
					   int  jj;
					   for  (  jj  =  0;  jj  <  m_var.av.bgWall.usCnt;  jj  ++  )  {
					   		 //  2014/10/10
						   tBuf[0]  =  0;
						   index  =  0;	pListCtrl->InsertItem(  *piCnt,  tBuf  );	
						   index  ++  ;
						   index  ++  ;
						   index  ++  ;
						   index  ++  ;
						   index  ++  ;

						   tBuf[0]  =  0;
						   pImgs  =  &m_var.av.bgWall.mems[jj].images;
						   snprintCapImages(  _T(  "bgWallImgs:"  ),  &pImgs->head,  pImgs->mems,  sizeof(  pImgs->mems[0]  ),  mycountof(  pImgs->mems  ),  tBuf,  mycountof(  tBuf  )  );
						   index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );
						   tBuf[0]  =  0;
						   //  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "gps -> (%d,%d) -> (%d,%d). -%dms"  ),  pShadow->viewGps.point_xy.x,  pShadow->viewGps.point_xy.y,  pShadow->viewGps.point.x,  pShadow->viewGps.point.y,  GetTickCount(  )  -  pShadow->viewGps.dwTickCnt_lastRefreshed  );  
						   index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );

						   (  *piCnt  )  ++  ;

					   }


		 //
		 if  (  m_var.m_pProcessQ  )  {
			 Q_NODE	*	pQNode;
			 for  (  pQNode  =  m_var.m_pProcessQ->front.pNext;  pQNode;  pQNode  =  pQNode->pNext  )  {			 
				   pMsg	=  (  MIS_MSGU  *  )pQNode->qElemMemory.m_pBuf;


				   switch  (  pMsg->uiType  )  {
						   case  CONST_misMsgType_task:
						
								 //tmpHandler_displayRealTimeTasks(  pListCtrl,  piCnt,  pMsg  );

								 break;
						   case  CONST_misMsgType_talk:

							     tBuf[0]  =  0;		
								 index  =  0;	pListCtrl->InsertItem(  *piCnt,  tBuf  );	
								 
								 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  qyGetDesByType1(  CONST_misMsgTypeTable,  pMsg->uiType  )  );
								 index  ++  ;  pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );


							     index  ++  ;

								 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u:"  ),  pMsg->talk.data.route.idInfo_from.ui64Id  );
								 IM_CONTENTU  *  pContent;  pContent  =  M_getMsgContent(  pMsg->talk.ucFlg,  &pMsg->talk.data  );
								 switch  (  pContent->uiType  )  {
										 case  CONST_imCommType_htmlContent:
											   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  tBuf,  pContent->html.wBuf  );
											   break;
										 default:
												break;
								 }
								 index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );

								 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  qyGetDesByType1(  CONST_qyStatusTable_en,  pMsg->talk.iStatus  )  );
								 //
								 if  (  pMsg->talk.tStartTime  )  {
									 getTimeStr(  pMsg->talk.tStartTime,  timeBuf,  mycountof(  timeBuf  )  );
									 qyDisplayTime(  timeBuf,  displayBuf,  mycountof(  displayBuf  )  );
									 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. startT %s"  ),  tBuf,  CQyString(  displayBuf  ).GetBuffer(  0  )  );
								 }
								 if  (  pMsg->talk.tLastModifiedTime  )  {
									 getTimeStr(  pMsg->talk.tLastModifiedTime,  timeBuf,  mycountof(  timeBuf  )  );
									 qyDisplayTime(  timeBuf,  displayBuf,  mycountof(  displayBuf  )  );
									 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. modifiedT %s"  ),  tBuf,  CQyString(  displayBuf  ).GetBuffer(  0  )  );
								 }
								 //
								 index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );

								 //
								 (  *piCnt  )  ++  ;

							     break;
						   default:

							     tBuf[0]  =  0;		
								 index  =  0;	pListCtrl->InsertItem(  *piCnt,  tBuf  );	
								 
								 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  qyGetDesByType1(  CONST_misMsgTypeTable,  pMsg->uiType  )  );
								 index  ++  ;  pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );

								 //
								 (  *piCnt  )  ++  ;

								  break;			  
				   }

				   continue;
			 } 
		 }
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
}


//  2015/12/04
int  displayActiveTalker(  HWND  hDlgTalk,  int  index_zoneMem,  CListCtrl  *  pListCtrl,  int  *  piCnt  )
{	
		 int  iErr  =  -1;

		 CHelp_getDlgTalkVar	help_getDlgTalkVar;

		 TCHAR  tBuf[128]  =  _T(  ""  );
		 int  index;

		 //printQ_mis(  m_var.m_pProcessQ,  FALSE  );

		 tBuf[0]  =  0;
		 index  =  0;	pListCtrl->InsertItem(  *piCnt,  tBuf  );	
		 

		 DLG_talk_var  *  pDlgTalkVar  =  (  DLG_talk_var  *  )help_getDlgTalkVar.getVar(  hDlgTalk  );
		 if  (  !pDlgTalkVar  )  {
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "ActiveTalker[%d]: "  ),  index_zoneMem  );			 
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s Invalid dlgTalk"  ),  tBuf  );				
			 //			 
			 index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );
			 }
		 else  {
			   DLG_talk_var  &  m_var  =  *pDlgTalkVar;
			   
			   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "ActiveTalker[%d]: "  ),  index_zoneMem  );
			   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%I64u"  ),  tBuf,  m_var.addr.idInfo.ui64Id  );
			   if  (  m_var.addr.uiTranNo_shadow  )  {		 
				   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, tn_shadow %d"  ),  tBuf,  m_var.addr.uiTranNo_shadow  );		 
			   }
			   		 
			   //
			   index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );
			   index  ++  ;
			   index  ++  ;
			   index  ++  ;
			   index  ++  ;
			   GetWindowText(  hDlgTalk,  tBuf,  mycountof(  tBuf  )  );
			   index  ++  ;	pListCtrl->SetItemText(  *piCnt,  index,  tBuf  );

		 }

		 (  *piCnt  )  ++  ;

		 iErr  =  0;
errLabel:
		 return  iErr;

}



//   BOOL  bDisplayMcViewContent_talkerList(  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
   BOOL  bDisplayMcViewContent_talkerList(  CListCtrl  * pListCtrl,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
{
	 BOOL								bRet					=			FALSE;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 QY_SERVICEGUI_INFO				*	pSgi					=			getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	 if  (  !pSgi  )  return  -1;
	 MC_VAR_isCli						*	pProcInfo				=			(  MC_VAR_isCli  *  )pSgi->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 if  (  !pListCtrl  )  return  FALSE;
	 //  CListCtrl						*	pListCtrl				=			&pMcView->GetListCtrl();
	 int								i;
	 //  QY_OBJ_DB						*	pObj;
	 int								cnt						=			0;
	 //  int								index;
	 MIS_CNT						*	pMisCnt					=			getMisCntByName(  pProcInfo,  _T(  ""  )  );

	 myListCtrl_delAllColumns(  pListCtrl->m_hWnd  );
	 if  (  !myListCtrl_bAddColumns(  pListCtrl->m_hWnd,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_talkerListColumns  )  )  )  goto  errLabel;

	 pListCtrl->DeleteAllItems(  );

	 //  2015/12/04
	 ZONE_objs  *  pZoneObjs  =  pProcInfo->pGZone_activeTalkers;
	 for  (  i  =  0;  i  <  mycountof(  pZoneObjs->mems  );  i  ++  )  {
		 ZONE_obj  *  pMem  =  &pZoneObjs->mems[i];
		 if  (  !pMem->hWndWallMem  )  continue;
		 displayActiveTalker(  pMem->hWndWallMem,  i,  pListCtrl,  &cnt  );
	 }


	 ///
	 COMMON_PARAM	commonParam;
	 MACRO_makeCommonParam3(  pMisCnt,  pListCtrl,  &cnt,  commonParam  );
	 qTraverse(  &pMisCnt->talkingFriendQ,  tmpHandler_displayTalker,  0,  &commonParam  );
 
	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}


 //
 __declspec(  dllexport  )  BOOL  bViewTalkerList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL						bRet			=	FALSE;
	QY_MC					*	pQyMc			=	QY_GET_GBUF(  );		
	QY_SERVICEGUI_INFO		*	pSgi			=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSgi  )  return  -1;
	MC_VAR_isCli				*	pProcInfo		=	(  MC_VAR_isCli  *  )pSgi->pVar;
	if  (  !pProcInfo  )  return  -1;
	QY_MC_SEL					sel;

	traceLogA(  "bViewTalkerList enters."  );

	//	 
	viewStatusCli(  CONST_qyLvType_talkerList,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_talkerList  ),  CONST_resId_talkerListColumns,  (  PF_commonHandler  )bDisplayMcViewContent_talkerList,  NULL  );

	traceLogA(  "bViewTalkerList leaves."  );

	return  bRet;
}



 int  tmpHandler_displayMessengerStatus(  int  *  pCnt,  CListCtrl  *  pListCtrl,  QM_OBJQ_MEM	*	pQMem  )
{
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli			*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	TCHAR						tBuf[256];
	int							index;

	QMEM_MESSENGER_CLI		*	pQMemObj	=  (  QMEM_MESSENGER_CLI  *  )pQMem->pQMemObj;
	int						&	cnt			=	*pCnt;

	QY_DMITEM				*	pTable		=  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d. %s, %I64u"  ),  cnt, qyGetDesByType1(  pTable,  pQMemObj->uiType  ),  pQMemObj->idInfo.ui64Id  );
	index  =  0;	pListCtrl->InsertItem(  cnt,  tBuf  );	

	tBuf[0]  =  0;

	if  (  pQMemObj->uiType  ==  CONST_objType_me  )  {
		MIS_CNT	*	pMisCnt  =  getMisCntByName(  pProcInfo,  _T(  ""  )  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, wall: %I64u, %d, %d"  ),  tBuf,  pMisCnt->imRules.conferenceId_shareWebcam.ui64Id,  (  int  )pMisCnt->imRules.ucbNoLocalVideoInThisConference,  (  int  )pMisCnt->imRules.ucbDistinguishSharedWebcams  ); 
	}

	//
	if  (  pQMemObj->rules.uiCmd_autoAnswer_av  )  {
		pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ruleCmdTable  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, av: %s"  ),  tBuf,  qyGetDesByType1(  pTable,  pQMemObj->rules.uiCmd_autoAnswer_av  )  );
	}
	if  (  pQMemObj->rules.uiCmd_autoAnswer_screen  )  {
		pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ruleCmdTable  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, screen: %s"  ),  tBuf,  qyGetDesByType1(  pTable,  pQMemObj->rules.uiCmd_autoAnswer_screen  )  );
	}
	if  (  pQMemObj->rules.uiCmd_autoAnswer_mediaFile  )  {
		pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ruleCmdTable  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, mediaFile: %s"  ),  tBuf,  qyGetDesByType1(  pTable,  pQMemObj->rules.uiCmd_autoAnswer_mediaFile  )  );
	}

	index  ++  ;	pListCtrl->SetItemText(  cnt,  index,  tBuf  );
	 
	cnt  ++  ;

	return  0;
 }

//  BOOL  bDisplayMcViewContent_messengerStatus(  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
   BOOL  bDisplayMcViewContent_messengerStatus(  CListCtrl  * pListCtrl,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCVIEW_SEL  *  pSel  )
{
	 BOOL								bRet					=			FALSE;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 QY_SERVICEGUI_INFO				*	pSgi					=			getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	 if  (  !pSgi  )  return  -1;
	 MC_VAR_isCli						*	pProcInfo				=			(  MC_VAR_isCli  *  )pSgi->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 if  (  !pListCtrl  )  return  FALSE;
	 //  CListCtrl						&	ListCtrl				=			pMcView->GetListCtrl();
	 //  int								i;
	 //  QY_OBJ_DB						*	pObj;
	 //  char								buf[256];
	 int								cnt						=			0;


	 myListCtrl_delAllColumns(  pListCtrl->m_hWnd  );
	 if  (  !myListCtrl_bAddColumns(  pListCtrl->m_hWnd,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_messengerStatusColumns  )  )  )  goto  errLabel;

	 pListCtrl->DeleteAllItems(  );

	 MIS_CNT	*	pMisCnt	=	getMisCntByName(  pProcInfo,  _T(  ""  )  );
	 
	 qmObjQTraverse(  pSgi,  pMisCnt->pObjQ,  (  PF_commonHandler  )tmpHandler_displayMessengerStatus,  &cnt,  pListCtrl  );


	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}



//
   __declspec(  dllexport  )  BOOL  bViewMessengerStatusList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL						bRet			=	FALSE;
	QY_MC					*	pQyMc			=	QY_GET_GBUF(  );		
	QY_SERVICEGUI_INFO		*	pSgi			=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSgi  )  return  -1;
	MC_VAR_isCli				*	pProcInfo		=	(  MC_VAR_isCli  *  )pSgi->pVar;
	if  (  !pProcInfo  )  return  -1;
	QY_MC_SEL					sel;

	traceLogA(  "bViewMessengerStatusList enters."  );

#if  0
	 memset(  &sel,  0,  sizeof(  sel  )  );

	 sel.type  =  CONST_qySelType_mcView;
	 sel.u.mcView.type  =  CONST_qyLvType_anyObjList;
	 sel.u.mcView.iDsnIndex  =  pQyMc->iDsnIndex_mainSys;					//  用基本系统的数据库
	 sel.u.mcView.pfDisplayListContent  =  (  PF_commonHandler  )bDisplayMcViewContent_messengerStatus;

	 sel.u.mcView.pfProcEvent			=  netMc_procMcViewEvent;
	 sel.u.mcView.uPopupMenuId			=  IDR_QYMCPOPUP;
	 //  sel.u.mcView.nSubMenuPos			=  pQyMc->cfg.pGuiCfg->iResId_popupMenu_procedObj;

	 _sntprintf(  sel.u.mcView.docName,  mycountof(  sel.u.mcView.docName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_messengerStatusList  )  );

	 bQyMcNewMcView(  &sel  );
#endif
	 viewStatusCli(  CONST_qyLvType_messengerStatusList,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_messengerStatusList  ),  CONST_resId_messengerStatusColumns,  (  PF_commonHandler  )bDisplayMcViewContent_messengerStatus,  NULL  );


	traceLogA(  "bViewMessengerStatusList leaves."  );

	return  bRet;
}


