// CSDemoServerDlg.h : 头文件
//

#pragma once
//#include "afxwin.h"
//#include <string>
//#include "afxcmn.h"

//#include "CServerAuth.h"



class CServerAuth;

// CCSDemoServerDlg 对话框
class CCSDemoServerDlg : public CDialog
{
// 构造
public:
    CCSDemoServerDlg(CWnd* pParent = NULL);// 标准构造函数
    virtual ~CCSDemoServerDlg();

// 对话框数据
    enum { IDD = IDD_CSDEMOSERVER_DIALOG };

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);// DDX/DDV 支持

// 实现
protected:
    HICON m_hIcon;

    // 生成的消息映射函数
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
    DECLARE_MESSAGE_MAP()

private:
    //
	static DWORD WINAPI ReciveClientRequestThread(LPVOID lpParameter);
	void DisplayAuthResult();

    HANDLE m_ReciveClientReqThreadHandle;
    SOCKET m_ListenSocket;

public:
    CButton m_StartServer;
    CIPAddressCtrl m_GateWayIP;
    CIPAddressCtrl m_ServerIP;
    BOOL m_ListenThreadStopFlag;

	CServerAuth* m_pServerAuth;
public:
    afx_msg void OnBnClickedButtonStop();
	int m_RadioGroupConnMode;
	afx_msg void OnBnClickedRadioConnMode();
};
