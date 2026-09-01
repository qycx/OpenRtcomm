
#include	"stdafx.h"
#include	"qyCommon.h"
#include	"qyString.h"
//
#include	"qmStruct_defs.h"
//
#include	"qmUiFunc.h"
//
#include	"ctxQyMcTmpl.h"


//

//
#define CONST_str_selectExcelFormat \
    TEXT("Excel Files (*.xls)\0*.xls\0")\
    TEXT("Html Files (*.html)\0*.html\0\0")

//	#define		CONST_str_selectExcelFormat							_T(  "Excel format(*.xls)|*.xls|Html format(*.html)|*.html||"  )
#define		CONST_str_selectExportFilenameFormat				_T(  "Select export filename and format"  )


UINT_PTR CALLBACK OFN_hookProc (HWND  hWnd, UINT  uMsg, WPARAM  w, LPARAM  l  )
{
	switch  (  uMsg  )  {
			case  WM_NOTIFY:
				  LPNMHDR	hdr;  hdr  =  (  LPNMHDR  )l;
				  if  (  hdr  &&  hdr->code  ==  CDN_INITDONE  )  {
					#if  0  
					  HWND	hFileDlg  =  hWnd;
					  hFileDlg  =  GetParent(  hWnd  );
					  #if  defined(  __isCli__  )  ||  defined(  __APP_qyMc_touchscreen__  )					  
						  if  (  setModalWnd_func(  hFileDlg,  TRUE  )  )  {					  
							  PostMessage(  hFileDlg,  WM_CLOSE,  0,  0  );				  
						  }
					  #endif					  
					#endif
				  }
				  break;
			case  WM_INITDIALOG:  //  2016/09/17
				  {
					  OPENFILENAME  *  pOfn  =  (  OPENFILENAME  *  )l;
					  if  (  pOfn  )  {
						  CCtxQyMcTmpl  *  pQyMcTmpl  =  (  CCtxQyMcTmpl  *  )pOfn->lCustData;
						  if  (  pQyMcTmpl  )  {
							  //
							  HWND	hFileDlg  =  hWnd;
							  hFileDlg  =  GetParent(  hWnd  );
							  #if  defined(  __isCli__  )  ||  defined(  __APP_qyMc_touchscreen__  )					  
								  if  (  pQyMcTmpl->setModalWnd_func(  hFileDlg,  TRUE  )  )  {					  
									  PostMessage(  hFileDlg,  WM_CLOSE,  0,  0  );				  
								  }
							  #endif				
						  }
						  if  (  !pQyMcTmpl  )  {
							  #ifdef  __DEBUG__
									  //MACRO_qyAssert(  0,  _T(  "OFN_hookProc: pQyMcTmpl is null"  )  );
									  OutputDebugString(  _T(  "ERROR: OFN_hookProc: pQyMcTmpl is null\n"  )  );									  
							  #endif
						  }
					  }
				  }
				  break;
			default:
					break;
	}

	return  FALSE;
}


 //  __declspec(  dllexport  )  int  qyBrowseForFile(  HWND  hwndOwner,  BOOL bOpen,  LPCTSTR  lpszDefExt,  DWORD  dwFlags,  LPCTSTR  lpszFilter,  LPCTSTR  title,  LPCTSTR  initialFile,  CQyString  &  fileStr  )
__declspec(  dllexport  )  int  qyBrowseForFile(  HWND  hwndOwner,  BOOL bOpen,  LPCTSTR  lpszDefExt,  DWORD  dwFlags,  LPCTSTR  lpszFilter,  LPCTSTR  title,  LPCTSTR  initialFile,  CCtxQyMcTmpl  *  pQyMcTmpl,  CQyString  &  fileStr  )
{	 
	 CString				pathCStr;
	 TCHAR					tFileName[MAX_PATH]	=	_T(  ""  );
	 TCHAR					tTitle[128]			=	_T(  ""  );

#if  10
	 //  CFileDialog		dlg(  bOpen,  (  lpszDefExt  ?  lpszDefExt  :  _T(  "html"  )  ),  (  initialFile  ?  initialFile  :  _T(  ""  )  ),  dwFlags  ?  dwFlags  :  OFN_CREATEPROMPT  |  OFN_OVERWRITEPROMPT,  (  lpszFilter  ?  lpszFilter  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_selectExcelFormat  )  ),  NULL  );
	 OPENFILENAME			m_ofn;

	 if  (  initialFile  )  lstrcpyn(  tFileName,  initialFile,  mycountof(  tFileName  )  );

	 memset(  &m_ofn,  0,  sizeof(  m_ofn  )  );
	 m_ofn.lStructSize = sizeof(m_ofn);
	 m_ofn.hwndOwner  =  hwndOwner;		//  2012/04/11
	 m_ofn.lpstrFile  =  tFileName;
	 // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	 // use the contents of szFile to initialize itself.
	 m_ofn.lpstrFile[0] = '\0';  
	 m_ofn.nMaxFile = mycountof(tFileName);
	 m_ofn.lpstrFilter  =  (  lpszFilter  ?  lpszFilter  :  CONST_str_selectExcelFormat  );
	 m_ofn.nFilterIndex = 1;
	 safeTcsnCpy(  (  title  ?  title  :  CONST_str_selectExportFilenameFormat  ),  tTitle,  mycountof(  tTitle  )  );
	 m_ofn.lpstrTitle  =  tTitle;
	 m_ofn.nMaxFileTitle  =  mycountof(  tTitle  ); 
	 m_ofn.lpstrDefExt  =  lpszDefExt  ?  lpszDefExt  :  _T(  "html"  );
	 
	 //  2016/09/17
	 m_ofn.lCustData  =  (  LPARAM  )pQyMcTmpl;

	 //
	 m_ofn.Flags  |=  dwFlags  ?  dwFlags  :  OFN_CREATEPROMPT  |  OFN_OVERWRITEPROMPT;
	 	
	 m_ofn.Flags  |=  (  OFN_ENABLEHOOK  |  OFN_EXPLORER  );
	 m_ofn.lpfnHook  =  OFN_hookProc;

	 
	 if (GetOpenFileName(&m_ofn)==TRUE) {
		 pathCStr  =  m_ofn.lpstrFile;
	 }

#else

	 if  (  initialFile  )  lstrcpyn(  tFileName,  initialFile,  mycountof(  tFileName  )  );

	 lpszDefExt  =  lpszDefExt  ?  lpszDefExt  :  _T(  "html"  );
	 dwFlags  =  dwFlags  ?  dwFlags  :  OFN_CREATEPROMPT  |  OFN_OVERWRITEPROMPT;
	 lpszFilter  =  (  lpszFilter  ?  lpszFilter  :  CONST_str_selectExcelFormat  );
	 title  =  (  title  ?  title  :  CONST_str_selectExportFilenameFormat  );

	 CFileDialog		dlg(  bOpen,  lpszDefExt,  tFileName,  dwFlags,  lpszFilter,  CWnd::FromHandle(  hwndOwner  )  );
	 
	 //  2012/04/12.这里lpszFilter是个特殊串,需要重新设置下
	 dlg.m_ofn.lpstrFilter  =  (  lpszFilter  ?  lpszFilter  :  CONST_str_selectExcelFormat  );


	 if  (  IDOK  ==  dlg.DoModal(  )  )  {
		 pathCStr  =  dlg.GetPathName(  );
	 }

#endif


	 fileStr  =  pathCStr.GetBuffer(  0  );
	 return  pathCStr.GetLength(  )  ?  0  :  -1;
}


 //
 __declspec(  dllexport  )  int  qyBrowseForFile1(  HWND  hwndOwner,  BOOL bOpen,  LPCTSTR  lpszDefExt,  DWORD  dwFlags,  LPCTSTR  lpszFilter,  LPCTSTR  title,  LPCTSTR  initialFile,  CCtxQyMcTmpl  *  pQyMcTmpl,  TCHAR  *  fileStr,  unsigned  int  fileStrCnt  )
{	 
	 CString				pathCStr;
	 TCHAR					tFileName[MAX_PATH]	=	_T(  ""  );
	 TCHAR					tTitle[128]			=	_T(  ""  );

#if  10
	 //  CFileDialog		dlg(  bOpen,  (  lpszDefExt  ?  lpszDefExt  :  _T(  "html"  )  ),  (  initialFile  ?  initialFile  :  _T(  ""  )  ),  dwFlags  ?  dwFlags  :  OFN_CREATEPROMPT  |  OFN_OVERWRITEPROMPT,  (  lpszFilter  ?  lpszFilter  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_selectExcelFormat  )  ),  NULL  );
	 OPENFILENAME			m_ofn;

	 if  (  initialFile  )  lstrcpyn(  tFileName,  initialFile,  mycountof(  tFileName  )  );

	 memset(  &m_ofn,  0,  sizeof(  m_ofn  )  );
	 m_ofn.lStructSize = sizeof(m_ofn);
	 m_ofn.hwndOwner  =  hwndOwner;		//  2012/04/11
	 m_ofn.lpstrFile  =  tFileName;
	 // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	 // use the contents of szFile to initialize itself.
	 m_ofn.lpstrFile[0] = '\0';  
	 m_ofn.nMaxFile = mycountof(tFileName);
	 m_ofn.lpstrFilter  =  (  lpszFilter  ?  lpszFilter  :  CONST_str_selectExcelFormat  );
	 m_ofn.nFilterIndex = 1;
	 safeTcsnCpy(  (  title  ?  title  :  CONST_str_selectExportFilenameFormat  ),  tTitle,  mycountof(  tTitle  )  );
	 m_ofn.lpstrTitle  =  tTitle;
	 m_ofn.nMaxFileTitle  =  mycountof(  tTitle  ); 
	 m_ofn.lpstrDefExt  =  lpszDefExt  ?  lpszDefExt  :  _T(  "html"  );
	 
	 //  2016/09/17
	 m_ofn.lCustData  =  (  LPARAM  )pQyMcTmpl;

	 //
	 m_ofn.Flags  |=  dwFlags  ?  dwFlags  :  OFN_CREATEPROMPT  |  OFN_OVERWRITEPROMPT;
	 	
	 m_ofn.Flags  |=  (  OFN_ENABLEHOOK  |  OFN_EXPLORER  );
	 m_ofn.lpfnHook  =  OFN_hookProc;

	 
	 if (GetOpenFileName(&m_ofn)==TRUE) {
		 pathCStr  =  m_ofn.lpstrFile;
	 }

#else

	 if  (  initialFile  )  lstrcpyn(  tFileName,  initialFile,  mycountof(  tFileName  )  );

	 lpszDefExt  =  lpszDefExt  ?  lpszDefExt  :  _T(  "html"  );
	 dwFlags  =  dwFlags  ?  dwFlags  :  OFN_CREATEPROMPT  |  OFN_OVERWRITEPROMPT;
	 lpszFilter  =  (  lpszFilter  ?  lpszFilter  :  CONST_str_selectExcelFormat  );
	 title  =  (  title  ?  title  :  CONST_str_selectExportFilenameFormat  );

	 CFileDialog		dlg(  bOpen,  lpszDefExt,  tFileName,  dwFlags,  lpszFilter,  CWnd::FromHandle(  hwndOwner  )  );
	 
	 //  2012/04/12.这里lpszFilter是个特殊串,需要重新设置下
	 dlg.m_ofn.lpstrFilter  =  (  lpszFilter  ?  lpszFilter  :  CONST_str_selectExcelFormat  );


	 if  (  IDOK  ==  dlg.DoModal(  )  )  {
		 pathCStr  =  dlg.GetPathName(  );
	 }

#endif

#if  0

	 fileStr  =  pathCStr.GetBuffer(  0  );
	 return  pathCStr.GetLength(  )  ?  0  :  -1;
#endif
	 safeTcsnCpy(  pathCStr.GetBuffer(  0  ),  fileStr,  fileStrCnt  );
	 return  pathCStr.GetLength(  )  ?  0  :  -1;
}


 //
  static  TCHAR  stInitialDir[MAX_PATH];
  
 INT CALLBACK BrowseCallbackProc(HWND hwnd, 
                                UINT uMsg,
                                LPARAM lp, 
                                LPARAM pData) 
{
   TCHAR szDir[MAX_PATH];   
   
   switch  (  uMsg  )  {
		   case  BFFM_INITIALIZED: 
			     lstrcpyn(  szDir,  stInitialDir,  mycountof(  szDir  )  );
				 //  WParam is TRUE since you are passing a path.
         		 // It would be FALSE if you were passing a pidl.
         		 SendMessage(hwnd, BFFM_SETSELECTION, TRUE, (LPARAM)szDir);
   				 break;   
		   case  BFFM_SELCHANGED: 
			     // Set the status window to the currently selected path.
			     if  (  SHGetPathFromIDList(  (  LPITEMIDLIST  )lp,  szDir  )  )  {
					 SendMessage(  hwnd,  BFFM_SETSTATUSTEXT,  0,  (  LPARAM  )szDir  );
      			 }
      			 break;
   
   }

   return  0;
}

 int  qyBrowseForDir(  HWND  hwndOwner,  LPCTSTR  title,  LPCTSTR  initialDir,  CQyString  &  dirStr  )
{
	 BROWSEINFO			bi  =  {  0  };
 	 TCHAR				path[MAX_PATH]	=	_T(  ""  );

	 bi.hwndOwner  =  hwndOwner;	//  2012/04/11
	 bi.ulFlags  =  BIF_RETURNONLYFSDIRS  |  BIF_STATUSTEXT;
	 bi.lpszTitle  =  title  ?  title  :  _T(  ""  );
	 //  bi.pszDisplayName;
	 
	 if  (  !initialDir  )  stInitialDir[0]  =  0;
	 else  {  
		   lstrcpyn(  stInitialDir,  initialDir,  mycountof(  stInitialDir  )  );
		   bi.lpfn = BrowseCallbackProc; 
	 }
	 
	 LPITEMIDLIST  pidl  =  SHBrowseForFolder(  &bi  );
	 if  (  pidl  !=  0  )  {
		 // get the name of the folder
		 if  (  SHGetPathFromIDList(  pidl,  path  )  )  {
			 traceLogA(  "Selected Folder: %s",  path  );
		 }

		 // free memory used
		 IMalloc  *  imalloc  =  0;
		 if  (  SUCCEEDED(  SHGetMalloc(  &imalloc  )  )  )  {
			 imalloc->Free(  pidl  );
			 imalloc->Release(  );
		 }
	 }

	 dirStr  =  path;
	 return  path[0]  ?  0  :  -1;
}

