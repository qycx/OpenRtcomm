
#include "stdafx.h"
#include	<afxpriv.h>

#include	<iphlpapi.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainWndProc.h"
#include	"funcsForIsCliHelp.h"
#include	"isCliHelpPublic.h"
#include	"qnmResDefs.h"
#include	"isCmdConst.h"
#include	"guiShare.h"



  __declspec(  dllexport  )  int mainWnd_OnQyTrayNotify(  HWND  hMainWnd,  void  *  pVar,  WPARAM  wParam,  LPARAM  lParam  )
{
	LONG				lRet				=	-1;
	CMenu				tmpMenu;
	CMenu			*	tmppPopupMenu		=		NULL;
	//
	int					nPos				=		CONST_resId_popup_trayNotify;		//  2006/12/31
	//
	QY_MC			*	pQyMc				=		QY_GET_GBUF(  );
	MC_VAR_isCli  *  pProcInfo  =   QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp	*	pFuncs			=		QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	QY_DMITEM		*	pItem;
	QY_OBJ_DB		*	pObjDb				=		NULL;
	OBJ_STATUS_INFO		objStatusInfoU;
	//
	unsigned  int		uCmd				=		0;

	
	QNM_cusRes_moduleMem  *  pResMem  =  getCurCusResModuleMem(  &pQyMc->cusRes  );
	 if  (  !pResMem  )  goto  errLabel;


	// Get the submenu to use as a pop-up menu
	//  HMENU submenu = GetSubMenu(_this->m_hmenu, 0);

	memset(  &objStatusInfoU,  0,  sizeof(  objStatusInfoU  )  );


	if  (  !(  tmpMenu.CreatePopupMenu(  )  )  )  goto  errLabel;
	if  (  !(  pItem  =  (  QY_DMITEM  *  )qyGetDesByType(  pResMem->pCusMenuTable,  CONST_resId_popupMenu  )  )  )  goto  errLabel;
	if  (  !(  pItem  =  qyGetDmItemByType(  pItem,  nPos,  sizeof(  QY_DMITEM  )  )  )  )  goto  errLabel;
	if  (	 makeDynaMenu(  &pQyMc->cusRes,  tmpMenu.m_hMenu,  (  QY_DMITEM  *  )pItem->pData,  pFuncs->pf_getMenuStatus,  pQyMc,  &objStatusInfoU  )  )  goto  errLabel;
	tmppPopupMenu  = &tmpMenu;

	if (tmppPopupMenu == NULL)  goto  errLabel;
		

	// What event are we responding to, RMB click?
	if (lParam==WM_RBUTTONUP)  {
		if (tmppPopupMenu == NULL)  return 0;
		
				
		// Make the first menu item the default (bold font)
		SetMenuDefaultItem(  tmppPopupMenu->m_hMenu, 0, TRUE);
				
		// Get the current cursor position, to display the menu at
		POINT mouse;
		GetCursorPos(&mouse);

		// There's a "bug"
		// (Microsoft calls it a feature) in Windows 95 that requires calling
		// SetForegroundWindow. To find out more, search for Q135788 in MSDN.
		//
		::SetForegroundWindow(  hMainWnd  );

		// Display the menu at the desired position
		uCmd  =  TrackPopupMenu(  tmppPopupMenu->m_hMenu,  TPM_RETURNCMD | TPM_LEFTALIGN | TPM_RIGHTBUTTON  |  TPM_NONOTIFY, mouse.x, mouse.y, 0,  hMainWnd, NULL);

		if  (  uCmd  )  PostMessage(  hMainWnd,  WM_COMMAND,  MAKEWPARAM(  uCmd,  0  ),  0  );
		/*
		switch  (  uCmd  )  {
				case  ID_APP_ABOUT:
					  SendMessage(  WM_COMMAND,  uCmd,  0  );
					  break;
					  
				default:
						break;
		}
		*/

				
		return 0;
	}
			
	// Or was there a LMB double click?
	if  (  lParam  ==  WM_LBUTTONDBLCLK  )  {
		// double click: execute first menu item
		::SendMessage(  hMainWnd,  WM_COMMAND,  GetMenuItemID(  tmppPopupMenu->m_hMenu, 0),  0);
			
	}
	
errLabel:
	return  0;
}


