// DlgMediaControl.cpp : implementation file
//

#include	"stdafx.h"

#include	<strmif.h>

#include	<mmsystem.h>

#include	<dbt.h>
#include	<mmreg.h>
#include	<msacm.h>
#include	<fcntl.h>
#include	<io.h>
#include	<stdio.h>
#include	<commdlg.h>
#include	<strsafe.h>

#include	<dshow.h>

#pragma include_alias( "dxtrans.h", "myqedit.h" )
#define __IDxtCompositor_INTERFACE_DEFINED__
#define __IDxtAlphaSetter_INTERFACE_DEFINED__
#define __IDxtJpeg_INTERFACE_DEFINED__
#define __IDxtKey_INTERFACE_DEFINED__
//  #include	<Qedit.h>
#include	<myQedit.h>
#include	<Mediaobj.h>
#include	<Dmo.h>


#include	"qyMcMainCommon.h"
//  #include	"qyMc.h"
#include	"myresource.h"
//  #include	"dlgVideos.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"
#include	"qmcDmoPublic.h"
#include	"qyCusResTemp.h"

#include	"qmcVideoCapture_dx.h"
#include	"qmcShareMediaFile.h"
#include	"qmcCmdProc.h"
#include	"DlgMediaControl.h"

//#include	"qmshell_open.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define		MACRO_setBtnPlayText(  )  {		\
									QY_MC	*	pQyMc	=	QY_GET_GBUF(  );	\
									MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );	\
									FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );	\
									if  (  pFuncs  )  {													\
										void	**  pp  =  get_ppShareMediaFile(  );  \
										if  (  pp  )  {		\
											int			state;	\
											state  =  (  *pp  ?  pFuncs->pf_getShareMediaFileState(  *pp  )  :  m_var.pShmCmd->psCurrent  );	\
											if  (  state  ==  State_Running  )  SetDlgItemText(  IDC_BUTTON_PLAY,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_pause  )  );	\
											else  SetDlgItemText(  IDC_BUTTON_PLAY,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_play  )  );	\
										}  }  }

QY_DMITEM	CONST_mediaTypeTable[] = {
      {	0,	TEXT("*.qt\0"),   TEXT("QuickTime video\0") },
      {	0,	TEXT("*.mov\0"),  TEXT("QuickTime video\0") },
      {	0,	TEXT("*.avi\0"),  TEXT("AVI video\0")    },
      {	0,	TEXT("*.mpg\0"),  TEXT("MPEG video\0")   },
      {	0,	TEXT("*.mpe*\0"), TEXT("MPEG video\0")   },  /* MPE, MPEG */
      {	0,	TEXT("*.m1v\0"),  TEXT("MPEG video\0")   },  /* MPEG-1 video */
      {	0,	TEXT("*.wav\0"),  TEXT("WAV audio\0")    },
      {	0,	TEXT("*.au\0"),   TEXT("AU audio\0")     },
      {	0,	TEXT("*.aif*\0"), TEXT("AIFF audio\0")   },  /* AIF, AIFF, AIFC */
      {	0,	TEXT("*.snd\0"),  TEXT("SND audio\0")    },
      {	0,	TEXT("*.mpa\0"),  TEXT("MPEG audio\0")   },  /* MPEG audio */
      {	0,	TEXT("*.mp1\0"),  TEXT("MPEG audio\0")   },  /* MPEG audio */
      {	0,	TEXT("*.mp2\0"),  TEXT("MPEG audio\0")   },  /* MPEG audio */
      {	0,	TEXT("*.mid\0"),  TEXT("MIDI\0")         },  /* MIDI       */
      {	0,	TEXT("*.midi\0"), TEXT("MIDI\0")         },  /* MIDI       */
      {	0,	TEXT("*.rmi\0"),  TEXT("MIDI\0")         },  /* MIDI       */
      {	0,	TEXT("*.asf\0"),  TEXT("ASF Video\0")       },  /* Advanced Streaming */
      {	0,	TEXT("*.wma\0"),  TEXT("Windows Audio\0")   },  /* Windows Media Audio */
      {	0,	TEXT("*.mp3\0"),  TEXT("MP3 audio\0")       },  /* MPEG-1 Layer III */
      {	0,	TEXT("*.wmv\0"),  TEXT("Windows Video\0")   },  /* Windows Media Video */
      {	0,	TEXT("*.dat\0"),  TEXT("Video CD\0")     },  /* Video CD format */
	  {	-1,		},
};


// CDlgMediaControl dialog

IMPLEMENT_DYNAMIC(CDlgMediaControl, CDialog)

CDlgMediaControl::CDlgMediaControl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMediaControl::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	m_var.m_pParent  =  pParent;
}

CDlgMediaControl::~CDlgMediaControl()
{
}


BOOL CDlgMediaControl::Create(const RECT& rect)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL						bRet		=	FALSE;
	
	if  (  !m_var.m_pParent  )  goto  errLabel;

	if  (  !CDialog::Create(  this->IDD,  m_var.m_pParent  )  )  goto  errLabel;

	//
	m_var.bCreated  =  TRUE;

	bRet  =  TRUE;
errLabel:
	return  bRet;
}

void  **  CDlgMediaControl::get_ppShareMediaFile(  )
{
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

#if  0
	if  (  isQmCmd(  )  )  {
		MC_VAR_qmCmd	*	pProcInfo	=	(  MC_VAR_qmCmd  *  )m_var.pProcInfo;
		return  &pProcInfo->pShareMediaFile;
	}
#endif

	MC_VAR_isCli	*	pProcInfo	=	(  MC_VAR_isCli  *  )m_var.pProcInfo;
	CAP_procInfo_mediaFileBmp	*	pCapBmp;
	QY_SHARED_OBJ				*	pSharedObj;

	pCapBmp	=	(  CAP_procInfo_mediaFileBmp  *  )getCapBmpBySth(  pProcInfo,  m_var.iIndex_capBmp,  CONST_capType_mediaFile  );
	if  (  !pCapBmp  )  goto  errLabel;

	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pCapBmp->iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;

	return  &pSharedObj->pShareMediaObj;

errLabel:
	return  NULL;
}


 BOOL CDlgMediaControl::CanStep(void)
{
    HRESULT hr;
	void  **  pp  =  get_ppShareMediaFile(  );
	if  (  !pp  )  return  FALSE;
	SHARE_MEDIA_FILE	*	pShareMediaFile  =  (  SHARE_MEDIA_FILE  *  )*pp;
	if  (  !pShareMediaFile  )  return  FALSE;

	if  (  !pShareMediaFile->m_pFS  )  return  FALSE;

    // Check if this decoder can step
    hr = pShareMediaFile->m_pFS->CanStep(0L, NULL);


    if (hr == S_OK)
        return TRUE;
    else
        return FALSE;
}


 void CDlgMediaControl::ConfigureSeekbar()
{
    // Disable seekbar for new file and reset tracker/position label
	IMediaSeeking	*	pMS	=	NULL;
	void  **  pp  =  get_ppShareMediaFile(  );
	if  (  !pp  )  return;
	SHARE_MEDIA_FILE	*	pShareMediaFile  =  (  SHARE_MEDIA_FILE  *  )*pp;
	if  (  !pShareMediaFile  )  return;
	pMS  =  pShareMediaFile->m_pMS;

    m_Seekbar.SetPos(0);
	SetDlgItemText(  IDC_STATIC_POSITION,  TEXT("00m:00s\0"));
    m_var.g_rtTotalTime=0;

    // If we can't read the file's duration, disable the seek bar
    if (pMS && SUCCEEDED(pMS->GetDuration(&m_var.g_rtTotalTime)))
        m_Seekbar.EnableWindow(TRUE);
    else
        m_Seekbar.EnableWindow(FALSE);
}


 void  CDlgMediaControl::StartSeekTimer()
{
    // Cancel any pending timer event
    StopSeekTimer();

    // Create a new timer
    m_var.wTimerID = SetTimer(  1, 1000, NULL  );

	return;
}

 void  CDlgMediaControl::StopSeekTimer()
{
	if  (  m_var.wTimerID  )  {
        KillTimer(  m_var.wTimerID  );
        m_var.wTimerID  =  0;
    }

	return;
}

 void  CDlgMediaControl::ReadMediaPosition(  )
{
    HRESULT hr;
    REFERENCE_TIME rtNow;
	IMediaSeeking	*	pMS	=	NULL;
	void  **pp  =  get_ppShareMediaFile(  );
	if  (  !pp  )  return;  
	SHARE_MEDIA_FILE	*	pShareMediaFile  =  (  SHARE_MEDIA_FILE  *  )*pp;
	if  (  !pShareMediaFile  )  return;
	pMS  =  pShareMediaFile->m_pMS;

    if (!pMS)
        return;

    // Read the current stream position
    hr = pMS->GetCurrentPosition(&rtNow);
    if (FAILED(hr))
        return;

 
	
	// Convert position into a percentage value and update slider position
    if  (  m_var.g_rtTotalTime != 0  )  {
        long lTick = (long)((rtNow * 100) / m_var.g_rtTotalTime);
        m_Seekbar.SetPos(lTick);
		}
    else
        m_Seekbar.SetPos(0);

    // Update the 'current position' string on the main dialog
    UpdatePosition(rtNow);
	

}


 void  CDlgMediaControl::UpdatePosition(REFERENCE_TIME rtNow)
{
    HRESULT hr;
	void    **  pp  =  get_ppShareMediaFile(  );
	if  (  !pp  )  return;
	SHARE_MEDIA_FILE	*	pShareMediaFile  =  (  SHARE_MEDIA_FILE  *  )*pp;
	if  (  !pShareMediaFile  )  return;
	IMediaSeeking	*	pMS	=	NULL;
	pMS  =  pShareMediaFile->m_pMS;

    if  (  !pMS  )  return;

    // If no reference time was passed in, read the current position
    if (rtNow == 0)
    {
        // Read the current stream position
        hr = pMS->GetCurrentPosition(&rtNow);
        if (FAILED(hr))
            return;
    }
	if  (  m_var.g_rtTotalTime  <  rtNow  )  return;

    // Convert the LONGLONG duration into human-readable format
    unsigned long nTotalMS = (unsigned long) (  m_var.g_rtTotalTime  -  rtNow  ) / 10000; // 100ns -> ms
    int nSeconds = nTotalMS / 1000;
    int nMinutes = nSeconds / 60;
    nSeconds %= 60;

    // Update the display
    TCHAR szPosition[24], szCurrentString[24];
    hr = StringCchPrintf(szPosition, NUMELMS(szPosition), _T("%02dm:%02ds\0"), nMinutes, nSeconds);

    // Read current string and compare to the new string.  To prevent flicker,
    // don't update this label unless the string has changed.
	GetDlgItemText(  IDC_STATIC_POSITION,  szCurrentString,  mycountof(  szCurrentString  )  );

    if (_tcscmp(szCurrentString, szPosition))
		SetDlgItemText(  IDC_STATIC_POSITION,  szPosition);
}

void  CDlgMediaControl::HandleTrackbar(WPARAM wReq)
{
    HRESULT hr;
	void  **  pp  =  get_ppShareMediaFile(  );
	if  (  !pp  )  return;
	SHARE_MEDIA_FILE	*	pShareMediaFile  =  (  SHARE_MEDIA_FILE  *  )*pp;
	if  (  !pShareMediaFile  )  return;
	IMediaSeeking	*	pMS	=	NULL;
	IMediaControl	*	pMC	=	NULL;
	pMS  =  pShareMediaFile->m_pMS;
	pMC  =  pShareMediaFile->m_pMC;

    static OAFilterState state;
    static BOOL bStartOfScroll = TRUE;

    if ((!pMS) || (!pMC))
        return;

    // If the file is not seekable, the trackbar is disabled.
    DWORD dwPosition = m_Seekbar.GetPos();

    // Pause when the scroll action begins.
    if (bStartOfScroll)
    {
        hr = pMC->GetState(10, &state);
        bStartOfScroll = FALSE;
        hr = pMC->Pause();
    }

    // Update the position continuously.
    REFERENCE_TIME rtNew = (m_var.g_rtTotalTime * dwPosition) / 100;

    hr = pMS->SetPositions(&rtNew, AM_SEEKING_AbsolutePositioning,
                           NULL,   AM_SEEKING_NoPositioning);

    // Restore the state at the end.
    if (wReq == TB_ENDTRACK)
    {
        if (state == State_Stopped)
            hr = pMC->Stop();
        else if (state == State_Running)
            hr = pMC->Run();

        bStartOfScroll = TRUE;
    }

    // Update the 'current position' string on the main dialog.
    UpdatePosition(rtNew);

	MACRO_setBtnPlayText(  );
}


 void CDlgMediaControl::FillFileList(LPTSTR pszRootDir)
{
    UINT	attr = 0;
	TCHAR	tOldPath[MAX_PATH]	=	_T(  ""  );

	GetCurrentDirectory(mycountof(  tOldPath  ), tOldPath  );

    m_ListFiles.ResetContent();

    ::SetCurrentDirectory(pszRootDir);
    //  Say(TEXT("Building file list..."));

    // Add all of our known supported media types to the file list.
    // Add files of each type in order.
	QY_DMITEM  *  pItem;
	for (  pItem  =  CONST_mediaTypeTable; pItem->type  !=  -1; pItem  ++  )
    {
		m_ListFiles.Dir(  attr, pItem->des  );
    }
    traceLogA(("File list complete."));

    // Update list box title with number of items added
    int nItems  = m_ListFiles.GetCount();
    TCHAR szTitle[64];
    (void)StringCchPrintf(szTitle, NUMELMS(szTitle), TEXT("Media files (%d found)\0"), nItems);
    //  m_StrFileList.SetWindowText(szTitle);

	m_var.m_nCurrentFileSelection = -1;     // No selection yet

	::SetCurrentDirectory( tOldPath  );
}



 void  CDlgMediaControl::SelectFile()
{
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;	
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	int		iErr	=	-1;
    //  HRESULT hr;
    TCHAR szFileName[MAX_PATH];

	void  **  pp  =  get_ppShareMediaFile(  );
	if  (  !pp  )  return;


    // If this is the currently selected file, do nothing
    int nItem = m_ListFiles.GetCurSel();
    if (nItem == m_var.m_nCurrentFileSelection)
        return;

	
	traceLogA(  "Not finished, because the video format of files are not the same."  );
	return;

    // Remember the current selection to speed double-click processing
    m_var.m_nCurrentFileSelection = nItem;

    // Read file name from list box
	m_ListFiles.GetLBText(nItem, szFileName);

    // Remember current play state to restart playback
	int nCurrentState = pFuncs->pf_getShareMediaFileState(  *pp  );

    // First release any existing interfaces
    //  ResetDirectShow();
	this->OnBnClickedButtonStop(  );
	pFuncs->pf_exitShareMediaFile(  pp  );

	//
	if  (  pFuncs->pf_initShareMediaFile(  szFileName,  0,  0,  pp  )  )  {
		GetDlgItem(  IDC_BUTTON_PLAY  )->EnableWindow(  FALSE  );
		MessageBeep(0);
		goto  errLabel;
	}
	GetDlgItem(  IDC_BUTTON_PLAY  )->EnableWindow(  TRUE  );
	

    // Display useful information about this file
    //  DisplayFileInfo(szFilename);
    //  DisplayImageInfo();
    //  DisplayFileDuration();


	GetDlgItem(  IDC_BUTTON_FRAMESTEP  )->EnableWindow(  this->CanStep(  )  );
    // Set up the seeking trackbar and read capabilities
    ConfigureSeekbar();


    // If the user has asked to mute audio then we
    // need to mute this new clip before continuing.
	//  if (  m_var.pCapBmp->bGlobalMute)  muteAudio(  m_var.pCapBmp  );

    // If we were running when the user changed selection,
    // start running the newly selected clip
    if  (  nCurrentState == State_Running  )  {
		OnBnClickedButtonPlay(  );
		}
    else  {
          // Cue the first video frame
		  OnBnClickedButtonStop(  );
    }
	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		pFuncs->pf_exitShareMediaFile(  pp  );
	}

}


void CDlgMediaControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER, m_Seekbar);
	DDX_Control(pDX, IDC_COMBO_mediaFile, m_ListFiles);
}


BEGIN_MESSAGE_MAP(CDlgMediaControl, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CDlgMediaControl::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CDlgMediaControl::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_FRAMESTEP, &CDlgMediaControl::OnBnClickedButtonFramestep)
	ON_BN_CLICKED(IDC_CHECK_PLAYTHROUGH, &CDlgMediaControl::OnBnClickedCheckPlaythrough)
	ON_BN_CLICKED(IDC_CHECK_LOOP, &CDlgMediaControl::OnBnClickedCheckLoop)
	ON_BN_CLICKED(IDC_CHECK_MUTE, &CDlgMediaControl::OnBnClickedCheckMute)
	ON_WM_DESTROY()
//	ON_WM_MOUSEMOVE()
ON_WM_HSCROLL()
ON_CBN_SELCHANGE(IDC_COMBO_mediaFile, &CDlgMediaControl::OnCbnSelchangeCombomediafile)
END_MESSAGE_MAP()

static  DWORD	sdwTickCnt_close_mediaControl  =  0;


#if  0
__declspec(  dllexport  )  int  viewMediaControl_qmCmd(  HWND  hDlgParent,  int  iIndex_capAudio,  int  iIndex_capBmp,  HWND  *  phWnd_mediaControl  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int								iErr					=	-1;
	QY_MC					*		pQyMc					=	QY_GET_GBUF(  );
	int								iServiceId				=	CONST_qyServiceId_mis;
	QY_SERVICEGUI_INFO		*		pSci					=	getServiceGuiInfo(  pQyMc,  iServiceId  );
	if  (  !pSci  )  return  -1;
	MC_VAR_common			*		pProcInfo				=	(  MC_VAR_common  *  )pSci->pVar;
	if  (  !pProcInfo  )  return  -1;

	CDlgMediaControl		*		pDlg					=	NULL;
	RECT							rect;

	if  (  !hDlgParent  ||  !phWnd_mediaControl  )  return  -1;

	//  traceLogA(  "viewMediaControl enters"  );

	if  (  GetTickCount(  )  -  sdwTickCnt_close_mediaControl  <  pQyMc->cfg.usDelayInMsToViewToolbar  )  {
		iErr  =  0;  goto  errLabel;
	}

	//
	if  (  IsWindow(  *phWnd_mediaControl  )  )  {
		pDlg  =  (  CDlgMediaControl  *  )CDlgMediaControl::FromHandle(  *phWnd_mediaControl  );
		pDlg->m_var.dwTickCnt_lastMouseMove  =  GetTickCount(  );
		pDlg  =  NULL;
		if  (  IsIconic(  *phWnd_mediaControl  )  )  SendMessage(  *phWnd_mediaControl,  WM_SYSCOMMAND,  SC_RESTORE,  0  );
		iErr  =  0;  goto  errLabel;
	}

	*phWnd_mediaControl  =  NULL;

	//
	pDlg  =  new  CDlgMediaControl(  CWnd::FromHandle(  hDlgParent  )  );
	if  (  !pDlg  )  goto  errLabel;

	//
	pDlg->m_var.pProcInfo  =  pProcInfo;
	pDlg->m_var.iIndex_capAudio  =  iIndex_capAudio;
	pDlg->m_var.iIndex_capBmp  =  iIndex_capBmp;
	
	//
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;
	pDlg->ShowWindow(  SW_SHOW  );

	//  2013/06/10
	pDlg->m_var.dwTickCnt_lastMouseMove  =  GetTickCount(  );


	//  
	*phWnd_mediaControl  =  pDlg->m_hWnd;

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}
	if  (  !iErr  )  {
	}

	//  traceLogA(  "viewMediaControl leaves, iErr is %d",  iErr  );

	return  iErr;
}
#endif



#if  1	//  ndef  __SUPPORT_subProcessToStartShareMediaFile__

__declspec(  dllexport  )  int  viewMediaControl(  HWND  hDlgParent,  int  iIndex_capAudio,  int  iIndex_capBmp,  HWND  *  phWnd_mediaControl  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int								iErr					=	-1;
	QY_MC					*		pQyMc					=	QY_GET_GBUF(  );
	int								iServiceId				=	CONST_qyServiceId_mis;
	QY_SERVICEGUI_INFO		*		pSci					=	getServiceGuiInfo(  pQyMc,  iServiceId  );
	if  (  !pSci  )  return  -1;
	MC_VAR_isCli				*		pProcInfo				=	(  MC_VAR_isCli  *  )pSci->pVar;
	if  (  !pProcInfo  )  return  -1;

	CDlgMediaControl		*		pDlg					=	NULL;
	RECT							rect;

	if  (  !hDlgParent  ||  !phWnd_mediaControl  )  return  -1;

	//  traceLogA(  "viewMediaControl enters"  );

	if  (  GetTickCount(  )  -  sdwTickCnt_close_mediaControl  <  pQyMc->cfg.usDelayInMsToViewToolbar  )  {
		iErr  =  0;  goto  errLabel;
	}

	//
	if  (  IsWindow(  *phWnd_mediaControl  )  )  {
		pDlg  =  (  CDlgMediaControl  *  )CDlgMediaControl::FromHandle(  *phWnd_mediaControl  );
		pDlg->m_var.dwTickCnt_lastMouseMove  =  GetTickCount(  );
		pDlg  =  NULL;
		if  (  IsIconic(  *phWnd_mediaControl  )  )  SendMessage(  *phWnd_mediaControl,  WM_SYSCOMMAND,  SC_RESTORE,  0  );
		iErr  =  0;  goto  errLabel;
	}

	*phWnd_mediaControl  =  NULL;

	//
	pDlg  =  new  CDlgMediaControl(  CWnd::FromHandle(  hDlgParent  )  );
	if  (  !pDlg  )  goto  errLabel;

	//
	pDlg->m_var.pProcInfo  =  (  MC_VAR_common  *  )pProcInfo;
	pDlg->m_var.iIndex_capAudio  =  iIndex_capAudio;
	pDlg->m_var.iIndex_capBmp  =  iIndex_capBmp;
	
	//
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;
	pDlg->ShowWindow(  SW_SHOW  );

	//  2013/06/10
	pDlg->m_var.dwTickCnt_lastMouseMove  =  GetTickCount(  );


	//  
	*phWnd_mediaControl  =  pDlg->m_hWnd;

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}
	if  (  !iErr  )  {
	}

	//  traceLogA(  "viewMediaControl leaves, iErr is %d",  iErr  );

	return  iErr;
}

#endif



// CDlgMediaControl message handlers



BOOL CDlgMediaControl::OnInitDialog()
{
	CDialog::OnInitDialog();
	int					iErr	=	-1;
	QY_MC			*	pQyMc	=	QY_GET_GBUF(  );
	CString				fileStr;
	void			**	pp		=	get_ppShareMediaFile(  );
	if  (  !pp  )  goto  errLabel;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	if  (  !m_var.m_pParent  )  goto  errLabel;

#if  0
	if  (  isQmCmd(  )  )  {
		MC_VAR_qmCmd	*	pProcInfo	=	(  MC_VAR_qmCmd  *  )m_var.pProcInfo;
		m_var.pShmCmd  =  getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  pProcInfo->iIndex_shmCmd  );
		if  (  !m_var.pShmCmd  )  goto  errLabel;
		}
	else
#endif
	{
		  MC_VAR_isCli	*	pProcInfo	=	(  MC_VAR_isCli  *  )m_var.pProcInfo;
		  CAP_procInfo_mediaFileBmp	*	pCapBmp;
		  CAP_procInfo_mediaFileAudio	*	pCapAudio;
		  QY_SHARED_OBJ				*	pSharedObj;

		  pCapBmp	=	(  CAP_procInfo_mediaFileBmp  *  )getCapBmpBySth(  pProcInfo,  m_var.iIndex_capBmp,  CONST_capType_mediaFile  );
		  if  (  !pCapBmp  )  goto  errLabel;
		  pCapAudio  =  (  CAP_procInfo_mediaFileAudio  *  )getCapAudioBySth(  pProcInfo,  m_var.iIndex_capAudio,  0  );
		  if  (  !pCapAudio  )  traceLogA(  "pCapAudio is null"  );

		  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pCapBmp->iIndex_sharedObj  );
		  if  (  !pSharedObj  )  goto  errLabel;
		  //m_var.pShmCmd  =  getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  pSharedObj->iIndex_shmCmd  );
		  if  (  !m_var.pShmCmd  )  {
			  traceLogA(  "dlgMediaControl::OnInitDialog failed, pShmCmd is null"  );
			  goto  errLabel;
		  }
	}

	// Initialize seeking trackbar range
    m_Seekbar.SetRange(0, 100, TRUE);
    m_Seekbar.SetTicFreq(  1  );

	TCHAR	*	filePart;
	if  (  *pp  )  {
		SHARE_MEDIA_FILE	*	pShareMediaFile;
		pShareMediaFile  =  (  SHARE_MEDIA_FILE  *  )*pp;

		if  (  !GetFullPathName(  pShareMediaFile->tFile,  mycountof(  m_var.pathBuf  ),  m_var.pathBuf,  &filePart  )  )  goto  errLabel;
		}
	else  {
		  if  (  !GetFullPathName(  m_var.pShmCmd->path,  mycountof(  m_var.pathBuf  ),  m_var.pathBuf,  &filePart  )  )  goto  errLabel;
	}
	fileStr  =  filePart;
	filePart[0]  =  0;
	#if  0
		 this->FillFileList(  m_var.pathBuf  );
	#else
		  this->m_ListFiles.InsertString(  -1,  fileStr  );
	#endif
	this->m_ListFiles.SelectString(  -1,  fileStr  );
	m_var.m_nCurrentFileSelection  =  m_ListFiles.GetCurSel();

	GetDlgItem(  IDC_BUTTON_FRAMESTEP  )->EnableWindow(  this->CanStep(  )  );
	ConfigureSeekbar(  );
	ReadMediaPosition(  );

	//  int  state;
	//  state  =  getShareMediaFileState(  m_var.pSharedObj->pShareMediaFile  );
	//  if  (  state  ==  State_Running  )  {
	
	MACRO_setBtnPlayText(  );

	if  (  m_var.pShmCmd->bLooping  )  (  (  CButton  *  )GetDlgItem(  IDC_CHECK_LOOP  )  )->SetCheck(  BST_CHECKED  );
	if  (  m_var.pShmCmd->bGlobalMute  )  (  (  CButton  *  )GetDlgItem(  IDC_CHECK_MUTE  )  )->SetCheck(  BST_CHECKED  );
	
	StartSeekTimer(  );

#if  1
	GetDlgItem(  IDC_CHECK_PLAYTHROUGH  )->ShowWindow(  SW_HIDE  );
#endif


	iErr	=	0;
errLabel:
	if  (  iErr  )  {
		PostMessage(  WM_CLOSE,  0,  0  );
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMediaControl::OnTimer(UINT_PTR nIDEvent)
{
	//  CDlgVideos	*	pDlg  =  (  CDlgVideos  *  )m_var.m_pParent;	
	if  (  GetTickCount(  )  -  m_var.dwTickCnt_lastMouseMove  >  10000  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "dlgMediaControl: timer, to close"  )  );
		#endif
		SendMessage(  WM_CLOSE,  0,  0  );
		return;
	}

	// TODO: Add your message handler code here and/or call default
    ReadMediaPosition();

	CDialog::OnTimer(nIDEvent);
}

void CDlgMediaControl::PostNcDestroy()
{
	CDialog::PostNcDestroy();

	// TODO: Add your specialized code here and/or call the base class
	if  (  m_var.bCreated  )  {
		traceLogA(  "CDlgMediaControl::PostNcDestroy, delete this"  );
		delete this;
	}


}

void CDlgMediaControl::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	traceLogA(  "CDlgMediaControl::OnCancel(  )"  );

	DestroyWindow(  );	
}

void CDlgMediaControl::OnBnClickedButtonPlay()
{
	// TODO: Add your control notification handler code here
	int								state;
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	
	FUNCS_for_isCliHelp			*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	void						**	pp		=  get_ppShareMediaFile(  );
	if  (  !pp  )  return;

	state  =  pFuncs->pf_getShareMediaFileState(  *pp  );

	if  (  state  !=  State_Running  )  {
		pFuncs->pf_runShareMediaFile(  *pp  );
        //  Say(TEXT("Running"));
		}
    else  {
		  pFuncs->pf_pauseShareMediaFile(  *pp  );
          //  Say(TEXT("PAUSED"));
    }

	MACRO_setBtnPlayText(  );

}

void CDlgMediaControl::OnBnClickedButtonStop()
{
	HRESULT					hr;
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	
	FUNCS_for_isCliHelp			*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;
	IMediaSeeking		*	pMS					=	NULL;
	IMediaControl		*	pMC					=	NULL;
	void				**	pp					=	get_ppShareMediaFile(  );
	if  (  !pp  )  return;

	SHARE_MEDIA_FILE	*	pShareMediaFile		=  (  SHARE_MEDIA_FILE  *  )*pp;
	if  (  !pShareMediaFile  )  return;
	pMC  =  pShareMediaFile->m_pMC;
	pMS  =  pShareMediaFile->m_pMS;

    // Stop playback immediately with IMediaControl::Stop().
    pFuncs->pf_stopShareMediaFile(  *pp  );

	if (!pMC || !pMS)  goto  errLabel;

    // Wait for the stop to propagate to all filters
    OAFilterState fs;
    hr = pMC->GetState(500, &fs);
    if (FAILED(hr))
    {
        traceLogA(("Failed to read graph state!  hr=0x%x\r\n"), hr);
    }

    // Reset to beginning of media clip
    LONGLONG pos=0;
    hr = pMS->SetPositions(&pos, AM_SEEKING_AbsolutePositioning ,
                           NULL, AM_SEEKING_NoPositioning);
    if (FAILED(hr))
    {
        traceLogA(("Failed to seek to beginning of media!  hr=0x%x\r\n"), hr);
    }

    // Display the first frame of the media clip, if it contains video.
    // StopWhenReady() pauses all filters internally (which allows the video
    // renderer to queue and display the first video frame), after which
    // it sets the filters to the stopped state.  This enables easy preview
    // of the video's poster frame.
    hr = pMC->StopWhenReady();
    if (FAILED(hr))
    {
        traceLogA(("Failed in StopWhenReady!  hr=0x%x\r\n"), hr);
    }

    //  Say(TEXT("Stopped"));

errLabel:

    // Reset slider bar and position label back to zero
    ReadMediaPosition();

	MACRO_setBtnPlayText(  );

}



void CDlgMediaControl::OnBnClickedButtonFramestep()
{
    // Get the Frame Stepping Interface
	MC_VAR_isCli		*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;
	
	FUNCS_for_isCliHelp			*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  pProcInfo  );
	if  (  !pFuncs  )  return;

	void  **pp  =  get_ppShareMediaFile(  );
	if  ( !pp  )  return;

	SHARE_MEDIA_FILE	*	pShareMediaFile  =  (  SHARE_MEDIA_FILE  *  )*pp;
	if  (  !pShareMediaFile  )  return;
	if  (  !pShareMediaFile->m_pFS  )  return;

    HRESULT  hr;

    // The graph must be paused for frame stepping to work
	if (  pShareMediaFile->psCurrent  !=  State_Paused  )  {
		//  OnPause();
		pFuncs->pf_pauseShareMediaFile(  pShareMediaFile  );
	}

    // Step one frame
    hr = pShareMediaFile->m_pFS->Step(1, NULL);

    // Since the media position has changed slightly, update the
    // slider bar and position label.
    ReadMediaPosition();

	MACRO_setBtnPlayText(  );

    return;
}





void CDlgMediaControl::OnBnClickedCheckPlaythrough()
{
	// TODO: Add your control notification handler code here
}

void CDlgMediaControl::OnBnClickedCheckLoop()
{
	// TODO: Add your control notification handler code here

	m_var.pShmCmd->bLooping  ^=  1;
}

void CDlgMediaControl::OnBnClickedCheckMute()
{
	// TODO: Add your control notification handler code here

	m_var.pShmCmd->bGlobalMute ^= 1;

	//  if (  m_var.pCapBmp->bGlobalMute)  muteAudio(  m_var.pCapBmp->pShareMediaFile  );
	//  else  resumeAudio(  m_var.pCapBmp->pShareMediaFile  );

}

void CDlgMediaControl::OnDestroy()
{
	sdwTickCnt_close_mediaControl  =  GetTickCount(  );

	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
}



BOOL CDlgMediaControl::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	switch  (  pMsg->message  )  {
			case  WM_MOUSEMOVE:
			case  WM_LBUTTONDOWN:
			case  WM_RBUTTONDOWN:
			case  WM_CHAR:
				  m_var.dwTickCnt_lastMouseMove  =  GetTickCount(  );				  
				  break;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgMediaControl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default

	HandleTrackbar(  nSBCode  );

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDlgMediaControl::OnCbnSelchangeCombomediafile()
{
	// TODO: Add your control notification handler code here
	SelectFile(  );
}
