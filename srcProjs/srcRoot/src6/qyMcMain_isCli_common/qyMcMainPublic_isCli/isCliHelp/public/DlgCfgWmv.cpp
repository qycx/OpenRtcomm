// DlgCfgWmv.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"qyMc.h"
#include	"myresource.h"
#include	"DlgCfgWmv.h"


__declspec(  dllexport  )  int  showDlgCfgWmv(  HWND  hParent  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int		iRet	=	-1;

	
	CDlgCfgWmv	dlg(  CWnd::FromHandle(  hParent  )  );

	iRet  =  dlg.DoModal(  );

	return  iRet;

}

/*
void SetEncodingDefaults(  VideoEncParams  &  g_VideoEncodingParams,  HWND hDlg)
{
    HWND hcb;

    DWORD ComplexityLive = 0;
    DWORD ComplexityOffline = 0;
    DWORD ComplexityMax = 0;
    char  ComplexityString[15];
    HRESULT hr = S_OK;

    g_VideoEncodingParams.fFrameRate = 29.97F;
    
    // Other codecs not supported in this sample
    g_VideoEncodingParams.dwTag = WMCFOURCC_WMV3;

    g_VideoEncodingParams.fIsVBR = FALSE;
    g_VideoEncodingParams.nBitrate = 0;
    g_VideoEncodingParams.nBufferDelay = 5000;
    g_VideoEncodingParams.nKeyDist = 8;
    g_VideoEncodingParams.nProfile = P_MAIN;
    g_VideoEncodingParams.nQuality = 75;
    g_VideoEncodingParams.nVBRQuality = 98;
    
    hcb = GetDlgItem(hDlg, IDC_CBR);
    SendMessage(hcb, BM_SETCHECK, BST_CHECKED, NULL);

    //Disable while CBR is checked
    hcb = GetDlgItem( hDlg, IDC_VBRQUALITY);
    EnableWindow( hcb, FALSE );

    SetDlgFloat(hDlg, IDC_FRAMERATE, g_VideoEncodingParams.fFrameRate);
    SetDlgItemInt(hDlg, IDC_BUFFERDELAY, g_VideoEncodingParams.nBufferDelay, TRUE);

    SetDlgItemInt(hDlg, IDC_BITRATE, g_VideoEncodingParams.nBitrate, TRUE);

    SetDlgItemInt(hDlg, IDC_MAXKEYDISTANCE, g_VideoEncodingParams.nKeyDist, TRUE);

    SetDlgItemInt(hDlg, IDC_QUALITY, g_VideoEncodingParams.nQuality, TRUE);
    SetDlgItemInt(hDlg, IDC_VBRQUALITY, g_VideoEncodingParams.nVBRQuality, TRUE);

    //Add profiles and set default selection
    hcb = GetDlgItem(hDlg, IDC_PROFILES);
    SendMessage(hcb, LB_ADDSTRING, NULL, (LPARAM) "Main");
    SendMessage(hcb, LB_ADDSTRING, NULL, (LPARAM) "Simple");
    SendMessage(hcb, LB_ADDSTRING, NULL, (LPARAM) "Complex");
    SendMessage(hcb, LB_SETCURSEL, g_VideoEncodingParams.nProfile, NULL);
    
    // Add complexity levels.
    hcb = GetDlgItem(hDlg, IDC_COMPLEXITY);

    // Get the complexity levels for the codec.
    hr = GetComplexitySettings(&ComplexityLive, 
                               &ComplexityOffline, 
                               &ComplexityMax);

    // Loop through the available complexity settings, 
    //  adding an entry for each.
    for(DWORD index = 0; index <= ComplexityMax; index++)
    {
        // Assemble the complexity list entry string 
        if(index == ComplexityLive)
            sprintf(ComplexityString, "%d (Live)", index);
        else if(index == ComplexityOffline)
            sprintf(ComplexityString, "%d (Offline)", index);
        else if(index == ComplexityMax)
            sprintf(ComplexityString, "%d (Max)", index);
        else
            sprintf(ComplexityString, "%d", index);
            
        // Add the string to the list box.        
        SendMessage(hcb, LB_ADDSTRING, NULL, (LPARAM) ComplexityString);
    }
    SendMessage(hcb, LB_SETCURSEL, ComplexityOffline, NULL);

}
*/


// CDlgCfgWmv dialog

IMPLEMENT_DYNAMIC(CDlgCfgWmv, CDialog)

CDlgCfgWmv::CDlgCfgWmv(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCfgWmv::IDD, pParent)
{

}

CDlgCfgWmv::~CDlgCfgWmv()
{
}

void CDlgCfgWmv::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgCfgWmv, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgCfgWmv::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgCfgWmv message handlers

void CDlgCfgWmv::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

BOOL CDlgCfgWmv::OnInitDialog()
{
	CDialog::OnInitDialog();
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );



	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
