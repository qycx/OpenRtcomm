
#include	"stdafx.h"

#include	<shellapi.h>

#include	"qnmTrayProc.h"


 BOOL  sendTrayMsg(  HINSTANCE  hInstance,  HWND  hWnd,  int  iIDR_TRAY, DWORD  opMsg,  int  iIDR_iconStr,  unsigned  int  nWM_TRAYNOTIFY  )
{
	NOTIFYICONDATA m_nid;

	memset(  &m_nid,  0,  sizeof(  m_nid  )  );

	m_nid.hWnd  =  hWnd;
	m_nid.cbSize = sizeof(m_nid);
	m_nid.uID = iIDR_TRAY;	// never changes after construction

        // LoadIcon seems to mess up 16x16 images. Maybe we should use
        // LoadImage instead?
        m_nid.hIcon = LoadIcon(  hInstance, MAKEINTRESOURCE(  iIDR_iconStr  )  );
  	//m_nid.hIcon = (HICON)LoadImage(pApp->m_instance,
        //                               MAKEINTRESOURCE(IDR_TRAY),
        //                               IMAGE_ICON, 0, 0,
        //                               LR_DEFAULTCOLOR|LR_SHARED);

	m_nid.uFlags = NIF_ICON | NIF_MESSAGE;
	m_nid.uCallbackMessage = nWM_TRAYNOTIFY;
	m_nid.szTip[0] = '\0';
	// Use resource string as tip if there is one
	if (LoadString(  hInstance, iIDR_iconStr, m_nid.szTip, sizeof(m_nid.szTip))) {
		m_nid.uFlags |= NIF_TIP;
	}
	return (bool) (Shell_NotifyIcon(opMsg, &m_nid) != 0);
}
