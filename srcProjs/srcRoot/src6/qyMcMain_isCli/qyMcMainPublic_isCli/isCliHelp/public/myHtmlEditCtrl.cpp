
#include	"stdafx.h"

#include	<windowsx.h>
#include	<math.h>
#include	"qymcMainCommon.h"


#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture_isCli.h"

#include	"myHtmlEditCtrl.h"

#include	"tmpCeLib.h"

#include	"qyOpenShellCommon.h"
#include	"myresource.h"
#include	"subtitles.h"
#include	"DlgTalk.h"
#include	"qyRtcCommProc.h"
#include	"qyCusResTemp.h"
#include	"DlgInstantAssistant.h"
#include	<assert.h>
#include	"qyPs.h"
#include	"qmcDxSurfacePublic.h"
#include	"qmcConferenceWall.h"
#include	"qmcCmdProc.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

//
#include	"DlgMsgToolProc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#ifdef  __DEBUG__
 __declspec(  dllexport  )	int  printHtmlEdit(  void  *  pCMyHtmlEditCtrl  )
{	
	CMyHtmlEditCtrl  *  pWnd  =  (  CMyHtmlEditCtrl  *  )pCMyHtmlEditCtrl;

	 CString				str;
	 IHTMLDocument2		*	pDoc		=	NULL;
	 IHTMLElement		*	pBody		=	NULL;
	 BOOL					bNothing	=	FALSE;
	
	 //  2008/10/25, 暂时关闭
	 //  return  0;

	 //
	 if  (  !pWnd  )  return  -1;

 	 if  (  SUCCEEDED(  pWnd->GetDocumentHTML(  str  )  )  )  {
	 	 traceLog(  _T(  "%s"  ),  str  );
	 }


	 if  (  !pWnd->GetDHtmlDocument(  &pDoc  )  )  goto  errLabel;

	 
	if  (  SUCCEEDED(  pDoc->get_body(  &pBody  )  )  )  {
		BSTR  bstr  =  NULL;
		if  (  SUCCEEDED(  pBody->get_innerText(  &bstr  )  )  )  {
			str  =  bstr;
			SysFreeString(  bstr  );
		}
		MACRO_CStringTrim(  str  );
		if  (  !str.GetLength(  )  )  bNothing  =  TRUE;
		
		if  (  SUCCEEDED(  pBody->get_innerHTML(  &bstr  )  )  )  {
			str  =  bstr;
			SysFreeString(  bstr  );
		}
		pBody->Release(  );
	}

	 //  myMessageBox(  str  );
	 //  traceLog(  _T(  "printHtmlEdit: %s"  ),  str  );
	OutputDebugString(  _T(  "printHtmlEdit: \n"  )  );
	OutputDebugString(  str  );
	OutputDebugString(  _T(  "\n"  )  );



errLabel:
	 return  0;
 }
#endif



IMPLEMENT_DYNCREATE(  CMyHtmlEditCtrl,  CHtmlEditCtrl  )

CMyHtmlEditCtrl::CMyHtmlEditCtrl(  )
{
	this->m_bInited			=  FALSE;
	//
	this->m_bDesignMode		=  FALSE;
	//	
	this->m_uiType			=  0;
	//
	this->m_bDisplayInited	=	FALSE; 

	//
	this->m_iWndContentType_hParent  =  0;
}

CMyHtmlEditCtrl::~CMyHtmlEditCtrl(  )
{
	traceLogA(  "~CMyHtmlEditCtrl(  )"  );
}

BOOL CMyHtmlEditCtrl::Create(LPCTSTR lpszWindowName, DWORD /*dwStyle*/, const RECT& rect, CWnd* pParentWnd,
						   int nID, CCreateContext *pContext) 
{
	BOOL			bRet			=	FALSE;
	//  IDropTarget	*	pIDropTarget	=	NULL;
	//  BOOL			bRegistered		=	FALSE;

	// create the control window

	//  AfxEnableControlContainer();
	if (CreateControl(CLSID_WebBrowser, lpszWindowName,
				WS_VISIBLE | WS_CHILD, rect, pParentWnd, nID))
	{
		//  if  (  !bRegisterDropWindow(  this->m_hWnd,  &pIDropTarget  )  )  goto  errLabel;
		//  bRegistered  =  TRUE;

		// in order to put the webbrowser in design mode, you must
		// first load a document into it. "about:blank" seems to
		// be the safest thing to load for a good starting point.
		CComQIPtr<IWebBrowser2> pBrowserApp = GetControlUnknown();
		ASSERT(pBrowserApp);
		if (pBrowserApp)
		{
			CComVariant vEmpty;
			LPCTSTR szDoc = GetStartDocument();
			if (szDoc)
			{
				CComBSTR bstrStart(szDoc);
				if (S_OK == pBrowserApp->Navigate(bstrStart, 
													&vEmpty,
													&vEmpty,
													&vEmpty,
													&vEmpty))
				{
					bRet = TRUE;
				}
			}
			else
				bRet = TRUE;

		}
	}

	
//  errLabel:
	if  (  !bRet  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "CMyHtmlEditCtrl:Create failed, to call destroyWindow"  )  );
		#endif

		//  if  (  bRegistered  )  UnregisterDropWindow(  this->m_hWnd,  pIDropTarget  );
		DestroyWindow(  );
	}
	if  (  bRet  )  {
		//  this->m_pIDropTarget  =  pIDropTarget;
	}
	return bRet;
}


LPCTSTR  CMyHtmlEditCtrl::GetStartDocument(  )
{
	traceLogA(  "CMyHtmlEditCtrl::GetStartDocument(  )"  );
	//  m_strHtmlAbout  =  CString(  "about:blank"  );
	//  return  m_strHtmlAbout;
	return  CHtmlEditCtrl::GetStartDocument(  );
}

BEGIN_MESSAGE_MAP(  CMyHtmlEditCtrl,  CHtmlEditCtrl  )
//	ON_WM_DROPFILES()
//ON_WM_LBUTTONDOWN()
//ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP(  );

BEGIN_EVENTSINK_MAP(  CMyHtmlEditCtrl,  CHtmlEditCtrl  )
	ON_EVENT_REFLECT(  CMyHtmlEditCtrl, 250 /* BeforeNavigate2 */, _OnBeforeNavigate2, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
	ON_EVENT_REFLECT(  CMyHtmlEditCtrl,  252/*  NavigateComplete2  */,  _OnNavigateComplete2,  VTS_DISPATCH  VTS_PVARIANT  )
END_EVENTSINK_MAP(  )





void CMyHtmlEditCtrl::_OnBeforeNavigate2(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Flags, VARIANT FAR* TargetFrameName, VARIANT FAR* PostData, VARIANT FAR* Headers, BOOL FAR* Cancel)
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	Flags; // unused
	TargetFrameName; // unused
	PostData; // unused
	Headers; // unused
	Cancel; // unused

	CString str(V_BSTR(URL));

	//  traceLogA(  "CMyHtmlEditCtrl::_OnBeforeNavigate2: enters, url is [%S]",  str.GetBuffer(  0  )  );

	if  (  this->m_bInited  )  {
		
		if  (  bQmInternalUrl(  str  )  )  {	//  内部的处理工作
			//  dlgTalk_procTask_htmlEdit(  this->GetParent(  )->m_hWnd,  this,  str  );
			dlgTalk_procTask_htmlEdit(  this->GetParent(  )->m_hWnd,  this->m_iWndContentType_hParent,  str  );
			}
		else  {		//  启动新IE来打开新的URL
			  ShellExecute(  NULL,  _T(  "open"  ),  str,  _T(  ""  ),  NULL,  SW_SHOW  );
		}

		*Cancel  =  TRUE;
	}

	//  CHtmlEditCtrl::_OnBeforeNavigate2( pDisp,  URL, Flags,  TargetFrameName,  PostData,  Headers, Cancel);

}



void  CMyHtmlEditCtrl::_OnNavigateComplete2(  LPDISPATCH  pDisp,  VARIANT  FAR  *  URL  )
{
	traceLogA(  "CMyHtmlEditCtrl::_OnNavigateComplete2"  );

	ASSERT(  V_VT(  URL  )  ==  VT_BSTR  );

	SetDesignMode(  this->m_bDesignMode  );

	if  (  !this->m_bInited  )  {
		::PostMessage(  GetParent(  )->m_hWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_idcInited,  (  LPARAM  )this->m_hWnd  );  
		this->m_bInited  =  TRUE;
	}

}

 int  procReturn(  LP_MyHtmlEditCtrl    pWnd  )
{
	IHTMLDocument2  *  pDoc	=	NULL;

	if  (  !pWnd->GetDHtmlDocument(  &pDoc  )  )  return  -1;

	IHTMLSelectionObject  *		pSelection			=	NULL;
	//  BOOL						bHtml				=	TRUE;
	//  WCHAR  *					wcpSelectedText		=	NULL;
	//  IHTMLEle
	CComBSTR					newHtml;

	if  (  SUCCEEDED(  pDoc->get_selection(  &pSelection  )  )  )  {
		
		IDispatch  *  pTxtRangeDisp  =  NULL;
		if  (  SUCCEEDED(  pSelection->createRange(  &pTxtRangeDisp  )  )  )  {

			IHTMLTxtRange  *  pRange  =  NULL;

			if  (  SUCCEEDED(  pTxtRangeDisp->QueryInterface(  IID_IHTMLTxtRange,  (  void  **  )&pRange  )  )  )  {
			
				newHtml.Empty(  );
				newHtml.Append(  "<br>"  );

				pRange->pasteHTML(  newHtml  );
		
				pRange->select(  );

				pRange->Release(  );
		
			}

			pTxtRangeDisp->Release(  );

		}
		
		pSelection->Release(  );
	}

	return  0;
}

 int  copyTxtToClipboard(  HWND  hWnd,  LPCTSTR  txt  )
 {
	 if  (  !txt  )  return  -1;
	 
	 CString  str  =  txt;

	if  (  OpenClipboard(  hWnd  )  )  {
			
		EmptyClipboard(  );

		HGLOBAL	hglb;
		int  cch  =  str.GetLength(  );
		hglb  =  GlobalAlloc(  GMEM_DDESHARE,  (  cch  +  1  )  *  sizeof(  TCHAR  )  );
		if  (  hglb  )  {
			LPTSTR  lpts  =  (  LPTSTR  )GlobalLock(  hglb  );
			if  (  lpts  )  {
				memcpy(  lpts,  str.GetBuffer(  0  ),  cch  *  sizeof(  TCHAR  )  );
				lpts[cch]  =  0;		
			}
			GlobalUnlock(  hglb  );
			//
			SetClipboardData(  CF_UNICODETEXT,  hglb  );	
		}		
	
		CloseClipboard(  );
	}

	return  0;
 }

 int  doCopy_htmlEdit(  LP_MyHtmlEditCtrl  p  )
 {					
	 IHTMLDocument2	*	pDoc	=	NULL;	
	 IHTMLElement	*	pIElem	=	NULL;
	 IHTMLSelectionObject *  selectionObject  =  NULL;
	 CString	str;
	
	 if  (  !p->GetDHtmlDocument(  &pDoc  )  )  goto  errLabel;
		
	 if  (  SUCCEEDED(  pDoc->get_selection(  &selectionObject  )  )  )  {	
		 IHTMLTxtRange  *  pRange;
		 BSTR  bstr;

		 if  (  SUCCEEDED(  selectionObject->createRange(  (  IDispatch  **  )&pRange  )  )  )  {										
			 if  (  SUCCEEDED(  pRange->get_text(  &bstr  )  )  )  {
				 str  =  bstr;						
				 SysFreeString(  bstr  );											
			 }
			 pRange->Release(  );						
		 }
		 selectionObject->Release(  );				
	 }
	 
	 copyTxtToClipboard(  p->m_hWnd,  str.GetBuffer(  0  )  );
				

errLabel:
	
	 return  0;

 }

  int  procRButtonDown(  LP_MyHtmlEditCtrl    p,  int  x,  int  y  )
{
#ifdef  __WINCE__
		return  -1;
#else
	CPoint				point(  x,  y  );
	CMenu				tmpMenu;
	CMenu			*	tmppPopupMenu		=		NULL;
	//
	int					nPos				=		CONST_resId_popup_htmlEdit;		//  2006/12/31
	//
	QY_MC			*	pQyMc				=		QY_GET_GBUF(  );
	QY_DMITEM		*	pItem;
	//
	unsigned  int		uCmd				=		0;

	//
	QNM_cusRes_moduleMem  *  pResMem  =  getCurCusResModuleMem(  &pQyMc->cusRes  );
	if  (  !pResMem  )  goto  errLabel;

	//
	ClientToScreen(  p->m_hWnd,  &point  );

	if  (  !(  tmpMenu.CreatePopupMenu(  )  )  )  goto  errLabel;
	if  (  !(  pItem  =  (  QY_DMITEM  *  )qyGetDesByType(  pResMem->pCusMenuTable,  CONST_resId_popupMenu  )  )  )  goto  errLabel;
	if  (  !(  pItem  =  qyGetDmItemByType(  pItem,  nPos,  sizeof(  QY_DMITEM  )  )  )  )  goto  errLabel;
	if  (	 makeDynaMenu(  &pQyMc->cusRes,  tmpMenu.m_hMenu,  (  QY_DMITEM  *  )pItem->pData,  NULL,  pQyMc,  NULL  )  )  goto  errLabel;
	tmppPopupMenu  = &tmpMenu;

	if (tmppPopupMenu == NULL)  goto  errLabel;

	
	if  (  p->m_uiType  !=  CONST_htmlEditType_input  )  {
		tmppPopupMenu->EnableMenuItem(  ID_qyPaste,  MF_BYCOMMAND  |  MF_GRAYED   );									   
	}

	uCmd  =  TrackPopupMenu(  tmppPopupMenu->m_hMenu,  TPM_RETURNCMD | TPM_LEFTALIGN | TPM_RIGHTBUTTON  |  TPM_NONOTIFY,  point.x, point.y, 0,  p->m_hWnd, NULL);

	traceLogA(  "procRButtonDown: uCmd %d",  uCmd  );

	switch  (  uCmd  )  {
			case  ID_qyCopy:
				  #if  0
				  keybd_event(  VK_CONTROL,  MapVirtualKey(  VK_CONTROL,  0  ),  KEYEVENTF_EXTENDEDKEY,  0  );
				  keybd_event(  (  'C'  ),  MapVirtualKey(  (  'C'  ),  0  ),  KEYEVENTF_EXTENDEDKEY,  0  );
				  keybd_event(  (  'C'  ),  MapVirtualKey(  (  'C'  ),  0  ),  KEYEVENTF_EXTENDEDKEY  |  KEYEVENTF_KEYUP,  0  );
				  keybd_event(  VK_CONTROL,  MapVirtualKey(  VK_CONTROL,  0  ),  KEYEVENTF_EXTENDEDKEY  |  KEYEVENTF_KEYUP,  0  );
				  #endif
				  				  	
				  doCopy_htmlEdit(  p  );

				  break;
			case  ID_qyPaste:
				  SetFocus(  p->m_hWnd  );
				  keybd_event(  VK_CONTROL,  MapVirtualKey(  VK_CONTROL,  0  ),  KEYEVENTF_EXTENDEDKEY,  0  );
				  keybd_event(  (  'V'  ),  MapVirtualKey(  (  'V'  ),  0  ),  KEYEVENTF_EXTENDEDKEY,  0  );
				  keybd_event(  (  'V'  ),  MapVirtualKey(  (  'V'  ),  0  ),  KEYEVENTF_EXTENDEDKEY  |  KEYEVENTF_KEYUP,  0  );
				  keybd_event(  VK_CONTROL,  MapVirtualKey(  VK_CONTROL,  0  ),  KEYEVENTF_EXTENDEDKEY  |  KEYEVENTF_KEYUP,  0  );
				  break;
			default:
					break;
	}

errLabel:
	 return  0;
#endif
}


BOOL CMyHtmlEditCtrl::PreTranslateMessage(MSG* pMsg)
 {
	 // TODO: Add your specialized code here and/or call the base class
	 if  (  this->m_uiType  ==  CONST_htmlEditType_input  )  {
		 if  (  pMsg->message  ==  WM_KEYDOWN  )  {
		 	 int  nVirtKey  =  (  int  )pMsg->wParam;
			 if  (  nVirtKey  ==  VK_RETURN  )  {
				 BOOL	bControl	=  FALSE;
				 SHORT	nState		=  GetKeyState(  VK_CONTROL  );
				 if  (  nState  &  0x8000  )  bControl  =  TRUE;

				 if  (  bControl  )  procReturn(   this  );
				 else  {
					   //  procTalkTo(  this->GetParent(  )->m_hWnd,  NULL  );
					   procTalkTo(  this->GetParent(  )->m_hWnd,  this->m_iWndContentType_hParent,  NULL  );
				 }

				 return  TRUE;
			 }
		 }
	 }
	 if  (  pMsg->message  ==  WM_RBUTTONDOWN  )  {
		 int	xPos,  yPos;

		 xPos = GET_X_LPARAM(pMsg->lParam); 
		 yPos = GET_Y_LPARAM(pMsg->lParam); 

		 procRButtonDown(  this,  xPos,  yPos  );

		 return  TRUE;
	 }
	 //  2013/09/19
	 if  (  pMsg->message  ==  WM_KEYDOWN  )  {
		 if  (  pMsg->wParam  ==  'C'  )  {
			 if  (  (GetKeyState(VK_CONTROL  )&0x8000  )  )  {
	 
				 traceLog(  _T(  "Ctrl-c"  )  );
				 doCopy_htmlEdit(  this  );

				 return  TRUE;	 
			 }
		 } 
	 }
	 //  2017/10/31
#if  0
	 if  (  pMsg->message  ==  WM_MOUSEMOVE  )  {
		 #ifdef  __DEBUG__
				 //traceLog(  _T(  "htmlEdit.mouseMove"  )  );
		 #endif
		 //				 
		 htmlEdit_proc_mouseMove(  this->GetParent(  )->m_hWnd,  this->m_iWndContentType_hParent  );
	 }
#endif

	 //
	 return CHtmlEditCtrl::PreTranslateMessage(pMsg);
 }

 CQyString  getCellId(  void  *  pIHTMLElement  )
{
	IHTMLElement  *  pCel	=	(  IHTMLElement  *  )pIHTMLElement;
	BSTR	bstr	=	NULL;
	CString	cellStr;

	if  (  SUCCEEDED(  pCel->get_id(  &bstr  )  )  )  {
		cellStr  =  bstr;
		SysFreeString(  bstr  );
	}
	return  CQyString(  cellStr  );
 }

 CQyString  getCellText(  void  *  pIHTMLElement  )
{
	IHTMLElement  *  pCel  =  (  IHTMLElement  *  )pIHTMLElement;
	BSTR	bstr	=	NULL;
	CString	cellStr;

	if  (  SUCCEEDED(  pCel->get_innerText(  &bstr  )  )  )  {
		cellStr  =  bstr;
		SysFreeString(  bstr  );
	}
	return  CQyString(  cellStr  );
 }


 CQyString  getIElemHtml(  void  *  pIHTMLElement  )
{
	IHTMLElement  *  pCel  =  (  IHTMLElement  *  )pIHTMLElement;
	BSTR	bstr	=	NULL;
	CString	cellStr;

	if  (  SUCCEEDED(  pCel->get_innerHTML(  &bstr  )  )  )  {
		cellStr  =  bstr;
		SysFreeString(  bstr  );
	}
	return  CQyString(  cellStr  );
 }


 int  insertCell(  void  *  pIHTMLTableRow,  int  i,  LPCTSTR  pCssTag,  LPCTSTR  tId,  LPCTSTR  pContent,  BOOL  bScrollIntoView,  TCHAR  *  tTxtBuf,  unsigned  int  tTxtBufCnt  )
{
	IHTMLTableRow  *  pIRow  =  (  IHTMLTableRow  *  )pIHTMLTableRow;
	 IDispatch			*	disCell			=	NULL;
	 IHTMLElement		*	cell_elem		=	NULL;
	 CString				str;

	 if  (  SUCCEEDED(  pIRow->insertCell(  i,  &disCell  )  )  )  {

		 if  (  SUCCEEDED(  disCell->QueryInterface(  IID_IHTMLElement,  (  void ** )&cell_elem  )  )  )  {

			 BSTR  bstr  =	NULL;

			 if  (  tId  )  {	//  2009/04/05
				 str  =  tId;
				 bstr  =  str.AllocSysString(  );
				 if  (  bstr  )  {
					 cell_elem->put_id(  bstr  );
					 SysFreeString(  bstr  );
				 }
			 }

			 if  (  pContent  )  {
				 str  =  pContent;
				 bstr  =  str.AllocSysString(  );
				 if  (  bstr  )  {
					 cell_elem->put_innerHTML(  bstr  );
					 SysFreeString(  bstr  );
				 }
			 }

			 /*
			 if  (  SUCCEEDED(  cell_elem->get_id(  &bstr  )  )  )  {
				 str  =  bstr;
				 SysFreeString(  bstr  );
			 }
			 */

			 //
			 IHTMLStyle	*	pStyle;
			 if  (  SUCCEEDED(  cell_elem->get_style(  (  IHTMLStyle  **  )&pStyle  )  &&  pStyle  )  )  {

				 str  =  DEFAULT_fontSize_talk;  
				 bstr  =  str.AllocSysString(  );
				 if  (  bstr  )  {
					 VARIANT	v;
					 //
					 v.vt  =  VT_BSTR;
					 v.bstrVal  =  bstr;
					 //					 
					 if  (  !SUCCEEDED(  pStyle->put_fontSize(  v  )  )  )  traceLogA(  "put_fontSize failed."  );
					 //
					 SysFreeString(  bstr  );
				 }


				 if  (  pCssTag  &&  pCssTag[0]  )  {

					 IHTMLStyle2	*	pStyle2;
					 if  (  SUCCEEDED(  pStyle->QueryInterface(  IID_IHTMLStyle2,  (  void  **  )&pStyle2  )  )  &&  pStyle2  )  {

						 str  =  _T(  "relative"  );
						 bstr  =  str.AllocSysString(  );
						 if  (  bstr  )  {
							 pStyle2->put_position(  bstr  );
							 SysFreeString(  bstr  );
						 }

						 if  (  SUCCEEDED(  pStyle2->get_position(  &bstr  )  )  &&  bstr  )  {
							 str  =  bstr;
							 SysFreeString(  bstr  );
						 }

						 pStyle2->Release(  );

					 }

					 //

					 if  (  !_tcsicmp(  _T(  CONST_cssTag1  ),  pCssTag  )  )  {
						 pStyle->put_pixelLeft(  10  );
						 }
					 else  if  (  !_tcsicmp(  _T(  CONST_cssTag2  ),  pCssTag  )  )  {
							   pStyle->put_pixelLeft(  20  );
				 	 }

					 str  =  CONST_paddingRight;
					 bstr  =  str.AllocSysString(  );
					 if  (  bstr  )  {
						 VARIANT	v;
						 //
						 v.vt  =  VT_BSTR;
						 v.bstrVal  =  bstr;
						 //					 
                         if  (  !SUCCEEDED(  pStyle->put_paddingRight(  v  )  )  )  traceLogA(  "put_paddingRight failed."  );
						 //
						 SysFreeString(  bstr  );
					 }

					 
				 }
				 
				 pStyle->Release(  );
		 
			 
			 }
			 
			 
			 if  (  SUCCEEDED(  cell_elem->get_outerHTML(  &bstr  )  )  )  {
				 str  =  bstr;
				 //  traceLogA(  "现在的htmlStr为%S",  str  );
				 SysFreeString(  bstr  );
			 }
			 
			 if  (  tTxtBuf  &&  tTxtBufCnt  )  {		//  2007/08/12, 将转换后的txt带出
                 str  =  getCellText(  cell_elem  );
				 lstrcpyn(  tTxtBuf,  str,  tTxtBufCnt  );
			 }


			 if  (  bScrollIntoView  )  {

			 	 VARIANT  varBool;
			 	 varBool.vt = VT_BOOL;
			 	 varBool.boolVal = FALSE;

				 cell_elem->scrollIntoView(  varBool  );
		
			 }

			 cell_elem->Release(  );							
		 }

		 disCell->Release(  );			
	 }

	 return  0;
}

 int  doRow(  void  *  pIHTMLTableRow,  PF_commonHandler  pf,  void  *  p0  )
{
	IHTMLTableRow  *  pIRow	=	(  IHTMLTableRow  *  )pIHTMLTableRow;
	IHTMLElementCollection	*	pCelColl	=	NULL;

	if  (  SUCCEEDED(  pIRow->get_cells(  &pCelColl  )  )  )  {
		long	count	=	0;

		pCelColl->get_length(  &count  );

		for  (  int  i  =  0;  i  <  count;  i  ++  )  {
			 VARIANT		var0	=	{	0,		};
			 VARIANT		varIndex	=	{	VT_UINT,	};
			 LPDISPATCH		pDisp		=	NULL;

			 varIndex.lVal  =  i;
			 if  (  SUCCEEDED(  pCelColl->item(  varIndex,  var0,  &pDisp  )  )  )  {
				 IHTMLElement	*	pElement	=	NULL;
				 if  (  SUCCEEDED(  pDisp->QueryInterface(  IID_IHTMLElement,  (  LPVOID  *  )&pElement  )  )  )  {
					 
					 CString	str;
					 //
					 //  str  =  getCellText(  pElement  );
					 str  =  getIElemHtml(  pElement  );
					 traceLogA(  "cel html is %S",  str  );

					 if  (  pf  )  pf(  p0,  (  void  *  )i,  (  void  *  )str.GetBuffer(  0  )  );

					 pElement->Release(  );
				 }
				 pDisp->Release(  );
			 }
		}



		pCelColl->Release(  );
	}
	return  0;
}

  int  doTable_print(  void  *  p0,  void  *  p1,  void  *  pIHTMLTable  )
{
	IHTMLTable  *  pTable	=	(  IHTMLTable  *  )pIHTMLTable;
	IHTMLElementCollection	*	pRowColl	=	NULL;

	if  (  SUCCEEDED(  pTable->get_rows(  &pRowColl  )  )  )  {
		long	rowCnt	=	0;
		if  (  SUCCEEDED(  pRowColl->get_length(  &rowCnt  )  )  )  {
			for  (  int  i  =  0;  i  <  rowCnt;  i  ++  )  {
				 VARIANT		vIndexRow	=	{  VT_UINT,	i,	};
				 VARIANT		var0		=	{  VT_I4,	0,	};
				 LPDISPATCH		pDisp		=	NULL;

				 vIndexRow.lVal  =  i;
				 if  (  SUCCEEDED(  pRowColl->item(  vIndexRow,  var0,  &pDisp  )  )  )  {
					 IHTMLElement	*	pElement	=	NULL;
					 if  (  SUCCEEDED(  pDisp->QueryInterface(  IID_IHTMLElement,  (  LPVOID  *  )&pElement  )  )  )  {
						 BSTR	bstrTagName;
						 CString	sTempTagName;

						 if  (  SUCCEEDED(  pElement->get_tagName(  &bstrTagName  )  )  )  {
							 sTempTagName  =  bstrTagName;
							 //
							 SysFreeString(  bstrTagName  );
						 }
						 pElement->Release(  );
					 }
					 //
					 IHTMLTableRow	*	pIRow	=	NULL;
					 if  (  SUCCEEDED(  pDisp->QueryInterface(  IID_IHTMLTableRow,  (  LPVOID  *  )&pIRow  )  )  )  {
						 doRow(  pIRow,  0,  0  );
						 pIRow->Release(  );
					 }
					 pDisp->Release(  );
				 }
			}
		}
		pRowColl->Release(  );
	}

	return  0;
 }

 int  getAbsolutePos(  IHTMLElement  *  pIElem,  long  *  plLeft,  long  *  plTop  )
{
	int				iErr	=	-1;
	IHTMLElement  *  p		=	NULL;
	IHTMLElement  *  p1		=	NULL;
	long			lLeft	=	0;
	long			lTop	=	0;  
	long			l;
	BOOL			bNeedRelease	=	FALSE;

	pIElem->get_offsetLeft(  &l  );
	lLeft  =  l;
	pIElem->get_offsetTop(  &l  );
	lTop  =  l;

	if  (  !SUCCEEDED(  pIElem->get_offsetParent(  &p1  )  )  ||  !p1  )  {
		p1  =  NULL;
		iErr  =  0;  goto  errLabel;
	}
	
	for  (  ;  ;  )  {
		 p1->get_offsetLeft(  &l  );  lLeft  +=  l;
		 p1->get_offsetTop(  &l  );  lTop  +=  l;

         if  (  !SUCCEEDED(  p1->get_offsetParent(  &p  )  )  ||  !p  )  break;
		 p1->Release(  );
		 p1  =  p;

	}
	
	iErr  =  0;

errLabel:

	if  (  p1  )  p1->Release(  );
	if  (  !iErr  )  {
		if  (  plLeft  )  *plLeft  =  lLeft;
		if  (  plTop  )  *plTop  =  lTop;
	}

	return  iErr;
}

  int  parseRowCol0(  int  i,  LPCTSTR  str,  int  *  piRowType  )
{
	int					iRowType	=	0;

	if  (  i  ==  0  )  {
		
		//  traceLogA(  "col0 is %S",  str  );

		TCHAR	*	pStr		=	_T(  "type="  );
		TCHAR	*	p			=	(  TCHAR  *  )_tcsstr(  str,  pStr  );
		if  (  p  )  {
			p  +=  lstrlen(  pStr  );
			iRowType  =  _ttol(  p  );
			
		}
	}

	if  (  piRowType  )  *piRowType  =  iRowType;

	return  0;
}

  int  getRowCol0FromIRow(  void  *  p0,  PARAM_PROC_ROW  *  pParam,  IHTMLTableRow  *  pIRow,  int  *piRowType,  int  *piTaskId  )
{
	 IDispatch					*	disCell			=	NULL;
	 CString						str;
	 IHTMLElementCollection		*	pCellColl		=	NULL;
	 VARIANT						varIndex,  var0;
	 int							iRowType		=	0;
	 int							iTaskId			=	0;
	 int							i;

	 if  (  !pParam  ||  !pIRow  )  return  -1;


	 if  (  SUCCEEDED(  pIRow->get_cells(  &pCellColl  )  )  )  {
		 
		 long  count  =  0;

		 pCellColl->get_length(  &count  );

		 i  =  0;
		 //
		 varIndex.vt  =  VT_UINT;
		 varIndex.lVal  =  i;
		 var0.vt  =  VT_UINT;
		 var0.ulVal  =  0;

		 if  (  SUCCEEDED(  pCellColl->item(  varIndex,  varIndex,  &disCell  )  )  &&  disCell  )  {    

			 IHTMLElement				*	cell_elem		=	NULL;

			 if  (  SUCCEEDED(  disCell->QueryInterface(  IID_IHTMLElement,  (  void ** )&cell_elem  )  )  )  {

				 BSTR		bstr  =  NULL;
				 
				 if  (  !i  )  {
					 str  =  getCellId(  cell_elem  );

					 parseRowCol0(  i,  str,  &iRowType  );
					 //
					 if  (  piRowType  )  *piRowType  =  iRowType;
				 }

				 cell_elem->Release(  );		
			 }

			 disCell->Release(  );
			
		 }


		 i  =  1;
		 //
		 varIndex.vt  =  VT_UINT;
		 varIndex.lVal  =  i;
		 //
		 if  (  SUCCEEDED(  pCellColl->item(  varIndex,  varIndex,  &disCell  )  )  &&  disCell  )  {    

			 IHTMLElement				*	cell_elem		=	NULL;

			 if  (  SUCCEEDED(  disCell->QueryInterface(  IID_IHTMLElement,  (  void ** )&cell_elem  )  )  )  {

				 BSTR		bstr	=	NULL;
				 TCHAR	*	pT		=	NULL;
				 
				 if  (  !i  )  {
					 str  =  getCellId(  cell_elem  );

					 iTaskId  =  _tcstol(  str,  &pT,  10  );
					 //
					 if  (  piTaskId  )  *piTaskId  =  iTaskId;
				 }

				 cell_elem->Release(  );		
			 }

			 disCell->Release(  );
			
		 }




		 pCellColl->Release(  );

	 }

	 return  0;
}

   //  
 static  int  activateRow(  void  *  p0,  PARAM_PROC_ROW  *  pParam,  IHTMLTableRow  *  pIRow  )
{
	
	 //  IDispatch					*	disCell			=	NULL;
	 //  IHTMLElement				*	cell_elem		=	NULL;
	 //  IHTMLElementCollection		*	pCellColl		=	NULL;
	 //  VARIANT						varIndex,  var0;
	 IHTMLElement				*	pIElem			=	NULL;
	 int							iRowType		=	0;


	 if  (  !pParam  ||  !pIRow  )  return  -1;

	 getRowCol0FromIRow(  0,  pParam,  pIRow,  &iRowType,  NULL  );

	 

	 if  (  SUCCEEDED(  pIRow->QueryInterface(  IID_IHTMLElement,  (  void  **  )&pIElem  )  )  &&  pIElem  )  {

		 if  (  iRowType  ==  CONST_rowType_content  )  {

		 IHTMLStyle	*	pStyle;
		 if  (  SUCCEEDED(  pIElem->get_style(  &pStyle  )  )  &&  pStyle  )  {
			 VARIANT	vColor;

			 vColor.vt  =  VT_I4;
			 vColor.lVal  =  pParam->lColor;
			 //
			 pStyle->put_backgroundColor(  vColor  );

			 pStyle->Release(  );
		 }

		 }


		 if  (  pParam->bScrollIntoView  )  {

			 long							rowTop,  rowHeight;
			 CString						str;
			 VARIANT						varBool;
			 long							lRowIndex;

			 getAbsolutePos(  pIElem,  NULL,  &rowTop  );
			 pIElem->get_offsetHeight(  &rowHeight  );
			 //
			 str  =  getIElemHtml(  pIElem  );
			 //
			 pIRow->get_rowIndex(  &lRowIndex  );

			 if  (  rowTop  <  pParam->scrollTop_body  )  {
				 
				 if  (  pParam->lRowIndex_top  ==  -1  ||  pParam->lRowIndex_top  >  lRowIndex  )  {
						 varBool.vt = VT_BOOL;
						 varBool.boolVal = TRUE;					//  滚到top

						 pIElem->scrollIntoView(  varBool  );
					 }
				}
			 else  if  (  rowTop  +  rowHeight  >  pParam->scrollTop_body  +  pParam->clientHeight_body  )  {
				       if  (  pParam->lRowIndex_bottom  ==  -1  ||  pParam->lRowIndex_bottom  <  lRowIndex  )  {
						   varBool.vt  =  VT_BOOL;
						   varBool.boolVal  =  FALSE;			//  底边可见
						
						   pIElem->scrollIntoView(  varBool  );
					   }
			 }	

			 if  (  pParam->lRowIndex_top  ==  -1  )  {
				 pParam->lRowIndex_top  =  lRowIndex;
				 pParam->lRowIndex_bottom  =  lRowIndex;
				}
			 else  {
				   if  (  pParam->lRowIndex_top  >  lRowIndex  )  pParam->lRowIndex_top  =  lRowIndex;
				   if  (  pParam->lRowIndex_bottom  <  lRowIndex  )  pParam->lRowIndex_bottom  =  lRowIndex;
			 }


		 }

		 pIElem->Release(  );
	 }


	 /*

	 if  (  SUCCEEDED(  pIRow->get_cells(  &pCellColl  )  )  )  {

		 varIndex.vt  =  VT_UINT;
		 varIndex.lVal  =  pParam->iCol;
		 var0.vt  =  VT_UINT;
		 var0.ulVal  =  0;

		 if  (  SUCCEEDED(  pCellColl->item(  varIndex,  varIndex,  &disCell  )  )  &&  disCell  )  {    

			 if  (  SUCCEEDED(  disCell->QueryInterface(  IID_IHTMLElement,  (  void ** )&cell_elem  )  )  )  {


				 IHTMLStyle	*	pStyle;
				 if  (  SUCCEEDED(  cell_elem->get_style(  &pStyle  )  )  &&  pStyle  )  {
					 VARIANT	vColor;

					 vColor.vt  =  VT_I4;
					 vColor.lVal  =  pParam->lColor;
					 //
					 pStyle->put_backgroundColor(  vColor  );

					 pStyle->Release(  );
				 }

				 if  (  pParam->bScrollIntoView  )  {

					 
					 VARIANT  varBool;
					 varBool.vt = VT_BOOL;
					 varBool.boolVal = TRUE;

					 cell_elem->scrollIntoView(  varBool  );
				 }

				 cell_elem->Release(  );		
			 }

			 disCell->Release(  );
			
		 }

		 pCellColl->Release(  );

	 }
	 */

//  errLabel:
	 return  0;
}


 __declspec(  dllexport  )  int  activateRowByRowId(  HWND  hDlgTalk,  LPCTSTR  rowIdStr  )
{
	//  CWnd  *  pDlg
	AFX_MANAGE_STATE(AfxGetStaticModuleState());


	CHelp_getDlgTalkVar		help_getDlgTalkVar;	
	DLG_TALK_var		*	pDlgTalkVar	=	NULL;
	
	pDlgTalkVar  =  (  DLG_TALK_var  *  )help_getDlgTalkVar.getVar(  hDlgTalk  );
	if  (  !pDlgTalkVar  )  return  -1;

	DLG_TALK_var	&	m_var	=	*(  DLG_TALK_var  *  )pDlgTalkVar;
	IHTMLDocument2	*	pDoc	=	NULL;
	PARAM_PROC_ROW		param;
	IHTMLElement	*	pIElem	=	NULL;
	
	//
	if  (  !IsWindow(  m_var.msgTool.hWnd_msgTool  )  )  return  -1;
	DLG_msgTool_var  *  pDlgMsgToolVar  =  (  DLG_msgTool_var  *  )getDlgMsgToolVar(  m_var.msgTool.hWnd_msgTool  );
	if  (  !pDlgMsgToolVar  )  return  -1;
	MSG_tool_common  &  msgToolCommon  =  pDlgMsgToolVar->msgToolCommon;

	//  2012/05/18
	if  (  !msgToolCommon.m_pHtmlEdit_recentMsgList  )  return  -1;

	//
	if  (  !msgToolCommon.m_pHtmlEdit_recentMsgList->GetDHtmlDocument(  &pDoc  )  )  return  -1;

	//  先把原来的激活单元的激活状态给取消了
	if  (  m_var.bCellActivated  )  {

		memset(  &param,  0,  sizeof(  param  )  );
		param.iCol  =  m_var.iCol_content;
		param.lColor  =  m_var.lColor_org;
		param.pf  =  (  PF_commonHandler  )activateRow;
		lstrcpyn(  param.rowIdStr,  m_var.rowIdStr_active,  mycountof(  param.rowIdStr  )  );

		doDoc(  pDoc,  (  PF_commonHandler  )doTable_byRowId,  0,  &param  );

		m_var.bCellActivated  =  FALSE;

	}
		 
	memset(  &param,  0, sizeof(  param  )  );
	//
	//  计算body的scrollTop和clientHeight
	if  (  SUCCEEDED(  pDoc->get_body(  &pIElem  )  )  &&  pIElem  )  {
		IHTMLElement2	*	pIElem2  =  NULL;
		long				l;

		if  (  SUCCEEDED(  pIElem->QueryInterface(  IID_IHTMLElement2,  (  void  **  )&pIElem2  )  )  )  {
			pIElem2->get_scrollTop(  &l  );		param.scrollTop_body  =  l;
			pIElem2->get_clientHeight(  &l  );	param.clientHeight_body  =  l;
			pIElem2->Release(  );
		}

		pIElem->Release(  );
	}
	//
	param.iCol  =  m_var.iCol_content;
	param.lColor  =  m_var.lColor_active;
	param.pf  =  (  PF_commonHandler  )activateRow;		
	lstrcpyn(  param.rowIdStr,  rowIdStr,  mycountof(  param.rowIdStr  )  );

	param.bScrollIntoView  =  TRUE;			
	param.lRowIndex_top  =  -1;
	param.lRowIndex_bottom  =  -1;
		
	doDoc(  pDoc,  (  PF_commonHandler  )doTable_byRowId,  0,  &param  );
	lstrcpyn(  m_var.rowIdStr_active,  param.rowIdStr,  mycountof(  param.rowIdStr  )  );
	m_var.bCellActivated  =  TRUE;

	return  0;
}


 __declspec(  dllexport  )  int  getlRowIndex(  void  *  p0,  void  *  pPARAM_PROC_ROW,  void  *  pIHTMLTableRow  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	PARAM_PROC_ROW	*	pParam	=	(  PARAM_PROC_ROW  *  )pPARAM_PROC_ROW;
	  IHTMLTableRow  *  pIRow	=	(  IHTMLTableRow  *  )pIHTMLTableRow;
	 IDispatch					*	disCell			=	NULL;
	 CString						str;
	 IHTMLElementCollection		*	pCellColl		=	NULL;
	 VARIANT						varIndex,  var0;
	 int							iRowType		=	0;

	 if  (  !pParam  ||  !pIRow  )  return  -1;


	 if  (  SUCCEEDED(  pIRow->get_cells(  &pCellColl  )  )  )  {
		 
		 long  count  =  0;

		 pCellColl->get_length(  &count  );

		 for  (  int  i  =  0;  i  <  count;  i  ++  )  {

			 //
			 varIndex.vt  =  VT_UINT;
			 varIndex.lVal  =  i;
			 var0.vt  =  VT_UINT;
			 var0.ulVal  =  0;

		 	 if  (  SUCCEEDED(  pCellColl->item(  varIndex,  varIndex,  &disCell  )  )  &&  disCell  )  {    

				 IHTMLElement				*	cell_elem		=	NULL;

				 if  (  SUCCEEDED(  disCell->QueryInterface(  IID_IHTMLElement,  (  void ** )&cell_elem  )  )  )  {

					 BSTR		bstr  =  NULL;
				 
					 if  (  !i  )  {
						 str  =  getCellText(  cell_elem  );
						 parseRowCol0(  i,  str,  &iRowType  );
					 }

					 if  (  iRowType  ==  CONST_rowType_who  )  pIRow->get_rowIndex(  &pParam->lRowIndex_who_gotByRowId  );
					 
					 cell_elem->Release(  );		
				 }

				 disCell->Release(  );
			
			 }

		 }

		 pCellColl->Release(  );

	 }

	 return  0;
}



 __declspec(  dllexport  )  int  modifyRow(  void  *  p0,  void  *  pPARAM_PROC_ROW,  void  *  pIHTMLTableRow  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	PARAM_PROC_ROW	*	pParam	=	(  PARAM_PROC_ROW  *  )pPARAM_PROC_ROW;

	IHTMLTableRow  *  pIRow	=	(  IHTMLTableRow  *  )pIHTMLTableRow;
	 IDispatch					*	disCell			=	NULL;
	 CString						str;
	 IHTMLElementCollection		*	pCellColl		=	NULL;
	 VARIANT						varIndex,  var0;
	 int							iRowType		=	0;

	 if  (  !pParam  ||  !pIRow  )  return  -1;


	 if  (  SUCCEEDED(  pIRow->get_cells(  &pCellColl  )  )  )  {
		 
		 long  count  =  0;

		 pCellColl->get_length(  &count  );

		 for  (  int  i  =  0;  i  <  count;  i  ++  )  {

			 //
			 varIndex.vt  =  VT_UINT;
			 varIndex.lVal  =  i;
			 var0.vt  =  VT_UINT;
			 var0.ulVal  =  0;

		 	 if  (  SUCCEEDED(  pCellColl->item(  varIndex,  varIndex,  &disCell  )  )  &&  disCell  )  {    

				 IHTMLElement				*	cell_elem		=	NULL;

				 if  (  SUCCEEDED(  disCell->QueryInterface(  IID_IHTMLElement,  (  void ** )&cell_elem  )  )  )  {

					 BSTR		bstr  =  NULL;
				 
					 if  (  !i  )  {
						 str  =  getCellId(  cell_elem  );
						 parseRowCol0(  i,  str,  &iRowType  );
					 }

					 if  (  iRowType  ==  CONST_rowType_who  )  pIRow->get_rowIndex(  &pParam->lRowIndex_who_gotByRowId  );

					 if  (  iRowType  ==  CONST_rowType_content  &&  i  ==  pParam->iCol  )  {
				 
						 if  (  SUCCEEDED(  cell_elem->get_innerHTML(  &bstr  )  )  )  {
							 str  =  bstr;
							 SysFreeString(  bstr  );
						 }

						 str  =  CString(  pParam->content  );
						 bstr  =  str.AllocSysString(  );
						 if  (  bstr  )  {
							 cell_elem->put_innerHTML(  bstr  );
							 SysFreeString(  bstr  );
						 }

						 IHTMLStyle  *  pStyle;
						 if  (  SUCCEEDED(  cell_elem->get_style(  &pStyle  )  )  )  {
							 str  =  CONST_paddingRight;
							 bstr  =  str.AllocSysString(  );
							 if  (  bstr  )  {
								 VARIANT	v;
								 //
								 v.vt  =  VT_BSTR;
								 v.bstrVal  =  bstr;
								 //					 
								 if  (  !SUCCEEDED(  pStyle->put_paddingRight(  v  )  )  )  traceLogA(  "put_paddingRight failed."  );
								 //
								 SysFreeString(  bstr  );
							 }

							 pStyle->Release(  );

						 }

					 }

					 cell_elem->Release(  );		
				 }

				 disCell->Release(  );
			
			 }

		 }

		 pCellColl->Release(  );

	 }

	 return  0;
}







int  makeRowCol0(  PARAM_PROC_ROW  *  pParam,  int  iRowType,  TCHAR  *  tBuf,  unsigned  int  size  )
{
	_sntprintf(  tBuf,  size,  _T(  "type=%u/bFol=%d"  ),  iRowType,  pParam->bFollowingRows  );

	return  0;
}

 int  doTable_insertRow(  void  *  p0,  PARAM_PROC_ROW  *  pParam,  IHTMLTable  *  pTable  )
{
	int					iErr								=	-1;
	TCHAR				tBuf[CONST_maxCnt_content]			=	_T(  ""  );
	IDispatch		*	disrow								=	NULL;
	HRESULT				hr;
	long				cols;
	BSTR				bstr								=	NULL;
	char				timeDisplayBuf[128]					=	"";
	int					iRowType							=	0;
	TCHAR			*	pTVerb								=	_T(  ""  );
	long				lRowIndex							=	-1;
	CString				cssTag;

	if  (  !pTable  )  return  -1;
	if  (  !bQyTimeValid(  pParam->timeBuf  )  )  return  -1;

	lRowIndex  =  pParam->lRowIndex;

	hr	=	pTable->get_cols(  &cols  );
	//  traceLogA(  "cols is %d",  cols  );
	if  (  !cols  )  goto  errLabel;
	
	if  (  pParam->usOp  ==  CONST_imOp_says
		||  pParam->usOp  ==  CONST_imOp_tryToSendFile  )  
	{

		//  先加入一行，描述： 谁，状态，状态发生时间
		iRowType  =  CONST_rowType_who;
		if  (  SUCCEEDED(  pTable->insertRow(  lRowIndex,  &disrow  )  )  )  {

			if  (  lRowIndex  !=  -1  )  lRowIndex  ++  ;
		
			IHTMLElement	*	pIElem	=	NULL;
			//
			if  (  SUCCEEDED(  disrow->QueryInterface(  IID_IHTMLElement,  (  void  **  )&pIElem  )  )  )  {
				BSTR		bstr	=	NULL;
				CString		str;
			
				//  traceLogA(  "这里是设置rowId"  );			
				str  =  CString(  pParam->rowIdStr  );
				if  (  (  bstr  =  str.AllocSysString(  )  )  )  {
					if  (  !SUCCEEDED(  pIElem->put_id(  bstr  )  )  )  traceLogA(  "set id failed"  );
					SysFreeString(  bstr  );
				}

				// 
				pIElem->Release(  );
			}

			IHTMLTableRow	*	pIRow	=	NULL;
			//
			if  (  SUCCEEDED(  disrow->QueryInterface(  IID_IHTMLTableRow,  (  void **  )&pIRow  )  )  )  {
				int					i;
				CString				str;

				str  =  CString(  "top"  );
				if  (  (  bstr  =  str.AllocSysString(  )  )  )  { 
					pIRow->put_vAlign(  bstr  );
					SysFreeString(  bstr  );
				}

				i  =  0;				
				makeRowCol0(  pParam,  iRowType,  tBuf,  mycountof(  tBuf  )  );
				insertCell(  pIRow,  i,  NULL,  tBuf,  NULL,  pParam->bScrollIntoView,  NULL,  0  );
				i  ++  ;			
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pParam->iTaskId  );
				insertCell(  pIRow,  i,  NULL,  tBuf,  NULL,  pParam->bScrollIntoView,  NULL,  0  );

				i  ++  ;
				//
				if  (  !pParam->bFollowingRows  )  cssTag  =  "";					
				else  cssTag  =  CONST_cssTag1;
				//
				qyDisplayTime(  pParam->timeBuf,  timeDisplayBuf,  mycountof(  timeDisplayBuf  )  );
				//  if  (  pParam->usOp  ==  CONST_imOp_says  )  pTVerb  =  _T(  "says"  );
				//
				{
					char		curTimeBuf[CONST_qyTimeLen  +  1]	=	"";
					char	*	pDisplayedStr						=	timeDisplayBuf;				//  2007/09/07，这里为了显示简洁，对当天的显示都只显示时分秒。
					//
                    getCurTime(  curTimeBuf  );
					if  (  !_strnicmp(  curTimeBuf,  pParam->timeBuf,  8  )  )  pDisplayedStr  =  timeDisplayBuf  +  11;
					//				
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s (%S): "  ),  (  pParam->talker[0]  ?  pParam->talker  :  _T(  "Stranger"  )  ),  pDisplayedStr  );
				}
				insertCell(  pIRow,  i,  cssTag,  NULL,  tBuf,  pParam->bScrollIntoView,  NULL,  0  );
				//

				pIRow->Release(  );

			}
		
			disrow->Release(  );

		}
		//  再加入聊天内容
		iRowType  =  CONST_rowType_content;
		if  (  SUCCEEDED(  pTable->insertRow(  lRowIndex,  &disrow  )  )  )  {

			if  (  lRowIndex  !=  -1  )  lRowIndex  ++  ;
		
			IHTMLElement	*	pIElem	=	NULL;
			//
			if  (  SUCCEEDED(  disrow->QueryInterface(  IID_IHTMLElement,  (  void  **  )&pIElem  )  )  )  {
				BSTR		bstr	=	NULL;
				CString		str;
			
				//  traceLogA(  "这里是设置rowId"  );
			
				str  =  CString(  pParam->rowIdStr  );
				if  (  (  bstr  =  str.AllocSysString(  )  )  )  {
					if  (  !SUCCEEDED(  pIElem->put_id(  bstr  )  )  )  traceLogA(  "set id failed"  );
					SysFreeString(  bstr  );
				}

				pIElem->Release(  );
			}

			IHTMLTableRow	*	pIRow	=	NULL;
			//
			if  (  SUCCEEDED(  disrow->QueryInterface(  IID_IHTMLTableRow,  (  void **  )&pIRow  )  )  )  {
				int					i;
				CString				str;
		
				str  =  CString(  "top"  );
				if  (  (  bstr  =  str.AllocSysString(  )  )  )  { 
					pIRow->put_vAlign(  bstr  );
					SysFreeString(  bstr  );
				}

				i  =  0;
				makeRowCol0(  pParam,  iRowType,  tBuf,  mycountof(  tBuf  )  );
				insertCell(  pIRow,  i,  NULL,  tBuf,  NULL,  pParam->bScrollIntoView,  NULL,  0  );
				i  ++  ;			
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pParam->iTaskId  );
				insertCell(  pIRow,  i,  NULL,  tBuf,  NULL,  pParam->bScrollIntoView,  NULL,  0  );

				i  ++  ;	//  内容
				//
				if  (  !pParam->bFollowingRows  )  cssTag  =  CONST_cssTag1;
				else  cssTag  =  CONST_cssTag2;
				//
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  pParam->content  );
				insertCell(  pIRow,  i,  cssTag,  NULL,  tBuf,  pParam->bScrollIntoView,  pParam->txtContent,  mycountof(  pParam->txtContent  )  );
				//

				pIRow->Release(  );

			}
		
			disrow->Release(  );

		}
	
		}
	else  if  (  pParam->usOp  ==  CONST_imOp_null  )  {		//  下面可以用来表明做一句话的描述
			
		      traceLogA(  "doTable_insertRow:"  );
			  //
			  iRowType  =  CONST_rowType_sendFile;
			  if  (  SUCCEEDED(  pTable->insertRow(  lRowIndex,  &disrow  )  )  )  {
		
				  if  (  lRowIndex  !=  -1  )  lRowIndex  ++  ;

				  IHTMLElement	*	pIElem	=	NULL;
				  //
				  if  (  SUCCEEDED(  disrow->QueryInterface(  IID_IHTMLElement,  (  void  **  )&pIElem  )  )  )  {
					  BSTR		bstr	=	NULL;
					  CString		str;
			
					  //  traceLogA(  "这里是设置rowId"  );
			
					  str  =  CString(  pParam->rowIdStr  );
					  if  (  (  bstr  =  str.AllocSysString(  )  )  )  {
						  if  (  !SUCCEEDED(  pIElem->put_id(  bstr  )  )  )  traceLogA(  "set id failed"  );
						  SysFreeString(  bstr  );
					  }

					  pIElem->Release(  );
				  }

				  IHTMLTableRow	*	pIRow	=	NULL;
				  //
				  if  (  SUCCEEDED(  disrow->QueryInterface(  IID_IHTMLTableRow,  (  void **  )&pIRow  )  )  )  {
					  int					i;
					  CString				str;
		
					  str  =  CString(  "top"  );
					  if  (  (  bstr  =  str.AllocSysString(  )  )  )  { 
						  pIRow->put_vAlign(  bstr  );
						  SysFreeString(  bstr  );
					  }

					  i  =  0;
					  makeRowCol0(  pParam,  iRowType,  tBuf,  mycountof(  tBuf  )  );
					  insertCell(  pIRow,  i,  NULL,  tBuf,  NULL,  pParam->bScrollIntoView,  NULL,  0  );
					  i  ++  ;			
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pParam->iTaskId  );
					  insertCell(  pIRow,  i,  NULL,  tBuf,  NULL,  pParam->bScrollIntoView,  NULL,  0  );
					  
					  i  ++  ;	//  描述
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s&nbsp;&nbsp;%s "  ),  (  pParam->talker[0]  ?  pParam->talker  :  _T(  "Stranger"  )  ),  pParam->content  );

					  insertCell(  pIRow,  i,  NULL,  NULL,  tBuf,  pParam->bScrollIntoView,  NULL,  0  );
					  //

					  pIRow->Release(  );
				  }
		
				  disrow->Release(  );
			  }
	
		}
	else  {
		  traceLogA(  "doTable_insertRow: imOp error"  );
		  goto  errLabel;
	}

	iErr  =  0;
errLabel:
	return  iErr;

}


//  插一次就够了
 int  doTable_insertRow_once(  void  *  p0,  PARAM_PROC_ROW  *  pParam,  void  *  pIHTMLTable  )
{	 
	IHTMLTable  *  pTable  =  (  IHTMLTable  *  )pIHTMLTable;
	int		iRet  =  doTable_insertRow(  p0,  pParam,  pTable  );
	return  iRet  ?  iRet  :  1;
}



					

 int  doTable_byRowId(  void  *  p0,  PARAM_PROC_ROW  *  pParam,  void  *  pIHTMLTable  )
{
	IHTMLTable				*	pTable		=	(  IHTMLTable  *  )pIHTMLTable;
	int							iErr		=	-1;
	IHTMLElementCollection	*	pRowColl	=	NULL;
	BSTR						bstr		=	NULL;
	CString						str;

	if  (  !pParam  )  return  -1;

	str  =  pParam->rowIdStr;
	bstr  =  str.AllocSysString(  );
	if  (  !bstr  )  goto  errLabel;

	if  (  SUCCEEDED(  pTable->get_rows(  &pRowColl  )  )  )  {
	
		long	rowCnt	=	0;
		if  (  SUCCEEDED(  pRowColl->get_length(  &rowCnt  )  )  )  {
			VARIANT			vIdStr;

			vIdStr.vt  =	VT_BSTR;
			vIdStr.bstrVal  = bstr;

			for  (  int  i  =  0;  i  <  rowCnt;  i  ++  )  {
				 VARIANT		vIndexRow	=	{  VT_UINT,	i,	};
				 LPDISPATCH		pDisp		=	NULL;

				 vIndexRow.lVal  =  i;
				 if  (  SUCCEEDED(  pRowColl->item(  vIdStr,  vIndexRow,  &pDisp  )  )  &&  pDisp  )  {
					 IHTMLElement	*	pElement	=	NULL;
					 if  (  SUCCEEDED(  pDisp->QueryInterface(  IID_IHTMLElement,  (  LPVOID  *  )&pElement  )  )  )  {
						 
						 BSTR		tmpBstr;
						 CString	tmpStr;
						 if  (  SUCCEEDED(  pElement->get_innerHTML(  &tmpBstr  )  )  )  {
							 tmpStr  =  tmpBstr;
							 SysFreeString(  tmpBstr  );
						 }

						 pElement->Release(  );
					 }

					 IHTMLTableRow  *  pIRow  =  NULL;
					 if  (  SUCCEEDED(  pDisp->QueryInterface(  IID_IHTMLTableRow,  (  LPVOID  *  )&pIRow  )  )  )  {

						 if  (  pParam->pf  )  pParam->pf(  p0,  pParam,  pIRow  );

						 pIRow->Release(  );
					 }

					 //
					 pDisp->Release(  );
				
				 }
				 
			}
		}
		pRowColl->Release(  );
	}

	iErr  =  0;

errLabel:

	if  (  bstr  )  SysFreeString(  bstr  );
	return  iErr;
}




 //  2007/07/13
 int  doTable_getLastRowIdStr(  void  *  p0,  PARAM_PROC_ROW  *  pParam,  void  *  pIHTMLTable  )
{
	IHTMLTable  *  pTable				=	(  IHTMLTable  *  )pIHTMLTable;
	IHTMLElementCollection	*	pColl	=	NULL;
	long						l		=	-1;						

	if  (  SUCCEEDED(  pTable->get_rows(  &pColl  )  )  &&  pColl  )  {
		
		if  (  SUCCEEDED(  pColl->get_length(  &l  )  )  &&  l  >  0  )  {

			VARIANT			vIndexRow	=	{  VT_UINT,	0,	};
			LPDISPATCH		pDisp		=	NULL;

			vIndexRow.lVal  =  l  -  1;				 
			if  (  SUCCEEDED(  pColl->item(  vIndexRow,  vIndexRow,  &pDisp  )  )  &&  pDisp  )  {
					
				IHTMLTableRow  *  pIRow  =  NULL;
				
				if  (  SUCCEEDED(  pDisp->QueryInterface(  IID_IHTMLTableRow,  (  LPVOID  *  )&pIRow  )  )  )  {

					//  if  (  pParam->pf  )  pParam->pf(  p0,  pParam,  pIRow  );

					IHTMLElement	*	pIElem	=	NULL;
					//
					if  (  SUCCEEDED(  pIRow->QueryInterface(  IID_IHTMLElement,  (  void  **  )&pIElem  )  )  )  {
						BSTR		bstr	=	NULL;
						CString		str;
			
						if  (  SUCCEEDED(  pIElem->get_id(  &bstr  )  )  )  {
							str  =  bstr;
							SysFreeString(  bstr  );
						}


						lstrcpyn(  pParam->rowIdStr,  str,  mycountof(  pParam->rowIdStr  )  );

						pIElem->Release(  );

					}


					pIRow->Release(  );
				}

				//
				pDisp->Release(  );
				

			}


		}	

		pColl->Release(  );
	}

	return  0;
}

 int  doDoc(  void  *  pIHtmlDocument2,  PF_commonHandler  pf_doTable,  void  *  p0,  void  *  pParam  )
{
	IHTMLDocument2			*  pDoc		=	(  IHTMLDocument2  *  )pIHtmlDocument2;
	IHTMLElementCollection  *  pColl	=  NULL;
	int							i;
	BOOL						bBreak	=	FALSE;

	//  pDoc->get

	if  (  SUCCEEDED(  pDoc->get_all(  &pColl  )  )  )  {
		long	cElems	=	0;

		if  (  SUCCEEDED(  pColl->get_length(  &cElems  )  )  )  {
			for  (  i  =  0;  i  <  cElems  &&  !bBreak;  i  ++  )  {
				 VARIANT 		vIndex	=	{	VT_I4,			};
				 VARIANT 		var2	=	{	VT_I4,	0,  	};
				 LPDISPATCH		pDisp	=	NULL;
				 //
				 vIndex.lVal  =  i;
				 if  (  SUCCEEDED(  pColl->item(  vIndex,  var2,  &pDisp  )  )  &&  pDisp  )  {
					 IHTMLTable  *  pTable  =  NULL;
					 //
					 if  (  SUCCEEDED(  pDisp->QueryInterface(  IID_IHTMLTable,  (  LPVOID  *  )&pTable  )  )  )  {
						 
						 //  doTable(  pTable  );
						 if  (  pf_doTable  &&  pf_doTable(  p0,  pParam,  pTable  )  )  bBreak  =  TRUE;

						 pTable->Release(  );
					 }
					 pDisp->Release(  );
				 }
			}

		}
		pColl->Release(  );
	}
	return  0;
 }

/////////


 ////////////////////
//
//



 BOOL  bQmInternalUrl(  LPCTSTR  url  )
{
	if  (  !url  )  return  FALSE;
	if  (  !_tcsnicmp(  url,  CONST_qmInternalUrl_root,  _tcslen(  CONST_qmInternalUrl_root  )  )  )  return  TRUE;
	return  FALSE;
}

 __declspec(  dllexport  )  int  parseQmInternalUrl(  LPCTSTR  url,  int  *  piTaskId,  TCHAR  *  rowIdStr,  unsigned  int  rowIdStrCnt,  unsigned  short  *  pusOp,  TCHAR  *  paramStr,  unsigned  int  paramStrCnt  )
{
	int			iErr				=	-1;
	TCHAR		taskIdStrBuf[32]	=	_T(  ""  );
	TCHAR		rowIdStrBuf[32]		=	_T(  ""  );
	TCHAR		opStrBuf[128]		=	_T(  ""  );
	TCHAR		paramStrBuf[128]	=	_T(  ""  );
	TCHAR	*	pT1,	*	pT2;

	if  (  !bQmInternalUrl(  url  )  )  return  -1;

	pT1		=  (  TCHAR  *  )url;
	pT1  +=  _tcslen(  CONST_qmInternalUrl_root  );
	pT2		=	_tcschr(  pT1,  _T(  '/'  )  );
	if  (  !pT2  )  goto  errLabel;
	lstrcpyn(  taskIdStrBuf,  pT1,  min(  pT2  -  pT1  +  1,  mycountof(  taskIdStrBuf  )  )  );
	//
	pT1  =  pT2  +  1;
	if  (  !pT1[0]  )  goto  errLabel;
	pT2  =  _tcschr(  pT1,  _T(  '/'  )  );
	if  (  !pT2  )  goto  errLabel;
	lstrcpyn(  rowIdStrBuf,  pT1,  min(  pT2  -  pT1  +  1,  mycountof(  rowIdStrBuf  )  )  );
	//
	pT1  =  pT2  +  1;
	if  (  !pT1[0]  )  goto  errLabel;
	pT2  =  _tcschr(  pT1,  _T(  '/'  )  );
	if  (  !pT2  )  goto  errLabel;
	lstrcpyn(  opStrBuf,  pT1,  min(  pT2  -  pT1  +  1,  mycountof(  opStrBuf  )  )  );
	//
	pT1  =  pT2  +  1;
	if  (  !pT1[0]  )  goto  errLabel;
	pT2  =  _tcsrchr(  pT1,  _T(  '/'  )  );
	if  (  !pT2  )  goto  errLabel;
	lstrcpyn(  paramStrBuf,  pT1,  min(  pT2  -  pT1  +  1,  mycountof(  paramStrBuf  )  )  );


	iErr  =  0;
errLabel:

	if  (  !iErr  )  {
		if  (  piTaskId  )  *piTaskId  =  _tcstol(  taskIdStrBuf,  &pT1,  10  );
        if  (  rowIdStr  )  lstrcpyn(  rowIdStr,  rowIdStrBuf,  rowIdStrCnt  );
		if  (  pusOp  )  *pusOp  =  (  unsigned  short  )_tcstol(  opStrBuf,  &pT1,  10  );
		if  (  paramStr  )  lstrcpyn(  paramStr,  paramStrBuf,  paramStrCnt  );
	}
	return  iErr;
}



#include	"DlgMsgTool.h"

  // 当pMsg不为空时，应该将txtContent赋上
// __declspec(  dllexport  )  int  addToRecentMsg(  HWND  hDlgTalk,  void  *  pDLG_TALK_var,  long  lRowIndex,  int  iTaskId,  MIS_MSG_TASK  * pMsgTask_unused,  QY_MESSENGER_ID  *  pIdInfo_talker,  LPCTSTR  talkerDesc,  unsigned  short  usOp,  int  iStatus,  char  *  timeBuf,  LPCTSTR  rowIdStr,  LPCTSTR  content,  BOOL  bFollowingRows,  BOOL  bScrollIntoView,  TCHAR  *  txtBuf,  unsigned  int  uiTxtBufCnt  )
 __declspec(dllexport)  int  addToRecentMsg(HWND  hDlgTalk, void* pDLG_TALK_var, long  lRowIndex, int  iTaskId, MIS_MSGU* pMsgU_unused, MIS_MSG_taskStatus* pMsgTaskStatus_unused, QY_MESSENGER_ID idInfo_talker, LPCTSTR  talkerDesc, unsigned  short  usOp, int  iStatus, char* timeBuf, LPCTSTR  rowIdStr, LPCTSTR  content, BOOL  bFollowingRows, BOOL  bScrollIntoView, TCHAR* txtBuf, unsigned  int  uiTxtBufCnt)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int							iErr		=	-1;
	DLG_TALK_var			*	pm_var		=	(  DLG_TALK_var  *  )pDLG_TALK_var;
	if  (  !pm_var  )  return  -1;
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return  -1;

	IHTMLDocument2		*	pDoc		=	NULL;
	PARAM_PROC_ROW			param;
	int						tmpiRet;
	MIS_CNT				*	pMisCnt		=	NULL;

	if  (  !hDlgTalk  )  return  -1;
	if  (  !pm_var  )  return  -1;
	//if  (  !pIdInfo_talker  )  return  -1;

	DLG_TALK_var  &  m_var  =  *pm_var;

	if  (  !(  pMisCnt  =  m_var.pMisCnt  )  )  goto  errLabel;

	//
	MSG_tool_common  *  pMsgToolCommon  =  NULL;

	if  (  !IsWindow(  m_var.msgTool.hWnd_msgTool  )  )  goto  errLabel;
	CDlgMsgTool  *  pDlgMsgTool  =  NULL;
	pDlgMsgTool  =  (  CDlgMsgTool  *  )CWnd::FromHandlePermanent(  m_var.msgTool.hWnd_msgTool  );
	if  (  !pDlgMsgTool  )  goto  errLabel;	
	//
	if  (  !pDlgMsgTool->m_var.guiData.bFinished_createCtrls  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "addToRecentMsg failed, bFinished_createCtrls is false"  )  );
		#endif
		goto  errLabel;
	}

	//
	pMsgToolCommon  =  &pDlgMsgTool->m_var.msgToolCommon;

	//
	if  (  !pMsgToolCommon  )  goto  errLabel;
	MSG_tool_common  &  msgToolCommon  =  *pMsgToolCommon;	//  m_var.msgToolCommon;


	//
	if  (  !msgToolCommon.m_pHtmlEdit_recentMsgList  )  goto  errLabel;

	if  (  !msgToolCommon.m_pHtmlEdit_recentMsgList->GetDHtmlDocument(  &pDoc  )  )  goto  errLabel;
	
	if  (  !content  )  content  =  _T(  ""  );


	memset(  &param,  0,  sizeof(  param  )  );
	param.lRowIndex  =  lRowIndex;
	param.iTaskId  =  iTaskId;
	param.idInfo_talker.ui64Id  =  idInfo_talker.ui64Id;
	if  (  talkerDesc  &&  talkerDesc[0]  )  lstrcpyn(  param.talker,  talkerDesc,  mycountof(  param.talker  )  );
	else  pFuncs->pf_getTalkerDesc(  idInfo_talker,  NULL,  0,  param.talker,  mycountof(  param.talker  )  );
	param.usOp  =  usOp;
	param.iStatus  =  iStatus;
	if  (  bQyTimeValid(  timeBuf  )  )  safeStrnCpy(  timeBuf,  param.timeBuf,  mycountof(  param.timeBuf  )  );
	else  getCurTime(  param.timeBuf  );
	
	if  (  rowIdStr  )  lstrcpyn(  param.rowIdStr,  rowIdStr,  mycountof(  param.rowIdStr  )  );

	lstrcpyn(  param.content,  content,  mycountof(  param.content  )  );

	param.bFollowingRows  =  bFollowingRows;
	param.bScrollIntoView  =  bScrollIntoView;

	tmpiRet  =  doDoc(  pDoc,  (  PF_commonHandler  )doTable_insertRow_once,  0,  &param  );
	if  (  tmpiRet  )  goto  errLabel;

	if  (  txtBuf  )  {
		lstrcpyn(  txtBuf,  param.txtContent,  uiTxtBufCnt  );
		//  traceLogA(  "这里要添加将消息内容记录日志的代码。打包送往schedulerQ, 在scheduler线程里记录数据库"  );
	}

	iErr  =  0;
errLabel:
	return  iErr;
}




 int  initHtmlDisplay(  void  *  pIHTMLDocument2,  CString  strInfo  )
{
#ifdef  __WINCE__
	return  -1;
#else

	IHTMLDocument2  *  pDoc			=	(  IHTMLDocument2  *  )pIHTMLDocument2;
	int					iErr		=	-1;
	VARIANT			*	pvParam		=	NULL;
	SAFEARRAY		*	sfArray		=	NULL;
	BSTR				bstr		=	NULL;

	bstr  =  strInfo.AllocSysString(  );
	if  (  !bstr  )  goto  errLabel;
						
	// Creates a new one-dimensional array
	sfArray = SafeArrayCreateVector(VT_VARIANT, 0, 1);	
	if  (  !sfArray  )  goto  errLabel;

	if  (  !SUCCEEDED(  SafeArrayAccessData(  sfArray,  (  LPVOID  *  )&pvParam  )  )  )  goto  errLabel;
	pvParam->vt = VT_BSTR;
	pvParam->bstrVal = (  BSTR  )bstr;
	if  (  !SUCCEEDED(  SafeArrayUnaccessData(  sfArray  )  )  )  goto  errLabel;

	if  (  !SUCCEEDED(  pDoc->write(  sfArray  )  )  )  goto  errLabel;

	iErr  =  0;

errLabel:

	if  (  sfArray  ) SafeArrayDestroy(  sfArray  );
	if  (  bstr  )  SysFreeString(  bstr  );

	return  iErr;
#endif
}


