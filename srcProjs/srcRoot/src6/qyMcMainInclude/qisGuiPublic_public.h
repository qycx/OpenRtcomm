

#ifndef  __qisGuiPublic_public_h__
#define  __qisGuiPublic_public_h__	//  {

//
#include	"qyLangCommProc.h"


//
typedef  struct  __param_qyMessengeBox_t  {
				 BOOL						bShow_noPrompt;
				 //
				 BOOL						bCheck_noPropmt;
}		 PARAM_qyMessengeBox;



//
__declspec(  dllexport  )  int  WINAPI  qyMessageBox(  HWND hWnd ,  LPCWSTR lpText,  LPCWSTR lpCaption,  UINT uType,  UINT  nTimeoutInS,  BOOL  *  pbSyncFlg  );
__declspec(  dllexport  )  int  WINAPI  qyMessageBox_custom(  HWND hWnd ,  LPCWSTR lpText,  LPCWSTR lpCaption,  UINT uType,  UINT  nTimeoutInS,  BOOL  *  pbSyncFlg,  PARAM_qyMessengeBox  *  pParam  );


//	
typedef  struct  __qyProgress_t									{
				 struct											{
						 HWND									hWnd;
						 unsigned  int							uiTranNo;
						 //
						 unsigned  char							ucbProgessEnd;
						 int									nResult;
						 //
				 }												var;

				 //					
				 BOOL											bInSequence_showDlgProgress;			//  2014/05/07
				 	
}  QY_PROGRESS;



  //  2010/08/14
  __declspec(dllexport)  int  startProgress(  QY_PROGRESS  *  pProgress,  unsigned  int  uiTranNo  );
  __declspec(dllexport) int  notifyProgressEnd(  QY_PROGRESS  *  pProgress,  unsigned  int  uiTranNo,  int  nResult  );
  __declspec(dllexport)  int  showProgress(  QY_PROGRESS  *  pProgress,  QNM_CUSRES_INFO  *  pCusResInfo,  HWND  hParent,  LPCTSTR  title,  LPCTSTR  progressTxt,  int  nStep_finished,  int  iIndex_shmCmd,  unsigned  int  uiTranNo  =  0,  BOOL  canUsrOk  =  FALSE,  PF_commonHandler  pf_doProgress  =  NULL  );



//
 __declspec(dllexport)  int   set_g_pQnmCusResInfo_qisGuiPublic(  void  *  pQnmCusResInfo  );
 

#endif  //  }


